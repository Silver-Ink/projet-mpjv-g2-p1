#include "TestClass.h"
#include "../primitives/Vec3.h"
#include "../matrix/Matrix3.h"
#include "../matrix/Matrix4.h"

#define COMMA ,

void TestClass::s_testVec3()
{
	INIT_TEST();
	Vec3 a;
	ASSERT(a.x == 0.f)
		ASSERT(a.y == 0.f)
		ASSERT(a.z == 0.f)
		ASSERT(a == a)

		Vec3 b{ 1.f, 2.f, 3.f };
	ASSERT(b == Vec3{ 1.f COMMA 2.f COMMA 3.f })
		ASSERT(b == a + b)
		a += b;
	ASSERT(a == b)

		a -= b;
	ASSERT(b == a + b)
		a = b;
	b *= 2;
	ASSERT(b == a + a)
		ASSERT(b == a * 2.f)
		ASSERT(b == 2.f * a)

		Vec3 c{ 3.f, 4.f, 0 };
	ASSERT(c.sqLength() == 25.f)
		ASSERT(c.length() == 5.f)

		Vec3 d{ -20.f, 0, 0 };
	Vec3 e{ -1.f, 0, 0 };
	ASSERT(d.getNormalized() == e)
		d.normalize();
	ASSERT(d == e)

		Vec3 h{ 1.f, 0, 0 };
	Vec3 i{ 0, 0, 1.f };
	ASSERT(s_floatComp(h.dot(i), 0.f))

		Vec3 j{ 0, -1.f, 0 };
	ASSERT(h.cross(i) == j)

		i.x += .5f;
	ASSERT(s_floatComp(h.dot(i), .5f))

}

void TestClass::s_testMatrix3()
{
	INIT_TEST();
	float elements1[3][3] = {
		{1.f, 2.f, 3.f},
		{4.f, 5.f, 6.f},
		{7.f, 8.f, 9.f}
	};
	float elements_id[3][3] = {
		{1.f, 0.f, 0.f},
		{0.f, 1.f, 0.f},
		{0.f, 0.f, 1.f}
	};

	Matrix3 a;
	Matrix3 b{ elements1 };
	Matrix3 identity{ elements_id };
	ASSERT(identity == Matrix3::identity)

		//test get and set
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ASSERT(a.get(i, j) == 0.f)
			}
		};
	a.set(1, 1, 5.f);
	ASSERT(a.get(1, 1) == 5.f)
		a.set(1, 1, 0.f);

	//test get_row and get_col
	std::array<float, 3> row = b.get_row(1);
	std::array<float, 3> col = b.get_col(1);
	std::array<float, 3> true_row{ 4.f, 5.f, 6.f };
	std::array<float, 3> true_col{ 2.f, 5.f, 8.f };

	ASSERT(row == true_row)
		ASSERT(col == true_col)

		//test operators
		ASSERT(a + b == b)
		ASSERT(b + b == b * 2.f)
		ASSERT(a - b == -b)
		ASSERT(b - b == a)
		ASSERT(b * 0 == a)
		ASSERT(b * 1 == b)
		ASSERT(b * -1 == -b)

		Matrix3 c{ b };
	c += b;
	ASSERT(c == b * 2.f)
		c -= b;
	ASSERT(c == b)
		c *= 2.f;
	ASSERT(c == b * 2.f)
		Matrix3 d{ new float[3] { 5.f, 5.f, 5.f } };
	c *= d;
	ASSERT(c == b * 10.f)

		//test transpose and determinant
		Matrix3 b_transposed = b.transpose();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ASSERT(b.get(i, j) == b_transposed.get(j, i))
		}
	}

	ASSERT(a.determinant() == 0.f)
		float elements2[3][3] = {
			{2.f, 3.f, 1.f},
			{4.f, 1.f, 6.f},
			{7.f, 5.f, 3.f}
	};
	Matrix3 e(elements2);
	e.print_matrix();
	ASSERT(s_floatComp(e.determinant(), 49.f))



}

void TestClass::s_testMatrix4()
{
	INIT_TEST();

	float elements1[4][4] = {
	{1.f, 2.f, 3.f, 4.f},
	{5.f, 6.f, 7.f, 8.f},
	{9.f, 10.f, 11.f, 12.f},
	{13.f, 14.f, 15.f, 16.f}
	};
	float elements_id[4][4] = {
	{1.f, 0.f, 0.f, 0.f},
	{0.f, 1.f, 0.f, 0.f},
	{0.f, 0.f, 1.f, 0.f},
	{0.f, 0.f, 0.f, 1.f}
	};

	Matrix4 a;
	Matrix4 b{ elements1 };
	Matrix4 identity{ elements_id };
	ASSERT(identity == Matrix4::identity)

	//test get and set
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ASSERT(a.get(i, j) == 0.f)
		}
	};
	a.set(1, 1, 5.f);
	ASSERT(a.get(1, 1) == 5.f)
	a.set(1, 1, 0.f);

	//test get_row and get_col
	std::array<float, 4> row = b.get_row(1);
	std::array<float, 4> col = b.get_col(1);
	std::array<float, 4> true_row{ 5.f, 6.f, 7.f, 8.f };
	std::array<float, 4> true_col{ 2.f, 6.f, 10.f, 14.f };

	ASSERT(row == true_row)
	ASSERT(col == true_col)

	//test operators
	ASSERT(a + b == b)
	ASSERT(b + b == b * 2.f)
	ASSERT(a - b == -b)
	ASSERT(b - b == a)
	ASSERT(b * 0 == a)
	ASSERT(b * 1 == b)
	ASSERT(b * -1 == -b)

	Matrix4 c{ b };
	c += b;
	ASSERT(c == b * 2.f)
	c -= b;
	ASSERT(c == b)
	c *= 2.f;
	ASSERT(c == b * 2.f)
	Matrix4 d{ new float[4] { 5.f, 5.f, 5.f, 5.f } };
	c *= d;
	ASSERT(c == b * 10.f)

	//test transpose and determinant
	Matrix4 b_transposed = b.transpose();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ASSERT(b.get(i, j) == b_transposed.get(j, i))
		}
	}

	ASSERT(a.determinant() == 0.f)
	float elements2[4][4] = {	
	{2.f, 3.f, 1.f, 4.f},
	{4.f, 1.f, 6.f, 2.f},
	{7.f, 5.f, 3.f, 1.f},
	{1.f, 0.f, 7.f, 5.f}
	};
	Matrix4 e(elements2);
	e.print_matrix();
	ASSERT(s_floatComp(e.determinant(), -104.f))

}
