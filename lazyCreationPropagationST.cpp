struct Node
{
  Node *left, *right;
  int val, lv, rv;
  bool prog;

  Node(int l, int r)
  {
    val = prog = 0;
    lv = l, rv = r;
    left = right = NULL;
  }

  ~Node()
  {
    if( left != NULL ) delete left;
    if( right != NULL ) delete right;
  }

  void propagate()
  {
    if( prog )
    {
      val = ( rv - lv + 1 ) - val;
      if( lv != rv ) 
      {
        ll mid = ( lv + rv ) / 2;
        if( left == NULL ) left = new Node( lv, mid );
        if( right == NULL ) right = new Node( mid + 1, rv );
        left->prog^=1, right->prog^=1;
      }
      prog = 0;
    }
  }

  void update( int l, int r )
  {

    ll mid = ( lv + rv ) / 2;

    if( lv != rv && left == NULL ) left = new Node( lv, mid );
    if( lv != rv && right == NULL ) right = new Node( mid + 1, rv );
    
    propagate();

    if( lv == l && rv == r )
    {
      prog ^= 1;
      propagate();
      return; 
    }

    if( mid >= r ) left->update( l, r );
    else if( l > mid ) right->update( l, r );
    else left->update( l, mid ), right->update( mid+1, r );

    left->propagate(), right->propagate();
    val = (left->val) + (right->val);

    if( left->val == 0 ) 
    {
      delete left;
      left = NULL;
    }

    if( right-> val == 0 )
    {
     delete right;
     right = NULL;
    }
  }

};