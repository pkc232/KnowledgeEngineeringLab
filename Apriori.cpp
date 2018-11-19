#include <bits/stdc++.h>
#define structure map<vector<int>,int>
#define mpit map<std::vector<int>,int> :: iterator 
#define vi vector<int> 
#define vvi std::vector<std::vector<int> > 
#define rep2(i,v) for(int i=0;i<v.size();i++)
#define rep(i,a,b) for(long long int i=a;i<b;i++)
#define ITEMS 5
#define minSup 2
#define ll long long int
using namespace std;

structure C;
structure L;
ifstream fin;

void scanDatabase(); 
bool findVec(vi in,vi out);
void increaseCount(vi v);
void initializeC0();
void generateL();
vvi getAllSubs(vi &v);
bool presentall(vi &v);
void generateC();
void printvec(vi v);
void printMap(structure &st);

void scanDatabase(){
	int c=0;
	string transac;
	int transNo,x;
	vi itemSet;
	while(fin){
		getline(fin,transac);
		// cout<<transac<<endl;
		itemSet.clear();
		stringstream ss;
		ss<<transac;
		ss>>transNo;
		while(ss>>x){
			itemSet.push_back(x);
		}
		increaseCount(itemSet);
	}
}

void increaseCount(vi v){
	mpit it=C.begin();
	while(it!=C.end()){
		if(findVec((*it).first,v)){
			// cout<<"Hello\n";
			(*it).second++;
		}
		it++;
	}
}

void initializeC0(){
	rep(i,1,ITEMS+1){
		vi v;
		v.push_back(i);
		C[v]=0;
	}
}

void generateL(){
	mpit it=C.begin();
	while(it!=C.end()){
		if((*it).second>=minSup){
			L[(*it).first]=(*it).second;
		}
		it++;
	}
	C.clear();
}

vvi getAllSubs(vi &v){
	vvi ans;
	ll n=v.size();
	ll num=(ll)pow(2,n);
	rep(i,0,num){
		vi temp;
		rep(j,0,n){
			if(num&&(1<<j)){
				temp.push_back(v[j]);
			}
		}
		if(temp.size()==((int)v.size()-1))
		ans.push_back(temp);
	}
	return ans;
}

bool presentall(vi &v){
	vvi subsets=getAllSubs(v);
	rep(i,0,subsets.size()){
		if(L.find(subsets[i])==L.end())
			return false;
	}
	return true;
}
bool satisfy(vi &v1,vi &v2){
	int l=v1.size();
	rep(i,0,l-1){
		if(v1[i]!=v2[i])
			return false;
	}
	return true;
}
vi join(vi &v1,vi &v2){
	vi v3=v1;
	v3.push_back(v2[(v2.size())-1]);
	return v3;
}

void generateC(){
	mpit it1=L.begin(),it2;
	while(it1!=L.end()){
		vi v1=(*it1).first;
		it2=it1;
		it2++;
		while(it2!=L.end()){
			vi v2=(*it2).first;
			if(satisfy(v1,v2)){
				vi v3=join(v1,v2);
				if(presentall(v3)){
					C[v3]=0;
				}
			}
		it2++;
		}
		it1++;
	}
	L.clear();
}

void printvec(vi v){
	rep2(i,v){
		cout<<v[i]<<" ";
	}

}

void printMap(structure &st){
	mpit it=st.begin();
	while(it!=st.end()){
		printvec((*it).first);
		cout<<" "<<(*it).second<<endl;
		it++;
	}
}

bool findVec(vi in,vi out){
	rep2(i,in){
		if(find(out.begin(), out.end(),in[i])==out.end())
			return false;
	}
	return true;
}

void Apriori(){
	C.clear();
	L.clear();
	initializeC0();
	while(!C.empty()){
		fin.open("transac.txt");
		scanDatabase();
		fin.close();
		cout<<"C\n";
		printMap(C);
		cout<<"L\n";
		generateL();
		printMap(L);
		generateC();
	}

}

int main(){
	Apriori();
}
