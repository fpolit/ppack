/*
 * CVSReade class definition
 * Allow you read CVS files,  23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __CSV_H__
#define __CSV_H__

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H_


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



class CSVReader
/*
 * A class to read data from a csv file.
 */
{
private:
    std::string fileName;
    std::string delimeter;
public:
    CSVReader(std::string filename, std::string delm = ",") :
            fileName(filename), delimeter(delm)
    { }
    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string>> getData();
};


#endif //__CSV_H__
