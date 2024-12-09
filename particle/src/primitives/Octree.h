#pragma once
#include "../rigidBody/RigidBody.h"

#define OCTREE_SIZE 2

struct AABB {
public:
    AABB() = default;
    AABB(float _x, float _y, float _z, float _length, float _height, float _width) : center(_x, _y, _z), h_length(_length / 2.f), h_height(_height / 2.f), h_width(_width / 2.f) {}

    bool contains(Vec3 _point)
    {
        return  (_point.x >= center.x - h_length && _point.x <= center.x + h_length) &&
            (_point.y >= center.y - h_height && _point.y <= center.y + h_height) &&
            (_point.z >= center.z - h_width && _point.z <= center.z + h_width);
    }

    bool intersects(const std::array<Vec3, 8>& _boxOfPoints)
    {
        for (Vec3 p : _boxOfPoints)
            if (contains(p))
                return true;
        return false;
    }
public:
    Vec3 center;
    float h_length;
    float h_height;
    float h_width;
};

class Octree
{
public:
    Octree() = default;
    Octree(const AABB& area) : boundary(area) {}

    bool insert(RigidBody* _rigidbody);
    void query(RigidBody* _rigidbody, std::vector<RigidBody*>& _outRigidBodies);

    void draw();

private:
    void queryRecursive(const std::array<Vec3, 8>& _rigidbodyPoints, RigidBody* _rigidbody, std::vector<RigidBody*>& _outRigidBodies);
    void subdivide();

private:
    AABB boundary;
    std::unique_ptr<Octree> nwTop{};
    std::unique_ptr<Octree> neTop{};
    std::unique_ptr<Octree> swTop{};
    std::unique_ptr<Octree> seTop{};
    std::unique_ptr<Octree> nwBot{};
    std::unique_ptr<Octree> neBot{};
    std::unique_ptr<Octree> swBot{};
    std::unique_ptr<Octree> seBot{};

    size_t contentCount{ 0 };
    std::array<RigidBody*, OCTREE_SIZE> content;
};

