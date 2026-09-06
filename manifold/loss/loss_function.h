

template <typename Scalar, typename Quaternion1, typename Quaternion2>
class LossFunc() {
  Loss(Quaternion1 q1, Quaternion2 q2) {
    BoxPlus(q1, q2);
  };

  Jacobian_Wrt_Q1() {
  }
};