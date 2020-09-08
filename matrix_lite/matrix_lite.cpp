#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

class matrix {
	//номера строк m
	//номера столбцов n
	//mxn
public:

	matrix(const size_t& quantityOfLine, const size_t& quantityOfColumn, double* array)
		: _n(quantityOfColumn), _m(quantityOfLine)
	{
		setMatrixUsingArray(array);
		std::cerr << "done. matrix" << _m << 'x' << _n << " created\n";
	};
	~matrix() {
		std::cerr << "matrix" << _m << 'x' << _n << " destroy now\n";
	}
	//PrintMatrix
	const void printMatrix(const bool& isReal) {
		/*1- выводит с nan 0-выводит без nan*/
		if (!isReal) {
			std::cerr << "Matrix" << _n << 'x' << _m << ":\n";
			for (size_t i = 0; i < _n; i++) {
				for (size_t j = 0; j < _m; j++) {
					std::cerr << _matrix4x4[i][j] << ' ';
				}
				std::cerr << std::endl;
			}
			std::cerr << std::endl;
		}
		else {
			std::cerr << "Matrix" << _n << 'x' << _m << ":\n";
			for (size_t i = 0; i < 4; i++) {
				for (size_t j = 0; j < 4; j++) {
					std::cerr << _matrix4x4[i][j] << ' ';
				}
				std::cerr << std::endl;
			}
			std::cerr << std::endl;
		}
	}
	//SetMatr
	void setMatrixUsingArray(double* array) {
		size_t i_a = 0;
		//printMatrix(0);
		for (size_t i = 0; i < _m; i++) {

			for (size_t j = 0; j < _n; j++) {
				_matrix4x4[i][j] = array[i_a];
				_matrixInMassive[i_a++] = array[i + j];
			}
		}
		//printMatrix(0);

	}

	double& getMatrixInMassive() {
		return _matrixInMassive[0];
	}
private:

	const size_t _n;
	const size_t _m;
	double _matrixInMassive[16];
	double _matrix4x4[4][4] = {

		{NAN, NAN, NAN, NAN},
		{NAN, NAN, NAN, NAN},
		{NAN, NAN, NAN, NAN},
		{NAN, NAN, NAN, NAN}

	};
};
std::ostream& operator << (std::ostream& os, matrix& m) {
	double a[] = { NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN };
	for (size_t i = 0; i < 16; i++) {

		a[i] = (m.getMatrixInMassive() + i);//хуйня, он прост оприбавляет к первуму элементу i
		if (m.getMatrixInMassive() + i == NAN) { break; }
	}
	os << "[ ";
	for (const double& i : a) {
		os << i << ' ';
	}
	return  os << ']\n';
}

int main() {
	double aa[16] =
	{ 1,2,3,4,
	  5,6,7,8,
	  9,10,11,12,
	  13,14,15,16
	};
	/*double bb[4] =
	{ 1,2,3,4};

	double cc[8] =
	{ 1,2,3,4,
	  1,2,3,4
	};
	double dd[4] =
	{ 1,2,
	  1,2
	};*/
	matrix a(4, 4, aa);
	//matrix b(4, 1, bb);
	//matrix c(4, 2, cc);
	//matrix d(2, 2, dd);

	std::cout << a;
	return 0;
}
