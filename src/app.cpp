#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <string>
#include "vector.h"
#include "queue.h"
#include "stack.h"
using namespace std;

void reverseQueue(Queue<string> & queue);

int main() {
    Queue<string> names;
    names.enqueue("a");
    names.enqueue("b");
    names.enqueue("c");
    names.enqueue("d");

    cout << "Names before reversal: " << names.toString() << endl;
    reverseQueue(names);
    cout << "Names after reversal: " << names.toString() << endl;

    return 0;
}

void reverseQueue(Queue<string> & queue) {
    Stack<string> stack;
    while (!queue.isEmpty()) {
        stack.push(queue.dequeue());
    }
    while (!stack.isEmpty()) {
        queue.enqueue(stack.pop());
    }
}
