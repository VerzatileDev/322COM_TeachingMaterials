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

However, in this coursework, procedurally generated water is required. So, imported water mesh is not allow.

To create a water mesh from scratch, we can use terrain mesh codes to create a flat large mesh object. 
Here is some example codes.

```C++
elViewMat * terrainCoords;
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

## Multiple textures

The multiple textures can be applied to the terrain so that different height levels have different colors.
For low level close to water, it will be sandy color. The color in the highest level is white (snow color).
So, you just import multiple texture maps in the C++ program and add texture colors into fragment shader. 
 
```C++
	if(height <= -4.5f)
	{
		textureMap = texture(sandTexture, texCoordsExport);
	}
	else if(height <= -3.5f)
	{
		float diff = -3.5f - height; // a value between 0, 1
		textureMap = (texture(sandTexture, texCoordsExport) * diff) + (texture(grassTexture, texCoordsExport) * (1-diff));
	}
	else if(height <= 8.5f)
	{
		textureMap = texture(grassTexture, texCoordsExport);
	}
	else
	{
		textureMap = texture(snowTexture, texCoordsExport);
	}
```



