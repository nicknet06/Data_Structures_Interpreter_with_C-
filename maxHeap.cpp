#include "MaxHeap.h"

/*
  Η κλάση MaxHeap παρέχει λειτουργίες για την οργάνωση ενός σωρού μέγιστης τιμής.
  Κάθε φορά που εισάγουμε ή αφαιρούμε ένα στοιχείο, εφαρμόζονται οι μέθοδοι heapifyUp ή heapifyDown
  ώστε η μέγιστη τιμή να βρίσκεται πάντα στο πρώτο στοιχείο του πίνακα.
  Η υλοποίηση βασίζεται σε έναν δυναμικό πίνακα (Vector<int>) που επεκτείνεται αυτόματα όταν χρειαστεί.
*/

MaxHeap::MaxHeap() {
}


MaxHeap::~MaxHeap() {
}

/*
  Η συνάρτηση BuildHeapFromFile λαμβάνει ένα όνομα αρχείου, ανοίγει το αρχείο
  και διαβάζει ακέραιους αριθμούς. Στη συνέχεια, τους εισάγει όλους στον πίνακα,
  και τέλος καλεί τη μέθοδο heapifyDown από το μέσο του πίνακα μέχρι την αρχή
  για να διαμορφωθεί σωστά ο MaxHeap. Η τεχνική αυτή ονομάζεται bottom-up εχει
  πολυπλοκότητα Ο(Ν).
*/
void MaxHeap::BuildHeapFromFile(const std::string& filename) {
    ifstream in;
    in.open(filename,ios::in);
    int num;
    while(in >> num) {
        array.push(num);
    }
    for(int i = array.size()/2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

/*
  Η συνάρτηση insert εισάγει ένα νέο στοιχείο στο τέλος του πίνακα
  και στη συνέχεια με τη heapifyUp διασφαλίζεται ότι η ιδιότητα του σωρού
  ικανοποιήται.
*/
void MaxHeap::insert(int key) {
    array.push(key);
    heapifyUp(array.size() - 1);
}

/*
  Η getMax επιστρέφει το στοιχείο που βρίσκεται στην κορυφή του σωρού.
*/
int MaxHeap::getMax() {
    return array[0];
}

/*
  Η deleteMax αφαιρεί το στοιχείο με τη μεγαλύτερη τιμή, το ανταλλάσσει με το τελευταίο στοιχείο
  του πίνακα. Έπειτα καλεί τη heapifyDown για να διατηρήσει την ιδιότητα του σωρού από την κορυφή προς τα κάτω.
*/
void MaxHeap::deleteMax() {
    array.swap(0, array.size() - 1);
    array.pop();
    heapifyDown(0);
}

/*
  Η getSize απλώς επιστρέφει το τρέχον πλήθος των στοιχείων που έχουν αποθηκευτεί
  μέσα στον σωρό.
*/
int MaxHeap::getSize() {
    return array.size();
}

/*
  Η heapifyUp μετακινεί το στοιχείο που προστέθηκε πρόσφατα προς την κορυφή, αν διαπιστωθεί
  ότι είναι μεγαλύτερο από τον γονέα του. Έτσι διασφαλίζουμε ότι η υψηλότερη τιμή
  σταδιακά κινείται προς τη ρίζα του σωρού.
*/
void MaxHeap::heapifyUp(int index) {
    while (true) {
        int parent = (index - 1) / 2;
        if (array[parent] < array[index]) {
            array.swap(parent, index);
            index = parent;
        } else {
            break;
        }
    }
}

/*
  Η heapifyDown μετακινεί ένα στοιχείο προς τα κάτω εφόσον είναι μικρότερο από κάποιο από τα παιδιά του.
  Στο τέλος αυτής της διαδικασίας, το στοιχείο που είχε αρχικά ταξινομηθεί λάθος τοποθετείται
  στη σωστή θέση, και η μέγιστη τιμή επανέρχεται στην κορυφή.
*/
void MaxHeap::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int size = array.size();
        int largest = index;

        if (leftChild < size && rightChild < size) {
            largest = array[index] < array[leftChild]
                      ? (array[leftChild] < array[rightChild] ? rightChild : leftChild)
                      : (array[index] < array[rightChild] ? rightChild : index);
        } else if (leftChild < size) {
            largest = array[index] < array[leftChild] ? leftChild : index;
        } else if (rightChild < size) {
            largest = array[index] < array[rightChild] ? rightChild : index;
        }

        array.swap(index, largest);
        if (index == largest) break;
        index = largest;
    }
}
