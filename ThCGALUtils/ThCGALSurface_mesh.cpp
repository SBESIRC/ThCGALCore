#include "pch.h"
#include "ThCGALSurface_mesh.h"

namespace ThCGAL {

    ThCGALSurface_mesh::ThCGALSurface_mesh()
    {
        //
    }

    ThCGALSurface_mesh::~ThCGALSurface_mesh()
    {
        //
    }

    void ThCGALSurface_mesh::OBB(double* result)
    {
        std::array<Point, 8> obb_points;
        CGAL::oriented_bounding_box(sm, obb_points, CGAL::parameters::use_convex_hull(true));
        for (int i = 0; i < 8; i++)
        {
            result[3 * i] = obb_points[i].x();
            result[3 * i + 1] = obb_points[i].y();
            result[3 * i + 2] = obb_points[i].z();
        }
    }

    bool ThCGALSurface_mesh::LoadFromFile(const std::string& path)
    {
        PMP::IO::read_polygon_mesh(path, sm);

#ifdef _DEBUG
        // expensive validity check
        // used in debug configurations only
        return sm.is_valid();
#endif // DEBUG
    }

    bool ThCGALSurface_mesh::Create(double* vertices, int vCount, int* face_indexes, int fCount)
    {
        std::vector<CGAL::SM_Vertex_index> indexes;
        for (int i = 0; i < vCount; i++)
        {
            indexes.push_back(sm.add_vertex(Point(vertices[3 * i], vertices[3 * i + 1], vertices[3 * i + 2])));
        }
        for (int i = 0; i < fCount; i++)
        {
            // triangle mesh
            sm.add_face(indexes[face_indexes[3 * i]], indexes[face_indexes[3 * i + 1]], indexes[face_indexes[3 * i + 2]]);
        }

#ifdef _DEBUG
        // expensive validity check
        // used in debug configurations only
        return sm.is_valid();
#endif // DEBUG
    }
}
