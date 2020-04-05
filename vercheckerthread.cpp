#include "vercheckerthread.h"
#include "externData.h"
#include "mainResources.h"
#include "Connector.h"
#include "Utils.h"

void VerCheckerThread::run()
{
	while(true) {
		const char request[] = "https://raw.githubusercontent.com/uis246/nesca/master/version";
		std::string buffer;
//		std::vector<std::string> headerVector{ "X-Nescav3: True" };
		Connector con;
		con.nConnect(request, 443, &buffer);

		uint_fast32_t newVer;
		{
			const char *ver;
			ver=strstr(buffer.c_str(), "\r\n\r\n");
			if(ver)
				newVer=(uint_fast32_t)atoi(ver+4);
			else
				newVer=0;
		}
			if(newVer > (uint_fast32_t)atoi(gVER))
		{
			stt->doEmitionFoundData("<br><font color=\"Pink\">======Update required======<br>Latest version: " + QString(to_string(newVer).c_str()) +
									"<br>Your version: " + QString(gVER) + "<br>=========================</font>");
			stt->doEmitionShowRedVersion();
		}
		vct->sleep(600000); //10 min
	}
	//vct->terminate();
}
