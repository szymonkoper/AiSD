#include <iostream>
#include <vector>
#include <climits>

unsigned int min_cost(std::vector<std::vector<unsigned int> > &v, std::vector<unsigned int> &c, unsigned int j, unsigned int i)
{
  unsigned int min = INT_MAX;
  for (unsigned int m = i; m < j; ++m)
  {
    unsigned int current = v[m][i] + v[j][m+1] + c[i] * c[m+1] * c[j+1];
    if (current < min) min = current;
  }

  return min;
}

int main()
{
  unsigned int tests_cnt;
  for (std::cin >> tests_cnt; tests_cnt > 0; --tests_cnt)
  {
    unsigned int matrices_cnt;
    std::cin >> matrices_cnt;

    std::vector<unsigned int> matrices_sizes;
    matrices_sizes.reserve(matrices_cnt + 1);

    std::vector<std::vector<unsigned int> > matrices_costs;
    matrices_costs.resize(matrices_cnt);

    for (unsigned int i = 0; i < matrices_cnt; ++i)
      matrices_costs[i].resize(i + 1);

    for (unsigned int i = 0; i <= matrices_cnt; ++i)
    {
      unsigned int current_size;
      std::cin >> current_size;

      matrices_sizes[i] = current_size;
    }

    for (unsigned int i = 0; i < matrices_cnt; ++i)
      matrices_costs[i][i] = 0;

    for (unsigned int z = 1; z < matrices_cnt; ++z)
      for (unsigned int x = 0; x < matrices_cnt - z; ++x)
        matrices_costs[z+x][x] = min_cost(matrices_costs, matrices_sizes, z + x, x);

    std::cout << matrices_costs[matrices_cnt - 1][0] << std::endl;
  }

  return 0;
}
