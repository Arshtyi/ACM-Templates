# 艾氏筛

```c++
// 埃氏筛 - 时间复杂度 O(n log log n)
vector<bool> sieve_of_eratosthenes(int n)
{
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    return is_prime;
}

int count_primes_eratosthenes(int n)
{
    vector<bool> is_prime = sieve_of_eratosthenes(n);
    return count(is_prime.begin(), is_prime.end(), true);
}
```

# 线性筛/欧拉筛

```c++
// 线性筛（欧拉筛）- 时间复杂度 O(n)
vector<int> linear_sieve(int n)
{
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++)
        {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0)
                break;
        }
    }

    return primes;
}

int count_primes_linear(int n)
{
    return linear_sieve(n).size();
}
```

# 区间筛/分段筛

```c++
// 线性筛（欧拉筛）- 时间复杂度 O(n)
vector<int> linear_sieve(int n)
{
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++)
        {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0)
                break;
        }
    }

    return primes;
}

// 区间筛（分段筛）- 用于处理大范围
vector<int> segmented_sieve(int n)
{
    const int SQRT_N = sqrt(n) + 1;

    // 先筛出sqrt(n)内的质数
    vector<int> small_primes = linear_sieve(SQRT_N);

    // 分段处理
    const int SEGMENT_SIZE = 1e5;
    vector<int> result = small_primes;

    vector<bool> segment(SEGMENT_SIZE);
    for (long long low = SQRT_N + 1; low <= n; low += SEGMENT_SIZE)
    {
        fill(segment.begin(), segment.end(), true);
        long long high = min(low + SEGMENT_SIZE - 1, (long long)n);

        for (int p : small_primes)
        {
            long long start = (low / p) * p;
            if (start < low)
                start += p;

            for (long long j = start; j <= high; j += p)
            {
                segment[j - low] = false;
            }
        }

        for (long long i = 0; i < high - low + 1; i++)
        {
            if (segment[i])
            {
                result.push_back(low + i);
            }
        }
    }

    return result;
}
```

# 优化艾氏筛

```c++
// 使用bitset优化的埃氏筛 - 节省内存
int bitset_sieve(int n)
{
    const int MAX_N = 1e8;
    static bitset<MAX_N + 1> is_prime;
    is_prime.set(); // 全部设为1
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                is_prime[j] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
            count++;
    }

    return count;
}
```

