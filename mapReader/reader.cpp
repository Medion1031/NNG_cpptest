#include <sstream>

#include "reader.h"

Reader::Reader(const std::string & str) {
    _file.open(str.c_str());

    if(_file.fail()) {
        throw FILE_NOT_FOUND;
    }
}

void Reader::first() {
    next();

    if(_geoData.name.empty()) {
        throw EMPTY_FILE;
    }
}

Reader::Status Reader::checkStatus() {
    if(_file.fail()) {
        return ABNORM;
    }
    return NORM;
}

void Reader::next() {
    std::string str;
    getline(_file, str);

    _currentStatus = checkStatus();
    _end = _currentStatus == ABNORM;

    if(!_end) {
        std::cout << "this is a line" << std::endl;
    }
}