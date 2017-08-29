struct node{
    int to,w;
    node(int a,int b)
    {
        to=a;w=b;
    }
};
vector<node>G[MAX_N];
int root,k;
int vs[MAX_N*2];
int deep[MAX_N*2];
int id[MAX_N];
int dp[MAX_N*2][25];
int dist[MAX_N];
void dfs(int v,int p,int d)//root,父节点,深度,数组的标号
{
    id[v]=k;
    vs[k]=v;
    deep[k++]=d;
    for(int i=0;i<G[v].size();i++)
    {
        if(G[v][i].to!=p)
        {
            dist[G[v][i].to]=dist[v]+G[v][i].w;//有权的lca
            dfs(G[v][i].to,v,d+1);
            vs[k]=v;
            deep[k++]=d;
        }                                      
    }
}
void rmq(int n)//返回最小值对应的下标
{
    for(int i=1;i<=n;i++)
        dp[i][0]=i;
    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;i+(1<<j)-1<=n;i++)
        {
            int a=dp[i][j-1],b=dp[i+(1<<j-1)][j-1];
            dp[i][j]=deep[a]<deep[b]? a:b;
        }
    }
}
int query(int l,int r)
{
    int k=(int)(log((r-l+1)*1.0)/log(2.0));
    int a=dp[l][k],b=dp[r-(1<<k)+1][k];
    return deep[a]<deep[b]? a:b;
}
int solve(int l,int r)//求出l,r的最近公共祖先
{
    int x=id[l],y=id[r];
    if(x>y)swap(x,y);
    int res=query(x,y);
    return vs[res];
}
void init(int v)
{
    root=1,k=1;
    dist[1]=0;
    dfs(root,-1,1);
    rmq(v*2-1);
}
