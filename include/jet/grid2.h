// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_GRID2_H_
#define INCLUDE_JET_GRID2_H_

#include <jet/size2.h>
#include <jet/bounding_box2.h>
#include <functional>
#include <utility>  // just make cpplint happy..

namespace jet {

//!
//! \brief Abstract base class for 2-D cartesian grid structure.
//!
//! This class represents 2-D cartesian grid structure. This class is an
//! abstract base class and does not store any data. The class only stores the
//! shape of the grid. The grid structure is axis-aligned and can have different
//! grid spacing per axis.
//!
class Grid2 {
 public:
    //! Function type for mapping data index to actual position.
    typedef std::function<Vector2D(size_t, size_t)> DataPositionFunc;

    //! Constructs an empty grid.
    Grid2();

    //! Default destructor.
    virtual ~Grid2();

    //! Returns the grid resolution.
    const Size2& resolution() const;

    //! Returns the grid origin.
    const Vector2D& origin() const;

    //! Returns the grid spacing.
    const Vector2D& gridSpacing() const;

    //! Returns the bounding box of the grid.
    const BoundingBox2D& boundingBox() const;

    //! Returns the function that maps grid index to the cell-center position.
    DataPositionFunc cellCenterPosition() const;

    //!
    //! \brief Invokes the given function \p func for each grid cell.
    //!
    //! This function invokes the given function object \p func for each grid
    //! cell in serial manner. The input parameters are i and j indices of a
    //! grid cell. The order of execution is i-first, j-last.
    //!
    void forEachCellIndex(
        const std::function<void(size_t, size_t)>& func) const;

    //!
    //! \brief Invokes the given function \p func for each grid cell parallelly.
    //!
    //! This function invokes the given function object \p func for each grid
    //! cell in parallel manner. The input parameters are i and j indices of a
    //! grid cell. The order of execution can be arbitrary since it's
    //! multi-threaded.
    //!
    void parallelForEachCellIndex(
        const std::function<void(size_t, size_t)>& func) const;

    //! Serializes the grid instance to the output stream \p strm.
    virtual void serialize(std::ostream* strm) const = 0;

    //! Deserializes the input stream \p strm to the grid instance.
    virtual void deserialize(std::istream* strm) = 0;

    //! Returns true if resolution, grid-spacing and origin are same.
    bool hasSameShape(const Grid2& other) const;

    //! Swaps the data with other grid.
    virtual void swap(Grid2* other) = 0;

 protected:
    //! Sets the size parameters including the resolution, grid spacing, and
    //! origin.
    void setSizeParameters(
        const Size2& resolution,
        const Vector2D& gridSpacing,
        const Vector2D& origin);

    //! Swaps the size parameters with given grid \p other.
    void swapGrid(Grid2* other);

    //! Sets the size parameters with given grid \p other.
    void setGrid(const Grid2& other);

    //! Serializes the size parameters to given output stream \p strm.
    void serializeGrid(std::ostream* strm) const;

    //! Deserializes the size parameters from given input stream \p strm.
    void deserializeGrid(std::istream* strm);

 private:
    Size2 _resolution;
    Vector2D _gridSpacing = Vector2D(1, 1);
    Vector2D _origin;
    BoundingBox2D _boundingBox = BoundingBox2D(Vector2D(), Vector2D());
};

}  // namespace jet

#endif  // INCLUDE_JET_GRID2_H_
