#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "manifold/quaternion/quaternion.h"
#include "manifold/autodiff/dual.h"

constexpr double kStepSize = 0.1;

void assert_close(double actual, double expected, double tolerance = 1e-3) {
  if (std::abs(actual - expected) >= tolerance) {
    std::cerr << "Expected " << expected << ", got " << actual << std::endl;
    std::abort();
  }
}

bool should_optimize_one_axis_rotation_problem() {
  const auto observed_angle_1 = QuaternionCartesianSpace(0.5, 0.0, 0.0);
  const auto observed_angle_2 = QuaternionCartesianSpace(0.3, 0.0, 0.0);
  const auto observed_angle_3 = QuaternionCartesianSpace(0.4, 0.0, 0.0);
  const auto observed_q_1 = observed_angle_1.Exp();
  const auto observed_q_2 = observed_angle_2.Exp();
  const auto observed_q_3 = observed_angle_3.Exp();

  const auto initial_guess = QuaternionCartesianSpace(0.45, 0.0, 0.0);
  auto guess_q = initial_guess.Exp();

  for (int i=0; i<5; i++) {
    auto perturbation_x = Dual<3>(0.0, {1.0, 0.0, 0.0});
    auto perturbation_y = Dual<3>(0.0, {0.0, 1.0, 0.0});
    auto perturbation_z = Dual<3>(0.0, {0.0, 0.0, 1.0});
    auto perturbation = QuaternionCartesianSpace<Dual<3>>(perturbation_x, perturbation_y, perturbation_z);
    auto perturbed_q = perturbation.Exp() * guess_q;

    const auto r_1 = (perturbed_q * observed_q_1.inverse()).Log();
    const auto r_2 = (perturbed_q * observed_q_2.inverse()).Log();
    const auto r_3 = (perturbed_q * observed_q_3.inverse()).Log();

    const auto error = SquaredNorm(r_1) + SquaredNorm(r_2) + SquaredNorm(r_3);

    const double update_angle_x = -error.derivative()[0] * kStepSize;
    const double update_angle_y = -error.derivative()[1] * kStepSize;
    const double update_angle_z = -error.derivative()[2] * kStepSize;

    const auto update = QuaternionCartesianSpace(
        update_angle_x, update_angle_y, update_angle_z).Exp();
    guess_q = update * guess_q;
  }

  const auto optimized_angle = guess_q.Log();
  assert_close(optimized_angle.x(), 0.4);
  assert_close(optimized_angle.y(), 0.0);
  assert_close(optimized_angle.z(), 0.0);

  const double quaternion_squared_norm =
      guess_q.x() * guess_q.x()
      + guess_q.y() * guess_q.y()
      + guess_q.z() * guess_q.z()
      + guess_q.w() * guess_q.w();
  assert_close(quaternion_squared_norm, 1.0, 1e-12);

  return true;
}

int main() {
  std::cout << "Starting optimization test" << std::endl;
  int passed = 0;
  passed += should_optimize_one_axis_rotation_problem() ? 1 : 0;
  std::cout << "Ending optimization test, " << passed << " tests passed" << std::endl;
  return 0;
}
