// test for string function
var a = " diff  ";
var b = a.trim();
var c = b.toUpperCase();
var d = c.toLowerCase();
var e = a.localeCompare(b);
var f = a.trimLeft();
var g = a.trimRight();
result = a == " diff  " && b == "diff" && c == "DIFF" && d == "diff" && e == -1 && f == "diff  "
			&& g == " diff";
