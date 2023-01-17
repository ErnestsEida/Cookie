#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class IDrawable {
public:
    Drawable* drawable;
    int z;

    IDrawable(Drawable* drawable, int z) {
        this->drawable = drawable;
        this->z = z;
    }

    static vector<IDrawable*> SortByZ(vector<IDrawable*> tDrawables) {
        int iterations = 1;

        while(iterations > 0) {
            iterations = 0;
            for(size_t i = 0; i < tDrawables.size() - 1; i++) {
                if (tDrawables[i]->z < tDrawables[i+1]->z) {
                    iter_swap(tDrawables.begin() + i, tDrawables.begin() + (i + 1));
                    iterations++;
                }
            }
        }
        
        return tDrawables;
    }
};