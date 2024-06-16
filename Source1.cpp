#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

template <typename T>
class Matrix
{
private:
	int rows;
	int columns;
	vector <vector<T>> matrix;
public:
	// Empty const
	Matrix()
	{
		rows = 0;
		columns = 0;
	}
	//Const of known size
	Matrix(int current_rows, int current_columns)
	{
		rows = current_rows;
		columns = current_columns;
		matrix = vector <vector<T>>(rows, vector<T>(columns));
	}
	//Const for reading matrix from file
	Matrix(string filename)
	{
		ifstream fileinput(filename);
		fileinput >> rows >> columns;
		matrix = vector <vector<T>>(rows, vector<T>(columns));
		for (int i = 0; i < rows; ++i)
			for (int j = 0; i < columns; ++j)
				fileinput >> matrix[i][j];
	}
	//Operator "+"
	Matrix operator+(const Matrix& other)
	{
		if ((rows != other.rows) or (columns != other.columns))
			throw invalid_argument("Error: diff sizes of matrices (+)");
		Matrix result(rows, columns);
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < columns; ++j)
				result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
		return result;
	}
	//Operator "-"
	Matrix operator-(const Matrix& other)
	{
		if ((rows != other.rows) or (columns != other.columns))
			throw invalid_argument("Error: diff sizes of matrices (-)");
		Matrix result(rows, columns);
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < columns; ++j)
				result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
		return result;
	}
	//Operator "*" for matrices
	Matrix operator*(const Matrix& other)
	{
		if ((rows != other.rows) or (columns != other.columns))
			throw invalid_argument("Error: diff sizes of matrices (*)");
		Matrix result(rows, other.columns);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < other.columns; ++j)
			{
				T value = 0;
				for (int l = 0; l < columns; ++l)
					value += matrix[i][l] * other.matrix[l][j];
				result.matrix[i][j] = value;
			}
		}
		return result;
	}
	//Operator "*" for scalar
	Matrix operator*(int scalar)
	{
		Matrix result(rows, columns);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; ++j)
				result.matrix[i][j] = matrix[i][j] * scalar;
		return result;
	}
	//Operator "="
	Matrix operator=(const Matrix& other)
	{
		if ((rows != other.rows) or (columns != other.columns))
			throw invalid_argument("Error: diff sizes of matrices (=)");
		this->rows = other.rows;
		this->columns = other.columns;
		this->matrix = other.matrix;
	}
	//Operator for output matrix to console
	friend ostream& operator<<(ostream& output, const Matrix& other)
	{
		for (auto row : other.matrix)
		{
			for (auto element : row)
				output << element << " ";
			output << endl;
		}
		return output;
	}
	//Operator for input matrix from console
	friend istream& operator>>(istream& input, Matrix& other)
	{
		int volume = other.rows * other.columns;
		cout << "Volume of current matrix: " << volume << endl;
		for (int i = 0; i < other.rows; ++i)
			for (int j = 0; j < other.columns; ++j)
				input >> other.matrix[i][j];
		return input;
	}
	//Operator "!" for obratnaya matrix
	Matrix<double> operator!()
	{
		if (this->rows != this->columns)
			throw invalid_argument("Error: matrix is not square (!)");
		int length = this->rows; //Pripishem* k ishodnoi matrice edinichnuyu v vide vektora is vektorov
		vector<vector<double>> dopolnMatrix(length, vector<double>(length * 2, 0.0));
		for (int i = 0; i < length; ++i)
		{
			dopolnMatrix[i][i + length] = 1.0;
			for (int j = 0; j < length; j++)
				dopolnMatrix[i][j] = this->matrix[i][j]
		}
		for (int i = 0; i < length; ++i)
		{
			if (dopolnMatrix[i][i] == 0)
				throw invalid_argument("Error: there is no obratnaya matrix");
			double temp = dopolnMatrix[i][i];
			for (int j = 0; j < 2 * length; ++j)
				dopolnMatrix[i][j] = dopolnMatrix[i][j] / temp;
			for (int l = 0; l < length; ++l)
				if (l != i)
				{
					double m = dopolnMatrix[l][i];
					for (int f = 0; f < 2 * length; ++f)
						dopolnMatrix[l][f] -= dopolnMatrix[i][f] * m;
				}
		}

		vector<vector<double>> obratn(n, vector<double>(length, 0));
		for (int i = 0; i < length; ++i)
			for (int j = 0; j < length; ++j)
				obratn[i][j] = dopolnMatrix[i][j + length];
		return obratn;
	}
	// Input from file
	void inputMatrixFile(string fileinput)
	{
		ifstream input(fileinput);
		input >> rows >> columns;
		matrix = vector<vector<T>>(rows, vector<T>(columns));
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < columns; ++j)
				input >> matrix[i][j];
		input.close();
	}
	// Output from file
	void printMatrixFile(string fileoutput)
	{
		ofstream output(fileoutput);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
				output << matrix[i][j] << " ";
			output << endl;
		}
		output.close();
	}
	// Uno matrix
	static Matrix unoMatrix(int rows)
	{
		vector<vector<T>> uno = vector<vector<T>>(rows, vector<T>(rows, 0));
		for (int i = 0; i < rows; ++i)
			uno[i][i] = 1;
		return uno;
	}
	// Zero matrix
	static Matrix zeroMatrix(int rows, int columns)
	{
		Matrix zero = vector<vector<T>>(rows, vector<T>(columns));
		return zero;
	}
};


int main()
{
	Matrix<int> intMatrix(3, 3);
	cin >> intMatrix;
	cout << Matrix<int>::zeroMatrix(3, 3) << endl;
	cout << Matrix<int>::unoMatrix(3) << endl;
}