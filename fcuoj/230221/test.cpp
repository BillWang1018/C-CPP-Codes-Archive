#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    string line;
    int count[91] = {0};
    cin >> n;
    getchar();
    while(n--)
    {
        getline(cin, line);
        for(int i=0 ; i<line.size() ; i++)
        {
            if(line[i]>='a' && line[i]<='z')
                count[line[i]-'a'+'A']++;
            else
                count[line[i]]++;
        }
    }
    for(int i=sizeof(line) ; i>=1 ; i--)
    {
        for(int j='A'; j<='Z'; j++)
        {
            if(count[j] == i)
                cout << char(j) << " " << i << endl;
        }
    }
    return 0;
}