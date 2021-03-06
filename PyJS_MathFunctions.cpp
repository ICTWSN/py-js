#include <math.h>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include "PyJS_MathFunctions.h"

using namespace std;

#define k_E                 exp(1.0)
#define k_PI                3.1415926535897932384626433832795

#define F_ABS(a)            ((a)>=0 ? (a) : (-(a)))
#define F_MIN(a,b)          ((a)>(b) ? (b) : (a))
#define F_MAX(a,b)          ((a)>(b) ? (a) : (b))
#define F_SGN(a)            ((a)>0 ? 1 : ((a)<0 ? -1 : 0 ))
#define F_RNG(a,min,max)    ((a)<(min) ? min : ((a)>(max) ? max : a ))
#define F_ROUND(a)          ((a)>0 ? (int) ((a)+0.5) : (int) ((a)-0.5) )
#define F_CEIL(a)           ceil(a)
#define F_FLOOR(a)          floor(a)
 
//CScriptVar shortcut macro
#define scIsInt(a)          ( c->getParameter(a)->isInt() )
#define scIsDouble(a)       ( c->getParameter(a)->isDouble() )  
#define scGetInt(a)         ( c->getParameter(a)->getInt() )
#define scGetDouble(a)      ( c->getParameter(a)->getDouble() )  
#define scReturnInt(a)      ( c->getReturnVar()->setInt(a) )
#define scReturnDouble(a)   ( c->getReturnVar()->setDouble(a) )  

#ifdef _MSC_VER
namespace
{
    double asinh( const double &value )
    {
        double returned;

        if(value>0)
        returned = log(value + sqrt(value * value + 1));
        else
        returned = -log(-value + sqrt(value * value + 1));

        return(returned);
    }

    double acosh( const double &value )
    {
        double returned;

        if(value>0)
        returned = log(value + sqrt(value * value - 1));
        else
        returned = -log(-value + sqrt(value * value - 1));

        return(returned);
    }
}
#endif

//Math.abs(x) - returns absolute of given value
void scMathAbs(CScriptVar *c, void *userdata) {
    if ( scIsInt("a") ) {
      scReturnInt( F_ABS( scGetInt("a") ) );
    } else if ( scIsDouble("a") ) {
      scReturnDouble( F_ABS( scGetDouble("a") ) );
    }
}

//Math.round(a) - returns nearest round of given value
void scMathRound(CScriptVar *c, void *userdata) {
    if ( scIsInt("a") ) {
      scReturnInt( F_ROUND( scGetInt("a") ) );
    } else if ( scIsDouble("a") ) {
      scReturnDouble( F_ROUND( scGetDouble("a") ) );
    }
}

//Math.ceil(a) - returns nearest round of given value
void scMathCeil(CScriptVar *c, void *userdata) {
	if ( scIsInt("a") ) {
		scReturnInt( F_CEIL( scGetInt("a") ) );
    } else if ( scIsDouble("a") ) {
		scReturnDouble( F_CEIL( scGetDouble("a") ) );
    }
}

//Math.floor(a) - returns nearest round of given value
void scMathFloor(CScriptVar *c, void *userdata) {
	if ( scIsInt("a") ) {
		scReturnInt( F_FLOOR( scGetInt("a") ) );
    } else if ( scIsDouble("a") ) {
		scReturnDouble( F_FLOOR( scGetDouble("a") ) );
    }
}

//Math.min(a,b) - returns minimum of two given values 
void scMathMin(CScriptVar *c, void *userdata) {
    if ( (scIsInt("a")) && (scIsInt("b")) ) {
      scReturnInt( F_MIN( scGetInt("a"), scGetInt("b") ) );
    } else {
      scReturnDouble( F_MIN( scGetDouble("a"), scGetDouble("b") ) );
    }
}

//Math.max(a,b) - returns maximum of two given values  
void scMathMax(CScriptVar *c, void *userdata) {
    if ( (scIsInt("a")) && (scIsInt("b")) ) {
      scReturnInt( F_MAX( scGetInt("a"), scGetInt("b") ) );
    } else {
      scReturnDouble( F_MAX( scGetDouble("a"), scGetDouble("b") ) );
    }
}

//Math.range(x,a,b) - returns value limited between two given values  
void scMathRange(CScriptVar *c, void *userdata) {
    if ( (scIsInt("x")) ) {
      scReturnInt( F_RNG( scGetInt("x"), scGetInt("a"), scGetInt("b") ) );
    } else {
      scReturnDouble( F_RNG( scGetDouble("x"), scGetDouble("a"), scGetDouble("b") ) );
    }
}

//Math.sign(a) - returns sign of given value (-1==negative,0=zero,1=positive)
void scMathSign(CScriptVar *c, void *userdata) {
    if ( scIsInt("a") ) {
      scReturnInt( F_SGN( scGetInt("a") ) );
    } else if ( scIsDouble("a") ) {
      scReturnDouble( F_SGN( scGetDouble("a") ) );
    }
}

void scMathRandom(CScriptVar *c, void *) {
	static int inited=0;
	if(!inited) {
		inited = 1;
		srand((unsigned int)time(NULL));
	}
	scReturnDouble(double(rand())/RAND_MAX);
}

//Math.PI() - returns PI value
void scMathPI(CScriptVar *c, void *userdata) {
    scReturnDouble(k_PI);
}

//Math.toDegrees(a) - returns degree value of a given angle in radians
void scMathToDegrees(CScriptVar *c, void *userdata) {
    scReturnDouble( (180.0/k_PI)*( scGetDouble("a") ) );
}

//Math.toRadians(a) - returns radians value of a given angle in degrees
void scMathToRadians(CScriptVar *c, void *userdata) {
    scReturnDouble( (k_PI/180.0)*( scGetDouble("a") ) );
}

//Math.sin(a) - returns trig. sine of given angle in radians
void scMathSin(CScriptVar *c, void *userdata) {
    scReturnDouble( sin( scGetDouble("a") ) );
}

//Math.asin(a) - returns trig. arcsine of given angle in radians
void scMathASin(CScriptVar *c, void *userdata) {
    scReturnDouble( asin( scGetDouble("a") ) );
}

//Math.cos(a) - returns trig. cosine of given angle in radians
void scMathCos(CScriptVar *c, void *userdata) {
    scReturnDouble( cos( scGetDouble("a") ) );
}

//Math.acos(a) - returns trig. arccosine of given angle in radians
void scMathACos(CScriptVar *c, void *userdata) {
    scReturnDouble( acos( scGetDouble("a") ) );
}

//Math.tan(a) - returns trig. tangent of given angle in radians
void scMathTan(CScriptVar *c, void *userdata) {
    scReturnDouble( tan( scGetDouble("a") ) );
}

//Math.atan(a) - returns trig. arctangent of given angle in radians
void scMathATan(CScriptVar *c, void *userdata) {
    scReturnDouble( atan( scGetDouble("a") ) );
}

//Math.sinh(a) - returns trig. hyperbolic sine of given angle in radians
void scMathSinh(CScriptVar *c, void *userdata) {
    scReturnDouble( sinh( scGetDouble("a") ) );
}

//Math.asinh(a) - returns trig. hyperbolic arcsine of given angle in radians
void scMathASinh(CScriptVar *c, void *userdata) {
    scReturnDouble( asinh( scGetDouble("a") ) );
}

//Math.cosh(a) - returns trig. hyperbolic cosine of given angle in radians
void scMathCosh(CScriptVar *c, void *userdata) {
    scReturnDouble( cosh( scGetDouble("a") ) );
}

//Math.acosh(a) - returns trig. hyperbolic arccosine of given angle in radians
void scMathACosh(CScriptVar *c, void *userdata) {
    scReturnDouble( acosh( scGetDouble("a") ) );
}

//Math.tanh(a) - returns trig. hyperbolic tangent of given angle in radians
void scMathTanh(CScriptVar *c, void *userdata) {
    scReturnDouble( tanh( scGetDouble("a") ) );
}

//Math.atan(a) - returns trig. hyperbolic arctangent of given angle in radians
void scMathATanh(CScriptVar *c, void *userdata) {
    scReturnDouble( atan( scGetDouble("a") ) );
}

//Math.E() - returns E Neplero value
void scMathE(CScriptVar *c, void *userdata) {
    scReturnDouble(k_E);
}

//Math.log(a) - returns natural logaritm (base E) of given value
void scMathLog(CScriptVar *c, void *userdata) {
    scReturnDouble( log( scGetDouble("a") ) );
}

//Math.log10(a) - returns logaritm(base 10) of given value
void scMathLog10(CScriptVar *c, void *userdata) {
    scReturnDouble( log10( scGetDouble("a") ) );
}

//Math.exp(a) - returns e raised to the power of a given number
void scMathExp(CScriptVar *c, void *userdata) {
    scReturnDouble( exp( scGetDouble("a") ) );
}

//Math.pow(a,b) - returns the result of a number raised to a power (a)^(b)
void scMathPow(CScriptVar *c, void *userdata) {
    scReturnDouble( pow( scGetDouble("a"), scGetDouble("b") ) );
}

//Math.sqr(a) - returns square of given value
void scMathSqr(CScriptVar *c, void *userdata) {
    scReturnDouble( ( scGetDouble("a") * scGetDouble("a") ) );
}

//Math.sqrt(a) - returns square root of given value
void scMathSqrt(CScriptVar *c, void *userdata) {
    scReturnDouble( sqrtf( scGetDouble("a") ) );
}

// ----------------------------------------------- Register Functions
void registerMathFunctions(CPyJS *PyJS) {
     
    // --- Math and Trigonometry functions ---
    PyJS->addNative("function Math.abs(a)", scMathAbs, 0);
    PyJS->addNative("function Math.round(a)", scMathRound, 0);
	PyJS->addNative("function Math.ceil(a)", scMathCeil, 0);
	PyJS->addNative("function Math.floor(a)", scMathFloor, 0);
    PyJS->addNative("function Math.min(a,b)", scMathMin, 0);
    PyJS->addNative("function Math.max(a,b)", scMathMax, 0);
    PyJS->addNative("function Math.range(x,a,b)", scMathRange, 0);
    PyJS->addNative("function Math.sign(a)", scMathSign, 0);
	PyJS->addNative("function Math.random(a)", scMathRandom, 0);
    
    PyJS->addNative("function Math.PI()", scMathPI, 0);
    PyJS->addNative("function Math.toDegrees(a)", scMathToDegrees, 0);
    PyJS->addNative("function Math.toRadians(a)", scMathToRadians, 0);
    PyJS->addNative("function Math.sin(a)", scMathSin, 0);
    PyJS->addNative("function Math.asin(a)", scMathASin, 0);
    PyJS->addNative("function Math.cos(a)", scMathCos, 0);
    PyJS->addNative("function Math.acos(a)", scMathACos, 0);
    PyJS->addNative("function Math.tan(a)", scMathTan, 0);
    PyJS->addNative("function Math.atan(a)", scMathATan, 0);
    PyJS->addNative("function Math.sinh(a)", scMathSinh, 0);
    PyJS->addNative("function Math.asinh(a)", scMathASinh, 0);
    PyJS->addNative("function Math.cosh(a)", scMathCosh, 0);
    PyJS->addNative("function Math.acosh(a)", scMathACosh, 0);
    PyJS->addNative("function Math.tanh(a)", scMathTanh, 0);
    PyJS->addNative("function Math.atanh(a)", scMathATanh, 0);
       
    PyJS->addNative("function Math.E()", scMathE, 0);
    PyJS->addNative("function Math.log(a)", scMathLog, 0);
    PyJS->addNative("function Math.log10(a)", scMathLog10, 0);
    PyJS->addNative("function Math.exp(a)", scMathExp, 0);
    PyJS->addNative("function Math.pow(a,b)", scMathPow, 0);
    
    PyJS->addNative("function Math.sqr(a)", scMathSqr, 0);
    PyJS->addNative("function Math.sqrt(a)", scMathSqrt, 0);    
  
}
