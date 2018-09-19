#include "litebot.h"

// MTX_REQ
_mtx req_mtx;
lok_defr lok_d;

// MTX_DBG
sint bot_dbg_l;
sint bot_dbg_m;

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
BOT_STRT_UP bot_strt;
bot_strt_syms bot_strt_s;

// MTX_FCON
BOTF_CONN FCON[BOT_FS_LIM];

// MTX_FPAD
_char* fpad[BOT_FS_LIM];

// MTX_BTIM
std::chrono::steady_clock::time_point bot_strt_tim;

// MTX_DMAP
#ifdef _WIN32
BOT_DIR bot_dmap("c:\\");
#else
#ifdef _BOT_FOR_ANDR_
BOT_DIR bot_dmap("\\storage\\");
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

// MTX_PORTS
bot_port_counter bot_prts;

// MTX_PCL
BOT_CLIENT pcli;

/* -------------------------------------------------------------------------------- */
sint main()
{
	sint xc = 0;
	carr_256 ncar;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, 0, "machine", true, true);
	xc = LITEBot.LITEBot(&ncar, true);
	std::cout << ncar.carr << std::endl;
	return xc;
	pthread_exit(0);
}
/* -------------------------------------------------------------------------------- */

bool bot_sisn(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}
	sint x = 0;
	c_char* nstr = BOT_N_STR;

	for (slen--; slen > -1; slen--)
	{
		x = 0;

		while (x < 10)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
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
	c_char* nstr = BOT_N_STR;

	for (slen--; slen > -1; slen--)
	{
		for (x = 0; x < 10; x++)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
			{
				return (sint)slen;
			}
		}
	}
	return -1;
}
bool bot_sish(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}

	if (!strcmp(&val[slen - 1], "'"))
	{
		if (slen > 3)
		{
			if (strcmp(&val[1], "'") || (strcmp(&val[0], "X") || strcmp(&val[0], "x")))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		slen--;
	}
	sint x = 0;
	c_char* nstr = "0123456789ABCDEF";

	for (slen--; slen > -1; slen--)
	{
		x = 0;

		while (x < 10)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
			{
				x = 10;
			}
			x++;
		}

		if (x == 10)
		{
			if (slen == 1)
			{
				if (!strcmp(&val[slen], "x") || !strcmp(&val[slen], "X"))
				{
					slen--;
					if (!strcmp(&val[slen], "0"))
					{
						return true;
					}
				}
				else if (!strcmp(&val[slen], "'"))
				{
					slen--;
					if (!strcmp(&val[slen], "x") || !strcmp(&val[slen], "X"))
					{
						return true;
					}
				}
				else {}
			}
			else if (!slen)
			{
				if (!strcmp(&val[slen], "x") || !strcmp(&val[slen], "X"))
				{
					return true;
				}
			}
			else {}
			return false;
		}
	}
	return true;
}
bool bot_sisa(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}
	sint x = 0;
	c_char* nstr = BOT_A_STR;

	for (slen--; slen > -1; slen--)
	{
		x = 0;

		while (x < 53)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
			{
				x = 53;
			}
			x++;
		}

		if (x == 53)
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
	c_char* nstr = BOT_A_STR;

	for (slen--; slen > -1; slen--)
	{
		for (x = 0; x < 53; x++)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
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

const size_t bot_strlen(_char val[])
{
	if (!val)
	{
		return 0;
	}
	_char term = '\0';
	size_t siz = 0;

	while (siz < (size_t)BOT_FILESIZE_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(_char)))
		{
			const size_t csiz = siz;
			return csiz;
		}
		siz++;
	}
	return 0;
}

const size_t bot_cstrlen(c_char val[])
{
	if (!val)
	{
		return 0;
	}
	c_char term{ '\0' };
	size_t siz = 0;

	while (siz < (size_t)BOT_FILESIZE_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(c_char)))
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

	while (siz < (size_t)BOT_FILESIZE_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)&term, sizeof(u_char)))
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

	while (siz < (size_t)BOT_FILESIZE_MAX)
	{
		if (!memcmp((void*)&val[siz], (void*)term, sizeof(cu_char)))
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
	size_t nl = bot_strlen(inchr);

	if (nl)
	{
		_char n = '\0';

		for (; nl; nl--)
		{
			memcpy((void*)&inchr[nl-1], (void*)&n, sizeof(_char));
		}
	}
}

void bot_ustrclr(u_char inchr[])
{
	if (!inchr)
	{
		return;
	}
	size_t nl = bot_ustrlen(inchr);

	if (nl)
	{
		u_char n = (u_char)'\0';

		for (; nl; nl--)
		{
			memcpy((void*)&inchr[nl-1], (void*)&n, sizeof(u_char));
		}
	}
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
		memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(_char));
		std::cout << "*BOTSTRERROR* _char[]: '" << inchr << "' was without a terminating NULL byte.*BOTSTRERROR*" << std::endl;
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
		memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(u_char));
		std::cout << "*BOTUSTRERROR* u_char[]: '" << inchr << "' was without a terminating NULL byte.*BOTUSTRERROR*" << std::endl;
	}
	return (sint)siz;
}

sint bot_cstrchk(c_char inchr[], size_t in_siz)
{
	if (!inchr || !in_siz || in_siz > (size_t)BOT_STRLEN_MAX)
	{
		return -1;
	}
	size_t siz = 0;
	c_char term = '\0';

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
		memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(c_char));
		std::cout << "*BOTSTRERROR* c_char[]: '" << inchr << "' was without a terminating NULL byte.*BOTSTRERROR*" << std::endl;
	}
	return (sint)siz;
}

sint bot_randstr(_char str_[], size_t siz, _char fstr_[], size_t fsiz)
{
	if (!siz || !str_)
	{
		return -1;
	}

	std::chrono::steady_clock::time_point tI = std::chrono::steady_clock::now();

	if (!fstr_)
	{

		_char cfr[64] = { 'W', 'E', 'R', 'n', 'I', 'Z', 'O', 'm', 'P', 'S', 'D', 'F', '5', 'u', 'J', 'K', 'v', 'b', 'y', 'i', '4', '2', 's', 'B', '_', 'L', 'X', 'C', '9', 'V', 'M', 'q', 'c', 'w', 'T', 'Y', 'e', 'r', 'f', '6', 't', 'U', 'A', 'o', 'Q', 'p', 'a', 'F', 'u', 'd', '1', '0', 'g', 'N', 'j', 'k', 'l', 'z', '8', 'x', '3', '7', 'h', '\0' };
		siz--;

		for (size_t x = 0; x < siz; x++)
		{
			std::chrono::steady_clock::time_point tII = std::chrono::steady_clock::now();
			std::chrono::duration<slint, std::nano> dur = std::chrono::duration_cast<std::chrono::nanoseconds>(tII - tI);
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
			std::chrono::steady_clock::time_point tII = std::chrono::steady_clock::now();
			std::chrono::duration<slint, std::nano> dur = std::chrono::duration_cast<std::chrono::nanoseconds>(tII - tI);
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

	size_t strsiz = bot_strlen(inchr);

	if (strsiz)
	{
		bot_strclr(inchr);
	}
	sint ret = -1;
	strsiz = strlen(fstr);
	std::vector<std::string> fspecs;
	std::vector<size_t> locs;
	std::string formspec;
	_char frm = '%';
	_char spec = '.';
	_char term = '\0';

	for (size_t siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr[siz], (void*)&frm, sizeof(_char)))
		{
			formspec.push_back(fstr[siz]);
			bool mustnum = false;

			for (size_t nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(_char)))
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
							memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
							return -2;
						}
						break;
					}
					case 'v':
					{
						if (!mustnum)
						{
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							for (size_t xsiz = siz + nsiz; xsiz < strsiz; xsiz++)
							{
								formspec.push_back(fstr[xsiz]);
								nsiz++;

								if (!memcmp((void*)&fstr[xsiz], (void*)&frm, sizeof(_char)))
								{
									for (xsiz++; xsiz < strsiz; xsiz++)
									{
										formspec.push_back(fstr[xsiz]);
										nsiz++;

										if (!memcmp((void*)&fstr[xsiz], (void*)&frm, sizeof(_char)))
										{
											locs.push_back(siz);
											fspecs.push_back(formspec);
											xsiz = strsiz;
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
							memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
							return -2;
						}
						break;
					}
					default:
					{
						memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
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
		size_t siz = 0;
		size_t at_inchr = 0;
		va_list args;
		va_start(args, fstr);

		for (siz = 0; siz < fspecs.size() && at_inchr < in_siz; siz++)
		{
			size_t hlong = 0;
			size_t sloc = 0;

			if (siz)
			{
				sloc = locs[siz - 1];
			}

			while (sloc < locs[siz] && at_inchr < in_siz)
			{
				memcpy((void*)&inchr[at_inchr], (void*)&fstr[sloc], sizeof(_char));
				at_inchr += sizeof(fstr[sloc]);
				sloc += sizeof(fstr[sloc]);
			}

			if (fspecs[siz].length() > 1)
			{
				sint isiz = 0;
				size_t nsiz = 1;

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(_char)))
				{
					_char fchr[3]{ 0 };
					nsiz++;
					size_t fsiz = 0;

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
								memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
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
							memcpy((void*)&fchr[fsiz], (void*)&fspecs[siz][nsiz], sizeof(_char));
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							memcpy((void*)&fchr[fsiz], (void*)&term, sizeof(_char));
							break;
						}
						}

						if (fsiz == 3)
						{
							memcpy((void*)&fchr[fsiz - 1], (void*)&term, sizeof(_char));
						}
						else
						{
							if (!memcmp((void*)&fchr[fsiz], (void*)&term, sizeof(_char)))
							{
								fsiz = 3;
							}
						}
					}
					if (!memcmp((void*)&fchr[2], (void*)&term, sizeof(_char)) || !memcmp((void*)&fchr[1], (void*)&term, sizeof(_char)) || !memcmp((void*)&fchr[0], (void*)&term, sizeof(_char)))
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (!memcmp((void*)&fspecs[siz][nsiz], (void*)&lenchr, sizeof(_char)))
				{
					hlong++;
					nsiz++;
				}

				_char zchar = '0';
				_char zweichar = '2';

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&zchar, sizeof(_char)) && nsiz < fspecs[siz].length())
				{
					if (!memcmp((void*)&fspecs[siz][nsiz + 1], (void*)&zweichar, sizeof(_char)))
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
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
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
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
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
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
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
						memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
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
							memcpy((void*)&inchr[at_inchr], (void*)&str[sloc], sizeof(_char));
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
						memcpy((void*)&inchr[at_inchr], (void*)&inv, sizeof(_char));
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
						sint xc = snprintf(ci, usiz, fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, usiz);

						for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
						{
							memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
							at_inchr++;
						}
					}
					break;
				}
				case 'v':
				{
					nsiz++;
					carr_21 pspc;
					carr_21 fspc;
					carr_21 spc;
					size_t nct = 0;

					while (nsiz < fspecs[siz].length() && nct < pspc.siz)
					{
						if (nsiz < fspecs[siz].length())
						{
							switch (fspecs[siz][nsiz])
							{
							case '%':
							{
								nct = pspc.siz;
								memcpy((void*)&fspc.carr[0], (void*)&fspecs[siz][nsiz], sizeof(_char));
								break;
							}
							default:
							{
								memcpy((void*)&pspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								break;
							}
							}
						}
						nct++;
						nsiz++;
					}

					nct = 1;

					while (nsiz < fspecs[siz].length() && nct < fspc.siz)
					{
						if (nsiz < fspecs[siz].length())
						{
							switch (fspecs[siz][nsiz])
							{
							case '%':
							{
								nct = fspc.siz;
								break;
							}
							case 'c':
							case 's':
							case 'd':
							case 'i':
							case 'u':
							case 'f':
							case 'X':
							{
								memcpy((void*)&fspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								nct = fspc.siz;
								break;
							}
							default:
							{
								memcpy((void*)&fspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								nct++;
								break;
							}
							}
						}
						nsiz++;
					}

					if (nsiz < fspecs[siz].length() - 1)
					{
						for (size_t x = 0; x < spc.siz && nsiz < fspecs[siz].length() - 1; x++)
						{
							if (memcmp((void*)&fspecs[siz][nsiz], (void*)&frm, sizeof(_char)))
							{
								memcpy((void*)&spc.carr[x], (void*)&fspecs[siz][nsiz], sizeof(_char));
							}
							else
							{
								nsiz = fspecs[siz].length();
							}
							nsiz++;
						}
					}

					size_t flen = bot_strlen(fspc.carr);

					if (flen)
					{
						flen--;
						size_t plen = bot_strlen(pspc.carr);
						size_t slen = strlen(spc.carr);;

						switch (fspc.carr[flen])
						{
						case 'c':
						{
							std::vector<_char>* inv = va_arg(args, std::vector<_char>*);

							for (size_t x = 0; x < inv->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
								if (at_inchr < in_siz)
								{
									memcpy((void*)&inchr[at_inchr], (void*)&inv->at(x), sizeof(_char));
									at_inchr++;
								}
								if (slen && x < (inv->size() - 1))
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
							}
							break;
						}
						case 's':
						{
							/*when specifying %v%<type><sep>% <type> = 's' we use a vector of std::string instead of a vector of c_char* */
							std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

							for (size_t x = 0; x < strv->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
								for (sloc = 0; sloc < strv->at(x).length() && at_inchr < in_siz; sloc++)
								{
									memcpy((void*)&inchr[at_inchr], (void*)&strv->at(x)[sloc], sizeof(_char));
									at_inchr++;
								}
								if (slen && x < (strv->size() - 1))
								{
									for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
										at_inchr++;
									}
								}
							}
							break;
						}
						case 'f':
						{
							std::vector<float>* fvec = va_arg(args, std::vector<float>*);

							for (size_t x = 0; x < fvec->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
								_char ci[64]{ 0 };
								sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
								xc = bot_strchk(ci, 64);

								for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
								{
									memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
									at_inchr++;
								}
								if (slen && x < (fvec->size() - 1))
								{
									for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[64]{ 0 };
									sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 64);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<long double>* fvec = va_arg(args, std::vector<long double>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[64]{ 0 };
									sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 64);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<slint>* fvec = va_arg(args, std::vector<slint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 2)
							{
								std::vector<sllint>* fvec = va_arg(args, std::vector<sllint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<ulint>* fvec = va_arg(args, std::vector<ulint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 2)
							{
								std::vector<ullint>* fvec = va_arg(args, std::vector<ullint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (size_t y = 0; y < slen && at_inchr < in_siz; y++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
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

							for (size_t x = 0; x < inv->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}

								const size_t usiz = (sizeof(u_char) * 16) + 1;

								if (usiz + at_inchr <= in_siz)
								{
									_char ci[usiz]{ 0 };
									sint xc = snprintf(ci, usiz, fspc.carr, (uint)inv->at(x));
									xc = bot_strchk(ci, sizeof(ci));

									for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;

										if (slen && x < (inv->size() - 1))
										{
											for (size_t y = 0; y < slen&& at_inchr < in_siz; y++)
											{
												memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[y], sizeof(_char));
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
			memcpy((void*)&inchr[at_inchr], (void*)&term, sizeof(_char));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(_char));
		}
	}
	else
	{
		size_t siz = 0;

		while (siz < in_siz && siz < strsiz)
		{
			memcpy((void*)&inchr[siz], (void*)&fstr[siz], sizeof(_char));
			siz++;
		}
		if (siz < in_siz)
		{
			memcpy((void*)&inchr[siz], (void*)&term, sizeof(_char));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(_char));
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

	size_t strsiz = bot_cstrlen(inchr);

	if (strsiz)
	{
		bot_cstrclr(inchr);
	}

	sint ret = -1;
	strsiz = strlen(fstr);
	std::vector<std::string> fspecs;
	std::vector<size_t> locs;
	std::string formspec;
	_char frm = '%';
	_char spec = '.';
	_char term = '\0';

	for (size_t siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr[siz], (void*)&frm, sizeof(_char)))
		{
			formspec.push_back(fstr[siz]);
			bool mustnum = false;

			for (size_t nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(_char)))
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
							memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
							return -2;
						}
						break;
					}
					case 'v':
					{
						if (!mustnum)
						{
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							for (size_t xsiz = siz + nsiz; xsiz < strsiz; xsiz++)
							{
								formspec.push_back(fstr[xsiz]);
								nsiz++;

								if (!memcmp((void*)&fstr[xsiz], (void*)&frm, sizeof(_char)))
								{
									for (xsiz++; xsiz < strsiz; xsiz++)
									{
										formspec.push_back(fstr[xsiz]);
										nsiz++;

										if (!memcmp((void*)&fstr[xsiz], (void*)&frm, sizeof(_char)))
										{
											locs.push_back(siz);
											fspecs.push_back(formspec);
											xsiz = strsiz;
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
							memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
							return -2;
						}
						break;
					}
					default:
					{
						memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
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
		size_t siz = 0;
		size_t at_inchr = 0;
		va_list args;
		va_start(args, fstr);

		for (siz = 0; siz < fspecs.size() && at_inchr < in_siz; siz++)
		{
			size_t hlong = 0;
			size_t sloc = 0;

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
				size_t nsiz = 1;

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(spec)))
				{
					_char fchr[3]{ 0 };
					nsiz++;
					size_t fsiz = 0;

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
								memcpy((void*)&inchr[0], (void*)&term, sizeof(_char));
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
							memcpy((void*)&fchr[fsiz], (void*)&fspecs[siz][nsiz], sizeof(_char));
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							memcpy((void*)&fchr[fsiz], (void*)&term, sizeof(_char));
							break;
						}
						}

						if (fsiz == 3)
						{
							memcpy((void*)&fchr[fsiz - 1], (void*)&term, sizeof(_char));
						}
						else
						{
							if (!memcmp((void*)&fchr[fsiz], (void*)&term, sizeof(_char)))
							{
								fsiz = 3;
							}
						}
					}
					if (!memcmp((void*)&fchr[2], (void*)&term, sizeof(_char)) || !memcmp((void*)&fchr[1], (void*)&term, sizeof(_char)) || !memcmp((void*)&fchr[0], (void*)&term, sizeof(_char)))
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (!memcmp((void*)&fspecs[siz][nsiz], (void*)&lenchr, sizeof(_char)))
				{
					hlong++;
					nsiz++;
				}

				_char zchar = '0';
				_char zweichar = '2';

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&zchar, sizeof(_char)) && nsiz < fspecs[siz].length())
				{
					if (!memcmp((void*)&fspecs[siz][nsiz + 1], (void*)&zweichar, sizeof(_char)))
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
					const size_t usiz = (sizeof(u_char) * 2) + 1;

					if (usiz <= in_siz)
					{
						_char ci[usiz]{ 0 };
						sint xc = snprintf(ci, usiz, fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, usiz);

						for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
						{
							memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
							at_inchr++;
						}
					}
					break;
				}
				case 'v':
				{
					nsiz++;
					carr_21 pspc;
					carr_21 fspc;
					carr_21 spc;
					size_t nct = 0;

					while (nsiz < fspecs[siz].length() && nct < pspc.siz)
					{
						if (nsiz < fspecs[siz].length())
						{
							switch (fspecs[siz][nsiz])
							{
							case '%':
							{
								nct = pspc.siz;
								memcpy((void*)&fspc.carr[0], (void*)&fspecs[siz][nsiz], sizeof(_char));
								break;
							}
							default:
							{
								memcpy((void*)&pspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								break;
							}
							}
						}
						nct++;
						nsiz++;
					}

					nct = 1;

					while (nsiz < fspecs[siz].length() && nct < fspc.siz)
					{
						if (nsiz < fspecs[siz].length())
						{
							switch (fspecs[siz][nsiz])
							{
							case '%':
							{
								nct = fspc.siz;
								break;
							}
							case 'c':
							case 's':
							case 'd':
							case 'i':
							case 'u':
							case 'f':
							case 'X':
							{
								memcpy((void*)&fspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								nct = fspc.siz;
								break;
							}
							default:
							{
								memcpy((void*)&fspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								nct++;
								break;
							}
							}
						}
						nsiz++;
					}

					if (nsiz < fspecs[siz].length() - 1)
					{
						for (size_t x = 0; x < spc.siz && nsiz < fspecs[siz].length() - 1; x++)
						{
							if (memcmp((void*)&fspecs[siz][nsiz], (void*)&frm, sizeof(_char)))
							{
								memcpy((void*)&spc.carr[x], (void*)&fspecs[siz][nsiz], sizeof(_char));
							}
							else
							{
								nsiz = fspecs[siz].length();
							}
							nsiz++;
						}
					}

					size_t flen = bot_strlen(fspc.carr);

					if (flen)
					{
						flen--;
						size_t plen = bot_strlen(pspc.carr);
						size_t slen = bot_strlen(spc.carr);

						switch (fspc.carr[flen])
						{
						case 'c':
						{
							std::vector<_char>* inv = va_arg(args, std::vector<_char>*);

							for (size_t x = 0; x < inv->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
								if (at_inchr < in_siz)
								{
									memcpy((void*)&inchr[at_inchr], (void*)&inv->at(x), sizeof(_char));
									at_inchr++;
								}
								if (slen && x < (inv->size() - 1))
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
							}
							break;
						}
						case 's':
						{
							/*when specifying %v%<type><sep>% <type> = 's' we use a vector of std::string instead of a vector of c_char* */
							std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

							for (size_t x = 0; x < strv->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
								for (sloc = 0; sloc < strv->at(x).length() && at_inchr < in_siz; sloc++)
								{
									memcpy((void*)&inchr[at_inchr], (void*)&strv->at(x)[sloc], sizeof(strv->at(x)[sloc]));
									at_inchr++;
								}
								if (slen && x < (strv->size() - 1))
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
							}
							break;
						}
						case 'f':
						{
							std::vector<float>* fvec = va_arg(args, std::vector<float>*);

							for (size_t x = 0; x < fvec->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}
								_char ci[64]{ 0 };
								sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
								xc = bot_strchk(ci, 64);

								for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
								{
									memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
									at_inchr++;
								}
								if (slen && x < (fvec->size() - 1))
								{
									for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[64]{ 0 };
									sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 64);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<long double>* fvec = va_arg(args, std::vector<long double>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[64]{ 0 };
									sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 64);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<slint>* fvec = va_arg(args, std::vector<slint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 2)
							{
								std::vector<sllint>* fvec = va_arg(args, std::vector<sllint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<ulint>* fvec = va_arg(args, std::vector<ulint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
								}
							}
							else if (hlong == 2)
							{
								std::vector<ullint>* fvec = va_arg(args, std::vector<ullint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
											at_inchr++;
										}
									}
									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);

									for (sloc = 0; (sint)sloc < xc && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(ci[sloc]));
										at_inchr++;
									}
									if (slen && x < (fvec->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
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

							for (size_t x = 0; x < inv->size(); x++)
							{
								if (plen)
								{
									for (sloc = 0; sloc < plen && at_inchr < in_siz; sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&pspc.carr[sloc], sizeof(_char));
										at_inchr++;
									}
								}

								const size_t usiz = (sizeof(u_char) * 2) + 1;

								if (usiz + at_inchr <= in_siz)
								{
									_char ci[usiz]{ 0 };
									sint xc = snprintf(ci, usiz, fspc.carr, (uint)inv->at(x));
									xc = bot_strchk(ci, usiz);

									for (sloc = 0; ((sint)sloc < xc && at_inchr < in_siz); sloc++)
									{
										memcpy((void*)&inchr[at_inchr], (void*)&ci[sloc], sizeof(_char));
										at_inchr++;
									}
									if (slen && x < (inv->size() - 1))
									{
										for (sloc = 0; sloc < slen && at_inchr < in_siz; sloc++)
										{
											memcpy((void*)&inchr[at_inchr], (void*)&spc.carr[sloc], sizeof(_char));
											at_inchr++;
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
			memcpy((void*)&inchr[at_inchr], (void*)&term, sizeof(_char));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(_char));
		}
	}
	else
	{
		size_t siz = 0;

		while (siz < in_siz && siz < strsiz)
		{
			memcpy((void*)&inchr[siz], (void*)&fstr[siz], sizeof(_char));
			siz++;
		}
		if (siz < in_siz)
		{
			memcpy((void*)&inchr[siz], (void*)&term, sizeof(_char));
			ret = 0;
		}
		else
		{
			memcpy((void*)&inchr[in_siz - 1], (void*)&term, sizeof(_char));
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

	size_t strsiz = strlen(fstr);
	std::vector<std::string> fspecs;
	std::vector<size_t> locs;
	std::string formspec;
	_char frm = '%';
	_char spec = '.';
	_char term = '\0';

	for (size_t siz = 0; siz < strsiz; siz++)
	{
		if (!memcmp((void*)&fstr[siz], (void*)&frm, sizeof(_char)))
		{
			formspec.push_back(fstr[siz]);
			bool mustnum = false;

			for (size_t nsiz = 1; siz + nsiz < strsiz; )
			{
				if (!memcmp((void*)&fstr[siz + nsiz], (void*)&spec, sizeof(_char)))
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
							formspec.push_back(fstr[siz + nsiz]);
							nsiz++;

							for (size_t xsiz = siz + nsiz; xsiz < strsiz; xsiz++)
							{
								formspec.push_back(fstr[xsiz]);
								nsiz++;

								if (!memcmp((void*)&fstr[xsiz], (void*)&frm, sizeof(_char)))
								{
									for (xsiz++; xsiz < strsiz; xsiz++)
									{
										formspec.push_back(fstr[xsiz]);
										nsiz++;

										if (!memcmp((void*)&fstr[xsiz], (void*)&frm, sizeof(_char)))
										{
											locs.push_back(siz);
											fspecs.push_back(formspec);
											xsiz = strsiz;
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
		size_t siz = 0;
		va_list args;
		va_start(args, fstr);

		for (siz = 0; siz < fspecs.size(); siz++)
		{
			size_t hlong = 0;
			size_t sloc = 0;

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
				size_t nsiz = 1;

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&spec, sizeof(_char)))
				{
					_char fchr[3]{ 0 };
					nsiz++;
					size_t fsiz = 0;

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
							memcpy((void*)&fchr[fsiz], (void*)&fspecs[siz][nsiz], sizeof(_char));
							nsiz++;
							fsiz++;
							break;
						}
						default:
						{
							memcpy((void*)&fchr[fsiz], (void*)&term, sizeof(_char));
							break;
						}
						}

						if (fsiz == 3)
						{
							memcpy((void*)&fchr[fsiz - 1], (void*)&term, sizeof(_char));
						}
						else
						{
							if (!memcmp((void*)&fchr[fsiz], (void*)&term, sizeof(_char)))
							{
								fsiz = 3;
							}
						}
					}
					if (!memcmp((void*)&fchr[2], (void*)&term, sizeof(_char)) || !memcmp((void*)&fchr[1], (void*)&term, sizeof(_char)) || !memcmp((void*)&fchr[0], (void*)&term, sizeof(_char)))
					{
						isiz = atoi(fchr);
					}
					if (isiz > 20)
					{
						va_end(args);
						return -4;
					}
				}

				while (!memcmp((void*)&fspecs[siz][nsiz], (void*)&lenchr, sizeof(_char)))
				{
					hlong++;
					nsiz++;
				}

				_char zchar = '0';
				_char zweichar = '2';

				if (!memcmp((void*)&fspecs[siz][nsiz], (void*)&zchar, sizeof(_char)) && nsiz < fspecs[siz].length())
				{
					if (!memcmp((void*)&fspecs[siz][nsiz + 1], (void*)&zweichar, sizeof(_char)))
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

					if ((str_->length() + strlen(ci)) < (size_t)BOT_STRLEN_MAX)
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

					if ((str_->length() + strlen(ci)) < (size_t)BOT_STRLEN_MAX)
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

					if ((str_->length() + strlen(ci)) < (size_t)BOT_STRLEN_MAX)
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

					if ((str_->length() + strlen(ci)) < (size_t)BOT_STRLEN_MAX)
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

					for (sloc = 0; (sloc + str_->length()) < (size_t)BOT_STRLEN_MAX; sloc++)
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

					if ((usiz + str_->length()) <= (size_t)BOT_STRLEN_MAX)
					{
						_char ci[usiz]{ 0 };
						sint xc = snprintf(ci, usiz, fspecs[siz].c_str(), (uint)inv_);
						xc = bot_strchk(ci, usiz);
						str_->append(ci);
					}
					break;
				}
				case 'v':
				{
					nsiz++;
					carr_21 pspc;
					carr_21 fspc;
					carr_21 spc;
					size_t nct = 0;

					while (nsiz < fspecs[siz].length() && nct < pspc.siz)
					{
						if (nsiz < fspecs[siz].length())
						{
							switch (fspecs[siz][nsiz])
							{
							case '%':
							{
								nct = pspc.siz;
								memcpy((void*)&fspc.carr[0], (void*)&fspecs[siz][nsiz], sizeof(_char));
								break;
							}
							default:
							{
								memcpy((void*)&pspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								break;
							}
							}
						}
						nct++;
						nsiz++;
					}

					nct = 1;

					while (nsiz < fspecs[siz].length() && nct < fspc.siz)
					{
						if (nsiz < fspecs[siz].length())
						{
							switch (fspecs[siz][nsiz])
							{
							case '%':
							{
								nct = fspc.siz;
								break;
							}
							case 'c':
							case 's':
							case 'd':
							case 'i':
							case 'u':
							case 'f':
							case 'X':
							{
								memcpy((void*)&fspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								nct = fspc.siz;
								break;
							}
							default:
							{
								memcpy((void*)&fspc.carr[nct], (void*)&fspecs[siz][nsiz], sizeof(_char));
								nct++;
								break;
							}
							}
						}
						nsiz++;
					}

					if (nsiz < fspecs[siz].length() - 1)
					{
						for (size_t x = 0; x < spc.siz && nsiz < fspecs[siz].length() - 1; x++)
						{
							if (memcmp((void*)&fspecs[siz][nsiz], (void*)&frm, sizeof(_char)))
							{
								memcpy((void*)&spc.carr[x], (void*)&fspecs[siz][nsiz], sizeof(_char));
							}
							else
							{
								nsiz = fspecs[siz].length();
							}
							nsiz++;
						}
					}

					size_t flen = bot_strlen(fspc.carr);

					if (flen)
					{
						flen--;
						size_t plen = bot_strlen(pspc.carr);
						size_t slen = bot_strlen(spc.carr);

						switch (fspc.carr[flen])
						{
						case 'c':
						{
							std::vector<_char>* inv = va_arg(args, std::vector<_char>*);

							for (size_t x = 0; x < inv->size() && str_->length() < (size_t)BOT_STRLEN_MAX; x++)
							{
								if (plen)
								{
									str_->append(pspc.carr);
								}

								str_->push_back(inv->at(x));

								if (slen && x < (inv->size() - 1))
								{
									str_->append(spc.carr);
								}
							}
							break;
						}
						case 's':
						{
							/*when specifying %v%<type><sep>% <type> = 's' we use a vector of std::string instead of a vector of c_char* */
							std::vector<std::string>* strv = va_arg(args, std::vector<std::string>*);

							for (size_t x = 0; x < strv->size() && str_->length() < (size_t)BOT_STRLEN_MAX; x++)
							{
								if (plen)
								{
									str_->append(pspc.carr);
								}

								str_->append(strv->at(x).c_str());

								if (slen && x < (strv->size() - 1))
								{
									str_->append(spc.carr);
								}
							}
							break;
						}
						case 'f':
						{
							std::vector<float>* fvec = va_arg(args, std::vector<float>*);

							for (size_t x = 0; x < fvec->size(); x++)
							{
								if (plen)
								{
									str_->append(pspc.carr);
								}

								_char ci[64]{ 0 };
								sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
								xc = bot_strchk(ci, 64);

								str_->append(ci);

								if (slen && x < (fvec->size() - 1))
								{
									str_->append(spc.carr);
								}
							}
							break;
						}
						case 'd':
						{
							if (!hlong)
							{
								std::vector<double>* fvec = va_arg(args, std::vector<double>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[64]{ 0 };
									sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 64);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<long double>* fvec = va_arg(args, std::vector<long double>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[64]{ 0 };
									sint xc = snprintf(ci, 64, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 64);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<slint>* fvec = va_arg(args, std::vector<slint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
									}
								}
							}
							else if (hlong == 2)
							{
								std::vector<sllint>* fvec = va_arg(args, std::vector<sllint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
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

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
									}
								}
							}
							else if (hlong == 1)
							{
								std::vector<ulint>* fvec = va_arg(args, std::vector<ulint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
									}
								}
							}
							else if (hlong == 2)
							{
								std::vector<ullint>* fvec = va_arg(args, std::vector<ullint>*);

								for (size_t x = 0; x < fvec->size(); x++)
								{
									if (plen)
									{
										str_->append(pspc.carr);
									}

									_char ci[21]{ 0 };
									sint xc = snprintf(ci, 21, fspc.carr, fvec->at(x));
									xc = bot_strchk(ci, 21);
									str_->append(ci);

									if (slen && x < (fvec->size() - 1))
									{
										str_->append(spc.carr);
									}
								}
							}
							else {}
							break;
						}
						case 'X':
						{
							std::vector<u_char>* inv = va_arg(args, std::vector<u_char>*);

							for (size_t x = 0; x < inv->size(); x++)
							{
								if (plen)
								{
									str_->append(pspc.carr);
								}

								const size_t usiz = (sizeof(u_char) * 16) + 1;

								if (usiz + str_->length() < (size_t)BOT_STRLEN_MAX)
								{
									_char ci[usiz]{ 0 };
									sint xc = snprintf(ci, usiz, fspc.carr, (uint)inv->at(x));
									xc = bot_strchk(ci, usiz);
									str_->append(ci);

									if (slen && x < (inv->size() - 1))
									{
										str_->append(spc.carr);
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
		if (strsiz < (size_t)BOT_STRLEN_MAX)
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

sllint bot_findin(_char val[], size_t offs, size_t lim, _char inv[])
{
	if (!inv || !val || offs < 0)
	{
		return -1;
	}

	size_t ilen = bot_strlen(inv);
	size_t vlen = bot_strlen(val);

	if (ilen < vlen || offs > ilen)
	{
		return -1;
	};

	if (lim && ilen > lim)
	{
		ilen = lim;
	}

	size_t x = 0;

	for (x = offs; x < ilen; x++)
	{
		_char n = '\0';
		size_t y = 0;

		if (!memcmp((void*)&val[y], (void*)&inv[x], sizeof(_char)))
		{
			y++;

			while (y < vlen)
			{
				if (memcmp((void*)&val[y], (void*)&inv[x + y], sizeof(_char)))
				{
					y = vlen;
				}
				y++;
			}

			if (y == vlen)
			{
				return sllint(x);
			}
		}
	}
	return -1;
}

sllint bot_findin(_char val[], size_t offs, size_t lim, c_char* inv)
{
	if (!inv || !val || offs < 0)
	{
		return -1;
	}

	size_t ilen = bot_cstrlen(inv);
	size_t vlen = bot_strlen(val);

	if (ilen < vlen || offs > ilen)
	{
		return -1;
	};

	if (lim && ilen > lim)
	{
		ilen = lim;
	}

	size_t x = 0;

	for (x = offs; x < ilen; x++)
	{
		_char n = '\0';
		size_t y = 0;

		if (!memcmp((void*)&val[y], (void*)&inv[x], sizeof(_char)))
		{
			y++;

			while (y < vlen)
			{
				if (memcmp((void*)&val[y], (void*)&inv[x + y], sizeof(_char)))
				{
					y = vlen;
				}
				y++;
			}

			if (y == vlen)
			{
				return sllint(x);
			}
		}
	}
	return -1;
}

sllint bot_findin(u_char val[], size_t offs, size_t lim, u_char inv[])
{
	if (!inv || !val || offs < 0)
	{
		return -1;
	}

	size_t ilen = bot_ustrlen(inv);
	size_t vlen = bot_ustrlen(val);

	if (ilen < vlen || offs > ilen)
	{
		return -1;
	};

	if (lim && ilen > lim)
	{
		ilen = lim;
	}

	size_t x = 0;

	for (x = offs; x < ilen; x++)
	{
		u_char n = (u_char)'\0';
		size_t y = 0;

		if (!memcmp((void*)&val[y], (void*)&inv[x], sizeof(u_char)))
		{
			y++;

			while (y < vlen)
			{
				if (memcmp((void*)&val[y], (void*)&inv[x + y], sizeof(u_char)))
				{
					y = vlen;
				}
				y++;
			}

			if (y == vlen)
			{
				return sllint(x);
			}
		}
	}
	return -1;
}

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
		rc = Output(outp.carr, 2, false);
	}
	if (!ncar_)
	{
		return -1;
	}

	sint xc = SetDBG(debug_lvl, debug_m);

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
	
	}*/

	xc = BOTFindHomeDir();

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

	xc = MT();

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
		sllint rst = nsRest((sllint)BOT_REQREST, true);
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
							xp = Output(ncar.carr, 1);
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
	if (debug_lvl >= 900 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::HasLock(sint g_opt(%i), sint ele(%i), bool is_meta(%u))", g_opt, ele, (uint)is_meta);
		op = Output(outp.carr, 2);
	}
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
					sllint rst = nsRest((sllint)BOT_LOCKREST);
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
		sint op = bot_sprintf(outp.carr, outp.siz, "::UnlockGMutex(sint g_opt(%i))", g_opt);
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
		sint op = bot_sprintf(outp.carr, outp.siz, "::LockElement(sint g_opt(%i), sint ele(%i), sint* had_lock(%i), bool sleep_wait(%u), bool is_meta(%u))", g_opt, ele, (sint)had_lock, (uint)sleep_wait, (uint)is_meta);
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
					sllint rst = nsRest((sllint)BOT_LOCKREST);
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
		sint op = bot_sprintf(outp.carr, outp.siz, "::UnlockElement(sint g_opt(%i), sint ele(%i), bool is_meta(%u))", g_opt, ele, (uint)is_meta);
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
	if (debug_lvl >= 900 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::OpenObject(sint nobj(%i), sint nele(%i), sint is_meta(%i), sint* omode(%i), sint* r_opt(%i), sint* n_opt(%i))", nobj, nele, (uint)is_meta, (sint)omode, (sint)r_opt, (sint)n_opt);
		op = Output(outp.carr, 2);
	}
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
	if (debug_lvl >= 900 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::CloseObject(sint nobj(%i), sint nele(%i), sint is_meta(%i), sint* r_opt(%i), sint* n_opt(%i))", nobj, nele, is_meta, (sint)r_opt, (sint)n_opt);
		op = Output(outp.carr, 2);
	}
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
					fileo_vec.d_vec[ele].FreeDat();
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
	struct tm tms;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	tms = *gmtime(&tstamp);

	if (forms)
	{
		xc = bot_sprintf(str_, 64, "%.2u : %.2u : %.2u : %.3u", (uint)tms.tm_hour, (uint)tms.tm_min, (uint)tms.tm_sec, (uint)ti.tv_nsec);
	}
	else
	{
		xc = bot_sprintf(str_, 64, "%.2u %.2u %.2u %.3u", (uint)tms.tm_hour, (uint)tms.tm_min, (uint)tms.tm_sec, (uint)ti.tv_nsec);
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

sint machine::SetDBG(sint lv, sint m)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_72 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::SetDBG(sint lv(%i), sint m(%i))", lv, m);
		op = Output(outp.carr, 2);
	}
	if (lv < 0 && m < 0)
	{
		return -1;
	}
	sint ox = -1;
	sint hx = LockGMutex(MTX_DBG, &ox);

	if (hx > -1)
	{
		if (lv > -1)
		{
			bot_dbg_l = lv;
		}

		if (m > -1)
		{
			bot_dbg_m = m;
		}

		if (!ox)
		{
			ox = UnlockGMutex(MTX_DBG);
		}
	}
	hx = GetDBG(&debug_lvl, &debug_m);
	return hx;
}
sint machine::GetDBG(sint* lv, sint* m)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_72 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetDBG(sint lv(%i), sint m(%i))", (sint)lv, (sint)m);
		op = Output(outp.carr, 2);
	}
	if (!lv && !m)
	{
		return -1;
	}
	sint ox = -1;
	sint hx = LockGMutex(MTX_DBG, &ox);

	if (hx > -1)
	{
		if (lv)
		{
			*lv = bot_dbg_l;
		}

		if (m)
		{
			*m = bot_dbg_m;
		}
		if (!ox)
		{
			ox = UnlockGMutex(MTX_DBG);
		}
	}
	return hx;
}
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
	if (!msg_)
	{
		return -1;
	}
	carr_32 dat;
	sint xc = GetDate(&dat, false);
	char nl = '\n';

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
			if (debug_m > 1)
			{
				for (uint x = 0; x < stk_ct; x++)
				{
					str.append("[Q]");
				}

				str.append(msg_);

				if (memcmp((void*)&str[str.length() - 1], (void*)&nl, sizeof(_char)))
				{
					str.push_back(nl);
				}

				u_logs[uc].log_q.push_back(str);
			}
			return 0;
		}

		str.append(msg_);

		if (memcmp((void*)&str[str.length() - 1], (void*)&nl, sizeof(_char)))
		{
			str.push_back(nl);
		}

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
			if (debug_m > 1)
			{
				for (uint x = 0; x < stk_ct; x++)
				{
					str.append("[Q]");
				}
				str.append(msg_);

				if (memcmp((void*)&str[str.length() - 1], (void*)&nl, sizeof(_char)))
				{
					str.push_back(nl);
				}

				u_logs[uc].log_q.push_back(str);
			}
			return 0;
		}

		str.append(msg_);

		if (memcmp((void*)&str[str.length() - 1], (void*)&nl, sizeof(_char)))
		{
			str.push_back(nl);
		}

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
	return 0;
}

// Commands
sint machine::Command(std::vector<BOT_ARG>* vec_)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::Command(std::vector<BOT_ARG>* vec_(%i))", (sint)vec_);
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

	BOTCOMMAND Command(UCASE(vec_->at(0).arg.c_str()).c_str());

	if (!strcmp(Command.cmd.substr(0, 2).c_str(), "/#"))
	{
		std::string inv(Command.cmd.substr(2, vec_->at(0).arg.length() - 2).c_str());
		Command.cmd.clear();
		Command.cmd.append(inv.c_str());
	}
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
		if (debug_lvl >= 100 && debug_m)
		{
			sint oc = Output("Telling threads to finish", 2);
		}
		sint oc = SetThreadQuit(1);
		break;
	}
	case 2:
	{
		if (vec_->size() > 2)
		{
			if (strlen(vec_->at(1).arg.c_str()))
			{
				BOT_CLIENT ProcClient;
				ProcClient.login_name.append(UCASE(vec_->at(1).arg.c_str()).c_str());
				sint rc = SetPCliMem(BOT_C_LOGIN_NAME, (void*)ProcClient.login_name.c_str());
				rc = GetLogin(vec_->at(2).arg.c_str());

				if (GetClientLoggedIn())
				{
					rc = GetPCli(&ProcClient);
					ProcClient.updatelogin = true;
					rc = UpdateAccount(&ProcClient);
					ProcClient.updatelogin = false;
					rc = PushToVec((void*)&ProcClient, MTX_CV, true, true, false);
				}
				else
				{
					rc = Output(true, "login failed", 2, 0);
					rc = GetPCli(&ProcClient);
					ProcClient.updatelogin = true;
					rc = UpdateAccount(&ProcClient);
				}
			}
			xc = 0;
		}
		break;
	}
	case 3:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 3", 2);
		}
		std::vector<BOTCOMMAND> vec;
		xc = GetCommands(&vec);

		if (vec_->size() == 1)
		{
			for (uint x = 0; x < vec.size(); x++)
			{
				carr_128 ncar;
				sint oc = bot_sprintf(ncar.carr, ncar.siz, "%i %s", vec[x].cmd_id, vec[x].cmd.c_str());
				oc = Output(true, ncar.carr, 2, 0);
			}
		}
		else
		{
			for (uint y = 1; y < vec_->size() && y < 21; y++)
			{
				std::string astr, bstr;
				bool sisn = bot_sisn(vec_->at(y).arg.c_str(), (sint)vec_->at(y).arg.length());
				
				if (sisn)
				{
					astr.append(vec_->at(y).arg.c_str());
				}
				else
				{
					astr.append(UCASE(vec_->at(y).arg.c_str()).c_str());
				}
				
				for (uint x = 0; x < vec.size(); x++)
				{
					bstr.clear();

					if (sisn)
					{
						carr_21 ncar;
						sint oc = bot_sprintf(ncar.carr, ncar.siz, "%i", vec[x].cmd_id);
						bstr.append(ncar.carr);
					}
					else
					{
						bstr.append(UCASE(vec[x].cmd.c_str()).c_str());
					}

					if (!strcmp(astr.c_str(), bstr.c_str()))
					{
						carr_1024 xcar;
						carr_128 ncar;
						sint oc = bot_sprintf(ncar.carr, ncar.siz, "%i %s", vec[x].cmd_id, vec[x].cmd.c_str());

						switch (vec[x].cmd_id)
						{
						case 1:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nquit program.", ncar.carr);
							break;
						}
						case 2:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\na: login name" \
								"\nb: password" \
								"\nSpace separated login", ncar.carr);
							break;
						}
						case 3:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nusage: /#help [a] ..." \
								"\n(optional)a: command name or id - If is a number find command by id, else find command by name, and print command help message." \
								"\nIf no args list commands" , ncar.carr);
							break;
						}
						case 4:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nLogout current user", ncar.carr);
							break;
						}
						case 5:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n(optional)a: new level 0-UINT_MAX - If arg(a) set the current level. debug_level restricts debug messages by 'approximate' level within code where more basic functions debug messages are a higher level." \
								"\n(optional)b: new mode 0-UINT_MAX - If arg(b) set the current mode 0: no debug output, 1: output debug to logs only, 2: output debug to console and logs" \
								"\nIf 0 args: show current level and mode", ncar.carr);
							break;
						}
						case 6:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: type" \
								"\n2: name" \
								"\n(optional)3: value" \
								"\nInitialize a variable of type: INT, REAL, TEXT, BLOB", ncar.carr);
							break;
						}
						case 7:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: name" \
								"\nShow variable", ncar.carr);
							break;
						}
						case 96:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "!DISABLED!%s\nusage: /#readfile [a]", ncar.carr);
							break;
						}
						case 98:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\na: mode" \
								"\nb: encoding" \
								"\nc: name" \
								"\nd: type" \
								"\ne: file destination" \
								"\nAdd a script at file destination to the db", ncar.carr);
							break;
						}
						case 99:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\na: script name or id" \
								"\nAttempt to run script with a call to system(c_char*)", ncar.carr);
							break;
						}
						case 100:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nGet host i.p. addresses", ncar.carr);
							break;
						}
						case 1000:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\na: command name" \
								"\nb: privlege level 0-UINT_MAX" \
								"\nAdd a command to the db", ncar.carr);
							break;
						}
						case 1001:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\na: command name" \
								"\nRemove a command from the db", ncar.carr);
							break;
						}
						default:
						{
							break;
						}
						}
						if (xcar.carr[0] != '\0')
						{
							oc = Output(true, xcar.carr, 2, 0);
						}
					}
				}
			}
		}
		break;
	}
	case 4:
	{
		if (GetClientLoggedIn())
		{
			sint rc = GetPCliMem(BOT_C_ID, &xc);
			rc = ClearVecEle(MTX_CV, xc, false);
			BOT_CLIENT ProcClient;
			rc = SetPCli(&ProcClient);
		}
		xc = 0;
		break;
	}
	case 5:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 5", 2);
		}

		xc = -1;

		if (vec_->size() == 1)
		{
			xc = GetDBG(&debug_lvl, &debug_m);;
			carr_128 ncar;
			xc = bot_sprintf(ncar.carr, ncar.siz, "debug level:%i debug mode:%i", debug_lvl, debug_m);
			xc = Output(true, ncar.carr, 2, 0);
		}
		else if (vec_->size() == 2)
		{
			if (bot_sisn(vec_->at(1).arg.c_str(), (sint)vec_->at(1).arg.length()))
			{
				xc = SetDBG(atoi(vec_->at(1).arg.c_str()), -1);
			}
			else if (!strcmp(&vec_->at(1).arg[0], "l"))
			{
				xc = GetDBG(&debug_lvl, &debug_m);;
				carr_64 ncar;
				xc = bot_sprintf(ncar.carr, ncar.siz, "debug level:%i", debug_lvl);
				xc = Output(true, ncar.carr, 2, 0);
			}
			else if (!strcmp(&vec_->at(1).arg[0], "m"))
			{
				xc = GetDBG(&debug_lvl, &debug_m);;
				carr_64 ncar;
				xc = bot_sprintf(ncar.carr, ncar.siz, "debug mode:%i", debug_m);
				xc = Output(true, ncar.carr, 2, 0);
			}
			else {}
		}
		else if (vec_->size() == 3)
		{
			if (!strcmp(&vec_->at(1).arg[0], "l") && bot_sisn(vec_->at(2).arg.c_str(), (sint)vec_->at(2).arg.length()))
			{
				xc = SetDBG(atoi(vec_->at(2).arg.c_str()), -1);
			}
			else if (!strcmp(&vec_->at(1).arg[0], "m") && bot_sisn(vec_->at(2).arg.c_str(), (sint)vec_->at(2).arg.length()))
			{
				xc = SetDBG(-1, atoi(vec_->at(2).arg.c_str()));
			}
			else if (bot_sisn(vec_->at(1).arg.c_str(), (sint)vec_->at(1).arg.length()) && bot_sisn(vec_->at(2).arg.c_str(), (sint)vec_->at(2).arg.length()))
			{
				xc = SetDBG(atoi(vec_->at(1).arg.c_str()), atoi(vec_->at(2).arg.c_str()));
			}
			else {}
		}
		else
		{
			carr_512 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n(optional)a: if num: new level 0-UINT_MAX else 'level'/'mode'" \
				"\n(optional)b: if arg(a) is num and arg(b) is num: new mode 0-UINT_MAX else set value for arg(a)" \
				"\nIf args: \ndebug_level restricts debug messages by 'approximate' level within code where more basic functions debug messages are a higher level.\nmode 0: no debug output, 1: debug output to logs only, 2: debug output to console and logs" \
				"\nIf 0 args: show current level and mode");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 6:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 6", 2);
		}
		if (vec_->size() > 2)
		{
			if (vec_->at(1).arg.length() > 512)
			{
				return -1;
			}
			if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "INT"))
			{
				if (vec_->size() > 3)
				{
					sllint var = (sllint)_atoi64(vec_->at(3).arg.c_str());
					xc = mv.AddVar(vec_->at(2).arg.c_str(), &var, BOT_RTV_SLLINT, BOT_RTV_SLLINT);
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_SLLINT, BOT_RTV_SLLINT);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "REAL"))
			{
				if (vec_->size() > 3)
				{
					float var = (float)atof(vec_->at(3).arg.c_str());
					xc = mv.AddVar(vec_->at(2).arg.c_str(), &var, BOT_RTV_REAL, BOT_RTV_REAL);
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_REAL, BOT_RTV_REAL);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "TEXT"))
			{
				if (vec_->size() > 3)
				{
					std::string var(vec_->at(3).arg.c_str());
					xc = mv.AddVar(vec_->at(2).arg.c_str(), &var, BOT_RTV_STR, BOT_RTV_STR);
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_STR, BOT_RTV_STR);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "BLOB"))
			{
				if (vec_->size() > 3)
				{
					_char* var = (_char*)malloc(vec_->at(3).arg.length() + 1);

					if (var)
					{
						_char trm = '\0';
						memcpy((void*)var, (void*)vec_->at(3).arg.c_str(), vec_->at(3).arg.length());
						memcpy((void*)&var[vec_->at(3).arg.length()], (void*)&trm, sizeof(_char));
						xc = mv.AddVar(vec_->at(2).arg.c_str(), var, BOT_RTV_BLOB, BOT_RTV_BLOB);
						free(var);
					}
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_BLOB, BOT_RTV_BLOB);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "VINT"))
			{
				if (vec_->size() > 3)
				{
					std::vector<sllint> var;
					std::vector<BOT_ARG> args;
					std::vector<std::string> seps;
					xc = vtool.CombV(&seps, VTV_VSTR, VTV_VCHAR, &msy.nrts_sep, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_, VTV_MAX);

					for (size_t z = 3; z < vec_->size(); z++)
					{
						if (bot_sisn(vec_->at(z).arg.c_str(), vec_->at(z).arg.length()))
						{
							var.push_back((sllint)_atoi64(vec_->at(z).arg.c_str()));
						}
						else
						{
							xc = ArgSep(&args, false, 0, vec_->at(z).arg.length(), vec_->at(z).arg.c_str(), BOT_RTV_VSTR, &seps);

							if (xc > -1)
							{
								for (size_t w = 0; w < args.size(); w++)
								{
									var.push_back((sllint)_atoi64(args[w].arg.c_str()));
								}
							}
							args.clear();
						}
					}
					xc = mv.AddVar(vec_->at(2).arg.c_str(), &var, BOT_RTV_VSLLINT, BOT_RTV_VSLLINT);
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_VSLLINT, BOT_RTV_SLLINT);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "VREAL"))
			{
				if (vec_->size() > 3)
				{
					std::vector<float> var;
					std::vector<BOT_ARG> args;
					std::vector<std::string> seps;
					xc = vtool.CombV(&seps, VTV_VSTR, VTV_VCHAR, &msy.nrts_sep, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_, VTV_MAX);

					for (size_t z = 3; z < vec_->size(); z++)
					{
						if (bot_sisn(vec_->at(z).arg.c_str(), vec_->at(z).arg.length()))
						{
							var.push_back((float)atof(vec_->at(z).arg.c_str()));
						}
						else
						{
							xc = ArgSep(&args, false, 0, vec_->at(z).arg.length(), vec_->at(z).arg.c_str(), BOT_RTV_VSTR, &seps);

							if (xc > -1)
							{
								for (size_t w = 0; w < args.size(); w++)
								{
									var.push_back((float)atof(args[w].arg.c_str()));
								}
							}
							args.clear();
						}
					}
					xc = mv.AddVar(vec_->at(2).arg.c_str(), &var, BOT_RTV_VREAL, BOT_RTV_VREAL);
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_VREAL, BOT_RTV_REAL);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "VTEXT"))
			{
				if (vec_->size() > 3)
				{
					std::vector<BOT_ARG> args;
					std::vector<std::string> seps;
					xc = vtool.CombV(&seps, VTV_VSTR, VTV_VCHAR, &msy.nrts_sep, VTV_VCHAR, &msy.nrts_lit, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_, VTV_MAX);

					for (size_t z = 3; z < vec_->size(); z++)
					{
						xc = ArgSep(&args, false, 0, vec_->at(z).arg.length(), vec_->at(z).arg.c_str(), BOT_RTV_VSTR, &seps);

						if (xc > -1)
						{
							if (args.size() == 1)
							{
								xc = mv.AddVar(vec_->at(2).arg.c_str(), &args[0].arg, BOT_RTV_VSTR, BOT_RTV_STR);
							}
							else
							{
								xc = mv.AddVar(vec_->at(2).arg.c_str(), &args, BOT_RTV_VSTR, BOT_RTV_VARG);
							}
						}
						args.clear();
					}
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_VREAL, BOT_RTV_REAL);
				}
			}
			else if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "VBLOB"))
			{
				if (vec_->size() > 3)
				{
					std::vector<BOT_ARG> args;
					std::vector<std::string> seps;
					xc = vtool.CombV(&seps, VTV_VSTR, VTV_VCHAR, &msy.nrts_sep, VTV_VCHAR, &msy.nrts_lit, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_, VTV_MAX);

					for (size_t z = 3; z < vec_->size(); z++)
					{
						xc = ArgSep(&args, false, 0, vec_->at(z).arg.length(), vec_->at(z).arg.c_str(), BOT_RTV_VSTR, &seps);

						if (xc > -1)
						{
							if (args.size() == 1)
							{
								_char* var = (_char*)malloc(args[0].arg.length() + 1);

								if (var)
								{
									_char trm = '\0';
									memcpy((void*)var, (void*)args[0].arg.c_str(), args[0].arg.length());
									memcpy((void*)&var[args[0].arg.length()], (void*)&trm, sizeof(_char));
									xc = mv.AddVar(vec_->at(2).arg.c_str(), var, BOT_RTV_VBLOB, BOT_RTV_BLOB);
									free(var);
								}
							}
							else
							{
								xc = mv.AddVar(vec_->at(2).arg.c_str(), &args, BOT_RTV_VBLOB, BOT_RTV_VARG);
							}
						}
						args.clear();
					}
				}
				else
				{
					xc = mv.AddVar(vec_->at(2).arg.c_str(), 0, BOT_RTV_VREAL, BOT_RTV_REAL);
				}
			}
			else {}
		}
		else
		{
			carr_168 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: type" \
				"\n2: name" \
				"\n(optional)3: value" \
				"\nInitialize a variable of type: INT, REAL, TEXT, BLOB, VINT, VREAL, VTEXT, VBLOB");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 7:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 7", 2);
		}
		if (vec_->size() > 1)
		{
			xc = mv.FindVar(vec_->at(1).arg.c_str());
			
			if (xc > -1)
			{
				switch (mv.vvars[xc].t)
				{
				case BOT_RTV_SLLINT:
				{
					std::string xcar("INT ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						if (!mv.vvars[xc].v[0].empty())
						{
							_char* nv = (_char*)malloc(sizeof(sllint));

							if (nv)
							{
								for (size_t z = 0; z < sizeof(sllint); z++)
								{
									memcpy((void*)&nv[z], (void*)&mv.vvars[xc].v[0][z], sizeof(_char));
								}

								sllint val;
								memcpy((void*)&val, (void*)nv, sizeof(sllint));
								sint xp = bot_sprintfs(&xcar, false, " = %lli", val);
								free(nv);
							}
						}
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_REAL:
				{
					std::string xcar("REAL ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						if (!mv.vvars[xc].v[0].empty())
						{
							_char* nv = (_char*)malloc(sizeof(float));

							if (nv)
							{
								for (size_t z = 0; z < sizeof(float); z++)
								{
									memcpy((void*)&nv[z], (void*)&mv.vvars[xc].v[0][z], sizeof(_char));
								}

								float val;
								memcpy((void*)&val, (void*)nv, sizeof(float));
								sint xp = bot_sprintfs(&xcar, false, " = %.9f", val);
								free(nv);
							}
						}
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_STR:
				{
					std::string xcar("TEXT ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						if (!mv.vvars[xc].v[0].empty())
						{
							xcar.append(" = ");

							for (size_t z = 0; z < mv.vvars[xc].v[0].size(); z++)
							{
								xcar.push_back(mv.vvars[xc].v[0][z]);
							}
						}
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_BLOB:
				{
					std::string xcar("BLOB ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						if (!mv.vvars[xc].v[0].empty())
						{
							xcar.append(" = ");

							for (size_t z = 0; z < mv.vvars[xc].v[0].size(); z++)
							{
								sint xp = bot_sprintfs(&xcar, false, "0x%02X ", mv.vvars[xc].v[0][z]);
							}
							xcar.pop_back();
						}
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					std::string xcar("VINT ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						_char* np = (_char*)malloc(sizeof(sllint));

						if (np)
						{
							xcar.append("\n{\n\t");

							for (size_t z = 0; z < mv.vvars[xc].v.size(); z++)
							{
								sint xp = bot_sprintfs(&xcar, false, "[%u] ", z);

								for (size_t w = 0; w < mv.vvars[xc].v[z].size(); w++)
								{
									memcpy((void*)&np[w], (void*)&mv.vvars[xc].v[z][w], sizeof(_char));
								}

								sllint val;
								memcpy((void*)&val, (void*)np, sizeof(sllint));
								xp = bot_sprintfs(&xcar, false, "%lli,\n\t", val);
							}
							free(np);
							xcar.pop_back();
							xcar.pop_back();
							xcar.pop_back();
							xcar.append("\n}");
						}
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::string xcar("VREAL ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						xcar.append("\n{\n\t");
						_char* nv = (_char*)malloc(sizeof(float));

						if (nv)
						{
							for (size_t z = 0; z < mv.vvars[xc].v.size(); z++)
							{
								sint xp = bot_sprintfs(&xcar, false, "[%u] ", z);

								for (size_t w = 0; w < sizeof(float); w++)
								{
									memcpy((void*)&nv[w], (void*)&mv.vvars[xc].v[z][w], sizeof(_char));
								}
								float val;
								memcpy((void*)&val, (void*)nv, sizeof(float));
								xp = bot_sprintfs(&xcar, false, "%.9f,\n\t", val);
							}
							free(nv);
							xcar.pop_back();
							xcar.pop_back();
							xcar.pop_back();
							xcar.append("\n}");
						}
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::string xcar("VTEXT ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						xcar.append("\n{\n\t");
						for (size_t z = 0; z < mv.vvars[xc].v.size(); z++)
						{
							sint xp = bot_sprintfs(&xcar, false, "[%u] ", z);

							for (size_t w = 0; w < mv.vvars[xc].v[z].size(); w++)
							{
								xcar.push_back(mv.vvars[xc].v[z][w]);
							}
							xcar.append(",\n\t");
						}
						xcar.pop_back();
						xcar.pop_back();
						xcar.pop_back();
						xcar.append("\n}");
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::string xcar("VBLOB ");
					xcar.append(mv.vvars[xc].n);

					if (!mv.vvars[xc].v.empty())
					{
						xcar.append("\n{\n\t");
						for (size_t z = 0; z < mv.vvars[xc].v.size(); z++)
						{
							sint xp = bot_sprintfs(&xcar, false, "[%u] %v0x%02X %,\n\t", z, &mv.vvars[xc].v[z]);
						}
						xcar.pop_back();
						xcar.pop_back();
						xcar.pop_back();
						xcar.append("\n}");
					}
					sint xp = Output(true, xcar.c_str(), 2, 0);
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		else
		{
			carr_24 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: name" \
				"\nShow variable");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 8:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 8", 2);
		}
		if (!vec_->empty())
		{
			for (size_t x = 0; x < mv.vvars.size(); x++)
			{
				std::string str;

				switch (mv.vvars[x].t)
				{
				case BOT_RTV_SLLINT:
				{
					str.append("INT ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}
					if (!mv.vvars[x].v.empty())
					{
						_char* nv = (_char*)malloc(sizeof(sllint));

						if (nv)
						{
							for (size_t z = 0; z < sizeof(sllint); z++)
							{
								memcpy((void*)&nv[z], (void*)&mv.vvars[x].v[0][z], sizeof(_char));
							}
							sllint val;
							memcpy((void*)&val, (void*)nv, sizeof(sllint));
							xc = bot_sprintfs(&str, false, " = %lli", val);
							free(nv);
						}
					}
					break;
				}
				case BOT_RTV_REAL:
				{
					str.append("REAL ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}
					if (!mv.vvars[x].v.empty())
					{
						_char* nv = (_char*)malloc(sizeof(float));

						if (nv)
						{
							for (size_t z = 0; z < sizeof(float); z++)
							{
								memcpy((void*)&nv[z], (void*)&mv.vvars[x].v[0][z], sizeof(_char));
							}
							float val;
							memcpy((void*)&val, (void*)nv, sizeof(float));
							xc = bot_sprintfs(&str, false, " = %.9f", val);
							free(nv);
						}
					}
					break;
				}
				case BOT_RTV_STR:
				{
					str.append("TEXT ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}
					if (!mv.vvars[x].v.empty())
					{
						str.append(" = ");

						for (size_t y = 0; y < mv.vvars[x].v[0].size(); y++)
						{
							str.push_back(mv.vvars[x].v[0][y]);
						}
					}
					break;
				}
				case BOT_RTV_BLOB:
				{
					str.append("BLOB ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}
					if (!mv.vvars[x].v.empty())
					{
						str.append(" = ");

						for (size_t y = 0; y < mv.vvars[x].v[0].size(); y++)
						{
							xc = bot_sprintfs(&str, false, "0x%02X ", mv.vvars[x].v[0][y]);
						}
						str.pop_back();
					}
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					str.append("VINT ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}
					_char* nv = (_char*)malloc(sizeof(sllint));

					if (nv)
					{
						if (!mv.vvars[x].v.empty())
						{
							str.append("\n{\n\t");
							for (size_t y = 0; y < mv.vvars[x].v.size(); y++)
							{
								xc = bot_sprintfs(&str, false, "[%u] ", y);
								for (size_t z = 0; z < sizeof(sllint); z++)
								{
									memcpy((void*)&nv[z], (void*)&mv.vvars[x].v[y][z], sizeof(_char));
								}
								sllint val;
								memcpy((void*)&val, (void*)nv, sizeof(sllint));
								xc = bot_sprintfs(&str, false, "%lli,\n\t", val);
							}
							free(nv);
							str.pop_back();
							str.pop_back();
							str.pop_back();
							str.append("\n}");
						}
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					str.append("VREAL ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}
					_char* nv = (_char*)malloc(sizeof(float));

					if (nv)
					{
						if (!mv.vvars[x].v.empty())
						{
							str.append("\n{\n\t");
							for (size_t y = 0; y < mv.vvars[x].v.size(); y++)
							{
								xc = bot_sprintfs(&str, false, "[%u] ", y);
								for (size_t z = 0; z < sizeof(float); z++)
								{
									memcpy((void*)&nv[z], (void*)&mv.vvars[x].v[y][z], sizeof(_char));
								}
								float val;
								memcpy((void*)&val, (void*)nv, sizeof(float));
								xc = bot_sprintfs(&str, false, "%.9f,\n\t", val);
							}
							free(nv);
							str.pop_back();
							str.pop_back();
							str.pop_back();
							str.append("\n}");
						}
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					str.append("VTEXT ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}

					if (!mv.vvars[x].v.empty())
					{
						str.append("\n{\n\t");
						for (size_t y = 0; y < mv.vvars[x].v.size(); y++)
						{
							xc = bot_sprintfs(&str, false, "[%u] %v%c%,\n\t", y, &mv.vvars[x].v[y]);
						}
						str.pop_back();
						str.pop_back();
						str.pop_back();
						str.append("\n}");
					}
					break;
				}
				case BOT_RTV_VBLOB:
				{
					str.append("VBLOB ");

					if (mv.vvars[x].n)
					{
						str.append(mv.vvars[x].n);
					}

					if (!mv.vvars[x].v.empty())
					{
						str.append("\n{\n\t");
						for (size_t y = 0; y < mv.vvars[x].v.size(); y++)
						{
							xc = bot_sprintfs(&str, false, "[%u] %v0x%02X %,\n\t", y, &mv.vvars[x].v[y]);
						}
						str.pop_back();
						str.pop_back();
						str.pop_back();
						str.append("\n}");
					}
					break;
				}
				default:
				{
					break;
				}
				}
				xc = Output(true, str.c_str(), 2, 0);
			}
		}
		else
		{
			carr_24 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: name" \
				"\nShow variable");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 96:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 96", 2);
		}
		carr_48 xcar;
		sint oc = bot_sprintf(xcar.carr, xcar.siz,
			"\n!DISABLED!");
		oc = Output(true, xcar.carr, 2, 0);
		break;
	}
	case 98:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 98", 2);
		}
		if (vec_->size() == 6)
		{
			BOT_FILE_M scp(vec_->at(3).arg.c_str(), vec_->at(4).arg.c_str(), vec_->at(5).arg.c_str(), BOT_FILE_APND, BOT_F_CON);
			sint ox = -1;
			sint rc = BOTOpenFile(&scp, &ox);

			if (xc < 0)
			{
				return -1;
			}

			bot_script ns;
			BOT_STMT qt(false, 0, "scripts", "SCRIPTS", 1, &ns);
			rc = qt.AddCol("NAME", EStr(vec_->at(3).arg.c_str()).c_str());
			rc = qt.AddCol("TYPE", EStr(vec_->at(4).arg.c_str()).c_str());
			rc = qt.AddCol("DEST", EStr(vec_->at(5).arg.c_str()).c_str());
			rc = Query(&qt, BOT_RTV_SCRPT);

			if (rc > -1)
			{
				return -1;
			}

			std::vector<BOT_STMT> tvec;
			BOT_STMT t(false, 2, "scripts", "SCRIPTS", 1);

			if (vec_->at(1).arg.length() < 10)
			{
				uint v = (uint)atoi(vec_->at(1).arg.c_str());
				const uint y = (sizeof(v) * 2) + 4;
				_char nuchar[y]{ 0 };
				sint rc = bot_sprintf(nuchar, y, "X'%02X'", vec_->at(1).arg.c_str());
				rc = t.AddCol("MODE", nuchar);
			}

			if (vec_->at(2).arg.length() < 128)
			{
				sint rc = t.AddCol("ENCODING", "X'");

				for (uint z = 0; z < vec_->at(2).arg.length(); z++)
				{
					const uint y = (sizeof(vec_->at(2).arg[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(2).arg[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}

			if (vec_->at(3).arg.length() < 512)
			{
				sint rc = t.AddCol("NAME", "X'");

				for (uint z = 0; z < vec_->at(3).arg.length(); z++)
				{
					const uint y = (sizeof(vec_->at(3).arg[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(3).arg[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}

			if (vec_->at(4).arg.length() < 256)
			{
				sint rc = t.AddCol("TYPE", "X'");

				for (uint z = 0; z < vec_->at(4).arg.length(); z++)
				{
					const uint y = (sizeof(vec_->at(4).arg[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(4).arg[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}

			if (vec_->at(5).arg.length() < 512)
			{
				sint rc = t.AddCol("DEST", "X'");

				for (uint z = 0; z < vec_->at(5).arg.length(); z++)
				{
					const uint y = (sizeof(vec_->at(5).arg[z]) * 2) + 1;
					_char nuchar[y]{ 0 };
					rc = bot_sprintf(nuchar, y, "%02X", (u_char)vec_->at(5).arg[z]);
					t.cols[rc].append(nuchar);
				}

				t.cols[rc].append("'");
			}
			t.spec = 2;
			tvec.push_back(t);
			xc = Commit(&tvec);
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\na: mode" \
				"\nb: encoding" \
				"\nc: name" \
				"\nd: type" \
				"\ne: file destination" \
				"\nAdd a script at file destination to the db");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 99:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 99", 2);
		}
		if (vec_->size() == 2)
		{
			if (bot_sisn(vec_->at(1).arg.c_str()))
			{
				bot_script rval;
				BOT_STMT t(false, 0, "scripts", "SCRIPTS", 1, &rval);
				sint rc = t.AddCol("ID", EStr(vec_->at(1).arg.c_str()).c_str());
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
				sint rc = t.AddCol("DEST", EStr(vec_->at(1).arg.c_str()).c_str());
				t.rblk = (void*)&rval;
				rc = Query(&t, BOT_RTV_SCRPT);

				if (rc > -1)
				{
					system(rval.script.c_str());
				}
			}
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\na: script name or id" \
				"\nAttempt to run script with a call to system(c_char*)");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 100:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 100", 2);
		}
		TINFO_M tts((sint)PTHREAD_CREATE_JOINABLE, "GIPS", GIPS, lid);
		sint rc = InitThread(&tts, &xc);
		break;
	}
	case 1000:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 1000", 2);
		}
		if (vec_->size() > 3)
		{
			if (!bot_sisn(vec_->at(2).arg.c_str(), vec_->at(2).arg.length()))
			{
				carr_128 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "Command ID(%s) invalid", vec_->at(2).arg.c_str());
				xp = Output(true, ncar.carr, 2, 0);
				return -1;
			}
			if (!bot_sisn(vec_->at(3).arg.c_str(), vec_->at(3).arg.length()))
			{
				carr_128 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "Command Priv(%s) invalid", vec_->at(3).arg.c_str());
				xp = Output(true, ncar.carr, 2, 0);
				return -1;
			}
			
			sint ox = GetPCliMem(BOT_C_PRIV, (void*)&xc);
			ox = (sint)atoi(vec_->at(3).arg.c_str());

			if (ox > xc)
			{
				carr_128 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "Command Priv(%i) exceeds User Priv(%i)", ox, xc);
				xp = Output(true, ncar.carr, 2, 0);
				return -1;
			}

			ox = (sint)atoi(vec_->at(2).arg.c_str());

			if (ox > 999)
			{
				return -1;
			}

			BOTCOMMAND Cmd("", ox);
			xc = GetCommand(&Cmd);

			if (xc < 0)
			{
				return -1;
			}

			if (Cmd.id > -1)
			{
				return -1;
			}

			Cmd.Clear();
			Cmd.Renew(vec_->at(1).arg.c_str(), ox);
			xc = GetCommand(&Cmd);

			if (xc < 0)
			{
				return -1;
			}

			if (Cmd.id > -1)
			{
				return -1;
			}

			if (Cmd.id < 0)
			{
				std::vector<std::string> nargs;
				sint na = 0;
				sint no = 0;
				std::string resp;
				carr_128 xcar;
				xc = bot_sprintf(xcar.carr, xcar.siz, "Required arg(%i): [desc] || empty to continue || EXIT to exit", na + 1);

				while (strlen(xcar.carr))
				{
					xc = Output(true, xcar.carr, 2, 0);
					bot_strclr(xcar.carr);
					xc = Input(": ", &resp);

					if (xc < 0)
					{
						return -1;
					}

					if (resp.length() > 999)
					{
						xc = bot_sprintf(xcar.carr, xcar.siz, "Length exceeds 999 characters");
					}
					else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else if (!resp.empty())
					{
						if (na < 21)
						{
							na++;
							nargs.push_back(resp);
							xc = bot_sprintf(xcar.carr, xcar.siz, "Required arg(%i): [desc] || empty to continue || EXIT to exit", na + 1);
						}
					}
					else {}
					resp.clear();
				}

				xc = bot_sprintf(xcar.carr, xcar.siz, "Optional arg(%i): [desc] || empty to continue || EXIT to exit", na + no + 1);

				while (strlen(xcar.carr))
				{
					xc = Output(true, xcar.carr, 2, 0);
					bot_strclr(xcar.carr);
					xc = Input(": ", &resp);

					if (xc < 0)
					{
						return -1;
					}

					if (resp.length() > 999)
					{
						xc = bot_sprintf(xcar.carr, xcar.siz, "Length exceeds 999 characters");
					}
					else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else if (!resp.empty())
					{
						if (no + na < 41)
						{
							no++;
							nargs.push_back(resp);
							xc = bot_sprintf(xcar.carr, xcar.siz, "Optional arg(%i): [desc] || empty to continue || EXIT to exit", na + no + 1);
						}
					}
					else {}
					resp.clear();
				}

				xc = bot_sprintf(xcar.carr, xcar.siz, "Description: [desc] || empty to continue || EXIT to exit");

				while (strlen(xcar.carr))
				{
					xc = Output(true, xcar.carr, 2, 0);
					bot_strclr(xcar.carr);
					xc = Input(": ", &resp);

					if (xc < 0)
					{
						return -1;
					}

					if (resp.length() > 999)
					{
						xc = bot_sprintf(xcar.carr, xcar.siz, "Length exceeds 999 characters");
					}
					else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else if (!resp.empty())
					{
						nargs.push_back(resp);
					}
					else {}
					resp.clear();
				}

				BOT_STMT t(false, 2, "litebot", "COMMANDS", 1);
				xc = t.AddCol("CMD", UCASE(EStr(vec_->at(1).arg.c_str()).c_str()).c_str());
				xc = t.AddCol("CMD_ID", vec_->at(2).arg.c_str());
				xc = t.AddCol("PRIV", vec_->at(3).arg.c_str());
				t.spec = 2;
				std::vector<BOT_STMT> tvec;
				xc = vtool.AVTV(&tvec, &t, true, true);
				xc = Commit(&tvec);

				if (xc > -1)
				{
					BOT_FILE_M hfile("litebot", ".cpp", BOTPathS(BOT_MOD_NM).c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
					ox = -1;
					xc = BOTOpenFile(&hfile, &ox, false, false, true);

					if (xc < 0)
					{
						BOT_FILE_M xfile("litebot", ".cpp", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
						sint nx = -1;
						xc = BOTOpenFile(&xfile, &nx, false, false, true);

						if (xc > -1)
						{
							xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

							if (!nx)
							{
								nx = BOTCloseFile(&xfile, true, false, true);
							}

							hfile.lid = -1;
							xc = BOTOpenFile(&hfile, &ox, false, false, true);
						}
					}

					if (xc > -1)
					{
						carr_32 ccar("\nsint machine::Command(std::");
						xc = BOTFindInFile(&hfile, true, 0, 0, ccar.carr, bot_strlen(ccar.carr));

						if (xc > -1)
						{
							BOT_CRS crs(0, lid);
							xc = hfile.GetCrs(&crs);
							xc = bot_sprintf(ccar.carr, ccar.siz, "switch (vec[x].cmd_id)");
							xc = BOTFindInFile(&hfile, true, crs.t, hfile.fst.e_loc, ccar.carr, bot_strlen(ccar.carr));
							xc = hfile.GetCrs(&crs);
							carr_16 lcara("case 1000:");
							xc = BOTFindInFile(&hfile, true, crs.t, hfile.fst.e_loc, lcara.carr, bot_strlen(lcara.carr));

							if (xc > -1)
							{
								sint nx = (sint)atoi(vec_->at(2).arg.c_str());
								BOT_CRS lcrsa(0, lid);
								xc = hfile.GetCrs(&lcrsa);
								sint ct = 0;

								while (ct < 2)
								{
									sint rc = 4;

									while (rc > -1 && rc < 1000)
									{
										if (rc > 4)
										{
											xc = hfile.GetCrs(&crs);

											if (ct)
											{
												xc = BOTFindInFile(&hfile, true, lcrsa.t + 1, hfile.dsiz - 1, lcara.carr, bot_strlen(lcara.carr));

												if (xc > -1)
												{
													xc = hfile.GetCrs(&crs);
												}
											}
										}
										rc++;
										xc = bot_sprintf(ccar.carr, ccar.siz, "case %i:", rc);
										xc = BOTFindInFile(&hfile, true, crs.t, lcrsa.f, ccar.carr, bot_strlen(ccar.carr));

										if (xc > -1)
										{
											xc = hfile.GetCrs(&crs);

											if (rc >= nx)
											{
												xc = bot_sprintf(ccar.carr, ccar.siz, "{");
												BOT_CRS ncs(0, lid);
												xc = BOTFindInFile(&hfile, true, crs.t, lcrsa.f, ccar.carr, bot_strlen(ccar.carr));
												xc = hfile.GetCrs(&ncs);
												std::string fstr;
												xc = bot_sprintf(ccar.carr, ccar.siz, " ");
												BOT_CRS mkc(0, lid);

												for (xc = BOTFindInFile(&hfile, true, crs.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)); xc > -1 && fstr.length() < 1024; xc = BOTFindInFile(&hfile, true, mkc.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)))
												{
													xc = hfile.GetCrs(&mkc);
													fstr.append(ccar.carr);
												}

												xc = bot_sprintf(ccar.carr, ccar.siz, "\t");

												for (xc = BOTFindInFile(&hfile, true, crs.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)); xc > -1 && fstr.length() < 1024; xc = BOTFindInFile(&hfile, true, mkc.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)))
												{
													xc = hfile.GetCrs(&mkc);
													fstr.append(ccar.carr);
												}

												xc = bot_sprintf(ccar.carr, ccar.siz, "\n");
												xc = BOTFindInFile(&hfile, true, ncs.t + 1, lcrsa.f, ccar.carr, bot_strlen(ccar.carr));

												if (xc > -1)
												{
													if (rc > nx)
													{
														std::string scar("case ");
														scar.append(vec_->at(2).arg.c_str());
														scar.append(":\n");
														scar.append(fstr.c_str());
														scar.append("{\n");
														scar.append(fstr.c_str());

														if (ct < 1)
														{
															scar.append("\toc = bot_sprintf(xcar.carr, xcar.siz, \"%s\"");
															carr_1024 ocar;

															for (size_t c = 0; c < nargs.size(); c++)
															{
																if (c == nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, " \\ \n\t\t%s\"\\n%s\"", fstr.c_str(), nargs[c].c_str());
																}
																else if (c < (size_t)na)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, " \\ \n\t\t%s\"\\n%u: %s\"", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else if (c < nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, " \\ \n\t\t%s\"\\n(optional)%u: %s\"", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else {}
																scar.append(ocar.carr);
															}
															scar.append(", ncar.carr);\n");
														}
														else
														{
															carr_1024 ocar;
															xc = bot_sprintf(ocar.carr, ocar.siz, "\tif (vec_->size() > %u)\n%s\t{\n%s\t\tif (debug_lvl >= 1000 && debug_m)\n%s\t\t{\n%s\t\t\tsint oc = Output(\"Found BOTCOMMAND id %s\", 2);\n%s\t\t}\n%s\t\t/*CMD*/\n%s\t}\n%s\telse\n%s\t{\n%s\t\tcarr_4096 xcar;\n%s\t\tsint oc = bot_sprintf(xcar.carr, xcar.siz,", na, fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), vec_->at(2).arg.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str());
															scar.append(ocar.carr);

															for (size_t c = 0; c < nargs.size(); c++)
															{
																if (c == nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, "\n\t\t\t%s\"\\n%s\"", fstr.c_str(), nargs[c].c_str());
																}
																else if (c < (size_t)na)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, "\n\t\t\t%s\"\\n%u: %s\" \\", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else if (c < nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, "\n\t\t\t%s\"\\n(optional)%u: %s\" \\", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else {}
																scar.append(ocar.carr);
															}
															scar.append(");\n\t\t\toc = Output(true, xcar.carr, 2, 0);\n");
															scar.append(fstr.c_str());
															scar.append("\t}\n");
														}

														scar.append(fstr.c_str());
														scar.append("\tbreak;\n");
														scar.append(fstr.c_str());
														scar.append("}\n");
														scar.append(fstr.c_str());
														xc = BOTFileOUT(&hfile, crs.f, true, BOT_RTV_STR, &scar, BOT_RTV_MAX);
													}
													else
													{
														std::string scar(ccar.carr);
														scar.append(fstr.c_str());

														if (ct < 1)
														{
															scar.append("\toc = bot_sprintf(xcar.carr, xcar.siz, \"%s\"");
															carr_1024 ocar;

															for (size_t c = 0; c < nargs.size(); c++)
															{
																if (c == nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, "\n\t\t%s\"\\n%s\"", fstr.c_str(), nargs[c].c_str());
																}
																else if (c <= (size_t)na)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, "\n\t\t%s\"\\n%u: %s\" \\", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else if (c < nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, "\n\t\t%s\"\\n(optional)%u: %s\" \\", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else {}
																scar.append(ocar.carr);
															}
															scar.append(", ncar.carr);");
														}
														else
														{
															carr_1024 ocar;
															xc = bot_sprintf(ocar.carr, ocar.siz, "\tif (vec_->size() > %u)\n%s\t{\n%s\t\tif (debug_lvl >= 1000 && debug_m)\n%s\t\t{\n%s\t\tcarr_4096 xcar;\n%s\t\t\tsint oc = Output(\"Found BOTCOMMAND id %s\", 2);\n%s\t\t}\n%s\t\t/*CMD*/\n%s\t}\n%s\telse\n%s\t{\n%s\t\tsint oc = bot_sprintf(xcar.carr, xcar.siz,", nargs.size() - 1, fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), vec_->at(2).arg.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str(), fstr.c_str());
															scar.append(ocar.carr);

															for (size_t c = 0; c < nargs.size(); c++)
															{
																if (c == nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, " \\ \n\t\t\t%s\"\\n%s\"", fstr.c_str(), nargs[c].c_str());
																}
																else if (c <= (size_t)na)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, " \\ \n\t\t\t%s\"\\n%u: %s\"", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else if (c < nargs.size() - 1)
																{
																	xc = bot_sprintf(ocar.carr, ocar.siz, " \\ \n\t\t\t%s\"\\n(optional)%u: %s\"", fstr.c_str(), c + 1, nargs[c].c_str());
																}
																else {}
																scar.append(ocar.carr);
															}
															scar.append(");\n\t\t\toc = Output(true, xcar.carr, 2, 0);\n");
															scar.append(fstr.c_str());
															scar.append("\t}\n");
														}
														xc = BOTFileOUT(&hfile, ncs.f + 1, true, BOT_RTV_STR, &scar, BOT_RTV_MAX);
													}
													xc = hfile.GetCrs(&crs);
												}
												rc = -1;
											}
										}
									}
									ct++;

								}
								xc = BOTSaveFile(&hfile, 0, true);
							}
						}
						if (!ox)
						{
							ox = BOTCloseFile(&hfile, true, false, true);
						}
					}

					hfile.Renew("litebot", ".h", BOTPathS(BOT_MOD_NM).c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
					ox = -1;
					xc = BOTOpenFile(&hfile, &ox, false, false, true);

					if (xc < 0)
					{
						BOT_FILE_M xfile("litebot", ".h", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
						sint nx = -1;
						xc = BOTOpenFile(&xfile, &nx, false, false, true);

						if (xc > -1)
						{
							xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

							if (!nx)
							{
								nx = BOTCloseFile(&xfile, true, false, true);
							}

							hfile.lid = -1;
							xc = BOTOpenFile(&hfile, &ox, false, false, true);
						}
					}

					if (xc > -1)
					{
						carr_32 ccar("<c_char*> litebot_stmts\n\t{\n\t\t");
						xc = BOTFindInFile(&hfile, true, 0, 0, ccar.carr, bot_strlen(ccar.carr));

						if (xc > -1)
						{
							BOT_CRS crs(0, lid);
							xc = hfile.GetCrs(&crs);
							carr_1024 ocar;
							xc = bot_sprintf(ocar.carr, ocar.siz, "\"INSERT INTO litebot.COMMANDS (\" \\\n\t\t\"CMD, PRIV, CMD_ID) \" \\\n\t\t\"\\\"%s\\\", %s, %s);\",\n\t\t\n\t\t", UCASE(vec_->at(1).arg.c_str()).c_str(), vec_->at(3).arg.c_str(), vec_->at(2).arg.c_str());
							xc = BOTFileOUT(&hfile, crs.t + 1, true, BOT_RTV_CHARP, ocar.carr, BOT_RTV_MAX);
						}

						xc = BOTSaveFile(&hfile, 0, true);

						if (!ox)
						{
							ox = BOTCloseFile(&hfile, true, false, true);
						}
					}

					xc = bot_sprintf(xcar.carr, xcar.siz, "Command: \"%s\" ID: %s added", UCASE(vec_->at(1).arg.c_str()).c_str(), vec_->at(2).arg.c_str());
					xc = Output(true, xcar.carr, 2, 0);
				}
			}
		}
		else
		{
			carr_128 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\na: command name" \
				"\nb: id 0-UINT_MAX" \
				"\nc: privlege level 0-UINT_MAX" \
				"\n(optional)d: file location " \
				"\nAdd a command to the db");
			oc = Output(true, xcar.carr, 2, 0);
		}
		break;
	}
	case 1001:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 1001", 2);
		}
		if (vec_->size() > 1)
		{
			std::vector<BOTCOMMAND> cmds;
			BOTCOMMAND Cmd;
			BOT_STMT t;
			std::vector<BOT_STMT> stmts;

			for (size_t x = 1; x < vec_->size(); x++)
			{
				t.Renew(false, 4, "litebot", "COMMANDS", 1);
				t.spec = 0;

				if (bot_sisn(vec_->at(1).arg.c_str(), vec_->at(1).arg.length()))
				{
					sint ox = (sint)atoi(vec_->at(1).arg.c_str());

					if (ox < 1000)
					{
						Cmd.Renew("", ox);
						xc = GetCommand(&Cmd);

						if (xc > -1 && Cmd.id > -1)
						{
							xc = t.AddCond(0, "CMD_ID", "=", vec_->at(2).arg.c_str());
							xc = vtool.AVTV(&stmts, &t, true, true);
							cmds.push_back(Cmd);
						}
					}
				}
				else
				{
					Cmd.Renew(vec_->at(1).arg.c_str());
					xc = GetCommand(&Cmd);

					if (xc > -1 && Cmd.id > -1)
					{
						xc = t.AddCond(0, "CMD", "=", UCASE(EStr(vec_->at(1).arg.c_str()).c_str()).c_str());
						xc = vtool.AVTV(&stmts, &t, true, true);
						cmds.push_back(Cmd);
					}
				}
			}
			
			if (!stmts.empty())
			{
				xc = Commit(&stmts);

				if (xc > -1)
				{
					for (size_t x = 0; x < cmds.size(); x++)
					{
						BOT_FILE_M hfile("litebot", ".h", BOTPathS(BOT_MOD_NM).c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
						sint ox = -1;
						xc = BOTOpenFile(&hfile, &ox, false, false, true);

						if (xc < 0)
						{
							BOT_FILE_M xfile("litebot", ".h", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
							sint nx = -1;
							xc = BOTOpenFile(&xfile, &nx, false, false, true);

							if (xc > -1)
							{
								xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

								if (!nx)
								{
									nx = BOTCloseFile(&xfile, true, false, true);
								}

								hfile.lid = -1;
								xc = BOTOpenFile(&hfile, &ox, false, false, true);
							}
						}

						carr_1024 xcar;

						if (xc > -1)
						{
							xc = bot_sprintf(xcar.carr, xcar.siz, "\"INSERT INTO litebot.COMMANDS (\" \\\n\t\t\"CMD, PRIV, CMD_ID) \" \\\n\t\t\"\\\"%s\\\", %i, %i);\",\n\t\t\n\t\t", cmds[x].cmd.c_str(), cmds[x].priv, cmds[x].cmd_id);
							xc = BOTFindInFile(&hfile, true, 0, 0, xcar.carr, bot_strlen(xcar.carr));

							if (xc > -1)
							{
								BOT_CRS crs(0, lid);
								xc = hfile.GetCrs(&crs);
								xc = BOTFileER(&hfile, true, crs.f, crs.t);
							}

							xc = BOTSaveFile(&hfile, 0, true);

							if (!ox)
							{
								ox = BOTCloseFile(&hfile, true, false, true);
							}
						}

						hfile.Renew("litebot", ".cpp", BOTPathS(BOT_MOD_NM).c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
						ox = -1;
						xc = BOTOpenFile(&hfile, &ox, false, false, true);

						if (xc < 0)
						{
							BOT_FILE_M xfile("litebot", ".cpp", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
							sint nx = -1;
							xc = BOTOpenFile(&xfile, &nx, false, false, true);

							if (xc > -1)
							{
								xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

								if (!nx)
								{
									nx = BOTCloseFile(&xfile, true, false, true);
								}

								hfile.lid = -1;
								xc = BOTOpenFile(&hfile, &ox, false, false, true);
							}
						}

						if (xc > -1)
						{
							carr_1024 xcar("\nsint machine::Command");
							xc = BOTFindInFile(&hfile, true, 0, 0, xcar.carr, bot_strlen(xcar.carr));

							if (xc > -1)
							{
								BOT_CRS crs(0, lid);
								xc = hfile.GetCrs(&crs);
								xc = bot_sprintf(xcar.carr, xcar.siz, "switch (vec[x].cmd_id)", cmds[x].cmd.c_str(), cmds[x].priv, cmds[x].cmd_id);
								xc = BOTFindInFile(&hfile, true, crs.t+1, 0, xcar.carr, bot_strlen(xcar.carr));

								if (xc > -1)
								{
									xc = hfile.GetCrs(&crs);

									for (uint ct = 0; ct < 2; ct++)
									{
										if (!ct)
										{
											xc = bot_sprintf(xcar.carr, xcar.siz, "case %i:\n", cmds[x].cmd_id);
											xc = BOTFindInFile(&hfile, true, crs.t + 1, 0, xcar.carr, bot_strlen(xcar.carr));

											if (xc > -1)
											{
												xc = hfile.GetCrs(&crs);
												carr_4 ccar("{");
												xc = BOTFindInFile(&hfile, true, crs.f, 0, ccar.carr, bot_strlen(ccar.carr));

												if (xc > -1)
												{
													BOT_CRS ncs(0, lid);
													xc = hfile.GetCrs(&ncs);
													xc = bot_sprintf(ccar.carr, ccar.siz, " ");
													std::string fstr;
													BOT_CRS mkc(0, lid);

													for (xc = BOTFindInFile(&hfile, true, crs.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)); xc > -1 && fstr.length() < 1024; xc = BOTFindInFile(&hfile, true, mkc.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)))
													{
														xc = hfile.GetCrs(&mkc);
														fstr.append(ccar.carr);
													}

													xc = bot_sprintf(ccar.carr, ccar.siz, "\t");

													for (xc = BOTFindInFile(&hfile, true, crs.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)); xc > -1 && fstr.length() < 1024; xc = BOTFindInFile(&hfile, true, mkc.t + 1, ncs.f, ccar.carr, bot_strlen(ccar.carr)))
													{
														xc = hfile.GetCrs(&mkc);
														fstr.append(ccar.carr);
													}

													xc = bot_sprintf(xcar.carr, xcar.siz, "break;\n%s}\n%s", fstr.c_str(), fstr.c_str());
													xc = BOTFindInFile(&hfile, true, ncs.f, 0, xcar.carr, xcar.siz);

													if (xc > -1)
													{
														xc = hfile.GetCrs(&ncs);
														xc = BOTFileER(&hfile, true, crs.f, ncs.t);
													}
												}
											}
										}
										else
										{
											xc = hfile.GetCrs(&crs);
											xc = bot_sprintf(xcar.carr, xcar.siz, "case %i:\n\t{", cmds[x].cmd_id);
											xc = BOTFindInFile(&hfile, true, crs.t + 1, 0, xcar.carr, bot_strlen(xcar.carr));

											if (xc > -1)
											{
												xc = hfile.GetCrs(&crs);
												std::string fstr("break;\n\t}\n\t");
												xc = bot_sprintf(xcar.carr, xcar.siz, "%s", fstr.c_str());
												xc = BOTFindInFile(&hfile, true, crs.t + 1, 0, xcar.carr, xcar.siz);

												if (xc > -1)
												{
													BOT_CRS ncs(0, lid);
													xc = hfile.GetCrs(&ncs);
													xc = BOTFileER(&hfile, true, crs.f, ncs.t);
												}
											}
										}
									}
								}
								xc = BOTSaveFile(&hfile, 0, true);

								if (!ox)
								{
									ox = BOTCloseFile(&hfile, true, false, true);
								}
							}
						}
						xc = bot_sprintf(xcar.carr, xcar.siz, "Command: \"%s\" ID: %i removed", Cmd.cmd.c_str(), Cmd.cmd_id);
						xc = Output(true, xcar.carr, 2, 0);
					}
				}
			}
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\na: command name OR command id" \
				"\nRemove a command from the db");
			oc = Output(true, xcar.carr, 2, 0);
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
sint machine::ArgSep(std::vector <std::string>* ret_, bool ksep, size_t f, size_t t, c_char* val, ...)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::ArgSep(std::vector <std::string>* ret_(%i), bool ksep(%u), size_t f(%u), size_t t(%u), c_char* val(%s), ...)", (sint)ret_, (uint)ksep, f, t, (sint)val);
		op = Output(outp.carr, 2);
	}

	if (!ret_ || !val)
	{
		return -1;
	}
	else
	{
		size_t ret = (size_t)bot_cstrchk(val);

		if (!ret || ret > (size_t)BOT_STRLEN_MAX)
		{
			std::string a;
			ret = (size_t)bot_sprintfs(&a, false, "Bad Size: len: %u", ret);
			ret_->push_back(a);
			return -1;
		}
		if (!t || t > ret - 1 || t < f)
		{
			t = ret - 1;
		}

	}

	slint lign = -1;
	slint lit = -1;
	slint litloc = 0;
	std::vector<size_t> ord;
	std::vector<size_t> ordl;
	std::string rstr;
	size_t mk = 0;
	_char ig = '\\';
	sint ret = -1;
	sint typ = BOT_RTV_MAX;
	va_list args;
	va_start(args, val);
	typ = va_arg(args, sint);

	switch (typ)
	{
	case BOT_RTV_SINT:
	{
		sint sep = va_arg(args, sint);
		size_t sl = sizeof(sint);

		for (size_t x = f; x < t + 1; x++)
		{
			if (lit > -1)
			{
				for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
				{
					if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
					{
						if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
						{
							if (lit == (slint)xl)
							{
								if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
								{
									if (ksep)
									{
										for (; mk < x + sl; mk++)
										{
											rstr.push_back(val[mk]);
										}

										if (!rstr.empty())
										{
											ret_->push_back(rstr);
											rstr.clear();
										}
									}
									else
									{
										for (mk += sl; mk < x; mk++)
										{
											rstr.push_back(val[mk]);
										}

										if (!rstr.empty())
										{
											ret_->push_back(rstr);
											rstr.clear();
										}
									}
									x += (sl - 1);
									mk = x + 1;
								}
								lit = -1;
								litloc = (slint)x;
							}
							xl = msy.nrts_lit.size();
						}
						else
						{
							if (x > 1)
							{
								if (!memcmp((void*)&ig, (void*)&val[x - 2], sl))
								{
									if (lit == (slint)xl)
									{
										if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
										{
											if (ksep)
											{
												for (; mk < x + sl; mk++)
												{
													rstr.push_back(val[mk]);
												}

												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											else
											{
												for (mk += sl; mk < x; mk++)
												{
													rstr.push_back(val[mk]);
												}

												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											x += (sl - 1);
											mk = x + 1;
										}
										lit = -1;
										litloc = (slint)x;
									}
									xl = msy.nrts_lit.size();
								}
							}
						}
					}
				}
			}
			else
			{
				if (lign > -1)
				{
					for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
					{
						if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sl))
						{
							size_t zl = 0;

							while (zl < msy.nrts_lign_[yl].length() && zl < t)
							{
								if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sl))
								{
									zl = msy.nrts_lign_[yl].length();
								}
								zl++;
							}

							if (zl == msy.nrts_lign_[yl].length())
							{
								if (lign == (slint)yl)
								{
									lign = -1;
									yl = msy.nrts_lign_.size();
								}
							}
						}
					}
				}
				if (lign < 0)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
						{
							if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
							{
								for (; mk < x; mk++)
								{
									rstr.push_back(val[mk]);
								}

								if (!rstr.empty())
								{
									ret_->push_back(rstr);
									rstr.clear();
								}
							}
							lit = (slint)xl;
							litloc = (slint)x;
							xl = msy.nrts_lit.size();
						}
					}
					if (lit < 0)
					{
						if (lign < 0)
						{
							for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
							{
								if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sl))
								{
									size_t zl = 0;

									while (zl < msy.nrts_lign[yl].length() && zl < t)
									{
										if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sl))
										{
											zl = msy.nrts_lign[yl].length();
										}
										zl++;
									}

									if (zl == msy.nrts_lign[yl].length())
									{
										lign = (slint)yl;
										yl = msy.nrts_lign.size();
									}
								}
							}
							if (lign < 0)
							{
								for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
								{
									if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sl))
									{
										if (ord.empty())
										{
											if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
											{
												for (; mk < x; mk++)
												{
													rstr.push_back(val[mk]);
												}

												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
										}
										ord.push_back(xl);
										ordl.push_back(x);
										xl = msy.nrts_ord.size();
									}
								}
								if (!ord.empty())
								{
									for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sl))
										{
											if (ord[ord.size() - 1] == xl)
											{
												ord.pop_back();
												ordl.pop_back();

												if (ord.empty())
												{
													if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
													{
														if (ksep)
														{
															for (; mk < x + sl; mk++)
															{
																rstr.push_back(val[mk]);
															}

															if (!rstr.empty())
															{
																ret_->push_back(rstr);
																rstr.clear();
															}
														}
														else
														{
															for (mk += sl; mk < x; mk++)
															{
																rstr.push_back(val[mk]);
															}

															if (!rstr.empty())
															{
																ret_->push_back(rstr);
																rstr.clear();
															}
														}
														x += (sl - 1);
														mk = x + 1;
													}
												}
											}
											xl = msy.nrts_ord_.size();
										}
									}
								}
								else
								{
									if (!memcmp((void*)&val[x], (void*)&sep, sl))
									{
										if (!x)
										{
											if (ksep)
											{
												std::string nsep;
												nsep.push_back(sep);
												ret_->push_back(nsep);
											}
											x += sl - 1;
											mk = x + 1;
										}
										else
										{
											if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
											{
												for (; mk < x; mk++)
												{
													rstr.push_back(val[mk]);
												}
												x += (sl - 1);
												mk = x + 1;

												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}

												if (ksep)
												{
													std::string nsep;
													nsep.push_back(sep);
													ret_->push_back(nsep);
												}
											}
											else
											{
												if (x > 1)
												{
													if (memcmp((void*)&ig, (void*)&val[x - 2], sl))
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														x += (sl - 1);
														mk = x + 1;

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}

														if (ksep)
														{
															std::string nsep;
															nsep.push_back(sep);
															ret_->push_back(nsep);
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
		break;
	}
	case BOT_RTV_CHAR:
	{
		sint ptr = va_arg(args, sint);
		_char sep = (_char)ptr;

		if (sep)
		{
			size_t sl = sizeof(_char);

			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
							{
								if (lit == (slint)xl)
								{
									if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
									{
										if (ksep)
										{
											for (; mk < x + sl; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										else
										{
											for (mk += sl; mk < x; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										x += (sl - 1);
										mk = x + 1;
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sl))
									{
										if (lit == (slint)xl)
										{
											if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
											{
												if (ksep)
												{
													for (; mk < x + sl; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												else
												{
													for (mk += sl; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												x += (sl - 1);
												mk = x + 1;
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sl))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sl))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
							{
								if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
								{
									for (; mk < x; mk++)
									{
										rstr.push_back(val[mk]);
									}

									if (!rstr.empty())
									{
										ret_->push_back(rstr);
										rstr.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sl))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sl))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sl))
										{
											if (ord.empty())
											{
												if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
												{
													for (; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sl))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
														{
															if (ksep)
															{
																for (; mk < x + sl; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															else
															{
																for (mk += sl; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															x += (sl - 1);
															mk = x + 1;
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep, sl))
										{
											if (!x)
											{
												if (ksep)
												{
													std::string nsep;
													nsep.push_back(sep);
													ret_->push_back(nsep);
												}
												x += sl - 1;
												mk = x + 1;
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
												{
													for (; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}
													x += (sl - 1);
													mk = x + 1;

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}

													if (ksep)
													{
														std::string nsep;
														nsep.push_back(sep);
														ret_->push_back(nsep);
													}
												}
												else
												{
													if (x > 1)
													{
														if (memcmp((void*)&ig, (void*)&val[x - 2], sl))
														{
															for (; mk < x; mk++)
															{
																rstr.push_back(val[mk]);
															}
															x += (sl - 1);
															mk = x + 1;

															if (!rstr.empty())
															{
																ret_->push_back(rstr);
																rstr.clear();
															}

															if (ksep)
															{
																std::string nsep;
																nsep.push_back(sep);
																ret_->push_back(nsep);
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
		}
		break;
	}
	case BOT_RTV_CHARP:
	{
		void* ptr = va_arg(args, void*);
		_char* sep = reinterpret_cast<_char*>(ptr);

		if (sep)
		{
			size_t sl = bot_strlen(sep);
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									if (!strcmp(sep, &msy.nrts_lit[xl]))
									{
										if (ksep)
										{
											for (; mk < x + sl; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										else
										{
											for (mk += sl; mk < x; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										x += (sl - 1);
										mk = x + 1;
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											if (!strcmp(sep, &msy.nrts_lit[xl]))
											{
												if (ksep)
												{
													for (; mk < x + sl; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												else
												{
													for (mk += sl; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												x += (sl - 1);
												mk = x + 1;
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								if (!strcmp(sep, &msy.nrts_lit[xl]))
								{
									for (; mk < x; mk++)
									{
										rstr.push_back(val[mk]);
									}

									if (!rstr.empty())
									{
										ret_->push_back(rstr);
										rstr.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
												{
													for (; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
														{
															if (ksep)
															{
																for (; mk < x + sl; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															else
															{
																for (mk += sl; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															x += (sl - 1);
															mk = x + 1;
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep[0], sizeof(_char)))
										{
											if (!x)
											{
												size_t y = 1;

												while (y < sl && x + y < t)
												{
													if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
													{
														y = sl;
													}
													y++;
												}

												if (y == sl)
												{
													if (ksep)
													{
														std::string nsep(sep);
														ret_->push_back(nsep);
													}
													x += sl - 1;
													mk = x + 1;
												}
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
												{
													size_t y = 1;

													while (y < sl && x + y < t)
													{
														if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
														{
															y = sl;
														}
														y++;
													}

													if (y == sl)
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														x += (sl - 1);
														mk = x + 1;

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}

														if (ksep)
														{
															std::string nsep(sep);
															ret_->push_back(nsep);
														}
													}
												}
												else
												{
													if (x > 1)
													{
														if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
														{
															size_t y = 1;

															while (y < sl && x + y < t)
															{
																if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
																{
																	y = sl;
																}
																y++;
															}

															if (y == sl)
															{
																for (; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}
																x += (sl - 1);
																mk = x + 1;

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}

																if (ksep)
																{
																	std::string nsep(sep);
																	ret_->push_back(nsep);
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
			}
		}
		break;
	}
	case BOT_RTV_CCHAR:
	{
		void* ptr = va_arg(args, void*);
		c_char* sep = reinterpret_cast<c_char*>(ptr);

		if (sep)
		{
			size_t sl = bot_cstrlen(sep);

			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									if (!strcmp(sep, &msy.nrts_lit[xl]))
									{
										if (ksep)
										{
											for (; mk < x + sl; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										else
										{
											for (mk += sl; mk < x; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										x += (sl - 1);
										mk = x + 1;
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											if (!strcmp(sep, &msy.nrts_lit[xl]))
											{
												if (ksep)
												{
													for (; mk < x + sl; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												else
												{
													for (mk += sl; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												x += (sl - 1);
												mk = x + 1;
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								if (!strcmp(sep, &msy.nrts_lit[xl]))
								{
									for (; mk < x; mk++)
									{
										rstr.push_back(val[mk]);
									}

									if (!rstr.empty())
									{
										ret_->push_back(rstr);
										rstr.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
												{
													for (; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
														{
															if (ksep)
															{
																for (; mk < x + sl; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															else
															{
																for (mk += sl; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															x += (sl - 1);
															mk = x + 1;
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep[0], sizeof(_char)))
										{
											if (!x)
											{
												size_t y = 1;

												while (y < sl && x + y < t)
												{
													if (memcmp((void*)&val[x + y], &sep[y], sizeof(_char)))
													{
														y = sl;
													}
													y++;
												}

												if (y == sl)
												{
													if (ksep)
													{
														std::string nsep(sep);
														ret_->push_back(nsep);
													}
													x += sl - 1;
													mk = x + 1;
												}
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
												{
													size_t y = 1;

													while (y < sl && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep[y], sizeof(_char)))
														{
															y = sl;
														}
														y++;
													}

													if (y == sl)
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														x += (sl - 1);
														mk = x + 1;

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}

														if (ksep)
														{
															std::string nsep(sep);
															ret_->push_back(nsep);
														}
													}
												}
												else
												{
													if (x > 1)
													{
														if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
														{
															size_t y = 1;

															while (y < sl && x + y < t)
															{
																if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
																{
																	y = sl;
																}
																y++;
															}

															if (y == sl)
															{
																for (; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}
																x += (sl - 1);
																mk = x + 1;

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}

																if (ksep)
																{
																	std::string nsep(sep);
																	ret_->push_back(nsep);
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
			}
		}
		break;
	}
	case BOT_RTV_STR:
	{
		void* ptr = va_arg(args, void*);
		std::string* sep = reinterpret_cast<std::string*>(ptr);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									if (!strcmp(sep->c_str(), &msy.nrts_lit[xl]))
									{
										if (ksep)
										{
											for (; mk < x + sep->length(); mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										else
										{
											for (mk += sep->length(); mk < x; mk++)
											{
												rstr.push_back(val[mk]);
											}

											if (!rstr.empty())
											{
												ret_->push_back(rstr);
												rstr.clear();
											}
										}
										x += (sep->length() - 1);
										mk = x + 1;
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											if (!strcmp(sep->c_str(), &msy.nrts_lit[xl]))
											{
												if (ksep)
												{
													for (; mk < x + sep->length(); mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												else
												{
													for (mk += sep->length(); mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
												x += (sep->length() - 1);
												mk = x + 1;
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								if (!strcmp(sep->c_str(), &msy.nrts_lit[xl]))
								{
									for (; mk < x; mk++)
									{
										rstr.push_back(val[mk]);
									}

									if (!rstr.empty())
									{
										ret_->push_back(rstr);
										rstr.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												if (!strcmp(sep->c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->c_str(), &msy.nrts_ord_[xl]))
												{
													for (; mk < x; mk++)
													{
														rstr.push_back(val[mk]);
													}

													if (!rstr.empty())
													{
														ret_->push_back(rstr);
														rstr.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!strcmp(sep->c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->c_str(), &msy.nrts_ord_[xl]))
														{
															if (ksep)
															{
																for (; mk < x + sep->length(); mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															else
															{
																for (mk += sep->length(); mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}
															}
															x += (sep->length() - 1);
															mk = x + 1;
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep->at(0), sizeof(_char)))
										{
											if (!x)
											{
												size_t y = 1;

												while (y < sep->length() && x + y < t)
												{
													if (memcmp((void*)&val[x + y], &sep->at(y), sizeof(_char)))
													{
														y = sep->length();
													}
													y++;
												}

												if (y == sep->length())
												{
													if (ksep)
													{
														ret_->push_back(*sep);
													}
													x += sep->length() - 1;
													mk = x + 1;
												}
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
												{
													size_t y = 1;

													while (y < sep->length() && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep->at(y), sizeof(_char)))
														{
															y = sep->length();
														}
														y++;
													}

													if (y == sep->length())
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														x += (sep->length() - 1);
														mk = x + 1;

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}

														if (ksep)
														{
															ret_->push_back(*sep);
														}
													}
												}
												else
												{
													if (x > 1)
													{
														if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
														{
															size_t y = 1;

															while (y < sep->length() && x + y < t)
															{
																if (memcmp((void*)&val[x + y], &sep->at(y), sizeof(_char)))
																{
																	y = sep->length();
																}
																y++;
															}

															if (y == sep->length())
															{
																for (; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}
																x += (sep->length() - 1);
																mk = x + 1;

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}

																if (ksep)
																{
																	ret_->push_back(*sep);
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
			}
		}
		break;
	}
	case BOT_RTV_VCHAR:
	{
		std::vector<_char>* sep = va_arg(args, std::vector<_char>*);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									for (size_t xt = 0; xt < sep->size(); xt++)
									{
										if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_lit[xl], sizeof(_char)))
										{
											if (ksep)
											{
												for (; mk < x + sizeof(_char); mk++)
												{
													rstr.push_back(val[mk]);
												}
												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											else
											{
												for (mk += sizeof(_char); mk < x; mk++)
												{
													rstr.push_back(val[mk]);
												}
												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											x += (sizeof(_char) - 1);
											mk = x + 1;
											xt = sep->size();
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											for (size_t xt = 0; xt < sep->size(); xt++)
											{
												if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_lit[xl], sizeof(_char)))
												{
													if (ksep)
													{
														for (; mk < x + sizeof(_char); mk++)
														{
															rstr.push_back(val[mk]);
														}
														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
													}
													else
													{
														for (mk += sizeof(_char); mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
													}
													x += (sizeof(_char) - 1);
													mk = x + 1;
													xt = sep->size();
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								for (size_t xt = 0; xt < sep->size(); xt++)
								{
									if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_lit[xl], sizeof(_char)))
									{
										for (; mk < x; mk++)
										{
											rstr.push_back(val[mk]);
										}

										if (!rstr.empty())
										{
											ret_->push_back(rstr);
											rstr.clear();
										}
										xt = sep->size();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												for (size_t xt = 0; xt < sep->size(); xt++)
												{
													if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord[xl], sizeof(_char)) || !memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord_[xl], sizeof(_char)))
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
														xt = sep->size();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														for (size_t xt = 0; xt < sep->size(); xt++)
														{
															if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord[xl], sizeof(_char)) || !memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord_[xl], sizeof(_char)))
															{
																if (ksep)
																{
																	for (; mk < x + sizeof(_char); mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}
																}
																else
																{
																	for (mk += sizeof(_char); mk < x; mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}
																}
																x += (sizeof(_char) - 1);
																mk = x + 1;
																xt = sep->size();
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										for (size_t xt = 0; xt < sep->size(); xt++)
										{
											if (!memcmp((void*)&val[x], (void*)&sep->at(xt), sizeof(_char)))
											{
												if (!x)
												{
													if (ksep)
													{
														std::string str;
														str.push_back(sep->at(xt));
														ret_->push_back(str);
													}
													x += sizeof(_char) - 1;
													mk = x + 1;
													xt = sep->size();
												}
												else
												{
													if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														x += sizeof(_char) - 1;
														mk = x + 1;

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}

														if (ksep)
														{
															std::string str;
															str.push_back(sep->at(xt));
															ret_->push_back(str);
														}
														xt = sep->size();
													}
													else
													{
														if (x > 1)
														{
															if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
															{
																for (; mk < x; mk++)
																{
																	rstr.push_back(val[mk]);
																}
																x += sizeof(_char) - 1;
																mk = x + 1;

																if (!rstr.empty())
																{
																	ret_->push_back(rstr);
																	rstr.clear();
																}

																if (ksep)
																{
																	std::string str;
																	str.push_back(sep->at(xt));
																	ret_->push_back(str);
																}
																xt = sep->size();
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
		}
		break;
	}
	case BOT_RTV_VCCHAR:
	{
		void* ptr = va_arg(args, void*);
		std::vector<c_char*>* sep = reinterpret_cast<std::vector<c_char*>*>(ptr);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									for (size_t xt = 0; xt < sep->size(); xt++)
									{
										size_t sl = bot_cstrlen(sep->at(xt));

										if (!strcmp(sep->at(xt), &msy.nrts_lit[xl]))
										{
											if (ksep)
											{
												for (; mk < x + sl; mk++)
												{
													rstr.push_back(val[mk]);
												}
												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											else
											{
												for (mk += sl; mk < x; mk++)
												{
													rstr.push_back(val[mk]);
												}
												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											x += (sl - 1);
											mk = x + 1;
											xt = sep->size();
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											for (size_t xt = 0; xt < sep->size(); xt++)
											{
												size_t sl = bot_cstrlen(sep->at(xt));

												if (!strcmp(sep->at(xt), &msy.nrts_lit[xl]))
												{
													if (ksep)
													{
														for (; mk < x + sl; mk++)
														{
															rstr.push_back(val[mk]);
														}
														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
													}
													else
													{
														for (mk += sl; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
													}
													x += (sl - 1);
													mk = x + 1;
													xt = sep->size();
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								for (size_t xt = 0; xt < sep->size(); xt++)
								{
									if (!strcmp(sep->at(xt), &msy.nrts_lit[xl]))
									{
										for (; mk < x; mk++)
										{
											rstr.push_back(val[mk]);
										}

										if (!rstr.empty())
										{
											ret_->push_back(rstr);
											rstr.clear();
										}
										xt = sep->size();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												for (size_t xt = 0; xt < sep->size(); xt++)
												{
													if (!strcmp(sep->at(xt), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt), &msy.nrts_ord_[xl]))
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
														xt = sep->size();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														for (size_t xt = 0; xt < sep->size(); xt++)
														{
															if (!strcmp(sep->at(xt), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt), &msy.nrts_ord_[xl]))
															{
																size_t sl = bot_cstrlen(sep->at(xt));

																if (ksep)
																{
																	for (; mk < x + sl; mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}
																}
																else
																{
																	for (mk += sl; mk < x; mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}
																}
																x += (sl - 1);
																mk = x + 1;
																xt = sep->size();
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										for (size_t xt = 0; xt < sep->size(); xt++)
										{
											if (!memcmp((void*)&val[x], (void*)&sep->at(xt)[0], sizeof(_char)))
											{
												if (!x)
												{
													size_t sl = bot_cstrlen(sep->at(xt));
													size_t y = 1;

													while (y < sl && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
														{
															y = sl;
														}
														y++;
													}

													if (y == sl)
													{
														if (ksep)
														{
															ret_->push_back(sep->at(xt));
														}
														x += (sl - 1);
														mk = x + 1;
														xt = sep->size();
													}
												}
												else
												{
													if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
													{
														size_t sl = bot_cstrlen(sep->at(xt));
														size_t y = 1;

														while (y < sl && x + y < t)
														{
															if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
															{
																y = sl;
															}
															y++;
														}

														if (y == sl)
														{
															for (; mk < x; mk++)
															{
																rstr.push_back(val[mk]);
															}
															x += (sl - 1);
															mk = x + 1;

															if (!rstr.empty())
															{
																ret_->push_back(rstr);
																rstr.clear();
															}

															if (ksep)
															{
																ret_->push_back(sep->at(xt));
															}
															xt = sep->size();
														}
													}
													else
													{
														if (x > 1)
														{
															if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
															{
																size_t sl = bot_cstrlen(sep->at(xt));
																size_t y = 1;

																while (y < sl && x + y < t)
																{
																	if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
																	{
																		y = sl;
																	}
																	y++;
																}

																if (y == sl)
																{
																	for (; mk < x; mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	x += (sl - 1);
																	mk = x + 1;

																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}

																	if (ksep)
																	{
																		ret_->push_back(sep->at(xt));
																	}
																	xt = sep->size();
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
			}
		}
		break;
	}
	case BOT_RTV_VSTR:
	{
		void* ptr = va_arg(args, void*);
		std::vector<std::string>* sep = reinterpret_cast<std::vector<std::string>*>(ptr);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									for (size_t xt = 0; xt < sep->size(); xt++)
									{
										if (!strcmp(sep->at(xt).c_str(), &msy.nrts_lit[xl]))
										{
											if (ksep)
											{
												for (; mk < x + sep->at(xt).length(); mk++)
												{
													rstr.push_back(val[mk]);
												}
												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											else
											{
												for (mk += sep->at(xt).length(); mk < x; mk++)
												{
													rstr.push_back(val[mk]);
												}
												if (!rstr.empty())
												{
													ret_->push_back(rstr);
													rstr.clear();
												}
											}
											x += (sep->at(xt).length() - 1);
											mk = x + 1;
											xt = sep->size();
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											for (size_t xt = 0; xt < sep->size(); xt++)
											{
												if (!strcmp(sep->at(xt).c_str(), &msy.nrts_lit[xl]))
												{
													if (ksep)
													{
														for (; mk < x + sep->at(xt).length(); mk++)
														{
															rstr.push_back(val[mk]);
														}
														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
													}
													else
													{
														for (mk += sep->at(xt).length(); mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}
														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
													}
													x += (sep->at(xt).length() - 1);
													mk = x + 1;
													xt = sep->size();
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								for (size_t xt = 0; xt < sep->size(); xt++)
								{
									if (!strcmp(sep->at(xt).c_str(), &msy.nrts_lit[xl]))
									{
										for (; mk < x; mk++)
										{
											rstr.push_back(val[mk]);
										}

										if (!rstr.empty())
										{
											ret_->push_back(rstr);
											rstr.clear();
										}
										xt = sep->size();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												for (size_t xt = 0; xt < sep->size(); xt++)
												{
													if (!strcmp(sep->at(xt).c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt).c_str(), &msy.nrts_ord_[xl]))
													{
														for (; mk < x; mk++)
														{
															rstr.push_back(val[mk]);
														}

														if (!rstr.empty())
														{
															ret_->push_back(rstr);
															rstr.clear();
														}
														xt = sep->size();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														for (size_t xt = 0; xt < sep->size(); xt++)
														{
															if (!strcmp(sep->at(xt).c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt).c_str(), &msy.nrts_ord_[xl]))
															{
																if (ksep)
																{
																	for (; mk < x + sep->at(xt).length(); mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}
																}
																else
																{
																	for (mk += sep->at(xt).length(); mk < x; mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}
																}
																x += (sep->at(xt).length() - 1);
																mk = x + 1;
																xt = sep->size();
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										for (size_t xt = 0; xt < sep->size(); xt++)
										{
											if (!memcmp((void*)&val[x], (void*)&sep->at(xt)[0], sizeof(_char)))
											{
												if (!x)
												{
													size_t y = 1;

													while (y < sep->at(xt).length() && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
														{
															y = sep->at(xt).length();
														}
														y++;
													}

													if (y == sep->at(xt).length())
													{
														if (ksep)
														{
															ret_->push_back(sep->at(xt));
														}
														x += (sep->at(xt).length() - 1);
														mk = x + 1;
														xt = sep->size();
													}
												}
												else
												{
													if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
													{
														size_t y = 1;

														while (y < sep->at(xt).length() && x + y < t)
														{
															if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
															{
																y = sep->at(xt).length();
															}
															y++;
														}

														if (y == sep->at(xt).length())
														{
															for (; mk < x; mk++)
															{
																rstr.push_back(val[mk]);
															}
															x += (sep->at(xt).length() - 1);
															mk = x + 1;

															if (!rstr.empty())
															{
																ret_->push_back(rstr);
																rstr.clear();
															}

															if (ksep)
															{
																ret_->push_back(sep->at(xt));
															}
															xt = sep->size();
														}
													}
													else
													{
														if (x > 1)
														{
															if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
															{
																size_t y = 1;

																while (y < sep->at(xt).length() && x + y < t)
																{
																	if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
																	{
																		y = sep->at(xt).length();
																	}
																	y++;
																}

																if (y == sep->at(xt).length())
																{
																	for (; mk < x; mk++)
																	{
																		rstr.push_back(val[mk]);
																	}
																	x += (sep->at(xt).length() - 1);
																	mk = x + 1;

																	if (!rstr.empty())
																	{
																		ret_->push_back(rstr);
																		rstr.clear();
																	}

																	if (ksep)
																	{
																		ret_->push_back(sep->at(xt));
																	}
																	xt = sep->size();
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
			}
		}
		break;
	}
	default:
	{
		break;
	}
	}
	for (; mk < t + 1; mk++)
	{
		rstr.push_back(val[mk]);
	}
	if (!rstr.empty())
	{
		ret_->push_back(rstr);
	}
	if (lit > -1)
	{
		ret = bot_sprintfs(&rstr, true, "Open literal '%c' at: %u", msy.nrts_lit[lit], (uint)litloc);
		ret_->push_back(rstr);
		ret = -1;
	}
	else if (!ord.empty())
	{
		ret = bot_sprintfs(&rstr, true, "Open bracket '%c' at: %u", msy.nrts_ord[ord[0]], (uint)ordl[0]);
		ret_->push_back(rstr);
		ret = -1;
	}
	else
	{
		ret = 0;
	}
	va_end(args);
	return ret;
}
sint machine::ArgSep(std::vector <BOT_ARG>* ret_, bool ksep, size_t f, size_t t, c_char* val, ...)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::ArgSep(std::vector <BOT_ARG>* ret_(%i), bool ksep(%u), size_t f(%u), size_t t(%u), c_char* val(%s), ...)", (sint)ret_, (uint)ksep, f, t, (sint)val);
		op = Output(outp.carr, 2);
	}

	if (!ret_ || !val)
	{
		return -1;
	}
	else
	{
		size_t ret = (size_t)bot_cstrchk(val);

		if (!ret || ret > (sint)BOT_STRLEN_MAX)
		{
			BOT_ARG a;
			ret = (size_t)bot_sprintfs(&a.arg, false, "Bad Size: len: %u", ret);
			ret_->push_back(a);
			return -1;
		}

		if (!t || t > ret - 1 || t < f)
		{
			t = ret - 1;
		}
	}

	slint lign = -1;
	slint lit = -1;
	slint litloc = 0;
	std::vector<size_t> ord;
	std::vector<size_t> ordl;
	size_t mk = f;
	sint ig = (sint)'\\';
	sint ret = -1;
	sint typ = BOT_RTV_MAX;
	BOT_ARG a((sllint)f);
	va_list args;
	va_start(args, val);
	typ = va_arg(args, sint);

	switch (typ)
	{
	case BOT_RTV_SINT:
	{
		sint sep = va_arg(args, sint);
		size_t sl = sizeof(sint);
		
		for (size_t x = f; x < t + 1; x++)
		{
			if (lit > -1)
			{
				for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
				{
					if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
					{
						if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
						{
							if (lit == (slint)xl)
							{
								if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
								{
									if (ksep)
									{
										a.loc = (sllint)mk;

										for (; mk < x + sl; mk++)
										{
											a.arg.push_back(val[mk]);
										}

										if (!a.arg.empty())
										{
											ret_->push_back(a);
											a.arg.clear();
										}

										x += (sl - 1);
										mk = x + 1;
									}
									else
									{
										a.loc = (sllint)mk + sl;

										for (mk += sl; mk < x; mk++)
										{
											a.arg.push_back(val[mk]);
										}

										if (!a.arg.empty())
										{
											ret_->push_back(a);
											a.arg.clear();
										}

										x += (sl - 1);
										mk = x + 1;
									}
								}
								lit = -1;
								litloc = (slint)x;
							}
							xl = msy.nrts_lit.size();
						}
						else
						{
							if (x > 1)
							{
								if (!memcmp((void*)&ig, (void*)&val[x - 2], sl))
								{
									if (lit == (slint)xl)
									{
										if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
										{
											if (ksep)
											{
												a.loc = (sllint)mk;

												for (; mk < x + sl; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;
											}
											else
											{
												a.loc = (sllint)mk + sl;

												for (mk += sl; mk < x; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;
											}
										}
										lit = -1;
										litloc = (slint)x;
									}
									xl = msy.nrts_lit.size();
								}
							}
						}
					}
				}
			}
			else
			{
				if (lign > -1)
				{
					for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
					{
						if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sl))
						{
							size_t zl = 0;

							while (zl < msy.nrts_lign_[yl].length() && zl < t)
							{
								if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sl))
								{
									zl = msy.nrts_lign_[yl].length();
								}
								zl++;
							}

							if (zl == msy.nrts_lign_[yl].length())
							{
								if (lign == (slint)yl)
								{
									lign = -1;
									yl = msy.nrts_lign_.size();
								}
							}
						}
					}
				}
				if (lign < 0)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
						{
							if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
							{
								a.loc = (sllint)mk;

								for (; mk < xl; mk++)
								{
									a.arg.push_back(val[mk]);
								}

								if (!a.arg.empty())
								{
									ret_->push_back(a);
									a.arg.clear();
								}
							}
							lit = (slint)xl;
							litloc = (slint)x;
							xl = msy.nrts_lit.size();
						}
					}
					if (lit < 0)
					{
						if (lign < 0)
						{
							for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
							{
								if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sl))
								{
									size_t zl = 0;

									while (zl < msy.nrts_lign[yl].length() && zl < t)
									{
										if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sl))
										{
											zl = msy.nrts_lign[yl].length();
										}
										zl++;
									}

									if (zl == msy.nrts_lign[yl].length())
									{
										lign = (slint)yl;
										yl = msy.nrts_lign.size();
									}
								}
							}
							if (lign < 0)
							{
								for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
								{
									if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sl))
									{
										if (ord.empty())
										{
											if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
											{
												a.loc = (sllint)mk;

												for (; mk < x; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}
											}
										}
										ord.push_back(xl);
										ordl.push_back(x);
										xl = msy.nrts_ord.size();
									}
								}
								if (!ord.empty())
								{
									for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sl))
										{
											if (ord[ord.size() - 1] == xl)
											{
												ord.pop_back();
												ordl.pop_back();

												if (ord.empty())
												{
													if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
													{
														if (ksep)
														{
															a.loc = (sllint)mk;

															for (; mk < x + sl; mk++)
															{
																a.arg.push_back(val[mk]);
															}

															if (!a.arg.empty())
															{
																ret_->push_back(a);
																a.arg.clear();
															}

															x += (sl - 1);
															mk = x + 1;
														}
														else
														{
															a.loc = (sllint)mk + sl;

															for (mk += sl; mk < x; mk++)
															{
																a.arg.push_back(val[mk]);
															}

															if (!a.arg.empty())
															{
																ret_->push_back(a);
																a.arg.clear();
															}

															x += (sl - 1);
															mk = x + 1;
														}
													}
												}
											}
											xl = msy.nrts_ord_.size();
										}
									}
								}
								else
								{
									if (!memcmp((void*)&val[x], (void*)&sep, sl))
									{
										if (!x)
										{
											if (ksep)
											{
												a.loc = (sllint)mk;
												a.arg.push_back(sep);
												ret_->push_back(a);
												a.arg.clear();
											}
											x += sl - 1;
											mk = x + 1;
										}
										else
										{
											if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
											{
												a.loc = (sllint)mk;

												for (; mk < x; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;

												if (ksep)
												{
													a.loc = (sllint)mk;
													a.arg.push_back(sep);
													ret_->push_back(a);
													a.arg.clear();
												}
											}
											else
											{
												if (x > 1)
												{
													if (memcmp((void*)&ig, (void*)&val[x - 2], sl))
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sl - 1);
														mk = x + 1;

														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.push_back(sep);
															ret_->push_back(a);
															a.arg.clear();
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
		break;
	}
	case BOT_RTV_CHAR:
	{
		sint ptr = va_arg(args, sint);
		_char sep = (_char)ptr;

		if (sep)
		{
			size_t sl = sizeof(_char);

			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
							{
								if (lit == (slint)xl)
								{
									if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
									{
										if (ksep)
										{
											a.loc = (sllint)mk;

											for (; mk < x + sl; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sl - 1);
											mk = x + 1;
										}
										else
										{
											a.loc = (sllint)mk + sl;

											for (mk += sl; mk < x; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sl - 1);
											mk = x + 1;
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sl))
									{
										if (lit == (slint)xl)
										{
											if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
											{
												if (ksep)
												{
													a.loc = (sllint)mk;

													for (; mk < x + sl; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;
												}
												else
												{
													a.loc = (sllint)mk + sl;

													for (mk += sl; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sl))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sl))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sl))
							{
								if (!memcmp((void*)&sep, (void*)&msy.nrts_lit[xl], sl))
								{
									a.loc = (sllint)mk;

									for (; mk < x; mk++)
									{
										a.arg.push_back(val[mk]);
									}

									if (!a.arg.empty())
									{
										ret_->push_back(a);
										a.arg.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sl))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sl))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sl))
										{
											if (ord.empty())
											{
												if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
												{
													a.loc = (sllint)mk;

													for (; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sl))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!memcmp((void*)&sep, (void*)&msy.nrts_ord[xl], sl) || !memcmp((void*)&sep, (void*)&msy.nrts_ord_[xl], sl))
														{
															if (ksep)
															{
																a.loc = (sllint)mk;

																for (; mk < x + sl; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;
															}
															else
															{
																a.loc = (sllint)mk + sl;

																for (mk += sl; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep, sl))
										{
											if (!x)
											{
												if (ksep)
												{
													a.loc = (sllint)mk;
													a.arg.push_back(sep);
													ret_->push_back(a);
													a.arg.clear();
												}
												x += sl - 1;
												mk = x + 1;
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sl))
												{
													a.loc = (sllint)mk;

													for (; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;

													if (ksep)
													{
														a.loc = (sllint)mk;
														a.arg.push_back(sep);
														ret_->push_back(a);
														a.arg.clear();
													}
												}
												else
												{
													if (x > 1)
													{
														if (memcmp((void*)&ig, (void*)&val[x - 2], sl))
														{
															a.loc = (sllint)mk;

															for (; mk < x; mk++)
															{
																a.arg.push_back(val[mk]);
															}

															if (!a.arg.empty())
															{
																ret_->push_back(a);
																a.arg.clear();
															}

															x += (sl - 1);
															mk = x + 1;

															if (ksep)
															{
																a.loc = (sllint)mk;
																a.arg.push_back(sep);
																ret_->push_back(a);
																a.arg.clear();
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
		}
		break;
	}
	case BOT_RTV_CHARP:
	{
		void* ptr = va_arg(args, void*);
		_char* sep = reinterpret_cast<_char*>(ptr);

		if (sep)
		{
			size_t sl = bot_strlen(sep);

			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									if (!strcmp(sep, &msy.nrts_lit[xl]))
									{
										if (ksep)
										{
											a.loc = (sllint)mk;

											for (; mk < x + sl; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sl - 1);
											mk = x + 1;
										}
										else
										{
											a.loc = (sllint)mk + sl;

											for (mk += sl; mk < x; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sl - 1);
											mk = x + 1;
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											if (!strcmp(sep, &msy.nrts_lit[xl]))
											{
												if (ksep)
												{
													a.loc = (sllint)mk;

													for (; mk < x + sl; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;
												}
												else
												{
													a.loc = (sllint)mk + sl;

													for (mk += sl; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								if (!strcmp(sep, &msy.nrts_lit[xl]))
								{
									a.loc = (sllint)mk;

									for (; mk < x; mk++)
									{
										a.arg.push_back(val[mk]);
									}

									if (!a.arg.empty())
									{
										ret_->push_back(a);
										a.arg.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
												{
													a.loc = (sllint)mk;

													for (; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
														{
															if (ksep)
															{
																a.loc = (sllint)mk;

																for (; mk < x + sl; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;
															}
															else
															{
																a.loc = (sllint)mk + sl;

																for (mk += sl; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep[0], sizeof(_char)))
										{
											if (!x)
											{
												size_t y = 1;

												while (y < sl && x + y < t)
												{
													if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
													{
														y = sl;
													}
													y++;
												}

												if (y == sl)
												{
													if (ksep)
													{
														a.loc = (sllint)mk;
														a.arg.append(sep);
														ret_->push_back(a);
														a.arg.clear();
													}
													x += sl - 1;
													mk = x + 1;
												}
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
												{
													size_t y = 1;

													while (y < sl && x + y < t)
													{
														if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
														{
															y = sl;
														}
														y++;
													}

													if (y == sl)
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sl - 1);
														mk = x + 1;

														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.append(sep);
															ret_->push_back(a);
															a.arg.clear();
														}
													}
												}
												else
												{
													if (x > 1)
													{
														if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
														{
															size_t y = 1;

															while (y < sl && x + y < t)
															{
																if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
																{
																	y = sl;
																}
																y++;
															}

															if (y == sl)
															{
																a.loc = (sllint)mk;

																for (; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;

																if (ksep)
																{
																	a.loc = (sllint)mk;
																	a.arg.append(sep);
																	ret_->push_back(a);
																	a.arg.clear();
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
			}
		}
		break;
	}
	case BOT_RTV_CCHAR:
	{
		void* ptr = va_arg(args, void*);
		c_char* sep = reinterpret_cast<c_char*>(ptr);

		if (sep)
		{
			size_t sl = bot_cstrlen(sep);

			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									if (!strcmp(sep, &msy.nrts_lit[xl]))
									{
										if (ksep)
										{
											a.loc = (sllint)mk;

											for (; mk < x + sl; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sl - 1);
											mk = x + 1;
										}
										else
										{
											a.loc = (sllint)mk + sl;

											for (mk += sl; mk < x; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sl - 1);
											mk = x + 1;
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											if (!strcmp(sep, &msy.nrts_lit[xl]))
											{
												if (ksep)
												{
													a.loc = (sllint)mk;

													for (; mk < x + sl; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;
												}
												else
												{
													a.loc = (sllint)mk + sl;

													for (mk += sl; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sl - 1);
													mk = x + 1;
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								if (!strcmp(sep, &msy.nrts_lit[xl]))
								{
									a.loc = (sllint)mk;

									for (; mk < x; mk++)
									{
										a.arg.push_back(val[mk]);
									}

									if (!a.arg.empty())
									{
										ret_->push_back(a);
										a.arg.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
												{
													a.loc = (sllint)mk;

													for (; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!strcmp(sep, &msy.nrts_ord[xl]) || !strcmp(sep, &msy.nrts_ord_[xl]))
														{
															if (ksep)
															{
																a.loc = (sllint)mk;

																for (; mk < x + sl; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;
															}
															else
															{
																a.loc = (sllint)mk + sl;

																for (mk += sl; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sl - 1);
																mk = x + 1;
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep[0], sizeof(_char)))
										{
											if (!x)
											{
												size_t y = 1;

												while (y < sl && x + y < t)
												{
													if (memcmp((void*)&val[x + y], &sep[y], sizeof(_char)))
													{
														y = sl;
													}
													y++;
												}

												if (y == sl)
												{
													if (ksep)
													{
														a.loc = (sllint)mk;
														a.arg.append(sep);
														ret_->push_back(a);
														a.arg.clear();
													}
													x += sl - 1;
													mk = x + 1;
												}
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
												{
													size_t y = 1;

													while (y < sl && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep[y], sizeof(_char)))
														{
															y = sl;
														}
														y++;
													}

													if (y == sl)
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}
														x += (sl - 1);
														mk = x + 1;

														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.append(sep);
															ret_->push_back(a);
															a.arg.clear();
														}
													}
												}
												else
												{
													if (x > 1)
													{
														if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
														{
															size_t y = 1;

															while (y < sl && x + y < t)
															{
																if (memcmp((void*)&val[x + y], (void*)&sep[y], sizeof(_char)))
																{
																	y = sl;
																}
																y++;
															}

															if (y == sl)
															{
																a.loc = (sllint)mk;

																for (; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}
																x += (sl - 1);
																mk = x + 1;

																if (ksep)
																{
																	a.loc = (sllint)mk;
																	a.arg.append(sep);
																	ret_->push_back(a);
																	a.arg.clear();
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
			}
		}
		break;
	}
	case BOT_RTV_STR:
	{
		void* ptr = va_arg(args, void*);
		std::string* sep = reinterpret_cast<std::string*>(ptr);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									if (!strcmp(sep->c_str(), &msy.nrts_lit[xl]))
									{
										if (ksep)
										{
											a.loc = (sllint)mk;

											for (; mk < x + sep->length(); mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sep->length() - 1);
											mk = x + 1;
										}
										else
										{
											a.loc = (sllint)mk + sep->length();

											for (mk += sep->length(); mk < x; mk++)
											{
												a.arg.push_back(val[mk]);
											}

											if (!a.arg.empty())
											{
												ret_->push_back(a);
												a.arg.clear();
											}

											x += (sep->length() - 1);
											mk = x + 1;
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											if (!strcmp(sep->c_str(), &msy.nrts_lit[xl]))
											{
												if (ksep)
												{
													a.loc = (sllint)mk;

													for (; mk < x + sep->length(); mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sep->length() - 1);
													mk = x + 1;
												}
												else
												{
													a.loc = (sllint)mk + sep->length();

													for (mk += sep->length(); mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}

													x += (sep->length() - 1);
													mk = x + 1;
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								if (!strcmp(sep->c_str(), &msy.nrts_lit[xl]))
								{
									a.loc = (sllint)mk;

									for (; mk < x; mk++)
									{
										a.arg.push_back(val[mk]);
									}

									if (!a.arg.empty())
									{
										ret_->push_back(a);
										a.arg.clear();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												if (!strcmp(sep->c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->c_str(), &msy.nrts_ord_[xl]))
												{
													a.loc = (sllint)mk;

													for (; mk < x; mk++)
													{
														a.arg.push_back(val[mk]);
													}

													if (!a.arg.empty())
													{
														ret_->push_back(a);
														a.arg.clear();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														if (!strcmp(sep->c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->c_str(), &msy.nrts_ord_[xl]))
														{
															if (ksep)
															{
																a.loc = (sllint)mk;

																for (; mk < x + sep->length(); mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sep->length() - 1);
																mk = x + 1;
															}
															else
															{
																a.loc = (sllint)mk + sep->length();

																for (mk += sep->length(); mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}

																x += (sep->length() - 1);
																mk = x + 1;
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										if (!memcmp((void*)&val[x], (void*)&sep->at(0), sizeof(_char)))
										{
											if (!x)
											{
												size_t y = 1;

												while (y < sep->length() && x + y < t)
												{
													if (memcmp((void*)&val[x + y], &sep->at(y), sizeof(_char)))
													{
														y = sep->length();
													}
													y++;
												}

												if (y == sep->length())
												{
													if (ksep)
													{
														a.loc = (sllint)mk;
														a.arg.append(sep->c_str());
														ret_->push_back(a);
														a.arg.clear();
													}
													x += sep->length() - 1;
													mk = x + 1;
												}
											}
											else
											{
												if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
												{
													size_t y = 1;

													while (y < sep->length() && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep->at(y), sizeof(_char)))
														{
															y = sep->length();
														}
														y++;
													}

													if (y == sep->length())
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}
														x += (sep->length() - 1);
														mk = x + 1;

														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.append(sep->c_str());
															ret_->push_back(a);
															a.arg.clear();
														}
													}
												}
												else
												{
													if (x > 1)
													{
														if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
														{
															size_t y = 1;

															while (y < sep->length() && x + y < t)
															{
																if (memcmp((void*)&val[x + y], &sep->at(y), sizeof(_char)))
																{
																	y = sep->length();
																}
																y++;
															}

															if (y == sep->length())
															{
																a.loc = (sllint)mk;

																for (; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}
																x += (sep->length() - 1);
																mk = x + 1;

																if (ksep)
																{
																	a.loc = (sllint)mk;
																	a.arg.append(sep->c_str());
																	ret_->push_back(a);
																	a.arg.clear();
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
			}
		}
		break;
	}
	case BOT_RTV_VCHAR:
	{
		void* ptr = va_arg(args, void*);
		std::vector<_char>* sep = reinterpret_cast<std::vector<_char>*>(ptr);

		if (sep)
		{
			size_t sl = sizeof(_char);
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									for (size_t xt = 0; xt < sep->size(); xt++)
									{
										if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_lit[xl], sizeof(_char)))
										{
											if (ksep)
											{
												a.loc = (sllint)mk;

												for (; mk < x + sl; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;
											}
											else
											{
												a.loc = (sllint)mk + sl;

												for (mk += sl; mk < x; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;
											}
											xt = sep->size();
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											for (size_t xt = 0; xt < sep->size(); xt++)
											{
												if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_lit[xl], sizeof(_char)))
												{
													if (ksep)
													{
														a.loc = (sllint)mk;

														for (; mk < x + sl; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sl - 1);
														mk = x + 1;
													}
													else
													{
														a.loc = (sllint)mk + sl;

														for (mk += sl; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sl - 1);
														mk = x + 1;
													}
													xt = sep->size();
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								for (size_t xt = 0; xt < sep->size(); xt++)
								{
									if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_lit[xl], sizeof(_char)))
									{
										a.loc = (sllint)mk;

										for (; mk < x; mk++)
										{
											a.arg.push_back(val[mk]);
										}

										if (!a.arg.empty())
										{
											ret_->push_back(a);
											a.arg.clear();
										}
										xt = sep->size();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												for (size_t xt = 0; xt < sep->size(); xt++)
												{
													if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord[xl], sizeof(_char)) || !memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord_[xl], sizeof(_char)))
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}
														xt = sep->size();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														for (size_t xt = 0; xt < sep->size(); xt++)
														{
															if (!memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord[xl], sizeof(_char)) || !memcmp((void*)&sep->at(xt), (void*)&msy.nrts_ord_[xl], sizeof(_char)))
															{
																if (ksep)
																{
																	a.loc = (sllint)mk;

																	for (; mk < x + sl; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}

																	x += (sl - 1);
																	mk = x + 1;
																}
																else
																{
																	a.loc = (sllint)mk + sl;

																	for (mk += sl; mk < x; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}

																	x += (sl - 1);
																	mk = x + 1;
																}
																xt = sep->size();
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										for (size_t xt = 0; xt < sep->size(); xt++)
										{
											if (!memcmp((void*)&val[x], (void*)&sep->at(xt), sizeof(_char)))
											{
												if (!x)
												{
													if (ksep)
													{
														a.loc = (sllint)mk;
														a.arg.push_back(sep->at(xt));
														ret_->push_back(a);
														a.arg.clear();
													}
													x += sizeof(_char) - 1;
													mk = x + 1;
													xt = sep->size();
												}
												else
												{
													if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}
														x += (sizeof(_char) - 1);
														mk = x + 1;

														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.push_back(sep->at(xt));
															ret_->push_back(a);
															a.arg.clear();
														}
														xt = sep->size();
													}
													else
													{
														if (x > 1)
														{
															if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
															{
																a.loc = (sllint)mk;

																for (; mk < x; mk++)
																{
																	a.arg.push_back(val[mk]);
																}

																if (!a.arg.empty())
																{
																	ret_->push_back(a);
																	a.arg.clear();
																}
																x += (sizeof(_char) - 1);
																mk = x + 1;

																if (ksep)
																{
																	a.loc = (sllint)mk;
																	a.arg.push_back(sep->at(xt));
																	ret_->push_back(a);
																	a.arg.clear();
																}
																xt = sep->size();
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
		}
		break;
	}
	case BOT_RTV_VCCHAR:
	{
		void* ptr = va_arg(args, void*);
		std::vector<c_char*>* sep = reinterpret_cast<std::vector<c_char*>*>(ptr);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									for (size_t xt = 0; xt < sep->size(); xt++)
									{
										size_t sl = bot_cstrlen(sep->at(xt));

										if (!strcmp(sep->at(xt), &msy.nrts_lit[xl]))
										{
											if (ksep)
											{
												a.loc = (sllint)mk;

												for (; mk < x + sl; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;
											}
											else
											{
												a.loc = (sllint)mk + sl;

												for (mk += sl; mk < x; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sl - 1);
												mk = x + 1;
											}
											xt = sep->size();
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											for (size_t xt = 0; xt < sep->size(); xt++)
											{
												size_t sl = bot_cstrlen(sep->at(xt));

												if (!strcmp(sep->at(xt), &msy.nrts_lit[xl]))
												{
													if (ksep)
													{
														a.loc = (sllint)mk;

														for (; mk < x + sl; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sl - 1);
														mk = x + 1;
													}
													else
													{
														a.loc = (sllint)mk + sl;

														for (mk += sl; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sl - 1);
														mk = x + 1;
													}
													xt = sep->size();
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								for (size_t xt = 0; xt < sep->size(); xt++)
								{
									if (!strcmp(sep->at(xt), &msy.nrts_lit[xl]))
									{
										a.loc = (sllint)mk;

										for (; mk < x; mk++)
										{
											a.arg.push_back(val[mk]);
										}

										if (!a.arg.empty())
										{
											ret_->push_back(a);
											a.arg.clear();
										}
										xt = sep->size();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												for (size_t xt = 0; xt < sep->size(); xt++)
												{
													if (!strcmp(sep->at(xt), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt), &msy.nrts_ord_[xl]))
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}
														xt = sep->size();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														for (size_t xt = 0; xt < sep->size(); xt++)
														{
															if (!strcmp(sep->at(xt), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt), &msy.nrts_ord_[xl]))
															{
																size_t sl = bot_cstrlen(sep->at(xt));
																if (ksep)
																{
																	a.loc = (sllint)mk;

																	for (; mk < x + sl; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}

																	x += (sl - 1);
																	mk = x + 1;
																}
																else
																{
																	a.loc = (sllint)mk + sl;

																	for (mk += sl; mk < x; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}

																	x += (sl - 1);
																	mk = x + 1;
																}
																xt = sep->size();
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										for (size_t xt = 0; xt < sep->size(); xt++)
										{
											if (!memcmp((void*)&val[x], (void*)&sep->at(xt)[0], sizeof(_char)))
											{
												if (!x)
												{
													size_t sl = bot_cstrlen(sep->at(xt));
													size_t y = 1;

													while (y < sl && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
														{
															y = sl;
														}
														y++;
													}

													if (y == sl)
													{
														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.append(sep->at(xt));
															ret_->push_back(a);
															a.arg.clear();
														}
														x += (sl - 1);
														mk = x + 1;
														xt = sep->size();
													}
												}
												else
												{
													if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
													{
														size_t sl = bot_cstrlen(sep->at(xt));
														size_t y = 1;

														while (y < sl && x + y < t)
														{
															if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
															{
																y = sl;
															}
															y++;
														}

														if (y == sl)
														{
															a.loc = (sllint)mk;

															for (; mk < x; mk++)
															{
																a.arg.push_back(val[mk]);
															}

															if (!a.arg.empty())
															{
																ret_->push_back(a);
																a.arg.clear();
															}
															x += (sl - 1);
															mk = x + 1;

															if (ksep)
															{
																a.loc = (sllint)mk;
																a.arg.append(sep->at(xt));
																ret_->push_back(a);
																a.arg.clear();
															}
															xt = sep->size();
														}
													}
													else
													{
														if (x > 1)
														{
															if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
															{
																size_t sl = bot_cstrlen(sep->at(xt));
																size_t y = 1;

																while (y < sl && x + y < t)
																{
																	if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
																	{
																		y = sl;
																	}
																	y++;
																}

																if (y == sl)
																{
																	a.loc = (sllint)mk;

																	for (; mk < x; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}
																	x += (sl - 1);
																	mk = x + 1;

																	if (ksep)
																	{
																		a.loc = (sllint)mk;
																		a.arg.append(sep->at(xt));
																		ret_->push_back(a);
																		a.arg.clear();
																	}
																	xt = sep->size();
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
			}
		}
		break;
	}
	case BOT_RTV_VSTR:
	{
		void* ptr = va_arg(args, void*);
		std::vector<std::string>* sep = reinterpret_cast<std::vector<std::string>*>(ptr);

		if (sep)
		{
			for (size_t x = f; x < t + 1; x++)
			{
				if (lit > -1)
				{
					for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
					{
						if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
						{
							if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
							{
								if (lit == (slint)xl)
								{
									for (size_t xt = 0; xt < sep->size(); xt++)
									{
										if (!strcmp(sep->at(xt).c_str(), &msy.nrts_lit[xl]))
										{
											if (ksep)
											{
												a.loc = (sllint)mk;

												for (; mk < x + sep->at(xt).length(); mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sep->at(xt).length() - 1);
												mk = x + 1;
											}
											else
											{
												a.loc = (sllint)mk + sep->at(xt).length();

												for (mk += sep->at(xt).length(); mk < x; mk++)
												{
													a.arg.push_back(val[mk]);
												}

												if (!a.arg.empty())
												{
													ret_->push_back(a);
													a.arg.clear();
												}

												x += (sep->at(xt).length() - 1);
												mk = x + 1;
											}
											xt = sep->size();
										}
									}
									lit = -1;
									litloc = (slint)x;
								}
								xl = msy.nrts_lit.size();
							}
							else
							{
								if (x > 1)
								{
									if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
									{
										if (lit == (slint)xl)
										{
											for (size_t xt = 0; xt < sep->size(); xt++)
											{
												if (!strcmp(sep->at(xt).c_str(), &msy.nrts_lit[xl]))
												{
													if (ksep)
													{
														a.loc = (sllint)mk;

														for (; mk < x + sep->at(xt).length(); mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sep->at(xt).length() - 1);
														mk = x + 1;
													}
													else
													{
														a.loc = (sllint)mk + sep->at(xt).length();

														for (mk += sep->at(xt).length(); mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}

														x += (sep->at(xt).length() - 1);
														mk = x + 1;
													}
													xt = sep->size();
												}
											}
											lit = -1;
											litloc = (slint)x;
										}
										xl = msy.nrts_lit.size();
									}
								}
							}
						}
					}
				}
				else
				{
					if (lign > -1)
					{
						for (size_t yl = 0; yl < msy.nrts_lign_.size(); yl++)
						{
							if (!memcmp((void*)&msy.nrts_lign_[yl][0], (void*)&val[x], sizeof(_char)))
							{
								size_t zl = 0;

								while (zl < msy.nrts_lign_[yl].length() && zl < t)
								{
									if (memcmp((void*)&msy.nrts_lign_[yl][zl], (void*)&val[x + zl], sizeof(_char)))
									{
										zl = msy.nrts_lign_[yl].length();
									}
									zl++;
								}

								if (zl == msy.nrts_lign_[yl].length())
								{
									if (lign == (slint)yl)
									{
										lign = -1;
										yl = msy.nrts_lign_.size();
									}
								}
							}
						}
					}
					if (lign < 0)
					{
						for (size_t xl = 0; xl < msy.nrts_lit.size(); xl++)
						{
							if (!memcmp((void*)&msy.nrts_lit[xl], (void*)&val[x], sizeof(_char)))
							{
								for (size_t xt = 0; xt < sep->size(); xt++)
								{
									if (!strcmp(sep->at(xt).c_str(), &msy.nrts_lit[xl]))
									{
										a.loc = (sllint)mk;

										for (; mk < x; mk++)
										{
											a.arg.push_back(val[mk]);
										}

										if (!a.arg.empty())
										{
											ret_->push_back(a);
											a.arg.clear();
										}
										xt = sep->size();
									}
								}
								lit = (slint)xl;
								litloc = (slint)x;
								xl = msy.nrts_lit.size();
							}
						}
						if (lit < 0)
						{
							if (lign < 0)
							{
								for (size_t yl = 0; yl < msy.nrts_lign.size(); yl++)
								{
									if (!memcmp((void*)&msy.nrts_lign[yl][0], (void*)&val[x], sizeof(_char)))
									{
										size_t zl = 0;

										while (zl < msy.nrts_lign[yl].length() && zl < t)
										{
											if (memcmp((void*)&msy.nrts_lign[yl][zl], (void*)&val[x + zl], sizeof(_char)))
											{
												zl = msy.nrts_lign[yl].length();
											}
											zl++;
										}

										if (zl == msy.nrts_lign[yl].length())
										{
											lign = (slint)yl;
											yl = msy.nrts_lign.size();
										}
									}
								}
								if (lign < 0)
								{
									for (size_t xl = 0; xl < msy.nrts_ord.size(); xl++)
									{
										if (!memcmp((void*)&msy.nrts_ord[xl], (void*)&val[x], sizeof(_char)))
										{
											if (ord.empty())
											{
												for (size_t xt = 0; xt < sep->size(); xt++)
												{
													if (!strcmp(sep->at(xt).c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt).c_str(), &msy.nrts_ord_[xl]))
													{
														a.loc = (sllint)mk;

														for (; mk < x; mk++)
														{
															a.arg.push_back(val[mk]);
														}

														if (!a.arg.empty())
														{
															ret_->push_back(a);
															a.arg.clear();
														}
														xt = sep->size();
													}
												}
											}
											ord.push_back(xl);
											ordl.push_back(x);
											xl = msy.nrts_ord.size();
										}
									}
									if (!ord.empty())
									{
										for (size_t xl = 0; xl < msy.nrts_ord_.size(); xl++)
										{
											if (!memcmp((void*)&msy.nrts_ord_[xl], (void*)&val[x], sizeof(_char)))
											{
												if (ord[ord.size() - 1] == xl)
												{
													ord.pop_back();
													ordl.pop_back();

													if (ord.empty())
													{
														for (size_t xt = 0; xt < sep->size(); xt++)
														{
															if (!strcmp(sep->at(xt).c_str(), &msy.nrts_ord[xl]) || !strcmp(sep->at(xt).c_str(), &msy.nrts_ord_[xl]))
															{
																if (ksep)
																{
																	a.loc = (sllint)mk;

																	for (; mk < x + sep->at(xt).length(); mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}

																	x += (sep->at(xt).length() - 1);
																	mk = x + 1;
																}
																else
																{
																	a.loc = (sllint)mk + sep->at(xt).length();

																	for (mk += sep->at(xt).length(); mk < x; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}

																	x += (sep->at(xt).length() - 1);
																	mk = x + 1;
																}
																xt = sep->size();
															}
														}
													}
												}
												xl = msy.nrts_ord_.size();
											}
										}
									}
									else
									{
										for (size_t xt = 0; xt < sep->size(); xt++)
										{
											if (!memcmp((void*)&val[x], (void*)&sep->at(xt)[0], sizeof(_char)))
											{
												if (!x)
												{
													size_t y = 1;

													while (y < sep->at(xt).length() && x + y < t)
													{
														if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
														{
															y = sep->at(xt).length();
														}
														y++;
													}

													if (y == sep->at(xt).length())
													{
														if (ksep)
														{
															a.loc = (sllint)mk;
															a.arg.append(sep->at(xt).c_str());
															ret_->push_back(a);
															a.arg.clear();
														}
														x += (sep->at(xt).length() - 1);
														mk = x + 1;
														xt = sep->size();
													}
												}
												else
												{
													if (memcmp((void*)&ig, (void*)&val[x - 1], sizeof(_char)))
													{
														size_t y = 1;

														while (y < sep->at(xt).length() && x + y < t)
														{
															if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
															{
																y = sep->at(xt).length();
															}
															y++;
														}

														if (y == sep->at(xt).length())
														{
															a.loc = (sllint)mk;

															for (; mk < x; mk++)
															{
																a.arg.push_back(val[mk]);
															}

															if (!a.arg.empty())
															{
																ret_->push_back(a);
																a.arg.clear();
															}
															x += (sep->at(xt).length() - 1);
															mk = x + 1;

															if (ksep)
															{
																a.loc = (sllint)mk;
																a.arg.append(sep->at(xt).c_str());
																ret_->push_back(a);
																a.arg.clear();
															}
															xt = sep->size();
														}
													}
													else
													{
														if (x > 1)
														{
															if (!memcmp((void*)&ig, (void*)&val[x - 2], sizeof(_char)))
															{
																size_t y = 1;

																while (y < sep->at(xt).length() && x + y < t)
																{
																	if (memcmp((void*)&val[x + y], &sep->at(xt)[y], sizeof(_char)))
																	{
																		y = sep->at(xt).length();
																	}
																	y++;
																}

																if (y == sep->at(xt).length())
																{
																	a.loc = (sllint)mk;

																	for (; mk < x; mk++)
																	{
																		a.arg.push_back(val[mk]);
																	}

																	if (!a.arg.empty())
																	{
																		ret_->push_back(a);
																		a.arg.clear();
																	}
																	x += (sep->at(xt).length() - 1);
																	mk = x + 1;

																	if (ksep)
																	{
																		a.loc = (sllint)mk;
																		a.arg.append(sep->at(xt).c_str());
																		ret_->push_back(a);
																		a.arg.clear();
																	}
																	xt = sep->size();
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
			}
		}
		break;
	}
	default:
	{
		break;
	}
	}

	a.loc = (sllint)mk;

	for (; mk < t + 1; mk++)
	{
		a.arg.push_back(val[mk]);
	}
	if (!a.arg.empty())
	{
		ret_->push_back(a);
	}
	if (lit > -1)
	{
		ret = bot_sprintfs(&a.arg, true, "Open literal '%c' at: %u", msy.nrts_lit[lit], (uint)litloc);
		ret_->push_back(a);
		a.arg.clear();
		ret = -1;
	}
	else if (!ord.empty())
	{
		ret = bot_sprintfs(&a.arg, true, "Open bracket '%c' at: %u", msy.nrts_ord[ord[0]], (uint)ordl[0]);
		ret_->push_back(a);
		a.arg.clear();
		ret = -1;
	}
	else
	{
		ret = 0;
	}
	va_end(args);
	return ret;
}

// File Directory

std::string machine::BOTPathS(c_char* spath_)
{
	if (debug_lvl >= 650 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTPathS(c_char* spath_(%i))", (sint)spath_);
		oc = Output(ncar.carr, 2);
	}
	std::string str;
	sint h = -1;
	sint p = LockGMutex(MTX_DMAP, &h);

	if (p > -1)
	{
		str.append(bot_dmap.bot_home_path.c_str());
		p = str.find(":", 1);

		if (p > (sint)str.length() - 2)
		{
			_char dmk = '\\';
			p = str.find(dmk, p + 1);

			if (p < 0)
			{
				str.push_back(dmk);
			}
			str.append(BOT_HMD);
		}

		if (spath_)
		{
			if (strlen(spath_) < 256)
			{
				_char dmk = '\\';
				str.push_back(dmk);
				str.append(spath_);
			}
		}
		if (!h)
		{
			h = UnlockGMutex(MTX_DMAP);
		}
	}
	return str;
}
sint machine::BOTPath(std::string* str_, c_char* spath_)
{
	if (debug_lvl >= 650 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTPath(std::string* str_(%i), c_char* spath_(%i))", (sint)str_, (sint)spath_);
		oc = Output(ncar.carr, 2);
	}

	if (!str_)
	{
		return -1;
	}

	sint h = -1;
	sint p = LockGMutex(MTX_DMAP, &h);

	if (p > -1)
	{
		str_->append(bot_dmap.bot_home_path.c_str());
		p = str_->find(":", 1);

		if (p > (sint)str_->length() - 2)
		{
			_char dmk = '\\';
			p = str_->find(dmk, p + 1);

			if (p < 0)
			{
				str_->push_back(dmk);
			}
			str_->append(BOT_HMD);
		}

		if (spath_)
		{
			if (strlen(spath_) < 256)
			{
				_char dmk = '\\';
				str_->push_back(dmk);
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
	if (debug_lvl >= 650 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenDir(c_char* dest_(%i), DIR** dir_(%i)))", (sint)dest_, (sint)dir_);
		oc = Output(ncar.carr, 2);
	}
	if (!dest_ || !dir_)
	{
		return -1;
	}
	if ((*dir_ = opendir(dest_)) != NULL)
	{
		return 0;
	}
	return -1;
}
sint machine::BOTCloseDir(DIR** dir_)
{
	if (debug_lvl >= 650 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTCloseDir(DIR** dir_(%i))", (sint)dir_);
		oc = Output(ncar.carr, 2);
	}
	if (!*dir_)
	{
		return -1;
	}
	closedir(*dir_);
	return 0;
}
sint machine::BOTReadDir(std::vector<BOT_FILE_M>* flds_, c_char* dest_)
{
	if (debug_lvl >= 650 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTReadDir(std::vector<BOT_FILE_M>* flds_(%i), c_char* dest_(%i))", (sint)flds_, (sint)dest_);
		oc = Output(ncar.carr, 2);
	}
	if (!dest_)
	{
		return -1;
	}

	sint ret = -1;
	DIR* dir_ = 0;

	if ((dir_ = opendir(dest_)) != NULL)
	{
		BOT_FILE_M xfile;
		std::vector<std::string> cvec = BOT_NOFLD_V;
		struct dirent* dp_ = 0;

		while ((dp_ = readdir(dir_)) != NULL)
		{
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
				xfile.Renew(dp_->d_name, "", dest_, 0);
				ret = BOTFileStats(&xfile);

				if (ret > -1)
				{
					if (S_ISDIR(xfile.fst.filestats.st_mode))
					{
						if (flds_)
						{
							flds_->push_back(xfile);
						}
					}
				}
			}
		}
		closedir(dir_);
		return ret;
	}
	return ret;
}
sint machine::BOTFindHomeDir()
{
	if (debug_lvl >= 600 && debug_m)
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
	BOT_FILE_M ndir(crf, "", "", 0, BOT_DIR_CON);
	xc = BOTOpenFile(&ndir, &of, true);

	if (xc < 0)
	{
		return -1;
	}
	else
	{
		if (!of)
		{
			xc = BOTCloseFile(&ndir);
		}
	}

	sint h = -1;
	sint p = LockGMutex(MTX_DMAP, &h);

	if (p > -1)
	{
		for (size_t x = 0; x < bot_dmap.drvs.size(); x++)
		{
			if (strlen(bot_dmap.drvs[x].drv.c_str()) < 1024)
			{
				BOT_FILE_M hmd(BOT_HMD, "", bot_dmap.drvs[x].drv.c_str(), 0, BOT_DIR_CON);
				std::vector<BOT_FILE_M> ndrcs;
				ndrcs.push_back(hmd);

				if (!BOTReadDir(&ndrcs, BOTFileStr(&hmd).c_str()))
				{
					for (size_t y = 1; y < ndrcs.size(); y++)
					{
						if (!strcmp(ndrcs[y].name.c_str(), crf))
						{
							bot_dmap.bot_home_path.clear();
							bot_dmap.bot_home_path.append(ndrcs[y].path.c_str());
							of = -1;
							p = BOTOpenFile(&ndir, &of);

							if (p > -1)
							{
								x = bot_dmap.drvs.size();
								xc = BOTCloseFile(&ndir, true, true);
							}
						}
						else
						{
							p = BOTReadDir(&ndrcs, BOTFileStr(&ndrcs[y]).c_str());
						}
					}
				}
			}
		}
		if (!h)
		{
			h = UnlockGMutex(MTX_DMAP);
		}
		return xc;
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
	_char dmk = '\\';
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
	_char dmk = '\\';
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
sint machine::BOTFileStr(std::string* str_, BOT_FILE_M* file_)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_64 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileStr(std::string* str_(%i), BOT_FILE_M* file_(%i))", (sint)str_, (sint)file_);
		oc = Output(ncar.carr, 2);
	}

	if (!str_ || !file_)
	{
		return -1;
	}
	_char dmk = '\\';
	_char term = '.';
	sint ret = 0;

	if (!file_->path.empty())
	{
		str_->append(file_->path.c_str());

		if (!file_->name.empty())
		{
			str_->push_back(dmk);
			str_->append(file_->name.c_str());

			if (!file_->type.empty())
			{
				str_->push_back(term);
				str_->append(file_->type);
			}
		}
	}
	else if (!file_->name.empty())
	{
		str_->append(file_->name.c_str());

		if (!file_->type.empty())
		{
			str_->push_back(term);
			str_->append(file_->type);
		}
	}
	else { ret = -1; }
	return ret;
}
std::string machine::BOTFileStr(BOT_FILE_M* file_)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_64 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileStr(BOT_FILE_M* file_(%i))", (sint)file_);
		oc = Output(ncar.carr, 2);
	}

	std::string str;

	if (!file_)
	{
		return str;
	}
	
	_char dmk = '\\';
	_char term = '.';
	sint ret = 0;

	if (!file_->path.empty())
	{
		str.append(file_->path.c_str());

		if (!file_->name.empty())
		{
			str.push_back(dmk);
			str.append(file_->name.c_str());

			if (!file_->type.empty())
			{
				str.push_back(term);
				str.append(file_->type);
			}
		}
	}
	else if (!file_->name.empty())
	{
		str.append(file_->name.c_str());

		if (!file_->type.empty())
		{
			str.push_back(term);
			str.append(file_->type);
		}
	}
	else { }
	return str;
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

	if (!strcmp(UCASE(val_->type.c_str()).c_str(), "STDIO"))
	{
		val_->cm = BOT_IO_CON;
	}
	else if (val_->type.empty())
	{
		val_->cm = BOT_DIR_CON;
	}
	else if (!strcmp(val_->type.c_str(), ".db"))
	{
		val_->cm = BOT_DB_CON;
	}
	else
	{
		val_->cm = BOT_F_CON;
	}

	if (val_->lid > -1)
	{
		sint xc = SetVecEleMem((void*)&val_->cm, MTX_FO, val_->lid, BOT_FS_CM, false);
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
	case BOT_IO_CON:
	{
		sint ret = vtool.VIV(&h_mtxs, MTX_O);

		if (ret > -1)
		{
			if (!h_mtxs[ret].locked)
			{
				ret = -1;
			}
		}
		return ret;
		break;
	}
	case BOT_DB_CON:
	{
		BOT_DB_M ndb(val_->name.c_str());
		return GetODBConn(&ndb);
		break;
	}
	case BOT_F_CON:
	{
		if (val_->fcon > -1)
		{
			if ((size_t)val_->fcon < f_con.size())
			{
				if (f_con[val_->fcon])
				{
					if (f_con[val_->fcon]->flid == val_->lid)
					{
						if (val_->omode > -1)
						{
							if (f_con[val_->fcon]->omode == val_->omode && f_con[val_->fcon]->encode == val_->encode)
							{
								if (f_con[val_->fcon]->fstrm.is_open())
								{
									return val_->fcon;
								}
								else
								{
									f_con[val_->fcon]->fstrm.open(BOTFileStr(val_).c_str(), val_->omode);

									if (f_con[val_->fcon]->fstrm.is_open())
									{
										return val_->fcon;
									}
								}
							}
							else
							{
								if (f_con[val_->fcon]->fstrm.is_open())
								{
									f_con[val_->fcon]->fstrm.close();
									f_con[val_->fcon]->fstrm.open(BOTFileStr(val_).c_str(), val_->omode);

									if (f_con[val_->fcon]->fstrm.is_open())
									{
										if (f_con[val_->fcon]->encode != val_->encode)
										{
											f_con[val_->fcon]->encode = val_->encode;
											sint ret = SetVecEleMem((void*)&val_->encode, MTX_FO, val_->lid, BOT_FS_ENC, false);
										}

										if (f_con[val_->fcon]->omode != val_->omode)
										{
											f_con[val_->fcon]->omode = val_->omode;
											sint ret = SetVecEleMem((void*)&val_->omode, MTX_FO, val_->lid, BOT_FS_OMODE, false);
										}
										return val_->fcon;
									}
								}
							}
						}
					}
				}
			}
		}
		for (size_t siz = 0; siz < f_con.size(); siz++)
		{
			if (f_con[siz])
			{
				if (f_con[siz]->flid == val_->lid)
				{
					if (val_->omode > -1)
					{
						if (f_con[siz]->omode == val_->omode && f_con[siz]->encode == val_->encode)
						{
							if (f_con[siz]->fstrm.is_open())
							{
								val_->fcon = (sint)siz;
								return val_->fcon;
							}
							else
							{
								f_con[siz]->fstrm.open(BOTFileStr(val_).c_str(), val_->omode);

								if (f_con[siz]->fstrm.is_open())
								{
									val_->fcon = (sint)siz;
									sint ret = SetVecEleMem((void*)&val_->fcon, MTX_FO, val_->lid, BOT_FS_FCON, false);
									return val_->fcon;
								}
							}
						}
						else
						{
							if (f_con[siz]->fstrm.is_open())
							{
								f_con[siz]->fstrm.close();
								f_con[siz]->fstrm.open(BOTFileStr(val_).c_str(), val_->omode);

								if (f_con[siz]->fstrm.is_open())
								{
									val_->fcon = (sint)siz;

									if (f_con[siz]->encode != val_->encode)
									{
										f_con[siz]->encode = val_->encode;
										sint ret = SetVecEleMem((void*)&val_->encode, MTX_FO, val_->lid, BOT_FS_ENC, false);
									}

									if (f_con[siz]->omode != val_->omode)
									{
										f_con[siz]->omode = val_->omode;
										sint ret = SetVecEleMem((void*)&val_->omode, MTX_FO, val_->lid, BOT_FS_OMODE, false);
									}

									sint ret = SetVecEleMem((void*)&val_->fcon, MTX_FO, val_->lid, BOT_FS_FCON, false);
									return val_->fcon;
								}
							}
						}
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
sint machine::GetFConn(BOT_FILE_M* val_, sint* was_open, slint mt)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_96 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::GetFConn(BOT_FILE_M *val_(%i)), sint* was_open(%i), sllint mt(%li))", (sint)val_, sint(was_open), mt);
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
		case BOT_IO_CON:
		{
			sint ox = vtool.VIV(&h_mtxs, MTX_O);
			ret = LockGMutex(MTX_O, &ox);
			val_->fcon = ret;
			ret = SetVecEleMem((void*)&val_->fcon, MTX_FO, val_->lid, BOT_FS_FCON, false);
			break;
		}
		case BOT_DIR_CON:
		{
			ret = 0;
			break;
		}
		case BOT_DB_CON:
		{
			BOT_DB_M ndb(val_->name.c_str());
			ndb.omode = val_->omode;
			ret = GetDBConn(&ndb, mt);
			break;
		}
		case BOT_F_CON:
		{
			sllint rst = -1;

			while (mt > -1)
			{
				sint h = -1;
				ret = LockGMutex(MTX_FCON, &h);

				if (ret > -1)
				{
					for (sint siz = 0; siz < (sint)BOT_FO_MAX; siz++)
					{
						sint xh = -1;
						ret = LockElement(MTX_FCON, siz, &xh, false, false);

						if (!ret)
						{
							ret = vtool.AVTV(&f_con, &FCON[siz], true, true);

							if (ret > -1)
							{
								f_con[ret]->Renew(val_, siz);
								val_->fcon = ret;
								ret = SetVecEleMem((void*)&val_->fcon, MTX_FO, val_->lid, BOT_FS_FCON, false);
								mt = -1;
							}
							else
							{
								if (!xh)
								{
									sint xc = UnlockElement(MTX_FCON, siz, false);
								}
							}
							siz = (sint)BOT_FO_MAX;
						}
					}

					if (!h)
					{
						h = UnlockGMutex(MTX_FCON);
					}
				}
				mt--;
				rst = nsRest((sllint)BOT_FO_REST);
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
	case BOT_IO_CON:
	{
		ret = UnlockGMutex(MTX_O);
		break;
	}
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
				sint ox = -1;
				sint hx = LockGMutex(MTX_FCON, &ox);

				if (hx > -1)
				{
					hx = f_con[ret]->lid;
					f_con[ret]->Clear();
					sint xret = UnlockElement(MTX_FCON, hx, false);
					f_con[ret] = 0;
					xret = vtool.CLNV(&f_con);

					if (!ox)
					{
						ox = UnlockGMutex(MTX_FCON);
					}
				}
				hx = -1;
				ox = SetVecEleMem((void*)&hx, MTX_FO, xfile_->lid, BOT_FS_FCON, false);
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
		if (file_->cm != (sint)BOT_F_CON)
		{
			sv_mth = file_->cm;
			file_->cm = (sint)BOT_F_CON;
		}
		ret = GetFConn(file_);

		if (ret > -1)
		{
			boto_file = true;
			ret = UpdMTXPrio();
			f_con[file_->fcon]->fstrm.open(BOTFileStr(file_).c_str(), BOT_FILE_READ);

			if (f_con[file_->fcon]->fstrm.is_open())
			{
				ret = -1;
				_char nuchar;
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

	for (size_t x = 0; x < file_->fst.compv.size(); x++)
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
						in its constituent symbols, and their avg locs in line should have a low variation or avg spacing should have low variation */

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

				for (size_t z = y + 1; z < res.size(); z++)
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
		std::vector<_char> cons;

		for (size_t x = 0; x < res.size(); x++)
		{
			ullint xloc = file_->fst.mean_loc[res_e[x]] + 1;

			if (x)
			{
				ullint rval = (ullint)((float)res[0] / 2.0f);

				if (res[x] >= rval)
				{
					sint ret = vtool.VIV(&file_->fst.mean_loc, xloc);

					while (ret > -1)
					{
						if (ret != (sint)res_e[x])
						{
							if (file_->fst.cts[ret] <= file_->fst.cts[res_e[x]] + 1 && file_->fst.cts[ret] >= file_->fst.cts[res_e[x]] - 1)
							{
								ret = vtool.AVTV(&cons, file_->fst.compv[res_e[x]], true, true);
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
							ret = vtool.AVTV(&file_->fst.seps, &nsym, true, true);
							cons.clear();
						}
						free(nuchar);
					}
				}
			}
			else
			{
				sint ret = vtool.AVTV(&cons, &file_->fst.compv[res_e[x]], true, true);
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
					sint ret = vtool.AVTV(&file_->fst.seps, &nsym, true, true);
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

		if (file_->cm != (sint)BOT_F_CON)
		{
			sv_mth = file_->cm;
			file_->cm = (sint)BOT_F_CON;
		}
		ret = GetFConn(file_);

		if (ret > -1)
		{
			boto_file = true;
			ret = UpdMTXPrio();
			f_con[file_->fcon]->fstrm.open(BOTFileStr(file_).c_str(), BOT_FILE_READ);

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
	sint ret = t.AddCond(0, "DATA", msy.sql_comp_keywords[5].c_str(), file_->type.c_str());
	ret = BOTFileIN(file_, false, 0, (ullint)BOT_FSCAN_LIM, BOT_RTV_MACS, &t, BOT_RTV_MAX);

	if (ret > -1)
	{
		if (in_sym.cons.empty())
		{
			in_sym.Renew(5, (u_char*)file_->type.c_str(), file_->encode);
		}
		
		ret = AddCode(&in_sym);
		return ret;
	}
	return 1;
}
sint machine::BOTFileStats(BOT_FILE_M *file_, bool doscan, sint scan_lvl)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_96 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileStats(BOT_FILE_M *file_(%i), bool doscan(%u), sint scan_lvl(%i))", (sint)file_, (uint)doscan, scan_lvl);
		oc = Output(ncar.carr, 2);
	}

	if (!file_)
	{
		return -1;
	}

	if (file_->cm < 0)
	{
		sint ret = BOTConnMethod(file_);
	}

	if (file_->cm == BOT_IO_CON)
	{
		return 0;
	}

#ifdef _WIN32
	struct _stat nstat;
	sint ret = _stat(BOTFileStr(file_).c_str(), &nstat);
#else
	struct stat nstat;
	sint ret = stat(BOTFileStr(file_).c_str(), &nstat);
#endif

	if (!ret)
	{
		if (file_->fst.cmpstats(&nstat))
		{
			file_->fst.RenewStats(&nstat);
		}
		if (file_->fst.exists < 1)
		{
			file_->fst.exists = 1;

			if (file_->bto < 0)
			{
				std::string onm;
				_char dmk = '\\';

				for (sint x = (sint)file_->path.length() - 2; x > -1; x--)
				{
					if (!memcmp((void*)&file_->path[x], (void*)&dmk, sizeof(_char)))
					{
						for (x++; x < (sint)file_->path.length(); x++)
						{
							onm.push_back(file_->path[x]);
						}
						x = -1;
					}
				}

				if (!onm.empty())
				{
					std::string np;
					np.append(file_->path.substr(0, file_->path.length() - onm.length()).c_str());
					BOT_FILE_M blt(onm.c_str(), "", np.c_str(), 0, BOT_DIR_CON);
					sint xret = GetInVec(&blt, MTX_FO);

					if (xret > -1)
					{
						file_->bto = blt.lid;
						sint xret = SetVecEleMem((void*)&file_->bto, MTX_FO, file_->lid, BOT_FS_BTO, false);
					}
				}
			}
		}

		sint xret = SetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE, false);

		if (file_->cm == BOT_DIR_CON)
		{
			ret = 0;
		}
		else
		{
			if (doscan)
			{
				if (scan_lvl < 0)
				{
					scan_lvl = BOT_FSCAN_LVL;
				}
				if (scan_lvl > 0)
				{
					if ((ullint)file_->fst.filestats.st_size > (ullint)BOT_STRLEN_MAX)
					{
						std::vector<TINFO_M> tvec;
						ullint x = (ullint)BOT_STRLEN_MAX;
						ullint last_x = 0;

						while (x < (ullint)file_->fst.filestats.st_size)
						{
							if ((ullint)file_->fst.filestats.st_size < (ullint)BOT_STRLEN_MAX)
							{
								x = (ullint)file_->fst.filestats.st_size;
							}

							std::vector<ullint> nvals{ (ullint)file_->lid, (ullint)file_->encode, last_x, x };
							TINFO_M nt((sint)PTHREAD_CREATE_JOINABLE, "ScanFileThread", ScanFileThread, lid, 0.0f, &nvals);
							tvec.push_back(nt);
							last_x = x;

							if (x + (ullint)BOT_STRLEN_MAX > (ullint)file_->fst.filestats.st_size)
							{
								x = (ullint)file_->fst.filestats.st_size;
							}
							else
							{
								x += (ullint)BOT_STRLEN_MAX;
							}
						}

						sint xret = HasLock(MTX_FO, file_->lid);

						if (xret)
						{
							xret = UnlockElement(MTX_FO, file_->lid, false);
						}

						if (!xret)
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
						file_->fst.AvgSyms();
						xret = DetSep(file_);

						if (scan_lvl > 1)
						{
							x = (ullint)BOT_STRLEN_MAX;
							last_x = 0;

							while (x < (ullint)file_->fst.filestats.st_size)
							{
								if ((ullint)file_->fst.filestats.st_size < (ullint)BOT_STRLEN_MAX)
								{
									x = (ullint)file_->fst.filestats.st_size;
								}

								std::vector<ullint> nvals{ (ullint)file_->lid, (ullint)file_->encode, last_x, x };
								TINFO_M nt((sint)PTHREAD_CREATE_JOINABLE, "RendFileThread", RendFileThread, lid, 0.0f, &nvals);
								tvec.push_back(nt);
								last_x = x;

								if (x + (ullint)BOT_STRLEN_MAX > (ullint)file_->fst.filestats.st_size)
								{
									x = (ullint)file_->fst.filestats.st_size;
								}
								else
								{
									x += (ullint)BOT_STRLEN_MAX;
								}
							}

							xret = HasLock(MTX_FO, file_->lid);

							if (xret)
							{
								xret = UnlockElement(MTX_FO, file_->lid, false);
							}

							if (!xret)
							{
								std::vector<sint> rets;
								ret = InitThreads(&tvec, &rets);
								xret = LockElement(MTX_FO, file_->lid, &xret, true, false);
							}

							xret = SetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE);

							if (ret > -1)
							{
								ret = 0;
							}
						}
					}
					else
					{
						if (file_->fst.filestats.st_size)
						{
							file_->fst.RenewLocs(file_->fst.filestats.st_size - 1, file_->fst.oa_loc, file_->fst.ia_loc);
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

							xret = SetVecEleMem((void*)&file_->fst, MTX_FO, file_->lid, BOT_FS_STATE, false);

							if (ret > -1)
							{
								ret = 0;
							}
						}
					}
				}
			}
			else
			{
				ret = 0;
			}
		}
	}
	else
	{
		file_->fst.Clear();
		ret = -1;
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
	if (file_->cm == BOT_IO_CON)
	{
		return 0;
	}
	sint ret = -1;

	if (strcmp(cur_path.c_str(), file_->path.c_str()))
	{
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
				BOT_FILE_M dirf("", "", file_->path.c_str(), file_->omode, BOT_DIR_CON);
				uf = f + 1;
				ret = BOTFileStats(&dirf);

				if (ret < 0)
				{
					sint of = -1;
					ret = BOTOpenFile(&dirf, &of, true);

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
				if (debug_lvl > 1 && debug_m)
				{
					carr_512 ncar;
					sint op = bot_sprintf(ncar.carr, ncar.siz, "error %i creating db: %s", ret, BOTFileStr(file_).c_str());
					op = Output(ncar.carr, 1);
				}
			}
			if (!*was_open)
			{
				sint xret = ret;
				ret = CloseDB(&ndb, &xh);
			}
		}
		break;
	}
	case BOT_F_CON:
	{
		bool wcl = false;

		if (file_->fcon < 0)
		{
			wcl = true;
			ret = GetFConn(file_);
		}

		if (file_->fcon > -1)
		{
			ret = -1;
			f_con[file_->fcon]->fstrm.open(BOTFileStr(file_).c_str(), BOT_FILE_APND);

			if (f_con[file_->fcon]->fstrm.is_open())
			{
				f_con[file_->fcon]->fstrm.close();
				ret = 0;
			}

			if (wcl)
			{
				sint xret = CloseFConn(file_);

				if (xret < 0)
				{
					ret = -1;
				}
			}
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
#ifdef _WIN32
		ret = _mkdir(BOTFileStr(file_).c_str());
#else
		ret = mkdir(BOTFileStr(file_).c_str(), S_IFDIR);
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

sint machine::BOTRenameFile(BOT_FILE_M* file_, c_char* nnm)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_96 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTRenameFile(BOT_FILE_M *xfile_(%i), c_char* nnm(%i))", (sint)file_, (sint)nnm);
		oc = Output(ncar.carr, 2);
	}

	if (!file_)
	{
		return -1;
	}

	if (file_->cm == BOT_IO_CON)
	{
		return 0;
	}
	sint ret = -1;
	switch (file_->cm)
	{
	case BOT_DIR_CON:
	{

		break;
	}
	case BOT_DB_CON:
	case BOT_F_CON:
	{
		ret = std::rename(BOTFileStr(file_).c_str(), nnm);

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

	if (xfile_->cm == BOT_IO_CON)
	{
		return -1;
	}
	sint ret = -1;
	switch (xfile_->cm)
	{
	case BOT_DIR_CON:
	{
#ifdef _WIN32
		ret = _rmdir(BOTFileStr(xfile_).c_str());
#else
		ret = rmdir(BOTFileStr(xfile_).c_str());
#endif
		break;
	}
	case BOT_DB_CON:
	case BOT_F_CON:
	{
		ret = std::remove(BOTFileStr(xfile_).c_str());

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
	return ret;
}
sint machine::BOTOpenFile(sint flid, sint *was_open, bool cine, bool r_to_st, bool dtp)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenFile(sint flid(%i), sint *was_open(%i), bool cine(%u), bool r_to_st(%u), bool dtp(%u))", flid, (sint)was_open, (uint)cine, (uint)r_to_st, (uint)dtp);
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
sint machine::BOTOpenFile(BOT_FILE_M* mfile_, sint *was_open, bool cine, bool r_to_st, bool dtp)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_168 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenFile(BOT_FILE_M* mfile_(%i), sint *was_open(%i), bool cine(%u), bool r_to_st(%u), bool dtp(%u))", (sint)mfile_, (sint)was_open, (uint)cine, (uint)r_to_st, (uint)dtp);
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
		if (mfile_->cm < 0)
		{
			gc = BOTConnMethod(mfile_);
		}

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

		std::vector<MACSYM> svec;

		if (!mfile_->path.empty())
		{
			MACSYM fc(16, (u_char*)mfile_->path.c_str(), 0);
			svec.push_back(fc);
		}

		if (!mfile_->name.empty())
		{
			MACSYM fc(7, (u_char*)mfile_->name.c_str(), mfile_->encode);
			svec.push_back(fc);
		}

		if (!mfile_->type.empty())
		{
			MACSYM fc(8, (u_char*)mfile_->type.c_str(), mfile_->encode);
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

	gc = BOTFileStats(mfile_, true);
	sint xh = -1;
	sint lx = LockElement(MTX_FO, mfile_->lid, &xh, true, false);

	if (lx)
	{
		return -1;
	}

	if (mfile_->fst.exists < 0)
	{
		if (mfile_->cm == BOT_IO_CON)
		{
			mfile_->fst.exists = 1;
			gc = SetVecEleMem(&mfile_->fst, MTX_FO, mfile_->lid, BOT_FS_STATE, false);
		}
		else if (cine)
		{
			gc = BOTCreateFile(mfile_, was_open);

			if (gc > -1)
			{
				gc = BOTFileStats(mfile_, true);

				if (gc)
				{
					gc = ClearVecEle(MTX_FO, mfile_->lid, false);

					if (!xh)
					{
						xh = UnlockElement(MTX_FO, mfile_->lid, false);
					}
					return -1;
				}
			}
			else
			{
				gc = ClearVecEle(MTX_FO, mfile_->lid, false);

				if (!xh)
				{
					xh = UnlockElement(MTX_FO, mfile_->lid, false);
				}
				return -5;
			}
		}
		else
		{
			gc = ClearVecEle(MTX_FO, mfile_->lid, false);

			if (!xh)
			{
				xh = UnlockElement(MTX_FO, mfile_->lid, false);
			}
			return -1;
		}
	}

	if (mfile_->cm != BOT_DIR_CON)
	{
		sint fc = GetFConn(mfile_, was_open);

		if (fc < 0)
		{
			if (!xh)
			{
				xh = UnlockElement(MTX_FO, mfile_->lid, false);
			}
			return -1;
		}
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

	if (mfile_->cm == BOT_IO_CON)
	{
		return 0;
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
			gc = OpenDB(&ndb, mfile_->omode, was_open, &xh);

			if (gc < 0)
			{
				gc = ClearVecEle(MTX_FO, mfile_->lid, false);
			}
			break;
		}
		case BOT_F_CON:
		{
			if (!f_con[mfile_->fcon]->fstrm.is_open())
			{
				f_con[mfile_->fcon]->fstrm.open(BOTFileStr(mfile_).c_str(), mfile_->omode);
			}
			if (!f_con[mfile_->fcon]->fstrm.is_open())
			{
				gc = ClearVecEle(MTX_FO, mfile_->lid, false);
				return -1;
			}
			else
			{
				if (dtp)
				{
					sint ox = -1;
					sint hx = LockGMutex(MTX_FO, &ox);

					if (hx > -1)
					{
						gc = -1;
						hx = LockGMutex(MTX_FPAD, &gc);

						if (hx > -1)
						{
							fileo_vec.d_vec[mfile_->lid].dat = fpad[mfile_->fcon];

							if (!gc)
							{
								gc = UnlockGMutex(MTX_FPAD);
							}
						}
						if (fileo_vec.d_vec[mfile_->lid].Alloc(mfile_->fst.filestats.st_size + 1))
						{
							mfile_->Renew(&fileo_vec.d_vec[mfile_->lid]);
							gc = SetVecEle((void*)mfile_, MTX_FO, mfile_->lid);
							gc = BOTFileIN(mfile_, false, 0, mfile_->fst.filestats.st_size, BOT_RTV_CHARP, fileo_vec.d_vec[mfile_->lid].dat, BOT_RTV_MAX);
						}

						if (!ox)
						{
							ox = UnlockGMutex(MTX_FO);
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
	else if (S_ISDIR(mfile_->fst.filestats.st_mode))
	{
		cur_path.clear();
		cur_path.append(BOTFileStr(mfile_).c_str());
	}
	else if (S_ISCHR(mfile_->fst.filestats.st_mode)) {}
	else if (S_ISBLK(mfile_->fst.filestats.st_mode)) {}
	else if (S_ISFIFO(mfile_->fst.filestats.st_mode)) {}
	else if (S_ISLNK(mfile_->fst.filestats.st_mode)) {}
	else if (S_ISSOCK(mfile_->fst.filestats.st_mode)) {}
	else {}
	return mfile_->lid;
}
sint machine::BOTFindInFile(BOT_FILE_M* file_, bool indat, size_t f, size_t t, void* f_, size_t len)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFindInFile(BOT_FILE_M* file_(%i), bool indat(%u), size_t f(%u), size_t t(%u), void* f_(%i), size_t len(%u))", (sint)file_, (uint)indat, f, t, (sint)f_, len);
		oc = Output(ncar.carr, 2);
	}

	if (!file_ || !f_ || !len || len > (size_t)BOT_STRLEN_MAX)
	{
		return -1;
	}

	if (!t || t < f || t > (size_t)file_->fst.filestats.st_size)
	{
		if (file_->fst.filestats.st_size)
		{
			t = (size_t)file_->fst.filestats.st_size - 1;
		}
		else
		{
			return -1;
		}
	}

	sllint xret = 0;
	sint ret = -1;
	_char* af = reinterpret_cast<_char*>(f_);

	if (!indat)
	{
		if (file_->cm == BOT_IO_CON)
		{

		}
		else if (file_->cm == BOT_F_CON)
		{
			sint ox = -1;

			if (file_->fcon < 0)
			{
				ret = BOTOpenFile(file_, &ox);
			}
			else if (!f_con[file_->fcon]->fstrm.is_open())
			{
				ret = BOTOpenFile(file_, &ox);
			}
			else
			{
				ret = 0;
			}
			if (ret > -1)
			{
				xret = (sllint)f_con[file_->fcon];

				if (file_->omode == BOT_FILE_INS || file_->omode == BOT_FILE_OVRL || file_->omode == BOT_FILE_READ || file_->omode == BOT_FILE_READATE)
				{
					size_t ph = file_->fst.ia_loc;
					size_t x = 0;

					for (x = 0; x < file_->fst.e_loc; x++)
					{
						_char n;
						ret = BOTFileIN(file_, false, f, t, BOT_RTV_CHARP, &n, BOT_RTV_MAX);
						size_t y = 0;

						if (!memcmp((void*)&af[y], (void*)&n, sizeof(_char)))
						{
							y++;

							while (y < len)
							{
								if (memcmp((void*)&af[y], (void*)&n, sizeof(_char)))
								{
									y = len;
								}
								y++;
							}

							if (y == len)
							{
								BOT_CRS nc(xret, lid, x, x + (len - 1));
								ret = PushToVecEleMem((void*)&nc, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
								ret = 0;
								x = file_->fst.e_loc + 1;
							}
						}
					}

					if (x == file_->fst.e_loc)
					{
						f_con[file_->fcon]->fstrm.seekg(ph);
					}
				}
			}

			if (!ox)
			{
				ret = BOTCloseFile(file_);
			}
		}
		else {}
	}
	else
	{
		if (file_->datp)
		{
			sllint x = bot_findin(af, (size_t)f, (size_t)t, file_->datp);

			if (x > -1)
			{
				BOT_CRS nc(0, lid, (size_t)x, (size_t)x + (bot_strlen(af) - 1));
				ret = PushToVecEleMem((void*)&nc, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
				ret = 0;
			}
		}
	}

	if (!ret)
	{
		sint ox = GetVecEle(file_, MTX_FO, file_->lid);
	}
	return ret;
}
sint machine::BOTFileOUT(BOT_FILE_M* file_, size_t f, bool to_fdat, ...)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileOUT(BOT_FILE_M* file_(%i), size_t f(%u), bool to_fdat(%u), ...)", (sint)file_, (uint)f, (uint)to_fdat);
		oc = Output(ncar.carr, 2);
	}
	if (!file_)
	{
		return -1;
	}

	sint ret = -1;

	if (!to_fdat)
	{
		if (file_->cm == BOT_IO_CON)
		{
			sint ox = -1;

			if (file_->fcon < 0)
			{
				ret = GetFConn(file_, &ox);
			}
			if (file_->fcon > -1)
			{
				bool done = false;
				va_list args;
				va_start(args, to_fdat);

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
						sint val_ = va_arg(args, sint);
						std::cout.put(val_);
						file_->fst.oa_loc++;
						ret = 0;
						break;
					}
					case BOT_RTV_CHAR:
					{
						sint val = va_arg(args, sint);
						_char val_ = (_char)val;
						std::cout.put(val_);
						file_->fst.oa_loc++;
						ret = 0;
						break;
					}
					case BOT_RTV_CHARP:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_)
						{
							size_t nt = bot_strlen(val_);
							for (size_t x = 0; x < nt; x++)
							{
								std::cout.put(val_[x]);
							}
							file_->fst.oa_loc += nt;
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CCHAR:
					{
						c_char* val_ = va_arg(args, c_char*);

						if (val_)
						{
							size_t nt = bot_cstrlen(val_);
							for (size_t x = 0; x < nt; x++)
							{
								std::cout.put(val_[x]);
							}
							file_->fst.oa_loc += nt;
							ret = 0;
						}
						break;
					}
					case BOT_RTV_STR:
					{
						std::string* val_ = va_arg(args, std::string*);

						if (val_)
						{
							for (size_t x = 0; x < val_->length(); x++)
							{
								std::cout.put(val_->at(x));
							}
							file_->fst.oa_loc += val_->length();
							ret = 0;
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
			}
			if (!ox)
			{
				ox = CloseFConn(file_, true);
			}
			return 0;
		}
		else if (file_->cm == BOT_F_CON)
		{
			sint ox = -1;
			ret = GetOFConn(file_, &ox);

			if (ret < 0)
			{
				ret = BOTOpenFile(file_, &ox);
			}

			if (file_->fcon > -1)
			{
				sint ud = BOTFileStats(file_);
				boto_file = true;
				ud = UpdMTXPrio();
				bool done = false;

				if (f > (size_t)file_->fst.filestats.st_size)
				{
					f = file_->fst.filestats.st_size;
				}
				if ((size_t)f_con[file_->fcon]->fstrm.tellp() != f)
				{
					f_con[file_->fcon]->fstrm.seekp(f);
				}

				va_list args;
				va_start(args, to_fdat);

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
						file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
						ret = 0;
						break;
					}
					case BOT_RTV_UCHAR:
					{
						uint val = va_arg(args, uint);
						u_char val_ = (u_char)val;
						f_con[file_->fcon]->fstrm.put(val_);
						file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
						ret = 0;
						break;
					}
					case BOT_RTV_SINT:
					{
						sint val_ = va_arg(args, sint);
						f_con[file_->fcon]->fstrm.put(val_);
						file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
						ret = 0;
						break;
					}
					case BOT_RTV_CHAR:
					{
						sint val = va_arg(args, sint);
						_char val_ = (_char)val;
						f_con[file_->fcon]->fstrm.put(val_);
						file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
						ret = 0;
						break;
					}
					case BOT_RTV_UCHARP:
					{
						uint* val_ = va_arg(args, uint*);

						if (val_)
						{
							u_char* val = (u_char*)val_;
							size_t nt = bot_ustrlen(val);

							for (size_t x = 0; x < nt; x++)
							{
								f_con[file_->fcon]->fstrm.put(val[x]);
							}
							file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CHARP:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_)
						{
							size_t nt = bot_strlen(val_);
							for (size_t x = 0; x < nt; x++)
							{
								f_con[file_->fcon]->fstrm.put(val_[x]);
							}
							file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CCHAR:
					{
						c_char* op_ = va_arg(args, c_char*);

						if (op_)
						{
							size_t nt = bot_cstrlen(op_);

							for (size_t x = 0; x < nt; x++)
							{
								f_con[file_->fcon]->fstrm.put(op_[x]);
							}
							file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
						}
						break;
					}
					case BOT_RTV_STR:
					{
						std::string* str = va_arg(args, std::string*);

						if (str)
						{
							if (!str->empty() && str->length() < BOT_STRLEN_MAX)
							{
								for (size_t x = 0; x < str->length(); x++)
								{
									f_con[file_->fcon]->fstrm.put(str->at(x));
								}
								file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
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
									if (strvec->at(siz).length() < BOT_STRLEN_MAX)
									{
										for (size_t x = 0; x < strvec->at(siz).length(); x++)
										{
											f_con[file_->fcon]->fstrm.put(strvec->at(siz)[x]);
										}
									}
									strvec->at(siz).clear();
								}
								strvec->clear();
								file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
								ret = 0;
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

				if (!ret)
				{
					ret = BOTFileStats(file_);
					BOT_CRS crs((sllint)f_con[file_->fcon], lid, file_->fst.oa_loc);
					ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
					ud = GetVecEle(file_, MTX_FO, file_->lid);
				}
				boto_file = false;
				ud = UpdMTXPrio();
			}
			if (!ox)
			{
				ox = BOTCloseFile(file_);
			}
		}
		else if (file_->cm == BOT_DB_CON)
		{
			std::vector<BOT_STMT> tvec;
			bool done = false;
			va_list args;
			va_start(args, to_fdat);

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
	}
	else
	{
		sint ox = -1;
		sint hx = LockGMutex(MTX_FO, &ox);

		if (hx > -1)
		{
			boto_file = true;
			sint ud = UpdMTXPrio();
			bool done = false;
			va_list args;
			va_start(args, to_fdat);

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
					if (file_->omode == BOT_FILE_OVRL)
					{

					}
					else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
					{
						if (fileo_vec.d_vec[file_->lid].Alloc(file_->dsiz + sizeof(uint)))
						{
							uint val_ = va_arg(args, uint);
							uint xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], sizeof(uint));
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)&val_, sizeof(uint));

							for (size_t x = f + 1; x < fileo_vec.d_vec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], sizeof(uint));
								memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&xval, sizeof(uint));
								memcpy((void*)&xval, (void*)&val_, sizeof(uint));
							}
							uint term = (uint)'\0';
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(uint));
							ret = 0;
							BOT_CRS crs(0, lid, f + sizeof(sint));
							ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						}
					}
					else {}
					break;
				}
				case BOT_RTV_UCHAR:
				{
					if (file_->omode == BOT_FILE_OVRL)
					{

					}
					else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
					{
						if (fileo_vec.d_vec[file_->lid].Alloc(file_->dsiz + sizeof(u_char)))
						{
							uint val_ = va_arg(args, uint);
							u_char val = (u_char)val_;
							u_char xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], sizeof(u_char));
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)&val_, sizeof(u_char));

							for (size_t x = f + 1; x < fileo_vec.d_vec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], sizeof(u_char));
								memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&xval, sizeof(u_char));
								memcpy((void*)&xval, (void*)&val_, sizeof(u_char));
							}
							u_char term = (u_char)'\0';
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(u_char));
							ret = 0;
							BOT_CRS crs(0, lid, f + sizeof(u_char));
							ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						}
					}
					else {}
					break;
				}
				case BOT_RTV_SINT:
				{
					if (file_->omode == BOT_FILE_OVRL)
					{

					}
					else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
					{
						if (fileo_vec.d_vec[file_->lid].Alloc(file_->dsiz + sizeof(sint)))
						{
							sint val_ = va_arg(args, sint);
							sint xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], sizeof(sint));
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)&val_, sizeof(sint));

							for (size_t x = f + 1; x < fileo_vec.d_vec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], sizeof(sint));
								memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&xval, sizeof(sint));
								memcpy((void*)&xval, (void*)&val_, sizeof(sint));
							}
							sint term = (sint)'\0';
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(sint));
							ret = 0;
							BOT_CRS crs(0, lid, f + sizeof(sint));
							ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						}
					}
					else {}
					break;
				}
				case BOT_RTV_CHAR:
				{
					if (file_->omode == BOT_FILE_OVRL)
					{

					}
					else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
					{
						if (fileo_vec.d_vec[file_->lid].Alloc(file_->dsiz + sizeof(_char)))
						{
							sint val_ = va_arg(args, sint);
							_char val = (_char)val_;
							_char xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], sizeof(_char));
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)&val_, sizeof(_char));

							for (size_t x = f + 1; x < fileo_vec.d_vec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], sizeof(_char));
								memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&xval, sizeof(_char));
								memcpy((void*)&xval, (void*)&val_, sizeof(_char));
							}
							_char term = '\0';
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
							ret = 0;
							BOT_CRS crs(0, lid, f + sizeof(_char));
							ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						}
					}
					else {}
					break;
				}
				case BOT_RTV_UCHARP:
				{
					u_char* val_ = va_arg(args, u_char*);

					if (val_)
					{
						size_t nt = bot_ustrlen(val_);

						if (file_->omode == BOT_FILE_OVRL)
						{
							if (f + nt > fileo_vec.d_vec[file_->lid].dsiz - 1)
							{
								if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + ((f + nt) - fileo_vec.d_vec[file_->lid].dsiz)))
								{
									ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									size_t x = f;

									while (x < (f + nt))
									{
										if (memcmp((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char)))
										{
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char));
										}
										x++;
									}
								}
							}
							else
							{
								size_t x = f;

								while (x < (f + nt))
								{
									if (memcmp((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char)))
									{
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char));
									}
									x++;
								}
							}
							u_char term = (u_char)'\0';
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(u_char));
						}
						else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
						{
							size_t osiz = fileo_vec.d_vec[file_->lid].dsiz;

							if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + nt))
							{
								u_char* xval = (u_char*)malloc(nt + 1);

								if (xval)
								{
									ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									memcpy((void*)xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], nt);
									memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)val_, nt);
									u_char term = (u_char)'\0';
									memcpy((void*)&xval[nt], (void*)&term, sizeof(u_char));
									size_t x = f + nt;

									while (x + nt < fileo_vec.d_vec[file_->lid].dsiz)
									{
										memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], nt);
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, nt);
										memcpy((void*)xval, (void*)val_, nt);
										x += nt;
									}

									if (x < fileo_vec.d_vec[file_->lid].dsiz)
									{
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, fileo_vec.d_vec[file_->lid].dsiz - x);
									}

									memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(u_char));
									free(xval);
									ret = 0;
									BOT_CRS crs(0, lid, f + nt);
									ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
								}
							}
						}
						else {}
					}
					break;
				}
				case BOT_RTV_CHARP:
				{
					_char* val_ = va_arg(args, _char*);

					if (val_)
					{
						size_t nt = bot_strlen(val_);

						if (file_->omode == BOT_FILE_OVRL)
						{
							if (f + nt > fileo_vec.d_vec[file_->lid].dsiz - 1)
							{
								if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + ((f + nt) - fileo_vec.d_vec[file_->lid].dsiz)))
								{
									ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									size_t x = f;

									while (x < (f + nt))
									{
										if (memcmp((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char)))
										{
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char));
										}
										x++;
									}
								}
							}
							else
							{
								size_t x = f;

								while (x < (f + nt))
								{
									if (memcmp((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char)))
									{
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char));
									}
									x++;
								}
							}
							_char term = '\0';
							memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
						}
						else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
						{
							size_t osiz = fileo_vec.d_vec[file_->lid].dsiz;

							if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + nt))
							{
								_char* xval = (_char*)malloc(nt + 1);

								if (xval)
								{
									ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									memcpy((void*)xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], nt);
									memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)val_, nt);
									_char term = '\0';
									memcpy((void*)&xval[nt], (void*)&term, sizeof(_char));
									size_t x = f + nt;

									while (x + nt < fileo_vec.d_vec[file_->lid].dsiz)
									{
										memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], nt);
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, nt);
										memcpy((void*)xval, (void*)val_, nt);
										x += nt;
									}

									if (x < fileo_vec.d_vec[file_->lid].dsiz)
									{
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, nt);
									}

									memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
									free(xval);
									ret = 0;
									BOT_CRS crs(0, lid, f + nt);
									ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
								}
							}
						}
						else {}
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
							if (file_->omode == BOT_FILE_OVRL)
							{
								if (f + str->length() > fileo_vec.d_vec[file_->lid].dsiz - 1)
								{
									if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + ((f + str->length()) - fileo_vec.d_vec[file_->lid].dsiz)))
									{
										ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
										size_t x = f;

										while (x < (f + str->length()))
										{
											if (memcmp((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char)))
											{
												memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char));
											}
											x++;
										}
									}
								}
								else
								{
									size_t x = f;

									while (x < (f + str->length()))
									{
										if (memcmp((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char)))
										{
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char));
										}
										x++;
									}
								}
								_char term = '\0';
								memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
							}
							else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
							{
								size_t osiz = fileo_vec.d_vec[file_->lid].dsiz;

								if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + str->length()))
								{
									ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									_char* val_ = (_char*)malloc(str->length() + 1);
									_char* xval = (_char*)malloc(str->length() + 1);

									if (val_ && xval)
									{
										_char term = '\0';
										memcpy((void*)xval, (void*)&fileo_vec.d_vec[file_->lid].dat[f], str->length());
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[f], (void*)str->c_str(), str->length());
										memcpy((void*)&val_[str->length()], (void*)&term, sizeof(_char));
										memcpy((void*)&xval[str->length()], (void*)&term, sizeof(_char));
										size_t x = f + str->length();

										while (x + str->length() < fileo_vec.d_vec[file_->lid].dsiz)
										{
											memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], str->length());
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, str->length());
											memcpy((void*)xval, (void*)val_, str->length());
											x += str->length();
										}

										if (x < fileo_vec.d_vec[file_->lid].dsiz)
										{
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, fileo_vec.d_vec[file_->lid].dsiz - x);
										}

										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
										free(val_);
										free(xval);
										ret = 0;
										BOT_CRS crs(0, lid, f + str->length());
										ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
									}
								}
							}
							else {}
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
							size_t tot = 0;

							for (size_t siz = 0; siz < strvec->size(); siz++)
							{
								tot += strvec->at(siz).length();;
							}

							if (BOT_FILE_OVRL)
							{
								if (f + tot < file_->dsiz)
								{
									size_t x = f;

									for (size_t siz = 0; siz < strvec->size(); siz++)
									{
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)strvec->at(siz).c_str(), strvec->at(siz).length());
										x += strvec->at(siz).length();
										strvec->at(siz).clear();
									}
									ret = 0;
									strvec->clear();
									BOT_CRS crs(0, lid, f + tot);
									ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
								}
								else
								{

								}
							}
							else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
							{
								if (fileo_vec.d_vec[file_->lid].Alloc(fileo_vec.d_vec[file_->lid].dsiz + tot))
								{
									ud = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									_char* val_ = (_char*)malloc(tot + 1);
									_char* xval = (_char*)malloc(tot + 1);

									if (val_ && xval)
									{
										_char term = '\0';
										memcpy((void*)&val_[tot], (void*)&term, sizeof(_char));
										memcpy((void*)&xval[tot], (void*)&term, sizeof(_char));
										size_t x = f;

										for (size_t siz = 0; siz < strvec->size(); siz++)
										{
											memcpy((void*)xval[x - f], (void*)&fileo_vec.d_vec[file_->lid].dat[x], strvec->at(siz).length());
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)strvec->at(siz).c_str(), strvec->at(siz).length());
											x += strvec->at(siz).length();
											strvec->at(siz).clear();
										}

										while (x + tot < fileo_vec.d_vec[file_->lid].dsiz)
										{
											memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[x], tot);
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, tot);
											memcpy((void*)xval, (void*)val_, tot);
											x += tot;
										}

										if (x < file_->dsiz)
										{
											memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[x], (void*)xval, fileo_vec.d_vec[file_->lid].dsiz - x);
										}
										memcpy((void*)&fileo_vec.d_vec[file_->lid].dat[fileo_vec.d_vec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
										free(val_);
										free(xval);
										ret = 0;
										strvec->clear();
										BOT_CRS crs(0, lid, f + tot);
										ud = PushToVecEleMem((void*)&crs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
									}
								}
							}
							else {}
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

			if (!ret)
			{
				sint xret = SetVecEleMem(fileo_vec.d_vec[file_->lid].dat, MTX_FO, file_->lid, BOT_FS_DATP);
				xret = GetVecEle(file_, MTX_FO, file_->lid);
			}

			boto_file = false;
			ud = UpdMTXPrio();

			if (!ox)
			{
				ox = UnlockGMutex(MTX_FO);
			}
		}
	}
	return ret;
}

sint machine::BOTFileIN(BOT_FILE_M* file_, bool f_fdat, size_t from, size_t to, ...)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileIN(BOT_FILE_M* file_(%i), bool f_fdat(%u), size_t from(%u), size_t to(%u), ...)", (sint)file_, (uint)f_fdat, (uint)from, (uint)to);
		oc = Output(ncar.carr, 2);
	}
	if (!file_ || to < from)
	{
		return -1;
	}

	sint ret = -1;

	if (!f_fdat)
	{
		if (file_->cm == BOT_IO_CON)
		{
			sint ox = -1;

			if (file_->fcon < 0)
			{
				ret = GetFConn(file_, &ox);
			}
			if (file_->fcon > -1)
			{
				bool done = false;
				va_list args;
				va_start(args, to);

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
					case BOT_RTV_SINTP:
					{
						sint* delm = va_arg(args, sint*);
						sint* val_ = va_arg(args, sint*);

						if (val_ && delm)
						{
							size_t nt = bot_strlen((_char*)val_);
							_char term = '\0';

							for (size_t x = 0; x < nt; x++)
							{
								val_[x] = std::cin.get();

								if (!memcmp((void*)&val_[x], (void*)&term, sizeof(_char)))
								{
									x = nt;
								}
							}
							file_->fst.oa_loc += nt;
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CHARP:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_)
						{
							size_t nt = bot_strlen(val_);
							for (size_t x = 0; x < nt; x++)
							{
								std::cout.put(val_[x]);
							}
							file_->fst.oa_loc += nt;
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CCHAR:
					{
						c_char* val_ = va_arg(args, c_char*);

						if (val_)
						{
							size_t nt = bot_cstrlen(val_);
							for (size_t x = 0; x < nt; x++)
							{
								std::cout.put(val_[x]);
							}
							file_->fst.oa_loc += nt;
							ret = 0;
						}
						break;
					}
					case BOT_RTV_STR:
					{
						std::string* val_ = va_arg(args, std::string*);

						if (val_)
						{
							for (size_t x = 0; x < val_->length(); x++)
							{
								std::cout.put(val_->at(x));
							}
							file_->fst.oa_loc += val_->length();
							ret = 0;
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
			}
			if (!ox)
			{
				ox = CloseFConn(file_);
			}
			return 0;
		}
		else if (file_->cm == BOT_F_CON)
		{
			if (!to || to > (size_t)file_->fst.filestats.st_size)
			{
				if (file_->fst.filestats.st_size)
				{
					to = (size_t)file_->fst.filestats.st_size - 1;
				}
				else
				{
					return -1;
				}
			}

			sint ox = -1;
			ret = GetOFConn(file_, &ox);

			if (ret < 0)
			{
				ret = BOTOpenFile(file_, &ox);
			}

			if (file_->fcon > -1)
			{
				f_con[file_->fcon]->fstrm.seekg(from);
				ret = -1;
				boto_file = true;
				sint ud = UpdMTXPrio();
				bool done = false;
				va_list args;
				va_start(args, to);

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
					case BOT_RTV_SINTP:
					{
						sint* val_ = va_arg(args, sint*);

						if (val_ != NULL)
						{
							_char nc;
							for (size_t ct = 0; ct < to - from; ct++)
							{
								if (f_con[file_->fcon]->fstrm.get(*((_char*)&nc)))
								{
									memcpy((void*)&val_[ct], (void*)&nc, sizeof(_char));
								}
							}
							nc = '\0';
							memcpy((void*)&val_[to], (void*)&nc, sizeof(_char));
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CHARP:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_ != NULL)
						{
							_char nc;
							for (size_t ct = 0; ct < to - from; ct++)
							{
								if (f_con[file_->fcon]->fstrm.get(nc))
								{
									memcpy((void*)&val_[ct], (void*)&nc, sizeof(_char));
								}
							}
							nc = '\0';
							memcpy((void*)&val_[to], (void*)&nc, sizeof(_char));
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_UINTP:
					{
						uint* val_ = va_arg(args, uint*);

						if (val_ != NULL)
						{
							u_char nc;
							for (size_t ct = 0; ct < to - from; ct++)
							{
								if (f_con[file_->fcon]->fstrm.get(*((_char*)&nc)))
								{
									memcpy((void*)&val_[ct], (void*)&nc, sizeof(u_char));
								}
							}
							nc = (u_char)'\0';
							memcpy((void*)&val_[to], (void*)&nc, sizeof(u_char));
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_UCHARP:
					{
						u_char* val_ = va_arg(args, u_char*);

						if (val_ != NULL)
						{
							u_char nc;
							for (size_t ct = 0; ct < to - from; ct++)
							{
								if (f_con[file_->fcon]->fstrm.get(*((_char*)&nc)))
								{
									memcpy((void*)&val_[ct], (void*)&nc, sizeof(u_char));
								}
							}
							nc = (u_char)'\0';
							memcpy((void*)&val_[to], (void*)&nc, sizeof(u_char));
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_REAL:
					{
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

							while (f_con[file_->fcon]->fstrm.get(xc) && str_->length() < (size_t)BOT_STRLEN_MAX)
							{
								str_->push_back(xc);
							}
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_VSINT:
					{
						std::vector<sint>* val_ = va_arg(args, std::vector<sint>*);

						if (val_ != NULL)
						{
							while (f_con[file_->fcon]->fstrm.get(*((_char*)&ud)) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(ud);
							}
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_VCHAR:
					{
						std::vector<_char>* val_ = va_arg(args, std::vector<_char>*);

						if (val_ != NULL)
						{
							_char nc;

							while (f_con[file_->fcon]->fstrm.get(nc) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(nc);
							}
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_VUINT:
					{
						std::vector<uint>* val_ = va_arg(args, std::vector<uint>*);

						if (val_ != NULL)
						{
							while (f_con[file_->fcon]->fstrm.get(*((_char*)&ud)) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(ud);
							}
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_VUCHAR:
					{
						std::vector<u_char>* val_ = va_arg(args, std::vector<u_char>*);

						if (val_ != NULL)
						{
							u_char nc;

							while (f_con[file_->fcon]->fstrm.get(*((_char*)&nc)) && val_->size() < BOTVEC_LIM)
							{
								val_->push_back(nc);
							}
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_VREAL:
					{
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

							while (f_con[file_->fcon]->fstrm.get(xc) && nstr.length() < (size_t)BOT_STRLEN_MAX)
							{
								nstr.push_back(xc);
							}
							file_->fst.ia_loc = (size_t)f_con[file_->fcon]->fstrm.tellg();
							BOT_CRS ncs((sllint)f_con[file_->fcon], lid, file_->fst.ia_loc);
							ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
							strvec_->push_back(nstr);
							ret = 0;
						}
						break;
					}
					default:
					{
						done = true;
						break;
					}
					}

					if ((sint)f_con[file_->fcon]->fstrm.tellg() == to)
					{
						done = true;
					}
				}
				va_end(args);
				boto_file = false;
				ud = UpdMTXPrio();

				if (!ret)
				{
					ud = GetVecEle((void*)file_, MTX_FO, file_->lid);
				}
			}

			if (!ox)
			{
				ox = BOTCloseFile(file_);
			}
		}
		else if (file_->cm == BOT_DB_CON)
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
	}
	else
	{
		if (!file_->dsiz)
		{
			return -1;
		}

		if (!to || to > file_->dsiz - 1)
		{
			to = file_->dsiz - 1;
		}

		ret = -1;
		sint ox = -1;
		sint hx = LockGMutex(MTX_FO, &ox);

		if (hx > -1)
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
						for (ullint ct = from; ct < to - from; ct++)
						{
							memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[ct], sizeof(sint));
						}
						sint nc = (sint)'\0';
						memcpy((void*)&val_[to], (void*)&nc, sizeof(sint));
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_CHAR:
				{
					_char* val_ = va_arg(args, _char*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from; ct++)
						{
							memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[ct], sizeof(_char));
						}
						_char nc = '\0';
						memcpy((void*)&val_[to], (void*)&nc, sizeof(_char));
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_UINT:
				{
					uint* val_ = va_arg(args, uint*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from; ct++)
						{
							memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[ct], sizeof(uint));
						}
						uint nc = (uint)'\0';
						memcpy((void*)&val_[to], (void*)&nc, sizeof(uint));
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_UCHAR:
				{
					u_char* val_ = va_arg(args, u_char*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from; ct++)
						{
							memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[ct], sizeof(u_char));
						}
						u_char nc = (u_char)'\0';
						memcpy((void*)&val_[to], (void*)&nc, sizeof(u_char));
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_REAL:
				{
					float* val_ = va_arg(args, float*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from; ct++)
						{
							memcpy((void*)val_, (void*)&fileo_vec.d_vec[file_->lid].dat[ct], sizeof(float));
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
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
						for (ullint ct = from; ct < to - from && ct < BOT_STRLEN_MAX; ct++)
						{
							str_->push_back(fileo_vec.d_vec[file_->lid].dat[ct]);
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_VSINT:
				{
					std::vector<sint>* val_ = va_arg(args, std::vector<sint>*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from && val_->size() < BOTVEC_LIM; ct++)
						{
							val_->push_back((sint)fileo_vec.d_vec[file_->lid].dat[ct]);
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_VCHAR:
				{
					std::vector<_char>* val_ = va_arg(args, std::vector<_char>*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from && val_->size() < BOTVEC_LIM; ct++)
						{
							val_->push_back(fileo_vec.d_vec[file_->lid].dat[ct]);
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_VUINT:
				{
					std::vector<uint>* val_ = va_arg(args, std::vector<uint>*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from && val_->size() < BOTVEC_LIM; ct++)
						{
							val_->push_back((uint)fileo_vec.d_vec[file_->lid].dat[ct]);
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_VUCHAR:
				{
					std::vector<u_char>* val_ = va_arg(args, std::vector<u_char>*);

					if (val_ != NULL)
					{
						for (ullint ct = from; ct < to - from && val_->size() < BOTVEC_LIM; ct++)
						{
							val_->push_back((u_char)fileo_vec.d_vec[file_->lid].dat[ct]);
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::vector<float>* val_ = va_arg(args, std::vector<float>*);

					if (val_ != NULL)
					{
						float nc;
						for (ullint ct = from; ct < to - from && val_->size() < BOTVEC_LIM; ct++)
						{
							memcpy((void*)&nc, (void*)&fileo_vec.d_vec[file_->lid].dat[ct], sizeof(float));
							val_->push_back(nc);
						}
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::vector<std::string>* strvec_ = va_arg(args, std::vector<std::string>*);

					if (strvec_ != NULL)
					{
						std::string nstr;
						for (ullint ct = from; ct < to - from && nstr.length() < BOT_STRLEN_MAX && strvec_->size() < BOTVEC_LIM; ct++)
						{
							nstr.push_back(fileo_vec.d_vec[file_->lid].dat[ct]);
						}
						strvec_->push_back(nstr);
						BOT_CRS ncs(0, lid, to);
						ud = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
						ret = 0;
					}
					break;
				}
				default:
				{
					done = true;
					break;
				}
				}

				if (file_->dsiz - 1 == to)
				{
					done = true;
				}
			}
			va_end(args);
			boto_file = false;
			ud = UpdMTXPrio();

			if (!ox)
			{
				ox = UnlockGMutex(MTX_FO);
			}

			if (!ret)
			{
				ud = GetVecEle((void*)file_, MTX_FO, file_->lid);
			}
		}
	}
	return ret;
}
sint machine::BOTFileER(BOT_FILE_M* file_, bool f_fdat, size_t from, size_t to)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileER(BOT_FILE_M* file_(%i), bool f_fdat(%u), size_t from(%u), size_t to(%u))", (sint)file_, (uint)f_fdat, (uint)from, (uint)to);
		oc = Output(ncar.carr, 2);
	}
	if (!file_)
	{
		return -1;
	}

	sint ret = -1;

	if (!f_fdat)
	{
		if (file_->cm == BOT_F_CON)
		{
			ret = BOTFileStats(file_);
			sint sv_mth = file_->omode;
			sint ox = -1;

			if (file_->omode != BOT_FILE_OVRL)
			{
				file_->omode = BOT_FILE_OVRL;
			}

			if (file_->fcon < 0)
			{
				ret = BOTOpenFile(file_, &ox);
			}

			if (file_->fcon > -1)
			{
				if ((size_t)f_con[file_->fcon]->fstrm.tellp() != from)
				{
					f_con[file_->fcon]->fstrm.seekp(from);
				}

				if (to + 1 < (size_t)file_->fst.filestats.st_size)
				{
					if ((size_t)f_con[file_->fcon]->fstrm.tellg() != to + 1)
					{
						f_con[file_->fcon]->fstrm.seekg(to + 1);
					}
				}

				for (size_t x = from; x < (size_t)file_->fst.filestats.st_size; x++)
				{
					if (to + 1 < (size_t)file_->fst.filestats.st_size)
					{
						f_con[file_->fcon]->fstrm.put(f_con[file_->fcon]->fstrm.get());
					}
					else
					{
						x = file_->fst.filestats.st_size;
					}
					to++;
				}

				file_->omode = std::ios::trunc;
				sint nx = -1;
				ret = BOTOpenFile(file_, &nx);

				if (file_->omode != sv_mth)
				{
					file_->omode = sv_mth;
					ret = GetOFConn(file_, &nx);
				}
				if (!ox)
				{
					ox = BOTCloseFile(file_);
				}
			}

			if (ret > -1)
			{
				BOT_CRS ncs((sllint)f_con[file_->fcon], lid, from);
				sint xc = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);
			}
		}
	}
	else
	{
		if (file_->datp)
		{
			sint ox = -1;
			sint hx = LockGMutex(MTX_FO, &ox);

			if (hx > -1)
			{
				_char n = '\0';
				size_t y = to + 1;
				for (size_t x = from; x < file_->dsiz; x++)
				{
					if (y < file_->dsiz)
					{
						memcpy((void*)&file_->datp[x], (void*)&file_->datp[y], sizeof(_char));
					}
					else
					{
						memcpy((void*)&file_->datp[x], (void*)&n, sizeof(_char));
					}
					y++;
				}

				if (fileo_vec.d_vec[file_->lid].Alloc(file_->dsiz - (to - from)))
				{
					ret = SetVecEleMem((void*)&fileo_vec.d_vec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
				}

				BOT_CRS ncs(0, lid, from);
				sint xc = PushToVecEleMem((void*)&ncs, MTX_FO, file_->lid, BOT_FS_CRSV, 2, false);

				if (!ox)
				{
					ox = UnlockGMutex(MTX_FO);
				}
			}
		}
	}

	return ret;
}
sint machine::BOTCloseFile(sint flid, bool clear_conn, bool del, bool clear_dat)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_128 instr;
		sint oc = bot_sprintf(instr.carr, instr.siz, "::BOTCloseFile(sint flid(%i), bool clear_conn(%u), bool del(%u), bool clear_dat(%u))", flid, (uint)clear_conn, (uint)del, (uint)clear_dat);
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
		return BOTCloseFile(&xfile, clear_conn, del, clear_dat);
	}
	return -1;
}
sint machine::BOTCloseFile(BOT_FILE_M* xfile_, bool clear_conn, bool del, bool clear_dat)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_128 instr;
		sint oc = bot_sprintf(instr.carr, instr.siz, "::BOTCloseFile(BOT_FILE_M* xfile_(%i), bool clear_conn(%u), bool del(%u), bool clear_dat(%u))", (sint)xfile_, (uint)clear_conn, (uint)del, (uint)clear_dat);
		oc = Output(instr.carr, 2);
	}

	if (!xfile_)
	{
		return -1;
	}

	sint ret = -1;

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
		if (clear_dat)
		{
			ret = ClearVecEleMem(MTX_FO, xfile_->lid, BOT_FS_DAT, false);
		}

		if (del)
		{
			if (xfile_->fst.filestats.st_size)
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
			}
		}
		ret = CloseFConn(xfile_, clear_conn);

		if (ret < 0)
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
		ret = BOTRemoveFile(xfile_);

		if (ret)
		{
			ret = -1;
		}
		ret = ClearVecEle(MTX_FO, xfile_->lid, false);
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
sint machine::BOTSaveFile(BOT_FILE_M* file_, c_char* to_, bool ow)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_256 instr;
		sint oc = bot_sprintf(instr.carr, instr.siz, "::BOTSaveFile(BOT_FILE_M* file_(%i), c_char* to_(%i), bool ow(%u))", (sint)file_, (sint)to_, (uint)ow);
		oc = Output(instr.carr, 2);
	}
	if (!file_)
	{
		return -1;
	}

	sint ret = -1;
	BOT_FILE_M xfile;
	xfile.Renew(file_);
	xfile.lid = -1;

	if (to_)
	{
		if (strcmp(xfile.path.c_str(), to_))
		{
			xfile.path.clear();
			xfile.path.append(to_);
		}
	}

	ret = BOTFileStats(&xfile);

	if (!ret)
	{
		carr_24 ncar;
		sint ct = 0;
		sint hx = 0;

		while (!hx && ct < INT32_MAX)
		{
			sint op = bot_sprintf(ncar.carr, ncar.siz, "(%i)", ++ct);
			xfile.name.clear();
			xfile.name.append(file_->name.c_str());
			xfile.name.append(ncar.carr);
			hx = BOTFileStats(&xfile);
		}
	}

	sint ox = -1;
	ret = BOTOpenFile(&xfile, &ox, true);

	if (ret > -1)
	{
		if (file_->datp)
		{
			ret = BOTFileOUT(&xfile, 0, false, BOT_RTV_CHARP, file_->datp, BOT_RTV_MAX);

			if (ret > -1)
			{
				if (ow)
				{
					bool wo = false;

					if (file_->fcon > -1)
					{
						wo = true;
						ret = CloseFConn(file_, true);
					}

					ret = BOTRemoveFile(file_);

					if (!ret)
					{
						ret = BOTCloseFile(&xfile);

						if (ret > -1)
						{
							ox = -1;
							ret = BOTRenameFile(&xfile, BOTFileStr(file_).c_str());

							if (!ret)
							{
								ret = ClearVecEle(MTX_FO, xfile.lid, false);
								file_->lid = -1;

								if (wo)
								{
									ret = BOTOpenFile(file_, &ox);
								}
							}
						}
					}
				}
				else
				{
					ret = 0;
				}
			}
		}
		if (!ox)
		{
			ox = BOTCloseFile(&xfile);
		}
	}
	return ret;
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
void machine::Nanosleep(sllint dur)
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
sllint machine::nsRest(sllint i, bool keep_mtx)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 instr;
		sint oc = bot_sprintf(instr.carr, instr.siz, "::nsRest(sllint i(%lli), bool keep_mtx(%u))", i, (uint)keep_mtx);
		oc = Output(instr.carr, 2);
	}
	stk_ct++;
	std::chrono::steady_clock::time_point t_I = std::chrono::steady_clock::now();
	
	if (i < (sllint)BOT_NANO_REST)
	{
		i = (sllint)BOT_NANO_REST;
	}

	//std::vector<lok_req> relocks;
	std::chrono::steady_clock::time_point t_II;
	std::chrono::duration<sllint, std::nano> span;
	sllint slpct = 0;

	while (slpct < i)
	{
		if (!keep_mtx && !h_mtxs.empty())
		{
			size_t blox = relocks.size();
			sint cheq = CheqMTXReqs(&relocks);

			if (relocks.size() > blox)
			{
				size_t elox = relocks.size() - blox;

				for (size_t x = blox; x < blox + elox; x++)
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
		t_II = std::chrono::steady_clock::now();
		span = std::chrono::duration_cast<std::chrono::nanoseconds>(t_II - t_I);
		slpct = (sllint)span.count();
	}

	if (!keep_mtx && stk_ct == 1)
	{
		for (size_t x = 0; x < relocks.size(); x++)
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
	t_II = std::chrono::steady_clock::now();
	span = std::chrono::duration_cast<std::chrono::nanoseconds>(t_II - t_I);
	slpct = (sllint)span.count();

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
sllint machine::Rest(sllint i, bool keep_mtx)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 instr;
		sint oc = bot_sprintf(instr.carr, instr.siz, "::Rest(sllint i(%lli), bool keep_mtx(%u))", i, (uint)keep_mtx);
		oc = Output(instr.carr, 2);
	}
	stk_ct++;
	std::chrono::steady_clock::time_point t_I = std::chrono::steady_clock::now();

	if (i < (sllint)BOT_MILLI_REST)
	{
		i = (sllint)BOT_MILLI_REST;
	}

	//std::vector<lok_req> relocks;
	std::chrono::steady_clock::time_point t_II;
	std::chrono::duration<sllint, std::milli> span;
	sllint slpct = 0;

	while (slpct < i)
	{
		if (!keep_mtx && !h_mtxs.empty())
		{
			size_t blox = relocks.size();
			sint cheq = CheqMTXReqs(&relocks);

			if (relocks.size() > blox)
			{
				size_t elox = relocks.size() - blox;

				for (size_t x = blox; x < blox + elox; x++)
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

		t_II = std::chrono::steady_clock::now();
		span = std::chrono::duration_cast<std::chrono::milliseconds>(t_II - t_I);
		slpct = (sllint)span.count();
	}

	if (!keep_mtx && stk_ct == 1)
	{
		for (size_t x = 0; x < relocks.size(); x++)
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
	t_II = std::chrono::steady_clock::now();
	span = std::chrono::duration_cast<std::chrono::milliseconds>(t_II - t_I);
	slpct = (sllint)span.count();

	if (debug_lvl >= 1000 && debug_m)
	{
		if (slpct)
		{
			carr_128 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "attempted to rest:%lims, rested for:%lims", i, (sllint)span.count());
			op = Output(outp.carr, 2);
		}
	}
	return slpct;
}

// Console I/O Functions

sint machine::UNRTS()
{
	if (debug_lvl >= 1000 && debug_m)
	{
		sint oc = Output("::UNRTS()", 2);
	}
	
	sint ox = -1;
	sint hx = LockGMutex(MTX_STRT, &ox);

	if (hx > -1)
	{
		hx = bot_strt_s.Update(&msy);
		hx = msy.Update(&bot_strt_s);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_STRT);
		}
	}
	return hx;
}
sint machine::BOTCOutput(std::string* np)
{
	if (!np)
	{
		return -1;
	}

	sint h = -1;
	sint p = LockGMutex(MTX_O, &h);

	if (p > -1)
	{
		for (size_t x = 0; x < np->length(); x++)
		{
			std::cout.put(np->at(x));
		}

		if (!h)
		{
			h = UnlockGMutex(MTX_O);
		}
		return 0;
	}
	return -1;
}

sint machine::Output(c_char* op_, sint opt, bool newl)
{
	carr_64 tdata;
	sint xc = GetTimeMS(tdata.carr);
	carr_256 instr;
	sint rc = GetPCliMem(BOT_C_PRIV, &xc);

	if (xc > 99)
	{
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][%s] ", lid, ptn.c_str());
	}
	else
	{
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][machine] ", lid);
	}
	std::string str(tdata.carr);
	str.append(instr.carr);
	str.append(op_);

	if (newl)
	{
		str.push_back('\n');
	}

	if (opt > -1)
	{
		xc = LogPut(str.c_str(), opt);

		if (!opt)
		{
			rc = BOTCOutput(&str);
		}
	}
	return xc;
}

sint machine::Output(bool newl, c_char* op_, ...)
{
	carr_64 tdata;
	sint xc = GetTimeMS(tdata.carr);
	carr_256 instr;
	sint rc = GetPCliMem(BOT_C_PRIV, &xc);

	if (xc > 99)
	{
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][%s] ", lid, ptn.c_str());
	}
	else
	{
		xc = bot_sprintf(instr.carr, instr.siz, " [%i][machine] ", lid);
	}
	std::string str(tdata.carr);
	str.append(instr.carr);
	str.append(op_);

	if (newl)
	{
		str.push_back('\n');
	}

	va_list args;
	va_start(args, op_);

	for (uint x = 0; x < (uint)BOT_OP_OPTS; x++)
	{
		rc = va_arg(args, sint);

		if (rc < 0 || rc >(uint)BOT_OP_OPTS)
		{
			x = (uint)BOT_OP_OPTS;
		}
		else
		{
			xc = LogPut(str.c_str(), rc);

			if (rc < 1)
			{
				if (!rc)
				{
					rc = BOTCOutput(&str);
				}
				x = (uint)BOT_OP_OPTS;
			}
		}
	}
	va_end(args);
	return xc;
}

sint machine::BOTCInput(std::string* np, carr_64* tdata)
{
	if (!tdata)
	{
		return -1;
	}
	
	sint h = -1;
	sint p = LockGMutex(MTX_O, &h);

	if (p > -1)
	{
		sllint rst = 0;
		sint chk = '\n';
		sint spc = ' ';
		sint x = -1;
		sint rc = -1;

		while (x > -2 && np->length() < (size_t)BOT_STRLEN_MAX)
		{
			rc = std::cin.get();

			if (rc)
			{
				if (x < 0)
				{
					if (!memcmp((void*)&spc, (void*)&rc, sizeof(sint)))
					{

					}
					else if (!memcmp((void*)&bot_strt_s.nrts_term[0], (void*)&rc, sizeof(sint)) || !memcmp((void*)&chk, (void*)&rc, sizeof(sint)))
					{
						x = -2;
					}
					else
					{
						np->push_back(rc);
						x = 0;
					}
				}
				else if (rc)
				{
					if (!memcmp((void*)&chk, (void*)&rc, sizeof(sint)) || !memcmp((void*)&bot_strt_s.nrts_term[0], (void*)&rc, sizeof(sint)))
					{
						x = -2;
					}
					else
					{
						np->push_back(rc);
					}
				}
			}
			else
			{
				rst = nsRest(BOT_IO_REST);
			}
		}

		x = GetTimeMS(tdata->carr);

		if (!h)
		{
			h = UnlockGMutex(MTX_O);
		}
		return 0;
	}
	return -1;
}
sint machine::Input(c_char* prp, std::string* np, bool itrp)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 xcar;
		sint op = bot_sprintf(xcar.carr, xcar.siz, "::Input(c_char* prp(%i), std::string* np(%i), bool itrp(%u))", (sint)prp, (sint)np, (uint)itrp);
		op = Output(xcar.carr, 2);
	}
	if (!np)
	{
		return -1;
	}

	sint ret = UNRTS();

	if (prp)
	{
		sint op = Output(prp, 0, false);
	}

	std::vector<std::string> args;
	std::vector<BOT_ARG> vec;
	carr_64 tdata;
	carr_512 instr;
	std::string nstr;
	std::string str;
	sint xc = GetPCliMem(BOT_C_NAME, &nstr);
	ret = vtool.CombV(&args, VTV_VSTR, VTV_VCHAR, &msy.nrts_sep, VTV_VCHAR, &msy.nrts_lit, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_, VTV_MAX);
	sint x = BOTCInput(np, &tdata);

	if (np->length() > 1)
	{
		ret = ArgSep(&vec, false, 0, np->length() - 1, np->c_str(), BOT_RTV_VSTR, &args);

		if (!strcmp(np->substr(0, 2).c_str(), "/#"))
		{
			np->clear();
			ret = Command(&vec);
			np->append(stool.VToStr(&vec, " ").c_str());
		}
		else
		{
			
		}
	}
	else
	{
		BOT_ARG a(0, np->c_str());
		vec.push_back(a);
	}

	if (itrp)
	{
		
	}

	if (nstr.empty())
	{
		x = GetPCliMem(BOT_C_NAME, &nstr);
	}

	x = bot_sprintf(instr.carr, instr.siz, "%s [%i][%s] ", tdata.carr, lid, nstr.c_str());
	str.append(instr.carr);
	str.append(np->c_str());
	x = LogPut(str.c_str(), 0);
	x = LogPut(str.c_str(), 2);
	str.clear();
	nstr.clear();
	bot_strclr(tdata.carr);
	bot_strclr(instr.carr);
	return xc;
}

sint machine::BOTConsole(c_char* prp)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_64 xcar;
		sint op = bot_sprintf(xcar.carr, xcar.siz, "::BOTConsole(c_char* prp(%i))", (sint)prp);
		op = Output(xcar.carr, 2);
	}
	
	std::string np;
	sint rc = Input(prp, &np);
	return rc;
}

// Str Manip

std::string machine::EStr(c_char* str_)
{
	if (debug_lvl >= 1100 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "EStr(string *str_(%i))", (sint)str_);
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

std::string machine::UCASE(c_char* str_)
{
	if (debug_lvl >= 1500 && debug_m)
	{
		carr_48 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::UCASE(c_char* str_(%i))", (sint)str_);
		oc = Output(ncar.carr, 2);
	}

	std::string r_str;

	if (!str_)
	{
		return r_str;
	}

	size_t slen = bot_cstrlen(str_);

	for (size_t i = 0; i < slen; i++)
	{
		if (bot_sisa(&str_[i], 1))
		{
			r_str.push_back(toupper(str_[i]));
		}
		else
		{
			r_str.push_back(str_[i]);
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

std::string machine::LCASE(c_char* str_)
{
	if (debug_lvl >= 1500 && debug_m)
	{
		carr_48 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::LCASE(c_char* str_(%i))", (sint)str_);
		oc = Output(ncar.carr, 2);
	}

	std::string r_str;

	if (!str_)
	{
		return r_str;
	}

	size_t slen = bot_cstrlen(str_);

	for (size_t i = 0; i < slen; i++)
	{
		if (bot_sisa(&str_[i], 1))
		{
			r_str.push_back(tolower(str_[i]));
		}
		else
		{
			r_str.push_back(str_[i]);
		}
	}

	if (debug_lvl >= 1100 && debug_m)
	{
		std::string output;
		output.append("lowercased: ");
		output.append(r_str);
		sint oc = Output(output.c_str(), 2);
	}
	return r_str;
}

std::string machine::CPunc(c_char* i_)
{
	if (debug_lvl >= 1500 && debug_m)
	{
		carr_48 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::CPunc(c_char* str_(%i))", (sint)i_);
		oc = Output(ncar.carr, 2);
	}
	std::string str;

	if (!i_)
	{
		return str;
	}

	size_t slen = strlen(i_);

	for (size_t i = 0; i < slen; i++)
	{
		if (bot_sisa(&i_[i], 1) || bot_sisn(&i_[i], 1))
		{
			str.push_back(i_[i]);
		}
	}
	return str;
}
// SQL statement manip

sint machine::AnalyzeStmt(BOT_STMT *t_)
{
	if (debug_lvl >= 110 && debug_m)
	{
		carr_48 outp;
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

	if (t_->stmt.empty())
	{
		return -1;
	}
	std::string stmt(t_->stmt.c_str());
	t_->Clear();
	std::vector<BOT_ARG> rets;
	std::vector<std::string> args;
	sint xc = vtool.CombV(&args, VTV_VSTR, VTV_CCAR, " ", VTV_CCAR, "\t", VTV_VSTR, &msy.sql_trans_keywords, VTV_VSTR, &msy.sql_spec_keywords, VTV_MAX);
	xc = ArgSep(&rets, true, 0, stmt.length() - 1, stmt.c_str(), BOT_RTV_VSTR, &args);

	if (xc > -1)
	{
		args.clear();

		for (size_t x = 0; x < rets.size(); x++)
		{
			if (strcmp(" ", rets[x].arg.c_str()) && strcmp("\t", rets[x].arg.c_str()))
			{
				args.push_back(rets[x].arg);
			}
			rets[x].arg.clear();
		}
		rets.clear();
		t_->it_type = vtool.VIV(&msy.sql_trans_keywords, args[0].c_str());

		if (t_->it_type > -1)
		{
			switch (t_->it_type)
			{
			case 0:
			{
				if (args.size() > 1)
				{
					sint rc = ArgSep(&rets, false, 0, args[1].length() - 1, args[1].c_str(), BOT_RTV_VCHAR, &msy.sql_opers_keywords);
					rc = -1;
				}
				break;
			}
			case 1:
			{
				if (args.size() > 1)
				{
					t_->ic_type = 1;
					sint rc = ArgSep(&rets, false, 0, args[1].length() - 1, args[1].c_str(), BOT_RTV_VCHAR, &msy.sql_opers_keywords);

					if (rc > -1)
					{
						if (rets.size() > 1)
						{
							if (!strcmp(rets[1].arg.c_str(), "."))
							{
								t_->dbname.append(rets[0].arg.c_str());
							}

							if (rets.size() > 2)
							{
								_char brk = '[';
								if (!memcmp((void*)&rets[2].arg[0], (void*)&brk, sizeof(_char)))
								{
									t_->cont.append(rets[2].arg.substr(1, rets[2].arg.length() - 2).c_str());
								}
								else
								{
									t_->cont.append(rets[2].arg.c_str());
								}
							}
							rets.clear();
						}
						else
						{
							_char brk = '[';
							if (!memcmp((void*)&rets[0].arg[0], (void*)&brk, sizeof(_char)))
							{
								t_->cont.append(rets[0].arg.substr(1, rets[0].arg.length() - 2).c_str());
							}
							else
							{
								t_->cont.append(rets[0].arg.c_str());
							}
						}
					}
					rets.clear();
				}
				break;
			}
			case 2:
			{
				if (args.size() > 4)
				{
					t_->ic_type = 1;
					sint rc = ArgSep(&rets, false, 0, args[1].length() - 1, args[1].c_str(), BOT_RTV_VCHAR, &msy.sql_opers_keywords);

					if (rc > -1)
					{
						if (rets.size() > 1)
						{
							t_->dbname.append(rets[0].arg.c_str());
							_char brk = '[';
							if (!memcmp((void*)&rets[1].arg[0], (void*)&brk, sizeof(_char)))
							{
								t_->cont.append(rets[1].arg.substr(1, rets[1].arg.length() - 2).c_str());
							}
							else
							{
								t_->cont.append(rets[1].arg.c_str());
							}
							rets.clear();
						}
						else
						{
							_char brk = '[';
							if (!memcmp((void*)&rets[0].arg[0], (void*)&brk, sizeof(_char)))
							{
								t_->cont.append(rets[0].arg.substr(1, rets[0].arg.length() - 2).c_str());
							}
							else
							{
								t_->cont.append(rets[0].arg.c_str());
							}
						}
						rets.clear();
						std::vector<_char> nargs;
						rc = vtool.CombV(&nargs, VTV_VCHAR, VTV_VCHAR, &msy.nrts_end, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_, VTV_VCHAR, &msy.nrts_sep, VTV_MAX);
						rc = ArgSep(&t_->cols, false, 0, args[2].length() - 2, args[2].substr(1,args[2].length() - 2).c_str(), BOT_RTV_VCHAR, &nargs);
						rc = ArgSep(&t_->vals, false, 0, args[4].length() - 2, args[4].substr(1, args[4].length() - 2).c_str(), BOT_RTV_VCHAR, &nargs);
					}
				}
				break;
			}
			case 3:
			{
				if (args.size() > 1)
				{
					std::vector<std::string> nargs;
					vtool.CombV(&nargs, VTV_VSTR, VTV_VSTR, &msy.sql_cond_qual_keywords, VTV_VSTR, &msy.sql_obj_qual_keywords, VTV_VSTR, &msy.sql_obj_keywords, VTV_MAX);
					sint rc = ArgSep(&rets, false, 0, args[1].length() - 1, args[1].c_str(), BOT_RTV_VSTR, &msy.sql_obj_qual_keywords);

					if (rc > -1)
					{
						rc = vtool.VIV(&msy.sql_cond_qual_keywords, rets[0].arg.c_str());

						if (rc > -1)
						{

						}
					}
					rets.clear();
				}
				break;
			}
			case 4:
			{

				break;
			}
			case 5:
			{

				break;
			}
			case 6:
			{

				break;
			}
			case 7:
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
	t_->an = true;
	return xc;
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

	if (t_->spec > -1 && (!t_->vals.empty() || !t_->cols.empty() || !t_->conds.empty()))
	{
		statement.append(msy.sql_spec_keywords[t_->spec].c_str());
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
		statement.append(msy.sql_decl_keywords[t_->opts[0]].c_str());
		statement.append(t_->cols[x].c_str());
		x++;
		statement.append(msy.sql_order_keywords[t_->opts[1]].c_str());
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

	if (!t_->it_type || !strcmp(msy.sql_trans_keywords[t_->it_type].c_str(), "SELECT"))
	{
		sint xc = BQS(t_);
		return xc;
	}

	std::string statement;
	statement.append(msy.sql_trans_keywords[t_->it_type].c_str());

	if (t_->it_type == 3 || t_->it_type == 5 || t_->it_type == 7)
	{
		if (t_->ospec > -1)
		{
			statement.append(" ");
			statement.append(msy.sql_obj_qual_keywords[t_->ospec].c_str());
		}

		statement.append(" ");
		statement.append(msy.sql_obj_keywords[t_->ic_type].c_str());
	}

	if (t_->ifex > -1)
	{
		statement.append(" ");
		statement.append(msy.sql_cond_qual_keywords[t_->ifex].c_str());
	}

	if (t_->it_type == 4 && t_->ic_type)
	{
		statement.append(" ");
		statement.append(msy.sql_targ_keywords[1].c_str());
	}

	if (t_->cont.empty())
	{
		if (!t_->dbname.empty() && t_->it_type == 9)
		{
			statement.clear();
			carr_512 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "%s %s AS %s;", msy.sql_trans_keywords[t_->it_type].c_str(), t_->dbname.c_str(), t_->dbname.c_str());
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
			statement.append(msy.sql_targ_keywords[2].c_str());
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
						statement.append(t_->cols[x].c_str());
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
								statement.append(t_->vals[x].c_str());
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
			statement.append(msy.sql_act_keywords[t_->act].c_str());

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

		if (t_->spec > -1)
		{
			if (t_->spec == 0)
			{
				statement.append(" ");
				statement.append(msy.sql_spec_keywords[t_->spec].c_str());

				for (uint x = 0; x < t_->conds.size(); x++)
				{
					statement.append(" ");
					statement.append(t_->conds[x]);
				}
			}
			else if (t_->spec == 2)
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
		trans.spec = t_->opts[11][1];
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
		for (size_t i = 0; i < pend_->size(); i++)
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

	for (size_t i = 0; i < stmts_->size(); i++)
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
			xc = bot_sprintf(ncar.carr, ncar.siz, "building maint/modi statements for %s", com_->dbs[i].name.c_str());
			xc = Output(ncar.carr, 2);
		}

		BOT_STMT trans((bool)db_maint[i], 1, com_->dbs[i].name.c_str(), "LAST_ACCESS", 1);
		trans.spec = 0;
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
	if (debug_lvl >= 550 && debug_m)
	{
		carr_48 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::GetODBConn(BOT_DB_M *db_(5i))", (sint)db_);
		oc = Output(ncar.carr, 2);
	}
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
sint machine::GetDBConn(BOT_DB_M* db_, slint mt)
{
	if (debug_lvl >= 550 && debug_m)
	{
		carr_72 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::GetDBConn(BOT_DB_M *db_(5i), slint mt(%li))", (sint)db_, mt);
		oc = Output(ncar.carr, 2);
	}
	if (!db_)
	{
		return -1;
	}

	sint ret = GetODBConn(db_);

	if (ret > -1)
	{
		return ret;
	}

	sllint rst = -1;

	while (mt > -1 && !d_con_)
	{
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
						db_->fcon = siz;
						ret = SetVecEleMem((void*)&db_->fcon, MTX_DBL, db_->lid, BOT_DB_FCON, false);
						d_con_->Renew(db_->name.c_str(), db_->lid, db_->omode, siz);
						ret = siz;
						siz = BOT_ATT_LIM;
						mt = -1;
					}
				}
			}
			if (!h)
			{
				h = UnlockGMutex(MTX_DBC);
			}
		}
		mt--;
		rst = nsRest((sllint)BOT_FO_REST);
	}
	return ret;
}
sint machine::CloseDBConn(BOT_DB_M* db_)
{
	if (debug_lvl >= 550 && debug_m)
	{
		carr_48 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::CloseDBConn(BOT_DB_M *db_(5i))", (sint)db_);
		oc = Output(ncar.carr, 2);
	}

	sint xc = -1;
	sint hlim = -1;
	sint plim = LockGMutex(MTX_DBC, &hlim);

	if (plim > -1)
	{
		sint f_ele = d_con_->lid;
		d_con_->Clear();
		xc = UnlockElement(MTX_DBC, f_ele, false);

		if (!xc)
		{
			d_con_ = 0;
			xc = UpdMTXPrio();
		}
		if (!hlim)
		{
			hlim = UnlockGMutex(MTX_DBC);
		}
	}
	return xc;
}
sint machine::OpenOpt(sint opt) { if (opt < 0) { return -1; } if (!opt) { return 0; } if (opt < 3) { return 2; } if (opt < 9) { return 3; } return -1; }
sint machine::OpenDB(sint db_lid, sint x, sint* was_open, sint* fwas_locked, bool r_to_st)
{
	if (debug_lvl >= 550 && debug_m)
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
	sint xc = BOTPath(&pth, BOT_DBD_NM);
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
		dbc = GetDBConn(db_);

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
				xc = BOTFileStr(&dbt, &nfilem);
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
					xc = Output(true, GetError().c_str(), 1, 2, -1);

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
							sllint rst = Rest((sllint)BOT_MILLI_REST, true);
							break;
						}
						default:
						{
							xc = Output(true, GetError().c_str(), 1, 2, -1);
							done = true;
							break;
						}
						}
					}

					rc = sqlite3_finalize(ppstmt);

					if (rc)
					{
						xc = Output(true, GetError().c_str(), 1, 2, -1);
					}
				}
				else
				{
					d_con_->o_com = false;
					rc = UpdMTXPrio();
					xc = Output(true, GetError().c_str(), 1, 2, -1);

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
			xc = Output(true, GetError().c_str(), 1, 2, -1);
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

					if (olim > 0)
					{
						olim--;
						nulim = olim;
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

					if (olim > 0)
					{
						olim--;
						nulim = olim;
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
					sllint rst = Rest((sllint)BOT_MILLI_REST, true);
					break;
				}
				default:
				{
					xc = Output(true, GetError().c_str(), 1, 2, -1);
					done = true;
					break;
				}
				}
			}
			xc = sqlite3_finalize(ppstmt);

			if (xc)
			{
				xc = Output(true, GetError().c_str(), 1, 2, -1);
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
					xc = Output(true, GetError().c_str(), 1, 2, -1);
					return -1;
				}
				else
				{
					if (olim > 0)
					{
						olim--;
						nulim = olim;
					}
					if (clear_conn)
					{
						xc = CloseDBConn(db_);

						if (xc < 0)
						{
							xc = Output(true, "Error CloseDBConn()", 1, 2, -1);
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
			ret = Output(true, GetError().c_str(), 1, 2, -1);
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
					sint xp = Output(true, GetError().c_str(), 1, 2, -1);
					done = true;
					break;
				}
				}
			}

			ret = sqlite3_finalize(ppstmt);

			if (ret)
			{
				sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
								sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
									sint xp = Output(true, GetError().c_str(), 1, 2, -1);
									break;
								}
								}
								rc = sqlite3_finalize(ppstmt);

								if (rc)
								{
									sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
									sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
											sint xp = Output(true, GetError().c_str(), 1, 2, -1);
											sdone = true;
											break;
										}
										}
									}
									rc = sqlite3_finalize(ppstmt);

									if (rc)
									{
										sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
						sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
							sint xp = Output(true, GetError().c_str(), 1, 2, -1);
							break;
						}
						}
						rc = sqlite3_finalize(ppstmt);

						if (rc)
						{
							sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
								sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
									sint xp = Output(true, GetError().c_str(), 1, 2, -1);
									break;
								}
								}
								rc = sqlite3_finalize(ppstmt);

								if (rc)
								{
									sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
		sint xc = BOTPath(&pth, BOT_DBD_NM);
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
				rc = Output(true, output.c_str(), 1, 2, -1);
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
				trans.spec = 2;
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
									op = Output(true, outp.carr, 1, 2, -1);
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
						t.spec = 2;
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
									op = Output(true, outp.carr, 1, 2, -1);
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
					rc = Output(true, GetError().c_str(), 1, 2, -1);
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
			rc = Output(true, GetError().c_str(), 1, 2, -1);
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
			t.spec = 2;
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
				t.spec = 0;
				_char dval[(sizeof(syms_->at(nsiz).sym) * 2) + 4]{ 0 };
				rc = bot_sprintf(dval, sizeof(dval), "X'%02X'", syms_->at(nsiz).sym);
				rc = t.AddCond(0, "SYMBOL", msy.sql_comp_keywords[5].c_str(), dval);
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
				rc = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), outc);
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
					rc = Output(true, GetError().c_str(), 1, 2, -1);
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
							rc = Output(true, GetError().c_str(), 1, 2, -1);
							done = true;
							break;
						}
						}
					}

					rc = sqlite3_finalize(ppstmt);

					if (rc)
					{
						sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
			t.spec = 2;

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
			t.spec = 0;
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
				sint xp = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), stool.ITOA(syms_->at(eles[x]).id).c_str());
			}
			_char str_[(sizeof(syms_->at(eles[x]).sym) * 2) + 4]{ 0 };
			sint xc = bot_sprintf(str_, sizeof(str_), "X'%02X'", syms_->at(eles[x]).sym);
			xc = t.AddCond(0, "SYMBOL", msy.sql_comp_keywords[5].c_str(), str_);
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
				t.spec = 0;

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
						rc = t.AddCond(0, "DATA", msy.sql_comp_keywords[5].c_str(), str.c_str());
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
					rc = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), outc);
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
					rc = Output(true, GetError().c_str(), 1, 2, -1);
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
							sint xp = Output(true, GetError().c_str(), 1, 2, -1);
							done = true;
							break;
						}
						}
					}

					rc = sqlite3_finalize(ppstmt);

					if (rc)
					{
						sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
				t.spec = 2;

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
				t.spec = 0;
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
					sint xp = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), stool.ITOA(codes_->at(eles[x]).id).c_str());
				}

				std::string xstr;
				xstr.append("X'");
				xstr.append(con_str.c_str());
				xstr.append("'");
				sint xc = t.AddCond(0, "DATA", msy.sql_comp_keywords[5].c_str(), xstr.c_str());
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
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetCommand(BOTCOMMAND *Command_(%i), std::vector<std::string> *conds_(%i))", (sint)Command_, (sint)conds_);
		op = Output(outp.carr, 2);
	}
	if (!Command_)
	{
		return -1;
	}
	std::vector<BOTCOMMAND> vec;
	vec.push_back(*Command_);
	sint xc = GetCommands(&vec);

	if (xc > -1 && !vec.empty())
	{
		Command_->Renew(&vec[0]);
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
			t.spec = 0;

			if (!Commands_->at(x).cmd.empty())
			{
				xc = t.AddCond(0, "CMD", msy.sql_comp_keywords[5].c_str(), EStr(UCASE(CPunc(Commands_->at(x).cmd.c_str()).c_str()).c_str()).c_str());
			}
			if (Commands_->at(x).cmd_id > 0)
			{
				xc = t.AddCond(0, "CMD_ID", msy.sql_comp_keywords[5].c_str(), stool.ITOA(Commands_->at(x).cmd_id).c_str());
			}
			if (Commands_->at(x).id > 0)
			{
				xc = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), stool.ITOA(Commands_->at(x).id).c_str());
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
			Commands_->at(x).Clear();
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
					t.spec = 0;
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
			t.spec = 0;
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
			sint ret = 0;
			d_con_->o_com = true;
			rc = UpdMTXPrio();

			for (uint s = 0; s < stmts.size(); s++)
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
								GetPCliMem(BOT_C_PRIV, &xc);

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
									while ((sint)Commands_->size() <= ret)
									{
										BOTCOMMAND n;
										Commands_->push_back(n);
									}
									Commands_->at(ret).priv = rc;

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

									rc = FindColumn("CMD", ppstmt);

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
							done = true;
							rc = Output(true, GetError().c_str(), 1, 2, -1);
							break;
						}
						}
					}

					rc = sqlite3_finalize(ppstmt);

					if (rc)
					{
						rc = Output(true, GetError().c_str(), 1, 2, -1);
					}

				}
				else
				{
					rc = Output(true, GetError().c_str(), 1, 2, -1);
				}
			}
			d_con_->o_com = false;
			rc = UpdMTXPrio();

			if (!hdb)
			{
				hdb = CloseDB(&dbs, &fdb);
			}
			ret = vtool.SortV(Commands_, VTV_VCMD, BOT_CMD_CID);
			return ret;
		}
	}
	return -1;
}
sint machine::GetLogin(c_char* str_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 ncar;
		sint xc = bot_sprintf(ncar.carr, ncar.siz, "::GetLogin(c_char* str_(%i))", (sint)str_);
		xc = Output(ncar.carr, 2);
	}

	if (!str_)
	{
		return -1;
	}

	BOT_STMT t(false, 0, "litebot", "ACCOUNTS", 1);
	std::string clstr;
	sint xc = GetPCliMem(BOT_C_LOGIN_NAME, &clstr);
	t.AddCond(0, "LOGIN_NAME", msy.sql_comp_keywords[5].c_str(), EStr(UCASE(clstr.c_str()).c_str()).c_str());
	t.spec = 0;
	t.rlim = 1;
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
							if (!strcmp(str_, reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, 2))))
							{
								_char dated[128]{ 0 };
								xc = GetDateTime(dated);
								bot_cstrclr(str_);
								xc = 0;
								xc = SetPCliMem(BOT_C_F_LOGINS, &xc);
								std::string str;
								xc = SetClientLoggedIn(true);
								xc = FindColumn("ID", ppstmt);

								if (xc > -1)
								{
									sint vc = sqlite3_column_int(ppstmt, xc);
									sint rc = SetPCliMem(BOT_C_ID, &vc);
								}

								xc = FindColumn("RAW_NAME", ppstmt);

								if (xc > -1)
								{
									if (sqlite3_column_text(ppstmt, xc) != NULL)
									{
										str.append(reinterpret_cast <c_char*> (sqlite3_column_text(ppstmt, xc)));
										sint rc = SetPCliMem(BOT_C_NAME, (void*)str.c_str());
										str.clear();
									}
								}

								//Client.password.append( reinterpret_cast < c_char* > ( sqlite3_column_text( ppstmt, 2 ) ) );
								xc = FindColumn("PRIV", ppstmt);

								if (xc > -1)
								{
									sint vc = sqlite3_column_int(ppstmt, xc);
									sint rc = SetPCliMem(BOT_C_PRIV, &vc);
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
										sint rc = SetPCliMem(BOT_C_L_LOGIN, &str);
										str.clear();
									}
								}

								xc = FindColumn("TOTAL_LOGINS", ppstmt);

								if (xc > -1)
								{
									sint vc = sqlite3_column_int(ppstmt, xc) + 1;
									sint rc = SetPCliMem(BOT_C_T_LOGINS, &vc);
								}

								xc = SetPCliMem(BOT_C_L_DATE, dated);
							}
							else
							{
								_char dated[128]{ 0 };
								xc = GetDateTimeMS(dated);
								std::string str;
								str.append(dated);
								xc = SetPCliMem(BOT_C_LFL, &str);
								str.clear();
								xc = FindColumn("ID", ppstmt);

								if (xc > -1)
								{
									sint vc = sqlite3_column_int(ppstmt, xc);
									sint rc = SetPCliMem(BOT_C_ID, &vc);
								}

								xc = FindColumn("FAILED_LOGINS", ppstmt);

								if (xc > -1)
								{
									sint vc = sqlite3_column_int(ppstmt, xc) + 1;
									sint rc = SetPCliMem(BOT_C_F_LOGINS, &vc);
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
						sint op = Output(true, GetError().c_str(), 1, 2, -1);
						break;
					}
					}
				}

				xc = sqlite3_finalize(ppstmt);

				if (xc)
				{
					sint op = Output(true, GetError().c_str(), 1, 2, -1);
				}
			}
			else
			{
				sint op = Output(true, GetError().c_str(), 1, 2, -1);
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
	t.spec = 0;
	t.act = 0;
	sint xc = t.AddCond(0, "LOGIN_NAME", msy.sql_comp_keywords[5].c_str(), EStr(Client_->login_name.c_str()).c_str());
	xc = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), stool.ITOA(Client_->lid).c_str());

	if (Client_->loggedin)
	{
		if (Client_->changename)
		{
			std::string str;
			str.append(UCASE(Client_->login_name.c_str()));
			xc = t.AddCol("LOGIN_NAME", EStr(str.c_str()).c_str());
		}

		if (Client_->updatepriv)
		{
			xc = t.AddCol("PRIV", stool.ITOA(Client_->priv).c_str());
		}

		if (Client_->updatelogin)
		{
			xc = t.AddCol("LAST_LOGIN", EStr(Client_->logindate.c_str()).c_str());
			xc = t.AddCol("TOTAL_LOGINS", stool.ITOA(Client_->totallogins).c_str());
			xc = t.AddCol("FAILED_LOGINS", stool.ITOA(0).c_str());
		}
	}
	else
	{
		if (Client_->updatelogin)
		{
			xc = t.AddCol("LAST_FAILED_LOGIN", EStr(Client_->last_failed_login.c_str()).c_str());
			xc = t.AddCol("FAILED_LOGINS", stool.ITOA(Client_->failed_logins + 1).c_str());
		}
	}
	xc = vtool.AVTV(&tvec, &t, false, false);
	xc = Commit(&tvec);
	return 0;
}
sint machine::GetLastAccess(BOT_DB_M *dbs_, sint *lmo_, sint *lmo_ns_, sint *lma_, sint *lma_ns_)
{
	if (debug_lvl >= 750 && debug_m)
	{
		carr_512 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetLastAccess(BOT_DB_M* dbs_(%i), sint *lmo_(%i), sint *lmo_ns_(%i), sint *lma_(%i), sint *lma_ns_(%i))(", (sint)dbs_, (sint)lmo_, (sint)lmo_ns_, (sint)lma_, (sint)lma_ns_);
		op = Output(outp.carr, 2);
	}

	if (!dbs_ || !lmo_ || !lmo_ns_ || !lma_ || !lma_ns_)
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

							if (lma_)
							{
								xc = FindColumn("LAST_MAINTAINED", ppstmt);

								if (xc > -1)
								{
									sint rc = sqlite3_column_int(ppstmt, xc);

									if (rc > *lma_)
									{
										*lma_ = rc;
									}
								}
							}
							if (lmo_)
							{
								xc = FindColumn("LAST_MODIFIED", ppstmt);

								if (xc > -1)
								{
									sint rc = sqlite3_column_int(ppstmt, xc);

									if (rc > *lmo_)
									{
										*lmo_ = rc;
									}
								}
							}
							if (lma_ns_)
							{
								xc = FindColumn("LAST_MAINTAINED_NS", ppstmt);

								if (xc > -1)
								{
									sint rc = sqlite3_column_int(ppstmt, xc);

									if (rc > *lma_ns_)
									{
										*lma_ns_ = rc;
									}
								}
							}
							if (lmo_ns_)
							{
								xc = FindColumn("LAST_MODIFIED_NS", ppstmt);

								if (xc > -1)
								{
									sint rc = sqlite3_column_int(ppstmt, xc);

									if (rc > *lmo_ns_)
									{
										*lmo_ns_ = rc;
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
							sint xp = Output(true, GetError().c_str(), 1, 2, -1);
							done = true;
							break;
						}
						}
					}

					xc = sqlite3_finalize(ppstmt);

					if (xc)
					{
						sint xp = Output(true, GetError().c_str(), 1, 2, -1);
					}
				}
				else
				{
					sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
									t.spec = 0;
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
									t.spec = 0;
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
							sint xp = Output(true, GetError().c_str(), 1, 2, -1);
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
						sint xp = Output(true, GetError().c_str(), 1, 2, -1);
					}
				}
				else
				{
					xc = Output(true, GetError().c_str(), 1, 2, -1);
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
		return (sint)BOT_THR_FIN;
	}
	mk_thr = true;
	UpdMTXPrio();
	TINFO_M tts;
	sint xc = GetVecEle((void*)&tts, MTX_TTS, lid);

	if (xc < 0)
	{
		mk_thr = false;
		UpdMTXPrio();
		return (sint)BOT_THR_FIN;
	}

	*thr_opt = tts.opt;
	xc = GetThreadQuit();

	if (xc)
	{
		mk_thr = false;
		UpdMTXPrio();
		return (sint)BOT_THR_RCL;
	}

	sllint lc = TestThreadTRat((sint)BOT_ITER_TO);

	if (thr_exe_mod < tts.min_ratv)
	{
		mk_thr = false;
		UpdMTXPrio();
		return (sint)BOT_THR_RJC;
	}

	xc = (sint)BOT_THR_RUN;
	sint rc = SetVecEleMem((void*)&xc, MTX_TTS, lid, BOT_TTS_FIN, false);

	if (rc < 0)
	{
		mk_thr = false;
		UpdMTXPrio();
		return (sint)BOT_THR_FIN;
	}
	mk_thr = false;
	UpdMTXPrio();
	rc = GetDBG(&debug_lvl, &debug_m);
	return (sint)BOT_THR_RUN;
}
sint machine::ThreadRest(sllint dur, sint qt_lvl)
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
		sllint rst = Rest(dur);
		std::chrono::steady_clock::time_point nt = std::chrono::steady_clock::now();
		sint rc = SetVecEleMem((void*)&nt, MTX_TTS, lid, BOT_TTS_TIMEP, false);
		rc = GetDBG(&debug_lvl, &debug_m);
		return 0;
	}
	return -1;
}
sint machine::ThreadEnd(std::vector<ullint>* rvals_)
{
	mk_thr = true;
	UpdMTXPrio();

	if (rvals_)
	{
		sint rc = SetVecEleMem((void*)rvals_, MTX_TTS, lid, BOT_TTS_VALS, false);
	}

	sint fin = (sint)BOT_THR_FIN;
	sint rc = SetVecEleMem((void*)&fin, MTX_TTS, lid, BOT_TTS_FIN, false);
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
	if (debug_lvl >= 100 && debug_m)
	{
		sint xc = Output("::StopAllThreads()", 2);
	}

	sint log_at = -1;
	sint db_at = -1;
	sint ret = -1;
	bool done = false;

	while (!done)
	{
		sllint rst = Rest((sllint)BOT_QUITREST);
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
						if (ret == (sint)BOT_THR_RUN)
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
		sllint rst = Rest((sllint)BOT_QUITREST);
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
						if (ret == (sint)BOT_THR_RUN)
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
		sllint rst = Rest((sllint)BOT_QUITREST);
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
					if (ret == (sint)BOT_THR_RUN)
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

		return xc;
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
			sllint rst = Rest((sllint)BOT_MILLI_REST);
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
					sllint rst = Rest((sllint)BOT_MILLI_REST);
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
		tts.fin = (sint)BOT_THR_PCL;
		xc = PushToVec(&tts, MTX_TTS, true, true, false);

		if (xc > -1)
		{
			sint na = pthread_attr_init(&tts.attr);
			pthread_attr_setdetachstate(&tts.attr, tts.opt);
			
			for (size_t ct = 0; ct < 10000; ct++)
			{
				xc = DecrThreads();

				if (xc < 0)
				{
					sllint rst = Rest((sllint)BOT_MILLI_REST);
				}
				else
				{
					ct = 10000;
				}
			}

			if (xc < 0)
			{
				sint xp = Output(true, "error: decrementing open thread count.", 1, 2, -1);
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

			while (tts.fin < (sint)BOT_THR_RJC)
			{
				sllint rst = Rest((sllint)BOT_MILLI_REST);
				na = GetVecEleMem((void*)&tts.fin, MTX_TTS, tts.lid, BOT_TTS_FIN);

				if (na < 0)
				{
					tts.fin = BOT_THR_DED;
				}
			}

			tts_->Renew(&tts);

			if (tts.fin > (sint)BOT_THR_RJC)
			{
				done = true;
			}
			else
			{
				while (FinishThread(tts_, ret_))
				{
					sllint rst = Rest((sllint)BOT_MILLI_REST);
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
		if (tts_->fin == (sint)BOT_THR_DED)
		{
			carr_512 outp;
			sint lx = bot_sprintf(outp.carr, outp.siz, "thread:%i (%s) - removed from list before create completed", tts_->lid, tts_->thread_name.c_str());
			lx = Output(true, outp.carr, 1, 2, -1);

			if (tts_->lid > -1)
			{
				lx = ClearVecEle(MTX_TTS, tts_->lid, false);
			}
			lx = IncrThreads();
			return 0;
		}
		else
		{
			xc = -1;

			switch (tts_->opt)
			{
			case (sint)PTHREAD_CREATE_JOINABLE:
			{
				if (debug_lvl >= 200 && debug_m)
				{
					sint lx = Output("attempting to join thread", 2);
				}

				if (tts_->fin == (sint)BOT_THR_RJC || tts_->fin > (sint)BOT_THR_RUN)
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
								lx = Output(true, outp.carr, 1, 2, -1);
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
									lx = Output(true, outp.carr, 1, 2, -1);
								}
							}

							lx = ClearVecEle(MTX_TTS, tts_->lid, false);
							lx = IncrThreads();

							if (lx < 0)
							{
								lx = Output(true, "error: incrementing open thread count.", 1, 2, -1);
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
			case (sint)PTHREAD_CREATE_DETACHED:
			{
				if (tts_->fin == (sint)BOT_THR_RJC || tts_->fin > (sint)BOT_THR_RUN)
				{
					sint rc = ClearVecEle(MTX_TTS, tts_->lid, false);
					rc = IncrThreads();
				}
				return 0;
				break;
			}
			default:
			{
				if (debug_lvl >= 1 && debug_m)
				{
					carr_128 outp;
					sint op = bot_sprintf(outp.carr, outp.siz, "Error Invalid join/detach opt(%i) for thread(%i)", tts_->opt, tts_->lid);
					op = Output(outp.carr, 2);
				}
				if (tts_->lid > -1)
				{
					sint lx = ClearVecEle(MTX_TTS, tts_->lid, false);
				}
				sint rc = IncrThreads();
				return 0;
				break;
			}
			}
		}
	}
	else
	{
		xc = (sint)tts_->thread;
	}
	return xc;
}

sint machine::MT()
{
	if (debug_lvl >= 200 && debug_m)
	{
		carr_8 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::MT()");
		op = Output(outp.carr, 2);
	}

	uint bot_started = 0;
	bool done = false;

	while (!done)
	{
		sint xc = TM(&bot_started);

		if (GetThreadQuit())
		{
			xc = StopAllThreads();
			done = true;
		}
		else
		{
			/*before we rest*/
		}
		sllint rst = Rest((sllint)BOT_THRREST);
	}
	return 0;
}

sint machine::TM(uint* is_s)
{
	if (debug_lvl >= 200 && debug_m)
	{
		carr_48 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::TM(uint* is_s(%i))", (sint)is_s);
		op = Output(outp.carr, 2);
	}

	if (!is_s)
	{
		return -1;
	}

	if (!GetThreadQuit())
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

				if (ntts.fin > (sint)BOT_THR_RUN && ntts.opt == (sint)PTHREAD_CREATE_DETACHED)
				{
					if (debug_lvl >= 200 && debug_m)
					{
						carr_64 outp;
						sint op = bot_sprintf(outp.carr, outp.siz, "clearing ele(%i)", p);
						op = Output(outp.carr, 2);
					}
					ClearVecEle(MTX_TTS, ntts.lid, false);
				}
				else if (ntts.fin == (sint)BOT_THR_BEG && strlen(ntts.thread_name.c_str()))
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
		}

		if (!has_self && !lid)
		{
			if (debug_lvl >= 200 && debug_m)
			{
				sint xc = Output("adding machine to thread list", 2);
			}

			TINFO tts((sint)PTHREAD_CREATE_DETACHED, ptn.c_str(), NULL);
			tts.fin = (sint)BOT_THR_RUN;
			tts.t_I = bot_st;
			sint xc = PushToVec(&tts, MTX_TTS, true, true, false);
			std::vector<TINFO_M> create_vec;

			for (sint p = 0; p < 100; p++)
			{
				TINFO_M tts((sint)PTHREAD_CREATE_JOINABLE, "TestThread", TestThread, lid);
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
			TINFO_M tts((sint)PTHREAD_CREATE_DETACHED, "LogMaintenance", LogMaintenance, lid, 1.0f);
			sint xc = InitThread(&tts);
		}
		if (!has_dm)
		{
			if (debug_lvl >= 200 && debug_m)
			{
				sint xc = Output("adding DBMaintenance to thread list", 2);
			}
			TINFO_M tts((sint)PTHREAD_CREATE_DETACHED, "DBMaintenance", DBMaintenance, lid, 1.0f);
			sint xc = InitThread(&tts);
		}
		if (!has_cons)
		{
			if (!*is_s)
			{
				if (debug_lvl >= 200 && debug_m)
				{
					sint xc = Output("adding ConsoleThread to thread list", 2);
				}
				TINFO_M tts((sint)PTHREAD_CREATE_DETACHED, "ConsoleThread", ConsoleThread, lid, 1.0f);
				sint xc = InitThread(&tts);
				*is_s = 1;
			}
			else
			{
				SetThreadQuit(1);
			}
		}
	}
	return 0;
}
sllint machine::TestThreadIter(sint to_)
{
	if (debug_lvl >= 200 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::TestThreadIter(sint to_(%i))", (sint)to_);
		op = Output(outp.carr, 2);
	}
	std::chrono::steady_clock::time_point t_I = std::chrono::steady_clock::now();
	float val = 3611.0f;
	//slint xval[2]{ 0 };

	for (sint xc = 0; xc < to_; xc++)
	{
		val /= 1.333f;
		//BOT_FTIA ftia(val);
		//BOT_IATF(ftia.a);
	}

	std::chrono::steady_clock::time_point t_II = std::chrono::steady_clock::now();
	std::chrono::duration<sllint, std::nano> span = std::chrono::duration_cast<std::chrono::nanoseconds>(t_II - t_I);
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
	if (debug_lvl >= 200 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::TestThreadTRat(sint to_(%i))", (sint)to_);
		op = Output(outp.carr, 2);
	}
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

sint machine::GetPCli(BOT_CLIENT* val)
{
	if (debug_lvl >= 90 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetPCli(BOT_CLIENT* val(%i))", (sint)val);
		op = Output(outp.carr, 2);
	}
	if (!val)
	{
		return -1;
	}

	sint lx = -1;
	sint xc = LockGMutex(MTX_PCL, &lx);

	if (xc > -1)
	{
		val->Renew(&pcli);

		if (!lx)
		{
			lx = UnlockGMutex(MTX_PCL);
		}
	}
	return xc;
}

sint machine::SetPCli(BOT_CLIENT* val)
{
	if (!val)
	{
		return -1;
	}

	sint lx = -1;
	sint xc = LockGMutex(MTX_PCL, &lx);

	if (xc > -1)
	{
		pcli.Renew(val);

		if (!lx)
		{
			lx = UnlockGMutex(MTX_PCL);
		}
	}
	return xc;
}

sint machine::GetPCliMem(sint mem, void* val)
{
	if (mem < 0 || !val)
	{
		return -1;
	}

	sint lx = -1;
	sint xc = LockGMutex(MTX_PCL, &lx);

	if (xc > -1)
	{
		switch (mem)
		{
		case (sint)BOT_C_NAMESET:
		{
			bool* xv = reinterpret_cast<bool*>(val);
			*xv = pcli.nameset;
			break;
		}
		case (sint)BOT_C_LOGGED_IN:
		{
			bool* xv = reinterpret_cast<bool*>(val);
			*xv = pcli.loggedin;
			break;
		}
		case (sint)BOT_C_CHANGE_N:
		{
			bool* xv = reinterpret_cast<bool*>(val);
			*xv = pcli.changename;
			break;
		}
		case (sint)BOT_C_U_LOGIN:
		{
			bool* xv = reinterpret_cast<bool*>(val);
			*xv = pcli.updatelogin;
			break;
		}
		case (sint)BOT_C_T_LOGINS:
		{
			sint* xv = reinterpret_cast<sint*>(val);
			*xv = pcli.totallogins;
			break;
		}
		case (sint)BOT_C_F_LOGINS:
		{
			sint* xv = reinterpret_cast<sint*>(val);
			*xv = pcli.failed_logins;
			break;
		}
		case (sint)BOT_C_PRIV:
		{
			sint* xv = reinterpret_cast<sint*>(val);
			*xv = pcli.priv;
			break;
		}
		case (sint)BOT_C_ID:
		{
			sint* xv = reinterpret_cast<sint*>(val);
			*xv = pcli.lid;
			break;
		}
		case (sint)BOT_C_LOGIN_NAME:
		{
			std::string* xv = reinterpret_cast<std::string*>(val);
			xv->clear();
			xv->append(pcli.login_name.c_str());
			break;
		}
		case (sint)BOT_C_NAME:
		{
			std::string* xv = reinterpret_cast<std::string*>(val);
			xv->clear();
			xv->append(pcli.name.c_str());
			break;
		}
		case (sint)BOT_C_L_LOGIN:
		{
			std::string* xv = reinterpret_cast<std::string*>(val);
			xv->clear();
			xv->append(pcli.lastlogin.c_str());
			break;
		}
		case (sint)BOT_C_L_DATE:
		{
			std::string* xv = reinterpret_cast<std::string*>(val);
			xv->clear();
			xv->append(pcli.logindate.c_str());
			break;
		}
		case (sint)BOT_C_LFL:
		{
			std::string* xv = reinterpret_cast<std::string*>(val);
			xv->clear();
			xv->append(pcli.last_failed_login.c_str());
			break;
		}
		case (sint)BOT_C_LAST_E:
		{
			std::string* xv = reinterpret_cast<std::string*>(val);
			xv->clear();
			xv->append(pcli.lastexchange.c_str());
			break;
		}
		case (sint)BOT_C_CBY:
		{
			sint* xv = reinterpret_cast<sint*>(val);
			*xv = pcli.c_by;
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		if (!lx)
		{
			lx = UnlockGMutex(MTX_PCL);
		}
	}
	return 0;
}

sint machine::SetPCliMem(sint mem, void* val)
{
	if (debug_lvl >= 90 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::SetPCliMem(sint mem(%i), void* val(%i))", mem, (sint)val);
		op = Output(outp.carr, 2);
	}
	if (mem < 0 || !val)
	{
		return -1;
	}

	sint lx = -1;
	sint xc = LockGMutex(MTX_PCL, &lx);

	if (xc > -1)
	{
		switch (mem)
		{
		case (sint)BOT_C_NAMESET:
		{
			bool* xp = reinterpret_cast<bool*>(val);
			pcli.nameset = *xp;
			break;
		}
		case (sint)BOT_C_LOGGED_IN:
		{
			bool* xp = reinterpret_cast<bool*>(val);
			pcli.loggedin = *xp;
			break;
		}
		case (sint)BOT_C_CHANGE_N:
		{
			bool* xp = reinterpret_cast<bool*>(val);
			pcli.changename = *xp;
			break;
		}
		case (sint)BOT_C_U_LOGIN:
		{
			bool* xp = reinterpret_cast<bool*>(val);
			pcli.updatelogin = *xp;
			break;
		}
		case (sint)BOT_C_T_LOGINS:
		{
			sint* xp = reinterpret_cast<sint*>(val);
			pcli.totallogins = *xp;
			break;
		}
		case (sint)BOT_C_F_LOGINS:
		{
			sint* xp = reinterpret_cast<sint*>(val);
			pcli.failed_logins = *xp;
			break;
		}
		case (sint)BOT_C_PRIV:
		{
			sint* xp = reinterpret_cast<sint*>(val);
			pcli.priv = *xp;
			break;
		}
		case (sint)BOT_C_ID:
		{
			sint* xp = reinterpret_cast<sint*>(val);
			pcli.lid = *xp;
			break;
		}
		case (sint)BOT_C_LOGIN_NAME:
		{
			c_char* xp = reinterpret_cast<c_char*>(val);
			pcli.login_name.clear();
			size_t len = strlen(xp);

			if (len && len < 128)
			{
				pcli.login_name.append(xp);
			}
			break;
		}
		case (sint)BOT_C_NAME:
		{
			c_char* xp = reinterpret_cast<c_char*>(val);
			pcli.name.clear();
			size_t len = strlen(xp);

			if (len && len < 128)
			{
				pcli.name.append(xp);
				pcli.nameset = true;
			}
			break;
		}
		case (sint)BOT_C_L_LOGIN:
		{
			c_char* xp = reinterpret_cast<c_char*>(val);
			pcli.lastlogin.clear();
			size_t len = strlen(xp);

			if (len && len < 128)
			{
				pcli.lastlogin.append(xp);
			}
			break;
		}
		case (sint)BOT_C_L_DATE:
		{
			c_char* xp = reinterpret_cast<c_char*>(val);
			pcli.logindate.clear();
			size_t len = strlen(xp);

			if (len && len < 128)
			{
				pcli.logindate.append(xp);
			}
			break;
		}
		case (sint)BOT_C_LFL:
		{
			c_char* xp = reinterpret_cast<c_char*>(val);
			pcli.last_failed_login.clear();
			size_t len = strlen(xp);

			if (len && len < 128)
			{
				pcli.last_failed_login.append(xp);
			}
			break;
		}
		case (sint)BOT_C_LAST_E:
		{
			c_char* xp = reinterpret_cast<c_char*>(val);
			pcli.lastexchange.clear();
			size_t len = strlen(xp);

			if (len && len < 128)
			{
				pcli.lastexchange.append(xp);
			}
			break;
		}
		case (sint)BOT_C_CBY:
		{
			sint* xp = reinterpret_cast<sint*>(val);
			pcli.c_by = *xp;
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		if (!lx)
		{
			lx = UnlockGMutex(MTX_PCL);
		}
	}
	return 0;
}

sint machine::SetClientLoggedIn(bool x)
{
	if (debug_lvl >= 90 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::SetClientLoggedIn(bool x(%u))", (uint)x);
		op = Output(outp.carr, 2);
	}
	sint lx = -1;
	sint xc = LockGMutex(MTX_PCL, &lx);

	if (xc > -1)
	{
		pcli.loggedin = x;

		if (!lx)
		{
			lx = UnlockGMutex(MTX_PCL);
		}
	}
	return 0;
}

bool machine::GetClientLoggedIn()
{
	if (debug_lvl >= 90 && debug_m)
	{
		sint op = Output("::SetClientLoggedIn()", 2);
	}
	bool x = false;
	sint lx = -1;
	sint xc = LockGMutex(MTX_PCL, &lx);

	if (xc > -1)
	{
		x = pcli.loggedin;

		if (!lx)
		{
			lx = UnlockGMutex(MTX_PCL);
		}
	}
	return x;
}

void* machine::ScanFileThread(void* vp_)
{
	sint xc = (sint)vp_;
	carr_64 ncar;
	sint rc = bot_sprintf(ncar.carr, ncar.siz, "ScanFileThread", xc);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, ncar.carr, true, false);
	rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
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
			nfile.fst.RenewLocs((size_t)vals[3], (size_t)0, (size_t)vals[2]);
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

	rc = LITEBot.ThreadEnd(&vals);
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)ret);
	return NULL;
}

void* machine::RendFileThread(void* vp_)
{
	sint xc = (sint)vp_;
	carr_64 ncar;
	sint rc = bot_sprintf(ncar.carr, ncar.siz, "RendFileThread", xc);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, ncar.carr, true, false);
	rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
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
			nfile.fst.e_loc = (size_t)vals[3];
			nfile.fst.ia_loc = (size_t)vals[2];
			vals.clear();

			if (rc > -1)
			{
				ret = LITEBot.BOTRendFileSyms(&nfile);
				vals.push_back((ullint)ret);
			}
		}
	}

	rc = LITEBot.ThreadEnd(&vals);
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)ret);
	return NULL;
}

void* machine::LogMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(10, 1, xc, "LogMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
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
							BOT_FILE_M xfile(logm.logtitle.c_str(), ".txt", pth.c_str(), BOT_FILE_APND, BOT_F_CON, -1, LITEBot.lid);
							sint ox = -1;
							rc = LITEBot.BOTOpenFile(&xfile, &ox, true);

							if (rc > -1)
							{
								sint op = LITEBot.BOTFileOUT(&xfile, xfile.fst.e_loc, false, BOT_RTV_VSTR, &bot_log_vec.d_vec[siz].log_q, BOT_RTV_MAX);

								if (!op)
								{
									bot_log_vec.d_vec[logm.lid].log_q.clear();
									rc = LITEBot.SetVecEleMem((void*)&bot_log_vec.d_vec[logm.lid].log_q, MTX_LOG, logm.lid, BOT_LOG_Q, false);
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

		rc = LITEBot.ThreadRest((sllint)BOT_LOGREST, (sint)BOT_THRQ_LOG);
		
		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::ConsoleThread(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ConsoleThread", true, false);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
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
		rc = LITEBot.BOTConsole(": ");
		rc = LITEBot.ThreadRest((sllint)BOT_CNSREST, (sint)BOT_THRQ_CONS);

		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::GIPS(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "GIPS", true, false);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
	}

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::GIPS(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	carr_64 pcar;
	sint ret = bot_sprintf(pcar.carr, pcar.siz, "%i", (sint)BOTLPORT_A);
	carr_64 adcar;
	ret = gethostname(adcar.carr, adcar.siz);
	hostent *hoe = gethostbyname(adcar.carr);

	if (hoe != NULL)
	{
#ifdef _WIN32
		struct in_addr addr;
#else
		struct sockaddr_storage addr;
#endif
		carr_1024 outp;

		if (hoe->h_addrtype == AF_INET)
		{
			ret = bot_sprintf(outp.carr, outp.siz, "Host IPv: IPv4 | Host Name:%s", hoe->h_name);
		}
		else if (hoe->h_addrtype == AF_INET6)
		{
			ret = bot_sprintf(outp.carr, outp.siz, "Host IPv: IPv6 | Host Name:%s", hoe->h_name);
		}
		else if (hoe->h_addrtype == AF_NETBIOS)
		{
			ret = bot_sprintf(outp.carr, outp.siz, "Host IPv: NETBIOS | Host Name:%s", hoe->h_name);
		}
		else
		{
			ret = bot_sprintf(outp.carr, outp.siz, "Host IPv: IPvU | Host Name:%s", hoe->h_name);
		}

		ret = LITEBot.Output(true, outp.carr, 2, 0);
		bot_strclr(outp.carr);

#ifdef _WIN32
		for (uint x = 0; hoe->h_addr_list[x] != NULL; x++)
		{
			addr.s_addr = *(uint*)hoe->h_addr_list[x];
			ret = bot_sprintf(outp.carr, outp.siz, "Host IP: %s", inet_ntoa(addr));
			ret = LITEBot.Output(true, outp.carr, 2, 0);
		}
#else
		for (uint x = 0; hoe->h_addr_list[x] != NULL; x++)
		{
			if (hoe->h_addrtype == AF_INET)
			{
				addr.sin_addr = *(struct sockaddr_in*)hoe->h_addr_list[x];
				ret = bot_sprintf(outp.carr, outp.siz, "Host IP: %s", inet_ntoa(addr.sin_addr));
			}
			else if (hoe->h_addrtype = AF_INET6)
			{
				addr.sin_addr = *(struct sockaddr_in6*)hoe->h_addr_list[x];
				ret = bot_sprintf(outp.carr, outp.siz, "Host IP: %s", inet_ntoa(addr.sin_addr));
			}
			else if (hoe->h_addrtype = AF_NETBIOS)
			{

			}
			else
			{

			}
			ret = LITEBot.Output(outp.carr, 0);
		}
#endif
	}

	rc = LITEBot.ThreadEnd();

	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::ServThread(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ServThread", true, false);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
	}

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ServThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	std::vector<ullint> vals;
	sint ret = rc = LITEBot.GetVecEleMem((void*)&vals, MTX_TTS, LITEBot.lid, BOT_TTS_VALS);
	carr_512 nurl;
	carr_64 nsvc;
	ret = -1;
	rc = 0;

	for (; ret < (sint)vals.size() && ret < 576; ret++)
	{
		if ((!vals[ret] && rc < 0) || ret >= 511)
		{
			_char ncar = '\0';
			memcpy((void*)&nurl.carr[ret], (void*)&ncar, sizeof(_char));
			rc++;
		}
		else if (vals[ret] && ret < 511 && rc < 0)
		{
			_char ncar = (_char)vals[ret];
			memcpy((void*)&nurl.carr[ret], (void*)&ncar, sizeof(_char));
		}
		else if (vals[ret] && rc < 63)
		{
			_char ncar = (_char)vals[ret];
			memcpy((void*)&nsvc.carr[rc], (void*)&ncar, sizeof(_char));
			rc++;
		}
		else if (rc >= 63)
		{
			_char ncar = '\0';
			memcpy((void*)&nsvc.carr[ret], (void*)&ncar, sizeof(_char));
			rc++;
		}
		else
		{
			_char ncar = '\0';
			memcpy((void*)&nsvc.carr[rc], (void*)&ncar, sizeof(_char));
			rc++;
		}
	}

	sllint xret = -1;
	bot_plug servp(nurl.carr, nsvc.carr);
	carr_256 outp;
	ret = servp.Open(AI_PASSIVE, AF_UNSPEC, SOCK_STREAM, true, true);

	if (ret)
	{
		rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
		rc = LITEBot.Output(true, outp.carr, 1, 0);
	}

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		while (!ret)
		{
			bot_strclr(outp.carr);
			rc = bot_sprintf(outp.carr, outp.siz, "Host IP(2):(%s) %s", servp.ifam.carr, servp.ipstr.carr);
			rc = LITEBot.Output(true, outp.carr, 2, 0);
			ret = servp.Next();
		}
	}

	xret = bot_prts.Add(servp.prt.fam, servp.prt.portn, servp.prt.proto, servp.prt.xcl);
	ret = servp.Sock(false);

	if (ret)
	{
		servp.Close();
		xret = bot_prts.Rem(servp.prt.portn, servp.prt.proto);
		bot_strclr(outp.carr);
		rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
		rc = LITEBot.Output(true, outp.carr, 1, 0);
	}

	ret = servp.Listen(10);

	if (ret)
	{
		servp.Close();
		xret = bot_prts.Rem(servp.prt.portn, servp.prt.proto);
		bot_strclr(outp.carr);
		rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
		rc = LITEBot.Output(true, outp.carr, 1, 0);
	}
	else
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			bot_strclr(outp.carr);
			rc = bot_sprintf(outp.carr, outp.siz, "Listening on Port:%s", servp.servc.carr);
			rc = LITEBot.Output(true, outp.carr, 2, 0);
		}
	}

	bool done = false;

	while (!done)
	{
		rc = LITEBot.ThreadRest((sllint)BOT_SERVREST, (sint)BOT_THRQ_CONS);

		if (rc)
		{
			done = true;
		}
	}

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		bot_strclr(outp.carr);
		rc = bot_sprintf(outp.carr, outp.siz, "Closing - Port(%s) Socket(%i)", servp.servc.carr, (slint)servp.sck);
		rc = LITEBot.Output(true, outp.carr, 2, 0);
	}

	servp.Close();
	xret = bot_prts.Rem(servp.prt.portn, servp.prt.proto);
	rc = LITEBot.ThreadEnd();

	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::CliThread(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "CliThread", true, false);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
	}

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::CliThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	bool done = false;

	bot_plug clip(0, false);

	while (!done)
	{
		rc = LITEBot.ThreadRest((sllint)BOT_CLIREST, (sint)BOT_THRQ_CONS);

		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::TestThread(void* vp_)
{
	sint xc = (sint)vp_;
	carr_64 ncar;
	sint rc = bot_sprintf(ncar.carr, ncar.siz, "TestThread%i", xc);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, ncar.carr, true, false);
	rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
	}

	if (LITEBot.debug_lvl >= 200 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::TestThread(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	sllint lc = LITEBot.TestThreadTRat((sint)BOT_ITER_TO);
	rc = LITEBot.ThreadEnd();
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)lc);
	return NULL;
}

// Database Maintenance

void* machine::DBMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "DBMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
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
			TINFO_M ntts((sint)PTHREAD_CREATE_JOINABLE, "LITEBotMaintenance", LITEBot.LITEBotMaintenance, LITEBot.lid);
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
	
		rc = LITEBot.ThreadRest((sllint)BOT_DBREST, (sint)BOT_THRQ_DBM);

		if (rc)
		{
			done = true;
		}
	}

	rc = LITEBot.ThreadEnd();
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::LITEBotMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "LITEBotMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
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

		sint lmo_ = 0;
		sint lma_ = 0;
		sint lmo_ns = 0;
		sint lma_ns = 0;
		rc = LITEBot.GetLastAccess(&dbs, &lmo_, &lmo_ns, &lma_, &lma_ns);
		rc = LITEBot.LastAccessMaintenance(&dbs);
	}
	else
	{
		rc = LITEBot.VerifyDatabases();
	}

	rc = LITEBot.ThreadEnd();
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}

void* machine::CodeMaintenance(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "CodeMaintenance", true, true);
	sint rc = LITEBot.StartThread(&xc);

	if (rc != (sint)BOT_THR_RUN)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		if (xc)
		{
			pthread_detach(pthread_self());
		}
		pthread_exit((void*)rc);
	}

	BOT_DB_M dbs("code", 2);
	rc = LITEBot.GetInVec((void*)&dbs, MTX_DBL, false, false);

	if (LITEBot.debug_lvl >= 100 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::CodeMaintenance(void* vp_(%i) for database:%s)", LITEBot.lid, dbs.name.c_str());
		rc = LITEBot.Output(outc.carr, 2);
	}

	sint lmo_ = 0;
	sint lma_ = 0;
	sint lmo_ns = 0;
	sint lma_ns = 0;
	rc = LITEBot.GetLastAccess(&dbs, &lmo_, &lmo_ns, &lma_, &lma_ns);
	rc = LITEBot.LastAccessMaintenance(&dbs);

	if ((lma_ == lmo_ && lma_ns > lmo_ns) || lmo_ < lma_)
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
	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}