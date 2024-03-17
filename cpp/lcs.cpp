#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string str1, str2;
int dp[70010];
int before, cur;

int Solve();

int main(void) {
	fastio;
	
	ifstream fin;
	fin.open("Q1.txt");

	getline(fin, str1);
	getline(fin, str2);
	
	cout << Solve();

	fin.close();
	return 0;
}

int Solve() {
	int i, j = 1;
	int len1 = str1.length(), len2 = str2.length();
	for (i = 1; i <= len1; i++) {
		before = 0;

		for (j = 1; j <= len2; j++){
			if (str1[i-1] == str2[j-1]) 
				cur = dp[j - 1] + 1;
			else 
				cur = max(before, dp[j]);

			dp[j - 1] = before;
			before = cur;
		}

		dp[j] = cur;
	}

	return dp[j];
}