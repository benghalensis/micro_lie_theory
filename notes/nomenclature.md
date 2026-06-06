# Nomenclature

This page collects the notation conventions used in these notes.

## Sets, groups, and elements

Spaces and groups are written with blackboard-bold symbols:

$$
\mathbb{G},\quad \mathbb{M},\quad \mathbb{R}^n,\quad \mathbb{H}_1
$$

Elements of a group or manifold are written with calligraphic symbols when the discussion is generic:

$$
\mathcal{X},\quad \mathcal{Y},\quad \mathcal{E}
$$

For concrete groups, familiar symbols are used:

$$
z \in S^1,\quad q \in \mathbb{H}_1,\quad R \in SO(3),\quad H \in SE(3)
$$

## Tangent spaces and coordinates

The tangent space at a point $\mathcal{X}$ is written

$$
T_\mathcal{X}\mathbb{M}
$$

The Lie algebra is the tangent space at the identity:

$$
\mathfrak{m} \triangleq T_\mathcal{E}\mathbb{M}
$$

A tangent-space element is written

$$
\epsilon \in \mathfrak{m}
$$

A vector-space coordinate is written

$$
\tau \in \mathbb{R}^m
$$

The coordinate-to-tangent-space conversion is kept implicit for now.

## exp, log, Exp, and Log

Lowercase $\exp$ maps a tangent-space element to a manifold element:

$$
\exp : \mathfrak{m} \to \mathbb{M}
$$

Lowercase $\log$ maps a manifold element to a tangent-space element:

$$
\log : \mathbb{M} \to \mathfrak{m}
$$

Uppercase $\operatorname{Exp}$ maps a vector-space coordinate to a manifold element:

$$
\operatorname{Exp} : \mathbb{R}^m \to \mathbb{M}
$$

Uppercase $\operatorname{Log}$ maps a manifold element to a vector-space coordinate:

$$
\operatorname{Log} : \mathbb{M} \to \mathbb{R}^m
$$

So the convention is:

$$
\operatorname{Exp}(\tau) = \exp(\epsilon)
$$

where $\tau$ is the vector-space coordinate corresponding to the tangent-space element $\epsilon$.
