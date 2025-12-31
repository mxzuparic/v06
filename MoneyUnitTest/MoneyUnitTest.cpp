#include "pch.h"
#include "CppUnitTest.h"
#include "../app/money.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vsite::oop::v7;

namespace MoneyUnitTest
{
	TEST_CLASS(MoneyUnitTest)
	{
	public:
		
		TEST_METHOD(Constructor_Zero)
		{
			money m;
			std::ostringstream os;
			os << m;
			Assert::AreEqual(std::string("0 ct"), os.str());
		}

		TEST_METHOD(Constructor_EurOnly)
		{
			money m(5, 0);
			std::ostringstream os;
			os << m;
			Assert::AreEqual(std::string("5 eur"), os.str());
		}

		TEST_METHOD(Constructor_CtOnly)
		{
			money m(0, 75);
			std::ostringstream os;
			os << m;
			Assert::AreEqual(std::string("75 ct"), os.str());
		}

		TEST_METHOD(Constructor_Normalization_Over100Ct)
		{
			money m(2, 150);
			std::ostringstream os;
			os << m;
			Assert::AreEqual(std::string("3 eur, 50 ct"), os.str());
		}

		TEST_METHOD(Addition_Simple)
		{
			money a(3, 20);
			money b(2, 30);
			a += b;

			std::ostringstream os;
			os << a;
			Assert::AreEqual(std::string("5 eur, 50 ct"), os.str());
		}

		TEST_METHOD(Addition_CarryFromCents)
		{
			money a(1, 80);
			money b(0, 40);
			a += b;

			std::ostringstream os;
			os << a;
			Assert::AreEqual(std::string("2 eur, 20 ct"), os.str());
		}

		TEST_METHOD(Subtraction_Simple)
		{
			money a(10, 0);
			money b(3, 50);
			a -= b;

			std::ostringstream os;
			os << a;
			Assert::AreEqual(std::string("6 eur, 50 ct"), os.str());
		}

		TEST_METHOD(Subraction_BorrowFromEuro)
		{
			money a(5, 20);
			money b(2, 50);
			a -= b;

			std::ostringstream os;
			os << a;
			Assert::AreEqual(std::string("2 eur, 70 ct"), os.str());
		}

		TEST_METHOD(Subtraction_ToNegative)
		{
			money a(3, 0);
			money b(5, 50);
			a -= b;

			std::ostringstream os;
			os << a;
			Assert::AreEqual(std::string("-2 eur, 50 ct"), os.str());
		}

		TEST_METHOD(InputOperator_ReadMoney)
		{
			std::istringstream is("6 80");
			money m;
			is >> m;

			std::ostringstream os;
			os << m;
			Assert::AreEqual(std::string("6 eur, 80 ct"), os.str());
		}

		TEST_METHOD(InputOperator_WithZeroCents)
		{
			std::istringstream is("4 0");
			money m;
			is >> m;

			std::ostringstream os;
			os << m;
			Assert::AreEqual(std::string("4 eur"), os.str());
		}

		TEST_METHOD(FullProgramScenario)
		{
			money total(0);

			total += money(6, 80);
			total += money(7, 20);
			total += money(12, 40);
			total -= money(5, 50);
			total += money(10, 15);

			std::ostringstream os;
			os << total;
			Assert::AreEqual(std::string("31 eur, 05 ct"), os.str());
		}

	};
}
