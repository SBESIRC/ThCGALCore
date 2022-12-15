#pragma once

namespace ThCGAL {
    class ThCGALSurface_mesh
    {
    public:
        ThCGALSurface_mesh();
        ~ThCGALSurface_mesh();

    public:
        void OBB(double* result);
        bool LoadFromFile(const char* stl);
        bool CreateFromSTLMesh(double* vertices, int vCount);

    private:
        class ThCGALSurface_mesh_impl;
        std::unique_ptr<ThCGALSurface_mesh_impl> PIMPL;
    };
}

