// Ball.h
#pragma once

#include "Vector.hpp"
#include <raylib.h>
class Ball {
public:
  Ball(const int &, const int &, const int &, const int &, const Color &,
       const int &, const int &);

  void draw() const;

  void updatePosition(const double &, const double &);
  // getters and setters

  Vector2D getPosition() const { return position; }
  Vector2D getVelocity() const { return velocity; }
  Color getColor() const { return color; }
  void setPosition(Vector2D _position) {
    position.x = _position.x;
    position.y = _position.y;
  }
  void setVelocity(Vector2D _velocity) {
    velocity.x = _velocity.x;
    velocity.y = _velocity.y;
  }
  int getRadius() const { return radius; }
  int getMass() const { return mass; }
  double getXVel() const { return velocity.x; }
  double getYVel() const { return velocity.y; }
  void setXVel(const double &_xVel) { velocity.x = _xVel; }
  void setYVel(const double &_yVel) { velocity.y = _yVel; }
  double getXPos() const { return position.x; }
  double getYPos() const { return position.y; }
  void setXPos(const double &_xPos) { position.x = _xPos; }
  void setYPos(const double &_yPos) { position.y = _yPos; }

private:
  Vector2D position;
  Vector2D velocity;
  Color color;
  int radius;
  int mass;
};
