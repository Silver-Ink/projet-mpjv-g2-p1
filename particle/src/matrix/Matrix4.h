#pragma once

#include <cmath>
#include <cstdio>
#include <iostream>

class Matrix4 {
private:
    float elements[4][4];

public:
    Matrix4();
    Matrix4(float elements[4][4]);

    void print_matrix();
    float get(int row, int col);
    void set(int row, int col, float value);

    Matrix4 operator+(const Matrix4& other);
    Matrix4& operator+=(const Matrix4& other);

    Matrix4 operator-(const Matrix4& other);
    Matrix4 operator-();
    Matrix4& operator-=(const Matrix4& other);

    Matrix4 operator*(const Matrix4& other);
    Matrix4& operator*=(const Matrix4& other);

    Matrix4 operator*(float scalar);
    Matrix4& operator*=(float scalar);

    bool operator==(const Matrix4& other);

    Matrix4 transpose();
    float determinant();
    Matrix4 inverse();
};
