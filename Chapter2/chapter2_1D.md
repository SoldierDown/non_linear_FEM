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

## 1.2 Notation
- indicial notation 
- tensor notation
- matrix notation

## 1.3 Mesh Descriptions
### 1.3.1 Some Concepts
- **Node**: a coordinate location in space where the degrees of freedom(*DoFs*) are defined. The results of FEM(deflections, stresses, etc.) are given at the nodes.
- **Element**: the basic building block of FEM. e.g., lines, areas, solids.
### 1.3.2 Lagrangian(material) description
- The nodes are coincident with **material points**.
### 1.3.3 Eulerian(spatial) description
- The nodes are **fixed** in space.
### 1.3.4 Pros and Cons
- Boundary nodes remain on the boundary in Lagrangian meshes(simplifies the imposition of boundary conditions). In Eulerian meshs, boundary conditions must be imposed at points which are not nodes(complicated).
- Elements in Lagrangian meshes can become severely **distorted**, and element accuracy degrades with distortion, which results in that the magnitude of deformation has to be limited. 
## 1.4 Classification of PDEs
### 1.4.1 Hyperbolic e.g. wave propagation
- wave propagation: $\frac{\partial^2 \psi}{\partial t^2}=c^2\nabla^2\psi$
### 1.4.2 Parabolic
- heat conduction: $\vec{q}=-k\nabla u$
### 1.4.3 Elliptic
- Laplace's equations: $\nabla^2 \phi=0$ 
- elasticity 




**Some Concepts**  
- semi-discretization: discretization **only** in space
