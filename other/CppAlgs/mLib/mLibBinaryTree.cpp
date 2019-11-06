#include "mLibBinaryTree.hpp"

namespace mLib
{
	void mLibBinaryTreeClassTest()
	{
		mbinary_searchtree<int> mbs;
		cout << mbs.remove(3) << endl;
		mbs.inorder();
		cout << endl;
		cout << mbs.insert(3) << endl;
		cout << mbs.insert(2) << endl;
		cout << mbs.insert(1) << endl;
		cout << mbs.insert(4) << endl;
		cout << mbs.insert(1) << endl;
		cout << mbs.insert(3) << endl;
		cout << mbs.insert(1) << endl;
		mbs.inorder();
		cout << endl;

		cout << mbs.find(3) << endl;
		cout << mbs.find(5) << endl;
		cout << mbs.find(1) << endl;

		mLib::mvector<int> res = mbs.RangeSearch(2, 4);
		for (size_t i = 0; i < res.getSize(); ++i) cout << res[i] << " ";
		cout << endl;

		cout << mbs.remove(3) << endl;
		mbs.inorder();
		cout << endl;

		cout << mbs.find(3) << endl;
	}
}
