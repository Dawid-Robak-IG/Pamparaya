//
// Created by dawid on 09.06.2023.
//

#ifndef PAMPARAYA_MUSICCONTROLLER_H
#define PAMPARAYA_MUSICCONTROLLER_H

/*
 Used music: (by Gareth Coker)
 34-Luma Pools
 51-Escaping the Sandworm
 56-The Spirit Willow
 57-Shriek and Ori
 */
#include <SFML/Audio.hpp>
#include <iostream>

class MusicController {
 sf::Music beginning;
 sf::Music gameplay;
 sf::Music victory;
 sf::Music defeat;
public:
    MusicController();
    void play_beginning();//muzyka poczatkowa wyboru wielk planszy
    void play_gameplay();//muzyka grajaca podczas gry
    void play_victory();
    void play_defeat();

    sf::SoundSource::Status get_status_beginning();
    sf::SoundSource::Status get_status_gameplay();
    sf::SoundSource::Status get_status_victory();
    sf::SoundSource::Status get_status_defeat();
private:
    void reset_all_music();
};


#endif //PAMPARAYA_MUSICCONTROLLER_H

//
//#include <chrono>
//#include <thread>
//using namespace std::literals::chrono_literals;
//
//std::this_thread::sleep_for(std::chrono::milliseconds(buffer_slimy.getDuration().asMilliseconds()));