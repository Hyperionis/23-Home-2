#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

template <typename Type>
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
		matrix = vector <vector<Type>>(rows, vector<Type>(columns));
	}
	//Const for reading matrix from file
	Matrix(string filename)
	{
		ifstream fileinput(filename);
		fileinput >> rows >> columns;
		matrix = vector <vector<Type>>(rows, vector<Type>(columns));
		for (int i = 0; i < rows; ++i)
			for (int j = 0; i < columns; ++j)
				fileinput >> matrix[i][j];
	}
	//Operator "+"
	Matrix operator+(const Matrix$ other)
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
	Matrix operator-(const Matrix$ other)
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
				Type value = 0;
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
	friend ostream& operator<<(ostream& output, const Matrix* other)
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
	friend istream& operator>>(istream& input, Maxtrix& other)
	{
		int volume = other.rows * other.columns;
		cout << "Valume of current matrix: " << volume << endl;
		for (int i = 0; i < other.rows; ++i)
			for (int j = 0; j < other.columns; ++j)
				input >> other.matrix[i][j];
		return input;
	}
	//Operator "!" for obratnaya matrix
	Matrix<Type> operator!()
	{
		if (this->rows != this->columns)
			throw invalid_argument("Error: matrix is not square (!)");
		int n = this->rows;
	}
};


int main()
{
	Matrix<int> intMatrix(3, 3);
	cin >> intMatrix;
}