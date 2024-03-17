public class CIter {
	public CNode cur;
	public CNode prev;
	public CList List;
	
	public CIter(CNode c, CNode p, CList caller) {
		cur = c;
		prev = p;
		List = caller;
	}
	
	public boolean isValid() {
		if (cur == null)
			return false;
		else
			return true;
	}
	
	public int getValue() {
		if (!isValid())
			return -1;
		else
			return cur.data;
	}
	
	public boolean setValue(int x) {
		if (!isValid())
			return false;
		else {
			cur.data = x;
			return true;
		}
	}
	
	public int delete() {
		int ret;
		
		if (!isValid())
			return -1;
		else if (cur == cur.next) {
			ret = cur.data;
			cur = null;
			prev = null;
			List.first = null;
			List.last = null;
			return ret;
		}else if (prev.next == cur) {
			ret = cur.data;
			cur = cur.next;
			prev.next = cur;
			List.first = cur;
			return ret;
		}else if (cur.next == prev) {
			ret = cur.data;
			cur = cur.next;
			prev.next = cur;
			List.last = prev;
			return ret;
		}else {
			ret = cur.data;
			cur = cur.next;
			prev.next = cur;
			return ret;
		}
	}
	
	public boolean insertAfter(int x) {
		CNode newnode = new CNode();
		
		if (!isValid())
			return false;
		else if (cur.next == List.first) {
			if (cur == cur.next)
				prev = newnode;
			List.append(x);
			return true;
		}else {
			newnode.data = x;
			newnode.next = cur.next;
			cur.next = newnode;
			return true;
		}
	}
	
	public void next() {
		if (!isValid()) {
			return;
		}
		else if (prev == cur) {
			cur = cur.next;
		}else {
			prev = cur;
			cur = cur.next;
		}
	}
}
