#include <fstream>
#include <vector>

using namespace std;

struct Arc {
    int b, u, c, f;
    size_t back;
};

class Graph{
private:
    const int INF = 1000*1000*1000;
    int n;
    int m;
    int s;
    int t;
    int k=INF;
    
    int flow;
    int cost;
    
    vector < vector<Arc> > adjList;
    
    vector<int> id;
    vector<int> d;
    vector<int> q;
    vector<int> p;
    vector<size_t> p_rib;
    
    void add(int a, int b, int u, int c) {
        Arc r1 = { b, u, c, 0, adjList[b].size() };
        Arc r2 = { a, 0, -c, 0, adjList[a].size() };
        adjList[a].push_back (r1);
        adjList[b].push_back (r2);
    }
public:
    Graph(){
        flow = 0;
        cost = 0;
    }
    void readGraph(std::ifstream& fin){
        fin>>n>>m>>s>>t;
        s--;
        t--;
        adjList.resize(n);
        id.resize(n);
        d.resize(n);
        q.resize(n);
        p.resize(n);
        p_rib.resize(n);
        int a,b,p,c;
        for(int i=0;i<m;i++){
            fin>>a>>b>>p>>c;
            add(a-1, b-1, p, c);
            add(b-1, a-1, p, c);
        }
    }
    void count(){
        while (flow < k) {
            std::fill(id.begin(), id.end(), 0);
            std::fill(d.begin(), d.end(), INF);
            int qh=0, qt=0;
            q[qt++] = s;
            d[s] = 0;
            while (qh != qt) {
                int v = q[qh++];
                id[v] = 2;
                if (qh == n)  qh = 0;
                for (size_t i=0; i<adjList[v].size(); ++i) {
                    Arc & r = adjList[v][i];
                    if (r.f < r.u && d[v] + r.c < d[r.b]) {
                        d[r.b] = d[v] + r.c;
                        if (id[r.b] == 2) {
                            if (--qh == -1)  qh = n-1;
                            q[qh] = r.b;
                        }
                        else if (id[r.b] == 0) {
                            q[qt++] = r.b;
                            if (qt == n)  qt = 0;
                        }
                        id[r.b] = 1;
                        p[r.b] = v;
                        p_rib[r.b] = i;
                    }
                }
            }
            if (d[t] == INF)  break;
            int addflow = k - flow;
            for (int v=t; v!=s; v=p[v]) {
                int pv = p[v];
                size_t pr = p_rib[v];
                addflow = min (addflow, adjList[pv][pr].u - adjList[pv][pr].f);
            }
            for (int v=t; v!=s; v=p[v]) {
                int pv = p[v];
                size_t pr = p_rib[v],  r = adjList[pv][pr].back;
                adjList[pv][pr].f += addflow;
                adjList[v][r].f -= addflow;
                cost += adjList[pv][pr].c * addflow;
            }
            flow += addflow;
        }
    }
    int getFlow(){
        return flow;
    }
    int getCost(){
        return cost;
    }
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    Graph gr;
    gr.readGraph(fin);
    gr.count();
    fout<<gr.getFlow()<<"\n"<<gr.getCost()<<"\n";
    return 0;
}
