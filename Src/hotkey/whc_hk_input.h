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

* \file wh_hk_input.h
* \brief {header file for hotkeys service }
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*   Variables définissant les hotkeys
*
*
*
*/

#ifndef WHC_HOTKEY_SIGNATURE_H
#define WHC_HOTKEY_SIGNATURE_H

//Allegro
#include <allegro/keyboard.h>
//Container C compatible
#include <string>
#include <vector>

class whc_hk_input
{
	public:

		whc_hk_input static c_scan(int tmp_scancode); // fonction création objet sur saisie utilisateur

		/** Default constructor */
		whc_hk_input();
		whc_hk_input(bool tmp_shift, bool tmp_ctrl, bool tmp_alt, int tmp_scancode);

		/** Default destructor */
		virtual ~whc_hk_input();
		/** Access shift
		 * \return The current value of shift
		 */
		bool shift() { return m_shift; }
		/** Set shift
		 * \param val New value to set
		 */
		void Setshift(const bool &val) { m_shift = val; }
		/** Access ctrl
		 * \return The current value of ctrl
		 */
		bool ctrl() { return m_ctrl; }
		/** Set ctrl
		 * \param val New value to set
		 */
		void Setctrl(const bool &val) { m_ctrl = val; }
		/** Access alt
		 * \return The current value of alt
		 */
		bool alt() { return m_alt; }
		/** Set alt
		 * \param val New value to set
		 */
		void Setalt(const bool &val) { m_alt = val; }
		/** Access scancode
		 * \return The current value of scancode
		 */
		int scancode() { return m_scancode; }
		/** Set scancode
		 * \param val New value to set
		 */
		void Setscancode(const int &val) { m_scancode = val; }
		/** Access wording
		 * \return The current value of wording
		 */
		std::string wording() { return m_wording; }
		/** Set wording
		 * \param val New value to set
		 */
		void Setwording(const std::string &val) { m_wording = val; }
	protected:
	private:
		bool m_shift; //!< Member variable "shift"
		bool m_ctrl; //!< Member variable "ctrl"
		bool m_alt; //!< Member variable "alt"
		int  m_scancode; //!< Member variable "scancode"
		std::string m_wording; //!< Member variable "wording"
};

#endif // WHC_HOTKEY_SIGNATURE_H
