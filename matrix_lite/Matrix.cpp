#include "Matrix.h"

using namespace std;
using strmatr = vector<vector<double>>;

void RESIZEvv(vector<vector<double>>& vv, const size_t& m1, const size_t& n2) {
	vv.resize(m1);
	for (vector<double>& i : vv) i.resize(n2);
}

matrix::matrix(const strmatr& str) {
	_M = str;
}
void matrix::SetMatr(const strmatr& str) {
	_M = str;
}
matrix::matrix() {}
double matrix::getElement(const size_t& i, const size_t& j)const {
	return _M.at(i).at(j);
}
pair<size_t, size_t> matrix::Get_MxN() const { return(make_pair(_M.size(), _M.at(0).size())); }
void matrix::PrintMatrix() {
	for (size_t i = 0; i < Get_MxN().first; i++) {
		for (size_t j = 0; j < Get_MxN().second; j++)
			cout << setw(4) << setfill(' ') << _M.at(i).at(j) << ' ';
		cout << endl;
	}
	cout << endl;
}
void  matrix::InsertOn(const double& value, const size_t& i, const size_t& j) {
	_M.at(i).at(j) = value;
}
double matrix::Determinant() const {
	{
		size_t m = Get_MxN().first;
		size_t n = Get_MxN().second;
		if (m == n) {
			switch (m) {
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
				return (det4()); } break;
			default: {
				throw invalid_argument("Matrx size more then 4");
				break;
			}
			}

		}
		else {
			throw invalid_argument("Matrix's (N_size != M_size)");
		}
	}
}

matrix matrix::PreMinor(const size_t& row, const size_t& col) const
{
	//возвращает матрицу минора(?)
	size_t size_minor = _M.size() - 1;
	strmatr vv;
	RESIZEvv(vv, size_minor, size_minor);

	size_t i, j, in, jn;

	for (i = 0, in = 0; i < size_minor + 1; i++) {
		if (i != row) {
			for (j = 0, jn = 0; j < size_minor + 1; j++) {
				if (j != col) {
					vv.at(in).at(jn++) = getElement(i, j);
				}
			}
			in++;
		}
	}
	matrix newMatrix(vv);
	return newMatrix;
}
matrix matrix::Inverted(const double& D) const {
	size_t size = _M.size();
	if ((size - 1) <= 0) {
		throw invalid_argument("Matrx less or equal then 0");
	}
	strmatr vv;
	RESIZEvv(vv, size, size);
	size_t i, j;

	for (j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			vv.at(j).at(i) = this->PreMinor(i, j).Determinant() * ((i + j) % 2 ? -1 : 1);
		}
	}
	matrix newMatrix(vv);

	return (1 / D) * newMatrix;
}

vector<double> matrix::Get_Line(const size_t& i)const {
	size_t size = Get_MxN().second;
	if (i > size)
		throw invalid_argument("Can't cout this line, may be out of range !");
	else {
		return _M.at(i);
	}
}
vector<double> matrix::Get_Column(const size_t& i)const {
	vector<double> Column;
	size_t size = Get_MxN().first;
	Column.resize(size);
	if (i > size)
		throw invalid_argument("Can't cout this line, may be out of range !");
	else {
		size_t j = 0;
		for (double& d : Column) {
			d = _M.at(j++).at(i);
		}
		return Column;
	}
}
double matrix::det4() const {
	strmatr m03, m13, m23, m33;
	m03 = {
		{getElement(1,0),getElement(1,1),getElement(1,2)},
		{getElement(2,0),getElement(2,1),getElement(2,2)},
		{getElement(3,0),getElement(3,1),getElement(3,2)}
	};
	m13 = {
		{getElement(0,0),getElement(0,1),getElement(0,2)},
		{getElement(2,0),getElement(2,1),getElement(2,2)},
		{getElement(3,0),getElement(3,1),getElement(3,2)}
	};
	m23 = {
		{getElement(0,0),getElement(0,1),getElement(0,2)},
		{getElement(1,0),getElement(1,1),getElement(1,2)},
		{getElement(3,0),getElement(3,1),getElement(3,2)}
	};
	m33 = {
		{getElement(0,0),getElement(0,1),getElement(0,2)},
		{getElement(1,0),getElement(1,1),getElement(1,2)},
		{getElement(2,0),getElement(2,1),getElement(2,2)}
	};
	matrix m0(m03), m1(m13), m2(m23), m3(m33);
	double
		d0 = m0.Determinant(),
		d1 = m1.Determinant(),
		d2 = m2.Determinant(),
		d3 = m3.Determinant();

	return(
		(-1) * getElement(0, 3) * d0
		+
		(+1) * getElement(1, 3) * d1
		+
		(-1) * getElement(2, 3) * d2
		+
		(+1) * getElement(3, 3) * d3
		);
}

ostream& operator << (ostream& os, const vector<double>& r) {
	os << "[ ";
	for (const double& i : r) {
		os << i << ' ';
	}
	return  os << ']';
}
ostream& operator << (ostream& os, const strmatr& r) {
	for (size_t i = 0; i < r.at(0).size(); i++) {
		for (size_t j = 0; j < r.size(); j++)
			cout << setw(15) << setfill(' ') << r.at(i).at(j) << endl;
	}
	return  os;
}
matrix operator*(const double& value, const matrix& M) {

	size_t n = M.Get_MxN().second;
	size_t m = M.Get_MxN().first;

	strmatr vv;
	RESIZEvv(vv, m, n);
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			vv.at(i).at(j) = M.getElement(i, j) * value;

	matrix r(vv);

	return(r);
}
matrix operator*(const matrix& M, const double& value) {

	size_t n = M.Get_MxN().second;
	size_t m = M.Get_MxN().first;

	strmatr vv;
	RESIZEvv(vv, m, n);
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			vv.at(i).at(j) = M.getElement(i, j) * value;

	matrix r(vv);

	return(r);
}
matrix operator*(const matrix& lhs, const matrix& rhs) {

	size_t m1 = lhs.Get_MxN().first;//m*n
	size_t m2 = rhs.Get_MxN().first;//m*n
	size_t n1 = lhs.Get_MxN().second;
	size_t n2 = rhs.Get_MxN().second;
	if (n1 == m2) {
		strmatr vv;
		RESIZEvv(vv, m1, n2);

		for (size_t i = 0; i < m1; i++)
			for (size_t j = 0; j < n2; j++)
			{
				vv.at(i).at(j) = 0;
				for (size_t k = 0; k < n1; k++)
					vv.at(i).at(j) += lhs.getElement(i, k) * rhs.getElement(k, j);
			}

		matrix res(vv);
		return res;
	}
	else {
		throw invalid_argument("Wrong sizes of matrix");
	}
}
matrix operator/(const matrix& lhs, const matrix& rhs) {
	return(lhs * rhs.Inverted(rhs.Determinant()));
}
matrix operator+(const matrix& lhs, const matrix& rhs) {
	size_t m1 = lhs.Get_MxN().first;//m*n
	size_t m2 = rhs.Get_MxN().first;//m*n
	size_t n1 = lhs.Get_MxN().second;
	size_t n2 = rhs.Get_MxN().second;

	if (m1 == m2 && n1 == n2) {
		strmatr vv; RESIZEvv(vv, m1, n1);
		for (size_t i = 0; i < m1; i++)
			for (size_t j = 0; j < n1; j++)
				vv.at(i).at(j) = (lhs.getElement(i, j) + rhs.getElement(i, j));

		matrix res(vv);
		return(res);
	}
	else {
		throw invalid_argument("Matrix's size are not equal !!!");
	}
}
matrix operator-(const matrix& lhs, const matrix& rhs) {
	size_t m1 = lhs.Get_MxN().first;//m*n
	size_t m2 = rhs.Get_MxN().first;//m*n
	size_t n1 = lhs.Get_MxN().second;
	size_t n2 = rhs.Get_MxN().second;

	if (m1 == m2 && n1 == n2) {
		strmatr vv; RESIZEvv(vv, m1, n1);
		for (size_t i = 0; i < m1; i++)
			for (size_t j = 0; j < n1; j++)
				vv.at(i).at(j) = (lhs.getElement(i, j) - rhs.getElement(i, j));

		matrix res(vv);
		return(res);
	}
	else {
		throw invalid_argument("Matrix's size are not equal !!!");
	}
}
matrix Transponierte(const matrix& M) {
	size_t m = M.Get_MxN().first, n = M.Get_MxN().second;

	size_t new_m = n, new_n = m;
	strmatr vv; RESIZEvv(vv, new_m, new_n);

	for (size_t i = 0; i < n; i++)
		vv.at(i) = M.Get_Column(i);

	matrix res(vv);
	return res;
}