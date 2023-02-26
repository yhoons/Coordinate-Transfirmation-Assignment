//
// Created by 서영훈 on 2023/02/23.
//

#ifndef HELLO_CMAKE_CLASSEIGENMAT_HPP
#define HELLO_CMAKE_CLASSEIGENMAT_HPP

#include "Eigen/Dense"
#include "Eigen/Geometry"
#include "Eigen/Core"
#include <iostream>
class ClassEigenMat
{
public:
    ClassEigenMat() = default;

private:
    Eigen::Matrix3d eigen_mat_;
};


#endif //HELLO_CMAKE_CLASSEIGENMAT_HPP
