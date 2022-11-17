#include "pch.h"
#include "ThCGALUtils.h"
#include "ThCGALSurface_mesh.h"

THCGALAPI void 
ThCGALMeshOBBFromData(double* vertices, int vCount, int* face_indexes, int fCount, double* result)
{
    ThCGAL::ThCGALSurface_mesh mesh;
    mesh.Create(vertices, vCount, face_indexes, fCount);
    mesh.OBB(result);
}

THCGALAPI void 
ThCGALMeshOBBFromFile(const char* path, double* result)
{
    ThCGAL::ThCGALSurface_mesh mesh;
    mesh.LoadFromFile(std::string(path));
    mesh.OBB(result);
}
