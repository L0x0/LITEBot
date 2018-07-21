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

//#define _BOT_FOR_ANDR_ 1

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include "../_includes/_win/dirent.h"
#include "../_includes/_win/sched.h"
#include "../_includes/_win/semaphore.h"
#include "../_includes/_win/pthread.h"
#include "../_includes/_win/sqlite3.h"
#define mode_t unsigned short
#define nlink_t unsigned long long
#define uid_t unsigned long long
#define gid_t unsigned long long
#else
#ifdef _BOT_FOR_ANDR_
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include "../_includes/_andr/sqlite3.h"
#ifndef errno_t
#define errno_t signed short
#endif
#else
#ifdef __GNUC__
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
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
#if (BOTTHREAD_MAX > _POSIX_THREAD_THREADS_MAX)
#define BOTTHREAD_MAX _POSIX_THREAD_THREADS_MAX
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

// How deeply we scan files while scanning directories
#ifndef BOT_DIRSCAN_LVL
#define BOT_DIRSCAN_LVL 0
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

#ifdef _WIN32
#define BOT_NOFLD_V std::vector<std::string>{ "$", ".", "..", "Windows", "WINDOWS", "WINDOWS" }
#else
#define BOT_NOFLD_V std::vector<std::string>{ "$", ".", ".." }
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

#ifndef BOT_DB_NM
#define BOT_DB_NM "_bot_dbs"
#else
#if (strlen(BOT_DB_NM) > 1024)
#define BOT_DB_NM "_bot_dbs"
#else
#if (strlen(BOT_DB_NM) < 4)
#define BOT_DB_NM "_bot_dbs"
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

#ifndef BOT_DEBUG_LVL
#define BOT_DEBUG_LVL 10
#endif
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

#ifndef BOT_ITER_TO
#define BOT_ITER_TO 100
#else
#if (BOT_ITER_TO > 100)
#define BOT_ITER_TO 100
#else
#if (BOT_ITER_TO < 2)
#define BOT_ITER_TO 2
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

#ifndef BOT_FILE_APPEND
#define BOT_FILE_APPEND (std::ios::out | std::ios::ate | std::ios::app)
#endif

#ifndef BOT_FILE_OVERW
#define BOT_FILE_OVERW (std::ios::in | std::ios::out)
#endif

#ifndef BOT_FILE_WRITE
#define BOT_FILE_WRITE (std::ios::in | std::ios::out | std::ios::ate | std::ios::app)
#endif

#ifndef BOT_FILE_READ
#define BOT_FILE_READ (std::ios::in)
#endif

#ifndef BOT_FILE_READATE
#define BOT_FILE_READATE (std::ios::in | std::ios::ate)
#endif

#ifndef BOT_FILE_WATE
#define BOT_FILE_WATE (std::ios::out | std::ios::ate)
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
#define BOT_FS_LIM 15
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
#define BOT_LOGREST (BOT_MILLI_REST*500)
#endif

#ifndef BOT_DBREST
#define BOT_DBREST (BOT_MILLI_REST*1000)
#endif

#ifndef BOT_THRREST
#define BOT_THRREST (BOT_MILLI_REST*100)
#endif

#ifndef BOT_QUITREST
#define BOT_QUITREST (BOT_MILLI_REST*200)
#endif

#ifndef BOT_REQREST
#define BOT_REQREST BOT_NANO_REST
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

sint bot_str_err(sint err_no = 0, c_char* msg = "")
{
	switch (err_no)
	{
	case 0:
	{
		msg = (c_char*)BOT_NOERROR_STR;
		break;
	}
	case -1:
	{
		msg = (c_char*)BOT_ERRORLIM_STR;
		break;
	}
	case -2:
	{
		msg = (c_char*)BOT_ERRORNINV_STR;
		break;
	}
	case -4:
	{
		msg = (c_char*)BOT_ERRORPREC_STR;
		break;
	}
	case -5:
	{
		msg = (c_char*)BOT_ERRORFPREC_STR;
		break;
	}
	default:
	{
		msg = (c_char*)BOT_ERRORUK_STR;
		return -1;
		break;
	}
	}
	return 0;
}

const size_t bot_sintlen(sint val[] = 0)
{
	if (!val)
	{
		return 0;
	}
	sint term = (sint)INT32_MIN;
	size_t siz = 0;

	while (siz < (size_t)BOT_STRLEN_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(term)))
		{
			const size_t csiz = siz;
			return csiz;
		}
		siz++;
	}
	return 0;
}

const size_t bot_uintlen(uint val[] = 0)
{
	if (!val)
	{
		return 0;
	}
	uint term = (uint)UINT32_MAX;
	size_t siz = 0;

	while (siz < (size_t)BOT_STRLEN_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(term)))
		{
			const size_t csiz = siz;
			return csiz;
		}
		siz++;
	}
	return 0;
}

const size_t bot_dbllen(double val[] = 0)
{
	if (!val)
	{
		return 0;
	}
	double term = (double)DBL_MIN;
	size_t siz = 0;

	while (siz < (size_t)BOT_STRLEN_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(term)))
		{
			const size_t csiz = siz;
			return csiz;
		}
		siz++;
	}
	return 0;
}

const size_t bot_ustrlen(u_char val[] = 0)
{
	if (!val)
	{
		return 0;
	}
	u_char term = (u_char)'\0';
	size_t siz = 0;
	
	while (siz < (size_t)BOT_STRLEN_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(term)))
		{
			const size_t csiz = siz;
			return csiz;
		}
		siz++;
	}
	return 0;
}

const size_t bot_custrlen(cu_char val[] = 0)
{
	if (!val)
	{
		return 0;
	}
	cu_char* term{ (cu_char*)"\0" };
	size_t siz = 0;

	while (siz < (size_t)BOT_STRLEN_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)term, sizeof(term)))
		{
			const size_t csiz = siz;
			return csiz;
		}
		siz++;
	}
	return 0;
}

void bot_strcpy(_char inv[] = 0, _char val[] = 0)
{
	if (!inv || !val)
	{
		return;
	}
	
	size_t isiz = strlen(inv);

	if (!isiz || isiz > BOT_STRLEN_MAX)
	{
		return;
	}
	
	_char term = '\0';

	for (size_t nsiz = 0; nsiz < isiz; nsiz++)
	{
		memcpy((void*)&inv[nsiz], (void*)&val[nsiz], sizeof(inv[nsiz]));

		if (!memcmp((void*)&val[nsiz], (void*)&term, 1))
		{
			return;
		}
	}
	memcpy((void*)&inv[isiz-1], (void*)&term, sizeof(inv[isiz-1]));
}

void bot_ustrcpy(u_char inv[] = 0, u_char val[] = 0)
{
	if (!inv || !val)
	{
		return;
	}

	size_t isiz = bot_ustrlen(inv);

	if (!isiz || isiz > BOT_STRLEN_MAX)
	{
		return;
	}

	u_char term = '\0';

	for (size_t nsiz = 0; nsiz < isiz; nsiz++)
	{
		memcpy((void*)&inv[nsiz], (void*)&val[nsiz], sizeof(inv[nsiz]));

		if (!memcmp((void*)&val[nsiz], (void*)&term, 1))
		{
			return;
		}
	}
	memcpy((void*)&inv[isiz - 1], (void*)&term, sizeof(inv[isiz - 1]));
}

void bot_strclr(_char inchr[] = 0)
{
	if (!inchr)
	{
		return;
	}
	inchr = { 0 };
}

void bot_ustrclr(u_char inchr[] = 0)
{
	if (!inchr)
	{
		return;
	}
	inchr = { 0 };
}

void bot_cstrclr(c_char inchr[] = 0)
{
	if (!inchr)
	{
		return;
	}

	_char term = '\0';
	size_t x = strlen(inchr);
	
	for (size_t y = 0; y < x; y++)
	{
		memcpy((void*)&inchr[y], (void*)&term, 1);
	}
}

void bot_custrclr(cu_char inchr[] = 0)
{
	if (!inchr)
	{
		return;
	}

	u_char term = '\0';
	size_t x = bot_custrlen(inchr);

	for (size_t y = 0; y < x; y++)
	{
		memcpy((void*)&inchr[y], (void*)&term, 1);
	}
}

sint bot_strchk(_char inchr[] = 0, size_t in_siz = 0)
{
	if (!inchr || !in_siz)
	{
		return -1;
	}
	size_t siz = 0;
	_char term = '\0';

	while (siz < in_siz)
	{
		if (!memcmp((void*)&inchr[siz], (void*)&term, 1))
		{
			return (sint)siz;
		}
		siz++;
	}
	if (siz == in_siz)
	{
		inchr[in_siz - 1] = '\0';
		std::cout << "*BOTSTRERROR* _char[]: \"" << inchr << "\" was without a terminating NULL byte.*BOTSTRERROR*" << std::endl;
	}
	return (sint)siz;
}

sint bot_ustrchk(u_char inchr[] = 0, size_t in_siz = 0)
{
	if (!inchr || !in_siz)
	{
		return -1;
	}
	size_t siz = 0;
	u_char term = (u_char)'\0';

	while (siz < in_siz)
	{
		if (!memcmp((void*)&inchr[siz], (void*)&term, 1))
		{
			return (sint)siz;
		}
		siz++;
	}
	if (siz == in_siz)
	{
		inchr[in_siz - 1] = '\0';
		std::cout << "*BOTUSTRERROR* u_char[]: \"" << inchr << "\" was without a terminating NULL byte.*BOTUSTRERROR*" << std::endl;
	}
	return (sint)siz;
}

sint bot_randstr(_char str_[] = 0, size_t siz = 0, _char fstr_[] = 0, size_t fsiz = 0)
{
	if (!siz || !str_)
	{
		return -1;
	}

	std::chrono::high_resolution_clock::time_point tI = std::chrono::high_resolution_clock::now();

	if (!fstr_)
	{
		
		_char cfr[64] = { 'W', 'E', 'R', 'n', 'I', 'Z', 'O', 'm', 'P', 'S', 'D', 'F', '5', 'u', 'J', 'K', 'v', 'b', 'y', 'i', '4', '2', 's', 'B', '_', 'L', 'X', 'C', '9', 'V', 'M', 'q', 'c', 'w', 'T', 'Y', 'e', 'r', 'f', '6', 't', 'U', 'A', 'o', 'Q', 'p', 'a', 'F', 'u', 'd', '1', '0', 'g', 'N', 'j', 'k', 'l', 'z', '8', 'x', '3', '7', 'h', '\0' };
		siz--;

		for (size_t x = 0; x < siz; x++)
		{
			std::chrono::high_resolution_clock::time_point tII = std::chrono::high_resolution_clock::now();
			std::chrono::duration<slint, std::nano> dur = std::chrono::duration_cast<std::chrono::duration<slint, std::nano>>(tII - tI);
			srand((slint)dur.count());
			memcpy((void*)&str_[x], (void*)&cfr[rand() % 63], 1);
		}
		memcpy((void*)&str_[siz], (void*)&cfr[63], 1);
		return 0;
	}
	else
	{
		siz--;
		fsiz--;
		_char term = '\0';
		memcpy((void*)&str_[siz], (void*)&term, sizeof(term));
		 0;

		for (; siz; siz--)
		{
			std::chrono::high_resolution_clock::time_point tII = std::chrono::high_resolution_clock::now();
			std::chrono::duration<slint, std::nano> dur = std::chrono::duration_cast<std::chrono::duration<slint, std::nano>>(tII - tI);
			srand((slint)dur.count());
			memcpy((void*)&str_[siz], (void*)&fstr_[rand() % fsiz], 1);
		}
		return 0;
	}
	return -1;
}

sint bot_sprintf(_char inchr[] = 0, size_t in_siz = 0, c_char* fstr = 0, ...)
{
	if (!inchr || !in_siz || in_siz > BOT_STRLEN_MAX || !fstr)
	{
		return -1;
	}

	sint ret = -1;
	uint strsiz = strlen(fstr);
	std::vector<std::string> fspecs;
	std::vector<uint> locs;
	std::string formspec;
	_char frm = '%';
	_char spec = '.';
	_char term = '\0';

	for (uint siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr[siz], (void*)&frm, 1))
		{
			formspec.push_back(fstr[siz]);
			bool mustnum = false;

			for (uint nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, 1))
				{
					if (!mustnum)
					{
						mustnum = true;
					}

					formspec.push_back(fstr[siz + nsiz]);
					nsiz++;

					switch (fstr[siz + nsiz])
					{
					case '-':
					case '+':
					case 'E':
					case 'e':
					case 'x':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case '0':
					{
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (fstr[siz + nsiz])
					{
					case 'l':
					case '-':
					case '+':
					case '0':
					case '2':
					case 'x':
					case 'e':
					case 'h':
					case 'E':
					{
						if (!mustnum)
						{
							mustnum = true;
						}
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
						break;
					}
					case 'd':
					case 'f':
					case 'u':
					case 'i':
					case 'X':
					{
						formspec.push_back(fstr[siz + nsiz]);
						fspecs.push_back(formspec);
						locs.push_back(siz);
						formspec.clear();
						siz += nsiz;
						nsiz = strsiz;
						break;
					}
					case 's':
					case 'c':
					{
						if (!mustnum)
						{
							formspec.push_back(fstr[siz + nsiz]);
							locs.push_back(siz);
							fspecs.push_back(formspec);
							formspec.clear();
							siz += nsiz;
							nsiz = strsiz;
						}
						else
						{
							memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
							return -2;
						}
						break;
					}
					case 'v':
					{
						if (!mustnum)
						{
							sint done = 0;
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							if (siz + nsiz < strsiz)
							{
								if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(spec)))
								{
									formspec.push_back(fstr[siz + nsiz]);

									while (siz + nsiz < strsiz)
									{
										nsiz++;

										if (siz + nsiz < strsiz)
										{
											formspec.push_back(fstr[siz + nsiz]);

											if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(spec)))
											{
												locs.push_back(siz);
												fspecs.push_back(formspec);
											}
										}
									}
								}
							}

							formspec.clear();
							siz += nsiz;
							nsiz = strsiz;
						}
						else
						{
							memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
							return -2;
						}
						break;
					}
					default:
					{
						memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
						return -3;
						break;
					}
					}
				}
			}
		}
	}

	_char lenchr = 'l';

	if (!fspecs.empty())
	{
		uint siz = 0;
		uint at_inchr = 0;
		va_list args;
		va_start(args, fstr);

		for (siz = 0; siz < fspecs.size() && at_inchr < in_siz; siz++)
		{
			uint hlong = 0;
			uint sloc = 0;

			if (siz)
			{
				sloc = locs[siz - 1];
			}

			while (sloc < locs[siz] && at_inchr < in_siz)
			{
				memcpy((void*)&inchr[at_inchr], (void*)&fstr[sloc], sizeof(fstr[sloc]));
				at_inchr += sizeof(fstr[sloc]);
				sloc += sizeof(fstr[sloc]);
			}

			if (fspecs[siz].length() > 1)
			{
				sint isiz = 0;
				uint nsiz = 1;

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
				{
					_char fchr[3]{ 0 };
					nsiz++;
					uint fsiz = 0;

					while (fsiz < 3 && nsiz < fspecs[siz].length())
					{
						switch (fspecs[siz][nsiz])
						{
						case '+':
						case '-':
						case 'E':
						case 'e':
						case 'h':
						case 'x':
						{
							if (fsiz)
							{
								va_end(args);
								memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
								c_char* msg = "";
								sint op = bot_str_err(-5, msg);
								return -5;
							}
							nsiz++;
							break;
						}
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case '0':
						{
							memcpy((void*)&fchr[fsiz], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							memcpy((void*)&fchr[fsiz], (void*)&term, sizeof(term));
							break;
						}
						}

						if (fsiz == 3)
						{
							memcpy((void*)&fchr[fsiz - 1], (void*)&term, sizeof(term));
						}
						else
						{
							if (!memcmp((void*)&fchr[fsiz], (void*)&term, sizeof(term)))
							{
								fsiz = 3;
							}
						}
					}
					if (!memcmp((void*)&fchr[2], (void*)&term, sizeof(term)) || !memcmp((void*)&fchr[1], (void*)&term, sizeof(term)) || !memcmp((void*)&fchr[0], (void*)&term, sizeof(term)))
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (!memcmp((void*)&fspecs[siz][nsiz], (void*)&lenchr, sizeof(lenchr)))
				{
					hlong++;
					nsiz++;
				}

				_char zchar = '0';
				_char zweichar = '2';
				
				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&zchar, sizeof(zchar)) && nsiz < fspecs[siz].length())
				{
					if (!memcmp((void*)&fspecs[siz][nsiz + 1], (void*)&zweichar, sizeof(zweichar)))
					{
						nsiz += 2;
					}
				}

				switch (fspecs[siz][nsiz])
				{
				case 'i':
				{
					_char ci[21]{ 0 };

					if (!hlong)
					{
						sint inv = va_arg(args, sint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						slint inv = va_arg(args, slint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 2)
					{
						sllint inv = va_arg(args, sllint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else {}

					sint xc = bot_strchk(ci, 21);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 'u':
				{
					_char ci[21]{ 0 };

					if (!hlong)
					{
						uint inv = va_arg(args, uint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						ulint inv = va_arg(args, ulint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 2)
					{
						ullint inv = va_arg(args, ullint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else {}

					sint xc = bot_strchk(ci, 21);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 'f':
				{
					double inv = va_arg(args, double);
					float ninv = (float)inv;
					_char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 'd':
				{
					_char ci[64]{ 0 };

					if (!hlong)
					{
						double inv = va_arg(args, double);
						sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						long double inv = va_arg(args, long double);
						sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					}
					else {}

					sint xc = bot_strchk(ci, 64);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 's':
				{
					c_char* str = va_arg(args, c_char*);
					_char cmp = '\0';
					sloc = 0;

					for (sloc = 0; sloc < BOT_STRLEN_MAX && at_inchr < in_siz; sloc++)
					{
						if (memcmp(&str[sloc], &cmp, sizeof(cmp)))
						{
							memcpy((void*)&inchr[at_inchr], (void*)&str[sloc], sizeof(str[sloc]));
							at_inchr++;
						}
						else
						{
							sloc = BOT_STRLEN_MAX;
						}
					}
					break;
				}
				case 'c':
				{
					sint inv_ = va_arg(args, sint);
					_char inv = (_char)inv_;

					if (at_inchr < in_siz)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&inv, sizeof(inv));
						at_inchr++;
					}
					break;
				}
				case 'X':
				{
#ifdef _WIN32
					u_char inv_ = va_arg(args, u_char);
#else
					sint sinv_ = va_arg(args, sint);
					u_char inv_ = (u_char)sinv_;
#endif
					const size_t usiz = (sizeof(inv_) * 2) + 1;

					if (usiz <= in_siz)
					{
						_char ci[usiz]{ 0 };
						sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, sizeof(ci));

						for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
						{
							memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
							at_inchr++;
						}
					}
					break;
				}
				case 'v':
				{
					nsiz++;
					if (nsiz < fspecs[siz].length())
					{
						if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
						{
							_char sep[4]{ 0 };
							_char fspec[4]{ 0 };
							uint nct = 0;

							while (nsiz < fspecs[siz].length() && nct < 3)
							{
								nsiz++;

								if (nsiz < fspecs[siz].length())
								{
									switch (fspecs[siz][nsiz])
									{
									case '.':
									{
										if (nct)
										{
											nct = 3;
										}
										break;
									}
									case 'l':
									{
										hlong++;
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nct++;
										break;
									}
									case 'c':
									case 'i':
									case 's':
									case 'f':
									case 'd':
									case 'u':
									case 'X':
									{
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nsiz++;
										nct = 3;
										break;
									}
									default:
									{
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nsiz++;
										nct++;
										break;
									}
									}
								}
							}
							if (nsiz < fspecs[siz].length())
							{
								for (uint x = 0; x < sizeof(sep) && nsiz < fspecs[siz].length(); x++)
								{
									if (memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
									{
										memcpy((void*)&sep[x], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
									}
									else
									{
										nsiz = fspecs[siz].length();
									}
									nsiz++;
								}
							}

							size_t flen = strlen(fspec);

							if (flen)
							{
								flen--;
								size_t slen = strlen(sep) - 1;;

								switch (fspec[flen])
								{
								case 'c':
								{
									std::vector<_char>* inv = va_arg(args, std::vector<_char>*);

									for (uint x = 0; x < inv->size(); x++)
									{
										if (at_inchr < in_siz)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&inv->at(x), sizeof(inv->at(x)));
											at_inchr++;
										}
										if (slen)
										{
											for (sloc = 0; sloc < strlen(sep) && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&sep[sloc], sizeof(sep[sloc]));
												at_inchr++;
											}
										}
									}
									break;
								}
								case 's':
								{
									/*when specifying %v.<type><sep>. <type> = 's' we use a vector of std::string instead of a vector of c_char* */
									std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

									for (uint x = 0; x < strv->size(); x++)
									{
										for (sloc = 0; sloc < strv->at(x).length() && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&strv->at(x)[sloc], sizeof(strv->at(x)[sloc]));
											at_inchr++;
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
												at_inchr++;
											}
										}
									}
									break;
								}
								case 'f':
								{
									std::vector<float>* fvec = va_arg(args, std::vector<float>*);

									for (uint x = 0; x < fvec->size(); x++)
									{
										_char ci[64]{ 0 };
										sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
										xc = bot_strchk(ci, 64);

										for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
											at_inchr++;
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
												at_inchr++;
											}
										}
									}
									break;
								}
								case 'd':
								{
									if (!hlong)
									{
										std::vector<double>* fvec = va_arg(args, std::vector<double>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<long double>* fvec = va_arg(args, std::vector<long double>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else {}
									break;
								}
								case 'i':
								{
									if (!hlong)
									{
										std::vector<sint>* fvec = va_arg(args, std::vector<sint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<slint>* fvec = va_arg(args, std::vector<slint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 2)
									{
										std::vector<sllint>* fvec = va_arg(args, std::vector<sllint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else {}
									break;
								}
								case 'u':
								{
									if (!hlong)
									{
										std::vector<uint>* fvec = va_arg(args, std::vector<uint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<ulint>* fvec = va_arg(args, std::vector<ulint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 2)
									{
										std::vector<ullint>* fvec = va_arg(args, std::vector<ullint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else {}
									break;
								}
								case 'X':
								{
									std::vector<u_char>* inv = va_arg(args, std::vector<u_char>*);

									for (uint x = 0; x < inv->size(); x++)
									{
										const size_t usiz = (sizeof(inv->at(x)) * 2) + 1;

										if (usiz + at_inchr <= in_siz)
										{
											_char ci[usiz]{ 0 };
											sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv->at(x));
											xc = bot_strchk(ci, sizeof(ci));

											for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;

												if (slen)
												{
													for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
													{
														memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
														at_inchr++;
													}
												}
											}
										}
									}
									break;
								}
								case 'v':
								{
									break;
								}
								default:
								{
									break;
								}
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
			}
			locs[siz] += fspecs[siz].length();
		}

		va_end(args);

		if (!locs.empty())
		{
			if (locs[siz - 1] < strsiz)
			{
				while (locs[siz - 1] < strsiz && at_inchr < in_siz)
				{
					memcpy((void*)&inchr[at_inchr], (void*)&fstr[locs[siz - 1]], sizeof(fstr[locs[siz - 1]]));
					locs[siz - 1]++;
					at_inchr++;
				}
			}
		}
		if (at_inchr < in_siz)
		{
			memcpy((void*)&inchr[at_inchr], (void*)&term, sizeof(term));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(term));
		}
	}
	else
	{
		uint siz = 0;

		while (siz < in_siz && siz < strsiz)
		{
			memcpy((void*)&inchr[siz], (void*)&fstr[siz], sizeof(fstr[siz]));
			siz++;
		}
		if (siz < in_siz)
		{
			memcpy((void*)&inchr[siz], (void*)&term, sizeof(term));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(term));
		}
	}
	return ret;
}

sint bot_sprintf(c_char inchr[] = 0, size_t in_siz = 0, c_char* fstr = 0, ...)
{
	if (!inchr || !in_siz || in_siz > BOT_STRLEN_MAX || !fstr)
	{
		return -1;
	}

	sint ret = -1;
	uint strsiz = strlen(fstr);
	std::vector<std::string> fspecs;
	std::vector<uint> locs;
	std::string formspec;
	_char frm = '%';
	_char spec = '.';
	_char term = '\0';

	for (uint siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr[siz], (void*)&frm, 1))
		{
			formspec.push_back(fstr[siz]);
			bool mustnum = false;

			for (uint nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, 1))
				{
					if (!mustnum)
					{
						mustnum = true;
					}

					formspec.push_back(fstr[siz + nsiz]);
					nsiz++;

					switch (fstr[siz + nsiz])
					{
					case '-':
					case '+':
					case 'E':
					case 'e':
					case 'x':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case '0':
					{
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (fstr[siz + nsiz])
					{
					case 'l':
					case '-':
					case '+':
					case '0':
					case '2':
					case 'x':
					case 'e':
					case 'h':
					case 'E':
					{
						if (!mustnum)
						{
							mustnum = true;
						}
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
						break;
					}
					case 'd':
					case 'f':
					case 'u':
					case 'i':
					case 'X':
					{
						formspec.push_back(fstr[siz + nsiz]);
						fspecs.push_back(formspec);
						locs.push_back(siz);
						formspec.clear();
						siz += nsiz;
						nsiz = strsiz;
						break;
					}
					case 's':
					case 'c':
					{
						if (!mustnum)
						{
							formspec.push_back(fstr[siz + nsiz]);
							locs.push_back(siz);
							fspecs.push_back(formspec);
							formspec.clear();
							siz += nsiz;
							nsiz = strsiz;
						}
						else
						{
							memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
							return -2;
						}
						break;
					}
					case 'v':
					{
						if (!mustnum)
						{
							sint done = 0;
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							if (siz + nsiz < strsiz)
							{
								if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(spec)))
								{
									formspec.push_back(fstr[siz + nsiz]);

									while (siz + nsiz < strsiz)
									{
										nsiz++;

										if (siz + nsiz < strsiz)
										{
											formspec.push_back(fstr[siz + nsiz]);

											if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(spec)))
											{
												locs.push_back(siz);
												fspecs.push_back(formspec);
											}
										}
									}
								}
							}

							formspec.clear();
							siz += nsiz;
							nsiz = strsiz;
						}
						else
						{
							memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
							return -2;
						}
						break;
					}
					default:
					{
						memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
						return -3;
						break;
					}
					}
				}
			}
		}
	}

	_char lenchr = 'l';

	if (!fspecs.empty())
	{
		uint siz = 0;
		uint at_inchr = 0;
		va_list args;
		va_start(args, fstr);

		for (siz = 0; siz < fspecs.size() && at_inchr < in_siz; siz++)
		{
			uint hlong = 0;
			uint sloc = 0;

			if (siz)
			{
				sloc = locs[siz - 1];
			}

			while (sloc < locs[siz] && at_inchr < in_siz)
			{
				memcpy((void*)&inchr[at_inchr], (void*)&fstr[sloc], sizeof(fstr[sloc]));
				at_inchr += sizeof(fstr[sloc]);
				sloc += sizeof(fstr[sloc]);
			}

			if (fspecs[siz].length() > 1)
			{
				sint isiz = 0;
				uint nsiz = 1;

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
				{
					_char fchr[3]{ 0 };
					nsiz++;
					uint fsiz = 0;

					while (fsiz < 3 && nsiz < fspecs[siz].length())
					{
						switch (fspecs[siz][nsiz])
						{
						case '+':
						case '-':
						case 'E':
						case 'e':
						case 'h':
						case 'x':
						{
							if (fsiz)
							{
								va_end(args);
								memcpy((void*)&inchr[0], (void*)&term, sizeof(term));
								c_char* msg = "";
								sint op = bot_str_err(-5, msg);
								return -5;
							}
							nsiz++;
							break;
						}
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case '0':
						{
							memcpy((void*)&fchr[fsiz], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							memcpy((void*)&fchr[fsiz], (void*)&term, sizeof(term));
							break;
						}
						}

						if (fsiz == 3)
						{
							memcpy((void*)&fchr[fsiz - 1], (void*)&term, sizeof(term));
						}
						else
						{
							if (!memcmp((void*)&fchr[fsiz], (void*)&term, sizeof(term)))
							{
								fsiz = 3;
							}
						}
					}
					if (!memcmp((void*)&fchr[2], (void*)&term, sizeof(term)) || !memcmp((void*)&fchr[1], (void*)&term, sizeof(term)) || !memcmp((void*)&fchr[0], (void*)&term, sizeof(term)))
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (!memcmp((void*)&fspecs[siz][nsiz], (void*)&lenchr, sizeof(lenchr)))
				{
					hlong++;
					nsiz++;
				}

				_char zchar = '0';
				_char zweichar = '2';

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&zchar, sizeof(zchar)) && nsiz < fspecs[siz].length())
				{
					if (!memcmp((void*)&fspecs[siz][nsiz + 1], (void*)&zweichar, sizeof(zweichar)))
					{
						nsiz += 2;
					}
				}

				switch (fspecs[siz][nsiz])
				{
				case 'i':
				{
					_char ci[21]{ 0 };

					if (!hlong)
					{
						sint inv = va_arg(args, sint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						slint inv = va_arg(args, slint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 2)
					{
						sllint inv = va_arg(args, sllint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else {}

					sint xc = bot_strchk(ci, 21);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 'u':
				{
					_char ci[21]{ 0 };

					if (!hlong)
					{
						uint inv = va_arg(args, uint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						ulint inv = va_arg(args, ulint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 2)
					{
						ullint inv = va_arg(args, ullint);
						sint xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else {}

					sint xc = bot_strchk(ci, 21);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 'f':
				{
					double inv = va_arg(args, double);
					float ninv = (float)inv;
					_char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 'd':
				{
					_char ci[64]{ 0 };

					if (!hlong)
					{
						double inv = va_arg(args, double);
						sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						long double inv = va_arg(args, long double);
						sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					}
					else {}

					sint xc = bot_strchk(ci, 64);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
						at_inchr++;
					}
					break;
				}
				case 's':
				{
					c_char* str = va_arg(args, c_char*);
					_char cmp = '\0';
					sloc = 0;

					for (sloc = 0; sloc < BOT_STRLEN_MAX && at_inchr < in_siz; sloc++)
					{
						if (memcmp(&str[sloc], &cmp, sizeof(cmp)))
						{
							memcpy((void*)&inchr[at_inchr], (void*)&str[sloc], sizeof(str[sloc]));
							at_inchr++;
						}
						else
						{
							sloc = BOT_STRLEN_MAX;
						}
					}
					break;
				}
				case 'c':
				{
					sint inv_ = va_arg(args, sint);
					_char inv = (_char)inv_;

					if (at_inchr < in_siz)
					{
						memcpy((void*)&inchr[at_inchr], (void*)&inv, sizeof(inv));
						at_inchr++;
					}
					break;
				}
				case 'X':
				{
#ifdef _WIN32
					u_char inv_ = va_arg(args, u_char);
#else
					sint sinv_ = va_arg(args, sint);
					u_char inv_ = (u_char)sinv_;
#endif
					const size_t usiz = (sizeof(inv_) * 2) + 1;

					if (usiz <= in_siz)
					{
						_char ci[usiz]{ 0 };
						sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, sizeof(ci));

						for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
						{
							memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
							at_inchr++;
						}
					}
					break;
				}
				case 'v':
				{
					nsiz++;
					if (nsiz < fspecs[siz].length())
					{
						if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
						{
							_char sep[4]{ 0 };
							_char fspec[4]{ 0 };
							uint nct = 0;

							while (nsiz < fspecs[siz].length() && nct < 3)
							{
								nsiz++;

								if (nsiz < fspecs[siz].length())
								{
									switch (fspecs[siz][nsiz])
									{
									case '.':
									{
										if (nct)
										{
											nct = 3;
										}
										break;
									}
									case 'l':
									{
										hlong++;
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nct++;
										break;
									}
									case 'c':
									case 'i':
									case 's':
									case 'f':
									case 'd':
									case 'u':
									case 'X':
									{
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nsiz++;
										nct = 3;
										break;
									}
									default:
									{
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nsiz++;
										nct++;
										break;
									}
									}
								}
							}
							if (nsiz < fspecs[siz].length())
							{
								for (uint x = 0; x < sizeof(sep) && nsiz < fspecs[siz].length(); x++)
								{
									if (memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
									{
										memcpy((void*)&sep[x], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
									}
									else
									{
										nsiz = fspecs[siz].length();
									}
									nsiz++;
								}
							}

							size_t flen = strlen(fspec);

							if (flen)
							{
								flen--;
								size_t slen = strlen(sep) - 1;;

								switch (fspec[flen])
								{
								case 'c':
								{
									std::vector<_char>* inv = va_arg(args, std::vector<_char>*);

									for (uint x = 0; x < inv->size(); x++)
									{
										if (at_inchr < in_siz)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&inv->at(x), sizeof(inv->at(x)));
											at_inchr++;
										}
										if (slen)
										{
											for (sloc = 0; sloc < strlen(sep) && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&sep[sloc], sizeof(sep[sloc]));
												at_inchr++;
											}
										}
									}
									break;
								}
								case 's':
								{
									/*when specifying %v.<type><sep>. <type> = 's' we use a vector of std::string instead of a vector of c_char* */
									std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

									for (uint x = 0; x < strv->size(); x++)
									{
										for (sloc = 0; sloc < strv->at(x).length() && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&strv->at(x)[sloc], sizeof(strv->at(x)[sloc]));
											at_inchr++;
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
												at_inchr++;
											}
										}
									}
									break;
								}
								case 'f':
								{
									std::vector<float>* fvec = va_arg(args, std::vector<float>*);

									for (uint x = 0; x < fvec->size(); x++)
									{
										_char ci[64]{ 0 };
										sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
										xc = bot_strchk(ci, 64);

										for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
											at_inchr++;
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
												at_inchr++;
											}
										}
									}
									break;
								}
								case 'd':
								{
									if (!hlong)
									{
										std::vector<double>* fvec = va_arg(args, std::vector<double>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<long double>* fvec = va_arg(args, std::vector<long double>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else {}
									break;
								}
								case 'i':
								{
									if (!hlong)
									{
										std::vector<sint>* fvec = va_arg(args, std::vector<sint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<slint>* fvec = va_arg(args, std::vector<slint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 2)
									{
										std::vector<sllint>* fvec = va_arg(args, std::vector<sllint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else {}
									break;
								}
								case 'u':
								{
									if (!hlong)
									{
										std::vector<uint>* fvec = va_arg(args, std::vector<uint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<ulint>* fvec = va_arg(args, std::vector<ulint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else if (hlong == 2)
									{
										std::vector<ullint>* fvec = va_arg(args, std::vector<ullint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
													at_inchr++;
												}
											}
										}
									}
									else {}
									break;
								}
								case 'X':
								{
									std::vector<u_char>* inv = va_arg(args, std::vector<u_char>*);

									for (uint x = 0; x < inv->size(); x++)
									{
										const size_t usiz = (sizeof(inv->at(x)) * 2) + 1;

										if (usiz + at_inchr <= in_siz)
										{
											_char ci[usiz]{ 0 };
											sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv->at(x));
											xc = bot_strchk(ci, sizeof(ci));

											for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
												at_inchr++;

												if (slen)
												{
													for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
													{
														memcpy((void*)&inchr[at_inchr], (void*)&sep[y], sizeof(sep[y]));
														at_inchr++;
													}
												}
											}
										}
									}
									break;
								}
								case 'v':
								{
									break;
								}
								default:
								{
									break;
								}
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
			}
			locs[siz] += fspecs[siz].length();
		}

		va_end(args);

		if (!locs.empty())
		{
			if (locs[siz - 1] < strsiz)
			{
				while (locs[siz - 1] < strsiz && at_inchr < in_siz)
				{
					memcpy((void*)&inchr[at_inchr], (void*)&fstr[locs[siz - 1]], sizeof(fstr[locs[siz - 1]]));
					locs[siz - 1]++;
					at_inchr++;
				}
			}
		}
		if (at_inchr < in_siz)
		{
			memcpy((void*)&inchr[at_inchr], (void*)&term, sizeof(term));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(term));
		}
	}
	else
	{
		uint siz = 0;

		while (siz < in_siz && siz < strsiz)
		{
			memcpy((void*)&inchr[siz], (void*)&fstr[siz], sizeof(fstr[siz]));
			siz++;
		}
		if (siz < in_siz)
		{
			memcpy((void*)&inchr[siz], (void*)&term, sizeof(term));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(term));
		}
	}
	return ret;
}

sint bot_sprintfs(std::string* str_ = 0, bool clear_str = false, c_char* fstr = 0, ...)
{
	if (!str_ || !fstr)
	{
		return -1;
	}

	if (!str_->empty() && clear_str)
	{
		str_->clear();
	}

	uint strsiz = strlen(fstr);
	std::vector<std::string> fspecs;
	std::vector<uint> locs;
	std::string formspec;
	_char frm = '%';
	_char spec = '.';
	_char term = '\0';

	for (uint siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr[siz], (void*)&frm, 1))
		{
			formspec.push_back(fstr[siz]);
			bool mustnum = false;

			for (uint nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, 1))
				{
					if (!mustnum)
					{
						mustnum = true;
					}

					formspec.push_back(fstr[siz + nsiz]);
					nsiz++;

					switch (fstr[siz + nsiz])
					{
					case '-':
					case '+':
					case 'E':
					case 'e':
					case 'x':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case '0':
					{
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (fstr[siz + nsiz])
					{
					case 'l':
					case '-':
					case '+':
					case '0':
					case '2':
					case 'x':
					case 'e':
					case 'h':
					case 'E':
					{
						if (!mustnum)
						{
							mustnum = true;
						}
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
						break;
					}
					case 'd':
					case 'f':
					case 'u':
					case 'i':
					case 'X':
					{
						formspec.push_back(fstr[siz + nsiz]);
						fspecs.push_back(formspec);
						locs.push_back(siz);
						formspec.clear();
						siz += nsiz;
						nsiz = strsiz;
						break;
					}
					case 's':
					case 'c':
					{
						if (!mustnum)
						{
							formspec.push_back(fstr[siz + nsiz]);
							locs.push_back(siz);
							fspecs.push_back(formspec);
							formspec.clear();
							siz += nsiz;
							nsiz = strsiz;
						}
						else
						{
							return -2;
						}
						break;
					}
					case 'v':
					{
						if (!mustnum)
						{
							sint done = 0;
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							if (siz + nsiz < strsiz)
							{
								if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(spec)))
								{
									formspec.push_back(fstr[siz + nsiz]);

									while (siz + nsiz < strsiz)
									{
										nsiz++;

										if (siz + nsiz < strsiz)
										{
											formspec.push_back(fstr[siz + nsiz]);

											if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(spec)))
											{
												locs.push_back(siz);
												fspecs.push_back(formspec);
											}
										}
									}
								}
							}

							formspec.clear();
							siz += nsiz;
							nsiz = strsiz;
						}
						else
						{
							return -2;
						}
						break;
					}
					default:
					{
						return -3;
						break;
					}
					}
				}
			}
		}
	}

	_char lenchr = 'l';

	if (!fspecs.empty())
	{
		uint siz = 0;
		va_list args;
		va_start(args, fstr);

		for (siz = 0; siz < fspecs.size(); siz++)
		{
			uint hlong = 0;
			uint sloc = 0;

			if (siz)
			{
				sloc = locs[siz - 1];
			}

			while (sloc < locs[siz])
			{
				str_->push_back(fstr[sloc]);
				sloc++;
			}

			if (fspecs[siz].length() > 1)
			{
				sint isiz = 0;
				uint nsiz = 1;

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
				{
					_char fchr[3]{ 0 };
					nsiz++;
					uint fsiz = 0;

					while (fsiz < 3 && nsiz < fspecs[siz].length())
					{
						switch (fspecs[siz][nsiz])
						{
						case '+':
						case '-':
						case 'E':
						case 'e':
						case 'h':
						case 'x':
						{
							if (fsiz)
							{
								va_end(args);
								str_->clear();
								c_char* msg = "";
								sint op = bot_str_err(-5, msg);
								return -5;
							}
							nsiz++;
							break;
						}
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case '0':
						{
							memcpy((void*)&fchr[fsiz], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							memcpy((void*)&fchr[fsiz], (void*)&term, sizeof(term));
							break;
						}
						}

						if (fsiz == 3)
						{
							memcpy((void*)&fchr[fsiz - 1], (void*)&term, sizeof(term));
						}
						else
						{
							if (!memcmp((void*)&fchr[fsiz], (void*)&term, sizeof(term)))
							{
								fsiz = 3;
							}
						}
					}
					if (!memcmp((void*)&fchr[2], (void*)&term, sizeof(term)) || !memcmp((void*)&fchr[1], (void*)&term, sizeof(term)) || !memcmp((void*)&fchr[0], (void*)&term, sizeof(term)))
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (!memcmp((void*)&fspecs[siz][nsiz], (void*)&lenchr, sizeof(lenchr)))
				{
					hlong++;
					nsiz++;
				}

				_char zchar = '0';
				_char zweichar = '2';

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&zchar, sizeof(zchar)) && nsiz < fspecs[siz].length())
				{
					if (!memcmp((void*)&fspecs[siz][nsiz + 1], (void*)&zchar, sizeof(zweichar)))
					{
						nsiz += 2;
					}
				}

				switch (fspecs[siz][nsiz])
				{
				case 'i':
				{
					_char ci[21]{ 0 };
					sint xc = -1;

					if (!hlong)
					{
						sint inv = va_arg(args, sint);
						xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						slint inv = va_arg(args, slint);
						xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 2)
					{
						sllint inv = va_arg(args, sllint);
						xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else {}

					xc = bot_strchk(ci, 21);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
					break;
				}
				case 'u':
				{
					sint xc = -1;
					_char ci[21]{ 0 };

					if (!hlong)
					{
						uint inv = va_arg(args, uint);
						xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 1)
					{
						ulint inv = va_arg(args, ulint);
						xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else if (hlong == 2)
					{
						ullint inv = va_arg(args, ullint);
						xc = snprintf(ci, 21, fspecs[siz].c_str(), inv);
					}
					else {}

					xc = bot_strchk(ci, 21);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
					break;
				}
				case 'f':
				{
					double inv = va_arg(args, double);
					float ninv = (float)inv;
					_char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
					break;
				}
				case 'd':
				{
					double inv = va_arg(args, double);
					_char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
					break;
				}
				case 's':
				{
					c_char* str = va_arg(args, c_char*);
					_char cmp = '\0';
					sloc = 0;

					for (sloc = 0; (sloc + str_->length()) < (uint)BOT_STRLEN_MAX; sloc++)
					{
						if (memcmp(&str[sloc], &cmp, 1))
						{
							str_->push_back(str[sloc]);
						}
						else
						{
							sloc = BOT_STRLEN_MAX;
						}
					}
					break;
				}
				case 'c':
				{
					sint inv_ = va_arg(args, sint);
					_char inv = (_char)inv_;
					str_->push_back(inv);
					break;
				}
				case 'X':
				{
#ifdef _WIN32
					u_char inv_ = va_arg(args, u_char);
#else
					sint sinv_ = va_arg(args, sint);
					u_char inv_ = (u_char)sinv_;
#endif
					const size_t usiz = (sizeof(inv_) * 2) + 1;

					if ((usiz + str_->length()) <= (uint)BOT_STRLEN_MAX)
					{
						_char ci[usiz]{ 0 };
						sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, sizeof(ci));
						str_->append(ci);
					}
					break;
				}
				case 'v':
				{
					nsiz++;
					if (nsiz < fspecs[siz].length())
					{
						if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
						{
							_char sep[4]{ 0 };
							_char fspec[4]{ 0 };
							uint nct = 0;

							while (nsiz < fspecs[siz].length() && nct < 3)
							{
								nsiz++;

								if (nsiz < fspecs[siz].length())
								{
									switch (fspecs[siz][nsiz])
									{
									case '.':
									{
										if (nct)
										{
											nct = 3;
										}
										break;
									}
									case 'l':
									{
										hlong++;
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nct++;
										break;
									}
									case 'c':
									case 'i':
									case 's':
									case 'f':
									case 'd':
									case 'u':
									case 'X':
									{
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nsiz++;
										nct = 3;
										break;
									}
									default:
									{
										memcpy((void*)&fspec[nct], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
										nsiz++;
										nct++;
										break;
									}
									}
								}
							}
							if (nsiz < fspecs[siz].length())
							{
								for (uint x = 0; x < sizeof(sep) && nsiz < fspecs[siz].length(); x++)
								{
									if (memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
									{
										memcpy((void*)&sep[x], (void*)&fspecs[siz][nsiz], sizeof(fspecs[siz][nsiz]));
									}
									else
									{
										nsiz = fspecs[siz].length();
									}
									nsiz++;
								}
							}

							size_t flen = strlen(fspec);

							if (flen)
							{
								flen--;
								size_t slen = strlen(sep) - 1;;

								switch (fspec[flen])
								{
								case 'c':
								{
									std::vector<_char>* inv = va_arg(args, std::vector<_char>*);

									for (uint x = 0; x < inv->size() && str_->length() < (uint)BOT_STRLEN_MAX; x++)
									{
										str_->push_back(inv->at(x));

										if (slen)
										{
											for (sloc = 0; sloc < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(sep[sloc]);
											}
										}
									}
									break;
								}
								case 's':
								{
									/*when specifying %v.<type><sep>. <type> = 's' we use a vector of std::string instead of a vector of c_char* */
									std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

									for (uint x = 0; x < strv->size() && str_->length() < (uint)BOT_STRLEN_MAX; x++)
									{
										for (sloc = 0; sloc < strv->at(x).length(); sloc++)
										{
											str_->push_back(strv->at(x)[sloc]);
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
											{
												str_->push_back(sep[y]);
											}
										}
									}
									break;
								}
								case 'f':
								{
									std::vector<float>* fvec = va_arg(args, std::vector<float>*);

									for (uint x = 0; x < fvec->size(); x++)
									{
										_char ci[64]{ 0 };
										sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
										xc = bot_strchk(ci, 64);

										for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
										{
											str_->push_back(ci[sloc]);
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
											{
												str_->push_back(sep[y]);
											}
										}
									}
									break;
								}
								case 'd':
								{
									if (!hlong)
									{
										std::vector<double>* fvec = va_arg(args, std::vector<double>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<long double>* fvec = va_arg(args, std::vector<long double>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else {}
									break;
								}
								case 'i':
								{
									if (!hlong)
									{
										std::vector<sint>* fvec = va_arg(args, std::vector<sint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<slint>* fvec = va_arg(args, std::vector<slint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else if (hlong == 2)
									{
										std::vector<sllint>* fvec = va_arg(args, std::vector<sllint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else {}
									break;
								}
								case 'u':
								{
									if (!hlong)
									{
										std::vector<uint>* fvec = va_arg(args, std::vector<uint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else if (hlong == 1)
									{
										std::vector<ulint>* fvec = va_arg(args, std::vector<ulint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else if (hlong == 2)
									{
										std::vector<ullint>* fvec = va_arg(args, std::vector<ullint>*);

										for (uint x = 0; x < fvec->size(); x++)
										{
											_char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX; sloc++)
											{
												str_->push_back(ci[sloc]);
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
												{
													str_->push_back(sep[y]);
												}
											}
										}
									}
									else {}
									break;
								}
								case 'X':
								{
									std::vector<u_char>* inv = va_arg(args, std::vector<u_char>*);

									for (uint x = 0; x < inv->size(); x++)
									{
										const size_t usiz = (sizeof(inv->at(x)) * 2) + 1;

										if (usiz + str_->length() < (uint)BOT_STRLEN_MAX)
										{
											_char ci[usiz]{ 0 };
											sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv->at(x));
											xc = bot_strchk(ci, sizeof(ci));

											for (sloc = 0; ((sint)sloc < xc && str_->length() < (uint)BOT_STRLEN_MAX); sloc++)
											{
												str_->push_back(ci[sloc]);

												if (slen)
												{
													for (uint y = 0; y < strlen(sep) && str_->length() < (uint)BOT_STRLEN_MAX; y++)
													{
														str_->push_back(sep[y]);
													}
												}
											}
										}
									}
									break;
								}
								case 'v':
								{
									break;
								}
								default:
								{
									break;
								}
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
			}
			locs[siz] += fspecs[siz].length();
		}

		va_end(args);

		if (!locs.empty())
		{
			if (locs[siz - 1] < strsiz)
			{
				while (locs[siz - 1] < strsiz)
				{
					str_->push_back(fstr[locs[siz - 1]]);
					locs[siz - 1]++;
				}
			}
		}
		return 0;
	}
	else
	{
		if (strsiz < (uint)BOT_STRLEN_MAX)
		{
			str_->append(fstr);
		}
		return 0;
	}
	return -1;
}

errno_t bot_itoa(sint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%i", i); }
errno_t bot_itoa(slint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%li", i); }
errno_t bot_itoa(sllint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lli", i); }
errno_t bot_itoa(uint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%u", i); }
errno_t bot_itoa(ulint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lu", i); }
errno_t bot_itoa(ullint i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%llu", i); }
errno_t bot_dtoa(double i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%d", i); }
errno_t bot_dtoa(long double i, _char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%ld", i); }

errno_t bot_itoa(sint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%i", i); }
errno_t bot_itoa(slint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%li", i); }
errno_t bot_itoa(sllint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lli", i); }
errno_t bot_itoa(uint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%u", i); }
errno_t bot_itoa(ulint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lu", i); }
errno_t bot_itoa(ullint i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%llu", i); }
errno_t bot_dtoa(double i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%d", i); }
errno_t bot_dtoa(long double i, c_char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%ld", i); }

errno_t bot_itoa(sint i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%i", i); }
errno_t bot_itoa(slint i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%li", i); }
errno_t bot_itoa(sllint i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%lli", i); }
errno_t bot_itoa(uint i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%u", i); }
errno_t bot_itoa(ulint i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%lu", i); }
errno_t bot_itoa(ullint i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%llu", i); }
errno_t bot_dtoa(double i, std::string* str = 0, sint radix = 10) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%d", i); }
errno_t bot_dtoa(long double i, std::string* str = 0, size_t in_siz = 0, sint radix = 10) { if (!str || !in_siz) { return -1; } return (errno_t)bot_sprintfs(str, true, "%ld", i); }

enum bot_con_val
{
	BOT_F_CON = 0,
	BOT_DB_CON = 1,
	BOT_DIR_CON = 2,
	BOT_MAX_CON = 3
};

enum bot_rtv_vals
{
	BOT_RTV_SINT = 0,
	BOT_RTV_UINT = 1,
	BOT_RTV_CHAR = 2,
	BOT_RTV_UCHAR = 3,
	BOT_RTV_SINTP = 4,
	BOT_RTV_UINTP = 5,
	BOT_RTV_CHARP = 6,
	BOT_RTV_UCHARP = 7,
	BOT_RTV_CCHAR = 8,
	BOT_RTV_STR = 9,
	BOT_RTV_REAL = 10,
	BOT_RTV_MICS = 11,
	BOT_RTV_MACS = 12,
	BOT_RTV_VSINT = 13,
	BOT_RTV_VUINT = 14,
	BOT_RTV_VCHAR = 15,
	BOT_RTV_VUCHAR = 16,
	BOT_RTV_VCCHAR = 17,
	BOT_RTV_VSTR = 18,
	BOT_RTV_VREAL = 19,
	BOT_RTV_VMICS = 20,
	BOT_RTV_VMACS = 21,
	BOT_RTV_MAX = 22
};

typedef struct bot_carr_2
{
	_char carr[2] = { 0 };
	size_t siz = 2;
}carr_2;

typedef struct bot_carr_3
{
	_char carr[3] = { 0 };
	size_t siz = 3;
}carr_3;

typedef struct bot_carr_4
{
	_char carr[4] = { 0 };
	size_t siz = 4;
}carr_4;

typedef struct bot_carr_8
{
	_char carr[8] = { 0 };
	size_t siz = 8;
}carr_8;

typedef struct bot_carr_12
{
	_char carr[12] = { 0 };
	size_t siz = 12;
}carr_12;

typedef struct bot_carr_16
{
	_char carr[16] = { 0 };
	size_t siz = 16;
}carr_16;

typedef struct bot_carr_21
{
	_char carr[21] = { 0 };
	size_t siz = 21;
}carr_21;

typedef struct bot_carr_24
{
	_char carr[24] = { 0 };
	size_t siz = 24;
}carr_24;

typedef struct bot_carr_32
{
	_char carr[32] = { 0 };
	size_t siz = 32;
}carr_32;

typedef struct bot_carr_48
{
	_char carr[48] = { 0 };
	size_t siz = 48;
}carr_48;

typedef struct bot_carr_64
{
	_char carr[64] = { 0 };
	size_t siz = 64;
}carr_64;

typedef struct bot_carr_96
{
	_char carr[96] = { 0 };
	size_t siz = 96;
}carr_96;

typedef struct bot_carr_128
{
	_char carr[128] = { 0 };
	size_t siz = 128;
}carr_128;

typedef struct bot_carr_192
{
	_char carr[192] = { 0 };
	size_t siz = 192;
}carr_192;

typedef struct bot_carr_256
{
	_char carr[256] = { 0 };
	size_t siz = 256;
}carr_256;

typedef struct bot_carr_384
{
	_char carr[384] = { 0 };
	size_t siz = 384;
}carr_384;

typedef struct bot_carr_512
{
	_char carr[512] = { 0 };
	size_t siz = 512;
}carr_512;

typedef struct bot_carr_768
{
	_char carr[768] = { 0 };
	size_t siz = 768;
}carr_768;

typedef struct bot_carr_1024
{
	_char carr[1024] = { 0 };
	size_t siz = 1024;
}carr_1024;

typedef struct bot_carr_2048
{
	_char carr[2048] = { 0 };
	size_t siz = 2048;
}carr_2048;

typedef struct bot_carr_4096
{
	_char carr[4096] = { 0 };
	size_t siz = 4096;
}carr_4096;

typedef struct bot_carr_8192
{
	_char carr[8192] = { 0 };
	size_t siz = 8192;
}carr_8192;

typedef struct bot_carr_16384
{
	_char carr[16384] = { 0 };
	size_t siz = 16384;
}carr_16384;

typedef struct bot_carr_32768
{
	_char carr[32768] = { 0 };
	size_t siz = 32768;
}carr_32768;

typedef struct bot_ucar_2
{
	u_char carr[2] = { 0 };
	size_t siz = 2;
}ucar_2;

typedef struct bot_ucar_4
{
	u_char carr[4] = { 0 };
	size_t siz = 4;
}ucar_4;

typedef struct bot_ucar_8
{
	u_char carr[8] = { 0 };
	size_t siz = 8;
}ucar_8;

typedef struct bot_ucar_16
{
	u_char carr[16] = { 0 };
	size_t siz = 16;
}ucar_16;

typedef struct bot_ucar_32
{
	u_char carr[32] = { 0 };
	size_t siz = 32;
}ucar_32;

typedef struct bot_ucar_64
{
	u_char carr[64] = { 0 };
	size_t siz = 64;
}ucar_64;

typedef struct bot_ucar_128
{
	u_char carr[128] = { 0 };
	size_t siz = 128;
}ucar_128;

typedef struct bot_ucar_256
{
	u_char carr[256] = { 0 };
	size_t siz = 256;
}ucar_256;

typedef struct bot_ucar_512
{
	u_char carr[512] = { 0 };
	size_t siz = 512;
}ucar_512;

typedef struct bot_ucar_1024
{
	u_char carr[1024] = { 0 };
	size_t siz = 1024;
}ucar_1024;

typedef struct bot_ucar_2048
{
	u_char carr[2048] = { 0 };
	size_t siz = 2048;
}ucar_2048;

typedef struct bot_ucar_4096
{
	u_char carr[4096] = { 0 };
	size_t siz = 4096;
}ucar_4096;

typedef struct bot_ucar_8192
{
	u_char carr[8192] = { 0 };
	size_t siz = 8192;
}ucar_8192;

typedef struct bot_ucar_16384
{
	u_char carr[16384] = { 0 };
	size_t siz = 16384;
}ucar_16384;

typedef struct bot_ucar_32768
{
	u_char carr[32768] = { 0 };
	size_t siz = 32768;
}ucar_32768;

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
	MTX_MAX = 17
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

	_mtx(pthread_mutexattr_t n_mtx_attr = 0) { mtx_attr = n_mtx_attr; sint px = pthread_mutexattr_init(&mtx_attr); if (!px) { px = pthread_mutex_init(&mtx, &mtx_attr); } else { std::cout << "pthread_mutexattr_init err:" << px << std::endl; } };
	~_mtx() { DESTROY(); };

#if (BOT_FILE_TLOCK == 1)
	sint Lock() { return pthread_mutex_trylock(&mtx); }
#else
	sint Lock() { return pthread_mutex_lock(&mtx); }
#endif

	sint Unlock() { return pthread_mutex_unlock(&mtx); }
	void Renew(pthread_mutexattr_t n_mtx_attr = 0) { DESTROY(); mtx_attr = n_mtx_attr; sint px = pthread_mutexattr_init(&mtx_attr); if (!px) { px = pthread_mutex_init(&mtx, &mtx_attr); } }
	pthread_mutexattr_t mtx_attr;
	pthread_mutex_t mtx;

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

	HELD_MTX(sint nw_mtx = -1, sint nlid = -1, bool nlocked = false) { w_mtx = nw_mtx; lid = nlid; locked = nlocked; };

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
	};

private:

};

class lok_defr
{

public:

	std::vector<lok_req> reqs;
	std::vector<std::vector<HELD_MTX>> held;
	std::vector<sint> held_ids;
	std::vector <std::chrono::steady_clock::time_point> held_t;
	std::vector<sint> held_p;

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

typedef struct bot_fld
{
	sllint fid;
	sllint ord;
	sllint bto;
	bool is_home;
	std::string fld;

	void Clear() { bto = ord = fid = -1; fld.clear(); }
	void Renew(bot_fld* nf = 0)
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

	bot_fld(c_char* nnm = "", sllint nfid = -1, bool nis_home = false, sllint nbto = -1, sllint nord = -1) { is_home = nis_home; bto = nbto; fid = nfid; ord = nord; fld.append(nnm); };

}BOT_FLD;

typedef struct bot_drv
{
	sllint did;
	bool is_v;
	std::string drv;
	std::vector<bot_fld> flds;

	void Clear() { did = 0; is_v = false; drv.clear(); flds.clear(); }
	void Renew(bot_drv* nd = 0)
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

	bot_drv(c_char* ndrv = "", sllint nid = 0, bool nis_v = false) { did = nid; is_v = nis_v; drv.append(ndrv); flds.clear(); };

}BOT_DRV;

typedef struct bot_dir
{

	std::string bot_home_path;
	std::vector<BOT_DRV> drvs;

	void Clear() { drvs.clear(); bot_home_path.clear(); }
	void Renew(bot_dir* nd = 0)
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

		if ( slen < 3 || slen > 254)
		{
			return -1;
		}

		bool has_dmk = true;
		bool has_drmk = true;
		_char dmk = '\\';
		_char drmk = ':';

		if (memcmp((void*)&nd[slen - 1], (void*)&dmk, sizeof(dmk)))
		{
			if (memcmp((void*)&nd[slen - 1], (void*)&drmk, sizeof(drmk)))
			{
				has_drmk = false;
			}
			has_dmk = false;
		}
		else
		{
			if (memcmp((void*)&nd[slen - 2], (void*)&drmk, sizeof(drmk)))
			{
				has_drmk = false;
			}
		}

		carr_256 dcar;
		
		if (!has_drmk)
		{
			if (!has_dmk)
			{
				sint xc = bot_sprintf(dcar.carr, dcar.siz, "%s%c%c", nd, drmk, dmk);
			}
			else
			{
				std::string nstr;
				nstr.append(nd);
				sint xc = bot_sprintf(dcar.carr, dcar.siz, "%s%c%c", nstr.substr(0, slen-1).c_str(), drmk, dmk);
			}
		}
		else
		{
			if (!has_dmk)
			{
				sint xc = bot_sprintf(dcar.carr, dcar.siz, "%s%c", nd, dmk);
			}
			else
			{
				sint xc = bot_sprintf(dcar.carr, dcar.siz, "%s", nd);
			}
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

	bot_dir(c_char* ndrv = 0)
	{
		bot_home_path.clear();
		drvs.clear();

		if (ndrv)
		{
			sint xc = BOTAddDrive(ndrv);
			//BOT_DRV nd("c:\\", drvs.size()); drvs.push_back(nd);
		}
	};

}BOT_DIR;

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
		if (col < 0 || !val )
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
	}

	bot_tbl(c_char* nname = "") { name.append(nname); };

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
	};
	
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
	std::vector<std::string> att;
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
		att.swap(val_->att);
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

	DB_CONN(c_char* nname = "", sint nmlid = -1, sint nomode = -1, sint nfid = -1) { exists = -1; mlid = nmlid; lid = nfid; in_use = o_com = persist = close_me = false; omode = nomode; size_t siz = strlen(nname); if (siz && siz < BOT_STRLEN_MAX) { name.append(nname); } t = std::chrono::steady_clock::now(); };

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

#ifdef _WIN32
	struct _stat filestats;
#else
	struct stat filestats;
#endif

	void ClearStats() { filestats.st_atime = 0; filestats.st_ctime = 0; filestats.st_dev = 0; filestats.st_ino = 0; filestats.st_mode = 0; filestats.st_mtime = 0; filestats.st_nlink = 0; filestats.st_rdev = 0; filestats.st_size = 0; filestats.st_uid = 0; }
	void Clear() { ClearStats(); connected = false; file_ele = omode = fcon = c_by = lid = exists = -1; if (!name.empty()) { name.clear(); } if (!tables.empty()) { tables.clear(); } if (!columns.empty()) { columns.clear(); } }
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
		filestats = val_->filestats;
	}

	BOT_DB(c_char* nstr = "", sint ntype = -1, sint nomode = -1)
	{
		connected = false;
		omode = nomode;
		file_ele = fcon = c_by = lid = -1;
		type = ntype; uint len = strlen(nstr);

		if (strlen(nstr))
		{
			std::string str;
			str.append("");
			str.append(nstr);
			str.append(".db");
#ifdef _WIN32
			exists = _stat(str.c_str(), &filestats);
#else
			exists = (sint)stat(str.c_str(), &filestats);
#endif
		}

		if (len && len < 128) { name.append(nstr); }
	};

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

#ifdef _WIN32
	struct _stat filestats;
#else
	struct stat filestats;
#endif

	void ClearStats() { filestats.st_atime = 0; filestats.st_ctime = 0; filestats.st_dev = 0; filestats.st_ino = 0; filestats.st_mode = 0; filestats.st_mtime = 0; filestats.st_nlink = 0; filestats.st_rdev = 0; filestats.st_size = 0; filestats.st_uid = 0; }
	void Clear() { ClearStats(); connected = false; file_ele = omode = fcon = c_by = lid = exists = -1; if (!name.empty()) { name.clear(); } tsiz = 0; csiz = 0; }
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
		filestats = val_->filestats;
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
		filestats = val_->filestats;
	}

	BOT_DB_M(c_char* nstr = "", sint ntype = -1, sint nomode = -1, sint nlid = -1, size_t ntsiz = 0, size_t ncsiz = 0, sint nexist = -1, sint nc_by = -1)
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

		if (strlen(nstr))
		{
			std::string str;
			str.append("");
			str.append(nstr);
			str.append(".db");
#ifdef _WIN32
			exists = _stat(str.c_str(), &filestats);
#else
			exists = stat(str.c_str(), &filestats);
#endif
		}

		c_by = nc_by;
		omode = nomode;
	};

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

	BOT_COMMIT() { opt = -1; };

private:
};


enum c_mems
{
	BOT_C_LQ = 0,
	BOT_C_NAMESET = 1,
	BOT_C_LOGGED_IN = 2,
	BOT_C_CHANGE_N = 3,
	BOT_C_U_PRIV = 4,
	BOT_C_U_LOGIN = 5,
	BOT_C_T_LOGINS = 6,
	BOT_C_F_LOGINS = 7,
	BOT_C_PRIV = 8,
	BOT_C_ID = 9,
	BOT_C_LOGIN_NAME = 10,
	BOT_C_NAME = 11,
	BOT_C_L_LOGIN = 12,
	BOT_C_L_DATE = 13,
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

	BOT_CLIENT(c_char* nstr = "") {nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); size_t siz = strlen(nstr); if (siz < 128) { name.append(nstr); if (siz) { nameset = true; } } };

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
	};

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

	BOTCOMMAND(c_char* ncmd = "", sint ncmd_id = -1) { id = -1; cmd_id = ncmd_id; priv = 0; cmd.append(ncmd); };

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

	BOT_LOGDET(c_char* titl = "", c_char* dat = "", sint ntype = -1, sint nc_by = -1) { file_ele = type = -1; started = false; if (ntype > -1) { type = ntype; } if (strlen(titl) < 256) { logtitle.append(titl); } if (strlen(dat) < 64) { startdate.append(dat); } c_by = nc_by; };

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

	BOT_LOGDET_M(c_char* titl = "", c_char* dat = "", sint ntype = -1, sint lid = -1, bool nstrt = false, sint nc_by = -1) { file_ele = type = -1; started = nstrt; if (ntype > -1) { type = ntype; } if (strlen(titl) < 256) { logtitle.append(titl); } if (strlen(dat) < 64) { startdate.append(dat); } lsiz = 0; c_by = nc_by; };

private:

};

typedef struct hist_p
{
	u_char sym;
	uint ct;

	hist_p(u_char* nsym = 0, uint nct = 0) { sym = BOT_BOUND_UCHR; ct = nct; if (nsym) { memcpy(&sym, &nsym[0], 1); } };

}HIST_P;

typedef struct hist_f
{
	u_char sym;
	uint ct;

	hist_f(u_char* nsym = 0, uint nct = 0) { sym = BOT_BOUND_UCHR; ct = nct; if (nsym) { memcpy(&sym, &nsym[0], 1); } };

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
	
	
	MICSYM(u_char* nsym = 0, sint nencoding = -1, std::vector<std::vector<u_char>>* ncto_ = 0, std::vector<HIST_P>* hp = 0, std::vector<HIST_F>* hf = 0) { ud_id = ud_history_following = ud_history_preceeding = ud_last_maintained = ud_last_modified = ud_last_maintained_ns = ud_last_modified_ns = false; last_maintained = last_modified = last_maintained_ns = last_modified_ns = id = loc = -1; constituent_to.clear(); encodings.clear(); history_following.clear(); history_preceeding.clear(); sym = BOT_BOUND_UCHR; if (nsym) { memcpy(&sym, &nsym[0], 1); } if (nencoding > -1) { AddEnc(nencoding, ncto_, hp, hf); } };

	private:

};

typedef struct hist_pv
{
	std::vector<MICSYM> cons;
	uint ct;

	hist_pv(std::vector<MICSYM>* nsym = 0, uint nct = 0) { ct = nct; if (nsym) { if (!ct) { ct++; } for (size_t siz = 0; siz < nsym->size(); siz++) { cons.push_back(nsym->at(siz)); } } };

}HIST_PV;

typedef struct hist_fv
{
	std::vector<MICSYM> cons;
	uint ct;

	hist_fv(std::vector<MICSYM>* nsym = 0, uint nct = 0) { ct = nct; if (nsym) { if (!ct) { ct++; } for (size_t siz = 0; siz < nsym->size(); siz++) { cons.push_back(nsym->at(siz)); } } };

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

	MACSYM(sint nua = -1, u_char ncons[] = 0, sint nencoding = -1, std::vector<HIST_PV>* nhp_v = 0, std::vector<HIST_FV>* nhf_v = 0) { ud_id = ud_usages = ud_cons = ud_pair_sym = ud_history_following = ud_history_preceeding = ud_last_maintained = ud_last_modified = ud_last_maintained_ns = ud_last_modified_ns = ud_used = ud_alters = false; used_as = nua; id = -1; if (ncons) { RenderCons(ncons, nencoding); } if (nua > -1) { AddUse(nua, 1, nhp_v, nhf_v); } };

private:

};

class bot_fstate
{
public:
	ullint e_loc;
	ullint oa_loc;
	ullint ia_loc;
	sint exists;
	ullint fbyte;
	std::vector<MACSYM> seps;

	std::vector<ullint> compv;
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
		fbyte = (ullint)'\0';
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
				if (!memcmp((void*)&nst->compv[x], (void*)&compv[y], sizeof(compv[y])))
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

		for (uint x = 0; x < compv.size(); x++)
		{
			sint xc = ReorderVs((sint)x);
		}
	}
	void RenewLocs( ullint ne_loc = 0, ullint noa_loc = 0, ullint nia_loc = 0)
	{
		e_loc = ne_loc;
		oa_loc = noa_loc;
		ia_loc = nia_loc;
	}

#ifdef _WIN32
	void RenewStats(struct _stat* nstat = 0)
	{
		ClearStats();

		if (!nstat)
		{
			return;
		}

		memcpy((void*)&filestats.st_atime, (void*)&nstat->st_atime, sizeof(nstat->st_atime));
		memcpy((void*)&filestats.st_ctime, (void*)&nstat->st_ctime, sizeof(nstat->st_ctime));
		memcpy((void*)&filestats.st_dev, (void*)&nstat->st_dev, sizeof(nstat->st_dev));
		memcpy((void*)&filestats.st_ino, (void*)&nstat->st_ino, sizeof(nstat->st_ino));
		memcpy((void*)&filestats.st_mode, (void*)&nstat->st_mode, sizeof(nstat->st_mode));
		memcpy((void*)&filestats.st_mtime, (void*)&nstat->st_mtime, sizeof(nstat->st_mtime));
		memcpy((void*)&filestats.st_nlink, (void*)&nstat->st_nlink, sizeof(nstat->st_nlink));
		memcpy((void*)&filestats.st_rdev, (void*)&nstat->st_rdev, sizeof(nstat->st_rdev));
		memcpy((void*)&filestats.st_size, (void*)&nstat->st_size, sizeof(nstat->st_size));
		memcpy((void*)&filestats.st_uid, (void*)&nstat->st_uid, sizeof(nstat->st_uid));
	}
#else
	void RenewStats(struct stat* nstat = 0)
	{
		ClearStats();

		if (!nstat)
		{
			return;
		}

		memcpy((void*)&filestats.st_atime, (void*)&nstat->st_atime, sizeof(nstat->st_atime));
		memcpy((void*)&filestats.st_ctime, (void*)&nstat->st_ctime, sizeof(nstat->st_ctime));
		memcpy((void*)&filestats.st_dev, (void*)&nstat->st_dev, sizeof(nstat->st_dev));
		memcpy((void*)&filestats.st_ino, (void*)&nstat->st_ino, sizeof(nstat->st_ino));
		memcpy((void*)&filestats.st_mode, (void*)&nstat->st_mode, sizeof(nstat->st_mode));
		memcpy((void*)&filestats.st_mtime, (void*)&nstat->st_mtime, sizeof(nstat->st_mtime));
		memcpy((void*)&filestats.st_nlink, (void*)&nstat->st_nlink, sizeof(nstat->st_nlink));
		memcpy((void*)&filestats.st_rdev, (void*)&nstat->st_rdev, sizeof(nstat->st_rdev));
		memcpy((void*)&filestats.st_size, (void*)&nstat->st_size, sizeof(nstat->st_size));
		memcpy((void*)&filestats.st_uid, (void*)&nstat->st_uid, sizeof(nstat->st_uid));
	}
#endif
	
#ifdef _WIN32
	sint cmpstats(struct _stat* nstat = 0)
	{
		if (!nstat)
		{
			return -1;
		}
		if (memcmp((void*)&filestats.st_atime, (void*)&nstat->st_atime, sizeof(nstat->st_atime)))
		{
			return 103;
		}
		if (memcmp((void*)&filestats.st_ctime, (void*)&nstat->st_ctime, sizeof(nstat->st_ctime)))
		{
			return 104;
		}
		if (memcmp((void*)&filestats.st_dev, (void*)&nstat->st_dev, sizeof(nstat->st_dev)))
		{
			return 105;
		}
		if (memcmp((void*)&filestats.st_ino, (void*)&nstat->st_ino, sizeof(nstat->st_ino)))
		{
			return 106;
		}
		if (memcmp((void*)&filestats.st_mode, (void*)&nstat->st_mode, sizeof(nstat->st_mode)))
		{
			return 107;
		}
		if (memcmp((void*)&filestats.st_mtime, (void*)&nstat->st_mtime, sizeof(nstat->st_mtime)))
		{
			return 108;
		}
		if (memcmp((void*)&filestats.st_nlink, (void*)&nstat->st_nlink, sizeof(nstat->st_nlink)))
		{
			return 109;
		}
		if (memcmp((void*)&filestats.st_rdev, (void*)&nstat->st_rdev, sizeof(nstat->st_rdev)))
		{
			return 110;
		}
		if (memcmp((void*)&filestats.st_size, (void*)&nstat->st_size, sizeof(nstat->st_size)))
		{
			return 111;
		}
		if (memcmp((void*)&filestats.st_uid, (void*)&nstat->st_uid, sizeof(nstat->st_uid)))
		{
			return 112;
		}
		return 0;
	}
#else
	sint cmpstats(struct stat* nstat = 0)
	{
		if (!nstat)
		{
			return -1;
		}
		if (memcmp((void*)&filestats.st_atime, (void*)&nstat->st_atime, sizeof(nstat->st_atime)))
		{
			return 103;
		}
		if (memcmp((void*)&filestats.st_ctime, (void*)&nstat->st_ctime, sizeof(nstat->st_ctime)))
		{
			return 104;
		}
		if (memcmp((void*)&filestats.st_dev, (void*)&nstat->st_dev, sizeof(nstat->st_dev)))
		{
			return 105;
		}
		if (memcmp((void*)&filestats.st_ino, (void*)&nstat->st_ino, sizeof(nstat->st_ino)))
		{
			return 106;
		}
		if (memcmp((void*)&filestats.st_mode, (void*)&nstat->st_mode, sizeof(nstat->st_mode)))
		{
			return 107;
		}
		if (memcmp((void*)&filestats.st_mtime, (void*)&nstat->st_mtime, sizeof(nstat->st_mtime)))
		{
			return 108;
		}
		if (memcmp((void*)&filestats.st_nlink, (void*)&nstat->st_nlink, sizeof(nstat->st_nlink)))
		{
			return 109;
		}
		if (memcmp((void*)&filestats.st_rdev, (void*)&nstat->st_rdev, sizeof(nstat->st_rdev)))
		{
			return 110;
		}
		if (memcmp((void*)&filestats.st_size, (void*)&nstat->st_size, sizeof(nstat->st_size)))
		{
			return 111;
		}
		if (memcmp((void*)&filestats.st_uid, (void*)&nstat->st_uid, sizeof(nstat->st_uid)))
		{
			return 112;
		}
		return 0;
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

		for (uint x = 0; x < compv.size(); x++)
		{
			uint y = 0;

			while (y < est->compv.size())
			{
				if (cts[x] != est->cts[x] || 
					memcmp((void*)&compv[x], (void*)&est->compv[x], sizeof(compv[x])) || 
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

				ullint vali;
				memcpy((void*)&vali, (void*)&compv[ele], sizeof(compv[ele]));
				memcpy((void*)&compv[ele], (void*)&compv[nele], sizeof(compv[nele]));
				memcpy((void*)&compv[nele], (void*)&vali, sizeof(vali));
				vali = cts[ele];
				cts[ele] = cts[nele];
				cts[nele] = vali;
				vali = mean_loc[ele];
				mean_loc[ele] = mean_loc[nele];
				mean_loc[nele] = vali;
				vali = mean_spc[ele];
				mean_spc[ele] = mean_spc[nele];
				mean_spc[nele] = vali;
				vali = med_spc[ele];
				med_spc[ele] = med_spc[nele];
				med_spc[nele] = vali;
				vali = mean_spc_var[ele];
				mean_spc_var[ele] = mean_spc_var[nele];
				mean_spc_var[nele] = vali;
				vali = mean_lens[ele];
				mean_lens[ele] = mean_lens[nele];
				mean_lens[nele] = vali;
				vali = med_lens[ele];
				med_lens[ele] = med_lens[nele];
				med_lens[nele] = vali;
				vali = mean_lens_var[ele];
				mean_lens_var[ele] = mean_lens_var[nele];
				mean_lens_var[nele] = vali;
				vali = mean_linl[ele];
				mean_linl[ele] = mean_linl[nele];
				mean_linl[nele] = vali;
				vali = med_linl[ele];
				med_linl[ele] = med_linl[nele];
				med_linl[nele] = vali;
				vali = mean_linl_var[ele];
				mean_linl_var[ele] = mean_linl_var[nele];
				mean_linl_var[nele] = vali;
				vali = mean_linct[ele];
				mean_linct[ele] = mean_linct[nele];
				mean_linct[nele] = vali;
				vali = med_linct[ele];
				med_linct[ele] = med_linct[nele];
				med_linct[nele] = vali;
				vali = mean_linct_var[ele];
				mean_linct_var[ele] = mean_linct_var[nele];
				mean_linct_var[nele] = vali;
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

				ullint vali;
				memcpy((void*)&vali, (void*)&compv[ele], sizeof(compv[ele]));
				memcpy((void*)&compv[ele], (void*)&compv[nele], sizeof(compv[nele]));
				memcpy((void*)&compv[nele], (void*)&vali, sizeof(vali));
				vali = cts[ele];
				cts[ele] = cts[nele];
				cts[nele] = vali;
				vali = mean_loc[ele];
				mean_loc[ele] = mean_loc[nele];
				mean_loc[nele] = vali;
				vali = mean_spc[ele];
				mean_spc[ele] = mean_spc[nele];
				mean_spc[nele] = vali;
				vali = med_spc[ele];
				med_spc[ele] = med_spc[nele];
				med_spc[nele] = vali;
				vali = mean_spc_var[ele];
				mean_spc_var[ele] = mean_spc_var[nele];
				mean_spc_var[nele] = vali;
				vali = mean_lens[ele];
				mean_lens[ele] = mean_lens[nele];
				mean_lens[nele] = vali;
				vali = med_lens[ele];
				med_lens[ele] = med_lens[nele];
				med_lens[nele] = vali;
				vali = mean_lens_var[ele];
				mean_lens_var[ele] = mean_lens_var[nele];
				mean_lens_var[nele] = vali;
				vali = mean_linl[ele];
				mean_linl[ele] = mean_linl[nele];
				mean_linl[nele] = vali;
				vali = med_linl[ele];
				med_linl[ele] = med_linl[nele];
				med_linl[nele] = vali;
				vali = mean_linl_var[ele];
				mean_linl_var[ele] = mean_linl_var[nele];
				mean_linl_var[nele] = vali;
				vali = mean_linct[ele];
				mean_linct[ele] = mean_linct[nele];
				mean_linct[nele] = vali;
				vali = med_linct[ele];
				med_linct[ele] = med_linct[nele];
				med_linct[nele] = vali;
				vali = mean_linct_var[ele];
				mean_linct_var[ele] = mean_linct_var[nele];
				mean_linct_var[nele] = vali;
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
	void IncrCts(ullint* val = 0, ullint loc = 0, ullint lin = 0, ullint lloc = 0)
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
	void DecrCts(u_char* val = 0)
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

	bot_fstate(ullint ne_loc = 0, ullint noa_loc = 0, ullint nia_loc = 0)
	{
		Clear();

		e_loc = ne_loc;
		oa_loc = noa_loc;
		ia_loc = nia_loc;
	};

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
	BOT_FS_MAX = 13
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
	bot_fstate fst;
	sint lid;
	sint c_by;
	sint cm;
	sllint bto;
	ullint dsiz;
	ullint* dat;

	void Clear() { fst.Clear(); ClearDat(); bto = -1; encode = cm = lid = c_by = omode = fcon = -1; if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } }
	void Renew(BOT_FILE* nf_ = 0)
	{
		if (nf_)
		{
			Clear();

			encode = nf_->encode;
			fcon = nf_->fcon;
			size_t x = nf_->name.length();
			
			if (x && x < BOT_FILENAME_MAX)
			{
				name.append(nf_->name.c_str());
			}

			x = nf_->path.length();

			if (x && x < UINT64_MAX)
			{
				path.append(nf_->path.c_str());
			}

			x = nf_->type.length();

			if (x && x < 128)
			{
				type.append(nf_->type.c_str());
			}
			
			bto = nf_->bto;
			omode = nf_->omode;
			c_by = nf_->c_by;
			lid = nf_->lid;
			cm = nf_->cm;
			fst.Renew(&nf_->fst);
			SetDat(nf_->dat, nf_->dsiz);
		}
	}
	void Renew(c_char* nm_ = 0, c_char* nt_ = 0, c_char* np_ = 0, sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sint nencode = -1, sllint nbto = -1, bot_fstate* nstate = 0, ullint* ndat = 0, ullint ndsiz = 0)
	{
		if (!nm_ || !nt_ || !np_ || nc_by < 0 || nomode < 0)
		{
			return;
		}

		Clear();

		size_t x = strlen(nm_);

		if (x && x < BOT_FILENAME_MAX)
		{
			name.append(nm_);
		}

		x = strlen(np_);

		if (x && x < UINT64_MAX)
		{
			path.append(np_);
		}

		x = strlen(nt_);

		if (x && x < 128)
		{
			type.append(nt_);
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
	void SetDat(ullint* val_ = 0, ullint siz = 0)
	{
		if (!val_)
		{
			return;
		}

		dat = (ullint*)realloc(dat, fst.filestats.st_size + 1);

		if (dat)
		{
			dsiz = fst.filestats.st_size + 1;
			ullint term = (ullint)'\0';

			for (ullint x = 0; x < (ullint)fst.filestats.st_size; x++)
			{
				memcpy((void*)&dat[x], (void*)val_[x], sizeof(dat[x]));

				if (!memcmp((void*)&val_, (void*)&term, sizeof(term)))
				{
					x = (ullint)fst.filestats.st_size;
				}
			}
			memcpy((void*)&dat[fst.filestats.st_size], (void*)&term, sizeof(term));
		}
	}
	void AddDat(ullint* val_ = 0, ullint f = 0, ullint to = 0)
	{
		if (f >= to || !val_)
		{
			return;
		}

		ullint term = '\0';
		ullint ne = fst.e_loc;

		if (to > fst.e_loc)
		{
			ne = to;
		}

		ullint nor = fst.ia_loc;

		if (f < fst.ia_loc)
		{
			nor = f;
		}

		ullint* tmp = (ullint*)malloc((size_t)(ne - nor) + 1);

		if (tmp)
		{
			ullint fsiz = (ullint)abs((sllint)fst.ia_loc - (sllint)f);

			if (fsiz)
			{
				if (fst.ia_loc < f)
				{
					for (ullint x = 0; x < f - nor; x++)
					{
						memcpy((void*)&tmp[x], (void*)&dat[x], sizeof(tmp[x]));
					}
				}

				for (ullint x = f - nor; x < to - nor; x++)
				{
					memcpy((void*)&tmp[x], (void*)&val_[x], sizeof(tmp[x]));
				}

				if (fst.ia_loc > to)
				{
					for (ullint x = fst.ia_loc - nor; x < fst.e_loc - nor; x++)
					{
						memcpy((void*)&tmp[x], (void*)&dat[x], sizeof(tmp[x]));
					}
				}
				else if (fst.e_loc > to)
				{
					for (ullint x = to - nor; x < fst.e_loc - nor; x++)
					{
						memcpy((void*)&tmp[x], (void*)&dat[x], sizeof(tmp[x]));
					}
				}
				else {}
			}
			memcpy((void*)&tmp[ne - nor], (void*)&term, sizeof(term));
		}

		dat = (ullint*)realloc(dat, (size_t)(ne - nor) + 1);
		
		if (dat)
		{
			dsiz = (ne - nor) + 1;

			for (ullint x = 0; x < ne - nor; x++)
			{
				memcpy((void*)&dat[x], (void*)&tmp[x], sizeof(dat[x]));
			}
			memcpy((void*)&dat[ne - nor], (void*)&term, sizeof(term));
		}
		free(tmp);
	}
	void ClearDat()
	{
		if (dat)
		{
			while (dsiz > 0)
			{
				dat[dsiz - 1] = 0;
				dsiz--;
			}

			if (dsiz > 1)
			{
				dat = (ullint*)realloc(dat, 1);

				if (dat)
				{
					dsiz = 1;
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
				free(dat);
				dsiz = 0;
			}
		}
	}
	BOT_FILE(c_char* nfn = "", c_char* nft = "", c_char* nfp = "", sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sllint nbto = -1, sint nencode = -1, bot_fstate* nfst = 0, ullint* ndat = 0, ullint ndsiz = 0)
	{
		if (strlen(nfn) && strlen(nfn) < BOT_FILENAME_MAX)
		{
			name.append(nfn);
		}

		if (strlen(nft) && strlen(nft) < 128)
		{
			type.append(nft);
		}

		if (strlen(nfp) && strlen(nfp) < UINT64_MAX)
		{
			path.append(nfp);
		}

		encode = nencode;
		bto = nbto;
		cm = ncm;
		omode = nomode;
		lid = nlid;
		fcon = -1;
		c_by = nc_by;
		dsiz = 0;

		if (!nfst)
		{
			fst.Renew(nfst);
		}
		
		if (ndsiz)
		{
			if (ndsiz < BOT_FILESIZE_MAX)
			{
				ullint term = (ullint)'\0';
				dat = (ullint*)malloc((size_t)(ndsiz + 1));

				if (dat)
				{
					memcpy((void*)&dat[ndsiz], (void*)&term, sizeof(term));
					memcpy((void*)dat, (void*)ndat, (size_t)ndsiz);
				}
			}
		}
	};
	
	~BOT_FILE()
	{
		Clear();
		FreeDat();
	};
	
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
	bot_fstate fst;
	sint lid;
	sint c_by;
	sint cm;
	sllint bto;

	void Clear() { fst.ClearStats(); bto = -1; encode = cm = lid = c_by = omode = fcon = -1; if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } }
	void Renew(BOT_FILE_M* nf_ = 0)
	{
		if (nf_)
		{
			Clear();

			encode = nf_->encode;
			bto = nf_->bto;
			fcon = nf_->fcon;
			size_t x = nf_->name.length();

			if (x && x < BOT_FILENAME_MAX)
			{
				name.append(nf_->name.c_str());
			}

			x = nf_->path.length();

			if (x && x < UINT64_MAX)
			{
				path.append(nf_->path.c_str());
			}

			x = nf_->type.length();

			if (x && x < 128)
			{
				type.append(nf_->type.c_str());
			}

			omode = nf_->omode;
			c_by = nf_->c_by;
			lid = nf_->lid;
			cm = nf_->cm;
			fst.Renew(&nf_->fst);
		}
	}
	void Renew(BOT_FILE* nf_ = 0)
	{
		if (nf_)
		{
			Clear();

			encode = nf_->encode;
			bto = nf_->bto;
			fcon = nf_->fcon;
			size_t x = nf_->name.length();

			if (x && x < BOT_FILENAME_MAX)
			{
				name.append(nf_->name.c_str());
			}

			x = nf_->path.length();

			if (x && x < UINT64_MAX)
			{
				path.append(nf_->path.c_str());
			}

			x = nf_->type.length();

			if (x && x < 128)
			{
				type.append(nf_->type.c_str());
			}

			omode = nf_->omode;
			c_by = nf_->c_by;
			lid = nf_->lid;
			cm = nf_->cm;
			fst.Renew(&nf_->fst);
		}
	}
	void Renew(c_char* nm_ = 0, c_char* nt_ = 0, c_char* np_ = 0, sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sllint nbto = -1, sint nencode = -1, bot_fstate* nstate = 0)
	{
		if (!nm_ || !nt_ || !np_ || nc_by < 0 || nomode < 0)
		{
			return;
		}

		Clear();
		
		encode = nencode;
		bto = nbto;
		size_t x = strlen(nm_);

		if (x && x < BOT_FILENAME_MAX)
		{
			name.append(nm_);
		}

		x = strlen(np_);

		if (x && x < UINT64_MAX)
		{
			path.append(np_);
		}

		x = strlen(nt_);

		if (x && x < 128)
		{
			type.append(nt_);
		}

		lid = nlid;
		cm = ncm;
		omode = nomode;
		c_by = nc_by;

		if (nstate)
		{
			fst.Renew(nstate);
		}
	}

	BOT_FILE_M(c_char* nfn = "", c_char* nft = "", c_char* nfp = "", sint nomode = -1, sint ncm = -1, sint nlid = -1, sint nc_by = -1, sllint nbto = -1, sint nencode = -1, bot_fstate* nfst = 0)
	{
		if (strlen(nfn) && strlen(nfn) < BOT_FILENAME_MAX)
		{
			name.append(nfn);
		}

		if (strlen(nft) && strlen(nft) < 128)
		{
			type.append(nft);
		}

		if (strlen(nfp) && strlen(nfp) < UINT64_MAX)
		{
			path.append(nfp);
		}

		encode = nencode;
		bto = nbto;
		omode = nomode;
		cm = ncm;
		lid = nlid;
		fcon = -1;
		c_by = nc_by;

		if (nfst)
		{
			fst.Renew(nfst);
		}
	};

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
	
	BOTF_CONN() { in_use = false; flid = encode = omode = lid = -1; };

private:
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
	std::string thread_name;
	pthread_t thread;
	pthread_attr_t attr;
	sint opt;
	sint fin;
	void *(*func)(void *);
	std::chrono::steady_clock::time_point t_I;
	sint c_by;
	float min_ratv;
	std::vector<ullint> vals;

	void Clear() { min_ratv = 0.0f; t_I = std::chrono::steady_clock::now(); opt = lid = c_by = -1; fin = -10; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; vals.clear(); }
	
	void Renew(TINFO* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		func = val_->func;
		opt = val_->opt;
		c_by = val_->c_by;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(thread_name.c_str());

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

		func = nfunc;
		opt = nopt;
		c_by = nc_by;
		min_ratv = nmin_ratv;
		t_I = std::chrono::steady_clock::now();
		size_t x = strlen(ntn);
		
		if (x && x < 256)
		{
			thread_name.append(ntn);
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

	TINFO(sint nopt = -1, c_char* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f, std::vector<ullint>* nvec = 0)
	{
		Clear();

		min_ratv = nmin_ratv;
		t_I = std::chrono::steady_clock::now();
		func = nfunc;
		c_by = nc_by;
		opt = nopt;
		lid = -1;
		fin = -10;
		size_t x = strlen(ntn);
		
		if (x && x < 256)
		{
			thread_name.append(ntn);
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
	};

private:
};

class TINFO_M
{
public:

	sint lid;
	std::string thread_name;
	sllint thread;
	sllint attr;
	sint opt;
	sint fin;
	void *(*func)(void *);
	std::chrono::steady_clock::time_point t_I;
	sint c_by;
	float min_ratv;
	std::vector<ullint> vals;

	void Clear() { min_ratv = 0.0f; attr = thread = 0; t_I = std::chrono::steady_clock::now(); opt = lid = c_by = -1; fin = -10; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; vals.clear(); }
	
	void Renew(TINFO_M* val_ = 0)
	{
		Clear();

		if (!val_)
		{
			return;
		}

		lid = val_->lid;
		fin = val_->fin;
		func = val_->func;
		opt = val_->opt;
		c_by = val_->c_by;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		attr = (sllint)&val_->attr;
		thread = (sllint)&val_->thread;
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
		fin = val_->fin;
		func = val_->func;
		opt = val_->opt;
		c_by = val_->c_by;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		attr = (sllint)&val_->attr;
		thread = (sllint)&val_->thread;
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
		Clear();

		min_ratv = nmin_ratv;
		t_I = std::chrono::steady_clock::now();
		func = nfunc;
		c_by = nc_by;
		opt = nopt;
		lid = -1;
		fin = -10;
		size_t x = strlen(ntn);

		if (x && x < 256)
		{
			thread_name.append(ntn);
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
	};

private:
};

class bot_thread_counter
{

public:

	sint Incr() { if (open_thr < (sint)BOTTHREAD_MAX) { open_thr++; return open_thr; } return -1; }
	sint Decr() { if (open_thr > 0) { open_thr--; return open_thr; } return -1; }
	sint Get() { return open_thr; }
	sint SetQuit(sint val = -1) { if (val > -1) { thr_quit = val; return 0; } return -1; }
	sint GetQuit() { return thr_quit; }

	bot_thread_counter() { open_thr = (sint)BOTTHREAD_MAX; thr_quit = 0; };

private:

	sint open_thr;
	sint thr_quit;
};

class STool
{
public:

	STool(std::chrono::steady_clock::time_point* nt = 0) { SetTClr(nt); };

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
			if (sx == strlen(str_) - 1 && x < sx)
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

	VTool(std::chrono::steady_clock::time_point* nt = 0, STool* nstool = 0) { SetTClr(nt); stool = nstool; };

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
	
	sint ValInVec(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_8> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_16> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_32> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_64> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_128> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_256> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_512> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_1024> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2048> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4096> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_8> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_16> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_32> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_64> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_128> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_256> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_512> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_1024> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2048> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4096> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { c_char* val_ = reinterpret_cast<c_char*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::vector<u_char>> *vec_ = 0, std::vector<u_char>* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).size() == val->size()) { vn = vuchrcmp(&vec_->at(siz), val); if (!vn) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz).size() == val->size()) { vn = vuchrcmp(&vec_->at(siz), val); if (!vn) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector <std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, u_char val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_ = 0, u_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, const sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, const slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, const sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, const uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, const ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz],(void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, const ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; u_char val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<u_char> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { u_char* val_ = (u_char*)val->c_str(); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { u_char* val_ = (u_char*)val->c_str(); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<_char> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<void*> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32	
	sint ValInVec(std::vector<slint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<slint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<sllint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<sllint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<sllint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<uint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<uint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<uint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<ulint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<ulint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<ulint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<ullint> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<ullint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<ullint> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<float> *vec_, u_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atof(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atof(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atof(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atof(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, u_char* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(*vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, void* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%i", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%li", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lli", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%u", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%llu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[32]{ 0 }; sint siz = bot_sprintf(mid, 32, "%0.3f", *val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, c_char* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<c_char*> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, u_char* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(*vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, void* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; c_char* mid = reinterpret_cast <c_char*>(vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%i", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%li", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lli", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%u", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; _char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%llu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_ = 0, float* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; _char mid[32]{ 0 }; sint siz = bot_sprintf(mid, 32, "%0.3f", *val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, std::string* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<DB_CONN*> *vec_ = 0, DB_CONN* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str()) && vec_->at(siz)->lid > -1 && (vec_->at(siz)->omode >= val->omode && val->omode > -1)) { vn = siz; val = vec_->at(siz); siz = vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str()) && vec_->at(siz)->lid > -1 && (vec_->at(siz)->omode >= val->omode && val->omode > -1)) { vn = siz; val = vec_->at(siz); siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; val->Renew(&vec_->at(siz)); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO> *vec_, TINFO* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->w_mtx == vec_->at(siz).w_mtx) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->w_mtx == vec_->at(siz).w_mtx) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<HELD_MTX> *vec_ = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!vec_ || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).w_mtx) { vn = siz; siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).w_mtx) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<lok_req> *vec_ = 0, lok_req* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->gmtx == vec_->at(siz).gmtx && val->ele == vec_->at(siz).ele && val->is_meta == vec_->at(siz).is_meta && val->fid == vec_->at(siz).fid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->gmtx == vec_->at(siz).gmtx && val->ele == vec_->at(siz).ele && val->is_meta == vec_->at(siz).is_meta && val->fid == vec_->at(siz).fid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE*> *vec_ = 0, BOT_FILE* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<HELD_MTX*> *vec_ = 0, HELD_MTX* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOTF_CONN*> *vec_ = 0, BOTF_CONN* val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->flid == val->flid) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->flid == val->flid) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val->lid == vec_->at(siz).lid) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_STMT> *vec_ = 0, BOT_STMT* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !comp_t_struct(val, &vec_->at(siz))) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !comp_t_struct(val, &vec_->at(siz))) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FLD> *vec_ = 0, BOT_FLD* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).fid > -1 && !strcmp(val->fld.c_str(), vec_->at(siz).fld.c_str()) && val->bto == vec_->at(siz).bto && val->ord == vec_->at(siz).ord) { vn = siz; *val = vec_->at(siz); siz = vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).fid > -1 && !strcmp(val->fld.c_str(), vec_->at(siz).fld.c_str()) && val->bto == vec_->at(siz).bto && val->ord == vec_->at(siz).ord) { vn = siz; *val = vec_->at(siz); siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<DB_CONN*> *vec_ = 0, c_char* val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && !strcmp(val, vec_->at(siz)->name.c_str()) && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && !strcmp(val, vec_->at(siz)->name.c_str()) && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOTF_CONN> *vec_ = 0, sint val = -1, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).flid) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).flid) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOTF_CONN*> *vec_ = 0, sint val = -1, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && val == vec_->at(siz)->flid) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && val == vec_->at(siz)->flid) { vn = siz; siz = -1; } } siz--; } } return vn; }
	//sint ValInVec(std::vector<DB_CONN*> *vec_ = 0, sint val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->lid == val && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->lid == val && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO_M> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FLD> *vec_ = 0, c_char* val = 0, sllint bto = -1, sllint ord = -1, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).fid > -1 && !strcmp(val, vec_->at(siz).fld.c_str()) && bto == vec_->at(siz).bto && ord == vec_->at(siz).ord) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).fid > -1 && !strcmp(val, vec_->at(siz).fld.c_str()) && bto == vec_->at(siz).bto && ord == vec_->at(siz).ord) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->logtitle.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO*> *vec_ = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->thread_name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInArr(BOTF_CONN arr[] = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0) { return -1; } sint msiz = (sint)sizeof(arr); sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (msiz + e_from); } if (forw) { while (siz < msiz) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = msiz; } siz++; } } else { while (siz > -1) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInArr(DB_CONN arr[] = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!arr || !val) { return -1; } sint msiz = (sint)sizeof(arr); sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (msiz + e_from); } if (forw) { while (siz < msiz) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = msiz; } siz++; } } else { while (siz > -1) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInArr(BOTF_CONN arr[] = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0) { return -1; } sint msiz = (sint)sizeof(*arr); sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (msiz + e_from); } if (forw) { while (siz < msiz) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = msiz; } siz++; } } else { while (siz > -1) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInArr(DB_CONN arr[] = 0, c_char* val = 0, sint e_from = 0, bool forw = true) { if (!arr || !val) { return -1; } sint msiz = (sint)sizeof(*arr); sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (msiz + e_from); } if (forw) { while (siz < msiz) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = msiz; } siz++; } } else { while (siz > -1) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint UseEmptyEle(std::vector<carr_2> *vec_ = 0, _char val[2] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 2) { if (val[siz] == '\0') { siz = 2; } siz++; } if (siz == 2) { _char nc = '\0'; memcpy((void*)&val[1], (void*)&nc, sizeof(val[1])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_4> *vec_ = 0, _char val[4] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 4) { if (val[siz] == '\0') { siz = 4; } siz++; } if (siz == 4) { _char nc = '\0'; memcpy((void*)&val[3], (void*)&nc, sizeof(val[3])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_8> *vec_ = 0, _char val[8] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 8) { if (val[siz] == '\0') { siz = 8; } siz++; } if (siz == 8) { _char nc = '\0'; memcpy((void*)&val[7], (void*)&nc, sizeof(val[7])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_16> *vec_ = 0, _char val[16] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 16) { if (val[siz] == '\0') { siz = 16; } siz++; } if (siz == 16) { _char nc = '\0'; memcpy((void*)&val[15], (void*)&nc, sizeof(val[15])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_32> *vec_ = 0, _char val[32] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 32) { if (val[siz] == '\0') { siz = 32; } siz++; } if (siz == 32) { _char nc = '\0'; memcpy((void*)&val[31], (void*)&nc, sizeof(val[31])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_64> *vec_ = 0, _char val[64] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 64) { if (val[siz] == '\0') { siz = 64; } siz++; } if (siz == 64) { _char nc = '\0'; memcpy((void*)&val[63], (void*)&nc, sizeof(val[63])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_128> *vec_ = 0, _char val[128] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 128) { if (val[siz] == '\0') { siz = 128; } siz++; } if (siz == 128) { _char nc = '\0'; memcpy((void*)&val[127], (void*)&nc, sizeof(val[127])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_256> *vec_ = 0, _char val[256] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 256) { if (val[siz] == '\0') { siz = 256; } siz++; } if (siz == 256) { _char nc = '\0'; memcpy((void*)&val[255], (void*)&nc, sizeof(val[255])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_512> *vec_ = 0, _char val[512] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 512) { if (val[siz] == '\0') { siz = 512; } siz++; } if (siz == 512) { _char nc = '\0'; memcpy((void*)&val[511], (void*)&nc, sizeof(val[511])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 1024) { if (val[siz] == '\0') { siz = 1024; } siz++; } if (siz == 1024) { _char nc = '\0'; memcpy((void*)&val[1023], (void*)&nc, sizeof(val[1023])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 2048) { if (val[siz] == '\0') { siz = 2048; } siz++; } if (siz == 2048) { _char nc = '\0'; memcpy((void*)&val[2047], (void*)&nc, sizeof(val[2047])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 4096) { if (val[siz] == '\0') { siz = 4096; } siz++; } if (siz == 4096) { _char nc = '\0'; memcpy((void*)&val[4095], (void*)&nc, sizeof(val[4095])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::vector<u_char>> *vec_ = 0, std::vector<u_char>* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { for (size_t nsiz = 0; nsiz < val->size(); nsiz++) { vec_->at(siz).push_back(val->at(nsiz)); } vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == vtclr) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<u_char> *vec_ = 0, u_char* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<u_char> *vec_, u_char val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { memcpy((void*)&vec_->at(siz), (void*)&val, sizeof(vec_->at(siz))); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<void*> *vec_ = 0, void* val = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<sint> *vec_, sint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<slint> *vec_, slint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT32_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<sllint> *vec_, sllint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT64_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<uint> *vec_, uint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<ulint> *vec_, ulint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT32_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<ullint> *vec_, ullint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT64_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<float> *vec_ = 0, float* fp = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == 0) { vec_->at(siz) = *fp; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<c_char*> *vec_ = 0, void* vp = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz), " ") || !strlen(vec_->at(siz))) { vec_->at(siz) = 0; c_char* mid = reinterpret_cast<c_char*>(vp); vec_->at(siz) = mid; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::string> *vec_ = 0, std::string* sp = 0) { if (!vec_ || !sp) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { vec_->at(siz).clear(); vec_->at(siz).append(*sp); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::string> *vec_ = 0, c_char* sp = 0) { if (!vec_ || !sp) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { vec_->at(siz).clear(); vec_->at(siz).append(sp); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<DB_CONN*> *vec_ = 0, DB_CONN* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == -1) { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } } else { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz).Renew(val); vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<TINFO> *vec_ = 0, TINFO* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0) { if (!val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<lok_req> *vec_ = 0, lok_req* val = 0) { if (!val || !vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_FILE*> *vec_, BOT_FILE* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<HELD_MTX*> *vec_ = 0, HELD_MTX* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vn = (sint)siz; vec_->at(siz) = val; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOTF_CONN*> *vec_ = 0, BOTF_CONN* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == -1) { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } } else { vec_->at(siz) = val; vn = (sint)siz; val->lid = vn; vec_->at(siz)->lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_STMT> *vec_ = 0, BOT_STMT* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->lid = vn; vec_->at(siz).lid = vn; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<BOT_FLD> *vec_ = 0, BOT_FLD* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).fid < 0) { vec_->at(siz) = *val; vn = (sint)siz; val->fid = vn; vec_->at(siz).fid = vn; siz = vec_->size(); } siz++; } return vn; }

	sint AddValToVec(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_8 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_16 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_32 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_64 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_128 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_256 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_512 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_1024 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2048 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4096 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<std::vector<u_char>>* vec_ = 0, std::vector<u_char>* val = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<std::chrono::steady_clock::time_point> *vec_, std::chrono::steady_clock::time_point* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<u_char> *vec_, u_char* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<u_char> *vec_, u_char val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, &val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, &val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<void*> *vec_, void* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<sint> *vec_, sint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<slint> *vec_, slint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<sllint> *vec_, sllint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<uint> *vec_, uint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<ulint> *vec_, ulint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<ullint> *vec_, ullint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<float> *vec_, float* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<c_char*> *vec_, void* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(reinterpret_cast<c_char*>(val)); return viv; }
	sint AddValToVec(std::vector<std::string> *vec_, std::string* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<std::string> *vec_, c_char* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } std::string nval; nval.append(val); vec_->push_back(nval); return viv; }
	sint AddValToVec(std::vector<BOT_DB> *vec_, BOT_DB* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<DB_CONN*> *vec_, DB_CONN* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<BOTF_CONN*> *vec_, BOTF_CONN* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOT_FO_MAX || viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<BOT_CLIENT> *vec_, BOT_CLIENT* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_LOGDET> *vec_, BOT_LOGDET* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_FILE> *vec_, BOT_FILE* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<TINFO> *vec_, TINFO* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<HELD_MTX> *vec_, HELD_MTX* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<lok_req> *vec_, lok_req* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_DB*> *vec_, BOT_DB* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<BOT_CLIENT*> *vec_, BOT_CLIENT* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<BOT_LOGDET*> *vec_, BOT_LOGDET* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<BOT_FILE*> *vec_, BOT_FILE* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<TINFO*> *vec_, TINFO* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<HELD_MTX*> *vec_, HELD_MTX* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<BOT_DB_M> *vec_, BOT_DB_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_CLIENT_M> *vec_, BOT_CLIENT_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_LOGDET_M> *vec_, BOT_LOGDET_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_FILE_M> *vec_, BOT_FILE_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<TINFO_M> *vec_, TINFO_M* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_STMT> *vec_, BOT_STMT* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->lid = viv; vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<BOT_FLD> *vec_, BOT_FLD* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } val->fid = viv; vec_->push_back(*val); return viv; }

	std::chrono::steady_clock::time_point GetValInVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { std::chrono::steady_clock::time_point ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { *val = vec_->at(ele); ret = ele; } return ret; }
	_char *GetValInVec(std::vector<carr_2> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_4> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_8> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_16> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_32> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_64> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_128> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_256> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_512> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_1024> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_2048> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	_char *GetValInVec(std::vector<carr_4096> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
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

	BOT_FLD GetValInVec(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1) { BOT_FLD ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret.Renew(&vec_->at(ele)); } return ret; }
	sint GetValInVec(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, BOT_FLD* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_FLD_FID, &val->fid);
			ret = GetMembValInVec(vec_, ele, BOT_FLD_ORD, &val->ord);
			ret = GetMembValInVec(vec_, ele, BOT_FLD_BTO, &val->bto);
			ret = GetMembValInVec(vec_, ele, BOT_FLD_IHM, &val->is_home);
			ret = GetMembValInVec(vec_, ele, BOT_FLD_FLD, &val->fld);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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

	sint GetValInArr(DB_CONN vec_[BOT_ATT_LIM] = 0, sint ele = -1, DB_CONN* val = 0) { if (ele < 0 || !vec_ || ele >= (sint)BOT_ATT_LIM) { return -1; } val->Renew(&vec_[ele]); return ele; }
	sint GetValInArr(BOTF_CONN vec_[BOT_FS_LIM] = 0, sint ele = -1, BOTF_CONN* val = 0) { if (ele < 0 || !vec_ || ele >= (sint)BOT_ATT_LIM) { return -1; } val->Renew(&vec_[ele]); return ele; }

	DB_CONN* GetValInVec(std::vector<DB_CONN*> *vec_ = 0, sint ele = -1) { DB_CONN* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }

	BOT_DB* GetValInVec(std::vector<BOT_DB*> *vec_ = 0, sint ele = -1) { BOT_DB* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_DB GetValInVec(std::vector<BOT_DB> *vec_ = 0, sint ele = -1) { BOT_DB ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, BOT_DB* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_DB_FCON, &val->fcon);
			ret = GetMembValInVec(vec_, ele, BOT_DB_TYPE, &val->type);
			ret = GetMembValInVec(vec_, ele, BOT_DB_ID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_DB_NAME, &val->name);
			ret = GetMembValInVec(vec_, ele, BOT_DB_TABLES, &val->tables);
			ret = GetMembValInVec(vec_, ele, BOT_DB_COLUMNS, &val->columns);
			ret = GetMembValInVec(vec_, ele, BOT_DB_EXISTS, &val->exists);
			ret = GetMembValInVec(vec_, ele, BOT_DB_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_DB_FELE, &val->file_ele);
			ret = GetMembValInVec(vec_, ele, BOT_DB_OMODE, &val->omode);
			ret = GetMembValInVec(vec_, ele, BOT_DB_CONN, &val->connected);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
				else if (memb == BOT_DB_TABLES) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).tables.size()) { vp->push_back(vec_->at(ele).tables[siz]); siz++; } }
				else if (memb == BOT_DB_COLUMNS) { std::vector<std::vector<std::vector<std::string>>>* vp = reinterpret_cast<std::vector<std::vector<std::vector<std::string>>>*>(val); size_t siz = 0; while (siz < vec_->at(ele).columns.size()) { vp->push_back(vec_->at(ele).columns[siz]); siz++; } }
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
	BOT_DB_M* GetValInVec(std::vector<BOT_DB_M*> *vec_ = 0, sint ele = -1) { BOT_DB_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_DB_M GetValInVec(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1) { BOT_DB_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, BOT_DB_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_DB_FCON, &val->fcon);
			ret = GetMembValInVec(vec_, ele, BOT_DB_TYPE, &val->type);
			ret = GetMembValInVec(vec_, ele, BOT_DB_ID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_DB_NAME, &val->name);
			ret = GetMembValInVec(vec_, ele, BOT_DB_TABLES, &val->tsiz);
			ret = GetMembValInVec(vec_, ele, BOT_DB_COLUMNS, &val->csiz);
			ret = GetMembValInVec(vec_, ele, BOT_DB_EXISTS, &val->exists);
			ret = GetMembValInVec(vec_, ele, BOT_DB_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_DB_FELE, &val->file_ele);
			ret = GetMembValInVec(vec_, ele, BOT_DB_OMODE, &val->omode);
			ret = GetMembValInVec(vec_, ele, BOT_DB_CONN, &val->connected);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	BOT_CLIENT* GetValInVec(std::vector<BOT_CLIENT*> *vec_ = 0, sint ele = -1) { BOT_CLIENT* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_CLIENT GetValInVec(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1) { BOT_CLIENT ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, BOT_CLIENT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_C_LOGGED_IN, &val->loggedin);
			ret = GetMembValInVec(vec_, ele, BOT_C_U_PRIV, &val->updatepriv);
			ret = GetMembValInVec(vec_, ele, BOT_C_U_LOGIN, &val->updatelogin);
			ret = GetMembValInVec(vec_, ele, BOT_C_T_LOGINS, &val->totallogins);
			ret = GetMembValInVec(vec_, ele, BOT_C_F_LOGINS, &val->failed_logins);
			ret = GetMembValInVec(vec_, ele, BOT_C_PRIV, &val->priv);
			ret = GetMembValInVec(vec_, ele, BOT_C_ID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_C_LOGIN_NAME, &val->login_name);
			ret = GetMembValInVec(vec_, ele, BOT_C_NAME, &val->name);
			ret = GetMembValInVec(vec_, ele, BOT_C_L_LOGIN, &val->lastlogin);
			ret = GetMembValInVec(vec_, ele, BOT_C_L_DATE, &val->logindate);
			ret = GetMembValInVec(vec_, ele, BOT_C_LFL, &val->last_failed_login);
			ret = GetMembValInVec(vec_, ele, BOT_C_LAST_E, &val->lastexchange);
			ret = GetMembValInVec(vec_, ele, BOT_C_CBY, &val->c_by);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	BOT_CLIENT_M* GetValInVec(std::vector<BOT_CLIENT_M*> *vec_ = 0, sint ele = -1) { BOT_CLIENT_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_CLIENT_M GetValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1) { BOT_CLIENT_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, BOT_CLIENT_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_C_LOGGED_IN, &val->loggedin);
			ret = GetMembValInVec(vec_, ele, BOT_C_U_PRIV, &val->updatepriv);
			ret = GetMembValInVec(vec_, ele, BOT_C_U_LOGIN, &val->updatelogin);
			ret = GetMembValInVec(vec_, ele, BOT_C_T_LOGINS, &val->totallogins);
			ret = GetMembValInVec(vec_, ele, BOT_C_F_LOGINS, &val->failed_logins);
			ret = GetMembValInVec(vec_, ele, BOT_C_PRIV, &val->priv);
			ret = GetMembValInVec(vec_, ele, BOT_C_ID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_C_LOGIN_NAME, &val->login_name);
			ret = GetMembValInVec(vec_, ele, BOT_C_NAME, &val->name);
			ret = GetMembValInVec(vec_, ele, BOT_C_L_LOGIN, &val->lastlogin);
			ret = GetMembValInVec(vec_, ele, BOT_C_L_DATE, &val->logindate);
			ret = GetMembValInVec(vec_, ele, BOT_C_LFL, &val->last_failed_login);
			ret = GetMembValInVec(vec_, ele, BOT_C_LAST_E, &val->lastexchange);
			ret = GetMembValInVec(vec_, ele, BOT_C_CBY, &val->c_by);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	BOT_LOGDET* GetValInVec(std::vector<BOT_LOGDET*> *vec_ = 0, sint ele = -1) { BOT_LOGDET* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_LOGDET GetValInVec(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1) { BOT_LOGDET ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, BOT_LOGDET* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;
		
		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_LOG_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_S, &val->started);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_T, &val->logtitle);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_S_DATE, &val->startdate);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_Q, &val->log_q);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_CBY, &val->c_by);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	BOT_LOGDET_M* GetValInVec(std::vector<BOT_LOGDET_M*> *vec_ = 0, sint ele = -1) { BOT_LOGDET_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_LOGDET_M GetValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1) { BOT_LOGDET_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, BOT_LOGDET_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_LOG_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_S, &val->started);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_T, &val->logtitle);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_S_DATE, &val->startdate);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_LOG_Q, &val->lsiz);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	BOT_FILE* GetValInVec(std::vector<BOT_FILE*> *vec_ = 0, sint ele = -1) { BOT_FILE* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_FILE GetValInVec(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1) { BOT_FILE ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, BOT_FILE* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_FS_NAME, &val->name);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FP, &val->path);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FT, &val->type);
			//ret = GetMembValInVec(vec_, ele, BOT_FS_DAT, &val->dat);
			ret = GetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = GetMembValInVec(vec_, ele, BOT_FS_STATE, &val->fst);
			ret = GetMembValInVec(vec_, ele, BOT_FS_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
			ret = GetMembValInVec(vec_, ele, BOT_FS_BTO, &val->bto);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
				//else if (memb == BOT_FS_DAT) { ullint* vp = reinterpret_cast<ullint*>(val); if (vec_->at(ele).fst.filestats.st_size && vp) { memcpy((void*)vp, (void*)vec_->at(ele).dat, vec_->at(ele).fst.filestats.st_size); } ullint term = (ullint)'\0'; memcpy((void*)&vp[vec_->at(ele).fst.filestats.st_size], (void*)&term, sizeof(term)); }
				else if (memb == BOT_FS_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_FS_STATE) { bot_fstate* vp = reinterpret_cast<bot_fstate*>(val); vp->Renew(&vec_->at(ele).fst); }
				else if (memb == BOT_FS_LID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_FS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_FS_CM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).cm; }
				else if (memb == BOT_FS_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
				else if (memb == BOT_FS_BTO) { sllint* vp = reinterpret_cast<sllint*>(val); *vp = vec_->at(ele).bto; }
				else {}
				ret = 0;
			}
		}
		return ret;
	}
	BOT_FILE_M* GetValInVec(std::vector<BOT_FILE_M*> *vec_ = 0, sint ele = -1) { BOT_FILE_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	BOT_FILE_M GetValInVec(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1) { BOT_FILE_M ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, BOT_FILE_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_FS_NAME, &val->name);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FP, &val->path);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FT, &val->type);
			ret = GetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = GetMembValInVec(vec_, ele, BOT_FS_STATE, &val->fst);
			ret = GetMembValInVec(vec_, ele, BOT_FS_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
			ret = GetMembValInVec(vec_, ele, BOT_FS_BTO, &val->bto);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
				else {}
				ret = 0;
			}
		}
		return ret;
	}
	TINFO* GetValInVec(std::vector<TINFO*> *vec_ = 0, sint ele = -1) { TINFO* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<TINFO> *vec_ = 0, sint ele = -1, TINFO* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_TTS_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_TNAME, &val->thread_name);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_THREAD, &val->thread);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_ATTR, &val->attr);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_OPT, &val->opt);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_FIN, &val->fin);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_FUNC, &val->func);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_TIMEP, &val->t_I);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_MINR, &val->min_ratv);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_VALS, &val->vals);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	TINFO_M* GetValInVec(std::vector<TINFO_M*> *vec_ = 0, sint ele = -1) { TINFO_M* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, TINFO_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_TTS_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_TNAME, &val->thread_name);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_THREAD, &val->thread);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_ATTR, &val->attr);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_OPT, &val->opt);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_FIN, &val->fin);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_FUNC, &val->func);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_TIMEP, &val->t_I);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_MINR, &val->min_ratv);
			ret = GetMembValInVec(vec_, ele, BOT_TTS_VALS, &val->vals);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	HELD_MTX* GetValInVec(std::vector<HELD_MTX*> *vec_ = 0, sint ele = -1) { HELD_MTX* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, HELD_MTX* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, HMTX_W_MTX, &val->w_mtx);
			ret = GetMembValInVec(vec_, ele, HMTX_LOCK, &val->locked);
			ret = GetMembValInVec(vec_, ele, HMTX_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, HMTX_MEMS, &val->h_mems);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	lok_req* GetValInVec(std::vector<lok_req*> *vec_ = 0, sint ele = -1) { lok_req* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<lok_req> *vec_ = 0, sint ele = -1, lok_req* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_REQ_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_REQ_FID, &val->fid);
			ret = GetMembValInVec(vec_, ele, BOT_REQ_GMTX, &val->gmtx);
			ret = GetMembValInVec(vec_, ele, BOT_REQ_ELE, &val->ele);
			ret = GetMembValInVec(vec_, ele, BOT_REQ_META, &val->is_meta);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<lok_req> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	BOT_STMT* GetValInVec(std::vector<BOT_STMT*> *vec_ = 0, sint ele = -1) { BOT_STMT* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, BOT_STMT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = GetMembValInVec(vec_, ele, BOT_STMT_MAINT, &val->maint);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_STMT, &val->stmt);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_TTYPE, &val->it_type);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_CTYPES, &val->ic_type);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_CONT, &val->cont);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_DBNAME, &val->dbname);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_DBALIAS, &val->dbalias);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_OPTS, &val->opts);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_CSPEC, &val->cspec);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_RLIM, &val->rlim);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_TARG, &val->targ);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_ACT, &val->act);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_OSPEC, &val->ospec);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_IFEX, &val->ifex);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_COLS, &val->cols);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_VALS, &val->vals);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_CONDS, &val->conds);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_LID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_AN, &val->an);
		}
		return ret;
	}
	sint GetMembValInVec(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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

	sint SetValInVec(std::vector<carr_2> *vec_ = 0, sint ele = -1, _char val[2] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_4> *vec_ = 0, sint ele = -1, _char val[4] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_8> *vec_ = 0, sint ele = -1, _char val[8] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_16> *vec_ = 0, sint ele = -1, _char val[16] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_32> *vec_ = 0, sint ele = -1, _char val[32] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_64> *vec_ = 0, sint ele = -1, _char val[64] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_128> *vec_ = 0, sint ele = -1, _char val[128] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_256> *vec_ = 0, sint ele = -1, _char val[256] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_512> *vec_ = 0, sint ele = -1, _char val[512] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_1024> *vec_ = 0, sint ele = -1, _char val[1024] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_2048> *vec_ = 0, sint ele = -1, _char val[2048] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_4096> *vec_ = 0, sint ele = -1, _char val[4096] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<u_char> *vec_ = 0, sint ele = -1, u_char val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<void*> *vec_ = 0, sint ele = -1, void* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1, std::chrono::steady_clock::time_point* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = *val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, uint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, ulint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, ullint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, uint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, ulint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, ullint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<float> *vec_ = 0, sint ele = -1, float* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = *val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<c_char*> *vec_ = 0, sint ele = -1, c_char* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1, std::string* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele).clear(); vec_->at((size_t)ele).append(*val); ret = ele; } return ret; }
	
	sint SetValInVec(std::vector<BOT_FLD*> *vec_ = 0, sint ele = -1, BOT_FLD* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, BOT_FLD* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_FLD_FID, &val->fid);
			ret = SetMembValInVec(vec_, ele, BOT_FLD_ORD, &val->ord);
			ret = SetMembValInVec(vec_, ele, BOT_FLD_BTO, &val->bto);
			ret = SetMembValInVec(vec_, ele, BOT_FLD_IHM, &val->is_home);
			ret = SetMembValInVec(vec_, ele, BOT_FLD_FLD, &val->fld);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_DB*> *vec_ = 0, sint ele = -1, BOT_DB* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, BOT_DB* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_DB_FCON, &val->fcon);
			ret = SetMembValInVec(vec_, ele, BOT_DB_TYPE, &val->type);
			ret = SetMembValInVec(vec_, ele, BOT_DB_ID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_DB_NAME, &val->name);
			ret = SetMembValInVec(vec_, ele, BOT_DB_TABLES, &val->tables);
			ret = SetMembValInVec(vec_, ele, BOT_DB_COLUMNS, &val->columns);
			ret = SetMembValInVec(vec_, ele, BOT_DB_EXISTS, &val->exists);
			ret = SetMembValInVec(vec_, ele, BOT_DB_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_DB_FELE, &val->file_ele);
			ret = SetMembValInVec(vec_, ele, BOT_DB_OMODE, &val->omode);
			ret = SetMembValInVec(vec_, ele, BOT_DB_CONN, &val->connected);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, BOT_DB_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_DB_FCON, &val->fcon);
			ret = SetMembValInVec(vec_, ele, BOT_DB_TYPE, &val->type);
			ret = SetMembValInVec(vec_, ele, BOT_DB_ID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_DB_NAME, &val->name);
			ret = SetMembValInVec(vec_, ele, BOT_DB_TABLES, &val->tsiz);
			ret = SetMembValInVec(vec_, ele, BOT_DB_COLUMNS, &val->csiz);
			ret = SetMembValInVec(vec_, ele, BOT_DB_EXISTS, &val->exists);
			ret = SetMembValInVec(vec_, ele, BOT_DB_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_DB_FELE, &val->file_ele);
			ret = SetMembValInVec(vec_, ele, BOT_DB_OMODE, &val->omode);
			ret = SetMembValInVec(vec_, ele, BOT_DB_CONN, &val->connected);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_CLIENT*> *vec_ = 0, sint ele = -1, BOT_CLIENT* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, BOT_CLIENT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_C_LOGGED_IN, &val->loggedin);
			ret = SetMembValInVec(vec_, ele, BOT_C_U_PRIV, &val->updatepriv);
			ret = SetMembValInVec(vec_, ele, BOT_C_U_LOGIN, &val->updatelogin);
			ret = SetMembValInVec(vec_, ele, BOT_C_T_LOGINS, &val->totallogins);
			ret = SetMembValInVec(vec_, ele, BOT_C_F_LOGINS, &val->failed_logins);
			ret = SetMembValInVec(vec_, ele, BOT_C_PRIV, &val->priv);
			ret = SetMembValInVec(vec_, ele, BOT_C_ID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_C_LOGIN_NAME, &val->login_name);
			ret = SetMembValInVec(vec_, ele, BOT_C_NAME, &val->name);
			ret = SetMembValInVec(vec_, ele, BOT_C_L_LOGIN, &val->lastlogin);
			ret = SetMembValInVec(vec_, ele, BOT_C_L_DATE, &val->logindate);
			ret = SetMembValInVec(vec_, ele, BOT_C_LFL, &val->last_failed_login);
			ret = SetMembValInVec(vec_, ele, BOT_C_LAST_E, &val->lastexchange);
			ret = SetMembValInVec(vec_, ele, BOT_C_CBY, &val->c_by);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, BOT_CLIENT_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_C_LOGGED_IN, &val->loggedin);
			ret = SetMembValInVec(vec_, ele, BOT_C_U_PRIV, &val->updatepriv);
			ret = SetMembValInVec(vec_, ele, BOT_C_U_LOGIN, &val->updatelogin);
			ret = SetMembValInVec(vec_, ele, BOT_C_T_LOGINS, &val->totallogins);
			ret = SetMembValInVec(vec_, ele, BOT_C_F_LOGINS, &val->failed_logins);
			ret = SetMembValInVec(vec_, ele, BOT_C_PRIV, &val->priv);
			ret = SetMembValInVec(vec_, ele, BOT_C_ID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_C_LOGIN_NAME, &val->login_name);
			ret = SetMembValInVec(vec_, ele, BOT_C_NAME, &val->name);
			ret = SetMembValInVec(vec_, ele, BOT_C_L_LOGIN, &val->lastlogin);
			ret = SetMembValInVec(vec_, ele, BOT_C_L_DATE, &val->logindate);
			ret = SetMembValInVec(vec_, ele, BOT_C_LFL, &val->last_failed_login);
			ret = SetMembValInVec(vec_, ele, BOT_C_LAST_E, &val->lastexchange);
			ret = SetMembValInVec(vec_, ele, BOT_C_CBY, &val->c_by);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_LOGDET*> *vec_ = 0, sint ele = -1, BOT_LOGDET* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, BOT_LOGDET* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_LOG_LID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_S, &val->started);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_T, &val->logtitle);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_S_DATE, &val->startdate);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_Q, &val->log_q);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_CBY, &val->c_by);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, BOT_LOGDET_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_LOG_LID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_S, &val->started);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_T, &val->logtitle);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_S_DATE, &val->startdate);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_Q, &val->lsiz);
			ret = SetMembValInVec(vec_, ele, BOT_LOG_CBY, &val->c_by);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_FILE*> *vec_ = 0, sint ele = -1, BOT_FILE* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, BOT_FILE* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_FS_NAME, &val->name);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FP, &val->path);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FT, &val->type);
			ret = SetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = SetMembValInVec(vec_, ele, BOT_FS_STATE, &val->fst);
			ret = SetMembValInVec(vec_, ele, BOT_FS_LID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
			ret = SetMembValInVec(vec_, ele, BOT_FS_BTO, &val->bto);
			//ret = SetMembValInVec(vec_, ele, BOT_FS_DAT, &val->dat);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
			//else if (memb == BOT_FS_DAT) { ullint* val_ = reinterpret_cast<ullint*>(val); vec_->at(ele).SetDat(val_); }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SetValInVec(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, BOT_FILE_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_FS_NAME, &val->name);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FP, &val->path);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FT, &val->type);
			ret = SetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = SetMembValInVec(vec_, ele, BOT_FS_STATE, &val->fst);
			ret = SetMembValInVec(vec_, ele, BOT_FS_LID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
			ret = SetMembValInVec(vec_, ele, BOT_FS_BTO, &val->bto);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
			else if (memb == BOT_FS_BTO) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).bto = *val_; }
			else {}
			ret = ele;
		}
		return ret;
	}
	sint SetValInVec(std::vector<TINFO*> *vec_ = 0, sint ele = -1, TINFO* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<TINFO> *vec_ = 0, sint ele = -1, TINFO* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_TTS_LID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_TNAME, &val->thread_name);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_THREAD, &val->thread);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_ATTR, &val->attr);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_OPT, &val->opt);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_FIN, &val->fin);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_FUNC, &val->func);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_TIMEP, &val->t_I);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_MINR, &val->min_ratv);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_VALS, &val->vals);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, TINFO_M* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_TTS_LID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_TNAME, &val->thread_name);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_THREAD, &val->thread);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_ATTR, &val->attr);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_OPT, &val->opt);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_FIN, &val->fin);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_FUNC, &val->func);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_TIMEP, &val->t_I);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_MINR, &val->min_ratv);
			ret = SetMembValInVec(vec_, ele, BOT_TTS_VALS, &val->vals);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<HELD_MTX*> *vec_ = 0, sint ele = -1, HELD_MTX* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, HELD_MTX* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, HMTX_W_MTX, &val->w_mtx);
			ret = SetMembValInVec(vec_, ele, HMTX_LOCK, &val->locked);
			ret = SetMembValInVec(vec_, ele, HMTX_LID, &ele);
			ret = SetMembValInVec(vec_, ele, HMTX_MEMS, &val->h_mems);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<lok_req*> *vec_ = 0, sint ele = -1, lok_req* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<lok_req> *vec_ = 0, sint ele = -1, lok_req* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }
		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_REQ_LID, &val->lid);
			ret = SetMembValInVec(vec_, ele, BOT_REQ_FID, &val->fid);
			ret = SetMembValInVec(vec_, ele, BOT_REQ_GMTX, &val->gmtx);
			ret = SetMembValInVec(vec_, ele, BOT_REQ_ELE, &val->ele);
			ret = SetMembValInVec(vec_, ele, BOT_REQ_META, &val->is_meta);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<lok_req> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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
	sint SetValInVec(std::vector<BOT_STMT*> *vec_ = 0, sint ele = -1, BOT_STMT* val = 0) { if (!vec_ || !val || ele < 0) { return -1; } sint ret = -1; if (ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, BOT_STMT* val = 0)
	{
		if (!vec_ || !val || ele < 0) { return -1; }

		sint ret = -1;

		if (ele < (sint)vec_->size())
		{
			ret = SetMembValInVec(vec_, ele, BOT_STMT_MAINT, &val->maint);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_STMT, &val->stmt);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_TTYPE, &val->it_type);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_CTYPES, &val->ic_type);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_CONT, &val->cont);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_DBNAME, &val->dbname);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_DBALIAS, &val->dbalias);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_OPTS, &val->opts);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_CSPEC, &val->cspec);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_RLIM, &val->rlim);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_TARG, &val->targ);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_ACT, &val->act);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_OSPEC, &val->ospec);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_IFEX, &val->ifex);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_COLS, &val->cols);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_VALS, &val->vals);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_CONDS, &val->conds);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_LID, &val->lid);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_AN, &val->an);
			ret = ele;
		}
		return ret;
	}
	sint SetMembValInVec(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1, sint memb = -1, void* val = 0)
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

	sint PushToMembVal(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
			else {}
		}
		return ret;
	}
	sint PushToMembVal(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
			else {}
		}
		return ret;
	}
	sint PushToMembVal(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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
	sint PushToMembVal(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1, sint memb = -1, sint opt = -1, void* val = 0)
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

	sint ClearValFromVec(std::vector<carr_2> *vec_ = 0, _char val[2] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_4> *vec_ = 0, _char val[4] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_8> *vec_ = 0, _char val[8] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_16> *vec_ = 0, _char val[16] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_32> *vec_ = 0, _char val[32] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_64> *vec_ = 0, _char val[64] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_128> *vec_ = 0, _char val[128] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_256> *vec_ = 0, _char val[256] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_512> *vec_ = 0, _char val[512] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_1024> *vec_ = 0, _char val[1024] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_2048> *vec_ = 0, _char val[2048] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_4096> *vec_ = 0, _char val[4096] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<u_char> *vec_ = 0, u_char val = UCHAR_MAX, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)&vec_->at(siz), (void*)&val, sizeof(vec_->at(siz)))) { vec_->at(siz) = UCHAR_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<void*> *vec_ = 0, void* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp(vec_->at(siz),val,sizeof(vec_->at(siz)))) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == *val) { vec_->at(siz) = vtclr; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<sint> *vec_ = 0, sint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<slint> *vec_ = 0, slint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT32_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<sllint> *vec_ = 0, sllint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT64_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<uint> *vec_ = 0, uint val = UINT_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<ulint> *vec_ = 0, ulint val = UINT32_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT32_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<ullint> *vec_ = 0, ullint val = UINT64_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT64_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<float> *vec_ = 0, float* fp = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == *fp) { vec_->at(siz) = 0.0f; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<c_char*> *vec_ = 0, c_char* mid = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<std::string> *vec_ = 0, std::string* mid = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid->c_str())) { vec_->at(siz).clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_DB> *vec_ = 0, BOT_DB* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_DB ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<DB_CONN*> *vec_ = 0, DB_CONN* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == val->lid) { vec_->at(siz)->Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOTF_CONN*> *vec_ = 0, BOTF_CONN* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid == val->lid) { vec_->at(siz)->Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_DB_M> *vec_ = 0, BOT_DB_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_DB_M ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_CLIENT> *vec_ = 0, BOT_CLIENT* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_CLIENT ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_CLIENT_M> *vec_ = 0, BOT_CLIENT_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_CLIENT_M ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_LOGDET> *vec_ = 0, BOT_LOGDET* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_LOGDET ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_LOGDET_M> *vec_ = 0, BOT_LOGDET_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_LOGDET_M ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_FILE> *vec_ = 0, BOT_FILE* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_FILE_M> *vec_ = 0, BOT_FILE_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { BOT_FILE_M ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<TINFO> *vec_ = 0, TINFO* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { TINFO ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<TINFO_M> *vec_ = 0, TINFO_M* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { TINFO_M ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<HELD_MTX> *vec_ = 0, HELD_MTX* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { HELD_MTX ns; vec_->at(siz) = ns; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<lok_req> *vec_ = 0, lok_req* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).lid == val->lid) { vec_->at(siz).Clear(); ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_DB*> *vec_ = 0, BOT_DB* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_CLIENT*> *vec_ = 0, BOT_CLIENT* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_LOGDET*> *vec_ = 0, BOT_LOGDET* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->logtitle.c_str(), val->logtitle.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<BOT_FILE*> *vec_ = 0, BOT_FILE* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->name.c_str(), val->name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<TINFO*> *vec_ = 0, TINFO* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz)->thread_name.c_str(), val->thread_name.c_str())) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }

	sint ClearEleFromVec(std::vector<carr_2> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_4> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_8> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_16> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_32> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_64> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_128> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_256> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_512> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_1024> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_2048> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<carr_4096> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { if (strlen(vec_->at(ele).carr)) { vec_->at(ele).carr[0] = '\0'; ret = ele; } }return ret; }
	sint ClearEleFromVec(std::vector<u_char> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UCHAR_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<void*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = vtclr; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<sint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT_MIN; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<slint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT32_MIN; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT64_MIN; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<uint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT32_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT64_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<float> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0.0f; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<c_char*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = ""; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<std::string> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<DB_CONN*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele)->Clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOTF_CONN*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele)->Clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_FLD> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_DB> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_DB ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_DB> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_DB_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_DB_M> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_CLIENT ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_CLIENT> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_CLIENT_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_CLIENT_M> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_LOGDET ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_LOGDET> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_LOGDET_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_LOGDET_M> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_FILE> *vec_ = 0, sint ele = -1, sint memb = -1)
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
				//vec_->at(ele).ClearDat();
				//ret = ele;
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
			else {}
		}
		return ret;
	}
	sint ClearEleFromVec(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { BOT_FILE_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
	sint ClearMembVal(std::vector<BOT_FILE_M> *vec_ = 0, sint ele = -1, sint memb = -1)
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
			else {}
		}
		return ret;
	}
	sint ClearEleFromVec(std::vector<TINFO> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearMembVal(std::vector<TINFO> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<TINFO_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearMembVal(std::vector<TINFO_M> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<HELD_MTX> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).lid = -1; vec_->at(ele).w_mtx = -1; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<lok_req> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearMembVal(std::vector<lok_req> *vec_ = 0, sint ele = -1, sint memb = -1)
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
	sint ClearEleFromVec(std::vector<BOT_DB*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOT_CLIENT*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOT_LOGDET*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOT_FILE*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<TINFO*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<HELD_MTX*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }

	sint CleanVec(std::vector<carr_2> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_4> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_8> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_16> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_32> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_64> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_128> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_256> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_512> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_1024> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_2048> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<carr_4096> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!strlen(vec_->at(x).carr)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (strlen(vec_->at(y).carr)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y).carr); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!strlen(vec_->at(siz).carr)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<u_char> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UCHAR_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UCHAR_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == UCHAR_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<void*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) =vec_->at(y); sint z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == vtclr) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != vtclr) { vec_->at(x) = vec_->at(y); sint z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == vtclr) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<sint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT_MIN) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<slint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT32_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT32_MIN) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT32_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<sllint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT64_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT64_MIN) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT64_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<uint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<ulint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT32_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT32_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT32_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<ullint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT64_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT64_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT64_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<float> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == DBL_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != DBL_MIN) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == DBL_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<c_char*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } else { if (!strlen(vec_->at(x))) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } } sint siz = vec_->size() - 1; while (siz > -1) { if (!strcmp(vec_->at(siz), "") || !strlen(vec_->at(siz))) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<std::string> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).empty()) { for (size_t y = x + 1; y < vec_->size(); y++) { if (!vec_->at(y).empty()) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = vec_->size() - 1; while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), "") || vec_->at(siz).empty()) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_DB> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<DB_CONN*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) = vec_->at(y); sint z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid < 0) { vec_->pop_back(); } else { siz = -1; } } else { vec_->pop_back(); } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOTF_CONN*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) = vec_->at(y); sint z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid < 0) { vec_->pop_back(); } else { siz = -1; } } else { vec_->pop_back(); } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_CLIENT> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_LOGDET> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_FILE> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<TINFO> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<HELD_MTX> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0 && vec_->at(x).h_mems.empty() && vec_->at(x).m_mems.empty()) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0 && vec_->at(siz).h_mems.empty() && vec_->at(siz).m_mems.empty()) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<lok_req> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_DB*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_CLIENT*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_LOGDET*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_FILE*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<TINFO*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<HELD_MTX*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_DB_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_CLIENT_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_LOGDET_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_FILE_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<TINFO_M> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_STMT> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).lid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).lid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).lid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<BOT_FLD> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x).fid < 0) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y).fid > -1) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz).fid < 0) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }

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
		"\"TEST\", 1, 2 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"DEBUGLEVEL\", 1, 3 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"READFILE\", 10, 4 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"LOGIN\", 0, 5 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"SHOWCOMMANDS\", 10, 6 );",

		"INSERT INTO litebot.COMMANDS (" \
		"COMMAND, PRIV, CMD_ID ) VALUES (" \
		"\"ADDCOMMAND\", 100, 7 );",

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
		"\"AaÄäBbCcDdEeËëFfGgHhIiÏïJjKkLlMmNnOoÖöPpQqRrSsßTtUuÜüVvWwXxYyZz\", " \
		"\"BCDFGHJKLMNPQRSTVWXY\", \"bcdfghjklmnpqrsßtvwxyz\", \"AÄEËIÏOÖUÜ\", " \
		"\"aäeëiïoöuü\", \"0123456789\" );"
		/*
		"INSERT INTO litebot.LANGUAGES ( LANGUAGE, ALPHABET, " \
		"U_CASE_CONSONANTS, L_CASE_CONSONANTS, U_CASE_VOWELS, " \
		"L_CASE_VOWELS, NUMBER_SYMS ) VALUES ( \"l337 5p34k\", " \
		"\"AaÄäBbCcDdEeËëFfGgHhIiÏïJjKkLlMmNnOoÖöPpQqRrSsßTtUuÜüVvWwXxYyZz123456780\", " \
		"\"BCDFGHJKLMNPQRSTVWXY\", \"bcdfghjklmnpqrsßtvwxyz25678\", \"AÄEËIÏOÖUÜ1340\", " \
		"\"aäeëiïoöuü\", \"0123456789\" );"

		"INSERT INTO litebot.COMMON_SYMS (" \
		"SYMBOL, USAGES ) VALUES (" \
		"\"/#\", \"5\" );"
		*/
	};

	std::vector<BOT_STMT> litebot_pend;

	std::vector<BOT_STMT> code_pend;

	std::vector<c_char*> litebot_tablenames
	{
		"LAST_ACCESS",
		"COMMANDS",
		"ACCOUNTS",
		"LANGUAGES",
		"SYMS"
	};

	std::vector<c_char*> math_tablenames
	{
		"LAST_ACCESS",
		"ARITHMATIC",
		"ALGEBRA",
		"GEOMETRY",
		"TRIGONOMETRY",
		"CALCULUS"
	};

	/*
	std::vector<c_char*> code_tablenames
	{
		"LAST_ACCESS",
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

	std::vector<c_char*> word_tablenames
	{
		"LAST_ACCESS"
	};

	std::vector<c_char*> ex_tablenames
	{
		"LAST_ACCESS"
	};

	std::vector<c_char*> litebot_columns
	{
		"ID INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

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
		"LAST_MAINTAINED_NS INTEGER",

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

	std::vector<c_char*> math_columns
	{
		"ID INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

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
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

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
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

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

	std::vector<c_char*> ex_columns
	{
		"ID INTEGER " \
		"LAST_MODIFIED INTEGER " \
		"LAST_MAINTAINED INTEGER " \
		"LAST_MODIFIED_NS INTEGER " \
		"LAST_MAINTAINED_NS INTEGER",

		"ID INTEGER " \
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

	log_vec() { d_vec.clear(); m_vec.clear(); };

}LOG_VEC;

typedef struct to_thr_vec
{
	std::vector<TINFO> d_vec;
	std::vector<TINFO_M> m_vec;

	to_thr_vec() { d_vec.clear(); m_vec.clear(); };

}TO_THR_VEC;

typedef struct db_vec
{
	std::vector<BOT_DB> d_vec;
	std::vector<BOT_DB_M> m_vec;

	db_vec() { d_vec.clear(); m_vec.clear(); };

}DB_VEC;

typedef struct c_vec
{
	std::vector<BOT_CLIENT> d_vec;
	std::vector<BOT_CLIENT_M> m_vec;

	c_vec() { d_vec.clear(); m_vec.clear(); };

}C_VEC;

typedef struct fo_vec
{
	std::vector<BOT_FILE> d_vec;
	std::vector<BOT_FILE_M> m_vec;

	fo_vec() { d_vec.clear(); m_vec.clear(); };

}FO_VEC;

/*
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
MTX_MAX = 17
};
*/

// MTX_REQ
_mtx req_mtx;
lok_defr lok_d;

// MTX_CV
C_VEC bot_c_vec;

// MTX_LOG
LOG_VEC bot_log_vec;

// MTX_O
// mutex for std::cout

// MTX_DBC
DB_CONN DCON[BOT_ATT_LIM];
uint olim;

// MTX_PEND
std::vector<BOT_STMT> bot_t_pend;

// MTX_TTS
TO_THR_VEC tts_vec;
bot_thread_counter bot_thr_ct;

// MTX_DBL
DB_VEC bot_db_vec;

// MTX_FO
FO_VEC fileo_vec;

// MTX_TRAT
sllint thr_exe_min;

// MTX_STRT
bot_strt_up bot_strt;

// MTX_FCON
BOTF_CONN FCON[BOT_FS_LIM];

// MTX_BTIM
std::chrono::steady_clock::time_point bot_strt_tim;

// MTX_DMAP
#ifdef _WIN32
bot_dir bot_dmap("c:\\");
#else
#ifdef _BOT_FOR_ANDR_
bot_dir bot_dmap("mnt:\\");
#else
#ifdef __GNUC__
bot_dir bot_dmap("c:\\");
#endif
#endif
#endif

// MTX_FTYPE

std::vector<c_char*> bot_code_types;

// MTX_STYPE

std::vector<c_char*> bot_symbol_types
{
	"",
	"unclassified",
	"terminators",
	"separators",
	"vowels",
	"consonants",
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

class machine
{	
public:
	
	machine(sint i_debug_lvl = BOT_DEBUG_LVL, sint i_debug_m = BOT_DEBUG_M, sint nlid = -1, c_char* i_name = "", bool logmain = false, bool logmine = false)
	{
		quit = false;
		req_lock = false;
		boto_file = false;
		mk_thr = false;
		log_to[0] = logmain;
		log_to[1] = logmine;
		h_mtxs.clear();
		ptn.clear();
		thr_exe_mod = 1.0f;
		cur_path.clear();
		u_logs.clear();
		d_con_ = 0;
		f_con.clear();
		debug_lvl = i_debug_lvl;
		debug_m = i_debug_m;
		lid = nlid;
		thr_prio = BOT_STND_PRIO;
		uint siz = strlen(i_name);

		if (siz && siz < 256)
		{
			ptn.append(i_name);
		}

		relocks.clear();
		stk_ct = 0;
		sint h = -1;
		sint p = LockGMutex(MTX_BTIM, &h);

		if (p > -1)
		{
			if (!nlid)
			{
				bot_strt_tim = std::chrono::steady_clock::now();
			}

			bot_st = bot_strt_tim;
			stool.SetTClr(&bot_st);
			vtool.SetTClr(&bot_st);
			vtool.SetSTool(&stool);

			if (!h)
			{
				h = UnlockGMutex(MTX_BTIM);
			}
		}
	}

	sint LITEBot(carr_256 *ncar_ = 0, bool do_start_up = false)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint rc = bot_sprintf(outp.carr, outp.siz, "LITEBot(carr_256* ncar_(%i), bool do_start_up(%u))", (sint)ncar_, (uint)do_start_up);
			rc = Output(outp.carr, 2);
		}
		/*
		if (do_start_up)
		{
		sint xc = ProcVINs(2, BOT_MOD_PATH, "error032418", ".txt", "27", "04", "03/25/2018", "237", "08");
		xc = ProcVINs(3, BOT_MOD_PATH, "error032418", ".txt", "27", "04", "03/25/2018", "237", "03/25/2018");
		xc = ProcErrLog(3, BOT_MOD_PATH, "error032418", ".txt", "27", "04", "03/25/2018", "237", "03/24/2018");

		if (xc)
		{
		sint e = -1;
		}
		}
		*/
		//TINFO tts(0, ptn.c_str(), NULL, 0);
		//tts.lid = lid;
		//tts.fin = 0;
		//tts.t_I = std::chrono::steady_clock::now();
		//sint xc = PushToVec(&tts, MTX_TTS, true, true, false);

		if (!ncar_)
		{
			return -1;
		}

		//std::chrono::steady_clock::time_point tI = std::chrono::steady_clock::now();
		//sint xc = BOTFindHomeDir();
		//std::chrono::steady_clock::time_point tII = std::chrono::steady_clock::now();
		//std::chrono::duration<slint, std::milli> durI = std::chrono::duration_cast<std::chrono::duration<slint, std::milli>>(tII - tI);
		//tI = std::chrono::steady_clock::now();
		sint xc = BOTFindHomeDir();
		//tII = std::chrono::steady_clock::now();
		//std::chrono::duration<slint, std::milli> durII = std::chrono::duration_cast<std::chrono::duration<slint, std::milli>>(tII - tI);
		//carr_128 ncar;
		//rc = bot_sprintf(ncar.carr, ncar.siz, "BOTFindHomeDir() eta = %li | BOTInitFDir(%u) eta = %li", (slint)durI.count(), (uint)1, (slint)durII.count());
		//rc = BotOut(ncar.carr);

		if (xc)
		{
			sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "BOTFindHomeDir(1) fault. %i", xc);
			return -1;
		}

		xc = VerifyDatabases();

		if (xc)
		{
			sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "VerifyDatabases fault. %i databases failed.", xc);
			return -1;
		}

		xc = TM();

		if (xc)
		{
			sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "ThreadMaintenance fault: %i", xc);
			return -1;
		}
		return xc;
	}
	
private:

	bool quit;
	bool log_to[2];
	bool req_lock;
	bool boto_file;
	bool mk_thr;
	sint lid;
	sint thr_prio;
	sint debug_lvl;
	sint debug_m; /* debug_m = 0: no debug; 1: debug no cout for debug functions used in Output(); 2: debug with cout debug for functions used in Output();*/
	BOT_CLIENT Client;
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
	
	std::vector<_char> nrts_sep
	{
		' ',
		','
	};

	std::vector<_char> nrts_ord
	{
		'(',
		'{',
		'[',
		'<'
	};
	std::vector<_char> nrts_ord_
	{
		')',
		'}',
		']',
		'>'
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

	// global mutexes for lists
	sint LockReq()
	{
		if (req_lock)
		{
			return 0;
		}
		sint p = -1;

#ifdef BOT_FILE_TLOCK
#if BOT_FILE_TLOCK > 0
		for (p = pthread_mutex_trylock(&req_mtx.mtx); p != 0; p = pthread_mutex_trylock(&req_mtx.mtx))
		{
			slint rst = nsRest(BOT_REQREST, true);
		}
#else
		p = pthread_mutex_lock(&req_mtx.mtx);
#endif
#else
		p = pthread_mutex_lock(&req_mtx.mtx);
#endif

		if (!p)
		{
			req_lock = true;
		}
		return p;
	}
	sint UnlockReq()
	{
		if (!req_lock)
		{
			return -1;
		}

		sint p = pthread_mutex_unlock(&req_mtx.mtx);

		if (!p)
		{
			req_lock = false;
		}
		return p;
	}
	sint CheqMTXReqs(std::vector<lok_req>* nreqs_ = 0)
	{
		if (!nreqs_)
		{
			return -1;
		}

		sint p = LockReq();

		if (!p)
		{
			sint xl = vtool.ValInVec(&lok_d.held_ids, lid);

			if (xl > -1)
			{
				for (uint z = 0; z < lok_d.reqs.size(); z++)
				{
					if (lok_d.reqs[z].lid > -1)
					{
						if (lok_d.reqs[z].fid != lid && lok_d.reqs[z].fid > -1)
						{
							sint yl = vtool.ValInVec(&lok_d.held[xl], lok_d.reqs[z].gmtx);

							if (yl > -1)
							{
								if (lok_d.reqs[z].ele < 0)
								{
									if (lok_d.held[xl][yl].locked)
									{
										lok_req oreq(-1, lok_d.reqs[z].gmtx, -1, -1);
										uint y = 0;

										while (y < nreqs_->size())
										{
											if (nreqs_->at(y).gmtx == lok_d.reqs[z].gmtx && nreqs_->at(y).ele < 0)
											{
												y = nreqs_->size();
											}
											y++;
										}

										if (y == nreqs_->size())
										{
											nreqs_->push_back(oreq);
										}
									}
								}
								else
								{
									if (!lok_d.reqs[z].is_meta)
									{
										sint nl = vtool.ValInVec(&lok_d.held[xl][yl].h_mems, lok_d.reqs[z].ele);

										if (nl > -1)
										{
											sint i = vtool.ValInVec(&lok_d.held_ids, lok_d.reqs[z].fid);

											if (i > -1)
											{
												if (thr_prio < lok_d.held_p[i])
												{
													uint y = 0;

													while (y < nreqs_->size())
													{
														if (nreqs_->at(y).gmtx == lok_d.reqs[z].gmtx && nreqs_->at(y).ele == lok_d.reqs[z].ele && nreqs_->at(y).is_meta == lok_d.reqs[z].is_meta)
														{
															y = nreqs_->size();
														}
														y++;
													}

													if (y == nreqs_->size())
													{
														nreqs_->push_back(lok_d.reqs[z]);
													}
												}
												else
												{
													if (thr_prio == lok_d.held_p[i])
													{
														if (lok_d.held_t[i] < lok_d.held_t[xl])
														{
															uint y = 0;

															while (y < nreqs_->size())
															{
																if (nreqs_->at(y).gmtx == lok_d.reqs[z].gmtx && nreqs_->at(y).ele == lok_d.reqs[z].ele && nreqs_->at(y).is_meta == lok_d.reqs[z].is_meta)
																{
																	y = nreqs_->size();
																}
																y++;
															}

															if (y == nreqs_->size())
															{
																nreqs_->push_back(lok_d.reqs[z]);
															}
														}
													}
												}
											}
										}
									}
									else
									{
										sint nl = vtool.ValInVec(&lok_d.held[xl][yl].m_mems, lok_d.reqs[z].ele);

										if (nl > -1)
										{
											sint i = vtool.ValInVec(&lok_d.held_ids, lok_d.reqs[z].fid);

											if (i > -1)
											{
												if (thr_prio < lok_d.held_p[i])
												{
													uint y = 0;

													while (y < nreqs_->size())
													{
														if (nreqs_->at(y).gmtx == lok_d.reqs[z].gmtx && nreqs_->at(y).ele == lok_d.reqs[z].ele && nreqs_->at(y).is_meta == lok_d.reqs[z].is_meta)
														{
															y = nreqs_->size();
														}
														y++;
													}

													if (y == nreqs_->size())
													{
														nreqs_->push_back(lok_d.reqs[z]);
													}
												}
												else
												{
													if (thr_prio == lok_d.held_p[i])
													{
														if (lok_d.held_t[i] < lok_d.held_t[xl])
														{
															uint y = 0;

															while (y < nreqs_->size())
															{
																if (nreqs_->at(y).gmtx == lok_d.reqs[z].gmtx && nreqs_->at(y).ele == lok_d.reqs[z].ele && nreqs_->at(y).is_meta == lok_d.reqs[z].is_meta)
																{
																	y = nreqs_->size();
																}
																y++;
															}

															if (y == nreqs_->size())
															{
																nreqs_->push_back(lok_d.reqs[z]);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			p = UnlockReq();
			return 0;
		}
		return -1;
	}
	sint UpdMTXPrio()
	{
		sint ret = -1;

		if (mk_thr)
		{
			thr_prio = (sint)BOT_THR_PRIO;
			ret = 0;
		}

		if (ret)
		{
			if (d_con_)
			{
				if (d_con_->o_com)
				{
					thr_prio = (sint)BOT_DBOUT_PRIO;
					ret = 0;
				}
				else
				{
					thr_prio = (sint)BOT_DBO_PRIO;
					ret = 0;
				}
			}
		}

		if (ret)
		{
			if (boto_file)
			{
				thr_prio = (sint)BOT_FOUT_PRIO;
				ret = 0;
			}
		}
		
		if (ret)
		{
			if (!f_con.empty())
			{
				thr_prio = (sint)BOT_FO_PRIO;
			}
			else
			{
				thr_prio = (sint)BOT_STND_PRIO;
			}
		}

		ret = -1;
		sint p = LockReq();

		if (!p)
		{
			sint xc = vtool.ValInVec(&lok_d.held_ids, lid);

			if (xc > -1)
			{
				if (xc < (sint)lok_d.held_p.size())
				{
					lok_d.held_p[xc] = thr_prio;
				}
				ret = 0;
			}
			p = UnlockReq();
		}
		return ret;
	}
	sint UpdMTX()
	{
		bool clear = true;

		if (!h_mtxs.empty())
		{
			for (uint x = 0; x < h_mtxs.size(); x++)
			{
				if (h_mtxs[x].locked || !h_mtxs[x].h_mems.empty() || !h_mtxs[x].m_mems.empty())
				{
					if (clear)
					{
						if (h_mtxs[x].w_mtx > -1)
						{
							clear = false;
						}
					}
				}
				else
				{
					h_mtxs[x].Clear();
				}
			}
			sint x = vtool.CleanVec(&h_mtxs);
		}

		sint ret = -1;
		sint p = LockReq();

		if (!p)
		{
			sint xc = vtool.ValInVec(&lok_d.held_ids, lid);

			if (xc > -1)
			{
				if (!clear)
				{
					if (xc >= (sint)lok_d.held.size())
					{
						while (xc >= (sint)lok_d.held.size())
						{
							std::vector<HELD_MTX> nmtx;
							lok_d.held.push_back(nmtx);
						}
					}
					else
					{
						if (!lok_d.held[xc].empty())
						{
							lok_d.held[xc].clear();
						}
					}

					while (xc >= (sint)lok_d.held_t.size())
					{
						std::chrono::steady_clock::time_point nmtx = std::chrono::steady_clock::now();
						lok_d.held_t.push_back(nmtx);
					}

					while (xc >= (sint)lok_d.held_p.size())
					{
						lok_d.held_p.push_back(BOT_STND_PRIO);
					}

					lok_d.held_p[xc] = thr_prio;

					for (uint x = 0; x < h_mtxs.size(); x++)
					{
						if (h_mtxs[x].locked || !h_mtxs[x].h_mems.empty() || !h_mtxs[x].m_mems.empty())
						{
							ret = vtool.AddValToVec(&lok_d.held[xc], &h_mtxs[x], false, true);
						}
					}
				}
				else
				{
					lok_d.held_ids[xc] = -1;
					lok_d.held[xc].clear();
					lok_d.held_t[xc] = std::chrono::steady_clock::now();
					lok_d.held_p[xc] = BOT_STND_PRIO;
				}
				ret = 0;
			}
			else
			{
				xc = vtool.AddValToVec(&lok_d.held_ids, lid, false, true);

				if (xc > -1)
				{
					if (xc >= (sint)lok_d.held.size())
					{
						while (xc >= (sint)lok_d.held.size())
						{
							std::vector<HELD_MTX> nmtx;
							lok_d.held.push_back(nmtx);
						}
					}
					else
					{
						if (!lok_d.held[xc].empty())
						{
							lok_d.held[xc].clear();
						}
					}
					if (xc >= (sint)lok_d.held_t.size())
					{
						while (xc >= (sint)lok_d.held_t.size())
						{
							std::chrono::steady_clock::time_point nmtx = std::chrono::steady_clock::now();
							lok_d.held_t.push_back(nmtx);
						}
					}
					else
					{
						lok_d.held_t[xc] = std::chrono::steady_clock::now();
					}
					if (xc >= (sint)lok_d.held_p.size())
					{
						while (xc >= (sint)lok_d.held_p.size())
						{
							std::chrono::steady_clock::time_point nmtx = std::chrono::steady_clock::now();
							lok_d.held_p.push_back(BOT_STND_PRIO);
						}
						lok_d.held_p[xc] = thr_prio;
					}
					else
					{
						lok_d.held_p[xc] = thr_prio;
					}
					for (uint x = 0; x < h_mtxs.size(); x++)
					{
						if (h_mtxs[x].locked || !h_mtxs[x].h_mems.empty() || !h_mtxs[x].m_mems.empty())
						{
							ret = vtool.AddValToVec(&lok_d.held[xc], &h_mtxs[x], false, true);
						}
					}
					ret = 0;
				}
			}

			for (sint x = (sint)lok_d.held_ids.size() - 1; x > -1; x--)
			{
				if (lok_d.held_ids[x] < 0)
				{
					lok_d.held_ids.pop_back();
					lok_d.held.pop_back();
					lok_d.held_t.pop_back();
					lok_d.held_p.pop_back();
				}
				else
				{
					x = -1;
				}
			}
			p = UnlockReq();
		}
		return ret;
	}
	sint ReqMTX(lok_req* nreq = 0, bool wait = false)
	{
		if (!nreq)
		{
			return -1;
		}

		sint ret = 0;
		sint p = LockReq();

		if (!p)
		{
			sint i_ele = vtool.ValInVec(&lok_d.held_ids, lid);
			sint f_ele = vtool.ValInVec(&lok_d.held_ids, -1);

			if (i_ele < 0)
			{
				if (f_ele < 0)
				{
					i_ele = (sint)lok_d.held_ids.size();
					lok_d.held_ids.push_back(lid);

					while (i_ele >= (sint)lok_d.held.size())
					{
						std::vector<HELD_MTX> nmtx;
						lok_d.held.push_back(nmtx);
					}
					while (i_ele >= (sint)lok_d.held_t.size())
					{
						std::chrono::steady_clock::time_point nmtx = std::chrono::steady_clock::now();
						lok_d.held_t.push_back(nmtx);
					}
					while (i_ele >= (sint)lok_d.held_p.size())
					{
						lok_d.held_p.push_back(BOT_STND_PRIO);
					}
					lok_d.held_p[i_ele] = thr_prio;

					for (uint x = 0; x < h_mtxs.size(); x++)
					{
						if (h_mtxs[x].locked || !h_mtxs[x].h_mems.empty() || !h_mtxs[x].m_mems.empty())
						{
							lok_d.held[i_ele].push_back(h_mtxs[x]);
						}
					}
				}
				else
				{
					i_ele = f_ele;
					lok_d.held_ids[f_ele] = lid;
					lok_d.held_t[f_ele] = std::chrono::steady_clock::now();
					lok_d.held_p[f_ele] = thr_prio;
					lok_d.held[f_ele].clear();

					for (uint x = 0; x < h_mtxs.size(); x++)
					{
						if (h_mtxs[x].locked || !h_mtxs[x].h_mems.empty() || !h_mtxs[x].m_mems.empty())
						{
							lok_d.held[f_ele].push_back(h_mtxs[x]);
						}
					}
				}
			}
			else
			{
				if (f_ele < i_ele && f_ele > -1)
				{
					lok_d.held_ids[f_ele] = lok_d.held_ids[i_ele];
					lok_d.held_ids[i_ele] = -1;
					lok_d.held_t[f_ele] = lok_d.held_t[i_ele];
					lok_d.held_t[i_ele] = std::chrono::steady_clock::now();
					lok_d.held_p[f_ele] = thr_prio;
					lok_d.held_p[i_ele] = BOT_STND_PRIO;
					lok_d.held[f_ele].clear();
					lok_d.held[i_ele].clear();

					for (uint x = 0; x < h_mtxs.size(); x++)
					{
						if (h_mtxs[x].locked || !h_mtxs[x].h_mems.empty() || !h_mtxs[x].m_mems.empty())
						{
							lok_d.held[f_ele].push_back(h_mtxs[x]);
						}
					}
					i_ele = f_ele;
				}

				sint x = vtool.ValInVec(&lok_d.held[i_ele], nreq->gmtx);

				if (x > -1)
				{
					if (nreq->ele < 0)
					{
						if (lok_d.held[i_ele][x].locked)
						{
							p = UnlockReq();
							return 0;
						}
					}
					else
					{
						if (nreq->is_meta)
						{
							sint y = vtool.ValInVec(&lok_d.held[i_ele][x].m_mems, nreq->ele);

							if (y > -1)
							{
								p = UnlockReq();
								return 0;
							}
						}
						else
						{
							sint y = vtool.ValInVec(&lok_d.held[i_ele][x].h_mems, nreq->ele);

							if (y > -1)
							{
								p = UnlockReq();
								return 0;
							}
						}
					}
				}
			}

			nreq->at_time = lok_d.held_t[i_ele];

			for (sint siz = 0; siz < (sint)lok_d.held_ids.size(); siz++)
			{
				if (siz != i_ele && lok_d.held_ids[siz] > -1)
				{
					sint x = vtool.ValInVec(&lok_d.held[siz], nreq->gmtx);

					if (x > -1)
					{
						if (nreq->ele < 0)
						{
							if (lok_d.held[siz][x].locked)
							{
								if (!wait)
								{
									p = UnlockReq();
									return -1;
								}
								else
								{
									ret = -1;
								}
							}
						}
						else
						{
							if (nreq->is_meta == 1)
							{
								sint y = vtool.ValInVec(&lok_d.held[siz][x].m_mems, nreq->ele);

								if (y > -1)
								{
									if (!wait)
									{
										p = UnlockReq();
										return -1;
									}
									else
									{
										ret = -1;
									}
								}
							}
							else if (!nreq->is_meta)
							{
								sint y = vtool.ValInVec(&lok_d.held[siz][x].h_mems, nreq->ele);

								if (y > -1)
								{
									if (!wait)
									{
										p = UnlockReq();
										return -1;
									}
									else
									{
										ret = -1;
									}
								}
							}
							else
							{
								carr_128 ncar;
								sint xp = bot_sprintf(ncar.carr, ncar.siz, "requested mutex for element:%i is_meta: -1", nreq->ele);
								xp = BotOut(ncar.carr);
							}
						}
					}
				}
			}

			if (ret)
			{
				if (wait)
				{
					sint x = vtool.AddValToVec(&lok_d.reqs, nreq, true, true);

					if (x < 0)
					{
						std::cout << "unable to add mtx g:" << nreq->gmtx << " e:" << nreq->ele << " m:" << nreq->is_meta << " for:" << nreq->fid << std::endl;
					}
				}
				p = UnlockReq();
				return -1;
			}
			else
			{
				sint x = vtool.ValInVec(&h_mtxs, nreq->gmtx);

				if (x < 0)
				{
					HELD_MTX nmtx(nreq->gmtx, -1, false);
					x = vtool.AddValToVec(&h_mtxs, &nmtx, false, true);
				}
				if (nreq->ele < 0)
				{
					h_mtxs[x].locked = true;
				}
				else
				{
					if (!nreq->is_meta)
					{
						sint y = vtool.AddValToVec(&h_mtxs[x].h_mems, nreq->ele, true, true);
					}
					else
					{
						sint y = vtool.AddValToVec(&h_mtxs[x].m_mems, nreq->ele, true, true);
					}
				}
				if (wait)
				{
					x = WithdMTXReq(nreq);
				}
				x = UpdMTX();
			}
			p = UnlockReq();
		}
		return ret;
	}
	sint WithdMTXReq(lok_req* nreq = 0)
	{
		if (!nreq)
		{
			return -1;
		}

		sint ret = -1;
		sint p = LockReq();

		if (!p)
		{
			if (nreq->lid < 0)
			{
				ret = vtool.ValInVec(&lok_d.reqs, nreq);
			}
			else
			{
				ret = nreq->lid;
			}
			
			if (ret > -1)
			{
				p = vtool.ClearEleFromVec(&lok_d.reqs, ret);
			}

			p = vtool.CleanVec(&lok_d.reqs);
			p = UnlockReq();
		}
		return ret;
	}
	sint HasLock(sint g_opt = -1, sint ele = -1, bool is_meta = true)
	{
		if (g_opt < 0)
		{
			return -1;
		}

		sint xret = vtool.ValInVec(&h_mtxs, g_opt);

		if (xret > -1)
		{
			if (ele > -1)
			{
				if (!is_meta)
				{
					xret = vtool.ValInVec(&h_mtxs[xret].h_mems, ele);
				}
				else
				{
					xret = vtool.ValInVec(&h_mtxs[xret].m_mems, ele);
				}

				if (xret > -1)
				{
					xret = 1;
				}
				else
				{
					xret = 0;
				}
			}
			else
			{
				xret = 1;
			}
		}
		return xret;
	}
	sint LockGMutex(sint g_opt = -1, sint* had_lock = 0, bool sleep_wait = true)
	{
		if (debug_lvl >= 900 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::LockGMutex(sint g_opt(%i), sint* had_lock(%i), bool sleep_wait(%u))", g_opt, (sint)had_lock, (uint)sleep_wait);
			op = Output(outp.carr, 2);
		}

		if (g_opt < 0 || !had_lock)
		{
			return -1;
		}

		sint ele = vtool.ValInVec(&h_mtxs, g_opt);

		if (ele < 0)
		{
			HELD_MTX nmtx(g_opt, (sint)h_mtxs.size(), false);
			ele = vtool.AddValToVec(&h_mtxs, &nmtx, false, true);

			if (ele < 0)
			{
				return -1;
			}
		}

		if (*had_lock < 1)
		{
			if (h_mtxs[ele].locked)
			{
				*had_lock = 1;
				return ele;
			}
			else
			{
				*had_lock = 0;
			}
		}

		sint ret = -1;
		uint ct = 0;

		if (!sleep_wait)
		{
			ct = (uint)BOT_MTX_MAXCT - 1;
		}

		while (ct < BOT_MTX_MAXCT)
		{
			ct++;
			lok_req nreq(-1, g_opt, lid, -1);
			ret = ReqMTX(&nreq, sleep_wait);

			if (!ret)
			{
				ct = BOT_MTX_MAXCT;
			}
			else
			{
				if (sleep_wait)
				{
					if (ct >= BOT_MTX_MAXCT)
					{
						sint w = WithdMTXReq(&nreq);
					}
					else
					{
						slint rst = nsRest((slint)BOT_LOCKREST);
					}
				}
			}
		}
		if (ret)
		{
			if (sleep_wait)
			{
				if (debug_lvl >= 1 && debug_m)
				{
					carr_64 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "unable to lock Global Mutex(opt:%i sleep count(%u).", g_opt, ct);
					op = Output(outp.carr, 2);
				}
			}
			return -1;
		}
		else
		{
			if (debug_lvl >= 900 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "Locked Global Mutex(opt:%i sleep count(%u)).", g_opt, ct);
				op = Output(outp.carr, 2);
			}
		}
		return ele;
	}
	sint UnlockGMutex(sint g_opt = -1)
	{
		if (debug_lvl >= 900 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "UnlockGMutex(sint g_opt(%i))", g_opt);
			op = Output(outp.carr, 2);
		}

		if (g_opt < 0)
		{
			return -1;
		}

		sint ele = vtool.ValInVec(&h_mtxs, g_opt);
		sint lox = -1;

		if (ele > -1)
		{
			h_mtxs[ele].locked = false;
			lox = UpdMTX();

			if (lox)
			{
				if (debug_lvl >= 1 && debug_m)
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "unable to Clear() lok_req(ele:%i, mtx:%i)).", ele, g_opt);
					op = Output(outp.carr, 2);
				}
			}
			if (debug_lvl >= 900 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "Unlocked Global Mutex(opt:%i).", g_opt);
				op = Output(outp.carr, 2);
			}
		}
		if (lox)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				carr_64 outp;

				if (ele < 0)
				{
					sint op = bot_sprintf(outp.carr, outp.siz, "unable to find Global Mutex(opt:%i).", g_opt);
				}
				else
				{
					sint op = bot_sprintf(outp.carr, outp.siz, "unable to unlock Global Mutex(opt:%i).", g_opt);
				}
				sint op = Output(outp.carr, 2);
			}
			return -1;
		}
		return lox;
	}

	// locks within lists

	sint LockElement(sint g_opt = -1, sint ele = -1, sint* had_lock = 0, bool sleep_wait = true, bool is_meta = true)
	{
		if (debug_lvl >= 900 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "LockElement(sint g_opt(%i), sint ele(%i), sint* had_lock(%i), bool sleep_wait(%u), bool is_meta(%u))", g_opt, ele, (sint)had_lock, (uint)sleep_wait, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		if (g_opt < 0 || ele < 0 || !had_lock)
		{
			return -1;
		}

		sint ret = vtool.ValInVec(&h_mtxs, g_opt);

		if (ret < 0)
		{
			HELD_MTX nmtx(g_opt, -1, false);
			ret = vtool.AddValToVec(&h_mtxs, &nmtx, true, true);

			if (ret < 0)
			{
				return -1;
			}
		}

		if (*had_lock < 1)
		{
			sint xret = ret;
			if (!is_meta)
			{
				ret = vtool.ValInVec(&h_mtxs[xret].h_mems, ele);
			}
			else
			{
				ret = vtool.ValInVec(&h_mtxs[xret].m_mems, ele);
			}

			if (ret < 0)
			{
				*had_lock = 0;
			}
			else
			{
				*had_lock = 1;
				return 0;
			}
		}

		ret = -1;

		lok_req nreq(ele, g_opt, lid, (sint)is_meta);
		uint ct = 0;

		if (!sleep_wait)
		{
			ct = BOT_MTX_MAXCT - 1;
		}

		while (ct < BOT_MTX_MAXCT)
		{
			ct++;
			ret = ReqMTX(&nreq, sleep_wait);

			if (!ret)
			{
				ct = BOT_MTX_MAXCT;
			}
			else
			{
				if (sleep_wait)
				{
					if (ct >= BOT_MTX_MAXCT)
					{
						sint w = WithdMTXReq(&nreq);
					}
					else
					{
						slint rst = nsRest((slint)BOT_LOCKREST);
					}
				}
			}
		}

		if (ret)
		{
			if (sleep_wait)
			{
				if (debug_lvl >= 1 && debug_m)
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "unable to lock element(g:%i ele:%i is_meta:%u).", g_opt, ele, (uint)is_meta);
					op = Output(outp.carr, 2);
				}
			}
			return -1;
		}
		if (debug_lvl >= 900 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "locked element(g:%i ele:%i is_meta:%u).", g_opt, ele, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		return ret;
	}
	sint UnlockElement(sint g_opt = -1, sint ele = -1, bool is_meta = true)
	{
		if (debug_lvl >= 900 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "UnlockElement(sint g_opt(%i), sint ele(%i), bool is_meta(%u))", g_opt, ele, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		if (g_opt < 0 || ele < 0)
		{
			return -1;
		}

		sint p = vtool.ValInVec(&h_mtxs, g_opt);

		if (p < 0)
		{
			return -1;
		}

		sint ret = -1;

		if (!is_meta)
		{
			ret = vtool.ValInVec(&h_mtxs[p].h_mems, ele);
		}
		else
		{
			ret = vtool.ValInVec(&h_mtxs[p].m_mems, ele);
		}

		if (ret > -1)
		{
			if (!is_meta)
			{
				sint xc = vtool.ClearValFromVec(&h_mtxs[p].h_mems, ele, false);
				xc = vtool.CleanVec(&h_mtxs[p].h_mems);
			}
			else
			{
				sint xc = vtool.ClearValFromVec(&h_mtxs[p].m_mems, ele, false);
				xc = vtool.CleanVec(&h_mtxs[p].m_mems);
			}

			sint retx = UpdMTX();

			if (debug_lvl >= 900 && debug_m)
			{
				carr_128 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "unlocked element(g:%i ele:%i is_meta:%u).", g_opt, ele, (uint)is_meta);
				op = Output(outp.carr, 2);
			}
			return 0;
		}

		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "unable to unlock element(g:%i ele:%i is_meta:%u).", g_opt, ele, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		return -1;
	}

	// Open/Close Global Objects

	sint OpenObject(sint nobj = -1, sint nele = -1, sint is_meta = -1, sint* omode = 0, sint* r_opt = 0, sint* n_opt = 0)
	{
		if (!omode)
		{
			return -1;
		}
		if (nobj < 0)
		{
			return -1;
		}

		sint ret = -1;

		if (nele < 0)
		{
			ret = LockGMutex(nobj, r_opt);
		}
		else
		{
			switch (nobj)
			{
			case MTX_FO:
			{
				if (!is_meta)
				{
					ret = vtool.ValInVec(&f_con, nele);

					if (ret > -1)
					{
						return BOTOpenFile(nele, r_opt, false, true);
					}
					else
					{
						return LockElement(nobj, nele, r_opt, true, (bool)is_meta);
					}
				}
				else
				{
					return LockElement(nobj, nele, r_opt, true, (bool)is_meta);
				}
				break;
			}
			case MTX_DBL:
			{
				if (!is_meta)
				{
					return OpenDB(nele, *omode, r_opt, n_opt, true);
				}
				else
				{
					return LockElement(nobj, nele, r_opt, true, (bool)is_meta);
				}
				break;
			}
			default:
			{
				return LockElement(nobj, nele, r_opt, true, (bool)is_meta);
				break;
			}
			}
		}
		return ret;
	}
	sint CloseObject(sint nobj = -1, sint nele = -1, sint is_meta = -1, sint* r_opt = 0, sint* n_opt = 0)
	{
		if (nobj < 0)
		{
			return -1;
		}

		if (nele < 0)
		{
			return UnlockGMutex(nobj);
		}
		else
		{
			switch (nobj)
			{
			case MTX_FO:
			{
				sint ret = vtool.ValInVec(&h_mtxs, nobj);

				if (ret > -1)
				{
					if (!is_meta)
					{
						sint xret = ret;
						ret = vtool.ValInVec(&h_mtxs[xret].h_mems, nele);

						if (ret > -1)
						{
							for (uint x = 0; x < f_con.size(); x++)
							{
								if (f_con[x]->flid == nele)
								{
									if (r_opt)
									{
										*r_opt = f_con[x]->omode;
									}
									return BOTCloseFile(nele, false);
								}
							}
							return UnlockElement(nobj, nele, false);
						}
					}
					else
					{
						sint xret = ret;
						ret = vtool.ValInVec(&h_mtxs[xret].m_mems, nele);

						if (ret > -1)
						{
							return UnlockElement(nobj, nele, true);
						}
					}
				}
				break;
			}
			case MTX_DBL:
			{
				sint ret = vtool.ValInVec(&h_mtxs, nobj);

				if (ret > -1)
				{
					if (!is_meta)
					{
						sint xret = ret;
						ret = vtool.ValInVec(&h_mtxs[xret].h_mems, nele);

						if (ret > -1)
						{
							if (d_con_)
							{
								if (r_opt)
								{
									*r_opt = d_con_->omode;
								}
								return CloseDB(nele, n_opt, false);
							}
							else
							{
								return UnlockElement(nobj, nele, false);
							}
						}
					}
					else
					{
						sint xret = ret;
						ret = vtool.ValInVec(&h_mtxs[xret].m_mems, nele);

						if (ret > -1)
						{
							return UnlockElement(nobj, nele, true);
						}
					}
				}
				break;
			}
			default:
			{
				return UnlockElement(nobj, nele, (bool)is_meta);
				break;
			}
			}
		}
		return -1;
	}

	// manip global lists

	sint PushToVec(void *val_, sint g_opt, bool check = true, bool use_empty = true, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "PushToVec(void *val_(%i), sint g_opt(%i), bool is_meta(%u))", (sint)val_, g_opt, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		sint ret = -1;
		sint h = -1;
		sint p = LockGMutex(g_opt, &h);

		if (p > -1)
		{
			if (!is_meta)
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					BOT_CLIENT* vp = reinterpret_cast<BOT_CLIENT*>(val_);

					if (!vp->name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&bot_c_vec.d_vec, vp, check, use_empty);

						if (ret > -1)
						{
							BOT_CLIENT_M ns;
							ns.Renew(vp);
							sint iret = PushToVec(&ns, g_opt, true, true, true);
						}
					}
					break;
				}
				case MTX_LOG:
				{
					BOT_LOGDET* vp = reinterpret_cast<BOT_LOGDET*>(val_);

					if (!vp->logtitle.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&bot_log_vec.d_vec, vp, check, use_empty);

						if (ret > -1)
						{
							BOT_LOGDET_M ns;
							ns.Renew(vp);
							sint iret = PushToVec(&ns, g_opt, true, true, true);
						}
					}
					break;
				}
				case MTX_TTS:
				{
					TINFO* vp = reinterpret_cast<TINFO*>(val_);

					if (!vp->thread_name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&tts_vec.d_vec, vp, check, use_empty);

						if (ret > -1)
						{
							TINFO_M ns;
							ns.Renew(vp);
							sint iret = PushToVec(&ns, g_opt, true, true, true);
						}
					}
					break;
				}
				case MTX_DBL:
				{
					BOT_DB* vp = reinterpret_cast<BOT_DB*>(val_);

					if (!vp->name.empty())
					{

						vp->c_by = lid;
						ret = vtool.AddValToVec(&bot_db_vec.d_vec, vp, check, use_empty);

						if (ret > -1)
						{
							BOT_DB_M ns;
							ns.Renew(vp);
							sint iret = PushToVec(&ns, g_opt, true, true, true);
						}
					}
					break;
				}
				case MTX_FO:
				{
					BOT_FILE* vp = reinterpret_cast<BOT_FILE*>(val_);

					if (!vp->name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&fileo_vec.d_vec, vp, check, use_empty);

						if (ret > -1)
						{
							BOT_FILE_M ns;
							ns.Renew(vp);
							sint iret = PushToVec(&ns, g_opt, true, true, true);
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
			else
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					BOT_CLIENT_M* vp = reinterpret_cast<BOT_CLIENT_M*>(val_);

					if (!vp->name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&bot_c_vec.m_vec, vp, check, use_empty);
					}
					break;
				}
				case MTX_LOG:
				{
					BOT_LOGDET_M* vp = reinterpret_cast<BOT_LOGDET_M*>(val_);

					if (!vp->logtitle.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&bot_log_vec.m_vec, vp, check, use_empty);
					}
					break;
				}
				case MTX_TTS:
				{
					TINFO_M* vp = reinterpret_cast<TINFO_M*>(val_);

					if (!vp->thread_name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&tts_vec.m_vec, vp, check, use_empty);
					}
					break;
				}
				case MTX_DBL:
				{
					BOT_DB_M* vp = reinterpret_cast<BOT_DB_M*>(val_);

					if (!vp->name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&bot_db_vec.m_vec, vp, check, use_empty);
					}
					break;
				}
				case MTX_FO:
				{
					BOT_FILE_M* vp = reinterpret_cast<BOT_FILE_M*>(val_);

					if (!vp->name.empty())
					{
						vp->c_by = lid;
						ret = vtool.AddValToVec(&fileo_vec.m_vec, vp, check, use_empty);
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
			if (!h)
			{
				h = UnlockGMutex(g_opt);
			}
		}
		return ret;
	}
	sint PushToVecEleMem(void *val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, sint v_opt = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "PushToVecEleMem(void *val_(%i), sint g_opt(%i), sint ele(%i), sint memb(%i), sint g_opt(%i), bool is_meta(%u))", (sint)val_, g_opt, ele, memb, v_opt, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		sint ret = -1;
		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.PushToMembVal(&bot_c_vec.d_vec, ele, memb, v_opt, val_);

						if (ret > -1)
						{
							sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
						}
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.PushToMembVal(&bot_log_vec.d_vec, ele, memb, v_opt, val_);

						if (ret > -1)
						{
							sint iret = -1;

							if (memb == BOT_LOG_Q)
							{
								if (v_opt == 3)
								{
									std::vector<std::string> nvec = *(std::vector<std::string>*)val_;
									size_t siz = nvec.size();
									iret = PushToVecEleMem(&siz, g_opt, ele, memb, v_opt);
								}
								else if (v_opt == 2)
								{
									size_t siz = 1;
									iret = PushToVecEleMem(&siz, g_opt, ele, memb, v_opt);
								}
								else {}
							}
							else
							{
								iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
							}
						}
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.PushToMembVal(&tts_vec.d_vec, ele, memb, v_opt, val_);

						if (ret > -1)
						{
							sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
						}
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.PushToMembVal(&bot_db_vec.d_vec, ele, memb, v_opt, val_);

						if (ret > -1)
						{
							sint iret = -1;

							if (memb == BOT_DB_TABLES)
							{
								if (v_opt == 3)
								{
									std::vector<std::string> nvec = *(std::vector<std::string>*)val_;
									size_t siz = nvec.size();
									iret = PushToVecEleMem(&siz, g_opt, ele, memb, v_opt);
								}
								else if (v_opt == 2)
								{
									size_t siz = 1;
									iret = PushToVecEleMem(&siz, g_opt, ele, memb, v_opt);
								}
								else {}
							}
							else if (memb == BOT_DB_COLUMNS)
							{
								if (v_opt == 3)
								{
									std::vector<std::vector<std::vector<std::string>>> nvec = *(std::vector<std::vector<std::vector<std::string>>>*)val_;
									size_t siz = nvec.size();
									iret = PushToVecEleMem(&siz, g_opt, ele, memb, v_opt);
								}
								else if (v_opt == 2)
								{
									std::vector<std::string> nvec = *(std::vector<std::string>*)val_;
									size_t siz = 1;
									iret = PushToVecEleMem(&siz, g_opt, ele, memb, v_opt);
								}
								else {}
							}
							else
							{
								iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
							}
						}
						break;
					}
					case MTX_FO:
					{
						ret = vtool.PushToMembVal(&fileo_vec.d_vec, ele, memb, v_opt, val_);

						if (ret > -1)
						{
							sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.PushToMembVal(&bot_c_vec.m_vec, ele, memb, v_opt, val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.PushToMembVal(&bot_log_vec.m_vec, ele, memb, v_opt, val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.PushToMembVal(&tts_vec.m_vec, ele, memb, v_opt, val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.PushToMembVal(&bot_db_vec.m_vec, ele, memb, v_opt, val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.PushToMembVal(&fileo_vec.m_vec, ele, memb, v_opt, val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint GetInVec(void* val_, sint g_opt, bool cine = false, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "GetInVec(void* val_(%i), sint g_opt(%i), bool cine(%u), bool is_meta(%u))", (sint)val_, g_opt, (uint)cine, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		sint vsiz = VecSize(g_opt);

		switch (g_opt)
		{
		case MTX_CV:
		{
			if (!is_meta)
			{
				BOT_CLIENT_M xval;
				xval.Renew(reinterpret_cast<BOT_CLIENT*>(val_));
				sint xc = GetInVec((void*)&xval, g_opt, false, true);

				if (xc > -1)
				{
					return GetVecEle(val_, g_opt, xval.lid, false);
				}
			}
			else
			{
				BOT_CLIENT_M* vp = reinterpret_cast<BOT_CLIENT_M*>(val_);
				BOT_CLIENT_M np;
				sint siz = 0;

				for (sint x = GetVecEle(&np, g_opt, siz, is_meta); x > -1; x = GetVecEle(&np, g_opt, siz, is_meta))
				{
					if (!strcmp(np.login_name.c_str(), vp->login_name.c_str()))
					{
						vp->Renew(&np);
						return siz;
					}
					siz++;
				}
			}
			if (cine)
			{
				return PushToVec(val_, g_opt, true, true, is_meta);
			}
			break;
		}
		case MTX_LOG:
		{
			if (!is_meta)
			{
				BOT_LOGDET_M xval;
				xval.Renew(reinterpret_cast<BOT_LOGDET*>(val_));
				sint xc = GetInVec((void*)&xval, g_opt, false, true);

				if (xc > -1)
				{
					return GetVecEle(val_, g_opt, xval.lid, false);
				}
			}
			else
			{
				BOT_LOGDET_M* vp = reinterpret_cast<BOT_LOGDET_M*>(val_);
				BOT_LOGDET_M np;
				sint siz = 0;

				for (sint x = GetVecEle(&np, g_opt, siz, is_meta); x > -1; x = GetVecEle(&np, g_opt, siz, is_meta))
				{
					if (!strcmp(np.logtitle.c_str(), vp->logtitle.c_str()))
					{
						vp->Renew(&np);
						return siz;
					}
					siz++;
				}
			}
			if (cine)
			{
				return PushToVec(val_, g_opt, true, true, is_meta);
			}
			break;
		}
		case MTX_TTS:
		{
			if (!is_meta)
			{
				TINFO_M xval;
				xval.Renew(reinterpret_cast<TINFO*>(val_));
				sint xc = GetInVec((void*)&xval, g_opt, false, true);

				if (xc > -1)
				{
					return GetVecEle(val_, g_opt, xval.lid, false);
				}
			}
			else
			{
				TINFO_M* vp = reinterpret_cast<TINFO_M*>(val_);
				TINFO_M np;
				sint siz = 0;

				for (sint x = GetVecEle(&np, g_opt, siz, is_meta); x > -1; x = GetVecEle(&np, g_opt, siz, is_meta))
				{
					if (!strcmp(np.thread_name.c_str(), vp->thread_name.c_str()))
					{
						vp->Renew(&np);
						return siz;
					}
					siz++;
				}
			}
			if (cine)
			{
				return PushToVec(val_, g_opt, true, true, is_meta);
			}
			break;
		}
		case MTX_DBL:
		{
			if (!is_meta)
			{
				BOT_DB_M xval;
				xval.Renew(reinterpret_cast<BOT_DB*>(val_));
				sint xc = GetInVec((void*)&xval, g_opt, false, true);

				if (xc > -1)
				{
					return GetVecEle(val_, g_opt, xval.lid, false);
				}
				if (cine)
				{
					return PushToDBList(reinterpret_cast<BOT_DB*>(val_));
				}
			}
			else
			{
				BOT_DB_M* vp = reinterpret_cast<BOT_DB_M*>(val_);
				BOT_DB_M np;
				sint siz = 0;

				for (sint x = GetVecEle(&np, g_opt, siz, is_meta); x > -1; x = GetVecEle(&np, g_opt, siz, is_meta))
				{
					if (!strcmp(np.name.c_str(), vp->name.c_str()) && (np.type == vp->type || vp->type < 0))
					{
						vp->Renew(&np);
						return siz;
					}
					siz++;
				}
				if (cine)
				{
					return PushToVec(val_, g_opt, true, true, is_meta);
				}
			}
			break;
		}
		case MTX_DBC:
		{
			DB_CONN* vp = reinterpret_cast<DB_CONN*>(val_);
			DB_CONN nc;

			for (sint siz = 0; siz < (sint)BOT_ATT_LIM; siz++)
			{
				sint x = GetVecEle(&nc, g_opt, siz, is_meta);

				if (x > -1)
				{
					if (nc.mlid == vp->mlid)
					{
						vp->Renew(&nc);
						return siz;
					}
				}
			}
			break;
		}
		case MTX_FO:
		{
			if (!is_meta)
			{
				BOT_FILE_M xval;
				xval.Renew(reinterpret_cast<BOT_FILE*>(val_));
				sint xc = GetInVec((void*)&xval, g_opt, false, true);

				if (xc > -1)
				{
					return GetVecEle(val_, g_opt, xval.lid, false);
				}
			}
			else
			{
				BOT_FILE_M* vp = reinterpret_cast<BOT_FILE_M*>(val_);
				BOT_FILE_M np;
				sint siz = 0;

				for (sint x = GetVecEle(&np, g_opt, siz, is_meta); x > -1; x = GetVecEle(&np, g_opt, siz, is_meta))
				{
					if (!strcmp(np.name.c_str(), vp->name.c_str()) && !strcmp(np.path.c_str(), vp->path.c_str()) && !strcmp(np.type.c_str(), vp->type.c_str()))
					{
						vp->Renew(&np);
						return siz;
					}
					siz++;
				}
			}
			if (cine)
			{
				return PushToVec(val_, g_opt, true, true, is_meta);
			}
			break;
		}
		case MTX_FCON:
		{
			BOTF_CONN* vp = reinterpret_cast<BOTF_CONN*>(val_);
			BOTF_CONN nc;

			for (sint siz = 0; siz < (sint)BOT_FS_LIM; siz++)
			{
				sint x = GetVecEle(&nc, g_opt, siz, is_meta);

				if (x > -1)
				{
					if (nc.flid == vp->flid)
					{
						vp->Renew(&nc);
						return siz;
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
		return -1;
	}
	sint GetVecEle(void* val_ = 0, sint g_opt = -1, sint ele = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "GetVecEle(void* val_(%i), sint g_opt(%i), size_t ele(%u), bool is_meta(%u))", (sint)val_, g_opt, ele, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		if (!val_ || g_opt < 0 || ele < 0)
		{
			return -1;
		}

		sint ret = -1;
		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.GetValInVec(&bot_c_vec.d_vec, ele, (BOT_CLIENT*)val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.GetValInVec(&bot_log_vec.d_vec, ele, (BOT_LOGDET*)val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.GetValInVec(&tts_vec.d_vec, ele, (TINFO*)val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.GetValInVec(&bot_db_vec.d_vec, ele, (BOT_DB*)val_);
						break;
					}
					case MTX_DBC:
					{
						ret = vtool.GetValInArr(DCON, ele, (DB_CONN*)val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.GetValInVec(&fileo_vec.d_vec, ele, (BOT_FILE*)val_);
						break;
					}
					case MTX_FCON:
					{
						ret = vtool.GetValInArr(FCON, ele, (BOTF_CONN*)val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.GetValInVec(&bot_c_vec.m_vec, ele, (BOT_CLIENT_M*)val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.GetValInVec(&bot_log_vec.m_vec, ele, (BOT_LOGDET_M*)val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.GetValInVec(&tts_vec.m_vec, ele, (TINFO_M*)val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.GetValInVec(&bot_db_vec.m_vec, ele, (BOT_DB_M*)val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.GetValInVec(&fileo_vec.m_vec, ele, (BOT_FILE_M*)val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint GetEmptyVecEle(sint g_opt, bool is_meta = true, sint mode = -1)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "GetEmptyVecEle(sint g_opt(%i), bool is_meta(%u), sint mode(%i))", g_opt, (uint)is_meta, mode);
			op = Output(outp.carr, 2);
		}

		if (!mode || mode < 0)
		{
			std::vector<std::string> svec;
			sint ret = GetElementNames(g_opt, &svec, is_meta);

			if (ret > -1)
			{
				for (sint c = 0; c < (sint)svec.size(); c++)
				{
					if (!strlen(svec[c].c_str()))
					{
						return c;
					}
				}
			}
		}
		if ( mode > 0 || mode < 0)
		{
			std::vector<sint> svec;
			sint ret = GetElementIDs(g_opt, &svec, is_meta);

			if (ret > -1)
			{
				for (sint c = 0; c < (sint)svec.size(); c++)
				{
					if (svec[c] < 0)
					{
						return c;
					}
				}
			}
		}
		return -1;
	}
	sint GetVecEleMem(void* val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "GetVecEleMem(void* val_(%i), sint g_opt(%i), size_t ele(%u), sint memb(%i), bool is_meta(%u))", (sint)val_, g_opt, ele, memb, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		if (!val_ || ele < 0 || g_opt < 0 || memb < 0)
		{
			return -1;
		}

		sint ret = -1;
		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.GetMembValInVec(&bot_c_vec.d_vec, ele, memb, val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.GetMembValInVec(&bot_log_vec.d_vec, ele, memb, val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.GetMembValInVec(&tts_vec.d_vec, ele, memb, val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.GetMembValInVec(&bot_db_vec.d_vec, ele, memb, val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.GetMembValInVec(&fileo_vec.d_vec, ele, memb, val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.GetMembValInVec(&bot_c_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.GetMembValInVec(&bot_log_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.GetMembValInVec(&tts_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.GetMembValInVec(&bot_db_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.GetMembValInVec(&fileo_vec.m_vec, ele, memb, val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint SetVecEle(void* val_ = 0, sint g_opt = -1, sint ele = -1, bool cine = false, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "SetVecEle(void* val_(%i), sint g_opt(%i), sint ele(%i), bool cine(%u), bool is_meta(%u))", (sint)val_, g_opt, ele, (uint)cine, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		sint ret = -1;

		if (cine)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				sint x = -1;

				if (ele < 0)
				{
					ele = VecSize(g_opt, is_meta);
				}

				while (VecSize(g_opt, is_meta) < ele + 1)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						if (is_meta)
						{
							BOT_CLIENT_M nval;
							x = vtool.AddValToVec(&bot_c_vec.m_vec, &nval, false, false);
						}
						else
						{
							BOT_CLIENT nval;
							x = vtool.AddValToVec(&bot_c_vec.d_vec, &nval, false, false);
						}
						break;
					}
					case MTX_LOG:
					{
						if (is_meta)
						{
							BOT_LOGDET_M nval;
							x = vtool.AddValToVec(&bot_log_vec.m_vec, &nval, false, false);
						}
						else
						{
							BOT_LOGDET nval;
							x = vtool.AddValToVec(&bot_log_vec.d_vec, &nval, false, false);
						}
						break;
					}
					case MTX_TTS:
					{
						if (is_meta)
						{
							TINFO_M nval;
							x = vtool.AddValToVec(&tts_vec.m_vec, &nval, false, false);
						}
						else
						{
							TINFO nval;
							x = vtool.AddValToVec(&tts_vec.d_vec, &nval, false, false);
						}
						break;
					}
					case MTX_DBL:
					{
						if (is_meta)
						{
							BOT_DB_M nval;
							x = vtool.AddValToVec(&bot_db_vec.m_vec, &nval, false, false);
						}
						else
						{
							BOT_DB nval;
							x = vtool.AddValToVec(&bot_db_vec.d_vec, &nval, false, false);
						}
						break;
					}
					case MTX_FO:
					{
						if (is_meta)
						{
							BOT_FILE_M nval;
							x = vtool.AddValToVec(&fileo_vec.m_vec, &nval, false, false);
						}
						else
						{
							BOT_FILE nval;
							x = vtool.AddValToVec(&fileo_vec.d_vec, &nval, false, false);

						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
		}

		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.SetValInVec(&bot_c_vec.d_vec, ele, (BOT_CLIENT*)val_);

						if (ret > -1)
						{
							BOT_CLIENT_M ns;
							ns.Renew((BOT_CLIENT*)val_);
							sint iret = SetVecEle(&ns, g_opt, ele, true);
						}
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.SetValInVec(&bot_log_vec.d_vec, ele, (BOT_LOGDET*)val_);

						if (ret > -1)
						{
							BOT_LOGDET_M ns;
							ns.Renew((BOT_LOGDET*)val_);
							sint iret = SetVecEle(&ns, g_opt, ele, true);
						}
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.SetValInVec(&tts_vec.d_vec, ele, (TINFO*)val_);

						if (ret > -1)
						{
							TINFO_M ns;
							ns.Renew((TINFO*)val_);
							sint iret = SetVecEle(&ns, g_opt, ele, true);
						}
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.SetValInVec(&bot_db_vec.d_vec, ele, (BOT_DB*)val_);

						if (ret > -1)
						{
							BOT_DB_M ns;
							ns.Renew((BOT_DB*)val_);
							sint iret = SetVecEle(&ns, g_opt, ele, true);
						}
						break;
					}
					case MTX_FO:
					{
						ret = vtool.SetValInVec(&fileo_vec.d_vec, ele, (BOT_FILE*)val_);

						if (ret > -1)
						{
							BOT_FILE_M ns;
							ns.Renew((BOT_FILE*)val_);
							sint iret = SetVecEle(&ns, g_opt, ele, true);
						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.SetValInVec(&bot_c_vec.m_vec, ele, (BOT_CLIENT_M*)val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.SetValInVec(&bot_log_vec.m_vec, ele, (BOT_LOGDET_M*)val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.SetValInVec(&tts_vec.m_vec, ele, (TINFO_M*)val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.SetValInVec(&bot_db_vec.m_vec, ele, (BOT_DB_M*)val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.SetValInVec(&fileo_vec.m_vec, ele, (BOT_FILE_M*)val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint SetVecEleMem(void* val_ = 0, sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "SetVecEleMem(void* val_(%i), sint g_opt(%i), sint ele(%i), sint memb(%i), bool is_meta(%u))", (sint)val_, g_opt, ele, memb, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		sint ret = -1;
		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.SetMembValInVec(&bot_c_vec.d_vec, ele, memb, val_);

						if (ret > -1)
						{
							sint iret = SetVecEleMem(val_, g_opt, ele, memb);
						}
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.SetMembValInVec(&bot_log_vec.d_vec, ele, memb, val_);

						if (ret > -1)
						{
							sint iret = -1;

							if (memb == BOT_LOG_Q)
							{
								std::vector<std::string> nvec = *(std::vector<std::string>*)val_;
								size_t siz = nvec.size();
								iret = SetVecEleMem((void*)&siz, g_opt, ele, memb);
							}
							else
							{
								iret = SetVecEleMem(val_, g_opt, ele, memb);
							}
							if (iret == ret)
							{

							}
						}
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.SetMembValInVec(&tts_vec.d_vec, ele, memb, val_);
						if (ret > -1)
						{
							sint iret = SetVecEleMem(val_, g_opt, ele, memb);
						}
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.SetMembValInVec(&bot_db_vec.d_vec, ele, memb, val_);

						if (ret > -1)
						{
							sint iret = -1;

							if (memb == BOT_DB_TABLES)
							{
								std::vector<std::string> nvec = *(std::vector<std::string>*)val_;
								size_t siz = nvec.size();
								iret = SetVecEleMem((void*)&siz, g_opt, ele, memb);
							}
							else if (memb == BOT_DB_COLUMNS)
							{
								std::vector<std::vector<std::string>> nvec = *(std::vector<std::vector<std::string>>*)val_;
								size_t siz = nvec.size();
								iret = SetVecEleMem((void*)&siz, g_opt, ele, memb);
							}
							else
							{
								iret = SetVecEleMem(val_, g_opt, ele, memb);
							}
							if (iret == ret)
							{

							}
						}
						break;
					}
					case MTX_FO:
					{
						ret = vtool.SetMembValInVec(&fileo_vec.d_vec, ele, memb, val_);

						if (ret > -1)
						{
							sint iret = SetVecEleMem(val_, g_opt, ele, memb);

							if (iret == ret)
							{

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
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.SetMembValInVec(&bot_c_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.SetMembValInVec(&bot_log_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.SetMembValInVec(&tts_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.SetMembValInVec(&bot_db_vec.m_vec, ele, memb, val_);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.SetMembValInVec(&fileo_vec.m_vec, ele, memb, val_);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint ClearVecEle(sint g_opt = -1, sint ele = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "ClearVecEle(sint g_opt(%i), sint ele(%i), bool is_meta(%u))", g_opt, ele, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		sint ret = -1;
		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.ClearEleFromVec(&bot_c_vec.d_vec, ele);
						sint cl = vtool.CleanVec(&bot_c_vec.d_vec);

						if (ret > -1)
						{
							sint iret = ClearVecEle(g_opt, ele);
						}
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.ClearEleFromVec(&bot_log_vec.d_vec, ele);
						sint cl = vtool.CleanVec(&bot_log_vec.d_vec);

						if (ret > -1)
						{
							sint iret = ClearVecEle(g_opt, ele);
						}
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.ClearEleFromVec(&tts_vec.d_vec, ele);
						sint cl = vtool.CleanVec(&tts_vec.d_vec);

						if (ret > -1)
						{
							sint iret = ClearVecEle(g_opt, ele);
						}
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.ClearEleFromVec(&bot_db_vec.d_vec, ele);
						sint cl = vtool.CleanVec(&bot_db_vec.d_vec);

						if (ret > -1)
						{
							sint iret = ClearVecEle(g_opt, ele);
						}
						break;
					}
					case MTX_FO:
					{
						ret = vtool.ClearEleFromVec(&fileo_vec.d_vec, ele);
						sint cl = vtool.CleanVec(&fileo_vec.d_vec);

						if (ret > -1)
						{
							sint iret = ClearVecEle(g_opt, ele);
						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.ClearEleFromVec(&bot_c_vec.m_vec, ele);
						sint cl = vtool.CleanVec(&bot_c_vec.m_vec);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.ClearEleFromVec(&bot_log_vec.m_vec, ele);
						sint cl = vtool.CleanVec(&bot_log_vec.m_vec);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.ClearEleFromVec(&tts_vec.m_vec, ele);
						sint cl = vtool.CleanVec(&tts_vec.m_vec);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.ClearEleFromVec(&bot_db_vec.m_vec, ele);
						sint cl = vtool.CleanVec(&bot_db_vec.m_vec);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.ClearEleFromVec(&fileo_vec.m_vec, ele);
						sint cl = vtool.CleanVec(&fileo_vec.m_vec);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint ClearVecEleMem(sint g_opt = -1, sint ele = -1, sint memb = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "ClearVecEle(sint g_opt(%i), sint ele(%i), sint memb(%i), bool is_meta(%u))", g_opt, ele, memb, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		sint ret = -1;
		sint xh = -1;
		sint x = LockElement(g_opt, ele, &xh, true, is_meta);

		if (!x)
		{
			sint h = -1;
			sint p = LockGMutex(g_opt, &h);

			if (p > -1)
			{
				if (!is_meta)
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.ClearMembVal(&bot_c_vec.d_vec, ele, memb);
						if (ret > -1)
						{
							sint iret = ClearVecEleMem(g_opt, ele, memb);
						}
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.ClearMembVal(&bot_log_vec.d_vec, ele, memb);
						if (ret > -1)
						{
							sint iret = ClearVecEleMem(g_opt, ele, memb);
						}
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.ClearMembVal(&tts_vec.d_vec, ele, memb);
						if (ret > -1)
						{
							sint iret = ClearVecEleMem(g_opt, ele, memb);
						}
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.ClearMembVal(&bot_db_vec.d_vec, ele, memb);
						if (ret > -1)
						{
							sint iret = ClearVecEleMem(g_opt, ele, memb);
						}
						break;
					}
					case MTX_FO:
					{
						ret = vtool.ClearMembVal(&fileo_vec.d_vec, ele, memb);
						if (ret > -1)
						{
							sint iret = ClearVecEleMem(g_opt, ele, memb);
						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
				{
					switch (g_opt)
					{
					case MTX_CV:
					{
						ret = vtool.ClearMembVal(&bot_c_vec.m_vec, ele, memb);
						break;
					}
					case MTX_LOG:
					{
						ret = vtool.ClearMembVal(&bot_log_vec.m_vec, ele, memb);
						break;
					}
					case MTX_TTS:
					{
						ret = vtool.ClearMembVal(&tts_vec.m_vec, ele, memb);
						break;
					}
					case MTX_DBL:
					{
						ret = vtool.ClearMembVal(&bot_db_vec.m_vec, ele, memb);
						break;
					}
					case MTX_FO:
					{
						ret = vtool.ClearMembVal(&fileo_vec.m_vec, ele, memb);
						break;
					}
					default:
					{
						break;
					}
					}
				}
				if (!h)
				{
					h = UnlockGMutex(g_opt);
				}
			}
			if (!xh)
			{
				xh = UnlockElement(g_opt, ele, is_meta);
			}
		}
		return ret;
	}
	sint VecSize(sint g_opt = -1, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "VecSize(sint g_opt(%i), bool is_meta(%u))", g_opt, (uint)is_meta);
			op = Output(outp.carr, 2);
		}
		sint ret = -1;
		sint h = -1;
		sint p = LockGMutex(g_opt, &h);

		if (p > -1)
		{
			if (!is_meta)
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					ret = (sint)bot_c_vec.d_vec.size();
					break;
				}
				case MTX_LOG:
				{
					ret = (sint)bot_log_vec.d_vec.size();
					break;
				}
				case MTX_TTS:
				{
					ret = (sint)tts_vec.d_vec.size();
					break;
				}
				case MTX_DBL:
				{
					ret = (sint)bot_db_vec.d_vec.size();
					break;
				}
				case MTX_FO:
				{
					ret = (sint)fileo_vec.d_vec.size();
					break;
				}
				default:
				{
					break;
				}
				}
			}
			else
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					ret = (sint)bot_c_vec.m_vec.size();
					break;
				}
				case MTX_LOG:
				{
					ret = (sint)bot_log_vec.m_vec.size();
					break;
				}
				case MTX_TTS:
				{
					ret = (sint)tts_vec.m_vec.size();
					break;
				}
				case MTX_DBL:
				{
					ret = (sint)bot_db_vec.m_vec.size();
					break;
				}
				case MTX_FO:
				{
					ret = (sint)fileo_vec.m_vec.size();
					break;
				}
				default:
				{
					break;
				}
				}
			}
			if (!h)
			{
				h = UnlockGMutex(g_opt);
			}
		}
		return ret;
	}
	sint GetElementNames(sint g_opt = -1, std::vector<std::string>* nvec = 0, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "GetElementNames(sint g_opt(%i), std::vector<std::string>* nvec(%i), is_meta(%u))", g_opt, (sint)nvec, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		sint ret = -1;
		
		for (sint ele = 0; ele < VecSize(g_opt, is_meta); ele++)
		{
			std::string str;

			if (!is_meta)
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_C_NAME);
					nvec->push_back(str);
					break;
				}
				case MTX_LOG:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_LOG_T);
					nvec->push_back(str);
					break;
				}
				case MTX_TTS:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_TTS_TNAME);
					nvec->push_back(str);
					break;
				}
				case MTX_DBL:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_DB_NAME);
					nvec->push_back(str);
					break;
				}
				case MTX_FO:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_FS_NAME);
					nvec->push_back(str);
					break;
				}
				default:
				{
					break;
				}
				}
			}
			else
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_C_NAME);
					nvec->push_back(str);
					break;
				}
				case MTX_LOG:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_LOG_T);
					nvec->push_back(str);
					break;
				}
				case MTX_TTS:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_TTS_TNAME);
					nvec->push_back(str);
					break;
				}
				case MTX_DBL:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_DB_NAME);
					nvec->push_back(str);
					break;
				}
				case MTX_FO:
				{
					ret = GetVecEleMem(&str, g_opt, ele, BOT_FS_NAME);
					nvec->push_back(str);
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		return ret;
	}
	sint GetElementIDs(sint g_opt = -1, std::vector<sint> *nvec = 0, bool is_meta = true)
	{
		if (debug_lvl >= 800 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "GetElementIDs(sint g_opt(%i), std::vector<sint>* nvec(%i), is_meta(%u))", g_opt, (sint)nvec, (uint)is_meta);
			op = Output(outp.carr, 2);
		}

		sint ret = -1;

		for (sint ele = 0; ele < VecSize(g_opt, is_meta); ele++)
		{
			sint r = -1;

			if (!is_meta)
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_C_ID);
					nvec->push_back(r);
					break;
				}
				case MTX_LOG:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_LOG_LID);
					nvec->push_back(r);
					break;
				}
				case MTX_TTS:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_TTS_LID);
					nvec->push_back(r);
					break;
				}
				case MTX_DBL:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_DB_ID);
					nvec->push_back(r);
					break;
				}
				case MTX_FO:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_FS_LID);
					nvec->push_back(r);
					break;
				}
				default:
				{
					break;
				}
				}
			}
			else
			{
				switch (g_opt)
				{
				case MTX_CV:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_C_ID);
					nvec->push_back(r);
					break;
				}
				case MTX_LOG:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_LOG_LID);
					nvec->push_back(r);
					break;
				}
				case MTX_TTS:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_TTS_LID);
					nvec->push_back(r);
					break;
				}
				case MTX_DBL:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_DB_ID);
					nvec->push_back(r);
					break;
				}
				case MTX_FO:
				{
					ret = GetVecEleMem(&r, g_opt, ele, BOT_FS_LID);
					nvec->push_back(r);
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		return ret;
	}

	// Date / Time 

	sint GetDateTimeMS(_char str_[] = 0, bool form = true)
	{
		if (!str_)
		{
			return -1;
		}
#ifdef _WIN32
		SYSTEMTIME tim;
		GetSystemTime(&tim);

		if (form)
		{
			sint xc = bot_sprintf(str_, 128, "%.2d / %.2d / %.4d %.2d : %.2d : %.2d : %.3d", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond, tim.wMilliseconds);
		}
		else
		{
			sint xc = bot_sprintf(str_, 128, "%.2d %.2d %.4d %.2d %.2d %.2d %.3d", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond, tim.wMilliseconds);
		}
#else
		std::time_t tstamp;
		struct tm t;
		struct timespec ti;
		sint xc = time(&tstamp);
		xc = clock_gettime(CLOCK_REALTIME, &ti);
		t = *gmtime(&tstamp);
		xc = bot_sprintf(str_, 128, "%.2d / %.2d / %.4d %.2d : %.2d : %.2d : %.9d", t.tm_mon, t.tm_mday, t.tm_year, t.tm_hour, t.tm_min, ti.tv_sec, ti.tv_nsec);
#endif	
		return 0;
	}
	sint GetDateTime(_char str_[] = 0, bool form = true)
	{
		if (!str_)
		{
			return -1;
		}
#ifdef _WIN32
		SYSTEMTIME tim;
		GetSystemTime(&tim);

		if (form)
		{
			sint xc = bot_sprintf(str_, 128, "%.2d / %.2d / %.4d %.2d : %.2d : %.2d", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond);
		}
		else
		{
			sint xc = bot_sprintf(str_, 128, "%.2d %.2d %.4d %.2d %.2d %.2d", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond);
		}
#else
		std::time_t tstamp;
		struct tm t;
		struct timespec ti;
		sint xc = time(&tstamp);
		xc = clock_gettime(CLOCK_REALTIME, &ti);
		t = *gmtime(&tstamp);
		xc = bot_sprintf(str_, 128, "%.2d / %.2d / %.4d %.2d : %.2d : %.2d", t.tm_mon, t.tm_mday, t.tm_year, t.tm_hour, t.tm_min, ti.tv_sec);
#endif
		return 0;
	}
	sint GetTime(_char str_[] = 0, bool forms = true)
	{
		if (!str_)
		{
			return -1;
		}
#ifdef _WIN32
		SYSTEMTIME tim;
		GetSystemTime(&tim);

		if (forms)
		{
			sint xc = bot_sprintf(str_, 64, "%.2u : %.2u : %.2u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond);
		}
		else
		{
			sint xc = bot_sprintf(str_, 64, "%.2d %.2d %.2d", (double)tim.wHour, (double)tim.wMinute, (double)tim.wSecond);
		}
#else
		std::time_t tstamp;
		struct tm t;
		struct timespec ti;
		sint xc = clock_gettime(CLOCK_REALTIME, &ti);
		t = *gmtime(&tstamp);

		if (forms)
		{
			xc = bot_sprintf(str_, 64, "%.2d : %.2d : %.2d", t.tm_hour, t.tm_min, ti.tv_sec);
		}
		else
		{
			xc = bot_sprintf(str_, 64, "%.2d %.2d %.2d", t.tm_hour, t.tm_min, ti.tv_sec);
		}
#endif
		return 0;
	}
	sint GetTimeMS(_char str_[] = 0, bool forms = true)
	{
		if (!str_)
		{
			return -1;
		}
#ifdef _WIN32
		SYSTEMTIME tim;
		GetSystemTime(&tim);

		if (forms)
		{
			sint xc = bot_sprintf(str_, 64, "%.2u : %.2u : %.2u : %.3u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond, (uint)tim.wMilliseconds);
		}
		else
		{
			sint xc = bot_sprintf(str_, 64, "%.2d %.2d %.2d %.3d", (double)tim.wHour, (double)tim.wMinute, (double)tim.wSecond, (double)tim.wMilliseconds);
		}
#else
		std::time_t tstamp;
		struct tm t;
		struct timespec ti;
		sint xc = clock_gettime(CLOCK_REALTIME, &ti);
		t = *gmtime(&tstamp);

		if (forms)
		{
			xc = bot_sprintf(str_, 64, "%.2d : %.2d : %.2d : %.9d", t.tm_hour, t.tm_min, ti.tv_sec, ti.tv_nsec);
		}
		else
		{
			xc = bot_sprintf(str_, 64, "%.2d %.2d %.2d %.9d", t.tm_hour, t.tm_min, ti.tv_sec, ti.tv_nsec);
		}
#endif
		return 0;
	}
	sint GetDate(carr_32* str_ = 0, bool form = true)
	{
		if (!str_)
		{
			return -1;
		}
		std::time_t tstamp;
		struct tm t;
		sint xc = (sint)time(&tstamp);
#ifdef _WIN32
		errno_t bot_err = gmtime_s(&t, &tstamp);
#else
		t = *gmtime(&tstamp);
#endif
		if (form)
		{
			xc = strftime(str_->carr, str_->siz, "%m/%d/%Y", &t);
		}
		else
		{
			xc = strftime(str_->carr, str_->siz, "%m%d%Y", &t);
		}
		return 0;
	}
	sllint GetCentSec()
	{
		std::time_t tstamp;
		struct tm t, tx;
		sint xc = (sint)time(&tstamp);
#ifdef _WIN32
		errno_t bot_err = gmtime_s(&t, &tstamp);
		errno_t bot_err1 = gmtime_s(&tx, &tstamp);
#else
		t = *gmtime(&tstamp);
		tx = *gmtime(&tstamp);
#endif
		t.tm_sec = 0;
		t.tm_min = 0;
		t.tm_hour = 0;
		t.tm_mday = 1;
		t.tm_mon = 1;
		t.tm_year = 100;
		sllint x = (sllint)difftime(mktime(&tx), mktime(&t));
		return x;
	}

	// Log Function

	sint UsingLog(_char nm[] = 0)
	{
		if (nm)
		{
			size_t siz = 0;

			while (siz < u_logs.size())
			{
				if (!strcmp(nm, u_logs[siz].logtitle.c_str()))
				{
					return (sint)siz;
				}
				siz++;
			}
		}
		return -1;
	}
	sint LogName(sint opt, carr_256* nm = 0, carr_32* dat = 0, bool tomine = false)
	{
		if (!nm || !dat)
		{
			return -1;
		}
		switch (opt)
		{
		case 0:
		{
			if (debug_lvl > 0 && debug_m)
			{
				if (!tomine)
				{
					sint xc = bot_sprintf(nm->carr, nm->siz, "Log_%s", dat->carr);
				}
				else
				{
					sint xc = bot_sprintf(nm->carr, nm->siz, "Log_%s_%s", dat->carr, ptn.c_str());
				}
			}
			break;
		}
		case 1:
		{
			if (!tomine)
			{
				sint xc = bot_sprintf(nm->carr, nm->siz, "Error_Log_%s", dat->carr);
			}
			else
			{
				sint xc = bot_sprintf(nm->carr, nm->siz, "Error_Log_%s_%s", dat->carr, ptn.c_str());
			}
			break;
		}
		case 2:
		{
			if (!tomine)
			{
				sint xc = bot_sprintf(nm->carr, nm->siz, "Activity_Log_%s", dat->carr);
			}
			else
			{
				sint xc = bot_sprintf(nm->carr, nm->siz, "Activity_Log_%s_%s", dat->carr, ptn.c_str());
			}
			break;
		}
		case 3:
		{
			if (!tomine)
			{
				sint xc = bot_sprintf(nm->carr, nm->siz, "Maintenance_Log_%s", dat->carr);
			}
			else
			{
				sint xc = bot_sprintf(nm->carr, nm->siz, "Maintenance_Log_%s_%s", dat->carr, ptn.c_str());
			}
			break;
		}
		default:
		{
			return opt;
			break;
		}
		}
		return 0;
	}
	sint LogPut(c_char* msg_ = "", sint option = -1)
	{
		carr_32 dat;
		sint xc = GetDate(&dat, false);

		if (log_to[0])
		{
			carr_256 nam;
			xc = LogName(option, &nam, &dat);
			sint uc = UsingLog(nam.carr);
			std::string str;

			if (uc < 0)
			{
				BOT_LOGDET Current(nam.carr, dat.carr, option);
				uc = vtool.AddValToVec(&u_logs, &Current, true, true);

				if (uc < 0)
				{
					return -1;
				}
			}
			if (!u_logs[uc].log_q.empty())
			{
				if (BOT_DEBUG_M > 1)
				{
					str.append("[Q]");
					str.append(msg_);
					u_logs[uc].log_q.push_back(str);
				}
				return 0;
			}

			str.append(msg_);
			u_logs[uc].log_q.push_back(str);
			BOT_LOGDET_M Current_m(nam.carr, dat.carr, option);
			xc = GetInVec(&Current_m, MTX_LOG);

			if (xc < 0)
			{
				BOT_LOGDET Current(nam.carr, dat.carr, option);
				xc = GetInVec(&Current, MTX_LOG, true, false);

				if (xc < 0)
				{
					return -1;
				}
				xc = GetVecEle(&Current_m, MTX_LOG, xc);

				if (xc < 0)
				{
					return -1;
				}
			}
			xc = PushToVecEleMem((void*)&u_logs[uc].log_q, MTX_LOG, Current_m.lid, BOT_LOG_Q, 3, false);
			u_logs[uc].log_q.clear();
			//xc = vtool.CleanVec(&u_logs);
		}
		if (log_to[1])
		{
			carr_256 nam;
			xc = LogName(option, &nam, &dat, true);
			sint uc = UsingLog(nam.carr);
			std::string str;

			if (uc < 0)
			{
				BOT_LOGDET Current(nam.carr, dat.carr, option);
				uc = vtool.AddValToVec(&u_logs, &Current, true, true);

				if (uc < 0)
				{
					return -1;
				}
			}
			if (!u_logs[uc].log_q.empty())
			{
				if (BOT_DEBUG_M > 1)
				{
					str.append("[Q]");
					str.append(msg_);
					u_logs[uc].log_q.push_back(str);
				}
				return 0;
			}

			str.append(msg_);
			u_logs[uc].log_q.push_back(str);
			BOT_LOGDET_M Current_m(nam.carr, dat.carr, option);
			xc = GetInVec(&Current_m, MTX_LOG);

			if (xc < 0)
			{
				BOT_LOGDET Current(nam.carr, dat.carr, option);
				xc = GetInVec(&Current, MTX_LOG, true, false);

				if (xc < 0)
				{
					return -1;
				}
				xc = GetVecEle(&Current_m, MTX_LOG, xc);

				if (xc < 0)
				{
					return -1;
				}
			}
			xc = PushToVecEleMem((void*)&u_logs[uc].log_q, MTX_LOG, Current_m.lid, BOT_LOG_Q, 3, false);
			u_logs[uc].log_q.clear();
			//xc = vtool.CleanVec(&u_logs);
		}
		return 0;
	}
	
	// Commands
	sint Command(std::vector<std::string> *vec_ = 0)
	{
		if (!vec_)
		{
			return -1;
		}

		if (vec_->empty())
		{
			return -1;
		}
		BOTCOMMAND Command(Uppercase(vec_->at(0).c_str()).c_str());
		sint xc = GetCommand(&Command);

		if (Command.cmd_id < 0)
		{
			return -1;
		}

		if (debug_lvl >= 1 && debug_m)
		{
			std::string output;
			output.append("Finding Command by id: ");
			xc = Output(output.c_str(), 2);
		}

		xc = -1;

		switch (Command.cmd_id)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			sint oc = Output("Telling threads to finish", 2);
			oc = SetThreadQuit(1);
			break;
		}
		case 2:
		{
			sint oc = Output("Found BOTCOMMAND id 2", 2);
			xc = 0;
			break;
		}
		case 3:
		{
			sint oc = Output("Found BOTCOMMAND id 3", 2);

			if (strlen(vec_->at(1).c_str()))
			{
				debug_lvl = atoi(vec_->at(1).c_str());
				xc = 0;
			}
			break;
		}
		case 4:
		{
			sint oc = Output("Found BOTCOMMAND id 4", 2);
			xc = 0;
			break;
		}
		case 5:
		{
			if (vec_->size() > 2)
			{
				if (strlen(vec_->at(1).c_str()))
				{
					BOT_CLIENT ProcClient;
					std::string str;
					str.append(Uppercase(vec_->at(1).c_str()));
					sint rc = SetClientLoginName(&str);
					rc = GetLogin(vec_->at(2).c_str());
					vec_->at(2) = "";

					if (GetClientLoggedIn())
					{
						ProcClient.loggedin = true;
						ProcClient.lid = GetClientID();
						rc = GetClientName(&ProcClient.name);
						rc = GetClientLoginName(&ProcClient.login_name);
						ProcClient.nameset = true;
						ProcClient.priv = GetClientPriv();
						ProcClient.updatelogin = true;
						rc = GetClientLastLogin(&ProcClient.lastlogin);
						ProcClient.totallogins = GetClientTotalLogins() + 1;
						_char dated[128]{ 0 };
						rc = GetDateTime(dated);
						ProcClient.logindate.append(dated);
						rc = UpdateAccount(&ProcClient);
						ProcClient.updatelogin = false;
						rc = PushToVec((void*)&ProcClient, MTX_CV, true, true, false);
					}
					else
					{
						std::string output;
						output.append("incorrect login name and/or password");
						rc = Output(output.c_str(), 2);
						ProcClient.updatelogin = true;
						ProcClient.lid = GetClientID();
						ProcClient.login_name.append(Uppercase(vec_->at(1).c_str()));
						ProcClient.failed_logins = GetClientFailedLogins() + 1;
						_char dated[128]{ 0 };
						rc = GetDateTimeMS(dated);
						ProcClient.last_failed_login.append(dated);
						rc = UpdateAccount(&ProcClient);
					}
				}
				xc = 0;
			}

			break;
		}
		case 6:
		{
			for (sint x = 0; x < UINT_MAX; x++)
			{
				BOTCOMMAND Cmd("", x);
				xc = GetCommand(&Cmd);

				if (xc < 0)
				{
					x = UINT_MAX;
				}
				else
				{
					carr_128 ncar;
					sint oc = bot_sprintf(ncar.carr, ncar.siz, "%s %i", Cmd.cmd.c_str(), Cmd.cmd_id);
					oc = Output(ncar.carr, 0);
				}
			}
			break;
		}
		case 7:
		{
			if (vec_->size() > 3)
			{
				BOTCOMMAND Cmd(vec_->at(1).c_str());
				xc = GetCommand(&Cmd);

				if (xc > -1)
				{
					return -1;
				}
			}
			else
			{
				return 1;
			}

			BOT_STMT t(false, 2, "litebot", "COMMANDS", 1);
			sint rc = t.AddCol("COMMANDS", Uppercase(LEncStrI(vec_->at(1).c_str(), -1).c_str()).c_str());
			rc = t.AddCol("CMD_ID", vec_->at(2).c_str());
			rc = t.AddCol("PRIV", vec_->at(3).c_str());
			t.cspec = 2;
			std::vector<BOT_STMT> tvec;
			tvec.push_back(t);
			xc = Commit(&tvec);
			break;
		}
		default:
		{
			return 1;
			break;
		}
		}
		return 0;
	}

	// File Directory
	sint BOTPath(std::string* str_ = 0, c_char* spath_ = 0)
	{
		if (!str_)
		{
			return -1;
		}

		sint h = -1;
		sint p = LockGMutex(MTX_DMAP, &h);

		if (p > -1)
		{
			str_->append(bot_dmap.bot_home_path.c_str());

			if (spath_)
			{
				if (strlen(spath_) < 256)
				{
					str_->append(spath_);
				}
			}
			if (!h)
			{
				h = UnlockGMutex(MTX_DMAP);
			}
		}
		return 0;
	}
	sint BOTOpenDir(c_char* dest_ = 0, DIR** dir_ = 0)
	{
		if (!dest_ || !dir_)
		{
			return -1;
		}

		BOT_FILE_M xfile("", "", dest_, 0, BOT_DIR_CON);
		sint xc = BOTFileStats(&xfile);

		if (!xc)
		{
			if ((*dir_ = opendir(dest_)) != NULL)
			{
				return 0;
			}
		}
		return -1;
	}
	sint BOTCloseDir(DIR** dir_ = 0)
	{
		if (!*dir_)
		{
			return -1;
		}

		closedir(*dir_);
		return 0;
	}
	sint BOTReadDir(std::vector<BOT_FILE_M>* flds_ = 0, c_char* dest_ = 0)
	{
		if (!flds_ || !dest_)
		{
			return -1;
		}
		
		_char dmk = '\\';
		std::string dest;

		if (memcmp((void*)&dest_[strlen(dest_) - 1], (void*)&dmk, sizeof(dmk)))
		{
			dest.append(dest_);
			dest.push_back(dmk);
			dest_ = dest.c_str();
		}

		DIR* dir_ = 0;

		if (!BOTOpenDir(dest_, &dir_))
		{
			struct dirent* dp_ = 0;
			
			while ((dp_ = readdir(dir_)) != NULL)
			{
				std::vector<std::string> cvec = BOT_NOFLD_V;
				uint x = 0;

				while (x < cvec.size())
				{
					uint xcmp = 0;

					while (xcmp < cvec[x].length() && xcmp < strlen(dp_->d_name))
					{
						if (memcmp((void*)&cvec[x][xcmp], (void*)&dp_->d_name[xcmp], sizeof(dp_->d_name[xcmp])))
						{
							xcmp = cvec[x].length();
						}
						xcmp++;
					}

					if (xcmp == cvec[x].length())
					{
						x = cvec.size();
					}
					x++;
				}

				if (x == cvec.size())
				{
					BOT_FILE_M xfile(dp_->d_name, "", dest_, 0);
					sint xc = BOTFileStats(&xfile, BOT_DIRSCAN_LVL);

					if (!xc)
					{
						if (S_ISDIR(xfile.fst.filestats.st_mode))
						{
							xc = vtool.AddValToVec(flds_, &xfile, true, true);
						}
					}
				}
			}
			sint xc = BOTCloseDir(&dir_);
			return xc;
		}
		return -1;
	}
	sint BOTFindHomeDir()
	{
		if (debug_lvl >= 1 && debug_m)
		{
			sint oc = Output("::BOTFindHomeDir()", 2);
		}

		_char crf[128]{ 0 };
		sint xc = bot_randstr(crf, 128);

		if (xc)
		{
			return -1;
		}

		sint of = -1;
		BOT_FILE_M hmdir(crf, "", "", 0, BOT_DIR_CON);
		xc = BOTOpenFile(&hmdir, &of, true);

		if (xc < 0)
		{
			return -1;
		}

		sint h = -1;
		sint p = LockGMutex(MTX_DMAP, &h);

		if (p > -1)
		{
			for (uint x = 0; x < bot_dmap.drvs.size(); x++)
			{
				if (strlen(bot_dmap.drvs[x].drv.c_str()) < 256)
				{
					std::vector<BOT_FILE_M> ndrcs;
					std::string fdir;
					fdir.append(bot_dmap.drvs[x].drv.c_str());

					if (!BOTReadDir(&ndrcs, fdir.c_str()))
					{
						for (uint y = 0; y < ndrcs.size(); y++)
						{
							if (!strcmp(ndrcs[y].name.c_str(), crf))
							{
								bot_dmap.bot_home_path.clear();
								bot_dmap.bot_home_path.append(fdir.c_str());

								if (!of)
								{
									xc = BOTCloseFile(&ndrcs[y], true, true);
								}

								if (!h)
								{
									p = UnlockGMutex(MTX_DMAP);
								}
								return 0;
							}
						}
					}
					if (!ndrcs.empty())
					{
						for (uint y = 0; y < ndrcs.size(); y++)
						{
							std::vector<std::string> pvec;
							sllint val = ndrcs[y].bto;

							while (val > -1)
							{
								pvec.push_back(ndrcs[(size_t)val].name);
								val = ndrcs[(size_t)val].bto;
							}

							for (val = (sllint)pvec.size() - 1; val > -1; val--)
							{
								fdir.append(pvec[(size_t)val].c_str());
								fdir.push_back('\\');
							}

							fdir.append(ndrcs[y].name.c_str());
							fdir.push_back('\\');
							size_t bsiz = ndrcs.size();

							if (!BOTReadDir(&ndrcs, fdir.c_str()))
							{
								for (uint z = bsiz; z < ndrcs.size(); z++)
								{
									if (!strcmp(ndrcs[z].name.c_str(), crf))
									{
										bot_dmap.bot_home_path.clear();
										bot_dmap.bot_home_path.append(fdir.c_str());
										cur_path.clear();
										cur_path.append(fdir.c_str());
										hmdir.path.append(cur_path.c_str());

										if (!of)
										{
											xc = BOTCloseFile(&hmdir, true, true);

											if (xc)
											{
												xc = -1;
											}
										}

										if (!h)
										{
											p = UnlockGMutex(MTX_DMAP);
										}
										return 0;
									}
									ndrcs[z].bto = (sllint)y;
								}
							}

							fdir.pop_back();

							for (uint z = 0; z < ndrcs[y].name.length(); z++)
							{
								fdir.pop_back();
							}

							for (uint z = 0; z < pvec.size(); z++)
							{
								fdir.pop_back();
								fdir.erase(fdir.length() - pvec[z].length(), pvec[z].length());
							}
						}
					}
				}
			}
			if (!h)
			{
				p = UnlockGMutex(MTX_DMAP);
			}
		}
		return -1;
	}
	sint BOTInitFDir(bool findself = true)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTInitFDir(bool findself(%u))", (uint)findself);
			oc = Output(ncar.carr, 2);
		}
		
		_char crf[128]{ 0 };

		if (findself)
		{
			sint xc = bot_randstr(crf, 128);

			if (xc)
			{
				xc = -1;
				return -1;
			}
#ifdef _WIN32
			xc = _mkdir(crf);
#else
			
			xc = mkdir(crf, S_IFDIR);
#endif
			if (xc)
			{
				return -1;
			}
		}

		sint h = -1;
		sint p = LockGMutex(MTX_DMAP, &h);

		if (p > -1)
		{
			for (uint x = 0; x < bot_dmap.drvs.size(); x++)
			{
				if (strlen(bot_dmap.drvs[x].drv.c_str()) < 256)
				{
					struct dirent *dp;
					std::string fdir;
					fdir.append(bot_dmap.drvs[x].drv.c_str());
					DIR *ndir = NULL;

					if ((ndir = opendir(fdir.c_str())) != NULL)
					{
						while ((dp = readdir(ndir)) != NULL)
						{
							std::string fldstr;
							fldstr.append(fdir.c_str());
							fldstr.append(dp->d_name);
							fldstr.push_back('\\');

#ifdef _WIN32
							struct _stat dstat;
							sint xc = _stat(fldstr.c_str(), &dstat);
#else
							struct stat dstat;
							sint xc = stat(fldstr.c_str(), &dstat);
#endif

							if (!xc)
							{
								if (S_ISDIR(dstat.st_mode))
								{
									if (findself && !strcmp(crf, dp->d_name))
									{
										bot_dmap.bot_home_path.clear();
										bot_dmap.bot_home_path.append(fdir.c_str());
#ifdef _WIN32
										xc = _rmdir(fldstr.c_str());
#else
										xc = rmdir(fldstr.c_str());
#endif
									}
									else
									{
										std::vector<std::string> nvec = BOT_NOFLD_V;
										uint cmp = 0;

										while (cmp < nvec.size())
										{
											if (nvec[cmp].length() == strlen(dp->d_name))
											{
												uint xcmp = 0;

												while (xcmp < nvec[cmp].length())
												{
													if (memcmp((void*)&nvec[cmp][xcmp], (void*)&dp->d_name[xcmp], 1))
													{
														xcmp = nvec[cmp].length();
													}
													xcmp++;
												}

												if (xcmp == nvec[cmp].length())
												{
													cmp = nvec.size();
												}
											}
											cmp++;
										}

										if (cmp == nvec.size())
										{
											BOT_FLD nfld(dp->d_name, (sllint)bot_dmap.drvs[x].flds.size());
											xc = bot_dmap.drvs[x].BOTAddFolder(&nfld);
										}
									}
								}
							}
						}

						closedir(ndir);

						if (!bot_dmap.drvs[x].flds.empty())
						{
							bool done = false;

							for (uint ct = 0; ct < bot_dmap.drvs[x].flds.size() && !done; ct++)
							{
								ndir = NULL;
								fdir.clear();
								fdir.append(bot_dmap.drvs[x].drv.c_str());
								std::vector<std::string> pvec;
								sllint val = bot_dmap.drvs[x].flds[ct].bto;

								while (val > -1)
								{
									pvec.push_back(bot_dmap.drvs[x].flds[(size_t)val].fld);
									val = bot_dmap.drvs[x].flds[(size_t)val].bto;
								}

								for (val = (sllint)pvec.size() - 1; val > -1; val--)
								{
									fdir.append(pvec[(size_t)val].c_str());
									fdir.push_back('\\');
								}

								fdir.append(bot_dmap.drvs[x].flds[ct].fld.c_str());
								fdir.push_back('\\');

								if ((ndir = opendir(fdir.c_str())) != NULL)
								{
									while ((dp = readdir(ndir)) != NULL)
									{
										std::string fldstr;
										fldstr.append(fdir.c_str());
										fldstr.append(dp->d_name);
										fldstr.push_back('\\');

#ifdef _WIN32
										struct _stat dstat;
										sint xc = _stat(fldstr.c_str(), &dstat);
#else
										struct stat dstat;
										sint xc = stat(fldstr.c_str(), &dstat);
#endif

										if (!xc)
										{
											if (S_ISDIR(dstat.st_mode))
											{
												if (findself && !strcmp(crf, dp->d_name))
												{
													bot_dmap.bot_home_path.clear();
													bot_dmap.bot_home_path.append(fdir.c_str());
#ifdef _WIN32
													xc = _rmdir(fldstr.c_str());
#else
													xc = rmdir(fldstr.c_str());
#endif
													done = true;
												}
												else
												{
													std::vector<std::string> nvec = BOT_NOFLD_V;
													uint cmp = 0;

													while (cmp < nvec.size())
													{
														uint xcmp = 0;

														while (xcmp < nvec[cmp].length())
														{
															if (memcmp((void*)&nvec[cmp][xcmp], (void*)&dp->d_name[xcmp], 1))
															{
																xcmp = nvec[cmp].length();
															}
															xcmp++;
														}

														if (xcmp == nvec[cmp].length())
														{
															cmp = nvec.size();
														}
														cmp++;
													}

													if (cmp == nvec.size())
													{
														BOT_FLD nfld(dp->d_name, (sllint)bot_dmap.drvs[x].flds.size(), false, bot_dmap.drvs[x].flds[ct].fid, bot_dmap.drvs[x].flds[ct].ord + 1);
														xc = bot_dmap.drvs[x].BOTAddFolder(&nfld);
													}
												}
											}
										}
									}
								}
							}

							std::vector<BOT_FLD> nvec;

							for (uint y = 0; y < bot_dmap.drvs[x].flds.size(); y++)
							{
								if (bot_dmap.drvs[x].flds[y].ord < 0 || bot_dmap.drvs[x].flds[y].is_home)
								{
									nvec.push_back(bot_dmap.drvs[x].flds[y]);
								}
							}

							bot_dmap.drvs[x].flds.clear();

							for (uint y = 0; y < nvec.size(); y++)
							{
								bot_dmap.drvs[x].flds.push_back(nvec[y]);
							}
						}
					}
				}
			}
			if (!h)
			{
				p = UnlockGMutex(MTX_DMAP);
			}
		}
		return 0;
	}

	// File I/O

	sint OutputFileStats(BOT_FILE* file_, sint opt)
	{
		if (!file_)
		{
			return -1;
		}
		struct tm atim;
		struct tm mtim;
		struct tm ctim;
		_char atdata[64] = { 0 };
		_char mtdata[64] = { 0 };
		_char ctdata[64] = { 0 };
		std::string fpstr;

		if (strlen(file_->path.c_str()) > 512)
		{
			sint f = file_->path.find('\\', (file_->path.length() - 512));

			if (f > -1)
			{
				fpstr.append("..\\");

				while (f < (sint)file_->path.length())
				{
					fpstr.push_back(file_->path[f]);
					f++;
				}
			}
			else
			{
				fpstr.append("filename too long to output: ");
				fpstr.append(stool.ITOA((sint)strlen(file_->name.c_str())));
			}
		}
		else
		{
			fpstr.append(file_->path);
		}
#ifdef _WIN32
		errno_t aerr = gmtime_s(&atim, &file_->fst.filestats.st_atime);
		errno_t merr = gmtime_s(&mtim, &file_->fst.filestats.st_mtime);
		errno_t cerr = gmtime_s(&ctim, &file_->fst.filestats.st_ctime);
#else
		atim = *gmtime((time_t*)&file_->fst.filestats.st_atime);
		mtim = *gmtime((time_t*)&file_->fst.filestats.st_mtime);
		ctim = *gmtime((time_t*)&file_->fst.filestats.st_ctime);
#endif
		strftime(atdata, 64, "%m/%d/%Y %H:%M:%S", &atim);
		strftime(mtdata, 64, "%m/%d/%Y %H:%M:%S", &mtim);
		strftime(ctdata, 64, "%m/%d/%Y %H:%M:%S", &ctim);
		_char instr[BOT_FILENAME_MAX + 1024] = { 0 };
		sint oc = bot_sprintf(instr, BOT_FILENAME_MAX + 1024, "BOTFileStats:%s%s\nFilePath:\"%s\"\nSize:%llu\nSerialNum:%u\nLastAccessed:%s\nLastMod:%s\nLastChangeStatus:%s\nExists:%i", file_->name.c_str(), file_->type.c_str(), fpstr.c_str(), (ullint)file_->fst.filestats.st_size, file_->fst.filestats.st_ino, atdata, mtdata, ctdata, file_->fst.exists);
		oc = Output(instr, 2);
		return 0;
	}
	sint BOTFileStr(std::string* str_ = 0, BOT_FILE_M* file_ = 0)
	{
		if (!str_ || !file_)
		{
			return -1;
		}

		_char dmk = '\\';
		_char term = '.';

		if (!file_->path.empty())
		{
			for (uint gc = file_->path.length() - 1; gc > -1; gc--)
			{
				if (!memcmp((void*)&file_->path[gc], (void*)&dmk, sizeof(dmk)))
				{
					uint alen = file_->path.length() - gc;

					if (alen)
					{
						if (file_->name.empty())
						{
							file_->name.append(file_->path.substr(gc, alen).c_str());

							if (file_->lid > -1)
							{
								sint ret = SetVecEleMem((void*)file_->name.c_str(), MTX_FO, file_->lid, BOT_FS_NAME, false);
							}
						}

						file_->path.erase(gc, alen);

						if (file_->lid > -1)
						{
							sint ret = SetVecEleMem((void*)file_->path.c_str(), MTX_FO, file_->lid, BOT_FS_FP, false);
						}
					}
					gc = 0;
				}
			}

			if (file_->path.length() > 1)
			{
				if (memcmp((void*)&file_->path[file_->path.length() - 1], (void*)&dmk, sizeof(dmk)))
				{
					file_->path.push_back(dmk);

					if (file_->lid > -1)
					{
						sint ret = SetVecEleMem((void*)file_->path.c_str(), MTX_FO, file_->lid, BOT_FS_FP, false);
					}
				}
			}
			else if (!file_->path.empty())
			{
				file_->path.clear();

				if (file_->lid > -1)
				{
					sint ret = SetVecEleMem((void*)file_->path.c_str(), MTX_FO, file_->lid, BOT_FS_FP, false);
				}
			}
			else {}
		}

		if (!file_->name.empty())
		{
			for (uint gc = file_->name.length() - 1; gc; gc--)
			{
				bool fterm = false;

				if (!memcmp((void*)&file_->name[gc], (void*)&term, sizeof(term)) && fterm && file_->cm != BOT_DIR_CON)
				{
					uint alen = file_->name.length() - gc;

					if (alen)
					{
						if (file_->type.empty())
						{
							file_->type.append(file_->name.substr(gc, alen).c_str());

							if (file_->lid > -1)
							{
								sint ret = SetVecEleMem((void*)file_->type.c_str(), MTX_FO, file_->lid, BOT_FS_FT, false);
							}
						}

						file_->name.erase(gc, alen);

						if (file_->lid > -1)
						{
							sint ret = SetVecEleMem((void*)file_->name.c_str(), MTX_FO, file_->lid, BOT_FS_NAME, false);
						}
					}
					fterm = true;
				}
				else if (!memcmp((void*)&file_->name[gc], (void*)&dmk, sizeof(dmk)))
				{
					if (!file_->type.empty() && !fterm)
					{
						file_->type.clear();

						if (file_->lid > -1)
						{
							sint ret = SetVecEleMem((void*)file_->type.c_str(), MTX_FO, file_->lid, BOT_FS_FT, false);
						}
					}

					if (file_->path.empty() && gc)
					{
						file_->path.append(file_->name.substr(0, gc + 1).c_str());

						if (file_->lid > -1)
						{
							sint ret = SetVecEleMem((void*)file_->path.c_str(), MTX_FO, file_->lid, BOT_FS_FP, false);
						}
					}
					gc = 0;
				}
				else {}
			}
		}

		sint ret = 0;

		if (!file_->path.empty())
		{
			str_->append(file_->path.c_str());
		}
		else
		{
			if (!cur_path.empty())
			{
				str_->append(cur_path.c_str());
			}
			else
			{
				ret = BOTPath(str_);
			}
		}

		if (!file_->name.empty())
		{
			str_->append(file_->name.c_str());
		}

		if (!file_->type.empty())
		{
			str_->append(file_->type);
		}
		return ret;
	}
	sint BOTConnMethod(BOT_FILE_M* val_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTConnMethod(BOT_FILE_M *val_(%i))", (sint)val_);
			oc = Output(ncar.carr, 2);
		}

		if (!val_)
		{
			return -1;
		}

		if (val_->type.empty())
		{
			val_->cm = BOT_DIR_CON;
			return 0;
		}
		if (val_->type.length() < 2)
		{
			return -1;
		}

		if (!strcmp(val_->type.c_str(), ".db"))
		{
			val_->cm = BOT_DB_CON;
		}
		else
		{
			val_->cm = BOT_F_CON;
		}
		return 0;
	}
	sint GetOFConn(BOT_FILE_M* val_ = 0, sint* was_open = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_96 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::GetOFConn(BOT_FILE_M *val_(%i), sint* was_open(%i))", (sint)val_, sint(was_open));
			oc = Output(ncar.carr, 2);
		}

		if (!val_)
		{
			return -1;
		}
		switch (val_->cm)
		{
		case BOT_DB_CON:
		{
			BOT_DB_M ndb(val_->name.c_str());
			return GetODBConn(&ndb);
			break;
		}
		case BOT_F_CON:
		{
			for (sint siz = 0; siz < (sint)f_con.size(); siz++)
			{
				if (f_con[siz])
				{
					if (f_con[siz]->flid == val_->lid)
					{
						if (val_->omode > -1)
						{
							if (f_con[siz]->omode == val_->omode)
							{
								val_->fcon = siz;
								return siz;
							}
						}
						else
						{
							val_->fcon = siz;
							return siz;
						}
					}
				}
			}
		}
		default:
		{
			break;
		}
		}
		return -1;
	}
	sint GetFConn(BOT_FILE_M* val_ = 0, sint* was_open = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_96 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::GetFConn(BOT_FILE_M *val_(%i)), sint* was_open(%i))", (sint)val_, sint(was_open));
			oc = Output(ncar.carr, 2);
		}

		if (!val_)
		{
			return -1;
		}

		if (val_->omode < 0)
		{
			return -1;
		}
		sint ret = -1;
		
		if (val_->cm < 0)
		{
			ret = BOTConnMethod(val_);

			if (ret < 0)
			{
				return -1;
			}

			ret = SetVecEleMem((void*)&val_->cm, MTX_FO, val_->lid, BOT_FS_CM, false);
		}

		ret = GetOFConn(val_, was_open);

		if (ret < 0)
		{
			if (was_open)
			{
				*was_open = 0;
			}

			switch (val_->cm)
			{
			case BOT_DIR_CON:
			{
				ret = 0;
				break;
			}
			case BOT_DB_CON:
			{
				BOT_DB_M ndb(val_->name.c_str());
				ndb.omode = val_->omode;
				ret = GetDBConn(&ndb);
				break;
			}
			case BOT_F_CON:
			{
				sint h = -1;
				sint p = LockGMutex(MTX_FCON, &h);

				if (p > -1)
				{
					for (sint siz = 0; siz < BOT_FO_MAX; siz++)
					{
						sint xh = -1;
						sint xc = LockElement(MTX_FCON, siz, &xh, false, false);

						if (!xc)
						{
							ret = vtool.AddValToVec(&f_con, &FCON[siz], true, true);

							if (ret > -1)
							{
								f_con[ret]->Renew(val_, siz);
								xc = SetVecEleMem((void*)&ret, MTX_FO, val_->lid, BOT_FS_FCON, false);
								val_->fcon = ret;
							}
							else
							{
								if (!xh)
								{
									xc = UnlockElement(MTX_FCON, siz, false);
								}
							}
							siz = BOT_FO_MAX;
						}
					}

					if (!h)
					{
						h = UnlockGMutex(MTX_FCON);
					}
					break;
				}
			}
			default:
			{
				break;
			}
			}
		}
		else
		{
			if (was_open)
			{
				*was_open = 1;
			}
		}
		return ret;
	}
	sint CloseFConn(BOT_FILE_M* xfile_ = 0, bool clear_conn = true)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_96 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::CloseFConn(BOT_FILE_M *xfile_(%i), bool clear_conn(%u))", (sint)xfile_, (uint)clear_conn);
			oc = Output(ncar.carr, 2);
		}

		if (!xfile_)
		{
			return -1;
		}

		sint ret = GetOFConn(xfile_);

		switch (xfile_->cm)
		{
		case BOT_DB_CON:
		{
			BOT_DB_M ndb(xfile_->name.c_str(), -1, xfile_->omode);
			sint x = 1;
			ret = CloseDB(&ndb, &x);
			break;
		}
		case BOT_F_CON:
		{
			if (ret > -1 && ret < (sint)f_con.size())
			{
				if (clear_conn)
				{
					f_con[ret]->Clear();
					ret = UnlockElement(MTX_FCON, ret, false);
					f_con[ret] = 0;
					ret = vtool.CleanVec(&f_con);
				}
				else
				{
					if (f_con[ret]->fstrm.is_open())
					{
						f_con[ret]->fstrm.close();
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
		return ret;
	}
	sint BOTScanFileSyms(BOT_FILE_M *file_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTScanFileSyms(BOT_FILE_M *file_(%i))", (sint)file_);
			oc = Output(ncar.carr, 2);
		}

		if (!file_)
		{
			return -1;
		}

		sint sv_mth = -1;
		sint ret = -1;

		if (S_ISDIR(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISREG(file_->fst.filestats.st_mode))
		{
			if (file_->cm)
			{
				sv_mth = file_->cm;
				file_->cm = 0;
			}
			ret = GetFConn(file_);

			if (ret > -1)
			{
				std::string str;
				ret = BOTFileStr(&str, file_);
				boto_file = true;
				ret = UpdMTXPrio();
				f_con[file_->fcon]->fstrm.open(str.c_str(), BOT_FILE_READ);

				if (f_con[file_->fcon]->fstrm.is_open())
				{
					ret = -1;
					ullint nuchar;
					f_con[file_->fcon]->fstrm.seekg(file_->fst.ia_loc);
					ullint term = (ullint)'\0';
					ullint lterm = (ullint)'\n';
					ullint loc = 0;
					ullint lin = 0;
					ullint linloc = 0;

					while (f_con[file_->fcon]->fstrm.get(*(_char*)&nuchar) && loc < file_->fst.e_loc && loc < (ullint)BOT_FSCAN_LIM)
					{
						file_->fst.IncrCts(&nuchar, loc, lin, linloc);
						linloc++;

						if (!memcmp((void*)&lterm, (void*)&nuchar, sizeof(lterm)))
						{
							linloc = 0;
							lin++;
						}
						loc++;
					}
					f_con[file_->fcon]->fstrm.close();
				}
				else
				{
					boto_file = false;
					ret = UpdMTXPrio();
					return -1;
				}
				boto_file = false;
				ret = UpdMTXPrio();
				ret = CloseFConn(file_, true);
			}
			if (sv_mth > -1)
			{
				file_->cm = sv_mth;
			}
		}
		else if (S_ISBLK(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISLNK(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISFIFO(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISCHR(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISSOCK(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else {}
		return ret;
	}
	sint DetSep(BOT_FILE_M* file_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::DetSep(BOT_FILE_M *file_(%i))", (sint)file_);
			oc = Output(ncar.carr, 2);
		}
		if (!file_)
		{
			return -1;
		}

		if (file_->fst.compv.empty())
		{
			return -1;
		}

		size_t insiz = file_->fst.seps.size();
		std::vector<ullint> res;
		std::vector<uint> res_e;

		for (uint x = 0; x < file_->fst.compv.size(); x++)
		{
			uint a = 0;
			uint b = 0;
			uint c = 0;
			uint d = 0;
			uint e = 0;
			uint f = 0;
			uint g = 0;
			uint y = 0;

			while (y < file_->fst.compv.size())
			{
				if (x != y)
				{
					if (!g)
					{
						if (file_->fst.cts[x] != file_->fst.cts[y])
						{
							if (!f)
							{
								f++;
							}
						}
						else
						{
							if (y > x)
							{
								if (file_->fst.mean_loc[x] > file_->fst.mean_loc[y])
								{
									g++;
								}
							}
							else
							{
								if (file_->fst.mean_loc[y] > file_->fst.mean_loc[x])
								{
									g++;
								}
							}
						}
					}

					if (!a)
					{
						if (abs((sllint)file_->fst.mean_spc[x] - (sllint)file_->fst.med_spc[x]) > abs((sllint)file_->fst.mean_spc[y] - (sllint)file_->fst.med_spc[y]))
						{
							a++;
						}
					}

					if (!b)
					{
						if (abs((sllint)file_->fst.mean_linct[x] - (sllint)file_->fst.med_linct[x]) > abs((sllint)file_->fst.mean_linct[y] - (sllint)file_->fst.med_linct[y]))
						{
							b++;
						}
					}

					if (!c)
					{
						if (file_->fst.mean_linct_var[x] && file_->fst.mean_linct_var[x] > file_->fst.mean_linct_var[y])
						{
							/* if our file containts formatted strings with a defined separator we should see a lower incidence of variation in count per line
							in its' constituent symbols, and their avg locs in line should have a low variation or avg spacing should have low variation */

							c++;
						}
					}

					if (!d)
					{
						if (file_->fst.mean_linl_var[x] && file_->fst.mean_linl_var[x] > file_->fst.mean_linl_var[y])
						{
							d++;
						}
					}

					if (!e)
					{
						if (file_->fst.mean_lens_var[x])
						{
							e++;
						}
					}

					if (a && b && c && d && e && f && g)
					{
						y = file_->fst.compv.size();
					}
				}
				y++;
			}

			ullint nres = (7 - (a + b + c + d + e + f + g));
			y = 0;

			while (y < res.size())
			{
				if (nres > res[y])
				{
					uint eres = x;
					ullint xval = res[y];
					uint eval = res_e[y];
					res[y] = nres;
					res_e[y] = eres;

					for (uint z = y + 1; z < res.size(); z++)
					{
						nres = res[z];
						eres = res_e[z];
						res[z] = xval;
						res_e[z] = eval;
						xval = nres;
						eval = eres;
					}

					res.push_back(nres);
					res_e.push_back(eres);
					y = res.size();
				}
				y++;
			}
			if (y == res.size())
			{
				res.push_back(nres);
				res_e.push_back(x);
			}
		}

		if (res.size() == 1)
		{
			u_char nuchar;
			memcpy((void*)&nuchar, (void*)&file_->fst.compv[res_e[0]], sizeof(nuchar));
			MACSYM nsym(3, &nuchar, file_->encode);
			file_->fst.seps.push_back(nsym);
		}
		else
		{
			std::vector<ullint> cons;

			for (uint x = 0; x < res.size(); x++)
			{
				ullint xloc = file_->fst.mean_loc[res_e[x]] + 1;

				if (x)
				{
					uint rval = (ullint)((float)res[0] / 2.0f);

					if (res[x] >= rval)
					{
						sint ret = vtool.ValInVec(&file_->fst.mean_loc, xloc);

						while (ret > -1)
						{
							if (ret != (sint)res_e[x])
							{
								if (file_->fst.cts[ret] <= file_->fst.cts[res_e[x]] + 1 && file_->fst.cts[ret] >= file_->fst.cts[res_e[x]] - 1)
								{
									cons.push_back(file_->fst.compv[res_e[x]]);
									xloc++;
									ret = vtool.ValInVec(&file_->fst.mean_loc, xloc);
								}
								else
								{
									ret = -1;
								}
							}
						}

						if (!cons.empty())
						{
							u_char* nuchar = (u_char*)malloc(cons.size() + 1);

							if (nuchar)
							{
								u_char term = (u_char)'\0';
								uint y = 0;

								while (y < cons.size())
								{
									memcpy((void*)&nuchar[y], (void*)&cons[y], sizeof(nuchar[y]));
									y++;
								}
								memcpy((void*)&nuchar[y], (void*)&term, sizeof(nuchar[y]));
								MACSYM nsym(3, nuchar, file_->encode);
								file_->fst.seps.push_back(nsym);
								cons.clear();
							}
							free(nuchar);
						}
					}
				}
				else
				{
					cons.push_back(file_->fst.compv[res_e[x]]);
					xloc++;
				}

				if (!cons.empty())
				{
					u_char* nuchar = (u_char*)malloc(cons.size() + 1);

					if (nuchar)
					{
						u_char term = (u_char)'\0';
						uint y = 0;

						while (y < cons.size())
						{
							memcpy((void*)&nuchar[y], (void*)&cons[y], sizeof(nuchar[y]));
							y++;
						}
						memcpy((void*)&nuchar[y], (void*)&term, sizeof(nuchar[y]));
						MACSYM nsym(3, nuchar, file_->encode);
						file_->fst.seps.push_back(nsym);
						cons.clear();
					}
					free(nuchar);
					cons.clear();
				}
			}
		}

		if (file_->fst.seps.size() != insiz)
		{
			sint ret = SetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE, false);
			return 0;
		}
		return -1;
	}
	sint BOTRendFileSyms(BOT_FILE_M *file_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTRendFileSyms(BOT_FILE_M *file_(%i))", (sint)file_);
			oc = Output(ncar.carr, 2);
		}
		if (!file_)
		{
			return -1;
		}

		
		sint ret = -1;

		if (S_ISDIR(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISREG(file_->fst.filestats.st_mode))
		{
			sint sv_mth = -1;

			if (file_->cm)
			{
				sv_mth = file_->cm;
				file_->cm = 0;
			}
			ret = GetFConn(file_);

			if (ret > -1)
			{
				std::string str;
				ret = BOTFileStr(&str, file_);
				boto_file = true;
				ret = UpdMTXPrio();
				f_con[file_->fcon]->fstrm.open(str.c_str(), BOT_FILE_READ);

				if (f_con[file_->fcon]->fstrm.is_open())
				{
					std::vector<MACSYM> svec;
					ullint siz = file_->fst.e_loc - file_->fst.ia_loc;
					ullint nuchar = 0;
					f_con[file_->fcon]->fstrm.seekg(file_->fst.ia_loc);
					ullint term = (ullint)'\0';
					ullint loc = 0;
					std::vector<ullint> uv;
					std::vector<uint> mat_ele;
					std::vector<uint> loc_in_sym;

					while (f_con[file_->fcon]->fstrm.get(*(_char*)&nuchar) && loc < siz)
					{
						uv.push_back(nuchar);

						for (size_t x = 0; x < file_->fst.seps.size(); x++)
						{
							if (!memcmp((void*)&file_->fst.seps[x].cons[0].sym, (void*)&nuchar, sizeof(nuchar)))
							{
								if (file_->fst.e_loc - loc > file_->fst.seps[x].cons.size())
								{
									mat_ele.push_back(x);
									loc_in_sym.push_back(0);
								}
							}
							else
							{
								if (!mat_ele.empty())
								{
									for (uint y = 0; y < mat_ele.size(); y++)
									{
										loc_in_sym[y]++;

										if (loc_in_sym[y] < file_->fst.seps[mat_ele[y]].cons.size())
										{
											if (memcmp((void*)&file_->fst.seps[mat_ele[y]].cons[loc_in_sym[y]], (void*)&nuchar, sizeof(nuchar)))
											{
												for (uint z = y + 1; z < mat_ele.size(); z++)
												{
													mat_ele[z - 1] = mat_ele[z];
													loc_in_sym[z - 1] = loc_in_sym[z];
												}
												mat_ele.pop_back();
												loc_in_sym.pop_back();
											}
										}
										else
										{
											u_char* xchar = (u_char*)malloc(uv.size() + 1);

											if (xchar)
											{
												for (uint z = 0; z < uv.size(); z++)
												{
													memcpy((void*)&xchar[z], (void*)&uv[z], sizeof(xchar[z]));
												}
												memcpy((void*)&xchar[uv.size()], (void*)&term, sizeof(xchar[uv.size()]));
												MACSYM nsym(1, xchar, file_->encode);
												svec.push_back(nsym);
											}
											free(xchar);
											uv.clear();
											svec.push_back(file_->fst.seps[mat_ele[y]]);
										}
									}
								}
							}
						}
						loc++;
					}
					f_con[file_->fcon]->fstrm.close();

					if (!svec.empty())
					{
						ret = AddCode(&svec);
					}
				}
				else
				{
					boto_file = false;
					ret = UpdMTXPrio();
					return -1;
				}
				boto_file = false;
				ret = UpdMTXPrio();
				ret = CloseFConn(file_, true);
			}
			if (sv_mth > -1)
			{
				file_->cm = sv_mth;
			}
		}
		else if (S_ISBLK(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISLNK(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISFIFO(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISCHR(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else if (S_ISSOCK(file_->fst.filestats.st_mode))
		{
			ret = 0;
		}
		else {}
		return ret;
	}
	sint BOTKnownFormat(BOT_FILE_M* file_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTKnownFormat(BOT_FILE_M* file_(%i))", (sint)file_);
			oc = Output(ncar.carr, 2);
		}

		if (!file_)
		{
			return -1;
		}

		MACSYM in_sym;
		BOT_STMT t(false, 0, "code", "filetype", 1, (void*)&in_sym);
		sint ret = t.AddCond(0, "DATA", sql_comp_keywords[5], file_->type.c_str());
		ret = BOTFileIN(-1, -1, -1, BOT_RTV_MACS, &t, BOT_RTV_MAX);

		if (ret > -1)
		{
			if (in_sym.cons.empty())
			{
				in_sym.Renew(5, (u_char*)file_->type.c_str(), file_->encode);
			}
			

			ret = AddCode(&in_sym);


		}
		return 1;
	}
	sint BOTFileStats(BOT_FILE_M *file_ = 0, sint scan_lvl = BOT_FSCAN_LVL)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_96 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileStats(BOT_FILE_M *file_(%i), sint scan_lvl(%i))", (sint)file_, scan_lvl);
			oc = Output(ncar.carr, 2);

			if (debug_lvl >= 10)
			{
				std::string xcar;
				oc = bot_sprintfs(&xcar, false, "%s%s%s", file_->path.c_str(), file_->name.c_str(), file_->type.c_str());
				oc = Output(xcar.c_str(), 2);
			}
		}
		if (!file_)
		{
			return -1;
		}

		std::string str;
		sint ret = BOTFileStr(&str, file_);

		if (file_->cm < 0)
		{
			ret = BOTConnMethod(file_);
		}

#ifdef _WIN32
		struct _stat nstat;
		ret = _stat(str.c_str(), &nstat);
#else
		struct stat nstat;
		ret = stat(str.c_str(), &nstat);
#endif
		if (!ret)
		{
			ret = file_->fst.cmpstats(&nstat);

			if (ret > -1)
			{
				switch (ret)
				{
				case 103:
				{
					// change to time of last access
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 104:
				{
					// change to time of last status change
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 105:
				{
					// change to device id
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 106:
				{
					// change to file serial number
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 107:
				{
					// change to mode
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 108:
				{
					// change to date of last modificatino
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 109:
				{
					// change to number of hd links to file
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 110:
				{
					// change to device id if file is 
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 111:
				{
					// change to size in bytes
					file_->fst.RenewStats(&nstat);
					break;
				}
				case 112:
				{
					// change to user id of file
					file_->fst.RenewStats(&nstat);
					break;
				}
				default:
				{
					break;
				}
				}
				file_->fst.exists = 1;
				ret = SetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE, false);
			}

			if (file_->cm == BOT_DIR_CON)
			{

				return 0;
			}
			if (scan_lvl)
			{
				if ((ullint)nstat.st_size > (ullint)BOT_STRLEN_MAX && scan_lvl > 1)
				{
					std::vector<TINFO_M> tvec;
					ullint x = (ullint)BOT_STRLEN_MAX;
					ullint last_x = 0;

					while (x < (ullint)nstat.st_size)
					{
						if ((ullint)nstat.st_size < (ullint)BOT_STRLEN_MAX)
						{
							x = (ullint)nstat.st_size;
						}

						std::vector<ullint> nvals{ (ullint)file_->lid, (ullint)file_->encode, last_x, x };
						TINFO_M nt(1, "ScanFileThread", ScanFileThread, lid, 0.0f, &nvals);
						tvec.push_back(nt);
						last_x = x;

						if (x + (ullint)BOT_STRLEN_MAX > (ullint)nstat.st_size)
						{
							x = (ullint)nstat.st_size;
						}
						else
						{
							x += (ullint)BOT_STRLEN_MAX;
						}
					}

					sint xret = HasLock(MTX_FO, file_->lid);

					if (!xret)
					{
						ret = UnlockElement(MTX_FO, file_->lid, false);
					}

					if (ret > -1)
					{
						std::vector<sint> rets;
						ret = InitThreads(&tvec, &rets);

						if (!xret)
						{
							ret = LockElement(MTX_FO, file_->lid, &xret, true, false);
						}
					}
					tvec.clear();
					xret = GetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE);
					xret = DetSep(file_);

					if (scan_lvl > 1)
					{
						x = (ullint)BOT_STRLEN_MAX;
						last_x = 0;

						while (x < (ullint)nstat.st_size)
						{
							if ((ullint)nstat.st_size < (ullint)BOT_STRLEN_MAX)
							{
								x = (ullint)nstat.st_size;
							}

							std::vector<ullint> nvals{ (ullint)file_->lid, (ullint)file_->encode, last_x, x };
							TINFO_M nt(1, "RendFileThread", RendFileThread, lid, 0.0f, &nvals);
							tvec.push_back(nt);
							last_x = x;

							if (x + (ullint)BOT_STRLEN_MAX > (ullint)nstat.st_size)
							{
								x = (ullint)nstat.st_size;
							}
							else
							{
								x += (ullint)BOT_STRLEN_MAX;
							}
						}

						xret = HasLock(MTX_FO, file_->lid);

						if (!xret)
						{
							ret = UnlockElement(MTX_FO, file_->lid, false);
						}

						if (!ret)
						{
							std::vector<sint> rets;
							ret = InitThreads(&tvec, &rets);

							if (!xret)
							{
								ret = LockElement(MTX_FO, file_->lid, &xret, true, false);
							}
						}
						xret = GetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE);
					}
				}
				else
				{
					if (nstat.st_size)
					{
						file_->fst.RenewLocs(nstat.st_size-1, 0, 0);
						ret = BOTScanFileSyms(file_);

						if (ret > -1)
						{
							file_->fst.AvgSyms();
							ret = DetSep(file_);

							if (scan_lvl > 1)
							{
								ret = BOTRendFileSyms(file_);

								if (ret < 0)
								{
									ret = -1;
								}
							}
						}
					}
				}
			}
			else
			{
				ret = 0;
			}

			std::vector<MACSYM> svec;

			if (!file_->path.empty())
			{
				MACSYM fc(16, (u_char*)file_->path.c_str(), 0);
				svec.push_back(fc);
			}

			if (!file_->name.empty())
			{
				MACSYM fc(7, (u_char*)file_->name.c_str(), file_->encode);
				svec.push_back(fc);
			}

			if (!file_->type.empty())
			{
				MACSYM fc(8, (u_char*)file_->type.c_str(), file_->encode);
				svec.push_back(fc);
			}

			if (!svec.empty())
			{
				sint xret = AddCode(&svec);

				if (xret < 0)
				{
					xret = -1;
				}
			}
		}
		else
		{
			file_->fst.Clear();
			ret = -1;
		}

		if (file_->lid > -1)
		{
			BOT_FILE nf(file_->name.c_str(), file_->type.c_str(), file_->path.c_str(), file_->omode, -1, file_->lid, lid, file_->bto, file_->encode, &file_->fst);
			sint xret = SetVecEle(&nf, MTX_FO, file_->lid, false, false);

			if (xret < 0)
			{
				xret = -1;
			}
		}
		return ret;
	}
	sint BOTCreateFile(BOT_FILE_M* file_ = 0, sint* was_open = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_96 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTCreateFile(BOT_FILE_M *file_(%i), sint* was_open(%i))", (sint)file_, (sint)was_open);
			oc = Output(ncar.carr, 2);
		}
		if (!file_ || !was_open)
		{
			return -1;
		}

		sint ret = -1;

		if (strcmp(cur_path.c_str(), file_->path.c_str()))
		{
			//if (file_->fcon > -1)
			//{
				_char pre = '.';
				_char dmk = '\\';
				uint uf = 0;
				uint f = 0;

				for (uint xf = f; xf < file_->path.length(); xf++)
				{
					if (memcmp((void*)&file_->path[xf], (void*)&pre, sizeof(pre)))
					{
						f = xf;
						xf = file_->path.length();
					}
				}

				for (uint xf = f + 1; xf < file_->path.length(); xf++)
				{
					if (!memcmp((void*)&file_->path[xf], (void*)&dmk, sizeof(dmk)))
					{
						f = xf + 1;
						xf = file_->path.length();
					}
				}

				uf = f;

				for (; f < file_->path.length(); f++)
				{
					if (!memcmp((void*)&file_->path[f], (void*)&dmk, sizeof(dmk)))
					{
						BOT_FILE_M dirf(file_->path.substr(uf, f - uf).c_str(), "", file_->path.substr(0, uf).c_str(), file_->omode, BOT_DIR_CON);
						uf = f + 1;
						ret = BOTFileStats(&dirf);

						if (ret < 0)
						{
							sint of = -1;
							ret = BOTOpenFile(&dirf, &of, true);
							//ret = _mkdir(dirf.path.c_str());

							if (ret < 0)
							{
								if (debug_lvl >= 1 && debug_m)
								{
									std::string ncar;
									sint oc = bot_sprintfs(&ncar, false, "failed to open and then failed to create directory: \"%s\"", (sint)dirf.path.c_str());
									oc = Output(ncar.c_str(), 1);
								}
								return -1;
							}
							ret = BOTFileStats(&dirf);

							if (ret)
							{
								if (debug_lvl >= 1 && debug_m)
								{
									std::string ncar;
									sint oc = bot_sprintfs(&ncar, false, "failed to acquite stats for created directory: \"%s\"", (sint)dirf.path.c_str());
									oc = Output(ncar.c_str(), 1);
								}
								return -1;
							}
							else
							{
								if (S_ISDIR(dirf.fst.filestats.st_mode))
								{
									if (!cur_path.empty())
									{
										cur_path.clear();
										cur_path.append(dirf.path.c_str());
									}
								}
								else
								{
									return -1;
								}
							}
						}
						else
						{
							if (S_ISDIR(dirf.fst.filestats.st_mode))
							{
								if (!cur_path.empty())
								{
									cur_path.clear();
									cur_path.append(dirf.path.c_str());
								}
							}
							else
							{
								return -1;
							}
						}
					}
				}
			//}
		}

		switch (file_->cm)
		{
		case BOT_DB_CON:
		{
			BOT_DB_M ndb(file_->name.c_str());
			sint xh = 1;
			ret = OpenDB(&ndb, 3, was_open, &xh);

			if (ret > -1)
			{
				ret = CreateDatabase(&ndb);

				if (ret)
				{

				}
				if (!*was_open)
				{
					sint xret = ret;
					ret = CloseDB(&ndb, &xh);
					/*
					if (ret > -1)
					{
						ret = GetDBConn(&ndb);
					}*/
				}
			}
			break;
		}
		case BOT_F_CON:
		{
			if (file_->fcon < 0)
			{
				ret = GetFConn(file_);
			}

			if (file_->fcon > -1)
			{
				ret = -1;
				std::string instr;
				instr.append(file_->path.c_str());
				instr.append(file_->name.c_str());
				instr.append(file_->type.c_str());
				f_con[file_->fcon]->fstrm.open(instr.c_str(), file_->omode);

				if (f_con[file_->fcon]->fstrm.is_open())
				{
					f_con[file_->fcon]->fstrm.close();
					ret = 0;
				}
				ret = CloseFConn(file_);
			}
			break;
		}
		case BOT_DIR_CON:
		{
			if (was_open)
			{
				if (*was_open < 0)
				{
					*was_open = 0;
				}
			}
			std::string dirf;
			dirf.append(file_->path.c_str());
			dirf.append(file_->name.c_str());
#ifdef _WIN32
			ret = _mkdir(dirf.c_str());
#else
			ret = mkdir(dirf.c_str(), S_IFDIR);
#endif
			break;
		}
		default:
		{
			break;
		}
		}

		if (ret > -1)
		{
			if (file_->fst.exists < 1)
			{
				file_->fst.exists = 1;
			}
		}
		return ret;
	}
	sint BOTRemoveFile(BOT_FILE_M *xfile_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTRemoveFile(BOT_FILE_M *xfile_(%i))", (sint)xfile_);
			oc = Output(ncar.carr, 2);
		}

		if (!xfile_)
		{
			return -1;
		}

		sint ret = -1;
		switch (xfile_->cm)
		{
		case BOT_DIR_CON:
		{
			std::string nmstr;
			nmstr.append(xfile_->path.c_str());
			nmstr.append(xfile_->name.c_str());
#ifdef _WIN32
			ret = _rmdir(nmstr.c_str());
#else
			ret = rmdir(nmstr.c_str());
#endif
			break;
		}
		case BOT_DB_CON:
		case BOT_F_CON:
		{
			f_con[xfile_->fcon]->fstrm.seekp(0);

			for (sint x = 0; x < f_con[xfile_->fcon]->fstrm.end; x++)
			{
				f_con[xfile_->fcon]->fstrm.put((_char)76);
				x++;

				if (x < f_con[xfile_->fcon]->fstrm.end)
				{
					f_con[xfile_->fcon]->fstrm.put((_char)79);
					x++;

					if (x < f_con[xfile_->fcon]->fstrm.end)
					{
						f_con[xfile_->fcon]->fstrm.put((_char)88);
						x++;

						if (x < f_con[xfile_->fcon]->fstrm.end)
						{
							f_con[xfile_->fcon]->fstrm.put((_char)79);
						}
					}
				}
			}
			std::string nmstr;
			nmstr.append(xfile_->path.c_str());
			nmstr.append(xfile_->name.c_str());
			nmstr.append(xfile_->type.c_str());
			ret = std::remove(nmstr.c_str());

			if (ret)
			{
				ret = -1;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		if (ret > -1)
		{
			sint p = ClearVecEle(MTX_FO, xfile_->lid, false);
		}

		return ret;
	}
	sint BOTOpenFile(sint flid = -1, sint *was_open = 0, bool cine = false, bool r_to_st = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_128 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenFile(sint flid(%i), sint *was_open(%i), bool cine(%u), bool r_to_st(%u))", flid, (sint)was_open, (uint)cine, (uint)r_to_st);
			oc = Output(ncar.carr, 2);
		}

		BOT_FILE_M nf;
		sint gc = GetVecEle((void*)&nf, MTX_FO, flid);

		if (gc < 0)
		{
			return -1;
		}
		return BOTOpenFile(&nf, was_open, cine, r_to_st);
	}
	sint BOTOpenFile(BOT_FILE_M* mfile_ = 0, sint *was_open = 0, bool cine = false, bool r_to_st = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_128 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenFile(BOT_FILE_M* mfile_(%i), sint *was_open(%i), bool cine(%u), bool r_to_st(%u))", (sint)mfile_, (sint)was_open, (uint)cine, (uint)r_to_st);
			oc = Output(ncar.carr, 2);
		}

		if (!mfile_ || !was_open)
		{
			return -10;
		}

		sint gc = -1;

		if (mfile_->lid < 0)
		{
			gc = GetInVec((void*)mfile_, MTX_FO);
		}
		else
		{
			gc = GetVecEle((void*)mfile_, MTX_FO, mfile_->lid);
		}

		if (mfile_->lid < 0)
		{
			BOT_FILE nfile(mfile_->name.c_str(), mfile_->type.c_str(), mfile_->path.c_str(), mfile_->omode, mfile_->cm, -1, lid, -1, mfile_->encode);
			gc = PushToVec((void*)&nfile, MTX_FO, true, true, false);

			if (gc < 0)
			{
				return -1;
			}

			gc = GetVecEle((void*)mfile_, MTX_FO, nfile.lid);

			if (gc < 0)
			{
				return -1;
			}
		}

		gc = BOTFileStats(mfile_, (sint)BOT_FSCAN_LVL);
		sint xh = -1;
		sint lx = LockElement(MTX_FO, mfile_->lid, &xh, true, false);

		if (lx)
		{
			return -1;
		}

		if (mfile_->fst.exists < 0)
		{
			if (cine)
			{
				gc = BOTCreateFile(mfile_, was_open);

				if (gc > -1)
				{
					gc = BOTFileStats(mfile_);

					if (gc)
					{
						return -1;
					}
					if (mfile_->cm == BOT_DIR_CON)
					{
						return mfile_->lid;
					}
				}
				else
				{
					return -5;
				}
			}
			else
			{
				return -1;
			}
		}

		sint fc = -1;
		gc = 0;

		for (fc = GetFConn(mfile_, was_open); fc < 0 && gc < INT32_MAX; fc = GetFConn(mfile_))
		{
			slint rst = nsRest((slint)BOT_FO_REST);
			gc++;
		}

		if (fc < 0)
		{
			return -1;
		}

		if (was_open)
		{
			if (*was_open)
			{
				if (!r_to_st)
				{
					return mfile_->lid;
				}
			}
		}

		if (S_ISREG(mfile_->fst.filestats.st_mode))
		{
			if (strcmp(cur_path.c_str(), mfile_->path.c_str()))
			{
				cur_path.clear();
				cur_path.append(mfile_->path);
			}

			if (!mfile_->path.empty())
			{
				if (mfile_->path[mfile_->path.length() - 1] != '\\')
				{
					mfile_->path.push_back('\\');
				}
			}

			switch (mfile_->cm)
			{
			case BOT_DB_CON:
			{
				BOT_DB_M ndb(mfile_->name.c_str());
				sint xh = 1;
				fc = OpenDB(&ndb, mfile_->omode, was_open, &xh);
				break;
			}
			case BOT_F_CON:
			{
				std::string instr;
				instr.append(mfile_->path.c_str());
				instr.append(mfile_->name.c_str());
				instr.append(mfile_->type.c_str());
				f_con[mfile_->fcon]->fstrm.open(instr.c_str(), mfile_->omode);

				if (!f_con[mfile_->fcon]->fstrm.is_open())
				{
					return -1;
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}
		else if (S_ISDIR(mfile_->fst.filestats.st_mode))
		{
			gc = -1;
			gc = mfile_->name.find(cur_path, 0);

			if (!gc)
			{
				cur_path.append("\\");
				cur_path.append(mfile_->name);
			}
			else
			{
				cur_path.clear();
				cur_path.append(mfile_->path);
			}
			fc = 0;
		}
		else if (S_ISCHR(mfile_->fst.filestats.st_mode)) {}
		else if (S_ISBLK(mfile_->fst.filestats.st_mode)) {}
		else if (S_ISFIFO(mfile_->fst.filestats.st_mode)) {}
		else if (S_ISLNK(mfile_->fst.filestats.st_mode)) {}
		else if (S_ISSOCK(mfile_->fst.filestats.st_mode)) {}
		else {}

		if (fc < 0)
		{
			if (!xh)
			{
				xh = UnlockElement(MTX_FO, mfile_->lid, false);
			}
			gc = ClearVecEle(MTX_FO, mfile_->lid, false);

			if (fc < 0)
			{
				return -1;
			}
		}
		return mfile_->lid;
	}
	sint BOTFileOUT(BOT_FILE_M* file_ = 0, ...)
	{
		if (!file_)
		{
			return -1;
		}

		sint ret = -1;

		if (file_->cm == BOT_F_CON)
		{
			boto_file = true;
			sint ud = UpdMTXPrio();
			bool done = false;
			va_list args;
			va_start(args, file_);

			while (!done)
			{
				sint as_opt = va_arg(args, sint);

				switch (as_opt)
				{
				case -1:
				case BOT_RTV_MAX:
				{
					done = true;
					break;
				}
				case BOT_RTV_UINT:
				{
					uint val_ = va_arg(args, uint);
					f_con[file_->fcon]->fstrm.put(val_);
					ret = 0;
					break;
				}
				case BOT_RTV_UCHAR:
				{
					uint val_ = va_arg(args, uint);
					u_char val = (u_char)val_;
					f_con[file_->fcon]->fstrm.put(val);
					ret = 0;
					break;
				}
				case BOT_RTV_SINT:
				{
					sint val_ = va_arg(args, sint);
					f_con[file_->fcon]->fstrm.put(val_);
					ret = 0;
					break;
				}
				case BOT_RTV_CHAR:
				{
					sint val_ = va_arg(args, sint);
					_char val = (_char)val_;
					f_con[file_->fcon]->fstrm.put(val);
					ret = 0;
					break;
				}
				case BOT_RTV_UINTP:
				{
					uint* val_ = va_arg(args, uint*);
					size_t nt = 0;
					uint term = (uint)'\0';

					while (memcmp((void*)&val_[nt], (void*)&term, sizeof(term)))
					{
						f_con[file_->fcon]->fstrm.put(val_[nt]);
						nt++;
					}
					ret = 0;
					break;
				}
				case BOT_RTV_UCHARP:
				{
					uint* val_ = va_arg(args, uint*);
					u_char* val = (u_char*)val_;
					size_t nt = 0;
					u_char term = (u_char)'\0';

					while (memcmp((void*)&val_[nt], (void*)&term, sizeof(term)))
					{
						f_con[file_->fcon]->fstrm.put(val_[nt]);
						nt++;
					}
					ret = 0;
					break;
				}
				case BOT_RTV_SINTP:
				{
					sint* val_ = va_arg(args, sint*);
					size_t nt = 0;
					sint term = (sint)'\0';

					while (memcmp((void*)&val_[nt], (void*)&term, sizeof(term)))
					{
						f_con[file_->fcon]->fstrm.put(val_[nt]);
						nt++;
					}
					ret = 0;
					break;
				}
				case BOT_RTV_CHARP:
				{
					sint* val_ = va_arg(args, sint*);
					_char* val = (_char*)val_;
					size_t nt = 0;
					_char term = '\0';

					while (memcmp((void*)&val_[nt], (void*)&term, sizeof(term)))
					{
						f_con[file_->fcon]->fstrm.put(val_[nt]);
						nt++;
					}
					ret = 0;
					break;
				}
				case BOT_RTV_CCHAR:
				{
					c_char* op_ = va_arg(args, c_char*);

					if (op_)
					{
						size_t osiz = strlen(op_);

						if (osiz && osiz < BOT_STRLEN_MAX)
						{
							f_con[file_->fcon]->fstrm << op_ << std::endl;
							ret = 0;
						}
					}
					break;
				}
				case BOT_RTV_STR:
				{
					std::string* str = va_arg(args, std::string*);

					if (str)
					{
						if (!str->empty())
						{
							f_con[file_->fcon]->fstrm << str->c_str() << std::endl;
						}
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* strvec = va_arg(args, std::vector<std::string>*);

					if (strvec)
					{
						if (!strvec->empty())
						{
							for (size_t siz = 0; siz < strvec->size(); siz++)
							{
								f_con[file_->fcon]->fstrm << strvec->at(siz).c_str() << std::endl;
								strvec->at(siz).clear();
							}
							strvec->clear();
						}
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
			boto_file = false;
			ud = UpdMTXPrio();
		}
		else if(file_->cm == BOT_DB_CON)
		{
			std::vector<BOT_STMT> tvec;
			bool done = false;
			va_list args;
			va_start(args, file_);

			while (!done)
			{
				sint as_opt = va_arg(args, sint);

				switch (as_opt)
				{
				case -1:
				case BOT_RTV_MAX:
				{
					done = true;
					break;
				}
				case BOT_RTV_CCHAR:
				{
					c_char* op_ = va_arg(args, c_char*);

					if (op_)
					{
						size_t osiz = strlen(op_);

						if (osiz && osiz < BOT_STRLEN_MAX)
						{
							BOT_STMT t;
							t.stmt.append(op_);
							tvec.push_back(t);
						}
					}
					break;
				}
				case BOT_RTV_STR:
				{
					std::string* str = va_arg(args, std::string*);

					if (str)
					{
						if (!str->empty())
						{
							BOT_STMT t;
							t.stmt.append(str->c_str());
							tvec.push_back(t);
						}
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* strvec = va_arg(args, std::vector<std::string>*);

					if (strvec)
					{
						if (!strvec->empty())
						{
							for (size_t siz = 0; siz < strvec->size(); siz++)
							{
								BOT_STMT t;
								t.stmt.append(strvec->at(siz).c_str());
								tvec.push_back(t);
								strvec->at(siz).clear();
							}
							strvec->clear();
						}
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

			if (!tvec.empty())
			{
				ret = Commit(&tvec);
			}
		}
		else {}
		return ret;
	}
	sint BOTFileIN(sint fcon = -1, sint from = -1, sint to = -1, ...)
	{
		if (fcon < 0)
		{
			return -1;
		}

		/*enum bot_rtv_vals
		{
			BOT_RTV_SINT = 0,
			BOT_RTV_UINT = 1,
			BOT_RTV_CHAR = 2,
			BOT_RTV_UCHAR = 3,
			BOT_RTV_SINTP = 4,
			BOT_RTV_UINTP = 5,
			BOT_RTV_CHARP = 6,
			BOT_RTV_UCHARP = 7,
			BOT_RTV_CCHAR = 8,
			BOT_RTV_STR = 9,
			BOT_RTV_REAL = 10,
			BOT_RTV_MICS = 11,
			BOT_RTV_MACS = 12,
			BOT_RTV_VSINT = 13,
			BOT_RTV_VUINT = 14,
			BOT_RTV_VCHAR = 15,
			BOT_RTV_VUCHAR = 16,
			BOT_RTV_VCCHAR = 17,
			BOT_RTV_VSTR = 18,
			BOT_RTV_VREAL = 19,
			BOT_RTV_VMICS = 20,
			BOT_RTV_VMACS = 21,
			BOT_RTV_MAX = 22
		};*/

		BOT_FILE_M nfile;
		sint ret = GetVecEle((void*)&nfile, MTX_FO, f_con[fcon]->flid);

		if (ret > -1)
		{
			if (from > -1)
			{
				f_con[fcon]->fstrm.seekg(from);
			}
			sint fend = f_con[fcon]->fstrm.end;

			if (to > -1)
			{
				fend = to;
			}
			sint ret = -1;

			if (nfile.cm == BOT_F_CON)
			{
				bool done = false;
				va_list args;
				va_start(args, to);
				boto_file = true;
				sint ud = UpdMTXPrio();

				while (!done)
				{
					sint as_opt = va_arg(args, sint);

					switch (as_opt)
					{
					case -1:
					case BOT_RTV_MAX:
					{
						done = true;
						break;
					}
					case BOT_RTV_SINT:
					{
						sint* val_ = va_arg(args, sint*);

						if (val_ != NULL)
						{
							if (f_con[fcon]->fstrm.get(*((_char*)&ud)))
							{
								memcpy((void*)val_, (void*)&ud, sizeof(ud));
								MICSYM nsym;
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_CHAR:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_ != NULL)
						{
							_char nc;

							if (f_con[fcon]->fstrm.get(nc))
							{
								memcpy((void*)val_, (void*)&nc, sizeof(nc));
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_UINT:
					{
						uint* val_ = va_arg(args, uint*);

						if (val_ != NULL)
						{
							if (f_con[fcon]->fstrm.get(*((_char*)&ud)))
							{
								memcpy((void*)val_, (void*)&ud, sizeof(ud));
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_UCHAR:
					{
						u_char* val_ = va_arg(args, u_char*);

						if (val_ != NULL)
						{
							u_char nc;

							if (f_con[fcon]->fstrm.get(*((_char*)&nc)))
							{
								memcpy((void*)val_, (void*)&nc, sizeof(nc));
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_REAL:
					{
						float* val_ = va_arg(args, float*);

						if (val_ != NULL)
						{
							if (f_con[fcon]->fstrm.get(*((_char*)&ud)))
							{
								float nd = (float)ud;
								memcpy((void*)val_, (void*)&nd, sizeof(nd));
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_CCHAR:
					{
						c_char* op_ = va_arg(args, c_char*);

						if (op_ != NULL)
						{

						}
						break;
					}
					case BOT_RTV_STR:
					{
						std::string* str_ = va_arg(args, std::string*);

						if (str_ != NULL)
						{
							_char xc;

							while (f_con[fcon]->fstrm.get(xc) && str_->length() < (size_t)BOT_STRLEN_MAX)
							{
								str_->push_back(xc);
							}
						}
						break;
					}
					case BOT_RTV_VSINT:
					{
						std::vector<sint>* val_ = va_arg(args, std::vector<sint>*);

						if (val_ != NULL)
						{
							while (f_con[fcon]->fstrm.get(*((_char*)&ud)) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(ud);
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_VCHAR:
					{
						std::vector<_char>* val_ = va_arg(args, std::vector<_char>*);

						if (val_ != NULL)
						{
							_char nc;

							while (f_con[fcon]->fstrm.get(nc) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(nc);
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_VUINT:
					{
						std::vector<uint>* val_ = va_arg(args, std::vector<uint>*);

						if (val_ != NULL)
						{
							while (f_con[fcon]->fstrm.get(*((_char*)&ud)) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(ud);
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_VUCHAR:
					{
						std::vector<u_char>* val_ = va_arg(args, std::vector<u_char>*);

						if (val_ != NULL)
						{
							u_char nc;

							while (f_con[fcon]->fstrm.get(*((_char*)&nc)) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(nc);
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_VREAL:
					{
						std::vector<float>* val_ = va_arg(args, std::vector<float>*);

						if (val_ != NULL)
						{
							while (f_con[fcon]->fstrm.get(*((_char*)&ud)) && val_->size() < BOTVEC_LIM)
							{
								float nd = (float)ud;
								val_->push_back(nd);
							}
						}
						ret = 0;
						break;
					}
					case BOT_RTV_VSTR:
					{
						std::vector<std::string>* strvec_ = va_arg(args, std::vector<std::string>*);

						if (strvec_ != NULL)
						{
							std::string nstr;
							_char xc;

							while (f_con[fcon]->fstrm.get(xc) && nstr.length() < (size_t)BOT_STRLEN_MAX)
							{
								nstr.push_back(xc);
							}
							strvec_->push_back(nstr);
						}
						break;
					}
					default:
					{
						done = true;
						break;
					}
					}

					if ((sint)f_con[fcon]->fstrm.tellg() == fend)
					{
						done = true;
					}
				}
				boto_file = false;
				ud = UpdMTXPrio();
				va_end(args);
			}
			else if (nfile.cm == BOT_DB_CON)
			{
				bool done = false;
				va_list args;
				va_start(args, to);

				while (!done)
				{
					sint as_opt = va_arg(args, sint);
					BOT_STMT* qval_ = va_arg(args, BOT_STMT*);

					if (qval_ != NULL)
					{
						ret = Query(qval_, as_opt);
					}
					
					if (ret < 0)
					{
						done = true;
					}
				}
				va_end(args);
			}
			else {}
			return ret;
		}
		return -1;
	}
	sint BOTCloseFile(sint flid = -1, bool clear_conn = true, bool del = false, bool encr = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_128 instr;
			sint oc = bot_sprintf(instr.carr, instr.siz, "::BOTCloseFile(sint flid(%i), bool clear_conn(%u), bool del(%u), bool encr(%u))", flid, (uint)clear_conn, (uint)del, (uint)encr);
			oc = Output(instr.carr, 2);
		}

		if (flid < 0)
		{
			return -1;
		}

		BOT_FILE_M xfile;
		sint xc = GetVecEle((void*)&xfile, MTX_FO, flid);

		if (xc > -1)
		{
			return BOTCloseFile(&xfile, clear_conn, del, encr);
		}
		return -1;
	}
	sint BOTCloseFile(BOT_FILE_M* xfile_ = 0, bool clear_conn = true, bool del = false, bool encr = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_128 instr;
			sint oc = bot_sprintf(instr.carr, instr.siz, "::BOTCloseFile(BOT_FILE_M* xfile_(%i), bool clear_conn(%u), bool del(%u), bool encr(%u))", (sint)xfile_, (uint)clear_conn, (uint)del, (uint)encr);
			oc = Output(instr.carr, 2);
		}

		if (!xfile_)
		{
			return -1;
		}

		switch (xfile_->cm)
		{
		case BOT_DB_CON:
		{
			BOT_DB_M xdb(xfile_->name.c_str());
			sint fc = GetInVec((void*)&xdb, MTX_DBL);

			if (fc > -1)
			{
				sint xh = 1;
				fc = CloseDB(&xdb, &xh, clear_conn);

				if (fc < 0)
				{
					return -1;
				}
			}
			break;
		}
		case BOT_F_CON:
		{
			if (encr)
			{

			}
			sint fc = CloseFConn(xfile_, clear_conn);

			if (fc < 0)
			{
				return -1;
			}
			break;
		}
		case BOT_DIR_CON:
		{

			break;
		}
		default:
		{
			return -1;
			break;
		}
		}

		if (del)
		{
			sint p = BOTRemoveFile(xfile_);

			if (p)
			{
				p = -1;
			}
		}
		else
		{
			sint p = BOTFileStats(xfile_);

			if (p)
			{
				p = -1;
			}
		}

		sint p = vtool.ValInVec(&h_mtxs, MTX_FO);

		if (p > -1)
		{
			sint xp = p;
			p = vtool.ValInVec(&h_mtxs[xp].h_mems, xfile_->lid);

			if (p > -1)
			{
				return UnlockElement(MTX_FO, xfile_->lid, false);
			}
		}
		return -1;
	}
	sint BotOpenError(sint err_id, std::string* err_str = 0)
	{
		if (!err_str)
		{
			return -1;
		}
		switch (err_id)
		{
		case -10:
		{
			err_str->append("empty file pointer.");
			break;
		}
		case -6:
		{
			err_str->append("fstream already open.");
			break;
		}
		case -5:
		{
			err_str->append("Unable to create file cine=true.");
			break;
		}
		case -4:
		{
			err_str->append("Unable to create file cine=false.");
			break;
		}
		case -3:
		{
			err_str->append("Empty file name.");
			break;
		}
		case -2:
		{
			err_str->append("Failed to acquire file mtx:");
			break;
		}
		case -1:
		{
			err_str->append("Unable to open file.");
			break;
		}
		case 1:
		{
			err_str->append("Is directory.");
			break;
		}
		default:
		{
			break;
		}
		}
		return 0;
	}

	// Sleep Functions
	void Nanosleep(slint dur = BOT_NANO_REST)
	{
#ifdef _WIN32
		HANDLE tmr;
		LARGE_INTEGER lint;
		dur /= 100;

		if (!(tmr = CreateWaitableTimer(NULL, TRUE, NULL)))
		{
			return;
		}

		lint.QuadPart = -dur;

		if (!SetWaitableTimer(tmr, &lint, 0, NULL, NULL, FALSE))
		{
			CloseHandle(tmr);
			return;
		}

		WaitForSingleObject(tmr, INFINITE);
		CloseHandle(tmr);
		return;
#else
		struct timespec tI, tII;
		tI.tv_sec = 0;
		tI.tv_nsec = dur;
		tII.tv_sec = 0;
		tII.tv_nsec = 0;
		slint xc = nanosleep(&tI, &tII);
		return;
#endif
	}
	slint nsRest(slint i = BOT_NANO_REST, bool keep_mtx = false)
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			carr_128 instr;
			sint oc = bot_sprintf(instr.carr, instr.siz, "nsRest(slint i(%li), bool keep_mtx(%u))", i, (uint)keep_mtx);
			oc = Output(instr.carr, 2);
		}
		stk_ct++;
		std::chrono::steady_clock::time_point t_I = std::chrono::steady_clock::now();

		if (i < (slint)BOT_NANO_REST)
		{
			i = (slint)BOT_NANO_REST;
		}

		//std::vector<lok_req> relocks;
		slint slpct = 0;

		while (slpct < i)
		{
			if (!keep_mtx && !h_mtxs.empty())
			{
				uint blox = relocks.size();
				sint cheq = CheqMTXReqs(&relocks);

				if (relocks.size() > blox)
				{
					uint elox = relocks.size() - blox;

					for (uint x = blox; x < blox+elox; x++)
					{
						cheq = CloseObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid); // returns fid as openmode

						if (cheq < 0)
						{
							relocks[x].Clear();
						}
					}
				}
			}

			Nanosleep(BOT_NANO_REST);
			std::chrono::steady_clock::time_point t_II = std::chrono::steady_clock::now();
			std::chrono::duration<slint, std::nano> span = std::chrono::duration_cast<std::chrono::duration<slint, std::nano>>(t_II - t_I);
			slpct = (slint)span.count();
		}

		if (!keep_mtx && stk_ct == 1)
		{
			for (uint x = 0; x < relocks.size(); x++)
			{
				if (relocks[x].gmtx > -1)
				{
					sint cheq = OpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);

					while (cheq < 0) // returns is_meta as wasopen, uses value set in fid by CloseObject() as var arg option for openmode
					{
						cheq = OpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);
					}

					relocks[x].Clear();
				}
			}
			sint y = vtool.CleanVec(&relocks);
		}
		
		stk_ct--;
		std::chrono::steady_clock::time_point t_II = std::chrono::steady_clock::now();
		std::chrono::duration<slint, std::nano> span = std::chrono::duration_cast<std::chrono::duration<slint, std::nano>>(t_II - t_I);
		slpct = (slint)span.count();

		if (debug_lvl >= 1000 && debug_m)
		{
			if (slpct)
			{
				carr_128 outp;
				i = bot_sprintf(outp.carr, outp.siz, "attempted to rest:%lins, rested for:%lins", i, slpct);
				i = Output(outp.carr, 2);
			}
		}
		return slpct;
	}
	slint Rest(slint i = BOT_MILLI_REST, bool keep_mtx = false)
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			carr_128 instr;
			sint oc = bot_sprintf(instr.carr, instr.siz, "Rest(slint i(%i), bool keep_mtx(%u))", i, (uint)keep_mtx);
			oc = Output(instr.carr, 2);
		}
		stk_ct++;
		std::chrono::steady_clock::time_point t_I = std::chrono::steady_clock::now();

		if (i < (slint)BOT_MILLI_REST)
		{
			i = (slint)BOT_MILLI_REST;
		}

		//std::vector<lok_req> relocks;
		slint slpct = 0;

		while (slpct < i)
		{
			if (!keep_mtx && !h_mtxs.empty())
			{
				uint blox = relocks.size();
				sint cheq = CheqMTXReqs(&relocks);

				if (relocks.size() > blox)
				{
					uint elox = relocks.size() - blox;

					for (uint x = blox; x < blox + elox; x++)
					{
						cheq = CloseObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid); // returns fid as openmode

						if (cheq < 0)
						{
							relocks[x].Clear();
						}
					}
				}
			}

#ifdef _WIN32
			Sleep(BOT_MILLI_REST);
#else
			sint xc = sleep(BOT_MILLI_REST);
#endif
			std::chrono::steady_clock::time_point t_II = std::chrono::steady_clock::now();
			std::chrono::duration<double, std::milli> span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t_II - t_I);
			slpct = (slint)span.count();
		}

		if (!keep_mtx && stk_ct == 1)
		{
			for (uint x = 0; x < relocks.size(); x++)
			{
				if (relocks[x].gmtx > -1)
				{
					sint cheq = OpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);

					while (cheq < 0) // returns is_meta as wasopen, uses value set in fid by CloseObject() as var arg option for openmode
					{
						cheq = OpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);
					}

					relocks[x].Clear();
				}
			}
			sint y = vtool.CleanVec(&relocks);
		}

		stk_ct--;
		std::chrono::steady_clock::time_point t_II = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t_II - t_I);
		slpct = (slint)span.count();

		if (debug_lvl >= 1000 && debug_m)
		{
			if (slpct)
			{
				carr_128 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "attempted to rest:%lims, rested for:%lims", i, (slint)span.count());
				op = Output(outp.carr, 2);
			}
		}
		return slpct;
	}

	// Client Functions
	sint ClearClient(BOT_CLIENT *c_) { if (c_) { c_->Clear(); return 0; } return -1; }
	sint SetClientName(std::string* ClientName_ );
	sint SetClientLoginName(std::string* ClientLoginName_ );
	sint SetClientLastLogin(std::string* str_ );
	sint SetClientLoginDate(std::string* str_ );
	sint SetClientLastFailedLogin(std::string* str_ );
	sint SetClientLastExchange(std::string* str_ );
	sint SetClientID(sint x );
	sint SetClientTotalLogins(sint x );
	sint SetClientFailedLogins(sint x );
	sint SetClientPriv(sint x );
	sint SetClientLoggedIn(bool x );
	sint GetClientName(std::string* str_ );
	sint GetClientLoginName(std::string* str_ );
	sint GetClientLastLogin(std::string* str_ );
	sint GetClientLoginDate(std::string* str_ );
	sint GetClientLastFailedLogin(std::string* str_ );
	sint GetClientLastExchange(std::string* str_ );
	sint GetClientID();
	sint GetClientTotalLogins();
	sint GetClientFailedLogins();
	sint GetClientPriv();
	bool GetClientLoggedIn();

	// Console I/O Functions
	sint Output(c_char* output_ = "", ...)
	{
		carr_64 tdata;
		sint xc = GetTimeMS(tdata.carr);
		carr_256 instr;
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][%s] ", lid, ptn.c_str());
		std::string str;
		str.append(tdata.carr);
		str.append(instr.carr);
		str.append(output_);
		sint opt[BOT_OP_OPTS];
		va_list args;
		va_start(args, output_);

		for (uint x = 0; x < sizeof(opt); x++)
		{
			opt[x] = va_arg(args, sint);

			if (opt[x] < 0 || opt[x] > 3)
			{
				x = sizeof(opt);
			}
			else
			{
				if (!opt[x])
				{
					xc = BotOut(str.c_str());
				}
				else
				{
					xc = LogPut(str.c_str(), opt[x]);
				}
			}
		}
		return xc;
	}
	sint BotOut(sint num = 0, ...)
	{
		sint ret = -1;
		if (num > 0)
		{
			std::string str;
			va_list args;
			va_start(args, num);

			for (sint x = num; x > 0 && str.length() < (uint)BOT_STRLEN_MAX; x--)
			{
				str.append(va_arg(args, c_char*));
			}
			ret = BotOut(str.c_str());
		}
		return ret;
	}
	sint BotOut(c_char* str_ = "")
	{
		sint h = -1;
		sint p = LockGMutex(MTX_O, &h);

		if (p > -1)
		{
			std::cout << str_ << std::endl;

			if (!h)
			{
				h = UnlockGMutex(MTX_O);
			}
			return 0;
		}
		return -1;
	}
	sint Output(c_char* output_ = "", sint option = 0)
	{
		carr_64 tdata;
		sint xc = GetTimeMS(tdata.carr);
		carr_256 instr;
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][%s] ", lid, ptn.c_str());
		std::string str;
		str.append(tdata.carr);
		str.append(instr.carr);
		str.append(output_);

		if (log_to[0] || log_to[1])
		{
			xc = LogPut(str.c_str(), option);
		}

		if (!option)
		{
			return BotOut(str.c_str());
		}
		return xc;
	}
	sint Input()
	{
		std::string input;
		std::getline(std::cin, input);
		sint xc = LogPut(input.c_str(), 0);

		if (!input.empty())
		{
			xc = InterpretInput(&input);
		}
		return 0;
	}
	sint DoOutput();

	sint InterpretInput(std::string *input_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::InterpretInput(std::string *input_(%i))", (sint)input_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 1 && input_)
			{
				op = Output(input_->c_str(), 2);
			}
		}

		if (!input_)
		{
			return -1;
		}

		if (input_->empty())
		{
			return -1;
		}

		sint ret = 0;

		if (input_->length() > 2)
		{
			_char com_c[3]{ '/', '#', '\0' };

			if (!memcmp((void*)&input_->at(0), (void*)&com_c[0], 1) && !memcmp((void*)&input_->at(1), (void*)&com_c[1], 1))
			{
				std::vector<std::string> vec;
				_char c = ' ';
				ret = stool.SeparateStrByChar(input_->substr(2, input_->length() - 2).c_str(), c, &vec);
				ret = Command(&vec);
			}
		}

		input_->clear();
		return ret;
	}

	std::string DetermineOutput();

	sint BOTConsole()
	{
		if (debug_lvl >= 1 && debug_m)
		{
			sint op = Output("::BOTConsole()", 2);
		}
		std::string np;
		std::getline(std::cin, np);

		if (!np.empty())
		{
			sint xc = InterpretInput(&np);
			return xc;
		}
		return -1;
	}

	// Str Manip

	std::string CleanPunctuation(c_char* clientinput_ = "");
	std::string Uppercase(c_char* str_ = "");
	std::string LEncStrI(c_char* str_ = "", sint opt = -1)
	{
		if (debug_lvl >= 100 && debug_m)
		{
			carr_128 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "LEncStrI(string *str_(%i), sint opt(%i))", (sint)str_, opt);
			oc = Output(ncar.carr, 2);
		}

		std::string s;

		if (!str_)
		{
			return s;
		}

		std::string nstr;
		nstr.append(str_);

		for (sint x = nstr.find("\"", 0); x > -1; x = nstr.find("\"", x+1))
		{
			nstr.at(x) = '\'';
		}
		s.append("\"");
		s.append(nstr.c_str());
		nstr.clear();
		s.append("\"");
		
		if (debug_lvl >= 100 && debug_m)
		{
			nstr.append("enclosed string: ");
			nstr.append(s.c_str());
			sint oc = Output(nstr.c_str(), 2);
		}
		return s;
	}
	sint OrdLocs(std::vector<size_t>* litlocs_ = 0, std::vector<size_t>* locs_ = 0, c_char* str_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::OrdLocs(vector<size_t>* litlocs_(%i), vector<size_t>* locs_(%i), c_char* str_(%u))", (sint)litlocs_, (sint)locs_, (sint)str_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_, 2);
			}
		}

		if (!litlocs_ || !locs_ || !str_)
		{
			return -1;
		}

		size_t slen = strlen(str_);

		for (size_t siz = 0; siz < slen; siz++)
		{
			sint xc = vtool.ValInVec(&nrts_ord, &str_[siz]);

			if (xc > -1)
			{
				sint lx = LitEnc(siz, litlocs_, str_);

				if (lx < 0)
				{
					locs_->push_back(siz);
					bool found = false;

					for (size_t nsiz = siz + 1; nsiz < slen; nsiz++)
					{
						if (!memcmp(&str_[nsiz], &nrts_ord_[xc], 1))
						{
							lx = LitEnc(nsiz, litlocs_, str_);

							if (lx < 0)
							{
								locs_->push_back(nsiz);
								siz = nsiz + 1;
								nsiz = slen;
								found = true;
							}
						}
					}
					if (!found)
					{
						return -1;
					}
				}
			}
		}

		if (!locs_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_1024 nump;
				sint oc = stool.VToStr(locs_, nump.carr, nump.siz);
				carr_2048 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "OrdLocs: %s", nump.carr);
				oc = Output(outp.carr, 2);
			}
			return 0;
		}
		if (debug_lvl >= 700 && debug_m)
		{
			sint oc = Output("no ordinals found.", 2);
		}
		return -1;
	}
	sint OrdEnc(size_t at_loc = 0, std::vector<size_t>* litlocs_ = 0, std::vector<size_t>* locs_ = 0, c_char* str_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::OrdEnc(size_t at_loc(%u), vector<size_t>* litlocs_(%i), vector<size_t>* locs_(%i), c_char* str_(%i))", at_loc, (sint)litlocs_, (sint)locs_, (sint)str_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_, 2);
			}
		}

		if (!litlocs_ || !locs_ || !str_)
		{
			return -1;
		}

		if (locs_->empty())
		{
			sint o = OrdLocs(litlocs_, locs_, str_);
		}

		sint ret = -1;

		for (size_t siz = 1; siz < locs_->size(); siz+=2)
		{
			if (at_loc > locs_->at(siz - 1) && at_loc < locs_->at(siz))
			{
				if (debug_lvl >= 700 && debug_m)
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, " \"%c\" enclosed between: %u \"%c\" and %u \"%c\"", str_[at_loc], locs_->at(siz - 1), str_[locs_->at(siz - 1)], locs_->at(siz), str_[locs_->at(siz - 1)]);
					op = Output(outp.carr, 2);
				}
				ret = 0;
				siz = locs_->size();
			}
		}

		if (debug_lvl >= 700 && debug_m)
		{
			carr_32 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "OrdEnc: %i", ret);
			op = Output(outp.carr, 2);
		}
		return ret;
	}
	sint LitLocs(std::vector<size_t>* locs_, c_char* str_)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::LitLocs(vector<size_t>* locs_(%i), c_char* str_(%i))", (sint)locs_, (sint)str_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_, 2);
			}
		}

		if (!locs_ || !str_)
		{
			return -1;
		}

		size_t slen = strlen(str_);
		sint cur_lit = -1;

		for (size_t siz = 0; siz < slen; siz++)
		{
			if (cur_lit > -1)
			{
				if (!memcmp(&str_[siz], &nrts_lit[cur_lit], 1))
				{
					locs_->push_back(siz);
					cur_lit = -1;
				}
			}
			else
			{
				for (size_t nsiz = 0; nsiz < nrts_lit.size(); nsiz++)
				{
					if (!memcmp(&str_[siz], &nrts_lit[nsiz], 1))
					{
						locs_->push_back(siz);
						cur_lit = (sint)nsiz;
						nsiz = nrts_lit.size();
					}
				}
			}
		}
		if (!locs_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_1024 nump;
				sint oc = stool.VToStr(locs_, nump.carr, nump.siz);
				carr_2048 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "LitLocs: %s", nump.carr);
				oc = Output(outp.carr, 2);
			}
			return 0;
		}
		if (debug_lvl >= 700 && debug_m)
		{
			sint oc = Output("no literals.", 2);
		}
		return -1;
	}
	sint LitEnc(size_t at_loc, std::vector<size_t>* locs_, c_char* str_)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::LitEnc(size_t at_loc(%u), vector<size_t>* locs_(%i), c_char* str_(%i))", at_loc, (sint)locs_, (sint)str_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 130 && str_)
			{
				op = Output(str_, 2);
			}
		}
		if (!locs_ || !str_)
		{
			return -1;
		}
		if (locs_->empty())
		{
			LitLocs(locs_, str_);
		}

		sint ret = -1;

		for (size_t siz = 1; siz < locs_->size(); siz+=2)
		{
			if (at_loc > locs_->at(siz - 1) && at_loc < locs_->at(siz))
			{
				if (debug_lvl >= 700 && debug_m)
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, " \"%c\" enclosed between: %u \"%c\" and %u \"%c\"", str_[at_loc], locs_->at(siz - 1), str_[locs_->at(siz - 1)], locs_->at(siz), str_[locs_->at(siz - 1)]);
					op = Output(outp.carr, 2);
				}
				ret = 0;
				siz = locs_->size();
			}
		}

		if (debug_lvl >= 700 && debug_m)
		{
			carr_32 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "LitEnc: %i", ret);
			op = Output(outp.carr, 2);
		}
		return ret;
	}
	bool XEnclosedInY(std::vector<size_t>* litlocs_ = 0, std::string* statements_ = 0, sint sc_loc = -1, sint x_loc = -1, std::string* fy_char = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::XenclosedInY(vector<size_t>* litlocs_(%i), string* statements(%i), sint sc_loc(%i), sint x_loc(%i), string* fy_char(%i))", (sint)litlocs_, (sint)statements_, sc_loc, x_loc, (sint)fy_char);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && statements_)
			{
				op = Output(statements_->c_str(), 2);
			}
		}

		if (!litlocs_ || !statements_ || sc_loc < 0 || x_loc < 0 || !fy_char)
		{
			return false;
		}

		if (litlocs_->empty())
		{
			LitLocs(litlocs_, statements_->c_str());
		}

		sint opens = 0;
		std::string by_char, lit_char_a, lit_char_b;
		lit_char_a.append("\"");
		lit_char_b.append("'");

		if (!strcmp(fy_char->c_str(), "(")) { by_char.append(")"); }
		else if (!strcmp(fy_char->c_str(), "{")) { by_char.append("}"); }
		else if (!strcmp(fy_char->c_str(), "<")) { by_char.append(">"); }
		else if (!strcmp(fy_char->c_str(), "[")) { by_char.append("]"); }
		else
		{
			sint x = LitEnc(x_loc, litlocs_, statements_->c_str());
			if (!x)
			{
				return true;
			}
			return false;
		}


		bool y = false;
		sint by_loc = -1;
		sint old_fy_loc = -1;
		sint fy_loc = statements_->find(*fy_char, old_fy_loc + 1);

		while (fy_loc > old_fy_loc && fy_loc < x_loc)
		{
			if (LitEnc(fy_loc, litlocs_, statements_->c_str()))
			{
				opens++;

				if (debug_lvl >= 700 && debug_m)
				{
					carr_256 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "opener found at:%i opens:%i", fy_loc, opens);
					op = Output(outp.carr, 2);
				}

				by_loc = statements_->find(by_char, fy_loc + 1);
				bool done = false;
				sint nloc = by_loc;

				while (!done)
				{
					if (nloc > fy_loc && nloc < sc_loc)
					{
						if (nloc == x_loc)
						{
							opens--;

							if (debug_lvl >= 700 && debug_m)
							{
								carr_256 outp;
								sint op = bot_sprintf(outp.carr, outp.siz, "closer is our _char at:%i opens:%i", x_loc, opens);
								op = Output(outp.carr, 2);
							}

							if (opens > 0)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							if (LitEnc(nloc, litlocs_, statements_->c_str()))
							{
								by_loc = nloc;

								if (nloc < x_loc)
								{
									opens--;

									if (debug_lvl >= 700 && debug_m)
									{
										carr_256 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is before our _char at:%i opens:%i", x_loc, opens);
										op = Output(outp.carr, 2);
									}
									nloc = statements_->find(by_char, by_loc + 1);
								}
								else
								{
									if (fy_loc < x_loc && nloc > x_loc)
									{
										y = true;
									}

									if (debug_lvl >= 700 && debug_m)
									{
										carr_256 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is after our _char at:%i opens:%i", nloc, opens);
										op = Output(outp.carr, 2);
									}
									done = true;
								}
							}
							else
							{
								if (debug_lvl >= 700 && debug_m)
								{
									carr_256 outp;
									sint op = bot_sprintf(outp.carr, outp.siz, "looking for another closer after:%i opens:%i", nloc + 1, opens);
									op = Output(outp.carr, 2);
								}
								nloc = statements_->find(by_char, by_loc + 1);
							}
						}
					}
					else
					{
						if (debug_lvl >= 700 && debug_m)
						{
							carr_256 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "no closer was found, opens:%i", opens);
							op = Output(outp.carr, 2);
						}
						done = true;
					}
				}
			}
			old_fy_loc = fy_loc;
			fy_loc = statements_->find(*fy_char, fy_loc + 1);
		}

		if (opens > 0 || y)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "a \"%s\" before this \"%c\" was open, opens:%i", fy_char->c_str(), statements_->at(x_loc), opens);
				op = Output(outp.carr, 2);
			}
			y = true;
		}
		else
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "\"%c\" not enclosed by \"%s\" (2)", statements_->at(x_loc), fy_char->c_str());
				op = Output(outp.carr, 2);
			}
		}
		return y;
	}
	bool XEnclosedInY(std::vector<size_t>* litlocs_ = 0, c_char* statements_ = "", sint sc_loc = -1, sint x_loc = -1, _char fy_char = '\0')
	{
		sint opens = 0;

		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::XenclosedInY(vector<size_t>* litlocs_(%i), string* statements(%i), sint sc_loc(%i), sint x_loc(%i), string* fy_char \"%c\")", (sint)litlocs_, (sint)statements_, sc_loc, x_loc, fy_char);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && statements_)
			{
				op = Output(statements_, 2);
			}
		}
		if (!litlocs_ || sc_loc < 0 || x_loc < 0 || fy_char == '\0')
		{
			return false;
		}
		if (litlocs_->empty())
		{
			LitLocs(litlocs_, statements_);
		}

		_char by_char;

		if (fy_char == '(') { by_char = ')'; }
		else if (fy_char == '{') { by_char = '}'; }
		else if (fy_char == '<') { by_char = '>'; }
		else if (fy_char == '[') { by_char = ']'; }
		else
		{
			sint x = LitEnc(x_loc, litlocs_, statements_);
			if (!x) { return true; }
			return false;
		}

		bool y = false;
		sint by_loc = -1;
		sint old_fy_loc = -1;
		sint fy_loc = stool.FindInStr(fy_char, statements_, old_fy_loc + 1, sc_loc, true);

		while (fy_loc > old_fy_loc && fy_loc < x_loc)
		{
			if (LitEnc(fy_loc, litlocs_, statements_))
			{
				opens++;

				if (debug_lvl >= 700 && debug_m)
				{
					carr_256 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "opener found at:%i opens:%i", fy_loc, opens);
					op = Output(outp.carr, 2);
				}

				by_loc = stool.FindInStr(by_char, statements_, fy_loc + 1, true);
				bool done = false;
				sint nloc = by_loc;

				while (!done)
				{
					if (nloc > fy_loc && nloc < sc_loc)
					{
						if (nloc == x_loc)
						{
							opens--;

							if (debug_lvl >= 700 && debug_m)
							{
								carr_256 outp;
								sint op = bot_sprintf(outp.carr, outp.siz, "closer is our _char at:%i opens:%i", x_loc, opens);
								op = Output(outp.carr, 2);
							}

							if (opens > 0)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							if (LitEnc(nloc, litlocs_, statements_))
							{
								by_loc = nloc;

								if (nloc < x_loc)
								{
									opens--;

									if (debug_lvl >= 700 && debug_m)
									{
										carr_256 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is before our _char at:%i opens:%i", x_loc, opens);
										op = Output(outp.carr, 2);
									}
									nloc = stool.FindInStr(by_char, statements_, by_loc + 1, true);
								}
								else
								{
									if (fy_loc < x_loc && nloc > x_loc)
									{
										y = true;
									}

									if (debug_lvl >= 700 && debug_m)
									{
										carr_256 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is after our _char at:%i opens:%i", nloc, opens);
										op = Output(outp.carr, 2);
									}
									done = true;
								}
							}
							else
							{
								if (debug_lvl >= 700 && debug_m)
								{
									carr_256 outp;
									sint op = bot_sprintf(outp.carr, outp.siz, "looking for another closer after:%i opens:%i", nloc + 1, opens);
									op = Output(outp.carr, 2);
								}
								nloc = stool.FindInStr(by_char, statements_, by_loc + 1, true);
							}
						}
					}
					else
					{
						if (debug_lvl >= 700 && debug_m)
						{
							carr_256 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "no closer was found, opens:%i", opens);
							op = Output(outp.carr, 2);
						}
						done = true;
					}
				}
			}
			old_fy_loc = fy_loc;
			fy_loc = stool.FindInStr(fy_char, statements_, fy_loc + 1, true);
		}

		if (opens > 0 || y)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "a \"%c\" before this \"%c\" was open", fy_char, statements_[x_loc]);
				op = Output(outp.carr, 2);
			}

			y = true;
		}
		else
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "\"%c\" not enclosed by \"%c\" (4)", statements_[x_loc], fy_char);
				op = Output(outp.carr, 2);
			}
		}

		return y;
	}

	// SQL statement manip

	sint SeparateSQL(std::string* statements_ = 0, std::vector<std::string>* vec_ = 0)
	{
		if (debug_lvl >= 75 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::SeparateSQL(string* statements_(%i), vec_(%i))", (sint)statements_, (sint)vec_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 80 && statements_)
			{
				op = Output(statements_->c_str(), 2);
			}
		}

		if (!statements_ || !vec_)
		{
			return -1;
		}
		std::vector<size_t> litlocs;
		LitLocs(&litlocs, statements_->c_str());
		bool done = false;
		sint sel_loc = 0;
		sint sc_loc = 0;
		sint sc_loci = 0;

		while (!done)
		{
			if (!statements_->empty())
			{
				sc_loc = statements_->find(";", sc_loc + 1);
				sint lenforloc = (sint)statements_->length() - 1;

				if (sc_loc > 0)
				{
					sint last_sc_loc = statements_->find_last_of(";");

					if (last_sc_loc == lenforloc)
					{
						sint bpar_loc = 0;
						sint fpar_loc = statements_->find("(");
						sint pos_fpar_loc = fpar_loc;
						bool closed = true;
						sint fpars = 0;
						sint bpars = 0;

						while (pos_fpar_loc > 0 && pos_fpar_loc < sc_loc)
						{
							bool par;

							if (!LitEnc(pos_fpar_loc, &litlocs, statements_->c_str()))
							{
								par = true;
							}

							if (par)
							{
								fpars++;
							}

							bpar_loc = statements_->find(")", bpar_loc + 1);

							if (bpar_loc > pos_fpar_loc && bpar_loc < sc_loc)
							{
								par = true;

								if (!LitEnc(bpar_loc, &litlocs, statements_->c_str()))
								{
									par = true;
								}

								if (par)
								{
									bpars++;
								}
							}
							else
							{
								par = false;
							}

							pos_fpar_loc = statements_->find("(", pos_fpar_loc + 1);
						}

						if (bpars < fpars)
						{
							closed = false;
						}

						sint q_loc = statements_->find("'");
						bool sq = false;

						if (q_loc > 0 && q_loc < sc_loc)
						{
							sint quotes = 0;
							sint pos_q_loc = q_loc;

							if (!XEnclosedInY(&litlocs, statements_->c_str(), sc_loc, q_loc, '('))
							{
								if (LitEnc(q_loc, &litlocs, statements_->c_str()))
								{
									sq = true;
								}
							}
						}

						q_loc = statements_->find("\"");
						bool dq = false;

						if (q_loc > 0 && q_loc < sc_loc)
						{
							sint quotes = 0;
							sint pos_q_loc = q_loc;

							if (!XEnclosedInY(&litlocs, statements_->c_str(), sc_loc, q_loc, '('))
							{
								if (LitEnc(pos_fpar_loc, &litlocs, statements_->c_str()))
								{
									dq = true;
								}
							}
						}

						if ((!sq && !dq && closed))
						{
							std::string sep_str = statements_->substr(0, sc_loc + 1);
							vec_->push_back(sep_str);
							statements_->erase(0, sc_loc + 1);
							sc_loc = 0;
						}
					}
					else
					{
						done = true;
						vec_->push_back("FAIL2"); // for now, attempt a repair later when we can read statement content
					}
				} // i believe we.may not.reach done if there is a ; in quotes but no ; at the end
				else
				{
					done = true;
					vec_->push_back("FAIL3"); // found no semi colons
				}
			}
			else
			{
				done = true;
			}
		}

		if (debug_lvl >= 75 && debug_m)
		{
			for (uint ct = 0; ct < (sint)vec_->size(); ct++)
			{
				sint oc = Output(vec_->at(ct).c_str(), 2);
			}
			sint oc = Output("Separate SQL done.", 2);
		}
		return -1;
	}
	sint AnalyzeStmt(BOT_STMT *t_ = 0)
	{
		if (debug_lvl >= 110 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::AnalyzeStmt(BOT_STMT *t_(%i))", (sint)t_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && t_)
			{
				carr_4096 xutp;
				op = bot_sprintf(xutp.carr, xutp.siz, "stmt(\"%s\")", t_->stmt.c_str());
				op = Output(xutp.carr, 2);
			}
		}

		if (!t_)
		{
			return -1;
		}

		sint lim = -1;
		sint ele = -1;

		if (!t_->stmt.empty())
		{
			sint x = 0;
			sint findx = stool.FindVInStr(&sql_trans_keywords, t_->stmt.c_str(), &x, lim, &ele, lim);

			if (x > -1)
			{
				t_->it_type = ele;
			}
			else
			{
				if (debug_lvl >= 10 && debug_m)
				{
					sint oc = Output("found no type", 2);
				}
				return -1;
			}
		}
		else
		{
			return -1;
		}

		std::string snip;
		std::vector<size_t> litlocs;
		sint at_loc = LitLocs(&litlocs, t_->stmt.c_str());
		std::vector<size_t> o_locs;
		at_loc = OrdLocs(&litlocs, &o_locs, t_->stmt.c_str());
		sint last_targ_loc = -1;
		at_loc = 0;
		sint spec_loc = 0;
		sint x = (sint)strlen(sql_trans_keywords[t_->it_type]);
		ele = -1;
		sint findx = stool.FindVInStr(&sql_cspec_keywords, t_->stmt.c_str(), &spec_loc, lim, &ele, lim);
		findx = stool.FindVInStr(&sql_obj_qual_keywords, t_->stmt.c_str(), &x, lim, &ele, lim);

		if (x > -1)
		{
			t_->ospec = ele;
			x += (sint)strlen(sql_obj_qual_keywords[ele]);
		}
		else
		{
			x = (sint)strlen(sql_trans_keywords[t_->it_type]);
		}

		if (!o_locs.empty())
		{
			if (strlen(sql_trans_keywords[t_->it_type]) - 1 < o_locs[0])
			{
				snip.append(t_->stmt.substr(strlen(sql_trans_keywords[t_->it_type]), o_locs[0] - strlen(sql_trans_keywords[t_->it_type])));
			}
		}
		else
		{
			snip.append(t_->stmt);
		}

		if (snip.empty())
		{
			if (debug_lvl >= 1 && debug_m)
			{
				sint oc = Output("snip was empty(), snip here should be to first ordinal encloser or the whole stmt", 2);
			}
			return -1;
		}

		litlocs.clear();
		sint xv = LitLocs(&litlocs, snip.c_str());
		xv = 0;
		sint yv = 1;
		bool open = false;
		bool end_stmt = false;

		while (!snip.empty())
		{
			if (debug_lvl >= 110 && debug_m)
			{
				std::string output;
				output.append("snip: \"");
				output.append(snip);
				output.append("\"");
				sint oc = Output(output.c_str(), 2);
			}

			x = 0;
			sint altx = x;

			if (!open)
			{
				if (t_->it_type == 3 || t_->it_type == 5 || t_->it_type == 7 || t_->it_type == 9 || t_->it_type == 10)
				{
					findx = stool.FindVInStr(&sql_cond_qual_keywords, snip.c_str(), &altx, lim, &ele, lim);

					if (altx > -1)
					{
						t_->ifex = ele;
						altx += (sint)strlen(sql_cond_qual_keywords[ele]);
						x = altx;
					}
					else
					{
						altx = x;
					}

					findx = stool.FindVInStr(&sql_obj_keywords, snip.c_str(), &altx, lim, &ele, lim);

					if (altx > -1)
					{
						altx += (sint)strlen(sql_obj_keywords[ele]);
						x = altx;
					}
					else
					{
						altx = x;
					}
				}
				else if ((!t_->it_type || t_->it_type == 4) && altx < spec_loc)
				{
					findx = stool.FindInStr("FROM", snip.c_str(), altx, lim);

					if (findx > -1)
					{
						_char spc = ' ';
						_char term = '\0';

						while (!memcmp((void*)&snip[x], (void*)&spc, sizeof(spc)) && !memcmp((void*)&snip[x], (void*)&term, sizeof(term)) && x < (sint)snip.length())
						{
							x++;
						}

						altx = findx;
						findx = stool.FindInStr('*', snip.c_str(), x, altx);

						if (findx > -1)
						{
							sint xc = vtool.AddValToVec(&t_->fcols, snip.substr(findx, 1).c_str(), true, true);
						}
						else
						{
							for (findx = stool.FindInStr(',', snip.c_str(), x, altx); findx > -1 && findx < altx; findx = stool.FindInStr(',', snip.c_str(), x, altx))
							{
								while (!memcmp((void*)&snip[x], (void*)&spc, sizeof(spc)) && !memcmp((void*)&snip[x], (void*)&term, sizeof(term)) && x < (sint)snip.length())
								{
									x++;
								}

								sint xc = vtool.AddValToVec(&t_->fcols, CleanPunctuation(snip.substr(x, findx - x).c_str()).c_str(), true, true);
								x = findx + 1;
							}
							x = altx;
						}
					}
					else
					{
						altx = x;
					}
				}
				else {}

				findx = stool.FindVInStr(&sql_targ_keywords, snip.c_str(), &altx, lim, &ele, lim);

				if (altx > -1)
				{
					t_->targ = ele;
					altx += (sint)strlen(sql_targ_keywords[ele]);
					x = altx;
				}
				else
				{
					altx = x;
				}

				bool found_db = false;

				for (altx = snip.find('.', altx + 1); altx > -1 && altx < (sint)snip.length(); altx = snip.find('.', altx + 1))
				{
					if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, altx, sql_opers_keywords[6]))
					{
						found_db = true;
						std::string cont_name;
						x = altx;
						std::vector<std::string> nvec;
						sint ix = GetElementNames(MTX_DBL, &nvec);
						ix = (sint)nvec.size() - 1;

						while (ix > -1)
						{
							sint loc = altx - (sint)strlen(nvec[ix].c_str());

							if (debug_lvl >= 110 && debug_m)
							{
								carr_256 outp;
								sint op = bot_sprintf(outp.carr, outp.siz, "searching for:\"%s\" from:%i x:%i", nvec[ix].c_str(), loc, x);
								op = Output(outp.carr, 2);
							}

							if (loc > -1 && loc < x)
							{
								sint nloc = snip.find(nvec[ix], loc);

								if (loc == nloc)
								{
									t_->AddDB(nvec[ix].c_str());
									nloc = altx + 1;
									findx = stool.FindVInStr(&sql_opers_keywords, snip.c_str(), &nloc, lim, &ele, lim);
									BOT_DB ndb(nvec[ix].c_str());
									ix = GetInVec((void*)&ndb, MTX_DBL, false, false);
									ix = (sint)ndb.tables.size() - 1;

									while (ix > -1)
									{
										loc = snip.find(ndb.tables[ix], altx + 1);

										if (loc == altx + 1)
										{
											if (nloc > altx && nloc < loc && ele == 4)
											{
												cont_name.append(snip.substr(loc, strlen(ndb.tables[ix].c_str())));
											}
											ix = -1;
										}
										ix--;
									}

									if (ix == -1 && nloc > -1)
									{
										loc = snip.find(']', nloc + 1);

										if (loc > nloc)
										{
											cont_name.append(nloc + 1, (loc - (nloc + 1)));
										}
									}
									ix = -1;
									// get tables for this db
								}
							}
							ix--;
						}

						if (ix == -1)
						{
							std::string str;
							str.append(snip.substr(0, altx).c_str());
							t_->AddDB(CleanPunctuation(str.c_str()).c_str());
						}

						if (altx + 1 < (sint)snip.length())
						{
							sint loc = snip.find('[', altx + 1);

							if (loc > -1)
							{
								loc = snip.find(']', altx + 1);

								if (loc > -1)
								{
									cont_name.append(snip.substr(altx + 1, loc - (altx + 1)).c_str());
								}
								else
								{
									sint ix = altx + 1;
									findx = stool.FindVInStr(&sql_opers_keywords, &snip, &ix, lim, &ele, lim);

									if (ix > -1)
									{
										std::string str;
										str.append(snip.substr(altx + 1, ix - (altx + 1)).c_str());
										cont_name.append(CleanPunctuation(str.c_str()));
									}
								}
							}
							else
							{
								sint ix = altx + 1;
								findx = stool.FindVInStr(&sql_opers_keywords, &snip, &ix, lim, &ele, lim);

								if (ix > -1)
								{
									std::string str;
									str.append(snip.substr(altx + 1, ix - (altx + 1)).c_str());
									cont_name.append(CleanPunctuation(str.c_str()).c_str());
								}
								else
								{
									std::string str;
									str.append(snip.substr(altx + 1, (sint)snip.length() - (altx + 1)).c_str());
									cont_name.append(CleanPunctuation(str.c_str()).c_str());
								}
							}
						}

						if (cont_name.empty())
						{
							sint dx = VecSize(MTX_DBL) - 1;
							while (dx > -1)
							{
								BOT_DB ndb;
								ix = GetVecEle(&ndb, MTX_DBL, dx, false);
								ix = vtool.ValInVec(&ndb.tables, snip.substr(1, snip.length() - 2).c_str());

								if (ix > -1)
								{
									if (!strcmp(t_->dbname.c_str(), ndb.name.c_str()))
									{
										t_->AddDB(ndb.name.c_str());
									}
									cont_name.append(snip.substr(1, snip.length() - 2).c_str());
									dx = -1;
								}
								dx--;
							}
						}
						ix = t_->AddCont(cont_name.c_str(), 1);
					}
				}

				if (!found_db && t_->dbname.empty())
				{
					sint cloc = -1;
					findx = stool.FindVInStr(&sql_cspec_keywords, snip.c_str(), &cloc, lim, &ele, lim);
					std::string cont_name;
					altx = snip.find('[', x + 1);

					if (altx > -1 && (altx < spec_loc || spec_loc == -1))
					{
						sint ex = snip.find(']', altx + 1);

						if (ex > -1)
						{
							cont_name.append(snip.substr(altx + 1, ex - (altx + 1)).c_str());
						}
						else
						{
							ex = altx + 1;
							findx = stool.FindVInStr(&sql_opers_keywords, &snip, &ex, lim, &ele, lim);

							if (ex > -1)
							{
								cont_name.append(snip.substr(altx + 1, ex - (altx + 1)).c_str());
							}
						}
					}
					else
					{
						altx = x + 1;
						findx = stool.FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);

						if (altx > -1 && altx != cloc)
						{
							cont_name.append(snip.substr(x + 1, altx - (x + 1)).c_str());
							cont_name = CleanPunctuation(cont_name.c_str());
						}
					}
					if (cont_name.empty() && cloc < 0)
					{
						for (sint dx = VecSize(MTX_DBL) - 1; dx > -1; dx--)
						{
							BOT_DB ndb;
							sint ix = GetVecEle(&ndb, MTX_DBL, dx, false);
							ix = vtool.ValInVec(&ndb.tables, snip.substr(1, snip.length() - 2).c_str());

							if (ix > -1)
							{
								if (!strcmp(t_->dbname.c_str(), ndb.name.c_str()))
								{
									t_->AddDB(ndb.name.c_str());
								}
								cont_name.append(snip.substr(1, snip.length() - 2).c_str());
								dx = -1;
							}
						}

						sint dx = t_->AddCont(cont_name.c_str(), 1);
					}
				}

				findx = stool.FindVInStr(&sql_cspec_keywords, snip.c_str(), &altx, lim, &ele, lim);

				if (altx > -1)
				{
					spec_loc = at_loc + altx;
					t_->cspec = ele;
					altx += (sint)strlen(sql_cspec_keywords[ele]);
					x = altx;

					if (ele == 0)
					{
						std::string cond;

						while (altx > -1)
						{
							findx = stool.FindVInStr(&sql_comp_keywords, snip.c_str(), &altx, lim, &ele, lim);

							if (altx > -1)
							{
								cond.append(snip.substr(x + 1, altx - (x + 1)).c_str());
								cond.append(sql_comp_keywords[ele]);
								altx += (sint)strlen(sql_comp_keywords[ele]);
								x = altx;

								if (ele == 0)
								{
									altx = snip.find("AND", altx + 1);

									if (altx > -1)
									{
										cond.append(snip.substr(x, altx - x).c_str());
										cond.append("AND");
										altx += 3;
										x = altx;
										findx = stool.FindVInStr(&sql_comp_keywords, snip.c_str(), &altx, lim, &ele, lim);

										if (altx > -1)
										{
											cond.append(snip.substr(x, altx - x).c_str());
											cond.append(sql_comp_keywords[ele]);
										}
										else
										{
											altx = x;
										}
									}
									else
									{
										altx = x;
									}
								}

								findx = stool.FindVInStr(&sql_conj_keywords, snip.c_str(), &altx, lim, &ele, lim);

								if (altx > -1)
								{
									cond.append(snip.substr(x, altx - x).c_str());
									cond.append(sql_conj_keywords[ele]);
									altx += (sint)strlen(sql_conj_keywords[ele]);
									x = altx;
								}
								else
								{
									cond.append(snip.substr(x, (sint)snip.length() - (x + 1)).c_str());
								}
							}
							else
							{
								altx = x;
							}
						}
						if (!cond.empty())
						{
							t_->conds.push_back(cond);
						}
					}
					else if (ele == 1)
					{
						if (t_->it_type == 3)
						{

						}
						else if (t_->it_type == 9)
						{
							findx = stool.FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);

							if (altx > -1)
							{
								t_->dbalias.append(snip.substr(x + 1, altx - (x + 1)).c_str());
							}
							else
							{
								altx = x;
							}
						}
						else {}
					}
					else if (ele == 2)
					{
						t_->cspec = ele;
						/* we only use VALUES for INSERT INTO afaik, for BTS() we should only need to know t_->it_type == 2 and that we have listed all our columns,
						or we are missing a ( or ) for our values*/
					}
					else {}
				}
				else
				{
					altx = x;
				}
			}
			else
			{
				if (snip[x] == '[')
				{
					if (at_loc > last_targ_loc && spec_loc > at_loc)
					{
						x++;
						findx = stool.FindVInStr(&sql_cspec_keywords, snip.c_str(), &x, lim, &ele, lim); // needs sint pointers for which vector member and location in str

						if (x > -1)
						{
							if (LitEnc(x, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, x, sql_opers_keywords[6]))
							{
								spec_loc = at_loc + x;
								x += (sint)strlen(sql_cspec_keywords[ele]);
								t_->cspec = ele;

								if (ele == 0)
								{
									findx = stool.FindVInStr(&sql_opers_keywords, &snip, &x, lim, &ele, lim);

									while (x > -1)
									{
										if (LitEnc(x, &litlocs, snip.c_str()))
										{
											if (ele == 1)
											{

											}
											else if (ele == 2 || ele == 3)
											{
												sint nloc = snip.find(sql_opers_keywords[ele], x + 1);

												if (nloc > -1)
												{
													std::string str;
													str.append(snip.substr(x, nloc - x).c_str());
													x = nloc + 1;
													findx = stool.FindVInStr(&sql_comp_keywords, snip.c_str(), &x, lim, &ele, lim, true, false);

													if (x > -1)
													{

													}
												}
											}
											else if (ele == 4 || ele == 5)
											{
												// unless in another statement or in a value we should not run across one of these
											}
											else if (ele == 6 || ele == 7)
											{
												sint nloc = x;

												if (ele == 7)
												{
													nloc--;
													for (nloc = stool.FindInStr(sql_opers_keywords[6], snip.c_str(), nloc, lim); nloc > -1; )
													{
														if (LitEnc(x, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, x, sql_opers_keywords[6]))
														{
															vtool.AddValToVec(&t_->conds, snip.substr(nloc, x - nloc).c_str(), false, false);
															nloc = -1;
														}
														else
														{
															nloc--;
															nloc = stool.FindInStr(sql_opers_keywords[6], snip.c_str(), nloc, lim);
														}
													}
												}
												else
												{
													for (nloc = snip.find(sql_opers_keywords[7], nloc + 1); nloc > -1; )
													{
														if (LitEnc(x, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, x, sql_opers_keywords[6]))
														{
															sint addv = vtool.AddValToVec(&t_->conds, snip.substr(nloc, x - nloc).c_str(), true, true);
															nloc = -1;
														}
														else
														{
															nloc = snip.find(sql_opers_keywords[7], (size_t)nloc - 1);
														}
													}
												}
											}
											else if (ele == 8 || ele == 9)
											{
												std::string ncar;
												ncar.push_back(sql_opers_keywords[ele]);
												sint addv = vtool.AddValToVec(&t_->conds, ncar.c_str(), true, true);

											}
											else if (ele == 10)
											{
												// commas if not in an enclosed stmt or literal value after a WHERE are out of place
											}
											else if (ele == 11)
											{
												// if not enclosed this ends our statement or is out of place
											}
											else {}
										}

										x++;
										findx = stool.FindVInStr(&sql_opers_keywords, &snip, &x, lim, &ele, lim);

										if (x < (sint)snip.length())
										{
											sint clox = x + 1;
											findx = stool.FindVInStr(&sql_conj_keywords, snip.c_str(), &clox, lim, &ele, lim);

											if (clox > -1 && clox < x)
											{
												if (LitEnc(clox, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, clox, sql_opers_keywords[6]))
												{
													if (ele == 1)
													{

													}
													else if (ele == 2)
													{

													}
													else if (ele == 3)
													{

													}
													else {}

													x = clox + 1;
												}
											}
										}

										findx = stool.FindVInStr(&sql_opers_keywords, &snip, &x, lim, &ele, lim);
									}

								}
								else if (ele == 1)
								{

								}
								else if (ele == 2)
								{

								}
								else {}
							}
						}
					}
					else
					{
						if (snip[snip.length() - 1] == ']' && snip.length() > 2)
						{
							std::string cont_name;

							if (t_->dbname.empty())
							{
								for (sint dx = VecSize(MTX_DBL) - 1; dx > -1; dx--)
								{
									BOT_DB ndb;
									sint ix = GetVecEle(&ndb, MTX_DBL, dx, false);

									if (ix > -1)
									{
										ix = vtool.ValInVec(&ndb.tables, snip.substr(1, snip.length() - 2).c_str());

										if (ix > -1)
										{
											if (!strcmp(t_->dbname.c_str(), ndb.name.c_str()))
											{
												ix = t_->AddDB(ndb.name.c_str());
											}
											cont_name.append(snip.substr(1, snip.length() - 2).c_str());
											dx = -1;
										}
									}
								}
							}

							if (!cont_name.empty())
							{
								sint dx = t_->AddCont(cont_name.c_str(), 1);
							}
							last_targ_loc = at_loc + x;
						}
						else
						{
							//empty bracket '[]'
						}
					}
				}
				else if (snip[x] == '(')
				{
					// if t_->cspec > -1 and we are past last_targ_loc and spec_loc we can assume these () contain a condition
					if (snip[snip.length() - 1] == ')')
					{
						if (t_->cspec > -1)
						{
							if (at_loc < spec_loc)
							{
								for (findx = stool.FindInStr(',', snip.c_str(), x, (sint)snip.length() - 1); findx > -1; findx = stool.FindInStr(',', snip.c_str(), x, (sint)snip.length() - 1))
								{
									sint xc = vtool.AddValToVec(&t_->fcols, CleanPunctuation(snip.substr(x, findx - x).c_str()).c_str(), true, true);
									x = findx + 1;
								}
							}
							else
							{
								if (!t_->cspec)
								{
									if (strlen(snip.c_str()) < 1024)
									{
										sint xp = vtool.AddValToVec(&t_->conds, snip.c_str(), true, true);
									}
									
								}
								else
								{
									std::string str;
									str.append(snip.substr(1, snip.length() - 2).c_str());
									snip.clear();
									snip.append(str);
								}
							}
							x = (sint)snip.length() - 1;
						}
						else
						{
							std::string str;
							str.append(snip.substr(1, snip.length() - 2).c_str());
							snip.clear();
							snip.append(str);
						}

						if (debug_lvl >= 110 && debug_m)
						{
							std::string output;
							if (t_->cspec > -1)
							{
								if (t_->cspec > 0)
								{
									output.append("snipped () at ends ");
								}

								output.append("t_->cspec > -1");
							}
							else
							{
								output.append("snipped () at ends");
							}
							sint oc = Output(output.c_str(), 2);
						}
					}
					else
					{
						if (debug_lvl >= 110 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "%c at 0, %c at end", snip[0], snip[snip.length() - 1]);
							op = Output(outp.carr, 2);
						}
					}

					findx = stool.FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);

					while (altx > -1)
					{
						if (ele == 1)
						{
							if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, altx, sql_opers_keywords[6]))
							{

								if (t_->cols.empty())
								{
									std::string str;
									str.push_back(sql_opers_keywords[ele]);
									t_->cols.push_back(str);
								}
							}
						}
						else if (ele == 2 || ele == 3)
						{

						}
						else if (ele == 4 || ele == 5)
						{

						}
						else if (ele == 6 || ele == 7)
						{
							if (ele == 7)
							{
								if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, altx, sql_opers_keywords[6]))
								{
									sint locx = stool.FindInStr(sql_opers_keywords[6], snip.c_str(), altx - 1, lim);

									if (locx > -1)
									{
										if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, locx, sql_opers_keywords[6]))
										{
											// we have likely found the closer containing variables for a function between x and locx.
											// we need to make sure there are no openers or closers in between
										}
									}
									else
									{
										// there is a stray ')' in this enclosed snip
									}
								}
							}
							else
							{
								if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, altx, sql_opers_keywords[6]))
								{
									sint locx = snip.find(sql_opers_keywords[7], altx + 1);

									if (locx > -1)
									{
										if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, locx, sql_opers_keywords[6]))
										{
											// we have likely found the closer containing variables for a function between x and locx.
										}
									}
									else
									{
										// there is a stray '(' in this enclose snip
									}
								}
							}
						}
						else if (ele == 8 || ele == 9)
						{

						}
						else if (ele == 10)
						{
							while (altx > -1)
							{
								if (LitEnc(altx, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, altx, sql_opers_keywords[6]))
								{
									if (at_loc < spec_loc || spec_loc == -1)
									{
										while (snip[x] == ' ') { x++; }
										if (debug_lvl >= 110 && debug_m)
										{
											carr_256 outp;
											sint op = bot_sprintf(outp.carr, outp.siz, "pushing to cols:\"%s\" strlen()=%u sizeof()=%u", snip.substr(x, altx - x).c_str(), strlen(snip.substr(x, altx - x).c_str()), sizeof(snip.substr(x, altx - x).c_str()));
											op = Output(outp.carr, 2);
										}
										t_->cols.push_back(snip.substr(x, altx - x));
									}
									else
									{
										while (snip[x] == ' ') { x++; }
										if (debug_lvl >= 110 && debug_m)
										{
											carr_256 outp;
											sint op = bot_sprintf(outp.carr, outp.siz, "pushing to vals:\"%s\" strlen()=%u sizeof()=%u", snip.substr(x, altx - x).c_str(), strlen(snip.substr(x, altx - x).c_str()), sizeof(snip.substr(x, altx - x).c_str()));
											op = Output(outp.carr, 2);
										}
										t_->vals.push_back(snip.substr(x, altx - x));
									}
									x = altx + 1;
								}

								altx = snip.find(sql_opers_keywords[ele], x);

								if (altx == -1)
								{
									if (at_loc < spec_loc || spec_loc == -1)
									{
										t_->cols.push_back(snip.substr(x + 1, (sint)snip.length() - (x + 1)));
									}
									else
									{
										t_->vals.push_back(snip.substr(x + 1, (sint)snip.length() - (x + 1)));
									}
								}
							}
						}
						else if (ele == 11)
						{

						}
						else {}

						if (altx > -1)
						{
							altx++;
							findx = stool.FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);
						}
					}
				}
				else if (snip[x] == '\'')
				{
					altx = snip.find(snip[x], x + 1);

					if (altx > -1)
					{
						t_->vals.push_back(snip.substr(x, (altx + 1) - x));
						x = altx + 1;
					}
				}
				else if (snip[x] == '"')
				{
					altx = snip.find(snip[x], x + 1);

					if (altx > -1)
					{
						t_->vals.push_back(snip.substr(x, (altx + 1) - x));
						x = altx + 1;
					}
				}
				else {}
			}

			if (yv < (sint)o_locs.size())
			{
				snip.clear();

				if (!open)
				{
					snip.append(t_->stmt.substr(o_locs[xv], (o_locs[yv] + 1) - o_locs[xv]));
					at_loc = o_locs[xv];
					open = true;
				}
				else
				{
					snip.append(t_->stmt.substr(o_locs[xv] + 1, o_locs[yv] - (o_locs[xv] + 1)).c_str());
					at_loc = o_locs[xv] + 1;
					open = false;
				}

				if (debug_lvl >= 110 && debug_m)
				{
					carr_256 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "snipping from:%u to:%u len=%u at_loc=%i spec_loc=%i open(%u)", o_locs[xv], o_locs[yv], o_locs[yv] - o_locs[xv], at_loc, spec_loc, (uint)open);
					op = Output(outp.carr, 2);
				}

				if (!snip.empty())
				{
					if (snip[snip.length() - 1] == ';')
					{
						snip.pop_back();
					}
					litlocs.clear();
					LitLocs(&litlocs, snip.c_str());
				}
				yv++;
				xv++;
			}
			else
			{
				snip.clear();
			}
		}
		if (!t_->stmt.empty())
		{
			t_->stmt.clear();
		}
		t_->an = true;

		if (debug_lvl >= 110 && debug_m)
		{
			sint oc = OutpuTINFO(t_);
		}
		return 0;
	}
	sint BQS(BOT_STMT *t_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_64 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::BQS(BOT_STMT *t_(%i))", (sint)t_);
			oc = Output(outp.carr, 2);
		}

		if (!t_)
		{
			return -1;
		}

		if (t_->it_type > 0)
		{
			sint xc = BTS(t_);
			return xc;
		}
		else if (!t_->it_type)
		{

		}
		else
		{
			return -1;
		}

		if (t_->ic_type < 0)
		{
			return -1;
		}

		if (!t_->stmt.empty() && !t_->an)
		{
			sint xc = AnalyzeStmt(t_);

			if (xc)
			{

				xc = -1;
			}
		}

		std::string statement;
		statement.append("SELECT ");

		if (t_->fcols.empty())
		{
			statement.append("*");
		}
		else
		{
			for (uint x = 0; x < t_->fcols.size(); x++)
			{
				statement.append(t_->fcols[x].c_str());
				statement.append(", ");
			}
			statement.pop_back();
		}

		statement.append(" FROM ");

		if (t_->ic_type == 1)
		{
			if (d_con_)
			{
				if (strcmp(t_->dbname.c_str(), d_con_->name.c_str()))
				{
					statement.append(t_->dbname.c_str());
					statement.append(".");
				}
				if (!t_->cont.empty())
				{
					statement.append("[");
					statement.append(t_->cont.c_str());
					statement.append("]");
				}
				else
				{
					statement.clear();
					return -1;
				}
			}
			else
			{
				if (!t_->cont.empty())
				{
					statement.append("[");
					statement.append(t_->cont.c_str());
					statement.append("]");
				}
			}
		}
		else { return -1; }

		statement.append(" ");
		uint x = 0;

		if (t_->cspec > -1 && (!t_->vals.empty() || !t_->cols.empty() || !t_->conds.empty()))
		{
			statement.append(sql_cspec_keywords[t_->cspec]);
			statement.append(" ");

			if (!t_->conds.empty())
			{
				for (uint xc = 0; xc < t_->conds.size(); xc++)
				{
					statement.append(t_->conds[xc].c_str());
					statement.append(" ");
				}
			}
		}

		if (t_->opts[0] > -1 && x < t_->cols.size())
		{
			statement.append(sql_decl_keywords[t_->opts[0]]);
			statement.append(t_->cols[x].c_str());
			x++;
			statement.append(sql_order_keywords[t_->opts[1]]);
		}

		if (t_->rlim > 0)
		{
			statement.append(" LIMIT ");
			statement.append(stool.ITOA(t_->rlim).c_str());
		}

		if (!statement.empty())
		{
			_char spc = ' ';

			while (!memcmp((void*)&statement[statement.size() - 1], (void*)&spc, sizeof(spc)))
			{
				statement.pop_back();
			}
			statement.append(";");
			t_->stmt.append(statement.c_str());

			if (t_->stmt.length() > 15) //SELECT * FROM ; 15 chars for an empty statement
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string outp;
					outp.append("Query Statement:");
					outp.append(statement.c_str());
					sint oc = Output(outp.c_str(), 2);
				}
				return 0;
			}
		}
		if (debug_lvl >= 10 && debug_m)
		{
			std::string outp;
			outp.append("Failed to build query statement:");
			outp.append(statement.c_str());
			sint oc = Output(outp.c_str(), 2);
		}
		return -1;
	}
	sint BTS(BOT_STMT *t_ = 0)
	{
		if (debug_lvl >= 500 && debug_m)
		{
			carr_64 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::BTS(BOT_STMT *t_(%i))", (sint)t_);
			oc = Output(outp.carr, 2);
		}

		if (!t_)
		{
			return -1;
		}

		if (!t_->it_type || !strcmp(sql_trans_keywords[t_->it_type], "SELECT"))
		{
			sint xc = BQS(t_);
			return xc;
		}

		std::string statement;
		statement.append(sql_trans_keywords[t_->it_type]);

		if (t_->it_type == 3 || t_->it_type == 5 || t_->it_type == 7)
		{
			if (t_->ospec > -1)
			{
				statement.append(" ");
				statement.append(sql_obj_qual_keywords[t_->ospec]);
			}

			statement.append(" ");
			statement.append(sql_obj_keywords[t_->ic_type]);
		}

		if (t_->ifex > -1)
		{
			statement.append(" ");
			statement.append(sql_cond_qual_keywords[t_->ifex]);
		}

		if (t_->it_type == 4 && t_->ic_type > 1)
		{
			statement.append(" ");
			statement.append(sql_targ_keywords[1]);
		}

		if (t_->cont.empty())
		{
			if (!t_->dbname.empty() && t_->it_type == 9)
			{
				statement.clear();
				carr_512 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "%s %s AS %s;", sql_trans_keywords[t_->it_type], t_->dbname.c_str(), t_->dbname.c_str());
				statement.append(outp.carr);
			}
		}
		else
		{
			statement.append(" ");

			if (d_con_)
			{
				if (!strcmp(t_->dbname.c_str(), d_con_->name.c_str()))
				{
					sint fx = t_->cont.find('.', 0);
					
					if (fx > -1)
					{
						fx++;
						std::string str;
						str.append(t_->cont.substr(fx, t_->cont.length() - fx));
						t_->cont.clear();
						t_->cont.append(str.c_str());
					}
				}
				else
				{
					statement.append(t_->dbname);
					statement.append(".");
				}
			}
			if (t_->ic_type > 0)
			{
				std::string s;

				if (t_->cont[0] != '[')
				{
					if (t_->ic_type == 2)
					{
						s.append("[IDX");
					}
					else
					{
						s.push_back('[');
					}
				}
				s.append(t_->cont);

				if (t_->cont[(sint)strlen(t_->cont.c_str()) - 1] != ']')
				{
					s.push_back(']');
				}

				if (t_->it_type < 9)
				{
					statement.append(s);
				}
			}
			else
			{
				if (t_->dbname.empty()) { return -1; }
			}

			if (t_->it_type == 6)
			{
				statement.pop_back();
			}

			if (t_->it_type == 3 && t_->ic_type == 2)
			{
				statement.append(" ");
				statement.append(sql_targ_keywords[2]);
				statement.append(" [");
				statement.append(t_->cont);
				statement.append("]");
			}

			if (t_->it_type < 4)
			{
				if (t_->it_type < 3)
				{
					if (t_->maint)
					{
						if (t_->ic_type > 0)
						{
							sllint xc = GetCentSec();
							sint xp = t_->AddCol("LAST_MAINTAINED", stool.LLITOA(xc).c_str());
						}

						if (t_->it_type != 3 && t_->ic_type > 0)
						{

#ifdef _WIN32
							SYSTEMTIME tim; // use chrono
							GetSystemTime(&tim);
							sint xc = t_->AddCol("LAST_MAINTAINED_NS", stool.LLITOA(tim.wMilliseconds * 1000000).c_str());
#else
							struct timespec ti;
							sint xc = clock_gettime(CLOCK_REALTIME, &ti);
							xc = t_->AddCol("LAST_MAINTAINED_NS", stool.LLITOA((sllint)ti.tv_nsec).c_str());
#endif

						}
					}
					else
					{
						if (t_->ic_type > 0)
						{
							sllint xc = GetCentSec();
							sint xp = t_->AddCol("LAST_MODIFIED", stool.LLITOA(xc).c_str());
						}

						if (t_->ic_type > 0)
						{

#ifdef _WIN32
							SYSTEMTIME tim;
							GetSystemTime(&tim);
							sint xc = t_->AddCol("LAST_MODIFIED_NS", stool.LLITOA(tim.wMilliseconds * 1000000).c_str());
#else
							struct timespec ti;
							sint xc = clock_gettime(CLOCK_REALTIME, &ti);
							xc = t_->AddCol("LAST_MODIFIED_NS", stool.LLITOA(ti.tv_nsec).c_str());
#endif

						}
					}
				}
				else if (t_->it_type == 3)
				{
					if (t_->cols.size())
					{
						statement.append(" ( ");

						for (uint x = 0; x < t_->cols.size(); x++)
						{
							statement.append(t_->cols[x]);
							statement.append(" ");

							if (t_->ic_type == 2)
							{
								statement.pop_back();
								statement.append(", ");
							}

							if (x < t_->vals.size())
							{
								if (t_->ic_type != 2)
								{
									statement.append(t_->vals[x]);
									statement.append(", ");
								}
							}
						}

						statement.erase(statement.length() - 2, 2);
						statement.append(" )");
					}
				}
				else {}
			}

			if (t_->act > -1)
			{
				statement.append(" ");
				statement.append(sql_act_keywords[t_->act]);

				if (t_->it_type == 7)
				{
					if (t_->ic_type == 1 && t_->act == 1)
					{
						statement.append(" TABLE");
					}
					else if (t_->ic_type == 2 && t_->act == 0)
					{
						statement.append(" COLUMN");
					}
					else if (t_->ic_type == 4)
					{
						statement.append(" TRIGGER");
					}
					else {}
				}

				sint x = 0;

				switch (t_->act)
				{
				case 0:
				{
					if (t_->vals.size() && t_->cols.size())
					{
						while (x < (sint)t_->cols.size() && x < (sint)t_->vals.size())
						{
							carr_256 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, " %s = %s, ", t_->cols[x].c_str(), t_->vals[x].c_str());
							statement.append(outp.carr);
							x++;
						}
						statement.pop_back();
						statement.pop_back();
					}
					break;
				}
				case 1:
				{
					if (t_->vals.size() && t_->cols.size())
					{
						while (x < (sint)t_->cols.size() && x < (sint)t_->vals.size())
						{
							carr_256 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, " %s %s, ", t_->cols[x].c_str(), t_->vals[x].c_str());
							statement.append(outp.carr);
							x++;
						}
						statement.pop_back();
						statement.pop_back();
					}
					break;
				}
				case 2:
				{
					statement.append(" [");

					if (x < (sint)t_->vals.size())
					{
						statement.append(t_->vals[x]);
					}
					statement.append("]");
					break;
				}
				default:
				{
					break;
				}
				}
			}

			if (t_->cspec > -1)
			{
				if (t_->cspec == 0)
				{
					statement.append(" ");
					statement.append(sql_cspec_keywords[t_->cspec]);

					for (uint x = 0; x < t_->conds.size(); x++)
					{
						statement.append(" ");
						statement.append(t_->conds[x]);
					}
				}
				else if (t_->cspec == 2)
				{
					if (t_->cols.size() == t_->vals.size())
					{
						statement.append(" ( ");

						for (uint x = 0; x < t_->cols.size(); x++)
						{
							statement.append(t_->cols[x]);
							statement.append(", ");
						}

						statement.pop_back();
						statement.pop_back();
						statement.append(" ) VALUES ( ");

						for (uint x = 0; x < (sint)t_->vals.size(); x++)
						{
							statement.append(t_->vals[x]);
							statement.append(", ");
						}

						statement.pop_back();
						statement.pop_back();
						statement.append(" )");
					}
					else
					{
						carr_64 outp;
						sint op = bot_sprintf(outp.carr, outp.siz, "columns(%u) vals(%u) mismatch.", t_->cols.size(), t_->vals.size());
						op = Output(outp.carr, 2);
						return 1;
					}
				}
				else {}
			}
			else if (t_->it_type == 2)
			{
				if (t_->cols.size() == t_->vals.size())
				{
					statement.append(" ( ");

					for (uint x = 0; x < t_->cols.size(); x++)
					{
						statement.append(t_->cols[x]);
						statement.append(", ");
					}

					statement.pop_back();
					statement.pop_back();
					statement.append(" ) VALUES ( ");

					for (uint x = 0; x < t_->vals.size(); x++)
					{
						statement.append(t_->vals[x]);
						statement.append(", ");
					}
					statement.pop_back();
					statement.pop_back();
					statement.append(" )");
				}
				else
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "columns(%u) vals(%u) mismatch.", t_->cols.size(), t_->vals.size());
					op = Output(outp.carr, 2);
					return 1;
				}
			}
			else {}

			/*if (!t_->opts[11].empty())
			{
				BOT_STMT trans;
				trans.dbname.append(t_->dbname.c_str());

				if (t_->vals.size())
				{
					sint xc = vtool.AddValToVec(&trans.tables, t_->vals[0].c_str());
					for (xc = 1; xc < (sint)t_->vals.size(); xc++)
					{
						sint nc = vtool.AddValToVec(&trans.cols, t_->vals[xc].c_str());
					}
				}

				trans.ic_types = t_->ic_types;
				trans.it_type = t_->opts[11][0];

				if (t_->opts[11].size() > 1)
				{
					trans.cspec = t_->opts[11][1];
				}

				if (!t_->conds.empty())
				{
					for (uint xc = 0; xc < t_->conds.size(); xc++)
					{
						sint nc = vtool.AddValToVec(&trans.conds, t_->conds[xc].c_str());
					}
				}

				trans.cols = t_->cols;
				sint xc = BQS(&trans);
				statement.append(" ");
				statement.append(trans.stmt);
				statement.pop_back();
			}*/
		}
		statement.append(";");

		if (debug_lvl >= 500 && debug_m)
		{
			std::string outp;
			outp.append("t_->stmt(");
			outp.append(statement.c_str());
			outp.append(")");
			sint oc = Output(outp.c_str(), 2);
		}

		if (!t_->stmt.empty())
		{
			t_->stmt.clear();
		}
		t_->stmt.append(statement);

		if (t_->stmt.length() > 6)
		{
			return 0;
		}
		return -1;
	}
	sint BuildStatements(std::vector<BOT_STMT>* stmts_ = 0, BOT_COMMIT *com_ = 0, std::vector<BOT_STMT>* pend_ = 0)
	{
		if (debug_lvl >= 500 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::BuildStatements((std::vector<BOT_STMT>* stmts_(%i), BOT_COMMIT *com_)(%i), std::vector<BOT_STMT>* pend_(%i))", (sint)stmts_, (sint)com_, (sint)pend_);
			op = Output(outp.carr, 2);
		}

		if (!com_ || !stmts_)
		{
			return -1;
		}

		std::vector<BOT_STMT> ncrts;
		std::vector<std::string> vec;
		std::vector<sint> db_maint;
		std::vector<std::vector<std::string>> cont_names;
		cont_names.push_back(vec);

		if (pend_)
		{
			for (uint i = 0; i < pend_->size(); i++)
			{
				sint xc = -1;

				if (!pend_->at(i).an && !pend_->at(i).stmt.empty())
				{
					xc = AnalyzeStmt(&pend_->at(i));
				}
				else
				{
					if (pend_->at(i).lid > -1)
					{
						xc = 0;
					}
				}
				if (!xc)
				{
					sint dx = vtool.ValInVec(&com_->dbs, pend_->at(i).dbname.c_str());

					if (dx < 0)
					{
						BOT_DB_M ndb(pend_->at(i).dbname.c_str());
						dx = vtool.AddValToVec(&com_->dbs, &ndb, false, false);

						if (dx > -1)
						{
							cont_names.push_back(vec);
							db_maint.push_back(0);

							if (pend_->at(i).maint)
							{
								db_maint[dx] = 1;
							}

							dx = OpenOpt(pend_->at(i).it_type);

							if (dx > com_->opt)
							{
								com_->opt = dx;
							}

							sint nx = vtool.AddValToVec(&cont_names[cont_names.size() - 1], &pend_->at(i).cont, true, false);

							if (!dx || dx > 2)
							{
								dx = vtool.AddValToVec(&com_->t, &pend_->at(i), true, true);
							}
							else
							{
								dx = vtool.AddValToVec(&ncrts, &pend_->at(i), true, true);
							}
						}
					}
					else
					{
						if (!pend_->at(i).maint)
						{
							db_maint[dx] = 0;
						}

						xc = OpenOpt(pend_->at(i).it_type);

						if (xc > com_->opt)
						{
							com_->opt = xc;
						}

						sint nc = vtool.AddValToVec(&cont_names[dx], &pend_->at(i).cont, true, false);
						if (!xc || xc > 2)
						{
							xc = vtool.AddValToVec(&com_->t, &pend_->at(i), true, true);
						}
						else
						{
							xc = vtool.AddValToVec(&ncrts, &pend_->at(i), true, true);
						}
					}
					pend_->at(i).Clear();
				}
			}
			sint xc = vtool.CleanVec(pend_);
		}

		for (uint i = 0; i < stmts_->size(); i++)
		{
			sint xc = -1;
			if (!stmts_->at(i).an && !stmts_->at(i).stmt.empty())
			{
				xc = AnalyzeStmt(&stmts_->at(i));
			}
			else
			{
				if (stmts_->at(i).lid > -1)
				{
					xc = 0;
				}
			}
			if (!xc)
			{
				sint dx = vtool.ValInVec(&com_->dbs, stmts_->at(i).dbname.c_str());

				if (dx < 0)
				{
					BOT_DB_M ndb(stmts_->at(i).dbname.c_str());
					dx = vtool.AddValToVec(&com_->dbs, &ndb, false, false);

					if (dx > -1)
					{
						cont_names.push_back(vec);
						db_maint.push_back(0);

						if (stmts_->at(i).maint)
						{
							db_maint[dx] = 1;
						}

						dx = OpenOpt(stmts_->at(i).it_type);

						if (dx > com_->opt)
						{
							com_->opt = dx;
						}

						sint nx = vtool.AddValToVec(&cont_names[cont_names.size() - 1], &stmts_->at(i).cont, true, false);

						if (!dx || dx > 2)
						{
							dx = vtool.AddValToVec(&com_->t, &stmts_->at(i), true, true);
						}
						else
						{
							dx = vtool.AddValToVec(&ncrts, &stmts_->at(i), true, true);
						}
					}
				}
				else
				{
					if (!stmts_->at(i).maint)
					{
						db_maint[dx] = 0;
					}

					xc = OpenOpt(stmts_->at(i).it_type);

					if (xc > com_->opt)
					{
						com_->opt = xc;
					}

					sint nc = vtool.AddValToVec(&cont_names[dx], &stmts_->at(i).cont, true, false);

					if (!xc || xc > 2)
					{
						xc = vtool.AddValToVec(&com_->t, &stmts_->at(i), true, true);
					}
					else
					{
						xc = vtool.AddValToVec(&ncrts, &stmts_->at(i), true, true);
					}
				}
				stmts_->at(i).Clear();
			}
		}

		sint hx = vtool.CleanVec(stmts_);

		for (sint i = 0; i < (sint)ncrts.size(); i++)
		{
			sint xc = vtool.AddValToVec(&com_->t, &ncrts[i], true, true);
		}

		for (sint i = (sint)com_->dbs.size() - 1; i > -1; i--)
		{
			sint xc = GetInVec((void*)&com_->dbs[i], MTX_DBL);

			if (debug_lvl >= 500 && debug_m)
			{
				carr_256 ncar;
				xc = bot_sprintf(ncar.carr, ncar.siz, "building necessary statements for %s", com_->dbs[i].name.c_str());
				xc = Output(ncar.carr, 2);
			}

			BOT_STMT trans((bool)db_maint[i], 1, com_->dbs[i].name.c_str(), "LAST_ACCESS", 1);
			trans.cspec = 0;
			trans.act = 0;
			xc = vtool.AddValToVec(&trans.conds, "ID > 0", false, false);
			xc = vtool.AddValToVec(&com_->t, &trans, true, false);
			

			for (uint c = 0; c < cont_names[i].size(); c++)
			{
				trans.Clear();
				trans.Renew((bool)db_maint[i], 8, com_->dbs[i].name.c_str(), cont_names[i][c].c_str(), 1);
				xc = vtool.AddValToVec(&com_->an, &trans, true, false);
			}
		}
		return 0;
	}
	sint OutpuTINFO(BOT_STMT *t_ = 0)
	{
		std::string output;

		if (t_)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, " it_type:%i dbname:\"%s\"\ntables:", t_->it_type, t_->dbname.c_str());
			output.append(ncar.carr);
		}
		else
		{
			return -1;
		}

		if (!t_->cont.empty())
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "%i %s", t_->ic_type, t_->cont.c_str());
			output.append(ncar.carr);
		}

		if (!output.empty())
		{
			carr_64 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "\nt_ has %u vals eles: ", t_->vals.size());
			output.append(ncar.carr);
		}

		for (uint o = 0; o < t_->vals.size(); o++)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "| %s ", t_->vals[o].c_str());
			output.append(ncar.carr);
		}

		if (!output.empty())
		{
			carr_64 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "\nt_ has %u cols eles: ", t_->cols.size());
			output.append(ncar.carr);
		}

		for (uint o = 0; o < t_->cols.size(); o++)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "| %s ", t_->cols[o].c_str());
			output.append(ncar.carr);
		}

		if (!output.empty())
		{
			carr_64 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "\nt_ has %u conds eles: ", t_->conds.size());
			output.append(ncar.carr);
		}

		for (uint o = 0; o < t_->conds.size(); o++)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "| %s ", t_->conds[o].c_str());
			output.append(ncar.carr);
		}

		for (uint o = 0; o < 2; o++)
		{
			carr_64 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "\nopts[%u]:%i has %u eles: ", o, t_->opts[o]);
			output.append(ncar.carr);
		}
		sint xc = Output(output.c_str(), 2);
		return 0;
	}


	// Database Functions

	std::string GetError()
	{
		std::string str;
		str.append(reinterpret_cast<c_char*>(sqlite3_errmsg(d_con_->db_)));
		return str;
	}
	sint FindColumn(c_char *str_, sqlite3_stmt* ppstmt)
	{
		sint xc = -1;
		sint s = sqlite3_column_count(ppstmt);

		if (s)
		{
			xc++;

			while (xc < s)
			{
				if (!strcmp(str_, sqlite3_column_name(ppstmt, xc)))
				{
					return xc;
				}
				xc++;
			}

			if (xc == s)
			{
				xc = -1;
			}
		}

		return xc;
	}
	sint GetODBConn(BOT_DB_M *db_ = 0)
	{
		if (!db_ || !d_con_)
		{
			return -1;
		}
		if (db_->name.empty())
		{
			return -1;
		}

		if (!strcmp(db_->name.c_str(), d_con_->name.c_str()))
		{
			db_->fcon = INT32_MAX;
			return INT32_MAX;
		}

		sint rc = vtool.ValInVec(&d_con_->att, db_->name.c_str());

		if (rc > -1)
		{
			return rc;
		}
		db_->fcon = rc;
		return -1;
	}
	sint GetDBConn(BOT_DB_M* val_ = 0)
	{
		if (!val_)
		{
			return -1;
		}

		sint ret = GetODBConn(val_);

		if (ret > -1)
		{
			return ret;
		}

		sint h = -1;
		sint p = LockGMutex(MTX_DBC, &h);

		if (p > -1)
		{
			if (olim < BOT_ATT_LIM)
			{
				for (sint siz = 0; siz < BOT_ATT_LIM; siz++)
				{
					sint xh = -1;
					sint xc = LockElement(MTX_DBC, siz, &xh, false, false);

					if (!xc)
					{
						d_con_ = &DCON[siz];
						ret = UpdMTXPrio();
						val_->fcon = siz;
						d_con_->Renew(val_->name.c_str(), val_->lid, val_->omode, siz);
						ret = siz;
						siz = BOT_ATT_LIM;
					}
				}
			}
			if (!h)
			{
				h = UnlockGMutex(MTX_DBC);
			}
		}
		return ret;
	}
	sint CloseDBConn(BOT_DB_M* db_ = 0)
	{
		sint f_ele = d_con_->lid;
		d_con_->Clear();
		sint xc = UnlockElement(MTX_DBC, f_ele, false);

		if (!xc)
		{
			d_con_ = 0;
			xc = UpdMTXPrio();
		}
		return xc;
	}
	sint OpenOpt(sint opt = -1) { if (opt < 0) { return -1; } if (!opt) { return 0; } if (opt < 3) { return 2; } if (opt < 9) { return 3; } return -1; }
	sint OpenDB(sint db_lid = -1, sint x = -1, sint* was_open = 0, sint* fwas_locked = 0, bool r_to_st = true)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_512 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::OpenDB(sint db_lid(%i), sint x(%i), sint* was_open(%i), sint* fwas_locked(%i), bool r_to_st(%u))", db_lid, x, (sint)was_open, (sint)fwas_locked, (uint)r_to_st);
			oc = Output(outp.carr, 2);
		}

		if (db_lid < 0 || x < 0 || !was_open || !fwas_locked || !d_con_)
		{
			return -1;
		}

		BOT_DB_M ndb;
		sint xc = GetVecEle((void*)&ndb, MTX_DBL, db_lid);

		if (xc > -1)
		{
			return OpenDB(&ndb, x, was_open, fwas_locked, r_to_st);
		}
		return -1;
	}
	sint OpenDB(BOT_DB_M *db_ = 0, sint x = -1, sint* was_open = 0, sint* fwas_locked = 0, bool r_to_st = false, bool is_verify = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_512 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::OpenDB(BOT_DB_M* db_(%i), sint x(%i), sint* was_open(%i), sint* fwas_locked(%i), bool r_to_st(%u), bool is_verify(%u))", (sint)db_, x, (sint)was_open, (sint)fwas_locked, (uint)r_to_st, (uint)is_verify);
			oc = Output(outp.carr, 2);
		}

		if (!was_open || !db_ || !fwas_locked)
		{
			return -1;
		}

		if (db_->name.empty() && db_->lid < 0)
		{
			sint oc = Output("Empty DB name.", 2);
			return -3;
		}

		if (db_->lid > -1)
		{
			sint xc = GetVecEle((void*)db_, MTX_DBL, db_->lid);
		}
		else
		{
			sint xc = GetInVec((void*)db_, MTX_DBL);
		}

		if (db_->lid < 0)
		{
			if (x == 3)
			{
				BOT_DB ndb(db_->name.c_str());
				sint xc = PushToDBList(&ndb);

				if (xc < 0)
				{
					return -1;
				}

				xc = GetVecEle((void*)db_, MTX_DBL, ndb.lid);

				if (xc < 0)
				{
					if (debug_lvl >= 4 && debug_m)
					{
						carr_256 outp;
						xc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\" not found in list, OpenOpt(%i)", db_->name.c_str(), x);
						xc = Output(outp.carr, 2);
					}
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}

		if (db_->exists < 0 && x != 3)
		{
			if (debug_lvl >= 4 && debug_m)
			{
				carr_256 outp;
				sint xc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\" does not exist, OpenOpt(%i)", db_->name.c_str(), x);
				xc = Output(outp.carr, 2);
			}
			return -1;
		}

		if (db_->exists < 1 && x != 3 && !is_verify)
		{
			if (debug_lvl >= 4 && debug_m)
			{
				carr_256 outp;
				sint xc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\" not created, OpenOpt(%i)", db_->name.c_str(), x);
				xc = Output(outp.carr, 2);
			}
			return -1;
		}

		sint dbc = -1;

		if (d_con_)
		{
			dbc = GetODBConn(db_);

			if (dbc < 0)
			{
				if (*was_open < 1)
				{
					*was_open = 0;
				}

				if (d_con_->o_com)
				{
					if (debug_lvl >= 4 && debug_m)
					{
						carr_256 outp;
						sint oc = bot_sprintf(outp.carr, outp.siz, "DB connection in use for this thread, OpenOpt(%i)", db_->name.c_str(), x);
						oc = Output(outp.carr, 2);
					}
					return -1;
				}
			}
			else
			{
				if (d_con_->in_use)
				{
					if (*was_open < 1)
					{
						*was_open = 1;
					}

					if (x > d_con_->omode)
					{
						if (debug_lvl >= 4 && debug_m)
						{
							carr_256 outp;
							sint oc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\" in use with lower priv for this thread, OpenOpt(%i)", db_->name.c_str(), x);
							oc = Output(outp.carr, 2);
						}
						return -1;
					}
					else {}

					if (!r_to_st)
					{
						return db_->lid;
					}
				}
				else
				{
					if (*was_open < 1)
					{
						*was_open = 0;
					}
				}
			}
		}
		else
		{
			if (*was_open < 1)
			{
				*was_open = 0;
			}
		}

		BOT_FILE_M nfilem(db_->name.c_str(), ".db", "", x, BOT_DB_CON, -1, lid, -1, 0);
		sint xc = GetInVec(&nfilem, MTX_FO, false, true);

		if (xc < 0)
		{
			BOT_FILE nfile(db_->name.c_str(), ".db", "", x, BOT_DB_CON, -1, lid, -1, 0);
			xc = GetInVec(&nfile, MTX_FO, true, false);

			if (xc < 0)
			{
				return -1;
			}
			xc = GetVecEle(&nfilem, MTX_FO, nfile.lid);

			if (xc < 0)
			{
				return -1;
			}
		}
		
		db_->file_ele = nfilem.lid;
		xc = SetVecEleMem(&nfilem.lid, MTX_DBL, db_->lid, BOT_DB_FELE, false);

		if (*fwas_locked < 1)
		{
			*fwas_locked = vtool.ValInVec(&h_mtxs, MTX_FO);

			if (*fwas_locked > -1)
			{
				xc = *fwas_locked;
				*fwas_locked = vtool.ValInVec(&h_mtxs[xc].h_mems, nfilem.lid);

				if (*fwas_locked < 0)
				{
					*fwas_locked = 0;
				}
				else
				{
					*fwas_locked = 1;
				}
			}
			else
			{
				*fwas_locked = 0;
			}
		}
		if (!*fwas_locked)
		{
			xc = LockElement(MTX_FO, nfilem.lid, fwas_locked, true, false);

			if (xc < 0)
			{
				return -1;
			}
		}

		sint xh = -1;
		sint lx = LockElement(MTX_DBL, db_->lid, &xh, true, false);

		if (lx)
		{
			if (!*fwas_locked)
			{
				lx = UnlockElement(MTX_FO, nfilem.lid, false);
			}
			if (debug_lvl >= 4 && debug_m)
			{
				carr_256 outp;
				xc = bot_sprintf(outp.carr, outp.siz, "Failed to acquire mtx for DB \"%s\"(%i)", db_->name.c_str(), db_->lid);
				xc = Output(outp.carr, 2);
			}
			return -2;
		}

		uint nulim = UINT_MAX;

		if (!d_con_)
		{
			xc = 0;

			for (dbc = GetDBConn(db_); dbc < 0 && xc < INT32_MAX; dbc = GetDBConn(db_))
			{
				slint rst = nsRest((slint)BOT_FO_REST);
				xc++;
			}

			if (!d_con_)
			{
				if (!xh)
				{
					xh = UnlockElement(MTX_DBL, db_->lid, false);
				}
				if (!*fwas_locked)
				{
					xc = UnlockElement(MTX_FO, nfilem.lid, false);
				}
				return -1;
			}
		}

		if (!d_con_->in_use)
		{
			sint hlim = -1;
			sint plim = LockGMutex(MTX_DBC, &hlim);

			if (plim > -1)
			{
				if (dbc > -1)
				{
					std::string dbt;
#ifdef BOT_USE_DBPATH
#if BOT_USE_DBPATH == 1
					dbt.append(BOT_DB_PATH);
#else

#endif
#endif
					dbt.append(db_->name.c_str());
					dbt.append(".db");

					xc = -1;

					if (x == 1)
					{
						xc = sqlite3_open_v2(dbt.c_str(), &d_con_->db_, SQLITE_OPEN_READONLY, 0);
					}
					else if (x == 2)
					{
						xc = sqlite3_open_v2(dbt.c_str(), &d_con_->db_, SQLITE_OPEN_READWRITE, 0);
					}
					else if (x == 3)
					{
						xc = sqlite3_open_v2(dbt.c_str(), &d_con_->db_, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
					}
					else
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_256 outp;
							xc = bot_sprintf(outp.carr, outp.siz, "invalid open opt:%i for %s", x, dbt.c_str());
							xc = Output(outp.carr, 2);
						}
						if (dbc > -1)
						{
							xc = UnlockElement(MTX_DBC, dbc, false);
						}
						if (!hlim)
						{
							hlim = UnlockGMutex(MTX_DBC);
						}
						if (!xh)
						{
							xh = UnlockElement(MTX_DBL, db_->lid, false);
						}
						if (!*fwas_locked)
						{
							xc = UnlockElement(MTX_FO, nfilem.lid, false);
						}
						return -1;
					}
					if (xc)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							xc = Output(GetError().c_str(), 1, 2, -1);
						}
						if (dbc > -1)
						{
							xc = UnlockElement(MTX_DBC, dbc, false);
						}
						if (!hlim)
						{
							hlim = UnlockGMutex(MTX_DBC);
						}
						if (!xh)
						{
							xh = UnlockElement(MTX_DBL, db_->lid, false);
						}
						if (!*fwas_locked)
						{
							xc = UnlockElement(MTX_FO, nfilem.lid, false);
						}
						return -1;
					}
					
					d_con_->Renew(db_->name.c_str(), db_->lid, x, d_con_->lid);
					d_con_->in_use = true;
					olim++;
					nulim = olim;

					if (d_con_->exists < 0)
					{
						d_con_->exists = 1;
					}
				}
				if (!hlim)
				{
					hlim = UnlockGMutex(MTX_DBC);
				}
			}
		}
		else
		{
			sint hlim = -1;
			sint plim = LockGMutex(MTX_DBC, &hlim);

			if (plim > -1)
			{
				if (d_con_->exists > -1 && !d_con_->o_com)
				{
					carr_512 bstmt;
					xc = bot_sprintf(bstmt.carr, bstmt.siz, "ATTACH %s AS %s;", db_->name.c_str(), db_->name.c_str());
					c_char* tail;
					sqlite3_stmt* ppstmt;

					if (debug_lvl >= 9 && debug_m)
					{
						xc = Output("preparing statement:", 2);

						if (debug_lvl >= 9 && debug_m)
						{
							xc = Output(bstmt.carr, 2);
						}
					}

					d_con_->o_com = true;
					sint rc = UpdMTXPrio();
					rc = sqlite3_prepare_v2(d_con_->db_, bstmt.carr, (sint)strlen(bstmt.carr), &ppstmt, &tail);

					if (!rc)
					{
						if (debug_lvl >= 9 && debug_m)
						{
							xc = Output("statement prepared.", 2);
						}
						bool done = false;

						while (!done)
						{
							rc = sqlite3_step(ppstmt);

							switch (rc)
							{
							case SQLITE_OK:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									xc = Output("SQLITE_OK", 2);
								}
								dbc = vtool.AddValToVec(&d_con_->att, db_->name.c_str(), true, true);
								olim++;
								nulim = olim;
								done = true;
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									xc = Output("SQLITE_DONE", 2);
								}
								dbc = vtool.AddValToVec(&d_con_->att, db_->name.c_str(), true, true);
								olim++;
								nulim = olim;
								done = true;
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									xc = Output("SQLITE_ROW", 2);
								}
								break;
							}
							case SQLITE_BUSY:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									xc = Output("SQLITE_BUSY", 2);
								}
								slint rst = Rest((slint)BOT_MILLI_REST, true);
								break;
							}
							default:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									xc = Output(GetError().c_str(), 1, 2, -1);
								}
								done = true;
								break;
							}
							}
						}

						rc = sqlite3_finalize(ppstmt);

						if (rc)
						{
							if (debug_lvl >= 1 && debug_m)
							{
								xc = Output(GetError().c_str(), 1, 2, -1);
							}
						}
					}
					else
					{
						d_con_->o_com = false;
						rc = UpdMTXPrio();
						if (debug_lvl >= 1 && debug_m)
						{
							xc = Output(GetError().c_str(), 1, 2, -1);
						}

						if (!hlim)
						{
							hlim = UnlockGMutex(MTX_DBC);
						}
						if (!xh)
						{
							xh = UnlockElement(MTX_DBL, db_->lid, false);
						}
						if (!*fwas_locked)
						{
							xc = UnlockElement(MTX_FO, nfilem.lid, false);
						}
						return -15;
					}
					d_con_->o_com = false;
					rc = UpdMTXPrio();
				}
				else
				{
					if (!hlim)
					{
						hlim = UnlockGMutex(MTX_DBC);
					}
					if (!xh)
					{
						xh = UnlockElement(MTX_DBL, db_->lid, false);
					}
					if (!*fwas_locked)
					{
						xc = UnlockElement(MTX_FO, nfilem.lid, false);
					}
					return -1;
				}
				if (!hlim)
				{
					hlim = UnlockGMutex(MTX_DBC);
				}
			}
		}

		if (dbc > -1)
		{
			db_->omode = x;
			xc = SetVecEleMem((void*)&db_->omode, MTX_DBL, db_->lid, BOT_DB_OMODE, false);
			nfilem.omode = x;
			xc = SetVecEleMem((void*)&x, MTX_FO, nfilem.lid, BOT_FS_OMODE, false);
			db_->connected = true;
			xc = SetVecEleMem((void*)&db_->connected, MTX_DBL, db_->lid, BOT_DB_CONN, false);
		}

		if (debug_lvl >= 4 && debug_m)
		{
			carr_256 outp;
			xc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\"(%i) opened, olim is:%u", db_->name.c_str(), db_->lid, nulim);
			xc = Output(outp.carr, 2);
		}
		return db_->lid;
	}
	sint CloseDB(sint db_lid = -1, sint* fwas_locked = 0, bool clear_conn = true)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_256 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::CloseDB(sint db_lid(%i), sint* fwas_locked(%i), bool clear_conn(%u))", db_lid, (sint)fwas_locked, (uint)clear_conn);
			oc = Output(outp.carr, 2);
		}

		if (db_lid < 0 || !fwas_locked || !d_con_)
		{
			return -1;
		}

		if (d_con_->o_com)
		{
			return -1;
		}

		BOT_DB_M ndb;
		sint xc = GetVecEle((void*)&ndb, MTX_DBL);

		if (xc > -1)
		{
			return CloseDB(&ndb, fwas_locked, clear_conn);
		}
		return -1;
	}
	sint CloseDB(BOT_DB_M* db_ = 0, sint* fwas_locked = 0, bool clear_conn = true)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_256 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::CloseDB(BOT_DB_M* db_lid(%i), sint* fwas_locked(%i), bool clear_conn(%u))", db_, (sint)fwas_locked, (uint)clear_conn);
			oc = Output(outp.carr, 2);
		}

		if (!db_ || !d_con_)
		{
			return -1;
		}

		if (d_con_->o_com)
		{
			return -1;
		}

		sint dbc = GetODBConn(db_);

		if (dbc < 0 || db_->lid < 0)
		{
			return -1;
		}

		uint nulim = UINT_MAX;

		if (dbc != INT32_MAX)
		{
			carr_256 bstmt;
			sint xc = bot_sprintf(bstmt.carr, bstmt.siz, "DETACH %s;", d_con_->att[dbc].c_str());
			c_char* tail;
			sqlite3_stmt* ppstmt;

			if (debug_lvl >= 9 && debug_m)
			{
				xc = Output("preparing statement:", 2);

				if (debug_lvl >= 9 && debug_m)
				{
					xc = Output(bstmt.carr, 2);
				}
			}
			d_con_->o_com = true;
			xc = UpdMTXPrio();
			xc = sqlite3_prepare_v2(d_con_->db_, bstmt.carr, (sint)strlen(bstmt.carr), &ppstmt, &tail);

			if (xc)
			{
				xc = Output(GetError().c_str(), 1, 2, -1);
			}
			else
			{
				if (debug_lvl >= 9 && debug_m)
				{
					xc = Output("statement prepared.", 2);

					if (debug_lvl >= 19 && debug_m)
					{
						xc = Output(bstmt.carr, 2);
					}
				}
				bool done = false;

				while (!done)
				{
					xc = sqlite3_step(ppstmt);

					switch (xc)
					{
					case SQLITE_OK:
					{
						if (debug_lvl >= 9 && debug_m)
						{
							xc = Output("SQLITE_OK", 2);
						}

						if (clear_conn)
						{
							xc = vtool.ClearEleFromVec(&d_con_->att, dbc);
							xc = vtool.CleanVec(&d_con_->att);
						}

						sint hlim = -1;
						sint plim = LockGMutex(MTX_DBC, &hlim);

						if (plim > -1)
						{
							if (olim > 0)
							{
								olim--;
								nulim = olim;
							}
							if (!hlim)
							{
								hlim = UnlockGMutex(MTX_DBC);
							}
						}

						db_->connected = false;
						db_->omode = -1;
						xc = SetVecEleMem((void*)&db_->connected, MTX_DBL, db_->lid, BOT_DB_CONN, false);
						xc = SetVecEleMem((void*)&db_->omode, MTX_DBL, db_->lid, BOT_DB_OMODE, false);
						done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 9 && debug_m)
						{
							xc = Output("SQLITE_DONE", 2);
						}

						if (clear_conn)
						{
							xc = vtool.ClearEleFromVec(&d_con_->att, dbc);
							xc = vtool.CleanVec(&d_con_->att);
						}

						sint hlim = -1;
						sint plim = LockGMutex(MTX_DBC, &hlim);

						if (plim > -1)
						{
							if (olim > 0)
							{
								olim--;
								nulim = olim;
							}
							if (!hlim)
							{
								hlim = UnlockGMutex(MTX_DBC);
							}
						}

						db_->connected = false;
						db_->omode = -1;
						xc = SetVecEleMem((void*)&db_->connected, MTX_DBL, db_->lid, BOT_DB_CONN, false);
						xc = SetVecEleMem((void*)&db_->omode, MTX_DBL, db_->lid, BOT_DB_OMODE, false);
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 9 && debug_m)
						{
							xc = Output("SQLITE_ROW", 2);
						}
						break;
					}
					case SQLITE_BUSY:
					{
						if (debug_lvl >= 9 && debug_m)
						{
							xc = Output("SQLITE_BUSY", 2);
						}
						slint rst = Rest((slint)BOT_MILLI_REST, true);
						break;
					}
					default:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							xc = Output(GetError().c_str(), 1, 2, -1);
						}
						done = true;
						break;
					}
					}
				}
				xc = sqlite3_finalize(ppstmt);

				if (xc)
				{
					if (debug_lvl >= 1 && debug_m)
					{
						xc = Output(GetError().c_str(), 1, 2, -1);
					}
				}
			}
			d_con_->o_com = false;
			xc = UpdMTXPrio();
		}
		else
		{
			if (d_con_->persist)
			{
				return -1;
			}
			if (!strcmp(d_con_->name.c_str(), db_->name.c_str()))
			{
				d_con_->close_me = true;

				if (d_con_->att.empty())
				{
					sint xc = sqlite3_close_v2(d_con_->db_);

					if (xc)
					{
						xc = Output(GetError().c_str(), 1, 2, -1);
						return -1;
					}
					else
					{
						sint hlim = -1;
						sint plim = LockGMutex(MTX_DBC, &hlim);

						if (plim > -1)
						{
							if (olim > 0)
							{
								olim--;
								nulim = olim;

								if (clear_conn)
								{
									xc = CloseDBConn(db_);
								}
							}
							if (!hlim)
							{
								hlim = UnlockGMutex(MTX_DBC);
							}
						}

						db_->connected = false;
						db_->omode = -1;
						xc = SetVecEleMem((void*)&db_->connected, MTX_DBL, db_->lid, BOT_DB_CONN, false);
						xc = SetVecEleMem((void*)&db_->omode, MTX_DBL, db_->lid, BOT_DB_OMODE, false);
					}
				}
			}
		}

		sint gc = vtool.ValInVec(&h_mtxs, MTX_DBL);

		if (gc > -1)
		{
			sint xgc = gc;
			gc = vtool.ValInVec(&h_mtxs[xgc].h_mems, db_->lid);

			if (gc > -1)
			{
				gc = UnlockElement(MTX_DBL, db_->lid, false);
			}

			if (!gc)
			{
				if (debug_lvl >= 9 && debug_m)
				{
					carr_256 outp;
					sint xc = bot_sprintf(outp.carr, outp.siz, "unlocked DB \"%s\" olim:%i.", db_->name.c_str(), nulim);
					xc = Output(outp.carr, 2);
				}
			}
		}

		BOT_FILE_M nfile;
		sint xc = GetVecEle(&nfile, MTX_FO, db_->file_ele);

		if (!*fwas_locked)
		{
			nfile.omode = db_->omode;

			if (gc > -1)
			{
				gc = BOTFileStats(&nfile);
			}

			xc = UnlockElement(MTX_FO, nfile.lid, false);
		}
		return gc;
	}

	sint OpenDBs(std::vector<BOT_DB_M> *dbs_, sint opt = -1, std::vector <sint> *wos_ = 0, std::vector<sint> *fwas_ = 0, std::vector<sint> *lids_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				carr_256 outp;
				sint oc = bot_sprintf(outp.carr, outp.siz, "::OpenDBs(std::vector <BOT_DB_M> *dbs_(%i), sint opt(%i), std::vector <sint> *wos_(%i), std::vector<sint>* fwas_(%i), std::vector<sint> lids_(%i))", (sint)dbs_, opt, (sint)wos_, (sint)fwas_, (sint)lids_);
				oc = Output(outp.carr, 2);
			}
		}
		if (!dbs_ || opt < 0 || !wos_ || !fwas_ || !lids_)
		{
			return -1;
		}
		if (dbs_->empty())
		{
			return -1;
		}

		sint ret = -1;

		for (uint opens = 0; opens < dbs_->size(); opens++)
		{
			if (dbs_->at(opens).name.empty())
			{
				sint oc = Output("Empty DB name.", 2);
			}
			else
			{
				fwas_->push_back(-1);
				wos_->push_back(-1);
				ret = OpenDB(&dbs_->at(opens), opt, &wos_->at(opens), &fwas_->at(opens));
				lids_->push_back(ret);
			}
		}
		sint cl = vtool.CleanVec(dbs_);
		// do stuff with fails and clear them as each is fixed, if all are corrected we can return 0
		return ret;
	}
	sint CloseDBs(std::vector<BOT_DB_M> *dbs_ = 0, std::vector<sint>* fwas_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::CloseDBs(std::vector<BOT_DB_M>* dbs_(%i), std::vector<sint>* fwas_(%i))", (sint)dbs_, (sint)fwas_);
			oc = Output(outp.carr, 2);
		}

		sint xc = -1;

		if (dbs_ && fwas_)
		{
			for (sint opens = (sint)dbs_->size() - 1; opens > -1; opens--)
			{
				if (!dbs_->at(opens).name.empty())
				{
					xc = CloseDB(&dbs_->at(opens), &fwas_->at(opens));

					if (!xc)
					{
						dbs_->at(opens).Clear();
					}
				}
			}
		}
		return xc;
	}
	sint Query(BOT_STMT* qval_ = 0, sint as_opt = -1)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::Query(BOT_COMMIT* qval_(%i), sint as_opt(%i))", (sint)qval_, as_opt);
			op = Output(outp.carr, 2);
		}

		if (!qval_ || as_opt < 0)
		{
			return -1;
		}

		if (qval_->dbname.empty() || !qval_->an)
		{
			if (qval_->stmt.empty())
			{
				sint ret = AnalyzeStmt(qval_);

				if (ret)
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}

		if (qval_->stmt.empty())
		{
			sint ret = BQS(qval_);

			if (ret)
			{
				return -1;
			}
		}

		BOT_DB_M dbs(qval_->dbname.c_str());
		sint ret = GetInVec((void*)&qval_, MTX_DBL, false, false);

		if (ret < 0)
		{
			return -1;
		}

		sint of = -1;
		sint hdb = -1;
		ret = OpenDB(&dbs, 1, &hdb, &of);

		if (ret > -1)
		{
			std::vector<std::vector<std::vector<std::string>>> ncols;
			ret = GetVecEleMem((void*)&ncols, MTX_DBL, dbs.lid, BOT_DB_COLUMNS, false);
			d_con_->o_com = true;
			ret = UpdMTXPrio();
			c_char* tail;
			sqlite3_stmt* ppstmt;
			ret = sqlite3_prepare_v2(d_con_->db_, qval_->stmt.c_str(), (sint)qval_->stmt.length(), &ppstmt, &tail);

			if (ret)
			{
				ret = Output(GetError().c_str(), 1, 2, -1);
			}
			else
			{
				bool done = false;

				while (!done)
				{
					ret = sqlite3_step(ppstmt);

					switch (ret)
					{
					case SQLITE_OK:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							ret = Output("SQLITE_OK", 2);
						}
						done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							ret = Output("SQLITE_DONE", 2);
						}
						done = true;
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							ret = Output("SQLITE_ROW", 2);
						}

						if (qval_->fcols.empty())
						{
							for (uint i = 0; i < ncols[0][0].size(); i++)
							{
								qval_->fcols.push_back(ncols[0][0][i]);
							}
						}

						for (uint iter = 0; iter < qval_->fcols.size(); iter++)
						{
							ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
							sint ct = sqlite3_column_type(ppstmt, ret);
							sint xret = sqlite3_column_bytes(ppstmt, ret);

							if (ct == SQLITE_INTEGER)
							{
								switch (as_opt)
								{
								case BOT_RTV_SINT:
								{
									sint* inv = reinterpret_cast<sint*>(qval_->rblk);
									*inv = sqlite3_column_int(ppstmt, ret);
									break;
								}
								case BOT_RTV_CHAR:
								{
									_char* inv = reinterpret_cast<_char*>(qval_->rblk);
									*inv = (_char)sqlite3_column_int(ppstmt, ret);
									break;
								}
								case BOT_RTV_UINT:
								{
									uint* inv = reinterpret_cast<uint*>(qval_->rblk);
									*inv = (uint)sqlite3_column_int(ppstmt, ret);
									break;
								}
								case BOT_RTV_UCHAR:
								{
									u_char* inv = reinterpret_cast<u_char*>(qval_->rblk);
									*inv = (u_char)sqlite3_column_int(ppstmt, ret);
									break;
								}
								case BOT_RTV_CCHAR:
								{
									c_char* inv = reinterpret_cast<c_char*>(qval_->rblk);
									errno_t rerr = bot_itoa((sint)sqlite3_column_int(ppstmt, ret), inv, strlen(inv));
									break;
								}
								case BOT_RTV_STR:
								{
									std::string* inv = reinterpret_cast<std::string*>(qval_->rblk);
									c_char ncar[21]{ 0 };
									errno_t rerr = bot_itoa((sint)sqlite3_column_int(ppstmt, ret), ncar, 21);
									inv->append(ncar);
									break;
								}
								case BOT_RTV_REAL:
								{
									float* inv = reinterpret_cast<float*>(qval_->rblk);
									sint xval = sqlite3_column_int(ppstmt, ret);
									*inv = (float)xval;
									break;
								}
								case BOT_RTV_MICS:
								{
									MICSYM* ns = reinterpret_cast<MICSYM*>(qval_->rblk);

									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										ns->id = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										ns->last_maintained = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										ns->last_maintained_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										ns->last_modified = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										ns->last_modified_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
									break;
								}
								case BOT_RTV_MACS:
								{
									MACSYM* ns = reinterpret_cast<MACSYM*>(qval_->rblk);

									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										ns->id = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										ns->last_maintained = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										ns->last_maintained_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										ns->last_modified = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										ns->last_modified_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
									break;
								}
								case BOT_RTV_VSINT:
								{
									std::vector<sint>* inv = reinterpret_cast<std::vector<sint>*>(qval_->rblk);
									inv->push_back(sqlite3_column_int(ppstmt, ret));
									break;
								}
								case BOT_RTV_VCHAR:
								{
									std::vector<_char>* inv = reinterpret_cast<std::vector<_char>*>(qval_->rblk);
									inv->push_back((_char)sqlite3_column_int(ppstmt, ret));
									break;
								}
								case BOT_RTV_VUINT:
								{
									std::vector<uint>* inv = reinterpret_cast<std::vector<uint>*>(qval_->rblk);
									inv->push_back((uint)sqlite3_column_int(ppstmt, ret));
									break;
								}
								case BOT_RTV_VUCHAR:
								{
									std::vector<u_char>* inv = reinterpret_cast<std::vector<u_char>*>(qval_->rblk);
									inv->push_back((u_char)sqlite3_column_int(ppstmt, ret));
									break;
								}
								case BOT_RTV_VCCHAR:
								{
									break;
								}
								case BOT_RTV_VSTR:
								{
									std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(qval_->rblk);
									c_char ncar[21]{ 0 };
									errno_t rerr = bot_itoa((sint)sqlite3_column_int(ppstmt, ret), ncar, 21);
									std::string nstr;
									nstr.append(ncar);
									inv->push_back(nstr);
									break;
								}
								case BOT_RTV_VREAL:
								{
									std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(qval_->rblk);
									sint xval = sqlite3_column_int(ppstmt, ret);
									inv->push_back((float)xval);
									break;
								}
								case BOT_RTV_VMICS:
								{
									std::vector<MICSYM>* nsv = reinterpret_cast<std::vector<MICSYM>*>(qval_->rblk);

									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{

									}
									else {}
									break;
								}
								case BOT_RTV_VMACS:
								{
									std::vector<MACSYM>* ns = reinterpret_cast<std::vector<MACSYM>*>(qval_->rblk);

									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{

									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{

									}
									else {}
									break;
								}
								default:
								{
									break;
								}
								}
							}
							else if (ct == SQLITE_FLOAT)
							{
								switch (as_opt)
								{
								case BOT_RTV_SINT:
								{
									sint* inv = reinterpret_cast<sint*>(qval_->rblk);
									*inv = (sint)sqlite3_column_double(ppstmt, ret);
									break;
								}
								case BOT_RTV_CHAR:
								{
									_char* inv = reinterpret_cast<_char*>(qval_->rblk);
									*inv = (_char)sqlite3_column_double(ppstmt, ret);
									break;
								}
								case BOT_RTV_UINT:
								{
									uint* inv = reinterpret_cast<uint*>(qval_->rblk);
									*inv = (uint)sqlite3_column_double(ppstmt, ret);
									break;
								}
								case BOT_RTV_UCHAR:
								{
									u_char* inv = reinterpret_cast<u_char*>(qval_->rblk);
									*inv = (u_char)sqlite3_column_double(ppstmt, ret);
									break;
								}
								case BOT_RTV_CCHAR:
								{
									c_char* inv = reinterpret_cast<c_char*>(qval_->rblk);
									errno_t rerr = bot_dtoa(sqlite3_column_double(ppstmt, ret), inv, strlen(inv));
									break;
								}
								case BOT_RTV_STR:
								{
									std::string* inv = reinterpret_cast<std::string*>(qval_->rblk);
									c_char ncar[64]{ 0 };
									errno_t rerr = bot_dtoa(sqlite3_column_double(ppstmt, ret), ncar, 64);
									inv->append(ncar);
									break;
								}
								case BOT_RTV_REAL:
								{
									float* inv = reinterpret_cast<float*>(qval_->rblk);
									*inv = (float)sqlite3_column_double(ppstmt, ret);
									break;
								}
								case BOT_RTV_VSINT:
								{
									std::vector<sint>* inv = reinterpret_cast<std::vector<sint>*>(qval_->rblk);
									inv->push_back((sint)sqlite3_column_double(ppstmt, ret));
									break;
								}
								case BOT_RTV_VCHAR:
								{
									std::vector<_char>* inv = reinterpret_cast<std::vector<_char>*>(qval_->rblk);
									inv->push_back((_char)sqlite3_column_double(ppstmt, ret));
									break;
								}
								case BOT_RTV_VUINT:
								{
									std::vector<uint>* inv = reinterpret_cast<std::vector<uint>*>(qval_->rblk);
									inv->push_back((uint)sqlite3_column_double(ppstmt, ret));
									break;
								}
								case BOT_RTV_VUCHAR:
								{
									std::vector<u_char>* inv = reinterpret_cast<std::vector<u_char>*>(qval_->rblk);
									inv->push_back((u_char)sqlite3_column_double(ppstmt, ret));
									break;
								}
								case BOT_RTV_VCCHAR:
								{
									break;
								}
								case BOT_RTV_VSTR:
								{
									std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(qval_->rblk);
									c_char ncar[64]{ 0 };
									errno_t rerr = bot_dtoa(sqlite3_column_double(ppstmt, ret), ncar, 64);
									std::string nstr;
									nstr.append(ncar);
									inv->push_back(nstr);
									break;
								}
								case BOT_RTV_VREAL:
								{
									std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(qval_->rblk);
									float xval = (float)sqlite3_column_double(ppstmt, ret);
									inv->push_back(xval);
									break;
								}
								default:
								{
									break;
								}
								}
							}
							else if (ct == SQLITE_TEXT)
							{
								switch (as_opt)
								{
								case BOT_RTV_SINT:
								{
									sint* inv = reinterpret_cast<sint*>(qval_->rblk);
									*inv = atoi(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									break;
								}
								case BOT_RTV_CHAR:
								{
									if (xret == 1)
									{
										_char* inv = reinterpret_cast<_char*>(qval_->rblk);
										*inv = (_char)*sqlite3_column_text(ppstmt, ret);
									}
									break;
								}
								case BOT_RTV_UINT:
								{
									uint* inv = reinterpret_cast<uint*>(qval_->rblk);
									*inv = (uint)atoi(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									break;
								}
								case BOT_RTV_UCHAR:
								{
									if (xret == 1)
									{
										u_char* inv = reinterpret_cast<u_char*>(qval_->rblk);
										*inv = (u_char)*sqlite3_column_text(ppstmt, ret);
									}
									break;
								}
								case BOT_RTV_CCHAR:
								{
									c_char* inv = reinterpret_cast<c_char*>(qval_->rblk);
									memcpy((void*)inv, (void*)sqlite3_column_text(ppstmt, ret), xret);
									break;
								}
								case BOT_RTV_STR:
								{
									std::string* inv = reinterpret_cast<std::string*>(qval_->rblk);
									inv->append(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									break;
								}
								case BOT_RTV_REAL:
								{
									float* inv = reinterpret_cast<float*>(qval_->rblk);
									*inv = (float)atof(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									break;
								}
								case BOT_RTV_VSINT:
								{
									std::vector<sint>* inv = reinterpret_cast<std::vector<sint>*>(qval_->rblk);
									sint i = atoi(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									inv->push_back(i);
									break;
								}
								case BOT_RTV_VCHAR:
								{
									if (xret == 1)
									{
										std::vector<_char>* inv = reinterpret_cast<std::vector<_char>*>(qval_->rblk);
										inv->push_back((_char)*sqlite3_column_text(ppstmt, ret));
									}
									break;
								}
								case BOT_RTV_VUINT:
								{
									std::vector<uint>* inv = reinterpret_cast<std::vector<uint>*>(qval_->rblk);
									sint i = (uint)atoi(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									inv->push_back(i);
									break;
								}
								case BOT_RTV_VUCHAR:
								{
									if (xret == 1)
									{
										std::vector<u_char>* inv = reinterpret_cast<std::vector<u_char>*>(qval_->rblk);
										inv->push_back((u_char)*sqlite3_column_text(ppstmt, ret));
									}
									break;
								}
								case BOT_RTV_VCCHAR:
								{
									/*std::vector<c_char*>* inv = reinterpret_cast<std::vector<c_char*>*>(qval_->rblk);
									c_char* inv_ = "";
									memcpy((void*)inv_, (void*)sqlite3_column_text(ppstmt, ret), xret);
									inv->push_back(inv_);*/
									break;
								}
								case BOT_RTV_VSTR:
								{
									std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(qval_->rblk);
									std::string nstr;
									nstr.append(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									inv->push_back(nstr);
									break;
								}
								case BOT_RTV_VREAL:
								{
									std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(qval_->rblk);
									float xval = (float)atof(reinterpret_cast<const _char*>(sqlite3_column_text(ppstmt, ret)));
									inv->push_back(xval);
									break;
								}
								default:
								{
									break;
								}
								}
							}
							else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
							{
								switch (as_opt)
								{
								case BOT_RTV_SINT:
								{
									sint* inv_ = reinterpret_cast<sint*>(qval_->rblk);

									if (xret <= sizeof(inv_))
									{
										memcpy((void*)inv_, sqlite3_column_blob(ppstmt, ret), xret);
									}
									break;
								}
								case BOT_RTV_CHAR:
								{
									_char* inv = reinterpret_cast<_char*>(qval_->rblk);

									if (sizeof(inv) > (xret * 3))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);
										
										if (nuchar)
										{
											u_char echar = (u_char)'\0';
											uint y = 0;
											memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

											for (uint x = 0; x < (uint)xret; x++)
											{
												_char nc[(sizeof(nuchar[x] * 2)) + 1];
												ct = bot_sprintf(nc, sizeof(nc), "%02X", nuchar[x]);

												for (uint z = 0; z < sizeof(nc) && y < sizeof(nuchar); z++)
												{
													memcpy((void*)&inv[y], (void*)&nc[z], sizeof(nc[z]));
													y++;
												}
											}
										}
										free(nuchar);
									}
									break;
								}
								case BOT_RTV_UINT:
								{
									sint* inv_ = reinterpret_cast<sint*>(qval_->rblk);

									if (xret <= sizeof(qval_->rblk))
									{
										memcpy((void*)inv_, sqlite3_column_blob(ppstmt, ret), xret);
									}
									break;
								}
								case BOT_RTV_UCHAR:
								{
									u_char* inv = reinterpret_cast<u_char*>(qval_->rblk);

									if (sizeof(inv) > (xret * 3))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char echar = (u_char)'\0';
											uint y = 0;
											memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

											for (uint x = 0; x < (uint)xret; x++)
											{
												_char nc[(sizeof(nuchar[x] * 2)) + 1];
												ct = bot_sprintf(nc, sizeof(nc), "%02X", nuchar[x]);

												for (uint z = 0; z < sizeof(nc) && y < sizeof(nuchar); z++)
												{
													memcpy((void*)&inv[y], (void*)&nc[z], sizeof(nc[z]));
													y++;
												}
											}
										}
										free(nuchar);
									}
									break;
								}
								case BOT_RTV_CCHAR:
								{
									break;
								}
								case BOT_RTV_STR:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::string* inv = reinterpret_cast<std::string*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

										for (uint x = 0; x < (uint)xret; x++)
										{
											_char nc[(sizeof(nuchar[x] * 2)) + 1];
											ct = bot_sprintf(nc, sizeof(nc), "%02X", nuchar[x]);
											inv->append(nc);
										}
									}
									free(nuchar);
									break;
								}
								case BOT_RTV_REAL:
								{
									float* inv_ = reinterpret_cast<float*>(qval_->rblk);

									if (xret <= sizeof(qval_->rblk))
									{
										memcpy((void*)inv_, sqlite3_column_blob(ppstmt, ret), xret);
									}
									break;
								}
								case BOT_RTV_VSINT:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::vector<sint>* inv = reinterpret_cast<std::vector<sint>*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

										for (uint x = 0; x < (uint)xret; x++)
										{
											sint ni;
											memcpy((void*)&ni, (void*)&nuchar[x], sizeof(nuchar[x]));
											inv->push_back(ni);
										}
									}
									free(nuchar);
									break;
								}
								case BOT_RTV_VCHAR:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::vector<_char>* inv = reinterpret_cast<std::vector<_char>*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

										for (uint x = 0; x < (uint)xret; x++)
										{
											_char ni;
											memcpy((void*)&ni, (void*)&nuchar[x], sizeof(nuchar[x]));
											inv->push_back(ni);
										}
									}
									free(nuchar);
									break;
								}
								case BOT_RTV_VUINT:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::vector<uint>* inv = reinterpret_cast<std::vector<uint>*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

										for (uint x = 0; x < (uint)xret; x++)
										{
											uint ni;
											memcpy((void*)&ni, (void*)&nuchar[x], sizeof(nuchar[x]));
											inv->push_back(ni);
										}
									}
									free(nuchar);
									break;
								}
								case BOT_RTV_VUCHAR:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::vector<u_char>* inv = reinterpret_cast<std::vector<u_char>*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

										for (uint x = 0; x < (uint)xret; x++)
										{
											u_char ni;
											memcpy((void*)&ni, (void*)&nuchar[x], sizeof(nuchar[x]));
											inv->push_back(ni);
										}
									}
									free(nuchar);
									break;
								}
								case BOT_RTV_VCCHAR:
								{
									/*
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
									std::vector<c_char>* inv = reinterpret_cast<std::vector<c_char>*>(qval_->rblk);
									u_char echar = (u_char)'\0';
									memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
									memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));
									std::string nstr;

									for (uint x = 0; x < (uint)xret; x++)
									{
										_char nc[(sizeof(nuchar[x] * 2)) + 1];
										ct = bot_sprintf(nc, sizeof(nc), "%02X", nuchar[x]);
										nstr.append(nc);
									}
									inv->push_back(*nstr.c_str());
									}
									free(nuchar);*/
									break;
								}
								case BOT_RTV_VSTR:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));
										std::string nstr;

										for (uint x = 0; x < (uint)xret; x++)
										{
											_char nc[(sizeof(nuchar[x] * 2)) + 1];
											ct = bot_sprintf(nc, sizeof(nc), "%02X", nuchar[x]);
											nstr.append(nc);
										}
										inv->push_back(nstr);
									}
									free(nuchar);
									break;
								}
								case BOT_RTV_VREAL:
								{
									u_char* nuchar = (u_char*)malloc(xret + 1);

									if (nuchar)
									{
										std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(qval_->rblk);
										u_char echar = (u_char)'\0';
										memcpy((void*)nuchar, sqlite3_column_blob(ppstmt, ret), xret);
										memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(echar));

										for (uint x = 0; x < (uint)xret; x++)
										{
											float ni;
											memcpy((void*)&ni, (void*)&nuchar[x], sizeof(nuchar[x]));
											inv->push_back(ni);
										}
									}
									free(nuchar);
									break;
								}
								default:
								{
									break;
								}
								}
							}
							else {}
						}
						break;
					}
					case SQLITE_BUSY:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							sint xp = Output("SQLITE_BUSY", 2);
						}
						done = true;
						break;
					}
					default:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							sint xp = Output(GetError().c_str(), 1, 2, -1);
						}
						done = true;
						break;
					}
					}
				}

				ret = sqlite3_finalize(ppstmt);

				if (ret)
				{
					sint xp = Output(GetError().c_str(), 1, 2, -1);
				}
			}
			d_con_->o_com = false;
			ret = UpdMTXPrio();
			if (!hdb)
			{
				hdb = CloseDB(&dbs, &of);
			}
		}
		return -1;
	}
	sint Commit(std::vector<BOT_STMT>* stmts_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::Commit(BOT_COMMIT* com_(%i))", (sint)stmts_);
			op = Output(outp.carr, 2);
		}

		if (!stmts_)
		{
			return -1;
		}

		if (stmts_->empty())
		{
			sint xc = Output("aborting commit, no statements", 2);
			return -1;
		}

		bool done = false;

		while (!done)
		{
			BOT_COMMIT Comm;
			sint hx = -1;
			sint ox = LockGMutex(MTX_PEND, &hx);

			if (ox > -1)
			{
				if (!done)
				{
					sint xc = BuildStatements(stmts_, &Comm, &bot_t_pend);

					if (xc)
					{
						if (!hx)
						{
							hx = UnlockGMutex(MTX_PEND);
						}
						sint xc = Output("aborting commit, no statements have a database name declared", 2);
						return xc;
					}
				}

				if (Comm.dbs.empty())
				{
					if (!hx)
					{
						hx = UnlockGMutex(MTX_PEND);
					}
					sint xc = Output("aborting commit, no statements have a database name declared", 2);
					return -1;
				}

				std::vector<sint> lids;
				std::vector<sint> fwas;
				std::vector<sint>  wos;
				sint odb = OpenDBs(&Comm.dbs, Comm.opt, &wos, &fwas, &lids);

				for (odb = 0; odb < (sint)lids.size(); odb++)
				{
					if (lids[odb] > -1)
					{
						odb = (sint)lids.size();
					}
				}

				if (odb > (sint)lids.size())
				{
					bool began = false;
					d_con_->o_com = true;
					sint xc = UpdMTXPrio();

					for (size_t nsiz = 0; nsiz < Comm.t.size(); nsiz++)
					{
						sint vv = vtool.ValInVec(&Comm.dbs, Comm.t[nsiz].dbname.c_str());

						if (vv > -1)
						{
							sint rc = 0;

							if (Comm.t[nsiz].it_type > 0 && !began || Comm.t[nsiz].it_type < 1 && began)
							{
								c_char* tail = "";
								sqlite3_stmt* ppstmt;

								if (Comm.t[nsiz].it_type > 0)
								{
									if (!began)
									{
										if (debug_lvl >= 1 && debug_m)
										{
											sint xp = Output("preparing commit statement: BEGIN;", 2);
										}
										rc = sqlite3_prepare_v2(d_con_->db_, "BEGIN;", strlen("BEGIN;"), &ppstmt, &tail);
										began = true;
									}
								}
								else
								{
									if (began)
									{
										if (debug_lvl >= 1 && debug_m)
										{
											sint xp = Output("preparing commit statement: COMMIT;", 2);
										}
										rc = sqlite3_prepare_v2(d_con_->db_, "COMMIT;", strlen("COMMIT;"), &ppstmt, &tail);
										began = false;
									}
								}

								if (rc)
								{
									sint xp = Output(GetError().c_str(), 1, 2, -1);
								}
								else
								{
									if (debug_lvl >= 1 && debug_m)
									{
										sint xp = Output("statement prepared", 2);
									}

									rc = sqlite3_step(ppstmt);

									switch (rc)
									{
									case SQLITE_OK:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_OK", 2);
										}
										break;
									}
									case SQLITE_DONE:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_DONE", 2);
										}
										break;
									}
									case SQLITE_ROW:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_ROW", 2);
										}
										break;
									}
									case SQLITE_BUSY:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_BUSY", 2);
										}
										break;
									}
									default:
									{
										sint xp = Output(GetError().c_str(), 1, 2, -1);
										break;
									}
									}
									rc = sqlite3_finalize(ppstmt);

									if (rc)
									{
										sint xp = Output(GetError().c_str(), 1, 2, -1);
									}
								}
							}
							if (!rc)
							{
								if (Comm.t[nsiz].stmt.empty())
								{
									rc = BTS(&Comm.t[nsiz]);
								}

								if (!rc)
								{
									c_char* tail = "";
									sqlite3_stmt* ppstmt;

									if (debug_lvl >= 1 && debug_m)
									{
										std::string outp;
										outp.append("preparing commit statement: ");
										outp.append(Comm.t[nsiz].stmt.c_str());
										sint xp = Output(outp.c_str(), 2);
									}

									rc = sqlite3_prepare_v2(d_con_->db_, Comm.t[nsiz].stmt.c_str(), (sint)Comm.t[nsiz].stmt.length(), &ppstmt, &tail);

									if (rc)
									{
										sint xp = Output(GetError().c_str(), 1, 2, -1);
									}
									else
									{
										if (debug_lvl >= 1 && debug_m)
										{
											sint xp = Output("statement prepared", 2);
										}

										bool sdone = false;

										while (!sdone)
										{
											rc = sqlite3_step(ppstmt);

											switch (rc)
											{
											case SQLITE_OK:
											{
												if (debug_lvl >= 20 && debug_m)
												{
													sint xp = Output("SQLITE_OK", 2);
												}
												sdone = true;
												break;
											}
											case SQLITE_DONE:
											{
												if (debug_lvl >= 20 && debug_m)
												{
													sint xp = Output("SQLITE_DONE", 2);
												}
												sdone = true;
												break;
											}
											case SQLITE_ROW:
											{
												if (debug_lvl >= 20 && debug_m)
												{
													sint xp = Output("SQLITE_ROW", 2);
												}
												break;
											}
											case SQLITE_BUSY:
											{
												if (debug_lvl >= 20 && debug_m)
												{
													sint xp = Output("SQLITE_BUSY", 2);
												}
												sdone = true;
												break;
											}
											default:
											{
												if (debug_lvl >= 1 && debug_m)
												{
													sint xp = Output(GetError().c_str(), 1, 2, -1);
												}
												sdone = true;
												break;
											}
											}
										}
										rc = sqlite3_finalize(ppstmt);

										if (rc)
										{
											sint xp = Output(GetError().c_str(), 1, 2, -1);
										}
									}
									Comm.t[nsiz].Clear();
								}
							}
						}
					}
					if (began)
					{
						c_char* tail = "";
						sqlite3_stmt* ppstmt;

						if (debug_lvl >= 1 && debug_m)
						{
							sint xp = Output("preparing commit statement: COMMIT;", 2);
						}
						sint rc = sqlite3_prepare_v2(d_con_->db_, "COMMIT;", strlen("COMMIT;"), &ppstmt, &tail);

						if (rc)
						{
							sint xp = Output(GetError().c_str(), 1, 2, -1);
						}
						else
						{
							if (debug_lvl >= 1 && debug_m)
							{
								sint xp = Output("statement prepared", 2);
							}

							rc = sqlite3_step(ppstmt);

							switch (rc)
							{
							case SQLITE_OK:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_OK", 2);
								}
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_DONE", 2);
								}
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_ROW", 2);
								}
								break;
							}
							case SQLITE_BUSY:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_BUSY", 2);
								}
								break;
							}
							default:
							{
								sint xp = Output(GetError().c_str(), 1, 2, -1);
								break;
							}
							}
							rc = sqlite3_finalize(ppstmt);

							if (rc)
							{
								sint xp = Output(GetError().c_str(), 1, 2, -1);
							}
						}
					}
					for (uint i = 0; i < Comm.an.size(); i++)
					{
						sint viv = vtool.ValInVec(&Comm.dbs, Comm.an[i].dbname.c_str());

						if (viv > -1)
						{
							sint rc = 0;

							if (Comm.an[i].stmt.empty())
							{
								rc = BTS(&Comm.an[i]);
							}
							if (!rc)
							{
								c_char* tail = "";
								sqlite3_stmt* ppstmt;

								if (debug_lvl >= 1 && debug_m)
								{
									std::string output;
									output.append("preparing commit statement: ");
									output.append(Comm.an[i].stmt);
									sint xp = Output(output.c_str(), 2);
								}
								rc = sqlite3_prepare_v2(d_con_->db_, Comm.an[i].stmt.c_str(), (sint)Comm.an[i].stmt.length(), &ppstmt, &tail);

								if (rc)
								{
									sint xp = Output(GetError().c_str(), 1, 2, -1);
								}
								else
								{
									if (debug_lvl >= 1 && debug_m)
									{
										sint xp = Output("statement prepared", 2);
									}

									rc = sqlite3_step(ppstmt);

									switch (rc)
									{
									case SQLITE_OK:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_OK", 2);
										}
										break;
									}
									case SQLITE_DONE:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_DONE", 2);
										}
										break;
									}
									case SQLITE_ROW:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_ROW", 2);
										}
										break;
									}
									case SQLITE_BUSY:
									{
										if (debug_lvl >= 20 && debug_m)
										{
											sint xp = Output("SQLITE_BUSY", 2);
										}
										break;
									}
									default:
									{
										sint xp = Output(GetError().c_str(), 1, 2, -1);
										break;
									}
									}
									rc = sqlite3_finalize(ppstmt);

									if (rc)
									{
										sint xp = Output(GetError().c_str(), 1, 2, -1);
									}
								}
							}
						}
					}

					d_con_->o_com = false;
					xc = UpdMTXPrio();

					if (!Comm.dbs.empty())
					{
						for (uint xp = 0; xp < Comm.dbs.size(); xp++)
						{
							if (wos[xp])
							{
								Comm.dbs[xp].Clear();
							}
						}
						odb = CloseDBs(&Comm.dbs, &fwas);
					}
				}
				else
				{
					done = true;

					if (!Comm.t.empty())
					{
						for (size_t csiz = 0; csiz < Comm.t.size(); csiz++)
						{
							sint rc = vtool.ValInVec(&bot_t_pend, &Comm.t[csiz]);

							if (rc < 0)
							{
								rc = vtool.AddValToVec(&bot_t_pend, &Comm.t[csiz], false, true);
							}
							else
							{
								for (size_t usiz = 0; usiz < bot_t_pend[rc].cols.size(); usiz++)
								{
									if (!strcmp(bot_t_pend[rc].cols[usiz].c_str(), BOT_INCR_STR))
									{
										if (usiz < bot_t_pend[rc].vals.size())
										{
											rc = atoi(bot_t_pend[rc].vals[usiz].c_str()) + 1;
											bot_t_pend[rc].vals[usiz].clear();
											bot_t_pend[rc].vals[usiz].append(stool.ITOA(rc));
											usiz = bot_t_pend[rc].cols.size();
										}
									}
								}
							}
							Comm.t[csiz].Clear();
						}
						Comm.t.clear();
					}
				}

				for (size_t i = 0; i < Comm.t.size(); i++)
				{
					if (Comm.t[i].lid > -1)
					{
						sint xc = vtool.AddValToVec(&bot_t_pend, &Comm.t[i], false, false);
						Comm.t[i].Clear();
					}
				}

				if (stmts_->empty())
				{
					done = true;
				}
				if (!hx)
				{
					hx = UnlockGMutex(MTX_PEND);
				}
			}
		}
		if (debug_lvl >= 10 && debug_m)
		{
			sint oc = Output("Commit() End", 2);
		}
		return 0;
	}
	// ol_ is overlapping statements which require more db connections than are available. the default limit for attached dbs is 10. the limit function can only reduce the limit below the compile option. gcc -DHAVE_STRCHRNUL=0 -DSQLITE_LIMIT_ATTACHED=50 sqlite3.c -o myfile we apparently need to root the device to compile the source with these options. realky we must enable this option so that we can query from karge groups too. HAVE_STRCHRNULL must be 0 to compile on, so far,: Galaxy S4, Galaxy Note 3 10.1 this may incur a huge performance loss on the db.

	sint VerifyDatabases()
	{
		if (debug_lvl >= 10 && debug_m)
		{
			sint op = Output("::VerifyDatabases()", 2);
		}

		uint db_failed = 0;

		std::vector<std::string> nms
		{
			"litebot",
			"math",
			"code"
		};

		for (uint x = 0; x < nms.size(); x++)
		{
			BOT_FILE_M ndb(nms[x].c_str(), ".db", "", 3, BOT_DB_CON, -1, -1, lid);
			sint of = -1;
			sint xc = BOTOpenFile(&ndb, &of, true);

			if (xc < 0)
			{
				db_failed++;
			}
			else
			{
				xc = BOTCloseFile(&ndb);

				if (xc)
				{

					sint e = -1;
				}
			}
		}
		if (!db_failed)
		{
			for (sint i = 0; i < VecSize(MTX_DBL); i++)
			{
				BOT_DB_M dbs;
				sint xc = GetVecEle(&dbs, MTX_DBL, i); //we could get the whole list before loop, but other threads could edit elements during iteration
				xc = VerifyDatabase(&dbs);

				if (xc)
				{
					sint rc = CreateDatabase(&dbs);

					if (rc < 0)
					{
						db_failed++;
					}
					else
					{
						xc = VerifyDatabase(&dbs);

						if (xc)
						{
							db_failed++;
							dbs.exists = -10;
							xc = SetVecEleMem((void*)&dbs.exists, MTX_DBL, dbs.lid, BOT_DB_EXISTS, false);
						}
					}
				}
				else
				{
					if (dbs.exists < 1)
					{
						dbs.exists = 1;
						xc = SetVecEleMem((void*)&dbs.exists, MTX_DBL, dbs.lid, BOT_DB_EXISTS, false);
					}
				}
			}
		}
		return db_failed;
	}
	sint VerifyDatabase(BOT_DB_M *dbs_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::VerifyDatabase(BOT_DB_M *dbs_(%i))", (sint)dbs_);
			op = Output(outp.carr, 2);
		}

		if (!dbs_)
		{
			return -1;
		}

		std::vector<BOT_STMT> tvec;
		sint fdb = -1;
		sint hdb = -1;
		sint odb = OpenDB(dbs_, 2, &hdb, &fdb, false, true);

		if (odb > -1)
		{
			BOT_DB dbs;
			sint xc = GetVecEle((void*)&dbs, MTX_DBL, dbs_->lid, false);

			if (xc > -1)
			{
				d_con_->o_com = true;
				sint ud = UpdMTXPrio();
				xc = 0;

				for (uint cc = 0; cc < dbs_->tsiz; cc++)
				{
					sint v = VerifyTable(&dbs, &tvec, cc, odb);

					if (v)
					{
						xc++;
					}
				}

				d_con_->o_com = false;
				ud = UpdMTXPrio();
			}
			if (!hdb)
			{
				hdb = CloseDB(dbs_, &fdb);
			}
			if (!xc)
			{
				return 0;
			}
		}
		return -1;
	}
	sint VerifyTable(BOT_DB *dbs_ = 0, std::vector<BOT_STMT> *tvec_ = 0, sint x = -1, sint odb = -1)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_512 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::VerifyTable(BOT_DB *dbs_(%i), std::vector<BOT_STMT> *tvec_(%i), sint x(%i), sint odb(%i))", (sint)dbs_, (sint)tvec_, x, odb);
			op = Output(outp.carr, 2);
		}

		if (!dbs_ || !tvec_ || odb < 0 || x < 0)
		{
			return -1;
		}
		
		sint xxc = 0;
		sint fail = 0;

		while (!xxc)
		{
			BOT_STMT trans(false, 0, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
			sint rc = BQS(&trans);

			if (rc)
			{
				return 1;
			}

			c_char* tail;
			sqlite3_stmt* ppstmt;
			rc = sqlite3_prepare_v2(d_con_->db_, trans.stmt.c_str(), (sint)trans.stmt.length(), &ppstmt, &tail);

			if (rc)
			{
				std::string output;
				output.append(GetError().c_str());

				if (debug_lvl >= 1 && debug_m)
				{
					rc = Output(output.c_str(), 1, 2, -1);
				}

				rc = output.find("no such");
				output.clear();

				if (rc > -1)
				{
					fail++;
					trans.Clear();
					trans.Renew(false, 3, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
					trans.ifex = 1;

					for (rc = 0; rc < (sint)dbs_->columns[x][0].size(); rc++)
					{
						if (rc < (sint)dbs_->columns[x][1].size())
						{
							sint nx = trans.AddCol(dbs_->columns[x][0][rc].c_str(), dbs_->columns[x][1][rc].c_str());
						}
					}

					rc = vtool.AddValToVec(tvec_, &trans, true, true);
					trans.ic_type = 3;
					trans.targ = 0;
					rc = vtool.AddValToVec(tvec_, &trans, true, true);
				}

				if (!dbs_->type && x == 4)
				{
					sint h = -1;
					sint p = LockGMutex(MTX_STRT, &h);

					if (p > -1)
					{
						for (size_t ins = 0; ins < bot_strt.litebot_stmts.size(); ins++)
						{
							trans.Clear();
							trans.stmt.append(bot_strt.litebot_stmts[ins]);
							rc = vtool.AddValToVec(tvec_, &trans, true, true);
						}
						if (!h)
						{
							h = UnlockGMutex(MTX_STRT);
						}
					}
				}
				else if (dbs_->type == 2 && x == 4)
				{
					
				}
				else {}

				if (!x)
				{
					trans.Clear();
					trans.Renew(false, 2, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
					trans.cspec = 2;
					rc = vtool.AddValToVec(tvec_, &trans, true, true);
				}
				return 1;
			}
			else
			{
				sint tries = 0;
				bool e = true;
				bool done = false;

				while (!done)
				{
					rc = sqlite3_step(ppstmt);

					switch (rc)
					{
					case SQLITE_OK:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							rc = Output("SQLITE_OK", 2);
						}

						xxc++;
						done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							rc = Output("SQLITE_DONE", 2);
						}

						rc = sqlite3_column_count(ppstmt);

						if (rc == (sint)dbs_->columns[x][0].size())
						{
							if (debug_lvl >= 10 && debug_m)
							{
								rc = Output("structure count == db count", 2);
							}
						}
						else if ((sint)dbs_->columns[x][0].size() > rc)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								rc = Output("structure count > db count", 2);
							}
						}
						else
						{
							if (debug_lvl >= 10 && debug_m)
							{
								rc = Output("structure count < db count", 2);
							}
						}

						std::vector<std::string> ex_cols, m_cols;
						for (sint stcount = (sint)dbs_->columns[x][0].size() - 1; stcount > -1; stcount--)
						{
							rc = sqlite3_column_int(ppstmt, 0);

							if (rc)
							{
								rc = sqlite3_column_count(ppstmt) - 1;

								while (rc > -1)
								{
									if (!strcmp(sqlite3_column_name(ppstmt, rc), dbs_->columns[x][0][stcount].c_str()))
									{
										if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "TEXT"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_TEXT)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "INTEGER"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_INTEGER)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "REAL"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_FLOAT)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "BLOB"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_BLOB)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "NULL"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_NULL)
											{
												rc = -1;
											}
											else
											{
												ex_cols.push_back(dbs_->columns[x][0][stcount]);
												rc = -2;
											}
										}
										else
										{
											std::string findin;
											findin.append(dbs_->columns[x][1][stcount]);
											sint f = findin.find("INTEGER");

											if (f > -1)
											{
												if (sqlite3_column_type(ppstmt, rc) == SQLITE_INTEGER)
												{
													rc = -1;
												}
												else
												{
													if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
													{
														ex_cols.push_back(dbs_->columns[x][0][stcount]);
														rc = -2;
													}
													else
													{
														rc = -1;
													}
												}
											}
										}
									}
									rc--;
								}

								if (rc == -1)
								{
									m_cols.push_back(dbs_->columns[x][0][stcount]);
									m_cols.push_back(dbs_->columns[x][1][stcount]);
								}
								else if (rc == -3)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										carr_512 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "%s found but of type %s not found in table %s.%s", dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str(), dbs_->name.c_str(), dbs_->tables[x].c_str());
										op = Output(outp.carr, 2);
									}
								}
								else {}
							}
						}

						if (!ex_cols.empty())
						{
							fail++;
							std::string ncar;
							ncar.append(dbs_->tables[x]);
							ncar.append("_");
							BOT_STMT t(false, 3, dbs_->name.c_str(), ncar.c_str(), 2);
							t.ifex = 1;
							ncar.clear();

							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								t.AddCol(dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str());
							}

							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							ncar.append(dbs_->tables[x]);
							ncar.append("_");
							t.Renew(false, 2, dbs_->name.c_str(), ncar.c_str(), 1);

							for (sint stcount = 0; stcount < sqlite3_column_count(ppstmt); stcount++)
							{
								ncar.clear();
								ncar.append(sqlite3_column_name(ppstmt, stcount));
								rc = vtool.AddValToVec(&t.cols, ncar.c_str(), true, true);
							}

							std::string nval;
							nval.append(dbs_->tables[x]);
							//t.opts[11].push_back(0);
							rc = vtool.AddValToVec(&t.vals, nval.c_str(), true, true);
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 5, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							ncar.clear();
							ncar.append(dbs_->tables[x]);
							ncar.append("_");
							t.Renew(false, 7, dbs_->name.c_str(), ncar.c_str(), 1);
							t.act = 2;
							rc = vtool.AddValToVec(&t.vals, nval.c_str(), true, true);
							rc = vtool.AddValToVec(tvec_, &t, false, false);
							t.Clear();
							t.Renew(false, 3, dbs_->name.c_str(), dbs_->tables[x].c_str(), 2);
							t.targ = 0;
							t.ifex = 1;

							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								if (stcount < (sint)dbs_->columns[x][1].size())
								{
									rc = t.AddCol(dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str());
								}
							}

							rc = vtool.AddValToVec(tvec_, &t, true, true);
						}
						else
						{
							if (!m_cols.empty())
							{
								fail++;
								for (uint m = 0; m < (sint)m_cols.size(); m += 2)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										carr_512 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "%s %s not found in table %s.%s", m_cols[m].c_str(), m_cols[m + 1].c_str(), dbs_->name.c_str(), dbs_->tables[x].c_str());
										op = Output(outp.carr, 1, 2, -1);
									}

									BOT_STMT t(false, 7, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
									t.act = 1;
									rc = t.AddCol(m_cols[m].c_str(), m_cols[m + 1].c_str());
									rc = vtool.AddValToVec(tvec_, &t, true, true);
								}

								BOT_STMT t(false, 3, dbs_->name.c_str(), dbs_->tables[x].c_str(), 2);
								t.targ = 0;
								t.ifex = 1;

								for (rc = 0; rc < (sint)dbs_->columns[x][0].size(); rc++)
								{
									if (rc < (sint)dbs_->columns[x][1].size())
									{
										rc = t.AddCol(dbs_->columns[x][0][rc].c_str(), dbs_->columns[x][1][rc].c_str());
									}
								}
								rc = vtool.AddValToVec(tvec_, &t, true, true);
							}
						}

						if (e && !x)
						{
							BOT_STMT t(false, 2, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
							t.cspec = 2;
							rc = vtool.AddValToVec(tvec_, &t, true, true);
						}
						xxc++;
						done = true;
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							rc = Output("SQLITE_ROW", 2);
						}

						e = false;
						rc = sqlite3_column_count(ppstmt);

						if (rc == (sint)dbs_->columns[x][0].size())
						{
							if (debug_lvl >= 10 && debug_m)
							{
								rc = Output("structure count == db count", 2);
							}
						}
						else if ((sint)dbs_->columns[x][0].size() > rc)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								rc = Output("structure count > db count", 2);
							}
						}
						else
						{
							if (debug_lvl >= 10 && debug_m)
							{
								rc = Output("structure count < db count", 2);
							}
						}

						std::vector<std::string> ex_cols, m_cols;

						for (sint stcount = (sint)dbs_->columns[x][0].size() - 1; stcount > -1; stcount--)
						{
							rc = sqlite3_column_int(ppstmt, 0);

							if (rc)
							{
								rc = sqlite3_column_count(ppstmt) - 1;

								while (rc > -1)
								{
									if (!strcmp(sqlite3_column_name(ppstmt, rc), dbs_->columns[x][0][stcount].c_str()))
									{
										if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "TEXT"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_TEXT)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "INTEGER"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_INTEGER)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "REAL"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_FLOAT)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "BLOB"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_BLOB)
											{
												rc = -1;
											}
											else
											{
												if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
												{
													ex_cols.push_back(dbs_->columns[x][0][stcount]);
													rc = -2;
												}
												else
												{
													rc = -1;
												}
											}
										}
										else if (!strcmp(dbs_->columns[x][1][stcount].c_str(), "NULL"))
										{
											if (sqlite3_column_type(ppstmt, rc) == SQLITE_NULL)
											{
												rc = -1;
											}
											else
											{
												ex_cols.push_back(dbs_->columns[x][0][stcount]);
												rc = -2;
											}
										}
										else
										{
											std::string findin;
											findin.append(dbs_->columns[x][1][stcount]);
											sint f = findin.find("INTEGER");

											if (f > -1)
											{
												if (sqlite3_column_type(ppstmt, rc) == SQLITE_INTEGER)
												{
													rc = -1;
												}
												else
												{
													if (sqlite3_column_type(ppstmt, rc) != SQLITE_NULL)
													{
														ex_cols.push_back(dbs_->columns[x][0][stcount]);
														rc = -2;
													}
													else
													{
														rc = -1;
													}
												}
											}
										}
									}
									rc--;
								}
								if (rc == -1)
								{
									m_cols.push_back(dbs_->columns[x][0][stcount]);
									m_cols.push_back(dbs_->columns[x][1][stcount]);
								}
								else if (rc == -3)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										carr_512 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "%s %s not found in table %s.%s", dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str(), dbs_->name.c_str(), dbs_->tables[x].c_str());
										op = Output(outp.carr, 1, 2, -1);
									}
								}
								else {}
							}
						}
						if (!ex_cols.empty())
						{
							fail++;
							std::string ntn;
							ntn.append(dbs_->tables[x]);
							ntn.append("_");
							BOT_STMT t(false, 3, dbs_->name.c_str(), ntn.c_str(), 1);
							t.ifex = 1;
							
							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								if (stcount < (sint)dbs_->columns[x][1].size())
								{
									rc = t.AddCol(dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str());
								}
							}

							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 2, dbs_->name.c_str(), ntn.c_str(), 1);

							for (sint stcount = 0; stcount < sqlite3_column_count(ppstmt); stcount++)
							{
								std::string ncol;
								ncol.append(sqlite3_column_name(ppstmt, stcount));
								rc = vtool.AddValToVec(&t.cols, ncol.c_str(), true, true);
							}

							//t.opts[11].push_back(0);
							std::string nval;
							nval.append(dbs_->tables[x]);
							rc = vtool.AddValToVec(&t.vals, nval.c_str(), true, true);

							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								rc = (sint)ex_cols.size() - 1;

								while (rc > -1)
								{
									if (!strcmp(dbs_->columns[x][0][stcount].c_str(), ex_cols[rc].c_str()))
									{
										rc = -1;
									}
									rc--;
								}

								if (rc == -1)
								{

								}
							}

							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 5, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 7, dbs_->name.c_str(), ntn.c_str(), 1);
							t.act = 2;
							rc = vtool.AddValToVec(&t.vals, nval.c_str(), true, true);
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 3, dbs_->name.c_str(), dbs_->tables[x].c_str(), 2);
							t.targ = 0;
							t.ifex = 1;

							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								if (stcount < (sint)dbs_->columns[x][1].size())
								{
									rc = t.AddCol(dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str());
								}
							}
							rc = vtool.AddValToVec(tvec_, &t, true, true);
						}
						else
						{
							if (!m_cols.empty())
							{
								fail++;
								for (uint m = 0; m < m_cols.size(); m += 2)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										carr_512 outp;
										sint op = bot_sprintf(outp.carr, outp.siz, "%s %s not found in table %s.%s", m_cols[m].c_str(), m_cols[m + 1].c_str(), dbs_->name.c_str(), dbs_->tables[x].c_str());
										op = Output(outp.carr, 2);
									}

									BOT_STMT t(false, 7, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
									t.act = 1;
									rc = t.AddCol(m_cols[m].c_str(), m_cols[m + 1].c_str());
									rc = vtool.AddValToVec(tvec_, &t, true, true);
								}

								BOT_STMT t(false, 3, dbs_->name.c_str(), dbs_->tables[x].c_str(), 2);
								t.targ = 0;
								t.ifex = 1;

								for (rc = 0; rc < (sint)dbs_->columns[x][0].size(); rc++)
								{
									if (rc < (sint)dbs_->columns[x][1].size())
									{
										sint nx = t.AddCol(dbs_->columns[x][0][rc].c_str(), dbs_->columns[x][1][rc].c_str());
									}
								}
								rc = vtool.AddValToVec(tvec_, &t, true, true);
							}
						}
						xxc++;
						done = true;
						break;
					}
					case SQLITE_BUSY:
					{
						sint xp = Output("SQLITE_BUSY", 1);
						done = true;
						tries++;
						break;
					}
					default:
					{
						rc = Output(GetError().c_str(), 1, 2, -1);
						xxc++;
						done = true;
						break;
					}
					}

					if (tries > 3)
					{
						fail++;
						xxc++;
						done = true;
					}
				}
			}

			rc = sqlite3_finalize(ppstmt);

			if (rc)
			{
				if (debug_lvl >= 10 && debug_m)
				{
					rc = Output(GetError().c_str(), 1, 2, -1);
				}
			}
		}
		return fail;
	}
	sint CreateDatabase(BOT_DB_M *dbs_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::CreateDatabase(BOT_DB *dbs_(%i))", (sint)dbs_);
			op = Output(outp.carr, 2);
		}

		if (!dbs_)
		{
			return -1;
		}

		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "creating db: \"%s\"", dbs_->name.c_str());
			op = Output(outp.carr, 2);
		}

		if (!strlen(dbs_->name.c_str()))
		{
			return -1;
		}

		BOT_DB dbs;
		sint xc = GetVecEle((void*)&dbs, MTX_DBL, dbs_->lid, false);
		std::vector<BOT_STMT> sepsql;

		for (size_t s = 0; s < dbs.tables.size(); s++)
		{
			BOT_STMT t(false, 3, dbs.name.c_str(), dbs.tables[s].c_str(), 1);
			t.ifex = 1;

			for (size_t xs = 0; xs < dbs.columns[s][0].size(); xs++)
			{
				sint oc = t.AddCol(dbs.columns[s][0][xs].c_str(), dbs.columns[s][1][xs].c_str());
			}
			sint oc = vtool.AddValToVec(&sepsql, &t, true, true);
			t.ic_type = 2;
			t.targ = 0;
			oc = vtool.AddValToVec(&sepsql, &t, true, true);

			if (!s)
			{
				t.Clear();
				t.Renew(false, 2, dbs.name.c_str(), dbs.tables[s].c_str(), 1);
				t.cspec = 2;
				xc = vtool.AddValToVec(&sepsql, &t, true, true);
			}
		}

		if (!dbs.type)
		{
			sint h = -1;
			sint p = LockGMutex(MTX_STRT, &h);

			if (p > -1)
			{
				for (size_t ins = 0; ins < bot_strt.litebot_stmts.size(); ins++)
				{
					BOT_STMT t;
					t.stmt.append(bot_strt.litebot_stmts[ins]);
					sint xc = vtool.AddValToVec(&sepsql, &t, true, true);
				}

				bot_strt.litebot_stmts.clear();

				for (size_t ins = 0; ins < bot_strt.litebot_pend.size(); ins++)
				{
					sepsql.push_back(bot_strt.litebot_pend[ins]);
				}

				bot_strt.litebot_pend.clear();

				if (!h)
				{
					h = UnlockGMutex(MTX_STRT);
				}
			}
		}
		else if (dbs.type == 2)
		{
			sint h = -1;
			sint p = LockGMutex(MTX_STRT, &h);

			if (p > -1)
			{
				for (uint x = 0; x < bot_strt.code_pend.size(); x++)
				{
					sepsql.push_back(bot_strt.code_pend[x]);
				}

				bot_strt.code_pend.clear();

				if (!h)
				{
					h = UnlockGMutex(MTX_STRT);
				}
			}
		}
		else {}

		sint s = Commit(&sepsql);

		if (!s)
		{
			if (dbs_->exists < 0)
			{
				dbs_->exists = 1;
				sint xc = SetVecEleMem(&dbs_->exists, MTX_DBL, dbs_->lid, BOT_DB_EXISTS, false);
			}
		}
		return s;
	}

	sint GetSymbol(MICSYM *sym_ = 0, c_char x_cond_[] = 0, bool maint = false) { if (!sym_) { return -1; } std::vector<MICSYM> vec; vec.push_back(*sym_); return GetSymbols(&vec, x_cond_, maint); }
	sint GetSymbols(std::vector <MICSYM> *syms_ = 0, c_char x_cond_[] = 0, bool maint = false)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::GetSymbols(std::vector <MICSYM> *syms_(%i), c_char* x_cond_(%i), bool maint(%u))", (sint)syms_, (sint)x_cond_, (uint)maint);
			op = Output(outp.carr, 2);
		}

		if (!syms_)
		{
			return -1;
		}

		sint rc = -1;
		std::vector<BOT_STMT> stmts;

		for (size_t nsiz = 0; nsiz < syms_->size(); nsiz++)
		{
			if (syms_->at(nsiz).id > -2)
			{
				BOT_STMT t(maint, 0, "litebot", "SYMS", 1);

				if (!maint)
				{
					t.cspec = 0;
					_char dval[(sizeof(syms_->at(nsiz).sym) * 2) + 4]{ 0 };
					rc = bot_sprintf(dval, sizeof(dval), "X'%02X'", syms_->at(nsiz).sym);
					rc = t.AddCond(0, "SYMBOL", sql_comp_keywords[5], dval);
				}

				if (x_cond_)
				{
					if (strlen(x_cond_))
					{
						rc = t.AddCond(x_cond_);
					}
				}

				if (syms_->at(nsiz).id > -1)
				{
					_char outc[21]{ 0 };
					rc = bot_sprintf(outc, 21, "%i", syms_->at(nsiz).id);
					rc = t.AddCond(0, "ID", sql_comp_keywords[5], outc);
				}

				rc = vtool.AddValToVec(&stmts, &t, true, true);

				if (rc)
				{
					sint cheq = -1;
				}
			}
		}

		if (stmts.empty())
		{
			return -1;
		}

		BOT_DB_M dbs("litebot", 0);
		sint fdb = -1;
		sint hdb = -1;
		sint odb = OpenDB(&dbs, 1, &hdb, &fdb);

		if (odb > -1)
		{
			for (size_t siz = 0; siz < stmts.size(); siz++)
			{
				rc = BQS(&stmts[siz]);

				if (!rc)
				{
					d_con_->o_com = true;
					rc = UpdMTXPrio();
					c_char* tail;
					sqlite3_stmt* ppstmt;
					rc = sqlite3_prepare_v2(d_con_->db_, stmts[siz].stmt.c_str(), (sint)stmts[siz].stmt.length(), &ppstmt, &tail);

					if (rc)
					{
						rc = Output(GetError().c_str(), 1, 2, -1);
					}
					else
					{
						bool done = false;

						while (!done)
						{
							rc = sqlite3_step(ppstmt);

							switch (rc)
							{
							case SQLITE_OK:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_OK", 2);
								}
								done = true;
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_DONE", 2);
								}
								done = true;
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_ROW", 2);
								}

								rc = FindColumn("SYMBOL", ppstmt);

								if (rc > -1)
								{
									uint ui = sqlite3_column_bytes(ppstmt, rc);

									if (ui && ui < BOT_STRLEN_MAX)
									{
										u_char* suc = (u_char*)malloc(ui + 1);

										if (suc)
										{
											u_char echar = (u_char)'\0';
											memcpy((void*)suc, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
											memcpy((void*)&suc[ui], (void*)&echar, 1);

											for (size_t nsiz = 0; nsiz < syms_->size(); nsiz++)
											{
												if (!memcmp(&suc[0], &syms_->at(nsiz).sym, 1))
												{
													rc = FindColumn("ID", ppstmt);

													if (rc > -1)
													{
														syms_->at(nsiz).id = sqlite3_column_int(ppstmt, rc);

														for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
														{
															if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
															{
																syms_->at(xsiz).id = syms_->at(nsiz).id;
															}
														}
													}

													rc = FindColumn("ENCODINGS", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															u_char* nuchar = (u_char*)malloc(ui + 1);

															if (nuchar)
															{
																memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
																memcpy((void*)&nuchar[ui], (void*)&echar, 1);

																for (size_t fi = 0; fi < ui; fi++)
																{
																	sint xi = vtool.AddValToVec(&syms_->at(nsiz).encodings, (uint)nuchar[fi], true, false);

																	for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																	{
																		if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																		{
																			xi = vtool.AddValToVec(&syms_->at(xsiz).encodings, (uint)nuchar[fi], true, false);
																		}
																	}
																}
															}
															free(nuchar);
														}
													}

													rc = FindColumn("HISTORY_FOLLOWING", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															u_char* nuchar = (u_char*)malloc(ui + 1);

															if (nuchar)
															{
																u_char sep = (u_char)',';
																memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
																memcpy((void*)&nuchar[ui], (void*)&echar, 1);
																std::vector<HIST_F> nvec;

																for (uint usiz = 0; (usiz + 1) < ui; usiz += 3)
																{
																	if (!memcmp((void*)&nuchar[usiz], &sep, 1) && !nvec.empty())
																	{
																		syms_->at(nsiz).history_following.push_back(nvec);

																		for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																		{
																			if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																			{
																				syms_->at(xsiz).history_following.push_back(nvec);
																			}
																		}
																		usiz++;
																		nvec.clear();
																	}
																	else
																	{
																		if (usiz)
																		{
																			usiz--;
																		}
																		HIST_F hf(&nuchar[usiz], (uint)nuchar[usiz + 1]);
																		nvec.push_back(hf);
																	}
																}
																if (!nvec.empty())
																{
																	syms_->at(nsiz).history_following.push_back(nvec);

																	for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																	{
																		if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																		{
																			syms_->at(xsiz).history_following.push_back(nvec);
																		}
																	}
																}
															}
															free(nuchar);
														}
													}

													rc = FindColumn("HISTORY_PRECEEDING", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															u_char* nuchar = (u_char*)malloc(ui + 1);

															if (nuchar)
															{
																u_char sep = (u_char)',';
																memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
																memcpy((void*)&nuchar[ui], (void*)&echar, 1);
																std::vector<HIST_P> nvec;

																for (uint usiz = 0; (usiz + 1) < ui; usiz += 3)
																{
																	if (!memcmp((void*)&nuchar[usiz], &sep, 1) && !nvec.empty())
																	{
																		syms_->at(nsiz).history_preceeding.push_back(nvec);

																		for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																		{
																			if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																			{
																				syms_->at(xsiz).history_preceeding.push_back(nvec);
																			}
																		}
																		usiz++;
																		nvec.clear();
																	}
																	else
																	{
																		if (usiz)
																		{
																			usiz--;
																		}
																		HIST_P hf(&nuchar[usiz], (uint)nuchar[usiz + 1]);
																		nvec.push_back(hf);
																	}
																}
																if (!nvec.empty())
																{
																	syms_->at(nsiz).history_preceeding.push_back(nvec);

																	for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																	{
																		if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																		{
																			syms_->at(xsiz).history_preceeding.push_back(nvec);
																		}
																	}
																}
															}
															free(nuchar);
														}
													}

													rc = FindColumn("CONSTITUENT_TO", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															u_char* nuchar = (u_char*)malloc(ui + 1);

															if (nuchar)
															{
																u_char lsep = (u_char)' ';
																u_char sep = (u_char)',';
																memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
																memcpy((void*)&nuchar[ui], (void*)&echar, 1);
																std::vector<std::vector<u_char>> nvec;
																std::vector<u_char> uvec;

																for (uint usiz = 0; usiz < ui; usiz++)
																{
																	if (!memcmp((void*)&nuchar[usiz], (void*)&sep, 1) && !nvec.empty())
																	{
																		syms_->at(nsiz).constituent_to.push_back(nvec);

																		for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																		{
																			if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																			{
																				syms_->at(xsiz).constituent_to.push_back(nvec);
																			}
																		}
																		nvec.clear();
																		usiz++;
																	}
																	else if (!memcmp((void*)&nuchar[usiz], (void*)&lsep, 1) && !uvec.empty())
																	{
																		sint xi = vtool.AddValToVec(&nvec, &uvec, true, false);

																		for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																		{
																			if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																			{
																				xi = vtool.AddValToVec(&nvec, &uvec, true, false);
																			}
																		}
																		uvec.clear();
																		usiz++;
																	}
																	else
																	{
																		uvec.push_back(nuchar[usiz]);
																	}
																}
																if (!nvec.empty())
																{
																	syms_->at(nsiz).constituent_to.push_back(nvec);

																	for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																	{
																		if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																		{
																			syms_->at(xsiz).constituent_to.push_back(nvec);
																		}
																	}
																}
															}
															free(nuchar);
														}
													}
													rc = FindColumn("LAST_MODIFIED", ppstmt);

													if (rc > -1)
													{
														syms_->at(nsiz).last_modified = sqlite3_column_int(ppstmt, rc);

														for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
														{
															if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
															{
																syms_->at(xsiz).last_modified = sqlite3_column_int(ppstmt, rc);
															}
														}
													}

													rc = FindColumn("LAST_MAINTAINED", ppstmt);

													if (rc > -1)
													{
														syms_->at(nsiz).last_maintained = sqlite3_column_int(ppstmt, rc);

														for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
														{
															if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
															{
																syms_->at(xsiz).last_maintained = sqlite3_column_int(ppstmt, rc);
															}
														}
													}

													rc = FindColumn("LAST_MODIFIED_NS", ppstmt);

													if (rc > -1)
													{
														syms_->at(nsiz).last_modified_ns = sqlite3_column_int(ppstmt, rc);

														for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
														{
															if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
															{
																syms_->at(xsiz).last_modified_ns = sqlite3_column_int(ppstmt, rc);
															}
														}
													}

													rc = FindColumn("LAST_MAINTAINED_NS", ppstmt);

													if (rc > -1)
													{
														syms_->at(nsiz).last_maintained_ns = sqlite3_column_int(ppstmt, rc);

														for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
														{
															if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
															{
																syms_->at(xsiz).last_maintained_ns = sqlite3_column_int(ppstmt, rc);
															}
														}
													}
												}
											}
										}
										free(suc);
									}
								}
								break;
							}
							case SQLITE_BUSY:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_BUSY", 2);
								}
								done = true;
								break;
							}
							default:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output(GetError().c_str(), 1, 2, -1);
								}
								done = true;
								break;
							}
							}
						}

						rc = sqlite3_finalize(ppstmt);

						if (rc)
						{
							sint xp = Output(GetError().c_str(), 1, 2, -1);
						}
					}
					d_con_->o_com = false;
					rc = UpdMTXPrio();
				}
			}

			if (!hdb)
			{
				hdb = CloseDB(&dbs, &fdb);
			}
			if (!maint)
			{
				for (size_t siz = 0; siz < syms_->size(); siz++)
				{
					if (syms_->at(siz).last_maintained < syms_->at(siz).last_modified || ((syms_->at(siz).last_maintained == syms_->at(siz).last_modified) && (syms_->at(siz).last_maintained_ns < syms_->at(siz).last_modified_ns)))
					{
						sint xp = syms_->at(siz).Proc();
					}
				}
			}
			if (debug_lvl >= 1 && debug_m)
			{
				sint xp = Output("GetSymbols() done", 2);
			}
			return 0;
		}
		return -1;
	}
	sint AddSymbol(MICSYM* sym_ = 0) { if (!sym_) { return -1; } std::vector<MICSYM> vec; vec.push_back(*sym_); return AddSymbols(&vec); }
	sint AddSymbols(std::vector <MICSYM> *syms_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::AddSymbols(std::vector <MICSYM> *syms_(%i))", (sint)syms_);
			op = Output(outp.carr, 2);
		}

		if (!syms_)
		{
			return -1;
		}
		if (syms_->empty())
		{
			return -1;
		}

		std::vector<size_t> eles;

		for (size_t x = 0; x < syms_->size(); x++)
		{
			bool aud = false;

			if (syms_->at(x).id > -2)
			{
				for (size_t xc = x + 1; xc < syms_->size(); xc++)
				{
					if (!memcmp(&syms_->at(x).sym, &syms_->at(xc).sym, sizeof(syms_->at(x).sym)))
					{
						if (syms_->at(x).id == syms_->at(xc).id || syms_->at(xc).id < 0)
						{
							if (!syms_->at(xc).encodings.empty())
							{
								for (size_t cf = 0; cf < syms_->at(xc).encodings.size() && cf < syms_->at(xc).constituent_to.size() && cf < syms_->at(xc).history_preceeding.size() && cf < syms_->at(xc).history_following.size(); cf++)
								{
									sint xf = syms_->at(x).AddEnc(syms_->at(xc).encodings[cf], &syms_->at(xc).constituent_to[cf], &syms_->at(xc).history_preceeding[cf], &syms_->at(xc).history_following[cf]);

									if (xf > -1)
									{
										if (!syms_->at(x).ud_encodings)
										{
											syms_->at(x).ud_encodings = true;
											aud = true;
										}
										if (!syms_->at(x).ud_constituent_to)
										{
											syms_->at(x).ud_constituent_to = true;
											aud = true;
										}
										if (!syms_->at(x).ud_history_preceeding)
										{
											syms_->at(x).ud_history_preceeding = true;
											aud = true;
										}
										if (!syms_->at(x).ud_history_following)
										{
											syms_->at(x).ud_history_following = true;
											aud = true;
										}
									}
								}
							}
							else
							{
								if (syms_->at(xc).ud_encodings)
								{
									if (!syms_->at(x).ud_encodings)
									{
										syms_->at(x).ud_encodings = true;
										aud = true;
									}
									syms_->at(x).encodings.clear();
									syms_->at(x).constituent_to.clear();
									syms_->at(x).history_following.clear();
									syms_->at(x).history_preceeding.clear();
								}
							}

							if (syms_->at(xc).constituent_to.empty())
							{
								if (syms_->at(xc).ud_constituent_to)
								{
									if (!syms_->at(x).ud_constituent_to)
									{
										syms_->at(x).ud_constituent_to = true;
										aud = true;
									}
									syms_->at(x).constituent_to.clear();
								}
							}

							if (syms_->at(xc).history_following.empty())
							{
								if (syms_->at(xc).ud_history_following)
								{
									if (!syms_->at(x).ud_history_following)
									{
										syms_->at(x).ud_history_following = true;
										aud = true;
									}
									syms_->at(x).history_following.clear();
								}
							}

							if (syms_->at(xc).history_preceeding.empty())
							{
								if (syms_->at(xc).ud_history_preceeding)
								{
									if (!syms_->at(x).ud_history_preceeding)
									{
										syms_->at(x).ud_history_preceeding = true;
										aud = true;
									}
									syms_->at(x).history_preceeding.clear();
								}
							}

							if (syms_->at(xc).last_modified > syms_->at(x).last_modified)
							{
								if (!syms_->at(x).ud_last_modified)
								{
									syms_->at(x).ud_last_modified = true;
								}
								syms_->at(x).last_modified = syms_->at(xc).last_modified;
							}

							if (syms_->at(xc).last_modified_ns > syms_->at(x).last_modified_ns)
							{
								if (!syms_->at(x).ud_last_modified_ns)
								{
									syms_->at(x).ud_last_modified_ns = true;
								}
								syms_->at(x).last_modified_ns = syms_->at(xc).last_modified_ns;
							}

							if (syms_->at(xc).last_maintained > syms_->at(x).last_maintained)
							{
								if (!syms_->at(x).ud_last_maintained)
								{
									syms_->at(x).ud_last_maintained = true;
								}
								syms_->at(x).last_maintained = syms_->at(xc).last_maintained;
							}

							if (syms_->at(xc).last_maintained_ns > syms_->at(x).last_maintained_ns)
							{
								if (!syms_->at(x).ud_last_maintained_ns)
								{
									syms_->at(x).ud_last_maintained_ns = true;
								}
								syms_->at(x).last_maintained_ns = syms_->at(xc).last_maintained_ns;
							}

							syms_->at(xc).id = -2;
						}
					}
				}
				sint rx = syms_->at(x).Proc();
				rx = vtool.AddValToVec(&eles, x, true, false);
			}
		}

		sint rc = GetSymbols(syms_, "", false);
		std::vector<BOT_STMT> tvec;

		for (size_t x = 0; x < eles.size(); x++)
		{
			BOT_STMT t(syms_->at(eles[x]).ud_last_maintained, 1, "litebot", "SYMS", 1);

			if (syms_->at(eles[x]).id < 0)
			{
				t.it_type = 2;
				t.cspec = 2;

				if (sizeof(syms_->at(eles[x]).sym))
				{
					_char xstr[(sizeof(syms_->at(eles[x]).sym) * 2) + 8]{ 0 };
					sint xp = bot_sprintf(xstr, sizeof(xstr), "X'%02X'", syms_->at(eles[x]).sym);
					xp = vtool.AddValToVec(&t.cols, "SYMBOL", false, false);
					xp = vtool.AddValToVec(&t.vals, xstr, false, false);
				}

				if (!syms_->at(eles[x]).encodings.empty())
				{
					std::string str;
					for (size_t xs = 0; xs < syms_->at(eles[x]).encodings.size(); xs++)
					{
						_char ci[(sizeof(syms_->at(eles[x]).encodings[xs]) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (u_char)syms_->at(eles[x]).encodings[xs]);
						str.append(ci);
					}
					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "ENCODINGS", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (!syms_->at(eles[x]).constituent_to.empty())
				{
					u_char lsep = (u_char)' ';
					u_char sep = (u_char)',';
					std::string str;

					for (size_t xs = 0; xs < syms_->at(eles[x]).constituent_to.size(); xs++)
					{
						for (size_t nsiz = 0; nsiz < syms_->at(eles[x]).constituent_to[xs].size(); nsiz++)
						{
							for (size_t xsiz = 0; xsiz < syms_->at(eles[x]).constituent_to[xs][nsiz].size(); xsiz++)
							{
								_char ci[(sizeof(syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]);
								str.append(ci);
							}
							_char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}
						_char xi[(sizeof(lsep) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
						str.append(xi);
					}
					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "CONSTITUENT_TO", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (!syms_->at(eles[x]).history_following.empty())
				{
					u_char sep = (u_char)',';
					std::string str;
					for (size_t xx = 0; xx < syms_->at(eles[x]).history_following.size(); xx++)
					{
						for (size_t xs = 0; xs < syms_->at(eles[x]).history_following[xx].size(); xs++)
						{
							_char ci[(sizeof(syms_->at(eles[x]).history_following[xx][xs].sym) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_following[xx][xs].sym);
							str.append(ci);
							_char xi[(sizeof(syms_->at(eles[x]).history_following[xx][xs].ct) * 2) + 1]{ 0 };
							xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)syms_->at(eles[x]).history_following[xx][xs].ct);
							str.append(xi);
						}
						_char xi[(sizeof(sep) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
						str.append(xi);
					}
					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (!syms_->at(eles[x]).history_preceeding.empty())
				{
					u_char sep = (u_char)',';
					std::string str;

					for (size_t xx = 0; xx < syms_->at(eles[x]).history_preceeding.size(); xx++)
					{
						for (size_t xs = 0; xs < syms_->at(eles[x]).history_preceeding[xx].size(); xs++)
						{
							_char ci[(sizeof(syms_->at(eles[x]).history_preceeding[xx][xs].sym) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_preceeding[xx][xs].sym);
							str.append(ci);
							_char xi[(sizeof(syms_->at(eles[x]).history_preceeding[xx][xs].ct) * 2) + 1]{ 0 };
							xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)syms_->at(eles[x]).history_preceeding[xx][xs].ct);
							str.append(xi);
						}
						_char xi[(sizeof(sep) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
						str.append(xi);
					}
					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (!t.cont.empty())
				{
					sint xc = vtool.AddValToVec(&tvec, &t, false, true);
				}
			}
			else
			{
				t.cspec = 0;
				t.act = 0;

				if (syms_->at(eles[x]).ud_id)
				{
					vtool.AddValToVec(&t.cols, "ID", false, false);
					vtool.AddValToVec(&t.vals, stool.ITOA(syms_->at(eles[x]).id).c_str(), false, false);
				}

				if (syms_->at(eles[x]).ud_sym)
				{
					if (sizeof(syms_->at(eles[x]).sym))
					{
						_char xstr[(sizeof(syms_->at(eles[x]).sym) * 2) + 8]{ 0 };
						sint xp = bot_sprintf(xstr, sizeof(xstr), "X'%02X'", syms_->at(eles[x]).sym);
						xp = vtool.AddValToVec(&t.cols, "SYMBOL", false, false);
						xp = vtool.AddValToVec(&t.vals, xstr, false, false);
					}
				}

				if (syms_->at(eles[x]).ud_encodings)
				{
					std::string str;
					for (size_t a = 0; a < syms_->at(eles[x]).encodings.size(); a++)
					{
						_char ci[(sizeof(syms_->at(eles[x]).encodings[a]) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (u_char)syms_->at(eles[x]).encodings[a]);
						str.append(ci);
					}
					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "ENCODINGS", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (syms_->at(eles[x]).ud_constituent_to)
				{
					u_char lsep = (u_char)' ';
					u_char sep = (u_char)',';
					std::string str;
					for (size_t xs = 0; xs < syms_->at(eles[x]).constituent_to.size(); xs++)
					{
						for (size_t nsiz = 0; nsiz < syms_->at(eles[x]).constituent_to[xs].size(); nsiz++)
						{
							for (size_t xsiz = 0; xsiz < syms_->at(eles[x]).constituent_to[xs][nsiz].size(); xsiz++)
							{
								_char ci[(sizeof(syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]);
								str.append(ci);
							}
							_char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}
						_char xi[(sizeof(lsep) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
						str.append(xi);
					}
					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "CONSTITUENT_TO", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (syms_->at(eles[x]).ud_history_following)
				{
					std::string str;
					u_char sep = (u_char)',';

					for (size_t a = 0; a < syms_->at(eles[x]).history_following.size(); a++)
					{
						for (size_t b = 0; b < syms_->at(eles[x]).history_following[a].size(); b++)
						{
							_char ci[(sizeof(syms_->at(eles[x]).history_following[a][b].sym) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_following[a][b].sym);
							str.append(ci);
							_char xi[(sizeof(syms_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{ 0 };
							xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)syms_->at(eles[x]).history_following[a][b].ct);
							str.append(xi);
						}
						_char xi[(sizeof(sep) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
						str.append(xi);
					}

					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (syms_->at(eles[x]).ud_history_preceeding)
				{
					std::string str;
					u_char sep = (u_char)',';

					for (size_t a = 0; a < syms_->at(eles[x]).history_preceeding.size(); a++)
					{
						for (size_t b = 0; b < syms_->at(eles[x]).history_preceeding[a].size(); b++)
						{
							_char ci[(sizeof(syms_->at(eles[x]).history_preceeding[a][b].sym) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_preceeding[a][b].sym);
							str.append(ci);
							_char xi[(sizeof(syms_->at(eles[x]).history_preceeding[a][b].ct) * 2) + 1]{ 0 };
							xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)syms_->at(eles[x]).history_preceeding[a][b].ct);
							str.append(xi);
						}
						_char xi[(sizeof(sep) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
						str.append(xi);
					}

					if (!str.empty())
					{
						sint xp = vtool.AddValToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
						xp = vtool.AddValToVec(&t.vals, "X'", false, false);
						if (xp > -1)
						{
							t.vals[xp].append(str.c_str());
							t.vals[xp].push_back('\'');
						}
					}
				}

				if (syms_->at(eles[x]).id > 0)
				{
					sint xp = t.AddCond(0, "ID", sql_comp_keywords[5], stool.ITOA(syms_->at(eles[x]).id).c_str());
				}
				_char str_[(sizeof(syms_->at(eles[x]).sym) * 2) + 4]{ 0 };
				sint xc = bot_sprintf(str_, sizeof(str_), "X'%02X'", syms_->at(eles[x]).sym);
				xc = t.AddCond(0, "SYMBOL", sql_comp_keywords[5], str_);
				xc = vtool.AddValToVec(&tvec, &t, true, true);
			}
		}
		if (!tvec.empty())
		{
			if (rc > -1)
			{
				return Commit(&tvec);
			}
			else
			{
				sint h = -1;
				sint l = LockGMutex(MTX_STRT, &h);

				if (l > -1)
				{
					for (uint x = 0; x < tvec.size(); x++)
					{
						rc = vtool.AddValToVec(&bot_strt.litebot_pend, &tvec[x], true, true);
					}
					if (!h)
					{
						h = UnlockGMutex(MTX_STRT);
					}
				}
			}
		}
		return -1;
	}
	sint GetCode(MACSYM* code_ = 0, c_char x_cond_[] = 0, bool maint = false) { if (!code_) { return -1; } std::vector<MACSYM> vec; vec.push_back(*code_); return GetCode(&vec, x_cond_,maint); }
	sint GetCode(std::vector<MACSYM>* codes_ = 0, c_char x_cond_[] = 0, bool maint = false)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::GetCode(std::vector <MACSYM> *codes_(%i), c_char* x_cond_(%i), bool maint(%u))", (sint)codes_, (sint)x_cond_, (uint)maint);
			op = Output(outp.carr, 2);
		}

		if (!codes_)
		{
			return -1;
		}
		
		BOT_DB cdb("code", 2);
		sint rc = GetInVec((void*)&cdb, MTX_DBL, false, false);

		if (rc < 0 || cdb.exists < 0)
		{
			return -1;
		}

		std::vector<BOT_STMT> stmts;

		for (size_t xsiz = 0; xsiz < codes_->size(); xsiz++)
		{
			if (!codes_->at(xsiz).cons.empty())
			{
				for (size_t siz = 1; siz < cdb.tables.size(); siz++)
				{
					if (codes_->at(xsiz).used_as > -1 && codes_->at(xsiz).used_as < (sint)cdb.tables.size())
					{
						siz = codes_->at(xsiz).used_as;
					}

					BOT_STMT t(maint, 0, cdb.name.c_str(), cdb.tables[siz].c_str(), 1);
					t.cspec = 0;

					if (!maint)
					{
						std::string str;
						str.append("X'");
						for (size_t siz = 0; siz < codes_->at(xsiz).cons.size(); siz++)
						{
							_char nchr[(sizeof(codes_->at(xsiz)).cons[siz] * 2) + 1]{ 0 };
							rc = bot_sprintf(nchr, sizeof(nchr), "%02X", codes_->at(xsiz).cons[siz].sym);
							str.append(nchr);
						}

						str.append("'");

						if (str.length() > 3)
						{
							rc = t.AddCond(0, "DATA", sql_comp_keywords[5], str.c_str());
						}
					}

					if (x_cond_)
					{
						if (strlen(x_cond_))
						{
							rc = t.AddCond(x_cond_);
						}
					}

					if (codes_->at(xsiz).id > -1)
					{
						_char outc[21]{ 0 };
						rc = bot_sprintf(outc, 21, "%i", codes_->at(xsiz).id);
						rc = t.AddCond(0, "ID", sql_comp_keywords[5], outc);
					}
					
					stmts.push_back(t);

					if (codes_->at(xsiz).used_as > -1 && codes_->at(xsiz).used_as < (sint)cdb.tables.size())
					{
						siz = cdb.tables.size();
					}
				}
			}
		}
		
		if (stmts.empty())
		{
			return -1;
		}

		sint fdb = -1;
		sint hdb = -1;
		BOT_DB_M dbs;
		dbs.Renew(&cdb);
		sint odb = OpenDB(&dbs, 1, &hdb, &fdb);

		if (odb > -1)
		{
			for (size_t siz = 0; siz < stmts.size(); siz++)
			{
				rc = BQS(&stmts[siz]);

				if (!rc)
				{
					d_con_->o_com = true;
					rc = UpdMTXPrio();
					c_char* tail;
					sqlite3_stmt* ppstmt;
					rc = sqlite3_prepare_v2(d_con_->db_, stmts[siz].stmt.c_str(), (sint)stmts[siz].stmt.length(), &ppstmt, &tail);

					if (rc)
					{
						rc = Output(GetError().c_str(), 1, 2, -1);
					}
					else
					{
						bool done = false;

						while (!done)
						{
							rc = sqlite3_step(ppstmt);

							switch (rc)
							{
							case SQLITE_OK:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_OK", 2);
								}
								done = true;
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_DONE", 2);
								}
								done = true;
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									rc = Output("SQLITE_ROW", 2);
								}

								rc = FindColumn("DATA", ppstmt);

								if (rc > -1)
								{
									uint ui = sqlite3_column_bytes(ppstmt, rc);

									if (ui && ui < BOT_STRLEN_MAX)
									{
										u_char* nuc = (u_char*)malloc(ui + 1);

										if (nuc)
										{
											u_char echar = (u_char)'\0';
											memcpy((void*)nuc, reinterpret_cast <const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
											memcpy((void*)&nuc[ui], (void*)&echar, 1);
											const size_t ssiz = bot_ustrlen(nuc);

											for (size_t nsiz = 0; nsiz < codes_->size(); nsiz++)
											{
												if (codes_->at(nsiz).cons.size() == ssiz)
												{
													size_t usiz = 0;

													while (usiz < ssiz)
													{
														if (memcmp(&nuc[usiz], &codes_->at(nsiz).cons[usiz].sym, 1))
														{
															usiz = ssiz;
														}
														usiz++;
													}
													if (usiz == ssiz)
													{
														rc = FindColumn("ID", ppstmt);

														if (rc > -1)
														{
															codes_->at(nsiz).id = sqlite3_column_int(ppstmt, rc);

															for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
															{
																if (codes_->at(xsiz).cons.size() == ssiz)
																{
																	usiz = 0;
																	while (usiz < ssiz)
																	{
																		if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																		{
																			usiz = ssiz;
																		}
																		usiz++;
																	}
																	if (usiz == ssiz)
																	{
																		codes_->at(xsiz).id = sqlite3_column_int(ppstmt, rc);
																	}
																}
															}
														}

														rc = FindColumn("USAGES", ppstmt);

														if (rc > -1)
														{
															ui = sqlite3_column_bytes(ppstmt, rc);

															if (ui && ui < BOT_STRLEN_MAX)
															{
																u_char* nuchar = (u_char*)malloc(ui + 1);

																if (nuchar)
																{
																	memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
																	memcpy((void*)&nuchar[ui], (void*)&echar, 1);

																	for (size_t fi = 0; fi < ui; fi++)
																	{
																		sint xi = vtool.AddValToVec(&codes_->at(nsiz).usages, (uint)nuchar[fi], false, false);

																		for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																		{
																			if (codes_->at(xsiz).cons.size() == ssiz)
																			{
																				usiz = 0;

																				while (usiz < ssiz)
																				{
																					if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																					{
																						usiz = ssiz;
																					}
																					usiz++;
																				}
																				if (usiz == ssiz)
																				{
																					xi = vtool.AddValToVec(&codes_->at(xsiz).usages, (uint)nuchar[fi], false, false);
																				}
																			}
																		}
																	}
																}
																free(nuchar);
															}
														}

														rc = FindColumn("USED", ppstmt);

														if (rc > -1)
														{
															ui = sqlite3_column_bytes(ppstmt, rc);

															if (ui && ui < BOT_STRLEN_MAX)
															{
																u_char* nuchar = (u_char*)malloc(ui + 1);

																if (nuchar)
																{
																	memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
																	memcpy((void*)&nuchar[ui], (void*)&echar, 1);

																	for (size_t fi = 0; fi < ui; fi++)
																	{
																		sint xi = vtool.AddValToVec(&codes_->at(nsiz).used, (uint)nuchar[fi], false, false);

																		for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																		{
																			if (codes_->at(xsiz).cons.size() == ssiz)
																			{
																				usiz = 0;

																				while (usiz < ssiz)
																				{
																					if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																					{
																						usiz = ssiz;
																					}
																					usiz++;
																				}
																				if (usiz == ssiz)
																				{
																					xi = vtool.AddValToVec(&codes_->at(xsiz).used, (uint)nuchar[fi], false, false);
																				}
																			}
																		}
																	}
																}
																free(nuchar);
															}
														}

														rc = FindColumn("HISTORY_FOLLOWING", ppstmt);

														if (rc > -1)
														{
															ui = sqlite3_column_bytes(ppstmt, rc);

															if (ui && ui < BOT_STRLEN_MAX)
															{
																u_char* nuchar = (u_char*)malloc(ui + 1);

																if (nuchar)
																{
																	memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
																	memcpy((void*)&nuchar[ui], (void*)&echar, 1);
																	std::vector<HIST_FV> nvec;
																	HIST_FV hf;
																	u_char lsep = (u_char)' ';
																	u_char sep = (u_char)',';

																	for (uint csiz = 0; (csiz + 1) < ui; csiz++)
																	{
																		if (!memcmp(&nuchar[csiz], &sep, ui) && !nvec.empty())
																		{
																			hf.ct = (uint)nuchar[csiz - 1];
																			nvec.push_back(hf);
																			hf.cons.clear();
																			hf.ct = 0;
																			csiz++;
																		}
																		else if (memcmp(&nuchar[csiz], &lsep, 1) && !nvec.empty())
																		{
																			codes_->at(nsiz).history_following.push_back(nvec);

																			for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																			{
																				if (codes_->at(xsiz).cons.size() == ssiz)
																				{
																					usiz = 0;

																					while (usiz < ssiz)
																					{
																						if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																						{
																							usiz = ssiz;
																						}
																						usiz++;
																					}
																					if (usiz == ssiz)
																					{
																						codes_->at(xsiz).history_following.push_back(nvec);
																					}
																				}
																			}
																			csiz++;
																			nvec.clear();
																		}
																		else
																		{
																			MICSYM nsym(&nuchar[csiz]);
																			hf.cons.push_back(nsym);
																		}
																	}
																	if (!nvec.empty())
																	{
																		codes_->at(nsiz).history_following.push_back(nvec);

																		for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																		{
																			if (codes_->at(xsiz).cons.size() == ssiz)
																			{
																				usiz = 0;

																				while (usiz < ssiz)
																				{
																					if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																					{
																						usiz = ssiz;
																					}
																					usiz++;
																				}
																				if (usiz == ssiz)
																				{
																					codes_->at(xsiz).history_following.push_back(nvec);
																				}
																			}
																		}
																	}
																}
																free(nuchar);
															}
														}

														rc = FindColumn("HISTORY_PRECEEDING", ppstmt);

														if (rc > -1)
														{
															ui = sqlite3_column_bytes(ppstmt, rc);

															if (ui && ui < BOT_STRLEN_MAX)
															{
																u_char* nuchar = (u_char*)malloc(ui + 1);

																if (nuchar)
																{
																	memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
																	memcpy((void*)&nuchar[ui], (void*)&echar, 1);
																	std::vector<HIST_PV> nvec;
																	HIST_PV hf;
																	u_char lsep = (u_char)' ';
																	u_char sep = (u_char)',';

																	for (uint csiz = 0; (csiz + 1) < ui; csiz++)
																	{
																		if (!memcmp(&nuchar[csiz], &sep, ui) && !nvec.empty())
																		{
																			hf.ct = (uint)nuchar[csiz - 1];
																			nvec.push_back(hf);
																			hf.cons.clear();
																			hf.ct = 0;
																			csiz++;
																		}
																		else if (memcmp(&nuchar[csiz], &lsep, 1) && !nvec.empty())
																		{
																			codes_->at(nsiz).history_preceeding.push_back(nvec);

																			for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																			{
																				if (codes_->at(xsiz).cons.size() == ssiz)
																				{
																					usiz = 0;

																					while (usiz < ssiz)
																					{
																						if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																						{
																							usiz = ssiz;
																						}
																						usiz++;
																					}
																					if (usiz == ssiz)
																					{
																						codes_->at(xsiz).history_preceeding.push_back(nvec);
																					}
																				}
																			}
																			csiz++;
																			nvec.clear();
																		}
																		else
																		{
																			MICSYM nsym(&nuchar[csiz]);
																			hf.cons.push_back(nsym);
																		}
																	}
																	if (!nvec.empty())
																	{
																		codes_->at(nsiz).history_preceeding.push_back(nvec);

																		for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																		{
																			if (codes_->at(xsiz).cons.size() == ssiz)
																			{
																				usiz = 0;

																				while (usiz < ssiz)
																				{
																					if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																					{
																						usiz = ssiz;
																					}
																					usiz++;
																				}
																				if (usiz == ssiz)
																				{
																					codes_->at(xsiz).history_preceeding.push_back(nvec);
																				}
																			}
																		}
																	}
																}
																free(nuchar);
															}
														}

														rc = FindColumn("ALTERS", ppstmt);

														if (rc > -1)
														{
															ui = sqlite3_column_bytes(ppstmt, rc);

															if (ui && ui < BOT_STRLEN_MAX)
															{
																u_char* nuchar = (u_char*)malloc(ui + 1);

																if (nuchar)
																{
																	memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
																	memcpy((void*)&nuchar[ui], (void*)&echar, 1);
																	std::vector<u_char> nvec;
																	u_char sep = (u_char)',';

																	for (uint csiz = 0; csiz < ui; csiz++)
																	{
																		if (!memcmp(&nuchar[csiz], &sep, 1) && !nvec.empty())
																		{
																			sint xi = vtool.AddValToVec(&codes_->at(nsiz).alters, &nvec, true, false);

																			for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																			{
																				if (codes_->at(xsiz).cons.size() == ssiz)
																				{
																					usiz = 0;

																					while (usiz < ssiz)
																					{
																						if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																						{
																							usiz = ssiz;
																						}
																						usiz++;
																					}
																					if (usiz == ssiz)
																					{
																						xi = vtool.AddValToVec(&codes_->at(xsiz).alters, &nvec, true, false);
																					}
																				}
																			}
																			nvec.clear();
																		}
																		else
																		{
																			nvec.push_back(nuchar[csiz]);
																		}
																	}
																	if (!nvec.empty())
																	{
																		sint xi = vtool.AddValToVec(&codes_->at(nsiz).alters, &nvec, true, false);

																		for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																		{
																			if (codes_->at(xsiz).cons.size() == ssiz)
																			{
																				usiz = 0;

																				while (usiz < ssiz)
																				{
																					if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																					{
																						usiz = ssiz;
																					}
																					usiz++;
																				}
																				if (usiz == ssiz)
																				{
																					xi = vtool.AddValToVec(&codes_->at(xsiz).alters, &nvec, true, false);
																				}
																			}
																		}
																	}
																}
																free(nuchar);
															}
														}
														rc = FindColumn("LAST_MODIFIED", ppstmt);

														if (rc > -1)
														{
															codes_->at(nsiz).last_modified = sqlite3_column_int(ppstmt, rc);

															for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
															{
																if (codes_->at(xsiz).cons.size() == ssiz)
																{
																	usiz = 0;

																	while (usiz < ssiz)
																	{
																		if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																		{
																			usiz = ssiz;
																		}
																		usiz++;
																	}
																	if (usiz == ssiz)
																	{
																		codes_->at(xsiz).last_modified = sqlite3_column_int(ppstmt, rc);
																	}
																}
															}
														}

														rc = FindColumn("LAST_MAINTAINED", ppstmt);

														if (rc > -1)
														{
															codes_->at(nsiz).last_maintained = sqlite3_column_int(ppstmt, rc);

															for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
															{
																if (codes_->at(xsiz).cons.size() == ssiz)
																{
																	usiz = 0;

																	while (usiz < ssiz)
																	{
																		if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																		{
																			usiz = ssiz;
																		}
																		usiz++;
																	}
																	if (usiz == ssiz)
																	{
																		codes_->at(xsiz).last_maintained = sqlite3_column_int(ppstmt, rc);
																	}
																}
															}
														}

														rc = FindColumn("LAST_MODIFIED_NS", ppstmt);

														if (rc > -1)
														{
															codes_->at(nsiz).last_modified_ns = sqlite3_column_int(ppstmt, rc);

															for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
															{
																if (codes_->at(xsiz).cons.size() == ssiz)
																{
																	usiz = 0;

																	while (usiz < ssiz)
																	{
																		if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																		{
																			usiz = ssiz;
																		}
																		usiz++;
																	}
																	if (usiz == ssiz)
																	{
																		codes_->at(xsiz).last_modified_ns = sqlite3_column_int(ppstmt, rc);
																	}
																}
															}
														}

														rc = FindColumn("LAST_MAINTAINED_NS", ppstmt);

														if (rc > -1)
														{
															codes_->at(nsiz).last_maintained_ns = sqlite3_column_int(ppstmt, rc);

															for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
															{
																if (codes_->at(xsiz).cons.size() == ssiz)
																{
																	usiz = 0;

																	while (usiz < ssiz)
																	{
																		if (memcmp(&nuc[usiz], &codes_->at(xsiz).cons[usiz].sym, 1))
																		{
																			usiz = ssiz;
																		}
																		usiz++;
																	}
																	if (usiz == ssiz)
																	{
																		codes_->at(xsiz).last_maintained_ns = sqlite3_column_int(ppstmt, rc);
																	}
																}
															}
														}
													}
												}
											}
										}
										free(nuc);
									}
								}
								break;
							}
							case SQLITE_BUSY:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									sint xp = Output("SQLITE_BUSY", 2);
								}
								done = true;
								break;
							}
							default:
							{
								if (debug_lvl >= 1 && debug_m)
								{
									sint xp = Output(GetError().c_str(), 1, 2, -1);
								}
								done = true;
								break;
							}
							}
						}

						rc = sqlite3_finalize(ppstmt);

						if (rc)
						{
							sint xp = Output(GetError().c_str(), 1, 2, -1);
						}
					}
					d_con_->o_com = false;
					rc = UpdMTXPrio();
				}
			}
			if (!hdb)
			{
				hdb = CloseDB(&dbs, &fdb);
			}

			if (!maint)
			{
				for (size_t siz = 0; siz < codes_->size(); siz++)
				{
					if (codes_->at(siz).last_maintained < codes_->at(siz).last_modified || ((codes_->at(siz).last_maintained == codes_->at(siz).last_modified) && (codes_->at(siz).last_maintained_ns < codes_->at(siz).last_modified_ns)))
					{
						rc = codes_->at(siz).Proc();
					}
				}
			}

			if (debug_lvl >= 1 && debug_m)
			{
				rc = Output("GetCode() done", 2);
			}
			return 0;
		}
		return -1;
	}
	sint AddCode(MACSYM *code_ = 0) { if (!code_) { return-1; } std::vector<MACSYM> vec; vec.push_back(*code_); return AddCode(&vec); }
	sint AddCode(std::vector<MACSYM > *codes_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::AddCode(std::vector <MACSYM> *codes_(%i))", (sint)codes_->size());
			op = Output(outp.carr, 2);
		}

		if (!codes_)
		{
			return -1;
		}
		if (codes_->empty())
		{
			return -1;
		}

		std::vector<size_t> eles;

		for (size_t x = 0; x < codes_->size(); x++)
		{
			bool aud = false;

			if (codes_->at(x).id > -2)
			{
				sint uc = codes_->at(x).Proc();
				uc = vtool.ValInVec(&codes_->at(x).usages, codes_->at(x).used_as);

				if (uc < 0)
				{
					if (!codes_->at(x).ud_usages)
					{
						codes_->at(x).ud_usages = true;
					}
					uc = vtool.AddValToVec(&codes_->at(x).usages, codes_->at(x).used_as, false, false);
				}

				if (uc > -1)
				{
					if (!codes_->at(x).ud_used)
					{
						codes_->at(x).ud_used = true;
					}
					while (codes_->at(x).used.size() < codes_->at(x).usages.size())
					{
						codes_->at(x).used.push_back(1);
					}
				}
				for (size_t xc = x + 1; xc < codes_->size(); xc++)
				{
					sint retc = vtool.vsymcmp(&codes_->at(x).cons, &codes_->at(xc).cons);

					if (!retc)
					{
						if (codes_->at(x).id == codes_->at(xc).id || codes_->at(xc).id < 0)
						{
							if (!codes_->at(xc).usages.empty())
							{
								for (size_t cf = 0; cf < codes_->at(xc).usages.size() && cf < codes_->at(xc).used.size() && cf < codes_->at(xc).history_preceeding.size() && cf < codes_->at(xc).history_following.size(); cf++)
								{
									sint xf = codes_->at(x).AddUse(codes_->at(xc).usages[cf], codes_->at(xc).used[cf], &codes_->at(xc).history_preceeding[cf], &codes_->at(xc).history_following[cf]);

									if (xf > -1)
									{
										if (!codes_->at(x).ud_usages)
										{
											codes_->at(x).ud_usages = true;
											aud = true;
										}
										if (!codes_->at(x).ud_used)
										{
											codes_->at(x).ud_used = true;
											aud = true;
										}
										if (!codes_->at(x).ud_history_preceeding)
										{
											codes_->at(x).ud_history_preceeding = true;
											aud = true;
										}
										if (!codes_->at(x).ud_history_following)
										{
											codes_->at(x).ud_history_following = true;
											aud = true;
										}
									}
								}
							}
							else
							{
								if (codes_->at(xc).ud_usages)
								{
									if (!codes_->at(x).ud_usages)
									{
										codes_->at(x).ud_usages = true;
										aud = true;
									}
									codes_->at(x).usages.clear();
									codes_->at(x).used.clear();
									codes_->at(x).history_following.clear();
									codes_->at(x).history_preceeding.clear();
								}
							}

							if (codes_->at(xc).used.empty())
							{
								if (codes_->at(xc).ud_used)
								{
									if (!codes_->at(x).ud_used)
									{
										codes_->at(x).ud_used = true;
										aud = true;
									}
									codes_->at(x).used.clear();
								}
							}

							if (!codes_->at(xc).pair_sym.empty())
							{
								if (codes_->at(xc).ud_pair_sym)
								{
									retc = vtool.vsymcmp(&codes_->at(x).pair_sym, &codes_->at(xc).pair_sym);

									if (retc)
									{
										codes_->at(x).pair_sym.clear();

										for (retc = 0; codes_->at(x).pair_sym.size() < codes_->at(xc).pair_sym.size(); retc++)
										{
											codes_->at(x).pair_sym.push_back(codes_->at(xc).pair_sym[retc]);
										}
									}
								}
							}
							else
							{
								if (codes_->at(xc).ud_pair_sym)
								{
									if (!codes_->at(x).ud_pair_sym)
									{
										codes_->at(x).ud_pair_sym = true;
										aud = true;
									}
									codes_->at(x).pair_sym.clear();
								}
							}

							if (!codes_->at(xc).alters.empty())
							{
								for (size_t cf = 0; cf < codes_->at(xc).alters.size(); cf++)
								{
									retc = vtool.ValInVec(&codes_->at(x).alters, &codes_->at(xc).alters[cf]);

									if (retc < 0)
									{
										if (!codes_->at(x).ud_alters)
										{
											codes_->at(x).ud_alters = true;
											aud = true;
										}
										retc = vtool.AddValToVec(&codes_->at(x).alters, &codes_->at(xc).alters[cf], true, true);
									}
								}
							}
							else
							{
								if (codes_->at(xc).ud_alters)
								{
									if (!codes_->at(x).ud_alters)
									{
										codes_->at(x).ud_alters = true;
										aud = true;
									}
									codes_->at(x).alters.clear();
								}
							}

							if (codes_->at(xc).history_following.empty())
							{
								if (codes_->at(xc).ud_history_following)
								{
									if (!codes_->at(x).ud_history_following)
									{
										codes_->at(x).ud_history_following = true;
										aud = true;
									}
									codes_->at(x).history_following.clear();
								}
							}

							if (codes_->at(xc).history_preceeding.empty())
							{
								if (codes_->at(xc).ud_history_preceeding)
								{
									if (!codes_->at(x).ud_history_preceeding)
									{
										codes_->at(x).ud_history_preceeding = true;
										aud = true;
									}
									codes_->at(x).history_preceeding.clear();
								}
							}

							if (codes_->at(xc).alters.empty())
							{
								if (codes_->at(xc).ud_alters)
								{
									if (!codes_->at(x).ud_alters)
									{
										codes_->at(x).ud_alters = true;
										aud = true;
									}
									codes_->at(x).alters.clear();
								}
							}

							if (codes_->at(xc).last_modified > codes_->at(x).last_modified)
							{
								if (!codes_->at(x).ud_last_modified)
								{
									codes_->at(x).ud_last_modified = true;
								}
								codes_->at(x).last_modified = codes_->at(xc).last_modified;
							}

							if (codes_->at(xc).last_modified_ns > codes_->at(x).last_modified_ns)
							{
								if (!codes_->at(x).ud_last_modified_ns)
								{
									codes_->at(x).ud_last_modified_ns = true;
								}
								codes_->at(x).last_modified_ns = codes_->at(xc).last_modified_ns;
							}

							if (codes_->at(xc).last_maintained > codes_->at(x).last_maintained)
							{
								if (!codes_->at(x).ud_last_maintained)
								{
									codes_->at(x).ud_last_maintained = true;
								}
								codes_->at(x).last_maintained = codes_->at(xc).last_maintained;
							}

							if (codes_->at(xc).last_maintained_ns > codes_->at(x).last_maintained_ns)
							{
								if (!codes_->at(x).ud_last_maintained_ns)
								{
									codes_->at(x).ud_last_maintained_ns = true;
								}
								codes_->at(x).last_maintained_ns = codes_->at(xc).last_maintained_ns;
							}

							codes_->at(xc).id = -2;
						}
					}
				}
				sint rc = codes_->at(x).Proc();
				rc = vtool.AddValToVec(&eles, x, true, false);
			}
		}

		BOT_DB dbs("code", 2);
		sint rc = GetInVec((void*)&dbs, MTX_DBL, false, false);

		if (rc > -1)
		{
			rc = GetCode(codes_, "", false);
		}

		for (size_t x = 0; x < eles.size(); x++)
		{
			std::vector<MICSYM> nv;
			for (size_t nx = 0; nx < codes_->at(eles[x]).cons.size(); nx++)
			{
				nv.push_back(codes_->at(eles[x]).cons[nx]);
			}
			sint xc = AddSymbols(&nv);
		}
		std::vector<BOT_STMT> tvec;

		for (size_t x = 0; x < eles.size(); x++)
		{
			std::string con_str;

			if (!codes_->at(eles[x]).cons.empty())
			{
				for (size_t a = 0; a < codes_->at(eles[x]).cons.size(); a++)
				{
					_char ci[(sizeof(codes_->at(eles[x]).cons[a].sym) * 2) + 1]{ 0 };
					sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).cons[a].sym);
					con_str.append(ci);
				}
			}

			for (size_t uc = 0; uc < codes_->at(eles[x]).usages.size(); uc++)
			{
				BOT_STMT t;

				if (dbs.lid < 0)
				{
					sint h = -1;
					sint p = LockGMutex(MTX_FTYPE, &h);

					if (p > -1)
					{
						t.Renew(codes_->at(eles[x]).ud_last_maintained, 1, "code", bot_symbol_types[codes_->at(eles[x]).usages[uc]], 1);

						if (!h)
						{
							h = UnlockGMutex(MTX_FTYPE);
						}
					}
				}
				else
				{
					t.Renew(codes_->at(eles[x]).ud_last_maintained, 1, dbs.name.c_str(), dbs.tables[codes_->at(eles[x]).usages[uc]].c_str(), 1);
				}

				if (codes_->at(eles[x]).id < 0)
				{
					t.it_type = 2;
					t.cspec = 2;

					if (!codes_->at(eles[x]).cons.empty())
					{
						if (!con_str.empty())
						{
							std::string fstr;
							fstr.append("X'");
							fstr.append(con_str.c_str());
							fstr.push_back('\'');
							sint xc = t.AddCol("DATA", fstr.c_str());
						}
					}

					if (!codes_->at(eles[x]).usages.empty())
					{
						std::string str;
						for (size_t xc = 0; xc < codes_->at(eles[x]).usages.size(); xc++)
						{
							_char ci[(sizeof(codes_->at(eles[x]).usages[xc]) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (u_char)codes_->at(eles[x]).usages[xc]);
							str.append(ci);
						}
						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "USAGES", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);

							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}
					if (!codes_->at(eles[x]).used.empty())
					{
						std::string str;
						for (size_t xc = 0; xc < codes_->at(eles[x]).used.size(); xc++)
						{
							_char ci[(sizeof(codes_->at(eles[x]).used[xc]) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (u_char)codes_->at(eles[x]).used[xc]);
							str.append(ci);
						}
						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "USED", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);

							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}
					if (!codes_->at(eles[x]).history_following.empty())
					{
						std::string str;
						u_char lsep = (u_char)' ';
						u_char sep = (u_char)',';

						for (size_t a = 0; a < codes_->at(eles[x]).history_following.size(); a++)
						{
							for (size_t b = 0; b < codes_->at(eles[x]).history_following[a].size(); b++)
							{
								for (size_t c = 0; c < codes_->at(eles[x]).history_following[a][b].cons.size(); c++)
								{
									_char ci[(sizeof(codes_->at(eles[x]).history_following[a][b].cons[c].sym) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_following[a][b].cons[c].sym);
									str.append(ci);
								}
								_char xi[(sizeof(codes_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)codes_->at(eles[x]).history_following[a][b].ct);
								str.append(xi);
								_char ci[(sizeof(sep) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
								str.append(ci);
							}
							_char xi[(sizeof(lsep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
							str.append(xi);
						}

						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);

							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}
					if (!codes_->at(eles[x]).history_preceeding.empty())
					{
						std::string str;
						u_char lsep = (u_char)' ';
						u_char sep = (u_char)',';

						for (size_t a = 0; a < codes_->at(eles[x]).history_preceeding.size(); a++)
						{
							for (size_t b = 0; b < codes_->at(eles[x]).history_preceeding[a].size(); b++)
							{
								for (size_t c = 0; c < codes_->at(eles[x]).history_preceeding[a][b].cons.size(); c++)
								{
									_char ci[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym);
									str.append(ci);
								}
								_char xi[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].ct) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)codes_->at(eles[x]).history_preceeding[a][b].ct);
								str.append(xi);
								_char ci[(sizeof(sep) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
								str.append(ci);
							}
							_char xi[(sizeof(lsep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
							str.append(xi);
						}

						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);

							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (!codes_->at(eles[x]).alters.empty())
					{
						u_char sep = (u_char)',';
						std::string str;

						for (size_t xc = 0; xc < codes_->at(eles[x]).alters.size(); xc++)
						{
							for (size_t nsiz = 0; nsiz < codes_->at(eles[x]).alters[xc].size(); nsiz++)
							{
								_char ci[(sizeof(codes_->at(eles[x]).alters[xc]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).alters[xc]);
								str.append(ci);
							}
							_char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}
						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "ALTERS", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);
							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (!t.cont.empty())
					{
						sint xc = vtool.AddValToVec(&tvec, &t, false, true);
					}
				}
				else
				{
					t.cspec = 0;
					t.act = 0;

					if (codes_->at(eles[x]).ud_id)
					{
						sint xc = t.AddCol("ID", stool.ITOA(codes_->at(eles[x]).id).c_str());
					}

					if (codes_->at(eles[x]).ud_cons)
					{
						if (!con_str.empty())
						{
							std::string fstr;
							fstr.append("X'");
							fstr.append(con_str.c_str());
							fstr.push_back('\'');
							sint xc = t.AddCol("DATA", fstr.c_str());
						}
					}

					if (codes_->at(eles[x]).ud_usages)
					{
						std::string str;

						for (size_t a = 0; a < codes_->at(eles[x]).usages.size(); a++)
						{
							_char ci[(sizeof(codes_->at(eles[x]).usages[a]) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (u_char)codes_->at(eles[x]).usages[a]);
							str.append(ci);
						}
						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "USAGES", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);
							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (codes_->at(eles[x]).ud_used)
					{
						std::string str;

						for (size_t a = 0; a < codes_->at(eles[x]).used.size(); a++)
						{
							_char ci[(sizeof(codes_->at(eles[x]).used[a]) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (u_char)codes_->at(eles[x]).used[a]);
							str.append(ci);
						}
						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "USED", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);
							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (codes_->at(eles[x]).ud_history_following)
					{
						std::string str;
						u_char lsep = (u_char)' ';
						u_char sep = (u_char)',';

						for (size_t a = 0; a < codes_->at(eles[x]).history_following.size(); a++)
						{
							for (size_t b = 0; b < codes_->at(eles[x]).history_following[a].size(); b++)
							{
								for (size_t c = 0; c < codes_->at(eles[x]).history_following[a][b].cons.size(); c++)
								{
									_char ci[(sizeof(codes_->at(eles[x]).history_following[a][b].cons[c].sym) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_following[a][b].cons[c].sym);
									str.append(ci);
								}
								_char xi[(sizeof(codes_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{  };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)codes_->at(eles[x]).history_following[a][b].ct);
								str.append(xi);
								_char ci[(sizeof(sep) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
								str.append(ci);
							}
							_char xi[(sizeof(lsep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
							str.append(xi);
						}

						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);
							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (codes_->at(eles[x]).ud_history_preceeding)
					{
						std::string str;
						u_char lsep = (u_char)' ';
						u_char sep = (u_char)',';

						for (size_t a = 0; a < codes_->at(eles[x]).history_preceeding.size(); a++)
						{
							for (size_t b = 0; b < codes_->at(eles[x]).history_preceeding[a].size(); b++)
							{
								for (size_t c = 0; c < codes_->at(eles[x]).history_preceeding[a][b].cons.size(); c++)
								{
									_char ci[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym);
									str.append(ci);
								}
								_char xi[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].ct) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (u_char)codes_->at(eles[x]).history_preceeding[a][b].ct);
								str.append(xi);
								_char ci[(sizeof(sep) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
								str.append(ci);
							}
							_char xi[(sizeof(lsep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
							str.append(xi);
						}

						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);
							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (codes_->at(eles[x]).ud_alters)
					{
						std::string str;
						u_char sep = (u_char)',';

						for (size_t a = 0; a < codes_->at(eles[x]).alters.size(); a++)
						{
							for (size_t b = 0; b < codes_->at(eles[x]).alters[a].size(); b++)
							{
								_char ci[(sizeof(codes_->at(eles[x]).alters[a]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).alters[a]);
								str.append(ci);
							}
							_char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}
						if (!str.empty())
						{
							sint xc = vtool.AddValToVec(&t.cols, "ALTERS", false, false);
							xc = vtool.AddValToVec(&t.vals, "X'", false, false);
							if (xc > -1)
							{
								t.vals[xc].append(str.c_str());
								t.vals[xc].push_back('\'');
							}
						}
					}

					if (codes_->at(eles[x]).id > 0)
					{
						sint xp = t.AddCond(0, "ID", sql_comp_keywords[5], stool.ITOA(codes_->at(eles[x]).id).c_str());
					}
					
					std::string xstr;
					xstr.append("X'");
					xstr.append(con_str.c_str());
					xstr.append("'");
					sint xc = t.AddCond(0, "DATA", sql_comp_keywords[5], xstr.c_str());
					xc = vtool.AddValToVec(&tvec, &t, true, true);
				}
			}
		}
		if (!tvec.empty())
		{
			if (rc > -1)
			{
				return Commit(&tvec);
			}
			else
			{
				sint h = -1;
				sint l = LockGMutex(MTX_STRT, &h);

				if (l > -1)
				{
					for (uint x = 0; x < tvec.size(); x++)
					{
						rc = vtool.AddValToVec(&bot_strt.code_pend, &tvec[x], true, true);
					}
					if (!h)
					{
						h = UnlockGMutex(MTX_STRT);
					}
				}
			}
		}
		return -1;
	}
	
	sint GetCommand(BOTCOMMAND *Command_ = 0, std::vector<std::string> *conds_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::GetCommand(BOTCOMMAND* Command_(%i), std::vector<std::string>* conds_(%i))", (sint)Command_, (sint)conds_);
			op = Output(outp.carr, 2);
		}

		if (!Command_)
		{
			return -1;
		}

		BOT_STMT t(false, 0, "litebot", "COMMANDS", 1);
		t.cspec = 0;

		if (conds_)
		{
			if (!conds_->empty())
			{
				for (size_t siz = 0; siz < conds_->size(); siz++)
				{
					sint xc = t.AddCond(&conds_->at(siz));
				}
			}
		}
		else
		{
			if (!Command_->cmd.empty())
			{
				sint rc = t.AddCond(0, "COMMAND", sql_comp_keywords[5], LEncStrI(Uppercase(CleanPunctuation(Command_->cmd.c_str()).c_str()).c_str(), -1).c_str());
			}

			if (Command_->cmd_id > 0)
			{
				sint rc = t.AddCond(0, "CMD_ID", sql_comp_keywords[5], stool.ITOA(Command_->cmd_id).c_str());
			}

			if (Command_->id > 0)
			{
				sint rc = t.AddCond(0, "ID", sql_comp_keywords[5], stool.ITOA(Command_->id).c_str());
			}
		}
		
		sint rc = BQS(&t);

		if (!rc)
		{
			BOT_DB_M dbs("litebot", 0);
			sint fdb = -1;
			sint hdb = -1;
			sint odb = OpenDB(&dbs, 1, &hdb, &fdb);

			if (odb > -1)
			{
				sint ret = -1;
				d_con_->o_com = true;
				rc = UpdMTXPrio();
				c_char* tail;
				sqlite3_stmt* ppstmt;
				rc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

				if (!rc)
				{
					bool done = false;

					while (!done)
					{
						rc = sqlite3_step(ppstmt);

						switch (rc)
						{
						case SQLITE_OK:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								rc = Output("SQLITE_OK", 2);
							}
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								rc = Output("SQLITE_DONE", 2);
							}
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								rc = Output("SQLITE_ROW", 2);
							}

							ret = 0;
							Command_->Clear();
							rc = FindColumn("PRIV", ppstmt);

							if (rc > -1)
							{
								rc = sqlite3_column_int(ppstmt, rc);
								sint xc = GetClientPriv();

								if (xc < rc)
								{
									if (debug_lvl >= 1 && debug_m)
									{
										c_char* output("not enough priv");
										xc = Output(output, 2);
									}
								}
								else
								{
									rc = FindColumn("ID", ppstmt);

									if (rc > -1)
									{
										Command_->id = sqlite3_column_int(ppstmt, rc);
									}

									rc = FindColumn("CMD_ID", ppstmt);

									if (rc > -1)
									{
										Command_->cmd_id = sqlite3_column_int(ppstmt, rc);
									}

									rc = FindColumn("COMMAND", ppstmt);

									if (rc > -1)
									{
										if (sqlite3_column_text(ppstmt, rc) != NULL)
										{
											Command_->cmd.append(reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, rc)));
										}
									}
								}
							}
							break;
						}
						default:
						{
							done = true;
							rc = Output(GetError().c_str(), 1, 2, -1);
							break;
						}
						}
					}

					rc = sqlite3_finalize(ppstmt);

					if (rc)
					{
						rc = Output(GetError().c_str(), 1, 2, -1);
					}

				}
				else
				{
					rc = Output(GetError().c_str(), 1, 2, -1);
				}

				d_con_->o_com = false;
				rc = UpdMTXPrio();

				if (!hdb)
				{
					hdb = CloseDB(&dbs, &fdb);
				}
				return ret;
			}
		}
		return -1;
	}
	sint GetLogin(c_char* str_ = "")
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 ncar;
			sint xc = bot_sprintf(ncar.carr, ncar.siz, "::GetLogin(c_char* str_(%i))", (sint)str_);
			xc = Output(ncar.carr, 2);
		}

		if (!str_)
		{
			return -1;
		}

		if (debug_lvl >= 1 && debug_m)
		{
			std::string output;
			output.append("Finding login name:");
			output.append(str_);
			sint xc = Output(output.c_str(), 2);
		}

		BOT_STMT t(false, 0, "litebot", "ACCOUNTS", 1);
		t.AddCond(0, "LOGIN_NAME", sql_comp_keywords[5], LEncStrI(str_, -1).c_str());
		t.cspec = 0;
		t.rlim = 1;
		sint xc = BQS(&t);

		if (!xc)
		{
			BOT_DB_M dbs("litebot", 0);
			sint fdb = -1;
			sint hdb = -1;
			sint odb = OpenDB(&dbs, 1, &hdb, &fdb);

			if (odb > -1)
			{
				d_con_->o_com = true;
				xc = UpdMTXPrio();
				c_char* tail;
				sqlite3_stmt* ppstmt;
				xc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

				if (!xc)
				{
					bool done = false;

					while (!done)
					{
						xc = sqlite3_step(ppstmt);

						switch (xc)
						{
						case SQLITE_OK:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								sint op = Output("SQLITE_OK", 2);
							}
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								sint op = Output("SQLITE_DONE", 2);
							}
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								sint op = Output("SQLITE_ROW", 2);
							}

							if (sqlite3_column_text(ppstmt, 2) != NULL)
							{
								if (!strcmp(str_, reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, 2))))
								{
									str_ = "";
									std::string str;
									xc = SetClientLoggedIn(true);
									xc = FindColumn("ID", ppstmt);

									if (xc > -1)
									{
										sint rc = SetClientID(sqlite3_column_int(ppstmt, xc));
									}

									xc = FindColumn("RAW_NAME", ppstmt);

									if (xc > -1)
									{
										if (sqlite3_column_text(ppstmt, xc) != NULL)
										{
											str.append(reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, xc)));
											sint rc = SetClientName(&str);
											str.clear();
										}
									}

									//Client.password.append( reinterpret_cast < c_char* > ( sqlite3_column_text( ppstmt, 2 ) ) );
									xc = FindColumn("PRIV", ppstmt);

									if (xc > -1)
									{
										sint rc = SetClientPriv(sqlite3_column_int(ppstmt, xc));
									}

									/*
									if ( sqlite3_column_text( ppstmt, 4 ) != NULL )
									{
									Client_->name.append( reinterpret_cast < c_char* > ( sqlite3_column_text( ppstmt, 4 ) ) );
									}
									*/
									xc = FindColumn("LAST_LOGIN", ppstmt);

									if (xc > -1)
									{
										if (sqlite3_column_text(ppstmt, xc) != NULL)
										{
											str.append(reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, xc)));
											sint rc = SetClientLastLogin(&str);
											str.clear();
										}
									}

									xc = FindColumn("TOTAL_LOGINS", ppstmt);

									if (xc > -1)
									{
										sint rc = SetClientTotalLogins(sqlite3_column_int(ppstmt, xc));
									}
								}
								else
								{
									std::string str;
									xc = FindColumn("ID", ppstmt);

									if (xc > -1)
									{
										sint rc = SetClientID(sqlite3_column_int(ppstmt, xc));
									}

									xc = FindColumn("LAST_FAILED_LOGIN", ppstmt);

									if (xc > -1)
									{
										if (sqlite3_column_text(ppstmt, xc) != NULL)
										{
											str.append(reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, xc)));
											sint rc = SetClientLastFailedLogin(&str);
											str.clear();
										}
									}

									xc = FindColumn("FAILED_LOGINS", ppstmt);

									if (xc > -1)
									{
										sint rc = SetClientFailedLogins(sqlite3_column_int(ppstmt, xc));
									}
								}
							}
							break;
						}
						case SQLITE_BUSY:
						{
							if (debug_lvl >= 1 && debug_m)
							{
								sint op = Output("SQLITE_BUSY", 2);
							}
							break;
						}
						default:
						{
							sint op = Output(GetError().c_str(), 1, 2, -1);
							break;
						}
						}
					}

					xc = sqlite3_finalize(ppstmt);

					if (xc)
					{
						sint op = Output(GetError().c_str(), 1, 2, -1);
					}
				}
				else
				{
					sint op = Output(GetError().c_str(), 1, 2, -1);
				}

				d_con_->o_com = false;
				xc = UpdMTXPrio();

				if (!hdb)
				{
					hdb = CloseDB(&dbs, &fdb);
				}
				return xc;
			}
		}
		return -1;
	}
	sint UpdateAccount(BOT_CLIENT *Client_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 ncar;
			sint xc = bot_sprintf(ncar.carr, ncar.siz, "::UpdateAccount(BOT_CLIENT* Client_(%i))", (sint)Client_);
			xc = Output(ncar.carr, 2);
		}
		if (!Client_)
		{
			return 0;
		}
		std::vector<BOT_STMT> tvec;
		BOT_STMT t(false, 1, "litebot", "ACCOUNTS", 1);
		t.cspec = 0;
		t.act = 0;
		sint xc = t.AddCond(0, "LOGIN_NAME", sql_comp_keywords[5], LEncStrI(Client_->login_name.c_str(), -1).c_str());
		xc = t.AddCond(0, "ID", sql_comp_keywords[5], stool.ITOA(Client_->lid).c_str());

		if (Client_->loggedin)
		{
			if (Client_->changename)
			{
				std::string str;
				str.append(Uppercase(Client_->login_name.c_str()));
				xc = t.AddCol("LOGIN_NAME", LEncStrI(str.c_str(), -1).c_str());
			}

			if (Client_->updatepriv)
			{
				xc = t.AddCol("PRIV", stool.ITOA(Client_->priv).c_str());
			}

			if (Client_->updatelogin)
			{
				xc = t.AddCol("LAST_LOGIN", LEncStrI(Client_->logindate.c_str(), -1).c_str());
				xc = t.AddCol("TOTAL_LOGINS", stool.ITOA(Client_->totallogins).c_str());
				xc = t.AddCol("FAILED_LOGINS", stool.ITOA(0).c_str());
			}
		}
		else
		{
			if (Client_->updatelogin)
			{
				xc = t.AddCol("LAST_FAILED_LOGIN", LEncStrI(Client_->last_failed_login.c_str(), -1).c_str());
				xc = t.AddCol("FAILED_LOGINS", stool.ITOA(Client_->failed_logins + 1).c_str());
			}
		}
		tvec.push_back(t);
		xc = Commit(&tvec);
		return 0;
	}
	sint GetLastAccess(BOT_DB_M *dbs_ = 0, sint *last_modi_ = 0, sint *last_modi_ns_ = 0, sint *last_maint_ = 0, sint *last_maint_ns_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_512 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::GetLastAccess(BOT_DB_M* dbs_(%i), sint *last_modi_(%i), sint *last_modi_ns_(%i), sint *last_maint_(%i), sint *last_maint_ns_(%i))(", (sint)dbs_, (sint)last_modi_, (sint)last_modi_ns_, (sint)last_maint_, (sint)last_maint_ns_);
			op = Output(outp.carr, 2);
		}

		if (!dbs_ || !last_modi_ || !last_modi_ns_ || !last_maint_ || !last_maint_ns_)
		{
			return -1;
		}

		if (dbs_->type > -1)
		{
			BOT_STMT t(false, 0, dbs_->name.c_str(), "LAST_ACCESS", 1);
			sint fdb = -1;
			sint hdb = -1;
			sint odb = OpenDB(dbs_, 1, &hdb, &fdb);

			if (odb > -1)
			{
				sint xc = BQS(&t);

				if (!xc)
				{
					d_con_->o_com = true;
					xc = UpdMTXPrio();
					c_char* tail;
					sqlite3_stmt* ppstmt;
					xc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

					if (!xc)
					{
						bool done = false;

						while (!done)
						{
							xc = sqlite3_step(ppstmt);

							switch (xc)
							{
							case SQLITE_OK:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_OK", 2);
								}
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_DONE", 2);
								}
								done = true;
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_ROW", 2);
								}

								if (last_maint_)
								{
									xc = FindColumn("LAST_MAINTAINED", ppstmt);

									if (xc > -1)
									{
										sint rc = sqlite3_column_int(ppstmt, xc);

										if (rc > *last_maint_)
										{
											*last_maint_ = rc;
										}
									}
								}
								if (last_modi_)
								{
									xc = FindColumn("LAST_MODIFIED", ppstmt);

									if (xc > -1)
									{
										sint rc = sqlite3_column_int(ppstmt, xc);

										if (rc > *last_modi_)
										{
											*last_modi_ = rc;
										}
									}
								}
								if (last_maint_ns_)
								{
									xc = FindColumn("LAST_MAINTAINED_NS", ppstmt);

									if (xc > -1)
									{
										sint rc = sqlite3_column_int(ppstmt, xc);

										if (rc > *last_maint_ns_)
										{
											*last_maint_ns_ = rc;
										}
									}
								}
								if (last_modi_ns_)
								{
									xc = FindColumn("LAST_MODIFIED_NS", ppstmt);

									if (xc > -1)
									{
										sint rc = sqlite3_column_int(ppstmt, xc);

										if (rc > *last_modi_ns_)
										{
											*last_modi_ns_ = rc;
										}
									}
								}
								break;
							}
							case SQLITE_BUSY:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_BUSY", 2);
								}
								done = true;
								break;
							}
							default:
							{
								sint xp = Output(GetError().c_str(), 1, 2, -1);
								done = true;
								break;
							}
							}
						}

						xc = sqlite3_finalize(ppstmt);

						if (xc)
						{
							sint xp = Output(GetError().c_str(), 1, 2, -1);
						}
					}
					else
					{
						sint xp = Output(GetError().c_str(), 1, 2, -1);
					}

					d_con_->o_com = false;
					xc = UpdMTXPrio();

					if (!hdb)
					{
						hdb = CloseDB(dbs_, &fdb);
					}
					return xc;
				}
			}
		}
		return -1;
	}
	sint LastAccessMaintenance(BOT_DB_M *dbs_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_256 outp;
			sint xc = bot_sprintf(outp.carr, outp.siz, "::LastAccessMaintenance(BOT_DB_M *dbs_(%i)", (sint)dbs_);
			xc = Output(outp.carr, 2);
		}

		if (!dbs_)
		{
			return 0;
		}

		if (dbs_->type > -1)
		{
			std::vector<std::string> strs;
			BOT_STMT t(true, 0, dbs_->name.c_str(), "LAST_ACCESS", 1);
			sint fdb = -1;
			sint hdb = -1;
			sint odb = OpenDB(dbs_, 2, &hdb, &fdb);

			if (odb > -1)
			{
				sint xc = BQS(&t);

				if (!xc)
				{
					d_con_->o_com = true;
					xc = UpdMTXPrio();
					c_char* tail;
					sqlite3_stmt* ppstmt;
					xc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

					if (!xc)
					{
						std::vector<BOT_STMT> tvec;
						bool done = false;

						while (!done)
						{
							xc = sqlite3_step(ppstmt);

							switch (xc)
							{
							case SQLITE_OK:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_OK", 2);
								}
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_DONE", 2);
								}

								xc = FindColumn("ID", ppstmt);

								if (xc > -1)
								{
									xc = sqlite3_column_int(ppstmt, xc);

									if (xc > 1)
									{
										BOT_STMT t(true, 4, dbs_->name.c_str(), "LAST_ACCESS", 1);
										std::string nstr;
										nstr.append("ID = ");
										nstr.append(stool.ITOA(xc).c_str());
										sint ac = vtool.AddValToVec(&t.conds, nstr.c_str(), true, true);
										t.cspec = 0;
										tvec.push_back(t);
									}
								}
								done = true;
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_ROW", 2);
								}

								xc = FindColumn("ID", ppstmt);

								if (xc > -1)
								{
									xc = sqlite3_column_int(ppstmt, xc);

									if (xc > 1)
									{
										BOT_STMT t(true, 4, dbs_->name.c_str(), "LAST_ACCESS", 1);
										std::string nstr;
										nstr.append("ID = ");
										nstr.append(stool.ITOA(xc).c_str());
										sint ac = vtool.AddValToVec(&t.conds, nstr.c_str(), true, true);
										t.cspec = 0;
										tvec.push_back(t);
									}
								}
								break;
							}
							case SQLITE_BUSY:
							{
								if (debug_lvl >= 20 && debug_m)
								{
									sint xp = Output("SQLITE_BUSY", 2);
								}
								done = true;
								break;
							}
							default:
							{
								sint xp = Output(GetError().c_str(), 1, 2, -1);
								done = true;
								break;
							}
							}
						}

						if (!tvec.empty())
						{
							xc = Commit(&tvec);
						}

						xc = sqlite3_finalize(ppstmt);

						if (xc)
						{
							sint xp = Output(GetError().c_str(), 1, 2, -1);
						}
					}
					else
					{
						xc = Output(GetError().c_str(), 1, 2, -1);
					}

					d_con_->o_com = false;
					xc = UpdMTXPrio();

					if (!hdb)
					{
						hdb = CloseDB(dbs_, &fdb);
					}
					return 0;
				}
			}
		}
		return -1;
	}
	sint PushToDBList(BOT_DB *dbs_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_64 outp;
			bot_sprintf(outp.carr, outp.siz, "PushToDBList(BOT_DB *dbs_(%i))", (sint)dbs_);
			sint op = Output(outp.carr, 2);
		}

		if (!dbs_)
		{
			return -1;
		}
		if (!strlen(dbs_->name.c_str()))
		{
			return -1;
		}

		if (dbs_->type < 0)
		{
			if (!strcmp(dbs_->name.c_str(), "litebot"))
			{
				dbs_->type = 0;
			}
			else if (!strcmp(dbs_->name.c_str(), "math"))
			{
				dbs_->type = 1;
			}
			else if (!strcmp(dbs_->name.c_str(), "code"))
			{
				dbs_->type = 2;
			}
			else if (strlen(dbs_->name.c_str()) < 3)
			{
				dbs_->type = 3;
			}
			else
			{
				dbs_->type = 4;
			}
		}

		sint ret = -1;
		sint h = -1;
		sint p = LockGMutex(MTX_STRT, &h);

		if (p > -1)
		{
			switch (dbs_->type)
			{
			case 0:
			{
				for (uint t = 0; t < bot_strt.litebot_tablenames.size(); t++)
				{
					ret = vtool.AddValToVec(&dbs_->tables, bot_strt.litebot_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					_char c = ' ';

					if (t < bot_strt.litebot_columns.size())
					{
						std::string str;
						str.append(bot_strt.litebot_columns[t]);
						sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.litebot_columns[(sint)bot_strt.litebot_columns.size() - 1]);
						sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
					}

					if (cols.size() > 1)
					{
						if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
						{
							cols[1].append(" PRIMARY KEY");
						}
						for (uint x = 0; x < cols.size(); )
						{
							dbs_->columns[t][0].push_back(cols[x]);
							x++;

							if (x < cols.size())
							{
								dbs_->columns[t][1].push_back(cols[x]);
								x++;
							}
						}
					}
				}
				break;
			}
			case 1:
			{
				for (uint t = 0; t < bot_strt.math_tablenames.size(); t++)
				{
					ret = vtool.AddValToVec(&dbs_->tables, bot_strt.math_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					_char c = ' ';

					if (t < bot_strt.math_columns.size())
					{
						std::string str;
						str.append(bot_strt.math_columns[t]);
						sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.math_columns[(sint)bot_strt.math_columns.size() - 1]);
						sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
					}

					if (cols.size() > 1)
					{
						if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
						{
							cols[1].append(" PRIMARY KEY");
						}
						for (uint x = 0; x < cols.size(); )
						{
							dbs_->columns[t][0].push_back(cols[x]);
							x++;

							if (x < cols.size())
							{
								dbs_->columns[t][1].push_back(cols[x]);
								x++;
							}
						}
					}
				}
				break;
			}
			case 2:
			{
				std::vector<std::vector<std::string>> tcols;
				std::vector<std::string> cols, colss;
				_char c = ' ';
				ret = vtool.AddValToVec(&dbs_->tables, "LAST_ACCESS", false, false);
				dbs_->columns.push_back(tcols);
				dbs_->columns[dbs_->columns.size() - 1].push_back(colss);
				dbs_->columns[dbs_->columns.size() - 1].push_back(colss);

				if (!bot_strt.code_columns.empty())
				{
					std::string str;
					str.append(bot_strt.code_columns[0]);
					sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
				}

				if (cols.size() > 1)
				{
					if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
					{
						cols[1].append(" PRIMARY KEY");
					}
					for (uint x = 0; x < cols.size(); )
					{
						dbs_->columns[dbs_->columns.size() - 1][0].push_back(cols[x]);
						x++;

						if (x < cols.size())
						{
							dbs_->columns[dbs_->columns.size() - 1][1].push_back(cols[x]);
							x++;
						}
					}
				}
				sint nh = -1;
				sint np = LockGMutex(MTX_FTYPE, &nh);

				if (np > -1)
				{
					for (uint t = 1; t < bot_symbol_types.size(); t++)
					{
						tcols.clear();
						cols.clear();
						colss.clear();
						ret = vtool.AddValToVec(&dbs_->tables, bot_symbol_types[t], false, false);
						dbs_->columns.push_back(tcols);
						dbs_->columns[t].push_back(colss);
						dbs_->columns[t].push_back(colss);

						if (t < bot_strt.code_columns.size())
						{
							std::string str;
							str.append(bot_strt.code_columns[t]);
							sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
						}
						else
						{
							std::string str;
							str.append(bot_strt.code_columns[(sint)bot_strt.code_columns.size() - 1]);
							sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
						}

						if (cols.size() > 1)
						{
							if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
							{
								cols[1].append(" PRIMARY KEY");
							}
							for (uint x = 0; x < cols.size(); )
							{
								dbs_->columns[dbs_->columns.size() - 1][0].push_back(cols[x]);
								x++;

								if (x < cols.size())
								{
									dbs_->columns[dbs_->columns.size() - 1][1].push_back(cols[x]);
									x++;
								}
							}
						}
					}
					if (!nh)
					{
						np = UnlockGMutex(MTX_FTYPE);
					}
				}
				break;
			}
			case 3:
			{
				break;
			}
			default:
			{
				for (uint t = 0; t < bot_strt.ex_tablenames.size(); t++)
				{
					ret = vtool.AddValToVec(&dbs_->tables, bot_strt.ex_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					_char c = ' ';

					if (t < bot_strt.ex_columns.size())
					{
						std::string str;
						str.append(bot_strt.ex_columns[t]);
						sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.ex_columns[(sint)bot_strt.ex_columns.size() - 1]);
						sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
					}

					if (cols.size() > 1)
					{
						if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
						{
							cols[1].append(" PRIMARY KEY");
						}
						for (uint x = 0; x < cols.size(); )
						{
							dbs_->columns[t][0].push_back(cols[x]);
							x++;

							if (x < cols.size())
							{
								dbs_->columns[t][1].push_back(cols[x]);
								x++;
							}
						}
					}
				}
				break;
			}
			}
			if (!h)
			{
				h = UnlockGMutex(MTX_STRT);
			}
			ret = PushToVec(dbs_, MTX_DBL, true, true, false);
		}
		return ret;
	}

	// Pthreads Functions

	sint StartThread(sint* thr_opt = 0)
	{
		if (!thr_opt)
		{
			return -1;
		}
		mk_thr = true;
		UpdMTXPrio();

		sint xc = GetThreadQuit();

		if (xc)
		{
			mk_thr = false;
			UpdMTXPrio();
			return -1;
		}

		TINFO_M tts;
		xc = GetVecEle((void*)&tts, MTX_TTS, lid);

		if (xc < 0)
		{
			mk_thr = false;
			UpdMTXPrio();
			return -1;
		}

		*thr_opt = tts.opt;
		sllint lc = TestThreadTRat((sint)BOT_ITER_TO);

		if (thr_exe_mod < tts.min_ratv)
		{
			mk_thr = false;
			UpdMTXPrio();
			return -8;
		}

		xc = 0;
		sint rc = SetVecEleMem((void*)&xc, MTX_TTS, lid, BOT_TTS_FIN, false);

		if (rc < 0)
		{
			mk_thr = false;
			UpdMTXPrio();
			return -1;
		}
		mk_thr = false;
		UpdMTXPrio();
		return 0;
	}
	sint ThreadRest(slint dur = BOT_MILLI_REST, sint qt_lvl = -1)
	{
		sint qt = GetThreadQuit();

		if (qt >= qt_lvl)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				sint rc = Output("finish signal", 2);
			}
		}
		else
		{
			slint rst = Rest(dur);
			std::chrono::steady_clock::time_point nt = std::chrono::steady_clock::now();
			sint rc = SetVecEleMem((void*)&nt, MTX_TTS, lid, BOT_TTS_TIMEP, false);
			return 0;
		}
		return -1;
	}
	sint ThreadEnd(std::vector<ullint>* rvals_ = 0)
	{
		mk_thr = true;
		UpdMTXPrio();
		sint fin = 1;
		sint rc = SetVecEleMem((void*)&fin, MTX_TTS, lid, BOT_TTS_FIN, false);

		if (rvals_)
		{
			rc = SetVecEleMem((void*)&fin, MTX_TTS, lid, BOT_TTS_VALS, false);
		}
		mk_thr = false;
		UpdMTXPrio();
		return 0;
	}
	sint PThreadErr(_char in_chr[], sint err)
	{
		switch (err)
		{
		case EINVAL:
		{
			sint x = bot_sprintf(in_chr, 256, "The mutex was created with the protocol attribute having the value PTHREAD_PRIO_PROTECT and the calling thread's priority is higher than the mutex's current priority ceiling(%i)", err);
			break;
		}
		case EAGAIN:
		{
			sint x = bot_sprintf(in_chr, 256, "The mutex could not be acquired because the maximum number of recusive locks for mutex has been exceeded(%i)", err);
			break;
		}
		case ENOTRECOVERABLE:
		{
			sint x = bot_sprintf(in_chr, 256, "The state protected by the mutex is not recoverable(%i)", err);
			break;
		}
		case EOWNERDEAD:
		{
			sint x = bot_sprintf(in_chr, 256, "The mutex is a robust mutex and the process containing the previous owning thread terminated while holding the mutex lock. The mutex shall be acquired by the calling thread and it is up to the new owner to make the state consistent(%i)", err);
			break;
		}
		case EDEADLK:
		{
			sint x = bot_sprintf(in_chr, 256, "A deadlock condition was or the mutex is type PTHREAD_MUTEX_ERRORCHECK and the current thread already owns the mutex(%i)", err);
			break;
		}
		case EBUSY:
		{
			sint x = bot_sprintf(in_chr, 256, "The mutex could not be acquired because it was already locked(%i)", err);
			break;
		}
		case EPERM:
		{
			sint x = bot_sprintf(in_chr, 256, "The mutex type is PTHREAD_MUTEX_ERRORCHECK or PTHREAD_MUTEX_RECURSIVE, or the mutex is a robust mutex, and the current thread does not own the mutex(%i)", err);
			break;
		}
		default:
		{
			sint x = bot_sprintf(in_chr, 256, "The mutex err code is unknown(%i)", err);
			return -1;
			break;
		}
		}
		return 0;
	}
	sint IncrThreads()
	{
		sint ret = -1;
		sint h = -1;
		sint l = LockGMutex(MTX_TTS, &h);
		
		if (l > -1)
		{
			ret = bot_thr_ct.Incr();

			if (!h)
			{
				h = UnlockGMutex(MTX_TTS);
			}
		}
		return ret;
	}
	sint DecrThreads()
	{
		sint ret = -1;
		sint h = -1;
		sint l = LockGMutex(MTX_TTS, &h);

		if (l > -1)
		{
			ret = bot_thr_ct.Decr();

			if (!h)
			{
				h = UnlockGMutex(MTX_TTS);
			}
		}
		return ret;
	}
	sint GetThreadsCt()
	{
		sint ret = -1;
		sint h = -1;
		sint l = LockGMutex(MTX_TTS, &h);

		if (l > -1)
		{
			ret = bot_thr_ct.Get();

			if (!h)
			{
				h = UnlockGMutex(MTX_TTS);
			}
		}
		return ret;
	}
	sint GetThreadQuit()
	{
		sint ret = -1;
		sint h = -1;
		sint l = LockGMutex(MTX_TTS, &h);

		if (l > -1)
		{
			ret = bot_thr_ct.GetQuit();

			if (!h)
			{
				h = UnlockGMutex(MTX_TTS);
			}
		}
		return ret;
	}
	sint SetThreadQuit(sint val = -1)
	{
		sint ret = -1;
		sint h = -1;
		sint l = LockGMutex(MTX_TTS, &h);

		if (l > -1)
		{
			if (val > -1)
			{
				ret = bot_thr_ct.SetQuit(val);
			}
			if (!h)
			{
				h = UnlockGMutex(MTX_TTS);
			}
		}
		return ret;
	}
	sint StopAllThreads()
	{
		if (debug_lvl >= 10 && debug_m)
		{
			sint xc = Output("::StopAllThreads()", 2);
		}

		sint log_at = -1;
		sint db_at = -1;
		sint ret = -1;
		bool done = false;

		while (!done)
		{
			slint rst = Rest(BOT_QUITREST);
			bool all = true;
			sint siz = VecSize(MTX_TTS) - 1;

			if (siz)
			{
				while (siz > 0)
				{
					if (siz != log_at && siz != db_at)
					{
						sint ret = 0;
						sint xc = GetVecEleMem((void*)&ret, MTX_TTS, siz, BOT_TTS_FIN);

						if (xc > -1)
						{
							if (log_at < 0)
							{
								std::string nm;
								xc = GetVecEleMem((void*)&nm, MTX_TTS, siz, BOT_TTS_TNAME);

								if (!strcmp(nm.c_str(), "LogMaintenance"))
								{
									log_at = siz;
								}
							}
							if (db_at < 0)
							{
								std::string nm;
								xc = GetVecEleMem((void*)&nm, MTX_TTS, siz, BOT_TTS_TNAME);

								if (!strcmp(nm.c_str(), "DBMaintenance"))
								{
									db_at = siz;
								}
							}
							if (!ret)
							{
								all = false;
							}
						}
					}
					siz--;
				}
				if (all)
				{
					done = true;
				}
			}
			else
			{
				done = true;
			}
		}

		ret = SetThreadQuit(2);
		done = false;

		while (!done)
		{
			slint rst = Rest(BOT_QUITREST);
			bool all = true;
			sint siz = VecSize(MTX_TTS) - 1;

			if (siz)
			{
				while (siz > 0)
				{
					if (siz != log_at)
					{
						sint ret = 0;
						sint xc = GetVecEleMem((void*)&ret, MTX_TTS, siz, BOT_TTS_FIN);

						if (xc > -1)
						{
							if (!ret)
							{
								all = false;
							}
						}
					}
					siz--;
				}
				if (all)
				{
					done = true;
				}
			}
			else
			{
				done = true;
			}
		}

		ret = SetThreadQuit(3);
		done = false;

		while (!done)
		{
			slint rst = Rest(BOT_QUITREST);
			bool all = true;
			sint siz = VecSize(MTX_TTS) - 1;

			if (siz)
			{
				while (siz > 0)
				{
					sint ret = 0;
					sint xc = GetVecEleMem((void*)&ret, MTX_TTS, siz, BOT_TTS_FIN);

					if (xc > -1)
					{
						if (!ret)
						{
							all = false;
						}
					}
					siz--;
				}
				if (all)
				{
					done = true;
				}
			}
			else
			{
				done = true;
			}
		}
		return 0;
	}
	sint JoinThread(sint thrid = -1, void* vp_ = 0)
	{
		if (thrid < 0)
		{
			return -1;
		}
		sint h = -1;
		sint l = LockGMutex(MTX_TTS, &h);

		if (l > -1)
		{
			sint xc = pthread_join(tts_vec.d_vec[thrid].thread, &vp_);

			if (!h)
			{
				h = UnlockGMutex(MTX_TTS);
			}

			if (!xc)
			{
				return 0;
			}
		}
		return -1;
	}
	sint InitThread(TINFO_M *tts_ = 0, sint* ret_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::InitThread(TINFO_M* tts_(%i), sint* ret_(%i))", (sint)tts_, (sint)ret_);
			op = Output(outp.carr, 2);
		}

		if (!tts_)
		{
			return -1;
		}

		sint xc = CreateThread(tts_, ret_);

		if (!xc)
		{
			while (FinishThread(tts_, ret_))
			{
				slint rst = Rest(BOT_MILLI_REST);
			}
		}
		return xc;
	}
	sint InitThreads(std::vector<TINFO_M> *tts_ = 0, std::vector<sint>* rets_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::InitThreads(std::vector<TINFO_M> *tts_(%i), std::vector<sint> *rets_(%i))", (sint)tts_, (sint)rets_);
			op = Output(outp.carr, 2);
		}

		if (!tts_ || !rets_)
		{
			return -1;
		}

		uint msiz = 0;
		sint ret = 0;

		for (uint siz = 0; siz < tts_->size(); siz++)
		{
			while (rets_->size() <= siz)
			{
				rets_->push_back(-1);
			}
			sint tret = CreateThread(&tts_->at(siz), &rets_->at(siz));

			if (tret)
			{
				
				sint e = -1;
			}

			tret = GetThreadsCt();

			if ((tret < 2) || (siz == tts_->size() - 1))
			{
				for (uint nsiz = msiz; nsiz <= siz; nsiz++)
				{
					sint xret = -1;
					
					while (FinishThread(&tts_->at(nsiz), &xret))
					{
						slint rst = Rest(BOT_MILLI_REST);
					}

					if (nsiz < rets_->size())
					{
						rets_->at(nsiz) = xret;
					}
					else
					{
						rets_->push_back(xret);
					}
				}
				msiz = siz + 1;
			}
		}
		ret = vtool.CleanVec(tts_);
		return ret;
	}
	sint CreateThread(TINFO_M* tts_ = 0, sint* ret_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::CreateThread(TINFO_M* tts_(%i), sint* ret(%i))", (sint)tts_, (sint)ret_);
			op = Output(outp.carr, 2);
		}

		if (!tts_)
		{
			return -1;
		}

		sint xc = -1;
		bool done = false;

		while (!done)
		{
			TINFO tts(tts_->opt, tts_->thread_name.c_str(), tts_->func, tts_->c_by, tts_->min_ratv);
			tts.fin = -9;
			xc = PushToVec(&tts, MTX_TTS, true, true, false);

			if (xc > -1)
			{
				sint na = pthread_attr_init(&tts.attr);

				if (tts_->opt)
				{
					pthread_attr_setdetachstate(&tts.attr, PTHREAD_CREATE_JOINABLE);
				}
				else
				{
					pthread_attr_setdetachstate(&tts.attr, PTHREAD_CREATE_DETACHED);
				}

				for (uint ct = 0; ct < 10000; ct++)
				{
					xc = DecrThreads();

					if (xc < 0)
					{
						slint rst = Rest((slint)BOT_MILLI_REST);
					}
					else
					{
						ct = 10000;
					}
				}

				if (xc < 0)
				{
					sint xp = Output("error: decrementing open thread count.", 1, 2);
					return xc;
				}

				sint h = -1;
				sint p = LockElement(MTX_TTS, tts.lid, &h, true, false);

				if (p > -1)
				{
					mk_thr = true;
					na = UpdMTXPrio();
					xc = pthread_create(&tts.thread, &tts.attr, tts.func, (void*)tts.lid);

					if (!xc)
					{
						na = pthread_attr_destroy(&tts.attr);
						na = SetVecEle((void*)&tts, MTX_TTS, tts.lid, false, false);
					}
					else
					{

						na = -1;
					}

					if (!h)
					{
						h = UnlockElement(MTX_TTS, tts.lid, false);
					}

					if (debug_lvl >= 10 && debug_m)
					{
						carr_512 ncar;
						if (xc)
						{
							na = bot_sprintf(ncar.carr, ncar.siz, "Error(%i) initializing thread:%s", xc, tts.thread_name.c_str());
						}
						else
						{
							na = bot_sprintf(ncar.carr, ncar.siz, "thread created %i %s", tts.lid, tts.thread_name.c_str());
						}
						na = Output(ncar.carr, 2);
					}
					mk_thr = false;
					na = UpdMTXPrio();
				}

				while (tts.fin < -8)
				{
					slint rst = Rest(BOT_MILLI_REST);
					na = GetVecEleMem((void*)&tts.fin, MTX_TTS, tts.lid, BOT_TTS_FIN);
				}

				tts_->Renew(&tts);

				if (tts.fin > -8)
				{
					done = true;
				}
				else
				{
					while (FinishThread(tts_, ret_))
					{
						slint rst = Rest(BOT_MILLI_REST);
					}

					if (debug_lvl >= 100 && debug_m)
					{
						carr_512 ncar;
						na = bot_sprintf(ncar.carr, ncar.siz, "thread cleared, tts_->lid=%i thread:%s - failed execution speed check", tts.lid, tts.thread_name.c_str());
						na = Output(ncar.carr, 2);
					}
				}
			}
		}
		return xc;
	}
	sint FinishThread(TINFO_M* tts_ = 0, sint* ret_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FinishThread(TINFO_M* tts_(%i), sint* ret_(%i))", (sint)tts_, (sint)ret_);
			op = Output(outp.carr, 2);
		}

		if (!tts_)
		{
			return -1;
		}

		sint xc = -1;

		// opt 0 = detach
		//     1 = join
		xc = GetVecEleMem((void*)&tts_->fin, MTX_TTS, tts_->lid, BOT_TTS_FIN);

		if (xc > -1)
		{
			xc = -1;

			switch (tts_->opt)
			{
			case 0:
			{
				if (tts_->fin == -8)
				{
					sint rc = ClearVecEle(MTX_TTS, tts_->lid, false);
					rc = IncrThreads();
				}
				return 0;
				break;
			}
			case 1:
			{
				sint lx = Output("attempting to join thread", 2);

				if (tts_->fin == 1 || tts_->fin == -1 || tts_->fin == -8)
				{
					mk_thr = true;
					sint hx = UpdMTXPrio();
					hx = -1;
					lx = LockElement(MTX_TTS, tts_->lid, &hx, true, false);

					if (lx > -1)
					{
						void* vp_ = 0;
						xc = JoinThread(tts_->lid, vp_);

						if (xc)
						{
							if (debug_lvl >= 1 && debug_m)
							{
								carr_128 outp;
								lx = bot_sprintf(outp.carr, outp.siz, "Error(%i) joining thread:%i", xc, tts_->lid);
								lx = Output(outp.carr, 1, 2);
							}
							xc = -1;
						}
						else
						{
							if (ret_)
							{
								*ret_ = (sint)vp_;

								if (debug_lvl >= 1 && debug_m)
								{
									carr_128 outp;
									lx = bot_sprintf(outp.carr, outp.siz, "thread joined, tts_->lid:%i *ret_:(%i)", tts_->lid, *ret_);
									lx = Output(outp.carr, 2);
								}
							}
							else
							{
								sint valx = (sint)vp_;

								if (debug_lvl >= 1 && debug_m)
								{
									carr_128 outp;
									lx = bot_sprintf(outp.carr, outp.siz, "error: thread joined, tts_->lid=%i xc==%i, return value will be lost as it was not assigned.", tts_->lid, valx);
									lx = Output(outp.carr, 1, 2);
								}
							}

							lx = ClearVecEle(MTX_TTS, tts_->lid, false);
							lx = IncrThreads();

							if (lx < 0)
							{
								lx = Output("error: incrementing open thread count.", 1, 2);
								xc = -1;
							}
						}
						if (!hx)
						{
							hx = UnlockElement(MTX_TTS, tts_->lid, false);
						}
						mk_thr = false;
						lx = UpdMTXPrio();
						tts_->Clear();
					}
				}
				break;
			}
			default:
			{
				if (debug_lvl >= 1 && debug_m)
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "Error Invalid join/detach opt(%i) for thread(%i)", xc, tts_->lid);
					op = Output(outp.carr, 2);
				}
				break;
			}
			}
		}
		return xc;
	}
	sint TM()
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_8 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::TM()");
			op = Output(outp.carr, 2);
		}

		bool bot_started = false;

		while (!GetThreadQuit())
		{
			bool has_dm = false;
			bool has_self = false;
			bool has_log = false;
			bool has_cons = false;

			for (sint p = 0; p < VecSize(MTX_TTS); p++)
			{
				TINFO_M ntts;
				sint sp = GetVecEle(&ntts, MTX_TTS, p);

				if (sp > -1)
				{
					if (!strcmp(ntts.thread_name.c_str(), "machine"))
					{
						has_self = true;
					}
					else if (!strcmp(ntts.thread_name.c_str(), "LogMaintenance"))
					{
						has_log = true;
					}
					else if (!strcmp(ntts.thread_name.c_str(), "DBMaintenance"))
					{
						has_dm = true;
					}
					else if (!strcmp(ntts.thread_name.c_str(), "ConsoleThread"))
					{
						has_cons = true;
					}
					else {}

					if ((ntts.fin == 1 || ntts.fin == -1) && !ntts.opt)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "clearing ele(%i)", p);
							op = Output(outp.carr, 2);
						}
						ClearVecEle(MTX_TTS, ntts.lid, false);
					}
					else if (ntts.fin == -10 && strlen(ntts.thread_name.c_str()))
					{
						if (debug_lvl >= 1 && debug_m)
						{
							if (p)
							{
								carr_64 outp;
								sint op = bot_sprintf(outp.carr, outp.siz, "found unstarted thread (%i)", p);
								op = Output(outp.carr, 2);
							}
						}
					}
					else {}
				}
				else
				{
					sint ret = -1;
					sp = FinishThread(&ntts, &ret);
				}
			}

			if (!has_self && !lid)
			{
				if (debug_lvl >= 1 && debug_m)
				{
					sint xc = Output("adding machine to thread list", 2);
				}

				TINFO tts(0, ptn.c_str(), NULL);
				tts.fin = 0;
				tts.t_I = bot_st;
				sint xc = PushToVec(&tts, MTX_TTS, true, true, false);
				std::vector<TINFO_M> create_vec;

				for (sint p = 0; p < 100; p++)
				{
					TINFO_M tts(1, "TestThread", TestThread, lid);
					create_vec.push_back(tts);
				}
				if (!create_vec.empty())
				{
					if (debug_lvl >= 1 && debug_m)
					{
						sint xc = Output("creating test threads", 2);
					}
					std::vector<sint> rets;
					sint p = InitThreads(&create_vec, &rets);
				}
			}
			if (!has_log)
			{
				if (debug_lvl >= 1 && debug_m)
				{
					sint xc = Output("adding LogMaintenance to thread list", 2);
				}
				TINFO_M tts(0, "LogMaintenance", LogMaintenance, lid, 1.0f);
				sint xc = InitThread(&tts);
			}
			if (!has_dm)
			{
				if (debug_lvl >= 1 && debug_m)
				{
					sint xc = Output("adding DBMaintenance to thread list", 2);
				}
				TINFO_M tts(0, "DBMaintenance", DBMaintenance, lid, 1.0f);
				sint xc = InitThread(&tts);
			}
			if (!has_cons)
			{
				if (!bot_started)
				{
					if (debug_lvl >= 1 && debug_m)
					{
						sint xc = Output("adding ConsoleThread to thread list", 2);
					}
					TINFO_M tts(0, "ConsoleThread", ConsoleThread, lid, 1.0f);
					sint xc = InitThread(&tts);
					bot_started = true;
				}
				else
				{
					SetThreadQuit(1);
				}
			}
			slint rst = Rest((sint)BOT_THRREST);
		}
		sint xc = StopAllThreads();
		return 0;
	}
	sllint TestThreadIter(sint to_ = (sint)BOT_ITER_TO)
	{
		std::chrono::high_resolution_clock::time_point t_I = std::chrono::high_resolution_clock::now();
		float val = 3610.0f;

		for (sint xc = 0; xc < to_; xc++)
		{
			val /= 1.333f;
		}

		std::chrono::high_resolution_clock::time_point t_II = std::chrono::high_resolution_clock::now();
		std::chrono::duration<sllint, std::nano> span = std::chrono::duration_cast<std::chrono::duration<sllint, std::nano>>(t_II - t_I);
		sllint lc = (sllint)span.count();

		if (debug_lvl >= 1 && debug_m)
		{
			carr_512 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "%s: iter_to:%i span.count()=%lli", ptn.c_str(), to_, lc);
			op = Output(outp.carr, 2);
		}
		return lc;
	}
	sllint TestThreadTRat(sint to_ = (sint)BOT_ITER_TO)
	{
		sllint rc = TestThreadIter(to_);
		sllint xc = rc;
		sint h = -1;
		sint p = LockGMutex(MTX_TRAT, &h);

		if (p > -1)
		{
			if (xc < thr_exe_min)
			{
				thr_exe_min = xc;
			}
			else
			{
				if (xc > 0)
				{
					if (thr_exe_min <= 0)
					{
						thr_exe_min = xc;
					}
					else
					{
						xc = thr_exe_min;
					}
				}
			}
			if (!h)
			{
				h = UnlockGMutex(MTX_TRAT);
			}
		}

		if (xc != rc)
		{
			thr_exe_mod = (float)xc / (float)rc;
		}
		else
		{
			thr_exe_mod = 1.0f;
		}

		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "this thread's time was:%lli compared to fastest time:%lli setting this ratio:%.9f", rc, xc, thr_exe_mod);
			op = Output(outp.carr, 2);
		}
		return rc;
	}

	sint CheckPrintFs()
	{
		std::string pth;
		BOTPath(&pth, BOT_MOD_NM);
		BOT_FILE_M xfile("litebot", ".h", pth.c_str(), BOT_FILE_READ, BOT_F_CON, -1, -1, lid);
		sint of = -1;
		sint lx = BOTOpenFile(&xfile, &of);

		if (lx > -1)
		{
			uint lct = 1;
			bool done = false;

			while (!done)
			{
				carr_2048 ncar;

				if (f_con[xfile.fcon]->fstrm.getline(ncar.carr, 2048))
				{
					std::string str;
					str.append(ncar.carr);
					sint f = str.find("bot_sprintf", 0);

					if (f > -1)
					{
						std::cout << "bot_sprintf found at litebot.h line:" << lct << std::endl;
						std::vector<uint> litv, ordv;
						sint xc = LitLocs(&litv, ncar.carr);
						uint fct = 0;

						if (litv.size() > 1)
						{
							std::string scar;

							for (uint x = litv[0] + 1; x < litv[litv.size() - 1]; x++)
							{
								scar.push_back(ncar.carr[x]);
							}
							for (sint xf = scar.find("%", 0); xf > -1; xf = scar.find("%", xf + 1))
							{
								fct++;
							}

							scar.clear();

							if (fct)
							{
								for (uint x = litv[litv.size() - 1] + 1; x < str.length() - 2; x++)
								{
									scar.push_back(str[x]);
								}
								litv.clear();
								xc = LitLocs(&litv, scar.c_str());
								xc = OrdLocs(&litv, &ordv, scar.c_str());
								uint sct = 0;

								for (sint xf = scar.find(",", 0); xf > -1; xf = scar.find(",", xf + 1))
								{
									xc = OrdEnc((uint)xf, &litv, &ordv, scar.c_str());

									if (xc < 0)
									{
										sct++;
									}
								}

								if (fct != sct)
								{
									std::cout << "var args mismatch at line:" << lct << "; " << fct << " format specifiers, " << sct << " var args" << std::endl;
								}
								else
								{
									std::cout << "var args match at line:" << lct << std::endl;
								}
							}
						}
					}
					lct++;
				}
				else
				{
					done = true;
				}
			}

			std::cout << "litebot.h ends at line:" << lct << std::endl;

			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}
		}

		if (lx > -1)
		{
			std::string pth;
			BOTPath(&pth, BOT_MOD_NM);
			xfile.Renew("litebot", ".cpp", pth.c_str(), BOT_FILE_READ, BOT_F_CON, -1, -1, lid);
			sint of = -1;
			lx = BOTOpenFile(&xfile, &of);

			if (lx > -1)
			{
				uint lct = 1;
				bool done = false;

				while (!done)
				{
					carr_2048 ncar;

					if (f_con[xfile.fcon]->fstrm.getline(ncar.carr, 2048))
					{
						std::string str;
						str.append(ncar.carr);
						sint f = str.find("bot_sprintf", 0);

						if (f > -1)
						{
							std::cout << "bot_sprintf found at litebot.cpp line:" << lct << std::endl;
							std::vector<uint> litv, ordv;
							sint xc = LitLocs(&litv, ncar.carr);
							uint fct = 0;

							if (litv.size() > 1)
							{
								std::string scar;

								for (uint x = litv[0] + 1; x < litv[litv.size() - 1]; x++)
								{
									scar.push_back(ncar.carr[x]);
								}
								for (sint xf = scar.find("%", 0); xf > -1; xf = scar.find("%", xf + 1))
								{
									fct++;
								}

								scar.clear();

								if (fct)
								{
									for (uint x = litv[litv.size() - 1] + 1; x < str.length() - 2; x++)
									{
										scar.push_back(str[x]);
									}
									litv.clear();
									xc = LitLocs(&litv, scar.c_str());
									xc = OrdLocs(&litv, &ordv, scar.c_str());
									uint sct = 0;

									for (sint xf = scar.find(",", 0); xf > -1; xf = scar.find(",", xf + 1))
									{
										xc = OrdEnc((uint)xf, &litv, &ordv, scar.c_str());

										if (xc < 0)
										{
											sct++;
										}
									}

									if (fct != sct)
									{
										std::cout << "var args mismatch at line:" << lct << "; " << fct << " format specifiers, " << sct << " var args" << std::endl;
									}
									else
									{
										std::cout << "var args match at line:" << lct << std::endl;
									}
								}
							}
						}
						lct++;
					}
					else
					{
						done = true;
					}
				}
				std::cout << "litebot.cpp ends at line:" << lct << std::endl;
				if (!of)
				{
					of = BOTCloseFile(&xfile);
				}
				return lx;
			}
		}
		return -1;
	}

	// work

	sint ProcErrLog(sint opt = -1, c_char* in_file_p = "", c_char* in_file_n = "", c_char* in_file_t = "", c_char* rampid = "", c_char* insp_type = "", c_char* date_ = "", c_char* eid_ = "", c_char* toval_ = "")
	{
		if (!in_file_n || !in_file_t || !in_file_p || !rampid)
		{
			return -1;
		}
		/*
		opt:

		1 = change ramp to toval_
		2 = change insptype to toval_
		3 = change date to toval_
		4 = change employee id to toval_

		*/
		carr_32 dcar;
		sint of = GetDate(&dcar, false);
		std::string vdate;
		for (uint x = 4; x < strlen(dcar.carr); x++)
		{
			vdate.push_back(dcar.carr[x]);
		}
		for (uint x = 0; x < 4; x++)
		{
			vdate.push_back(dcar.carr[x]);
		}
		of = BotOut(1, "searching for inspections ");

		bool use_ramp = false;

		if (strlen(rampid))
		{
			of = BotOut(2, "ramp: ", rampid);
			use_ramp = true;
		}

		bool use_itype = false;

		if (strlen(insp_type))
		{
			of = BotOut(2, "type: ", insp_type);
			use_itype = true;
		}

		bool use_date = false;

		if (strlen(date_))
		{
			of = BotOut(2, "date: ", date_);
			use_date = true;
		}

		bool use_eid = false;

		if (strlen(eid_))
		{
			of = BotOut(2, "inspector id: ", eid_);
			use_eid = true;
		}

		of = BotOut(4, "in file: ", in_file_p, in_file_n, in_file_t);
		std::vector<carr_512> vvec;
		BOT_FILE_M xfile(in_file_n, in_file_t, in_file_p, BOT_FILE_READ, BOT_F_CON, -1, -1, lid);
		of = -1;
		sint lx = BOTOpenFile(&xfile, &of);

		if (lx > -1)
		{
			_char spc = ' ';
			std::string nm_str;
			bool done = false;

			while (!done)
			{
				carr_512 ncar;

				if (f_con[xfile.fcon]->fstrm.getline(ncar.carr, 511))
				{
					if (strlen(ncar.carr) > 22)
					{
						bool pass = false;

						if (use_ramp)
						{
							std::string nvin;

							for (size_t siz = 0; siz < 5 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(rampid, nvin.c_str()))
							{
								pass = true;
							}
						}
						if (use_itype)
						{
							std::string nvin;

							for (size_t siz = 45; siz < 47 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(insp_type, nvin.c_str()))
							{
								pass = true;
							}
						}
						if (use_date)
						{
							std::string nvin;

							for (size_t siz = 29; siz < 37 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(vdate.c_str(), nvin.c_str()))
							{
								pass = true;
							}
						}
						if (use_eid)
						{
							std::string nvin;

							for (size_t siz = 37; siz < 40 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(eid_, nvin.c_str()))
							{
								pass = true;
							}
						}

						if (pass)
						{
							switch (opt)
							{
							case 1:
							{
								for (uint x = 0; x < ncar.siz; x++)
								{
									for (uint y = 0; y < 5; y++)
									{
										if (y < strlen(toval_))
										{
											memcpy((void*)&ncar.carr[y], (void*)&toval_[y], 1);
										}
										else
										{
											memcpy((void*)&ncar.carr[y], (void*)&spc, 1);
										}
									}
								}
								break;
							}
							case 2:
							{
								for (uint x = 0; x < ncar.siz; x++)
								{
									for (uint y = 45; y < 47; y++)
									{
										if (y - 45 < strlen(toval_))
										{
											memcpy((void*)&ncar.carr[y], (void*)&toval_[y - 45], 1);
										}
									}
								}
								break;
							}
							case 3:
							{
								for (uint x = 0; x < ncar.siz; x++)
								{
									std::string pdate;

									if (strlen(toval_) > 8)
									{
										for (uint x = 0; x < strlen(toval_); x++)
										{
											if (toval_[x] != '/')
											{
												pdate.push_back(toval_[x]);
											}
										}
									}
									else
									{
										pdate.append(toval_);
									}
									std::string ndate;

									if (pdate[0] == '0' || pdate[0] == '1')
									{
										for (uint x = 4; x < pdate.length(); x++)
										{
											ndate.push_back(pdate[x]);
										}
										for (uint x = 0; x < 4; x++)
										{
											ndate.push_back(pdate[x]);
										}
									}
									else
									{
										ndate.append(pdate.c_str());
									}
									for (uint y = 29; y < 37; y++)
									{
										if (y - 29 < ndate.length())
										{
											memcpy((void*)&ncar.carr[y], (void*)&ndate[y - 29], 1);
										}
									}
								}
								break;
							}
							case 4:
							{
								for (uint x = 0; x < ncar.siz; x++)
								{
									for (uint y = 37; y < 40; y++)
									{
										if (y - 37 < strlen(toval_))
										{
											memcpy((void*)&ncar.carr[y], (void*)&toval_[y - 37], 1);
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
						}
						vvec.push_back(ncar);
					}
				}
				else
				{
					done = true;
				}
			}
			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}

			if (use_ramp)
			{
				nm_str.append(rampid);
				nm_str.push_back('_');
			}
			if (use_itype)
			{
				nm_str.append(insp_type);
				nm_str.push_back('_');
			}
			if (use_date)
			{
				nm_str.append(vdate.c_str());
				nm_str.push_back('_');
			}
			if (use_eid)
			{
				nm_str.append(eid_);
				nm_str.push_back('_');
			}

			nm_str.append("redo");
			nm_str.append(vdate.c_str());
			std::string pth;
			BOTPath(&pth, BOT_MOD_NM);
			xfile.Renew(nm_str.c_str(), ".txt", pth.c_str(), BOT_FILE_APPEND, BOT_F_CON, -1, -1, lid);
			of = -1;
			lx = BOTOpenFile(&xfile, &of, true);

			for (uint siz = 0; siz < vvec.size(); siz++)
			{
				f_con[xfile.fcon]->fstrm << vvec[siz].carr << std::endl;
			}

			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}
			return 0;
		}
		return -1;
	}

	sint ProcVINs(sint opt = -1, c_char* in_file_p = "", c_char* in_file_n = "", c_char* in_file_t = "", c_char* rampid = "", c_char* insp_type = "", c_char* date_ = "", c_char* eid_ = "", c_char* toval_ = "")
	{
		if (!in_file_n || !in_file_t || !in_file_p || !rampid)
		{
			return -1;
		}
		/*
		opt:
		-1/default = vin list
		1 = rename photos script
		2 = SQL - UPDATE insptype
		3 = correct inspdate

		*/
		carr_32 dcar;
		sint of = GetDate(&dcar, false);
		std::string vdate;
		for (uint x = 4; x < strlen(dcar.carr); x++)
		{
			vdate.push_back(dcar.carr[x]);
		}
		for (uint x = 0; x < 4; x++)
		{
			vdate.push_back(dcar.carr[x]);
		}
		of = BotOut(1, "searching for VINs ");

		bool use_ramp = false;

		if (strlen(rampid))
		{
			of = BotOut(2, "ramp: ", rampid);
			use_ramp = true;
		}

		bool use_itype = false;

		if (strlen(insp_type))
		{
			of = BotOut(2, "type: ", insp_type);
			use_itype = true;
		}

		bool use_date = false;

		if (strlen(date_))
		{
			of = BotOut(2, "date: ", date_);
			use_date = true;
		}

		bool use_eid = false;

		if (strlen(eid_))
		{
			of = BotOut(2, "inspector id: ", eid_);
			use_eid = true;
		}

		of = BotOut(4, "in file: ", in_file_p, in_file_n, in_file_t);
		std::vector<std::string> vvec;
		BOT_FILE_M xfile(in_file_n, in_file_t, in_file_p, BOT_FILE_READ, BOT_F_CON, -1, -1, lid);
		of = -1;
		sint lx = BOTOpenFile(&xfile, &of);

		if (lx > -1)
		{
			std::string nm_str;
			bool done = false;

			while (!done)
			{
				carr_512 ncar;

				if (f_con[xfile.fcon]->fstrm.getline(ncar.carr, 511))
				{
					if (strlen(ncar.carr) > 22)
					{
						bool pass = false;

						if (!use_ramp && !use_itype && !use_date && !use_eid)
						{
							pass = true;
						}

						if (use_ramp)
						{
							std::string nvin;

							for (size_t siz = 0; siz < 5 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(rampid, nvin.c_str()))
							{
								pass = true;
							}
							else
							{
								pass = false;
							}

						}
						if (use_itype)
						{
							std::string nvin;

							for (size_t siz = 45; siz < 47 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(insp_type, nvin.c_str()))
							{
								pass = true;
							}
							else
							{
								pass = false;
							}

						}
						if (use_date)
						{
							std::string nvin;

							for (size_t siz = 29; siz < 37 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(vdate.c_str(), nvin.c_str()))
							{
								pass = true;
							}
							else
							{
								pass = false;
							}

						}
						if (use_eid)
						{
							std::string nvin;

							for (size_t siz = 37; siz < 40 && ncar.carr[siz] != ' '; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							if (!strcmp(eid_, nvin.c_str()))
							{
								pass = true;
							}
							else
							{
								pass = false;
							}

						}

						if (pass)
						{
							std::string nvin;

							for (size_t siz = 5; siz < 23; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}

							switch (opt)
							{
							case 1:
							{
								carr_128 xcar;
								sint x = bot_sprintf(xcar.carr, xcar.siz, "ren ?27????%s20180325%s*.* ?27????%s20180324%s*.*", nvin.c_str(), insp_type, nvin.c_str(), insp_type);
								nvin.clear();
								nvin.append(xcar.carr);
								vvec.push_back(nvin);
								break;
							}
							case 2:
							case 3:
							{
								if (use_ramp && use_date && use_itype && use_eid)
								{
									carr_2048 xcar;
									sint x = bot_sprintf(xcar.carr, xcar.siz, "'%s',\n", nvin.c_str());
									nvin.clear();
									nvin.append(xcar.carr);
									vvec.push_back(nvin);
								}
								break;
							}
							default:
							{
								carr_32 xcar;
								sint x = bot_sprintf(xcar.carr, xcar.siz, "%s", nvin.c_str());
								nvin.clear();
								nvin.append(xcar.carr);
								vvec.push_back(nvin);
								break;
							}
							}
						}
					}
				}
				else
				{
					done = true;
				}
			}
			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}

			if (use_ramp)
			{
				nm_str.append(rampid);
				nm_str.push_back('_');
			}
			if (use_itype)
			{
				nm_str.append(insp_type);
				nm_str.push_back('_');
			}
			if (use_date)
			{
				nm_str.append(vdate.c_str());
				nm_str.push_back('_');
			}
			if (use_eid)
			{
				nm_str.append(eid_);
				nm_str.push_back('_');
			}
			switch (opt)
			{
			case 1:
			{
				nm_str.append("photo_correct_scripts_");
				break;
			}
			case 2:
			{
				vvec[vvec.size() - 1].pop_back();
				vvec[vvec.size() - 1].pop_back();

				if (use_ramp && use_date && use_itype && use_eid)
				{
					std::vector<std::string>nvec;
					nm_str.append("SQL_scripts_");
					carr_2048 xcar;
					sint x = bot_sprintf(xcar.carr, xcar.siz, "update vehicleadmin.inspect\n set insptype='%s'\n where insptype='%s'\n and inspdate=to_date('%s','mm/dd/yyyy'\n and ramp='%s'\n and empno='%s'\n and vin in (\n%v.s\n.\n);", toval_, insp_type, date_, rampid, eid_, &vvec);
					std::string str;
					str.append(xcar.carr);
					nvec.push_back(str);
					str.clear();
					bot_strclr(xcar.carr);
					x = bot_sprintf(xcar.carr, xcar.siz, "update vehicleadmin.damage\n set insptype='%s'\n where insptype='%s'\n and inspdate=to_date('%s','mm/dd/yyyy'\n and ramp='%s'\n and vin in (\n%v.s\n.\n);", toval_, insp_type, date_, rampid, &vvec);
					str.append(xcar.carr);
					nvec.push_back(str);
					vvec.clear();

					for (uint y = 0; y < nvec.size(); y++)
					{
						vvec.push_back(nvec[y]);
					}
				}
				break;
			}
			case 3:
			{
				vvec[vvec.size() - 1].pop_back();
				vvec[vvec.size() - 1].pop_back();

				if (use_ramp && use_date && use_itype && use_eid)
				{
					std::vector<std::string>nvec;
					nm_str.append("SQL_scripts_");
					carr_2048 xcar;
					sint x = bot_sprintf(xcar.carr, xcar.siz, "update vehicleadmin.inspect\n set inspdate=to_date('%s','mm/dd/yy')\n where insptype='%s'\n and inspdate=to_date('%s','mm/dd/yyyy'\n and ramp='%s'\n and empno='%s'\n and vin in (\n%v.s\n.\n);", toval_, insp_type, date_, rampid, eid_, &vvec);
					std::string str;
					str.append(xcar.carr);
					nvec.push_back(str);
					str.clear();
					bot_strclr(xcar.carr);
					x = bot_sprintf(xcar.carr, xcar.siz, "update vehicleadmin.damage\n set inspdate=to_date('%s','mm/dd/yyyy')\n where insptype='%s'\n and inspdate=to_date('%s','mm/dd/yyyy'\n and ramp='%s'\n and vin in (\n%v.s\n.\n);", toval_, insp_type, date_, rampid, &vvec);
					str.append(xcar.carr);
					nvec.push_back(str);
					vvec.clear();

					for (uint y = 0; y < nvec.size(); y++)
					{
						vvec.push_back(nvec[y]);
					}
				}
				break;
			}
			default:
			{
				nm_str.append("vin_");
				break;
			}
			}
			std::string pth;
			BOTPath(&pth, BOT_MOD_NM);
			xfile.Renew(nm_str.c_str(), ".txt", pth.c_str(), BOT_FILE_APPEND, BOT_F_CON, -1, -1, lid);
			of = -1;
			lx = BOTOpenFile(&xfile, &of, true);

			for (uint siz = 0; siz < vvec.size(); siz++)
			{
				f_con[xfile.fcon]->fstrm << vvec[siz].c_str() << std::endl;
			}

			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}
			return 0;
		}
		return -1;
	}

	sint GetVINs(c_char* in_file_p = "", c_char* in_file_n = "", c_char* in_file_t = "", c_char* rampid = "")
	{
		if (!in_file_n || !in_file_t || !in_file_p || !rampid)
		{
			return -1;
		}

		if (!strlen(rampid))
		{
			return -1;
		}

		std::string vrid;
		vrid.append(rampid);

		while (vrid.length() < 5)
		{
			vrid.push_back(' ');
		}
		std::vector<std::string> vvec;
		sint xc = BotOut(6, "searching for VINs from ramp: ", rampid, " in file: ", in_file_p, in_file_n, in_file_t);
		BOT_FILE_M xfile(in_file_n, in_file_t, in_file_p, BOT_FILE_READ, BOT_F_CON, -1, -1, lid);
		sint of = -1;
		sint lx = BOTOpenFile(&xfile, &of);

		if (lx > -1)
		{
			bool done = false;

			while (!done)
			{
				carr_1024 ncar;

				if (f_con[xfile.fcon]->fstrm.getline(ncar.carr, 1023))
				{
					if (strlen(ncar.carr) > 22)
					{
						std::string nvin;

						for (size_t siz = 0; siz < 5; siz++)
						{
							nvin.push_back(ncar.carr[siz]);
						}

						if (!strcmp(vrid.c_str(), nvin.c_str()))
						{
							nvin.clear();


							for (size_t siz = 5; siz < 23; siz++)
							{
								nvin.push_back(ncar.carr[siz]);
							}
							carr_128 xcar;
							sint x = bot_sprintf(xcar.carr, xcar.siz, "ren ?27????0420180325%s*.* ?27????0420180324%s*.*", nvin.c_str(), nvin.c_str());
							nvin.clear();
							nvin.append(xcar.carr);
							vvec.push_back(nvin);
						}
					}
				}
				else
				{
					done = true;
				}
			}
			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}

			std::string nm_str;
			carr_32 dcar;
			of = GetDate(&dcar, false);
			nm_str.append(rampid);
			nm_str.append("vins");
			nm_str.append(dcar.carr);
			std::string pth;
			BOTPath(&pth, BOT_MOD_NM);
			xfile.Renew(nm_str.c_str(), ".txt", pth.c_str(), BOT_FILE_APPEND, BOT_F_CON, -1, -1, lid);
			of = -1;
			lx = BOTOpenFile(&xfile, &of, true);

			for (uint siz = 0; siz < vvec.size(); siz++)
			{
				f_con[xfile.fcon]->fstrm << vvec[siz].c_str() << std::endl;
			}

			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}
		}
		return -1;
	}

	sint AddDlrCode(c_char* to_vin = "", c_char* in_file = "")
	{
		if (strlen(to_vin) != 17)
		{
			return -1;
		}

		std::cout << "searching for VIN: " << to_vin << " to correct dealer code in file: " << in_file << std::endl;
		std::string pth;
		BOTPath(&pth, BOT_MOD_NM);
		BOT_FILE_M xfile(in_file, ".txt", pth.c_str(), BOT_FILE_OVERW, BOT_F_CON, -1, -1, lid);
		sint of = -1;
		sint lx = BOTOpenFile(&xfile, &of);

		if (lx > -1)
		{
			//lx = 1;
			bool done = false;

			while (!done)
			{
				size_t lin_strt = (size_t)f_con[xfile.fcon]->fstrm.tellp();
				carr_512 ncar;

				if (f_con[xfile.fcon]->fstrm.getline(ncar.carr, 511))
				{
					if (strlen(ncar.carr) > 23)
					{
						_char cvin[18] = { 0 };

						for (size_t siz = 0; siz < 17; siz++)
						{
							memcpy(&cvin[siz], &ncar.carr[siz + 5], 1);
						}

						std::cout << "VIN: " << cvin << " : " << lx << std::endl;

						if (!strcmp(to_vin, cvin))
						{
							f_con[xfile.fcon]->fstrm.seekp(lin_strt + 81);
							std::cout << "writing dealer code at: " << f_con[xfile.fcon]->fstrm.tellp() << " for VIN: " << cvin << std::endl;
							f_con[xfile.fcon]->fstrm.write("ZZZZZZ", strlen("ZZZZZZ"));
							done = true;

							if (!of)
							{
								of = BOTCloseFile(&xfile);
							}
							return 0;
						}
					}
				}
				else
				{
					done = true;
				}
				lx++;
			}

			if (!of)
			{
				of = BOTCloseFile(&xfile);
			}
		}
		return -1;
	}

	static void* DBMaintenance(void* vp_ = 0);
	static void* LITEBotMaintenance(void* vp_ = 0);
	static void* CodeMaintenance(void* vp_ = 0);
	static void* LogMaintenance(void* vp_ = 0);
	static void* TestThread(void* vp_ = 0);
	static void* ConsoleThread(void* vp_ = 0);
	static void* ScanFileThread(void* vp_ = 0);
	static void* RendFileThread(void* vp_ = 0);
};

#endif