# Right Jacobians - Unit Complex Numbers

This note derives useful right Jacobians for the unit complex Lie group

$$
S^1 = \{z \in \mathbb{C} : z^*z = 1\}.
$$

For unit complex numbers,

$$
z = e^{i\theta} = \mathrm{Exp}(\theta),
\qquad
\mathrm{Exp}(\tau)=e^{i\tau},
\qquad
\mathrm{Log}(z)=\mathrm{atan2}(\mathrm{Im}(z),\mathrm{Re}(z)).
$$

The group operation is complex multiplication. The right plus and right minus are

$$
z \oplus {}^z\tau
\triangleq
z\,\mathrm{Exp}({}^z\tau),
$$

$$
z_2 \ominus z_1
\triangleq
\mathrm{Log}(z_1^{-1}z_2).
$$

So, for a group-input, group-output function

$$
f:S^1\rightarrow S^1,
$$

the right Jacobian is

$$
\mathbf{J}_{f,r}(z)
=
\lim_{\tau \to 0}
\frac{
\mathrm{Log}
\left(
f(z)^{-1}f(z\,\mathrm{Exp}(\tau))
\right)
}{
\tau
}.
$$

The input is the manifold element $z$, not the coordinate $\theta$. The coordinate $\tau$ is only the small tangent-space perturbation used to move from $z$ to $z\,\mathrm{Exp}(\tau)$.

Because $S^1$ is one-dimensional, the group-to-group Jacobians below are scalars.

All uses of $\mathrm{Log}(\mathrm{Exp}(\tau))=\tau$ are local around $\tau=0$, which is the region used by the Jacobian limit. Globally, the angle wraps at the usual $\pm\pi$ branch cut.

## Right Jacobian of inverse

Let

$$
f(z)=z^{-1}.
$$

Start from the right-Jacobian definition:

$$
\mathbf{J}_{f,r}(z)
=
\lim_{\tau \to 0}
\frac{
\mathrm{Log}
\left(
f(z)^{-1}f(z\,\mathrm{Exp}(\tau))
\right)
}{
\tau
}.
$$

Now substitute $f(z)=z^{-1}$:

$$
\mathbf{J}_{f,r}(z)
=
\lim_{\tau \to 0}
\frac{
\mathrm{Log}
\left(
(z^{-1})^{-1}
(z\,\mathrm{Exp}(\tau))^{-1}
\right)
}{
\tau
}.
$$

Simplify the first term:

$$
(z^{-1})^{-1}=z.
$$

Simplify the second term using $(ab)^{-1}=b^{-1}a^{-1}$:

$$
(z\,\mathrm{Exp}(\tau))^{-1}
=
\mathrm{Exp}(\tau)^{-1}z^{-1}
=
\mathrm{Exp}(-\tau)z^{-1}.
$$

Substitute both simplifications back into the numerator:

$$
\mathrm{Log}
\left(
(z^{-1})^{-1}
(z\,\mathrm{Exp}(\tau))^{-1}
\right)
=
\mathrm{Log}
\left(
z\,\mathrm{Exp}(-\tau)z^{-1}
\right).
$$

For $S^1$, multiplication is commutative, so the $z$ and $z^{-1}$ cancel:

$$
\mathrm{Log}
\left(
z\,\mathrm{Exp}(-\tau)z^{-1}
\right)
=
\mathrm{Log}
\left(
zz^{-1}\mathrm{Exp}(-\tau)
\right)
=
\mathrm{Log}(\mathrm{Exp}(-\tau))
=
-\tau.
$$

Therefore the limit is

$$
\mathbf{J}_{f,r}(z)
=
\lim_{\tau \to 0}
\frac{-\tau}{\tau}
=
-1,
$$

so

$$
\boxed{
\mathbf{J}^{z^{-1}}_{z,r} = -1
}.
$$

## Right Jacobians of composition

Let

$$
h(z_1,z_2)=z_1z_2.
$$

The output is

$$
z = h(z_1,z_2)=z_1z_2.
$$

### With respect to $z_1$

Perturb only the first argument:

$$
z_1' = z_1\mathrm{Exp}(\tau_1).
$$

Then

$$
h(z_1',z_2)
=
z_1\mathrm{Exp}(\tau_1)z_2.
$$

Since $S^1$ is commutative,

$$
z_1\mathrm{Exp}(\tau_1)z_2
=
z_1z_2\mathrm{Exp}(\tau_1)
=
z\,\mathrm{Exp}(\tau_1).
$$

So the output right perturbation is $\tau_1$:

$$
h(z_1',z_2) \ominus h(z_1,z_2)
=
\mathrm{Log}(z^{-1}z\mathrm{Exp}(\tau_1))
=
\tau_1.
$$

Therefore

$$
\boxed{
\mathbf{J}^{z}_{z_1,r}=1
}.
$$

### With respect to $z_2$

Perturb only the second argument:

$$
z_2' = z_2\mathrm{Exp}(\tau_2).
$$

Then

$$
h(z_1,z_2')
=
z_1z_2\mathrm{Exp}(\tau_2)
=
z\,\mathrm{Exp}(\tau_2).
$$

So the output right perturbation is $\tau_2$:

$$
h(z_1,z_2') \ominus h(z_1,z_2)
=
\mathrm{Log}(z^{-1}z\mathrm{Exp}(\tau_2))
=
\tau_2.
$$

Therefore

$$
\boxed{
\mathbf{J}^{z}_{z_2,r}=1
}.
$$

Both composition Jacobians are $1$ for $S^1$ because the group is commutative. For non-commutative groups such as $SO(3)$ and $SE(3)$, the corresponding Jacobians are not this simple.

## Right Jacobian of group action

Let $S^1$ act on a 2D point represented as a complex number $x\in\mathbb{C}$:

$$
y = z \cdot x \triangleq zx.
$$

The output $y$ is a vector-space object, not a group element, so output changes use ordinary subtraction.

### With respect to $z$

Perturb the group element on the right:

$$
z' = z\mathrm{Exp}(\tau).
$$

Then

$$
y'
=
z'x
=
z\mathrm{Exp}(\tau)x.
$$

For small $\tau$,

$$
\mathrm{Exp}(\tau)=e^{i\tau}\approx 1+i\tau.
$$

So

$$
y'
\approx
z(1+i\tau)x
=
zx+i(zx)\tau
=
y+iy\tau.
$$

Thus

$$
y'-y
\approx
iy\tau.
$$

As a complex scalar multiplying the one-dimensional perturbation $\tau$,

$$
\boxed{
\mathbf{J}^{y}_{z,r}=iy
}.
$$

If

$$
y=y_x+iy_y,
$$

then

$$
iy=-y_y+iy_x.
$$

In real vector coordinates,

$$
\boxed{
\mathbf{J}^{y}_{z,r}
=
\begin{bmatrix}
-y_y \\
y_x
\end{bmatrix}
}.
$$

### With respect to $x$

Perturb the vector-space input:

$$
x' = x+\delta x.
$$

Then

$$
y'
=
zx'
=
z(x+\delta x)
=
zx+z\delta x.
$$

Therefore

$$
y'-y=z\delta x.
$$

In real vector coordinates, multiplication by $z=e^{i\theta}$ is the rotation matrix

$$
\mathbf{R}(z)
=
\begin{bmatrix}
\cos\theta & -\sin\theta \\
\sin\theta & \cos\theta
\end{bmatrix}.
$$

So

$$
\boxed{
\mathbf{J}^{y}_{x}
=
\mathbf{R}(z)
}.
$$

## Summary

| Map | Right Jacobian |
| --- | --- |
| $f(z)=z^{-1}$ | $\mathbf{J}^{z^{-1}}_{z,r}=-1$ |
| $h(z_1,z_2)=z_1z_2$ with respect to $z_1$ | $\mathbf{J}^{z}_{z_1,r}=1$ |
| $h(z_1,z_2)=z_1z_2$ with respect to $z_2$ | $\mathbf{J}^{z}_{z_2,r}=1$ |
| $y=z\cdot x=zx$ with respect to $z$ | $\mathbf{J}^{y}_{z,r}=\begin{bmatrix}-y_y & y_x\end{bmatrix}^\top$ |
| $y=z\cdot x=zx$ with respect to $x$ | $\mathbf{J}^{y}_{x}=\mathbf{R}(z)$ |
