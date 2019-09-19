#include <fstream>

long long solve(int k,int n);

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n,m;
    fin>>n;
    fin>>m;
    
    long long answer = solve(n,m);
    fout<<answer<<"\n";
    return 0;
}

long long solve(int n,int m){
    long long arr[100001];
    for (long long i = 0; i < m; i++)
    {
        arr[i] = 1;
    }
    for (long long i = 1; i < n; i++)
    {
        for (long long j = 1; j < m; j++)
        {
            arr[j] += arr[j - 1];
            arr[j] %= 1000000007L;
        }
    }
    return arr[m - 1];
}

