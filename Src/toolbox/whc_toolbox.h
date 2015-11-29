#ifndef WHC_TOOLBOX_H
#define WHC_TOOLBOX_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <windows.h>

class whc_toolbox
{
	public:
		bool static fileexist(const std::string &fic_name);
		std::vector<std::string> static split_string(const std::string &text, char separator);
		int static string_to_int(const std::string &text);
		std::string static int_to_string(const int &number);
		std::string static bool_to_string(const bool &eval);
		std::string static executablePath();

		/** Default constructor */
		whc_toolbox();
		/** Default destructor */
		virtual ~whc_toolbox();
	protected:
	private:
};

#endif // WHC_TOOLBOX_H
