// test for string slice
var a = "HelloWorld!";
var b = a.slice(3,-2);
var c = a.slice(5,10);
var d = a.slice(5,3);
var b1 = a.substring(5,10);
var c1 = a.substring(5,3);
var d1 = a.substring(3,-2);
result = b == "loWorl" && c == "World" && d == ""
		&& b1 == "World" && c1 == "lo" && d1 == "Hel";
