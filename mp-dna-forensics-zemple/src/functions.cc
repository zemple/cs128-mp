#include "functions.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int CountMax(const string& sequence, const string& dna) {
  int count = 0;
  int max = 0;
  for (unsigned int i = 0; i < sequence.size(); i++) {
    while (sequence.substr(i, dna.length()) == dna) {
      i += dna.length();
      count++;
    }
    if (count > max) {
      max = count;
      count = 0;
    }
  }
  return max;
}


string Search(string str, string sequence) {

  vector<vector<string>> dataframe;
  ifstream ifs{str};
  for (string line; getline(ifs,line); line = "") {
    dataframe.push_back(utilities::GetSubstrs(line, ','));
  }
  vector<string> names = dataframe[0];

  for (unsigned int i = 0; i < sequence.size(); i++) {
    if (sequence[i]!= 'A' && sequence[i] != 'T' && sequence[i] != 'G' && sequence[i] != 'C') {
      return "No match";
    }
  }

	for (unsigned int i = 1; i < dataframe.size(); i++) {
    if (stoi(dataframe[i][1]) == CountMax(sequence, names[1])) {
		  for (unsigned int j = 1; j < names.size(); j++) {
			  while (stoi(dataframe[i][j]) == CountMax(sequence, names[j])) {
          if (j == names.size()-1) {
            return dataframe[i][0];
          }
          j++;
			  }
		  }
	  }
  }
  return "No match";
}

void Print(string str1, string str2) {
  cout << Search(str1, str2) << endl;
}