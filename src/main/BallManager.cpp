#include "BallManager.hpp"
#include "Ball.hpp"
#include "Vector.hpp"
#include <cmath>
#include <iostream>
#include <list>
#include <random>
#include <raylib.h>

BallManager::BallManager(const int _minWidth, const int _minHeight,
                         const int _maxWidth, const int _maxHeight,
                         const double _gravity)
    : minWidth(_minWidth), minHeight(_minHeight), maxWidth(_maxWidth),
      maxHeight(_maxHeight), gravity(_gravity) {}

void BallManager::addBall() {
  int x = GetRandomValue(minWidth, maxHeight);
  int y = GetRandomValue(minHeight, maxHeight);
  int dx = GetRandomValue(-15, 15);
  int dy = GetRandomValue(-15, 15);
  int radius = GetRandomValue(15, 25);

  int mass = radius;

  Color color;
  color.a = 255;
  int flag = 1;
  do {
    color.r = GetRandomValue(0, 255);
    color.g = GetRandomValue(0, 255);
    color.b = GetRandomValue(0, 255);
    if (color.r + color.g + color.b > 320) {
      flag = 0;
    }
  } while (flag == 1);

  ballList.push_back(Ball(x, y, dx, dy, color, radius, mass));
}

void BallManager::addBall(const int x, const int y, const int dx, const int dy,
                          const Color color, const int radius, const int mass) {
  ballList.push_back(Ball(x, y, dx, dy, color, radius, mass));
}

void BallManager::addBigBall() {
  int x = GetRandomValue(minWidth, maxHeight);
  int y = GetRandomValue(minHeight, maxHeight);
  int dx = GetRandomValue(-15, 15);
  int dy = GetRandomValue(-15, 15);
  int radius = GetRandomValue(36, 60);

  int mass = radius;

  Color color;
  color.a = 255;
  int flag = 1;
  do {
    color.r = GetRandomValue(0, 255);
    color.g = GetRandomValue(0, 255);
    color.b = GetRandomValue(0, 255);
    if (color.r + color.g + color.b > 320) {
      flag = 0;
    }
  } while (flag == 1);

  ballList.push_back(Ball(x, y, dx, dy, color, radius, mass));
}

void BallManager::addMetalBall() {

  int x = GetRandomValue(minWidth, maxHeight);
  int y = GetRandomValue(minHeight, maxHeight);
  int dx = GetRandomValue(-15, 15);
  int dy = GetRandomValue(-15, 15);
  int radius = GetRandomValue(15, 25);

  int mass = radius * 3;

  Color color;
  color.a = 255;
  int metalShade = GetRandomValue(0, 100) + 100;

  color.r = metalShade + GetRandomValue(-15, 15);
  color.b = metalShade + GetRandomValue(-15, 15);
  color.g = metalShade + GetRandomValue(-15, 15);

  ballList.push_back(Ball(x, y, dx, dy, color, radius, mass));
}

void BallManager::addBigMetalBall() {

  int x = GetRandomValue(minWidth, maxHeight);
  int y = GetRandomValue(minHeight, maxHeight);
  int dx = GetRandomValue(-15, 15);
  int dy = GetRandomValue(-15, 15);
  int radius = GetRandomValue(36, 60);

  int mass = radius * 3;

  Color color;
  color.a = 255;
  int metalShade = GetRandomValue(0, 100) + 100;

  color.r = metalShade + GetRandomValue(-15, 15);
  color.b = metalShade + GetRandomValue(-15, 15);
  color.g = metalShade + GetRandomValue(-15, 15);

  ballList.push_back(Ball(x, y, dx, dy, color, radius, mass));
}

void BallManager::removeBall() { ballList.pop_back(); }

void BallManager::removeAll() { ballList.clear(); }

void BallManager::drawBalls() {

  for (Ball &ball : ballList) {
    ball.updatePosition(0, gravity);
  }

  int i = 0, j = 0;

  for (Ball &ball : ballList) {

    isInWall(ball);

    j = 0;
    for (Ball &ball2 : ballList) {
      if (i == j) {

      } else {
        if (areIntersecting(ball, ball2)) {
          ballBounce(ball, ball2);
        }
      }
      j++;
    }
    i++;
  }

  for (const Ball &ball : ballList) {
    ball.draw();
  }
}

bool BallManager::areIntersecting(const Ball &ball1, const Ball &ball2) const {

  Vector2D resPos = ball1.getPosition() - ball2.getPosition();

  if (resPos.magnitude() <= ball1.getRadius() + ball2.getRadius()) {
    return true;
  } else {
    return false;
  }
}

void BallManager::isInWall(Ball &ball) {

  Vector2D position = ball.getPosition();
  Vector2D velocity = ball.getVelocity();

  if (position.x <= minWidth + ball.getRadius()) {
    velocity.x = -velocity.x;
    position.x = minWidth + ball.getRadius();
  } else if (position.x >= maxWidth - ball.getRadius()) {
    velocity.x = -velocity.x;
    position.x = maxWidth - ball.getRadius();
  }
  if (position.y <= minHeight + ball.getRadius()) {
    velocity.y = -velocity.y;
    position.y = minHeight + ball.getRadius();
  } else if (position.y >= maxHeight - ball.getRadius()) {
    velocity.y = -velocity.y;
    position.y = maxHeight - ball.getRadius();
  }

  ball.setVelocity(velocity);
  ball.setPosition(position);
}

void BallManager::ballBounce(Ball &ball1, Ball &ball2) {

  Vector2D x1 = ball1.getPosition();
  Vector2D x2 = ball2.getPosition();
  Vector2D v1 = ball1.getVelocity();
  Vector2D v2 = ball2.getVelocity();
  // only bounce balls if they move towards each other
  if ((v1.x - v2.x) * (x2.x - x1.x) + (v1.y - v2.y) * (x2.y - x1.y) >= 0) {

    double massValue = (ball2.getMass() + ball1.getMass());

    massValue = (2 * ball2.getMass()) / massValue;

    double dotProduct = (v1 - v2).dot(x1 - x2);
    double scalar = massValue * dotProduct;
    int magnitudeSquared = (x1 - x2).magnitude() * (x1 - x2).magnitude();
    scalar = scalar / magnitudeSquared;
    Vector2D nV1 = x1 - x2;
    nV1 = nV1 * scalar;
    nV1 = v1 - nV1;

    ball1.setVelocity(nV1);

    massValue = (double)2 * ball1.getMass() /
                (double)(ball2.getMass() + ball1.getMass());

    scalar = massValue * dotProduct / std::pow((x2 - x1).magnitude(), 2);

    Vector2D nV2 = x2 - x1;
    nV2 = nV2 * scalar;
    nV2 = v2 - nV2;

    ball2.setVelocity(nV2);
  }
}
