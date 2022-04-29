const T MIN_VALUE = -INF;

template< typename T, const T& MX(const T&, const T&) = std::max >
struct node
{
  int l, r, mid;
  T mx;
  node *L, *R;

  node( int ll, int rr ) : l( ll ), r ( rr )
  {
    mx = MIN_VALUE; 
    mid = ( l + r ) >> 1;
    if( l == r ) return;
    L = new node( l, mid ), R = new node( mid + 1, r );
  }

  void set_value( int x, const T &val )
  {
    if( l == r )
    {
      mx = val;
      return;
    }
    ( x <= mid ? L : R ) -> set_value( x, val );
    mx = MX( L-> mx, R-> mx );
  }

  T query( int x, int y )
  {
    if( x == l && y == r )
      return mx;

    if( y <= mid ) return L->query( x, y );
    if( x > mid ) return R->query( x, y );
    return MX( L->query( x, mid ), R ->query( mid + 1, y ) );
  }
};
