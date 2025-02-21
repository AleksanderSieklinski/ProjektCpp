# Micromouse Simulation

## Overview
The Micromouse simulation application is designed to simulate the behavior of a Micromouse robot navigating through a maze. The project includes various components that work together to create an interactive simulation environment.

## Project Structure
The project is organized into the following directories and files:

- **src/**: Contains the source code for the application.
  - **main.cpp**: Entry point of the application that initializes the GUI and starts the simulation.
  - **mouse.cpp**: Implementation of the Mouse class, handling movement and decision-making.
  - **mouse.h**: Header file for the Mouse class, declaring its methods and properties.
  - **maze.cpp**: Implementation of the Maze class, responsible for maze generation and management.
  - **maze.h**: Header file for the Maze class, declaring its methods and properties.
  - **utils/**: Contains utility classes for the application.
    - **logger.cpp**: Implementation of the Logger class for logging simulation data.
    - **logger.h**: Header file for the Logger class, declaring its methods and properties.
  
- **CMakeLists.txt**: Configuration file for CMake, specifying project details and source files.

- **README.md**: Documentation for the project, providing an overview, setup instructions, and usage guidelines.

## Setup Instructions
1. **Clone the Repository**: 
   ```
   git clone <repository-url>
   cd micromouse-simulation
   ```

2. **Build the Project**:
   - Ensure you have CMake installed.
   - Create a build directory and navigate into it:
     ```
     mkdir build
     cd build
     ```
   - Run CMake to configure the project:
     ```
     cmake ..
     ```
   - Compile the project:
     ```
     make
     ```

3. **Run the Simulation**:
   - After building, you can run the simulation executable:
     ```
     ./micromouse-simulation
     ```

## Usage Guidelines
- The simulation allows you to observe the Micromouse robot as it navigates through randomly generated mazes.
- You can adjust parameters such as sensor range and speed in the Mouse class to see how they affect the robot's performance.
- Logs of the simulation can be accessed through the Logger class for analysis and debugging.

## Contributing
Contributions to the Micromouse simulation project are welcome. Please submit a pull request or open an issue for any suggestions or improvements.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.