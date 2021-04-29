#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include <string>
#include <vector>

class Menu
{
public:
    Menu(int id);
    void chargerFond();
    void dessinerFond();
    void chargerBoutons();
    void dessinerBoutons();
    void libererEspace();
    void quelBoutonMenu(float x, float y, int* loop, bool* contreIA);
    void quelBoutonMenuOptions(float x, float y, int* loop, int* id_map,int* nb_unite_depart,Textures** textes);
    void quelBoutonMenuRegles(float x, float y, int* loop);
    void quelBoutonMenuJeu(float x, float y, Joueur** joueur, Unite** nouvelleUnite, int nb_unite_depart, int* loop, Tour* tour, bool* placement, Textures** textes);
    void quelBoutonJeu(float x, float y, int* cxs, int* cys, int* cxd, int* cyd, int* cxa,int* cya,
    							Map* carte, Joueur** joueur, Unite** uniteActuelle, Unite** uniteEnnemie,
    							Tour* tour, int* idNouveauMenu, Actions* action, Textures** textes, Menu** menuUnite, Quefeje* quefeje);
    void quelBoutonMenuFin(float x, float y, int* loop, bool* contreIA);
    float boutonGetX(int indice);
    float boutonGetY(int indice);
    int getIdMenu();

private:
    int m_id;
    float m_xg,m_xd,m_yh,m_yb;
    Bouton** tabBoutons;
    int m_nbBoutons;
    Textures* m_tex;
    GLuint m_texture;
    const char* m_icone; //Référence du fichier de l'icone de l'unite
    Unite uniteAffiche;
};
#endif
