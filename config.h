#ifndef PyJS_config_h__
#define PyJS_config_h__

//////////////////////////////////////////////////////////////////////////

/* POOL-ALLOCATOR 
 * ==============
 * To speed-up new & delete PyJS adds an object-pool
 * The pool is activated by default.
 * To deactivate this stuff define NO_POOL_ALLOCATOR 
 */
//#define NO_POOL_ALLOCATOR

/*
 * for debugging-stuff you can define DEBUG_POOL_ALLOCATOR
 * if a memory-leak detected the allocator usage is printed to stderr
 */
//#define DEBUG_POOL_ALLOCATOR
/*
 * with define LOG_POOL_ALLOCATOR_MEMORY_USAGE
 * the allocator usage is always printed to stderr
 */
//#define LOG_POOL_ALLOCATOR_MEMORY_USAGE

// NOTE: _DEBUG or LOG_POOL_ALLOCATOR_MEMORY_USAGE implies DEBUG_POOL_ALLOCATOR

//////////////////////////////////////////////////////////////////////////

/* REGEXP-SUPPORT
 * ==============
 * The RegExp-support needs boost-regex or TR1-regex
 * To deactivate this stuff define NO_REGEXP 
 */
//#define NO_REGEXP

/* if NO_REGEXP not defined <regex> is included and std::regex is used
 * you can define HAVE_BOOST_REGEX and <boost/regex.hpp> is included and boost::regex is used
 */
//#define HAVE_BOOST_REGEX

/* or you can define HAVE_TR1_REGEX and <tr1/regex> is included and std::tr1::regex is used
 */
//#define HAVE_TR1_REGEX


//////////////////////////////////////////////////////////////////////////

/* LET-STUFF
 * =========
 * Redeclaration of LET-vars is not allowed in block-scopes.
 * But in the root- and functions-scopes it is currently allowed
 * In future ECMAScript versions this will be also in root-and functions-scopes forbidden
 * To enable the future behavior define PREVENT_REDECLARATION_IN_FUNCTION_SCOPES
 */
//#define PREVENT_REDECLARATION_IN_FUNCTION_SCOPES

//////////////////////////////////////////////////////////////////////////

/* GENERATOR's
 * ===========
 * functions with "yield" in it is detected as Generator.
 * Generator-support needs threading-stuff
 * To disable Generators define NO_GENERATORS
 */
//#define NO_GENERATORS


//////////////////////////////////////////////////////////////////////////

/* MULTI-THREADING
 * ===============
 * PyJS is basically thread-save.
 * You can run different or the same JS-code simultaneously in different instances of class PyJS. 
 * >>> NOTE: You can NOT run more threads on the SAME instance of class PyJS <<<
 * The threading-stuff is needed by the pool-allocator (locking) and the generator-/yield-stuff
 * to deactivate threading define NO_THREADING
 * NOTE: if NO_POOL_ALLOCATOR not defined you can not run JS-code simultaneously
 */
//#define NO_THREADING

/* with C++2011 (or MS VisualC++ 2012 and above) the C++ 2011 STL-Threading-API is used. 
 * You can define NO_CXX_THREADS to use alternate API's
 */
//#define NO_CXX_THREADS 

/* if C++ 2011 STL-Threading-API not available
 * on Windows the windows-threading-API is used by default.
 * on non-Windows (WIN32 is not defined) it is tried to use the POSIX pthread-API
 * to force the pthread-API define HAVE_PTHREAD (windows needs in this case 
 *   a pthread-lib e.g http://http://sourceware.org/pthreads-win32/)
 */
//#define HAVE_PTHREAD

/* you can implement your own custom thread-implementation.
 * to prevent the using of the win- or pthread-API define HAVE_CUSTOM_THREADING_IMPL
 */
//#define HAVE_CUSTOM_THREADING_IMPL

////////////////////////////////////////////////
// DO NOT MAKE CHANGES OF THE FOLLOWING STUFF //
////////////////////////////////////////////////

#if defined(NO_THREADING) && !defined(NO_GENERATORS)
#	define NO_GENERATORS
#pragma message("\n***********************************************************************\n\
* You have defined NO_THREADING and not defined NO_GENERATORS\n\
* NOTE: GENERATORS needs THREADING. Generators/Yield are deactivated\n\
***********************************************************************\n")
#endif

#if defined(NO_POOL_ALLOCATOR) && defined(NO_GENERATORS) && !defined(NO_THREADING)
#	define NO_THREADING
#endif

#if !defined(NO_POOL_ALLOCATOR) && defined(NO_THREADING)
#pragma message("\n***********************************************************************\n\
* You have defined NO_THREADING and not defined NO_POOL_ALLOCATOR\n\
* NOTE: you can not run JS-code simultaneously in different threads\n\
***********************************************************************\n")
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L

#	define HAVE_CXX11_RVALUE_REFERENCE 1
#	define MEMBER_DELETE =delete

#	if !defined(NO_CXX_THREADS) && !defined(NO_THREADING)
#		define HAVE_CXX_THREADS 1
#	endif
#else
#	if _MSC_VER >= 1600
#		define HAVE_CXX11_RVALUE_REFERENCE 1
#	endif
#	if _MSC_VER >= 1700
#		if !defined(NO_CXX_THREADS) && !defined(NO_THREADING)
#			define HAVE_CXX_THREADS 1
#		endif
#	endif
#	if _MSC_VER >= 1800
#		define define MEMBER_DELETE =delete
#	endif
#endif

#ifndef MEMBER_DELETE
#	define MEMBER_DELETE
#endif

#endif // PyJS_config_h__
