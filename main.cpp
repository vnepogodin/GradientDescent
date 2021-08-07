/* g++ -O2 -flto main.cpp -lsfml-system -lsfml-window -lsfml-graphics -pthread */
#include "header.hpp"

static inline float mnp(float n, int start1, int stop1, int start2, int stop2) {
    return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

void setup() {
    nn = NeuralNetwork(2, 4, 1);
    nn.setLearningRate(learning_rate);
}

void gradientDescent() {
    for (const auto& shape : shapes) {
        const float& x = shape.getPosition().x;
        const float& y = shape.getPosition().y;

        const float& guess = m * x + b;
        const float& error = y - guess;

        m += error / x * learning_rate;
        b += error * learning_rate;
    }
}

void drawLine() {
    float x1 = 0, y1 = m * x1 + b,
          x2 = 0, y2 = m * x2 + b;

    x1 = mnp(x1, 0, 1, 0, widthI);
    y1 = mnp(y1, 0, 1, 0, heightI);
    x2 = mnp(x2, 0, 1, widthI, 0);
    y2 = mnp(y2, 0, 1, heightI, 0);

    const sf::Vertex vertices[2] = {
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::White),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::White),
    };

    window.draw(vertices, 2, sf::Lines);
}

void mousePressed() {
    const auto& mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    const double x       = mousepos.x;
    const double y       = mousepos.y;

    sf::CircleShape point;
    point.setRadius(8);
    point.setOutlineColor(sf::Color::White);
    point.setPosition(x, y);

    shapes.push_back(point);
}

void itLegal() {
    if (shapes.size() > 1) {
        gradientDescent();
        drawLine();
    }
}

void draw() {
    window.clear({red, green, blue});

    for (const auto& shape : shapes) {
        window.draw(shape);
    }

    std::thread statements(itLegal);

    statements.join();

    window.display();
}

int main() {

    std::thread pre(setup);
    pre.join();

    while (window.isOpen()) {
        std::thread first(setup);
        first.join();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                mousePressed();
        }

        std::thread second(draw);
        second.join();
    }

    return 0;
}
