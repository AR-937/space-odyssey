#pragma once

namespace conf
{
	// window config
	sf::Vector2u const windows_size = { 1920, 1080 };
	sf::Vector2f const windows_size_f = static_cast<sf::Vector2f>(windows_size);
	uint32_t const max_framerate = 144;
	float const dt = 1.0f / static_cast<float>(max_framerate);

	// Star config
	uint32_t const count = 10000;
	float const radius = 7.5f;
	float const far = 10.0f;
	float const near = 0.1f;
	float const speed = 5.0f;
}