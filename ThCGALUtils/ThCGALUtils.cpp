#include "pch.h"
#include "ThCGALUtils.h"
#include "ThCGALSurface_mesh.h"
#include "ThCGALShape_regularization.h"

THCGALAPI void 
ThCGALMeshOBBFromSTLMesh(double* vertices, int vCount, double* result)
{
    ThCGAL::ThCGALSurface_mesh mesh;
    if (mesh.CreateFromSTLMesh(vertices, vCount))
    {
        mesh.OBB(result);
    }
}

THCGALAPI void 
ThCGALMeshOBBFromFile(const char* path, double* result)
{
    ThCGAL::ThCGALSurface_mesh mesh;
    mesh.LoadFromFile(path);
    mesh.OBB(result);
}

THCGALAPI void 
ThCGALUniqueSegments(double* segments, int segCount, double* result, int* count)
{
    ThCGAL::ThCGALShape_regularization worker;
}
