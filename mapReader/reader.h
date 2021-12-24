#ifndef READER
#define READER

#include <fstream>

struct GeoData {
    std::string name;
    char rightScheme;
    int rightStart;
    int rightEnd;
    char leftScheme;
    int leftStart;
    int leftEnd;
};

class Reader {
    private: 
        enum Status { NORM, ABNORM };
        GeoData _geoData;
        Status _currentStatus;
        std::ifstream _file;
        bool _end;

    public:
        enum Error { FILE_NOT_FOUND, EMPTY_FILE };

        Reader(const std::string & str);

        void first();
        void next();
        Status checkStatus();
        
        GeoData current() const { return _geoData; }
        bool end() const { return _end; }
};

#endif //READER