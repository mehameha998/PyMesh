/* This file is part of PyMesh. Copyright (c) 2016 by Qingnan Zhou */
#pragma once
#ifdef WITH_CGAL

#include "../TriangulationTest.h"

class ConstrainedDelaunayTest : public TriangulationTest {
};

TEST_F(ConstrainedDelaunayTest, simple) {
    MatrixFr points(3, 2);
    points << 0.0, 0.0,
              1.0, 0.0,
              0.0, 1.0;

    Triangulation::Ptr t = Triangulation::create("cgal_constrained_delaunay");
    t->set_points(points);
    t->run();

    const MatrixFr vertices = t->get_vertices();
    const MatrixIr faces = t->get_faces();
    ASSERT_EQ(1, faces.rows());
    ASSERT_TRUE(
            (faces(0, 0) == 0 && faces(0, 1) == 1 && faces(0, 2) == 2) ||
            (faces(0, 0) == 1 && faces(0, 1) == 2 && faces(0, 2) == 0) ||
            (faces(0, 0) == 2 && faces(0, 1) == 0 && faces(0, 2) == 1));
    assert_valid_triangulation(vertices, faces);
}

TEST_F(ConstrainedDelaunayTest, simple2) {
    MatrixFr points(4, 2);
    points << 0.0, 0.0,
              0.5, 0.0,
              1.0, 0.0,
              0.0, 1.0;

    Triangulation::Ptr t = Triangulation::create("cgal_constrained_delaunay");
    t->set_points(points);
    t->run();
    const MatrixFr vertices = t->get_vertices();
    const MatrixIr faces = t->get_faces();
    ASSERT_EQ(2, faces.rows());
    assert_valid_triangulation(vertices, faces);
}

TEST_F(ConstrainedDelaunayTest, simple3) {
    MatrixFr points(4, 2);
    points << 0.0, 1.0,
              0.5, 0.0,
              1.0, 0.0,
              0.0, 0.0;

    Triangulation::Ptr t = Triangulation::create("cgal_constrained_delaunay");
    t->set_points(points);
    t->run();
    const MatrixFr vertices = t->get_vertices();
    const MatrixIr faces = t->get_faces();
    ASSERT_EQ(2, faces.rows());
    assert_valid_triangulation(vertices, faces);
}

TEST_F(ConstrainedDelaunayTest, degenerate) {
    MatrixFr points(3, 2);
    points << 0.0, 0.0,
              0.5, 0.0,
              1.0, 0.0;

    Triangulation::Ptr t = Triangulation::create("cgal_constrained_delaunay");
    t->set_points(points);
    t->run();
    const MatrixIr faces = t->get_faces();
    ASSERT_EQ(0, faces.rows());
}

#endif
