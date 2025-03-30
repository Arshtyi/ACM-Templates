int bitset_sieve(int n)
{
    const int MAX_N = 1e8;
    static bitset<MAX_N + 1> is_prime;
    is_prime.set(); // 全部设为1
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= n; i++)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = 0;
    int count = 0;
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            count++;
    return count;
}