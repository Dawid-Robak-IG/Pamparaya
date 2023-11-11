//
// Created by dawid on 31.05.2023.
//

#include "PrepareToPlay.h"

PrepareToPlay::PrepareToPlay()
{
    LightBlue=sf::Color(134, 255, 223);
    LightPink=sf::Color(249,144,255);
    font_size=30;
    block_scalar=4;
    blockYsize=block_scalar*font_size;
    SetTextParameters();
    SetIntructions();
    Dimensions={3,5,10,25}; //boarda
}

void PrepareToPlay::SetTextParameters()
{
    font.loadFromFile("../arial.ttf");
    text.setFont(font);
    text.setCharacterSize(font_size);
    text.setFillColor(LightPink);
    text.setStyle(sf::Text::Bold);
}
void PrepareToPlay::SetIntructions()
{
    instructions.push_back("Move by WASD  |  Change weapon: 1,2,3  |  Attack: Left Mouse Button");
    instructions.push_back("Put Mountain: Right Mouse Button");
    instructions.push_back("Step on the rock or press any button to collect it");
    instructions.push_back("Put mountains on all board edges to win");
    instructions.push_back("Put mountains on all board edges to win");
    instructions.push_back("If you put mountain on mountain, mountain will be destroyed");
}
void PrepareToPlay::draw_RecWithoutFilling(sf::RenderWindow &win, int posX, int posY,int lengthX,int lengthY, sf::Color color)
{
    /*
     Funckja rysuje prostokat bez wypelnienia
     Boki prostokat sa prostokatani z czarnym wypelnieniem o krawedzi jednego piksela
    -posX, posY - okreslaja pozycje lewego gornego wierzcholka
    -lengthX, lengthY - okreslaja wielkosc prostokata
    -color - okresla kolor prostokata
     * */
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);
    line.setOutlineThickness(1);
    line.setOutlineColor(color);

    line.setSize(sf::Vector2f(1,lengthY));
    line.setPosition( posX,posY);
    win.draw(line);

    line.setPosition( posX+lengthX,posY);;
    win.draw(line);

    line.setSize(sf::Vector2f(lengthX,1));
    line.setPosition( posX,posY);;
    win.draw(line);

    line.setPosition( posX,posY+lengthY);;
    win.draw(line);
}
void PrepareToPlay::draw_chose_dimensions(sf::RenderWindow &win)
{
    /*
     * Wyswietla ekran wyboru wielkosci planszy
     * Oraz wywoluje funkcje draw_instruction
     * */
    SetTextParameters();

    font_size=win.getSize().y/(block_scalar*(Dimensions.size()+1) + instructions.size()*2);
    blockYsize=block_scalar*font_size;

    text.setFillColor(LightBlue);
    text.setString("Choose dimensions");
    text.setPosition((win.getSize().x - text.getGlobalBounds().width)/2,0);
    win.draw(text);
    text.setFillColor(LightPink);
    for(int i=1;i<Dimensions.size()+1;i++)
    {
        draw_RecWithoutFilling(win, 0,i*blockYsize, win.getSize().x, blockYsize, LightBlue);
        text.setString(intToString(Dimensions[i-1])+"x"+ intToString(Dimensions[i-1]));
        text.setPosition((win.getSize().x - text.getGlobalBounds().width)/2,
                         blockYsize/2-text.getLocalBounds().height+ i*blockYsize);
        win.draw(text);
    }
    draw_instruction(win);
}
int PrepareToPlay::choose_dimension(sf::Event &event)
{
    /*
     * Funkcja zwraca wartosc wymiaru ktory zostal wybrany na podstawie wspolrzednych myszy
     * Jesli wspolrzedne myszy nie sa na bloku wyboru jakiegokolwiek wymiaru
     * Funkcja zwroci wartosc 0 (czyli wartosc ktora nie ma sensu,a wiec widac ze nie wybrano
     * poprawenj wartosci)
     * */
    for(int i=1;i<Dimensions.size()+1;i++)
    {
        if(event.mouseButton.y<(i+1)*blockYsize and event.mouseButton.y>blockYsize)
            return Dimensions[i-1];
    }
    return 0;
}
void PrepareToPlay::draw_instruction(sf::RenderWindow &win)
{
    /*
     * Funkcja wyswietla instrukcje pod bloczkami wyboru wymiarow planszy
     * */
    int i=0;
    text.setFillColor(sf::Color::White);
    while(i<instructions.size()-1)
    {
        text.setString(instructions[i]);
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,
                         (Dimensions.size()+1)*blockYsize+(i*2)*font_size);
        win.draw(text);
        i++;
    }
    text.setCharacterSize(font_size/2);
    text.setString(instructions[i]);
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,
                     (Dimensions.size()+1)*blockYsize+(i*2)*font_size);
    win.draw(text);
}

std::string PrepareToPlay::intToString(int x)
{
    std::string result;
    char adding;
    if(x<0)
    {
        x*=-1;
        while(x>0)
        {
            adding=x%10 + '0';
            result=adding+result;
            x=x/10;
        }
        return "-"+result;
    }
    if(x==0)return "0";
    while(x>0)
    {
        adding=x%10 + '0';
        result=adding+result;
        x=x/10;
    }
    return result;
}