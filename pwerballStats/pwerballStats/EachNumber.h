#ifndef _EACHNUMBER_H_
#define _EACHNUMBER_H_
#include <string>
#include <map>
using namespace std;

class Number
{
public:
	Number();
	Number(string str_in);
	~Number();
	void populateMapsCounter();
	void addMainCount();
	int getMainCount();
	string getMainInt();
	void addFollower(string string_in);
	void addPowerFollower(string string_in);
	map<string, int> printFollowers();
private:
	string mainInt;
	map<string, int> followNums;
	map<string, int> followPows;
	int mainCount;
};

#endif