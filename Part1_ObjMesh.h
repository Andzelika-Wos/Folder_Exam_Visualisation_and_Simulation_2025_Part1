#ifndef PART1_OBJMESH_H
#define PART1_OBJMESH_H

#include "Part1_VisualObj.h"
#include <string>

class ObjMesh : public VisualObject
{
public:
    ObjMesh(const std::string& filename);

private:
    bool readObjFile(const std::string& filename);
};

#endif // PART1_OBJMESH_H
