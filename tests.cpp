#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <dirent.h>
#include <sys/sysinfo.h>
#include <fstream>
#include <stdio.h>

class TestCaseOne
{
    public:
        int tc_id;
        std::string name;
        int execute()
        {
            if (prep() == true)
            {
                run();
                return clean();
            }
            else
            {
                return 1;
            }
        };
    private:
        bool prep()
        {
            const std::time_t result = std::time(nullptr);
            char *ctime(nullptr);
            std::cout << result <<std::endl;
            return !(result & 1);
        };

        void run()
        {
            const char* homedir = getenv("HOME");
            DIR *dir; 
            struct dirent *diread;
            std::vector<char *> files;

            if ((dir = opendir(homedir)) != nullptr) 
            {
                while ((diread = readdir(dir)) != nullptr) 
                {
                    files.push_back(diread->d_name);
                }
                closedir (dir);
            } else 
            {
                perror ("opendir");
            }

            for (auto file : files) std::cout << file << std::endl;

        };

        int clean()
        {
            return 0;
        };
};

class TestCaseTwo
{
    public:
        int tc_id;
        std::string name;
        int execute()
        {
            if (prep() == true)
            {
                run();
                return clean();
            }
            else
            {
                return 1;
            }
        };
    private:
        bool prep()
        {
            struct sysinfo SI;
            sysinfo(&SI);
            if (SI.totalram/(1024*1024) >= 1024)
                return true;
            else
                return false;
        };

        void run()
        {
            char* buffer = new char[1024*1024];
            
            std::ifstream src( "/dev/urandom", std::ios::binary );
            std::ofstream dst( "test", std::ios::binary );

            src.read(buffer, 1024*1024);
            dst.write(buffer, 1024*1024);
            
            delete[] buffer;

            std::cout << "ready" <<std::endl;
        };

        int clean()
        {
            if (remove("test") != 0 )
                std::cout << "error" <<std::endl;
            else
                std::cout << "file deleted" << std::endl;
            return 0;
        };
};

int main()
{
    TestCaseOne case1;
    case1.tc_id = 1;
    case1.name = "q";
    int res = case1.execute();
    return 0;
}