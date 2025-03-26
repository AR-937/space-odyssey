#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>

struct Star {
    sf::Vector2f pos;    
    float depth;         
    
    [[nodiscard]] sf::Vector2f scaled_pos() const { 
        return pos * (1.0f / depth); 
    }
    
    [[nodiscard]] uint8_t brightness(float near_plane, float inv_depth_range) const {
        float brightness_ratio = 1.0f - (depth - near_plane) * inv_depth_range;
        return static_cast<uint8_t>(brightness_ratio * 255.0f);
    }
};

class Scene : public sf::Drawable {
private:
    std::vector<Star> stars;
    std::unique_ptr<sf::CircleShape> star_shape;
    size_t first_idx = 0;
    
    void draw_stars(unsigned int count, float max_dist);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Scene(unsigned int count, float max_dist, std::optional<float> custom_radius = std::nullopt);
    ~Scene() = default;
    
    void update(float dt, float speed);
    
    void reset(float max_dist);
}; 