#include "GUI.hpp"
#include <filesystem>
#include <string>
#define RAYGUI_IMPLEMENTATION
#include "BallManager.hpp"
#include "raygui.h"
#include "raylib.h"
#include <iostream>

#define NUM_BUTTONS 6

#define SPACE_GRAVITY 0
#define MOON_GRAVITY 0.1
#define EARTH_GRAVITY 0.3
#define JUPITER_GRAVITY 0.75
#define ANTI_GRAVITY -0.4

GUI::GUI() : ballManager(0, 0, screenWidth, screenHeight, SPACE_GRAVITY) {
  InitWindow(screenWidth, screenHeight, "Ball Game");
  GuiLoadStyle("assets/styles/dark/style_dark.rgs");
  GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

  bgImage = LoadTexture("assets/images/space_planet.png");
}

void GUI::run() {
  GUI gui;
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    gui.step();
  }
  CloseWindow();
}

void GUI::step() {

  BeginDrawing();

  ClearBackground(WHITE);

  setupButtonPanel();

  ballManager.drawBalls();

  EndDrawing();
}

void GUI::setupButtonPanel() {

  float dividerX = getScreenWidth() * 0.8;
  ballManager.setMaxWidth(dividerX);
  float panelWidth = getScreenWidth() - dividerX;
  float buttonHeight = (float)getScreenHeight() / NUM_BUTTONS;

  NPatchInfo nPatchInfo = {
      (Rectangle){0.0f, 0.0f, (float)bgImage.width, (float)bgImage.height},
      0,
      0,
      0,
      0,
      NPATCH_NINE_PATCH};

  Rectangle rect = {0, 0, dividerX, (float)getScreenHeight()};

  DrawTextureNPatch(bgImage, nPatchInfo, rect, Vector2{0, 0}, 0, RAYWHITE);

  float i = 0;

  if (GuiButton((Rectangle){dividerX, i, panelWidth, buttonHeight},
                "Add Ball")) {
    if (ballType == 1) {

      ballManager.addBall();
    }
    if (ballType == 2) {
      ballManager.addMetalBall();
    }
  }

  i += buttonHeight;

  if (GuiButton((Rectangle){dividerX, i, panelWidth, buttonHeight},
                "Add Big Ball")) {
    if (ballType == 1) {

      ballManager.addBigBall();
    }

    if (ballType == 2) {
      ballManager.addBigMetalBall();
    }
  }

  i += buttonHeight;

  if (GuiButton((Rectangle){dividerX, i, panelWidth, buttonHeight},
                "Reset Screen")) {
    ballManager.removeAll();
  }

  i += buttonHeight;

  if (GuiButton((Rectangle){dividerX, i, panelWidth, buttonHeight},
                "Change Ball Type")) {
    toggleBallType();
  }

  i += buttonHeight;

  if (GuiButton((Rectangle){dividerX, i, panelWidth, buttonHeight},
                "Change Planet")) {
    togglePlanet();
  }

  i += buttonHeight;

  if (GuiButton((Rectangle){dividerX, i, panelWidth, buttonHeight},
                "Toggle Theme")) {
    toggleTheme();
  }
}

void GUI::togglePlanet() {
  planet++;

  if (planet >= 6) {
    planet = 1;
    bgImage = LoadTexture("assets/images/space_planet.png");
    ballManager.setGravity(SPACE_GRAVITY);
  }
  if (planet == 2) {
    bgImage = LoadTexture("assets/images/moon_planet.png");
    ballManager.setGravity(MOON_GRAVITY);
  }
  if (planet == 3) {
    bgImage = LoadTexture("assets/images/earth_planet.png");
    ballManager.setGravity(EARTH_GRAVITY);
  }
  if (planet == 4) {
    bgImage = LoadTexture("assets/images/jupiter_planet.png");
    ballManager.setGravity(JUPITER_GRAVITY);
  }
  if (planet == 5) {
    bgImage = LoadTexture("assets/images/anti_gravity_planet.png");
    ballManager.setGravity(ANTI_GRAVITY);
  }
}

void GUI::toggleBallType() {
  ballType++;

  if (ballType >= 3) {
    ballType = 1;
  }
}

void GUI::toggleTheme() {

  theme++;

  std::cout << theme << std::endl;

  if (theme >= 13) {
    theme = 1;
    GuiLoadStyleDefault();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 2) {
    GuiLoadStyle("assets/styles/dark/style_dark.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }

  if (theme == 3) {
    GuiLoadStyle("assets/styles/bluish/style_bluish.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }

  if (theme == 4) {
    GuiLoadStyle("assets/styles/candy/style_candy.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 5) {
    GuiLoadStyle("assets/styles/cherry/style_cherry.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 6) {
    GuiLoadStyle("assets/styles/cyber/style_cyber.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 7) {
    GuiLoadStyle("assets/styles/jungle/style_jungle.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 8) {
    GuiLoadStyle("assets/styles/lavanda/style_lavanda.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 9) {
    GuiLoadStyle("assets/styles/terminal/style_terminal.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 10) {
    GuiLoadStyle("assets/styles/sunny/style_sunny.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 11) {
    GuiLoadStyle("assets/styles/ashes/style_ashes.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
  if (theme == 12) {
    GuiLoadStyle("assets/styles/enefete/style_enefete.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  }
}
