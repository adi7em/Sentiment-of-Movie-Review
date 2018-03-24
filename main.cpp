#include <bits/stdc++.h>
#include<stdlib.h>
#include<time.h>
#include <unordered_map>
#include "utility.h"
#define F 8
#define N 1000
#define E 2
using namespace std;

int main(int argc,char* argv[])
{
    if(argc<2){
        cout<<"To few arguments, Please provide experiment number"<<endl;
        return 0;
    }
    if(arg[1][0]=='3'){
        cout<<"Sorry, this problem is not solved"<<endl;
        return 0;
    }
    fstream file;
    file.open("TrainSet.txt");
vector<int> arr;
arr=getFeat();//contains the seriul number of features
//printv(arr,5000);
vector<unordered_map<int,int>> Previews;//for containing feature number and its frequncey
vector<unordered_map<int,int>> Nreviews;//for containing feature number and its frequncey
vector<unordered_map<int,int>> Sample;
vector<int> rating;

//block for storing reviews in array of map
createTrainSet(Previews,Nreviews);
createTestSet(Sample,rating);

for(int i=0;i<Previews.size();i++){
    unordered_map::iterator it;
    for(it=Previews[i].begin();it!=Previews.end();++it){
file<<it->first<<" "<<it->second<<" ";
    }
    cout<<endl;
}
for(int i=0;i<Nreviews.size();i++){
    unordered_map::iterator it;
    for(it=Nreviews[i].begin();it!=Nreviews.end();++it){
file<<it->first<<" "<<it->second<<" ";
    }
    cout<<endl;
}
file.close();
fstream file;
file.open("TrainSet.txt");
for(int i=0;i<Sample.size();i++){
    unordered_map::iterator it;
    for(it=Sample[i].begin();it!=Sample.end();++it){
file<<it->first<<" "<<it->second<<" ";
    }
    cout<<endl;
}
file.close();
vector<unordered_map<int,int>> Plast;//for containing feature number and its frequncey
vector<unordered_map<int,int>> Nlast;
//cout<<"created"<<endl;
//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
///////////////////////////////////////////////'
//printr(Previews);
//printr(Nreviews);
vector<int> Plist(500),Nlist(500);
for(int i=0;i<500;i++){
    Plist[i]=i;
    Nlist[i]=i;
}
Dtree t;
switch(argv[1][0]){
    case '1':{

node* root=t.makeTree(Plist,Nlist,Previews,Nreviews,arr,0);
cout<<"*********************RESULTS OF FIRST TASK*******************"<<endl<<endl;
cout<<"Root attribute of the tree="<<root->attribute<<endl;
cout<<"Total number of nodes in the tree="<<size(root)<<endl;
cout<<"Total number of leaf nodes in the tree="<<leaf(root)<<endl;
cout<<"accuracy on Training set="<<accOnTrain(root,Previews,Nreviews)<<"%"<<endl;
int counter[2][5000];
for(int i=0;i<5000;i++){
    counter[0][i]=i;
    counter[1][i]=0;
}
double accuracy=testAccuracy(root,counter,Sample,rating);
cout<<"accuracy on Test set="<<accuracy<<"%"<<endl;
    }
    case '2':{
node* rootearly=t.makeTree(Plist,Nlist,Previews,Nreviews,arr,E);
cout<<endl<<endl<<endl<<"*********************RESULTS OF SECOND TASK::EARLY STOPPING*******************"<<endl<<endl;
cout<<"Root attribute of the tree="<<rootearly->attribute<<endl;
cout<<"Total number of nodes in the tree="<<size(rootearly)<<endl;
cout<<"Total number of leaf nodes in the tree="<<leaf(rootearly)<<endl;
counter[2][5000];
for(int i=0;i<5000;i++){
    counter[0][i]=i;
    counter[1][i]=0;
}
accuracy=testAccuracy(rootearly,counter,Sample,rating);
mergeSort(counter,0,4999);
cout<<"In testing, number of times attribute is used in for all reviews in test set"<<endl<<endl;
cout<<"attribute     count"<<endl;
for(int i=0;i<25;i++){
    cout<<counter[0][i]<<"    "<<counter[1][i]<<endl;
}
cout<<"accuracy on Training set="<<accOnTrain(rootearly,Previews,Nreviews)<<"%"<<endl;
cout<<"accuracy on test set="<<accuracy<<"%"<<endl;
    }
    case '4':{
cout<<endl<<endl<<endl<<"************************RESULTS OF THIRD TASK::NOISE ADDITION*********************"<<endl;
srand(time(0));
random_shuffle(Previews.begin(),Previews.end());
srand(time(0));
random_shuffle(Nreviews.begin(),Nreviews.end());
for(int i=0;i<5;i++){
    unordered_map<int,int> temp=Previews[i];
    Previews[i]=Nreviews[i];
    Nreviews[i]=temp;
}
node* root1=t.makeTree(Plist,Nlist,Previews,Nreviews,arr,0);
cout<<"*********************   Noise=0.5%   *******************"<<endl;
cout<<"Root attribute of the tree="<<root1->attribute<<endl;
cout<<"Total number of nodes in the tree="<<size(root1)<<endl;
cout<<"Total number of leaf nodes in the tree="<<leaf(root1)<<endl;
accuracy=testAccuracy(root1,counter,Sample,rating);
cout<<"accuracy on Training set="<<accOnTrain(root1,Previews,Nreviews)<<"%"<<endl;
cout<<"accuracy on test set="<<accuracy<<"%"<<endl<<endl;

for(int i=5;i<10;i++){
    unordered_map<int,int> temp=Previews[i];
    Previews[i]=Nreviews[i];
    Nreviews[i]=temp;
}
node* root2=t.makeTree(Plist,Nlist,Previews,Nreviews,arr,0);
cout<<"*********************   Noise=1%   *******************"<<endl;
cout<<"Root attribute of the tree="<<root2->attribute<<endl;
cout<<"Total number of nodes in the tree="<<size(root2)<<endl;
cout<<"Total number of leaf nodes in the tree="<<leaf(root2)<<endl;
accuracy=testAccuracy(root2,counter,Sample,rating);
cout<<"accuracy on Training set="<<accOnTrain(root2,Previews,Nreviews)<<"%"<<endl;
cout<<"accuracy on test set="<<accuracy<<"%"<<endl<<endl;

for(int i=10;i<15;i++){
    unordered_map<int,int> temp=Previews[i];
    Previews[i]=Nreviews[i];
    Nreviews[i]=temp;
}
node* root3=t.makeTree(Plist,Nlist,Previews,Nreviews,arr,0);
cout<<"*********************   Noise=1.5%   *******************"<<endl;
cout<<"Root attribute of the tree="<<root3->attribute<<endl;
cout<<"Total number of nodes in the tree="<<size(root3)<<endl;
cout<<"Total number of leaf nodes in the tree="<<leaf(root3)<<endl;
accuracy=testAccuracy(root3,counter,Sample,rating);
cout<<"accuracy on Training set="<<accOnTrain(root3,Previews,Nreviews)<<"%"<<endl;
cout<<"accuracy on test set="<<accuracy<<"%"<<endl<<endl;
for(int i=15;i<100;i++){
    unordered_map<int,int> temp=Previews[i];
    Previews[i]=Nreviews[i];
    Nreviews[i]=temp;
}
node* root4=t.makeTree(Plist,Nlist,Previews,Nreviews,arr,0);
cout<<"*********************   Noise=10%   *******************"<<endl;
cout<<"Root attribute of the tree="<<root4->attribute<<endl;
cout<<"Total number of nodes in the tree="<<size(root4)<<endl;
cout<<"Total number of leaf nodes in the tree="<<leaf(root4)<<endl;
accuracy=testAccuracy(root4,counter,Sample,rating);
cout<<"accuracy on Training set="<<accOnTrain(root4,Previews,Nreviews)<<"%"<<endl;
cout<<"accuracy on test set="<<accuracy<<"%"<<endl<<endl;

    }
    case '5':{
cout<<endl<<endl<<"*******************RESULTS FROM FIFTH TASK::FOREST****************************"<<endl<<endl;
for(int i=0;i<100;i++){
    unordered_map<int,int> temp=Previews[i];
    Previews[i]=Nreviews[i];
    Nreviews[i]=temp;
}

vector<node*> rootOftrees;
for(int j=10;j<=40;j=j+10){
        cout<<"number of trees="<<i<<endl<<endl;
for(int i=0;i<j;i++){
    srand(time(0));
    random_shuffle(arr.begin(),arr.end());
    vector<int> temp;
    for(int j=0;j<N;j++){
        temp.push_back(arr[j]);
    }
    rootOftrees.push_back(t.makeTree(Plist,Nlist,Previews,Nreviews,temp,0));
}
cout<<"Accuracy on Forest of Train set="<<trainAccInForest(rootOftrees,Previews,Nreviews)<<"%"<<endl;
cout<<"Accuracy on Forest of Test set="<<testAccInForest(rootOftrees,Sample,rating)<<"%"<<endl;
    }
    }
    return 0;
}
