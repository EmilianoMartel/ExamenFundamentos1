// ExamenFundamentos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//In this enum we have a price of pickaxe
enum PickAxeType {
	Wood = 5,
	Iron = 10,
	Diamond = 20
};

//Const
const int MAX_LIFE = 10;
const string TITLE = "Un enano en Tlönbir";
const int MAX_PLAYCHOOSE = 3;
const int MAX_OPTION = 6;
const int MAX_GOLD = 100;
const string PLAYERNAME = "Gorgomir";
//ExploreCONST
const int EXPLORE_CHANCE = 10;
const int MIN_GOLD_EXPLORE = 5;
const int MAX_GOLD_EXPLORE = 20;
const int EXPLORE_LOST_LIFE = 1;
//CollectCONST
const int BERRIES_HEALING = 3;
const int COLLECT_CHANCE = 30;
//MineCONST
const int MIN_LIFE = 4;
const int MIN_DURABILITY_FOR_MINE = 0;
const int MINE_LOST_LIFE = 1;
const int IRON_WIN = 1;
const float DURABILITY_LOST = 0.5f;
//PickaxeCONST
const int WOOD_MAX_DURABILITY = 10;
const int IRON_MAX_DURABILITY = 15;
const int DIAMOND_MAX_DURABILITY = 30;
const int WOOD_CHANCE_MINE = 30;
const int IRON_CHANCE_MINE = 50;
const int DIAMOND_CHANCE_MINE = 60;
//ForgeCONST
const int IRON_NEED_TO_FORGE = 2;
const int ARMOR_PRICE = 30;
//NFT CONST
const int WIN_GOLD_NFT = 10;
const int CHANCE_NFT = 5;

//Global variables
int actualDay = 1;
int gold = 5;
int expMining = 0;
int life = 10;
string pickaxeName = "None";
float pickActualDurability = 0;
int actualIron = 0;
int actualForgeArmor = 0;
PickAxeType actualPickaxe = PickAxeType::Wood;
int pickMaxDurability = 0;
//GameOptions
int playChoose;
int option;
bool rePlay = true;

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
//Set Default Game
void SetDefault() {
	actualDay = 1;
	gold = 5;
	expMining = 0;
	life = 10;
	pickaxeName = "None";
	pickActualDurability = 0;
	actualIron = 0;
	actualForgeArmor = 0;
	actualPickaxe = PickAxeType::Wood;
	pickMaxDurability = 0;
}
//Menu Game Logic
int MenuGame() {
	bool isValidOption = false;
	int option;
	do
	{
		cout << "Day = " << actualDay << endl;
		cout << "Gorgomir" << endl;
		cout << "Life = " << life << endl;
		cout << "Gold = " << gold << endl;
		cout << "Iron ingots = " << actualIron << endl;
		cout << "Pickaxe = " << pickaxeName << " durability " << pickActualDurability << endl;
		cout << "Forged armor = " << actualForgeArmor << endl;
		cout << "1 - Explore area" << endl;
		cout << "2 - Collect berries" << endl;
		cout << "3 - Mine" << endl;
		cout << "4 - Forge armor" << endl;
		cout << "5 - Repair inventory" << endl;
		cout << "6 - Buy a new pickaxe" << endl;
		option = CheckIntInput(MAX_OPTION);

		//Check if can mine
		if (option == 3 && (life <= MIN_LIFE || pickActualDurability == MIN_DURABILITY_FOR_MINE)) {
			cout << "You cant mine." << endl;
			cout << "Please try with another option." << endl;
			isValidOption = false;
			PressAnyButton();
		}
		//Check if can forge
		else if (option == 4 && actualIron < 2) {
			cout << "You cant forge armor." << endl;
			cout << "Please try with another option." << endl;
			isValidOption = false;
			PressAnyButton();
		}
		//Check if can Repair
		else  if (option == 5 && (pickActualDurability == pickMaxDurability || gold == 0)) {
			cout << "You cant repair the armor." << endl;
			if (pickActualDurability == pickMaxDurability) {
				cout << "Because your equip is full durability." << endl;
			}
			else if (gold == 0) {
				cout << "Because you dont have gold." << endl;
			}
			cout << "Please try with another option." << endl;
			isValidOption = false;
			PressAnyButton();
		}
		//Check if can buy new pickaxe
		else if (option == 6 && (actualPickaxe == PickAxeType::Diamond || gold < static_cast<int>(actualPickaxe))) {
			cout << "You cant buy a new pickaxe." << endl;
			if (actualPickaxe == PickAxeType::Diamond) {
				cout << "Because you have a Diamond pickaxe." << endl;
			}
			else {
				cout << "Because you dont have enough gold." << endl;
			}
			cout << "Please try with another option." << endl;
			isValidOption = false;
			PressAnyButton();
		}
		else {
			isValidOption = true;
		}
	} while (!isValidOption);
	system("cls");
	return option;
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
	if (chance <= EXPLORE_CHANCE) {
		sumGold = MakeRandom(MIN_GOLD_EXPLORE, MAX_GOLD_EXPLORE);
		gold += sumGold;
		cout << "Congratulations, you obtained " << sumGold << " gold." << endl;
	}
	life -= EXPLORE_LOST_LIFE;
	cout << "You lost 1 life point." << endl;
}
//Collect berries logic
void Collect() {
	int chance = MakeRandom();
	if (chance <= COLLECT_CHANCE) {
		life += BERRIES_HEALING;
		if (life > MAX_LIFE) {
			life = MAX_LIFE;
		}
		cout << "Congratulations, you found berries, you healed " << BERRIES_HEALING << " points." << endl;
	}
	else {
		cout << "Unfortunately, you didn't find anything." << endl;
	}
}
//Mine Logic
void Mine() {
	int chance;
	int sumValues = 0;
	bool isMining = false;

	switch (actualPickaxe)
	{
	case Wood:
		sumValues += WOOD_CHANCE_MINE;
		break;
	case Iron:
		sumValues += IRON_CHANCE_MINE;
		break;
	case Diamond:
		sumValues += DIAMOND_CHANCE_MINE;
		break;
	}
	sumValues += expMining;

	for (size_t i = 0; i < 4; i++)
	{
		chance = MakeRandom();
		if (chance <= sumValues) {
			isMining = true;
			actualIron += IRON_WIN;
			cout << "Congratulations, you mining " << IRON_WIN << " iron ingot!" << endl;
		}
		else {
			cout << "Too bad, you don´t mining anything" << endl;
		}
		pickActualDurability -= DURABILITY_LOST;
	}
	if (!isMining) {
		cout << "Congratulations, you gain a 1 point of mining experience" << endl;
		expMining += 1;
	}

	cout << "You are exhausted by what you lose " << MINE_LOST_LIFE << " of life points" << endl;
	life -= MINE_LOST_LIFE;
}
//Forge Armor Logic
void Forge() {
	do
	{
		actualIron -= IRON_NEED_TO_FORGE;
		gold += ARMOR_PRICE;
		cout << "The armor was successfully forged and sold for " << ARMOR_PRICE << " gold." << endl;
	} while (actualIron >= IRON_NEED_TO_FORGE);
}
//Repair inventory Logic
void Repair() {
	int sum = 0;
	do
	{
		gold -= 1;
		pickActualDurability += 1;
		sum += 1;
	} while (pickActualDurability != pickMaxDurability && gold != 0);
	cout << "You repaired " << sum << " durability points." << endl;
	cout << "You Spend " << sum << " gold." << endl;
}
//Buy a new pickaxe  Logic
void BuyNew() {
	switch (actualPickaxe)
	{
	case PickAxeType::Wood:
		if (pickaxeName == "None") {
			cout << "You bought the wooden pickaxe for " << static_cast<int>(PickAxeType::Wood) << endl;
			gold -= static_cast<int>(actualPickaxe);
			pickActualDurability = WOOD_MAX_DURABILITY;
			pickMaxDurability = WOOD_MAX_DURABILITY;
			pickaxeName = "Wood";
			break;
		}
		else {
			cout << "You bought the iron pickaxe for " << static_cast<int>(PickAxeType::Iron) << endl;
			actualPickaxe = PickAxeType::Iron;
			gold -= static_cast<int>(actualPickaxe);
			pickActualDurability = IRON_MAX_DURABILITY;
			pickMaxDurability = IRON_MAX_DURABILITY;
			pickaxeName = "Iron";
			break;
		}
		break;
	case PickAxeType::Iron:
		cout << "You bought the diamond pickaxe for " << static_cast<int>(PickAxeType::Diamond) << endl;
		actualPickaxe = PickAxeType::Diamond;
		gold -= static_cast<int>(actualPickaxe);
		pickActualDurability = DIAMOND_MAX_DURABILITY;
		pickMaxDurability = DIAMOND_MAX_DURABILITY;
		pickaxeName = "Diamond";
		break;
	default:
		break;
	}
}
//Replay option function
void Replay() {
	int reReplayChoose;
	cout << "¿Play again?." << endl;
	cout << "1 - RePlay" << endl;
	cout << "2 - Back to menu" << endl;
	cout << "3 - Exit" << endl;
	reReplayChoose = CheckIntInput(3);
	switch (reReplayChoose)
	{
	case 1:
		SetDefault();
		cout << "Okey! Good luck!" << endl;
		PressAnyButton();
		break;
	case 2:
		rePlay = false;
		cout << "Back to menu." << endl;
		PressAnyButton();
		break;
	case 3:
		rePlay = false;
		playChoose = 3;
		break;
	default:
		break;
	}
}
//Lose and victory Logic
void EndGame() {
	if (gold >= 100) {
		cout << "Congratulations! " << PLAYERNAME << " reached the goal of 100 gold" << endl;
		Replay();
	}
	else if (life == 0) {
		cout << "What a pity, you don't have more life points, you lost.";
		Replay();
	}
}
//NFT CHANCE
void ChanceNFT() {
	int chance = MakeRandom();
	if (chance <= CHANCE_NFT) {
		cout << "You earned " << WIN_GOLD_NFT << " gold for investing in NFTs." << endl;
		gold += WIN_GOLD_NFT;
	}
	else {
		cout << "Nothing happened on this beautiful day." << endl;
	}
}
//MAIN
int main()
{
	
	//Menu
	do
	{
		cout << TITLE << endl;
		cout << "Choose an option." << endl;
		cout << "1 - Play" << endl;
		cout << "2 - Instructions" << endl;
		cout << "3 - Exit" << endl;
		playChoose = CheckIntInput(MAX_PLAYCHOOSE);
		system("cls");
		switch (playChoose)
		{
			//GAME
		case 1:
			rePlay = true;
			SetDefault();
			do
			{
				if (actualDay == 1) {
					History();
				}
				option = MenuGame();
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
					//Mine
				case 3:
					Mine();
					break;
					//Forge
				case 4:
					Forge();
					break;
					//Repair
				case 5:
					Repair();
					break;
					//Buy
				case 6:
					BuyNew();
					break;
				default:
					break;
				}
				actualDay += 1;
				ChanceNFT();
				PressAnyButton();
				EndGame();
			} while (rePlay);
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
