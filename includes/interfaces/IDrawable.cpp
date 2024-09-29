#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class IDrawable
{
public:
  Drawable *source;
  int z = 0;

  static void Sort(vector<IDrawable> &drawables)
  {
    if (drawables.empty())
      return;

    int iterations = 0;

    while (iterations > 0)
    {
      iterations = 0;
      for (ulong i = 0; i < drawables.size() - 1; i++)
      {
        if (drawables[i].z < drawables[i + 1].z)
        {
          iter_swap(drawables.begin() + i, drawables.begin() + (i + 1));
          iterations++;
        }
      }
    }
  }

  IDrawable(Drawable *source, int z = 0)
  {
    this->source = source;
    this->z = z;
  }

  Transformable *transformable()
  {
    return dynamic_cast<Transformable *>(this->source);
  }
};