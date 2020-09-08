#include <iostream>
#include <iomanip>
#include <stdexcept>

using strmatr = double[4][4];
//		: _m(quantityOfLine),_n(quantityOfColumn)

class matrix {
public:
	matrix() {}
	matrix(const strmatr& str,const size_t& m, const size_t& n):_m(m),_n(n){
		set_M(str);
	}
	void set_M(const strmatr& str) {
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) { _M[i][j] = str[i][j]; }
		}
	}
	void insertOn(const double& value, const size_t& i, const size_t& j) {
		_M[i][j] = value;
	}
	double getElement(const size_t& i, const size_t& j)const {
		return _M[i][j];
	}
	size_t get_m() const {
		return _m;
	}
	size_t get_n() const {
		return _n;
	}
	void printMatrix() {
		for (size_t i = 0; i < get_m(); i++) {
			for (size_t j = 0; j < get_n(); j++)
				std::cout << std::setw(4) << std::setfill(' ') << _M[i][j] << ' ';
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	double determinant(const size_t& size_of_matrix) const {
		switch (size_of_matrix) {
		case (1): {return(getElement(0, 0)); }
		case (2): {
			return(
				getElement(0, 0) * getElement(1, 1) -
				getElement(1, 0) * getElement(0, 1)
				); } break;
		case (3): {
			return (
				getElement(0, 0) * getElement(1, 1) * getElement(2, 2) +
				getElement(2, 0) * getElement(0, 1) * getElement(1, 2) +
				getElement(1, 0) * getElement(2, 1) * getElement(0, 2) -
				getElement(2, 0) * getElement(1, 1) * getElement(0, 2) -
				getElement(0, 0) * getElement(2, 1) * getElement(1, 2) -
				getElement(1, 0) * getElement(0, 1) * getElement(2, 2)
				); } break;
		case (4): {
			return
				(
					getElement(0, 0) *
					(
						(
							(getElement(1, 1) * getElement(2, 2) * getElement(3, 3))
							+ (getElement(1, 2) * getElement(2, 3) * getElement(3, 1))
							+ (getElement(1, 3) * getElement(2, 1) * getElement(3, 2))
							)
						-
						(
							(getElement(1, 3) * getElement(2, 2) * getElement(3, 1))
							+ (getElement(1, 1) * getElement(2, 3) * getElement(3, 2))
							+ (getElement(1, 2) * getElement(2, 1) * getElement(3, 3))
							)
						)

					-

					getElement(0, 1) *
					(
						(
							(getElement(1, 0) * getElement(2, 2) * getElement(3, 3))
							+ (getElement(1, 2) * getElement(2, 3) * getElement(3, 0))
							+ (getElement(1, 3) * getElement(2, 0) * getElement(3, 2))
							)
						-
						(
							(getElement(1, 3) * getElement(2, 2) * getElement(3, 0))
							+ (getElement(1, 0) * getElement(2, 3) * getElement(3, 2))
							+ (getElement(1, 2) * getElement(2, 0) * getElement(3, 3))
							)
						)

					+

					getElement(0, 2) *
					(
						(
							(getElement(1, 0) * getElement(2, 1) * getElement(3, 3))
							+ (getElement(1, 1) * getElement(2, 3) * getElement(3, 0))
							+ (getElement(1, 3) * getElement(2, 0) * getElement(3, 1))
							)
						-
						(
							(getElement(1, 3) * getElement(2, 1) * getElement(3, 0))
							+ (getElement(1, 0) * getElement(2, 3) * getElement(3, 1))
							+ (getElement(1, 1) * getElement(2, 0) * getElement(3, 3))
							)
						)

					-

					getElement(0, 3) *
					(
						(
							(getElement(1, 0) * getElement(2, 1) * getElement(3, 2))
							+ (getElement(1, 1) * getElement(2, 2) * getElement(3, 0))
							+ (getElement(1, 2) * getElement(2, 0) * getElement(3, 1))
							)
						-
						(
							(getElement(1, 2) * getElement(2, 1) * getElement(3, 0))
							+ (getElement(1, 0) * getElement(2, 2) * getElement(3, 1))
							+ (getElement(1, 1) * getElement(2, 0) * getElement(3, 2))
							)
						)
					);

		} break;
		default: {
			std::cerr << "\ninvalid_argument(Matrx size more then 4)\n";

			//throw invalid_argument("Matrx size more then 4");
			break;
		}
		}
	}
	matrix transponierte() const{

		strmatr r = {
		{NAN,NAN,NAN,NAN},
		{NAN,NAN,NAN,NAN},
		{NAN,NAN,NAN,NAN},
		{NAN,NAN,NAN,NAN}
		};

		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				r[i][j] = _M[j][i];
			}
		}
		matrix res(r, 4, 4);
		//res.printMatrix();
		return res;
	}
private:
	size_t _m, _n;//lines, columns
	strmatr _M = { 
		{NAN,NAN,NAN,NAN},
		{NAN,NAN,NAN,NAN},
		{NAN,NAN,NAN,NAN},
		{NAN,NAN,NAN,NAN}
	};
};



int main() {

	matrix a4x4(
	{
		{1.0, 2.0, 3.0, 4.0},
		{5.0, 2.0, 3.0, 4.0},
		{6.0, 2.0, 0.0, 4.0},
		{7.0, 2.0, 3.0, 9.0}
	},
		4, 4);

	matrix a4x1(
		{
			{1.0},
			{5.0},
			{6.0},
			{7.0}
		}, 4, 1);

	matrix a1x4(
		{
			{1.0, 2.0, 3.0, 4.0}
		}
	, 1, 4);

	matrix a2x2(
		{
			{1.0, 2.0},
			{5.0, 2.0}
		},
		4, 4);

	matrix a1x1({
		{7} 
		},1, 1);
	//std::cout << a4x4.determinant(4);

	a4x4.Transponierte();

	return 0;
}























































//#include <vector>
//#include <stdexcept>
//#include <iomanip>
//#include <iostream>
//#include <utility>
//#include <fstream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <windows.h>
//
//class matrix {
//	//номера строк m
//	//номера столбцов n
//	//mxn
//public:
//
//	matrix(const size_t& quantityOfLine, const size_t& quantityOfColumn, double* array)
//		: _m(quantityOfLine),_n(quantityOfColumn)
//	{
//		setMatrixUsingArray(array);
//		//std::cerr << "done. matrix" << _m << 'x' << _n << " created\n";
//	};
//	~matrix() {
//		//std::cerr << "matrix" << _m << 'x' << _n << " destroy now\n";
//	}
//
//	//friend matrix operator*(const matrix& a, const matrix& b);
//	
//
//	//PrintMatrix
//	const void printMatrix(const bool& isReal) {
//		/*1- выводит с nan 0-выводит без nan*/
//		if (!isReal) {
//			std::cerr << "Matrix" << _m << 'x' << _n << ":\n";
//			for (size_t i = 0; i < _m; i++) {
//				for (size_t j = 0; j < _n; j++) {
//					std::cerr << _matrix4x4[i][j] << ' ';
//				}
//				std::cerr << std::endl;
//			}
//			std::cerr << std::endl;
//		}
//		else {
//			std::cerr << "Matrix" << _n << 'x' << _m << ":\n";
//			for (size_t i = 0; i < 4; i++) {
//				for (size_t j = 0; j < 4; j++) {
//					std::cerr << _matrix4x4[i][j] << ' ';
//				}
//				std::cerr << std::endl;
//			}
//			std::cerr << std::endl;
//		}
//	}
//	//SetMatr
//	void setMatrixUsingArray(double* array) {
//		size_t i_a = 0;
//		//printMatrix(0);
//		for (size_t i = 0; i < _m; i++) {
//
//			for (size_t j = 0; j < _n; j++) {
//				_matrix4x4[i][j] = array[i_a];
//				_matrixInMassive[i_a++] = array[i + j];
//			}
//		}
//		//printMatrix(0);
//
//	}
//	//Get_MxN
//	const size_t getM() {
//		return(_m);
//	}
//	//Get_MxN
//	const size_t getN() {
//		return(_n);
//	}
//
//	double& getMatrixInMassive() {
//		return _matrixInMassive[0];
//	}
//	
//	const double getElement(const size_t& i, const size_t& j) {
//		return(_matrix4x4[i - 1][j - 1]);
//	}
//
//	matrix multiplyOn(const matrix& rhs) {
//		double vv[16] =
//		{
//			0,0,0,0,
//			0,0,0,0,
//			0,0,0,0,
//			0,0,0,0
//		};
//		
//		size_t i_a = 0;
//		if (_n == rhs._m) {
//			for (size_t i = 0; i < _m; i++)
//				for (size_t j = 0; j < rhs._n; j++)
//				{
//					for (size_t k = 0; k < _n; k++)
//						vv[4 * (i - 1) + (j - 1)] += _matrix4x4[i][k]*rhs._matrix4x4[k][j];
//				}
//			matrix res(_m, rhs._n, vv);
//			res.printMatrix(0);
//			return res;
//		}
//		else {
//			std::cerr << "Wrong sizes of matrix";
//			//throw invalid_argument("Wrong sizes of matrix");
//		}
//	}
//
//private:
//
//	
//	const size_t _n;
//	const size_t _m;
//	double _matrixInMassive[16];//неправильно заполняется
//	double _matrix4x4[4][4] = {
//
//		{NAN, NAN, NAN, NAN},
//		{NAN, NAN, NAN, NAN},
//		{NAN, NAN, NAN, NAN},
//		{NAN, NAN, NAN, NAN}
//
//	};
//};
//
//int main() {
//	double aa[16] =
//	{ 
//	  1,2,3,4,
//	  5,6,7,8,
//	  9,10,11,12,
//	  13,14,15,16
//	};
//	double bb[4] =
//	{ 
//		1,2,3,4
//	};
//
//	double cc[8] =
//	{ 
//	  1,2,3,4,
//	  1,2,3,4
//	};
//	double dd[4] =
//	{ 
//	  1,2,
//	  1,2
//	};
//	matrix a(4, 4, aa);
//	matrix b(1, 4, bb);
//	matrix c(2, 4, cc);
//	matrix d(2, 2, dd);
//	//a.printMatrix(1);
//	//b.printMatrix(1);
//	//c.printMatrix(1);
//	//d.printMatrix(1);
//	double rres[16] = { NAN, NAN, NAN, NAN,
//		NAN, NAN, NAN, NAN,
//		NAN, NAN, NAN, NAN,
//		NAN, NAN, NAN, NAN 
//	};
//	matrix res(4, 4, rres);
//	d.multiplyOn(c);
//	for (int i = 1; i <= 4; i++) {
//		for (int j = 1; j <= 4; j++) {
//			std::cout << a.getElement(i, j) << ' ';
//		}
//		std::cout << '\n';
//	}
//
//	return 0;
//}
