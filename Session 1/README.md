# Session 1 - Setting up the project and GitHub

#### Table of Contents
1. [Setting up in GitHub](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#setting-up-in-github)
2. [Cloning the repository](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#cloning-the-repository)
3. [Creating a C++ Project using Visual Studio](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#creating-a-c-project-using-visual-studio)
4. [Base Code](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#base-code)
5. [Add GLM library](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#Add-GLM-library)
6. [Add Spheres](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201#Add-Spheres)


Welcome to this 322COM tutorial series! 

> Session 1 and 2 are instructions for using Github (basic commands). If you are familiar with Github or you do not want to use github. You can go straight to section 3.

For this week's session, we will be setting up GitHub and starting the base C++ project. This will get us ready for the later weeks and become a start for your coursework.

## Setting up in GitHub

As you will know by reading the assessment brief, your coursework can be on the Coventry GitHub server. 

Go onto the Coventry GitHub server via https://github.coventry.ac.uk and sign in via the top right. _This will be your normal username and password you use to log into university PCs._



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
 
  ## Cloning the repository
  
Once you have made your repository, it should take you to it's page. (If you have backed out of this, you can always find it by clicking on your profile picture and selecting _"Your repositories"_.)
  
The next step is to clone this repository to your PC so you have a local copy to do changes on.

> For these tutorials, I will be using the command line (_cmd_) to use Git. You are allowed to use programs like GitHub Desktop (which can be accessed via AppsAnywhere) but if you come into problems with them, **staff might not be able to help**.

To clone a respository you will need the URL of it. Copy this from the address bar of your browser or use the green _"Clone or download"_ button and copy the URL from the pop up box.

![Cloning a repository picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/Clone%20or%20Download.PNG)
  
  Open command line by typing cmd into Windows search. 
  
  Once there, you might have to navigate to your user area on the hard drive.
  
  The following cmd commands will be helpful to do this.
  
  Command     |  Explanation
------------- | -------------
C:            | Will change what hard drive disk is currently looked at.
cd "folder name" | Go into that directory / folder.
cd .. | Go back a directory / folder.
dir      | Print out what is in the directory.
mkdir "name for directory" | Create that directory / folder.
git clone "url" | Clones the repository into the current directory you are at.

![cmd steps picture](https://github.coventry.ac.uk/217CR-1920JANMAY/Teaching-Material/blob/master/Session%201/Readme%20Pictures/cmd%20steps.PNG)

> _These are the steps I took to get to my Documents folder for example._

**Make sure you are at a sensible place directory wise before you clone your repository so you can find it later!**

Once at a good directory, git clone your repository. It might ask you to log in with your GitHub credentials. 

When you have submitted them, the repository (and it's files) should now be on your PC.

At the moment, it should only be the README file.
  
![cloned picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/Cloned.PNG)

It is here that we will create a C++ project so it is in the GitHub repository, meaning we can push and pull changes to it.

## Creating a C++ Project using Visual Studio
 
> If you are not using Visual Studio 2019

* Open Visual Studio and Click _"File"_ -> _"New"_ -> _"Project.."_
* Select _"Empty Project"_.
* Make sure _"Create directory for solution"_ is unticked.
* Give it a sensible name.
* Make sure the location is the same as where the README file is stored.

> If you are using Visual Studio 2019, click "Continue without code".

* Click _"File"_ -> _"New"_ -> _"Project.."_
* Pick _"C++"_ as the Language to filter the list.
* Select _"Empty Project"_ and then _"Next"_.
* Give it a sensible name.
* Make sure _"Place solution and project in the same directory"_ is ticked.
* Make sure the location is the same as where the README file is stored.

Once this has been done, click _"Create"_.

![color ray picture](https://github.coventry.ac.uk/ac7020/212CR_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/Empty%20Project.PNG)

We need to create the _.cpp_ file that will hold the _main()_ function. Remember, every C++ program needs a _main()_ function to run.

This can be done by right clicking "Source Files" on the right hand side (in the Solution Explorer) and clicking _"Add"_ -> _"New Item..."_.

Make sure C++ File (_.cpp_) is highlighted and either change the name (I always use _main.cpp_) or keep it as _Source.cpp_ and click _"Add"_ in the bottom right.


## Base Code

We will just add some base codes.The base codes are the first step in ray casting: constructing rays
from the camera that pass through each pixel and when completed should look something similar to
this. 

![empty project picture](https://github.coventry.ac.uk/ac7020/322COM_TeachingMaterial/blob/master/Session%201/Readme%20Pictures/ColorRay.JPG)

Copy all the code from the _"BaseCode.cpp"_ which is on the Week 1 GitHub page and paste it over everything in your _"main.cpp"_.

If you want to find out how codes work. Please refer to _"Workshop 1A Instructions.pdf"_.

The program does not display anything, instead it generate a PPM image file. It can be opened using Photoshop.

## Add GLM library

Doownload _"glm_0.9.9.8.zip"_ which is on the Week 1 GitHub page. GLM is a header-file only library. So, it will be added in C/C++ section 
in project property pages. The path refer to the library should be relative (.\glm-0.9.9.8). Make sure that you unzip the library zip inside your project folder.
Now, you compile the project and generate an executable file.

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
