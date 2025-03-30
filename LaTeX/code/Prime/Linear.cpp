vector<int> linear_sieve(int n)
{
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
            primes.push_back(i);
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