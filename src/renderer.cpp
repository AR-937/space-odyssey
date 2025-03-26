#include "renderer.h"
#include "config.h"
#include <iostream>

Renderer::Renderer() : 
    window(sf::VideoMode(config::window_width, config::window_height),
          "Space Odyssey", sf::Style::Fullscreen)
{
    window.setFramerateLimit(config::max_fps);
    window.setMouseCursorVisible(false);
    
    scene = std::make_unique<Scene>(config::star_count, config::far_plane);
}

bool Renderer::handle_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || 
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
            return false;
        }
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            scene->reset(config::far_plane);
        }
    }
    return true;
}

void Renderer::update(float dt) {
    accumulated_time += dt;
    
    while (accumulated_time >= config::fixed_update_time) {
        scene->update(config::fixed_update_time, config::travel_speed);
        accumulated_time -= config::fixed_update_time;
    }
}

void Renderer::run() {
    while (window.isOpen()) {
        handle_events();
        
        const float dt = frame_clock.restart().asSeconds();
        
        update(dt);
        
        fps_update_time += dt;
        frame_count++;
        if (fps_update_time >= 1.0f) {
            const float fps = static_cast<float>(frame_count) / fps_update_time;
            std::cout << "FPS: " << fps << std::endl;
            fps_update_time = 0.0f;
            frame_count = 0;
        }
        
        window.clear();
        window.draw(*scene);
        window.display();
    }
} 