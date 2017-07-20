#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iomanip>
#include <iostream>
#include <string>
#include "stack.h"
#include "queue.h"
using namespace std;

void reverseQueue(Queue<char> & queue);
void roll(Stack<char> & stack, int n, int k);

int main() {
    Stack<char> stack_a, stack_b;
    stack_a.push('A');
    stack_a.push('B');
    stack_a.push('C');
    stack_a.push('D');

    stack_b = stack_a;

    cout << "Stack A Before roll " << stack_a.toString() << endl;
    roll(stack_a, 4, 1);
    cout << "Stack A After roll " << stack_a.toString() << endl;

    cout << "Stack B Before roll " << stack_b.toString() << endl;
    roll(stack_b, 3, 2);
    cout << "Stack B After roll " << stack_b.toString() << endl;

    return 0;
}

void reverseQueue(Queue<char> & queue) {
    Stack<char> stack;
    while (!queue.isEmpty()) {
        stack.push(queue.dequeue());
    }
    while (!stack.isEmpty()) {
        queue.enqueue(stack.pop());
    }
}

void roll(Stack<char> & stack, int n, int k) {
    Queue<char> queue;
    for (int i = 0; i < n; i++) {
        queue.enqueue(stack.pop());
    }
    for (int i = 0; i < k; i++) {
        queue.enqueue(queue.dequeue());
    }
    reverseQueue(queue);
    while (!queue.isEmpty())
        stack.push(queue.dequeue());
}
