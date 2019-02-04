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
    double dt = 0.01;
    double damping = 0.01;
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
    //std::cout<<"HERE"<<std::endl;
    force -= glm::vec3(damping * v[0], damping * v[1], damping * v[2]);
    glm::vec3 a = glm::vec3(force[0]/mass, force[1]/mass, force[2]/mass);
    v += glm::vec3(dt*a[0], dt*a[1], dt*a[2]);
    pos_cur += glm::vec3(dt*v[0],dt*v[1],dt*v[2]);
    //std::cout<<pos_cur[0]<<", "<<pos_cur[1]<<", "<<pos_cur[2]<<std::endl;
    pos_cur += glm::vec3((1.0-damping)*(pos_cur[0]-pos_last[0]), (1.0-damping)*(pos_cur[1]-pos_last[1]), (1.0-damping)*(pos_cur[2]-pos_last[2]))   
                        + glm::vec3(dt * a[0], dt * a[1], dt * a[2]);
    force = glm::vec3(0.0, 0.0, 0.0);
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