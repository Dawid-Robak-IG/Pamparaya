//
// Created by dawid on 29.04.2023.
//

#ifndef PAMPARAYA_SFMLVIEW_H
#define PAMPARAYA_SFMLVIEW_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pamparaya.h"
//#include "SFMLController.h"
#include "Weapon.h"

struct RectangleInfo{
    int posX; //lewy gorny
    int posY;//lewy gorny
    int width;
    int height;
};

class SFMLView {
    Board &board;
    int side;
    int frame_scalar;

    int font_size;
    sf::Font font;
    sf::Text text;

    int nr_of_intructions; //end i in draw_instruction

    sf::RectangleShape block;
    sf::Texture grass_texture;
    sf::Sprite grass_sprite;

    sf::Texture buffer_block;

    //weapons textures and sprites
    sf::Texture sword_texture;
    sf::Sprite sword_sprite;
    sf::Texture bow_texture;
    sf::Sprite bow_sprite;
    sf::Texture arrow_texture;
    sf::Sprite arrow_sprite;
    sf::Texture axe_texture;
    sf::Sprite axe_sprite;

    Pamparaya &pamparaya;
    float scale;
    //hero textures and sprites
    sf::Texture standing_texture;
    sf::Sprite standing_sprite;
    sf::Texture right_texture;
    sf::Sprite right_sprite;
    sf::Texture left_texture;
    sf::Sprite left_sprite;
    sf::Texture up_texture;
    sf::Sprite up_sprite;
    sf::Texture down_texture;
    sf::Sprite down_sprite;

    //enemies
    sf::Texture gslime_texture;
    sf::Sprite gslime_sprite;
    sf::Texture splotch_up_texture;
    sf::Sprite splotch_up_sprite;
    sf::Texture splotch_down_texture;
    sf::Sprite splotch_down_sprite;
    sf::Texture splotch_left_texture;
    sf::Sprite splotch_left_sprite;
    sf::Texture splotch_right_texture;
    sf::Sprite splotch_right_sprite;

    sf::Texture Pslime_texture;
    sf::Sprite Pslime_sprite;
    sf::Texture spine_upRight_texture;
    sf::Sprite spine_upRight_sprite;
    sf::Texture spine_upLeft_texture;
    sf::Sprite spine_upLeft_sprite;
    sf::Texture spine_downRight_texture;
    sf::Sprite spine_downRight_sprite;
    sf::Texture spine_downLeft_texture;
    sf::Sprite spine_downLeft_sprite;

    //rocks
    sf::Texture rocks_texture;
    sf::Sprite rocks_sprite;
    sf::Texture mountain_texture;
    sf::Sprite mountain_sprite;

    //colors
    sf::Color HPColor;
    sf::Color ActionColor;
    sf::Color DMGColor;
    sf::Color EXPColor;
    sf::Color LightYellow;

    RectangleInfo swordBuff_Rec;
    RectangleInfo axeBuff_Rec;
    RectangleInfo bowBuff_Rec;

public:
    SFMLView(Board &b, int fr_scalar,Pamparaya &Pam,sf::RenderWindow &win);
    void draw(sf::RenderWindow &win, int turns);

    int get_side_value() const;
    int get_frame_scalar() const;
    int GraphicRow_to_on_board(int row);

    int GraphicColumn_to_on_board(int column);
    void draw_choosingBuff(sf::RenderWindow &win, Buff swordBuff, Buff axeBuff, Buff bowBuff);
    void draw_Enemies_Attacks(sf::RenderWindow &win);
    void draw_end(sf::RenderWindow &win);

    RectangleInfo get_swordRec_Info();
    RectangleInfo get_axeRec_Info();
    RectangleInfo get_bowRec_Info();

    void rescale(sf::RenderWindow &win);

private:
    void draw_how_to_play(sf::RenderWindow &win,int turns);
    void draw_hero(sf::RenderWindow &win, int x, int y);
    void draw_weapon(WEAPON weapon_to_draw, sf::RenderWindow &win);
    void draw_bow(sf::RenderWindow &win);
    void draw_arrow(sf::RenderWindow &win, int sight,int range);
    void draw_axe(sf::RenderWindow &win);
    void draw_sword(sf::RenderWindow &win);
    void draw_cross(sf::RenderWindow &win,int x,int y);
    void draw_attackable_area(sf::RenderWindow &win);
    void draw_blockFilling(sf::RenderWindow &win,int row,int column);
    void draw_enemy(sf::RenderWindow &win, int row, int column);
    void draw_RecWithoutFilling(sf::RenderWindow &win, int posX, int posY,int lengthX,int lengthY, sf::Color color);
    void draw_Spine(sf::RenderWindow &win,Point enemyPos);
    void draw_Splotch(sf::RenderWindow &win,Point enemyPos);

    std::string intToString(int x);
    std::string WeaponKindToString(WEAPON weapon);
    int GraphicRow_to_PosY(int row);
    int GraphicCol_to_PosX(int col);

    int get_center_posX_text_after_board(sf::RenderWindow &win);

    void SetTextParameters();
    void SetBlockParameters();
    void SetSpritesTextures();
    void SetHeroSpritesTextures();
    void SetWeaponsSpritesTextures();
    void SetEnemiesSpritesTextures();
    void SetEnemiesAttacksSpirtesTextures();
    void SetRocksTexturesSprites();
};


#endif //PAMPARAYA_SFMLVIEW_H

