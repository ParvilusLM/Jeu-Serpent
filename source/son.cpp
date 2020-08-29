#include "son.h"


Son::Son()
{
    m_serpSoundBuf.loadFromFile("donnees/serp.wav");
    m_sonSerp.setBuffer(m_serpSoundBuf);
}

void Son::jouerSon()
{
    m_sonSerp.play();

}

Son::~Son()
{

}
