#include <fstream>
#include <queue>
#include <vector>

int min(int a,int b){
    return a<b ? a : b;
}

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n;
    int m;
    fin>>n>>m;
    std::vector < std::vector < std::pair<int,int> > > g (n); //adj list
    int u,v,c;
    for(int i=0;i<m;i++){
        fin>>u>>v>>c;
        g[u-1].push_back(std::make_pair(v-1, c)); //u->{v,c}
        g[v-1].push_back(std::make_pair(u-1, c)); //u->{v,c}
    }
    std::vector<int> d (n, INT_MAX);
    std::vector<bool> visited(n,false);
    d[0] = 0;
    auto compG = []( std::pair<int,int>  a, std::pair<int,int> b ) {
        if(a.second==b.second){
            return a.first > b.first;
        } else{
            return a.second < b.second;
        }
    };
    std::priority_queue < std::pair<int,int>,std::vector<std::pair<int,int>>, decltype(compG)> q(compG);
    q.push (std::make_pair (0, 0)); //val, d
    while (!q.empty()) {
        std::pair<int, int> node=q.top();
        q.pop();
        if (visited[node.first])  {
            continue;
        }
        visited[node.first]=true;
        for (size_t j=0; j<g[node.first].size(); ++j) {
            if(visited[g[node.first][j].first]){
                q.push(std::make_pair(j, node.second+g[node.first][j].second));
                d[j]=min(node.second+g[node.first][j].second, d[j]);
            }
        }
    }
//    while (!q.empty()) {
//        int v = q.top().second,  cur_d = -q.top().first;
//        q.pop();
//        if (cur_d > d[v])  continue;
//        for (size_t j=0; j<g[v].size(); ++j) {
//            int to = g[v][j].first,
//            len = g[v][j].second;
//            if (d[v] + len < d[to]) {
//                d[to] = d[v] + len;
//                q.push (std::make_pair (-d[to], to));
//            }
//        }
//    }
    fout<<d[n-1]<<"\n";
    return 0;
}
