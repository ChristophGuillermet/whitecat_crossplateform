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

#ifndef WHC_TOOLBOX_H
#define WHC_TOOLBOX_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <windows.h>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

class whc_toolbox
{
	public:
		bool static fileexist(const std::string &fic_name);
		std::vector<std::string> static split_string(const std::string &text, char separator);
		int static string_to_int(const std::string &text);
		std::string static int_to_string(const int &number);
		std::string static bool_to_string(const bool &eval);
		std::string static executablePath();
		void copy_until_eol(char* target, unsigned int target_size, char* line);
		std::string static &ltrim(std::string &s);
		std::string static &rtrim(std::string &s);
		std::string static &trim(std::string &s);

		/** Default constructor */
		whc_toolbox();
		/** Default destructor */
		virtual ~whc_toolbox();
	protected:
	private:
};

#endif // WHC_TOOLBOX_H
