#include "Octree.h"

bool Octree::insert(RigidBody* _rigidbody)
{
    std::array<Vec3, 8> points;
    _rigidbody->getPoints(points);

    if (!boundary.intersects(points))
        return false;

    if (contentCount < OCTREE_SIZE && !nwTop)
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
    queryRecursive(rigidbodyPoints, _rigidbody, _outRigidBodies);
}

void Octree::draw()
{
    ofSetColor(ofColor::lawnGreen, 10);
    ofBoxPrimitive box;
    box.setPosition((glm::vec3)boundary.center);
    box.setDepth(boundary.h_length * 2);
    box.setHeight(boundary.h_height * 2);
    box.setWidth(boundary.h_width * 2);
    box.setResolution(1);
    box.drawFaces();

    if (swBot)
    {
        ofSetColor(ofColor::lawnGreen, 20);
        Vec3 front  { boundary.h_length, 0, 0 };
        Vec3 up     { 0, boundary.h_height, 0 };
        Vec3 right  { 0, 0, boundary.h_width };
        ofDrawLine( (glm::vec3)(boundary.center + front ), (glm::vec3)(boundary.center - front  ));
        ofDrawLine( (glm::vec3)(boundary.center + up    ), (glm::vec3)(boundary.center - up     ));
        ofDrawLine( (glm::vec3)(boundary.center + right ), (glm::vec3)(boundary.center - right  ));
        nwTop->draw();
        neTop->draw();
        swTop->draw();
        seTop->draw();
        nwBot->draw();
        neBot->draw();
        swBot->draw();
        seBot->draw();
    }
}

void Octree::queryRecursive(const std::array<Vec3, 8>& _rigidbodyPoints, RigidBody* _rigidbody, std::vector<RigidBody*>& _outRigidBodies)
{
    if (!boundary.intersects(_rigidbodyPoints))
        return;

    //adds content of this level inside the results list
    for (size_t i = 0; i < contentCount; i++)
    {
        RigidBody* rb = content[i];

        //Checks autoCollision
        if (rb == _rigidbody)
            continue;

        //Checks if contained rigidBody is not already in the results list
        bool found = false;
        for (size_t i = 0; i < _outRigidBodies.size(); i++)
        {
            if (_outRigidBodies[i] == rb)
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
        nwTop->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        neTop->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        swTop->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        seTop->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        nwBot->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        neBot->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        swBot->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
        seBot->queryRecursive(_rigidbodyPoints, _rigidbody, _outRigidBodies);
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


    nwTop = std::make_unique<Octree>(AABB{ x + l/2.f, y + h/2.f, z - w/2.f,    l, h, w });
    neTop = std::make_unique<Octree>(AABB{ x + l/2.f, y + h/2.f, z + w/2.f,    l, h, w });
    swTop = std::make_unique<Octree>(AABB{ x - l/2.f, y + h/2.f, z - w/2.f,    l, h, w });
    seTop = std::make_unique<Octree>(AABB{ x - l/2.f, y + h/2.f, z + w/2.f,    l, h, w });
    nwBot = std::make_unique<Octree>(AABB{ x + l/2.f, y - h/2.f, z - w/2.f,    l, h, w });
    neBot = std::make_unique<Octree>(AABB{ x + l/2.f, y - h/2.f, z + w/2.f,    l, h, w });
    swBot = std::make_unique<Octree>(AABB{ x - l/2.f, y - h/2.f, z - w/2.f,    l, h, w });
    seBot = std::make_unique<Octree>(AABB{ x - l/2.f, y - h/2.f, z + w/2.f,    l, h, w });

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