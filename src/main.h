
// CONSTANTS
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

// VARIABLES
sf::Font font_lexend("../../../../fonts/Lexend-Regular.ttf");
sf::Text brush_info(font_lexend);

float brush_size = 25;
sf::CircleShape brush_shape(brush_size);

std::vector<sf::Color> colors =
{
    sf::Color(255, 0,   0),    // 0: RED
    sf::Color(255, 160, 0),    // 1: ORANGE
    sf::Color(255, 255, 0),    // 2: YELLOW
    sf::Color(0,   0,   255),  // 3: GREEN
    sf::Color(0,   255, 0),    // 4: BLUE
    sf::Color(60,  0,   255),  // 5: INDIGO
    sf::Color(255, 0,   255),  // 6: VIOLET
};

std::vector<std::string> color_names =
{
    "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "VIOLET"
};

int color_index = 0;

sf::Vector2f last_pos;
bool is_drawing = false;

// HELPER FUNCTIONS
void updateBrushInfo();

void increaseBrushSize();
void decreaseBrushSize();