#include "testClass.h"
#include "../primitives/vec3.h"

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