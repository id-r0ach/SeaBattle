#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

#define DEBU

int main() {
	system("color F0");
	using namespace std;
	long double a = 15.20;
	cout << sizeof(a);
	system("pause");
	setlocale(LC_ALL, ".UTF8");
	srand(time(nullptr));
	Human hum(10, 10);
	Computer comp(10, 10, false, 0, 0);
	enum motion { player1, player2 };
	motion move;
	shot_result res;
	hum.PlaceShip();
	comp.PlaceShip();
	move = player1;



	while (hum.is_alive() && comp.is_alive()) {
		if (move == player1) {
			system("cls");
			cout << "Твой ход" << endl;
			cout << "------------------------------------------------" << endl << endl;
			hum.PrintMyBoard();
			hum.PrintEnemyBoard();
#ifdef DEBUG
			cout << "///////////////////////////////" << endl;
			comp.PrintMyBoard();
			cout << "///////////////////////////////" << endl;
#endif //DEBUG
			res = hum.shot(comp);
			system("pause");
			if (res != ShotHit && res != ShotDead)
				move = player2;
		}

		else if (move == player2) {
			system("cls");
			cout << "Ход врага" << endl;
			cout << "------------------------------------------------" << endl << endl;
			res = comp.shot(hum);
			hum.PrintMyBoard();
			system("pause");
			if (res != ShotHit && res != ShotDead)
				move = player1;
		}
	}
	system("cls");
	cout << "==============================================" << endl;
	cout << "                 ИГРА ОКОНЧЕНА               " << endl;
	cout << "==============================================" << endl;
	cout << endl;
	if (!hum.is_alive()) {
		cout << "Все ваши корабли были уничтожены..." << endl;
		cout << "Компьютер одержал победу!" << endl;
	}
	else {
		cout << "Поздравляем!" << endl;
		cout << "Вы уничтожили весь вражеский флот!" << endl;
		cout << "Победа за вами!" << endl;
	}

	cout << endl;
	cout << "Спасибо за игру!" << endl;
	cout << "==============================================" << endl;

	system("pause");

	return 0;
}