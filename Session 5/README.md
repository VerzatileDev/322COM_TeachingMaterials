# Session 5 - Vulkan Real-time Ray Tracing 

#### Table of Contents
1. [Installation](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Installation)
2. [Example Project](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Example-Project)
3. [Add your own models](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Acceleration-structure)
4. [Recursive Reflection](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Recursive-Reflection)

## Installation

The best way to find Vulkan SDK is to search Google with keyword "Vulkan SDK". Current it is located at
https://vulkan.lunarg.com/ . Choose your Platform. I only test it on Windows 10 and Windows 7. 
So, I will only talk about installation in Windows. However, other platform installation is similar. 

Step 1: Download Windows installer file and install it on your PC.

Step 2: Download CMake (https://cmake.org/). Install it.

Step 3: Download Vulkan Tutorials from Github https://github.com/SaschaWillems/Vulkan 

Step 4: Luach CMake and generate Visual Studio Project from Makefile
Follow on-screen instruction.

![CMake picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/CMake.JPG)

You need to configure the project first and generate the Visual Studio project. Normally, I put Visual Studio Project files into Bin folder or Build folder.

Step 5: Build tutorial project.

When you try to compile "ALL_BUILD" project, you often find something is missing.
In my case, the glm library is missing. Download latest version of glm and zip it into external folder inside Vulkan tutorial folder.

Step 6: Run Vulkan examples

Hardware requirement for Vulkan is pretty OK. I used two 10 year-old laptop run examples. Both are fine.
Both laptops have NVidia graphic cards. 
Some examples requires binary assets (models, textures, etc.) which is not stored in Github. They have to be downloaded manually.
The instructions are
https://github.com/SaschaWillems/Vulkan/blob/master/data/README.md
 
## Example Project

One of example projects is called as shadowmapping. It is a good start project for our real-time ray tracing using Vulkan.

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/shadowmapping.JPG)

To extract the project files and combine with source codes, You might follow instructions below:

1. Locate project files. 
In side the Vulkan tutorial folder, look for "bin/examples" folder.
You can find  shadowmapping.vcxproj and shadowmapping.vcxproj.filters files.

2. Copy both project files into /examples/shadowmapping folder.

3. Open project and try to compile it. You will find out one library file (base.lib) is missing.
That is because we moved project file. The relative path to base library file is no longer working.

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/projectsetting.JPG)

4. Fix the missing library. 



## Acceleration structure

Acceleration structure optimised the Ray Tracing algorithm using bounding volumes. Bounding volumes are
the foundation for both Bounding Volume Hierarchies and Uniform Grid acceleration structures and
standalone provide a significant performance increase to the ray tracing algorithm.

Detailed instruction of implementation can be found in _"Workshop 4 Instructions.pdf"_

The example of class for bounding box is shown below.
Header file

```C++
#pragma once
#include "glm/glm.hpp"
```

