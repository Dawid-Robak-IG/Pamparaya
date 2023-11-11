#include <iostream>
#include <fstream>
#include "SFMLView.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Object.h"
#include "SFMLController.h"
#include "Weapon.h"
#include "Sword.h"
#include "Bow.h"
#include "Axe.h"
#include "PrepareToPlay.h"
#include "MusicController.h"

/*
 Used sounds:
 https://www.youtube.com/watch?v=BQV5rbBMjCQ <- sword
 https://www.youtube.com/watch?v=JcG_ugrzfHE <- plain hit
 https://www.youtube.com/watch?v=l1XG1rBstSk <- axe
 https://www.youtube.com/watch?v=fm3963W8x2I <- bow
 https://www.youtube.com/watch?v=EQ6npXuftf8 <- walking on grass
 https://www.youtube.com/watch?v=4IJR6enytq0 <- slimy sound

 */

void test_nr_of_use(Sword sword, Bow bow, Axe axe,Pamparaya hero)
{
    std::cout << "SWORD nr of use: " << sword.get_number_of_use() << std::endl;
    std::cout << "BOW nr of use: " << bow.get_number_of_use() << std::endl;
    std::cout << "AXE nr of use: " << axe.get_number_of_use() << std::endl;
    std::cout << "PAMPARAYA nr of use: " << hero.get_nr_of_actions()<< std::endl;
    std::cout<<"__________________________"<<std::endl;
}

int main() {
    srand(time(NULL));
    int win_y=900;
    sf::RenderWindow window(sf::VideoMode(win_y+win_y/3, win_y), "PAMPARAYA",
                            sf::Style::Titlebar | sf::Style::Close); //dodajemy jakie style chcemy by nie mozna
                            // bylo zmieniac wielkosci
//    sf::RenderWindow window(sf::VideoMode(win_y+win_y/3, win_y), "PAMPARAYA");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    PrepareToPlay prepareToPlay;
    int dimension=0;
    MusicController musicController;
    bool reset=true;

    // ekran wyboru wielkosci mapy
    while(window.isOpen() and dimension==0)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type==sf::Event::MouseButtonPressed and event.mouseButton.button==sf::Mouse::Left)
                dimension = prepareToPlay.choose_dimension(event);
        }
        window.clear();
        prepareToPlay.draw_chose_dimensions(window);
        window.display();
        if(musicController.get_status_beginning()!=sf::SoundSource::Playing)
            musicController.play_beginning();
        if(dimension>0)reset = false;
        if(!reset)
        {
            Sword sword(4,5);
            Bow bow(1,2);
            Axe axe(2,2);

            Board board(dimension,dimension,5);
            Pamparaya pamparaya(100,5,board.get_height(),board.get_width(),sword);
            board.occupy(pamparaya.get_position());

            SFMLView view(board,100,pamparaya,window);
            SFMLController controller(board,pamparaya,view,sword,bow,axe);

            //glowna rozgrywka
            while(window.isOpen() and pamparaya.get_health()>0 and !board.Are_Edges_Mountains())
            {
                /*if(win_y!=window.getSize().y)//zmienianie skali przy zmianie wielkosci okna
                {
                    win_y=window.getSize().y;
                    window.setSize(sf::Vector2u(win_y+win_y/3,win_y));
                    view.rescale(window);
                }*/
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if(event.type==sf::Event::KeyPressed)
                        controller.play(event);
                    else if(event.type==sf::Event::MouseButtonPressed and event.mouseButton.button==sf::Mouse::Left)
                        controller.hero_attack(window,event);
                    else if(event.type==sf::Event::MouseButtonPressed and event.mouseButton.button==sf::Mouse::Right)
                        controller.put_mountain(event);
                }
                window.clear();
                view.draw(window,controller.get_turns());
                window.display();
                if(musicController.get_status_gameplay()!=sf::SoundSource::Playing)
                    musicController.play_gameplay();
            }
            //ekran konca gry
            while(window.isOpen() and !reset)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if(event.type==sf::Event::KeyPressed and event.key.code==sf::Keyboard::R)
                    {
                        reset=true;
                        dimension=0;
                    }
                }
                window.clear();
                view.draw_end(window);
                window.display();
                if(pamparaya.get_health()>0)
                {
                    if(musicController.get_status_victory()!=sf::SoundSource::Playing)
                        musicController.play_victory();
                }
                else
                {
                    if(musicController.get_status_defeat()!=sf::SoundSource::Playing)
                        musicController.play_defeat();
                }
            }
        }
    }

    return 0;
}
