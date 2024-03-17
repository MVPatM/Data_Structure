import java.io.*;

public class As11 {

	public static void main(String[] args){	
		
		int l_num, i, min, temp_n, w;
		String first, min_mc, temp_str;
		
		try {			
			BufferedReader rd = new BufferedReader(new FileReader("input.txt"));
			BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
			
			first = rd.readLine();
			l_num = Integer.parseInt(first);
			
			temp_str = rd.readLine();
			w = temp_str.indexOf(" ");
			min = Integer.parseInt(temp_str.substring(0, w));
			w += 1;
			min_mc = temp_str.substring(w);
			
			for (i = 1; i < l_num; i++){
				temp_str = rd.readLine();
				w = temp_str.indexOf(" ");
				temp_n = Integer.parseInt(temp_str.substring(0, w));
				
				if (min > temp_n) {
					min = temp_n;
					w += 1;
					min_mc = temp_str.substring(w);
					}
				}
			rd.close();
			
			wr.write(min_mc);
			wr.newLine();
			wr.close();
		}
		catch (IOException e){
			System.out.println("ERROR");
		}

	}
}
