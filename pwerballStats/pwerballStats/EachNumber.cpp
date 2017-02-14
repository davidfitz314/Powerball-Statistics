#include <sstream>
#include <iostream>
#include "EachNumber.h"


Number::Number()
{
	//default constructor
	this->mainInt = "0";
	this->mainCount = 0;
}

Number::Number(string str_in)
{
	//string in constructor
	this->mainInt = str_in;
	this->mainCount = 1;
	this->populateMapsCounter();
}

Number::~Number()
{
	//deconstructor
}

void Number::populateMapsCounter()
{
	if (mainInt[0] != 'p' && mainInt[0] != 'x'){	
		for (int i = 1; i <= 69; i++)
		{
			if (i < 10){
				string zero = "0";
				stringstream ss;
				ss << i;
				string str = ss.str();
				zero += str;
				followNums[zero] = 1;
			} else {
				stringstream ss;
				ss << i;
				string str = ss.str();
				followNums[str] = 1;
			}
		}
	
		for (int i = 1; i <= 26; i++)
		{
			if (i < 10){
				string zero = "p0";
				stringstream ss;
				ss << i;
				string str = ss.str();
				zero += str;
				followPows[zero] = 1;
			} else {
				string zero = "p";
				stringstream ss;
				ss << i;
				string str = ss.str();
				zero += str;
				followPows[zero] = 1;
			}
		}
	}
}

void Number::addMainCount()
{
	this->mainCount += 1;
}

int Number::getMainCount()
{
	return this->mainCount;
}

string Number::getMainInt()
{
	return this->mainInt;
}

void Number::addFollower(string string_in)
{
	if (followNums.find(string_in) == followNums.end()){
		//send error
//		cout << "error" << endl;
		return;
//		exit(0);
	} else {
		followNums[string_in] += 1;
	}
}

void Number::addPowerFollower(string string_in)
{
	if (followPows.find(string_in) == followPows.end()){
		//send error
//		cout << "error" << endl;
		return;
//		exit(0);
	} else {
		followPows[string_in] += 1;
	}
}

map<string, int> Number::printFollowers()
{
	/*for (map<string, int>::iterator it = followNums.begin(); it != followNums.end(); ++it)
	{
		if (it->second > 1){
			cout << it->first << " => " << it->second << endl;
		}
	}*/
	return this->followNums;
}