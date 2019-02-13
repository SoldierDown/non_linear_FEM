#ifndef CLOTH_H_
#define CLOTH_H_
#include "Particle.h"
#include "Triangle.h"
#include "Spring.h"
#include <vector>
#include<iostream>
#define STRUCTURAL 0.8
#define SHEAR    0.8
#define BENDING  0.8
class Cloth
{
private:

public:
    Cloth(/* args */);
    ~Cloth();
    double time_step = 10.0;
    int rows;
    int cols;
    double cell_width;
    std::vector<Particle> particles;
    std::vector<Triangle> triangles;
    std::vector<Spring> springs;
    glm::vec3 gravity = glm::vec3(0.0, -0.3, 0.0);
    glm::vec3 wind = glm::vec3(0.0, 0.0, 0.0);
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
            particles.push_back(Particle(glm::vec3(j * cell_width, i * cell_width, 0.0),50));
        }
    }


    std::cout<<"PARTICLES ALL SET: "<<(rows - 1) * (cols - 1)<<std::endl;

    // set up triangles

    for(int i = 1; i < rows; i++)
    {
        for(int j = 1; j < cols; j++)
        {
            triangles.push_back(Triangle((i - 1) * cols + j - 1,i * cols + j, i * cols + j - 1));
            triangles.push_back(Triangle(i * cols + j, (i - 1) * cols + j - 1, (i - 1) * cols + j));
        }
    }
    std::cout<<"TRIANGLES ALL SET. SIZE: "<<triangles.size()<<std::endl;

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
    particles[rows * cols/2+cols/2].force[2] -= 50;
    particles[rows * cols/2+cols/2 + 5].force[2] -= 50;
    particles[rows * cols/2+cols/2 - 5].force[2] -= 50;
    particles[rows * cols/2+cols/2 + 20].force[2] -= 50;
    // pin some vertices
    //for(int i = (rows - 1) * cols; i < rows * cols; i++) particles[i].SetStatic();
    //for(int i = 0; i < rows; i++) particles[i * cols].SetStatic();
    particles[rows * cols - 1].SetStatic();
    particles[(rows - 1) * cols].SetStatic();





}


void Cloth::Update()
{
    // add external forces
    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].force += glm::vec3(time_step * gravity[0], time_step * gravity[1], time_step * gravity[2]);
        //particles[i].force += glm::vec3(time_step * wind[0], time_step * wind[1], time_step * wind[2]);
    }
    // apply spring forces
    for(int n = 0; n < 20; n++)
    {
        for(int i = 0; i < springs.size(); i++)
        {
            springs[i].Constraint();
        }
    }

    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].Update();
    }
    
    
}


void Cloth::Visualize()
{

}





#endif