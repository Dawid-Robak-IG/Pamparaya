//
// Created by dawid on 09.06.2023.
//

#include "MusicController.h"

MusicController::MusicController()
{
    if(!beginning.openFromFile(("../Sounds/51escaping.ogg")))
    {
        std::cout<<"no music 51escaping found"<<std::endl;
    }
    if(!gameplay.openFromFile(("../Sounds/56spirit.ogg")))
    {
        std::cout<<"no music 56spirit found"<<std::endl;
    }
    if(!victory.openFromFile(("../Sounds/34luma.ogg")))
    {
        std::cout<<"no music 34luma found"<<std::endl;
    }
    if(!defeat.openFromFile(("../Sounds/57schriek.ogg")))
    {
        std::cout<<"no music 57schriek found"<<std::endl;
    }
}
void MusicController::reset_all_music()
{
    /*
     Funckja zatzrymuje kazda muzyke
     * */
    beginning.stop();
    gameplay.stop();
    victory.stop();
    defeat.stop();
}

void MusicController::play_beginning()
{
    reset_all_music();
    beginning.play();
}
void MusicController::play_gameplay()
{
    reset_all_music();
    gameplay.play();
}
void MusicController::play_victory()
{
    reset_all_music();
    victory.play();
}
void MusicController::play_defeat()
{
    reset_all_music();
    defeat.play();
}
sf::SoundSource::Status MusicController::get_status_beginning()
{
    return beginning.getStatus();
}
sf::SoundSource::Status MusicController::get_status_gameplay()
{
    return gameplay.getStatus();
}
sf::SoundSource::Status MusicController::get_status_victory()
{
    return victory.getStatus();
}
sf::SoundSource::Status MusicController::get_status_defeat()
{
    return defeat.getStatus();
}