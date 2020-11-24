/*
 * CVSReade class definition
 * Allow you read CVS files,  23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef __INCLUDE_CSV_H__
#define __INCLUDE_CSV_H__
#include "../include/csv.hpp"
#endif //__INCLUDE_CSV_H__



#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_


#ifndef __INCLUDE_FSTREAM_H__
#define __INCLUDE_FSTREAM_H__
#include<fstream>
#endif //__INCLUDE_FSTREAM_H__


#ifndef __INCLUDE_ALGORITHM_H__
#define __INCLUDE_ALGORITHM_H__
#include<algorithm>
#endif //__INCLUDE_ALGORITHM_H__


#ifndef __INCLUDE_BOOST_ALGORITHM_H__
#define __INCLUDE_BOOST_ALGORITHM_H__
#include <boost/algorithm/string.hpp>
#endif //__INCLUDE_BOOST_ALGORITHM_H__


std::vector<std::vector<std::string>> CSVReader::getData()
/*
 * Parses through csv file line by line and returns the data
 * in vector of vector of strings.
 */
{
  std::ifstream file(fileName);
  std::vector<std::vector<std::string> > dataList;
  std::string line = "";
  // Iterate through each line and split the content using delimeter
  while (getline(file, line))
    {
      std::vector<std::string> vec;
      boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
      dataList.push_back(vec);
    }
  // Close the File
  file.close();
  return dataList;
}
