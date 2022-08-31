#pragma once

#include "GameObject.hpp"

class Helpers {
public:
    static vector<GameObject*> SortGameObjectsByZ(vector<GameObject*> objects) {
        int iterations = 1;

        while(iterations > 0){
            iterations = 0;
            for(int i = 0; i < objects.size(); i++){
                if (i == objects.size() - 1) continue;

                if (objects.at(i)->getZ() > objects.at(i+1)->getZ()){
                    iter_swap(objects.begin() + i, objects.begin() + (i+1));
                    iterations++;
                }
            }
        }

        return objects;
    }
};