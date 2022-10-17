#include <windows.h>
#include<iostream>
#include<opencv/opencv2.hpp>
#include <shellapi.h>
using namespace std;
int main()
{
	string Url = "http://192.168.43.18:80/left";
	char a;
	cin >> a;
	
	
	system(string("start " + Url).c_str());
	
}
