#include <fstream>

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n;
    fin>>n;
    int i=0;
    if(n==0){
        fout<<"-1\n";
    }
    while(n!=0){
        if(n%2){
            fout<<i<<"\n";
        }
        n/=2;
        i++;
    }
    return 0;
}


