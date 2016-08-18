#ifndef WHC_REPORT_H
#define WHC_REPORT_H


#include <list>
#include <string>


class whc_report
{
	public:
		static unsigned short int c_objCount;
		static std::list<const whc_report*> c_reportList;

		/** Default constructor */
		whc_report();
		whc_report(std::string);
		whc_report(bool,std::string);
		/** Default destructor */
		virtual ~whc_report();
		/** Access m_alarm
		 * \return The current value of m_alarm
		 */
		bool alarm() { return m_alarm; }
		/** Set m_alarm
		 * \param val New value to set
		 */
		void alarm(bool val) { m_alarm = val; }
		/** Access m_objId
		 * \return The current value of m_objId
		 */
		unsigned short int id() {return m_objId;}
		/** Set m_objId
		 * \param val New value to set
		 */
		void id(unsigned short int val) {m_objId = val;}
		/** Access m_msg
		 * \return The current value of m_msg
		 */
		std::string msg() { return m_msg; }
		/** Set m_msg
		 * \param val New value to set
		 */
		void msg(std::string val) { m_msg = val; }
	protected:
	private:
		bool m_alarm; //!< Member variable "m_alarm"
		unsigned short int m_objId; //!< Member variable "m_objId"
		std::string m_msg; //!< Member variable "m_msg"
};

#endif // WHC_REPORT_H
