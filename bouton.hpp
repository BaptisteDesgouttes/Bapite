#ifndef BOUTON_HPP_INCLUDED
#define BOUTON_HPP_INCLUDED

#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


#define BOUTON_CLIQUE SDL_USEREVENT

class Bouton
{
public:
  Bouton();
  Bouton(float x, float y, float width, float height, const char* icone); //x et y sont les coordonnées du centre du bouton
  void chargerFond();
  void modifierIcone(const char* icone);
  void dessinerBouton();
  void libererEspace();
  bool cliqueBouton(float x, float y);
  float getX();
  float getY();

private:
    enum Etat {SURVOLE, ENFONCE, PAS_SURVOLE};
    Textures* m_tex;
    GLuint m_texture;
    const char* m_icone; //Référence du fichier de l'icone de l'unite
    float x,y;
    float w,h;
};

#endif
