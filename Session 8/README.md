# Session 8 - Camera, Skybox and water 

#### Table of Contents
1. [Camera and Skybox](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%208#Camera-and-Skybox)
2. [Animated Water](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%208#Animated-Water)
3. [Terran Texture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%208#Terran-Texture)
4. [Multiple textures](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%208#Multiple-textures)

## Camera and Skybox

Keyboard and mouse controlled OpenGL camera can be used in this scene. The camera and skybox tutorials are in 
https://github.coventry.ac.uk/ac7020/212CR_TeachingMaterial/tree/master/Session%207


## Animated Water

Animated water tutorial using a imported mesh can be found in

https://github.coventry.ac.uk/ac7020/212CR_TeachingMaterial/tree/master/Session%209

However, in this coursework, procedurally generated water is required. So, imported water mesh is not allowed.

To create a water mesh from scratch, we can use terrain mesh codes to create a flat large mesh object. 
Here is some example codes.

```C++
struct Vertex
{
	float coords[4];
	float colors[4];
};

const int MAP_SIZE = 33;  //define mesh size
static Vertex waterVertices[MAP_SIZE*MAP_SIZE] = {};

const int numStripsRequired = MAP_SIZE - 1;
const int verticesPerStrip = 2 * MAP_SIZE;
unsigned int waterIndexData[numStripsRequired][verticesPerStrip];

int i = 0;

	for (int z = 0; z < MAP_SIZE; z++)
	{
		for (int x = 0; x < MAP_SIZE; x++)
		{
			// y value is the height value (set to 0.0) // second part is color value
			waterVertices[i] = { { (float)x, 0.0, (float)z, 1.0 }, { 0.0, 0.0, 0.0, 1.0 } };
			i++;
		}
	}
	
	// Now build the index data
	i = 0;
	for (int z = 0; z < MAP_SIZE - 1; z++)
	{
		i = z * MAP_SIZE;
		for (int x = 0; x < MAP_SIZE * 2; x += 2)
		{
			waterIndexData[z][x] = i;
			i++;
		}
		for (int x = 1; x < MAP_SIZE * 2 + 1; x += 2)
		{
			waterIndexData[z][x] = i;
			i++;
		}
	}
```
 
## Terran Texture

The instruction for lab task can be found in _"Workshop 7 Instructions.pdf"_.

You need to add texture import codes in the C++ program. The texture tutorials can be found in
https://github.coventry.ac.uk/ac7020/212CR_TeachingMaterial/tree/master/Session%204

You need to change fragment shader codes to include texture. For example 
```C++
	fieldTexColor = texture(grassTex, texCoordsExport);
	//final color is combination of diffuse color and texture color
	colorsExport = fAndBDif*fieldTexColor;
```

![TerrainTex picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%207/Readme%20Pictures/TerrainTexture.JPG)





