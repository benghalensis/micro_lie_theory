#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

#include "manifold/autodiff/dual.h"
#include "manifold/quaternion/quaternion.h"

using Vector3 = std::array<double, 3>;
using Matrix3 = std::array<std::array<double, 3>, 3>;

constexpr double kLearningRate = 0.1;

struct ResidualLinearization {
  Vector3 residual{};
  Matrix3 jacobian{};
};

Quaternion<Dual> ToDual(const Quaternion<double>& q) {
  return Quaternion<Dual>(
      Dual(q.x(), 0.0),
      Dual(q.y(), 0.0),
      Dual(q.z(), 0.0),
      Dual(q.w(), 0.0));
}

Quaternion<double> Exp(const Vector3& tangent) {
  return QuaternionCartesianSpace<double>(
      tangent[0], tangent[1], tangent[2]).Exp();
}

Vector3 Values(const QuaternionCartesianSpace<double>& tangent) {
  return {tangent.x(), tangent.y(), tangent.z()};
}

double SquaredNorm(const Vector3& vector) {
  return vector[0] * vector[0]
      + vector[1] * vector[1]
      + vector[2] * vector[2];
}

ResidualLinearization LinearizeResidual(
    const Quaternion<double>& observation,
    const Quaternion<double>& estimate) {
  ResidualLinearization result;

  for (int column = 0; column < 3; ++column) {
    const QuaternionCartesianSpace<Dual> perturbation(
        Dual(0.0, column == 0 ? 1.0 : 0.0),
        Dual(0.0, column == 1 ? 1.0 : 0.0),
        Dual(0.0, column == 2 ? 1.0 : 0.0));

    const Quaternion<Dual> perturbed_estimate =
        perturbation.Exp() * ToDual(estimate);
    const QuaternionCartesianSpace<Dual> residual =
        (ToDual(observation) * perturbed_estimate.inverse()).Log();

    if (column == 0) {
      result.residual = {
          residual.x().value(),
          residual.y().value(),
          residual.z().value()};
    }

    result.jacobian[0][column] = residual.x().derivative();
    result.jacobian[1][column] = residual.y().derivative();
    result.jacobian[2][column] = residual.z().derivative();
  }

  return result;
}

double Cost(
    const std::array<Quaternion<double>, 6>& observations,
    const Quaternion<double>& estimate) {
  double cost = 0.0;
  for (const auto& observation : observations) {
    const Vector3 residual =
        Values((observation * estimate.inverse()).Log());
    cost += 0.5 * SquaredNorm(residual);
  }
  return cost;
}

bool should_optimize_a_full_3d_rotation() {
  const Quaternion<double> target = Exp({0.35, -0.25, 0.20});
  const std::array<Quaternion<double>, 6> observations{
      Exp({0.03, 0.00, 0.00}) * target,
      Exp({-0.03, 0.00, 0.00}) * target,
      Exp({0.00, 0.025, 0.00}) * target,
      Exp({0.00, -0.025, 0.00}) * target,
      Exp({0.00, 0.00, 0.02}) * target,
      Exp({0.00, 0.00, -0.02}) * target};

  Quaternion<double> estimate = Exp({-0.20, 0.15, -0.10});
  const double initial_cost = Cost(observations, estimate);

  for (int iteration = 0; iteration < 100; ++iteration) {
    Vector3 gradient{};

    for (const auto& observation : observations) {
      const ResidualLinearization linearization =
          LinearizeResidual(observation, estimate);

      for (int row = 0; row < 3; ++row) {
        for (int residual_component = 0;
             residual_component < 3;
             ++residual_component) {
          gradient[row] +=
              linearization.jacobian[residual_component][row]
              * linearization.residual[residual_component];

        }
      }
    }

    Vector3 delta{};
    for (int row = 0; row < 3; ++row) {
      delta[row] = -kLearningRate * gradient[row];
    }

    estimate = Exp(delta) * estimate;

    if (SquaredNorm(delta) < 1e-20) {
      break;
    }
  }

  const double final_cost = Cost(observations, estimate);
  const Vector3 target_error =
      Values((target * estimate.inverse()).Log());

  assert(final_cost < initial_cost);
  assert(SquaredNorm(target_error) < 1e-16);
  return true;
}

int main() {
  std::cout << "Starting full quaternion optimization test" << std::endl;
  const bool passed = should_optimize_a_full_3d_rotation();
  std::cout << "Ending full quaternion optimization test, "
            << (passed ? 1 : 0) << " tests passed" << std::endl;
  return passed ? 0 : 1;
}
