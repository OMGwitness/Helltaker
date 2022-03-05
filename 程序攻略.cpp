#include<bits/stdc++.h>
using namespace std;
const int N=15;
const int dx[]={-1,1,0,0};
const int dy[]={0,0,-1,1};
int n;
struct node{
    int id;
    bool key;
    bool door;
    int kuai[N][N];
    int x,y;
    int step;
    bool operator < (const node &r) const{
        if(step!=r.step)
            return step<r.step;
        if(key!=r.key)
            return key;
        if(door!=r.door)
            return door;
        if(x!=r.x)
            return x<r.x;
        if(y!=r.y)
            return y<r.y;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(kuai[i][j]!=r.kuai[i][j])
                    return kuai[i][j]<r.kuai[i][j];
        return false;
    }
    bool operator > (const node &r) const{
        if(step!=r.step)
            return step>r.step;
        if(key!=r.key)
            return r.key;
        if(door!=r.door)
            return r.door;
        if(x!=r.x)
            return x>r.x;
        if(y!=r.y)
            return y>r.y;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(kuai[i][j]!=r.kuai[i][j])
                    return kuai[i][j]>r.kuai[i][j];
        return false;
    }
    bool operator == (const node &r) const{
        if(key!=r.key||door!=r.door||x!=r.x||y!=r.y)
            return false;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(kuai[i][j]!=r.kuai[i][j])
                    return false;
        return true;
    }
};
set<node> s;
int maze[N][N];
int beginx,beginy,keyx,keyy,doorx,doory,endx,endy;
bool needkey,cihuibian;
int qian[10000005];
int jilu[10000005];
priority_queue<node,vector<node>,greater<node> > q;
int id=0;
void chuangjianxin(node& xin,node& now){
    xin=now;
    xin.id=++id;
    xin.step++;
    if(cihuibian){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(xin.kuai[i][j]==4)
                    xin.kuai[i][j]=5;
                else if(xin.kuai[i][j]==5)
                    xin.kuai[i][j]=4;
                else if(xin.kuai[i][j]==6)
                    xin.kuai[i][j]=7;
                else if(xin.kuai[i][j]==7)
                    xin.kuai[i][j]=6;
                else if(xin.kuai[i][j]==8)
                    xin.kuai[i][j]=4;
            }
        }
    }
    qian[xin.id]=now.id;
}
void shuchu(int eid){
    vector<int> ans;
    while(eid!=1){
        ans.push_back(jilu[eid]);
        eid=qian[eid];
    }
    for(int i=ans.size()-1;i>=0;i--){
        if(ans[i]==0)
            printf("上 ");
        else if(ans[i]==1)
            printf("下 ");
        else if(ans[i]==2)
            printf("左 ");
        else
            printf("右 ");
    }
    puts("");
}
bool judge(node& xin){
    if(xin.x==keyx&&xin.y==keyy)
        xin.key=true;
    if(xin.key&&xin.x==doorx&&xin.y==doory)
        xin.door=true;
    if(xin.door&&abs(xin.x-endx)+abs(xin.y-endy)==1){
        printf("%d\n",xin.step);
        shuchu(id);
        return true;
    }
    return false;
}
void bfs(){
    node chushi;
    chushi.id=++id;
    if(needkey){
        chushi.key=false;
        chushi.door=false;
    }
    else{
        chushi.key=true;
        chushi.door=true;
    }
    chushi.x=beginx;
    chushi.y=beginy;
    chushi.step=0;
    memcpy(chushi.kuai,maze,sizeof(maze));
    q.push(chushi);
    s.insert(chushi);
    while(!q.empty()){
        bool flag=false;
        node now=q.top();
        q.pop();
        for(int i=0;i<4;i++){
            if(now.kuai[now.x+dx[i]][now.y+dy[i]]==0){
                if(now.key&&now.x+dx[i]==doorx&&now.y+dy[i]==doory){
                    node xin;
                    chuangjianxin(xin,now);
                    xin.kuai[doorx][doory]=1;
                    xin.x=doorx;
                    xin.y=doory;
                    jilu[xin.id]=i;
                    if(s.find(xin)!=s.end())
                        id--;
                    else{
                        if(judge(xin)){
                            flag=true;
                            break;
                        }
                        q.push(xin);
                        s.insert(xin);
                    }
                }
            }
            else if(now.kuai[now.x+dx[i]][now.y+dy[i]]==1){
                node xin;
                chuangjianxin(xin,now);
                xin.x=now.x+dx[i];
                xin.y=now.y+dy[i];
                jilu[xin.id]=i;
                if(s.find(xin)!=s.end())
                    id--;
                else{
                    if(judge(xin)){
                        flag=true;
                        break;
                    }
                    q.push(xin);
                    s.insert(xin);
                }
            }
            else if(now.kuai[now.x+dx[i]][now.y+dy[i]]==2||now.kuai[now.x+dx[i]][now.y+dy[i]]==8){
                node xin;
                chuangjianxin(xin,now);
                if(xin.kuai[now.x][now.y]==4)
                    xin.step++;
                jilu[xin.id]=i;
                if(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==0||xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==3||xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==4||xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==6||xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==7)
                    xin.kuai[now.x+dx[i]][now.y+dy[i]]=1;
                else if(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==1){
                    xin.kuai[now.x+dx[i]][now.y+dy[i]]=1;
                    xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]=2;
                }
                else if(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==5){
                    xin.kuai[now.x+dx[i]][now.y+dy[i]]=1;
                    xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]=8;
                }
                if(s.find(xin)!=s.end())
                    id--;
                else{
                    q.push(xin);
                    s.insert(xin);
                }
            }
            else if(now.kuai[now.x+dx[i]][now.y+dy[i]]==3||now.kuai[now.x+dx[i]][now.y+dy[i]]==6||now.kuai[now.x+dx[i]][now.y+dy[i]]==7){
                node xin;
                chuangjianxin(xin,now);
                if(xin.kuai[now.x][now.y]==4)
                    xin.step++;
                jilu[xin.id]=i;
                if((now.x+2*dx[i]!=doorx||now.y+2*dy[i]!=doory)&&(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==1||xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==4||xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==5)){
                    if(xin.kuai[now.x+dx[i]][now.y+dy[i]]==3)
                        xin.kuai[now.x+dx[i]][now.y+dy[i]]=1;
                    else if(xin.kuai[now.x+dx[i]][now.y+dy[i]]==6)
                        xin.kuai[now.x+dx[i]][now.y+dy[i]]=4;
                    else if(xin.kuai[now.x+dx[i]][now.y+dy[i]]==7)
                        xin.kuai[now.x+dx[i]][now.y+dy[i]]=5;
                    if(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==1)
                        xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]=3;
                    else if(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==4)
                        xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]=6;
                    else if(xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]==5)
                        xin.kuai[now.x+2*dx[i]][now.y+2*dy[i]]=7;
                }
                if(s.find(xin)!=s.end())
                    id--;
                else{
                    q.push(xin);
                    s.insert(xin);
                }
            }
            else{
                node xin;
                chuangjianxin(xin,now);
                if(xin.kuai[now.x+dx[i]][now.y+dy[i]]==4)
                    xin.step++;
                jilu[xin.id]=i;
                xin.x=now.x+dx[i];
                xin.y=now.y+dy[i];
                if(s.find(xin)!=s.end())
                    id--;
                else{
                    if(judge(xin)){
                        flag=true;
                        break;
                    }
                    q.push(xin);
                    s.insert(xin);
                }
            }
        }
        if(flag)
            break;
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>maze[i][j];
    cin>>beginx>>beginy;
    cin>>needkey;
    if(needkey){
        cin>>keyx>>keyy;
        cin>>doorx>>doory;
        maze[keyx][keyy]=1;
        maze[doorx][doory]=0;
    }
    else{
        keyx=-1;
        keyy=-1;
        doorx=-1;
        doory=-1;
    }
    cin>>cihuibian;
    cin>>endx>>endy;
    maze[endx][endy]=0;
    bfs();
    int t;
    cin>>t;
    return 0;
}