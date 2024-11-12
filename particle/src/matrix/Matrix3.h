#pragma once
#include <array>

#include "../primitives/vec3.h"

class Matrix3 {
private:
    float elements[3][3];

public:
    Matrix3(); 
    Matrix3(float elements[3][3]); 
    Matrix3(float diagonal[3]);
    Matrix3(const Matrix3& other);
    static Matrix3 identity;

    void print_matrix();
    float get(int row, int col);
    std::array<float, 3> get_row(int row);
    std::array<float, 3> get_col(int col);
    void set(int row, int col, float value);

    Matrix3 operator+(const Matrix3& other); 
    Matrix3& operator+=(const Matrix3& other);

    Matrix3 operator-(const Matrix3& other); 
    Matrix3 operator-();
    Matrix3& operator-=(const Matrix3& other);

    Matrix3 operator*(const Matrix3& other); 
    Matrix3& operator*=(const Matrix3& other);
    Vec3 operator*(const Vec3& other) const;

    Matrix3 operator*(float scalar); 
    Matrix3& operator*=(float scalar);

    bool operator==(const Matrix3& other);

    Matrix3 transpose(); 
    float determinant();
};

