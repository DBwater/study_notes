#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	//冒泡排序
   	void bubble_sort(vector<int> &mg){
		int n=mg.size();
		for(int i=0;i<n;i++){
			for(int j=n-1;j>i;j--){
				if(mg[j]<mg[j-1])
					swap(mg[j],mg[j-1]);
			}
		}
  	}
	//插入排序
	void insert_sort(vector<int> &mg){
		int n=mg.size();
		for(int i=1;i<n;i++){
			for(int j=i;j>0;j--){
				if(mg[j]<mg[j-1])
					swap(mg[j],mg[j-1]);
				else 
					break;
			}
		}
	}
	//shell排序
	void shell_sort(vector<int> &mg){
		int n=mg.size();
		for(int gap=n/2;gap>0;gap/=2){
			for(int i=gap;i<n;i++){
				for(int j=i;j>=gap;j-=gap){
					if(mg[j-gap]>mg[j])
						swap(mg[j-gap],mg[j]);
					else break;
				}
			}
		}
	}
	//选择排序
	void select_sort(vector<int> &mg){
		int n=mg.size();
		for(int i=0;i<n;i++){
			int index=i;
			for(int j=i+1;j<n;j++){
				if(mg[index]>mg[j])
					index=j;
			}
			swap(mg[index],mg[i]);
		}
	}
	//快速排序
   	void fast_sort(vector<int> &mg,int l,int r){
    	if(l<r){
        	int left=l,right=r;
           	int key=mg[left];
           	while(left<right){
            	while(left<right&&mg[right]>=key)right--;
               	swap(mg[left],mg[right]);
               	while(left<right&&mg[left]<=key)left++;
               	swap(mg[left],mg[right]);
           	}
           	int mid=left;
           	fast_sort(mg,l,mid-1);
           	fast_sort(mg,mid+1,r);
       }
   	}
	//堆排序
	void heap_adjust(vector<int> &mg,int start,int end){
		for(int i=start*2+1;i<end;i=i*2+1){
			if(i+1<end&&mg[i]<mg[i+1]){
				i++;
			}
			if(mg[start]>mg[i])break;
			swap(mg[start],mg[i]);
			start=i;
		}
	}
	void heap_sort(vector<int> &mg){
			int n=mg.size();
			for(int i=(n-1)/2;i>=0;i--){
				heap_adjust(mg,i,n);
			}
			for(int i=n-1;i>0;i--){
				swap(mg[0],mg[i]);
				heap_adjust(mg,0,i);
			}
		 }
	//归并排序
	void mergearray(vector<int> &mg,int l,int mid,int r,vector<int> &ans){
		int i=l,j=mid+1,k=0;
		for(;i<=mid&&j<=r;k++){
			if(mg[i]<=mg[j]){
				ans[k]=mg[i++];
			}
			else{
				ans[k]=mg[j++];
			}
		}
		while(i<=mid)
			ans[k++]=mg[i++];
		while(j<=r)
			ans[k++]=mg[j++];
		for(int i=0;i<k;i++){
			mg[l+i]=ans[i];
		}
	}
	void merge_sort(vector<int> &mg,int l,int r,vector<int> &ans){
		if(l<r){
			int mid=(l+r)>>1;
			merge_sort(mg,l,mid,ans);
			merge_sort(mg,mid+1,r,ans);
			mergearray(mg,l,mid,r,ans);
		}		
		//桶排序
	}
};

int main()
{
	vector<int>mg{10,5,4,3,-6,6,7,-3,3,2,1,1,1};
	vector<int>ans(100,0);
	Solution A;
	A.merge_sort(mg,0,mg.size()-1,ans);
	for(int i=0;i<mg.size();i++)
		cout<<mg[i]<<" ";
	return 0;
}
