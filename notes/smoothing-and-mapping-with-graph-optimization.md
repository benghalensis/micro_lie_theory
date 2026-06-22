# Smoothing and Mapping with Graph Optimization

Notes from Section V-B of [A micro Lie theory for state estimation in robotics](https://arxiv.org/pdf/1812.01537).

For simultaneous localization and mapping, the unknowns include both the robot trajectory and the landmark positions. The paper's small example uses three poses and three landmarks:

$$
\mathcal{X}
=
\langle X_1, X_2, X_3, b_4, b_5, b_6 \rangle,
\qquad
X_i \in SE(2),
\quad
b_k \in \mathbb{R}^2.
$$

Motion measurements connect two poses:

$$
u_{ij}
=
X_j \ominus X_i + w_{ij}
=
\mathrm{Log}(X_i^{-1}X_j) + w_{ij}.
$$

Landmark measurements connect one pose to one landmark:

$$
y_{ik} = X_i^{-1} \cdot b_k + n_{ik}.
$$

Each prior, motion measurement, and landmark measurement becomes a residual in the factor graph. Using information matrices $\Omega$, the residuals have this shape:

$$
r_1(\mathcal{X})
=
\Omega_1^{\top/2}(X_1 \ominus \hat X_1),
$$

$$
r_{ij}(\mathcal{X})
=
\Omega_{ij}^{\top/2}
\left(
u_{ij} - (\hat X_j \ominus \hat X_i)
\right),
$$

$$
r_{ik}(\mathcal{X})
=
\Omega_{ik}^{\top/2}
\left(
y_{ik} - \hat X_i^{-1}\cdot \hat b_k
\right).
$$

The optimizer finds a tangent-space increment $\delta x$ for the whole composite state:

$$
\delta x^*
=
\arg\min_{\delta x}
\sum_{p \in \mathcal{P}}
r_p(\mathcal{X} \oplus \delta x)^\top
r_p(\mathcal{X} \oplus \delta x).
$$

After linearization,

$$
r_p(\mathcal{X} \oplus \delta x)
\approx
r_p(\mathcal{X}) + J_p\delta x,
$$

the stacked least-squares problem is

$$
\delta x^*
=
\arg\min_{\delta x}
\|r + J\delta x\|^2.
$$

The normal-equation update is:

$$
\delta x^*
=
-(J^\top J)^{-1}J^\top r,
\qquad
\mathcal{X} \leftarrow \mathcal{X} \oplus \delta x^*.
$$

In larger systems, the same structure is solved with sparse numerical methods such as QR or Cholesky factorization. The important Lie theory point is that the composite state can mix $SE(2)$ poses and Euclidean landmarks, while the linear step still lives in one stacked tangent vector.
