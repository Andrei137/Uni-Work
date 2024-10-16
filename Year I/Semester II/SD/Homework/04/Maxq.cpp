// https://www.infoarena.ro/job_detail/3132701

#include <fstream>
#include <vector>

template <typename T>
T read(std::istream& a_in)
{
    T temp{};
    a_in >> temp;
    return temp;
}

struct node
{
    long long m_seg{}, m_pref{}, m_suf{}, m_sum{};
};

struct segtree
{
    int m_size{};
    std::vector<node> m_tree;
 
    void init(int a_n)
    {
        m_size = 1;
        while (m_size < a_n)
        {
            m_size *= 2;
        }
        m_tree.resize(2 * m_size);
    }
 
    node NEUTRAL_ELEMENT = {0, 0, 0, 0};
 
    node single(int a_v)
    {
        if (a_v > 0)
        {
            return {a_v, a_v, a_v, a_v};
        }
        return {0, 0, 0, a_v};
    }
 
    node merge(node a_n1, node a_n2)
    {
        return 
        {
            std::max(a_n1.m_seg, std::max(a_n2.m_seg, a_n1.m_suf + a_n2.m_pref)),
            std::max(a_n1.m_pref, a_n1.m_sum + a_n2.m_pref),
            std::max(a_n2.m_suf, a_n2.m_sum + a_n1.m_suf),
            a_n1.m_sum + a_n2.m_sum
        };
    }
 
    void build(std::vector<int>& a_v, int a_x, int a_lx, int a_rx)
    {
        if (a_rx - a_lx == 1)
        {
            if (a_lx < (int)a_v.size())
            {
                m_tree[a_x] = single(a_v[a_lx]);
            }
            return;
        }
        int m{ (a_lx + a_rx) / 2 };
        build(a_v, a_x * 2 + 1, a_lx, m);
        build(a_v, a_x * 2 + 2, m, a_rx);
        m_tree[a_x] = merge(m_tree[a_x * 2 + 1], m_tree[a_x * 2 + 2]);
    }
 
    void set(int a_i, int a_v, int a_x, int a_lx, int a_rx)
    {
        if (a_rx - a_lx == 1)
        {
            m_tree[a_x] = single(a_v);
            return;
        }
        int m{ (a_lx + a_rx) / 2};
        if (a_i < m)
        {
            set(a_i, a_v, a_x * 2 + 1, a_lx, m);
        }
        else
        {
            set(a_i, a_v, a_x * 2 + 2, m, a_rx);
        }
        m_tree[a_x] = merge(m_tree[a_x * 2 + 1], m_tree[a_x * 2 + 2]);
    }
 
    node query(int a_l, int a_r, int a_x, int a_lx, int a_rx)
    {
        if (a_lx >= a_r || a_l >= a_rx)
        {
            return NEUTRAL_ELEMENT;
        }
        if (a_lx >= a_l && a_rx <= a_r)
        {
            return m_tree[a_x];
        }
        int m{ (a_lx + a_rx) / 2 };
        node s1{ query(a_l, a_r, a_x * 2 + 1, a_lx, m ) };
        node s2{ query(a_l, a_r, a_x * 2 + 2, m, a_rx) };
        return merge(s1, s2);
    }

    void build(std::vector<int>& a_v)
    {
        build(a_v, 0, 0, m_size);
    }

    void set(int a_i, int a_v)
    {
        set(a_i, a_v, 0, 0, m_size);
    }
 
    node query(int a_l, int a_r)
    {
        return query(a_l, a_r, 0, 0, m_size);
    }
};
 
int main()
{
    std::ifstream in("maxq.in");
    std::ofstream out("maxq.out");
 
    int n{ read<int>(in) };
 
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        a[i] = read<int>(in);
    }
 
    segtree st{};
    st.init(n);
    st.build(a);

    int m{ read<int>(in) };
    while (m--)
    {
        int op{ read<int>(in) };
        if (op == 0)
        {
            int i{ read<int>(in) };
            int v{ read<int>(in) };
            st.set(i, v);
        }
        else
        {
            int l{ read<int>(in) };
            int r{ read<int>(in) };
            out << st.query(l, r + 1).m_seg << '\n';
        }
    }

    in.close();
    out.close();
    return 0;
}