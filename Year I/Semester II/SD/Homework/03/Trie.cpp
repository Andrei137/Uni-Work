#include <fstream>
#include <vector>

struct Node
{
    int m_count{0}, m_finish{0};
    std::vector<Node*> m_sons{};
    Node(): m_sons(26) {}
};

void ins(Node*& a_head, const char* a_ch)
{
    if (a_head == NULL)
    {
        a_head = new Node;
    }
    ++a_head->m_count;
    if (a_ch[0] == '\0')
    {
        ++a_head->m_finish;
    }
    else
    {
        ins(a_head->m_sons[a_ch[0] - 'a'], a_ch + 1);
    }
    return;
}

void del(Node*& a_head, const char* a_ch)
{
    if (a_head == NULL)
    {
        return;
    }
    if (a_ch[0] == '\0')
    {
        --a_head->m_finish;
    }
    else
    {
        del(a_head->m_sons[a_ch[0] - 'a'], a_ch + 1);
    }
    --a_head->m_count;
    if (a_head->m_count == 0)
    {
        delete a_head;
        a_head = NULL;
    }
    return;
}

int query_count(Node* a_head, const char* a_ch)
{
    if (a_head == NULL)
    {
        return 0;
    }
    if (a_ch[0] == '\0')
    {
        return a_head->m_finish;
    }
    return query_count(a_head->m_sons[a_ch[0] - 'a'], a_ch + 1);
}

int query_prefix(Node* a_head, const char* a_ch)
{
    if (a_head == NULL || a_ch[0] == '\0')
    {
        return 0;
    }
    if (a_head->m_sons[a_ch[0] - 'a'] == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + query_prefix(a_head->m_sons[a_ch[0] - 'a'], a_ch + 1);
    }
}
int main()
{
    std::ifstream in("trie.in");
    std::ofstream out("trie.out");
    Node* trie{NULL};
    int op{};
    std::string s{};
    while (in >> op >> s)
    {
        if (op == 0)
        {
            ins(trie, s.c_str());
        }
        else if (op == 1)
        {
            del(trie, s.c_str());
        }
        else if (op == 2)
        {
            out << query_count(trie, s.c_str()) << '\n';
        }
        else
        {
            out << query_prefix(trie, s.c_str()) << '\n';
        }
    }
    delete trie;
    return 0;
}