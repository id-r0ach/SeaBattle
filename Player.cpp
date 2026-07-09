#include "Player.h"
#include "Ship.h"
#include "Matrix.h"
#include <iostream>

char Player::GetStatus(status value) {
	if (value == Free) {
		return '.';
	}
	if (value == Hit) {
		return 'X';
	}
	if (value == Dead) {
		return '#';
	}
	if (value == Used) {
		return 'O';
	}
	if (value == Miss) {
		return '*';
	}

	return '?';
}


void Player::PrintBoard(Matrix<status>& board) {
	std::cout << "    ";
	for (int i = 1; i <= board_size; i++) {
		std::cout << i << ' ';
	}
	std::cout << "| x";
	std::cout << std::endl;
	for (int i = 1; i <= board_size+3; i++) {
		std::cout << "- ";
	}
	std::cout << std::endl;
	for (int y = 0; y < board_size; y++) {
		if (y + 1 < 10) {
			std::cout << ' ';
		}
		std::cout << y + 1 << '|' << ' ';
		for (int x = 0; x < board_size; x++) {
			std::cout << GetStatus(board[y][x]) << ' ';
		}
		std::cout << std::endl;
	}
}






void Player::PrintMyBoard() {
	PrintBoard(my_board);
}
void Player::PrintEnemyBoard() {
	PrintBoard(enemy_board);
}



shot_result Player::get_shot(int x, int y, Player& att) {
	if (my_board[y][x] == Miss || my_board[y][x] == Dead || my_board[y][x] == Hit) {
		return ShotAlready;
	}
	if (my_board[y][x] == Free) {
		my_board[y][x] = Miss;
		return ShotMiss;
	}

	if (my_board[y][x] == Used) {
		for (int i = 0; i < number_ships; i++) {
			if (Ships[i].check_hit(x, y)) {
				Ships[i].get_damage();
				if (Ships[i].check_health()) {
					my_board[y][x] = Hit;
					return ShotHit;
				}
				else {
					ship_dead(Ships[i]);
					copy_cells(Ships[i], att);
					return ShotDead;

				}

			}
		}
	}
	return ShotMiss;
}


void Player::ship_dead(Ship& sh) {
	for (int i = 0; i < sh.size; i++) {
		int x_cur = sh.x, y_cur = sh.y;
		if (sh.orient == vertical)
			y_cur += i;
		else if (sh.orient == horizon)
			x_cur += i;
		my_board[y_cur][x_cur] = Dead;
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (x_cur + dx < 0 || x_cur + dx >= board_size || y_cur + dy < 0 || y_cur + dy >= board_size)
					continue;
				if (my_board[y_cur + dy][x_cur + dx] == Free)
					my_board[y_cur + dy][x_cur + dx] = Miss;
			}
		}
	}
}



void Player::copy_cells(Ship& sh, Player& att) {
	for (int i = 0; i < sh.size; i++) {
		int x_cur = sh.x, y_cur = sh.y;
		if (sh.orient == vertical) {
			y_cur += i;
		}
		if (sh.orient == horizon) {
			x_cur += i;
		}

		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				if (0 > (y_cur + dy) || (y_cur + dy) >= board_size || 0 > (x_cur + dx) || (x_cur + dx) >= board_size) {
					continue;
				}
				if (my_board[y_cur + dy][x_cur + dx] == Miss || my_board[y_cur + dy][x_cur + dx] == Hit || my_board[y_cur + dy][x_cur + dx] == Dead) {
					att.enemy_board[y_cur + dy][x_cur + dx] = my_board[y_cur + dy][x_cur + dx];
				}
			}
		}
	}
}


bool Player::is_alive() {
	for (int i = 0; i < number_ships; i++)
		if (Ships[i].check_health() == true)
			return true;
	return false;
}