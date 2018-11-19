#include <bits/stdc++.h>
#define ITEMS 5
#define trans 10
#define minsup 2
using namespace std;

struct Node
{
	int item;
	int count;
	Node* child[ITEMS];
	Node* par;
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

struct FPNode
{
	Nodeptr root;
	vector<nptr> path[ITEMS];
	int cnt[ITEMS];
FPNode()
	{
		root = NULL;
		memset(count,0,sizeof count);
	}

};

int Cnt[ITEMS];
std::vector<Nodeptr> Path;

bool comp1(int a,int b)
{
	return Cnt[a]>Cnt[b];
}

Nodeptr insert(Nodeptr &Root,std::vector<int> &trans,int times){
	Nodeptr it=Root;
	sort(trans.begin(), trans.end(),comp1);
	int i=0;
	it->cnt+=times;
	while(i<trans.size()){
		if(it->child[trans[i]]==NULL){
			it->child[trans[i]]=new Node(trans[i],0,it);
			Path[trans[i]].push_back(it->child[trans[i]]);
		}
		it->child[trans[i]]->cnt+=times;
		it=it->child[trans[i]];
		i++;
	}
	return Root;
}

void findSingleFrequencyInput()
{
	fin.open("transac.txt");
	int s2,key;
    string s1;
    int i;
	while(fin){
		getline(fin,s1);
		stringstream ss;
		ss<<s1;
		ss>>s2;
		while(ss>>s2){
		Cnt[s2]++;
		}
	}
	fin.close();
}
void makeFPTree(Nodeptr &root){

fin.open("Transactions.txt");
	int s2,key;
    string s1;
    int i;
    head=new node();
    initialize(head,-1);
	while(fin){
		getline(fin,s1);
		stringstream ss;
		ss<<s1;
		int fl=1;
		vector<int> v;
		ss>>s2;
		while(ss>>s2){
			v.push_back(s2);
		}
		sort(v.begin(),v.end(),comp2);
		insert(head,v,0);
	}
	fin.close();
}

void FP_Growth(FPNode* Froot,int maskA){
	bool singlePath=true;
	int cnt=0;
	Nodeptr it1=NULL,it2=Froot->root;
	

}


