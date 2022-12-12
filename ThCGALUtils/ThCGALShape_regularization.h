#pragma once

namespace ThCGAL {
    class ThCGALShape_regularization
    {
    public:
        ThCGALShape_regularization();
        ~ThCGALShape_regularization();
    public:
        void UniqueSegments(double* buffer, int count, double* result, int* rCount);
    private:
        class ThCGALShape_regularization_impl;
        std::unique_ptr<ThCGALShape_regularization_impl> PIMPL;
    };
}
