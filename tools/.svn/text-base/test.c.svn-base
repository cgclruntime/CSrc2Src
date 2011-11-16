#include<stdio.h>
#define abs(x) (x>0?x:-(x))
int p[MAXN],root,tot,top,ans;
int f(int x)
{
	if(x!=p[x])p[x]=f(p[x]);
	return p[x];
}
struct node{
    int par,left,right;
    int key,sl;
}tree[MAXN];
void zig(int x) {
     int y=tree[x].par;
     tree[x].sl=tree[y].sl;
     tree[y].sl--;
     if (tree[x].left) tree[y].sl-=tree[tree[x].left].sl;
     tree[y].left=tree[x].right;
     if (tree[x].right) tree[tree[x].right].par=y;
     tree[x].par=tree[y].par;
     if (tree[y].par) {
         if (tree[tree[y].par].left==y) tree[tree[y].par].left=x;
         else tree[tree[y].par].right=x;
     }
     tree[y].par=x;tree[x].right=y;
}
void zag(int x) {
     int y=tree[x].par;
     tree[x].sl=tree[y].sl;
     tree[y].sl--;
     if (tree[x].right) tree[y].sl-=tree[tree[x].right].sl;
     tree[y].right=tree[x].left;
     if (tree[x].left) tree[tree[x].left].par=y;
     tree[x].par=tree[y].par;
     if (tree[y].par) {
         if (tree[tree[y].par].left==y) tree[tree[y].par].left=x;
         else tree[tree[y].par].right=x;
     }
     tree[y].par=x;tree[x].left=y;
}
void splay(int now) {
    int t;
    while (tree[now].par) {
        t=tree[now].par;
        if (!tree[t].par) {
            if (now==tree[t].left) zig(now);
            else zag(now);
            break;
        }
        if (now==tree[t].left) {
            if (t==tree[tree[t].par].left) {
                zig(t);                   
                zig(now);
            }
            else {
                zig(now);                 
                zag(now);
            }
        }
        else {
            if (t==tree[tree[t].par].right) {
                  zag(t);                  
                  zag(now);
            }
            else {
                  zag(now);                
                  zig(now);
            }
        }
    }
    root=now;
}
int find(int ff)
{
    int p=root,res;
    while (ff!=tree[p].key) {
        if (ff<=tree[p].key) {
            if (tree[p].left) p=tree[p].left;
            else break;
        }
        else {
            if (tree[p].right) p=tree[p].right;
            else break;
        }
    }
    return p;
}
int findsame(int ff)
{
    int p=root,res;
    while (1) {
        if (ff<=tree[p].key) {
            if (tree[p].left) p=tree[p].left;
            else break;
        }
        else {
            if (tree[p].right) p=tree[p].right;
            else break;
        }
    }
    return p;
}
void dfs(int k)
{
    printf("%d ",tree[k].key);
    if (tree[k].left) dfs(tree[k].left);
    if (tree[k].right) dfs(tree[k].right);
}
void del(int v)
{
    tot--;
    if (tot==0) {
        root=0;
        return;
    }
    int x=find(v);
    if (tree[x].left&&tree[x].right) {
        int y=tree[x].right,pos=1;
        while (tree[y].left) {pos=0;y=tree[y].left;}
        if (pos==0) {
            tree[tree[y].par].left=tree[y].right;
            tree[tree[y].right].par=tree[y].par;
        }
        else {
            tree[x].right=tree[y].right;
            if (tree[y].right) tree[tree[y].right].par=x;
        }
        tree[x].key=tree[y].key;
        
        y=tree[y].par;
        while (y) {tree[y].sl--;y=tree[y].par;}
        
        splay(x);
        return;
    }
    if (tree[x].left==0&&tree[x].right==0) {
        if (tree[x].par) {
            if (tree[tree[x].par].left==x) tree[tree[x].par].left=0;
            else tree[tree[x].par].right=0;
            
            int tem=tree[x].par;
            while (tem) {tree[tem].sl--;tem=tree[tem].par;}
            
            splay(tree[x].par);
        }
        return;
    }
    if (tree[x].par==0) {
        if (tree[x].left) {root=tree[x].left;tree[tree[x].left].par=0;}
        else {root=tree[x].right;tree[tree[x].right].par=0;}
        return;
    }
    
    if (tree[x].left) {
        tree[tree[x].left].par=tree[x].par;
        if (tree[tree[x].par].left==x) tree[tree[x].par].left=tree[x].left;
        else tree[tree[x].par].right=tree[x].left;
    }
    else {
        tree[tree[x].right].par=tree[x].par;
        if (tree[tree[x].par].left==x) tree[tree[x].par].left=tree[x].right;
        else tree[tree[x].par].right=tree[x].right;
    }
    int tem=tree[x].par;
    while (tem) {tree[tem].sl--;tem=tree[tem].par;}
    splay(tree[x].par);
}
void add(int v)
{
    
    tree[++top].key=v;
    tree[top].par=tree[top].left=tree[top].right=0;
    tree[top].sl=1;
    tot++;
    if (tot==1) {
        root=top;
        return;
    }
    int sit=findsame(v);
    if (tree[top].key<=tree[sit].key) {
        tree[sit].left=top;
        tree[top].par=sit;
    }
    else {
        tree[sit].right=top;
        tree[top].par=sit;
    }
    int tem=tree[top].par;
    while (tem) {tree[tem].sl++;tem=tree[tem].par;}
    splay(top);
}
void check(int x,int k)
{
    int tem=0;
    if (tree[x].left) tem=tree[tree[x].left].sl;
    if (tem==k-1) {ans=tree[x].key;return;}
    if (tem>k-1) check(tree[x].left,k);
    else check(tree[x].right,k-tem-1);
}
int tj[MAXN];
int getnum()  
{
    char ch;
    while (ch=getchar(),ch==10||ch==32);
    int ans=ch-48;
    while ((ch=getchar())!=EOF&&(ch>='0'&&ch<='9'))
    {
        ans*=10;
        ans+=ch-'0';
    }
    return ans;
}
int main()
{
    int i,j,n,m,ch,tt,u,v;
    scanf("%d%d",&n,&m);
    for (i=0;i<n;i++) {p[i]=i;tj[i]=1;}
    while (m--) {
		ch=getnum();
		if (ch) {
			tt=getnum();
			if (tt>tot) printf("1\n");
			else {
				check(root,tot+1-tt);
				printf("%d\n",ans);
			}
		}
		else {
			u=getnum();
			v=getnum();
			u=f(u);v=f(v);
			if (u==v) continue;
			p[v]=u;
			if (tj[u]>1) del(tj[u]);
			if (tj[v]>1) del(tj[v]);
			tj[u]+=tj[v];
			add(tj[u]);
		}
	}
	parallel f f1,f2;
	f1(5);
	f2<f1>(10);
	parallel check g1,g2;
	f2<g1&&g2>();
}
