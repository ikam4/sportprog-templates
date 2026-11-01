#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Подключаем исходные самостоятельные примеры, не выполняя их функции main.
#define main example_main
#pragma GCC push_options
namespace dsu_example {
#include "../data_structures/dsu.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace pool_example {
#include "../data_structures/lazy_impl_segtree.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace bit_example {
#include "../data_structures/bit_trie.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace sat_example {
#include "../graphs/2sat.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace negative_example {
#include "../graphs/paths_negative.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace gauss_example {
#include "../math/linal_comod.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace number_example {
#include "../math/number_theory.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace modint_example {
#include "../templates/template2.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace sequence_example {
#include "../dp/knapsack_and_sequences.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace exam_example {
#include "../templates/exam_2sem.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace hld_example {
#include "../graphs/heavy_light.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace centroid_example {
#include "../graphs/centroid.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace mst_example {
#include "../graphs/min_spanning_tree.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace scc_example {
#include "../graphs/scc.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace lowlink_example {
#include "../graphs/bridges_dots.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace topo_example {
#include "../graphs/topo_sort.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace euler_example {
#include "../graphs/euler_cycle.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace treap_example {
#include "../data_structures/treap.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace sum_tree_example {
#include "../data_structures/segment_tree.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace min_tree_example {
#include "../data_structures/lazy_segtree.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace point_pool_example {
#include "../data_structures/impl_segtree.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace lca_example {
#include "../graphs/lca.cpp"
}
#pragma GCC pop_options
#pragma GCC push_options
namespace sparse_example {
#include "../data_structures/sparse_table.cpp"
}
#pragma GCC pop_options
#undef main

using namespace std;
using ll = long long;
using vi = vector<int>;
mt19937 rng(20261102);
int ri(int n) { return rng() % n; }
void check(bool ok, const char* label) {
    if (!ok) { cerr << "FAIL: " << label << '\n'; exit(1); }
}
template<class F> string run_io(const string& input, F f) {
    istringstream in(input); ostringstream out;
    auto* old_in = cin.rdbuf(in.rdbuf()); auto* old_out = cout.rdbuf(out.rdbuf());
    cin.clear(); f(); cin.rdbuf(old_in); cout.rdbuf(old_out); cin.clear();
    return out.str();
}
bool subsequence(const vi& s, const vi& a) {
    size_t k=0; for (int x:a) if (k<s.size() && s[k]==x) ++k;
    return k==s.size();
}

template<class T> T three_node_treap() {
    T t;t.tr.resize(4);t.root=2;
    for(int i=1;i<=3;++i){t.tr[i].val=10*i;t.tr[i].y=(i==2?100:1);}
    t.tr[2].children={1,3};t.recalc(1);t.recalc(3);t.recalc(2);
    return t;
}
template<class T> void check_sequence(T& t,const vi& a) {
    check(t.tr[t.root].sz==(int)a.size(),"implicit treap size");
    for(int k=0;k<(int)a.size();++k)
        check(t.get_kth(k)==a[k],"implicit treap versus vector");
}
template<class T> void test_treap_copy() {
    const vi a={10,20,30};
    for(int k=0;k<=3;++k){
        auto t=three_node_treap<T>();auto [l,r]=t.split(t.root,k);
        t.root=l;check_sequence(t,vi(a.begin(),a.begin()+k));
        t.root=r;check_sequence(t,vi(a.begin()+k,a.end()));
        t.root=t.merge(l,r);check_sequence(t,a);
    }
    for(int k=0;k<3;++k){
        auto t=three_node_treap<T>();vi expected=a;expected.erase(expected.begin()+k);
        t.erase(k);check_sequence(t,expected);
    }
    for(int z=0;z<50;++z){
        T t;vi expected;
        for(int it=0;it<500;++it){
            int op=ri(3);
            if(expected.empty()||op==0){
                int k=ri((int)expected.size()+1),value=ri(61)-30;
                t.insert(k,value);expected.insert(expected.begin()+k,value);
            }else if(op==1){
                int k=ri((int)expected.size());t.erase(k);expected.erase(expected.begin()+k);
            }else{
                int k=ri((int)expected.size()+1);auto [l,r]=t.split(t.root,k);
                t.root=l;check_sequence(t,vi(expected.begin(),expected.begin()+k));
                t.root=r;check_sequence(t,vi(expected.begin()+k,expected.end()));
                t.root=t.merge(l,r);
            }
            check_sequence(t,expected);
        }
    }
}

void test_lcis() {
    vi a={1,2,3,4,5,0,1,2,3}, b={0,1,2,3,4,5};
    auto s=sequence_example::lcis(a,b);
    check(s.size()==5 && subsequence(s,a) && subsequence(s,b), "LCIS predecessor regression");
    for(int z=0;z<600;++z) {
        a.resize(ri(9)); b.resize(ri(9));
        for(int& x:a)x=ri(7)-3;for(int& x:b)x=ri(7)-3;
        int best=0;
        for(int mask=0;mask<(1<<a.size());++mask) {
            vi t;for(int i=0;i<(int)a.size();++i)if(mask>>i&1)t.push_back(a[i]);
            if(adjacent_find(t.begin(),t.end(),greater_equal<int>())==t.end() && subsequence(t,b)) best=max(best,(int)t.size());
        }
        s=sequence_example::lcis(a,b);
        check((int)s.size()==best && subsequence(s,a) && subsequence(s,b) &&
              adjacent_find(s.begin(),s.end(),greater_equal<int>())==s.end(), "LCIS exhaustive oracle");
    }
}

void test_modint_gauss() {
    check(modint_example::mint((__int128)-3).v==1000000004, "signed int128 ModInt");
    check(lowlink_example::mint((__int128)-3).v==1000000004, "copied ModInt in bridges");
    check(topo_example::mint((__int128)-3).v==1000000004, "copied ModInt in topo");
    constexpr ll p=9223372036854775783LL;
    using Big=modint_example::ModInt<ll,p>;
    check((Big(p-1)+Big(4)).v==3 && (Big(2)-Big(p-1)).v==3,"large-modulus add/subtract");
    for(int z=0;z<10000;++z) {
        ll a=((uint64_t(rng())<<32)|rng())%p,b=((uint64_t(rng())<<32)|rng())%p;
        check((Big(a)+Big(b)).v==((__int128)a+b)%p,"ModInt addition oracle");
        check((Big(a)-Big(b)).v==((__int128)a-b+p)%p,"ModInt subtraction oracle");
    }
    vi ans;
    check(gauss_example::SLAE::gauss_mod({{1,2,5},{1,1,3}},ans)==1 && ans==vi({1,2}), "modular subtraction regression");
    check(gauss_example::SLAE::gauss_mod({{1,1,3},{2,2,6}},ans)==2,"modular free variables");
    check(gauss_example::SLAE::gauss_mod({{1,1,3},{2,2,7}},ans)==0,"modular inconsistency");
}

void test_pool_and_bits() {
    pool_example::ImplSegtreePool p(1<<20);
    int root=p.update(0,0,(1<<20)-1,3),l,r;
    p.split(root,12345,l,r);
    check(p.query(l,0,(1<<20)-1)==3LL*12345,"lazy split left with reallocation");
    check(p.query(r,0,(1<<20)-1)==3LL*((1<<20)-12345),"lazy split right with reallocation");
    root=p.merge(l,r);check(p.query(root,0,(1<<20)-1)==3LL*(1<<20),"lazy merge after split");
    bit_example::BitTrie<5> bt;bt.insert(0);bt.insert(5);bt.insert(31);
    for(uint64_t limit:{32ULL,33ULL,64ULL,~0ULL}) {
        check(bt.order_of_key(limit)==3,"bit rank above domain");
        check(bt.count_xor_less(7,limit)==3,"xor threshold above domain");
        check(bt.lower_bound(limit)==~0ULL,"preserved lower_bound wrapper");
    }
    bit_example::BitTrie<64> b64;b64.insert(0);b64.insert(~0ULL);
    check(b64.order_of_key(~0ULL)==1 && b64.count_xor_less(0,~0ULL)==1,"64-bit boundaries");
}

template<class Sat> void test_sat_copy() {
    Sat s(1);check(s.get_ans(),"initial SAT");s.set(0,true);
    check(s.get_ans()&&s.ans[0],"SAT repeated after fixing true");
    s.set(0,false);check(!s.get_ans()&&!s.get_ans(),"SAT repeated contradiction");
}

struct ModelSegtree {
    vector<ll> a;
    ModelSegtree()=default;ModelSegtree(const vi& v):a(v.begin(),v.end()){}
    ll query(int l,int r){return accumulate(a.begin()+l,a.begin()+r+1,0LL);}
    void update(int l,int r,int d){for(int i=l;i<=r;++i)a[i]+=d;}
};
void test_zero_based() {
    dsu_example::RollbackDSU d(4);check(d.parent.size()==4&&d.comps==4,"rollback domain");
    int mark=d.snapshot();d.union_sets(0,3);d.union_sets(0,1);
    check(d.comps==2 && d.find_set(0)==d.find_set(3),"rollback zero vertex");
    d.rollback(mark);check(d.comps==4&&d.find_set(0)!=d.find_set(3),"rollback restoration");
    vector<vi> g={{1},{0,2},{1}},one(1),empty;
    hld_example::HLD<ModelSegtree> h(0,g,{4,5,6});
    exam_example::HLD<ModelSegtree> eh(0,g,{4,5,6});
    check(h.query(0,2)==15&&eh.query(0,2)==15,"HLD includes vertex zero");
    h.update(0,2,2);eh.update(0,2,2);
    check(h.query(0,2)==21&&eh.query(0,2)==21,"HLD update with zero-based positions");
    centroid_example::centroid_decomp c(one),ce(empty);
    exam_example::centroid_decomp ec(one),ece(empty);
    check(c.used[0]&&ec.used[0],"centroid single vertex zero");
    vector<vector<pair<int,int>>> one_with_ids(1);
    lowlink_example::bridges::solve(one_with_ids);lowlink_example::dots::solve(one_with_ids);
    exam_example::bridges::solve(one_with_ids);exam_example::dots::solve(one_with_ids);
    vector<vi> dg={{},{2},{1}},rg=dg;
    auto [dag,comp]=scc_example::scc::solve(dg,rg);
    auto [edag,ecomp]=exam_example::scc::solve(dg,rg);
    check(comp[0]>=0&&comp[1]==comp[2]&&comp[0]!=comp[1],"SCC isolated zero");
    check(ecomp[0]>=0&&ecomp[1]==ecomp[2]&&ecomp[0]!=ecomp[1],"copied SCC isolated zero");
    vector<array<int,3>> edges={{0,1,2},{1,2,-3},{0,2,5}};
    vector<vector<pair<int,int>>> wg={{{1,2},{2,5}},{{0,2},{2,-3}},{{1,-3},{0,5}}};
    check(mst_example::kruskal(3,edges)==-1 && mst_example::boruvka(3,edges)==-1 && mst_example::prim(wg)==-1 && mst_example::prim_v2(wg)==-1,"zero-based thematic MST");
    check(exam_example::MST::kruskal(3,edges)==-1 && exam_example::MST::boruvka(3,edges)==-1 && exam_example::MST::prim(3,wg)==-1,"zero-based copied MST");
    wg.assign(1,{});edges.clear();
    check(exam_example::MST::prim(1,wg)==0&&mst_example::boruvka(1,edges)==0,"MST single vertex zero");
    check(run_io("3 2\n0 1\n1 2\n",[]{topo_example::solve();})=="0 1 2 ","zero-based topo example");
    for(int i=0;i<2;++i) {
        check(run_io("3 2\n0 1\n1 2\n",[]{euler_example::solve();})=="012","zero-based Euler example and state reset");
        check(run_io("3 3\n0 1\n1 2\n2 0\n",[]{euler_example::solve2();})=="0120","zero-based directed Euler example");
    }
    check(run_io("1 0\n",[]{euler_example::solve();})=="0","Euler without edges");
}

void test_wide_segment_values() {
    const ll big=1000000000000LL;
    sum_tree_example::segtree sum(vi{1000000000,1000000000,1000000000});
    check(sum.query(0,2)==3000000000LL,"segment sum exceeds int with int input");
    sum.update(1,-1000000000);check(sum.query(0,2)==1000000000LL,"int point assignment and wide sum");
    sum_tree_example::segtree sum_int(vi{1,2,3}),sum_empty(vi{});
    check(sum_int.query(0,2)==6,"TRD segment constructor");
    min_tree_example::min_segtree minimum(vi{1000000000,-1000000000,0});
    minimum.update(0,1,3*big);
    check(minimum.get(0,1)==3*big-1000000000&&minimum.get(0,0)==3*big+1000000000,"wide lazy minimum and neutral value");
    min_tree_example::min_segtree min_int(vi{2,1}),zeros(3);
    check(min_int.get(0,1)==1&&zeros.get(0,2)==0,"minimum constructors preserved");
    for(int z=0;z<40;++z){
        int n=1+ri(20);vi initial(n);
        for(int& x:initial)x=(ri(2001)-1000)*1000000;
        vector<ll> a(initial.begin(),initial.end()),b=a;
        sum_tree_example::segtree s(initial);min_tree_example::min_segtree m(initial);
        for(int it=0;it<150;++it){
            int pos=ri(n),value=(ri(2001)-1000)*1000000;
            s.update(pos,value);b[pos]=value;
            int l=ri(n),r=ri(n);if(l>r)swap(l,r);
            check(s.query(l,r)==accumulate(b.begin()+l,b.begin()+r+1,0LL),"TRD point tree versus vector");
            ll delta=(ll(ri(2001))-1000)*1000000000LL;
            m.update(l,r,delta);for(int j=l;j<=r;++j)a[j]+=delta;
            l=ri(n);r=ri(n);if(l>r)swap(l,r);
            check(m.get(l,r)==*min_element(a.begin()+l,a.begin()+r+1),"wide lazy minimum versus vector");
        }
    }
    point_pool_example::ImplSegtreePool pool(16);
    point_pool_example::ImplSegtree left(pool),right(&pool);
    left.update(0,300);right.update(15,-100);left.merge(right);
    check(left.query(0,15)==200&&left.query(0,0)==300,"int implicit point wrapper and merge");
    pool_example::ImplSegtreePool lazy_pool(16);
    pool_example::ImplSegtree lazy(lazy_pool);
    lazy.update(0,15,big);lazy.update_point(0,2*big);
    auto high=lazy.split(8);
    check(lazy.query(0,15)==10*big&&high.query(0,15)==8*big,"lazy wrapper split with default reserve");
    vector<vi> graph={{1},{0,2},{1}};vi values(3,1000000000);
    hld_example::HLD<ModelSegtree> h(0,graph,values);
    exam_example::HLD<ModelSegtree> eh(0,graph,values);
    check(h.query(0,2)==3000000000LL&&eh.query(0,2)==3000000000LL,"64-bit HLD result in both copies");
    h.update(0,2,1000000000);eh.update(0,2,1000000000);
    check(h.query(0,2)==6000000000LL&&eh.query(0,2)==6000000000LL,"HLD keeps int updates and wide sums");
}

int component_count(int n,const vector<pair<int,int>>& edges,int removed_edge=-1,int removed_vertex=-1) {
    vector<vi> graph(n);
    for(int i=0;i<(int)edges.size();++i){
        auto [u,v]=edges[i];if(i==removed_edge||u==removed_vertex||v==removed_vertex)continue;
        graph[u].push_back(v);graph[v].push_back(u);
    }
    vector<bool> seen(n);if(removed_vertex>=0)seen[removed_vertex]=true;int count=0;
    for(int start=0;start<n;++start)if(!seen[start]){
        ++count;vi q={start};seen[start]=true;
        for(int j=0;j<(int)q.size();++j)for(int v:graph[q[j]])if(!seen[v]){seen[v]=true;q.push_back(v);}
    }
    return count;
}
template<auto BridgeDfs,auto DotDfs,auto BridgeSolve,auto DotSolve> void test_multigraph_copy() {
    for(int z=0;z<900;++z){
        int n=ri(8),m=n?ri(18):0;vector<pair<int,int>> edges;
        vector<vector<pair<int,int>>> graph(n);
        for(int id=0;id<m;++id){int u=ri(n),v=ri(n);edges.push_back({u,v});graph[u].push_back({v,id});graph[v].push_back({u,id});}
        vi tin(n),low(n);int timer=1;vector<pair<int,int>> found;
        for(int v=0;v<n;++v)if(!tin[v])BridgeDfs(v,-1,tin,low,timer,graph,found);
        for(auto& e:found)if(e.first>e.second)swap(e.first,e.second);
        sort(found.begin(),found.end());vector<pair<int,int>> expected;
        int baseline=component_count(n,edges);
        for(int id=0;id<m;++id)if(component_count(n,edges,id)>baseline){auto [u,v]=edges[id];expected.push_back({min(u,v),max(u,v)});}
        sort(expected.begin(),expected.end());check(found==expected,"bridges in disconnected multigraph");
        auto returned=BridgeSolve(graph);
        for(auto& e:returned)if(e.first>e.second)swap(e.first,e.second);
        sort(returned.begin(),returned.end());
        check(returned==expected,"bridge wrapper returns its result");
        fill(tin.begin(),tin.end(),0);fill(low.begin(),low.end(),0);timer=1;vector<bool> dots(n);
        for(int v=0;v<n;++v)if(!tin[v])DotDfs(v,-1,tin,low,timer,graph,dots);
        for(int v=0;v<n;++v)check(dots[v]==(component_count(n,edges,-1,v)>baseline),"articulation points in multigraph");
        check(DotSolve(graph)==dots,"articulation wrapper returns its result");
    }
}

void test_floyd_and_factor() {
    vector<vi> matrix(70,vi(70,-1));
    auto saturated=negative_example::floyd_yorshell(70,matrix);
    check(saturated.cycle&&saturated.dp[0][0]>=-negative_example::LINF,"Floyd negative-cycle saturation");
    check(saturated.get_path(0,0).empty(),"Floyd does not restore through negative cycles");
    check(run_io("",[&]{negative_example::floyd_example(70,matrix);})=="Negative cycle found\n","Floyd diagnostic example retained");
    vector<vector<pair<int,ll>>> g(70);
    for(int i=0;i<70;++i)for(int j=0;j<70;++j)g[i].push_back({j,-1});
    check(exam_example::shortest_path_neg::floyd_yorshell<ll>(70,g).empty(),"copied Floyd saturation");
    for(ll n:{1LL,-1LL,360LL,-360LL,9223372036854775807LL}) {
        auto f=number_example::factor(n);__int128 product=1;
        for(auto [p,e]:f)while(e--)product*=p;
        check(product==(n<0?-(__int128)n:(__int128)n),"factor reconstruction");
    }
}

template<class T> void test_centroid_parents() {
    vector<vi> empty;T zero(empty);check(zero.centroid_parent.empty(),"empty centroid parent array");
    for(int z=0;z<100;++z){
        int n=1+ri(45);vector<vi> graph(n);
        for(int v=1;v<n;++v){int p=ri(v);graph[v].push_back(p);graph[p].push_back(v);}
        T c(graph,ri(n));check((int)c.centroid_parent.size()==n,"centroid parent size");int roots=0;
        for(int v=0;v<n;++v){
            roots+=c.centroid_parent[v]==-1;vector<bool> blocked(n);int u=v,steps=0;
            while(c.centroid_parent[u]!=-1){
                int p=c.centroid_parent[u];check(p>=0&&p<n&&++steps<n,"centroid parent valid and acyclic");blocked[p]=true;u=p;
            }
            blocked[v]=true;int total=1,biggest=0;
            for(int start:graph[v])if(!blocked[start]){
                vi q={start};blocked[start]=true;
                for(int j=0;j<(int)q.size();++j)for(int w:graph[q[j]])if(!blocked[w]){blocked[w]=true;q.push_back(w);}
                total+=(int)q.size();biggest=max(biggest,(int)q.size());
            }
            check(biggest<=total/2,"centroid parent hierarchy respects balance");
        }
        check(roots==1,"exactly one centroid root");
    }
}

void test_shortest_path_results() {
    const int inf=negative_example::INF;const ll linf=negative_example::LINF;
    vector<array<int,3>> edges={{0,1,2},{1,2,-1},{0,2,10}};
    auto b=negative_example::bellman_ford(0,4,edges);
    check(!b.cycle&&b.dp[2]==1&&b.dp[3]==linf,"Bellman returns distances and cycle flag");
    check(b.get_path(2)==vi({0,1,2})&&b.get_path(0)==vi({0})&&b.get_path(3).empty(),"Bellman restores returned parents");
    check(run_io("",[&]{negative_example::bellman_ford(0,2,4,edges);})=="Path: 0 1 2\n","Bellman original printing overload retained");
    vector<vi> matrix={{0,2,10,inf},{inf,0,-1,inf},{inf,inf,0,inf},{inf,inf,inf,0}};
    auto f=negative_example::floyd_yorshell(4,matrix);
    check(!f.cycle&&f.dp[0][2]==1&&f.get_path(0,2)==vi({0,1,2}),"Floyd returns next hops and paths");
    check(f.get_path(3,3)==vi({3})&&f.get_path(2,0).empty(),"Floyd diagonal and unreachable paths");
    edges.push_back({2,1,0});b=negative_example::bellman_ford(0,4,edges);
    check(b.cycle&&b.get_path(2).empty(),"Bellman avoids invalid negative-cycle restoration");
    for(int z=0;z<800;++z){
        int n=1+ri(7);edges.clear();matrix.assign(n,vi(n,inf));
        const ll oo=1000000000000LL;vector<vector<ll>> d(n,vector<ll>(n,oo));
        for(int i=0;i<n;++i)d[i][i]=0;
        for(int i=0,m=ri(28);i<m;++i){int u=ri(n),v=ri(n),w=ri(17)-8;edges.push_back({u,v,w});matrix[u][v]=min(matrix[u][v],w);d[u][v]=min(d[u][v],(ll)w);}
        for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)
            if(d[i][k]!=oo&&d[k][j]!=oo)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        auto fw=negative_example::floyd_yorshell(n,matrix);bool cycle=false;
        for(int k=0;k<n;++k)cycle|=d[k][k]<0;
        check(fw.cycle==cycle,"returned Floyd cycle flag oracle");
        for(int s=0;s<n;++s){
            auto bf=negative_example::bellman_ford(s,n,edges);bool reachable_cycle=false;
            for(int k=0;k<n;++k)reachable_cycle|=d[s][k]!=oo&&d[k][k]<0;
            check(bf.cycle==reachable_cycle,"returned Bellman cycle flag oracle");
            for(int t=0;t<n;++t){
                bool affected=false;for(int k=0;k<n;++k)affected|=d[s][k]!=oo&&d[k][k]<0&&d[k][t]!=oo;
                if(affected)continue;
                ll want=d[s][t]==oo?linf:d[s][t];
                check(bf.dp[t]==want&&fw.dp[s][t]==want,"returned finite distances oracle");
                auto check_path=[&](const vi& path){
                    if(want==linf){check(path.empty(),"unreachable returned path");return;}
                    check(!path.empty()&&path.front()==s&&path.back()==t&&path.size()<=(size_t)n,"returned path endpoints");ll sum=0;
                    for(int i=1;i<(int)path.size();++i){int w=matrix[path[i-1]][path[i]];check(w!=inf,"returned path edge exists");sum+=w;}
                    check(sum==want,"returned path weight");
                };
                if(!bf.cycle)check_path(bf.get_path(t));
                if(!fw.cycle)check_path(fw.get_path(s,t));
            }
        }
    }
}

template<class Binary,class Fast>
void check_lca_case(const vector<vi>& graph,int root,Binary& binary,Fast& fast) {
    int n=(int)graph.size();vi parent(n,-1),depth(n),q={root};parent[root]=root;
    for(int i=0;i<(int)q.size();++i)for(int u:graph[q[i]])if(parent[u]==-1){
        parent[u]=q[i];depth[u]=depth[q[i]]+1;q.push_back(u);
    }
    check(binary.depth==depth&&fast.depth==depth,"LCA stores depths for the chosen root");
    check(binary.LOG==max(1,(int)bit_width((unsigned)n)),"LCA LOG depends on tree size");
    check((int)fast.ord.size()==2*n-1,"Euler LCA keeps one current traversal");
    for(int it=0;it<250;++it){
        int u=ri(n),v=ri(n),a=u,b=v;
        while(depth[a]>depth[b])a=parent[a];
        while(depth[b]>depth[a])b=parent[b];
        while(a!=b){a=parent[a];b=parent[b];}
        check(binary.query(u,v)==a&&fast.query(u,v)==a,"LCA objects versus parent climbing");
        check(binary.get_lca(u,v,binary.depth,binary.up)==a,"binary helper retained");
        check(fast.get_lca(u,v,fast.st,fast.first,fast.euler_ord,fast.ord)==a,"Euler helper retained");
    }
}
template<class Binary,class Fast> void test_lca_copy() {
    vector<vi> empty,one(1);Binary zero(0,empty);Fast fzero(0,empty);
    check(zero.up.empty()&&zero.depth.empty()&&fzero.st.empty(),"empty LCA construction");
    zero.solve(0,one);fzero.solve(0,one);
    check(zero.query(0,0)==0&&fzero.query(0,0)==0,"single vertex after LCA rebuild");
    for(int z=0;z<100;++z){
        int n=1+ri(100),root=ri(n);vector<vi> graph(n);
        for(int v=1;v<n;++v){int p=ri(v);graph[v].push_back(p);graph[p].push_back(v);}
        Binary binary(root,graph);Fast fast(root,graph);
        check_lca_case(graph,root,binary,fast);
        Binary other(0,one);Fast fother(0,one);
        check_lca_case(graph,root,binary,fast);
        int next_root=ri(n);binary.solve(next_root,graph);fast.solve(next_root,graph);
        check_lca_case(graph,next_root,binary,fast);
        binary.solve(0,one);fast.solve(0,one);
        check(binary.query(0,0)==0&&fast.query(0,0)==0,"LCA rebuild for another tree size");
    }
    vector<vi> chain(2049);
    for(int i=1;i<(int)chain.size();++i){chain[i-1].push_back(i);chain[i].push_back(i-1);}
    Binary binary(2048,chain);Fast fast(2048,chain);
    check_lca_case(chain,2048,binary,fast);
}

template<template<class> class H,class Segtree> void test_concrete_hld_copy() {
    Segtree sum(vi{1,2,3,4});sum.update(1,3,1000000000000LL);
    check(sum.query(0,3)==3000000000010LL,"concrete HLD tree scales range addition by length");
    check(sum.query(2,2)==1000000000003LL,"concrete HLD tree pushes lazy tags");
    sum.update(2,2,-1000000000000LL);check(sum.query(2,2)==3,"concrete HLD tree point range");
    vector<vi> chain={{1},{0,2},{1}};vi big(3,1000000000);
    H<Segtree> wide(0,chain,big);check(wide.query(0,2)==3000000000LL,"ready HLD wide sum");
    wide.update(0,2,1000000000);check(wide.query(0,2)==6000000000LL,"ready HLD wide update");
    for(int z=0;z<70;++z){
        int n=1+ri(65),root=ri(n);vector<vi> graph(n);vi initial(n);
        for(int& x:initial)x=(ri(2001)-1000)*1000000;
        for(int v=1;v<n;++v){int p=ri(v);graph[v].push_back(p);graph[p].push_back(v);}
        vi parent(n,-1),depth(n),q={root};parent[root]=root;
        for(int i=0;i<(int)q.size();++i)for(int v:graph[q[i]])if(parent[v]==-1){parent[v]=q[i];depth[v]=depth[q[i]]+1;q.push_back(v);}
        H<Segtree> h(root,graph,initial);vector<ll> values(initial.begin(),initial.end());
        for(int it=0;it<250;++it){
            int u=ri(n),v=ri(n),x=u,y=v;vi path,tail;
            while(depth[x]>depth[y]){path.push_back(x);x=parent[x];}
            while(depth[y]>depth[x]){tail.push_back(y);y=parent[y];}
            while(x!=y){path.push_back(x);tail.push_back(y);x=parent[x];y=parent[y];}
            path.push_back(x);reverse(tail.begin(),tail.end());path.insert(path.end(),tail.begin(),tail.end());
            ll expected=0;for(int w:path)expected+=values[w];
            check(h.query(u,v)==expected&&h.lca(u,v)==x,"ready HLD versus explicit path");
            int delta=(ri(2001)-1000)*1000000;h.update(u,v,delta);for(int w:path)values[w]+=delta;
            if(it%30==0){
                int s=ri(n);vi subtree={s};for(int j=0;j<(int)subtree.size();++j)for(int w:graph[subtree[j]])if(parent[w]==subtree[j]&&w!=root)subtree.push_back(w);
                ll total=0;for(int w:subtree)total+=values[w];
                check((int)subtree.size()==h.size[s]&&h.tr.query(h.pos[s],h.pos[s]+h.size[s]-1)==total,"ready HLD subtree interval");
            }
        }
    }
}

void test_sparse_and_topo_interfaces() {
    for(int z=0;z<100;++z){
        int n=1+ri(80);vi a(n);for(int& x:a)x=ri(2001)-1000;
        if(z%3==0)a[0]=INT_MAX;if(z%5==0)a[n-1]=INT_MIN;
        const sparse_example::SparseTable table(a);
        for(int l=0;l<n;++l)for(int r=l;r<n;++r)
            check(table.query(l,r)==*min_element(a.begin()+l,a.begin()+r+1),"SparseTable versus range minimum");
    }
    check(run_io("5\n7 2 9 1 5\n4\n0 4\n0 0\n1 2\n3 4\n",[]{sparse_example::solve();})=="1\n7\n2\n1\n","sparse table IO example retained");
    check(run_io("3 3\n0 1\n1 2\n2 0\n",[]{topo_example::solve();})=="cycle is found\n","topo cycle example returns without exiting");
    check(run_io("3 2\n0 1\n1 2\n",[]{topo_example::solve();})=="0 1 2 ","topo valid call after cycle");
    for(int z=0;z<1200;++z){
        int n=ri(9),m=n?ri(26):0;vector<vi> graph(n);vi indegree(n);
        for(int i=0;i<m;++i){int u=ri(n),v=ri(n);graph[u].push_back(v);++indegree[v];}
        vi q;for(int v=0;v<n;++v)if(indegree[v]==0)q.push_back(v);
        for(int i=0;i<(int)q.size();++i)for(int v:graph[q[i]])if(--indegree[v]==0)q.push_back(v);
        bool want=(int)q.size()==n,ok=true;vi color(n),answer;
        check(run_io("",[&]{for(int v=0;v<n;++v)if(!color[v]&&!topo_example::topo_sort(v,graph,color,answer)){ok=false;break;}}).empty(),"topo DFS does not print");
        check(ok==want,"topo cycle flag versus Kahn");
        if(ok){
            reverse(answer.begin(),answer.end());check((int)answer.size()==n,"topo visits all vertices");vi pos(n,-1);
            for(int i=0;i<n;++i){int v=answer[i];check(v>=0&&v<n&&pos[v]==-1,"topo is a permutation");pos[v]=i;}
            for(int u=0;u<n;++u)for(int v:graph[u])check(pos[u]<pos[v],"topo edge order");
        }
    }
}

int main() {
    test_treap_copy<treap_example::ImplTreap>();
    test_treap_copy<exam_example::ImplTreap>();
    test_lcis();test_modint_gauss();test_pool_and_bits();
    test_sat_copy<sat_example::TWO_SAT>();test_sat_copy<exam_example::TWO_SAT>();
    test_zero_based();test_floyd_and_factor();
    test_wide_segment_values();
    test_multigraph_copy<lowlink_example::bridges::dfs,lowlink_example::dots::dfs,
                         lowlink_example::bridges::solve,lowlink_example::dots::solve>();
    test_multigraph_copy<exam_example::bridges::dfs,exam_example::dots::dfs,
                         exam_example::bridges::solve,exam_example::dots::solve>();
    test_centroid_parents<centroid_example::centroid_decomp>();
    test_centroid_parents<exam_example::centroid_decomp>();
    test_shortest_path_results();
    test_lca_copy<lca_example::LCA,lca_example::fast_LCA>();
    test_lca_copy<exam_example::LCA,exam_example::fast_LCA>();
    test_concrete_hld_copy<hld_example::HLD,hld_example::HldSegtree>();
    test_concrete_hld_copy<exam_example::HLD,exam_example::HldSegtree>();
    test_sparse_and_topo_interfaces();
    cout<<"Approved regression tests passed\n";
}
