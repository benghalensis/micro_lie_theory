#pragma once

#include <array>
#include <cmath>

using std::sin;
using std::cos;
using std::sqrt;
using std::atan2;

template<typename Scalar>
class Quaternion;

template<typename Scalar>
class QuaternionCartesianSpace {
 public:
  QuaternionCartesianSpace() {
  }

  QuaternionCartesianSpace(const Scalar x, const Scalar y, const Scalar z) : data{x, y, z} {}

  Scalar x() const {
    return data[0];
  }
  Scalar y() const {
    return data[1];
  }
  Scalar z() const {
    return data[2];
  }

  Quaternion<Scalar> Exp() const {
    const Scalar theta = sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
    const Scalar half_theta = Scalar(0.5) * theta;
    if (theta < 1e-8) {
 return Quaternion(Scalar(0.5) * data[0], Scalar(0.5) * data[1], Scalar(0.5) * data[2], Scalar(1));
    }
    const Scalar scale = sin(half_theta) / theta;
    return Quaternion(data[0]*scale, data[1]*scale, data[2]*scale, cos(half_theta));
  }

 private:
  std::array<Scalar, 3> data;
};

template<typename Scalar>
Scalar SquaredNorm(const QuaternionCartesianSpace<Scalar>& qcs) {
  return qcs.x() * qcs.x() + qcs.y() * qcs.y() + qcs.z() * qcs.z();
}

template<typename Scalar>
class Quaternion {
 public:
  Quaternion() {
  }

  Quaternion(const Scalar x, const Scalar y, const Scalar z, const Scalar w) : data{x, y, z, w} {}

  QuaternionCartesianSpace<Scalar> Log() const {
    const Scalar x = data[0];
    const Scalar y = data[1];
    const Scalar z = data[2];
    const Scalar w = data[3];

    const Scalar v_norm = sqrt(x * x + y * y + z * z);

    if (v_norm < Scalar(1e-8)) {
      return QuaternionCartesianSpace<Scalar>(Scalar(2) * x, Scalar(2) * y, Scalar(2) * z);
    }

    const Scalar theta = Scalar(2) * atan2(v_norm, w);

    const Scalar scale = theta / v_norm;

    return QuaternionCartesianSpace<Scalar>(scale * x, scale * y, scale * z);
  }

  Scalar x() const {
    return data[0];
  }
  Scalar y() const {
    return data[1];
  }
  Scalar z() const {
    return data[2];
  }
  Scalar w() const {
    return data[3];
  }

  template<typename OtherScalar>
  auto operator*(const Quaternion<OtherScalar>& other) const {
    const Scalar ax = x();
    const Scalar ay = y();
    const Scalar az = z();
    const Scalar aw = w();

    const OtherScalar bx = other.x();
    const OtherScalar by = other.y();
    const OtherScalar bz = other.z();
    const OtherScalar bw = other.w();

    using ResultScalar = decltype(ax * bx);
    return Quaternion<ResultScalar>(
        aw * bx + ax * bw + ay * bz - az * by,
        aw * by - ax * bz + ay * bw + az * bx,
        aw * bz + ax * by - ay * bx + az * bw,
        aw * bw - ax * bx - ay * by - az * bz);
  }

  Quaternion inverse() const {
    const Scalar ax = x();
    const Scalar ay = y();
    const Scalar az = z();
    const Scalar aw = w();

    return Quaternion(-ax, -ay, -az, aw);
  }

 private:
  std::array<Scalar, 4> data;
};

