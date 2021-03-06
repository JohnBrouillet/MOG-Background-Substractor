#include "utils.h"

std::vector<std::string> open_files(std::string path) 
{
    struct dirent **namelist;
    int n,i;
    std::vector<std::string> files;
    n = scandir(path.c_str(), &namelist, 0, versionsort);
    if (n < 0)
        perror("scandir");
    else
    {
        for(i =0 ; i < n; ++i)
        {
        	if(namelist[i]->d_name == std::string(".") || namelist[i]->d_name == std::string("..") || namelist[i]->d_name == std::string(".directory"))
    			continue;
            files.push_back(namelist[i]->d_name);
            free(namelist[i]);
        }
        free(namelist);
    }
    
    return files;
}

bool checkMaskDirExist(std::string directory)
{
	struct stat info;
	std::string dir = directory + "mask";
	if( stat( dir.c_str(), &info ) != 0 )
	{
		std::cout << "Mask directory doesn't exist" << std::endl;
		std::cout << "Creation of mask in " + directory << std::endl;
		
		mkdir(dir.c_str(), 0700);
        return 0;
	}
	else
        return 1;
}