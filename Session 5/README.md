# Session 5 - Vulkan Real-time Ray Tracing 

#### Table of Contents
1. [Installation](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Installation)
2. [Example Project](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Example-Project)
3. [Change models](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Change-models)
4. [etets](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%205#Recursive-Reflection)

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
