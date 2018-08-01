#include "litebot.h"

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
BOT_DIR bot_dmap("c:\\");
#else
#ifdef _BOT_FOR_ANDR_
BOT_DIR bot_dmap("/storage/emulated/0/Android/data/com.litebot/files/");
#else
#ifdef __GNUC__
BOT_DIR bot_dmap("c:\\");
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
sint main()
{
	sint xc = 0;
	carr_256 ncar;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, 0, "machine", true, true);
	xc = LITEBot.LITEBot(&ncar, true);
	std::cout << ncar.carr << std::endl;

	pthread_exit(NULL);
	return 0;
}

bool bot_sisn(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}
	sint x = 0;
	c_char* nstr = "0123456789";

	for (slen--; slen > 0; slen--)
	{
		x = 0;

		while (x < 10)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[slen], 1))
			{
				x = 10;
			}
			x++;
		}

		if (x == 10)
		{
			return false;
		}
	}
	return true;
}
sint bot_shasn(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return -1;
	}
	uint x = 0;
	c_char* nstr = "0123456789";

	for (slen--; slen > 0; slen--)
	{
		for (x = 0; x < 10; x++)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[slen], 1))
			{
				return (sint)slen;
			}
		}
	}
	return -1;
}
bool bot_sisa(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}
	sint x = 0;
	c_char* nstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	for (slen--; slen > 0; slen--)
	{
		x = 0;

		while (x < 53)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[slen], 1))
			{
				x = 10;
			}
			x++;
		}

		if (x == 10)
		{
			return false;
		}
	}
	return true;
}
sint bot_shasa(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return -1;
	}
	uint x = 0;
	c_char* nstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	for (slen--; slen > 0; slen--)
	{
		for (x = 0; x < 53; x++)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[slen], 1))
			{
				return (sint)slen;
			}
		}
	}
	return -1;
}

sint bot_str_err(sint err_no, c_char* msg)
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

const size_t bot_sintlen(sint val[])
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

const size_t bot_uintlen(uint val[])
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

const size_t bot_dbllen(double val[])
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

const size_t bot_ustrlen(u_char val[])
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

const size_t bot_custrlen(cu_char val[])
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

void bot_strcpy(_char inv[], _char val[])
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
	memcpy((void*)&inv[isiz - 1], (void*)&term, sizeof(inv[isiz - 1]));
}

void bot_ustrcpy(u_char inv[], u_char val[])
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

void bot_strclr(_char inchr[])
{
	if (!inchr)
	{
		return;
	}
	inchr = { 0 };
}

void bot_ustrclr(u_char inchr[])
{
	if (!inchr)
	{
		return;
	}
	inchr = { 0 };
}

void bot_cstrclr(c_char inchr[])
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

void bot_custrclr(cu_char inchr[])
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

sint bot_strchk(_char inchr[], size_t in_siz)
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

sint bot_ustrchk(u_char inchr[], size_t in_siz)
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

sint bot_randstr(_char str_[], size_t siz, _char fstr_[], size_t fsiz)
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

sint bot_sprintf(_char inchr[], size_t in_siz, c_char* fstr, ...)
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

sint bot_sprintf(c_char inchr[], size_t in_siz, c_char* fstr, ...)
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

sint bot_sprintfs(std::string* str_, bool clear_str, c_char* fstr, ...)
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

errno_t bot_itoa(sint i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%i", i); }
errno_t bot_itoa(slint i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%li", i); }
errno_t bot_itoa(sllint i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lli", i); }
errno_t bot_itoa(uint i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%u", i); }
errno_t bot_itoa(ulint i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lu", i); }
errno_t bot_itoa(ullint i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%llu", i); }
errno_t bot_dtoa(double i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%d", i); }
errno_t bot_dtoa(long double i, _char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%ld", i); }

errno_t bot_itoa(sint i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%i", i); }
errno_t bot_itoa(slint i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%li", i); }
errno_t bot_itoa(sllint i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lli", i); }
errno_t bot_itoa(uint i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%u", i); }
errno_t bot_itoa(ulint i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%lu", i); }
errno_t bot_itoa(ullint i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%llu", i); }
errno_t bot_dtoa(double i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%d", i); }
errno_t bot_dtoa(long double i, c_char in_chr[], size_t in_siz, sint radix) { if (!in_chr || !in_siz) { return -1; } return (errno_t)bot_sprintf(in_chr, in_siz, "%ld", i); }

errno_t bot_itoa(sint i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%i", i); }
errno_t bot_itoa(slint i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%li", i); }
errno_t bot_itoa(sllint i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%lli", i); }
errno_t bot_itoa(uint i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%u", i); }
errno_t bot_itoa(ulint i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%lu", i); }
errno_t bot_itoa(ullint i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%llu", i); }
errno_t bot_dtoa(double i, std::string* str, sint radix) { if (!str) { return -1; } return (errno_t)bot_sprintfs(str, true, "%d", i); }
errno_t bot_dtoa(long double i, std::string* str, size_t in_siz, sint radix) { if (!str || !in_siz) { return -1; } return (errno_t)bot_sprintfs(str, true, "%ld", i); }

machine::machine(sint i_debug_lvl, sint i_debug_m, sint nlid, c_char* i_name, bool logmain, bool logmine)
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

sint machine::LITEBot(carr_256 *ncar_, bool do_start_up)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint rc = bot_sprintf(outp.carr, outp.siz, "LITEBot(carr_256* ncar_(%i), bool do_start_up(%u))", (sint)ncar_, (uint)do_start_up);
		rc = Output(outp.carr, 2);
	}
	if (!ncar_)
	{
		return -1;
	}
	sint xc = -1;

#ifdef _WIN32
	WSADATA WSD;

	if ((xc = WSAStartup(MAKEWORD(1, 1), &WSD)) != 0)
	{
		if ((xc = WSAStartup(MAKEWORD(2, 2), &WSD)) != 0)
		{
			sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "Windows Network Startup Failed (%i)", xc);
			return -1;
		}
	}
#endif

	/*if (do_start_up)
	{
	sint xc = ProcVINs(2, BOT_MOD_PATH, "error032418", ".txt", "27", "04", "03/25/2018", "237", "08");
	xc = ProcVINs(3, BOT_MOD_PATH, "error032418", ".txt", "27", "04", "03/25/2018", "237", "03/25/2018");
	xc = ProcErrLog(3, BOT_MOD_PATH, "error032418", ".txt", "27", "04", "03/25/2018", "237", "03/24/2018");

		if (xc)
		{
			sint e = -1;
		}
	}*/

	//TINFO tts(0, ptn.c_str(), NULL, 0);
	//tts.lid = lid;
	//tts.fin = 0;
	//tts.t_I = std::chrono::steady_clock::now();
	//sint xc = PushToVec(&tts, MTX_TTS, true, true, false);

	//std::chrono::steady_clock::time_point tI = std::chrono::steady_clock::now();
	//sint xc = BOTFindHomeDir();
	//std::chrono::steady_clock::time_point tII = std::chrono::steady_clock::now();
	//std::chrono::duration<slint, std::milli> durI = std::chrono::duration_cast<std::chrono::duration<slint, std::milli>>(tII - tI);
	//tI = std::chrono::steady_clock::now();
	xc = BOTFindHomeDir();
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
#ifdef _WIN32
	sint oc = WSACleanup();
#endif
	return xc;
}

sint machine::LockReq()
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
sint machine::UnlockReq()
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
sint machine::CheqMTXReqs(std::vector<lok_req>* nreqs_)
{
	if (!nreqs_)
	{
		return -1;
	}

	sint p = LockReq();

	if (!p)
	{
		sint xl = vtool.VIV(&lok_d.held_ids, lid);

		if (xl > -1)
		{
			for (uint z = 0; z < lok_d.reqs.size(); z++)
			{
				if (lok_d.reqs[z].lid > -1)
				{
					if (lok_d.reqs[z].fid != lid && lok_d.reqs[z].fid > -1)
					{
						sint yl = vtool.VIV(&lok_d.held[xl], lok_d.reqs[z].gmtx);

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
									sint nl = vtool.VIV(&lok_d.held[xl][yl].h_mems, lok_d.reqs[z].ele);

									if (nl > -1)
									{
										sint i = vtool.VIV(&lok_d.held_ids, lok_d.reqs[z].fid);

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
									sint nl = vtool.VIV(&lok_d.held[xl][yl].m_mems, lok_d.reqs[z].ele);

									if (nl > -1)
									{
										sint i = vtool.VIV(&lok_d.held_ids, lok_d.reqs[z].fid);

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
sint machine::UpdMTXPrio()
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
		sint xc = vtool.VIV(&lok_d.held_ids, lid);

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
sint machine::UpdMTX()
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
		sint x = vtool.CLNV(&h_mtxs);
	}

	sint ret = -1;
	sint p = LockReq();

	if (!p)
	{
		sint xc = vtool.VIV(&lok_d.held_ids, lid);

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
						ret = vtool.AVTV(&lok_d.held[xc], &h_mtxs[x], false, true);
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
			xc = vtool.AVTV(&lok_d.held_ids, lid, false, true);

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
						ret = vtool.AVTV(&lok_d.held[xc], &h_mtxs[x], false, true);
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
sint machine::ReqMTX(lok_req* nreq, bool wait)
{
	if (!nreq)
	{
		return -1;
	}

	sint ret = 0;
	sint p = LockReq();

	if (!p)
	{
		sint i_ele = vtool.VIV(&lok_d.held_ids, lid);
		sint f_ele = vtool.VIV(&lok_d.held_ids, -1);

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

			sint x = vtool.VIV(&lok_d.held[i_ele], nreq->gmtx);

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
						sint y = vtool.VIV(&lok_d.held[i_ele][x].m_mems, nreq->ele);

						if (y > -1)
						{
							p = UnlockReq();
							return 0;
						}
					}
					else
					{
						sint y = vtool.VIV(&lok_d.held[i_ele][x].h_mems, nreq->ele);

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
				sint x = vtool.VIV(&lok_d.held[siz], nreq->gmtx);

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
							sint y = vtool.VIV(&lok_d.held[siz][x].m_mems, nreq->ele);

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
							sint y = vtool.VIV(&lok_d.held[siz][x].h_mems, nreq->ele);

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
				sint x = vtool.AVTV(&lok_d.reqs, nreq, true, true);

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
			sint x = vtool.VIV(&h_mtxs, nreq->gmtx);

			if (x < 0)
			{
				HELD_MTX nmtx(nreq->gmtx, -1, false);
				x = vtool.AVTV(&h_mtxs, &nmtx, false, true);
			}
			if (nreq->ele < 0)
			{
				h_mtxs[x].locked = true;
			}
			else
			{
				if (!nreq->is_meta)
				{
					sint y = vtool.AVTV(&h_mtxs[x].h_mems, nreq->ele, true, true);
				}
				else
				{
					sint y = vtool.AVTV(&h_mtxs[x].m_mems, nreq->ele, true, true);
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
sint machine::WithdMTXReq(lok_req* nreq)
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
			ret = vtool.VIV(&lok_d.reqs, nreq);
		}
		else
		{
			ret = nreq->lid;
		}

		if (ret > -1)
		{
			p = vtool.CEFV(&lok_d.reqs, ret);
		}

		p = vtool.CLNV(&lok_d.reqs);
		p = UnlockReq();
	}
	return ret;
}

sint machine::HasLock(sint g_opt, sint ele, bool is_meta)
{
	if (g_opt < 0)
	{
		return -1;
	}

	sint xret = vtool.VIV(&h_mtxs, g_opt);

	if (xret > -1)
	{
		if (ele > -1)
		{
			if (!is_meta)
			{
				xret = vtool.VIV(&h_mtxs[xret].h_mems, ele);
			}
			else
			{
				xret = vtool.VIV(&h_mtxs[xret].m_mems, ele);
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

sint machine::LockGMutex(sint g_opt, sint* had_lock, bool sleep_wait)
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

	sint ele = vtool.VIV(&h_mtxs, g_opt);

	if (ele < 0)
	{
		HELD_MTX nmtx(g_opt, (sint)h_mtxs.size(), false);
		ele = vtool.AVTV(&h_mtxs, &nmtx, false, true);

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
sint machine::UnlockGMutex(sint g_opt)
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

	sint ele = vtool.VIV(&h_mtxs, g_opt);
	sint lox;

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

sint machine::LockElement(sint g_opt, sint ele, sint* had_lock, bool sleep_wait , bool is_meta)
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

	sint ret = vtool.VIV(&h_mtxs, g_opt);

	if (ret < 0)
	{
		HELD_MTX nmtx(g_opt, -1, false);
		ret = vtool.AVTV(&h_mtxs, &nmtx, true, true);

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
			ret = vtool.VIV(&h_mtxs[xret].h_mems, ele);
		}
		else
		{
			ret = vtool.VIV(&h_mtxs[xret].m_mems, ele);
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
sint machine::UnlockElement(sint g_opt, sint ele, bool is_meta)
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

	sint p = vtool.VIV(&h_mtxs, g_opt);

	if (p < 0)
	{
		return -1;
	}

	sint ret = -1;

	if (!is_meta)
	{
		ret = vtool.VIV(&h_mtxs[p].h_mems, ele);
	}
	else
	{
		ret = vtool.VIV(&h_mtxs[p].m_mems, ele);
	}

	if (ret > -1)
	{
		if (!is_meta)
		{
			sint xc = vtool.CFV(&h_mtxs[p].h_mems, ele, false);
			xc = vtool.CLNV(&h_mtxs[p].h_mems);
		}
		else
		{
			sint xc = vtool.CFV(&h_mtxs[p].m_mems, ele, false);
			xc = vtool.CLNV(&h_mtxs[p].m_mems);
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

sint machine::OpenObject(sint nobj, sint nele, sint is_meta, sint* omode, sint* r_opt, sint* n_opt)
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
				ret = vtool.VIV(&f_con, nele);

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
sint machine::CloseObject(sint nobj, sint nele, sint is_meta, sint* r_opt, sint* n_opt)
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
			sint ret = vtool.VIV(&h_mtxs, nobj);

			if (ret > -1)
			{
				if (!is_meta)
				{
					sint xret = ret;
					ret = vtool.VIV(&h_mtxs[xret].h_mems, nele);

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
					ret = vtool.VIV(&h_mtxs[xret].m_mems, nele);

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
			sint ret = vtool.VIV(&h_mtxs, nobj);

			if (ret > -1)
			{
				if (!is_meta)
				{
					sint xret = ret;
					ret = vtool.VIV(&h_mtxs[xret].h_mems, nele);

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
					ret = vtool.VIV(&h_mtxs[xret].m_mems, nele);

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

sint machine::PushToVec(void *val_, sint g_opt, bool check, bool use_empty, bool is_meta)
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
					ret = vtool.AVTV(&bot_c_vec.d_vec, vp, check, use_empty);

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
					ret = vtool.AVTV(&bot_log_vec.d_vec, vp, check, use_empty);

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
					ret = vtool.AVTV(&tts_vec.d_vec, vp, check, use_empty);

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
					ret = vtool.AVTV(&bot_db_vec.d_vec, vp, check, use_empty);

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
					ret = vtool.AVTV(&fileo_vec.d_vec, vp, check, use_empty);

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
					ret = vtool.AVTV(&bot_c_vec.m_vec, vp, check, use_empty);
				}
				break;
			}
			case MTX_LOG:
			{
				BOT_LOGDET_M* vp = reinterpret_cast<BOT_LOGDET_M*>(val_);

				if (!vp->logtitle.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&bot_log_vec.m_vec, vp, check, use_empty);
				}
				break;
			}
			case MTX_TTS:
			{
				TINFO_M* vp = reinterpret_cast<TINFO_M*>(val_);

				if (!vp->thread_name.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&tts_vec.m_vec, vp, check, use_empty);
				}
				break;
			}
			case MTX_DBL:
			{
				BOT_DB_M* vp = reinterpret_cast<BOT_DB_M*>(val_);

				if (!vp->name.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&bot_db_vec.m_vec, vp, check, use_empty);
				}
				break;
			}
			case MTX_FO:
			{
				BOT_FILE_M* vp = reinterpret_cast<BOT_FILE_M*>(val_);

				if (!vp->name.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&fileo_vec.m_vec, vp, check, use_empty);
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
sint machine::PushToVecEleMem(void *val_, sint g_opt, sint ele, sint memb, sint v_opt, bool is_meta)
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
					ret = vtool.PTM(&bot_c_vec.d_vec, ele, memb, v_opt, val_);

					if (ret > -1)
					{
						sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.PTM(&bot_log_vec.d_vec, ele, memb, v_opt, val_);

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
					ret = vtool.PTM(&tts_vec.d_vec, ele, memb, v_opt, val_);

					if (ret > -1)
					{
						sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.PTM(&bot_db_vec.d_vec, ele, memb, v_opt, val_);

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
					ret = vtool.PTM(&fileo_vec.d_vec, ele, memb, v_opt, val_);

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
					ret = vtool.PTM(&bot_c_vec.m_vec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.PTM(&bot_log_vec.m_vec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.PTM(&tts_vec.m_vec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.PTM(&bot_db_vec.m_vec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.PTM(&fileo_vec.m_vec, ele, memb, v_opt, val_);
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
sint machine::GetInVec(void* val_, sint g_opt, bool cine, bool is_meta)
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
sint machine::GetVecEle(void* val_, sint g_opt, sint ele, bool is_meta)
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
					ret = vtool.GVIV(&bot_c_vec.d_vec, ele, (BOT_CLIENT*)val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GVIV(&bot_log_vec.d_vec, ele, (BOT_LOGDET*)val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GVIV(&tts_vec.d_vec, ele, (TINFO*)val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GVIV(&bot_db_vec.d_vec, ele, (BOT_DB*)val_);
					break;
				}
				case MTX_DBC:
				{
					ret = vtool.GVIA(DCON, ele, (DB_CONN*)val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GVIV(&fileo_vec.d_vec, ele, (BOT_FILE*)val_);
					break;
				}
				case MTX_FCON:
				{
					ret = vtool.GVIA(FCON, ele, (BOTF_CONN*)val_);
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
					ret = vtool.GVIV(&bot_c_vec.m_vec, ele, (BOT_CLIENT_M*)val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GVIV(&bot_log_vec.m_vec, ele, (BOT_LOGDET_M*)val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GVIV(&tts_vec.m_vec, ele, (TINFO_M*)val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GVIV(&bot_db_vec.m_vec, ele, (BOT_DB_M*)val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GVIV(&fileo_vec.m_vec, ele, (BOT_FILE_M*)val_);
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
sint machine::GetEmptyVecEle(sint g_opt, bool is_meta, sint mode)
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
	if (mode > 0 || mode < 0)
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
sint machine::GetVecEleMem(void* val_, sint g_opt, sint ele, sint memb, bool is_meta)
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
					ret = vtool.GMIV(&bot_c_vec.d_vec, ele, memb, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GMIV(&bot_log_vec.d_vec, ele, memb, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GMIV(&tts_vec.d_vec, ele, memb, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GMIV(&bot_db_vec.d_vec, ele, memb, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GMIV(&fileo_vec.d_vec, ele, memb, val_);
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
					ret = vtool.GMIV(&bot_c_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GMIV(&bot_log_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GMIV(&tts_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GMIV(&bot_db_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GMIV(&fileo_vec.m_vec, ele, memb, val_);
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
sint machine::SetVecEle(void* val_, sint g_opt, sint ele, bool cine, bool is_meta)
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
						x = vtool.AVTV(&bot_c_vec.m_vec, &nval, false, false);
					}
					else
					{
						BOT_CLIENT nval;
						x = vtool.AVTV(&bot_c_vec.d_vec, &nval, false, false);
					}
					break;
				}
				case MTX_LOG:
				{
					if (is_meta)
					{
						BOT_LOGDET_M nval;
						x = vtool.AVTV(&bot_log_vec.m_vec, &nval, false, false);
					}
					else
					{
						BOT_LOGDET nval;
						x = vtool.AVTV(&bot_log_vec.d_vec, &nval, false, false);
					}
					break;
				}
				case MTX_TTS:
				{
					if (is_meta)
					{
						TINFO_M nval;
						x = vtool.AVTV(&tts_vec.m_vec, &nval, false, false);
					}
					else
					{
						TINFO nval;
						x = vtool.AVTV(&tts_vec.d_vec, &nval, false, false);
					}
					break;
				}
				case MTX_DBL:
				{
					if (is_meta)
					{
						BOT_DB_M nval;
						x = vtool.AVTV(&bot_db_vec.m_vec, &nval, false, false);
					}
					else
					{
						BOT_DB nval;
						x = vtool.AVTV(&bot_db_vec.d_vec, &nval, false, false);
					}
					break;
				}
				case MTX_FO:
				{
					if (is_meta)
					{
						BOT_FILE_M nval;
						x = vtool.AVTV(&fileo_vec.m_vec, &nval, false, false);
					}
					else
					{
						BOT_FILE nval;
						x = vtool.AVTV(&fileo_vec.d_vec, &nval, false, false);

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
					ret = vtool.SVIV(&bot_c_vec.d_vec, ele, (BOT_CLIENT*)val_);

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
					ret = vtool.SVIV(&bot_log_vec.d_vec, ele, (BOT_LOGDET*)val_);

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
					ret = vtool.SVIV(&tts_vec.d_vec, ele, (TINFO*)val_);

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
					ret = vtool.SVIV(&bot_db_vec.d_vec, ele, (BOT_DB*)val_);

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
					ret = vtool.SVIV(&fileo_vec.d_vec, ele, (BOT_FILE*)val_);

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
					ret = vtool.SVIV(&bot_c_vec.m_vec, ele, (BOT_CLIENT_M*)val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.SVIV(&bot_log_vec.m_vec, ele, (BOT_LOGDET_M*)val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.SVIV(&tts_vec.m_vec, ele, (TINFO_M*)val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.SVIV(&bot_db_vec.m_vec, ele, (BOT_DB_M*)val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.SVIV(&fileo_vec.m_vec, ele, (BOT_FILE_M*)val_);
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
sint machine::SetVecEleMem(void* val_, sint g_opt, sint ele, sint memb, bool is_meta)
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
					ret = vtool.SMIV(&bot_c_vec.d_vec, ele, memb, val_);

					if (ret > -1)
					{
						sint iret = SetVecEleMem(val_, g_opt, ele, memb);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.SMIV(&bot_log_vec.d_vec, ele, memb, val_);

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
					ret = vtool.SMIV(&tts_vec.d_vec, ele, memb, val_);
					if (ret > -1)
					{
						sint iret = SetVecEleMem(val_, g_opt, ele, memb);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.SMIV(&bot_db_vec.d_vec, ele, memb, val_);

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
					ret = vtool.SMIV(&fileo_vec.d_vec, ele, memb, val_);

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
					ret = vtool.SMIV(&bot_c_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.SMIV(&bot_log_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.SMIV(&tts_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.SMIV(&bot_db_vec.m_vec, ele, memb, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.SMIV(&fileo_vec.m_vec, ele, memb, val_);
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
sint machine::ClearVecEle(sint g_opt, sint ele, bool is_meta)
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
					ret = vtool.CEFV(&bot_c_vec.d_vec, ele);
					sint cl = vtool.CLNV(&bot_c_vec.d_vec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CEFV(&bot_log_vec.d_vec, ele);
					sint cl = vtool.CLNV(&bot_log_vec.d_vec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CEFV(&tts_vec.d_vec, ele);
					sint cl = vtool.CLNV(&tts_vec.d_vec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CEFV(&bot_db_vec.d_vec, ele);
					sint cl = vtool.CLNV(&bot_db_vec.d_vec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CEFV(&fileo_vec.d_vec, ele);
					sint cl = vtool.CLNV(&fileo_vec.d_vec);

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
					ret = vtool.CEFV(&bot_c_vec.m_vec, ele);
					sint cl = vtool.CLNV(&bot_c_vec.m_vec);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CEFV(&bot_log_vec.m_vec, ele);
					sint cl = vtool.CLNV(&bot_log_vec.m_vec);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CEFV(&tts_vec.m_vec, ele);
					sint cl = vtool.CLNV(&tts_vec.m_vec);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CEFV(&bot_db_vec.m_vec, ele);
					sint cl = vtool.CLNV(&bot_db_vec.m_vec);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CEFV(&fileo_vec.m_vec, ele);
					sint cl = vtool.CLNV(&fileo_vec.m_vec);
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
sint machine::ClearVecEleMem(sint g_opt, sint ele, sint memb, bool is_meta)
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
					ret = vtool.CMV(&bot_c_vec.d_vec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CMV(&bot_log_vec.d_vec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CMV(&tts_vec.d_vec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CMV(&bot_db_vec.d_vec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CMV(&fileo_vec.d_vec, ele, memb);
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
					ret = vtool.CMV(&bot_c_vec.m_vec, ele, memb);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CMV(&bot_log_vec.m_vec, ele, memb);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CMV(&tts_vec.m_vec, ele, memb);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CMV(&bot_db_vec.m_vec, ele, memb);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CMV(&fileo_vec.m_vec, ele, memb);
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
sint machine::VecSize(sint g_opt, bool is_meta)
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
sint machine::GetElementNames(sint g_opt, std::vector<std::string>* nvec, bool is_meta)
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
sint machine::GetElementIDs(sint g_opt, std::vector<sint> *nvec, bool is_meta)
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

sint machine::GetDateTimeMS(_char str_[], bool form)
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
		sint xc = bot_sprintf(str_, 128, "%.2u / %.2u / %.4u %.2u : %.2u : %.2u : %.3u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond, tim.wMilliseconds);
	}
	else
	{
		sint xc = bot_sprintf(str_, 128, "%.2u %.2u %.4u %.2u %.2u %.2u %.3u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond, tim.wMilliseconds);
	}
#else
	std::time_t tstamp;
	struct tm t;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	t = *gmtime(&tstamp);
	xc = bot_sprintf(str_, 128, "%.2u / %.2u / %.4u %.2u : %.2u : %.2u : %.9u", (uint)t.tm_mon, (uint)t.tm_mday, (uint)t.tm_year, (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec, (uint)ti.tv_nsec);
#endif	
	return 0;
}
sint machine::GetDateTime(_char str_[], bool form)
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
		sint xc = bot_sprintf(str_, 128, "%.2u / %.2u / %.4u %.2u : %.2u : %.2u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond);
	}
	else
	{
		sint xc = bot_sprintf(str_, 128, "%.2u %.2u %.4u %.2u %.2u %.2u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond);
	}
#else
	std::time_t tstamp;
	struct tm t;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	t = *gmtime(&tstamp);
	xc = bot_sprintf(str_, 128, "%.2u / %.2u / %.4u %.2u : %.2u : %.2u", (uint)t.tm_mon, (uint)t.tm_mday, (uint)t.tm_year, (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
#endif
	return 0;
}
sint machine::GetTime(_char str_[], bool forms)
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
		sint xc = bot_sprintf(str_, 64, "%.2u %.2u %.2u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond);
	}
#else
	std::time_t tstamp;
	struct tm t;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	t = *gmtime(&tstamp);

	if (forms)
	{
		xc = bot_sprintf(str_, 64, "%.2u : %.2u : %.2u", (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
	}
	else
	{
		xc = bot_sprintf(str_, 64, "%.2u %.2u %.2u", (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
	}
#endif
	return 0;
}
sint machine::GetTimeMS(_char str_[], bool forms)
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
		sint xc = bot_sprintf(str_, 64, "%.2u %.2u %.2u %.3u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond, (uint)tim.wMilliseconds);
	}
#else
	std::time_t tstamp;
	struct tm t;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	t = *gmtime(&tstamp);

	if (forms)
	{
		xc = bot_sprintf(str_, 64, "%.2u : %.2u : %.2u : %.3u", (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec, (uint)ti.tv_nsec);
	}
	else
	{
		xc = bot_sprintf(str_, 64, "%.2u %.2u %.2u %.3u", (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec, (uint)ti.tv_nsec);
	}
#endif
	return 0;
}
sint machine::GetDate(carr_32* str_, bool form)
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
sllint machine::GetCentSec()
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

sint machine::UsingLog(_char nm[])
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
sint machine::LogName(sint opt, carr_256* nm, carr_32* dat, bool tomine)
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
sint machine::LogPut(c_char* msg_, sint option)
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
			uc = vtool.AVTV(&u_logs, &Current, true, true);

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
			uc = vtool.AVTV(&u_logs, &Current, true, true);

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
		//xc = vtool.CLNV(&u_logs);
	}
	return 0;
}

// Commands
sint machine::Command(std::vector<std::string> *vec_)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::Command(std::vector<std::string> *vec_(%i))", (sint)vec_);
		op = Output(outp.carr, 2);
	}
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
				rc = GetLogin(vec_->at(1).c_str(), vec_->at(2).c_str());

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
		std::vector<BOTCOMMAND> vec;
		xc = GetCommands(&vec);

		for (uint x = 0; x < vec.size(); x++)
		{
			carr_128 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "%s %i", vec[x].cmd.c_str(), vec[x].cmd_id);
			oc = Output(ncar.carr, 0);
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
			return -1;
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
	case 8:
	{
		if (vec_->size() > 5)
		{
			BOT_FILE_M scp(vec_->at(3).c_str(), vec_->at(4).c_str(), vec_->at(5).c_str(), BOT_FILE_APPEND, BOT_F_CON);
			sint ox = -1;
			sint rc = BOTOpenFile(&scp, &ox);

			if (xc < 0)
			{
				return -1;
			}

			bot_script ns;
			BOT_STMT qt(false, 0, "scripts", "SCRIPTS", 1, &ns);
			rc = qt.AddCol("NAME", LEncStrI(vec_->at(3).c_str(), -1).c_str());
			rc = qt.AddCol("TYPE", LEncStrI(vec_->at(4).c_str(), -1).c_str());
			rc = qt.AddCol("DEST", LEncStrI(vec_->at(5).c_str(), -1).c_str());
			rc = Query(&qt, BOT_RTV_SCRPT);

			if (rc > -1)
			{
				return -1;
			}

			std::vector<BOT_STMT> tvec;
			BOT_STMT t(false, 2, "scripts", "SCRIPTS", 1);

			if (vec_->at(1).length() < 10)
			{
				uint v = (uint)atoi(vec_->at(1).c_str());
				const uint y = (sizeof(v) * 2) + 4;
				_char nuchar[y]{ 0 };
				sint rc = bot_sprintf(nuchar, y, "X'%02X'", vec_->at(1).c_str());
				rc = t.AddCol("MODE", nuchar);
			}

			if (vec_->at(2).length() < 128)
			{
				sint rc = t.AddCol("ENCODING", "X'");

				for (uint z = 0; z < vec_->at(2).length(); z++)
				{
					const uint y = (sizeof(vec_->at(2)[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(2)[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}

			if (vec_->at(3).length() < 512)
			{
				sint rc = t.AddCol("NAME", "X'");

				for (uint z = 0; z < vec_->at(3).length(); z++)
				{
					const uint y = (sizeof(vec_->at(3)[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(3)[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}

			if (vec_->at(4).length() < 256)
			{
				sint rc = t.AddCol("TYPE", "X'");

				for (uint z = 0; z < vec_->at(4).length(); z++)
				{
					const uint y = (sizeof(vec_->at(4)[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(4)[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}

			if (vec_->at(5).length() < 512)
			{
				sint rc = t.AddCol("DEST", "X'");

				for (uint z = 0; z < vec_->at(5).length(); z++)
				{
					const uint y = (sizeof(vec_->at(5)[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(5)[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}
			t.cspec = 2;
			tvec.push_back(t);
			xc = Commit(&tvec);
		}
		break;
	}
	case 9:
	{
		if (vec_->size() > 1)
		{
			if (bot_sisn(vec_->at(1).c_str()))
			{
				bot_script rval;
				BOT_STMT t(false, 0, "scripts", "SCRIPTS", 1, &rval);
				sint rc = t.AddCol("ID", LEncStrI(vec_->at(1).c_str(), -1).c_str());
				rc = Query(&t, BOT_RTV_SCRPT);

				if (rc > -1)
				{
					system(rval.script.c_str());
				}
			}
			else
			{

				bot_script rval;
				BOT_STMT t(false, 0, "scripts", "SCRIPTS", 1);
				sint rc = t.AddCol("DEST", LEncStrI(vec_->at(1).c_str(), -1).c_str());
				t.rblk = (void*)&rval;
				rc = Query(&t, BOT_RTV_SCRPT);

				if (rc > -1)
				{
					system(rval.script.c_str());
				}
			}
		}
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
sint machine::BOTPath(std::string* str_, c_char* spath_)
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
sint machine::BOTOpenDir(c_char* dest_, DIR** dir_)
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
sint machine::BOTCloseDir(DIR** dir_)
{
	if (!*dir_)
	{
		return -1;
	}

	closedir(*dir_);
	return 0;
}
sint machine::BOTReadDir(std::vector<BOT_FILE_M>* flds_, c_char* dest_)
{
	if (!flds_ || !dest_)
	{
		return -1;
	}
#ifdef _WIN32
	_char dmk = '\\';
#else
	_char dmk = '/';
#endif
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

#ifdef _WIN32
				sint xc = BOTFileStats(&xfile, BOT_DIRSCAN_LVL, true, true);
#else
				sint xc = BOTFileStats(&xfile, BOT_DIRSCAN_LVL, true);
#endif

				if (!xc)
				{
					if (S_ISDIR(xfile.fst.filestats.st_mode))
					{
						xc = vtool.AVTV(flds_, &xfile, true, true);
					}
				}
			}
		}
		sint xc = BOTCloseDir(&dir_);
		return xc;
	}
	return -1;
}
sint machine::BOTFindHomeDir()
{
	if (debug_lvl >= 600 && debug_m)
	{
		sint oc = Output("::BOTFindHomeDir()", 2);
	}
#ifdef _WIN32
	_char dmk = '\\';
#else
	_char dmk = '/';
#endif
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
							fdir.push_back(dmk);
						}

						fdir.append(ndrcs[y].name.c_str());
						fdir.push_back(dmk);
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
sint machine::BOTInitFDir(bool findself)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_64 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTInitFDir(bool findself(%u))", (uint)findself);
		oc = Output(ncar.carr, 2);
	}
#ifdef _WIN32
	_char dmk = '\\';
#else
	_char dmk = '/';
#endif
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
						fldstr.push_back(dmk);

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
								fdir.push_back(dmk);
							}

							fdir.append(bot_dmap.drvs[x].flds[ct].fld.c_str());
							fdir.push_back(dmk);

							if ((ndir = opendir(fdir.c_str())) != NULL)
							{
								while ((dp = readdir(ndir)) != NULL)
								{
									std::string fldstr;
									fldstr.append(fdir.c_str());
									fldstr.append(dp->d_name);
									fldstr.push_back(dmk);

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

sint machine::OutputFileStats(BOT_FILE* file_, sint opt)
{
	if (!file_)
	{
		return -1;
	}
#ifdef _WIN32
	_char dmk = '\\';
#else
	_char dmk = '/';
#endif
	struct tm atim;
	struct tm mtim;
	struct tm ctim;
	_char atdata[64] = { 0 };
	_char mtdata[64] = { 0 };
	_char ctdata[64] = { 0 };
	std::string fpstr;

	if (strlen(file_->path.c_str()) > 512)
	{
		sint f = file_->path.find(dmk, (file_->path.length() - 512));

		if (f > -1)
		{
#ifdef _WIN32
			fpstr.append("..\\");
#else
			fpstr.append("../");
#endif
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
sint machine::BOTFileStr(std::string* str_, BOT_FILE_M* file_)
{
	if (!str_ || !file_)
	{
		return -1;
	}
#ifdef _WIN32
	_char dmk = '\\';
#else
	_char dmk = '/';
#endif
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
sint machine::BOTConnMethod(BOT_FILE_M* val_)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::GetOFConn(BOT_FILE_M* val_, sint* was_open)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::GetFConn(BOT_FILE_M* val_, sint* was_open)
{
	if (debug_lvl >= 600 && debug_m)
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
						ret = vtool.AVTV(&f_con, &FCON[siz], true, true);

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
sint machine::CloseFConn(BOT_FILE_M* xfile_, bool clear_conn)
{
	if (debug_lvl >= 600 && debug_m)
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
				ret = vtool.CLNV(&f_con);
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
sint machine::BOTScanFileSyms(BOT_FILE_M *file_)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::DetSep(BOT_FILE_M* file_)
{
	if (debug_lvl >= 600 && debug_m)
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
					sint ret = vtool.VIV(&file_->fst.mean_loc, xloc);

					while (ret > -1)
					{
						if (ret != (sint)res_e[x])
						{
							if (file_->fst.cts[ret] <= file_->fst.cts[res_e[x]] + 1 && file_->fst.cts[ret] >= file_->fst.cts[res_e[x]] - 1)
							{
								cons.push_back(file_->fst.compv[res_e[x]]);
								xloc++;
								ret = vtool.VIV(&file_->fst.mean_loc, xloc);
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
sint machine::BOTRendFileSyms(BOT_FILE_M *file_)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::BOTKnownFormat(BOT_FILE_M* file_)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::BOTFileStats(BOT_FILE_M *file_, sint scan_lvl, bool doscan, bool addd)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_96 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileStats(BOT_FILE_M *file_(%i), sint scan_lvl(%i), bool doscan(%u), bool addd(%u))", (sint)file_, scan_lvl, (uint)doscan, (uint)addd);
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

	bool adddet = false;

	if (file_->fst.exists < 0 && addd)
	{
		adddet = true;
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

		if (scan_lvl && doscan)
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

					if (x + (ullint)BOT_STRLEN_MAX >(ullint)nstat.st_size)
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
				if (scan_lvl > 1)
				{
					xret = GetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE);
					xret = DetSep(file_);
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

						if (x + (ullint)BOT_STRLEN_MAX >(ullint)nstat.st_size)
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
					file_->fst.RenewLocs(nstat.st_size - 1, 0, 0);
					ret = BOTScanFileSyms(file_);

					if (ret > -1 && scan_lvl > 1)
					{
						file_->fst.AvgSyms();
						ret = DetSep(file_);
						ret = BOTRendFileSyms(file_);

						if (ret < 0)
						{
							ret = -1;
						}
					}
				}
			}
		}
		else
		{
			ret = 0;
		}

		if (adddet)
		{
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
sint machine::BOTCreateFile(BOT_FILE_M* file_, sint* was_open)
{
	if (debug_lvl >= 600 && debug_m)
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
#ifdef _WIN32
		_char dmk = '\\';
#else
		_char dmk = '/';
#endif
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
sint machine::BOTRemoveFile(BOT_FILE_M *xfile_)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::BOTOpenFile(sint flid, sint *was_open, bool cine, bool r_to_st)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::BOTOpenFile(BOT_FILE_M* mfile_, sint *was_open, bool cine, bool r_to_st)
{
	if (debug_lvl >= 600 && debug_m)
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

	gc = BOTFileStats(mfile_, (sint)BOT_FSCAN_LVL, true, true);

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

		switch (mfile_->cm)
		{
		case BOT_DB_CON:
		{
			BOT_DB_M ndb(mfile_->name.c_str(),-1,mfile_->omode, mfile_->fst.exists);
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
#ifdef _WIN32
			cur_path.append("\\");
#else
			cur_path.append("/");
#endif
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
sint machine::BOTFileOUT(BOT_FILE_M* file_, ...)
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
	else if (file_->cm == BOT_DB_CON)
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
sint machine::BOTFileIN(sint fcon, sint from, sint to, ...)
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
sint machine::BOTCloseFile(sint flid, bool clear_conn, bool del, bool encr)
{
	if (debug_lvl >= 600 && debug_m)
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
sint machine::BOTCloseFile(BOT_FILE_M* xfile_, bool clear_conn, bool del, bool encr)
{
	if (debug_lvl >= 600 && debug_m)
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

	sint p = vtool.VIV(&h_mtxs, MTX_FO);

	if (p > -1)
	{
		sint xp = p;
		p = vtool.VIV(&h_mtxs[xp].h_mems, xfile_->lid);

		if (p > -1)
		{
			return UnlockElement(MTX_FO, xfile_->lid, false);
		}
	}
	return -1;
}
sint machine::BotOpenError(sint err_id, std::string* err_str)
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
void machine::Nanosleep(slint dur)
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
slint machine::nsRest(slint i, bool keep_mtx)
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
		sint y = vtool.CLNV(&relocks);
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
slint machine::Rest(slint i, bool keep_mtx)
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
		sint y = vtool.CLNV(&relocks);
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

// Console I/O Functions
sint machine::Output(c_char* output_, ...)
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

	for (uint x = 0; x < (uint)BOT_OP_OPTS; x++)
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
sint machine::BotOut(sint num, ...)
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
sint machine::BotOut(c_char* str_)
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
sint machine::Output(c_char* output_, sint option)
{
	carr_64 tdata;
	sint xc = GetTimeMS(tdata.carr);
	carr_256 instr;
	xc = bot_sprintf(instr.carr, instr.siz, " [%i][machine] ", lid);
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
sint machine::Input()
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

sint machine::InterpretInput(std::string *input_)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::InterpretInput(std::string *input_(%i))", (sint)input_);
		op = Output(outp.carr, 2);
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
			if (!strcmp(Uppercase(input_->substr(0, 7).c_str()).c_str(), "/#LOGIN"))
			{
				input_->clear();
			}
		}
	}
	return ret;
}

sint machine::BOTConsole()
{
	if (debug_lvl >= 100 && debug_m)
	{
		sint op = Output("::BOTConsole()", 2);
	}
	sint xc = -1;
	sint x = -1;
	std::string np;
	carr_64 tdata;
	std::getline(std::cin, np);
	x = GetTimeMS(tdata.carr);
	
	if (np.length() < BOT_STRLEN_MAX)
	{
		xc = InterpretInput(&np);
		carr_256 instr;
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][%s] ", lid, Client.name.c_str());
		std::string str;
		str.append(tdata.carr);
		str.append(instr.carr);
		str.append(np.c_str());
		xc = LogPut(str.c_str(), 0);
		xc = LogPut(str.c_str(), 2);
	}
	return xc;
}

// Str Manip

std::string machine::LEncStrI(c_char* str_, sint opt)
{
	if (debug_lvl >= 1100 && debug_m)
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

	for (sint x = nstr.find("\"", 0); x > -1; x = nstr.find("\"", x + 1))
	{
		nstr.at(x) = '\'';
	}
	s.append("\"");
	s.append(nstr.c_str());
	nstr.clear();
	s.append("\"");

	if (debug_lvl >= 1100 && debug_m)
	{
		nstr.append("enclosed string: ");
		nstr.append(s.c_str());
		sint oc = Output(nstr.c_str(), 2);
	}
	return s;
}
sint machine::OrdLocs(std::vector<size_t>* litlocs_, std::vector<size_t>* locs_, c_char* str_)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::OrdLocs(vector<size_t>* litlocs_(%i), vector<size_t>* locs_(%i), c_char* str_(%u))", (sint)litlocs_, (sint)locs_, (sint)str_);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 1100 && str_)
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
		sint xc = vtool.VIV(&nrts_ord, &str_[siz]);

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
		if (debug_lvl >= 1100 && debug_m)
		{
			carr_1024 nump;
			sint oc = stool.VToStr(locs_, nump.carr, nump.siz);
			carr_2048 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "OrdLocs: %s", nump.carr);
			oc = Output(outp.carr, 2);
		}
		return 0;
	}
	if (debug_lvl >= 1100 && debug_m)
	{
		sint oc = Output("no ordinals found.", 2);
	}
	return -1;
}
sint machine::OrdEnc(size_t at_loc, std::vector<size_t>* litlocs_, std::vector<size_t>* locs_, c_char* str_)
{
	if (debug_lvl >= 1100 && debug_m)
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

	for (size_t siz = 1; siz < locs_->size(); siz += 2)
	{
		if (at_loc > locs_->at(siz - 1) && at_loc < locs_->at(siz))
		{
			if (debug_lvl >= 1100 && debug_m)
			{
				carr_128 outp;
				sint op = bot_sprintf(outp.carr, outp.siz, " \"%c\" enclosed between: %u \"%c\" and %u \"%c\"", str_[at_loc], locs_->at(siz - 1), str_[locs_->at(siz - 1)], locs_->at(siz), str_[locs_->at(siz - 1)]);
				op = Output(outp.carr, 2);
			}
			ret = 0;
			siz = locs_->size();
		}
	}

	if (debug_lvl >= 1100 && debug_m)
	{
		carr_32 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "OrdEnc: %i", ret);
		op = Output(outp.carr, 2);
	}
	return ret;
}
sint machine::LitLocs(std::vector<size_t>* locs_, c_char* str_)
{
	if (debug_lvl >= 1100 && debug_m)
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
		if (debug_lvl >= 1100 && debug_m)
		{
			carr_1024 nump;
			sint oc = stool.VToStr(locs_, nump.carr, nump.siz);
			carr_2048 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "LitLocs: %s", nump.carr);
			oc = Output(outp.carr, 2);
		}
		return 0;
	}
	if (debug_lvl >= 1100 && debug_m)
	{
		sint oc = Output("no literals.", 2);
	}
	return -1;
}
sint machine::LitEnc(size_t at_loc, std::vector<size_t>* locs_, c_char* str_)
{
	if (debug_lvl >= 1100 && debug_m)
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

	for (size_t siz = 1; siz < locs_->size(); siz += 2)
	{
		if (at_loc > locs_->at(siz - 1) && at_loc < locs_->at(siz))
		{
			if (debug_lvl >= 1100 && debug_m)
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
bool machine::XEnclosedInY(std::vector<size_t>* litlocs_, std::string* statements_, sint sc_loc, sint x_loc, std::string* fy_char)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::XenclosedInY(vector<size_t>* litlocs_(%i), string* statements(%i), sint sc_loc(%i), sint x_loc(%i), string* fy_char(%i))", (sint)litlocs_, (sint)statements_, sc_loc, x_loc, (sint)fy_char);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 1100 && statements_)
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

			if (debug_lvl >= 1100 && debug_m)
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

						if (debug_lvl >= 1100 && debug_m)
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

								if (debug_lvl >= 1100 && debug_m)
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

								if (debug_lvl >= 1100 && debug_m)
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
							if (debug_lvl >= 1100 && debug_m)
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
					if (debug_lvl >= 1100 && debug_m)
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
		if (debug_lvl >= 1100 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "a \"%s\" before this \"%c\" was open, opens:%i", fy_char->c_str(), statements_->at(x_loc), opens);
			op = Output(outp.carr, 2);
		}
		y = true;
	}
	else
	{
		if (debug_lvl >= 1100 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "\"%c\" not enclosed by \"%s\" (2)", statements_->at(x_loc), fy_char->c_str());
			op = Output(outp.carr, 2);
		}
	}
	return y;
}
bool machine::XEnclosedInY(std::vector<size_t>* litlocs_, c_char* statements_, sint sc_loc, sint x_loc, _char fy_char)
{
	sint opens = 0;

	if (debug_lvl >= 1100 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::XenclosedInY(vector<size_t>* litlocs_(%i), string* statements(%i), sint sc_loc(%i), sint x_loc(%i), string* fy_char \"%c\")", (sint)litlocs_, (sint)statements_, sc_loc, x_loc, fy_char);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 1100 && statements_)
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

			if (debug_lvl >= 1100 && debug_m)
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

						if (debug_lvl >= 1100 && debug_m)
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

								if (debug_lvl >= 1100 && debug_m)
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

								if (debug_lvl >= 1100 && debug_m)
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
							if (debug_lvl >= 1100 && debug_m)
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
					if (debug_lvl >= 1100 && debug_m)
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
		if (debug_lvl >= 1100 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "a \"%c\" before this \"%c\" was open", fy_char, statements_[x_loc]);
			op = Output(outp.carr, 2);
		}

		y = true;
	}
	else
	{
		if (debug_lvl >= 1100 && debug_m)
		{
			carr_64 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "\"%c\" not enclosed by \"%c\" (4)", statements_[x_loc], fy_char);
			op = Output(outp.carr, 2);
		}
	}

	return y;
}

// SQL statement manip

sint machine::SeparateSQL(std::string* statements_, std::vector<std::string>* vec_)
{
	if (debug_lvl >= 750 && debug_m)
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

	if (debug_lvl >= 750 && debug_m)
	{
		for (uint ct = 0; ct < (sint)vec_->size(); ct++)
		{
			sint oc = Output(vec_->at(ct).c_str(), 2);
		}
		sint oc = Output("Separate SQL done.", 2);
	}
	return -1;
}
sint machine::AnalyzeStmt(BOT_STMT *t_)
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
						sint xc = vtool.AVTV(&t_->fcols, snip.substr(findx, 1).c_str(), true, true);
					}
					else
					{
						for (findx = stool.FindInStr(',', snip.c_str(), x, altx); findx > -1 && findx < altx; findx = stool.FindInStr(',', snip.c_str(), x, altx))
						{
							while (!memcmp((void*)&snip[x], (void*)&spc, sizeof(spc)) && !memcmp((void*)&snip[x], (void*)&term, sizeof(term)) && x < (sint)snip.length())
							{
								x++;
							}

							sint xc = vtool.AVTV(&t_->fcols, CleanPunctuation(snip.substr(x, findx - x).c_str()).c_str(), true, true);
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
							ix = vtool.VIV(&ndb.tables, snip.substr(1, snip.length() - 2).c_str());

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
						ix = vtool.VIV(&ndb.tables, snip.substr(1, snip.length() - 2).c_str());

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
														vtool.AVTV(&t_->conds, snip.substr(nloc, x - nloc).c_str(), false, false);
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
														sint addv = vtool.AVTV(&t_->conds, snip.substr(nloc, x - nloc).c_str(), true, true);
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
											sint addv = vtool.AVTV(&t_->conds, ncar.c_str(), true, true);

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
									ix = vtool.VIV(&ndb.tables, snip.substr(1, snip.length() - 2).c_str());

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
								sint xc = vtool.AVTV(&t_->fcols, CleanPunctuation(snip.substr(x, findx - x).c_str()).c_str(), true, true);
								x = findx + 1;
							}
						}
						else
						{
							if (!t_->cspec)
							{
								if (strlen(snip.c_str()) < 1024)
								{
									sint xp = vtool.AVTV(&t_->conds, snip.c_str(), true, true);
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
sint machine::BQS(BOT_STMT *t_)
{
	if (debug_lvl >= 500 && debug_m)
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
			if (debug_lvl >= 500 && debug_m)
			{
				std::string outp;
				outp.append("Query Statement:");
				outp.append(statement.c_str());
				sint oc = Output(outp.c_str(), 2);
			}
			return 0;
		}
	}
	if (debug_lvl >= 1 && debug_m)
	{
		std::string outp;
		outp.append("Failed to build query statement:");
		outp.append(statement.c_str());
		sint oc = Output(outp.c_str(), 2);
	}
	return -1;
}
sint machine::BTS(BOT_STMT *t_)
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
		sint xc = vtool.AVTV(&trans.tables, t_->vals[0].c_str());
		for (xc = 1; xc < (sint)t_->vals.size(); xc++)
		{
		sint nc = vtool.AVTV(&trans.cols, t_->vals[xc].c_str());
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
		sint nc = vtool.AVTV(&trans.conds, t_->conds[xc].c_str());
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
sint machine::BuildStatements(std::vector<BOT_STMT>* stmts_, BOT_COMMIT *com_, std::vector<BOT_STMT>* pend_)
{
	if (debug_lvl >= 550 && debug_m)
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
				sint dx = vtool.VIV(&com_->dbs, pend_->at(i).dbname.c_str());

				if (dx < 0)
				{
					BOT_DB_M ndb(pend_->at(i).dbname.c_str());
					dx = vtool.AVTV(&com_->dbs, &ndb, false, false);

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

						sint nx = vtool.AVTV(&cont_names[cont_names.size() - 1], &pend_->at(i).cont, true, false);

						if (!dx || dx > 2)
						{
							dx = vtool.AVTV(&com_->t, &pend_->at(i), true, true);
						}
						else
						{
							dx = vtool.AVTV(&ncrts, &pend_->at(i), true, true);
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

					sint nc = vtool.AVTV(&cont_names[dx], &pend_->at(i).cont, true, false);
					if (!xc || xc > 2)
					{
						xc = vtool.AVTV(&com_->t, &pend_->at(i), true, true);
					}
					else
					{
						xc = vtool.AVTV(&ncrts, &pend_->at(i), true, true);
					}
				}
				pend_->at(i).Clear();
			}
		}
		sint xc = vtool.CLNV(pend_);
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
			sint dx = vtool.VIV(&com_->dbs, stmts_->at(i).dbname.c_str());

			if (dx < 0)
			{
				BOT_DB_M ndb(stmts_->at(i).dbname.c_str());
				dx = vtool.AVTV(&com_->dbs, &ndb, false, false);

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

					sint nx = vtool.AVTV(&cont_names[cont_names.size() - 1], &stmts_->at(i).cont, true, false);

					if (!dx || dx > 2)
					{
						dx = vtool.AVTV(&com_->t, &stmts_->at(i), true, true);
					}
					else
					{
						dx = vtool.AVTV(&ncrts, &stmts_->at(i), true, true);
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

				sint nc = vtool.AVTV(&cont_names[dx], &stmts_->at(i).cont, true, false);

				if (!xc || xc > 2)
				{
					xc = vtool.AVTV(&com_->t, &stmts_->at(i), true, true);
				}
				else
				{
					xc = vtool.AVTV(&ncrts, &stmts_->at(i), true, true);
				}
			}
			stmts_->at(i).Clear();
		}
	}

	sint hx = vtool.CLNV(stmts_);

	for (sint i = 0; i < (sint)ncrts.size(); i++)
	{
		sint xc = vtool.AVTV(&com_->t, &ncrts[i], true, true);
	}

	for (sint i = (sint)com_->dbs.size() - 1; i > -1; i--)
	{
		sint xc = GetInVec((void*)&com_->dbs[i], MTX_DBL);

		if (debug_lvl >= 550 && debug_m)
		{
			carr_256 ncar;
			xc = bot_sprintf(ncar.carr, ncar.siz, "building necessary statements for %s", com_->dbs[i].name.c_str());
			xc = Output(ncar.carr, 2);
		}

		BOT_STMT trans((bool)db_maint[i], 1, com_->dbs[i].name.c_str(), "LAST_ACCESS", 1);
		trans.cspec = 0;
		trans.act = 0;
		xc = vtool.AVTV(&trans.conds, "ID > 0", false, false);
		xc = vtool.AVTV(&com_->t, &trans, true, false);


		for (uint c = 0; c < cont_names[i].size(); c++)
		{
			trans.Clear();
			trans.Renew((bool)db_maint[i], 8, com_->dbs[i].name.c_str(), cont_names[i][c].c_str(), 1);
			xc = vtool.AVTV(&com_->an, &trans, true, false);
		}
	}
	return 0;
}
sint machine::OutpuTINFO(BOT_STMT *t_)
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

std::string machine::GetError()
{
	std::string str;
	str.append(reinterpret_cast<c_char*>(sqlite3_errmsg(d_con_->db_)));
	return str;
}
sint machine::FindColumn(c_char *str_, sqlite3_stmt* ppstmt)
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
sint machine::GetODBConn(BOT_DB_M *db_)
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

	sint rc = vtool.VIV(&d_con_->att, db_->name.c_str());

	if (rc > -1)
	{
		return rc;
	}
	db_->fcon = rc;
	return -1;
}
sint machine::GetDBConn(BOT_DB_M* val_)
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
sint machine::CloseDBConn(BOT_DB_M* db_)
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
sint machine::OpenOpt(sint opt) { if (opt < 0) { return -1; } if (!opt) { return 0; } if (opt < 3) { return 2; } if (opt < 9) { return 3; } return -1; }
sint machine::OpenDB(sint db_lid, sint x, sint* was_open, sint* fwas_locked, bool r_to_st)
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
sint machine::OpenDB(BOT_DB_M *db_, sint x, sint* was_open, sint* fwas_locked, bool r_to_st, bool is_verify)
{
	if (debug_lvl >= 550 && debug_m)
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
			BOT_DB ndb(db_->name.c_str(), db_->type, db_->omode, db_->exists);
			sint xc = PushToDBList(&ndb);

			if (xc < 0)
			{
				return -1;
			}

			xc = GetVecEle((void*)db_, MTX_DBL, ndb.lid);

			if (xc < 0)
			{
				if (debug_lvl >= 1 && debug_m)
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
		if (debug_lvl >= 1 && debug_m)
		{
			carr_256 outp;
			sint xc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\" does not exist, OpenOpt(%i)", db_->name.c_str(), x);
			xc = Output(outp.carr, 2);
		}
		return -1;
	}

	if (db_->exists < 1 && x != 3 && !is_verify)
	{
		if (debug_lvl >= 550 && debug_m)
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
				if (debug_lvl >= 1 && debug_m)
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
					if (debug_lvl >= 1 && debug_m)
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
	std::string pth;
	sint xc = BOTPath(&pth, BOT_DB_NM);

#ifdef _WIN32
	pth.push_back('\\');
#else
	pth.push_back('/');
#endif

	BOT_FILE_M nfilem(db_->name.c_str(), ".db", pth.c_str(), x, BOT_DB_CON, -1, lid, -1, 0);
	xc = GetInVec(&nfilem, MTX_FO, false, true);

	if (xc < 0)
	{
		BOT_FILE nfile(db_->name.c_str(), ".db", pth.c_str(), x, BOT_DB_CON, -1, lid, -1, 0);
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
		*fwas_locked = vtool.VIV(&h_mtxs, MTX_FO);

		if (*fwas_locked > -1)
		{
			xc = *fwas_locked;
			*fwas_locked = vtool.VIV(&h_mtxs[xc].h_mems, nfilem.lid);

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
		if (debug_lvl >= 1 && debug_m)
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
				dbt.append(pth.c_str());
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

				if (debug_lvl >= 550 && debug_m)
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
					if (debug_lvl >= 550 && debug_m)
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
							if (debug_lvl >= 550 && debug_m)
							{
								xc = Output("SQLITE_OK", 2);
							}
							dbc = vtool.AVTV(&d_con_->att, db_->name.c_str(), true, true);
							olim++;
							nulim = olim;
							done = true;
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 550 && debug_m)
							{
								xc = Output("SQLITE_DONE", 2);
							}
							dbc = vtool.AVTV(&d_con_->att, db_->name.c_str(), true, true);
							olim++;
							nulim = olim;
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 550 && debug_m)
							{
								xc = Output("SQLITE_ROW", 2);
							}
							break;
						}
						case SQLITE_BUSY:
						{
							if (debug_lvl >= 550 && debug_m)
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

	if (debug_lvl >= 550 && debug_m)
	{
		carr_256 outp;
		xc = bot_sprintf(outp.carr, outp.siz, "DB \"%s\"(%i) opened, olim is:%u", db_->name.c_str(), db_->lid, nulim);
		xc = Output(outp.carr, 2);
	}
	return db_->lid;
}
sint machine::CloseDB(sint db_lid, sint* fwas_locked, bool clear_conn)
{
	if (debug_lvl >= 550 && debug_m)
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
sint machine::CloseDB(BOT_DB_M* db_, sint* fwas_locked, bool clear_conn)
{
	if (debug_lvl >= 550 && debug_m)
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

		if (debug_lvl >= 550 && debug_m)
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
			if (debug_lvl >= 550 && debug_m)
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
					if (debug_lvl >= 550 && debug_m)
					{
						xc = Output("SQLITE_OK", 2);
					}

					if (clear_conn)
					{
						xc = vtool.CEFV(&d_con_->att, dbc);
						xc = vtool.CLNV(&d_con_->att);
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
					if (debug_lvl >= 550 && debug_m)
					{
						xc = Output("SQLITE_DONE", 2);
					}

					if (clear_conn)
					{
						xc = vtool.CEFV(&d_con_->att, dbc);
						xc = vtool.CLNV(&d_con_->att);
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
					if (debug_lvl >= 550 && debug_m)
					{
						xc = Output("SQLITE_ROW", 2);
					}
					break;
				}
				case SQLITE_BUSY:
				{
					if (debug_lvl >= 550 && debug_m)
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

	sint gc = vtool.VIV(&h_mtxs, MTX_DBL);

	if (gc > -1)
	{
		sint xgc = gc;
		gc = vtool.VIV(&h_mtxs[xgc].h_mems, db_->lid);

		if (gc > -1)
		{
			gc = UnlockElement(MTX_DBL, db_->lid, false);
		}

		if (!gc)
		{
			if (debug_lvl >= 550 && debug_m)
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
		xc = UnlockElement(MTX_FO, nfile.lid, false);
	}
	return gc;
}

sint machine::OpenDBs(std::vector<BOT_DB_M> *dbs_, sint opt, std::vector <sint> *wos_, std::vector<sint> *fwas_, std::vector<sint> *lids_)
{
	if (debug_lvl >= 550 && debug_m)
	{
		if (debug_lvl >= 550 && debug_m)
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
	sint cl = vtool.CLNV(dbs_);
	// do stuff with fails and clear them as each is fixed, if all are corrected we can return 0
	return ret;
}
sint machine::CloseDBs(std::vector<BOT_DB_M> *dbs_, std::vector<sint>* fwas_)
{
	if (debug_lvl >= 550 && debug_m)
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
sint machine::Query(BOT_STMT* qval_, sint as_opt)
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
							case BOT_RTV_SCRPT:
							{
								bot_script* ns = reinterpret_cast<bot_script*>(qval_->rblk);

								if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
								{
									ns->lid = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "MODE"))
								{
									ns->mode = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "ENCODING"))
								{
									ns->encoding = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "USED"))
								{
									ns->used = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED_BY"))
								{
									ns->lub = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "NAME"))
								{
									ns->name.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "TYPE"))
								{
									ns->type.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "DEST"))
								{
									ns->dest.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED"))
								{
									ns->lused.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
								{
									ns->last_maint = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
								{
									ns->last_maint_ns = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
								{
									ns->last_mod = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
								{
									ns->last_mod_ns = sqlite3_column_int(ppstmt, ret);
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
								/*std::vector<MICSYM>* nsv = reinterpret_cast<std::vector<MICSYM>*>(qval_->rblk);

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
								else {}*/
								break;
							}
							case BOT_RTV_VMACS:
							{
								/*std::vector<MACSYM>* ns = reinterpret_cast<std::vector<MACSYM>*>(qval_->rblk);

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
								else {}*/
								break;
							}
							case BOT_RTV_VSCRPT:
							{
								/*bot_script* ns = reinterpret_cast<bot_script*>(qval_->rblk);

								if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
								{
									ns->lid = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "MODE"))
								{
									ns->mode = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "ENCODING"))
								{
									ns->encoding = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "USED"))
								{
									ns->used = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED_BY"))
								{
									ns->lub = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "NAME"))
								{
									ns->name.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "TYPE"))
								{
									ns->type.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "DEST"))
								{
									ns->dest.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED"))
								{
									ns->lused.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
								{
									ns->last_maint = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
								{
									ns->last_maint_ns = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
								{
									ns->last_mod = sqlite3_column_int(ppstmt, ret);
								}
								else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
								{
									ns->last_mod_ns = sqlite3_column_int(ppstmt, ret);
								}
								else {}*/
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
sint machine::Commit(std::vector<BOT_STMT>* stmts_)
{
	if (debug_lvl >= 500 && debug_m)
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
					sint vv = vtool.VIV(&Comm.dbs, Comm.t[nsiz].dbname.c_str());

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
									if (debug_lvl >= 500 && debug_m)
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
									if (debug_lvl >= 500 && debug_m)
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
								if (debug_lvl >= 500 && debug_m)
								{
									sint xp = Output("statement prepared", 2);
								}

								rc = sqlite3_step(ppstmt);

								switch (rc)
								{
								case SQLITE_OK:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_OK", 2);
									}
									break;
								}
								case SQLITE_DONE:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_DONE", 2);
									}
									break;
								}
								case SQLITE_ROW:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_ROW", 2);
									}
									break;
								}
								case SQLITE_BUSY:
								{
									if (debug_lvl >= 500 && debug_m)
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

								if (debug_lvl >= 500 && debug_m)
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
									if (debug_lvl >= 500 && debug_m)
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
											if (debug_lvl >= 500 && debug_m)
											{
												sint xp = Output("SQLITE_OK", 2);
											}
											sdone = true;
											break;
										}
										case SQLITE_DONE:
										{
											if (debug_lvl >= 500 && debug_m)
											{
												sint xp = Output("SQLITE_DONE", 2);
											}
											sdone = true;
											break;
										}
										case SQLITE_ROW:
										{
											if (debug_lvl >= 500 && debug_m)
											{
												sint xp = Output("SQLITE_ROW", 2);
											}
											break;
										}
										case SQLITE_BUSY:
										{
											if (debug_lvl >= 500 && debug_m)
											{
												sint xp = Output("SQLITE_BUSY", 2);
											}
											sdone = true;
											break;
										}
										default:
										{
											if (debug_lvl >= 500 && debug_m)
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

					if (debug_lvl >= 500 && debug_m)
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
						if (debug_lvl >= 500 && debug_m)
						{
							sint xp = Output("statement prepared", 2);
						}

						rc = sqlite3_step(ppstmt);

						switch (rc)
						{
						case SQLITE_OK:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								sint xp = Output("SQLITE_OK", 2);
							}
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								sint xp = Output("SQLITE_DONE", 2);
							}
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								sint xp = Output("SQLITE_ROW", 2);
							}
							break;
						}
						case SQLITE_BUSY:
						{
							if (debug_lvl >= 500 && debug_m)
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
					sint viv = vtool.VIV(&Comm.dbs, Comm.an[i].dbname.c_str());

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

							if (debug_lvl >= 500 && debug_m)
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
								if (debug_lvl >= 500 && debug_m)
								{
									sint xp = Output("statement prepared", 2);
								}

								rc = sqlite3_step(ppstmt);

								switch (rc)
								{
								case SQLITE_OK:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_OK", 2);
									}
									break;
								}
								case SQLITE_DONE:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_DONE", 2);
									}
									break;
								}
								case SQLITE_ROW:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_ROW", 2);
									}
									break;
								}
								case SQLITE_BUSY:
								{
									if (debug_lvl >= 500 && debug_m)
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
						sint rc = vtool.VIV(&bot_t_pend, &Comm.t[csiz]);

						if (rc < 0)
						{
							rc = vtool.AVTV(&bot_t_pend, &Comm.t[csiz], false, true);
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
					sint xc = vtool.AVTV(&bot_t_pend, &Comm.t[i], false, false);
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
	if (debug_lvl >= 500 && debug_m)
	{
		sint oc = Output("Commit() End", 2);
	}
	return 0;
}
// ol_ is overlapping statements which require more db connections than are available. the default limit for attached dbs is 10. the limit function can only reduce the limit below the compile option. gcc -DHAVE_STRCHRNUL=0 -DSQLITE_LIMIT_ATTACHED=50 sqlite3.c -o myfile we apparently need to root the device to compile the source with these options. realky we must enable this option so that we can query from karge groups too. HAVE_STRCHRNULL must be 0 to compile on, so far,: Galaxy S4, Galaxy Note 3 10.1 this may incur a huge performance loss on the db.

sint machine::VerifyDatabases()
{
	if (debug_lvl >= 450 && debug_m)
	{
		sint op = Output("::VerifyDatabases()", 2);
	}

	uint db_failed = 0;

	std::vector<std::string> nms
	{
		"litebot",
		"symbols",
		"math",
		"code",
		"scripts"
	};

	for (uint x = 0; x < nms.size(); x++)
	{
		std::string pth;
		sint xc = BOTPath(&pth, BOT_DB_NM);
#ifdef _WIN32
		pth.push_back('\\');
#else
		pth.push_back('/');
#endif
		BOT_FILE_M ndb(nms[x].c_str(), ".db", pth.c_str(), 3, BOT_DB_CON, -1, -1, lid);
		sint of = -1;
		xc = BOTOpenFile(&ndb, &of, true);

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
sint machine::VerifyDatabase(BOT_DB_M *dbs_)
{
	if (debug_lvl >= 500 && debug_m)
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
sint machine::VerifyTable(BOT_DB *dbs_, std::vector<BOT_STMT> *tvec_, sint x, sint odb)
{
	if (debug_lvl >= 500 && debug_m)
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

				rc = vtool.AVTV(tvec_, &trans, true, true);
				trans.ic_type = 3;
				trans.targ = 0;
				rc = vtool.AVTV(tvec_, &trans, true, true);
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
						rc = vtool.AVTV(tvec_, &trans, true, true);
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
				rc = vtool.AVTV(tvec_, &trans, true, true);
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
					if (debug_lvl >= 500 && debug_m)
					{
						rc = Output("SQLITE_OK", 2);
					}

					xxc++;
					done = true;
					break;
				}
				case SQLITE_DONE:
				{
					if (debug_lvl >= 500 && debug_m)
					{
						rc = Output("SQLITE_DONE", 2);
					}

					rc = sqlite3_column_count(ppstmt);

					if (rc == (sint)dbs_->columns[x][0].size())
					{
						if (debug_lvl >= 500 && debug_m)
						{
							rc = Output("structure count == db count", 2);
						}
					}
					else if ((sint)dbs_->columns[x][0].size() > rc)
					{
						if (debug_lvl >= 500 && debug_m)
						{
							rc = Output("structure count > db count", 2);
						}
					}
					else
					{
						if (debug_lvl >= 500 && debug_m)
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
								if (debug_lvl >= 500 && debug_m)
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

						rc = vtool.AVTV(tvec_, &t, true, true);
						t.Clear();
						ncar.append(dbs_->tables[x]);
						ncar.append("_");
						t.Renew(false, 2, dbs_->name.c_str(), ncar.c_str(), 1);

						for (sint stcount = 0; stcount < sqlite3_column_count(ppstmt); stcount++)
						{
							ncar.clear();
							ncar.append(sqlite3_column_name(ppstmt, stcount));
							rc = vtool.AVTV(&t.cols, ncar.c_str(), true, true);
						}

						std::string nval;
						nval.append(dbs_->tables[x]);
						//t.opts[11].push_back(0);
						rc = vtool.AVTV(&t.vals, nval.c_str(), true, true);
						rc = vtool.AVTV(tvec_, &t, true, true);
						t.Clear();
						t.Renew(false, 5, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
						rc = vtool.AVTV(tvec_, &t, true, true);
						t.Clear();
						ncar.clear();
						ncar.append(dbs_->tables[x]);
						ncar.append("_");
						t.Renew(false, 7, dbs_->name.c_str(), ncar.c_str(), 1);
						t.act = 2;
						rc = vtool.AVTV(&t.vals, nval.c_str(), true, true);
						rc = vtool.AVTV(tvec_, &t, false, false);
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

						rc = vtool.AVTV(tvec_, &t, true, true);
					}
					else
					{
						if (!m_cols.empty())
						{
							fail++;
							for (uint m = 0; m < (sint)m_cols.size(); m += 2)
							{
								if (debug_lvl >= 500 && debug_m)
								{
									carr_512 outp;
									sint op = bot_sprintf(outp.carr, outp.siz, "%s %s not found in table %s.%s", m_cols[m].c_str(), m_cols[m + 1].c_str(), dbs_->name.c_str(), dbs_->tables[x].c_str());
									op = Output(outp.carr, 1, 2, -1);
								}

								BOT_STMT t(false, 7, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
								t.act = 1;
								rc = t.AddCol(m_cols[m].c_str(), m_cols[m + 1].c_str());
								rc = vtool.AVTV(tvec_, &t, true, true);
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
							rc = vtool.AVTV(tvec_, &t, true, true);
						}
					}

					if (e && !x)
					{
						BOT_STMT t(false, 2, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
						t.cspec = 2;
						rc = vtool.AVTV(tvec_, &t, true, true);
					}
					xxc++;
					done = true;
					break;
				}
				case SQLITE_ROW:
				{
					if (debug_lvl >= 500 && debug_m)
					{
						rc = Output("SQLITE_ROW", 2);
					}

					e = false;
					rc = sqlite3_column_count(ppstmt);

					if (rc == (sint)dbs_->columns[x][0].size())
					{
						if (debug_lvl >= 500 && debug_m)
						{
							rc = Output("structure count == db count", 2);
						}
					}
					else if ((sint)dbs_->columns[x][0].size() > rc)
					{
						if (debug_lvl >= 500 && debug_m)
						{
							rc = Output("structure count > db count", 2);
						}
					}
					else
					{
						if (debug_lvl >= 500 && debug_m)
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
								if (debug_lvl >= 500 && debug_m)
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

						rc = vtool.AVTV(tvec_, &t, true, true);
						t.Clear();
						t.Renew(false, 2, dbs_->name.c_str(), ntn.c_str(), 1);

						for (sint stcount = 0; stcount < sqlite3_column_count(ppstmt); stcount++)
						{
							std::string ncol;
							ncol.append(sqlite3_column_name(ppstmt, stcount));
							rc = vtool.AVTV(&t.cols, ncol.c_str(), true, true);
						}

						//t.opts[11].push_back(0);
						std::string nval;
						nval.append(dbs_->tables[x]);
						rc = vtool.AVTV(&t.vals, nval.c_str(), true, true);

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

						rc = vtool.AVTV(tvec_, &t, true, true);
						t.Clear();
						t.Renew(false, 5, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
						rc = vtool.AVTV(tvec_, &t, true, true);
						t.Clear();
						t.Renew(false, 7, dbs_->name.c_str(), ntn.c_str(), 1);
						t.act = 2;
						rc = vtool.AVTV(&t.vals, nval.c_str(), true, true);
						rc = vtool.AVTV(tvec_, &t, true, true);
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
						rc = vtool.AVTV(tvec_, &t, true, true);
					}
					else
					{
						if (!m_cols.empty())
						{
							fail++;
							for (uint m = 0; m < m_cols.size(); m += 2)
							{
								if (debug_lvl >= 500 && debug_m)
								{
									carr_512 outp;
									sint op = bot_sprintf(outp.carr, outp.siz, "%s %s not found in table %s.%s", m_cols[m].c_str(), m_cols[m + 1].c_str(), dbs_->name.c_str(), dbs_->tables[x].c_str());
									op = Output(outp.carr, 2);
								}

								BOT_STMT t(false, 7, dbs_->name.c_str(), dbs_->tables[x].c_str(), 1);
								t.act = 1;
								rc = t.AddCol(m_cols[m].c_str(), m_cols[m + 1].c_str());
								rc = vtool.AVTV(tvec_, &t, true, true);
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
							rc = vtool.AVTV(tvec_, &t, true, true);
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
sint machine::CreateDatabase(BOT_DB_M *dbs_)
{
	if (debug_lvl >= 500 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::CreateDatabase(BOT_DB *dbs_(%i))", (sint)dbs_);
		op = Output(outp.carr, 2);
	}

	if (!dbs_)
	{
		return -1;
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
		sint oc = vtool.AVTV(&sepsql, &t, true, true);
		t.ic_type = 2;
		t.targ = 0;
		oc = vtool.AVTV(&sepsql, &t, true, true);

		if (!s)
		{
			t.Clear();
			t.Renew(false, 2, dbs.name.c_str(), dbs.tables[s].c_str(), 1);
			t.cspec = 2;
			xc = vtool.AVTV(&sepsql, &t, true, true);
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
				sint xc = vtool.AVTV(&sepsql, &t, true, true);
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

sint machine::GetSymbol(MICSYM *sym_, c_char x_cond_[], bool maint) { if (!sym_) { return -1; } std::vector<MICSYM> vec; vec.push_back(*sym_); return GetSymbols(&vec, x_cond_, maint); }
sint machine::GetSymbols(std::vector <MICSYM> *syms_, c_char x_cond_[], bool maint)
{
	if (debug_lvl >= 500 && debug_m)
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
			BOT_STMT t(maint, 0, "symbols", "SYMS", 1);

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

			rc = vtool.AVTV(&stmts, &t, true, true);

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

	BOT_DB_M dbs("symbols", 3);
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
							if (debug_lvl >= 500 && debug_m)
							{
								rc = Output("SQLITE_OK", 2);
							}
							done = true;
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								rc = Output("SQLITE_DONE", 2);
							}
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 500 && debug_m)
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
																sint xi = vtool.AVTV(&syms_->at(nsiz).encodings, (uint)nuchar[fi], true, false);

																for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																{
																	if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																	{
																		xi = vtool.AVTV(&syms_->at(xsiz).encodings, (uint)nuchar[fi], true, false);
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
																	sint xi = vtool.AVTV(&nvec, &uvec, true, false);

																	for (size_t xsiz = nsiz + 1; xsiz < syms_->size(); xsiz++)
																	{
																		if (!memcmp(&suc[0], &syms_->at(xsiz).sym, 1))
																		{
																			xi = vtool.AVTV(&nvec, &uvec, true, false);
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
							if (debug_lvl >= 500 && debug_m)
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
		if (debug_lvl >= 500 && debug_m)
		{
			sint xp = Output("GetSymbols() done", 2);
		}
		return 0;
	}
	return -1;
}
sint machine::AddSymbol(MICSYM* sym_) { if (!sym_) { return -1; } std::vector<MICSYM> vec; vec.push_back(*sym_); return AddSymbols(&vec); }
sint machine::AddSymbols(std::vector <MICSYM> *syms_)
{
	if (debug_lvl >= 500 && debug_m)
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
			rx = vtool.AVTV(&eles, x, true, false);
		}
	}

	sint rc = GetSymbols(syms_, "", false);
	std::vector<BOT_STMT> tvec;

	for (size_t x = 0; x < eles.size(); x++)
	{
		BOT_STMT t(syms_->at(eles[x]).ud_last_maintained, 1, "symbols", "SYMS", 1);

		if (syms_->at(eles[x]).id < 0)
		{
			t.it_type = 2;
			t.cspec = 2;

			if (sizeof(syms_->at(eles[x]).sym))
			{
				_char xstr[(sizeof(syms_->at(eles[x]).sym) * 2) + 8]{ 0 };
				sint xp = bot_sprintf(xstr, sizeof(xstr), "X'%02X'", syms_->at(eles[x]).sym);
				xp = vtool.AVTV(&t.cols, "SYMBOL", false, false);
				xp = vtool.AVTV(&t.vals, xstr, false, false);
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
					sint xp = t.AddCol("ENCODINGS", "X'");
					//sint xp = vtool.AVTV(&t.cols, "ENCODINGS", false, false);
					//xp = vtool.AVTV(&t.vals, "X'", false, false);
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
					sint xp = t.AddCol("CONSTITUENT_TO", "X'");
					//sint xp = vtool.AVTV(&t.cols, "CONSTITUENT_TO", false, false);
					//xp = vtool.AVTV(&t.vals, "X'", false, false);
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
					sint xp = t.AddCol("HISTORY_FOLLOWING", "X'");
					//sint xp = vtool.AVTV(&t.cols, "HISTORY_FOLLOWING", false, false);
					//xp = vtool.AVTV(&t.vals, "X'", false, false);
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
					sint xp = t.AddCol("HISTORY_PRECEEDING", "X'");
					//sint xp = vtool.AVTV(&t.cols, "HISTORY_PRECEEDING", false, false);
					//xp = vtool.AVTV(&t.vals, "X'", false, false);
					if (xp > -1)
					{
						t.vals[xp].append(str.c_str());
						t.vals[xp].push_back('\'');
					}
				}
			}

			if (!t.cont.empty())
			{
				sint xc = vtool.AVTV(&tvec, &t, false, true);
			}
		}
		else
		{
			t.cspec = 0;
			t.act = 0;

			if (syms_->at(eles[x]).ud_id)
			{
				vtool.AVTV(&t.cols, "ID", false, false);
				vtool.AVTV(&t.vals, stool.ITOA(syms_->at(eles[x]).id).c_str(), false, false);
			}

			if (syms_->at(eles[x]).ud_sym)
			{
				if (sizeof(syms_->at(eles[x]).sym))
				{
					_char xstr[(sizeof(syms_->at(eles[x]).sym) * 2) + 8]{ 0 };
					sint xp = bot_sprintf(xstr, sizeof(xstr), "X'%02X'", syms_->at(eles[x]).sym);
					xp = vtool.AVTV(&t.cols, "SYMBOL", false, false);
					xp = vtool.AVTV(&t.vals, xstr, false, false);
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
					sint xp = vtool.AVTV(&t.cols, "ENCODINGS", false, false);
					xp = vtool.AVTV(&t.vals, "X'", false, false);
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
					sint xp = vtool.AVTV(&t.cols, "CONSTITUENT_TO", false, false);
					xp = vtool.AVTV(&t.vals, "X'", false, false);
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
					sint xp = vtool.AVTV(&t.cols, "HISTORY_FOLLOWING", false, false);
					xp = vtool.AVTV(&t.vals, "X'", false, false);
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
					sint xp = vtool.AVTV(&t.cols, "HISTORY_PRECEEDING", false, false);
					xp = vtool.AVTV(&t.vals, "X'", false, false);
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
			xc = vtool.AVTV(&tvec, &t, true, true);
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
					rc = vtool.AVTV(&bot_strt.sym_pend, &tvec[x], true, true);
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
sint machine::GetCode(MACSYM* code_, c_char x_cond_[], bool maint) { if (!code_) { return -1; } std::vector<MACSYM> vec; vec.push_back(*code_); return GetCode(&vec, x_cond_, maint); }
sint machine::GetCode(std::vector<MACSYM>* codes_, c_char x_cond_[], bool maint)
{
	if (debug_lvl >= 500 && debug_m)
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
							if (debug_lvl >= 500 && debug_m)
							{
								rc = Output("SQLITE_OK", 2);
							}
							done = true;
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								rc = Output("SQLITE_DONE", 2);
							}
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 500 && debug_m)
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
																	sint xi = vtool.AVTV(&codes_->at(nsiz).usages, (uint)nuchar[fi], false, false);

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
																				xi = vtool.AVTV(&codes_->at(xsiz).usages, (uint)nuchar[fi], false, false);
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
																	sint xi = vtool.AVTV(&codes_->at(nsiz).used, (uint)nuchar[fi], false, false);

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
																				xi = vtool.AVTV(&codes_->at(xsiz).used, (uint)nuchar[fi], false, false);
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
																		sint xi = vtool.AVTV(&codes_->at(nsiz).alters, &nvec, true, false);

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
																					xi = vtool.AVTV(&codes_->at(xsiz).alters, &nvec, true, false);
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
																	sint xi = vtool.AVTV(&codes_->at(nsiz).alters, &nvec, true, false);

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
																				xi = vtool.AVTV(&codes_->at(xsiz).alters, &nvec, true, false);
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
							if (debug_lvl >= 500 && debug_m)
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

		if (debug_lvl >= 500 && debug_m)
		{
			rc = Output("GetCode() done", 2);
		}
		return 0;
	}
	return -1;
}
sint machine::AddCode(MACSYM *code_) { if (!code_) { return-1; } std::vector<MACSYM> vec; vec.push_back(*code_); return AddCode(&vec); }
sint machine::AddCode(std::vector<MACSYM > *codes_)
{
	if (debug_lvl >= 500 && debug_m)
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
			uc = vtool.VIV(&codes_->at(x).usages, codes_->at(x).used_as);

			if (uc < 0)
			{
				if (!codes_->at(x).ud_usages)
				{
					codes_->at(x).ud_usages = true;
				}
				uc = vtool.AVTV(&codes_->at(x).usages, codes_->at(x).used_as, false, false);
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
								retc = vtool.VIV(&codes_->at(x).alters, &codes_->at(xc).alters[cf]);

								if (retc < 0)
								{
									if (!codes_->at(x).ud_alters)
									{
										codes_->at(x).ud_alters = true;
										aud = true;
									}
									retc = vtool.AVTV(&codes_->at(x).alters, &codes_->at(xc).alters[cf], true, true);
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
			rc = vtool.AVTV(&eles, x, true, false);
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
						sint xc = vtool.AVTV(&t.cols, "USAGES", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);

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
						sint xc = vtool.AVTV(&t.cols, "USED", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);

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
						sint xc = vtool.AVTV(&t.cols, "HISTORY_FOLLOWING", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);

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
						sint xc = vtool.AVTV(&t.cols, "HISTORY_PRECEEDING", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);

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
						sint xc = vtool.AVTV(&t.cols, "ALTERS", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);
						if (xc > -1)
						{
							t.vals[xc].append(str.c_str());
							t.vals[xc].push_back('\'');
						}
					}
				}

				if (!t.cont.empty())
				{
					sint xc = vtool.AVTV(&tvec, &t, false, true);
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
						sint xc = vtool.AVTV(&t.cols, "USAGES", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);
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
						sint xc = vtool.AVTV(&t.cols, "USED", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);
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
							_char xi[(sizeof(codes_->at(eles[x]).history_following[a][b].ct) * 2) + 1]{};
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
						sint xc = vtool.AVTV(&t.cols, "HISTORY_FOLLOWING", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);
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
						sint xc = vtool.AVTV(&t.cols, "HISTORY_PRECEEDING", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);
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
						sint xc = vtool.AVTV(&t.cols, "ALTERS", false, false);
						xc = vtool.AVTV(&t.vals, "X'", false, false);
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
				xc = vtool.AVTV(&tvec, &t, true, true);
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
					rc = vtool.AVTV(&bot_strt.code_pend, &tvec[x], true, true);
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
sint machine::GetCommand(BOTCOMMAND *Command_, std::vector<std::string> *conds_)
{
	if (!Command_)
	{
		return -1;
	}
	std::vector<BOTCOMMAND> vec;
	vec.push_back(*Command_);
	sint xc = GetCommands(&vec);

	if (xc > -1)
	{
		Command_->cmd.append(vec[0].cmd.c_str());
		Command_->priv = vec[0].priv;
		Command_->id = vec[0].id;
		Command_->cmd_id = vec[0].cmd_id;
	}
	return xc;
}

sint machine::GetCommands(std::vector<BOTCOMMAND> *Commands_, std::vector<std::string> *conds_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetCommands(std::vector<BOTCOMMAND> *Command_(%i), std::vector<std::string>* conds_(%i))", (sint)Commands_, (sint)conds_);
		op = Output(outp.carr, 2);
	}

	if (!Commands_)
	{
		return -1;
	}

	std::vector<BOT_STMT> stmts;
	sint rc = 0;
	sint xc = -1;

	if (!Commands_->empty())
	{
		for (uint x = 0; x < Commands_->size(); x++)
		{
			BOT_STMT t(false, 0, "litebot", "COMMANDS", 1);
			t.cspec = 0;

			if (!Commands_->at(x).cmd.empty())
			{
				xc = t.AddCond(0, "COMMAND", sql_comp_keywords[5], LEncStrI(Uppercase(CleanPunctuation(Commands_->at(x).cmd.c_str()).c_str()).c_str(), -1).c_str());
			}
			if (Commands_->at(x).cmd_id > 0)
			{
				xc = t.AddCond(0, "CMD_ID", sql_comp_keywords[5], stool.ITOA(Commands_->at(x).cmd_id).c_str());
			}
			if (Commands_->at(x).id > 0)
			{
				xc = t.AddCond(0, "ID", sql_comp_keywords[5], stool.ITOA(Commands_->at(x).id).c_str());
			}
			if (xc > -1)
			{
				if (conds_)
				{
					if (!conds_->empty())
					{
						for (size_t siz = 0; siz < conds_->size(); siz++)
						{
							xc = t.AddCond(&conds_->at(siz));
						}
					}

				}
				xc = BQS(&t);

				if (xc)
				{
					t.stmt.clear();
				}

				stmts.push_back(t);
			}
		}
	}
	else
	{
		if (conds_)
		{
			if (!conds_->empty())
			{
				for (size_t siz = 0; siz < conds_->size(); siz++)
				{
					BOT_STMT t(false, 0, "litebot", "COMMANDS", 1);
					t.cspec = 0;
					xc = t.AddCond(&conds_->at(siz));
					xc = BQS(&t);

					if (xc)
					{
						t.stmt.clear();
					}
					stmts.push_back(t);
				}
			}

		}
		else
		{
			BOT_STMT t(false, 0, "litebot", "COMMANDS", 1);
			t.cspec = 0;
			xc = BQS(&t);

			if (xc)
			{
				t.stmt.clear();
			}
			stmts.push_back(t);
		}
	}

	if (!stmts.empty())
	{
		BOT_DB_M dbs("litebot", 0);
		sint fdb = -1;
		sint hdb = -1;
		sint odb = OpenDB(&dbs, 1, &hdb, &fdb);

		if (odb > -1)
		{
			uint s = 0;
			sint ret = 0;
			d_con_->o_com = true;
			rc = UpdMTXPrio();
			bool sdone = false;
			while (!sdone)
			{
				if (stmts[s].stmt.empty() && Commands_->size() == stmts.size())
				{
					Commands_->at(s).Clear();
				}
				else
				{
					c_char* tail;
					sqlite3_stmt* ppstmt;
					rc = sqlite3_prepare_v2(d_con_->db_, stmts[s].stmt.c_str(), (sint)stmts[s].stmt.length(), &ppstmt, &tail);

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
								if (debug_lvl >= 700 && debug_m)
								{
									rc = Output("SQLITE_OK", 2);
								}
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 700 && debug_m)
								{
									rc = Output("SQLITE_DONE", 2);
								}
								done = true;
								break;
							}
							case SQLITE_ROW:
							{
								if (debug_lvl >= 700 && debug_m)
								{
									rc = Output("SQLITE_ROW", 2);
								}
								
								rc = FindColumn("PRIV", ppstmt);

								if (rc > -1)
								{
									rc = sqlite3_column_int(ppstmt, rc);
									sint xc = GetClientPriv();

									if (xc < rc)
									{
										if (debug_lvl >= 500 && debug_m)
										{
											c_char* output("not enough priv");
											xc = Output(output, 2);
										}
									}
									else
									{
										BOTCOMMAND ncm;
										Commands_->push_back(ncm);
										Commands_->at(ret).Clear();

										rc = FindColumn("ID", ppstmt);

										if (rc > -1)
										{
											Commands_->at(ret).id = sqlite3_column_int(ppstmt, rc);
										}

										rc = FindColumn("CMD_ID", ppstmt);

										if (rc > -1)
										{
											Commands_->at(ret).cmd_id = sqlite3_column_int(ppstmt, rc);
										}

										rc = FindColumn("COMMAND", ppstmt);

										if (rc > -1)
										{
											if (sqlite3_column_text(ppstmt, rc) != NULL)
											{
												Commands_->at(ret).cmd.append(reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, rc)));
											}
										}
										ret++;
									}
								}
								break;
							}
							default:
							{
								sdone = true;
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
					s++;

					if (s >= stmts.size())
					{
						sdone = true;
					}
				}
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
sint machine::GetLogin(c_char* str_, c_char* strI_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 ncar;
		sint xc = bot_sprintf(ncar.carr, ncar.siz, "::GetLogin(c_char* str_(%i), c_char* strI_(%i))", (sint)str_, (sint)str_);
		xc = Output(ncar.carr, 2);
	}

	if (!str_)
	{
		return -1;
	}

	BOT_STMT t(false, 0, "litebot", "ACCOUNTS", 1);
	t.AddCond(0, "LOGIN_NAME", sql_comp_keywords[5], LEncStrI(Uppercase(str_).c_str(), -1).c_str());
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
						if (debug_lvl >= 700 && debug_m)
						{
							sint op = Output("SQLITE_OK", 2);
						}
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 700 && debug_m)
						{
							sint op = Output("SQLITE_DONE", 2);
						}
						done = true;
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 700 && debug_m)
						{
							sint op = Output("SQLITE_ROW", 2);
						}

						if (sqlite3_column_text(ppstmt, 2) != NULL)
						{
							if (!strcmp(strI_, reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, 2))))
							{
								strI_ = "";
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
						if (debug_lvl >= 700 && debug_m)
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
sint machine::UpdateAccount(BOT_CLIENT *Client_)
{
	if (debug_lvl >= 700 && debug_m)
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
	xc = vtool.AVTV(&tvec, &t, false, false);
	xc = Commit(&tvec);
	return 0;
}
sint machine::GetLastAccess(BOT_DB_M *dbs_, sint *last_modi_, sint *last_modi_ns_, sint *last_maint_, sint *last_maint_ns_)
{
	if (debug_lvl >= 750 && debug_m)
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
							if (debug_lvl >= 750 && debug_m)
							{
								sint xp = Output("SQLITE_OK", 2);
							}
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 750 && debug_m)
							{
								sint xp = Output("SQLITE_DONE", 2);
							}
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 750 && debug_m)
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
							if (debug_lvl >= 750 && debug_m)
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
sint machine::LastAccessMaintenance(BOT_DB_M *dbs_)
{
	if (debug_lvl >= 750 && debug_m)
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
							if (debug_lvl >= 750 && debug_m)
							{
								sint xp = Output("SQLITE_OK", 2);
							}
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 750 && debug_m)
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
									sint ac = vtool.AVTV(&t.conds, nstr.c_str(), true, true);
									t.cspec = 0;
									tvec.push_back(t);
								}
							}
							done = true;
							break;
						}
						case SQLITE_ROW:
						{
							if (debug_lvl >= 750 && debug_m)
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
									sint ac = vtool.AVTV(&t.conds, nstr.c_str(), true, true);
									t.cspec = 0;
									ac = vtool.AVTV(&tvec, &t, true, true);
								}
							}
							break;
						}
						case SQLITE_BUSY:
						{
							if (debug_lvl >= 750 && debug_m)
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
sint machine::PushToDBList(BOT_DB *dbs_)
{
	if (debug_lvl >= 550 && debug_m)
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
		else if (!strcmp(dbs_->name.c_str(), "symbols"))
		{
			dbs_->type = 3;
		}
		else if (!strcmp(dbs_->name.c_str(), "scripts"))
		{
			dbs_->type = 4;
		}
		else if (strlen(dbs_->name.c_str()) < 3)
		{
			dbs_->type = 5;
		}
		else
		{
			dbs_->type = 6;
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
				ret = vtool.AVTV(&dbs_->tables, bot_strt.litebot_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols, colss;
				dbs_->columns[ret].push_back(colss);
				dbs_->columns[ret].push_back(colss);
				_char c = ' ';

				if (t < (sint)bot_strt.litebot_columns.size())
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
						dbs_->columns[ret][0].push_back(cols[x]);
						x++;

						if (x < cols.size())
						{
							dbs_->columns[ret][1].push_back(cols[x]);
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
				ret = vtool.AVTV(&dbs_->tables, bot_strt.math_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols, colss;
				dbs_->columns[ret].push_back(colss);
				dbs_->columns[ret].push_back(colss);
				_char c = ' ';

				if (t < (sint)bot_strt.math_columns.size())
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
						dbs_->columns[ret][0].push_back(cols[x]);
						x++;

						if (x < cols.size())
						{
							dbs_->columns[ret][1].push_back(cols[x]);
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
			sint nh = -1;
			sint np = LockGMutex(MTX_FTYPE, &nh);

			if (np > -1)
			{
				for (uint t = 1; t < bot_symbol_types.size(); t++)
				{
					tcols.clear();
					cols.clear();
					colss.clear();
					ret = vtool.AVTV(&dbs_->tables, bot_symbol_types[t], false, false);
					dbs_->columns.push_back(tcols);
					dbs_->columns[ret].push_back(colss);
					dbs_->columns[ret].push_back(colss);

					if (t < (sint)bot_strt.code_columns.size())
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
							dbs_->columns[ret][0].push_back(cols[x]);
							x++;

							if (x < cols.size())
							{
								dbs_->columns[ret][1].push_back(cols[x]);
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
			for (uint t = 0; t < bot_strt.syms_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.syms_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols, colss;
				dbs_->columns[ret].push_back(colss);
				dbs_->columns[ret].push_back(colss);
				_char c = ' ';

				if (t < (sint)bot_strt.syms_cols.size())
				{
					std::string str;
					str.append(bot_strt.syms_cols[t]);
					sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
				}
				else
				{
					std::string str;
					str.append(bot_strt.syms_cols[(sint)bot_strt.syms_cols.size() - 1]);
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
						dbs_->columns[ret][0].push_back(cols[x]);
						x++;

						if (x < cols.size())
						{
							dbs_->columns[ret][1].push_back(cols[x]);
							x++;
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			for (uint t = 0; t < bot_strt.scripts_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.scripts_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols, colss;
				dbs_->columns[ret].push_back(colss);
				dbs_->columns[ret].push_back(colss);
				_char c = ' ';

				if (t < (sint)bot_strt.scripts_cols.size())
				{
					std::string str;
					str.append(bot_strt.scripts_cols[t]);
					sint xp = stool.SeparateStrByChar(str.c_str(), c, &cols);
				}
				else
				{
					std::string str;
					str.append(bot_strt.scripts_cols[(sint)bot_strt.scripts_cols.size() - 1]);
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
						dbs_->columns[ret][0].push_back(cols[x]);
						x++;

						if (x < cols.size())
						{
							dbs_->columns[ret][1].push_back(cols[x]);
							x++;
						}
					}
				}
			}
			break;
		}
		default:
		{
			ret = -1;
			if (!dbs_->tables.empty() || strcmp(dbs_->tables[0].c_str(), "LAST_ACCESS"))
			{
				return -1;
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

sint machine::StartThread(sint* thr_opt)
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
sint machine::ThreadRest(slint dur, sint qt_lvl)
{
	sint qt = GetThreadQuit();

	if (qt >= qt_lvl)
	{
		if (debug_lvl >= 100 && debug_m)
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
sint machine::ThreadEnd(std::vector<ullint>* rvals_)
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
sint machine::PThreadErr(_char in_chr[], sint err)
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
sint machine::IncrThreads()
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
sint machine::DecrThreads()
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
sint machine::GetThreadsCt()
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
sint machine::GetThreadQuit()
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
sint machine::SetThreadQuit(sint val)
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
sint machine::StopAllThreads()
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
sint machine::JoinThread(sint thrid, void* vp_)
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
sint machine::InitThread(TINFO_M *tts_, sint* ret_)
{
	if (debug_lvl >= 200 && debug_m)
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
sint machine::InitThreads(std::vector<TINFO_M> *tts_, std::vector<sint>* rets_)
{
	if (debug_lvl >= 200 && debug_m)
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
	ret = vtool.CLNV(tts_);
	return ret;
}
sint machine::CreateThread(TINFO_M* tts_, sint* ret_)
{
	if (debug_lvl >= 200 && debug_m)
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

				if (debug_lvl >= 1 && debug_m)
				{
					carr_512 ncar;

					if (xc)
					{
						na = bot_sprintf(ncar.carr, ncar.siz, "Error(%i) initializing thread:%s", xc, tts.thread_name.c_str());
						na = Output(ncar.carr, 2);
					}
					else
					{
						if (debug_lvl >= 200)
						{
							na = bot_sprintf(ncar.carr, ncar.siz, "thread created %i %s", tts.lid, tts.thread_name.c_str());
							na = Output(ncar.carr, 2);
						}
					}
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

				if (debug_lvl >= 200 && debug_m)
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
sint machine::FinishThread(TINFO_M* tts_, sint* ret_)
{
	if (debug_lvl >= 200 && debug_m)
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
			if (debug_lvl >= 200 && debug_m)
			{
				sint lx = Output("attempting to join thread", 2);
			}

			if (tts_->fin == 1 || tts_->fin == -1 || tts_->fin == -8)
			{
				mk_thr = true;
				sint hx = UpdMTXPrio();
				hx = -1;
				sint lx = LockElement(MTX_TTS, tts_->lid, &hx, true, false);

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

							if (debug_lvl >= 200 && debug_m)
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
sint machine::TM()
{
	if (debug_lvl >= 200 && debug_m)
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
					if (debug_lvl >= 200 && debug_m)
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
			if (debug_lvl >= 200 && debug_m)
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
				if (debug_lvl >= 200 && debug_m)
				{
					sint xc = Output("creating test threads", 2);
				}
				std::vector<sint> rets;
				sint p = InitThreads(&create_vec, &rets);
			}
		}
		if (!has_log)
		{
			if (debug_lvl >= 200 && debug_m)
			{
				sint xc = Output("adding LogMaintenance to thread list", 2);
			}
			TINFO_M tts(0, "LogMaintenance", LogMaintenance, lid, 1.0f);
			sint xc = InitThread(&tts);
		}
		if (!has_dm)
		{
			if (debug_lvl >= 200 && debug_m)
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
				if (debug_lvl >= 200 && debug_m)
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
sllint machine::TestThreadIter(sint to_)
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

	if (debug_lvl >= 200 && debug_m)
	{
		carr_512 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "%s: iter_to:%i span.count()=%lli", ptn.c_str(), to_, lc);
		op = Output(outp.carr, 2);
	}
	return lc;
}
sllint machine::TestThreadTRat(sint to_)
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

	if (debug_lvl >= 200 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "this thread's time was:%lli compared to fastest time:%lli setting this ratio:%.9f", rc, xc, thr_exe_mod);
		op = Output(outp.carr, 2);
	}
	return rc;
}

sint machine::CheckPrintFs()
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

sint machine::ProcErrLog(sint opt, c_char* in_file_p, c_char* in_file_n, c_char* in_file_t, c_char* rampid, c_char* insp_type, c_char* date_, c_char* eid_, c_char* toval_)
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

sint machine::ProcVINs(sint opt, c_char* in_file_p, c_char* in_file_n, c_char* in_file_t, c_char* rampid, c_char* insp_type, c_char* date_, c_char* eid_, c_char* toval_)
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

sint machine::GetVINs(c_char* in_file_p, c_char* in_file_n, c_char* in_file_t, c_char* rampid)
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

sint machine::AddDlrCode(c_char* to_vin, c_char* in_file)
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

sint machine::SetClientName(std::string* ClientName )
{
	Client.name.clear();
	Client.name.append(*ClientName);
	Client.nameset = true;
	return 0;
}

sint machine::GetClientName(std::string* str_ )
{
	str_->clear();
	str_->append(Client.name.c_str() );
	return 0;
}

sint machine::SetClientLoginName(std::string* ClientLoginName )
{
	Client.login_name.clear();
	Client.login_name.append( *ClientLoginName);
	return 0;
}

sint machine::GetClientLoginName(std::string* str_)
{
	if (!str_)
	{
		return -1;
	}

	if (!str_->empty())
	{
		str_->clear();
	}

	str_->append(Client.login_name.c_str());

	return 0;
}

sint machine::SetClientLastLogin(std::string* LastLogin)
{
	if (!LastLogin)
	{
		return -1;
	}

	Client.lastlogin.clear();
	Client.lastlogin.append(LastLogin->c_str());
	return 0;
}

sint machine::GetClientLastLogin(std::string* str_)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.lastlogin.c_str());
	return 0;
}

sint machine::SetClientLastFailedLogin(std::string* LastFailedLogin)
{
	if (!LastFailedLogin)
	{
		return -1;
	}

	Client.last_failed_login.clear();
	Client.last_failed_login.append(LastFailedLogin->c_str());
	return 0;
}

sint machine::GetClientLastFailedLogin(std::string* str_)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.last_failed_login.c_str());
	return 0;
}

sint machine::SetClientLastExchange(std::string* LastExchange)
{
	if (!LastExchange)
	{
		return -1;
	}
	Client.lastexchange.clear();
	Client.lastexchange.append(LastExchange->c_str());
	return 0;
}

sint machine::GetClientLastExchange(std::string* str_)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.lastexchange.c_str());
	return 0;
}

sint machine::SetClientLoginDate(std::string* LoginDate)
{
	if (!LoginDate)
	{
		return -1;
	}

	Client.logindate.clear();
	Client.logindate.append(LoginDate->c_str());
	return 0;
}

sint machine::GetClientLoginDate(std::string* str_)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.logindate.c_str());
	return 0;
}

sint machine::SetClientID(sint x)
{
	Client.lid = x;
	return 0;
}

sint machine::GetClientID()
{
	sint xc = Client.lid;
	return xc;
}

sint machine::SetClientPriv(sint x)
{
	Client.priv = x;
	return 0;
}

sint machine::GetClientPriv()
{
	sint xc = Client.priv;
	return xc;
}

sint machine::SetClientTotalLogins(sint x)
{
	Client.totallogins = x;
	return 0;
}

sint machine::GetClientTotalLogins()
{
	sint xc = Client.totallogins;
	return xc;
}

sint machine::SetClientFailedLogins(sint x)
{
	Client.failed_logins = x;
	return 0;
}

sint machine::GetClientFailedLogins()
{
	sint xc = Client.failed_logins;
	return xc;
}

sint machine::SetClientLoggedIn(bool x)
{
	Client.loggedin = x;
	return 0;
}

bool machine::GetClientLoggedIn()
{
	bool x = Client.loggedin;
	return x;
}

sint machine::DoOutput()
{
	if (Client.name.empty())
	{
		return 0;
	}

	std::string output = DetermineOutput();
	sint oc = Output(output.c_str(), 0);
	return oc;
}

std::string machine::DetermineOutput()
{
	std::string suboutput;
	return suboutput;
}

void* machine::ScanFileThread(void* vp_)
{
	sint xc = (sint)vp_;
	carr_64 ncar;
	sint rc = bot_sprintf(ncar.carr, ncar.siz, "ScanFileThread", xc);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, ncar.carr, true, false);
	rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ScanFileThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	sint ret = -1;
	std::vector<ullint> vals;
	rc = LITEBot.GetVecEleMem((void*)&vals, MTX_TTS, LITEBot.lid, BOT_TTS_VALS);
	
	if (vals.size() > 3)
	{
		BOT_FILE_M nfile;
		rc = LITEBot.GetVecEle((void*)&nfile, MTX_FO, (sint)vals[0]);

		if (rc > -1)
		{
			nfile.fst.RenewLocs(vals[3], 0, vals[2]);
			vals.clear();

			if (rc > -1)
			{
				ret = LITEBot.BOTScanFileSyms(&nfile);
				vals.push_back((ullint)ret);
				rc = LITEBot.PushToVecEleMem((void*)&nfile.fst, MTX_FO, nfile.lid, BOT_FS_STATE, false);
				vals.push_back((ullint)rc);
			}
		}
	}

	rc = LITEBot.ThreadEnd();
	pthread_exit((void*)ret);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::RendFileThread(void* vp_)
{
	sint xc = (sint)vp_;
	carr_64 ncar;
	sint rc = bot_sprintf(ncar.carr, ncar.siz, "RendFileThread", xc);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, ncar.carr, true, false);
	rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::RendFileThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	sint ret = -1;
	std::vector<ullint> vals;
	rc = LITEBot.GetVecEleMem((void*)&vals, MTX_TTS, LITEBot.lid, BOT_TTS_VALS);

	if (vals.size() > 3)
	{
		BOT_FILE_M nfile;
		rc = LITEBot.GetVecEle((void*)&nfile, MTX_FO, (sint)vals[0]);

		if (rc > -1)
		{
			nfile.omode = (sint)vals[1];
			nfile.fst.e_loc = vals[3];
			nfile.fst.ia_loc = vals[2];
			vals.clear();

			if (rc > -1)
			{
				ret = LITEBot.BOTRendFileSyms(&nfile);
				vals.push_back((ullint)ret);
			}
		}
	}

	rc = LITEBot.ThreadEnd();
	pthread_exit((void*)ret);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::LogMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(10, 1, xc, "LogMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::LogMaintenance(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	slint rst_for = (slint)BOT_LOGREST;
	bool done = false;

	while (!done)
	{
		for (sint siz = 0; siz < LITEBot.VecSize(MTX_LOG); siz++)
		{
			BOT_LOGDET_M logm;
			rc = LITEBot.GetVecEle((void*)&logm, MTX_LOG, siz);

			if (rc > -1)
			{
				if (logm.lsiz)
				{
					sint h = -1;
					sint p = LITEBot.LockGMutex(MTX_LOG, &h, true);
					
					if (p > -1)
					{
						sint hl = -1;
						rc = LITEBot.LockElement(MTX_LOG, siz, &hl, true, false);

						if (rc > -1)
						{
							std::string pth;
							LITEBot.BOTPath(&pth, BOT_LOG_NM);
#ifdef _WIN32
							pth.push_back('\\');
#else
							pth.push_back('/');
#endif
							BOT_FILE_M xfile(logm.logtitle.c_str(), ".txt", pth.c_str(), BOT_FILE_APPEND, BOT_F_CON, -1, LITEBot.lid);
							sint ox = -1;
							rc = LITEBot.BOTOpenFile(&xfile, &ox, true);

							if (rc > -1)
							{
								sint op = LITEBot.BOTFileOUT(&xfile, BOT_RTV_VSTR, &bot_log_vec.d_vec[siz].log_q, BOT_RTV_MAX);

								if (!op)
								{
									bot_log_vec.d_vec[logm.lid].log_q.clear();
								}
								if (!ox)
								{
									ox = LITEBot.BOTCloseFile(&xfile);
								}
							}
							if (!hl)
							{
								hl = LITEBot.UnlockElement(MTX_LOG, siz, false);
							}
						}
						if (!h)
						{
							h = LITEBot.UnlockGMutex(MTX_LOG);
						}
					}
				}
			}
		}

		rc = LITEBot.ThreadRest((slint)BOT_LOGREST, (sint)BOT_THRQ_LOG);
		
		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	rc = 1;
	pthread_exit((void*)rc);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::ConsoleThread(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ConsoleThread", true, false);
	sint rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ConsoleThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	rc = LITEBot.Output("win_LITEBot_I 2018", 0);
	bool done = false;

	while (!done)
	{
		rc = LITEBot.BOTConsole();
		rc = LITEBot.ThreadRest((slint)BOT_CNSREST, (sint)BOT_THRQ_CONS);

		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	rc = 1;
	pthread_exit((void*)rc);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::TestThread(void* vp_)
{
	sint xc = (sint)vp_;
	carr_64 ncar;
	sint rc = bot_sprintf(ncar.carr, ncar.siz, "TestThread%i", xc);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, ncar.carr, true, false);
	rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	if (LITEBot.debug_lvl >= 200 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::TestThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	sllint lc = LITEBot.TestThreadTRat((sint)BOT_ITER_TO);
	rc = LITEBot.ThreadEnd();
	pthread_exit((void*)lc);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

// Database Maintenance

void* machine::DBMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "DBMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_256 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::DBMaintenance(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	bool done = false;

	while (!done)
	{
		BOT_DB_M dbs("litebot", 0);
		rc = LITEBot.GetInVec((void*)&dbs, MTX_DBL);

		if (rc > -1)
		{
			TINFO_M ntts(1, "LITEBotMaintenance", LITEBot.LITEBotMaintenance, LITEBot.lid);
			sint ret = -1;
			rc = LITEBot.InitThread(&ntts, &ret);

			if (rc)
			{

				sint xret = -1;
			}
		}
		else
		{
			if (LITEBot.debug_lvl >= 1 && &LITEBot.debug_m)
			{
				rc = LITEBot.Output("could not find db: litebot", 2);
			}
		}
	
		rc = LITEBot.ThreadRest((slint)BOT_DBREST, (sint)BOT_THRQ_DBM);

		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	rc = 1;
	pthread_exit((void*)rc);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::LITEBotMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "LITEBotMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	BOT_DB_M dbs("litebot", 0);
	rc = LITEBot.GetInVec((void*)&dbs, MTX_DBL, false);

	if (rc > -1)
	{
		if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
		{
			carr_64 outc;
			rc = bot_sprintf(outc.carr, outc.siz, "::LITEBotMaintenance(void* vp_(%i) for database:%s)", LITEBot.lid, dbs.name.c_str());
			rc = LITEBot.Output(outc.carr, 2);
		}

		sint last_modi = 0;
		sint last_maint = 0;
		sint last_modi_ns = 0;
		sint last_maint_ns = 0;
		rc = LITEBot.GetLastAccess(&dbs, &last_modi, &last_modi_ns, &last_maint, &last_maint_ns);
		rc = LITEBot.LastAccessMaintenance(&dbs);
	}
	else
	{
		rc = LITEBot.VerifyDatabases();
	}

	rc = LITEBot.ThreadEnd();
	rc = 0;
	pthread_exit((void*)rc);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::CodeMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "CodeMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc < 0)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	BOT_DB_M dbs("code", 2);
	rc = LITEBot.GetInVec((void*)&dbs, MTX_DBL, false, false);

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::CodeMaintenance(void* vp_(%i) for database:%s)", LITEBot.lid, dbs.name.c_str());
		rc = LITEBot.Output(outc.carr, 2);
	}

	sint last_modi = 0;
	sint last_maint = 0;
	sint last_modi_ns = 0;
	sint last_maint_ns = 0;
	rc = LITEBot.GetLastAccess(&dbs, &last_modi, &last_modi_ns, &last_maint, &last_maint_ns);
	rc = LITEBot.LastAccessMaintenance(&dbs);

	if ((last_maint == last_modi && last_maint_ns > last_modi_ns) || last_modi < last_maint)
	{
		rc = 0;
	}
	else
	{
		BOT_DB ndb;
		rc = LITEBot.GetVecEle((void*)&ndb, MTX_DBL, dbs.lid, false);

		if (rc > -1)
		{
			sint ct = 0;
			std::vector<MACSYM> rcodes;

			for (sint i = (sint)ndb.tables.size() - 1; i > 0; i--)
			{
				MACSYM nc;
				rc = LITEBot.GetCode(&rcodes, "LAST_MODIFIED > LAST_MAINTAINED OR LAST_MODIFIED = LAST_MAINTAINED AND LAST_MODIFIED_NS > LAST_MAINTAINED_NS", true);

				if (!rcodes.empty())
				{
					if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
					{
						std::string output;
						output.append("Maintenance for table: ");
						output.append(ndb.name);
						output.append(".");
						output.append(ndb.tables[i]);
						rc = LITEBot.Output(output.c_str(), 2);
					}

					if (!strcmp("unclassified", ndb.tables[i].c_str()))
					{
						for (rc = ct; rc < (sint)rcodes.size(); rc++)
						{
							rcodes[rc].ud_last_maintained = true;
							for (sint a = 0; a < (sint)rcodes[rc].usages.size(); a++)
							{
								if (rcodes[rc].usages[a] > -1)
								{
									for (sint b = (sint)rcodes[rc].usages.size() - 1; b > a; b--)
									{
										if (rcodes[rc].usages[a] == rcodes[rc].usages[b])
										{
											rcodes[rc].ud_usages = true;
											rcodes[rc].usages[b] = -1;
										}
									}
								}
							}
							rcodes[rc].used_as = -1;
						}
						ct = rc;
					}
					else if (!strcmp("word", ndb.tables[i].c_str()))
					{

					}
					else if (!strcmp("punctuation", ndb.tables[i].c_str()))
					{

					}
					else if (!strcmp("filename", ndb.tables[i].c_str()))
					{

					}
					else if (!strcmp("filetype", ndb.tables[i].c_str()))
					{

					}
					else if (!strcmp("command_symbol", ndb.tables[i].c_str()))
					{

					}
					else if (!strcmp("logical", ndb.tables[i].c_str()))
					{

					}
					else if (!strcmp("LAST_ACCESS", ndb.tables[i].c_str()))
					{

					}
					else
					{
						//address new table
					}
				}
			}

			if (!rcodes.empty())
			{
				rc = LITEBot.AddCode(&rcodes);
			}
			else
			{
				BOT_STMT t(true);
				t.maint = true;
				t.AddDB(dbs.name.c_str());
				t.AddCont("LAST_ACCESS", 1);
				std::vector<BOT_STMT> tvec;
				tvec.push_back(t);
				rc = LITEBot.Commit(&tvec);
			}
		}
	}
	rc = LITEBot.ThreadEnd();
	rc = 0;
	pthread_exit((void*)rc);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

std::string machine::Uppercase(c_char* str_)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		std::string output;
		output.append("Uppercase(");
		output.append(str_);
		output.append(")");
		sint oc = Output(output.c_str(), 2);
	}

	std::string r_str;

	if (!str_)
	{
		return r_str;
	}

	size_t slen = strlen(str_);

	for (size_t i = 0; i < slen; i++)
	{
		switch (str_[i])
		{
		case 'a':
		{
			r_str.push_back('A');
			break;
		}
		case 'b':
		{
			r_str.push_back('B');
			break;
		}
		case 'c':
		{
			r_str.push_back('C');
			break;
		}
		case 'd':
		{
			r_str.push_back('D');
			break;
		}
		case 'e':
		{
			r_str.push_back('E');
			break;
		}
		case 'f':
		{
			r_str.push_back('F');
			break;
		}
		case 'g':
		{
			r_str.push_back('G');
			break;
		}
		case 'h':
		{
			r_str.push_back('H');
			break;
		}
		case 'i':
		{
			r_str.push_back('I');
			break;
		}
		case 'j':
		{
			r_str.push_back('J');
			break;
		}
		case 'k':
		{
			r_str.push_back('K');
			break;
		}
		case 'l':
		{
			r_str.push_back('L');
			break;
		}
		case 'm':
		{
			r_str.push_back('M');
			break;
		}
		case 'n':
		{
			r_str.push_back('N');
			break;
		}
		case 'o':
		{
			r_str.push_back('O');
			break;
		}
		case 'p':
		{
			r_str.push_back('P');
			break;
		}
		case 'q':
		{
			r_str.push_back('Q');
			break;
		}
		case 'r':
		{
			r_str.push_back('R');
			break;
		}
		case 's':
		{
			r_str.push_back('S');
			break;
		}
		case 't':
		{
			r_str.push_back('T');
			break;
		}
		case 'u':
		{
			r_str.push_back('U');
			break;
		}
		case 'v':
		{
			r_str.push_back('V');
			break;
		}
		case 'w':
		{
			r_str.push_back('W');
			break;
		}
		case 'x':
		{
			r_str.push_back('X');
			break;
		}
		case 'y':
		{
			r_str.push_back('Y');
			break;
		}
		case 'z':
		{
			r_str.push_back('Z');
			break;
		}
		case '+':
		{
			r_str.push_back(str_[i]);// using a common symbol seems to expand support for char constants so foreign chars will compile. comment out chars after this and compile, future compiles will succeed until c4droid is minimized or closed.
			break;
		}
		/*
		case 'ä' :
		{
		r_str+=( 'Ä' );
		break;
		}

		case 'ï' :
		{
		r_str+=( 'Ï' );
		break;
		}

		case 'ë' :
		{
		r_str+=( 'Ë' );
		break;
		}

		case 'ö' :
		{
		r_str+=( 'Ö' );
		break;
		}

		case 'ü' :
		{
		r_str+=( 'Ü' );
		break;
		}

		case 'ß' :
		{
		r_str+=( 'ß' );
		break;
		}

		case 'ñ' :
		{
		r_str+=( 'Ñ' );
		break;
		}
		*/
		default:
		{
			r_str.push_back(str_[i]);
			break;
		}
		}
	}
	if (debug_lvl >= 1100 && debug_m)
	{
		std::string output;
		output.append("uppercased: ");
		output.append(r_str);
		sint oc = Output(output.c_str(), 2);
	}
	return r_str;
}

std::string machine::CleanPunctuation(c_char* clientinput_)
{
	std::string str;

	if (!clientinput_)
	{
		return str;
	}

	size_t slen = strlen(clientinput_);

	for (uint i = 0; i < slen; i++)
	{
		bool b = true;

		switch (clientinput_[i])
		{
		case '+':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			break;
		}
		/*
		case 'ß' :
		case 'Ñ' :
		case 'ñ' :
		case 'ë' :
		case 'ē' :
		case 'ę' :
		case 'ě' :
		case 'ĕ' :
		case 'ə' :
		case 'è' :
		case 'é' :
		case 'ê' :
		case 'ŕ' :
		case 'ř' :
		case 'þ' :
		case 'ť' :
		case 'ț' :
		case 'ţ' :
		case 'ý' :
		case 'ų' :
		case 'ű' :
		case 'ů' :
		case 'ū' :
		case 'ü' :
		case 'û' :
		case 'ú' :
		case 'ù' :
		case 'į' :
		case 'ī' :
		case 'ï' :
		case 'î' :
		case 'í' :
		case 'ì' :
		case 'œ' :
		case 'ő' :
		case 'ø' :
		case 'ö' :
		case 'õ' :
		case 'ô' :
		case 'ó' :
		case 'ò' :
		case 'å' :
		case 'æ' :
		case 'ā' :
		case 'ă' :
		case 'ą' :
		case '@' :
		case 'à' :
		case 'á' :
		case 'â' :
		case 'ã' :
		case 'ä' :
		case 'ś' :
		case 'š' :
		case 'ş' :
		case '§' :
		case 'ď' :
		case 'đ' :
		case 'ģ' :
		case 'ğ' :
		case 'ķ' :
		case 'ł' :
		case 'ľ' :
		case 'ļ' :
		case 'ĺ' :
		case 'ź' :
		case 'ż' :
		case 'ž' :
		case 'ç' :
		case 'ć' :
		case 'č' :
		case 'ň' :
		case 'ņ' :
		case 'ń' :
		case 'Ė' :
		case 'Ę' :
		case 'Ě' :
		case 'Ĕ' :
		case 'È' :
		case 'É' :
		case 'Ê' :
		case 'Ë' :
		case 'Ē' :
		case 'Ŕ' :
		case 'Ř' :
		case 'Ť' :
		case 'Ț' :
		case 'Ţ' :
		case 'Ý' :
		case 'Ų' :
		case 'Ű' :
		case 'Ů' :
		case 'Ū' :
		case 'Ü' :
		case 'Û' :
		case 'Ú' :
		case 'Ù' :
		case 'Œ' :
		case 'Ő' :
		case 'Ø' :
		case 'Ö' :
		case 'Õ' :
		case 'Ô' :
		case 'Ó' :
		case 'Ò' :
		case 'Å' :
		case 'Æ' :
		case 'Ā' :
		case 'Ă' :
		case 'Ą' :
		case 'À' :
		case 'Á' :
		case 'Â' :
		case 'Ã' :
		case 'Ä' :
		case 'Ś' :
		case 'Š' :
		case 'Ş' :
		case 'Ď' :
		case 'Đ' :
		case 'Ģ' :
		case 'Ğ' :
		case 'Ķ' :
		case 'Ł' :
		case 'Ľ' :
		case 'Ļ' :
		case 'Ĺ' :
		case 'Ź' :
		case 'Ż' :
		case 'Ž' :
		case 'Ç' :
		case 'Ć' :
		case 'Č' :
		case 'Ň' :
		case 'Ņ' :
		case 'Ń' :
		case '$' :
		case '€' :
		case '£' :
		case '¥' :
		{
		break;
		}
		*/
		default:
		{
			b = false;
			break;
		}
		}
		if (b)
		{
			str.push_back(clientinput_[i]);
		}
	}
	return str;
}