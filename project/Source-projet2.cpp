#include "Header_projet2.h";

int main(int argn, char* argv[]) {

	srand(time(NULL));
	initialisation();
	charger_texture(texture);
	menu_principale();

	
	int tabtopscore[8] = { 0,0, 0,0,0,0,0,0 };
	int tab_nombre_essaie[8] = { 0,0, 0,0,0,0,0,0 };
	int num_lvl = 0;
	SDL_Rect carre;
	Plateau plat;
	affichage_topscore(plat, tabtopscore);

	int taille_case_L = LARGEUR / plat.nombre_colonnes;
	int taille_case_H = HAUTEUR / plat.nombre_lignes;
	int largeur_niveau = LARGEUR / 20;
	int score = 0;
	char niveau[20];
	
	int texture_theme;
	int nombre_niveau = 2;


	//SDL_Rect rectangle = { LARGEUR / 3, HAUTEUR / 3, LARGEUR / 3, HAUTEUR / 3 };
	bool continuer = true;
	SDL_Event event;


	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			
			test_survolement(event);
			break;

		case SDL_QUIT:
			continuer = false;
			break;

			//nniveau = { largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3  - 10};
		case SDL_MOUSEBUTTONUP:
			if (event.button.x > largeur_niveau + 5 && event.button.x < largeur_niveau + 5 + 3 * largeur_niveau - 10
				&& event.button.y > HAUTEUR / 4 + 5 && event.button.y < HAUTEUR / 4 + 5 + (HAUTEUR / 3 - 10)) {

				num_lvl = 1;
				TEXTURE_VICTOIRE = 15;
				TEXTURE_THEME = 8;
				strcpy_s(niveau, 20, "Niveau1.txt");
				loop_jeu(plat, niveau, continuer);
				cout << " Nimbre de coups joué fin de loop : " << plat.nb_coups_joues << endl;

				if (tabtopscore[num_lvl - 1] > plat.nb_coups_joues && tab_nombre_essaie[num_lvl - 1] != 0 && plat.nb_point == plat.score) {
					tabtopscore[num_lvl - 1] = plat.nb_coups_joues;
				}

				else if (tab_nombre_essaie[num_lvl - 1] == 0 && plat.nb_point == plat.score) {
					tabtopscore[num_lvl - 1] = plat.nb_coups_joues;
				}
				if (plat.code_sortie == 0) {
					tab_nombre_essaie[num_lvl - 1] ++;
				}
				cout << " Nimbre de coups joué fin de loop (Record): " << tabtopscore[num_lvl - 1] << endl;
				reset_plateau(plat);
				
			}
			
			else if (event.button.x > 2 * largeur_niveau + 3 * largeur_niveau + 5 && event.button.x < 2 * largeur_niveau + 3 * largeur_niveau + 5 + 3 * largeur_niveau - 10
				&& event.button.y > HAUTEUR / 4 + 5 && event.button.y < HAUTEUR / 4 + 5 + (HAUTEUR / 3 - 10)) {

				num_lvl = 2;
				TEXTURE_VICTOIRE = 16;
				TEXTURE_THEME = 14;
				strcpy_s(niveau, 20, "Niveau2.txt");
				loop_jeu(plat, niveau, continuer);

				if (tabtopscore[num_lvl - 1] > plat.nb_coups_joues && tab_nombre_essaie[num_lvl - 1] != 0 && plat.nb_point == plat.score) {
					tabtopscore[num_lvl - 1] = plat.nb_coups_joues;
				}

				else if (tab_nombre_essaie[num_lvl - 1] == 0 && plat.nb_point == plat.score) {
					tabtopscore[num_lvl - 1] = plat.nb_coups_joues;
				}

				if (plat.code_sortie == 0) {
					tab_nombre_essaie[num_lvl - 1] ++;
				}
				cout << " Nimbre de coups joué fin de loop (Record): " << tabtopscore[num_lvl - 1] << endl;
				reset_plateau(plat);


			}

			menu_principale();
			affichage_topscore(plat, tabtopscore);
			SDL_RenderPresent(rendu);
			break;

		}
	}



	




	destroy();
	return 0;
}



int initialisation() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Echec à l’ouverture";
		return 1;
	}



	win = SDL_CreateWindow("JEU PAPA NOEL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		LARGEUR ,
		HAUTEUR,
		SDL_WINDOW_SHOWN
	);

	if (win == NULL)
		cout << "erreur ouverture fenetre";

	rendu = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED);


	SDL_RenderPresent(rendu);
}

void destroy() {
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

bool charger_plateau(Plateau& p, char* nom_fichier) {



	if (p.tableau != NULL) {
		for (int i = 0; i < p.nombre_lignes; i++) {
			delete[]p.tableau[i];
		}
		delete[]p.tableau;
		p.tableau = NULL;
	}


	ifstream niveau(nom_fichier, ios::in);


	niveau >> p.nombre_lignes;
	niveau >> p.nombre_colonnes;
	niveau >> p.bonhomme_i;
	niveau >> p.bonhomme_j;


	p.tableau = new TypeCase * [p.nombre_lignes];
	for (int i = 0; i < p.nombre_lignes; i++) {
		p.tableau[i] = new TypeCase[p.nombre_colonnes];
	}
	
	if (!niveau)
		return false;
	else {
		p.nombre_cases = 0;
		
		int type;
		for (int i = 0; i < p.nombre_lignes; i++) {
			for (int j = 0; j < p.nombre_colonnes; j++) {
				niveau >> type;
				switch (type) {
				case 0:
					p.tableau[i][j] = MUR;
					break;

				case 1:
					p.tableau[i][j] = CAISSE;
					p.nombre_cases++;
					
					break;

				case 2:
					p.tableau[i][j] = POINT;
					p.nombre_cases++;
					p.nb_point++;
					break;

				case 3:
					p.tableau[i][j] = SOL;
					p.nombre_cases++;
					break;
				}
			}
		}

		return true;
		niveau.close();

	}

}

void afficher_plateau(Plateau& p) {
	int taille_case_L = LARGEUR / p.nombre_colonnes;
	int taille_case_H = HAUTEUR / p.nombre_lignes;
	SDL_Rect carre;
	for (int i = 0; i < p.nombre_lignes; i++) {
		for (int j = 0; j < p.nombre_colonnes; j++) {
			carre = { j * taille_case_L, i * taille_case_H, taille_case_L, taille_case_H };
			
			switch (p.tableau[i][j])
			{

			case SOL:
				SDL_RenderCopy(rendu, texture[3], NULL, &carre);
				break;

			case MUR:
				SDL_RenderCopy(rendu, texture[0], NULL, &carre);
				break;

			case POINT:
				SDL_RenderCopy(rendu, texture[2], NULL, &carre);
				break;

			case CAISSE:
				SDL_RenderCopy(rendu, texture[1], NULL, &carre);
				break;

			case POINT_GAGNANT:
				SDL_RenderCopy(rendu, texture[TEXTURE_THEME], NULL, &carre);
				break;

			default:
				break;
			}

		}
	}
	if (p.nb_coups_joues == 0) {
		carre = { p.bonhomme_j * taille_case_L, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
		
		SDL_RenderCopy(rendu, texture[6], NULL, &carre);
		
	}

	
	
}

void charger_texture(SDL_Texture* texture[]) {

	texture[0] = loadImage(rendu, "Mur.png");
	texture[1] = loadImage(rendu, "caisse_p.jpg");
	texture[2] = loadImage(rendu, "point.png");
	texture[3] = loadImage(rendu, "Sol.jpg");
	texture[4] = loadImage(rendu, "luffy_01r.png"); //Courir-gauche
	texture[5] = loadImage(rendu, "luffy_02r.png"); //Courir-droite
	texture[6] = loadImage(rendu, "luffy_03r.png"); //Stable-droit
	texture[7] = loadImage(rendu, "luffy_04r.png"); //Stable-gauche
	texture[8] = loadImage(rendu, "francky.png"); // Franckyyyyyyyy
	texture[9] = loadImage(rendu, "bannire_bien.jpg"); // Bannière
	texture[10] = loadImage(rendu, "interog.png");
	texture[11] = loadImage(rendu, "fond_ecran.jpg"); 
	texture[12] = loadImage(rendu, "francky_wanted_rr.jpg");
	texture[13] = loadImage(rendu, "robin_wanted_r.jpg");
	texture[14] = loadImage(rendu, "robin.jpg");
	texture[15] = loadImage(rendu, "chibi_francky_rbg.png");
	texture[16] = loadImage(rendu, "chibi_robin.png");
	texture[17] = loadImage(rendu, "chopper.gif"); // Chop Sad
	texture[18] = loadImage(rendu, "chopper2.gif"); // Chop content
	texture[19] = loadImage(rendu, "1-remplie-etoile.png");
	texture[20] = loadImage(rendu, "2-remplie-etoile.png"); 
	texture[21] = loadImage(rendu, "3-remplie-etoile.png");
	texture[22] = loadImage(rendu, "vide-etoile.png");
	texture[23] = loadImage(rendu, "sanji_wanted.jpg");
	texture[24] = loadImage(rendu, "usopp_wanted.jpg");

}

void deplacement(SDL_Event event, Plateau& p) {
	
	
	int taille_case_L = LARGEUR / p.nombre_colonnes;
	int taille_case_H = HAUTEUR / p.nombre_lignes;
	
	SDL_Rect carre;
	SDL_Rect caisse;

	switch (event.key.keysym.sym)
	{
	case SDLK_DOWN:
		

		//BAS

		if ((p.tableau[p.bonhomme_i + 1][p.bonhomme_j] == MUR)
			|| (p.tableau[p.bonhomme_i + 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i + 2][p.bonhomme_j] == MUR)
			||(p.tableau[p.bonhomme_i + 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i + 2][p.bonhomme_j] == CAISSE)
			|| (p.tableau[p.bonhomme_i + 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i + 2][p.bonhomme_j] == POINT_GAGNANT)) {
			
			return;
		}

		else if (p.tableau[p.bonhomme_i + 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i + 2][p.bonhomme_j] == POINT) {
			
			p.tableau[p.bonhomme_i + 1][p.bonhomme_j] = SOL;
			p.nb_coups_joues++;
			p.score++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int y_bonhomme = p.bonhomme_i * taille_case_H;
			int y_caisse = (p.bonhomme_i + 1) * taille_case_H;
			int i_case_sui = (p.bonhomme_i + 1) * taille_case_H;

			while (y_bonhomme != i_case_sui) {
				y_bonhomme++; // AUGMENTER L'INCREMENTATION POUR AUGMENTER LA VITESSE DE L'ANIMATION, ( ex: x_bonhomme = x_bonhomme + 2 )
				y_caisse++;
				carre = { p.bonhomme_j * taille_case_L, y_bonhomme, taille_case_L, taille_case_H };
				caisse = { p.bonhomme_j * taille_case_L, y_caisse, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[7], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);
				

			}



			p.tableau[p.bonhomme_i + 2][p.bonhomme_j] = POINT_GAGNANT;
			p.bonhomme_i = p.bonhomme_i + 1;
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[7], NULL, &carre);
			SDL_RenderPresent(rendu);
			p.dir = BAS;
			
			
			
			
			

		}

		
		else if (p.tableau[p.bonhomme_i + 1][p.bonhomme_j] == CAISSE) {
			
			p.tableau[p.bonhomme_i + 1][p.bonhomme_j] = SOL;
			p.nb_coups_joues++;
			
			SDL_RenderClear(rendu);
			afficher_plateau(p);

			
			int y_bonhomme = p.bonhomme_i * taille_case_H;
			int y_caisse = (p.bonhomme_i + 1) * taille_case_H;
			int i_case_sui = (p.bonhomme_i + 1)* taille_case_H;
			
			while (y_bonhomme != i_case_sui) {
				y_bonhomme++; // AUGMENTER L'INCREMENTATION POUR AUGMENTER LA VITESSE DE L'ANIMATION, ( ex: x_bonhomme = x_bonhomme + 2 )
				y_caisse++;
				carre = { p.bonhomme_j * taille_case_L, y_bonhomme, taille_case_L, taille_case_H };
				caisse = { p.bonhomme_j * taille_case_L, y_caisse, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[7], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			p.tableau[p.bonhomme_i + 2][p.bonhomme_j] = CAISSE;
			p.bonhomme_i = p.bonhomme_i + 1;
			p.dir = BAS;
			
		}

		else {
			
			
			p.nb_coups_joues++;
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			

			
			int y_bonhomme = p.bonhomme_i * taille_case_H;
			int i_case_sui = (p.bonhomme_i + 1) * taille_case_H;
			

			while (y_bonhomme != i_case_sui) {
				y_bonhomme++;
				carre = { p.bonhomme_j * taille_case_L, y_bonhomme, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[7], NULL, &carre);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			p.bonhomme_i = p.bonhomme_i + 1;
			p.dir = BAS;
			
		}

		
		break;

		// GAUCHE
	case SDLK_LEFT:

		if ((p.tableau[p.bonhomme_i][p.bonhomme_j - 1] == MUR)
			|| (p.tableau[p.bonhomme_i][p.bonhomme_j - 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j - 2] == MUR)
			||(p.tableau[p.bonhomme_i][p.bonhomme_j - 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j - 2] == CAISSE)
			|| (p.tableau[p.bonhomme_i][p.bonhomme_j - 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j - 2] == POINT_GAGNANT)) {
			
			return;
		}

		else if (p.tableau[p.bonhomme_i][p.bonhomme_j - 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j - 2] == POINT) {

			p.tableau[p.bonhomme_i][p.bonhomme_j - 1] = SOL;
			p.nb_coups_joues++;
			p.score++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);


			int x_bonhomme = p.bonhomme_j * taille_case_L;
			int x_caisse = (p.bonhomme_j - 1) * taille_case_L;
			int j_case_sui = (p.bonhomme_j - 1) * taille_case_L;

			while (x_bonhomme != j_case_sui) {
				x_bonhomme--;
				x_caisse--;
				carre = { x_bonhomme, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				caisse = { x_caisse, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[4], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			p.tableau[p.bonhomme_i][p.bonhomme_j - 2] = POINT_GAGNANT;
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[7], NULL, &carre);
			SDL_RenderPresent(rendu);

			
			p.bonhomme_j = p.bonhomme_j - 1;
			p.dir = GAUCHE;
		}

		else if (p.tableau[p.bonhomme_i][p.bonhomme_j - 1] == CAISSE) {

			p.tableau[p.bonhomme_i][p.bonhomme_j - 1] = SOL;
			p.nb_coups_joues++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);
			

			int x_bonhomme = p.bonhomme_j * taille_case_L;
			int x_caisse = (p.bonhomme_j - 1) * taille_case_L;
			int j_case_sui = (p.bonhomme_j - 1) * taille_case_L;

			while (x_bonhomme != j_case_sui) {
				x_bonhomme--;
				x_caisse--;
				carre = { x_bonhomme, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				caisse = { x_caisse, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[4], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[7], NULL, &carre);
			SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
			SDL_RenderPresent(rendu);

			p.tableau[p.bonhomme_i][p.bonhomme_j - 2] = CAISSE;
			p.bonhomme_j = p.bonhomme_j - 1;
			p.dir = GAUCHE;
			
			
		}

		else {
			
			
			p.nb_coups_joues++;
			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int x_bonhomme = p.bonhomme_j * taille_case_L;
			int j_case_sui = (p.bonhomme_j - 1) * taille_case_L;

			while (x_bonhomme != j_case_sui) {
				x_bonhomme--;
				carre = { x_bonhomme, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H }; 
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[4], NULL, &carre);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[7], NULL, &carre);
			SDL_RenderPresent(rendu);

			p.bonhomme_j = p.bonhomme_j - 1;
			p.dir = GAUCHE;

			
		}
		
		break;

		//DROITE
	case SDLK_RIGHT:

		if ((p.tableau[p.bonhomme_i][p.bonhomme_j + 1] == MUR)
			|| (p.tableau[p.bonhomme_i][p.bonhomme_j + 1] == CAISSE && p.tableau[p.bonhomme_i ][p.bonhomme_j + 2] == MUR)
			||(p.tableau[p.bonhomme_i][p.bonhomme_j + 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j + 2] == CAISSE)
			|| (p.tableau[p.bonhomme_i][p.bonhomme_j + 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j + 2] == POINT_GAGNANT)) {
			
			return;
		}

		else if (p.tableau[p.bonhomme_i][p.bonhomme_j + 1] == CAISSE && p.tableau[p.bonhomme_i][p.bonhomme_j + 2] == POINT) {

			p.tableau[p.bonhomme_i][p.bonhomme_j + 1] = SOL;
			p.nb_coups_joues++;
			p.score++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int x_bonhomme = p.bonhomme_j * taille_case_L;
			int x_caisse = (p.bonhomme_j + 1) * taille_case_L;
			int j_case_sui = (p.bonhomme_j + 1) * taille_case_L;

			while (x_bonhomme != j_case_sui) {
				x_bonhomme++;
				x_caisse++;
				carre = { x_bonhomme, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				caisse = { x_caisse, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[5], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			p.tableau[p.bonhomme_i][p.bonhomme_j + 2] = POINT_GAGNANT;
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[6], NULL, &carre);
			SDL_RenderPresent(rendu);


			
			p.bonhomme_j = p.bonhomme_j + 1;
			p.dir = DROITE;

		}

		else if (p.tableau[p.bonhomme_i][p.bonhomme_j + 1] == CAISSE) {

			p.tableau[p.bonhomme_i][p.bonhomme_j + 1] = SOL;
			p.nb_coups_joues++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int x_bonhomme = p.bonhomme_j * taille_case_L;
			int x_caisse = (p.bonhomme_j + 1) * taille_case_L;
			int j_case_sui = (p.bonhomme_j + 1) * taille_case_L;

			while (x_bonhomme != j_case_sui) {
				x_bonhomme++;
				x_caisse++;
				carre = { x_bonhomme, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				caisse = { x_caisse, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[5], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}
			

			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[6], NULL, &carre);
			SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
			SDL_RenderPresent(rendu);

			p.tableau[p.bonhomme_i][p.bonhomme_j + 2] = CAISSE;
			p.bonhomme_j = p.bonhomme_j + 1;
			p.dir = DROITE;

			
		}

		else {
			
			p.nb_coups_joues++;
			
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			int x_bonhomme = p.bonhomme_j * taille_case_L;
			int j_case_sui = (p.bonhomme_j + 1) * taille_case_L;
			

			while (x_bonhomme != j_case_sui) {
				x_bonhomme++;
				carre = { x_bonhomme, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[5], NULL, &carre);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			SDL_RenderClear(rendu);
			afficher_plateau(p);
			bouton_menu_info();
			SDL_RenderCopy(rendu, texture[6], NULL, &carre);
			SDL_RenderPresent(rendu);

			p.bonhomme_j = p.bonhomme_j + 1;
			p.dir = DROITE;
		}
		
		
		break;

		//HAUT
	case SDLK_UP:

		if ((p.tableau[p.bonhomme_i - 1][p.bonhomme_j] == MUR)
			|| (p.tableau[p.bonhomme_i - 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i - 2][p.bonhomme_j] == MUR)
			||(p.tableau[p.bonhomme_i - 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i - 2][p.bonhomme_j] == CAISSE)
			|| (p.tableau[p.bonhomme_i - 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i - 2][p.bonhomme_j] == POINT_GAGNANT)) {
			
			return;
		}
		
		else if (p.tableau[p.bonhomme_i - 1][p.bonhomme_j] == CAISSE && p.tableau[p.bonhomme_i - 2][p.bonhomme_j] == POINT) {

			p.tableau[p.bonhomme_i - 1][p.bonhomme_j] = SOL;
			p.nb_coups_joues++;
			p.score++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int y_bonhomme = p.bonhomme_i * taille_case_H;
			int y_caisse = (p.bonhomme_i - 1) * taille_case_H;
			int i_case_sui = (p.bonhomme_i - 1) * taille_case_H;

			while (y_bonhomme != i_case_sui) {
				y_bonhomme--;
				y_caisse--;
				carre = { p.bonhomme_j * taille_case_L, y_bonhomme, taille_case_L, taille_case_H };
				caisse = { p.bonhomme_j * taille_case_L, y_caisse, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[6], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}



			p.tableau[p.bonhomme_i - 2][p.bonhomme_j] = POINT_GAGNANT;
			p.bonhomme_i = p.bonhomme_i - 1;
			SDL_RenderClear(rendu);
			afficher_plateau(p);
			SDL_RenderCopy(rendu, texture[6], NULL, &carre);
			SDL_RenderPresent(rendu);
			p.dir = HAUT;

			
			

		}

		else if (p.tableau[p.bonhomme_i - 1][p.bonhomme_j] == CAISSE) {


			p.tableau[p.bonhomme_i - 1][p.bonhomme_j] = SOL;
			p.nb_coups_joues++;

			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int y_bonhomme = p.bonhomme_i * taille_case_H;
			int y_caisse = (p.bonhomme_i - 1) * taille_case_H;
			int i_case_sui = (p.bonhomme_i - 1) * taille_case_H;

			while (y_bonhomme != i_case_sui) {
				y_bonhomme--;
				y_caisse--;
				carre = { p.bonhomme_j * taille_case_L, y_bonhomme, taille_case_L, taille_case_H };
				caisse = { p.bonhomme_j * taille_case_L, y_caisse, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[6], NULL, &carre);
				SDL_RenderCopy(rendu, texture[1], NULL, &caisse);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}

			SDL_RenderCopy(rendu, texture[6], NULL, &carre);
			SDL_RenderPresent(rendu);

			p.tableau[p.bonhomme_i - 2][p.bonhomme_j] = CAISSE;
			p.bonhomme_i = p.bonhomme_i - 1;
			p.dir = HAUT;
			
		}

		else {
			
			p.nb_coups_joues++;
			
			SDL_RenderClear(rendu);
			afficher_plateau(p);

			int x_bonhomme = p.bonhomme_i * taille_case_H;
			int i_case_sui = (p.bonhomme_i - 1) * taille_case_H;

			while (x_bonhomme != i_case_sui) {

				x_bonhomme--; 
				carre = { p.bonhomme_j * taille_case_L, x_bonhomme, taille_case_L, taille_case_H };
				SDL_RenderClear(rendu);
				afficher_plateau(p);
				SDL_RenderCopy(rendu, texture[6], NULL, &carre);
				bouton_menu_info();
				SDL_RenderPresent(rendu);

			}


			p.bonhomme_i = p.bonhomme_i - 1;
			p.dir = HAUT;

			
		}
		
		break;
	default:
		break;
	}

	cout << " direction : " << p.dir << endl;
}

void bouton_menu_info() {
	SDL_Rect rectangle{ 10,10,50,50 };
	SDL_RenderCopy(rendu, texture[10], NULL, &rectangle);
	
}

void menu_information() {
	

	SDL_Rect menu_ext = { 60,60, LARGEUR / 5, HAUTEUR / 2 + 50 };
	SDL_Rect menu_int = { 65, 65, LARGEUR / 5 - 10, HAUTEUR / 2 + 50 - 10 };

	SDL_RenderFillRect(rendu, &menu_ext);
	SDL_RenderCopy(rendu, texture[9], NULL, &menu_int);
	
	

}

void efface_menu(Plateau p) {
	
	SDL_RenderClear(rendu);
	afficher_plateau(p);
	affichage_luffy(p);

	
	
	

}

void affichage_luffy(Plateau p) {
	int taille_case_L = LARGEUR / p.nombre_colonnes;
	int taille_case_H = HAUTEUR / p.nombre_lignes;

	SDL_Rect carre = { p.bonhomme_j * taille_case_L, p.bonhomme_i * taille_case_H, taille_case_L, taille_case_H };

	switch (p.dir)
	{

	case HAUT:

		SDL_RenderCopy(rendu, texture[6], NULL, &carre);
		break;

	case BAS:

		SDL_RenderCopy(rendu, texture[7], NULL, &carre);
		break;

	case DROITE:

		SDL_RenderCopy(rendu, texture[6], NULL, &carre);
		break;

	case GAUCHE:

		SDL_RenderCopy(rendu, texture[7], NULL, &carre);
		break;

	default:
		break;
	}
}

void menu_principale() {
	SDL_RenderClear(rendu);
	int largeur_niveau = LARGEUR / 20;
	SDL_Rect fond = { 0,0, LARGEUR, HAUTEUR };
	SDL_Rect rectangle = { LARGEUR / 3, HAUTEUR / 3, LARGEUR / 3, HAUTEUR / 3 };
	SDL_Rect niveau;
	SDL_Rect Affiche;

	SDL_SetRenderDrawColor(rendu, 142, 71, 2, 255);
	SDL_RenderFillRect(rendu, &fond);
	fond = { 10,10, LARGEUR - 20, HAUTEUR - 20 };
	SDL_RenderCopy(rendu, texture[11], NULL, &fond);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 130);
	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(rendu, &fond);


	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
	niveau = { largeur_niveau, HAUTEUR / 4, 3*largeur_niveau, HAUTEUR / 3 };
	SDL_RenderFillRect(rendu, &niveau);
	niveau = { largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3  - 10};
	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &niveau);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderCopy(rendu, texture[12], NULL, &niveau);
	

	niveau = { 2*largeur_niveau + 3 * largeur_niveau, HAUTEUR / 4, 3 * largeur_niveau, HAUTEUR / 3 };
	SDL_RenderFillRect(rendu, &niveau);
	niveau = { 2 * largeur_niveau + 3 * largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 -10};
	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &niveau);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderCopy(rendu, texture[13], NULL, &niveau);

	//NIVEAU 3 SANJI
	niveau = {LARGEUR - (largeur_niveau + (3 * largeur_niveau)), HAUTEUR / 4, 3 * largeur_niveau, HAUTEUR / 3 };
	SDL_RenderFillRect(rendu, &niveau);
	niveau = { LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 -10};
	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &niveau);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderCopy(rendu, texture[23], NULL, &niveau);


	//NIVEAU 4 USOPP
	niveau = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)), HAUTEUR / 4, 3 * largeur_niveau, HAUTEUR / 3  };
	SDL_RenderFillRect(rendu, &niveau);
	niveau = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau -10, HAUTEUR / 3 -10};
	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &niveau);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderCopy(rendu, texture[24], NULL, &niveau);


}

void loop_jeu(Plateau& plat, char* nom_niveau, bool& continuer_global ) {

	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderClear(rendu);
	
	charger_plateau(plat, nom_niveau);
	cout << "nombre de point = " << plat.nb_point << endl;
	afficher_plateau(plat);
	bouton_menu_info();
	SDL_RenderPresent(rendu);

	SDL_Event event;
	bool continuer_jeu = true;
	while (continuer_jeu) {
		SDL_WaitEvent(&event);
		
		switch (event.type)
		{
		case SDL_QUIT:
			continuer_jeu = false;
			continuer_global = false;
			break;

		case SDL_MOUSEMOTION:

			
			if (event.motion.x > 10 && event.motion.x < 60 && event.motion.y > 10 && event.motion.y < 60) {
				int verif = 0;

				menu_information();
				bouton_menu_info();
				SDL_RenderPresent(rendu);
				SDL_PollEvent(&event);
				while (verif != 1) {
					event.type = SDL_MOUSEBUTTONDOWN;
					SDL_PollEvent(&event);

					if (event.type == SDL_MOUSEMOTION) {
						if (event.motion.x > 10 && event.motion.x < 60 && event.motion.y > 10 && event.motion.y < 60) {
							cout << "ez" << endl;
						}
						else {
							efface_menu(plat);
							SDL_RenderPresent(rendu);
							cout << "SORTIE DE LA BOUCLE" << endl;
							verif = 1;
						}
					}
					cout << "RETOUR HAUT DE LA BOUCLE" << endl;
				}
			}

			else {
				afficher_all(plat);
				SDL_RenderPresent(rendu);

			}

			break;

		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_ESCAPE) {
				cout << "------------------------" << endl;
				cout << "Escape" << endl;
				menu_echape(plat, continuer_jeu);
				loop_echape(event, continuer_jeu, plat, nom_niveau);

			}

			deplacement(event, plat);
			cout << "-------------------------" << endl;
			cout << "Nombre de coup = " << plat.nb_coups_joues << endl;
			cout << "-------------------------" << endl;
			break;


		}

		if (plat.score == plat.nb_point) {

			pop_up_victoire(continuer_jeu);

		}


	}
}

void pop_up_victoire(bool& continuer) {

	continuer = false;
	SDL_Color Blanc = { 0, 210, 243 };
	char chaine[10] = "Victoire";
	SDL_Rect pop_up = { LARGEUR / 3, HAUTEUR / 6, LARGEUR / 3, HAUTEUR / 2 };
	SDL_RenderCopy(rendu, texture[TEXTURE_VICTOIRE], NULL, &pop_up);
	

	SDL_Rect Victoire = { LARGEUR / 3 - 50 , HAUTEUR / 6 + HAUTEUR / 2 + 20, LARGEUR / 3 + 100, 150 };

	
	

	Texte(Victoire, chaine, Blanc, 150);

	SDL_RenderPresent(rendu);
	SDL_Delay(4000);
}

void Texte(SDL_Rect cadre, char chaine[], SDL_Color couleur, int taille) {

	TTF_Init();
	int tempo;
	TTF_Font* font = TTF_OpenFont("one piece font.ttf", taille);
	SDL_Texture* texture = loadText(rendu, chaine, couleur, font);
	SDL_QueryTexture(texture, NULL, NULL, &cadre.w, &cadre.h);
	SDL_SetRenderDrawColor(rendu, couleur.r, couleur.g, couleur.b, 255);
	tempo = cadre.x;
	cadre.x = cadre.x + cadre.w/5;

	

	SDL_RenderCopy(rendu, texture, NULL, &cadre);
	cadre.x = tempo;
	
}

void affichage_topscore(Plateau p, int tabScore[]) {
	
	int largeur_niveau = LARGEUR / 20;
	
	char chaine2[15] = "Coups";
	char score_c[5];
	int topscore = p.nb_coups_joues;
	
	SDL_Color Bleu = { 0, 210, 243 };
	//niveau = {LARGEUR - (largeur_niveau + (3 * largeur_niveau)), HAUTEUR / 4, 3 * largeur_niveau, HAUTEUR / 3 };
	//niveau = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)), HAUTEUR / 4, 3 * largeur_niveau, HAUTEUR / 3  };
	SDL_Rect Etoile_niveau1 = { largeur_niveau + (largeur_niveau * 3)/8,  HAUTEUR / 4 + HAUTEUR / 3 + HAUTEUR/ 30, 3 * ((largeur_niveau * 3)/4), HAUTEUR/20 };
	SDL_Rect Etoile_niveau2 = { 2 * largeur_niveau + 3 * largeur_niveau + (largeur_niveau * 3) / 8 , HAUTEUR / 4 + HAUTEUR / 3 + HAUTEUR / 30 , 3 * ((largeur_niveau * 3) / 4) , HAUTEUR / 20 };
	SDL_Rect Etoile_niveau3 = { LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + (largeur_niveau * 3) / 8,  HAUTEUR / 4 + HAUTEUR / 3 + HAUTEUR / 30, 3 * ((largeur_niveau * 3) / 4), HAUTEUR / 20 };
	SDL_Rect Etoile_niveau4 = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + (largeur_niveau * 3) / 8,  HAUTEUR / 4 + HAUTEUR / 3 + HAUTEUR / 30, 3 * ((largeur_niveau * 3) / 4), HAUTEUR / 20 };


	SDL_Rect score = {2 * largeur_niveau - 55, HAUTEUR / 4 + HAUTEUR / 3 ,largeur_niveau , (HAUTEUR / 3 )/6};	

	//Niveau 0 = Niveau 1; Niveau 1 = Niveau 2; .......
	
	dessiner_etoilescore(tabScore, 0, Etoile_niveau1);
	dessiner_etoilescore(tabScore, 1, Etoile_niveau2);
	dessiner_etoilescore(tabScore, 2, Etoile_niveau3);
	dessiner_etoilescore(tabScore, 3, Etoile_niveau4);
	

	SDL_RenderPresent(rendu);

}

void reset_plateau(Plateau& p) {
	
	
	p.nb_coups_joues = 0;
	p.code_sortie = 0;
	p.score = 0;
	p.nb_point = 0;
	


}

void menu_echape(Plateau& p, bool& continue_jeu ) {
	SDL_Event event;
	bool continuer_echape = true ;
	char chaine[15];
	//SDL_Color Blanc = { 0, 215, 237 };
	SDL_Color Blanc = { 255, 255, 255 };
	SDL_Rect Noir = { 0,0,LARGEUR, HAUTEUR };
	SDL_Rect Quit = { (LARGEUR / 8) * 3, 3 * (HAUTEUR / 10), (LARGEUR / 8) * 2,	HAUTEUR / 8 };
	SDL_Rect Restart = { (LARGEUR / 8) * 3, 5 * (HAUTEUR / 10)  , (LARGEUR / 8) * 2,HAUTEUR / 8 };
	SDL_Rect Restart_T = { (LARGEUR / 8) * 3 + (LARGEUR/62), 5 * (HAUTEUR / 10)  , (LARGEUR / 8) * 2,HAUTEUR / 8 };

	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 150);
	SDL_RenderFillRect(rendu, &Noir);

	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &Quit);
	Quit = { (LARGEUR / 8) * 3 + 5, 3 * (HAUTEUR / 10) + 5, (LARGEUR / 8) * 2 - 10,	HAUTEUR / 8 - 10 };
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderCopy(rendu, texture[18], NULL, &Quit);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 50);
	SDL_RenderFillRect(rendu, &Quit);
	
	strcpy_s(chaine, 15, "Quitter");
	Texte(Quit, chaine, Blanc, 80);


	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &Restart);
	Restart = { (LARGEUR / 8) * 3 + 5, 5 * (HAUTEUR / 10) +5 , (LARGEUR / 8) * 2 - 10,HAUTEUR / 8 - 10 };
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderCopy(rendu, texture[18], NULL, &Restart);
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 50);
	SDL_RenderFillRect(rendu, &Restart);

	strcpy_s(chaine, 15, "Rejouer");
	Texte(Restart_T, chaine, Blanc, 80);

	SDL_RenderPresent(rendu);


	
	return;
	
}

void loop_echape(SDL_Event event, bool& continuer_jeu, Plateau& p, char* n_niveau) {
	SDL_Rect Quit = { (LARGEUR / 8) * 3 + 5, 3 * (HAUTEUR / 10) + 5, (LARGEUR / 8) * 2 - 10,	HAUTEUR / 8 - 10 };
	SDL_Rect Restart = { (LARGEUR / 8) * 3 + 5, 5 * (HAUTEUR / 10) + 5 , (LARGEUR / 8) * 2 - 10,HAUTEUR / 8 - 10 };
	SDL_Rect Restart_T = { (LARGEUR / 8) * 3 + (LARGEUR / 62), 5 * (HAUTEUR / 10)  , (LARGEUR / 8) * 2,HAUTEUR / 8 };
	//SDL_Color Blanc = { 0, 215, 237 };
	SDL_Color Blanc = { 255, 255, 255 };
	char chaine[15];
	bool continuer = true;
	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type)
		{

		case SDL_MOUSEMOTION:
			if (event.motion.x > (LARGEUR / 8) * 3 + 5 && event.motion.x < (LARGEUR / 8) * 3 + 5 + (LARGEUR / 8) * 2 - 10
				&& event.motion.y > 3 * (HAUTEUR / 10) + 5 && event.motion.y < 3 * (HAUTEUR / 10) + 5 + HAUTEUR / 8) {
				SDL_RenderCopy(rendu, texture[17], NULL, &Quit);
				
				SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(rendu, 0, 0, 0, 100);
				SDL_RenderFillRect(rendu, &Quit);
				strcpy_s(chaine, 15, "Quitter");
				Texte(Quit, chaine, Blanc, 80);
				SDL_RenderPresent(rendu);
				SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
				SDL_RenderCopy(rendu, texture[17], NULL, &Quit);
				

			}

			else if (event.motion.x > (LARGEUR / 8) * 3 + 5 && event.motion.x < (LARGEUR / 8) * 3 + 5 + (LARGEUR / 8) * 2 - 10
				&& event.motion.y > 5 * (HAUTEUR / 10) + 5 && event.motion.y < 5 * (HAUTEUR / 10) + 5 + HAUTEUR / 8) {
				SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(rendu, 0, 0, 0, 120);
				SDL_RenderFillRect(rendu, &Restart);
				strcpy_s(chaine, 15, "Rejouer");
				Texte(Restart_T, chaine, Blanc, 80);
				SDL_RenderPresent(rendu);
				SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
				SDL_RenderCopy(rendu, texture[18], NULL, &Restart);
				}

			else {

				
				SDL_RenderCopy(rendu, texture[18], NULL, &Quit);
				SDL_SetRenderDrawColor(rendu, 0, 0, 0, 50);
				SDL_RenderFillRect(rendu, &Quit);

				SDL_RenderCopy(rendu, texture[18], NULL, &Restart);
				SDL_SetRenderDrawColor(rendu, 0, 0, 0, 50);
				SDL_RenderFillRect(rendu, &Restart);

				strcpy_s(chaine, 15, "Quitter");
				Texte(Quit, chaine, Blanc, 80);
				strcpy_s(chaine, 15, "Rejouer");
				Texte(Restart_T, chaine, Blanc, 80);
				SDL_RenderPresent(rendu);
			}

			break;

		case SDL_MOUSEBUTTONUP:
			
			if (event.button.x > (LARGEUR / 8) * 3 + 5 && event.button.x < (LARGEUR / 8) * 3 + 5 + (LARGEUR / 8) * 2 - 10
				&& event.button.y > 3 * (HAUTEUR / 10) + 5 && event.button.y < 3 * (HAUTEUR / 10) + 5 + HAUTEUR / 8) {

				continuer = false;
				continuer_jeu = false;
				p.code_sortie = 1; // La sortie se fait par le menu et non pas par une victoire

			}

			//RESTART
			else if (event.button.x > (LARGEUR / 8) * 3 + 5 && event.button.x < (LARGEUR / 8) * 3 + 5 + (LARGEUR / 8) * 2 - 10
				&& event.button.y > 5 * (HAUTEUR / 10) + 5 && event.button.y < 5 * (HAUTEUR / 10) + 5 + HAUTEUR / 8) {

				reset_plateau(p);
				charger_plateau(p, n_niveau	);
				afficher_all(p);
				SDL_RenderPresent(rendu);
				continuer = false;

			}
			break;

		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_ESCAPE) {
				continuer = false;
				afficher_all(p);
				SDL_RenderPresent(rendu);
			}
			break;


		default:

			break;
		}
	}


	
}

void afficher_all(Plateau p) {

	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderClear(rendu);
	afficher_plateau(p);
	bouton_menu_info();
	affichage_luffy(p);

}

int verif_score(int score, int niveau) { // Decide du nombre d'étoile à mettre en fonction du nombre de coup joués ( SCORE );


	switch (niveau)
	{ 
	case 0: // Test du niveau 1

		if (score == 27) {
			return 3;
		}

		else if (score > 27 && score <= 45) {
			return 2;
		}

		else if (score > 45) {
			return 1;
		}

		else {
			return 0;
		}

		break;

	case 1: // Test du niveau 2

		// Record sur le niveau 2 = 77:
		if (score == 83 || score < 83 && score != 0) { 
			return 3;
		}

		else if (score > 83 && score <= 110) {
			return 2;
		}

		else if (score > 110) {
			return 1;
		}

		else {
			return 0;
		}

		break;

	case 2: // Test du niveau 3

		if (score == 83 || score < 83 && score != 0) {
			return 3;
		}

		else if (score > 83 && score <= 110) {
			return 2;
		}

		else if (score > 110) {
			return 1;
		}

		else {
			return 0;
		}

		break;

	case 3:  // Test du niveau 4

		if (score == 83 || score < 83 && score != 0) {
			return 3;
		}

		else if (score > 83 && score <= 110) {
			return 2;
		}

		else if (score > 110) {
			return 1;
		}

		else {
			return 0;
		}

		break;

	default:
		break;
	}
}

void dessiner_etoilescore(int tabScore[], int niveau, SDL_Rect position_etoile) { // Dessine les étoile en appellant la fonction verif_score 
																				  // qui elle verifie le nombre d'étoile à afficher

	int nbr_etoile;

	nbr_etoile = verif_score(tabScore[niveau], niveau);

	switch (nbr_etoile)
	{

	case 0:
		SDL_RenderCopy(rendu, texture[22], NULL, &position_etoile);
		break;

	case 3:
		SDL_RenderCopy(rendu, texture[21], NULL, &position_etoile);
		break;

	case 2:
		SDL_RenderCopy(rendu, texture[20], NULL, &position_etoile);
		break;

	case 1:
		SDL_RenderCopy(rendu, texture[19], NULL, &position_etoile);
		break;

	default:
		break;
	}
}

void test_survolement(SDL_Event event) {

	int largeur_niveau = LARGEUR / 20;


	if (event.motion.x > largeur_niveau + 5 && event.motion.x < largeur_niveau + 5 + 3 * largeur_niveau - 10
		&& event.motion.y > HAUTEUR / 4 + 5 && event.motion.y < HAUTEUR / 4 + 5 + HAUTEUR / 3 - 10) {

		//Survolement lvl 1
		SDL_Rect recouvrement = { largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		animation_survolement(recouvrement, 12);

	}

	else if (event.motion.x > 2 * largeur_niveau + 3 * largeur_niveau + 5 && event.motion.x < 2 * largeur_niveau + 3 * largeur_niveau + 5 + 3 * largeur_niveau - 10
		&& event.motion.y > HAUTEUR / 4 + 5 && event.motion.y < HAUTEUR / 4 + 5 + HAUTEUR / 3 - 10) {

		//Survolement lvl 2
		SDL_Rect recouvrement = { 2 * largeur_niveau + 3 * largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		animation_survolement(recouvrement, 13);
	}

	//niveau = {LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 -10
	else if (event.motion.x > LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + 5 && event.motion.x < LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + 5 + 3 * largeur_niveau - 10
		&& event.motion.y > HAUTEUR / 4 + 5 && event.motion.y < HAUTEUR / 4 + 5 + HAUTEUR / 3 - 10) {

		//Survolement lvl 3
		SDL_Rect recouvrement = { LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		animation_survolement(recouvrement, 23);
	}

	//niveau = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau -10, HAUTEUR / 3 -10};
	else if (event.motion.x > LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + 5 && event.motion.x < LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + 5 + 3 * largeur_niveau - 10
		&& event.motion.y > HAUTEUR / 4 + 5 && event.motion.y < HAUTEUR / 4 + 5 + HAUTEUR / 3 - 10) {

		//Survolement lvl 4
		SDL_Rect recouvrement = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		animation_survolement(recouvrement, 24);

	}

	else {
		SDL_Rect recouvrement = { largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		SDL_RenderCopy(rendu, texture[12], NULL, &recouvrement);
		recouvrement = { 2 * largeur_niveau + 3 * largeur_niveau + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		SDL_RenderCopy(rendu, texture[13], NULL, &recouvrement);
		recouvrement = { LARGEUR - (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		SDL_RenderCopy(rendu, texture[23], NULL, &recouvrement);
		recouvrement = { LARGEUR - 2 * (largeur_niveau + (3 * largeur_niveau)) + 5, HAUTEUR / 4 + 5, 3 * largeur_niveau - 10, HAUTEUR / 3 - 10 };
		SDL_RenderCopy(rendu, texture[24], NULL, &recouvrement);

		SDL_RenderPresent(rendu);
	}

}

void animation_survolement(SDL_Rect recouvrement, int texture_survol){
	SDL_Color couleur = { 255,255,255 };

	char chaine[15] = "Niveau 1";
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 180);
	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(rendu, &recouvrement);

	SDL_RenderPresent(rendu);
	SDL_RenderCopy(rendu, texture[texture_survol], NULL, &recouvrement);
	
}