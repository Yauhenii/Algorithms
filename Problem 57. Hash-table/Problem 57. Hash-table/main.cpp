#include <fstream>
#include <vector>

class HashTable{
private:
    int c;
    int m;
public:
    
    std::vector<int> table;
    
    HashTable(int m,int c){
        this->m=m;
        this->c=c;
        table.resize(m);
        for(int i=0;i<m;i++){
            table[i]=-1;
        }
    }
    
    void add(int x){
        int i=0;
        int h=hash(x, i);
        while(true){
            if(table[h]==-1){
                table[h]=x;
            } else if(table[h]==x){
                break;
            } else{
                h=hash(x,i++);
            }
        }
    }
    
    int hash(int x,int i){
        return ((x%m)+c*i)%m;
    }
};


int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int m,c,n;
    fin>>m;
    fin>>c;
    fin>>n;
    HashTable hTable(m,c);
    int x;
    for(int i=0;i<n;i++){
        fin>>x;
        hTable.add(x);
    }
    for(int i=0;i<m;i++){
        fout<<hTable.table[i]<<" ";
    }
    fout<<"\n";
    return 0;
}

