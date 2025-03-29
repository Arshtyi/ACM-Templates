void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void shellSort(vector<int> &arr)
{
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void heapify(vector<int> &arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> &arr)
{
    int n = arr.size();

    // 建立堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 一个个从堆顶取出元素
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void countingSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;

    // 找出最大值
    int maxVal = *max_element(arr.begin(), arr.end());

    vector<int> count(maxVal + 1, 0);
    vector<int> output(n);

    // 统计每个元素出现的次数
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // 计算累积和
    for (int i = 1; i <= maxVal; i++)
        count[i] += count[i - 1];

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 复制回原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
void bucketSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;

    // 确定桶的数量，这里设为元素最大值+1
    int maxVal = *max_element(arr.begin(), arr.end());
    int numBuckets = maxVal + 1;
    vector<vector<int>> buckets(numBuckets);

    // 将元素分配到桶中
    for (int i = 0; i < n; i++)
    {
        buckets[arr[i]].push_back(arr[i]);
    }

    // 从桶中取出元素并重新放回原数组
    int idx = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            arr[idx++] = buckets[i][j];
        }
    }
}
void countingSortForRadix(vector<int> &arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // 统计出现次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 计算累积和
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 复制回原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;

    // 找出最大值
    int maxVal = *max_element(arr.begin(), arr.end());

    // 对每一位进行计数排序
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortForRadix(arr, exp);
}