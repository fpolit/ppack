/*
 * CVSReade class definition
 * A class to read data from a csv file.
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef _CSV_H
#define _CSV_H

#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

#include <boost/algorithm/string.hpp>

class CSVReader
{

private:
  string filename;
  string delimeter;

public:
  CSVReader(string filename, string delm = ",");
  // Function to fetch data from a CSV File
  vector<vector<string>> get_data();
};

#endif //_CSV_H
