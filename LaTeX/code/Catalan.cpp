// #include <iostream>
// #include <vector>
// #include <string>
// #include <stdexcept>
// using namespace std;
// 大整数类，用于处理超大数值
class BigInteger
{
private:
    vector<int> digits; // 存储数字，低位在前，高位在后

public:
    // 默认构造函数
    BigInteger()
    {
        digits.push_back(0);
    }

    // 从整数构造
    BigInteger(int n)
    {
        if (n == 0)
        {
            digits.push_back(0);
            return;
        }

        while (n > 0)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
    }

    // 乘以整数
    BigInteger operator*(int num) const
    {
        if (num == 0)
            return BigInteger(0);

        BigInteger result;
        result.digits.clear();

        long long carry = 0;
        for (int digit : digits)
        {
            long long product = (long long)digit * num + carry;
            result.digits.push_back(product % 10);
            carry = product / 10;
        }

        while (carry > 0)
        {
            result.digits.push_back(carry % 10);
            carry /= 10;
        }

        return result;
    }

    // 除以整数
    BigInteger divideBy(int divisor) const
    {
        if (divisor == 0)
            throw runtime_error("Division by zero");

        BigInteger result;
        result.digits.resize(digits.size());

        long long remainder = 0;
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            remainder = remainder * 10 + digits[i];
            result.digits[i] = remainder / divisor;
            remainder %= divisor;
        }

        // 移除前导零
        while (result.digits.size() > 1 && result.digits.back() == 0)
        {
            result.digits.pop_back();
        }

        return result;
    }

    // 转换为字符串
    string toString() const
    {
        string result;
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            result += (char)(digits[i] + '0');
        }
        return result;
    }
};

// 计算1到n的卡特兰数
vector<BigInteger> calculateCatalanNumbers(int n)
{
    vector<BigInteger> catalan(n + 1);
    catalan[0] = BigInteger(1);

    for (int i = 1; i <= n; i++)
    {
        // 使用公式: C(n) = C(n-1) * (4*n-2) / (n+1)
        catalan[i] = catalan[i - 1] * (4 * i - 2);
        catalan[i] = catalan[i].divideBy(i + 1);
    }

    return catalan;
}