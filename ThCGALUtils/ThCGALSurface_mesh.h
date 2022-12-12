#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#include <CGAL/optimal_bounding_box.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/measure.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Optimal_bounding_box/Oriented_bounding_box_traits_3.h>

namespace PMP = CGAL::Polygon_mesh_processing;

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef K::Point_3                                             Point;
typedef CGAL::Surface_mesh<Point>                              Surface_mesh;

namespace ThCGAL {
    class ThCGALSurface_mesh
    {
    public:
        ThCGALSurface_mesh();
        ~ThCGALSurface_mesh();

    public:
        void OBB(double* result);
        bool LoadFromFile(const std::string& path);
        bool Create(double* vertices, int fCount);

    private:
        Surface_mesh sm;
    };
}

