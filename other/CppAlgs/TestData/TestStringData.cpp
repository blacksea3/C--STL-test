#include "../String/Trie.hpp"
#include "TestStringData.hpp"

/*
 * ��������ַ���, ȫ��Сд��ĸ
 * ����: paraStringLengthStart: paraStringLengthEnd ��������ַ�������, ��Χ��[..Start, ..End], �ڲ�ǿ������: ���ߴ��ڵ���ǰ��
 * �����ַ���
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
 * �����ֵ�����������
 * Ŀ��: һ���ı��ļ�: ÿһ�в�����(����) �ո� ����(�ַ���)���
 * ����: 1: ����, �����ַ���, 2: ����ǰ׺, �����ַ���, 3:�����Ƿ����, �����ַ���, 4:ɾ��, �����ַ���
 * ����������(��Լ)50����ѡ���Ѳ�����ַ���, ǰ׺��ѡ���Ѳ�����ַ���, ��ѡ��һ��Ȼ�����һ��λ�ôӶ��������ǰ׺
 *
 * ����: opStart:�������ֿ�ʼ, opEnd�������ֽ���,
 * paraStringLengthStart: paraStringLengthEnd ��������ַ�������, ��Χ��[..Start, ..End], �ڲ�ǿ������: ���ߴ��ڵ���ǰ��
 *  ǰ��>=1, ����<=10
 * nums��������(��Ҫ̫��, ���10000, ��С1), filename:�ļ���
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
 * �����ֵ������
 * �ñ����㷨, ������ַ���ȫ���ŵ�unordered_set��
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
 * �����ֵ������
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
