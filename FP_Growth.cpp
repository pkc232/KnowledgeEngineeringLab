#include<bits/stdc++.h>
#define noOfItems 5
#define min_sup 2
using namespace std;
ifstream fin;
map<int,int> msrt;

struct node{
	node* child[noOfItems+1];
	node* next;
	int val;
	int cnt;
	node* parent;
};
typedef node* nptr;
nptr nxtPtr[noOfItems+1];
struct table{
	int id;
	int sup_count;
	nptr strt;
};
vector<table> db;

int freq[noOfItems+1];
//storing the input from file
void readInput(){
	fin.open("Transactions.txt");
	int s2,key;
    string s1;
    int i;
	while(fin){
		getline(fin,s1);
		stringstream ss;
		ss<<s1;
		ss>>s2;
		while(ss>>s2){
		freq[s2]++;
		}
	}
	fin.close();
}
//input stored

//making a trie
nptr head;
void initialize(nptr t,int item){
	t->val=item;
	t->cnt=0;
	for(int i=0;i<=noOfItems;i++)
	t->child[i]=NULL;
	t->next=NULL;
}

void insert(nptr head,vector<int> &v,int i){
	if(i==v.size())
	return;
	if(head->child[v[i]]==NULL){
		head->child[v[i]]=new node;
		initialize(head->child[v[i]],v[i]);
		head->child[v[i]]->parent=head;
		if(nxtPtr[v[i]]==NULL){
			nxtPtr[v[i]]=head->child[v[i]];
			int ind;
			for(ind=0;ind<db.size();ind++){
				if(db[ind].id==v[i])
				break;
			}
			db[ind].strt=nxtPtr[v[i]];
		}
		else
		{
			nxtPtr[v[i]]->next=head->child[v[i]];
			nxtPtr[v[i]]=head->child[v[i]];	
		}
	}
	head->child[v[i]]->cnt++;
	insert(head->child[v[i]],v,i+1);
}
//trie made


bool comp1(table t1,table t2){
	return t1.sup_count>t2.sup_count;
}
void storeTable(){
	for(int i=1;i<=noOfItems;i++){
		table temp;
		if(freq[i]>=min_sup){
			temp.id=i;
			temp.sup_count=freq[i];
			temp.strt=NULL;
			db.push_back(temp);
		}	
	}
	sort(db.begin(),db.end(),comp1);
}
void printTable(){
	for(int i=0;i<db.size();i++)
	{
		msrt[db[i].id]=i;
	}
}

bool comp2(int x1,int x2){
	return msrt[x1]<msrt[x2];
}

void insertInTree(){
	
}


//storing from database
void storeInTreeFromFile(){
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
// stored from file

void printTree(nptr te){
	if(!te)
	return;
	cout<<te->val<<":"<<te->cnt<<endl;
	for(int i=1;i<=noOfItems;i++)
	printTree(te->child[i]);
}

void printLink(nptr temp){
	if(!temp)
	return;
	
	cout<<temp->val<<" : "<<temp->cnt<<"\t";
	printLink(temp->next);
}


vector<pair<int,vector<pair<vector<int>,int> > > >PatternBase;


pair<vector<int>,int> storePath(nptr temp){
	vector<int> nm;
	nptr jh=temp;
	temp=temp->parent;
	
	while(temp->parent){
		nm.push_back(temp->val);
		temp=temp->parent;
	}
	return make_pair(nm,jh->cnt);
}

void createPB(){
	int i;
	nptr temp;
	for(i=db.size()-1;i>=0;i--){
		temp=db[i].strt;
		vector<pair<vector<int>,int> >  nop;
		while(temp)
		{
			pair<vector<int>,int> ach=storePath(temp);
			if(ach.first.size()>0)
			nop.push_back(ach);
			temp=temp->next;
		}
		if(nop.size())
		{
			PatternBase.push_back(make_pair(db[i].id,nop));
		//	createFPTree(nop);
		}
	}
}


void printPatternBase(){
	for(int i=0;i<PatternBase.size();i++)
	{
		
		cout<<PatternBase[i].first<<" "<<endl;
		vector<pair<vector<int>,int> > temp=PatternBase[i].second;
		for(int j=0;j<temp.size();j++){
		vector<int> t=temp[j].first;
		for(int k=0;k<t.size();k++)
			cout<<t[k]<<" ";
			cout<<": ";
			cout<<temp[j].second<<endl;
		}
	}
}

void createFPTree(vector<pair<vector<int>,int> > &tempDB){
	
}

int main(){
	
	
	//storing from database
	for(int i=0;i<=noOfItems;i++)
	nxtPtr[i]=NULL;
	memset(freq,0,sizeof(freq));
	readInput();
	storeTable();
	printTable();
	storeInTreeFromFile();
	
	
	printTree(head);
	createPB();
	printPatternBase();
	
}


