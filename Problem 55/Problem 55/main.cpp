#include <fstream>

bool isHeap(int* arr,int n);

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int* arr;
    int n;
    fin>>n;
    arr=new int[n];
    for(int i=0; i<n; i++){
        fin>>arr[i];
    }
    if(isHeap(arr,n)){
        fout<<"Yes\n";
    } else{
        fout<<"No\n";
    }
    return 0;
}

bool isHeap(int* arr,int n){
    for(int i=0;i<(n-2)/2+1;i++){
        if(arr[i]>arr[2*i+1]){
            return false;
        }
        if(2*i+2 < n && arr[i]>arr[2*i+2]){
            return false;
        }
    }
    return true;
}

