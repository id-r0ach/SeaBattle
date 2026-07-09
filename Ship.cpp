#include "Ship.h"

bool Ship::check_hit(int x_cor, int y_cor) {
	int x_cur = x, y_cur = y;
	for (int i = 0; i < size; i++) {
		if (orient == vertical) {
			if (x_cur == x_cor && (y_cur + i) == y_cor) {
				return true;
			}
		}
		if (orient == horizon) {
			if ((x_cur + i) == x_cor && y_cur == y_cor) {
				return true;
			}
		}
	}
	return false;
}

void Ship::get_damage() {
	if (hp > 0) {
		hp--;
	}
}

bool Ship::check_health() {
	if (hp > 0) {
		return true;
	}
	return false;
}

