#include <fstream>
#include <set>

class BinarySearchTree{
private:
    //fields
    struct Node{
        //fields
        long long value;
        Node* left;
        Node* right;
        Node* parent;
        long long height;
        long long depth;
        //constructor
        Node(long long value, Node* parent){
            this->value=value;
            left=NULL;
            right=NULL;
            this->parent=parent;
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
            countDepth(node->left);
            countDepth(node->right);
        }
    }
    long long max(long long a, long long b){
        return a>b ? a : b;
    }
    long long max(long long a, long long b, long long c){
        long long m1=max(a,b);
        long long m2=max(b,c);
        return max(m1,m2);
    }
    long long getMaxHalfWay(Node* node){
        long long distU=maxDist(node);
        if(node->left==NULL && node->right==NULL){
            return distU;
        } else if(node->left==NULL){
            return distU+node->right->height+1;
        } else if(node->right==NULL){
            return distU+node->left->height+1;
        } else{
            return max(distU+node->right->height +1,
                       distU+node->left->height +1,
                       node->right->height + node->left->height+2);
        }
    }
    long long maxDist(Node* node){
        Node* parent=node->parent;
        Node* u=node;
        long long distU=0;
        long long maxDist=-1, currDist=-1;
        do {
            distU++;
            if(u->value < parent->value){
                if(parent->right!=NULL){
                    currDist=distU+parent->right->height+1;
                }
            } else if(u->value > parent->value){
                if(parent->left!=NULL){
                    currDist=distU+parent->left->height+1;
                }
            }
            u=parent;
            parent=u->parent;
            maxDist=max(maxDist,currDist);
        } while (parent!=NULL);
        return maxDist;
    }
    Node* getNode(Node* node,long long value){
        if(node==NULL || node->value==value){
            return node;
        }else if(value<node->value){
            return getNode(node->left, value);
        }else{
            return getNode(node->right, value);
        }
    }
    std::set<long long> getDistToLeafsSetDown(Node* node){
        std::set<long long> distSet;
        postOder(node, distSet, node->depth);
        return distSet;
    }
    void postOder(Node* node,std::set<long long>& distSet, long long depth){
        if(node!=NULL){
            postOder(node->left, distSet, depth);
            postOder(node->right, distSet, depth);
            if(node->left==NULL && node->right==NULL){
                distSet.insert(node->depth-depth);
            }
        }
    }
    std::set<long long> getDistToLeafsSetUp(Node* node){
        std::set<long long> distSet;
        if (cur == NULL) return;
        if (cur == head){
            calcUp(cur->left);
            calcUp(cur->right);
            return;
        }
        if (cur->parent){
            for (int it = 0; it < k; it++)
                if (cur->parent->up[it] == 1) cur->up[it + 1] = 1;
        }
        if (cur -> parent && cur -> parent -> right && cur -> parent -> left == cur){
            for (int it = 0; it < k; it++)
                if (cur->parent->right->down[it] == 1) cur->up[it + 2] = 1;
        }
        if (cur->parent && cur->parent->left && cur->parent->right == cur){
            for (int it = 0; it < k; it++)
                if (cur->parent->left->down[it] == 1) cur->up[it + 2] = 1;
        }
        calcUp(cur->left);
        calcUp(cur->right);
    }
public:
    //constructors
    BinarySearchTree(){
        root=NULL;
    }
    BinarySearchTree(long long value){
        root=new Node(value, NULL);
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
    long long getHeight(){
        return root->height;
    }
    long long getMaxHalfWay(long long value){
        return getMaxHalfWay(getNode(root,value));
    }
    std::set<long long> getDistToLeafsSetDown(long long value){
        return getDistToLeafsSetDown(getNode(root, value));
    }
    void algorithm(long long value){
        
    }
};

int main(int argc, const char * argv[]) {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    BinarySearchTree* tree= new BinarySearchTree();
    long long value;
    while ( (fin>>value) ){
        tree->addNode(value);
    }
    tree->countHeight();
    tree->countDepth();
    tree->algorithm(value);
    tree->writePreOrder(fout);
    delete tree;
    return 0;
}





