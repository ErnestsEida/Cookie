// STD Includes
#include <vector>
#include <iostream>

// SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// Cookie Includes
#include "./GameObject.cpp"

using namespace sf;
using namespace std;

class CookieEngine {
private:
    RenderWindow app;
    bool window_initialized = false;
public:
    void InitWindow(int width, int height, string title){
        ContextSettings settings;
        settings.antialiasingLevel = 16;
        app.create(VideoMode(width, height), title, Style::Default, settings);
        window_initialized = true;
    }

    void Run(){
        if (!window_initialized) {
            cout << "Window not initialzed!" << endl;
            return;
        }
        app.setFramerateLimit(60);

        vector<Transformable*> holder;
        while(app.isOpen()){
            Event event;
            if (app.pollEvent(event)){
                if (event.type == Event::Closed)
                    app.close();
            }
            vector<GameObject*> gameobjects = GameObject::object_vector;
            vector<Transformable*> all_drawables;
            // GAMEOBJECT UPDATE AND STORAGE UPDATES
            for(int i = 0;i < gameobjects.size();i++) {
                // SYNC AND UPDATE
                gameobjects[i]->UpdateRenderer();
                gameobjects[i]->Update();
                gameobjects[i]->FindCollision();
                gameobjects[i]->SyncComponents();
                // -------------
                holder = gameobjects[i]->GetDrawables();
                all_drawables.insert(all_drawables.end(), holder.begin(), holder.end());
            }

            app.clear();
            for(int i = 0;i < all_drawables.size();i++){
                app.draw(*dynamic_cast<Drawable*>(all_drawables[i]));
            }
            app.display();
        }
    }
};