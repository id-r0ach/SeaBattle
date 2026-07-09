#include "Human.h"
#include <iostream>
#include <cstdlib>
#include "Exception.h"
#include "Player.h"
#include "Ship.h"

void Human::PlaceShip() {
	system("cls");
	std::cout << "Расстановка кораблей:" << std::endl;
	std::cout << "Нужно расставить:" << std::endl;
	std::cout << "* 1 - 4-ёх палубный" << std::endl;
	std::cout << "* 2 - 3-ёх палубных" << std::endl;
	std::cout << "* 3 - 2-ух палубных" << std::endl;
	std::cout << "* 4 - 1-на палубных" << std::endl;
	system("pause");

	int x_cor, y_cor;
	int orien;
	int lenght_ship;
	bool correct_input;
	for (int ship_index = 0; ship_index < number_ships; ship_index++) {
		system("cls");
		correct_input = false;
		if (ship_index == 0)
			lenght_ship = 4;
		if (1 <= ship_index && ship_index <= 2)
			lenght_ship = 3;
		if (3 <= ship_index && ship_index <= 5)
			lenght_ship = 2;
		if (6 <= ship_index)
			lenght_ship = 1;


		while (!correct_input) {
			std::cout << "Нужно расставить корабль длинной: " << lenght_ship << std::endl << std::endl;
			PrintMyBoard();
			std::cout << std::endl << "Введите координату x: ";
			std::cin >> x_cor;
			std::cout << "Введите координату y: ";
			std::cin >> y_cor;
			std::cout << "Ориентация корабля(0-вертикальная/1-горизонтальная): ";
			std::cin >> orien;


			try {


				CheckInput(x_cor, y_cor, orien);


				x_cor--;
				y_cor--;

				CheckShipFit(x_cor, y_cor, lenght_ship, static_cast<orientation>(orien));

				CheckShipArea(x_cor, y_cor, lenght_ship, static_cast<orientation>(orien));

				PutShipOnBoard(x_cor, y_cor, lenght_ship, static_cast<orientation>(orien));

				Ships[ship_index] = Ship(lenght_ship, x_cor, y_cor, lenght_ship, static_cast<orientation>(orien));


				correct_input = true;
			}

			catch (const Exception& ex) {
				std::cout << std::endl << std::endl;
				std::cout << "Ошибка при вводе данных: " << std::endl;
				std::cout << ex << std::endl;
				system("pause");
			}
		}
	}
}



void Human::CheckInput(int x, int y, int orien) {

	if (1 > x || x > board_size) {
		throw Exception(__FILE__, __FUNCTION__, "Координата x находится вне поля", __LINE__);
	}
	if (1 > y || y > board_size) {
		throw Exception(__FILE__, __FUNCTION__, "Координата y находится вне поля", __LINE__);
	}
	if (orien != 0 && orien != 1) {
		throw Exception(__FILE__, __FUNCTION__, "Ориентация должна быть 0 или 1", __LINE__);
	}
}

void Human::CheckShipFit(int x, int y, int lenght_ship, orientation orien) {
	if (orien == vertical) {
		if (y + lenght_ship > board_size) {
			throw Exception(__FILE__, __FUNCTION__, "Корабль не помещается по вертикали", __LINE__);
		}
	}
	if (orien == horizon) {
		if (x + lenght_ship > board_size) {
			throw Exception(__FILE__, __FUNCTION__, "Корабль не помещается по горизонтали", __LINE__);
		}
	}
}


void Human::CheckShipArea(int x, int y, int lenght_ship, orientation orien) {
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
					throw Exception(__FILE__, __FUNCTION__, "Рядом уже есть корабль", __LINE__);
				}

			}
		}
	}
}

void Human::PutShipOnBoard(int x, int y, int length_ship, orientation orien) {
	for (int i = 0; i < length_ship; i++) {
		if (orien == vertical) {
			my_board[y + i][x] = Used;
		}
		if (orien == horizon) {
			my_board[y][x + i] = Used;
		}
	}
}


shot_result Human::shot(Player& enemy) {
	bool correct_input = false;
	int x_cor, y_cor;
	while (!correct_input) {
		std::cout << "На какую клетку хотите нанести удар?" << std::endl;
		std::cout << "Введите координату x: ";
		std::cin >> x_cor;
		std::cout << "Введите координату y: ";
		std::cin >> y_cor;
		x_cor--;
		y_cor--;
		try {
			if (x_cor < 0 || x_cor >= board_size) {
				throw Exception(__FILE__, __FUNCTION__, "Координата x находится вне поля", __LINE__);
			}
			if (y_cor < 0 || y_cor >= board_size) {
				throw Exception(__FILE__, __FUNCTION__, "Координата y находится вне поля", __LINE__);
			}

			if (enemy_board[y_cor][x_cor] == Hit || enemy_board[y_cor][x_cor] == Dead || enemy_board[y_cor][x_cor] == Miss) {
				throw Exception(__FILE__, __FUNCTION__, "В эту клетку уже стреляли", __LINE__);
			}

			correct_input = true;
		}
		catch (const Exception& ex) {
			std::cout << std::endl << std::endl;
			std::cout << "Ошибка при вводе данных: " << std::endl;
			std::cout << ex << std::endl;
			system("pause");
		}
	}
 	
	shot_result res = enemy.get_shot(x_cor, y_cor, *this);
	switch (res)
	{
	case ShotMiss:
		enemy_board[y_cor][x_cor] = Miss;
		std::cout << std::endl << std::endl;
		PrintEnemyBoard();
		std::cout << std::endl << std::endl;
		std::cout << "Неудача, промах(" << std::endl;
		return res;
		break;
	case ShotHit:
		enemy_board[y_cor][x_cor] = Hit;
		std::cout << std::endl << std::endl;
		PrintEnemyBoard();
		std::cout << std::endl << std::endl;
		std::cout << "Есть! Попадание!" << std::endl;
		return res;
		break;
	case ShotDead:
		enemy_board[y_cor][x_cor] = Dead;
		std::cout << std::endl << std::endl;
		PrintEnemyBoard();
		std::cout << std::endl << std::endl;
		std::cout << "Корабль потоплен!" << std::endl;
		return res;
		break;
	case ShotAlready:
		std::cout << std::endl << std::endl;
		PrintMyBoard();
		std::cout << std::endl << std::endl;
		std::cout << "В эту клетку уже стреляли" << std::endl;
		return res;
		break;
	default:
		break;
	}
}