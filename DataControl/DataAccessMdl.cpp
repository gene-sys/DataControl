#include "StdAfx.h"
#include "DataAccessMdl.h"


DataAccessMdl::DataAccessMdl(void)
{
}
std::vector<std::string>  DataAccessMdl::ReadDataBases() {
	// открыть св€зь с SQL сервером
	// объ€вить ADODB соединение и рекордсет
	ADODB::ConnectionClass^ cnn = gcnew ADODB::ConnectionClass();
	ADODB::RecordsetClass ^ rs = gcnew ADODB::RecordsetClass();
	cnn->Open("provider=SQLOLEDB.1;Data Source=(local);Initial Catalog='master';User Id='sa';Password='123456'","","",-1);
	rs->CursorLocation = ADODB::CursorLocationEnum::adUseClient;
	rs->Open("select name from sys.databases", cnn,ADODB::CursorTypeEnum::adOpenStatic,ADODB::LockTypeEnum::adLockBatchOptimistic,-1);

	std::vector <std::string> v_name_base;
	rs->MoveFirst();
	int ir=rs->RecordCount;
	//Loop through the Record set
	for(int i=0;i<ir;i++)	{
		ADODB::Field^ fld= rs->default[0];
		String^ i_str=fld->default->ToString();
		v_name_base.push_back(SysToStd(i_str));
		rs->MoveNext();
	}

	rs->ActiveConnection = nullptr;
	cnn->Close();

	return v_name_base;
}

/**
* @brief
*/
   void DataAccessMdl::NewTable() {
   }


	/**
	* @brief
	*/
  std::vector <std::string>   DataAccessMdl::ReadTables(std::string namebase) {		
	  //use DBN1
      //SELECT * FROM sys.objects WHERE type in (N'U')
	  // объ€вить ADODB соединение и рекордсет
	  ADODB::ConnectionClass^ cnn = gcnew ADODB::ConnectionClass();
	  ADODB::RecordsetClass ^ rs = gcnew ADODB::RecordsetClass();

	  char connStr[1024]; 
	  memset(connStr,0,1024);
	  sprintf(connStr, "provider=SQLOLEDB.1;Data Source=(local);Initial Catalog='%s';User Id='sa';Password='123456'",namebase.c_str());
	   String^ clistr = gcnew String(connStr);
	  cnn->Open(clistr,"","",-1);
	  rs->CursorLocation = ADODB::CursorLocationEnum::adUseClient;
	  rs->Open("SELECT * FROM sys.objects WHERE type in (N'U')", cnn,ADODB::CursorTypeEnum::adOpenStatic,ADODB::LockTypeEnum::adLockBatchOptimistic,-1);

	  std::vector <std::string> v_name_base;
	  if (rs->State==1 && rs->RecordCount>0) {
		  rs->MoveFirst();
		  int ir=rs->RecordCount;
		  //Loop through the Record set
		  for(int i=0;i<ir;i++)	{
			  ADODB::Field^ fld= rs->default[0];
			  String^ i_str=fld->default->ToString();
			  v_name_base.push_back(SysToStd(i_str));
			  rs->MoveNext();
		  }
	  }
	  rs->ActiveConnection = nullptr;
	  cnn->Close();

	  return v_name_base; 
  }

  std::vector <std::string>   DataAccessMdl::ReadStrucTeble(std::string namebase,std::string nametbl) {
	//use DBN1
	//select * from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME = N'tblCont' ;
	  std::vector <std::string> v_name_tbl;
	  return v_name_tbl;
  }

  // функци€ вывода сообщени€ в лог файл
void DataAccessMdl::StringLogOut(char* tik) {
	FILE *strm; //
	char sDate[18];
	struct tm *tday;
	time_t gtime;
	//
	time(&gtime); // получить системную дату
	tday=localtime(&gtime); // преобразовать к локалным
	strftime(sDate, 18, "%d.%m.%y %H:%M:%S",tday);

	strm=fopen("dbme.log","a");
	if (strm != NULL) {
		long size;

		fseek(strm, 0, SEEK_END);
		size = ftell(strm);
		fseek(strm, 0, SEEK_SET);
		if (size>1000000) {
			fclose(strm);
			strm=fopen("dbme.log","w");
		}
		fprintf(strm,"%s - %s\n",sDate, tik); // пропустить первую строку
		fclose(strm);
	}
}

/**/
const std::string DataAccessMdl::SysToStd(System::String^ SysStr){
	char *v = (char*) (Marshal::StringToHGlobalAnsi(SysStr)).ToPointer() ;
	std::string result = std::string(v);
	Marshal::FreeHGlobal(System::IntPtr((void*)v));
	return result;
}


	//  онвертаци€ std::string в System::String*
System::String^ DataAccessMdl::StdToSys(std::string StdStr){
	 String ^systemstring = gcnew String(StdStr.c_str());
		return (systemstring);
}