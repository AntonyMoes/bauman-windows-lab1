#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>

std::tuple<sf::Color, sf::Vector2u, unsigned int, float>  get_symb_params(sf::Vector2u window_size) {
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_int_distribution<> dis_r(0, 255);
    static std::uniform_int_distribution<> dis_g(0, 255);
    static std::uniform_int_distribution<> dis_b(0, 255);
    static std::uniform_int_distribution<> dis_size(10, 50);
    static std::uniform_real_distribution<> dis_ang(0, 360);
    std::uniform_int_distribution<> dis_x(0, window_size.x);
    std::uniform_int_distribution<> dis_y(0, window_size.y);

    sf::Color color = {sf::Uint8(dis_r(gen)), sf::Uint8(dis_g(gen)), sf::Uint8(dis_b(gen)), 255};
    sf::Vector2u position(dis_x(gen), dis_y(gen));
    unsigned int size = dis_size(gen);
    float angle = dis_ang(gen);

    return std::make_tuple(color, position, size, angle);

}


int main () {
    sf::RenderWindow window(sf::VideoMode(700, 700), "ACID");
    window.setFramerateLimit(60);


    while (true) {
        sf::Event event{};
        //window.pollEvent(event);
        while (window.pollEvent(event)) {
            std::cout << event.type << std::endl;

            if (event.type == sf::Event::Resized) {
                auto view = window.getView();
                sf::Vector2u size = window.getSize();
                view.setSize(size.x, size.y);
                window.setView(view);

                std::cout << "MMM" << std::endl;
            }

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                std::cout << "WOW" << std::endl;
                window.close();
                return 0;
            }
        }

        static bool lmb_is_pressed = false;
        if (window.hasFocus()) {
            if (!lmb_is_pressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                lmb_is_pressed = true;
                std::cout << "ОАМ" << std::endl;

                sf::Text symb;
                symb.setString("@");

                sf::Color color;
                sf::Vector2u position;
                unsigned int size;
                float angle;
                // std::tie(color, position, size, angle) = get_symb_params(window.getSize());

                symb.setColor(color);
                symb.setPosition(position.x, position.y);
                symb.setCharacterSize(size); // in pixels, not points!
                symb.setRotation(angle);

                window.draw(symb);


            } else if (lmb_is_pressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                lmb_is_pressed = false;
            }
        }

        window.display();
        window.clear({64, 224, 208, 255});
    }
}
