# SFML_Bouncing_Balls

![Random King](https://github.com/Loksta8/SFML_Bouncing_Balls/blob/main/SFMLRandomBallsBouncing2024-12-1809-41-25-ezgif.com-optimize.gif?raw=true)

**PURPOSE**:
To use SFML and simulate bouncing balls.


**BACKGROUND**:
To use SFML graphically, to simulate balls colliding off each other.

## CMAKE Steps to build project

1. Download `CMAKE`.

2. A file named `CMakeLists.txt` is inside the root directory of this project.

3. Open `CMAKE` and in the `Where is the source code:` navigate to the root `CMakeLists.txt`.

4. In the `Where to build the binaries:` create a `build` folder preferably outside of the repo and point to that folder.

5. Assuming you already have `CMAKE` configured correctly with `Visual Studio 17 2022` click `Generate` and once completed then open the project.

6. Inside the IDE right click on `main` and click `Set as Startup Project`.

7. Build the project (If it errors you might have to click on `Show all Files` and delete `Debug`).

8. Click `Play` (Debug) and watch the balls randomly spawn and proceed to bounce around the screen.


**CMake version used**: 
cmake_minimum_required(VERSION 3.29.2)

**Compiler**: 
C++17