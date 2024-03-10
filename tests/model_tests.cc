#include <gtest/gtest.h>

#include "../src/Controller/Controller.h"

namespace s21 {
class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  s21::Model model{};
  s21::Controller controller{&model};
};

TEST_F(ModelTest, SineTest) {
  std::string expression = "sin(10)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.17364817766693033};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);
  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, CosineTest) {
  std::string expression = "cos(10)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.98480775301220802};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);
  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, TangentTest) {
  std::string expression = "tan(10)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.17632698070846498};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);
  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, InvertSineTest) {
  std::string expression = "asin(0.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.72883358640186935};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);
  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, InvertSineErrorTest) {
  std::string expression = "asin(1.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};
  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);
  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, InvertCosineTest) {
  std::string expression = "acos(0.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.84196274039302721};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, InvertCosineErrorTest) {
  std::string expression = "acos(1.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, SqrtTest1) {
  std::string expression = "sqrt(1.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{1.2907362240210043};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, SqrtTest2) {
  std::string expression = "sqrt(0.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.8160882305241266};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, SqrtErrorTest) {
  std::string expression = "sqrt(-1.666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, CommonLogarithmTest) {
  std::string expression = "log(666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{2.823474229170301};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, CommonLogarithmErrorTest1) {
  std::string expression = "log(0)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, CommonLogarithmErrorTest2) {
  std::string expression = "log(-100)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, NaturalLogarithmTest) {
  std::string expression = "ln(666)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{6.5012896705403893};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, NaturalLogarithmErrorTest1) {
  std::string expression = "ln(0)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, NaturalLogarithmErrorTest2) {
  std::string expression = "ln(-100)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, AdditionTest) {
  std::string expression = "1.5+1.4";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{2.8999999999999999};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, NoOperatorsAndFuncsTest) {
  std::string expression = "1.4";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{1.4};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, MultipleOperatorsTest1) {
  std::string expression = "1235+12314-124124-1";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{-110576};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, MultipleOperatorsTest2) {
  std::string expression = "1235/100000+0.00061*5235/111";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0.041118918918918917};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, DivisionByZeroTest) {
  std::string expression = "123/0";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, ModulusByZeroTest1) {
  std::string expression = "123%0";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, ModulusByZeroTest2) {
  std::string expression = "1%(1-1)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, ParethesisTest) {
  std::string expression = "(1+1)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{2};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, NestedTwoParethesisTest1) {
  std::string expression = "((1+1) / 2)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{1};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, NestedTwoParethesisTest2) {
  std::string expression = "(1+1*(100 + 100))";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{201};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, NestedFourParethesisTest) {
  std::string expression =
      "(1+(sin(1 - (15 * 4) / 5 - (11 + "
      "15))*(911*(900/140)-cos(2*(sin(1))))-100*sin(11) / 98765/sin(4))*(100 - "
      "(sin(1) ^ 2 + cos(1) ^ 2) + 100))";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{-701252.64253988361};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, UnaryOperatorsTest1) {
  std::string expression = "-(pi)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{-M_PI};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, UnaryOperatorsTest2) {
  std::string expression = "-(-pi)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{M_PI};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, UnaryOperatorsTest3) {
  std::string expression = "-(+(-(pi)))";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{M_PI};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}
TEST_F(ModelTest, UnaryOperatorsTest4) {
  std::string expression = "-(-100 + 10)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{90};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, false);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, UnaryOperatorsErrorTest1) {
  std::string expression = "-(-+100 + 10)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, UnaryOperatorsErrorTest2) {
  std::string expression = "-+100 + 10";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, MismatchedParethesis1) {
  std::string expression = "-100 + 10)";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, MismatchedParethesis2) {
  std::string expression = "-100 + 10(()";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, EmptyParethesis1) {
  std::string expression = "-100 + 10 + ()";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST_F(ModelTest, EmptyParethesis2) {
  std::string expression = "-100 + 10 + (1) - ()";
  int error_code = controller.ExpressionCalculate(expression);
  double result = controller.ExpressionGetResult();
  double expected_result{0};

  bool is_error = error_code > 0;
  ASSERT_EQ(is_error, true);

  EXPECT_DOUBLE_EQ(result, expected_result);
}

}  // namespace s21
