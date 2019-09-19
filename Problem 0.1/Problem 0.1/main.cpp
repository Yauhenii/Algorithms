#include <fstream>

class BinarySearchTree{
private:
    //fields
    struct Node{
        //fields
        int value;
        Node* left;
        Node* right;
        //constructor
        Node(int value){
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
    void addNode(Node*& node, int value){
        if(node==NULL){
            node=new Node(value);
        }else if(node->value > value){
            addNode(node->left,value);
        }else{
            addNode(node->right,value);
        }
    }
    bool find(Node* node,int value){
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
    void writeInOrder(Node* node,std::ofstream &fout){
        if(node!=NULL){
            fout<<node->value<<"\n";
            writeInOrder(node->left, fout);
            writeInOrder(node->right, fout);
        }
    }
public:
    //constructors
    BinarySearchTree(){
        root=NULL;
    }
    BinarySearchTree(int value){
        root=new Node(value);
    }
    //destructor
    ~BinarySearchTree(){
        freeMemory(root);
    }
    //methods
    void addNode(int value){
        addNode(root, value);
    }
    void writeInOrder(std::ofstream& fout){
        writeInOrder(root, fout);
    }
    bool find(int value){
        return find(root, value);
    }
};

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    BinarySearchTree* tree= new BinarySearchTree();
    int value;
    while ( (fin>>value) )
    {
        if(!tree->find(value)){
            tree->addNode(value);
        }
    }
    
    tree->writeInOrder(fout);
    delete tree;
    return 0;
}



