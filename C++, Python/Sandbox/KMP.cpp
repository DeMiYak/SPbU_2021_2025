#include "KMP.h"

vector<int> computeLPSArray(const string& pattern) {
	int m = pattern.length();
	vector<int> lps(m, 0);
	int length = 0;
	int i = 1;

	while (i < m) {
		if (pattern[i] == pattern[length]) {
			++length;
			lps[i] = length;
			++i;
		}
		else {
			if (length != 0) {
				length = lps[length - 1];
			}
			else {
				lps[i] = 0;
				++i;
			}
		}
	}
	return lps;
}

void KMPSearch(const string& text, const string& pattern)
{
	int n = text.length();
	int m = pattern.length();

	if (m == 0) {
		cout << "Pattern empty" << endl;
		return;
	}
	if (n == 0) {
		cout << "Text empty" << endl;
		return;
	}
	if (m > n) {
		cout << "Pattern > Text" << endl;
		return;
	}

	vector<int> lps = computeLPSArray(pattern);

	int i = 0;
	int j = 0;

	while (i < n) {
		if (pattern[j] == text[i]) {
			++i;
			++j;
		}
		if (j == m) {
			cout << "Index: " << i - j << endl;
			j = lps[j - 1];
		}
		else if (i < n && pattern[j] != text[i]) {
			if (j != 0) {
				j = lps[j - 1];
			}
			else {
				++i;
			}
		}
	}
}

map<char, int> buildBadCharTable(const string& pattern)
{
	int m = pattern.length();
	map<char, int> badChar;
	for (int i = 0; i < m; ++i) {
		badChar[pattern[i]] = i;
	}
	return badChar;
}

void BoyerMooreSearch(const string& text, const string& pattern)
{
	int n = text.length();
	int m = pattern.length();

	if (m == 0) {
		cout << "Pattern empty" << endl;
		return;
	}

	if (n == 0) {
		cout << "Text empty" << endl;
		return;
	}

	if (m > n) {
		cout << "Pattern > Text" << endl;
		return;
	}

	map<char, int> badChar = buildBadCharTable(pattern);

	int s = 0;
	while (s <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && pattern[j] == text[s + j]) {
			j--;
		}
		if (j < 0) {
			cout << "Index: " << s << endl;
			s += (s + m < n) ? m - badChar[text[s + m]] : 1;
		}
		else {
			int badCharShift = (badChar.count(text[s + j])) ? badChar[text[s + j]] : -1;
			s += max(1, j - badCharShift);
		}
	}
}

void RabinKarpSearch(const string& text, const string& pattern)
{
	int n = text.length();
	int m = pattern.length();

	if (m == 0 || n == 0 || m > n) {
		cout << "Bad input" << endl;
		return;
	}

	long long patternHash = 0;
	long long textHash = 0;
	long long h = 1;

	for (int i = 0; i < m - 1; ++i) {
		h = (h * D) % Q;
	}

	for (int i = 0; i < m; ++i) {
		patternHash = (D * patternHash + pattern[i]) % Q;
		textHash = (D * textHash + text[i]) % Q;
	}

	for (int i = 0; i <= n - m; ++i) {
		if (patternHash == textHash) {
			bool match = true;
			for (int j = 0; j < m; ++j) {
				if (text[i + j] != pattern[j]) {
					match = false;
					break;
				}
			}
			if (match) {
				cout << "Index: " << i << endl;
			}
		}

		if (i < n - m) {
			textHash = (D * (textHash - text[i] * h) + text[i + m]) % Q;
			if (textHash < 0) {
				textHash = (textHash + Q);
			}
		}
	}
}