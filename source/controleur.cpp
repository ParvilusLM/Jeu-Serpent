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
            ajouteFruit();
            ajouteNPDS(compt+1);
            m_decor->getSon().jouerSon();
            m_decor->getInfo().gestionScore(compt);
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
    // vecteur representant l'ensemble des cases des differents chemins
    std::vector<CaseValable> eChemin;

    //vecteur pour stocker les cases a tester
    std::vector<CaseValable> eCasesATester;

    //vector pour le chemin choisi
    std::vector<CaseValable> eCaseChemChoisi;

    //initialisation du tableau virtuel
    int tableauVirtuel[29][33]={0};
    int compt=0;
    while(compt<m_decor->getSerpent().getVectSerpents().size())
    {
        int compt2=0;
        while(compt2<m_decor->getSerpent().getVectSerpents().at(compt).size())
        {
            int positX=m_decor->getSerpent().getVectSerpents().at(compt).at(compt2).el_spr.getPosition().x/20.f;
            int positY=m_decor->getSerpent().getVectSerpents().at(compt).at(compt2).el_spr.getPosition().y/20.f;

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

    int positX=m_decor->getPosFruit().x/20.f;
    int positY=m_decor->getPosFruit().y/20.f;

    tableauVirtuel[positX][positY]=FRUIT;

    //affiche le tableau virtuel
    int cmpt=0;

    while(cmpt<29)
    {
        int cmpt2=0;
        while(cmpt2<33)
        {
            std::cout<<tableauVirtuel[cmpt][cmpt2]<<"  ";

            cmpt2++;
        }
        std::cout<<"\n";
        cmpt++;
    }

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
                if(compt2>0)
                {
                    if(tableauVirtuel[compt2-1][compt3]==4)
                    {
                        changDirPossib=true;
                    }
                }

                if(compt2<32)
                {
                    if(tableauVirtuel[compt2+1][compt3]==4)
                    {
                        changDirPossib=true;
                    }
                }

                if(compt3>0)
                {
                    if(tableauVirtuel[compt2][compt3-1]==4)
                    {
                        changDirPossib=true;
                    }
                }

                if(compt3<28)
                {
                    if(tableauVirtuel[compt2][compt3+1]==4)
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
        int nChemins=0;
        int nCheminsTerm=0;

        //
        int comptt=0;
        while(comptt<1)
        {
            if(valAVerif==4)
            {
                CaseValable elCase;
                elCase.valeur_chemin=4;

                int comp=0;
                while(comp<29)
                {
                    int comp2=0;
                    while(comp2<33)
                    {
                        if(tableauVirtuel[comp][comp2]==4)
                        {
                            elCase.positionX=comp2;
                            elCase.positionY=comp;
                        }
                        comp2++;
                    }
                    comp++;
                }

                elCase.lien_ch_precd=0;
                elCase.num_chem=4;
                eChemin.insert(eChemin.end(),elCase);
            }

            int noChemin=0; //pour savoir le nombre de cases a tester

            //initialisation de la variable noChemin
            int cmptt=0;
            while(cmptt<29)
            {
                int cmptt2=0;
                while(cmptt2<33)
                {
                    if(tableauVirtuel[cmptt][cmptt2]==valAVerif)
                    {
                        noChemin++;
                    }
                    cmptt2++;
                }
                cmptt++;
            }

            //stockage des cases dans le eCasesATester
            eCasesATester.clear();
            int dernEl=eChemin.size()-1;
            int pseudoNoChem=noChemin;

            int cmp=0;
            while(cmp<noChemin)
            {
                int indicEl=pseudoNoChem-1;
                eCasesATester.insert(eCasesATester.end(),eChemin.at(dernEl-indicEl));
                pseudoNoChem--;
                cmp++;
            }

            int pseudoCompt=0;
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
                            if(tableauVirtuel[compt3][compt4-1]==0 || tableauVirtuel[compt3][compt4-1]==1)
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
                            if(tableauVirtuel[compt3][compt4+1]==0 || tableauVirtuel[compt3][compt4+1]==1)
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
                            if(tableauVirtuel[compt3-1][compt4]==0 || tableauVirtuel[compt3-1][compt4]==1)
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
                            if(tableauVirtuel[compt3+1][compt4]==0 || tableauVirtuel[compt3+1][compt4]==1)
                            {
                                if(tableauVirtuel[compt3+1][compt4]==1)
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
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                        }
                        else if(!dirG && dirD && !dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,1);
                        }
                        else if(!dirG && !dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,2);
                        }
                        else if(!dirG && !dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,3);
                        }
                        else if(dirG && dirD && !dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,1);
                            nChemins++;
                        }
                        else if(dirG && !dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,2);
                            nChemins++;
                        }
                        else if(dirG && !dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,3);
                            nChemins++;
                        }
                        else if(!dirG && dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,1);
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,2);
                            nChemins++;
                        }
                        else if(!dirG && dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,1);
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,3);
                            nChemins++;
                        }
                        else if(!dirG && !dirD && dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,2);
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,3);
                            nChemins++;
                        }
                        else if(dirG && dirD && dirH && !dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,1);
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+2,2);
                            nChemins+=2;
                        }
                        else if(dirG && dirD && !dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,1);
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+2,3);
                            nChemins+=2;
                        }
                        else if(dirG && !dirD && dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }
                            insertionCase(eChemin,compt4-1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,0);
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,2);
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+2,3);
                            nChemins+=2;
                        }
                        else if(!dirG && dirD && dirH && dirB)
                        {
                            if(caseArrivee)
                            {
                                comptt++;
                            }

                            insertionCase(eChemin,compt4+1,compt3,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem,1);
                            insertionCase(eChemin,compt4,compt3-1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+1,2);
                            insertionCase(eChemin,compt4,compt3+1,valAVerif+1,eCasesATester.at(pseudoCompt).num_chem,eCasesATester.at(pseudoCompt).num_chem+2,3);
                            nChemins+=2;
                        }
                        else if(!dirG && !dirD && !dirH && !dirB)
                        {
                            nCheminsTerm++;
                        }
                        else
                        {

                        }

                        pseudoCompt++;

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

        //selection et insertion de la case d'arrivee dans eCaseChemChoisi
        int compt3=0;
        while(compt3<eChemin.size())
        {
            if(eChemin.at(compt3).positionX==positX && eChemin.at(compt3).positionY==positY)
            {
                eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(compt3));
            }
            compt3++;
        }

        //initialisation du parcours
        int pseudoCmpt=eChemin.size()-1;
        int compt4=0;
        while(compt4<eChemin.size())
        {
            if(eChemin.at(pseudoCmpt).num_chem==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).lien_ch_precd && eChemin.at(pseudoCmpt).valeur_chemin==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).valeur_chemin-1)
            {
                eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(pseudoCmpt));
            }
            pseudoCmpt--;
            compt4++;
        }

        //determiner la direction a prendre
        int dernEl=eCaseChemChoisi.size()-1;
        if(eCaseChemChoisi.at(dernEl-1).i_d_g)
        {
            changerDirSerp(SERPENT_2,Droite);
        }
        else if(eCaseChemChoisi.at(dernEl-1).i_d_d)
        {
            changerDirSerp(SERPENT_2,Gauche);
        }
        else if(eCaseChemChoisi.at(dernEl-1).i_d_h)
        {
            changerDirSerp(SERPENT_2,Bas);
        }
        else
        {
            changerDirSerp(SERPENT_2,Haut);
        }



    }


}

void Controleur::insertionCase(std::vector<CaseValable> &eChemin,int posX,int posY,int valCh,int lienChPrecd,int numCh,int mouv)
{
    std::vector<CaseValable> *eChmin=&eChemin;

    CaseValable elCase;
    elCase.positionX=posX;
    elCase.positionY=posY;
    elCase.valeur_chemin=valCh;
    elCase.lien_ch_precd=lienChPrecd;
    elCase.num_chem=numCh;

    if(mouv==0)
    {
        elCase.mouv_g=true;
        elCase.mouv_d=false;
        elCase.mouv_h=false;
        elCase.mouv_b=false;

        elCase.i_d_g=false;
        elCase.i_d_d=true;
        elCase.i_d_h=false;
        elCase.i_d_b=false;
    }
    else if(mouv==1)
    {
        elCase.mouv_g=false;
        elCase.mouv_d=true;
        elCase.mouv_h=false;
        elCase.mouv_b=false;

        elCase.i_d_g=true;
        elCase.i_d_d=false;
        elCase.i_d_h=false;
        elCase.i_d_b=false;
    }
    else if(mouv==2)
    {
        elCase.mouv_g=false;
        elCase.mouv_d=false;
        elCase.mouv_h=true;
        elCase.mouv_b=false;

        elCase.i_d_g=false;
        elCase.i_d_d=false;
        elCase.i_d_h=false;
        elCase.i_d_b=true;
    }
    else
    {
        elCase.mouv_g=false;
        elCase.mouv_d=false;
        elCase.mouv_h=false;
        elCase.mouv_b=true;

        elCase.i_d_g=false;
        elCase.i_d_d=false;
        elCase.i_d_h=true;
        elCase.i_d_b=false;
    }

    eChmin->insert(eChmin->end(),elCase);
}


Controleur::~Controleur()
{
    delete m_decor;
}



