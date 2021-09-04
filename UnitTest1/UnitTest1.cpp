#include "pch.h"
#include "CppUnitTest.h"
# include <vector>
# include <string>
#include "../LR4/Source.h"
#include "../LR4/Source.cpp"
#include "iostream"
#include "fstream"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
	TEST_CLASS(UnitTest1)
	{
	public:
		//1 - нормальная работа
		//2 - пустой файл
		//3 - неоткрытый файл
		//4 - непустой вектор
		
		TEST_METHOD(InvalidFileName)
		{
			vector<string> test;
			string fileName = "123";
			//test.clear();
			string str = "rok";
			//TestAho(str, test, fileName);
			Assert::AreEqual(3, TestAho(str, test, fileName));
		}

		TEST_METHOD(NotEmptyVector)
		{
			vector<string> test;
			string name = "str.txt";
			test.push_back("asd");
			string str = "rok";
			Assert::AreEqual(4, TestAho(str, test, name));
		}

		TEST_METHOD(YEmptyFile)//последний
		{
			vector<string> test;
			string name = "str.txt";
			ofstream ofs;
			ofs.open(name, ios::out | ios::trunc);
			ofs.close();
			string str = "rok";
			Assert::AreEqual(2, TestAho(str, test, name));
		}

	};
}
