# Session 6 - Terrain Generation 

#### Table of Contents
1. [Base project](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%206#Base-project)
2. [Terran generation](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%206#Terran-generation)
3. [Change models](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%206#Change-models)
4. [Change camera](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%206#Change-camera)

## Base project

The base project can be downloaded from this week Github folder. which contains the TerrainShaderized Visual
Studio Solution to get you started with the modern version of OpenGL. The project uses the
libraries: GLM, GLEW and freeglut. The project contains initialisation code to create a window and to draw a flat
height map. Compile and run the code and check that you get the grid shown below.

### Make Sure, the project Configuration is set as 'x64' (NOT 'Win32').

![baseProject picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%206/Readme%20Pictures/TerranFlat.JPG)
 
## Terran generation

The instruction for lab task can be found in _"Workshop 6B Instructions.pdf"_.

Hint: The random function with range from -1 to 1 should be expressed as

```C++
	h1 = (rand() % 10) / 5.0 - 1.0;
```

The final result should like this:

![Finalresult picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%206/Readme%20Pictures/Terran.JPG)





