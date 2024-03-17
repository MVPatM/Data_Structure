import java.io.*;

public class As31 {
	public static void main(String[] args) {
		try {
			BufferedReader rd = new BufferedReader(new FileReader("input.txt"));
			BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
			
			String infix = rd.readLine();
			rd.close();
			String output = "";
			int length = infix.length();//string's length
			int n = 0; //string's index + 1 = length
			char ch;
			stack operands = new stack();
			
			while(length > n) {
				ch = infix.charAt(n); 
				
				if (ch == '(') {
					operands.push(ch);
				}
				else if (ch == ')') {
					while (operands.peek() != '(') {
						output += operands.pop();
					}
					operands.pop();
				}
				else if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/')) {
					while (!operands.isempty() && !operands.islow(ch)) {
							output += operands.pop();
							}
					operands.push(ch);
				}
				else {
					output += ch;
				}
				n += 1;
			}
			
			while (!operands.isempty()) {
				output += operands.pop();
			}
			
			wr.write(output);
			wr.close();
		}
		catch (IOException e) {
			System.out.println("ERROR");
		}
	}
}
