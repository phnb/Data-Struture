#include<iostream>
#include<stdio.h>
#include <climits>
using namespace std;

int n = 0;
int m = 0;
int start = 0;

struct Node {
    int id;
    int32_t key;
};

struct Neighbor {
    int id;
    int32_t weight;
    Neighbor *link;
};


class PriorityQueue {
public:
    PriorityQueue(int n);
    ~PriorityQueue();
    int size();
    Node* extract_min();
    void min_heapify(int i);
    void push(Node* node);
    void expandCapacity();

private:
    Node **arr;
    int len;
    int capacity;
};

PriorityQueue::PriorityQueue(int n) {
    capacity = n;
    arr = new Node* [capacity];
    len = 0;
}

PriorityQueue::~PriorityQueue() {
    delete [] arr;
}

int PriorityQueue::size() {
    return len;
}

Node* PriorityQueue::extract_min() {
    Node* min = arr[0];
    arr[0] = arr[len-1];
    len--;
    min_heapify(0);
    return min;
}

void PriorityQueue::min_heapify(int i) {
    int l, r, smallest;
    while (true) {
        l = 2*i + 1;
        r = 2*i + 2;
        smallest = i;
        if (l < len && arr[l]->key < arr[i]->key) {
            smallest = l;
        }
        if (r < len && arr[r]->key < arr[smallest]->key) {
            smallest = r;
        }
        if (smallest == i) {
            break;
        } else {
            Node* tmp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = tmp;
            i = smallest;
        }
    }
}

void PriorityQueue::push(Node *n) {
    if (len == capacity) {
        expandCapacity();
    }
    int i = len;
    arr[len++] = n;
    Node* temp = arr[i];
    int p = (i-1) / 2;
    while (i > 0) {
        if (arr[p]->key > temp->key) {
            arr[i] = arr[p];
            i = p;
            p = (p-1)/2;
        } else {
            break;
        }
    }
    arr[i] = temp;
}

void PriorityQueue::expandCapacity() {
    Node **oldArray = arr;
    capacity *= 2;
    arr = new Node* [capacity];
    for (int i = 0; i < len; i++)
    {
        arr[i] = oldArray[i];
    }
    delete [] oldArray;
}

void output(int a) {    //print the answer
    if(a < 0) {
        putchar('-');
        a = -a;
    }
    if(a >= 10) {
        output(a / 10);
    }
    putchar(a % 10 + '0');
}

int input() {    //Input all numbers
    int n1 = 0, n2 = 0;
    char ch;
    if((ch = getchar()) == '-') {
        n2 = 1;
    } else if (ch >= '0' && ch <= '9') {
        n1 = ch - '0';
    }
    while((ch = getchar()) >= '0' && ch <= '9') {
        n1 = n1 * 10 + (ch - '0');
    }
    return n2 ? -n1 : n1;
}

int main() {
    n = input();
    m = input();
    start = input();

    Neighbor* array[n];
    int results[n];
    bool arr1[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = 1;
    }
    for (int i=0;i<n;i++) {
        array[i] = NULL;
    }

    for (int j=0;j<m;j++) {
        int num1, num2;
        int32_t weight;
        num1 = input();
        num2 = input();
        weight = input();
        Neighbor* cp = new Neighbor;
        cp->id = num2-1;
        cp->weight = weight;
        cp->link = array[num1-1];
        array[num1-1] = cp;
    }

    PriorityQueue pq(m);
    Node *p=new Node;
    p->key = 0;
    p->id = start-1;
    pq.push(p);
    for (int i = 0; i < n; i++) {
        if (i != start -1) {
            Node* n=new Node;
            n->key =INT_MAX;
            n->id =i;
            pq.push(n);
        }
        arr1[i]=0;
        results[i]=INT_MAX;
    }
    results[start-1]=0;

    while (true) {
        if (pq.size() > 0) {
            Node *cp = pq.extract_min();
            Neighbor *cp2 = array[cp->id];
            if (arr1[cp->id]) {
                continue;
            }
            arr1[cp->id] = 1;
            results[cp->id] = cp->key;
            while (cp2 != NULL) {
                if (!arr1[cp2->id]) {
                    int distance = cp2->weight + results[cp->id];
                    if (distance < 0) {
                        distance =INT_MAX;
                    }
                    if (distance < results[cp2->id]) {
                        Node* cp = new Node;
                        cp->key = distance;
                        cp->id = cp2->id;
                        pq.push(cp);
                    }
                }
                cp2 = cp2->link;
            }
        } else {
            break;
        }
    }

    for(int i = 0 ; i < n ; i++) {
        if (results[i] != INT_MAX) {
            output(results[i]);
            putchar('\n');
        } else {
            output(-1);
            putchar('\n');
        }
    }
    return 0;
}
