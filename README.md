
# Data Structures Command Interpreter (C++)

This project is a C++ command interpreter for classic data structures: AVL Tree, Graph, Hash Table, Min Heap, and Max Heap. It reads commands from a file, executes them on the corresponding data structure, and writes results to an output file. The project is designed for educational and demonstration purposes.

## How It Works

1. **Command Input:**
	- The interpreter reads commands from `commands.txt`.
	- Each command specifies an operation (e.g., build, insert, delete, search) and the target data structure.

2. **Supported Data Structures:**
	- AVL Tree
	- Graph
	- Hash Table
	- Min Heap
	- Max Heap

3. **Supported Commands:**
	- `BUILD <DATA_STRUCTURE> <FILENAME>`: Build the structure from a file.
	- `GETSIZE <DATA_STRUCTURE>`: Get the number of elements (or vertices/edges for Graph).
	- `FINDMIN <MINHEAP/AVLTREE>`: Find the minimum element.
	- `FINDMAX <MAXHEAP>`: Find the maximum element.
	- `SEARCH <DATA_STRUCTURE> <VALUE>`: Search for a value.
	- `INSERT <DATA_STRUCTURE> <VALUE...>`: Insert a value (or edge for Graph).
	- `DELETE <DATA_STRUCTURE> <VALUE...>`: Delete a value (or edge for Graph).
	- `DELETEMIN <MINHEAP>`: Remove the minimum element.
	- `DELETEMAX <MAXHEAP>`: Remove the maximum element.
	- `COMPUTESHORTESTPATH <GRAPH> <START> <END>`: Compute shortest path in a graph.
	- `COMPUTESPANNINGTREE <GRAPH>`: Compute minimum spanning tree cost.
	- `FINDCONNECTEDCOMPONENTS <GRAPH>`: Find the number of connected components.

4. **Output:**
	- Results are written to `output.txt`.
	- Each command's execution time (in microseconds) is logged.

5. **Example Workflow:**
	- Place your commands in `commands.txt`.
	- Place any required data files (e.g., for building structures) in the project directory.
	- Run the compiled executable. Check `output.txt` for results.

## File Structure

- `main.cpp`: Command interpreter and program entry point
- `AVLTree.cpp`, `Graph.cpp`, `HashTable.cpp`, `MinHeap.cpp`, `MaxHeap.cpp`: Data structure implementations
- `test1/`, `test2/`, ...: Example input/output and data files
- `CMakeLists.txt`: Build configuration

## Example Command (in `commands.txt`)

```
BUILD AVLTREE avltree.txt
INSERT AVLTREE 42
SEARCH AVLTREE 42
GETSIZE AVLTREE
```

## License
See `LICENSE` for details.
