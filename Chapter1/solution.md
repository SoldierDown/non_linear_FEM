# Solution
## 1.1.  
Let 
\begin{aligned}
u_x &= \alpha v_t \\\\
u &= v_x
\end{aligned} 
along with the following derivatives
\begin{aligned}
u_s &= u_x x_s + u_y y_s \\\\
v_s &= v_x x_s + v_y y_s
\end{aligned}
Writing equations above as a single matrix equation gives
\begin{gather}
\begin{bmatrix}
    1 & 0 & 0 & -\alpha \\\\
    0 & 0 & 1 & 0 \\\\
    x_s & y_s & 0 & 0 \\\\
    0 & 0 & x_s & y_s
\end{bmatrix}
\begin{bmatrix}
0  \\\\
-u \\\\
u_s \\\\
v_s \\\\
\end{bmatrix}=
\begin{bmatrix}
E_1 \\\\
E_2 \\\\
u_s \\\\
v_s \\\\
\end{bmatrix}
\end{gather}
Set $\det (A) = 0$, which yields 
\begin{aligned}
y^2_s = 0
\end{aligned}
In this case, $a = 1, b = c = 0$, so $ b^2 -ac = 0 \Rightarrow parabolic$
