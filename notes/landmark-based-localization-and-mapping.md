# Landmark-Based Localization and Mapping

Notes from Section V of [A micro Lie theory for state estimation in robotics](https://arxiv.org/pdf/1812.01537).

## Problem definition

We start with the localization problem. The map is already known, meaning the landmark positions $b_k$ are given. The robot only needs to estimate its own pose.

The robot pose lives in $SE(2)$:

$$
X =
\begin{bmatrix}
R & t \\
0 & 1
\end{bmatrix}
\in SE(2).
$$

Here:

- $R \in SO(2)$ is the robot orientation.
- $t \in \mathbb{R}^2$ is the robot position in the world frame.

Each landmark is a point in the world frame:

$$
b_k =
\begin{bmatrix}
x_k \\
y_k
\end{bmatrix}
\in \mathbb{R}^2.
$$

The control input is a noisy twist in $\mathfrak{se}(2)$:

$$
u =
\begin{bmatrix}
u_v \\
u_s \\
u_\omega
\end{bmatrix}
=
\begin{bmatrix}
v\,\delta t \\
0 \\
\omega\,\delta t
\end{bmatrix}
+ w,
\qquad
w \sim \mathcal{N}(0, W).
$$

The middle component $u_s$ is the sideways motion. It is nominally zero for a wheeled robot, but the noise term can model side slip.

## Motion and measurement equations

The motion model moves the previous pose $X_i$ forward using the control $u_j$:

$$
X_j = X_i \oplus u_j.
$$

Because $\oplus$ is a right perturbation, this means:

$$
X_j = X_i\,\mathrm{Exp}(u_j).
$$

The landmark measurement is the known world landmark $b_k$ expressed in the robot frame:

$$
y_k
=
X^{-1} \cdot b_k + n
=
R^\top(b_k - t) + n,
\qquad
n \sim \mathcal{N}(0, N).
$$

This equation is worth reading slowly:

1. $b_k - t$ points from the robot to the landmark in the world frame.
2. $R^\top(b_k - t)$ rotates that vector into the robot frame.
3. $n$ adds measurement noise.

## ESKF algorithm

The ESKF state is the estimated pose and its local error covariance:

$$
(\hat X, P),
\qquad
\hat X \in SE(2),
\quad
P \in \mathbb{R}^{3 \times 3}.
$$

The pose estimate lives on the manifold. The covariance lives in the tangent space of the pose error:

$$
\delta x = X \ominus \hat X \in \mathbb{R}^3,
\qquad
P = \mathbb{E}\left[(X \ominus \hat X)(X \ominus \hat X)^\top\right].
$$

### Prediction

$$
\hat X_j = \hat X_i \oplus u_j.
$$

$$
\hat X_j = \hat X_i\,\mathrm{Exp}(u_j).
$$

$$
P_j = F P_i F^\top + G W_j G^\top.
$$

### Correction

$$
z = y_k - \hat X_j^{-1}\cdot b_k.
$$

$$
Z = H P_j H^\top + N.
$$

$$
K = P_j H^\top Z^{-1}.
$$

$$
\delta x = Kz.
$$

The correction $\delta x$ is a tangent-space vector, so the pose update uses $\oplus$:

$$
\hat X \leftarrow \hat X \oplus \delta x.
$$

$$
P \leftarrow P - K Z K^\top.
$$

## Our task: find the Jacobians

The ESKF equations are standard once the Jacobians are known. The important part for us is deriving $F$, $G$, and $H$ from the Lie group operations.

For prediction, define

$$
f(X_i, u_j) = X_i\,\mathrm{Exp}(u_j).
$$

For correction, define

$$
h(X_j) = X_j^{-1}\cdot b_k.
$$

The Jacobians we need are:

| Jacobian | Result |
| --- | --- |
| $F = \frac{\partial f(X_i, u_j)}{\partial X_i}$ | $\mathrm{Ad}_{\mathrm{Exp}(u_j)}^{-1}$ |
| $G = \frac{\partial f(X_i, u_j)}{\partial u_j}$ | $J_r(u_j)$ |
| $H = \frac{\partial h(X_j)}{\partial X_j}$ | $\begin{bmatrix}-1 & 0 & q_y \\ 0 & -1 & -q_x\end{bmatrix}$ |

Be careful about the domains:

- $F$ is a pose-to-pose Jacobian, so the input perturbation is in the tangent space of $X_i$ and the output perturbation is in the tangent space of $X_j$.
- $G$ starts from a control perturbation in $\mathbb{R}^3 \cong \mathfrak{se}(2)$ and maps it into the tangent space of $X_j$.
- $H$ starts from a pose perturbation in $\mathbb{R}^3$ and maps it into a Cartesian measurement perturbation in $\mathbb{R}^2$.

where

$$
q = \hat X_j^{-1}\cdot b_k
=
\hat R_j^\top(b_k - \hat t_j)
=
\begin{bmatrix}
q_x \\
q_y
\end{bmatrix}.
$$

We should derive the Jacobians in this order:

1. Derive $F$ from $X_j = X_i\mathrm{Exp}(u_j)$ using a right perturbation on $X_i$.
2. Derive $G$ from $X_j = X_i\mathrm{Exp}(u_j)$ using a small perturbation on $u_j$.
3. Derive $H$ from $h(X) = X^{-1}\cdot b_k$ using the inverse and action Jacobians.
