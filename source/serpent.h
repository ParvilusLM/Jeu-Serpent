#ifndef DEF_SERPENT
#define DEF_SERPENT

#include<SFML/Graphics.hpp>
#include "varG.h"
#include "constantes.h"
#include "enums.h"
#include <iostream>

#include "enums.h"
#include "varG.h"
#include "constantes.h"

class Serpent
{
public:
    Serpent(sf::RenderWindow &fenetre);
    ~Serpent();
    void mouvementSerpent(int no_serp);
    void ajouteNPDS(int no_serp);
    void appliquerTexture();
    void changPosPartPreced(int no_serp);
    void initSerpent();
    std::vector< std::vector<element_serpent> > getVectSerpents();
    void afficherSerpent();
    void setDirectSerp(int no_serp, int dirSerp);





private:
    sf::RenderWindow* m_fenetre;
    float m_mouvX,m_mouvY;
    std::vector<directionSerpent> m_dirSerp;
    std::vector< std::vector<element_serpent> > m_serpent;
    sf::Texture m_t_spritesSerp,m_t_spritesSerp2;


};

#endif // DEF_SERPENT
