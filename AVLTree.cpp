#include "AVLTree.h"
#include "Vector.h"

/*
  Η συνάρτηση max συγκρίνει δύο ακεραίους και επιστρέφει τον μεγαλύτερο
  από τους δύο. Χρησιμοποιείται σε πολλά σημεία του δέντρου AVL για την
  ανανέωση του ύψους των κόμβων.
*/
int max(int a, int b) {
    return a > b ? a : b;
}

/*
  Η συνάρτηση insertNode εισάγει έναν νέο κόμβο με τιμή key στο AVL δέντρο.
  Χρησιμοποιεί μια στοίβα (Vector<AVLNode*>) για να εντοπίσει γρήγορα τους προγόνους, και
  προβαίνει στις περιστροφές όπου χρειάζεται, ώστε να διατηρηθεί η ιδιότητα του AVL.
*/
AVLNode* AVLTree::insertNode(AVLNode* node, int key) {
    if (!node) {
        size++;
        return new AVLNode(key);
    }

    AVLNode* current = node;
    AVLNode* parent = nullptr;
    Vector<AVLNode*> ancestors;

    while (current) {
        parent = current;
        ancestors.push(current);
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return node;
        }
    }

    AVLNode* newNode = new AVLNode(key);
    size++;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    int Dheight;
    for (int i = ancestors.size() - 1; i >= 0; --i) {
        AVLNode* ancestor = ancestors[i];
        ancestor->height = 1 + max(getHeight(ancestor->left), getHeight(ancestor->right));
        Dheight = getHeight(ancestor->left) - getHeight(ancestor->right);

        // Έλεγχος για τις τέσσερις βασικές Παραβιάσεις (LL, RR, LR, RL)
        if (Dheight > 1 && key < ancestor->left->key) {
            // Περιστροφή δεξιά
            if (i > 0) {
                if (ancestors[i - 1]->left == ancestor) ancestors[i - 1]->left = rotateRight(ancestor);
                else ancestors[i - 1]->right = rotateRight(ancestor);
            } else {
                node = rotateRight(ancestor);
            }
        }
        else if (Dheight < -1 && key > ancestor->right->key) {
            // Περιστροφή αριστερά
            if (i > 0) {
                if (ancestors[i - 1]->right == ancestor) ancestors[i - 1]->right = rotateLeft(ancestor);
                else ancestors[i - 1]->left = rotateLeft(ancestor);
            } else {
                node = rotateLeft(ancestor);
            }
        }
        else if (Dheight > 1 && key > ancestor->left->key) {
            // Αριστερά περιστροφή  στο αριστερό παιδί και μετά δεξιά στον πρόγονο
            ancestor->left = rotateLeft(ancestor->left);
            if (i > 0) {
                if (ancestors[i - 1]->left == ancestor) ancestors[i - 1]->left = rotateRight(ancestor);
                else ancestors[i - 1]->right = rotateRight(ancestor);
            } else {
                node = rotateRight(ancestor);
            }
        }
        else if (Dheight < -1 && key < ancestor->right->key) {
            // Δεξιά περιστροφή στο δεξί παιδί και μετά αριστερά στον πρόγονο
            ancestor->right = rotateRight(ancestor->right);
            if (i > 0) {
                if (ancestors[i - 1]->right == ancestor) ancestors[i - 1]->right = rotateLeft(ancestor);
                else ancestors[i - 1]->left = rotateLeft(ancestor);
            } else {
                node = rotateLeft(ancestor);
            }
        }
    }

    return node;
}

/*
  Η συνάρτηση deleteNode διαγράφει από το δέντρο τον κόμβο με τιμή key, αν υπάρχει.
  Αν διαπιστωθεί κάποια παράβαση της ιδιότητας AVL σε κάποιον από τους προγονούς του
  διαγραφομένου κόμβου προβαίνει στις κατάλληλες περιστροφες (LL,LR,RL,RR).
*/
AVLNode* AVLTree::deleteNode(AVLNode* node, int key) {
    if (!node) return node;

    Vector<AVLNode*> ancestors;
    AVLNode* current = node;
    AVLNode* parent = nullptr;

    // Εντοπισμός κόμβου προς διαγραφή
    while (current && current->key != key) {
        parent = current;
        ancestors.push(current);
        if (key < current->key) current = current->left;
        else current = current->right;
    }
    if (!current) return node;

    // Αν ο κόμβος έχει δύο παιδιά, ανταλλάσσει με το ελάχιστο
    if (current->left && current->right) {
        AVLNode* minNode = current->right;
        AVLNode* minParent = current;
        ancestors.push(current);
        while (minNode->left) {
            minParent = minNode;
            ancestors.push(minNode);
            minNode = minNode->left;
        }
        current->key = minNode->key;
        current = minNode;
        parent = minParent;
    }

    // Αποσύνδεση και διαγραφή του κόμβου
    AVLNode* child = current->left ? current->left : current->right;
    if (!parent) {
        node = child;
    } else {
        if (parent->left == current) parent->left = child;
        else parent->right = child;
    }
    delete current;
    size--;

    // Αποκατάσταση AVL ιδιότητας για τους προγόνους
    int Dheight;
    for (int i = ancestors.size() - 1; i >= 0; --i) {
        AVLNode* ancestor = ancestors[i];
        ancestor->height = 1 + max(getHeight(ancestor->left), getHeight(ancestor->right));
        Dheight = getHeight(ancestor->left) - getHeight(ancestor->right);

        if (Dheight > 1 && key < ancestor->left->key) {
            if (i > 0) {
                if (ancestors[i - 1]->left == ancestor) ancestors[i - 1]->left = rotateRight(ancestor);
                else ancestors[i - 1]->right = rotateRight(ancestor);
            } else {
                node = rotateRight(ancestor);
            }
        }
        else if (Dheight < -1 && key > ancestor->right->key) {
            if (i > 0) {
                if (ancestors[i - 1]->right == ancestor) ancestors[i - 1]->right = rotateLeft(ancestor);
                else ancestors[i - 1]->left = rotateLeft(ancestor);
            } else {
                node = rotateLeft(ancestor);
            }
        }
        else if (Dheight > 1 && key > ancestor->left->key) {
            ancestor->left = rotateLeft(ancestor->left);
            if (i > 0) {
                if (ancestors[i - 1]->left == ancestor) ancestors[i - 1]->left = rotateRight(ancestor);
                else ancestors[i - 1]->right = rotateRight(ancestor);
            } else {
                node = rotateRight(ancestor);
            }
        }
        else if (Dheight < -1 && key < ancestor->right->key) {
            ancestor->right = rotateRight(ancestor->right);
            if (i > 0) {
                if (ancestors[i - 1]->right == ancestor) ancestors[i - 1]->right = rotateLeft(ancestor);
                else ancestors[i - 1]->left = rotateLeft(ancestor);
            } else {
                node = rotateLeft(ancestor);
            }
        }
    }

    return node;
}

/*
  Η συνάρτηση rotateLeft εκτελεί μια απλή περιστροφή προς τα αριστερά
  σε έναν κόμβο y, επανατοποθετώντας κατάλληλα τους δεσμούς για να επανέλθει
  η ισορροπία του δέντρου.
*/
AVLNode* AVLTree::rotateLeft(AVLNode* y) {
    AVLNode* x = y->right;
    y->right = x->left;
    x->left = y;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

/*
  Η συνάρτηση rotateRight εκτελεί μια απλή περιστροφή προς τα δεξιά
  σε έναν κόμβο x, επανατοποθετώντας κατάλληλα τους δεσμούς για να επανέλθει
  η ισορροπία του δέντρου.
*/
AVLNode* AVLTree::rotateRight(AVLNode* x) {
    AVLNode* y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

/*
  Η συνάρτηση getHeight επιστρέφει το ύψος που έχει αποθηκευτεί σε έναν κόμβο.
  Αν ο κόμβος είναι nullptr, επιστρέφει 0.
*/
int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

/*
  Η συνάρτηση findMinNode αναζητά και επιστρέφει τον κόμβο που περιέχει
  το ελάχιστο κλειδί σε ένα υποδέντρο. Αν το υποδέντρο είναι κενό, επιστρέφει nullptr.
*/
AVLNode* AVLTree::findMinNode(AVLNode* node) {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}

/*
  Στον κατασκευαστή AVLTree, αρχικοποιείται η ρίζα
  και μεταβλητή size (πλήθος κόμβων) με την τιμή 0.
*/
AVLTree::AVLTree() {
    root = nullptr;
    size = 0;
}

/*
  Η συνάρτηση buildFromFile διαβάζει από ένα αρχείο ακέραιους αριθμούς
  και τους εισάγει διαδοχικά στο AVL δέντρο. Χρησιμοποιεί τη συνάρτηση insertKey.
*/
void AVLTree::buildFromFile(const string &filename) {
    ifstream in;
    in.open(filename, ios::in);
    int num;
    in >> num;
    insertKey(num);
    while (in >> num) {
        insertKey(num);
    }
}

/*
  Η getSize επιστρέφει το τρέχον πλήθος των κόμβων που υπάρχουν στο AVL δέντρο.
*/
int AVLTree::getSize() {
    return size;
}

/*
  Η findMin χρησιμοποιεί τη συνάρτηση findMinNode για να εντοπίσει τον κόμβο
  με το ελάχιστο κλειδί και επιστρέφει την τιμή του.
*/
int AVLTree::findMin() {
    return findMinNode(root)->key;
}

/*
  Η συνάρτηση search αναζητά ένα κλειδί στο AVL δέντρο. Επιστρέφει true
  αν το κλειδί βρεθεί, αλλιως false.
*/
bool AVLTree::search(int key) {
    AVLNode* current = root;
    while (current) {
        if (key == current->key) return true;
        if (key < current->key) current = current->left;
        else current = current->right;
    }
    return false;
}

/*
  Η insertKey καλεί την insertNode για να εισαγάγει νέο κόμβο με κλειδί key
  στο AVL δέντρο.
*/
void AVLTree::insertKey(int key) {
    root = insertNode(root, key);
}

/*
  Η deleteKey καλεί τη deleteNode για να διαγράψει τον κόμβο με κλειδί key.
*/
void AVLTree::deleteKey(int key) {
    root = deleteNode(root, key);
}