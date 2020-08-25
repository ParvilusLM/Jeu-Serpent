#ifndef DEF_VARG
#define DEF_VARG

extern bool HumvsHum;
extern bool jeuEnCours;
extern bool jeuPause;
extern int sourisX,sourisY;

struct CaseValable
{
    int positionX;
    int positionY;
    int valeur_chemin;
    int lien_ch_precd;
    int num_chem;

    //pour savoir la position precedente
    bool i_d_g;
    bool i_d_d;
    bool i_d_h;
    bool i_d_b;

    //pour savoir ou va etre la piece
    bool mouv_g;
    bool mouv_d;
    bool mouv_h;
    bool mouv_b;
};

#endif // DEF_VARG
