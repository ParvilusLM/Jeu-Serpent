#include "decor.h"

Decor::Decor(sf::RenderWindow& fenetre):m_fenetre(0),m_son(0),m_serpent(0),m_info(0),m_menu(0)
{
    m_fenetre=&fenetre;

    m_info=new Info(*m_fenetre);
    m_serpent=new Serpent(*m_fenetre);
    m_son=new Son();
    m_menu=new Menu(*m_fenetre);

    m_t_fondEc.loadFromFile("donnees/fondEc.png");
    m_t_fruit.loadFromFile("donnees/fruit.png");

    m_s_fondEc.setTexture(m_t_fondEc);

    m_s_fruit.setTexture(m_t_fruit);
    m_s_fruit.setOrigin(10.f,10.f);



}

Info& Decor::getInfo()
{
    return *m_info;
}

Serpent& Decor::getSerpent()
{
    return *m_serpent;
}

Son& Decor::getSon()
{
    return *m_son;
}

Menu& Decor::getMenu()
{
    return *m_menu;
}

sf::Vector2f Decor::getPosFruit()
{
    return m_s_fruit.getPosition();
}

void Decor::setPosFruit(sf::Vector2f posF)
{
    m_s_fruit.setPosition(posF);
}

void Decor::afficheFruit()
{
  m_fenetre->draw(m_s_fruit);
}

void Decor::afficheFondEc()
{
    m_fenetre->draw(m_s_fondEc);
}

sf::FloatRect Decor::getBoiteEFruit()
{
    return m_s_fruit.getGlobalBounds();
}

Decor::~Decor()
{
    delete m_son;
    delete m_serpent;
    delete m_menu;
    delete m_info;
}
