//
// Created by 서영훈 on 2023/02/24.
// Copyright https://github.com/gaoxiang12/slambook2
//
#include "module2/ClassEigenMat.hpp"
#include "module3/ClassPangolinMat.hpp"

// path to trajectory file
const std::string trajectory_file_path = "/Users/hoon/CLion_project/hello_cmake/examples/trajectory.txt";

// Trajectory function declaration
void DrawTrajectory(std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>>);



int main(int argc, char **argv)
{
    // initialize EigenSTL::vector_Isometry3d, named poses
    std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>> poses;
    std::ifstream fin(trajectory_file_path); //Declare a stream variable

    // check if the trajectory file can be opened
    if (!fin)
    {
        std::cerr << "cannot find trajectory file at " << trajectory_file_path << '\n';
        exit(EXIT_FAILURE);
    }

    // Read the trajectory file
    while (!fin.eof())
    {
        /*
         * Position = {tx, ty, tz}
         * Quaternion = {qx, qy, qz, qw}
         * pretranslate : (tx, ty, tz) * (qx, qy, qz)
         */
        double time, tx, ty, tz, qx, qy, qz, qw;
        fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
        Eigen::Isometry3d Twr(Eigen::Quaterniond(qw, qx, qy, qz));
        Twr.pretranslate(Eigen::Vector3d(tx, ty, tz));
        poses.push_back(Twr);
    }

    DrawTrajectory(poses);
    return 0;
}

void DrawTrajectory(std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>> poses)
{
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //s_cam as the State of the camera
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    //create named display managed by pangolin
    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));

    while (pangolin::ShouldQuit() == false)
    {
        /*
         * 2D pixels drawn in transformation are stored in color buffer,
         * and depth information for each pixel is stored in depth buffer, which initializes this.
         */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(2);

        //Draw the three axes of each pose
        for (size_t i = 0; i < poses.size(); i++) {
            Eigen::Vector3d Ow = poses[i].translation();
            Eigen::Vector3d Xw = poses[i] * (0.1 * Eigen::Vector3d(1, 0, 0));
            Eigen::Vector3d Yw = poses[i] * (0.1 * Eigen::Vector3d(0, 1, 0));
            Eigen::Vector3d Zw = poses[i] * (0.1 * Eigen::Vector3d(0, 0, 1));

            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]);
            glVertex3d(Xw[0], Xw[1], Xw[2]);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]);
            glVertex3d(Yw[0], Yw[1], Yw[2]);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]);
            glVertex3d(Zw[0], Zw[1], Zw[2]);
            glEnd();
        }

        for (size_t i = 0; i < poses.size(); i++)
        {
            //drawing dots or lines, put them between glbegin and glend
            glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            auto p1 = poses[i], p2 = poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }

        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
}