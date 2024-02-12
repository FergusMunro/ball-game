#include <raylib.h>
#define CATCH_CONFIG_MAIN
#include "Ball.hpp"
#include "BallManager.hpp"
#include "catch.h"

class BallManagerTest {
public:
  BallManagerTest() : ballManager(0, 0, 100, 100, 0) {}

  void testIsInWall1() {
    Ball ball(50, 50, 20, 20, BLACK, 20, 20);

    ballManager.isInWall(ball);
    REQUIRE(ball.getXPos() == 50);
    REQUIRE(ball.getYPos() == 50);
    REQUIRE(ball.getXVel() == 20);
    REQUIRE(ball.getYVel() == 20);
  }

  void testIsInWall2() {
    Ball ball(10, 50, 20, 20, BLACK, 20, 20);

    ballManager.isInWall(ball);
    REQUIRE(ball.getXPos() == 20);
    REQUIRE(ball.getYPos() == 50);
    REQUIRE(ball.getXVel() == -20);
    REQUIRE(ball.getYVel() == 20);
  }

  void testIsInWall3() {
    Ball ball(50, 90, 20, 20, BLACK, 20, 20);

    ballManager.isInWall(ball);
    REQUIRE(ball.getXPos() == 50);
    REQUIRE(ball.getYPos() == 80);
    REQUIRE(ball.getXVel() == 20);
    REQUIRE(ball.getYVel() == -20);
  }

  void testIsInWall4() {
    Ball ball(20, 50, 20, 20, BLACK, 20, 20);

    ballManager.isInWall(ball);
    REQUIRE(ball.getXPos() == 20);
    REQUIRE(ball.getYPos() == 50);
    REQUIRE(ball.getXVel() == -20);
    REQUIRE(ball.getYVel() == 20);
  }

  void testIntersecting1() {
    Ball ball1(50, 70, 0, 0, BLACK, 5, 5);
    Ball ball2(40, 50, 0, 0, BLACK, 12, 12);

    REQUIRE(!ballManager.areIntersecting(ball1, ball2));
  }

  void testIntersecting2() {
    Ball ball1(50, 70, 0, 0, BLACK, 5, 5);
    Ball ball2(55, 60, 0, 0, BLACK, 12, 12);

    REQUIRE(ballManager.areIntersecting(ball1, ball2));
  }

  void testIntersecting3() {
    Ball ball1(50, 70, 0, 0, BLACK, 5, 5);
    Ball ball2(55, 58, 0, 0, BLACK, 12, 12);

    REQUIRE(ballManager.areIntersecting(ball1, ball2));
  }

  void testBounceBalls1() {
    Ball ball1(50, 70, 15, 20, BLACK, 10, 10);
    Ball ball2(80, 20, -40, 15, BLACK, 15, 15);
    ballManager.ballBounce(ball1, ball2);

    Vector2D v1 = ball1.getVelocity();
    Vector2D v2 = ball2.getVelocity();

    REQUIRE(v1.x == Approx(0.176).epsilon(0.1));
    REQUIRE(v1.y == Approx(44.7).epsilon(0.1));

    REQUIRE(v2.x == Approx(-30.1).epsilon(0.1));
    REQUIRE(v2.y == Approx(-1.47).epsilon(0.1));
  }

private:
  BallManager ballManager;
};

TEST_CASE("Wall Bounce") {
  BallManagerTest ballManagerTest;
  ballManagerTest.testIsInWall1();
  ballManagerTest.testIsInWall2();
  ballManagerTest.testIsInWall3();
  ballManagerTest.testIsInWall4();
}

TEST_CASE("Balls Intersecting") {
  BallManagerTest ballManagerTest;
  ballManagerTest.testIntersecting1();
  ballManagerTest.testIntersecting2();
  ballManagerTest.testIntersecting3();
}

TEST_CASE("Balls Bounce") {
  BallManagerTest ballManagerTest;
  ballManagerTest.testBounceBalls1();
}
