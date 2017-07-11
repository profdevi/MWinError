/*    
    MWinError.exe : Displays the error string for an Windows API error 
    code returned from the GetLastError() function
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


//v1.0 copyright Comine.com 20170711T1116
#include <Windows.h>
#include "MStdLib.h"
#include "TVector.h"
#include "MCommandArg.h"
#include "MLicenseGPL.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MWinError";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static const int GMaxErrorSize=2048;

////////////////////////////////////////////////////
static void GDisplayHelp(void);
static bool GPrintError(DWORD value);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL license(true);
		license.Print();
		return 0;
		}

	///////////////////////////////////////////////
	if(args.GetArgCount()<2)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	for(int i=1;i<args.GetArgCount();++i)
		{
		DWORD errorvalue=MStdAToI(args.GetArg(i));
		GPrintError(errorvalue);
		}


	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s <ErrorCode>+ [-?|-gpl]\n"
				"           v%s copyright Comine.com\n"
				"           -gpl displays the GNU public Licence\n"
				"\n"
				"   Displays the error associated with a error value that comes from\n"
				"   the GetLastError() function of the Windows API\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


///////////////////////////////////////////////////////
static bool GPrintError(DWORD value)
	{
	MStdPrintf(" Code %-8u (0x%08x)  : ",value,value);

	TVector<char> buffer(GMaxErrorSize+2);
	if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,NULL,(DWORD)value
			,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),buffer.Get(),buffer.GetCount(),0)==0)
		{
		MStdPrintf("**Unable to get error string\n");
		return false;
		}

	MStdStrTrimRight(buffer.Get());
	MStdPrintf("%s\n",buffer.Get() );
	return true;
	}


