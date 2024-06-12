#include <iostream>

using namespace std;

#define MATRIX float**

int Power(int number, int power)
{
    int result = number;
    for (int i = 0; i < power - 1; i++)
    {
        result *= number;
    }
    return result;
}

namespace Vector
{
    float DotProduct(float* VectorOne, float* Vector2, int length)
    {
        float result = 0;
        for (int i = 0; i < length; i++)
        {
            result += VectorOne[i] * Vector2[i];
        }
        return result;
    }
}

namespace Matrix
{
    // prints a matrix
    void PrintMatrix(float** pMatrix, int rows, int columns)
    {
              // iterates through the matrix rows
        for (int row = 0; row < rows; row++)
        {
            // iterates through the matrix columns
            for (int column = 0; column < columns; column++)
            {
                // prints the matrix value
                cout << pMatrix[row][column] << "\t";
            }
            // adds a newline
            cout << endl;
        }
    }

    float** Multiply(float** pMatrixOne, int rowsOne, int columnsOne, float** pMatrixTwo, int rowsTwo, int columnsTwo)
    {
        if (columnsOne == rowsTwo)
        {
            // creates a new matrix of the correct size
            float** Result = new float*[rowsOne];
            // iterates through the matrix columns
            for (int i = 0; i < rowsOne; i++)
                // creates a new column
                Result[i] = new float[columnsTwo];
            // iterates through the matrix rows
            for (int row = 0; row < rowsOne; row++)
            {
                // iterates through the matrix columns
                for (int column = 0; column < columnsTwo; column++)
                {
                    float* Vect = new float[rowsTwo];
                    // iterates through the matrix rows
                    for (int x = 0; x < rowsTwo; x++)
                    {
                        Vect[x] = pMatrixTwo[x][column];
                    }
                    Result[row][column] = Vector::DotProduct(pMatrixOne[row], Vect, columnsOne);
                }
            }
            return Result;
        }
        return 0;
    }

    // transposes the given matrix
    float** Transpose(float** pMatrix, int rows, int columns)
    {
        // creates a new matrix of the correct size
        float** Transposed = new float*[columns];
        // iterates through the matrix columns
        for (int i = 0; i < columns; i++)
            // creates a new column
            Transposed[i] = new float[rows];
        // iterates through the matrix rows
        for (int row = 0; row < rows; row++)
        {
            // iterates through the matrix columns
            for (int column = 0; column < columns; column++)
            {
                // adds the row value to the column
                Transposed[column][row] = pMatrix[row][column];
            }
        }
        // returns the matrix
        return Transposed;
    }

    // returns the minor matrix of a given matrix
    float** Minor(float** pMatrix, int rows, int columns, int remove_row, int remove_column)
    {
        // creates a new matrix of the correct size
        float** Minor = new float*[rows - 1];
        // iterates through the matrix columns
        for (int i = 0; i < rows - 1; i++)
            // creates a new column
            Minor[i] = new float[columns - 1];
        // iterates through the matrix rows
        for (int row = 0, minor_row = 0; row < rows; row++, minor_row++)
        {
            // checks the row index
            if (row != remove_row)
            {
                // iterates through the matrix columns
                for (int column = 0, minor_column = 0; column < columns; column++, minor_column++)
                {
                    // checks the column index
                    if (column != remove_column)
                    {
                        // adds the row value to the column
                        Minor[minor_row][minor_column] = pMatrix[row][column];
                    }
                    else
                    {
                        minor_column--;
                    }
                }
            }
            else
            {
                minor_row--;
            }
        }
        // returns the matrix
        return Minor;
    }

    // returns the determinant of the given matrix
    int Determinant(float** pMatrix, int rows, int columns)
    {
        if (rows == 1 && columns == 1)
        {
            return pMatrix[0][0];
        }
        // stores the determinant
        int determinant = 0;
        // iterates through the first row elements
        for (int element = 0; element < columns; element++)
        {
            // calculates the determinant
            determinant += pMatrix[0][element] * Power((-1), (1+(element + 1))) * Determinant(Minor(pMatrix, rows, columns, 0, element), rows-1, columns-1);
        }
        // returns the determinant
        return determinant;
    }

    // returns the adjoint of the given matrix
    float** Adjoint(float** pMatrix, int rows, int columns)
    {
        // creates a new matrix of the correct size
        float** Adjoint = new float*[rows];
        // iterates through the matrix columns
        for (int i = 0; i < rows; i++)
            // creates a new column
            Adjoint[i] = new float[columns];
        // iterates through the matrix rows
        for (int row = 0; row < rows; row++)
        {
            // iterates through the matrix columns
            for (int column = 0; column < columns; column++)
            {
                // calculates the element via the determinant of a minor
                Adjoint[row][column] = Power((-1), ((row + 1) + (column + 1))) * Determinant(Minor(pMatrix, rows, columns, row, column), rows-1, columns-1);
            }
        }
        // transposes and returns the matrix
        return Transpose(Adjoint, rows, columns);
    }

    // divides the given matrix by the given scalar
    float** ScalarDivide(float** pMatrix, int rows, int columns, float scalar)
    {
        // iterates through the matrix rows
        for (int row = 0; row < rows; row++)
        {
            // iterates through the matrix columns
            for (int column = 0; column < columns; column++)
            {
                // adds the row value to the column
                pMatrix[row][column] /= scalar;
            }
        }
        // returns the matrix
        return pMatrix;
    }

    // calculates and returns the inverse of the given matrix
    float** Inverse(float** pMatrix, int rows, int columns)
    {
        // creates a new matrix of the correct size
        float** pAdjoint = new float*[rows];
        // iterates through the matrix columns
        for (int i = 0; i < rows; i++)
            // creates a new column
            pAdjoint[i] = new float[columns];
        // gets the adjoint of the matrix
        pAdjoint = Adjoint(pMatrix, rows, columns);
        // gets the determinant of the matrix
        float det = Determinant(pMatrix, rows, columns);
        // divides the matrix by the detriment
        return ScalarDivide(pAdjoint, rows, columns, det);
    }
}

int main()
{
    // creates a new matrix of the correct size
    float** pMatrix = new float*[3];
    // creates a new column
    pMatrix[0] = new float[3]{ 2, 0, 0 };
    // creates a new column
    pMatrix[1] = new float[3]{ 0, 3, 0 };
    // creates a new column
    pMatrix[2] = new float[3]{ 0, 0, 7 };
    // prints the matrix
    Matrix::PrintMatrix(pMatrix, 3, 3);
    // calculates the inverse matrix
    float** pInverse = Matrix::Inverse(pMatrix, 3, 3);
    // prints the matrix
    Matrix::PrintMatrix(pInverse, 3, 3);
    // calculate the identity matrix
    float** Identity = Matrix::Multiply(pInverse, 3, 3, pMatrix, 3, 3);
    // prints the matrix
    Matrix::PrintMatrix(Identity, 3, 3);
    // prints the matrix
    // Matrix::PrintMatrix(pMatrix, 4, 4);
    // transposes the matrix
    //pMatrix = Matrix::Transpose(pMatrix, 4, 6);
    // creates a new line
    //cout << endl;
    // prints the matrix
    //Matrix::PrintMatrix(pMatrix, 6, 4);
    return 0;
}
