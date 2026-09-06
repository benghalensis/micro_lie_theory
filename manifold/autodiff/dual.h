#pragma once

#include <array>
#include <cmath>

template <int N>
class Dual {
 public:
  Dual(const double value, const std::array<double, N> derivative) : value_(value), derivative_(derivative) {}

  Dual(const double value) : derivative_(std::array<double, N>()) {
    value_ = value;
  }

  Dual operator+(const Dual& other) const {
    const auto new_value = other.value() + value_;
    std::array<double, N> new_derivative;
    for (int i = 0; i < N; ++i) {
      new_derivative[i] = other.derivative()[i] + derivative_[i];
    }
    return Dual(new_value, new_derivative);
  }

  Dual operator-(const Dual& other) const {
    const auto new_value = value_ - other.value();
    std::array<double, N> new_derivative;
    for (int i = 0; i < N; ++i) {
      new_derivative[i] = derivative_[i] - other.derivative()[i];
    }
    return Dual(new_value, new_derivative);
  }

  Dual operator-() const {
    std::array<double, N> new_derivative;
    for (int i = 0; i < N; ++i) {
      new_derivative[i] = -derivative_[i];
    }
    return Dual(-value_, new_derivative);
  }

  Dual operator*(const Dual& other) const {
    const auto new_value = other.value() * value_;
    std::array<double, N> new_derivative;
    for (int i = 0; i < N; ++i) {
      new_derivative[i] = other.value() * derivative_[i] + value_ * other.derivative()[i];
    }
    return Dual(new_value, new_derivative);
  }

  Dual operator/(const Dual& other) const {
    const auto new_value = value_ / other.value();
    std::array<double, N> new_derivative;
    for (int i = 0; i < N; ++i) {
      new_derivative[i] = (other.value() * derivative_[i] - value_ * other.derivative()[i]) / (other.value() * other.value());
    }
    return Dual(new_value, new_derivative);
  }

  bool operator<(double other) const {
    return value_ < other;
  }

  bool operator<(const Dual& other) const {
    return value_ < other.value();
  }

  double value() const {
    return value_;
  }

  const std::array<double, N>& derivative() const {
    return derivative_;
  }

 private: 
  double value_ = 0.0;
  std::array<double, N> derivative_ = {};
};

template <int N, typename T>
inline Dual<N> operator+(const Dual<N>& x, const T& y) {
  const double value = x.value() + y;
  std::array<double, N> derivative{};
  for (int i = 0; i < N; ++i) {
    derivative[i] = x.derivative()[i];
  }
  return Dual<N>(value, derivative);
}

template <int N, typename T>
inline Dual<N> operator*(const Dual<N>& x, const T& y) {
  const double value = x.value() * y;
  std::array<double, N> derivative{};
  for (int i = 0; i < N; ++i) {
    derivative[i] = y * x.derivative()[i];
  }
  return Dual<N>(value, derivative);
}

template <int N>
inline Dual<N> sin(const Dual<N>& x) {
  const double value = std::sin(x.value());
  std::array<double, N> derivative{};

  for (int i = 0; i < N; ++i) {
    derivative[i] = x.derivative()[i] * std::cos(x.value());
  }

  return Dual<N>(value, derivative);
}

template <int N>
inline Dual<N> cos(const Dual<N>& x) {
  const double value = std::cos(x.value());
  std::array<double, N> derivative{};

  for (int i = 0; i < N; ++i) {
    derivative[i] = -x.derivative()[i] * std::sin(x.value());
  }

  return Dual<N>(value, derivative);
}

template <int N>
inline Dual<N> sqrt(const Dual<N>& x) {
  const auto value = std::sqrt(x.value());
  std::array<double, N> derivative{};
  for (int i = 0; i < N; ++i) {
    derivative[i] = x.derivative()[i] / (2.0 * value);
  }
  return Dual<N>(value, derivative);
}

template <int N>
inline Dual<N> atan2(const Dual<N>& y, const Dual<N>& x) {
  const double value = std::atan2(y.value(), x.value());
  std::array<double, N> derivative{};
  for (int i = 0; i < N; ++i) {
    derivative[i] = (x.value() * y.derivative()[i] - y.value() * x.derivative()[i]) / 
      (x.value() * x.value() + y.value() * y.value());
  } 
  return Dual<N>(value, derivative);
}
