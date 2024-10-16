#include <iostream>

struct Node
{
    int info{};
    Node* next{};
};


int length(Node*& a_head)
{
    Node* p{ a_head };
    int count{0};
    while (p != NULL)
    {
        ++count;
        p = p->next;
    }
    return count;
}

void print_list(Node*& a_head)
{
    std::cout << length(a_head);
    Node* p{ a_head };
    while (p != NULL)
    {
        std::cout << p->info << ' ';
        p = p->next;
    }
    std::cout << '\n';
}

void insert_front(Node*& a_head, int a_element)
{
    Node* p{ new Node };
    p->info = a_element;
    p->next = a_head;
    a_head = p;
}

void insert_end(Node*& a_head, int a_element)
{
    Node* p{ new Node };
    p->info = a_element;
    p->next = NULL;
    if (a_head == NULL)
    {
        a_head = p;
    }
    else
    {
        Node* t{ a_head };
        while (t->next != NULL)
        {
            t = t->next;
        }
        t->next = p;
    }
}

void delete_front(Node*& a_head)
{
    if (a_head != NULL)
    {
        Node* p{ a_head->next };
        a_head = p;
    }
}

void delete_end(Node*& a_head)
{
    if (a_head != NULL)
    {
        Node* p{ a_head };
        while (p->next->next != NULL)
        {
            p = p->next;
        }
        p->next = NULL;
    }
}

int main()
{
    Node* head = NULL;
    insert_front(head, 3);
    insert_front(head, 2);
    insert_front(head, 1);
    insert_end(head, 4);
    insert_end(head, 5);
    insert_end(head, 6);
    delete_front(head);
    delete_front(head);
    delete_end(head);
    print_list(head);
    return 0;
}