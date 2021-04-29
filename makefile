CFLAGS = -Wall -ansi
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm -lSDL_ttf

imacwars2 : main.o interface_fin.o interface_regles.o interface_jeu.o interface_menu.o interface_options.o fonctions.o Menu.o ordinateur.o Joueur.o bouton.o Map.o Noeud.o Case.o Unite.o Textures.o
	g++ $^ -o $@ $(LDFLAGS)

Textures.o : Textures.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

Unite.o : Unite.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

Case.o : Case.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

Noeud.o : Noeud.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

Map.o : Map.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

bouton.o : bouton.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

Joueur.o : Joueur.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

ordinateur.o : ordinateur.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

Menu.o : Menu.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

fonctions.o : fonctions.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

interface_options.o : interface_options.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

interface_menu.o : interface_menu.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

interface_jeu.o : interface_jeu.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

interface_regles.o : interface_regles.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
		g++ -o $@ -c $< $(CFLAGS)

interface_fin.o : interface_fin.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

main.o : main.cpp constantes.hpp Textures.hpp Unite.hpp Case.hpp Noeud.hpp Map.hpp bouton.hpp Joueur.hpp ordinateur.hpp Menu.hpp fonctions.hpp
	g++ -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
