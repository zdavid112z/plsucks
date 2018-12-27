#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>
#define inf 0x3f3f3f3f
#define BIT(x) (1<<(x))

using namespace std;

struct edge
{
    int a, b, ok;
    int other(int k) const
    {
        return k == a ? b : a;
    }
} mc[100];

struct vec2
{
    int i, j;
};

struct matrix
{
    int n;
    int m[20][20];

    matrix operator*(const matrix& a) const
    {
        matrix r;
        r.n = n;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                r[i][j] = 0;
                for(int k = 0; k < n; k++)
                    r[i][j] += m[i][k] * a[k][j];
            }
        }
        return r;
    }
    int* operator[](int i) { return m[i]; }
    const int* operator[](int i) const { return m[i]; }
};

vector<int> g[20];
unordered_map<string, int> ids;
string names[20];
int ap[20];
vector<int> st;
int tata[20];
int viz[20];
vec2 pos[20];
int mat[20][20];
int indst[20];
int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int best = inf;
int n, m;
int hcmin;
int solc[20][20];
int sol[20][20];

int cicluri_impare()
{
    matrix a, an;
    a.n = n;
    memset(a.m, 0, sizeof(a.m));
    for(int i = 0; i < m; i++)
    {
        if(mc[i].ok)
        {
            a[mc[i].a][mc[i].b] = 1;
            a[mc[i].b][mc[i].a] = 1;
        }
    }
    memcpy(&an, &a, sizeof(matrix));
    for(int t = 1; t <= n; t++)
    {
        if(t % 2 != 0)
        {
            for(int i = 0; i < n; i++)
                if(an[i][i] == 1)
                    return 1;
        }
        an = an * a;
    }
    return 0;
}

int bitdiff(int a, int b)
{
    int r = 0;
    for(int i = 0; i < 4; i++)
        if((a & BIT(i)) != (b & BIT(i)))
            r++;
    return r;
}

int calc_biti(int i, int j)
{
    int q1q0, q3q2;
    if(i <= 1) q1q0 = i;
    else q1q0 = i ^ 1;
    if(j <= 1) q3q2 = j;
    else q3q2 = j ^ 1;
    return q3q2 * 4 + q1q0;
}

int calc_hazard()
{
    int h = 1;
    for(int i = 0; i < m; i++)
    {
        int ba = calc_biti(pos[mc[i].a].i, pos[mc[i].a].j);
        int bb = calc_biti(pos[mc[i].b].i, pos[mc[i].b].j);
        h *= bitdiff(ba, bb);
    }
    return h;
}

bool check_pos(vec2 p, int k, int ind)
{
    for(int i = 0; i < g[k].size(); i++)
    {
        const auto& m = mc[g[k][i]];
        if(m.ok)
        {
            if(indst[m.other(k)] < ind)
            {
                int di = abs(p.i - pos[m.other(k)].i);
                if(di == 3) di = 1;
                int dj = abs(p.j - pos[m.other(k)].j);
                if(dj == 3) dj = 1;
                if(di + dj != 1)
                    return false;
            }
        }
    }
    return true;
}

void back(int ind)
{
    int k = st[ind];
    vec2 pot[20];
    int lpot = 0;
    if(tata[k] != -1)
    {
        vec2 pt = pos[tata[k]];
        for(int i = 0; i < 4; i++)
        {
            vec2 pk;
            pk.i = (pt.i + d[i][0] + 4) % 4;
            pk.j = (pt.j + d[i][1] + 4) % 4;
            pot[lpot++] = pk;
        }
    }
    else
    {
        for(int i = 0; i < 16; i++)
            pot[lpot++] = {i / 4, i % 4};

    }
    for(int i = 0; i < lpot; i++)
    {
        vec2 pk = pot[i];
        if(mat[pk.i][pk.j] == -1)
        {
            if(check_pos(pk, k, ind))
            {
                pos[k] = pk;
                mat[pk.i][pk.j] = k;
                if(ind + 1 < st.size())
                {
                    back(ind + 1);
                }
                else
                {
                    int h = calc_hazard();
                    if(h < hcmin)
                    {
                        hcmin = h;
                        memcpy(solc, mat, sizeof(mat));
                    }
                }
                mat[pk.i][pk.j] = -1;
            }
        }
    }
}

int solve()
{
    if(cicluri_impare())
        return inf;

    for(int i = 0; i < n; i++)
    {
        int grad = 0;
        for(int j = 0; j < g[i].size(); j++)
        {
            if(mc[g[i][j]].ok)
                grad++;
        }
        if(grad > 4)
            return inf;
    }

    memset(viz, 0, sizeof(viz));
    st.clear();
    do
    {
        for(int i = 0; i < n; i++)
        {
            if(viz[i] == 0)
            {
                indst[i] = st.size();
                viz[i] = 1;
                tata[i] = -1;
                st.push_back(i);
                break;
            }
        }
        int r = st.size() - 1;
        while(r < st.size())
        {
            int k = st[r];
            for(int i = 0; i < g[k].size(); i++)
            {
                if(mc[g[k][i]].ok)
                {
                    int p = mc[g[k][i]].other(k);
                    if(viz[p] == 0)
                    {
                        indst[p] = st.size();
                        viz[p] = 1;
                        tata[p] = k;
                        st.push_back(p);
                    }
                }
            }
            r++;
        }
    } while(st.size() != n);

    memset(mat, 0xff, sizeof(mat));
    mat[0][0] = st[0];
    mat[1][0] = st[1];
    pos[st[0]] = {0, 0};
    pos[st[1]] = {1, 0};
    hcmin = inf;
    back(2);
    return hcmin;
}

int main()
{
    freopen("in.in", "r", stdin);
    char name[50], name2[50];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%s", name);
        ids[name] = i;
        names[i] = name;
    }
    m = 0;
    while(scanf("%s %s", name, name2) > 0)
    {
        int a = ids[name];
        int b = ids[name2];
        mc[m].a = a;
        mc[m].b = b;
        g[a].push_back(m);
        g[b].push_back(m);
        m++;
    }
    for(int z = 0; z < n; z++)
    {
        if(best <= BIT(z))
            break;
        for(int i = 0; i < z; i++)
            ap[i] = 0;
        for(int i = z; i < n; i++)
            ap[i] = 1;
        do
        {
            for(int i = 0; i < n; i++)
                mc[i].ok = ap[i];
            int haz = solve();
            if(haz < best)
            {
                best = haz;
                memcpy(sol, solc, sizeof(sol));
                if(best < BIT(z))
                    break;
            }
        } while(next_permutation(ap, ap + n));
    }
    int vcod[20];
    for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
    {
        if(sol[i][j] != -1)
        {
            int cod = calc_biti(i, j);
            vcod[sol[i][j]] = cod;
        }
    }
    printf("H = %d\n", best);
    int lgmax = 0;
    for(int i = 0; i < n; i++)
        lgmax = max(lgmax, int(strlen(names[i].c_str())));
    for(int i = 0; i < n; i++)
    {
        int cod = vcod[i];
        printf("%# *s : %d%d%d%d = %# 2d\n", lgmax, names[i].c_str(), (cod & BIT(3)) != 0, (cod & BIT(2)) != 0, (cod & BIT(1)) != 0, (cod & BIT(0)) != 0, cod);
    }
    return 0;
}
