class MST {

	// define this method
    public static boolean find(int n, int m, int[] x, int[] y, int[] c, int[] ans) {
    	int i, out, j, ed;
    	node tp = new node();
    	UF uf = new UF(n);
    	Heap heap = new Heap(m);
    	out = 0;
    	
    	for (i = 0; i < m; i++) {
    		heap.insert(c[i]);
    	}
    	
    	for (j = 0; j < m; j++) {
    		tp = heap.deleteMin();		
    		ed = tp.edge;
    		
    		if (uf.union(x[ed], y[ed])) {
    			ans[out] = ed;
    			out += 1;
    		}
    		
    		if (out == n-1) {
    			return true;
    		}
    	}
    	
		return false;
    }
}
