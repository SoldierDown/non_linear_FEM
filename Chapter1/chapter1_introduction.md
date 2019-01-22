# Chapter 1.  Introduction
## 1.1 Basic steps for non-linear FEM:
- Develop a model
- Formulate governing equations
- Discretize the equations
- Solve the equations
- Interpretate the results

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
- Elements in Lagrangian meshes can become severely**distorted**, and element accuracy degrades with distortion, which results in that the magnitude of deformation has to be limited. 
## 1.4 Classification of PDEs
### 1.4.1 Hyperbolic e.g. wave propagation
### 1.4.2 Parabolic e.g. diffusion problems such as heat conduction
$\vec{q}=-k\nabla u$
### 1.4.3 Elliptic e.g. elasticity and Laplace equations
