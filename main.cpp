#include <iostream>
#include <string>
#include <vector>
#include "mymemory.h"

int main() {

	const int ROWS = 10, COLS = 10;

	std::vector<std::vector<my::shared_ptr<int>>> data(ROWS);

	for (int i = 0; i < data.size(); ++i) {
		data[i].resize(COLS);
		for (my::shared_ptr<int>& temp : data[i]) {
			(*temp) = i; 
		}
	}

	for (std::vector<my::shared_ptr<int>>& temp : data) {
		for (my::shared_ptr<int> ptr : temp) {
			std::cout << *ptr << " ";
		}
		std::cout << "\n";
	}

	std::cout << data[0][0] << ": " << *data[0][0];




	return 0;
}