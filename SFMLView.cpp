//
// Created by dawid on 29.04.2023.
//

#include "SFMLView.h"

SFMLView::SFMLView(Board &b, int fr_scalar, Pamparaya &Pam,sf::RenderWindow &win):
        board(b),pamparaya(Pam)
{
    nr_of_intructions=win.getSize().y;
    frame_scalar= fr_scalar;
    buffer_block.loadFromFile("../Grafiki/grass2.png");
    scale=static_cast<float>(win.getSize().y)/
            static_cast<float>(buffer_block.getSize().y*(2*pamparaya.get_sight()+1));
    SetSpritesTextures();

    side=standing_sprite.getGlobalBounds().height;

    SetBlockParameters();
    font_size=20;
    SetTextParameters();

    HPColor=sf::Color(154, 0, 0);
    ActionColor=sf::Color(0,142,109);
    DMGColor=sf::Color(255,26,26);
    EXPColor=sf::Color(9,255,0);
    LightYellow=sf::Color(252,255,127);

    swordBuff_Rec={0,0,0,0};
    bowBuff_Rec={0,0,0,0};
    axeBuff_Rec={0,0,0,0};
}

void SFMLView::SetSpritesTextures()
{
    grass_texture.loadFromFile("../Grafiki/grass2.png");
    grass_sprite.setTexture(grass_texture);
    grass_sprite.scale(scale,scale);

    SetWeaponsSpritesTextures();
    SetHeroSpritesTextures();
    SetEnemiesSpritesTextures();
    SetEnemiesAttacksSpirtesTextures();
    SetRocksTexturesSprites();
}
void SFMLView::SetWeaponsSpritesTextures()
{
    if(!sword_texture.loadFromFile("../Grafiki/miecz.png" ))
        std::cout<<"Blad wczytania pliku miecz.png"<<std::endl;
    sword_sprite.setTexture(sword_texture);
    sword_sprite.scale(scale,scale);

    if(!bow_texture.loadFromFile("../Grafiki/bow_square.png" ))
        std::cout<<"Blad wczytania pliku bow_square.png"<<std::endl;
    bow_sprite.setTexture(bow_texture);
    bow_sprite.scale(scale,scale);

    if(!arrow_texture.loadFromFile("../Grafiki/arrow_square.png" ))
        std::cout<<"Blad wczytania pliku arrow_square.png"<<std::endl;
    arrow_sprite.setTexture(arrow_texture);
    arrow_sprite.scale(scale,scale);

    if(!axe_texture.loadFromFile("../Grafiki/axe2.png"))
        std::cout<<"Blad wczytania pliku axe2.png"<<std::endl;
    axe_sprite.setTexture(axe_texture);
    axe_sprite.scale(scale,scale);
}
void SFMLView::SetHeroSpritesTextures()
{
    if(!standing_texture.loadFromFile("../Grafiki/Pamparaya.png" ) )
        std::cout<<"Blad wczytania pliku Pamparaya.png"<<std::endl;
    standing_sprite.setTexture(standing_texture);
    standing_sprite.scale(scale,scale);

    if(!right_texture.loadFromFile("../Grafiki/PamparayaRekaPrawo.png" ) )
        std::cout<<"Blad wczytania pliku PamparayaRekaPrawo.png"<<std::endl;
    right_sprite.setTexture(right_texture);
    right_sprite.scale(scale,scale);

    if(!left_texture.loadFromFile("../Grafiki/PamparayaRekaLewo.png" ) )
        std::cout<<"Blad wczytania pliku PamparayaRekaLewo.png"<<std::endl;
    left_sprite.setTexture(left_texture);
    left_sprite.scale(scale,scale);

    if(!up_texture.loadFromFile("../Grafiki/PamparayaRekaGora.png" ) )
        std::cout<<"Blad wczytania pliku PamparayaRekaGora.png"<<std::endl;
    up_sprite.setTexture(up_texture);
    up_sprite.scale(scale,scale);

    if(!down_texture.loadFromFile("../Grafiki/PamparayaRekaDol.png" ) )
        std::cout<<"Blad wczytania pliku PamparayaRekaDol.png"<<std::endl;
    down_sprite.setTexture(down_texture);
    down_sprite.scale(scale,scale);
}
void SFMLView::SetTextParameters()
{
    font.loadFromFile("../PR Viking.ttf");
    text.setFont(font);
    text.setCharacterSize(font_size);
    text.setFillColor(sf::Color::White);
}
void SFMLView::SetBlockParameters()
{
    block.setSize(sf::Vector2f(side, side));
    block.setFillColor(sf::Color::Black);
    block.setOutlineColor(sf::Color::White);
    block.setOutlineThickness(side/frame_scalar);
}
void SFMLView::SetEnemiesSpritesTextures()
{
    if(!gslime_texture.loadFromFile("../Grafiki/gslime.png" ) )
        std::cout<<"Blad wczytania pliku gslime.png"<<std::endl;
    gslime_sprite.setTexture(gslime_texture);
    gslime_sprite.scale(scale,scale);

    if(!Pslime_texture.loadFromFile("../Grafiki/purple_slime.png" ) )
        std::cout<<"Blad wczytania pliku purple_slime.png"<<std::endl;
    Pslime_sprite.setTexture(Pslime_texture);
    Pslime_sprite.scale(scale,scale);
}
void SFMLView::SetEnemiesAttacksSpirtesTextures()
{
    if(!splotch_up_texture.loadFromFile("../Grafiki/plamaGora.png" ) )
        std::cout<<"Blad wczytania pliku plamaGora.png"<<std::endl;
    splotch_up_sprite.setTexture(splotch_up_texture);
    splotch_up_sprite.scale(scale,scale);

    if(!splotch_down_texture.loadFromFile("../Grafiki/plamaDol.png" ) )
        std::cout<<"Blad wczytania pliku plamaDol.png"<<std::endl;
    splotch_down_sprite.setTexture(splotch_down_texture);
    splotch_down_sprite.scale(scale,scale);

    if(!splotch_left_texture.loadFromFile("../Grafiki/plamaLewo.png" ) )
        std::cout<<"Blad wczytania pliku plamaLewo.png"<<std::endl;
    splotch_left_sprite.setTexture(splotch_left_texture);
    splotch_left_sprite.scale(scale,scale);

    if(!splotch_right_texture.loadFromFile("../Grafiki/plamaPrawo.png" ) )
        std::cout<<"Blad wczytania pliku plamaPrawo.png"<<std::endl;
    splotch_right_sprite.setTexture(splotch_right_texture);
    splotch_right_sprite.scale(scale,scale);

    if(!spine_upRight_texture.loadFromFile("../Grafiki/KolecPrawyGora.png" ) )
        std::cout<<"Blad wczytania pliku KolecPrawyGora.png"<<std::endl;
    spine_upRight_sprite.setTexture(spine_upRight_texture);
    spine_upRight_sprite.scale(scale,scale);

    if(!spine_upLeft_texture.loadFromFile("../Grafiki/KolecLewyGora.png" ) )
        std::cout<<"Blad wczytania pliku KolecLewyGora.png"<<std::endl;
    spine_upLeft_sprite.setTexture(spine_upLeft_texture);
    spine_upLeft_sprite.scale(scale,scale);

    if(!spine_downRight_texture.loadFromFile("../Grafiki/KolecPrawyDol.png" ) )
        std::cout<<"Blad wczytania pliku KolecPrawyDol.png"<<std::endl;
    spine_downRight_sprite.setTexture(spine_downRight_texture);
    spine_downRight_sprite.scale(scale,scale);

    if(!spine_downLeft_texture.loadFromFile("../Grafiki/KolecLewyDol.png" ) )
        std::cout<<"Blad wczytania pliku KolecLewyDol.png"<<std::endl;
    spine_downLeft_sprite.setTexture(spine_downLeft_texture);
    spine_downLeft_sprite.scale(scale,scale);
}
void SFMLView::SetRocksTexturesSprites()
{
    if(!rocks_texture.loadFromFile("../Grafiki/rocks_normal.png" ) )
        std::cout<<"Blad wczytania pliku rocks_normal.png"<<std::endl;
    rocks_sprite.setTexture(rocks_texture);
    rocks_sprite.scale(scale,scale);

    if(!mountain_texture.loadFromFile("../Grafiki/mountains_normal.png" ) )
        std::cout<<"Blad wczytania pliku gora.png"<<std::endl;
    mountain_sprite.setTexture(mountain_texture);
    mountain_sprite.scale(scale,scale);
}

void SFMLView::draw(sf::RenderWindow &win, int turns)
{
    /*
     Funckja wyswietla obraz glownej gry
     */
    draw_how_to_play(win, turns);
    for(int row=0;row<2*pamparaya.get_sight()+1;row++)
    {
        for(int column=0;column<2*pamparaya.get_sight()+1;column++)
        {
            block.setPosition( side/frame_scalar + column * (side/frame_scalar +side),
                               side/frame_scalar + row * (side/frame_scalar +side));
            win.draw(block);
            draw_blockFilling(win,row,column);
            draw_enemy(win, row, column);
        }
    }
    //std::cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<std::endl;
    draw_attackable_area(win);
    draw_hero(win, GraphicCol_to_PosX(pamparaya.get_sight()),
              GraphicRow_to_PosY(pamparaya.get_sight()));
    draw_weapon(pamparaya.get_choosen_weapon(),win);
    draw_Enemies_Attacks(win);

    /*std::cout<<"_____________________________________________"<<std::endl;
    std::cout<<side/frame_scalar + pamparaya.get_sight() * (side/frame_scalar +side)<<" "
    <<side/frame_scalar + pamparaya.get_sight() * (side/frame_scalar +side)<<std::endl;
    std::cout<<"_____________________________________________"<<std::endl;*/

}
void SFMLView::draw_cross(sf::RenderWindow &win, int x, int y)
{
    /*_______________________________________________________________________
     Funkcja wyswietla krzyzyk oznaczajacy ze nie ma tam pola na ktorym mozna stanac
     x i y w funkcji oznaczaja pozycje umieszczenia krzyzyka na oknie gry
     * */
    sf::RectangleShape line(sf::Vector2f(side+side/2,1));
    line.setFillColor(sf::Color(70,65,85));
    line.setPosition(x,y);
    line.rotate(45);
    win.draw(line);
    line.setPosition(x+side,y);
    line.rotate(90);
    win.draw(line);
}
void SFMLView::draw_attackable_area(sf::RenderWindow &win)
{
    /*_______________________________________________________________________
     Funkcja wyswietla obszar, na ktory mozna kliknac by wykonac akcje
     * */
    std::vector<Point>area=pamparaya.get_useablePoints();//kazda bron ma te same useablePoints
    for(int i=0;i<area.size();i++)
    {
        //side/frame_scalar + (pamparaya.get_sight()+area[i].x) * (side/frame_scalar +side)
        draw_RecWithoutFilling(win, GraphicCol_to_PosX(pamparaya.get_sight() + area[i].x),
                               GraphicRow_to_PosY(pamparaya.get_sight() + area[i].y),
                               side, side,
                               sf::Color(202,4,4));
    }
}
void SFMLView::draw_blockFilling(sf::RenderWindow &win,int row,int column)
{
    /*
     Funkcja wyswietla zawartosc widocznego pola,
     row i column sa rzedami i kolumnami na widoku planszy (ale nie pozycja na oknie!!!)
     * */
    //w granicach planszy
    Point coordinates{GraphicColumn_to_on_board(column), GraphicRow_to_on_board(row)};
    if(board.is_on_board(coordinates))
    {
        if(!board.get_Object(coordinates).get_destroyable()) //gora,bo nie da sie zniszczyc fizycznymi atakami
        {
            mountain_sprite.setPosition(GraphicCol_to_PosX(column),
                                        GraphicRow_to_PosY(row));
            win.draw(mountain_sprite);
        }
        else if(board.get_Object(coordinates).get_health()<=0) //nic tu nie ma
        {
            grass_sprite.setPosition(GraphicCol_to_PosX(column),
                                     GraphicRow_to_PosY(row));
            win.draw(grass_sprite);
        }
        else  //kamien, mozna zniszczyc i ma zycie
        {
            rocks_sprite.setPosition(GraphicCol_to_PosX(column),
                                     GraphicRow_to_PosY(row));
            win.draw(rocks_sprite);
        }
    }
    else //poza zakresem planszy
        draw_cross(win, GraphicCol_to_PosX(column),
                   GraphicRow_to_PosY(row));
}
void SFMLView::draw_how_to_play(sf::RenderWindow &win, int turns)
{
    /*
     Funkcja wyswietla informacje dla gracza:
        -hp
        -bron
        -ilosc akcji
        itp.
     * */
    int end_of_board=side/frame_scalar + (2*pamparaya.get_sight()+1) * (side/frame_scalar +side);
    int i=1;
    font_size= win.getSize().y / nr_of_intructions;


    text.setFillColor(sf::Color::White);
    text.setString("Movement: W A S D");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setString("Number of turns: "+ intToString(turns));
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i+=2;

    text.setString("Weapon:");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(sf::Color(142,138,255));
    text.setString(WeaponKindToString(pamparaya.get_choosen_weapon()));
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(DMGColor);
    text.setString(intToString(pamparaya.get_weapon()->get_dmg()) + " dmg");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(ActionColor);
    text.setString(intToString(pamparaya.get_weapon()->get_current_number_of_use()) + " (to use)");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i+=2;

    text.setFillColor(sf::Color::White);
    text.setString("Pamparaya:");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(ActionColor);
    text.setString(intToString(pamparaya.get_current_nr_actions())+" (actions)");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(HPColor);
    text.setString(intToString(pamparaya.get_health())+" hp");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(sf::Color(112,255,155));
    text.setString(intToString(pamparaya.get_lvl())+" lvl");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i+=2;

    text.setFillColor(EXPColor);
    text.setString("EXP: "+ intToString(pamparaya.get_exp()) + "/"+ intToString(pamparaya.get_exp_tolvlup()));
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    text.setFillColor(sf::Color(179,178,178));
    text.setString("Rocks: "+ intToString(pamparaya.get_picked_rocks())+"/"
                    +intToString(pamparaya.get_rocks_for_mountain()));
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i+=2;

    text.setFillColor(LightYellow);
    text.setString("Column: "+ intToString(pamparaya.get_col()));
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;
    text.setString("Row: "+ intToString(pamparaya.get_row()));
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    win.draw(text);
    i++;

    //________________________________________________________________
    text.setFillColor(sf::Color::White);
    i+=10;

    text.setCharacterSize(font_size-font_size/3);
    text.setString("To change weapon:");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    i++;
    win.draw(text);
    text.setString("1 - Sword, 2 - Bow, 3 - Axe");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    i++;
    win.draw(text);
    text.setString("SKIP -> SPACE");
    text.setPosition(get_center_posX_text_after_board(win),
                     i*font_size);
    i++;
    win.draw(text);
    text.setCharacterSize(font_size);

    nr_of_intructions=i;
}
void SFMLView::draw_hero(sf::RenderWindow &win, int x, int y)
{
    /*
     Funkcja wyswietla bohatera,
     x i y sa rzeczywista pozyjca gdzie bohater ma byc wyswietlony
     * */
    if(pamparaya.get_appearance()==STANDING)
    {
        standing_sprite.setPosition(x, y);
        win.draw(standing_sprite);
    }
    else if(pamparaya.get_appearance()==UP)
    {
        up_sprite.setPosition(x, y);
        win.draw(up_sprite);
    }
    else if(pamparaya.get_appearance()==DOWN)
    {
        down_sprite.setPosition(x, y);
        win.draw(down_sprite);
    }
    else if(pamparaya.get_appearance()==RIGHT)
    {
        right_sprite.setPosition(x, y);
        win.draw(right_sprite);
    }
    else
    {
        left_sprite.setPosition(x, y);
        win.draw(left_sprite);
    }
}
void SFMLView::draw_weapon(WEAPON weapon_to_draw, sf::RenderWindow &win)
{
    /*
     Funkcja wyswietla bron
     weapon_to_draw -> bron ktoy ma byc narysowana
     * */
    if(pamparaya.get_appearance()==STANDING)return;

    if(weapon_to_draw==SWORD)draw_sword(win);
    else if(weapon_to_draw==BOW)draw_bow(win);
    else draw_axe(win);
}
void SFMLView::draw_sword(sf::RenderWindow &win)
{
    int x,y;
    if(pamparaya.get_appearance()==UP)
    {
        x=side/frame_scalar + pamparaya.get_sight() * (side/frame_scalar +side);
        y=side/frame_scalar + (pamparaya.get_sight()-1) * (side/frame_scalar +side);
    }
    else if(pamparaya.get_appearance()==DOWN)
    {
        x=side/frame_scalar + pamparaya.get_sight() * (side/frame_scalar +side);
        y=side/frame_scalar + (pamparaya.get_sight()+1) * (side/frame_scalar +side);
    }
    else if(pamparaya.get_appearance()==RIGHT)
    {
        x=side/frame_scalar + (pamparaya.get_sight()+1) * (side/frame_scalar +side);
        y=side/frame_scalar + pamparaya.get_sight() * (side/frame_scalar +side);
    }
    else //pamparaya.get_appearance()==left
    {
        x=side/frame_scalar + (pamparaya.get_sight()-1) * (side/frame_scalar +side);
        y=side/frame_scalar + pamparaya.get_sight() * (side/frame_scalar +side);
    }
    sword_sprite.setPosition(x,y);
    win.draw(sword_sprite);
}
void SFMLView::draw_bow(sf::RenderWindow &win)
{
    int fitting_scalar=5;
    if(pamparaya.get_appearance()==UP)
    {
        bow_sprite.setRotation(270);
        bow_sprite.setPosition(up_sprite.getPosition().x,
                               up_sprite.getPosition().y+side-up_sprite.getGlobalBounds().height/fitting_scalar);
    }
    else if(pamparaya.get_appearance()==DOWN)
    {
        bow_sprite.setRotation(90);
        bow_sprite.setPosition(down_sprite.getPosition().x+side,
                               down_sprite.getPosition().y + down_sprite.getGlobalBounds().height/fitting_scalar);
    }
    else if(pamparaya.get_appearance()==RIGHT)
    {
        bow_sprite.setRotation(0);
        bow_sprite.setPosition(right_sprite.getPosition().x + right_sprite.getGlobalBounds().width/fitting_scalar,
                               right_sprite.getPosition().y);
    }
    else //pamparaya.get_appearance()==left
    {
        bow_sprite.setRotation(180);
        bow_sprite.setPosition(left_sprite.getPosition().x + side - left_sprite.getGlobalBounds().width/fitting_scalar,
                               left_sprite.getPosition().y + side);
    }
    win.draw(bow_sprite);
    draw_arrow(win,pamparaya.get_sight(),pamparaya.get_weapon()->get_range());
}
void SFMLView::draw_arrow(sf::RenderWindow &win, int sight, int range)
{
    int i=1;
    while(i<=sight and i<=pamparaya.get_weapon()->get_range())
    {
        if (pamparaya.get_appearance() == UP)
        {
            arrow_sprite.setRotation(270);
            arrow_sprite.setPosition(up_sprite.getPosition().x,
                                     up_sprite.getPosition().y -i*side +side);
        }
        else if (pamparaya.get_appearance() == DOWN)
        {
            arrow_sprite.setRotation(90);
            arrow_sprite.setPosition(down_sprite.getPosition().x +side,
                                     down_sprite.getPosition().y + i*side);
        }
        else if (pamparaya.get_appearance() == RIGHT)
        {
            arrow_sprite.setRotation(0);
                arrow_sprite.setPosition(right_sprite.getPosition().x +i*side,
                                         right_sprite.getPosition().y);
        }
        else //pamparaya.get_appearance()==left
        {
            arrow_sprite.setRotation(180);
            arrow_sprite.setPosition(left_sprite.getPosition().x -i*side +side,
                                     left_sprite.getPosition().y + side);
    }
    win.draw(arrow_sprite);
    i++;
    }
}
void SFMLView::draw_axe(sf::RenderWindow &win)
{
    if(pamparaya.get_appearance()==UP)
    {
        axe_sprite.setRotation(0);
        axe_sprite.setPosition(up_sprite.getPosition().x-side,
                               up_sprite.getPosition().y-side);
    }
    else if(pamparaya.get_appearance()==DOWN)
    {
        axe_sprite.setRotation(180);
        axe_sprite.setPosition(down_sprite.getPosition().x+axe_sprite.getGlobalBounds().width - side,
                               down_sprite.getPosition().y+axe_sprite.getGlobalBounds().height);
    }
    else if(pamparaya.get_appearance()==RIGHT)
    {
        axe_sprite.setRotation(90);
        axe_sprite.setPosition(right_sprite.getPosition().x+axe_sprite.getGlobalBounds().width,
                               right_sprite.getPosition().y - side);
    }
    else //pamparaya.get_appearance()==left
    {
        axe_sprite.setRotation(270);
        axe_sprite.setPosition(left_sprite.getPosition().x -axe_sprite.getGlobalBounds().width + side ,
                               left_sprite.getPosition().y + axe_sprite.getGlobalBounds().height - side);
    }
    win.draw(axe_sprite);
}
void SFMLView::draw_enemy(sf::RenderWindow &win, int row, int column)
{
    /*
     Funkcja wyswietla przeciwnika na podanym polu
     row i column sa rzedami i kolumnami na widoku planszy (ale nie pozycja na oknie!!!)
     * */
    int row_true= GraphicRow_to_on_board(row);//potrzebuje row i column jakie sa na bordzie
    int column_true= GraphicColumn_to_on_board(column);// a nie graficzne
    text.setCharacterSize(grass_sprite.getGlobalBounds().width/5);

    if(!board.is_on_board({column_true,row_true}) or !board.isFieldOccupied(column_true,row_true))
        return;

    for(int i=0;i<board.get_nr_of_enemies();i++)
    {
        if (board.get_enemy_position(i).x == column_true and board.get_enemy_position(i).y == row_true)
        {
            int x = GraphicCol_to_PosX(column);
            int y = GraphicRow_to_PosY(row);
            //std::cout<<"WESZLISMY"<<std::endl;
            text.setFillColor(sf::Color::Blue);
            text.setPosition(x,y);
            text.setString(intToString(board.get_enemy_hp(i)));
            win.draw(text);
            if (board.get_type(i) == GREEN_SLIME)
            {
                gslime_sprite.setPosition(x, y);
                win.draw(gslime_sprite);
                return; //znalezlismy i narysowalismy tego przeciwnika ktory znajduje sie na polu
            }
            else if(board.get_type(i)== PURPLE_SLIME)
            {
                Pslime_sprite.setPosition(x,y);
                win.draw(Pslime_sprite);
                return;
            }
        }
    }
}
void SFMLView::draw_choosingBuff(sf::RenderWindow &win, Buff swordBuff, Buff axeBuff, Buff bowBuff)
{
    /*
     Funkcja wyswietla ekran wyboru ulepszenia
      Buff swordBuff, Buff axeBuff, Buff bowBuff -> ulepszenia do wyswietlenia
     * */
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color(139,255,147));
    int relative_pos_to_font=3; // o iletrzeba mnozyc font size przy pozycji
    int rec_height_multiplier=4; //to mnozymy przez wielkosc czcionki i mamy wys prostokata
    int weapon_rec_posY=relative_pos_to_font*font_size;

    text.setString("Choose your buff:");
    text.setCharacterSize(font_size*relative_pos_to_font);
    relative_pos_to_font++;
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,0);
    win.draw(text);

    text.setFillColor(sf::Color(255,129,248));
    text.setCharacterSize(font_size);

    //sword buff ____________________________________________________________________________________
    weapon_rec_posY=relative_pos_to_font*font_size;
    text.setString("SWORD");
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);

    text.setString(swordBuff.message + intToString(swordBuff.value));
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);

    swordBuff_Rec.width=text.getGlobalBounds().width + text.getGlobalBounds().width/5;
    swordBuff_Rec.height=rec_height_multiplier*text.getGlobalBounds().height;
    swordBuff_Rec.posX=text.getPosition().x-text.getGlobalBounds().width/10;
    swordBuff_Rec.posY=weapon_rec_posY;
    draw_RecWithoutFilling(win,swordBuff_Rec.posX,
                           swordBuff_Rec.posY,swordBuff_Rec.width ,
                           swordBuff_Rec.height,sf::Color(104,139,255));


    text.setString("Action change: " + intToString(swordBuff.actions_value));
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);
    //______________________________________________________________________________________________________
    relative_pos_to_font+=2;
    //axe buff ____________________________________________________________________________________________
    weapon_rec_posY=relative_pos_to_font*font_size;
    text.setString("AXE");
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);

    text.setString(axeBuff.message + intToString(axeBuff.value));
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);

    axeBuff_Rec.width=text.getGlobalBounds().width + text.getGlobalBounds().width/5;
    axeBuff_Rec.height=rec_height_multiplier*text.getGlobalBounds().height;
    axeBuff_Rec.posX=text.getPosition().x-text.getGlobalBounds().width/10;
    axeBuff_Rec.posY=weapon_rec_posY;
    draw_RecWithoutFilling(win,axeBuff_Rec.posX,
                           axeBuff_Rec.posY,axeBuff_Rec.width ,
                           axeBuff_Rec.height,sf::Color(104,139,255));

    text.setString("Action change: " + intToString(axeBuff.actions_value));
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);
    //_________________________________________________________________________________________________________
    relative_pos_to_font+=2;
    //bow buff ______________________________________________________________________________________________
    weapon_rec_posY=relative_pos_to_font*font_size;
    text.setString("BOW");
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);

    text.setString(bowBuff.message + intToString(bowBuff.value));
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);

    bowBuff_Rec.width=text.getGlobalBounds().width + text.getGlobalBounds().width/5;
    bowBuff_Rec.height=rec_height_multiplier*text.getGlobalBounds().height;
    bowBuff_Rec.posX=text.getPosition().x-text.getGlobalBounds().width/10;
    bowBuff_Rec.posY=weapon_rec_posY;
    draw_RecWithoutFilling(win,bowBuff_Rec.posX,
                           bowBuff_Rec.posY,bowBuff_Rec.width ,
                           bowBuff_Rec.height,sf::Color(104,139,255));

    text.setString("Action change: " + intToString(bowBuff.actions_value));
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,relative_pos_to_font*font_size);
    relative_pos_to_font++;
    win.draw(text);
    //___________________________________________________________________________________________________________

}
void SFMLView::draw_RecWithoutFilling(sf::RenderWindow &win, int posX, int posY,int lengthX,int lengthY, sf::Color color)
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
void SFMLView::draw_Enemies_Attacks(sf::RenderWindow &win)
{
    /*
     Funkcja wyswietla wszysktie ataki jakie zostaly zadane bohaterowie w danej duze
     (ale tylko w momencie gdy po ataku zadna akcja nie zostala wykonana)
     * */
    if(pamparaya.get_nr_of_actions()!=pamparaya.get_current_nr_actions())return; //bohater wykonal ruch - nie interesuje
    //nas juz co go zaatakowalo wiec nic nie wyswietlamy
    std::vector<attackingInfo> enemies_attacks=board.get_enemies_attacks();
    for(int i=0; i < enemies_attacks.size(); i++)
    {
        if(enemies_attacks[i].type == PURPLE_SLIME) draw_Spine(win, enemies_attacks[i].enemy_pos);
        else if(enemies_attacks[i].type == GREEN_SLIME) draw_Splotch(win, enemies_attacks[i].enemy_pos);
    }
}
void SFMLView::draw_Spine(sf::RenderWindow &win,Point enemyPos)
{
    /*
     Funkcja wyswietla kolec na danej pozycji bohatera
     enemyPos jest rzeczystymi wspolrzednymi wroga na boardzie (nie na widoku ani nie pozycji w oknie!!!)
     funkcja wyswietla spine w miejscu gdzie znajduje sie sprite bohatera standing,
     a wiec nalezy pamietac by w przypadku gdy wywolujemy ta funkcje bohater byl wlasnie w tej pozie
     jesli chcemy prawidlowo wyswietlic spine na bohaterze
     * */
    if(enemyPos.x>pamparaya.get_col() and enemyPos.y<pamparaya.get_row())
    {
        spine_downLeft_sprite.setPosition(standing_sprite.getPosition());
        win.draw(spine_downLeft_sprite);
    }
    else if(enemyPos.x>pamparaya.get_col() and enemyPos.y>pamparaya.get_row())
    {
        spine_upLeft_sprite.setPosition(standing_sprite.getPosition());
        win.draw(spine_upLeft_sprite);
    }
    else if(enemyPos.x<pamparaya.get_col() and enemyPos.y<pamparaya.get_row())
    {
        spine_downRight_sprite.setPosition(standing_sprite.getPosition());
        win.draw(spine_downRight_sprite);
    }
    else if(enemyPos.x<pamparaya.get_col() and enemyPos.y>pamparaya.get_row())
    {
        spine_upRight_sprite.setPosition(standing_sprite.getPosition());
        win.draw(spine_upRight_sprite);
    }
}
void SFMLView::draw_Splotch(sf::RenderWindow &win, Point enemyPos)
{
    /*
     Funkcja wyswietla plame na danej pozycji bohatera
     enemyPos jest rzeczystymi wspolrzednymi wroga na boardzie (nie na widoku ani nie pozycji w oknie!!!)
     funkcja wyswietla spine w miejscu gdzie znajduje sie sprite bohatera standing,
     a wiec nalezy pamietac by w przypadku gdy wywolujemy ta funkcje bohater byl wlasnie w tej pozie
     jesli chcemy prawidlowo wyswietlic spine na bohaterze
     * */
    if(enemyPos.x>pamparaya.get_col() and enemyPos.y==pamparaya.get_row())
    {
        splotch_left_sprite.setPosition(standing_sprite.getPosition());
        win.draw(splotch_left_sprite);
    }
    else if(enemyPos.x<pamparaya.get_col() and enemyPos.y==pamparaya.get_row())
    {
        splotch_right_sprite.setPosition(standing_sprite.getPosition());
        win.draw(splotch_right_sprite);
    }
    else if(enemyPos.y<pamparaya.get_row() and enemyPos.x==pamparaya.get_col())
    {
        splotch_down_sprite.setPosition(standing_sprite.getPosition());
        win.draw(splotch_down_sprite);
    }
    else if(enemyPos.y>pamparaya.get_row() and enemyPos.x==pamparaya.get_col())
    {
        splotch_up_sprite.setPosition(standing_sprite.getPosition());
        win.draw(splotch_up_sprite);
    }
}
void SFMLView::draw_end(sf::RenderWindow &win)
{
    /*
     Funkcja wyswietla ekran konca gry, ekran rozni sie w zaleznosci od tego
     czy wygrano czy tez nie
     * */
    int current_font_size=win.getSize().y/5;
    text.setCharacterSize(current_font_size);
    if(pamparaya.get_health()<=0)
    {
        text.setFillColor(DMGColor);
        text.setString("LOST");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,0);
        win.draw(text);

        text.setFillColor(ActionColor);
        text.setCharacterSize(current_font_size/2);

        text.setString("Pampraya is defeated");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2 ,win.getSize().y/3);
        win.draw(text);
        text.setString(" He has lost all his lands");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,text.getPosition().y+text.getCharacterSize());
        win.draw(text);
    }
    else if(board.Are_Edges_Mountains())
    {
        text.setFillColor(EXPColor);
        text.setString("VICTORY");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,0);
        win.draw(text);

        text.setFillColor(ActionColor);
        text.setCharacterSize(current_font_size/3);

        text.setString("Pamparaya has secured his lands");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,win.getSize().y/3);
        win.draw(text);
        text.setString("from upcoming invasions");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,text.getPosition().y+text.getCharacterSize());
        win.draw(text);
        text.setString("once and for all");
        text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,text.getPosition().y+2*text.getCharacterSize());
        win.draw(text);
    }

    text.setString("R -> RESET");
    text.setPosition((win.getSize().x-text.getGlobalBounds().width)/2,win.getSize().y-current_font_size);
    win.draw(text);

}

std::string SFMLView::intToString(int x)
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
std::string SFMLView::WeaponKindToString(WEAPON weapon)
{
    /*
     Funkcja w przypadku przypadku nie znalezienia odpowiedniego odpowiednika string do broni
     zwroci odpowiednik dla miecza
     * */
    if(weapon==BOW)return "Bow";
    if(weapon==AXE)return "Axe";
    return "Sword";
}
int SFMLView::GraphicRow_to_PosY(int row)
{
    /*
     Funkcja zamieni row widoku planszy na pozycje Y ktora mozna nadac obrazkowi na planszy
     wspolrzedne row widoku --> pozycja Y na oknie
     * */
    return side/frame_scalar + row * (side/frame_scalar +side);
}
int SFMLView::GraphicCol_to_PosX(int col)
{
    /*
     Funkcja zamieni column widoku planszy na pozycje X ktora mozna nadac obrazkowi na planszy
     wspolrzedne col widoku --> pozycja X na oknie
     * */
    return side/frame_scalar + col * (side/frame_scalar +side);
}
int SFMLView::GraphicRow_to_on_board(int row)
{
    /*
     Funkcja zamieni row widoku planszy na row na boardzie
     wspolrzedne row widoku --> wspolrzedne row na boardzie
     * */
    return pamparaya.get_row()-pamparaya.get_sight()+row;
}
int SFMLView::GraphicColumn_to_on_board(int column)
{
    /*
     Funkcja zamieni column widoku planszy na column na boardzie
     wspolrzedne col widoku --> wspolrzedne col na boardzie
     * */
    return pamparaya.get_col()-pamparaya.get_sight()+column;
}
int SFMLView::get_center_posX_text_after_board(sf::RenderWindow &win)
{
    /*
     * Zwraca pozycje X jaka powinien przyjac aktualny text aby zostac wysrodkowany
     * na X'ie w obszarze po prawej od wyswietlonej planszy gry
     * */
    int end_of_board=side/frame_scalar + (2*pamparaya.get_sight()+1) * (side/frame_scalar +side);
    return end_of_board+(win.getSize().x-end_of_board-text.getGlobalBounds().width)/2;
}
int SFMLView::get_side_value() const
{
    return side;
}

int SFMLView::get_frame_scalar() const
{
    return frame_scalar;
}
RectangleInfo SFMLView::get_swordRec_Info()
{
    return swordBuff_Rec;
}
RectangleInfo SFMLView::get_axeRec_Info()
{
    return axeBuff_Rec;
}
RectangleInfo SFMLView::get_bowRec_Info()
{
    return bowBuff_Rec;
}

void SFMLView::rescale(sf::RenderWindow &win)
{
    scale=static_cast<float>(win.getSize().y)/
                static_cast<float>(buffer_block.getSize().y*(2*pamparaya.get_sight()+1));

    grass_sprite.setScale(scale,scale);


    //weapons textures and sprites;
    sword_sprite.setScale(scale,scale);
    bow_sprite.setScale(scale,scale);
    arrow_sprite.setScale(scale,scale);
    axe_sprite.setScale(scale,scale);

    //hero textures and sprites
    standing_sprite.setScale(scale,scale);
    right_sprite.setScale(scale,scale);
    left_sprite.setScale(scale,scale);
    up_sprite.setScale(scale,scale);
    down_sprite.setScale(scale,scale);

    //enemies
    gslime_sprite.setScale(scale,scale);
    splotch_up_sprite.setScale(scale,scale);
    splotch_down_sprite.setScale(scale,scale);;
    splotch_left_sprite.setScale(scale,scale);
    splotch_right_sprite.setScale(scale,scale);

    Pslime_sprite.setScale(scale,scale);
    spine_upRight_sprite.setScale(scale,scale);
    spine_upLeft_sprite.setScale(scale,scale);
    spine_downRight_sprite.setScale(scale,scale);
    spine_downLeft_sprite.setScale(scale,scale);

    //rocks
    rocks_sprite.setScale(scale,scale);
    mountain_sprite.setScale(scale,scale);

    side=standing_sprite.getGlobalBounds().height;

}