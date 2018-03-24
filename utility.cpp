#include<bits/stdc++.h>
#include "utility.h"
using namespace std;


bool is(int feat,vector<int> arr){
for(unsigned int i=0;i<arr.size();i++){
    if(arr[i]==feat)
        return true;
}
return false;
}
/////////////////////////////////////////////////////////////////////////
void print(double arr[],int n){
for(int i=0;i<n;i++){
    cout<<arr[i]<<" ";
}
cout<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////
void printv(vector<int> v,int n){
for(int i=0;i<n;i++){
    cout<<v[i]<<" ";
}
cout<<endl;
}
////////////////////////////////////////////////////////////////////////////////////
void printr(vector<unordered_map<int,int>> r){

unsigned int i;
for(i=0;i<r.size();i++){
    for(auto it=r[i].begin();it!=r[i].end();++it){
        cout<<it->first<<":"<<it->second<<" ";
    }
    cout<<endl<<endl<<endl;
}
cout<<endl;
}
///////////////////////////////////////////////////////////////////////////////////
vector<int>& getFeat(){
    vector<int> allfeat;
int i=0;
while(i<5000){//store the words and polarity
    allfeat.push_back(i);
    i++;
}
return allfeat;
}
////////////////////////////////////////////////////////////////////////////
void freq(string str,int& fe,int& fr){
unsigned int i=0;
fe=0;
fr=0;
while(str[i]!=':'){
    fe=10*fe+(str[i]-'0');
    i++;
}
i++;
while(i<str.length()){
    fr=10*fr+(str[i]-'0');
    i++;
}
}
/////////////////////////////////////////////////////////////////////////////////////
node::node(const int& a){
    attribute=a;
    left=NULL;
    right=NULL;
};

bool node::isleaf() const{
    return attribute==-1 || attribute==INT_MAX;
}
///////////////////////////////////////
/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


node* Dtree::makeTree(vector<int> Plist,vector<int> Nlist,vector<unordered_map<int,int>>& Positive,vector<unordered_map<int,int>>& Negative,vector<int> attr,double early){
//cout<<"enter in make tree"<<endl;
if(Plist.empty()){
    return (node*)new node(-1);
}
if(Nlist.empty()){
    return (node*)new node(INT_MAX);
}
if(attr.empty()){
    if((double)Plist.size()>(double)Nlist.size())
        return (node*)new node(INT_MAX);
        return (node*)new node(-1);
}

if(early>0){
    if(Plist.size()/Nlist.size()>early)
        return (node*)new node(INT_MAX);

    else if  (Nlist.size()/Plist.size()>early)
        return (node*)new node(-1);
}

int pos=gain(Plist,Nlist,Positive,Negative,attr);//return s the best position for root
//cout<<"pos="<<pos<<endl;
//creating arguments for left and rightvector<unordered_map<int,int>> PRight;
vector<int> NRight;
vector<int> PRight;
vector<int> NLeft;
vector<int> PLeft;
for(unsigned int j=0;j<Plist.size();j++){
     //   std::unordered_map<int,int> temp=Positive[j];
    if(Positive[Plist[j]].find(attr[pos])!=Positive[Plist[j]].end()){
        PRight.push_back(Plist[j]);
}
else{
  PLeft.push_back(Plist[j]);
}
//cout<<"j="<<j<<endl;
}
//cout<<"PR created"<<endl;
for(unsigned int j=0;j<Nlist.size();j++){
    if(Negative[Nlist[j]].find(attr[pos])!=Negative[Nlist[j]].end()){
        NRight.push_back(Nlist[j]);
}
else{
 NLeft.push_back(Nlist[j]);
}
}
//cout<<"NR created"<<endl;
node* head=new node(attr[pos]);
//head->attribute=attr[pos];
attr.erase(attr.begin()+pos);
head->left=makeTree(PLeft,NLeft,Positive,Negative,attr,early);
head->right=makeTree(PRight,NRight,Positive,Negative,attr,early);
return head;
}


int gain(vector<int>& Plist,vector<int>& Nlist,vector<unordered_map<int,int> >& Positive,vector<unordered_map<int,int> >& Negative,vector<int> attr){
//cout<<"entered in gain"<<endl;
double gain=INT_MAX;
//cout<<"size="<<attr.size()<<endl;
int pos=0;
for(unsigned int i=0;i<attr.size();i++){//calculate the position of best attribute

double lp=0,rp=0,ln=0,rn=0;
for(unsigned int j=0;j<Plist.size();j++){
       // std::unordered_map<int,int> temp=Positive[j];
    if(Positive[Plist[j]].find(attr[i])!=Positive[Plist[j]].end())
        rp=rp+1;
    else
        lp=lp+1;
}

for(unsigned int j=0;j<Nlist.size();j++){
        //std::unordered_map<int,int> temp=Negative[j];
    if(Negative[Nlist[j]].find(attr[i])!=Negative[Nlist[j]].end())
        rn=rn+1;
    else
        ln=ln+1;
}
//cout<<"rr";
//cout<<"lp="<<lp<<" rp="<<rp<<" ln="<<ln<<" rn="<<rn<<endl;
double g=Gain(lp,ln,rp,rn);
//cout<<"g="<<g<<endl;
if(g<gain){
    gain=g;
    pos=i;
   // cout<<"gain="<<gain<<" i="<<i<<endl;
}

}
return pos;
}


double Gain(double lp,double ln,double rp,double rn){
return ((lp+ln)/(rp+rn+lp+ln))*entropy(lp,ln)+((rp+rn)/(rp+rn+lp+ln))*entropy(rp,rn);
}


double entropy(double a,double b){
if(a==0 || b==0)
    return 0;

    return (-1)*((a/(a+b))*log2(a/(a+b))+(b/(a+b))*log2(b/(a+b)));
}


int size(node* node)
{
  if (node==NULL)
    return 0;
  else
    return (size(node->left) + 1 + size(node->right));
  }

int leaf(node* node){
    if(node==NULL)
        return 0;
    if(node->left==NULL && node->right==NULL)
        return 1;
    else
        return leaf(node->left)+leaf(node->right);
}

double testAccuracy(node* root,int number[2][5000],vector<unordered_map<int,int>> Sample,vector<int> rating){


//test map created
/////////////////////////////////////////////////
////////////////////////////////////////////////
///////////////////////////////////////////

double count=0;
for(unsigned int i=0;i<Sample.size();i++){
    node* temp=root;
    while(temp!=NULL){
        if(temp->isleaf()){
            if(rating[i]==temp->attribute)
                count++;
                break;
        }
        else{
            if(Sample[i].find(temp->attribute)!=Sample[i].end()){
                temp=temp->right;
            }
            else
                temp=temp->left;
        }
        number[1][temp->attribute]++;
    }
}
return (count/1000)*100;
}



double testAccInForest(vector<node*> allroot,vector<unordered_map<int,int>> Sample,vector<int> rating){

//test map created
/////////////////////////////////////////////////
////////////////////////////////////////////////
///////////////////////////////////////////
double count=0;
for(unsigned int i=0;i<Sample.size();i++){
        int positive=0;
        for(unsigned int j=0;j<allroot.size();j++){
    node* temp=allroot[j];
    while(temp!=NULL){
        if(temp->isleaf()){
            if(temp->attribute==INT_MAX)
                positive++;
                break;
        }
        else{
            if(Sample[i].find(temp->attribute)!=Sample[i].end()){
                temp=temp->right;
            }
            else
                temp=temp->left;
        }
    }
}
if((positive>=allroot.size()-positive && rating[i]==INT_MAX) || (positive<allroot.size()-positive && rating[i]==-1)){
        count++;
}
}
return count*100/1000;
}







double trainAccInForest(vector<node*> allroot,vector<unordered_map<int,int>> P,vector<unordered_map<int,int>> N){
//test map created
/////////////////////////////////////////////////
////////////////////////////////////////////////
///////////////////////////////////////////
double count=0;
for(unsigned int i=0;i<P.size();i++){
        int positive=0;
        for(unsigned int j=0;j<allroot.size();j++){
    node* temp=allroot[j];
    while(temp!=NULL){
        if(temp->isleaf()){
            if(temp->attribute==INT_MAX)
                positive++;
                break;
        }
        else{
            if(P[i].find(temp->attribute)!=P[i].end()){
                temp=temp->right;
            }
            else
                temp=temp->left;
        }
    }
}
if(positive>=allroot.size()-positive ){
        count++;
}
}


for(unsigned int i=0;i<N.size();i++){
        int positive=0;
        for(unsigned int j=0;j<allroot.size();j++){
    node* temp=allroot[j];
    while(temp!=NULL){
        if(temp->isleaf()){
            if(temp->attribute==INT_MAX)
                positive++;
                break;
        }
        else{
            if(N[i].find(temp->attribute)!=N[i].end()){
                temp=temp->right;
            }
            else
                temp=temp->left;
        }
    }
}
if(positive<allroot.size()-positive){
        count++;
}
}
return count*100/1000;
}






double accOnTrain(node* root,vector<unordered_map<int,int>> P,vector<unordered_map<int,int>> N){
double count=0;
for(unsigned int i=0;i<P.size();i++){
    node* temp=root;
    while(temp!=NULL){
        if(temp->isleaf()){
            if(temp->attribute==INT_MAX)
                count++;
                break;
        }
        else{
            if(P[i].find(temp->attribute)!=P[i].end()){
                temp=temp->right;
            }
            else
                temp=temp->left;
        }
    }
}
for(unsigned int i=0;i<N.size();i++){
    node* temp=root;
    while(temp!=NULL){
        if(temp->isleaf()){
            if(temp->attribute==-1)
                count++;
                break;
        }
        else{
            if(N[i].find(temp->attribute)!=N[i].end()){
                temp=temp->right;
            }
            else
                temp=temp->left;
        }
    }
}
return (count/1000)*100;
}


void createTestSet(vector<unordered_map<int,int>>& Sample,vector<int>& rating){
ifstream file;
file.open("labeledBowTest.feat");
vector<string> myall;
string line;
while(getline(file,line)){
    myall.push_back(line);
}
srand(time(0));
random_shuffle(myall.begin(),myall.begin()+12499);
srand(time(0));
random_shuffle(myall.begin()+12500,myall.end());

int i=0;
while(i<500){//for 1000 reviews
        unordered_map<int,int> mat;

  //  getline(file,line);//reading one line from file
    line=myall[i];
    unsigned int k=0;
    int rate=0;;
        while(line[k]!=' '){//ignore extra spsces;
            rate=10*rate+(line[k]-'0');
            k++;
        }
    k++;

rating.push_back(INT_MAX);
    string word="";//reading single word
    int feature,frequency;
    while(k<line.length()){//reading characters from line and store in word
        word="";
        while(line[k]==' '){//ignore extra spsces;
            k++;
        }
        while(k<line.length() && line[k]!=' ' && line[k]!='\n'){//extract word from the line
            word=word+line[k];
            k++;
        }
        freq(word,feature,frequency);//extract feature number and frequency of feature in that review
       pair<int,int> myfeature(feature,frequency);
            mat.insert(myfeature);
       k++;
    }
    Sample.push_back(mat);
i++;
}

i=0;
while(i<500){//for 1000 reviews
        unordered_map<int,int> mat;
line=myall[24999-i];
    getline(file,line);//reading one line from file
    unsigned int k=0;
    int rate=0;;
        while(line[k]!=' '){//ignore extra spsces;
            rate=10*rate+(line[k]-'0');
            k++;
        }
    k++;

rating.push_back(-1);
    string word="";//reading single word
    int feature,frequency;
    while(k<line.length()){//reading characters from line and store in word
        word="";
        while(line[k]==' '){//ignore extra spsces;
            k++;
        }
        while(k<line.length() && line[k]!=' ' && line[k]!='\n'){//extract word from the line
            word=word+line[k];
            k++;
        }
        freq(word,feature,frequency);//extract feature number and frequency of feature in that review
       pair<int,int> myfeature(feature,frequency);
            mat.insert(myfeature);
       k++;
    }
    Sample.push_back(mat);
i++;
}
file.close();
}


void createTrainSet(vector<unordered_map<int,int>>& Positive,vector<unordered_map<int,int>>& Negative){
ifstream file;
file.open("labeledBowTrain.feat");
vector<string> mypositive;
vector<string> mynegative;
string line;
int i=0;
while(i<12500){
        getline(file,line);
    mypositive.push_back(line);
    i++;
}
while(getline(file,line)){
    mynegative.push_back(line);

}
srand(time(0));
random_shuffle(mypositive.begin(),mypositive.end());
srand(time(0));
random_shuffle(mynegative.begin(),mynegative.end());
i=0;
//cout<<"some"<<endl;
while(i<500){//for 1000 reviews
        unordered_map<int,int> mat;
  //  getline(file,line);//reading one line from file
  line=mypositive[i];
    unsigned int k=0;
    int rate=0;
        while(line[k]!=' '){//ignore extra spsces;
            rate=10*rate+(line[k]-'0');
            k++;
        }
    k++;
    string word="";//reading single word
    int feature,frequency;
    while(k<line.length()){//reading characters from line and store in word
        word="";
        while(line[k]==' '){//ignore extra spsces;
            k++;
        }
        while(k<line.length() && line[k]!=' ' && line[k]!='\n'){//extract word from the line
            word=word+line[k];
            k++;
        }
        freq(word,feature,frequency);//extract feature number and frequency of feature in that review

        if(feature<5000){//if yes then initialize that frequency of that feature at that position
            //cout<<"word"<<word<<" feature="<<feature<<" fre="<<frequency<<endl;
            pair<int,int> myfeature(feature,frequency);
            mat.insert(myfeature);
        }
       k++;
    }

if(!mat.empty()){
Positive.push_back(mat);
i++;
}
}

///////////////////////////////////////////////////////////////////////////////
i=0;

while(i<500){//for 1000 reviews
    unordered_map<int,int> mat;
    //getline(file,line);//reading one line from file
    line=mynegative[i];
    unsigned int k=0;
    int rate=0;
        while(line[k]!=' '){//ignore extra spsces;
            rate=rate+(line[k]-'0');
            k++;
        }
    k++;
    string word="";//reading single word
    int feature,frequency;
    while(k<line.length()){//reading characters from line and store in word
        word="";
        while(line[k]==' '){//ignore extra spsces;
            k++;
        }
        while(k<line.length() && line[k]!=' ' && line[k]!='\n'){
            word=word+line[k];
            k++;
        }
        freq(word,feature,frequency);
        if(feature<5000){
               // cout<<"word="<<word<<" feature="<<feature<<" fre="<<frequency<<endl;
            pair<int,int> myfeature(feature,frequency);
            mat.insert(myfeature);
        }
       k++;
    }
if(!mat.empty()){
Negative.push_back(mat);
i++;
}
}
//cout<<"some2"<<endl;
file.close();
}



void Merge(int arr[][5000],int low,int mid,int high){
int n1=mid-low+1;
int n2=high-mid;

int temp1[n1],temp2[n2];
int temp11[n1],temp22[n2];

for(int i=0;i<n1;i++){
    temp1[i]=arr[0][low+i];
    temp11[i]=arr[1][low+i];
}
for(int i=0;i<n2;i++){
    temp2[i]=arr[0][i+mid+1];
    temp22[i]=arr[1][i+mid+1];
}
int i=0,j=0,step=low;

while(i<n1 && j<n2){
    if(temp11[i]>=temp22[j]){
        arr[0][step]=temp1[i];
        arr[1][step]=temp11[i];
        i++;
    }
    else{
        arr[0][step]=temp2[j];
        arr[1][step]=temp22[i];
        j++;
    }

    step++;
}

while(i<n1){
    arr[0][step]=temp1[i];
    arr[1][step]=temp11[i];
    i++;
    step++;
}
while(j<n2){
        arr[0][step]=temp2[j];
        arr[1][step]=temp22[i];
    j++;
    step++;
}
}

void mergeSort(int arr[2][5000],int low,int high){
if(low<high){
    int mid=(low+high)/2;
    mergeSort(arr,low,mid);
    mergeSort(arr,mid+1,high);
    Merge(arr,low,mid,high);
}
}
