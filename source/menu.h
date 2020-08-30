#ifndef DEF_MENU
#define DEF_MENU

#include<SFML/Graphics.hpp>
#include "varG.h"
#include "constantes.h"
#include "enums.h"
#include <sstream>


class Menu
{
public:
    Menu(sf::RenderWindow &fenetre);
    ~Menu();
    void initMenuP();
    void initMenuNP();
    void initMenuI();
    void initMenuAp();
    void initMenuPause();
    void initMenuFinPart();

    void afficheMenuP();
    void afficheMenuNP();
    void afficheMenuI();
    void afficheMenuAp();
    void afficheMenuPause();
    void afficheMenuFinPart();
    void afficheMenu();

    void elementActif();
    void selectionElActif();
    void retourMenuP();
    bool collisionTS(sf::FloatRect elem);

    void setTypeMenu(int menuActuel);
    TypeJeu getTypeJeu();
    void quitterJeu();


private:
    sf::RenderWindow* m_fenetre;

    TypeMenu m_typeMenu;
    sf::Font m_font;
    sf::Font m_font2;
    sf::Font m_font3;

    int m_elementActif;
    sf::Text m_txtRetour;
    sf::Text m_txtTypeMenu;
    sf::Sprite m_sFondEc;

    //pour menu principale
    sf::Text m_txtNouvlPartie;
    sf::Text m_txtInstructions;
    sf::Text m_txtAPropos;
    sf::Text m_txtQuitter;

    sf::Texture m_tFondEc;
    sf::Texture m_tFondEc2;

    //pour menu nouvellePartie
    sf::Text m_txtHvsH;
    sf::Text m_txtHvsIA;
    TypeJeu m_typeJeu;

    //pour menu Instructions
    sf::Text m_txtMI;
    std::ostringstream m_stream_txtMI;


    //pour menu Apropos
    sf::Text m_txtTMAP;
    std::ostringstream m_stream_txtTMAP;

    sf::Text m_txtMAP;
    std::ostringstream m_stream_txtMAP;

    //pour menu pause
    sf::Texture m_tMenuPause;
    sf::Sprite m_sMenuPause;

    //pour menu fin Partie
    sf::Texture m_tMenuFinP;
    sf::Sprite m_sMenuFinP;

//boites engl des boutons
    sf::FloatRect boiteEBPR,boiteEBPI,boiteEBPQ,boiteEBFQ,boiteEBFR;





};

#endif // DEF_MENU
