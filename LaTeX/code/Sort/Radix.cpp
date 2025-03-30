void countingSortForRadix(vector<int> &arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
void radixSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortForRadix(arr, exp);
}