#ifndef WHC_HOTKEY_FONCTIONALITY_H
#define WHC_HOTKEY_FONCTIONALITY_H

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

#endif // WHC_HOTKEY_FONCTIONALITY_H
