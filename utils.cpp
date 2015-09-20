#include "utils.hpp"

bool isInt(std::string s) {
	for(int i = 0; i < int(s.size()); ++i)
		if (!(s[i]>='0' && s[i]<='9'))
			return false;
	return true;
}

int myStoi(std::string s) {
	int x=0;
	for (int i = 0; i < int(s.size()); ++i)
		x = 10*x+(s[i]-'0');
	return x;
}