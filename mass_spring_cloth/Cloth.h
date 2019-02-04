#ifndef CLOTH_H_
#define CLOTH_H_
#include "Particle.h"
#include "Triangle.h"
#include "Spring.h"
#include <vector>
#include<iostream>
#define STRUCTURAL 1000
#define SHEAR    1000
#define BENDING  1000
class Cloth
{
private:

public:
    Cloth(/* args */);
    ~Cloth();
    int rows;
    int cols;
    double cell_width;
    std::vector<Particle> particles;
    std::vector<Triangle> triangles;
    std::vector<Spring> springs;
    glm::vec3 gravity = glm::vec3(0.0, -0.5, 0.0);
    void Init();
    void Update();
    void Visualize();
};

Cloth::Cloth(/* args */)
:rows(100), cols(100), cell_width(1.0)
{
    Init();
}

Cloth::~Cloth()
{
}

void Cloth::Init()
{
    // set up particles
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            particles.push_back(Particle(glm::vec3(j * cell_width, 0.0, i * cell_width), 1.0));
        }
    }


    std::cout<<"PARTICLES ALL SET"<<std::endl;

    // set up triangles

    for(int i = 1; i < rows; i++)
    {
        for(int j = 1; j < cols; j++)
        {
            triangles.push_back(Triangle((i - 1) * cols + j - 1, i * cols + j - 1, i * cols + j));
            triangles.push_back(Triangle(i * cols + j, (i - 1) * cols + j, (i - 1) * cols + j - 1));
        }
    }
    std::cout<<"TRIANGLES ALL SET"<<std::endl;

    // set up mass-spring system
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(i == 0)
            {
                if(j != 0)
                {
                    // horizontal(-) springs  on the top row
                    springs.push_back(Spring(&particles[i * cols + j - 1], &particles[i * cols + j], STRUCTURAL));
                    // (/) springs on the top row
                    springs.push_back(Spring(&particles[(i + 1) * cols + j - 1],&particles[i * cols + j], SHEAR));
                }
            }
            else if(j == 0)
            {   
                // vertical(|) springs on the left boundary col
                springs.push_back(Spring(&particles[(i - 1) * cols], &particles[i * cols], STRUCTURAL));
            }
            else
            {
                // vertical(|) springs
                springs.push_back(Spring(&particles[(i - 1) * cols + j], &particles[i * cols + j], STRUCTURAL));
                // horizontal(-) springs
                springs.push_back(Spring(&particles[i * cols + j - 1], &particles[i * cols + j], STRUCTURAL));
                // (\) springs 
                springs.push_back(Spring(&particles[(i - 1) * cols + j - 1], &particles[i * cols + j], SHEAR));
                if(i != rows - 1)
                {
                    // (/) springs
                    springs.push_back(Spring(&particles[(i + 1) * cols + j -1], &particles[i * cols + j], SHEAR));
                }
            }

            if(i > 1)
            {
                springs.push_back(Spring(&particles[(i - 2) * cols + j], &particles[i * cols + j], BENDING));
            }
            if(j > 1)
            {
                springs.push_back(Spring(&particles[i * cols + j], &particles[i * cols + j - 2], BENDING));
            }
            
        }
    }
    

    std::cout<<"SPRINGS ALL SET"<<std::endl;

    // pin some vertices
    for(int i = 0 ; i < cols; i++) 
    {
        if(i < cols/3 | i > 2 * cols /3)
        particles[cols * rows -1 - i].SetStatic();
    }
    //particles[0].SetStatic();
    //particles[cols - 1].SetStatic();





}


void Cloth::Update()
{
    // apply spring forces
    for(int i = 0; i < springs.size(); i++)
    {
        springs[i].Update();
    }
    // apply external forces
    for(int i = 0; i < particles.size(); i++)
    {
        //if(i == particles.size()/2) particles[i].force += glm::vec3(-1, 0, 0);
        particles[i].force += gravity;
        particles[i].Update();
    }
}


void Cloth::Visualize()
{

}





#endif