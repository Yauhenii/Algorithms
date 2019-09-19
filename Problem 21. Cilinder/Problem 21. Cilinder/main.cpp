#include <fstream>
#include <stack>

int solve(int** arr,int m,int n);

int main(int argc, const char * argv[]) {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    int m,n;
    fin>>m;
    fin>>n;
    int**arr=new int*[m];
    for(int i=0;i<m;i++){
        arr[i]=new int[n];
    }
    
    for(int i=0;i<m; i++){
        for(int j=0; j<n; j++){
            fin>>arr[i][j];
        }
    }
    int answer = solve(arr,m,n);
    fout<<answer<<"\n";
    return 0;
}

int solve(int **arr,int m,int n){
    int marker=2;
    int quantity=1;
    for(int j=0;j<n-1;j++){
        for(int i=0;i<m;i++){
            if(arr[i][j]==0){
                if()
            }
        }
    }
    
}
