#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <cstdint>

typedef double VPFloat;
//typedef float VPFloat;
typedef Eigen::Matrix<VPFloat, Eigen::Dynamic, 1> VectorXVP;
typedef Eigen::Matrix<VPFloat, 2, 1> Vector2VP;
typedef Eigen::Matrix<VPFloat, 3, 1> Vector3VP;
typedef Eigen::Matrix<VPFloat, 4, 1> Vector4VP;
typedef Eigen::Matrix<VPFloat, 3, 3> Matrix3VP;
typedef Eigen::Matrix<VPFloat, 4, 4> Matrix4VP;
typedef Eigen::Quaternion<VPFloat> QuaternionVP;

namespace Common // Just to avoid conflicts
{
	typedef std::vector<VPFloat> PointSet; // Assuming 3D, so contains 3 x n points

	const uint16_t g_BGValue = 32001; // Background value for depth pixels
	const uint16_t g_InvalidValue1 = 32000;
	const uint16_t g_InvalidValue2 = 31999;
	const uint16_t g_MinInvalidValue = 31999;
}

#ifdef _OPENMP
#include <omp.h>
#include <algorithm>
#define EASEL_MAX_THREADS std::max(omp_get_max_threads(), 8)
//#define EASEL_MAX_THREADS 1
#endif
