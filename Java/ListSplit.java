public class ListSplit {
	public Node outn;
	public Node outp;
	
	public ListSplit() {
		outn = new Node();
		outp = new Node();
	}
	
	public void split(Node first) {
		int n = 0;
		Node tn = outn;
		Node tp = outp;
		
		while ((n<10000000) && (first!=null)) {
			if (first.data > 0) {
				tp.data = first.data;//append
				tp.next = first;
				tp = tp.next;
			}else {
				tn.data = first.data;//append
				tn.next = first;
				tn = tn.next;
			}
			first = first.next;
			n += 1;
		}
	}
}
