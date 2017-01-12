#include "PyJS.h"
#include "PyJS_Functions.h"
#include <assert.h>
#include <stdio.h>


//const char *code = "var a = 5; if (a==5) a=4; else a=3;";
//const char *code = "{ var a = 4; var b = 1; while (a>0) { b = b * 2; a = a - 1; } var c = 5; }";
//const char *code = "{ var b = 1; for (var i=0;i<4;i=i+1) b = b * 2; }";
//const char *code = "function myfunc(x, y) { return x + y; } var a = myfunc(1,2); print(a);";

void js_print(CScriptVar *v, void *userdata) {
    printf("> %s\n", v->getParameter("text")->getString().c_str());
}

void js_dump(CScriptVar *v, void *userdata) {
    CPyJS *js = (CPyJS*)userdata;
    js->root->trace(">  ");
}

int main(int argc, char **argv)
{
  CPyJS *js = new CPyJS();
  /* add the functions from TinyJS_Functions.cpp */
  registerFunctions(js);
  /* Add a native function */
  js->addNative("function print(text)", &js_print, 0);
  js->addNative("function dump()", &js_dump, js);
  /* Execute out bit of code - we could call 'evaluate' here if
     we wanted something returned */
  try {
    js->execute("var lets_quit = 0; function quit() { lets_quit = 1; }");
    js->execute("print(\"Interactive mode... Type quit(); to exit, or print(...); to print something, or dump() to dump the symbol table!\");");
  } catch (CScriptException *e) {
    printf("ERROR: %s\n", e->text.c_str());
  }

  while (js->evaluate("lets_quit") == "0") {
    char buffer[2048];
    fgets ( buffer, sizeof(buffer), stdin );
    try {
      js->execute(buffer);
    } catch (CScriptException *e) {
      printf("ERROR: %s\n", e->text.c_str());
    }
  }
  delete js;
#ifdef _WIN32
#ifdef _DEBUG
  _CrtDumpMemoryLeaks();
#endif
#endif
  return 0;
}
