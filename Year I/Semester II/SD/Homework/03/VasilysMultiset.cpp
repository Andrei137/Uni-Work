// https://codeforces.com/problemset/submission/706/201720573

#include <iostream>
#include <vector>

using str = std::string;

struct Node
{
    int m_count{ 0 };
    std::vector<Node*> m_sons{};
    Node() : m_sons(2) {}
};

void ins(Node*& a_head, int a_pow, int a_number)
{
    ++a_head->m_count;
    if (a_pow == 0)
    {
        return;
    }
    int next{ ((a_number >> (a_pow - 1)) & 1) };
    if (a_head->m_sons[next] == nullptr)
    {
        a_head->m_sons[next] = new Node;
    }
    ins(a_head->m_sons[next], a_pow - 1, a_number);
}

void del(Node*& a_head, int a_pow, int a_number)
{
    --a_head->m_count;
    if (a_pow == 0)
    {
        return;
    }
    int next{ ((a_number >> (a_pow - 1)) & 1) };
    del(a_head->m_sons[next], a_pow - 1, a_number);
    if (a_head->m_sons[next]->m_count == 0)
    {
        delete a_head->m_sons[next];
        a_head->m_sons[next] = nullptr;
    }
}

int query(Node* a_head, int a_pow, int a_number)
{
    if (a_pow == 0)
    {
        return 0;
    }
    int next{ 1 - ((a_number >> (a_pow - 1)) & 1) };
    if (a_head->m_sons[next] == nullptr)
    {
        next = 1 - next;
    }
    return (next << (a_pow - 1)) + query(a_head->m_sons[next], a_pow - 1, a_number);
}

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);

    Node* root{ new Node }; 
    ins(root, 32, 0);
    int n{};
    std::cin >> n;
    while (n--)
    {
        char ch{};
        int x{};
        std::cin >> ch >> x;
        if (ch == '+')
        {
            ins(root, 32, x);
        }
        else if (ch == '-')
        {
            del(root, 32, x);
        }
        else
        {
            std::cout << (x ^ query(root, 32, x)) << '\n';
        }
    }
    return 0;
}