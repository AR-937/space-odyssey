#include "scene.h"
#include "config.h"
#include <random>
#include <algorithm>

Scene::Scene(unsigned int count, float max_dist, std::optional<float> custom_radius) {
    const float radius = custom_radius.value_or(config::star_radius);
    
    star_shape = std::make_unique<sf::CircleShape>(radius);
    star_shape->setOrigin(radius, radius);
    
    draw_stars(count, max_dist);
}

void Scene::draw_stars(unsigned int count, float max_dist) {
    stars.clear();
    stars.reserve(count);
    
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> pos_dist(-0.5f, 0.5f);
    std::uniform_real_distribution<float> depth_dist(config::near_plane, config::far_plane);
    
    constexpr float center_factor = 0.5f;
    const float center_size = config::near_plane * center_factor;
    sf::FloatRect center_area(
        -center_size * config::window_width,
        -center_size * config::window_height,
        center_size * config::window_width * 2,
        center_size * config::window_height * 2
    );
    
    for (unsigned int i = 0; i < count; ++i) {
        sf::Vector2f pos(
            pos_dist(rng) * config::window_width * max_dist,
            pos_dist(rng) * config::window_height * max_dist
        );
        
        if (center_area.contains(pos)) {
            --i;
            continue;
        }
        
        stars.emplace_back(Star{pos, depth_dist(rng)});
    }
    
    std::sort(stars.begin(), stars.end(), 
              [](const Star& a, const Star& b) { return a.depth > b.depth; });
    
    first_idx = 0;
}

void Scene::update(float dt, float speed) {
    const float distance = speed * dt;
    
    for (size_t i = 0; i < stars.size(); ++i) {
        stars[i].depth -= distance;
        
        if (stars[i].depth < config::near_plane) {
            stars[i].depth = config::far_plane - (config::near_plane - stars[i].depth);
            first_idx = i;
        }
    }
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (size_t i = 0; i < stars.size(); ++i) {
        const size_t idx = (i + first_idx) % stars.size();
        const Star& star = stars[idx];
        
        const float scale = 1.0f / star.depth;
        const uint8_t color_value = star.brightness(config::near_plane, config::inv_depth_range);
        
        star_shape->setPosition(star.scaled_pos() + config::window_center);
        star_shape->setFillColor(sf::Color(color_value, color_value, color_value));
        star_shape->setScale(scale, scale);
        
        target.draw(*star_shape, states);
    }
}

void Scene::reset(float max_dist) {
    draw_stars(stars.capacity(), max_dist);
} 