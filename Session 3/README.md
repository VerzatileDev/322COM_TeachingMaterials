# Session 3 - Interactive Ray Tracing

#### Table of Contents
1. [Add screen display using SDL2 Library](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Add-screen-display-using-SDL2-Library)
2. [Redesign data class](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Redesign-data-class)
3. [Add triangle class](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Add-triangle-class)
4. [Rendering complex shape](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Rendering-complex-shape)
5. [Example of mesh class](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Example-of-mesh-class)


## Add screen display using SDL2 Library

Simple DirectMedia Layer (SDL2) is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. 

SDL officially supports Windows, Mac OS X, Linux, iOS, and Android.

An example of screen display is provide in _"SDLPixel.cpp"_. The example code only display a white screen. You need to add ray casting/tracing codes.

The function PutPixel32_nolock ouput color into computer screen. You need to create a Uint32 color object using convertColour() function.

If you use empty project as startup option in Visual Studio, you must choose the Console option. 
It is Project Property->Linker->System->SubSystem. SubSystem should set to Console (/SUBSYSTEM:CONSOLE)
 
## Redesign data class
 
Before your code becomes too complex this is a good opportunity to refactor your ray casting code
so that it is capable of rendering any primitive e.g. planes and triangles.

Step 1: Create a base Shape class which should contain a virtual method for the intersection and
then inherit Sphere from this class. Test that your code still runs correctly after the refactoring.

Step 2: Add a Plane class that also inherits from your Shape class. The plane can be defined by a
point on the plane and the normal to the plane. Add the intersect method using the ray-plane
intersection method (see lecture slides for more details). Add a floor plane instead of the floor
Sphere and test your code. Your scene may look very similar to before but actually the previous floor
Sphere had a very slight curve whereas your floor will now be flat.

Note: you will need to experiment with the field of view angle to effectively zoom out and see more
of the floor.

![Plane picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%202/Readme%20Pictures/Plane.jpg)

## Add triangle class

Add a Triangle class that also inherits from your Shape class. A triangle can be defined by 3
vertices. Add the intersect method using the ray-triangle intersection method (see lecture slide for
more details). Add a triangle to a scene and test that it appears correctly.

![Triangle picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%202/Readme%20Pictures/Triangle.jpg)

Triangle with vertices: (0, 1, -2), (-1.9, -1, -2), (1.6, -0.5, -2)

## Rendering complex shape

This section is advanced level so it is optional. 
To render more complex shapes e.g. teapot you will need to be able to load a mesh from a file and
render each of its triangles. A simple mesh loader (OBJloader.h) written in C++ can be downloaded from Week 2 folder.
Note this code is limited to only loading meshes of file type OBJ. 

The mesh loader handle the import of OBJ file is inside the header file : OBJloader.h.
This is a head file only library. It is a simplified version of Bly7 OBJ Loader library ( https://github.com/Bly7/OBJ-Loader  ).

Examples of a cube and a teapot OBJ files can also be downloaded from week 2.

## Example of mesh class

This section is advanced level so it is optional.

An example of abstract shape class
 ```C++
#pragma once
#include "glm/glm/glm.hpp"

using namespace glm;

class shape
{
private:
	vec3 center;
	vec3 diffuseColor; 
	vec3 diffuseItensity; 

public:
	shape();
	virtual bool intersection(vec3 rayDirection, vec3 rayOrigin, float& t, vec3& IntPt, vec3& normVec);
	
	//for future ray tracing
	virtual void ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, float& ColValue);
	~shape();
	vec3 position;
	vec3 mcolor;
};
```

You need to write your own CPP file for shape class

An example of mesh/triangle class
 ```C++
#pragma once
#include "shape.h"
#include "glm/glm/glm.hpp"

class triangle : public shape
{
private:
	vec3 vertex0, vertex1, vertex2;
	vec3 norm0, norm1, norm2;

public:
	triangle(vec3 pos, vec3 v0, vec3 v1, vec3 v2, vec3 color);
	triangle(vec3 pos, vec3 v0, vec3 v1, vec3 v2,
		vec3 n0, vec3 n1, vec3 n2,
		vec3 color) :
		vertex0(v0), vertex1(v1), vertex2(v2), norm0(n0), norm1(n1), norm2(n2)
	{
		mcolor = color;
	};

	bool intersection(vec3 rayDirection, vec3 rayOrigin, float& t, vec3 &IntPt, vec3& normVec)override;
	void ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, const vec3 tNormvec, float& ColValue);
	~triangle();
};
```

An example of triangle interection implementation (Moller-Trumbore method).
The method is explained in https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

```C++
bool triangle::intersection(vec3 rayDirection, vec3 rayOrigin, float &t, vec3 &IntPt, vec3 &normVec)
{
	//Moller-Trumbore

	vec3 v0v1 = vertex1 - vertex0;
	vec3 v0v2 = vertex2 - vertex0;

	float u = (dot((rayOrigin - vertex0), (cross(rayDirection, v0v2)))) / dot(v0v1, cross(rayDirection, v0v2));
	float v = (dot(rayDirection, cross(rayOrigin - vertex0, v0v1))) / dot(v0v1, cross(rayDirection, v0v2));

	float w = 1 - u - v;

	if (u < 0 || u > 1)
		return false;
	else if (v < 0 || (u + v) > 1)
		return false;
	else
	{
		IntPt = rayOrigin + t * rayDirection;
		normVec = glm::normalize(w * norm0 + u * norm1 + v * norm2);
		//normVec = norm0;
		t = dot(v0v2, cross((rayOrigin - vertex0), v0v1)) / dot(v0v1, cross(rayDirection, v0v2));
		return true;
	}
}
```
