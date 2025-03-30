// 高精度数类
// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <sstream>
class BigInteger
{
private:
    std::vector<int> digits; // 按位存储，digits[0]为最低位，digits[n-1]为最高位,倒序
    bool isNegative;         // 是否为负数
    // 去除前导零
    void removeLeadingZeros()
    {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        // 如果只剩0，确保是正数
        if (digits.size() == 1 && digits[0] == 0)
            isNegative = false;
    }

public:
    // 构造函数
    BigInteger() : isNegative(false)
    {
        digits.push_back(0);
    }
    BigInteger(long long num)
    {
        isNegative = (num < 0);
        if (num < 0)
            num = -num;
        if (num == 0)
            digits.push_back(0);
        else
            while (num > 0)
            {
                digits.push_back(num % 10);
                num /= 10;
            }
    }
    BigInteger(const std::string &str)
    {
        digits.clear();
        isNegative = false;
        size_t startPos = 0;
        if (str[0] == '-')
        {
            isNegative = true;
            startPos = 1;
        }
        else if (str[0] == '+')
            startPos = 1;
        for (int i = static_cast<int>(str.size()) - 1; i >= static_cast<int>(startPos); i--)
            digits.push_back(str[i] - '0');
        removeLeadingZeros();
    }
    friend std::ostream &operator<<(std::ostream &os, const BigInteger &num)
    {
        if (num.isNegative && !(num.digits.size() == 1 && num.digits[0] == 0))
            os << '-';
        for (int i = num.digits.size() - 1; i >= 0; i--)
            os << num.digits[i];
        return os;
    }
    bool operator<(const BigInteger &other) const
    {
        if (isNegative != other.isNegative)
            return isNegative;

        if (digits.size() != other.digits.size())
            return isNegative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();

        for (int i = digits.size() - 1; i >= 0; i--)
            if (digits[i] != other.digits[i])
                return isNegative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        return false; // 相等
    }
    bool operator>(const BigInteger &other) const
    {
        return other < *this;
    }
    bool operator==(const BigInteger &other) const
    {
        return !(*this < other) && !(other < *this);
    }
    bool operator<=(const BigInteger &other) const
    {
        return *this < other || *this == other;
    }
    bool operator>=(const BigInteger &other) const
    {
        return *this > other || *this == other;
    }
    bool operator!=(const BigInteger &other) const
    {
        return !(*this == other);
    }
    BigInteger operator+(const BigInteger &other) const
    {
        if (isNegative != other.isNegative)
            if (isNegative)
            {
                BigInteger temp = *this;
                temp.isNegative = false;
                return other - temp;
            }
            else
            {
                BigInteger temp = other;
                temp.isNegative = false;
                return *this - temp;
            }
        BigInteger result;
        result.digits.clear();
        result.isNegative = isNegative;
        int carry = 0;
        size_t maxSize = std::max(digits.size(), other.digits.size());
        for (size_t i = 0; i < maxSize || carry; i++)
        {
            int sum = carry;
            if (i < digits.size())
                sum += digits[i];
            if (i < other.digits.size())
                sum += other.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        result.removeLeadingZeros();
        return result;
    }
    BigInteger operator-(const BigInteger &other) const
    {
        if (isNegative != other.isNegative)
        {
            BigInteger temp = other;
            temp.isNegative = !temp.isNegative;
            return *this + temp;
        }
        if (isNegative)
        {
            BigInteger a = other;
            BigInteger b = *this;
            a.isNegative = false;
            b.isNegative = false;
            return a - b;
        }
        if (this->compare(other, false) < 0)
        {
            BigInteger result = other - *this;
            result.isNegative = !result.isNegative;
            return result;
        }
        BigInteger result;
        result.digits.clear();
        int borrow = 0;
        for (size_t i = 0; i < digits.size(); i++)
        {
            int diff = digits[i] - borrow;
            if (i < other.digits.size())
                diff -= other.digits[i];
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
                borrow = 0;
            result.digits.push_back(diff);
        }
        result.removeLeadingZeros();
        return result;
    }
    int compare(const BigInteger &other, bool considerSign = true) const
    {
        if (considerSign && isNegative != other.isNegative)
            return isNegative ? -1 : 1;
        if (digits.size() != other.digits.size())
            if (!considerSign && isNegative && other.isNegative)
                return digits.size() > other.digits.size() ? -1 : 1;
            else
                return digits.size() > other.digits.size() ? 1 : -1;
        for (int i = digits.size() - 1; i >= 0; i--)
            if (digits[i] != other.digits[i])
                if (!considerSign && isNegative && other.isNegative)
                    return digits[i] > other.digits[i] ? -1 : 1;
                else
                    return digits[i] > other.digits[i] ? 1 : -1;
        return 0; // 相等
    }
    BigInteger operator*(const int num) const
    {
        if (num == 0 || (*this == BigInteger(0)))
            return BigInteger(0);
        BigInteger result;
        result.digits.clear();
        int carry = 0;
        int absNum = abs(num);
        for (size_t i = 0; i < digits.size() || carry; i++)
        {
            int prod = carry;
            if (i < digits.size())
                prod += digits[i] * absNum;

            result.digits.push_back(prod % 10);
            carry = prod / 10;
        }
        result.isNegative = isNegative ^ (num < 0);
        result.removeLeadingZeros();
        return result;
    }
    BigInteger operator*(const BigInteger &other) const
    {
        if (*this == BigInteger(0) || other == BigInteger(0))
            return BigInteger(0);
        BigInteger result;
        result.digits.resize(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); i++)
        {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; j++)
            {
                long long curr = result.digits[i + j] + carry;
                if (j < other.digits.size())
                    curr += (long long)digits[i] * other.digits[j];
                result.digits[i + j] = curr % 10;
                carry = curr / 10;
            }
        }
        result.isNegative = isNegative ^ other.isNegative;
        result.removeLeadingZeros();
        return result;
    }
    BigInteger pow(int exponent) const
    {
        if (exponent < 0)
            throw std::invalid_argument("Negative exponent not supported for BigInteger");
        if (exponent == 0)
            return BigInteger(1);
        if (exponent == 1)
            return *this;
        BigInteger result(1);
        BigInteger base = *this;
        while (exponent >>= 1)
        {
            if (exponent & 1)
                result = result * base;
            base = base * base;
        }
        return result;
    }
    static BigInteger factorial(const BigInteger &n)
    {
        if (n.isNegative)
        {
            throw std::invalid_argument("Factorial not defined for negative numbers");
        }
        if (n == BigInteger(0) || n == BigInteger(1))
            return BigInteger(1);
        BigInteger result(1);
        BigInteger i(2);
        while (i <= n)
        {
            result = result * i;
            i = i + BigInteger(1);
        }
        return result;
    }
    static BigInteger factorial(int n)
    {
        if (n < 0)
        {
            throw std::invalid_argument("Factorial not defined for negative numbers");
        }
        return factorial(BigInteger(n));
    }
    BigInteger divideByInt(const int divisor) const
    {
        if (divisor == 0)
            throw std::invalid_argument("Division by zero");
        BigInteger result;
        result.digits.clear();
        result.isNegative = isNegative ^ (divisor < 0);
        int absDivisor = abs(divisor);
        long long remainder = 0;
        std::vector<int> quotient;
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            remainder = remainder * 10 + digits[i];
            quotient.push_back(remainder / absDivisor);
            remainder %= absDivisor;
        }
        std::reverse(quotient.begin(), quotient.end());
        result.digits = quotient;
        result.removeLeadingZeros();
        return result;
    }
    // 高精度除高精度（整除）
    std::pair<BigInteger, BigInteger> divideAndRemainder(const BigInteger &divisor) const
    {
        if (divisor == BigInteger(0))
            throw std::invalid_argument("Division by zero");
        if (*this == BigInteger(0))
            return {BigInteger(0), BigInteger(0)};
        BigInteger absDividend = *this;
        BigInteger absDivisor = divisor;
        absDividend.isNegative = false;
        absDivisor.isNegative = false;
        if (absDividend < absDivisor)
            return {BigInteger(0), *this};
        BigInteger quotient;
        BigInteger remainder;
        quotient.digits.clear();
        remainder.digits.clear();
        remainder.isNegative = false;
        std::vector<int> reversedDividendDigits = digits;
        std::reverse(reversedDividendDigits.begin(), reversedDividendDigits.end());
        for (size_t i = 0; i < reversedDividendDigits.size(); i++)
        {
            remainder.digits.insert(remainder.digits.begin(), reversedDividendDigits[i]);
            remainder.removeLeadingZeros();
            int q = 0;
            BigInteger temp = absDivisor;
            while (temp <= remainder)
            {
                remainder = remainder - temp;
                q++;
            }
            quotient.digits.insert(quotient.digits.begin(), q);
        }
        quotient.isNegative = isNegative ^ divisor.isNegative;
        quotient.removeLeadingZeros();
        remainder.isNegative = isNegative;
        remainder.removeLeadingZeros();
        return {quotient, remainder};
    }
    BigInteger operator/(const int divisor) const
    {
        return divideByInt(divisor);
    }
    BigInteger operator/(const BigInteger &divisor) const
    {
        return divideAndRemainder(divisor).first;
    }
    int operator%(const int divisor) const
    {
        if (divisor == 0)
            throw std::invalid_argument("Division by zero");
        long long remainder = 0;
        int absDivisor = abs(divisor);
        for (int i = digits.size() - 1; i >= 0; i--)
            remainder = (remainder * 10 + digits[i]) % absDivisor;
        if (isNegative)
            remainder = -remainder;
        return remainder;
    }
    BigInteger operator%(const BigInteger &divisor) const
    {
        return divideAndRemainder(divisor).second;
    }
    std::string divideWithPrecision(const BigInteger &divisor, int precision = 10) const
    {
        if (divisor == BigInteger(0))
            throw std::invalid_argument("Division by zero");
        auto divmod = divideAndRemainder(divisor);
        BigInteger integerPart = divmod.first;
        BigInteger remainder = divmod.second;
        std::stringstream result;
        result << integerPart;
        if (remainder == BigInteger(0))
            return result.str();
        result << ".";
        BigInteger absDivisor = divisor;
        absDivisor.isNegative = false;
        for (int i = 0; i < precision && remainder != BigInteger(0); i++)
        {
            remainder = remainder * 10;
            auto divmod = remainder.divideAndRemainder(absDivisor);
            int digit = 0;
            if (divmod.first.digits.size() > 0)
                digit = divmod.first.digits[0];
            result << digit;
            remainder = divmod.second;
        }
        return result.str();
    }
};