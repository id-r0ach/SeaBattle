#pragma once
#include <string>
#include <iostream>
class Exception{
private:
	std::string File, Func, Message;
	int Line;
public:
	Exception(std::string _File, std::string _Func, std::string _Message, int _Line) : File(_File), Func(_Func), Message(_Message), Line(_Line) {};
	~Exception() {}
	Exception(const Exception& ex) : File(ex.File), Func(ex.Func), Message(ex.Message), Line(ex.Line) {};
	friend std::ostream& operator<<(std::ostream& out, const Exception& s);
};

