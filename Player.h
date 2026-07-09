#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Ship.h"

enum status{Free, Hit, Dead, Used, Miss};
enum shot_result{ShotMiss, ShotHit, ShotDead, ShotAlready};
// Free - свободная клетка; Hit - попадание; Dead - убит корабль; Used - стоит корабль; Miss - промах
class Player{
protected:
	Vector<Ship> Ships;
	const int board_size{ 10 };
	Matrix<status> my_board, enemy_board;
	const int number_ships;
public:
	Player(int _board_size, int _number_ships) : Ships(_number_ships), board_size(_board_size), my_board(_board_size), enemy_board(_board_size), number_ships(_number_ships) {
		my_board.Fill(Free);
		enemy_board.Fill(Free);
	}	
	virtual void PlaceShip() = 0;
	virtual shot_result shot(Player& enemy) = 0;
	void PrintBoard(Matrix<status>&);
	char GetStatus(status value);

	void PrintMyBoard();
	void PrintEnemyBoard();

	shot_result get_shot(int, int, Player&);

	void ship_dead(Ship&);
	void copy_cells(Ship&, Player&);


	bool is_alive();
};

