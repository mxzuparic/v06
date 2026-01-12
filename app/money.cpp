#include "../MoneyUnitTest/pch.h"
#include "money.h"
#include <algorithm>

namespace vsite {
	namespace oop {
		namespace v7
		{
			money::money(long long eur, long long ct) : eur(eur), ct(ct) {
				normalize();
			}

			void money::normalize() {
				eur += ct / 100;
				ct %= 100;

				if (eur > 0 && ct < 0) {
					eur--;
					ct += 100;
				}

				if (eur < 0 && ct > 0) {
					eur++;
					ct -= 100;
				}
			}

			money& money::operator+=(const money& other) {
				eur += other.eur;
				ct += other.ct;
				normalize();
				return *this;
			}

			money& money::operator-=(const money& other) {
				eur -= other.eur;
				ct -= other.ct;
				normalize();
				return *this;
			}

			std::ostream& operator<<(std::ostream& os, const money& m) {
				if (m.eur == 0 && m.ct == 0) {
					os << "0 ct";
					return os;
				}

				if (m.eur != 0) {
					os << m.eur << " eur";
					if (m.ct != 0)
						os << ", ";
				}

				if (m.ct != 0) {
					long long absCt = std::max(m.ct, -m.ct);
					if (absCt < 10)
						os << "0";
					os << absCt << " ct";
				}

				return os;
			}

			std::istream& operator>>(std::istream& is, money& m) {
				long long eur, ct;
				is >> eur >> ct;
				m = money(eur, ct);
				return is;
			}
		}
	}
}
