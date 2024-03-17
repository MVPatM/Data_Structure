public class stack {
	public char[] arb;
	public int top;
	
	public stack() {
		arb = new char[1000000];
		top = -1;
	}
	
	public void push(char ch) {
		arb[++top] = ch; // don't consider full
	}
	
	public char pop() {
		return arb[top--]; // don't consider empty
	}
	
	public char peek() {
		return arb[top];
	}
	
	public boolean islow(char ch) {
		if (ch == '+' || ch == '-') {
			if(peek() == '(') {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (peek() == '*' || peek() == '/') {
				return false;
			}
			else {
				return true;
			}
		}
	}
	
	public boolean isempty() {
		return top == -1;
	}
}