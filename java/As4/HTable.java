class HTable {
	public Node[] table;
	public Node bef;
	public Node checkee;

	// define this method
	public HTable() {
		table = new Node[997];
		bef = null;
		checkee = null;
		
		for (int i = 0; i < 997; i++) {
			table[i] = null;
		}

	}
	
	// define this method
	public boolean insert(String k, int p) {
		int thekey = hash(k);
		
		if (table[thekey] == null) {
			Node ins1 = new Node(k, p, null);
			table[thekey] = ins1;
			return true;
		}
			
		checkee = table[thekey];
		
		while (checkee != null) {
			if (checkee.key == k) {
				return false;
			}
			
			bef = checkee;
			checkee = checkee.next;
		}
		
		Node ins2 = new Node(k, p, null);
		bef.next = ins2;
		
		return true;
	}

	// define this method
	public boolean delete(String k) {
		int thekey = hash(k);
		bef = table[thekey];
		checkee = table[thekey];
		
		while (checkee != null) {
			if (checkee.key == k) {
				if (bef == checkee) {
					table[thekey] = checkee.next;
				}
				else { 
					bef.next = checkee.next;
				}
				return true;
			}
			
			bef = checkee;
			checkee = checkee.next;
		}
		
		return false;
	}

	// define this method
	public int query(String k) {
		int thekey = hash(k);
		checkee = table[thekey];
		
		while (checkee != null) {
			if (checkee.key == k) {
				return checkee.payload;
			}
			
			checkee = checkee.next;
		}
		
		return 0;
	}

	// define this method
	public boolean modify(String k, int p) {
		int thekey = hash(k);
		checkee = table[thekey];
		
		while (checkee != null) {
			if (checkee.key == k) {
				checkee.payload = p;
				return true;
			}
			
			checkee = checkee.next;
		}
		
		return false;
	}

	// do NOT modify this method
	public static int hash(String k) {
		if (k == null)
			return 0;

		int ret = k.hashCode();
		if (ret < 0)
			ret = -ret;
		ret = ret % 997;
		return ret;
	}
}
