/*
    Διερµηνευτής Εντολών ∆οµών ∆εδοµένων
    Υποστηρίζει: Σωρούς ελαχίστων/μεγίστων, AVL δέντρα, Γράφους και Πίνακες Κατακερματισμού.
    Διαβάζει τις εντολές από το αρχείο commands.txt και εκτελεί αντίστοιχες λειτουργίες.
    Τα αποτελέσµατα γράφονται στο αρχείο output.txt.
*/

#include <iostream>
#include <sstream>   // Επιτρέπει τη δημιουργία ρευμάτων δεδομένων από strings (istringstream)
#include <string>
#include <chrono>
#include <fstream>
#include "MinHeap.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "Graph.h"
#include "HashTable.h"


using namespace std;


int main() {
    // Δείκτες για κάθε δομή δεδομένων: δημιουργούνται δυναμικά όταν χρειάζονται
    MinHeap* minHeap = nullptr;
    MaxHeap* maxHeap = nullptr;
    AVLTree* avlTree = nullptr;
    Graph* graph = nullptr;
    HashTable* hashTable = nullptr;

    // Ρεύματα δεδομένων για την είσοδο εντολών και την έξοδο αποτελεσμάτων
    ifstream inputFile("commands.txt");
    ofstream outputFile("output.txt");

    // Έλεγχος για τη δημιουργία του αρχείου εξόδου
    if (!outputFile.is_open()) {
        cerr << "Σφάλμα: Αδυναμία δημιουργίας του output.txt" << endl;
        return 1;
    }

    string line;
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    while (getline(inputFile, line)) {
        // Αν η γραμμή είναι κενή, καταγράφεται ως κενή στο αρχείο εξόδου
        if (line.empty()) {
            outputFile << endl;
            continue;
        }
        outputFile<<line<<" \t-> ";
        // Χρήση istringstream για τη διάσπαση της γραμμής σε εντολή και ορίσματα
        istringstream iss(line);
        string command;
        iss >> command;

        // Εντολή BUILD <DATA_STRUCTURE> <FILENAME>
        // Φορτώνει τη συγκεκριμένη δομή δεδομένων από αρχείο
        start = std::chrono::high_resolution_clock::now();
        if (command == "BUILD") {
            string dataStructure, filename;
            iss >> dataStructure >> filename;

            if (dataStructure == "MINHEAP") {
                if (!minHeap) {
                    minHeap = new MinHeap();
                }
                minHeap->BuildHeapFromFile(filename);
            }
            else if (dataStructure == "MAXHEAP") {
                if (!maxHeap) {
                    maxHeap = new MaxHeap();
                }
                maxHeap->BuildHeapFromFile(filename);
            }
            else if (dataStructure == "AVLTREE") {
                if (!avlTree) {
                    avlTree = new AVLTree();
                }
                avlTree->buildFromFile(filename);
            }
            else if (dataStructure == "GRAPH") {
                if (!graph) {
                    graph = new Graph();
                }
                graph->buildFromFile(filename);
            }
            else if (dataStructure == "HASHTABLE") {
                if (!hashTable) {
                    hashTable = new HashTable();
                }
                hashTable->buildFromFile(filename);
            }
            outputFile<<"\n";
        }

            // Εντολή GETSIZE <DATA_STRUCTURE>
            // Επιστρέφει το πλήθος στοιχείων ή (για Γράφο) κορυφών και ακμών
        else if (command == "GETSIZE") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "MINHEAP") {
                outputFile << (minHeap ? minHeap->getSize() : 0) << endl;
            }
            else if (dataStructure == "MAXHEAP") {
                outputFile << (maxHeap ? maxHeap->getSize() : 0) << endl;
            }
            else if (dataStructure == "AVLTREE") {
                outputFile << (avlTree ? avlTree->getSize() : 0) << endl;
            }
            else if (dataStructure == "GRAPH") {
                if (!graph) {
                    outputFile << "0 0" << endl;
                } else {
                    outputFile << graph->getNumVertices() << " " << graph->getNumEdges() << endl;
                }
            }
            else if (dataStructure == "HASHTABLE") {
                outputFile << (hashTable ? hashTable->getSize() : 0) << endl;
            }
        }

            // Εντολή FINDMIN <MINHEAP/AVLTREE>
            // Επιστρέφει το ελάχιστο στοιχείο από τον MinHeap ή το AVLTree
        else if (command == "FINDMIN") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "MINHEAP") {
                if (!minHeap) {
                    outputFile << "EMPTY" << endl;
                } else {
                    outputFile << minHeap->getMin() << endl;
                }
            }
            else if (dataStructure == "AVLTREE") {
                if (!avlTree) {
                    outputFile << "EMPTY" << endl;
                } else {
                    outputFile << avlTree->findMin() << endl;
                }
            }
        }

            // Εντολή FINDMAX <MAXHEAP>
            // Επιστρέφει το μέγιστο στοιχείο από τον MaxHeap
        else if (command == "FINDMAX") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "MAXHEAP") {
                if (!maxHeap) {
                    outputFile << "EMPTY" << endl;
                } else {
                    outputFile << maxHeap->getMax() << endl;
                }
            }
        }

            // Εντολή SEARCH <DATA_STRUCTURE> <VALUE>
            // Αναζητά ένα στοιχείο σε AVLTree ή HashTable
        else if (command == "SEARCH") {
            string dataStructure;
            int number;
            iss >> dataStructure >> number;

            if (dataStructure == "AVLTREE") {
                if (!avlTree) {
                    outputFile << "FAILURE" << endl;
                } else {
                    outputFile << (avlTree->search(number) ? "SUCCESS" : "FAILURE") << endl;
                }
            }
            else if (dataStructure == "HASHTABLE") {
                if (!hashTable) {
                    outputFile << "FAILURE" << endl;
                } else {
                    outputFile << (hashTable->searchKey(number) ? "SUCCESS" : "FAILURE") << endl;
                }
            }
        }

            // Εντολή INSERT <DATA_STRUCTURE> <VALUE...>
            // Εισάγει ένα νέο στοιχείο στη δομή που καθορίζεται
        else if (command == "INSERT") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "MINHEAP") {
                int number;
                iss >> number;
                if (!minHeap) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    minHeap->insert(number);
                }
            }
            else if (dataStructure == "MAXHEAP") {
                int number;
                iss >> number;
                if (!maxHeap) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    maxHeap->insert(number);
                }
            }
            else if (dataStructure == "AVLTREE") {
                int number;
                iss >> number;
                if (!avlTree) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    avlTree->insertKey(number);
                }
            }
            else if (dataStructure == "HASHTABLE") {
                int number;
                iss >> number;
                if (!hashTable) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    hashTable->insertKey(number);
                }
            }
            else if (dataStructure == "GRAPH") {
                int num1, num2, weight;
                iss >> num1 >> num2 >> weight;
                if (!graph) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    graph->addEdge(num1, num2, weight);
                }
            }
            outputFile<<"\n";
        }

            // Εντολή DELETEMIN <DATA_STRUCTURE>
            // Αφαιρεί το ελάχιστο στοιχείο από MinHeap
        else if (command == "DELETEMIN") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "MINHEAP") {
                if (!minHeap) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    minHeap->deleteMin();
                }
            }
            outputFile<<"\n";
        }

            // Εντολή DELETEMAX <DATA_STRUCTURE>
            // Αφαιρεί το μέγιστο στοιχείο από MaxHeap
        else if (command == "DELETEMAX") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "MAXHEAP") {
                if (!maxHeap) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    maxHeap->deleteMax();
                }
            }
            outputFile<<"\n";
        }

            // Εντολή DELETE <DATA_STRUCTURE> <VALUE...>
            // Διαγράφει συγκεκριμένο στοιχείο από AVLTree, HashTable ή ακμή από Graph
        else if (command == "DELETE") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "AVLTREE") {
                int number;
                iss >> number;
                if (!avlTree) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    avlTree->deleteKey(number);
                }
            }
            else if (dataStructure == "HASHTABLE") {
                int number;
                iss >> number;
                if (!hashTable) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    hashTable->deleteKey(number);
                }
            }
            else if (dataStructure == "GRAPH") {
                int num1, num2;
                iss >> num1 >> num2;
                if (!graph) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    graph->removeEdge(num1, num2);
                }
            }
            outputFile<<"\n";
        }

            // Εντολή COMPUTESHORTESTPATH <DATA_STRUCTURE> <START> <END>
            // Υπολογίζει τη συντομότερη διαδρομή σε Γράφο μεταξύ δύο κορυφών
        else if (command == "COMPUTESHORTESTPATH") {
            string dataStructure;
            int start, end;
            iss >> dataStructure >> start >> end;

            if (dataStructure == "GRAPH") {
                if (!graph) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    int cost = graph->computeShortestPath(start, end);
                    if (cost == -1) {
                        outputFile << "No path found" << endl;
                    } else {
                        outputFile << cost << endl;
                    }
                }
            }
        }

            // Εντολή COMPUTESPANNINGTREE <DATA_STRUCTURE>
            // Υπολογίζει το ελάχιστο spanning tree σε Γράφο και επιστρέφει το συνολικό κόστος
        else if (command == "COMPUTESPANNINGTREE") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "GRAPH") {
                if (!graph) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    int cost = graph->computeSpanningTree();
                    outputFile << cost << endl;
                }
            }
        }

            // Εντολή FINDCONNECTEDCOMPONENTS <DATA_STRUCTURE>
            // Υπολογίζει τον αριθμό συνεκτικών συνιστωσών σε Γράφο
        else if (command == "FINDCONNECTEDCOMPONENTS") {
            string dataStructure;
            iss >> dataStructure;

            if (dataStructure == "GRAPH") {
                if (!graph) {
                    outputFile << "NOT BUILT" << endl;
                } else {
                    int components = graph->findConnectedComponents();
                    outputFile << components << endl;
                }
            }
        }
        stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        outputFile<< "Time taken by function: " << duration.count() << " microseconds" << endl;
    }

    // Απελευθέρωση της δυναμικά δεσμευμένης μνήμης
    if (minHeap)    delete minHeap;
    if (maxHeap)    delete maxHeap;
    if (avlTree)    delete avlTree;
    if (graph)      delete graph;
    if (hashTable)  delete hashTable;

    inputFile.close();
    outputFile.close();

    return 0;
}