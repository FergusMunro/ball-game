// BallManager.h
#include <list>
#include <raylib.h>
#pragma once

#define LEFT_WALL 0
#define RIGHT_WALL 1
#define TOP_WALL 2
#define BOTTOM_WALL 3

class Ball;

class BallManager {
public:
  BallManager(const int, const int, const int, const int, const double);

  void addBall();
  void addBall(const int, const int, const int, const int, const Color,
               const int, const int);
  void removeBall();
  void removeAll();
  void drawBalls();
  void addBigBall();

  void addMetalBall();
  void addBigMetalBall();

  std::list<Ball> getBallList() { return ballList; }
  double getGravity() { return gravity; }

  // setters
  void setGravity(const double &newGravity) { gravity = newGravity; }
  void setMinWidth(const int &newMinWidth) { minWidth = newMinWidth; }
  void setMaxWidth(const int &newMaxWidth) { maxWidth = newMaxWidth; }
  void setMinHeight(const int &newMinHeight) { minHeight = newMinHeight; }
  void setMaxHeight(const int &newMaxHeight) { maxHeight = newMaxHeight; }

  friend class BallManagerTest;

private:
  int minWidth;
  int minHeight;
  int maxWidth;
  int maxHeight;
  double gravity;

  std::list<Ball> ballList;

  bool areIntersecting(const Ball &, const Ball &) const;
  void isInWall(Ball &);
  void ballBounce(Ball &, Ball &);
};
