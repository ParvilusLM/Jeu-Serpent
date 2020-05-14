#ifndef DEF_SON
#define DEF_SON

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "enums.h"
#include "varG.h"
#include "constantes.h"

class Son
{
public:
    Son();
    ~Son();
    void jouerSon();


private:
    sf::Sound m_sonSerp;
    sf::SoundBuffer m_serpSoundBuf;


};

#endif // DEF_SON
