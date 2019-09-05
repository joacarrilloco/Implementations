#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
using namespace std;
const int N = 3100 * 3100;
const ll INF = (ll) 1e10;

struct Edge {
  int v, idr;
  ll w, c;
};
vector < Edge > gr[N];

int ss = N-2, tt = N-1, pr[N], ide[N];
ll dis[N], phi[N];


bool dijkstra()
{
  for( int i = 0; i<N; ++i ) dis[i] = INF;
  dis[ss] = 0;
  priority_queue< pair<ll,int> > pq;
  pq.push({0LL,ss});

  while( !pq.empty() )
  {
    int u = pq.top().second;
    ll pd = -pq.top().first;
    pq.pop();

    if( dis[u] != pd ) continue;

    for( int i = 0; i < gr[u].size(); ++i )
    {
      Edge &e = gr[u][i];
      ll nd = pd + e.c + phi[u] - phi[e.v];
      if( e.w && nd < dis[e.v] )
      {
        pr[e.v] = u, ide[e.v] = i;
        dis[e.v] = nd;
        pq.push( {-nd,e.v} );
      }
    }
  }
  for( int i = 0; i < N; ++i ) phi[i] = min( INF, phi[i] + dis[i]);
  return dis[tt] != INF; 
}

void add ( int u, int v, ll w, ll c )
{
  gr[u].push_back( {v, int(gr[v].size()), w, c } );
  gr[v].push_back( {u,int(gr[u].size()-1), 0LL, -c } );
}

pair<ll,ll> mfmc()
{
  memset( phi, 0, sizeof phi );

  ll mf = 0;
  ll mc = 0;
  
  while( dijkstra() )
  {
    ll cf = INF;

    for( int v = tt; v != ss; v = pr[v] )
      cf = min( cf, gr[pr[v]][ide[v]].w );
    if( cf == INF ) return {INF,INF};

    for( int v = tt; v != ss; v = pr[v] )
    {
      auto &e = gr[pr[v]][ide[v]];
      auto &er = gr[v][e.idr];
      e.w -= cf;
      er.w += cf;
      mc += cf * e.c;
    }
    mf += cf;
  }
  return {mf,mc};
}


int main()
{

  return 0;
}