#include <bits/stdc++.h>
#define threshold 2
#define N 5
#define T 9
using namespace std;
struct node
{
	int item;
	int cnt=0;
	struct node* ptr[20]={NULL};
	struct node* par;
};
typedef struct node* nodeptr;
struct fptreenode
{
	nodeptr Fp;
	vector<nodeptr> header[20];
	int cnt[20];
};
int cnt[1001];
vector<nodeptr> link[1001];
bool comp(int a,int b)
{
	return cnt[a]>cnt[b];
}
void GenrateFile()
{
	ofstream fout;
	fout.open("TIDFp.txt");
	//fout<<"TID No.   Items\n";
	int i,j,k;
	for(i=0;i<T;i++)
	{
		fout<<i<<"   ";
		int num=(rand())%N+1;
		fout<<num<<" ";
		bool vis[N]={0};
		vector<int> v;
		for(j=0;j<num;)
		{
			int item=(rand())%N;
			if(vis[item])
			continue;
			vis[item]=1;
			v.push_back(item);
			j++;
		}
		sort(v.begin(),v.end());
		for(j=0;j<v.size();j++)
		fout<<v[j]<<" ";
		fout<<endl;
	}
	fout.close();	
}
void FindSingleFreq()
{
	ifstream fin;
	fin.open("TIDFp.txt");
	int i,j,k;
	while(!fin.eof())
	{
		int t;fin>>t;
		if(fin.eof())
		break;
		//cout<<t<<endl;
		int num;fin>>num;
	//	cout<<num<<endl;
		for(i=0;i<num;i++)
		{
			int x;fin>>x;
			//cout<<x<<" ";
			cnt[x+1]++;
		}
		//cout<<endl;
	}
//	for(int i=1;i<=N;i++)
//	cout<<i<<" "<<cnt[i]<<endl;
	
}
nodeptr Insert(nodeptr Fp,vector<int> &trans,int minc)
{
	
	sort(trans.begin(),trans.end(),comp);
	nodeptr tFp=Fp;
	for(int i=0;i<trans.size();i++)
	{
		tFp->cnt+=minc;
		if(tFp->ptr[trans[i]]==NULL)
		{
			tFp->ptr[trans[i]]=new node;
			nodeptr temp=tFp;
			tFp=tFp->ptr[trans[i]];
			tFp->par=temp;
			tFp->item=trans[i];
			link[trans[i]].push_back(tFp);
		}
		else
			tFp=tFp->ptr[trans[i]];
	}
	tFp->cnt+=minc;
	return Fp;
}
void MakeFPTree(nodeptr& Fp)
{
	Fp=new node;
	Fp->item=0;
	ifstream fin;
	fin.open("TIDFp.txt");
	int i,j,k;
	while(!fin.eof())
	{
		int t;fin>>t;
		if(fin.eof())
		break;
		//cout<<t<<endl;
		int num;fin>>num;
	//	cout<<num<<endl;
		vector<int> v;
		for(i=0;i<num;i++)
		{
			int x;fin>>x;
			//cout<<x<<" ";
			v.push_back(x+1);
		}
		Fp=Insert(Fp,v,1);
		//cout<<endl;
	}
}
void Print(nodeptr Fp)
{
	if(Fp==NULL)return;
	cout<<Fp->item<<" "<<Fp->cnt<<endl;
	for(int i=1;i<=N;i++)
	if(Fp->ptr[i]!=NULL)
	Print(Fp->ptr[i]);
}
void Check()
{ 
	for(int i=1;i<=N;i++)
	{
		for(int j=0;j<link[i].size();j++)
		{
			nodeptr t=link[i][j];
			while(t->item!=0)
			{
				cout<<t->item<<" ";
				t=t->par;
			}
			cout<<endl;
		}
	}
}
void PrintItemset(int mask)
{
	for(int i=0;i<N;i++)
	{
		if((mask&(1<<i)))
		cout<<"I"<<i+1<<" ";
	}
	cout<<endl;
}
fptreenode ConditionalBase(fptreenode Tree,int item)
{	
	fptreenode Treecond;
	Treecond.Fp=new node;
	Treecond.Fp->item=0;
	
	if(Tree.header[item].size()==0)
	{
	 Treecond.Fp=NULL;
	 return Treecond;
	}
	
	for(int i=1;i<=N;i++)
	{
		cnt[i]=0;
		link[i].clear();
	}
	for(int i=0;i<Tree.header[item].size();i++)
	{
		nodeptr leaf=Tree.header[item][i];
		int minc=leaf->cnt;
		vector<int> prefix;
		while(leaf->item!=0)
		{
			cnt[leaf->item]++;
			if(leaf->item!=item)
			prefix.push_back(leaf->item);
			leaf=leaf->par;
		}
		reverse(prefix.begin(),prefix.end());
		Treecond.Fp=Insert(Treecond.Fp,prefix,minc);
	}
	for(int i=1;i<=N;i++)
	{
	 Treecond.header[i]=link[i];
	 if(cnt[i]>=threshold)
	 Treecond.cnt[i]=cnt[i];
	 else
	 Treecond.cnt[i]=0;
	}
	return Treecond;
}
void PrintFrequent(int mask,vector<int>& v)
{
	int size=v.size();
	int totalset=pow(2,size);
	for(int i=1;i<totalset;i++)
	{
		int curr=mask;
		for(int j=0;j<size;j++)
		if(i&(1<<j))
		curr=curr|(1<<(v[j]-1));
		
		PrintItemset(curr);
	}
}
void FP_Growth(fptreenode Tree,int maskalpha)
{
	bool SinglePath=true;
	int cnt=0;
	nodeptr it1=NULL,it2=Tree.Fp;
	while(SinglePath && it2)
	{
		//cout<<"Hello"<<endl;
		cnt=0;
		for(int i=1;i<=N;i++)
		if(it2 && it2->ptr[i]!=NULL)
		{
			cnt++;
			it1=it2->ptr[i];	
		}
		if(cnt>1) SinglePath=false;
		if(cnt==0) it2=NULL;
	}
	
//	PrintItemset(maskalpha);
//	Print(Tree.Fp);
	if(SinglePath==true)
	{
		vector<int> subset;
		nodeptr t=Tree.Fp;
		while(t!=NULL)
		{
			if(t->cnt>=threshold && t->item!=0)
			subset.push_back(t->item);
			int i,j,k;
			for(i=1;i<=N;i++)
			if(t->ptr[i]!=NULL)
			{
				t=t->ptr[i];
				break;
			}
			if(i==N+1)
			t=NULL;
		}
	   // PrintItemset(maskalpha);cout<<"per\n";
	    //for(int i=0;i<subset.size();i++)
	    //cout<<subset[i]<<" ";
	    //cout<<endl;
	
		cout<<"Conditional Fp Tree ";
		PrintItemset(maskalpha);
		Print(Tree.Fp);
		PrintItemset(maskalpha);
		PrintFrequent(maskalpha,subset);
		return;
	}
	else
	{
		cout<<"Conditional Fp Tree ";
		PrintItemset(maskalpha);
		Print(Tree.Fp);
		PrintItemset(maskalpha);
		for(int i=1;i<=N;i++)
		{
			if(Tree.header[i].size()!=0)
			{
				int maskbeta=maskalpha|(1<<(i-1));
			   // cout<<i<<endl;
				fptreenode Treebeta=ConditionalBase(Tree,i);
			   // Print(Treebeta.Fp);
				if(Treebeta.Fp!=NULL)
				FP_Growth(Treebeta,maskbeta);
			}
		}
		
	}
}
int main()
{
   // GenrateFile();
	FindSingleFreq();
	nodeptr Fp;
	Fp=new node;
	Fp->item=0;
	MakeFPTree(Fp);
//	Print(Fp);
//	Check();
	fptreenode Tree;
	Tree.Fp=Fp;
	for(int i=1;i<=N;i++)
	{
		Tree.header[i]=link[i];
		Tree.cnt[i]=cnt[i];
	}
	
    FP_Growth(Tree,0);
	return 0;
}