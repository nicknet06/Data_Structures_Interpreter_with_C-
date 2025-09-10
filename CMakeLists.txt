cmake_minimum_required(VERSION 3.16)
project(Semaster)

set(CMAKE_CXX_STANDARD 20)

add_executable(semaster main.cpp
        MinHeap.h
        Vector.h
        minHeap.cpp
        AVLTree.h
        AVLTree.cpp
        HashTable.h
        HashTable.cpp
        HashtablePairs.h
        HashtablePairs.cpp
        LinkedList.h
        Graph.h
        Graph.cpp
        maxHeap.cpp)
