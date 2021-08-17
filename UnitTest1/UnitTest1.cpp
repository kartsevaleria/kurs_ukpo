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
		TEST_METHOD(AWithSpace)
		{
			vector<string> test;
			string fileName = "C:\\Users\\user\\Desktop\\Учеба\\3 курс\\Управление качеством ПО\\ЛР2\\LR4\\LR4\\str.txt";
			//test.clear();
			string str = "test rok";
			string str1 = "test";
			string str2 = "rok";
			//TestAho(str, test, fileName);
			TestAho(str, test, fileName);
			Assert::AreEqual(str1, test[0]);
			Assert::AreEqual(str2, test[1]);

		}
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
			string name = "C:\\Users\\user\\Desktop\\Учеба\\3 курс\\Управление качеством ПО\\ЛР2\\LR4\\LR4\\str.txt";
			test.push_back("asd");
			string str = "rok";
			Assert::AreEqual(4, TestAho(str, test, name));
		}

		TEST_METHOD(YEmptyFile)//последний
		{
			vector<string> test;
			string name = "C:\\Users\\user\\Desktop\\Учеба\\3 курс\\Управление качеством ПО\\ЛР2\\LR2\\LR2\\str.txt";
			ofstream ofs;
			ofs.open(name, ios::out | ios::trunc);
			ofs.close();
			string str = "rok";
			Assert::AreEqual(2, TestAho(str, test, name));
		}

	};
}