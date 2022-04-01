#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include<iostream>
#include "config_sdl.h"
# include < ctime >
#include <stdio.h>
#include <fstream>
#include <ostream>
using namespace std;


const int LARGEUR = 1280; // NE PEUX PAS ENCORE ETRE CHANGE
const int HAUTEUR = 900; // NE PEUX PAS ENCORE ETRE CHANGE
int TEXTURE_THEME;
int TEXTURE_VICTOIRE;

SDL_Window* win = NULL;
SDL_Renderer* rendu = NULL;
SDL_Texture* texture[25] = { NULL };


enum TypeCase { MUR, CAISSE, POINT, SOL, POINT_GAGNANT, BOMBE };
enum Direction { HAUT, BAS, DROITE,GAUCHE };
enum Sens {POSITIF = +1, NEGATIF = -1};


struct Plateau {
	int nombre_lignes;
	int nombre_colonnes;
	TypeCase** tableau = NULL;
	int bonhomme_i;
	int bonhomme_j;
	int nombre_cases;
	int nb_coups_joues = 0;
	Direction dir;
	int score = 0;
	int nb_point = 0;
	int code_sortie = 0; // Determine si la sortie est par une fin de niveau ou un restart

};


//MENU 
void menu_principale();
void affichage_topscore(Plateau p, int tabScore[]);
int verif_score(int score, int niveau);
void dessiner_etoilescore(int tabScore[], int niveau, SDL_Rect position_etoile);
void test_survolement(SDL_Event event);
void animation_survolement(SDL_Rect recouvrement, int texture_survol);;

//FENETRE
void destroy();
int initialisation();

//CHARGEMENT
bool charger_plateau(Plateau& p, char* nom_fichier);
void charger_texture(SDL_Texture* texture[]);


//EN JEU
void afficher_plateau(Plateau& p);
void deplacement(SDL_Event event, Plateau& p);
void menu_information();
void bouton_menu_info();
void efface_menu(Plateau p);
void affichage_luffy(Plateau p);
void pop_up_victoire(bool& continuer_jeu);
void menu_echape(Plateau& p, bool& continue_jeu);

void loop_jeu(Plateau& plat, char* nom_niveau, bool& continuer_global);
void loop_echape(SDL_Event event, bool& continuer_jeu, Plateau& p, char* n_niveau);

//OUTILS
void Texte(SDL_Rect cadre, char chaine[], SDL_Color couleur, int taille);
void reset_plateau(Plateau& p);
void afficher_all(Plateau p);














