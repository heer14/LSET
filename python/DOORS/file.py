import socket

dxl_command = b"""
// String replacement function
string replace (string sSource, string sSearch, string sReplace) 
{
int iLen = length sSource
if (iLen == 0) return ""

int iLenSearch = length(sSearch)

if (iLenSearch == 0) 
{ 
    print "search string must not be empty"
    return "" 
}

// read the first char for latter comparison -> speed optimization
char firstChar = sSearch[0]

Buffer s = create() 
int pos = 0, d1,d2;    
int i

while (pos < iLen) { 
    char ch = sSource[pos]; 
    bool found = true

    if (ch != firstChar) {pos ++; s+= ch; continue}
    for (i = 1; i < iLenSearch; i++) 
       if (sSource[pos+i] != sSearch[i]) { found = false; break }
    if (!found) {pos++; s+= ch; continue}
    s += sReplace
    pos += iLenSearch
}

string result = stringOf s
delete s
return result
}
Module currentModule = read("/Car/Daimler/DAIMLER_OMS/SAD/AP/LGE_Daimler_OMSEntry_SW Architecture Design_AP", false, false)
Object obj
Stream outfile = write("C:\\Users\\hiral.sanjaybhaishah\\Desktop\\Git\\Programming\\python\\DOORS\\output.txt" , 8 )
string s = " "
for obj in currentModule do
{   
   s = obj."Object Text"
   s = replace(s,"\n","\\n")
   outfile << s "\n"    
}
close outfile

"""

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 5094))
s.send(dxl_command)
s.send(b"quit_")
s.close()