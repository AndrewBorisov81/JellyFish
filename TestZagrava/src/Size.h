#pragma once

class Size
{
public:
  Size() {};
  Size(float aW, float aH) : w(aW), h(aH) { };

  float w{ 0.0f };
  float h{ 0.0f };
};