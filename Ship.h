#pragma once
enum orientation { vertical, horizon };
class Ship{
private:
	friend class Player;
	friend class Human;
	friend class Computer;
	int size, x, y, hp;
	orientation orient;
public:
	Ship() : size(0), x(0), y(0), hp(0), orient(horizon) {};
	Ship(int _size, int _x, int _y, int _hp, orientation _orient) : size(_size), x(_x), y(_y), hp(_hp), orient(_orient) {};
	Ship(const Ship& s) : size(s.size), x(s.x), y(s.y), hp(s.hp), orient(s.orient) {};
	bool check_hit(int, int);
	void get_damage();
	bool check_health();
};

