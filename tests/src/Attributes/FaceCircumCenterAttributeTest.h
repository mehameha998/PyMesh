#pragma once

#include <string>

#include <Misc/Environment.h>

class FaceCircumCenterAttributeTest : public ::testing::Test {
    protected:
        typedef Mesh::Ptr MeshPtr;

        virtual void SetUp() {
            std::string proj_root =
                Environment::get_required("PYMESH_PATH");
            m_data_dir = proj_root + "/tests/data/";
        }

        MeshPtr load_mesh(const std::string& filename) {
            std::string mesh_file = m_data_dir + filename;
            return MeshPtr(
                    MeshFactory()
                    .load_file(mesh_file)
                    .with_attribute("face_circumcenter")
                    .create());
        }

        void assert_equal_dist_to_vertices(
                const VectorF& center,
                const VectorF& p1,
                const VectorF& p2,
                const VectorF& p3) {
            Float d1 = (center - p1).norm();
            Float d2 = (center - p2).norm();
            Float d3 = (center - p3).norm();
            ASSERT_FLOAT_EQ(d1, d2);
            ASSERT_FLOAT_EQ(d1, d3);
        }

    protected:
        std::string m_data_dir;
};

TEST_F(FaceCircumCenterAttributeTest, 2D) {
    MeshPtr square = load_mesh("square_2D.obj");
    ASSERT_EQ(3, square->get_vertex_per_face());
    ASSERT_TRUE(square->has_attribute("face_circumcenter"));
    const VectorF& circumcenters = square->get_attribute("face_circumcenter");

    const size_t dim = square->get_dim();
    const size_t num_faces = square->get_num_faces();
    for (size_t i=0; i<num_faces; i++) {
        VectorI face = square->get_face(i);
        VectorF center = circumcenters.segment(i*dim, dim);
        assert_equal_dist_to_vertices(center,
                square->get_vertex(face[0]),
                square->get_vertex(face[1]),
                square->get_vertex(face[2]));
    }
}

TEST_F(FaceCircumCenterAttributeTest, 3D) {
    MeshPtr cube = load_mesh("cube.msh");
    ASSERT_EQ(3, cube->get_vertex_per_face());
    ASSERT_TRUE(cube->has_attribute("face_circumcenter"));
    const VectorF& circumcenters = cube->get_attribute("face_circumcenter");

    const size_t dim = cube->get_dim();
    const size_t num_faces = cube->get_num_faces();
    for (size_t i=0; i<num_faces; i++) {
        VectorI face = cube->get_face(i);
        VectorF center = circumcenters.segment(i*dim, dim);
        assert_equal_dist_to_vertices(center,
                cube->get_vertex(face[0]),
                cube->get_vertex(face[1]),
                cube->get_vertex(face[2]));
    }
}

