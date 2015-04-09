#include "StdAfx.h"
#include "Analyze.h"


Analyze::Analyze(void)
{
	conn = NULL;
	res = NULL;
	DBclass = new DBConnection;
	myRoot = new osg::Group;
}


Analyze::~Analyze(void)
{
	
}


char * Analyze::callBackValue(char *(*callfunct)(const PGresult * res,int tup_num,int field_num),const PGresult * res,int tup_num,int field_num)
{
	return callfunct(res,tup_num,field_num);
}



/*type ---0 �� ---1
  ---0 ��ʾ��ѡ�й��ߵ�����ŷ��� ����������Ĺ���
  ---1 ��ʾ��ѡ�й��ߵ��յ��ŷ��� ����������Ĺ���
*/
set<CString> Analyze::getIDs(CString tableName,CString objectID,int type)
{
	//string result = "";
	//connect to db
	set<CString> vec;
	int *row_num=new int(0);

	char *startID,*endID;
	startID = NULL;
	endID = NULL;
	if (!conn)
	{
		DBclass->ConnectToDB(conn,"192.168.1.111","5432","HRBPipe","postgres","123456");
	}
	//char *sql = "select rs.�����,rs.�յ��� from (select �����,�յ��� from baoguan('"+tableName+"', '"+objectID+"',"+type+")) as rs";
	CString sql ;
	sql.Format("select rs.�����,rs.�յ���,st_astext(rs.geom) from (select �����,�յ���,geom from baoguan('%s','%s','%d')) as rs",tableName,objectID,type);
	//std::cout<<"sql getIDs() is :"<<sql<<endl;
	res=DBclass->ExecSQL(conn,sql,row_num);

	for (int i=0;i<(*row_num);i++)
	{
	startID = this->callBackValue(PQgetvalue,res,i,0);
	endID = this->callBackValue(PQgetvalue,res,i,1);
	vec.insert(startID);
	vec.insert(endID);
	}

	return vec;
}
set<CString> Analyze::getAllIDs(CString tableNameOfLine,CString objectID)
{
	set<CString> vec;
	set<CString> vec_end ;
	set<CString> vec_start ;

	vec_end =  this->getIDs(tableNameOfLine, objectID, 0);//[F26RSG21637, F26RSG21636, F26RSG21631, F26RSG21630, F26RSG21632]
	vec_start = this->getIDs(tableNameOfLine, objectID, 1);//[F26RSG21640, F26RSG21638, F26RSG21639, F26RSG21637, F26RSG21636]

	

	for(set<CString>::iterator it1=vec_end.begin();it1!=vec_end.end();it1++){
		CString key = (CString) *it1;
		vec.insert(key);
	}

	
	for(set<CString>::iterator it2=vec_start.begin();it2!=vec_start.end();it2++){
		CString key = (CString) *it2;
		vec.insert(key);
		
	}
	
	return vec;
}

//�ڹܵ���л�ȡ�����ܵ� ���marker;
void Analyze::addMarker(MapNode * mapNode,osg::Group * root,CString tableNameOfPoint,CString objectID)
{
	CString result = "";
	CString sql = "";
	char * startGeometry;
	char * endGeometry;
	startGeometry = NULL;
	endGeometry = NULL;
	sql.Format("select ������,st_astext(geom),����߳�,��ʶ�� as mygeom from %s where ��̽���='%s'",tableNameOfPoint,objectID);
	std::cout<<"sql getValve()  is  :"<<sql<<endl;
	int *row_num=new int(0);
	if (!conn)
	{
		DBclass->ConnectToDB(conn,"192.168.1.111","5432","HRBPipe","postgres","123456");
		res=DBclass->ExecSQL(conn,sql,row_num);
	}else
	{
		res=DBclass->ExecSQL(conn,sql,row_num);
	}
	
	Style pin;		
	std::string noteName="hello";
	GeoPoint geoPoint;
	pin.getOrCreate<IconSymbol>()->url()->setLiteral( "E:/HRB/data/placemark32.png" );
	const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();

	// just one record
	PipePoint * _point;
	_point = NULL;
	for (int i=0;i<(*row_num);i++)
	{
		string fushuwu;//������;
		CString temp = "";
		string pointStr;//point(x,y,z)
		char * geom_temp;//geometry
		char * elevation;
		char * idOfPoint;
		fushuwu = this->callBackValue(PQgetvalue,res,i,0);//�ܵ�ĸ�����
		geom_temp = this->callBackValue(PQgetvalue,res,i,1);//�ܵ��geometry
		elevation = this->callBackValue(PQgetvalue,res,i,2);//�ܵ�ĵ���߳�
		idOfPoint = this->callBackValue(PQgetvalue,res,i,3);//�ܵ�ı�ʶ��

		_point = new PipePoint(geom_temp,elevation);
		//temp.Format("POINT(%d,%d,%d)",_point->getLon(),_point->getLat(),_point->getEle());
		temp.Format("POINT(%.14f,%.15f,%.14f)",_point->getLon(),_point->getLat(),_point->getEle());
		pointStr = temp.GetBuffer(0);
	
		if (fushuwu == "��ˮ��")
		{
			myRoot->addChild(new PlaceNode(mapNode, GeoPoint(geoSRS, _point->getLon(),_point->getLat(),_point->getEle()),idOfPoint, pin));
			cout<<"��ӳɹ�"<<endl;
			objectIDsVector.insert(idOfPoint);
			Id_Geom.insert(map<std::string,std::string>::value_type(idOfPoint,pointStr));
		}
	}
	
	/*bgMarkerLayer=new ModelLayer("bgMarker",myRoot);
	mapNode->getMap()->addModelLayer(bgMarkerLayer);*/
	if (_point!=NULL)
	{
		delete _point;
		_point = NULL;
	}
}
void Analyze::addMarkers(MapNode * mapNode,osg::Group * root,CString tableNameOfLine,CString tableNameOfPoint,CString objectID)
{
	set<CString> IDs;
	CString geom;
	IDs = this->getAllIDs(tableNameOfLine,objectID);
	for (set<CString>::iterator it = IDs.begin();it!=IDs.end();it++)
	{
		this->addMarker(mapNode,root,tableNameOfPoint,(*it));
	}
	bgMarkerLayer=new ModelLayer("bgMarker",myRoot);
	mapNode->getMap()->addModelLayer(bgMarkerLayer);
}

boolean Analyze::clearMarkers(MapNode * mapNode)
{
	//dynamic_cast<osgEarth::ModelLayer*>(mapNode->getMap()->getModelLayerByName("bgMarker"))->setVisible(false);
	bgMarkerLayer->setVisible(false);
	return 1;
}

