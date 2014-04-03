#include <vector>
#include <cstdio>

class Elem
{
public:
	int x;
	int y;
	long long int val;

	Elem(int x, int y)
	: x(x), y(y), val((long long int)x*y)
	{}

	Elem (const Elem& e)
	{
		x = e.x;
		y = e.y;
		val = e.val;
	}
};

class Heap
{
private:
	std::vector<Elem> list;

	void heapify(int i)
	{
 		int left = i << 1; // left ← 2i
		int right = i << 1 | 1; // right ← 2i + 1
		int largest = i; // largest ← i

		if ((left <= size()) && (list[left].val > list[largest].val)) // if left ≤ heap_length[A] and A[left] > A[largest] then:
			largest = left; // largest ← left
		if ((right <= size()) && (list[right].val > list[largest].val)) // if right ≤ heap_length[A] and A[right] > A[largest] then:
			largest = right; // largest ← right
		if (largest != i) // if largest ≠ i then:
		{ // swap A[i] ↔ A[largest]
			Elem temp = list[i];
			list[i] = list[largest];
			list[largest] = temp;

			heapify(largest);
		}
	}

public:
	Heap() // OK
	{
		list.push_back( Elem(0, 0) ); // Add some trash in 0 index. I won't use it.
	}

	int size() // OK
	{
		return list.size() - 1; // I have trash at index 0. That's why there is '-1'.
	}

	void insert(Elem e) // OK
	{
		list.push_back(e); // Add the element to the bottom level of the heap.
		
		int i = size() - 1;
		int parent = i >> 1;

		while ((parent >= 1) && (list[parent].val < list[i].val)) // Compare the added element with its parent; if they are in the correct order, stop.
		{ // If not, swap the element with its parent and return to the previous step.
			Elem temp = list[parent];
			list[parent] = list[i];
			list[i] = temp;

			i = parent;
			parent = i >> 1;
		}
	}

	Elem extract()
	{
		Elem e = list[1];
		list[1] = list[size()];
		list.pop_back();
		heapify(1);
		
		return e; 
	}
};


int main(void)
{
	int M, k; // M <= 10^6, k <= 2*10^6
	scanf("%d %d", &M, &k);

	Heap heap = Heap();
	heap.insert( Elem(M, M) );

	int counter = 0;
	long long int last = 1000000000001;

	Elem E = Elem(0, 0);

	while (counter < k) // <= ????
	{
		E = heap.extract();

		if (E.val < last)
		{
			last = E.val;
			printf("%lld\n", E.val);
			counter++;
		}
		
		if (E.y >= 1)
		{
			if (E.x - 1 == E.y)
				heap.insert( Elem(E.x - 1, E.y) );

			heap.insert( Elem(E.x, E.y - 1) );
		}
	}

	return 0;
}
