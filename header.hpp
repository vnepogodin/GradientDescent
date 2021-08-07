#ifndef HEADER_HPP_
#define HEADER_HPP_

enum { widthI = 400, heightI = 400 };

// Includes
#include "nn.hpp"
#include <deque>
#include <iostream>
#include <thread>

// SFML
#include <SFML/Graphics.hpp>

// Constants
static constexpr float heightF = 400.f, widthF = 400.f;
static constexpr double learning_rate = 0.01;
static constexpr std::uint8_t red = 235, green = 92, blue = 83;

// Variables
float m = 0, b = 0;
NeuralNetwork nn;

sf::ContextSettings settings(32, 0, 8);
sf::RenderWindow window(sf::VideoMode(widthI, heightI), "Neural Networks", sf::Style::Default, settings);

static std::deque<sf::CircleShape> shapes;

#endif  // HEADER_HPP_
