#pragma once
#include "Player.h"
#include "Ship.h"
class Computer : public Player{
private:
	bool CheckShipFit(int x, int y, int lenght_ship, orientation orien);
	bool CheckShipArea(int x, int y, int lenght_ship, orientation orien);
	void PutShipOnBoard(int x, int y, int length_ship, orientation orien);
	bool hun;
	int xlast, ylast;
public:
	Computer(int _board_size, int _number_ships, bool _hun, int _xlast, int _ylast) : Player(_board_size, _number_ships), hun(_hun), xlast(_xlast), ylast(_ylast) {}
	void PlaceShip() override; 
	shot_result shot(Player& enemy);
	shot_result hunter(Player& enemy, int&, int&);
	shot_result search(Player& enemy, int&, int&);
};

