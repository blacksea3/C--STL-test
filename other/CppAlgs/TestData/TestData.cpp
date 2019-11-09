#include "../public/public.hpp"
#include "../mLib/mLibBinaryTree.hpp"

/*
 * ���ɲ������ݷ����ı��ļ�
 * Ŀ����: ÿ���������ֵ�һ���ǲ���, �ڶ����ǲ���, ����int
 * ����: opStart:�������ֿ�ʼ, opEnd�������ֽ���,
 * paraStart������ʼ, paraEnd��������, nums��������
 * filename:�ļ���
 * 
 * ע��: numsӦ��С�ڵ��ڲ�����������������һ��
 * 
 * ��Զ��������, Ŀ����: ����:1���� ������ֵ, 2ɾ�� ������ֵ(��һ���������ɾ���Ѿ����ڵ�ֵ), 
 *    3��ӡ, ������0(����������), 4��֤�������Ƿ�Ϸ�, ������0(����������)
 * 
 */
void genTestDataBinaryTree(int opStart, int opEnd, int paraStart, int paraEnd, int nums, std::string filename)
{
	assert(nums <= (paraEnd - paraStart + 1) / 2);

	fstream fout(filename, std::ios::out);

	vector<int> pre;

	for (int i = 0; i < nums; ++i)
	{
		int opR = rand() % (opEnd - opStart + 1) + opStart;
		switch (opR)
		{
		case 1:
		{
			int paraR = rand() % (paraEnd - paraStart + 1) + paraStart;
			fout << 1 << " " << paraR << endl;
			pre.emplace_back(paraR);
			break;
		}
		case 2:
		{
			int isDelOccur = rand() % 2;
			if (isDelOccur == 0 || pre.empty())
			{
				while (true)
				{
					int paraR = rand() % (paraEnd - paraStart + 1) + paraStart;
					if (find(pre.begin(), pre.end(), paraR) == pre.end())
					{
						fout << 2 << " " << paraR << endl;
						break;
					}
				}
			}
			else
			{
				while (true)
				{
					int paraR = rand() % (paraEnd - paraStart + 1) + paraStart;
					vector<int>::iterator iter = find(pre.begin(), pre.end(), paraR);
					if (iter != pre.end())
					{
						fout << 2 << " " << paraR << endl;
						pre.erase(iter);
						break;
					}
				}
			}
			break;
		}
		case 3:
		{
			fout << 3 << " " << 0 << endl;
			break;
		}
		case 4:
		{
			fout << 4 << " " << 0 << endl;
		}
		default:
			break;
		}
	}
	fout.close();
}

/*
 * ���ɲ������ݽ�������ı��ļ�
 * �ÿ⺯����set����
 * ����: (in/out)filename:�ļ���
 */
void genOutputDataBinaryTree(std::string infilename, std::string outfilename)
{
	fstream fin;  //����ȫ��std:cin
	fin.open(infilename, std::ios::in);
	if (!fin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream fout;
	fout.open(outfilename, std::ios::out);
	if (!fout.is_open())
	{
		fin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	set<int> s;
	int op, para;
	while (fin >> op >> para)
	{
		switch (op)
		{
		case 1:
		{
			if (s.find(para) == s.end())
			{
				fout << 1 << endl;
				s.insert(para);
			}
			else
			{
				fout << 0 << endl;
			}
			break;
		}
		case 2:
		{
			if (s.find(para) == s.end())
			{
				fout << 0 << endl;
			}
			else
			{
				s.erase(para);
				fout << 1 << endl;
			}
			break;
		}
		case 3:
		{
			fout << s.size() << " ";
			for (auto& iters : s) fout << iters << " ";
			fout << endl;
			break;
		}
		case 4:
		{
			fout << 1 << endl;
		}
		default:
			break;
		}
	}
	fin.close();
	fout.close();
}

/*
 * �����Զ������������
 * ���ɲ������ݷ����ı��ļ�, �ⲿ�ӿ�
 */
void genTestDataBinarySearchTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		genTestDataBinaryTree(1, 3, 0, 10000, 3 * (int)pow(2, i), fileName);
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		genOutputDataBinaryTree(fileName, outName);
	}
}

/*
 * �����Զ���AVL��
 * ���ɲ������ݷ����ı��ļ�, �ⲿ�ӿ�
 */
void genTestDataAVLTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		genTestDataBinaryTree(1, 4, 0, 10000, 3 * (int)pow(2, i), fileName);
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		genOutputDataBinaryTree(fileName, outName);
	}
}

/*
 * �����Զ������������
 * ����: (in/out)filename:�ļ���
 */
void testBinarySearchTree(std::string infilename, std::string outfilename)
{
	fstream finin;  //����ȫ��std:cin
	finin.open(infilename, std::ios::in);
	if (!finin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream foutin;
	foutin.open(outfilename, std::ios::in);
	if (!foutin.is_open())
	{
		finin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	mLib::mbinary_searchtree<int> mbs;
	int op, para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		int testRes = mbs.checkIfTreeValid();
		assert((1 == testRes));
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mbs.insert(para);
			assert(rightRes == testRes);
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mbs.remove(para);
			assert(rightRes == testRes);
			break;
		}
		case 3:
		{
			int rsize;
			foutin >> rsize;
			vector<int> rightRes(rsize);
			for (int i = 0; i < rsize; ++i) foutin >> rightRes[i];
			vector<int> testRes = mbs.inorder();
			assert(rightRes == testRes);
			break;
		}
		default:
			break;
		}
	}

	finin.close();
	foutin.close();
}

/*
 * �����Զ�������������ӿ�
 */
void TestBinarySearchTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		testBinarySearchTree(fileName, outName);
		std::cout << "mbinary_searchtreeClass insert/remove/inorder test case" << i <<  " OK!" << endl;
	}
}

/*
 * �����Զ���AVL��
 * ����: (in/out)filename:�ļ���
 */
void testAVLTree(std::string infilename, std::string outfilename)
{
	fstream finin;  //����ȫ��std:cin
	finin.open(infilename, std::ios::in);
	if (!finin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream foutin;
	foutin.open(outfilename, std::ios::in);
	if (!foutin.is_open())
	{
		finin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	mLib::mAVLtree<int> mAVL;
	int op, para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		int testRes = mAVL.checkIfAVLValid();
		assert((1 == testRes));
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mAVL.insert(para);
			assert(rightRes == testRes);
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mAVL.remove(para);
			assert(rightRes == testRes);
			break;
		}
		case 3:
		{
			int rsize;
			foutin >> rsize;
			vector<int> rightRes(rsize);
			for (int i = 0; i < rsize; ++i) foutin >> rightRes[i];
			vector<int> testRes = mAVL.inorder();
			assert(rightRes == testRes);
			break;
		}
		case 4:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mAVL.checkIfAVLValid();
			assert((rightRes == 1) && (rightRes == testRes));
		}
		default:
			break;
		}
	}

	finin.close();
	foutin.close();
}

/*
 * �����Զ���AVL���ӿ�
 */
void TestAVLTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		testAVLTree(fileName, outName);
		std::cout << "mAVLtreeClass insert/remove/inorder test case" << i << " OK!" << endl;
	}
}
