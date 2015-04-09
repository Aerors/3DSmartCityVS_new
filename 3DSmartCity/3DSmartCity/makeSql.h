#pragma once
#include <sstream>
#include "string"
using namespace std;
class makeSql
{
public:
	makeSql(void);
	makeSql(char* tablename);
	makeSql(string tablename);
	~makeSql(void);
	char* getPolySql(string sql);
public:
	string makePolySql(const double topleftlat,const double topleftlon,const double bottomrightlat,const double bottomrightlon);
	string makeLineSql(const double topleftlat,const double topleftlon,const double bottomrightlat,const double bottomrightlon);
	string flowDirectionSql(string bzm);
	string trackPipeSql(string bzm);
private:
	string mTableName;
};

