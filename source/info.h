 #ifndef DEF_INFO
 #define DEF_INFO

 #include <sstream>
#include "enums.h"
#include "varG.h"
#include "constantes.h"

 class Info
 {
 public:

     Info(sf::RenderWindow &fenetre);
     ~Info();
     template <class T> std::string nbEnString(T nb);
     void initInfo();
     void reinitInfo();
     void afficheInfo();
     void indiquerScore();
     int getScore(int num_joueur);
     void gestionScore(int num_joueur);



 private:
     sf::RenderWindow *m_fenetre;
     sf::Text m_txtScoreJ1;
     sf::Text m_txtScoreJ2;
     sf::Text m_txtPause;
     sf::Font m_font1,m_font2;
     int m_score[2];



 };

 #endif // DEF_INFO
