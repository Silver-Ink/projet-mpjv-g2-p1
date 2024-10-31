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

	Vec3 b{1.f, 2.f, 3.f};
	ASSERT(b == Vec3{1.f COMMA 2.f COMMA 3.f})
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

	Vec3 c{3.f, 4.f, 0};
	ASSERT(c.sqLength() == 25.f)
	ASSERT(c.length()   == 5.f)

	Vec3 d{-20.f, 0, 0};
	Vec3 e{-1.f, 0, 0};
	ASSERT(d.getNormalized() == e)
	d.normalize();
	ASSERT(d == e)

	Vec3 h{1.f, 0, 0};
	Vec3 i{0, 0, 1.f};
	ASSERT(s_floatComp( h.dot(i), 0.f))

	Vec3 j{0, -1.f, 0};
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
	Matrix3 b(elements1);
	Matrix3 identity(elements_id);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ASSERT(a.get(i,j) == 0.f)
		}
	}
	
	ASSERT(a + b == b)
	ASSERT(b + b == b * 2.f)
	ASSERT(a - b == -b)
	ASSERT(b - b == a)
	ASSERT(b * 0 == a)
	ASSERT(b * 1 == b)
	ASSERT(b * -1 == -b)

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
	Matrix3 c(elements2);
	c.print_matrix();
	ASSERT(s_floatComp(c.determinant(), 49.f))



}

void TestClass::s_testMatrix4()
{
	INIT_TEST();

	
}
