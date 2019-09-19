#pragma comment(linker, "/STACK:16777216")
#include <fstream>
#include <algorithm>
#include <set>

class Bush{
public:
    Bush(){
    }
    Bush(int x,int y){
        this->x=x;
        this->y=y;
    }
    int x,y;
    bool operator<(const Bush& obj) const {
        if(x==obj.x){
            return y<obj.y;
        }
        return x<obj.x;
    }
};

int max(int a,int b);
bool compare(Bush a,Bush b);
bool isOut(int x,int y, int r,int c);
int countPath(Bush bush, int distX,int distY,int r,int c);

std::set<Bush> bushesSet;

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    Bush* bushes;
    int r,c;
    int n;
    fin>>r;
    fin>>c;
    fin>>n;
    //read
    int x,y;
    bushes=new Bush[n];
    for(int i=0;i<n;i++){
        fin>>x;
        fin>>y;
        bushes[i].x=x;
        bushes[i].y=y;
        bushesSet.insert(Bush(x,y));
    }
    //sort
    std::sort(bushes, bushes+n, compare);
    //algo
    int distX,distY,nextX,nextY;
    int maxPath=2;
    for(int i=0;i<n-1;i++){
        for(int j=i+1; j<n;j++){
            distX=bushes[j].x-bushes[i].x;
            distY=bushes[j].y-bushes[i].y;
            nextX=bushes[i].x+distX*maxPath;
            nextY=bushes[i].y+distY*maxPath;
            if(nextX > r){
                break;
            }
            if(isOut(bushes[i].x-distX, bushes[i].y-distY,r,c)){
                continue;
            }
            if(!isOut(nextX, nextY,r,c)){
                continue;
            }
            maxPath=max(countPath(bushes[i],distX,distY,r,c),maxPath);
        }
    }
    if(maxPath<3){
        fout<<0<<"\n";
    } else{
        fout<<maxPath<<"\n";
    }
    return 0;
}

bool compare(Bush a,Bush b){
    if(a.x==b.x){
        return a.y<b.y;
    }
    return a.x<b.x;
}

bool isOut(int x,int y, int r,int c){
    return (0 < x && x < r+1 && 0 < y && y < c+1);
}
int countPath(Bush bush, int distX,int distY,int r,int c){
    int path=0;
    while(isOut(bush.x, bush.y, r, c)){
        if(!(bushesSet.find(bush)!=bushesSet.end())){
            return 0;
        }
        bush.x+=distX;
        bush.y+=distY;
        path++;
    }
    return path;
}

int max(int a,int b){
    return a<b ? b : a;
}
