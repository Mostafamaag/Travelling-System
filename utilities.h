
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int ReadInt(int start , int end){
	cout << "\nEnter Number between " << start << "-" << end <<": ";
	int num ;
	cin >> num;
	if(num >= start || num <= end){
		return num;
	}
	return ReadInt(start,end);
}

//string GetCurrentTimeDate() {
//	auto now = std::chrono::system_clock::now();
//	auto in_time_t = std::chrono::system_clock::to_time_t(now);
//
//	std::stringstream ss;
//	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
//	return ss.str();
//}

int ShowMenu(const vector<string> &menu , string menu_name="Menu") {
	cout << "\n" << menu_name << "\n";
	for (int i = 0 ; i < (int)menu.size(); i++) {
		cout <<"\t" << i+1 <<": "<< menu[i] << "\n";
	}
	return ReadInt(1,menu.size());
}

#endif /* UTILITIES_H_ */
