public class UF {
	public int[] parent, card;
	
	public UF(int vertices) {
		parent = new int[vertices];
		card = new int[vertices];
		
		for (int i = 0; i < vertices; i++) {//initialize
			parent[i] = -1;
			card[i] = 1;
		}
	}
	
	public boolean union(int v1, int v2) {//if a pair of edge is in the same group, return false 
		int p1, p2;
		p1 = find(v1);
		p2 = find(v2);
		
		if (p1 == p2) {
			return false;
		}
		
		if (card[p1] >= card[p2]) {//more cardinality, being root node
			parent[v2] = p1;
			card[p1] += card[p2];
		}
		else {
			parent[v1] = p2;
			card[p2] += card[p1];
		}
		
		return true;
	}
	
	public int find(int v) {//return parent
		int p;
		
		do {
			p = v;
			v = parent[v];
			
		}while (v != -1);
		
		return p;
	}

}
