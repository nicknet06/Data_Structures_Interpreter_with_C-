#include "Graph.h"


Graph::Graph() {
    numEdges = 0;
}

Graph::~Graph() {
}

void Graph::buildFromFile(const string& filename) {
    ifstream file(filename);
    int source, destination, weight;
    while (file >> source >> destination >> weight) {
        addEdge(source, destination, weight);
    }
    file.close();
}

void Graph::addVertex(int vertex) {
    // Προσθέτουμε μια νέα κορυφή, αν δεν υπάρχει ήδη, στην εσωτερική δομή κατακερματισμού
    vertices.addVertex(vertex);
}

void Graph::addEdge(int source, int destination, int weight) {
    /*
      Προσθέτει μία ακμή (source->destination) και άλλη μία αντίστροφη (destination->source).
      Αν η ακμή υπάρχει ήδη, απλώς δεν την προσθέτει ξανά. Στη συνέχεια, αυξάνει το numEdges +1.
    */
    if (!hasEdge(source, destination)) {
        LinkedList<Edge>* srcEdges = vertices.getVertexEdges(source);
        LinkedList<Edge>* destEdges = vertices.getVertexEdges(destination);

        srcEdges->push_back(Edge(destination, weight));
        destEdges->push_back(Edge(source, weight));
        numEdges++;
    }
}

bool Graph::hasEdge(int source, int destination) {

      //Ψάχνουμε μέσα στη λίστα ακμών (srcEdges) να βρούμε αν υπάρχει ακμή προς το destination.

    if (!vertices.hasVertex(source)) return false;

    LinkedList<Edge>* srcEdges = vertices.getVertexEdges(source);
    LinkedList<Edge>::Node* head = srcEdges->getHead();
    while (head) {
        if (head->data.destination == destination) {
            return true;
        }
        head = head->next;
    }
    return false;
}

int Graph::getEdgeWeight(int source, int destination) {

     // Επιστρέφει το βάρος της ακμής (source->destination) ή -1
     // αν δεν υπάρχει τέτοια ακμή
    if (!vertices.hasVertex(source)) return -1;

    LinkedList<Edge>* srcEdges = vertices.getVertexEdges(source);
    LinkedList<Edge>::Node* head = srcEdges->getHead();
    while (head) {
        if (head->data.destination == destination) {
            return head->data.weight;
        }
        head = head->next;
    }
    return -1;
}

void Graph::removeEdge(int source, int destination) {
    /*
      Αν υπάρχει ακμή ανάμεσα στο source και το destination,
      την αφαιρούμε και από τις δύο αντίστοιχες λίστες ακμών κι ενημερώνουμε το numEdges.
    */
    if (hasEdge(source, destination)) {
        LinkedList<Edge>* srcEdges = vertices.getVertexEdges(source);
        LinkedList<Edge>::Node* head = srcEdges->getHead();
        while (head) {
            if (head->data.destination == destination) {
                srcEdges->remove(head->data);
                break;
            }
            head = head->next;
        }

        LinkedList<Edge>* destEdges = vertices.getVertexEdges(destination);
        head = destEdges->getHead();
        while (head) {
            if (head->data.destination == source) {
                destEdges->remove(head->data);
                break;
            }
            head = head->next;
        }
        numEdges--;
    }
}

int Graph::getNumVertices() const {
    // Επιστρέφει το πλήθος των κορυφών που υπάρχουν στον γράφο
    return vertices.getVertexCount();
}

int Graph::getNumEdges() const {
    // Επιστρέφει τον αριθμό των ακμών (numEdges) που υπάρχουν στον γράφο
    return numEdges;
}

Vector<int> Graph::getNeighbors(int vertex) {
    /*
      Επιστρέφει όλους τους γείτονες μίας κορυφής, δηλαδή όλες τις κορυφές
      που συνδέονται απευθείας με αυτήν. Αν η κορυφή δεν υπάρχει, επιστρέφουμε
      έναν κενό Vector<int>.
    */
    Vector<int> neighbors;

    if (vertices.hasVertex(vertex)) {
        LinkedList<Edge>* edges = vertices.getVertexEdges(vertex);
        LinkedList<Edge>::Node* head = edges->getHead();
        while (head) {
            neighbors.push(head->data.destination);
            head = head->next;
        }
    }

    return neighbors;
}

int Graph::computeShortestPath(int source, int destination) {
    /*
      Υλοποίηση του αλγορίθμου Dijkstra για τον υπολογισμό της "αυντομότερης" διαδρομής
      μεταξύ δύο κορυφών. Επιστρέφει το κόστος αν υπάρχει
      διαδρομή, αλλιώς -1.
    */
    if (!vertices.hasVertex(source) || !vertices.hasVertex(destination)) return -1;

    // Περνουμε όλες τις κορυφές.
    Vector<int> allVertices = vertices.getAllVertices();
    int numVertices = allVertices.size();

    Vector<int> distance;
    Vector<bool> visited;
    distance.resize(numVertices);
    visited.resize(numVertices);

    // Βρίσκουμε το index της κορυφής source και της destination στον πίνακα allVertices
    int srcIndex = -1, destIndex = -1;
    for (int i = 0; i < numVertices; i++) {
        if (allVertices[i] == source) srcIndex = i;
        if (allVertices[i] == destination) destIndex = i;
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    // το μειον ενα σημαινει οτι δεν βρεθηκε
    if (srcIndex == -1 || destIndex == -1) return -1;

    distance[srcIndex] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        // Βρίσκουμε την κορυφή με τη μικρότερη απόσταση προς το παρόν, που δεν έχει επισκεφθεί ακόμα
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && distance[v] <= minDist) {
                minDist = distance[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break; // Δεν υπάρχουν περισσότερες προσβάσιμες κορυφές

        visited[minIndex] = true;

        // Επικαιροποιούμε τις αποστάσεις των γειτονικών κορυφών
        LinkedList<Edge>* edges = vertices.getVertexEdges(allVertices[minIndex]);
        LinkedList<Edge>::Node* head = edges->getHead();
        while (head) {
            // Βρίσκουμε το index της γειτονικής κορυφής
            int neighborIndex = -1;
            for (int i = 0; i < numVertices; i++) {
                if (allVertices[i] == head->data.destination) {
                    neighborIndex = i;
                    break;
                }
            }
            if (neighborIndex != -1 && !visited[neighborIndex]) {
                int newDist = distance[minIndex] + head->data.weight;
                if (newDist < distance[neighborIndex]) {
                    distance[neighborIndex] = newDist;
                }
            }
            head = head->next;
        }
    }

    return (distance[destIndex] == INT_MAX) ? -1 : distance[destIndex];
}

int Graph::computeSpanningTree() {
    /*
      Υλοποίηση Prim για τον υπολογισμό ενός Ελάχιστου Δέντρου Κάλυψης (MST).
      Στο τέλος, επιστρέφει το συνολικό κόστος του δέντρου (sum of weights).
      Αν ο γράφος είναι συνεκτικός, το δέντρο θα περιλαμβάνει όλες τις κορυφές.
      Διαφορετικά, υπολογίζει ένα το δέντρο που αφορά όσες κορυφές είναι συνδεδεμένες.
    */
    Vector<int> allVertices = vertices.getAllVertices();
    int numVertices = allVertices.size();

    if (numVertices == 0) return 0;  // Αν δεν έχουμε κορυφές, το κόστος είναι μηδενικό

    Vector<int> key;
    Vector<bool> inMST;
    key.resize(numVertices);
    inMST.resize(numVertices);

    // Αρχικοποιούμε τις τιμές key σε INT_MAX και τις inMST σε false
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    // Ξεκινάμε από την πρώτη κορυφή (index 0)
    key[0] = 0;
    int totalCost = 0;

    for (int count = 0; count < numVertices; count++) {
        // Εντοπίζουμε την κορυφή που δεν έχει συμπεριληφθεί ακόμα στο MST και έχει τη μικρότερη τιμή key
        int minKey = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break; // Δεν υπάρχει άλλη προσιτή κορυφή

        inMST[minIndex] = true;
        totalCost += key[minIndex]; // Προσθέτουμε το κόστος αυτής της ακμής στο συνολικό κόστος

        // Ενημερώνουμε τα key για τις γειτονικές κορυφές
        LinkedList<Edge>* edges = vertices.getVertexEdges(allVertices[minIndex]);
        LinkedList<Edge>::Node* head = edges->getHead();
        while (head) {
            int neighborIndex = -1;
            for (int i = 0; i < numVertices; i++) {
                if (allVertices[i] == head->data.destination) {
                    neighborIndex = i;
                    break;
                }
            }
            if (neighborIndex != -1 && !inMST[neighborIndex] && head->data.weight < key[neighborIndex]) {
                key[neighborIndex] = head->data.weight;
            }
            head = head->next;
        }
    }

    return totalCost;
}

int Graph::findConnectedComponents() {
    /*
        Χρησιμοποιούμε την Αναζήτηση Βάθους (DFS) για να υπολογίσουμε πόσες ανεξάρτητες συνιστώσες
        (δηλαδη σε ποσες ομαδες μπορουμε να τους χωρισουμε) έχει ο γράφος.
    */
    Vector<int> allVertices = vertices.getAllVertices();
    int numVertices = allVertices.size();

    Vector<bool> visited;
    visited.resize(numVertices);

    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    int components = 0;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            components++;
            // Εκτελούμε DFS
            Vector<int> stack;
            stack.push(i);

            while (!stack.empty()) {
                int current = stack[stack.size() - 1];
                stack.pop();

                if (!visited[current]) {
                    visited[current] = true;
                    LinkedList<Edge>* edges = vertices.getVertexEdges(allVertices[current]);
                    LinkedList<Edge>::Node* head = edges->getHead();
                    while (head) {
                        // Βρίσκουμε το index του γείτονα
                        int neighborIndex = -1;
                        for (int j = 0; j < numVertices; j++) {
                            if (allVertices[j] == head->data.destination) {
                                neighborIndex = j;
                                break;
                            }
                        }
                        if (neighborIndex != -1 && !visited[neighborIndex]) {
                            stack.push(neighborIndex);
                        }
                        head = head->next;
                    }
                }
            }
        }
    }

    return components;
}