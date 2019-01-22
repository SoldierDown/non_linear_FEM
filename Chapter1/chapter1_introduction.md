# Introduction
## Basic steps for non-linear FEM:
- Develop a model
- Formulate governing equations
- Discretize the equations
- Solve the equations
- Interpretate the results

## Notation
- indicial notation 
- tensor notation
- matrix notation

## Mesh Descriptions
### Some Concepts
- Node: a coordinate location in space where the degrees of freedom(*DoFs*) are defined. The results of FEM(deflections, stresses, etc.) are given at the nodes.
- Element: the basic building block of FEM. e.g., lines, areas, solidsmZ
### Lagrangian(material) description
- The nodes are coincident with material points.
### Eulerian(spatial) description
- The nodes are fixed in space.
### Pros and Cons
- Boundary nodes remain on the boundary in Lagrangian meshes(simplifies the imposition of boundary conditions). In Eulerian meshs, boundary conditions must be imposed at points which are not nodes(complicated).
- Elements in Lagrangian meshes can become severely distorted, and element accuracy degrades with distortion, which results in that the magnitude of deformation has to be limited. 
## Classification of PDEs
### Hyperbolic
### Parabolic
### Elliptic
