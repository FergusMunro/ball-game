#pragma once

#include <cmath>
#include <iostream>

struct Vector2D {
public:
  double x, y;

  // Constructors
  Vector2D() : x(0.0), y(0.0) {}
  Vector2D(double _x, double _y) : x(_x), y(_y) {}

  // Vector addition
  Vector2D operator+(const Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  // Vector subtraction
  Vector2D operator-(const Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  // Scalar multiplication
  Vector2D operator*(int scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }
  Vector2D operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  // Dot product
  double dot(const Vector2D &other) const { return x * other.x + y * other.y; }

  // Magnitude (length) of the vector
  double magnitude() const { return std::sqrt(x * x + y * y); }

  // Normalized vector
  Vector2D normalize() const {
    double mag = magnitude();
    if (mag != 0.0) {
      return Vector2D(x / mag, y / mag);
    } else {
      // Handle division by zero or zero magnitude
      std::cerr << "Cannot normalize a zero vector.\n";
      return *this;
    }
  }
};
