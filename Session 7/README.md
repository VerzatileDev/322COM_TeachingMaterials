# Session 7 - Terrain Lighting and Texturing 

#### Table of Contents
1. [Terran generation solution](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%207#Terran-generation-solution)
2. [Lighting](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%207#Lighting)
3. [Terran Texture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%207#Terran-Texture)
4. [Change camera](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%207#Change-camera)

## Terran generation solution

If you have trouble to implement Diamend-Square algorithm. Here is the function codes. 
In the while loop, there are diamond step, then followed by first square step and other three quare steps.


```C++
    // set height values for four corners 
	terrain[0][0] = h1*10.0;
	terrain[MAP_SIZE - 1][0] = h2*10.0;
	terrain[MAP_SIZE - 1][MAP_SIZE - 1] = h3*10.0;
	terrain[0][MAP_SIZE-1] = h4*10.0;
	int step_size,tt,H,count;
	float rand_max;
	tt  = MAP_SIZE;
	step_size = tt - 1;
	H = 1;
	rand_max = 1.0;

	while (step_size > 1)
	{
		for (int x = 0; x < MAP_SIZE - 1; x += step_size)
			for (int y = 0; y < MAP_SIZE - 1; y += step_size)
			{
				//diamond_step(x, y, stepsize)
				h1 = terrain[x][y];
				h2 = terrain[x+ step_size][y];
				h3 = terrain[x][y + step_size];
				h4 = terrain[x + step_size][y + step_size];
				aver = (h1 + h2 + h3 + h4) / 4.0;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h*10.0*rand_max;
				terrain[x + step_size / 2][y + step_size / 2] = aver;
			}

		for (int x = 0; x < MAP_SIZE - 1; x += step_size)
			for (int y = 0; y < MAP_SIZE - 1; y += step_size)
			{
				//square_step(x, y)
				count = 0;
				h1 = terrain[x][y];  count++;
				h2 = terrain[x][y + step_size];  count++; //below
				if ((x - step_size / 2) >= 0) { h3 = terrain[x - step_size / 2][y + step_size / 2]; count++; }
				else { h3 = 0.0; }
				if ((x + step_size / 2) <MAP_SIZE) { h4 = terrain[x + step_size / 2][y + step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) /(float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h*10.0*rand_max;
				terrain[x][y + step_size / 2] = aver;

				//second one
				count = 0;
				h1 = terrain[x][y];  count++;
				h2 = terrain[x + step_size][y];  count++; //below
				if ((y - step_size / 2) >= 0) { h3 = terrain[x + step_size / 2][y - step_size / 2]; count++; }
				else { h3 = 0.0; }
				if ((y + step_size / 2) <MAP_SIZE) { h4 = terrain[x + step_size / 2][y + step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h*10.0*rand_max;
				terrain[x + step_size / 2][y] = aver;

				//third one
				count = 0;
				h1 = terrain[x + step_size][y];  count++;
				h2 = terrain[x + step_size][y + step_size];  count++; //below
				h3 = terrain[x + step_size / 2][y + step_size / 2]; count++; 
				if ((x + 3*step_size / 2) <MAP_SIZE) { h4 = terrain[x + 3 * step_size / 2][y + step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h*10.0*rand_max;
				terrain[x + step_size][y + step_size / 2] = aver;

				//fourth one
				count = 0;
				h1 = terrain[x][y + step_size];  count++;
				h2 = terrain[x + step_size][y + step_size];  count++; //below
				h3 = terrain[x + step_size / 2][y + step_size / 2]; count++;
				if ((y + 3 * step_size / 2) <MAP_SIZE) { h4 = terrain[x + step_size / 2][y + 3 * step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h*10.0*rand_max;
				terrain[x + step_size / 2][y + step_size] = aver;
			}

		rand_max = rand_max * pow(2, -H);
		step_size = step_size / 2;
	}
```

The completed solution can be found in TerrainGeneration.cpp.

## Lighting

The wireframe of terrain need to be added light effects. The instruction can be found in "Workshop 7 Instructions.pdf". 

The final result of lighting should look like this

![TerrainLight picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%207/Readme%20Pictures/TerrainLight.JPG)

The vertex shader codes are standard codes for importing terrain mesh data from C++ program.

```C++
#version 420 core

layout(location=0) in vec4 terrainCoords;
layout(location=1) in vec3 terrainNormals;

struct Material
{
vec4 ambRefl;
vec4 difRefl;
vec4 specRefl;
vec4 emitCols;
float shininess;
};

uniform vec4 globAmb;
uniform mat4 projMat;
uniform mat4 modelViewMat;
uniform mat3 normalMat;

out vec3 normalExport;

void main(void)
{
   normalExport = terrainNormals;
   normalExport = normalize(normalMat * normalExport);
   
   gl_Position = projMat * modelViewMat * terrainCoords;
}
```

The fragment shader involve diffuse light calculation

```C++
#version 430 core

in vec3 normalExport;

out vec4 colorsExport;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};
uniform Light light0;

uniform vec4 globAmb;
  
struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};
uniform Material terrainFandB;

vec3 normal, lightDirection;
vec4 fAndBDif;

void main(void)
{
   normal = normalize(normalExport);
   lightDirection = normalize(vec3(light0.coords));
   fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols *
   terrainFandB.difRefl); 
   colorsExport =  vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);  
}
```
 
## Terran Texture

The instruction for lab task can be found in _"Workshop 7 Instructions.pdf"_.

```C++
	h1 = (rand() % 10) / 5.0 - 1.0;
```








