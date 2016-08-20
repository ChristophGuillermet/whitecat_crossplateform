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

* \file whc_hk_connector.cpp
* \brief {hotkeys service - object - link apply & input to manage hotkey service}
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Objet décrivant un raccourcis (sa signature et sa représentation textuelle)
*
*/

#include "whc_hk_input.h"

whc_hk_input::whc_hk_input()
{

    m_scancode = -1 ;
    m_shift = false ;
    m_ctrl  = false ;
    m_alt   = false ;

    m_wording = "--unset--" ;
}

whc_hk_input::whc_hk_input( bool tmp_shift,
											bool tmp_ctrl,
											bool tmp_alt,
											int tmp_scancode)
{
    //ctor
    m_scancode = tmp_scancode ;

    m_shift    = tmp_shift ;
    m_ctrl     = tmp_ctrl ;
    m_alt      = tmp_alt ;

	if (m_scancode>-1)
	{
		if (m_shift) m_wording  = "[Shift]+";
		if (m_ctrl)  m_wording += "[Ctrl]+";
		if (m_alt)   m_wording += "[Alt]+";

		char const *keyname = scancode_to_name(m_scancode);

		m_wording += "[";
		m_wording += std::string(keyname);
		m_wording += "]";
	}
	else
	{
		m_wording = "--none--";
	}
}

whc_hk_input::~whc_hk_input()
{
	//dtor
//	if (whc_hk_input::c_list.size()>1)
//	{
//		whc_hk_input* tmp_it;
//		std::vector<whc_hk_input>::iterator it;
//		for (unsigned i=0; i<whc_hk_input::c_list.size(); i++)
//		{
//			if (whc_hk_input::c_list.at(i).wording() == this->wording())
//			{
//				whc_hk_input::c_list.erase(whc_hk_input::c_list.begin()+i);
//				i = whc_hk_input::c_list.size()+1;
//			}
//		}
//
//	}
//	else
//	{
//		whc_hk_input::c_list.clear();
//	}
}

whc_hk_input whc_hk_input::c_scan(int tmp_scancode)
{
    //ctor
    bool tmp_shift = (key[KEY_LSHIFT]   || key[KEY_RSHIFT]);
    bool tmp_ctrl  = (key[KEY_LCONTROL] || key[KEY_RCONTROL]);
    bool tmp_alt   = (key[KEY_ALT]      || key[KEY_ALTGR]);

    return whc_hk_input(tmp_shift, tmp_ctrl, tmp_alt, tmp_scancode) ;
}
