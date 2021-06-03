#include <iostream>
#include <string>
using namespace std;

struct Node {
    string code = "";
    Node* left = NULL;
    Node* right = NULL;
    char key;
    int freqency;
};

class PriorityQueue {
public:
   PriorityQueue();
   ~PriorityQueue();
   int size();
   void clear();
   void enqueue(Node* element);
   Node* dequeue();

private:
   struct Cell {
      Node *node;
      Cell *link;
   };

   Cell *head;   //Pointer to the cell at the head
   int count;    //Number of elements in the queue
};

PriorityQueue::PriorityQueue() {
   head = new Cell;
   head->link = NULL;
   head->node = NULL;
   count = 0;
}

PriorityQueue::~PriorityQueue() {
   clear();
}

int PriorityQueue::size() {
   return count;
}

void PriorityQueue::clear() {
   while (count > 0) {
      dequeue();
   }
}

void PriorityQueue::enqueue(Node *n)
{
    Cell *cp = new Cell;
    Cell *temp = head;
    cp->node = n;
    if (count == 0) {
        head->link = cp;
        cp->link = NULL;
    } else {
        while (true) {
            if ((temp->link != NULL) && ((n->freqency > temp->link->node->freqency) || ((n->freqency == temp->link->node->freqency) && (n->key > temp->link->node->key)))) {
                temp = temp->link;
                continue;
            } else {
                break;
            }
        }
        cp->link = temp->link;
        temp->link = cp;
    }
    count++;
}

Node *PriorityQueue::dequeue()
{
    Node *n = head->link->node;
    head->link = head->link->link;
    count--;
    return n;
}

void add(Node* n, string s) {
    if (n != NULL) {
        n->code = s + n->code;
        add(n->left, s);
        add(n->right, s);
    }
}

int main() {
    string s;
    getline(cin,s);

    PriorityQueue pq;
    Node *arr[256];
    for (int i = 0; i < 256; i++) {
        arr[i] = NULL;
    }

    int pos1 = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        int pos2 = 0;
        for (int j = 0; j < pos1; j++) {
            if (arr[j]->key == s[i]) {
                break;
            } else {
                pos2 += 1;
                continue;
            }
        }
        if (pos2 == pos1) {
            Node *n=new Node;
            n->key = s[i];
            n->freqency = 1;
            arr[pos1] = n;
            pos1++;
        } else {
            arr[pos2]->freqency += 1;
        }
    }

    for (int i = 0; i < pos1; i++) {
        Node *temp = arr[i];
        pq.enqueue(temp);
    }

    while (pq.size() >= 2) {
        Node *temp1 = pq.dequeue();
        Node *temp2 = pq.dequeue();
        Node *cp = new Node;
        cp->left = temp1;
        cp->right = temp2;
        cp->key = temp1->key;
        cp->freqency = temp1->freqency + temp2->freqency;

        add(temp1, "0");
        add(temp2, "1");
        pq.enqueue(cp);
    }

    string res ="";
    for (int i = 0; i < (int)s.length(); i++) {
        for (int j = 0; j < 256; j++) {
            if (arr[j]->key == s[i]) {
                res += arr[j]->code;
                break;
            }
        }
    }
    cout << res;
    return 0;
}

