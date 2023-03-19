#include "../include/point.hpp"

const double Point::kEps = 0.00001;

Point::Point(double x, double y) : x(x), y(y) {}

Point& Point::operator+=(const Point& p) {
  x += p.x;
  y += p.y;
  return *this;
}

Point& Point::operator-=(const Point& p) {
  x -= p.x;
  y -= p.y; 
  return *this;
}

Point& Point::operator*=(double k) {
  x *= k;
  y *= k;
  return *this;
}

Point& Point::operator/=(double k) {
  x /= k;
  y /= k;
  return *this;
}

Point operator+(const Point& lhs, const Point& rhs) {
  Point res = lhs;
  res += rhs;
  return res;
}

Point operator-(const Point& lhs, const Point& rhs) {
  Point res = lhs;
  res -= rhs;
  return res;
}

Point operator*(const Point& lhs, double k) {
  Point res = lhs;
  res *= k;
  return res;
}

Point operator*(double k, const Point& rhs) { return rhs * k; }
Point operator/(const Point& lhs, double k) {
  Point res = lhs;
  res /= k;
  return res;
}

Point floor(const Point& p) {
  Point ret = p;
  ret.x = std::floor(ret.x);
  ret.y = std::floor(ret.y);
  return ret;
}

Point ceil(const Point& p) {
  Point ret = p;
  ret.x = std::ceil(ret.x);
  ret.y = std::ceil(ret.y);
  return ret;
}

double Point::Len2() const { return x * x + y * y; }
double Point::Len() const { return std::sqrt(Len2()); }
double dist2(const Point& p1, const Point& p2) { return (p2 - p1).Len2(); }
double dist(const Point& p1, const Point& p2) { return (p2 - p1).Len(); }

bool operator==(const Point& p1, const Point& p2) {
  return dist2(p1, p2) < Point::kEps * Point::kEps;
}

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x >> p.y;
  return in;
}