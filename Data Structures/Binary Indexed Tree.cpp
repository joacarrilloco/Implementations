const int LG = 20;

struct BIT
{
  vector< long long > bit;

  BIT( int n )
  {
    bit.resize( n + 1 );
  }

  void add( int x, int del )
  {
    for( ++x; x < (int) bit.size(); x += x & -x )
      bit[x] += del;
  }

  long long query( int x )
  {
    long long ans = 0;
    for( ++x; x; x -= x & -x )
      ans += bit[x];

    return ans;
  }

  long long query_range( int l, int r )
  {
    return query( r ) - query( l - 1 );
  }

  int query_last_LE( long long lb )
  {
    long long sum = 0;
    int x = 0;
    for( int l = LG; l >= 0; --l )
    {
      int y = x + ( 1 << l );
      if( y < (int) bit.size() && sum + bit[y] <= lb )
      {
        x = y;
        sum += bit[x];
      }
    }
    return --x;
  }
};
