#include <fstream>

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n;
    fin>>n;
    
    bool** adj=new bool*[n];
    for(int i=0;i<n;i++){
        adj[i]=new bool[n];
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fin>>adj[i][j];
        }
    }
    
    int* arr=new int[n];
    
    for(int i=0;i<n;i++){
        arr[i]=0;
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adj[i][j]){
                arr[j]=i+1;
            }
        }
    }
    
    for(int i=0;i<n;i++){
        fout<<arr[i]<<" ";
    }
    
    fout<<"\n";
    return 0;
}
