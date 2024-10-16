// https://infoarena.ro/job_detail/3121176

#include <fstream>
#include <cstring>
#include <vector>

struct Node
{
    int m_last{ 0 };
    std::vector<Node*> m_sons{};
    Node() : m_sons(26) {}
};

Node* trie{ new Node() };

void ins(Node*& a_head, const char* a_str)
{
    if (a_str[0] == '\0')
    {
        return;
    }
    if (a_head->m_sons[a_str[0] - 'a'] == nullptr)
    {
        a_head->m_sons[a_str[0] - 'a'] = new Node();
    }
    ins(a_head->m_sons[a_str[0] - 'a'], a_str + 1);
}

void upd(Node*& a_head, const char* a_str, const int a_index)
{
    a_head->m_last = a_index;
    if (a_str[0] == '\0')
    {
        return;
    }
    if (a_head->m_sons[a_str[0] - 'a'] != nullptr)
    {
        upd(a_head->m_sons[a_str[0] - 'a'], a_str + 1, a_index);
    }
}

bool del(Node*& a_head, const int a_index)
{
    for (int i = 0; i < 26; ++i)
    {
        if (a_head->m_sons[i] != nullptr && del(a_head->m_sons[i], a_index))
        {
            a_head->m_sons[i] = nullptr;
        }
    }
    if (a_head->m_last != a_index && a_head != trie)
    {
        delete a_head;
        return true;
    }
    return false;
}

int query(Node*& a_head)
{
    int nr{ (a_head->m_last != -1) };
    for (int i = 0; i < 26; ++i)
    {
        if (a_head->m_sons[i] != nullptr)
        {
            nr += query(a_head->m_sons[i]);
        }
    }
    return nr;
}

int main()
{
    std::ifstream in("sub.in");
    std::ofstream out("sub.out");

    int n{};
    in >> n;
    for (int i = 0; i < n; ++i)
    {
        char c[305]{};
        in >> c;
        for (int j = 0; j < (int)strlen(c); ++j)
        {
            if (i)
            {
                upd(trie, c+ j, i);
            }
            else
            {
                ins(trie, c + j);
            }
        }
        del(trie, i);
    }
    in >> n;
    for (int i = 0; i < n; ++i)
    {
        char c[305]{};
        in >> c;
        for (int j = 0; j < (int)strlen(c); ++j)
        {
            upd(trie, c + j, -1);
        }
    }
    out << query(trie);
    in.close();
    out.close();
    return 0;
}