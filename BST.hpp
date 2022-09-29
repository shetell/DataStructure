#include<iostream>
#include<vector>
#include<iomanip>
#include<math.h>
using namespace std;

#define baseInterval 3
#define elementInterval 1

int a = 0;

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BST{
private:

    void InOrderTraversal(BST* bt){
        if(bt){
            InOrderTraversal(bt->left);
            cout << bt->val << " ";
            InOrderTraversal(bt->right);
        }
    }

    BST* insert(int val, BST* bst){
        if(!bst){
            bst = new BST(val);
        }
        else{
            if(val < bst->val){
                bst->left = insert(val,bst->left);
                if(getHeight(bst->left)-getHeight(bst->right) == 2){
                    if(val < bst->left->val)bst = LL_Rotation(bst);
                    else bst = LR_Rotation(bst);
                }
            }
            else if(val > bst->val){
                bst->right = insert(val,bst->right);
                if(getHeight(bst->left)-getHeight(bst->right) == -2){
                    if(val > bst->right->val)bst = RR_Rotation(bst);
                    else bst = RL_Rotation(bst);
                }
            }
        }
        return bst;
    }

    BST* find(int val, BST* bst){
        if(!bst)return NULL;
        if(val > bst->val){
            return find(val,bst->right);
        }
        if(val < bst->val){
            return find(val,bst->left);
        }
        else return bst;
    }

    BST* getNodeCode(int val, BST* bst, vector<int>& code){
        while(bst){
            if(val > bst->val){
                code.push_back(1);
                bst = bst->right;
            }
            else if(val < bst->val){
                code.push_back(0);
                bst = bst->left;
            }
            else return bst;
        }
        return NULL;
    }

    BST* findMax(BST* bst){
        if(!bst)return NULL;
        else if(!bst->right)return bst;
        else return findMax(bst->right);
    }

    BST* findMin(BST* bst){
        if(!bst)return NULL;
        else if(!bst->left)return bst;
        else return findMax(bst->left);
    }

    BST* _Delete(int val, BST* bst){
        BST* temp;
        if(!bst)cout<<"not found"<<endl;
        else if(val < bst->val)bst->left = _Delete(val,bst->left);
        else if(val > bst->val)bst->right = _Delete(val,bst->right);
        else{
            if(bst->left && bst->right){
                temp = findMin(bst->right);
                bst->val = temp->val;
                bst->right = _Delete(bst->val,bst->right);
            }
            else{
                temp = bst;
                if(!bst->left)bst = bst->right;
                else if(!bst->right)bst = bst->left;
                free(temp);
            }
        }
        return bst;
    }

    int getHeight(BST* bst){
        int height;
        if(bst){
            int lheight = getHeight(bst->left);
            int rheight = getHeight(bst->right);
            return ((lheight > rheight)?lheight:rheight) + 1; 
        }
        else return 0;
    }

    BST* LL_Rotation(BST* bst){
        BST* temp = bst->left;
        bst->left = temp->right;
        temp->right = bst;
        return temp;
    }

    BST* RR_Rotation(BST* bst){
        BST* temp = bst->right;
        bst->right = temp->left;
        temp->left = bst;
        return temp;
    }

    BST* LR_Rotation(BST* bst){
        BST *A,*B,*C;
        A = bst;
        B = A->left;
        C = B->right;
        B->right = C->left;
        A->left = C->right;
        C->left = B;
        C->right = A;
        return C;
    }

    BST* RL_Rotation(BST* bst){
        BST *A,*B,*C;
        A = bst;
        B = A->right;
        C = B->left;
        B->left = C->right;
        A->right = C->left;
        C->right = B;
        C->left = A;
        return C;
    }

    

    void getTreeLevel(BST* bst,vector<int>* nums,int depth){
        if(depth <= 0 || bst == NULL)return;
        if(depth == 1){
            nums->push_back(bst->val);
            return;
        }
        getTreeLevel(bst->left,nums,depth-1);
        getTreeLevel(bst->right,nums,depth-1);
    }

    void output_impl(BST* n, bool left, string const& indent){
        if (n->left)
        {
            output_impl(n->left, true, indent + (left ? "      " : "|     "));
        }
        cout << indent;
        cout << (left ? '/' : '\\');
        cout << "-----";
        cout << n->val << endl;
        if (n->right)
        {
            output_impl(n->right, false, indent + (left ? "|     " : "      "));
        }
    }



    class Node{
    public:
        int val;
        int pos;
        Node(int val, int pos){
            this->val = val;
            this->pos = pos;
        }
    };

    int getPos(vector<int> code){
        int pos = 0;
        for(int i = 0; i < code.size(); i++){
            pos += code[code.size()-1-i]*pow(2,i);
        }
        return pos;
    }

    int Interval(int h,int line){
        if(line == h)return baseInterval;
        int interval = Interval(h,line+1)*2+1;
        return interval;
    }

    void drawBaseLine(const int maxSize,vector<Node> Nodes,int interval,int startBlank,int h,int height,BST* bst){
        vector<int> line(maxSize);
        vector<int> dash(maxSize);
        for(int i = 0; i < maxSize; i++){
            line[i] = -1;
            dash[i] = -1;
        }
        for(int i = 0; i < Nodes.size(); i++){
            int j = Nodes[i].pos*(1+interval)+startBlank;
            line[j] = Nodes[i].val;
            if(Nodes[i].val >= 10){
                line[j+1] = -2;
            }          
        }
        if(h != 1){
            for(int i = 0; i < maxSize; i++){
                if(line[i] < 0)cout << " ";
                //else if(line[i] == -2);
                else cout << "|";
            }
            cout << endl;
        }
        for(int i = 0; i < maxSize; i++){
            if(line[i] == -1)cout << " ";
            else if(line[i] == -2);
            else cout << line[i];
        }
        cout << endl;
        if(h != height){
            for(int i = 0; i < maxSize; i++){
                if(line[i] < 0)cout << " ";
                //else if(line[i] == -2);
                else if(bst->Find(line[i])->left || bst->Find(line[i])->right)cout << "|";
                else cout << " ";
            }
            cout << endl;
        }
        if(h != height){       
            for(int i = 0; i < maxSize; i++){
                if(line[i] > -1){
                    int next_interval = Interval(height,h+1);
                    if(bst->Find(line[i])->left){
                        for(int j = i-next_interval/2-1; j <= i;j++){
                            dash[j] = 0;
                        }
                    }
                    if(bst->Find(line[i])->right){
                        for(int j = i; j <= i+next_interval/2+1;j++){
                            dash[j] = 0;
                        }
                    }
                }
            }
            for(int i = 0; i < dash.size(); i++){
                if(dash[i]==-1)cout << " ";
                else cout << "-";
            }
            cout << endl;
        }
    }

    void drawline(BST* bst,int line){
        int height = bst->GetHeight();
        int interval = Interval(height,line);
        int startBlank;
        vector<int> nodes = bst->GetNodesOnHeight(line);
        vector<Node> Nodes;
        for(int i = 0; i < nodes.size(); i++){
            int pos = getPos(bst->GetNodeCode(nodes[i]));
            Node* node = new Node(nodes[i],pos);
            Nodes.push_back(*node);
        }
        int num = pow(2,height-1);
        int n = pow(2,line-1);
        int maxSize = (num-1)*(1+baseInterval)+1;
        startBlank = (maxSize - n - (n-1)*interval)/2;
        drawBaseLine(maxSize,Nodes,interval,startBlank,line,height,bst);
    }

public:
    
    BST* root;

    int val;
    BST* left;
    BST* right;

    BST(int val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    BST(vector<int>* nums){
        BST* bst;
        for(int i = 0; i < nums->size(); i++){
            if(i == 0){
                bst = new BST(nums->at(0));
                continue;
            }
            bst = insert(nums->at(i),bst);
        }
        root = bst;
    }

    void Insert(int val){
        root = insert(val,root);
    }

    BST* Find(int val){
        return find(val,root);
    }

    BST* FindMax(){
        return findMax(root);
    }

    BST* FindMin(){
        return findMin(root);
    }

    void Delete(int val){
        _Delete(val,root);
    }

    int GetHeight(){
        return getHeight(root);
    }

    void DrawHorizontal(){
        if (root->left){
            output_impl(root->left, true, "");
        }
        cout << root->val << endl;
        if (root->right){
            output_impl(root->right, false, "");
        }      
    }

    vector<int> GetNodesOnHeight(int depth){
        vector<int> nodes;
        BST* p = root;
        getTreeLevel(root,&nodes,depth);
        return nodes;
    }

    vector<int> GetNodeCode(int val){
        vector<int> code;
        getNodeCode(val,root,code);
        return code;
    }

    void DrawVertical(){
        for(int i = 1; i <= GetHeight(); i++){
            drawline(this,i);
        }
    }

};
