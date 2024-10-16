// https://codeforces.com/contest/714/submission/201721421

#include <iostream>
#include <vector>

using str = std::string;

str transform(str a_n)
{
    str s{};
    for (char c : a_n)
    {
        if ((c - '0') % 2 == 0)
        {
            s += '0';
        }
        else
        {
            s += '1';
        }
    }
    while (s.size() < 31)
    {
        s = '0' + s;
    }
    return s;
}

struct Node
{
    int m_count{ 0 };
    std::vector<Node*> m_sons{};
    Node() : m_sons(2) {}
};

void add(Node*& a_head, const char* a_str)
{
    if (a_head == NULL)
    {
        a_head = new Node;
    }
    if (a_str[0] == '\0')
    {
        ++a_head->m_count;
    }
    else
    {
        add(a_head->m_sons[a_str[0] - '0'], a_str + 1);
    }
    return;
}

void del(Node*& a_head, const char* a_str)
{
    if (a_head == NULL)
    {
        return;
    }
    if (a_str[0] == '\0')
    {
        if (a_head->m_count > 0)
        {
            --a_head->m_count;
        }
    }
    else
    {
        del(a_head->m_sons[a_str[0] - '0'], a_str + 1);
    }
    return;
}

int query_count(Node* a_head, const char* a_str)
{
    if (a_head == NULL)
    {
        return 0;
    }
    if (a_str[0] == '\0')
    {
        return a_head->m_count;
    }
    return query_count(a_head->m_sons[a_str[0] - '0'], a_str + 1);
}

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);

    Node* root{ new Node };
    int n{};
    std::cin >> n;
    while (n--)
    {
        char ch{};
        str s{};
        std::cin >> ch >> s;
        s = transform(s);
        if (ch == '+')
        {
            add(root, s.c_str());
        }
        else if (ch == '-')
        {
            del(root, s.c_str());
        }
        else
        {
            std::cout << query_count(root, s.c_str()) << '\n';
        }
    }
}