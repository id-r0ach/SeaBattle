#pragma once
#include "Player.h"
#include "Ship.h"

class Human : public Player{
private:
	void CheckInput(int x, int y, int orien);
	void CheckShipFit(int x, int y, int lenght_ship, orientation orien);
	void CheckShipArea(int x, int y, int lenght_ship, orientation orien);
	void PutShipOnBoard(int x, int y, int length_ship, orientation orien);
public:
	Human(int _board_size, int _number_ships) : Player(_board_size, _number_ships) {}

	void PlaceShip() override;
	shot_result shot(Player& enemy) override;
};

