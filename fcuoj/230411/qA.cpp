#include <iostream>
#include <iomanip>
using namespace std;
int main() {
	
	string a, b;
	while(cin >> a) {  //How (check EOF)
		double n;
		cin >> a;	   //many
		cin >> a;	   //a
		cin >> b >> b; //are in
		cin >> n >> b; //n b?
		
		a = a.substr(0,5), b = b.substr(0,5);

		if	   (a == "centi" && b == "meter")
			printf("%.1f\n", (n*100));
		else if(a == "meter" && b == "centi")
			printf("%.1f\n", (n/100));
		else if(a == "kilog" && b == "pound")
			printf("%.1f\n", (n*0.46));
		else if(a == "pound" && b == "kilog")
			printf("%.1f\n", (n/0.46));
		else if(a == "milli" && b == "liter")
			printf("%.1f\n", (n*1000));
		else if(a == "liter" && b == "milli")
			printf("%.1f\n", (n/1000));
		else
			printf("ERROR\n");
	}
	return 0;
}
