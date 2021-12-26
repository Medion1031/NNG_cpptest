#include <sstream>
#include <iostream>
#include <vector>

#include "reader.h"

Reader::Reader(const std::string & str) {
    _file.open(str.c_str());

    if(_file.fail()) {
        throw FILE_NOT_FOUND;
    }
}

void Reader::first() {
    next();

    if(_geoData[0].getName().empty()) {
        throw EMPTY_FILE;
    }
}

Reader::Status Reader::checkStatus() {
    if(_file.fail()) {
        return ABNORM;
    }
    return NORM;
}

std::vector<std::string> lineSplit(const std::string & str) {
   std::vector<std::string> outputArray;
   std::stringstream streamData(str);
   std::string val;

   while(std::getline(streamData, val, ',')) {
       std::cout << val << "\n";
       outputArray.push_back(val);
   } 

   return outputArray;
}

void Reader::next() {
    std::string str;
    getline(_file, str);

    _currentStatus = checkStatus();
    _end = _currentStatus == ABNORM;

    if(!_end) {
        //TODO: megcsinalni a beolvasot.
        lineSplit(str);
    }
}