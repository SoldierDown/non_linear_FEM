#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include "glm/glm.hpp"
class Particle
{
private:
    /* data */

public:
    Particle(glm::vec3 pos_, double mass_);
    ~Particle();
    bool isStatic;
    double mass;
    double time_step = 1.0;
    double damping = 0.99;
    glm::vec3 pos_cur;
    glm::vec3 pos_last;
    glm::vec3 v;
    glm::vec3 force;
    void Init(glm::vec3 pos_, double mass_);
    void SetStatic();
    void Update();


    Particle& operator=(const Particle& other);
};

Particle::Particle(glm::vec3 pos_, double mass_)
:pos_last(pos_), pos_cur(pos_), mass(mass_), isStatic(false), v(glm::vec3(0.0, 0.0, 0.0)), force(glm::vec3(0.0, 0.0, 0.0))
{
    //Init(pos_, mass_, damping_);
}

Particle::~Particle()
{
}

void Particle::Init(glm::vec3 pos_, double mass_)
{
    pos_last = pos_;
    pos_cur = pos_;
    mass = mass_;
    isStatic = false;
}

void Particle::SetStatic()
{
    isStatic =  true;
}

void Particle::Update()
{
    if (isStatic) {
        return;
    }
    else
    {
	    glm::vec3 temp = pos_cur;
	    pos_cur += (glm::vec3((pos_cur[0] - pos_last[0]) * damping, (pos_cur[0] - pos_last[0]) * damping, (pos_cur[0] - pos_last[0]) * damping) 
                    + glm::vec3((force[0]/mass)*time_step, (force[1]/mass)*time_step, (force[2]/mass)*time_step));
	    pos_last = temp;
	    force = glm::vec3(0,0,0);
    }
}

Particle& Particle::operator=(const Particle& other) 
{
    isStatic = other.isStatic;
    mass = other.mass;
    force = other.force;
    pos_cur = other.pos_cur;
    pos_last = other.pos_last;
    return *this;
}






#endif