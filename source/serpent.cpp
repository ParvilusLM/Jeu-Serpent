#include "serpent.h"


Serpent::Serpent(sf::RenderWindow &fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;
    m_t_spritesSerp.loadFromFile("donnees/serpent_sprit.png");
    m_t_spritesSerp2.loadFromFile("donnees/serpent_sprit2.png");

    m_mouvX=20.f;
    m_mouvY=20.f;
}

void Serpent::initSerpent()
{
    m_serpent.clear();

    std::vector<element_serpent> m_serpent1;

    element_serpent tete;
    tete.el_spr.setPosition(190.f,210.f);
    tete.el_spr.setOrigin(10.f,10.f);
    tete.el_spr.setTexture(m_t_spritesSerp);
    m_serpent1.insert(m_serpent1.begin(),tete);


    element_serpent corps1;
    corps1.el_spr.setPosition(170.f,210.f);
    corps1.el_spr.setOrigin(10.f,10.f);
    corps1.el_spr.setTexture(m_t_spritesSerp);
    m_serpent1.insert(m_serpent1.end(),corps1);

    element_serpent corps2;
    corps2.el_spr.setPosition(150.f,210.f);
    corps2.el_spr.setOrigin(10.f,10.f);
    corps2.el_spr.setTexture(m_t_spritesSerp);
    m_serpent1.insert(m_serpent1.end(),corps2);


    element_serpent queu;
    queu.el_spr.setPosition(130.f,210.f);
    queu.el_spr.setOrigin(10.f,10.f);
    queu.el_spr.setTexture(m_t_spritesSerp);
    m_serpent1.insert(m_serpent1.end(),queu);

    m_serpent.insert(m_serpent.end(),m_serpent1);

    directionSerpent direcSerp;
    direcSerp.dir_s_g=false;
    direcSerp.dir_s_d=true;
    direcSerp.dir_s_h=false;
    direcSerp.dir_s_b=false;

    m_dirSerp.push_back(direcSerp);

    std::vector<element_serpent> m_serpent2;
    element_serpent tete2;
    tete2.el_spr.setPosition(190.f,410.f);
    tete2.el_spr.setOrigin(10.f,10.f);
    tete2.el_spr.setTexture(m_t_spritesSerp2);
    m_serpent2.insert(m_serpent2.begin(),tete2);

    element_serpent corps1s;
    corps1s.el_spr.setPosition(170.f,410.f);
    corps1s.el_spr.setOrigin(10.f,10.f);
    corps1s.el_spr.setTexture(m_t_spritesSerp2);
    m_serpent2.insert(m_serpent2.end(),corps1s);

    element_serpent corps2s;
    corps2s.el_spr.setPosition(150.f,410.f);
    corps2s.el_spr.setOrigin(10.f,10.f);
    corps2s.el_spr.setTexture(m_t_spritesSerp2);
    m_serpent2.insert(m_serpent2.end(),corps2s);

    element_serpent queus;
    queus.el_spr.setPosition(130.f,410.f);
    queus.el_spr.setOrigin(10.f,10.f);
    queus.el_spr.setTexture(m_t_spritesSerp2);
    m_serpent2.insert(m_serpent2.end(),queus);

    m_serpent.insert(m_serpent.end(),m_serpent2);

    directionSerpent direcSerp2;
    direcSerp2.dir_s_g=false;
    direcSerp2.dir_s_d=true;
    direcSerp2.dir_s_h=false;
    direcSerp2.dir_s_b=false;

    m_dirSerp.push_back(direcSerp2);
}


void Serpent::mouvementSerpent(int no_serp)
{
    //std::cout<<"AAAAAAAAAAAA"<<std::endl;
    changPosPartPreced(no_serp);
    //std::cout<<"BBBBBBBBBB"<<std::endl;

    if(m_dirSerp.at(no_serp).dir_s_g)
    {
        m_serpent.at(no_serp).at(0).el_spr.move(-m_mouvX,0);
    }

    if(m_dirSerp.at(no_serp).dir_s_d)
    {
        m_serpent.at(no_serp).at(0).el_spr.move(m_mouvX,0);
    }

    if(m_dirSerp.at(no_serp).dir_s_h)
    {
        m_serpent.at(no_serp).at(0).el_spr.move(0,-m_mouvY);
    }

    if(m_dirSerp.at(no_serp).dir_s_b)
    {
        m_serpent.at(no_serp).at(0).el_spr.move(0,m_mouvY);
    }




}

void Serpent::ajouteNPDS(int no_serp)
{
    element_serpent nouv_morceau;
    nouv_morceau.el_spr.setOrigin(10.f,10.f);

    if(no_serp==1)
    {
        nouv_morceau.el_spr.setTexture(m_t_spritesSerp);
    }
    else
    {
        nouv_morceau.el_spr.setTexture(m_t_spritesSerp2);
    }


    int dern_el=m_serpent.at(no_serp-1).size()-1;
    float posX=m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().x;
    float posY=m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().y;

    if(m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().x > m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().x && m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().y == m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().y )
    {
        m_serpent.at(no_serp-1).at(dern_el).el_spr.move(20.f,0);
    }

    if(m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().x < m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().x && m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().y == m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().y )
    {
        m_serpent.at(no_serp-1).at(dern_el).el_spr.move(-20.f,0);
    }

    if(m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().x == m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().x && m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().y > m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().y )
    {
        m_serpent.at(no_serp-1).at(dern_el).el_spr.move(0,20.f);
    }

    if(m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().x == m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().x && m_serpent.at(no_serp-1).at(dern_el).el_spr.getPosition().y < m_serpent.at(no_serp-1).at(dern_el-1).el_spr.getPosition().y )
    {
        m_serpent.at(no_serp-1).at(dern_el).el_spr.move(0,-20.f);
    }

    nouv_morceau.el_spr.setPosition(posX,posY);
    m_serpent.at(no_serp-1).insert(m_serpent.at(no_serp-1).end()-1,nouv_morceau);

}

void Serpent::appliquerTexture()
{
    int compt=0;

    while(compt<m_serpent.size())
    {
        int compt2=0;

        while(compt2<m_serpent[compt].size())
        {
            if(compt2==0)
            {
                //tete bas
                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(20,0,20,20));
                }

                //tete haut
                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(40,0,20,20));
                }

                //tete gauche
                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(60,0,20,20));
                }

                //tete droite
                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(0,0,20,20));
                }

            }
            else if( compt2>0 && compt2<m_serpent[compt].size()-1 )
            {
                //corps horiz
                if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(20,60,20,20));
                   }

                //corps horiz
                if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(20,60,20,20));
                   }

                 //corps vertic
                if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(0,60,20,20));
                   }

                //corps vertic
                if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(0,60,20,20));
                   }

                //corps GH
                if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(60,20,20,20));
                   }

                //corps HG
                if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(60,20,20,20));
                   }

               //corps DH
               if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(0,20,20,20));
                   }

               //corps HD
               if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(0,20,20,20));
                   }

               //corps BD
               if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(40,20,20,20));
                   }


               //corps DB
               if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x > m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(40,20,20,20));
                   }


              //corps BG
              if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(20,20,20,20));
                   }


              //corps GB
              if( (m_serpent.at(compt).at(compt2).el_spr.getPosition().x == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y) &&
                   (m_serpent.at(compt).at(compt2).el_spr.getPosition().x < m_serpent.at(compt).at(compt2+1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2+1).el_spr.getPosition().y) )
                   {
                       m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(20,20,20,20));
                   }


            }
            else
            {
                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x<m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(0,40,20,20));
                }

                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x>m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y == m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(60,40,20,20));
                }

                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y < m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(40,40,20,20));
                }

                if(m_serpent.at(compt).at(compt2).el_spr.getPosition().x==m_serpent.at(compt).at(compt2-1).el_spr.getPosition().x && m_serpent.at(compt).at(compt2).el_spr.getPosition().y > m_serpent.at(compt).at(compt2-1).el_spr.getPosition().y )
                {
                    m_serpent.at(compt).at(compt2).el_spr.setTextureRect(sf::IntRect(20,40,20,20));
                }
            }

            compt2++;
        }

        compt++;
    }
}

void Serpent::changPosPartPreced(int no_serp)
{
    int compt=0;
    int taill=m_serpent.at(no_serp).size()-1;
    while(compt<m_serpent.at(no_serp).size())
    {
        if(taill>0)
        {
            m_serpent.at(no_serp).at(taill).el_spr.setPosition(m_serpent.at(no_serp).at(taill-1).el_spr.getPosition());
        }

        taill--;

        compt++;
    }
}


std::vector< std::vector<element_serpent> > Serpent::getVectSerpents()
{
    return m_serpent;
}

void Serpent::afficherSerpent()
{
    appliquerTexture();
    int compt=0;
    while(compt<m_serpent.size())
    {
        int compt2=0;
        while(compt2<m_serpent[compt].size())
        {
           m_fenetre->draw(m_serpent.at(compt).at(compt2).el_spr);

           compt2++;
        }


        compt++;
    }
}


void Serpent::setDirectSerp(int no_serp, int dirSerp)
{
    bool possib=true;

    if(dirSerp==Haut && m_dirSerp.at(no_serp).dir_s_b)
    {
        possib=false;
    }

    if(dirSerp==Bas && m_dirSerp.at(no_serp).dir_s_h)
    {
        possib=false;
    }

    if(dirSerp==Gauche && m_dirSerp.at(no_serp).dir_s_d)
    {
        possib=false;
    }

    if(dirSerp==Droite && m_dirSerp.at(no_serp).dir_s_g)
    {
        possib=false;
    }




    if(possib)
    {
        m_dirSerp.at(no_serp).dir_s_b=false;
       m_dirSerp.at(no_serp).dir_s_h=false;
       m_dirSerp.at(no_serp).dir_s_g=false;
       m_dirSerp.at(no_serp).dir_s_d=false;

       if(dirSerp==Haut)
       {
          m_dirSerp.at(no_serp).dir_s_h=true;
       }

       if(dirSerp==Bas)
       {
           m_dirSerp.at(no_serp).dir_s_b=true;
       }

       if(dirSerp==Gauche)
       {
           m_dirSerp.at(no_serp).dir_s_g=true;
       }

       if(dirSerp==Droite)
       {
           m_dirSerp.at(no_serp).dir_s_d=true;
       }
    }

}


Serpent::~Serpent()
{

}

