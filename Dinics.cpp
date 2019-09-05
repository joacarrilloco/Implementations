#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int M = 21000;
const ll INF = (ll) 1e13 ;

int ss = M-2, tt = M-1, vis[M];

struct Edge {
  int v, idr;
  ll w;
};
vector < Edge > gr[M];

bool bfs(){
  queue < int > q;
  memset( vis, 0, sizeof vis );
  vis[ss] = 1;
  q.push( ss );

  while( !q.empty() ){
    int x = q.front();
    q.pop();
    if( x == tt ) return true;

    for( auto P : gr[x] ){
      if( vis[P.v] || P.w == 0 ) continue;
      vis[P.v] = vis[x] + 1;
      q.push(P.v);
    }
  }
  return false;
} 

ll dinics(int u, ll prx )
{
  if( u == tt ) return prx;
  ll res = 0;
  for( auto &P : gr[u] )
  {
    if( P.w == 0 || vis[P.v] != vis[u] + 1 ) continue;
    ll sfx = dinics( P.v, min( P.w, prx ) );
    res += sfx;
    prx -= sfx;
    P.w -= sfx;
    gr[P.v][P.idr].w += sfx;
    if( prx == 0 ) return res;
  }

  if( res == 0 ) vis[u] = -1;
  return res;
}

void add ( int u, int v, ll w )
{
  gr[u].push_back( {v,int(gr[v].size()), w } );
  gr[v].push_back( {u,int(gr[u].size()-1), 0 } );
}

ll flow()
{
  ll mf = 0;
  while( bfs() ) mf += dinics(ss,INF);
  return mf;
}


int main()
{
  
  return 0;  
}

