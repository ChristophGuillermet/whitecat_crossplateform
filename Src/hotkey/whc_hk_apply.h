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

* \file whc_hk_apply.h
* \brief {header file for hotkeys service  }
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*   Variables pour décrire les fonctions auxquelles seront associées les hotkeys
*
*
*
*/


#ifndef WHC_HK_APPLY_H
#define WHC_HK_APPLY_H

#include "whc_hk_input.h"

//Container C compatible
#include <string>
#include <vector>

class whc_hk_apply
{
	typedef void (*ptrMthd)(void);
	public:

		/** Default constructor */
		whc_hk_apply();
		whc_hk_apply(int id, std::string module, std::string description, ptrMthd processOnHotkey);
		/** Default destructor */
		virtual ~whc_hk_apply();

		int id() { return m_id; }
		void Setid(const int &val) { m_id = val; }

		std::string module() { return m_module; }
		void Setmodule(const std::string &val) { m_module = val; }

		std::string description() { return m_description; }
		void Setdescription(const std::string &val) { m_description = val; }

		ptrMthd processOnHotkey() { return m_processOnHotkey; }
		void SetprocessOnHotkey(const ptrMthd &val) { m_processOnHotkey = val; }

	protected:
	private:
		int m_id; //!<Identifiant unique de la fonctionnalité
		std::string m_module; //!< Lotissement des fonctionnalités
		std::string m_description; //!< Description de la fonctionnalité activée par le raccourci clavier
		ptrMthd m_processOnHotkey ; //!< Méthode à appeler pour exécuter la fonctionnalité
};

#endif // WHC_HK_APPLY_H
