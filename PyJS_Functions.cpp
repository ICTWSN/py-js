#include "PyJS_Functions.h"
#include <math.h>
#include <cstdlib>
#include <sstream>
#include <algorithm>

#ifndef NO_REGEXP 
#	if defined HAVE_TR1_REGEX
#		include <tr1/regex>
		using namespace std::tr1;
#	elif defined HAVE_BOOST_REGEX
#		include <boost/regex.hpp>
		using namespace boost;
#	else
#		include <regex>
#	endif
#endif

using namespace std;
// ----------------------------------------------- Actual Functions
void scTrace(CScriptVar *c, void *userdata) {
    CPyJS *js = (CPyJS*)userdata;
    js->root->trace();
}

void scObjectDump(CScriptVar *c, void *) {
    c->getParameter("this")->trace("> ");
}

void scObjectClone(CScriptVar *c, void *) {
    CScriptVar *obj = c->getParameter("this");
    c->getReturnVar()->copyValue(obj);
}

void scMathRand(CScriptVar *c, void *) {
    c->getReturnVar()->setDouble((double)rand()/RAND_MAX);
}

void scMathRandInt(CScriptVar *c, void *) {
    int min = c->getParameter("min")->getInt();
    int max = c->getParameter("max")->getInt();
    int val = min + (int)(rand()%(1+max-min));
    c->getReturnVar()->setInt(val);
}

void scCharToInt(CScriptVar *c, void *) {
    string str = c->getParameter("ch")->getString();;
    int val = 0;
    if (str.length()>0)
        val = (int)str.c_str()[0];
    c->getReturnVar()->setInt(val);
}

void scStringIndexOf(CScriptVar *c, void *) {
    string str = c->getParameter("this")->getString();
    string search = c->getParameter("search")->getString();
    size_t p = str.find(search);
    int val = (p==string::npos) ? -1 : p;
    c->getReturnVar()->setInt(val);
}

void scStringSlice(CScriptVar *c, void *) {
    string str = c->getParameter("this")->getString();
    int start = c->getParameter("start")->getInt();
	int end = c->getParameter("end")->getInt();
	if(end<0) end = str.length() + end;
	int length = end-start;
    if (length>0 && start>=0 && start+length<=(int)str.length())
		c->getReturnVar()->setString(str.substr(start, length));
    else
		c->getReturnVar()->setString("");
}

void scStringSubstr(CScriptVar *c, void *){
	string str = c->getParameter("this")->getString();
	int length = c->getParameter("length")->getInt();
	int start = c->getParameter("start")->getInt();

	if (length>0 && start>=0 && start+length<=(int)str.length())
		c->getReturnVar()->setString(str.substr(start, length));
    else
		c->getReturnVar()->setString("");
}

void scStringSubstring(CScriptVar *c, void *) {
    string str = c->getParameter("this")->getString();
    int start = c->getParameter("start")->getInt();
    int end = c->getParameter("end")->getInt();
	if(end<0) end = 0;
	if(end<start){
		int temp = end;
		end = start;
		start = temp;
	}
    int length = end-start;
    if (length>0 && start>=0 && start+length<=(int)str.length())
		c->getReturnVar()->setString(str.substr(start, length));
    else
		c->getReturnVar()->setString("");
}

void scStringCharAt(CScriptVar *c, void *) {
    string str = c->getParameter("this")->getString();
    int p = c->getParameter("pos")->getInt();
    if (p>=0 && p<(int)str.length())
      c->getReturnVar()->setString(str.substr(p, 1));
    else
      c->getReturnVar()->setString("");
}

void scStringCharCodeAt(CScriptVar *c, void *) {
    string str = c->getParameter("this")->getString();
    int p = c->getParameter("pos")->getInt();
    if (p>=0 && p<(int)str.length())
      c->getReturnVar()->setInt(str.at(p));
    else
      c->getReturnVar()->setInt(0);
}

void scStringSplit(CScriptVar *c, void *) {
    string str = c->getParameter("this")->getString();
    string sep = c->getParameter("separator")->getString();
    CScriptVar *result = c->getReturnVar();
    result->setArray();
    int length = 0;

    size_t pos = str.find(sep);
    while (pos != string::npos) {
      result->setArrayIndex(length++, new CScriptVar(str.substr(0,pos)));
      str = str.substr(pos+1);
      pos = str.find(sep);
    }

    if (str.size()>0)
      result->setArrayIndex(length++, new CScriptVar(str));
}

void scStringFromCharCode(CScriptVar *c, void *) {
    char str[2];
    str[0] = c->getParameter("char")->getInt();
    str[1] = 0;
    c->getReturnVar()->setString(str);
}

void scStringToLowerCase(CScriptVar *c, void *) {
	string str = c->getParameter("this")->getString();
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	c->getReturnVar()->setString(str);
}

void scStringToUpperCase(CScriptVar *c, void *) {
	string str = c->getParameter("this")->getString();
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	c->getReturnVar()->setString(str);
}

void scStringTrim(CScriptVar *c, void *userdata) {
	string str = c->getParameter("this")->getString();
	string::size_type start = 0;
	string::size_type end = string::npos;
	if((((int)userdata) & 2) == 0) {
		start = str.find_first_not_of(" \t\r\n");
		if(start == string::npos) start = 0;
	}
	if((((int)userdata) & 1) == 0) {
		end = str.find_last_not_of(" \t\r\n");
		if(end != string::npos) end = 1+end-start;
	}
	c->getReturnVar()->setString(str.substr(start,end));
}

void scStringLocaleCompare(CScriptVar *c, void *userdata) {
	string str = c->getParameter("this")->getString();
	string compareString = c->getParameter("compareString")->getString();
	int val = 0;
	if(str<compareString) val = -1;
	else if(str>compareString) val = 1;
	c->getReturnVar()->setInt(val);
}

void scStringQuote(CScriptVar *c, void *userdata) {
	string str = c->getParameter("this")->getString();
	c->getReturnVar()->setString(getJSString(str));
}

void scIntegerParseInt(CScriptVar *c, void *) {
    string str = c->getParameter("str")->getString();
    int val = strtol(str.c_str(),0,0);
    c->getReturnVar()->setInt(val);
}

void scIntegerValueOf(CScriptVar *c, void *) {
    string str = c->getParameter("str")->getString();

    int val = 0;
    if (str.length()==1)
      val = str[0];
    c->getReturnVar()->setInt(val);
}

void scJSONStringify(CScriptVar *c, void *) {
    std::ostringstream result;
    c->getParameter("obj")->getJSON(result);
    c->getReturnVar()->setString(result.str());
}

void scExec(CScriptVar *c, void *data) {
    CPyJS *pyJS = (CPyJS *)data;
    std::string str = c->getParameter("jsCode")->getString();
    pyJS->execute(str);
}

void scEval(CScriptVar *c, void *data) {
    CPyJS *pyJS = (CPyJS *)data;
    std::string str = c->getParameter("jsCode")->getString();
    c->setReturnVar(pyJS->evaluateComplex(str).var);
}

void scArrayContains(CScriptVar *c, void *data) {
  CScriptVar *obj = c->getParameter("obj");
  CScriptVarLink *v = c->getParameter("this")->firstChild;

  bool contains = false;
  while (v) {
      if (v->var->equals(obj)) {
        contains = true;
        break;
      }
      v = v->nextSibling;
  }

  c->getReturnVar()->setInt(contains);
}

void scArrayRemove(CScriptVar *c, void *data) {
  CScriptVar *obj = c->getParameter("obj");
  vector<int> removedIndices;
  CScriptVarLink *v;
  // remove
  v = c->getParameter("this")->firstChild;
  while (v) {
      if (v->var->equals(obj)) {
        removedIndices.push_back(v->getIntName());
      }
      v = v->nextSibling;
  }
  // renumber
  v = c->getParameter("this")->firstChild;
  while (v) {
      int n = v->getIntName();
      int newn = n;
      for (size_t i=0;i<removedIndices.size();i++)
        if (n>=removedIndices[i])
          newn--;
      if (newn!=n)
        v->setIntName(newn);
      v = v->nextSibling;
  }
}

void scArrayJoin(CScriptVar *c, void *data) {
  string sep = c->getParameter("separator")->getString();
  CScriptVar *arr = c->getParameter("this");

  ostringstream sstr;
  int l = arr->getArrayLength();
  for (int i=0;i<l;i++) {
    if (i>0) sstr << sep;
    sstr << arr->getArrayIndex(i)->getString();
  }

  c->getReturnVar()->setString(sstr.str());
}

// ----------------------------------------------- Register Functions
void registerFunctions(CPyJS *pyJS) {
    pyJS->addNative("function exec(jsCode)", scExec, pyJS); // execute the given code
    pyJS->addNative("function eval(jsCode)", scEval, pyJS); // execute the given string (an expression) and return the result
    pyJS->addNative("function trace()", scTrace, pyJS);

    pyJS->addNative("function Object.dump()", scObjectDump, 0);
    pyJS->addNative("function Object.clone()", scObjectClone, 0);

    pyJS->addNative("function Math.rand()", scMathRand, 0);
    pyJS->addNative("function Math.randInt(min, max)", scMathRandInt, 0);

    pyJS->addNative("function charToInt(ch)", scCharToInt, 0); //  convert a character to an int - get its value
	// slice
	pyJS->addNative("function String.prototype.slice(start,end)", scStringSlice, 0); // find the last position of a string in a string, -1 if not
	pyJS->addNative("function String.slice(start,end)", scStringSlice, (void*)1); // find the last position of a string in a string, -1 if not
	// substr
	pyJS->addNative("function String.prototype.substr(start,length)", scStringSubstr, 0);
	pyJS->addNative("function String.substr(start,length)", scStringSubstr, (void*)1);
	// substring
	pyJS->addNative("function String.prototype.substring(start,end)", scStringSubstring, (void*)2);
	pyJS->addNative("function String.substring(start,end)", scStringSubstring, (void*)3);
	//fromCharCode
    pyJS->addNative("function String.fromCharCode(char)", scStringFromCharCode, 0);
	pyJS->addNative("function String.prototype.fromCharCode(char)", scStringFromCharCode, 0);
	// charAt
	pyJS->addNative("function String.prototype.charAt(pos)", scStringCharAt, 0);
	pyJS->addNative("function String.charAt(pos)", scStringCharAt, 0);
	// charCodeAt
	pyJS->addNative("function String.prototype.charCodeAt(pos)", scStringCharCodeAt, 0);
	pyJS->addNative("function String.charCodeAt(pos)", scStringCharCodeAt, 0);
	// concat
	//pyJS->addNative("function String.prototype.concat()", scStringConcat, 0);
	//pyJS->addNative("function String.concat(this)", scStringConcat, (void*)1);
	// indexOf
	pyJS->addNative("function String.prototype.indexOf(search)", scStringIndexOf, 0); // find the position of a string in a string, -1 if not
	pyJS->addNative("function String.indexOf(search)", scStringIndexOf, 0); // find the position of a string in a string, -1 if not
	// lastIndexOf
	pyJS->addNative("function String.prototype.lastIndexOf(search)", scStringIndexOf, (void*)-1); // find the last position of a string in a string, -1 if not
	pyJS->addNative("function String.lastIndexOf(search)", scStringIndexOf, (void*)-1); // find the last position of a string in a string, -1 if not
	// split
	pyJS->addNative("function String.prototype.split(separator)", scStringSplit, 0);
	pyJS->addNative("function String.split(separator)", scStringSplit, 0);
	//Add some string functions here
	// toLowerCase toLocaleLowerCase currently the same function
	pyJS->addNative("function String.prototype.toLowerCase()", scStringToLowerCase, 0);
	pyJS->addNative("function String.toLowerCase()", scStringToLowerCase, 0);
	pyJS->addNative("function String.prototype.toLocaleLowerCase()", scStringToLowerCase, 0);
	pyJS->addNative("function String.toLocaleLowerCase()", scStringToLowerCase, 0);
	// toUpperCase toLocaleUpperCase currently the same function
	pyJS->addNative("function String.prototype.toUpperCase()", scStringToUpperCase, 0);
	pyJS->addNative("function String.toUpperCase()", scStringToUpperCase, 0);
	pyJS->addNative("function String.prototype.toLocaleUpperCase()", scStringToUpperCase, 0);
	pyJS->addNative("function String.toLocaleUpperCase()", scStringToUpperCase, 0);
	// trim
	pyJS->addNative("function String.prototype.trim()", scStringTrim, 0);
	pyJS->addNative("function String.trim()", scStringTrim, 0);
	// trimLeft
	pyJS->addNative("function String.prototype.trimLeft()", scStringTrim, (void*)1);
	pyJS->addNative("function String.trimLeft()", scStringTrim, (void*)1);
	// trimRight
	pyJS->addNative("function String.prototype.trimRight()", scStringTrim, (void*)2);
	pyJS->addNative("function String.trimRight()", scStringTrim, (void*)2);
	// localeCompare
	pyJS->addNative("function String.prototype.localeCompare(compareString)", scStringLocaleCompare, 0);
	pyJS->addNative("function String.localeCompare(compareString)", scStringLocaleCompare, 0);
	// quote
	pyJS->addNative("function String.prototype.quote()", scStringQuote, 0);
	pyJS->addNative("function String.quote()", scStringQuote, 0);

    pyJS->addNative("function Integer.parseInt(str)", scIntegerParseInt, 0); // string to int
    pyJS->addNative("function Integer.valueOf(str)", scIntegerValueOf, 0); // value of a single character
    pyJS->addNative("function JSON.stringify(obj, replacer)", scJSONStringify, 0); // convert to JSON. replacer is ignored at the moment
    // JSON.parse is left out as you can (unsafely!) use eval instead
    pyJS->addNative("function Array.contains(obj)", scArrayContains, 0);
    pyJS->addNative("function Array.remove(obj)", scArrayRemove, 0);
    pyJS->addNative("function Array.join(separator)", scArrayJoin, 0);
}

