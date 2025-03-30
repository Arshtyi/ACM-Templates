int binarySearch(vector<int> &arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // 未找到
}
// 二分查找左边界 - O(log n)
int lowerBound(vector<int> &arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
// 二分查找右边界 - O(log n)
int upperBound(vector<int> &arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}