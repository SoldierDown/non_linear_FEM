#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Particle.h"
#include<iostream>

class Triangle
{
private:
    
public:
    Triangle(int p1_, int p2_, int p3_);
    ~Triangle();
    std::vector<int> vertices;
    void Init(int p1_, int p2_, int p3_);
    void Visualize();
};

Triangle::Triangle(int p1_, int p2_, int p3_)
{
    Init(p1_, p2_, p3_);    
}

Triangle::~Triangle()
{
}

void Triangle::Init(int p1_, int p2_, int p3_)
{
    vertices.clear();
    vertices.push_back(p1_);
    vertices.push_back(p2_);
    vertices.push_back(p3_);
}

void Triangle::Visualize()
{

}












#endif