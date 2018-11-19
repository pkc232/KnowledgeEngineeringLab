#include<bits/stdc++.h>
using namespace std;

#define MIN_SUP 2
#define ITEMS 5


struct Node{
	int item;
	int count;
	Node* par;
	Node* child[ITEMS];
	Node()
	{
		this->item=-1;
		this->count=0;
		this->par=NULL;
		for(int i=0;i<ITEMS;i++) this->child[i]=NULL;
	}
	Node(int item,int count,Node* par)
	{
		this->item=item; this->count=count; this->par=par;
		for(int i=0;i<ITEMS;i++) this->child[i]=NULL;
	}
}; 
typedef Node* Nodeptr;

struct FPNode{
	Nodeptr root;
	int count[ITEMS];
	vector<Nodeptr> path[ITEMS];
	FPNode()
	{
		root = NULL;
		memset(count,0,sizeof count);
	}
	
};
int Cnt[ITEMS];
vector<Nodeptr> Path[ITEMS];

bool comp1(int a,int b)
{
	return Cnt[a]>Cnt[b];
}

void Print(Nodeptr Fp)
{
	if(Fp==NULL)return;
	cout<<Fp->item<<" "<<Fp->count<<endl;
	for(int i=0;i<ITEMS;i++) Print(Fp->child[i]);
}
void PrintItemset(int mask)
{
	for(int i=0;i<ITEMS;i++)
	{
		if((mask&(1<<i)))
		cout<<"I"<<i<<" ";
	}
	cout<<endl;
}
void PrintFrequent(int mask,vector<int>& v)
{
	int size=v.size();
	int totalset=pow(2,size);
	for(int i=0;i<totalset;i++)
	{
		int curr=mask;
		for(int j=0;j<size;j++)
		if(i&(1<<j))
		curr=curr|(1<<(v[j]));
		
		PrintItemset(curr);
	}
}
Nodeptr insert(Nodeptr &Root,vector<int>& trans,int count)
{
	Nodeptr it=Root;
	int i=0;
	sort(trans.begin(),trans.end(),comp1);
	it->count+=count;
	while(i<trans.size())
	{
		if(it->child[trans[i]]==NULL)
		{
			
			it->child[trans[i]]=new Node(trans[i],0,it);
			Path[trans[i]].push_back(it->child[trans[i]]);
		}
		it->child[trans[i]]->count+=count;
		it = it->child[trans[i++]];
	}
	return Root;
}

void findSingleFrequencyInput()
{
	ifstream fin;
	fin.open("FPInput.txt");
	int n,x;
	while(fin>>n)
	{
		for(int i=0;i<n;i++)
		{
			fin>>x;
			Cnt[x]++;
		}
	}
	fin.close();
	cout<<"Printing the initial count array "<<endl;
	for(int i=0; i<ITEMS; i++) 
	{
		cout<<"Item"<<i<<"->"<<Cnt[i]<<endl;
	}
}


void makeFPTree(Nodeptr &root)
{
	
	ifstream fin;
	fin.open("FPInput.txt");
	int n,t,c=0; 
	while(fin>>n)
	{
		c++;
		vector<int> v;
		for(int i=0;i<n;i++)
		{
			fin>>t;
			v.push_back(t);	
		}
		root = insert(root,v,1);
	}
	fin.close();
}


void makeConditionalFPTree(FPNode* &Treecond,FPNode* &Tree,int item)
{
	if(Tree->path[item].size()==0)
	{
	 	return;
	}
	Treecond->root=new Node(-1,0,NULL);
	for(int i=0;i<ITEMS;i++)
	{
		Cnt[i]=0;
		Path[i].clear();
	}
	for(int i=0;i<Tree->path[item].size();i++)
	{
		int coun=0;
		Nodeptr leaf=Tree->path[item][i];
		coun=leaf->count;
		vector<int> prefix;
		leaf=leaf->par;
		while(leaf->item!=-1)
		{
			Cnt[leaf->item]+= coun;
			if(leaf->item!=item) prefix.push_back(leaf->item);
			leaf=leaf->par;
		}
		Treecond->root= insert(Treecond->root,prefix,coun);
	}
	for(int i=0;i<ITEMS;i++)
	{
	 	Treecond->path[i]=Path[i];
	 	if(Cnt[i]>=MIN_SUP) Treecond->count[i]=Cnt[i];
	 	else
	 	Treecond->count[i]=0;
	 }

}

void FPGrowth(FPNode* FRoot,int maskA)
{
	bool SinglePath=true;
	int cnt=0;
	Nodeptr it1=NULL,it2=FRoot->root;
	while(SinglePath && it2)
	{
		cnt=0;
		it1 = NULL;
		for(int i=0;i<ITEMS;i++)
		{
			if(it2->child[i]!=NULL)
			{
				cnt++;
				it1=it2->child[i];
			}
		}
		if(cnt>1) SinglePath = false;
		it2 = it1;
	}
	if(SinglePath)
	{
		vector<int> subset;
		Nodeptr t= FRoot->root;
		while(t!=NULL)
		{
			if(t->count>= MIN_SUP && t->item!=-1) subset.push_back(t->item);
			int i,j,k;
			for(i=0;i<ITEMS;i++)
			if(t->child[i]!=NULL)
			{
				t=t->child[i];
				break;
			}
			if(i==ITEMS) t=NULL;
		}
	    cout<<"Conditional Fp Tree in Single Path"<<endl;
		PrintItemset(maskA);
		Print(FRoot->root);
		PrintItemset(maskA);
		cout<<"Printing frequent item sets------------------------------ "<<endl;
		PrintFrequent(maskA,subset);
		cout<<"-----------------------------------------------------------"<<endl;
		return;
	}
	else
	{
		cout<<"Conditional Fp Tree in Non Single Path "<<endl;
		for(int i=0;i<ITEMS;i++)
		{
			int maskB;
			if(FRoot->path[i].size())
			{
				maskB = maskA|(1<<i);
				FPNode* condFPRoot = new FPNode();
				makeConditionalFPTree(condFPRoot,FRoot,i);
				if(condFPRoot->root!=NULL) FPGrowth(condFPRoot,maskB);
			}
		}
	}
	
}

int main()
{
	memset(Cnt,0,sizeof Cnt);
	findSingleFrequencyInput();
	Nodeptr root = new Node();
	makeFPTree(root);
	FPNode* FRoot = new FPNode();
	FRoot->root=root;
	for(int i=0;i<ITEMS;i++)
	{
		FRoot->count[i]=Cnt[i];
		FRoot->path[i]=Path[i];
	}
	Print(FRoot->root);
	FPGrowth(FRoot,0);
}
