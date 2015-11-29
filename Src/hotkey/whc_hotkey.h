#ifndef WHC_HOTKEY_H
#define WHC_HOTKEY_H

//Allegro
#include <allegro/keyboard.h>
//Container C compatible
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//
#include <whc_hk_input.h>
#include <whc_hk_apply.h>

#include <whc_toolbox.h>

class whc_hotkey
{
	typedef void (*ptrMthd)(void);
	public:
		int static c_nbr;
		std::vector<whc_hotkey> static c_list;

		/** Default constructor */
		whc_hotkey();
		whc_hotkey(whc_hk_apply fonctionality, whc_hk_input signature);
		/** Default destructor */
		virtual ~whc_hotkey();

		whc_hk_apply fonctionality() { return m_fonctionality; }
		void Setfonctionality(const whc_hk_apply &val) { m_fonctionality = val; }

		whc_hk_input signature() { return m_signature; }
		void Setsignature(const whc_hk_input &val) { m_signature = val; }

		whc_hk_input user_signature() { return m_user_signature; }
		void Setuser_signature(const whc_hk_input &val) { m_user_signature = val; }

		int collect();
		void link_keyFocusIndicator(bool &val){m_inputIsOn = &val ; }
		int shortcutprocess(int isreadkey);
		whc_hk_apply search_fct(whc_hk_input signature);
		void init(std::string fic_name);
		void load(std::string fic_name);
		void save(std::string fic_name);
		void connect_fct(int fctid, ptrMthd fctptr);
		void link_fct_hk(int fctid, whc_hk_input signature);
		void replace_link_fct_hk();
		void user_hk_init();

	protected:
	private:
		whc_hk_apply m_fonctionality ;
		whc_hk_input m_signature ;

		bool* m_inputIsOn;

		int     m_user_selectfunc ; // fonctionality->id()
		whc_hk_input     m_user_signature ;
		whc_hk_apply m_user_conflictfunc ; // in case of conflict for a signature
		bool    m_user_askconfirm ; // on demande confirmation, si signature déjà attribuée à une autre fonction
		bool    m_user_didanswer ; // si la demande de confirmation a été répondue
		bool    m_user_answer ; // la réponse est oui/non

};

#endif // WHC_HOTKEY_H
