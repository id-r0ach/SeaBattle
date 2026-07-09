#pragma once
#include <iostream>

template <typename T>
class Matrix{
private:
	int m, n;
	T** data;
public:
	Matrix<T> (int _m, int _n) {
		m = _m;
		n = _n;
		data = new T * [m];
		for (int i = 0; i < m; i++) {
			data[i] = new T[n];
		}
	}

	Matrix<T> (int s = 10) {
		n = s;
		m = s;
		data = new T * [n];
		for (int i = 0; i < n; i++) {
			data[i] = new T[n];
		}
	}

	Matrix<T>(const Matrix<T>& arr) {
		m = arr.m;
		n = arr.n;
		data = new T * [m];
		for (int i = 0; i < m; i++) {
			data[i] = new T[n];
			for (int j = 0; j < n; j++) {
				data[i][j] = arr.data[i][j];
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < m; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

	void Print() {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << data[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}


	T* operator[](int i) {
		return data[i];
	}

	void Fill(T value) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				data[i][j] = value;
			}
		}
	}

};

