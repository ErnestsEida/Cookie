#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class IDrawable {
public:
  Drawable* drawable = nullptr;
  int z;

  IDrawable(Drawable* drawable, int z = 0) {
    this->drawable = drawable;
    this->z = z;
  }

  // Currently using bubble sort, but might need to remake this into quick sort or something if performance issues are enountered
  static vector<IDrawable> SortByZ(vector<IDrawable> tDrawables) {
        if (tDrawables.size() < 2) return tDrawables;
        int iterations = 1;

        while(iterations > 0) {
            iterations = 0;
            for(size_t i = 0; i < tDrawables.size() - 1; i++) {
                if (tDrawables[i].z < tDrawables[i+1].z) {
                    iter_swap(tDrawables.begin() + i, tDrawables.begin() + (i + 1));
                    iterations++;
                }
            }
        }
        
        return tDrawables;
    }
};