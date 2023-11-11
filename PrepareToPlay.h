//
// Created by dawid on 31.05.2023.
//

#ifndef PAMPARAYA_PREPARETOPLAY_H
#define PAMPARAYA_PREPARETOPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>

class PrepareToPlay {
    sf::Color LightBlue;
    sf::Color LightPink;

    int font_size;
    int blockYsize;
    int block_scalar;
    std::vector<int> Dimensions;
    sf::Font font;
    sf::Text text;

    std::vector<std::string> instructions;
public:
    PrepareToPlay();
    int choose_dimension(sf::Event &event);
    void draw_chose_dimensions(sf::RenderWindow &win);
private:
    void SetTextParameters();
    void SetIntructions();
    void draw_RecWithoutFilling(sf::RenderWindow &win, int posX, int posY,int lengthX,int lengthY, sf::Color color);
    std::string intToString(int x);
    void draw_instruction(sf::RenderWindow &win);
};


#endif //PAMPARAYA_PREPARETOPLAY_H
