#ifndef SPRING_H_
#define SPRING_H_
#include<iostream>
#include"Particle.h"
class Spring
{
private:
    Particle *p1;
    Particle *p2;
    double l0;
    double stiff;
public:
    Spring(Particle* p1_, Particle* p2_, double stiff_);
    ~Spring();
    void Constraint();
};

Spring::Spring(Particle *p1_, Particle *p2_, double stiff_)
:p1(p1_), p2(p2_), stiff(stiff_)
{
    // set original length
    l0 = glm::length(p2_->pos_cur - p1_->pos_cur);
}

Spring::~Spring()
{

}

void Spring::Constraint()
{
	glm::vec3 p2_to_p1 = p1->pos_cur - p2->pos_cur; // vector from p1 to p2
	p2_to_p1 *= (1.0f - l0/glm::length(p2_to_p1)) * stiff;
    if(!p1->isStatic)
    p1->pos_cur -= p2_to_p1;
    if(!p2->isStatic)
    p2->pos_cur += p2_to_p1;
}




#endif 