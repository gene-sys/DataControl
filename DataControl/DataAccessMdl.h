#pragma once

#include <ctime>
#include <stdio.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <vector>

using namespace ADODB;
//typdef ADODB::Recordset::EOF e_OF_F;
//using e_OF_F =ADODB::Recordset::EOF;

using namespace System;
using namespace System::Data;
using namespace System::Data::OleDb;
using namespace System::Runtime::InteropServices;


class DataAccessMdl
{
public:
	DataAccessMdl(void);
	std::vector <std::string>  ReadDataBases();
	void NewTable();
	std::vector <std::string>  ReadTables(std::string);
	std::vector <std::string>  ReadStrucTeble(std::string namebase,std::string nametbl);
private:
	void StringLogOut(char* );
	const std::string SysToStd(System::String^ );
	System::String^ StdToSys(std::string );
};


