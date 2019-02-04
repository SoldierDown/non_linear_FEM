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
    void Update();
};

Spring::Spring(Particle *p1_, Particle *p2_, double stiff_)
:p1(p1_), p2(p2_), stiff(stiff_)
{
    // set original length
    l0 = (p2_->pos_cur - p1_->pos_cur).length();
}

Spring::~Spring()
{

}

void Spring::Update()
{
	
	glm::vec3 p1_to_p2 = p2->pos_cur - p1->pos_cur; // vector from p1 to p2
	float current_distance = p1_to_p2.length(); // current distance between p1 and p2
	glm::vec3 correctionVector = glm::vec3(p1_to_p2[0] * (1 - l0/current_distance), p1_to_p2[1] *(1 - l0/current_distance), p1_to_p2[2] * (1 - l0/current_distance)); // The offset vector that could moves p1 into a distance of rest_distance to p2
	glm::vec3 correctionVectorHalf = glm::vec3(correctionVector[0]*0.5, correctionVector[1]*0.5, correctionVector[2]*0.5); // Lets make it half that length, so that we can move BOTH p1 and p2.
	p1->pos_cur +=(correctionVectorHalf); // correctionVectorHalf is pointing from p1 to p2, so the length should move p1 half the length needed to satisfy the constraint.
	p2->pos_cur +=(-correctionVectorHalf); // we must move p2 the negative direction of correctionVectorHalf since it points from p2 to p1, and not p1 to p2.	
	
}




#endif 