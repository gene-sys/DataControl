#pragma once


#include "DataAccessMdl.h"


class DataAccessCtrl
{
public:
	DataAccessCtrl(void);
	~DataAccessCtrl(void);
	std::vector<std::string> ReadDataSrv();
	std::vector<std::string> ReadDataBase(std::string);

	DataAccessMdl* m_Data;
};

