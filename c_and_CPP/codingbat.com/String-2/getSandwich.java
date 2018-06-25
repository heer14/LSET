public String getSandwich(String str) {
String ans;
int first_bread = -1;
int last_bread = -1;
  for(int i=0; i< str.length() - 5; i++){
    if(str.charAt(i) == 'b' &&
    str.charAt(i) == 'r' &&
    str.charAt(i) == 'e' &&
    str.charAt(i) == 'a' &&
    str.charAt(i) == 'd' && ) first_bread = i;
  }
  if(first_bread != -1)
  {
     for(int i=str.length()-1 ;i>=5 ;  i-- ){
       if(str.charAt(i) == 'd' &&
       str.charAt(i) == 'a' &&
       str.charAt(i) == 'e' &&
       str.charAt(i) == 'r' &&
       str.charAt(i) == 'b' && ) last_bread = i;
     }
     if (last_bread != -1)
     {
       char[] n = new char[last_bread - first_bread] ;
       for(int i= first_bread ; i< last_bread ; i++)
       {
         n[k] = str.charAt(i);
         k++;
       }
        ans = new String(n);
    }
  else{ ans= new String(" ");}
}
else{ ans= new String(" ");}
return ans;

}
