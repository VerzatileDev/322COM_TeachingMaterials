# Session 2 - Ray Casting

#### Table of Contents
1. [Sphere Ray Casting Solution](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%202#setting-up-in-github)
2. [Cloning the repository](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#cloning-the-repository)
3. [Creating a C++ Project using Visual Studio](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#creating-a-c-project-using-visual-studio)
4. [Base Code](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#base-code)


## Sphere Ray Casting Solution

If you have trouble to implement sphere ray intersection. Here is the function codes.

```C++
//center is the sphere center position
//orig is the origin of the ray. You set it up as (0,0,0)
//dir is the direction of the ray
//t is the return parameter value of intersection. Range from [0,1]
bool intersectSphere(vec3 center, vec3 orig, vec3 dir, float radius, float &t)
{
	float t0, t1; // solutions for t if the ray intersects 

	// geometric solution  // vector dir has to be normalize, length is 1.0
	vec3 L = center - orig;
	float tca = dot(L, dir);
	if (tca < 0) return false;
	float d = dot(L,L) - tca * tca;
	if (d > (radius*radius)) return false;

	float thc = sqrt(radius*radius - d);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return false; // both t0 and t1 are negative 
	}

	t = t0;
	return true;
}
```

A simple sphere class (header file):
```C++
#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Sphere
{
private:
	float radius;
	vec3  center;
	vec3 mycolor;
public:
	Sphere(float,vec3,vec3);
	~Sphere();
	float getRadius(void);
	vec3 getCenter(void);
	vec3 getMyColor(void);
};
```

CPP file for the sphere class
```C++
#include "stdafx.h"
#include "sphere.h"

Sphere::Sphere(float r, vec3 cen, vec3 col) {
	radius = r;
	center = cen;
	mycolor = col;
}

Sphere::~Sphere()
{
}

float Sphere::getRadius(void)
{
	return radius;
}

vec3 Sphere::getCenter(void)
{
	return center;
}

vec3 Sphere::getMyColor(void)
{
	return mycolor;
}
```

![Sign in picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/Sign%20in.PNG)
 
Once you have logged into the server, 

Click on + button to add new repository under your username. You are also welcome to use your own organization. 

![Organizations picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/AddRepos.JPG)
 
 Once there, create a new repository via the green _"New button"_.
 
 * For the repository name, call it something obvious (and add your student ID) to the front.
 * Set it to private (or everyone in the university can see it!).
 * Initialize a README file.
 
 By doing all of this, it means that the markers will be able to see it, that other students cannot and that you can clone it straight away to your PC.
 
![Create a repository picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/CreateRepos.PNG)
 
 Finally, add the module staff to your repository so they have access to it. (Our information can be found on the 212CR Aula page under _Module Essentials_.)
 
 Go into your repository from the website, click "Settings", then "Collaborators", and then search for, and add, both members of module staff (YingLiang Ma (ac7020) and Ian) to the page. 
 
 ![Add collaborators picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/Add%20Collabs.png)
 
  
## Creating a C++ Project using Visual Studio
 
> If you are not using Visual Studio 2019

* Open Visual Studio and Click _"File"_ -> _"New"_ -> _"Project.."_
* Select _"Empty Project"_.
* Make sure _"Create directory for solution"_ is unticked.
* Give it a sensible name.
* Make sure the location is the same as where the README file is stored.



## Add Spheres
This section is based on rendering 3D spheres using the Ray Casting algorithm and when
completed should look something similar to this:

![Sphere picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/Spheres.jpg)

First you need to create primitives to populate the world. In this workshop you will render
spheres so you will need to create a Sphere class and add some test spheres to your world. The
Sphere class should contain the position of the centre of the sphere and its radius as well as its
surface colour. Feel free to create your own colours, sizes and positions of spheres but they won’t
appear until you have completed the next step.
 
Here is an example scene, based on the screenshot above:
* Red sphere: Position (0, 0, -20), Radius (4), Colour (1.00, 0.32, 0.36)
* Yellow sphere: Position (5, -1, -15), Radius (2), Colour (0.90, 0.76, 0.46)
* Light blue sphere: Position (5, 0, -25), Radius (3), Colour (0.65, 0.77, 0.97)
* Light grey sphere: Position (-5.5, 0, -15), Radius (3), Colour (0.90, 0.90, 0.90)

Notice that even though the light blue and light grey sphere are the same size the light grey sphere
appears much larger as it is nearer to the camera.

Even the floor can be created by a very large sphere:
* Dark grey sphere: Position (0, -10004, -20), Radius (10000), Colour (0.2, 0.2, 0.2)

### Step two
Find intersections between the ray and spheres. Add a method for ray-sphere intersection to
your Sphere class (see lecture slide on geometric solution for more details). If the ray hits a sphere,
return true, else return false.

There is also some different methods/implementations.
https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

### Step three
Use the intersect method for each ray, if the ray hits a sphere, set the colour of the nearest
sphere at the intersection point, else set the background colour.

Your ray casting algorithm is now complete so if you compile and run your code you should be able
to see your spheres in the output file. Verify that the spheres appear as you intended and make sure
that some of your spheres overlap so that you can test if you are correctly displaying the colour of
the nearest sphere.
Although, the spheres look boring right now your code can be extended for shading, shadows and
reflections, these will be covered in future workshops.
