// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_CONSTANT_SCALAR_FIELD2_H_
#define INCLUDE_JET_CONSTANT_SCALAR_FIELD2_H_

#include <jet/scalar_field2.h>

namespace jet {

//! 2-D constant scalar field.
class ConstantScalarField2 final : public ScalarField2 {
 public:
    //! Constructs a constant scalar field with given \p value.
    explicit ConstantScalarField2(double value);

    //! Returns the sampled value at given position \p x.
    double sample(const Vector2D& x) const override;

    //! Returns the sampler function.
    std::function<double(const Vector2D&)> sampler() const override;

 private:
    double _value = 0.0;
};

}  // namespace jet

#endif  // INCLUDE_JET_CONSTANT_SCALAR_FIELD2_H_
