#ifndef GRAPH_H
#define GRAPH_H


#include "Vector.h"
#include "LinkedList.h"
#include "HashtablePairs.h"

#include <iostream>
#include <fstream>
#include <string>
#include <climits> // Χρησιμοποιείται για το INT_MAX(το απειρο), όταν δεν υπάρχει ορισμένη τιμή βάρους

using namespace std;


class Graph {
private:
    // Χρησιμοποιούμε την GraphHashTable για να αποθηκεύσουμε τις κορυφές και τις ακμες
    GraphHashTable vertices;  // Σε κάθε καταχώρηση αποθηκεύεται μια λίστα ακμών (destination/weight)
    int numEdges;             // Συνολικό πλήθος ακμών στο γράφημα

public:
    /*
      O default constructor αρχικοποιεί τον πίνακα κορυφών (μέσω της GraphHashTable)
      και ρυθμίζει τις διάφορες μεταβλητές (π.χ. numEdges) σε αρχικές τιμές.
    */
    Graph();

    /*
      Ο destructor καταστρέφει τα δυναμικά στοιχεία (κόμβους/κατακερματισμούς).
      Υλοποιείται εδώ κενά ή με διαγραφή δομών, τα οποία απελευθερώνουν μνήμη.
    */
    ~Graph();

    /*
      Η buildFromFile διαβάζει δεδομένα από ένα αρχείο (filename) και προσθέτει ακμές
      καλώντας την συνάρτηση addEdge. Θεωρείται ότι το αρχείο περιέχει γραμμές της μορφής:
      source destination weight
      αναπαριστώντας μια ακμή για κάθε σειρά.
    */
    void buildFromFile(const string& filename);

    /*
      Η addEdge προσθέτει στο γράφημα μια ακμή από μια κορυφή source σε μια κορυφή destination,
      με συγκεκριμένο βάρος. Αν κάποια από τις κορυφές δεν υπάρχει, δημιουργείται αυτόματα (addVertex).
    */
    void addEdge(int source, int destination, int weight);

    /*
      Η hasEdge ελέγχει αν υπάρχει ήδη μια ακμή ανάμεσα σε δύο κορυφές (source, destination).
      Επιστρέφει true αν βρεθεί, αλλιώς false.
    */
    bool hasEdge(int source, int destination);

    /*
      Η getEdgeWeight επιστρέφει το βάρος μιας ακμής ανάμεσα σε δύο κορυφές.
    */
    int getEdgeWeight(int source, int destination);

    /*
      Η removeEdge αφαιρεί την ακμή μεταξύ δύο κορυφών, αν αυτή υπάρχει.
      Το πλήθος ακμών (numEdges) ενημερώνεται αναλόγως.
    */
    void removeEdge(int source, int destination);

    /*
      Η getNumVertices επιστρέφει τον αριθμό των κορυφών που έχουν καταχωρηθεί
      έως τώρα στον γράφο.
    */
    int getNumVertices() const;

    /*
      Η getNumEdges επιστρέφει τον τρέχοντα αριθμό ακμών που έχουν αποθηκευτεί
      στον γράφο (numEdges).
    */
    int getNumEdges() const;

    /*
      Η getNeighbors επιστρέφει ένα Vector<int> που περιέχει τις γειτονικές κορυφές
      μιας συγκεκριμένης κορυφής (vertex). Αν η κορυφή δεν υπάρχει, επιστρέφεται κενός πίνακας.
    */
    Vector<int> getNeighbors(int vertex);

    /*
      Η addVertex προσθέτει μια νέα κορυφή στο γράφημα, ενημερώνοντας
      την εσωτερική δομή GraphHashTable εφόσον δεν υπάρχει ήδη.
    */
    void addVertex(int vertex);

    /*
      Η computeShortestPath υλοποιεί έναν αλγόριθμο υπολογισμού της συντομότερης διαδρομής
      (Dijkstra) μεταξύ δύο δοσμένων κορυφών (source, destination). Επιστρέφει το
      ελάχιστο κόστος διαδρομής ή -1 αν δεν υπάρχει διαδρομή.
    */
    int computeShortestPath(int source, int destination);

    /*
      Η computeSpanningTree υλοποιεί έναν αλγόριθμο κατασκευής ενός Minimum spanning tree.
      Χρεισιμοποιόντας την μέ του Prim θοδο
    */
    int computeSpanningTree();

    /*
      Η findConnectedComponents Υπολογίζει το πλήθος των συνεκτικών συνιστωσών του γραφήματος και επιστρέφει τον
        αριθμό αυτόν
    */
    int findConnectedComponents();
};

#endif