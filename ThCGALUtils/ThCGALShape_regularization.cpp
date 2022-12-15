#include "pch.h"
#include "ThCGALKernel.h"
#include "ThCGALShape_regularization.h"
#include <CGAL/Shape_regularization/regularize_segments.h>

namespace SR = CGAL::Shape_regularization;

namespace ThCGAL {

    class ThCGALShape_regularization::ThCGALShape_regularization_impl {
    public:
        void ReadSegments(std::vector<EPICK::Segment_2>& segments, double* buffer, int count)
        {
            for (int i = 0; i < count / 4; i++)
            {
                EPICK::Segment_2 segment(
                    EPICK::Point_2(buffer[4 * i], buffer[4 * i + 1]),
                    EPICK::Point_2(buffer[4 * i + 2], buffer[4 * i + 3]));
                segments.push_back(segment);
            }
        }
        void WriteSegments(const std::vector<EPICK::Segment_2>& segments, double* buffer, int* count)
        {
            *count = (int)segments.size() * 4;
            for (int i = 0; i < *count /4; i++)
            {
                buffer[4 * i] = segments[i].source().x();
                buffer[4 * i + 1] = segments[i].source().y();
                buffer[4 * i + 2] = segments[i].target().x();
                buffer[4 * i + 3] = segments[i].target().y();
            }
        }
        void UniqueSegments(const std::vector<EPICK::Segment_2>& segments, std::vector<EPICK::Segment_2>& unique_segments)
        {
            SR::Segments::unique_segments(segments, std::back_inserter(unique_segments));
        }
    };

    ThCGALShape_regularization::ThCGALShape_regularization()
        :PIMPL(new ThCGALShape_regularization_impl()) {
    }

    ThCGALShape_regularization::~ThCGALShape_regularization() {
        //
    }

    void ThCGALShape_regularization::UniqueSegments(double* buffer, int count, double* result, int* rCount)
    {
        std::vector<EPICK::Segment_2> segments;
        std::vector<EPICK::Segment_2> unique_segments;
        PIMPL->ReadSegments(segments, buffer, count);
        PIMPL->UniqueSegments(segments, unique_segments);
        PIMPL->WriteSegments(unique_segments, result, rCount);
    }
}
