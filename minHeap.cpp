#include "MinHeap.h"

/*
  Η κλάση MinHeap παρέχει λειτουργίες για την οργάνωση ενός σωρού ελάχιστης τιμής.
  Κάθε φορά που εισάγουμε ή αφαιρούμε ένα στοιχείο, εφαρμόζονται οι μέθοδοι heapifyUp ή heapifyDown
  ώστε η ελάχιστη τιμή να βρίσκεται πάντα στο πρώτο στοιχείο του πίνακα.
  Η υλοποίηση βασίζεται σε έναν δυναμικό πίνακα (Vector<int>) που επεκτείνεται αυτόματα όταν χρειαστεί.
*/


MinHeap::MinHeap() {}


MinHeap::~MinHeap() {}

/*
  Η συνάρτηση BuildHeapFromFile λαμβάνει το όνομα ενός αρχείου, ανοίγει το αρχείο
  και διαβάζει ακέραιους αριθμούς. Κάθε αριθμός εισάγεται στον πίνακα και στη συνέχεια
  καλείται η heapifyDown από το μέσο του πίνακα έως την αρχή
  για να διασφαλιστεί η ιδιότητα του ελάχιστου σωρού (bottom-up προσέγγιση).
*/
void MinHeap::BuildHeapFromFile(const std::string& filename) {
    ifstream in;
    in.open(filename, ios::in);
    int num;
    while (in >> num) {
        array.push(num);
    }
    for(int i = array.size()/2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

/*
  Η συνάρτηση insert εισάγει ένα νέο στοιχείο στο τέλος του πίνακα
  και με τη μέθοδο heapifyUp εξασφαλίζει ότι η ιδιότητα του ελάχιστου σωρού
  διατηρείται μετά την εισαγωγή.
*/
void MinHeap::insert(int key) {
    array.push(key);
    heapifyUp(array.size() - 1);
}

/*
  Η getMin επιστρέφει το στοιχείο που βρίσκεται στην κορυφή του σωρού,
  δηλαδή το μικρότερο στοιχείο.
*/
int MinHeap::getMin() {
    return array[0];
}

/*
  Η deleteMin αφαιρεί το στοιχείο με τη μικρότερη τιμή, το ανταλλάσσει με το τελευταίο στοιχείο
  του πίνακα και στη συνέχεια καλεί τη heapifyDown για να αναδιατάξει τον σωρό
  ώστε το καινούργιο ελάχιστο στοιχείο να μετακινηθεί στην κορυφή.
*/
void MinHeap::deleteMin() {
    array.swap(0, array.size() - 1);
    array.pop();
    heapifyDown(0);
}

/*
  Η getSize επιστρέφει το πλήθος των στοιχείων του πίνακα,
  δηλαδή πόσα στοιχεία περιέχει αυτή τη στιγμή ο σωρός.
*/
int MinHeap::getSize() {
    return array.size();
}

/*
  Η heapifyUp εξετάζει έναν κόμβο και το συγκρίνει με τον γονέα του.
  Αν το στοιχείο είναι μικρότερο/μεγαλύτερο από τον γονέα, γίνεται η απαιτούμενη ανταλλαγή
  και προχωράμε προς τα πάνω μέχρι να αποκατασταθεί η ιδιότητα του ελάχιστου σωρού.
*/
void MinHeap::heapifyUp(int index) {
    while (true) {
        int parent = (index - 1) / 2;
        if (array[parent] > array[index]) {
            array.swap(parent, index);
            index = parent;
        } else {
            break;
        }
    }
}

/*
  Η heapifyDown εξετάζει έναν κόμβο και τον συγκρίνει με τα παιδιά του.
  Αν κάποιο από τα παιδιά του είναι μικρότερο/μεγαλύτερο από τον κόμβο, γίνεται η απαιτούμενη ανταλλαγή
  και προχωράμε προς τα κάτω μέχρι να αποκατασταθεί η ιδιότητα του ελάχιστου σωρού.
*/
void MinHeap::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int size = array.size();
        int smallest = index;

        if (leftChild < size && rightChild < size) {
            smallest = array[index] > array[leftChild]
                       ? (array[leftChild] > array[rightChild] ? rightChild : leftChild)
                       : (array[index] > array[rightChild] ? rightChild : index);
        } else if (leftChild < size) {
            smallest = array[index] > array[leftChild] ? leftChild : index;
        } else if (rightChild < size) {
            smallest = array[index] > array[rightChild] ? rightChild : index;
        }

        array.swap(index, smallest);
        if (index == smallest) break;
        index = smallest;
    }
}