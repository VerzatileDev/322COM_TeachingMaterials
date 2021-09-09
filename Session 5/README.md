# Session 5 - Vulkan Real-time Ray Tracing 

#### Table of Contents
1. [Installation](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Installation)
2. [Example Project](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Example-Project)
3. [Change models](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Change-models)
4. [Change camera](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Change-camera)
5. [Move light](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Move-light)
6. [Shader programming](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Shader-programming)
7. [Self-learning Topics](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Self-learning-Topics)

## Installation

The best way to find Vulkan SDK is to search Google with keyword "Vulkan SDK". Current it is located at
https://vulkan.lunarg.com/ . Choose your Platform. I only test it on Windows 10 and Windows 7. 
So, I will only talk about installation in Windows. However, other platform installation is similar. 

Step 1: Download Windows installer file and install it on your PC.

Step 2: Download CMake (https://cmake.org/). Install it.

Step 3: Download Vulkan Tutorials from Github https://github.com/SaschaWillems/Vulkan 

Step 4: Launch CMake and generate Visual Studio Project from Makefile
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
 
## Example Project

One of example projects is called as shadowmapping. It is a good start project for our real-time ray tracing using Vulkan.

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/shadowmapping.JPG)

To extract the project files and combine with source codes, You might follow instructions below:

1. Locate project files. 
Inside the Vulkan tutorial folder, look for "bin/examples" folder.
You can find  shadowmapping.vcxproj and shadowmapping.vcxproj.filters files.

2. Copy both project files into /examples/shadowmapping folder.

3. Open project and try to compile it. You will find out one library file (base.lib) is missing.
That is because we moved project file. The relative path to base library file is no longer working.

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/projectsetting.JPG)

4. Fix the missing library. 
I just copy base.lib to project folder. Set relative path to "./base.lib". Now, you should be able to compile the project. 


## Change models

Changing models are relatively easy in this project. Inside the Vulkan tutorial folder, there is a /data/models/ folder.
There are many models including colored models you can choose.
You can change models by changing model name in 

From 

```C++
	void loadAssets()
	{
		const uint32_t glTFLoadingFlags = vkglTF::FileLoadingFlags::PreTransformVertices | vkglTF::FileLoadingFlags::PreMultiplyVertexColors | vkglTF::FileLoadingFlags::FlipY;
		scenes.resize(2);
		scenes[0].loadFromFile(getAssetPath() + "models/vulkanscene_shadow.gltf", vulkanDevice, queue, glTFLoadingFlags);
		scenes[1].loadFromFile(getAssetPath() + "models/samplescene.gltf", vulkanDevice, queue, glTFLoadingFlags);
		sceneNames = {"Vulkan scene", "Teapots and pillars" };
	}
```

to

```C++
	void loadAssets()
	{
		const uint32_t glTFLoadingFlags = vkglTF::FileLoadingFlags::PreTransformVertices | vkglTF::FileLoadingFlags::PreMultiplyVertexColors | vkglTF::FileLoadingFlags::FlipY;
		scenes.resize(2);
		scenes[0].loadFromFile(getAssetPath() + "models/chinesedragon.gltf", vulkanDevice, queue, glTFLoadingFlags);
		scenes[1].loadFromFile(getAssetPath() + "models/samplescene.gltf", vulkanDevice, queue, glTFLoadingFlags);
		sceneNames = {"chinesedragon", "Teapots and pillars" };
	}
```

New results are

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/dragon.JPG)

## Change camera

The old camera is too far from our new model and rotated. To fix that, find the construct function and camera parameters

From 

```C++
	VulkanExample() : VulkanExampleBase(ENABLE_VALIDATION)
	{
		title = "Projected shadow mapping";
		camera.type = Camera::CameraType::lookat;
		camera.setPosition(glm::vec3(0.0f, -0.0f, -20.0f));
		camera.setRotation(glm::vec3(-15.0f, -390.0f, 0.0f));
		camera.setPerspective(60.0f, (float)width / (float)height, 1.0f, 256.0f);
		timerSpeed *= 0.5f;
		settings.overlay = true;
	}
```

To

```C++
	VulkanExample() : VulkanExampleBase(ENABLE_VALIDATION)
	{
		title = "Projected shadow mapping";
		camera.type = Camera::CameraType::lookat;
		camera.setPosition(glm::vec3(0.0f, -0.0f, -5.0f));  //move camera close to the object by change Z values
		camera.setRotation(glm::vec3(-90.0f, 0.0f, 90.0f)); //Reset camera rotation
		camera.setPerspective(60.0f, (float)width / (float)height, 1.0f, 256.0f);
		timerSpeed *= 0.5f;
		settings.overlay = true;
	}
```

New results are

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/dragonReset.JPG)


## Move light

The old light is too far from the object. It need to be adjusted. The light position is defined in void updateLight() function.

Old codes

```C++
	void updateLight()
	{
		// Animate the light source
		lightPos.x = cos(glm::radians(timer * 360.0f)) * 40.0f;
		lightPos.y = -50.0f + sin(glm::radians(timer * 360.0f)) * 20.0f;
		lightPos.z = 25.0f + sin(glm::radians(timer * 360.0f)) * 5.0f;
	}
```

New codes

```C++
	void updateLight()
	{
		// Animate the light source
		lightPos.x = -20.0f + cos(glm::radians(timer * 360.0f)) * 2.0f; //align with object center
		lightPos.y = -10.0f + sin(glm::radians(timer * 360.0f)) * 20.0f;
		lightPos.z = -20.0f + sin(glm::radians(timer * 360.0f)) * 5.0f;  // move light close to the camera
	}
```

You also can test new light position with teapot scene. Just got shadowmapping scene setting menu. Change to Teapots.

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/Teapot.JPG)

## Shader programming

Before we can change the shader codes, first we need to find out where the shader codes are.
The Vulkan tutorials store all shader files in /data/shader/glsl/ folder. As we are familar with OpenGL glsl shader codes, we are better to use codes in glsl format.

Copy shadowmapping shader to your project folder and rename it as shader folder. Now, we change path setting in shadowmapping project.

The path is defined in void preparePipelines() function

```C++
		shaderStages[0] = loadShader(getShadersPath() + "shadowmapping/scene.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
		shaderStages[1] = loadShader(getShadersPath() + "shadowmapping/scene.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
```

If you move shader folder inside your project folder, you can change codes to


```C++
		shaderStages[0] = loadShader("./shader/scene.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);  
		shaderStages[1] = loadShader("./shader/scene.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
```

You might notice that the shader file (*.spv) for Vulkan is binary so you can not edit. 
But there are glsl format of shaders which are text format.

To convert glsl format to spv format using following commands

```C++
   glslc.exe shader.vert -o vert.spv
   glslc.exe shader.frag -o frag.spv
```

### Change object color via shader codes

In the fragment shader 

```C++
	vec3 N = normalize(inNormal);
	vec3 L = normalize(inLightVec);
	vec3 V = normalize(inViewVec);
	vec3 R = normalize(-reflect(L, N));
	vec3 diffuse = max(dot(N, L), ambient) * inColor;

	outFragColor = vec4(diffuse * shadow, 1.0);
```

Change to 

```C++
	vec3 N = normalize(inNormal);
	vec3 L = normalize(inLightVec);
	vec3 V = normalize(inViewVec);
	vec3 R = normalize(-reflect(L, N));
	vec3 newColor = vec3(0.0,1.0,1.0);
	vec3 diffuse = max(dot(N, L), ambient) * newColor;

	outFragColor = vec4(diffuse * shadow, 1.0);
```

Delete old scene.frag.spv and run converting command

```C++
	glslc.exe scene.frag -o scene.frag.spv
```

The new color result is

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/dragonColor.JPG)

### Add specular lighting effect

We can continue to work on fragment shader by adding specular lighting calculation codes. As we learn in second-year graphic module,
 spec = pow(max(dot(viewDir,reflectDir),0.0),32); // 32 is specular power factor. The higher value, more reflective.
 refelctDir vector = reflect(-lightDir, normal); 
 
 Finally, the new codes for fragment shader
 
```C++
	vec3 N = normalize(inNormal);
	vec3 L = normalize(inLightVec);
	vec3 V = normalize(inViewVec);
	vec3 R = normalize(-reflect(L, N));
	vec3 newColor = vec3(0.0,1.0,1.0);
	vec3 diffuse = max(dot(N, L), ambient) * newColor;
	
	vec3 reflectDir = reflect(-L, N);
	float spec = pow(max(dot(V,reflectDir),0.0),16);
	vec3 speColor = vec3(1.0,1.0,1.0);
	vec3 specular = spec * speColor;

	outFragColor = vec4((diffuse+specular) * shadow, 1.0);
```

The new result is

![shadowmapping picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205/Readme%20Pictures/dragonSpec.JPG)

## Self-learning Topics

Before we can change the shader codes, first we need to find out where the shader codes are.