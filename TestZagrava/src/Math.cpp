#include "Math.h"
#include "Point.h"

#include <stdlib.h>
#include <math.h>  

float Math::area(Point A, Point B, Point C)
{
  return abs((A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y))/2);
}

bool Math::isInside(Point A, Point B, Point C, Point D, Point m)
{
  float S = area(A, B, C) + area(A, D, C);
  float A1 = area(m, A, B);
  float A2 = area(m, B, C);
  float A3 = area(m, C, D);
  float A4 = area(m, A, D);

  return (S == (A1 + A2 + A3 + A4));
}

float Math::distance(int x1, int y1, int x2, int y2)
{
  return sqrt(pow(x2 - x1, 2) +
    pow(y2 - y1, 2) * 1.0);
}
