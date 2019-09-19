#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
using std::vector;
using std::ifstream;
using std::ofstream;
using std::endl;

class HalfPath{
    vector<int> nodes;
    
    HalfPath(){}
    
    bool add(int key) {
        return nodes.push_back(key);
    }
    int size(){
        return nodes.size() - 1;
    }
    bool contains(int key){
        return std::find(nodes.begin(), nodes.end(), <#const _Tp &__value_#>)(key);
    }
    
};

int main() {
    
    Tree tree;
    
    ifstream in("tst.in");
    ofstream out("tst.out");
    long long k,val;
    in>>k;
    int num_of_verticles = 0;
    while (!in.eof()) {
        in>>val;
            tree.insert(val, k);
            num_of_verticles++;
    }
    if (k < 1000) {
        
        
        if (num_of_verticles == 0 || num_of_verticles == 1 && k!=0) {
            out << "Empty" << endl;
        }
        //left-right-up
        
        
        else
        {
            if (num_of_verticles == 1 && k == 0) {
                out << tree.getroot()->key << endl;
            }
            else {
                Node* new_root = tree.getroot();
                postorder(tree.getroot(), new_root, k);
                if (tree.getroot()->left_son == NULL) {
                    tree.getroot()->left_pathes[0] = true;
                }
                if (tree.getroot()->right_son == NULL) {
                    tree.getroot()->right_pathes[0] = true;
                }
                Node* max = preorder(tree.getroot(), k);
                tree.remove(max);
                write(tree.getroot(), out);
            }
            
        }
    }
    
    else
    {
        if (num_of_verticles == 0 || num_of_verticles == 1) {
            out << "Empty" << endl;
        }
        else {
            
            Node*next = tree.getroot();
            while (next->right_son != NULL) {
                next = next->right_son;
            }
            tree.remove(next);
            write(tree.getroot(), out);
        }
    }
    return 0;
}
