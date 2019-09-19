#include <fstream>
#include <set>
#include <vector>

typedef std::pair<int, long long> _pair;

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n=0,m;
    fin>>m;
    //works
    auto compG = []( _pair a, _pair b ) {
        if(a.second==b.second){
            return a.first > b.first;
        } else{
            return a.second > b.second;
        }
    };
    std::set<_pair, decltype(compG) > works(compG);
    long long temp;
    while (fin>>temp) {
        n++;
        works.insert(std::make_pair(n, temp));
    }
    fin.close();
    std::vector<int> works_workers(n,0);
    //workers
    auto compL = []( _pair a, _pair b ) {
        if(a.second==b.second){
            return a.first > b.first;
        } else{
            return a.second < b.second;
        }
    };
    std::set<_pair,decltype(compL) > workers(compL);
    for(int i=0;i<m;i++){
        workers.insert(std::make_pair(i+1, 0));
    }
    //algo
    _pair t_work,t_worker;
    while (!works.empty()) {
        t_work=*works.begin();
        works.erase(works.begin());
        t_worker=*workers.begin();
        workers.erase(workers.begin());
        
        works_workers[t_work.first-1]=t_worker.first;
        workers.insert(std::make_pair(t_worker.first, t_worker.second+t_work.second));
    }
    //out
    fout<<(*(--workers.end())).second<<"\n";
    for(int i=0;i<n;i++){
        fout<<works_workers[i]<<" ";
    }
    fout<<"\n";
    fout.close();
    return 0;
}
