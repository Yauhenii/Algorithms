#include <fstream>
#include <queue>
int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n;
    fin>>n;
    //init and read adj matrix
    int* mark=new int[n];
    int* path=new int[n];
    bool** adj=new bool*[n];
    for(int i=0;i<n;i++){
        adj[i]=new bool[n];
    }
    bool* visit=new bool[n];
    std::queue<int> fifo;
    for(int i=0;i<n;i++){
        path[i]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fin>>adj[i][j];
            if(adj[i][j]){
                path[j]=i+1;
            }
        }
    }
    for(int i=0;i<n;i++){
        visit[i]=false;
    }
    
    int m=0;
    
    for(int i=0;i<n;i++){
        if(!visit[i]){
            fifo.push(i);
            visit[i]=true;
            m++;
            mark[i]=m;
            while (!fifo.empty()) {
                int e=fifo.front();
                fifo.pop();
                for(int i=0;i<n;i++){
                    if(adj[e][i]&&!visit[i]){
                        mark[i]=m+1;
                        m++;
                        visit[i]=true;
                        fifo.push(i);
                    }
                }
            }
        }
    }
    
    for (int i=0; i<n; i++) {
        fout<<mark[i]<<" ";
    }
    fout<<"\n";
    return 0;
}
