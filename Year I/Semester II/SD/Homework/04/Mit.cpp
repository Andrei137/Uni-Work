// https://www.infoarena.ro/job_detail/3132752

#include <fstream>
#include <vector>

template <typename T>
T read(std::istream& a_in)
{
    T temp{};
    a_in >> temp;
    return temp;
}

struct segtree
{
    int m_size;
    std::vector<int> m_tree;
    std::vector<int> m_lazy;

    void init(int a_n)
    {
        m_size = a_n;
        m_tree.resize(4 * m_size);
        m_lazy.assign(4 * m_size, 0);
    }

    int single(int a_v)
    {
        return a_v;
    }

    int merge(int a_n1, int a_n2)
    {
        return std::max(a_n1, a_n2);
    }

    void build(std::vector<int>& a_v, int a_x, int a_lx, int a_rx)
    {
        if (a_rx == a_lx)
        {
            if (a_lx < (int)a_v.size())
            {
                m_tree[a_x] = single(a_v[a_lx]);
            }
            return;
        }
        int m{ (a_lx + a_rx) / 2 };
        build(a_v, a_x * 2, a_lx, m);
        build(a_v, a_x * 2 + 1, m + 1, a_rx);
        m_tree[a_x] = merge(m_tree[a_x * 2], m_tree[a_x * 2 + 1]);
    }

    void propagate(int a_x, int a_lx, int a_rx)
    {
        if (!m_lazy[a_x])
        {
            return;
        }
        m_tree[a_x] += m_lazy[a_x];
        if (a_lx != a_rx)
        {
            m_lazy[a_x * 2] += m_lazy[a_x];
            m_lazy[a_x * 2 + 1] += m_lazy[a_x];
        }
        m_lazy[a_x] = 0;
    }

    void update(int a_v, int a_l, int a_r, int a_x, int a_lx, int a_rx)
    {
        propagate(a_x, a_lx, a_rx);
        if (a_l <= a_lx && a_rx <= a_r)
        {
            m_lazy[a_x] += a_v;
            return;
        }
        int m{ (a_lx + a_rx) / 2 };
        if (a_l <= m)
        {
            update(a_v, a_l, a_r, a_x * 2, a_lx, m);
        }
        if (m < a_r)
        {
            update(a_v, a_l, a_r, a_x * 2 + 1, m + 1, a_rx);
        }
        propagate(a_x * 2, a_lx, m);
        propagate(a_x * 2 + 1, m + 1, a_rx);
        m_tree[a_x] = merge(m_tree[a_x * 2], m_tree[a_x * 2 + 1]);
    }

    int query(int a_l, int a_r, int a_x, int a_lx, int a_rx)
    {
        propagate(a_x, a_lx, a_rx);
        if (a_l <= a_lx && a_rx <= a_r)
        {
            return m_tree[a_x];
        }
        int m{ (a_lx + a_rx) / 2 };
        int n1{ 0 }, n2{ 0 };
        if (a_l <= m)
        {
            n1 = query(a_l, a_r, a_x * 2, a_lx, m);
        }
        if (m < a_r)
        {
            n2 = query(a_l, a_r, a_x * 2 + 1, m + 1, a_rx);
        }
        return merge(n1, n2);
    }

    void build(std::vector<int>& a_v)
    {
        build(a_v, 1, 1, m_size);
    }

    void update(int a_v, int a_l, int a_r)
    {
        update(a_v, a_l, a_r, 1, 1, m_size);
    }

    int query(int a_l, int a_r)
    {
       return query(a_l, a_r, 1, 1, m_size);
    }
};

int main()
{
    std::ifstream in("mit.in");
    std::ofstream out("mit.out");

    int n{ read<int>(in) };
    int m{ read<int>(in) };

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read<int>(in);
    }

    segtree st{};
    st.init(n + 1);
    st.build(a);
    while (m--)
    {
        int op{ read<int>(in) };
        if (op == 1)
        {
            int l{ read<int>(in) };
            int r{ read<int>(in) };
            out << st.query(l, r) << '\n';
        }
        else
        {
            int l{ read<int>(in) };
            int r{ read<int>(in) };
            int v{ read<int>(in) };
            st.update(v, l, r);
        }
    }

    in.close();
    out.close();
    return 0;
}