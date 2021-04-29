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

Textures::Textures()
{

}

Textures::Textures(SDL_Surface* surface, GLuint* texture){
	/* Chargement de l'image */
    m_surface = surface;
    if(NULL == m_surface) {
        fprintf(stderr, "Echec du chargement de l'image %d\n", *texture);
        exit(EXIT_FAILURE);
    }


    /* Initialisation de la texture */
    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    switch(m_surface->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %d non supporte.\n", *texture);
            //return EXIT_FAILURE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_surface->w, m_surface->h, 0, format, GL_UNSIGNED_BYTE, m_surface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    //return(1);
}

void Textures::chargeTexte(const char* message,int taille,Uint8 b,Uint8 g,Uint8 r)
{

  this->m_surface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,0,0,32,0,0,0,0);

  this->font = TTF_OpenFont("police/8-Bit-Madness.ttf", taille);

  SDL_Color couleur = {r,g,b};
  SDL_Surface* sText = TTF_RenderUTF8_Blended(this->font, message, couleur);
  if(NULL == sText) {
      fprintf(stderr, "Echec du chargement de l'image %s\n",(char*)&this->m_idTexture);
      exit(EXIT_FAILURE);
  }
  glGenTextures(1, &(this->m_idTexture));

  glBindTexture(GL_TEXTURE_2D, this->m_idTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  GLenum format;
  switch(sText->format->BytesPerPixel) {
      case 1:
          format = GL_RED;
          break;
      case 3:
          format = GL_RGB;
          break;
      case 4:
          format = GL_RGBA;
          break;
      default:
          fprintf(stderr, "Format des pixels de l'image %s non supporte.\n",(char*)&this->m_idTexture);
          //return EXIT_FAILURE;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sText->w, sText->h, 0, format, GL_UNSIGNED_BYTE, sText->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);

  this->m_surface->w = sText->w;
  this->m_surface->h = sText->h;
}

void Textures::dessineTexte(float x, float y)
{
  glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, this->m_idTexture);

          glPushMatrix();

            glBegin(GL_QUADS);
              glTexCoord2f(0, 0);
              glVertex2f(x-((float)this->m_surface->w/1000)/2,y+((float)this->m_surface->h/1000)/2);

              glTexCoord2f(1, 0);
              glVertex2f(x+((float)this->m_surface->w/1000)/2,y+((float)this->m_surface->h/1000)/2);

              glTexCoord2f(1, 1);
              glVertex2f(x+((float)this->m_surface->w/1000)/2,y-((float)this->m_surface->h/1000)/2);

              glTexCoord2f(0, 1);
              glVertex2f(x-((float)this->m_surface->w/1000)/2,y-((float)this->m_surface->h/1000)/2);
            glEnd();

          glPopMatrix();


        glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}

void Textures::libererTexte()
{
  TTF_CloseFont(this->font);
  SDL_FreeSurface(this->m_surface);
}

void Textures::libererEspace(GLuint* texture)
{
    /* Liberation de la memoire allouee sur le GPU pour la texture */
    glDeleteTextures(1, texture);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(m_surface);
}