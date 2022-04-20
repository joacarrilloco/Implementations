using T = pair< int, int >;
const T MIN_VALUE = make_pair( -INF, -INF );

struct node
{
	int l, r, mid;
	T mx;
	node *L, *R;

	node( int ll, int rr ) : l( ll ), r ( rr )
	{
		mx = MIN_VALUE;
		mid = ( l + r ) / 2;
		if( l == r ) return;
		L = new node( l, mid ), R = new node( mid + 1, r );
	}

	void update( int x, T val )
	{
		if( l == r )
		{
			mx = max( mx, val );
			return;
		}
		( x <= mid ? L : R ) -> update( x, val );
		mx = max( L-> mx, R-> mx );
	}

	T query( int x, int y )
	{
		if( x == l && y == r )
			return mx;

		if( y <= mid ) return L->query( x, y );
		if( x > mid ) return R->query( x, y );
		return max( L->query( x, mid ), R ->query( mid + 1, y ) );
	};
};
