#include "HashtablePairs.h"
#include <fstream>
#include <iostream>

/*
  Η κλάση GraphHashTable διατηρεί μια δομή κατακερματισμού για την αποθήκευση κορυφών ενός γράφου. 
  Κάθε καταχώρηση περιέχει ένα αντικείμενο Pair<Edge> που περιλαμβάνει το αναγνωριστικό της κορυφής (vertexId)
  και μια λίστα από Edge αντικείμενα, τα οποία αντιπροσωπεύουν τις ακμές που ξεκινούν από τη συγκεκριμένη κορυφή.
*/

//Ο constructor GraphHashTable αρχικοποιεί την χωρητικότητα (capacity) σε 100, το size σε 0 
GraphHashTable::GraphHashTable(int cap) {
    capacity = 100; 
    size = 0; 
    table.resize(capacity);
}

/*
  Η συνάρτηση hashFunction δέχεται σαν είσοδο  ένα ακέραιο κλειδί (vertexId), 
  και επιστρέφει το vertexId % capacity ως θέση στον πίνακα (table). 
*/
int GraphHashTable::hashFunction(int key) {
    return key % capacity;   
}

/*
  Η getVertexEdges επιστρέφει μια αναφορά σε LinkedList<Edge> για την κορυφή με αναγνωριστικό vertexId.
  - Αν η κορυφή υπάρχει επιστρέφουμε το αντικείμενο της λίστας ακμών (edges).
  - Αν η κορυφή δεν βρεθεί, δημιουργείται αμέσως μέσω addVertex, και έπειτα επιστρέφεται η αντίστοιχη λίστα ακμών.
*/
LinkedList<Edge>* GraphHashTable::getVertexEdges(int vertexId) {
    int idx = hashFunction(vertexId);
    LinkedList<Pair<Edge>>::Node* current = table[idx].getHead();
    while (current) {
        if (current->data.id == vertexId) {
            return &(current->data.edges); 
        }
        current = current->next;  
    }

    // Αν η κορυφή δεν υπάρχει, δημιουργούμε και την αναζητούμε
    addVertex(vertexId);

    current = table[idx].getHead();
    while (current) {
        if (current->data.id == vertexId) {
            return &(current->data.edges);
        }
        current = current->next; 
    }

    return nullptr;
}

/*
  Η hasVertex ελέγχει αν το vertexId υπάρχει μεταξύ των καταχωρήσεων της δομής κατακερματισμού.
  - Με χρήση της hashFunction, πηγαίνει στην αντίστοιχη λίστα και ελέγχει αν βρίσκει το vertexId.
  - Αν το βρει, επιστρέφει true, διαφορετικά false.
*/
bool GraphHashTable::hasVertex(int vertexId) {
    int idx = hashFunction(vertexId);
    LinkedList<Pair<Edge>>::Node* current = table[idx].getHead();
    while (current) {
        if (current->data.id == vertexId) {
            return true;
        }
        current = current->next;
    }
    return false;
}

/*
  Η addVertex εισάγει μια νέα κορυφή στη δομή κεκερματισμού, εφόσον δεν υπάρχει ήδη.
*/
void GraphHashTable::addVertex(int vertexId) {
    if (!hasVertex(vertexId)) {
        int idx = hashFunction(vertexId);
        Pair<Edge> newVertex(vertexId);
        table[idx].push_back(newVertex);
        size++;
    }
}

/*
  Η removeVertex αφαιρεί μια κορυφή από τη δομή κατακερματισμού, εφόσον υπάρχει..
*/
void GraphHashTable::removeVertex(int vertexId) {
    int idx = hashFunction(vertexId);
    Pair<Edge> temp(vertexId); 
    if (table[idx].remove(temp)) {
        size--;
    }
}

/*
  Η getAllVertices επιστρέφει ένα Vector<int> με όλες τις κορυφές (vertexIds) που υπάρχουν
  στη δομή.
*/
Vector<int> GraphHashTable::getAllVertices() const {
    Vector<int> vertices;
    for (int i = 0; i < capacity; i++) {
        LinkedList<Pair<Edge>>::Node* current = table[i].getHead();
        while (current) {
            vertices.push(current->data.id);
            current = current->next;
        }
    }
    return vertices;
}

/*
  Η getVertexCount επιστρέφει το μέγεθος (size), δηλαδή τον αριθμό κορυφών
  που περιέχει η δομή κατακερματισμού.
*/
int GraphHashTable::getVertexCount() const {
    return size; 
}
