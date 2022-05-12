#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
using namespace std;
using ints =vector<int>;
ints allnums{ 1,2,3,4,5,6,7,8,9 };
inline bool in(auto&& container, auto&& item) {
	return find(container.begin(), container.end(), item) != container.end();
}
ints what_can_put(ints& state, ints::iterator pos) {
	auto x = (pos - state.begin()) % 9,y= (pos - state.begin())/9;
	ints had(pos - x, pos - x + 9);
	for (int i = 0; i < 9; ++i)had.push_back(state.at(i * 9 + x));
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; ++i)for (int j = y / 3 * 3; j < y / 3 * 3 + 3; ++j)
		had.push_back(state.at(j*9+i));
	ints res;
	for (auto& i : allnums) if (!in(had, i))res.push_back(i);
	return res;
}
void output(const ints& state) {
	cout << "\t----------------------\n\t";
	for (size_t i = 0; i < state.size(); ++i) {
		cout << state.at(i) << ' ';
		if ((i + 1) % 3 == 0)cout << "| ";
		if ((i + 1) % 9==0)cout << "\n\t";
		if ((i + 1) % 27 == 0)cout << "----------------------\n\t";
	}
}
bool solve(ints& state) {
	if (!in(state, 0))return true;
	for (auto at{ state.begin() }; at != state.end(); ++at) if (*at == 0) {
			auto cans{ what_can_put(state, at) };
			for (auto&& v : cans) {
				*at = v;
				if (solve(state))return true;
			}
			*at = 0; return false;
		}
}
int main() {
	string _board;
	ints board;
	cout << "请逐行输入，空格输0：\n";
	cin >> _board;
	if (size_t len = _board.length();len != 81) {
		cout << format("数量错误，长度为{}",len);
		return 1;
	}
	format_to(back_inserter(board), "{}", _board);
	for (auto& i : board)i -= 48;
	solve(board);
	output(board);
	system("pause");
	return 0;
}