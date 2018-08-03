#include <iostream>
#include <iomanip>

using namespace std ;
int main()
{
	int n ,snail =0 , cnt=0 , day=1 ;
	cout << "Please input depth of the well(in Centimeter):  ";
	cin >> n;
	while(n > snail  )
	{
		if(day)
		{
			snail+=50 ;
			day =0 ;
			cnt++;
		}
		else if(!day)
		{
			snail-=20 ;
			day=1 ;
		}
//cout << snail << endl;
	}

	std::cout << std::fixed;
	 std::cout << std::setprecision(2);
	cout <<	" It takes " << cnt << " days to escape from the " <<  (double)n/100 <<  " meters deep well." ; 
	return 0;
}