#include <bits/stdc++.h>
using namespace std;
int n;
int C[21][21];
int X[21];
int visited[21]={0};
int mincost=INT_MAX;
int cost=0;
int minfee=INT_MAX;
bool check(int v, int k){
    if(visited[v]!=0) return false;
    return true;
}
void Try(int k){
    for(int v=2;v<=n;v++){
        if(check(v,k)){
            X[k]=v;
            visited[v]=1;
            cost+=C[X[k-1]][X[k]];
            if(k==n){
                cost+=C[X[k]][1];
                if(cost < mincost) mincost=cost;
                cost-=C[X[k]][1];
            }
            else if(cost + minfee*(n-k+1)<mincost){
                Try(k+1);
            }
            visited[v]=0;
            cost-=C[X[k-1]][X[k]];
        }
    }
}

int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> C[i][j];
            if(C[i][j]!=0 && C[i][j]<minfee) minfee= C[i][j];
        }
    }
    X[1]=1;
    Try(2);
    cout << mincost;
    return 0;

}
