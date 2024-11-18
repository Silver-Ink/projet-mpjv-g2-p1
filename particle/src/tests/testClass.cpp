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
	Quaternion g2 = g1 - g1;
	ASSERT(!s_floatComp(g2.a, 0.));
	ASSERT(s_floatComp(g2.b, 0.));
	ASSERT(s_floatComp(g2.c, 0.));
	ASSERT(s_floatComp(g2.d, 0.));

	Quaternion i1{ 0., 0., 0., 0. };
	ASSERT(i1 == -i1);

	Quaternion i2{ 1., 2., 3., 4. };
	Quaternion i3 = -i2;
	ASSERT(s_floatComp(-i2.a, i3.a));
	ASSERT(s_floatComp(-i2.b, i3.b));
	ASSERT(s_floatComp(-i2.c, i3.c));
	ASSERT(s_floatComp(-i2.d, i3.d));

	//testing quaternion multiplication specifically
	Quaternion h1{ 34., 58.2, 41., 1. };
	ASSERT(h1 == h1 * Quaternion::IDENTITY);

	Quaternion quatMult_minusReal{ -1., 0., 0., 0. };
	Quaternion quatMult_i{ 0., 1., 0., 0. }, quatMult_minusI{ 0., -1., 0., 0. };
	Quaternion quatMult_j{ 0., 0., 1., 0. }, quatMult_minusJ{ 0., 0., -1., 0. };
	Quaternion quatMult_k{ 0., 0., 0., 1. }, quatMult_minusK{ 0., 0., 0., -1. };

	ASSERT(quatMult_i * quatMult_i == quatMult_minusReal);
	ASSERT(quatMult_j * quatMult_j == quatMult_minusReal);
	ASSERT(quatMult_k * quatMult_k == quatMult_minusReal);
	ASSERT(quatMult_i * quatMult_j * quatMult_k == quatMult_minusReal);

	ASSERT(quatMult_i * quatMult_j == quatMult_k);
	ASSERT(quatMult_j * quatMult_i == quatMult_minusK);

	ASSERT(quatMult_j * quatMult_k == quatMult_i);
	ASSERT(quatMult_k * quatMult_j == quatMult_minusI);

	ASSERT(quatMult_k * quatMult_i == quatMult_j);
	ASSERT(quatMult_i * quatMult_k == quatMult_minusJ);

	//testing remaining methods
	Quaternion j1{ 100., 0., 0., 0. };
	ASSERT(j1 == j1.getConjugate());

	Quaternion j2{ 1., 2., 3., 4. };
	Quaternion j3 = j2.getConjugate();
	ASSERT((j2.a == j3.a) && (j2.b == -j3.b) && (j2.c == -j3.c) && (j2.d == -j3.d));

	Quaternion k1;
	for (float i = 1.; i < 6.; i++)
	{
		k1 = { i, 0., 0., 0. };
		ASSERT(k1.getInverse() == Quaternion::IDENTITY); //inverse must also normalize
	}

	Quaternion k2{ 26., 30., 45., 7. };
	Quaternion k3 = k2 * k2.getInverse();
	k3 = k3 / k3.length();
	ASSERT(k3 == Quaternion::IDENTITY);

	//dotProduct()
	Quaternion l1{ 1., 1., 0., 0.};
	Quaternion l2{ 0., 0., 1., 1.};
	ASSERT(l1.dotProduct(l2) == 0.f);

	//getExpo()
	Quaternion m1{ 0.383, 0., 0.,  0.924 }; //135° around Z axis
	Quaternion m2{ 0.831, 0., 0.,  0.556 }; //135°/2 around Z axis
	ASSERT(m1.getExpo(.5) == m2)
	ASSERT(Quaternion::IDENTITY.getExpo(.3) == Quaternion::IDENTITY)

	Quaternion n1{ 1., 1., 1., 1. };
	ASSERT(s_floatComp(n1.length(), 2.));

	Quaternion n2{ 0., 0., -1., 0. };
	ASSERT(s_floatComp(n2.length(), 1.));

	Quaternion o1{ 1., 1., 1., 1. };
	Quaternion o2 = o1.getNormalized();
	ASSERT(s_floatComp(o2.length(), 1.));
	ASSERT((o2.a == .5) && (o2.b == .5) && (o2.c == .5) && (o2.d == .5));

	Quaternion o3{ -1., 0., 0., 0. };
	ASSERT(o3.getNormalized() == o3);

	//toMatrix3()
	Quaternion p1{ .866, 0., 0., .5 };

	float _matrix1[3][3] = {
		{.5,   -.866,	0.},
		{.866,	.5,	   -0.},
		{0.,	0.,		1.},
	};
	Matrix3 matrix1{ _matrix1 };
	Matrix3 matrix2{ p1.toMatrix3() };
	ASSERT(p1.toMatrix3() == matrix1);
	ASSERT(Quaternion::IDENTITY.toMatrix3() == Matrix3::identity);

	//rotateVector()
	Vec3 v1{1., 0., 0.};
	Vec3 v2{ .5, .866, 0 };
	Quaternion q1{ 0.866 , 0., 0., .5 }; //60° around Z axis
	ASSERT(q1.rotateVector(v1) == v2)


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
