#include "../String/Trie.hpp"
#include "TestStringData.hpp"

/*
 * 生成随机字符串, 全是小写字母
 * 输入: paraStringLengthStart: paraStringLengthEnd 代表参数字符串长度, 范围是[..Start, ..End], 内部强制限制: 后者大于等于前者
 * 返回字符串
 */
std::string GenRandString(int paraStringLengthStart, int paraStringLengthEnd)
{
	int stringSize = rand() % (paraStringLengthEnd - paraStringLengthStart + 1) + paraStringLengthStart;
	std::string res;
	for (int i = 0; i < stringSize; ++i)
	{
		char ch = rand() % 26 + 'a';
		res.push_back(ch);
	}
	return res;
}

/*
 * 生成字典树测试数据
 * 目标: 一个文本文件: 每一行操作符(数字) 空格 参数(字符串)组成
 * 操作: 1: 插入, 参数字符串, 2: 查找前缀, 参数字符串, 3:查找是否存在, 参数字符串, 4:删除, 参数字符串
 * 后三个均有(大约)50概率选择已插入的字符串, 前缀若选择已插入的字符串, 则选择一个然后随机一下位置从而获得它的前缀
 *
 * 输入: opStart:操作数字开始, opEnd操作数字结束,
 * paraStringLengthStart: paraStringLengthEnd 代表参数字符串长度, 范围是[..Start, ..End], 内部强制限制: 后者大于等于前者
 *  前者>=1, 后者<=10
 * nums操作数量(不要太大, 最多10000, 最小1), filename:文件名
 */
void GenTrieTestData(int opStart, int opEnd, int paraStringLengthStart, int paraStringLengthEnd, int nums, std::string filename)
{
	assert(paraStringLengthStart >= 1 && paraStringLengthEnd <= 10 && paraStringLengthEnd >= paraStringLengthStart);
	assert(nums <= 10000 && nums >= 1);
	std::fstream fout(filename, std::ios::out);

	std::vector<std::string> pre;

	for (int i = 0; i < nums; ++i)
	{
		int opR = rand() % (opEnd - opStart + 1) + opStart;
		switch (opR)
		{
		case 1:
		{
			std::string paraR = GenRandString(paraStringLengthStart, paraStringLengthEnd);
			fout << opR << " " << paraR << endl;
			pre.emplace_back(paraR);
			break;
		}
		case 2:
		{
			int isPreOccur = rand() % 2;
			if (isPreOccur == 0 || pre.empty())
			{
				std::string paraR = GenRandString(paraStringLengthStart, paraStringLengthEnd);
				fout << opR << " " << paraR << endl;
			}
			else
			{
				int selRand = rand() % (int)pre.size();
				std::string selStr = pre[selRand];
				int lengthRand = rand() % (int)selStr.size() + 1;
				fout << opR << " " << selStr.substr(0, lengthRand) << endl;
			}
			break;
		}
		case 3:
		{
			int isPreOccur = rand() % 2;
			if (isPreOccur == 0 || pre.empty())
			{
				std::string paraR = GenRandString(paraStringLengthStart, paraStringLengthEnd);
				fout << opR << " " << paraR << endl;
			}
			else
			{
				int selRand = rand() % (int)pre.size();
				std::string selStr = pre[selRand];
				fout << opR << " " << selStr << endl;
			}
			break;
		}
		case 4:
		{
			int isPreOccur = rand() % 2;
			if (isPreOccur == 0 || pre.empty())
			{
				std::string paraR = GenRandString(paraStringLengthStart, paraStringLengthEnd);
				fout << opR << " " << paraR << endl;
			}
			else
			{
				int selRand = rand() % (int)pre.size();
				std::string selStr = pre[selRand];
				fout << opR << " " << selStr << endl;
			}
			break;
		}
		default:
			break;
		}
	}
	fout.close();
}

/*
 * 生成字典树输出
 * 用暴力算法, 插入的字符串全部放到unordered_set中
 */
void GenTrieOutputData(std::string infilename, std::string outfilename)
{
	fstream fin;
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

	std::unordered_set<std::string> uss;
	int op;
	std::string para;
	while (fin >> op >> para)
	{
		switch (op)
		{
		case 1:
		{
			if (uss.find(para) == uss.end()) uss.insert(para);
			fout << -1 << endl;
			break;
		}
		case 2:
		{
			bool isFindPre = false;
			for (auto& iteruss : uss)
			{
				int iIndex = 0;
				int iterSize = iteruss.size();
				int pSize = para.size();
				if (iteruss.size() < para.size()) continue;
				else
				{
					while (iIndex < iterSize && iIndex < pSize
						&& iteruss[iIndex] == para[iIndex])
					{
						iIndex++;
					}
					if (iIndex == pSize)
					{
						isFindPre = true;
						break;
					}
				}
			}
			if (isFindPre) fout << 1 << endl;
			else fout << 0 << endl;
			break;
		}
		case 3:
		{
			if (uss.find(para) == uss.end())
			{
				fout << 0 << endl;
			}
			else
			{
				fout << 1 << endl;
			}
			break;
		}
		case 4:
		{
			if (uss.find(para) == uss.end())
			{
				fout << 0 << endl;
			}
			else
			{
				uss.erase(para);
				fout << 1 << endl;
			}
			break;
		}
		default:
			break;
		}
	}
	fin.close();
	fout.close();
}

void GenTrieTestDataInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\TrieTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		GenTrieTestData(1, 4, 1, 10, 3 * (int)pow(2, i), fileName);
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		GenTrieOutputData(fileName, outName);
	}
}

/*
 * 测试字典树输出
 */
void TrieClassTest(std::string infilename, std::string outfilename)
{
	fstream finin;
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

	Trie t;
	int op;
	std::string para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		if (count == 6)
			int i = 1;
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			t.insert(para);
			assert(rightRes == -1);
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = t.isPrefix(para);
			assert(rightRes == testRes);
			break;
		}
		case 3:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = t.isOccur(para);
			assert(rightRes == testRes);
			break;
		}
		case 4:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = t.remove(para);
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

void TrieClassTestInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\TrieTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		TrieClassTest(fileName, outName);
		std::cout << "Trie Class insert/remove/isOccur/isPrefix passed test case" << i << " !!!" << endl;
	}
}
