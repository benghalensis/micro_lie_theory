# Right Jacobians - SO3

This note derives useful right Jacobians for the rotation group

$$
SO(3)=\{R\in\mathbb{R}^{3\times 3}:R^\top R=I,\det(R)=1\}.
$$

For $SO(3)$, tangent coordinates live in $\mathbb{R}^3$. The hat operator turns a vector into a skew-symmetric matrix:

$$
\phi^\wedge =
\begin{bmatrix}
0 & -\phi_z & \phi_y \\
\phi_z & 0 & -\phi_x \\
-\phi_y & \phi_x & 0
\end{bmatrix}.
$$

The coordinate exponential and logarithm are

$$
\mathrm{Exp}(\phi)=\exp(\phi^\wedge),
\qquad
\mathrm{Log}(R)=\left(\log(R)\right)^\vee.
$$

The group operation is matrix multiplication. The right plus and right minus are

$$
R \oplus {}^R\tau
\triangleq
R\,\mathrm{Exp}({}^R\tau),
$$

$$
R_2 \ominus R_1
\triangleq
\mathrm{Log}(R_1^{-1}R_2)
=
\mathrm{Log}(R_1^\top R_2).
$$

So, for a group-input, group-output function

$$
f:SO(3)\rightarrow SO(3),
$$

the right Jacobian is

$$
\mathbf{J}_{f,r}(R)
=
\lim_{\tau \to 0}
\frac{
\mathrm{Log}
\left(
f(R)^{-1}f(R\,\mathrm{Exp}(\tau))
\right)
}{
\tau
}.
$$

The input is the manifold element $R$, not a rotation-vector coordinate. The coordinate $\tau$ is only the small tangent-space perturbation used to move from $R$ to $R\,\mathrm{Exp}(\tau)$.

All uses of $\mathrm{Log}(\mathrm{Exp}(\tau))=\tau$ are local around $\tau=0$, which is the region used by the Jacobian limit.

Useful identities for $SO(3)$:

$$
\phi^\wedge x = \phi \times x = -x^\wedge \phi,
$$

$$
Q\phi^\wedge Q^\top=(Q\phi)^\wedge,
$$

$$
Q\,\mathrm{Exp}(\phi)\,Q^\top=\mathrm{Exp}(Q\phi).
$$

For $SO(3)$, the adjoint matrix is just the rotation matrix:

$$
\mathrm{Ad}_R = R.
$$

## Right Jacobian of inverse

Let

$$
f(R)=R^{-1}=R^\top.
$$

Start from the right-Jacobian definition:

$$
\mathbf{J}_{f,r}(R)
=
\lim_{\tau \to 0}
\frac{
\mathrm{Log}
\left(
f(R)^{-1}f(R\,\mathrm{Exp}(\tau))
\right)
}{
\tau
}.
$$

Now substitute $f(R)=R^{-1}$:

$$
\mathbf{J}_{f,r}(R)
=
\lim_{\tau \to 0}
\frac{
\mathrm{Log}
\left(
(R^{-1})^{-1}
(R\,\mathrm{Exp}(\tau))^{-1}
\right)
}{
\tau
}.
$$

Simplify the first term:

$$
(R^{-1})^{-1}=R.
$$

Simplify the second term using $(AB)^{-1}=B^{-1}A^{-1}$:

$$
(R\,\mathrm{Exp}(\tau))^{-1}
=
\mathrm{Exp}(\tau)^{-1}R^{-1}
=
\mathrm{Exp}(-\tau)R^\top.
$$

Substitute both simplifications back into the numerator:

$$
\mathrm{Log}
\left(
(R^{-1})^{-1}
(R\,\mathrm{Exp}(\tau))^{-1}
\right)
=
\mathrm{Log}
\left(
R\,\mathrm{Exp}(-\tau)\,R^\top
\right).
$$

Use the conjugation identity:

$$
R\,\mathrm{Exp}(-\tau)\,R^\top
=
\mathrm{Exp}(-R\tau).
$$

Therefore

$$
\mathrm{Log}
\left(
R\,\mathrm{Exp}(-\tau)\,R^\top
\right)
=
-R\tau.
$$

So

$$
\boxed{
\mathbf{J}^{R^{-1}}_{R,r} = -R
}
$$

or, equivalently,

$$
\boxed{
\mathbf{J}^{R^{-1}}_{R,r} = -\mathrm{Ad}_R
}.
$$

## Right Jacobians of composition

Let

$$
h(R_1,R_2)=R_1R_2.
$$

The output is

$$
R = h(R_1,R_2)=R_1R_2.
$$

### With respect to $R_1$

Perturb only the first argument:

$$
R_1' = R_1\mathrm{Exp}(\tau_1).
$$

Then

$$
h(R_1',R_2)
=
R_1\mathrm{Exp}(\tau_1)R_2.
$$

The output right perturbation is

$$
h(R_1',R_2)\ominus h(R_1,R_2)
=
\mathrm{Log}
\left(
R^{-1}R_1\mathrm{Exp}(\tau_1)R_2
\right).
$$

Substitute $R=R_1R_2$:

$$
\mathrm{Log}
\left(
(R_1R_2)^{-1}R_1\mathrm{Exp}(\tau_1)R_2
\right)
=
\mathrm{Log}
\left(
R_2^\top \mathrm{Exp}(\tau_1)R_2
\right).
$$

Use the conjugation identity:

$$
R_2^\top \mathrm{Exp}(\tau_1)R_2
=
\mathrm{Exp}(R_2^\top\tau_1).
$$

So

$$
h(R_1',R_2)\ominus h(R_1,R_2)
=
R_2^\top\tau_1.
$$

Therefore

$$
\boxed{
\mathbf{J}^{R}_{R_1,r}=R_2^\top
}.
$$

This is the main difference from the unit-complex case: $SO(3)$ is non-commutative, so the perturbation on $R_1$ must be transported through $R_2$ before it becomes the output right perturbation.

### With respect to $R_2$

Perturb only the second argument:

$$
R_2' = R_2\mathrm{Exp}(\tau_2).
$$

Then

$$
h(R_1,R_2')
=
R_1R_2\mathrm{Exp}(\tau_2)
=
R\,\mathrm{Exp}(\tau_2).
$$

So the output right perturbation is $\tau_2$:

$$
h(R_1,R_2')\ominus h(R_1,R_2)
=
\mathrm{Log}
\left(
R^{-1}R\mathrm{Exp}(\tau_2)
\right)
=
\tau_2.
$$

Therefore

$$
\boxed{
\mathbf{J}^{R}_{R_2,r}=I_3
}.
$$

## Right Jacobian of group action

Let $SO(3)$ act on a 3D point $x\in\mathbb{R}^3$:

$$
y = R \cdot x \triangleq Rx.
$$

The output $y$ is a vector-space object, not a group element, so output changes use ordinary subtraction.

### With respect to $R$

Perturb the group element on the right:

$$
R' = R\mathrm{Exp}(\tau).
$$

Then

$$
y'
=
R'x
=
R\mathrm{Exp}(\tau)x.
$$

For small $\tau$,

$$
\mathrm{Exp}(\tau)
\approx
I+\tau^\wedge.
$$

So

$$
y'
\approx
R(I+\tau^\wedge)x
=
Rx+R\tau^\wedge x.
$$

Using $\tau^\wedge x=-x^\wedge\tau$,

$$
y'
\approx
y-Rx^\wedge\tau.
$$

Thus

$$
y'-y
\approx
-Rx^\wedge\tau.
$$

Therefore

$$
\boxed{
\mathbf{J}^{y}_{R,r}=-Rx^\wedge
}.
$$

Equivalently, since $y=Rx$,

$$
-Rx^\wedge = -y^\wedge R.
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
Rx'
=
R(x+\delta x)
=
Rx+R\delta x.
$$

Therefore

$$
y'-y=R\delta x,
$$

so

$$
\boxed{
\mathbf{J}^{y}_{x}=R
}.
$$

## Summary

| Map | Right Jacobian |
| --- | --- |
| $f(R)=R^{-1}$ | $\mathbf{J}^{R^{-1}}_{R,r}=-R$ |
| $h(R_1,R_2)=R_1R_2$ with respect to $R_1$ | $\mathbf{J}^{R}_{R_1,r}=R_2^\top$ |
| $h(R_1,R_2)=R_1R_2$ with respect to $R_2$ | $\mathbf{J}^{R}_{R_2,r}=I_3$ |
| $y=R\cdot x=Rx$ with respect to $R$ | $\mathbf{J}^{y}_{R,r}=-Rx^\wedge$ |
| $y=R\cdot x=Rx$ with respect to $x$ | $\mathbf{J}^{y}_{x}=R$ |
