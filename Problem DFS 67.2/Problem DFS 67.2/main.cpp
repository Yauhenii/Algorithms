#include <fstream>
#include <stack>

int* mark;
bool** adj;
bool* visit;
int n;
int tim;

void dfs(int i);

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    fin>>n;
    //init and read adj matrix
    mark=new int[n];
    adj=new bool*[n];
    for(int i=0;i<n;i++){
        adj[i]=new bool[n];
    }
    visit=new bool[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fin>>adj[i][j];
        }
    }
    for(int i=0;i<n;i++){
        visit[i]=false;
    }
    
    tim=0;
    
    for(int i=0;i<n;i++){
        if(!visit[i]){
            dfs(i);
        }
    }
    
    for (int i=0; i<n; i++) {
        fout<<mark[i]<<" ";
    }
    fout<<"\n";
    return 0;
}

void dfs(int v){
    visit[v]=true;
    tim++;
    mark[v]=tim;
    for(int i=0;i<n;i++){
        if(adj[v][i]&&!visit[i]){
            dfs(i);
        }
    }
}

