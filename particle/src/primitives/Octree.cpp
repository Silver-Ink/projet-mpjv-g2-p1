#include "Octree.h"

bool Octree::insert(RigidBody* _rigidbody)
{
    std::array<Vec3, 8> points;
    _rigidbody->getPoints(points);

    if (!boundary.intersects(points));
    return false;

    if (contentCount < 5 && !nwTop)
    {
        content.at(contentCount++) = _rigidbody;
        return true;
    }

    if (!nwTop)
        subdivide();

    bool r1, r2, r3, r4, r5, r6, r7, r8;
    r1 = nwTop->insert(_rigidbody);
    r2 = neTop->insert(_rigidbody);
    r3 = swTop->insert(_rigidbody);
    r4 = seTop->insert(_rigidbody);
    r5 = nwBot->insert(_rigidbody);
    r6 = neBot->insert(_rigidbody);
    r7 = swBot->insert(_rigidbody);
    r8 = seBot->insert(_rigidbody);

    return r1 || r2 || r3 || r4 || r5 || r6 || r7 || r8;
}

void Octree::query(RigidBody* _rigidbody, std::vector<RigidBody*>& _outRigidBodies)
{
    std::array<Vec3, 8> rigidbodyPoints{};
    _rigidbody->getPoints(rigidbodyPoints);
    queryReccursive(rigidbodyPoints, _rigidbody, _outRigidBodies);
}

void Octree::queryReccursive(const std::array<Vec3, 8>& _rigidbodyPoints, RigidBody* _rigidbody, std::vector<RigidBody*>& _outRigidBodies)
{
    if (!boundary.intersects(_rigidbodyPoints))
        return;

    //adds content of this level inside the results list
    for (size_t i = 0; i < contentCount; i++)
    {
        RigidBody* rb = content[i];

        //Checks if contained rigidBody is not already in the results list
        bool found = false;
        for (size_t i = 0; i < _outRigidBodies.size(); i++)
        {
            if (_outRigidBodies[i] == rb || _rigidbody == rb)
            {
                found = true;
                break;
            }
        }
        if (!found)
            _outRigidBodies.emplace_back(rb);
    }

    if (nwTop)
    {
        nwTop->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwTop->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwTop->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwTop->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwBot->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwBot->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwBot->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwBot->queryReccursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
    }
}

void Octree::subdivide()
{
    const float x = boundary.center.x;
    const float y = boundary.center.y;
    const float z = boundary.center.z;

    const float l = boundary.h_length;
    const float h = boundary.h_height;
    const float w = boundary.h_width;


    nwTop = std::make_unique<Octree>(AABB{ x + l, y + h, z - w,    l * 2.f, h * 2.f, w * 2.f });
    neTop = std::make_unique<Octree>(AABB{ x + l, y + h, z + w,    l * 2.f, h * 2.f, w * 2.f });
    swTop = std::make_unique<Octree>(AABB{ x - l, y + h, z - w,    l * 2.f, h * 2.f, w * 2.f });
    seTop = std::make_unique<Octree>(AABB{ x - l, y + h, z + w,    l * 2.f, h * 2.f, w * 2.f });
    nwBot = std::make_unique<Octree>(AABB{ x + l, y - h, z - w,    l * 2.f, h * 2.f, w * 2.f });
    neBot = std::make_unique<Octree>(AABB{ x + l, y - h, z + w,    l * 2.f, h * 2.f, w * 2.f });
    swBot = std::make_unique<Octree>(AABB{ x - l, y - h, z - w,    l * 2.f, h * 2.f, w * 2.f });
    seBot = std::make_unique<Octree>(AABB{ x - l, y - h, z + w,    l * 2.f, h * 2.f, w * 2.f });

    //for (RigidBody* rb : content)
    //{
    //    nwTop->Insert(rb);
    //    neTop->Insert(rb);
    //    swTop->Insert(rb);
    //    seTop->Insert(rb);
    //    nwBot->Insert(rb);
    //    neBot->Insert(rb);
    //    swBot->Insert(rb);
    //    seBot->Insert(rb);
    //}
}