// https://csacademy.com/submission/4022787

#include <algorithm>
#include <iostream>
#include <vector>

using str = std::string;

struct Node
{
    bool m_finished{ 0 };
    std::vector<Node*> m_sons{};
    Node() : m_sons(26) {}
};

void ins(Node*& a_head, int& a_leaves, const char* a_str)
{
    if (a_head == nullptr)
    {
        a_head = new Node();
    }
    if (a_str[0] != '\0')
    {
        if (a_head->m_finished)
        {
            a_head->m_finished = false;
            --a_leaves;
        }
        ins(a_head->m_sons[a_str[0] - 'a'], a_leaves, a_str + 1);
    }
    else
    {
        if (!a_head->m_finished)
        {
            a_head->m_finished = true;
            ++a_leaves;
        }
    }
}

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);

    Node* trie{ nullptr };
    int n{};
    int k{};
    std::cin >> n >> k;
    std::vector<str> v{};
    for (int i = 0; i < n; ++i)
    {
        str temp{};
        std::cin >> temp;
        v.push_back(temp);
    }
    std::sort(v.begin(), v.end(), [](const str& a, const str& b) { return a.size() < b.size(); });
    int leaves{ 0 };
    bool found{ false };
    for (int i = 0; i < (int)v.size() && !found; ++i)
    {
        ins(trie, leaves, v[i].c_str());
        if (leaves == k) 
        {
            std::cout << v[i].size();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << -1;
    }
    return 0;
}