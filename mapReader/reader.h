#ifndef READER
#define READER

#include "GeoData.cpp"

class Reader {
    private: 
        enum Status { NORM, ABNORM };
        std::vector<GeoData> _geoData;
        //collect the names to search easier for an element
        std::vector<std::string> _geoDataNames;
        Status _currentStatus;
        std::ifstream _file;
        std::string currentLine;
        bool _end;
        int iterator{};

        Status checkStatus();

        void createStreet(const std::string & name);
        int searchForStreetIndex(const std::string & str);
        void processLine(const std::string & str, const int & index);
        std::vector<std::string> lineSplit(const std::string & str);
        bool checkEmpty(const int & index, const std::string & str);
        Street intPairToStreet(const int & fstElement, const int & scndElement);
        void checkRoadsAreEmpty(const std::string & str, const int & index);

    public:
        enum Error { FILE_NOT_FOUND, EMPTY_FILE };

        Reader(const std::string & str);

        void read();
        void next();
        bool end() const { return _end; }
        
        std::vector<GeoData> getGeoData() const { return _geoData; }
        bool checkElementIfTrue(const std::vector<Street> & vector, GeoData gd);
        void printVectorIfTrue(const std::string & type, const std::vector<Street> & vector, GeoData gd);
        void processData(const std::vector<GeoData> & geoData);
};

#endif //READER