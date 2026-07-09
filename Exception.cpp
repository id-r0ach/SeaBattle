#include "Exception.h"

std::ostream& operator<<(std::ostream& out, const Exception& s) {
	std::cout << "Файл: " << s.File << std::endl;
	std::cout << "Функция: " << s.Func << std::endl;
	std::cout << "В строке: " << s.Line << std::endl;
	std::cout << s.Message << std::endl;
	return out;
}