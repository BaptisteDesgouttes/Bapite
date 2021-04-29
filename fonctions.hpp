#ifndef FONCTIONS_HPP_INCLUDED
#define FONCTIONS_HPP_INCLUDED

#include <iostream>
#include <string>

void drawSquare(float x, float y, float taille,int r, int v, int b,float a);
void drawRect(float x, float y, float w, float h,int r, int v, int b,float a);
void drawRect2(float x, float y, float w, float h,int r, int v, int b,float a);
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);

// char* convertirNombreEnChar(int valeur,char* phrase);

void dessinerImage(GLuint idTexture,float xg, float xd, float yh, float yb);
void creationTextesMenus(Textures** textes);
void creationTextes(Textures** textes, bool contreIA);
void dessinerTexte(Textures** textes, Menu* menu);

void interface_menu(SDL_Surface* surface,float* aspectRatio,int* loop,float* px,float* py,Textures** textes, bool* contreIA);
void interface_jeu(SDL_Surface* surface, Textures** textes, float* aspectRatio,int* loop, float* px, float* py, int idMap, int nbInitJoueur, bool contreIA, int* vainqueur);
void interface_options(SDL_Surface* surface,float* aspectRatio,int* loop,float* px,float* py, Textures** textes, int* nb_unite_depart,int* id_map);
void interface_regles(SDL_Surface* surface,float* aspectRatio,int* loop,float* px,float* py,Textures** textes,int* nb_unite_depart,int* id_map);
void interface_fin(SDL_Surface* surface,float* aspectRatio,int* loop,float* px,float* py, Textures** textes, bool* contreIA, int* vainqueur);

bool selection(int cx, int cy, int* cxs, int* cys, int idMenu, int idProchainMenu, int* idNouveauMenu, Map* carte, Joueur** joueur, Unite** uniteActuelle, Textures** texte1, Textures** texte2);
bool deplacement(int cx, int cy, int cxsd, int cysd, int* cxd, int* cyd, int idMenu, int idProchainMenu, int* idNouveauMenu,Map* carte, Unite** uniteActuelle, Textures** texte1, Textures** texte2);
bool attaque(int cx, int cy, int* cxa, int* cya, int idMenu, int idProchainMenu, int* idNouveauMenu, Joueur** joueur, Unite** uniteActuelle, Unite** uniteEnnemie, Map* carte, Textures** texte1, Textures** texte2, Quefeje* quefeje);

bool estDans(int val, Case** tableau, int size);
bool estVide(Case** tableau, int size);

#endif
