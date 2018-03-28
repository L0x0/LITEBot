#ifndef LOXOBOT_H
#define LOXOBOT_H

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

#ifdef _WIN32
#include <windows.h>
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
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include "../_includes/_andr/sqlite3.h"
#ifndef errno_t
#define errno_t signed short
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

#ifndef BOT_LOG_PATH
#define BOT_LOG_PATH "c:\\dev-litebot\\win_LITEBot\\_logs\\"
#else
#if (strlen(BOT_LOG_PATH) > 1024)
#define BOT_LOG_PATH "c:\\BOTLogs\\"
#else
#if (strlen(BOT_LOG_PATH) < 4)
#define BOT_LOG_PATH "c:\\BOTLogs\\"
#endif
#endif
#endif

#ifndef BOT_DB_PATH
#define BOT_DB_PATH "c:\\dev-litebot\\win_LITEBot\\_dbs\\"
#else
#if (strlen(BOT_DB_PATH) > 1024)
#define BOT_DB_PATH "c:\\BOTDBs\\"
#else
#if (strlen(BOT_DB_PATH) < 4)
#define BOT_DB_PATH "c:\\BOTDBs\\"
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

#ifndef BOT_MOD_PATH
#define BOT_MOD_PATH "c:\\dev-litebot\\win_LITEBot\\_mods\\"
#else
#if (strlen(BOT_MOD_PATH) > 1024)
#define BOT_MOD_PATH "c:\\BOTMods\\"
#else
#if (strlen(BOT_MOD_PATH) < 4)
#define BOT_MOD_PATH "c:\\BOTMods\\"
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

#ifndef BOT_STMT_OPTSLIM
#define BOT_STMT_OPTSLIM 13
#endif

#ifndef BOT_OP_OPTS
#define BOT_OP_OPTS 4
#endif

#ifndef BOT_MTX_MAXCT
#define BOT_MTX_MAXCT UINT_MAX
#endif

#ifndef BOT_LOGREST
#define BOT_LOGREST (BOT_MILLI_REST*500)
#endif

#ifndef BOT_DBREST
#define BOT_DBREST (BOT_MILLI_REST*350)
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

#define uint unsigned int
#define sint signed int
#define ulint unsigned long int
#define slint signed long int
#define ullint unsigned long long int
#define sllint signed long long int

#ifndef uchar
#define uchar unsigned char
#endif

#define cchar const char
#define schar signed char

#ifndef BOT_BOUND_CHR
#define BOT_BOUND_CHR (uchar)(UINT_MAX - 1)
#endif

#ifndef BOT_NOERROR_STR
#define BOT_NOERROR_STR "*BOTERROR*no error.*BOTERROR*"
#endif

#ifndef BOT_ERRORLIM_STR
#define BOT_ERRORLIM_STR "*BOTERROR*input exceeds size limit.*BOTERROR*"
#endif

#ifndef BOT_ERRORNINV_STR
#define BOT_ERRORNINV_STR "*BOTERROR*numerical format specifier used for char string type var.*BOTERROR*"
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

sint bot_str_err(sint err_no = 0, cchar* msg = "")
{
	switch (err_no)
	{
	case 0:
	{
		msg = BOT_NOERROR_STR;
		break;
	}
	case -1:
	{
		msg = BOT_ERRORLIM_STR;
		break;
	}
	case -2:
	{
		msg = BOT_ERRORNINV_STR;
		break;
	}
	case -4:
	{
		msg = BOT_ERRORPREC_STR;
		break;
	}
	case -5:
	{
		msg = BOT_ERRORFPREC_STR;
		break;
	}
	default:
	{
		msg = BOT_ERRORUK_STR;
		return -1;
		break;
	}
	}
	return 0;
}

const size_t bot_ustrlen(uchar val[] = 0) { if (!val) { return 0; } if (sizeof(val) < BOT_STRLEN_MAX) { size_t siz = 0; while (siz < BOT_STRLEN_MAX && siz < sizeof(val)) { if (val[siz] == '\0') { const size_t csiz = siz; return csiz; } siz++; } } return 0; }

void bot_strcpy(char inv[] = 0, char val[] = 0)
{
	if (!inv || !val)
	{
		return;
	}
	
	size_t isiz = sizeof(*inv);

	if (!isiz || isiz > BOT_STRLEN_MAX)
	{
		return;
	}
	
	for (size_t nsiz = 0; nsiz < isiz; nsiz++)
	{
		memcpy((void*)&inv[nsiz], (void*)&val[nsiz], sizeof(inv[nsiz]));

		if (val[nsiz] == '\0')
		{
			return;
		}
	}
	
	char nc = '\0';
	memcpy((void*)&inv[isiz-1], (void*)&nc, sizeof(inv[isiz-1]));
}

sint bot_strclr(char inchr[] = 0)
{
	if (!inchr)
	{
		return -1;
	}
	inchr = { 0 };
	return 0;
}

sint bot_strchk(char inchr[] = 0, size_t in_siz = 0)
{
	if (!inchr || !in_siz)
	{
		return -1;
	}
	size_t siz = 0;

	while (siz < in_siz)
	{
		if (inchr[siz] == '\0')
		{
			return (sint)siz;
		}
		siz++;
	}
	if (siz == in_siz)
	{
		inchr[in_siz - 1] = '\0';
		std::cout << "*BOTSTRERROR*char[]: \"" << inchr << "\" was without a terminating NULL byte.*BOTSTRERROR*" << std::endl;
	}
	return (sint)siz;
}

sint bot_sprintf(char inchr[] = 0, size_t in_siz = 0, cchar* fstr = 0, ...)
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
	char frm = '%';
	char spec = '.';

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
					if (fstr[siz + nsiz] == 'l' || fstr[siz + nsiz] == '-' || fstr[siz + nsiz] == '+' || fstr[siz + nsiz] == '0' || fstr[siz + nsiz] == '2' || fstr[siz + nsiz] == 'x' || fstr[siz + nsiz] == 'e' || fstr[siz + nsiz] == 'h' || fstr[siz + nsiz] == 'E')
					{
						if (!mustnum)
						{
							mustnum = true;
						}
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
					}
					else if (fstr[siz + nsiz] == 'd' || fstr[siz + nsiz] == 'f' || fstr[siz + nsiz] == 'u' || fstr[siz + nsiz] == 'i' || fstr[siz + nsiz] == 'X')
					{
						formspec.push_back(fstr[siz + nsiz]);
						fspecs.push_back(formspec);
						locs.push_back(siz);
						formspec.clear();
						siz += nsiz;
						nsiz = strsiz;
					}
					else if (fstr[siz + nsiz] == 's' || fstr[siz + nsiz] == 'c')
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
							inchr[0] = '\0';
							return -2;
						}
					}
					else if (fstr[siz + nsiz] == 'v')
					{
						if (!mustnum)
						{
							sint done = 0;
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							if (siz + nsiz < strsiz)
							{
								if (fstr[siz + nsiz] == '.')
								{
									formspec.push_back(fstr[siz + nsiz]);

									while (siz + nsiz < strsiz)
									{
										nsiz++;

										if (siz + nsiz < strsiz)
										{
											formspec.push_back(fstr[siz + nsiz]);

											if (fstr[siz + nsiz] == '.')
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
							inchr[0] = '\0';
							return -2;
						}
					}
					else
					{
						inchr[0] = '\0';
						return -3;
					}
				}
			}
		}
	}

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
				inchr[at_inchr] = fstr[sloc];
				at_inchr++;
				sloc++;
			}

			if (fspecs[siz].length() > 1)
			{
				sint isiz = 0;
				uint nsiz = 1;

				if (fspecs[siz][nsiz] == '.')
				{
					char fchr[3]{ 0 };
					nsiz++;

					for (uint fsiz = 0; fsiz < 3 && nsiz < fspecs[siz].length(); )
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
								inchr[0] = '\0';
								cchar* msg = "";
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
							fchr[fsiz] = fspecs[siz][nsiz];
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							fchr[fsiz] = '\0';
							break;
						}
						}

						if (fsiz == 3)
						{
							fchr[fsiz - 1] = '\0';
						}
						else
						{
							if (fchr[fsiz] == '\0')
							{
								fsiz = 3;
							}
						}
					}
					if (fchr[2] == '\0' || fchr[1] == '\0' || fchr[0] == '\0')
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (fspecs[siz][nsiz] == 'l')
				{
					hlong++;
					nsiz++;
				}

				if (fspecs[siz][nsiz] == '0')
				{
					if (fspecs[siz][nsiz + 1] == '2')
					{
						nsiz += 2;
					}
				}

				if (fspecs[siz][nsiz] == 'i')
				{
					char ci[21]{ 0 };

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
						inchr[at_inchr] = ci[sloc];
						at_inchr++;
					}
				}
				else if (fspecs[siz][nsiz] == 'u')
				{
					char ci[21]{ 0 };

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
						inchr[at_inchr] = ci[sloc];
						at_inchr++;
					}
				}
				else if (fspecs[siz][nsiz] == 'f')
				{
					double inv = va_arg(args, double);
					float ninv = (float)inv;
					char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
					{
						inchr[at_inchr] = ci[sloc];
						at_inchr++;
					}
				}
				else if (fspecs[siz][nsiz] == 'd')
				{
					char ci[64]{ 0 };

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
						inchr[at_inchr] = ci[sloc];
						at_inchr++;
					}
				}
				else if (fspecs[siz][nsiz] == 's')
				{
					cchar* str = va_arg(args, cchar*);
					char cmp = '\0';
					sloc = 0;

					for (sloc = 0; sloc < BOT_STRLEN_MAX && at_inchr < in_siz; sloc++)
					{
						if (memcmp(&str[sloc], &cmp, 1))
						{
							inchr[at_inchr] = str[sloc];
							at_inchr++;
						}
						else
						{
							sloc = BOT_STRLEN_MAX;
						}
					}
				}
				else if (fspecs[siz][nsiz] == 'c')
				{
					sint inv_ = va_arg(args, sint);
					char inv = (char)inv_;

					if (at_inchr < in_siz)
					{
						inchr[at_inchr] = inv;
						at_inchr++;
					}
				}
				else if (fspecs[siz][nsiz] == 'X')
				{
					uchar inv_ = va_arg(args, uchar);
					const size_t usiz = (sizeof(inv_) * 2) + 1;

					if (usiz <= in_siz)
					{
						char ci[usiz]{ 0 };
						sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, sizeof(ci));

						for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
						{
							inchr[at_inchr] = ci[sloc];
							at_inchr++;
						}
					}
				}
				else if (fspecs[siz][nsiz] == 'v')
				{
					nsiz++;
					if (nsiz < fspecs[siz].length())
					{
						if (fspecs[siz][nsiz] == '.')
						{
							char sep[4]{ 0 };
							char fspec[4]{ 0 };
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
										fspec[nct] = fspecs[siz][nsiz];
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
										fspec[nct] = fspecs[siz][nsiz];
										nsiz++;
										nct = 3;
										break;
									}
									default:
									{
										fspec[nct] = fspecs[siz][nsiz];
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
									if (fspecs[siz][nsiz] != '.')
									{
										sep[x] = fspecs[siz][nsiz];
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
									std::vector<char>* inv = va_arg(args, std::vector<char>*);

									for (uint x = 0; x < inv->size(); x++)
									{
										if (at_inchr < in_siz)
										{
											inchr[at_inchr] = inv->at(x);
											at_inchr++;
										}
										if (slen)
										{
											for (sloc = 0; sloc < strlen(sep) && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = sep[sloc];
												at_inchr++;
											}
										}
									}
									break;
								}
								case 's':
								{
									/*when specifying %v.<type><sep>. type = 's' we use a vector of std::string instead of const char* */
									std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

									for (uint x = 0; x < strv->size(); x++)
									{
										for (sloc = 0; sloc < strv->at(x).length() && at_inchr < in_siz; sloc++)
										{
											inchr[at_inchr] = strv->at(x)[sloc];
											at_inchr++;
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
											{
												inchr[at_inchr] = sep[y];
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
										char ci[64]{ 0 };
										sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
										xc = bot_strchk(ci, 64);

										for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
										{
											inchr[at_inchr] = ci[sloc];
											at_inchr++;
										}
										if (slen)
										{
											for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
											{
												inchr[at_inchr] = sep[y];
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
											char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[64]{ 0 };
											sint xc = snprintf(ci, 64, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 64);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
											char ci[21]{ 0 };
											sint xc = snprintf(ci, 21, fspecs[siz].c_str(), fvec->at(x));
											xc = bot_strchk(ci, 21);

											for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;
											}
											if (slen)
											{
												for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
												{
													inchr[at_inchr] = sep[y];
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
									std::vector<uchar>* inv = va_arg(args, std::vector<uchar>*);
									
									for (uint x = 0; x < inv->size(); x++)
									{
										const size_t usiz = (sizeof(inv->at(x)) * 2) + 1;

										if (usiz + at_inchr <= in_siz)
										{
											char ci[usiz]{ 0 };
											sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv->at(x));
											xc = bot_strchk(ci, sizeof(ci));

											for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
											{
												inchr[at_inchr] = ci[sloc];
												at_inchr++;

												if (slen)
												{
													for (uint y = 0; y < strlen(sep) && at_inchr < in_siz; y++)
													{
														inchr[at_inchr] = sep[y];
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
				}
				else {}
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
					inchr[at_inchr] = fstr[locs[siz - 1]];
					locs[siz - 1]++;
					at_inchr++;
				}
			}
		}
		if (at_inchr < in_siz)
		{
			inchr[at_inchr] = '\0';
			ret = 0;
		}
		else
		{
			inchr[in_siz - 1] = '\0';
		}
	}
	else
	{
		uint siz = 0;

		while (siz < in_siz && siz < strsiz)
		{
			inchr[siz] = fstr[siz];
			siz++;
		}
		if (siz < in_siz)
		{
			inchr[siz] = '\0';
			ret = 0;
		}
		else
		{
			inchr[in_siz - 1] = '\0';
		}
	}
	return ret;
}

sint bot_sprintfs(std::string* str_ = 0, bool clear_str = false, cchar* fstr = 0, ...)
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
	char frm = '%';
	char spec = '.';

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
					if (fstr[siz + nsiz] == 'l' || fstr[siz + nsiz] == '-' || fstr[siz + nsiz] == '+' || fstr[siz + nsiz] == '0' || fstr[siz + nsiz] == '2' || fstr[siz + nsiz] == 'x' || fstr[siz + nsiz] == 'e' || fstr[siz + nsiz] == 'h' || fstr[siz + nsiz] == 'E')
					{
						if (!mustnum)
						{
							mustnum = true;
						}
						formspec.push_back(fstr[siz + nsiz]);
						nsiz++;
					}
					else if (fstr[siz + nsiz] == 'd' || fstr[siz + nsiz] == 'f' || fstr[siz + nsiz] == 'u' || fstr[siz + nsiz] == 'i' || fstr[siz + nsiz] == 'X')
					{
						formspec.push_back(fstr[siz + nsiz]);
						fspecs.push_back(formspec);
						locs.push_back(siz);
						formspec.clear();
						siz += nsiz;
						nsiz = strsiz;
					}
					else if (fstr[siz + nsiz] == 's' || fstr[siz + nsiz] == 'c')
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
					}
					else
					{
						return -3;
					}
				}
			}
		}
	}

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

				if (fspecs[siz][nsiz] == '.')
				{
					char fchr[3]{ 0 };
					nsiz++;

					for (uint fsiz = 0; fsiz < 3 && nsiz < fspecs[siz].length(); )
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
								cchar* msg = "";
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
							fchr[fsiz] = fspecs[siz][nsiz];
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							break;
						}
						}
					}
					if (fchr[2] == '\0' || fchr[1] == '\0' || fchr[0] == '\0')
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (fspecs[siz][nsiz] == 'l')
				{
					hlong++;
					nsiz++;
				}

				if (fspecs[siz][nsiz] == '0')
				{
					if (fspecs[siz][nsiz + 1] == '2')
					{
						nsiz += 2;
					}
				}

				if (fspecs[siz][nsiz] == 'i')
				{
					char ci[21]{ 0 };
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
				}
				else if (fspecs[siz][nsiz] == 'u')
				{
					sint xc = -1;
					char ci[21]{ 0 };

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
				}
				else if (fspecs[siz][nsiz] == 'f')
				{
					double inv = va_arg(args, double);
					float ninv = (float)inv;
					char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
				}
				else if (fspecs[siz][nsiz] == 'd')
				{
					double inv = va_arg(args, double);
					char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
				}
				else if (fspecs[siz][nsiz] == 's')
				{
					cchar* str = va_arg(args, cchar*);
					char cmp = '\0';
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
				}
				else if (fspecs[siz][nsiz] == 'c')
				{
					sint inv_ = va_arg(args, sint);
					char inv = (char)inv_;
					str_->push_back(inv);
				}
				else if (fspecs[siz][nsiz] == 'X')
				{
					uchar inv_ = va_arg(args, uchar);
					const size_t usiz = (sizeof(inv_) * 2) + 1;

					if ((usiz + str_->length()) <= (uint)BOT_STRLEN_MAX)
					{
						char ci[usiz]{ 0 };
						sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, sizeof(ci));
						str_->append(ci);
					}
				}
				else {}
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

sint bot_sprintfss(std::string* str_ = 0, bool clear_str = false, std::string* fstr_ = 0, ...)
{
	if (!str_ || !fstr_)
	{
		return -1;
	}

	if (!str_->empty() && clear_str)
	{
		str_->clear();
	}

	uint strsiz = fstr_->length();
	std::vector<std::string> fspecs;
	std::vector<uint> locs;
	std::string formspec;
	char frm = '%';
	char spec = '.';

	for (uint siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr_->at(siz), (void*)&frm, 1))
		{
			formspec.push_back(fstr_->at(siz));
			bool mustnum = false;

			for (uint nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr_->at(siz + nsiz), (void*)&spec, 1))
				{
					if (!mustnum)
					{
						mustnum = true;
					}

					formspec.push_back(fstr_->at(siz + nsiz));
					nsiz++;

					switch (fstr_->at(siz + nsiz))
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
						formspec.push_back(fstr_->at(siz + nsiz));
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
					if (fstr_->at(siz + nsiz) == 'l' || fstr_->at(siz + nsiz) == '-' || fstr_->at(siz + nsiz) == '+' || fstr_->at(siz + nsiz) == '0' || fstr_->at(siz + nsiz) == '2' || fstr_->at(siz + nsiz) == 'x' || fstr_->at(siz + nsiz) == 'e' || fstr_->at(siz + nsiz) == 'h' || fstr_->at(siz + nsiz) == 'E')
					{
						if (!mustnum)
						{
							mustnum = true;
						}
						formspec.push_back(fstr_->at(siz + nsiz));
						nsiz++;
					}
					else if (fstr_->at(siz + nsiz) == 'd' || fstr_->at(siz + nsiz) == 'f' || fstr_->at(siz + nsiz) == 'u' || fstr_->at(siz + nsiz) == 'i' || fstr_->at(siz + nsiz) == 'X')
					{
						formspec.push_back(fstr_->at(siz + nsiz));
						fspecs.push_back(formspec);
						locs.push_back(siz);
						formspec.clear();
						siz += nsiz;
						nsiz = strsiz;
					}
					else if (fstr_->at(siz + nsiz) == 's' || fstr_->at(siz + nsiz) == 'c')
					{
						if (!mustnum)
						{
							formspec.push_back(fstr_->at(siz + nsiz));
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
					}
					else
					{
						return -3;
					}
				}
			}
		}
	}

	if (!fspecs.empty())
	{
		uint siz = 0;
		va_list args;
		va_start(args, fstr_);

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
				str_->push_back(fstr_->at(sloc));
				sloc++;
			}

			if (fspecs[siz].length() > 1)
			{
				sint isiz = 0;
				uint nsiz = 1;

				if (fspecs[siz][nsiz] == '.')
				{
					char fchr[3]{ 0 };
					nsiz++;

					for (uint fsiz = 0; fsiz < 3 && nsiz < fspecs[siz].length(); )
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
								cchar* msg = "";
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
							fchr[fsiz] = fspecs[siz][nsiz];
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							break;
						}
						}
					}
					if (fchr[2] == '\0' || fchr[1] == '\0' || fchr[0] == '\0')
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (fspecs[siz][nsiz] == 'l')
				{
					hlong++;
					nsiz++;
				}

				if (fspecs[siz][nsiz] == '0')
				{
					if (fspecs[siz][nsiz + 1] == '2')
					{
						nsiz += 2;
					}
				}

				if (fspecs[siz][nsiz] == 'i')
				{
					char ci[21]{ 0 };
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
				}
				else if (fspecs[siz][nsiz] == 'u')
				{
					sint xc = -1;
					char ci[21]{ 0 };

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
				}
				else if (fspecs[siz][nsiz] == 'f')
				{
					double inv = va_arg(args, double);
					float ninv = (float)inv;
					char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
				}
				else if (fspecs[siz][nsiz] == 'd')
				{
					double inv = va_arg(args, double);
					char ci[64]{ 0 };
					sint xc = snprintf(ci, 64, fspecs[siz].c_str(), inv);
					xc = bot_strchk(ci, 64);

					if ((str_->length() + strlen(ci)) < (uint)BOT_STRLEN_MAX)
					{
						str_->append(ci);
					}
				}
				else if (fspecs[siz][nsiz] == 's')
				{
					cchar* str = va_arg(args, cchar*);
					char cmp = '\0';
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
				}
				else if (fspecs[siz][nsiz] == 'c')
				{
					sint inv_ = va_arg(args, sint);
					char inv = (char)inv_;
					str_->push_back(inv);
				}
				else if (fspecs[siz][nsiz] == 'X')
				{
					uchar inv_ = va_arg(args, uchar);
					const size_t usiz = (sizeof(inv_) * 2) + 1;

					if ((usiz + str_->length()) <= (uint)BOT_STRLEN_MAX)
					{
						char ci[usiz]{ 0 };
						sint xc = snprintf(ci, sizeof(ci), fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, sizeof(ci));
						str_->append(ci);
					}
				}
				else {}
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
					str_->push_back(fstr_->at(locs[siz - 1]));
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
			str_->append(fstr_->c_str());
		}
		return 0;
	}
	return -1;
}

errno_t bot_itoa(sint i, char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%i", i); }
errno_t bot_itoa(slint i, char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%li", i); }
errno_t bot_itoa(sllint i, char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lli", i); }
errno_t bot_itoa(uint i, char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%u", i); }
errno_t bot_itoa(ulint i, char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lu", i); }
errno_t bot_itoa(ullint i, char in_chr[] = 0, size_t in_siz = 0, sint radix = 10) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%llu", i); }

/* To do list: 
Xupdate void functions to ints for return call options **and one day use those xcs
Xbuild an alter table fix in DBVerify
Xbuild comparedatesi
Xget ns from last second
Xchange last_access to date ans ns
sortaXlet new alter table func fix last_access
Xchange Client to vector of clients and logs to vector of logs in LITEBot()
Xmutex funcs for access to those vecs
mutex funcs for access to globals in the public area
implement savepoints n rollbacks... or not, these are pointless.  adding a list of our last transactions in the db would serve the purpose much better 3 rows: id transaction completed; check last entry for completed, iterate statements with Get/analyze to look for the one that did not finish...  what about backups? add a backup routine to maint funcs
sortaX prevent deadlocks - current mtx scheme defers to lowest db type, or should at least.  checks for a req on a db we already have and prevents double locking then while waiting for a mtx to open a thread checks its other db h_mtxs for threads requesting a lock on h_mtxs this thread holds and keeps or defers and unlocks, then acquires dropped h_mtxs again.  this prevents mtx locks but multiple updates could still be made to the same row with gets acquired before the first intended update commits.  this might be a flaw in our update scheme which we see as either appending new data or replacing old data.  what else could we do here?  how do we want to handle differing values in cols vs. struct elements?
SeparateSymbolsI or II needs an Add/Update for Code, and a pattern get/compare/add.  Code Maint can add basic idents.  
We might need to return to using dbcommits thread, and running maint functions after each update
If i use sep funcs I Ii III IV in sep/build sql funcs i can add idents presuming we are using sql, but this might also lead to our current prob in basic idents + lencstrI of providing too much info without enough discernible context. if we build no idents and let a db maint routine determine context we would not run across invalid operators like \ for a long time.  
add a machine status struct and nec funcs.
one million return calls.
32 bit max 2,147,483,647
*/
struct status_struct
{
	
};

struct task_struct
{
	
};

struct st_mem_struct
{
	
};

struct lt_mem_struct
{
	
};

typedef struct bot_carr_2
{
	char carr[2]{ 0 };
	const size_t siz = 2;
}carr_2;

typedef struct bot_carr_3
{
	char carr[3]{ 0 };
	const size_t siz = 3;
}carr_3;

typedef struct bot_carr_4
{
	char carr[4]{ 0 };
	const size_t siz = 4;
}carr_4;

typedef struct bot_carr_8
{
	char carr[8]{ 0 };
	const size_t siz = 8;
}carr_8;

typedef struct bot_carr_16
{
	char carr[16]{ 0 };
	const size_t siz = 16;
}carr_16;

typedef struct bot_carr_32
{
	char carr[32]{ 0 };
	const size_t siz = 32;
}carr_32;

typedef struct bot_carr_64
{
	char carr[64]{ 0 };
	const size_t siz = 64;
}carr_64;

typedef struct bot_carr_128
{
	char carr[128]{ 0 };
	const size_t siz = 128;
}carr_128;

typedef struct bot_carr_256
{
	char carr[256]{ 0 };
	const size_t siz = 256;
}carr_256;

typedef struct bot_carr_512
{
	char carr[512]{ 0 };
	const size_t siz = 512;
}carr_512;

typedef struct bot_carr_1024
{
	char carr[1024]{ 0 };
	const size_t siz = 1024;
}carr_1024;

typedef struct bot_carr_2048
{
	char carr[2048]{ 0 };
	const size_t siz = 2048;
}carr_2048;

typedef struct bot_carr_4096
{
	char carr[4096]{ 0 };
	const size_t siz = 4096;
}carr_4096;

typedef struct bot_carr_8192
{
	char carr[8192]{ 0 };
	const size_t siz = 8192;
}carr_8192;

typedef struct bot_carr_16384
{
	char carr[16384]{ 0 };
	const size_t siz = 16384;
}carr_16384;

typedef struct bot_carr_32768
{
	char carr[32768]{ 0 };
	const size_t siz = 32768;
}carr_32768;

typedef struct bot_ucar_2
{
	uchar carr[2]{ 0 };
	const size_t siz = 2;
}ucar_2;

typedef struct bot_ucar_4
{
	uchar carr[4]{ 0 };
	const size_t siz = 4;
}ucar_4;

typedef struct bot_ucar_8
{
	uchar carr[8]{ 0 };
	const size_t siz = 8;
}ucar_8;

typedef struct bot_ucar_16
{
	uchar carr[16]{ 0 };
	const size_t siz = 16;
}ucar_16;

typedef struct bot_ucar_32
{
	uchar carr[32]{ 0 };
	const size_t siz = 32;
}ucar_32;

typedef struct bot_ucar_64
{
	uchar carr[64]{ 0 };
	const size_t siz = 64;
}ucar_64;

typedef struct bot_ucar_128
{
	uchar carr[128]{ 0 };
	const size_t siz = 128;
}ucar_128;

typedef struct bot_ucar_256
{
	uchar carr[256]{ 0 };
	const size_t siz = 256;
}ucar_256;

typedef struct bot_ucar_512
{
	uchar carr[512]{ 0 };
	const size_t siz = 512;
}ucar_512;

typedef struct bot_ucar_1024
{
	char carr[1024]{ 0 };
	const size_t siz = 1024;
}ucar_1024;

typedef struct bot_ucar_2048
{
	uchar carr[2048]{ 0 };
	const size_t siz = 2048;
}ucar_2048;

typedef struct bot_ucar_4096
{
	uchar carr[4096]{ 0 };
	const size_t siz = 4096;
}ucar_4096;

typedef struct bot_ucar_8192
{
	uchar carr[8192]{ 0 };
	const size_t siz = 8192;
}ucar_8192;

typedef struct bot_ucar_16384
{
	uchar carr[16384]{ 0 };
	const size_t siz = 16384;
}ucar_16384;

typedef struct bot_ucar_32768
{
	uchar carr[32768]{ 0 };
	const size_t siz = 32768;
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
	MTX_MAX = 14
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

typedef struct col_struct
{
	uint type;
	std::string name;
	std::vector<std::vector<uchar>> rows;

	col_struct(sint ntype = 0, cchar* nname = "") { type = ntype; name.append(nname); };

}COL_STRUCT;

class bot_tbl
{

public:

	std::string name;
	std::vector<col_struct> cvec;

	sint cmpto(uchar uto[] = 0, sint col = -1, sint row = -1)
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
	sint cmpto(cchar uto[] = 0, sint col = -1, sint row = -1)
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
						if (memcmp(&cvec[col].rows[row][nsiz], (uchar*)&uto[nsiz], 1))
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
						if (memcmp(&cvec[col].rows[row][nsiz], (uchar*)&uto[nsiz], 1))
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
						if (memcmp(&cvec[col].rows[row][nsiz], (uchar*)&uto[nsiz], 1))
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
						if (memcmp(&cvec[col].rows[row][nsiz], (uchar*)&uto[nsiz], 1))
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
			return-1;
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
				siz = cvec.size();
			}
			siz++;
		}
		if (siz == cvec.size())
		{
			std::vector<uchar> ncar;
			while (val->rows.size() < csiz)
			{
				val->rows.push_back(ncar);
			}
			cvec.push_back(*val);
		}
	}
	sint AddRow()
	{
		if (!cvec.empty())
		{
			std::vector<uchar> vec;
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
	}

	bot_tbl(cchar* nname = "") { name.append(nname); };

	private:

};

enum stmt_mems
{
	BOT_STMT_MAINT = 0,
	BOT_STMT_STMT = 1,
	BOT_STMT_TTYPE = 2,
	BOT_STMT_CTYPES = 3,
	BOT_STMT_TABLES = 4,
	BOT_STMT_DBNAME = 5,
	BOT_STMT_DBALIAS = 6,
	BOT_STMT_OPTS = 7,
	BOT_STMT_COLS = 8,
	BOT_STMT_VALS = 9,
	BOT_STMT_CONDS = 10,
	BOT_STMT_LID = 11,
	BOT_STMT_AN = 12,
	BOT_STMT_MAX = 13
};

class BOT_STMT
{

public:

	bool maint;
	bool an;
	sint lid;
	sint it_type;
	std::string stmt;
	std::vector<sint> ic_types;
	std::vector<std::string> tables;
	std::string dbname;
	std::string dbalias;
	std::vector<std::vector<size_t>> opts{ BOT_STMT_OPTSLIM };
	std::vector<std::string> cols;
	std::vector<std::string> vals;
	std::vector<std::string> conds;

	void Clear()
	{
		an = false; maint = false;
		lid = it_type = -1;

		if (!stmt.empty())
		{
			stmt.clear();
		}
		if (!tables.empty())
		{
			tables.clear();
		}
		if (!ic_types.empty())
		{
			ic_types.clear();
		}
		if (!dbname.empty())
		{
			dbname.clear();
		}
		if (!dbalias.empty())
		{
			dbalias.clear();
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
		
		for (size_t o = 0; o < opts.size(); o++)
		{
			if (!opts[o].empty())
			{
				opts[o].clear();
			}
		}
	}
	void Renew(bool nmaint = false, sint nit_type = -1, cchar* nname = "")
	{
		Clear();
		maint = nmaint;
		it_type = nit_type;
		size_t siz = strlen(nname);
		
		if (siz && siz < BOT_STRLEN_MAX)
		{
			dbname.append(nname);
		}
	}

	sint AddDB(cchar* dname = "")
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
	sint AddCont(cchar* cname = "", sint ctype = -1)
	{
		sint ret = -1;

		if (cname)
		{
			if (strlen(cname) < BOT_STRLEN_MAX)
			{
				size_t siz = 0;

				while (siz < tables.size())
				{
					if (!strcmp(tables[siz].c_str(), cname))
					{
						return (sint)siz;
					}
					siz++;
				}
				if (siz == tables.size())
				{
					std::string cont;
					cont.append(cname);
					tables.push_back(cont);
					ic_types.push_back(ctype);
					return (sint)siz;
				}
			}
		}
		return ret;
	}
	sint AddCol(cchar* col_n = "", cchar* val = "")
	{
		sint ret = -1;

		if (col_n)
		{
			size_t nlen = strlen(col_n);
			size_t vlen = strlen(val);

			if ((nlen < BOT_STRLEN_MAX) && (vlen < BOT_STRLEN_MAX))
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
				if (siz == cols.size())
				{
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

	BOT_STMT(bool nmaint = false, sint nit_type = -1, cchar* nname = "") { an = false; maint = nmaint; lid = -1; it_type = nit_type; size_t siz = strlen(nname); if (siz && siz < BOT_STRLEN_MAX) { dbname.append(nname); } };
	
private:

};

class DB_CONN
{
public:

	_mtx mtx;
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
	void Renew(DB_CONN* val_ = 0) { Clear(); mlid = val_->mlid; lid = val_->lid; omode = val_->omode; name.append(val_->name.c_str()); t = val_->t; att.swap(val_->att); exists = val_->exists; }
	void Renew(cchar* nname = "", sint nmlid = -1, sint nomode = -1, sint nfid = -1) { Clear(); mlid = nmlid; lid = nfid; omode = nomode; size_t siz = strlen(nname); if (siz && siz < BOT_STRLEN_MAX) { name.append(nname); } t = std::chrono::steady_clock::now(); }

	DB_CONN(cchar* nname = "", sint nmlid = -1, sint nomode = -1, sint nfid = -1) { exists = -1; mlid = nmlid; lid = nfid; in_use = o_com = persist = close_me = false; omode = nomode; size_t siz = strlen(nname); if (siz && siz < BOT_STRLEN_MAX) { name.append(nname); } t = std::chrono::steady_clock::now(); };

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

	void Clear() { connected = false; file_ele = omode = fcon = c_by = lid = exists = -1; if (!name.empty()) { name.clear(); } if (!tables.empty()) { tables.clear(); } if (!columns.empty()) { columns.clear(); } }
	void Renew(BOT_DB* val_ = 0) { Clear(); file_ele = val_->file_ele; lid = val_->lid; fcon = val_->fcon; type = val_->type; exists = val_->exists; c_by = val_->c_by; omode = val_->omode; uint len = (uint)val_->name.length(); if (len && len < 128) { name.append(val_->name.c_str()); } for (uint x = 0; x < val_->tables.size(); x++) { tables.push_back(val_->tables[x]); } for (uint x = 0; x < val_->columns.size(); x++) { columns.push_back(val_->columns[x]); } }

	BOT_DB(cchar* nstr = "", sint ntype = -1, sint nomode = -1)
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
			struct _stat filestats;
			exists = _stat(str.c_str(), &filestats);
#else
			struct stat filestats;
			exists = stat(str.c_str(), &filestats);
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

	void Clear() { connected = false; file_ele = omode = fcon = c_by = lid = exists = -1; if (!name.empty()) { name.clear(); } tsiz = 0; csiz = 0; }
	void Renew(BOT_DB_M* val_ = 0) { Clear(); lid = val_->lid; connected = val_->connected; file_ele = val_->file_ele; fcon = val_->fcon; type = val_->type; exists = val_->exists; c_by = val_->c_by; omode = val_->omode; name.append(val_->name.c_str()); tsiz = val_->tsiz; csiz = val_->csiz; }
	void Renew(BOT_DB* val_ = 0) { Clear(); lid = val_->lid; connected = val_->connected; file_ele = val_->file_ele; fcon = val_->fcon; type = val_->type; exists = val_->exists; c_by = val_->c_by; omode = val_->omode; name.append(val_->name.c_str()); tsiz = val_->tables.size(); csiz = val_->columns.size(); }

	sint Update(BOT_DB* val_ = 0)
	{
		fcon = val_->fcon;

		if (!name.empty())
		{
			name.clear();
		}
		
		if (strlen(val_->name.c_str()) < 128)
		{
			name.append(val_->name.c_str());
		}
		type = val_->type;
		lid = val_->lid;
		tsiz = val_->tables.size();
		csiz = val_->columns.size();
		exists = val_->exists;
		c_by = val_->c_by;
		file_ele = val_->file_ele;
		connected = val_->connected;
		return 0;
	}

	BOT_DB_M(cchar* nstr = "", sint ntype = -1, sint nomode = -1, sint nlid = -1, size_t ntsiz = 0, size_t ncsiz = 0, sint nexist = -1, sint nc_by = -1)
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
			struct _stat filestats;
			exists = _stat(str.c_str(), &filestats);
#else
			struct stat filestats;
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
	sint lok;
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

	void Clear() { lok = -1; nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); }
	void Renew(BOT_CLIENT* nc = 0) { if (!nc) { return; } Clear(); login_name.append(nc->login_name.c_str()); name.append(nc->name.c_str()); lastlogin.append(nc->lastlogin.c_str()); last_failed_login.append(nc->last_failed_login.c_str()); lastexchange.append(nc->lastexchange.c_str()); }

	BOT_CLIENT(cchar* nstr = "") { lok = -1; nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); size_t siz = strlen(nstr); if (siz < 128) { name.append(nstr); if (siz) { nameset = true; } } };

private:

};

class BOT_CLIENT_M
{
public:

	sint lok;
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

	void Clear() { lok = -1; nameset = loggedin = changename = updatepriv = updatelogin = false; totallogins = failed_logins = priv = 0; lid = c_by = -1; name.clear(); login_name.clear(); lastlogin.clear(); logindate.clear(); last_failed_login.clear(); lastexchange.clear(); }
	void Renew(BOT_CLIENT_M* nc = 0) { if (!nc) { return; } Clear(); login_name.append(nc->login_name.c_str()); name.append(nc->name.c_str()); lastlogin.append(nc->lastlogin.c_str()); last_failed_login.append(nc->last_failed_login.c_str()); lastexchange.append(nc->lastexchange.c_str()); }
	void Renew(BOT_CLIENT* nc = 0) { if (!nc) { return; } Clear(); login_name.append(nc->login_name.c_str()); name.append(nc->name.c_str()); lastlogin.append(nc->lastlogin.c_str()); last_failed_login.append(nc->last_failed_login.c_str()); lastexchange.append(nc->lastexchange.c_str()); }


	sint Update(BOT_CLIENT* val_ = 0)
	{
		lok = -1;
		nameset = val_->nameset;
		loggedin = val_->loggedin;
		changename = val_->changename;
		updatepriv = val_->updatepriv;
		updatelogin = val_->updatelogin;
		totallogins = val_->totallogins;
		failed_logins = val_->failed_logins;
		priv = val_->priv;
		lid = val_->lid;

		if (!name.empty())
		{
			name.clear();
		}
		size_t siz = strlen(val_->name.c_str());
		if (siz < 128)
		{
			name.append(val_->name.c_str());
		}

		if (!login_name.empty())
		{
			login_name.clear();
		}
		siz = strlen(val_->login_name.c_str());
		if (siz < 128)
		{
			login_name.append(val_->login_name.c_str());
		}

		if (!lastlogin.empty())
		{
			lastlogin.clear();
		}
		siz = strlen(val_->lastlogin.c_str());
		if (siz < 128)
		{
			lastlogin.append(val_->lastlogin.c_str());
		}

		if (!logindate.empty())
		{
			logindate.clear();
		}
		siz = strlen(val_->logindate.c_str());
		if (siz < 128)
		{
			logindate.append(val_->logindate.c_str());
		}

		if (!last_failed_login.empty())
		{
			last_failed_login.clear();
		}
		siz = strlen(val_->last_failed_login.c_str());
		if (siz < 128)
		{
			last_failed_login.append(val_->last_failed_login.c_str());
		}

		if (!lastexchange.empty())
		{
			lastexchange.clear();
		}
		siz = strlen(val_->lastexchange.c_str());
		if (siz < 128)
		{
			lastexchange.append(val_->lastexchange.c_str());
		}
		
		c_by = val_->c_by;
		return 0;
	}

	BOT_CLIENT_M(cchar* nstr = "",
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
		cchar* nlogin_name = "",
		cchar* nlastlogin = "",
		cchar* nlogindate = "",
		cchar* nlast_failed_login = "",
		cchar* nlastexchange = "")
	{
		lok = -1;
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

	BOTCOMMAND(cchar* ncmd = "", sint ncmd_id = -1) { id = -1; cmd_id = ncmd_id; priv = 0; cmd.append(ncmd); };

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
	sint lok;
	sint lid;
	sint type;
	sint c_by;
	sint file_ele;
	bool started;
	std::string logtitle;
	std::string startdate;
	std::vector<std::string> log_q;

	void Clear() { logtitle.clear(); startdate.clear(); log_q.clear(); started = false; file_ele = lok = lid = type = c_by = -1; }
	void Renew(BOT_LOGDET* val_ = 0) { if (!val_) { return; } Clear(); logtitle.append(val_->logtitle.c_str()); startdate.append(val_->startdate.c_str()); log_q.swap(val_->log_q); file_ele = val_->file_ele; lok = val_->lok; type = val_->type; c_by = val_->c_by; }

	BOT_LOGDET(cchar* titl = "", cchar* dat = "", sint ntype = -1, sint nc_by = -1) { file_ele = lok = type = -1; started = false; if (ntype > -1) { type = ntype; } if (strlen(titl) < 256) { logtitle.append(titl); } if (strlen(dat) < 64) { startdate.append(dat); } c_by = nc_by; };

private:

};

class BOT_LOGDET_M
{
public:

	sint lok;
	sint lid;
	sint type;
	sint c_by;
	sint file_ele;
	bool started;
	std::string logtitle;
	std::string startdate;
	size_t lsiz;

	void Clear() { logtitle.clear(); startdate.clear(); lsiz = 0; started = false; file_ele = lok = lid = type = c_by = -1; }
	void Renew(BOT_LOGDET_M* val_ = 0) { if (!val_) { return; } Clear(); file_ele = val_->file_ele; logtitle.append(val_->logtitle.c_str()); startdate.append(val_->startdate.c_str()); lsiz = val_->lsiz; lok = val_->lok; type = val_->type; c_by = val_->c_by; lid = val_->lid; }
	void Renew(BOT_LOGDET* val_ = 0) { if (!val_) { return; } Clear(); file_ele = val_->file_ele; logtitle.append(val_->logtitle.c_str()); startdate.append(val_->startdate.c_str()); lsiz = val_->log_q.size(); lok = val_->lok; type = val_->type; c_by = val_->c_by; lid = val_->lid; }

	sint Update(BOT_LOGDET* val_ = 0)
	{
		lok = -1;
		type = val_->lid;
		started = val_->started;

		if (!logtitle.empty())
		{
			logtitle.clear();
		}
		
		if (strlen(val_->logtitle.c_str()) < 256)
		{
			logtitle.append(val_->logtitle.c_str());
		}

		if (!startdate.empty())
		{
			startdate.clear();
		}
		if (strlen(val_->startdate.c_str()) < 64)
		{
			startdate.append(val_->startdate.c_str());
		}
		lsiz = val_->log_q.size();
		c_by = val_->c_by;
		lid = val_->lid;
		file_ele = val_->file_ele;
		return 0;
	}

	BOT_LOGDET_M(cchar* titl = "", cchar* dat = "", sint ntype = -1, sint lid = -1, bool nstrt = false, sint nc_by = -1) { file_ele = lok = type = -1; started = nstrt; if (ntype > -1) { type = ntype; } if (strlen(titl) < 256) { logtitle.append(titl); } if (strlen(dat) < 64) { startdate.append(dat); } lsiz = 0; c_by = nc_by; };

private:

};

typedef struct hist_p
{
	uchar sym;
	uint ct;

	hist_p(uchar* nsym = 0, uint nct = 0) { sym = BOT_BOUND_CHR; ct = nct; if (nsym) { memcpy(&sym, &nsym[0], 1); } };

}HIST_P;

typedef struct hist_f
{
	uchar sym;
	uint ct;

	hist_f(uchar* nsym = 0, uint nct = 0) { sym = BOT_BOUND_CHR; ct = nct; if (nsym) { memcpy(&sym, &nsym[0], 1); } };

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
	uchar sym;
	bool ud_encodings;
	std::vector<sint> encodings;
	bool ud_constituent_to;
	std::vector<std::vector<std::vector<uchar>> > constituent_to;
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

	void Clear() { encodings.clear(); constituent_to.clear(); history_preceeding.clear(); history_following.clear(); id = last_maintained = last_modified = last_maintained_ns = last_modified_ns = -1; ud_id = ud_sym = ud_encodings = ud_constituent_to = ud_history_preceeding = ud_history_following = ud_last_modified = ud_last_maintained = ud_last_maintained_ns = ud_last_maintained_ns = false; }
	void Renew(MICSYM* val_ = 0) { Clear(); id = val_->id; memcpy((void*)&sym, (void*)&val_->sym, sizeof(sym)); encodings.swap(val_->encodings); constituent_to.swap(val_->constituent_to); history_preceeding.swap(val_->history_preceeding); history_following.swap(val_->history_following); }
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
				std::vector<std::vector<std::vector<uchar>> > alterv;
				for (size_t siz = 0; siz < constituent_to.size(); siz++)
				{
					std::vector<std::vector<uchar>> xvec;
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

	sint AddEnc(sint enc = -1, std::vector<std::vector<uchar>>* cto_ = 0, std::vector<HIST_P>* nhp = 0, std::vector<HIST_F>* nhf = 0)
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
							std::vector<std::vector<uchar>> vec;
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
				std::vector<std::vector<uchar>> vec;
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
	
	
	MICSYM(uchar* nsym = 0, sint nencoding = -1, std::vector<std::vector<uchar>>* ncto_ = 0, std::vector<HIST_P>* hp = 0, std::vector<HIST_F>* hf = 0) { ud_id = ud_history_following = ud_history_preceeding = ud_last_maintained = ud_last_modified = ud_last_maintained_ns = ud_last_modified_ns = false; last_maintained = last_modified = last_maintained_ns = last_modified_ns = id = loc = -1; constituent_to.clear(); encodings.clear(); history_following.clear(); history_preceeding.clear(); sym = BOT_BOUND_CHR; if (nsym) { memcpy(&sym, &nsym[0], 1); } if (nencoding > -1) { AddEnc(nencoding, ncto_, hp, hf); } };

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
	std::vector<std::vector<uchar>> alters;
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

	void Clear() { cons.clear(); pair_sym.clear(); usages.clear(); used.clear(); alters.clear(); history_preceeding.clear(); history_following.clear(); id = last_maintained = last_modified = last_maintained_ns = last_modified_ns = -1; ud_id = ud_cons = ud_pair_sym = ud_usages = ud_used = ud_alters = ud_history_preceeding = ud_history_following = ud_last_modified = ud_last_maintained = ud_last_maintained_ns = ud_last_maintained_ns = false; }
	void Renew(MACSYM* val_ = 0) { Clear(); id = val_->id; cons.swap(val_->cons); pair_sym.swap(val_->pair_sym); usages.swap(val_->usages); used.swap(val_->used); alters.swap(val_->alters); history_preceeding.swap(val_->history_preceeding); history_following.swap(val_->history_following); }

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
				std::vector<std::vector<uchar>> alterv;
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
					std::vector<std::vector<uchar>> alterv;
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

	sint RenderCons(uchar sym[], sint encoding = -1)
	{
		if (!sym || encoding < 0)
		{
			return -1;
		}
		sint ssiz = (sint)sizeof(sym);

		if (ssiz)
		{
			std::vector<uchar> ftvec;

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
					uchar xcar = BOT_BOUND_CHR;
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
					uchar xcar = BOT_BOUND_CHR;
					HIST_F hp(&xcar, 1);
					hf_v.push_back(hp);
				}

				std::vector<std::vector<uchar>> nftvec;
				nftvec.push_back(ftvec);
				MICSYM nss(&sym[rc], encoding, &nftvec, &hp_v, &hf_v);
				nss.AddEnc(encoding, &nftvec, &hp_v, &hf_v);
				cons.push_back(nss);
			}
			return 0;
		}
		return -1;
	}

	MACSYM(sint nua = -1, uchar ncons[] = 0, sint nencoding = -1, std::vector<HIST_PV>* nhp_v = 0, std::vector<HIST_FV>* nhf_v = 0) { ud_id = ud_usages = ud_cons = ud_pair_sym = ud_history_following = ud_history_preceeding = ud_last_maintained = ud_last_modified = ud_last_maintained_ns = ud_last_modified_ns = ud_used = ud_alters = false; used_as = nua; id = -1; if (ncons) { RenderCons(ncons, nencoding); } if (nua > -1) { AddUse(nua, 1, nhp_v, nhf_v); } };

private:

};

typedef struct bot_fstate
{
	sllint e_loc;
	sllint oa_loc;
	sllint ia_loc;
	sint omode;

	bot_fstate(sint no_mode = -1, sllint ne_loc = -1, sllint noa_loc = -1, sllint nia_loc = -1) { omode = no_mode; e_loc = ne_loc; oa_loc = noa_loc; ia_loc = nia_loc; };

}BOT_FSTATE;

enum file_mems
{
	BOT_FS_NAME = 0,
	BOT_FS_FT = 1,
	BOT_FS_FP = 2,
	BOT_FS_STRVEC = 3,
	BOT_FS_OMODE = 4,
	BOT_FS_STATS = 5,
	BOT_FS_ID = 6,
	BOT_FS_E = 8,
	BOT_FS_CBY = 9,
	BOT_FS_CM = 10,
	BOT_FS_FCON = 11,
	BOT_FS_MAX = 12
};

class BOT_FILE
{
public:
	std::string name;
	std::string path;
	std::string type;
	std::vector<std::string> strvec;
	sint omode;
	sint fcon;
#ifdef _WIN32
	struct _stat filestats;
#else
	struct stat filestats;
#endif
	sint lid;
	sint exists;
	sint c_by;
	sint cm;

	void ClearStats() { filestats.st_atime = 0; filestats.st_ctime = 0; filestats.st_dev = 0; filestats.st_ino = 0; filestats.st_mode = 0; filestats.st_mtime = 0; filestats.st_nlink = 0; filestats.st_rdev = 0; filestats.st_size = 0; filestats.st_uid = 0; }
	void Clear() { ClearStats(); cm = lid = exists = c_by = omode = fcon = -1; if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } if (!strvec.empty()) { strvec.clear(); } }
	void Renew(BOT_FILE* nf_ = 0)
	{
		if (nf_)
		{
			Clear();

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

			if (!strvec.empty())
			{
				for (size_t y = 0; y < nf_->strvec.size() && y < BOTVEC_LIM; y++)
				{
					strvec.push_back(nf_->strvec[y]);
				}
			}
			filestats = nf_->filestats;
			omode = nf_->omode;
			c_by = nf_->c_by;
			exists = nf_->exists;
			lid = nf_->lid;
			cm = nf_->cm;
		}
	}
#ifdef _WIN32
	void Renew(cchar* nm_ = 0, cchar* nt_ = 0, cchar*np_ = 0, sint nc_by = -1, sint nomode = -1, sint nexists = -1, sint ncm = -1, sint nlid = -1, struct _stat* nstat = 0)
#else
	void Renew(cchar* nm_ = 0, cchar* nt_ = 0, cchar*np_ = 0, sint nc_by = -1, sint nomode = -1, sint nexists = -1, sint ncm = -1, sint nlid = -1, struct stat* nstat = 0)
#endif
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
		lid = nlid;
		cm = ncm;
		omode = nomode;
		c_by = nc_by;
		exists = nexists;

		if (nstat)
		{
			filestats = *nstat;
		}
	}

	BOT_FILE(cchar* nfn = "", cchar* nft = "", cchar* nfp = "", sint nc_by = -1, sint nomode = -1)
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
		omode = nomode;
		cm = lid = fcon = -1;

		if (strlen(nfn))
		{
			std::string str;
			str.append(nfp);
			str.append(nfn);
			str.append(nft);
#ifdef _WIN32
			exists = _stat(str.c_str(), &filestats);
#else
			exists = stat(str.c_str(), &filestats);
#endif
		}
		c_by = nc_by; 
	};

private:
};

class BOT_FILE_M
{
public:

	std::string name;
	std::string path;
	std::string type;
	size_t strsiz;
	sint omode;
	sint fcon;
#ifdef _WIN32
	struct _stat filestats;
#else
	struct stat filestats;
#endif
	sint lid;
	sint exists;
	sint c_by;
	sint cm;

	void ClearStats() { filestats.st_atime = 0; filestats.st_ctime = 0; filestats.st_dev = 0; filestats.st_ino = 0; filestats.st_mode = 0; filestats.st_mtime = 0; filestats.st_nlink = 0; filestats.st_rdev = 0; filestats.st_size = 0; filestats.st_uid = 0; }
	void Clear() { ClearStats(); cm = lid = exists = c_by = omode = fcon = -1; if (!path.empty()) { path.clear(); } if (!type.empty()) { type.clear(); } if (!name.empty()) { name.clear(); } strsiz = 0; }
	void Renew(BOT_FILE_M* nf_ = 0)
	{
		if (nf_)
		{
			Clear();

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

			strsiz = nf_->strsiz;
			filestats = nf_->filestats;
			omode = nf_->omode;
			c_by = nf_->c_by;
			exists = nf_->exists;
			lid = nf_->lid;
			cm = nf_->cm;
		}
	}
	void Renew(BOT_FILE* nf_ = 0)
	{
		if (nf_)
		{
			Clear();

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

			strsiz = nf_->strvec.size();
			filestats = nf_->filestats;
			omode = nf_->omode;
			c_by = nf_->c_by;
			exists = nf_->exists;
			lid = nf_->lid;
			cm = nf_->cm;
		}
	}
#ifdef _WIN32
	void Renew(cchar* nm_ = 0, cchar* nt_ = 0, cchar*np_ = 0, sint nc_by = -1, sint nomode = -1, sint nexists = -1, sint ncm = -1, sint nlid = -1, struct _stat* nstat = 0)
#else
	void Renew(cchar* nm_ = 0, cchar* nt_ = 0, cchar*np_ = 0, sint nc_by = -1, sint nomode = -1, sint nexists = -1, sint ncm = -1, sint nlid = -1, struct stat* nstat = 0)
#endif
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
		lid = nlid;
		cm = ncm;
		omode = nomode;
		c_by = nc_by;
		exists = nexists;

		if (nstat)
		{
			filestats = *nstat;
		}
	}
	sint Update(BOT_FILE* val_ = 0)
	{
		omode = val_->omode;
		fcon = val_->fcon;

		if (!name.empty())
		{
			name.clear();
		}

		if (!type.empty())
		{
			type.clear();
		}

		if (!path.empty())
		{
			path.clear();
		}

		size_t siz = strlen(val_->name.c_str());
		
		if (siz && siz < BOT_FILENAME_MAX)
		{
			name.append(val_->name.c_str());
		}
		siz = strlen(val_->type.c_str());
		
		if (siz && siz < 128)
		{
			type.append(val_->type.c_str());
		}
		siz = strlen(val_->path.c_str());
		
		if (siz && siz < UINT64_MAX)
		{
			path.append(val_->path.c_str());
		}
		strsiz = val_->strvec.size();
		lid = val_->lid;
		exists = val_->exists;
		c_by = val_->c_by;
		cm = val_->cm;
		return 0;
	}

	BOT_FILE_M(cchar* nfn = "", cchar* nft = "", cchar* nfp = "", sint nc_by = -1, sint nomode = -1)
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
		omode = nomode;
		cm = lid = fcon = -1;
		c_by = nc_by;

		if (strlen(nfn))
		{
			std::string str;
			str.append(nfp);
			str.append(nfn);
			str.append(nft);
#ifdef _WIN32
			exists = _stat(str.c_str(), &filestats);
#else
			exists = stat(str.c_str(), &filestats);
#endif
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
	std::fstream fstrm;

	void Clear() { in_use = false; flid = omode = lid = -1; if (fstrm.is_open()) { fstrm.close(); } }
	void Renew(BOTF_CONN* val_ = 0)
	{
		Clear();

		if (val_)
		{
			flid = val_->flid;
			omode = val_->omode;
			lid = val_->lid;
			in_use = val_->in_use;
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
			in_use = true;
		}
	}
	
	BOTF_CONN() { in_use = false; flid = omode = lid = -1; };

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
	BOT_TTS_MAX = 11
};

class TINFO
{
public:
	sint lok;
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

	void Clear() { min_ratv = 0.0f; t_I = std::chrono::steady_clock::now(); opt = lok = lid = c_by = -1; fin = -10; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; attr = NULL; }
	void Renew(TINFO* val_ = 0)
	{
		Clear();

		func = val_->func;
		opt = val_->opt;
		c_by = val_->c_by;
		t_I = val_->t_I;
		min_ratv = val_->min_ratv;
		thread_name.append(thread_name.c_str());
	}

	void Renew(sint nopt = -1, cchar* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f)
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
	}

	TINFO(sint nopt = -1, cchar* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f) { min_ratv = nmin_ratv; attr = NULL; t_I = std::chrono::steady_clock::now(); func = nfunc; c_by = nc_by; opt = nopt; lok = lid = -1; fin = -10; size_t x = strlen(ntn); if (x && x < 256) { thread_name.append(ntn); } };

private:
};

class TINFO_M
{
public:
	sint lok;
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

	void Clear() { min_ratv = 0.0f; attr = thread = 0; t_I = std::chrono::steady_clock::now(); opt = lok = lid = c_by = -1; fin = -10; if (!thread_name.empty()) { thread_name.clear(); } func = NULL; }
	void Renew(TINFO_M* val_ = 0)
	{
		Clear();

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
	}
	void Renew(TINFO* val_ = 0)
	{
		Clear();

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
	}

	TINFO_M(sint nopt = -1, cchar* ntn = "", void *(*nfunc)(void *) = NULL, sint nc_by = -1, float nmin_ratv = 0.0f) { min_ratv = nmin_ratv; t_I = std::chrono::steady_clock::now(); opt = lid = lok = -1; fin = -10; if (nopt > -1) { opt = nopt; } if (strlen(ntn) && strlen(ntn) < 256) { thread_name.append(ntn); } func = nfunc; c_by = nc_by; };

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

class VTool
{
public:

	VTool(std::chrono::steady_clock::time_point* nt = 0) { SetTClr(nt); };

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
	sint vuchrcmp(std::vector<uchar>* a = 0, std::vector<uchar>* b = 0)
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
	sint vchrcmp(std::vector<char>* a = 0, std::vector<char>* b = 0)
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
	sint vccpcmp(std::vector<cchar*>* a = 0, std::vector<cchar*>* b = 0)
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

		if (valI->maint != valII->maint)
		{
			return -1;
		}

		if (valI->it_type != valII->it_type)
		{
			return -1;
		}

		if (strcmp(valI->dbname.c_str(), valII->dbname.c_str())) { return -1; }

		size_t Isiz = valI->tables.size();
		size_t IIsiz = valII->tables.size();

		if (Isiz != IIsiz)
		{
			return -1;
		}

		for (Isiz = 0; Isiz < valI->tables.size(); Isiz++) { if (strcmp(valI->tables[Isiz].c_str(), valII->tables[Isiz].c_str())) { Isiz = valI->tables.size(); } }

		if (Isiz != valI->tables.size()) { return -1; }

		Isiz = valI->opts.size();
		IIsiz = valII->opts.size();

		if (Isiz != IIsiz)
		{
			return -1;
		}

		for (Isiz = 0; Isiz < valI->opts.size(); Isiz++) { if (valI->opts[Isiz].size() != valII->opts[Isiz].size()) { Isiz = valI->opts.size(); } else { IIsiz = 0; while (IIsiz < valI->opts[Isiz].size()) { if (valI->opts[Isiz][IIsiz] != valII->opts[Isiz][IIsiz]) { return -1; } IIsiz++; } } }

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
	
	sint ValInVec(std::vector<carr_2> *vec_ = 0, char val[2] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4> *vec_ = 0, char val[4] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_8> *vec_ = 0, char val[8] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_16> *vec_ = 0, char val[16] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_32> *vec_ = 0, char val[32] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_64> *vec_ = 0, char val[64] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_128> *vec_ = 0, char val[128] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_256> *vec_ = 0, char val[256] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_512> *vec_ = 0, char val[512] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_1024> *vec_ = 0, char val[1024] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2048> *vec_ = 0, char val[2048] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4096> *vec_ = 0, char val[4096] = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_8> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_16> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_32> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_64> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_128> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_256> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_512> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_1024> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2048> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4096> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).carr, val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_8> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_16> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_32> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_64> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_128> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_256> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_512> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_1024> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_2048> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<carr_4096> *vec_ = 0, void* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { cchar* val_ = reinterpret_cast<cchar*>(val); if (!strcmp(vec_->at(siz).carr, val_)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::vector<uchar>> *vec_ = 0, std::vector<uchar>* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).size() == val->size()) { vn = vuchrcmp(&vec_->at(siz), val); if (!vn) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz).size() == val->size()) { vn = vuchrcmp(&vec_->at(siz), val); if (!vn) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector <std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, uchar val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_ = 0, uchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uchar* val_ = (uchar*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uchar* val_ = (uchar*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, const sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; uchar val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, const slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; uchar val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, const sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; uchar val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, const uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; uchar val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, const ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; uchar val_[valsiz]; memcpy((void*)&val_[siz],(void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, const ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } const size_t valsiz = sizeof(val)+1; uchar val_[valsiz]; memcpy((void*)&val_[siz], (void*)&val, valsiz); if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uchar* val_ = (uchar*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uchar* val_ = (uchar*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uchar* val_ = (uchar*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uchar* val_ = (uchar*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uchar> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uchar* val_ = (uchar*)val->c_str(); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uchar* val_ = (uchar*)val->c_str(); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<char> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<void*> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sint *val_ = reinterpret_cast<sint*>(val); if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { slint *val_ = (slint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (slint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32	
	sint ValInVec(std::vector<slint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<slint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (slint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<slint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<sllint> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { sllint *val_ = (sllint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (sllint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<sllint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<sllint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (sllint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<sllint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<uint> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { uint *val_ = (uint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (uint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (uint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<uint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<uint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<uint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<ulint> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ulint *val_ = (ulint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ulint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ulint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<ulint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<ulint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ulint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<ullint> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { ullint *val_ = (ullint*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (ullint)*val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (ullint)*val) { vn = siz; siz = -1; } siz--; } } return vn; }
#ifdef _WIN32
	sint ValInVec(std::vector<ullint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == _atoi64(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#else
	sint ValInVec(std::vector<ullint> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<ullint> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atoi(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
#endif
	sint ValInVec(std::vector<float> *vec_, uchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, void* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { float *val_ = (float*)val; if (vec_->at(siz) == *val_) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == (float)val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == (float)val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == *val) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == *val) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atof(val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atof(val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<float> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz) == atof(val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz) == atof(val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, uchar* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; cchar* mid = reinterpret_cast <cchar*>(*vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, void* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; cchar* mid = reinterpret_cast <cchar*>(vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%i", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%li", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lli", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%u", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%llu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, float* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[32]{ 0 }; sint siz = bot_sprintf(mid, 32, "%0.3f", *val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, cchar* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), val)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<cchar*> *vec_, std::string* val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz), val->c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz), val->c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, uchar* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; cchar* mid = reinterpret_cast <cchar*>(*vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, void* vp, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; cchar* mid = reinterpret_cast <cchar*>(vp); sint siz = 0; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, sint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%i", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, slint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%li", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, sllint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lli", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, uint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%u", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, ulint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%lu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_, ullint val, sint e_from = 0, bool forw = true) { if (!vec_) { return -1; } sint vn = -1; char mid[21]{ 0 }; sint siz = bot_sprintf(mid, 21, "%llu", val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_ = 0, float* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; char mid[32]{ 0 }; sint siz = bot_sprintf(mid, 32, "%0.3f", *val); siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), mid)) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<std::string> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (!strcmp(vec_->at(siz).c_str(), val)) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (!strcmp(vec_->at(siz).c_str(), val)) { vn = siz; siz = -1; } siz--; } } return vn; }
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
	sint ValInVec(std::vector<BOT_DB> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<DB_CONN*> *vec_ = 0, cchar* val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && !strcmp(val, vec_->at(siz)->name.c_str()) && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && !strcmp(val, vec_->at(siz)->name.c_str()) && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOTF_CONN> *vec_ = 0, sint val = -1, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).flid) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && val == vec_->at(siz).flid) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOTF_CONN*> *vec_ = 0, sint val = -1, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && val == vec_->at(siz)->flid) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && val == vec_->at(siz)->flid) { vn = siz; siz = -1; } } siz--; } } return vn; }
	//sint ValInVec(std::vector<DB_CONN*> *vec_ = 0, sint val = 0, sint omode = -1, sint e_from = 0, bool forw = true) { if (omode < 0 || val < 0) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->lid == val && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (vec_->at(siz)->lid > -1 && vec_->at(siz)->lid == val && (omode <= vec_->at(siz)->omode)) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB_M> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT_M> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET_M> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).logtitle.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE_M> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO_M> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } siz++; } } else { while (siz > -1) { if (vec_->at(siz).lid > -1 && !strcmp(val, vec_->at(siz).thread_name.c_str())) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_DB*> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_CLIENT*> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_LOGDET*> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->logtitle.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->logtitle.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<BOT_FILE*> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }
	sint ValInVec(std::vector<TINFO*> *vec_ = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!vec_ || !val) { return -1; } sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = ((sint)vec_->size() + e_from); } if (forw) { while (siz < (sint)vec_->size()) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->thread_name.c_str())) { vn = siz; siz = (sint)vec_->size(); } } siz++; } } else { while (siz > -1) { if (vec_->at(siz)) { if (!strcmp(val, vec_->at(siz)->thread_name.c_str())) { vn = siz; siz = -1; } } siz--; } } return vn; }

	sint ValInArr(BOTF_CONN arr[] = 0, sint val = -1, sint e_from = 0, bool forw = true) { if (!arr || val < 0) { return -1; } sint msiz = (sint)sizeof(arr); sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (msiz + e_from); } if (forw) { while (siz < msiz) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = msiz; } siz++; } } else { while (siz > -1) { if (arr[siz].flid == val && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }
	sint ValInArr(DB_CONN arr[] = 0, cchar* val = 0, sint e_from = 0, bool forw = true) { if (!arr || !val) { return -1; } sint msiz = (sint)sizeof(arr); sint vn = -1; sint siz = e_from; if (e_from < 0) { siz = (msiz + e_from); } if (forw) { while (siz < msiz) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = msiz; } siz++; } } else { while (siz > -1) { if (!strcmp(arr[siz].name.c_str(), val) && arr[siz].lid > -1) { vn = siz; siz = -1; } siz--; } } return vn; }

	sint UseEmptyEle(std::vector<carr_2> *vec_ = 0, char val[2] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 2) { if (val[siz] == '\0') { siz = 2; } siz++; } if (siz == 2) { char nc = '\0'; memcpy((void*)&val[1], (void*)&nc, sizeof(val[1])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_4> *vec_ = 0, char val[4] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 4) { if (val[siz] == '\0') { siz = 4; } siz++; } if (siz == 4) { char nc = '\0'; memcpy((void*)&val[3], (void*)&nc, sizeof(val[3])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_8> *vec_ = 0, char val[8] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 8) { if (val[siz] == '\0') { siz = 8; } siz++; } if (siz == 8) { char nc = '\0'; memcpy((void*)&val[7], (void*)&nc, sizeof(val[7])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_16> *vec_ = 0, char val[16] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 16) { if (val[siz] == '\0') { siz = 16; } siz++; } if (siz == 16) { char nc = '\0'; memcpy((void*)&val[15], (void*)&nc, sizeof(val[15])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_32> *vec_ = 0, char val[32] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 32) { if (val[siz] == '\0') { siz = 32; } siz++; } if (siz == 32) { char nc = '\0'; memcpy((void*)&val[31], (void*)&nc, sizeof(val[31])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_64> *vec_ = 0, char val[64] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 64) { if (val[siz] == '\0') { siz = 64; } siz++; } if (siz == 64) { char nc = '\0'; memcpy((void*)&val[63], (void*)&nc, sizeof(val[63])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_128> *vec_ = 0, char val[128] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 128) { if (val[siz] == '\0') { siz = 128; } siz++; } if (siz == 128) { char nc = '\0'; memcpy((void*)&val[127], (void*)&nc, sizeof(val[127])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_256> *vec_ = 0, char val[256] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 256) { if (val[siz] == '\0') { siz = 256; } siz++; } if (siz == 256) { char nc = '\0'; memcpy((void*)&val[255], (void*)&nc, sizeof(val[255])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_512> *vec_ = 0, char val[512] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 512) { if (val[siz] == '\0') { siz = 512; } siz++; } if (siz == 512) { char nc = '\0'; memcpy((void*)&val[511], (void*)&nc, sizeof(val[511])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_1024> *vec_ = 0, char val[1024] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 1024) { if (val[siz] == '\0') { siz = 1024; } siz++; } if (siz == 1024) { char nc = '\0'; memcpy((void*)&val[1023], (void*)&nc, sizeof(val[1023])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_2048> *vec_ = 0, char val[2048] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 2048) { if (val[siz] == '\0') { siz = 2048; } siz++; } if (siz == 2048) { char nc = '\0'; memcpy((void*)&val[2047], (void*)&nc, sizeof(val[2047])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<carr_4096> *vec_ = 0, char val[4096] = 0) { if (!vec_ || !val) { return -1; } size_t siz = 0; while (siz < 4096) { if (val[siz] == '\0') { siz = 4096; } siz++; } if (siz == 4096) { char nc = '\0'; memcpy((void*)&val[4095], (void*)&nc, sizeof(val[4095])); } sint vn = -1; siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).carr[0] == '\0') { bot_strcpy(vec_->at(siz).carr, val); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::vector<uchar>> *vec_ = 0, std::vector<uchar>* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { for (size_t nsiz = 0; nsiz < val->size(); nsiz++) { vec_->at(siz).push_back(val->at(nsiz)); } vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == vtclr) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<uchar> *vec_ = 0, uchar* val = 0) { if (!vec_ || !val) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = *val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<uchar> *vec_, uchar val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { memcpy((void*)&vec_->at(siz), (void*)&val, sizeof(vec_->at(siz))); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<void*> *vec_ = 0, void* val = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!vec_->at(siz)) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<sint> *vec_, sint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<slint> *vec_, slint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT32_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<sllint> *vec_, sllint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == INT64_MIN) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<uint> *vec_, uint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<ulint> *vec_, ulint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT32_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<ullint> *vec_, ullint val) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == UINT64_MAX) { vec_->at(siz) = val; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<float> *vec_ = 0, float* fp = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == 0) { vec_->at(siz) = *fp; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<cchar*> *vec_ = 0, void* vp = 0) { if (!vec_) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz), " ") || !strlen(vec_->at(siz))) { vec_->at(siz) = 0; cchar* mid = reinterpret_cast<cchar*>(vp); vec_->at(siz) = mid; vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::string> *vec_ = 0, std::string* sp = 0) { if (!vec_ || !sp) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { vec_->at(siz).clear(); vec_->at(siz).append(*sp); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
	sint UseEmptyEle(std::vector<std::string> *vec_ = 0, cchar* sp = 0) { if (!vec_ || !sp) { return -1; } sint vn = -1; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz).empty()) { vec_->at(siz).clear(); vec_->at(siz).append(sp); vn = (sint)siz; siz = vec_->size(); } siz++; } return vn; }
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

	sint AddValToVec(std::vector<carr_2> *vec_ = 0, char val[2] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_4> *vec_ = 0, char val[4] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_8> *vec_ = 0, char val[8] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_8 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_16> *vec_ = 0, char val[16] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_16 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_32> *vec_ = 0, char val[32] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_32 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_64> *vec_ = 0, char val[64] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_64 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_128> *vec_ = 0, char val[128] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_128 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_256> *vec_ = 0, char val[256] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_256 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_512> *vec_ = 0, char val[512] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_512 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_1024> *vec_ = 0, char val[1024] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_1024 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_2048> *vec_ = 0, char val[2048] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_2048 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<carr_4096> *vec_ = 0, char val[4096] = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } carr_4096 ncar; bot_strcpy(ncar.carr, val); vec_->push_back(ncar); return viv; }
	sint AddValToVec(std::vector<std::vector<uchar>>* vec_ = 0, std::vector<uchar>* val = 0, bool check = false, bool use_empty = false) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<std::chrono::steady_clock::time_point> *vec_, std::chrono::steady_clock::time_point* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<uchar> *vec_, uchar* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<uchar> *vec_, uchar val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, &val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, &val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<void*> *vec_, void* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<sint> *vec_, sint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<slint> *vec_, slint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<sllint> *vec_, sllint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<uint> *vec_, uint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<ulint> *vec_, ulint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<ullint> *vec_, ullint val, bool check, bool use_empty) { if (!vec_) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(val); return viv; }
	sint AddValToVec(std::vector<float> *vec_, float* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<cchar*> *vec_, void* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(reinterpret_cast<cchar*>(val)); return viv; }
	sint AddValToVec(std::vector<std::string> *vec_, std::string* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } vec_->push_back(*val); return viv; }
	sint AddValToVec(std::vector<std::string> *vec_, cchar* val, bool check, bool use_empty) { if (!vec_ || !val) { return -1; } sint viv = -1; if (check) { viv = ValInVec(vec_, val); if (viv > -1) { return viv; } } if (use_empty) { viv = UseEmptyEle(vec_, val); if (viv > -1) { return viv; } } viv = (sint)vec_->size(); if (viv > BOTVEC_LIM) { return -1; } std::string nval; nval.append(val); vec_->push_back(nval); return viv; }
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

	std::chrono::steady_clock::time_point GetValInVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { std::chrono::steady_clock::time_point ret; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele); } return ret; }
	sint GetValInVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { *val = vec_->at(ele); ret = ele; } return ret; }
	char *GetValInVec(std::vector<carr_2> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_4> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_8> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_16> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_32> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_64> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_128> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_256> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_512> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_1024> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_2048> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
	char *GetValInVec(std::vector<carr_4096> *vec_ = 0, sint ele = -1) { if (!vec_) { return 0; } if (ele > -1 && ele < (sint)vec_->size()) { return vec_->at(ele).carr; } return 0; }
/*	uchar GetValInVecUC(std::vector<uchar> *vec_, sint ele = -1) { uchar ret = 0; if (ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }*/
	uchar GetValInVecUC(std::vector<void*> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, vec_->at(ele), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<sint> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<slint> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<sllint> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<uint> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<ulint> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<ullint> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<float> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<cchar*> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = sizeof(vec_->at(ele)); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uchar GetValInVecUC(std::vector<std::string> *vec_ = 0, sint ele = -1) { uchar ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { cchar* cret = vec_->at(ele).c_str(); const size_t inv_siz = sizeof(&cret); uchar ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&cret), inv_siz); ret = *ret_; } return ret; }
	void* GetValInVecV_(std::vector<uchar> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<void*> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = vec_->at(ele); } return ret; }
	void* GetValInVecV_(std::vector<sint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<slint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<sllint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<uint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<ulint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<ullint> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<float> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<cchar*> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { ret = reinterpret_cast<void*>(&vec_->at(ele)); } return ret; }
	void* GetValInVecV_(std::vector<std::string> *vec_ = 0, sint ele = -1) { void* ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { cchar* cret = vec_->at(ele).c_str(); ret = reinterpret_cast<void*>(&cret); } return ret; }
	sint GetValInVecI(std::vector<uchar> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); sint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	slint GetValInVecLI(std::vector<uchar> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); slint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	sllint GetValInVecLLI(std::vector<uchar> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); sllint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	uint GetValInVecU(std::vector<uchar> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); uint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	ulint GetValInVecLU(std::vector<uchar> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); ulint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
	ullint GetValInVecLLU(std::vector<uchar> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { const size_t inv_siz = (sizeof(vec_->at(ele))); ullint ret_[inv_siz]; memcpy((void*)ret_, reinterpret_cast<void*>(&vec_->at(ele)), inv_siz); ret = *ret_; } return ret; }
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
	sint GetValInVecI(std::vector<cchar*> *vec_ = 0, sint ele = -1) { sint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
	slint GetValInVecLI(std::vector<cchar*> *vec_ = 0, sint ele = -1) { slint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#ifdef _WIN32
	sllint GetValInVecLLI(std::vector<cchar*> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = _atoi64(vec_->at(ele)); } } return ret; }
#else
	sllint GetValInVecLLI(std::vector<cchar*> *vec_ = 0, sint ele = -1) { sllint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#endif
	uint GetValInVecU(std::vector<cchar*> *vec_ = 0, sint ele = -1) { uint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
	ulint GetValInVecLU(std::vector<cchar*> *vec_ = 0, sint ele = -1) { ulint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
#ifdef _WIN32
	ullint GetValInVecLLU(std::vector<cchar*> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = _atoi64(vec_->at(ele)); } } return ret; }
#else
	ullint GetValInVecLLU(std::vector<cchar*> *vec_ = 0, sint ele = -1) { ullint ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = atoi(vec_->at(ele)); } } return ret; }
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
	float GetFValInVec(std::vector<uchar> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { float* fp_ = reinterpret_cast<float*>(&vec_->at(ele)); ret = *fp_; } return ret; }
	float GetFValInVec(std::vector<void*> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { float* fp_ = reinterpret_cast<float*>(vec_->at(ele)); ret = *fp_; } } return ret; }
	float GetFValInVec(std::vector<float> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<sint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<slint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<uint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)vec_->at(ele); } } return ret; }
	float GetFValInVec(std::vector<cchar*> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)atof(vec_->at(ele)); } } return ret; }
	float GetFValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1) { float ret = 0; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret = (float)atof(vec_->at(ele).c_str()); } } return ret; }
	void GetCValInVec(std::vector<uchar> *vec_ = 0, sint ele = -1, cchar* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = reinterpret_cast<cchar*>(&vec_->at(ele)); } } }
	void GetCValInVec(std::vector<void*> *vec_ = 0, sint ele = -1, cchar* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = reinterpret_cast<cchar*>(vec_->at(ele)); } } }
	void GetCValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%i", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%li", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%lli", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%u", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%lu", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, char val[21] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 21, "%llu", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<float> *vec_ = 0, sint ele = -1, char val[32] = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { sint xc = bot_sprintf(val, 32, "%0.3f", vec_->at(ele)); } } }
	void GetCValInVec(std::vector<cchar*> *vec_ = 0, sint ele = -1, cchar* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = (vec_->at(ele)); } } }
	void GetCValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1, cchar* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val = (vec_->at(ele).c_str()); } } }
	std::string GetStrValInVec(std::vector<uchar> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { cchar* ret_ = reinterpret_cast<cchar*>(&vec_->at(ele)); ret.append(ret_); } } return ret; }
	std::string GetStrValInVec(std::vector<void*> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret.append(reinterpret_cast<cchar*>(vec_->at(ele))); } } return ret; }
#ifdef _WIN32
	std::string GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = (_itoa_s(vec_->at(ele), mid, 10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = (_itoa_s(vec_->at(ele), mid,10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
#else
	std::string GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = (bot_itoa(vec_->at(ele), mid, 10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = (bot_itoa(vec_->at(ele), mid, 10)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); ret.append(mid); } } return ret; }
#endif
	std::string GetStrValInVec(std::vector<float> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[64]{ 0 }; bot_sprintf(mid, 64, "%0.3f", vec_->at(ele)); ret.append(mid); } } return ret; }
	std::string GetStrValInVec(std::vector<cchar*> *vec_ = 0, sint ele = -1) { std::string ret; if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { ret.append(vec_->at(ele)); } } return ret; }
	void GetStrValInVec(std::vector<uchar> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { cchar* ret_ = reinterpret_cast<cchar*>(&vec_->at(ele)); val->append(ret_); } } }
	void GetStrValInVec(std::vector<void*> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val->append(reinterpret_cast<cchar*>(vec_->at(ele))); } } }
#ifdef _WIN32
	void GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _itoa_s(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
	void GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _i64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
	void GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _itoa_s(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = _ui64toa_s(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)),10); val->append(mid); } } }
#else
	void GetStrValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
	void GetStrValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[22]{ 0 }; errno_t err = bot_itoa(vec_->at(ele), mid, sizeof((sint)vec_->at(ele)), 10); val->append(mid); } } }
#endif
	void GetStrValInVec(std::vector<float> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { char mid[64]{ 0 }; bot_sprintf(mid, 64, "%0.3f", vec_->at(ele)); val->append(mid); } } }
	void GetStrValInVec(std::vector<cchar*> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val->append(vec_->at(ele)); } } }
	void GetStrValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1, std::string* val = 0) { if (vec_ && ele > -1) { if (ele < (sint)vec_->size()) { val->append(vec_->at(ele)); } } }

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
			ret = GetMembValInVec(vec_, ele, BOT_FS_STRVEC, &val->strvec);
			ret = GetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = GetMembValInVec(vec_, ele, BOT_FS_STATS, &val->filestats);
			ret = GetMembValInVec(vec_, ele, BOT_FS_ID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_FS_E, &val->exists);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
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
				else if (memb == BOT_FS_STRVEC) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).strvec.size()) { vp->push_back(vec_->at(ele).strvec[siz]); siz++; } }
				else if (memb == BOT_FS_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_FS_STATS) { struct stat* vp = reinterpret_cast<struct stat*>(val); memcpy(vp, &vec_->at(ele).filestats, sizeof(vec_->at(ele).filestats)); }
				else if (memb == BOT_FS_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_FS_E) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).exists; }
				else if (memb == BOT_FS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_FS_CM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).cm; }
				else if (memb == BOT_FS_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
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
			ret = GetMembValInVec(vec_, ele, BOT_FS_STRVEC, &val->strsiz);
			ret = GetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = GetMembValInVec(vec_, ele, BOT_FS_STATS, &val->filestats);
			ret = GetMembValInVec(vec_, ele, BOT_FS_ID, &val->lid);
			ret = GetMembValInVec(vec_, ele, BOT_FS_E, &val->exists);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = GetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = GetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
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
				else if (memb == BOT_FS_STRVEC) { size_t* vp = reinterpret_cast<size_t*>(val); *vp = vec_->at(ele).strsiz; }
				else if (memb == BOT_FS_OMODE) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).omode; }
				else if (memb == BOT_FS_STATS) { struct stat* vp = reinterpret_cast<struct stat*>(val); memcpy(vp, &vec_->at(ele).filestats, sizeof(vec_->at(ele).filestats)); }
				else if (memb == BOT_FS_ID) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).lid; }
				else if (memb == BOT_FS_E) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).exists; }
				else if (memb == BOT_FS_CBY) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).c_by; }
				else if (memb == BOT_FS_CM) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).cm; }
				else if (memb == BOT_FS_FCON) { sint* vp = reinterpret_cast<sint*>(val); *vp = vec_->at(ele).fcon; }
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
			ret = GetMembValInVec(vec_, ele, BOT_STMT_CTYPES, &val->ic_types);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_TABLES, &val->tables);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_DBNAME, &val->dbname);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_DBALIAS, &val->dbalias);
			ret = GetMembValInVec(vec_, ele, BOT_STMT_OPTS, &val->opts);
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
				else if (memb == BOT_STMT_CTYPES) { std::vector<sint>* vp = reinterpret_cast<std::vector<sint>*>(val); size_t siz = 0; while (siz < vec_->at(ele).ic_types.size()) { vp->push_back(vec_->at(ele).ic_types[siz]); siz++; } }
				else if (memb == BOT_STMT_TABLES) { std::vector<std::string>* vp = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; while (siz < vec_->at(ele).tables.size()) { vp->push_back(vec_->at(ele).tables[siz]); siz++; } }
				else if (memb == BOT_STMT_DBNAME) { std::string* vp = reinterpret_cast<std::string*>(val); size_t siz = 0; vp->append(vec_->at(ele).dbname.c_str()); }
				else if (memb == BOT_STMT_DBALIAS) { std::string* vp = reinterpret_cast<std::string*>(val); vp->clear(); vp->append(vec_->at(ele).dbalias.c_str()); }
				else if (memb == BOT_STMT_OPTS) { std::vector<std::vector<size_t>>* vp = reinterpret_cast<std::vector<std::vector<size_t>>*>(val); size_t siz = 0; while (siz < vec_->at(ele).cols.size()) { vp->push_back(vec_->at(ele).opts[siz]); siz++; } }
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

	sint SetValInVec(std::vector<carr_2> *vec_ = 0, sint ele = -1, char val[2] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_4> *vec_ = 0, sint ele = -1, char val[4] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_8> *vec_ = 0, sint ele = -1, char val[8] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_16> *vec_ = 0, sint ele = -1, char val[16] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_32> *vec_ = 0, sint ele = -1, char val[32] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_64> *vec_ = 0, sint ele = -1, char val[64] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_128> *vec_ = 0, sint ele = -1, char val[128] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_256> *vec_ = 0, sint ele = -1, char val[256] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_512> *vec_ = 0, sint ele = -1, char val[512] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_1024> *vec_ = 0, sint ele = -1, char val[1024] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_2048> *vec_ = 0, sint ele = -1, char val[2048] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<carr_4096> *vec_ = 0, sint ele = -1, char val[4096] = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { bot_strcpy(vec_->at((size_t)ele).carr, val); ret = ele; } return ret; }
	sint SetValInVec(std::vector<uchar> *vec_ = 0, sint ele = -1, uchar val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<void*> *vec_ = 0, sint ele = -1, void* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1, std::chrono::steady_clock::time_point* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = *val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<sint> *vec_ = 0, sint ele = -1, uint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<slint> *vec_ = 0, sint ele = -1, ulint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<sllint> *vec_ = 0, sint ele = -1, ullint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<uint> *vec_ = 0, sint ele = -1, uint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<ulint> *vec_ = 0, sint ele = -1, ulint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<ullint> *vec_ = 0, sint ele = -1, ullint val = 0) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<float> *vec_ = 0, sint ele = -1, float* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = *val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<cchar*> *vec_ = 0, sint ele = -1, cchar* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele) = val; ret = ele; } return ret; }
	sint SetValInVec(std::vector<std::string> *vec_ = 0, sint ele = -1, std::string* val = 0) { sint ret = -1; if (vec_ && val && ele > -1 && ele < (sint)vec_->size()) { vec_->at((size_t)ele).clear(); vec_->at((size_t)ele).append(*val); ret = ele; } return ret; }
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
			ret = SetMembValInVec(vec_, ele, BOT_FS_STRVEC, &val->strvec);
			ret = SetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = SetMembValInVec(vec_, ele, BOT_FS_STATS, &val->filestats);
			ret = SetMembValInVec(vec_, ele, BOT_FS_ID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_FS_E, &val->exists);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
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
			else if (memb == BOT_FS_STRVEC) { std::vector <std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).strvec.clear(); while (siz < val_->size()) { vec_->at(ele).strvec.push_back(val_->at(siz)); siz++; } }
			else if (memb == BOT_FS_OMODE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).omode = *val_; }
#ifdef _WIN32
			else if (memb == BOT_FS_STATS) { memcpy(&vec_->at(ele).filestats, val, sizeof(val)); }
#else
			else if (memb == BOT_FS_STATS) { struct stat *val_ = reinterpret_cast<struct stat*>(val); vec_->at(ele).filestats = *val_; }
#endif
			else if (memb == BOT_FS_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_FS_E) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).exists = *val_; }
			else if (memb == BOT_FS_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_FS_CM) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).cm = *val_; }
			else if (memb == BOT_FS_FCON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fcon = *val_; }
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
			ret = SetMembValInVec(vec_, ele, BOT_FS_STRVEC, &val->strsiz);
			ret = SetMembValInVec(vec_, ele, BOT_FS_OMODE, &val->omode);
			ret = SetMembValInVec(vec_, ele, BOT_FS_STATS, &val->filestats);
			ret = SetMembValInVec(vec_, ele, BOT_FS_ID, &ele);
			ret = SetMembValInVec(vec_, ele, BOT_FS_E, &val->exists);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CBY, &val->c_by);
			ret = SetMembValInVec(vec_, ele, BOT_FS_CM, &val->cm);
			ret = SetMembValInVec(vec_, ele, BOT_FS_FCON, &val->fcon);
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
			else if (memb == BOT_FS_STRVEC) { size_t* val_ = reinterpret_cast<size_t*>(val); vec_->at(ele).strsiz = *val_; }
			else if (memb == BOT_FS_OMODE) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).omode = *val_; }
#ifdef _WIN32
			else if (memb == BOT_FS_STATS) { memcpy(&vec_->at(ele).filestats, val, sizeof(val)); }
#else
			else if (memb == BOT_FS_STATS) { struct stat *val_ = reinterpret_cast<struct stat*>(val); vec_->at(ele).filestats = *val_; }
#endif
			else if (memb == BOT_FS_ID) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).lid = *val_; }
			else if (memb == BOT_FS_E) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).exists = *val_; }
			else if (memb == BOT_FS_CBY) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).c_by = *val_; }
			else if (memb == BOT_FS_CM) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).cm = *val_; }
			else if (memb == BOT_FS_FCON) { sint* val_ = reinterpret_cast<sint*>(val); vec_->at(ele).fcon = *val_; }
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
			ret = SetMembValInVec(vec_, ele, BOT_STMT_CTYPES, &val->ic_types);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_TABLES, &val->tables);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_DBNAME, &val->dbname);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_DBALIAS, &val->dbalias);
			ret = SetMembValInVec(vec_, ele, BOT_STMT_OPTS, &val->opts);
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
			else if (memb == BOT_STMT_CTYPES) { std::vector <sint>* val_ = reinterpret_cast<std::vector<sint>*>(val); size_t siz = 0; vec_->at(ele).ic_types.clear(); while (siz < val_->size()) { vec_->at(ele).ic_types.push_back(val_->at(siz)); siz++; } }
			else if (memb == BOT_STMT_TABLES) { std::vector <std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val); size_t siz = 0; vec_->at(ele).tables.clear(); while (siz < val_->size()) { vec_->at(ele).tables.push_back(val_->at(siz)); siz++; } }
			else if (memb == BOT_STMT_DBNAME) { std::string* val_ = reinterpret_cast<std::string*>(val); size_t siz = 0; vec_->at(ele).dbname.clear(); vec_->at(ele).dbname.append(val_->c_str()); }
			else if (memb == BOT_STMT_DBALIAS) { std::string* val_ = reinterpret_cast<std::string*>(val); vec_->at(ele).dbalias.clear(); vec_->at(ele).dbalias.append(val_->c_str()); }
			else if (memb == BOT_STMT_OPTS) { std::vector<std::vector<size_t>>* val_ = reinterpret_cast<std::vector<std::vector<size_t>>*>(val); size_t siz = 0; vec_->at(ele).opts.clear(); while (siz < val_->size()) { vec_->at(ele).opts.push_back(val_->at(siz)); siz++; } }
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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					cchar* val_ = reinterpret_cast<cchar*>(val);
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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).login_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).lastlogin.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).logindate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).last_failed_login.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).lastexchange.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).login_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).lastlogin.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).logindate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).last_failed_login.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).lastexchange.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).logtitle.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).startdate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					cchar* val_ = reinterpret_cast<cchar*>(val);
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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).logtitle.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).startdate.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).path.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).type.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

					if (val_)
					{
						vec_->at(ele).type.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_STRVEC)
			{
				if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);
					std::string str;
					str.append(val_);
					vec_->at(ele).strvec.push_back(str);
				}
				else if (opt == 3)
				{
					std::vector<std::string>* val_ = reinterpret_cast<std::vector<std::string>*>(val);
					size_t siz = 0;

					while (siz < val_->size())
					{
						vec_->at(ele).strvec.push_back(val_->at(siz));
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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).path.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).type.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

					if (val_)
					{
						vec_->at(ele).type.append(val_);
					}
				}
				else {}
				ret = ele;
			}
			else if (memb == BOT_FS_STRVEC)
			{
				size_t* val_ = reinterpret_cast<size_t*>(val);
				vec_->at(ele).strsiz += *val_;
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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).thread_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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
					char* val_ = reinterpret_cast<char*>(val);

					if (val_)
					{
						vec_->at(ele).thread_name.push_back(*val_);
					}
				}
				else if (opt == 2)
				{
					cchar* val_ = reinterpret_cast<cchar*>(val);

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

	sint ClearValFromVec(std::vector<carr_2> *vec_ = 0, char val[2] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_4> *vec_ = 0, char val[4] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_8> *vec_ = 0, char val[8] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_16> *vec_ = 0, char val[16] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_32> *vec_ = 0, char val[32] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_64> *vec_ = 0, char val[64] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_128> *vec_ = 0, char val[128] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_256> *vec_ = 0, char val[256] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_512> *vec_ = 0, char val[512] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_1024> *vec_ = 0, char val[1024] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_2048> *vec_ = 0, char val[2048] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<carr_4096> *vec_ = 0, char val[4096] = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz).carr, (void*)val, sizeof(vec_->at(siz).carr)) && sizeof(vec_->at(siz).carr)) { vec_->at(siz).carr[0] = '\0'; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<uchar> *vec_ = 0, uchar val = UCHAR_MAX, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp((void*)vec_->at(siz), (void*)&val, sizeof(vec_->at(siz)))) { vec_->at(siz) = UCHAR_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<void*> *vec_ = 0, void* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (!memcmp(vec_->at(siz),val,sizeof(vec_->at(siz)))) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, std::chrono::steady_clock::time_point* val = 0, bool clear_all = false) { sint ret = -1; if (!vec_ || !val) { return ret; } ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == *val) { vec_->at(siz) = vtclr; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<sint> *vec_ = 0, sint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<slint> *vec_ = 0, slint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT32_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<sllint> *vec_ = 0, sllint val = INT32_MIN, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = INT64_MIN; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<uint> *vec_ = 0, uint val = UINT_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<ulint> *vec_ = 0, ulint val = UINT32_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT32_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<ullint> *vec_ = 0, ullint val = UINT64_MAX, bool clear_all = false) { sint ret = -1; ret++; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == val) { vec_->at(siz) = UINT64_MAX; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<float> *vec_ = 0, float* fp = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (vec_->at(siz) == *fp) { vec_->at(siz) = 0.0f; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
	sint ClearValFromVec(std::vector<cchar*> *vec_ = 0, cchar* mid = 0, bool clear_all = false) { sint ret = 0; size_t siz = 0; while (siz < vec_->size()) { if (!strcmp(vec_->at(siz), mid)) { vec_->at(siz) = 0; ret++; if (!clear_all) { siz = vec_->size(); } } siz++; } return ret; }
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
	sint ClearEleFromVec(std::vector<uchar> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UCHAR_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<void*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = vtclr; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<sint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT_MIN; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<slint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT32_MIN; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<sllint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = INT64_MIN; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<uint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<ulint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT32_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<ullint> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = UINT64_MAX; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<float> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = 0.0f; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<cchar*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele) = ""; ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<std::string> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOT_STMT> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele).Clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<DB_CONN*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele)->Clear(); ret = ele; } return ret; }
	sint ClearEleFromVec(std::vector<BOTF_CONN*> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { vec_->at(ele)->Clear(); ret = ele; } return ret; }
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
			else if (memb == BOT_FS_STRVEC)
			{
				vec_->at(ele).strvec.clear();
				ret = ele;
			}
			else if (memb == BOT_FS_OMODE)
			{
				vec_->at(ele).omode = -1;
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
			else if (memb == BOT_FS_STRVEC)
			{
				vec_->at(ele).strsiz = 0;
				ret = ele;
			}
			else if (memb == BOT_FS_OMODE)
			{
				vec_->at(ele).omode = -1;
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
		}
		return ret;
	}
	sint ClearEleFromVec(std::vector<TINFO_M> *vec_ = 0, sint ele = -1) { sint ret = -1; if (vec_ && ele > -1 && ele < (sint)vec_->size()) { TINFO_M ns; vec_->at(ele) = ns; ret = ele; } return ret; }
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
	sint CleanVec(std::vector<uchar> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UCHAR_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UCHAR_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == UCHAR_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<void*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { vec_->at(x) =vec_->at(y); sint z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (!vec_->at(siz)) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<std::chrono::steady_clock::time_point> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == vtclr) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != vtclr) { vec_->at(x) = vec_->at(y); sint z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == vtclr) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<sint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT_MIN) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<slint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT32_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT32_MIN) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT32_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<sllint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == INT64_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != INT64_MIN) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==INT64_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<uint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<ulint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT32_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT32_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT32_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<ullint> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == UINT64_MAX) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != UINT64_MAX) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz)==UINT64_MAX) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<float> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (vec_->at(x) == DBL_MIN) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y) != DBL_MIN) { sint z = SetValInVec(vec_, (sint)x, &vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } sint siz = (sint)vec_->size() - 1; while (siz > -1) { if (vec_->at(siz) == DBL_MIN) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
	sint CleanVec(std::vector<cchar*> *vec_ = 0, bool compactify = false) { if (!vec_) { return -1; } if (compactify && vec_->size() > 1) { for (size_t x = 0; x + 1 < vec_->size(); x++) { if (!vec_->at(x)) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } else { if (!strlen(vec_->at(x))) { for (size_t y = x + 1; y < vec_->size(); y++) { if (vec_->at(y)) { sint z = SetValInVec(vec_, (sint)x, vec_->at(y)); z = ClearEleFromVec(vec_, (sint)y); } } } } } } sint siz = vec_->size() - 1; while (siz > -1) { if (!strcmp(vec_->at(siz), "") || !strlen(vec_->at(siz))) { vec_->pop_back(); } else { siz = -1; } siz--; } return (sint)vec_->size(); }
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

	void SetTClr(std::chrono::steady_clock::time_point* nt = 0) { if (!nt) { vtclr = std::chrono::steady_clock::now(); } else { vtclr = *nt; } }

private:

	std::chrono::steady_clock::time_point vtclr;

};

	// start up strings

class bot_strt_up
{
public:

	std::vector<cchar* > litebot_stmts
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

	std::vector<cchar* > litebot_tablenames
	{
		"LAST_ACCESS",
		"COMMANDS",
		"ACCOUNTS",
		"LANGUAGES",
		"SYMS"
	};

	std::vector<cchar* > math_tablenames
	{
		"LAST_ACCESS",
		"ARITHMATIC",
		"ALGEBRA",
		"GEOMETRY",
		"TRIGONOMETRY",
		"CALCULUS"
	};

	std::vector<cchar* > code_tablenames
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

	std::vector<cchar* > word_tablenames
	{
		"LAST_ACCESS"
	};

	std::vector<cchar* > ex_tablenames
	{
		"LAST_ACCESS"
	};

	std::vector<cchar* > litebot_columns
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

	std::vector<cchar* > math_columns
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

	std::vector<cchar* > code_columns //add LANGUAGE TEXT column for language syntax code symbols.
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

	std::vector<cchar* > word_columns
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

	std::vector<cchar* > ex_columns
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

	// start up symbol vectors

	std::vector<cchar* > symbol_types
	{
		"enders",
		"vowels",
		"consonants",
		"number",
		"literal_encs",
		"literal_uncs",
		"order_encs",
		"order_uncs"
	};

	std::vector<cchar* > code_types
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
MTX_MAX = 14
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

class machine
{	
public:
	
	machine(sint i_debug_lvl = BOT_DEBUG_LVL, sint i_debug_m = BOT_DEBUG_M, sint nlid = -1, cchar* i_name = "", bool logmain = false, bool logmine = false)
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
			vtool.SetTClr(&bot_st);

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
		TINFO tts(0, ptn.c_str(), NULL, 0);
		tts.lid = lid;
		tts.fin = 0;
		tts.t_I = std::chrono::steady_clock::now();
		sint xc = PushToVec(&tts, MTX_TTS, true, true, false);

		if (do_start_up)
		{
			if (!ncar_)
			{
				return -1;
			}
			xc = LITEBotStartUp(ncar_);

			if (!xc)
			{
				xc = LITEBotProcess(ncar_);

				switch (xc)
				{
				case 1:
				{
					xc = bot_sprintf(ncar_->carr, ncar_->siz, "LITEBotProcess() fault.");
					xc = -1;
					break;
				}
				case 2:
				{
					xc = bot_sprintf(ncar_->carr, ncar_->siz, "LITEBotProcess() quit.");
					xc = 0;
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
				switch (xc)
				{
				case 1:
				{
					xc = bot_sprintf(ncar_->carr, ncar_->siz, "start up broken");
					xc = -2;
					break;
				}
				case 2:
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
		return 0;
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
	VTool vtool;
	std::vector<BOT_LOGDET> u_logs;
	DB_CONN* d_con_;
	std::vector<BOTF_CONN*> f_con;
	std::vector<lok_req> relocks;
	uint stk_ct;

	sint LITEBotStartUp(carr_256* ncar_ = 0)
	{
		if (!ncar_)
		{
			return -1;
		}

		sint xc = DoIntro();
		xc = VerifyDatabases();

		if (xc)
		{
			sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "VerifyDatabases fault. %i databases failed.", xc);
		}
		else
		{
			xc = TM(0);

			if (xc)
			{
				sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "ThreadMaintenance fault.");
			}
		}
		return xc;
	}
	sint LITEBotProcess(carr_256* ncar_ = 0)
	{
		if (!ncar_)
		{
			return -1;
		}
		sint xc = 0;

		while (!quit && !xc)
		{
			if (!VecSize(MTX_CV))
			{
				xc = DoLogin();
			}
			else
			{
				xc = Input();

				if (!quit && !xc)
				{
					xc = DoOutput();
				}
			}
		}

		if (quit)
		{
			xc = 2;
		}
		return xc;
	}
	
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
						return OpenFile(nele, r_opt, false, true);
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
									return CloseFile(nele, false);
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
							ns.Update(vp);
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
							ns.Update(vp);
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
							ns.Update(vp);
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
							ns.Update(vp);
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
							sint iret = -1;
							if (memb == BOT_FS_STRVEC)
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
				xval.Update(reinterpret_cast<BOT_CLIENT*>(val_));
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
				xval.Update(reinterpret_cast<BOT_LOGDET*>(val_));
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
				xval.Update(reinterpret_cast<BOT_DB*>(val_));
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
				xval.Update(reinterpret_cast<BOT_FILE*>(val_));
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
							ns.Update((BOT_CLIENT*)val_);
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
							ns.Update((BOT_LOGDET*)val_);
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
							ns.Update((BOT_DB*)val_);
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
							ns.Update((BOT_FILE*)val_);
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
							sint iret = -1;
							if (memb == BOT_FS_STRVEC)
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
					ret = GetVecEleMem(&r, g_opt, ele, BOT_FS_ID);
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
					ret = GetVecEleMem(&r, g_opt, ele, BOT_FS_ID);
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

	sint GetDateTimeMS(char str_[] = 0, bool form = true)
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
	sint GetDateTime(char str_[] = 0, bool form = true)
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
	sint GetTime(char str_[] = 0, bool forms = true)
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
	sint GetTimeMS(char str_[] = 0, bool forms = true)
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

	sint UsingLog(char nm[] = 0)
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
	sint LogPut(cchar* msg_ = "", sint option = -1)
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
	sint DoLogin();
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
			oc = StopAllThreads();
			xc = 0;
			quit = true;
			//exit( 1 );
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
						char dated[128]{ 0 };
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
						char dated[128]{ 0 };
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

			BOT_STMT t(false, 2, "litebot");
			sint rc = t.AddCont("COMMANDS", 1);
			rc = AddStrToVec(&t.cols, "COMMAND");
			rc = AddStrToVec(&t.vals, Uppercase(LEncStrI(vec_->at(1).c_str(), -1).c_str()).c_str());
			rc = AddStrToVec(&t.cols, "CMD_ID");
			rc = AddStrToVec(&t.vals, vec_->at(2).c_str());
			rc = AddStrToVec(&t.cols, "PRIV");
			rc = AddStrToVec(&t.vals, vec_->at(3).c_str());
			t.opts[0].push_back(2);
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
		char atdata[64] = { 0 };
		char mtdata[64] = { 0 };
		char ctdata[64] = { 0 };
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
				fpstr.append(ITOA((sint)strlen(file_->name.c_str())));
			}
		}
		else
		{
			fpstr.append(file_->path);
		}
#ifdef _WIN32
		errno_t aerr = gmtime_s(&atim, &file_->filestats.st_atime);
		errno_t merr = gmtime_s(&mtim, &file_->filestats.st_mtime);
		errno_t cerr = gmtime_s(&ctim, &file_->filestats.st_ctime);
#else
		atim = *gmtime((time_t*)&file_->filestats.st_atime);
		mtim = *gmtime((time_t*)&file_->filestats.st_mtime);
		ctim = *gmtime((time_t*)&file_->filestats.st_ctime);
#endif
		strftime(atdata, 64, "%m/%d/%Y %H:%M:%S", &atim);
		strftime(mtdata, 64, "%m/%d/%Y %H:%M:%S", &mtim);
		strftime(ctdata, 64, "%m/%d/%Y %H:%M:%S", &ctim);
		char instr[BOT_FILENAME_MAX + 1024] = { 0 };
		sint oc = bot_sprintf(instr, BOT_FILENAME_MAX + 1024, "FileStats:%s%s\nFilePath:\"%s\"\nSize:%llu\nSerialNum:%u\nLastAccessed:%s\nLastMod:%s\nLastChangeStatus:%s\nExists:%i", file_->name.c_str(), file_->type.c_str(), fpstr.c_str(), (ullint)file_->filestats.st_size, file_->filestats.st_ino, atdata, mtdata, ctdata, file_->exists);
		oc = Output(instr, 2);
		return 0;
	}
	sint ConMethod(BOT_FILE_M* val_ = 0)
	{
		if (!val_)
		{
			return -1;
		}

		if (val_->type.length() < 2)
		{
			return -1;
		}

		if (!strcmp(val_->type.c_str(), ".db"))
		{
			val_->cm = 1;
		}
		else
		{
			val_->cm = 2;
		}
		return 0;
	}
	sint GetOFConn(BOT_FILE_M* val_ = 0)
	{
		if (!val_)
		{
			return -1;
		}
		switch (val_->cm)
		{
		case 1:
		{
			BOT_DB_M ndb(val_->name.c_str());
			return GetODBConn(&ndb);
			break;
		}
		case 2:
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
	sint GetFConn(BOT_FILE_M* val_ = 0)
	{
		if (!val_)
		{
			return -1;
		}

		if (val_->omode < 0)
		{
			return -1;
		}

		sint ret = GetOFConn(val_);

		if (ret < 0)
		{
			switch (val_->cm)
			{
			case 1:
			{
				BOT_DB_M ndb(val_->name.c_str());
				ndb.omode = val_->omode;
				ret = GetDBConn(&ndb);
				break;
			}
			case 2:
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
		return ret;
	}
	sint CloseFConn(BOT_FILE_M* xfile_ = 0, bool clear_conn = true)
	{
		if (!xfile_)
		{
			return -1;
		}

		sint ret = GetOFConn(xfile_);

		switch (xfile_->cm)
		{
		case 1:
		{
			BOT_DB_M ndb(xfile_->name.c_str(), -1, xfile_->omode);
			sint x = 1;
			ret = CloseDB(&ndb, &x);
			break;
		}
		case 2:
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
	sint FileStats(BOT_FILE_M *file_ = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::FileStats(BOT_FILE_M *file_(%i))", (sint)file_);
			oc = Output(ncar.carr, 2);

			if (debug_lvl >= 10)
			{
				carr_512 xcar;
				oc = bot_sprintf(xcar.carr, xcar.siz, "%s%s%s", file_->path.c_str(), file_->name.c_str(), file_->type.c_str());
				oc = Output(xcar.carr, 2);
			}
		}
		if (!file_)
		{
			return -1;
		}
		if (file_->name.empty())
		{
			return -2;
		}

		sint ret = -1;
		std::string str;
		str.append(file_->path.c_str());
		str.append(file_->name.c_str());
		str.append(file_->type);

#ifdef _WIN32
		ret = _stat(str.c_str(), &file_->filestats);
#else
		ret = stat(str.c_str(), &file_->filestats);
#endif

		if (!ret)
		{
			if (file_->exists < 0)
			{
				file_->exists = 1;
			}

			BOT_FILE nf;
			nf.Renew(file_->name.c_str(), file_->type.c_str(), file_->path.c_str(), lid, file_->omode, file_->exists, file_->cm, file_->lid, &file_->filestats);
			ret = SetVecEle(&nf, MTX_FO, file_->lid, false, false);
			return 0;
		}
		return -1;
	}
	sint BOTCreateFile(BOT_FILE_M* file_ = 0, sint* was_open = 0)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_128 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTCreateFile(BOT_FILE_M *file_(%i), sint* was_open(%i))", (sint)file_, (sint)was_open);
			oc = Output(ncar.carr, 2);
		}
		if (!file_ || !was_open)
		{
			return -1;
		}

		sint ret = -1;

		switch (file_->cm)
		{
		case 1:
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
				}
			}
			break;
		}
		case 2:
		{
			if (file_->fcon > -1)
			{
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
	sint OpenFile(sint flid = -1, sint *was_open = 0, bool cine = false, bool r_to_st = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_512 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::OpenFile(sint flid(%i), sint *was_open(%i), bool cine(%u), bool r_to_st(%u))", flid, (sint)was_open, (uint)cine, (uint)r_to_st);
			oc = Output(ncar.carr, 2);
		}

		BOT_FILE_M nf;
		sint gc = GetVecEle((void*)&nf, MTX_FO, flid);

		if (gc < 0)
		{
			return -1;
		}
		return OpenFile(&nf, was_open, cine, r_to_st);
	}
	sint OpenFile(BOT_FILE_M* mfile_ = 0, sint *was_open = 0, bool cine = false, bool r_to_st = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_512 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "::OpenFile(BOT_FILE_M* mfile_(%i), sint *was_open(%i), bool cine(%u), bool r_to_st(%u))", (sint)mfile_, (sint)was_open, (uint)cine, (uint)r_to_st);
			oc = Output(ncar.carr, 2);
		}

		if (!mfile_ || !was_open)
		{
			return -10;
		}
		
		if (mfile_->lid < 0)
		{
			sint gc = GetInVec((void*)mfile_, MTX_FO);
		}
		else
		{
			sint gc = GetVecEle((void*)mfile_, MTX_FO, mfile_->lid);
		}
		
		if (mfile_->lid < 0)
		{
			BOT_FILE nfile(mfile_->name.c_str(), mfile_->type.c_str(), mfile_->path.c_str(), lid, mfile_->omode);
			sint gc = PushToVec((void*)&nfile, MTX_FO, true, true, false);

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

		if (!mfile_->path.empty())
		{
			if (mfile_->path[mfile_->path.length() - 1] != '\\')
			{
				mfile_->path.push_back('\\');
			}
		}

		sint gc = mfile_->name.find('.', 0);

		if (gc > 0)
		{
			if (mfile_->type.empty())
			{
				mfile_->type.append(mfile_->name.substr(gc, mfile_->name.length() - gc));
			}
			mfile_->name.erase(gc, mfile_->name.length() - gc);
		}

		if (mfile_->type.empty())
		{
			return -3;
		}
		else
		{
			MACSYM fc(5, (uchar*)mfile_->type.c_str(), 0);
			gc = AddCode(&fc);
		}

		gc = ConMethod(mfile_);
		gc = SetVecEleMem((void*)&mfile_->cm, MTX_FO, mfile_->lid, BOT_FS_CM, false);
		sint fc = GetOFConn(mfile_);

		if (fc < 0)
		{
			if (was_open)
			{
				*was_open = 0;
			}

			if (mfile_->cm != 1)
			{
				gc = 0;

				for (fc = GetFConn(mfile_); fc < 0 && gc < INT32_MAX; fc = GetFConn(mfile_))
				{
					slint rst = nsRest((slint)BOT_FO_REST);
					gc++;
				}

				if (fc < 0)
				{
					return -1;
				}
			}
			/*if (r_to_st)
			{
				BOT_FSTATE ofst;
				ofst.omode = f_con[*was_open]->omode;
				ofst.ia_loc = f_con[*was_open]->fstrm.tellg();
				ofst.oa_loc = f_con[*was_open]->fstrm.tellp();
				f_con[*was_open]->fstrm.seekg(f_con[*was_open]->fstrm.end);
				ofst.e_loc = f_con[*was_open]->fstrm.tellg();
				f_con[*was_open]->fstrm.seekg(ofst.ia_loc);
				f_con[*was_open]->fstrm.close();
			}*/
		}
		else
		{
			if (was_open)
			{
				*was_open = 1;
			}

			if (!r_to_st)
			{
				return mfile_->lid;
			}
		}

		sint xh = -1;
		sint lx = LockElement(MTX_FO, mfile_->lid, &xh, true, false);

		if (lx)
		{
			return -1;
		}

		gc = FileStats(mfile_);

		if (gc)
		{
			if (cine)
			{
				gc = BOTCreateFile(mfile_, was_open);

				if (gc > -1)
				{
					gc = FileStats(mfile_);

					if (gc)
					{
						return -1;
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

		if (S_ISREG(mfile_->filestats.st_mode))
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
			case 1:
			{
				BOT_DB_M ndb(mfile_->name.c_str());
				sint xh = 1;
				fc = OpenDB(&ndb, mfile_->omode, was_open, &xh);
				break;
			}
			case 2:
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
		else if (S_ISDIR(mfile_->filestats.st_mode))
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
		else if (S_ISCHR(mfile_->filestats.st_mode)) {}
		else if (S_ISBLK(mfile_->filestats.st_mode)) {}
		else if (S_ISFIFO(mfile_->filestats.st_mode)) {}
		else if (S_ISLNK(mfile_->filestats.st_mode)) {}
		else if (S_ISSOCK(mfile_->filestats.st_mode)) {}
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
	sint FileOut(sint fcon = -1, sint as_opt = 0, ...)
	{
		if (fcon < 0 || as_opt < 0)
		{
			return -1;
		}

		BOT_FILE_M nfile;
		sint ret = GetVecEle((void*)&nfile, MTX_FO, f_con[fcon]->flid);

		if (ret > -1)
		{
			boto_file = true;
			sint ud = UpdMTXPrio();

			switch (as_opt)
			{
			case 0:
			{
				va_list args;
				va_start(args, as_opt);
				bool done = false;

				while (!done)
				{
					uint val_ = va_arg(args, uint);
					uchar val = (uchar)val_;

					if (val)
					{
						if (nfile.cm == 2)
						{
							f_con[fcon]->fstrm << val << std::endl;
						}
					}
					else
					{
						done = true;
					}
				}
				va_end(args);
				ret = 0;
				break;
			}
			case 1:
			{
				if (nfile.cm == 2)
				{
					va_list args;
					va_start(args, as_opt);
					bool done = false;

					while (!done)
					{
						cchar* op_ = va_arg(args, cchar*);

						if (op_ != NULL)
						{
							size_t osiz = strlen(op_);

							if (osiz && osiz < BOT_STRLEN_MAX)
							{
								f_con[fcon]->fstrm << op_ << std::endl;
							}
						}
						else
						{
							done = true;
						}
					}
					va_end(args);
					ret = 0;
				}
				else if (nfile.cm == 1)
				{
					va_list args;
					va_start(args, as_opt);
					bool done = false;
					std::vector<BOT_STMT> tvec;

					while (!done)
					{
						cchar* op_ = va_arg(args, cchar*);

						if (op_ != NULL)
						{
							size_t osiz = strlen(op_);

							if (osiz && osiz < BOT_STRLEN_MAX)
							{
								BOT_STMT t;
								t.stmt.append(op_);
								tvec.push_back(t);
							}
						}
						else
						{
							done = true;
						}
					}
					va_end(args);
					ret = Commit(&tvec);
				}
				else {}
				break;
			}
			case 2:
			{
				if (nfile.cm == 2)
				{
					va_list args;
					va_start(args, as_opt);
					bool done = false;

					while (!done)
					{
						std::string str;
						str.append(va_arg(args, cchar*));

						if (!str.empty())
						{

							f_con[fcon]->fstrm << str.c_str() << std::endl;
							str.clear();
						}
						else
						{
							done = true;
						}
					}
					va_end(args);
					ret = 0;
				}
				else if (nfile.cm == 1)
				{
					std::vector<BOT_STMT> tvec;
					va_list args;
					va_start(args, as_opt);
					bool done = false;

					while (!done)
					{
						std::string str;
						str.append(va_arg(args, cchar*));

						if (!str.empty())
						{
							BOT_STMT t;
							t.stmt.append(str.c_str());
							tvec.push_back(t);
						}
						else
						{
							done = true;
						}
					}
					va_end(args);
					ret = Commit(&tvec);
				}
				break;
			}
			case 3:
			{
				if (nfile.cm == 2)
				{
					va_list args;
					va_start(args, as_opt);
					bool done = false;

					while (!done)
					{
						std::vector<std::string>* strvec = va_arg(args, std::vector<std::string>*);

						if (strvec)
						{
							if (!strvec->empty())
							{
								for (size_t siz = 0; siz < strvec->size(); siz++)
								{
									f_con[fcon]->fstrm << strvec->at(siz).c_str() << std::endl;
									strvec->at(siz).clear();
								}
								strvec->clear();
							}
						}
						else
						{
							done = true;
						}
					}
					va_end(args);
					ret = 0;
				}
				else if (nfile.cm == 1)
				{
					std::vector<BOT_STMT> tvec;
					va_list args;
					va_start(args, as_opt);
					bool done = false;

					while (!done)
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
						else
						{
							done = true;
						}
					}
					va_end(args);
					ret = Commit(&tvec);
				}
				else {}
				break;
			}
			default:
			{
				break;
			}
			}

			boto_file = false;
			ud = UpdMTXPrio();
		}
		return ret;
	}
	sint CloseFile(sint flid = -1, bool clear_conn = true, bool del = false, bool encr = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_2048 instr;
			sint oc = bot_sprintf(instr.carr, instr.siz, "::CloseFile(sint flid(%i), bool clear_conn(%u), bool del(%u), bool encr(%u))", flid, (uint)clear_conn, (uint)del, (uint)encr);
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
			return CloseFile(&xfile, clear_conn, del, encr);
		}
		return -1;
	}
	sint CloseFile(BOT_FILE_M* xfile_ = 0, bool clear_conn = true, bool del = false, bool encr = false)
	{
		if (debug_lvl >= 4 && debug_m)
		{
			carr_2048 instr;
			sint oc = bot_sprintf(instr.carr, instr.siz, "::CloseFile(BOT_FILE_M* xfile_(%i), bool clear_conn(%u), bool del(%u), bool encr(%u))", (sint)xfile_, (uint)clear_conn, (uint)del, (uint)encr);
			oc = Output(instr.carr, 2);
		}

		if (!xfile_)
		{
			return -1;
		}

		switch (xfile_->cm)
		{
		case 1:
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
		case 2:
		{
			sint fc = CloseFConn(xfile_, clear_conn);

			if (fc < 0)
			{
				return -1;
			}
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}

		if (xfile_->lid > -1)
		{
			sint p = FileStats(xfile_);
			p = vtool.ValInVec(&h_mtxs, MTX_FO);

			if (p > -1)
			{
				sint xp = p;
				p = vtool.ValInVec(&h_mtxs[xp].h_mems, xfile_->lid);

				if (p > -1)
				{
					return UnlockElement(MTX_FO, xfile_->lid, false);
				}
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
			if (!keep_mtx)
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
			if (!keep_mtx)
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
			std::chrono::duration<slint, std::milli> span = std::chrono::duration_cast<std::chrono::duration<slint, std::milli>>(t_II - t_I);
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
		std::chrono::duration<slint, std::milli> span = std::chrono::duration_cast<std::chrono::duration<slint, std::milli>>(t_II - t_I);
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
	sint Output(cchar* output_ = "", ...)
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
				str.append(va_arg(args, cchar*));
			}
			ret = BotOut(str.c_str());
		}
		return ret;
	}
	sint BotOut(cchar* str_ = "")
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
	sint Output(cchar* output_ = "", sint option = 0)
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
	sint InterpretInput(std::string *input_);
	sint DoIntro();
	sint DoGreeting();
	std::string DetermineOutput();
	sint GetName(std::string *str_);

	// Str Manip

	sint AddStrToVec(std::vector<std::string> *cvec_, cchar* str_, bool check = false, bool use_empty = false)
	{
		std::string str;
		sint ret = vtool.AddValToVec(cvec_, &str, check, use_empty);
		
		if (ret > -1)
		{
			if (!cvec_->at(ret).empty())
			{
				cvec_->at(ret).clear();
			}
			cvec_->at(ret).append(str_);
		}
		return ret;
	}
	sint AddStrToVec(std::vector<std::string> *cvec_, std::string* str_, bool check = false, bool use_empty = false) 
	{
		return vtool.AddValToVec(cvec_, str_, check, use_empty);
	}
	std::string CleanPunctuation(cchar* clientinput_ = "");
	std::string Uppercase(cchar* str_ = "");
	std::string LEncStrI(cchar* str_ = "", sint opt = -1)
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
	sint VToStr(std::vector<ullint>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
				char icar[64]{ 0 };
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
	sint VToStr(std::vector<ulint>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
				char icar[64]{ 0 };
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
	sint VToStr(std::vector<uint>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
				char icar[64]{ 0 };
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
	sint VToStr(std::vector<sllint>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
				char icar[64]{ 0 };
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
	sint VToStr(std::vector<slint>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
				char icar[64]{ 0 };
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
	sint VToStr(std::vector<sint>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
				char icar[64]{ 0 };
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
	sint VToStr(std::vector<cchar*>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
	sint VToStr(std::vector<std::string>* vec_ = 0, char instr_[] = 0, size_t i_siz = 0, cchar* sep = " ")
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
	std::string VToStr(std::vector<cchar*>* vec_, cchar* sep = " ")
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
	std::string VToStr(std::vector<std::string>* vec_, cchar* sep = " ")
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
	
	std::string ITOA(sint i) { std::string str = ""; char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%i", i); if (xc > -1) { str.append(ci); }	return str;	}
	std::string LITOA(slint i) { std::string str = ""; char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%li", i); if (xc > -1) { str.append(ci); } return str; }
	std::string LLITOA(sllint i) { std::string str = ""; char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%lli", i); if (xc > -1) { str.append(ci);	} return str; }
	std::string UTOA(uint i) { std::string str = ""; char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%u", i); if (xc > -1) { str.append(ci); } return str; }
	std::string LUTOA(ulint i) { std::string str = ""; char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%lu", i); if (xc > -1) { str.append(ci); } return str; }
	std::string LLUTOA(ullint i) { std::string str = ""; char ci[21]{ 0 }; sint xc = bot_sprintf(ci, 21, "%llu", i); if (xc > -1) { str.append(ci); } return str; }
	std::string DTOA(double i) { std::string str = ""; char ci[64]{ 0 }; sint xc = bot_sprintf(ci, 64, "%f", i); if (xc < 64 && xc > -1) { str.append(ci); } return str; }
	std::string LDTOA(long double i) { std::string str = ""; char ci[64]{ 0 }; sint xc = bot_sprintf(ci, 64, "%f", i); if (xc < 64 && xc > -1) { str.append(ci); } return str; }

	sint FindInStr(uchar f, const uchar* str, sint at, sint lim, bool fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindInStr(uchar f(%02X), const uchar* str(%i), sint at(%i), sint lim(%i) bool fwd(%u))", f, (sint)str, at, lim, (uint)fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && debug_m)
			{
				std::string xutp;
				xutp.append(reinterpret_cast<cchar*>(str));
				op = Output(xutp.c_str(), 2);
			}
		}
		sint flen = 1;
		sint slen = (sint)sizeof(*str);
		if (!slen)
		{
			if (debug_lvl >= 120 && debug_m)
			{
				sint op = Output("!slen(str)", 2);
			}
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
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("flen > slen || (fwd && *at > lim) || (!fwd && *at < lim)", 2);
			}
			return -1;
		}
		if (fwd)
		{
			while (at < slen && at <= lim)
			{
				sint siz = 0;

				while (siz < flen && at + siz <= lim)
				{
					if (f == str[at + siz])
					{
						if (debug_lvl >= 700 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at + siz);
							op = Output(outp.carr, 2);
						}
					}
					else
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
					if (f == str[at + siz])
					{
						if (debug_lvl >= 700 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at + siz);
							op = Output(outp.carr, 2);
						}
					}
					else
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
		if (debug_lvl >= 700 && debug_m)
		{
			sint op = Output("not found", 2);
		}
		return -1;
	}
	sint FindInStr(uchar f, uchar* str, sint at, sint lim, bool fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindInStr(uchar f(%02X), uchar* str(%i), sint at(%i), sint lim(%i) bool fwd(%u))", f, (sint)str, at, lim, (uint)fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && debug_m)
			{
				std::string xutp;
				xutp.append(reinterpret_cast<cchar*>(str));
				op = Output(xutp.c_str(), 2);
			}
		}
		sint flen = 1;
		sint slen = (sint)sizeof(*str);
		if (!slen)
		{
			if (debug_lvl >= 120 && debug_m)
			{
				sint op = Output("!slen(str)", 2);
			}
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
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("flen > slen || (fwd && *at > lim) || (!fwd && *at < lim)", 2);
			}
			return -1;
		}
		if (fwd)
		{
			while (at < slen && at <= lim)
			{
				sint siz = 0;

				while (siz < flen && at+siz <= lim)
				{
					if (f == str[at+siz])
					{
						if (debug_lvl >= 700 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at+siz);
							op = Output(outp.carr, 2);
						}
					}
					else
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
					at+=flen;
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
					if (f == str[at + siz])
					{
						if (debug_lvl >= 700 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at + siz);
							op = Output(outp.carr, 2);
						}
					}
					else
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
		if (debug_lvl >= 700 && debug_m)
		{
			sint op = Output("not found", 2);
		}
		return -1;
	}
	sint FindInStr(char f, cchar* str, sint at, sint lim, bool fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindInStr(char f(%c), cchar* str(%i), sint at(%i), sint lim(%i) bool fwd(%u))", f, (sint)str, at, lim, (uint)fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && str)
			{
				op = Output(str, 2);
			}
		}

		if (!str)
		{
			return -1;
		}

		sint flen = 1;
		sint slen = (sint)strlen(str);

		if (!slen)
		{
			if (debug_lvl >= 120 && debug_m)
			{
				sint op = Output("!slen(str)", 2);
			}
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
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("flen > slen || (fwd && *at > lim) || (!fwd && *at < lim)", 2);
			}
			return -1;
		}
		if (fwd)
		{
			while (at < (sint)strlen(str) && at <= lim)
			{
				if (f == str[at])
				{
					if (debug_lvl >= 700 && debug_m)
					{
						carr_64 outp;
						sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at);
						op = Output(outp.carr, 2);
					}
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
					if (debug_lvl >= 700 && debug_m)
					{
						carr_64 outp;
						sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at);
						op = Output(outp.carr, 2);
					}
					return at;
				}
				at--;
			}
		}
		if (debug_lvl >= 700 && debug_m)
		{
			sint op = Output("not found", 2);
		}
		return -1;
	}
	sint FindInStr(cchar* f, cchar* str, sint at, sint lim, bool fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindInStr(cchar* f(%i), cchar* str(%i), sint at(%i), sint lim(%i) bool fwd(%u))", (sint)f, (sint)str, at, lim, (uint)fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 120 && str)
			{
				op = Output(str, 2);
			}
		}

		if (!str)
		{
			return -1;
		}

		sint flen = (sint)strlen(f);
		sint slen = (sint)strlen(str);

		if (!slen)
		{
			if (debug_lvl >= 120 && debug_m)
			{
				sint op = Output("!slen(str)", 2);
			}
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
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("flen > slen || (fwd && *at > lim) || (!fwd && *at < lim)", 2);
			}
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
						if (debug_lvl >= 700 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at);
							op = Output(outp.carr, 2);
						}
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
						if (debug_lvl >= 700 && debug_m)
						{
							carr_64 outp;
							sint op = bot_sprintf(outp.carr, outp.siz, "found at:%i", at);
							op = Output(outp.carr, 2);
						}
						return at;
					}
				}
				at--;
			}
		}
		if (debug_lvl >= 120 && debug_m)
		{
			sint op = Output("not found", 2);
		}
		return -1;
	}
	sint FindVInStr(std::vector<std::string>* strvec_, std::string* str_, sint* loc, sint lim, sint* ele, sint ele_lim, bool fwd = true, bool v_fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindVInStr(vector<string>* strvec_(%i), string* str_(%i), sint* loc(%i), sint lim(%i), sint* ele(%i), sint ele_lim(%i), bool fwd(%u), bool v_fwd(%u))", (sint)strvec_, (sint)str_, (sint)loc, lim, (sint)ele, ele_lim, (uint)fwd, (uint)v_fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_->c_str(), 2);
			}
		}

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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting lim:%i to %i", lim, nlim);
				op = Output(outp.carr, 2);
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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting ele_lim:%i to %i", ele_lim, nlim);
				op = Output(outp.carr, 2);
			}
			ele_lim = nlim;
		}

		if (*loc >= (sint)str_->length())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "%i >= (sint)strlen(str_)", *loc);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if (strvec_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("cvec_->empty()", 2);
			}
			*loc = -1;
			return -1;
		}
		else if (str_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("(str_->empty())", 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((fwd && *loc > lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) > lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!fwd && *loc < lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) < lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((v_fwd && *ele > ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) > ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!v_fwd && *ele < ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) < ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else {}

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
		if (debug_lvl >= 700 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "returning %i", ret);
			op = Output(outp.carr, 2);
		}
		*loc = ret;
		return ret;
	}
	sint FindVInStr(std::vector<char>* cvec_, std::string* str_, sint* loc, sint lim, sint* ele, sint ele_lim, bool fwd = true, bool v_fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindVInStr(vector<char>* cvec_(%i), string* str_(%i), sint* loc(%i), sint lim(%i), sint* ele(%i), sint ele_lim(%i), bool fwd(%u), bool v_fwd(%u))", (sint)cvec_, (sint)str_, (sint)loc, lim, (sint)ele, ele_lim, (uint)fwd, (uint)v_fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_->c_str(), 2);
			}
		}

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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting lim:%i to %i", lim, nlim);
				op = Output(outp.carr, 2);
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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting ele_lim:%i to %i", ele_lim, nlim);
				op = Output(outp.carr, 2);
			}
			ele_lim = nlim;
		}

		if (*loc >= (sint)str_->length())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "%i >= (sint)str_->length())", *loc);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if (cvec_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("cvec_->empty()", 2);
			}
			*loc = -1;
			return -1;
		}
		else if (str_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("str_->empty()", 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((fwd && *loc > lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) > lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!fwd && *loc < lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) < lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((v_fwd && *ele > ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) > ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!v_fwd && *ele < ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) < ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else {}

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
		if (debug_lvl >= 700 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "returning %i", ret);
			op = Output(outp.carr, 2);
		}
		*loc = ret;
		return ret;
	}
	sint FindVInStr(std::vector<cchar*>* cvec_, cchar* str_, sint* loc, sint lim, sint* ele, sint ele_lim, bool fwd = true, bool v_fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindVInStr(vector<cchar*>* strvec_(%i), cchar* str_(%i), sint* loc(%i), sint lim(%i), sint* ele(%i), sint ele_lim(%i), bool fwd(%u), bool v_fwd(%u))", (sint)cvec_, (sint)str_, (sint)loc, lim, (sint)ele, ele_lim, (uint)fwd, (uint)v_fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_, 2);
			}
		}

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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting lim:%i to %i", lim, nlim);
				op = Output(outp.carr, 2);
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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting ele_lim:%i to %i", ele_lim, nlim);
				op = Output(outp.carr, 2);
			}
			ele_lim = nlim;
		}

		if (*loc >= slen)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "%i >= (sint)strlen(str_)", *loc);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if (cvec_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("cvec_->empty()", 2);
			}
			*loc = -1;
			return -1;
		}
		else if (!slen)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("!strlen(str_)", 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((fwd && *loc > lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) > lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!fwd && *loc < lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) < lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((v_fwd && *ele > ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) > ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!v_fwd && *ele < ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) < ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else {}

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
		if (debug_lvl >= 700 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "returning %i", ret);
			op = Output(outp.carr, 2);
		}
		*loc = ret;
		return ret;
	}
	sint FindVInStr(std::vector<char>*cvec_, cchar* str_, sint* loc, sint lim, sint* ele, sint ele_lim, bool fwd = true, bool v_fwd = true)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::FindVInStr(vector<char>* strvec_(%i), cchar* str_(%i), sint* loc(%i), sint lim(%i), sint* ele(%i), sint ele_lim(%i), bool fwd(%u), bool v_fwd(%u))", (sint)cvec_, (sint)str_, (sint)loc, lim, (sint)ele, ele_lim, (uint)fwd, (uint)v_fwd);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 720 && str_)
			{
				op = Output(str_, 2);
			}
		}

		sint slen = (sint)strlen(str_);

		if (lim < 0)
		{
			sint nlim = 0;

			if (fwd)
			{
				nlim = slen - 1;
			}
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting lim:%i to %i", lim, nlim);
				op = Output(outp.carr, 2);
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
			if (debug_lvl >= 120 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "adjusting ele_lim:%i to %i", ele_lim, nlim);
				op = Output(outp.carr, 2);
			}
			ele_lim = nlim;
		}

		if (*loc >= slen)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "%i >= (sint)strlen(str_)", *loc);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if (cvec_->empty())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("cvec_->empty()", 2);
			}
			*loc = -1;
			return -1;
		}
		else if (!slen)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				sint op = Output("!strlen(str_)", 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((fwd && *loc > lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) > lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!fwd && *loc < lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "fwd(%u) && *loc(%i) < lim(%i)", (uint)fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((v_fwd && *ele > ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) > ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else if ((!v_fwd && *ele < ele_lim))
		{
			if (debug_lvl >= 700 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "v_fwd(%u) && *loc(%i) < ele_lim)(%i)", (uint)v_fwd, *loc, lim);
				op = Output(outp.carr, 2);
			}
			*loc = -1;
			return -1;
		}
		else {}

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
		if (debug_lvl >= 700 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "returning %i", ret);
			op = Output(outp.carr, 2);
		}
		*loc = ret;
		return ret;
	}
	sint OrdLocs(std::vector<size_t>* litlocs_ = 0, std::vector<size_t>* locs_ = 0, cchar* str_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::OrdLocs(vector<size_t>* litlocs_(%i), vector<size_t>* locs_(%i), cchar* str_(%u))", (sint)litlocs_, (sint)locs_, (sint)str_);
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
				sint oc = VToStr(locs_, nump.carr, nump.siz);
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
	sint OrdEnc(size_t at_loc = 0, std::vector<size_t>* litlocs_ = 0, std::vector<size_t>* locs_ = 0, cchar* str_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::OrdEnc(size_t at_loc(%u), vector<size_t>* litlocs_(%i), vector<size_t>* locs_(%i), cchar* str_(%i))", at_loc, (sint)litlocs_, (sint)locs_, (sint)str_);
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
	sint LitLocs(std::vector<size_t>* locs_, cchar* str_)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::LitLocs(vector<size_t>* locs_(%i), cchar* str_(%i))", (sint)locs_, (sint)str_);
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
				sint oc = VToStr(locs_, nump.carr, nump.siz);
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
	sint LitEnc(size_t at_loc, std::vector<size_t>* locs_, cchar* str_)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::LitEnc(size_t at_loc(%u), vector<size_t>* locs_(%i), cchar* str_(%i))", at_loc, (sint)locs_, (sint)str_);
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
								sint op = bot_sprintf(outp.carr, outp.siz, "closer is our char at:%i opens:%i", x_loc, opens);
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
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is before our char at:%i opens:%i", x_loc, opens);
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
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is after our char at:%i opens:%i", nloc, opens);
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

	bool XEnclosedInY(std::vector<size_t>* litlocs_ = 0, cchar* statements_ = "", sint sc_loc = -1, sint x_loc = -1, char fy_char = '\0')
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

		char by_char;

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
		sint fy_loc = FindInStr(fy_char, statements_, old_fy_loc + 1, sc_loc, true);

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

				by_loc = FindInStr(by_char, statements_, fy_loc + 1, true);
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
								sint op = bot_sprintf(outp.carr, outp.siz, "closer is our char at:%i opens:%i", x_loc, opens);
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
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is before our char at:%i opens:%i", x_loc, opens);
										op = Output(outp.carr, 2);
									}
									nloc = FindInStr(by_char, statements_, by_loc + 1, true);
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
										sint op = bot_sprintf(outp.carr, outp.siz, "closer is after our char at:%i opens:%i", nloc, opens);
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
								nloc = FindInStr(by_char, statements_, by_loc + 1, true);
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
			fy_loc = FindInStr(fy_char, statements_, fy_loc + 1, true);
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

	sint SeparateStrByStr(std::string *str_ = 0, std::string *sstr_ = 0, std::vector<std::string> *rvec_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrByStr(std::string *str_(%i), std::string *sstr_(%i), std::vector<std::string> *rvec_(%i))", (sint)str_, (sint)sstr_, (sint)rvec_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 700)
			{
				op = Output(str_->c_str(), 2);
			}
		}

		if (!str_ || !sstr_ || !rvec_)
		{
			return -1;
		}

		size_t x = 0;

		for (size_t sx = 0; sx < str_->length(); sx++)
		{
			if (sx + sstr_->length() < str_->length())
			{
				if (debug_lvl >= 700 && debug_m)
				{
					carr_128 ncar;
					sint op = bot_sprintf(ncar.carr, ncar.siz, "comparing \"%s\" vs \"%s\"", sstr_->c_str(), str_->substr(sx, sstr_->length()).c_str());
					op = Output(ncar.carr, 2);
				}

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
		
		if (debug_lvl >= 700 && debug_m)
		{
			std::string output;
			for (size_t r = 0; r < rvec_->size(); r++)
			{
				output.append("\n");
				output.append(rvec_->at(r));
			}
			sint xc = Output(output.c_str(), 2);
		}
		return 0;
	}
	sint SeparateStrByCChar(cchar *str_ = "", cchar *sstr_ = "", std::vector<std::string> *rvec_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrByCChar(cchar *str_(%i), cchar *sstr_(%i), std::vector<std::string> *rvec_(%i))", (sint)str_, (sint)sstr_, (sint)rvec_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 700 && str_)
			{
				op = Output(str_, 2);
			}
		}
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
					if (debug_lvl >= 700 && debug_m)
					{
						std::string output;

						for (size_t xs = sx; xs < sslen; xs++)
						{
							output.push_back(str_[xs]);
						}
						carr_128 ncar;
						sint op = bot_sprintf(ncar.carr, ncar.siz, "comparing \"%s\" vs \"%s\"", sstr_, output.c_str());
						op = Output(ncar.carr, 2);
					}

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

		if (debug_lvl >= 700 && debug_m)
		{
			std::string output;
			for (size_t r = 0; r < rvec_->size(); r++)
			{
				output.append("\n");
				output.append(rvec_->at(r));
			}
			sint xc = Output(output.c_str(), 2);
		}

		return 0;
	}
	sint SeparateStrByChar(cchar *str_ = "", char chr = ' ', std::vector<std::string> *rvec_ = 0)
	{
		if (debug_lvl >= 700 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrByChar(cchar *str_(%i), char chr(%i), std::vector<std::string> *rvec_(%i))", (sint)str_, (sint)chr, (sint)rvec_);
			op = Output(outp.carr, 2);

			if (debug_lvl >= 700 && str_)
			{
				op = Output(str_, 2);
			}
		}

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
			if (debug_lvl >= 700 && debug_m)
			{
				carr_128 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "comparing '%c' vs '%c'", chr, str_[sx]);
				xp = Output(ncar.carr, 2);
			}

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

		if (debug_lvl >= 700 && debug_m)
		{
			std::string output;
			for (uint r = 0; r < rvec_->size(); r++)
			{
				output.append(rvec_->at(r));
				output.append("\n");
			}
			sint xc = Output(output.c_str(), 2);
		}
		return 0;
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
			sint findx = FindVInStr(&sql_trans_keywords, t_->stmt.c_str(), &x, lim, &ele, lim);

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
		sint findx = FindVInStr(&sql_cspec_keywords, t_->stmt.c_str(), &spec_loc, lim, &ele, lim);
		findx = FindVInStr(&sql_obj_qual_keywords, t_->stmt.c_str(), &x, lim, &ele, lim);

		if (x > -1)
		{
			t_->opts[1].push_back(ele);
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
					findx = FindVInStr(&sql_cond_qual_keywords, snip.c_str(), &altx, lim, &ele, lim);

					if (altx > -1)
					{
						t_->opts[7].push_back(ele);
						altx += (sint)strlen(sql_cond_qual_keywords[ele]);
						x = altx;
						findx = FindVInStr(&sql_create_cond_keywords, snip.c_str(), &altx, lim, &ele, lim);

						if (altx > -1)
						{
							t_->opts[8].push_back(x);
							altx += (sint)strlen(sql_create_cond_keywords[ele]);
							x = altx;
						}
					}
					else
					{
						altx = x;
					}

					findx = FindVInStr(&sql_obj_keywords, snip.c_str(), &altx, lim, &ele, lim);

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

				findx = FindVInStr(&sql_targ_keywords, snip.c_str(), &altx, lim, &ele, lim);

				if (altx > -1)
				{
					t_->opts[0].push_back(ele);
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
									findx = FindVInStr(&sql_opers_keywords, snip.c_str(), &nloc, lim, &ele, lim);

									if (nloc > altx)
									{
										//if (ele == 4)
										//{
										//	snip.find(sql_opers_keywords[5], nloc + 1);
										//}
									}
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
							str.append(snip.substr(0, altx));
							CleanPunctuation(str.c_str());
							t_->AddDB(str.c_str());
						}

						if (altx + 1 < (sint)snip.length())
						{
							sint loc = snip.find('[', altx + 1);

							if (loc > -1)
							{
								loc = snip.find(']', altx + 1);

								if (loc > -1)
								{
									cont_name.append(snip.substr(altx + 1, loc - (altx + 1)));
								}
								else
								{
									sint ix = altx + 1;
									findx = FindVInStr(&sql_opers_keywords, &snip, &ix, lim, &ele, lim);

									if (ix > -1)
									{
										std::string str;
										str.append(snip.substr(altx + 1, ix - (altx + 1)));
										CleanPunctuation(str.c_str());
										cont_name.append(str);
									}
								}
							}
							else
							{
								sint ix = altx + 1;
								findx = FindVInStr(&sql_opers_keywords, &snip, &ix, lim, &ele, lim);

								if (ix > -1)
								{
									std::string str;
									str.append(snip.substr(altx + 1, ix - (altx + 1)));
									CleanPunctuation(str.c_str());
									cont_name.append(str);
								}
								else
								{
									std::string str;
									str.append(snip.substr(altx + 1, (sint)snip.length() - (altx + 1)));
									CleanPunctuation(str.c_str());
									cont_name.append(str);
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
									cont_name.append(snip.substr(1, snip.length() - 2));
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
					findx = FindVInStr(&sql_cspec_keywords, snip.c_str(), &cloc, lim, &ele, lim);
					std::string cont_name;
					altx = snip.find('[', x + 1);

					if (altx > -1 && (altx < spec_loc || spec_loc == -1))
					{
						sint ex = snip.find(']', altx + 1);

						if (ex > -1)
						{
							cont_name.append(snip.substr(altx + 1, ex - (altx + 1)));
						}
						else
						{
							ex = altx + 1;
							findx = FindVInStr(&sql_opers_keywords, &snip, &ex, lim, &ele, lim);

							if (ex > -1)
							{
								cont_name.append(snip.substr(altx + 1, ex - (altx + 1)));
							}
						}
					}
					else
					{
						altx = x + 1;
						findx = FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);

						if (altx > -1 && altx != cloc)
						{
							cont_name.append(snip.substr(x + 1, altx - (x + 1)));
							CleanPunctuation(cont_name.c_str());
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
								cont_name.append(snip.substr(1, snip.length() - 2));
								dx = -1;
							}
						}

						sint dx = t_->AddCont(cont_name.c_str(), 1);
					}
				}

				findx = FindVInStr(&sql_cspec_keywords, snip.c_str(), &altx, lim, &ele, lim);

				if (altx > -1)
				{
					spec_loc = at_loc + altx;
					t_->opts[0].push_back(ele);
					altx += (sint)strlen(sql_cspec_keywords[ele]);
					x = altx;

					if (ele == 0)
					{
						while (altx > -1)
						{
							findx = FindVInStr(&sql_comp_keywords, snip.c_str(), &altx, lim, &ele, lim);

							if (altx > -1)
							{
								t_->cols.push_back(snip.substr(x + 1, altx - (x + 1)));
								t_->opts[1].push_back(ele);
								altx += (sint)strlen(sql_comp_keywords[ele]);
								x = altx;

								if (ele == 0)
								{
									altx = snip.find("AND", altx + 1);

									if (altx > -1)
									{
										t_->vals.push_back(snip.substr(x, altx - x));
										altx += 3;
										x = altx;
										findx = FindVInStr(&sql_comp_keywords, snip.c_str(), &altx, lim, &ele, lim);

										if (altx > -1)
										{
											t_->vals.push_back(snip.substr(x, altx - x));
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
							}
							else
							{
								altx = x;
							}

							findx = FindVInStr(&sql_conj_keywords, snip.c_str(), &altx, lim, &ele, lim);

							if (altx > -1)
							{
								t_->opts[3].push_back(ele);

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

								altx += (sint)strlen(sql_conj_keywords[ele]);
								x = altx;
							}
						}
					}
					else if (ele == 1)
					{
						if (t_->it_type == 3)
						{

						}
						else if (t_->it_type == 9)
						{
							findx = FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);

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
						if (debug_lvl >= 110 && debug_m)
						{
							sint oc = Output("pushing VALUES to opts", 2);
						}
						t_->opts[0].push_back(ele);
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
						findx = FindVInStr(&sql_cspec_keywords, snip.c_str(), &x, lim, &ele, lim); // needs sint pointers for which vector member and location in str

						if (x > -1)
						{
							if (LitEnc(x, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, x, sql_opers_keywords[6]))
							{
								spec_loc = at_loc + x;
								x += (sint)strlen(sql_cspec_keywords[ele]);
								t_->opts[0].push_back(ele);

								if (ele == 0)
								{
									findx = FindVInStr(&sql_opers_keywords, &snip, &x, lim, &ele, lim);

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
													str.append(snip.substr(x, nloc - x));
													x = nloc + 1;
													findx = FindVInStr(&sql_comp_keywords, snip.c_str(), &x, lim, &ele, lim, true, false);

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
													for (nloc = FindInStr(sql_opers_keywords[6], snip.c_str(), nloc, lim); nloc > -1; )
													{
														if (LitEnc(x, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, x, sql_opers_keywords[6]))
														{
															vtool.AddValToVec(&t_->conds, snip.substr(nloc, x - nloc).c_str(), false, false);
															nloc = -1;
														}
														else
														{
															nloc--;
															nloc = FindInStr(sql_opers_keywords[6], snip.c_str(), nloc, lim);
														}
													}
												}
												else
												{
													for (nloc = snip.find(sql_opers_keywords[7], nloc + 1); nloc > -1; )
													{
														if (LitEnc(x, &litlocs, snip.c_str()) && !XEnclosedInY(&litlocs, snip.c_str(), (sint)snip.length() - 1, x, sql_opers_keywords[6]))
														{
															AddStrToVec(&t_->conds, snip.substr(nloc, x - nloc).c_str());
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
												AddStrToVec(&t_->conds, ncar.c_str());

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
										findx = FindVInStr(&sql_opers_keywords, &snip, &x, lim, &ele, lim);

										if (x < (sint)snip.length())
										{
											sint clox = x + 1;
											findx = FindVInStr(&sql_conj_keywords, snip.c_str(), &clox, lim, &ele, lim);

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

										findx = FindVInStr(&sql_opers_keywords, &snip, &x, lim, &ele, lim);
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
											cont_name.append(snip.substr(1, snip.length() - 2));
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
					// if t_->opts[0] is not empty and we are past last_targ_loc and spec_loc we can assume these () contain a condition
					if (snip[snip.length() - 1] == ')')
					{
						if (!t_->opts[0].empty())
						{
							if (t_->opts[0][0] == 0)
							{
								if (strlen(snip.c_str()) < 1024)
								{
									sint xp = AddStrToVec(&t_->conds, snip.c_str());
								}
								x = (sint)snip.length() - 1;
							}
							else
							{
								std::string str;
								str.append(snip.substr(1, snip.length() - 2));
								snip.clear();
								snip.append(str);
							}
						}
						else
						{
							std::string str;
							str.append(snip.substr(1, snip.length() - 2));
							snip.clear();
							snip.append(str);
						}

						if (debug_lvl >= 110 && debug_m)
						{
							std::string output;
							if (!t_->opts[0].empty())
							{
								if (t_->opts[0][0] > 0)
								{
									output.append("snipped () at ends");
								}

								output.append(" t_->opts[0] is not empty");
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

					findx = FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);

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
									sint locx = FindInStr(sql_opers_keywords[6], snip.c_str(), altx - 1, lim);

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
							findx = FindVInStr(&sql_opers_keywords, &snip, &altx, lim, &ele, lim);
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
					snip.append(t_->stmt.substr(o_locs[xv] + 1, o_locs[yv] - (o_locs[xv] + 1)));
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
			carr_128 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "::BQS(BOT_STMT *t_(%i))", (sint)t_);
			oc = Output(outp.carr, 2);
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
			return 1;
		}

		if (!t_->stmt.empty())
		{
			//	BOT_STMT t;
			//	t.stmt.append( t_->stmt );
			//	sint xc = AnalyzeStmt(&t );

			//compare t to t_ yada...
			t_->stmt.clear();
		}

		std::string statement;
		statement.append("SELECT ");

		sint x = 0;

		if (!t_->cols.size())
		{
			statement.append("*");
		}
		else
		{
			if (!strcmp(t_->cols[x].c_str(), ""))
			{
				statement.append("*");
				x++;
			}
			else if (t_->cols.size() > t_->vals.size())
			{
				for (sint xmax = (sint)(t_->cols.size() - t_->vals.size()); x < xmax; x++)
				{
					statement.append(t_->cols[x]);
					statement.append(", ");
				}

				statement.erase((sint)statement.length() - 2, 2);
			}
			else
			{
				statement.append("*");
			}
		}

		statement.append(" FROM ");

		if (!t_->ic_types.empty())
		{
			if (t_->ic_types[0] == 1)
			{
				if (d_con_)
				{
					if (strcmp(t_->dbname.c_str(), d_con_->name.c_str()))
					{
						statement.append(t_->dbname);
						statement.append(".");
					}
					if (!t_->tables.empty())
					{
						statement.append("[");
						statement.append(t_->tables[0]);
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
					if (!t_->tables.empty())
					{
						statement.append("[");
						statement.append(t_->tables[0]);
						statement.append("]");
					}
				}
			}
			else { return -1; }
		}
		else { return 1; }

		statement.append(" ");

		if (!t_->opts[0].empty() && (!t_->vals.empty() || !t_->cols.empty() || !t_->conds.empty()))
		{
			statement.append(sql_cspec_keywords[t_->opts[0][0]]);
			statement.append(" ");

			if (!t_->conds.empty())
			{
				for (uint xc = 0; xc < t_->conds.size(); xc++)
				{
					statement.append(t_->conds[xc]);

					if (xc < t_->opts[3].size())
					{
						statement.append(" ");
						statement.append(sql_conj_keywords[t_->opts[3][xc]]);
					}
					statement.append(" ");
				}
			}

			uint y = 0;
			uint z = 0;
			for (uint xc = 0; xc < t_->vals.size() && x < (sint)t_->cols.size(); xc++)
			{
				statement.append(t_->cols[x]);
				x++;

				if (!t_->opts[1].empty())
				{
					if (y < t_->opts[1].size())
					{
						statement.append(" ");
						statement.append(sql_comp_keywords[t_->opts[1][y]]);
						y++;
					}
				}
				statement.append(" ");
				statement.append(t_->vals[xc]);

				if (!t_->opts[3].empty())
				{
					if (z < t_->opts[3].size())
					{
						statement.append(sql_conj_keywords[t_->opts[3][z]]);
						statement.append(" ");
						z++;
					}
				}
			}
		}

		if (!t_->opts[5].empty() && x < (sint)t_->cols.size())
		{
			statement.append("ORDER BY ");
			statement.append(t_->cols[x]);
			x++;

			if (t_->opts[5][0])
			{
				statement.append(" { ASC }");
			}
			else
			{
				statement.append(" { DESC }");
			}
		}

		if (!t_->opts[6].empty())
		{
			statement.append(" LIMIT ");
			statement.append(ITOA(t_->opts[6][0]));
		}

		if (!statement.empty())
		{
			while (statement[statement.size() - 1] == ' ')
			{
				statement.pop_back();
			}
			statement.append(";");
			t_->stmt.append(statement);

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
		//t_->stmt.append( sql_trans_keywords[ t_->it_type ] );
		statement.append(sql_trans_keywords[t_->it_type]);

		if (!t_->ic_types.empty())
		{
			uint t = 0;
			while (t < t_->ic_types.size())
			{
				if (t_->ic_types[0] != t_->ic_types[t] && t_->ic_types[t] > -1 && t_->ic_types[0] > -1)
				{
					t = t_->ic_types.size();
				}
				t++;
			}
			if (t > t_->ic_types.size())
			{
				if (debug_lvl >= 1 && debug_m)
				{
					t = Output("multiple container types", 2);
				}
				return 1;
			}
		}

		if (t_->it_type == 3 || t_->it_type == 5 || t_->it_type == 7)
		{
			if (!t_->opts[1].empty())
			{
				statement.append(" ");
				statement.append(sql_obj_qual_keywords[t_->opts[1][0]]);
			}

			statement.append(" ");
			statement.append(sql_obj_keywords[t_->ic_types[0]]);
		}

		if (!t_->opts[7].empty())
		{
			if (!t_->opts[8].empty())
			{
				statement.append(" ");
				statement.append(sql_cond_qual_keywords[t_->opts[8][0]]);
			}

			statement.append(" ");
			statement.append(sql_create_cond_keywords[t_->opts[7][0]]);
		}

		if (t_->it_type == 4 && t_->ic_types[0] > 1)
		{
			statement.append(" ");
			statement.append(sql_trans_spec_keywords[0]);
		}

		if (t_->tables.empty())
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
			uint tx = 0;
			while (tx < t_->tables.size())
			{
				statement.append(" ");

				if (d_con_)
				{
					if (!strcmp(t_->dbname.c_str(), d_con_->name.c_str()))
					{
						sint fx = t_->tables[tx].find('.', 0);

						if (fx > -1)
						{
							fx++;
							std::string str;
							str.append(t_->tables[tx].substr(fx, t_->tables[tx].length() - fx));
							t_->tables[tx].clear();
							t_->tables[tx].append(str.c_str());
						}
					}
					else
					{
						statement.append(t_->dbname);
						statement.append(".");
					}
				}
				if (t_->ic_types[tx] > 0)
				{
					if (strlen(t_->tables[tx].c_str()))
					{
						std::string s;

						if (t_->tables[tx][0] != '[')
						{
							if (t_->ic_types[tx] == 2)
							{
								s.append("[IDX");
							}
							else
							{
								s.push_back('[');
							}
						}

						s.append(t_->tables[tx]);

						if (t_->tables[tx][(sint)strlen(t_->tables[tx].c_str()) - 1] != ']')
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
						carr_256 outp;
						sint op = bot_sprintf(outp.carr, outp.siz, "Could not find tablename \"%s\" in vectors.", t_->tables[0].c_str());
						op = Output(outp.carr, 1, 2, -1);
						return 1;
					}
				}
				else
				{
					if (!strlen(t_->dbname.c_str()) && !strlen(t_->tables[tx].c_str())) { return 1; }
					else if (!strlen(t_->dbname.c_str()) && strlen(t_->tables[tx].c_str())) {}
					else if (!strlen(t_->tables[tx].c_str()) && strlen(t_->dbname.c_str())) {}
					else {}
				}

				if (t_->it_type == 6)
				{
					statement.pop_back();
				}

				if (t_->it_type == 3 && t_->ic_types[tx] == 2)
				{
					statement.append(" ");
					statement.append(sql_trans_spec_keywords[1]);
					statement.append(" [");
					statement.append(t_->tables[tx]);
					statement.append("]");
				}
				tx++;
			}

			if (t_->it_type < 4)
			{
				if (t_->it_type < 3)
				{
					if (t_->maint)
					{
						if (t_->ic_types[0] > 0)
						{
							sllint xc = GetCentSec();
							sint xp = t_->AddCol("LAST_MAINTAINED", LLITOA(xc).c_str());
						}

						if (t_->it_type != 3 && t_->ic_types[0] > 0)
						{
#ifdef _WIN32
							SYSTEMTIME tim; // use chrono
							GetSystemTime(&tim);
							sint xc = t_->AddCol("LAST_MAINTAINED_NS", LLITOA(tim.wMilliseconds * 1000000).c_str());
#else
							struct timespec ti;
							sint xc = clock_gettime(CLOCK_REALTIME, &ti);
							t_->vals.push_back(LLITOA(ti.tv_nsec));
#endif
						}
					}
					else
					{
						if (t_->ic_types[0] > 0)
						{
							sllint xc = GetCentSec();
							sint xp = t_->AddCol("LAST_MODIFIED", LLITOA(xc).c_str());
						}

						if (t_->ic_types[0] > 0)
						{
#ifdef _WIN32
							SYSTEMTIME tim;
							GetSystemTime(&tim);
							sint xc = t_->AddCol("LAST_MODIFIED_NS", LLITOA(tim.wMilliseconds * 1000000).c_str());
#else
							struct timespec ti;
							sint xc = clock_gettime(CLOCK_REALTIME, &ti);
							statement.append(LLITOA(ti.tv_nsec));
#endif
						}
					}
				}
				else if (t_->it_type == 3)
				{
					if (t_->cols.size())
					{
						statement.append(" ( ");
						sint x = 0;

						while (x < (sint)t_->cols.size())
						{
							statement.append(t_->cols[x]);
							statement.append(" ");

							if (t_->ic_types[tx - 1] == 2)
							{
								statement.pop_back();
								statement.append(", ");
							}

							if (x < (sint)t_->vals.size())
							{
								if (t_->ic_types[tx - 1] != 2)
								{
									statement.append(t_->vals[x]);
									statement.append(", ");
								}
							}
							x++;
						}
						statement.erase((sint)statement.length() - 2, 2);
						statement.append(" )");
					}
				}
				else {}
			}

			if (t_->opts[9].size())
			{
				statement.append(" ");
				statement.append(sql_act_keywords[t_->opts[9][0]]);

				if (t_->it_type == 7)
				{
					if (t_->ic_types[0] == 1 && t_->opts[9][0] == 1)
					{
						statement.append(" TABLE");
					}
					else if (t_->ic_types[0] == 2 && t_->opts[9][0] == 0)
					{
						statement.append(" COLUMN");
					}
					else if (t_->ic_types[0] == 4)
					{
						statement.append(" TRIGGER");
					}
					else {}
				}

				sint x = 0;

				switch (t_->opts[9][0])
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

			if (t_->opts[0].size())
			{
				if (t_->opts[0][0] == 0)
				{
					statement.append(" ");
					statement.append(sql_cspec_keywords[t_->opts[0][0]]);
					sint x = 0;
					sint xmax = (sint)t_->cols.size();

					if ((sint)t_->opts[2].size() && x < xmax)
					{
						statement.append(" ");
						statement.append(t_->cols[x]);
						statement.append(" ");
						statement.append(sql_comp_keywords[t_->opts[2][0]]);
					}

					x = 0;
					xmax = (sint)t_->conds.size();

					if (xmax)
					{
						if (t_->opts[3].size())
						{
							uint t = 0;

							while (x < xmax)
							{
								statement.append(" ");
								statement.append(t_->conds[x]);
								x++;

								if ((sint)t_->opts[3].size() > t)
								{
									statement.append(" ");
									statement.append(sql_conj_keywords[t_->opts[3][t]]);
									t++;
								}
							}
						}
						else
						{
							statement.append(" ");
							statement.append(t_->conds[x]);
						}
					}
				}
				else if (t_->opts[0][0] == 2)
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

			if (!t_->opts[11].empty())
			{
				BOT_STMT trans;
				trans.dbname.append(t_->dbname.c_str());

				if (t_->vals.size())
				{
					sint xc = AddStrToVec(&trans.tables, t_->vals[0].c_str());
					for (xc = 1; xc < (sint)t_->vals.size(); xc++)
					{
						sint nc = AddStrToVec(&trans.cols, t_->vals[xc].c_str());
					}
				}

				trans.ic_types = t_->ic_types;
				trans.it_type = t_->opts[11][0];

				if (t_->opts[11].size() > 1)
				{
					trans.opts[0].push_back(t_->opts[11][1]);
				}

				if (!t_->conds.empty())
				{
					for (uint xc = 0; xc < t_->conds.size(); xc++)
					{
						sint nc = AddStrToVec(&trans.conds, t_->conds[xc].c_str());
					}
				}

				trans.cols = t_->cols;
				sint xc = BQS(&trans);
				statement.append(" ");
				statement.append(trans.stmt);
				statement.pop_back();
			}
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

							for (size_t tsiz = 0; tsiz < pend_->at(i).tables.size(); tsiz++)
							{
								sint nx = vtool.AddValToVec(&cont_names[cont_names.size() - 1], &pend_->at(i).tables[tsiz], true, false);
							}
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

						for (size_t tsiz = 0; tsiz < pend_->at(i).tables.size(); tsiz++)
						{
							sint nc = vtool.AddValToVec(&cont_names[dx], &pend_->at(i).tables[tsiz], true, false);
						}
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

						for (size_t tsiz = 0; tsiz < stmts_->at(i).tables.size(); tsiz++)
						{
							sint nx = vtool.AddValToVec(&cont_names[cont_names.size() - 1], &stmts_->at(i).tables[tsiz], true, false);
						}
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

					for (size_t tsiz = 0; tsiz < stmts_->at(i).tables.size(); tsiz++)
					{
						sint nc = vtool.AddValToVec(&cont_names[dx], &stmts_->at(i).tables[tsiz], true, false);
					}
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

			BOT_STMT trans((bool)db_maint[i], 1, com_->dbs[i].name.c_str());
			xc = trans.AddCont("LAST_ACCESS", 1);
			trans.opts[0].push_back(0);
			trans.opts[9].push_back(0);
			xc = AddStrToVec(&trans.conds, "ID > 0", false, false);
			xc = vtool.AddValToVec(&com_->t, &trans, true, false);
			trans.Clear();
			trans.Renew((bool)db_maint[i], 8, com_->dbs[i].name.c_str());

			for (uint c = 0; c < cont_names[i].size(); c++)
			{
				xc = trans.AddCont(cont_names[i][c].c_str(), 1);
				xc = vtool.AddValToVec(&com_->an, &trans, true, false);
				trans.tables.clear();
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

		for (uint o = 0; o < t_->tables.size(); o++)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, " %i:%s", o, t_->tables[o].c_str());
			output.append(ncar.carr);
		}

		if (!output.empty())
		{
			output.append("\nic_types: ");
		}

		for (uint o = 0; o < t_->ic_types.size(); o++)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, " %i:%i %s", o, t_->ic_types[o], sql_obj_keywords[t_->ic_types[o]]);
			output.append(ncar.carr);
		}

		if (!output.empty())
		{
			carr_256 ncar;
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
			carr_256 ncar;
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
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "\nt_ has %u conds eles: ", t_->conds.size());
			output.append(ncar.carr);
		}

		for (uint o = 0; o < t_->conds.size(); o++)
		{
			carr_256 ncar;
			sint xp = bot_sprintf(ncar.carr, ncar.siz, "| %s ", t_->conds[o].c_str());
			output.append(ncar.carr);
		}

		for (uint o = 0; o < t_->opts.size(); o++)
		{
			if (!t_->opts[o].empty())
			{
				carr_256 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "\nopts[%i] has %u eles: ", o, t_->opts[o].size());
				output.append(ncar.carr);

				for (uint xc = 0; xc < t_->opts[o].size(); xc++)
				{
					carr_256 ncar;
					sint xp = bot_sprintf(ncar.carr, ncar.siz, ", %i ", t_->opts[o][xc]);
					output.append(ncar.carr);
				}
			}
		}
		sint xc = Output(output.c_str(), 2);
		return 0;
	}


	// Database Functions

	std::string GetError()
	{
		std::string str;
		str.append(reinterpret_cast<cchar*>(sqlite3_errmsg(d_con_->db_)));
		return str;
	}
	sint FindColumn(cchar *str_, sqlite3_stmt* ppstmt)
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
		}
		else
		{
			if (*was_open < 1)
			{
				*was_open = 0;
			}
		}

		BOT_FILE_M nfilem(db_->name.c_str(), ".db", "", lid, x);
		sint xc = GetInVec(&nfilem, MTX_FO, false, true);

		if (xc < 0)
		{
			BOT_FILE nfile(db_->name.c_str(), ".db", "", lid, x);
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

		if (d_con_->name.empty())
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
					
					d_con_->Renew(db_->name.c_str(), db_->lid, x, dbc);
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
					cchar* tail;
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
			cchar* tail;
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

		BOT_FILE_M nfile;
		sint xc = GetVecEle(&nfile, MTX_FO, db_->file_ele);

		if (!*fwas_locked)
		{
			if (gc > -1)
			{
				gc = FileStats(&nfile);
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
								cchar* tail = "";
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
									cchar* tail = "";
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
						cchar* tail = "";
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
								cchar* tail = "";
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
											bot_t_pend[rc].vals[usiz].append(ITOA(rc));
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
		sint oc = Output("Commit() End", 2);
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
			BOT_FILE_M ndb(nms[x].c_str(), ".db", "", lid, 3);
			sint of = -1;
			sint xc = OpenFile(&ndb, &of, true);

			if (xc < 0)
			{
				db_failed++;
			}
			else
			{
				xc = CloseFile(&ndb);

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
			BOT_STMT trans(false, 0, dbs_->name.c_str());
			trans.AddCont(dbs_->tables[x].c_str(), 1);
			sint rc = BQS(&trans);

			if (rc)
			{
				return 1;
			}

			cchar* tail;
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
					trans.Renew(false, 3, dbs_->name.c_str());
					trans.opts[7].push_back(0);
					trans.opts[8].push_back(1);
					rc = trans.AddCont(dbs_->tables[x].c_str(), 1);

					for (rc = 0; rc < (sint)dbs_->columns[x][0].size(); rc++)
					{
						if (rc < (sint)dbs_->columns[x][1].size())
						{
							sint nx = trans.AddCol(dbs_->columns[x][0][rc].c_str(), dbs_->columns[x][1][rc].c_str());
						}
					}

					rc = vtool.AddValToVec(tvec_, &trans, true, true);
					trans.ic_types[(sint)trans.ic_types.size() - 1] = 3;
					trans.opts[1].push_back(0);
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
					trans.Renew(false, 2, dbs_->name.c_str());
					trans.AddCont(dbs_->tables[x].c_str(), 1);
					trans.opts[0].push_back(2);
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
							BOT_STMT t(false, 3, dbs_->name.c_str());
							t.opts[7].push_back(1);
							t.opts[8].push_back(2);
							std::string ncar;
							ncar.append(dbs_->tables[x]);
							ncar.append("_");
							rc = t.AddCont(ncar.c_str(), 2);
							ncar.clear();

							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								t.AddCol(dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str());
							}

							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 2, dbs_->name.c_str());
							ncar.append(dbs_->tables[x]);
							ncar.append("_");
							rc = t.AddCont(ncar.c_str(), 1);

							for (sint stcount = 0; stcount < sqlite3_column_count(ppstmt); stcount++)
							{
								ncar.clear();
								ncar.append(sqlite3_column_name(ppstmt, stcount));
								rc = AddStrToVec(&t.cols, ncar.c_str());
							}

							std::string nval;
							nval.append(dbs_->tables[x]);
							t.opts[11].push_back(0);
							rc = AddStrToVec(&t.vals, nval.c_str());
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 5, dbs_->name.c_str());
							rc = t.AddCont(dbs_->tables[x].c_str(), 1);
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 7, dbs_->name.c_str());
							t.opts[9].push_back(2);
							ncar.clear();
							ncar.append(dbs_->tables[x]);
							ncar.append("_");
							rc = t.AddCont(ncar.c_str(), 1);
							rc = AddStrToVec(&t.vals, nval.c_str());
							rc = vtool.AddValToVec(tvec_, &t, false, false);
							t.Clear();
							t.Renew(false, 3, dbs_->name.c_str());
							t.opts[1].push_back(0);
							t.opts[7].push_back(0);
							t.opts[8].push_back(1);
							rc = t.AddCont(dbs_->tables[x].c_str(), 2);

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

									BOT_STMT t(false, 7, dbs_->name.c_str());
									t.opts[9].push_back(1);
									rc = t.AddCont(dbs_->tables[x].c_str(), 1);
									rc = t.AddCol(m_cols[m].c_str(), m_cols[m + 1].c_str());
									rc = vtool.AddValToVec(tvec_, &t, true, true);
								}

								BOT_STMT t(false, 3, dbs_->name.c_str());
								rc = t.AddCont(dbs_->tables[x].c_str(), 2);
								t.opts[1].push_back(0);
								t.opts[7].push_back(0);
								t.opts[8].push_back(1);

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
							BOT_STMT t(false, 2, dbs_->name.c_str());
							rc = t.AddCont(dbs_->tables[x].c_str(), 1);
							t.opts[0].push_back(2);
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
							BOT_STMT t(false, 3, dbs_->name.c_str());
							t.opts[7].push_back(0);
							t.opts[8].push_back(1);
							std::string ntn;
							ntn.append(dbs_->tables[x]);
							ntn.append("_");
							rc = t.AddCont(ntn.c_str(), 1);

							for (uint stcount = 0; stcount < (sint)dbs_->columns[x][0].size(); stcount++)
							{
								if (stcount < (sint)dbs_->columns[x][1].size())
								{
									rc = t.AddCol(dbs_->columns[x][0][stcount].c_str(), dbs_->columns[x][1][stcount].c_str());
								}
							}

							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 2, dbs_->name.c_str());
							rc = t.AddCont(ntn.c_str(), 1);

							for (sint stcount = 0; stcount < sqlite3_column_count(ppstmt); stcount++)
							{
								std::string ncol;
								ncol.append(sqlite3_column_name(ppstmt, stcount));
								rc = AddStrToVec(&t.cols, ncol.c_str());
							}

							t.opts[11].push_back(0);
							std::string nval;
							nval.append(dbs_->tables[x]);
							rc = AddStrToVec(&t.vals, nval.c_str());

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
							t.Renew(false, 5, dbs_->name.c_str());
							rc = t.AddCont(dbs_->tables[x].c_str(), 1);
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 7, dbs_->name.c_str());
							t.opts[9].push_back(2);
							rc = t.AddCont(ntn.c_str(), 1);
							rc = AddStrToVec(&t.vals, nval.c_str());
							rc = vtool.AddValToVec(tvec_, &t, true, true);
							t.Clear();
							t.Renew(false, 3, dbs_->name.c_str());
							t.opts[1].push_back(0);
							t.opts[7].push_back(0);
							t.opts[8].push_back(1);
							rc = t.AddCont(dbs_->tables[x].c_str(), 2);

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

									BOT_STMT t(false, 7, dbs_->name.c_str());
									t.opts[9].push_back(1);
									rc = t.AddCont(dbs_->tables[x].c_str(), 1);
									rc = t.AddCol(m_cols[m].c_str(), m_cols[m + 1].c_str());
									rc = vtool.AddValToVec(tvec_, &t, true, true);
								}

								BOT_STMT t(false, 3, dbs_->name.c_str());
								t.opts[1].push_back(0);
								t.opts[7].push_back(0);
								t.opts[8].push_back(1);
								rc = t.AddCont(dbs_->tables[x].c_str(), 2);

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
			BOT_STMT t(false, 3, dbs.name.c_str());
			t.opts[7].push_back(0);
			t.opts[8].push_back(1);
			xc = t.AddCont(dbs.tables[s].c_str(), 1);

			for (size_t xs = 0; xs < dbs.columns[s][0].size(); xs++)
			{
				sint oc = t.AddCol(dbs.columns[s][0][xs].c_str(), dbs.columns[s][1][xs].c_str());
			}

			sint oc = vtool.AddValToVec(&sepsql, &t, true, true);
			t.ic_types[xc] = 2;
			t.opts[1].push_back(0);
			oc = vtool.AddValToVec(&sepsql, &t, true, true);

			if (!s)
			{
				t.Clear();
				t.Renew(false, 2, dbs.name.c_str());
				t.opts[0].push_back(2);
				xc = t.AddCont(dbs.tables[s].c_str(), 1);
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
				if (!h)
				{
					h = UnlockGMutex(MTX_STRT);
				}
			}
		}
		else if (dbs.type == 2)
		{
			
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

	sint GetSymbol(MICSYM *sym_ = 0, cchar x_cond_[] = 0, bool maint = false) { if (!sym_) { return -1; } std::vector<MICSYM> vec; vec.push_back(*sym_); return GetSymbols(&vec, x_cond_, maint); }
	sint GetSymbols(std::vector <MICSYM> *syms_ = 0, cchar x_cond_[] = 0, bool maint = false)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::GetSymbols(std::vector <MICSYM> *syms_(%i), cchar* x_cond_(%i), bool maint(%u))", (sint)syms_, (sint)x_cond_, (uint)maint);
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
				BOT_STMT t(maint, 0, "litebot");
				rc = t.AddCont("SYMS", 1);

				if (!maint)
				{
					t.opts[0].push_back(0);
					char dval[(sizeof(syms_->at(nsiz).sym) * 2) + 18]{ 0 };
					rc = bot_sprintf(dval, sizeof(dval), "SYMBOL = X'%02X'", syms_->at(nsiz).sym);
					rc = AddStrToVec(&t.conds, dval, false, false);
				}

				if (x_cond_)
				{
					if (strlen(x_cond_))
					{
						char outc[sizeof(x_cond_) + 1]{ 0 };
						rc = bot_sprintf(outc, sizeof(outc), "%s", x_cond_);

						if (!t.conds.empty())
						{
							t.opts[3].push_back(0);
						}
						rc = AddStrToVec(&t.conds, outc);
					}
				}
				if (syms_->at(nsiz).id > -1)
				{
					char outc[32]{ 0 };
					rc = bot_sprintf(outc, 32, "ID = %i", syms_->at(nsiz).id);

					if (!t.conds.empty())
					{
						t.opts[3].push_back(0);
					}
					rc = AddStrToVec(&t.conds, outc, false, false);
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
					cchar* tail;
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
										uchar echar = (uchar)'\0';
										uchar* suc = (uchar*)malloc(ui + 1);
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
														uchar* nuchar = (uchar*)malloc(ui + 1);
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
														free(nuchar);
													}
												}

												rc = FindColumn("HISTORY_FOLLOWING", ppstmt);

												if (rc > -1)
												{
													ui = sqlite3_column_bytes(ppstmt, rc);

													if (ui && ui < BOT_STRLEN_MAX)
													{
														uchar sep = (uchar)',';
														uchar* nuchar = (uchar*)malloc(ui + 1);
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
														free(nuchar);
													}
												}

												rc = FindColumn("HISTORY_PRECEEDING", ppstmt);

												if (rc > -1)
												{
													ui = sqlite3_column_bytes(ppstmt, rc);

													if (ui && ui < BOT_STRLEN_MAX)
													{
														uchar sep = (uchar)',';
														uchar* nuchar = (uchar*)malloc(ui + 1);
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
														free(nuchar);
													}
												}

												rc = FindColumn("CONSTITUENT_TO", ppstmt);

												if (rc > -1)
												{
													ui = sqlite3_column_bytes(ppstmt, rc);

													if (ui && ui < BOT_STRLEN_MAX)
													{
														uchar lsep = (uchar)' ';
														uchar sep = (uchar)',';
														uchar* nuchar = (uchar*)malloc(ui + 1);
														memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
														memcpy((void*)&nuchar[ui], (void*)&echar, 1);
														std::vector<std::vector<uchar>> nvec;
														std::vector<uchar> uvec;

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

		if (rc > -1)
		{
			for (size_t x = 0; x < eles.size(); x++)
			{
				BOT_STMT t(syms_->at(eles[x]).ud_last_maintained, 1);
				sint xc = t.AddDB("litebot");
				xc = t.AddCont("SYMS", 1);

				if (syms_->at(eles[x]).id < 0)
				{
					t.it_type = 2;
					t.opts[0].push_back(2);

					if (sizeof(syms_->at(eles[x]).sym))
					{
						char xstr[(sizeof(syms_->at(eles[x]).sym) * 2) + 8]{ 0 };
						sint xp = bot_sprintf(xstr, sizeof(xstr), "X'%02X'", syms_->at(eles[x]).sym);
						xp = AddStrToVec(&t.cols, "SYMBOL", false, false);
						xp = AddStrToVec(&t.vals, xstr, false, false);
					}

					if (!syms_->at(eles[x]).encodings.empty())
					{
						std::string str;
						for (size_t xs = 0; xs < syms_->at(eles[x]).encodings.size(); xs++)
						{
							char ci[(sizeof(syms_->at(eles[x]).encodings[xs]) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (uchar)syms_->at(eles[x]).encodings[xs]);
							str.append(ci);
						}
						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "ENCODINGS", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
							if (xp > -1)
							{
								t.vals[xp].append(str.c_str());
								t.vals[xp].push_back('\'');
							}
						}
					}

					if (!syms_->at(eles[x]).constituent_to.empty())
					{
						uchar lsep = (uchar)' ';
						uchar sep = (uchar)',';
						std::string str;

						for (size_t xs = 0; xs < syms_->at(eles[x]).constituent_to.size(); xs++)
						{
							for (size_t nsiz = 0; nsiz < syms_->at(eles[x]).constituent_to[xs].size(); nsiz++)
							{
								for (size_t xsiz = 0; xsiz < syms_->at(eles[x]).constituent_to[xs][nsiz].size(); xsiz++)
								{
									char ci[(sizeof(syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]);
									str.append(ci);
								}
								char xi[(sizeof(sep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
								str.append(xi);
							}
							char xi[(sizeof(lsep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
							str.append(xi);
						}
						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "CONSTITUENT_TO", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
							if (xp > -1)
							{
								t.vals[xp].append(str.c_str());
								t.vals[xp].push_back('\'');
							}
						}
					}

					if (!syms_->at(eles[x]).history_following.empty())
					{
						uchar sep = (uchar)',';
						std::string str;
						for (size_t xx = 0; xx < syms_->at(eles[x]).history_following.size(); xx++)
						{
							for (size_t xs = 0; xs < syms_->at(eles[x]).history_following[xx].size(); xs++)
							{
								char ci[(sizeof(syms_->at(eles[x]).history_following[xx][xs].sym) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_following[xx][xs].sym);
								str.append(ci);
								char xi[(sizeof(syms_->at(eles[x]).history_following[xx][xs].ct) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)syms_->at(eles[x]).history_following[xx][xs].ct);
								str.append(xi);
							}
							char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}
						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
							if (xp > -1)
							{
								t.vals[xp].append(str.c_str());
								t.vals[xp].push_back('\'');
							}
						}
					}

					if (!syms_->at(eles[x]).history_preceeding.empty())
					{
						uchar sep = (uchar)',';
						std::string str;

						for (size_t xx = 0; xx < syms_->at(eles[x]).history_preceeding.size(); xx++)
						{
							for (size_t xs = 0; xs < syms_->at(eles[x]).history_preceeding[xx].size(); xs++)
							{
								char ci[(sizeof(syms_->at(eles[x]).history_preceeding[xx][xs].sym) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_preceeding[xx][xs].sym);
								str.append(ci);
								char xi[(sizeof(syms_->at(eles[x]).history_preceeding[xx][xs].ct) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)syms_->at(eles[x]).history_preceeding[xx][xs].ct);
								str.append(xi);
							}
							char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}
						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
							if (xp > -1)
							{
								t.vals[xp].append(str.c_str());
								t.vals[xp].push_back('\'');
							}
						}
					}

					if (!t.tables.empty())
					{
						xc = vtool.AddValToVec(&tvec, &t, false, true);
					}
				}
				else
				{
					t.opts[0].push_back(0);
					t.opts[9].push_back(0);

					if (syms_->at(eles[x]).ud_id)
					{
						AddStrToVec(&t.cols, "ID", false, false);
						AddStrToVec(&t.vals, ITOA(syms_->at(eles[x]).id).c_str(), false, false);
					}

					if (syms_->at(eles[x]).ud_sym)
					{
						if (sizeof(syms_->at(eles[x]).sym))
						{
							char xstr[(sizeof(syms_->at(eles[x]).sym) * 2) + 8]{ 0 };
							sint xp = bot_sprintf(xstr, sizeof(xstr), "X'%02X'", syms_->at(eles[x]).sym);
							xp = AddStrToVec(&t.cols, "SYMBOL", false, false);
							xp = AddStrToVec(&t.vals, xstr, false, false);
						}
					}

					if (syms_->at(eles[x]).ud_encodings)
					{
						std::string str;
						for (size_t a = 0; a < syms_->at(eles[x]).encodings.size(); a++)
						{
							char ci[(sizeof(syms_->at(eles[x]).encodings[a]) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (uchar)syms_->at(eles[x]).encodings[a]);
							str.append(ci);
						}
						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "ENCODINGS", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
							if (xp > -1)
							{
								t.vals[xp].append(str.c_str());
								t.vals[xp].push_back('\'');
							}
						}
					}

					if (syms_->at(eles[x]).ud_constituent_to)
					{
						uchar lsep = (uchar)' ';
						uchar sep = (uchar)',';
						std::string str;
						for (size_t xs = 0; xs < syms_->at(eles[x]).constituent_to.size(); xs++)
						{
							for (size_t nsiz = 0; nsiz < syms_->at(eles[x]).constituent_to[xs].size(); nsiz++)
							{
								for (size_t xsiz = 0; xsiz < syms_->at(eles[x]).constituent_to[xs][nsiz].size(); xsiz++)
								{
									char ci[(sizeof(syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).constituent_to[xs][nsiz][xsiz]);
									str.append(ci);
								}
								char xi[(sizeof(sep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
								str.append(xi);
							}
							char xi[(sizeof(lsep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
							str.append(xi);
						}
						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "CONSTITUENT_TO", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
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
						uchar sep = (uchar)',';

						for (size_t a = 0; a < syms_->at(eles[x]).history_following.size(); a++)
						{
							for (size_t b = 0; b < syms_->at(eles[x]).history_following[a].size(); b++)
							{
								char ci[(sizeof(syms_->at(eles[x]).history_following[a][b].sym) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_following[a][b].sym);
								str.append(ci);
								char xi[(sizeof(syms_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)syms_->at(eles[x]).history_following[a][b].ct);
								str.append(xi);
							}
							char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}

						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
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
						uchar sep = (uchar)',';

						for (size_t a = 0; a < syms_->at(eles[x]).history_preceeding.size(); a++)
						{
							for (size_t b = 0; b < syms_->at(eles[x]).history_preceeding[a].size(); b++)
							{
								char ci[(sizeof(syms_->at(eles[x]).history_preceeding[a][b].sym) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", syms_->at(eles[x]).history_preceeding[a][b].sym);
								str.append(ci);
								char xi[(sizeof(syms_->at(eles[x]).history_preceeding[a][b].ct) * 2) + 1]{ 0 };
								xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)syms_->at(eles[x]).history_preceeding[a][b].ct);
								str.append(xi);
							}
							char xi[(sizeof(sep) * 2) + 1]{ 0 };
							sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
							str.append(xi);
						}

						if (!str.empty())
						{
							sint xp = AddStrToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
							xp = AddStrToVec(&t.vals, "X'", false, false);
							if (xp > -1)
							{
								t.vals[xp].append(str.c_str());
								t.vals[xp].push_back('\'');
							}
						}
					}

					if ((sint)t.conds.size())
					{
						t.opts[3].push_back(1);
					}

					if (syms_->at(eles[x]).id > 0)
					{
						AddStrToVec(&t.conds, "ID = ");
						t.conds[(sint)t.conds.size() - 1].append(ITOA(syms_->at(eles[x]).id));
					}
					else
					{
						char str_[(sizeof(syms_->at(eles[x]).sym) * 2) + 14]{ 0 };
						xc = bot_sprintf(str_, sizeof(str_), "SYMBOL = X'%02X'", syms_->at(eles[x]).sym);
						xc = AddStrToVec(&t.conds, str_);
					}
					xc = vtool.AddValToVec(&tvec, &t, true, true);
				}
			}
			if (!tvec.empty())
			{
				return Commit(&tvec);
			}
		}
		return -1;
	}
	sint GetCode(MACSYM* code_ = 0, cchar x_cond_[] = 0, bool maint = false) { if (!code_) { return -1; } std::vector<MACSYM> vec; vec.push_back(*code_); return GetCode(&vec, x_cond_,maint); }
	sint GetCode(std::vector<MACSYM>* codes_ = 0, cchar x_cond_[] = 0, bool maint = false)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::GetCode(std::vector <MACSYM> *codes_(%i), cchar* x_cond_(%i), bool maint(%u))", (sint)codes_, (sint)x_cond_, (uint)maint);
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

					BOT_STMT t(maint, 0, cdb.name.c_str());
					rc = t.AddCont(cdb.tables[siz].c_str(), 1);
					t.opts[0].push_back(0);

					if (!maint)
					{
						std::string str;
						for (size_t siz = 0; siz < codes_->at(xsiz).cons.size(); siz++)
						{
							char nchr[(sizeof(codes_->at(xsiz)).cons[siz] * 2) + 1]{ 0 };
							rc = bot_sprintf(nchr, sizeof(nchr), "%02X", codes_->at(xsiz).cons[siz].sym);
							str.append(nchr);
						}
						if (!str.empty())
						{
							rc = AddStrToVec(&t.conds, "DATA = X'", false, false);

							if (rc > -1)
							{
								t.conds[rc].append(str.c_str());
								t.conds[rc].push_back('\'');
							}
						}
					}

					if (x_cond_)
					{
						if (strlen(x_cond_))
						{
							char outc[sizeof(x_cond_) + 1]{ 0 };
							rc = bot_sprintf(outc, sizeof(outc), "%s", x_cond_);
							t.opts[3].push_back(0);
							rc = AddStrToVec(&t.conds, outc);
						}
					}

					if (codes_->at(xsiz).id > -1)
					{
						char outc[32]{ 0 };
						rc = bot_sprintf(outc, 32, "ID = %i", codes_->at(xsiz).id);

						if (!t.conds.empty())
						{
							t.opts[3].push_back(0);
						}
						rc = AddStrToVec(&t.conds, outc, false, false);
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
		dbs.Update(&cdb);
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
					cchar* tail;
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
										uchar echar = (uchar)'\0';
										uchar* nuc = (uchar*)malloc(ui + 1);
										memcpy((void*)nuc, reinterpret_cast <const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
										memcpy((void*)&nuc[ui], (void*)&echar, 1);
										const size_t ssiz = sizeof(nuc);

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
															if (codes_->at(nsiz).cons.size() == ssiz)
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
															uchar* nuchar = (uchar*)malloc(ui + 1);
															memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
															memcpy((void*)&nuchar[ui], (void*)&echar, 1);

															for (size_t fi = 0; fi < ui; fi++)
															{
																sint xi = vtool.AddValToVec(&codes_->at(nsiz).usages, (uint)nuchar[fi], false, false);

																for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																{
																	if (codes_->at(nsiz).cons.size() == ssiz)
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
															free(nuchar);
														}
													}

													rc = FindColumn("USED", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															uchar* nuchar = (uchar*)malloc(ui + 1);
															memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
															memcpy((void*)&nuchar[ui], (void*)&echar, 1);

															for (size_t fi = 0; fi < ui; fi++)
															{
																sint xi = vtool.AddValToVec(&codes_->at(nsiz).used, (uint)nuchar[fi], false, false);

																for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																{
																	if (codes_->at(nsiz).cons.size() == ssiz)
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
															free(nuchar);
														}
													}

													rc = FindColumn("HISTORY_FOLLOWING", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															uchar* nuchar = (uchar*)malloc(ui + 1);
															memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
															memcpy((void*)&nuchar[ui], (void*)&echar, 1);
															std::vector<HIST_FV> nvec;
															HIST_FV hf;
															uchar lsep = (uchar)' ';
															uchar sep = (uchar)',';

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
																		if (codes_->at(nsiz).cons.size() == ssiz)
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
																	if (codes_->at(nsiz).cons.size() == ssiz)
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
															free(nuchar);
														}
													}

													rc = FindColumn("HISTORY_PRECEEDING", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															uchar* nuchar = (uchar*)malloc(ui + 1);
															memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, rc)), ui);
															memcpy((void*)&nuchar[ui], (void*)&echar, 1);
															std::vector<HIST_PV> nvec;
															HIST_PV hf;
															uchar lsep = (uchar)' ';
															uchar sep = (uchar)',';

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
																		if (codes_->at(nsiz).cons.size() == ssiz)
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
																	if (codes_->at(nsiz).cons.size() == ssiz)
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
															free(nuchar);
														}
													}

													rc = FindColumn("ALTERS", ppstmt);

													if (rc > -1)
													{
														ui = sqlite3_column_bytes(ppstmt, rc);

														if (ui && ui < BOT_STRLEN_MAX)
														{
															uchar* nuchar = (uchar*)malloc(ui + 1);
															memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, rc)), ui);
															memcpy((void*)&nuchar[ui], (void*)&echar, 1);
															std::vector<uchar> nvec;
															uchar sep = (uchar)',';

															for (uint csiz = 0; csiz < ui; csiz++)
															{
																if (!memcmp(&nuchar[csiz], &sep, 1) && !nvec.empty())
																{
																	sint xi = vtool.AddValToVec(&codes_->at(nsiz).alters, &nvec, true, false);

																	for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
																	{
																		if (codes_->at(nsiz).cons.size() == ssiz)
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
																	if (codes_->at(nsiz).cons.size() == ssiz)
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
															free(nuchar);
														}
													}
													rc = FindColumn("LAST_MODIFIED", ppstmt);

													if (rc > -1)
													{
														codes_->at(nsiz).last_modified = sqlite3_column_int(ppstmt, rc);

														for (size_t xsiz = nsiz + 1; xsiz < codes_->size(); xsiz++)
														{
															if (codes_->at(nsiz).cons.size() == ssiz)
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
															if (codes_->at(nsiz).cons.size() == ssiz)
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
															if (codes_->at(nsiz).cons.size() == ssiz)
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
															if (codes_->at(nsiz).cons.size() == ssiz)
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
		if (rc > -1)
		{
			std::vector<BOT_STMT> tvec;

			for (size_t x = 0; x < eles.size(); x++)
			{
				std::string con_str;

				if (!codes_->at(eles[x]).cons.empty())
				{
					for (size_t a = 0; a < codes_->at(eles[x]).cons.size(); a++)
					{
						char ci[(sizeof(codes_->at(eles[x]).cons[a].sym) * 2) + 1]{ 0 };
						sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).cons[a].sym);
						con_str.append(ci);
					}
				}

				for (size_t uc = 0; uc < codes_->at(eles[x]).usages.size(); uc++)
				{
					BOT_STMT t(codes_->at(eles[x]).ud_last_maintained, 1);

					if (dbs.lid > -1)
					{
						sint xc = t.AddDB(dbs.name.c_str());
						xc = t.AddCont(dbs.tables[codes_->at(eles[x]).usages[uc]].c_str(), 1);
					}
					else
					{
						sint h = -1;
						sint p = LockGMutex(MTX_STRT, &h);

						if (p > -1)
						{
							sint xc = t.AddDB("code");
							xc = t.AddCont(bot_strt.code_tablenames[codes_->at(eles[x]).usages[uc]], 1);

							if (!h)
							{
								h = UnlockGMutex(MTX_STRT);
							}
						}
					}

					if (codes_->at(eles[x]).id < 0)
					{
						t.it_type = 2;
						t.opts[0].push_back(2);

						if (!codes_->at(eles[x]).cons.empty())
						{
							if (!con_str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "DATA", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);

								if (xc > -1)
								{
									t.vals[xc].append(con_str.c_str());
									t.vals[xc].push_back('\'');
								}
							}
						}

						if (!codes_->at(eles[x]).usages.empty())
						{
							std::string str;
							for (size_t xc = 0; xc < codes_->at(eles[x]).usages.size(); xc++)
							{
								char ci[(sizeof(codes_->at(eles[x]).usages[xc]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (uchar)codes_->at(eles[x]).usages[xc]);
								str.append(ci);
							}
							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "USAGES", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
								char ci[(sizeof(codes_->at(eles[x]).used[xc]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (uchar)codes_->at(eles[x]).used[xc]);
								str.append(ci);
							}
							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "USED", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
							uchar lsep = (uchar)' ';
							uchar sep = (uchar)',';

							for (size_t a = 0; a < codes_->at(eles[x]).history_following.size(); a++)
							{
								for (size_t b = 0; b < codes_->at(eles[x]).history_following[a].size(); b++)
								{
									for (size_t c = 0; c < codes_->at(eles[x]).history_following[a][b].cons.size(); c++)
									{
										char ci[(sizeof(codes_->at(eles[x]).history_following[a][b].cons[c].sym) * 2) + 1]{ 0 };
										sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_following[a][b].cons[c].sym);
										str.append(ci);
									}
									char xi[(sizeof(codes_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)codes_->at(eles[x]).history_following[a][b].ct);
									str.append(xi);
									char ci[(sizeof(sep) * 2) + 1]{ 0 };
									xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
									str.append(ci);
								}
								char xi[(sizeof(lsep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
								str.append(xi);
							}

							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
							uchar lsep = (uchar)' ';
							uchar sep = (uchar)',';

							for (size_t a = 0; a < codes_->at(eles[x]).history_preceeding.size(); a++)
							{
								for (size_t b = 0; b < codes_->at(eles[x]).history_preceeding[a].size(); b++)
								{
									for (size_t c = 0; c < codes_->at(eles[x]).history_preceeding[a][b].cons.size(); c++)
									{
										char ci[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym) * 2) + 1]{ 0 };
										sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym);
										str.append(ci);
									}
									char xi[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].ct) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)codes_->at(eles[x]).history_preceeding[a][b].ct);
									str.append(xi);
									char ci[(sizeof(sep) * 2) + 1]{ 0 };
									xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
									str.append(ci);
								}
								char xi[(sizeof(lsep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
								str.append(xi);
							}

							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
								if (xc > -1)
								{
									t.vals[xc].append(str.c_str());
									t.vals[xc].push_back('\'');
								}
							}
						}

						if (!codes_->at(eles[x]).alters.empty())
						{
							uchar sep = (uchar)',';
							std::string str;
							for (size_t xc = 0; xc < codes_->at(eles[x]).alters.size(); xc++)
							{
								for (size_t nsiz = 0; nsiz < codes_->at(eles[x]).alters[xc].size(); nsiz++)
								{
									char ci[(sizeof(codes_->at(eles[x]).alters[xc]) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).alters[xc]);
									str.append(ci);
								}
								char xi[(sizeof(sep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
								str.append(xi);
							}
							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "ALTERS", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
								if (xc > -1)
								{
									t.vals[xc].append(str.c_str());
									t.vals[xc].push_back('\'');
								}
							}
						}

						if (!t.tables.empty())
						{
							sint xc = vtool.AddValToVec(&tvec, &t, false, true);
						}
					}
					else
					{
						t.opts[0].push_back(0);
						t.opts[9].push_back(0);

						if (codes_->at(eles[x]).ud_id)
						{
							AddStrToVec(&t.cols, "ID", false, false);
							AddStrToVec(&t.vals, ITOA(codes_->at(eles[x]).id).c_str(), false, false);
						}

						if (codes_->at(eles[x]).ud_cons)
						{
							if (!con_str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "DATA", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
								if (xc > -1)
								{
									t.vals[xc].append(con_str.c_str());
									t.vals[xc].push_back('\'');
								}
							}
						}

						if (codes_->at(eles[x]).ud_usages)
						{
							std::string str;
							for (size_t a = 0; a < codes_->at(eles[x]).usages.size(); a++)
							{
								char ci[(sizeof(codes_->at(eles[x]).usages[a]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (uchar)codes_->at(eles[x]).usages[a]);
								str.append(ci);
							}
							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "USAGES", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
								char ci[(sizeof(codes_->at(eles[x]).used[a]) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(ci, sizeof(ci), "%02X", (uchar)codes_->at(eles[x]).used[a]);
								str.append(ci);
							}
							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "USED", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
							uchar lsep = (uchar)' ';
							uchar sep = (uchar)',';

							for (size_t a = 0; a < codes_->at(eles[x]).history_following.size(); a++)
							{
								for (size_t b = 0; b < codes_->at(eles[x]).history_following[a].size(); b++)
								{
									for (size_t c = 0; c < codes_->at(eles[x]).history_following[a][b].cons.size(); c++)
									{
										char ci[(sizeof(codes_->at(eles[x]).history_following[a][b].cons[c].sym) * 2) + 1]{ 0 };
										sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_following[a][b].cons[c].sym);
										str.append(ci);
									}
									char xi[(sizeof(codes_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{  };
									sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)codes_->at(eles[x]).history_following[a][b].ct);
									str.append(xi);
									char ci[(sizeof(sep) * 2) + 1]{ 0 };
									xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
									str.append(ci);
								}
								char xi[(sizeof(lsep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
								str.append(xi);
							}

							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "HISTORY_FOLLOWING", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
							uchar lsep = (uchar)' ';
							uchar sep = (uchar)',';

							for (size_t a = 0; a < codes_->at(eles[x]).history_preceeding.size(); a++)
							{
								for (size_t b = 0; b < codes_->at(eles[x]).history_preceeding[a].size(); b++)
								{
									for (size_t c = 0; c < codes_->at(eles[x]).history_preceeding[a][b].cons.size(); c++)
									{
										char ci[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym) * 2) + 1]{ 0 };
										sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).history_preceeding[a][b].cons[c].sym);
										str.append(ci);
									}
									char xi[(sizeof(codes_->at(eles[x]).history_preceeding[a][b].ct) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(xi, sizeof(xi), "%02X", (uchar)codes_->at(eles[x]).history_preceeding[a][b].ct);
									str.append(xi);
									char ci[(sizeof(sep) * 2) + 1]{ 0 };
									xp = bot_sprintf(xi, sizeof(ci), "%02X", sep);
									str.append(ci);
								}
								char xi[(sizeof(lsep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", lsep);
								str.append(xi);
							}

							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "HISTORY_PRECEEDING", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
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
							uchar sep = (uchar)',';

							for (size_t a = 0; a < codes_->at(eles[x]).alters.size(); a++)
							{
								for (size_t b = 0; b < codes_->at(eles[x]).alters[a].size(); b++)
								{
									char ci[(sizeof(codes_->at(eles[x]).alters[a]) * 2) + 1]{ 0 };
									sint xp = bot_sprintf(ci, sizeof(ci), "%02X", codes_->at(eles[x]).alters[a]);
									str.append(ci);
								}
								char xi[(sizeof(sep) * 2) + 1]{ 0 };
								sint xp = bot_sprintf(xi, sizeof(xi), "%02X", sep);
								str.append(xi);
							}
							if (!str.empty())
							{
								sint xc = AddStrToVec(&t.cols, "ALTERS", false, false);
								xc = AddStrToVec(&t.vals, "X'", false, false);
								if (xc > -1)
								{
									t.vals[xc].append(str.c_str());
									t.vals[xc].push_back('\'');
								}
							}
						}

						if ((sint)t.conds.size())
						{
							t.opts[3].push_back(1);
						}

						if (codes_->at(eles[x]).id > 0)
						{
							AddStrToVec(&t.conds, "ID = ");
							t.conds[(sint)t.conds.size() - 1].append(ITOA(codes_->at(eles[x]).id));
						}
						else
						{
							sint xc = AddStrToVec(&t.conds, "DATA = X'", false, false);
							if (xc > -1)
							{
								t.conds[xc].append(con_str.c_str());
								t.conds[xc].push_back('\'');
							}
						}
						sint yc = vtool.AddValToVec(&tvec, &t, true, true);
					}
				}
			}
			if (!tvec.empty())
			{
				return Commit(&tvec);
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

		BOT_STMT t(false, 0, "litebot");
		t.opts[0].push_back(0);
		sint rc = t.AddCont("COMMANDS", 1);

		if (conds_)
		{
			if (!conds_->empty())
			{
				for (size_t siz = 0; siz < conds_->size(); siz++)
				{
					AddStrToVec(&t.conds, conds_->at(siz).c_str());
				}
			}
		}
		else
		{
			if (!Command_->cmd.empty())
			{
				t.opts[1].push_back(5);
				rc = t.AddCol("COMMAND", LEncStrI(Uppercase(CleanPunctuation(Command_->cmd.c_str()).c_str()).c_str(), -1).c_str());
			}

			if (Command_->cmd_id > 0)
			{
				if (!t.vals.empty())
				{
					t.opts[3].push_back(0);
				}
				rc = t.AddCol("CMD_ID", ITOA(Command_->cmd_id).c_str());
			}

			if (Command_->id > 0)
			{
				if ((sint)t.opts[3].size() < (sint)t.vals.size() - 1)
				{
					t.opts[3].push_back(0);
				}
				rc = t.AddCol("ID", ITOA(Command_->id).c_str());
			}
		}
		
		rc = BQS(&t);

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
				cchar* tail;
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
										cchar* output("not enough priv");
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
											Command_->cmd.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
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
	sint GetLogin(cchar* str_ = "")
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 ncar;
			sint xc = bot_sprintf(ncar.carr, ncar.siz, "::GetLogin(cchar* str_(%i))", (sint)str_);
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

		BOT_STMT t(false, 0, "litebot");
		sint xc = t.AddCont("ACCOUNTS", 1);
		t.AddCol();
		t.AddCol("LOGIN_NAME", LEncStrI(str_, -1).c_str());
		t.opts[0].push_back(0);
		t.opts[1].push_back(5);
		t.opts[6].push_back(1);
		xc = BQS(&t);

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
				cchar* tail;
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
								if (!strcmp(str_, reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, 2))))
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
											str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, xc)));
											sint rc = SetClientName(&str);
											str.clear();
										}
									}

									//Client.password.append( reinterpret_cast < cchar* > ( sqlite3_column_text( ppstmt, 2 ) ) );
									xc = FindColumn("PRIV", ppstmt);

									if (xc > -1)
									{
										sint rc = SetClientPriv(sqlite3_column_int(ppstmt, xc));
									}

									/*
									if ( sqlite3_column_text( ppstmt, 4 ) != NULL )
									{
									Client_->name.append( reinterpret_cast < cchar* > ( sqlite3_column_text( ppstmt, 4 ) ) );
									}
									*/
									xc = FindColumn("LAST_LOGIN", ppstmt);

									if (xc > -1)
									{
										if (sqlite3_column_text(ppstmt, xc) != NULL)
										{
											str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, xc)));
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
											str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, xc)));
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
		BOT_STMT t(false, 1, "litebot");
		t.opts[0].push_back(0);
		t.opts[9].push_back(0);
		sint xc = t.AddCont("ACCOUNTS", 1);
		std::string condstr;
		condstr.append("LOGIN_NAME = ");
		condstr.append(LEncStrI(Client_->login_name.c_str(), -1));
		xc = AddStrToVec(&t.conds, condstr.c_str());
		t.opts[3].push_back(0);
		condstr.clear();
		condstr.append("ID = ");
		condstr.append(ITOA(Client_->lid));
		xc = AddStrToVec(&t.conds, condstr.c_str());

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
				xc = t.AddCol("PRIV", ITOA(Client_->priv).c_str());
			}

			if (Client_->updatelogin)
			{
				xc = t.AddCol("LAST_LOGIN", LEncStrI(Client_->logindate.c_str(), -1).c_str());
				xc = t.AddCol("TOTAL_LOGINS", ITOA(Client_->totallogins).c_str());
				xc = t.AddCol("FAILED_LOGINS", ITOA(0).c_str());
			}
		}
		else
		{
			if (Client_->updatelogin)
			{
				xc = t.AddCol("LAST_FAILED_LOGIN", LEncStrI(Client_->last_failed_login.c_str(), -1).c_str());
				xc = t.AddCol("FAILED_LOGINS", ITOA(Client_->failed_logins + 1).c_str());
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
			BOT_STMT t(false, 0, dbs_->name.c_str());
			sint xc = t.AddCont("LAST_ACCESS", 1);
			sint fdb = -1;
			sint hdb = -1;
			sint odb = OpenDB(dbs_, 1, &hdb, &fdb);

			if (odb > -1)
			{
				xc = BQS(&t);

				if (!xc)
				{
					d_con_->o_com = true;
					xc = UpdMTXPrio();
					cchar* tail;
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
			BOT_STMT t(true, 0, dbs_->name.c_str());
			sint xc = t.AddCont("LAST_ACCESS", 1);
			sint fdb = -1;
			sint hdb = -1;
			sint odb = OpenDB(dbs_, 2, &hdb, &fdb);

			if (odb > -1)
			{
				xc = BQS(&t);

				if (!xc)
				{
					d_con_->o_com = true;
					xc = UpdMTXPrio();
					cchar* tail;
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
										BOT_STMT t(true, 4, dbs_->name.c_str());
										sint ac = t.AddCont("LAST_ACCESS", 1);
										std::string nstr;
										nstr.append("ID = ");
										nstr.append(ITOA(xc));
										ac = AddStrToVec(&t.conds, nstr.c_str());
										t.opts[0].push_back(0);
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
										BOT_STMT t(true, 4, dbs_->name.c_str());
										sint ac = t.AddCont("LAST_ACCESS", 1);
										std::string nstr;
										nstr.append("ID = ");
										nstr.append(ITOA(xc));
										ac = AddStrToVec(&t.conds, nstr.c_str());
										t.opts[0].push_back(0);
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
					AddStrToVec(&dbs_->tables, bot_strt.litebot_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					char c = ' ';

					if (t < bot_strt.litebot_columns.size())
					{
						std::string str;
						str.append(bot_strt.litebot_columns[t]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.litebot_columns[(sint)bot_strt.litebot_columns.size() - 1]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
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
					AddStrToVec(&dbs_->tables, bot_strt.math_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					char c = ' ';

					if (t < bot_strt.math_columns.size())
					{
						std::string str;
						str.append(bot_strt.math_columns[t]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.math_columns[(sint)bot_strt.math_columns.size() - 1]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
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
				for (uint t = 0; t < bot_strt.code_tablenames.size(); t++)
				{
					AddStrToVec(&dbs_->tables, bot_strt.code_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					char c = ' ';

					if (t < bot_strt.code_columns.size())
					{
						std::string str;
						str.append(bot_strt.code_columns[t]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.code_columns[(sint)bot_strt.code_columns.size() - 1]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
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
			case 3:
			{
				break;
			}
			default:
			{
				for (uint t = 0; t < bot_strt.ex_tablenames.size(); t++)
				{
					AddStrToVec(&dbs_->tables, bot_strt.ex_tablenames[t], false, false);
					std::vector<std::vector<std::string>> tcols;
					dbs_->columns.push_back(tcols);
					std::vector<std::string> cols, colss;
					dbs_->columns[t].push_back(colss);
					dbs_->columns[t].push_back(colss);
					char c = ' ';

					if (t < bot_strt.ex_columns.size())
					{
						std::string str;
						str.append(bot_strt.ex_columns[t]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
					}
					else
					{
						std::string str;
						str.append(bot_strt.ex_columns[(sint)bot_strt.ex_columns.size() - 1]);
						sint xp = SeparateStrByChar(str.c_str(), c, &cols);
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

		sint xc = GetThreadQuit();

		if (xc)
		{
			return -1;
		}

		TINFO_M tts;
		xc = GetVecEle((void*)&tts, MTX_TTS, lid);

		if (xc < 0)
		{
			return -1;
		}

		*thr_opt = tts.opt;
		sllint lc = TestThreadTRat((sint)BOT_ITER_TO);

		if (thr_exe_mod < tts.min_ratv)
		{
			return -5;
		}

		xc = 0;
		sint rc = SetVecEleMem((void*)&xc, MTX_TTS, lid, BOT_TTS_FIN, false);

		if (rc < 0)
		{
			return -1;
		}

		return 0;
	}
	sint ThreadRest(slint dur = BOT_MILLI_REST, sint qt_lvl = -1)
	{
		sint qt = GetThreadQuit();

		if (qt > qt_lvl)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				carr_32 ncar;
				sint rc = bot_sprintf(ncar.carr, ncar.siz, "finish signal");
				rc = Output(ncar.carr, 2);
			}
		}
		else
		{
			slint rst = Rest(dur);
		}
		return qt;
	}
	sint ThreadEnd()
	{
		sint fin = 1;
		sint rc = SetVecEleMem((void*)&fin, MTX_TTS, lid, BOT_TTS_FIN, false);
		return 0;
	}
	sint PThreadErr(char in_chr[], sint err)
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
		sint thr_at = -1;
		sint ret = SetThreadQuit(1);
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
					if (siz != log_at && siz != thr_at)
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
							if (thr_at < 0)
							{
								std::string nm;
								xc = GetVecEleMem((void*)&nm, MTX_TTS, siz, BOT_TTS_TNAME);

								if (!strcmp(nm.c_str(), "ThreadMaintenance"))
								{
									thr_at = siz;
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

		sint xc = CreateThread(tts_);

		if (!xc)
		{
			xc = FinishThread(tts_, ret_);

			while (xc)
			{
				slint rst = Rest(BOT_MILLI_REST);
				xc = FinishThread(tts_, ret_);
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
			sint tret = CreateThread(&tts_->at(siz));

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
					tret = FinishThread(&tts_->at(nsiz), &xret);

					if (nsiz < rets_->size())
					{
						rets_->at(nsiz) = xret;
					}
					else
					{
						rets_->push_back(xret);
					}

					if (tret)
					{

						sint e = -1;
					}
				}
				msiz = siz + 1;
			}
		}
		return ret;
	}
	sint CreateThread(TINFO_M* tts_ = 0)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::CreateThread(TINFO_M* tts_(%i))", (sint)tts_);
			op = Output(outp.carr, 2);
		}

		if (!tts_)
		{
			return -1;
		}

		TINFO tts(tts_->opt, tts_->thread_name.c_str(), tts_->func, tts_->c_by, tts_->min_ratv);
		tts.fin = -2;
		sint xc = PushToVec(&tts, MTX_TTS, true, true, false);

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
			mk_thr = true;
			na = UpdMTXPrio();

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
				xc = Output("error: decrementing open thread count.", 1, 2);
				return xc;
			}

			sint h = -1;
			sint p = LockElement(MTX_TTS, tts.lid, &h, true, false);

			if (p > -1)
			{
				xc = pthread_create(&tts.thread, &tts.attr, tts.func, (void*)tts.lid);

				if (!xc)
				{
					na = pthread_attr_destroy(&tts.attr);

					if (na)
					{

						na = -1;
					}
					na = SetVecEle((void*)&tts, MTX_TTS, tts.lid, false, false);
					tts_->Renew(&tts);
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
						na = bot_sprintf(ncar.carr, ncar.siz, "thread created, tts_->lid=%i, initializing thread:%s", tts.lid, tts.thread_name.c_str());
					}
					na = Output(ncar.carr, 2);
				}
			}
			mk_thr = false;
			na = UpdMTXPrio();
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

		switch (tts_->opt)
		{
		case 0:
		{
			xc = tts_->opt;
			break;
		}
		case 1:
		{
			xc = Output("attempting to join thread", 2);
			xc = GetVecEle(tts_, MTX_TTS, tts_->lid);

			if (xc > -1)
			{
				if (tts_->fin == 1 || tts_->fin == -1)
				{
					mk_thr = true;
					xc = UpdMTXPrio();

					sint hx = -1;
					sint lx = LockElement(MTX_TTS, tts_->lid, &hx, true, false);

					if (lx > -1)
					{
						
						void* vp_ = 0;
						/*sint h = -1;
						sint l = LockGMutex(MTX_TTS, &h);

						if (l > -1)
						{
							xc = pthread_join(tts_vec.d_vec[tts_->lid].thread, &vp_);

							if (!h)
							{
								h = UnlockGMutex(MTX_TTS);
							}
						}*/

						/*TINFO nt;
						xc = GetVecEle((void*)&nt, MTX_TTS, tts_->lid, false);

						if (xc > -1)
						{
							xc = pthread_join(nt.thread, &vp_);
						}*/

						xc = JoinThread(tts_->lid, vp_);

						if (xc)
						{
							if (debug_lvl >= 1 && debug_m)
							{
								carr_128 outp;
								sint rc = bot_sprintf(outp.carr, outp.siz, "Error(%i) joining thread:%i", xc, tts_->lid);
								rc = Output(outp.carr, 1, 2);
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
									sint rc = bot_sprintf(outp.carr, outp.siz, "thread joined, tts_->lid:%i *ret_:(%i)", tts_->lid, *ret_);
									rc = Output(outp.carr, 2);
								}
							}
							else
							{
								xc = (sint)vp_;

								if (debug_lvl >= 1 && debug_m)
								{
									carr_128 outp;
									sint rc = bot_sprintf(outp.carr, outp.siz, "error: thread joined, tts_->lid=%i xc==%i, return value will be lost as it was not assigned.", tts_->lid, xc);
									rc = Output(outp.carr, 1, 2);
								}
							}
							
							sint rc = ClearVecEle(MTX_TTS, tts_->lid, false);
							rc = IncrThreads();

							if (rc < 0)
							{
								rc = Output("error: incrementing open thread count.", 1, 2);
							}
							else
							{
								xc = 0;
							}
						}
						if (!hx)
						{
							hx = UnlockElement(MTX_TTS, tts_->lid, false);
						}
						mk_thr = false;
						sint rc = UpdMTXPrio();
						tts_->Clear();
					}
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
		return xc;
	}
	sint TM(sint opt)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "::TM(sint opt(%i))", opt);
			op = Output(outp.carr, 2);
		}

		bool has_dm = false;
		bool has_tm = false;
		bool has_self = false;
		bool has_log = false;
		std::vector<TINFO_M> create_vec;

		for (sint p = 0; p < VecSize(MTX_TTS); p++)
		{
			TINFO_M ntts;
			sint sp = GetVecEle(&ntts, MTX_TTS, p);

			if (!strcmp(ntts.thread_name.c_str(), "machine"))
			{
				has_self = true;
			}
			else if (!strcmp(ntts.thread_name.c_str(), "LogMaintenance"))
			{
				has_log = true;
			}
			if (!strcmp(ntts.thread_name.c_str(), "ThreadMaintenance"))
			{
				has_tm = true;
			}
			else if (!strcmp(ntts.thread_name.c_str(), "DBMaintenance"))
			{
				has_dm = true;
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
				//create_vec.push_back(ntts);
			}
			else {}
		}

		if (debug_lvl >= 1 && debug_m)
		{
			sint xc = Output("creating test threads", 2);
		}

		if (!lid)
		{
			for (sint p = 0; p < 100; p++)
			{
				char tn[32];
				sint ntn = bot_sprintf(tn, 32, "TestThread(%i)", p);
				TINFO_M tts(1, tn, TestThread, lid);
				create_vec.push_back(tts);
			}
		}

		std::vector<sint> rets;
		sint p = InitThreads(&create_vec, &rets);

		if (!create_vec.empty())
		{
			if (debug_lvl >= 1 && debug_m)
			{
				carr_64 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, "found (%u) threads uncreated", create_vec.size());
				op = Output(outp.carr, 2);
			}
		}
		if (!has_self && !lid)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				sint xc = Output("adding machine to thread list", 2);
			}
			TINFO_M tts(0, ptn.c_str(), NULL);
			tts.fin = 0;
			sint xc = PushToVec(&tts, MTX_TTS, true, true, false);
		}
		if (!has_log)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				sint xc = Output("adding LogMaintenance to thread list", 2);
			}
			TINFO_M tts(0, "LogMaintenance", LogMaintenance, lid);
			sint xc = InitThread(&tts);
		}
		if (!has_dm)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				sint xc = Output("adding DBMaintenance to thread list", 2);
			}
			TINFO_M tts(0, "DBMaintenance", DBMaintenance, lid);
			sint xc = InitThread(&tts);
		}
		if (!has_tm)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				sint xc = Output("adding ThreadMaintenance to thread list", 2);
			}
			TINFO_M tts(0, "ThreadMaintenance", ThreadMaintenance, lid);
			sint xc = InitThread(&tts);
		}
		return 0;
	}
	sllint TestThreadIter(sint to_ = (sint)BOT_ITER_TO)
	{
		std::chrono::steady_clock::time_point t_I = std::chrono::steady_clock::now();
		float val = 3610.0f;

		for (sint xc = 0; xc < to_; xc++)
		{
			val /= 1.333f;
		}

		std::chrono::steady_clock::time_point t_II = std::chrono::steady_clock::now();
		std::chrono::duration < sllint, std::nano > span = std::chrono::duration_cast<std::chrono::duration < sllint, std::nano > >(t_II - t_I);
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

	static void* DBMaintenance(void * vp);
	static void* LITEBotMaintenance(void * vp);
	static void* CodeMaintenance(void * vp);
	static void* AddThisCode(void * vp);
	static void *LogMaintenance(void * vp);
	static void *ThreadMaintenance(void * vp);
	static void *TestThread(void * vp);

	sint CheckPrintFs()
	{
		BOT_FILE_M xfile("litebot", ".h", BOT_MOD_PATH, lid, BOT_FILE_READ);
		sint of = -1;
		sint lx = OpenFile(&xfile, &of);

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

							for (uint x = litv[0] + 1; x < litv[litv.size()-1]; x++)
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
				of = CloseFile(&xfile);
			}
		}

		if (lx > -1)
		{
			xfile.Renew("litebot", ".cpp", BOT_MOD_PATH, lid, BOT_FILE_READ);
			sint of = -1;
			lx = OpenFile(&xfile, &of);

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

								for (uint x = litv[0] + 1; x < litv[litv.size()-1]; x++)
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
					of = CloseFile(&xfile);
				}
				return lx;
			}
		}
		return -1;
	}

	// work
	
	sint ProcErrLog(sint opt = -1, cchar* in_file_p = "", cchar* in_file_n = "", cchar* in_file_t = "", cchar* rampid = "", cchar* insp_type = "", cchar* date_ = "", cchar* eid_ = "", cchar* toval_ = "")
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
		BOT_FILE_M xfile(in_file_n, in_file_t, in_file_p, lid, BOT_FILE_READ);
		of = -1;
		sint lx = OpenFile(&xfile, &of);

		if (lx > -1)
		{
			char spc = ' ';
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
				of = CloseFile(&xfile);
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
			xfile.Renew(nm_str.c_str(), ".txt", BOT_MOD_PATH, lid, BOT_FILE_APPEND);
			of = -1;
			lx = OpenFile(&xfile, &of, true);

			for (uint siz = 0; siz < vvec.size(); siz++)
			{
				f_con[xfile.fcon]->fstrm << vvec[siz].carr << std::endl;
			}

			if (!of)
			{
				of = CloseFile(&xfile);
			}
			return 0;
		}
		return -1;
	}

	sint ProcVINs(sint opt = -1, cchar* in_file_p = "", cchar* in_file_n = "", cchar* in_file_t = "", cchar* rampid = "", cchar* insp_type = "", cchar* date_ = "", cchar* eid_ = "", cchar* toval_ = "")
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
		BOT_FILE_M xfile(in_file_n, in_file_t, in_file_p, lid, BOT_FILE_READ);
		of = -1;
		sint lx = OpenFile(&xfile, &of);

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
				of = CloseFile(&xfile);
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
			
			xfile.Renew(nm_str.c_str(), ".txt", BOT_MOD_PATH, lid, BOT_FILE_APPEND);
			of = -1;
			lx = OpenFile(&xfile, &of, true);

			for (uint siz = 0; siz < vvec.size(); siz++)
			{
				f_con[xfile.fcon]->fstrm << vvec[siz].c_str() << std::endl;
			}

			if (!of)
			{
				of = CloseFile(&xfile);
			}
			return 0;
		}
		return -1;
	}

	sint GetVINs(cchar* in_file_p = "", cchar* in_file_n = "", cchar* in_file_t = "", cchar* rampid = "")
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
		BOT_FILE_M xfile(in_file_n, in_file_t, in_file_p, lid, BOT_FILE_READ);
		sint of = -1;
		sint lx = OpenFile(&xfile, &of);

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
				of = CloseFile(&xfile);
			}

			std::string nm_str;
			carr_32 dcar;
			of = GetDate(&dcar, false);
			nm_str.append(rampid);
			nm_str.append("vins");
			nm_str.append(dcar.carr);
			xfile.Renew(nm_str.c_str(), ".txt", BOT_MOD_PATH, lid, BOT_FILE_APPEND);
			of = -1;
			lx = OpenFile(&xfile, &of, true);

			for (uint siz = 0; siz < vvec.size(); siz++)
			{
				f_con[xfile.fcon]->fstrm << vvec[siz].c_str() << std::endl;
			}

			if (!of)
			{
				of = CloseFile(&xfile);
			}
		}
		return -1;
	}

	sint AddDlrCode(cchar* to_vin = "", cchar* in_file = "")
	{
		if (strlen(to_vin) != 17)
		{
			return -1;
		}

		std::cout << "searching for VIN: " << to_vin << " to correct dealer code in file: " << in_file << std::endl;
		BOT_FILE_M xfile(in_file, ".txt", BOT_MOD_PATH, lid, BOT_FILE_OVERW);
		sint of = -1;
		sint lx = OpenFile(&xfile, &of);

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
						char cvin[18] = { 0 };

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
								of = CloseFile(&xfile);
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
				of = CloseFile(&xfile);
			}
		}
		return -1;
	}
	
	std::vector<cchar* > sql_vals_keywords
	{
		"INTEGER",
		"REAL",
		"TEXT",
		"BLOB",
		"NULL"
	};
	
	std::vector<char > sql_opers_keywords
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
	
	std::vector<cchar* > sql_trans_keywords
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

	std::vector<cchar* > sql_obj_keywords
	{
		"DATABASE",
		"TABLE",
		"INDEX",
		"COLUMN",
		"VIEW",
		"TRIGGER",
		"ROW"
	};
	
	std::vector<cchar* > sql_obj_qual_keywords
	{
		"UNIQUE",
		"TEMP",
		"DISTINCT",
		"VIRTUAL"
	};
	
	std::vector<cchar* > sql_trans_spec_keywords
	{
		"FROM",
		"ON"
	};

	std::vector<cchar* > sql_targ_keywords
	{
		"USING",
		"FROM",
		"ON"
	};
	
	std::vector<cchar* > sql_create_cond_keywords
	{
		"EXISTS"
	};
	
	std::vector<cchar* > sql_cond_qual_keywords
	{
		"IF",
		"IF NOT"
	};
	
	std::vector<cchar* > sql_act_keywords
	{
		"SET",
		"ADD",
		"RENAME TO"
	};
	
	std::vector<cchar* > sql_decl_keywords
	{
		"VALUES",
		"ORDER BY",
		"GROUP BY"
	};
	
	std::vector<cchar* > sql_cspec_keywords
	{
		"WHERE",
		"AS",
		"VALUES"
	};
	
	std::vector<cchar* > sql_comp_keywords
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
	
	std::vector<cchar* > sql_conj_keywords
	{
		"AND",
		"OR",
		"BETWEEN"
	};

	std::vector<char > nrts_sep
	{
		' ',
		','
	};

	std::vector<char > nrts_ord
	{
		'(',
		'{',
		'[',
		'<'
	};
	std::vector<char > nrts_ord_
	{
		')',
		'}',
		']',
		'>'
	};

	std::vector<char > nrts_ass
	{
		'='
	};

	std::vector<char > nrts_end
	{
		';',
		'\0'
	};

	std::vector<char > nrts_lit
	{
		'\'',
		'"'
	};

	std::vector<char > nrts_pun
	{
		';',
		'.',
		'?',
		'!',
		','
	};
};

#endif