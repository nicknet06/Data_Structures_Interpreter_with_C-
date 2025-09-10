#ifndef HASHTABLE_H
#define HASHTABLE_H

/*
  Η κλάση HashTable υλοποιεί έναν κατακερματισμό για την αποθήκευση και αναζήτηση ακεραίων.
  Χρησιμοποιεί ένα δυναμικό πίνακα (Vector<LinkedList<int>>) όπου κάθε θέση λειτουργεί ως
  λίστα που περιέχει τα στοιχεία με το ίδιο hash. Η μέθοδος hashFunction
  καθορίζει το index της θέσης στον πίνακα για κάθε κλειδί.
*/

#include "Vector.h"
#include "LinkedList.h"
#include <string>


class HashTable {
private:
    Vector<LinkedList<int>> table;    // Πίνακας λιστών
    int capacity;                     // Μέγιστη χωρητικότητα
    int size;                         // Τρέχων αριθμός στοιχείων

    /*
      Η συνάρτηση hashFunction επιστρέφει τον δείκτη (hash index) για ένα δεδομένο κλειδί (key).
      Συνήθως ορίζεται ως key % capacity.
    */
    int hashFunction(int key);

public:
    /*
      Ο κατασκευαστής HashTable αρχικοποιεί τον πίνακα με μέγεθος cap (προεπιλογή: 100).
      Αρχικά, κάθε LinkedList στον πίνακα είναι κενή και το μέγεθος (size) της δομής ορίζεται στο 0.
    */
    HashTable(int cap = 100);

    /*
      Η buildFromFile διαβάζει ακέραιους από ένα αρχείο (filename) και τους εισάγει
      διαδοχικά στον πίνακα κατακερματισμού (με insertKey).
    */
    void buildFromFile(const std::string&  filename);

    /*
      Η getSize επιστρέφει τον τρέχοντα αριθμό των στοιχείων του πίνακα (size).
    */
    int getSize() const;

    /*
      Η searchKey αναζητά ένα στοιχείο (key) στον πίνακα κατακερματισμού κι επιστρέφει
      true αν βρεθεί, διαφορετικά false.
    */
    bool searchKey(int key);

    /*
      Η insertKey εισάγει ένα νέο κλειδί στον πίνακα, τοποθετώντας το στην κατάλληλη λίστα
      σύμφωνα με την τιμή του hashFunction. Αν το στοιχείο υπάρχει ήδη, η υλοποίηση δεν το εισάγει ξανά.
    */
    void insertKey(int key);

    /*
      Η deleteKey διαγράφει ένα στοιχείο (key) από τον πίνακα, αν υπάρχει.
    */
    void deleteKey(int key);

};

#endif