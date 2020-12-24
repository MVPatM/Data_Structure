public class Heap {
	public node[] d;
	public int entry;//array d's length
	
	// ������ cost�� minimum heap�� ����� edge�� ���� ������ �־� �־�� �Ѵ�.
	public Heap(int size) { //constructor 
		d = new node[size+1];
		entry = 0;
	
		for (int i = 0; i < (size + 1); i++) {
			d[i] = new node();
		}
	}
	
	public boolean isEmpty() {
		return entry == 0;
	}
	
	public void insert(int x) {
		int pos = ++entry;
		node in = new node();
		in.cost = x;
		in.edge = pos - 1;
		//d[0]�� �ʱ�ȭ ���� ������ d[0].cost �� ���� ������ �Ұ��� �ϴ�.
			
		while ((d[pos/2].cost > x) && (pos != 1)) { //up from bottom to root, if parent is bigger
			d[pos] = d[pos/2];
			pos = pos/2;
			}
		
		d[pos] = in;//insert node
	}

	public node deleteMin() {
		if (isEmpty()) {
			return null;
		}
		else {
			node min = d[1];//minimum value's node
			node last = d[entry--];//last node(cost, edge)
			int parent = 1; //index
			int childs = 2; //index
			
			while (entry >= childs) {
				if (entry > childs) { //select the candidate
					if (d[childs].cost > d[childs+1].cost) {
						childs += 1;
					}
				}
				
				if (last.cost <= d[childs].cost) { // don't change
					break;
				}
				//change
				d[parent] = d[childs];
				parent = childs;
				childs = 2 * parent;
			}
			
			d[parent] = last;
			
			return min;//return minimum value's node
		}
	}
}


