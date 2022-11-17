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
    THCGALAPI void ThCGALMeshOBBFromData(double* vertices, int vCount, int* face_index, int fCount, double* result);


#ifdef __cplusplus
}
#endif