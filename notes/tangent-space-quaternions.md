# Tangent Space - Quaternions

## Unit quaternions using the group constraint

Unit quaternions form a Lie group:

$$
\mathbb{H}_1 = \{q \in \mathbb{H} : q^*q = 1\}
$$

where $\mathbb{H}$ is the set of all quaternions, $\mathbb{H}_1$ is the subset of unit quaternions, and $q^*$ is the quaternion conjugate. If

$$
q =
\begin{bmatrix}
w \\
\mathbf{v}
\end{bmatrix}
$$

then

$$
q^* =
\begin{bmatrix}
w \\
-\mathbf{v}
\end{bmatrix}
$$

The constraint

$$
q^*q = 1
$$

means the quaternion must stay on the unit 3-sphere $S^3$.

Now suppose $q(t)$ is a unit quaternion moving over time. Its velocity is $\dot q(t)$. Since $q(t)$ must stay on $S^3$, $\dot q(t)$ cannot point in an arbitrary direction in $\mathbb{H}$. It must be tangent to the unit sphere at $q$.

To find the tangent condition, differentiate the constraint:

$$
\frac{d}{dt}(q^*q) = 0
$$

Using the product rule:

$$
\dot q^*q + q^*\dot q = 0
$$

Now define the pulled-back velocity:

$$
a = q^*\dot q
$$

Since quaternion conjugation reverses multiplication order,

$$
a^* = (q^*\dot q)^* = \dot q^*q
$$

so the differentiated constraint becomes

$$
a^* + a = 0
$$

This says that $a$ has zero real part. Therefore $a$ must be a pure imaginary quaternion:

$$
q^*\dot q =
\begin{bmatrix}
0 \\
\omega
\end{bmatrix},
\quad \omega \in \mathbb{R}^3
$$

Since $q^{-1} = q^*$ for unit quaternions, this is also

$$
q^{-1}\dot q =
\begin{bmatrix}
0 \\
\omega
\end{bmatrix}
$$

Multiplying both sides by $q$ gives the velocity at the point $q$:

$$
\dot q =
q
\begin{bmatrix}
0 \\
\omega
\end{bmatrix}
$$

So $q^{-1}\dot q$ is the velocity pulled back from the tangent space at $q$ to the tangent space at the identity, while $\dot q$ is the tangent vector on $S^3$ at $q$.

## Tangent space and Lie algebra

At a point $q \in \mathbb{H}_1$, the tangent space is

$$
T_q\mathbb{H}_1 =
\left\{
q
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
:
\phi \in \mathbb{R}^3
\right\}
$$

The Lie algebra is the special tangent space at the identity quaternion:

$$
\mathfrak{h}_1 = T_1\mathbb{H}_1 =
\left\{
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
:
\phi \in \mathbb{R}^3
\right\}
$$

So the intuition is:

$$
\text{unit quaternion group} = \text{points on } S^3
$$

$$
\text{quaternion Lie algebra} = \text{pure imaginary quaternions}
$$

When unit quaternions are used to represent 3D rotations, the pure imaginary part is related to a 3D rotation vector. The vector $\phi$ does not need to be a unit vector; its norm gives the magnitude, and its normalized direction is the unit axis.

## exp and log on unit quaternions

Lowercase $\exp$ acts on a tangent-space element, which is a pure imaginary quaternion:

$$
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
$$

If

$$
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
\in \mathfrak{h}_1,\quad
\theta = \|\phi\|,\quad
u = \frac{\phi}{\|\phi\|}
$$

then

$$
\exp\left(
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
\right) =
\begin{bmatrix}
\cos \theta \\
u\sin \theta
\end{bmatrix}
$$

Equivalently:

$$
\exp\left(
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
\right) =
\begin{bmatrix}
\cos \|\phi\| \\
\dfrac{\phi}{\|\phi\|}\sin \|\phi\|
\end{bmatrix}
$$

The lowercase logarithm returns a tangent-space element. If

$$
q =
\begin{bmatrix}
w \\
\mathbf{v}
\end{bmatrix}
$$

then

$$
\log(q) =
\begin{bmatrix}
0 \\
\dfrac{\mathbf{v}}{\|\mathbf{v}\|}
\mathrm{atan2}(\|\mathbf{v}\|, w)
\end{bmatrix}
$$

## Exp and Log on unit quaternions

Uppercase $\mathrm{Exp}$ acts on the vector-space coordinate $\phi \in \mathbb{R}^3$ and returns the corresponding manifold element:

$$
\mathrm{Exp}(\phi) \triangleq
\exp
\left(
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
\right)
$$

Therefore:

$$
\mathrm{Exp}(\phi) =
\begin{bmatrix}
\cos \|\phi\| \\
\dfrac{\phi}{\|\phi\|}\sin \|\phi\|
\end{bmatrix}
$$

The uppercase logarithm returns the vector-space coordinate:

$$
\mathrm{Log}(q) =
\dfrac{\mathbf{v}}{\|\mathbf{v}\|}
\mathrm{atan2}(\|\mathbf{v}\|, w)
$$

## Rotation convention

There is one important convention issue.

A unit quaternion representing a 3D rotation by angle $\theta$ around unit axis $u$ is usually written as

$$
q =
\begin{bmatrix}
\cos(\theta/2) \\
u\sin(\theta/2)
\end{bmatrix}
$$

This means the uppercase quaternion logarithm gives the half-angle vector:

$$
\mathrm{Log}(q) = \frac{\theta}{2}u
$$

If you want the usual 3D rotation vector, you multiply by $2$:

$$
\theta u = 2\mathrm{Log}(q)
$$

So for quaternions, be clear about which object you want:

$$
\text{quaternion Lie algebra coordinate} = \frac{\theta}{2}u
$$

$$
\text{SO(3) rotation vector} = \theta u
$$

The key idea is that the group constraint $q^*q = 1$ forces valid velocities to lie in a tangent space. When we pull a tangent vector back to the identity using $q^{-1}\dot q$, we get a pure imaginary quaternion, which is an element of the Lie algebra.
