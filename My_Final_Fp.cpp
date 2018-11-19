#include <bits/stdc++.h>
#define ITEMS 5
#define minsup 2
#define vi vector<int>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb(x) push_back(x)
#define ll long long int
using namespace std;


struct  Node
{
	int item;
	int cnt;
	Node* par;
	Node* child[ITEMS+1];
	Node(){
		item=-1;
		cnt=0;
		par=NULL;
		rep(i,0,ITEMS+1){
			child[i]=NULL;
		}
	}

	Node(int it,int c,Node* p){
		item=it;
		cnt=c;
		par=p;
		rep(i,0,ITEMS+1){
			child[i]=NULL;
		}
	}
};
typedef Node* nptr;
int CNT[ITEMS+1];
std::vector<nptr> PATH[ITEMS+1];

struct  Tree
{
	nptr root;
	int freq[ITEMS+1];
	vector<nptr> path[ITEMS+1];

	Tree(nptr r){
		root=r;
		rep(i,0,ITEMS+1){
			freq[i]=CNT[i];
			path[i]=PATH[i];
		}
	}
};
void insert(nptr root,vi &v,int ind);
void storeSingleFreq();
Tree* initialFpTree();




void insert(nptr root,vi &v,int ind){
	if(ind==v.size())
		return;
	root->cnt++;
	if(root->child[v[ind]]==NULL){
		root->child[v[ind]]=new Node(v[ind],0,root);
		PATH[v[ind]].pb(root->child[v[ind]]);
	}
	root->cnt++;
	insert(root->child[v[ind]],v,ind+1);
}

void storeSingleFreq(){
	ifstream fin;
	fin.open("transac.txt");
	string transac;
	memset(CNT,0,sizeof(CNT));
	int tid,it;
	while(fin){
		getline(fin,transac);
		stringstream ss;
		ss<<transac;
		ss>>tid;
		while(ss>>it){
			CNT[it]++;
		}
	}
	fin.close();
}

bool comp(int x1,int x2){
	return CNT[x1]>CNT[x2];
}

Tree* initialFpTree(){
	ifstream fin;
	fin.open("transac.txt");
	string transac;
	int tid,it;
	nptr root=new Node();
	while(fin){
		getline(fin,transac);
		stringstream ss;
		ss<<transac;
		vi v;
		while(ss>>it){
			v.pb(it);
		}
		sort(v.begin(), v.end(),comp);
		insert(root,v,0);
	}
	fin.close();
	Tree *FpTree= new Tree(root);
	return FpTree;
}

Tree* createCondFp(Tree* curFp,int item){
	nptr root=new Node();
	for(int i=0;i<ITEMS;i++)
	{
		Cnt[i]=0;
		Path[i].clear();
	}
	for(int i=0;i<curFp->path[item].size();i++){
		nptr leaf=curFp->path[item][i];
		int cn=leaf->cnt;
		vector<int> prefix;
		leaf=leaf->par;
		while(leaf){
			prefix.push_back(leaf->item);
			leaf=leaf->par;
		}
		rep(i,0,cn){
			insert(root,prefix,0);
		}

	}
	curFp->root=root;

	rep(i,1,ITEMS+1){
		curFp->path[i]=Path[i];
		curFp->cnt[i]=Cnt[i];
	}
}

void Fp_Growth(Tree* Fp,ll num){
	nptr root=Fp->root;
	bool singlePath=true;
	nptr it1=root,it2=NULL;
	int c=0;
	while(singlePath&&it1){
		c=0;
		rep(i,1,ITEMS+1){
			if(it1->child[i]){
				it2=it1->child[i];
				cnt++;
			}
		}
		if(cnt>=2)
			singlePath=false;
		it1=it2;
	}

	if(singlePath){
		vi subset;
		it1=root,it2=NULL;
		while(it1){
			it2=NULL;
			if(it1->item!=-1)
			subset.pb(it1->item);
			rep(i,1,ITEMS+1){
				if(it1->child[i]){
					it2=it1->child[i];
					break;
				}
			}
			it1=it2;
		}
		printFreq(subset,num);
	}
	else
	{
		rep(i,1,ITEMS+1){
			ll maskB;
			if(Fp->path[i].size()){
				maskB = (maskA|(1<<i))
				// Tree* nrt=new Tree();
				nrt=createCondFp(Fp,i);
				if(nrt->root){
					Fp_Growth(nrt,maskB);
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	storeSingleFreq();
	Tree* Fp=initialFpTree();
	return 0;
}


 


