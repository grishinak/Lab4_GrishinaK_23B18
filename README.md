# Lab4_GrishinaK_23B18
graph visualisation

# Graph Visualization Project

This project is aimed at visualizing graphs using force-directed algorithms. It takes input graph data, performs force-directed planarization, and generates a visual representation of the graph.

## Setup and Dependencies

- This project requires a C++ compiler that supports C++11 or higher.
- This project uses inputreader.h, painter.h, graph.h, masks.h, and functions.h header files.

## Usage

1. Compile the project using C++ compiler via cmake by these commands in terminal.
    1) cmake ..
    2) make 
2. Run the compiled executable.
3. Provide input graph data in input.txt in the project directory with this structure:
   - Number of vertices (V)
   - Number of edges (E)
   - |E| strings of pairs of vertices connected by edges
4. The program will output:
   - Number of vertices and edges in terminal.
   - List of vertex pairs connected by edges in terminal.
   - Coordinates of vertices after force-directed planarization in terminal.
5. The generated image will be saved as "output.bmp" in the project directory.

## Code Overview

- main.cpp: Contains the main function responsible for reading input, performing graph planarization, and generating the visualization.
- inputreader.h: Header file for reading input graph data.
- painter.h: Header file for drawing edges and vertices on the canvas.
- graph.h: Header file for graph representation and planarization algorithms.
- masks.h: Header file for masks used for drawing numbers of vertieces in visualization.
- functions.h: Header file for utility functions used in the project.

## Algorithm

The main algorithm used for graph planarization is the force-directed algorithm, which simulates physical forces between vertices to achieve a graph layout.

## Author

Grishina Kseniya 23B18