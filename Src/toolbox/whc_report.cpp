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
* \brief {general use debug function for developpers}
* \author Rui Serge Azevedo Brooks
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - general use - toolboox

*
*	Fonctions génériques utiles pour debugguer
*
*/

#include "whc_report.h"

unsigned short int whc_report::c_objCount = 0 ;
std::list<const whc_report*> whc_report::c_reportList;

whc_report::whc_report() : m_alarm(false),m_objId(++c_objCount),m_msg("")
{
	//ctor
}

whc_report::whc_report(std::string message)
{
	m_alarm = false;
	m_objId = ++c_objCount;
	m_msg   = message;
	c_reportList.push_back(this); //
}

whc_report::whc_report(bool alarme, std::string message)
{
	m_alarm = alarme;
	m_objId = ++c_objCount;
	m_msg   = message;
	c_reportList.push_back(this); //
}

whc_report::~whc_report()
{
	//dtor
}
