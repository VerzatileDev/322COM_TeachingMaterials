# Session 3 - Ray Tracing

#### Table of Contents
1. [Ray Tracing Spheres](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Ray-Tracing-Spheres)
2. [Ray Tracing Primitives](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Ray-Tracing-Primitives)
3. [Add triangle class](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Add-triangle-class)
4. [Rendering complex shape](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Rendering-complex-shape)
5. [Example of mesh class](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Example-of-mesh-class)


## Ray Tracing Spheres

This week follows on from the Ray Casting algorithm so you need to have completed at least
last week worload (section 1 and 2). This week involves modelling light to create diffuse and specular
lighting as illustrated below:

![SphereRayTracing picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203/Readme%20Pictures/SphereRayTracing.JPG)

Detailed instruction of implementation can be found in _"Workshop 2A Instructions.pdf"_
 
## Ray Tracing Primitives
 
### Shading planes
To correctly shade other shapes you should refactor your code so that each shape has its own
function to calculate the normal. This is trivial for the plane as you can simply return the normal. You
also need to refactor each shape to replace colour with diffuse colour (𝐤𝐝) and specular colour (𝐤𝐬)
and shininess. Make the specular colour grey, with equal red, green, and blue values e.g.
(0.7,0.7,0.7). Set shininess to zero for matte surface or to a higher value for shiny surfaces.
of the floor.

### Shading triangles
Often triangles are used as an approximation to a smooth surface and many models will come with
the normals supplied (e.g. the cube and teapot used later in this workshop). Assuming the normals
will be supplied for each vertex of the triangle in the model you first you need to store these normals
(n0, n1 and n2) in your triangle class.

Then you need to interpolate the normals over the surface of the triangle so that you can apply the
shading at each pixel. You can re-use the barycentric weights u, v and w that you calculated in your
triangle intersection function to interpolate the normals for each intersection point:
n = w*n0 + u*n1 + v*n2
Hint: don’t forget to normalise n before using it in the shading equations

Render the triangle shown in the image below by using the parameters given.

![Triangle picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203/Readme%20Pictures/TriangleRT.JPG)

Olive triangle with vertices: (0, 1, -2), (-1.9, -1, -2), (1.6, -0.5, -2), normals (0.0, 0.6, 1.0), (-0.4,-0.4,1.0),
vec3(0.4, -0.4, 1.0), diffuse colour (0.5,0.5,0.0), specular colour (0.7, 0.7, 0.7) and shininess (100). Light with
position (1,3,1) and intensity (1,1,1).

### Shading more complex shapes

It is advanced level and is optional.
You previously read the obj files (cubes and teapots) using the loadOBJ function from objloader class
which returned vertices and normals (see code snippet below):

Define data structure of vertex

```C++
 #ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct  VertexWithAll
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textcoord;
	glm::vec3 normal;
};

#endif
};
```

Codes for load mesh data

```C++
	std::vector<VertexWithAll> mesh = loadOBJ(name); //Import OBJ file data into a vector array
	int NumVert = mesh.size();
```

You already created triangles for each 3 vertices and added it to your scene, you
now also need to pass the 3 normals to your triangle class. Once this simple step is complete you
should be able to render any model that you load, start by testing the cube and teapot:

Warning: you will need the “teapot simple smooth.obj” file from moodle to render the smooth
teapot shown below.

![Triangle picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203/Readme%20Pictures/CubeRT.JPG)

Cube - diffuse colour (0.5,0.5,0.0) and shininess(0). Light with position (1,3,1) and intensity (1,1,1)

![Triangle picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203/Readme%20Pictures/TeapotRT.JPG)

Teapot - diffuse colour (0.5,0.5,0.0), specular
colour (0.7, 0.7, 0.7) and shininess (100). Light with
position (1,3,1) and intensity (1,1,1).

## Add triangle class

Add a Triangle class that also inherits from your Shape class. A triangle can be defined by 3
vertices. Add the intersect method using the ray-triangle intersection method (see lecture slide for
more details). Add a triangle to a scene and test that it appears correctly.



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
