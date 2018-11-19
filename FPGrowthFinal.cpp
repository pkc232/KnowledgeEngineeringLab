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
void initialize_nxtptr(){
	for(int i=0;i<=noOfItems;i++)
	nxtPtr[i]=NULL;
}
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
void storeTable(vector<table> &tempdb,int normfreq[]){
	for(int i=1;i<=noOfItems;i++){
		table temp;
		if(normfreq[i]>=min_sup){
			temp.id=i;
			temp.sup_count=normfreq[i];
			temp.strt=NULL;
			tempdb.push_back(temp);
		}	
	}
	sort(tempdb.begin(),tempdb.end(),comp1);
}
void printTable(vector<table> &tempdb){
	for(int i=0;i<tempdb.size();i++)
	{
		cout<<tempdb[i].id<<" "<<tempdb[i].sup_count<<endl;
		msrt[tempdb[i].id]=i;
	}
}

bool comp2(int x1,int x2){
	return msrt[x1]<msrt[x2];
}


//storing from database
void storeInTreeFromFile(){
	fin.open("Transactions.txt");
	int s2,key;
    string s1;
    int i;
    nptr head=new node();
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
void printLink(nptr temp){
	if(!temp)
	return;
	
	cout<<temp->val<<" : "<<temp->cnt<<"\t";
	printLink(temp->next);
}

void printTree(nptr te){
	if(!te)
	return;
	cout<<te->val<<":"<<te->cnt<<endl;
	for(int i=1;i<=noOfItems;i++)
	printTree(te->child[i]);
}



vector<pair<int,vector<pair<vector<int>,int> > > >PatternBase;


pair<vector<int>,int> storePath(nptr temp){
	vector<int> nm;
	if(!temp)
	return make_pair(nm,0);
	nptr jh=temp;
	
	temp=temp->parent;
	
	while(temp&&temp->parent){
	//	cout<<"Phir\n";
		if(!temp)
		break;
		nm.push_back(temp->val);
		if(temp->val==-1)
		break;
		temp=temp->parent;
	}
//	cout<<"Thik hai\n";
	return make_pair(nm,jh->cnt);
}
void insertFromRec(nptr head,vector<int> &v,int i,vector<table> &tempdb){
	if(i==v.size())
	return;
	if(head->child[v[i]]==NULL){
		head->child[v[i]]=new node;
		initialize(head->child[v[i]],v[i]);
		head->child[v[i]]->parent=head;
		if(nxtPtr[v[i]]==NULL){
			nxtPtr[v[i]]=head->child[v[i]];
			int ind;
			for(ind=0;ind<tempdb.size();ind++){
				if(tempdb[ind].id==v[i])
				break;
			}
			tempdb[ind].strt=nxtPtr[v[i]];
		}
		else
		{
			nxtPtr[v[i]]->next=head->child[v[i]];
			nxtPtr[v[i]]=head->child[v[i]];	
		}
	}
	head->child[v[i]]->cnt++;
	insertFromRec(head->child[v[i]],v,i+1,tempdb);
}
void createPB(vector<table> &tempdb);
void doRecursion(vector<pair<vector<int>,int> > &nop,int treeKaMalik){
	vector<table> tempdb;
	int normfreq[noOfItems+1];
	memset(normfreq,0,sizeof(normfreq));
	int sz=nop.size();
	
	for(int i=0;i<sz;i++)
	{
		for(int j=0;j<nop[i].first.size();j++){
			normfreq[nop[i].first[j]]+=nop[i].second;
		}
	}
	storeTable(tempdb,normfreq);
//	cout<<"Tree ka malik "<<treeKaMalik<<endl;
//	cout<<"IDHR "<<tempdb.size()<<endl;
	if(tempdb.size()==1){
//	for(int i=0;i<ans.size();i++)
//	cout<<ans[i]<<" "<<endl;
	return;	
	}
	
	
	printTable(tempdb);
	
	initialize_nxtptr();
	nptr head=NULL;
	head=new node;
	initialize(head,-1);
	
	for(int i=0;i<sz;i++){
		vector<int> vtp;
		for(int j=0;j<nop[i].first.size();j++){
			if(normfreq[nop[i].first[j]]>=min_sup){
				vtp.push_back(nop[i].first[j]);
			}
		}
		sort(vtp.begin(),vtp.end(),comp2);
		insertFromRec(head,vtp,0,tempdb);	
	}
	//cout<<"Iske liye Tree\n";
	printTree(head);
	createPB(tempdb);

}

void createPB(vector<table> &tempdb){
	cout<<"Recursion me ghusa\n";
	int i;
	nptr temp;
	for(i=tempdb.size()-1;i>=0;i--){
		temp=tempdb[i].strt;
		vector<pair<vector<int>,int> >  nop;
		while(temp)
		{
			//cout<<"Galti\n";
			pair<vector<int>,int> ach=storePath(temp);
			//cout<<"Galti 2\n";
			if(ach.first.size()>0)
			nop.push_back(ach);
			temp=temp->next;
		}
		if(nop.size())
		{
			//PatternBase.push_back(make_pair(db[i].id,nop));
			doRecursion(nop,tempdb[i].id);
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


int main(){
	
	
	//storing from database
	initialize_nxtptr();
	memset(freq,0,sizeof(freq));
	readInput();
	storeTable(db,freq);
	printTable(db);
	storeInTreeFromFile();
//	printTree(head);
	createPB(db);
	//printPatternBase();
	
}


