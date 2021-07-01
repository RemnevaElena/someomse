#pragma once

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Matrix
{
private:
	int rows;
	int colms;

	T **values;
	string name;
public:
	Matrix();
	Matrix(int rows, int colms, string name, vector<T> vals);
	~Matrix();

	Matrix(const Matrix<T>& secmat)
	{

		values = new T* [secmat.rows];
		for (int i = 0; i < secmat.rows; i++)
			values[i] = new T[secmat.colms];
		
		rows = secmat.rows;
		colms = secmat.colms;
		name = secmat.name;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < colms; j++)
				values[i][j] = secmat.values[i][j];

	}
	int GetRows() {
		return this.rows;
	}
	int GetColms() {
		return this.colms;
	}
	int GetSize() {
		return (this.row*this.colms);
	}
	
	Matrix operator = (const Matrix<T>& secmat) {

		if (colms > 0)
			for (int i = 0; i < rows; i++)
				delete[] values[i];

		if (rows > 0)
			delete[] values;

		values =  new T* [secmat.rows];
		for (int i = 0; i < secmat.rows; i++)
			values[i] = new T[secmat.colms];

		name = secmat.name;
		rows = secmat.rows;
		colms = secmat.colms;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < colms; j++)
				values[i][j] = secmat.values[i][j];

		return *this;
	}

	Matrix operator + (const Matrix<T>& secmat) {

		if (rows == secmat.rows && colms == secmat.colms)
		{
			Matrix temp;
			temp.colms = this->colms;
			temp.rows = this->rows;
			temp.name = this->name;

			temp.values = new T * [rows];

			for (int i = 0; i < rows; i++) {
				temp.values[i] = new T[colms];
				for (int j = 0; j < colms; j++)
					temp.values[i][j] = values[i][j] + secmat.values[i][j];
			}
			return temp;
		}
		else
		{
			cout << "¬ы пытаетесь сложить матрицы разных размеров." << endl;
			return *this;
		}
	}
	Matrix operator - (const Matrix<T>& secmat) {

		if (rows == secmat.rows && colms == secmat.colms)
		{
			Matrix temp;
			temp.colms = this->colms;
			temp.rows = this->rows;
			temp.name = this->name;

			temp.values = new T * [rows];

			for (int i = 0; i < rows; i++) {
				temp.values[i] = new T[colms];
				for (int j = 0; j < colms; j++)
					temp.values[i][j] = values[i][j] - secmat.values[i][j];
			}
			return temp;
		}
		else
		{
			cout << "¬ы пытаетесь вычесть матрицы разных размеров." << endl;
			return *this;
		}
	}
	Matrix operator * (const Matrix<T>& secmat) {

		if (colms == secmat.rows)
		{
			Matrix temp;
			temp.rows = this->rows;
			temp.colms = secmat.colms;
			temp.name = this->name;

			temp.values = new T * [rows];
			for (int i = 0; i < rows; i++)
				temp.values[i] = new T[secmat.colms];

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < secmat.colms; j++) {
					temp.values[i][j] = 0;
					for (int z = 0; z < colms; z++)
					{
						temp.values[i][j] += values[i][z] * secmat.values[z][j];
					}
				}
			}
			return temp;
		}
		else
		{
			cout << "¬ы пытаетесь перемножить матрицы несовместимых размеров." << endl;
			return *this;
		}
	};

	Matrix operator * (const T& secmat) {
		Matrix temp;
		temp.rows = this->rows;
		temp.colms = this->colms;
		temp.name = this->name;

		temp.values = new T * [rows];
		for (int i = 0; i < rows; i++)
			temp.values[i] = new T[colms];

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < colms; j++)
				temp.values[i][j] = values[i][j] * secmat;

		return temp;

	};

	/*Matrix operator / (const Matrix<T>& secmat) {
		if (rows == colms)
		{
			Matrix<T> matrixminors;
			matrixminors.rows = rows;
			matrixminors.colms = colms;
			matrixminors.name = name;

			matrixminors.values = new T * [rows];
			for (int i = 0; i < rows; i++)
				matrixminors.values[i] = new T[colms];

			for (int i = 0; i < colms; i++)
				for (int j = 0; j < colms; j++) {
					if (j%2 != 0)
						matrixminors.values[i][j] = (this->MatrixDelRowColm(i, j)).MatrixDet(0)*-1;
					else
						matrixminors.values[i][j] = (this->MatrixDelRowColm(i, j)).MatrixDet(0);
				}

			matrixminors = matrixminors.MatrixTrans();
			return secmat*(matrixminors / (this->MatrixDet));
		}
		else {
			cout << "ƒл€ неквадратных матриц обратных матриц не существует." << endl;
			return *this;
		}
	};*/
	Matrix<T> MatrixDelRowColm(int n1, int n2) {
		int size = rows - 1;
		T *arr = new T[size*size];
		int j = 0;

		for (int i = 0; i < rows*rows; i++) {
			if (i / rows != n1 && i % rows != n2) {
				arr[j] = values[i / rows][i % rows];
				j++;
			}
		}

		Matrix<T> temp = { size, size, name, arr};
		delete[] arr;
		return temp;
	}

	T MatrixDet(T sum) {
		if (rows == colms)
		{
			if (rows == 2) {
				return values[0][0] * values[1][1] - values[0][1] * values[1][0];
			}
			else
			{
				Matrix<T>* matrixes = new Matrix<T>[colms];
				for (int i = 0; i < colms; i++)
				{
					matrixes[i] = (this->MatrixDelRowColm(0, i));
				}

				for (int i = 0; i < colms; i++)
				{
					if (i % 2 != 0)
						sum += matrixes[i].MatrixDet(0)* values[0][i]*-1;
					else
						sum += matrixes[i].MatrixDet(0)* values[0][i];
				}
				delete[] matrixes;
			}
		}
		else {
			cout << "¬ы пытаетесь найти определитель у неквардатной матрицы." << endl;
			return 0;
		}
		return sum;
	}
	Matrix<T> MatrixTrans() {

		Matrix temp;
		temp.rows = this->colms;
		temp.colms = this->rows;
		temp.name = this->name;

		temp.values = new T * [temp.rows];
		for (int i = 0; i < temp.rows; i++)
			temp.values[i] = new T[temp.colms];

		for (int i = 0; i < temp.rows; i++)
			for (int j = 0; j < temp.colms; j++)
				temp.values[i][j] = values[j][i];

		return temp;
	}
	friend istream& operator>> (istream& in, Matrix<T>& fr) {
		cout << "¬ведите название матрицы: " << endl;
		in >> fr.name;
		cout << "¬ведите количество строк: " << endl;
		in >> fr.rows;
		cout << "¬ведите количество колонок: " << endl;
		in >> fr.colms;

		fr.values = new T*[fr.rows];
		for (int i = 0; i < fr.rows; i++)
			fr.values[i] = new T[fr.colms];

		for (int i = 0; i < fr.rows; i++) {
			cout << "¬ведите значени€ " << i+1 << " сроки:" << endl;
			for (int j = 0; j < fr.colms; j++)
				in >> fr.values[i][j];
		}
		return in;
	}
	friend ostream& operator<< (ostream& os, const Matrix<T>& fr) {
		//cout << fr.name << endl;
		for (int i = 0; i < fr.rows; i++) {
			for (int j = 0; j < fr.colms; j++)
				os << fr.values[i][j] << " ";
			os << endl;
		}
		return os;
	}
	
};


template<class T>
inline Matrix<T>::Matrix() {
	name = "Matrix Template";
	colms = 0;
	rows = 0;
}

template<typename T>
inline Matrix<T>::Matrix(int rows, int colms, string name, vector<T> vals)
{
	this->rows = rows;
	this->colms = colms;
	this->values = new T*[rows];
	for (int i = 0; i < rows; i++)
		values[i] = new T[colms];

	for (int i = 0; i < rows*colms; i++) {
		values[i/colms][i % colms] = vals[i];
	}
	this->name = name;
}

template<typename T>
inline Matrix<T>::~Matrix()
{
	if (colms > 0)
		for (int i = 0; i < rows; i++)
			delete [] values[i];

	if (rows > 0 )
		delete[] values;
}


