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
