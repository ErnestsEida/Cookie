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
#include "./Camera.hpp"

using namespace sf;
using namespace std;

class CookieEngine {
private:
    RenderWindow app;
    bool window_initialized = false;
    Camera* mainCamera;
public:
    void InitWindow(int width, int height, string title){
        ContextSettings settings;
        settings.antialiasingLevel = 16;
        app.create(VideoMode(width, height), title, Style::Default, settings);
        window_initialized = true;
        Camera* camera = new Camera(width, height);
        camera->SetCenter(width/2, height/2);
        this->mainCamera = camera;
        this->app.setView(*this->mainCamera->GetView());
    }

    Camera* GetMainCamera() const {
        return this->mainCamera;
    }

    void Run(){
        if (!window_initialized) {
            cout << "Window not initialzed!" << endl;
            return;
        }
        app.setFramerateLimit(60);

        vector<Transformable*> holder;
        while(app.isOpen()){
            this->app.setView(*this->mainCamera->GetView());
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
                gameobjects[i]->TriggerComponents();
                gameobjects[i]->FindCollision();
                gameobjects[i]->SyncComponents();
                gameobjects[i]->Update();
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