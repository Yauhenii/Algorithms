#include <fstream>

class BinarySearchTree{
private:
    //fields
    struct Node{
        //fields
        long long value;
        Node* left;
        Node* right;
        //constructor
        Node(long long value){
            this->value=value;
            left=NULL;
            right=NULL;
        }
        //destructor
        //?
    };
    Node* root;
    //methods
    void freeMemory(Node*& node){
        if(node!=NULL){
            freeMemory(node->left);
            freeMemory(node->right);
            delete node;
        }
    }
    void addNode(Node*& node, long long value){
        if(node==NULL){
            node=new Node(value);
        }else if(node->value > value){
            addNode(node->left,value);
        }else{
            addNode(node->right,value);
        }
    }
    void getNodeSum(Node* node,long long& sum){
        if(node!=NULL){
            sum+=node->value;
            getNodeSum(node->left, sum);
            getNodeSum(node->right, sum);
        }
    }
    bool find(Node* node,long long value){
        if(node==NULL){
            return false;
        } else {
            if(node->value==value){
                return true;
            }
            else if(node->value > value){
                return find(node->left, value);
            }
            else {
                return find(node->right, value);
            }
        }
    }
public:
    //constructors
    BinarySearchTree(){
        root=NULL;
    }
    BinarySearchTree(long long value){
        root=new Node(value);
    }
    //destructor
    ~BinarySearchTree(){
        freeMemory(root);
    }
    //methods
    void addNode(long long value){
        addNode(root, value);
    }
    long long getNodeSum(){
        long long sum=0;
        getNodeSum(root, sum);
        return sum;
    }
    bool find(long long value){
        return find(root, value);
    }
};

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    BinarySearchTree* tree= new BinarySearchTree();
    long long value;
    while ( (fin>>value) )
    {
        if(!tree->find(value)){
            tree->addNode(value);
        }
    }
    fout<<tree->getNodeSum()<<"\n";
    delete tree;
    return 0;
}
