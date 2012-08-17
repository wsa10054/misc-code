#ifndef known_env_h__
#define known_env_h__



/***************************************************************************
*
* _ENV_I386                Intel i386/i486/Pentium (little endian)
* _ENV_X86_64              AMD64(x86)/Intel64(x86) (little endian)
* _ENV_ALPHA               Compaq/Digital Alpha (little endian)
* _ENV_SPARC               Sun Sparc
* _ENV_HPPA                HP PA-RISC
* _ENV_MIPS                MIPS
* _ENV_PPC                 PowerPC
* _ENV_POWER               POWER Processors.
*
* _ENV_MSVCPP              Microsoft Visual C++ compiler; version
* _ENV_WIN                 32 or 64 bit Windows
* _ENV_WINNT               Windows NT
* _ENV_WIN32               32 bit Windows
* _ENV_WIN64               64 bit Windows
*
* _ENV_UNIX                UNIX
*
* _ENV_SOLARIS             SUN Solaris
* _ENV_LINUX               Linux
* _ENV_HPUX                HP UNIX
* _ENV_AOSF                Digital UNIX/Tru64 UNIX
*
* _ENV_AIX                 IBM AIX
* _ENV_IRIX                SGI IRIX
* _ENV_OS390               IBM OS/390
* _ENV_AS400               IBM OS/400, AS/400
* _ENV_MACOS               Macintosh
*
* _ENV_GNUC                GNU C/C++ compiler; major version
*
* _ENV_HP_ACC              HP aC++ compiler; version
*
* _ENV_SUNPRO              Sun Pro/Workshop/Forte compiler; version (_ENV_SUNPRO_CC)
* _ENV_SUNPRO_CC           Sun Pro/Workshop/Forte CC compiler; version
* _ENV_SUNPRO_C            Sun Pro/Workshop/Forte C compiler; version
*
* _ENV_SUN_SPARC           Sun Sparc compilation mode
* _ENV_SUN_SPARC32         Sun Sparc 32-bit compilation mode
* _ENV_SUN_SPARC64         Sun Sparc 64-bit compilation mode
* _ENV_SUN_I386            Sun i386 compilation mode
*
* _ENV_AOSF_CC             Compaq C++ compiler for Tru64; version
*
* _ENV_INT64_NATIVE        Compiler provides a 64-bit integer (not supported yet)
* _ENV_64BIT_NATIVE        defined for 64 bit platforms       (not supported yet)
*
* _ENV_CSET                IBM AIX xlC, xlc, etc. this may be in old version.
* _ENV_IBMC                IBM AIX c compiler,xlc, cc.
* _ENV_IBMCPP              IBM AIX cpp compiler, xlC.
* _ENV_MVSCPP              IBM OS390 c++, cxx.
* _ENV_MIPSPRO_CC          SGI IRIX C
*
* _ENV_BIG_ENDIAN_ARCH     Defined if big-endian architecture
* _ENV_LITTLE_ENDIAN_ARCH  Defined if little-endian architecture
*
* _ENV_SYSCALL             __stdcall on Windows
*
* _ENV_DECLSPEC_DLLEXPORT  __declspec(dllexport) for VC++; empty otherwise
* _ENV_DECLSPEC_DLLIMPORT  __declspec(dllimport) for VC++; empty otherwise
*
***************************************************************************/


/*********************************/
/*  Operating system / platform  */
/*********************************/

/* Windows platforms */
#if (defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(__WIN32__))
#define _ENV_WIN
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
#define _ENV_WIN32
#elif (defined(WIN64) || defined(_WIN64))
#define _ENV_WIN64
#endif
#ifdef _WIN32_WINNT
#define _ENV_WINNT
#endif
/* Alpha OSF / Tru64 / Digital UNIX */
#elif (defined(__osf__))
#define _ENV_AOSF
#define _ENV_UNIX
/* SUN Solaris - assumed */
#elif (defined(__sun))
#define _ENV_SOLARIS
#define _ENV_UNIX
/* IBM AIX */
#elif (defined(_AIX))
#define _ENV_AIX
#define _ENV_UNIX      /* AIX4.2 supports UNIX95, AIX4.3 supports UNIX98 */
/* SGI IRIX */
#elif (defined(IRIX))
#define _ENV_IRIX
#define _ENV_UNIX
/* IBM OS390 */
#elif (defined(__MVS__))
#define _ENV_OS390
#define _ENV_UNIX    /* OS/390 V2R2 UNIX95, OS/390 V2R7 UNIX98 */
#elif (defined(EXM_OS390))
#define _ENV_OS390
#define _ENV_UNIX
/* IBM AS400 */
#elif (defined(__OS400__))
#define _ENV_AS400
#define _ENV_UNIX
/* Macintosh */
#elif (defined(macintosh))
#define _ENV_MACOS
/* Linux */
#elif (defined(__linux__))
#define _ENV_LINUX
#define _ENV_UNIX
/* HP Unix */
#elif (defined(__hpux))
#define _ENV_HPUX
#define _ENV_UNIX
/* Else */
#else
#warning  "Unknown platform!"
#endif


/**************/
/*  Compiler  */
/**************/

#if (defined(_MSC_VER)) /* Microsoft Visual C++ */
#define _ENV_MSVCPP _MSC_VER
#elif defined(__BORLANDC__)
#define _ENV_BORC        /* Borland C/C++ */
#elif defined(__WATCOMC__)
#define _ENV_WATCOMC    /* watcom c/c++ */
#elif (defined(__GNUC__)) /* GNU Project */
#define _ENV_GNUC __GNUC__
#elif (defined(__SUNPRO_CC) || defined(__SUNPRO_C)) /* SUN Pro/Workshop/Forte */
#define _ENV_SUNPRO __SUNPRO_CC
#ifdef __SUNPRO_CC
#define _ENV_SUNPRO_CC __SUNPRO_CC
#endif
#ifdef __SUNPRO_C
#define _ENV_SUNPRO_C __SUNPRO_C
#endif
#elif (defined(__HP_aCC)) /* HP aCC */
#define _ENV_HP_ACC __HP_aCC
#elif (defined(__xlC__))    /* IBM C SET */
#define _ENV_CSET __xlC__
#elif (defined(__IBMC__))   /* IBM c compiler */
#define _ENV_IBMC __IBMC__
#elif (defined(__IBMCPP__)) /* IBM c++ compiler */
#define _ENV_IBMCPP __IBMCPP__
#elif (defined(_ENV_IRIX) || defined(__sgi))
#define _ENV_MPISPRO_CC
#elif (defined(__MVS__) && defined(__cplusplus)) /* OS390 c++ compiler */
#define _ENV_MVSCPP
#elif (defined(EXM_OS390) && defined(__cplusplus)) /* OS390 c++ compiler */
#define _ENV_MVSCPP
#elif (defined(__OS400__))
#elif (defined(__DECCXX_VER)) /* Compaq C++ */
#define _ENV_AOSF_CC __DECCXX_VER
#else
#warning  "Unknown compiler!"
#endif


/****************************/
/*  Processor architecture  */
/****************************/

#if (defined(_ENV_MSVCPP))

	#ifdef _M_IX86 /* i386 architecture */
	#define _ENV_I386
	#endif
	
	#if ( defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) )
	#define _ENV_X86_64
	#endif
	
	#ifdef _M_ALPHA /* Alpha architecture */
	#define _ENV_ALPHA
	#endif

#elif (defined(_ENV_SUNPRO))

	#ifdef __sparc /* Sparc architecture - 32-bit compilation mode */
	#define _ENV_SPARC
	#define _ENV_SUN_SPARC
	#define _ENV_SUN_SPARC32
	#endif
	#ifdef __sparcv9 /* Sparc architecture - 64-bit compilation mode */
	#define _ENV_SPARC
	#define _ENV_SUN_SPARC
	#define _ENV_SUN_SPARC64
	#endif
	#ifdef __i386 /* I386 architecture */
	#define _ENV_I386
	#define _ENV_SUN_I386
	#endif

#elif (defined(_ENV_AOSF_CC))

	#ifdef __alpha /* Alpha architecture */
	#define _ENV_ALPHA
	#endif

#elif (defined(_ENV_GNUC))

	#if (defined(__alpha) || defined(__alpha__))
	#define _ENV_ALPHA
	#elif (defined(__i386__))
	#define _ENV_I386
	#elif (defined(__sparc))
	#define _ENV_SUN_SPARC32
	#elif (defined(__hppa__))
	#define _ENV_HPPA
	#elif (defined(__mips__))
	#define _ENV_MIPS
	#elif (defined(__PPC__))
	#define _ENV_PPC
	#elif ( defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) )
	#define _ENV_X86_64
	#else
	#warning  "Unknown processor architecture!"
	#endif

#elif (defined(_ENV_HP_ACC))

	#if defined(__hppa)
	#define _ENV_HPPA
	#endif

	#elif (defined(__mips) || defined(__mips__) || defined(__MIPS__))
	#define _ENV_MIPS

	#elif (defined(_ENV_AIX))
	#if defined(_POWER)
	#define _ENV_POWER
	#endif

#elif (defined(_ENV_MACOS))

	#define _ENV_PPC

	#elif (defined(_ENV_OS390)||defined(_ENV_AS400))
	#define _ENV_POWER

#else
#warning "Unknown processor architecture!"

#endif


/*****************/
/*  Endian-ness  */
/*****************/

#if (defined(_ENV_I386) || defined(_ENV_X86_64)|| defined(_ENV_ALPHA))
#ifndef _ENV_LITTLE_ENDIAN_ARCH
#define _ENV_LITTLE_ENDIAN_ARCH
#endif /* _ENV_LITTLE_ENDIAN_ARCH */
#ifdef _ENV_BIG_ENDIAN_ARCH
#undef _ENV_BIG_ENDIAN_ARCH
#endif /* _ENV_BIG_ENDIAN_ARCH */
#else /* Sparc, etc. */
#ifndef _ENV_BIG_ENDIAN_ARCH
#define _ENV_BIG_ENDIAN_ARCH
#endif /* _ENV_BIG_ENDIAN_ARCH */
#ifdef _ENV_LITTLE_ENDIAN_ARCH
#undef _ENV_LITTLE_ENDIAN_ARCH
#endif /* _ENV_LITTLE_ENDIAN_ARCH */
#endif /* Little-endian architectures */

/* TBD:  How the hell do I detect endian-ness of HPPA machines, or is
   it transparent to the program? */


/**************************/
/*  Miscellaneous macros  */
/**************************/

#if (defined(_ENV_MSVCPP))
#define _ENV_DECLSPEC_DLLEXPORT __declspec(dllexport)
#define _ENV_DECLSPEC_DLLIMPORT __declspec(dllimport)
#define _ENV_SYSCALL            __stdcall

#define _ENV_DECLSPEC_DLLEXPORT_MID

#elif defined(_ENV_OS390)

#define _ENV_DECLSPEC_DLLEXPORT
#define _ENV_DECLSPEC_DLLIMPORT
#define _ENV_SYSCALL           
#define _ENV_DECLSPEC_DLLEXPORT_MID _Export

#else /* not _ENV_MSVCPP */

#define _ENV_DECLSPEC_DLLEXPORT
#define _ENV_DECLSPEC_DLLIMPORT
#define _ENV_SYSCALL

#define _ENV_DECLSPEC_DLLEXPORT_MID

#endif /* _ENV_MSVCPP */


#endif // known_env_h__
