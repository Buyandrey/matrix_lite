#pragma once

#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;
using strmatr = vector<vector<double>>;											   // ������� ��� ������� ��������, ����� ������� ����. ������ �������� ���� == "�������-������".
																				   //
void RESIZEvv(strmatr& vv, const size_t& m1, const size_t& n2);					   // ������� ������� ��������� �� ������ �������-������ � ������ � ������ (������ � ������ ������ � ������ �������).
																				   //
class matrix {																	   // /*	������ ������		    */
public:																			   //
	matrix(const strmatr& str);													   // �����������, ����������� ��������� ������ matrix ��������� �������: matrix m(	{  {0,1}, {1,2}, {3,4}, {4,5}  }	); // ������� 4 �� 2.
	
	matrix();																	   // �����������, ����������� ��������� ������ matrix ��������� �������: matrix m;
	void SetMatr(const strmatr& str);											   //
	void InsertOn(const double& value, const size_t& i, const size_t& j);
	double getElement(const size_t& i, const size_t& j)const;					   // �����, ����������� �������� �������� �������� ������� �� ������� {i j}.
	pair<size_t, size_t> Get_MxN() const;										   // �����, ����������� �������� ������ �������. �������� ������������ � ���� (���������� utility). ����� � ����� <������, �������> <.first, .second>
	void PrintMatrix();															   // �����, ����������� ������� ������� � �������
	double Determinant() const;													   // �����, ����������� �������� ������������ ������� 2�2 3�3 4�4
																				   //
	matrix PreMinor(const size_t& row, const size_t& col) const;				   // �����, ����������� �������� �������-����� ��� �������� �� ������� {row,col} (������� ��� ������� � �������� row � �������� col).
	matrix Inverted(const double& D) const;										   // �����, ����������� �������� �������� ������� (^-1). ����� ��� ������ ��������� �������. �� ���� ������ ���������� ������������ ����������� (��������.) �������.
																				   //
	friend matrix operator*(const matrix& m, const double& value);				   //  /*	������������� �������	*/
	friend matrix operator*(const double& value, const matrix& m);				   //  
	friend matrix operator*(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix operator/(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix operator+(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix operator-(const matrix& lhs, const matrix& rhs);				   //  
	friend matrix Transponierte(const matrix& M);								   //  /*							*/
private:																		   //
																				   //
	vector<double> Get_Line(const size_t& i)const;								   // ��������� �����, ����������� �������� i-��� ������ �������
	vector<double> Get_Column(const size_t& i)const;							   // ��������� �����, ����������� �������� i-��� ������� �������
	double det4() const;														   // ��������� ������� ��� ������������ 4�4
	strmatr _M;																	   // � � � � � � �
																				   //
};																				   //  /*	����� ������			*/
																				   //
ostream& operator << (ostream& os, const vector<double>& r);					   // ��������������� ��������� ������ �������.
ostream& operator << (ostream& os, const strmatr& r);							   // ��������������� ��������� ������ �������-������.												     // ���-�� �� ����� ���� ������, ��������.
matrix operator*(const double& value, const matrix& M);							   // ��������������� ���������  * ����� �������� � ������.
matrix operator*(const matrix& M, const double& value);							   // ��������������� ���������  * ����� ������ � ��������.
matrix operator*(const matrix& lhs, const matrix& rhs);							   // ��������������� ���������  * ����� �������� � ��������.
matrix operator/(const matrix& lhs, const matrix& rhs);							   // ��������������� ���������  / ����� �������� � ��������.
matrix operator+(const matrix& lhs, const matrix& rhs);							   // ��������������� ���������  + ����� �������� � ��������.
matrix operator-(const matrix& lhs, const matrix& rhs);							   // ��������������� ���������  - ����� �������� � ��������.
matrix Transponierte(const matrix& M);											   //				  �������� ���������������� �������.