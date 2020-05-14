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

void Controleur::changerDirSerpIa()
{

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

Controleur::~Controleur()
{
    delete m_decor;
}



