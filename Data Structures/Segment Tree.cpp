template< typename T, const T MERGE(const T&, const T&) >
struct node
{
  int l, r, mid;
  T val;
  std::unique_ptr<node<T,MERGE>> L, R;
 
  node( int _l, int _r ) : l( _l ), r ( _r )
  {
    mid = ( l + r ) >> 1;
    if( l == r ) 
    {
      val = T();
      return; 
    }
    L = std::make_unique<node<T,MERGE>>( l, mid );
    R = std::make_unique<node<T,MERGE>>( mid + 1, r );
    val = MERGE( L-> val, R-> val );
  }
 
  void set_value( int x, const T n_val )
  {
    if( l == r )
    {
      val = n_val;
      return;
    }
    ( x <= mid ? L : R ) -> set_value( x, n_val );
    val = MERGE( L-> val, R-> val );
  }
 
  T query( int x, int y )
  {
    if( x == l && y == r )
      return val;
 
    if( y <= mid ) return L->query( x, y );
    if( x > mid ) return R->query( x, y );
    return MERGE( L->query( x, mid ), R ->query( mid + 1, y ) );
  }
};
