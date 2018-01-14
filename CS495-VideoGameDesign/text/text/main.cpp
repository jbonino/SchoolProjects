#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(){
	
	for(int i=0;i<6;i++){
		int count=0;
		for(int r=0;r<3;r++){
			for(int c=0;c<3;c++){
				count++;
				
				cout<<"Face: "<<i<<endl;
				if(count==9) cout<<"	END FACE	="<<count<<endl;
			}
		}

	}
	system("pause");
}