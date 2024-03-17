#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

//use the biginteger class for c++ from https://www.geeksforgeeks.org/bigint-big-integers-in-c-with-example/
class BigInt {
    string digits;
public:
    //Constructors:
    BigInt(unsigned long long n = 0);
    BigInt(string&);
    BigInt(const char*);
    BigInt(BigInt&);

    //Helper Functions:
    friend bool Null(const BigInt&);
    friend int Length(const BigInt&);
    int operator[](const int)const;

    //Direct assignment
    BigInt& operator=(const BigInt&);

    //Post/Pre - Incrementation
    BigInt& operator++();
    BigInt operator++(int temp);
    BigInt& operator--();
    BigInt operator--(int temp);

    //Addition and Subtraction
    friend BigInt& operator+=(BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt& operator-=(BigInt&, const BigInt&);

    //Comparison operators
    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);

    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator>=(const BigInt&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator<=(const BigInt&, const BigInt&);

    //Multiplication and Division
    friend BigInt& operator*=(BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt& operator/=(BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);

    //Read and Write
    friend ostream& operator<<(ostream&, const BigInt&);
    friend istream& operator>>(istream&, BigInt&);
};

BigInt::BigInt(string& s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(unsigned long long nr) {
    do {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}
BigInt::BigInt(const char* s) {
    digits = "";
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(BigInt& a) {
    digits = a.digits;
}

bool Null(const BigInt& a) {
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}
int Length(const BigInt& a) {
    return a.digits.size();
}
int BigInt::operator[](const int index)const {
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}
bool operator==(const BigInt& a, const BigInt& b) {
    return a.digits == b.digits;
}
bool operator!=(const BigInt& a, const BigInt& b) {
    return !(a == b);
}
bool operator<(const BigInt& a, const BigInt& b) {
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}
bool operator>(const BigInt& a, const BigInt& b) {
    return b < a;
}
bool operator>=(const BigInt& a, const BigInt& b) {
    return !(a < b);
}
bool operator<=(const BigInt& a, const BigInt& b) {
    return !(a > b);
}

BigInt& BigInt::operator=(const BigInt& a) {
    digits = a.digits;
    return *this;
}

BigInt& BigInt::operator++() {
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++)
        digits[i] = 0;
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}
BigInt BigInt::operator++(int temp) {
    BigInt aux;
    aux = *this;
    ++(*this);
    return aux;
}

BigInt& BigInt::operator--() {
    if (digits[0] == 0 && digits.size() == 1)
        throw("UNDERFLOW");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++)
        digits[i] = 9;
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}
BigInt BigInt::operator--(int temp) {
    BigInt aux;
    aux = *this;
    --(*this);
    return aux;
}

BigInt& operator+=(BigInt& a, const BigInt& b) {
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++) {
        if (i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

BigInt& operator-=(BigInt& a, const BigInt& b) {
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(),
        n--;
    return a;
}
BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

istream& operator>>(istream& in, BigInt& a) {
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i];
    }
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        cout << (short)a.digits[i];
    return cout;
}

// /, * •û±â
BigInt arr[100001];
int len = 0;

void QuickSort(int from, int to);

int main(void) {
	fastio;
    // open the file
    arr[0] = 10;
    arr[1] = 5;
    arr[2] = 1;
    arr[3] = 11;
    arr[4] = 7;
    arr[5] = 9;

    QuickSort(0, 6);
    // print the result 
    for (int i = 0; i < 6; i++)
        cout << arr[i] << " ";

    // close the file
	return 0;
}

void QuickSort(int from, int to) {
    if (from >= to)
        return;
    
    srand((unsigned int)time(NULL));
    int pivot_pos = rand() % (to - from + 1);

    BigInt pivot = arr[pivot_pos + from];
    arr[pivot_pos + from] = arr[from];
    pivot_pos = from;

    int j;
    BigInt var;
    for (j = from + 1; j <= to; j++) {
        if (arr[j] < pivot) {
            pivot_pos++;
            var = arr[pivot_pos];
            arr[pivot_pos] = arr[j];
            arr[j] = var;
        }
    }

    arr[from] = arr[pivot_pos];
    arr[pivot_pos] = pivot;

    QuickSort(from, pivot_pos - 1);
    QuickSort(pivot_pos + 1, to);
}
