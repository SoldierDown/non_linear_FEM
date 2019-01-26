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
  $\left\{\right\}$
- ~~Conservation of energy~~
- Measure of deformation: strain-displacement equation
- Constitutive equation  
  
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
