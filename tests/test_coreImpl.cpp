#include "coreImpl.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using namespace Core::impl;
using namespace testing;

class FixtureCollatzProcessorImpl : public Test {
 protected:
  static CollatzProcessorImpl object;

  ~FixtureCollatzProcessorImpl() {
    for (int i = 0; i < object.s_ThreadResults.size(); ++i) {
      object.s_ThreadResults[i] = std::make_pair(0, 0);
    }
    for (int i = 0; i < object.cs_UpperLimitCap; ++i) {
      object.s_pCache[i].store(0);
    }
    object.IsOverflow = false;
  }
};
CollatzProcessorImpl FixtureCollatzProcessorImpl::object;

TEST_F(FixtureCollatzProcessorImpl, TestConstructor) {
  EXPECT_EQ(object.cs_CoresCount, object.s_ThreadResults.size());
  EXPECT_EQ(object.cs_CoresCount, object.s_ThreadPool.size());
}

TEST_F(FixtureCollatzProcessorImpl, TestWillOverflow) {
  EXPECT_FALSE(object.WillOverflow(object.cs_MaxSizeBeforeOverflow));
  EXPECT_TRUE(object.WillOverflow(object.cs_MaxSizeBeforeOverflow + 1));
}
TEST_F(FixtureCollatzProcessorImpl, FindFinalResult) {
  object.s_ThreadResults[0] = std::make_pair(3, 7);
  object.s_ThreadResults[1] = std::make_pair(5, 5);
  object.s_ThreadResults[2] = std::make_pair(16, 4);
  EXPECT_EQ(object.FindFinalResult(), std::make_pair(3, 7));
  EXPECT_EQ(object.s_ThreadResults[0], std::make_pair(0, 0));
}

struct CalculateCollatzElement {
  qsizetype CurrentElement;
  const qsizetype UpperLimit;
  std::vector<qsizetype> CalculatedCache;
  CalculateCollatzElement(const qsizetype Element, const qsizetype UpperLimit)
      : CurrentElement{Element}, UpperLimit{UpperLimit} {
    CalculatedCache.resize(UpperLimit, 0);
    qsizetype StepCounter = 0;
    this->MakeCalculation(this->CurrentElement, StepCounter);
  }

 private:
  void MakeCalculation(qsizetype CurrentElement, qsizetype& StepCounter) {
    if (CurrentElement == 1) return;
    if (CurrentElement < this->UpperLimit + 1 &&
        CalculatedCache[CurrentElement - 1] != 0) {
      StepCounter += CalculatedCache[CurrentElement - 1];
      return;
    }
    MakeCalculation(
        CurrentElement % 2 ? CurrentElement * 3 + 1 : CurrentElement / 2,
        StepCounter);
    ++StepCounter;
    if (CurrentElement < this->UpperLimit + 1 &&
        CalculatedCache[CurrentElement - 1] == 0)
      CalculatedCache[CurrentElement - 1] = StepCounter;
    return;
  }
};

void PrintTo(const CalculateCollatzElement& element, std::ostream* os) {
  *os << "CurrentElement: " << element.CurrentElement << " ";
  *os << "UpperLimit: " << element.UpperLimit << " ";
  *os << "Cache size: " << element.CalculatedCache.size() << " | ";
  for (int i = 0; i < element.CalculatedCache.size() && i < 16; ++i) {
    *os << element.CalculatedCache[i] << " ";
  }
}

class TestCalculateCollatz : public WithParamInterface<CalculateCollatzElement>,
                             public FixtureCollatzProcessorImpl {};

TEST_P(TestCalculateCollatz, DifferentElementsProcessing) {
  auto Element = this->GetParam();
  qsizetype StepCounter = 0;
  object.CalculateCollatz(Element.CurrentElement, StepCounter);
  for (int i = 0; i < Element.CalculatedCache.size(); ++i) {
    EXPECT_EQ(object.s_pCache[i], Element.CalculatedCache[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(
    NumbersAndCorrespondingCacheState, TestCalculateCollatz,
    testing::Values(
        CalculateCollatzElement{1, 1}, CalculateCollatzElement{3, 16},
        CalculateCollatzElement{150000, CollatzProcessorImpl::cs_UpperLimitCap},
        CalculateCollatzElement{CollatzProcessorImpl::cs_UpperLimitCap,
                                CollatzProcessorImpl::cs_UpperLimitCap}));

struct RunElement {
  const qsizetype IntervalBegin;
  const qsizetype IntervalEnd;
  const qsizetype IndexInResultsVector;
  const qsizetype ExpectedNumber;
  const qsizetype ExpectedStepCount;
};

void PrintTo(const RunElement& element, std::ostream* os) {
  *os << "[" << element.IntervalBegin << ", " << element.IntervalEnd << "] ";
  *os << "IndexInREsultsVector: " << element.IndexInResultsVector << " ";
  *os << "Expected Number/StepCount: " << element.ExpectedNumber << "/"
      << element.ExpectedStepCount << " ";
}

class TestRun : public WithParamInterface<RunElement>,
                public FixtureCollatzProcessorImpl {};

TEST_P(TestRun, TestDifferencIntervals) {
  auto CurrentElement = this->GetParam();
  std::stop_token StopToken;
  object.Run(StopToken, CurrentElement.IntervalBegin,
             CurrentElement.IntervalEnd, CurrentElement.IndexInResultsVector);
  EXPECT_EQ(object.s_ThreadResults[CurrentElement.IndexInResultsVector].first,
            CurrentElement.ExpectedNumber);
  EXPECT_EQ(object.s_ThreadResults[CurrentElement.IndexInResultsVector].second,
            CurrentElement.ExpectedStepCount);
}

INSTANTIATE_TEST_SUITE_P(IntervalsAndCorrespondingLongestChain, TestRun,
                         testing::Values(RunElement{0, 1, 0, 0, 0},
                                         RunElement{0, 5, 2, 3, 7},
                                         RunElement{0, 10, 8, 9, 19}));

struct StartProcessingElement {
  const bool RequireStop;
  const qsizetype ThreadLimit;
  const qsizetype UpperLimit;
  const std::pair<qsizetype, qsizetype> ExpectedResult;
};

void PrintTo(const StartProcessingElement& element, std::ostream* os) {
  *os << std::boolalpha;
  *os << "RequireStop: " << element.RequireStop << " ";
  *os << "ThreadLimit: " << element.ThreadLimit << " ";
  *os << "UpperLimit: " << element.UpperLimit << " ";
  *os << "Expected Number/StepCount: " << element.ExpectedResult.first << "/"
      << element.ExpectedResult.second << " ";
}

class TestStartProcessing : public WithParamInterface<StartProcessingElement>,
                            public FixtureCollatzProcessorImpl {};

TEST_P(TestStartProcessing, TestDifferentThreadAndUpperLimits) {
  auto CurrentElement = this->GetParam();
  std::jthread ProcessingThread;
  ProcessingThread = std::jthread{[&](std::stop_token StopToken) {
    if (CurrentElement.RequireStop) ProcessingThread.request_stop();
    EXPECT_EQ(object.StartProcessing(StopToken, CurrentElement.ThreadLimit,
                                     CurrentElement.UpperLimit),
              CurrentElement.ExpectedResult);
  }};
  ProcessingThread.join();
}

INSTANTIATE_TEST_SUITE_P(
    NumberOfThreadsAndUpperLimitIfStopRequested, TestStartProcessing,
    testing::Values(
        StartProcessingElement{false, 1, 5, std::make_pair(3, 7)},
        StartProcessingElement{true, 1, 5,
                               std::make_pair(Signals::STOP, Signals::STOP)},
        StartProcessingElement{false, CollatzProcessorImpl::cs_CoresCount / 2,
                               150000, std::make_pair(142587, 374)},
        StartProcessingElement{false, CollatzProcessorImpl::cs_CoresCount,
                               CollatzProcessorImpl::cs_UpperLimitCap,
                               std::make_pair(63728127, 949)}));
