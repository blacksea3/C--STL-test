#include "../public/public.hpp"
//#include "mLibhash.hpp"
#include "mLibunordered_map.hpp"

namespace mLib
{
	void mLibunorderedmapClassTest()
	{
		cout << mLib::mhash<int>(1, 10) << endl;
		cout << mLib::mhash<unsigned int>(1, 10) << endl;
		cout << mLib::mhash<long>(1, 10) << endl;
		cout << mLib::mhash<unsigned long>(1, 10) << endl;
		cout << mLib::mhash<long long>(1, 10) << endl;
		cout << mLib::mhash<unsigned long long>(1, 10) << endl;
		cout << mLib::mhash<short>(1, 10) << endl;
		cout << mLib::mhash<unsigned short>(1, 10) << endl;
		cout << mLib::mhash<std::string>("ssss", 10) << endl;
		cout << mLib::mhash<const std::string>((std::string)"ssss", 10) << endl;
		cout << mLib::mhash<std::pair<int, int>>(std::pair<int, int>{1,1}, 10) << endl;
	}
}
