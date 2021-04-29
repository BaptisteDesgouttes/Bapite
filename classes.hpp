#include <iostream>
#include <string>

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 600;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "IMACWARS 2.0";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 2.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

void drawSquare(float x, float y, float taille, int r, int v, int b);

class Unite
{
public:
	Unite();
	void attaquer();
	void deplacer();
private:
	int m_id;
	Joueur m_joueur;
	int m_r, m_v, m_b;
	Case m_caseActuelle; //Case dans laquelle elle se trouve
	int m_pv;
	int m_force;
	int m_portee;
	int m_mobilite;
	int m_cout;
	string m_icone; //Référence du fichier de l'icone de l'unite
	char m_type;
	char m_typeMouvement;
	int m_efficacite;

};

class Joueur
{
public:
	Joueur();
private:
	int m_id;
	int m_type; // 1 -> vrai joueur / 2 -> IA
	std::string m_nom;
	int m_r, m_v, m_b;
	int m_fonds;
	int m_nbUnites;
	Unite m_tabUnites[];
};

class Case
{
public:
	Case();
	Case(char type,int x,int y,int nbCases);
	void dessinerCase();
private:
	float m_taille;
	int m_r, m_v, m_b;
	char m_type;
	float m_x,m_y; //Coordonnées en openGL du coin supérieur gauche de la case
	int m_occupee;
	Unite m_occupant;
};


class Map
{ 
public:
	Map(int largeur, int hauteur);
	void dessinerCarte();
private:
	int m_largeur, m_hauteur; //Nombre de cases en largeur et en hauteur
	int m_nbCases;
	Case** m_tabCases;
};