#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::ios::sync_with_stdio(false);

	// useful variables
	register unsigned int i, j, k, l, r; // iterators for inner loops
	unsigned char a, b, c; // temporary variables to store symbols from input
	std::string w; // word to find in the grammar
	unsigned int w_len; // word length

	// I want to store values in triangle-shaped array because I don't like wasting memory.
	std::vector< std::vector<unsigned char> > triangle;


	// number of instances
	unsigned int instCnt; // 1 <= instCnt <= 20
	std::cin >> instCnt;

	// for each instance
	for (unsigned int inst = 0; inst < instCnt; ++inst)
	{
		// number of type I rules
		unsigned int m1;
		std::cin >> m1;

		// number of type II rules
		unsigned int m2;
		std::cin >> m2;


		// get all rules of type I: A -> BC
		unsigned char rules1[8][8];
		for (i = 0; i < 8; ++i) // zeroing
			for (j = 0; j < 8; ++j)
				rules1[i][j] = 0;


		for (i = 0; i < m1; ++i)
		{
			std::cin >> a >> b >> c;
			rules1[b - 'A'][c - 'A'] |= (1 << (a - 'A'));
		}

		// get all rules of type II: A -> b
		unsigned char rules2[26]; // There may be error - Maybe 26 is too few?
		for (i = 0; i < 26; ++i) // zeroing
			rules2[i] = 0;

		for (i = 0; i < m2; ++i)
		{
			std::cin >> a >> b;
			rules2[b - 'a'] |= (1 << (a - 'A'));
		}

		// get w - word to find
		std::cin >> w; // example: bbaab
		w_len = w.length();

		triangle.clear(); // Not sure if it's necessary.
		triangle.reserve(w_len);

		bool isfull = 1; // if all elements in row are 255 - print "TAK"
		if (w_len < 201) // better for short words (counts in fly)
		{
			for (i = 0; i < w_len; ++i)
			{
				triangle[i].reserve(w_len - i); // reserve space in vectors
				for (j = 0; j < w_len - i; ++j) // zeroing triangle
					triangle[i][j] = 0;
				triangle[0][i] = rules2[ w[i] - 'a' ]; // initialize bottom row
			}

			for (i = 0; i < w_len; ++i) // row
			{
				isfull = 1;
				for (j = 0; j < w_len - i; ++j) // column
				{
					for (k = 0; k < i; ++k) if (triangle[i-k-1][j] && triangle[k][i+j-k]) // division
						for (l = 0; l < 8; ++l) if ((1 << l) & triangle[i-k-1][j])
							for (r = 0; r < 8; ++r) if ((1 << r) & (triangle[k][i+j-k]))
								triangle[i][j] |= rules1[l][r];
				
					if (triangle[i][j] != 255) isfull = 0;
				}

				if (isfull && i) break;
			}
		}
		else // better for long words (using preprocessing)
		{
			unsigned char combinations[256][256]; // array to store values for all possible combinations
			for (i = 0; i < 256; ++i) // maybe we can make this array from the other side? if there is sth in rules1 then light bit
				for (j = 0; j < 256; ++j)
				{
					combinations[i][j] = 0; // zeroing
					for (l = 0; l < 8; ++l) if (i & (1 << l)) // maybe change for to while and add 2^x to i after miss
						for (r = 0; r < 8; ++r) if (j & (1 << r))
							combinations[i][j] |= rules1[l][r];
				}

			for (i = 0; i < w_len; ++i)
			{
				triangle[i].reserve(w_len - i); // reserve space in vectors
				for (j = 0; j < w_len - i; ++j) // zeroing triangle
					triangle[i][j] = 0;
				triangle[0][i] = rules2[ w[i] - 'a' ]; // initialize bottom row
			}

			for (i = 0; i < w_len; ++i) // row
			{
				isfull = 1;
				for (j = 0; j < w_len - i; ++j) // column
				{
					for (k = 0; k < i; ++k) //if (triangle[i-k-1][j] != 0 && triangle[k][i+j-k] != 0) // division
						triangle[i][j] |= combinations[ triangle[i-k-1][j] ][ triangle[k][i+j-k] ];

					if (triangle[i][j] != 255) isfull = 0;
				}

				if (isfull && i) break;
			}
		}

		if ((isfull || (triangle[w_len - 1][0] & 0x01))) std::cout << "TAK\n";
		else std::cout << "NIE\n";
	}

	return 0;
}
