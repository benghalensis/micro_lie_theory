# Tangent Space - Quaternions

## Unit quaternions using the group constraint

We can derive the Lie algebra of unit quaternions in the same way as unit complex numbers.

**The unit quaternion group is**

$$
\mathbb{H}_1 = \{q \in \mathbb{H} : q^*q = 1\}
$$

where $(q^*)$ is the quaternion conjugate.

**The group constraint is**

$$
q^*q = 1
$$

This is the quaternion version of the unit complex constraint $(z^*z = 1)$. It simply means that the quaternion must always stay on the unit 3-sphere.

If $(q(t))$ is a unit quaternion moving over time, then differentiating the constraint gives a condition on its velocity $(dot{q})$. This tells us what valid tangent vectors look like.

**The important result is**

$$
q^{-1}\dot{q} = q^*\dot{q}
$$

and this quantity must be a pure imaginary quaternion:

$$
q^*\dot{q} =
\begin{bmatrix}
0 \\
\omega
\end{bmatrix}
$$

where $(omega in mathbb{R}^3)$.

So the Lie algebra of unit quaternions is the space of pure imaginary quaternions:

$$
\mathfrak{h}_1 =
\left\{
\begin{bmatrix}
0 \\
\phi
\end{bmatrix}
:
\phi \in \mathbb{R}^3
\right\}
$$

**Intuitively:**

$$
\text{unit quaternion group} = \text{valid 3D rotations}
$$

$$
\text{quaternion Lie algebra} = \text{small 3D rotation vectors}
$$

The exponential map takes a vector in the Lie algebra and maps it to a unit quaternion:

$$
\operatorname{Exp}(\phi) =
\begin{bmatrix}
\cos \|\phi\| \\
\dfrac{\phi}{\|\phi\|}\sin \|\phi\|
\end{bmatrix}
$$

The logarithm map takes a unit quaternion back to the Lie algebra:

$$
\operatorname{Log}(q) = \dfrac{\mathbf{v}}{\|\mathbf{v}\|}\operatorname{atan2}(\|\mathbf{v}\|, w)
$$

where

$$
q =
\begin{bmatrix}
w \\
\mathbf{v}
\end{bmatrix}
$$

In robotics, quaternions are usually written with the half-angle convention:

$$
q =
\begin{bmatrix}
\cos(\theta/2) \\
 u\sin(\theta/2)
\end{bmatrix}
$$

So depending on the convention, the Lie algebra vector may represent either the full rotation vector $(\theta u)$ or the half-angle vector $(theta u / 2)$.

The key idea is that the group constraint $(q^*q = 1)$ forces valid quaternion velocities to lie in a tangent space, and when we move that tangent vector back to the identity, we get a pure imaginary quaternion. That pure imaginary quaternion is the Lie algebra.