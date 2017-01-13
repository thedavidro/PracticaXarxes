#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <limits>

void DecToBin(void) {
	while (true) {
		std::cout << "Enter a non-negative number (0-exit): ";

		unsigned long long x = 0;
		std::cin >> x;

		if (!x) break;

		std::string s =
			std::bitset<std::numeric_limits<unsigned long long>::digits>(x).to_string();

		std::string::size_type n = s.find('1');
		std::cout << s.substr(n) << std::endl;
	}
}