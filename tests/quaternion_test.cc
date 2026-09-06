#include <iostream>
#include <cassert>

#include "manifold/quaternion/quaternion.h"
#include "manifold/autodiff/dual.h"

void assert_close(double actual, double expected, double tol = 1e-12) {
  assert(std::abs(actual - expected) < tol);
}

bool should_return_unit_quaternion_while_input_zero_vector() {
  const QuaternionCartesianSpace<double> qcs(0.0, 0.0, 0.0);
  const Quaternion<double> q = qcs.Exp();
  assert_close(q.w(), 1.0);
  assert_close(q.x(), 0.0);
  assert_close(q.y(), 0.0);
  assert_close(q.z(), 0.0);
  return true;
}

bool should_return_zero_vector_when_input_is_unit_quaternion() {
  const Quaternion<double> q(0.0, 0.0, 0.0, 1.0);
  const QuaternionCartesianSpace<double> qcs = q.Log();
  assert_close(qcs.x(), 0.0);
  assert_close(qcs.y(), 0.0);
  assert_close(qcs.z(), 0.0);
  return true;
}

bool should_recover_original_vector_when_exp_and_log() {
  const QuaternionCartesianSpace<double> theta(0.1, -0.2, 0.3);
  const auto theta_recovered = theta.Exp().Log();

  assert_close(theta.x(), theta_recovered.x());
  assert_close(theta.y(), theta_recovered.y());
  assert_close(theta.z(), theta_recovered.z());
  return true;
}

bool should_keep_same_quaternion_when_multiplied_by_identity() {
  const Quaternion<double> q = QuaternionCartesianSpace<double>(0.1, -0.2, 0.3).Exp();
  const Quaternion<double> I = QuaternionCartesianSpace<double>(0.0, 0.0, 0.0).Exp();

  const auto q_I = q * I;

  assert_close(q.w(), q_I.w());
  assert_close(q.x(), q_I.x());
  assert_close(q.y(), q_I.y());
  assert_close(q.z(), q_I.z());

  return true;
}

bool should_get_identity_when_multplied_by_inverse() {
  const Quaternion<double> q = QuaternionCartesianSpace<double>(0.1, -0.2, 0.3).Exp();

  const auto I = q * q.inverse();

  assert_close(I.w(), 1.0);
  assert_close(I.x(), 0.0);
  assert_close(I.y(), 0.0);
  assert_close(I.z(), 0.0);

  return true;
}

bool should_differentiate_quaternion_exp_about_x_axis() {
  const Dual<3> theta_x(0.4, {1.0, 0.0, 0.0});
  const Dual<3> theta_y(0.0, {0.0, 1.0, 0.0});
  const Dual<3> theta_z(0.0, {0.0, 0.0, 1.0});

  const QuaternionCartesianSpace<Dual<3>> phi(theta_x, theta_y, theta_z);
  const Quaternion<Dual<3>> q = phi.Exp();

  assert_close(q.x().value(), std::sin(0.2));
  assert_close(q.w().value(), std::cos(0.2));

  const double radial_derivative = 0.5 * std::cos(0.2);
  const double transverse_derivative = std::sin(0.2) / 0.4;
  const double scalar_derivative = -0.5 * std::sin(0.2);

  const auto& dx = q.x().derivative();
  assert_close(dx[0], radial_derivative);
  assert_close(dx[1], 0.0);
  assert_close(dx[2], 0.0);

  const auto& dy = q.y().derivative();
  assert_close(dy[0], 0.0);
  assert_close(dy[1], transverse_derivative);
  assert_close(dy[2], 0.0);

  const auto& dz = q.z().derivative();
  assert_close(dz[0], 0.0);
  assert_close(dz[1], 0.0);
  assert_close(dz[2], transverse_derivative);

  const auto& dw = q.w().derivative();
  assert_close(dw[0], scalar_derivative);
  assert_close(dw[1], 0.0);
  assert_close(dw[2], 0.0);

  return true;
}

int main() {
  std::cout << "Starting quaternion test" << std::endl;
  int passed = 0;
  passed += should_return_unit_quaternion_while_input_zero_vector() ? 1 : 0;
  passed += should_return_zero_vector_when_input_is_unit_quaternion() ? 1 : 0;
  passed += should_recover_original_vector_when_exp_and_log() ? 1 : 0;
  passed += should_keep_same_quaternion_when_multiplied_by_identity() ? 1 : 0;
  passed += should_get_identity_when_multplied_by_inverse() ? 1 : 0;
  passed += should_differentiate_quaternion_exp_about_x_axis() ? 1 : 0;
  std::cout << "Ending quaternion test, " << passed << " tests passed" << std::endl;
  return 0;
}
