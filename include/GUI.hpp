// GUI.h
#pragma once

#include "Ball.hpp"
#include "BallManager.hpp"
#include <raylib.h>

class GUI {
public:
  int getScreenWidth() const { return screenWidth; }
  int getScreenHeight() const { return screenHeight; }
  static void run();

private:
  GUI();
  void step();
  void toggleTheme();
  void setupButtonPanel();
  void togglePlanet();
  void toggleBallType();
  int screenWidth = 1500;
  int screenHeight = 1000;

  int ballType = 1, planet = 1, theme = 2;

  Texture2D bgImage;

  BallManager ballManager;
};
