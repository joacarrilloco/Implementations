#include<memory>

const int INITIAL_VALUE = 0;

template< typename T, const T& MAX(const T&, const T&) = std::max >
struct node
{
  int l, r, mid;
  T mx;
  std::unique_ptr<node<T,MAX>> L, R;

  node( int ll, int rr ) : l( ll ), r ( rr )
  {
    mid = ( l + r ) >> 1;
    if( l == r ) 
    {
      mx = INITIAL_VALUE;
      return; 
    }
    L = std::make_unique<node<T,MAX>>( l, mid );
    R = std::make_unique<node<T,MAX>>( mid + 1, r );
    mx = MAX( L-> mx, R-> mx );
  }

  void set_value( int x, const T &val )
  {
    if( l == r )
    {
      mx = val;
      return;
    }
    ( x <= mid ? L : R ) -> set_value( x, val );
    mx = MAX( L-> mx, R-> mx );
  }

  T query( int x, int y )
  {
    if( x == l && y == r )
      return mx;

    if( y <= mid ) return L->query( x, y );
    if( x > mid ) return R->query( x, y );
    return MAX( L->query( x, mid ), R ->query( mid + 1, y ) );
  }
};
