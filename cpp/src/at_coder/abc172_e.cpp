//include
//------------------------------------------
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

//conversion
//------------------------------------------
inline int toint(string s) { int v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

template <class Integer>
class ResidueInteger
{
private:
	Integer mod_;
	Integer n_;
	static Integer global_mod_;

	// computational complexity: o(log(max(a, b))) 
	static inline pair<Integer, Integer> getBezoutsIdentitySolution(Integer a, Integer b)
	{
		if (b == 0)
		{
			return { 1, 0 };
		}
		auto sol = getBezoutsIdentitySolution(b, a % b);
		return { sol.second, sol.first - (a / b) * sol.second };
	}

public:
	static Integer default_mod_;

	Integer getModValue(const Integer& n) const
	{
		return (n % mod_ + mod_) % mod_;
	}

	// computational complexity: o(log(max(n, mod))) 
	inline Integer getModInverse(const Integer& n) const
	{
		auto sol = getBezoutsIdentitySolution(n, mod_);
		if (n * sol.first + mod_ * sol.second != 1)
		{
			return -1;
		}
		return getModValue(sol.first);
	}

	ResidueInteger() : mod_(default_mod_), n_(getModValue(0)) {}
	ResidueInteger(Integer n) : mod_(default_mod_), n_(getModValue(n)) {}
	ResidueInteger(Integer n, Integer mod) : mod_(mod), n_(getModValue(n)) {}

	inline ResidueInteger operator+(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ + rhs.n_, this->mod_ };
	}
	inline ResidueInteger operator+(const Integer& rhs) const
	{
		return { this->n_ + getModValue(rhs), this->mod_ };
	}
	friend inline ResidueInteger operator+(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) + rhs.n_, rhs.mod_ };
	}
	inline ResidueInteger& operator+=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ + rhs.n_);
		return *this;
	}
	inline ResidueInteger& operator+=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ + getModValue(rhs));
		return *this;
	}

	inline ResidueInteger operator-(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ - rhs.n_, this->mod_ };
	}
	inline ResidueInteger operator-(const Integer& rhs) const
	{
		return { this->n_ - getModValue(rhs), this->mod_ };
	}
	friend inline ResidueInteger operator-(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) - rhs.n_, rhs.mod_ };
	}
	inline ResidueInteger& operator-=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ - rhs.n_);
		return *this;
	}
	inline ResidueInteger& operator-=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ - getModValue(rhs));
		return *this;
	}

	inline ResidueInteger operator*(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ * rhs.n_, this->mod_ };
	}
	inline ResidueInteger operator*(const Integer& rhs) const
	{
		return { this->n_ * getModValue(rhs), this->mod_ };
	}
	friend inline ResidueInteger operator*(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) * rhs.n_, rhs.mod_ };
	}
	inline ResidueInteger& operator*=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ * rhs.n_);
		return *this;
	}
	inline ResidueInteger& operator*=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ * getModValue(rhs));
		return *this;
	}

	inline ResidueInteger operator/(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ * getModInverse(rhs.n_), this->mod_ };
	}
	inline ResidueInteger operator/(const Integer& rhs) const
	{
		return { this->n_ * getModInverse(getModValue(rhs)), this->mod_ };
	}
	friend inline ResidueInteger operator/(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) * rhs.getModInverse(rhs.n_), rhs.mod_ };
	}
	inline ResidueInteger& operator/=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ * getModInverse(rhs.n_));
		return *this;
	}
	inline ResidueInteger& operator/=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ * getModInverse(getModValue(rhs)));
		return *this;
	}

	inline bool operator==(const ResidueInteger& rhs) const
	{
		return (this->n_ == rhs.n_) && (this->mod_ == rhs.mod_);
	}
	inline bool operator==(const Integer& rhs) const
	{
		return this->n_ == getModValue(rhs);
	}
	friend bool operator==(const Integer& lhs, const ResidueInteger& rhs)
	{
		return rhs.getModValue(lhs) == rhs.n_;
	}

	Integer get_n() const { return n_; }

	friend std::ostream& operator<<(std::ostream& lhs, const ResidueInteger& rhs)
	{
		return lhs << rhs.n_;
	}

	friend std::istream& operator>>(std::istream& lhs, ResidueInteger& rhs)
	{
		lhs >> rhs.n_;
		return lhs;
	}
};
using rll = ResidueInteger<ll>;
template<> ll rll::default_mod_ = 1000000007LL;

int solve() {
	ll n, m;
	cin >> n >> m;

	vector<ll> factorials(m + 1LL);
	factorials[0] = 1LL;
	for (ll i = 1; i <= m; ++i) {
		factorials[i] = (rll(factorials[i - 1]) * i).get_n();
	}

	rll res = rll(factorials[m]) / factorials[m - n];
	ll sign = -1;
	for (ll i = 1; i <= n; ++i) {
		res += rll(factorials[m - i]) / factorials[m - n] * factorials[n] / factorials[i] / factorials[n - i] * sign;
		sign *= -1;
	}
	res *= rll(factorials[m]) / factorials[m - n];

	cout << res.get_n() << endl;

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}