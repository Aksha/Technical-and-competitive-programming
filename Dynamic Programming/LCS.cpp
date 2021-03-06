int n = s1.size()-1;
int m = s2.size()-1;
int result = 0;

string LCS(string s1, string s2, int n, int m) { 
  if(n == 0 && m == 0) {
    return 0;
  }
  if(s1[n] == s2[m]) 
    result = 1 + LCS(s1,s2,n-1,m-1);
  else if(s1[n] != s2[m])
    tmp1 = LCS(s1,s2,n,m-1);
    tmp2 = LCS(s1,s3,n-1,m);
    result = max(tmp1,tmp2);
    return result;
}
