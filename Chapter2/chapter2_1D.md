# Chapter 2.  Lagrangian and Eulerian Finite Elements in One Dimension
## 2.1 Introduction  
### 2.1.1 Two Approach in development of Lagrangian finite elements  
- ***total Lagrangian formulation***  
  - with respect to the **Lagrangian**(material) coordinates $X$.  
  - variables are described in the **original** configuration.  
  - used much in solid mechanics.  
- ***updated Lagrangian formulation***  
  - with respect to the **Eulerian**(spatial) coordinates $x$.  
  - variables are described in the **current** configuration.  
  - can be used in solid mechanics where very large deformations are encountered.  
Besides, different **stress** and **deformation** measures are used.  
## 2.2 Total Lagrangian Formulation  
### 2.2.1 Governing Equations  
- Conservation of mass  
  $\rho J = \rho_0 J_0, J = \frac{\partial x}{\partial X}\frac{A}{A_0}$  
  $\Rightarrow \rho FA = \rho_0A_0$  
- Conservation of momentum  

  - $(A_0P)_X+\rho_0A_0b=\rho_0A_0\ddot{u}$  
  if cross-sectional area is constant in space:  
  $(A_0P)_X=A_0P_X\Rightarrow P_X+\rho_0b=\rho_0\ddot{u}$  
  - Equilibrium equation:  
  $\ddot{u}=0\Rightarrow(A_0P)_X+\rho_0A_0b=0$  
- ~~Conservation of energy~~: need not be considered if there's no heat or energy transfer.    
  $\rho_0\dot{\omega}_int=\dot{F}P$  
- Measure of deformation: strain-displacement equation  
  - displacement: $u(X,t)=\phi(X,t)-X=x-X$  
  - deformation gradient: $F=\frac{\partial\phi}{\partial X}=\frac{\partial x}{\partial X}$  
  - strain: $\varepsilon(X,t)=F(X,t)-1=\frac{\partial x}{\partial X}-1=\frac{\partial u}{\partial X}$  
- Constitutive equations  
  - totol form: $P(X,t)=S^{PF}(F(X,\overline{t}), \dot{F}(X,\overline{t}), etc., \overline{t}\leq t)$  
  - rate form: $\dot{P}(X,t)=S^{PF}_t(\dot{F}(X.overline{t}), F(X,\overline{t}), P(X,\overline{t}), etc., \overline{t}\leq t)$  
  - Example:($\alpha$: magnitude of damping, $E^PF$: Young's modulus for small deformations)  
    - Linear elastic material  
      total form: $P(X,t)=E^{PF}\varepsilon(X,t)=E^{PF}(F(X,t)-1)$  
      rate form: $\dot{P}(X,t)=E^{PF}\dot{\varepsilon}(X,t)=E^{PF}\dot{F}(X,t)$  
    - Linear viscoelastic material  
      $P(X,t)=E^{PF}[(F(X,t)-1)+\alpha\dot{F}(X,t)]=E^{PF}(\varepsilon+{\alpha}\dot{\varepsilon})$  
  
Besides, we require the deformation to be continuous: compatibility requirement.  
### 2.2.2 Boundary Conditions($X$)  
- displacement boundary  
  $u = \overline{u}$ on $\Gamma_u$  
- traction boundary  
  $n^0P=\overline{t_x}^0$ on $\Gamma_t$  
**NOTE**: the traction and displacement cannot be prescribed at the same point! See [explanation](./boundary_condition.pdf).  
### 2.2.3 Initial Conditions(t)
- $u(X,0)=u_0(X)$ for $X\in\[X_a,X_b\]$  
  $\dot{u}(X,0)=\nu_0(X)$ for $X\in\[X_a,X_b\]$  
- or if undeformed initially:
  $u(X,0)=0$, $\dot{u}(X,0)=0$
### Interior Continuity Conditions(jump conditions)
- $\[\[A_0P\]\]=0$
- $\[\[f(X)\]\]=f(X+\varepsilon)-f(X-\varepsilon)$, $\varepsilon\rightarrow 0$  
**NOTE**: in calculus, if $f(x)\in C^{-1}$: 	$\int_{a}^{b} f_x(x)\ dx=\sum_{i}^k\int_{x_{i-1}}^{x_i} f_x(x)\ dx=f(b)-f(a)-\sum_i^{k-1}\[\[f(x_i)\]\]$
  

  
## **Some Concepts**  
- semi-discretization: discretization **only** in space
