#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "scene.h"

class Renderer {
private:
    sf::RenderWindow window;
    std::unique_ptr<Scene> scene;
    sf::Clock frame_clock;
    
    float accumulated_time = 0.0f;
    float fps_update_time = 0.0f;
    int frame_count = 0;
    
    bool handle_events();
    void update(float dt);

public:
    Renderer();
    ~Renderer() = default;
    
    void run();
}; 