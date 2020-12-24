public class CList {
	public CNode first;
	public CNode last;
	
	public CList() {
		first = null;
		last = null;
	}
	
	public void append (int x) {
		CNode newnode = new CNode();
		
		newnode.data = x;
		if (first == null) { 
			first = newnode;
			last = newnode;
			last.next = first;
		}
		else {
			last.next = newnode;
			last = newnode;
			last.next = first;
		}
	}
	
	public CIter getIter() {
		if (first == null)
			return new CIter(null, null, this);
		else
			return new CIter(first, last, this);
	}
}
