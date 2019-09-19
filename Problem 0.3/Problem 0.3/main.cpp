#include <fstream>

int getOperationsQuantity(int** A, int n);

int min(int a, int b){
    return a<b ? a : b;
}

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int quantity;
    fin>>quantity;
    int**A= new int*[2];
    for(int i=0;i<2;i++){
        A[i]=new int[quantity];
    }
    int m,n;
    for(int i=0;i<quantity; i++){
        fin>>m;
        fin>>n;
        A[0][i]=m;
        A[1][i]=n;
    }
    fout<<getOperationsQuantity(A, quantity)<<"\n";
    return 0;
}

int getOperationsQuantity(int** A, int n){
    int** dp = new int*[n];
    for(int i=0;i<n;i++){
        dp[i]=new int[n];
    }
    for(int r=0;r<n;r++){
        for(int l=r;l>=0; l--){
            dp[l][r]=INT_MAX;
            if(l==r){
                dp[l][r]=0;
                continue;
            }
            for(int k=l;k!=r; k++){
                dp[l][r]=min(dp[l][r], dp[l][k]+dp[k+1][r]+A[0][l]*A[1][k]*A[1][r]);
            }
        }
    }
    return dp[0][n-1];
}



