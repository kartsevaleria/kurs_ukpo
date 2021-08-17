#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include <vector>
#include "../LR4/Source.h"
#include "../LR4/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		string name = "C:\\Users\\user\\Desktop\\Учеба\\3 курс\\Управление качеством ПО\\ЛР2\\LR4\\LR4\\str.txt";

		TEST_METHOD(NotIncludingOtherString)
		{
			
			string str2 = "rok";
			vector<string> test;
			TestAho(str2, test, name);
			Assert::AreEqual(str2, test.at(0));
		}

		TEST_METHOD(NotExistsString)
		{
			string str2 = " ";
			vector<string> test;
			TestAho(str2, test, name);
			Assert::AreEqual(true, test.empty());
		}

		TEST_METHOD(IncludingOtherString)
		{
			WriteInFile();
			string str = "strok";
			string str2 = "rok";
			vector<string> test;
			TestAho(str, test, name);
			Assert::AreEqual(str, test[0]);
			Assert::AreEqual(str2, test[1]);
		}

	};
}
