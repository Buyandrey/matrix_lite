#pragma once

#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;
using strmatr = vector<vector<double>>;											   // Синоним для вектора векторов, чтобы удобней было. Вектор векторов дабл == "Матрица-строка".
																				   //
void RESIZEvv(strmatr& vv, const size_t& m1, const size_t& n2);					   // Функция которая принимает по ссылке матрицу-строку и меняет её размер (меняет и размер строки и размер столбца).
																				   //
class matrix {																	   // /*	начало класса		    */
public:																			   //
	matrix(const strmatr& str);													   // Конструктор, позволяющий создавать объект matrix следующим образом: matrix m(	{  {0,1}, {1,2}, {3,4}, {4,5}  }	); // матрица 4 на 2.
	
	matrix();																	   // Конструктор, позволяющий создавать объект matrix следующим образом: matrix m;
	void SetMatr(const strmatr& str);											   //
	void InsertOn(const double& value, const size_t& i, const size_t& j);
	double getElement(const size_t& i, const size_t& j)const;					   // Метод, позволяющий получить значение элемента матрицы на позиции {i j}.
	pair<size_t, size_t> Get_MxN() const;										   // Метод, позволяющий получить размер матрицы. Резльтат записывается в пару (библиотека utility). Ответ в форме <строка, столбец> <.first, .second>
	void PrintMatrix();															   // Метод, позволяющий вывести матрицу в консоль
	double Determinant() const;													   // Метод, позволяющий получить определитель матрицы 2х2 3х3 4х4
																				   //
	matrix PreMinor(const size_t& row, const size_t& col) const;				   // Метод, позволяющий получить матрицу-минор для элемента на позиции {row,col} (матрица без строчки с индексом row и столбцом col).
	matrix Inverted(const double& D) const;										   // Метод, позволяющий получить обратную матрицу (^-1). Нужна для работы оператора деления. На вход должен подаваться дискриминант изначальной (неинверт.) матрицы.
																				   //
	friend matrix operator*(const matrix& m, const double& value);				   //  /*	Дружественные функции	*/
	friend matrix operator*(const double& value, const matrix& m);				   //  
	friend matrix operator*(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix operator/(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix operator+(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix operator-(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix Transponierte(const matrix& M);								   //  /*							*/
private:																		   //
																				   //
	vector<double> Get_Line(const size_t& i)const;								   // Приватный метод, позволяющий получить i-тую строку матрицы
	vector<double> Get_Column(const size_t& i)const;							   // Приватный метод, позволяющий получить i-тый столбец матрицы
	double det4() const;														   // Приватный костыль для определителя 4х4
	strmatr _M;																	   // М А Т Р И Ц А
																				   //
};																				   //  /*	конец класса			*/
																				   //
ostream& operator << (ostream& os, const vector<double>& r);					   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА вывода вектора.
ostream& operator << (ostream& os, const strmatr& r);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА вывода матрицы-строки.												     // Что-то из этого надо убрать, наверное.
matrix operator*(const double& value, const matrix& M);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА  * между матрицоы и числом.
matrix operator*(const matrix& M, const double& value);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА  * между числом и матрицой.
matrix operator*(const matrix& lhs, const matrix& rhs);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА  * между матрицей и матрицей.
matrix operator/(const matrix& lhs, const matrix& rhs);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА  / между матрицей и матрицей.
matrix operator+(const matrix& lhs, const matrix& rhs);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА  + между матрицей и матрицей.
matrix operator-(const matrix& lhs, const matrix& rhs);							   // ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРА  - между матрицей и матрицей.
matrix Transponierte(const matrix& M);											   //				  ОПЕРАЦИЯ транспонирования матрицы.