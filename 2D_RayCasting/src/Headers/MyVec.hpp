#pragma once
#include <SFML/Graphics.hpp>

template<class T>
sf::Vector2<T> fromAngle(float Angle)
{
	return sf::Vector2<T>(std::cos(Angle), std::sin(Angle));
}

template<class T>
sf::Vector2<T> fromAngle(float Angle, float mag)
{
	return sf::Vector2<T>(mag * std::cos(Angle), mag * std::sin(Angle));
}

template<class T>
inline float getMagnitude(sf::Vector2<T> v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

template<class T>
inline float getAngle(sf::Vector2<T> v)
{
	return std::atan(v.y / v.x);
}

template<class T>
inline sf::Vector2<T> normalize(sf::Vector2<T> v)
{
	float mag = getMagnitude(v);
	if (mag == 0) return { 0, 0 };
	return { T(v.x / mag), T(v.y / mag) };
}
