#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char * argv[])
{
    // WINDOW SET-UP
    const int WIN_WIDTH = 1280;
    const int WIN_HEIGHT = 720;

    sf::RenderWindow window(sf::VideoMode({ WIN_WIDTH, WIN_HEIGHT }), "cppaint");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(120);

    // CANVAS SET-UP
    sf::RenderTexture canvas;
    canvas.resize({ WIN_WIDTH, WIN_HEIGHT });
    canvas.clear(sf::Color::Black);

    sf::Sprite sprite(canvas.getTexture());

    // BRUSH SET-UP
    const float DEFAULT_BRUSH_SIZE = 25;

    sf::CircleShape brush_shape(DEFAULT_BRUSH_SIZE);
    brush_shape.setOrigin({ DEFAULT_BRUSH_SIZE, DEFAULT_BRUSH_SIZE });

    sf::Vector2f last_pos;
    bool is_drawing = false;

    const std::vector<sf::Color> colors =
    {
        sf::Color(255, 0,   0),    // RED
        sf::Color(255, 160, 0),    // ORANGE
        sf::Color(255, 255, 0),    // YELLOW
        sf::Color(0,   0,   255),  // GREEN
        sf::Color(0,   255, 0),    // BLUE
        sf::Color(60,  0,   255),  // INDIGO
        sf::Color(255, 0,   255),  // VIOLET
    };

    unsigned int color_index = 0;
    brush_shape.setFillColor(colors[color_index]);

    // MAIN LOOP
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // CLOSING
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            // RESIZING
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::View view(window.getView());
                const sf::Vector2f size(window.getSize().x, window.getSize().y);
                view.setSize(size);
                view.setCenter(size / 2.0f);    // MOVES DOODLE TO TOP LEFT
                window.setView(view);
            }
            // DRAWING
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    is_drawing = true;
                    last_pos = window.mapPixelToCoords({ mouseButtonPressed->position.x, mouseButtonPressed->position.y });
                    brush_shape.setPosition(last_pos);
                    canvas.draw(brush_shape);
                    canvas.display();
                }
            }
            // CONTINUE DRAWING
            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if (is_drawing)
                {
                    const sf::Vector2f new_pos(window.mapPixelToCoords(sf::Vector2i({ mouseMoved->position.x, mouseMoved->position.y })));
                    brush_shape.setPosition(new_pos);

                    canvas.draw(brush_shape);
                    canvas.display();
                }
            }
            // STOP DRAWING + CLEAR
            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                {
                    is_drawing = false;
                }
                if (mouseButtonReleased->button == sf::Mouse::Button::Right)
                {
                    canvas.clear(sf::Color::Black);
                    canvas.display();
                }
            }
            // CHANGING BRUSH COLOR
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->scancode)
                {
                    // RED
                case sf::Keyboard::Scan::Num1:
                    color_index = 0;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // ORANGE
                case sf::Keyboard::Scan::Num2:
                    color_index = 1;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // YELLOW
                case sf::Keyboard::Scan::Num3:
                    color_index = 2;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // GREEN
                case sf::Keyboard::Scan::Num4:
                    color_index = 3;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // BLUE
                case sf::Keyboard::Scan::Num5:
                    color_index = 4;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // INDIGO
                case sf::Keyboard::Scan::Num6:
                    color_index = 5;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // VIOLET
                case sf::Keyboard::Scan::Num7:
                    color_index = 6;
                    brush_shape.setFillColor(colors[color_index]);
                    break;
                    // CLOSE WINDOW SHORTCUT (F8)
                case sf::Keyboard::Scan::F8:
                    window.close();
                }
            }
        }

        window.clear(sf::Color(64, 64, 64));
        window.draw(sprite);
        window.display();
    }

    return 0;
}