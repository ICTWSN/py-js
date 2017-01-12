// built-in functions

r = Math.rand();
var a = 2.1, b = 2.6, c = -2.1, d = -2.6, e = 3.0;

result = Math.round(a) == 2 && Math.ceil(a) == 3 && Math.floor(a) == 2 
	&& Math.round(b) == 3 && Math.ceil(b) == 3 && Math.floor(b) == 2
	&& Math.round(c) == -2 && Math.ceil(c) == -2 && Math.floor(c) == -3
	&& Math.round(d) == -3 && Math.ceil(d) == -2 && Math.floor(d) == -3
	&& Math.round(e) == 3 && Math.ceil(e) == 3 && Math.floor(e) == 3;