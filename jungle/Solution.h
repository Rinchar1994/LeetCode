#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <map>
#include <typeinfo>
#include <fstream>
#include <stack>

using namespace std;

class Method {
public:
	//正整数转换
	list<int> InttoBin(int a) {
		list<int> bin;
		while (a) {
			bin.push_back(a % 2);
			a /= 2;
		}
		return bin;
	}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x), left(NULL), right(NULL){}
};

class Solution {
public:
	string reverseString(string s) {
		int len = s.size();
		for (int h = 0, t = len - 1; h < t; h++, t--) {
			char temp = s[h];
			s[h] = s[t];
			s[t] = temp;
		}
		return s;
	}

	//-----------------------------------------------------------------
	//正整数加法
	int getSum_pos(int a, int b) {
		Method func;
		list<int> bin_a = func.InttoBin(a), bin_b = func.InttoBin(b), bin_sum;
		int carry = 0;
		list<int> bin_min = bin_a.size() > bin_b.size() ? bin_b : bin_a;
		list<int> bin_max = bin_a.size() > bin_b.size() ? bin_a : bin_b;
		for (int index = bin_min.size(); index < bin_max.size(); index++) {
			bin_min.push_back(0);
		}
		list<int>::iterator p_a = bin_max.begin(), p_b = bin_min.begin();
		while (p_a != bin_max.end()) {
			bin_sum.push_back(*p_a ^ *p_b ^ carry);
			if ((*p_a&&*p_b) || (*p_a&&carry) || (*p_b&&carry)) {
				carry = 1;
			}
			else
				carry = 0;
			p_a++;
			p_b++;
		}
		if (carry == 1)
			bin_sum.push_back(1);
		list<int>::iterator p_sum = bin_sum.end();
		int sum = 0;
		while (p_sum != bin_sum.begin()) {
			sum = sum * 2 + (*(--p_sum));
		}
		return sum;
	}

	//整数类型
	int sumOfTwoIntegers(int a, int b) {
		int sum = 0, bin_a, bin_b, carry = 0;
		for (int index = 0; index < 32; index++) {
			bin_a = a & (1 << index);
			bin_b = b & (1 << index);
			carry = carry << index;
			sum += (bin_a ^ bin_b ^ carry);
			if ((bin_a&&bin_b) || (bin_a&&carry) || (bin_b&&carry))
				carry = 1;
			else
				carry = 0;
		}
		return sum;
	}

	//-----------------------------------------------------------------
	int singleNumber(vector<int>& nums) {
		map<int, int> twice;
		vector<int>::iterator p = nums.begin();
		while (p != nums.end()) {
			if (twice.find(*p) != twice.end()) {
				twice.erase(*p);
			}
			else {
				twice[*p] = 1;
			}
			p++;
		}
		return twice.begin()->first;
	}

	//-----------------------------------------------------------------
	bool happyNumber(int n) {
		list<int> sum;
		list<int>::iterator item;
		sum.push_back(n);
		int temp = happyNumberAdd(n);
		while (temp != 1) {
			item = find(sum.begin(), sum.end(), temp);
			if (item != sum.end()) {
				return false;
			}
			sum.push_back(temp);
			temp = happyNumberAdd(temp);
		}
		return true;
	}

	int happyNumberAdd(int n) {
		int sum = 0;
		while (n) {
			sum += (n % 10) * (n % 10);
			n /= 10;
		}
		return sum;
	}

	//-----------------------------------------------------------------
	//时间复杂度过高，超时
	int GasStation(vector<int>& gas, vector<int>& cost) {
		//排除一些非常明显的错误
		int sum = 0;
		for (int i = 0; i < gas.size(); i++) {
			sum += gas[i] - cost[i];
		}
		if (sum < 0) {
			return -1;
		}
		//正常情况
		int status, cnt, start = 0;
		while (start < gas.size()) {
			cnt = 0, status = 0;
			int j = start;
			while (cnt < gas.size()) {
				status += gas[j] - cost[j];
				if (status < 0) {
					start = ++j;
					break;
				}
				if (j == gas.size() - 1)
					j = 0;
				else
					j++;
				cnt++;
			}
			if (cnt == gas.size())
				return start;
		}
		return -1;
	}

	//--------------------------------------------------------------------
	vector<int> rows;
	vector<int> cols;
	vector<int> diagonal_p;
	vector<int> diagonal_n;

	vector<vector<string>> NQueens(int n) {
		vector<string> model = NQueens_init(n);
		vector<vector<string>> result;
		rows = vector<int>(n, 0);
		cols = vector<int>(n, 0);
		diagonal_p = vector<int>(2 * n - 1, 0);
		diagonal_n = vector<int>(2 * n - 1, 0);
		solveNQueens(0, n, result, model);
		return result;
	}

	vector<string> NQueens_init(int n) {
		vector<string> model;
		/*string str = "";
		for (int i = 0; i < n; i++) {
			str += '.';
		}*/
		string str = string(n, '.');
		for (int i = 0; i < n; i++) {
			model.push_back(str);
		}
		return model;
	}

	void solveNQueens(int currentRow, int n, vector<vector<string>>& result,
		vector<string>& model) {
		if (currentRow == n) {
			result.push_back(model);
			return;
		}
		for (int currentCol = 0; currentCol < n; currentCol++) {
			if (!NQueens_Valid(currentRow, currentCol, n)) {
				continue;
			}
			PutQueen(currentRow, currentCol, n, model);
			solveNQueens(currentRow + 1, n, result, model);
			DeleteQueen(currentRow, currentCol, n, model);
		}
	}

	void DeleteQueen(int currentRow, int currentCol, int n, vector<string>& model) {
		model[currentRow][currentCol] = '.';
		rows[currentRow] = 0;
		cols[currentCol] = 0;
		diagonal_p[currentCol + currentRow] = 0;
		diagonal_n[currentCol - currentRow + n - 1] = 0;
	}

	void PutQueen(int currentRow, int currentCol, int n, vector<string>& model) {
		model[currentRow][currentCol] = 'Q';
		rows[currentRow] = 1;
		cols[currentCol] = 1;
		diagonal_p[currentCol + currentRow] = 1;
		diagonal_n[currentCol - currentRow + n - 1] = 1;
	}

	bool NQueens_Valid(int row, int col, int n) {
		if (rows[row] == 0 && cols[col] == 0 && diagonal_p[row + col] == 0
			&& diagonal_n[col - row + n - 1]==0)
			return true;
		else
			return false;
	}

	//--------------------------------------------------------------------
	struct pos{
		int pos_x;
		int pos_y;
	};
	void SudokuSolver(vector<vector<char>>& board) {
		struct pos position;
		FindEmptyCheck(board, position);
		SudokuSolve(board, position);
	}

	void SudokuSolve(vector<vector<char>>& board, struct pos position) {
		if (position.pos_x == -1)
			return;
		struct pos pos_next;
		for (int i = 1; i <= 9; i++) {
			if (SudokuValid(board, position.pos_x, position.pos_y, '0' + i) == true) {
				board[position.pos_x][position.pos_y] = '0' + i;
				FindEmptyCheck(board, pos_next);
				SudokuSolve(board, pos_next);
				FindEmptyCheck(board, pos_next);
				if (pos_next.pos_x == -1)
					return;
				board[position.pos_x][position.pos_y] = '.';
			}
		}
	}

	void FindEmptyCheck(vector<vector<char>> board, struct pos& position) {
		for(int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == '.') {
					position.pos_x = i;
					position.pos_y = j;
					return;
				}
			}
		position.pos_x = -1, position.pos_y = -1;
	}

	bool SudokuValid(vector<vector<char>> board, int row, int col, char ch) {
		if (find(board[row].begin(), board[row].end(), ch) != board[row].end())
			return false;
		for (int index = 0; index < 9; index++) {
			if (board[index][col] == ch)
				return false;
		}
		int row_init = row / 3 * 3, col_init = col / 3 * 3;
		for (int col_i = 0; col_i < 3; col_i++) {
			for (int row_i = 0; row_i < 3; row_i++) {
				if (board[row_init + row_i][col_init + col_i] == ch)
					return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------
	vector<vector<int>> PascalTriangle(int numRows) {
		vector<vector<int>> triangle;
		if (numRows == 0)
			return triangle;
		if (numRows < 3) {
			for (int num = 1; num <= numRows; num++) {
				vector<int> row = vector<int>(num, 1);
				triangle.push_back(row);
			}
			return triangle;
		}
		for (int num = 1; num <= 2; num++) {
			vector<int> row = vector<int>(num, 1);
			triangle.push_back(row);
		}
		for (int num = 3; num <= numRows; num++) {
			vector<int> row = vector<int>(1, 1);
			for (int _num = 2; _num < num; _num++) {
				row.push_back(triangle[num - 2][_num - 2] + triangle[num - 2][_num - 1]);
			}
			row.push_back(1);
			triangle.push_back(row);
		}
		return triangle;
	}

	//--------------------------------------------------------------------
	bool BalancedBinaryTree(TreeNode* root) {
		if (TreeDepth(root) <=2) {
			return true;
		}
		TreeNode* dup = root;
		stack<TreeNode*> node;
		while (dup != NULL) {
			int right = TreeDepth(dup->right);
			int left = TreeDepth(dup->left);
			if (right - left > 1 || left - right > 1)
				return false;
			if (right > 2)
				node.push(dup->right);
			if (left > 2) {
				dup = dup->left;
			}
			else {
				if (node.empty())
					break;
				dup = node.top();
				node.pop();
			}
		}
		return true;
	}

	int TreeDepth(TreeNode* root) {
		if (root == NULL)
			return 0;
		int depth_left = TreeDepth(root->left) + 1;
		int depth_right = TreeDepth(root->right) + 1;
		return depth_left > depth_right ? depth_left : depth_right;
	}

	//--------------------------------------------------------------------
	int AddDigits(int num) {
		while (num / 10) {
			int _num = num, sum = 0;
			while (_num) {
				sum += _num % 10;
				_num /= 10;
			}
			num = sum;
		}
		return num;
	}

	//--------------------------------------------------------------------
	char findTheDifferent(string s, string t) {
		vector<int> count = vector<int>(26, 0);
		int i;
		for (i = 0; i < s.size(); i++) {
			count[s[i] - 'a']++;
			count[t[i] - 'a']--;
		}
		count[t[i] - 'a']--;
		return int(find(count.begin(), count.end(), -1) - count.begin()) + 'a';
	}

	//--------------------------------------------------------------------
	TreeNode* invertTree(TreeNode* root) {
		TreeNode* p = root;
		invertTreeSolve(p);
		return root;
	}

	void invertTreeSolve(TreeNode* p) {
		if (p == NULL)
			return;
		TreeNode* temp = p->left;
		p->left = p->right;
		p->right = temp;
		invertTreeSolve(p->left);
		invertTreeSolve(p->right);
	}

	//--------------------------------------------------------------------
	void moveZeroes(vector<int>& nums) {
		vector<int>::iterator front = nums.begin();
		int len = nums.size();
		while (front < nums.end()) {
			if (*front == 0) {
				//如果不重新赋值的话某些编译器可能会报错，比如visual studio
				front = nums.erase(front);
				continue;
			}
			front++;
		}
		int len_later = nums.size();
		for (int i = 0; i < len - len_later; i++) {
			nums.push_back(0);
		}
	}
};