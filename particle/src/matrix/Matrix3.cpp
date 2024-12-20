#include "Matrix3.h"

#include <iostream>
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

Matrix3::Matrix3(float diagonal[3]) 
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            if (i == j)
            {
                elements[i][j] = diagonal[i];
            }
            else
            {
                elements[i][j] = 0.0f;
            }
        }
    }
}

Matrix3::Matrix3(const Matrix3& other) 
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            elements[i][j] = other.elements[i][j];
        }
    }
}

Matrix3 Matrix3::identity = Matrix3(new float[3] {1, 1, 1});



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

std::array<float, 3> Matrix3::get_row(int row)
{
    std::array<float, 3> result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = elements[row][i];
    }
    return result;
}

std::array<float, 3> Matrix3::get_col(int col)
{
	std::array<float, 3> result;
	for (int i = 0; i < 3; i++)
	{
		result[i] = elements[i][col];
	}
	return result;
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
            result.elements[i][j] = -elements[i][j];  
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

Vec3 Matrix3::operator*(const Vec3& other) const
{
	Vec3 result;
	result.x = elements[0][0] * other.x + elements[0][1] * other.y + elements[0][2] * other.z;
	result.y = elements[1][0] * other.x + elements[1][1] * other.y + elements[1][2] * other.z;
	result.z = elements[2][0] * other.x + elements[2][1] * other.y + elements[2][2] * other.z;
	return result;
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
#define EPS .001
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (fabs(elements[i][j] - other.elements[i][j]) > EPS)
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

Matrix3 Matrix3::inverse()
{
	float det = determinant();
	if (det == 0)
	{
		throw std::invalid_argument("Matrix is not invertible");
	}
	Matrix3 result;
	result.elements[0][0] = (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) / det;
	result.elements[0][1] = (elements[0][2] * elements[2][1] - elements[0][1] * elements[2][2]) / det;
	result.elements[0][2] = (elements[0][1] * elements[1][2] - elements[0][2] * elements[1][1]) / det;
	result.elements[1][0] = (elements[1][2] * elements[2][0] - elements[1][0] * elements[2][2]) / det;
	result.elements[1][1] = (elements[0][0] * elements[2][2] - elements[0][2] * elements[2][0]) / det;
	result.elements[1][2] = (elements[1][0] * elements[0][2] - elements[0][0] * elements[1][2]) / det;
	result.elements[2][0] = (elements[1][0] * elements[2][1] - elements[2][0] * elements[1][1]) / det;
	result.elements[2][1] = (elements[2][0] * elements[0][1] - elements[0][0] * elements[2][1]) / det;
	result.elements[2][2] = (elements[0][0] * elements[1][1] - elements[1][0] * elements[0][1]) / det;

	return result;
}

