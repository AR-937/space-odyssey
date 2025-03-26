#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace config {
    constexpr unsigned int window_width = 1920;
    constexpr unsigned int window_height = 1080;
    inline const sf::Vector2f window_center = {
        window_width / 2.0f, 
        window_height / 2.0f
    };
    constexpr unsigned int max_fps = 144;
    
    constexpr unsigned int star_count = 10000;
    constexpr float star_radius = 3.0f;
    
    constexpr float near_plane = 0.1f;
    constexpr float far_plane = 10.0f;
    constexpr float travel_speed = 5.0f;
    
    constexpr float depth_range = far_plane - near_plane;
    constexpr float inv_depth_range = 1.0f / depth_range;
    
    constexpr float fixed_update_time = 1.0f / 60.0f;
} 