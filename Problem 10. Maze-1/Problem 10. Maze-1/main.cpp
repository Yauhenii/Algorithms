#include <fstream>
#include <stack>

struct Triplet{
    long long first;
    long long second;
    long long third;
    Triplet(long long f,long long s,long long t){
        first=f;
        second=s;
        third=t;
    }
    Triplet(std::pair<long long, long long> p,long long t){
        first=p.first;
        second=p.second;
        third=t;
    }
};

class Maze{
private:
    enum direction {LEFT,DOWN,RIGHT,UP};
    
    
    long long* fromUp=new long long[3]{RIGHT, UP,LEFT};
    long long* fromDown=new long long[3]{LEFT, DOWN, RIGHT};
    long long* fromLeft=new long long[3]{UP,LEFT, DOWN};
    long long* fromRight=new long long[3]{DOWN, RIGHT, UP};
    
    long long n;
    long long m;
    long long **maze;
    
    //    int* availDir;
    
public:
    Maze(){
    }
    void readMaze(std::ifstream& fin){
        fin>>n;
        fin>>m;
        //init maze
        maze=new long long*[n];
        for(long long i=0;i<n;i++){
            maze[i]=new long long[m];
        }
        //fill default maze
        char t;
        for(long long i=0;i<n;i++){
            for(long long j=0;j<m;j++){
                fin>>t;
                maze[i][j]=t-'0';
            }
        }
    }
    
    bool step(std::stack<Triplet> st){
        while (!st.empty()) {
            long long dx,dy;
            switch (st.top().third) {
                case UP:
                    dx=-1;
                    dy=0;
                    break;
                case DOWN:
                    dx=1;
                    dy=0;
                    break;
                case LEFT:
                    dx=0;
                    dy=-1;
                    break;
                case RIGHT:
                    dx=0;
                    dy=1;
                    break;
                default:
                    dx=n;
                    dy=m;
                    break;
            }
            std::pair<long long, long long> next=std::make_pair(st.top().first+dx, st.top().second+dy);
            
            if(isOut(next)){
                st.pop();
                continue;
            }
            maze[next.first][next.second]=2;
            if(next.first==n-1){
                return true;
            }
            long long* availDir;
            switch (st.top().third) {
                case UP:
                    availDir=fromUp;
                    break;
                case DOWN:
                    availDir=fromDown;
                    break;
                case LEFT:
                    availDir=fromLeft;
                    break;
                case RIGHT:
                    availDir=fromRight;
                    break;
                default:
                    availDir=NULL;
                    break;
            }
            st.pop();
            for(long long i=2;i>=0;i--){
                st.push(Triplet(next,availDir[i]));
            }
        }
        return false;
    }
    bool isOut(const std::pair<long long, long long>& point){
        return (point.first<0 || point.second<0 || point.first>=n || point.second>=m || maze[point.first][point.second]!=0);
    }
    bool getAnswer(){
        //algorithm
        if(n==1){
            for(long long i=0;i<m;i++){
                if(maze[0][i]==0){
                    return true;
                }
            }
            return false;
        }
        else{
            bool answer=false;
            for(long long i=0;i<m;i++){
                if(maze[0][i]==0){
                    maze[0][i]=2;
                    std::stack<Triplet> st;
                    st.push(Triplet(0,i,DOWN));
                    if(!step(st)){
                        answer= false;
                        break;
                    }
                    answer =true;
                }
            }
            return answer;
        }
    }
    void printAnswer(std::ofstream& fout){
        if(getAnswer()==false){
            fout<<"Impossible\n";
        } else{
            fout<<"Possible\n";
        }
//                for(int i=0;i<n;i++){
//                    for(int j=0;j<m;j++){
//                        fout<<maze[i][j];
//                    }
//                    fout<<"\n";
//                }
    }
};

int main(int argc, const char * argv[]) {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    Maze mz;
    mz.readMaze(fin);
    mz.printAnswer(fout);
    return 0;
}
