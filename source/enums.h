#ifndef DEF_ENUMS
#define DEF_ENUMS

#include <SFML/Graphics.hpp>

using namespace sf;

struct element_serpent
{
    Sprite el_spr;

};

struct directionSerpent
{
    bool dir_s_g;
    bool dir_s_d;
    bool dir_s_h;
    bool dir_s_b;
};

enum
{
    SERPENT_1,
    SERPENT_2,
    SERPENT_IA
};



enum TypeMenu
{
    MenuPrincipal,
    MenuNvlPartie,
    MenuInstructions,
    MenuApropos
};

enum TypeJeu
{
    HUMAINvsHUMAIN,
    HUMAINvsIA
};

enum
{
    AUCUN_EL_ACT,
    NP_ACTIF,
    I_ACTIF,
    AP_ACTIF,
    Q_ACTIF,
    JHvsH_ACTIF,
    JHvsIA_ACTIF,
    R_ACTIF
};

enum
{
    p_tete,
    p_corps,
    p_queue
};

enum
{
    Bas,
    Haut,
    Droite,
    Gauche
};

enum
{
    s_tete_G,
    s_tete_D,
    s_tete_B,
    s_tete_H,
    s_corps_h,
    s_corps_v,
    s_corps_GH,
    s_corps_GB,
    s_corps_DH,
    s_corps_DB,
    s_queue_G,
    s_queue_D,
    s_queue_H,
    s_queue_B
};

enum
{
    VIDE,
    FRUIT,
    CORPS,
    TETE1,
    TETE2
};


#endif // DEF_ENUMS
