#include<iostream>
#include<vector>
#include<stack>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int L[maxn],R[maxn];
int main()
{
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
	a[0]=a[n+1]=-1;
    stack<int>st;
    for(int i=0;i<=n+1;i++){
		while(!st.empty()&&a[i]<=a[st.top()]){
			R[st.top()]=i-1;
            st.pop();
        }
		if(st.empty())L[i]=0;
		else L[i]=st.top()+1;
		st.push(i);
    }
    for(int i=1;i<=n;i++){
        cout<<L[i]<<" "<<R[i]<<endl;
    }
}

