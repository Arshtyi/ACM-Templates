vector<int> segmented_sieve(int n)
{
    const int SQRT_N = sqrt(n) + 1;
    vector<int> small_primes = linear_sieve(SQRT_N);
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
                segment[j - low] = false;
        }
        for (long long i = 0; i < high - low + 1; i++)
        {
            if (segment[i])
                result.push_back(low + i);
        }
    }
    return result;
}