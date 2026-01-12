#pragma once
#include <iostream>
#include "../MoneyUnitTest/pch.h"


namespace vsite {
	namespace oop {
		namespace v7
		{

			class money {
				long long eur;
				long long ct;

				void normalize();
			public:
				money(long long eur = 0, long long ct = 0);

				money& operator+=(const money& other);
				money& operator-=(const money& other);

				friend std::ostream& operator<<(std::ostream& os, const money& m);
				friend std::istream& operator>>(std::istream& is, money& m);
			};

		}
	}
	}