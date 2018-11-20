#ifndef LITEBOT_H
#define LITEBOT_H

/*****************************************************************************

	- DEFINES
		
	- CONVERT STRUCTS
		
	- STRING FUNCTIONS

	- FORMATTED STRUCTS

	- STRUCTS AND ENUMS

	- STOOL
		string tool

	- VTOOL
		vector tool

	- BOT RUNTIME VARIABLES

	- LITEBot
		
		Mutex Manip



******************************************************************************/

// DEFINES

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <ratio>
#include <climits>
#include <cstdint>
#include <cfloat>
#include <sys/stat.h>
#include <iostream> 
#include <cmath>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <sys/types.h>

//#define _BOT_FOR_ANDR_ 1

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <direct.h>
#include "../_includes/_win/dirent.h"
#include "../_includes/_win/sched.h"
#include "../_includes/_win/semaphore.h"
#include "../_includes/_win/pthread.h"
#include "../_includes/_win/sqlite3.h"
#pragma comment(lib, "Ws2_32.lib")
#define mode_t unsigned short
#define nlink_t unsigned long long
#define uid_t unsigned long long
#define gid_t unsigned long long
#else
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif
#ifdef _BOT_FOR_ANDR_
#include <unistd.h>
#include <csignal.hs>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "../_includes/_andr/sqlite3.h"
#ifndef errno_t
#define errno_t signed short
#endif
#else
#ifdef __GNUC__
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "../_includes/_gcc/sqlite3.h"
#ifndef errno_t
#define errno_t signed short
#endif
#endif
#endif
#endif

#ifndef _POSIX_THREAD_THREADS_MAX
#define _POSIX_THREAD_THREADS_MAX 64
#endif

#ifndef BOTTHREAD_MAX
#define BOTTHREAD_MAX _POSIX_THREAD_THREADS_MAX
#else
#if (BOTTHREAD_MAX < 8)
#define BOTTHREAD_MAX 8
#else
#if (BOTTHREAD_MAX > _POSIX_THREAD_THREADS_MAX)
#define BOTTHREAD_MAX _POSIX_THREAD_THREADS_MAX
#endif
#endif
#endif

#ifndef BOTOPORT_MAX
#define BOTOPORT_MAX 100
#else
#if (BOTOPORT_MAX < 4)
#define BOTOPORT_MAX 4
#else
#if (BOTOPORT_MAX > UINT32_MAX - 1025)
#define BOTOPORT_MAX UINT32_MAX - 1025
#endif
#endif
#endif

#ifndef BOT_SCKMAX
#define BOT_SCKMAX 10
#else
#if BOT_SCKMAX > SOMAXCONN
#define BOT_SCKMAX SOMAXCONN
#else
#if BOT_SCKMAX < 1
#define BOT_SCKMAX 1
#endif
#endif
#endif

#ifndef BOT_SCKT_MAX
#define BOT_SCKT_MAX 5
#endif

#ifndef BOTLPORT_A
#define BOTLPORT_A 3141
#else
#if BOTLPORT_A < 1024
#define BOTLPORT_A 3141
#endif
#endif

#ifndef BOTLPORT_B
#define BOTLPORT_B 17776
#else
#if BOTLPORT_B < 1024
#define BOTLPORT_B 17776
#endif
#endif

#ifndef BOTLPORT_C
#define BOTLPORT_C 12345
#else
#if BOTLPORT_C < 1024
#define BOTLPORT_C 12345
#endif
#endif

#ifndef BOT_STRLEN_MAX
#define BOT_STRLEN_MAX 5242880
#else
#if (BOT_STRLEN_MAX > 5242880)
#define BOT_STRLEN_MAX 5242880
#else
#if (BOT_STRLEN_MAX < 16 )
#define BOT_STRLEN_MAX 16
#endif
#endif
#endif

#ifndef BOT_MAX_RCV
#define BOT_MAX_RCV 5242880
#else
#if (BOT_MAX_RCV > 5242880)
#define BOT_MAX_RCV 5242880
#else
#if (BOT_MAX_RCV < 16 )
#define BOT_MAX_RCV 16
#endif
#endif
#endif

#ifndef BOT_SEEDV_A
#define BOT_SEEDV_A 2701
#endif

#ifndef BOT_SEEDV_B
#define BOT_SEEDV_B 2501
#endif

#ifndef BOT_SEEDV_C
#define BOT_SEEDV_C 701
#endif

// How deeply we scan folder structure while opening directories
#ifndef BOT_DIRSCAN_LVL
#define BOT_DIRSCAN_LVL 1
#else
#if (BOT_DIRSCAN_LVL > 2)
#define BOT_DIRSCAN_LVL 2
#else
#if (BOT_DIRSCAN_LVL < 0 )
#define BOT_DIRSCAN_LVL 0
#endif
#endif
#endif

// How deeply we scan files accessed by our program
#ifndef BOT_FSCAN_LVL
#define BOT_FSCAN_LVL 1
#else
#if (BOT_FSCAN_LVL > 2)
#define BOT_FSCAN_LVL 2
#else
#if (BOT_FSCAN_LVL < 0 )
#define BOT_FSCAN_LVL 0
#endif
#endif
#endif

// How many bytes we scan in files accessed by our program
#ifndef BOT_FSCAN_LIM
#define BOT_FSCAN_LIM 10240
#else
#if (BOT_FSCAN_LIM > BOT_STRLEN_MAX)
#define BOT_FSCAN_LIM BOT_STRLEN_MAX
#else
#if (BOT_FSCAN_LIM < 4 )
#define BOT_FSCAN_LIM 4
#endif
#endif
#endif

#ifndef BOT_A_STR
#define BOT_A_STR "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
#endif

#ifndef BOT_N_STR
#define BOT_N_STR "0123456789.,-"
#endif

#ifndef BOT_I_STR
#define BOT_I_STR "0123456789"
#endif

#ifdef _WIN32
#define BOT_NOFLD_V std::vector<std::string>{ "$", ".", "..", "Windows", "WINDOWS", "WINDOWS" }
#else
#define BOT_NOFLD_V std::vector<std::string>{ "$", ".", ".." }
#endif

#ifdef _WIN32
#ifndef BOT_HMD
#define BOT_HMD "LITEBot"
#else
#if (strlen(BOT_HMD) > 1024)
#define BOT_HMD "LITEBot"
#else
#if (strlen(BOT_HMD) < 1)
#define BOT_HMD "LITEBot"
#endif
#endif
#endif
#else
#ifdef _BOT_FOR_ANDR_
#ifndef BOT_HMD
#define BOT_HMD "emulated\\0\\Android\\data\\com.litebot\\files"
#else
#if (strlen(BOT_HMD) > 1024)
#define BOT_HMD "emulated\\0\\Android\\data\\com.litebot\\files"
#else
#if (strlen(BOT_HMD) < 1)
#define BOT_HMD "emulated\\0\\Android\\data\\com.litebot\\files"
#endif
#endif
#endif
#endif
#endif

#ifndef BOT_LOG_NM
#define BOT_LOG_NM "_bot_logs"
#else
#if (strlen(BOT_LOG_NM) > 1024)
#define BOT_LOG_NM "_bot_logs"
#else
#if (strlen(BOT_LOG_NM) < 4)
#define BOT_LOG_NM "_bot_logs"
#endif
#endif
#endif

#ifndef BOT_DBD_NM
#define BOT_DBD_NM "_bot_dbs"
#else
#if (strlen(BOT_DBD_NM) > 1024)
#define BOT_DBD_NM "_bot_dbs"
#else
#if (strlen(BOT_DBD_NM) < 4)
#define BOT_DBD_NM "_bot_dbs"
#endif
#endif
#endif

#ifndef BOT_USE_DBPATH
#define BOT_USE_DBPATH 0
#else
#if BOT_USE_DBPATH > 1
#define BOT_USE_DBPATH 1
#endif
#endif

#ifndef BOT_MOD_NM
#define BOT_MOD_NM "_bot_mods"
#else
#if (strlen(BOT_MOD_NM) > 1024)
#define BOT_MOD_NM "_bot_mods"
#else
#if (strlen(BOT_MOD_NM) < 4)
#define BOT_MOD_NM "_bot_mods"
#endif
#endif
#endif

#ifndef BOT_LDSI_NM
#define BOT_LDSI_NM "_bot_lds\\ldsi"
#else
#if (strlen(BOT_LDSI_NM) > 1024)
#define BOT_LDSI_NM "_bot_lds\\ldsi"
#else
#if (strlen(BOT_LDSI_NM) < 4)
#define BOT_LDSI_NM "_bot_lds\\ldsi"
#endif
#endif
#endif

#ifndef BOT_LDSO_NM
#define BOT_LDSO_NM "_bot_lds\\ldso"
#else
#if (strlen(BOT_LDSO_NM) > 1024)
#define BOT_LDSO_NM "_bot_lds\\ldso"
#else
#if (strlen(BOT_LDSI_NM) < 4)
#define BOT_LDSO_NM "_bot_lds\\ldso"
#endif
#endif
#endif

#ifndef BOT_SCD_NM
#define BOT_SCD_NM "_bot_scripts"
#else
#if (strlen(BOT_SCD_NM) > 1024)
#define BOT_SCD_NM "_bot_scripts"
#else
#if (strlen(BOT_SCD_NM) < 4)
#define BOT_SCD_NM "_bot_scripts"
#endif
#endif
#endif

#ifndef BOT_NETI_NM
#define BOT_NETI_NM "_bot_neti"
#else
#if (strlen(BOT_NETI_NM) > 1024)
#define BOT_NETI_NM "_bot_neti"
#else
#if (strlen(BOT_NETI_NM) < 4)
#define BOT_NETI_NM "_bot_neti"
#endif
#endif
#endif

/* default debug level for each instance of class LITEBot. */
#ifndef BOT_DEBUG_LVL
#define BOT_DEBUG_LVL 10
#endif

/* default debug mode for each instance of class LITEBot. */
/* debug_m = || (0) == no debug || (1) == debug messages from instances of functions within call stack for Output() are ignored || (2) == debug messages from instances of functions within call stack for Output() are held in queue and prepended with [Q] */
#ifndef BOT_DEBUG_M
#define BOT_DEBUG_M 2
#endif

#ifndef BOT_VARARG_MAX
#define BOT_VARARG_MAX 100
#else
#if (BOT_VARARG_MAX > 100)
#define BOT_VARARG_MAX 100
#else
#if (BOT_VARARG_MAX < 1)
#define BOT_VARARG_MAX 1
#endif
#endif
#endif

/* number of times we will try to acquire locks for a fstream object before giving up*/
#ifndef BOT_FTRY_MAX
#define BOT_FTRY_MAX INT32_MAX
#else
#if (BOT_FTRY_MAX > INT32_MAX)
#define BOT_FTRY_MAX INT32_MAX
#else
#if (BOT_FTRY_MAX < 1)
#define BOT_FTRY_MAX 1
#endif
#endif
#endif

/*number of iterations in the test thread*/
#ifndef BOT_ITER_TO
#define BOT_ITER_TO 101
#else
#if (BOT_ITER_TO > 1000)
#define BOT_ITER_TO 1000
#else
#if (BOT_ITER_TO < 10)
#define BOT_ITER_TO 10
#endif
#endif
#endif

#ifndef BOT_FILENAME_MAX
#define BOT_FILENAME_MAX 1024
#else
#if (BOT_FILENAME_MAX > 1024)
#define BOT_FILENAME_MAX 1024
#else
#if (BOT_FILENAME_MAX < 16)
#define BOT_FILENAME_MAX 16
#endif
#endif
#endif

#ifndef BOT_FILE_CHUNK
#define BOT_FILE_CHUNK 512
#else
#if (BOT_FILE_CHUNK > BOT_STRLEN_MAX)
#define BOT_FILE_CHUNK BOT_STRLEN_MAX
#endif
#endif

#ifndef BOT_FILESIZE_MAX
#define BOT_FILESIZE_MAX (UINT64_MAX - 1)
#else
#if (BOT_FILESIZE_MAX > (UINT64_MAX - 1))
#define BOT_FILESIZE_MAX (UINT64_MAX - 1)
#else
#if (BOT_FILESIZE_MAX < 16)
#define BOT_FILESIZE_MAX 16
#endif
#endif
#endif

#ifndef BOT_CRSV_MAX
#define BOT_CRSV_MAX 4096
#else
#if (BOT_CRSV_MAX > BOT_STRLEN_MAX)
#define BOT_CRSV_MAX BOT_STRLEN_MAX
#endif
#endif

#ifndef BOT_FILE_APND
#define BOT_FILE_APND (std::ios::out | std::ios::ate | std::ios::app | std::ios::binary)
#endif

#ifndef BOT_FILE_OVRL
#define BOT_FILE_OVRL (std::ios::out | std::ios::binary)
#endif

#ifndef BOT_FILE_INS
#define BOT_FILE_INS (std::ios::in | std::ios::out | std::ios::binary)
#endif

#ifndef BOT_FILE_READ
#define BOT_FILE_READ (std::ios::in | std::ios::binary)
#endif

#ifndef BOT_FILE_READATE
#define BOT_FILE_READATE (std::ios::in | std::ios::ate | std::ios::binary)
#endif

/*1=use pthread_trylock() 0=use pthread_lock()*/
#ifndef BOT_FILE_TLOCK
#define BOT_FILE_TLOCK 1
#else
#if (BOT_FILE_TLOCK > 1)
#define BOT_FILE_TLOCK 1
#else
#if (BOT_FILE_TLOCK < 0)
#define BOT_FILE_TLOCK 0
#endif
#endif
#endif

#ifndef BOT_TST_PKL
#define BOT_TST_PKL 32
#endif

#ifndef BOT_TST_PKS
#define BOT_TST_PKS (BOT_TST_PKL + 8)
#endif

/* limit number of databases a thread can attach to */
#ifndef BOT_ATT_LIM
#define BOT_ATT_LIM 10
#endif

/* number of fstream objects threads can use */
#ifndef BOT_FS_LIM
#define BOT_FS_LIM 50
#endif

#ifndef BOT_INCR_STR
#define BOT_INCR_STR "USED"
#endif

#ifndef BOT_NANO_REST
#define BOT_NANO_REST 100000
#endif

#ifndef BOT_MILLI_REST
#define BOT_MILLI_REST 1
#endif

/* number of blocks of data threads can use to store data, BOT_FILE member .dat points to blocks in this array */
#ifndef BOT_FPAD_MAX
#define BOT_FPAD_MAX 100
#endif

#ifndef BOTVEC_LIM
#define BOTVEC_LIM (BOT_STRLEN_MAX - 1)
#endif

#ifndef BOT_OUT_OPTS
#define BOT_OUT_OPTS 4
#endif

#ifndef BOT_MTX_MAXCT
#define BOT_MTX_MAXCT UINT_MAX
#endif

#ifndef BOT_TERM_WAIT
#define BOT_TERM_WAIT 60000
#endif

#ifndef BOT_LOGREST
#define BOT_LOGREST (BOT_MILLI_REST*500)
#endif

#ifndef BOT_DBREST
#define BOT_DBREST (BOT_MILLI_REST*5000)
#endif

#ifndef BOT_THRREST
#define BOT_THRREST (BOT_MILLI_REST*400)
#endif

#ifndef BOT_QUITREST
#define BOT_QUITREST (BOT_MILLI_REST*200)
#endif

#ifndef BOT_REQREST
#define BOT_REQREST (BOT_NANO_REST)
#endif

#ifndef BOT_LOCKREST
#define BOT_LOCKREST (BOT_NANO_REST*10)
#endif

#ifndef BOT_FO_REST
#define BOT_FO_REST (BOT_NANO_REST*50)
#endif

#ifndef BOT_IO_REST
#define BOT_IO_REST (BOT_NANO_REST*40)
#endif

#ifndef BOT_CNSREST
#define BOT_CNSREST (BOT_MILLI_REST*10)
#endif

#ifndef BOT_SERVREST
#define BOT_SERVREST (BOT_MILLI_REST)
#endif

#ifndef BOT_CLIREST
#define BOT_CLIREST (BOT_MILLI_REST)
#endif

#ifndef uint
#define uint unsigned int
#endif
#ifndef sint
#define sint int
#endif
#ifndef ulint
#define ulint unsigned long int
#endif
#ifndef slint
#define slint signed long int
#endif
#ifndef ullint
#define ullint unsigned long long int
#endif
#ifndef sllint
#define sllint signed long long int
#endif
#ifndef u_char
#define u_char unsigned char
#endif
#ifndef cu_char
#define cu_char const unsigned char
#endif
#ifndef _char
#define _char char
#endif
#ifndef c_char
#define c_char const char
#endif
#ifndef s_char
#define s_char signed char
#endif
#ifndef cs_char
#define cs_char const signed char
#endif

#ifndef BOT_BOUND_UCHR
#define BOT_BOUND_UCHR (u_char)(UINT_MAX - 1)
#endif

#ifndef BOT_BOUND_CHR
#define BOT_BOUND_CHR (_char)(INT_MAX - 1)
#endif

#ifndef BOT_BOUND_SCHR
#define BOT_BOUND_SCHR (s_char)(UINT_MAX - 1)
#endif

#ifndef BOT_NOERROR_STR
#define BOT_NOERROR_STR "*BOTERROR*no error.*BOTERROR*"
#endif

#ifndef BOT_ERRORLIM_STR
#define BOT_ERRORLIM_STR "*BOTERROR*input exceeds size limit.*BOTERROR*"
#endif

#ifndef BOT_ERRORNINV_STR
#define BOT_ERRORNINV_STR "*BOTERROR*numerical format specifier used for _char string type var.*BOTERROR*"
#endif


#ifndef BOT_ERRORUK_STR
#define BOT_ERRORUK_STR "*BOTERROR*uknonwn format specifier.*BOTERROR*"
#endif

#ifndef BOT_ERRORPREC_STR
#define BOT_ERRORPREC_STR "*BOTERROR*format precision > 20.*BOTERROR*"
#endif

#ifndef BOT_ERRORFPREC_STR
#define BOT_ERRORFPREC_STR "*BOTERROR*format specifier following precision.*BOTERROR*"
#endif

// CONVERT STRUCTS

typedef struct bot_ftia
{
	slint a[2];

	bot_ftia(float* x = 0)
	{
		if (x)
		{
			if (*x != 0.0f)
			{
				a[0] = (slint)*x;
				a[1] = (slint)((10000000000) * (*x - (float)(a[0])));
			}
			else
			{
				a[0] = a[1] = 0;
			}
		}
	}

}BOT_FTIA;

typedef struct bot_iatf
{
	float a;

	bot_iatf(slint vala = 0, slint valb = 0)
	{
		if (vala)
		{
			a = (float)vala;

			if (valb)
			{
				a += (float)(valb) / 10000000000.0f;
			}
		}
		else
		{
			a = 0.0f;
		}
	}

}BOT_IATF;

// STRING FUNCTIONS

bool bot_sisn(c_char* val = 0, sint slen = 0);
sint bot_shasn(c_char* val = 0, sint slen = 0);
bool bot_sisf(c_char* val = 0, sint slen = 0);
bool bot_sisa(c_char* val = 0, sint slen = 0);
sint bot_shasa(c_char* val = 0, sint slen = 0);
sint bot_str_err(sint err_no = 0, c_char* msg = "");
const size_t bot_sintlen(sint val[] = 0);
const size_t bot_uintlen(uint val[] = 0);
const size_t bot_dbllen(double val[] = 0);
const size_t bot_strlen(_char val[] = 0);
const size_t bot_cstrlen(c_char val[] = 0);
const size_t bot_ustrlen(u_char val[] = 0);
const size_t bot_custrlen(cu_char val[] = 0);
void bot_strcpy(_char inv[] = 0, _char val[] = 0);
void bot_ustrcpy(u_char inv[] = 0, u_char val[] = 0);
void bot_strclr(_char inchr[] = 0, size_t nl = 0);
void bot_ustrclr(u_char inchr[] = 0, size_t nl = 0);
void bot_cstrclr(c_char inchr[] = 0, size_t nl = 0);
void bot_custrclr(cu_char inchr[] = 0, size_t nl = 0);
sint bot_strchk(_char inchr[] = 0, size_t in_siz = (size_t)BOT_STRLEN_MAX);
sint bot_ustrchk(u_char inchr[] = 0, size_t in_siz = (size_t)BOT_STRLEN_MAX);
sint bot_cstrchk(c_char inchr[] = 0, size_t in_siz = (size_t)BOT_STRLEN_MAX);
sint bot_randstr(_char str_[] = 0, size_t siz = 0, _char fstr_[] = 0, size_t fsiz = 0);
sint bot_sprintf(_char inchr[] = 0, size_t in_siz = 0, c_char* fstr = 0, ...);
sint bot_sprintf(c_char inchr[] = 0, size_t in_siz = 0, c_char* fstr = 0, ...);
sint bot_sprintfs(std::string* str_ = 0, bool clear_str = false, c_char* fstr = 0, ...);

errno_t bot_itoa(sint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(slint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(sllint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(uint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(ulint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(ullint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_dtoa(double i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_dtoa(long double i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);

errno_t bot_itoa(sint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(slint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(sllint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(uint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(ulint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_itoa(ullint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_dtoa(double i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);
errno_t bot_dtoa(long double i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10);

errno_t bot_itoa(sint i, std::string* str = 0, sint radix = 10);
errno_t bot_itoa(slint i, std::string* str = 0, sint radix = 10);
errno_t bot_itoa(sllint i, std::string* str = 0, sint radix = 10);
errno_t bot_itoa(uint i, std::string* str = 0, sint radix = 10);
errno_t bot_itoa(ulint i, std::string* str = 0, sint radix = 10);
errno_t bot_itoa(ullint i, std::string* str = 0, sint radix = 10);
errno_t bot_dtoa(double i, std::string* str = 0, sint radix = 10);
errno_t bot_dtoa(long double i, std::string* str = 0, size_t in_siz = 0, sint radix = 10);

sllint bot_findin(_char val[] = 0, size_t offs = 0, size_t lim = 0, _char inv[] = 0);
sllint bot_findin(_char val[] = 0, size_t offs = 0, size_t lim = 0, c_char* inv = 0);
sllint bot_findin(u_char val[] = 0, size_t offs = 0, size_t lim = 0, u_char inv[] = 0);

// FORMATTED STRUCTS

typedef struct bot_carr_2
{
	size_t siz = 2;
	_char carr[2] = { 0 };

	bot_carr_2(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_2() { bot_strclr(carr); }
}carr_2;

typedef struct bot_carr_3
{
	size_t siz = 3;
	_char carr[3] = { 0 };

	bot_carr_3(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_3() { bot_strclr(carr); }
}carr_3;

typedef struct bot_carr_4
{
	size_t siz = 4;
	_char carr[4] = { 0 };

	bot_carr_4(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_4() { bot_strclr(carr); }
}carr_4;

typedef struct bot_carr_6
{
	size_t siz = 6;
	_char carr[6] = { 0 };

	bot_carr_6(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_6() { bot_strclr(carr); }
}carr_6;

typedef struct bot_carr_8
{
	size_t siz = 8;
	_char carr[8] = { 0 };

	bot_carr_8(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_8() { bot_strclr(carr); }
}carr_8;

typedef struct bot_carr_9
{
	size_t siz = 9;
	_char carr[9] = { 0 };

	bot_carr_9(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_9() { bot_strclr(carr); }
}carr_9;

typedef struct bot_carr_12
{
	size_t siz = 12;
	_char carr[12] = { 0 };

	bot_carr_12(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_12() { bot_strclr(carr); }
}carr_12;

typedef struct bot_carr_16
{
	size_t siz = 16;
	_char carr[16] = { 0 };

	bot_carr_16(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_16() { bot_strclr(carr); }
}carr_16;

typedef struct bot_carr_18
{
	size_t siz = 18;
	_char carr[18] = { 0 };

	bot_carr_18(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_18() { bot_strclr(carr); }
}carr_18;

typedef struct bot_carr_21
{
	size_t siz = 21;
	_char carr[21] = { 0 };

	bot_carr_21(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_21() { bot_strclr(carr); }
}carr_21;

typedef struct bot_carr_24
{
	size_t siz = 24;
	_char carr[24] = { 0 };

	bot_carr_24(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_24() { bot_strclr(carr); }
}carr_24;

typedef struct bot_carr_32
{
	size_t siz = 32;
	_char carr[32] = { 0 };

	bot_carr_32(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_32() { bot_strclr(carr); }
}carr_32;

typedef struct bot_carr_36
{
	size_t siz = 36;
	_char carr[36] = { 0 };

	bot_carr_36(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_36() { bot_strclr(carr); }
}carr_36;

typedef struct bot_carr_48
{
	size_t siz = 48;
	_char carr[48] = { 0 };

	bot_carr_48(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_48() { bot_strclr(carr); }
}carr_48;

typedef struct bot_carr_56
{
	size_t siz = 56;
	_char carr[56] = { 0 };

	bot_carr_56(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_56() { bot_strclr(carr); }
}carr_56;

typedef struct bot_carr_64
{
	size_t siz = 64;
	_char carr[64] = { 0 };

	bot_carr_64(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_64() { bot_strclr(carr); }
}carr_64;

typedef struct bot_carr_72
{
	size_t siz = 72;
	_char carr[72] = { 0 };

	bot_carr_72(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_72() { bot_strclr(carr); }
}carr_72;

typedef struct bot_carr_81
{
	size_t siz = 81;
	_char carr[81] = { 0 };

	bot_carr_81(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_81() { bot_strclr(carr); }
}carr_81;

typedef struct bot_carr_96
{
	size_t siz = 96;
	_char carr[96] = { 0 };

	bot_carr_96(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_96() { bot_strclr(carr); }
}carr_96;

typedef struct bot_carr_112
{
	size_t siz = 112;
	_char carr[112] = { 0 };

	bot_carr_112(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_112() { bot_strclr(carr); }
}carr_112;

typedef struct bot_carr_128
{
	size_t siz = 128;
	_char carr[128] = { 0 };

	bot_carr_128(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_128() { bot_strclr(carr); }
}carr_128;

typedef struct bot_carr_144
{
	size_t siz = 144;
	_char carr[144] = { 0 };

	bot_carr_144(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_144() { bot_strclr(carr); }
}carr_144;

typedef struct bot_carr_168
{
	size_t siz = 168;
	_char carr[168] = { 0 };

	bot_carr_168(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_168() { bot_strclr(carr); }
}carr_168;

typedef struct bot_carr_192
{
	size_t siz = 192;
	_char carr[192] = { 0 };

	bot_carr_192(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_192() { bot_strclr(carr); }
}carr_192;

typedef struct bot_carr_256
{
	size_t siz = 256;
	_char carr[256] = { 0 };

	bot_carr_256(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_256() { bot_strclr(carr); }
}carr_256;

typedef struct bot_carr_384
{
	size_t siz = 384;
	_char carr[384] = { 0 };

	bot_carr_384(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_384() { bot_strclr(carr); }
}carr_384;

typedef struct bot_carr_512
{
	size_t siz = 512;
	_char carr[512] = { 0 };

	bot_carr_512(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_512() { bot_strclr(carr); }
}carr_512;

typedef struct bot_carr_768
{
	size_t siz = 768;
	_char carr[768] = { 0 };

	bot_carr_768(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_768() { bot_strclr(carr); }
}carr_768;

typedef struct bot_carr_1024
{
	size_t siz = 1024;
	_char carr[1024] = { 0 };

	bot_carr_1024(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_1024() { bot_strclr(carr); }
}carr_1024;

typedef struct bot_carr_2048
{
	size_t siz = 2048;
	_char carr[2048] = { 0 };

	bot_carr_2048(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_2048() { bot_strclr(carr); }
}carr_2048;

typedef struct bot_carr_4096
{
	size_t siz = 4096;
	_char carr[4096] = { 0 };

	bot_carr_4096(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_4096() { bot_strclr(carr); }
}carr_4096;

typedef struct bot_carr_8192
{
	size_t siz = 8192;
	_char carr[8192] = { 0 };

	bot_carr_8192(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_8192() { bot_strclr(carr); }
}carr_8192;

typedef struct bot_carr_16384
{
	size_t siz = 16384;
	_char carr[16384] = { 0 };

	bot_carr_16384(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_16384() { bot_strclr(carr); }
}carr_16384;

typedef struct bot_carr_32768
{
	size_t siz = 32768;
	_char carr[32768] = { 0 };

	bot_carr_32768(_char ncar[] = 0) { if (ncar) { size_t nl = bot_strlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_carr_32768() { bot_strclr(carr); }
}carr_32768;

typedef struct bot_ucar_2
{
	size_t siz = 2;
	u_char carr[2] = { 0 };

	bot_ucar_2(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_2() { bot_ustrclr(carr); }
}ucar_2;

typedef struct bot_ucar_4
{
	size_t siz = 4;
	u_char carr[4] = { 0 };

	bot_ucar_4(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_4() { bot_ustrclr(carr); }
}ucar_4;

typedef struct bot_ucar_8
{
	size_t siz = 8;
	u_char carr[8] = { 0 };

	bot_ucar_8(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_8() { bot_ustrclr(carr); }
}ucar_8;

typedef struct bot_ucar_16
{
	size_t siz = 16;
	u_char carr[16] = { 0 };

	bot_ucar_16(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_16() { bot_ustrclr(carr); }
}ucar_16;

typedef struct bot_ucar_32
{
	size_t siz = 32;
	u_char carr[32] = { 0 };

	bot_ucar_32(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_32() { bot_ustrclr(carr); }
}ucar_32;

typedef struct bot_ucar_64
{
	size_t siz = 64;
	u_char carr[64] = { 0 };

	bot_ucar_64(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_64() { bot_ustrclr(carr); }
}ucar_64;

typedef struct bot_ucar_128
{
	size_t siz = 128;
	u_char carr[128] = { 0 };

	bot_ucar_128(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_128() { bot_ustrclr(carr); }
}ucar_128;

typedef struct bot_ucar_256
{
	size_t siz = 256;
	u_char carr[256] = { 0 };

	bot_ucar_256(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_256() { bot_ustrclr(carr); }
}ucar_256;

typedef struct bot_ucar_512
{
	size_t siz = 512;
	u_char carr[512] = { 0 };

	bot_ucar_512(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_512() { bot_ustrclr(carr); }
}ucar_512;

typedef struct bot_ucar_1024
{
	size_t siz = 1024;
	u_char carr[1024] = { 0 };

	bot_ucar_1024(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_1024() { bot_ustrclr(carr); }
}ucar_1024;

typedef struct bot_ucar_2048
{
	size_t siz = 2048;
	u_char carr[2048] = { 0 };

	bot_ucar_2048(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_2048() { bot_ustrclr(carr); }
}ucar_2048;

typedef struct bot_ucar_4096
{
	size_t siz = 4096;
	u_char carr[4096] = { 0 };

	bot_ucar_4096(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_4096() { bot_ustrclr(carr); }
}ucar_4096;

typedef struct bot_ucar_8192
{
	size_t siz = 8192;
	u_char carr[8192] = { 0 };

	bot_ucar_8192(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_8192() { bot_ustrclr(carr); }
}ucar_8192;

typedef struct bot_ucar_16384
{
	size_t siz = 16384;
	u_char carr[16384] = { 0 };

	bot_ucar_16384(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_16384() { bot_ustrclr(carr); }
}ucar_16384;

typedef struct bot_ucar_32768
{
	size_t siz = 32768;
	u_char carr[32768] = { 0 };

	bot_ucar_32768(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_32768() { bot_ustrclr(carr); }
}ucar_32768;

typedef struct bot_ucar_65535
{
	size_t siz = 65535;
	u_char carr[65535] = { 0 };

	bot_ucar_65535(u_char ncar[] = 0) { if (ncar) { size_t nl = bot_ustrlen(ncar); size_t ns = (nl > siz) ? siz - 1 : nl; memcpy((void*)carr, (void*)ncar, ns); } }
	~bot_ucar_65535() { bot_ustrclr(carr); }
}ucar_65535;

// STRUCTS AND ENUMS

/* connection types */
enum bot_con_val
{
	BOT_M_CON = 0,
	BOT_IO_CON = 1,
	BOT_DIR_CON = 2,
	BOT_F_CON = 3,
	BOT_DB_CON = 4,
	BOT_EXE_CON = 5,
	BOT_I4_CON = 6,
	BOT_I6_CON = 7,
	BOT_E128_CON = 12,
	BOT_E256_CON = 25,
	BOT_MAX_CON = 100
};

/* data types */
enum bot_rtv_vals
{
	BOT_RTV_MIN = SCHAR_MIN,
	BOT_RTV_SINT = 1,
	BOT_RTV_SLINT = 2,
	BOT_RTV_SLLINT = 3,
	BOT_RTV_UINT = 4,
	BOT_RTV_ULINT = 5,
	BOT_RTV_ULLINT = 6,
	BOT_RTV_CHAR = 7,
	BOT_RTV_UCHAR = 8,
	BOT_RTV_SINTP = 9,
	BOT_RTV_UINTP = 10,
	BOT_RTV_CHARP = 11,
	BOT_RTV_UCHARP = 12,
	BOT_RTV_CCHAR = 13,
	BOT_RTV_STR = 14,
	BOT_RTV_BLOB = 15,
	BOT_RTV_REAL = 16,
	BOT_RTV_MICS = 17,  //MICSYM
	BOT_RTV_MACS = 18,  //MACSYM
	BOT_RTV_SCRPT = 19, //BOT_SCRPT
	BOT_RTV_ARG = 20,   //BOT_ARG
	BOT_RTV_SES = 21,   //BOT_SESSION
	BOT_RTV_VAR = 22,   //BOT_VAR_T,
	BOT_RTV_ASINT = 51,
	BOT_RTV_ASLINT = 52,
	BOT_RTV_ASLLINT = 53,
	BOT_RTV_AUINT = 54,
	BOT_RTV_AULINT = 55,
	BOT_RTV_AULLINT = 56,
	BOT_RTV_ACHAR = 57,
	BOT_RTV_AUCHAR = 58,
	BOT_RTV_ASINTP = 59,
	BOT_RTV_AUINTP = 60,
	BOT_RTV_ACHARP = 61,
	BOT_RTV_AUCHARP = 62,
	BOT_RTV_ACCHAR = 63,
	BOT_RTV_ASTR = 64,
	BOT_RTV_ABLOB = 65,
	BOT_RTV_AREAL = 66,
	BOT_RTV_AMICS = 67, //array MICSYM
	BOT_RTV_AMACS = 68, //array MACSYM
	BOT_RTV_ASCRPT = 69,//array BOT_SCRPT
	BOT_RTV_AARG = 70,  //array BOT_ARG
	BOT_RTV_ASES = 71,  //array BOT_SESSION
	BOT_RTV_AVAR = 72,  //array BOT_VAR_T
	BOT_RTV_VSINT = 73,
	BOT_RTV_VSLINT = 74,
	BOT_RTV_VSLLINT = 75,
	BOT_RTV_VUINT = 76,
	BOT_RTV_VULINT = 77,
	BOT_RTV_VULLINT = 78,
	BOT_RTV_VCHAR = 79,
	BOT_RTV_VUCHAR = 80,
	BOT_RTV_VCCHAR = 81,
	BOT_RTV_VSTR = 82,
	BOT_RTV_VREAL = 83,
	BOT_RTV_VBLOB = 84,
	BOT_RTV_VMICS = 85,  //std::vector<MICSYM>
	BOT_RTV_VMACS = 86,  //std::vector<MACSYM>
	BOT_RTV_VSCRPT = 87, //std::vector<BOT_SCRPT>
	BOT_RTV_VARG = 88,   //std::vector<BOT_ARG>
	BOT_RTV_VSES = 89,   //std::vector<BOT_SESSION>
	BOT_RTV_VVAR = 90,   //std::vector<BOT_VAR_T>
	BOT_RTV_MAX = SCHAR_MAX
};

/* priority levels for threads */
enum bot_mtx_prio
{
	BOT_STND_PRIO = 1,
	BOT_FO_PRIO = 2,
	BOT_FOUT_PRIO = 3,
	BOT_DBO_PRIO = 4,
	BOT_DBOUT_PRIO = 5,
	BOT_THR_PRIO = 6,
	BOT_MAX_PRIO = 7
};

/* mutex values associated with global objects threads can access */
enum bot_strt_mtx
{
	MTX_REQ = 0,
	MTX_C = 1,
	MTX_CV = 2,
	MTX_LOG = 3,
	MTX_O = 4,
	MTX_I = 5,
	MTX_DBC = 6,
	MTX_PEND = 7,
	MTX_TTS = 8,
	MTX_DBL = 9,
	MTX_FO = 10,
	MTX_TRAT = 11,
	MTX_STRT = 12,
	MTX_FCON = 13,
	MTX_FPAD = 14,
	MTX_BTIM = 15,
	MTX_DMAP = 16,
	MTX_FTYPE = 17,
	MTX_STYPE = 18,
	MTX_PORTS = 19,
	MTX_PCL = 20,
	MTX_DBG = 21,
	MTX_PRC = 22,
	MTX_CIPS = 23,
	MTX_BIPS = 24,
	MTX_SES = 25,
	MTX_VPKO = 26,
	MTX_VPKI = 27,
	MTX_SVPKO = 28,
	MTX_SVPKI = 29,
	MTX_MAX = SCHAR_MAX
};

typedef struct bot_blk
{
	size_t siz;
	_char* blk;

	bot_blk(_char op = 0, _char* nb = NULL, size_t nlen = 0)
	{
		siz = 0;
		blk = NULL;

		if (nb)
		{
			_char trm = '\0';
			siz = nlen;

			if (!siz)
			{
				siz = bot_strlen(nb);
			}

			if (siz && siz < BOT_FILESIZE_MAX)
			{
				blk = (_char*)malloc(siz + 2);

				if (blk)
				{
					memcpy((void*)&blk[0], (void*)&op, sizeof(_char));
					memcpy((void*)&blk[siz + 1], (void*)&trm, sizeof(_char));

					for (size_t x = 1; x < siz + 1; x++)
					{
						memcpy((void*)&blk[x], (void*)&nb[x - 1], sizeof(ulint));
					}
				}
			}
			else
			{
				siz = 0;
			}
		}
	}
	~bot_blk()
	{
		if (blk)
		{
			if (siz > 1)
			{
				while (siz)
				{
					blk[siz] = 0;
					siz--;
				}
				_char* nblk = (_char*)realloc(blk, 1);

				if (nblk)
				{
					blk = nblk;
				}
			}
			free(blk);
		}
	}

}BOT_BLK;

class bot_vblko
{

public:

	size_t siz;
	carr_64 servc;
	carr_64 addr;
	_char ack;
	bot_vblko* nxt;
	_char* blk;

	void Clear()
	{
		ack = 0;
		bot_strclr(addr.carr);
		bot_strclr(servc.carr);
		ClearBlk();
	}
	void ClearBlk()
	{
		if (blk)
		{
			if (siz > 1)
			{
				while (siz)
				{
					blk[siz] = 0;
					siz--;
				}
				_char* nblk = (_char*)realloc(blk, 1);

				if (nblk)
				{
					blk = nblk;
				}
			}
			free(blk);
		}
	}
	void SetBlk(_char* ndat = 0, size_t nsiz = 0)
	{
		if (ndat && nsiz && nsiz < BOT_FILESIZE_MAX)
		{
			if (!blk)
			{
				blk = (_char*)malloc(nsiz + sizeof(_char));
			}
			else
			{
				_char* nblk = (_char*)realloc(blk, nsiz + sizeof(_char));

				if (nblk)
				{
					blk = nblk;
				}
			}

			if (blk)
			{
				_char trm = '\0';
				memcpy((void*)blk, (void*)ndat, nsiz);
				memcpy((void*)&blk[nsiz], (void*)&trm, sizeof(_char));
				siz = nsiz;
			}
		}
	}
	sint Add(_char a = 0, ...)
	{
		_char trm = '\0';
		bool done = false;
		va_list args;
		va_start(args, a);

		while (!done)
		{
			_char vt = va_arg(args, _char);

			switch (vt)
			{
			case BOT_RTV_SINT:
			{
				sint inv = va_arg(args, sint);
				sint xv = htons(inv);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(sint) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(sint));
					siz += (sizeof(sint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_SLINT:
			{
				slint inv = va_arg(args, slint);
				slint xv = htonl(inv);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(slint) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(slint));
					siz += (sizeof(slint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_SLLINT:
			{
				sllint inv = va_arg(args, sllint);
				sllint xv = htonll(inv);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(sllint) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(sllint));
					siz += (sizeof(sllint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_UINT:
			{
				uint inv = va_arg(args, uint);
				uint xv = htons(inv);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(uint) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(uint));
					siz += (sizeof(uint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_ULINT:
			{
				ulint inv = va_arg(args, ulint);
				ulint xv = htonl(inv);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(ulint) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(ulint));
					siz += (sizeof(ulint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_ULLINT:
			{
				ullint inv = va_arg(args, ullint);
				ullint xv = htonll(inv);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(ullint) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(ullint));
					siz += (sizeof(ullint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_REAL:
			{
				float* inv = va_arg(args, float*);
				BOT_FTIA nia(inv);
				slint xv = htonl(nia.a[0]);
				_char* nblk = (_char*)realloc(blk, siz + ((sizeof(slint) * 2) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(slint));
					siz += (sizeof(slint));
					xv = htonl(nia.a[1]);
					memcpy((void*)&nblk[siz], (void*)&xv, sizeof(slint));
					siz += (sizeof(slint));
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_CHAR:
			{
				_char inv = va_arg(args, _char);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(_char) + sizeof(_char) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&inv, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char)); // terminates our string
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_UCHAR:
			{
				u_char inv = va_arg(args, u_char);
				_char* nblk = (_char*)realloc(blk, siz + (sizeof(_char) + sizeof(u_char) + sizeof(_char)));

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&inv, sizeof(u_char));
					siz += sizeof(u_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char)); // terminates our string
					siz += sizeof(u_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_CHARP:
			{
				_char* inv = va_arg(args, _char*);
				size_t ln = bot_strlen(inv);
				_char* nblk = (_char*)realloc(blk, siz + ln + sizeof(_char) + sizeof(_char)); // extra element to terminate our string

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)inv, ln * sizeof(_char));
					siz += ln * sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char)); // terminates our string
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_UCHARP:
			{
				u_char* inv = va_arg(args, u_char*);
				size_t ln = bot_ustrlen(inv);
				_char* nblk = (_char*)realloc(blk, siz + ln + sizeof(_char) + sizeof(_char)); // extra element to terminate our string

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)inv, ln * sizeof(u_char));
					siz += ln * sizeof(u_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char)); // terminates our string
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			case BOT_RTV_STR:
			{
				std::string* inv = va_arg(args, std::string*);
				_char* nblk = (_char*)realloc(blk, siz + inv->length() + sizeof(_char) + sizeof(_char)); // extra element to terminate our string

				if (nblk)
				{
					memcpy((void*)&nblk[siz], (void*)&vt, sizeof(_char));
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)inv->c_str(), inv->length());
					siz += inv->length();
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char)); // terminates our string
					siz += sizeof(_char);
					memcpy((void*)&nblk[siz], (void*)&trm, sizeof(_char));
					blk = nblk;
				}
				break;
			}
			default:
			{
				done = true;
				break;
			}
			}
		}
		va_end(args);
		return (sint)siz;
	}
	bot_vblko(_char op = 0, c_char* naddr = 0, c_char* nport = 0, _char nack = 0)
	{
		ack = nack;
		siz = 0;

		if (naddr)
		{
			bot_sprintf(addr.carr, addr.siz, "%s", naddr);
		}

		if (nport)
		{
			bot_sprintf(servc.carr, servc.siz, "%s", nport);
		}
		blk = NULL;
		nxt = NULL;
		blk = (_char*)malloc(2);
		
		if (blk)
		{
			siz = 1;
			blk[0] = op;
			blk[1] = '\0';
		}
	}
	~bot_vblko()
	{
		if (blk)
		{
			Clear();
		}
	}
private:

};
class bot_vblki
{
public:
	size_t siz;
	carr_64 servc;
	carr_64 addr;
	_char ack;
	bot_vblki* nxt;
	_char* blk;

	void Clear()
	{
		ack = 0;
		bot_strclr(servc.carr);
		bot_strclr(addr.carr);
		ClearBlk();
	}
	void ClearBlk()
	{
		if (blk)
		{
			if (siz > 1)
			{
				while (siz)
				{
					blk[siz] = 0;
					siz--;
				}
				_char* nblk = (_char*)realloc(blk, 1);

				if (nblk)
				{
					blk = nblk;
				}
			}
			free(blk);
		}
	}
	void SetBlk(_char* ndat = 0, size_t nsiz = 0)
	{
		if (ndat && nsiz && nsiz < BOT_FILESIZE_MAX)
		{
			if (!blk)
			{
				blk = (_char*)malloc(nsiz + sizeof(_char));
			}
			else
			{
				_char* nblk = (_char*)realloc(blk, nsiz + sizeof(_char));

				if (nblk)
				{
					blk = nblk;
				}
			}

			if (blk)
			{
				siz = nsiz;
				_char trm = '\0';
				memcpy((void*)&blk[0], (void*)&ndat[0], sizeof(_char));
				memcpy((void*)&blk[nsiz], (void*)&trm, sizeof(_char));
				size_t x = sizeof(_char);
				size_t y = sizeof(_char);

				while (x < nsiz && y < siz)
				{
					switch (ndat[x])
					{
					case BOT_RTV_SINT:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						sint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(sint));
						sint nv = ntohs(xv);
						memcpy((void*)&blk[y], (void*)&nv, sizeof(sint));
						x += sizeof(sint);
						y += sizeof(sint);
						break;
					}
					case BOT_RTV_SLINT:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						slint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(slint));
						slint nv = ntohl(xv);
						memcpy((void*)&blk[y], (void*)&nv, sizeof(slint));
						x += sizeof(slint);
						y += sizeof(slint);
						break;
					}
					case BOT_RTV_SLLINT:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						sllint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(sllint));
						sllint nv = ntohll(xv);
						memcpy((void*)&blk[y], (void*)&nv, sizeof(sllint));
						x += sizeof(sllint);
						y += sizeof(sllint);
						break;
					}
					case BOT_RTV_UINT:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						uint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(uint));
						uint nv = ntohs(xv);
						memcpy((void*)&blk[y], (void*)&nv, sizeof(uint));
						x += sizeof(uint);
						y += sizeof(uint);
						break;
					}
					case BOT_RTV_ULINT:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						ulint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(ulint));
						ulint nv = ntohl(xv);
						memcpy((void*)&blk[y], (void*)&nv, sizeof(ulint));
						x += sizeof(ulint);
						y += sizeof(ulint);
						break;
					}
					case BOT_RTV_ULLINT:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						ullint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(ullint));
						ullint nv = ntohll(xv);
						memcpy((void*)&blk[y], (void*)&nv, sizeof(ullint));
						x += sizeof(ullint);
						y += sizeof(ullint);
						break;
					}
					case BOT_RTV_REAL:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						slint xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(slint));
						slint av = ntohl(xv);
						x += sizeof(slint);
						xv = 0;
						memcpy((void*)&xv, (void*)&ndat[x], sizeof(slint));
						slint bv = ntohl(xv);
						BOT_IATF nf(av, bv);
						memcpy((void*)&blk[y], (void*)&nf.a, sizeof(float));
						x += sizeof(slint);
						y += sizeof(float);

						_char* nblk = (_char*)realloc(blk, siz - (x - y) + sizeof(_char));

						if (nblk)
						{
							blk = nblk;
							siz -= (x - y);
							memcpy((void*)&blk[siz], (void*)&trm, sizeof(_char));
						}
						break;
					}
					case BOT_RTV_CHAR:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						memcpy((void*)&blk[y], (void*)&trm, sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						break;
					}
					case BOT_RTV_UCHAR:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(u_char));
						x += sizeof(u_char);
						y += sizeof(_char);
						memcpy((void*)&blk[y], (void*)&trm, sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						break;
					}
					case BOT_RTV_CHARP:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						size_t ln = bot_strlen(&ndat[x]);
						memcpy((void*)&blk[y], (void*)&ndat[x], ln * sizeof(_char));
						x += sizeof(_char) * ln;
						y += sizeof(_char) * ln;
						memcpy((void*)&blk[y], (void*)&trm, sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						break;
					}
					case BOT_RTV_UCHARP:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						size_t ln = bot_strlen(ndat);
						memcpy((void*)&blk[y], (void*)&ndat[x], ln * sizeof(u_char));
						x += sizeof(u_char) * ln;
						y += sizeof(u_char) * ln;
						memcpy((void*)&blk[y], (void*)&trm, sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						break;
					}
					case BOT_RTV_STR:
					{
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						size_t ln = bot_strlen(&ndat[x]);
						memcpy((void*)&blk[y], (void*)&ndat[x], sizeof(_char) * ln);
						x += sizeof(_char) * ln;
						y += sizeof(_char) * ln;
						memcpy((void*)&blk[y], (void*)&trm, sizeof(_char));
						x += sizeof(_char);
						y += sizeof(_char);
						break;
					}
					default:
					{
						x = nsiz;
						break;
					}
					}
				}
			}
		}
	}
	bot_vblki(_char* ndat = 0, size_t nsiz = 0, c_char* naddr = 0, c_char* nport = 0, _char nack = 0)
	{
		ack = nack;
		siz = 0;

		if (naddr)
		{
			bot_sprintf(addr.carr, addr.siz, "%s", naddr);
		}

		if (nport)
		{
			bot_sprintf(servc.carr, servc.siz, "%s", nport);
		}

		blk = NULL;
		nxt = NULL;
		SetBlk(ndat, nsiz);
	}
	~bot_vblki()
	{
		Clear();
	}
private:
};
class bot_svblko
{

public:

	size_t siz;
	carr_64 servc;
	carr_64 addr;
	_char ack;
	bot_svblko* nxt;
	_char* blk;

	void Clear()
	{
		ack = 0;
		bot_strclr(addr.carr);
		bot_strclr(servc.carr);
		ClearBlk();
	}
	void ClearBlk()
	{
		if (blk)
		{
			if (siz > 1)
			{
				while (siz)
				{
					blk[siz] = 0;
					siz--;
				}
				_char* nblk = (_char*)realloc(blk, 1);

				if (nblk)
				{
					blk = nblk;
				}
			}
			free(blk);
		}
	}
	void SetBlk(_char* ndat = 0, size_t nsiz = 0, slint svb = BOT_SEEDV_B, slint svc = BOT_SEEDV_C)
	{
		size_t xsiz = nsiz * sizeof(slint);

		if (ndat && xsiz && xsiz < BOT_FILESIZE_MAX)
		{
			if (!blk)
			{
				blk = (_char*)malloc(xsiz + sizeof(_char));
			}
			else
			{
				_char* nblk = (_char*)realloc(blk, xsiz + sizeof(_char));

				if (nblk)
				{
					blk = nblk;
				}
			}

			if (blk)
			{
				memcpy((void*)&blk[0], (void*)&ndat[0], sizeof(_char));
				_char trm = '\0';
				slint val = 0;
				size_t y = sizeof(_char);

				for (size_t x = sizeof(_char); x < nsiz; x += sizeof(_char))
				{
					val = htonl((slint)((slint)ndat[x] * (svc * svb)));
					memcpy((void*)&blk[y], (void*)&val, sizeof(slint));
					y += sizeof(slint);
				}

				while (y < xsiz)
				{
					memcpy((void*)&blk[y], (void*)&trm, sizeof(_char));
					y++;
				}
				memcpy((void*)&blk[xsiz], (void*)&trm, sizeof(_char));
				siz = xsiz;
			}
		}
	}
	bot_svblko(_char op = 0, c_char* naddr = 0, c_char* nport = 0, _char nack = 0)
	{
		ack = nack;
		siz = 0;

		if (naddr)
		{
			bot_sprintf(addr.carr, addr.siz, "%s", naddr);
		}

		if (nport)
		{
			bot_sprintf(servc.carr, servc.siz, "%s", nport);
		}
		blk = NULL;
		nxt = NULL;
		blk = (_char*)malloc(2);

		if (blk)
		{
			siz = 1;
			blk[0] = op;
			blk[1] = '\0';
		}
	}
	~bot_svblko()
	{
		if (blk)
		{
			Clear();
		}
	}
private:

};
class bot_svblki
{
public:
	size_t siz;
	carr_64 servc;
	carr_64 addr;
	_char ack;
	bot_svblki* nxt;
	_char* blk;

	void Clear()
	{
		ack = 0;
		bot_strclr(servc.carr);
		bot_strclr(addr.carr);
		ClearBlk();
	}
	void ClearBlk()
	{
		if (blk)
		{
			if (siz > 1)
			{
				while (siz)
				{
					blk[siz] = 0;
					siz--;
				}
				_char* nblk = (_char*)realloc(blk, 1);

				if (nblk)
				{
					blk = nblk;
				}
			}
			free(blk);
		}
	}
	void SetBlk(_char* ndat = 0, size_t nsiz = 0, slint svb = BOT_SEEDV_B, slint svc = BOT_SEEDV_C)
	{
		if (ndat && nsiz > sizeof(slint) && nsiz < BOT_FILESIZE_MAX)
		{
			if (!blk)
			{
				blk = (_char*)malloc((nsiz / sizeof(slint)) + sizeof(_char));
			}
			else
			{
				_char* nblk = (_char*)realloc(blk, (nsiz / sizeof(slint)) + sizeof(_char));

				if (nblk)
				{
					blk = nblk;
				}
			}

			if (blk)
			{
				siz = nsiz / sizeof(slint);
				_char trm = '\0';
				memcpy((void*)&blk[0], (void*)&ndat[0], sizeof(_char));
				size_t x = sizeof(_char);
				size_t y = sizeof(_char);

				while (x < nsiz && y < siz)
				{
					slint val = 0;
					memcpy((void*)&val, (void*)&ndat[x], sizeof(slint));
					val = ntohl(val);
					_char ival = (_char)(val / (svc * svb));
					x += sizeof(slint);
					memcpy((void*)&blk[y], (void*)&ival, sizeof(_char));
					y += sizeof(_char);
				}
				memcpy((void*)&blk[siz], (void*)&trm, sizeof(_char));
			}
		}
	}
	bot_svblki(_char* ndat = 0, size_t nsiz = 0, c_char* naddr = 0, c_char* nport = 0, _char nack = 0)
	{
		ack = nack;
		siz = 0;

		if (naddr)
		{
			bot_sprintf(addr.carr, addr.siz, "%s", naddr);
		}

		if (nport)
		{
			bot_sprintf(servc.carr, servc.siz, "%s", nport);
		}

		blk = NULL;
		nxt = NULL;
		SetBlk(ndat, nsiz);
	}
	~bot_svblki()
	{
		Clear();
	}
private:
};
enum bot_ops
{
	BOT_OP_MIN = SCHAR_MIN,
	BOT_OP_TST = 1,
	BOT_OP_TSTR = 2,
	BOT_OP_ACK = 6,
	BOT_OP_KNK = 9,
	BOT_OP_COM = 15,
	BOT_OP_FHD = 23,
	BOT_OP_RSTR = 36,
	BOT_OP_NPT = 47,
	BOT_OP_ESTA = 58,
	BOT_OP_GDAT = 59,
	BOT_OP_NDAT = 60,
	BOT_OP_SDAT = 61,
	BOT_OP_WDAT = 62,
	BOT_OP_VDAT = 69,
	BOT_OP_ESTB = 77,
	BOT_OP_SIZ = 99,
	BOT_OP_SEC = 101,
	BOT_OP_SES = 103,
	BOT_OP_ESTC = 105,
	BOT_OP_FCK = 107,
	BOT_OP_CLS = 115,
	BOT_OP_MAX = SCHAR_MAX - 1
};

typedef struct bot_tst_pkt
{
	_char op;
	size_t dlen;
	_char dat[BOT_TST_PKL];

	bot_tst_pkt(_char nop = 0, _char* ind = 0, size_t ndlen = 0)
	{
		op = nop;
		dlen = 0;

		if (ind && ndlen < BOT_TST_PKL)
		{
			dlen = ndlen;
			memcpy((void*)dat, (void*)ind, dlen);
		}
		_char trm = '\0';
		memcpy((void*)&dat[dlen], (void*)&trm, sizeof(_char));
	}

	bot_tst_pkt(_char nop = 0, c_char* ind = 0, size_t ndlen = 0)
	{
		op = nop;
		dlen = 0;

		if (ind && ndlen < BOT_TST_PKL)
		{
			dlen = ndlen;
			memcpy((void*)dat, (void*)ind, dlen);
		}
		_char trm = '\0';
		memcpy((void*)&dat[dlen], (void*)&trm, sizeof(_char));
	}

}BOT_TST_PKT;

typedef struct bot_hdr_pkt
{
	_char op[4]{ 0 };
	size_t siz;
	slint ka;

	bot_hdr_pkt(_char nop = 0, size_t nsiz = 0, slint nka = 0, _char nack = 0)
	{
		op[0] = nop;
		op[3] = nack;
		siz = htonl(nsiz);
		ka = htonl(nka);
	}

}BOT_HDR_PKT;

enum bot_proc_mems
{
	BOT_PROC_LID = 0,
	BOT_PROC_NM = 1,
	BOT_PROC_PID = 2,
	BOT_PROC_SIN = 3,
	BOT_PROC_PIN = 4,
	BOT_PROC_MAX = 5
};

#ifdef _WIN32
class bot_proc
{
public:

	sint lid;
	slint pid;
	ulint f;
	std::string anm;
	void* env;
	STARTUPINFOA sinfo;
	PROCESS_INFORMATION pinfo;

	void Clear()
	{
		lid = -1;
		f = 0;
		pid = 0;
		env = NULL;
		anm.clear();
		memset((void*)&sinfo, 0, sizeof(STARTUPINFOA));
		memset((void*)&pinfo, 0, sizeof(PROCESS_INFORMATION));
	}
	void Renew(bot_proc* np = 0)
	{
		Clear();

		if (!np)
		{
			return;
		}

		lid = np->lid;
		f = np->f;
		env = np->env;
		anm.append(np->anm.c_str());
		memcpy((void*)&sinfo, (void*)&np->sinfo, sizeof(STARTUPINFOA));
		sinfo.cb = sizeof(sinfo);
		memcpy((void*)&pinfo, (void*)&np->pinfo, sizeof(PROCESS_INFORMATION));
		pid = np->pid;
	}
	void Close()
	{
		if (pinfo.hThread)
		{
			CloseHandle(pinfo.hThread);
		}
		if (pinfo.hProcess)
		{
			CloseHandle(pinfo.hProcess);
		}
	}
	bot_proc(c_char* nanm = 0, ulint nflags = 0, ulint clrs = 0, void* nenv = 0)
	{
		if (nanm)
		{
			f = nflags;
			size_t ln = bot_cstrlen(nanm);

			if (ln < 4096)
			{
				memset((void*)&sinfo, 0, sizeof(STARTUPINFOA));
				sinfo.dwFillAttribute = clrs;

				for (size_t x = 0; x < ln; x++)
				{
					anm.push_back(nanm[x]);
				}
				sinfo.cb = sizeof(sinfo);
			}
			if (nenv)
			{
				env = nenv;
			}
			else
			{
				env = NULL;
			}
		}
	}

private:

};
#else
class bot_proc
{
public:
	sint lid;
	slint pid;
	ulint f;
	std::string anm;
	void* env;
	slint sinfo[21];
	slint pinfo;

	void Clear()
	{
		lid = -1;
		pid = 0;
		f = 0;
		env = NULL;
		anm.clear();
		memset((void*)sinfo, 0, sizeof(slint) * 21);
		pinfo = 0;
	}
	void Renew(bot_proc* np = 0)
	{
		Clear();

		if (!np)
		{
			return;
		}

		lid = np->lid;
		pid = np->pid;
		f = np->f;
		env = np->env;
		anm.append(np->anm.c_str());
		memcpy((void*)sinfo, (void*)np->sinfo, sizeof(slint) * 21);
		pinfo = np->pinfo;
	}

	bot_proc(c_char* nanm = 0, ulint nflags = 0, slint nsinfo[21] = 0, void* nenv = 0)
	{
		if (nanm)
		{
			f = nflags;
			size_t ln = bot_cstrlen(nanm);

			if (ln < 4096)
			{
				for (size_t x = 0; x < ln; x++)
				{
					anm.push_back(nanm[x]);
				}
			}

			if (nsinfo)
			{
				memcpy((void*)sinfo, (void*)nsinfo, 21);
			}

			if (nenv)
			{
				env = nenv;
			}
			else
			{
				env = NULL;
			}
		}
	}

private:

};
#endif

class bot_proc_m
{
public:

	sint lid;
	std::string anm;
	slint pid;

	void Clear() { lid = -1; anm.clear(); pid = 0; }
	void Renew(bot_proc* np = 0)
	{
		Clear();

		if (np)
		{
			lid = np->lid;
			anm.append(np->anm.c_str());
			pid = np->pid;
		}
	}
	void Renew(bot_proc_m* np = 0)
	{
		Clear();

		if (np)
		{
			lid = np->lid;
			anm.append(np->anm.c_str());
			pid = np->pid;
		}
	}

	bot_proc_m(bot_proc* np = 0)
	{
		lid = -1;
		anm.clear();
		pid = 0;

		if (np)
		{
			lid = np->lid;
			anm.append(np->anm.c_str());
			pid = np->pid;
		}
	}

private:

};

class bot_procs
{
public:

	std::vector<bot_proc> dvec;
	std::vector<bot_proc_m> mvec;

	bot_procs() { dvec.clear(); mvec.clear(); }

private:

};

enum bot_thr_qlvl
{
	BOT_THRQ_CONS = 1,
	BOT_THRQ_DBM = 2,
	BOT_THRQ_LOG = 3,
	BOT_THRQ_MAX = 4
};

class _mtx
{
public:

	pthread_mutexattr_t mtx_attr;
	pthread_mutex_t mtx;

	_mtx(pthread_mutexattr_t n_mtx_attr = 0) { mtx_attr = n_mtx_attr; sint px = pthread_mutexattr_init(&mtx_attr); if (!px) { px = pthread_mutex_init(&mtx, &mtx_attr); } else { std::cout << "pthread_mutexattr_init err:" << px << std::endl; } }
	~_mtx() { DESTROY(); }
#if (BOT_FILE_TLOCK == 1)
	sint Lock() { return pthread_mutex_trylock(&mtx); }
#else
	sint Lock() { return pthread_mutex_lock(&mtx); }
#endif
	sint Unlock() { return pthread_mutex_unlock(&mtx); }
	void Renew(pthread_mutexattr_t n_mtx_attr = 0) { DESTROY(); mtx_attr = n_mtx_attr; sint px = pthread_mutexattr_init(&mtx_attr); if (!px) { px = pthread_mutex_init(&mtx, &mtx_attr); } }
	
private:

	void DESTROY() { sint ret = pthread_mutexattr_destroy(&mtx_attr); if (!ret) { ret = pthread_mutex_destroy(&mtx); } }
};

enum held_mtx_mems
{
	HMTX_W_MTX = 0,
	HMTX_LOCK = 1,
	HMTX_LID = 2,
	HMTX_TIME = 3,
	HMTX_MEMS = 4,
	HMTX_MAX = 5
};

class HELD_MTX
{
public:

	bool locked;
	sint w_mtx;
	sint lid;
	std::vector<sint> h_mems;
	std::vector<sint> m_mems;
	void Clear()
	{
		locked = false;
		w_mtx = lid = -1;

		if (!h_mems.empty())
		{
			h_mems.clear();
		}
		if (!m_mems.empty())
		{
			m_mems.clear();
		}
	}
	void Renew(HELD_MTX* val = 0)
	{
		if (!val)
		{
			return;
		}

		Clear();
		w_mtx = val->w_mtx;
		lid = val->lid;
		locked = val->locked;

		for (uint x = 0; x < val->h_mems.size(); x++)
		{
			if (val->h_mems[x] > -1)
			{
				h_mems.push_back(val->h_mems[x]);
			}
		}
		for (uint x = 0; x < val->m_mems.size(); x++)
		{
			if (val->m_mems[x] > -1)
			{
				m_mems.push_back(val->m_mems[x]);
			}
		}
	}
	HELD_MTX(sint nw_mtx = -1, sint nlid = -1, bool nlocked = false) { w_mtx = nw_mtx; lid = nlid; locked = nlocked; }

private:

};

enum lok_req_mems
{
	BOT_REQ_LID = 0,
	BOT_REQ_FID = 1,
	BOT_REQ_GMTX = 2,
	BOT_REQ_ELE = 3,
	BOT_REQ_META = 4,
	BOT_REQ_TIME = 5,
	BOT_REQ_MAX = 7
};

class lok_req
{

public:

	sint lid;
	sint fid;
	sint gmtx;
	sint ele;
	sint is_meta;
	std::chrono::steady_clock::time_point at_time;
	void Clear(bool timetoo = false)
	{
		lid = fid = gmtx = ele = is_meta = -1;

		if (timetoo)
		{
			at_time = std::chrono::steady_clock::now();
		}
	}
	void Renew(lok_req* nreq = 0)
	{
		if (!nreq)
		{
			return;
		}
		Clear();

		at_time = nreq->at_time;
		fid = nreq->fid;
		gmtx = nreq->gmtx;
		ele = nreq->ele;
		is_meta = nreq->is_meta;
		lid = nreq->lid;
	}
	lok_req(sint nele = -1, sint wmtx = -1, sint nid = -1, sint nmeta = -1)
	{
		at_time = std::chrono::steady_clock::now();
		lid = -1;
		fid = nid;
		gmtx = wmtx;
		ele = nele;
		is_meta = nmeta;
	}

private:

};

class lok_defr
{

public:

	std::vector<lok_req> reqs;
	std::vector<std::vector<HELD_MTX>> held;
	std::vector<sint> held_ids;
	std::vector<std::chrono::steady_clock::time_point> held_t;
	std::vector<sint> held_p;

private:

};

typedef struct bot_sopt
{

public:

	sint sopt;
	sint proto;
	sint val;

	bot_sopt(sint nproto = -1, sint nopt = -1, sint nval = -1) { proto = nproto; sopt = nopt; val = nval; }

private:

}BOT_SOPT;

enum bot_port_mems
{
	BOT_PORT_LID = 1,
	BOT_PORT_PTN = 2,
	BOT_PORT_RPT = 3,
	BOT_PORT_PCL = 4,
	BOT_PORT_SOP = 5,
	BOT_PORT_XCL = 6,
	BOT_PORT_IPS = 7,
	BOT_PORT_OPS = 8,
	BOT_PORT_STP = 9,
	BOT_PORT_SCK = 10,
	BOT_PORT_KYA = 11,
	BOT_PORT_BDP = 12,
	BOT_PORT_SIG = 13,
	BOT_PORT_OAD = 14,
	BOT_PORT_MAX = 15
};

class bot_port
{

public:

	sint lid;
	sint portn;
	sint rport;
	sint proto;
	sint stype;
	sint signal;
	slint key_a;
	carr_64 ipstr;
	carr_64 oipstr;
	struct sockaddr_storage oaddr;

#ifdef _WIN32
	SOCKET sck;
#else
	sint sck;
#endif
	std::vector<BOT_SOPT> sopts;
	bool xcl;
	bool bndp;

	void Clear()
	{
		bndp = false;
		xcl = false;
		signal = 0;
		lid = portn = rport = proto = stype = -1;
		key_a = 0;
		bot_strclr(ipstr.carr);
		bot_strclr(oipstr.carr);
		sopts.clear();
		memset((void*)&oaddr, 0, sizeof(sockaddr_storage));

#ifdef _WIN32
		sck = INVALID_SOCKET;
#else
		FD_ZERO(sck);
#endif
	}
	void Renew(bot_port* nport = 0)
	{
		Clear();

		if (!nport)
		{
			return;
		}
		
		key_a = nport->key_a;
		sck = nport->sck;
		bndp = nport->bndp;
		stype = nport->stype;
		xcl = nport->xcl;
		signal = nport->signal;
		lid = nport->lid;
		portn = nport->portn;
		rport = nport->rport;
		proto = nport->proto;
		bot_sprintf(ipstr.carr, ipstr.siz, "%s", nport->ipstr.carr);
		bot_sprintf(oipstr.carr, oipstr.siz, "%s", nport->oipstr.carr);

		for (uint x = 0; x < nport->sopts.size(); x++)
		{
			sopts.push_back(nport->sopts[x]);
		}

		memcpy((void*)&oaddr, (void*)&nport->oaddr, sizeof(oaddr));
	}
	sint AddSOpt(BOT_SOPT* val = 0)
	{
		if (!val)
		{
			return -1;
		}
		if (sopts.size() < (size_t)BOTTHREAD_MAX)
		{
			size_t x = 0;

			while (x < sopts.size())
			{
				if (sopts[x].sopt == val->sopt && sopts[x].proto == val->proto)
				{
					if (val->sopt == SO_EXCLUSIVEADDRUSE && val->proto == SOL_SOCKET && (sint)val->val == 1)
					{
						if ((sint)val->val == 1)
						{
							if (!xcl)
							{
								xcl = true;
							}
						}
						else if ((sint)val->val == 0)
						{
							if (xcl)
							{
								xcl = false;
							}
						}
						else {}
					}
					else if (val->sopt == SO_REUSEADDR && val->proto == SOL_SOCKET)
					{
						if ((sint)val->val == 1)
						{
							if (xcl)
							{
								xcl = false;
							}
						}
						else if ((sint)val->val == 0)
						{
							if (!xcl)
							{
								xcl = true;
							}
						}
						else {}
					}
					else {}
					return (sint)x;
				}
				x++;
			}
			sopts.push_back(*val);
			return (sint)x;
		}
		return -1;
	}
	sint RemSOpt(BOT_SOPT* val = 0)
	{
		if (!val)
		{
			return -1;
		}
		sint ret = -1;
		if (sopts.size())
		{
			size_t x;
			for (x = 0; x < sopts.size(); x++)
			{
				if (sopts[x].sopt == val->sopt && sopts[x].proto == val->proto)
				{
					for (size_t y = x + 1; y < sopts.size(); y++)
					{
						sopts[y - 1] = sopts[y];
					}

					sopts.pop_back();

					if (ret)
					{
						ret = 0;
					}
				}
			}
		}
		return ret;
	}
	sint GeSOptCt() { return (sint)sopts.size(); }
	sint GetSopts(std::vector<BOT_SOPT>* rvec = 0, bool clear_first = false)
	{
		if (!rvec)
		{
			return -1;
		}

		if (clear_first)
		{
			rvec->clear();
		}

		for (uint x = 0; x < sopts.size(); x++)
		{
			rvec->push_back(sopts[x]);
		}
		return 0;
	}

	bot_port(sint nstype = -1, sint nprt = -1, sint nproto = -1, bool nxcls = false, bool bindp = false)
	{
		signal = 0;
		key_a = 0;
		bndp = bindp;
		xcl = nxcls;
		stype = nstype;
		proto = nproto;
		portn = nprt;
		rport = -1;
		sopts.clear();

#ifdef _WIN32
		sck = INVALID_SOCKET;
#else
		FD_ZERO(sck);
#endif
	}

	~bot_port() { Clear(); }
private:

};

enum bot_plug_mems
{
	BOT_PLUG_LID = 1,
	BOT_PLUG_ERR = 2,
	BOT_PLUG_BDP = 3,
	BOT_PLUG_SRV = 4,
	BOT_PLUG_CON = 5,
	BOT_PLUG_QSZ = 6,
	BOT_PLUG_PRT = 7,
	BOT_PLUG_RES = 8,
	BOT_PLUG_PTR = 9,
	BOT_PLUG_HNT = 10,
	BOT_PLUG_URL = 11,
	BOT_PLUG_ORL = 12,
	BOT_PLUG_FAM = 13,
	BOT_PLUG_SVC = 14,
	BOT_PLUG_MAX = 15
};

class bot_plug
{
public:

	sint lid;
	carr_256 emsg;
	bool isserv;
	sint con;
	sint qsiz;
	bot_port prt;
	struct addrinfo *res;
	struct addrinfo *ptr;
	struct addrinfo hints;
	carr_512 url;
	carr_512 ourl;
	carr_8 ifam;
	carr_64 servc;

	void Clear()
	{
		Close();
		lid = con = qsiz = -1;
		isserv = false;
		bot_strclr(emsg.carr);
		bot_strclr(url.carr);
		bot_strclr(ifam.carr);
		bot_strclr(servc.carr);
		res = ptr = 0;
		memset((void*)&hints, 0, sizeof(hints));
		prt.Clear();
	}

	void Renew(bot_plug* val = 0)
	{
		Clear();

		if (!val)
		{
			return;
		}

		lid = val->lid;
		con = val->con;
		qsiz = val->qsiz;
		isserv = val->isserv;
		res = val->res;
		ptr = val->ptr;
		memcpy((void*)&hints, (void*)&val->hints, sizeof(hints));
		prt.Renew(&val->prt);
		sint xc = bot_sprintf(emsg.carr, emsg.siz, "%s", val->emsg.carr);
		xc = bot_sprintf(url.carr, url.siz, "%s", val->url.carr);
		xc = bot_sprintf(ifam.carr, ifam.siz, "%s", val->ifam.carr);
		xc = bot_sprintf(servc.carr, servc.siz, "%s", val->servc.carr);
	}

	void Renew(c_char* naddr = 0, c_char* nservc = 0, sint ntyp = -1, bool nisserv = false)
	{
		Clear();
		memset(&hints, 0, sizeof(hints));

		if (nservc)
		{
			sint xc = bot_sprintf(servc.carr, servc.siz, "%s", nservc);
		}
		if (naddr)
		{
			sint xc = bot_sprintf(url.carr, url.siz, "%s", naddr);
		}

		isserv = nisserv;
		hints.ai_socktype = ntyp;
		res = ptr = NULL;
		con = -1;
	}
	sint Open(sint flg = AI_PASSIVE, bool nbndp = false)
	{
		if (isserv && !nbndp)
		{
			return INT32_MIN;
		}

		if (!isserv)
		{
			prt.bndp = nbndp;
			hints.ai_flags = flg;
		}
		else
		{
			if (!prt.bndp)
			{
				return INT32_MIN;
			}
		}

		if (strlen(servc.carr))
		{
			if (strlen(url.carr))
			{
				con = getaddrinfo(url.carr, servc.carr, &hints, &res);
			}
			else
			{
				con = getaddrinfo(NULL, servc.carr, &hints, &res);
			}
		}
		else
		{
			if (strlen(url.carr))
			{
				con = getaddrinfo(url.carr, NULL, &hints, &res);
			}
			else
			{
				con = getaddrinfo(NULL, servc.carr, &hints, &res);
			}
		}

		if (!con && res != NULL)
		{
			ptr = res;
			inet_ntop(ptr->ai_family, GetAddr(ptr->ai_addr), prt.ipstr.carr, INET6_ADDRSTRLEN);

			if (ptr->ai_family == AF_INET)
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "IPv4");
			}
			else if (ptr->ai_family == AF_INET6)
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "IPv6");
			}
			else if (ptr->ai_family == AF_NETBIOS)
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "NETBIOS");
			}
			else
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "IPvU");
			}
		}
		else
		{
			PError(con);
		}
		return con;
	}

	sint Next()
	{
		if (con < 0)
		{
			return INT32_MIN;
		}
		if (ptr->ai_next != NULL)
		{
			ptr = ptr->ai_next;
			inet_ntop(ptr->ai_family, GetAddr(ptr->ai_addr), prt.ipstr.carr, prt.ipstr.siz);

			if (ptr->ai_family == AF_INET)
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "IPv4");
			}
			else if (ptr->ai_family == AF_INET6)
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "IPv6");
			}
			else if (ptr->ai_family == AF_NETBIOS)
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "NETBIOS");
			}
			else
			{
				sint xc = bot_sprintf(ifam.carr, ifam.siz, "IPvU");
			}
			return 0;
		}
		return INT32_MIN;
	}
	
#ifdef _WIN32

	sint AddSOpt(sint popt = -1, sint sopt = -1, _char* val = 0, size_t vlen = 0)
	{
		if (sopt < 0 || popt < 0 || !val)
		{
			return INT32_MIN;
		}
		
		sint ret = setsockopt(prt.sck, popt, sopt, val, vlen);

		if (ret < 0)
		{
			PError();
			return ret;
		}

		BOT_SOPT nopt(popt, sopt, (sint)val);
		ret = prt.AddSOpt(&nopt);
		return ret;
	}
	sint Sock(bool xclsck = false)
	{
		if (con < 0)
		{
			return INT32_MIN;
		}
		
		if (ptr->ai_family == AF_INET)
		{
			prt.sck = socket(PF_INET, ptr->ai_socktype, prt.proto);
		}
		else if (ptr->ai_family == AF_INET6)
		{
			prt.sck = socket(PF_INET6, ptr->ai_socktype, prt.proto);
		}
		else if (ptr->ai_family == AF_UNSPEC)
		{
			prt.sck = socket(PF_UNSPEC, ptr->ai_socktype, prt.proto);
		}
		else {}

		if (prt.sck == INVALID_SOCKET)
		{
			PError();
			return INT32_MIN;
		}

		sint ret = 0;

		if (prt.bndp)
		{
			sint sopt = -1;
			if (xclsck)
			{
				prt.xcl = true;
				sopt = (sint)SO_EXCLUSIVEADDRUSE;
			}
			else
			{
				prt.xcl = false;
				sopt = (sint)SO_REUSEADDR;
			}
			sint opt = 1;
			ret = AddSOpt(SOL_SOCKET, sopt, (_char*)&opt, sizeof(sint));

			if (ret < 0)
			{
				PError();
				return ret;
			}
			
			ret = bind(prt.sck, ptr->ai_addr, ptr->ai_addrlen);

			if (ret < 0)
			{
				PError();
				return ret;
			}
			freeaddrinfo(res);
		}
		con = 1;
		return ret;
	}
#else
	sint AddSOpt(sint popt = -1, sint sopt = -1, sint val = -1)
	{
		if (sopt < 0 || popt < 0)
		{
			return INT32_MIN;
		}
		
		sint ret = setsockopt(prt.sck, popt, sopt, &val, sizeof(val));

		if (ret < 0)
		{
			perror(esmg.carr);
			return ret;
		}

		BOT_SOPT nopt(popt, sopt, val);
		ret = prt.AddSOpt(*nopt);
		return ret;
	}

	sint Sock(bool xclsck = true)
	{
		if (con < 0)
		{
			return INT32_MIN;
		}
		if (prt.fam == AF_INET)
		{
			prt.sck = socket(PF_INET, hints.ai_socktype, prt.proto);
		}
		else if (prt.fam == AF_INET6)
		{
			prt.sck = socket(PF_INET6, hints.ai_socktype, prt.proto);
		}
		else if (prt.fam == AF_UNSPEC)
		{
			prt.sck = socket(PF_UNSPEC, hints.ai_socktype, prt.proto);
		}
		else {}

		if (prt.sck == INVALID_SOCKET)
		{
			perror(emsg.carr);
			return INT32_MIN;
		}
		/*sint sopt = 30000;
		sint ret = setsockopt(prt.sck, SOL_SOCKET, SO_SNDTIMEO, (_char*)&sopt, sizeof(sopt));

		if (ret > -1)
		{
			bot_sopt nopt(prt.proto, (sint)SOL_SOCKET, sopt);
			ret = prt.AddSOpt(&nopt);
		}
		else
		{
			PError();
			return ret;
		}

		sopt = 9000;
		ret = setsockopt(prt.sck, SOL_SOCKET, SO_RCVTIMEO, (_char*)&sopt, sizeof(sopt));

		if (ret > -1)
		{
			bot_sopt nopt(prt.proto, (sint)SOL_SOCKET, sopt);
			ret = prt.AddSOpt(&nopt);
		}
		else
		{
			PError();
			return ret;
		}*/
		if (prt.bndp)
		{
			sint sopt = -1;
			if (xclsck)
			{
				sopt = (sint)SO_EXCLUSIVEADDRUSE;
			}
			else
			{
				sopt = (sint)SO_REUSEADDR;
			}

			sint opt = 1;
			sint opt = 1;
			ret = AddSOpt(SOL_SOCKET, sopt, (_char*)&opt, sizeof(sint));
			//ret = setsockopt(sck, SOL_SOCKET, sopt, &opt, sizeof(opt));

			if (ret < 0)
			{
				perror(esmg.carr);
				return ret;
			}

			ret = bind(prt.sck, ptr->ai_addr, ptr->ai_addrlen);

			if (ret < 0)
			{
				perror(esmg.carr);
				return ret;
			}
		}
		freeaddrinfo(res);
		con = 1;
		return ret;
	}
#endif

	sint Conn()
	{
		if (con != 1)
		{
			return INT32_MIN;
		}

		sint ret = -1;

		if (!isserv)
		{
			ret = connect(prt.sck, ptr->ai_addr, ptr->ai_addrlen);
		}
		else
		{
			ret = connect(prt.sck, (struct sockaddr*)&prt.oaddr, sizeof(prt.oaddr));
		}
#ifdef _WIN32
		if (ret == SOCKET_ERROR)
		{
			PError();
			return INT32_MIN;
		}
#else
		if (ret < 0)
		{
			PError((sint)errno));
			return ret;
		}
#endif
		con = 2;
		return 0;
	}

	sint Listen(sint nqsiz = 0)
	{
		if (hints.ai_socktype == SOCK_DGRAM)
		{
			return 0;
		}
		if (con != 1)
		{
			return INT32_MIN;
		}
		if (!isserv)
		{
			return INT32_MIN + 1;
		}
		if (nqsiz < 1)
		{
			qsiz = 1;
		}
		else if (nqsiz > SOMAXCONN - 1)
		{
			qsiz = SOMAXCONN - 1;
		}
		else
		{
			qsiz = nqsiz;
		}
		sint ret = listen(prt.sck, qsiz);

		if (ret == SOCKET_ERROR)
		{
#ifdef _WIN32
			PError();
#else
			perror(emsg.carr);
#endif
			return INT32_MIN + 2;
		}
		return ret;
	}
	void *GetAddr(struct sockaddr* x = 0)
	{
		if (!x)
		{
			return 0;
		}
		if (x->sa_family == AF_INET)
		{
			return &(((struct sockaddr_in*)x)->sin_addr);
		}
		else if (x->sa_family == AF_INET6)
		{
			return &(((struct sockaddr_in6*)x)->sin6_addr);
		}
		else if (x->sa_family == AF_NETBIOS)
		{

		}
		else if (x->sa_family == AF_IRDA)
		{

		}
		else {}
		return 0;
	}
	sint Accept()
	{
		if (con != 1)
		{
			return INT32_MIN;
		}

		sint len = sizeof(prt.oaddr);

#ifdef _WIN32
		SOCKET tsck = accept(prt.sck, (struct sockaddr*)&prt.oaddr, &len);

		if (tsck == SOCKET_ERROR)
		{
			PError();
			return (sint)tsck;
		}
#else
		sint tsck = accept(prt.sck, (struct sockaddr*)&prt.oaddr, &len);

		if (prt.tsck < 0)
		{
			perror(emsg.carr);
			return prt.tsck;
		}
#endif
		inet_ntop(prt.oaddr.ss_family, GetAddr((struct sockaddr*)&prt.oaddr), prt.oipstr.carr, prt.oipstr.siz);
		Close(&prt.sck);
		prt.sck = tsck;
		return 0;
	}
	sllint Send(_char *dat = 0, sint dlen = 0)
	{
		if (!dat || !dlen)
		{
			return INT32_MIN + 1;
		}
		sllint add = 0;
		sllint ret = 0;

		if (prt.proto == IPPROTO_TCP || (prt.proto == IPPROTO_UDP && con > 1))
		{
			if (!isserv)
			{
				for (; ret > -1 && ret < dlen;)
				{
					add = (sllint)send(prt.sck, dat, dlen, 0);

					if (add > 0)
					{
						ret += add;
					}
					else if (!add)
					{
						return ret;
					}
					else
					{
						PError();
						return add;
					}
				}
			}
			else
			{
				for (; ret > -1 && ret < dlen;)
				{
					add = (sllint)send(prt.sck, dat, dlen, 0);

					if (add > 0)
					{
						ret += add;
					}
					else if (!add)
					{
						return ret;
					}
					else
					{
						PError();
						return add;
					}
				}
			}
		}
		else if (prt.proto == IPPROTO_UDP && con > 0)
		{
			if (!isserv)
			{
				for (; ret > -1 && ret < dlen;)
				{
					add = (sllint)sendto(prt.sck, dat, dlen, 0, ptr->ai_addr, ptr->ai_addrlen);

					if (add > 0)
					{
						ret += add;
					}
					else if (!add)
					{
						return ret;
					}
					else
					{
						PError();
						return add;
					}
				}
			}
			else
			{
				for (; ret > -1 && ret < dlen;)
				{
					sint alen = sizeof(prt.oaddr);
					add = (sllint)sendto(prt.sck, dat, dlen, 0, (struct sockaddr*)&prt.oaddr, alen);

					if (add > 0)
					{
						ret += add;
					}
					else if (!add)
					{
						return ret;
					}
					else
					{
						PError();
						return add;
					}
				}
			}
		}
		else
		{
#ifdef _WIN32
			if (prt.proto == IPPROTO_PGM && con > 1)
			{

			}
#endif
			ret = INT32_MIN;

		}
		return ret;
	}
	sllint Rec(_char *dat = 0, sllint dlen = 0)
	{
		if (con < 1)
		{
			return INT32_MIN;
		}
		if (!dat || !dlen)
		{
			return INT32_MIN + 1;
		}

		sllint ret = 0;

		if (prt.proto == IPPROTO_TCP || (prt.proto == IPPROTO_UDP && con > 1))
		{
			_char trm = '\0';

			while (ret < dlen && ret > -1)
			{
				if (!isserv)
				{
					ret += (sllint)recv(prt.sck, dat, (sint)(dlen - ret), 0);

					if (ret < 0)
					{
						PError();
						memcpy((void*)&dat[0], (void*)&trm, sizeof(_char));
					}
					else if (ret <= dlen)
					{
						memcpy((void*)&dat[ret], (void*)&trm, sizeof(_char));
					}
					else
					{
						memcpy((void*)&dat[ret], (void*)&trm, sizeof(_char));
					}
				}
				else
				{
					ret = (sllint)recv(prt.sck, dat, (sint)(dlen - ret), 0);

					if (ret < 0)
					{
						PError();
						memcpy((void*)&dat[0], (void*)&trm, sizeof(_char));
					}
					else if (ret <= dlen)
					{
						memcpy((void*)&dat[ret], (void*)&trm, sizeof(_char));
					}
					else
					{
						memcpy((void*)&dat[ret], (void*)&trm, sizeof(_char));
					}
				}
			}
			return ret;
		}
		else if (prt.proto == IPPROTO_UDP)
		{
			_char trm = '\0';

			while (ret < dlen && ret > -1)
			{
				memset((void*)&prt.oaddr, 0, sizeof(prt.oaddr));
				sint alen = sizeof(prt.oaddr);
				ret += (sllint)recvfrom(prt.sck, dat, (sint)(dlen - ret), 0, (struct sockaddr*)&prt.oaddr, &alen);

				if (ret < 0)
				{
					PError();
					memcpy((void*)&dat[0], (void*)&trm, sizeof(_char));
				}
				else if (ret <= dlen)
				{
					inet_ntop(prt.oaddr.ss_family, GetAddr((struct sockaddr*)&prt.oaddr), prt.oipstr.carr, prt.oipstr.siz);
					memcpy((void*)&dat[ret], (void*)&trm, sizeof(_char));
				}
				else
				{
					memcpy((void*)&dat[ret], (void*)&trm, sizeof(_char));
				}
			}
			return ret;
		}
		else
		{
#ifdef _WIN32
			if (prt.proto == IPPROTO_PGM)
			{

			}
#endif
		}
		return 0;
	}

#ifdef _WIN32
	sint Shutdown(sint opt = -1, SOCKET nsck = INVALID_SOCKET)
	{
		if (opt < 0 || nsck == INVALID_SOCKET)
		{
			return INT32_MIN;
		}
		sint xc = shutdown(nsck, opt);
		if (xc == SOCKET_ERROR)
		{
			PError();
		}
		return xc;
	}
#else
	sint Shutdown(sint opt = -1, SOCKET nsck = INVALID_SOCKET)
	{
		if (opt < 0 || nsck == INVALID_SOCKET)
		{
			return INT32_MIN;
		}
		sint xc = shutdown(nsck, opt);
		if (xc < 0)
		{
			PError();
		}
		return xc;
	}
#endif

#ifdef _WIN32
	void Close(SOCKET* nsck = 0)
	{
		if (!nsck)
		{
			if (prt.sck != INVALID_SOCKET)
			{
				closesocket(prt.sck);
			}
		}
		else
		{
			if (*nsck != INVALID_SOCKET)
			{
				closesocket(*nsck);
			}
		}
	}
#else
	void Close(sint* nsck = 0)
	{
		if (!nsck)
		{
			if (prt.sck != INVALID_SOCKET)
			{
				closesocket(prt.sck);
			}
		}
		else
		{
			if (*nsck != INVALID_SOCKET)
			{
				closesocket(*nsck);
			}
		}
	}
#endif
	
#ifdef _WIN32
	void PError(DWORD err = 0)
	{
		if (!err)
		{
			sint xc = bot_sprintf(emsg.carr, emsg.siz, "%i", WSAGetLastError());
		}
		else
		{
			sint xc = bot_sprintf(emsg.carr, emsg.siz, "%d", err);
		}
	}
#else
	void PError(sint err = INT32_MIN)
	{
		if (!err)
		{
			sint xc = bot_sprintf(emsg.carr, emsg.siz, "%s", gai_strerror(err));
		}
		else
		{
			sint xc = bot_sprintf(emsg.carr, emsg.siz, "%s", strerror(errno));
		}
	}
#endif
	bot_plug(c_char* nurl = 0, c_char* nservice = 0, sint ntyp = -1, sint nfam = -1, bool nisserv = false)
	{
		memset(&hints, 0, sizeof(hints));
		isserv = nisserv;
		hints.ai_socktype = ntyp;
		prt.stype = ntyp;
		hints.ai_family = nfam;

		if (nservice)
		{
			bot_sprintf(servc.carr, servc.siz, "%s", nservice);
		}
		if (!bot_strlen(servc.carr))
		{
			bot_sprintf(servc.carr, servc.siz, "%i", (sint)BOTLPORT_A);
		}
		if (nurl)
		{
			if (strcmp(nurl, "0") && strcmp(nurl, "\"\"") && strcmp(nurl, "''"))
			{
				bot_sprintf(url.carr, url.siz, "%s", nurl);
			}
		}

		if (nisserv)
		{
			prt.bndp = true;
		}

		if ((nfam == AF_UNSPEC || nfam == AF_INET || nfam == AF_INET6) && ntyp == SOCK_STREAM)
		{
			hints.ai_protocol = IPPROTO_TCP;
		}
		else if ((nfam == AF_UNSPEC || nfam == AF_INET || nfam == AF_INET6) && ntyp == SOCK_DGRAM)
		{
			hints.ai_protocol = IPPROTO_UDP;
		}
		else if (nfam == AF_IRDA && ntyp == SOCK_STREAM)
		{
			hints.ai_protocol = 0;
		}
		else if ((nfam == AF_UNSPEC || nfam == AF_INET || nfam == AF_INET6) && ntyp == SOCK_RAW)
		{
			hints.ai_protocol = IPPROTO_RAW;
		}
		else
		{
#ifdef _WIN32
			if (nfam == AF_INET && ntyp == SOCK_RDM)
			{
				hints.ai_protocol = IPPROTO_PGM;
			}
#endif
		}
		prt.proto = (sint)hints.ai_protocol;
		prt.portn = (sint)atoi(servc.carr);
		res = ptr = NULL;
		con = -1;
	}

	~bot_plug() { if (con > -1) { Close(); } }

private:

};

enum bot_fld_mems
{
	BOT_FLD_FID = 1,
	BOT_FLD_ORD = 2,
	BOT_FLD_BTO = 3,
	BOT_FLD_IHM = 4,
	BOT_FLD_FLD = 5,
	BOT_FLD_MAX = 6
};

class BOT_FLD
{
public:
	sllint fid;
	sllint ord;
	sllint bto;
	bool is_home;
	std::string fld;
	void Clear() { bto = ord = fid = -1; fld.clear(); }
	void Renew(BOT_FLD* nf = 0)
	{
		Clear();

		if (!nf)
		{
			return;
		}

		ord = nf->ord;
		fid = nf->fid;
		bto = nf->bto;
		fld.append(nf->fld.c_str());
	}

	BOT_FLD(c_char* nnm = "", sllint nfid = -1, bool nis_home = false, sllint nbto = -1, sllint nord = -1) { is_home = nis_home; bto = nbto; fid = nfid; ord = nord; fld.append(nnm); }

private:

};

class BOT_DRV
{
public:
	sllint did;
	bool is_v;
	std::string drv;
	std::vector<BOT_FLD> flds;
	void Clear() { did = 0; is_v = false; drv.clear(); flds.clear(); }
	void Renew(BOT_DRV* nd = 0)
	{
		Clear();

		if (!nd)
		{
			return;
		}

		did = nd->did;
		is_v = nd->is_v;
		drv.append(nd->drv.c_str());

		for (uint x = 0; x < nd->flds.size(); x++)
		{
			flds.push_back(nd->flds[x]);
		}
	}
	sint BOTAddFolder(BOT_FLD* nf = 0)
	{
		if (!nf)
		{
			return -1;
		}
		for (uint x = 0; x < flds.size(); x++)
		{
			if (!strcmp(flds[x].fld.c_str(), nf->fld.c_str()) && nf->bto == flds[x].bto)
			{
				size_t slen = nf->fld.length();
				nf->fld.push_back('_');
				nf->fld.push_back((_char)1);
				sint nxt = 2;

				while (!strcmp(flds[x].fld.c_str(), nf->fld.c_str()) && nf->bto == flds[x].bto)
				{
					nf->fld.erase(slen, nf->fld.length() - slen);
					nf->fld.push_back((_char)nxt);
					nxt++;
				}
			}
		}
		nf->fid = flds.size();
		sint ret = (sint)nf->fid;
		flds.push_back(*nf);
		return ret;
	}

	BOT_DRV(c_char* ndrv = "", sllint nid = 0, bool nis_v = false) { did = nid; is_v = nis_v; drv.append(ndrv); flds.clear(); }

private:

};

class BOT_DIR
{
public:
	std::string bot_home_path;
	std::vector<BOT_DRV> drvs;
	void Clear() { drvs.clear(); bot_home_path.clear(); }
	void Renew(BOT_DIR* nd = 0)
	{
		Clear();

		if (!nd)
		{
			return;
		}

		bot_home_path.append(nd->bot_home_path.c_str());

		for (uint x = 0; x < nd->drvs.size(); x++)
		{
			drvs.push_back(nd->drvs[x]);
		}
	}
	sint BOTAddDrive(c_char* nd = 0, bool nis_v = false)
	{
		if (!nd)
		{
			return -1;
		}

		size_t slen = strlen(nd);

		if (slen < 3 || slen > 254)
		{
			return -1;
		}

		bool has_dmk = true;
		_char dmk = '\\';

		if (memcmp((void*)&nd[slen - 1], (void*)&dmk, sizeof(dmk)))
		{
			has_dmk = false;
		}

		carr_256 dcar;

		if (!has_dmk)
		{
			sint xc = bot_sprintf(dcar.carr, dcar.siz, "%s%c", nd, dmk);
		}
		else
		{
			std::string nstr;
			nstr.append(nd);
			sint xc = bot_sprintf(dcar.carr, dcar.siz, "%s%c", nstr.substr(0, slen - 1).c_str(), dmk);
		}

		for (uint x = 0; x < drvs.size(); x++)
		{
			if (!strcmp(drvs[x].drv.c_str(), dcar.carr))
			{
				return -1;
			}
		}

		BOT_DRV ndrv(dcar.carr, drvs.size(), nis_v);
		sint ret = (sint)ndrv.did;
		drvs.push_back(ndrv);
		return ret;
	}

	BOT_DIR(c_char* ndrv = 0)
	{
		bot_home_path.clear();
		drvs.clear();

		if (ndrv)
		{
			sint xc = BOTAddDrive(ndrv);
			//BOT_DRV nd("c:\\", drvs.size()); drvs.push_back(nd);
		}
	}

private:

};

class bot_script
{
public:
	sint lid;
	uint mode;
	uint encoding;
	std::string name;
	std::string type;
	std::string dest;
	std::string script;
	uint used;
	std::string lused;
	sint lub;
	sllint last_mod;
	sllint last_mod_ns;
	sllint last_maint;
	sllint last_maint_ns;

	void Clear()
	{
		lid = lub = -1;
		last_mod = last_mod_ns = last_maint = last_maint_ns = -1;
		mode = encoding = used = 0;
		name.clear();
		type.clear();
		dest.clear();
		script.clear();
		lused.clear();
	}
	void Renew(bot_script* ns = 0)
	{
		Clear();
		mode = ns->mode;
		encoding = ns->encoding;
		used = ns->used;
		lub = ns->lub;
		last_mod = ns->last_mod;
		last_mod_ns = ns->last_mod_ns;
		last_maint = ns->last_maint;
		last_maint_ns = ns->last_maint_ns;
		char term = '\0';
		uint x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ns->dest[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				dest.push_back(ns->dest[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				dest.push_back(term);
			}
		}
		x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ns->type[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				type.push_back(ns->type[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				type.push_back(term);
			}
		}
		x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ns->name[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				name.push_back(ns->name[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				name.push_back(term);
			}
		}

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ns->lused[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				lused.push_back(ns->lused[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				lused.push_back(term);
			}
		}

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ns->script[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				script.push_back(ns->script[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				script.push_back(term);
			}
		}
	}
	void Renew(uint nmod = UINT_MAX, uint nenc = UINT_MAX, c_char* nnam = "", c_char* ntyp = "", c_char* ndst = "")
	{
		Clear();
		mode = nmod;
		encoding = nenc;
		char term = '\0';
		uint x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ndst[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				dest.push_back(ndst[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				dest.push_back(term);
			}
		}
		x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ntyp[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				type.push_back(ntyp[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				type.push_back(term);
			}
		}
		x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&nnam[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				name.push_back(nnam[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				name.push_back(term);
			}
		}
	}

	bot_script(uint nmod = UINT_MAX, uint nenc = UINT_MAX, c_char* nnam = "", c_char* ntyp = "", c_char* ndst = "")
	{
		lid = lub = -1;
		last_mod = last_mod_ns = last_maint = last_maint_ns = -1;
		mode = nmod;
		encoding = nenc;
		char term = '\0';
		uint x = 0;
		
		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ndst[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				dest.push_back(ndst[x]);
			}
			x++;
			
			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				dest.push_back(term);
			}
		}
		x = 0;

		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&ntyp[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				type.push_back(ntyp[x]);
			}
			x++;

			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				type.push_back(term);
			}
		}
		x = 0;
		
		while (x < (uint)BOT_STRLEN_MAX)
		{
			if (!memcmp((void*)&term, (void*)&nnam[x], 1))
			{
				x = (uint)BOT_STRLEN_MAX;
			}
			else
			{
				name.push_back(nnam[x]);
			}
			x++;
			
			if (x == (uint)BOT_STRLEN_MAX + 1)
			{
				name.push_back(term);
			}
		}
	}
private:
};

typedef struct col_struct
{
	uint type;
	std::string name;
	std::vector<std::vector<u_char>> rows;

	col_struct(sint ntype = 0, c_char* nname = "") { type = ntype; name.append(nname); };

}COL_STRUCT;

class bot_tbl
{

public:

	std::string name;
	std::vector<col_struct> cvec;

	sint cmpto(u_char uto[] = 0, sint col = -1, sint row = -1)
	{
		if (!uto || row < 0 || col < 0) { return -1; }

		if (col < (sint)cvec.size())
		{
			if (row < (sint)cvec[col].rows.size())
			{
				if (cvec[col].rows[row].size() == sizeof(*uto))
				{
					size_t nsiz = 0;
					while (nsiz <cvec[col].rows[row].size())
					{
						if (memcmp(&cvec[col].rows[row][nsiz], &uto[nsiz], 1))
						{
							return -1;
						}
						nsiz++;
					}
					return 0;
				}
			}
		}
		return -1;
	}
	sint cmpto(c_char uto[] = 0, sint col = -1, sint row = -1)
	{
		if (!uto || row < 0 || col < 0) { return -1; }

		if (col < (sint)cvec.size())
		{
			if (row < (sint)cvec[col].rows.size())
			{
				if (cvec[col].rows[row].size() == strlen(uto))
				{
					size_t nsiz = 0;
					while (nsiz <cvec[col].rows[row].size())
					{
						if (memcmp(&cvec[col].rows[row][nsiz], (u_char*)&uto[nsiz], 1))
						{
							return -1;
						}
						nsiz++;
					}
					return 0;
				}
			}
		}
		return -1;
	}
	sint cmpto(uint uto[] = 0, sint col = -1, sint row = -1)
	{
		if (!uto || row < 0 || col < 0) { return -1; }

		if (col < (sint)cvec.size())
		{
			if (row < (sint)cvec[col].rows.size())
			{
				if (cvec[col].rows[row].size() == sizeof(*uto))
				{
					size_t nsiz = 0;
					while (nsiz <cvec[col].rows[row].size())
					{
						if (memcmp(&cvec[col].rows[row][nsiz], (u_char*)&uto[nsiz], 1))
						{
							return -1;
						}
						nsiz++;
					}
					return 0;
				}
			}
		}
		return -1;
	}
	sint cmpto(sint uto[] = 0, sint col = -1, sint row = -1)
	{
		if (!uto || row < 0 || col < 0) { return -1; }

		if (col < (sint)cvec.size())
		{
			if (row < (sint)cvec[col].rows.size())
			{
				if (cvec[col].rows[row].size() == sizeof(*uto))
				{
					size_t nsiz = 0;
					while (nsiz <cvec[col].rows[row].size())
					{
						if (memcmp(&cvec[col].rows[row][nsiz], (u_char*)&uto[nsiz], 1))
						{
							return -1;
						}
						nsiz++;
					}
					return 0;
				}
			}
		}
		return -1;
	}
	sint cmpto(double uto[] = 0, sint col = -1, sint row = -1)
	{
		if (!uto || row < 0 || col < 0) { return -1; }

		if (col < (sint)cvec.size())
		{
			if (row < (sint)cvec[col].rows.size())
			{
				if (cvec[col].rows[row].size() == sizeof(*uto))
				{
					size_t nsiz = 0;
					while (nsiz <cvec[col].rows[row].size())
					{
						if (memcmp(&cvec[col].rows[row][nsiz], (u_char*)&uto[nsiz], 1))
						{
							return -1;
						}
						nsiz++;
					}
					return 0;
				}
			}
		}
		return -1;
	}
	sint AddCol(COL_STRUCT* val = 0)
	{
		if (!val)
		{
			return -1;
		}
		if (val->name.empty())
		{
			return -1;
		}
		size_t siz = 0;
		size_t csiz = 0;

		while (siz < cvec.size())
		{
			if (!siz)
			{
				csiz = cvec[siz].rows.size();
			}
			if (!strcmp(cvec[siz].name.c_str(), val->name.c_str()))
			{
				return (sint)siz;
			}
			siz++;
		}

		if (siz == cvec.size())
		{
			std::vector<u_char> ncar;

			while (val->rows.size() < csiz)
			{
				val->rows.push_back(ncar);
			}

			sint ret = (sint)cvec.size();
			cvec.push_back(*val);
			return ret;
		}
		return -1;
	}
	sint DelCol(sint col = -1)
	{
		if (col < 0)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			cvec[col].rows.clear();

			for (uint x = (uint)col + 1; x < cvec.size(); x++)
			{
				for (uint y = 0; y < cvec[x].rows.size(); y++)
				{
					cvec[x - 1].rows.push_back(cvec[x].rows[y]);
				}
			}
			cvec.pop_back();
		}
		return -1;
	}
	sint SetCol(u_char val[] = 0, sint col = -1, sint row = -1)
	{
		if (col < 0 || !val)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			for (uint y = 0; y < cvec[col].rows.size(); y++)
			{
				if (row > -1)
				{
					y = (uint)row;
				}
				uint x = 0;

				if (bot_ustrlen(val) == cvec[col].rows[y].size())
				{
					while (x < cvec[col].rows[y].size())
					{
						if (memcmp((void*)&cvec[col].rows[y][x], (void*)&val[x], sizeof(cvec[col].rows[y][x])))
						{
							x = cvec[col].rows[y].size();
						}
						x++;
					}
				}
				else
				{
					x = cvec[col].rows[y].size() + 1;
				}

				if (x != cvec[col].rows[row].size())
				{
					cvec[col].rows[row].clear();

					for (x = 0; x < bot_ustrlen(val); x++)
					{
						cvec[col].rows[row].push_back(val[x]);
					}
				}
				if (row > -1)
				{
					y = cvec[col].rows.size();
				}
			}
		}
		return 0;
	}
	sint SetCol(_char val[] = 0, sint col = -1, sint row = -1)
	{
		if (col < 0 || !val)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			for (uint y = 0; y < cvec[col].rows.size(); y++)
			{
				if (row > -1)
				{
					y = (uint)row;
				}
				uint x = 0;

				if (strlen(val) == cvec[col].rows[y].size())
				{
					while (x < cvec[col].rows[y].size())
					{
						if (memcmp((void*)&cvec[col].rows[y][x], (void*)&val[x], sizeof(cvec[col].rows[y][x])))
						{
							x = cvec[col].rows[y].size();
						}
						x++;
					}
				}
				else
				{
					x = cvec[col].rows[y].size() + 1;
				}

				if (x != cvec[col].rows[row].size())
				{
					cvec[col].rows[row].clear();

					for (x = 0; x < strlen(val); x++)
					{
						cvec[col].rows[row].push_back((u_char)val[x]);
					}
				}
				if (row > -1)
				{
					y = cvec[col].rows.size();
				}
			}
		}
		return 0;
	}
	sint SetCol(sint val[] = 0, sint col = -1, sint row = -1)
	{
		if (col < 0 || !val)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			for (uint y = 0; y < cvec[col].rows.size(); y++)
			{
				if (row > -1)
				{
					y = (uint)row;
				}
				uint x = 0;

				if (bot_sintlen(val) == cvec[col].rows[y].size())
				{
					while (x < cvec[col].rows[y].size())
					{
						if (memcmp((void*)&cvec[col].rows[y][x], (void*)&val[x], sizeof(cvec[col].rows[y][x])))
						{
							x = cvec[col].rows[y].size();
						}
						x++;
					}
				}
				else
				{
					x = cvec[col].rows[y].size() + 1;
				}

				if (x != cvec[col].rows[row].size())
				{
					cvec[col].rows[row].clear();

					for (x = 0; x < bot_sintlen(val); x++)
					{
						cvec[col].rows[row].push_back((u_char)val[x]);
					}
				}
				if (row > -1)
				{
					y = cvec[col].rows.size();
				}
			}
		}
		return 0;
	}
	sint SetCol(uint val[] = 0, sint col = -1, sint row = -1)
	{
		if (col < 0 || !val)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			for (uint y = 0; y < cvec[col].rows.size(); y++)
			{
				if (row > -1)
				{
					y = (uint)row;
				}
				uint x = 0;

				if (bot_uintlen(val) == cvec[col].rows[y].size())
				{
					while (x < cvec[col].rows[y].size())
					{
						if (memcmp((void*)&cvec[col].rows[y][x], (void*)&val[x], sizeof(cvec[col].rows[y][x])))
						{
							x = cvec[col].rows[y].size();
						}
						x++;
					}
				}
				else
				{
					x = cvec[col].rows[y].size() + 1;
				}

				if (x != cvec[col].rows[row].size())
				{
					cvec[col].rows[row].clear();

					for (x = 0; x < bot_uintlen(val); x++)
					{
						cvec[col].rows[row].push_back((u_char)val[x]);
					}
				}
				if (row > -1)
				{
					y = cvec[col].rows.size();
				}
			}
		}
		return 0;
	}
	sint SetCol(double val[] = 0, sint col = -1, sint row = -1)
	{
		if (col < 0 || !val)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			for (uint y = 0; y < cvec[col].rows.size(); y++)
			{
				if (row > -1)
				{
					y = (uint)row;
				}
				uint x = 0;

				if (bot_dbllen(val) == cvec[col].rows[y].size())
				{
					while (x < cvec[col].rows[y].size())
					{
						if (memcmp((void*)&cvec[col].rows[y][x], (void*)&val[x], sizeof(cvec[col].rows[y][x])))
						{
							x = cvec[col].rows[y].size();
						}
						x++;
					}
				}
				else
				{
					x = cvec[col].rows[y].size() + 1;
				}

				if (x != cvec[col].rows[row].size())
				{
					cvec[col].rows[row].clear();

					for (x = 0; x < bot_dbllen(val); x++)
					{
						cvec[col].rows[row].push_back((u_char)val[x]);
					}
				}
				if (row > -1)
				{
					y = cvec[col].rows.size();
				}
			}
		}
		return 0;
	}
	sint SetColName(c_char* nm = "", sint col = -1)
	{
		if (!nm)
		{
			return -1;
		}
		if (!strlen(nm) || col < 0)
		{
			return -1;
		}

		if (col < (sint)cvec.size())
		{
			cvec[col].name.clear();
			cvec[col].name.append(nm);
		}
		return -1;
	}
	sint FindColumn(c_char* nm = "")
	{
		if (!nm)
		{
			return -1;
		}
		if (!strlen(nm))
		{
			return -1;
		}

		for (uint x = 0; x < cvec.size(); x++)
		{
			if (!strcmp(cvec[x].name.c_str(), nm))
			{
				return (sint)x;
			}
		}
		return -1;
	}
	sint AddRow()
	{
		if (cvec.empty())
		{
			COL_STRUCT ncol(0, "row_id");
			cvec.push_back(ncol);
		}

		std::vector<u_char> vec;

		for (size_t siz = 0; siz < cvec.size(); siz++)
		{
			if (!siz)
			{
				cvec[siz].rows.push_back(vec);
			}
			else
			{
				while (cvec[siz].rows.size() < cvec[0].rows.size())
				{
					cvec[siz].rows.push_back(vec);
				}
			}
		}
		return 0;
	}

	bot_tbl(c_char* nname = "") { name.append(nname); }

	private:

};

enum stmt_mems
{
	BOT_STMT_MAINT = 0,
	BOT_STMT_STMT = 1,
	BOT_STMT_TTYPE = 2,
	BOT_STMT_CTYPES = 3,
	BOT_STMT_CONT = 4,
	BOT_STMT_DBNAME = 5,
	BOT_STMT_DBALIAS = 6,
	BOT_STMT_OPTS = 7,
	BOT_STMT_SPEC = 8,
	BOT_STMT_RLIM = 9,
	BOT_STMT_TARG = 10,
	BOT_STMT_ACT = 11,
	BOT_STMT_OSPEC = 12,
	BOT_STMT_IFEX = 13,
	BOT_STMT_COLS = 14,
	BOT_STMT_VALS = 15,
	BOT_STMT_CONDS = 16,
	BOT_STMT_LID = 17,
	BOT_STMT_AN = 18,
	BOT_STMT_MAX = 19
};

class BOT_STMT
{

public:

	bool maint;
	bool an;
	sint lid;
	sint it_type;
	std::string stmt;
	std::string nst;
	sint ic_type;
	std::string cont;
	std::string dbname;
	std::string dbalias;
	sint spec;
	sint rlim;
	sint targ;
	sint act;
	sint ospec;
	sint ifex;
	sint opts[2];
	std::vector<std::string> fcols;
	std::vector<std::string> cols;
	std::vector<std::string> vals;
	std::vector<std::string> conds;
	void* rblk;
	void Clear()
	{
		an = maint = false;
		rblk = 0;
		opts[0] = opts[1] = ifex = ospec = act = targ = rlim = spec = lid = it_type = ic_type = -1;

		if (!stmt.empty())
		{
			stmt.clear();
		}
		if (!cont.empty())
		{
			cont.clear();
		}
		if (!nst.empty())
		{
			nst.clear();
		}
		if (!dbname.empty())
		{
			dbname.clear();
		}
		if (!dbalias.empty())
		{
			dbalias.clear();
		}
		if (!fcols.empty())
		{
			fcols.clear();
		}
		if (!cols.empty())
		{
			cols.clear();
		}
		if (!vals.empty())
		{
			vals.clear();
		}
		if (!conds.empty())
		{
			conds.clear();
		}
	}
	void Renew(bool nmaint = false, sint nit_type = -1, c_char* nname = "", c_char* cname = "", sint ctype = -1, void* nrblk = 0)
	{
		Clear();
		maint = nmaint;
		it_type = nit_type;
		size_t siz = strlen(nname);

		if (siz && siz < BOT_STRLEN_MAX)
		{
			dbname.append(nname);
		}

		ic_type = ctype;
		siz = strlen(cname);

		if (siz && siz < BOT_STRLEN_MAX)
		{
			cont.append(cname);
		}
		rblk = nrblk;
	}
	sint AddDB(c_char* dname = "")
	{
		sint ret = -1;
		if (dname)
		{
			if (strlen(dname) < BOT_STRLEN_MAX)
			{
				if (!dbname.empty())
				{
					dbname.clear();
				}
				dbname.append(dname);
			}
		}
		return ret;
	}
	sint AddCont(c_char* cname = "", sint ctype = -1)
	{
		sint ret = -1;

		if (cname)
		{
			if (strlen(cname) < BOT_STRLEN_MAX)
			{
				if (!strcmp(cont.c_str(), cname))
				{
					return 0;
				}
				if (!cont.empty())
				{
					cont.clear();
				}
				cont.append(cname);
				ic_type = ctype;
				return 0;
			}
		}
		return ret;
	}
	sint AddCol(c_char* col_n = "", c_char* val = "", bool q = false)
	{
		sint ret = -1;

		if (col_n)
		{
			size_t nlen = strlen(col_n);
			size_t vlen = 0;

			if (val)
			{
				vlen = strlen(val);
			}

			if ((nlen < BOT_STRLEN_MAX) && (vlen < BOT_STRLEN_MAX))
			{
				if (q)
				{
					size_t siz = 0;

					while (siz < fcols.size())
					{
						if (!strcmp(fcols[siz].c_str(), col_n))
						{
							return (sint)siz;
						}
						siz++;
					}
					std::string ncol;
					ncol.append(col_n);
					fcols.push_back(ncol);
				}
				else
				{
					size_t siz = 0;

					while (siz < cols.size())
					{
						if (!strcmp(cols[siz].c_str(), col_n))
						{
							return (sint)siz;
						}
						siz++;
					}
					std::string ncol;
					ncol.append(col_n);
					cols.push_back(ncol);

					if (vlen)
					{
						ncol.clear();
						ncol.append(val);
						vals.push_back(ncol);
					}
					return (sint)siz;
				}
			}
		}
		return ret;
	}
	sint AddCond(c_char* conj_ = "", c_char* col_ = "", c_char* cmp_ = "", c_char* val_ = "", c_char* sub_cond = "")
	{
		if (!col_ || !cmp_ || !val_ || !sub_cond)
		{
			return -1;
		}

		if (!strlen(col_) || !strlen(cmp_))
		{
			return -1;
		}

		sint xc = -1;
		std::string cond;

		if (conds.empty())
		{
			if (strlen(sub_cond))
			{
				xc = bot_sprintfs(&cond, false, "(%s %s %s %s)", col_, cmp_, val_, sub_cond);
			}
			else
			{
				xc = bot_sprintfs(&cond, false, "(%s %s %s)", col_, cmp_, val_);
			}
		}
		else
		{
			if (!conj_)
			{
				if (strlen(sub_cond))
				{
					xc = bot_sprintfs(&cond, false, "AND (%s %s %s %s)", col_, cmp_, val_, sub_cond);
				}
				else
				{
					xc = bot_sprintfs(&cond, false, "AND (%s %s %s)", col_, cmp_, val_);
				}
			}
			else
			{
				if (strlen(sub_cond))
				{
					xc = bot_sprintfs(&cond, false, "%s (%s %s %s %s)", conj_, col_, cmp_, val_, sub_cond);
				}
				else
				{
					xc = bot_sprintfs(&cond, false, "%s (%s %s %s)", conj_, col_, cmp_, val_);
				}
			}
		}

		if (xc > -1)
		{
			conds.push_back(cond);
		}
		return xc;
	}
	sint AddCond(std::string* cond_ = 0)
	{
		if (!cond_)
		{
			return -1;
		}

		if (cond_->empty())
		{
			return -1;
		}

		sint xc = -1;
		std::string cond;

		if (conds.empty())
		{
			cond.append(" AND ");
		}

		cond.append(cond_->c_str());

		if (xc > -1)
		{
			conds.push_back(cond);
		}
		return xc;
	}

	BOT_STMT(bool nmaint = false, sint nit_type = -1, c_char* nname = "", c_char* cname = "", sint ctype = -1, void* nrblk = 0)
	{
		an = false;
		maint = nmaint;
		rblk = nrblk;
		ifex = ospec = act = rlim = spec = targ = lid = -1;
		opts[0] = -1;
		opts[1] = -1;
		it_type = nit_type;
		size_t siz = strlen(nname);

		if (siz && siz < BOT_STRLEN_MAX)
		{
			dbname.append(nname);
		}

		siz = strlen(cname);

		if (siz && siz < BOT_STRLEN_MAX)
		{
			cont.append(cname);
			ic_type = ctype;
		}
	}
	
private:

};

class DB_CONN
{
public:

	sint lid;
	sint omode;
	sint exists;
	std::string name;
	sint mlid;
	std::vector <std::string> att;
	bool in_use;
	bool close_me;
	bool persist;
	bool o_com;
	std::chrono::steady_clock::time_point t;
	sqlite3* db_;

	void Clear()
	{
		in_use = o_com = persist = close_me = false;
		mlid = exists = lid = omode = -1;

		if (!name.empty())
		{
			name.clear();
		}
		if (!att.empty())
		{
			att.clear();
		}
		t = std::chrono::steady_clock::now();
	}
	void Renew(DB_CONN* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		lid = val_->lid;
		omode = val_->omode;
		mlid = val_->mlid;
		exists = val_->exists;
		for (uint x = 0; x < val_->att.size(); x++)
		{
			att.push_back(val_->att[x]);
		}
		name.append(val_->name.c_str());
		t = val_->t;

	}
	void Renew(c_char* nname = "", sint nmlid = -1, sint nomode = -1, sint nfid = -1)
	{
		Clear();
		mlid = nmlid;
		lid = nfid;
		omode = nomode;
		size_t siz = strlen(nname);

		if (siz && siz < BOT_STRLEN_MAX)
		{
			name.append(nname);
		}

		t = std::chrono::steady_clock::now();
	}

	DB_CONN(c_char* nname = "", sint nmlid = -1, sint nomode = -1, sint nfid = -1) { exists = -1; mlid = nmlid; lid = nfid; in_use = o_com = persist = close_me = false; omode = nomode; size_t siz = strlen(nname); if (siz && siz < BOT_STRLEN_MAX) { name.append(nname); } t = std::chrono::steady_clock::now(); att.clear(); }

private:
};

enum db_mems
{
	BOT_DB_FCON = 0,
	BOT_DB_TYPE = 1,
	BOT_DB_ID = 2,
	BOT_DB_NAME = 3,
	BOT_DB_TABLES = 4,
	BOT_DB_COLUMNS = 5,
	BOT_DB_EXISTS = 6,
	BOT_DB_CONN = 7,
	BOT_DB_CBY = 8,
	BOT_DB_FELE = 9,
	BOT_DB_OMODE = 10,
	BOT_DB_MAX = 11
};

class BOT_DB
{
public:
	sint fcon;
	sint type;
	sint lid;
	sint exists;
	sint c_by;
	sint omode;
	sint file_ele;
	bool connected;
	std::string name;
	std::vector<std::string> tables;
	std::vector<std::vector<std::vector<std::string>> > columns;

	void Clear()
	{
		connected = false;
		file_ele = omode = fcon = c_by = lid = exists = -1;
		
		if (!name.empty())
		{
			name.clear();
		}
		if (!tables.empty())
		{
			tables.clear();
		}
		if (!columns.empty())
		{
			columns.clear();
		}
	}
	void Renew(BOT_DB* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		file_ele = val_->file_ele;
		lid = val_->lid;
		fcon = val_->fcon;
		type = val_->type;
		exists = val_->exists;
		c_by = val_->c_by;
		omode = val_->omode;
		uint len = val_->name.length();

		if (len && len < 128)
		{
			name.append(val_->name.c_str());
		}
		for (uint x = 0; x < val_->tables.size(); x++)
		{
			tables.push_back(val_->tables[x]);
		}
		for (uint x = 0; x < val_->columns.size(); x++)
		{
			columns.push_back(val_->columns[x]);
		}
	}

	BOT_DB(c_char* nstr = "", sint ntype = -1, sint nomode = -1, sint nexists = -1)
	{
		connected = false;
		exists = nexists;
		omode = nomode;
		file_ele = fcon = c_by = lid = -1;
		type = ntype;
		uint len = strlen(nstr);
		tables.clear();
		tables.push_back("LAST_ACCESS");
		std::vector < std::vector < std::string>> avec;
		columns.push_back(avec);
		std::vector<std::string> bvec;
		columns[0].push_back(bvec);
		columns[0].push_back(bvec);
		columns[0][0].push_back("ID");
		columns[0][1].push_back("INTEGER PRIMARY KEY");
		columns[0][0].push_back("LAST_MODIFIED");
		columns[0][1].push_back("INTEGER");
		columns[0][0].push_back("LAST_MAINTAINED");
		columns[0][1].push_back("INTEGER");
		columns[0][0].push_back("LAST_MODIFIED_NS");
		columns[0][1].push_back("INTEGER");
		columns[0][0].push_back("LAST_MAINTAINED_NS");
		columns[0][1].push_back("INTEGER");

		if (len)
		{
			std::string str;
			str.append("");
			str.append(nstr);
			str.append(".db");
		}

		if (len && len < 128) { name.append(nstr); }
	}

private:
};

class BOT_DB_M
{
public:
	sint fcon;
	sint type;
	sint lid;
	std::string name;
	size_t tsiz;
	size_t csiz;
	sint exists;
	sint c_by;
	sint omode;
	sint file_ele;
	bool connected;

	void Clear()
	{
		connected = false;
		file_ele = omode = fcon = c_by = lid = exists = -1;
		
		if (!name.empty())
		{
			name.clear();
		}
		tsiz = 0;
		csiz = 0;
	}
	void Renew(BOT_DB_M* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		fcon = val_->fcon;
		type = val_->type;
		lid = val_->lid;
		name.append(val_->name.c_str());
		tsiz = val_->tsiz;
		csiz = val_->csiz;
		exists = val_->exists;
		c_by = val_->c_by;
		omode = val_->omode;
		file_ele = val_->file_ele;
		connected = val_->connected;
	}
	void Renew(BOT_DB* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		fcon = val_->fcon;
		type = val_->type;
		lid = val_->lid;
		name.append(val_->name.c_str());
		tsiz = val_->tables.size();
		csiz = val_->columns.size();
		exists = val_->exists;
		c_by = val_->c_by;
		omode = val_->omode;
		file_ele = val_->file_ele;
		connected = val_->connected;
	}

	BOT_DB_M(c_char* nstr = "", sint ntype = -1, sint nomode = -1, sint nexists = -1, sint nlid = -1, size_t ntsiz = 0, size_t ncsiz = 0, sint nc_by = -1)
	{
		connected = false;
		
		if (strlen(nstr) < 128)
		{
			file_ele = fcon = -1;
			name.append(nstr);
		}
		type = ntype;
		lid = nlid;
		tsiz = ntsiz;
		csiz = ncsiz;
		exists = nexists;

		if (strlen(nstr))
		{
			std::string str;
			str.append("");
			str.append(nstr);
			str.append(".db");
		}

		c_by = nc_by;
		omode = nomode;
	}

private:
};

class BOT_COMMIT
{
public:

	std::vector<BOT_DB_M> dbs;
	std::vector<BOT_STMT> t;
	std::vector<BOT_STMT> an;
	sint opt;

	void Clear() { opt = -1; if (!dbs.empty()) { dbs.clear(); } if (!t.empty()) { t.clear(); } if (!an.empty()) { an.clear(); } }

	BOT_COMMIT() { opt = -1; }

private:
};

enum botcmd_mems
{
	BOT_CMD_ID = 0,
	BOT_CMD_CID = 1,
	BOT_CMD_PRV = 2,
	BOT_CMD_CMD = 3,
	BOT_CMD_MAX = 4
};

class BOTCOMMAND
{
public:

	sint id;
	sint cmd_id;
	sint priv;
	std::string cmd;

	void Clear() { id = cmd_id = -1; priv = 0; if (!cmd.empty()) { cmd.clear(); } }
	void Renew(BOTCOMMAND* val = 0)
	{
		Clear();

		if (!val)
		{
			return;
		}
		id = val->id;
		cmd_id = val->cmd_id;
		priv = val->priv;
		cmd.append(val->cmd.c_str());
	}
	void Renew(c_char* ncmd = "", sint ncmd_id = -1)
	{
		Clear();

		cmd.append(ncmd);
		cmd_id = ncmd_id;
	}

	BOTCOMMAND(c_char* ncmd = 0, sint ncmd_id = -1) { id = -1; cmd_id = ncmd_id; priv = 0; if (ncmd) { sint chk = bot_cstrchk(ncmd); if (chk < 128) { if (bot_sisn(ncmd, chk)) { cmd_id = atoi(ncmd); } else { cmd.append(ncmd); } } } }

private:
};

enum log_mems
{
	BOT_LOG_LOK = 0,
	BOT_LOG_LID = 1,
	BOT_LOG_TYPE = 2,
	BOT_LOG_S = 3,
	BOT_LOG_T = 4,
	BOT_LOG_S_DATE = 5,
	BOT_LOG_Q = 6,
	BOT_LOG_CBY = 8,
	BOT_LOG_MAX = 9
};

class BOT_LOGDET
{
public:

	sint lid;
	sint type;
	sint c_by;
	sint file_ele;
	bool started;
	std::string logtitle;
	std::string startdate;
	std::vector<std::string> log_q;

	void Clear() { logtitle.clear(); startdate.clear(); log_q.clear(); started = false; file_ele = lid = type = c_by = -1; }
	void Renew(BOT_LOGDET* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		logtitle.append(val_->logtitle.c_str());
		startdate.append(val_->startdate.c_str());
		log_q.swap(val_->log_q);
		file_ele = val_->file_ele;
		type = val_->type;
		c_by = val_->c_by;
	}

	BOT_LOGDET(c_char* titl = "", c_char* dat = "", sint ntype = -1, sint nc_by = -1) { file_ele = type = -1; started = false; if (ntype > -1) { type = ntype; } if (strlen(titl) < 256) { logtitle.append(titl); } if (strlen(dat) < 64) { startdate.append(dat); } c_by = nc_by; }

private:

};

class BOT_LOGDET_M
{
public:

	sint lid;
	sint type;
	sint c_by;
	sint file_ele;
	bool started;
	std::string logtitle;
	std::string startdate;
	size_t lsiz;

	void Clear() { logtitle.clear(); startdate.clear(); lsiz = 0; started = false; file_ele = lid = type = c_by = -1; }
	void Renew(BOT_LOGDET_M* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		file_ele = val_->file_ele;
		logtitle.append(val_->logtitle.c_str());
		startdate.append(val_->startdate.c_str());
		lsiz = val_->lsiz;
		type = val_->type;
		c_by = val_->c_by;
		lid = val_->lid;
	}
	void Renew(BOT_LOGDET* val_ = 0)
	{
		if (!val_)
		{
			return;
		}
		Clear();
		file_ele = val_->file_ele;
		logtitle.append(val_->logtitle.c_str());
		startdate.append(val_->startdate.c_str());
		lsiz = val_->log_q.size();
		type = val_->type;
		c_by = val_->c_by;
		lid = val_->lid;
	}

	BOT_LOGDET_M(c_char* titl = "", c_char* dat = "", sint ntype = -1, sint lid = -1, bool nstrt = false, sint nc_by = -1) { file_ele = type = -1; started = nstrt; if (ntype > -1) { type = ntype; } if (strlen(titl) < 256) { logtitle.append(titl); } if (strlen(dat) < 64) { startdate.append(dat); } lsiz = 0; c_by = nc_by; }

private:

};

typedef struct hist_p
{
	u_char sym;
	uint ct;

	hist_p(u_char* nsym = 0, uint nct = 0) { sym = BOT_BOUND_UCHR; ct = nct; if (nsym) { memcpy(&sym, &nsym[0], 1); } }

}HIST_P;

typedef struct hist_f
{
	u_char sym;
	uint ct;

	hist_f(u_char* nsym = 0, uint nct = 0) { sym = BOT_BOUND_UCHR; ct = nct; if (nsym) { memcpy(&sym, &nsym[0], 1); } }

}HIST_F;

enum MICSS_MEMS
{
	MICSS_ID = 0,
	MICSS_SYM = 1,
	MICSS_ENCODINGS = 2,
	MICSS_CTO = 3,
	MICSS_HP = 4,
	MICSS_HF = 5,
	MICSS_MAINT = 6,
	MICSS_MAINT_NS = 7,
	MICSS_MOD = 8,
	MICSS_MOD_NS = 9,
	MICSS_MAX = 10
};

class MICSYM
{
public:
	bool ud_id;
	sint id;
	bool ud_sym;
	u_char sym;
	bool ud_encodings;
	std::vector<sint> encodings;
	bool ud_constituent_to;
	std::vector<std::vector<std::vector<u_char>> > constituent_to;
	bool ud_history_preceeding;
	std::vector<std::vector<HIST_P>> history_preceeding;
	bool ud_history_following;
	std::vector<std::vector<HIST_F>>history_following;
	bool ud_last_maintained;
	sint last_maintained;
	bool ud_last_modified;
	sint last_modified;
	bool ud_last_maintained_ns;
	sint last_maintained_ns;
	bool ud_last_modified_ns;
	sint last_modified_ns;

	sint loc;

	sint cmpto(MICSYM* val_ = 0)
	{
		if (id != val_->id ||
			last_modified != val_->last_modified ||
			last_modified_ns != val_->last_modified_ns ||
			last_maintained != val_->last_maintained ||
			last_maintained_ns != val_->last_maintained_ns ||
			memcmp((void*)&sym, (void*)&val_->sym, sizeof(sym)) ||
			encodings.size() != val_->encodings.size() ||
			constituent_to.size() != val_->constituent_to.size() ||
			history_preceeding.size() != val_->history_preceeding.size() ||
			history_following.size() != val_->history_following.size())
		{
			return -1;
		}

		for (uint x = 0; x < encodings.size(); x++)
		{
			if (encodings[x] != val_->encodings[x])
			{
				return -1;
			}
		}
		for (uint x = 0; x < constituent_to.size(); x++)
		{
			for (uint y = 0; y < constituent_to[x].size(); y++)
			{
				if (memcmp((void*)&constituent_to[x][y], (void*)&val_->constituent_to[x][y], sizeof(constituent_to[x][y])))
				{
					return -1;
				}
			}
		}
		for (uint x = 0; x < history_preceeding.size(); x++)
		{
			if (history_preceeding[x].size() != val_->history_preceeding[x].size())
			{
				return -1;
			}
			for (uint y = 0; y < history_preceeding[x].size(); x++)
			{
				if (memcmp((void*)&history_preceeding[x][y].sym, (void*)&val_->history_preceeding[x][y].sym, sizeof(history_preceeding[x][y].sym)))
				{
					return -1;
				}
			}
		}
		for (uint x = 0; x < history_following.size(); x++)
		{
			if (history_following[x].size() != val_->history_following[x].size())
			{
				return -1;
			}
			for (uint y = 0; y < history_following[x].size(); x++)
			{
				if (memcmp((void*)&history_following[x][y].sym, (void*)&val_->history_following[x][y].sym, sizeof(history_following[x][y].sym)))
				{
					return -1;
				}
			}
		}
		return 0;
	}
	void Clear() { encodings.clear(); constituent_to.clear(); history_preceeding.clear(); history_following.clear(); id = last_maintained = last_modified = last_maintained_ns = last_modified_ns = -1; ud_id = ud_sym = ud_encodings = ud_constituent_to = ud_history_preceeding = ud_history_following = ud_last_modified = ud_last_maintained = ud_last_maintained_ns = ud_last_maintained_ns = false; }
	void Renew(MICSYM* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		id = val_->id;
		last_modified = val_->last_modified;
		last_modified_ns = val_->last_modified_ns;
		last_maintained = val_->last_maintained;
		last_maintained_ns = val_->last_maintained_ns;
		memcpy((void*)&sym, (void*)&val_->sym, sizeof(sym));
		encodings.swap(val_->encodings);
		constituent_to.swap(val_->constituent_to);
		history_preceeding.swap(val_->history_preceeding);
		history_following.swap(val_->history_following);
	}
	sint Proc(sint memb = -1)
	{
		if (memb < 0)
		{
			for (size_t siz = 0; siz < encodings.size(); siz++)
			{
				for (size_t nsiz = siz + 1; nsiz < encodings.size(); nsiz++)
				{
					if (encodings[siz] == encodings[nsiz])
					{
						if (nsiz < constituent_to.size())
						{
							for (size_t usiz = 0; usiz < constituent_to[nsiz].size(); usiz++)
							{
								constituent_to[siz].push_back(constituent_to[nsiz][usiz]);
							}
							constituent_to[nsiz].clear();
						}
						if (nsiz < history_preceeding.size())
						{
							for (size_t usiz = 0; usiz < history_preceeding[nsiz].size(); usiz++)
							{
								history_preceeding[siz].push_back(history_preceeding[nsiz][usiz]);
							}
							history_preceeding[nsiz].clear();
						}
						if (nsiz < history_following.size())
						{
							for (size_t usiz = 0; usiz < history_following[nsiz].size(); usiz++)
							{
								history_following[siz].push_back(history_following[nsiz][usiz]);
							}
							history_following[nsiz].clear();
						}
						encodings[nsiz] = -1;
					}
				}
			}
			if (!encodings.empty())
			{
				std::vector<sint> usedv;
				for (size_t siz = 0; siz < encodings.size(); siz++)
				{
					if (encodings[siz] > -1)
					{
						usedv.push_back(encodings[siz]);
					}
				}
				if (usedv.size() != encodings.size())
				{
					encodings.clear();
					for (size_t siz = 0; siz < usedv.size(); siz++)
					{
						encodings.push_back(usedv[siz]);
					}
				}
			}
			if (!history_preceeding.empty())
			{
				std::vector<std::vector<HIST_P>> hp_v;
				for (size_t siz = 0; siz < history_preceeding.size(); siz++)
				{
					if (!history_preceeding[siz].empty())
					{
						hp_v.push_back(history_preceeding[siz]);
					}
				}
				if (hp_v.size() != history_preceeding.size())
				{
					history_preceeding.clear();
					for (size_t siz = 0; siz < hp_v.size(); siz++)
					{
						history_preceeding.push_back(hp_v[siz]);
					}
				}
			}
			while (history_preceeding.size() > encodings.size())
			{
				history_preceeding.pop_back();
			}
			if (!history_following.empty())
			{
				std::vector<std::vector<HIST_F>> hf_v;
				for (size_t siz = 0; siz < history_following.size(); siz++)
				{
					if (!history_following[siz].empty())
					{
						hf_v.push_back(history_following[siz]);
					}
				}
				if (hf_v.size() != history_following.size())
				{
					history_following.clear();
					for (size_t siz = 0; siz < hf_v.size(); siz++)
					{
						history_following.push_back(hf_v[siz]);
					}
				}
			}
			while (history_following.size() > encodings.size())
			{
				history_following.pop_back();
			}
			for (size_t siz = 0; siz < constituent_to.size(); siz++)
			{
				if (!constituent_to[siz].empty())
				{
					for (size_t nsiz = 0; nsiz < constituent_to[siz].size(); nsiz++)
					{
						for (size_t xsiz = nsiz + 1; xsiz < constituent_to[siz].size(); xsiz++)
						{
							if (constituent_to[siz][nsiz].size() == constituent_to[siz][xsiz].size())
							{
								size_t usiz = 0;
								while (usiz < constituent_to[siz][xsiz].size())
								{
									if (memcmp(&constituent_to[siz][nsiz][usiz], &constituent_to[siz][xsiz][usiz], sizeof(constituent_to[siz][nsiz][usiz])))
									{
										usiz = constituent_to[siz][xsiz].size();
									}
									usiz++;
								}
								if (usiz == constituent_to[siz][xsiz].size())
								{
									constituent_to[siz][xsiz].clear();
								}
							}
						}
					}
				}
			}
			if (!constituent_to.empty())
			{
				std::vector<std::vector<std::vector<u_char>> > alterv;
				for (size_t siz = 0; siz < constituent_to.size(); siz++)
				{
					std::vector<std::vector<u_char>> xvec;
					for (size_t nsiz = 0; nsiz < constituent_to[siz].size(); nsiz++)
					{
						if (!constituent_to[siz][nsiz].empty())
						{
							xvec.push_back(constituent_to[siz][nsiz]);
						}
					}
					if (xvec.size() != constituent_to[siz].size())
					{
						constituent_to[siz].clear();
						for (size_t nsiz = 0; nsiz < xvec.size(); nsiz++)
						{
							constituent_to[siz].push_back(xvec[nsiz]);
						}
					}
				}
			}
			while (constituent_to.size() > encodings.size())
			{
				constituent_to.pop_back();
			}
			for (size_t siz = 0; siz < history_preceeding.size(); siz++)
			{
				for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
				{
					size_t usiz = nsiz + 1; 
					
					while (usiz < history_preceeding[siz].size())
					{
						if (!memcmp(&history_preceeding[siz][nsiz].sym, &history_preceeding[siz][usiz].sym, sizeof(history_preceeding[siz][nsiz].sym)))
						{
							history_preceeding[siz][nsiz].ct += history_preceeding[siz][usiz].ct;
							history_preceeding[siz][usiz].ct = 0;
							usiz = history_preceeding[siz].size();
						}
						usiz++;
					}
				}
				if (!history_preceeding[siz].empty())
				{
					std::vector<HIST_P> hp_v;
					for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
					{
						if (history_preceeding[siz][nsiz].ct)
						{
							hp_v.push_back(history_preceeding[siz][nsiz]);
						}
					}
					if (hp_v.size() != history_preceeding[siz].size())
					{
						history_preceeding[siz].clear();
						for (size_t nsiz = 0; nsiz < hp_v.size(); nsiz++)
						{
							history_preceeding[siz].push_back(hp_v[nsiz]);
						}
					}
				}
			}
			for (size_t siz = 0; siz < history_following.size(); siz++)
			{
				for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
				{
					size_t usiz = nsiz + 1;

					while (usiz < history_following[siz].size())
					{
						if (!memcmp(&history_following[siz][nsiz].sym, &history_following[siz][usiz].sym, sizeof(history_following[siz][nsiz].sym)))
						{
							history_following[siz][nsiz].ct += history_following[siz][usiz].ct;
							history_following[siz][usiz].ct = 0;
							usiz = history_following[siz].size();
						}
						usiz++;
					}
				}
				if (!history_following[siz].empty())
				{
					std::vector<HIST_F> hf_v;
					for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
					{
						if (history_following[siz][nsiz].ct)
						{
							hf_v.push_back(history_following[siz][nsiz]);
						}
					}
					if (hf_v.size() != history_following[siz].size())
					{
						history_following[siz].clear();
						for (size_t nsiz = 0; nsiz < hf_v.size(); nsiz++)
						{
							history_following[siz].push_back(hf_v[nsiz]);
						}
					}
				}
			}
		}
		else
		{
			switch (memb)
			{
			case MICSS_ENCODINGS:
			{
				Proc();
				break;
			}
			case MICSS_CTO:
			{
				for (size_t siz = 0; siz < constituent_to.size(); siz++)
				{
					if (!constituent_to[siz].empty())
					{
						for (size_t nsiz = siz + 1; nsiz < constituent_to.size(); nsiz++)
						{
							if (constituent_to[siz].size() == constituent_to[nsiz].size())
							{
								size_t usiz = 0;
								while (usiz < constituent_to[nsiz].size())
								{
									if (memcmp(&constituent_to[siz][usiz], &constituent_to[nsiz][usiz], sizeof(constituent_to[siz][usiz])))
									{
										usiz = constituent_to[nsiz].size();
									}
									usiz++;
								}
								if (usiz == constituent_to[nsiz].size())
								{
									constituent_to[nsiz].clear();
								}
							}
						}
					}
				}
				while (constituent_to.size() > encodings.size())
				{
					constituent_to.pop_back();
				}
				break;
			}
			
			case MICSS_HP:
			{
				for (size_t siz = 0; siz < history_preceeding.size(); siz++)
				{
					for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
					{
						for (size_t usiz = nsiz + 1; usiz < history_preceeding[siz].size(); usiz++)
						{
							if (!memcmp(&history_preceeding[siz][nsiz].sym, &history_preceeding[siz][usiz].sym, sizeof(history_preceeding[siz][nsiz].sym)))
							{
								history_preceeding[siz][nsiz].ct += history_preceeding[siz][usiz].ct;
								history_preceeding[siz][usiz].ct = 0;
								usiz = history_preceeding[siz].size();
							}
						}
					}
					if (!history_preceeding[siz].empty())
					{
						std::vector<HIST_P> hp_v;
						for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
						{
							if (history_preceeding[siz][nsiz].ct)
							{
								hp_v.push_back(history_preceeding[siz][nsiz]);
							}
						}
						if (hp_v.size() != history_preceeding[siz].size())
						{
							history_preceeding[siz].clear();
							for (size_t nsiz = 0; nsiz < hp_v.size(); nsiz++)
							{
								history_preceeding[siz].push_back(hp_v[nsiz]);
							}
						}
					}
				}
				break;
			}
			case MICSS_HF:
			{
				for (size_t siz = 0; siz < history_following.size(); siz++)
				{
					for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
					{
						for (size_t usiz = nsiz + 1; usiz < history_following[siz].size(); usiz++)
						{
							if (!memcmp(&history_following[siz][nsiz].sym, &history_following[siz][usiz].sym, sizeof(history_following[siz][nsiz].sym)))
							{
								history_following[siz][nsiz].ct += history_following[siz][usiz].ct;
								history_following[siz][usiz].ct = 0;
								usiz = history_following[siz].size();
							}
						}
					}
					if (!history_following[siz].empty())
					{
						std::vector<HIST_F> hf_v;
						for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
						{
							if (history_following[siz][nsiz].ct)
							{
								hf_v.push_back(history_following[siz][nsiz]);
							}
						}
						if (hf_v.size() != history_following[siz].size())
						{
							history_following[siz].clear();
							for (size_t nsiz = 0; nsiz < hf_v.size(); nsiz++)
							{
								history_following[siz].push_back(hf_v[nsiz]);
							}
						}
					}
				}
				break;
			}
			case MICSS_ID:
			case MICSS_SYM:
			case MICSS_MAINT:
			case MICSS_MAINT_NS:
			case MICSS_MOD:
			case MICSS_MOD_NS:
			case MICSS_MAX:
			{
				break;
			}
			default:
			{
				break;
			}
			}
		}
		return 0;
	}
	sint AddEnc(sint enc = -1, std::vector<std::vector<u_char>>* cto_ = 0, std::vector<HIST_P>* nhp = 0, std::vector<HIST_F>* nhf = 0)
	{
		if (enc < 0 || !cto_ || !nhp || !nhf)
		{
			return -1;
		}

		sint ret = -1;
		size_t siz = 0;

		while (siz < encodings.size())
		{
			if (encodings[siz] == enc)
			{
				ret = (sint)siz;

				if (cto_)
				{
					if (siz < constituent_to.size())
					{
						for (size_t nsiz = 0; nsiz < cto_->size(); nsiz++)
						{
							for (size_t usiz = 0; usiz < constituent_to[siz].size(); usiz++)
							{
								if (constituent_to[siz][usiz].size() == cto_->at(nsiz).size())
								{
									size_t msiz = 0;

									while (msiz < cto_->at(nsiz).size())
									{
										if (memcmp(&constituent_to[siz][usiz][msiz], &cto_->at(nsiz)[msiz], 1))
										{
											msiz = cto_->at(nsiz).size();
										}
										msiz++;
									}
									if (msiz != cto_->at(nsiz).size())
									{
										constituent_to[siz].push_back(cto_->at(nsiz));
									}
								}
							}
						}
					}
					else if (siz == constituent_to.size())
					{
						constituent_to.push_back(*cto_);
					}
					else
					{
						while (siz > constituent_to.size())
						{
							std::vector<std::vector<u_char>> vec;
							constituent_to.push_back(vec);
							siz++;
						}
						constituent_to.push_back(*cto_);
					}
				}
				if (nhp)
				{
					for (size_t nsiz = 0; nsiz < nhp->size(); nsiz++)
					{
						history_preceeding[siz].push_back(nhp->at(nsiz));
					}
				}
				if (nhf)
				{
					for (size_t nsiz = 0; nsiz < nhf->size(); nsiz++)
					{
						history_following[siz].push_back(nhf->at(nsiz));
					}
				}
				siz = encodings.size();
			}
			siz++;
		}
		if (siz == encodings.size())
		{
			ret = (sint)siz;
			encodings.push_back(enc);

			if (cto_)
			{
				constituent_to.push_back(*cto_);
			}
			else
			{
				std::vector<std::vector<u_char>> vec;
				constituent_to.push_back(vec);
			}
			if (nhp)
			{
				history_preceeding.push_back(*nhp);
			}
			else
			{
				std::vector<HIST_P> vec;
				history_preceeding.push_back(vec);
			}
			if (nhf)
			{
				history_following.push_back(*nhf);
			}
			else
			{
				std::vector<HIST_F> vec;
				history_following.push_back(vec);
			}
		}
		Proc();
		return ret;
	}
	
	
	MICSYM(u_char* nsym = 0, sint nencoding = -1, std::vector<std::vector<u_char>>* ncto_ = 0, std::vector<HIST_P>* hp = 0, std::vector<HIST_F>* hf = 0) { ud_id = ud_history_following = ud_history_preceeding = ud_last_maintained = ud_last_modified = ud_last_maintained_ns = ud_last_modified_ns = false; last_maintained = last_modified = last_maintained_ns = last_modified_ns = id = loc = -1; constituent_to.clear(); encodings.clear(); history_following.clear(); history_preceeding.clear(); sym = BOT_BOUND_UCHR; if (nsym) { memcpy(&sym, &nsym[0], 1); } if (nencoding > -1) { AddEnc(nencoding, ncto_, hp, hf); } }

	private:

};

typedef struct hist_pv
{
	std::vector<MICSYM> cons;
	uint ct;

	hist_pv(std::vector<MICSYM>* nsym = 0, uint nct = 0) { ct = nct; if (nsym) { if (!ct) { ct++; } for (size_t siz = 0; siz < nsym->size(); siz++) { cons.push_back(nsym->at(siz)); } } }

}HIST_PV;

typedef struct hist_fv
{
	std::vector<MICSYM> cons;
	uint ct;

	hist_fv(std::vector<MICSYM>* nsym = 0, uint nct = 0) { ct = nct; if (nsym) { if (!ct) { ct++; } for (size_t siz = 0; siz < nsym->size(); siz++) { cons.push_back(nsym->at(siz)); } } }

}HIST_FV;

enum MACSYM_MEMS
{
	SYM_ID = 0,
	SYM_CONS = 1,
	SYM_PAIR_SYM = 2,
	SYM_USAGES = 3,
	SYM_USED = 4,
	SYM_ALTER = 5,
	SYM_HF = 6,
	SYM_HP = 7,
	SYM_MAINT = 8,
	SYM_MAINT_NS = 9,
	SYM_MOD = 10,
	SYM_MOD_NS = 11,
	SYM_MAX = 12
};

class MACSYM
{
public:

	bool ud_id;
	sint id;
	bool ud_cons;
	std::vector <MICSYM> cons;
	bool ud_pair_sym;
	std::vector <MICSYM> pair_sym;
	bool ud_usages;
	std::vector<sint> usages;
	bool ud_used;
	std::vector<uint> used;
	bool ud_alters;
	std::vector<std::vector<u_char>> alters;
	bool ud_history_following;
	std::vector<std::vector<HIST_PV>> history_preceeding;
	bool ud_history_preceeding;
	std::vector<std::vector<HIST_FV>> history_following;
	bool ud_last_maintained;
	sint last_maintained;
	bool ud_last_modified;
	sint last_modified;
	bool ud_last_maintained_ns;
	sint last_maintained_ns;
	bool ud_last_modified_ns;
	sint last_modified_ns;

	sint used_as;

	sint cmpto(MACSYM* val_ = 0)
	{
		if (id != val_->id ||
			used_as != val_->used_as ||
			last_maintained != val_->last_maintained ||
			last_maintained_ns != val_->last_maintained_ns ||
			last_modified != val_->last_modified ||
			last_modified_ns != val_->last_modified_ns ||
			cons.size() != val_->cons.size() ||
			pair_sym.size() != val_->pair_sym.size() ||
			usages.size() != val_->usages.size() ||
			used.size() != val_->used.size() ||
			alters.size() != val_->alters.size() ||
			history_preceeding.size() != val_->history_preceeding.size() ||
			history_following.size() != val_->history_following.size())
		{
			return -1;
		}

		for (uint x = 0; x < cons.size(); x++)
		{
			if (memcmp((void*)&cons[x].sym, (void*)&val_->cons[x].sym, sizeof(cons[x].sym)))
			{
				return -1;
			}
		}
		for (uint x = 0; x < pair_sym.size(); x++)
		{
			if (memcmp((void*)&pair_sym[x].sym, (void*)&val_->pair_sym[x].sym, sizeof(pair_sym[x].sym)))
			{
				return -1;
			}
		}
		for (uint x = 0; x < usages.size(); x++)
		{
			if (usages[x] != val_->usages[x])
			{
				return -1;
			}
		}
		for (uint x = 0; x < alters.size(); x++)
		{
			for (uint y = 0; y < alters.size(); y++)
			{
				if (memcmp((void*)&alters[x][y], (void*)&val_->alters[x][y], sizeof(alters[x][y])))
				{
					return -1;
				}
			}
		}
		for (uint x = 0; x < history_preceeding.size(); x++)
		{
			for (uint y = 0; y < history_preceeding.size(); y++)
			{
				for (uint z = 0; z < history_preceeding[x][y].cons.size(); z++)
				{
					if (memcmp((void*)&history_preceeding[x][y].cons[z].sym, (void*)&val_->history_preceeding[x][y].cons[z].sym, sizeof(history_preceeding[x][y].cons[z].sym)))
					{
						return -1;
					}
				}
			}
		}
		for (uint x = 0; x < history_following.size(); x++)
		{
			for (uint y = 0; y < history_following.size(); y++)
			{
				for (uint z = 0; z < history_following[x][y].cons.size(); z++)
				{
					if (memcmp((void*)&history_following[x][y].cons[z].sym, (void*)&val_->history_following[x][y].cons[z].sym, sizeof(history_following[x][y].cons[z].sym)))
					{
						return -1;
					}
				}
			}
		}
		return 0;
	}
	void Clear() { cons.clear(); pair_sym.clear(); usages.clear(); used.clear(); alters.clear(); history_preceeding.clear(); history_following.clear(); used_as = id = last_maintained = last_modified = last_maintained_ns = last_modified_ns = -1; ud_id = ud_cons = ud_pair_sym = ud_usages = ud_used = ud_alters = ud_history_preceeding = ud_history_following = ud_last_modified = ud_last_maintained = ud_last_maintained_ns = ud_last_maintained_ns = false; }
	void Renew(MACSYM* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		id = val_->id;
		used_as = val_->used_as;
		last_maintained = val_->last_maintained;
		last_maintained_ns = val_->last_maintained_ns;
		last_modified = val_->last_modified;
		last_modified_ns = val_->last_modified_ns;
		cons.swap(val_->cons);
		pair_sym.swap(val_->pair_sym);
		usages.swap(val_->usages);
		used.swap(val_->used);
		alters.swap(val_->alters);
		history_preceeding.swap(val_->history_preceeding);
		history_following.swap(val_->history_following);
	}
	void Renew(sint nua = -1, u_char ncons[] = 0, sint nencoding = -1, std::vector<HIST_PV>* nhp_v = 0, std::vector<HIST_FV>* nhf_v = 0)
	{
		Clear();
		used_as = nua;
		id = -1;
		
		if (ncons)
		{
			RenderCons(ncons, nencoding);
		}
		
		if (nua > -1)
		{
			AddUse(nua, 1, nhp_v, nhf_v);
		}
	}

	sint Proc(sint memb = -1)
	{
		if (memb < 0)
		{
			for (size_t siz = 0; siz < usages.size(); siz++)
			{
				for (size_t nsiz = siz+1; nsiz < usages.size(); nsiz++)
				{
					if (usages[siz] == usages[nsiz])
					{
						if (nsiz < used.size())
						{
							used[siz] += used[nsiz];
							used[nsiz] = 0;
						}
						if (nsiz < alters.size())
						{
							for (size_t usiz = 0; usiz < alters[nsiz].size(); usiz++)
							{
								alters[siz].push_back(alters[nsiz][usiz]);
							}
							alters[nsiz].clear();
						}
						if (nsiz < history_preceeding.size())
						{
							for (size_t usiz = 0; usiz < history_preceeding[nsiz].size(); usiz++)
							{
								history_preceeding[siz].push_back(history_preceeding[nsiz][usiz]);
							}
							history_preceeding[nsiz].clear();
						}
						if (nsiz < history_following.size())
						{
							for (size_t usiz = 0; usiz < history_following[nsiz].size(); usiz++)
							{
								history_following[siz].push_back(history_following[nsiz][usiz]);
							}
							history_following[nsiz].clear();
						}
						usages[nsiz] = -1;
					}
				}
			}
			if (!usages.empty())
			{
				std::vector<sint> usedv;
				for (size_t siz = 0; siz < usages.size(); siz++)
				{
					if (usages[siz] > -1)
					{
						usedv.push_back(usages[siz]);
					}
				}
				if (usedv.size() != usages.size())
				{
					usages.clear();
					for (size_t siz = 0; siz < usedv.size(); siz++)
					{
						usages.push_back(usedv[siz]);
					}
				}
			}
			if (!used.empty())
			{
				std::vector<uint> usedv;
				for (size_t siz = 0; siz < used.size(); siz++)
				{
					if (used[siz])
					{
						usedv.push_back(used[siz]);
					}
				}
				if (usedv.size() != used.size())
				{
					used.clear();
					for (size_t siz = 0; siz < usedv.size(); siz++)
					{
						used.push_back(usedv[siz]);
					}
				}
			}
			while (used.size() > usages.size())
			{
				used.pop_back();
			}
			if (!history_preceeding.empty())
			{
				std::vector<std::vector<HIST_PV>> hp_v;
				for (size_t siz = 0; siz < history_preceeding.size(); siz++)
				{
					if (!history_preceeding[siz].empty())
					{
						hp_v.push_back(history_preceeding[siz]);
					}
				}
				if (hp_v.size() != history_preceeding.size())
				{
					history_preceeding.clear();
					for (size_t siz = 0; siz < hp_v.size(); siz++)
					{
						history_preceeding.push_back(hp_v[siz]);
					}
				}
			}
			while (history_preceeding.size() > usages.size())
			{
				history_preceeding.pop_back();
			}
			if (!history_following.empty())
			{
				std::vector<std::vector<HIST_FV>> hf_v;
				for (size_t siz = 0; siz < history_following.size(); siz++)
				{
					if (!history_following[siz].empty())
					{
						hf_v.push_back(history_following[siz]);
					}
				}
				if (hf_v.size() != history_following.size())
				{
					history_following.clear();
					for (size_t siz = 0; siz < hf_v.size(); siz++)
					{
						history_following.push_back(hf_v[siz]);
					}
				}
			}
			while (history_following.size() > usages.size())
			{
				history_following.pop_back();
			}
			for (size_t siz = 0; siz < alters.size(); siz++)
			{
				if (!alters[siz].empty())
				{
					for (size_t nsiz = siz + 1; nsiz < alters.size(); nsiz++)
					{
						if (alters[siz].size() == alters[nsiz].size())
						{
							size_t usiz = 0;
							while (usiz < alters[nsiz].size())
							{
								if (memcmp(&alters[siz][usiz], &alters[nsiz][usiz], sizeof(alters[siz][usiz])))
								{
									usiz = alters[nsiz].size();
								}
								usiz++;
							}
							if (usiz == alters[nsiz].size())
							{
								alters[nsiz].clear();
							}
						}
					}
				}
			}
			if (!alters.empty())
			{
				std::vector<std::vector<u_char>> alterv;
				for (size_t siz = 0; siz < alters.size(); siz++)
				{
					if (!alters[siz].empty())
					{
						alterv.push_back(alters[siz]);
					}
				}
				if (alterv.size() != alters.size())
				{
					alters.clear();
					for (size_t siz = 0; siz < alterv.size(); siz++)
					{
						alters.push_back(alterv[siz]);
					}
				}
			}
			while (alters.size() > usages.size())
			{
				alters.pop_back();
			}
			for (size_t siz = 0; siz < history_preceeding.size(); siz++)
			{
				for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
				{
					for (size_t usiz = nsiz+1; usiz < history_preceeding[siz].size(); usiz++)
					{
						if (history_preceeding[siz][nsiz].cons.size() == history_preceeding[siz][usiz].cons.size())
						{
							size_t xsiz = 0;
							while (xsiz < history_preceeding[siz][usiz].cons.size())
							{
								if (memcmp(&history_preceeding[siz][usiz].cons[xsiz].sym, &history_preceeding[siz][nsiz].cons[xsiz].sym, sizeof(history_preceeding[siz][usiz].cons[xsiz].sym)))
								{
									xsiz = history_preceeding[siz][usiz].cons.size();
								}
								xsiz++;
							}
							if (xsiz == history_preceeding[siz][usiz].cons.size())
							{
								history_preceeding[siz][nsiz].ct += history_preceeding[siz][usiz].ct;
								history_preceeding[siz][usiz].cons.clear();
							}
						}
					}
				}
				if (!history_preceeding[siz].empty())
				{
					std::vector<HIST_PV> hp_v;
					for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
					{
						if (!history_preceeding[siz][nsiz].cons.empty())
						{
							hp_v.push_back(history_preceeding[siz][nsiz]);
						}
					}
					if (hp_v.size() != history_preceeding[siz].size())
					{
						history_preceeding[siz].clear();
						for (size_t nsiz = 0; nsiz < hp_v.size(); nsiz++)
						{
							history_preceeding[siz].push_back(hp_v[nsiz]);
						}
					}
				}
			}
			for (size_t siz = 0; siz < history_following.size(); siz++)
			{
				for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
				{
					for (size_t usiz = nsiz + 1; usiz < history_following[siz].size(); usiz++)
					{
						if (history_following[siz][nsiz].cons.size() == history_following[siz][usiz].cons.size())
						{
							size_t xsiz = 0;
							while (xsiz < history_following[siz][usiz].cons.size())
							{
								if (memcmp(&history_following[siz][usiz].cons[xsiz].sym, &history_following[siz][nsiz].cons[xsiz].sym, sizeof(history_following[siz][usiz].cons[xsiz].sym)))
								{
									xsiz = history_following[siz][usiz].cons.size();
								}
								xsiz++;
							}
							if (xsiz == history_following[siz][usiz].cons.size())
							{
								history_following[siz][nsiz].ct += history_following[siz][usiz].ct;
								history_following[siz][usiz].cons.clear();
							}
						}
					}
				}
				if (!history_following[siz].empty())
				{
					std::vector<HIST_FV> hf_v;
					for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
					{
						if (!history_following[siz][nsiz].cons.empty())
						{
							hf_v.push_back(history_following[siz][nsiz]);
						}
					}
					if (hf_v.size() != history_following[siz].size())
					{
						history_following[siz].clear();
						for (size_t nsiz = 0; nsiz < hf_v.size(); nsiz++)
						{
							history_following[siz].push_back(hf_v[nsiz]);
						}
					}
				}
			}
		}
		else
		{
			switch (memb)
			{
			case SYM_USAGES:
			{
				Proc(-1);
				break;
			}
			case SYM_HF:
			{
				for (size_t siz = 0; siz < history_following.size(); siz++)
				{
					for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
					{
						for (size_t usiz = nsiz + 1; usiz < history_following[siz].size(); usiz++)
						{
							if (history_following[siz][nsiz].cons.size() == history_following[siz][usiz].cons.size())
							{
								size_t xsiz = 0;
								while (xsiz < history_following[siz][usiz].cons.size())
								{
									if (memcmp(&history_following[siz][usiz].cons[xsiz].sym, &history_following[siz][nsiz].cons[xsiz].sym, sizeof(history_following[siz][usiz].cons[xsiz].sym)))
									{
										xsiz = history_following[siz][usiz].cons.size();
									}
									xsiz++;
								}
								if (xsiz == history_following[siz][usiz].cons.size())
								{
									history_following[siz][nsiz].ct += history_following[siz][usiz].ct;
									history_following[siz][usiz].cons.clear();
								}
							}
						}
					}
					if (!history_following[siz].empty())
					{
						std::vector<HIST_FV> hf_v;
						for (size_t nsiz = 0; nsiz < history_following[siz].size(); nsiz++)
						{
							if (!history_following[siz][nsiz].cons.empty())
							{
								hf_v.push_back(history_following[siz][nsiz]);
							}
						}
						if (hf_v.size() != history_following[siz].size())
						{
							history_following[siz].clear();
							for (size_t nsiz = 0; nsiz < hf_v.size(); nsiz++)
							{
								history_following[siz].push_back(hf_v[nsiz]);
							}
						}
					}
				}
				break;
			}
			case SYM_HP:
			{
				for (size_t siz = 0; siz < history_preceeding.size(); siz++)
				{
					for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
					{
						for (size_t usiz = nsiz + 1; usiz < history_preceeding[siz].size(); usiz++)
						{
							if (history_preceeding[siz][nsiz].cons.size() == history_preceeding[siz][usiz].cons.size())
							{
								size_t xsiz = 0;
								while (xsiz < history_preceeding[siz][usiz].cons.size())
								{
									if (memcmp(&history_preceeding[siz][usiz].cons[xsiz].sym, &history_preceeding[siz][nsiz].cons[xsiz].sym, sizeof(history_preceeding[siz][usiz].cons[xsiz].sym)))
									{
										xsiz = history_preceeding[siz][usiz].cons.size();
									}
									xsiz++;
								}
								if (xsiz == history_preceeding[siz][usiz].cons.size())
								{
									history_preceeding[siz][nsiz].ct += history_preceeding[siz][usiz].ct;
									history_preceeding[siz][usiz].cons.clear();
								}
							}
						}
					}
					if (!history_preceeding[siz].empty())
					{
						std::vector<HIST_PV> hp_v;
						for (size_t nsiz = 0; nsiz < history_preceeding[siz].size(); nsiz++)
						{
							if (!history_preceeding[siz][nsiz].cons.empty())
							{
								hp_v.push_back(history_preceeding[siz][nsiz]);
							}
						}
						if (hp_v.size() != history_preceeding[siz].size())
						{
							history_preceeding[siz].clear();
							for (size_t nsiz = 0; nsiz < hp_v.size(); nsiz++)
							{
								history_preceeding[siz].push_back(hp_v[nsiz]);
							}
						}
					}
				}
				break;
			}
			case SYM_ALTER:
			{
				for (size_t siz = 0; siz < alters.size(); siz++)
				{
					if (!alters[siz].empty())
					{
						for (size_t nsiz = siz + 1; nsiz < alters.size(); nsiz++)
						{
							if (alters[siz].size() == alters[nsiz].size())
							{
								size_t usiz = 0;
								while (usiz < alters[nsiz].size())
								{
									if (memcmp(&alters[siz][usiz], &alters[nsiz][usiz], sizeof(alters[siz][usiz])))
									{
										usiz = alters[nsiz].size();
									}
									usiz++;
								}
								if (usiz == alters[nsiz].size())
								{
									alters[nsiz].clear();
								}
							}
						}
					}
				}
				if (!alters.empty())
				{
					std::vector<std::vector<u_char>> alterv;
					for (size_t siz = 0; siz < alters.size(); siz++)
					{
						if (!alters[siz].empty())
						{
							alterv.push_back(alters[siz]);
						}
					}
					if (alterv.size() != alters.size())
					{
						alters.clear();
						for (size_t siz = 0; siz < alterv.size(); siz++)
						{
							alters.push_back(alterv[siz]);
						}
					}
				}
				while (alters.size() > usages.size())
				{
					alters.pop_back();
				}
				break;
			}
			case SYM_USED:
			case SYM_CONS:
			case SYM_PAIR_SYM:
			case SYM_ID:
			case SYM_MAINT:
			case SYM_MAINT_NS:
			case SYM_MOD:
			case SYM_MOD_NS:
			case SYM_MAX:
			{
				break;
			}
			default:
			{
				break;
			}
			}
		}
		return 0;
	}
	sint AddUse(sint use = -1, uint used_ = 0, std::vector<HIST_PV>* nhp = 0, std::vector<HIST_FV>* nhf = 0)
	{
		if (use < 1)
		{
			return -1;
		}
		sint ret = -1;
		size_t siz = 0;
		while (siz < usages.size())
		{
			if (usages[siz] == use)
			{
				ret = (sint)siz;

				if (used_ > 0)
				{
					used[siz] += used_;
				}
				if (nhp)
				{
					if (siz < history_preceeding.size())
					{
						for (size_t nsiz = 0; nsiz < nhp->size(); nsiz++)
						{
							history_preceeding[siz].push_back(nhp->at(nsiz));
						}
					}
				}
				if (nhf)
				{
					if(siz < history_following.size())
					{
						for (size_t nsiz = 0; nsiz < nhf->size(); nsiz++)
						{
							history_following[siz].push_back(nhf->at(nsiz));
						}
					}
				}
				siz = usages.size();
			}
			siz++;
		}
		if (siz == usages.size())
		{
			ret = (sint)siz;
			usages.push_back(use);

			if (used_)
			{
				used.push_back(used_);
			}
			else
			{
				used.push_back(1);
			}
			if (nhp)
			{
				history_preceeding.push_back(*nhp);
			}
			else
			{
				std::vector<HIST_PV> vec;
				history_preceeding.push_back(vec);
			}
			if (nhf)
			{
				history_following.push_back(*nhf);
			}
			else
			{
				std::vector<HIST_FV> vec;
				history_following.push_back(vec);
			}
		}
		return ret;
	}
	sint PairSym(std::vector<MICSYM>* vec_ = 0)
	{
		if (!vec_)
		{
			return -1;
		}

		if (!pair_sym.empty())
		{
			pair_sym.clear();
		}
		for (size_t siz = 0; siz < vec_->size(); siz++)
		{
			pair_sym.push_back(vec_->at(siz));
		}
		return 0;
	}
	sint RenderCons(u_char sym[], sint encoding = -1)
	{
		if (!sym)
		{
			return -1;
		}
		sint ssiz = (sint)bot_ustrlen(sym);

		if (ssiz)
		{
			std::vector<u_char> ftvec;

			for (sint rc = 0; rc < ssiz; rc++)
			{
				ftvec.push_back(sym[rc]);
			}
			for (sint rc = 0; rc < ssiz; rc++)
			{
				std::vector<HIST_P> hp_v;
				std::vector<HIST_F> hf_v;

				if (rc)
				{
					HIST_P hp(&sym[rc-1],1);
					hp_v.push_back(hp);
				}
				else
				{
					u_char xcar = BOT_BOUND_UCHR;
					HIST_P hp(&xcar, 1);
					hp_v.push_back(hp);
				}

				if (rc < ssiz - 1)
				{
					HIST_F hp(&sym[rc + 1], 1);
					hf_v.push_back(hp);
				}
				else
				{
					u_char xcar = BOT_BOUND_UCHR;
					HIST_F hp(&xcar, 1);
					hf_v.push_back(hp);
				}

				std::vector<std::vector<u_char>> nftvec;
				nftvec.push_back(ftvec);
				MICSYM nss(&sym[rc], encoding, &nftvec, &hp_v, &hf_v);
				nss.AddEnc(encoding, &nftvec, &hp_v, &hf_v);
				cons.push_back(nss);
			}
			return 0;
		}
		return -1;
	}

	MACSYM(sint nua = -1, u_char ncons[] = 0, sint nencoding = -1, std::vector<HIST_PV>* nhp_v = 0, std::vector<HIST_FV>* nhf_v = 0) { ud_id = ud_usages = ud_cons = ud_pair_sym = ud_history_following = ud_history_preceeding = ud_last_maintained = ud_last_modified = ud_last_maintained_ns = ud_last_modified_ns = ud_used = ud_alters = false; used_as = nua; id = -1; if (ncons) { RenderCons(ncons, nencoding); } if (nua > -1) { AddUse(nua, 1, nhp_v, nhf_v); } }

private:

};

typedef struct bot_crs
{
	sllint fid;
	sint lid;
	size_t f;
	size_t t;
	size_t w;

	bot_crs(sllint nfid = -1, sint nlid = -1, size_t nf = 0, size_t nt = 0) { lid = nlid; fid = nfid; if (nf <= nt) { f = nf; t = nt; } else { f = nf; t = nf + 1; } w = (t - f) + 1; }

}BOT_CRS;

class bot_fstate
{
public:
	size_t e_loc;
	size_t oa_loc;
	size_t ia_loc;
	sint exists;
	_char fbyte;
	std::vector<MACSYM> seps;

	std::vector<_char> compv;
	std::vector<ullint> cts;

	std::vector<std::vector<ullint>> locs;
	std::vector<std::vector<ullint>> lins;
	std::vector<std::vector<std::vector<ullint>>> loc_in_lin;

	std::vector<ullint> mean_loc;
	std::vector<ullint> mean_spc;
	std::vector<ullint> med_spc;
	std::vector<ullint> mean_spc_var;
	std::vector<ullint> mean_lens;
	std::vector<ullint> med_lens;
	std::vector<ullint> mean_lens_var;
	std::vector<ullint> mean_linct;
	std::vector<ullint> med_linct;
	std::vector<ullint> mean_linct_var;
	std::vector<ullint> mean_linl;
	std::vector<ullint> med_linl;
	std::vector<ullint> mean_linl_var;

#ifdef _WIN32
	struct _stat filestats;
#else
	struct stat filestats;
#endif

	void ClearStats() { filestats.st_atime = 0; filestats.st_ctime = 0; filestats.st_dev = 0; filestats.st_ino = 0; filestats.st_mode = 0; filestats.st_mtime = 0; filestats.st_nlink = 0; filestats.st_rdev = 0; filestats.st_size = 0; filestats.st_uid = 0; }
	void Clear()
	{
		ClearStats();
		e_loc = oa_loc = ia_loc = 0; 
		exists = -1;
		fbyte = '\0';
		seps.clear();
		compv.clear();
		cts.clear();
		locs.clear();
		lins.clear();
		loc_in_lin.clear();
		mean_loc.clear();
		mean_spc.clear();
		med_spc.clear();
		mean_spc_var.clear();
		mean_lens.clear();
		med_lens.clear();
		mean_lens_var.clear();
		mean_linct.clear();
		med_linct.clear();
		mean_linct_var.clear();
		mean_linl.clear();
		med_linl.clear();
		mean_linl_var.clear();
	}
	sint AddSep(MACSYM* ns = 0)
	{
		if (!ns)
		{
			return -1;
		}

		uint x = 0;

		while (x < seps.size())
		{
			if (!ns->cmpto(&seps[x]))
			{
				return (sint)x;
			}
			x++;
		}

		if (x == seps.size())
		{
			seps.push_back(*ns);
		}
		return (sint)x;
	}
	void comb(bot_fstate* nst = 0)
	{
		if (!nst)
		{
			return;
		}

		if (!locs.empty())
		{
			AvgSyms();
		}
		if (!nst->locs.empty())
		{
			nst->AvgSyms();
		}
		for (uint x = 0; x < nst->compv.size(); x++)
		{
			uint y = 0;

			while (y < compv.size())
			{
				if (!memcmp((void*)&nst->compv[x], (void*)&compv[y], sizeof(_char)))
				{
					cts[y] += nst->cts[x];
					float cur_q = (float)(e_loc - ia_loc);
					float n_q = (float)(nst->e_loc - nst->ia_loc);

					if (mean_loc[y] != nst->mean_loc[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_loc[y] = (ullint)(((float)mean_loc[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_loc[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_spc[y] != nst->mean_spc[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_spc[y] = (ullint)(((float)mean_spc[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_spc[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (med_spc[y] != nst->med_spc[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							
							med_spc[y] = (ullint)(((float)med_spc[y] * (cur_q / (cur_q + n_q))) + ((float)nst->med_spc[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_spc_var[y] != nst->mean_spc_var[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_spc_var[y] = (ullint)(((float)mean_spc_var[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_spc_var[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_lens[y] != nst->mean_lens[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_lens[y] = (ullint)(((float)mean_lens[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_lens[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (med_lens[y] != nst->med_lens[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{

							med_lens[y] = (ullint)(((float)med_lens[y] * (cur_q / (cur_q + n_q))) + ((float)nst->med_lens[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_lens_var[y] != nst->mean_lens_var[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_lens_var[y] = (ullint)(((float)mean_lens_var[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_lens_var[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_linct[y] != nst->mean_linct[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_linct[y] = (ullint)(((float)mean_linct[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_linct[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (med_linct[y] != nst->med_linct[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{

							med_linct[y] = (ullint)(((float)med_linct[y] * (cur_q / (cur_q + n_q))) + ((float)nst->med_linct[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_linct_var[y] != nst->mean_linct_var[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_linct_var[y] = (ullint)(((float)mean_linct_var[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_linct_var[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_linl[y] != nst->mean_linl[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_linl[y] = (ullint)(((float)mean_linl[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_linl[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (med_linl[y] != nst->med_linl[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{

							med_linl[y] = (ullint)(((float)med_linl[y] * (cur_q / (cur_q + n_q))) + ((float)nst->med_linl[x] * (n_q / (cur_q + n_q))));
						}
					}
					if (mean_linl_var[y] != nst->mean_linl_var[x])
					{
						if (e_loc > ia_loc && nst->e_loc > nst->ia_loc)
						{
							mean_linl_var[y] = (ullint)(((float)mean_linl_var[y] * (cur_q / (cur_q + n_q))) + ((float)nst->mean_linl_var[x] * (n_q / (cur_q + n_q))));
						}
					}
					y = compv.size();
				}
				y++;
			}
			if (y == compv.size())
			{
				compv.push_back(nst->compv[x]);
				std::vector<ullint> nvec;
				locs.push_back(nvec);

				for (y = 0; y < nst->locs[x].size(); y++)
				{
					locs[locs.size() - 1].push_back(nst->locs[x][y]);
				}

				lins.push_back(nvec);

				for (y = 0; y < nst->lins[x].size(); y++)
				{
					lins[lins.size() - 1].push_back(nst->lins[x][y]);
				}

				std::vector<std::vector<ullint>> xvec;
				loc_in_lin.push_back(xvec);

				for (y = 0; y < nst->loc_in_lin[x].size(); y++)
				{
					loc_in_lin[loc_in_lin.size() - 1].push_back(nvec);

					for (uint z = 0; z < nst->loc_in_lin[x][y].size(); z++)
					{
						loc_in_lin[loc_in_lin.size() - 1][loc_in_lin[loc_in_lin.size() - 1].size() - 1].push_back(nst->loc_in_lin[x][y][z]);
					}
				}
			}
		}
		if (nst->ia_loc < ia_loc)
		{
			ia_loc = nst->ia_loc;
		}
		if (nst->e_loc > e_loc)
		{
			e_loc = nst->e_loc;
		}
	}
	void Renew(bot_fstate* nst = 0)
	{
		Clear();

		if (!nst)
		{
			return;
		}

		e_loc = nst->e_loc;
		oa_loc = nst->oa_loc;
		ia_loc = nst->ia_loc;
		exists = nst->exists;

		for (uint x = 0; x < nst->seps.size(); x++)
		{
			seps.push_back(nst->seps[x]);
		}
		for (uint x = 0; x < nst->compv.size(); x++)
		{
			compv.push_back(nst->compv[x]);
		}
		for (uint x = 0; x < nst->cts.size(); x++)
		{
			cts.push_back(nst->cts[x]);
		}
		for (uint x = 0; x < nst->locs.size(); x++)
		{
			std::vector<ullint> nvec;
			
			for (uint y = 0; y < nst->locs[x].size(); y++)
			{
				nvec.push_back(nst->locs[x][y]);
			}
			locs.push_back(nvec);
		}
		for (uint x = 0; x < nst->lins.size(); x++)
		{
			std::vector<ullint> nvec;

			for (uint y = 0; y < nst->lins[x].size(); y++)
			{
				nvec.push_back(nst->lins[x][y]);
			}
			lins.push_back(nvec);
		}
		for (uint x = 0; x < nst->loc_in_lin.size(); x++)
		{
			std::vector<std::vector<ullint>> nvec;

			for (uint y = 0; y < nst->loc_in_lin[x].size(); y++)
			{
				std::vector<ullint> xvec;

				for (uint z = 0; z < nst->loc_in_lin[x][y].size(); z++)
				{
					xvec.push_back(nst->loc_in_lin[x][y][z]);
				}
				nvec.push_back(xvec);
			}
			loc_in_lin.push_back(nvec);
		}
		for (uint x = 0; x < nst->mean_loc.size(); x++)
		{
			mean_loc.push_back(nst->mean_loc[x]);
		}
		for (uint x = 0; x < nst->mean_spc.size(); x++)
		{
			mean_spc.push_back(nst->mean_spc[x]);
		}
		for (uint x = 0; x < nst->med_spc.size(); x++)
		{
			med_spc.push_back(nst->med_spc[x]);
		}
		for (uint x = 0; x < nst->mean_spc_var.size(); x++)
		{
			mean_spc_var.push_back(nst->mean_spc_var[x]);
		}
		for (uint x = 0; x < nst->mean_lens.size(); x++)
		{
			mean_lens.push_back(nst->mean_lens[x]);
		}
		for (uint x = 0; x < nst->med_lens.size(); x++)
		{
			med_lens.push_back(nst->med_lens[x]);
		}
		for (uint x = 0; x < nst->mean_lens_var.size(); x++)
		{
			mean_lens_var.push_back(nst->mean_lens_var[x]);
		}
		for (uint x = 0; x < nst->mean_linct.size(); x++)
		{
			mean_linct.push_back(nst->mean_linct[x]);
		}
		for (uint x = 0; x < nst->med_linct.size(); x++)
		{
			med_linct.push_back(nst->med_linct[x]);
		}
		for (uint x = 0; x < nst->mean_linct_var.size(); x++)
		{
			mean_linct_var.push_back(nst->mean_linct_var[x]);
		}
		for (uint x = 0; x < nst->mean_linl.size(); x++)
		{
			mean_linl.push_back(nst->mean_linl[x]);
		}
		for (uint x = 0; x < nst->med_linl.size(); x++)
		{
			med_linl.push_back(nst->med_linl[x]);
		}
		for (uint x = 0; x < nst->mean_linl_var.size(); x++)
		{
			mean_linl_var.push_back(nst->mean_linl_var[x]);
		}

		RenewStats(&nst->filestats);
		RenewLocs(nst->e_loc, nst->oa_loc, nst->ia_loc);

		for (uint x = 0; x < compv.size(); x++)
		{
			sint xc = ReorderVs((sint)x);
		}
	}
	void RenewLocs(size_t ne_loc = 0, size_t noa_loc = 0, size_t nia_loc = 0)
	{
		e_loc = ne_loc;
		oa_loc = noa_loc;
		ia_loc = nia_loc;
	}

#ifdef _WIN32
	void RenewStats(struct _stat* nstat = 0)
	{
		if (!nstat)
		{
			return;
		}

		filestats.st_atime = nstat->st_atime;
		filestats.st_ctime = nstat->st_ctime;
		filestats.st_dev = nstat->st_dev;
		filestats.st_ino = nstat->st_ino;
		filestats.st_mode = nstat->st_mode;
		filestats.st_mtime = nstat->st_mtime;
		filestats.st_nlink = nstat->st_nlink;
		filestats.st_rdev = nstat->st_rdev;
		filestats.st_size = nstat->st_size;
		filestats.st_uid = nstat->st_uid;
	}
#else
	void RenewStats(struct stat* nstat = 0)
	{
		if (!nstat)
		{
			return;
		}

		filestats.st_atime = nstat->st_atime;
		filestats.st_ctime = nstat->st_ctime;
		filestats.st_dev = nstat->st_dev;
		filestats.st_ino = nstat->st_ino;
		filestats.st_mode = nstat->st_mode;
		filestats.st_mtime = nstat->st_mtime;
		filestats.st_nlink = nstat->st_nlink;
		filestats.st_rdev = nstat->st_rdev;
		filestats.st_size = nstat->st_size;
		filestats.st_uid = nstat->st_uid;
	}
#endif
	
#ifdef _WIN32
	sint cmpstats(struct _stat* nstat = 0)
	{
		sint ret = 0;
		if (!nstat)
		{
			return -1;
		}
		if (memcmp((void*)&filestats.st_atime, (void*)&nstat->st_atime, sizeof(nstat->st_atime)))
		{
			ret++;
		}
		if (memcmp((void*)&filestats.st_ctime, (void*)&nstat->st_ctime, sizeof(nstat->st_ctime)))
		{
			ret+=3;
		}
		if (memcmp((void*)&filestats.st_nlink, (void*)&nstat->st_nlink, sizeof(nstat->st_nlink)))
		{
			ret+=7;
		}
		if (memcmp((void*)&filestats.st_ino, (void*)&nstat->st_ino, sizeof(nstat->st_ino)))
		{
			ret+=17;
		}
		if (memcmp((void*)&filestats.st_mode, (void*)&nstat->st_mode, sizeof(nstat->st_mode)))
		{
			ret+=37;
		}
		if (memcmp((void*)&filestats.st_rdev, (void*)&nstat->st_rdev, sizeof(nstat->st_rdev)))
		{
			ret+=79;
		}
		if (memcmp((void*)&filestats.st_dev, (void*)&nstat->st_dev, sizeof(nstat->st_dev)))
		{
			ret+=167;
		}
		if (memcmp((void*)&filestats.st_mtime, (void*)&nstat->st_mtime, sizeof(nstat->st_mtime)))
		{
			ret+=337;
		}
		if (memcmp((void*)&filestats.st_size, (void*)&nstat->st_size, sizeof(nstat->st_size)))
		{
			ret+=657;
		}
		if (memcmp((void*)&filestats.st_uid, (void*)&nstat->st_uid, sizeof(nstat->st_uid)))
		{
			ret+=1317;
		}
		return ret;
	}
#else
	sint cmpstats(struct stat* nstat = 0)
	{
		sint ret = 0;
		if (!nstat)
		{
			return -1;
		}
		if (memcmp((void*)&filestats.st_atime, (void*)&nstat->st_atime, sizeof(nstat->st_atime)))
		{
			ret++;
		}
		if (memcmp((void*)&filestats.st_ctime, (void*)&nstat->st_ctime, sizeof(nstat->st_ctime)))
		{
			ret += 3;
		}
		if (memcmp((void*)&filestats.st_dev, (void*)&nstat->st_dev, sizeof(nstat->st_dev)))
		{
			ret += 7;
		}
		if (memcmp((void*)&filestats.st_ino, (void*)&nstat->st_ino, sizeof(nstat->st_ino)))
		{
			ret += 17;
		}
		if (memcmp((void*)&filestats.st_mode, (void*)&nstat->st_mode, sizeof(nstat->st_mode)))
		{
			ret += 37;
		}
		if (memcmp((void*)&filestats.st_mtime, (void*)&nstat->st_mtime, sizeof(nstat->st_mtime)))
		{
			ret += 79;
		}
		if (memcmp((void*)&filestats.st_nlink, (void*)&nstat->st_nlink, sizeof(nstat->st_nlink)))
		{
			ret += 167;
		}
		if (memcmp((void*)&filestats.st_rdev, (void*)&nstat->st_rdev, sizeof(nstat->st_rdev)))
		{
			ret += 337;
		}
		if (memcmp((void*)&filestats.st_size, (void*)&nstat->st_size, sizeof(nstat->st_size)))
		{
			ret += 657;
		}
		if (memcmp((void*)&filestats.st_uid, (void*)&nstat->st_uid, sizeof(nstat->st_uid)))
		{
			ret += 1117;
		}
		return ret;
	}
#endif
	
	sint cmpto(bot_fstate* est = 0)
	{
		if (!est)
		{
			return -1;
		}

		if (ia_loc != est->ia_loc ||
			oa_loc != est->oa_loc ||
			exists != est->exists)
		{
			return 1;
		}

		if (e_loc != est->e_loc)
		{
			return 101;
		}
		if (compv.size() != est->compv.size())
		{
			return 102;
		}

		for (size_t x = 0; x < compv.size(); x++)
		{
			size_t y = 0;

			while (y < est->compv.size())
			{
				if (cts[x] != est->cts[x] || 
					memcmp((void*)&compv[x], (void*)&est->compv[x], sizeof(_char)) || 
					locs[x].size() != est->locs[x].size() || 
					lins.size() != est->lins.size() || 
					loc_in_lin.size() != est->loc_in_lin.size())
				{
					y = est->compv.size();
				}
				y++;
			}
			if (y != est->compv.size())
			{
				return 102;
			}
		}
		return cmpstats(&est->filestats);
	}
	sint ReorderVs(sint ele = -1)
	{
		if (ele < 0)
		{
			return -1;
		}

		if (ele + 1 < (sint)cts.size())
		{
			size_t nele = (size_t)ele + 1;

			if (cts[ele] < cts[nele])
			{
				bool done = false;

				while (!done)
				{
					if (nele >= cts.size())
					{
						done = true;
						nele--;
					}
					else
					{
						if (cts[ele] >= cts[nele])
						{
							nele--;
							done = true;
						}
					}
					nele++;
				}

				_char vali;
				ullint valii = 0;
				memcpy((void*)&vali, (void*)&compv[ele], sizeof(_char));
				memcpy((void*)&compv[ele], (void*)&compv[nele], sizeof(_char));
				memcpy((void*)&compv[nele], (void*)&vali, sizeof(_char));
				valii = cts[ele];
				cts[ele] = cts[nele];
				cts[nele] = valii;
				valii = mean_loc[ele];
				mean_loc[ele] = mean_loc[nele];
				mean_loc[nele] = valii;
				valii = mean_spc[ele];
				mean_spc[ele] = mean_spc[nele];
				mean_spc[nele] = valii;
				valii = med_spc[ele];
				med_spc[ele] = med_spc[nele];
				med_spc[nele] = valii;
				valii = mean_spc_var[ele];
				mean_spc_var[ele] = mean_spc_var[nele];
				mean_spc_var[nele] = valii;
				valii = mean_lens[ele];
				mean_lens[ele] = mean_lens[nele];
				mean_lens[nele] = valii;
				valii = med_lens[ele];
				med_lens[ele] = med_lens[nele];
				med_lens[nele] = valii;
				valii = mean_lens_var[ele];
				mean_lens_var[ele] = mean_lens_var[nele];
				mean_lens_var[nele] = valii;
				valii = mean_linl[ele];
				mean_linl[ele] = mean_linl[nele];
				mean_linl[nele] = valii;
				valii = med_linl[ele];
				med_linl[ele] = med_linl[nele];
				med_linl[nele] = valii;
				valii = mean_linl_var[ele];
				mean_linl_var[ele] = mean_linl_var[nele];
				mean_linl_var[nele] = valii;
				valii = mean_linct[ele];
				mean_linct[ele] = mean_linct[nele];
				mean_linct[nele] = valii;
				valii = med_linct[ele];
				med_linct[ele] = med_linct[nele];
				med_linct[nele] = valii;
				valii = mean_linct_var[ele];
				mean_linct_var[ele] = mean_linct_var[nele];
				mean_linct_var[nele] = valii;
				std::vector<ullint> nvec;

				for (uint x = 0; x < locs[ele].size(); x++)
				{
					nvec.push_back(locs[ele][x]);
				}

				locs[ele].clear();

				for (uint x = 0; x < locs[nele].size(); x++)
				{
					locs[ele].push_back(locs[nele][x]);
				}

				locs[nele].clear();

				for (uint x = 0; x < nvec.size(); x++)
				{
					locs[nele].push_back(nvec[x]);
				}

				nvec.clear();

				for (uint x = 0; x < lins[ele].size(); x++)
				{
					nvec.push_back(lins[ele][x]);
				}

				lins[ele].clear();

				for (uint x = 0; x < lins[nele].size(); x++)
				{
					lins[ele].push_back(lins[nele][x]);
				}

				lins[nele].clear();

				for (uint x = 0; x < nvec.size(); x++)
				{
					lins[nele].push_back(nvec[x]);
				}

				nvec.clear();
				std::vector<std::vector<ullint>> uvec;

				for (uint x = 0; x < loc_in_lin[ele].size(); x++)
				{
					for (uint y = 0; y < loc_in_lin[ele][x].size(); y++)
					{
						nvec.push_back(loc_in_lin[ele][x][y]);
					}
					uvec.push_back(nvec);
					nvec.clear();
				}

				loc_in_lin[ele].clear();

				for (uint x = 0; x < loc_in_lin[nele].size(); x++)
				{
					for (uint y = 0; y < loc_in_lin[nele][x].size(); y++)
					{
						nvec.push_back(loc_in_lin[nele][x][y]);
					}

					loc_in_lin[ele].push_back(nvec);
					nvec.clear();
				}

				loc_in_lin[nele].clear();

				for (uint x = 0; x < uvec.size(); x++)
				{
					for (uint y = 0; y < uvec[x].size(); y++)
					{
						nvec.push_back(uvec[x][y]);
					}
					loc_in_lin[nele].push_back(nvec);
					nvec.clear();
				}

				uvec.clear();
			}
		}
		if (ele)
		{
			sint nele = ele - 1;

			if (cts[ele] > cts[nele])
			{
				bool done = false;

				while (!done)
				{
					nele--;

					if (nele < 0)
					{
						nele = 0;
						done = true;
					}
					else
					{
						if (cts[ele] <= cts[nele])
						{
							nele++;
							done = true;
						}
					}
				}

				_char vali;
				ullint valii = 0;
				memcpy((void*)&vali, (void*)&compv[ele], sizeof(_char));
				memcpy((void*)&compv[ele], (void*)&compv[nele], sizeof(_char));
				memcpy((void*)&compv[nele], (void*)&vali, sizeof(_char));
				valii = cts[ele];
				cts[ele] = cts[nele];
				cts[nele] = valii;
				valii = mean_loc[ele];
				mean_loc[ele] = mean_loc[nele];
				mean_loc[nele] = valii;
				valii = mean_spc[ele];
				mean_spc[ele] = mean_spc[nele];
				mean_spc[nele] = valii;
				valii = med_spc[ele];
				med_spc[ele] = med_spc[nele];
				med_spc[nele] = valii;
				valii = mean_spc_var[ele];
				mean_spc_var[ele] = mean_spc_var[nele];
				mean_spc_var[nele] = valii;
				valii = mean_lens[ele];
				mean_lens[ele] = mean_lens[nele];
				mean_lens[nele] = valii;
				valii = med_lens[ele];
				med_lens[ele] = med_lens[nele];
				med_lens[nele] = valii;
				valii = mean_lens_var[ele];
				mean_lens_var[ele] = mean_lens_var[nele];
				mean_lens_var[nele] = valii;
				valii = mean_linl[ele];
				mean_linl[ele] = mean_linl[nele];
				mean_linl[nele] = valii;
				valii = med_linl[ele];
				med_linl[ele] = med_linl[nele];
				med_linl[nele] = valii;
				valii = mean_linl_var[ele];
				mean_linl_var[ele] = mean_linl_var[nele];
				mean_linl_var[nele] = valii;
				valii = mean_linct[ele];
				mean_linct[ele] = mean_linct[nele];
				mean_linct[nele] = valii;
				valii = med_linct[ele];
				med_linct[ele] = med_linct[nele];
				med_linct[nele] = valii;
				valii = mean_linct_var[ele];
				mean_linct_var[ele] = mean_linct_var[nele];
				mean_linct_var[nele] = valii;
				std::vector<ullint> nvec;

				for (uint x = 0; x < locs[ele].size(); x++)
				{
					nvec.push_back(locs[ele][x]);
				}

				locs[ele].clear();

				for (uint x = 0; x < locs[nele].size(); x++)
				{
					locs[ele].push_back(locs[nele][x]);
				}

				locs[nele].clear();

				for (uint x = 0; x < nvec.size(); x++)
				{
					locs[nele].push_back(nvec[x]);
				}

				nvec.clear();

				for (uint x = 0; x < lins[ele].size(); x++)
				{
					nvec.push_back(lins[ele][x]);
				}

				lins[ele].clear();

				for (uint x = 0; x < lins[nele].size(); x++)
				{
					lins[ele].push_back(lins[nele][x]);
				}

				lins[nele].clear();

				for (uint x = 0; x < nvec.size(); x++)
				{
					lins[nele].push_back(nvec[x]);
				}

				nvec.clear();
				std::vector<std::vector<ullint>> uvec;

				for (uint x = 0; x < loc_in_lin[ele].size(); x++)
				{
					for (uint y = 0; y < loc_in_lin[ele][x].size(); y++)
					{
						nvec.push_back(loc_in_lin[ele][x][y]);
					}
					uvec.push_back(nvec);
					nvec.clear();
				}

				loc_in_lin[ele].clear();

				for (uint x = 0; x < loc_in_lin[nele].size(); x++)
				{
					for (uint y = 0; y < loc_in_lin[nele][x].size(); y++)
					{
						nvec.push_back(loc_in_lin[nele][x][y]);
					}

					loc_in_lin[ele].push_back(nvec);
					nvec.clear();
				}

				loc_in_lin[nele].clear();

				for (uint x = 0; x < uvec.size(); x++)
				{
					for (uint y = 0; y < uvec[x].size(); y++)
					{
						nvec.push_back(uvec[x][y]);
					}
					loc_in_lin[nele].push_back(nvec);
					nvec.clear();
				}

				uvec.clear();
			}
		}
		for (sint x = (sint)compv.size() - 1; x > -1; x--)
		{
			if (cts[x])
			{
				x = -1;
			}
			else
			{
				compv.pop_back();
				cts.pop_back();
				locs.pop_back();
				lins.pop_back();
				loc_in_lin.pop_back();
				mean_loc.pop_back();
				mean_spc.pop_back();
				med_spc.pop_back();
				mean_spc_var.pop_back();
				mean_lens.pop_back();
				med_lens.pop_back();
				mean_lens_var.pop_back();
				mean_linct.pop_back();
				med_linct.pop_back();
				mean_linct_var.pop_back();
				mean_linl.pop_back();
				med_linl.pop_back();
				mean_linl_var.pop_back();
			}
		}
		return 0;
	}
	void IncrCts(_char* val = 0, ullint loc = 0, ullint lin = 0, ullint lloc = 0)
	{
		if (!val)
		{
			return;
		}

		bool done = false;
		sint ele = 0;

		while (!done)
		{
			if (ele == (sint)compv.size())
			{
				done = true;
			}
			else
			{
				if (!memcmp((void*)&compv[ele], (void*)val, sizeof(compv[ele])))
				{
					std::vector<std::vector<ullint>> uvec;
					std::vector<ullint> nvec;
					cts[ele]++;

					while ((sint)(locs.size()) - 1 < ele)
					{
						locs.push_back(nvec);
					}

					while ((sint)(lins.size()) - 1 < ele)
					{
						lins.push_back(nvec);
						loc_in_lin.push_back(uvec);
					}

					locs[ele].push_back(loc);
					
					if (!lloc)
					{
						lins[ele].push_back(lin);
						loc_in_lin[ele].push_back(nvec);
						loc_in_lin[ele][loc_in_lin[ele].size() - 1].push_back(lloc);
					}
					else
					{
						uint x = 0;

						while (x < lins[ele].size())
						{
							if (lins[ele][x] == lin)
							{
								loc_in_lin[ele][x].push_back(lloc);
								x = lins[ele].size();
							}
							x++;
						}

						if (x == lins[ele].size())
						{
							lins[ele].push_back(lin);
							loc_in_lin[ele].push_back(nvec);
							loc_in_lin[ele][0].push_back(lloc);
						}
					}
					done = true;
				}
				else
				{
					ele++;
				}
			}
		}
		if (ele == compv.size())
		{
			compv.push_back(*val);
			cts.push_back(1);
			mean_loc.push_back(0);
			mean_spc.push_back(0);
			med_spc.push_back(0);
			mean_spc_var.push_back(0);
			mean_lens.push_back(0);
			med_lens.push_back(0);
			mean_lens_var.push_back(0);
			mean_linct.push_back(0);
			med_linct.push_back(0);
			mean_linct_var.push_back(0);
			mean_linl.push_back(0);
			med_linl.push_back(0);
			mean_linl_var.push_back(0);
			std::vector<ullint> nvec;
			locs.push_back(nvec);
			lins.push_back(nvec);
			locs[locs.size() - 1].push_back(loc);
			lins[lins.size() - 1].push_back(lin);
			std::vector<std::vector<ullint>> xvec;
			loc_in_lin.push_back(xvec);
			loc_in_lin[loc_in_lin.size() - 1].push_back(nvec);
			loc_in_lin[loc_in_lin.size() - 1][0].push_back(lloc);
		}
		else
		{
			sint xc = ReorderVs(ele);
		}
	}
	void DecrCts(_char* val = 0)
	{
		if (!val)
		{
			return;
		}

		for (uint ele = 0; ele < compv.size(); ele++)
		{
			if (!memcmp((void*)val, (void*)&compv[ele], sizeof(compv[ele])))
			{
				cts[ele]--;
				sint xc = ReorderVs(ele);
			}
		}
	}

	void AvgSyms()
	{
		for (uint x = 0; x < locs.size(); x++)
		{
			if (!locs[x].empty())
			{
				ullint lvg = locs[x][0];
				ullint rlen = 1;
				std::vector<ullint> av, rv;

				for (uint y = 1; y < locs[x].size(); y++)
				{
					lvg+=locs[x][y];

					if (locs[x][y - 1] + 1 == locs[x][y])
					{
						rlen++;
					}
					else
					{
						ullint slen = locs[x][y] - (locs[x][y - 1] + 1);
						uint z = 0;

						while (z < av.size())
						{
							if (slen >= av[z])
							{
								ullint ph = av[z];
								av[z] = slen;

								for (uint xz = z + 1; xz < av.size(); xz++)
								{
									slen = av[xz];
									av[xz] = ph;
									ph = slen;
								}

								av.push_back(ph);
								z = av.size();
							}
							z++;
						}
						if (z == av.size())
						{
							av.push_back(slen);
						}

						z = 0;

						while (z < rv.size())
						{
							if (rlen >= rv[z])
							{
								ullint ph = rv[z];
								rv[z] = rlen;

								for (uint xz = z + 1; xz < rv.size(); xz++)
								{
									rlen = rv[xz];
									rv[xz] = ph;
									ph = rlen;
								}

								rv.push_back(ph);
								z = rv.size();
							}
							z++;
						}
						if (z == rv.size())
						{
							rv.push_back(rlen);
						}
						rlen = 1;
					}
				}

				mean_loc[x] = (ullint)((float)lvg / (float)locs[x].size());
				ullint med_v = 0;
				ullint av_i = 0;
				ullint av_v = 0;

				if (!av.empty())
				{
					for (uint y = 0; y < av.size(); y++)
					{
						av_i += av[y];

						if (y)
						{
							av_v += (ullint)(abs(((sllint)av[y] - (sllint)av[y - 1])));
						}

						if (!med_v)
						{
							if (av.size() > 2)
							{
								if ((y + y) + 1 >= av.size())
								{
									med_v = av[y];
								}
							}
							else
							{
								if (av.size() == 2)
								{
									med_v = (ullint)((float)(av[0] + av[1]) / 2.0f);
								}
								else
								{
									med_v = av[0];
								}
							}
						}
					}
					if (av_i && med_v)
					{
						mean_spc[x] = (ullint)((float)av_i / (float)av.size());
						med_spc[x] = med_v;
						mean_spc_var[x] = (ullint)((float)av_v / (float)av.size());
					}
				}

				med_v = 0;
				av_i = 0;
				av_v = 0;

				if (!rv.empty())
				{
					for (uint y = 0; y < rv.size(); y++)
					{
						av_i += rv[y];

						if (y)
						{
							av_v += (ullint)(abs(((sllint)rv[y] - (sllint)rv[y - 1])));
						}

						if (!med_v)
						{
							if (rv.size() > 2)
							{
								if ((y + y) + 1 >= rv.size())
								{
									med_v = rv[y];
								}
							}
							else
							{
								if (rv.size() == 2)
								{
									med_v = (ullint)((float)(rv[0] + rv[1]) / 2.0f);
								}
								else
								{
									med_v = rv[0];
								}
							}
						}
					}
					if (av_i && med_v)
					{
						mean_lens[x] = (ullint)((float)av_i / (float)rv.size());
						med_lens[x] = med_v;
						mean_lens_var[x] = (ullint)((float)av_v / (float)rv.size());
					}
					else
					{
						if (!av_i)
						{
							mean_lens[x] = 1;
						}
						else
						{
							mean_lens[x] = av_i;
						}
						if (!med_v)
						{
							med_lens[x] = 1;
						}
						else
						{
							med_lens[x] = med_v;
						}
					}
				}
			}
		}

		locs.clear();

		for (uint x = 0; x < loc_in_lin.size(); x++)
		{
			if (!loc_in_lin[x].empty())
			{
				std::vector<ullint> nct;
				std::vector<ullint> nloc;

				for (uint y = 0; y < loc_in_lin[x].size(); y++)
				{
					uint z = 0;

					while (z < nct.size())
					{
						if (loc_in_lin[x][y].size() >= nct[z])
						{
							ullint ph = nct[z];
							ullint xh = 0;
							nct[z] = loc_in_lin[x][y].size();

							for (uint xz = z + 1; xz < nct.size(); xz++)
							{
								xh = nct[xz];
								nct[xz] = ph;
								ph = xh;
							}

							nct.push_back(ph);
							z = nct.size();
						}
						z++;
					}
					if (z == nct.size())
					{
						nct.push_back(loc_in_lin[x][y].size());
					}

					ullint aloc = 0;

					for (z = 0; z < loc_in_lin[x][y].size(); z++)
					{
						aloc += loc_in_lin[x][y][z];
					}

					aloc = (ullint)((float)aloc / (float)loc_in_lin[x][y].size());
					z = 0;

					while (z < nloc.size())
					{
						if (aloc >= nloc[z])
						{
							ullint ph = nloc[z];
							nloc[z] = aloc;

							for (uint xz = z + 1; xz < nloc.size(); xz++)
							{
								aloc = nloc[xz];
								nloc[xz] = ph;
								ph = aloc;
							}

							nloc.push_back(ph);
							z = nloc.size();
						}
						z++;
					}
					if (z == nloc.size())
					{
						nloc.push_back(aloc);
					}
				}

				ullint med_v = 0;
				ullint av_i = 0;
				ullint av_v = 0;

				if (!nct.empty())
				{
					bool all_same = true;

					for (uint y = 0; y < nct.size(); y++)
					{
						av_i += nct[y];

						if (y)
						{
							if (all_same)
							{
								if (nct[y] != nct[y - 1])
								{
									all_same = false;
								}
							}
							av_v += (ullint)(abs((sllint)nct[y] - (sllint)nct[y-1]));
						}
						if (!med_v)
						{
							if (nct.size() > 2)
							{
								if ((y + y) + 1 >= nct.size())
								{
									med_v = nct[y];
								}
							}
							else
							{
								if (nct.size() == 2)
								{
									med_v = (ullint)((float)(nct[0] + nct[1]) / 2.0f);
								}
								else
								{
									med_v = nct[0];
								}
							}
						}
					}

					if (av_i)
					{
						mean_linct[x] = (ullint)((float)av_i / (float)nct.size());
					}
					
					med_linct[x] = med_v;

					if(av_v)
					{
						mean_linct_var[x] = (ullint)((float)av_v / (float)nct.size());
					}
				}

				med_v = 0;
				av_i = 0;
				av_v = 0;

				if (!nloc.empty())
				{
					bool all_same = true;

					for (uint y = 0; y < nloc.size(); y++)
					{
						av_i += nloc[y];

						if (y)
						{
							if (all_same)
							{
								if (nloc[y] != nloc[y - 1])
								{
									all_same = false;
								}
							}
							av_v += (ullint)(abs((sllint)nloc[y] - (sllint)nloc[y - 1]));
						}
						if (!med_v)
						{
							if (nloc.size() > 2)
							{
								if ((y + y) + 1 >= nloc.size())
								{
									med_v = nloc[y];
								}
							}
							else
							{
								if (nloc.size() == 2)
								{
									med_v = (ullint)((float)(nloc[0] + nloc[1]) / 2.0f);
								}
								else
								{
									med_v = nloc[0];
								}
							}
						}
					}

					if (av_i)
					{
						mean_linct[x] = (ullint)((float)av_i / (float)nloc.size());
					}

					med_linct[x] = med_v;

					if (av_v)
					{
						mean_linct_var[x] = (ullint)((float)av_v / (float)nloc.size());
					}
				}
			}
		}
		
		lins.clear();
		loc_in_lin.clear();
	}

	bot_fstate(size_t ne_loc = 0, size_t noa_loc = 0, size_t nia_loc = 0)
	{
		Clear();

		e_loc = ne_loc;
		oa_loc = noa_loc;
		ia_loc = nia_loc;
	}

private:

};

enum file_mems
{
	BOT_FS_NAME = 0,
	BOT_FS_FT = 1,
	BOT_FS_FP = 2,
	BOT_FS_OMODE = 3,
	BOT_FS_ENC = 4,
	BOT_FS_STATE = 5,
	BOT_FS_LID = 6,
	BOT_FS_CBY = 7,
	BOT_FS_CM = 8,
	BOT_FS_FCON = 9,
	BOT_FS_FPAD = 10,
	BOT_FS_BTO = 11,
	BOT_FS_DSIZ = 12,
	BOT_FS_DAT = 13,
	BOT_FS_DATP = 14,
	BOT_FS_CRS = 15,
	BOT_FS_CRSV = 16,
	BOT_FS_SELV = 17,
	BOT_FS_MAX = 18
};

enum file_funs
{
	BOT_FFS_CLR = 0,
	BOT_FFS_REN = 1,
	BOT_FFS_SCS = 2,
	BOT_FFS_GCS = 3,
	BOT_FFS_RCS = 4,
	BOT_FFS_
};

class BOT_FILE
{
public:
	std::string name;
	std::string path;
	std::string type;
	sint encode;
	sint omode;
	sint fcon;
	sint fpad;
	std::vector<std::vector<BOT_CRS>> crsv;
	std::vector<std::vector<BOT_CRS>> selv;
	bot_fstate fst;
	sint lid;
	sint c_by;
	sint cm;
	sllint bto;
	size_t dsiz;
	_char* dat;

	void Clear() { fst.Clear(); ClearDat(); bto = -1; encode = cm = lid = c_by = omode = fcon = fpad = -1; if (!crsv.empty()) { crsv.clear(); } if (!selv.empty()) { selv.clear(); } if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } }
	void Renew(BOT_FILE* nf_ = 0)
	{
		if (nf_)
		{
			Clear();
			size_t nlen = (size_t)nf_->name.length();
			size_t tlen = (size_t)nf_->type.length();
			size_t plen = (size_t)nf_->path.length();

			if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
			{
				_char dmk = '\\';

				if (tlen)
				{
					_char term = '.';

					if (!memcmp((void*)&nf_->type[0], (void*)&term, sizeof(_char)))
					{
						for (uint x = 1; x < tlen; x++)
						{
							type.push_back(nf_->type[x]);
						}
						tlen--;
					}
					else
					{
						type.append(nf_->type.c_str());
					}
				}
				else
				{
					if (nlen)
					{
						_char term = '.';
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->name[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < nlen; x++)
								{
									type.push_back(nf_->name[x]);
									tlen++;
								}

								nlen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nf_->name[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
					if (!tlen && plen)
					{
						_char term = '.';
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->path[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < plen; x++)
								{
									type.push_back(nf_->path[x]);
									tlen++;
								}

								plen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nf_->path[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (plen)
				{
					if (!nlen)
					{
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->path[x], (void*)&dmk, sizeof(_char)))
							{
								size_t xlen = plen;
								plen = x;

								for (x++; x < xlen; x++)
								{
									name.push_back(nf_->path[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}
								for (x = 0; x < plen; x++)
								{
									path.push_back(nf_->path[x]);
								}
								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}

					}
					else
					{
						path.append(nf_->path);

						if (!path.empty())
						{
							if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
							{
								path.pop_back();
							}
						}
					}
				}
				else
				{
					if (nlen)
					{
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->name[x], (void*)&dmk, sizeof(_char)))
							{
								plen = x;

								for (x++; x < nlen; x++)
								{
									name.push_back(nf_->name[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}

								nlen = 0;

								for (x = 0; x < plen; x++)
								{
									path.push_back(nf_->name[x]);
								}

								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (nlen)
				{
					for (size_t x = 0; x < nlen; x++)
					{
						name.push_back(nf_->name[x]);
					}

					if (!name.empty())
					{
						if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							name.pop_back();
						}
					}
				}

				if (!name.empty() || !path.empty())
				{
					encode = nf_->encode;
					fcon = nf_->fcon;
					fpad = nf_->fpad;
					bto = nf_->bto;
					omode = nf_->omode;
					c_by = nf_->c_by;
					lid = nf_->lid;
					cm = nf_->cm;
					fst.Renew(&nf_->fst);

					for (uint x = 0; x < nf_->crsv.size(); x++)
					{
						if (!nf_->crsv[x].empty())
						{
							std::vector<BOT_CRS> nv;
							crsv.push_back(nv);

							for (uint y = 0; y < nf_->crsv[x].size(); y++)
							{
								crsv[x].push_back(nf_->crsv[x][y]);
							}
						}
					}
					for (uint x = 0; x < nf_->selv.size(); x++)
					{
						if (!nf_->selv[x].empty())
						{
							std::vector<BOT_CRS> nv;
							selv.push_back(nv);

							for (uint y = 0; y < nf_->selv[x].size(); y++)
							{
								selv[x].push_back(nf_->selv[x][y]);
							}
						}
					}
					SetDat(nf_->dat, nf_->dsiz);
				}
			}
		}
	}
	void Renew(c_char* nfn = 0, c_char* nft = 0, c_char* nfp = 0, sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sint nencode = -1, sllint nbto = -1, std::vector<std::vector<BOT_CRS>>* ncrsv = 0, std::vector<std::vector<BOT_CRS>>* nselv = 0, bot_fstate* nstate = 0, _char* ndat = 0, size_t ndsiz = 0)
	{
		if (!nfn || !nft || !nfp)
		{
			return;
		}

		Clear();
		size_t nlen = bot_cstrlen(nfn);
		size_t tlen = bot_cstrlen(nft);
		size_t plen = bot_cstrlen(nfp);

		if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
		{
			_char dmk = '\\';

			if (tlen)
			{
				_char term = '.';

				if (!memcmp((void*)&nft[0], (void*)&term, sizeof(_char)))
				{
					for (uint x = 1; x < tlen; x++)
					{
						type.push_back(nft[x]);
					}
					tlen--;
				}
				else
				{
					type.append(nft);
				}
			}
			else
			{
				if (nlen)
				{
					_char term = '.';
					size_t x = nlen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfn[x], (void*)&term, sizeof(_char)))
						{
							size_t xlen = x;

							for (x++; x < nlen; x++)
							{
								type.push_back(nfn[x]);
								tlen++;
							}

							nlen = xlen;
							x = 0;
						}
						else if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
						{
							x = 0;
						}
						else { x--; }
					}
				}
				if (!tlen && plen)
				{
					_char term = '.';
					size_t x = plen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfp[x], (void*)&term, sizeof(_char)))
						{
							size_t xlen = x;

							for (x++; x < plen; x++)
							{
								type.push_back(nfp[x]);
								tlen++;
							}

							plen = xlen;
							x = 0;
						}
						else if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
						{
							x = 0;
						}
						else { x--; }
					}
				}
			}

			if (plen)
			{
				if (!nlen)
				{
					size_t x = plen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
						{
							size_t xlen = plen;
							plen = x;

							for (x++; x < xlen; x++)
							{
								name.push_back(nfp[x]);
							}
							if (!name.empty())
							{
								if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									name.pop_back();
								}
							}
							for (x = 0; x < plen; x++)
							{
								path.push_back(nfp[x]);
							}
							if (!path.empty())
							{
								if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									path.pop_back();
								}
							}
							x = 0;
						}
						else { x--; }
					}

				}
				else
				{
					path.append(nfp);

					if (!path.empty())
					{
						if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							path.pop_back();
						}
					}
				}
			}
			else
			{
				if (nlen)
				{
					size_t x = nlen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
						{
							plen = x;

							for (x++; x < nlen; x++)
							{
								name.push_back(nfn[x]);
							}
							if (!name.empty())
							{
								if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									name.pop_back();
								}
							}

							nlen = 0;

							for (x = 0; x < plen; x++)
							{
								path.push_back(nfn[x]);
							}

							if (!path.empty())
							{
								if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									path.pop_back();
								}
							}
							x = 0;
						}
						else { x--; }
					}
				}
			}

			if (nlen)
			{
				for (size_t x = 0; x < nlen; x++)
				{
					name.push_back(nfn[x]);
				}

				if (!name.empty())
				{
					if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
					{
						name.pop_back();
					}
				}
			}

			if (!name.empty() || !path.empty())
			{
				if (ncrsv)
				{
					for (size_t x = 0; x < ncrsv->size(); x++)
					{
						if (!ncrsv->at(x).empty())
						{
							std::vector<BOT_CRS> nv;
							crsv.push_back(nv);

							for (size_t y = 0; y < ncrsv->at(x).size(); y++)
							{
								crsv[x].push_back(ncrsv->at(x)[y]);
							}
						}
					}
				}

				if (nselv)
				{
					for (size_t x = 0; x < nselv->size(); x++)
					{
						if (!nselv->at(x).empty())
						{
							std::vector<BOT_CRS> nv;
							selv.push_back(nv);

							for (size_t y = 0; y < nselv->at(x).size(); y++)
							{
								selv[x].push_back(nselv->at(x)[y]);
							}
						}
					}
				}

				encode = nencode;
				bto = nbto;
				lid = nlid;
				cm = ncm;
				omode = nomode;
				c_by = nc_by;

				if (nstate)
				{
					fst.Renew(nstate);
				}
				SetDat(ndat, ndsiz);
			}
		}
	}
	sint SetCrs(BOT_CRS* ncrs = 0)
	{
		if (!ncrs)
		{
			return -1;
		}
		if (ncrs->t < ncrs->f)
		{
			ncrs->t = ncrs->f;
		}

		if (ncrs->t - ncrs->f < (ullint)BOT_FILESIZE_MAX)
		{
			if (crsv.empty())
			{
				std::vector<BOT_CRS> nv;
				crsv.push_back(nv);
				crsv[0].push_back(*ncrs);
			}
			else if (crsv.size() < (size_t)BOT_CRSV_MAX)
			{
				size_t x = 0;

				while (x < crsv.size())
				{
					if (!crsv[x].empty())
					{
						if (crsv[x][0].fid == ncrs->fid && crsv[x][0].lid == ncrs->lid)
						{
							size_t y = crsv[x].size() - 1;

							if (crsv[x][y].f != ncrs->f || crsv[x][y].t != ncrs->t)
							{
								crsv[x].push_back(*ncrs);
								return (sint)x;
							}
						}
					}
					x++;
				}

				if (x == crsv.size())
				{
					std::vector<BOT_CRS> nv;
					crsv.push_back(nv);
					crsv[x].push_back(*ncrs);
				}
			}
			else {}
		}
		return (sint)crsv.size();
	}
	sint GetCrs(BOT_CRS* ncrs = 0)
	{
		if (!ncrs)
		{
			return -1;
		}

		for (size_t x = 0; x < crsv.size(); x++)
		{
			if (!crsv[x].empty())
			{
				if (crsv[x][0].fid == ncrs->fid && crsv[x][0].lid == ncrs->lid)
				{
					*ncrs = crsv[x][crsv[x].size() - 1];
					return (sint)x;
				}
			}
		}
		return -1;
	}
	sint RemCrs(BOT_CRS* ncrs = 0)
	{
		if (!ncrs)
		{
			return -1;
		}

		sint ret = -1;

		for (slint x = 0; x < (slint)crsv.size(); x++)
		{
			if (!crsv[x].empty())
			{
				if (crsv[x][0].fid == ncrs->fid && crsv[x][0].lid == ncrs->lid)
				{
					for (slint y = (slint)crsv[x].size() - 1; y > -1; y--)
					{
						if (crsv[x][y].fid == ncrs->fid && crsv[x][y].lid == ncrs->lid && crsv[x][y].f == ncrs->f && crsv[x][y].t == ncrs->t)
						{
							for (slint z = y + 1; z < (slint)crsv[x].size(); z++)
							{
								crsv[x][z - 1] = crsv[x][z];
							}
							crsv[x].pop_back();
							ret++;
							y = -1;
						}
					}
				}
			}
		}
		return ret;
	}
	sint RemFCrs(sllint fid = -1, sint nlid = -1)
	{
		sint ret = -1;

		if (!crsv.empty())
		{
			for (size_t x = crsv.size() - 1; x; x--)
			{
				if (!crsv[x].empty())
				{
					if (crsv[x][0].fid == fid && crsv[x][0].lid == lid)
					{
						crsv[x].clear();
						ret++;
					}
				}
			}

			for (slint x = (slint)crsv.size() - 1; x > -1; x--)
			{
				if (crsv[x].empty())
				{
					crsv.pop_back();
				}
				else
				{
					x = -1;
				}
			}
		}
		return ret;
	}
	ullint AddSel(BOT_CRS* nsel = 0)
	{
		if (nsel->t < nsel->f)
		{
			nsel->t = nsel->f;
		}

		if (nsel->t - nsel->f < (ullint)BOT_FILESIZE_MAX)
		{
			if (selv.size() < (size_t)BOT_CRSV_MAX)
			{
				
			}
		}
	}
	size_t Alloc(size_t siz = 0)
	{
		if (!siz)
		{
			ClearDat();
			return 0;
		}

		if (siz < (size_t)BOT_FILESIZE_MAX)
		{
			if (dat)
			{
				_char* ndat = 0;
				ndat = (_char*)realloc(dat, siz);

				if (ndat)
				{
					dat = ndat;
				}
			}
			else
			{
				dat = (_char*)malloc(siz);
			}

			if (dat)
			{
				dsiz = siz;
				_char term = '\0';
				memcpy((void*)&dat[dsiz - 1], (void*)&term, sizeof(_char));
				return dsiz;
			}
		}
		return 0;
	}
	void SetDat(_char* val_ = 0, size_t siz = 0)
	{
		if (!val_)
		{
			return;
		}

		if (!siz)
		{
			siz = bot_strlen(val_);
		}

		if (!siz)
		{
			ClearDat();
		}

		if (dsiz != siz)
		{
			if (!Alloc(siz))
			{
				return;
			}
		}

		if (dat)
		{
			_char term = '\0';

			for (size_t x = 0; x < siz; x++)
			{
				memcpy((void*)&dat[x], (void*)&val_[x], sizeof(_char));
			}
			memcpy((void*)&dat[siz], (void*)&term, sizeof(_char));
		}
	}
	size_t AddDat(_char* val_ = 0, size_t f = 0)
	{
		if (!val_)
		{
			return 0;
		}

		size_t ret = 0;
		size_t len = bot_strlen(val_);
		_char term = '\0';

		if (omode == BOT_FILE_OVRL)
		{
			if (f + len > dsiz)
			{
				_char* tmp = (_char*)malloc(((f + len) - dsiz) + 1);

				if (tmp)
				{
					memcpy((void*)tmp, (void*)&dat[f], (f + len) - dsiz);
					memcpy((void*)&tmp[len], (void*)&term, sizeof(_char));
					size_t osiz = dsiz;

					if (Alloc(f + len))
					{
						memcpy((void*)&dat[f], (void*)val_, len);
						memcpy((void*)&dat[f + len], (void*)tmp, (f + len) - osiz);
						memcpy((void*)&dat[dsiz - 1], (void*)&term, sizeof(_char));
						ret = f + len;
					}
					free(tmp);
				}
			}
			else
			{
				memcpy((void*)&dat[f], (void*)val_, len);
				memcpy((void*)&dat[dsiz - 1], (void*)&term, sizeof(_char));
			}
		}
		else if (omode == BOT_FILE_APND || omode == BOT_FILE_INS)
		{
			if (dsiz - f > 1024)
			{
				_char* tmp = (_char*)malloc(len + 1);

				if (tmp)
				{
					memcpy((void*)&tmp[len], (void*)&term, sizeof(_char));
					size_t osiz = dsiz;

					if (Alloc(osiz + len))
					{
						size_t x = f;

						while (x < osiz)
						{
							memcpy((void*)tmp, (void*)&dat[x], len);
							memcpy((void*)&dat[x], (void*)val_, len);
							memcpy((void*)val_, (void*)tmp, len);
							x += len;
						}

						if (x != osiz)
						{
							memcpy((void*)&dat[x], (void*)tmp, x - osiz);
						}
						memcpy((void*)&dat[dsiz - 1], (void*)&term, sizeof(_char));
						ret = f + len;
					}
					free(tmp);
				}
			}
			else
			{
				_char* tmp = (_char*)malloc((dsiz - f) + 1);

				if (tmp)
				{
					memcpy((void*)tmp, (void*)&dat[f], dsiz - f);
					memcpy((void*)tmp[dsiz - f], (void*)&term, sizeof(_char));
					size_t osiz = dsiz;

					if (Alloc(osiz + len))
					{
						memcpy((void*)&dat[f], (void*)val_, len);
						memcpy((void*)&dat[f + len], (void*)tmp, osiz - f);
						memcpy((void*)&dat[dsiz - 1], (void*)&term, sizeof(_char));
						ret = f + len;
					}
					free(tmp);
				}
			}
		}
		else {}
		return ret;
	}
	void ClearDat()
	{
		if (dat && dsiz)
		{
			size_t nsiz = dsiz - 1;

			while (nsiz)
			{
				dat[nsiz] = 0;
				nsiz--;
			}
			
			if (dsiz > 1)
			{
				_char* ndat = 0;
				ndat = (_char*)realloc(dat, 1);

				if (ndat)
				{
					dat = ndat;
					dat[0] = 1;
					dsiz = 1;
				}
				else
				{
					dsiz = 0;
				}
			}
		}
	}
	void FreeDat()
	{
		if (dat)
		{
			if (dsiz)
			{
				ClearDat();
			}
			free(dat);
			dsiz = 0;
		}
	}
	BOT_FILE(c_char* nfn = "", c_char* nft = "", c_char* nfp = "", sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sllint nbto = -1, sint nencode = -1, std::vector<std::vector<BOT_CRS>>* ncrsv = 0, std::vector<std::vector<BOT_CRS>>* nselv = 0, bot_fstate* nfst = 0, size_t ndsiz = 0)
	{
		if (nfn && nft && nfp)
		{
			size_t nlen = bot_cstrlen(nfn);
			size_t tlen = bot_cstrlen(nft);
			size_t plen = bot_cstrlen(nfp);

			if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
			{
				_char dmk = '\\';
				
				if (tlen)
				{
					_char term = '.';

					if (!memcmp((void*)&nft[0], (void*)&term, sizeof(_char)))
					{
						for (uint x = 1; x < tlen; x++)
						{
							type.push_back(nft[x]);
						}
						tlen--;
					}
					else
					{
						type.append(nft);
					}
				}
				else
				{
					if (nlen)
					{
						_char term = '.';
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfn[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < nlen; x++)
								{
									type.push_back(nfn[x]);
									tlen++;
								}

								nlen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
					if (!tlen && plen)
					{
						_char term = '.';
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfp[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < plen; x++)
								{
									type.push_back(nfp[x]);
									tlen++;
								}

								plen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (plen)
				{
					if (!nlen)
					{
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
							{
								size_t xlen = plen;
								plen = x;

								for (x++; x < xlen; x++)
								{
									name.push_back(nfp[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}
								for (x = 0; x < plen; x++)
								{
									path.push_back(nfp[x]);
								}
								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}

					}
					else
					{
						path.append(nfp);

						if (!path.empty())
						{
							if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
							{
								path.pop_back();
							}
						}
					}
				}
				else
				{
					if (nlen)
					{
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
							{
								plen = x;

								for (x++; x < nlen; x++)
								{
									name.push_back(nfn[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}

								nlen = 0;

								for (x = 0; x < plen; x++)
								{
									path.push_back(nfn[x]);
								}

								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (nlen)
				{
					for (size_t x = 0; x < nlen; x++)
					{
						name.push_back(nfn[x]);
					}

					if (!name.empty())
					{
						if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							name.pop_back();
						}
					}
				}

				if (!name.empty() || !path.empty())
				{
					if (ncrsv)
					{
						for (uint x = 0; x < ncrsv->size(); x++)
						{
							if (!ncrsv->at(x).empty())
							{
								std::vector<BOT_CRS> nv;
								crsv.push_back(nv);

								for (uint y = 0; y < ncrsv->at(x).size(); y++)
								{
									crsv[x].push_back(ncrsv->at(x)[y]);
								}
							}
						}
					}

					if (nselv)
					{
						for (uint x = 0; x < nselv->size(); x++)
						{
							if (!nselv->at(x).empty())
							{
								std::vector<BOT_CRS> nv;
								selv.push_back(nv);

								for (uint y = 0; y < nselv->at(x).size(); y++)
								{
									selv[x].push_back(nselv->at(x)[y]);
								}
							}
						}
					}

					encode = nencode;
					bto = nbto;
					cm = ncm;
					omode = nomode;
					lid = nlid;
					fcon = -1;
					fpad = -1;
					c_by = nc_by;
					dsiz = ndsiz;
					dat = 0;

					if (!nfst)
					{
						fst.Renew(nfst);
					}
				}
			}
		}
	}
	
	/*~BOT_FILE()
	{
		Clear();

		if (dsiz)
		{
			FreeDat();
		}
	}*/
	
private:
};

class BOT_FILE_M
{
public:

	std::string name;
	std::string path;
	std::string type;
	sint encode;
	sint omode;
	sint fcon;
	sint fpad;
	std::vector<BOT_CRS> crsv;
	size_t crss;
	size_t sels;
	bot_fstate fst;
	sint lid;
	sint c_by;
	sint cm;
	_char* datp;
	sllint bto;
	size_t dsiz;

	void Clear() { crss = sels = 0; crsv.clear(); datp = 0; dsiz = 0; fst.ClearStats(); bto = -1; encode = cm = lid = c_by = omode = fcon = fpad = -1; if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } }
	void Renew(BOT_FILE_M* nf_ = 0)
	{
		if (nf_)
		{
			Clear();
			size_t nlen = (size_t)nf_->name.length();
			size_t tlen = (size_t)nf_->type.length();
			size_t plen = (size_t)nf_->path.length();

			if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
			{
				_char dmk = '\\';
				
				if (tlen)
				{
					_char term = '.';

					if (!memcmp((void*)&nf_->type[0], (void*)&term, sizeof(_char)))
					{
						for (uint x = 1; x < tlen; x++)
						{
							type.push_back(nf_->type[x]);
						}
						tlen--;
					}
					else
					{
						type.append(nf_->type.c_str());
					}
				}
				else
				{
					if (nlen)
					{
						_char term = '.';
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->name[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < nlen; x++)
								{
									type.push_back(nf_->name[x]);
									tlen++;
								}

								nlen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nf_->name[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
					if (!tlen && plen)
					{
						_char term = '.';
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->path[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < plen; x++)
								{
									type.push_back(nf_->path[x]);
									tlen++;
								}

								plen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nf_->path[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (plen)
				{
					if (!nlen)
					{
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->path[x], (void*)&dmk, sizeof(_char)))
							{
								size_t xlen = plen;
								plen = x;

								for (x++; x < xlen; x++)
								{
									name.push_back(nf_->path[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}
								for (x = 0; x < plen; x++)
								{
									path.push_back(nf_->path[x]);
								}
								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}

					}
					else
					{
						path.append(nf_->path);

						if (!path.empty())
						{
							if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
							{
								path.pop_back();
							}
						}
					}
				}
				else
				{
					if (nlen)
					{
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->name[x], (void*)&dmk, sizeof(_char)))
							{
								plen = x;

								for (x++; x < nlen; x++)
								{
									name.push_back(nf_->name[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}

								nlen = 0;

								for (x = 0; x < plen; x++)
								{
									path.push_back(nf_->name[x]);
								}

								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (nlen)
				{
					for (size_t x = 0; x < nlen; x++)
					{
						name.push_back(nf_->name[x]);
					}

					if (!name.empty())
					{
						if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							name.pop_back();
						}
					}
				}

				if (!name.empty() || !path.empty())
				{
					encode = nf_->encode;
					bto = nf_->bto;
					fcon = nf_->fcon;
					fpad = nf_->fpad;

					if (!nf_->crsv.empty())
					{
						for (uint x = 0; x < nf_->crsv.size(); x++)
						{
							crsv.push_back(nf_->crsv[x]);
						}
					}

					crss = nf_->crss;
					sels = nf_->sels;
					datp = nf_->datp;
					dsiz = nf_->dsiz;
					omode = nf_->omode;
					c_by = nf_->c_by;
					lid = nf_->lid;
					cm = nf_->cm;
					fst.Renew(&nf_->fst);
				}
			}
		}
	}
	void Renew(BOT_FILE* nf_ = 0)
	{
		if (nf_)
		{
			Clear();
			size_t nlen = (size_t)nf_->name.length();
			size_t tlen = (size_t)nf_->type.length();
			size_t plen = (size_t)nf_->path.length();

			if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
			{
				_char dmk = '\\';
				
				if (tlen)
				{
					_char term = '.';

					if (!memcmp((void*)&nf_->type[0], (void*)&term, sizeof(_char)))
					{
						for (size_t x = 1; x < tlen; x++)
						{
							type.push_back(nf_->type[x]);
						}
						tlen--;
					}
					else
					{
						type.append(nf_->type.c_str());
					}
				}
				else
				{
					if (nlen)
					{
						_char term = '.';
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->name[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < nlen; x++)
								{
									type.push_back(nf_->name[x]);
									tlen++;
								}

								nlen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nf_->name[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
					if (!tlen && plen)
					{
						_char term = '.';
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->path[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < plen; x++)
								{
									type.push_back(nf_->path[x]);
									tlen++;
								}

								plen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nf_->path[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (plen)
				{
					if (!nlen)
					{
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->path[x], (void*)&dmk, sizeof(_char)))
							{
								size_t xlen = plen;
								plen = x;

								for (x++; x < xlen; x++)
								{
									name.push_back(nf_->path[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}
								for (x = 0; x < plen; x++)
								{
									path.push_back(nf_->path[x]);
								}
								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}

					}
					else
					{
						path.append(nf_->path);

						if (!path.empty())
						{
							if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
							{
								path.pop_back();
							}
						}
					}
				}
				else
				{
					if (nlen)
					{
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nf_->name[x], (void*)&dmk, sizeof(_char)))
							{
								plen = x;

								for (x++; x < nlen; x++)
								{
									name.push_back(nf_->name[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}

								nlen = 0;

								for (x = 0; x < plen; x++)
								{
									path.push_back(nf_->name[x]);
								}

								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (nlen)
				{
					for (size_t x = 0; x < nlen; x++)
					{
						name.push_back(nf_->name[x]);
					}

					if (!name.empty())
					{
						if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							name.pop_back();
						}
					}
				}

				if (!name.empty() || !path.empty())
				{
					encode = nf_->encode;
					crss = nf_->crsv.size();
					sels = nf_->selv.size();

					if (crss)
					{
						for (size_t x = 0; x < nf_->crsv.size(); x++)
						{
							if (!nf_->crsv[x].empty())
							{
								crsv.push_back(nf_->crsv[x][nf_->crsv[x].size() - 1]);
							}
						}
					}

					bto = nf_->bto;
					fcon = nf_->fcon;
					fpad = nf_->fpad;
					datp = &nf_->dat[0];
					dsiz = nf_->dsiz;
					omode = nf_->omode;
					c_by = nf_->c_by;
					lid = nf_->lid;
					cm = nf_->cm;
					fst.Renew(&nf_->fst);
				}
			}
		}
	}
	void Renew(c_char* nfn = "", c_char* nft = "", c_char* nfp = "", sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sllint nbto = -1, sint nencode = -1, size_t ncrss = 0, size_t nsels = 0, bot_fstate* nfst = 0, size_t ndsiz = 0, _char* ndatp = 0)
	{
		if (!nfn || !nft || !nfp)
		{
			return;
		}

		Clear();
		size_t nlen = bot_cstrlen(nfn);
		size_t tlen = bot_cstrlen(nft);
		size_t plen = bot_cstrlen(nfp);

		if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
		{
			_char dmk = '\\';
			
			if (tlen)
			{
				_char term = '.';

				if (!memcmp((void*)&nft[0], (void*)&term, sizeof(_char)))
				{
					for (uint x = 1; x < tlen; x++)
					{
						type.push_back(nft[x]);
					}
					tlen--;
				}
				else
				{
					type.append(nft);
				}
			}
			else
			{
				if (nlen)
				{
					_char term = '.';
					size_t x = nlen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfn[x], (void*)&term, sizeof(_char)))
						{
							size_t xlen = x;

							for (x++; x < nlen; x++)
							{
								type.push_back(nfn[x]);
								tlen++;
							}

							nlen = xlen;
							x = 0;
						}
						else if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
						{
							x = 0;
						}
						else { x--; }
					}
				}
				if (!tlen && plen)
				{
					_char term = '.';
					size_t x = plen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfp[x], (void*)&term, sizeof(_char)))
						{
							size_t xlen = x;

							for (x++; x < plen; x++)
							{
								type.push_back(nfp[x]);
								tlen++;
							}

							plen = xlen;
							x = 0;
						}
						else if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
						{
							x = 0;
						}
						else { x--; }
					}
				}
			}

			if (plen)
			{
				if (!nlen)
				{
					size_t x = plen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
						{
							size_t xlen = plen;
							plen = x;

							for (x++; x < xlen; x++)
							{
								name.push_back(nfp[x]);
							}
							if (!name.empty())
							{
								if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									name.pop_back();
								}
							}
							for (x = 0; x < plen; x++)
							{
								path.push_back(nfp[x]);
							}
							if (!path.empty())
							{
								if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									path.pop_back();
								}
							}
							x = 0;
						}
						else { x--; }
					}

				}
				else
				{
					path.append(nfp);

					if (!path.empty())
					{
						if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							path.pop_back();
						}
					}
				}
			}
			else
			{
				if (nlen)
				{
					size_t x = nlen - 1;

					while (x)
					{
						if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
						{
							plen = x;

							for (x++; x < nlen; x++)
							{
								name.push_back(nfn[x]);
							}
							if (!name.empty())
							{
								if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									name.pop_back();
								}
							}

							nlen = 0;

							for (x = 0; x < plen; x++)
							{
								path.push_back(nfn[x]);
							}

							if (!path.empty())
							{
								if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
								{
									path.pop_back();
								}
							}
							x = 0;
						}
						else { x--; }
					}
				}
			}

			if (nlen)
			{
				for (size_t x = 0; x < nlen; x++)
				{
					name.push_back(nfn[x]);
				}

				if (!name.empty())
				{
					if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
					{
						name.pop_back();
					}
				}
			}

			if (!name.empty() || !path.empty())
			{
				encode = nencode;
				bto = nbto;
				dsiz = ndsiz;

				if (ndatp)
				{
					datp = ndatp;
				}
				else
				{
					datp = 0;
				}

				crss = ncrss;
				sels = nsels;
				lid = nlid;
				cm = ncm;
				omode = nomode;
				c_by = nc_by;

				if (nfst)
				{
					fst.Renew(nfst);
				}
			}
		}
	}
	sint SetCrs(BOT_CRS* ncrs = 0)
	{
		if (!ncrs)
		{
			return -1;
		}

		if (ncrs->t < ncrs->f)
		{
			ncrs->t = ncrs->f;
		}

		sint ret = -1;

		if (ncrs->t - ncrs->f < (size_t)BOT_FILESIZE_MAX)
		{
			if (crsv.empty())
			{
				crsv.push_back(*ncrs);
			}
			else if (crsv.size() < (size_t)BOT_CRSV_MAX)
			{
				for (size_t x = 0; x < crsv.size(); x++)
				{
					if (crsv[x].fid == ncrs->fid && crsv[x].lid == ncrs->lid)
					{
						crsv[x] = *ncrs;
						return (sint)x;
					}
				}
				ret = (sint)crsv.size();
				crsv.push_back(*ncrs);
			}
			else {}
		}
		return ret;
	}
	sint GetCrs(BOT_CRS* ncrs = 0)
	{
		if (!ncrs)
		{
			return -1;
		}

		for (size_t x = 0; x < crsv.size(); x++)
		{
			if (crsv[x].fid == ncrs->fid && crsv[x].lid == ncrs->lid)
			{
				*ncrs = crsv[x];
				return (sint)x;
			}
		}
		return -1;
	}
	sint RemCrs(BOT_CRS* ncrs)
	{
		if (!ncrs)
		{
			return -1;
		}

		sint ret = -1;

		for (size_t x = 0; x < crsv.size(); x++)
		{
			if (crsv[x].fid == ncrs->fid && crsv[x].lid == ncrs->lid &&crsv[x].f == ncrs->f && crsv[x].t == ncrs->t)
			{
				for (size_t y = x + 1; y < crsv.size(); y++)
				{
					crsv[y - 1] = crsv[y];
				}
				crsv.pop_back();
				ret = 0;
				x = crsv.size();
			}
		}
		return ret;
	}
	sint RemFCrs(sllint fid)
	{
		sint ret = -1;

		for (size_t x = 0; x < crsv.size(); x++)
		{
			if (crsv[x].fid == fid && crsv[x].lid == lid)
			{
				for (size_t y = x + 1; y < crsv.size(); y++)
				{
					crsv[y - 1] = crsv[y];
				}
				crsv.pop_back();
				ret++;
			}
		}
		return ret;
	}
	BOT_FILE_M(c_char* nfn = "", c_char* nft = "", c_char* nfp = "", sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sllint nbto = -1, sint nencode = -1, size_t ncrss = 0, size_t nsels = 0, bot_fstate* nfst = 0, size_t ndsiz = 0, _char* ndatp = 0)
	{
		if (nfn && nft && nfp)
		{
			size_t nlen = bot_cstrlen(nfn);
			size_t tlen = bot_cstrlen(nft);
			size_t plen = bot_cstrlen(nfp);

			if (plen < (size_t)UINT32_MAX && tlen < 128 && nlen < (size_t)BOT_FILENAME_MAX)
			{
				_char dmk = '\\';
				
				if (tlen)
				{
					_char term = '.';

					if (!memcmp((void*)&nft[0], (void*)&term, sizeof(_char)))
					{
						for (size_t x = 1; x < tlen; x++)
						{
							type.push_back(nft[x]);
						}
						tlen--;
					}
					else
					{
						type.append(nft);
					}
				}
				else
				{
					if (nlen)
					{
						_char term = '.';
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfn[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < nlen; x++)
								{
									type.push_back(nfn[x]);
									tlen++;
								}

								nlen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
					if (!tlen && plen)
					{
						_char term = '.';
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfp[x], (void*)&term, sizeof(_char)))
							{
								size_t xlen = x;

								for (x++; x < plen; x++)
								{
									type.push_back(nfp[x]);
									tlen++;
								}

								plen = xlen;
								x = 0;
							}
							else if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
							{
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (plen)
				{
					if (!nlen)
					{
						size_t x = plen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfp[x], (void*)&dmk, sizeof(_char)))
							{
								size_t xlen = plen;
								plen = x;

								for (x++; x < xlen; x++)
								{
									name.push_back(nfp[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}
								for (x = 0; x < plen; x++)
								{
									path.push_back(nfp[x]);
								}
								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--;	}
						}

					}
					else
					{
						path.append(nfp);

						if (!path.empty())
						{
							if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
							{
								path.pop_back();
							}
						}
					}
				}
				else
				{
					if (nlen)
					{
						size_t x = nlen - 1;

						while (x)
						{
							if (!memcmp((void*)&nfn[x], (void*)&dmk, sizeof(_char)))
							{
								plen = x;
								
								for (x++; x < nlen; x++)
								{
									name.push_back(nfn[x]);
								}
								if (!name.empty())
								{
									if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										name.pop_back();
									}
								}

								nlen = 0;

								for (x = 0; x < plen; x++)
								{
									path.push_back(nfn[x]);
								}

								if (!path.empty())
								{
									if (!memcmp((void*)&path[path.length() - 1], (void*)&dmk, sizeof(_char)))
									{
										path.pop_back();
									}
								}
								x = 0;
							}
							else { x--; }
						}
					}
				}

				if (nlen)
				{
					for (size_t x = 0; x < nlen; x++)
					{
						name.push_back(nfn[x]);
					}

					if (!name.empty())
					{
						if (!memcmp((void*)&name[name.length() - 1], (void*)&dmk, sizeof(_char)))
						{
							name.pop_back();
						}
					}
				}

				if (!name.empty() || !path.empty())
				{

					if (ndatp)
					{
						datp = ndatp;
					}
					else
					{
						datp = 0;
					}

					crss = ncrss;
					sels = nsels;
					encode = nencode;
					bto = nbto;
					omode = nomode;
					cm = ncm;
					lid = nlid;
					fcon = -1;
					fpad = -1;
					c_by = nc_by;
					dsiz = ndsiz;

					if (nfst)
					{
						fst.Renew(nfst);
					}
				}
			}
		}
	}

private:
};

class BOTF_CONN
{
public:

	_mtx mtx;
	bool in_use;
	sint lid;
	sint omode;
	sint flid;
	sint encode;
	std::fstream fstrm;

	void Clear() { in_use = false; encode = flid = omode = lid = -1; if (fstrm.is_open()) { fstrm.close(); } }
	void Renew(BOTF_CONN* val_ = 0)
	{
		Clear();

		if (val_)
		{
			flid = val_->flid;
			omode = val_->omode;
			lid = val_->lid;
			in_use = val_->in_use;
			encode = val_->encode;
		}
	}
	void Renew(BOT_FILE* val_ = 0, sint nid = -1)
	{
		Clear();
		
		if (val_)
		{
			flid = val_->lid;
			omode = val_->omode;
			lid = nid;
			encode = val_->encode;
			in_use = true;
		}
	}
	void Renew(BOT_FILE_M* val_ = 0, sint nid = -1)
	{
		Clear();

		if (val_)
		{
			flid = val_->lid;
			omode = val_->omode;
			lid = nid;
			encode = val_->encode;
			in_use = true;
		}
	}
	
	BOTF_CONN() { in_use = false; flid = encode = omode = lid = -1; }

private:
};

enum tts_sigs
{
	BOT_TSG_RSRT = 1,
	BOT_TSG_CLS = 2,
	BOT_TSG_CLRV = 3,
	BOT_TSG_PAWS = 4,
	BOT_TSG_CONT = 999,
	BOT_TSG_MAX = 1000
};

enum tts_states
{
	BOT_THR_BEG = 1,
	BOT_THR_PCL = 2,
	BOT_THR_RJC = 3,
	BOT_THR_RUN = 4,
	BOT_THR_FIN = 5,
	BOT_THR_RCL = 6,
	BOT_THR_DED = 10,
	BOT_THR_MAX = 11
};

enum tts_mems
{
	BOT_TTS_LQ = 0,
	BOT_TTS_LID = 1,
	BOT_TTS_TNAME = 2,
	BOT_TTS_THREAD = 3,
	BOT_TTS_ATTR = 4,
	BOT_TTS_OPT = 5,
	BOT_TTS_FIN = 6,
	BOT_TTS_FUNC = 7,
	BOT_TTS_TIMEP = 8,
	BOT_TTS_CBY = 9,
	BOT_TTS_MINR = 10,
	BOT_TTS_VALS = 11,
	BOT_TTS_SIG = 12,
	BOT_TTS_TID = 13,
	BOT_TTS_MAX = 14
};

class TINFO
{
public:

	sint lid;
	sint opt;
	sint fin;
	slint tid;
	sint c_by;
	pthread_t thread;
	pthread_attr_t attr;
	void *(*func)(void *);
	std::chrono::steady_clock::time_point t_I;
	float min_ratv;
	std::string thread_name;
	std::vector<ullint> vals;
	sint sig;

	void Clear() { sig = 0; min_ratv = 0.0f; t_I = std::chrono::steady_clock::now(); opt = lid = c_by = -1; tid = -1; fin = BOT_THR_BEG; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; vals.clear(); }
	void Renew(TINFO* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		lid = val_->lid;
		tid = val_->tid;
		opt = val_->opt;
		fin = val_->fin;
		c_by = val_->c_by;
		thread = val_->thread;
		attr = val_->attr;
		func = val_->func;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(val_->thread_name.c_str());
		sig = val_->sig;

		if (val_->vals.size() < BOTVEC_LIM)
		{
			for (uint x = 0; x < val_->vals.size(); x++)
			{
				vals.push_back(val_->vals[x]);
			}
		}
	}
	TINFO(sint nopt = -1, c_char* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f, std::vector<ullint>* nvec = 0)
	{
		lid = -1;
		tid = -1;
		opt = nopt;
		fin = BOT_THR_BEG;
		c_by = nc_by;
		func = nfunc;
		t_I = std::chrono::steady_clock::now();
		min_ratv = nmin_ratv;
		sig = 0;

		if (ntn)
		{
			size_t x = strlen(ntn);

			if (x && x < 256)
			{
				thread_name.append(ntn);
			}
		}
		if (nvec)
		{
			if (nvec->size() < BOTVEC_LIM)
			{
				for (uint x = 0; x < nvec->size(); x++)
				{
					vals.push_back(nvec->at(x));
				}
			}
		}
	}

private:
};

class TINFO_M
{
public:

	sint lid;
	sint opt;
	sint fin;
	slint tid;
	sint c_by;
	sllint thread;
	sllint attr;
	void *(*func)(void *);
	std::chrono::steady_clock::time_point t_I;
	float min_ratv;
	std::string thread_name;
	std::vector<ullint> vals;
	sint sig;

	void Clear()
	{
		sig = 0;
		min_ratv = 0.0f;
		attr = thread = 0;
		t_I = std::chrono::steady_clock::now();
		opt = lid = c_by = -1;
		tid = -1;
		fin = BOT_THR_BEG;

		if (!thread_name.empty())
		{
			thread_name.clear();
		}

		func = NULL;
		vals.clear();
	}
	
	void Renew(TINFO_M* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		lid = val_->lid;
		tid = val_->tid;
		opt = val_->opt;
		fin = val_->fin;
		c_by = val_->c_by;
		thread = val_->thread;
		attr = val_->attr;
		func = val_->func;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(val_->thread_name.c_str());
		sig = val_->sig;

		if (val_->vals.size() < BOTVEC_LIM)
		{
			for (uint x = 0; x < val_->vals.size(); x++)
			{
				vals.push_back(val_->vals[x]);
			}
		}
	}
	void Renew(TINFO* val_ = 0)
	{
		Clear();
		
		if (!val_)
		{
			return;
		}

		lid = val_->lid;
		tid = val_->tid;
		opt = val_->opt;
		fin = val_->fin;
		c_by = val_->c_by;
		thread = (sllint)&val_->thread;
		attr = (sllint)&val_->attr;
		func = val_->func;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(val_->thread_name.c_str());
		sig = val_->sig;

		if (val_->vals.size() < BOTVEC_LIM)
		{
			for (uint x = 0; x < val_->vals.size(); x++)
			{
				vals.push_back(val_->vals[x]);
			}
		}
	}
	void Renew(sint nopt = -1, c_char* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f, std::vector<ullint>* nvec = 0)
	{
		Clear();
		opt = nopt;
		c_by = nc_by;
		func = nfunc;
		min_ratv = nmin_ratv;
		sig = 0;

		if (ntn)
		{
			size_t x = strlen(ntn);

			if (x && x < 256)
			{
				thread_name.append(ntn);
			}
		}
		if (nvec)
		{
			if (nvec->size() < BOTVEC_LIM)
			{
				for (uint x = 0; x < nvec->size(); x++)
				{
					vals.push_back(nvec->at(x));
				}
			}
		}
	}

	TINFO_M(sint nopt = -1, c_char* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f, std::vector<ullint>* nvec = 0)
	{
		lid = -1;
		tid = -1;
		opt = nopt;
		fin = BOT_THR_BEG;
		c_by = nc_by;
		func = nfunc;
		t_I = std::chrono::steady_clock::now();
		min_ratv = nmin_ratv;
		sig = 0;

		if (ntn)
		{
			size_t x = strlen(ntn);

			if (x && x < 256)
			{
				thread_name.append(ntn);
			}
		}
		if (nvec)
		{
			if (nvec->size() < BOTVEC_LIM)
			{
				for (uint x = 0; x < nvec->size(); x++)
				{
					vals.push_back(nvec->at(x));
				}
			}
		}
	}

private:
};

class bot_thread_counter
{

public:

	sint open_thr;
	sint thr_quit;

	sint Incr() { if (open_thr < (sint)BOTTHREAD_MAX) { open_thr++; return open_thr; } return -1; }
	sint Decr() { if (open_thr > 0) { open_thr--; return open_thr; } return -1; }
	sint Get() { return open_thr; }
	sint SetQuit(sint val = -1) { if (val > -1) { thr_quit = val; return 0; } return -1; }
	sint GetQuit() { return thr_quit; }

	bot_thread_counter() { open_thr = (sint)BOTTHREAD_MAX; thr_quit = 0; }

private:
	
};

typedef struct bot_arg
{
	sllint loc;
	std::string arg;

	bot_arg(sllint nl = -1, c_char* narg = 0) { loc = nl; if (narg) { size_t x = bot_cstrlen(narg); if (x && x < (size_t)BOT_STRLEN_MAX) { arg.append(narg); } } }
}BOT_ARG;


// BOT RUNTIME VARIABLES

typedef struct bot_var_t
{
	_char* n;
	std::vector<std::vector<_char>> v;
	sint t;

	bot_var_t()
	{
		n = 0;
		v.clear();
		t = 0;
	}

}BOT_VAR_T;

class bot_vars
{

public:

	std::vector<BOT_VAR_T> vars;

	void Clear()
	{
		vars.clear();
	}
	void Renew(bot_vars* nval)
	{
		Clear();
		for (size_t x = 0; x < nval->vars.size(); x++)
		{
			vars.push_back(nval->vars[x]);
		}
	}
	sint AddVar(c_char* nn = 0, void* nv = 0, sint nt = -1, sint vt = -1, bool overw = false)
	{
		if (nn && nt > -1 && vt > -1)
		{
			if (nn[0])
			{
				_char trm = '\0';
				sint y = -1;
				size_t x = 0;

				while (x < vars.size())
				{
					if (vars[x].t < 0)
					{
						y = (sint)x;
					}
					else if (!strcmp(vars[x].n, nn))
					{
						if (nv && overw)
						{
							switch (vars[x].t)
							{
							case BOT_RTV_SLLINT:
							{
								if (!vars[x].v.empty())
								{
									vars[x].v.clear();
								}
								std::vector<_char> nvec;
								vars[x].v.push_back(nvec);
								_char* ov = (_char*)malloc(sizeof(sllint));

								if (ov)
								{
									switch (vt)
									{
									case BOT_RTV_SLLINT:
									{
										memcpy((void*)ov, nv, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}

										break;
									}
									case BOT_RTV_REAL:
									{
										float* av = reinterpret_cast<float*>(nv);

										if (av)
										{
											sllint xv = (sllint)(*av);
											memcpy((void*)ov, (void*)&xv, sizeof(sllint));

											for (size_t z = 0; z < sizeof(sllint); z++)
											{
												vars[x].v[0].push_back(ov[z]);
											}
										}
										break;
									}
									case BOT_RTV_STR:
									{
										std::string* av = reinterpret_cast<std::string*>(nv);

										if (av)
										{
											if (bot_sisn(av->c_str(), av->length()))
											{
												sllint xv = (sllint)_atoi64(av->c_str());
											}
										}
										break;
									}
									case BOT_RTV_BLOB:
									{
										_char* av = reinterpret_cast<_char*>(nv);

										if (av)
										{
											size_t ln = bot_strlen(av);

											if (ln == sizeof(sllint))
											{
												for (size_t z = 0; z < sizeof(sllint); z++)
												{
													vars[x].v[0].push_back(av[z]);
												}
											}
										}
										break;
									}
									default:
									{
										break;
									}
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								if (!vars[x].v.empty())
								{
									vars[x].v.clear();
								}
								std::vector<_char> nvec;
								vars[x].v.push_back(nvec);
								_char* ov = (_char*)malloc(sizeof(float));

								if (ov)
								{
									switch (vt)
									{
									case BOT_RTV_REAL:
									{
										memcpy((void*)ov, nv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}
										break;
									}
									case BOT_RTV_SLLINT:
									{
										sllint* av = reinterpret_cast<sllint*>(nv);

										if (av)
										{
											float xv = (float)(*av);
											memcpy((void*)ov, (void*)&xv, sizeof(float));

											for (size_t z = 0; z < sizeof(float); z++)
											{
												vars[x].v[0].push_back(ov[z]);
											}
										}
										break;
									}
									case BOT_RTV_STR:
									{
										std::string* av = reinterpret_cast<std::string*>(nv);

										if (av)
										{
											if (bot_sisn(av->c_str(), av->length()))
											{
												float xv = (float)atof(av->c_str());
											}
										}
										break;
									}
									case BOT_RTV_BLOB:
									{
										_char* av = reinterpret_cast<_char*>(nv);

										if (av)
										{
											size_t ln = bot_strlen(av);

											if (ln == sizeof(float))
											{
												for (size_t z = 0; z < sizeof(float); z++)
												{
													vars[x].v[0].push_back(av[z]);
												}
											}
										}
										break;
									}
									default:
									{
										break;
									}
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_STR:
							{
								if (!vars[x].v.empty())
								{
									vars[x].v.clear();
								}
								std::vector<_char> nvec;
								vars[x].v.push_back(nvec);

								switch (vt)
								{
								case BOT_RTV_SLLINT:
								{
									sllint* xv = reinterpret_cast<sllint*>(nv);
									std::string av;
									bot_itoa(*xv, &av);
									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[0].push_back(av[z]);
									}
									break;
								}
								case BOT_RTV_REAL:
								{
									float* xv = reinterpret_cast<float*>(nv);
									std::string av;
									bot_dtoa(*xv, &av);
									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[0].push_back(av[z]);
									}
									break;
								}
								case BOT_RTV_STR:
								{
									std::string* xv = reinterpret_cast<std::string*>(nv);

									for (size_t z = 0; z < xv->length(); z++)
									{
										vars[x].v[0].push_back(xv->at(z));
									}
									break;
								}
								case BOT_RTV_BLOB:
								{
									_char* xv = reinterpret_cast<_char*>(nv);
									size_t ln = bot_strlen(xv);

									for (size_t z = 0; z < ln; z++)
									{
										vars[x].v[0].push_back(xv[z]);
									}
									break;
								}
								default:
								{
									break;
								}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								if (!vars[x].v.empty())
								{
									vars[x].v.clear();
								}
								std::vector<_char> nvec;
								vars[x].v.push_back(nvec);

								switch (vt)
								{
								case BOT_RTV_SLLINT:
								{
									_char* xv = (_char*)malloc(sizeof(sllint));

									if (xv)
									{
										memcpy((void*)xv, nv, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[0].push_back(xv[z]);
										}
										free(xv);
									}
									break;
								}
								case BOT_RTV_REAL:
								{
									_char* xv = (_char*)malloc(sizeof(float));

									if (xv)
									{
										memcpy((void*)xv, nv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[0].push_back(xv[z]);
										}
										free(xv);
									}
									break;
								}
								case BOT_RTV_STR:
								{
									std::string* xv = reinterpret_cast<std::string*>(nv);

									if (xv)
									{
										for (size_t z = 0; z < xv->length(); z++)
										{
											vars[x].v[0].push_back(xv->at(z));
										}
									}
									break;
								}
								case BOT_RTV_BLOB:
								{
									_char* xv = reinterpret_cast<_char*>(nv);

									if (xv)
									{
										size_t ln = bot_strlen(xv);

										for (size_t z = 0; z < ln; z++)
										{
											vars[x].v[0].push_back(xv[z]);
										}
									}
									break;
								}
								default:
								{
									break;
								}
								}
								break;
							}
							case BOT_RTV_VSLLINT:
							{
								switch (vt)
								{
								case BOT_RTV_SLLINT:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										memcpy((void*)ov, nv, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_REAL:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										float* xv = reinterpret_cast<float*>(nv);
										sllint av = (sllint)&xv;
										memcpy((void*)ov, (void*)&av, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_STR:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										std::string* xv = reinterpret_cast<std::string*>(nv);

										if (bot_sisn(xv->c_str(), xv->length()))
										{
											sllint av = (sllint)_atoi64(xv->c_str());
											memcpy((void*)ov, (void*)&av, sizeof(sllint));

											for (size_t z = 0; z < sizeof(sllint); z++)
											{
												vars[x].v[st].push_back(ov[z]);
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_BLOB:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* xv = reinterpret_cast<_char*>(nv);
									size_t ln = bot_strlen(xv);

									if (ln == sizeof(sllint))
									{
										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(xv[z]);
										}
									}
									break;
								}
								case BOT_RTV_VSLLINT:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(sllint));

											for (size_t w = 0; w < sizeof(sllint); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VREAL:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											sllint av = (sllint)xv->at(z);
											memcpy((void*)ov, (void*)&av, sizeof(sllint));

											for (size_t w = 0; w < sizeof(sllint); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VSTR:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).c_str(), xv->at(z).length()))
											{
												vars[x].v.push_back(nvec);
												sllint av = (sllint)_atoi64(xv->at(z).c_str());
												memcpy((void*)ov, (void*)&av, sizeof(sllint));

												for (size_t w = 0; w < sizeof(sllint); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VBLOB:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}

									std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);
									std::vector<_char> nvec;
									for (size_t z = 0; z < xv->size(); z++)
									{
										if (xv->at(z).size() == sizeof(sllint))
										{
											vars[x].v.push_back(nvec);

											for (size_t w = 0; w < sizeof(sllint); w++)
											{
												vars[x].v[z].push_back(xv->at(z)[w]);
											}
										}
									}
									break;
								}
								case BOT_RTV_VARG:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).arg.c_str(), xv->at(z).arg.length()))
											{
												vars[x].v.push_back(nvec);
												sllint av = (sllint)_atoi64(xv->at(z).arg.c_str());
												memcpy((void*)ov, (void*)&av, sizeof(sllint));

												for (size_t w = 0; w < sizeof(sllint); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
									break;
								}
								default:
								{
									break;
								}
								}
								break;
							}
							case BOT_RTV_VREAL:
							{
								switch (vt)
								{
								case BOT_RTV_SLLINT:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										sllint* xv = reinterpret_cast<sllint*>(nv);
										float av = (float)*xv;
										memcpy((void*)ov, (void*)&av, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_REAL:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										memcpy((void*)ov, nv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_STR:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										std::string* xv = reinterpret_cast<std::string*>(nv);
										float av = (float)atof(xv->c_str());
										memcpy((void*)ov, nv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_BLOB:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										std::string* xv = reinterpret_cast<std::string*>(nv);
										float av = (float)atof(xv->c_str());
										memcpy((void*)ov, nv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VSLLINT:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											float av = (float)xv->at(z);
											memcpy((void*)ov, (void*)&av, sizeof(float));

											for (size_t w = 0; w < sizeof(float); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VREAL:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(float));

											for (size_t w = 0; w < sizeof(float); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VSTR:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).c_str(), xv->at(z).length()))
											{
												vars[x].v.push_back(nvec);
												float av = (float)atof(xv->at(z).c_str());
												memcpy((void*)ov, (void*)&av, sizeof(float));

												for (size_t w = 0; w < sizeof(float); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VBLOB:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (xv->at(z).size() == sizeof(float))
											{
												vars[x].v.push_back(nvec);

												for (size_t w = 0; w < sizeof(float); w++)
												{
													vars[x].v[z].push_back(xv->at(z)[w]);
												}
											}
										}
										free(ov);
									}
									break;
								}
								case BOT_RTV_VARG:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);
									std::vector<_char> nvec;
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).arg.c_str(), xv->at(z).arg.length()))
											{
												vars[x].v.push_back(nvec);
												float av = (float)atof(xv->at(z).arg.c_str());
												memcpy((void*)ov, (void*)&av, sizeof(float));

												for (size_t w = 0; w < sizeof(float); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
									break;
								}
								default:
								{
									break;
								}
								}
								break;
							}
							case BOT_RTV_VSTR:
							{
								switch (vt)
								{
								case BOT_RTV_SLLINT:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									sllint* xv = reinterpret_cast<sllint*>(nv);
									std::string av;
									bot_itoa(*xv, &av);
									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[st].push_back(av[z]);
									}
									break;
								}
								case BOT_RTV_REAL:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									float* xv = reinterpret_cast<float*>(nv);
									std::string av;
									bot_dtoa(*xv, &av);
									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[st].push_back(av[z]);
									}
									break;
								}
								case BOT_RTV_STR:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									std::string* xv = reinterpret_cast<std::string*>(nv);

									for (size_t z = 0; z < xv->length(); z++)
									{
										vars[x].v[st].push_back(xv->at(z));
									}
									break;
								}
								case BOT_RTV_BLOB:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* xv = reinterpret_cast<_char*>(nv);
									size_t ln = bot_strlen(xv);

									for (size_t z = 0; z < ln; z++)
									{
										vars[x].v[st].push_back(xv[z]);
									}
									break;
								}
								case BOT_RTV_VSLLINT:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);
										std::string av;
										bot_itoa(xv->at(z), &av);
										for (size_t n = 0; n < av.length(); n++)
										{
											vars[x].v[z].push_back(av[n]);
										}
									}
									break;
								}
								case BOT_RTV_VREAL:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);
										std::string av;
										bot_dtoa(xv->at(z), &av);
										for (size_t n = 0; n < av.length(); n++)
										{
											vars[x].v[z].push_back(av[n]);
										}
									}
									break;
								}
								case BOT_RTV_VSTR:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
									break;
								}
								case BOT_RTV_VBLOB:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).size(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
									break;
								}
								case BOT_RTV_VARG:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).arg.length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z).arg[n]);
										}
									}
									break;
								}
								default:
								{
									break;
								}
								}
								break;
							}
							case BOT_RTV_VBLOB:
							{
								switch (vt)
								{
								case BOT_RTV_SLLINT:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									sllint* xv = reinterpret_cast<sllint*>(nv);

									if (xv)
									{
										_char* ov = (_char*)malloc(sizeof(sllint));

										if (ov)
										{
											memcpy((void*)ov, (void*)xv, sizeof(sllint));

											for (size_t z = 0; z < sizeof(sllint); z++)
											{
												vars[x].v[st].push_back(ov[z]);
											}
											free(ov);
										}
									}
									break;
								}
								case BOT_RTV_REAL:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									float* xv = reinterpret_cast<float*>(nv);

									if (xv)
									{
										_char* ov = (_char*)malloc(sizeof(float));

										if (ov)
										{
											memcpy((void*)ov, (void*)xv, sizeof(float));

											for (size_t z = 0; z < sizeof(float); z++)
											{
												vars[x].v[st].push_back(ov[z]);
											}
											free(ov);
										}
									}
									break;
								}
								case BOT_RTV_STR:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									std::string* xv = reinterpret_cast<std::string*>(nv);

									if (xv)
									{
										for (size_t z = 0; z < xv->length(); z++)
										{
											vars[x].v[st].push_back(xv->at(z));
										}
									}
									break;
								}
								case BOT_RTV_BLOB:
								{
									size_t st = vars[x].v.size();
									std::vector<_char> nvec;
									vars[x].v.push_back(nvec);
									_char* xv = reinterpret_cast<_char*>(nv);

									if (xv)
									{
										size_t vl = bot_strlen(xv);

										for (size_t z = 0; z < vl; z++)
										{
											vars[x].v[st].push_back(xv[z]);
										}
									}
									break;
								}
								case BOT_RTV_VSLLINT:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										_char* ov = (_char*)malloc(sizeof(sllint));

										if (ov)
										{
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(sllint));
											vars[x].v.push_back(nvec);

											for (size_t n = 0; n < sizeof(sllint); n++)
											{
												vars[x].v[z].push_back(ov[n]);
											}
											free(ov);
										}
									}
									break;
								}
								case BOT_RTV_VREAL:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										_char* ov = (_char*)malloc(sizeof(float));

										if (ov)
										{
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(float));
											vars[x].v.push_back(nvec);

											for (size_t n = 0; n < sizeof(float); n++)
											{
												vars[x].v[z].push_back(ov[n]);
											}
											free(ov);
										}
									}
									break;
								}
								case BOT_RTV_VSTR:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
									break;
								}
								case BOT_RTV_VBLOB:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).size(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
									break;
								}
								case BOT_RTV_VARG:
								{
									if (!vars[x].v.empty())
									{
										vars[x].v.clear();
									}
									std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);
									std::vector<_char> nvec;

									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).arg.length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z).arg[n]);
										}
									}
									break;
								}
								default:
								{
									break;
								}
								}
								break;
							}
							default:
							{
								break;
							}
							}
						}
						x = vars.size();
					}
					else {}
					x++;
				}

				if (x == vars.size())
				{
					if (nt == BOT_RTV_MAX)
					{
						nt = vt;
					}

					size_t vl = bot_cstrlen(nn);

					if (y > -1)
					{
						x = y;
						vars[x].t = nt;
						_char* nvar = (_char*)realloc(vars[x].n, vl + 1);

						if (nvar)
						{
							vars[x].n = nvar;
							memcpy((void*)vars[x].n, (void*)nn, vl);
							memcpy((void*)&vars[x].n[vl], (void*)&trm, sizeof(_char));
						}
					}
					else
					{
						BOT_VAR_T nvar;
						vars.push_back(nvar);
						vars[x].t = nt;
						vars[x].n = (_char*)malloc(vl + 1);

						if (vars[x].n)
						{
							memcpy((void*)vars[x].n, (void*)nn, vl);
							memcpy((void*)&vars[x].n[vl], (void*)&trm, sizeof(_char));
						}
					}

					if (!nv)
					{
						if (!vars[x].v.empty())
						{
							vars[x].v.clear();
						}
						std::vector<_char> nvec;
						vars[x].v.push_back(nvec);
						vl = 0;
					}
					else
					{
						switch (nt)
						{
						case BOT_RTV_SLLINT:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}
							std::vector<_char> nvec;
							vars[x].v.push_back(nvec);

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								_char* ov = (_char*)malloc(sizeof(sllint));

								if (ov)
								{
									memcpy((void*)ov, nv, sizeof(sllint));

									for (size_t z = 0; z < sizeof(sllint); z++)
									{
										vars[x].v[0].push_back(ov[z]);
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								_char* ov = (_char*)malloc(sizeof(sllint));

								if (ov)
								{
									float* xv = reinterpret_cast<float*>(nv);
									sllint av = (sllint)*xv;
									memcpy((void*)ov, (void*)&av, sizeof(sllint));

									for (size_t z = 0; z < sizeof(sllint); z++)
									{
										vars[x].v[0].push_back(ov[z]);
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_STR:
							{
								_char* ov = (_char*)malloc(sizeof(sllint));

								if (ov)
								{
									std::string* xv = reinterpret_cast<std::string*>(nv);

									if (bot_sisn(xv->c_str(), xv->length()))
									{
										sllint av = (sllint)_atoi64(xv->c_str());
										memcpy((void*)ov, (void*)&av, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								_char* ov = (_char*)malloc(sizeof(sllint));

								if (ov)
								{
									_char* xv = reinterpret_cast<_char*>(nv);
									size_t ln = bot_strlen(xv);

									if (ln == sizeof(sllint))
									{
										memcpy((void*)ov, (void*)xv, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}
									}
									free(ov);
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_REAL:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}
							std::vector<_char> nvec;
							vars[x].v.push_back(nvec);

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								_char* ov = (_char*)malloc(sizeof(float));

								if (ov)
								{
									sllint* xv = reinterpret_cast<sllint*>(nv);
									float av = (float)*xv;
									memcpy((void*)ov, (void*)&av, sizeof(float));

									for (size_t z = 0; z < sizeof(float); z++)
									{
										vars[x].v[0].push_back(ov[z]);
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								_char* ov = (_char*)malloc(sizeof(float));

								if (ov)
								{
									memcpy((void*)ov, nv, sizeof(float));

									for (size_t z = 0; z < sizeof(float); z++)
									{
										vars[x].v[0].push_back(ov[z]);
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_STR:
							{
								_char* ov = (_char*)malloc(sizeof(float));

								if (ov)
								{
									std::string* xv = reinterpret_cast<std::string*>(nv);
									float av = (float)atof(xv->c_str());
									memcpy((void*)ov, (void*)&av, sizeof(float));

									for (size_t z = 0; z < sizeof(float); z++)
									{
										vars[x].v[0].push_back(ov[z]);
									}
									free(ov);
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								_char* ov = (_char*)malloc(sizeof(float));

								if (ov)
								{
									_char* xv = reinterpret_cast<_char*>(nv);
									size_t ln = bot_strlen(xv);

									if (ln == sizeof(float))
									{
										memcpy((void*)ov, (void*)xv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}
									}
									free(ov);
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_STR:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}
							std::vector<_char> nvec;
							vars[x].v.push_back(nvec);

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								sllint* xv = reinterpret_cast<sllint*>(nv);

								if (xv)
								{
									std::string av;
									bot_itoa(*xv, &av);

									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[0].push_back(av[z]);
									}
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								float* xv = reinterpret_cast<float*>(nv);

								if (xv)
								{
									std::string av;
									bot_dtoa(*xv, &av);

									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[0].push_back(av[z]);
									}
								}
								break;
							}
							case BOT_RTV_STR:
							{
								std::string* xv = reinterpret_cast<std::string*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->length(); z++)
									{
										vars[x].v[0].push_back(xv->at(z));
									}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								_char* xv = reinterpret_cast<_char*>(nv);

								if (xv)
								{
									size_t ln = bot_strlen(xv);

									for (size_t z = 0; z < ln; z++)
									{
										vars[x].v[0].push_back(xv[z]);
									}
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_BLOB:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}
							std::vector<_char> nvec;
							vars[x].v.push_back(nvec);

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								sllint* xv = reinterpret_cast<sllint*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								float* xv = reinterpret_cast<float*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[0].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_STR:
							{
								std::string* xv = reinterpret_cast<std::string*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->length(); z++)
									{
										vars[x].v[0].push_back(xv->at(z));
									}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								_char* xv = reinterpret_cast<_char*>(nv);

								if (xv)
								{
									size_t vl = bot_strlen(xv);

									for (size_t z = 0; z < vl; z++)
									{
										vars[x].v[0].push_back(xv[z]);
									}
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_VSLLINT:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}
							size_t st = vars[x].v.size();
							std::vector<_char> nvec;

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								sllint* xv = reinterpret_cast<sllint*>(nv);

								if (xv)
								{
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										memcpy((void*)ov, (void*)xv, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								float* xv = reinterpret_cast<float*>(nv);

								if (xv)
								{
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										sllint av = (sllint)*xv;
										memcpy((void*)ov, (void*)&av, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_STR:
							{
								std::string* xv = reinterpret_cast<std::string*>(nv);

								if (xv)
								{
									if (bot_sisn(xv->c_str(), xv->length()))
									{
										vars[x].v.push_back(nvec);
										_char* ov = (_char*)malloc(sizeof(sllint));

										if (ov)
										{
											sllint av = (sllint)_atoi64(xv->c_str());
											memcpy((void*)ov, (void*)&av, sizeof(sllint));

											for (size_t z = 0; z < sizeof(sllint); z++)
											{
												vars[x].v[st].push_back(ov[z]);
											}
											free(ov);
										}
									}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								_char* xv = reinterpret_cast<_char*>(nv);

								if (xv)
								{
									size_t ln = bot_strlen(xv);

									if (ln == sizeof(sllint))
									{
										vars[x].v.push_back(nvec);

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(xv[z]);
										}
									}
								}
								break;
							}
							case BOT_RTV_VSLLINT:
							{
								std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(sllint));

											for (size_t w = 0; w < sizeof(sllint); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VREAL:
							{
								std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											sllint av = (sllint)xv->at(z);
											memcpy((void*)ov, (void*)&av, sizeof(sllint));

											for (size_t w = 0; w < sizeof(sllint); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VSTR:
							{
								std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).c_str(), xv->at(z).length()))
											{
												vars[x].v.push_back(nvec);
												sllint av = (sllint)_atoi64(xv->at(z).c_str());
												memcpy((void*)ov, (void*)&av, sizeof(sllint));

												for (size_t w = 0; w < sizeof(sllint); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VBLOB:
							{
								std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (xv->at(z).size() == sizeof(sllint))
											{
												vars[x].v.push_back(nvec);

												for (size_t w = 0; w < sizeof(sllint); w++)
												{
													vars[x].v[z].push_back(xv->at(z)[w]);
												}
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VARG:
							{
								std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).arg.c_str(), xv->at(z).arg.length()))
											{
												vars[x].v.push_back(nvec);
												sllint av = (sllint)_atoi64(xv->at(z).arg.c_str());
												memcpy((void*)ov, (void*)&av, sizeof(sllint));

												for (size_t w = 0; w < sizeof(sllint); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_VREAL:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}
							size_t st = vars[x].v.size();
							std::vector<_char> nvec;

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								sllint* xv = reinterpret_cast<sllint*>(nv);

								if (xv)
								{
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										float av = (float)*xv;
										memcpy((void*)ov, (void*)&av, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								float* xv = reinterpret_cast<float*>(nv);

								if (xv)
								{
									vars[x].v.push_back(nvec);
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										memcpy((void*)ov, (void*)xv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_STR:
							{
								std::string* xv = reinterpret_cast<std::string*>(nv);

								if (xv)
								{
									if (bot_sisn(xv->c_str(), xv->length()))
									{
										vars[x].v.push_back(nvec);
										_char* ov = (_char*)malloc(sizeof(float));

										if (ov)
										{
											float av = (float)atof(xv->c_str());
											memcpy((void*)ov, (void*)&av, sizeof(float));

											for (size_t z = 0; z < sizeof(float); z++)
											{
												vars[x].v[st].push_back(ov[z]);
											}
											free(ov);
										}
									}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								_char* xv = reinterpret_cast<_char*>(nv);

								if (xv)
								{
									size_t ln = bot_strlen(xv);

									if (ln == sizeof(float))
									{
										vars[x].v.push_back(nvec);

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(xv[z]);
										}
									}
								}
								break;
							}
							case BOT_RTV_VSLLINT:
							{
								std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											float av = (float)xv->at(z);
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&av, sizeof(float));

											for (size_t w = 0; w < sizeof(float); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VREAL:
							{
								std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(float));

											for (size_t w = 0; w < sizeof(float); w++)
											{
												vars[x].v[z].push_back(ov[w]);
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VSTR:
							{
								std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).c_str(), xv->at(z).length()))
											{
												vars[x].v.push_back(nvec);
												float av = (float)atof(xv->at(z).c_str());
												memcpy((void*)ov, (void*)&av, sizeof(float));

												for (size_t w = 0; w < sizeof(float); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VBLOB:
							{
								std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (xv->at(z).size() == sizeof(float))
											{
												vars[x].v.push_back(nvec);

												for (size_t w = 0; w < sizeof(float); w++)
												{
													vars[x].v[z].push_back(xv->at(z)[w]);
												}
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VARG:
							{
								std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											if (bot_sisn(xv->at(z).arg.c_str(), xv->at(z).arg.length()))
											{
												vars[x].v.push_back(nvec);
												float av = (float)atof(xv->at(z).arg.c_str());
												memcpy((void*)ov, (void*)&av, sizeof(float));

												for (size_t w = 0; w < sizeof(float); w++)
												{
													vars[x].v[z].push_back(ov[w]);
												}
											}
										}
										free(ov);
									}
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_VSTR:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}

							size_t st = vars[x].v.size();
							std::vector<_char> nvec;

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								vars[x].v.push_back(nvec);
								sllint* xv = reinterpret_cast<sllint*>(nv);

								if (xv)
								{
									std::string av;
									bot_itoa(*xv, &av);
									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[st].push_back(av[z]);
									}
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								vars[x].v.push_back(nvec);
								float* xv = reinterpret_cast<float*>(nv);

								if (xv)
								{
									std::string av;
									bot_dtoa(*xv, &av);
									for (size_t z = 0; z < av.length(); z++)
									{
										vars[x].v[st].push_back(av[z]);
									}
								}
								break;
							}
							case BOT_RTV_STR:
							{
								vars[x].v.push_back(nvec);
								std::string* xv = reinterpret_cast<std::string*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->length(); z++)
									{
										vars[x].v[st].push_back(xv->at(z));
									}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								vars[x].v.push_back(nvec);
								_char* xv = reinterpret_cast<_char*>(nv);

								if (xv)
								{
									size_t ln = bot_strlen(xv);
									for (size_t z = 0; z < ln; z++)
									{
										vars[x].v[st].push_back(xv[z]);
									}
								}
								break;
							}
							case BOT_RTV_VSTR:
							{
								std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
								}
								break;
							}
							case BOT_RTV_VARG:
							{
								if (!vars[x].v.empty())
								{
									vars[x].v.clear();
								}
								std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).arg.length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z).arg[n]);
										}
									}
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						case BOT_RTV_VBLOB:
						{
							if (!vars[x].v.empty())
							{
								vars[x].v.clear();
							}

							size_t st = vars[x].v.size();
							std::vector<_char> nvec;

							switch (vt)
							{
							case BOT_RTV_SLLINT:
							{
								vars[x].v.push_back(nvec);
								sllint* xv = reinterpret_cast<sllint*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										memcpy((void*)ov, (void*)xv, sizeof(sllint));

										for (size_t z = 0; z < sizeof(sllint); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_REAL:
							{
								vars[x].v.push_back(nvec);
								float* xv = reinterpret_cast<float*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										memcpy((void*)ov, (void*)xv, sizeof(float));

										for (size_t z = 0; z < sizeof(float); z++)
										{
											vars[x].v[st].push_back(ov[z]);
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_STR:
							{
								vars[x].v.push_back(nvec);
								std::string* xv = reinterpret_cast<std::string*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->length(); z++)
									{
										vars[x].v[st].push_back(xv->at(z));
									}
								}
								break;
							}
							case BOT_RTV_BLOB:
							{
								vars[x].v.push_back(nvec);
								_char* xv = reinterpret_cast<_char*>(nv);

								if (xv)
								{
									size_t vl = bot_strlen(xv);

									for (size_t z = 0; z < vl; z++)
									{
										vars[x].v[st].push_back(xv[z]);
									}
								}
								break;
							}
							case BOT_RTV_VSLLINT:
							{
								std::vector<sllint>* xv = reinterpret_cast<std::vector<sllint>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(sllint));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(sllint));

											for (size_t n = 0; n < sizeof(sllint); n++)
											{
												vars[x].v[z].push_back(ov[n]);
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VREAL:
							{
								std::vector<float>* xv = reinterpret_cast<std::vector<float>*>(nv);

								if (xv)
								{
									_char* ov = (_char*)malloc(sizeof(float));

									if (ov)
									{
										for (size_t z = 0; z < xv->size(); z++)
										{
											vars[x].v.push_back(nvec);
											memcpy((void*)ov, (void*)&xv->at(z), sizeof(float));

											for (size_t n = 0; n < sizeof(float); n++)
											{
												vars[x].v[z].push_back(ov[n]);
											}
										}
										free(ov);
									}
								}
								break;
							}
							case BOT_RTV_VSTR:
							{
								std::vector<std::string>* xv = reinterpret_cast<std::vector<std::string>*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
								}
								break;
							}
							case BOT_RTV_VBLOB:
							{
								std::vector<std::vector<_char>>* xv = reinterpret_cast<std::vector<std::vector<_char>>*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).size(); n++)
										{
											vars[x].v[z].push_back(xv->at(z)[n]);
										}
									}
								}
								break;
							}
							case BOT_RTV_VARG:
							{
								std::vector<BOT_ARG>* xv = reinterpret_cast<std::vector<BOT_ARG>*>(nv);

								if (xv)
								{
									for (size_t z = 0; z < xv->size(); z++)
									{
										vars[x].v.push_back(nvec);

										for (size_t n = 0; n < xv->at(z).arg.length(); n++)
										{
											vars[x].v[z].push_back(xv->at(z).arg[n]);
										}
									}
								}
								break;
							}
							default:
							{
								break;
							}
							}
							break;
						}
						default:
						{
							break;
						}
						}
					}
				}
				return (sint)x;
			}
		}
		return -1;
	}
	sint FindVar(c_char* nn = 0)
	{
		if (!nn)
		{
			return -1;
		}

		for (size_t x = 0; x < vars.size(); x++)
		{
			if (!strcmp(vars[x].n, nn) && vars[x].t > -1)
			{
				return (sint)x;
			}
		}
		return -1;
	}
	sint GetVar(c_char* nm = 0, sint as_t = -1, void* val = 0)
	{
		if (!nm || as_t < 0 || !val)
		{
			return -1;
		}
		sint ret = FindVar(nm);

		if (ret > -1)
		{
			switch (vars[ret].t)
			{
			case BOT_RTV_SLLINT:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					switch (as_t)
					{
					case BOT_RTV_SLLINT:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						sllint* inv = reinterpret_cast<sllint*>(val);
						*inv = av;
						break;
					}
					case BOT_RTV_REAL:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						float* inv = reinterpret_cast<float*>(val);
						*inv = (float)av;
						break;
					}
					case BOT_RTV_STR:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						std::string* inv = reinterpret_cast<std::string*>(val);
						bot_itoa(av, inv);
						break;
					}
					case BOT_RTV_BLOB:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						_char* inv = reinterpret_cast<_char*>(val);
						size_t x = 0;
						for (; x < sizeof(sllint); x++)
						{
							memcpy((void*)&inv[x], (void*)&sumv[x], sizeof(_char));
						}
						_char trm = '\0';
						memcpy((void*)&inv[x], (void*)&trm, sizeof(_char));
						break;
					}
					case BOT_RTV_ARG:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);
						bot_itoa(av, &inv->arg);
						break;
					}
					case BOT_RTV_VSLLINT:
					{
						std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							inv->push_back(av);
						}
						break;
					}
					case BOT_RTV_VREAL:
					{
						std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							inv->push_back((float)av);
						}
						break;
					}
					case BOT_RTV_VSTR:
					{
						std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							std::string str;
							bot_itoa(av, &str);
							inv->push_back(str);
						}
						break;
					}
					case BOT_RTV_VBLOB:
					{
						std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							size_t z = inv->size();
							std::vector<_char> nv;
							inv->push_back(nv);

							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								inv->at(z).push_back(vars[ret].v[x][y]);
							}
						}
						break;
					}
					case BOT_RTV_VARG:
					{
						std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							BOT_ARG arg;
							bot_itoa(av, &arg.arg);
							inv->push_back(arg);
						}
						break;
					}
					default:
					{
						break;
					}
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_REAL:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					switch (as_t)
					{
					case BOT_RTV_SLLINT:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						sllint* inv = reinterpret_cast<sllint*>(val);
						*inv = (sllint)av;
						break;
					}
					case BOT_RTV_REAL:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						float* inv = reinterpret_cast<float*>(val);
						*inv = av;
						break;
					}
					case BOT_RTV_STR:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						std::string* inv = reinterpret_cast<std::string*>(val);
						bot_dtoa((double)av, inv);
						break;
					}
					case BOT_RTV_BLOB:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						_char* inv = reinterpret_cast<_char*>(val);
						size_t x = 0;
						for (; x < sizeof(float); x++)
						{
							memcpy((void*)&inv[x], (void*)&sumv[x], sizeof(_char));
						}
						_char trm = '\0';
						memcpy((void*)&inv[x], (void*)&trm, sizeof(_char));
						break;
					}
					case BOT_RTV_ARG:
					{
						for (size_t x = 0; x < vars[ret].v[0].size(); x++)
						{
							memcpy((void*)sumv, (void*)&vars[ret].v[0][x], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);
						bot_dtoa((double)av, &inv->arg);
						break;
					}
					case BOT_RTV_VSLLINT:
					{
						std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							inv->push_back((sllint)av);
						}
						break;
					}
					case BOT_RTV_VREAL:
					{
						std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							inv->push_back(av);
						}
						break;
					}
					case BOT_RTV_VSTR:
					{
						std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							std::string str;
							bot_dtoa((double)av, &str);
							inv->push_back(str);
						}
						break;
					}
					case BOT_RTV_VBLOB:
					{
						std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							size_t z = inv->size();
							std::vector<_char> nv;
							inv->push_back(nv);

							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								inv->at(z).push_back(vars[ret].v[x][y]);
							}
						}
						break;
					}
					case BOT_RTV_VARG:
					{
						std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

						for (size_t x = 0; x < vars[x].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							BOT_ARG arg;
							bot_dtoa((double)av, &arg.arg);
							inv->push_back(arg);
						}
						break;
					}
					default:
					{
						break;
					}
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_STR:
			{
				std::string str;

				for (size_t y = 0; y < vars[ret].v[0].size(); y++)
				{
					str.push_back(vars[ret].v[0][y]);
				}

				switch (as_t)
				{
				case BOT_RTV_SLLINT:
				{
					sllint* inv = reinterpret_cast<sllint*>(val);
					*inv = _atoi64(str.c_str());
					break;
				}
				case BOT_RTV_REAL:
				{
					float* inv = reinterpret_cast<float*>(val);
					*inv = (float)atof(str.c_str());
					break;
				}
				case BOT_RTV_STR:
				{
					std::string* inv = reinterpret_cast<std::string*>(val);
					inv->append(str.c_str());
					break;
				}
				case BOT_RTV_BLOB:
				{
					_char* inv = reinterpret_cast<_char*>(val);
					size_t len = bot_strlen(inv);
					for (size_t y = 0; y < len && y < str.length(); y++)
					{
						memcpy((void*)&inv[y], (void*)&str[y], sizeof(_char));
					}
					break;
				}
				case BOT_RTV_ARG:
				{
					BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);
					inv->arg.append(str.c_str());
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);
					inv->push_back(_atoi64(str.c_str()));
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);
					inv->push_back((float)atof(str.c_str()));
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);
					inv->push_back(str);
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);
					std::vector<_char> nv;
					size_t vl = inv->size();
					inv->push_back(nv);

					for (size_t y = 0; y < str.length(); y++)
					{
						inv->at(vl).push_back(str[y]);
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);
					BOT_ARG arg(0, str.c_str());
					inv->push_back(arg);
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case BOT_RTV_BLOB:
			{
				switch (as_t)
				{
				case BOT_RTV_SLLINT:
				{
					if (vars[ret].v[0].size() == sizeof(sllint))
					{
						_char* sumv = (_char*)malloc(vars[ret].v[0].size() + 1);

						if (sumv)
						{
							_char trm = '\0';
							memcpy((void*)&sumv[vars[ret].v[0].size()], (void*)&trm, sizeof(_char));

							sllint* inv = reinterpret_cast<sllint*>(val);

							for (size_t y = 0; y < sizeof(sllint); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[0][y], sizeof(_char));
							}
							memcpy((void*)inv, (void*)sumv, sizeof(sllint));
							free(sumv);
						}
					}
					break;
				}
				case BOT_RTV_REAL:
				{
					if (vars[ret].v[0].size() == sizeof(float))
					{
						_char* sumv = (_char*)malloc(vars[ret].v[0].size() + 1);

						if (sumv)
						{
							_char trm = '\0';
							memcpy((void*)&sumv[vars[ret].v[0].size()], (void*)&trm, sizeof(_char));

							float* inv = reinterpret_cast<float*>(val);

							for (size_t y = 0; y < sizeof(float); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[0][y], sizeof(_char));
							}
							memcpy((void*)inv, (void*)sumv, sizeof(float));
							free(sumv);
						}
					}
					break;
				}
				case BOT_RTV_STR:
				{
					std::string* inv = reinterpret_cast<std::string*>(val);

					for (size_t y = 0; y < vars[ret].v[0].size(); y++)
					{
						inv->push_back(vars[ret].v[0][y]);
					}
					break;
				}
				case BOT_RTV_BLOB:
				{
					_char* inv = reinterpret_cast<_char*>(val);
					size_t vl = bot_strlen(inv);

					for (size_t y = 0; y < vl; y++)
					{
						memcpy((void*)&inv[y], (void*)&vars[ret].v[0][y], sizeof(_char));
					}
					break;
				}
				case BOT_RTV_ARG:
				{
					BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);

					for (size_t y = 0; y < vars[ret].v[0].size(); y++)
					{
						inv->arg.push_back(vars[ret].v[0][y]);
					}
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					if (vars[ret].v[0].size() == sizeof(sllint))
					{
						_char* sumv = (_char*)malloc(vars[ret].v[0].size() + 1);

						if (sumv)
						{
							_char trm = '\0';
							memcpy((void*)&sumv[vars[ret].v[0].size()], (void*)&trm, sizeof(_char));

							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							inv->push_back(av);
							free(sumv);
						}
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					if (vars[ret].v[0].size() == sizeof(float))
					{
						_char* sumv = (_char*)malloc(vars[ret].v[0].size() + 1);

						if (sumv)
						{
							_char trm = '\0';
							memcpy((void*)&sumv[vars[ret].v[0].size()], (void*)&trm, sizeof(_char));

							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							inv->push_back(av);
							free(sumv);
						}
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					if (!vars[ret].v[0].empty())
					{
						std::string av;

						for (size_t y = 0; y < vars[ret].v[0].size(); y++)
						{
							av.push_back(vars[ret].v[0][y]);
						}
						inv->push_back(av);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					if (!vars[ret].v[0].empty())
					{
						size_t vl = inv->size();
						std::vector<_char> av;
						inv->push_back(av);

						for (size_t y = 0; y < vars[ret].v[0].size(); y++)
						{
							inv->at(vl).push_back(vars[ret].v[0][y]);
						}

					}
					break;
				}
				case BOT_RTV_VARG:
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					if (!vars[ret].v[0].empty())
					{
						BOT_ARG av;

						for (size_t y = 0; y < vars[ret].v[0].size(); y++)
						{
							av.arg.push_back(vars[ret].v[0][y]);
						}
						inv->push_back(av);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				switch (as_t)
				{
				case BOT_RTV_VSLLINT:
				{
					_char* sumv = (_char*)malloc(sizeof(sllint));

					if (sumv)
					{
						std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							inv->push_back(av);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					_char* sumv = (_char*)malloc(sizeof(sllint));

					if (sumv)
					{
						std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							inv->push_back((float)av);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					_char* sumv = (_char*)malloc(sizeof(sllint));

					if (sumv)
					{
						std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							std::string str;
							bot_itoa(av, &str);
							inv->push_back(str);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::vector<_char> nv;
						size_t vl = inv->size();
						inv->push_back(nv);

						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							inv->at(vl).push_back(vars[ret].v[x][y]);
						}
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					_char* sumv = (_char*)malloc(sizeof(sllint));

					if (sumv)
					{
						std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							BOT_ARG a;
							bot_itoa(av, &a.arg);
							inv->push_back(a);
						}
						free(sumv);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case BOT_RTV_VREAL:
			{
				switch (as_t)
				{
				case BOT_RTV_VSLLINT:
				{
					_char* sumv = (_char*)malloc(sizeof(float));

					if (sumv)
					{
						std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							inv->push_back((sllint)av);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					_char* sumv = (_char*)malloc(sizeof(float));

					if (sumv)
					{
						std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							inv->push_back(av);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					_char* sumv = (_char*)malloc(sizeof(float));

					if (sumv)
					{
						std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							std::string str;
							bot_dtoa((double)av, &str);
							inv->push_back(str);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::vector<_char> nv;
						size_t vl = inv->size();
						inv->push_back(nv);

						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							inv->at(vl).push_back(vars[ret].v[x][y]);
						}
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					_char* sumv = (_char*)malloc(sizeof(float));

					if (sumv)
					{
						std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ret].v[x][y], sizeof(_char));
							}
							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							BOT_ARG a;
							bot_dtoa((double)av, &a.arg);
							inv->push_back(a);
						}
						free(sumv);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case BOT_RTV_VSTR:
			{
				switch (as_t)
				{
				case BOT_RTV_VSLLINT:
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::string sumv;
						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							sumv.push_back(vars[ret].v[x][y]);
						}

						if (bot_sisn(sumv.c_str(), sumv.length()))
						{
							inv->push_back(_atoi64(sumv.c_str()));
						}
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::string sumv;
						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							sumv.push_back(vars[ret].v[x][y]);
						}

						if (bot_sisn(sumv.c_str(), sumv.length()))
						{
							inv->push_back((float)atof(sumv.c_str()));
						}
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::string sumv;
						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							sumv.push_back(vars[ret].v[x][y]);
						}
						inv->push_back(sumv);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::vector<_char> nv;
						size_t vl = inv->size();
						inv->push_back(nv);

						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							inv->at(vl).push_back(vars[ret].v[x][y]);
						}
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						BOT_ARG sumv;
						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							sumv.arg.push_back(vars[ret].v[x][y]);
						}
						inv->push_back(sumv);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case BOT_RTV_VBLOB:
			{
				switch (as_t)
				{
				case BOT_RTV_VSLLINT:
				{
					_char* sumv = (_char*)malloc(sizeof(sllint));

					if (sumv)
					{
						std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ret].v[x].size(); y++)
							{
								memcpy((void*)&sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
							}

							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							inv->push_back(av);
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					_char* sumv = (_char*)malloc(sizeof(float));

					if (sumv)
					{
						std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

						for (size_t x = 0; x < vars[ret].v.size(); x++)
						{
							for (size_t x = 0; x < vars[ret].v.size(); x++)
							{
								for (size_t y = 0; y < vars[ret].v[x].size(); y++)
								{
									memcpy((void*)&sumv, (void*)&vars[ret].v[x][y], sizeof(_char));
								}

								float av = 0.0f;
								memcpy((void*)&av, (void*)sumv, sizeof(float));
								inv->push_back(av);
							}
						}
						free(sumv);
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::string sumv;
						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							sumv.push_back(vars[ret].v[x][y]);
						}
						inv->push_back(sumv);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						std::vector<_char> nv;
						size_t vl = inv->size();
						inv->push_back(nv);

						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							inv->at(vl).push_back(vars[ret].v[x][y]);
						}
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					for (size_t x = 0; x < vars[ret].v.size(); x++)
					{
						BOT_ARG sumv;
						for (size_t y = 0; y < vars[ret].v[x].size(); y++)
						{
							sumv.arg.push_back(vars[ret].v[x][y]);
						}
						inv->push_back(sumv);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			default:
			{
				break;
			}
			}
			return 0;
		}
		return -1;
	}
	sint GetVar(size_t ele = 0, sint as_t = -1, void* val = 0)
	{
		if (ele > vars.size() || as_t < 0 || !val)
		{
			return -1;
		}
		switch (vars[ele].t)
		{
		case BOT_RTV_SLLINT:
		{
			_char* sumv = (_char*)malloc(sizeof(sllint));

			if (sumv)
			{
				switch (as_t)
				{
				case BOT_RTV_SLLINT:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					sllint av = 0;
					memcpy((void*)&av, (void*)sumv, sizeof(sllint));
					sllint* inv = reinterpret_cast<sllint*>(val);
					*inv = av;
					break;
				}
				case BOT_RTV_REAL:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					sllint av = 0;
					memcpy((void*)&av, (void*)sumv, sizeof(sllint));
					float* inv = reinterpret_cast<float*>(val);
					*inv = (float)av;
					break;
				}
				case BOT_RTV_STR:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					sllint av = 0;
					memcpy((void*)&av, (void*)sumv, sizeof(sllint));
					std::string* inv = reinterpret_cast<std::string*>(val);
					bot_itoa(av, inv);
					break;
				}
				case BOT_RTV_BLOB:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					_char* inv = reinterpret_cast<_char*>(val);
					size_t x = 0;
					for (; x < sizeof(sllint); x++)
					{
						memcpy((void*)&inv[x], (void*)&sumv[x], sizeof(_char));
					}
					_char trm = '\0';
					memcpy((void*)&inv[x], (void*)&trm, sizeof(_char));
					break;
				}
				case BOT_RTV_ARG:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					sllint av = 0;
					memcpy((void*)&av, (void*)sumv, sizeof(sllint));
					BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);
					bot_itoa(av, &inv->arg);
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						inv->push_back(av);
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						inv->push_back((float)av);
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						std::string str;
						bot_itoa(av, &str);
						inv->push_back(str);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						size_t z = inv->size();
						std::vector<_char> nv;
						inv->push_back(nv);

						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							inv->at(z).push_back(vars[ele].v[x][y]);
						}
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						BOT_ARG arg;
						bot_itoa(av, &arg.arg);
						inv->push_back(arg);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				free(sumv);
			}
			break;
		}
		case BOT_RTV_REAL:
		{
			_char* sumv = (_char*)malloc(sizeof(float));

			if (sumv)
			{
				switch (as_t)
				{
				case BOT_RTV_SLLINT:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					float av = 0.0f;
					memcpy((void*)&av, (void*)sumv, sizeof(float));
					sllint* inv = reinterpret_cast<sllint*>(val);
					*inv = (sllint)av;
					break;
				}
				case BOT_RTV_REAL:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					float av = 0.0f;
					memcpy((void*)&av, (void*)sumv, sizeof(float));
					float* inv = reinterpret_cast<float*>(val);
					*inv = av;
					break;
				}
				case BOT_RTV_STR:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					float av = 0.0f;
					memcpy((void*)&av, (void*)sumv, sizeof(sllint));
					std::string* inv = reinterpret_cast<std::string*>(val);
					bot_dtoa((double)av, inv);
					break;
				}
				case BOT_RTV_BLOB:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					_char* inv = reinterpret_cast<_char*>(val);
					size_t x = 0;
					for (; x < sizeof(float); x++)
					{
						memcpy((void*)&inv[x], (void*)&sumv[x], sizeof(_char));
					}
					_char trm = '\0';
					memcpy((void*)&inv[x], (void*)&trm, sizeof(_char));
					break;
				}
				case BOT_RTV_ARG:
				{
					for (size_t x = 0; x < vars[ele].v[0].size(); x++)
					{
						memcpy((void*)&sumv[x], (void*)&vars[ele].v[0][x], sizeof(_char));
					}

					float av = 0.0f;
					memcpy((void*)&av, (void*)sumv, sizeof(float));
					BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);
					bot_dtoa((double)av, &inv->arg);
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						inv->push_back((sllint)av);
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						inv->push_back(av);
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						std::string str;
						bot_dtoa((double)av, &str);
						inv->push_back(str);
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						size_t z = inv->size();
						std::vector<_char> nv;
						inv->push_back(nv);

						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							inv->at(z).push_back(vars[ele].v[x][y]);
						}
					}
					break;
				}
				case BOT_RTV_VARG:
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					for (size_t x = 0; x < vars[x].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						BOT_ARG arg;
						bot_dtoa((double)av, &arg.arg);
						inv->push_back(arg);
					}
					break;
				}
				default:
				{
					break;
				}
				}
				free(sumv);
			}
			break;
		}
		case BOT_RTV_STR:
		{
			std::string str;

			for (size_t y = 0; y < vars[ele].v[0].size(); y++)
			{
				str.push_back(vars[ele].v[0][y]);
			}

			switch (as_t)
			{
			case BOT_RTV_SLLINT:
			{
				sllint* inv = reinterpret_cast<sllint*>(val);
				*inv = _atoi64(str.c_str());
				break;
			}
			case BOT_RTV_REAL:
			{
				float* inv = reinterpret_cast<float*>(val);
				*inv = (float)atof(str.c_str());
				break;
			}
			case BOT_RTV_STR:
			{
				std::string* inv = reinterpret_cast<std::string*>(val);
				inv->append(str.c_str());
				break;
			}
			case BOT_RTV_BLOB:
			{
				_char* inv = reinterpret_cast<_char*>(val);
				size_t len = bot_strlen(inv);
				for (size_t y = 0; y < len && y < str.length(); y++)
				{
					memcpy((void*)&inv[y], (void*)&str[y], sizeof(_char));
				}
				break;
			}
			case BOT_RTV_ARG:
			{
				BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);
				inv->arg.append(str.c_str());
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);
				inv->push_back(_atoi64(str.c_str()));
				break;
			}
			case BOT_RTV_VREAL:
			{
				std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);
				inv->push_back((float)atof(str.c_str()));
				break;
			}
			case BOT_RTV_VSTR:
			{
				std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);
				inv->push_back(str);
				break;
			}
			case BOT_RTV_VBLOB:
			{
				std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);
				std::vector<_char> nv;
				size_t vl = inv->size();
				inv->push_back(nv);

				for (size_t y = 0; y < str.length(); y++)
				{
					inv->at(vl).push_back(str[y]);
				}
				break;
			}
			case BOT_RTV_VARG:
			{
				std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);
				BOT_ARG arg(0, str.c_str());
				inv->push_back(arg);
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case BOT_RTV_BLOB:
		{
			switch (as_t)
			{
			case BOT_RTV_SLLINT:
			{
				if (vars[ele].v[0].size() == sizeof(sllint))
				{
					_char* sumv = (_char*)malloc(vars[ele].v[0].size() + 1);

					if (sumv)
					{
						_char trm = '\0';
						memcpy((void*)&sumv[vars[ele].v[0].size()], (void*)&trm, sizeof(_char));

						sllint* inv = reinterpret_cast<sllint*>(val);

						for (size_t y = 0; y < sizeof(sllint); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[0][y], sizeof(_char));
						}
						memcpy((void*)inv, (void*)sumv, sizeof(sllint));
						free(sumv);
					}
				}
				break;
			}
			case BOT_RTV_REAL:
			{
				if (vars[ele].v[0].size() == sizeof(float))
				{
					_char* sumv = (_char*)malloc(vars[ele].v[0].size() + 1);

					if (sumv)
					{
						_char trm = '\0';
						memcpy((void*)&sumv[vars[ele].v[0].size()], (void*)&trm, sizeof(_char));

						float* inv = reinterpret_cast<float*>(val);

						for (size_t y = 0; y < sizeof(float); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[0][y], sizeof(_char));
						}
						memcpy((void*)inv, (void*)sumv, sizeof(float));
						free(sumv);
					}
				}
				break;
			}
			case BOT_RTV_STR:
			{
				std::string* inv = reinterpret_cast<std::string*>(val);

				for (size_t y = 0; y < vars[ele].v[0].size(); y++)
				{
					inv->push_back(vars[ele].v[0][y]);
				}
				break;
			}
			case BOT_RTV_BLOB:
			{
				_char* inv = reinterpret_cast<_char*>(val);
				size_t vl = bot_strlen(inv);

				for (size_t y = 0; y < vl; y++)
				{
					memcpy((void*)&inv[y], (void*)&vars[ele].v[0][y], sizeof(_char));
				}
				break;
			}
			case BOT_RTV_ARG:
			{
				BOT_ARG* inv = reinterpret_cast<BOT_ARG*>(val);

				for (size_t y = 0; y < vars[ele].v[0].size(); y++)
				{
					inv->arg.push_back(vars[ele].v[0][y]);
				}
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

				if (vars[ele].v[0].size() == sizeof(sllint))
				{
					_char* sumv = (_char*)malloc(vars[ele].v[0].size() + 1);

					if (sumv)
					{
						_char trm = '\0';
						memcpy((void*)&sumv[vars[ele].v[0].size()], (void*)&trm, sizeof(_char));

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						inv->push_back(av);
						free(sumv);
					}
				}
				break;
			}
			case BOT_RTV_VREAL:
			{
				std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

				if (vars[ele].v[0].size() == sizeof(float))
				{
					_char* sumv = (_char*)malloc(vars[ele].v[0].size() + 1);

					if (sumv)
					{
						_char trm = '\0';
						memcpy((void*)&sumv[vars[ele].v[0].size()], (void*)&trm, sizeof(_char));

						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						inv->push_back(av);
						free(sumv);
					}
				}
				break;
			}
			case BOT_RTV_VSTR:
			{
				std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

				if (!vars[ele].v[0].empty())
				{
					std::string av;

					for (size_t y = 0; y < vars[ele].v[0].size(); y++)
					{
						av.push_back(vars[ele].v[0][y]);
					}
					inv->push_back(av);
				}
				break;
			}
			case BOT_RTV_VBLOB:
			{
				std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

				if (!vars[ele].v[0].empty())
				{
					size_t vl = inv->size();
					std::vector<_char> av;
					inv->push_back(av);

					for (size_t y = 0; y < vars[ele].v[0].size(); y++)
					{
						inv->at(vl).push_back(vars[ele].v[0][y]);
					}

				}
				break;
			}
			case BOT_RTV_VARG:
			{
				std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

				if (!vars[ele].v[0].empty())
				{
					BOT_ARG av;

					for (size_t y = 0; y < vars[ele].v[0].size(); y++)
					{
						av.arg.push_back(vars[ele].v[0][y]);
					}
					inv->push_back(av);
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case BOT_RTV_VSLLINT:
		{
			switch (as_t)
			{
			case BOT_RTV_STR:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					std::string* inv = reinterpret_cast<std::string*>(val);

					if (inv)
					{
						for (size_t x = 0; x < vars[ele].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ele].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
							}
							sllint av = 0;
							memcpy((void*)&av, (void*)sumv, sizeof(sllint));
							sint ret = bot_sprintfs(inv, false, "%lli, ", av);
						}
						inv->pop_back();
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						inv->push_back(av);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VREAL:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						inv->push_back((float)av);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VSTR:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						std::string str;
						bot_itoa(av, &str);
						inv->push_back(str);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VBLOB:
			{
				std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::vector<_char> nv;
					size_t vl = inv->size();
					inv->push_back(nv);

					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						inv->at(vl).push_back(vars[ele].v[x][y]);
					}
				}
				break;
			}
			case BOT_RTV_VARG:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						BOT_ARG a;
						bot_itoa(av, &a.arg);
						inv->push_back(a);
					}
					free(sumv);
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case BOT_RTV_VREAL:
		{
			switch (as_t)
			{
			case BOT_RTV_STR:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					std::string* inv = reinterpret_cast<std::string*>(val);

					if (inv)
					{
						for (size_t x = 0; x < vars[ele].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ele].v[x].size(); y++)
							{
								memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
							}
							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							sint ret = bot_sprintfs(inv, false, "%.9f, ", av);
						}
						inv->pop_back();
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						inv->push_back((sllint)av);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VREAL:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						inv->push_back(av);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VSTR:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						std::string str;
						bot_dtoa((double)av, &str);
						inv->push_back(str);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VBLOB:
			{
				std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::vector<_char> nv;
					size_t vl = inv->size();
					inv->push_back(nv);

					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						inv->at(vl).push_back(vars[ele].v[x][y]);
					}
				}
				break;
			}
			case BOT_RTV_VARG:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv[y], (void*)&vars[ele].v[x][y], sizeof(_char));
						}
						float av = 0.0f;
						memcpy((void*)&av, (void*)sumv, sizeof(float));
						BOT_ARG a;
						bot_dtoa((double)av, &a.arg);
						inv->push_back(a);
					}
					free(sumv);
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case BOT_RTV_VSTR:
		{
			switch (as_t)
			{
			case BOT_RTV_STR:
			{
				std::string* inv = reinterpret_cast<std::string*>(val);

				if (inv)
				{
					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							inv->push_back(vars[ele].v[x][y]);
						}
						inv->append(" ");
					}
					inv->pop_back();
				}
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::string sumv;
					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						sumv.push_back(vars[ele].v[x][y]);
					}

					if (bot_sisn(sumv.c_str(), sumv.length()))
					{
						inv->push_back(_atoi64(sumv.c_str()));
					}
				}
				break;
			}
			case BOT_RTV_VREAL:
			{
				std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::string sumv;
					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						sumv.push_back(vars[ele].v[x][y]);
					}

					if (bot_sisn(sumv.c_str(), sumv.length()))
					{
						inv->push_back((float)atof(sumv.c_str()));
					}
				}
				break;
			}
			case BOT_RTV_VSTR:
			{
				std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::string sumv;
					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						sumv.push_back(vars[ele].v[x][y]);
					}
					inv->push_back(sumv);
				}
				break;
			}
			case BOT_RTV_VBLOB:
			{
				std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::vector<_char> nv;
					size_t vl = inv->size();
					inv->push_back(nv);

					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						inv->at(vl).push_back(vars[ele].v[x][y]);
					}
				}
				break;
			}
			case BOT_RTV_VARG:
			{
				std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					BOT_ARG sumv;
					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						sumv.arg.push_back(vars[ele].v[x][y]);
					}
					inv->push_back(sumv);
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case BOT_RTV_VBLOB:
		{
			switch (as_t)
			{
			case BOT_RTV_STR:
			{
				std::string* inv = reinterpret_cast<std::string*>(val);

				if (inv)
				{
					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							sint ret = bot_sprintfs(inv, false, "%02X ", vars[ele].v[x][y]);
						}
						inv->pop_back();
						inv->push_back('\n');
					}
					inv->pop_back();
				}
				break;
			}
			case BOT_RTV_VSLLINT:
			{
				_char* sumv = (_char*)malloc(sizeof(sllint));

				if (sumv)
				{
					std::vector<sllint>* inv = reinterpret_cast<std::vector<sllint>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t y = 0; y < vars[ele].v[x].size(); y++)
						{
							memcpy((void*)&sumv, (void*)&vars[ele].v[x][y], sizeof(_char));
						}

						sllint av = 0;
						memcpy((void*)&av, (void*)sumv, sizeof(sllint));
						inv->push_back(av);
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VREAL:
			{
				_char* sumv = (_char*)malloc(sizeof(float));

				if (sumv)
				{
					std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(val);

					for (size_t x = 0; x < vars[ele].v.size(); x++)
					{
						for (size_t x = 0; x < vars[ele].v.size(); x++)
						{
							for (size_t y = 0; y < vars[ele].v[x].size(); y++)
							{
								memcpy((void*)&sumv, (void*)&vars[ele].v[x][y], sizeof(_char));
							}

							float av = 0.0f;
							memcpy((void*)&av, (void*)sumv, sizeof(float));
							inv->push_back(av);
						}
					}
					free(sumv);
				}
				break;
			}
			case BOT_RTV_VSTR:
			{
				std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::string sumv;
					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						sint ret = bot_sprintfs(&sumv, false, "%02X ", vars[ele].v[x][y]);
					}
					sumv.pop_back();
					inv->push_back(sumv);
				}
				break;
			}
			case BOT_RTV_VBLOB:
			{
				std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					std::vector<_char> nv;
					size_t vl = inv->size();
					inv->push_back(nv);

					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						inv->at(vl).push_back(vars[ele].v[x][y]);
					}
				}
				break;
			}
			case BOT_RTV_VARG:
			{
				std::vector<BOT_ARG>* inv = reinterpret_cast<std::vector<BOT_ARG>*>(val);

				for (size_t x = 0; x < vars[ele].v.size(); x++)
				{
					BOT_ARG sumv;
					for (size_t y = 0; y < vars[ele].v[x].size(); y++)
					{
						sumv.arg.push_back(vars[ele].v[x][y]);
					}
					inv->push_back(sumv);
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		default:
		{
			break;
		}
		}
		return 0;
	}
	sint RemVar(c_char* nn = 0)
	{
		if (nn)
		{
			if (nn[0])
			{
				for (size_t x = 0; x < vars.size(); x++)
				{
					if (!strcmp(vars[x].n, nn))
					{
						vars[x].t = -1;
						bot_strclr(vars[x].n);
						vars[x].v.clear();
					}
				}
			}
		}
		CleanVars();
		return 0;
	}
	sint RemVars(bool b = false, ...)
	{
		std::vector<std::string> vec;
		va_list args;
		va_start(args, b);

		while (!b)
		{
			c_char* val = va_arg(args, c_char*);

			if (val)
			{
				if (val[0])
				{
					std::string str(val);
					vec.push_back(str);
				}
				else
				{
					b = true;
				}
			}
			else
			{
				b = true;
			}
		}
		va_end(args);

		for (size_t x = 0; x < vars.size(); x++)
		{
			for (size_t y = 0; y < vec.size(); y++)
			{
				if (!strcmp(vars[x].n, vec[y].c_str()))
				{
					vars[x].t = -1;
					bot_strclr(vars[x].n);
					vec[y].clear();
					y = vec.size();
				}
			}
		}
		CleanVars();
		return 0;
	}
	void CleanVars()
	{
		for (sint x = (sint)vars.size() - 1; x > -1; x--)
		{
			if (vars[x].t < 0)
			{
				vars[x].v.clear();
				free(vars[x].n);
				vars.pop_back();
			}
			else
			{
				x = -1;
			}
		}
	}

private:

};

class bot_strt_syms
{
public:

	void Clear()
	{
		sql_vals_keywords.clear();
		sql_opers_keywords.clear();
		sql_trans_keywords.clear();
		sql_obj_keywords.clear();
		sql_spec_keywords.clear();
		sql_targ_keywords.clear();
		sql_targ_keywords.clear();
		sql_comp_keywords.clear();
		sql_conj_keywords.clear();
		sql_obj_qual_keywords.clear();
		sql_decl_keywords.clear();
		sql_order_keywords.clear();
		sql_order_keywords.clear();
		sql_lim_keywords.clear();
		sql_cond_qual_keywords.clear();
		sql_act_keywords.clear();
		nrts_ign.clear();
		nrts_lign.clear();
		nrts_lign_.clear();
		nrts_sep.clear();
		nrts_ord.clear();
		nrts_ord_.clear();
		nrts_ass.clear();
		nrts_end.clear();
		nrts_lit.clear();
		nrts_pun.clear();
		nrts_term.clear();
	}
	void Renew(bot_strt_syms* val = 0)
	{
		Clear();

		for (size_t x = 0; x < val->sql_vals_keywords.size(); x++)
		{
			sql_vals_keywords.push_back(val->sql_vals_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_opers_keywords.size(); x++)
		{
			sql_opers_keywords.push_back(val->sql_opers_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_trans_keywords.size(); x++)
		{
			sql_trans_keywords.push_back(val->sql_trans_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_obj_keywords.size(); x++)
		{
			sql_obj_keywords.push_back(val->sql_obj_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_spec_keywords.size(); x++)
		{
			sql_spec_keywords.push_back(val->sql_spec_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_targ_keywords.size(); x++)
		{
			sql_targ_keywords.push_back(val->sql_targ_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_targ_keywords.size(); x++)
		{
			sql_targ_keywords.push_back(val->sql_targ_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_comp_keywords.size(); x++)
		{
			sql_comp_keywords.push_back(val->sql_comp_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_conj_keywords.size(); x++)
		{
			sql_conj_keywords.push_back(val->sql_conj_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_obj_qual_keywords.size(); x++)
		{
			sql_obj_qual_keywords.push_back(val->sql_obj_qual_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_decl_keywords.size(); x++)
		{
			sql_decl_keywords.push_back(val->sql_decl_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_order_keywords.size(); x++)
		{
			sql_order_keywords.push_back(val->sql_order_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_order_keywords.size(); x++)
		{
			sql_order_keywords.push_back(val->sql_order_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_lim_keywords.size(); x++)
		{
			sql_lim_keywords.push_back(val->sql_lim_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_cond_qual_keywords.size(); x++)
		{
			sql_cond_qual_keywords.push_back(val->sql_cond_qual_keywords[x]);
		}

		for (size_t x = 0; x < val->sql_act_keywords.size(); x++)
		{
			sql_act_keywords.push_back(val->sql_act_keywords[x]);
		}

		for (size_t x = 0; x < val->nrts_ign.size(); x++)
		{
			nrts_ign.push_back(val->nrts_ign[x]);
		}

		for (size_t x = 0; x < val->nrts_lign.size(); x++)
		{
			nrts_lign.push_back(val->nrts_lign[x]);
		}

		for (size_t x = 0; x < val->nrts_lign_.size(); x++)
		{
			nrts_lign_.push_back(val->nrts_lign_[x]);
		}

		for (size_t x = 0; x < val->nrts_sep.size(); x++)
		{
			nrts_sep.push_back(val->nrts_sep[x]);
		}

		for (size_t x = 0; x < val->nrts_ord.size(); x++)
		{
			nrts_ord.push_back(val->nrts_ord[x]);
		}

		for (size_t x = 0; x < val->nrts_ord_.size(); x++)
		{
			nrts_ord_.push_back(val->nrts_ord_[x]);
		}

		for (size_t x = 0; x < val->nrts_ass.size(); x++)
		{
			nrts_ass.push_back(val->nrts_ass[x]);
		}

		for (size_t x = 0; x < val->nrts_end.size(); x++)
		{
			nrts_end.push_back(val->nrts_end[x]);
		}

		for (size_t x = 0; x < val->nrts_lit.size(); x++)
		{
			nrts_lit.push_back(val->nrts_lit[x]);
		}

		for (size_t x = 0; x < val->nrts_pun.size(); x++)
		{
			nrts_pun.push_back(val->nrts_pun[x]);
		}

		for (size_t x = 0; x < val->nrts_term.size(); x++)
		{
			nrts_term.push_back(val->nrts_term[x]);
		}
	}
	sint Update(bot_strt_syms* val = 0)
	{
		sint ret = 0;
		for (size_t x = 0; x < val->sql_vals_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_vals_keywords.size())
			{
				if (!strcmp(val->sql_vals_keywords[x].c_str(), sql_vals_keywords[y].c_str()))
				{
					y = sql_vals_keywords.size();
				}
				y++;
			}

			if (y == sql_vals_keywords.size())
			{
				sql_vals_keywords.push_back(val->sql_vals_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_opers_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_opers_keywords.size())
			{
				if (!memcmp((void*)&val->sql_opers_keywords[x], (void*)&sql_opers_keywords[y], sizeof(_char)))
				{
					y = sql_opers_keywords.size();
				}
				y++;
			}

			if (y == sql_opers_keywords.size())
			{
				sql_opers_keywords.push_back(val->sql_opers_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_trans_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_trans_keywords.size())
			{
				if (!strcmp(val->sql_trans_keywords[x].c_str(), sql_trans_keywords[y].c_str()))
				{
					y = sql_trans_keywords.size();
				}
				y++;
			}

			if (y == sql_trans_keywords.size())
			{
				sql_trans_keywords.push_back(val->sql_trans_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_obj_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_obj_keywords.size())
			{
				if (!strcmp(val->sql_obj_keywords[x].c_str(), sql_obj_keywords[y].c_str()))
				{
					y = sql_obj_keywords.size();
				}
				y++;
			}

			if (y == sql_obj_keywords.size())
			{
				sql_obj_keywords.push_back(val->sql_obj_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_spec_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_spec_keywords.size())
			{
				if (!strcmp(val->sql_spec_keywords[x].c_str(), sql_spec_keywords[y].c_str()))
				{
					y = sql_spec_keywords.size();
				}
				y++;
			}

			if (y == sql_spec_keywords.size())
			{
				sql_spec_keywords.push_back(val->sql_spec_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_targ_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_targ_keywords.size())
			{
				if (!strcmp(val->sql_targ_keywords[x].c_str(), sql_targ_keywords[y].c_str()))
				{
					y = sql_targ_keywords.size();
				}
				y++;
			}

			if (y == sql_targ_keywords.size())
			{
				sql_targ_keywords.push_back(val->sql_targ_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_targ_keywords.size(); x++)
		{
			size_t y = 0;
			while (y < sql_targ_keywords.size())
			{
				if (!strcmp(val->sql_targ_keywords[x].c_str(), sql_targ_keywords[y].c_str()))
				{
					y = sql_targ_keywords.size();
				}
				y++;
			}

			if (y == sql_targ_keywords.size())
			{
				sql_targ_keywords.push_back(val->sql_targ_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_comp_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_comp_keywords.size())
			{
				if (!strcmp(val->sql_comp_keywords[x].c_str(), sql_comp_keywords[y].c_str()))
				{
					y = sql_comp_keywords.size();
				}
				y++;
			}

			if (y == sql_comp_keywords.size())
			{
				sql_comp_keywords.push_back(val->sql_comp_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_conj_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_conj_keywords.size())
			{
				if (!strcmp(val->sql_conj_keywords[x].c_str(), sql_conj_keywords[y].c_str()))
				{
					y = sql_conj_keywords.size();
				}
				y++;
			}

			if (y == sql_conj_keywords.size())
			{
				sql_conj_keywords.push_back(val->sql_conj_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_obj_qual_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_obj_qual_keywords.size())
			{
				if (!strcmp(val->sql_obj_qual_keywords[x].c_str(), sql_obj_qual_keywords[y].c_str()))
				{
					y = sql_obj_qual_keywords.size();
				}
				y++;
			}

			if (y == sql_obj_qual_keywords.size())
			{
				sql_obj_qual_keywords.push_back(val->sql_obj_qual_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_decl_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_decl_keywords.size())
			{
				if (!strcmp(val->sql_decl_keywords[x].c_str(), sql_decl_keywords[y].c_str()))
				{
					y = sql_decl_keywords.size();
				}
				y++;
			}

			if (y == sql_decl_keywords.size())
			{
				sql_decl_keywords.push_back(val->sql_decl_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_order_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_order_keywords.size())
			{
				if (!strcmp(val->sql_order_keywords[x].c_str(), sql_order_keywords[y].c_str()))
				{
					y = sql_order_keywords.size();
				}
				y++;
			}

			if (y == sql_order_keywords.size())
			{
				sql_order_keywords.push_back(val->sql_order_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_order_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_order_keywords.size())
			{
				if (!strcmp(val->sql_order_keywords[x].c_str(), sql_order_keywords[y].c_str()))
				{
					y = sql_order_keywords.size();
				}
				y++;
			}

			if (y == sql_order_keywords.size())
			{
				sql_order_keywords.push_back(val->sql_order_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_lim_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_lim_keywords.size())
			{
				if (!strcmp(val->sql_lim_keywords[x].c_str(), sql_lim_keywords[y].c_str()))
				{
					y = sql_lim_keywords.size();
				}
				y++;
			}

			if (y == sql_lim_keywords.size())
			{
				sql_lim_keywords.push_back(val->sql_lim_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_cond_qual_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_cond_qual_keywords.size())
			{
				if (!strcmp(val->sql_cond_qual_keywords[x].c_str(), sql_cond_qual_keywords[y].c_str()))
				{
					y = sql_cond_qual_keywords.size();
				}
				y++;
			}

			if (y == sql_cond_qual_keywords.size())
			{
				sql_cond_qual_keywords.push_back(val->sql_cond_qual_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->sql_act_keywords.size(); x++)
		{
			size_t y = 0;

			while (y < sql_act_keywords.size())
			{
				if (!strcmp(val->sql_act_keywords[x].c_str(), sql_act_keywords[y].c_str()))
				{
					y = sql_act_keywords.size();
				}
				y++;
			}

			if (y == sql_act_keywords.size())
			{
				sql_act_keywords.push_back(val->sql_act_keywords[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_ign.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_ign.size())
			{
				if (!memcmp((void*)&val->nrts_ign[x], (void*)&nrts_ign[y], sizeof(_char)))
				{
					y = nrts_ign.size();
				}
				y++;
			}

			if (y == nrts_ign.size())
			{
				nrts_ign.push_back(val->nrts_ign[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_lign.size(); x++)
		{
			size_t y = 0;

			while (y < nrts_lign.size())
			{
				if (!strcmp(val->nrts_lign[x].c_str(), nrts_lign[y].c_str()))
				{
					y = nrts_lign.size();
				}
				y++;
			}

			if (y == nrts_lign.size())
			{
				nrts_lign.push_back(val->nrts_lign[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_lign_.size(); x++)
		{
			size_t y = 0;

			while (y < nrts_lign_.size())
			{
				if (!strcmp(val->nrts_lign_[x].c_str(), nrts_lign_[y].c_str()))
				{
					y = nrts_lign_.size();
				}
				y++;
			}

			if (y == nrts_lign_.size())
			{
				nrts_lign_.push_back(val->nrts_lign_[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_sep.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_sep.size())
			{
				if (!memcmp((void*)&val->nrts_sep[x], (void*)&nrts_sep[y], sizeof(_char)))
				{
					y = nrts_sep.size();
				}
				y++;
			}

			if (y == nrts_sep.size())
			{
				nrts_sep.push_back(val->nrts_sep[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_ord.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_ord.size())
			{
				if (!memcmp((void*)&val->nrts_ord[x], (void*)&nrts_ord[y], sizeof(_char)))
				{
					y = nrts_ord.size();
				}
				y++;
			}

			if (y == nrts_ord.size())
			{
				nrts_ord.push_back(val->nrts_ord[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_ord_.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_ord_.size())
			{
				if (!memcmp((void*)&val->nrts_ord_[x], (void*)&nrts_ord_[y], sizeof(_char)))
				{
					y = nrts_ord_.size();
				}
				y++;
			}

			if (y == nrts_ord_.size())
			{
				nrts_ord_.push_back(val->nrts_ord_[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_ass.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_ass.size())
			{
				if (!memcmp((void*)&val->nrts_ass[x], (void*)&nrts_ass[y], sizeof(_char)))
				{
					y = nrts_ass.size();
				}
				y++;
			}

			if (y == nrts_ass.size())
			{
				nrts_ass.push_back(val->nrts_ass[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_end.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_end.size())
			{
				if (!memcmp((void*)&val->nrts_end[x], (void*)&nrts_end[y], sizeof(_char)))
				{
					y = nrts_end.size();
				}
				y++;
			}

			if (y == nrts_end.size())
			{
				nrts_end.push_back(val->nrts_end[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_lit.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_lit.size())
			{
				if (!memcmp((void*)&val->nrts_lit[x], (void*)&nrts_lit[y], sizeof(_char)))
				{
					y = nrts_lit.size();
				}
				y++;
			}

			if (y == nrts_lit.size())
			{
				nrts_lit.push_back(val->nrts_lit[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_pun.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_pun.size())
			{
				if (!memcmp((void*)&val->nrts_pun[x], (void*)&nrts_pun[y], sizeof(_char)))
				{
					y = nrts_pun.size();
				}
				y++;
			}

			if (y == nrts_pun.size())
			{
				nrts_pun.push_back(val->nrts_pun[x]);
				ret++;
			}
		}

		for (size_t x = 0; x < val->nrts_term.size(); x++)
		{
			size_t y = 0;
			while (y < nrts_term.size())
			{
				if (!memcmp((void*)&val->nrts_term[x], (void*)&nrts_term[y], sizeof(_char)))
				{
					y = nrts_term.size();
				}
				y++;
			}

			if (y == nrts_term.size())
			{
				nrts_term.push_back(val->nrts_term[x]);
				ret++;
			}
		}
		return ret;
	}

	std::vector<_char> sql_opers_keywords
	{
		' ',
		'*',
		'"',
		'\'',
		'[',
		']',
		'(',
		')',
		'{',
		'}',
		',',
		'.',
		';'
	};

	std::vector<std::string> sql_vals_keywords
	{
		"INTEGER",
		"REAL",
		"TEXT",
		"BLOB",
		"NULL"
	};

	//it_type
	std::vector<std::string> sql_trans_keywords
	{
		"SELECT",
		"UPDATE",
		"INSERT INTO",
		"CREATE",
		"DELETE",
		"DROP",
		"REINDEX",
		"ALTER",
		"ANALYZE",
		"ATTACH",
		"DETACH"
	};

	//ic_type and cont
	std::vector<std::string> sql_obj_keywords
	{
		"DATABASE",
		"TABLE",
		"INDEX",
		"COLUMN",
		"VIEW",
		"TRIGGER",
		"ROW"
	};

	//targ
	std::vector<std::string> sql_targ_keywords
	{
		"USING",
		"FROM",
		"ON"
	};

	// ospec
	std::vector<std::string> sql_obj_qual_keywords
	{
		"UNIQUE",
		"TEMP",
		"DISTINCT",
		"VIRTUAL"
	};

	//spec
	std::vector<std::string> sql_spec_keywords
	{
		"WHERE",
		"AS",
		"VALUES"
	};

	//opts[0]
	std::vector<std::string> sql_comp_keywords
	{
		"BETWEEN",
		"HAVING",
		"LIKE",
		"NOT IN",
		"IN",
		"=",
		">",
		"<",
		">=",
		"<=",
		"!="
	};

	//opts[1]
	std::vector<std::string> sql_conj_keywords
	{
		"AND",
		"OR",
		"BETWEEN"
	};

	//opts[2][0]
	std::vector<std::string> sql_decl_keywords
	{
		"ORDER BY",
		"GROUP BY"
	};

	//opts[2][1]
	std::vector<std::string> sql_order_keywords
	{
		"ASC",
		"DESC"
	};

	//rlim
	std::vector<std::string> sql_lim_keywords
	{
		"LIMIT"
	};

	//ifex
	std::vector<std::string> sql_cond_qual_keywords
	{
		"IF EXISTS",
		"IF NOT EXISTS"
	};

	//act
	std::vector<std::string> sql_act_keywords
	{
		"SET",
		"ADD",
		"RENAME TO"
	};

	std::vector<_char> nrts_ign
	{
		'\\'
	};

	std::vector<std::string> nrts_lign
	{
		"//",
		"/*"
	};

	std::vector<std::string> nrts_lign_
	{
		"\n",
		"*/"
	};

	std::vector<_char> nrts_sep
	{
		' ',
		'\t',
		','
	};

	std::vector<_char> nrts_ord
	{
		'(',
		'{',
		'['
	};

	std::vector<_char> nrts_ord_
	{
		')',
		'}',
		']'
	};

	std::vector<_char> nrts_ass
	{
		'='
	};

	std::vector<_char> nrts_end
	{
		';',
		'\n'
	};

	std::vector<_char> nrts_lit
	{
		'\'',
		'"'
	};

	std::vector<_char> nrts_pun
	{
		';',
		'.',
		'?',
		'!',
		','
	};

	std::vector<_char> nrts_term
	{
		'\0'
	};

private:

};

typedef struct bot_strt_up
{
	std::vector<std::string> dbn
	{
		"litebot",
		"symbols",
		"math",
		"code",
		"scripts",
		"vars"
	};

	std::vector<c_char*> litebot_stmts
	{
		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"QUIT\", 0, 1 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LOGIN\", 0, 2 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"HELP\", 0, 3 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LOGOUT\", 1, 4 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"DEBUGLEVEL\", 1, 5 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"IVAR\", 1, 6 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"PVAR\", 1, 7 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"CVAR\", 1, 8 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LVARS\", 1, 9 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"SPROC\", 100, 20 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LPROC\", 100, 21 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"CPROC\", 100, 22 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LTHREAD\", 100, 30 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"TESTTHREAD\", 100, 31 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"CTHREAD\", 100, 32 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"ADDCOMMAND\", 999, 1000 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"REMOVECOMMAND\", 999, 1001 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"READFILE\", 10, 96 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"ADDSCRIPT\", 100, 98 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"RUNSCRIPT\", 100, 99 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"GIPS\", 100, 100 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"SERVP\", 100, 101 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"CONNECT\", 100, 102 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"DISCONNECT\", 100, 103 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"VSEND\", 100, 104 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"SVSEND\", 100, 105 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"BANIP\", 100, 125 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"ALLOWIP\", 100, 126 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LBANIPS\", 100, 107 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"GETVINS\", 1, 200 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"RENAMEPHOTOS\", 1, 201 );",

		"INSERT INTO litebot.COMMANDS (" \
		"CMD, PRIV, CMD_ID ) VALUES (" \
		"\"LDSSTMT\", 1, 202 );",

		"INSERT INTO litebot.ACCOUNTS ( LOGIN_NAME, PASSWORD, " \
		"PRIV, RAW_NAME, LAST_LOGIN, TOTAL_LOGINS ) VALUES ( " \
		"\"TESTER\", \"1\", 1, \"Tester\", \";)\", 0 );",

		"INSERT INTO litebot.ACCOUNTS ( LOGIN_NAME, PASSWORD, " \
		"PRIV, RAW_NAME, LAST_LOGIN, TOTAL_LOGINS ) VALUES ( " \
		"\"LOXO\", \"s3xohol\", 1000, \"Loxo\", \";)\", 0 );",

		"INSERT INTO litebot.LANGUAGES ( LANGUAGE, ALPHABET, " \
		"U_CASE_CONSONANTS, L_CASE_CONSONANTS, U_CASE_VOWELS, " \
		"L_CASE_VOWELS, NUMBER_SYMS ) VALUES ( \"ENGLISH\", " \
		"\"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz\", " \
		"\"BCDFGHJKLMNPQRSTVWXY\", \"bcdfghjklmnpqrstvwxyz\", \"AEIOU\", " \
		"\"aeiou\", \"0123456789\" );"
	};

	std::vector<BOT_STMT> litebot_pend;

	std::vector<BOT_STMT> sym_pend;

	std::vector<BOT_STMT> code_pend;

	std::vector<c_char*> litebot_tablenames
	{
		"COMMANDS",
		"ACCOUNTS",
		"LANGUAGES",
		"NRTS",
		"SESSION",
		"PORTS",
		"GIPS",
		"BIPS"
	};

	std::vector<c_char*> syms_tablenames
	{
		"SYMS"
	};

	std::vector<c_char*> math_tablenames
	{
		"ARITHMATIC",
		"ALGEBRA",
		"GEOMETRY",
		"TRIGONOMETRY",
		"CALCULUS"
	};

	std::vector<c_char*> scripts_tablenames
	{
		"SCRIPTS"
	};

	std::vector<c_char*> vars_tablenames
	{
		"SINT",
		"REAL",
		"TEXT",
		"BLOB"
	};

	/*
	std::vector<c_char*> code_tablenames
	{
	"unclassified",
	"word",
	"punctuation",
	"filename",
	"filetype",
	"command_symbol",
	"literal_enclosers",
	"order_enclosers",
	"sql",
	"c",
	"number",
	"html",
	"filesystem",
	"logical"
	};
	*/

	std::vector<c_char*> word_tablenames;

	std::vector<c_char*> ex_tablenames;

	std::vector<c_char*> litebot_columns
	{
		"ID INTEGER " \
		"CMD_ID INTEGER " \
		"CMD TEXT " \
		"PRIV INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"LOGIN_NAME TEXT " \
		"PASSWORD TEXT " \
		"PRIV INTEGER " \
		"RAW_NAME TEXT " \
		"LAST_LOGIN TEXT " \
		"LAST_FAILED_LOGIN TEXT " \
		"FAILED_LOGINS INTEGER " \
		"TOTAL_LOGINS INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"LANGUAGE TEXT " \
		"ALPHABET TEXT " \
		"U_CASE_CONSONANTS TEXT " \
		"L_CASE_CONSONANTS TEXT " \
		"CONSONANT_GROUPS TEXT " \
		"U_CASE_VOWELS TEXT " \
		"L_CASE_VOWELS TEXT " \
		"NUMBER_SYMS TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"SYM BLOB " \
		"TYP BLOB " \
		"WID BLOB " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"QUIT INTEGER " \
		"NAME TEXT " \
		"PID INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"PORT INTEGER " \
		"STYPE INTEGER " \
		"PID INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"FAM INTEGER " \
		"ADR TEXT " \
		"NOTE TEXT " \
		"DATE TEXT "  \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"FAM INTEGER " \
		"ADR TEXT " \
		"NOTE TEXT " \
		"DATE TEXT "  \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
	};

	std::vector<c_char*> syms_cols
	{
		"ID INTEGER " \
		"SYMBOL BLOB " \
		"CONSTITUENT_TO BLOB " \
		"ENCODINGS BLOB " \
		"HISTORY_PRECEEDING BLOB " \
		"HISTORY_FOLLOWING BLOB " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
	};

	std::vector<c_char*> scripts_cols
	{
		"ID INTEGER " \
		"MODE BLOB " \
		"ENCODING BLOB " \
		"NAME BLOB " \
		"TYPE BLOB " \
		"DEST BLOB " \
		"USED BLOB " \
		"LAST_USED BLOB " \
		"LAST_USED_BY BLOB " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
	};

	std::vector<c_char*> vars_cols
	{
		"ID INTEGER " \
		"VALUE INTEGER " \
		"WVALUE BLOB " \
		"ASBTR TEXT " \
		"WASBTR BLOB " \
		"DEF TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"VALUE REAL " \
		"WVALUE BLOB " \
		"ASBTR TEXT " \
		"WASBTR BLOB " \
		"DEF TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"VALUE TEXT " \
		"WVALUE BLOB " \
		"ASBTR TEXT " \
		"WASBTR BLOB " \
		"DEF TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"VALUE BLOB " \
		"WVALUE BLOB " \
		"ASBTR TEXT " \
		"WASBTR BLOB " \
		"DEF TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
	};

	std::vector<c_char*> math_columns
	{
		"ID INTEGER " \
		"OPERATOR TEXT " \
		"VARIABLES TEXT " \
		"SYNTAX TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
		"OPERATOR TEXT " \
		"VARIABLES TEXT " \
		"REQ_VARS TEXT " \
		"SYNTAX TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
	};

	std::vector<c_char*> code_columns //add LANGUAGE TEXT column for language syntax code symbols.
	{
		"ID INTEGER " \
		"DATA BLOB " \
		"HISTORY_PRECEEDING BLOB " \
		"HISTORY_FOLLOWING BLOB " \
		"ALTERS BLOB " \
		"ENCODINGS BLOB " \
		"USAGES BLOB " \
		"USED BLOB " \
		"FUNCTIONS TEXT " \
		"LANGUAGES TEXT " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
		//first encoding
	};

	std::vector<c_char*> word_columns
	{
		"ID INTEGER " \
		"USED INTEGER " \
		"WORD TEXT " \
		"LANGUAGES TEXT " \
		"FUNCTIONS TEXT " \
		"ROOTWORDS TEXT " \
		"PHOENETICS TEXT " \
		"SYLLABLES TEXT "\
		"DUPLICATE INTEGER " \
		"SYNTAX TEXT " \
		"NUMBER_EQUIV TEXT " \
		"AS_NAME INTEGER " \
		"AS_TITLE INTEGER " \
		"INTERCHANGEABLES TEXT " \
		"CONJUNCTION_OF TEXT " \
		"COMMON_PRECEEDING TEXT " \
		"COMMON_FOLLOWING TEXT " \
		"HISTORY_PRECEEDING TEXT " \
		"HISTORY_FOLLOWING TEXT " \
		"DEFINITIONS TEXT " \
		"EXAMPLES TEXT " \
		"ALT_LANG_EQUIVS TEXT " \
		"ASSOC_SOUND TEXT " \
		"ASSOC_IMG TEXT " \
		"PROFANITY INTEGER " \
		"AS_CODE INTEGER " \
		"USED_AS_CODE INTEGER " \
		"USAGES TEXT " \
		"LAST_USED_AS TEXT "\
		"LAST_USED INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER"
	};
}BOT_STRT_UP;

typedef struct bot_session
{
	size_t siz;
	sint id;
	sint lid;
	slint pid;
	sint quit;
	carr_256 nm;
	sllint last_mod;
	sllint last_mod_ns;
	sllint last_maint;
	sllint last_maint_ns;

	bot_session(_char* nnm = 0)
	{
		if (nnm)
		{
			size_t ln = bot_strlen(nnm);
			
			if (ln < 4096)
			{
				bot_sprintf(nm.carr, nm.siz, "%s", nnm);
			}
		}
		lid = id = quit = -1;
		last_mod = last_mod_ns = last_maint = last_maint_ns = 0;
		pid = 0;
	}

}BOT_SESSION;

enum c_mems
{
	BOT_C_NAMESET = 0,
	BOT_C_LOGGED_IN = 1,
	BOT_C_CHANGE_N = 2,
	BOT_C_U_PRIV = 3,
	BOT_C_U_LOGIN = 4,
	BOT_C_T_LOGINS = 5,
	BOT_C_F_LOGINS = 6,
	BOT_C_PRIV = 7,
	BOT_C_ID = 8,
	BOT_C_LID = 9,
	BOT_C_NAME = 10,
	BOT_C_L_LOGIN = 11,
	BOT_C_L_DATE = 12,
	BOT_C_LFL = 13,
	BOT_C_LAST_E = 14,
	BOT_C_CBY = 15,
	BOT_C_PRT = 16,
	BOT_C_KYA = 17,
	BOT_C_MAX = 18
};

class BOT_CLIENT
{
public:
	bool nameset;
	bool loggedin;
	bool changename;
	bool updatepriv;
	bool updatelogin;
	sint totallogins;
	sint failed_logins;
	sint priv;
	sint id;
	sint lid;
	sint c_by;
	bot_port prt;
	std::string name;
	std::string lastlogin;
	std::string logindate;
	std::string last_failed_login;
	std::string lastexchange;

	void Clear()
	{
		nameset = loggedin = changename = updatepriv = updatelogin = false;
		totallogins = failed_logins = priv = 0;
		lid = c_by = id = -1;
		name.clear();
		lastlogin.clear();
		logindate.clear();
		last_failed_login.clear();
		lastexchange.clear();
		prt.Clear();
	}
	void Renew(BOT_CLIENT* val_ = 0)
	{
		if (!val_)
		{
			return;
		}

		Clear();
		nameset = val_->nameset;
		loggedin = val_->loggedin;
		changename = val_->changename;
		updatepriv = val_->updatepriv;
		updatelogin = val_->updatelogin;
		totallogins = val_->totallogins;
		failed_logins = val_->failed_logins;
		priv = val_->priv;
		id = val_->id;
		lid = val_->lid;
		c_by = val_->c_by;
		name.append(val_->name.c_str());
		lastlogin.append(val_->lastlogin.c_str());
		last_failed_login.append(val_->last_failed_login.c_str());
		lastexchange.append(val_->lastexchange.c_str());
		prt.Renew(&val_->prt);
	}

	BOT_CLIENT(c_char* nstr = "", bot_port* nport = 0)
	{
		nameset = loggedin = changename = updatepriv = updatelogin = false;
		totallogins = failed_logins = priv = 0;
		lid = c_by = id = -1;
		name.clear();
		lastlogin.clear();
		logindate.clear();
		last_failed_login.clear();
		lastexchange.clear();
		size_t siz = bot_cstrlen(nstr);
		
		if (siz && siz < 128)
		{
			name.append(nstr);
			nameset = true;
		}

		if (nport)
		{
			prt.Renew(nport);
		}
	}

private:

};

class BOT_CLIENT_M
{
public:

	bool nameset;
	bool loggedin;
	bool changename;
	bool updatepriv;
	bool updatelogin;
	sint totallogins;
	sint failed_logins;
	sint priv;
	sint id;
	sint lid;
	sint c_by;
	bot_port prt;
	std::string name;
	std::string lastlogin;
	std::string logindate;
	std::string last_failed_login;
	std::string lastexchange;

	void Clear()
	{
		nameset = loggedin = changename = updatepriv = updatelogin = false;
		totallogins = failed_logins = priv = 0;
		lid = c_by = id = -1;
		name.clear();
		lastlogin.clear();
		logindate.clear();
		last_failed_login.clear();
		lastexchange.clear();
		prt.Clear();
	}
	void Renew(BOT_CLIENT_M* val_ = 0)
	{
		if (!val_)
		{
			return;
		}

		Clear();
		nameset = val_->nameset;
		loggedin = val_->loggedin;
		changename = val_->changename;
		updatepriv = val_->updatepriv;
		updatelogin = val_->updatelogin;
		totallogins = val_->totallogins;
		failed_logins = val_->failed_logins;
		prt.Renew(&val_->prt);
		priv = val_->priv;
		id = val_->id;
		lid = val_->lid;
		c_by = val_->c_by;
		name.append(val_->name.c_str());
		lastlogin.append(val_->lastlogin.c_str());
		last_failed_login.append(val_->last_failed_login.c_str());
		lastexchange.append(val_->lastexchange.c_str());
	}
	void Renew(BOT_CLIENT* val_ = 0)
	{
		if (!val_)
		{
			return;
		}

		Clear();
		nameset = val_->nameset;
		loggedin = val_->loggedin;
		changename = val_->changename;
		updatepriv = val_->updatepriv;
		updatelogin = val_->updatelogin;
		totallogins = val_->totallogins;
		failed_logins = val_->failed_logins;
		prt.Renew(&val_->prt);
		priv = val_->priv;
		id = val_->id;
		lid = val_->lid;
		c_by = val_->c_by;
		name.append(val_->name.c_str());
		lastlogin.append(val_->lastlogin.c_str());
		last_failed_login.append(val_->last_failed_login.c_str());
		lastexchange.append(val_->lastexchange.c_str());
	}

	BOT_CLIENT_M(c_char* nstr = "", bot_port* nport = 0)
	{
		nameset = loggedin = changename = updatepriv = updatelogin = false;
		totallogins = failed_logins = priv = 0;
		lid = c_by = id = -1;
		name.clear();
		lastlogin.clear();
		logindate.clear();
		last_failed_login.clear();
		lastexchange.clear();
		size_t siz = bot_cstrlen(nstr);

		if (siz && siz < 128)
		{
			name.append(nstr);
			nameset = true;
		}

		if (nport)
		{
			prt.Renew(nport);
		}
	}

private:

};

typedef struct log_vec
{
	std::vector<BOT_LOGDET> dvec;
	std::vector<BOT_LOGDET_M> mvec;

	log_vec() { dvec.clear(); mvec.clear(); }

}LOG_VEC;

typedef struct to_thr_vec
{
	std::vector<TINFO> dvec;
	std::vector<TINFO_M> mvec;

	to_thr_vec() { dvec.clear(); mvec.clear(); }

}TO_THR_VEC;

typedef struct db_vec
{
	std::vector<BOT_DB> dvec;
	std::vector<BOT_DB_M> mvec;

	db_vec() { dvec.clear(); mvec.clear(); }

}DB_VEC;

typedef struct c_vec
{
	std::vector<BOT_CLIENT> dvec;
	std::vector<BOT_CLIENT_M> mvec;

	c_vec() { dvec.clear(); mvec.clear(); }

}C_VEC;

typedef struct fo_vec
{
	std::vector<BOT_FILE> dvec;
	std::vector<BOT_FILE_M> mvec;

	fo_vec() { dvec.clear(); mvec.clear(); }

}FO_VEC;

// STOOL

class STool
{
public:

	STool(std::chrono::steady_clock::time_point* nt = 0) { SetTClr(nt); }

	sint TestFindInStr(c_char* inp_ = "", ...)
	{
		if (!inp_)
		{
			return -1;
		}
	}
	std::string CleanFromStr(c_char* inp_ = "", sint from = 0, sint lim = 0, ...)
	{
		std::string str;

		if (!inp_)
		{
			return str;
		}

		sint ilen = (sint)strlen(inp_);

		if (!ilen)
		{
			return str;
		}

		std::vector<_char> cvec;
		va_list args;
		va_start(args, lim);

		for (_char fin = va_arg(args, _char); fin != '\0'; fin = va_arg(args, _char))
		{
			cvec.push_back(fin);
		}
		va_end(args);

		if (!lim)
		{
			lim = ilen - 1;
		}

		for (sint x = from; x < lim; x++)
		{
			uint y = 0;
			while (y < cvec.size())
			{
				if (!memcmp((void*)&inp_[x], (void*)&cvec[y], sizeof(inp_[x])))
				{
					y = cvec.size();
				}
				y++;
			}
			if (y == cvec.size())
			{
				str.push_back(inp_[x]);
			}
		}
		return str;
	}
#ifdef _WIN32
	sint CleanFromCStr(c_char inp_[] = 0, sint from = 0, sint lim = 0, ...)
	{
		if (!inp_)
		{
			return -1;
		}

		sint ilen = (sint)strlen(inp_);

		if (!ilen)
		{
			return -1;
		}

		_char term = '\0';
		_char nuchar[sizeof(inp_)];
		std::vector<_char> cvec;
		va_list args;
		va_start(args, lim);

		for (_char fin = va_arg(args, _char); memcmp((void*)&fin, (void*)&term, 1); fin = va_arg(args, _char))
		{
			cvec.push_back(fin);
		}

		va_end(args);

		if (!lim)
		{
			lim = ilen - 1;
		}

		sint z = 0;

		for (sint x = from; x < lim; x++)
		{
			uint y = 0;

			while (y < cvec.size())
			{
				if (!memcmp((void*)&inp_[x], (void*)&cvec[y], sizeof(inp_[x])))
				{
					y = cvec.size();
				}
				y++;
			}
			if (y == cvec.size())
			{
				memcpy((void*)&nuchar[z], (void*)&inp_[x], sizeof(inp_[x]));
				z += (sint)sizeof(inp_[x]);
			}
		}

		memcpy((void*)&nuchar[z], (void*)&term, 1);

		for (sint x = from; x < z; x++)
		{
			memcpy((void*)&inp_[x], (void*)&nuchar[x], 1);
		}

		memcpy((void*)&inp_[z], (void*)&term, 1);
		return z - 1;
	}
	sint CleanFromUStr(u_char inp_[] = 0, sint from = 0, sint lim = 0, ...)
	{
		if (!inp_)
		{
			return -1;
		}

		sint ilen = (sint)bot_ustrlen(inp_);

		if (!ilen)
		{
			return -1;
		}

		u_char term = (u_char)'\0';
		u_char nuchar[sizeof(inp_)];
		std::vector<u_char> cvec;
		va_list args;
		va_start(args, lim);

		for (u_char fin = va_arg(args, u_char); memcmp((void*)&fin, (void*)&term, 1); fin = va_arg(args, u_char))
		{
			cvec.push_back(fin);
		}
		va_end(args);

		if (!lim)
		{
			lim = ilen - 1;
		}

		sint z = 0;

		for (sint x = from; x < lim; x++)
		{
			uint y = 0;

			while (y < cvec.size())
			{
				if (!memcmp((void*)&inp_[x], (void*)&cvec[y], sizeof(inp_[x])))
				{
					y = cvec.size();
				}
				y++;
			}
			if (y == cvec.size())
			{
				memcpy((void*)&nuchar[z], (void*)&inp_[x], sizeof(inp_[x]));
				z += (sint)sizeof(inp_[x]);
			}
		}

		memcpy((void*)&nuchar[z], (void*)&term, 1);

		for (sint x = from; x < z; x++)
		{
			memcpy((void*)&inp_[x], (void*)&nuchar[x], 1);
		}

		memcpy((void*)&inp_[z], (void*)&nuchar[z], 1);
		return z - 1;
	}
#else
	sint CleanFromCStr(c_char inp_[] = 0, sint from = 0, sint lim = 0, ...)
	{
		if (!inp_)
		{
			return -1;
		}

		sint ilen = (sint)strlen(inp_);

		if (!ilen)
		{
			return -1;
		}

		_char term = '\0';
		_char nuchar[strlen(inp_)];
		std::vector<_char> cvec;
		va_list args;
		va_start(args, lim);

		for (_char fin = va_arg(args, _char); memcmp((void*)&fin, (void*)&term, 1); fin = va_arg(args, _char))
		{
			cvec.push_back(fin);
		}
		va_end(args);

		if (!lim)
		{
			lim = ilen - 1;
		}

		sint z = 0;

		for (sint x = from; x < lim; x++)
		{
			uint y = 0;

			while (y < cvec.size())
			{
				if (!memcmp((void*)&inp_[x], (void*)&cvec[y], sizeof(inp_[x])))
				{
					y = cvec.size();
				}
				y++;
			}
			if (y == cvec.size())
			{
				memcpy((void*)&nuchar[z], (void*)&inp_[x], sizeof(inp_[x]));
				z += (sint)sizeof(inp_[x]);
			}
		}

		memcpy((void*)&nuchar[z], (void*)&term, 1);

		for (sint x = from; x < z; x++)
		{
			memcpy((void*)&inp_[x], (void*)&nuchar[x], 1);
		}

		memcpy((void*)&inp_[z], (void*)&term, 1);
		return z - 1;
	}
	sint CleanFromUStr(u_char inp_[] = 0, sint from = 0, sint lim = 0, ...)
	{
		if (!inp_)
		{
			return -1;
		}

		sint ilen = (sint)bot_ustrlen(inp_);

		if (!ilen)
		{
			return -1;
		}

		u_char term = (u_char)'\0';
		u_char nuchar[bot_ustrlen(inp_)];
		std::vector<u_char> cvec;
		va_list args;
		va_start(args, lim);

		for (sint fin = va_arg(args, sint); memcmp((void*)&fin, (void*)&term, 1); fin = va_arg(args, sint))
		{
			cvec.push_back((u_char)fin);
		}
		va_end(args);

		if (!lim)
		{
			lim = ilen - 1;
		}

		sint z = 0;

		for (sint x = from; x < lim; x++)
		{
			uint y = 0;

			while (y < cvec.size())
			{
				if (!memcmp((void*)&inp_[x], (void*)&cvec[y], sizeof(inp_[x])))
				{
					y = cvec.size();
				}
				y++;
			}
			if (y == cvec.size())
			{
				memcpy((void*)&nuchar[z], (void*)&inp_[x], sizeof(inp_[x]));
				z += (sint)sizeof(inp_[x]);
			}
		}

		memcpy((void*)&nuchar[z], (void*)&term, 1);

		for (sint x = from; x < z; x++)
		{
			memcpy((void*)&inp_[x], (void*)&nuchar[x], 1);
		}

		memcpy((void*)&inp_[z], (void*)&nuchar[z], 1);
		return z - 1;
	}
#endif
	
	sint VToStr(std::vector<ullint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}
		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };

				if (sep)
				{
					sint xc = bot_sprintf(icar, 64, "%llu%s", vec_->at(siz), sep);
				}
				else
				{
					sint xc = bot_sprintf(icar, 64, "%llu", vec_->at(siz));
				}
				size_t il = bot_strlen(icar);
				if (curlen + il < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s", icar);
					curlen += il;
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<ulint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}
		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };

				if (sep)
				{
					sint xc = bot_sprintf(icar, 64, "%lu%s", vec_->at(siz), sep);
				}
				else
				{
					sint xc = bot_sprintf(icar, 64, "%lu", vec_->at(siz));
				}
				size_t il = bot_strlen(icar);
				if (curlen + il < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s", icar);
					curlen += il;
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<uint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };

				if (sep)
				{
					sint xc = bot_sprintf(icar, 64, "%u%s", vec_->at(siz), sep);
				}
				else
				{
					sint xc = bot_sprintf(icar, 64, "%u", vec_->at(siz));
				}
				size_t il = bot_strlen(icar);
				if (curlen + il < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s", icar);
					curlen += il;
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<sllint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };

				if (sep)
				{
					sint xc = bot_sprintf(icar, 64, "%lli%s", vec_->at(siz), sep);
				}
				else
				{
					sint xc = bot_sprintf(icar, 64, "%lli", vec_->at(siz));
				}
				size_t il = bot_strlen(icar);
				if (curlen + il < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s", icar);
					curlen += il;
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<slint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };

				if (sep)
				{
					sint xc = bot_sprintf(icar, 64, "%li%s", vec_->at(siz), sep);
				}
				else
				{
					sint xc = bot_sprintf(icar, 64, "%li", vec_->at(siz));
				}
				size_t il = bot_strlen(icar);
				if (curlen + il < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s", icar);
					curlen += il;
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<sint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };

				if (sep)
				{
					sint xc = bot_sprintf(icar, 64, "%i%s", vec_->at(siz), sep);
				}
				else
				{
					sint xc = bot_sprintf(icar, 64, "%i", vec_->at(siz));
				}
				size_t il = bot_strlen(icar);
				if (curlen + il < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s", icar);
					curlen += il;
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<c_char*>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				size_t nl = bot_cstrlen(vec_->at(siz));
				if (curlen + nl + sl < i_siz)
				{
					if (sep)
					{
						sint xc = bot_sprintf(&instr_[curlen], i_siz, "%s%s", vec_->at(siz), sep);
					}
					else
					{
						sint xc = bot_sprintf(&instr_[curlen], i_siz, "%s", vec_->at(siz));
					}
					curlen += (nl + sl);
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';

			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<std::string>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t sl = 0;

			if (sep)
			{
				sl = bot_cstrlen(sep);
			}
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				if (curlen + vec_->at(siz).length() + sl < i_siz)
				{
					if (sep)
					{
						sint xc = bot_sprintf(&instr_[curlen], i_siz, "%s%s", vec_->at(siz).c_str(), sep);
					}
					else
					{
						sint xc = bot_sprintf(&instr_[curlen], i_siz, "%s", vec_->at(siz).c_str());
					}
					curlen += (vec_->at(siz).length() + sl);
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}

			instr_[curlen - sl] = '\0';
			
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	std::string VToStr(std::vector<c_char*>* vec_ = 0, c_char* sep = " ", size_t offs = 0, size_t lim = 0)
	{
		if (!vec_)
		{
			std::string str;
			return str;
		}
		size_t sl = 0;
		std::string str;

		if (!lim || lim > vec_->size())
		{
			lim = vec_->size();
		}

		if (sep)
		{
			sl = bot_cstrlen(sep);
		}

		for (size_t siz = offs; siz < lim; siz++)
		{
			if (bot_cstrlen(vec_->at(siz)) + str.length() + sl < BOT_STRLEN_MAX)
			{
				str.append(vec_->at(siz));

				if (sl)
				{
					str.append(sep);
				}
			}
			else
			{
				siz = vec_->size();
			}
		}
		for (size_t siz = 0; siz < sl; siz++)
		{
			str.pop_back();
		}
		return str;
	}
	std::string VToStr(std::vector<std::string>* vec_ = 0, c_char* sep = " ", size_t offs = 0, size_t lim = 0)
	{
		if (!vec_)
		{
			std::string str;
			return str;
		}
		size_t sl = 0;
		std::string str;

		if (!lim || lim > vec_->size())
		{
			lim = vec_->size();
		}

		if (sep)
		{
			sl = bot_cstrlen(sep);
		}

		for (size_t siz = offs; siz < lim; siz++)
		{
			if (vec_->at(siz).length() + str.length() + sl < BOT_STRLEN_MAX)
			{
				str.append(vec_->at(siz));

				if (sl)
				{
					str.append(sep);
				}
			}
			else
			{
				siz = vec_->size();
			}
		}
		for (size_t siz = 0; siz < sl; siz++)
		{
			str.pop_back();
		}
		return str;
	}
	std::string VToStr(std::vector<BOT_ARG>* vec_ = 0, c_char* sep = " ", size_t offs = 0, size_t lim = 0)
	{
		if (!vec_)
		{
			std::string str;
			return str;
		}

		std::string str;
		size_t sl = 0;

		if (!lim || lim > vec_->size())
		{
			lim = vec_->size();
		}

		if (sep)
		{
			sl = bot_cstrlen(sep);
		}

		for (size_t siz = offs; siz < lim; siz++)
		{
			if (vec_->at(siz).arg.length() + str.length() + sl < BOT_STRLEN_MAX)
			{
				str.append(vec_->at(siz).arg.c_str());

				if (sl)
				{
					str.append(sep);
				}
			}
			else
			{
				siz = vec_->size();
			}
		}
		for (size_t siz = 0; siz < sl; siz++)
		{
			str.pop_back();
		}
		return str;
	}

	std::string ITOA(sint i) { std::string str = ""; _char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%i", i); if (xc > -1) { str.append(ci); }	return str; }
	std::string LITOA(slint i) { std::string str = ""; _char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%li", i); if (xc > -1) { str.append(ci); } return str; }
	std::string LLITOA(sllint i) { std::string str = ""; _char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%lli", i); if (xc > -1) { str.append(ci); } return str; }
	std::string UTOA(uint i) { std::string str = ""; _char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%u", i); if (xc > -1) { str.append(ci); } return str; }
	std::string LUTOA(ulint i) { std::string str = ""; _char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%lu", i); if (xc > -1) { str.append(ci); } return str; }
	std::string LLUTOA(ullint i) { std::string str = ""; _char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%llu", i); if (xc > -1) { str.append(ci); } return str; }
	std::string DTOA(double i) { std::string str = ""; _char ci[64]{ 0 }; sint xc = bot_sprintf(ci, 64, "%f", i); if (xc < 64 && xc > -1) { str.append(ci); } return str; }
	std::string LDTOA(long double i) { std::string str = ""; _char ci[64]{ 0 }; sint xc = bot_sprintf(ci, 64, "%f", i); if (xc < 64 && xc > -1) { str.append(ci); } return str; }

	sint FindInStr(u_char f, const u_char* str = 0, sint at = -1, sint lim = -1, bool fwd = true)
	{
		if (!str)
		{
			return -1;
		}

		sint flen = 1;
		sint slen = (sint)sizeof(*str);

		if (!slen)
		{
			return -1;
		}
		if (lim < 0)
		{
			lim = 0;

			if (fwd)
			{
				lim = slen - 1;
			}
		}
		if (flen > slen || (fwd && at > lim) || (!fwd && at < lim))
		{
			return -1;
		}
		if (fwd)
		{
			while (at < slen && at <= lim)
			{
				sint siz = 0;

				while (siz < flen && at + siz <= lim)
				{
					if (f != str[at + siz])
					{
						siz = flen;
					}
					siz++;
				}
				if (siz == flen)
				{
					return at;
				}
				at++;

				if (at + flen > lim)
				{
					at += flen;
				}
			}
		}
		else
		{
			while (at > -1 && at >= lim)
			{
				sint siz = 0;

				while (siz < flen && at + siz <= lim)
				{
					if (f != str[at + siz])
					{
						siz = flen;
					}
					siz++;
				}

				if (siz == flen)
				{
					return at;
				}
				at--;

				if (at - flen < 0)
				{
					at -= flen;
				}
			}
		}
		return -1;
	}
	sint FindInStr(u_char f, u_char* str = 0, sint at = -1, sint lim = -1, bool fwd = true)
	{
		if (!str)
		{
			return -1;
		}

		sint flen = 1;
		sint slen = (sint)sizeof(*str);

		if (!slen)
		{
			return -1;
		}
		if (lim < 0)
		{
			lim = 0;

			if (fwd)
			{
				lim = slen - 1;
			}
		}
		if (flen > slen || (fwd && at > lim) || (!fwd && at < lim))
		{
			return -1;
		}
		if (fwd)
		{
			while (at < slen && at <= lim)
			{
				sint siz = 0;

				while (siz < flen && at + siz <= lim)
				{
					if (f != str[at + siz])
					{
						siz = flen;
					}
					siz++;
				}
				if (siz == flen)
				{
					return at;
				}
				at++;

				if (at + flen > lim)
				{
					at += flen;
				}
			}
		}
		else
		{
			while (at > -1 && at >= lim)
			{
				sint siz = 0;

				while (siz < flen && at + siz <= lim)
				{
					if (f != str[at + siz])
					{
						siz = flen;
					}
					siz++;
				}

				if (siz == flen)
				{
					return at;
				}
				at--;

				if (at - flen < 0)
				{
					at -= flen;
				}
			}
		}
		return -1;
	}
	sint FindInStr(_char f, c_char* str = 0, sint at = -1, sint lim = -1, bool fwd = true)
	{
		if (!str)
		{
			return -1;
		}

		sint flen = 1;
		sint slen = (sint)strlen(str);

		if (!slen)
		{
			return -1;
		}
		if (lim < 0)
		{
			lim = 0;

			if (fwd)
			{
				lim = slen - 1;
			}
		}
		if (flen > slen || (fwd && at > lim) || (!fwd && at < lim))
		{
			return -1;
		}
		if (fwd)
		{
			while (at < (sint)strlen(str) && at <= lim)
			{
				if (f == str[at])
				{
					return at;
				}
				at++;
			}
		}
		else
		{
			while (at > -1 && at >= lim)
			{
				if (f == str[at])
				{
					return at;
				}
				at--;
			}
		}
		return -1;
	}
	sint FindInStr(c_char* f = 0, c_char* str = 0, sint at = -1, sint lim = -1, bool fwd = true)
	{
		if (!str || !f)
		{
			return -1;
		}

		sint flen = (sint)strlen(f);
		sint slen = (sint)strlen(str);

		if (!slen)
		{
			return -1;
		}

		if (lim < 0)
		{
			lim = 0;

			if (fwd)
			{
				lim = slen - 1;
			}
		}
		if (flen > slen || (fwd && at > lim) || (!fwd && at < lim))
		{
			return -1;
		}

		if (fwd)
		{
			while (at <= lim)
			{
				sint nlen = 0;
				if (f[nlen] == str[at])
				{
					nlen++;
					at++;

					while (at <= lim && nlen < flen)
					{
						if (f[nlen] == str[at])
						{
							at++;
							nlen++;
						}
						else
						{
							at -= nlen;
							nlen = flen + 1;
						}
					}
					if (nlen == flen)
					{
						at -= flen;
						return at;
					}
				}
				at++;
			}
		}
		else
		{
			while (at >= lim)
			{
				sint nlen = flen - 1;
				if (f[nlen] == str[at])
				{
					at--;
					nlen--;
					while (at >= lim && nlen > -1)
					{
						if (f[nlen] == str[at])
						{
							at--;
							nlen--;
						}
						else
						{
							at += nlen;
							nlen = -2;
						}
					}
					if (nlen == -1)
					{
						return at;
					}
				}
				at--;
			}
		}
		return -1;
	}
	sint FindVInStr(std::vector<std::string>* strvec_ = 0, std::string* str_ = 0, sint* loc = 0, sint lim = -1, sint* ele = 0, sint ele_lim = -1, bool fwd = true, bool v_fwd = true)
	{
		if (!strvec_ || !str_ || !loc || !ele)
		{
			return -1;
		}
		if (lim < 0)
		{
			sint nlim = 0;

			if (fwd)
			{
				nlim = (sint)str_->length() - 1;
			}
			lim = nlim;
		}
		if (ele_lim < 0)
		{
			sint nlim = 0;

			if (v_fwd)
			{
				nlim = (sint)strvec_->size() - 1;
			}
			ele_lim = nlim;
		}

		if (*loc >= (sint)str_->length() || strvec_->empty() || str_->empty() || (fwd && *loc > lim) || (!fwd && *loc < lim) || (v_fwd && *ele > ele_lim) || (!v_fwd && *ele < ele_lim))
		{
			*loc = -1;
			return -1;
		}

		sint ret = -1;

		if (v_fwd)
		{
			for (sint x = 0; x <= ele_lim; x++)
			{
				sint fx = FindInStr(strvec_->at(x).c_str(), str_->c_str(), *loc, lim, fwd);

				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		else
		{
			for (sint x = (sint)strvec_->size() - 1; x >= ele_lim; x--)
			{
				sint fx = FindInStr(strvec_->at(x).c_str(), str_->c_str(), *loc, lim, fwd);
				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		*loc = ret;
		return ret;
	}
	sint FindVInStr(std::vector<_char>* cvec_ = 0, std::string* str_ = 0, sint* loc = 0, sint lim = -1, sint* ele = 0, sint ele_lim = -1, bool fwd = true, bool v_fwd = true)
	{
		if (!cvec_ || !str_ || !loc || !ele)
		{
			return -1;
		}

		if (lim < 0)
		{
			sint nlim = 0;

			if (fwd)
			{
				nlim = (sint)str_->length() - 1;
			}
			lim = nlim;
		}
		if (ele_lim < 0)
		{
			sint nlim = 0;

			if (v_fwd)
			{
				nlim = (sint)cvec_->size() - 1;
			}
			ele_lim = nlim;
		}

		if (*loc >= (sint)str_->length() || cvec_->empty() || str_->empty() || (fwd && *loc > lim) || (!fwd && *loc < lim) || (v_fwd && *ele > ele_lim) || (!v_fwd && *ele < ele_lim))
		{
			*loc = -1;
			return -1;
		}

		sint ret = -1;

		if (v_fwd)
		{
			for (sint x = 0; x <= ele_lim; x++)
			{
				sint fx = FindInStr(cvec_->at(x), str_->c_str(), *loc, lim, fwd);

				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		else
		{
			for (sint x = (sint)cvec_->size() - 1; x >= ele_lim; x--)
			{
				sint fx = FindInStr(cvec_->at(x), str_->c_str(), *loc, lim, fwd);
				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		*loc = ret;
		return ret;
	}
	sint FindVInStr(std::vector<c_char*>* cvec_ = 0, c_char* str_ = 0, sint* loc = 0, sint lim = -1, sint* ele = 0, sint ele_lim = -1, bool fwd = true, bool v_fwd = true)
	{
		if (!cvec_ || !str_ || !loc || !ele)
		{
			return -1;
		}

		sint slen = (sint)strlen(str_);

		if (lim < 0)
		{
			sint nlim = 0;

			if (fwd)
			{
				nlim = slen - 1;
			}
			lim = nlim;
		}
		if (ele_lim < 0)
		{
			sint nlim = 0;

			if (v_fwd)
			{
				nlim = (sint)cvec_->size() - 1;
			}
			ele_lim = nlim;
		}

		if (*loc >= slen || cvec_->empty() || !slen || (fwd && *loc > lim) || (!fwd && *loc < lim) || (v_fwd && *ele > ele_lim) || (!v_fwd && *ele < ele_lim))
		{
			*loc = -1;
			return -1;
		}

		sint ret = -1;

		if (v_fwd)
		{
			for (sint x = 0; x <= ele_lim; x++)
			{
				sint fx = FindInStr(cvec_->at(x), str_, *loc, lim, fwd);

				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		else
		{
			for (sint x = (sint)cvec_->size() - 1; x >= ele_lim; x--)
			{
				sint fx = FindInStr(cvec_->at(x), str_, *loc, lim, fwd);

				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		*loc = ret;
		return ret;
	}
	sint FindVInStr(std::vector<_char>*cvec_ = 0, c_char* str_ = 0, sint* loc = 0, sint lim = -1, sint* ele = 0, sint ele_lim = -1, bool fwd = true, bool v_fwd = true)
	{
		if (!cvec_ || !str_ || !loc || !ele)
		{
			return -1;
		}

		sint slen = (sint)strlen(str_);

		if (lim < 0)
		{
			sint nlim = 0;

			if (fwd)
			{
				nlim = slen - 1;
			}
			lim = nlim;
		}
		if (ele_lim < 0)
		{
			sint nlim = 0;

			if (v_fwd)
			{
				nlim = (sint)cvec_->size() - 1;
			}
			ele_lim = nlim;
		}

		if (*loc >= slen || cvec_->empty() || !slen || (fwd && *loc > lim) || (!fwd && *loc < lim) || (v_fwd && *ele > ele_lim) || (!v_fwd && *ele < ele_lim))
		{
			*loc = -1;
			return -1;
		}

		sint ret = -1;

		if (v_fwd)
		{
			for (sint x = 0; x <= ele_lim; x++)
			{
				sint fx = FindInStr(cvec_->at(x), str_, *loc, lim, fwd);

				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		else
		{
			for (sint x = (sint)cvec_->size() - 1; x >= ele_lim; x--)
			{
				sint fx = FindInStr(cvec_->at(x), str_, *loc, lim, fwd);
				if (fwd)
				{
					if (fx > -1 && (fx < ret || ret == -1))
					{
						*ele = x;
						ret = fx;
					}
				}
				else
				{
					if (fx > ret)
					{
						*ele = x;
						ret = fx;
					}
				}
			}
		}
		*loc = ret;
		return ret;
	}
	sint SeparateStrByStr(std::string *str_ = 0, std::string *sstr_ = 0, std::vector<std::string> *rvec_ = 0)
	{
		if (!str_ || !sstr_ || !rvec_)
		{
			return -1;
		}

		size_t x = 0;

		for (size_t sx = 0; sx < str_->length(); sx++)
		{
			if (sx + sstr_->length() < str_->length())
			{
				if (!strcmp(sstr_->c_str(), str_->substr(sx, sstr_->length()).c_str()))
				{
					if (x < sx)
					{
						rvec_->push_back(str_->substr(x, sx - x));
						x = sx + 1;
					}
					sx += sstr_->length() - 1;
				}
			}
		}
		if (rvec_->empty())
		{
			rvec_->push_back(*str_);
		}
		return 0;
	}
	sint SeparateStrByCChar(c_char *str_ = "", c_char *sstr_ = "", std::vector<std::string> *rvec_ = 0)
	{
		if (!str_ || !rvec_ || !sstr_)
		{
			return -1;
		}

		size_t slen = strlen(str_);

		if (!strlen(str_))
		{
			return -1;
		}

		size_t sslen = strlen(sstr_);

		if (!strlen(sstr_))
		{
			std::string nstr;
			nstr.append(str_);
			rvec_->push_back(str_);
			return 0;
		}

		if (slen)
		{
			size_t x = 0;

			for (size_t sx = 0; sx < slen; sx++)
			{
				if (sx + sslen <= slen)
				{
					size_t xs = 0;

					while (xs < sslen && sx < slen)
					{
						if (memcmp((void*)&str_[xs + sx], (void*)&sstr_[xs], 1))
						{
							xs = sslen;
						}
						xs++;
					}

					if (xs == sslen)
					{
						if (x < sx)
						{
							std::string tov;

							while (x < sx)
							{
								tov.push_back(str_[x]);
								x++;
							}
							x = sx + 1;
							rvec_->push_back(tov);
						}
					}
				}
			}
			if (x < slen - 1)
			{
				std::string tov;

				while (x < slen)
				{
					tov.push_back(str_[x]);
					x++;
				}
				rvec_->push_back(tov);
			}
		}

		if (rvec_->empty())
		{
			std::string nstr;
			nstr.append(str_);
			rvec_->push_back(nstr);
		}
		return 0;
	}
	sint SeparateStrByChar(c_char *str_ = "", _char chr = ' ', std::vector<std::string> *rvec_ = 0)
	{
		if (!str_ || !rvec_)
		{
			return -1;
		}

		if (!strlen(str_))
		{
			return -1;
		}

		uint x = 0;

		for (uint sx = 0; sx < strlen(str_); sx++)
		{
			if (!memcmp((void*)&chr, (void*)&str_[sx], 1))
			{
				if (x < sx)
				{
					std::string pstr;

					while (x < sx)
					{
						pstr.push_back(str_[x]);
						x++;
					}
					rvec_->push_back(pstr);
					x = sx + 1;
				}
			}
			if (sx == strlen(str_) - 1 && x < strlen(str_))
			{
				std::string pstr;

				while (x < strlen(str_))
				{
					pstr.push_back(str_[x]);
					x++;
				}
				rvec_->push_back(pstr);
			}
		}

		if (rvec_->empty())
		{
			std::string nstr;
			nstr.append(str_);
			rvec_->push_back(nstr);
		}
		return 0;
	}

	void SetTClr(std::chrono::steady_clock::time_point* nt = 0) { if (!nt) { vtclr = std::chrono::steady_clock::now(); } else { vtclr = *nt; } }

private:

	std::chrono::steady_clock::time_point vtclr;
};

// VTOOL

enum vtool_valt
{
	VTV_BOOL = 0,
	VTV_SINT = 1,
	VTV_SLINT = 2,
	VTV_SLLINT = 3,
	VTV_UINT = 4,
	VTV_ULINT = 5,
	VTV_ULLINT = 6,
	VTV_CHAR = 7,
	VTV_UCAR = 8,
	VTV_CCAR = 9,
	VTV_CARP = 10,
	VTV_UCARP = 11,
	VTV_SINTP = 12,
	VTV_SLINTP = 13,
	VTV_SLLINTP = 14,
	VTV_UINTP = 15,
	VTV_ULINTP = 16,
	VTV_ULLINTP = 17,
	VTV_STR = 17,
	VTV_MTX = 24,
	VTV_HMTX = 25,
	VTV_LRQ = 26,
	VTV_PORT = 27,
	VTV_PLUG = 28,
	VTV_FLD = 29,
	VTV_DRV = 30,
	VTV_DIR = 31,
	VTV_SCR = 32,
	VTV_STMT = 33,
	VTV_DB = 34,
	VTV_USR = 35,
	VTV_CMD = 36,
	VTV_LOG = 37,
	VTV_MICS = 38,
	VTV_MACS = 39,
	VTV_FIL = 40,
	VTV_THR = 41,
	VTV_ARG = 42,
	VTV_VBOOL = 1000,
	VTV_VSINT = 1001,
	VTV_VSLINT = 1002,
	VTV_VSLLINT = 1003,
	VTV_VUINT = 1004,
	VTV_VULINT = 1005,
	VTV_VULLINT = 1006,
	VTV_VCHAR = 1007,
	VTV_VUCAR = 1008,
	VTV_VCCAR = 1009,
	VTV_VCARP = 1010,
	VTV_VUCARP = 1011,
	VTV_VSINTP = 1012,
	VTV_VSLINTP = 1013,
	VTV_VSLLINTP = 1014,
	VTV_VUINTP = 1015,
	VTV_VULINTP = 1016,
	VTV_VULLINTP = 1017,
	VTV_VSTR = 1017,
	VTV_VMTX = 1024,
	VTV_VHMTX = 1025,
	VTV_VLRQ = 1026,
	VTV_VPORT = 1027,
	VTV_VPLUG = 1028,
	VTV_VFLD = 1029,
	VTV_VDRV = 1030,
	VTV_VDIR = 1031,
	VTV_VSCR = 1032,
	VTV_VSTMT = 1033,
	VTV_VDB = 1034,
	VTV_VUSR = 1035,
	VTV_VCMD = 1036,
	VTV_VLOG = 1037,
	VTV_VMICS = 1038,
	VTV_VMACS = 1039,
	VTV_VFIL = 1040,
	VTV_VTHR = 1041,
	VTV_VARG = 1042,
	VTV_MAX = 1200
};

class VTool
{
public:

	VTool(std::chrono::steady_clock::time_point* nt = 0, STool* nstool = 0) { SetTClr(nt); stool = nstool; }

	sint vsymcmp(std::vector<MICSYM>* a = 0, std::vector<MICSYM>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (memcmp(&a->at(siz).sym, &b->at(siz).sym, sizeof(a->at(siz).sym)))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vuchrcmp(std::vector<u_char>* a = 0, std::vector<u_char>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (memcmp(&a->at(siz), &b->at(siz), 1))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vchrcmp(std::vector<_char>* a = 0, std::vector<_char>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (memcmp(&a->at(siz), &b->at(siz), 1))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vccpcmp(std::vector<c_char*>* a = 0, std::vector<c_char*>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (strcmp(a->at(siz), b->at(siz)))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vuicmp(std::vector<uint>* a = 0, std::vector<uint>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (a->at(siz) != b->at(siz))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vsicmp(std::vector<ulint>* a = 0, std::vector<ulint>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (a->at(siz) != b->at(siz))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vsicmp(std::vector<ullint>* a = 0, std::vector<ullint>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (a->at(siz) != b->at(siz))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vsicmp(std::vector<sint>* a = 0, std::vector<sint>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (a->at(siz) != b->at(siz))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vslicmp(std::vector<slint>* a = 0, std::vector<slint>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (a->at(siz) != b->at(siz))
			{
				return -1;
			}
		}
		return 0;
	}
	sint vsllicmp(std::vector<sllint>* a = 0, std::vector<slint>* b = 0)
	{
		if (!a || !b)
		{
			return -1;
		}
		size_t asiz = a->size();

		if (!asiz || asiz != b->size() || asiz >= BOT_STRLEN_MAX)
		{
			return -1;
		}
		for (size_t siz = 0; siz < asiz; siz++)
		{
			if (a->at(siz) != b->at(siz))
			{
				return -1;
			}
		}
		return 0;
	}
	sint comp_t_struct(BOT_STMT* valI = 0, BOT_STMT* valII = 0)
	{
		if (!valI || !valII)
		{
			return -1;
		}

		if ((valI->maint != valII->maint) || (valI->ic_type != valII->ic_type) || (valI->it_type != valII->it_type) || (valI->spec != valII->spec) || (valI->act != valII->act) || (valI->ifex != valII->ifex) || (valI->targ != valII->targ))
		{
			return -1;
		}
		
		if (valI->rblk && valII->rblk)
		{
			if (memcmp(valI->rblk, valII->rblk, sizeof(valI->rblk)))
			{
				return -1;
			}
		}
		else if (valI->rblk && !valII->rblk)
		{
			return -1;
		}
		else if (!valI->rblk && valII->rblk)
		{
			return -1;
		}
		else {}

		if (strcmp(valI->dbname.c_str(), valII->dbname.c_str())) { return -1; }

		size_t Isiz = valI->cont.length();
		size_t IIsiz = valII->cont.length();

		if (Isiz != IIsiz)
		{
			return -1;
		}

		if (strcmp(valI->cont.c_str(), valII->cont.c_str()))
		{
			return -1;
		}

		if (valI->opts[0] != valII->opts[0] || valI->opts[1] != valII->opts[1])
		{
			return -1;
		}
		Isiz = valI->fcols.size();
		IIsiz = valII->fcols.size();

		if (Isiz != IIsiz)
		{
			return -1;
		}

		for (Isiz = 0; Isiz < valI->fcols.size(); Isiz++)
		{
			if (strcmp(valI->fcols[Isiz].c_str(), valII->fcols[Isiz].c_str()))
			{
				Isiz = valI->fcols.size() + 1;
			}
		}

		if (Isiz != valI->fcols.size()) { return -1; }

		Isiz = valI->cols.size();
		IIsiz = valII->cols.size();

		if (Isiz != IIsiz || valI->vals.size() != valII->vals.size())
		{
			return -1;
		}

		sint iga = -1;
		sint igb = -1;
		sint igc = -1;
		for (Isiz = 0; Isiz < valI->cols.size(); Isiz++)
		{
			if (!strcmp(valI->cols[Isiz].c_str(), "LAST_MODIFIED"))
			{
				iga = (sint)Isiz;
			}
			else if (!strcmp(valI->cols[Isiz].c_str(), "LAST_MODIFIED_NS"))
			{
				igb = (sint)Isiz;
			}
			else if (!strcmp(valI->cols[Isiz].c_str(), "LAST_MAINTAINED"))
			{
				iga = (sint)Isiz;
			}
			else if (!strcmp(valI->cols[Isiz].c_str(), "LAST_MAINTAINED_NS"))
			{
				igb = (sint)Isiz;
			}
			else if (!strcmp(valI->cols[Isiz].c_str(), BOT_INCR_STR))
			{
				igc = (sint)Isiz;
			}
			else
			{
				if (strcmp(valI->cols[Isiz].c_str(), valII->cols[Isiz].c_str()))
				{
					Isiz = valI->cols.size();
				}
			}
		}

		if (Isiz != valI->cols.size()) { return -1; }

		Isiz = valI->vals.size();
		IIsiz = valII->vals.size();

		if (Isiz != IIsiz)
		{
			return -1;
		}

		for (Isiz = 0; Isiz < IIsiz; Isiz++) { if ((sint)Isiz != iga && (sint)Isiz != igb && Isiz != igc) { if (strcmp(valI->vals[Isiz].c_str(), valII->vals[Isiz].c_str())) { Isiz = valI->vals.size(); } } }

		if (Isiz != valI->vals.size()) { return -1; }

		if (!valI->stmt.empty() && !valII->stmt.empty())
		{
			if (strcmp(valI->stmt.c_str(), valII->stmt.c_str()))
			{
				return -1;
			}
		}

		Isiz = valI->conds.size();
		IIsiz = valII->conds.size();

		if (Isiz != IIsiz)
		{
			return -1;
		}

		for (Isiz = 0; Isiz < IIsiz; Isiz++)
		{
			if (strcmp(valI->conds[Isiz].c_str(), valII->conds[Isiz].c_str()))
			{
				return -1;
			}
		}

		return 0;
	}
	sint CombV(void* vec_ = 0, sint ovalt = -1, ...)
	{
		if (!vec_ || ovalt < 0)
		{
			return -1;
		}

		va_list args;
		va_start(args, ovalt);

		switch (ovalt)
		{
		case VTV_VSINT:
		{
			std::vector<sint>* p_ = reinterpret_cast<std::vector<sint>*>(vec_);

			if (p_)
			{
				bool done = false;
				
				while (!done)
				{
					sint ivalt = va_arg(args, sint);

					switch (ivalt)
					{
					case VTV_SINT:
					{
						sint val = va_arg(args, sint);
						p_->push_back(val);
						break;
					}
					case VTV_SLINT:
					{
						slint val = va_arg(args, slint);
						p_->push_back((sint)val);
						break;
					}
					case VTV_SLLINT:
					{
						sllint val = va_arg(args, sllint);
						p_->push_back((sint)val);
						break;
					}
					case VTV_UINT:
					{
						uint val = va_arg(args, uint);
						p_->push_back((sint)val);
						break;
					}
					case VTV_ULINT:
					{
						ulint val = va_arg(args, ulint);
						p_->push_back((sint)val);
						break;
					}
					case VTV_ULLINT:
					{
						ullint val = va_arg(args, ullint);
						p_->push_back((sint)val);
						break;
					}
					case VTV_CHAR:
					{
						_char val = va_arg(args, _char);
						p_->push_back((sint)val);
						break;
					}
					case VTV_UCAR:
					{
						u_char val = va_arg(args, u_char);
						p_->push_back((sint)val);
						break;
					}
					case VTV_CCAR:
					{
						c_char* np = va_arg(args, c_char*);

						if (np)
						{
							p_->push_back((sint)atoi(np));
						}
						break;
					}
					case VTV_STR:
					{
						std::string* np = va_arg(args, std::string*);

						if (np)
						{
							p_->push_back((sint)atoi(np->c_str()));
						}
						break;
					}
					case VTV_ARG:
					{
						BOT_ARG* np = va_arg(args, BOT_ARG*);

						if (np)
						{
							p_->push_back((sint)atoi(np->arg.c_str()));
						}
						break;
					}
					case VTV_VSINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sint>* nvec = reinterpret_cast<std::vector<sint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VSLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<slint>* nvec = reinterpret_cast<std::vector<slint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VSLLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sllint>* nvec = reinterpret_cast<std::vector<sllint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VUINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<uint>* nvec = reinterpret_cast<std::vector<uint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VULINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ulint>* nvec = reinterpret_cast<std::vector<ulint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VULLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ullint>* nvec = reinterpret_cast<std::vector<ullint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VCHAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<_char>* nvec = reinterpret_cast<std::vector<_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VUCAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<u_char>* nvec = reinterpret_cast<std::vector<u_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VCCAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<c_char*>* nvec = reinterpret_cast<std::vector<c_char*>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)atoi(nvec->at(x)));
								}
							}
						}
						break;
					}
					case VTV_VSTR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<std::string>* nvec = reinterpret_cast<std::vector<std::string>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)atoi(nvec->at(x).c_str()));
								}
							}
						}
						break;
					}
					case VTV_VARG:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<BOT_ARG>* nvec = reinterpret_cast<std::vector<BOT_ARG>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((sint)atoi(nvec->at(x).arg.c_str()));
								}
							}
						}
						break;
					}
					case VTV_MAX:
					{
						done = true;
						break;
					}
					default:
					{
						done = true;
						break;
					}
					}
				}
			}
			break;
		}
		case VTV_VUINT:
		{
			std::vector<uint>* p_ = reinterpret_cast<std::vector<uint>*>(vec_);

			if (p_)
			{

			}
			break;
		}
		case VTV_VCHAR:
		{
			std::vector<_char>* p_ = reinterpret_cast<std::vector<_char>*>(vec_);

			if (p_)
			{
				bool done = false;

				while (!done)
				{
					sint ivalt = va_arg(args, sint);

					switch (ivalt)
					{
					case VTV_SINT:
					{
						sint val = va_arg(args, sint);
						p_->push_back(val);
						break;
					}
					case VTV_SLINT:
					{
						slint val = va_arg(args, slint);
						p_->push_back((_char)val);
						break;
					}
					case VTV_SLLINT:
					{
						sllint val = va_arg(args, sllint);
						p_->push_back((_char)val);
						break;
					}
					case VTV_UINT:
					{
						uint val = va_arg(args, uint);
						p_->push_back((_char)val);
						break;
					}
					case VTV_ULINT:
					{
						ulint val = va_arg(args, ulint);
						p_->push_back((_char)val);
						break;
					}
					case VTV_ULLINT:
					{
						ullint val = va_arg(args, ullint);
						p_->push_back((_char)val);
						break;
					}
					case VTV_CHAR:
					{
						_char val = va_arg(args, _char);
						p_->push_back((_char)val);
						break;
					}
					case VTV_UCAR:
					{
						u_char val = va_arg(args, u_char);
						p_->push_back((_char)val);
						break;
					}
					case VTV_CCAR:
					{
						c_char* np = va_arg(args, c_char*);

						if (np)
						{
							size_t ln = bot_cstrlen(np);
							for (size_t x = 0; x < ln; x++)
							{
								p_->push_back(np[x]);
							}
						}
						break;
					}
					case VTV_STR:
					{
						std::string* np = va_arg(args, std::string*);

						if (np)
						{
							for (size_t x = 0; x < np->length(); x++)
							{
								p_->push_back(np->at(x));
							}
						}
						break;
					}
					case VTV_ARG:
					{
						BOT_ARG* np = va_arg(args, BOT_ARG*);

						if (np)
						{
							for (size_t x = 0; x < np->arg.length(); x++)
							{
								p_->push_back(np->arg[x]);
							}
						}
						break;
					}
					case VTV_VSINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sint>* nvec = reinterpret_cast<std::vector<sint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VSLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<slint>* nvec = reinterpret_cast<std::vector<slint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((_char)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VSLLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sllint>* nvec = reinterpret_cast<std::vector<sllint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((_char)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VUINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<uint>* nvec = reinterpret_cast<std::vector<uint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VULINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ulint>* nvec = reinterpret_cast<std::vector<ulint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((_char)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VULLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ullint>* nvec = reinterpret_cast<std::vector<ullint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back((_char)nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VCHAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<_char>* nvec = reinterpret_cast<std::vector<_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VUCAR:
					{
						sllint np = va_arg(args, sllint);

						if (np)
						{
							std::vector<u_char>* nvec = reinterpret_cast<std::vector<u_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VCCAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<c_char*>* nvec = reinterpret_cast<std::vector<c_char*>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									size_t ln = bot_cstrlen(nvec->at(x));

									for (size_t y = 0; y < ln; y++)
									{
										p_->push_back(nvec->at(x)[y]);
									}
								}
							}
						}
						break;
					}
					case VTV_VSTR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<std::string>* nvec = reinterpret_cast<std::vector<std::string>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									for (size_t y = 0; y < nvec->at(x).length(); y++)
									{
										p_->push_back(nvec->at(x)[y]);
									}
								}
							}
						}
						break;
					}
					case VTV_VARG:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<BOT_ARG>* nvec = reinterpret_cast<std::vector<BOT_ARG>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									for (size_t y = 0; y < nvec->at(x).arg.length(); y++)
									{
										p_->push_back(nvec->at(x).arg[y]);
									}
								}
							}
						}
						break;
					}
					case VTV_MAX:
					{
						done = true;
						break;
					}
					default:
					{
						done = true;
						break;
					}
					}
				}
			}
			break;
		}
		case VTV_VSTR:
		{
			std::vector<std::string>* p_ = reinterpret_cast<std::vector<std::string>*>(vec_);

			if (p_)
			{
				bool done = false;

				while (!done)
				{
					sint ivalt = va_arg(args, sint);

					switch (ivalt)
					{
					case VTV_SINT:
					{
						sint val = va_arg(args, sint);
						std::string str(stool->ITOA(val).c_str());
						p_->push_back(str);
						break;
					}
					case VTV_SLINT:
					{
						slint val = va_arg(args, slint);
						std::string str(stool->LITOA(val).c_str());
						p_->push_back(str);
						break;
					}
					case VTV_SLLINT:
					{
						sllint val = va_arg(args, sllint);
						std::string str(stool->LLITOA(val).c_str());
						p_->push_back(str);
						break;
					}
					case VTV_UINT:
					{
						uint val = va_arg(args, uint);
						std::string str(stool->ITOA(val).c_str());
						p_->push_back(str);
						break;
					}
					case VTV_ULINT:
					{
						ulint val = va_arg(args, ulint);
						std::string str(stool->LITOA(val).c_str());
						p_->push_back(str);
						break;
					}
					case VTV_ULLINT:
					{
						ullint val = va_arg(args, ullint);
						std::string str(stool->LLITOA(val).c_str());
						p_->push_back(str);
						break;
					}
					case VTV_CHAR:
					{
						_char val = va_arg(args, _char);
						std::string str;
						str.push_back(val);
						p_->push_back(str);
						break;
					}
					case VTV_UCAR:
					{
						u_char val = va_arg(args, u_char);
						std::string str;
						str.push_back(val);
						p_->push_back(str);
						break;
					}
					case VTV_CCAR:
					{
						c_char* np = va_arg(args, c_char*);

						if (np)
						{
							std::string str(np);
							p_->push_back(str);
						}
						break;
					}
					case VTV_STR:
					{
						std::string* np = va_arg(args, std::string*);

						if (np)
						{
							p_->push_back(*np);
						}
						break;
					}
					case VTV_ARG:
					{
						BOT_ARG* np = va_arg(args, BOT_ARG*);

						if (np)
						{
							p_->push_back(np->arg);
						}
						break;
					}
					case VTV_VSINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sint>* nvec = reinterpret_cast<std::vector<sint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str(stool->ITOA(nvec->at(x)).c_str());
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VSLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<slint>* nvec = reinterpret_cast<std::vector<slint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str(stool->LITOA(nvec->at(x)).c_str());
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VSLLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sllint>* nvec = reinterpret_cast<std::vector<sllint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str(stool->LLITOA(nvec->at(x)).c_str());
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VUINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<uint>* nvec = reinterpret_cast<std::vector<uint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str(stool->ITOA(nvec->at(x)).c_str());
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VULINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ulint>* nvec = reinterpret_cast<std::vector<ulint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str(stool->LITOA(nvec->at(x)).c_str());
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VULLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ullint>* nvec = reinterpret_cast<std::vector<ullint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str(stool->LLITOA(nvec->at(x)).c_str());
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VCHAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<_char>* nvec = reinterpret_cast<std::vector<_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str;
									str.push_back(nvec->at(x));
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VUCAR:
					{
						sllint np = va_arg(args, sllint);

						if (np)
						{
							std::vector<u_char>* nvec = reinterpret_cast<std::vector<u_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string str;
									str.push_back(nvec->at(x));
									p_->push_back(str);
								}
							}
						}
						break;
					}
					case VTV_VCCAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<c_char*>* nvec = reinterpret_cast<std::vector<c_char*>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									std::string sval(nvec->at(x));
									p_->push_back(sval);
								}
							}
						}
						break;
					}
					case VTV_VSTR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<std::string>* nvec = reinterpret_cast<std::vector<std::string>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_VARG:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<BOT_ARG>* nvec = reinterpret_cast<std::vector<BOT_ARG>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x).arg);
								}
							}
						}
						break;
					}
					case VTV_MAX:
					{
						done = true;
						break;
					}
					default:
					{
						done = true;
						break;
					}
					}
				}
			}
			break;
		}
		case VTV_VARG:
		{
			std::vector<BOT_ARG>* p_ = reinterpret_cast<std::vector<BOT_ARG>*>(vec_);
			BOT_ARG a(-1);

			if (p_)
			{
				bool done = false;

				while (!done)
				{
					sint ivalt = va_arg(args, sint);

					switch (ivalt)
					{
					case VTV_SINT:
					{
						sint val = va_arg(args, sint);
						a.arg.append(stool->ITOA(val).c_str());
						p_->push_back(a);
						break;
					}
					case VTV_SLINT:
					{
						slint val = va_arg(args, slint);
						a.arg.append(stool->LITOA(val).c_str());
						p_->push_back(a);
						break;
					}
					case VTV_SLLINT:
					{
						sllint val = va_arg(args, sllint);
						a.arg.append(stool->LLITOA(val).c_str());
						p_->push_back(a);
						break;
					}
					case VTV_UINT:
					{
						uint val = va_arg(args, uint);
						a.arg.append(stool->ITOA(val).c_str());
						p_->push_back(a);
						break;
					}
					case VTV_ULINT:
					{
						ulint val = va_arg(args, ulint);
						a.arg.append(stool->LITOA(val).c_str());
						p_->push_back(a);
						break;
					}
					case VTV_ULLINT:
					{
						ullint val = va_arg(args, ullint);
						a.arg.append(stool->LLITOA(val).c_str());
						p_->push_back(a);
						break;
					}
					case VTV_CHAR:
					{
						_char val = va_arg(args, _char);
						a.arg.push_back(val);
						p_->push_back(a);
						break;
					}
					case VTV_UCAR:
					{
						u_char val = va_arg(args, u_char);
						a.arg.push_back(val);
						p_->push_back(a);
						break;
					}
					case VTV_CCAR:
					{
						c_char* np = va_arg(args, c_char*);

						if (np)
						{
							a.arg.append(np);
							p_->push_back(a);
						}
						break;
					}
					case VTV_STR:
					{
						std::string* np = va_arg(args, std::string*);

						if (np)
						{
							a.arg.append(np->c_str());
							p_->push_back(a);
						}
						break;
					}
					case VTV_ARG:
					{
						BOT_ARG* np = va_arg(args, BOT_ARG*);

						if (np)
						{
							p_->push_back(*np);
						}
						break;
					}
					case VTV_VSINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sint>* nvec = reinterpret_cast<std::vector<sint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(stool->ITOA(nvec->at(x)).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VSLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<slint>* nvec = reinterpret_cast<std::vector<slint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(stool->LITOA(nvec->at(x)).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VSLLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<sllint>* nvec = reinterpret_cast<std::vector<sllint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(stool->LLITOA(nvec->at(x)).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VUINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<uint>* nvec = reinterpret_cast<std::vector<uint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(stool->ITOA(nvec->at(x)).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VULINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ulint>* nvec = reinterpret_cast<std::vector<ulint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(stool->LITOA(nvec->at(x)).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VULLINT:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<ullint>* nvec = reinterpret_cast<std::vector<ullint>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(stool->LLITOA(nvec->at(x)).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VCHAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<_char>* nvec = reinterpret_cast<std::vector<_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.push_back(nvec->at(x));
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VUCAR:
					{
						sllint np = va_arg(args, sllint);

						if (np)
						{
							std::vector<u_char>* nvec = reinterpret_cast<std::vector<u_char>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.push_back(nvec->at(x));
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VCCAR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<c_char*>* nvec = reinterpret_cast<std::vector<c_char*>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(nvec->at(x));
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VSTR:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<std::string>* nvec = reinterpret_cast<std::vector<std::string>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									a.arg.append(nvec->at(x).c_str());
									p_->push_back(a);
									a.arg.clear();
								}
							}
						}
						break;
					}
					case VTV_VARG:
					{
						void* np = va_arg(args, void*);

						if (np)
						{
							std::vector<BOT_ARG>* nvec = reinterpret_cast<std::vector<BOT_ARG>*>(np);

							if (nvec)
							{
								for (size_t x = 0; x < nvec->size(); x++)
								{
									p_->push_back(nvec->at(x));
								}
							}
						}
						break;
					}
					case VTV_MAX:
					{
						done = true;
						break;
					}
					default:
					{
						done = true;
						break;
					}
					}
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}
		va_end(args);
		return 0;
	}
	sint SortV(void* vec_ = 0, sint valt = -1, sint mem = -1)
	{
		if (!vec_ || valt < 0)
		{
			return -1;
		}

		if (mem < 0)
		{
			mem = 0;
		}

		switch (valt)
		{
		case VTV_VCMD:
		{
			std::vector<BOTCOMMAND>* p_ = reinterpret_cast<std::vector<BOTCOMMAND>*>(vec_);

			if (p_)
			{
				botcmd_mems cmem = (botcmd_mems)mem;

				switch (cmem)
				{
				case BOT_CMD_CID:
				{
					for (size_t y = 0; y < p_->size(); y++)
					{
						for (size_t x = y + 1; x < p_->size(); x++)
						{
							if (p_->at(x).cmd_id < p_->at(y).cmd_id || p_->at(y).cmd_id < 0)
							{
								BOTCOMMAND xval;
								xval.Renew(&p_->at(y));
								p_->at(y).Renew(&p_->at(x));
								p_->at(x).Renew(&xval);
							}
						}
					}
					for (sint y = (sint)p_->size() - 1; y > -1; y--)
					{
						if (p_->at(y).cmd_id < 0)
						{
							p_->pop_back();
						}
						else
						{
							y = -1;
						}
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}
		return 0;
	}

	sint VIV(std::vector<carr_2> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_8> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_16> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_32> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_64> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_128> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_256> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_512> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_1024> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_2048> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4096> *vec_ = 0, _char val[] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_2> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_8> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_16> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_32> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_64> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_128> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_256> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_512> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_1024> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_2048> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4096> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_2> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_8> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_16> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_32> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_64> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_128> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_256> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_512> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_1024> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_2048> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4096> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::vector<u_char>> *vec_ = 0, std::vector<u_char>* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).size() == val->size()) { vn = vuchrcmp(&vec_->at(siz), val); if (!vn) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz).size() == val->size()) { vn = vuchrcmp(&vec_->at(siz), val); if (!vn) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector <std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<_char*> *vec_, _char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<_char> *vec_, _char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<_char> *vec_, _char val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, u_char val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_ = 0, u_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, const sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, const slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, const sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, const uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, const ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz],(void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, const ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<u_char> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val->c_str(); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val->c_str(); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<_char> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<void*> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32	
	sint VIV(std::vector<slint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint VIV(std::vector<slint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<slint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint VIV(std::vector<sllint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint VIV(std::vector<sllint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint VIV(std::vector<sllint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<sllint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint VIV(std::vector<uint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint VIV(std::vector<uint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint VIV(std::vector<uint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<uint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint VIV(std::vector<ulint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint VIV(std::vector<ulint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint VIV(std::vector<ulint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ulint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint VIV(std::vector<ullint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint VIV(std::vector<ullint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint VIV(std::vector<ullint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<ullint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint VIV(std::vector<float> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atof(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atof(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<float> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atof(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atof(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, u_char* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(*vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, void* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%i", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%li", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lli", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%u", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%llu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[32]{ 0 }; sint siz = bot_sprintf(mid, 32, "%0.3f", *val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<c_char*> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, u_char* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(*vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, void* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%i", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%li", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lli", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%u", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%llu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_ = 0, float* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; _char mid[32]{ 0 }; sint siz = bot_sprintf(mid, 32, "%0.3f", *val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<std::string> *vec_, std::string* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<MICSYM> *vec_ = 0, MICSYM* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).id > -1 && !memcmp((void*)&val->sym, (void*)&vec_->at(siz).sym, sizeof(u_char))) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).id > -1 && !memcmp((void*)&val->sym, (void*)&vec_->at(siz).sym, sizeof(u_char))) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<MACSYM> *vec_ = 0, MACSYM* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).id > -1 && !vsymcmp(&val->cons, &vec_->at(siz).cons)) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).id > -1 && !vsymcmp(&val->cons, &vec_->at(siz).cons)) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<DB_CONN*> *vec_ = 0, DB_CONN* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str()) && vec_->at(siz)->lid > -1 && (vec_->at(siz)->omode >= val->omode && val->omode > -1)) { vn = siz; val = vec_->at(siz); siz = vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str()) && vec_->at(siz)->lid > -1 && (vec_->at(siz)->omode >= val->omode && val->omode > -1)) { vn = siz; val = vec_->at(siz); siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid && vec_->at(siz).prt.lid == val->prt.lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid && vec_->at(siz).prt.lid == val->prt.lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val->name.c_str(),vec_->at(siz).name.c_str()) && !strcmp(val->path.c_str(), vec_->at(siz).path.c_str()) && !strcmp(val->type.c_str(), vec_->at(siz).type.c_str())) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val->name.c_str(), vec_->at(siz).name.c_str()) && !strcmp(val->path.c_str(), vec_->at(siz).path.c_str()) && !strcmp(val->type.c_str(), vec_->at(siz).type.c_str())) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<TINFO> *vec_, TINFO* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->w_mtx == vec_->at(siz).w_mtx) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->w_mtx == vec_->at(siz).w_mtx) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<HELD_MTX> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).w_mtx) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).w_mtx) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<lok_req> *vec_ = 0, lok_req* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->gmtx == vec_->at(siz).gmtx && val->ele == vec_->at(siz).ele && val->is_meta == vec_->at(siz).is_meta && val->fid == vec_->at(siz).fid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->gmtx == vec_->at(siz).gmtx && val->ele == vec_->at(siz).ele && val->is_meta == vec_->at(siz).is_meta && val->fid == vec_->at(siz).fid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE*> *vec_ = 0, BOT_FILE* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<HELD_MTX*> *vec_ = 0, HELD_MTX* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOTF_CONN*> *vec_ = 0, BOTF_CONN* val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->flid == val->flid) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->flid == val->flid) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid && vec_->at(siz).prt.lid == val->prt.lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid && vec_->at(siz).prt.lid == val->prt.lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val->name.c_str(), vec_->at(siz).name.c_str()) && !strcmp(val->path.c_str(), vec_->at(siz).path.c_str()) && !strcmp(val->type.c_str(), vec_->at(siz).type.c_str())) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val->name.c_str(), vec_->at(siz).name.c_str()) && !strcmp(val->path.c_str(), vec_->at(siz).path.c_str()) && !strcmp(val->type.c_str(), vec_->at(siz).type.c_str())) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_STMT> *vec_ = 0, BOT_STMT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !comp_t_struct(val, &vec_->at(siz))) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !comp_t_struct(val, &vec_->at(siz))) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FLD> *vec_ = 0, BOT_FLD* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).fid > -1 && !strcmp(val->fld.c_str(), vec_->at(siz).fld.c_str()) && val->bto == vec_->at(siz).bto && val->ord == vec_->at(siz).ord) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).fid > -1 && !strcmp(val->fld.c_str(), vec_->at(siz).fld.c_str()) && val->bto == vec_->at(siz).bto && val->ord == vec_->at(siz).ord) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_port> *vec_ = 0, bot_port* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && vec_->at(siz).portn == val->portn && vec_->at(siz).stype == val->stype) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && vec_->at(siz).portn == val->portn && vec_->at(siz).stype == val->stype) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_port> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid == val) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_plug> *vec_ = 0, bot_plug* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && vec_->at(siz).prt.portn == val->prt.portn && vec_->at(siz).prt.stype == val->prt.stype) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && vec_->at(siz).prt.portn == val->prt.portn && vec_->at(siz).prt.stype == val->prt.stype) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_plug> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid == val) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_proc> *vec_ = 0, bot_proc* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && vec_->at(siz).lid == val->lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && vec_->at(siz).lid == val->lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_proc> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid == val) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_proc_m> *vec_ = 0, bot_proc_m* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && vec_->at(siz).lid == val->lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && vec_->at(siz).lid == val->lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_proc_m> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid == val) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid == val) { vn = siz; siz = -1; } siz--; } } return vn; }

	sint VIV(std::vector<BOT_DB> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<DB_CONN*> *vec_ = 0, c_char* val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && !strcmp(val, vec_->at(siz)->name.c_str()) && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && !strcmp(val, vec_->at(siz)->name.c_str()) && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOTF_CONN> *vec_ = 0, sint val = -1, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).flid) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).flid) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOTF_CONN*> *vec_ = 0, sint val = -1, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && val == vec_->at(siz)->flid) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && val == vec_->at(siz)->flid) { vn = siz; siz = -1; } } siz--; } } return vn; }
	//sint VIV(std::vector<DB_CONN*> *vec_ = 0, sint val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->lid == val && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->lid == val && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_CLIENT> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<TINFO> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_DB_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_CLIENT_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<TINFO_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FLD> *vec_ = 0, c_char* val = 0, sllint bto = -1, sllint ord = -1, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).fid > -1 && !strcmp(val, vec_->at(siz).fld.c_str()) && bto == vec_->at(siz).bto && ord == vec_->at(siz).ord) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).fid > -1 && !strcmp(val, vec_->at(siz).fld.c_str()) && bto == vec_->at(siz).bto && ord == vec_->at(siz).ord) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_DB*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_CLIENT*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->logtitle.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint VIV(std::vector<TINFO*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->thread_name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }

	sint VIA(sint arr[] = 0, sint asiz = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz] == val) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz] == val) { vn = siz; siz = -1; }siz--; } } return vn; }
	sint VIA(uint arr[] = 0, sint asiz = 0, uint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz] == val) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz] == val) { vn = siz; siz = -1; }siz--; } } return vn; }
	sint VIA(slint arr[] = 0, sint asiz = 0, slint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz] == val) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz] == val) { vn = siz; siz = -1; }siz--; } } return vn; }
	sint VIA(ulint arr[] = 0, sint asiz = 0, ulint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz] == val) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz] == val) { vn = siz; siz = -1; }siz--; } } return vn; }
	sint VIA(sllint arr[] = 0, sint asiz = 0, sllint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz] == val) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz] == val) { vn = siz; siz = -1; }siz--; } } return vn; }
	sint VIA(ullint arr[] = 0, sint asiz = 0, ullint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz] == val) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz] == val) { vn = siz; siz = -1; }siz--; } } return vn; }
	sint VIA(BOTF_CONN arr[] = 0, sint asiz = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0 || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIA(DB_CONN arr[] = 0, sint asiz = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!arr || !val || !asiz) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (asiz + e_from); } if (forw) { while (siz < asiz) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = asiz; } siz++; } } else { while (siz > -1) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }

	sint UEE(std::vector<carr_2> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_4> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_8> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_16> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_32> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_64> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_128> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_256> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_512> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_1024> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_2048> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<carr_4096> *vec_ = 0, _char val[] = 0) { if (!vec_ || !val) { return -1; } for (size_t x = 0; x < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { bot_sprintf(vec_->at(x).carr, vec_->at(x).siz, "%s", val); return (sint)x; } } return -1; }
	sint UEE(std::vector<std::vector<u_char>> *vec_ = 0, std::vector<u_char>* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { for (size_t nsiz = 0; nsiz < val->size(); nsiz++) { vec_->at(siz).push_back(val->at(nsiz)); } vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == vtclr) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<_char*> *vec_ = 0, _char* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<_char> *vec_ = 0, _char* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<_char> *vec_ = 0, _char val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<u_char> *vec_ = 0, u_char* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<u_char> *vec_, u_char val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { memcpy((void*)&vec_->at(siz), (void*)&val, sizeof(vec_->at(siz))); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<void*> *vec_ = 0, void* val = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<sint> *vec_, sint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<slint> *vec_, slint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT32_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<sllint> *vec_, sllint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT64_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<uint> *vec_, uint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<ulint> *vec_, ulint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT32_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<ullint> *vec_, ullint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT64_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<float> *vec_ = 0, float* fp = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == 0) { vec_->at(siz) = *fp; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<c_char*> *vec_ = 0, void* vp = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz), " ") || !strlen(vec_->at(siz))) { vec_->at(siz) = 0; c_char* mid = reinterpret_cast<c_char*>(vp); vec_->at(siz) = mid; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<std::string> *vec_ = 0, std::string* sp = 0) { if (!vec_ || !sp) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { vec_->at(siz).clear(); vec_->at(siz).append(*sp); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<std::string> *vec_ = 0, c_char* sp = 0) { if (!vec_ || !sp) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { vec_->at(siz).clear(); vec_->at(siz).append(sp); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<MICSYM> *vec_ = 0, MICSYM* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).id < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->id = vn; vec_->at(siz).id = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<MACSYM> *vec_ = 0, MACSYM* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).id < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->id = vn; vec_->at(siz).id = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<DB_CONN*> *vec_ = 0, DB_CONN* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == -1) { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } } else { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz).Renew(val); vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<TINFO> *vec_ = 0, TINFO* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0) { if (!val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<lok_req> *vec_ = 0, lok_req* val = 0) { if (!val || !vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_FILE*> *vec_, BOT_FILE* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<HELD_MTX*> *vec_ = 0, HELD_MTX* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOTF_CONN*> *vec_ = 0, BOTF_CONN* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == -1) { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } } else { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_STMT> *vec_ = 0, BOT_STMT* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<BOT_FLD> *vec_ = 0, BOT_FLD* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).fid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->fid = vn; vec_->at(siz).fid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<bot_port> *vec_ = 0, bot_port* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz).Renew(val); vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<bot_plug> *vec_ = 0, bot_plug* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz).Renew(val); vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<bot_proc> *vec_ = 0, bot_proc* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz).Renew(val); vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<bot_proc_m> *vec_ = 0, bot_proc_m* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz).Renew(val); vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(sint arr[] = 0, sint asiz = 0, sint val = -1) { if (!arr || !asiz) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] < 0) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(uint arr[] = 0, sint asiz = 0, uint val = (uint)UINT_MAX) { if (!arr || asiz == UINT_MAX) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] == (uint)UINT_MAX) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(slint arr[] = 0, sint asiz = 0, slint val = -1) { if (!arr || !asiz) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] < 0) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(ulint arr[] = 0, sint asiz = 0, ulint val = (ulint)UINT32_MAX) { if (!arr || asiz == (ulint)UINT32_MAX) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] == (ulint)UINT32_MAX) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(sllint arr[] = 0, sint asiz = 0, sllint val = -1) { if (!arr || !asiz) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] < 0) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(ullint arr[] = 0, sint asiz = 0, ullint val = (ullint)UINT64_MAX) { if (!arr || asiz == (ullint)UINT64_MAX) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] == (ullint)UINT64_MAX) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	
	sint AVTV(std::vector<carr_2> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_4> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_8> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_8 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_16> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_16 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_32> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_32 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_64> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_64 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_128> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_128 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_256> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_256 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_512> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_512 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_1024> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_1024 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_2048> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2048 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_4096> *vec_ = 0, _char val[] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4096 ncar; bot_sprintf(ncar.carr, ncar.siz, "%s", val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<std::vector<u_char>>* vec_ = 0, std::vector<u_char>* val = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<std::chrono::steady_clock::time_point> *vec_, std::chrono::steady_clock::time_point* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<_char*> *vec_, _char* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<_char> *vec_, _char* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<_char> *vec_, _char val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, &val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, &val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<u_char> *vec_, u_char* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<u_char> *vec_, u_char val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, &val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, &val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<void*> *vec_, void* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<sint> *vec_, sint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<slint> *vec_, slint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<sllint> *vec_, sllint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<uint> *vec_, uint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<ulint> *vec_, ulint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<ullint> *vec_, ullint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AVTV(std::vector<float> *vec_, float* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<c_char*> *vec_, void* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(reinterpret_cast<c_char*>(val)); return viv; }
	sint AVTV(std::vector<std::string> *vec_, std::string* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<std::string> *vec_, c_char* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } std::string nval; nval.append(val); vec_->push_back(nval); return viv; }
	sint AVTV(std::vector<MICSYM> *vec_, MICSYM* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->id = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<MACSYM> *vec_, MACSYM* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->id = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_DB> *vec_, BOT_DB* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<DB_CONN*> *vec_, DB_CONN* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<BOTF_CONN*> *vec_, BOTF_CONN* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOT_FS_LIM || viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<BOT_CLIENT> *vec_, BOT_CLIENT* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_LOGDET> *vec_, BOT_LOGDET* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_FILE> *vec_, BOT_FILE* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<TINFO> *vec_, TINFO* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<HELD_MTX> *vec_, HELD_MTX* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<lok_req> *vec_, lok_req* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_DB*> *vec_, BOT_DB* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<BOT_CLIENT*> *vec_, BOT_CLIENT* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<BOT_LOGDET*> *vec_, BOT_LOGDET* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<BOT_FILE*> *vec_, BOT_FILE* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<TINFO*> *vec_, TINFO* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<HELD_MTX*> *vec_, HELD_MTX* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AVTV(std::vector<BOT_DB_M> *vec_, BOT_DB_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_CLIENT_M> *vec_, BOT_CLIENT_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_LOGDET_M> *vec_, BOT_LOGDET_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_FILE_M> *vec_, BOT_FILE_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<TINFO_M> *vec_, TINFO_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_STMT> *vec_, BOT_STMT* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<BOT_FLD> *vec_, BOT_FLD* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->fid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<bot_port> *vec_, bot_port* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<bot_plug> *vec_, bot_plug* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<bot_proc> *vec_, bot_proc* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<bot_proc_m> *vec_, bot_proc_m* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }

	sint AVTA(sint arr[] = 0, sint asiz = 0, sint val = -1, bool check = true, bool use_empty = true) { if (!arr || !asiz) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(uint arr[] = 0, sint asiz = 0, uint val = UINT_MAX, bool check = true, bool use_empty = true) { if (!arr || asiz == UINT_MAX) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(slint arr[] = 0, sint asiz = 0, slint val = -1, bool check = true, bool use_empty = true) { if (!arr || !asiz) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(ulint arr[] = 0, sint asiz = 0, ulint val = UINT32_MAX, bool check = true, bool use_empty = true) { if (!arr || asiz == UINT32_MAX) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(sllint arr[] = 0, sint asiz = 0, sllint val = -1, bool check = true, bool use_empty = true) { if (!arr || !asiz) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(ullint arr[] = 0, sint asiz = 0, ullint val = UINT64_MAX, bool check = true, bool use_empty = true) { if (!arr || asiz == UINT64_MAX) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }

	std::chrono::steady_clock::time_point GVIV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { std::chrono::steady_clock::time_point ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele); } return ret; }
	sint GVIV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { *val = vec_->at(ele); ret = ele; } return ret; }
	sint GVIV(std::vector<carr_2> *vec_ = 0, sint ele = -1, carr_2* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_4> *vec_ = 0, sint ele = -1, carr_4* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_8> *vec_ = 0, sint ele = -1, carr_8* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_16> *vec_ = 0, sint ele = -1, carr_16* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_32> *vec_ = 0, sint ele = -1, carr_32* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_64> *vec_ = 0, sint ele = -1, carr_64* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_128> *vec_ = 0, sint ele = -1, carr_128* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_256> *vec_ = 0, sint ele = -1, carr_256* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_512> *vec_ = 0, sint ele = -1, carr_512* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_1024> *vec_ = 0, sint ele = -1, carr_1024* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_2048> *vec_ = 0, sint ele = -1, carr_2048* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
	sint GVIV(std::vector<carr_4096> *vec_ = 0, sint ele = -1, carr_4096* val = 0) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr,val->siz,"%s",vec_->at(ele).carr); } return -1; }
/*	u_char GetValInVecUC(std::vector<u_char> *vec_, sint ele = -1) { u_char ret = 0; if (ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }*/
	u_char GetValInVecUC(std::vector<void*> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, vec_->at(ele), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<sint> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<slint> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<sllint> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<uint> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<ulint> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<ullint> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<float> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<c_char*> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	u_char GetValInVecUC(std::vector<std::string> *vec_ = 0, sint ele = -1) { u_char ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { c_char* cret = vec_->at(ele).c_str(); const size_t inv_siz = sizeof(&cret); u_char ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&cret), inv_siz); ret = *ret_; } return ret; }
	void* GetValInVecV_(std::vector<u_char> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<void*> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	void* GetValInVecV_(std::vector<sint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<slint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<sllint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<uint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<ulint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<ullint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<float> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<c_char*> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<std::string> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { c_char* cret = vec_->at(ele).c_str(); ret = reinterpret_cast<void*>(&cret); } return ret; }
	sint GetValInVecI(std::vector<u_char> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); sint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	slint GetValInVecLI(std::vector<u_char> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); slint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	sllint GetValInVecLLI(std::vector<u_char> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); sllint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uint GetValInVecU(std::vector<u_char> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); uint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	ulint GetValInVecLU(std::vector<u_char> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); ulint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	ullint GetValInVecLLU(std::vector<u_char> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); ullint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	sint GetValInVecI(std::vector<sint> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<sint> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (slint)vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<sint> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sllint)vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<slint> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sint)vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<slint> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<slint> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sllint)vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<sllint> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sint)vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<sllint> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (slint)vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<sllint> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<uint> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sint)vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<uint> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (slint)vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<uint> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sllint)vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<ulint> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sint)vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<ulint> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (slint)vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<ulint> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sllint)vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<ullint> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sint)vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<ullint> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (slint)vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<ullint> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sllint)vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<uint> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<uint> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ulint)vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<uint> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ullint)vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<ulint> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (uint)vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<ulint> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<ulint> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ullint)vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<ullint> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (uint)vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<ullint> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ulint)vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<ullint> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<sint> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (uint)vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<sint> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ulint)vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<sint> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ullint)vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<slint> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (uint)vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<slint> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ulint)vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<slint> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ullint)vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<sllint> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (uint)vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<sllint> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ulint)vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<sllint> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ullint)vec_->at(ele); } } return ret; }
	//void* GetValInVecV_(std::vector<float> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (void*)&vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<float> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sint)vec_->at(ele); } } return ret; }
	slint GetValInVecLI(std::vector<float> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (slint)vec_->at(ele); } } return ret; }
	sllint GetValInVecLLI(std::vector<float> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (sllint)vec_->at(ele); } } return ret; }
	uint GetValInVecU(std::vector<float> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (uint)vec_->at(ele); } } return ret; }
	ulint GetValInVecLU(std::vector<float> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ulint)vec_->at(ele); } } return ret; }
	ullint GetValInVecLLU(std::vector<float> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (ullint)vec_->at(ele); } } return ret; }
	sint GetValInVecI(std::vector<c_char*> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
	slint GetValInVecLI(std::vector<c_char*> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#ifdef _WIN32
	sllint GetValInVecLLI(std::vector<c_char*> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = _atoi64(vec_->at(ele)); } } return ret; }
#else
	sllint GetValInVecLLI(std::vector<c_char*> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#endif
	uint GetValInVecU(std::vector<c_char*> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
	ulint GetValInVecLU(std::vector<c_char*> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#ifdef _WIN32
	ullint GetValInVecLLU(std::vector<c_char*> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = _atoi64(vec_->at(ele)); } } return ret; }
#else
	ullint GetValInVecLLU(std::vector<c_char*> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#endif
	sint GetValInVecI(std::vector<std::string> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele).c_str()); } } return ret; }
	slint GetValInVecLI(std::vector<std::string> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele).c_str()); } } return ret; }
#ifdef _WIN32
	sllint GetValInVecLLI(std::vector<std::string> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = _atoi64(vec_->at(ele).c_str()); } } return ret; }
#else
	sllint GetValInVecLLI(std::vector<std::string> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele).c_str()); } } return ret; }
#endif
	uint GetValInVecU(std::vector<std::string> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele).c_str()); } } return ret; }
	ulint GetValInVecLU(std::vector<std::string> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele).c_str()); } } return ret; }
#ifdef _WIN32
	ullint GetValInVecLLU(std::vector<std::string> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = _atoi64(vec_->at(ele).c_str()); } } return ret; }
#else
	ullint GetValInVecLLU(std::vector<std::string> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele).c_str()); } } return ret; }
#endif
	float GetFValInVec(std::vector<u_char> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { float* fp_ = reinterpret_cast<float*>(&vec_->at(ele)); ret = *fp_; } return ret; }
	float GetFValInVec(std::vector<void*> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { float* fp_ = reinterpret_cast<float*>(vec_->at(ele)); ret = *fp_; } } return ret; }
	float GetFValInVec(std::vector<float> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<sint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<slint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<uint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<c_char*> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)atof(vec_->at(ele)); } } return ret; }
	float GetFValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)atof(vec_->at(ele).c_str()); } } return ret; }
	void GetCValInVec(std::vector<u_char> *vec_ = 0, sint ele = -1, c_char* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = reinterpret_cast<c_char*>(&vec_->at(ele)); } } }
	void GetCValInVec(std::vector<void*> *vec_ = 0, sint ele = -1, c_char* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = reinterpret_cast<c_char*>(vec_->at(ele)); } } }
	void GetCValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, _char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%i", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, _char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%li", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, _char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%lli", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, _char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%u", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, _char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%lu", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, _char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%llu", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<float> *vec_ = 0, sint ele = -1, _char val[32] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 32, "%0.3f", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<c_char*> *vec_ = 0, sint ele = -1, c_char* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = (vec_->at(ele)); } } }
	void GetCValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1, c_char* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = (vec_->at(ele).c_str()); } } }
	std::string GetStrValInVec(std::vector<u_char> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { c_char* ret_ = reinterpret_cast<c_char*>(&vec_->at(ele)); ret.append(ret_); } } return ret; }
	std::string GetStrValInVec(std::vector<void*> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret.append(reinterpret_cast<c_char*>(vec_->at(ele))); } } return ret; }
#ifdef _WIN32
	std::string GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = (_itoa_s(vec_->at(ele), mid, 10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = (_itoa_s(vec_->at(ele), mid,10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
#else
	std::string GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = (bot_itoa(vec_->at(ele), mid, 10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = (bot_itoa(vec_->at(ele), mid, 10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
#endif
	std::string GetStrValInVec(std::vector<float> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[64]{ 0 }; bot_sprintf(mid, 64, "%0.3f", vec_->at(ele)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<c_char*> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret.append(vec_->at(ele)); } } return ret; }
	void GetStrValInVec(std::vector<u_char> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { c_char* ret_ = reinterpret_cast<c_char*>(&vec_->at(ele)); val->append(ret_); } } }
	void GetStrValInVec(std::vector<void*> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val->append(reinterpret_cast<c_char*>(vec_->at(ele))); } } }
#ifdef _WIN32
	void GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _itoa_s(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
	void GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
	void GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _itoa_s(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
#else
	void GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
#endif
	void GetStrValInVec(std::vector<float> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { _char mid[64]{ 0 }; bot_sprintf(mid, 64, "%0.3f", vec_->at(ele)); val->append(mid); } } }
	void GetStrValInVec(std::vector<c_char*> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val->append(vec_->at(ele)); } } }
	void GetStrValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val->append(vec_->at(ele)); } } }

	MICSYM GVIV(std::vector<MICSYM> *vec_ = 0, sint ele = -1) { MICSYM ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<MICSYM> *vec_ = 0, sint ele = -1, MICSYM* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
		}
		return ret;
	}
	MACSYM GVIV(std::vector<MACSYM> *vec_ = 0, sint ele = -1) { MACSYM ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<MACSYM> *vec_ = 0, sint ele = -1, MACSYM* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;
		
		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
		}
		return ret;
	}
	BOT_FLD GVIV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1) { BOT_FLD ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, BOT_FLD* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_FLD_MAX && memb > -1)
			{
				if (memb == BOT_FLD_FID) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).fid; }
				else if (memb == BOT_FLD_ORD) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).ord; }
				else if (memb == BOT_FLD_BTO) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).bto; }
				else if (memb == BOT_FLD_IHM) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).is_home; }
				else if (memb == BOT_FLD_FLD) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).fld.c_str()); }
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	sint GVIA(DB_CONN vec_[BOT_ATT_LIM] = 0, sint ele = -1, DB_CONN* val = 0) { if (ele < 0 || !vec_ || ele >= (sint)BOT_ATT_LIM) { return -1; } val->Renew(&vec_[ele]); return ele; }
	sint GVIA(BOTF_CONN vec_[BOT_FS_LIM] = 0, sint ele = -1, BOTF_CONN* val = 0) { if (ele < 0 || !vec_ || ele >= (sint)BOT_ATT_LIM) { return -1; } val->Renew(&vec_[ele]); return ele; }

	DB_CONN* GVIV(std::vector<DB_CONN*> *vec_ = 0, sint ele = -1) { DB_CONN* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }

	BOT_DB* GVIV(std::vector<BOT_DB*> *vec_ = 0, sint ele = -1) { BOT_DB* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_DB GVIV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1) { BOT_DB ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, BOT_DB* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_DB_MAX && memb > -1)
			{
				if (memb == BOT_DB_TYPE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).type; }
				else if (memb == BOT_DB_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
				else if (memb == BOT_DB_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_DB_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_DB_TABLES) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vp->clear(); while (siz < vec_->at(ele).tables.size()) { vp->push_back(vec_->at(ele).tables[siz]); siz++; } }
				else if (memb == BOT_DB_COLUMNS) { std::vector<std::vector<std::vector<std::string>>>* vp = reinterpret_cast<std::vector<std::vector<std::vector<std::string>>>*>(val); size_t siz = 0; vp->clear(); while (siz < vec_->at(ele).columns.size()) { vp->push_back(vec_->at(ele).columns[siz]); siz++; } }
				else if (memb == BOT_DB_EXISTS) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).exists; }
				else if (memb == BOT_DB_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_DB_FELE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).file_ele; }
				else if (memb == BOT_DB_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_DB_CONN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).connected; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	BOT_DB_M* GVIV(std::vector<BOT_DB_M*> *vec_ = 0, sint ele = -1) { BOT_DB_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_DB_M GVIV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1) { BOT_DB_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, BOT_DB_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_DB_MAX && memb > -1)
			{
				if (memb == BOT_DB_TYPE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).type; }
				else if (memb == BOT_DB_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_DB_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
				else if (memb == BOT_DB_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name.c_str()); }
				else if (memb == BOT_DB_TABLES) { size_t* vp = reinterpret_cast<size_t*>(val); *vp = vec_->at(ele).tsiz; }
				else if (memb == BOT_DB_COLUMNS) { size_t* vp = reinterpret_cast<size_t*>(val); *vp = vec_->at(ele).csiz; }
				else if (memb == BOT_DB_EXISTS) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).exists; }
				else if (memb == BOT_DB_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_DB_FELE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).file_ele; }
				else if (memb == BOT_DB_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_DB_CONN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).connected; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	BOT_CLIENT* GVIV(std::vector<BOT_CLIENT*> *vec_ = 0, sint ele = -1) { BOT_CLIENT* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_CLIENT GVIV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1) { BOT_CLIENT ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, BOT_CLIENT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_C_MAX && memb > -1)
			{
				if (memb == BOT_C_LOGGED_IN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).loggedin; }
				else if (memb == BOT_C_U_PRIV) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).updatepriv; }
				else if (memb == BOT_C_U_LOGIN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).updatelogin; }
				else if (memb == BOT_C_T_LOGINS) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).totallogins; }
				else if (memb == BOT_C_F_LOGINS) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).failed_logins; }
				else if (memb == BOT_C_PRIV) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).priv; }
				else if (memb == BOT_C_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).id; }
				else if (memb == BOT_C_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_C_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_C_L_LOGIN) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastlogin); }
				else if (memb == BOT_C_L_DATE) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).logindate); }
				else if (memb == BOT_C_LFL) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).last_failed_login); }
				else if (memb == BOT_C_LAST_E) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastexchange); }
				else if (memb == BOT_C_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_C_PRT) { bot_port* vp = reinterpret_cast<bot_port*>(val); vp->Renew(&vec_->at(ele).prt); }
				else if (memb == BOT_C_KYA) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).prt.key_a; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	BOT_CLIENT_M* GVIV(std::vector<BOT_CLIENT_M*> *vec_ = 0, sint ele = -1) { BOT_CLIENT_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_CLIENT_M GVIV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1) { BOT_CLIENT_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, BOT_CLIENT_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_C_MAX && memb > -1)
			{
				if (memb == BOT_C_LOGGED_IN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).loggedin; }
				else if (memb == BOT_C_U_PRIV) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).updatepriv; }
				else if (memb == BOT_C_U_LOGIN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).updatelogin; }
				else if (memb == BOT_C_T_LOGINS) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).totallogins; }
				else if (memb == BOT_C_F_LOGINS) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).failed_logins; }
				else if (memb == BOT_C_PRIV) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).priv; }
				else if (memb == BOT_C_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).id; }
				else if (memb == BOT_C_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_C_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_C_L_LOGIN) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastlogin); }
				else if (memb == BOT_C_L_DATE) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).logindate); }
				else if (memb == BOT_C_LFL) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).last_failed_login); }
				else if (memb == BOT_C_LAST_E) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastexchange); }
				else if (memb == BOT_C_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_C_PRT) { bot_port* vp = reinterpret_cast<bot_port*>(val); vp->Renew(&vec_->at(ele).prt); }
				else if (memb == BOT_C_KYA) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).prt.key_a; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	BOT_LOGDET* GVIV(std::vector<BOT_LOGDET*> *vec_ = 0, sint ele = -1) { BOT_LOGDET* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_LOGDET GVIV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1) { BOT_LOGDET ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, BOT_LOGDET* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;
		
		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_LOG_MAX && memb > -1)
			{
				if (memb == BOT_LOG_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_LOG_S) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).started; }
				else if (memb == BOT_LOG_T) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).logtitle); }
				else if (memb == BOT_LOG_S_DATE) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).startdate); }
				else if (memb == BOT_LOG_Q) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).log_q.size()) { vp->push_back(vec_->at(ele).log_q[siz]); siz++; } }
				else if (memb == BOT_LOG_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else {}
				ret = 0;
			}
		}
		return ret;
	}
	BOT_LOGDET_M* GVIV(std::vector<BOT_LOGDET_M*> *vec_ = 0, sint ele = -1) { BOT_LOGDET_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_LOGDET_M GVIV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1) { BOT_LOGDET_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, BOT_LOGDET_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_LOG_MAX && memb > -1)
			{
				if (memb == BOT_LOG_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_LOG_S) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).started; }
				else if (memb == BOT_LOG_T) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).logtitle); }
				else if (memb == BOT_LOG_S_DATE) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).startdate); }
				else if (memb == BOT_LOG_Q) { size_t* vp = reinterpret_cast<size_t*>(val); size_t siz = 0; *vp = vec_->at(ele).lsiz; }
				else if (memb == BOT_LOG_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else {}
				ret = 0;
			}
		}
		return ret;
	}
	BOT_FILE* GVIV(std::vector<BOT_FILE*> *vec_ = 0, sint ele = -1) { BOT_FILE* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_FILE GVIV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1) { BOT_FILE ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, BOT_FILE* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_FS_MAX && memb > -1)
			{
				if (memb == BOT_FS_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_FS_FP) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).path); }
				else if (memb == BOT_FS_FT) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).type); }
				else if (memb == BOT_FS_DAT) { _char* vp = reinterpret_cast<_char*>(val); if (vec_->at(ele).fst.filestats.st_size && vp) { memcpy((void*)vp, (void*)vec_->at(ele).dat, (size_t)vec_->at(ele).dsiz); } _char term = '\0'; memcpy((void*)&vp[vec_->at(ele).dsiz], (void*)&term, sizeof(_char)); }
				else if (memb == BOT_FS_DATP) { val = vec_->at(ele).dat; }
				else if (memb == BOT_FS_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_FS_STATE) { bot_fstate* vp = reinterpret_cast<bot_fstate*>(val); vp->Renew(&vec_->at(ele).fst); }
				else if (memb == BOT_FS_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_FS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_FS_CM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).cm; }
				else if (memb == BOT_FS_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
				else if (memb == BOT_FS_FPAD) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fpad; }
				else if (memb == BOT_FS_BTO) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).bto; }
				else if (memb == BOT_FS_DSIZ) { ullint* vp = reinterpret_cast<ullint*>(val); *vp = vec_->at(ele).dsiz; }
				else if (memb == BOT_FS_CRS) { BOT_CRS* vp = reinterpret_cast<BOT_CRS*>(val); vec_->at(ele).GetCrs(vp); }
				else if (memb == BOT_FS_CRSV) { std::vector<std::vector<BOT_CRS>>* vp = reinterpret_cast<std::vector<std::vector<BOT_CRS>>*>(val); if (vp) { vp->clear(); for (uint x = 0; x < vec_->at(ele).crsv.size(); x++) { std::vector<BOT_CRS> nv; vp->push_back(nv); for (uint y = 0; y < vec_->at(ele).crsv[x].size(); y++) { vp->at(x).push_back(vec_->at(ele).crsv[x][y]); } } } }
				else if (memb == BOT_FS_SELV) { std::vector<std::vector<BOT_CRS>>* vp = reinterpret_cast<std::vector<std::vector<BOT_CRS>>*>(val); if (vp) { vp->clear(); for (uint x = 0; x < vec_->at(ele).selv.size(); x++) { std::vector<BOT_CRS> nv; vp->push_back(nv); for (uint y = 0; y < vec_->at(ele).selv[x].size(); y++) { vp->at(x).push_back(vec_->at(ele).selv[x][y]); } } } }
				else {}
				ret = 0;
			}
		}
		return ret;
	}
	BOT_FILE_M* GVIV(std::vector<BOT_FILE_M*> *vec_ = 0, sint ele = -1) { BOT_FILE_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_FILE_M GVIV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1) { BOT_FILE_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, BOT_FILE_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_FS_MAX && memb > -1)
			{
				if (memb == BOT_FS_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_FS_FP) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).path); }
				else if (memb == BOT_FS_FT) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).type); }
				else if (memb == BOT_FS_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_FS_STATE) { bot_fstate* vp = reinterpret_cast<bot_fstate*>(val); vp->Renew(&vec_->at(ele).fst); }
				else if (memb == BOT_FS_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_FS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_FS_CM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).cm; }
				else if (memb == BOT_FS_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
				else if (memb == BOT_FS_FPAD) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fpad; }
				else if (memb == BOT_FS_BTO) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).bto; }
				else if (memb == BOT_FS_DSIZ) { ullint* vp = reinterpret_cast<ullint*>(val); *vp = vec_->at(ele).dsiz; }
				else if (memb == BOT_FS_DATP) { val = vec_->at(ele).datp; }
				else if (memb == BOT_FS_CRS) { BOT_CRS* vp = reinterpret_cast<BOT_CRS*>(val); if (vp) { vec_->at(ele).GetCrs(vp); } }
				else if (memb == BOT_FS_CRSV) { size_t* vp = reinterpret_cast<size_t*>(val); if (vp) { *vp = vec_->at(ele).crss; } }
				else if (memb == BOT_FS_SELV) { size_t* vp = reinterpret_cast<size_t*>(val); if (vp) { *vp = vec_->at(ele).sels; } }
				else {}
				ret = 0;
			}
		}
		return ret;
	}
	TINFO* GVIV(std::vector<TINFO*> *vec_ = 0, sint ele = -1) { TINFO* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<TINFO> *vec_ = 0, sint ele = -1, TINFO* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_TTS_MAX && memb > -1)
			{
				if (memb == BOT_TTS_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_TTS_TNAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).thread_name); }
				else if (memb == BOT_TTS_THREAD) { pthread_t* vp = reinterpret_cast<pthread_t*>(val); *vp = vec_->at(ele).thread; }
				else if (memb == BOT_TTS_ATTR) { pthread_attr_t* vp = reinterpret_cast<pthread_attr_t*>(val); *vp = vec_->at(ele).attr; }
				else if (memb == BOT_TTS_OPT) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).opt; }
				else if (memb == BOT_TTS_FIN) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fin; }
				else if (memb == BOT_TTS_FUNC) { void *(*vp)(void *) = reinterpret_cast<void *(*)(void *)>(val); vp = vec_->at(ele).func; }
				else if (memb == BOT_TTS_TIMEP) { std::chrono::steady_clock::time_point* vp = reinterpret_cast<std::chrono::steady_clock::time_point*>(val); *vp = vec_->at(ele).t_I; }
				else if (memb == BOT_TTS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_TTS_MINR) { float* vp = reinterpret_cast<float*>(val); *vp = vec_->at(ele).min_ratv; }
				else if (memb == BOT_TTS_VALS) { std::vector<ullint>* vp = reinterpret_cast<std::vector<ullint>*>(val); vp->clear(); for (uint x = 0; x < vec_->at(ele).vals.size(); x++) { vp->push_back(vec_->at(ele).vals[x]); } }
				else if (memb == BOT_TTS_SIG) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).sig; }
				else if (memb == BOT_TTS_TID) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).tid; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	TINFO_M* GVIV(std::vector<TINFO_M*> *vec_ = 0, sint ele = -1) { TINFO_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, TINFO_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_TTS_MAX && memb > -1)
			{
				if (memb == BOT_TTS_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_TTS_TNAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).thread_name); }
				else if (memb == BOT_TTS_THREAD) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).thread; }
				else if (memb == BOT_TTS_ATTR) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).attr; }
				else if (memb == BOT_TTS_OPT) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).opt; }
				else if (memb == BOT_TTS_FIN) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fin; }
				else if (memb == BOT_TTS_FUNC) { void *(*vp)(void *) = reinterpret_cast<void *(*)(void *)>(val); vp = vec_->at(ele).func; }
				else if (memb == BOT_TTS_TIMEP) { std::chrono::steady_clock::time_point* vp = reinterpret_cast<std::chrono::steady_clock::time_point*>(val); *vp = vec_->at(ele).t_I; }
				else if (memb == BOT_TTS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_TTS_MINR) { float* vp = reinterpret_cast<float*>(val); *vp = vec_->at(ele).min_ratv; }
				else if (memb == BOT_TTS_VALS) { std::vector<ullint>* vp = reinterpret_cast<std::vector<ullint>*>(val); vp->clear(); for (uint x = 0; x < vec_->at(ele).vals.size(); x++) { vp->push_back(vec_->at(ele).vals[x]); } }
				else if (memb == BOT_TTS_SIG) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).sig; }
				else if (memb == BOT_TTS_TID) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).tid; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	HELD_MTX* GVIV(std::vector<HELD_MTX*> *vec_ = 0, sint ele = -1) { HELD_MTX* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, HELD_MTX* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < HMTX_MAX && memb > -1)
			{
				if (memb == HMTX_W_MTX) { size_t* vp = reinterpret_cast<size_t*>(val); *vp = vec_->at(ele).w_mtx; }
				else if (memb == HMTX_LOCK) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).locked; }
				else if (memb == HMTX_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == HMTX_MEMS) { std::vector<sint>* vp = reinterpret_cast<std::vector<sint>*>(val); size_t siz = 0; while (siz < vec_->at(ele).h_mems.size()) { vp->push_back(vec_->at(ele).h_mems[siz]); siz++; } }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	lok_req* GVIV(std::vector<lok_req*> *vec_ = 0, sint ele = -1) { lok_req* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<lok_req> *vec_ = 0, sint ele = -1, lok_req* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<lok_req> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_REQ_MAX && memb > -1)
			{
				if (memb == BOT_REQ_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_REQ_FID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fid; }
				else if (memb == BOT_REQ_GMTX) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).gmtx; }
				else if (memb == BOT_REQ_ELE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).ele; }
				else if (memb == BOT_REQ_META) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).is_meta; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	BOT_STMT* GVIV(std::vector<BOT_STMT*> *vec_ = 0, sint ele = -1) { BOT_STMT* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GVIV(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, BOT_STMT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_STMT_MAX && memb > -1)
			{
				if (memb == BOT_STMT_MAINT) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).maint; }
				else if (memb == BOT_STMT_STMT) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).stmt); }
				else if (memb == BOT_STMT_TTYPE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).it_type; }
				else if (memb == BOT_STMT_CTYPES) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).ic_type; }
				else if (memb == BOT_STMT_CONT) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).cont.c_str()); }
				else if (memb == BOT_STMT_DBNAME) { std::string* vp = reinterpret_cast<std::string*>(val); size_t siz = 0; vp->append(vec_->at(ele).dbname.c_str()); }
				else if (memb == BOT_STMT_DBALIAS) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).dbalias.c_str()); }
				else if (memb == BOT_STMT_OPTS) { sint* vp = reinterpret_cast<sint*>(val); size_t siz = 0; while (siz < sizeof(vec_->at(ele).opts)) { vp[siz] = vec_->at(ele).opts[siz]; siz++; } }
				else if (memb == BOT_STMT_SPEC) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).spec; }
				else if (memb == BOT_STMT_RLIM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).rlim; }
				else if (memb == BOT_STMT_TARG) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).targ; }
				else if (memb == BOT_STMT_ACT) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).act; }
				else if (memb == BOT_STMT_OSPEC) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).ospec; }
				else if (memb == BOT_STMT_IFEX) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).ifex; }
				else if (memb == BOT_STMT_COLS) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).cols.size()) { vp->push_back(vec_->at(ele).cols[siz]); siz++; } }
				else if (memb == BOT_STMT_VALS) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).vals.size()) { vp->push_back(vec_->at(ele).vals[siz]); siz++; } }
				else if (memb == BOT_STMT_CONDS) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).conds.size()) { vp->push_back(vec_->at(ele).conds[siz]); siz++; } }
				else if (memb == BOT_STMT_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_STMT_AN) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).an; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	bot_port* GVIV(std::vector<bot_port*> *vec_ = 0, sint ele = -1) { bot_port* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	bot_port GVIV(std::vector<bot_port> *vec_ = 0, sint ele = -1) { bot_port ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<bot_port> *vec_ = 0, sint ele = -1, bot_port* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<bot_port> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_PORT_MAX && memb > -1)
			{
				if (memb == BOT_PORT_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_PORT_STP) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).stype; }
				else if (memb == BOT_PORT_PTN) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).portn; }
				else if (memb == BOT_PORT_RPT) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).rport; }
				else if (memb == BOT_PORT_PCL) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).proto; }
				else if (memb == BOT_PORT_SOP) { std::vector<BOT_SOPT>* vp = reinterpret_cast<std::vector<BOT_SOPT>*>(val); size_t siz = 0; vp->clear(); while (siz < vec_->at(ele).sopts.size()) { vp->push_back(vec_->at(ele).sopts[siz]); siz++; } }
				else if (memb == BOT_PORT_XCL) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).xcl; }
				else if (memb == BOT_PORT_IPS) { carr_64* vp = reinterpret_cast<carr_64*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).ipstr, sizeof(carr_64)); }
				else if (memb == BOT_PORT_OPS) { carr_64* vp = reinterpret_cast<carr_64*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).oipstr, sizeof(carr_64)); }
#ifdef _WIN32
				else if (memb == BOT_PORT_SCK) { SOCKET* vp = reinterpret_cast<SOCKET*>(val); *vp = vec_->at(ele).sck; }
#else
				else if (memb == BOT_PORT_SCK) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).sck; }
#endif
				else if (memb == BOT_PORT_KYA) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).key_a; }
				else if (memb == BOT_PORT_BDP) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).bndp; }
				else if (memb == BOT_PORT_SIG) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).signal; }
				else if (memb == BOT_PORT_OAD) { sockaddr_storage* vp = reinterpret_cast<sockaddr_storage*>(val); *vp = vec_->at(ele).oaddr; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	bot_plug* GVIV(std::vector<bot_plug*> *vec_ = 0, sint ele = -1) { bot_plug* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	bot_plug GVIV(std::vector<bot_plug> *vec_ = 0, sint ele = -1) { bot_plug ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<bot_plug> *vec_ = 0, sint ele = -1, bot_plug* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<bot_plug> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_PLUG_MAX && memb > -1)
			{
				if (memb == BOT_PLUG_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_PLUG_ERR) { carr_256* vp = reinterpret_cast<carr_256*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).url, sizeof(carr_256)); }
				else if (memb == BOT_PLUG_SRV) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).isserv; }
				else if (memb == BOT_PLUG_CON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).con; }
				else if (memb == BOT_PLUG_QSZ) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).qsiz; }
				else if (memb == BOT_PLUG_PRT) { bot_port* vp = reinterpret_cast<bot_port*>(val); vp->Renew(&vec_->at(ele).prt); }
				else if (memb == BOT_PLUG_RES) { addrinfo* vp = reinterpret_cast<addrinfo*>(val); vp = vec_->at(ele).res; }
				else if (memb == BOT_PLUG_PTR) { addrinfo* vp = reinterpret_cast<addrinfo*>(val); vp = vec_->at(ele).ptr; }
				else if (memb == BOT_PLUG_HNT) { addrinfo* vp = reinterpret_cast<addrinfo*>(val); *vp = vec_->at(ele).hints; }
				else if (memb == BOT_PLUG_URL) { carr_512* vp = reinterpret_cast<carr_512*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).url, sizeof(carr_512)); }
				else if (memb == BOT_PLUG_ORL) { carr_512* vp = reinterpret_cast<carr_512*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).ourl, sizeof(carr_512)); }
				else if (memb == BOT_PLUG_FAM) { carr_8* vp = reinterpret_cast<carr_8*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).ifam, sizeof(carr_8)); }
				else if (memb == BOT_PLUG_SVC) { carr_64* vp = reinterpret_cast<carr_64*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).servc, sizeof(carr_64)); }
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	bot_proc* GVIV(std::vector<bot_proc*> *vec_ = 0, sint ele = -1) { bot_proc* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	bot_proc GVIV(std::vector<bot_proc> *vec_ = 0, sint ele = -1) { bot_proc ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<bot_proc> *vec_ = 0, sint ele = -1, bot_proc* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<bot_proc> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_PROC_MAX && memb > -1)
			{
				if (memb == BOT_PROC_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_PROC_PID) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).pid; }
				else if (memb == BOT_PROC_NM) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).anm.c_str()); }
#ifdef _WIN32
				else if (memb == BOT_PROC_SIN) { STARTUPINFOA* vp = reinterpret_cast<STARTUPINFOA*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).sinfo, sizeof(STARTUPINFOA)); }
				else if (memb == BOT_PROC_PIN) { PROCESS_INFORMATION* vp = reinterpret_cast<PROCESS_INFORMATION*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).pinfo, sizeof(PROCESS_INFORMATION)); }
#else
				else if (memb == BOT_PROC_SIN) { memcpy(val, (void*)vec_->at(ele).sinfo, sizeof(slint) * 21); }
				else if (memb == BOT_PROC_PIN) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).pinfo; }
#endif
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	bot_proc_m* GVIV(std::vector<bot_proc_m*> *vec_ = 0, sint ele = -1) { bot_proc_m* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	bot_proc_m GVIV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1) { bot_proc_m ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GVIV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1, bot_proc_m* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			val->Renew(&vec_->at(ele));
			ret = ele;
		}
		return ret;
	}
	sint GMIV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			if (memb < BOT_PROC_MAX && memb > -1)
			{
				if (memb == BOT_PROC_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_PROC_NM) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).anm.c_str()); }
				else if (memb == BOT_PROC_PID) { slint* vp = reinterpret_cast<slint*>(val); *vp = vec_->at(ele).pid; }
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	sint SVIV(std::vector<carr_2> *vec_ = 0, sint ele = -1, carr_2* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_4> *vec_ = 0, sint ele = -1, carr_4* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_8> *vec_ = 0, sint ele = -1, carr_8* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_16> *vec_ = 0, sint ele = -1, carr_16* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_32> *vec_ = 0, sint ele = -1, carr_32* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_64> *vec_ = 0, sint ele = -1, carr_64* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_128> *vec_ = 0, sint ele = -1, carr_128* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_256> *vec_ = 0, sint ele = -1, carr_256* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_512> *vec_ = 0, sint ele = -1, carr_512* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_1024> *vec_ = 0, sint ele = -1, carr_1024* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_2048> *vec_ = 0, sint ele = -1, carr_2048* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<carr_4096> *vec_ = 0, sint ele = -1, carr_4096* val = 0) { if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { return bot_sprintf(val->carr, val->siz, "%s", vec_->at((size_t)ele).carr); } return -1; }
	sint SVIV(std::vector<_char*> *vec_ = 0, sint ele = -1, _char* val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<_char> *vec_ = 0, sint ele = -1, _char val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<u_char> *vec_ = 0, sint ele = -1, u_char val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<void*> *vec_ = 0, sint ele = -1, void* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1, std::chrono::steady_clock::time_point* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = *val; ret = ele; } return ret; }
	sint SVIV(std::vector<sint> *vec_ = 0, sint ele = -1, uint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<slint> *vec_ = 0, sint ele = -1, ulint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<sllint> *vec_ = 0, sint ele = -1, ullint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<uint> *vec_ = 0, sint ele = -1, uint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<ulint> *vec_ = 0, sint ele = -1, ulint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<ullint> *vec_ = 0, sint ele = -1, ullint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<float> *vec_ = 0, sint ele = -1, float* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = *val; ret = ele; } return ret; }
	sint SVIV(std::vector<c_char*> *vec_ = 0, sint ele = -1, c_char* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<std::string> *vec_ = 0, sint ele = -1, std::string* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele).clear(); vec_->at((size_t)ele).append(*val); ret = ele; } return ret; }
	
	sint SVIV(std::vector<MICSYM> *vec_ = 0, sint ele = -1, MICSYM* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele).Renew(val); ret = ele; } return ret; }
	sint SVIV(std::vector<MACSYM> *vec_ = 0, sint ele = -1, MACSYM* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele).Renew(val); ret = ele; } return ret; }

	sint SVIV(std::vector<BOT_FLD*> *vec_ = 0, sint ele = -1, BOT_FLD* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sllint SVIV(std::vector<BOT_FLD> *vec_ = 0, BOT_FLD* val = 0) { if (!vec_ || !val) { return -1; }  if (val->fid < 0) { return -1; } sllint ret = -1; if (val->fid < (sllint)vec_->size()) { vec_->at((size_t)(val->fid)).Renew(val); ret = val->fid; } return ret; }
	sint SVIV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, BOT_FLD* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FLD_MAX)
		{
			if (memb == BOT_FLD_FID) { sllint* val_ = reinterpret_cast<sllint*>(val); vec_->at(ele).fid = *val_; }
			else if (memb == BOT_FLD_ORD) { sllint* val_ = reinterpret_cast<sllint*>(val); vec_->at(ele).ord = *val_; }
			else if (memb == BOT_FLD_BTO) { sllint* val_ = reinterpret_cast<sllint*>(val); vec_->at(ele).bto = *val_; }
			else if (memb == BOT_FLD_IHM) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).is_home = *val_; }
			else if (memb == BOT_FLD_FLD) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).fld.clear(); if (val_->length() < 128) { vec_->at(ele).fld.append(val_->c_str()); } }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_DB*> *vec_ = 0, sint ele = -1, BOT_DB* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, BOT_DB* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;
		
		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_DB_MAX) 
		{
			if (memb == BOT_DB_TYPE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).type = *val_; }
			else if (memb == BOT_DB_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_DB_FCON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fcon = *val_; }
			else if (memb == BOT_DB_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < 128) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_DB_TABLES) { std::vector <std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).tables.clear(); while (siz < vp->size()) { vec_->at(ele).tables.push_back(vp->at(siz)); siz++; } }
			else if (memb == BOT_DB_COLUMNS) { std::vector<std::vector<std::vector <std::string>>>* vp = reinterpret_cast<std::vector<std::vector<std::vector<std::string>>>*>(val); size_t siz = 0; vec_->at(ele).columns.clear(); while (siz < vp->size()) { vec_->at(ele).columns.push_back(vp->at(siz)); siz++; } }
			else if (memb == BOT_DB_EXISTS) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).exists = *val_; }
			else if (memb == BOT_DB_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_DB_FELE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).file_ele = *val_; }
			else if (memb == BOT_DB_OMODE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).omode = *val_; }
			else if (memb == BOT_DB_CONN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).connected = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, BOT_DB_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_DB_MAX)
		{
			if (memb == BOT_DB_TYPE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).type = *val_; }
			else if (memb == BOT_DB_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_DB_FCON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fcon = *val_; }
			else if (memb == BOT_DB_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < 128) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_DB_TABLES) { size_t* val_ = reinterpret_cast<size_t*>(val); vec_->at(ele).tsiz = *val_; }
			else if (memb == BOT_DB_COLUMNS) { size_t* val_ = reinterpret_cast<size_t*>(val); vec_->at(ele).csiz = *val_; }
			else if (memb == BOT_DB_EXISTS) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).exists = *val_; }
			else if (memb == BOT_DB_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_DB_FELE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).file_ele = *val_; }
			else if (memb == BOT_DB_OMODE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).omode = *val_; }
			else if (memb == BOT_DB_CONN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).connected = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_CLIENT*> *vec_ = 0, sint ele = -1, BOT_CLIENT* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, BOT_CLIENT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_C_MAX)
		{
			if (memb == BOT_C_LOGGED_IN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).loggedin = *val_; }
			else if (memb == BOT_C_U_PRIV) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).updatepriv = *val_; }
			else if (memb == BOT_C_U_LOGIN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).updatelogin = *val_; }
			else if (memb == BOT_C_T_LOGINS) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).totallogins = *val_; }
			else if (memb == BOT_C_F_LOGINS) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).failed_logins = *val_; }
			else if (memb == BOT_C_PRIV) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).priv = *val_; }
			else if (memb == BOT_C_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).id = *val_; }
			else if (memb == BOT_C_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_C_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < 128) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_C_L_LOGIN) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastlogin.clear(); if (val_->length() < 128) { vec_->at(ele).lastlogin.append(val_->c_str()); } }
			else if (memb == BOT_C_L_DATE) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).logindate.clear(); if (val_->length() < 128) { vec_->at(ele).logindate.append(val_->c_str()); } }
			else if (memb == BOT_C_LFL) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).last_failed_login.clear(); if (val_->length() < 128) { vec_->at(ele).last_failed_login.append(val_->c_str()); } }
			else if (memb == BOT_C_LAST_E) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastexchange.clear(); if (val_->length() < 128) { vec_->at(ele).lastexchange.append(val_->c_str()); } }
			else if (memb == BOT_C_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_C_PRT) { bot_port* val_ = reinterpret_cast<bot_port*>(val); vec_->at(ele).prt.Renew(val_); }
			else if (memb == BOT_C_KYA) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).prt.key_a = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_CLIENT_M*> *vec_ = 0, sint ele = -1, BOT_CLIENT_M* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, BOT_CLIENT_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_C_MAX)
		{
			if (memb == BOT_C_LOGGED_IN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).loggedin = *val_; }
			else if (memb == BOT_C_U_PRIV) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).updatepriv = *val_; }
			else if (memb == BOT_C_U_LOGIN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).updatelogin = *val_; }
			else if (memb == BOT_C_T_LOGINS) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).totallogins = *val_; }
			else if (memb == BOT_C_F_LOGINS) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).failed_logins = *val_; }
			else if (memb == BOT_C_PRIV) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).priv = *val_; }
			else if (memb == BOT_C_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).id = *val_; }
			else if (memb == BOT_C_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_C_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < 128) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_C_L_LOGIN) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastlogin.clear(); if (val_->length() < 128) { vec_->at(ele).lastlogin.append(val_->c_str()); } }
			else if (memb == BOT_C_L_DATE) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).logindate.clear(); if (val_->length() < 128) { vec_->at(ele).logindate.append(val_->c_str()); } }
			else if (memb == BOT_C_LFL) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).last_failed_login.clear(); if (val_->length() < 128) { vec_->at(ele).last_failed_login.append(val_->c_str()); } }
			else if (memb == BOT_C_LAST_E) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastexchange.clear(); if (val_->length() < 128) { vec_->at(ele).lastexchange.append(val_->c_str()); } }
			else if (memb == BOT_C_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_C_PRT) { bot_port* val_ = reinterpret_cast<bot_port*>(val); vec_->at(ele).prt.Renew(val_); }
			else if (memb == BOT_C_KYA) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).prt.key_a = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_LOGDET*> *vec_ = 0, sint ele = -1, BOT_LOGDET* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, BOT_LOGDET* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_LOG_MAX)
		{
			if (memb == BOT_LOG_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_LOG_S) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).started = *val_; }
			else if (memb == BOT_LOG_T) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).logtitle.clear(); if (val_->length() < 256) { vec_->at(ele).logtitle.append(val_->c_str()); } }
			else if (memb == BOT_LOG_S_DATE) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).startdate.clear(); if (val_->length() < 128) { vec_->at(ele).startdate.append(val_->c_str()); } }
			else if (memb == BOT_LOG_Q) { std::vector <std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).log_q.clear(); while (siz < vp->size()) { vec_->at(ele).log_q.push_back(vp->at(siz)); siz++; } }
			else if (memb == BOT_LOG_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_LOGDET_M*> *vec_ = 0, sint ele = -1, BOT_LOGDET_M* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, BOT_LOGDET_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_LOG_MAX)
		{
			if (memb == BOT_LOG_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_LOG_S) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).started = *val_; }
			else if (memb == BOT_LOG_T) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).logtitle.clear(); if (val_->length() < 256) { vec_->at(ele).logtitle.append(val_->c_str()); } }
			else if (memb == BOT_LOG_S_DATE) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).startdate.clear(); if (val_->length() < 128) { vec_->at(ele).startdate.append(val_->c_str()); } }
			else if (memb == BOT_LOG_Q) { size_t* vp = reinterpret_cast<size_t*>(val); size_t siz = 0; vec_->at(ele).lsiz = *vp; }
			else if (memb == BOT_LOG_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_FILE*> *vec_ = 0, sint ele = -1, BOT_FILE* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, BOT_FILE* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FS_MAX)
		{
			if (memb == BOT_FS_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < BOT_FILENAME_MAX) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_FS_FP) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).path.clear(); if (val_->length() < UINT64_MAX) { vec_->at(ele).path.append(val_->c_str()); } }
			else if (memb == BOT_FS_FT) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).type.clear(); if (val_->length() < 128) { vec_->at(ele).type.append(val_->c_str()); } }
			else if (memb == BOT_FS_OMODE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).omode = *val_; }
			else if (memb == BOT_FS_STATE) { bot_fstate* val_ = reinterpret_cast<bot_fstate*>(val); vec_->at(ele).fst.Renew(val_); }
			else if (memb == BOT_FS_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_FS_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_FS_CM) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).cm = *val_; }
			else if (memb == BOT_FS_FCON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fcon = *val_; }
			else if (memb == BOT_FS_FPAD) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fpad = *val_; }
			else if (memb == BOT_FS_BTO) { sllint* val_ = reinterpret_cast<sllint*>(val); vec_->at(ele).bto = *val_; }
			else if (memb == BOT_FS_DAT) { _char* val_ = reinterpret_cast<_char*>(val); vec_->at(ele).SetDat(val_); }
			else if (memb == BOT_FS_DATP) { _char* val_ = reinterpret_cast<_char*>(val); vec_->at(ele).dat = val_; }
			else if (memb == BOT_FS_DSIZ) { size_t* val_ = reinterpret_cast<size_t*>(val); vec_->at(ele).dsiz = *val_; }
			else if (memb == BOT_FS_CRS) { BOT_CRS* val_ = reinterpret_cast<BOT_CRS*>(val); vec_->at(ele).SetCrs(val_); }
			else if (memb == BOT_FS_CRSV) { std::vector<std::vector<BOT_CRS>>* val_ = reinterpret_cast<std::vector<std::vector<BOT_CRS>>*>(val); vec_->at(ele).crsv.clear(); for (uint x = 0; x < val_->size(); x++) { for (uint y = 0; y < val_->at(x).size(); y++) { vec_->at(ele).crsv[x].push_back(val_->at(x)[y]); } } }
			else if (memb == BOT_FS_SELV) { std::vector<std::vector<BOT_CRS>>* val_ = reinterpret_cast<std::vector<std::vector<BOT_CRS>>*>(val); vec_->at(ele).selv.clear(); for (uint x = 0; x < val_->size(); x++) { for (uint y = 0; y < val_->at(x).size(); y++) { vec_->at(ele).selv[x].push_back(val_->at(x)[y]); } } }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_FILE_M*> *vec_ = 0, sint ele = -1, BOT_FILE_M* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, BOT_FILE_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FS_MAX)
		{
			if (memb == BOT_FS_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); if (val_) { vec_->at(ele).name.clear(); if (val_->length() < BOT_FILENAME_MAX) { vec_->at(ele).name.append(val_->c_str()); } } }
			else if (memb == BOT_FS_FP) { std::string* val_ = reinterpret_cast<std::string*>(val); if (val_) { vec_->at(ele).path.clear(); if (val_->length() < UINT64_MAX) { vec_->at(ele).path.append(val_->c_str()); } } }
			else if (memb == BOT_FS_FT) { std::string* val_ = reinterpret_cast<std::string*>(val); if (val_) { vec_->at(ele).type.clear(); if (val_->length() < 128) { vec_->at(ele).type.append(val_->c_str()); } } }
			else if (memb == BOT_FS_OMODE) { sint* val_ = reinterpret_cast<sint*>(val); if (val_) { vec_->at(ele).omode = *val_; } }
			else if (memb == BOT_FS_STATE) { bot_fstate* val_ = reinterpret_cast<bot_fstate*>(val); if (val_) { vec_->at(ele).fst.Renew(val_); } }
			else if (memb == BOT_FS_LID) { sint* val_ = reinterpret_cast<sint*>(val); if (val_) { vec_->at(ele).lid = *val_; } }
			else if (memb == BOT_FS_CBY) { sint* val_ = reinterpret_cast<sint*>(val); if (val_) { vec_->at(ele).c_by = *val_; } }
			else if (memb == BOT_FS_CM) { sint* val_ = reinterpret_cast<sint*>(val); if (val_) { vec_->at(ele).cm = *val_; } }
			else if (memb == BOT_FS_FCON) { sint* val_ = reinterpret_cast<sint*>(val); if (val_) { vec_->at(ele).fcon = *val_; } }
			else if (memb == BOT_FS_FPAD) { sint* val_ = reinterpret_cast<sint*>(val); if (val_) { vec_->at(ele).fpad = *val_; } }
			else if (memb == BOT_FS_BTO) { sllint* val_ = reinterpret_cast<sllint*>(val); if (val_) { vec_->at(ele).bto = *val_; } }
			else if (memb == BOT_FS_DSIZ) { size_t* val_ = reinterpret_cast<size_t*>(val); if (val_) { vec_->at(ele).dsiz = *val_; } }
			else if (memb == BOT_FS_DATP) { _char* val_ = reinterpret_cast<_char*>(val); if (val_) { vec_->at(ele).datp = val_; } }
			else if (memb == BOT_FS_CRS) { BOT_CRS* val_ = reinterpret_cast<BOT_CRS*>(val); if (val_) { vec_->at(ele).SetCrs(val_); } }
			else if (memb == BOT_FS_CRSV) { size_t* val_ = reinterpret_cast<size_t*>(val); if (val_) { vec_->at(ele).crss = *val_; } }
			else if (memb == BOT_FS_SELV) { size_t* val_ = reinterpret_cast<size_t*>(val); if (val_) { vec_->at(ele).sels = *val_; } }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<TINFO*> *vec_ = 0, sint ele = -1, TINFO* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<TINFO> *vec_ = 0, TINFO* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<TINFO> *vec_ = 0, sint ele = -1, TINFO* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_TTS_MAX)
		{
			if (memb == BOT_TTS_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_TTS_TNAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).thread_name.clear(); if (val_->length() < 256) { vec_->at(ele).thread_name.append(val_->c_str()); } }
			else if (memb == BOT_TTS_THREAD) { pthread_t* val_ = (pthread_t*)val; vec_->at(ele).thread = *val_; }
			else if (memb == BOT_TTS_ATTR) { pthread_attr_t* val_ = (pthread_attr_t*)val; vec_->at(ele).attr = *val_; }
			else if (memb == BOT_TTS_OPT) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).opt = *val_; }
			else if (memb == BOT_TTS_FIN) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fin = *val_; }
			else if (memb == BOT_TTS_FUNC) { void *(*val_)(void *) = reinterpret_cast<void*(*)(void*)> (val); vec_->at(ele).func = val_; }
			else if (memb == BOT_TTS_TIMEP) { std::chrono::steady_clock::time_point* val_ = reinterpret_cast<std::chrono::steady_clock::time_point*>(val); vec_->at(ele).t_I = *val_; }
			else if (memb == BOT_TTS_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_TTS_MINR) { float* val_ = reinterpret_cast<float*>(val); vec_->at(ele).min_ratv = *val_; }
			else if (memb == BOT_TTS_VALS) { std::vector<ullint>* val_ = reinterpret_cast<std::vector<ullint>*>(val); vec_->at(ele).vals.clear(); for (uint x = 0; x < val_->size(); x++) { vec_->at(ele).vals.push_back(val_->at(x)); } }
			else if (memb == BOT_TTS_SIG) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).sig = *val_; }
			else if (memb == BOT_TTS_TID) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).tid = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<TINFO_M*> *vec_ = 0, sint ele = -1, TINFO_M* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0) { if (!vec_ || !val) { return -1; } if (val->lid < 0) { return -1; }  sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, TINFO_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_TTS_MAX)
		{
			if (memb == BOT_TTS_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_TTS_TNAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).thread_name.clear(); if (val_->length() < 256) { vec_->at(ele).thread_name.append(val_->c_str()); } }
			else if (memb == BOT_TTS_THREAD) { sllint* val_ = (sllint*)val; vec_->at(ele).thread = *val_; }
			else if (memb == BOT_TTS_ATTR) { sllint* val_ = (sllint*)val; vec_->at(ele).attr = *val_; }
			else if (memb == BOT_TTS_OPT) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).opt = *val_; }
			else if (memb == BOT_TTS_FIN) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fin = *val_; }
			else if (memb == BOT_TTS_FUNC) { void *(*val_)(void *) = reinterpret_cast<void*(*)(void*)> (val); vec_->at(ele).func = val_; }
			else if (memb == BOT_TTS_TIMEP) { std::chrono::steady_clock::time_point* val_ = reinterpret_cast<std::chrono::steady_clock::time_point*>(val); vec_->at(ele).t_I = *val_; }
			else if (memb == BOT_TTS_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_TTS_MINR) { float* val_ = reinterpret_cast<float*>(val); vec_->at(ele).min_ratv = *val_; }
			else if (memb == BOT_TTS_VALS) { std::vector<ullint>* val_ = reinterpret_cast<std::vector<ullint>*>(val); vec_->at(ele).vals.clear(); for (uint x = 0; x < val_->size(); x++) { vec_->at(ele).vals.push_back(val_->at(x)); } }
			else if (memb == BOT_TTS_SIG) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).sig = *val_; }
			else if (memb == BOT_TTS_TID) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).tid = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<HELD_MTX*> *vec_ = 0, sint ele = -1, HELD_MTX* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, HELD_MTX* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < HMTX_MAX)
		{
			if (memb == HMTX_W_MTX) { size_t* val_ = reinterpret_cast<size_t*>(val); vec_->at(ele).w_mtx = *val_; }
			else if (memb == HMTX_LOCK) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).locked = *val_; }
			else if (memb == HMTX_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == HMTX_MEMS) { std::vector<sint>* val_ = reinterpret_cast<std::vector<sint>*>(val); size_t siz = 0; vec_->at(ele).h_mems.clear(); while (siz < val_->size()) { vec_->at(ele).h_mems.push_back(val_->at(siz)); siz++; } }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<lok_req*> *vec_ = 0, sint ele = -1, lok_req* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<lok_req> *vec_ = 0, lok_req* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<lok_req> *vec_ = 0, sint ele = -1, lok_req* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }
		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<lok_req> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_REQ_MAX)
		{
			if (memb == BOT_REQ_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_REQ_FID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fid = *val_; }
			else if (memb == BOT_REQ_GMTX) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).gmtx = *val_; }
			else if (memb == BOT_REQ_ELE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).ele = *val_; }
			else if (memb == BOT_REQ_META) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).is_meta = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<BOT_STMT*> *vec_ = 0, sint ele = -1, BOT_STMT* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<BOT_STMT> *vec_ = 0, BOT_STMT* val = 0) { if (!vec_ || !val) { return -1; }  if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, BOT_STMT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_STMT_MAX)
		{
			if (memb == BOT_STMT_MAINT) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).maint = *val_; }
			else if (memb == BOT_STMT_STMT) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).stmt.clear(); if (val_->length() < 256) { vec_->at(ele).stmt.append(val_->c_str()); } }
			else if (memb == BOT_STMT_TTYPE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).it_type = *val_; }
			else if (memb == BOT_STMT_CTYPES) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).ic_type = *val_; }
			else if (memb == BOT_STMT_CONT) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).cont.clear(); vec_->at(ele).cont.append(val_->c_str()); }
			else if (memb == BOT_STMT_DBNAME) { std::string* val_ = reinterpret_cast<std::string*>(val); size_t siz = 0; vec_->at(ele).dbname.clear(); vec_->at(ele).dbname.append(val_->c_str()); }
			else if (memb == BOT_STMT_DBALIAS) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).dbalias.clear(); vec_->at(ele).dbalias.append(val_->c_str()); }
			else if (memb == BOT_STMT_OPTS) { sint* val_ = reinterpret_cast<sint*>(val); size_t siz = 0; while (siz < sizeof(vec_->at(ele).opts)) { val_[siz] = vec_->at(ele).opts[siz]; siz++; } }
			else if (memb == BOT_STMT_SPEC) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).spec = *val_; }
			else if (memb == BOT_STMT_RLIM) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).rlim = *val_; }
			else if (memb == BOT_STMT_TARG) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).targ = *val_; }
			else if (memb == BOT_STMT_ACT) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).act = *val_; }
			else if (memb == BOT_STMT_OSPEC) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).ospec = *val_; }
			else if (memb == BOT_STMT_IFEX) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).ifex = *val_; }
			else if (memb == BOT_STMT_COLS) { std::vector <std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).cols.clear(); while (siz < val_->size()) { vec_->at(ele).cols.push_back(val_->at(siz)); siz++; } }
			else if (memb == BOT_STMT_VALS) { std::vector <std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).vals.clear(); while (siz < val_->size()) { vec_->at(ele).vals.push_back(val_->at(siz)); siz++; } }
			else if (memb == BOT_STMT_CONDS) { std::vector <std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).conds.clear(); while (siz < val_->size()) { vec_->at(ele).conds.push_back(val_->at(siz)); siz++; } }
			else if (memb == BOT_STMT_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_STMT_AN) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).an = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<bot_port*> *vec_ = 0, sint ele = -1, bot_port* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<bot_port> *vec_ = 0, bot_port* val = 0) { if (!vec_ || !val) { return -1; } if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<bot_port> *vec_ = 0, sint ele = -1, bot_port* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<bot_port> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PORT_MAX)
		{
			if (memb == BOT_PORT_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_PORT_STP) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).stype = *val_; }
			else if (memb == BOT_PORT_PTN) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).portn = *val_; }
			else if (memb == BOT_PORT_RPT) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).rport = *val_; }
			else if (memb == BOT_PORT_PCL) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).proto = *val_; }
			else if (memb == BOT_PORT_SOP) { std::vector <BOT_SOPT>* vp = reinterpret_cast<std::vector<BOT_SOPT>*>(val); size_t siz = 0; vec_->at(ele).sopts.clear(); while (siz < vp->size()) { vec_->at(ele).sopts.push_back(vp->at(siz)); siz++; } }
			else if (memb == BOT_PORT_XCL) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).xcl = *val_; }
			else if (memb == BOT_PORT_IPS) { carr_64* val_ = reinterpret_cast<carr_64*>(val); memcpy((void*)&vec_->at(ele).ipstr, val, sizeof(carr_64)); }
			else if (memb == BOT_PORT_OPS) { carr_64* val_ = reinterpret_cast<carr_64*>(val); memcpy((void*)&vec_->at(ele).oipstr, val, sizeof(carr_64)); }
#ifdef _WIN32
			else if (memb == BOT_PORT_SCK) { SOCKET* val_ = reinterpret_cast<SOCKET*>(val); vec_->at(ele).sck = *val_; }
#else
			else if (memb == BOT_PORT_SCK) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).sck = *val_; }
#endif
			else if (memb == BOT_PORT_KYA) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).key_a = *val_; }
			else if (memb == BOT_PORT_BDP) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).bndp = *val_; }
			else if (memb == BOT_PORT_SIG) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).signal = *val_; }
			else if (memb == BOT_PORT_OAD) { sockaddr_storage* val_ = reinterpret_cast<sockaddr_storage*>(val); vec_->at(ele).oaddr = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<bot_plug*> *vec_ = 0, sint ele = -1, bot_plug* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<bot_plug> *vec_ = 0, bot_plug* val = 0) { if (!vec_ || !val) { return -1; } if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<bot_plug> *vec_ = 0, sint ele = -1, bot_plug* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<bot_plug> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PLUG_MAX)
		{
			if (memb == BOT_PLUG_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_PLUG_ERR) { carr_256* val_ = reinterpret_cast<carr_256*>(val); memcpy((void*)&vec_->at(ele).emsg, val, sizeof(carr_256)); }
			else if (memb == BOT_PLUG_SRV) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).isserv = *val_; }
			else if (memb == BOT_PLUG_CON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).con = *val_; }
			else if (memb == BOT_PLUG_QSZ) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).qsiz = *val_; }
			else if (memb == BOT_PLUG_PRT) { bot_port* val_ = reinterpret_cast<bot_port*>(val); vec_->at(ele).prt.Renew(val_); }
			else if (memb == BOT_PLUG_RES) { addrinfo* val_ = reinterpret_cast<addrinfo*>(val); vec_->at(ele).res = val_; }
			else if (memb == BOT_PLUG_PTR) { addrinfo* val_ = reinterpret_cast<addrinfo*>(val); vec_->at(ele).ptr = val_; }
			else if (memb == BOT_PLUG_HNT) { addrinfo* val_ = reinterpret_cast<addrinfo*>(val); vec_->at(ele).hints = *val_; }
			else if (memb == BOT_PLUG_URL) { carr_512* val_ = reinterpret_cast<carr_512*>(val); memcpy((void*)&vec_->at(ele).url, val, sizeof(carr_512)); }
			else if (memb == BOT_PLUG_ORL) { carr_512* val_ = reinterpret_cast<carr_512*>(val); memcpy((void*)&vec_->at(ele).ourl, val, sizeof(carr_512)); }
			else if (memb == BOT_PLUG_FAM) { carr_8* val_ = reinterpret_cast<carr_8*>(val); memcpy((void*)&vec_->at(ele).ifam, val, sizeof(carr_8)); }
			else if (memb == BOT_PLUG_SVC) { carr_64* val_ = reinterpret_cast<carr_64*>(val); memcpy((void*)&vec_->at(ele).servc, val, sizeof(carr_64)); }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<bot_proc*> *vec_ = 0, sint ele = -1, bot_proc* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<bot_proc> *vec_ = 0, bot_proc* val = 0) { if (!vec_ || !val) { return -1; } if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<bot_proc> *vec_ = 0, sint ele = -1, bot_proc* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<bot_proc> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PROC_MAX)
		{
			if (memb == BOT_PROC_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_PROC_PID) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).pid = *val_; }
			else if (memb == BOT_PROC_NM) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).anm.clear(); vec_->at(ele).anm.append(val_->c_str()); }
#ifdef _WIN32
			else if (memb == BOT_PROC_SIN) { STARTUPINFOA* val_ = reinterpret_cast<STARTUPINFOA*>(val); memcpy((void*)&vec_->at(ele).sinfo, (void*)val_, sizeof(STARTUPINFOA)); }
			else if (memb == BOT_PROC_PIN) { PROCESS_INFORMATION* val_ = reinterpret_cast<PROCESS_INFORMATION*>(val); memcpy((void*)&vec_->at(ele).pinfo, (void*)val_, sizeof(PROCESS_INFORMATION)); }
#else
			else if (memb == BOT_PROC_SIN) { slint* val_ = reinterpret_cast<slint*>(val); memcpy((void*)vec_->at(ele).sinfo, (void*)val_, sizeof(slint) * 21); }
			else if (memb == BOT_PROC_PIN) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).pinfo = *val_; }
#endif
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SVIV(std::vector<bot_proc_m*> *vec_ = 0, sint ele = -1, bot_proc_m* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SVIV(std::vector<bot_proc_m> *vec_ = 0, bot_proc_m* val = 0) { if (!vec_ || !val) { return -1; } if (val->lid < 0) { return -1; } sint ret = -1; if (val->lid < (sint)vec_->size()) { vec_->at((size_t)(val->lid)).Renew(val); ret = val->lid; } return ret; }
	sint SVIV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1, bot_proc_m* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			vec_->at(ele).Renew(val);
			ret = ele;
		}
		return ret;
	}
	sint SMIV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PROC_MAX)
		{
			if (memb == BOT_PROC_LID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_PROC_NM) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).anm.clear(); vec_->at(ele).anm.append(val_->c_str()); }
			else if (memb == BOT_PROC_PID) { slint* val_ = reinterpret_cast<slint*>(val); vec_->at(ele).pid = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint PTM(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_DB_MAX)
		{
			if (memb == BOT_DB_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_DB_TABLES)
			{
				if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);
					std::string str;
					str.append(val_);
					vec_->at(ele).tables.push_back(str);
				}
				else if (opt==3)
				{
					std::vector<std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val);
					size_t siz = 0;

					while (siz < val_->size())
					{
						vec_->at(ele).tables.push_back(val_->at(siz));
						siz++;
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_DB_COLUMNS)
			{
				if (opt == 2)
				{
					std::vector<std::vector<std::string>>* val_ = reinterpret_cast<std::vector<std::vector<std::string>>*>(val);
					vec_->at(ele).columns.push_back(*val_);
				}
				else if (opt==3)
				{
					std::vector<std::vector<std::vector<std::string>>>* val_ = reinterpret_cast<std::vector<std::vector<std::vector<std::string>>>*>(val);
					size_t siz = 0;

					while (siz < val_->size())
					{
						vec_->at(ele).columns.push_back(val_->at(siz));
						siz++;
					}
				}
				else {}
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_DB_MAX)
		{
			if (memb == BOT_DB_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_DB_TABLES)
			{
				size_t* val_ = reinterpret_cast<size_t*>(val);
				vec_->at(ele).tsiz += *val_;
				ret = ele;
			}
			else if (memb == BOT_DB_COLUMNS)
			{
				size_t* val_ = reinterpret_cast<size_t*>(val);
				vec_->at(ele).csiz += *val_;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_C_MAX)
		{
			if (memb == BOT_C_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_L_LOGIN)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastlogin.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastlogin.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_L_DATE)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).logindate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).logindate.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_LFL)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).last_failed_login.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).last_failed_login.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_LAST_E)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastexchange.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastexchange.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_C_MAX)
		{
			if (memb == BOT_C_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_L_LOGIN)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastlogin.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastlogin.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_L_DATE)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).logindate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).logindate.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_LFL)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).last_failed_login.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).last_failed_login.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_LAST_E)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastexchange.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).lastexchange.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_LOG_MAX)
		{
			if (memb == BOT_LOG_T)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).logtitle.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).logtitle.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_LOG_S_DATE)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).startdate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).startdate.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_LOG_Q)
			{
				if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);
					std::string str;
					str.append(val_);
					vec_->at(ele).log_q.push_back(str);
				}
				else if (opt == 3)
				{
					std::vector<std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val);

					for (size_t siz = 0; siz < val_->size(); siz++)
					{
						vec_->at(ele).log_q.push_back(val_->at(siz));
					}
				}
				else {}
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_LOG_MAX)
		{
			if (memb == BOT_LOG_T)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).logtitle.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).logtitle.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_LOG_S_DATE)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).startdate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).startdate.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_LOG_Q)
			{
				size_t* val_ = reinterpret_cast<size_t*>(val);
				vec_->at(ele).lsiz += *val_;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FS_MAX)
		{
			if (memb == BOT_FS_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_FP)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).path.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).path.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_FT)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).type.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).type.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_STATE)
			{
				bot_fstate* val_ = reinterpret_cast<bot_fstate*>(val);
				vec_->at(ele).fst.comb(val_);
				ret = ele;
			}
			else if (memb == BOT_FS_CRSV)
			{
				if (opt == 2)
				{
					BOT_CRS* val_ = reinterpret_cast<BOT_CRS*>(val);

					if (val_)
					{
						vec_->at(ele).SetCrs(val_);
					}
					ret = ele;
				}
				else if (opt == 3)
				{
					std::vector<BOT_CRS>* val_ = reinterpret_cast<std::vector<BOT_CRS>*>(val);

					if (val_)
					{
						if (!val_->empty())
						{
							for (uint x = 0; x < val_->size(); x++)
							{
								vec_->at(ele).SetCrs(&val_->at(x));
							}
						}
					}
					ret = ele;
				}
				else {}
			}
			else if (memb == BOT_FS_SELV)
			{
				ret = ele;
			}
			else if (memb == BOT_FS_DAT)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						size_t len = bot_strlen(val_);
						size_t xret = vec_->at(ele).Alloc(len);
						
						if (xret)
						{
							ret = ele;
						}
					}
				}
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FS_MAX)
		{
			if (memb == BOT_FS_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_FP)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).path.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).path.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_FT)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).type.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).type.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_STATE)
			{
				bot_fstate* val_ = reinterpret_cast<bot_fstate*>(val);
				vec_->at(ele).fst.comb(val_);
				ret = ele;
			}
			else if (memb == BOT_FS_CRSV)
			{
				if (opt == 2)
				{
					BOT_CRS* val_ = reinterpret_cast<BOT_CRS*>(val);

					if (val_)
					{
						vec_->at(ele).SetCrs(val_);
					}
					ret = ele;
				}
				else if (opt == 3)
				{
					std::vector<BOT_CRS>* val_ = reinterpret_cast<std::vector<BOT_CRS>*>(val);

					if (val_)
					{
						if (!val_->empty())
						{
							for (uint x = 0; x < val_->size(); x++)
							{
								vec_->at(ele).SetCrs(&val_->at(x));
							}
						}
					}
					ret = ele;
				}
				else {}
			}
			else if (memb == BOT_FS_SELV)
			{
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint PTM(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_TTS_MAX)
		{
			if (memb == BOT_TTS_TNAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).thread_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).thread_name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	sint PTM(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_TTS_MAX)
		{
			if (memb == BOT_TTS_TNAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).thread_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).thread_name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	sint PTM(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < HMTX_MAX)
		{
			if (memb == HMTX_MEMS)
			{
				if (!opt)
				{
					sint* val_ = (sint*)val;
					vec_->at(ele).h_mems.push_back(*val_);
				}
				else if (opt == 3)
				{
					std::vector<sint>* val_ = reinterpret_cast<std::vector<sint>*>(val);
					size_t siz = 0;

					while (siz < val_->size())
					{
						vec_->at(ele).h_mems.push_back(val_->at(siz));
						siz++;
					}
				}
				else {}
				ret = ele;
			}
		}
		return ret;
	}
	sint PTM(std::vector<bot_port> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
	{
		if (!vec_ || ele < 0 || opt < 0 || !val)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PORT_MAX)
		{
			if (memb == BOT_PORT_SOP)
			{
				if (!opt)
				{
					BOT_SOPT* val_ = reinterpret_cast<BOT_SOPT*>(val);

					if (val_)
					{
						vec_->at(ele).sopts.push_back(*val_);
					}
				}
				else if (opt == 3)
				{
					std::vector<BOT_SOPT>* val_ = reinterpret_cast<std::vector<BOT_SOPT>*>(val);

					if (val_)
					{
						size_t siz = 0;

						while (siz < val_->size())
						{
							vec_->at(ele).sopts.push_back(val_->at(siz));
							siz++;
						}
					}
				}
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	sint CFV(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).carr, vec_->at(siz).carr)) { bot_strclr(vec_->at(siz).carr); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<u_char> *vec_ = 0, u_char val = UCHAR_MAX, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)&vec_->at(siz), (void*)&val, sizeof(vec_->at(siz)))) { vec_->at(siz) = UCHAR_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<void*> *vec_ = 0, void* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp(vec_->at(siz),val,sizeof(vec_->at(siz)))) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == *val) { vec_->at(siz) = vtclr; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<sint> *vec_ = 0, sint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<slint> *vec_ = 0, slint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT32_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<sllint> *vec_ = 0, sllint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT64_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<uint> *vec_ = 0, uint val = UINT_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<ulint> *vec_ = 0, ulint val = UINT32_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT32_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<ullint> *vec_ = 0, ullint val = UINT64_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT64_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<float> *vec_ = 0, float* fp = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == *fp) { vec_->at(siz) = 0.0f; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<c_char*> *vec_ = 0, c_char* mid = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<std::string> *vec_ = 0, std::string* mid = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid->c_str())) { vec_->at(siz).clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<MICSYM> *vec_ = 0, MICSYM* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)&val->sym, (void*)&vec_->at(siz).sym, sizeof(u_char))) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<MACSYM> *vec_ = 0, MACSYM* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!vsymcmp(&val->cons, &vec_->at(siz).cons)) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<DB_CONN*> *vec_ = 0, DB_CONN* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == val->lid) { vec_->at(siz)->Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } } siz++; } return ret; }
	sint CFV(std::vector<BOTF_CONN*> *vec_ = 0, BOTF_CONN* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == val->lid) { vec_->at(siz)->Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } } siz++; } return ret; }
	sint CFV(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) {vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<TINFO> *vec_ = 0, TINFO* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<lok_req> *vec_ = 0, lok_req* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<bot_port> *vec_ = 0, bot_port* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<bot_plug> *vec_ = 0, bot_plug* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<bot_proc> *vec_ = 0, bot_proc* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<bot_proc_m> *vec_ = 0, bot_proc_m* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->logtitle.c_str(), val->logtitle.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_FILE*> *vec_ = 0, BOT_FILE* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->thread_name.c_str(), val->thread_name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }

	sint CEFV(std::vector<carr_2> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_4> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_8> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_16> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_32> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_64> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_128> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_256> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_512> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_1024> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_2048> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<carr_4096> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { bot_strclr(vec_->at(ele).carr); ret = ele; } return ret; }
	sint CEFV(std::vector<_char*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<_char> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = '\0'; ret = ele; } return ret; }
	sint CEFV(std::vector<u_char> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UCHAR_MAX; ret = ele; } return ret; }
	sint CEFV(std::vector<void*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = vtclr; ret = ele; } return ret; }
	sint CEFV(std::vector<sint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT_MIN; ret = ele; } return ret; }
	sint CEFV(std::vector<slint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT32_MIN; ret = ele; } return ret; }
	sint CEFV(std::vector<sllint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT64_MIN; ret = ele; } return ret; }
	sint CEFV(std::vector<uint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT_MAX; ret = ele; } return ret; }
	sint CEFV(std::vector<ulint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT32_MAX; ret = ele; } return ret; }
	sint CEFV(std::vector<ullint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT64_MAX; ret = ele; } return ret; }
	sint CEFV(std::vector<float> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0.0f; ret = ele; } return ret; }
	sint CEFV(std::vector<c_char*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = ""; ret = ele; } return ret; }
	sint CEFV(std::vector<std::string> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).clear(); ret = ele; } return ret; }
	sint CEFV(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CEFV(std::vector<DB_CONN*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele)->Clear(); ret = ele; } return ret; }
	sint CEFV(std::vector<BOTF_CONN*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele)->Clear(); ret = ele; } return ret; }
	sint CEFV(std::vector<MICSYM> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CEFV(std::vector<MACSYM> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CEFV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	
	sint CMV(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FLD_MAX)
		{
			if (memb == BOT_FLD_FID)
			{
				vec_->at(ele).fid = -1;
				ret = ele;
			}
			else if (memb == BOT_FLD_ORD)
			{
				vec_->at(ele).ord = -1;
				ret = ele;
			}
			else if (memb == BOT_FLD_BTO)
			{
				vec_->at(ele).bto = -1;
				ret = ele;
			}
			else if (memb == BOT_FLD_IHM)
			{
				vec_->at(ele).is_home = false;
				ret = ele;
			}
			else if (memb == BOT_FLD_FLD)
			{
				vec_->at(ele).fld.clear();
				ret = ele;
			}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_DB ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_DB_MAX)
		{
			if (memb == BOT_DB_NAME)
			{
				vec_->at(ele).name.clear();
				ret = ele;
			}
			else if (memb == BOT_DB_TABLES)
			{
				vec_->at(ele).tables.clear();
				ret = ele;
			}
			else if (memb == BOT_DB_COLUMNS)
			{
				vec_->at(ele).columns.clear();
				ret = ele;
			}
			else if (memb == BOT_DB_EXISTS)
			{
				vec_->at(ele).exists = -1;
				ret = ele;
			}
			else if (memb == BOT_DB_FELE)
			{
				vec_->at(ele).file_ele = -1;
				ret = ele;
			}
			else if (memb == BOT_DB_OMODE)
			{
				vec_->at(ele).omode = -1;
				ret = ele;
			}
			else if (memb == BOT_DB_CONN)
			{
				vec_->at(ele).connected = false;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_DB_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_DB_MAX)
		{
			if (memb == BOT_DB_NAME)
			{
				vec_->at(ele).name.clear();
				ret = ele;
			}
			else if (memb == BOT_DB_TABLES)
			{
				vec_->at(ele).tsiz = UINT_MAX;
				ret = ele;
			}
			else if (memb == BOT_DB_COLUMNS)
			{
				vec_->at(ele).csiz = UINT_MAX;
				ret = ele;
			}
			else if (memb == BOT_DB_EXISTS)
			{
				vec_->at(ele).exists = -1;
				ret = ele;
			}
			else if (memb == BOT_DB_FELE)
			{
				vec_->at(ele).file_ele = -1;
				ret = ele;
			}
			else if (memb == BOT_DB_OMODE)
			{
				vec_->at(ele).omode = -1;
				ret = ele;
			}
			else if (memb == BOT_DB_CONN)
			{
				vec_->at(ele).connected = false;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_CLIENT ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_C_MAX)
		{
			if (memb == BOT_C_NAME)
			{
				vec_->at(ele).name.clear();
				ret = ele;
			}
			else if (memb == BOT_C_L_LOGIN)
			{
				vec_->at(ele).lastlogin.clear();
				ret = ele;
			}
			else if (memb == BOT_C_L_DATE)
			{
				vec_->at(ele).logindate.clear();
				ret = ele;
			}
			else if (memb == BOT_C_LFL)
			{
				vec_->at(ele).last_failed_login.clear();
				ret = ele;
			}
			else if (memb == BOT_C_LAST_E)
			{
				vec_->at(ele).lastexchange.clear();
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_CLIENT_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_C_MAX)
		{
			if (memb == BOT_C_NAME)
			{
				vec_->at(ele).name.clear();
				ret = ele;
			}
			else if (memb == BOT_C_L_LOGIN)
			{
				vec_->at(ele).lastlogin.clear();
				ret = ele;
			}
			else if (memb == BOT_C_L_DATE)
			{
				vec_->at(ele).logindate.clear();
				ret = ele;
			}
			else if (memb == BOT_C_LFL)
			{
				vec_->at(ele).last_failed_login.clear();
				ret = ele;
			}
			else if (memb == BOT_C_LAST_E)
			{
				vec_->at(ele).lastexchange.clear();
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_LOGDET ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_LOG_MAX)
		{
			if (memb == BOT_LOG_T)
			{
				vec_->at(ele).logtitle.clear();
				ret = ele;
			}
			else if (memb == BOT_LOG_S_DATE)
			{
				vec_->at(ele).startdate.clear();
				ret = ele;
			}
			else if (memb == BOT_LOG_Q)
			{
				vec_->at(ele).log_q.clear();
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_LOGDET_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_LOG_MAX)
		{
			if (memb == BOT_LOG_T)
			{
				vec_->at(ele).logtitle.clear();
				ret = ele;
			}
			else if (memb == BOT_LOG_S_DATE)
			{
				vec_->at(ele).startdate.clear();
				ret = ele;
			}
			else if (memb == BOT_LOG_Q)
			{
				vec_->at(ele).lsiz = 0;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FS_MAX)
		{
			if (memb == BOT_FS_NAME)
			{
				vec_->at(ele).name.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_FP)
			{
				vec_->at(ele).path.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_FT)
			{
				vec_->at(ele).type.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_DAT)
			{
				vec_->at(ele).ClearDat();
				ret = ele;
			}
			else if (memb == BOT_FS_OMODE)
			{
				vec_->at(ele).omode = -1;
				ret = ele;
			}
			else if (memb == BOT_FS_STATE)
			{
				vec_->at(ele).fst.Clear();
				ret = ele;
			}
			else if (memb == BOT_FS_CRSV)
			{
				vec_->at(ele).crsv.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_SELV)
			{
				vec_->at(ele).selv.clear();
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_FILE_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint CMV(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_FS_MAX)
		{
			if (memb == BOT_FS_NAME)
			{
				vec_->at(ele).name.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_FP)
			{
				vec_->at(ele).path.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_FT)
			{
				vec_->at(ele).type.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_DAT)
			{
				vec_->at(ele).datp = 0;
				vec_->at(ele).dsiz = 1;
				ret = ele;
			}
			else if (memb == BOT_FS_OMODE)
			{
				vec_->at(ele).omode = -1;
				ret = ele;
			}
			else if (memb == BOT_FS_STATE)
			{
				vec_->at(ele).fst.Clear();
				ret = ele;
			}
			else if (memb == BOT_FS_CRSV)
			{
				vec_->at(ele).crsv.clear();
				vec_->at(ele).crss = 0;
				ret = ele;
			}
			else if (memb == BOT_FS_SELV)
			{
				vec_->at(ele).sels = 0;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<TINFO> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_TTS_MAX)
		{
			if (memb == BOT_TTS_TNAME)
			{
				vec_->at(ele).thread_name.clear();
				ret = ele;
			}
			else if (memb == BOT_TTS_VALS)
			{
				vec_->at(ele).vals.clear();
			}
			else if (memb == BOT_TTS_SIG)
			{
				vec_->at(ele).sig = 0;
			}
			else if (memb == BOT_TTS_TID)
			{
				vec_->at(ele).tid = -1;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<TINFO_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_TTS_MAX)
		{
			if (memb == BOT_TTS_TNAME)
			{
				vec_->at(ele).thread_name.clear();
				ret = ele;
			}
			else if (memb == BOT_TTS_VALS)
			{
				vec_->at(ele).vals.clear();
			}
			else if (memb == BOT_TTS_SIG)
			{
				vec_->at(ele).sig = 0;
			}
			else if (memb == BOT_TTS_TID)
			{
				vec_->at(ele).tid = -1;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).lid = -1; vec_->at(ele).w_mtx = -1; ret = ele; } return ret; }
	sint CEFV(std::vector<lok_req> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<lok_req> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_REQ_MAX)
		{
			switch (memb)
			{
			case BOT_REQ_LID:
			{
				vec_->at(ele).lid = -1;
				break;
			}
			case BOT_REQ_FID:
			{
				vec_->at(ele).fid = -1;
				break;
			}
			case BOT_REQ_GMTX:
			{
				vec_->at(ele).gmtx = -1;
				break;
			}
			case BOT_REQ_ELE:
			{
				vec_->at(ele).ele = -1;
				break;
			}
			case BOT_REQ_META:
			{
				vec_->at(ele).is_meta = -1;
				break;
			}

			default:
			{
				break;
			}
			}
		}
		return ret;
	}
	sint CEFV(std::vector<bot_port> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<bot_port> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PORT_MAX)
		{
			if (memb == BOT_PORT_LID)
			{
				vec_->at(ele).lid = -1;
				ret = ele;
			}
			else if (memb == BOT_PORT_STP)
			{
				vec_->at(ele).stype = -1;
				ret = ele;
			}
			else if (memb == BOT_PORT_PTN)
			{
				vec_->at(ele).portn = -1;
				ret = ele;
			}
			else if (memb == BOT_PORT_RPT)
			{
				vec_->at(ele).rport = -1;
				ret = ele;
			}
			else if (memb == BOT_PORT_PCL)
			{
				vec_->at(ele).proto = -1;
				ret = ele;
			}
			else if (memb == BOT_PORT_SOP)
			{
				vec_->at(ele).sopts.clear();
				ret = ele;
			}
			else if (memb == BOT_PORT_XCL)
			{
				vec_->at(ele).xcl = false;
				ret = ele;
			}
			else if (memb == BOT_PORT_IPS)
			{
				bot_strclr(vec_->at(ele).ipstr.carr);
				ret = ele;
			}
			else if (memb == BOT_PORT_OPS)
			{
				bot_strclr(vec_->at(ele).ipstr.carr);
				ret = ele;
			}
#ifdef _WIN32
			else if (memb == BOT_PORT_SCK)
			{
				vec_->at(ele).sck = INVALID_SOCKET;
				ret = ele;
			}
#else
			else if (memb == BOT_PORT_SCK)
			{
				vec_->at(ele).sck = -1;
				ret = ele;
			}
#endif
			else if (memb == BOT_PORT_KYA)
			{
				vec_->at(ele).key_a = 0;
				ret = ele;
			}
			else if (memb == BOT_PORT_BDP)
			{
				vec_->at(ele).bndp = false;
				ret = ele;
			}
			else if (memb == BOT_PORT_SIG)
			{
				vec_->at(ele).signal = 0;
				ret = ele;
			}
			else if (memb == BOT_PORT_OAD)
			{
				memset((void*)&vec_->at(ele).oaddr, 0, sizeof(sockaddr_storage));
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<bot_plug> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<bot_plug> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PLUG_MAX)
		{
			if (memb == BOT_PLUG_LID)
			{
				vec_->at(ele).lid = -1;
				ret = ele;
			}
			else if (memb == BOT_PLUG_ERR)
			{
				bot_strclr(vec_->at(ele).emsg.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_SRV)
			{
				vec_->at(ele).isserv = false;
				ret = ele;
			}
			else if (memb == BOT_PLUG_CON)
			{
				vec_->at(ele).con = -1;
				ret = ele;
			}
			else if (memb == BOT_PLUG_QSZ)
			{
				vec_->at(ele).qsiz = 0;
				ret = ele;
			}
			else if (memb == BOT_PLUG_PRT)
			{
				vec_->at(ele).prt.Clear();
				ret = ele;
			}
			else if (memb == BOT_PLUG_RES)
			{
				vec_->at(ele).res = NULL;
				ret = ele;
			}
			else if (memb == BOT_PLUG_PTR)
			{
				vec_->at(ele).ptr = NULL;
				ret = ele;
			}
			else if (memb == BOT_PLUG_HNT)
			{
				memset((void*)&vec_->at(ele).hints, 0, sizeof(addrinfo));
				ret = ele;
			}
			else if (memb == BOT_PLUG_URL)
			{
				bot_strclr(vec_->at(ele).url.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_ORL)
			{
				bot_strclr(vec_->at(ele).ourl.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_FAM)
			{
				bot_strclr(vec_->at(ele).ifam.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_SVC)
			{
				bot_strclr(vec_->at(ele).servc.carr);
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<bot_proc> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) {vec_->at(ele).Clear(); vec_->at(ele).Close(); ret = ele; } return ret; }
	sint CMV(std::vector<bot_proc> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PROC_MAX)
		{
			if (memb == BOT_PROC_LID)
			{
				vec_->at(ele).lid = -1;
				ret = ele;
			}
			else if (memb == BOT_PROC_PID)
			{
				vec_->at(ele).pid = 0;
				ret = ele;
			}
			else if (memb == BOT_PROC_NM)
			{
				vec_->at(ele).anm.clear();
				ret = ele;
			}
			else if (memb == BOT_PROC_SIN)
			{
#ifdef _WIN32
				memset((void*)&vec_->at(ele).sinfo, 0, sizeof(STARTUPINFOA));
#else
				memset((void*)vec_->at(ele).sinfo, 0, sizeof(slint) * 21);
#endif
				ret = ele;
			}
			else if (memb == BOT_PROC_PIN)
			{
#ifdef _WIN32
				CloseHandle(vec_->at(ele).pinfo.hThread);
				CloseHandle(vec_->at(ele).pinfo.hProcess);
				memset((void*)&vec_->at(ele).pinfo, 0, sizeof(PROCESS_INFORMATION));
#else
				vec_->at(ele).pinfo = 0;
#endif
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint CMV(std::vector<bot_proc_m> *vec_ = 0, sint ele = -1, sint memb = -1)
	{
		if (!vec_ || ele < 0)
		{
			return -1;
		}

		sint ret = -1;

		if (ele < (sint)vec_->size() && memb > -1 && memb < BOT_PROC_MAX)
		{
			if (memb == BOT_PROC_LID)
			{
				vec_->at(ele).lid = -1;
				ret = ele;
			}
			else if (memb == BOT_PROC_NM)
			{
				vec_->at(ele).anm.clear();
				ret = ele;
			}
			else if (memb == BOT_PROC_PID)
			{
				vec_->at(ele).pid = 0;
				ret = ele;
			}
			else {}
		}
		return ret;
	}
	sint CEFV(std::vector<BOT_DB*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<BOT_CLIENT*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<BOT_LOGDET*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<BOT_FILE*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<TINFO*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint CEFV(std::vector<HELD_MTX*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }

	sint CLNV(std::vector<carr_2> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_4> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_8> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_16> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_32> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_64> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_128> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_256> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_512> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_1024> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_2048> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_4096> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!bot_strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (bot_strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!bot_strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<_char*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<_char> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == '\0') { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != '\0') { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == '\0') { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<u_char> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UCHAR_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UCHAR_MAX) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == UCHAR_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<void*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) =vec_->at(y); sint z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == vtclr) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != vtclr) { vec_->at(x) = vec_->at(y); sint z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == vtclr) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<sint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT_MIN) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<slint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT32_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT32_MIN) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT32_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<sllint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT64_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT64_MIN) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT64_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<uint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT_MAX) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<ulint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT32_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT32_MAX) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT32_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<ullint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT64_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT64_MAX) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT64_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<float> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == DBL_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != DBL_MIN) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == DBL_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<c_char*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } else { if (!strlen(vec_->at(x))) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } } sint siz = vec_->size() - 1; while (siz > -1) { if (!strcmp(vec_->at(siz), "") || !strlen(vec_->at(siz))) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<std::string> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).empty()) { for (size_t y = x + 1; y < vec_->size(); y++) { if (!vec_->at(y).empty()) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = vec_->size() - 1; while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), "") || vec_->at(siz).empty()) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<MICSYM> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).id < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).id > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).id < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<MACSYM> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).id < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).id > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).id < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_DB> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<DB_CONN*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) = vec_->at(y); sint z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid < 0) { vec_->pop_back(); } else { siz = -1; } } else { vec_->pop_back(); } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOTF_CONN*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) = vec_->at(y); sint z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid < 0) { vec_->pop_back(); } else { siz = -1; } } else { vec_->pop_back(); } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_CLIENT> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_LOGDET> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_FILE> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<TINFO> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<HELD_MTX> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0 && vec_->at(x).h_mems.empty() && vec_->at(x).m_mems.empty()) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0 && vec_->at(siz).h_mems.empty() && vec_->at(siz).m_mems.empty()) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<lok_req> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_DB*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_CLIENT*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_LOGDET*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_FILE*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<TINFO*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<HELD_MTX*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SVIV(vec_, (sint)x, vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_DB_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_CLIENT_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_LOGDET_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_FILE_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<TINFO_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_STMT> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<bot_port> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<bot_plug> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<BOT_FLD> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).fid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).fid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).fid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<bot_proc> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<bot_proc_m> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SVIV(vec_, (sint)x, &vec_->at(y)); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }

	void SetTClr(std::chrono::steady_clock::time_point* nt = 0) { if (!nt) { vtclr = std::chrono::steady_clock::now(); } else { vtclr = *nt; } }
	void SetSTool(STool* nstool = 0) { if (!nstool) { return; } stool = nstool; }

private:

	std::chrono::steady_clock::time_point vtclr;
	STool* stool;
};

// LITEBot

class machine
{	
public:
	
	machine(sint i_debug_lvl = BOT_DEBUG_LVL, sint i_debug_m = BOT_DEBUG_M, sint nlid = -1, c_char* i_name = "", bool logmain = false, bool logmine = false);
	sint LITEBot(carr_256 *ncar_ = 0, sint argc = 0, _char *argv[] = 0);
	
private:

	bool quit;
	bool log_to[2];
	bool req_lock;
	bool boto_file;
	bool mk_thr;
	sint lid;
	sint thr_prio;
	sint debug_lvl;
	sint debug_m; /* debug_m = || (0) == no debug || (1) == debug messages from instances of functions within call stack for Output() are ignored || (2) == debug messages from instances of functions within call stack for Output() are held in queue and prepended with [Q] */
	sint bot_mode;
	float thr_exe_mod;
	std::vector<HELD_MTX> h_mtxs;
	std::string pcn;
	std::string ptn;
	std::string cur_path;
	std::chrono::steady_clock::time_point bot_st;
	STool stool;
	VTool vtool;
	std::vector<BOT_LOGDET> u_logs;
	DB_CONN* d_con_;
	std::vector<BOTF_CONN*> f_con;
	std::vector<lok_req> relocks;
	uint stk_ct;
	bot_strt_syms msy;
	bot_vars mv;
	carr_32 ses_date;
	
	sint GetDebugLevel() { return debug_lvl; }
	sint GetDebugMode() { return debug_m; }

	// Mutex Manip

	sint LockReq();
	sint UnlockReq();
	sint CheqMTXReqs(std::vector<lok_req>* nreqs_ = 0);
	sint UpdMTXPrio();
	sint UpdMTX();
	sint ReqMTX(lok_req* nreq = 0, bool wait = false);
	sint WithdMTXReq(lok_req* nreq = 0);
	sint HasLock(sint g_opt = -1, sint ele = -1, bool is_meta = true);

		/* mutexes for global lists */

	sint LockGMutex(sint g_opt = -1, sint* had_lock = 0, bool sleep_wait = true);
	sint UnlockGMutex(sint g_opt = -1);

		/* locks for elements within global lists */

	sint LockElement(sint g_opt = -1, sint ele = -1, sint* had_lock = 0, bool sleep_wait = true, bool is_meta = true);
	sint UnlockElement(sint g_opt = -1, sint ele = -1, bool is_meta = true);

	// Open/Close Global Objects

	sint OpenObject(sint nobj = -1, sint nele = -1, sint is_meta = -1, sint* omode = 0, sint* r_opt = 0, sint* n_opt = 0);
	sint CloseObject(sint nobj = -1, sint nele = -1, sint is_meta = -1, sint* r_opt = 0, sint* n_opt = 0);

	// Manip Global Lists

	sint PushToVec(void *val_, sint g_opt, bool check = true, bool use_empty = true, bool is_meta = true);
	sint PushToVecEleMem(void *val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, sint v_opt = -1, bool is_meta = true);
	sint GetVecEle(void* val_ = 0, sint g_opt = -1, sint ele = -1, bool is_meta = true);
	sint GetEmptyVecEle(sint g_opt, bool is_meta = true, sint mode = -1);
	sint GetVecEleMem(void* val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true);
	sint SetVecEle(void* val_ = 0, sint g_opt = -1, sint ele = -1, bool cine = false, bool is_meta = true);
	sint SetVecEleMem(void* val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true);
	sint ClearVecEle(sint g_opt = -1, sint ele = -1, bool is_meta = true);
	sint ClearVecEleMem(sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true);
	sint VecSize(sint g_opt = -1, bool is_meta = true);
	sint GetInVec(void* val_, sint g_opt, bool cine = false, bool is_meta = true);
	sint GetElementNames(sint g_opt = -1, std::vector<std::string>* nvec = 0, bool is_meta = true);
	sint GetElementIDs(sint g_opt = -1, std::vector<sint> *nvec = 0, bool is_meta = true);

	// Date / Time 

	sint GetDateTimeMS(_char str_[] = 0, bool form = true);
	sint GetDateTime(_char str_[] = 0, bool form = true);
	sint GetTime(_char str_[] = 0, bool forms = true);
	sint GetTimeMS(_char str_[] = 0, bool forms = true);
	sint GetDate(carr_32* str_ = 0, bool form = true);
	sllint GetCentSec();

	// Log Functions

	sint SetDBG(sint lv = BOT_DEBUG_LVL, sint m = BOT_DEBUG_M);
	sint GetDBG(sint* lv = 0, sint* m = 0);
	sint UsingLog(_char nm[] = 0);
	sint LogName(sint opt, carr_256* nm = 0, carr_32* dat = 0, bool tomine = false);
	sint LogPut(c_char* msg_ = "", sint option = -1);

	// Runtime Variables

	sint IVAR(c_char* typ = 0, c_char* nm = 0, c_char* val = 0);
	sint IVAR(sint typ = 0, c_char* nm = 0, c_char* val = 0);
	sint PVAR(c_char* nm = 0, ...);
	sint FVAR(c_char* nm = 0);
	sint GVAR(c_char* nm = 0, sint as_t = 0, void* val = 0);
	sint SVAR(c_char* nm = 0, sllint* val = 0);
	sint SVAR(c_char* nm = 0, float* val = 0);
	sint SVAR(c_char* nm = 0, std::string* val = 0);
	sint SVAR(c_char* nm = 0, BOT_ARG* val = 0);
	sint SVAR(c_char* nm = 0, _char* val = 0);
	sint SVAR(c_char* nm = 0, std::vector<sllint>* val = 0);
	sint SVAR(c_char* nm = 0, std::vector<float>* val = 0);
	sint SVAR(c_char* nm = 0, std::vector<std::string>* val = 0);
	sint SVAR(c_char* nm = 0, std::vector<std::vector<_char>>* val = 0);
	sint SVAR(c_char* nm = 0, std::vector<BOT_ARG>* val = 0);
	sint RVAR(c_char* nm = 0);
	sint LVARS(sint n, ...);

	// Commands

	sint Command(std::vector<BOT_ARG>* vec_ = 0);

	// File Directory

	std::string BOTPathS(c_char* spath_ = 0);
	sint BOTPath(std::string* str_ = 0, c_char* spath_ = 0);
	sint BOTOpenDir(c_char* dest_ = 0, DIR** dir_ = 0);
	sint BOTCloseDir(DIR** dir_ = 0);
	sint BOTReadDir(std::vector<BOT_FILE_M>* flds_ = 0, c_char* dest_ = 0);
	sint BOTFindHomeDir();
	sint BOTInitFDir(bool findself = true);

	// File I/O

	sint OutputFileStats(BOT_FILE* file_, sint opt);
	sint BOTFileStr(std::string* str_ = 0, BOT_FILE_M* file_ = 0);
	std::string BOTFileStr(BOT_FILE_M* file_ = 0);
	sint BOTConnMethod(BOT_FILE_M* val_ = 0);
	sint GetOFConn(BOT_FILE_M* val_ = 0, sint* was_open = 0);
	sint GetFConn(BOT_FILE_M* val_ = 0, sint* was_open = 0, slint mt = BOT_FTRY_MAX);
	sint CloseFConn(BOT_FILE_M* xfile_ = 0, bool clear_conn = true);
	sint GetFPad(BOT_FILE_M* val_ = 0, slint mt = BOT_FTRY_MAX);
	sint CloseFPad(BOT_FILE_M* xfile_ = 0);
	sint BOTScanFileSyms(BOT_FILE_M *file_ = 0);
	sint DetSep(BOT_FILE_M* file_ = 0);
	sint BOTRendFileSyms(BOT_FILE_M *file_ = 0);
	sint BOTKnownFormat(BOT_FILE_M* file_ = 0);
	sint BOTDirSep(BOT_FILE_M* file_ = 0);
	sint BOTFileStats(BOT_FILE_M *file_ = 0, bool doscan = false, sint scan_lvl = -1);
	sint BOTCreateFile(BOT_FILE_M* file_ = 0, sint* was_open = 0);
	sint BOTRemoveFile(BOT_FILE_M *xfile_ = 0);
	sint BOTRenameFile(BOT_FILE_M *xfile_ = 0, c_char* nnm = 0);
	sint BOTNewFile(BOT_FILE_M* mfile_ = 0, bool overw = false,  _char* argv = 0);
	sint BOTOpenFile(sint flid = -1, sint *was_open = 0, bool do_scan = false, bool cine = false, bool r_to_st = false, bool dtp = false, _char* dat_ = 0, void* blk = 0);
	sint BOTOpenFile(BOT_FILE_M* mfile_ = 0, sint *was_open = 0, bool do_scan = false, bool cine = false, bool r_to_st = false, bool dtp = false, _char* dat_ = 0, void* blk = 0);
	sint BOTFindInFile(BOT_FILE_M* file_ = 0, bool indat = false, size_t f = 0, size_t t = 0, void* f_ = 0, size_t len = 0);
	sint BOTFileOUT(BOT_FILE_M* file_ = 0, size_t f = 0, bool to_fdat = false, ...);
	sint BOTFileIN(BOT_FILE_M* file_ = 0, bool f_fdat = false, size_t from = -1, size_t to = -1, ...);
	sint BOTFileER(BOT_FILE_M* file_ = 0, bool f_fdat = false, size_t from = -1, size_t to = -1);
	sint BOTCloseFile(sint flid = -1, bool clear_conn = true, bool del = false, bool clear_dat = false);
	sint BOTCloseFile(BOT_FILE_M* xfile_ = 0, bool clear_conn = true, bool del = false, bool clear_dat = false);
	sint BOTSaveFile(BOT_FILE_M* xfile_ = 0, c_char* to_ = 0, bool ow = false);
	sint BotOpenError(sint err_id, std::string* err_str = 0);

	// Sleep Functions

	void Nanosleep(sllint dur = BOT_NANO_REST);
	sllint nsRest(sllint i = (sllint)BOT_NANO_REST, bool keep_mtx = false);
	sllint Rest(sllint i = (sllint)BOT_MILLI_REST, bool keep_mtx = false);

	// Client Functions

	sint GetPCli(BOT_CLIENT* val = 0);
	sint SetPCli(BOT_CLIENT* val = 0);
	sint GetPCliMem(sint mem = -1, void* val = 0);
	sint SetPCliMem(sint mem = -1, void* val = 0);
	sint ClearClient(BOT_CLIENT *c_ = 0) { if (c_) { c_->Clear(); return 0; } return -1; }
	bool GetClientLoggedIn();
	sint SetClientLoggedIn(bool x);	
	sint GetClientByPort(BOT_CLIENT* c_ = 0, _char* addr = 0, sint portn = 0, sint stype = 0);
	// Console I/O Functions

	sint UNRTS();
	sint BOTCOutput(std::string* np = 0);
	sint Output(c_char* op_ = "", sint opt = -1, bool newl = true);
	sint Output(bool newl = true, c_char* op_ = "", ...);
	sint BOTCInput(std::string* np = 0, carr_64* tdata = 0);
	sint Input(c_char* prp = 0, std::string* np = 0, bool itrp = true);
	sint BOTConsole(c_char* prp = 0);
	sint ArgSep(std::vector <BOT_ARG>* ret_ = 0, std::vector<BOT_VAR_T>* uvars = 0, bool ksep = false, size_t f = 0, size_t t = 0, c_char* val = 0, ...);
	sint ArgSep(std::vector <std::string>* ret_ = 0, std::vector<BOT_VAR_T>* uvars = 0, bool ksep = false, size_t f = 0, size_t t = 0, c_char* val = 0, ...);
	sint ArgRep(std::string* arg = 0);

	// Str Manip

	std::string CPunc(c_char* i_ = "");
	std::string UCASE(c_char* str_ = "");
	std::string LCASE(c_char* str_ = "");
	std::string EStr(c_char* str_ = "");

	// SQL statement manip

	sint AnalyzeStmt(BOT_STMT *t_ = 0);
	sint FinStmt(sqlite3_stmt** ppstmt = 0);
	sint BQS(BOT_STMT *t_ = 0);
	sint BTS(BOT_STMT *t_ = 0);
	sint BuildStatements(std::vector<BOT_STMT>* stmts_ = 0, BOT_COMMIT *com_ = 0, std::vector<BOT_STMT>* pend_ = 0);

	// Database Functions

	std::string GetError();
	sint FindColumn(c_char *str_ = "", sqlite3_stmt* ppstmt = 0);
	sint GetODBConn(BOT_DB_M *db_ = 0);
	sint GetDBConn(BOT_DB_M* val_ = 0, slint mt = (slint)BOT_FTRY_MAX);
	sint CloseDBConn(BOT_DB_M* db_ = 0);
	sint OpenOpt(sint opt = -1);
	sint OpenDB(sint db_lid = -1, sint x = -1, sint* was_open = 0, sint* fwas_locked = 0, bool r_to_st = true);
	sint OpenDB(BOT_DB_M *db_ = 0, sint x = -1, sint* was_open = 0, sint* fwas_locked = 0, bool r_to_st = false, bool is_verify = false);
	sint CloseDB(sint db_lid = -1, sint* fwas_locked = 0, bool clear_conn = true);
	sint CloseDB(BOT_DB_M* db_ = 0, sint* fwas_locked = 0, bool clear_conn = true);
	sint OpenDBs(std::vector<BOT_DB_M> *dbs_, sint opt = -1, std::vector <sint> *wos_ = 0, std::vector<sint> *fwas_ = 0, std::vector<sint> *lids_ = 0);
	sint CloseDBs(std::vector<BOT_DB_M> *dbs_ = 0, std::vector<sint>* fwas_ = 0);
	sint Query(BOT_STMT* qval_ = 0, sint as_opt = -1);
	sint Commit(BOT_STMT* stmt_ = 0);
	sint Commit(std::vector<BOT_STMT>* stmts_ = 0);
	sint VerifyDatabases();
	sint VerifyDatabase(BOT_DB_M *dbs_ = 0);
	sint VerifyTable(BOT_DB *dbs_ = 0, std::vector<BOT_STMT> *tvec_ = 0, sint x = -1, sint odb = -1);
	sint CreateDatabase(BOT_DB_M *dbs_ = 0);
	sint GetSymbol(MICSYM *sym_ = 0, c_char x_cond_[] = 0, bool maint = false);
	sint GetSymbols(std::vector <MICSYM> *syms_ = 0, c_char x_cond_[] = 0, bool maint = false);
	sint AddSymbol(MICSYM* sym_ = 0);
	sint AddSymbols(std::vector <MICSYM> *syms_ = 0);
	sint GetCode(MACSYM* code_ = 0, c_char x_cond_[] = 0, bool maint = false);
	sint GetCode(std::vector<MACSYM>* codes_ = 0, c_char x_cond_[] = 0, bool maint = false);
	sint AddCode(MACSYM *code_ = 0);
	sint AddCode(std::vector<MACSYM > *codes_ = 0);
	sint GetCommand(BOTCOMMAND *Command_ = 0, std::vector<std::string> *conds_ = 0);
	sint GetCommands(std::vector<BOTCOMMAND> *Commands_ = 0, std::vector<std::string> *conds_ = 0);
	sint GetLogin(BOT_CLIENT* c = 0, c_char* str_ = 0);
	sint UpdateAccount(BOT_CLIENT *Client_ = 0);
	sint GetLastAccess(BOT_DB_M *dbs_ = 0, sint *lmo_ = 0, sint *lmo_ns = 0, sint *lma_ = 0, sint *lma_ns = 0);
	sint LastAccessMaintenance(BOT_DB_M *dbs_ = 0);
	sint PushToDBList(BOT_DB *dbs_ = 0);

	// Fork

	sint BOTFork(bot_proc* np = 0, _char* cl = 0, _char* cdir = 0);
	sint BOTUnFork(bot_proc* np = 0, ulint wait = 30000);

	// Monitor Process

	sint BOTMonitor();

	// Start/End Session

	sint BOTStartSession(slint pid = 0);
	std::string BOTSessionName();
	sint BOTSetSessionName(c_char* nnm = 0);
	sint BOTEndSession(slint pid = 0);

	// Network Functions

	sint StartConnection(std::vector<ullint>* vals = 0, sint opt = -1);
	sint CloseConnection(sint stype = -1, sint opt = -1, sint portn = -1);
	//sint PauseConnection(sint stype = -1, sint opt = -1, sint portn = -1);
	//sint UnPauseConnection(sint stype = -1, sint opt = -1, sint portn = -1);
	sint ConnectionStatus(sint stype = -1, sint opt = -1, sint portn = -1);
	slint KeyACGen();
	sint KeyAServR(slint* in = 0);
	sint KeyAServCreateII(slint* in = 0);
	sint KeyAClientProcII(slint* in = 0);
	sint KeyAServRecII(slint* in = 0, slint* prt = 0);
	sint BOTNCon(c_char* addr = 0, c_char* port = "", sint type = -1);
	sint BOTXNCon(c_char* addr = 0, c_char* port = "", sint type = -1);
	sint BanIP(c_char* ipstr = 0, c_char* note = 0);
	sint UnbanIP(c_char* ipstr = 0);
	sint RefBIPS();
	sint AddVPKI(sint stype = -1, size_t len = 0, _char* dat = 0, c_char* addr = 0, c_char* port = 0, _char ack = 0);
	sint AddVPKO(sint stype = -1, size_t len = 0, _char* dat = 0, c_char* addr = 0, c_char* port = 0, _char ack = 0);
	sint VPKO(sint stype = -1);
	sint AddSVPKI(sint stype = -1, size_t len = 0, _char* dat = 0, c_char* addr = 0, c_char* port = 0, _char ack = 0);
	sint AddSVPKO(sint stype = -1, size_t len = 0, _char* dat = 0, c_char* addr = 0, c_char* port = 0, _char ack = 0);
	sint SVPKO(sint stype = -1);
	sint BOTServR(std::vector<ullint>* vals = 0);
	sint BOTServPS(sint stype = -1);
	sint BOTServP(sint stype = -1);

	sint GetVINs(BOT_FILE_M* file_ = 0, c_char* ramp = "", c_char* emp = "", c_char* fdate = "", c_char* ftyp = "", bool as_var = false);
	sint ProcVINList(BOT_FILE_M* file_ = 0, c_char* stmt_ = 0, c_char* ramp = 0, c_char* date = 0, c_char* empno = 0, bool is_errlog = false);

	// Pthreads Functions

	sint StartThread(sint* thr_opt = 0);
	sint SignalThread(_char* thr = 0, sint sign = -1);
	sint ThreadRest(sllint dur = BOT_MILLI_REST, sint qt_lvl = -1);
	sint ThreadEnd(std::vector<ullint>* rvals_ = 0);
	sint PThreadErr(_char in_chr[], sint err);
	sint IncrThreads();
	sint DecrThreads();
	sint GetThreadsCt();
	sint GetThreadQuit(sint qlvl = -1);
	sint SetThreadQuit(sint val = -1);
	sint StopAllThreads();
	sint JoinThread(sint thrid = -1, void* vp_ = 0);
	sint InitThread(TINFO_M *tts_ = 0, sint* ret_ = 0);
	sint InitThreads(std::vector<TINFO_M> *tts_ = 0, std::vector<sint>* rets_ = 0);
	sint CreateThread(TINFO_M* tts_ = 0, sint* ret_ = 0);
	sint FinishThread(TINFO_M* tts_ = 0, sint* ret_ = 0);
	sint MT(std::vector<ullint>* vals = 0);
	sint TM(uint* is_s = 0);
	sint TestThreads(sint num = 0);
	sllint TestThreadIter(sint to_ = (sint)BOT_ITER_TO);
	sllint TestThreadTRat(sint to_ = (sint)BOT_ITER_TO);

	static void* DBMaintenance(void* vp_ = 0);
	static void* LITEBotMaintenance(void* vp_ = 0);
	static void* CodeMaintenance(void* vp_ = 0);
	static void* LogMaintenance(void* vp_ = 0);
	static void* TestThread(void* vp_ = 0);
	static void* ConsoleThread(void* vp_ = 0);
	static void* ScanFileThread(void* vp_ = 0);
	static void* RendFileThread(void* vp_ = 0);
	static void* GIPS(void* vp_ = 0);
	static void* ServR(void* vp_ = 0);
	static void* ServS(void* vp_ = 0);
	static void* ServP(void* vp_ = 0);
	static void* CliThread(void* vp_ = 0);
};

#endif