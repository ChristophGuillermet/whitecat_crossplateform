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
