#include "mLibDisjointSet.hpp"

namespace mLib
{
	void mLibDisjointSetClassTest()
	{
		mLib::mvector<std::string> m;
		m.push_back(std::string("a"));
		m.push_back(std::string("b"));
		m.push_back(std::string("c"));
		m.push_back(std::string("d"));
		m.push_back(std::string("e"));

		mLib::mDisjoint<std::string> mdj(m);

		cout << "raw:";
		cout << mdj.Find(std::string("a")) << " ";
		cout << mdj.Find(std::string("b")) << " ";
		cout << mdj.Find(std::string("c")) << " ";
		cout << mdj.Find(std::string("d")) << " ";
		cout << mdj.Find(std::string("e")) << endl;

		mdj.Union("a", "b");
		mdj.Union("d", "e");
		cout << "after union(a,b), union(d,e):";
		cout << mdj.Find(std::string("a")) << " ";
		cout << mdj.Find(std::string("b")) << " ";
		cout << mdj.Find(std::string("c")) << " ";
		cout << mdj.Find(std::string("d")) << " ";
		cout << mdj.Find(std::string("e")) << endl;

		mdj.Union("a", "e");
		cout << "after union(a,e):";
		cout << mdj.Find(std::string("a")) << " ";
		cout << mdj.Find(std::string("b")) << " ";
		cout << mdj.Find(std::string("c")) << " ";
		cout << mdj.Find(std::string("d")) << " ";
		cout << mdj.Find(std::string("e")) << endl;
	}
}


