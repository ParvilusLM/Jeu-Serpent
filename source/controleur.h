#ifndef DEF_CONTROLEUR
#define DEF_CONTROLEUR

#include "decor.h"

class Controleur
{
public:
    Controleur(sf::RenderWindow &fenetre);
    ~Controleur();

    void afficheMenu();
    void afficheInfo();
    void afficheJeu();
    void afficheSerp();
    void mouvementSerp();
    void changerDirSerp(int no_serp, int dirSerp);
    void changerDirSerpIa();
    void ajouteNPDS(int no_serp);
    void ajouteFruit();
    void collisionSerp();
    bool Collision(FloatRect boiteE_obj1,FloatRect boiteE_obj2);

    void debutJeu();
    void retourMenu();
    void finJeu();
    void gestionDplSouris();
    void gestionSelectionSouris();
    void pauseJeu();



private:
    sf::RenderWindow* m_fenetre;
    Decor* m_decor;


};

#endif // DEF_CONTROLEUR
