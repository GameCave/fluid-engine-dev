// Copyright (c) 2016 Doyub Kim

#include <manual_tests.h>

#include <jet/flip_solver2.h>
#include <jet/grid_point_generator2.h>
#include <jet/grid_fractional_single_phase_pressure_solver2.h>
#include <jet/level_set_utils.h>
#include <jet/implicit_surface_set2.h>
#include <jet/rigid_body_collider2.h>
#include <jet/sphere2.h>
#include <jet/surface_to_implicit2.h>

using namespace jet;

JET_TESTS(FlipSolver2);

JET_BEGIN_TEST_F(FlipSolver2, Empty) {
    FlipSolver2 solver;

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 1; frame.advance()) {
        solver.update(frame);
    }
}
JET_END_TEST_F

JET_BEGIN_TEST_F(FlipSolver2, SteadyState) {
    FlipSolver2 solver;

    GridSystemData2Ptr grid = solver.gridSystemData();
    double dx = 1.0 / 32.0;
    grid->resize(Size2(32, 32), Vector2D(dx, dx), Vector2D());

    GridPointGenerator2 pointsGen;
    Array1<Vector2D> points;
    pointsGen.generate(
        BoundingBox2D(Vector2D(), Vector2D(1.0, 0.5)), 0.5 * dx, &points);

    auto particles = solver.particleSystemData();
    particles->addParticles(points);

    saveParticleDataXy(particles, 0);

    auto sdf = solver.signedDistanceField();
    saveData(sdf->constDataAccessor(), "sdf_#grid2,0000.npy");

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 120; frame.advance()) {
        solver.update(frame);

        saveParticleDataXy(particles, frame.index);

        char filename[256];
        snprintf(
            filename,
            sizeof(filename),
            "sdf_#grid2,%04d.npy",
            frame.index);
        saveData(sdf->constDataAccessor(), filename);
    }

    Array2<double> dataU(32, 32);
    Array2<double> dataV(32, 32);
    auto velocity = grid->velocity();

    dataU.forEachIndex([&](size_t i, size_t j) {
        Vector2D vel = velocity->valueAtCellCenter(i, j);
        dataU(i, j) = vel.x;
        dataV(i, j) = vel.y;
    });

    saveData(dataU.constAccessor(), "data_#grid2,x.npy");
    saveData(dataV.constAccessor(), "data_#grid2,y.npy");
}
JET_END_TEST_F

JET_BEGIN_TEST_F(FlipSolver2, DamBreaking) {
    FlipSolver2 solver;

    GridSystemData2Ptr grid = solver.gridSystemData();
    double dx = 1.0 / 64.0;
    grid->resize(Size2(64, 64), Vector2D(dx, dx), Vector2D());

    GridPointGenerator2 pointsGen;
    Array1<Vector2D> points;
    pointsGen.generate(
        BoundingBox2D(Vector2D(), Vector2D(0.2, 0.6)), 0.5 * dx, &points);

    auto particles = solver.particleSystemData();
    particles->addParticles(points);

    saveParticleDataXy(particles, 0);

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 240; frame.advance()) {
        solver.update(frame);

        saveParticleDataXy(particles, frame.index);
    }

    Array2<double> dataU(64, 64);
    Array2<double> dataV(64, 64);
    auto velocity = grid->velocity();

    dataU.forEachIndex([&](size_t i, size_t j) {
        Vector2D vel = velocity->valueAtCellCenter(i, j);
        dataU(i, j) = vel.x;
        dataV(i, j) = vel.y;
    });

    saveData(dataU.constAccessor(), "data_#grid2,x.npy");
    saveData(dataV.constAccessor(), "data_#grid2,y.npy");
    saveData(
        solver.signedDistanceField()->constDataAccessor(),
        "sdf_#grid2.npy");
}
JET_END_TEST_F

JET_BEGIN_TEST_F(FlipSolver2, DamBreakingWithCollider) {
    FlipSolver2 solver;

    // Collider setting
    auto sphere = std::make_shared<Sphere2>(
        Vector2D(0.5, 0.0), 0.15);
    auto surface = std::make_shared<SurfaceToImplicit2>(sphere);
    auto collider = std::make_shared<RigidBodyCollider2>(surface);
    solver.setCollider(collider);

    GridSystemData2Ptr grid = solver.gridSystemData();
    double dx = 1.0 / 100.0;
    grid->resize(Size2(100, 100), Vector2D(dx, dx), Vector2D());

    GridPointGenerator2 pointsGen;
    Array1<Vector2D> points;
    pointsGen.generate(
        BoundingBox2D(Vector2D(), Vector2D(0.2, 0.8)), 0.5 * dx, &points);

    auto particles = solver.particleSystemData();
    particles->addParticles(points);

    saveParticleDataXy(particles, 0);

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 240; frame.advance()) {
        solver.update(frame);

        saveParticleDataXy(particles, frame.index);
    }
}
JET_END_TEST_F
