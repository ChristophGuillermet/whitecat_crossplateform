/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2016  Christoph Guillermet
       WWWWWWWWWWWWWWW           |
     WWWWWWWWWWWWWWWWWWW         | This file is part of White Cat.
    WWWWWWWWWWWWWWWWWCWWWW       |
   WWWWWWWWWWWWWWWWW tWWWWW      | White Cat is free software: you can redistribute it and/or modify
  WWWW   WWWWWWWWWW  tWWWWWW     | it under the terms of the GNU General Public License as published by
 WWWWWt              tWWWWWWa    | the Free Software Foundation, either version 2 of the License, or
 WWWWWW               WWWWWWW    | (at your option) any later version.
WWWWWWWW              WWWWWWW    |
WWWWWWWW               WWWWWWW   | White Cat is distributed in the hope that it will be useful,
WWWWWWW               WWWWWWWW   | but WITHOUT ANY WARRANTY; without even the implied warranty of
WWWWWWW      CWWW    W WWWWWWW   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
WWWWWWW            aW  WWWWWWW   | GNU General Public License for more details.
WWWWWWWW           C  WWWWWWWW   |
 WWWWWWWW            CWWWWWWW    | You should have received a copy of the GNU General Public License
 WWWWWWWWW          WWWWWWWWW    | along with White Cat.  If not, see <http://www.gnu.org/licenses/>.
  WWWWWWWWWWC    CWWWWWWWWWW     |
   WWWWWWWWWWWWWWWWWWWWWWWW      |
    WWWWWWWWWWWWWWWWWWWWWW       |
      WWWWWWWWWWWWWWWWWWa        |
        WWWWWWWWWWWWWWW          |
           WWWWWWWWt             |
                                 |
---------------------------------------------------------------------------------------------------------------*/

/**

* \file hotkey_config_tab.cpp
* \brief {general use function}
* \author Rui Serge Azevedo Brooks
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - genral use - toolboox

*
*	Fonctions génériques utiles
*
*/

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


// trim from start
std::string &whc_toolbox::ltrim(std::string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(),
                               not1(std::ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
std::string &whc_toolbox::rtrim(std::string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(),
                    not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both sides
std::string &whc_toolbox::trim(std::string &s)
{
    return ltrim(rtrim(s));
}
