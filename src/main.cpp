#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.h"

int main(int argc, char * argv[])
{
    // WINDOW SET-UP
    sf::RenderWindow window(sf::VideoMode({ WIN_WIDTH, WIN_HEIGHT }), "cppaint");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(120);

    // CANVAS SET-UP
    sf::RenderTexture canvas;
    canvas.resize({ WIN_WIDTH, WIN_HEIGHT });
    canvas.clear(sf::Color::Black);
    sf::Sprite sprite(canvas.getTexture());

    // BRUSH SET-UP
    brush_shape.setOrigin({ brush_size, brush_size });
    brush_shape.setFillColor(colors[color_index]);

    // TEXT SET-UP
    brush_info.setCharacterSize(24);
    updateBrushInfo();

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
                    increaseBrushSize();
                    break;
                    // DECREASE BRUSH SIZE
                case sf::Mouse::Button::Extra1:
                    decreaseBrushSize();
                    break;
                }
            }
            // CHANGING BRUSH COLOR + BRUSH RESIZING
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->scancode)
                {
                    // RED (1)
                case sf::Keyboard::Scan::Num1:
                    color_index = 0;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // ORANGE (2)
                case sf::Keyboard::Scan::Num2:
                    color_index = 1;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // YELLOW (3)
                case sf::Keyboard::Scan::Num3:
                    color_index = 2;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // GREEN (4)
                case sf::Keyboard::Scan::Num4:
                    color_index = 3;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // BLUE (5)
                case sf::Keyboard::Scan::Num5:
                    color_index = 4;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // INDIGO (6)
                case sf::Keyboard::Scan::Num6:
                    color_index = 5;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // VIOLET (7)
                case sf::Keyboard::Scan::Num7:
                    color_index = 6;
                    brush_shape.setFillColor(colors[color_index]);
                    updateBrushInfo();
                    break;
                    // INCREASE SIZE (+)
                case sf::Keyboard::Scan::Equal:
                    increaseBrushSize();
                    break;
                    // DECREASE SIZE (-)
                case sf::Keyboard::Scan::Hyphen:
                    decreaseBrushSize();
                    break;
                    // CLOSE WINDOW SHORTCUT (F8)
                case sf::Keyboard::Scan::F8:
                    window.close();
                    break;
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

void updateBrushInfo()
{
    brush_info.setString("Brush Size: " + std::to_string((int)brush_size) + ", Color: " + color_names[color_index]);
}

void increaseBrushSize()
{
    brush_size += 2;
    brush_shape.setRadius(brush_size);
    brush_shape.setOrigin({ brush_size, brush_size });
    updateBrushInfo();
}

void decreaseBrushSize()
{
    if (brush_size - 2 <= 1)
    {
        brush_size = 1;
        brush_shape.setRadius(brush_size);
        brush_shape.setOrigin({ brush_size, brush_size });
        updateBrushInfo();
    }
    else
    {
        brush_size -= 2;
        brush_shape.setRadius(brush_size);
        brush_shape.setOrigin({ brush_size, brush_size });
        updateBrushInfo();
    }
}