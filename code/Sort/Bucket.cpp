void bucketSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;
    int maxVal = *max_element(arr.begin(), arr.end());
    int numBuckets = maxVal + 1;
    vector<vector<int>> buckets(numBuckets);
    for (int i = 0; i < n; i++)
    {
        buckets[arr[i]].push_back(arr[i]);
    }
    int idx = 0;
    for (int i = 0; i < numBuckets; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            arr[idx++] = buckets[i][j];
}