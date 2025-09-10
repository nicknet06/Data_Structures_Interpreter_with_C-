#ifndef HASHTABLEPAIRS_H
#define HASHTABLEPAIRS_H

#include "Vector.h"
#include "LinkedList.h"

/*
  Η δομή Edge αποτελεί μια απλή δομή δεδομένων που αποθηκεύει τις πληροφορίες για μια ακμή γράφου:
  destination (προορισμός της ακμής) και weight (βάρος ακμής).
  Παρέχονται constructor κι ένα operator==, ώστε να είναι δυνατή η σύγκριση δύο Edge αντικειμένων.
*/
struct Edge {
    int destination = 0;
    int weight = 0;

    Edge() {}
    Edge(int dest, int w) {
        destination = dest;
        weight = w;
    }

    bool operator==(const Edge& other) const {
        return destination == other.destination && weight == other.weight;
    }
};

/*
  Το template Pair<T> αποθηκεύει ένα αναγνωριστικό κορυφής (id) και μια συνδεδεμένη λίστα (edges)
  που περιέχει αντικείμενα τύπου T. Εδώ T είναι τύπος ακμής, οπότε αποθηκεύουμε τη λίστα ακμών μιας κορυφής.
*/
template<typename T>
class Pair {
public:
    int id;
    LinkedList<T> edges;

    Pair() : id(0) {}
    Pair(int vertex_id) : id(vertex_id) {}

    bool operator==(const Pair<T>& right) const {
        return this->id == right.id;
    }
};

/*
  Η κλάση GraphHashTable υλοποιεί έναν specialized πίνακα κατακερματισμού για την αποθήκευση
  κορυφών (με τα αναγνωριστικά τους) και των σχετικών λιστών ακμών (edges).
  - table: Ένας Vector που κρατάει συνδεδεμένες λίστες (LinkedList<Pair<Edge>>),
           όπου κάθε κόμβος κρατάει info για μια κορυφή και τις ακμές της.
  - capacity: Μέγεθος του πίνακα κατακερματισμού (πλήθος "ομαδών").
  - size: Συνολικός αριθμός κορυφών που έχουν εισαχθεί.
  - hashFunction: Η συνάρτηση κατακερματισμού που καθορίζει σε ποια λίστα θα μπεί μια κορυφή.
*/
class GraphHashTable {
private:
    Vector<LinkedList<Pair<Edge>>> table;
    int capacity;
    int size;
    int hashFunction(int key);

public:
    // Δημιουργεί τη δομή με προεπιλεγμένη χωρητικότητα 100
    GraphHashTable(int cap = 100);

    // Επιστρέφει τη λίστα ακμών για την κορυφή vertexId
    LinkedList<Edge>* getVertexEdges(int vertexId);

    // Ελέγχει αν η κορυφή vertexId υπάρχει
    bool hasVertex(int vertexId);

    // Προσθέτει μια νέα κορυφή αν δεν υπάρχει ήδη
    void addVertex(int vertexId);

    // Αφαιρεί μια κορυφή και όλες τις ακμές της
    void removeVertex(int vertexId);

    // Επιστρέφει όλες τις κορυφές
    Vector<int> getAllVertices() const;

    // Επιστρέφει το πλήθος των κορυφών (size)
    int getVertexCount() const;

};

#endif