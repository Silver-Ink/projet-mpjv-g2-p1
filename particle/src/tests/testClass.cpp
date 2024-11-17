#include "TestClass.h"
#include "../primitives/Vec3.h"
#include "../primitives/Quaternion.h"
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

void TestClass::s_testQuaternion()
{
	INIT_TEST();

	//testing constructors
	Quaternion a{1., 0., 0., 0.};
	ASSERT(a == Quaternion::IDENTITY);

	Quaternion b1{ 0., {50., 60., 70.} };
	ASSERT(b1 == Quaternion::IDENTITY);

	Quaternion b2{ 1.567, {10., 10., 10.} };
	ASSERT(s_floatComp(b2.b, b2.c) && s_floatComp(b2.c, b2.d));

	Quaternion c{ {1., 2., 3.} };
	ASSERT(c.a == 0.);
	ASSERT(c.b == 1.);
	ASSERT(c.c == 2.);
	ASSERT(c.d == 3.);

	//testing operators
	Quaternion d1{ 1., 2., 4., 8. };
	d1 = d1 * 4.9367;
	ASSERT(s_floatComp(d1.b, 2. * d1.a));
	ASSERT(s_floatComp(d1.c, 2. * d1.b));
	ASSERT(s_floatComp(d1.d, 2. * d1.c));

	Quaternion d2{ 1., 56.4, 78.3, 0. };
	Quaternion d3 = d2 * 1.;
	ASSERT(d2 == d3);

	Quaternion e{ 20., 35., 56.24, 1. };
	for (int i = 1; i < 6; i++)
	{
		ASSERT((e / i) == (e * (1. / i)));
	}

	Quaternion f1{ 45.7, 12.9, 0., 378. };
	Quaternion f2{ 1., 2.4, 98.01, 0. };
	Quaternion f3 = f1 + f2;
	ASSERT(s_floatComp(f3.a, f1.a + f2.a));
	ASSERT(s_floatComp(f3.b, f1.b + f2.b));
	ASSERT(s_floatComp(f3.c, f1.c + f2.c));
	ASSERT(s_floatComp(f3.d, f1.d + f2.d));

	Quaternion f4{ 1., 2., 3., 4.56 };
	ASSERT(f4 * 2. == f4 + f4);

	Quaternion f5{0., 0., 0., 0.};
	ASSERT(f4 == f4 + f5);

	Quaternion g1{ 2., 45., 1.4, 0.99 };
	Quaternion g2{ 0.,0.,0.,0. };
	/*std::cout << g1.a << "-" << g2.a << "=" << (g1 - g2).a << "\n";
	std::cout << g1.b << "-" << g2.b << "=" << (g1 - g2).b << "\n";
	std::cout << g1.c << "-" << g2.c << "=" << (g1 - g2).c << "\n";
	std::cout << g1.d << "-" << g2.d << "=" << (g1 - g2).d << "\n";
	ASSERT(g1 - g2 == g1);
	ASSERT(g1 - g1 == g2);*/
	
	Quaternion h; // TODO operator*(Quaternion& _q) (potentiellement tester i*j=k et autres)

	Quaternion i1{ 0., 0., 0., 0. };
	ASSERT(i1 == -i1);

	Quaternion i2{ 1., 2., 3., 4. };
	Quaternion i3 = -i2;
	ASSERT(s_floatComp(-i2.a, i3.a));
	ASSERT(s_floatComp(-i2.b, i3.b));
	ASSERT(s_floatComp(-i2.c, i3.c));
	ASSERT(s_floatComp(-i2.d, i3.d));

	// TODO test regular methods
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
