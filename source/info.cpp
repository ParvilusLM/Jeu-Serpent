#include "info.h"

Info::Info(sf::RenderWindow& fenetre):m_fenetre(0)
{
    m_score[0]=0;
    m_score[1]=0;

    m_font1.loadFromFile("donnees/keypunc.ttf");
    m_font2.loadFromFile("donnees/ALGER.ttf");

    m_fenetre=&fenetre;
}

template <class T> std::string Info::nbEnString(T nb)
{
    std::ostringstream chaineCar;
    chaineCar << nb;
    return chaineCar.str();
}

void Info::initInfo()
{
    m_txtScoreJ1.setFont(m_font1);
    m_txtScoreJ1.setCharacterSize(30);
    m_txtScoreJ1.setPosition((largeurF/2)-310,30);
    m_txtScoreJ1.setFillColor(sf::Color::Black);


    m_txtScoreJ2.setFont(m_font1);
    m_txtScoreJ2.setCharacterSize(30);
    m_txtScoreJ2.setPosition((largeurF/2)+260,30);
    m_txtScoreJ2.setFillColor(sf::Color::Black);


    m_txtPause.setFont(m_font2);
    m_txtPause.setCharacterSize(80);
    m_txtPause.setPosition((largeurF/2)-130,(hauteurF/2)-50 );
    m_txtPause.setFillColor(sf::Color::Red);
    m_txtPause.setString("PAUSE");

}

void Info::reinitInfo()
{
    m_score[0]=0;
    m_score[1]=0;


}

void Info::afficheInfo()
{
    indiquerScore();

    m_fenetre->draw(m_txtScoreJ1);
    m_fenetre->draw(m_txtScoreJ2);


}

void Info::indiquerScore()
{
    m_txtScoreJ1.setString(nbEnString(m_score[0]));

    m_txtScoreJ2.setString(nbEnString(m_score[1]));

}

int Info::getScore(int num_joueur)
{
    if(num_joueur==SERPENT_1)
    {
        return m_score[0];
    }
    else
        return m_score[1];
}

void Info::gestionScore(int num_joueur)
{
    if(num_joueur==SERPENT_1)
    {
        m_score[0] +=1;
    }
    else
        m_score[1] +=1;
}


Info::~Info()
{

}

