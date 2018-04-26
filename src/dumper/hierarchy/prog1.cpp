
#include <string>
#include <ostream>
#include <iostream>
#include <utility>
#include <iomanip>

template<class L, class R>
class CMine {
public:
	CMine(L _l, R _r) : l(_l), r(_r) {
		std::cout << "CMine: (t,r) = (" << l << "," << r << ")" << std::endl;
	}
	
	bool operator()() {
		return l == r;
	}
private:
	L l;
	R r;
};

template<typename T1, typename T2>
auto Plus1(T1&& t1, T2&& t2) -> decltype(std::forward<T1>(t1) + std::forward<T2>(t2))
{
	CMine<T1, T2> my(t1, t2);

	
	//return std::forward<T1>(t1) + std::forward<T2>(t2);
	return my();
}

template<typename T1, typename T2>
bool Plus2(T1 t1, T2 t2) 
{
	CMine<T1, T2> my(t1, t2);

	
	return my();
}


int factorial1(int n) 
{
	int f = 1;

	for (int i = 1; i <= n; i++) {
		f = f * i;
		std::cout << "f  = " << f << " i = " << i <<  std::endl;
	}

	return f;
}

int factorial2(int n) 
{
	
	if (n <= 1) { 
		return 1;
	}
	
	return factorial2(n - 1) * n;
}


int
main(int argc, char *argv[])
{
	std::cout << factorial1(4) << std::endl;	
	std::cout << factorial2(4) << std::endl;	
	int n = 8;
	int w = n >> 2;

	std::cout << "w = " << w << " n = " << n << std::endl;

	//	b = b << 2;
	int r = n - (w << 2);	
	std::cout << "rmain = " << r  << std::endl;
//	std::cout << "main: etnter to .." << std::endl;
//	std::cout << "plus1(5,6) = " << Plus1(5,6) << std::endl;
//	std::cout << "plus2(5,6) = " << Plus2(5,6) << std::endl;
//	std::cout << "plus2(5,5) = " << Plus2(5,5) << std::endl;

	CMine<int, int> my(5, 6);
	auto i = 6;
}
