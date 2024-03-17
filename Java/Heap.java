public class Heap {
	public int[] d;
	public int entry;//array d's length
	
	public Heap(int size) { //constructor 
		d = new int[size+1];
		entry = 0;
	}
	
	public boolean isEmpty() {
		return entry == 0;
	}
	
	public void insert(int x) {
		int pos = ++entry;
			
		while ((d[pos/2] > x) && (pos != 1)) { 
			d[pos] = d[pos/2];
			pos = pos/2;
			}
		d[pos] = x;
	}
	
	public int deleteMin() {
		if (isEmpty()) {
			return Integer.MAX_VALUE;
		}
		else {
			int min = d[1];
			int last = d[entry--];
			int parent = 1; //index
			int childs = 2; //index
			
			while (entry >= childs) {
				if (entry > childs) { //select the candidate
					if (d[childs] > d[childs+1]) {
						childs += 1;
					}
				}
				
				if (last <= d[childs]) { // don't change
					break;
				}
				//change
				d[parent] = d[childs];
				parent = childs;
				childs = 2 * parent;
			}
			
			d[parent] = last;
			return min;
		}
	}

	public int queryMin() {
		if (isEmpty()) {
			return Integer.MAX_VALUE;
		}
		else {
			return d[1];
		}
	}
	
	public static void sort(int[] a, int n) {
		Heap s = new Heap(n);
		int i;
		
		for (i = 1; i <= n; i++) {
			s.insert(a[i]);
		}

		for (i = n; i > 0; i--) {
			a[i] = s.deleteMin();
		}
	}
}
