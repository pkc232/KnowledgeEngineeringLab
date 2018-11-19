#include <bits/stdc++.h>
#define structure map<std::vector<int> ,pair<int,int> >
#define vi vector<int> 
#define vvi std::vector<std::vector<int> > 
#define rep2(i,v) for(int i=0;i<v.size();i++)
#define rep(i,a,b) for(long long int i=a;i<b;i++)
#define noOfPart 3
#define PartSize 4
#define ITEMS 5
#define minSup 2
#define mpit map<vector<int>,pair<int,int> >::iterator 
#define ll long long int
using namespace std;

ifstream fin;
int curPat;
structure DC;
structure DS;
structure SC;
structure SS;


void readPartition();
void increaseCount(vi &v);
vvi getAllSubs(vi &v);
void fillInitial();
void updateDC_and_DS();
void immediate_SuperSet_inDC(vi v);
vvi generateSuperset(vi &v);
void printMap(structure &st);
void printFreq();
void eraseFromMap(vvi &toBeErased,structure &st);

void readPartition(){
	int c=0;
	string transac;
	int transNo,x;
	vi itemSet;
	while(c<PartSize&&fin){
		getline(fin,transac);
		cout<<transac<<endl;
		itemSet.clear();
		stringstream ss;
		ss<<transac;
		ss>>transNo;
		while(ss>>x){
			itemSet.push_back(x);
		}
		increaseCount(itemSet);
		c++;
	}
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
		if(temp.size()==v.size()-1)
		ans.push_back(temp);
	}
	return ans;
}
bool findVec(vi in,vi out){
	rep2(i,in){
		if(find(out.begin(), out.end(),in[i])==out.end())
			return false;
	}
	return true;
}


void increaseCount(vi &v){
	mpit it1=DC.begin(),it2=DS.begin();
	while(it1!=DC.end()){
		if(findVec((*it1).first,v))
			((*it1).second.first)=(*it1).second.first+1;
		it1++;
	}
	while(it2!=DS.end()){
		if(findVec((*it2).first,v))
			((*it2).second.first)=(*it2).second.first+1;
		it2++;
	}
}

void fillInitial(){
	rep(i,1,ITEMS+1){
		vi temp;
		temp.push_back(i);
		DC[temp]=make_pair(0,0);
	}
}
void eraseFromMap(vvi &toBeErased,structure &st){
	rep(i,0,toBeErased.size()){
		st.erase(toBeErased[i]);
	}
}

void updateSS_and_SC(){
	vvi toBeErased,toBeErased2;
	mpit it1=DS.begin();
	while(it1!=DS.end()){
		if(((*it1).second.second)%noOfPart==(curPat+1)%noOfPart){
			toBeErased.push_back((*it1).first);
			SS[(*it1).first]=(*it1).second;
		}
		it1++;
	}

	eraseFromMap(toBeErased,DS);
	mpit it2=DC.begin();
	while(it2!=DC.end()){
		if(((*it2).second.second)%noOfPart==(curPat+1)%noOfPart){
			toBeErased2.push_back((*it2).first);
			if((*it2).second.first<minSup){
			SC[(*it2).first]=(*it2).second;
		}
		else
		{
			SS[(*it2).first]=(*it2).second;
		}
		}
		it2++;
	}
	eraseFromMap(toBeErased2,DC);
}

void dynamicItemSetCounting(){
	while(DC.size()||DS.size()){
		if(curPat==0){
			fin.close();
			fin.open("transac2.txt");
		}
		readPartition();

		
		updateDC_and_DS();
		cout<<"DC is \n";
		printMap(DC);
		cout<<endl<<endl;
		cout<<"DS is \n";
		printMap(DS);
		cout<<"SS is \n";
		printMap(SS);
		cout<<"SC is \n";
		printMap(SC);
		cout<<"Hello\n";
		curPat=((curPat+1)%noOfPart);
		updateSS_and_SC();
	}
}

void updateDC_and_DS(){
	mpit it1=DC.begin(),it2;
	vvi toBeErased;
	while(it1!=DC.end()){
		if((*it1).second.first>=minSup){
			DS[(*it1).first]=((*it1).second);
			toBeErased.push_back((*it1).first);
			immediate_SuperSet_inDC((*it1).first);
		}
		it1++;
	}
	eraseFromMap(toBeErased,DC);
	
}

vvi generateSuperset(vi &v){
	vvi ans;
	rep(i,1,ITEMS+1){
		if(find(v.begin(),v.end(),i)==v.end()){
		vi temp=v;
		temp.push_back(i);
		sort(temp.begin(),temp.end());
		ans.push_back(temp);
	}
	}
	return ans;
}
bool allPresent(vvi &v){
	rep(i,0,v.size()){
		if((DS.find(v[i])==DS.end())&&(SS.find(v[i])==SS.end()))
			return false;
	}

	return true;
}

void immediate_SuperSet_inDC(vi v){
	vvi superSets = generateSuperset(v);
	rep(i,0,superSets.size()){
		vvi allSubs=getAllSubs(superSets[i]);
		if(allPresent(allSubs)){
			DC[superSets[i]]=make_pair(0,(curPat+1)%noOfPart);
		}
	} 
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
		cout<<"\t";
		cout<<((*it).second.first)<<" "<<((*it).second.second)<<endl;
		it++;
	}
}

void printFreq(){
	printMap(SS);
}

int main(int argc, char const *argv[])
{
	int curPat=0;
	fillInitial();
	printMap(DC);
	dynamicItemSetCounting();
	cout<<"Frequent ItemSets Are:\n";
	printFreq();
	return 0;
}