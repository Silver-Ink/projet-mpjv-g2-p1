#pragma once

#include <cmath>
#include <cstdio>
#include <iostream>

class Matrix3 {
private:
    float elements[3][3];

public:
    Matrix3(); 
    Matrix3(float elements[3][3]); 


    void print_matrix();
    float get(int row, int col);
    void set(int row, int col, float value);


    Matrix3 operator+(const Matrix3& other); 
    Matrix3& operator+=(const Matrix3& other);

    Matrix3 operator-(const Matrix3& other); 
    Matrix3 operator-();
    Matrix3& operator-=(const Matrix3& other);

    Matrix3 operator*(const Matrix3& other); 
    Matrix3& operator*=(const Matrix3& other);

    Matrix3 operator*(float scalar); 
    Matrix3& operator*=(float scalar);

	bool operator==(const Matrix3& other);

	
    Matrix3 transpose(); 
    float determinant();
};
