# ST表

预处理$O(n\log n)$，查询$O(1)$.

```c++
template <typename T>
class SparseTable
{
    using VT = vec<T>;
    using VVT = vec<VT>;
    using FT = function<T(cs T &, cs T &)>;
    VVT ST;
    static T df(cs T &t1, cs T &t2) { return max(t1, t2); }
    FT op;
public:
    SparseTable(cs vec<T> &v, FT f = df)
    {
        op = f;
        int len = v.size(), l1 = ceil(log2(len)) + 1;
        ST.assign(len, VT(l1, 0));
        FOR(i, 0, len - 1)
        ST[i][0] = v[i];
        FOR(j, 1, l1 - 1)
        {
            int pj = (1 << (j - 1));
            for (int i = 0; i + pj < len; ++i)
                ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
        }
    }
    T query(int l, int r)
    {
        int lt = r - l + 1;
        int q = floor(log2(lt));
        return op(ST[l][q], ST[r - (1 << q) + 1][q]);
    }
};
```

