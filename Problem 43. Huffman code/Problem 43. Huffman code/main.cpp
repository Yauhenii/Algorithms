#include <fstream>
#include <queue>
#include <vector>

class BinarySearchTree{
private:
    //fields
    struct Node{
        //fields
        long long value;
        long long depth;
        Node* left;
        Node* right;
        Node* parent;
        //constructor
        Node(long long value){
            this->value=value;
            left=NULL;
            right=NULL;
            parent=NULL;
        }
        //method
        bool isLeaf(){
            if(left==NULL && right==NULL){
                return true;
            }
            return false;
        }
    };
    Node* root;
    long long answer=0;
    //methods
    void freeMemory(Node*& node){
        if(node!=NULL){
            freeMemory(node->left);
            freeMemory(node->right);
            delete node;
        }
    }
    void writePreOrder(Node* node,std::ofstream &fout){
        if(node!=NULL){
            writePreOrder(node->left, fout);
            writePreOrder(node->right, fout);
        }
    }
    void countDepth(Node* node){
        if(node!=NULL){
            if(node->parent==NULL){
                node->depth=0;
            } else{
                node->depth=node->parent->depth+1;
                if (node->isLeaf()) {
//                    fout<<node->value<<" "<<node->depth<<"\n";
                    answer+=node->value*node->depth;
                }
            }
            countDepth(node->left);
            countDepth(node->right);
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
    //friend function
    friend BinarySearchTree* linkTrees(BinarySearchTree* tree1,BinarySearchTree* tree2);
    //get
    long long getValue(){
        if(root!=NULL){
            return root->value;
        }else{
            return -1;
        }
    }
    //methods
    void writePreOrder(std::ofstream& fout){
        writePreOrder(root, fout);
    }
    void countDepth(){
        countDepth(root);
    }
    long long getAnswer(){
        return answer;
    }
};

struct Comparator {
    bool operator()(BinarySearchTree* b1, BinarySearchTree* b2)
    {
        return b1->getValue() > b2->getValue();
    }
};

BinarySearchTree* linkTrees(BinarySearchTree* tree1,BinarySearchTree* tree2);

int main(int argc, const char * argv[]) {
    std::ifstream fin("huffman.in");
    std::ofstream fout("huffman.out");
    std::priority_queue<BinarySearchTree*,std::vector<BinarySearchTree*>,Comparator> prior;
    
    long long n;
    fin>>n;
    long long quantity;
    for(long long i=0;i<n;i++){
        fin>>quantity;
        prior.push(new BinarySearchTree(quantity));
    }
    BinarySearchTree* b1,* b2;
    for(long long i=0;i<n;i++){
        if(prior.size()>=2){
            b1=prior.top();
            prior.pop();
            b2=prior.top();
            prior.pop();
            b1=linkTrees(b1, b2);
            prior.push(b1);
        } else{
            break;
        }
    }
    prior.top()->countDepth();
    fout<<prior.top()->getAnswer()<<"\n";
    return 0;
}

BinarySearchTree* linkTrees(BinarySearchTree* tree1,BinarySearchTree* tree2){
    long long v1=tree1->getValue();
    long long v2=tree2->getValue();
    BinarySearchTree* tree= new BinarySearchTree(v1+v2);
    if(v1>v2){
        tree->root->right=tree1->root;
        tree->root->left=tree2->root;
    } else{
        tree->root->right=tree2->root;
        tree->root->left=tree1->root;
    }
    tree->root->left->parent=tree->root;
    tree->root->right->parent=tree->root;
    return tree;
}

