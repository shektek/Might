#ifndef TOOLS_H
#define TOOLS_H

#include <string>

class Tools
{
	private:
		Tools() {}

	public:

		Tools(Tools const&) = delete;
		void operator =(Tools const&) = delete;

		std::string DataDirectory;

		std::string ParseResourceString(std::string resourceString)
		{
			//this will probably grow as requirements change
			std::string parsed = resourceString;

			if (parsed.substr(0, 6) == "res://")
			{
				parsed = DataDirectory + parsed.substr(6, parsed.size() - 6);
			}

			return parsed;
		}

		static Tools& GetInstance()
		{
			static Tools instance;
			return instance;
		}
};

#endif
