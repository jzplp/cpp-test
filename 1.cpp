#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> ve;

void output()
{
  for (auto ip = ve.begin(); ip != ve.end(); ++ip)
    cout << *ip << endl;
}

string computed(int a)
{
  string s;
  int i, j;
  for (i = 0; i < ve[a - 1].size(); ++i)
  {
    if (i >= ve[a].size())
      break;
    if (ve[a][i] == ve[a - 1][i])
      s.push_back(ve[a][i]);
    else if (ve[a][i] == ve[a - 1][i] + 1)
    {
      s.push_back(ve[a - 1][i]);
      return s;
    }
    else
    {
      s.push_back(ve[a - 1][i] + 1);
      return s;
    }
  }
  if (i < ve[a - 1].size())
  {
    if (ve[a - 1][i] != 'Z')
    {
      s.push_back(ve[a - 1][i] + 1);
      return s;
    }
    else
    {
      s.push_back(ve[a - 1][i]);
      // s.push_back('A');
      return s;
    }
  }
  if (i < ve[a].size())
  {
    if (ve[a][i] != 'A')
    {
      // s.push_back(ve[a][i] - 1);
      return s;
    }
    else
      return s;
  }
  return s;
}

int main()
{
  int n, i, j;
  string s;
  while (cin >> n && n > 0)
  {
    ve.clear();
    for (i = 0; i < n; ++i)
    {
      cin >> s;
      ve.push_back(s);
    }
    sort(ve.begin(), ve.end());
    i = n / 2;
    cout << computed(i) << endl;
    // output();
  }
}
