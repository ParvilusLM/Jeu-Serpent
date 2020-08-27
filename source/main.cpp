#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "controleur.h"




using namespace sf;


bool jeuEnCours=false;
bool HumvsHum=false;
bool jeuPause=false;
int sourisX=0,sourisY=0;




int main()
{
    srand(time(0));
    RenderWindow fenetre(VideoMode(700,700),"Serpent");
    fenetre.setVerticalSyncEnabled(true);

    Controleur controleurJ(fenetre);

    Clock horloge;
    float timer=0, delai=0.2;



    while(fenetre.isOpen())
    {

        float time = horloge.getElapsedTime().asSeconds();
		horloge.restart();
        timer+=time;

        Event evenement;

        while(fenetre.pollEvent(evenement))
        {
            if(evenement.type==Event::Closed)
            {
                fenetre.close();
                break;
            }

            if(evenement.type==Event::MouseMoved)
            {
                sourisX=evenement.mouseMove.x;
                sourisY=evenement.mouseMove.y;
                if(!jeuEnCours)
                {
                    controleurJ.gestionDplSouris();
                }
            }

            if(evenement.type==Event::MouseButtonPressed && !jeuEnCours)
            {
                  Mouse::Button button = evenement.mouseButton.button;
                  if (button == Mouse::Left) // Bouton gauche
                  {
                      controleurJ.gestionSelectionSouris();

                      if(jeuEnCours)
                      {
                          horloge.restart();
                          controleurJ.debutJeu();

                      }
                  }
            }

            if((evenement.type==Event::KeyPressed )&& (evenement.key.code==Keyboard::Space) && jeuEnCours)
            {
                controleurJ.pauseJeu();
            }

            if((evenement.type==Event::KeyPressed )&& (evenement.key.code==Keyboard::R) && jeuEnCours && !jeuPause)
            {
                controleurJ.finJeu();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)  && jeuEnCours && !jeuPause)
            {
                controleurJ.changerDirSerp(SERPENT_1, Haut);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && jeuEnCours && !jeuPause)
            {
                controleurJ.changerDirSerp(SERPENT_1, Bas);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && jeuEnCours && !jeuPause)
            {
                controleurJ.changerDirSerp(SERPENT_1, Gauche);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && jeuEnCours && !jeuPause)
            {
                controleurJ.changerDirSerp(SERPENT_1, Droite);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && jeuEnCours && !jeuPause && HumvsHum)
            {
                controleurJ.changerDirSerp(SERPENT_2, Haut);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && jeuEnCours && !jeuPause && HumvsHum)
            {
                controleurJ.changerDirSerp(SERPENT_2, Bas);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && jeuEnCours && !jeuPause && HumvsHum)
            {
                controleurJ.changerDirSerp(SERPENT_2, Gauche);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && jeuEnCours && !jeuPause && HumvsHum)
            {
                controleurJ.changerDirSerp(SERPENT_2, Droite);
            }

            if(jeuEnCours && !HumvsHum)
            {

            }

        }

        //gestions des donnnees du jeu

        if(jeuEnCours)
        {


            if(timer>delai && !jeuPause)
            {
                timer=0;
                controleurJ.changerDirSerpIA();
                controleurJ.mouvementSerp();
                controleurJ.collisionSerp();

            }
        }
        else
        {

        }

        //effacement de l'ecran du jeu
        fenetre.clear(Color(12,58,86));

        //affichage des donnees du jeu
        if(jeuEnCours)
        {
            controleurJ.afficheJeu();
        }
        else
        {
            controleurJ.afficheMenu();
        }

        //on affiche tout a l'ecran
        fenetre.display();


    }



    return EXIT_SUCCESS;
}
