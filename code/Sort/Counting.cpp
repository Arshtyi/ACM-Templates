void countingSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    vector<int> output(n);
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    for (int i = 1; i <= maxVal; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}