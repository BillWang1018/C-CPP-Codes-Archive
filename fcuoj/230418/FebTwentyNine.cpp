#include <iostream>
#include <string>
using namespace std;

bool checkLunar(int n) {
	return (!(n%4) && (n%100 || !n%400));
}


int main() {
	int T;
	cin >> T;
	for (int _=1; _<=T; _++) {
		string m1, d1, y1, m2, d2, y2;
		cin >> m1 >> d1 >> y1 >> m2 >> d2 >> y2;
		
		int mi, di, yi, mii, dii, yii;
		auto monthToInt = [](string m) -> int {
			if(m == "January") return 1;
			if(m == "February") return 2;
			if(m == "March") return 3;
			if(m == "April") return 4;
			if(m == "May") return 5;
			if(m == "June") return 6;
			if(m == "July") return 7;
			if(m == "August") return 8; 
			if(m == "September") return 9;
			if(m == "October") return 10;
			if(m == "November") return 11;
			if(m == "December") return 12;
		};
		
		mi = monthToInt(m1);
		mii = monthToInt(m2);
		
		di = stoi(d1.substr(0, d1.size()-1));
		dii = stoi(d2.substr(0, d2.size()-1));
		
		yi = stoi(y1);
		yii = stoi(y2);
		
		int ans{};
		
		if(mi <= 2) //  check first year, yi-- if 2/29 is excluded
			yi--;	
			
		if(mii <= 2) // check last year, yii-- if 2/29 is excluded
			yii--;
		if(mii == 2 && dii == 29)
			yii++;
		
		ans = (yii/4 - yii/100 + yii/400) - (yi/4 - yi/100 + yi/400); // count from yi+1 ~ yii
		cout << (yii/4 - yii/100 + yii/400) << " " << ((yii-1)/4 - (yii-1)/100 + (yii-1)/400) << " ";
		
		cout << "Case " << _ << ": " << ans << "\n";
	}
	
	return 0;
}
