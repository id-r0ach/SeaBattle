#include "Player.h"
#include "Computer.h"
#include "Ship.h"
#include <iostream>
#include <cstdlib>

void Computer::PlaceShip() {
	for (int ship_index = 0; ship_index < number_ships; ship_index++) {
		int lenght_ship;
		if (ship_index == 0)
			lenght_ship = 4;
		if (1 <= ship_index && ship_index <= 2)
			lenght_ship = 3;
		if (3 <= ship_index && ship_index <= 5)
			lenght_ship = 2;
		if (6 <= ship_index)
			lenght_ship = 1;

		bool ship_placed = false;
		while (!ship_placed) {
			int x = rand() % board_size;
			int y = rand() % board_size;
			orientation orien = static_cast<orientation>(rand() % 2);

			if (CheckShipFit(x, y, lenght_ship, orien) && CheckShipArea(x, y, lenght_ship, orien)){
				ship_placed = true;
				PutShipOnBoard(x, y, lenght_ship, orien);
				Ships[ship_index] = Ship(lenght_ship, x, y, lenght_ship, orien);
			}
		}

	}

}

bool Computer::CheckShipFit(int x, int y, int lenght_ship, orientation orien) {
	if (orien == vertical) {
		if (y + lenght_ship > board_size) {
			return false;
		}
	}
	if (orien == horizon) {
		if (x + lenght_ship > board_size) {
			return false;
		}
	}
	return true;
}


bool Computer::CheckShipArea(int x, int y, int lenght_ship, orientation orien) {
	for (int i = 0; i < lenght_ship; i++) {
		int ship_x = x;
		int ship_y = y;

		if (orien == vertical) {
			ship_y += i;
		}
		else if (orien == horizon) {
			ship_x += i;
		}

		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {

				if (ship_x + dx < 0 || ship_x + dx >= board_size || ship_y + dy < 0 || ship_y + dy >= board_size) {
					continue;
				}

				if (my_board[ship_y + dy][ship_x + dx] != Free) {
					return false;
				}

			}
		}
	}
	return true;
}


void Computer::PutShipOnBoard(int x, int y, int length_ship, orientation orien) {
	for (int i = 0; i < length_ship; i++) {
		if (orien == vertical) {
			my_board[y + i][x] = Used;
		}
		if (orien == horizon) {
			my_board[y][x + i] = Used;
		}
	}
}


shot_result Computer::hunter(Player& enemy, int& x_cor, int& y_cor) {
	int dirs[4] = { 0, 0, 0, 0 };
	dirs[0] = 1 + rand() % 4;
	for (int i = 0; i < 3; i++) {


		while (1) {
			bool flag = true;
			int temp = 1 + rand() % 4;

			for (int j = 0; j < 4; j++) {
				if (dirs[j] == temp) {
					flag = false;
				}
				if (flag == false) {
					break;
				}
			}
			if (flag) {
				dirs[1 + i] = temp;
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		int ch = dirs[i];
		x_cor = xlast;
		y_cor = ylast;
		switch (ch)
		{
		case 1:
			if (0 <= y_cor + 1 && y_cor + 1 < board_size && enemy_board[y_cor + 1][x_cor] == Free) {
				y_cor++;
				shot_result res = enemy.get_shot(x_cor, y_cor, *this);
				return res;
			}
			break;
		case 2:
			if (0 <= x_cor + 1 && x_cor + 1 < board_size && enemy_board[y_cor][x_cor + 1] == Free) {
				x_cor++;
				shot_result res = enemy.get_shot(x_cor, y_cor, *this);
				return res;
			}
			break;
		case 3:
			if (0 <= y_cor - 1 && y_cor - 1 < board_size && enemy_board[y_cor - 1][x_cor] == Free) {
				y_cor--;
				shot_result res = enemy.get_shot(x_cor, y_cor, *this);
				return res;
			}
			break;
		case 4:
			if (0 <= x_cor - 1 && x_cor - 1 < board_size && enemy_board[y_cor][x_cor - 1] == Free) {
				x_cor--;
				shot_result res = enemy.get_shot(x_cor, y_cor, *this);
				return res;
			}
			break;
		}
	}
	hun = false;
	shot_result res = search(enemy, x_cor, y_cor);
	return res;
}


shot_result Computer::search(Player& enemy, int& x_cor, int& y_cor) {
	while (true) {
		x_cor = rand() % board_size;
		y_cor = rand() % board_size;
		if (enemy_board[y_cor][x_cor] == Free)
			break;
	}
	shot_result res = enemy.get_shot(x_cor, y_cor, *this);
	return res;
}

shot_result Computer::shot(Player& enemy) {

	int x_cor, y_cor;
	shot_result res;

	if (hun) {
		res = hunter(enemy, x_cor, y_cor);
	}
	else {
		res = search(enemy, x_cor, y_cor);
	}


	if (res == ShotMiss || res == ShotAlready) {
		enemy_board[y_cor][x_cor] = Miss;
		std::cout << "Выстрел на позицию: " << x_cor + 1 << ", " << y_cor + 1 << std::endl;
		std::cout << "Промах!" << std::endl;
	}
	else if (res == ShotHit) {
		enemy_board[y_cor][x_cor] = Hit;
		std::cout << "Выстрел на позицию: " << x_cor + 1 << ", " << y_cor + 1 << std::endl;
		std::cout << "Попадание!" << std::endl;
		xlast = x_cor;
		ylast = y_cor;
		hun = true;
	}
	else if (res == ShotDead) {
		enemy_board[y_cor][x_cor] = Dead;
		std::cout << "Выстрел на позицию: " << x_cor + 1 << ", " << y_cor + 1 << std::endl;
		std::cout << "Корабль потоплен" << std::endl;
		hun = false;
	}
	return res;
}