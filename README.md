# EE4730_Project
## Group Project for EE4730 - 3D Modeling.

The purpose of this application is to capture input from monocular source, perform pose estimation, and then apply the pose to a skeleton for animation. The pre-rendering portions will be written in C++, while the rendering will be handled in C#.

## Pose Estimation: [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openposehere)
This project will use OpenPose, an open sourced library, for pose estimation purposes. OpenPose also has webcam integration built-in, which should be sufficient for our purposes.

## Skeleton/Animation Retargeting
Yet to be determined. Code library is needed to be found that fits the parameters of the project.

## Application Interface: [Unity](https://unity.com/)
The Unity game engine will be used for the rendering portion of the project. This will be accomplished by writing C++ DLL files and importing them as Unity PlugIns.
