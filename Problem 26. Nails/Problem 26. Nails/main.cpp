#include <fstream>
#include<iomanip>

double* arr;
double* dp;
int n;

double min(double a,double b);
double getMinLen();

int main(int argc, const char * argv[]) {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    double lenght;
    fin>>n;
    arr=new double[n];
    for(int i=0;i<n;i++){
        fin>>arr[i];
    }
    dp=new double[n];
    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    lenght=getMinLen();
    fout<<std::fixed;
    fout<<std::setprecision(2)<<lenght<<"\n";
    return 0;
}
double min(double a,double b){
    return a<b ? a : b;
}
double getMinLen(){
    dp[1] = arr[1] - arr[0];
    double delta;
    for(int i = 1; i < n-1; i++){
        delta=arr[i+1] - arr[i];
        dp[i+1] = min(dp[i], dp[i-1])+delta;
    }
    return dp[n - 1];
}

