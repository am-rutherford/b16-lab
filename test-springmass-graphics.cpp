/** file: test-springmass-graphics.cpp
 ** brief: Tests the spring mass simulation with graphics
 ** author: Andrea Vedaldi
 **/

#include "graphics.h"
#include "springmass.h"

#include <iostream>
#include <sstream>
#include <iomanip>
// need to initalise the drawable function better
/* ---------------------------------------------------------------- */
class SpringMassDrawable : public SpringMass, public Drawable {
/* ---------------------------------------------------------------- */
private:
  Figure figure ;

public:
  SpringMassDrawable(Spring * spring) // delegation of constructors
  : figure("Spring Mass"), SpringMass(spring)
  {
    figure.addDrawable(this) ;
  }

  void draw() {
    // need mass objects
    double thickness = 1;
    Mass * m1 = spring->getMass1() ; 
    Mass * m2 = spring->getMass2() ;

    Vector2 m1pos = m1->getPosition() ;
    Vector2 m2pos = m2->getPosition() ;

    figure.drawCircle(m1pos.x,m1pos.y,m1->getRadius()) ;
    figure.drawCircle(m2pos.x,m2pos.y,m2->getRadius()) ;
    figure.drawLine(m1pos.x,m1pos.y,m2pos.x,m2pos.y, thickness) ;
  }

  void display() {
    figure.update() ; // updates the figure rather than printing message on screen
  }
} ;

int main(int argc, char** argv)
{
  glutInit(&argc,argv) ;
  const double dt = 1/120.0 ;
  const double mass = 0.05 ;
  const double radius = 0.02 ;
  const double naturalLength = 0.95 ;
  const double stiffness = 1 ;
  
  Mass m1(Vector2(-.5,0), Vector2(), mass, radius) ;
  Mass m2(Vector2(+.5,0), Vector2(), mass, radius) ;

  Spring spring(&m1,&m2, naturalLength, stiffness); 

  SpringMassDrawable springmass(&spring) ;


  run(&springmass, dt) ;
  return 0 ;
}

