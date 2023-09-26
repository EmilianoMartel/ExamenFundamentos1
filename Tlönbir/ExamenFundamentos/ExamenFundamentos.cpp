// ExamenFundamentos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum PickType {
	Wood,
	Iron,
	Diamond
};
//Const
const int MAXLIFE = 10;
const string TITLE = "Un enano en Tlönbir";
const int MAXPLAYCHOOSE = 3;
const int MAXOPTION = 6;
const int MAXGOLD = 100;
const string PLAYERNAME = "Gorgomir";
//ExploreCONST
const int EXPLORECHANCE = 10;
const int MINGOLDEXPLORE = 5;
const int MAXGOLDEXPLORE = 20;
//CollectCONST
const int BERRIESHEALING = 3;
const int COLLECTCHANCE = 30;

//Global variables
int actualDay = 1;
int gold = 5;
int expMining = 0;
int life = 10;
string pick = "ninguno";
int pickDurability = 0;

//Chek input option
int CheckIntInput(int cant) {
	string input;
	bool inputValue = false;
	int inputNum = 1;

	do {
		cout << "Enter a option: " << endl;
		getline(cin, input);

		istringstream stream(input);

		if (stream >> inputNum) {
			inputValue = true;
			if (inputNum > cant) {
				cout << "The input is out of range. Please try again" << endl;
				inputValue = false;
			}
		}
		else {
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!inputValue);

	return inputNum;
}
//Clear console
void PressAnyButton() {
	cout << "Press any key to continue..." << endl;
	getchar();
	system("cls");
}
//Instructions of game
void Instructions() {
	system("cls");
	cout << "The goal of the game is for Gorgomir to achieve his dream of obtaining 100 coins." << endl;
	cout << "If you reach 0 life points, you lose." << endl;
	cout << "To achieve this goal, you will have several options..." << endl;
	PressAnyButton();
	cout << "Explore = You have a chance to find between 5 and 20 gold, but you will lose one life point." << endl;
	cout << "Collect Berries = You have a chance to find berries that will restore 3 life points." << endl;
	cout << "Mine = YOU CAN ONLY MINE IF YOU HAVE MORE THAN 4 LIFE POINTS." << endl;
	cout << "If you mine, you can strike the rocks 4 times, and each time you have a chance to find 1 iron." << endl;
	cout << "Your equipment will lose durability with each strike, and you will lose 1 life point at the end." << endl;
	cout << "If you don't find anything, you gain 1 mining experience, increasing your chances next time!" << endl;
	PressAnyButton();
	cout << "Forge = YOU CAN ONLY FORGE IF YOU HAVE 2 OR MORE UNITS OF IRON." << endl;
	cout << "They sell for 30 gold each." << endl;
	cout << "Repair = It costs 1 gold for each point of durability to repair." << endl;
	cout << "Shop = You can buy the next pickaxe upgrade! There are Wood, Iron, and Diamond picks." << endl;
	cout << "With each upgrade, you have a better chance of mining successfully." << endl;
	PressAnyButton();
	cout << "Good luck! Now, back to the menu." << endl;
	PressAnyButton();
}
//History of Player
void History() {
	cout << "It's the year 157 in the village of Tlönbir, and a small dwarf named Gorgomir stands out for" << endl;
	cout << "his strength and intelligence above all others. His dream is to become the best miner and blacksmith" << endl;
	cout << "in all of Middle-earth. But to achieve that, he will need to use his audacity and perspicacity" << endl;
	cout << "to navigate this vast world full of dangers and challenges." << endl;
	PressAnyButton();
}
//Random value
int MakeRandom(int min = 0, int max = 100) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(min, max);
	int result = distribution(gen);
	return result;
}
//Explore Area Logic
void Explore() {
	int chance = MakeRandom();
	int sumGold = 0;
	if (chance <= EXPLORECHANCE) {
		sumGold = MakeRandom(MINGOLDEXPLORE,MAXGOLDEXPLORE);
		gold += sumGold;
		cout << "Congratulations, you obtained " << sumGold << " gold." << endl;
	}
	life -= 1;
	cout << "You lost 1 life point." << endl;
	PressAnyButton();
}
//Collect berries logic
void Collect() {
	int chance = MakeRandom();
	if (chance <= COLLECTCHANCE) {
		life += BERRIESHEALING;
		if (life > MAXLIFE) {
			life = MAXLIFE;
		}
		cout << "Congratulations, you found berries, you healed " << BERRIESHEALING << " points." << endl;
	}
	else {
		cout << "Unfortunately, you didn't find anything." << endl;
	}
	PressAnyButton();
}

int main()
{
	int playChoose;
	int option;
	//Menu
	do
	{
		cout << TITLE << endl;
		cout << "Choose an option." << endl;
		cout << "1 - Play" << endl;
		cout << "2 - Instructions" << endl;
		cout << "3 - Exit" << endl;
		playChoose = CheckIntInput(MAXPLAYCHOOSE);
		system("cls");
		switch (playChoose)
		{
		//GAME
		case 1:
			do
			{
				if (actualDay == 1) {
					History();
				}
				cout << "Day = " << actualDay << endl;
				cout << "Gorgomir" << endl;
				cout << "Life = " << life << endl;
				cout << "Gold = " << gold << endl;
				cout << "Pickaxe = " << pick << endl;
				cout << "1 - Explore area" << endl;
				cout << "2 - Collect berries" << endl;
				cout << "3 - Mine" << endl;
				cout << "4 - Forge armor" << endl;
				cout << "5 - Repair inventory" << endl;
				cout << "6 - Buy a new pickaxe" << endl;
				option = CheckIntInput(MAXOPTION);
				system("cls");
				switch (option)
				{
				//Explore
				case 1:
					Explore();
					break;
				//Collect
				case 2:
					Collect();
					break;
				default:
					break;
				}
			} while (true);
			break;
		case 2:
			Instructions();
			break;
		default:
			break;
		}
	} while (playChoose != 3);
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
