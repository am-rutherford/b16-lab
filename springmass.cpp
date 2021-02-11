/** file: springmass.cpp
 ** brief: SpringMass simulation implementation
 ** author: Andrea Vedaldi
 **/

#include "springmass.h"

#include <iostream>

/* ---------------------------------------------------------------- */
// class Mass
/* ---------------------------------------------------------------- */

Mass::Mass()
: position(), velocity(), force(), mass(1), radius(1)
{ }

Mass::Mass(Vector2 position, Vector2 velocity, double mass, double radius)
: position(position), velocity(velocity), force(), mass(mass), radius(radius),
xmin(-1),xmax(1),ymin(-1),ymax(1)
{ }

void Mass::setForce(Vector2 f)
{
  force = f ;
}

void Mass::addForce(Vector2 f)
{
  force = force + f ;
}

Vector2 Mass::getForce() const
{
  return force ;
}

Vector2 Mass::getPosition() const
{
  return position ;
}

Vector2 Mass::getVelocity() const
{
  return velocity ;
}

double Mass::getRadius() const
{
  return radius ;
}

double Mass::getMass() const
{
  return mass ;
}

double Mass::getEnergy(double gravity) const
{
  double energy = mass*position.y*gravity + 0.5*mass*velocity.norm()*velocity.norm();
  return energy ;
}

void Mass::step(double dt)
{
  Vector2 acc = force / mass ;
  position = position + velocity * dt + 0.5*acc*dt*dt;
  velocity = velocity + dt * acc ;
}

/* ---------------------------------------------------------------- */
// class Spring
/* ---------------------------------------------------------------- */

Spring::Spring(Mass * mass1, Mass * mass2, double naturalLength, double stiffness, double damping)
: mass1(mass1), mass2(mass2),
naturalLength(naturalLength), stiffness(stiffness), damping(damping)
{ }

Mass * Spring::getMass1() const
{
  return mass1 ;
}

Mass * Spring::getMass2() const
{
  return mass2 ;
}

Vector2 Spring::getForce() const //returns F_1
{
  Vector2 F;
  Vector2 u = mass2->getPosition() - mass1->getPosition() ;
  double l = u.norm() ;
  u = u/l ; //normalise u
  Vector2 v = dot(mass2->getVelocity() - mass1->getVelocity(),u) * u ; // potentially bad to have in one line 
  F = stiffness*(l-naturalLength)*u + damping*v;
  return F ;
}

double Spring::getLength() const
{
  Vector2 u = mass2->getPosition() - mass1->getPosition() ;
  return u.norm() ;
}

double Spring::getEnergy() const {
  double length = getLength() ;
  double dl = length - naturalLength;
  return 0.5 * stiffness * dl * dl ;
}

std::ostream& operator << (std::ostream& os, const Mass& m)
{
  os<<"("
  <<m.getPosition().x<<","
  <<m.getPosition().y<<")" ;
  return os ;
}

std::ostream& operator << (std::ostream& os, const Spring& s)
{
  return os<<"$"<<s.getLength() ;
}

/* ---------------------------------------------------------------- */
// class SpringMass : public Simulation
/* ---------------------------------------------------------------- */

SpringMass::SpringMass(Spring * spring, double gravity)
: spring(spring), gravity(gravity)
{ }

void SpringMass::display()
{
  Mass * m1 = spring->getMass1() ; 
  Mass * m2 = spring->getMass2() ;

  Vector2 m1pos = m1->getPosition() ;
  Vector2 m2pos = m2->getPosition() ;
  std::cout<< m1pos.x<<" "<<m1pos.y<<" "<<m2pos.x<<" "<<m2pos.y<<std::endl ;

}

double SpringMass::getEnergy() const
{
  double energy = 0 ;

/* INCOMPLETE: TYPE YOUR CODE HERE */

  return energy ;
}

void SpringMass::step(double dt)
{
  Vector2 g(0,-gravity) ;
  Mass * m1 = spring->getMass1() ; //why this no work man
  Mass * m2 = spring->getMass2() ;

  m1->setForce(g*(m1->getMass())) ; // set inital forces
  m2->setForce(g*(m1->getMass())) ; 

  Vector2 F = spring->getForce() ; // get force on spring
  m1->addForce(F) ;
  m2->addForce(-1*F) ;

  m1->step(dt) ; 
  m2->step(dt) ;

}



