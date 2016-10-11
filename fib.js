#!/usr/bin/env jjs
var num = 7;
print("Hello, username!");

function fibonaci(x) {
	if (x == 1) {
		return 1;
	}
	if (x < 0) {
		return 0;
	}
	return fibonaci(x - 1) + fibonaci(x - 2);
}

print(fibonaci(num));
