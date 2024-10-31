#include "Matrix4.h"
#include <stdexcept>

Matrix4::Matrix4() 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            elements[i][j] = 0.0f;
        }
    }
}

Matrix4::Matrix4(float elements[4][4]) 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->elements[i][j] = elements[i][j];
        }
    }
}

void Matrix4::print_matrix() 
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << elements[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

float Matrix4::get(int row, int col) 
{
    return elements[row][col];
}

void Matrix4::set(int row, int col, float value) 
{
    elements[row][col] = value;
}

Matrix4 Matrix4::operator+(const Matrix4& other) 
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.elements[i][j] = elements[i][j] + other.elements[i][j];
        }
    }
    return result;
}

Matrix4& Matrix4::operator+=(const Matrix4& other) 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            elements[i][j] += other.elements[i][j];
        }
    }
    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& other) 
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.elements[i][j] = elements[i][j] - other.elements[i][j];
        }
    }
    return result;
}

Matrix4 Matrix4::operator-()
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.elements[i][j] = -elements[i][j];  // Multiplie chaque élément par -1
        }
    }
    return result;
}

Matrix4& Matrix4::operator-=(const Matrix4& other) 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            elements[i][j] -= other.elements[i][j];
        }
    }
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& other) 
{
    Matrix4 result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result.elements[i][j] = 0;
            for (int k = 0; k < 4; ++k)
            {
                result.elements[i][j] += elements[i][k] * other.elements[k][j];
            }
        }
    }
    return result;
}

Matrix4& Matrix4::operator*=(const Matrix4& other) 
{
    Matrix4 result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result.elements[i][j] = 0;
            for (int k = 0; k < 4; ++k)
                result.elements[i][j] += elements[i][k] * other.elements[k][j];
        }
    }
    *this = result;
    return *this;
}

Matrix4 Matrix4::operator*(float scalar) 
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.elements[i][j] = elements[i][j] * scalar;
        }
    }
    return result;
}

Matrix4& Matrix4::operator*=(float scalar) 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            elements[i][j] *= scalar;
        }
    }
    return *this;
}

bool Matrix4::operator==(const Matrix4& other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (elements[i][j] != other.elements[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

Matrix4 Matrix4::transpose() 
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.elements[i][j] = elements[j][i];
        }
    }
    return result;
}

float Matrix4::determinant() 
{
    return
        elements[0][0] * (
            elements[1][1] * (elements[2][2] * elements[3][3] - elements[2][3] * elements[3][2]) -
            elements[1][2] * (elements[2][1] * elements[3][3] - elements[2][3] * elements[3][1]) +
            elements[1][3] * (elements[2][1] * elements[3][2] - elements[2][2] * elements[3][1])
            ) -
        elements[0][1] * (
            elements[1][0] * (elements[2][2] * elements[3][3] - elements[2][3] * elements[3][2]) -
            elements[1][2] * (elements[2][0] * elements[3][3] - elements[2][3] * elements[3][0]) +
            elements[1][3] * (elements[2][0] * elements[3][2] - elements[2][2] * elements[3][0])
            ) +
        elements[0][2] * (
            elements[1][0] * (elements[2][1] * elements[3][3] - elements[2][3] * elements[3][1]) -
            elements[1][1] * (elements[2][0] * elements[3][3] - elements[2][3] * elements[3][0]) +
            elements[1][3] * (elements[2][0] * elements[3][1] - elements[2][1] * elements[3][0])
            ) -
        elements[0][3] * (
            elements[1][0] * (elements[2][1] * elements[3][2] - elements[2][2] * elements[3][1]) -
            elements[1][1] * (elements[2][0] * elements[3][2] - elements[2][2] * elements[3][0]) +
            elements[1][2] * (elements[2][0] * elements[3][1] - elements[2][1] * elements[3][0])
            );
}