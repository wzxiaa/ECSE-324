extern int MAX_2(int x, int y);

int main(void)
{
	int arr[] = {9, 8, 7, 6, 5, 4, 20, 1};
	int n = sizeof(arr)/sizeof(arr[0]);
	int result = arr[0];
	int i;

	for(i = 0; i < n; i++) {
		result = MAX_2(result, arr[i]);
	}
	return result;
}
