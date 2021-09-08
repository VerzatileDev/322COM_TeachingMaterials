# Session 3 - Ray Tracing

#### Table of Contents
1. [Ray Tracing Spheres](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Ray-Tracing-Spheres)
2. [Ray Tracing Primitives](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Ray-Tracing-Primitives)
3. [Multithread](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%203#Multithread)
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

## Multithread

You might find your ray tracing programming is quite slow if including a lot of objects. You can use multithread to speed up.
An simple implementation of multithread can be found in _"MThread.cpp"_.
It creates 10 threads and display "Hello from thread". 

To use multithread in your ray tracing progamming. You should split your intersection and computing color tasks into different threads.
For example, you create 32 threads. Each one 1/32 of screen rendering for ray tracing.
 
```C++
	std::vector<std::thread> threads;
	const int threadCount = 32;
	for (int i = 0; i < threadCount; i++) {
		threads.push_back( std::thread(MultiThread,i*WIDTH/threadCount,(i+1)* WIDTH / threadCount));

	}

	for (int i = 0; i < threadCount; i++) {
		threads[i].join();

	}
```

Then you define a multithread function which executes in each thread. It assign colors directly to image[x][y],
which will be updated in computer screen.

```C++
void MultiThread(int start, int end) {
	vec3 finalCol;

	//loop through pixels
	for (int x = start; x < end; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			vec3 thisPixelRayDir = ConstructRay(x, y);

			finalCol = vec3(0,0,0);
			TraceAndGetColour(thisPixelRayDir, RAYORIGIN, finalCol, 0);
			image[x][y] = finalCol;

		}
		OutputToScreen();
	}
}
```

The TraceAndGetColour is your ray tracing function which does heavy computation.

## Rendering 

This section 