#include "controleur.h"

Controleur::Controleur(sf::RenderWindow &fenetre):m_fenetre(0),m_decor(0)
{
    m_fenetre= &fenetre;
    m_decor= new Decor(*m_fenetre);


}

void Controleur::afficheMenu()
{
    m_decor->getMenu().affficheMenu();
}

void Controleur::afficheSerp()
{
    m_decor->getSerpent().afficherSerpent();
}

void Controleur::afficheInfo()
{
    m_decor->getInfo().afficheInfo();
}

void Controleur::afficheJeu()
{
    m_decor->afficheFondEc();
    afficheInfo();
    m_decor->afficheFruit();
    afficheSerp();
}

void Controleur::mouvementSerp()
{
    m_decor->getSerpent().mouvementSerpent(SERPENT_1);
    m_decor->getSerpent().mouvementSerpent(SERPENT_2);

}


void Controleur::changerDirSerp(int no_serp, int dirSerp)
{
    m_decor->getSerpent().setDirectSerp(no_serp,dirSerp);
}

void Controleur::ajouteNPDS(int no_serp)
{
    m_decor->getSerpent().ajouteNPDS(no_serp);
}

void Controleur::ajouteFruit()
{
    bool x_vide=false,y_vide=false;
   int nb_al_x;
   int nb_al_y;
   while(!x_vide && !y_vide)
   {
       nb_al_x=rand()% 33;
       nb_al_y=rand()% 29;

       nb_al_x+=2;
       nb_al_y+=6;


       x_vide=true;
       y_vide=true;


       int comptt=0;
       while(comptt<m_decor->getSerpent().getVectSerpents().size())
       {

           int cmpt=0;
           while(cmpt<m_decor->getSerpent().getVectSerpents().at(comptt).size())
           {
              if(m_decor->getSerpent().getVectSerpents().at(comptt).at(cmpt).el_spr.getPosition().x==(nb_al_x*20)-10)
              {
                  x_vide=false;
              }

              if(m_decor->getSerpent().getVectSerpents().at(comptt).at(cmpt).el_spr.getPosition().y==(nb_al_y*20)-10)
              {
                  y_vide=false;
              }
              cmpt++;
           }

           comptt++;
       }


   }

    sf::Vector2f posiFruit;
    posiFruit.x=(nb_al_x*20)-10;
    posiFruit.y=(nb_al_y*20)-10;
    m_decor->setPosFruit(posiFruit);
}

void Controleur::collisionSerp()
{
    // **collisions sur les bords**//

    //serpent 1
    if(m_decor->getSerpent().getVectSerpents().at(0).at(0).el_spr.getPosition().x < 20.f || m_decor->getSerpent().getVectSerpents().at(0).at(0).el_spr.getPosition().x > 680.f)
    {
        jeuPause=true;
    }

    if(m_decor->getSerpent().getVectSerpents().at(0).at(0).el_spr.getPosition().y < 100.f || m_decor->getSerpent().getVectSerpents().at(0).at(0).el_spr.getPosition().y > 680.f)
    {
        jeuPause=true;
    }

    //serpent 2
    if(m_decor->getSerpent().getVectSerpents().at(1).at(0).el_spr.getPosition().x < 20.f || m_decor->getSerpent().getVectSerpents().at(1).at(0).el_spr.getPosition().x > 680.f)
    {
        jeuPause=true;
    }

    if(m_decor->getSerpent().getVectSerpents().at(1).at(0).el_spr.getPosition().y < 100.f || m_decor->getSerpent().getVectSerpents().at(1).at(0).el_spr.getPosition().y > 680.f)
    {
        jeuPause=true;
    }


    //collisions avec le fruit

    sf::FloatRect boiteE_f=m_decor->getBoiteEFruit();

    int compt=0;
    while(compt<m_decor->getSerpent().getVectSerpents().size())
    {
        sf::FloatRect boiteE_tS=m_decor->getSerpent().getVectSerpents().at(compt).at(0).el_spr.getGlobalBounds();
        if(Collision(boiteE_tS,boiteE_f))
        {
            ajouteNPDS(compt+1);
            m_decor->getSon().jouerSon();
            m_decor->getInfo().gestionScore(compt);
            ajouteFruit();
        }


        compt++;
    }




    //collisions entre serpents et eux memes

    //serpent 1
    int compt2=0;
    while(compt2<m_decor->getSerpent().getVectSerpents().size())
    {
        //collision serpent avec lui meme
        int compt3=0;
        while(compt3<m_decor->getSerpent().getVectSerpents().at(compt2).size())
        {
            if(compt3>0)
            {
                if(m_decor->getSerpent().getVectSerpents().at(compt2).at(0).el_spr.getGlobalBounds() == m_decor->getSerpent().getVectSerpents().at(compt2).at(compt3).el_spr.getGlobalBounds())
                {
                   jeuPause=true;

                }

            }

            compt3++;
        }

        //collision serpent avec un autre
        int serp_opp=0;
        if(compt2==0)
        {
            serp_opp=1;
        }
        else
        {
            serp_opp=0;
        }

        int compt4=0;
        while(compt4<m_decor->getSerpent().getVectSerpents().at(serp_opp).size())
        {
            if(m_decor->getSerpent().getVectSerpents().at(compt2).at(0).el_spr.getGlobalBounds() == m_decor->getSerpent().getVectSerpents().at(serp_opp).at(compt4).el_spr.getGlobalBounds() )
            {
                jeuPause=true;
            }

            compt4++;
        }


        compt2++;
    }

}

bool Controleur::Collision(FloatRect boiteE_obj1,FloatRect boiteE_obj2)
{
   if((boiteE_obj1.left >= boiteE_obj2.left + boiteE_obj2.width)      // trop à droite
	|| (boiteE_obj1.left + boiteE_obj1.width <= boiteE_obj2.left) // trop à gauche
	|| (boiteE_obj1.top >= boiteE_obj2.top + boiteE_obj2.height) // trop en bas
	|| (boiteE_obj1.top + boiteE_obj1.height <= boiteE_obj2.top))  // trop en haut
          return false;
   else
          return true;
}

void Controleur::debutJeu()
{
    jeuEnCours=true;
    m_decor->getInfo().initInfo();
    m_decor->getSerpent().initSerpent();
    ajouteFruit();

}

void Controleur::retourMenu()
{
    m_decor->getMenu().retourMenuP();
}

void Controleur::finJeu()
{
    jeuEnCours=false;
    jeuPause=false;
    m_decor->getMenu().retourMenuP();
}

void Controleur::gestionDplSouris()
{
    m_decor->getMenu().elementActif();
}

void Controleur::gestionSelectionSouris()
{
    m_decor->getMenu().selectionElActif();
}

void Controleur::pauseJeu()
{
    if(jeuPause)
    {
        jeuPause=false;
    }
    else
        jeuPause=true;
}

void Controleur::changerDirSerpIA()
{
    //initialisation du tableau virtuel
    int tableauVirtuel[29][33]={0};
    int compt=0;
    while(compt<m_decor->getSerpent().getVectSerpents().size())
    {
        int compt2=0;
        while(compt2<m_decor->getSerpent().getVectSerpents().at(compt).size())
        {
            int positX=((m_decor->getSerpent().getVectSerpents().at(compt).at(compt2).el_spr.getPosition().x+10)/20)-2;
            int positY=((m_decor->getSerpent().getVectSerpents().at(compt).at(compt2).el_spr.getPosition().y+10)/20)-6;

            if(compt==0 && compt2==0)
            {
                tableauVirtuel[positY][positX]=TETE1;
            }
            else if(compt==1 && compt2==0)
            {
                tableauVirtuel[positY][positX]=TETE2;
            }
            else
            {
                tableauVirtuel[positY][positX]=CORPS;
            }

            compt2++;
        }

        compt++;

    }

    int positX=((m_decor->getPosFruit().x+10)/20)-2;
    int positY=((m_decor->getPosFruit().y+10)/20)-6;

    tableauVirtuel[positY][positX]=FRUIT;

    //**  determiner la direction a suivre   **//

    //determiner s'il y a au moins une case vide pour se deplacer
    bool changDirPossib=false;
    int compt2=0;
    while(compt2<29)
    {
        int compt3=0;
        while(compt3<33)
        {
            if(tableauVirtuel[compt2][compt3]==4)
            {
                if(compt3>0)
                {
                    if(tableauVirtuel[compt2][compt3-1]==VIDE || tableauVirtuel[compt2][compt3-1]==FRUIT)
                    {
                        changDirPossib=true;
                    }
                }

                if(compt2<32)
                {
                    if(tableauVirtuel[compt2][compt3+1]==VIDE || tableauVirtuel[compt2][compt3+1]==FRUIT)
                    {
                        changDirPossib=true;
                    }
                }

                if(compt3>0)
                {
                    if(tableauVirtuel[compt2-1][compt3]==VIDE || tableauVirtuel[compt2-1][compt3]==FRUIT)
                    {
                        changDirPossib=true;
                    }
                }

                if(compt3<28)
                {
                    if(tableauVirtuel[compt2+1][compt3]==VIDE || tableauVirtuel[compt2+1][compt3]==FRUIT)
                    {
                        changDirPossib=true;
                    }

                }
            }
            compt3++;
        }
        compt2++;
    }


    if(changDirPossib)
    {
        //valeur a verifier
        int valAVerif=4;

        //variables pour connaitre le nombre de chemins
        int nChemins=1;
        int nCheminsTerm=0;

        //
        int comptt=0;
        while(comptt<1)
        {

            //boucle dans le tableau virtuel pour trouver valAVerif
            int compt3=0;
            while(compt3<29)
            {
                int compt4=0;
                while(compt4<33)
                {
                    if(tableauVirtuel[compt3][compt4]==valAVerif)
                    {
                        bool dirG=false;
                        bool dirD=false;
                        bool dirH=false;
                        bool dirB=false;


                        bool caseArrivee=false;

                        //condition pour savoir que la direction est valide
                        if(compt4>0) //dirG
                        {
                            if(tableauVirtuel[compt3][compt4-1]==VIDE || tableauVirtuel[compt3][compt4-1]==FRUIT)
                            {
                                if(tableauVirtuel[compt3][compt4-1]==1)
                                {
                                    caseArrivee=true;
                                }
                                dirG=true;
                            }
                        }

                        if(compt4<32) //dirD
                        {
                            if(tableauVirtuel[compt3][compt4+1]==VIDE || tableauVirtuel[compt3][compt4+1]==FRUIT)
                            {
                                if(tableauVirtuel[compt3][compt4+1]==1)
                                {
                                    caseArrivee=true;
                                }
                                dirD=true;
                            }
                        }

                        if(compt3>0) //dirH
                        {
                            if(tableauVirtuel[compt3-1][compt4]==VIDE || tableauVirtuel[compt3-1][compt4]==FRUIT)
                            {
                                if(tableauVirtuel[compt3-1][compt4]==1)
                                {
                                    caseArrivee=true;
                                }
                                dirH=true;
                            }
                        }

                        if(compt3<28) //dirB
                        {
                            if(tableauVirtuel[compt3+1][compt4]==VIDE || tableauVirtuel[compt3+1][compt4]==FRUIT)
                            {
                                if(tableauVirtuel[compt3+1][compt4]==FRUIT)
                                {
                                    caseArrivee=true;
                                }
                                dirB=true;
                            }
                        }

                        //**insertion des direction dans le tableauVirtuel**//

                        if(dirG && !dirD && !dirH && !dirB )
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;
                        }
                        else if(!dirG && dirD && !dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;
                        }
                        else if(!dirG && !dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;

                        }
                        else if(!dirG && !dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                        }
                        else if(dirG && dirD && !dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;


                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;

                            nChemins++;
                        }
                        else if(dirG && !dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;


                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;

                            nChemins++;
                        }
                        else if(dirG && !dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;


                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                            nChemins++;
                        }
                        else if(!dirG && dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;


                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;

                            nChemins++;
                        }
                        else if(!dirG && dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;


                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                            nChemins++;
                        }
                        else if(!dirG && !dirD && dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;


                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                            nChemins++;
                        }
                        else if(dirG && dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;


                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;


                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;

                            nChemins+=2;
                        }
                        else if(dirG && dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;


                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;


                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                            nChemins+=2;
                        }
                        else if(dirG && !dirD && dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4-1]=valAVerif+1;


                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;


                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                            nChemins+=2;
                        }
                        else if(!dirG && dirD && dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            tableauVirtuel[compt3][compt4+1]=valAVerif+1;


                            tableauVirtuel[compt3-1][compt4]=valAVerif+1;


                            tableauVirtuel[compt3+1][compt4]=valAVerif+1;

                            nChemins+=2;
                        }
                        else if(!dirG && !dirD && !dirH && !dirB)
                        {
                            nCheminsTerm++;
                        }
                        else
                        {

                        }

                    }
                    compt4++;
                }
                compt3++;
            }

            if(nChemins==nCheminsTerm)
            {
                comptt++;
            }
            else
            {
                valAVerif++;
            }

        }


        //selection et insertion de la case d'arrivee
        sf::Vector2i positionActuel;
        bool directionG=false;
        bool directionD=false;
        bool directionH=false;
        bool directionB=false;

        positionActuel.x=positY;
        positionActuel.y=positX;


        int valeurActuel=tableauVirtuel[positionActuel.x][positionActuel.y];

        //initialisation du parcours
        int commpt=0;
        while(commpt<1)
        {
            directionG=false;
            directionD=false;
            directionH=false;
            directionB=false;

            if(tableauVirtuel[positionActuel.x][positionActuel.y-1]==valeurActuel-1)
            {
                directionG=true;
            }
            else if(tableauVirtuel[positionActuel.x][positionActuel.y+1]==valeurActuel-1)
            {
                directionD=true;
            }
            else if(tableauVirtuel[positionActuel.x-1][positionActuel.y]==valeurActuel-1)
            {
                directionH=true;
            }
            else
            {
                directionB=true;
            }


            if(directionG)
            {
                valeurActuel--;
                positionActuel.y--;
            }
            else if(directionD)
            {
                valeurActuel--;
                positionActuel.y++;
            }
            else if(directionH)
            {
                valeurActuel--;
                positionActuel.x--;
            }
            else
            {
                valeurActuel--;
                positionActuel.x++;
            }

            if(valeurActuel==4)
            {
                commpt++;
            }

        }

        //determiner la direction a prendre

        if(directionG)
        {
            //std::cout<<"Direction Droite"<<std::endl;
            changerDirSerp(SERPENT_2,Droite);
        }
        else if(directionD)
        {
            //std::cout<<"Direction Gauche"<<std::endl;
            changerDirSerp(SERPENT_2,Gauche);
        }
        else if(directionH)
        {
            //std::cout<<"Direction Bas"<<std::endl;
            changerDirSerp(SERPENT_2,Bas);
        }
        else
        {
            //std::cout<<"Direction Haut"<<std::endl;
            changerDirSerp(SERPENT_2,Haut);
        }

    }

}


Controleur::~Controleur()
{
    delete m_decor;
}



