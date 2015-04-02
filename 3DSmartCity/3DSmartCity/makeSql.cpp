#include "StdAfx.h"
#include "makeSql.h"


makeSql::makeSql(void)
{
}

makeSql::makeSql(char* tn)
{
	this->mTableName = string(tn);
}

makeSql::makeSql(string tn)
{
	this->mTableName = tn;
}

makeSql::~makeSql(void)
{
}

//管网查询sql
string makeSql::makePolySql(double topleftlat,double topleftlon,double bottomrightlat,double bottomrightlon)
{
	char* p = "POLYGON((126.652002305689 45.7528259108467, 126.653364042412 45.7528259108467, 126.653364042412 45.747337756813, 126.652002305689 45.747337756813, 126.652002305689 45.7528259108467))')";
	string begin("select gid,标识码 from (select *,");
	string end(" as queryresult where isContain=true");
	string s;
	ostringstream buf;
	buf.precision(13);  
    buf.setf(std::ios::fixed); // 将浮点数的位数限定为小数点之后的位数 
	buf<<"st_contains(st_geomfromtext('polygon(("<<topleftlon<<' '<<topleftlat<<','<<bottomrightlon<<' '
		<<topleftlat<<','<<bottomrightlon<<' '<<bottomrightlat<<','<<topleftlon<<' '<<bottomrightlat<<','
		<<topleftlon<<' '<<topleftlat<<"))'),ysgline_new.geom) as isContain from ysgline_new )";
	s = buf.str();
	string sql;
	sql = begin.append(s);
	sql = sql.append(end);
	//p = const_cast<char*>(s.c_str());
	return sql;
}

string makeSql::flowDirectionSql(string bzm)
{
	//flow_direction('ysgline_new','28028')
	ASSERT(bzm.find(this->mTableName)==0);
	int x = bzm.find(' ');
	string b = bzm.substr(x+1);
	string sql = "select flow_direction('" + mTableName + "','" + b + "')";
	return sql;
}