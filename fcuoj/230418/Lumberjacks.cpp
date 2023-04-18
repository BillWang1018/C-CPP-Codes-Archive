#include <iostream>
using namespace std;
int main() {
	int N, t;
	cin >> N;
	cout << "Lumberjacks:\n";
	while(N--) {
		int nums[10];
		bool accending;
		bool flag = true;
		for(int i=0; i<10; i++) {
			cin >> nums[i];
			if(i==1)
				accending = nums[i-1] < nums[i];
			if(i>1)
				if((nums[i-1] < nums[i]) ^ accending )
					flag = false;
		}
		
		cout << (flag? "Ordered" : "Unordered") << "\n";
		
	}
	
	return 0;
}
