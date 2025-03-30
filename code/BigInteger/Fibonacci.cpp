// #include <iostream>
// #include <vector>
// Matrix structure for 2x2 matrices
struct Matrix
{
    long long a, b, c, d;

    Matrix(long long a = 1, long long b = 0, long long c = 0, long long d = 1)
        : a(a), b(b), c(c), d(d) {}
    Matrix operator*(const Matrix &other) const
    {
        return Matrix(
            a * other.a + b * other.c,
            a * other.b + b * other.d,
            c * other.a + d * other.c,
            c * other.b + d * other.d);
    }
};
Matrix matrix_power(Matrix base, long long exponent)
{
    Matrix result(1, 0, 0, 1); // Identity matrix
    while (exponent > 0)
    {
        if (exponent & 1)
            result = result * base;
        base = base * base;
        exponent >>= 1;
    }
    return result;
}
long long fibonacci(long long n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    Matrix base(1, 1, 1, 0);
    Matrix result = matrix_power(base, n - 1);
    return result.a;
}