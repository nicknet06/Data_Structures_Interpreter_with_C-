#ifndef AVLTREE_H
#define AVLTREE_H

/*
  Η κλάση AVLTree ορίζει ένα AVL δέντρο, το οποίο είναι ένα αυτοϊσορροπούμενο δυαδικό δέντρο αναζήτησης.
  Με κάθε εισαγωγή ή διαγραφή, γίνεται έλεγχος και πιθανή περιστροφή των κόμβων, έτσι ώστε το ύψος
  του δέντρου να διατηρείται λογαριθμικό.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
  Η δομή AVLNode αναπαριστά έναν κόμβο του AVL δέντρου.
*/
struct AVLNode {
    int key;            // Κλειδί του κόμβου
    int height;         // Ύψος του κόμβου στο AVL δέντρο
    AVLNode* left;      // Δείκτης στον αριστερό υποδεντρο
    AVLNode* right;     // Δείκτης στον δεξιό υποδεντρο
    AVLNode(int k) {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

/*
  Η κλάση AVLTree χρησιμοποιεί έναν δείκτη στη ρίζα (root) του δέντρου και μεταβλητή size
  που καταμετρά τον αριθμό των κόμβων. Παρέχονται βασικές λειτουργίες όπως insertKey, deleteKey,
  αναζήτηση (search) και εύρεση του ελάχιστου κλειδιού (findMin).
*/
class AVLTree {
private:
    AVLNode* root;                          // Ρίζα του AVL δέντρου
    int size;                               // Πλήθος κόμβων στο δέντρο

    AVLNode* insertNode(AVLNode* node, int key);   // Εισαγωγή νέου κόμβου
    AVLNode* deleteNode(AVLNode* node, int key);   // Διαγραφή υπάρχοντος κόμβου
    AVLNode* rotateLeft(AVLNode* y);               // Περιστροφή προς τα αριστερά
    AVLNode* rotateRight(AVLNode* x);              // Περιστροφή προς τα δεξιά
    int getHeight(AVLNode* node);                  // Βοηθητική συνάρτηση για το ύψος ενός κόμβου
    AVLNode* findMinNode(AVLNode* node);           // Επιστρέφει τον κόμβο με το ελάχιστο κλειδί

public:
    AVLTree();                                     // Κατασκευαστής
    void buildFromFile(const string& filename);    // Δημιουργία του AVL από αρχείο
    int getSize();                                 // Επιστρέφει τον αριθμό κόμβων
    int findMin();                                 // Επιστρέφει το ελάχιστο στοιχείο
    bool search(int key);                          // Αναζήτηση κόμβου με κλειδί key
    void insertKey(int key);                       // Εισαγωγή νέου κόμβου με κλειδί key
    void deleteKey(int key);                       // Διαγραφή κόμβου με κλειδί key
};

#endif