#include <bits/stdc++.h>
using namespace std;

void printsubstr(string &str, int &l, int r)
{
    for (int i = l; i < r; i++)
        cout << str[i];
    cout << "\n";
}

void manacher(string &str)
{
    int n = str.size();       // length of the string
    int len = 2 * n + 3;      // length of the new string
    vector<char> schars(len); // new string
    vector<int> p(len, 0);    // array to store the length of the palindrome centered at i

    // adding special characters to the string
    schars[0] = '@';
    schars[len - 1] = '$';
    int t = 1;

    for (char c : str)
    {
        schars[t++] = '#';
        schars[t++] = c;
    }
    schars[t] = '#';

    // manacher's algorithm
    int center = 0, maxright = 0, start = 0, maxlen = 0; // center, rightmost palindrome, start of the longest palindrome, length of the longest palindrome

    for (int i = 1; i < len - 1; ++i)
    {
        if (i < maxright)
            p[i] = min(maxright - i, p[2 * center - i]); // if i is within the rightmost palindrome, p[i] = min(rightmost - i, p[2 * center - i])

        while (schars[i + p[i] + 1] == schars[i - p[i] - 1])
            p[i]++; // expand the palindrome centered at i

        if (i + p[i] > maxright)
        { // if the palindrome centered at i expands beyond the rightmost palindrome
            center = i;
            maxright = i + p[i];
        }

        if (p[i] > maxlen)
        { // if the palindrome centered at i is longer than the longest palindrome found so far
            maxlen = p[i];
            start = (i - p[i]) / 2;
        }
    }

    printsubstr(str, start, start + maxlen);
}

void solve()
{
    string s;
    cin >> s;

    manacher(s);
}

int main()
{
    solve();
}