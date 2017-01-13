﻿#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <mutex>
#include <thread>
#include <chrono>
//#include <stdlib.h>


using namespace std;
std::thread;
mutex perma;

#define ARRIBA     72      // CONSTANTS AMB LES FLETXES DEL TECLAT
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13

int backcolor = 0;
int dir = 0;
int x = 39, y = 22;
int anteriorpx, anteriorpy;

long int punts = 0;
int vides = 3;
int metas = 1;

void setCColor(int color)
{
	static HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color | (backcolor * 0x10 + 0x100));
}

int color[7] = {
	0x009,
	0x00E,
	0x00C,
	0x002,
	0x00B,
	0x005,
	0x00F
};

struct fantasma {
	int fdir; //direcció del fantasma que pot prendre valors del 0-3 i pot ser inicialitzat rand() % 4
	int _x, _y; // posicíó del fantasma
	int col; //color del fantasma
};

void gotoxy(int x, int y)  // funcio que posiciona el cursor a la coordenada (x,y)
{
	HANDLE hCon;
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

char mapa[50][100] = {
	"                                                      ",
	"                  AXXXXXXXXXXXXXXXXXXXB AXXXXXXXXXXXXXXXXXXXB",
	"                  Y___________________Y Y___________________Y",
	"                  Y_AXXXXXB_AXXXXXXXB_Y Y_AXXXXXXXB_AXXXXXB_Y",
	"                  Y_Y     Y_Y       Y_Y Y_Y       Y_Y     Y_Y",
	"                  Y_DXXXXXC_DXXXXXXXC_DXC_DXXXXXXXC_DXXXXXC_Y",
	"                  Y________|_________|___|_________|________Y",
	"                  Y_AXXXXXB_AXB_AXXXXXXXXXXXXXB_AXB_AXXXXXB_Y",
	"                  Y_DXXXXXC_Y Y_DXXXXB   AXXXXC_Y Y_DXXXXXC_Y",
	"                  Y_________Y Y______Y   Y______Y Y_________Y",
	"                  DXXXXXXXB_Y DXXXXB_Y   Y_AXXXXC Y_AXXXXXXXC",
	"                          Y_Y AXXXXC_DXXXC_DXXXXB Y_Y        ",
	"                          Y_Y Y_________________Y Y_Y        ",
	"                  XXXXXXXXC_DXC_AXXXXXX XXXXXXB_DXC_DXXXXXXXX",
	"                  P________|____Y      *      Y____|________P",
	"                  XXXXXXXXB_AXB_DXXXXXXXXXXXXXC_AXB_AXXXXXXXX",
	"                          Y_Y Y_________________Y Y_Y        ",
	"                          Y_Y Y_AXXXXXXXXXXXXXB_Y Y_Y        ",
	"                  AXXXXXXXC_DXC_DXXXXB   AXXXXC_DXC_DXXXXXXXB",
	"                  Y________|_________Y   Y_________|________Y",
	"                  Y_AXXXXXB_AXXXXXXB_Y   Y_AXXXXXXB_AXXXXXB_Y",
	"                  Y_DXXXB Y_DXXXXXXC_DXXXC_DXXXXXXC_Y AXXXC_Y",
	"                  Y_____Y Y_________|_____|_________Y Y_____Y",
	"                  DXXXB_Y Y_AXB_AXXXXXXXXXXXXXB_AXB_Y Y_AXXXC",
	"                  AXXXC_DXC_Y Y_DXXXXB   AXXXXC_Y Y_DXC_DXXXB",
	"                  Y_________Y Y______Y   Y______Y Y_________Y",
	"                  Y_AXXXXXXXC DXXXXB_Y   Y_AXXXXC DXXXXXXXB_Y",
	"                  Y_DXXXXXXXXXXXXXXC_DXXXC_DXXXXXXXXXXXXXXC_Y",
	"                  Y_________________|_____|_________________Y",
	"                  DXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXC",
};


void pintar_mapa()// Funcio que imprimeix el mapa basant-se en el mapa codificat
{
	for (int i = 0; i < 78; i++) {
		for (int j = 0; j < 30; j++) {
			gotoxy(i, j);

			if (mapa[j][i] == 'X') {
				setCColor(color[0]);
				printf("%c", 205);
			}
			if (mapa[j][i] == '_') {
				setCColor(color[1]);
				printf("%c", 250);
			}
			else if (mapa[j][i] == 'Y') {
				setCColor(color[0]);
				printf("%c", 186);
			}
			else if (mapa[j][i] == 'A') {
				setCColor(color[0]);
				printf("%c", 201);
			}
			else if (mapa[j][i] == 'B') {
				setCColor(color[0]);
				printf("%c", 187);
			}
			else if (mapa[j][i] == 'C') {
				setCColor(color[0]);
				printf("%c", 188);
			}
			else if (mapa[j][i] == 'D') {
				setCColor(color[0]);
				printf("%c", 200);
			}


		}
	}
}

void Input() {
	if (_kbhit()) {						//Si hay un input:
		char tecla = _getch();			//Se mira que valor de la tecla corresponde.
		switch (tecla) {
		case ARRIBA:
			dir = 0;
			break;

		case ABAJO:
			dir = 1;
			break;

		case DERECHA:
			dir = 2;
			break;

		case IZQUIERDA:
			dir = 3;
			break;
		}
	}

}


bool hayPunto(int x, int y) {
	if (mapa[y][x] == '_') {
		return true;
	}
	return false;

}


void pintarPacman(int x, int y) {
	setCColor(color[1]);					//COLOR AMARILLO
	gotoxy(x, y);							//PONGO EL CURSOR EN EL SITIO CORRESPONGIENTRE
	printf("%c", 6);						//PRINTEO EL CHAR DE PAC-MAN -> En el enunciado pone el 6 aunque las vidas es el 2 KEK

											//TODO imprimir el caracter amb codi ASCII 6
}

void borrarPacman(int x, int y) {
	gotoxy(x, y);							//PONGO EL CURSOR DONDE ESTA EL PAC-MAN PARA PODER SUBSTITUIRLO POR UN VACIO.
	printf("%c", 32);							//PONGO UN VACIO.
	mapa[y][x] = ' ';
}

void UpdatePuntos(int puntos) {
	perma.lock();
	punts += puntos;
	perma.unlock();

	if (punts == 25 * metas) {
		perma.lock();
		vides++;
		perma.unlock();
		metas++;
	}
}

void moverPacman()
{
	//Esborrar el pacman de l'anterior posició i imprimir-lo en la nova
	borrarPacman(x, y);
	Input();

	//Guardar la posició anterior del pacman
	anteriorpx = x;
	anteriorpy = y;

	//Detectar cap a on moure pacman
	//Comprovar si es pot moure en aquesta direcció
	switch (dir) {
	case 0: //arriba
		if (mapa[y - 1][x] == '_' || mapa[y - 1][x] == '|' || mapa[y - 1][x] == ' ') {
			perma.lock();
			y--;
			perma.unlock();
		}

		break;

	case 1: //abajo
		if (mapa[y + 1][x] == '_' || mapa[y + 1][x] == '|' || mapa[y + 1][x] == ' ') {
			perma.lock();
			y++;
			perma.unlock();
		}

		break;

	case 2: //derecha
		if (mapa[y][x + 1] == '_' || mapa[y][x + 1] == '|' || mapa[y][x + 1] == ' ') {
			perma.lock();
			x++;
			perma.unlock();
		}
		else if (mapa[y][x + 1] == 'P') {
			perma.lock();
			x = 19;
			y = 14;
			perma.unlock();
		}

		break;

	case 3: //izquierda
		if (mapa[y][x - 1] == '_' || mapa[y][x - 1] == '|' || mapa[y][x - 1] == ' ') {
			perma.lock();
			x--;
			perma.unlock();
		}
		else if (mapa[y][x - 1] == 'P') {
			perma.lock();
			x = 59;
			y = 14;
			perma.unlock();
		}

		break;

	}

	if (hayPunto(x, y)) {
		UpdatePuntos(5);
		if (punts) {

		}
	}
	//pintarPacman(x, y);
	thread(pintarPacman, x, y).join();
}


fantasma inicialitzarFantasma(int x, int y, int color) {
	static fantasma prov;		//Creo un objeto estatico de manera a que solo se cree una sola vez y poder cambiar sus variables cada vez que se cree un fantasma nuevo.
	prov._x = x;
	prov._y = y;
	prov.col = color;
	prov.fdir = 0;

	return prov;
	//TODO inicialitzar el fantasma amb les dades donades i la direcció rand() % 4
}


void pintarFantasma(fantasma ghost) {
	setCColor(ghost.col);					//COLOR AZUL
	gotoxy(ghost._x, ghost._y);				//PONGO EL CURSOR EN EL SITIO CORRESPONGIENTRE
	printf("%c", 6);						//PRINTEO EL CHAR DE PAC-MAN -> En el enunciado pone el 6 aunque las vidas es el 2 KEK (Radev in pieces gona rekt yo' ass)

											//TODO imprimir el caracter amb codi ASCII 6
}

void borrarFantasma(fantasma ghost) {
	gotoxy(ghost._x, ghost._y);				//PONGO EL CURSOR DONDE ESTA EL FANTASMA PARA PODER SUBSTITUIRLO POR UN VACIO.
	setCColor(color[0]);
	printf("%c", 32);							//PONGO UN VACIO. ( David's heart ( ͡° ͜ʖ ͡°) )

}

void xocPacman(fantasma ghost) {
	if (((ghost._x == anteriorpx) && (ghost._y == anteriorpy)) || ((ghost._x == x) && (ghost._y == y))) {
		//Colisión: Borrar PAC-MAN + -1 Vida + Reposicionamiento de PAC-MAN.
		borrarPacman(x, y);
		vides -= 1;
		punts -= 25;
		//pintarPacman(39, 22);
		thread(pintarPacman, 39, 22).join();
		perma.lock();
		x = 39;
		y = 22;
		dir = 0;
		perma.unlock();
	}
	//TODO detectar si el fantasma colisiona amb l'actual o l'anterior posició del Pacman, de ser aixi posicionar al jugador a x=39, y=22, dir = 3 i disminuir en una les vides
}

void moureFantasma(fantasma &ghost) {
	int bolx = ghost._x, boly = ghost._y;

	/*
	Esta función contradice el enunciado: Nos piden que los fantasmas mantengan su dirección siempre que sea posible. Es decir que aunque tenga otros caminos siga en su misma dirección.
	En el caso de esta función hace que el fantasma cambie de dirección un 75% de las veces en el momento que esté en un cruce.

	if (mapa[ghost._y][ghost._x] == '|') {
	ghost.fdir = rand() % 4;
	}
	*/

	borrarFantasma(ghost);	//Esborrar el fantasma
	xocPacman(ghost);
	//Intentar seguir en la direcció que anava, en cas de trobar-se amb algun obstacle (X,A,B,C,D) intentar-lo redirigir. (El fantasma NUNCA se chocará con A,B,C,D)
	switch (ghost.fdir) {
	case 0: //arriba
		if (mapa[ghost._y - 1][ghost._x] == 'X') {
			if (mapa[ghost._y][ghost._x + 1] == 'Y' && mapa[ghost._y][ghost._x - 1] == 'Y') {
				ghost.fdir = 1;
			}
			else if (mapa[ghost._y][ghost._x + 1] == 'Y') {	//No puede ir derecha
				ghost.fdir = 3;			//Irá izquierda

			}
			else if (mapa[ghost._y][ghost._x - 1] == 'Y') {	//No puede ir izquierda
				ghost.fdir = 2;					//Irá derecha

			}
			else {
				ghost.fdir = (rand() % 3) + 1; //Random [1, 2, 3]
			}
		}
		else { ghost._y--; }
		break;

	case 1: //abajo
		if (mapa[ghost._y + 1][ghost._x] == 'X') {
			if (mapa[ghost._y][ghost._x + 1] == 'Y' && mapa[ghost._y][ghost._x - 1] == 'Y') {
				ghost.fdir = 0;
			}
			else if (mapa[ghost._y][ghost._x + 1] == 'Y') {	//No puede ir derecha
				ghost.fdir = 3;				//Irá izquierda
			}
			else if (mapa[ghost._y][ghost._x - 1] == 'Y') {	//No puede ir izquierda
				ghost.fdir = 2;					//Irá derecha
			}
			else {
				ghost.fdir = (rand() % 2) + 2; //Random [2, 3] -> derecha o izquierda
			}
		}
		else { ghost._y++; }
		break;

	case 2: //derecha
		if (mapa[ghost._y][ghost._x + 1] == 'Y') {
			if (mapa[ghost._y - 1][ghost._x] == 'X' && mapa[ghost._y + 1][ghost._x] == 'X') {
				ghost.fdir = 3;
			}
			else if (mapa[ghost._y - 1][ghost._x] == 'X') {	//No puede ir arriba
				ghost.fdir = 1;
				ghost._y++;
			}
			else if (mapa[ghost._y + 1][ghost._x] == 'X') {	//No puede ir abajo
				ghost.fdir = 0;
				ghost._y--;
			}
			else {
				ghost.fdir = (rand() % 2); //Random [0, 1]
			}
		}
		else { ghost._x++; }
		break;

	case 3: //izquierda
		if (mapa[ghost._y][ghost._x - 1] == 'Y') {
			if (mapa[ghost._y - 1][ghost._x] == 'X' && mapa[ghost._y + 1][ghost._x] == 'X') {
				ghost.fdir = 2;
			}
			else if (mapa[ghost._y - 1][ghost._x] == 'X') {	//No puede ir arriba
				ghost.fdir = 1;
			}
			else if (mapa[ghost._y + 1][ghost._x] == 'X') {	//No puede ir abajo
				ghost.fdir = 0;
			}
			else {
				ghost.fdir = (rand() % 3); //Random [0, 1, 2]
			}
		}
		else { ghost._x--; }
		break;
	}

	if (mapa[ghost._y][ghost._x] == '*') {
		ghost.fdir = 0;
		ghost._y -= 2;
	}

	//Printar el fantasma
	//pintarFantasma(ghost);
	thread(pintarFantasma, ghost).join();

	//Esta funcion pone bolitas si en el mapa habían bolitas.
	if (mapa[boly][bolx] == '_') {
		setCColor(color[1]);
		gotoxy(bolx, boly);
		printf("%c", 250);
	}


}

void marcador() {
	setCColor(color[2]);
	gotoxy(5, 4); printf("PUNTS");
	gotoxy(5, 6); printf("    ");
	setCColor(color[6]);
	gotoxy(5, 6); printf("%ld", punts);

	setCColor(color[1]);
	gotoxy(5, 25); printf("VIDES");
	for (int i = 0; i <= vides; i++) {
		gotoxy(5, i + 27); printf(" ");

	}
	for (int i = 0; i < vides; i++) {
		gotoxy(5, i + 27); printf("%c", 2);

	}
	setCColor(color[2]);
	gotoxy(70, 27); printf("%c", 169);


}

int main() {

	fantasma ghostA = inicialitzarFantasma(41, 14, 2);
	fantasma ghostB = inicialitzarFantasma(43, 14, 3);
	fantasma ghostC = inicialitzarFantasma(40, 14, 4);
	fantasma ghostD = inicialitzarFantasma(39, 14, 5);


	pintar_mapa();
	/*
	//SPAWNEAR FANTASMAS:
	thread esperaFantasma(ordenFantasmas, 4);
	esperaFantasma.join();
	*/
	while (vides > 0 && punts < 1940) {
		//marcador();					//CONVERTIR EN UN THREAD APARTE
		thread(marcador).join();

		moureFantasma(ghostA);
		moureFantasma(ghostB);
		moureFantasma(ghostC);
		moureFantasma(ghostD);

		moverPacman();
		//TODO Moure el Pacman, els fantasmes i detectar els possibles xocs

		Sleep(110);
	}




	for (int i = 0; i <= vides; i++) {
		gotoxy(5, i + 27);
		printf(" ");
	}

	system("pause>NULL");
	return 0;

}