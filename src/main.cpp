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
    const int HOVER_ALPHA = 16;

    float brush_size = 25;

    sf::CircleShape brush_shape(brush_size);
    brush_shape.setOrigin({ brush_size, brush_size });

    sf::Vector2f last_pos;
    bool is_drawing = false;

    const std::vector<sf::Color> colors =
    {
        sf::Color(255, 0,   0),    // 0: RED
        sf::Color(255, 160, 0),    // 1: ORANGE
        sf::Color(255, 255, 0),    // 2: YELLOW
        sf::Color(0,   0,   255),  // 3: GREEN
        sf::Color(0,   255, 0),    // 4: BLUE
        sf::Color(60,  0,   255),  // 5: INDIGO
        sf::Color(255, 0,   255),  // 6: VIOLET
        sf::Color(255, 0,   0,   HOVER_ALPHA), // 7:  RED    (HOVER)
        sf::Color(255, 160, 0,   HOVER_ALPHA), // 8:  ORANGE (HOVER)
        sf::Color(255, 255, 0,   HOVER_ALPHA), // 9:  YELLOW (HOVER)
        sf::Color(0,   0,   255, HOVER_ALPHA), // 10: GREEN  (HOVER)
        sf::Color(0,   255, 0,   HOVER_ALPHA), // 11: BLUE   (HOVER)
        sf::Color(60,  0,   255, HOVER_ALPHA), // 12: INDIGO (HOVER)
        sf::Color(255, 0,   255, HOVER_ALPHA), // 13: VIOLET (HOVER)
    };

    const std::vector<std::string> color_names =
    {
        "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "VIOLET"
    };

    unsigned int color_index = 0;
    brush_shape.setFillColor(colors[color_index]);

    // TEXT SET-UP
    sf::Font font_lexend("fonts/Lexend-Regular.ttf");

    sf::Text brush_info(font_lexend);
    brush_info.setCharacterSize(24);
    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);

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
            // WINDOW RESIZING
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
                // CONTINUE DRAWING
                if (is_drawing)
                {
                    const sf::Vector2f new_pos(window.mapPixelToCoords(sf::Vector2i({ mouseMoved->position.x, mouseMoved->position.y })));
                    brush_shape.setPosition(new_pos);

                    canvas.draw(brush_shape);
                    canvas.display();
                }
            }
            // STOP DRAWING + CLEAR + BRUSH RESIZING
            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                switch (mouseButtonReleased->button)
                {
                    // STOP DRAWING
                case sf::Mouse::Button::Left:
                    is_drawing = false;
                    break;
                    // CLEAR
                case sf::Mouse::Button::Right:
                    canvas.clear(sf::Color::Black);
                    canvas.display();
                    break;
                    // INCREASE BRUSH SIZE
                case sf::Mouse::Button::Extra2:
                    brush_size += 2;
                    brush_shape.setRadius(brush_size);
                    brush_shape.setOrigin({ brush_size, brush_size });
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // DECREASE BRUSH SIZE
                case sf::Mouse::Button::Extra1:
                    if (brush_size - 2 <= 1)
                    {
                        brush_size = 1;
                        brush_shape.setRadius(brush_size);
                        brush_shape.setOrigin({ brush_size, brush_size });
                        brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    }
                    else
                    {
                        brush_size -= 2;
                        brush_shape.setRadius(brush_size);
                        brush_shape.setOrigin({ brush_size, brush_size });
                        brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    }
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
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // ORANGE
                case sf::Keyboard::Scan::Num2:
                    color_index = 1;
                    brush_shape.setFillColor(colors[color_index]);
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // YELLOW
                case sf::Keyboard::Scan::Num3:
                    color_index = 2;
                    brush_shape.setFillColor(colors[color_index]);
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // GREEN
                case sf::Keyboard::Scan::Num4:
                    color_index = 3;
                    brush_shape.setFillColor(colors[color_index]);
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // BLUE
                case sf::Keyboard::Scan::Num5:
                    color_index = 4;
                    brush_shape.setFillColor(colors[color_index]);
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // INDIGO
                case sf::Keyboard::Scan::Num6:
                    color_index = 5;
                    brush_shape.setFillColor(colors[color_index]);
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // VIOLET
                case sf::Keyboard::Scan::Num7:
                    color_index = 6;
                    brush_shape.setFillColor(colors[color_index]);
                    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
                    break;
                    // CLOSE WINDOW SHORTCUT (F8)
                case sf::Keyboard::Scan::F8:
                    window.close();
                }
            }
        }

        window.clear(sf::Color(64, 64, 64));
        window.draw(sprite);
        window.draw(brush_info);
        window.display();
    }

    return 0;
}