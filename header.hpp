#pragma once
enum { widthI = 400, heightI = 400 };

// Includes
#include <iostream>
#include <thread>
#include <deque>
#include <nn.hpp>

// SFML
#include <SFML/Graphics.hpp>

// Namespaces
using namespace std;
using namespace sf;

// Constants
static const float heightF = 400.f, widthF = 400.f;

// Variables
ContextSettings settings(32, 0, 8);
RenderWindow window(VideoMode(widthI, heightI), "Neural Networks", Style::Default, settings);