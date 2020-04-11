#include <header.hpp>

NeuralNetwork *ptr;

deque<CircleShape> shape;

int red = 235, green = 348, blue = 339;
float m = 0, b = 0;

float mnp(float n, int start1, int stop1, int start2, int stop2) {
    return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

void setup() {
    NeuralNetwork brain = *new NeuralNetwork(3, 3, 2);
    ptr = &brain;
}

void gradientDescent() {
    float learning_rate = 0.01;

    int i = 0;
    while(i < shape.size()) {
        float x = shape[i].getPosition().x,
              y = shape[i].getPosition().y,

              guess = m * x + b,

              error = y - guess;

        m += error / x * learning_rate;
        b += error * learning_rate;

        i++;
    }

}

void drawLine() {
    float x1 = 0, y1 = m * x1 + b,
        x2 = 0, y2 = m * x2 + b;

    x1 = mnp(x1, 0, 1, 0, widthI);
    y1 = mnp(y1, 0, 1, 0, heightI);
    x2 = mnp(x2, 0, 1, widthI, 0);
    y2 = mnp(y2, 0, 1, heightI, 0);

    Vertex vertices[2] = {
            Vertex(Vector2f(x1, y1), Color::White),
            Vertex(Vector2f(x2, y2), Color::White),
    };

    window.draw(vertices, 2, Lines);
}

void mousePressed() {
    Vector2f mousepos = window.mapPixelToCoords(Mouse::getPosition(window));
    float x = mousepos.x, y = mousepos.y;

    CircleShape point;
    point.setRadius(8);
    point.setOutlineColor(Color(255));
    point.setPosition(x, y);

    shape.push_back(point);
}

void itLegal() {
    if (shape.size() > 1) {
        gradientDescent();
        drawLine();
    }
}

void draw() {
    window.clear(Color(red, green, blue));

    int i = 0;
    while(i < shape.size()) {
        window.draw(shape[i]);
        i++;
    }

    thread statements(itLegal);

    statements.join();

    window.display();
}

int main() {

    thread pre(setup);
    pre.join();

    while (window.isOpen()) {
        thread first(setup);
        first.join();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
                mousePressed();
        }

        thread second(draw);
        second.join();
    }

    return 0;
}
