#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "constantes.hpp"
#include "Textures.hpp"
#include "Unite.hpp"
#include "Case.hpp"
#include "Noeud.hpp"
#include "Map.hpp"
#include "bouton.hpp"
#include "Joueur.hpp"
#include "ordinateur.hpp"
#include "Menu.hpp"
#include "fonctions.hpp"

using namespace std;

Bouton::Bouton()
{
  m_icone="img/IMAGE_NULLE.png";
  x=0;
  y=0;
  w=0;
  h=0;
}

Bouton::Bouton(float Posx, float Posy, float width, float height, const char* icone)
{
  m_icone=icone;
  x=Posx;
  y=Posy;
  w=width;
  h=height;
}

void Bouton::chargerFond()
{
    this->m_tex = new Textures(IMG_Load(this->m_icone),&(this->m_texture));
}

void Bouton::modifierIcone(const char* icone)
{
  this->libererEspace();
  this->m_icone = icone;
  this->chargerFond();
}

void Bouton::dessinerBouton()
{
  dessinerImage(this->m_texture,this->x-(this->w)/2,this->x+(this->w)/2,this->y+(this->h)/2,this->y-(this->h)/2);
}

void Bouton::libererEspace()
{
  this->m_tex->libererEspace(&(this->m_texture));
}

bool Bouton::cliqueBouton(float x, float y)
{
  if(x>this->x-(this->w)/2 && x<this->x+(this->w)/2 && y>this->y-(this->h)/2 && y<this->y+(this->h)/2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

float Bouton::getX()
{
  return this->x;
}

float Bouton::getY()
{
  return this->y;
}