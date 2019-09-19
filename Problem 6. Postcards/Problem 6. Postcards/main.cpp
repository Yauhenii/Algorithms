#include <fstream>
#include <vector>
#include <math.h>


std::vector<int> matching;
std::vector<bool> used;
std::vector<std::vector<int>> graph;

struct Dimension{
    int w,h;
};

void swap(double& a,double& b){
    if(a<b){
        int t=a;
        a=b;
        b=t;
    }
}

bool isIn(Dimension card, Dimension cover){
    double p,q,a,b;
    p=(double)card.w;
    q=(double)card.h;
    a=(double)cover.w;
    b=(double)cover.h;
    swap(p, q);
    swap(a, b);
    bool ans1 =((p <= a) && (q <= b));
    bool ans2 = q <= b && (p <= a || b * (p*p+q*q) >= (2*p*q*a + (p*p-q*q)*sqrt(p*p+q*q-a*a)));
    return ans1 || ans2;
}

bool dfs(int i){
    if(used[i]){
        return false;
    }
    used[i]=true;
    for(int j=0;j<graph[i].size();j++){
        int v=graph[i][j];
        if(matching[v]==-1 || dfs(matching[v])){
            matching[v]=i;
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    
    std::ifstream fin("input.in");
    std::ofstream fout("output.out");
    int n;
    fin>>n;
    
    std::vector<Dimension> cards;
    std::vector<Dimension> covers;
    
    int w,h;
    for(int i=0; i<n;i++){
        fin>>w>>h;
        Dimension dim={w,h};
        cards.push_back(dim);
    }
    for(int i=0; i<n;i++){
        fin>>w>>h;
        Dimension dim={w,h};
        covers.push_back(dim);
    }
    fin.close();
    
    graph.resize(n);
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(isIn(cards[i],covers[j])){
                graph[i].push_back(j);
            }
        }
    }
    
    //    matching.resize(n);
    //    used.resize(n);
    //    std::fill(matching.begin(), matching.end(), -1);
    matching.assign(n,-1);
    
    int counter=0;
    
    for(int i=0;i<n;i++){
        //std::fill(used.begin(), used.end(), false);
        used.assign(n, false);
        if(dfs(i)){
            counter++;
        }
    }
    
    if(counter==n){
        fout<<"YES\n";
    } else{
        fout<<"NO\n"<<counter<<"\n";
    }
    fout.close();
    
    return 0;
}





