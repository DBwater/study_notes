#include<iostream>
#include<stack>
using namespace std;
typedef struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int _val):val(_val){}
}TreeNode;
//先序
void DLR(TreeNode* root){
	TreeNode* p = root;
	stack<TreeNode*>st;
	while(p!=NULL||!st.empty()){
		if(p!=NULL){
			st.push(p);
			cout<<(p->val)<<" ";
			p=p->left;
		}
		else{
			p = st.top();
			st.pop();
			p= p->right;
		}
	}
}
//中序
void LDR(TreeNode* root){
	TreeNode* p = root;
	stack<TreeNode*>st;
	while(p!=NULL||!st.empty()){
		if(p!=NULL){
			st.push(p);
			p = p->left;
		}
		else{
			p = st.top();
			cout<<(p->val)<<" ";
			st.pop();
			p = p->right;
		}
	}
}
//后序

void LRD(TreeNode* root){
	TreeNode* p = root;
	TreeNode* pre = NULL;
	stack<TreeNode*> st;
	while(p!=NULL||!st.empty()){
		if(p!=NULL){
			st.push(p);
			p=p->left;
		}
		else{
			p=st.top();
			if(p->right==NULL||p->right==pre){
					cout<<(p->val)<<" ";
					pre = p ;
					st.pop();
					p = NULL;
			}
			else{
				p = p->right;
			}
		}

	}
}
int main()
{
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	root->right->left = new TreeNode(6);
	DLR(root);	
	cout<<endl;

	LDR(root);
	cout<<endl;
	
	LRD(root);
	cout<<endl;
}
