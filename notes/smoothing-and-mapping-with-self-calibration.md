# Smoothing and Mapping with Self-Calibration

Notes from Section V-C of [A micro Lie theory for state estimation in robotics](https://arxiv.org/pdf/1812.01537).

This example augments the smoothing-and-mapping state with an unknown motion-sensor calibration bias:

$$
c =
\begin{bmatrix}
c_v \\
c_\omega
\end{bmatrix}.
$$

The measured control contains this bias:

$$
\tilde u
=
\begin{bmatrix}
v\,\delta t + c_v \\
0 \\
\omega\,\delta t + c_\omega
\end{bmatrix}
+ w.
$$

Define a bias-corrected control:

$$
u = g(\tilde u, c)
=
\begin{bmatrix}
\tilde u_v - c_v \\
\tilde u_s \\
\tilde u_\omega - c_\omega
\end{bmatrix}.
$$

The composite state becomes:

$$
\mathcal{X}
=
\langle c, X_1, X_2, X_3, b_4, b_5, b_6 \rangle.
$$

The optimization procedure is unchanged. Only the motion residual now depends on the calibration variable:

$$
r_{ij}(\mathcal{X})
=
\Omega_{ij}^{\top/2}
\left(
g(\tilde u_{ij}, c) - (\hat X_j \ominus \hat X_i)
\right).
$$

This adds a new Jacobian block with respect to $c$. Once optimized, the state contains both the trajectory/map estimate and the sensor bias estimate.
