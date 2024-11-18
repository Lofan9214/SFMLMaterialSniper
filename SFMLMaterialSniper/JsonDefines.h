#pragma once

namespace sf
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector3f, x, y, z)

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y)

}