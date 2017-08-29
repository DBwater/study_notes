#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution{
public:
	vector<int>findOrder(int numCourses,vector<pair<int,int> >& prerequisites){
		vector<int>in(numCourses,0);
		vector<int>ans;
		vector<int>G[numCourses];
		for(int i=0;i<prerequisites.size();i++){
			G[prerequisites[i].second].push_back(prerequisites[i].first);
			in[prerequisites[i].first]++;
		}
		queue<int>que;
		int t=0;
		for(int i=0;i<numCourses;i++){
			if(in[i]==0)que.push(i);
		}
		while(!que.empty()){
			int v = que.front();
			que.pop();
			ans.push_back(v);
			for(int i=0;i<G[v].size();i++){
				in[G[v][i]]--;
				if(in[G[v][i]]==0)que.push(G[v][i]);
			}
		}
		if(ans.size()<numCourses)ans.clear();
		return ans;
	}
};
int main()
{
	vector<pair<int,int> > data;
	data.push_back(make_pair(1,0));
	data.push_back(make_pair(2,0));
	data.push_back(make_pair(3,1));
	data.push_back(make_pair(3,2));
	Solution A ;
	
	vector<int>ans = A.findOrder(4,data);
	for(int i=0;i<ans.size();i++)
	cout<<ans[i]<<endl;
}
