# PacMan

![playdesc](https://github.com/akhileshzmishra/PacMan/blob/master/images/displayPacman.png)

## Work Done as of now
1. Score Calculation in progress
2. Basic play is done.
3. When Ghost catches up, that scenario is not correctly displayed.

## Platform Supported
1. Mac is supported as of now.
2. Windows would be built a little latere.

## Requirements
1. Git.
2. CMake
3. Visual Studio 2017 (for Windows)
4. XCode 13+ (for Mac)

## How to build
1. First generate resources by running ./genProject.sh
2. Then open the project and run

## Known issue
1. When ./genProject.sh is run, it might fail to install FLAC framework. That is ok. The project has been built by this time.
2. If rebuild is a problem, clean and build from XCode or Visual Studio.


# Dependency:
The project depends upon https://www.sfml-dev.org. Specifically the version 2.4.1. If you are developing and need to change version, you can look into ./genproject.sh 



