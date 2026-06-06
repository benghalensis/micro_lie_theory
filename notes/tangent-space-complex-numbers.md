# Tangent Space - Complex Numbers

## Unit complex numbers using the group constraint

We can derive the Lie algebra of unit complex numbers using the group constraint.

The unit complex group is

$$
S^1 = \{z \in \mathbb{C} : z^* z = 1\}
$$

where $z^*$ is the complex conjugate.

The group constraint is

$$
z^* z = 1
$$

This means the complex number must always stay on the unit circle.

If (z(t)) is a unit complex number moving over time, then differentiating the constraint gives a condition on its velocity (dot{z}). This tells us what valid tangent vectors look like.

The important result is

$$
z^{-1}\dot{z} = z^*\dot{z}
$$

and this quantity must be a pure imaginary complex number:

$$
z^*\dot{z} = i\omega: \omega \in \mathbb{R}
$$

So the Lie algebra of unit complex numbers is the space of pure imaginary numbers:

$$
\mathfrak{s}^1
\{i\omega : \omega \in \mathbb{R}\}
$$

Intuitively:

$$
\text{unit complex group} = \text{valid 2D rotations}
$$

$$
\text{complex Lie algebra} = \text{small 1D rotation angles}
$$

The exponential map takes a scalar angle in the Lie algebra and maps it to a unit complex number:

$$
\operatorname{Exp}(\omega)=
e^{i\omega}=
\cos\omega + i\sin\omega
$$

The logarithm map takes a unit complex number back to the Lie algebra:

$$
\operatorname{Log}(z)
\operatorname{atan2}(\operatorname{Im}(z), \operatorname{Re}(z))
$$

where

$$
z = x + iy
$$

so equivalently,

$$
\operatorname{Log}(x+iy)
\operatorname{atan2}(y,x)
$$

The key idea is that the group constraint (z^*z = 1) forces valid complex-number velocities to lie in a tangent space, and when we move that tangent vector back to the identity, we get a pure imaginary number. That pure imaginary number is the Lie algebra.