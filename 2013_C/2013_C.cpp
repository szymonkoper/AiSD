#include <stdio.h>


int c[101];
int w[101];



long long int A[100001];
long long int B[100001];

unsigned char AQ[100001];
unsigned char BQ[100001];

int nominalsA[101];
int nominalsB[101];

long long int sumA = 0;
long long int sumB = 0;


int main()
{
	register int i;
	register int j;

	int F;
	int C;

	scanf("%d", &F);
	scanf("%d", &C);


	for (i = 0; i < C; ++i)
	{
		scanf("%d %d", &c[i], &w[i]);
	}

	A[0] = 0;
	B[0] = 0;

	for (i = 1; i <= F; ++i)
	{
		A[i] = -1;
		B[i] = 9223372036854775807;
		for (j = 0; j < C; ++j)
		{
			if (w[j] <= i && A[i - w[j]] > -1)
			{
				if (A[i] < A[i - w[j]] + c[j])
				{
					A[i] = A[i - w[j]] + c[j];
					AQ[i] = j;
				}
				if (B[i] > B[i - w[j]] + c[j])
				{
					B[i] = B[i - w[j]] + c[j];
					BQ[i] = j;
				}
			}
		}
	}

	if (A[F] <= 0 && B[F] >= 9223372036854775807)
	{
		printf("NIE\n");
		return 0;
	}


	i = F;
	while (i > 0)
	{
		nominalsA[ AQ[i] ]++;
		sumA += c[ AQ[i] ];
		i -= w[ AQ[i] ];
	}

	i = F;
	while (i > 0)
	{
		nominalsB[ BQ[i] ]++;
		sumB += c[ BQ[i] ];
		i -= w[ BQ[i] ];
	}


	printf("TAK\n");

	printf("%lld\n", sumB);
	for (i = 0; i < C; ++i)
		printf("%d ", nominalsB[i]);
	printf("\n");

	printf("%lld\n", sumA);
	for (i = 0; i < C; ++i)
		printf("%d ", nominalsA[i]);
	printf("\n");


	return 0;
}