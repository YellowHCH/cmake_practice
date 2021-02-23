#include "gdb_try.h"
#include <list>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fstream>

void test_strace()
{
  time_t tnow = time(NULL);
  std::list<int> myList;
  for(size_t i = 0; i < 200; ++i)
    {
      myList.push_front(i);
      sleep(1);
    }
  sleep(1);
}

void print_func(char* argv[])
{
  std::cout << "__fun__ " <<  argv[0] << std::endl;
}

void vectoratloop(){
	std::vector<int> v1;
	int idx = 10;
	while (idx > 0)
	{
		for (int i = 0; i < idx; ++i)
		{
			v1.push_back(i);
		}
		--idx;
	}
	for (auto it : v1)
	{
		std::cout << it << " ";
	}
	return;
}

void GetFileContent(char* sPath)
{
	std::ofstream oFile("output.exe");
	std::ifstream iFile(sPath);
	std::string sLine;
	if (iFile)
	{
		while (getline(iFile, sLine))
		{
			std::cout << sLine << std::endl;
			int iTabPos = sLine.find("\t^^");
			std::string sFirstSub = sLine.substr(0, iTabPos);
			if (iTabPos == -1) 
			{
//				std::cout << "not find tab" << std::endl; continue;
				oFile << "not find tab, pos=" << iTabPos << std::endl; continue;
			}
//			std::cout << sFirstSub << "?????" << std::endl;
			oFile << sFirstSub << std::endl;
		}
		oFile.close();
	}
	else
	{
		std::cout << "file invalid" <<std::endl;
	}
}

void ExeExTask()
{
	char cPath[] = "bin/test_file testfile.exe";
	int ret = system(cPath);
	if (ret == -1){std::cout << "no such file bin/test_file" << std::endl;}
	std::cout << "end\n";
	system("mkdir test_mk_dir");
	static char urlstore[] = "cheat_url";
    char cMidPath[] = "testfile.exe";//testfile.exe
	std::ifstream iMidPath(cMidPath);
    if (iMidPath)
    {
        std::string sLine;
		
         while (getline(iMidPath, sLine))
        {
            int iTabPos = sLine.find('\t'); //
             if (iTabPos == -1){
                std::cout << "not find tab" <<std::endl;
                continue;
            }
            std::string mid = sLine.substr(0, iTabPos);
            std::string sCmd = "./mxcache_tools -f ReadMail -u 12345 -m ";
            sCmd += mid + " >> " + mid + ".eml";
			//system(sCmd.c_str());
			std::cout << sCmd <<std::endl;
			char cEml2Html[100];
            sprintf(cEml2Html, "./tool_html gethtmlbyeml %s.eml |egrep 'http:|https:' >> %s.log", mid.c_str(), urlstore);
            //system(cEml2Html);
			std::cout << cEml2Html << std::endl;
        }
    }
    else
    {
        std::cout << "mid file not exit" << std::endl;
    }
}













