// https://www.infoarena.ro/job_detail/3132680

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
    int m_size{};
    std::vector<int> m_tree;
 
    void init(int a_n)
    {
        m_size = 1;
        while (m_size < a_n)
        {
            m_size *= 2;
        }
        m_tree.resize(2 * m_size);
    }

    void update(int& a_pos, int a_x, int a_lx, int a_rx)
    {
        if (a_lx == a_rx)
        {
            m_tree[a_x] = 1;
            return;
        }
        int m{ (a_lx + a_rx) / 2 };
        if (a_pos <= m)
        {
            update(a_pos, a_x * 2, a_lx, m);
        }
        else
        {
            update(a_pos, a_x * 2 + 1, m + 1, a_rx);
        }
        m_tree[a_x] = m_tree[a_x * 2] + m_tree[a_x * 2 + 1];
    }

    int query(int a_k, int a_x, int a_lx, int a_rx)
    {
        if (a_lx == a_rx)
        {
            return a_lx;
        }
        int m{ (a_lx + a_rx) / 2 };
        int nr0_leftside{ (m - a_lx + 1) - m_tree[2 * a_x] };
        if (a_k <= nr0_leftside)
        {
            return query(a_k, a_x * 2, a_lx, m);
        }
        else
        {
            return query(a_k - nr0_leftside, a_x * 2 + 1, m + 1, a_rx);
        }
    }

    void update(int& a_pos)
    {
        update(a_pos, 1, 1, m_size);
    }

    int query(int a_k)
    {
        return query(a_k, 1, 1, m_size);
    }
};
 
int main()
{
    std::ifstream in("schi.in");
    std::ofstream out("schi.out");
 
    int n{ read<int>(in) };
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)
    {
        v[i] = read<int>(in);
    }

    segtree st{};
    st.init(n);
    std::vector<int> a(n);
    for (int i = n - 1; i >= 0; --i)
    {
        int pos{ st.query(v[i]) };
        st.update(pos);
        a[pos - 1] = i + 1;
    }

    for (int i = 0; i < n; ++i)
    {
        out << a[i] << '\n';
    }

    in.close();
    out.close();
    return 0;
}