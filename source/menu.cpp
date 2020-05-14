#include "menu.h"

Menu::Menu(sf::RenderWindow &fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;
    m_font.loadFromFile("donnees/forte.ttf");
    m_font2.loadFromFile("donnees/ALGER.ttf");
    m_font3.loadFromFile("donnees/rod.ttf");

    m_tFondEc.loadFromFile("donnees/cadre_menu.png");
    m_tFondEc2.loadFromFile("donnees/cadre_menu2.png");

    m_txtTypeMenu.setFont(m_font2);
    m_txtTypeMenu.setCharacterSize(35);
    m_txtTypeMenu.setFillColor(sf::Color::Black);
    m_txtTypeMenu.setPosition(200,220);



    m_txtRetour.setFont(m_font);
    m_txtRetour.setCharacterSize(25);
    m_txtRetour.setFillColor(sf::Color::Black);
    m_txtRetour.setPosition(25,28);
    m_txtRetour.setString("RETOUR");


    m_typeMenu=MenuPrincipal;
    initMenuP();
    initMenuNP();
    initMenuI();
    initMenuAp();


}


void Menu::initMenuP()
{
    m_sFondEc.setTexture(m_tFondEc);
    m_sFondEc.setPosition(0,0);

    m_txtNouvlPartie.setFont(m_font);
    m_txtNouvlPartie.setCharacterSize(40);
    m_txtNouvlPartie.setFillColor(sf::Color::Black);
    m_txtNouvlPartie.setPosition(210,320);
    m_txtNouvlPartie.setString("Nouvelle Partie");

    m_txtInstructions.setFont(m_font);
    m_txtInstructions.setCharacterSize(40);
    m_txtInstructions.setFillColor(sf::Color::Black);
    m_txtInstructions.setPosition(240,400);
    m_txtInstructions.setString("Instructions");

    m_txtAPropos.setFont(m_font);
    m_txtAPropos.setCharacterSize(40);
    m_txtAPropos.setFillColor(sf::Color::Black);
    m_txtAPropos.setPosition(260,480);
    m_txtAPropos.setString("A Propos");

    m_txtQuitter.setFont(m_font);
    m_txtQuitter.setCharacterSize(40);
    m_txtQuitter.setFillColor(sf::Color::Black);
    m_txtQuitter.setPosition(285,560);
    m_txtQuitter.setString("Quitter");

}

void Menu::initMenuNP()
{
     m_txtHvsH.setFont(m_font);
     m_txtHvsH.setCharacterSize(40);
     m_txtHvsH.setFillColor(sf::Color::Black);
     m_txtHvsH.setPosition(140,450);
     m_txtHvsH.setString("    Humain vs Humain");

     m_txtHvsIA.setFont(m_font);
     m_txtHvsIA.setCharacterSize(40);
     m_txtHvsIA.setFillColor(sf::Color::Black);
     m_txtHvsIA.setPosition(190,350);
     m_txtHvsIA.setString("  Humain vs CPU");

}

void Menu::initMenuI()
{
    m_txtMI.setFont(m_font3);
    m_txtMI.setCharacterSize(25);
    m_txtMI.setFillColor(sf::Color::Black);
    m_txtMI.setPosition(10,300);



    m_stream_txtMI.str("");
    m_stream_txtMI<<"Serpent vs Serpent se joue a deux, en mode Humain vs Humain \n ou Humain vs CPU.\n\n"
                  <<"Pour gagner une partie, il faut manger le plus de fruit "
                  <<"que son \n adversaire, "
                  <<"tout en evitant aussi d'entrer en collision avec lui, \n les bords ou soi même.\n\n"
                  <<"Pour deplaser le serpent 1, utiliser les touches W : S et A : D \n"
                  <<"Pour deplacer le serpent 2, utiliser les touches 8 : 2  et 4 : 6 \n\n"
                  <<"Pour mettre le jeu en pause : Touche barre d'espace \n"
                  <<"Pour retourner dans le menu pricincipal utiliser la touche R";

    m_txtMI.setString(m_stream_txtMI.str());
}

void Menu::initMenuAp()
{

}


void Menu::affficheMenu()
{
    m_fenetre->draw(m_sFondEc);


    if(m_typeMenu==MenuPrincipal)
    {
        afficheMenuP();
    }
    else if(m_typeMenu==MenuNvlPartie)
    {
        afficheMenuNP();
    }
    else if(m_typeMenu==MenuInstructions)
    {
        afficheMenuI();
    }
    else
    {
        afficheMenuAp();
    }
}

void Menu::afficheMenuP()
{
    m_fenetre->draw(m_txtNouvlPartie);
    m_fenetre->draw(m_txtInstructions);
    m_fenetre->draw(m_txtAPropos);
    m_fenetre->draw(m_txtQuitter);

    m_txtTypeMenu.setString(" Menu Principal");
    m_fenetre->draw(m_txtTypeMenu);
}

void Menu::afficheMenuNP()
{
    m_fenetre->draw(m_txtHvsH);
    m_fenetre->draw(m_txtHvsIA);
    m_fenetre->draw(m_txtRetour);

    m_txtTypeMenu.setString("       Type Jeu");
    m_fenetre->draw(m_txtTypeMenu);
}

void Menu::afficheMenuI()
{
    m_fenetre->draw(m_txtRetour);

    m_txtTypeMenu.setString("   Instructions");
    m_fenetre->draw(m_txtTypeMenu);
    m_fenetre->draw(m_txtMI);
}

void Menu::afficheMenuAp()
{
    m_fenetre->draw(m_txtRetour);

    m_txtTypeMenu.setString("       A propos");
    m_fenetre->draw(m_txtTypeMenu);
}

void Menu::quitterJeu()
{
    m_fenetre->close();
}

void Menu::elementActif()
{

    if(m_typeMenu==MenuPrincipal)
    {
        if(collisionTS(m_txtNouvlPartie.getGlobalBounds()))
        {
            m_txtNouvlPartie.setColor(sf::Color::Red);
            m_elementActif=NP_ACTIF;
        }
        else if(collisionTS(m_txtInstructions.getGlobalBounds()))
        {
            m_txtInstructions.setColor(sf::Color::Red);
            m_elementActif=I_ACTIF;
        }
        else if(collisionTS(m_txtAPropos.getGlobalBounds()))
        {
            m_txtAPropos.setColor(sf::Color::Red);
            m_elementActif=AP_ACTIF;
        }
        else if(collisionTS(m_txtQuitter.getGlobalBounds()))
        {
            m_txtQuitter.setColor(sf::Color::Red);
            m_elementActif=Q_ACTIF;
        }
        else
        {
            m_txtNouvlPartie.setColor(sf::Color::Black);
            m_txtInstructions.setColor(sf::Color::Black);
            m_txtAPropos.setColor(sf::Color::Black);
            m_txtQuitter.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }

    }
    else if(m_typeMenu==MenuNvlPartie)
    {
        if(collisionTS(m_txtHvsH.getGlobalBounds()))
        {
            m_txtHvsH.setColor(sf::Color::Red);
            m_elementActif=JHvsH_ACTIF;
        }
        else if(collisionTS(m_txtHvsIA.getGlobalBounds()))
        {
            m_txtHvsIA.setColor(sf::Color::Red);
            m_elementActif=JHvsIA_ACTIF;
        }
        else if(collisionTS(m_txtRetour.getGlobalBounds()))
        {
            m_txtRetour.setColor(sf::Color::Red);
            m_elementActif=R_ACTIF;
        }
        else
        {
            m_txtHvsH.setColor(sf::Color::Black);
            m_txtHvsIA.setColor(sf::Color::Black);
            m_txtRetour.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }
    }
    else if(m_typeMenu==MenuInstructions)
    {
        if(collisionTS(m_txtRetour.getGlobalBounds()))
        {
            m_txtRetour.setColor(sf::Color::Red);
            m_elementActif=R_ACTIF;
        }
        else
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }
    }
    else
    {
        if(collisionTS(m_txtRetour.getGlobalBounds()))
        {
            m_txtRetour.setColor(sf::Color::Red);
            m_elementActif=R_ACTIF;
        }
        else
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }
    }

}

void Menu::selectionElActif()
{
    if(m_typeMenu==MenuPrincipal)
    {
        if(m_elementActif==NP_ACTIF)
        {
            m_txtNouvlPartie.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc2);
            m_typeMenu=MenuNvlPartie;
        }
        else if(m_elementActif==I_ACTIF)
        {
            m_txtInstructions.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc2);
            m_typeMenu=MenuInstructions;
        }
        else if(m_elementActif==AP_ACTIF)
        {
            m_txtAPropos.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc2);
            m_typeMenu=MenuApropos;
        }
        else if(m_elementActif==Q_ACTIF)
        {
            m_txtQuitter.setColor(sf::Color::Black);
            quitterJeu();
        }
        else
        {

        }
    }
    else if(m_typeMenu==MenuNvlPartie)
    {
        if(m_elementActif==JHvsH_ACTIF)
        {
            m_txtHvsH.setColor(sf::Color::Black);
            HumvsHum=true;
            jeuEnCours=true;
            m_typeJeu=HUMAINvsHUMAIN;
        }
        else if(m_elementActif==JHvsIA_ACTIF)
        {
            m_txtHvsIA.setColor(sf::Color::Black);
            HumvsHum=false;
            jeuEnCours=true;
            m_typeJeu=HUMAINvsIA;
        }
        else if(m_elementActif==R_ACTIF)
        {
             m_txtRetour.setColor(sf::Color::Black);
             m_sFondEc.setTexture(m_tFondEc);
             m_typeMenu=MenuPrincipal;
        }
        else
        {

        }

    }
    else if(m_typeMenu==MenuInstructions)
    {
        if(m_elementActif==R_ACTIF)
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc);
            m_typeMenu=MenuPrincipal;
        }
        else
        {

        }

    }
    else
    {
        if(m_elementActif==R_ACTIF)
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc);
            m_typeMenu=MenuPrincipal;
        }
        else
        {

        }
    }
}

bool Menu::collisionTS(sf::FloatRect elem)
{
    bool collision=false;
    if((elem.left<sourisX && elem.left+elem.width>sourisX) && (elem.top<sourisY && elem.top+elem.height>sourisY))
    {
        collision=true;
    }
    return collision;
}

void Menu::retourMenuP()
{
    m_typeMenu=MenuPrincipal;
    m_sFondEc.setTexture(m_tFondEc);
    m_elementActif=AUCUN_EL_ACT;
}

TypeJeu Menu::getTypeJeu()
{
    return m_typeJeu;
}

Menu::~Menu()
{

}

