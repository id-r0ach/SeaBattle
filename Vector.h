#pragma once
#include <iostream>


template <typename T> 
class Vector{
private:
	int size;
	T* data;
public:
	
	Vector<T> (int s) {
		size = s;
		data = new T[size];
	}


	Vector<T> (const Vector<T>& v) {
		size = v.size;
		data = new T[size];
		for (int i = 0; i < size; i++) {
			data[i] = v.data[i];
		}
	}


	~Vector<T>() {
		delete[] data;
	}



	T& operator[](int i) {
		return data[i];
	}



	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& v) {
		for (int i = 0; i < v.size; i++) {
			out << v.data[i] << ' ';
		}
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector<T>& v) {
		for (int i = 0; i < v.size; i++) {
			in >> v.data[i];
		}
		return in;
	}
};

