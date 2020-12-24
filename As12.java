public class As12 {

	public static void main(String[] args) {
		Oracle o = new Oracle();
		int tofind, n, left, right, mid;
		boolean ans;
		
		n = o.getN();
		tofind = o.getWhatToFind();
		
		left = 0;
		right = n-1;
		
		while (left<right)
		{
			mid = (left+right)/2;
			if (o.getElementAt(mid) > tofind)
				left = mid+1;
			else
				right = mid;
		}
		
		if ((left==right)&&(o.getElementAt(left)==tofind))
			ans = true;
		else {
			ans = false;
			left = 0;
		}
		
		o.reportAnswer(ans, left);
	}

}
