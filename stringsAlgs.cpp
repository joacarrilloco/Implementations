int phi[N];

void kmpProcess( string & s ){
	phi[0] = -1;
	for( int i = 0, j = -1; i < s.length();  ){
		while( j > -1 && s[i] != s[j] ) j = phi[j];
		j++, i++;
		phi[i] = j;
	}
}

int kmpSearch( string & s, string & p ){
	kmpProcess( p );
	int matches = 0;
	for( int i = 0, j = 0; i < s.length();  ){
		while( j > -1 && s[i] != p[j] ) j = phi[j];
		i++, j++;
		if( j == p.length() ) j = phi[j], matches++;
	}	
	return matches;
}



int z[N];

void Z( string &s){
	int r = 0, l = 0;
	for( int i = 1; i<s.length(); i++ ){
		if( i > r ){
			l = r = i;
			while( r < s.length() && s[r] == s[r - l] ) r++;
			z[i] = r - l;
			r--;
		}else{
			int a = i - l;
			if( z[a] <= r - i ){
				z[i] = z[a];
			}else{
				l = i;
				while( r < s.length() && s[r] == s[r-l] ) r++;
				z[i] = r - l;
				r--;
			}
		}
	}
}


int minimum_expression( string s ){
	s = s + s;
	int i = 0, j = 1, k = 0;
	while( j + k < s.length() && i + k < s.length()){
		if( s[i+k] == s[j+k] ){
			k++;
		}else if( s[i + k] > s[j + k] ){
			i = i + k + 1;
			if( i <= j ) i = j + 1;
			k = 0;
		}else{
			j = j + k + 1;
			if( j <= i ) j = i + 1;
			k = 0;
		}
	}
	return min(i,j);
}


//to = i - from[i];
//len = to - from[i] + 1 = i - 2 * from[i] + 1;
vector<int>  manacher ( string &s ) {
    int p = 0, pr = -1;
    vector < int > from (2 * s.length() - 1, 0);
    for (int i = 0; i < from.size(); ++i) {
        int r = i <= 2*pr ? min(p - from[2*p - i], pr) : i/2;
        int l = i - r;
        while (l > 0 && r < s.length()-1 && s[l-1] == s[r+1]) --l, ++r;
        from[i] = l;
        if (r > pr) pr = r, p = i;
    }
    return from;
}



//suffix array


vector < int > v;
int n, sa[maxN], ra[maxN], tsa[maxN], cn[maxN], saI[maxN], tra[maxN];

void cnsrt( int k ){
	memset( cn, 0, sizeof cn );
	
	int bound = max( 321, n ); // sigma 
	
	for( int i = 0; i < n; i++ ){
		cn[i + k< n ? ra[i + k] : 0]++;
	}
	
	int sum = 0;
	for( int i = 0; i <bound; i++ ){
		int t  = cn[i];
		cn[i] = sum;
		sum += t;
	}
	
	for( int i = 0; i < n; i++ ){
		tsa[ cn[ sa[i] + k < n ? ra[sa[i] + k] : 0 ]++] = sa[i];
	}
	
	for( int i = 0; i <n; i++ ) 
		sa[i] = tsa[i];
}

build_sa(){
	
	n = v.size();
	
	for( int i = 0; i < n; i++ ) sa[i] = i;
	for( int i = 0; i < n; i++ ) ra[i] = v[i];
	
	for( int k = 1; k < n; k<<=1 ){
		cnsrt( k );
		cnsrt( 0 );
		
		int r = 0;
		tra[sa[0]] = 0;
		for( int i = 1; i < n; i++ ){
			tra[sa[i]] = ( ra[sa[i]] == ra[sa[i-1]]  && ra[sa[i] + k] == ra[sa[i-1] + k]) ? r : ++ r;
		}
		
		for( int i = 0; i < n; i++ ) ra[i] = tra[i];
		if( ra[sa[n-1]] == n - 1 ) break;
	}
	
	for( int i = 0; i < n; i++ ) saI[sa[i]] = i;
}
