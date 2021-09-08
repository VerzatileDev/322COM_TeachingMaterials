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
 
## Soft Shadows

It is advanced level and optional. 
This week follows on from the last session. This week involves distributed ray tracing to create soft shadows.

Detailed instruction of implementation can be found in _"Workshop 3B Instructions.pdf"_

![SphereRayTracing picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%204/Readme%20Pictures/Shadows.jpg)

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
#include "GlobalVars.h"
class AxisAlignedBoundingBox
{
public:
	glm::vec3 pMin;
	glm::vec3 pMax;

	AxisAlignedBoundingBox();
	AxisAlignedBoundingBox(glm::vec3 min, glm::vec3 max);
	bool CheckForIntersection(glm::vec3 origin, glm::vec3 rayDir); //check intersection with bouding box
};
```

Implementation of intersection check function
```C++
bool AxisAlignedBoundingBox::CheckForIntersection(glm::vec3 origin, glm::vec3 rayDir)
{
	float epsilon = 0.0001f;

	float tmin = (pMin.x - origin.x) / (rayDir.x+ epsilon);
	float tmax = (pMax.x - origin.x) / (rayDir.x + epsilon);

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (pMin.y - origin.y) / (rayDir.y + epsilon);
	float tymax = (pMax.y - origin.y) / (rayDir.y + epsilon);

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (pMin.z - origin.z) / (rayDir.z + epsilon);
	float tzmax = (pMax.z - origin.z) / (rayDir.z + epsilon);

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	return true;
}
```

The example of usage in ray tracing implementation
```C++
    //Check Intersection of Objects
	for (int j = 0; j < listOfObjects.size(); j++) {
	//bounding box intersection check
	if (listOfObjects[j]->boundingBox.CheckForIntersection(origin, thisPixelRayDir)) {
		
		//here is your ray tracing intersection check

	}
```

## Recursive Reflection

It is advanced level and optional. 
This workshop involves implementing reflections as illustrated below:

![Reflection picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%204/Readme%20Pictures/Reflection.jpg)

Detailed instruction of implementation can be found in _"Workshop 5 Instructions.pdf"_