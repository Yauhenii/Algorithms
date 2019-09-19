#include <fstream>
#include <vector>

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
        Node* parent;
        //constructor
        Node(long long value, Node* parent){
            this->value=value;
            this->height=0;
            this->depth=0;
            left=NULL;
            right=NULL;
            this->parent=parent;
        }
        //destructor
        //?
    };
    Node* root;
    long long maxHalfWay=INT_MIN;
    long long maxNodeValue=INT_MIN;
    long long minDepth=INT_MAX;
    //methods
    void freeMemory(Node*& node){
        if(node!=NULL){
            freeMemory(node->left);
            freeMemory(node->right);
            delete node;
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
//    void traverse(Node* node){
//        if(node!=NULL){
//
//            traverse(node->left);
//            traverse(node->right);
//        }
//    }
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
    long long countHeight(Node* node){
        if(node==NULL){
            return -1;
        }
        node->height=max(countHeight(node->left),countHeight(node->right))+1;
        return node->height;
    }
    void countDepth(Node* node){
        if(node!=NULL){
            if(node->parent==NULL){
                node->depth=0;
            } else{
                node->depth=node->parent->depth+1;
            }
            long long halfWay=getHalfWay(node);
            if(maxHalfWay<halfWay){
                maxHalfWay=halfWay;
                maxNodeValue=node->value;
                minDepth=node->depth;
            } else if(maxHalfWay==halfWay){
                if(minDepth>node->depth){
                    maxNodeValue=node->value;
                    minDepth=node->depth;
                }
            }
            countDepth(node->left);
            countDepth(node->right);
        }
    }
    long long max(long long a,long long b){
        return a>b ? a : b;
    }
    long long getHalfWay(Node* node){
        if(node->left && node->right){
            return node->left->height+node->right->height+2;
        } else if(node->left){
            return node->left->height+1;
        } else if(node->right){
            return node->right->height+1;
        } else{
            return 0;
        }
    }
public:
    //constructors
    BinarySearchTree(){
        root=NULL;
    }
    BinarySearchTree(int value){
        root=new Node(value,NULL);
    }
    //destructor
    ~BinarySearchTree(){
        freeMemory(root);
    }
    //methods
    void addNode(long long value){
        if(root==NULL){
            root=new Node(value,NULL);
            return;
        }
        Node* parent=NULL;
        Node* u=root;
        while (u!=NULL) {
            parent=u;
            if(value<u->value){
                u=u->left;
            }else if(value>u->value){
                u=u->right;
            } else{
                return;
            }
        }
        if(value<parent->value){
            parent->left=new Node(value,parent);
        } else if(value>parent->value){
            parent->right=new Node(value,parent);
        }
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
    void countHeight(){
        countHeight(root);
    }
    void countDepth(){
        countDepth(root);
    }
    long long getMaxValue(){
        return maxNodeValue;
    }
};

int main(int argc, const char * argv[]) {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    BinarySearchTree* tree= new BinarySearchTree();
    long long value;
    while ( (fin>>value) )
    {
        if(!tree->find(value)){
            tree->addNode(value);
        }
    }
    fin.close();
    tree->countHeight();
    tree->countDepth();
    tree->deleteNode(tree->getMaxValue());
    tree->writePreOrder(fout);
    delete tree;
    fout.close();
    return 0;
}



