/*
 * CVSReade class definition
 * Allow you read CVS files,  23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

//#include "ppack/csv.hpp"
#include "../include/csv.hpp"

CSVReader::CSVReader(string filename, string delm = ",")
  :filename(filename), delimeter(delm)
{ }

vector<vector<string>> CSVReader::get_data()
/*
 * Parses through csv file line by line and returns the data
 * in vector of vector of strings.
 */
{
  std::ifstream file(filename);
  std::vector<std::vector<std::string> > dataList;
  std::string line = "";
  // Iterate through each line and split the content using delimeter
  while (getline(file, line))
    {
      vector<string> vec;
      boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
      dataList.push_back(vec);
    }
  // Close the File
  file.close();
  return dataList;
}
