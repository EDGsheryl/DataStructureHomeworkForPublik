#include <bits/stdc++.h>
using namespace std;

class TreeNode{
public:
    char val;
    TreeNode* lc,*rc;
    TreeNode* fa;
    int depth;
    TreeNode() {
        val = depth = 0;
        lc = rc = nullptr;
        fa= nullptr;
    }
};

void pre_order_traversal(TreeNode *root) {

    cout<<"visit:"<<root->val<<endl;

    if (root->lc != nullptr)
        pre_order_traversal(root->lc);

    if (root->rc != nullptr)
        pre_order_traversal(root->rc);

}

void in_order_traversal(TreeNode *root) {

    if (root->lc != nullptr)
        in_order_traversal(root->lc);

    cout<<"visit:"<<root->val<<endl;

    if (root->rc != nullptr)
        in_order_traversal(root->rc);
}

void post_order_traversal(TreeNode *root) {

    if (root->lc != nullptr)
        post_order_traversal(root->lc);

    if (root->rc != nullptr)
        post_order_traversal(root->rc);

    cout<<"visit:"<<root->val<<endl;
}

TreeNode* longest= nullptr;
void dfs(TreeNode *root,int dep=1) {
    root->depth=dep;
    if (longest== nullptr || root->depth>longest->depth) longest=root;
    if (root->lc != nullptr)
        dfs(root->lc,dep+1);
    if (root->rc != nullptr)
        dfs(root->rc,dep+1);
}
void Getlongest(TreeNode* root)
{
    dfs(root);
    stack<TreeNode*> s;
    while (!s.empty()) s.pop();
    TreeNode* now=longest;
    while (now != nullptr && now!=NULL)
    {
        s.push(now);
        now=now->fa;
    }
    cout<<"the longest way is:";
    while (!s.empty())
    {
        if (s.top()!=NULL && s.top()!= nullptr)
            cout<<((*(s.top())).val)<<" ";
        s.pop();
    }
    cout<<endl;
    return;
}

void GetLeaf(TreeNode *root) {
    if (root== nullptr || root == NULL ) return ;
    if (root->lc == nullptr && root->rc == nullptr)
        cout << root->val << " is a leaf" << endl;

    else {
        if (root->rc != nullptr)
            GetLeaf(root->lc);

        if (root->rc != nullptr)
            GetLeaf(root->rc);
    }
}

TreeNode a[30];
void Init()
{
    a[1].val='A';
    a[2].val='B';
    a[3].val='C';
    a[4].val='D';
    a[5].val='E';
    a[6].val='F';
    a[7].val='G';
    a[8].val='H';
    a[9].val='I';

    a[1].lc=&a[2];
    a[1].rc=&a[7];
    a[1].fa= nullptr;

    a[2].lc=&a[3];
    a[2].rc=&a[5];
    a[2].fa=&a[1];

    a[3].lc=nullptr;
    a[3].rc=&a[4];
    a[3].fa=&a[2];

    a[4].lc= nullptr;
    a[4].rc= nullptr;
    a[4].fa=&a[3];

    a[5].lc=nullptr;
    a[5].rc=&a[6];
    a[5].fa=&a[2];

    a[6].lc=nullptr;
    a[6].rc=nullptr;
    a[6].fa=&a[5];

    a[7].lc=&a[8];
    a[7].rc=&a[9];
    a[7].fa=&a[1];

    a[6].lc=nullptr;
    a[6].rc=nullptr;
    a[6].fa=&a[7];

    a[6].lc=nullptr;
    a[6].rc=nullptr;
    a[6].fa=&a[7];
}

int main()
{
    Init();
    pre_order_traversal(&a[1]);
    cout<<endl;
    in_order_traversal(&a[1]);
    cout<<endl;
    Getlongest(&a[1]);
    cout<<endl;
    GetLeaf(&a[1]);
}