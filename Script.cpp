/*
 * This is a simple program showing how to use PyJS
 */

#include "PyJS.h"
#include <assert.h>
#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
#	ifndef _MSC_VER
#		define DEBUG_MEMORY 1
#	endif
#endif

const char *code = "function myfunc(x, y) { return x + y; } var a = myfunc(1,2); print(a);";

void js_print(const CFunctionsScopePtr &v, void *) {
	printf("> %s\n", v->getArgument("text")->toString().c_str());
}

void js_dump(const CFunctionsScopePtr &v, void *) {
	v->getContext()->getRoot()->trace(">  ");
}


char *topOfStack;
#define sizeOfStack 1*1024*1024 /* for example 1 MB depend of Compiler-Options */
#define sizeOfSafeStack 50*1024 /* safety area */

int main(int , char **)
{
	char dummy;
	topOfStack = &dummy;
//	printf("%i %i\n", __cplusplus, _MSC_VER);

//	printf("Locale:%s\n",setlocale( LC_ALL, 0 ));
//	setlocale( LC_ALL, ".858" );
//	printf("Locale:%s\n",setlocale( LC_ALL, 0 ));
	CPyJS *js = new CPyJS();
	/* add the functions from TinyJS_Functions.cpp */
//	registerFunctions(js);
//	registerStringFunctions(js);
//	registerMathFunctions(js);
	/* Add a native function */
	js->addNative("function print(text)", &js_print, 0);
//  js->addNative("function dump()", &js_dump, js);
	/* Execute out bit of code - we could call 'evaluate' here if
		we wanted something returned */
	js->setStackBase(topOfStack-(sizeOfStack-sizeOfSafeStack));
	try {
		js->execute("var lets_quit = 0; function quit() { lets_quit = 1; }");
		js->execute("print(\"Interactive mode... Type quit(); to exit, or print(...); to print something, or dump() to dump the symbol table!\");");
		js->execute("print(function () {print(\"gen\");yield 5;yield 6;}().next());", "yield-test.js");
		js->execute("for each(i in function () {print(\"gen\");yield 5;yield 6;}()) print(i);", "yield-test.js");
		js->execute("function g(){				\n\n"
			"	throw \"error\"\n"
			"	try{									\n"
			"		yield 1; yield 2				\n"
			"	}finally{							\n"
			"		print(\"finally\")			\n"
			"		yield 3;							\n"
			"		throw StopIteration			\n"
			"	}										\n"
			"	print(\"after finally\")		\n"
			"}t=g()", "test");
	} catch (CScriptException *e) {
		printf("%s\n", e->toString().c_str());
		delete e;
	}
	int lineNumber = 0;
	while (js->evaluate("lets_quit") == "0") {
		std::string buffer;
		if(!std::getline(std::cin, buffer)) break;
		try {
			js->execute(buffer, "console.input", lineNumber++);
		} catch (CScriptException *e) {
			printf("%s\n", e->toString().c_str());
			delete e;
		}
	}
	delete js;
#ifdef _WIN32
#ifdef _DEBUG
//  _CrtDumpMemoryLeaks();
/*
	no dump momoryleaks here
	_CrtSetDbgFlag(..) force dump memoryleake after call of all global deconstructors
*/
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
#endif
	return 0;
}
