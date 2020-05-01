RED='\033[0;31m' # Red Color
GREEN='\033[0;32m' # Green Color
NC='\033[0m' # No Color

Success=${GREEN}Succeeded${NC}
Failure=${RED}Failed${NC}
Err=${RED}Error${NC}

sfmlVersion="2.4.1"


projectMake=$Failure

rootDir=$(pwd)
resourceDir=$rootDir/resources
sfmlDir=$resourceDir/SFML
smflBuildDir=$sfmlDir/build
smflInstallDir=$sfmlDir/install
smflInstalledlibs=$smflInstallDir/lib
smflExtLibs=$sfmlDir/extlibs/libs-osx/lib
smflExtFrameworks=$sfmlDir/extlibs/libs-osx/Frameworks

printf "Welcome to the akhilesh PacMan resource builder\n"

function cloneAndFixDirectories {
	printf "Cloning and Making relevant directories\n"
	cd "$rootDir"
	printf "Creating resource directory\n"
	mkdir resources
	cd "$resourceDir"

	printf "Started cloning\n"
	git clone https://github.com/SFML/SFML.git
	cd SFML
	git submodule update --init --recursive -f

	printf "Checking out version = $sfmlVersion\n"
	git checkout $sfmlVersion

	printf "making install and build directory\n"
	mkdir build
	mkdir install
	printf "Cloning completed\n"
	cd "$sfmlDir"
}

function checkRequirements {
	if ! [ -x "$(command -v cmake)" ]
	then
		printf "$Err: cmake command not found. Install cmake and update PATH and then run the script again.\n"
		exit 4
	else
		printf "CMake exists\n"
	fi

	if ! [ -x "$(command -v git)" ]
	then
		printf "$Err: git command not found. Install GIT and update PATH and then run the script again.\n"
		exit 4
	else
		printf "GIT exists\n"
	fi
}



if ! [[ -z "$1" ]]
then
	if [[ $1 = "clean" ]]
	then
		printf "Cleaning the resources\n"
	
		cd "$rootDir"
		rm -rf "$resourceDir"
		exit 0
	else
		checkRequirements
		cloneAndFixDirectories

		printf "Running CMake.\n"
		if [[ $1 = "release" ]]
		then
			cmake -DCMAKE_INSTALL_PREFIX=./build -DSFML_DEPENDENCIES_INSTALL_PREFIX=./install -DSFML_MISC_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE="Release" -DBUILD_SHARED_LIBS=1 -DSFML_BUILD_GRAPHICS=1 -DSFML_BUILD_WINDOW=1
		else
			cmake -DCMAKE_INSTALL_PREFIX=./build -DSFML_DEPENDENCIES_INSTALL_PREFIX=./install -DSFML_MISC_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE="Debug" -DBUILD_SHARED_LIBS=1 -DSFML_BUILD_GRAPHICS=1 -DSFML_BUILD_WINDOW=1
		fi
	fi
else
	checkRequirements
	cloneAndFixDirectories
	printf "Running CMake.\n"
	cmake -DCMAKE_INSTALL_PREFIX=./build -DSFML_DEPENDENCIES_INSTALL_PREFIX=./install -DSFML_MISC_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug -DSFML_BUILD_GRAPHICS=1 -DSFML_BUILD_WINDOW=1

fi

if [[ $? == 0 ]]
then
	projectMake=$Success
else
	projectMake=$Failure
fi

printf "Running Make install.\n"
cd "$sfmlDir"
make clean
make install

if [[ $? == 0 ]]
then
	installResult=$Success
else
	installResult=$Failure
fi

printf "Copying libraries and dependencies\n"

cd "$sfmlDir"
cp -r lib/. install/lib
cp -r include install
cp -r "$smflExtLibs/." "$smflInstalledlibs"
cp -r "$smflExtFrameworks/." "$smflInstalledlibs"

cd "$rootDir"
printf "CMake Result = $projectMake\n"
printf "Make Result = $installResult\n"




