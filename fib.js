#!/usr/bin/env jjs
var x1 = $ARG[0];
print("Hi, " + $ENV.USER);

function fibonaci(x) {
	if (x == 1) {
		return 1;
	}
	if (x < 0) {
		return 0;
	}
	return fibonaci(x - 1) + fibonaci(x - 2);
}

print(fibonaci(x1));
