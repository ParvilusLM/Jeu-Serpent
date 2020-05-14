#ifndef DEF_DECOR
#define DEF_DECOR

#include "serpent.h"
#include "son.h"
#include "info.h"
#include "menu.h"
#include "enums.h"
#include "varG.h"
#include "constantes.h"

class Decor
{
public:
    Decor(sf::RenderWindow& fenetre);
    ~Decor();

    Info& getInfo();
    Serpent& getSerpent();
    Son& getSon();
    Menu& getMenu();
    void afficheFondEc();
    void afficheFruit();
    sf::Vector2f getPosFruit();
    sf::FloatRect getBoiteEFruit();
    void setPosFruit(sf::Vector2f posF);



private:
    sf::RenderWindow* m_fenetre;
    Serpent* m_serpent;
    Son* m_son;
    Info* m_info;
    Menu* m_menu;

    sf::Texture m_t_fondEc;
    sf::Sprite m_s_fondEc;
    sf::Texture m_t_fruit;
    sf::Sprite m_s_fruit;



};

#endif // DEF_DECOR
