// Copyright (c) 2016 Doyub Kim

#include <pch.h>
#include <jet/custom_vector_field2.h>

using namespace jet;

CustomVectorField2::CustomVectorField2(
    const std::function<Vector2D(const Vector2D&)>& customFunction,
    double derivativeResolution) :
    _customFunction(customFunction),
    _resolution(derivativeResolution) {
}

CustomVectorField2::CustomVectorField2(
    const std::function<Vector2D(const Vector2D&)>& customFunction,
    const std::function<double(const Vector2D&)>& customDivergenceFunction,
    double derivativeResolution) :
    _customFunction(customFunction),
    _customDivergenceFunction(customDivergenceFunction),
    _resolution(derivativeResolution) {
}

CustomVectorField2::CustomVectorField2(
    const std::function<Vector2D(const Vector2D&)>& customFunction,
    const std::function<double(const Vector2D&)>& customDivergenceFunction,
    const std::function<double(const Vector2D&)>& customCurlFunction) :
    _customFunction(customFunction),
    _customDivergenceFunction(customDivergenceFunction),
    _customCurlFunction(customCurlFunction) {
}

Vector2D CustomVectorField2::sample(const Vector2D& x) const {
    return _customFunction(x);
}

std::function<Vector2D(const Vector2D&)> CustomVectorField2::sampler() const {
    return _customFunction;
}

double CustomVectorField2::divergence(const Vector2D& x) const {
    if (_customDivergenceFunction) {
        return _customDivergenceFunction(x);
    } else {
        double left = _customFunction(x - Vector2D(0.5 * _resolution, 0.0)).x;
        double right = _customFunction(x + Vector2D(0.5 * _resolution, 0.0)).x;
        double bottom = _customFunction(x - Vector2D(0.0, 0.5 * _resolution)).y;
        double top = _customFunction(x + Vector2D(0.0, 0.5 * _resolution)).y;

        return (right - left + top - bottom) / _resolution;
    }
}

double CustomVectorField2::curl(const Vector2D& x) const {
    if (_customCurlFunction) {
        return _customCurlFunction(x);
    } else {
        double left = _customFunction(x - Vector2D(0.5 * _resolution, 0.0)).y;
        double right = _customFunction(x + Vector2D(0.5 * _resolution, 0.0)).y;
        double bottom = _customFunction(x - Vector2D(0.0, 0.5 * _resolution)).x;
        double top = _customFunction(x + Vector2D(0.0, 0.5 * _resolution)).x;

        return (top - bottom - right + left) / _resolution;
    }
}
