#pragma once

#if defined(THCGALUTILS_EXPORTS)
#   define THCGALAPI   __declspec(dllexport)
#else
#   define THCGALAPI   __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // Declare C functions here
    THCGALAPI void ThCGALMeshOBBFromFile(const char* path, double* result);
    THCGALAPI void ThCGALMeshOBBFromSTLMesh(double* vertices, int fCount, double* result);

    // Shape Regularization
    THCGALAPI void ThCGALUniqueSegments(double* segments, int segCount, double* result, int* count);

#ifdef __cplusplus
}
#endif