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

* \file whc_hk_apply.cpp
* \brief {hotkeys service - object - function to apply}
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {20/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Objet décrivant la fonction interne à déclencher
*
*/

#include "whc_hk_apply.h"

whc_hk_apply::whc_hk_apply()
{
	//ctor
	m_module          = " ";
	m_id              = -1 ;
	m_description     = " none " ;
	m_processOnHotkey = nullptr ;

}
whc_hk_apply::whc_hk_apply(int id, std::string module, std::string description, ptrMthd processOnHotkey)
{
	//ctor
	m_module          = module ;
	m_id              = id ;
	m_description     = description ;
	m_processOnHotkey = processOnHotkey ;
}

whc_hk_apply::~whc_hk_apply()
{
	//dtor
}
