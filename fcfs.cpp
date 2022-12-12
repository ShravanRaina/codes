#include <iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;

void print(int arr[], int n){
    for (int i = 0 ; i< n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
void printC(string arr[], int n){
    for (int i = 0 ; i< n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void completionTime(int AT[],int BT[], int CT[]){
    int buffer=0;
    
    CT[0] = AT[0] + BT[0];

    for(int i = 1 ;i< 4; i++){
        
        buffer = CT[i-1]-AT[i];
        
        if(buffer>0){
            CT[i] = CT[i-1] + BT[i];
        }
        else{
            CT[i] = CT[i-1] + BT[i] + abs(buffer);
        }
    }
    print(CT,4);
}

void turnAround(int AT[], int CT[], int TAT[]){
    for(int i =0 ;i<4;i++){
        TAT[i] = CT[i] - AT[i];
    }

    print(TAT,4);
}

void waitTime(int BT[], int TAT[], int WT[]){
    for(int i=0;i<4;i++){
        WT[i] = TAT[i] - BT[i];
    }

    print(WT,4);
}


void sort(int AT[], int BT[], string P[], int n){
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (AT[j] > AT[j + 1])
            {
                swap(AT[j],AT[j+1]);
                swap(BT[j],BT[j+1]);
                swap(P[j],P[j+1]);
            }
        }
    }
}

int main(){
    string P[4] = {"P0","P1","P2","P3"};
    int AT[4] = {0,1,2,3};
    int BT[4] = {5,3,8,6};
    int CT[4];
    int TAT[4];
    int WT[4];
    int RT[4];    

    // sort(AT,BT,P,4);
    sort(AT,BT,P,4);

    cout<<"Process id:"<<endl;
    printC(P,4);

    cout<<"Completion time :"<<endl;
    completionTime(AT,BT,CT);

    cout<<"Turn Around time:"<<endl;
    turnAround(AT,CT,TAT);

    cout<<"Waiting time:"<<endl;
    waitTime(BT,TAT,WT);

    cout<<"Avg Waiting time : "<<endl;
    float sum = 0 ;
    for(int i = 0 ;i<4;i++){
        sum = sum + WT[i];
    }
    cout<<sum/4<<endl;


    return 0;
}