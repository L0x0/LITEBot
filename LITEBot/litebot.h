#ifndef LITEBOT_H
#define LITEBOT_H

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
#include <iomanip>
#include <fstream>
#include <chrono>
#include <sys/types.h>

//#define _BOT_FOR_ANDR_ 1

#ifdef _WIN32
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
#define BOT_N_STR "0123456789.,"
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

#ifndef BOT_THR_VALS
#define BOT_THR_VALS 10
#else
#if (BOT_THR_VALS > 1024)
#define BOT_THR_VALS 1024
#else
#if (BOT_THR_VALS < 3)
#define BOT_THR_VALS 3
#endif
#endif
#endif

#ifndef BOT_ATT_LIM
#define BOT_ATT_LIM 10
#endif

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

#ifndef BOT_FO_MAX
#define BOT_FO_MAX 5
#endif

#ifndef BOTVEC_LIM
#define BOTVEC_LIM (BOT_STRLEN_MAX - 1)
#endif

#ifndef BOT_OORETS_MAX
#define BOT_OORETS_MAX 2
#endif

#ifndef BOT_OP_OPTS
#define BOT_OP_OPTS 4
#endif

#ifndef BOT_MTX_MAXCT
#define BOT_MTX_MAXCT UINT_MAX
#endif

#ifndef BOT_TERM_WAIT
#define BOT_TERM_WAIT 60000
#endif

#ifndef BOT_LOGREST
#define BOT_LOGREST (BOT_MILLI_REST*1000)
#endif

#ifndef BOT_DBREST
#define BOT_DBREST (BOT_MILLI_REST*2500)
#endif

#ifndef BOT_THRREST
#define BOT_THRREST (BOT_MILLI_REST*500)
#endif

#ifndef BOT_QUITREST
#define BOT_QUITREST (BOT_MILLI_REST*600)
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

#ifndef BOT_CNSREST
#define BOT_CNSREST (BOT_MILLI_REST*10)
#endif

#ifndef BOT_SERVREST
#define BOT_SERVREST (BOT_MILLI_REST*10)
#endif

#ifndef BOT_CLIREST
#define BOT_CLIREST (BOT_MILLI_REST*10)
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

typedef struct bot_ftia
{
	slint a[2];

	bot_ftia(float x = 0.0f)
	{
		if (x != 0.0f)
		{
			a[0] = (slint)x;
			a[1] = (slint)((10 ^ 19) * (x - (float)(a[0])));
		}
		else
		{
			a[0] = a[1] = 0;
		}
	}

}BOT_FTIA;

typedef struct bot_iatf
{
	float a;

	bot_iatf(slint val[2] = 0)
	{
		if (val)
		{
			a = (float)val[0];
			a += (float)(val[1]) * (float)(10 ^ -19);
		}
		else
		{
			a = 0.0f;
		}
	}

}BOT_IATF;

bool bot_sisn(c_char* val = 0, sint slen = 0);
sint bot_shasn(c_char* val = 0, sint slen = 0);
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
void bot_strclr(_char inchr[] = 0);
void bot_ustrclr(u_char inchr[] = 0);
void bot_cstrclr(c_char inchr[] = 0);
void bot_custrclr(cu_char inchr[] = 0);
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
sllint bot_findin(u_char val[] = 0, size_t offs = 0, size_t lim = 0, u_char inv[] = 0);

enum bot_con_val
{
	BOT_F_CON = 0,
	BOT_DB_CON = 1,
	BOT_DIR_CON = 2,
	BOT_I4_CON = 3,
	BOT_I6_CON = 4,
	BOT_E128_CON = 5,
	BOT_E256_CON = 6,
	BOT_MAX_CON = 7
};

enum bot_rtv_vals
{
	BOT_RTV_SINT = 0,
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
	BOT_RTV_REAL = 15,
	BOT_RTV_MICS = 16,
	BOT_RTV_MACS = 17,
	BOT_RTV_SCRPT = 18,
	BOT_RTV_VSINT = 1000,
	BOT_RTV_VSLINT = 1001,
	BOT_RTV_VSLLINT = 1002,
	BOT_RTV_VUINT = 1003,
	BOT_RTV_VULINT = 1004,
	BOT_RTV_VULLINT = 1005,
	BOT_RTV_VCHAR = 1006,
	BOT_RTV_VUCHAR = 1007,
	BOT_RTV_VCCHAR = 1008,
	BOT_RTV_VSTR = 1009,
	BOT_RTV_VREAL = 1010,
	BOT_RTV_VMICS = 1011,
	BOT_RTV_VMACS = 1012,
	BOT_RTV_VSCRPT = 1013,
	BOT_RTV_MAX = 1014
};

typedef struct bot_carr_2
{
	size_t siz = 2;
	_char carr[2] = { 0 };

	bot_carr_2(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_2() { bot_strclr(carr); }
}carr_2;

typedef struct bot_carr_3
{
	size_t siz = 3;
	_char carr[3] = { 0 };

	bot_carr_3(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_3() { bot_strclr(carr); }
}carr_3;

typedef struct bot_carr_4
{
	size_t siz = 4;
	_char carr[4] = { 0 };

	bot_carr_4(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_4() { bot_strclr(carr); }
}carr_4;

typedef struct bot_carr_6
{
	size_t siz = 6;
	_char carr[6] = { 0 };

	bot_carr_6(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_6() { bot_strclr(carr); }
}carr_6;

typedef struct bot_carr_8
{
	size_t siz = 8;
	_char carr[8] = { 0 };

	bot_carr_8(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_8() { bot_strclr(carr); }
}carr_8;

typedef struct bot_carr_9
{
	size_t siz = 9;
	_char carr[9] = { 0 };

	bot_carr_9(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_9() { bot_strclr(carr); }
}carr_9;

typedef struct bot_carr_12
{
	size_t siz = 12;
	_char carr[12] = { 0 };

	bot_carr_12(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_12() { bot_strclr(carr); }
}carr_12;

typedef struct bot_carr_16
{
	size_t siz = 16;
	_char carr[16] = { 0 };

	bot_carr_16(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_16() { bot_strclr(carr); }
}carr_16;

typedef struct bot_carr_18
{
	size_t siz = 18;
	_char carr[18] = { 0 };

	bot_carr_18(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_18() { bot_strclr(carr); }
}carr_18;

typedef struct bot_carr_21
{
	size_t siz = 21;
	_char carr[21] = { 0 };

	bot_carr_21(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_21() { bot_strclr(carr); }
}carr_21;

typedef struct bot_carr_24
{
	size_t siz = 24;
	_char carr[24] = { 0 };

	bot_carr_24(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_24() { bot_strclr(carr); }
}carr_24;

typedef struct bot_carr_32
{
	size_t siz = 32;
	_char carr[32] = { 0 };

	bot_carr_32(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_32() { bot_strclr(carr); }
}carr_32;

typedef struct bot_carr_36
{
	size_t siz = 36;
	_char carr[36] = { 0 };

	bot_carr_36(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_36() { bot_strclr(carr); }
}carr_36;

typedef struct bot_carr_48
{
	size_t siz = 48;
	_char carr[48] = { 0 };

	bot_carr_48(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_48() { bot_strclr(carr); }
}carr_48;

typedef struct bot_carr_56
{
	size_t siz = 56;
	_char carr[56] = { 0 };

	bot_carr_56(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_56() { bot_strclr(carr); }
}carr_56;

typedef struct bot_carr_64
{
	size_t siz = 64;
	_char carr[64] = { 0 };

	bot_carr_64(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_64() { bot_strclr(carr); }
}carr_64;

typedef struct bot_carr_72
{
	size_t siz = 72;
	_char carr[72] = { 0 };

	bot_carr_72(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_72() { bot_strclr(carr); }
}carr_72;

typedef struct bot_carr_81
{
	size_t siz = 81;
	_char carr[81] = { 0 };

	bot_carr_81(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_81() { bot_strclr(carr); }
}carr_81;

typedef struct bot_carr_96
{
	size_t siz = 96;
	_char carr[96] = { 0 };

	bot_carr_96(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_96() { bot_strclr(carr); }
}carr_96;

typedef struct bot_carr_112
{
	size_t siz = 112;
	_char carr[112] = { 0 };

	bot_carr_112(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_112() { bot_strclr(carr); }
}carr_112;

typedef struct bot_carr_128
{
	size_t siz = 128;
	_char carr[128] = { 0 };

	bot_carr_128(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_128() { bot_strclr(carr); }
}carr_128;

typedef struct bot_carr_144
{
	size_t siz = 144;
	_char carr[144] = { 0 };

	bot_carr_144(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_144() { bot_strclr(carr); }
}carr_144;

typedef struct bot_carr_168
{
	size_t siz = 168;
	_char carr[168] = { 0 };

	bot_carr_168(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_168() { bot_strclr(carr); }
}carr_168;

typedef struct bot_carr_192
{
	size_t siz = 192;
	_char carr[192] = { 0 };

	bot_carr_192(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_192() { bot_strclr(carr); }
}carr_192;

typedef struct bot_carr_256
{
	size_t siz = 256;
	_char carr[256] = { 0 };

	bot_carr_256(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_256() { bot_strclr(carr); }
}carr_256;

typedef struct bot_carr_384
{
	size_t siz = 384;
	_char carr[384] = { 0 };

	bot_carr_384(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_384() { bot_strclr(carr); }
}carr_384;

typedef struct bot_carr_512
{
	size_t siz = 512;
	_char carr[512] = { 0 };

	bot_carr_512(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_512() { bot_strclr(carr); }
}carr_512;

typedef struct bot_carr_768
{
	size_t siz = 768;
	_char carr[768] = { 0 };

	bot_carr_768(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_768() { bot_strclr(carr); }
}carr_768;

typedef struct bot_carr_1024
{
	size_t siz = 1024;
	_char carr[1024] = { 0 };

	bot_carr_1024(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_1024() { bot_strclr(carr); }
}carr_1024;

typedef struct bot_carr_2048
{
	size_t siz = 2048;
	_char carr[2048] = { 0 };

	bot_carr_2048(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_2048() { bot_strclr(carr); }
}carr_2048;

typedef struct bot_carr_4096
{
	size_t siz = 4096;
	_char carr[4096] = { 0 };

	bot_carr_4096(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_4096() { bot_strclr(carr); }
}carr_4096;

typedef struct bot_carr_8192
{
	size_t siz = 8192;
	_char carr[8192] = { 0 };

	bot_carr_8192(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_8192() { bot_strclr(carr); }
}carr_8192;

typedef struct bot_carr_16384
{
	size_t siz = 16384;
	_char carr[16384] = { 0 };

	bot_carr_16384(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_16384() { bot_strclr(carr); }
}carr_16384;

typedef struct bot_carr_32768
{
	size_t siz = 32768;
	_char carr[32768] = { 0 };

	bot_carr_32768(_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_carr_32768() { bot_strclr(carr); }
}carr_32768;

typedef struct bot_ucar_2
{
	size_t siz = 2;
	u_char carr[2] = { 0 };

	bot_ucar_2(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_2() { bot_ustrclr(carr); }
}ucar_2;

typedef struct bot_ucar_4
{
	size_t siz = 4;
	u_char carr[4] = { 0 };

	bot_ucar_4(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_4() { bot_ustrclr(carr); }
}ucar_4;

typedef struct bot_ucar_8
{
	size_t siz = 8;
	u_char carr[8] = { 0 };

	bot_ucar_8(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_8() { bot_ustrclr(carr); }
}ucar_8;

typedef struct bot_ucar_16
{
	size_t siz = 16;
	u_char carr[16] = { 0 };

	bot_ucar_16(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_16() { bot_ustrclr(carr); }
}ucar_16;

typedef struct bot_ucar_32
{
	size_t siz = 32;
	u_char carr[32] = { 0 };

	bot_ucar_32(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_32() { bot_ustrclr(carr); }
}ucar_32;

typedef struct bot_ucar_64
{
	size_t siz = 64;
	u_char carr[64] = { 0 };

	bot_ucar_64(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_64() { bot_ustrclr(carr); }
}ucar_64;

typedef struct bot_ucar_128
{
	size_t siz = 128;
	u_char carr[128] = { 0 };

	bot_ucar_128(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_128() { bot_ustrclr(carr); }
}ucar_128;

typedef struct bot_ucar_256
{
	size_t siz = 256;
	u_char carr[256] = { 0 };

	bot_ucar_256(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_256() { bot_ustrclr(carr); }
}ucar_256;

typedef struct bot_ucar_512
{
	size_t siz = 512;
	u_char carr[512] = { 0 };

	bot_ucar_512(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_512() { bot_ustrclr(carr); }
}ucar_512;

typedef struct bot_ucar_1024
{
	size_t siz = 1024;
	u_char carr[1024] = { 0 };

	bot_ucar_1024(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_1024() { bot_ustrclr(carr); }
}ucar_1024;

typedef struct bot_ucar_2048
{
	size_t siz = 2048;
	u_char carr[2048] = { 0 };

	bot_ucar_2048(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_2048() { bot_ustrclr(carr); }
}ucar_2048;

typedef struct bot_ucar_4096
{
	size_t siz = 4096;
	u_char carr[4096] = { 0 };

	bot_ucar_4096(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_4096() { bot_ustrclr(carr); }
}ucar_4096;

typedef struct bot_ucar_8192
{
	size_t siz = 8192;
	u_char carr[8192] = { 0 };

	bot_ucar_8192(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_8192() { bot_ustrclr(carr); }
}ucar_8192;

typedef struct bot_ucar_16384
{
	size_t siz = 16384;
	u_char carr[16384] = { 0 };

	bot_ucar_16384(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_16384() { bot_ustrclr(carr); }
}ucar_16384;

typedef struct bot_ucar_32768
{
	size_t siz = 32768;
	u_char carr[32768] = { 0 };

	bot_ucar_32768(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_32768() { bot_ustrclr(carr); }
}ucar_32768;

typedef struct bot_ucar_65535
{
	size_t siz = 65535;
	u_char carr[65535] = { 0 };

	bot_ucar_65535(u_char ncar[] = 0) { if (ncar) { memcpy((void*)carr, (void*)ncar, siz); } }
	~bot_ucar_65535() { bot_ustrclr(carr); }
}ucar_65535;

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

enum bot_strt_mtx
{
	MTX_REQ = 0,
	MTX_C = 1,
	MTX_CV = 2,
	MTX_LOG = 3,
	MTX_O = 4,
	MTX_DBC = 5,
	MTX_PEND = 6,
	MTX_TTS = 7,
	MTX_DBL = 8,
	MTX_FO = 9,
	MTX_TRAT = 10,
	MTX_STRT = 11,
	MTX_FCON = 12,
	MTX_BTIM = 13,
	MTX_DMAP = 14,
	MTX_FTYPE = 15,
	MTX_STYPE = 16,
	MTX_PORTS = 17,
	MTX_PCL = 18,
	MTX_FPAD = 19,
	MTX_MAX = 20
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
	BOT_PORT_FAM = 2,
	BOT_PORT_PTN = 3,
	BOT_PORT_PCL = 4,
	BOT_PORT_SOP = 5,
	BOT_PORT_XCL = 6,
	BOT_PORT_MAX = 7
};

class bot_port
{

public:

	sint lid;
	sint fam;
	sint portn;
	sint proto;
	std::vector<BOT_SOPT> sopts;
	bool xcl;

	void Clear() { xcl = true; lid = fam = portn = proto = -1; sopts.clear(); }
	void Renew(bot_port* nport = 0)
	{
		Clear();

		if (!nport)
		{
			return;
		}
		
		xcl = nport->xcl;
		lid = nport->lid;
		fam = nport->fam;
		portn = nport->portn;
		proto = nport->proto;

		for (uint x = 0; x < nport->sopts.size(); x++)
		{
			sopts.push_back(nport->sopts[x]);
		}
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

	bot_port(sint nfam = -1, sint nprt = -1, sint nproto = -1, bool nxcls = true) { xcl = nxcls; fam = nfam; proto = nproto; portn = nprt; sopts.clear(); }
	~bot_port() { Clear(); }
private:

};

class bot_port_counter
{
public:

	std::vector<bot_port> oprt;

	sllint Add(sint nfam = -1, sint nprt = -1, sint nproto = -1, bool xcls = true)
	{
		if (nfam < 0 || nprt < 0 || nproto < 0)
		{
			return -1;
		}
		if (oprt.size() < (size_t)BOTOPORT_MAX)
		{
			bool fail = false;
			size_t x = 0;

			while (x < oprt.size())
			{
				if (oprt[x].portn == nprt)
				{
					std::vector<BOT_SOPT> vec;
					sint rc = oprt[x].GetSopts(&vec);

					for (uint y = 0; y < vec.size(); y++)
					{
						if (vec[y].sopt == IPV6_V6ONLY && nfam != (sint)AF_INET6)
						{
							fail = true;
						}
						if (!fail)
						{
							if (vec[y].sopt == SO_EXCLUSIVEADDRUSE)
							{
								fail = true;
							}
						}
					}
				}
				x++;
			}
			if (!fail)
			{
				bot_port xport(nfam, nprt, nproto, xcls);
				oprt.push_back(xport);
				return (sllint)x;
			}
		}
		return -1;
	}
	sllint Rem(sint nprt = -1, sint nproto = -1)
	{
		if (nprt < 0)
		{
			return -1;
		}
		sint ret = -1;

		if (oprt.size())
		{
			size_t x;
			for (x = 0; x < oprt.size(); x++)
			{
				if (oprt[x].portn == nprt && oprt[x].proto == nproto)
				{
					for (uint y = x + 1; y < oprt.size(); y++)
					{
						oprt[y - 1].Renew(&oprt[y]);
					}
					oprt.pop_back();
					if (ret)
					{
						ret = 0;
					}
				}
			}
		}
		return ret;
	}
	sllint GetCt() { return (sllint)oprt.size(); }

	bot_port_counter() { oprt.clear(); }
	~bot_port_counter() { oprt.clear(); }

private:

};

enum bot_plug_mems
{
	BOT_PLUG_LID = 1,
	BOT_PLUG_ERR = 2,
	BOT_PLUG_BDP = 3,
	BOT_PLUG_SRV = 4,
	BOT_PLUG_CON = 5,
	BOT_PLUG_DSC = 6,
	BOT_PLUG_SOP = 7,
	BOT_PLUG_QSZ = 8,
	BOT_PLUG_PRT = 9,
	BOT_PLUG_RES = 10,
	BOT_PLUG_PTR = 11,
	BOT_PLUG_HNT = 12,
	BOT_PLUG_STO = 13,
	BOT_PLUG_URL = 14,
	BOT_PLUG_FAM = 15,
	BOT_PLUG_IPS = 16,
	BOT_PLUG_SVC = 17,
	BOT_PLUG_SCK = 18,
	BOT_PLUG_TSCK = 19,
	BOT_PLUG_MAX = 20
};

class bot_plug
{
public:

	sint lid;
	carr_256 emsg;
	bool bndp;
	bool isserv;
	sint con;
	sint dsc;
	sint sopt;
	sint qsiz;
	bot_port prt;
	struct addrinfo *res;
	struct addrinfo *ptr;
	struct addrinfo hints;
	struct sockaddr_storage *sto;
	carr_512 url;
	carr_8 ifam;
	carr_64 ipstr;
	carr_64 servc;

#ifdef _WIN32
	SOCKET sck;
	SOCKET tsck;
#else
	sint sck;
	sint tsck;
#endif

	void Clear()
	{
		Close();
		lid = con = dsc = sopt = qsiz = -1;
		bndp = isserv = false;
		bot_strclr(emsg.carr);
		bot_strclr(url.carr);
		bot_strclr(ifam.carr);
		bot_strclr(ipstr.carr);
		bot_strclr(servc.carr);
		res = ptr = 0;
		memset((void*)&hints, 0, sizeof(hints));
		sto = 0;
		prt.Clear();

#ifdef _WIN32
		sck = tsck = INVALID_SOCKET;
#else
		FD_ZERO(sck);
		FD_ZERO(tsck);
#endif
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
		dsc = val->dsc;
		sopt = val->sopt;
		qsiz = val->qsiz;
		bndp = val->bndp;
		isserv = val->isserv;
		res = val->res;
		ptr = val->ptr;
		memcpy((void*)&hints, (void*)&val->hints, sizeof(hints));
		memcpy((void*)sto, (void*)val->sto, sizeof(sockaddr_storage));
		prt.Renew(&val->prt);
		sck = val->sck;
		tsck = val->tsck;
		sint xc = bot_sprintf(emsg.carr, emsg.siz, "%s", val->emsg.carr);
		xc = bot_sprintf(url.carr, url.siz, "%s", val->url.carr);
		xc = bot_sprintf(ifam.carr, ifam.siz, "%s", val->ifam.carr);
		xc = bot_sprintf(ipstr.carr, ipstr.siz, "%s", val->ipstr.carr);
		xc = bot_sprintf(servc.carr, servc.siz, "%s", val->servc.carr);
	}

	sint Open(sint flg = AI_PASSIVE, sint nfam = AF_UNSPEC, sint ntyp = 0, bool nbndp = false, bool nisserv = false)
	{
		if (isserv && !nbndp)
		{
			return INT32_MIN;
		}

		isserv = nisserv;
		bndp = nbndp;
		isserv = nisserv;
		memset((void*)&hints, 0, sizeof(hints));
		hints.ai_flags = flg;
		hints.ai_family = nfam;
		hints.ai_socktype = ntyp;

		if ((hints.ai_family == AF_UNSPEC || hints.ai_family == AF_INET || hints.ai_family == AF_INET6) && hints.ai_socktype == SOCK_STREAM)
		{
			hints.ai_protocol = IPPROTO_TCP;
		}
		else if ((hints.ai_family == AF_UNSPEC || hints.ai_family == AF_INET || hints.ai_family == AF_INET6) && hints.ai_socktype == SOCK_DGRAM)
		{
			hints.ai_protocol = IPPROTO_UDP;
		}
		else if (hints.ai_family == AF_IRDA && hints.ai_socktype == SOCK_STREAM)
		{
			hints.ai_protocol = 0;
		}
		else if ((hints.ai_family == AF_UNSPEC || hints.ai_family == AF_INET || hints.ai_family == AF_INET6) && hints.ai_socktype == SOCK_RAW)
		{
			hints.ai_protocol = IPPROTO_RAW;
		}
		else
		{
#ifdef _WIN32
			if (hints.ai_family == AF_INET && hints.ai_socktype == SOCK_RDM)
			{
				hints.ai_protocol = IPPROTO_PGM;
			}
#endif
			return INT32_MIN;
		}

		if (strlen(servc.carr))
		{
			if (strlen(url.carr))
			{
				dsc = getaddrinfo(url.carr, servc.carr, &hints, &res);
			}
			else
			{
				dsc = getaddrinfo(NULL, servc.carr, &hints, &res);
			}
		}
		else
		{
			if (strlen(url.carr))
			{
				dsc = getaddrinfo(url.carr, NULL, &hints, &res);
			}
			else
			{
				sint xc = bot_sprintf(servc.carr, servc.siz, "%i", (sint)BOTLPORT_A);
				dsc = getaddrinfo(NULL, servc.carr, &hints, &res);
			}
		}

		if (!dsc && res != NULL)
		{
			ptr = res;
			sto = (struct sockaddr_storage*)ptr->ai_addr;
			inet_ntop(ptr->ai_family, sto, ipstr.carr, ipstr.siz);

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
			PError(dsc);
		}
		con = 0;
		return dsc;
	}
	
#ifdef _WIN32

	sint AddSOpt(sint popt = -1, sint sopt = -1, char val = (char)-1)
	{
		if (sopt < 0 || popt < 0 || (sint)val < 0)
		{
			return INT32_MIN;
		}
		
		sint ret = setsockopt(sck, popt, sopt, &val, sizeof(val));

		if (ret < 0)
		{
			PError();
			return ret;
		}

		BOT_SOPT nopt(popt, sopt, (sint)val);
		ret = prt.AddSOpt(&nopt);
		return ret;
	}

	sint Sock(bool xclsck = true)
	{
		if (con < 0)
		{
			return INT32_MIN;
		}
		
		if (ptr->ai_family == AF_INET)
		{
			sck = socket(PF_INET, ptr->ai_socktype, ptr->ai_protocol);
		}
		else if (ptr->ai_family == AF_INET6)
		{
			sck = socket(PF_INET6, ptr->ai_socktype, ptr->ai_protocol);
		}
		else if (ptr->ai_family == AF_UNSPEC)
		{
			sck = socket(PF_UNSPEC, ptr->ai_socktype, ptr->ai_protocol);
		}
		else {}

		if (sck == INVALID_SOCKET)
		{
			PError();
			return INT32_MIN;
		}
		sint ret = 0;

		if (bndp)
		{
			if (xclsck)
			{
				sopt = (sint)SO_EXCLUSIVEADDRUSE;
			}
			else
			{
				sopt = (sint)SO_REUSEADDR;
			}

			char opt = '1';
			ret = setsockopt(sck, SOL_SOCKET, sopt, &opt, sizeof(opt));

			if (ret < 0)
			{
				PError();
				return ret;
			}
			
			bot_sopt nopt((sint)SOL_SOCKET, sopt);
			ret = prt.AddSOpt(&nopt);
			ret = bind(sck, ptr->ai_addr, ptr->ai_addrlen);

			if (ret < 0)
			{
				PError();
				return ret;
			}
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
		
		sint ret = setsockopt(sck, popt, sopt, &val, sizeof(val));

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
		if (ptr->ai_family == AF_INET)
		{
			sck = socket(PF_INET, ptr->ai_socktype, ptr->ai_protocol);
		}
		else if (ptr->ai_family == AF_INET6)
		{
			sck = socket(PF_INET6, ptr->ai_socktype, ptr->ai_protocol);
		}
		else if (ptr->ai_family == AF_UNSPEC)
		{
			sck = socket(PF_UNSPEC, ptr->ai_socktype, ptr->ai_protocol);
		}
		else {}

		if (sck == INVALID_SOCKET)
		{
			perror(emsg.carr);
			return INT32_MIN;
		}

		sint ret = 0;

		if (bndp)
		{
			if (xclsck)
			{
				sopt = (sint)SO_EXCLUSIVEADDRUSE;
			}
			else
			{
				sopt = (sint)SO_REUSEADDR;
			}

			sint opt = 1;
			ret = setsockopt(sck, SOL_SOCKET, sopt, &opt, sizeof(opt));

			if (ret < 0)
			{
				perror(esmg.carr);
				return ret;
			}

			bot_sopt nopt((sint)SOL_SOCKET, sopt);
			ret = prt.AddSOpt(&nopt);
			ret = bind(sck, ptr->ai_addr, ptr->ai_addrlen);

			if (ret < 0)
			{
				perror(esmg.carr);
				return ret;
			}
		}
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
		sint ret = connect(sck, ptr->ai_addr, sizeof(ptr->ai_addr));

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
		sint ret = listen(sck, qsiz);

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

#ifdef _WIN32
	SOCKET Accept()
	{
		if (con != 1)
		{
			return INT32_MIN;
		}
		sint len = sizeof(ptr->ai_addrlen);
		SOCKET ret = accept(tsck, ptr->ai_addr, &len);

		if (ret == SOCKET_ERROR)
		{
			PError();
			return ret;
		}
		return 0;
	}
#else
	sint Accept()
	{
		if (con != 1)
		{
			return INT32_MIN;
		}
		sint len = (sint)ptr->ai_addrlen;
		sint ret = accept(tsck, ptr->ai_addr, &len);

		if (ret < 0)
		{
			perror(emsg.carr);
			return ret;
		}
		return 0;
	}
#endif

	sllint Send(_char *dat = 0, sint dlen = 0)
	{
		if (!dat || !dlen)
		{
			return INT32_MIN + 1;
		}
		sllint add = 0;
		sllint ret = 0;

		if (ptr->ai_protocol == IPPROTO_TCP || (ptr->ai_protocol == IPPROTO_UDP && con > 1))
		{
			for (; ret > -1 && ret < dlen;)
			{
				add = (sllint)send(tsck, dat, dlen, 0);

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
		else if (ptr->ai_protocol == IPPROTO_UDP && con > 0)
		{
			for (; ret > 0 && ret < dlen;)
			{
				sint alen = sizeof(ptr->ai_addr);
				add = (sllint)sendto(tsck, dat, dlen, 0, ptr->ai_addr, alen);

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
#ifdef _WIN32
			if (ptr->ai_protocol == IPPROTO_PGM && con > 1)
			{

			}
#endif
			ret = INT32_MIN;

		}
		return ret;
	}

	sllint Rec(_char *dat = 0, sint dlen = 0)
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

		if (ptr->ai_protocol == IPPROTO_TCP)
		{
			for (; ret > 0 && ret < dlen;)
			{
				ret += (sllint)recv(tsck, dat, dlen, 0);

				if (ret > BOT_MAX_RCV)
				{
					return ret;
				}
			}
		}
		else if (ptr->ai_protocol == IPPROTO_UDP)
		{
			for (; ret > 0 && ret < dlen;)
			{
				sint alen = sizeof(ptr->ai_addr);
				ret += (sllint)recvfrom(tsck, dat, dlen, 0, ptr->ai_addr, &alen);

				if (ret > BOT_MAX_RCV)
				{
					return ret;
				}
			}
		}
		else
		{
#ifdef _WIN32
			if (ptr->ai_protocol == IPPROTO_PGM)
			{

			}
#endif
		}

#ifdef _WIN32
		closesocket(tsck);
#else
		close(tsck);
#endif
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

	sint Next()
	{
		if (con < 0)
		{
			return INT32_MIN;
		}
		if (ptr->ai_next != NULL)
		{
			ptr = ptr->ai_next;
			sto = (struct sockaddr_storage*)ptr->ai_addr;
			inet_ntop(ptr->ai_family, sto, ipstr.carr, ipstr.siz);

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

	void Close()
	{
		if (dsc > -1)
		{
			if (tsck != INVALID_SOCKET)
			{
#ifdef _WIN32
				closesocket(tsck);

				if (tsck == INVALID_SOCKET)
				{
					PError();
				}
#else
				close(tsck);
#endif
			}
			if (sck != INVALID_SOCKET)
			{
#ifdef _WIN32
				closesocket(sck);

				if (sck == INVALID_SOCKET)
				{
					PError();
				}
#else
				close(sck);
#endif
			}
			
			freeaddrinfo(res);
			dsc = -1;
		}
	}
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
	bot_plug(c_char* nurl = 0, c_char* nservice = 0)
	{
		memset(&hints, 0, sizeof(hints));

		if (nservice)
		{
			sint xc = bot_sprintf(servc.carr, servc.siz, "%s", nservice);
		}
		if (nurl)
		{
			sint xc = bot_sprintf(url.carr, url.siz, "%s", nurl);
		}

		dsc = -1;
		res = ptr = NULL;
		sck = INVALID_SOCKET;
		tsck = INVALID_SOCKET;
#ifndef _WIN32
		FD_ZERO(sck);
		FD_ZERO(tsck);
#endif
		con = -1;
	}

	~bot_plug() { if (dsc > -1) { Close(); } }

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
	BOT_STMT_CSPEC = 8,
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
	sint cspec;
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
		opts[0] = opts[1] = ifex = ospec = act = targ = rlim = cspec = lid = it_type = ic_type = -1;

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
		ifex = ospec = act = rlim = cspec = targ = lid = -1;
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
	BOT_C_LOGIN_NAME = 9,
	BOT_C_NAME = 10,
	BOT_C_L_LOGIN = 11,
	BOT_C_L_DATE = 12,
	BOT_C_LFL = 14,
	BOT_C_LAST_E = 15,
	BOT_C_CBY = 16,
	BOT_C_MAX = 17
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
	sint lid;
	sint c_by;
	std::string login_name;
	std::string name;
	std::string lastlogin;
	std::string logindate;
	std::string last_failed_login;
	std::string lastexchange;

	void Clear() { nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); }
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
		lid = val_->lid;
		c_by = val_->c_by;
		login_name.append(val_->login_name.c_str());
		name.append(val_->name.c_str());
		lastlogin.append(val_->lastlogin.c_str());
		last_failed_login.append(val_->last_failed_login.c_str());
		lastexchange.append(val_->lastexchange.c_str());
	}

	BOT_CLIENT(c_char* nstr = "") {nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); size_t siz = strlen(nstr); if (siz < 128) { name.append(nstr); if (siz) { nameset = true; } } }

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
	sint lid;
	sint c_by;
	std::string login_name;
	std::string name;
	std::string lastlogin;
	std::string logindate;
	std::string last_failed_login;
	std::string lastexchange;

	void Clear() { nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); }
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
		priv = val_->priv;
		lid = val_->lid;
		c_by = val_->c_by;
		login_name.append(val_->login_name.c_str());
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
		priv = val_->priv;
		lid = val_->lid;
		c_by = val_->c_by;
		login_name.append(val_->login_name.c_str());
		name.append(val_->name.c_str());
		lastlogin.append(val_->lastlogin.c_str());
		last_failed_login.append(val_->last_failed_login.c_str());
		lastexchange.append(val_->lastexchange.c_str());
	}

	BOT_CLIENT_M(c_char* nstr = "",
		bool nnameset = false,
		bool nloggedin = false,
		bool nchangename = false,
		bool nupdatepriv = false,
		bool nupdatelogin = false,
		sint ntotallogins = -1,
		sint nfailed_logins = -1,
		sint npriv = -1,
		sint nlid = -1,
		sint nc_by = -1,
		c_char* nlogin_name = "",
		c_char* nlastlogin = "",
		c_char* nlogindate = "",
		c_char* nlast_failed_login = "",
		c_char* nlastexchange = "")
	{

		nameset = nnameset;
		loggedin = nloggedin;
		changename = nchangename;
		updatepriv = nupdatepriv;
		updatelogin = nupdatelogin;
		totallogins = ntotallogins;
		failed_logins = nfailed_logins;
		priv = npriv;
		lid = nlid;
		c_by = nc_by;
		size_t siz = strlen(nstr);
		if (siz < 128)
		{
			name.append(nstr);
		}
		siz = strlen(nlogin_name);
		if (siz < 128)
		{
			login_name.append(nlogin_name);
		}
		siz = strlen(nlastlogin);
		if (siz < 128)
		{
			lastlogin.append(nlastlogin);
		}
		siz = strlen(nlogindate);
		if (siz < 128)
		{
			logindate.append(nlogindate);
		}
		siz = strlen(nlast_failed_login);
		if (siz < 128)
		{
			last_failed_login.append(nlast_failed_login);
		}
		siz = strlen(nlastexchange);
		if (siz < 128)
		{
			lastexchange.append(nlastexchange);
		}
	}

private:

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
	BOT_FS_BTO = 10,
	BOT_FS_DSIZ = 11,
	BOT_FS_DAT = 12,
	BOT_FS_DATP = 13,
	BOT_FS_CRS = 14,
	BOT_FS_CRSV = 15,
	BOT_FS_SELV = 16,
	BOT_FS_MAX = 17
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
	std::vector<std::vector<BOT_CRS>> crsv;
	std::vector<std::vector<BOT_CRS>> selv;
	bot_fstate fst;
	sint lid;
	sint c_by;
	sint cm;
	sllint bto;
	size_t dsiz;
	_char* dat;

	void Clear() { fst.Clear(); ClearDat(); bto = -1; encode = cm = lid = c_by = omode = fcon = -1; if (!crsv.empty()) { crsv.clear(); } if (!selv.empty()) { selv.clear(); } if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } }
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
				memcpy((void*)&dat[x], (void*)val_[x], sizeof(_char));
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

	void Clear() { crss = sels = 0; crsv.clear(); datp = 0; dsiz = 0; fst.ClearStats(); bto = -1; encode = cm = lid = c_by = omode = fcon = -1; if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } }
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
	BOT_TTS_MAX = 12
};

class TINFO
{
public:

	sint lid;
	sint opt;
	sint fin;
	sint c_by;
	pthread_t thread;
	pthread_attr_t attr;
	void *(*func)(void *);
	std::chrono::steady_clock::time_point t_I;
	float min_ratv;
	std::string thread_name;
	std::vector<ullint> vals;

	void Clear() { min_ratv = 0.0f; t_I = std::chrono::steady_clock::now(); opt = lid = c_by = -1; fin = BOT_THR_BEG; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; vals.clear(); }
	void Renew(TINFO* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		lid = val_->lid;
		opt = val_->opt;
		fin = val_->fin;
		c_by = val_->c_by;
		thread = val_->thread;
		attr = val_->attr;
		func = val_->func;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(val_->thread_name.c_str());

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
		opt = nopt;
		fin = BOT_THR_BEG;
		c_by = nc_by;
		func = nfunc;
		t_I = std::chrono::steady_clock::now();
		min_ratv = nmin_ratv;

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
	sint c_by;
	sllint thread;
	sllint attr;
	void *(*func)(void *);
	std::chrono::steady_clock::time_point t_I;
	float min_ratv;
	std::string thread_name;
	std::vector<ullint> vals;

	void Clear() { min_ratv = 0.0f; attr = thread = 0; t_I = std::chrono::steady_clock::now(); opt = lid = c_by = -1; fin = BOT_THR_BEG; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; vals.clear(); }
	
	void Renew(TINFO_M* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		lid = val_->lid;
		opt = val_->opt;
		fin = val_->fin;
		c_by = val_->c_by;
		thread = val_->thread;
		attr = val_->attr;
		func = val_->func;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(val_->thread_name.c_str());

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
		opt = val_->opt;
		fin = val_->fin;
		c_by = val_->c_by;
		thread = (sllint)&val_->thread;
		attr = (sllint)&val_->attr;
		func = val_->func;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(val_->thread_name.c_str());

		if (val_->vals.size() < BOTVEC_LIM)
		{
			for (uint x = 0; x < val_->vals.size(); x++)
			{
				vals.push_back(val_->vals[x]);
			}
		}
	}

	TINFO_M(sint nopt = -1, c_char* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f, std::vector<ullint>* nvec = 0)
	{
		lid = -1;
		opt = nopt;
		fin = BOT_THR_BEG;
		c_by = nc_by;
		func = nfunc;
		t_I = std::chrono::steady_clock::now();
		min_ratv = nmin_ratv;

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
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}
		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };
				sint xc = bot_sprintf(icar, 64, "%s%lli", sep, vec_->at(siz));
				curlen += strlen(icar);

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<ulint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}
		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };
				sint xc = bot_sprintf(icar, 64, "%s%lu", sep, vec_->at(siz));
				curlen += strlen(icar);

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<uint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };
				sint xc = bot_sprintf(icar, 64, "%s%u", sep, vec_->at(siz));
				curlen += strlen(icar);

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<sllint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };
				sint xc = bot_sprintf(icar, 64, "%s%lli", sep, vec_->at(siz));
				curlen += strlen(icar);

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<slint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };
				sint xc = bot_sprintf(icar, 64, "%s%li", sep, vec_->at(siz));
				curlen += strlen(icar);

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<sint>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				_char icar[64]{ 0 };
				sint xc = bot_sprintf(icar, 64, "%s%i", sep, vec_->at(siz));
				curlen += strlen(icar);

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<c_char*>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				curlen += (strlen(vec_->at(siz)) + strlen(sep));

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz));
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	sint VToStr(std::vector<std::string>* vec_ = 0, _char instr_[] = 0, size_t i_siz = 0, c_char* sep = " ")
	{
		if (!vec_ || !instr_ || !i_siz || !sep)
		{
			return -1;
		}

		if (i_siz < BOT_STRLEN_MAX)
		{
			size_t siz = 0;
			size_t curlen = 0;

			while (siz < vec_->size())
			{
				curlen += (vec_->at(siz).length() + strlen(sep));

				if (curlen < i_siz)
				{
					sint xc = bot_sprintf(instr_, i_siz, "%s%s", instr_, vec_->at(siz).c_str());
				}
				else
				{
					siz = vec_->size();
				}
				siz++;
			}
			if (siz == vec_->size())
			{
				return 0;
			}
		}
		return -1;
	}
	std::string VToStr(std::vector<c_char*>* vec_ = 0, c_char* sep = " ")
	{
		if (!vec_ || !sep)
		{
			std::string str;
			return str;
		}
		std::string str;

		for (size_t siz = 0; siz < vec_->size(); siz++)
		{
			if (strlen(vec_->at(siz)) + str.length() + strlen(sep) < BOT_STRLEN_MAX)
			{
				str.append(vec_->at(siz));
				str.append(sep);
			}
			else
			{
				siz = vec_->size();
			}
		}
		return str;
	}
	std::string VToStr(std::vector<std::string>* vec_ = 0, c_char* sep = " ")
	{
		if (!vec_ || !sep)
		{
			std::string str;
			return str;
		}
		std::string str;

		for (size_t siz = 0; siz < vec_->size(); siz++)
		{
			if (vec_->at(siz).length() + str.length() + strlen(sep) < BOT_STRLEN_MAX)
			{
				str.append(vec_->at(siz));
				str.append(sep);
			}
			else
			{
				siz = vec_->size();
			}
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

		if ((valI->maint != valII->maint) || (valI->ic_type != valII->ic_type) || (valI->it_type != valII->it_type) || (valI->cspec != valII->cspec) || (valI->act != valII->act) || (valI->ifex != valII->ifex) || (valI->targ != valII->targ))
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
	
	sint VIV(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
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
	sint VIV(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
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
	sint VIV(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val->name.c_str(), vec_->at(siz).name.c_str()) && !strcmp(val->path.c_str(), vec_->at(siz).path.c_str()) && !strcmp(val->type.c_str(), vec_->at(siz).type.c_str())) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val->name.c_str(), vec_->at(siz).name.c_str()) && !strcmp(val->path.c_str(), vec_->at(siz).path.c_str()) && !strcmp(val->type.c_str(), vec_->at(siz).type.c_str())) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_STMT> *vec_ = 0, BOT_STMT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !comp_t_struct(val, &vec_->at(siz))) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !comp_t_struct(val, &vec_->at(siz))) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<BOT_FLD> *vec_ = 0, BOT_FLD* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).fid > -1 && !strcmp(val->fld.c_str(), vec_->at(siz).fld.c_str()) && val->bto == vec_->at(siz).bto && val->ord == vec_->at(siz).ord) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).fid > -1 && !strcmp(val->fld.c_str(), vec_->at(siz).fld.c_str()) && val->bto == vec_->at(siz).bto && val->ord == vec_->at(siz).ord) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_port> *vec_ = 0, bot_port* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && vec_->at(siz).portn == val->portn) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && vec_->at(siz).portn == val->portn) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_port> *vec_ = 0, sint val = -1, sint nport = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0 || nport < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid == val && vec_->at(siz).portn == nport) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid == val && vec_->at(siz).portn == nport) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_plug> *vec_ = 0, bot_plug* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && vec_->at(siz).lid == val->lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && vec_->at(siz).lid == val->lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint VIV(std::vector<bot_plug> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid == val) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid == val) { vn = siz; siz = -1; } siz--; } } return vn; }
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

	sint UEE(std::vector<carr_2> *vec_ = 0, _char val[2] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 2) { if (val[siz] == '\0') { siz = 2; } siz++; } if (siz == 2) { _char nc = '\0'; memcpy((void*)&val[1], (void*)&nc, sizeof(val[1])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_4> *vec_ = 0, _char val[4] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 4) { if (val[siz] == '\0') { siz = 4; } siz++; } if (siz == 4) { _char nc = '\0'; memcpy((void*)&val[3], (void*)&nc, sizeof(val[3])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_8> *vec_ = 0, _char val[8] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 8) { if (val[siz] == '\0') { siz = 8; } siz++; } if (siz == 8) { _char nc = '\0'; memcpy((void*)&val[7], (void*)&nc, sizeof(val[7])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_16> *vec_ = 0, _char val[16] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 16) { if (val[siz] == '\0') { siz = 16; } siz++; } if (siz == 16) { _char nc = '\0'; memcpy((void*)&val[15], (void*)&nc, sizeof(val[15])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_32> *vec_ = 0, _char val[32] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 32) { if (val[siz] == '\0') { siz = 32; } siz++; } if (siz == 32) { _char nc = '\0'; memcpy((void*)&val[31], (void*)&nc, sizeof(val[31])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_64> *vec_ = 0, _char val[64] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 64) { if (val[siz] == '\0') { siz = 64; } siz++; } if (siz == 64) { _char nc = '\0'; memcpy((void*)&val[63], (void*)&nc, sizeof(val[63])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_128> *vec_ = 0, _char val[128] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 128) { if (val[siz] == '\0') { siz = 128; } siz++; } if (siz == 128) { _char nc = '\0'; memcpy((void*)&val[127], (void*)&nc, sizeof(val[127])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_256> *vec_ = 0, _char val[256] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 256) { if (val[siz] == '\0') { siz = 256; } siz++; } if (siz == 256) { _char nc = '\0'; memcpy((void*)&val[255], (void*)&nc, sizeof(val[255])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_512> *vec_ = 0, _char val[512] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 512) { if (val[siz] == '\0') { siz = 512; } siz++; } if (siz == 512) { _char nc = '\0'; memcpy((void*)&val[511], (void*)&nc, sizeof(val[511])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 1024) { if (val[siz] == '\0') { siz = 1024; } siz++; } if (siz == 1024) { _char nc = '\0'; memcpy((void*)&val[1023], (void*)&nc, sizeof(val[1023])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 2048) { if (val[siz] == '\0') { siz = 2048; } siz++; } if (siz == 2048) { _char nc = '\0'; memcpy((void*)&val[2047], (void*)&nc, sizeof(val[2047])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 4096) { if (val[siz] == '\0') { siz = 4096; } siz++; } if (siz == 4096) { _char nc = '\0'; memcpy((void*)&val[4095], (void*)&nc, sizeof(val[4095])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<std::vector<u_char>> *vec_ = 0, std::vector<u_char>* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { for (size_t nsiz = 0; nsiz < val->size(); nsiz++) { vec_->at(siz).push_back(val->at(nsiz)); } vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UEE(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == vtclr) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
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
	sint UEE(sint arr[] = 0, sint asiz = 0, sint val = -1) { if (!arr || !asiz) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] < 0) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(uint arr[] = 0, sint asiz = 0, uint val = (uint)UINT_MAX) { if (!arr || asiz == UINT_MAX) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] == (uint)UINT_MAX) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(slint arr[] = 0, sint asiz = 0, slint val = -1) { if (!arr || !asiz) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] < 0) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(ulint arr[] = 0, sint asiz = 0, ulint val = (ulint)UINT32_MAX) { if (!arr || asiz == (ulint)UINT32_MAX) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] == (ulint)UINT32_MAX) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(sllint arr[] = 0, sint asiz = 0, sllint val = -1) { if (!arr || !asiz) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] < 0) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	sint UEE(ullint arr[] = 0, sint asiz = 0, ullint val = (ullint)UINT64_MAX) { if (!arr || asiz == (ullint)UINT64_MAX) { return -1; } sint vn = -1; for (sint x = 0; x < asiz; x++) { if (arr[x] == (ullint)UINT64_MAX) { arr[x] = val; vn = x; x = asiz; } } return vn; }
	
	sint AVTV(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_8 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_16 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_32 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_64 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_128 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_256 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_512 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_1024 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2048 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4096 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AVTV(std::vector<std::vector<u_char>>* vec_ = 0, std::vector<u_char>* val = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AVTV(std::vector<std::chrono::steady_clock::time_point> *vec_, std::chrono::steady_clock::time_point* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
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
	sint AVTV(std::vector<BOTF_CONN*> *vec_, BOTF_CONN* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = VIV(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOT_FO_MAX || viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
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

	sint AVTA(sint arr[] = 0, sint asiz = 0, sint val = -1, bool check = true, bool use_empty = true) { if (!arr || !asiz) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(uint arr[] = 0, sint asiz = 0, uint val = UINT_MAX, bool check = true, bool use_empty = true) { if (!arr || asiz == UINT_MAX) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(slint arr[] = 0, sint asiz = 0, slint val = -1, bool check = true, bool use_empty = true) { if (!arr || !asiz) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(ulint arr[] = 0, sint asiz = 0, ulint val = UINT32_MAX, bool check = true, bool use_empty = true) { if (!arr || asiz == UINT32_MAX) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(sllint arr[] = 0, sint asiz = 0, sllint val = -1, bool check = true, bool use_empty = true) { if (!arr || !asiz) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }
	sint AVTA(ullint arr[] = 0, sint asiz = 0, ullint val = UINT64_MAX, bool check = true, bool use_empty = true) { if (!arr || asiz == UINT64_MAX) { return -1; } sint viv = -1; if (check) { viv = VIA(arr, asiz, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UEE(arr, asiz, val); if (viv > -1) { return viv; } } return viv; }

	std::chrono::steady_clock::time_point GVIV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { std::chrono::steady_clock::time_point ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele); } return ret; }
	sint GVIV(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { *val = vec_->at(ele); ret = ele; } return ret; }
	_char *GVIV(std::vector<carr_2> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_4> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_8> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_16> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_32> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_64> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_128> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_256> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_512> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_1024> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_2048> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GVIV(std::vector<carr_4096> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
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
				else if (memb == BOT_C_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_C_LOGIN_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).login_name); }
				else if (memb == BOT_C_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_C_L_LOGIN) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastlogin); }
				else if (memb == BOT_C_L_DATE) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).logindate); }
				else if (memb == BOT_C_LFL) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).last_failed_login); }
				else if (memb == BOT_C_LAST_E) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastexchange); }
				else if (memb == BOT_C_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
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
				else if (memb == BOT_C_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_C_LOGIN_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).login_name); }
				else if (memb == BOT_C_NAME) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).name); }
				else if (memb == BOT_C_L_LOGIN) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastlogin); }
				else if (memb == BOT_C_L_DATE) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).logindate); }
				else if (memb == BOT_C_LFL) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).last_failed_login); }
				else if (memb == BOT_C_LAST_E) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).lastexchange); }
				else if (memb == BOT_C_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
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
				else if (memb == BOT_STMT_CSPEC) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).cspec; }
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
				else if (memb == BOT_PORT_FAM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fam; }
				else if (memb == BOT_PORT_PTN) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).portn; }
				else if (memb == BOT_PORT_PCL) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).proto; }
				else if (memb == BOT_PORT_SOP) { std::vector<BOT_SOPT>* vp = reinterpret_cast<std::vector<BOT_SOPT>*>(val); size_t siz = 0; vp->clear(); while (siz < vec_->at(ele).sopts.size()) { vp->push_back(vec_->at(ele).sopts[siz]); siz++; } }
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
				else if (memb == BOT_PLUG_BDP) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).bndp; }
				else if (memb == BOT_PLUG_SRV) { bool* vp = reinterpret_cast<bool*>(val); *vp = vec_->at(ele).isserv; }
				else if (memb == BOT_PLUG_CON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).con; }
				else if (memb == BOT_PLUG_DSC) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).dsc; }
				else if (memb == BOT_PLUG_SOP) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).sopt; }
				else if (memb == BOT_PLUG_QSZ) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).qsiz; }
				else if (memb == BOT_PLUG_PRT) { bot_port* vp = reinterpret_cast<bot_port*>(val); vp->Renew(&vec_->at(ele).prt); }
				else if (memb == BOT_PLUG_RES) { addrinfo* vp = reinterpret_cast<addrinfo*>(val); vp = vec_->at(ele).res; }
				else if (memb == BOT_PLUG_PTR) { addrinfo* vp = reinterpret_cast<addrinfo*>(val); vp = vec_->at(ele).ptr; }
				else if (memb == BOT_PLUG_HNT) { addrinfo* vp = reinterpret_cast<addrinfo*>(val); *vp = vec_->at(ele).hints; }
				else if (memb == BOT_PLUG_STO) { sockaddr_storage* vp = reinterpret_cast<sockaddr_storage*>(val); vp = vec_->at(ele).sto; }
				else if (memb == BOT_PLUG_URL) { carr_512* vp = reinterpret_cast<carr_512*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).url, sizeof(carr_512)); }
				else if (memb == BOT_PLUG_FAM) { carr_8* vp = reinterpret_cast<carr_8*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).ifam, sizeof(carr_8)); }
				else if (memb == BOT_PLUG_IPS) { carr_64* vp = reinterpret_cast<carr_64*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).ipstr, sizeof(carr_64)); }
				else if (memb == BOT_PLUG_SVC) { carr_64* vp = reinterpret_cast<carr_64*>(val); memcpy((void*)vp, (void*)&vec_->at(ele).servc, sizeof(carr_64)); }
#ifdef _WIN32
				else if (memb == BOT_PLUG_SCK) { SOCKET* vp = reinterpret_cast<SOCKET*>(val); *vp = vec_->at(ele).sck; }
				else if (memb == BOT_PLUG_TSCK) { SOCKET* vp = reinterpret_cast<SOCKET*>(val); *vp = vec_->at(ele).tsck; }
#else
				else if (memb == BOT_PLUG_SCK) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).sck; }
				else if (memb == BOT_PLUG_TSCK) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).tsck; }
#endif
				else {}
				ret = ele;
			}
		}
		return ret;
	}

	sint SVIV(std::vector<carr_2> *vec_ = 0, sint ele = -1, _char val[2] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_4> *vec_ = 0, sint ele = -1, _char val[4] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_8> *vec_ = 0, sint ele = -1, _char val[8] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_16> *vec_ = 0, sint ele = -1, _char val[16] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_32> *vec_ = 0, sint ele = -1, _char val[32] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_64> *vec_ = 0, sint ele = -1, _char val[64] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_128> *vec_ = 0, sint ele = -1, _char val[128] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_256> *vec_ = 0, sint ele = -1, _char val[256] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_512> *vec_ = 0, sint ele = -1, _char val[512] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_1024> *vec_ = 0, sint ele = -1, _char val[1024] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_2048> *vec_ = 0, sint ele = -1, _char val[2048] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SVIV(std::vector<carr_4096> *vec_ = 0, sint ele = -1, _char val[4096] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
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
			else if (memb == BOT_C_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_C_LOGIN_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).login_name.clear(); if (val_->length() < 128) { vec_->at(ele).login_name.append(val_->c_str()); } }
			else if (memb == BOT_C_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < 128) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_C_L_LOGIN) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastlogin.clear(); if (val_->length() < 128) { vec_->at(ele).lastlogin.append(val_->c_str()); } }
			else if (memb == BOT_C_L_DATE) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).logindate.clear(); if (val_->length() < 128) { vec_->at(ele).logindate.append(val_->c_str()); } }
			else if (memb == BOT_C_LFL) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).last_failed_login.clear(); if (val_->length() < 128) { vec_->at(ele).last_failed_login.append(val_->c_str()); } }
			else if (memb == BOT_C_LAST_E) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastexchange.clear(); if (val_->length() < 128) { vec_->at(ele).lastexchange.append(val_->c_str()); } }
			else if (memb == BOT_C_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
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
			else if (memb == BOT_C_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_C_LOGIN_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).login_name.clear(); if (val_->length() < 128) { vec_->at(ele).login_name.append(val_->c_str()); } }
			else if (memb == BOT_C_NAME) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).name.clear(); if (val_->length() < 128) { vec_->at(ele).name.append(val_->c_str()); } }
			else if (memb == BOT_C_L_LOGIN) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastlogin.clear(); if (val_->length() < 128) { vec_->at(ele).lastlogin.append(val_->c_str()); } }
			else if (memb == BOT_C_L_DATE) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).logindate.clear(); if (val_->length() < 128) { vec_->at(ele).logindate.append(val_->c_str()); } }
			else if (memb == BOT_C_LFL) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).last_failed_login.clear(); if (val_->length() < 128) { vec_->at(ele).last_failed_login.append(val_->c_str()); } }
			else if (memb == BOT_C_LAST_E) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).lastexchange.clear(); if (val_->length() < 128) { vec_->at(ele).lastexchange.append(val_->c_str()); } }
			else if (memb == BOT_C_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
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
			else if (memb == BOT_STMT_CSPEC) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).cspec = *val_; }
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
			else if (memb == BOT_PORT_FAM) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fam = *val_; }
			else if (memb == BOT_PORT_PTN) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).portn = *val_; }
			else if (memb == BOT_PORT_PCL) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).proto = *val_; }
			else if (memb == BOT_PORT_SOP) { std::vector <BOT_SOPT>* vp = reinterpret_cast<std::vector<BOT_SOPT>*>(val); size_t siz = 0; vec_->at(ele).sopts.clear(); while (siz < vp->size()) { vec_->at(ele).sopts.push_back(vp->at(siz)); siz++; } }
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
			else if (memb == BOT_PLUG_BDP) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).bndp = *val_; }
			else if (memb == BOT_PLUG_SRV) { bool* val_ = reinterpret_cast<bool*>(val); vec_->at(ele).isserv = *val_; }
			else if (memb == BOT_PLUG_CON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).con = *val_; }
			else if (memb == BOT_PLUG_DSC) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).dsc = *val_; }
			else if (memb == BOT_PLUG_SOP) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).sopt = *val_; }
			else if (memb == BOT_PLUG_QSZ) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).qsiz = *val_; }
			else if (memb == BOT_PLUG_PRT) { bot_port* val_ = reinterpret_cast<bot_port*>(val); vec_->at(ele).prt.Renew(val_); }
			else if (memb == BOT_PLUG_RES) { addrinfo* val_ = reinterpret_cast<addrinfo*>(val); vec_->at(ele).res = val_; }
			else if (memb == BOT_PLUG_PTR) { addrinfo* val_ = reinterpret_cast<addrinfo*>(val); vec_->at(ele).ptr = val_; }
			else if (memb == BOT_PLUG_HNT) { addrinfo* val_ = reinterpret_cast<addrinfo*>(val); vec_->at(ele).hints = *val_; }
			else if (memb == BOT_PLUG_STO) { sockaddr_storage* val_ = reinterpret_cast<sockaddr_storage*>(val); vec_->at(ele).sto = val_; }
			else if (memb == BOT_PLUG_URL) { carr_512* val_ = reinterpret_cast<carr_512*>(val); memcpy((void*)&vec_->at(ele).url, val, sizeof(carr_512)); }
			else if (memb == BOT_PLUG_FAM) { carr_8* val_ = reinterpret_cast<carr_8*>(val); memcpy((void*)&vec_->at(ele).ifam, val, sizeof(carr_8)); }
			else if (memb == BOT_PLUG_IPS) { carr_64* val_ = reinterpret_cast<carr_64*>(val); memcpy((void*)&vec_->at(ele).ipstr, val, sizeof(carr_64)); }
			else if (memb == BOT_PLUG_SVC) { carr_64* val_ = reinterpret_cast<carr_64*>(val); memcpy((void*)&vec_->at(ele).servc, val, sizeof(carr_64)); }
#ifdef _WIN32
			else if (memb == BOT_PLUG_SCK) { SOCKET* val_ = reinterpret_cast<SOCKET*>(val); vec_->at(ele).sck = *val_; }
			else if (memb == BOT_PLUG_TSCK) { SOCKET* val_ = reinterpret_cast<SOCKET*>(val); vec_->at(ele).tsck = *val_; }
#else
			else if (memb == BOT_PLUG_SCK) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).sck = *val_; }
			else if (memb == BOT_PLUG_TSCK) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).tsck = *val_; }
#endif
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
			if (memb == BOT_C_LOGIN_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).login_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).login_name.append(val_);
					}
				}
				else{}
				ret = ele;
			}
			else if (memb == BOT_C_NAME)
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
			if (memb == BOT_C_LOGIN_NAME)
			{
				if (opt == 1)
				{
					_char* val_ = reinterpret_cast<_char*>(val);

					if (val_)
					{
						vec_->at(ele).login_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					c_char* val_ = reinterpret_cast<c_char*>(val);

					if (val_)
					{
						vec_->at(ele).login_name.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_C_NAME)
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

	sint CFV(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
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
	sint CFV(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->logtitle.c_str(), val->logtitle.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<BOT_FILE*> *vec_ = 0, BOT_FILE* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint CFV(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->thread_name.c_str(), val->thread_name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }

	sint CEFV(std::vector<carr_2> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_4> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_8> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_16> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_32> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_64> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_128> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_256> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_512> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_1024> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_2048> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint CEFV(std::vector<carr_4096> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
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
			if (memb == BOT_C_LOGIN_NAME)
			{
				vec_->at(ele).login_name.clear();
				ret = ele;
			}
			else if (memb == BOT_C_NAME)
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
			if (memb == BOT_C_LOGIN_NAME)
			{
				vec_->at(ele).login_name.clear();
				ret = ele;
			}
			else if (memb == BOT_C_NAME)
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
			if (memb == BOT_TTS_VALS)
			{
				vec_->at(ele).vals.clear();
			}
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
			if (memb == BOT_TTS_VALS)
			{
				vec_->at(ele).vals.clear();
			}
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
			else if (memb == BOT_PORT_FAM)
			{
				vec_->at(ele).fam = -1;
				ret = ele;
			}
			else if (memb == BOT_PORT_PTN)
			{
				vec_->at(ele).portn = -1;
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
			else if (memb == BOT_PLUG_BDP)
			{
				vec_->at(ele).bndp = false;
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
			else if (memb == BOT_PLUG_DSC)
			{
				vec_->at(ele).dsc = -1;
				ret = ele;
			}
			else if (memb == BOT_PLUG_SOP)
			{
				vec_->at(ele).sopt = -1;
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
			else if (memb == BOT_PLUG_STO)
			{
				memset((void*)vec_->at(ele).sto, 0, sizeof(sockaddr_storage));
				ret = ele;
			}
			else if (memb == BOT_PLUG_URL)
			{
				bot_strclr(vec_->at(ele).url.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_FAM)
			{
				bot_strclr(vec_->at(ele).ifam.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_IPS)
			{
				bot_strclr(vec_->at(ele).ipstr.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_SVC)
			{
				bot_strclr(vec_->at(ele).servc.carr);
				ret = ele;
			}
			else if (memb == BOT_PLUG_SCK)
			{
#ifdef _WIN32
				vec_->at(ele).sck = INVALID_SOCKET;
#else
				FD_ZERO(vec_->at(ele).sck);
#endif
				ret = ele;
			}
			else if (memb == BOT_PLUG_SCK)
			{
#ifdef _WIN32
				vec_->at(ele).tsck = INVALID_SOCKET;
#else
				FD_ZERO(vec_->at(ele).tsck);
#endif
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

	sint CLNV(std::vector<carr_2> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_4> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_8> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_16> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_32> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_64> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_128> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_256> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_512> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_1024> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_2048> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CLNV(std::vector<carr_4096> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SVIV(vec_, (sint)x, vec_->at(y).carr); z = CEFV(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
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

	void SetTClr(std::chrono::steady_clock::time_point* nt = 0) { if (!nt) { vtclr = std::chrono::steady_clock::now(); } else { vtclr = *nt; } }
	void SetSTool(STool* nstool = 0) { if (!nstool) { return; } stool = nstool; }

private:

	std::chrono::steady_clock::time_point vtclr;
	STool* stool;
};

class bot_strt_up
{
public:

	std::vector<c_char*> litebot_stmts
	{
		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"QUIT\", 0, 1 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"LOGIN\", 0, 2 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"HELP\", 0, 3 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"LOGOUT\", 1, 4 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"DEBUGLEVEL\", 1, 5 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"ADDCOMMAND\", 100, 17 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"READFILE\", 10, 96 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"ADDSCRIPT\", 100, 98 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"RUNSCRIPT\", 100, 99 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"GIPS\", 100, 100 );",

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
		"\"aeiou\", \"0123456789\" );",

		"INSERT INTO litebot.LANGUAGES ( LANGUAGE, ALPHABET, " \
		"U_CASE_CONSONANTS, L_CASE_CONSONANTS, U_CASE_VOWELS, " \
		"L_CASE_VOWELS, NUMBER_SYMS ) VALUES ( \"DUETSCHE\", " \
		"\"Aa��BbCcDdEe��FfGgHhIi��JjKkLlMmNnOo��PpQqRrSs�TtUu��VvWwXxYyZz\", " \
		"\"BCDFGHJKLMNPQRSTVWXY\", \"bcdfghjklmnpqrs�tvwxyz\", \"A�E�I�O�U�\", " \
		"\"a�e�i�o�u�\", \"0123456789\" );"
		/*
		"INSERT INTO litebot.LANGUAGES ( LANGUAGE, ALPHABET, " \
		"U_CASE_CONSONANTS, L_CASE_CONSONANTS, U_CASE_VOWELS, " \
		"L_CASE_VOWELS, NUMBER_SYMS ) VALUES ( \"l337 5p34k\", " \
		"\"Aa��BbCcDdEe��FfGgHhIi��JjKkLlMmNnOo��PpQqRrSs�TtUu��VvWwXxYyZz123456780\", " \
		"\"BCDFGHJKLMNPQRSTVWXY\", \"bcdfghjklmnpqrs�tvwxyz25678\", \"A�E�I�O�U�1340\", " \
		"\"a�e�i�o�u�\", \"0123456789\" );"

		"INSERT INTO litebot.COMMON_SYMS (" \
		"SYMBOL, USAGES ) VALUES (" \
		"\"/#\", \"5\" );"
		*/
	};

	std::vector<BOT_STMT> litebot_pend;

	std::vector<BOT_STMT> sym_pend;

	std::vector<BOT_STMT> code_pend;

	std::vector<c_char*> litebot_tablenames
	{
		"COMMANDS",
		"ACCOUNTS",
		"LANGUAGES"
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
		"COMMAND TEXT " \
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

private:
};

typedef struct log_vec
{
	std::vector<BOT_LOGDET> d_vec;
	std::vector<BOT_LOGDET_M> m_vec;

	log_vec() { d_vec.clear(); m_vec.clear(); }

}LOG_VEC;

typedef struct to_thr_vec
{
	std::vector<TINFO> d_vec;
	std::vector<TINFO_M> m_vec;

	to_thr_vec() { d_vec.clear(); m_vec.clear(); }

}TO_THR_VEC;

typedef struct db_vec
{
	std::vector<BOT_DB> d_vec;
	std::vector<BOT_DB_M> m_vec;

	db_vec() { d_vec.clear(); m_vec.clear(); }

}DB_VEC;

typedef struct c_vec
{
	std::vector<BOT_CLIENT> d_vec;
	std::vector<BOT_CLIENT_M> m_vec;

	c_vec() { d_vec.clear(); m_vec.clear(); }

}C_VEC;

typedef struct fo_vec
{
	std::vector<BOT_FILE> d_vec;
	std::vector<BOT_FILE_M> m_vec;

	fo_vec() { d_vec.clear(); m_vec.clear(); }

}FO_VEC;

class machine
{	
public:
	
	machine(sint i_debug_lvl = BOT_DEBUG_LVL, sint i_debug_m = BOT_DEBUG_M, sint nlid = -1, c_char* i_name = "", bool logmain = false, bool logmine = false);
	sint LITEBot(carr_256 *ncar_ = 0, bool do_start_up = false);
	
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
	float thr_exe_mod;
	std::vector<HELD_MTX> h_mtxs;
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

	std::vector<c_char*> sql_vals_keywords
	{
		"INTEGER",
		"REAL",
		"TEXT",
		"BLOB",
		"NULL"
	};

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

	//it_type
	std::vector<c_char*> sql_trans_keywords
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
	std::vector<c_char*> sql_obj_keywords
	{
		"DATABASE",
		"TABLE",
		"INDEX",
		"COLUMN",
		"VIEW",
		"TRIGGER",
		"ROW"
	};

	//cspec
	std::vector<c_char*> sql_cspec_keywords
	{
		"WHERE",
		"AS",
		"VALUES"
	};

	//targ
	std::vector<c_char*> sql_targ_keywords
	{
		"USING",
		"FROM",
		"ON"
	};

	//opts[0]
	std::vector<c_char*> sql_comp_keywords
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
	std::vector<c_char*> sql_conj_keywords
	{
		"AND",
		"OR",
		"BETWEEN"
	};

	// ospec
	std::vector<c_char*> sql_obj_qual_keywords
	{
		"UNIQUE",
		"TEMP",
		"DISTINCT",
		"VIRTUAL"
	};

	//opts[2][0]
	std::vector<c_char*> sql_decl_keywords
	{
		"ORDER BY",
		"GROUP BY"
	};

	//opts[2][1]
	std::vector<c_char*> sql_order_keywords
	{
		"ASC",
		"DESC"
	};

	//rlim
	std::vector<c_char*> sql_lim_keywords
	{
		"LIMIT"
	};
	

	//ifex
	std::vector<c_char*> sql_cond_qual_keywords
	{
		"IF EXISTS",
		"IF NOT EXISTS"
	};

	//act
	std::vector<c_char*> sql_act_keywords
	{
		"SET",
		"ADD",
		"RENAME TO"
	};
	
	std::vector<_char> nrts_ign
	{
		'\\'
	};

	std::vector<c_char*> nrts_lign
	{
		"//",
		"/*"
	};

	std::vector<c_char*> nrts_lign_
	{
		"\n",
		"*/"
	};

	std::vector<_char> nrts_sep
	{
		' ',
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
		'\n',
		'\0'
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

	/* global mutexes for lists */

	sint LockGMutex(sint g_opt = -1, sint* had_lock = 0, bool sleep_wait = true);
	sint UnlockGMutex(sint g_opt = -1);

	/* locks within lists */

	sint LockElement(sint g_opt = -1, sint ele = -1, sint* had_lock = 0, bool sleep_wait = true, bool is_meta = true);
	sint UnlockElement(sint g_opt = -1, sint ele = -1, bool is_meta = true);

	// Open/Close Global Objects

	sint OpenObject(sint nobj = -1, sint nele = -1, sint is_meta = -1, sint* omode = 0, sint* r_opt = 0, sint* n_opt = 0);
	sint CloseObject(sint nobj = -1, sint nele = -1, sint is_meta = -1, sint* r_opt = 0, sint* n_opt = 0);

	// Manip global lists

	sint PushToVec(void *val_, sint g_opt, bool check = true, bool use_empty = true, bool is_meta = true);
	sint PushToVecEleMem(void *val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, sint v_opt = -1, bool is_meta = true);
	sint GetInVec(void* val_, sint g_opt, bool cine = false, bool is_meta = true);
	sint GetVecEle(void* val_ = 0, sint g_opt = -1, sint ele = -1, bool is_meta = true);
	sint GetEmptyVecEle(sint g_opt, bool is_meta = true, sint mode = -1);
	sint GetVecEleMem(void* val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true);
	sint SetVecEle(void* val_ = 0, sint g_opt = -1, sint ele = -1, bool cine = false, bool is_meta = true);
	sint SetVecEleMem(void* val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true);
	sint ClearVecEle(sint g_opt = -1, sint ele = -1, bool is_meta = true);
	sint ClearVecEleMem(sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true);
	sint VecSize(sint g_opt = -1, bool is_meta = true);
	sint GetElementNames(sint g_opt = -1, std::vector<std::string>* nvec = 0, bool is_meta = true);
	sint GetElementIDs(sint g_opt = -1, std::vector<sint> *nvec = 0, bool is_meta = true);

	// Date / Time 

	sint GetDateTimeMS(_char str_[] = 0, bool form = true);
	sint GetDateTime(_char str_[] = 0, bool form = true);
	sint GetTime(_char str_[] = 0, bool forms = true);
	sint GetTimeMS(_char str_[] = 0, bool forms = true);
	sint GetDate(carr_32* str_ = 0, bool form = true);
	sllint GetCentSec();

	// Log Function

	sint UsingLog(_char nm[] = 0);
	sint LogName(sint opt, carr_256* nm = 0, carr_32* dat = 0, bool tomine = false);
	sint LogPut(c_char* msg_ = "", sint option = -1);

	// Commands

	sint Command(std::vector<std::string> *vec_ = 0);

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
	sint BOTScanFileSyms(BOT_FILE_M *file_ = 0);
	sint DetSep(BOT_FILE_M* file_ = 0);
	sint BOTRendFileSyms(BOT_FILE_M *file_ = 0);
	sint BOTKnownFormat(BOT_FILE_M* file_ = 0);
	sint BOTFileStats(BOT_FILE_M *file_ = 0, bool doscan = false, sint scan_lvl = -1);
	sint BOTCreateFile(BOT_FILE_M* file_ = 0, sint* was_open = 0);
	sint BOTRemoveFile(BOT_FILE_M *xfile_ = 0);
	sint BOTRenameFile(BOT_FILE_M *xfile_ = 0, c_char* nnm = 0);
	sint BOTOpenFile(sint flid = -1, sint *was_open = 0, bool cine = false, bool r_to_st = false, bool dtp = false);
	sint BOTOpenFile(BOT_FILE_M* mfile_ = 0, sint *was_open = 0, bool cine = false, bool r_to_st = false, bool dtp = false);
	sint BOTFindInFile(BOT_FILE_M* file_ = 0, bool indat = false, size_t f = 0, size_t t = 0, void* f_ = 0, size_t len = 0);
	sint BOTFileOUT(BOT_FILE_M* file_ = 0, size_t f = 0, bool to_fdat = false, ...);
	sint BOTFileIN(BOT_FILE_M* file_ = 0, bool f_fdat = false, size_t from = -1, size_t to = -1, ...);
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
	sint ClearClient(BOT_CLIENT *c_) { if (c_) { c_->Clear(); return 0; } return -1; }
	bool GetClientLoggedIn();
	sint SetClientLoggedIn(bool x);	

	// Console I/O Functions

	sint Output(c_char* op_ = "", ...);
	sint BotOut(sint num = 0, ...);
	sint BotOut(c_char* str_ = "");
	sint SOutput(c_char* op_ = "", sint o = 0);
	sint Input(std::string* np = 0, bool itrp = true);
	sint DoOutput();
	sint InterpretInput(std::string *input_ = 0);
	std::string DetermineOutput();
	sint BOTConsole();
	sint ArgSep(std::vector <std::string>* ret_ = 0, c_char* val = 0, size_t f = 0, size_t t = 0, carr_4* sep = 0);
	sint ArgSep(std::vector <std::string>* ret_ = 0, c_char* val = 0, carr_4* sep = 0);
	sint ArgSep(std::vector <std::string>* ret_ = 0, c_char* val = 0, ...);

	// Str Manip

	std::string CleanPunctuation(c_char* i_ = "");
	std::string Uppercase(c_char* str_ = "");
	std::string LEncStrI(c_char* str_ = "", sint opt = -1);
	sint OrdLocs(std::vector<size_t>* litlocs_ = 0, std::vector<size_t>* locs_ = 0, c_char* str_ = 0);
	sint OrdEnc(size_t at_loc = 0, std::vector<size_t>* litlocs_ = 0, std::vector<size_t>* locs_ = 0, c_char* str_ = 0);
	sint LitLocs(std::vector<size_t>* locs_, c_char* str_);
	sint LitEnc(size_t at_loc, std::vector<size_t>* locs_, c_char* str_);
	bool XEnclosedInY(std::vector<size_t>* ll_ = 0, std::string* stmts_ = 0, sint sc_loc = -1, sint x_loc = -1, std::string* fy_char = 0);
	bool XEnclosedInY(std::vector<size_t>* ll_ = 0, c_char* stmts_ = "", sint sc_loc = -1, sint x_loc = -1, _char fy_char = '\0');

	// SQL statement manip

	sint SeparateSQL(std::string* stmts_ = 0, std::vector<std::string>* vec_ = 0);
	sint AnalyzeStmt(BOT_STMT *t_ = 0);
	sint BQS(BOT_STMT *t_ = 0);
	sint BTS(BOT_STMT *t_ = 0);
	sint BuildStatements(std::vector<BOT_STMT>* stmts_ = 0, BOT_COMMIT *com_ = 0, std::vector<BOT_STMT>* pend_ = 0);
	sint OutpuTINFO(BOT_STMT *t_ = 0);

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
	sint GetLogin(c_char* str_ = "");
	sint UpdateAccount(BOT_CLIENT *Client_ = 0);
	sint GetLastAccess(BOT_DB_M *dbs_ = 0, sint *lmo_ = 0, sint *lmo_ns = 0, sint *lma_ = 0, sint *lma_ns = 0);
	sint LastAccessMaintenance(BOT_DB_M *dbs_ = 0);
	sint PushToDBList(BOT_DB *dbs_ = 0);

	// Pthreads Functions

	sint StartThread(sint* thr_opt = 0);
	sint ThreadRest(sllint dur = BOT_MILLI_REST, sint qt_lvl = -1);
	sint ThreadEnd(std::vector<ullint>* rvals_ = 0);
	sint PThreadErr(_char in_chr[], sint err);
	sint IncrThreads();
	sint DecrThreads();
	sint GetThreadsCt();
	sint GetThreadQuit();
	sint SetThreadQuit(sint val = -1);
	sint StopAllThreads();
	sint JoinThread(sint thrid = -1, void* vp_ = 0);
	sint InitThread(TINFO_M *tts_ = 0, sint* ret_ = 0);
	sint InitThreads(std::vector<TINFO_M> *tts_ = 0, std::vector<sint>* rets_ = 0);
	sint CreateThread(TINFO_M* tts_ = 0, sint* ret_ = 0);
	sint FinishThread(TINFO_M* tts_ = 0, sint* ret_ = 0);
	sint MT();
	sint TM(uint* is_s = 0);
	sllint TestThreadIter(sint to_ = (sint)BOT_ITER_TO);
	sllint TestThreadTRat(sint to_ = (sint)BOT_ITER_TO);
	sint CheckPrintFs();

	// work

	sint ProcErrLog(sint opt = -1, c_char* in_file_p = "", c_char* in_file_n = "", c_char* in_file_t = "", c_char* rampid = "", c_char* insp_type = "", c_char* date_ = "", c_char* eid_ = "", c_char* toval_ = "");
	sint ProcVINs(sint opt = -1, c_char* in_file_p = "", c_char* in_file_n = "", c_char* in_file_t = "", c_char* rampid = "", c_char* insp_type = "", c_char* date_ = "", c_char* eid_ = "", c_char* toval_ = "");
	sint GetVINs(c_char* in_file_p = "", c_char* in_file_n = "", c_char* in_file_t = "", c_char* rampid = "");
	sint AddDlrCode(c_char* to_vin = "", c_char* in_file = "");

	static void* DBMaintenance(void* vp_ = 0);
	static void* LITEBotMaintenance(void* vp_ = 0);
	static void* CodeMaintenance(void* vp_ = 0);
	static void* LogMaintenance(void* vp_ = 0);
	static void* TestThread(void* vp_ = 0);
	static void* ConsoleThread(void* vp_ = 0);
	static void* ScanFileThread(void* vp_ = 0);
	static void* RendFileThread(void* vp_ = 0);
	static void* GIPS(void* vp_ = 0);
	static void* ServThread(void* vp_ = 0);
	static void* CliThread(void* vp_ = 0);
};

#endif