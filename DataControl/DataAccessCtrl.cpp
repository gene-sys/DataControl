#include "StdAfx.h"
#include "DataAccessCtrl.h"


DataAccessCtrl::DataAccessCtrl(void)
{
	m_Data= new DataAccessMdl();
}


DataAccessCtrl::~DataAccessCtrl(void)
{
}

std::vector<std::string> DataAccessCtrl::ReadDataSrv(){
	return m_Data->ReadDataBases();

}

std::vector<std::string> DataAccessCtrl::ReadDataBase(std::string m_base) {
	return m_Data->ReadTables(m_base);
}