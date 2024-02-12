#include "Ball.hpp"
#include <raylib.h>

Ball::Ball(const int &_x, const int &_y, const int &_dx, const int &_dy,
           const Color &_color, const int &_radius, const int &_mass)
    : color(_color), radius(_radius), mass(_mass) {

  position.x = _x;
  position.y = _y;
  velocity.x = _dx;
  velocity.y = _dy;
}

void Ball::updatePosition(const double &xAcc, const double &yAcc) {
  velocity.x = velocity.x + xAcc;
  velocity.y = velocity.y + yAcc;

  position = position + velocity;
}

void Ball::draw() const { DrawCircle(position.x, position.y, radius, color); }
