# Session 4 - Shadows, Acceleration structure and reflection

#### Table of Contents
1. [Hard Shadows](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%204#Hard-Shadows)
2. [Soft Shadows](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%204#Soft-Shadows)
3. [Acceleration structure](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%204#Acceleration-structure)


## Hard Shadows

This week follows on from the Ray Tracing algorithm you developed in Week 3. You need to
have completed at least workshop 2A to add shadows. This week involves standard ray
tracing to create hard shadows as shown below:

![SphereRayTracing picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%204/Readme%20Pictures/Shadows.jpg)

Detailed instruction of implementation can be found in _"Workshop 3A Instructions.pdf"_
 
## Soft Shadows

It is advanced level and optional. 
This week follows on from the last session. This week involves distributed ray tracing to create soft shadows.

Detailed instruction of implementation can be found in _"Workshop 3B Instructions.pdf"_

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