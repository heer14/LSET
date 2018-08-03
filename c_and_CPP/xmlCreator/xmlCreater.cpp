#include <iostream>
#include <fstream>
#include<string.h>
using namespace std;

typedef struct xmlNode
{
	char key[1000];
	char value[1000];
};

 
int main()
{
	
	ifstream myfile;
	myfile.open ("input.txt" , ios::in);
	cout<<"file opened sucessfully"<< endl;
	char data[10000] ;
	char xmlKey[1000] ,xmlValue[1000] ;
	myfile >> data ; 
	
	//for output file 
	
	ofstream outfile ;
	outfile.open("output.xml" , ios::out);
	outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl << "<members> " << endl ;
	outfile<< "<user>"<<endl ;
	
	
	
	int i =0 , v=0, k =0 ,p=0 ,u=0 ,cnt=0 , max=0; 
	while(i < strlen(data) ){
 		char c = data[i];
		
		if( c == '[')
			 cnt++;
		else if (c ==']')
				cnt--;
		else
		{
		if (cnt==2 && c!='[' && c!=']')
			{
				while(c!=']')
				{
				if(c!=']' && c!='['){
				xmlKey[k] = c ;
				k++;
				}
				i++;
				c=data[i];
				if( c == '[')cnt++;
				else if (c ==']')cnt--;
				}
				
				while(c!='[')
				{
				if(c!=']' && c!='['){
				xmlValue[v] = c ;
				v++;
				}
				i++;
				c=data[i];
				if( c == '[') cnt++;
				else if (c ==']') cnt--;
				}
				
				xmlKey[k] = NULL;
				xmlValue[v] = NULL; 
				struct xmlNode node;
			
				
				k=0;
				v=0;
				
				strcpy( node.key , xmlKey );
				strcpy(node.value  , xmlValue  );
				
				cout <<"node : " << node.key << ":" << node.value <<endl ; 
				outfile << "<" << node.key << ">" << node.value  << "</" << node.key << ">" << endl ;
				if(cnt == 1 ) { 
				outfile << "</user >"<<endl <<"<user>"<<endl ;
				u++;  p=0;}
				else p++;
			}
		}
		i++;	
	}
	outfile << "</user>" << endl ;
	outfile <<"<members>" << endl << "</xml>" ;
	return 0;
	}