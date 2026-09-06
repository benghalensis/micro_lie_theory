#include <cassert>
#include <cmath>
#include <iostream>

#include "manifold/autodiff/dual.h"

using TestDual = Dual<1>;

void assert_close(double actual, double expected, double tol = 1e-12) {
  assert(std::abs(actual - expected) < tol);
}

bool should_return_correct_value_when_input_quadratic_equation() {
  TestDual x(2.0, {1.0});
  TestDual three(3.0, {0.0});

  const TestDual y = x * x + three * x;

  assert_close(y.value(), 10.0);
  assert_close(y.derivative()[0], 7.0);

  return true;
}

bool should_return_correct_value_when_input_is_sin() {
  const TestDual x(2.0, {1.0});
  const TestDual y = sin(x * x);

  assert_close(y.value(), std::sin(4.0));
  assert_close(y.derivative()[0], 4.0 * std::cos(4.0));

  return true;
}

bool should_subtract_values_and_derivatives() {
  const TestDual left(5.0, {2.0});
  const TestDual right(3.0, {0.5});

  const TestDual result = left - right;

  assert_close(result.value(), 2.0);
  assert_close(result.derivative()[0], 1.5);

  return true;
}

bool should_divide_values_and_apply_quotient_rule() {
  const TestDual numerator(8.0, {3.0});
  const TestDual denominator(2.0, {0.5});

  const TestDual result = numerator / denominator;

  assert_close(result.value(), 4.0);
  assert_close(result.derivative()[0], 0.5);

  return true;
}

bool should_return_correct_value_when_input_is_cos() {
  const TestDual x(2.0, {1.0});
  const TestDual y = cos(x * x);

  assert_close(y.value(), std::cos(4.0));
  assert_close(y.derivative()[0], -4.0 * std::sin(4.0));

  return true;
}

bool should_return_correct_value_when_input_is_sqrt() {
  const TestDual x(9.0, {6.0});
  const TestDual y = sqrt(x);

  assert_close(y.value(), 3.0);
  assert_close(y.derivative()[0], 1.0);

  return true;
}

bool should_return_correct_value_when_input_is_atan2() {
  const TestDual y_variable(1.0, {1.0});
  const TestDual x_constant(2.0, {0.0});
  const TestDual angle_from_y = atan2(y_variable, x_constant);

  assert_close(angle_from_y.value(), std::atan2(1.0, 2.0));
  assert_close(angle_from_y.derivative()[0], 0.4);

  const TestDual y_constant(1.0, {0.0});
  const TestDual x_variable(2.0, {1.0});
  const TestDual angle_from_x = atan2(y_constant, x_variable);

  assert_close(angle_from_x.value(), std::atan2(1.0, 2.0));
  assert_close(angle_from_x.derivative()[0], -0.2);

  return true;
}

int main() {
  std::cout << "Starting dual test" << std::endl;
  int passed = 0;
  passed += should_return_correct_value_when_input_quadratic_equation() ? 1 : 0;
  passed += should_return_correct_value_when_input_is_sin() ? 1 : 0;
  passed += should_subtract_values_and_derivatives() ? 1 : 0;
  passed += should_divide_values_and_apply_quotient_rule() ? 1 : 0;
  passed += should_return_correct_value_when_input_is_cos() ? 1 : 0;
  passed += should_return_correct_value_when_input_is_sqrt() ? 1 : 0;
  passed += should_return_correct_value_when_input_is_atan2() ? 1 : 0;
  std::cout << "Ending dual test, " << passed << " tests passed" << std::endl;
  return 0;
}
