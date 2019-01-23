# Solution
## 1.1.
let 
\begin{aligned}
u_x &= \alpha v_t \\\\
u &= v_x
\end{aligned} 
along with the following derivatives
\begin{aligned}
u_s &= u_x x_s + u_y y_s \\\\
v_s &= v_x x_s + v_y y_s
\end{aligned}
Writing (1)-(2) as a single matrix equation gives
\begin{bmatrix}
    1 & 0 & 0 & -\alpha \\\\
    0 & 0 & 1 & 0 \\\\
    x_s & y_s & 0 & 0 \\\\
    0 & 0 & x_s & y_s
\end{bmatrix}
=
\begin{bmatrix}
    x_{11} & x_{12} & x_{13} & \dots  & x_{1n} \\
    x_{21} & x_{22} & x_{23} & \dots  & x_{2n} \\
    \vdots & \vdots & \vdots & \ddots & \vdots \\
    x_{d1} & x_{d2} & x_{d3} & \dots  & x_{dn}
\end{bmatrix}
