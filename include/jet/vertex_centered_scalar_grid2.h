// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_VERTEX_CENTERED_SCALAR_GRID2_H_
#define INCLUDE_JET_VERTEX_CENTERED_SCALAR_GRID2_H_

#include <jet/array2.h>
#include <jet/scalar_grid2.h>
#include <utility>  // just make cpplint happy..

namespace jet {

//!
//! \brief 2-D Vertex-centered scalar grid structure.
//!
//! This class represents 2-D vertex-centered scalar grid which extends
//! ScalarGrid3. As its name suggests, the class defines the data point at the
//! grid vertices (corners). Thus, A x B grid resolution will have (A+1) x (B+1)
//! data points.
//!
class VertexCenteredScalarGrid2 final : public ScalarGrid2 {
 public:
    //! Constructs zero-sized grid.
    VertexCenteredScalarGrid2();

    //! Constructs a grid with given resolution, grid spacing, origin and
    //! initial value.
    VertexCenteredScalarGrid2(
         size_t resolutionX,
         size_t resolutionY,
         double gridSpacingX = 1.0,
         double gridSpacingY = 1.0,
         double originX = 0.0,
         double originY = 0.0,
         double initialValue = 0.0);

    //! Constructs a grid with given resolution, grid spacing, origin and
    //! initial value.
    VertexCenteredScalarGrid2(
        const Size2& resolution,
        const Vector2D& gridSpacing = Vector2D(1.0, 1.0),
        const Vector2D& origin = Vector2D(),
        double initialValue = 0.0);

    //! Copy constructor.
    VertexCenteredScalarGrid2(const VertexCenteredScalarGrid2& other);

    //! Returns the actual data point size.
    Size2 dataSize() const override;

    //! Returns data position for the grid point at (0, 0).
    //! Note that this is different from origin() since origin() returns
    //! the lower corner point of the bounding box.
    Vector2D dataOrigin() const override;

    //! Returns the copy of the grid instance.
    std::shared_ptr<ScalarGrid2> clone() const override;

    //!
    //! \brief Swaps the contents with the given \p other grid.
    //!
    //! This function swaps the contents of the grid instance with the given
    //! grid object \p other only if \p other has the same type with this grid.
    //!
    void swap(Grid2* other) override;

    //! Sets the contents with the given \p other grid.
    void set(const VertexCenteredScalarGrid2& other);

    //! Sets the contents with the given \p other grid.
    VertexCenteredScalarGrid2& operator=(
        const VertexCenteredScalarGrid2& other);

    //! Returns the grid builder instance.
    static ScalarGridBuilder2Ptr builder();
};

//! A grid builder class that returns 2-D vertex-centered scalar grid.
class VertexCenteredScalarGridBuilder2 final : public ScalarGridBuilder2 {
 public:
    //! Returns a vertex-centered grid for given parameters.
    ScalarGrid2Ptr build(
        const Size2& resolution,
        const Vector2D& gridSpacing,
        const Vector2D& gridOrigin,
        double initialVal) const override;
};

}  // namespace jet

#endif  // INCLUDE_JET_VERTEX_CENTERED_SCALAR_GRID2_H_
