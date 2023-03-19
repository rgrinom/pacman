#pragma once

#include <cstdint>
#include <iostream>
#include <cmath>

struct Point {
  static const double kEps;
  double x, y;
  Point(double x = 0, double y = 0);
  Point& operator+=(const Point& p);
  Point& operator-=(const Point& p);
  Point& operator*=(double k);
  Point& operator/=(double K);
  double Len2() const;
  double Len() const;
};

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& lhs, double k);
Point operator*(double k, const Point& rhs);
Point operator/(const Point& lhs, double k);
Point floor(const Point& p);
Point ceil(const Point& p);
double dist2(const Point& p1, const Point& p2);
double dist(const Point& p1, const Point& p2);

bool operator==(const Point& p1, const Point& p2);

std::istream& operator>>(std::istream& in, Point& p);