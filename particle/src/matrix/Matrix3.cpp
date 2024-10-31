#include "Matrix3.h"
#include <stdexcept>

Matrix3::Matrix3() 
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            
            elements[i][j] = 0.0f;
        }
    }
}

Matrix3::Matrix3(float elements[3][3]) 
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            this->elements[i][j] = elements[i][j];
        }
    }
}

void Matrix3::print_matrix()  
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            std::cout << elements[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
float Matrix3::get(int row, int col)  
{
    return elements[row][col];
}

void Matrix3::set(int row, int col, float value)
{
    elements[row][col] = value;
}

Matrix3 Matrix3::operator+(const Matrix3& other)  
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.elements[i][j] = elements[i][j] + other.elements[i][j];
        }
    }
    return result;
}

Matrix3& Matrix3::operator+=(const Matrix3& other) 
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			elements[i][j] += other.elements[i][j];
		}
	}
	return *this;
}

Matrix3 Matrix3::operator-(const Matrix3& other)  
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            result.elements[i][j] = elements[i][j] - other.elements[i][j];
        }
    }
    return result;
}

Matrix3 Matrix3::operator-()
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.elements[i][j] = -elements[i][j];  // Multiplie chaque élément par -1
        }
    }
    return result;
}

Matrix3& Matrix3::operator-=(const Matrix3& other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            elements[i][j] -= other.elements[i][j];
        }
    }
	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& other)  
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.elements[i][j] = 0;
            for (int k = 0; k < 3; ++k)
            {
                result.elements[i][j] += elements[i][k] * other.elements[k][j];
            }
        }
    }
    return result;
}

Matrix3& Matrix3::operator*=(const Matrix3& other)
{
	Matrix3 result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.elements[i][j] = 0;
			for (int k = 0; k < 3; ++k)
			{
				result.elements[i][j] += elements[i][k] * other.elements[k][j];
			}
		}
	}
	*this = result;
	return *this;
}

Matrix3 Matrix3::operator*(float scalar)  
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.elements[i][j] = elements[i][j] * scalar;
        }
    }
    return result;
}

Matrix3& Matrix3::operator*=(float scalar)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            elements[i][j] *= scalar;
        }
    }
    return *this;
}

bool Matrix3::operator==(const Matrix3& other)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (elements[i][j] != other.elements[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

Matrix3 Matrix3::transpose()  
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.elements[i][j] = elements[j][i];
        }
    }
    return result;
}

float Matrix3::determinant()  
{
    return elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1])
        - elements[0][1] * (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0])
        + elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
}


