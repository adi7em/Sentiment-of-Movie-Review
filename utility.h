#include<bits/stdc++.h>
#include <unordered_map>
#ifndef UTILITY_H_
#define UTILITY_H_
class Dtree;
class node;
double Log(double);
double Gain(double,double,double,double);
void print(double [],int );
void printv(std::vector<int>,int );
void Merge(double [],int,int,int,std::vector<int>&);
void mergeSort(double [],int,int,std::vector<int>&);
void freq(std::string,int&,int&);
void mergeSort(int [][5000],int,int);
void Merge(int [][5000],int,int,int);
bool is(int,std::vector<int>);
double entropy(double,double);
int leaf(node*);
double testAccInForest(std::vector<node*>,std::vector<std::unordered_map<int,int>>,std::vector<int>);
double accOnTrain(node*,std::vector<std::unordered_map<int,int>>,std::vector<std::unordered_map<int,int>>);
double trainAccInForest(std::vector<node*>,std::vector<std::unordered_map<int,int>>,std::vector<std::unordered_map<int,int>>);
//void review(std::vector<int>,std::unordered_map<int,int> &[1000]);
std::vector<int>& getFeat();
void printr(std::vector<std::unordered_map<int,int>>);
int gain(std::vector<int>&,std::vector<int>&,std::vector<std::unordered_map<int,int>>&,std::vector<std::unordered_map<int,int>>&,std::vector<int>);
int size(node*) ;
void createTrainSet(std::vector<std::unordered_map<int,int>>&,std::vector<std::unordered_map<int,int>>&);
class Dtree;
double testAccuracy(node*,int number[][5000],std::vector<std::unordered_map<int,int>>,std::vector<int>);
void createTestSet(std::vector<std::unordered_map<int,int>>&,std::vector<int>&);
class node{

public:
    int attribute;
    node* left;
    node* right;
    node(const int&);
    bool isleaf() const;
    ~node();
friend class Dtree;
};

class Dtree{
public:
    node* makeTree(std::vector<int>,std::vector<int>,std::vector<std::unordered_map<int,int>>&,std::vector<std::unordered_map<int,int>>&,std::vector<int>,double);

};
#endif
