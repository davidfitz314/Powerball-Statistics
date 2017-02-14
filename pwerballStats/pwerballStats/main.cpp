#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;
#include "EachNumber.h"

double totalcounts = 69;
double totalcounts2 = 26;
map<string, int> powerballcounts;
map<string, int> powerballpower;
map<string, Number> allNums;
vector<string> MostPopularOrder;

void counter(string st_in)
{
	stringstream ss(st_in);
	string first, second, third, fourth, fifth;
	int count = 0;
	//cout << "check this " << endl;
	while (ss.good()){
		string substr;
		getline(ss, substr, ' ');
		if (count == 0){
			first = substr;
			//find map for first string
			//add next element for follower.
			count += 1;
		} else if (count == 1){
			second = substr;
			allNums[first].addFollower(second);
			count += 1;
		} else if (count == 2){
			third = substr;
			allNums[second].addFollower(third);
			count += 1;
		} else if (count == 3){
			fourth = substr;
			allNums[third].addFollower(fourth);
			count += 1;
		} else if (count == 4){
			fifth = substr;
			allNums[fourth].addFollower(fifth);
			count += 1;
		} else if (count >= 5 && substr[0] != 'x'){
			allNums[first].addPowerFollower(substr);
			allNums[second].addPowerFollower(substr);
			allNums[third].addPowerFollower(substr);
			allNums[fourth].addPowerFollower(substr);
			allNums[fifth].addPowerFollower(substr);
		}
		//add substring to other numbers
		//cout << substr << endl;
		if ( powerballcounts.find(substr) == powerballcounts.end() ) {

			if (substr[0] == 'p'){
				powerballpower[substr] += 1;
			}
		} else {
			powerballcounts[substr] += 1;
			if (substr[0] == 'p')
			{
				totalcounts2 += 1;
			} else if (substr[0] == 'x') {
				//do nothing
			} else {
				totalcounts += 1;
			}
		}
		allNums[substr].addMainCount();
		//cout << "count " << allNums[i].getMainCount() << endl;
		//cout << substr << endl;
	}
}

void mostPopularNumbers()
{
	//copy the map
	map<string, int> tempM = powerballcounts;
	map<string, int>::iterator bye;
	for (int i = 0; i < 69; i++)
	{
		string currentMostPop = "100";
		int currentMostPopCount = 0;
		for (map<string, int>::iterator it = tempM.begin(); it != tempM.end(); ++it)
		{
			if (it->second > currentMostPopCount){
				currentMostPop = it->first;
				currentMostPopCount = it->second;
			}
		}
		cout << currentMostPop << endl;
		MostPopularOrder.push_back(currentMostPop);
		bye = tempM.find(currentMostPop);
		tempM.erase(bye);
	}
}

void populateMapsCounters(){
	for (int i = 1; i <= 69; i++)
	{
		if (i < 10)
		{
			string zero = "0";
			stringstream ss;
			ss << i;
			string str = ss.str();
			zero += str;
			powerballcounts[zero] = 1;
			Number temp = Number(zero);
			allNums[zero] = temp;
		} else {
			stringstream ss;
			ss << i;
			string str = ss.str();
			powerballcounts[str] = 1;
			Number temp = Number(str);
			allNums[str] = temp;
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
			powerballpower[zero] = 1;
			Number temp = Number(zero);
			allNums[zero] = temp;
		} else {
			string zero = "p";
			stringstream ss;
			ss << i;
			string str = ss.str();
			zero += str;
			powerballpower[zero] = 1;
			Number temp = Number(zero);
			allNums[zero] = temp;
		}
	}
}


int main(){
	ifstream pballs;
	pballs.open("powerball.txt");
	if (!pballs){
		cout << "error in opening file." << endl;
		exit(0);
	}

	ofstream outfile;
	outfile.open("stats.txt");
	if (!outfile){
		cout << "error writing to file" << endl;
		exit(0);
	}
	//populate maps with default minimums
	populateMapsCounters();

	//pass data to powerball maps
	string line;
	while (getline(pballs,line))
	{
//		cout << line << endl;
		counter(line);
//		outfile << line << endl;
	}

	//print maps data to file
	outfile << "Each Number chosen By Powerball since Oct 7th, 2015 and it's frequency rate." << endl;
	outfile << "All probabilities have been given laplace smoothing" << endl;
	outfile << "Chosen Number => Amount of times chosen" << endl;
	outfile << endl;
	for (map<string, int>::iterator it = powerballcounts.begin(); it != powerballcounts.end(); ++it)
	{
		outfile << it->first << " => " << it->second << endl;
		outfile << "total percentage " << double(it->second)/totalcounts << endl;
		outfile << endl;
	}

	for (map<string, int>::iterator it = powerballpower.begin(); it != powerballpower.end(); ++it)
	{
		outfile << it->first << " => " << it->second << endl;
		outfile << "total percentage " << double(it->second)/totalcounts2 << endl;
		outfile << endl;
	}

	outfile << "Each Number and the followers" << endl;
	outfile << "Due to laplace smoothing only followers with a count greater then 1 were included" << endl;
	outfile << endl;
	for (map<string, Number>::iterator it = allNums.begin(); it != allNums.end(); ++it)
	{
		if (it->first.find("x") == string::npos && it->first.find("p") == string::npos){

			//outfile << it->first << " => " << it->second.getMainCount() << endl;
			outfile << "print main num: " << it->first << endl;

			map<string, int> temp = it->second.printFollowers();
			outfile << "Number Following => amount of times followed" << endl;
			for (map<string, int>::iterator it2 = temp.begin(); it2 != temp.end(); it2++)
			{
				if (it2->second > 1){
					outfile << it2->first << " => " << it2->second << endl;
				}
			}
		}
		outfile << endl;
	}

	outfile << "Ordered by Most Popular to Least" << endl;
	outfile << endl;
	mostPopularNumbers();
	for (int i = 0; i < MostPopularOrder.size(); i++){
		outfile << MostPopularOrder[i] << endl;
	}
	pballs.close();
	
	return 0;
}