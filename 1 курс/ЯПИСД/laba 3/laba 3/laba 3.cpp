#include <iostream>
#include <fstream>


struct Node
{
    int data;
    Node* prev;
    Node* next;
};

void push(Node*& head, int newData)
{
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

Node* insert(Node*& head, int data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr)
    {
        head->prev = newNode;
    }

    head = newNode;
    return newNode;
}

void swap(Node* a, Node* b)
{
    if (!a || !b || a == b)
        return;

    Node* temp = a->next;
    a->next = b->next;
    b->next = temp;

    if (a->next)
        a->next->prev = a;
    if (b->next)
        b->next->prev = b;

    temp = a->prev;
    a->prev = b->prev;
    b->prev = temp;

    if (a->prev)
        a->prev->next = a;
    if (b->prev)
        b->prev->next = b;
}

void bubble_sort(Node*& head)
{
    bool sorted = false;

    while (!sorted)
    {
        Node* p = head;
        while (p->prev)
        {
            p = p->prev;
        }
        sorted = true;
        while (p->next)
        {
            if (p->data > p->next->data)
            {
                swap(p, p->next);
                sorted = false;
            }
            else
            {
                p = p->next;
            }
        }
    }
}

Node* getLastNode(Node* head)
{
    Node* current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current;
}

void Swap(Node* a, Node* b) {
    if (a == b) return;

    if (a->next == b) {
        Node* temp = a;
        a = b;
        b = temp;
    }

    Node* temp = a->next;
    a->next = b->next;
    b->next = temp;

    if (a->next != NULL)
        a->next->prev = a;
    if (b->next != NULL)
        b->next->prev = b;

    temp = a->prev;
    a->prev = b->prev;
    b->prev = temp;

    if (a->prev != NULL)
        a->prev->next = a;
    if (b->prev != NULL)
        b->prev->next = b;


}

Node* partition(Node* low, Node* high)
{
    int pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next)
    {
        if (j->data < pivot)
        {
            i = (i == nullptr) ? low : i->next;
            Swap(i, j);
        }
    }

    i = (i == nullptr) ? low : i->next;
    int temp = i->data;
    i->data = high->data;
    high->data = temp;

    return i;
}

void quickSortRec(Node* low, Node* high)
{
    if (high != nullptr && low != high && low != high->next)
    {
        Node* pivot = partition(low, high);

        quickSortRec(low, pivot->prev);
        quickSortRec(pivot->next, high);
    }
}

void quickSort(Node* head)
{
    Node* lastNode = getLastNode(head);

    quickSortRec(head, lastNode);
}

int findSize(struct Node* node)
{
    int res = 0;
    while (node != NULL)
    {
        res++;
        node = node->next;
    }
    return res;
}

void printList(Node* head, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    head = insert(head, findSize(head));

    Node* current = head;
    int count = 0;
    while (current != nullptr)
    {
        file << current->data << " ";
        count++;
        current = current->next;
    }


    file.close();
}

int main()
{
    Node* head = nullptr;

    std::ifstream file("input.txt");

    if (!file)
    {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    int sortMethod;
    file >> sortMethod;

    int num;
    while (file >> num)
    {
        push(head, num);
    }

    file.close();

    if (sortMethod == 0)
    {
        quickSort(head);
    }
    else if (sortMethod == 1)
    {
        int count = 0;
        Node* current = head;

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        bubble_sort(head);
        Node* p = head;
        while (p->prev)
        {
            p = p->prev;
        }

        head = p;
    }

    printList(head, "output.txt");

    return 0;
}