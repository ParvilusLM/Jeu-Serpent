#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "controleur.h"





using namespace sf;


bool jeuEnCours=false;
bool HumvsHum=false;
bool jeuPause=false;
bool jeuFinPartie=false;
bool jeuDebut=false;
bool jeuRejouer=false;

int sourisX=0,sourisY=0;




int main()
{
    srand(time(0));
    RenderWindow fenetre(VideoMode(700,700),"Serpent");
    fenetre.setFramerateLimit(60);


    Controleur controleurJ(fenetre);

    Clock horloge;
    float timer=0, delai=0.2;

    bool interdictionDpl1=false,interdictionDpl2=false;


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

                if(jeuEnCours && jeuPause)
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

            if(evenement.type==Event::MouseButtonPressed && jeuEnCours && jeuPause)
            {
                  Mouse::Button button = evenement.mouseButton.button;
                  if (button == Mouse::Left) // Bouton gauche
                  {
                      controleurJ.gestionSelectionSouris();
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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)  && jeuEnCours && !jeuPause && !interdictionDpl1)
            {
                controleurJ.changerDirSerp(SERPENT_1, Haut);
                interdictionDpl1=true;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && jeuEnCours && !jeuPause && !interdictionDpl1)
            {
                controleurJ.changerDirSerp(SERPENT_1, Bas);
                interdictionDpl1=true;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && jeuEnCours && !jeuPause && !interdictionDpl1)
            {
                controleurJ.changerDirSerp(SERPENT_1, Gauche);
                interdictionDpl1=true;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && jeuEnCours && !jeuPause && !interdictionDpl1)
            {
                controleurJ.changerDirSerp(SERPENT_1, Droite);
                interdictionDpl1=true;
            }
            else
            {

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && jeuEnCours && !jeuPause && HumvsHum && !interdictionDpl2)
            {
                controleurJ.changerDirSerp(SERPENT_2, Haut);
                interdictionDpl2=true;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && jeuEnCours && !jeuPause && HumvsHum && !interdictionDpl2)
            {
                controleurJ.changerDirSerp(SERPENT_2, Bas);
                interdictionDpl2=true;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && jeuEnCours && !jeuPause && HumvsHum && !interdictionDpl2)
            {
                controleurJ.changerDirSerp(SERPENT_2, Gauche);
                interdictionDpl2=true;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && jeuEnCours && !jeuPause && HumvsHum && !interdictionDpl2)
            {
                controleurJ.changerDirSerp(SERPENT_2, Droite);
                interdictionDpl2=true;
            }
            else
            {

            }

        }

        //gestions des donnnees du jeu

        if(jeuEnCours)
        {


            if(timer>delai && !jeuPause)
            {
                timer=0;

                if(!HumvsHum)
                {
                    controleurJ.changerDirSerpIA();
                }

                controleurJ.gestMajDonnees();

                //controleurJ.mouvementSerp();
                //controleurJ.collisionSerp();

                interdictionDpl1=false;
                interdictionDpl2=false;

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
            if(jeuPause)
            {
                controleurJ.afficheMenu();
            }
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
