// https://atcoder.jp/contests/abc287/submissions/40523558

#include <iostream>
#include <vector>

using str = std::string;

struct Node
{
    int m_count{ 0 };
    std::vector<Node*> m_sons{};
    Node(): m_sons(26) {}
};

void add(Node*& a_head, const char* a_str)
{
    if (a_head == nullptr)
    {
        a_head = new Node();
    }
    ++a_head->m_count;
    if (a_str[0] != '\0')
    {
        add(a_head->m_sons[a_str[0] - 'a'], a_str + 1);
    }
    return;
}

int query(Node* a_head, const char* a_str)
{
    if (a_str[0] == '\0')
    {
        return 0;
    }
    if (a_head->m_sons[a_str[0] - 'a']->m_count == 1)
    {
        return 0;
    }
    return 1 + query(a_head->m_sons[a_str[0] - 'a'], a_str + 1);
}

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);

    Node* trie{ nullptr };
    int n{};
    std::cin >> n;
    std::vector<str> s{};
    for (int i = 0; i < n; ++i)
    {
        str temp{};
        std::cin >> temp;
        s.push_back(temp);
        add(trie, s[i].c_str());
    }
    for (int i = 0; i < n; ++i)
    {
        std::cout << query(trie, s[i].c_str()) << '\n';
    }
    return 0;
}