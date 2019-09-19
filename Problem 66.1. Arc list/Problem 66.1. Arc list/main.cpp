#include <fstream>

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n;
    fin>>n;
    int* arr=new int[n];
    for(int i=0;i<n;i++){
        arr[i]=0;
    }
    int u,v;
    for(int i=0;i<n-1;i++){
        fin>>u;
        fin>>v;
        arr[v-1]=u;
    }
    for(int i=0;i<n;i++){
        fout<<arr[i]<<" ";
    }
    fout<<"\n";
    return 0;
}
