#include "whc_toolbox.h"

whc_toolbox::whc_toolbox()
{
    //ctor
}

whc_toolbox::~whc_toolbox()
{
    //dtor
}

bool whc_toolbox::fileexist(const std::string &fic_name)
{
    return std::ifstream(fic_name.c_str()).good() ;
}

std::vector<std::string> whc_toolbox::split_string(const std::string &text, char separator)
{
    std::vector<std::string> tokens ;
    int start = 0, end = 0 ;
    while ((end = text.find(separator, start)) != std::string::npos) // à savoir : std::string::npos = end of the string
    {
        tokens.push_back(text.substr(start, end - start)) ;
        start = end + 1 ;
    }
    tokens.push_back(text.substr(start)) ;
    return tokens ;
}

int whc_toolbox::string_to_int(const std::string &text)
{
    const char *tmp  = text.c_str() ;
    return atoi(tmp) ;
}

std::string whc_toolbox::int_to_string(const int &number)
{
    std::stringstream ss ;
    ss << number;
    return  ss.str();
}

std::string whc_toolbox::bool_to_string(const bool &eval)
{
    if (eval)
    {
        return  "1";
    }
    else return "0";
}

std::string whc_toolbox::executablePath()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL,buffer,sizeof(buffer));
	std::string path = buffer;
	int i = path.size();
	while (path[i]!='\\')
	{
		i--;
	}
	path.resize(i);
	return  path;
}

void whc_toolbox::copy_until_eol(char* final_target, unsigned int max_size, char* line)
{
    std::string wrk_target(line);
    int copy_index = wrk_target.size();
    while (wrk_target[copy_index]!='\n')
    {
        copy_index--;
    }
    if (copy_index>max_size)
    {
        copy_index=max_size;
    }
    wrk_target.resize(copy_index);
    final_target[wrk_target.size()]=0;
    memcpy(final_target,wrk_target.c_str(),wrk_target.size());
}