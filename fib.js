#!/usr/bin/env jjs
var num = 7;
print("Hello, username!");

function fibonaci(x) {
	function _fib(n, a, b) {
		if (n == 0) {
			return a;
		}
		return (n - 1, b, a + b);
	}
	return _fib(x, 0, 1);
}

print(fibonaci(num));
