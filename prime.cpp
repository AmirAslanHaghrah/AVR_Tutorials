#include <iostream>
#define N 20
bool isPrime(int num);
int main() {
	int primes[N] = { 0 };
	int n = 0;
	int i = 2;
	while (n < N) {
		if (isPrime(i)) {
			primes[n] = i;
			n++;
		}
		i++;
	}
	for (int i = 0; i < N; i++) {
		std::cout << primes[i] << "\n";
	}
	system("pause");
	return 0;
}
bool isPrime(int num) {
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}
