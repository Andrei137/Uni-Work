// https://codeforces.com/problemset/submission/380/206962304

#include <iostream>
#include <vector>

using str = std::string;

template <typename T>
T read()
{
    T temp{};
    std::cin >> temp;
    return temp;
}

struct node
{
    int m_ans{}, m_left{}, m_right{};
};
 
struct segtree
{
    long long m_size{};
    std::vector<node> m_tree;
 
    void init(long long a_n)
    {
        m_size = 1;
        while (m_size < a_n)
        {
            m_size *= 2;
        }
        m_tree.resize(2 * m_size);
    }
 
    node NEUTRAL_ELEMENT = {0, 0, 0};
 
    node single(char a_v)
    {
        return {0, (a_v == '('), (a_v == ')')};
    }
 
    node merge(node a_n1, node a_n2)
    {
        int update{ std::min(a_n1.m_left, a_n2.m_right) };
        return 
        {
            a_n1.m_ans + a_n2.m_ans + update,
            a_n1.m_left + a_n2.m_left - update,
            a_n1.m_right + a_n2.m_right - update
        };
    }
 
    void build(const str& a_s, int a_x, int a_lx, int a_rx)
    {
        if (a_rx - a_lx == 1)
        {
            if (a_lx < (int)a_s.size())
            {
                m_tree[a_x] = single(a_s[a_lx]);
            }
            return;
        }
        int m{ (a_lx + a_rx) / 2 };
        build(a_s, a_x * 2 + 1, a_lx, m);
        build(a_s, a_x * 2 + 2, m, a_rx);
        m_tree[a_x] = merge(m_tree[a_x * 2 + 1], m_tree[a_x * 2 + 2]);
    }
 
    node query(int a_l, int a_r, int a_x, int a_lx, int a_rx)
    {
        if (a_lx >= a_r || a_l >= a_rx)
        {
            return NEUTRAL_ELEMENT;
        }
        if (a_l <= a_lx && a_rx <= a_r)
        {
            return m_tree[a_x];
        }
        int m{ (a_lx + a_rx) / 2 };
        if (a_l <= m && m < a_r)
        {
            return merge(query(a_l, a_r, a_x * 2 + 1, a_lx, m), query(a_l, a_r, a_x * 2 + 2, m, a_rx));
        }
        if (a_l < m)
        {
            return query(a_l, a_r, a_x * 2 + 1, a_lx, m);
        }
        return query(a_l, a_r, a_x * 2 + 2, m, a_rx);
    }

    void build(const str& a_s)
    {
        build(a_s, 0, 0, m_size);
    }
 
    node query(int a_l, int a_r)
    {
        return query(a_l, a_r, 0, 0, m_size);
    }
};

int main()
{
    std::cin.tie(0)->sync_with_stdio(0);

    str s{ read<str>() };

    segtree st{};
    st.init(s.size());
    st.build(s);

    int m{ read<int>() };
    while (m--)
    {
        int l{ read<int>() - 1 }, r{ read<int>() };
        std::cout << st.query(l, r).m_ans * 2 << '\n';
    }

    return 0;
}