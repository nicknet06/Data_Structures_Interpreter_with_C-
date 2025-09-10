#include "HashTable.h"
#include <fstream>
#include <iostream>

/*
  Ο κατασκευαστής HashTable αρχικοποιεί τη μεταβλητή capacity σε 100,
  το size σε 0, και στη συνέχεια αλλάζει το μέγεθος του table
  (Vector<LinkedList<int>>) στη συγκεκριμένη χωρητικότητα.
*/
HashTable::HashTable(int cap) {
    capacity = 100;
    size = 0;
    table.resize(capacity);
}

/*
  Η συνάρτηση hashFunction υπολογίζει το index για ένα κλειδί (key)
  εκτελώντας πράξη modulus (% capacity).
*/
int HashTable::hashFunction(int key) {
    return key % capacity;
}

/*
  Η buildFromFile καθαρίζει το table και
  στη συνέχεια, διαβάζει ακεραίους από ένα αρχείο
  και καλεί τη συνάρτηση insertKey για καθέναν από αυτούς.
*/
void HashTable::buildFromFile(const std::string&  filename) {
    table.clear();
    size = 0;
    table.resize(capacity);

    std::ifstream ifs(filename);


    int val;
    while (ifs >> val) {
        insertKey(val);
    }
    ifs.close();
}

/*
  Η getSize επιστρέφει το τρέχον μέγεθος της δομής κατακερματισμού (size),
  δηλαδή τον αριθμό των στοιχείων που περιέχονται στον πίνακα κατακερματισμού.
*/
int HashTable::getSize() const {
    return size;
}

/*
  Η searchKey ελέγχει αν ένα κλειδί υπάρχει στον πίνακα κατακερματισμού.
  Υπολογίζει το index μέσω της hashFunction, και κατόπιν καλεί τη μέθοδο contains
  στην αντίστοιχη λίστα (LinkedList<int>) έτσι ώστε να διαπιστώσει αν περιέχει το key.
*/
bool HashTable::searchKey(int key) {
    int idx = hashFunction(key);
    return table[idx].contains(key);
}

/*
  Η insertKey εισάγει ένα νέο κλειδί στον πίνακα, an δεν υπάρχει ήδη.
  Υπολογίζει το hash και εισάγει το key στην κατάλληλη λίστα.
  Αυξάνει το size
*/
void HashTable::insertKey(int key) {
    if (!searchKey(key)) {
        int idx = hashFunction(key);
        table[idx].push_back(key);
        size++;
    }
}

/*
  Η deleteKey διαγράφει ένα κλειδί από τον πίνακα κατακερματισμού, υπολογίζοντας
  το index του μέσω της hashFunction και καλώντας τη remove της αντίστοιχης λίστας
  (LinkedList<int>) για να αφαιρέσει το key.
*/
void HashTable::deleteKey(int key) {
    int idx = hashFunction(key);
    table[idx].remove(key);
}