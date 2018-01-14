#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

int main(){
	const float DEG_TO_RAD = 0.0174532925f;
	int angle=45;
	double opposite=0;
	double adjacent=5;
	double hypo=0;
	opposite = (adjacent*(tan(angle*DEG_TO_RAD)));
	hypo = (adjacent/(cos(angle*DEG_TO_RAD)));
	cout<<"op: "<<opposite<<"	hypo: "<<hypo<<endl;

	system("pause");


	return 0;
}