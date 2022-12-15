#include "pch.h"
#include "ThCGALKernel.h"
#include "ThCGALSurface_mesh.h"

#include <CGAL/Surface_mesh.h>
#include <CGAL/optimal_bounding_box.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/measure.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Optimal_bounding_box/Oriented_bounding_box_traits_3.h>

namespace PMP = CGAL::Polygon_mesh_processing;

using Surface_mesh = CGAL::Surface_mesh<EPICK::Point_3>;

namespace ThCGAL {

    class ThCGALSurface_mesh::ThCGALSurface_mesh_impl {
    public:
        void OBB(double* result)
        {
            std::array<EPICK::Point_3, 8> obb_points;
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

        bool LoadFromFile(const std::string& path)
        {
            PMP::IO::read_polygon_mesh(path, sm);

#ifdef _DEBUG
            // expensive validity check
            // used in debug configurations only
            return sm.is_valid();
#endif // DEBUG
        }

        bool Create(double* vertices, int vCount)
        {
            for (int i = 0; i < vCount / 3; i++)
            {
                // triangle vertices
                CGAL::SM_Vertex_index v0 = sm.add_vertex(EPICK::Point_3(vertices[9 * i], vertices[9 * i + 1], vertices[9 * i + 2]));
                CGAL::SM_Vertex_index v1 = sm.add_vertex(EPICK::Point_3(vertices[9 * i + 3], vertices[9 * i + 4], vertices[9 * i + 5]));
                CGAL::SM_Vertex_index v2 = sm.add_vertex(EPICK::Point_3(vertices[9 * i + 6], vertices[9 * i + 7], vertices[9 * i + 8]));

                // triangle face
                sm.add_face(v0, v1, v2);
            }

#ifdef _DEBUG
            // expensive validity check
            // used in debug configurations only
            return sm.is_valid();
#endif // DEBUG
        }

    private:
        Surface_mesh sm;
    };


    ThCGALSurface_mesh::ThCGALSurface_mesh()
        :PIMPL(new ThCGALSurface_mesh_impl()){
        //
    }

    ThCGALSurface_mesh::~ThCGALSurface_mesh()
    {
        //
    }

    void ThCGALSurface_mesh::OBB(double* result)
    {
        PIMPL->OBB(result);
    }

    bool ThCGALSurface_mesh::LoadFromFile(const char* stl)
    {
        return PIMPL->LoadFromFile(stl);
    }

    bool ThCGALSurface_mesh::CreateFromSTLMesh(double* vertices, int vCount)
    {
        return PIMPL->Create(vertices, vCount);
    }
}
