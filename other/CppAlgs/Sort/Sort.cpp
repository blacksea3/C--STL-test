#include "../public/public.hpp"

//Time:O(n^2)
void SelectionSortInterface(vector<int>& v)
{
	int vSize = v.size();
	for (int i = 0; i < vSize - 1; ++i)
	{
		int minLoc = i;
		int minVal = v[i];
		for (int j = i + 1; j < vSize; ++j)
		{
			if (v[j] < minVal)
			{
				minLoc = j;
				minVal = v[j];
			}
		}
		swap(v[i], v[minLoc]);
	}
}

//Time:O(nlogn)
void MergeSortRecu(vector<int>& v, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		MergeSortRecu(v, left, mid);
		MergeSortRecu(v, mid + 1, right);
		vector<int> temp(right - left + 1);
		int leftLoc = left;
		int rightLoc = mid + 1;
		int tempLoc = 0;
		while (leftLoc <= mid && rightLoc <= right)
		{
			if (v[leftLoc] < v[rightLoc])
				temp[tempLoc++] = v[leftLoc++];
			else
				temp[tempLoc++] = v[rightLoc++];
		}
		if (leftLoc > mid)
			while (rightLoc <= right) temp[tempLoc++] = v[rightLoc++];
		else
			while (leftLoc <= mid) temp[tempLoc++] = v[leftLoc++];
		for (int i = left; i <= right; ++i) v[i] = temp[i - left];
	}
}

void MergeSortInterface(vector<int>& v)
{
	if (v.empty()) return;
	else MergeSortRecu(v, 0, v.size() - 1);
}

//used for small number range sort
//time: O(n + m) m: maxNum - minNum + 1
void CountSortInterface(vector<int>& v)
{
	pair<vector<int>::iterator, vector<int>::iterator> p = minmax_element(v.begin(), v.end());
	int minV = *(p.first);
	int maxV = *(p.second);

	vector<int> memory(maxV - minV + 1);

	for (auto& iterv : v) memory[iterv - minV]++;

	int preIndex = 0;
	for (int iterv = 0; iterv <= maxV - minV; ++iterv)
	{
		int st = memory[iterv];
		while (st > 0)
		{
			v[preIndex++] = iterv + minV;
			st--;
		}
	}
}

//partition vector v
//input: target v, left loc l, right loc r
//return one loc

//  v[i] <= v[loc] equals i < loc
//  v[i] > v[loc] means i > loc

// eg:
// v = [5,7,2,4,8,1,2], l = 2, r = 6
// after function: return 4, v = [5,7,2,1,2,4,8]
int QuickSortPartition(vector<int>& v, int l, int r)
{
	int cmp = v[l];
	int res = l;
	for (int index = l + 1; index <= r; ++index)
	{
		if (v[index] <= cmp)
		{
			swap(v[index], v[res + 1]);
			res++;
		}
	}
	swap(v[l], v[res]);
	return res;
}

void QuickSortRecu(vector<int>& v, int l, int r)
{
	if (l < r)
	{
		int mid = QuickSortPartition(v, l, r);
		QuickSortRecu(v, l, mid - 1);
		QuickSortRecu(v, mid + 1, r);
	}
}

//average time: O(nlogn)
void QuickSortInterface(vector<int>& v)
{
	if (!v.empty()) QuickSortRecu(v, 0, v.size() - 1);
}

//partition vector v
//input: target v, left loc l, right loc r
//return one loc, the pivot value is randomly selected

//  v[i] <= v[loc] equals i < loc
//  v[i] > v[loc] means i > loc

// eg:
// v = [5,7,2,4,8,1,2], l = 2, r = 6
// after function: (pivot == 2) return 4, v = [5,7,2,1,2,4,8]
int RandomQuickSortPartition(vector<int>& v, int l, int r)
{
	int rloc = rand() % (r - l + 1) + l;
	swap(v[rloc], v[l]);
	int cmp = v[l];
	int res = l;
	for (int index = l + 1; index <= r; ++index)
	{
		if (v[index] <= cmp)
		{
			swap(v[index], v[res + 1]);
			res++;
		}
	}
	swap(v[l], v[res]);
	return res;
}

void RandomQuickSortRecu(vector<int>& v, int l, int r)
{
	if (l < r)
	{
		int mid = QuickSortPartition(v, l, r);
		RandomQuickSortRecu(v, l, mid - 1);
		RandomQuickSortRecu(v, mid + 1, r);
	}
}

//average time: O(nlogn)
void RandomQuickSortInterface(vector<int>& v)
{
	if (!v.empty()) RandomQuickSortRecu(v, 0, v.size() - 1);
}

//partition vector v
//input: target v, left loc l, right loc r
//return two loc(m and n), the pivot value is randomly selected

// when i < m, v[i] < pivot
// when n < i, v[i] > pivot
// when m <= i <= n, v[i] == pivot

// eg:
// v = [5,7,2,4,8,1,2], l = 2, r = 6
// after function: (pivot == 2) return pair<int, int>{3,4}, v = [5,7,1,2,2,4,8]
pair<int, int> RandomQuickSort3Partition(vector<int>& v, int l, int r)
{
	int rloc = rand() % (r - l + 1) + l;
	swap(v[rloc], v[l]);
	int pivot = v[l];
	int m = l;
	int n = l;

	for (int index = l + 1; index <= r; ++index)
	{
		if (v[index] < pivot)
		{
			if (m == n) swap(v[index], v[m + 1]);
			else
			{
				swap(v[index], v[m + 1]);
				swap(v[index], v[n + 1]);
			}
			m++;
			n++;
		}
		else if (v[index] == pivot)
		{
			n++;
		}
	}
	swap(v[l], v[m]);
	return pair<int, int>{m, n};
}

void RandomQuickSort3Recu(vector<int>& v, int l, int r)
{
	if (l < r)
	{
		pair<int, int> mid = RandomQuickSort3Partition(v, l, r);
		RandomQuickSort3Recu(v, l, mid.first - 1);
		RandomQuickSort3Recu(v, mid.second + 1, r);
	}
}

//average time: O(nlogn)
void RandomQuickSort3Interface(vector<int>& v)
{
	if (!v.empty()) RandomQuickSort3Recu(v, 0, v.size() - 1);
}

void HeapSortsiftdown(vector<int>& v, size_t i, size_t size)
{
	size_t maxi = i;
	size_t lchild = 2 * i;
	if ((lchild <= size) && (v[lchild - 1] > v[maxi - 1]))
	{
		maxi = lchild;
	}
	size_t rchild = 2 * i + 1;
	if ((rchild <= size) && (v[rchild - 1] > v[maxi - 1]))
	{
		maxi = rchild;
	}
	if (i != maxi)
	{
		swap(v[i - 1], v[maxi - 1]);
		HeapSortsiftdown(v, maxi, size);
	}
}

void HeapSortInterface(vector<int>& v)
{
	if (v.empty()) return;
	for (int i = v.size() / 2; i >= 1; --i) HeapSortsiftdown(v, i, v.size());
	for (size_t loc = v.size() - 1; loc >= 1; --loc)
	{
		swap(v[0], v[loc]);
		HeapSortsiftdown(v, 1, loc);
	}
}

void SortInterface()
{
	vector<int> v = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v) cout << iv << " ";
	cout << endl;
	SelectionSortInterface(v);
	for (auto& iv:v) cout << iv << " ";
	cout << endl;

	vector<int> v2 = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v2) cout << iv << " ";
	cout << endl;
	MergeSortInterface(v2);
	for (auto& iv : v2) cout << iv << " ";
	cout << endl;

	vector<int> v3 = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v3) cout << iv << " ";
	cout << endl;
	CountSortInterface(v3);
	for (auto& iv : v3) cout << iv << " ";
	cout << endl;

	vector<int> v4 = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v4) cout << iv << " ";
	cout << endl;
	QuickSortInterface(v4);
	for (auto& iv : v4) cout << iv << " ";
	cout << endl;

	vector<int> v5 = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v5) cout << iv << " ";
	cout << endl;
	RandomQuickSortInterface(v5);
	for (auto& iv : v5) cout << iv << " ";
	cout << endl;

	vector<int> v6 = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v6) cout << iv << " ";
	cout << endl;
	RandomQuickSort3Interface(v6);
	for (auto& iv : v6) cout << iv << " ";
	cout << endl;

	vector<int> v7 = { 1,7,-1,1,2,3,1,3,2,3,6,7,1,5 };
	for (auto& iv : v7) cout << iv << " ";
	cout << endl;
	HeapSortInterface(v7);
	for (auto& iv : v7) cout << iv << " ";
	cout << endl;
}

/*
int main()
{
	SortInterface();
}
*/
