# EE4730 (3D Modeling) Group Project 
### Members: Sean Brown, Austin Copper, Colburn Randel, & Rahsaan Nahar

The purpose of this application is to capture input from monocular source, perform pose estimation, and then apply the pose to a skeleton for animation. The pre-rendering portions will be written in C++, while the rendering will be handled in C#.

## Pose Estimation: [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openposehere)
This project will use OpenPose, an open sourced library, for pose estimation purposes. OpenPose also has webcam integration built-in, which should be sufficient for our purposes.
The published paper can found [here](https://arxiv.org/pdf/1812.08008.pdf).

## Skeleton/Animation Retargeting
Yet to be determined. Code library is needed to be found that fits the parameters of the project.

## Application Interface: [Unity](https://unity.com/)
The Unity game engine will be used for the rendering portion of the project. This will be accomplished by writing C++ DLL files and importing them as Unity PlugIns.

# Installation

## Installing OpenPose Library
You will need to install the [OpenPose Repository](https://github.com/CMU-Perceptual-Computing-Lab/openpose) (following the steps below) to be able to include the library in the project. It could not be included with the rest of the project as it is not possible to nest .git repositories. If there is any confusion in these steps, please look the [OpenPose's documentation](https://github.com/CMU-Perceptual-Computing-Lab/openpose/tree/master/doc) for a more thorough explanation.

### OpenPose Prerequisites
You will need to install the following before being able to execute OpenPose.
- Visual Studio 2017 Community or Enterprise edition
- [CMake GUI](https://cmake.org/download/) for building OpenPose and possibly some of its dependecies.
- [Nvidia Cuda 10.0](https://developer.nvidia.com/cuda-downloads)
- [cuDNN 7.5](https://developer.nvidia.com/rdp/cudnn-archive) 
  - In order to manually install it, just unzip it and copy (merge) the contents on the CUDA folder, usually C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.0 in Windows


### Installing OpenPose
- Download/Clone the OpenPose Repo
  - If downloaded - extract the file "openpose-master" to wherever you prefer
- If you have not done so already, install the prerequisites following the instructions listed in the above section.
- Open CMake GUI
  - Select /openpose-master as the source
  - Select /openpose-master/build for destination
  - Click on configure towards the bottom left
    - For the generator select Visual Studio 15 2017
    - For the optional platform select x64 or Win64 (whichever appears).
  - Click **Finish**
  - You should see CMake configure the file and download Caffe and OpenCV. You will get errors if it fails to do so - wait and try again after a few minutes... Or an hour in my case... Their servers are powered by hamsters apparently.
  - Afterward configuration has been successfully completed, click **Generate**.
  - It should generate a Visual Studio 2017 project (you can click on Open Project to save time)
- Open the Visual Studio 2017 Project
  - Change the configuration from Debug to Release
  - Build the project (the green triangle or press f5)
    - if successful, this should generate the .lib file needed for incorporating OpenPose into our project solution. 
  
 ### Incorporating OpenPose into the project solution
  - Open the project solution in Visual Studio (2017 or 2019 - shouldn't matter)
  - In the solution explorer, right click on the project "EE4730_Project" and open properties.
  - Go to C/C++ -> General -> Additional Include Directories. Add your local file path location of the openpose-master\include folder to it.
  - Go to Linker -> Input -> Additional Dependencies. Add your local file path location of the openposed.lib file to it.
    - file can be found in: openpose-master\build\src\openpose\Debug\

Now you should be able to use OpenPose in the project. If the #includes are still producing errors, double check your file locations and make sure they are correct. 
