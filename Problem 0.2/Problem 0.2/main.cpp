#include <fstream>

class BinarySearchTree{
private:
    //fields
    struct Node{
        //fields
        long long value;
        long long height;
        long long depth;
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
    void writePreOrder(Node* node,std::ofstream &fout){
        if(node!=NULL){
            fout<<node->value<<"\n";
            writePreOrder(node->left, fout);
            writePreOrder(node->right, fout);
        }
    }
    long long getMinValue(Node* node){
        long long minValue=node->value;
        while (node->left!=NULL) {
            minValue=node->left->value;
            node=node->left;
        }
        return minValue;
    }
    void deleteNode(Node*& node,long long  value){
        if(node==NULL){
        
        }else if(node->value > value){
            deleteNode(node->left, value);
        } else if(node->value < value){
            deleteNode(node->right, value);
        } else{
            if(node->left==NULL){
                Node* tempNode = node->right;
                delete node;
                node=tempNode;
            }else if(node->right==NULL){
                Node*tempNode = node->left;
                delete node;
                node=tempNode;
            }else{
            node->value=getMinValue(node->right);
            deleteNode(node->right, node->value);
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
    void writePreOrder(std::ofstream& fout){
        writePreOrder(root, fout);
    }
    bool find(long long value){
        return find(root, value);
    }
    void deleteNode(long long value){
        deleteNode(root, value);
    }
    void countHeight(long long value);
};

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    BinarySearchTree* tree= new BinarySearchTree();
    long long value;
    while (fin>>value) {
        if(!tree->find(value)){
            tree->addNode(value);
        }
    }
    
    int valueToDelete;
    fin>>valueToDelete;
    tree->deleteNode(valueToDelete);
    tree->writePreOrder(fout);
    delete tree;
    return 0;
}



