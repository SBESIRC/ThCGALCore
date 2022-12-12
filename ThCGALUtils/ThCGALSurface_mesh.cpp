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

#ifdef _DEBUG
        Surface_mesh obb_sm;
        CGAL::make_hexahedron(obb_points[0], obb_points[1], obb_points[2], obb_points[3],
            obb_points[4], obb_points[5], obb_points[6], obb_points[7], obb_sm);
        std::ofstream("D:\\obb.off") << obb_sm;

        PMP::triangulate_faces(obb_sm);
        std::cout << "Volume: " << PMP::volume(obb_sm) << std::endl;
#endif // _DEBUG
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

    bool ThCGALSurface_mesh::Create(double* vertices, int fCount)
    {
        for (int i = 0; i < fCount; i++)
        {
            // triangle vertices
            CGAL::SM_Vertex_index v0 = sm.add_vertex(Point(vertices[9 * i], vertices[9 * i + 1], vertices[9 * i + 2]));
            CGAL::SM_Vertex_index v1 = sm.add_vertex(Point(vertices[9 * i + 3], vertices[9 * i + 4], vertices[9 * i + 5]));
            CGAL::SM_Vertex_index v2 = sm.add_vertex(Point(vertices[9 * i + 6], vertices[9 * i + 7], vertices[9 * i + 8]));

            // triangle face
            sm.add_face(v0, v1, v2);
        }

#ifdef _DEBUG
        // expensive validity check
        // used in debug configurations only
        return sm.is_valid();
#endif // DEBUG
    }
}
