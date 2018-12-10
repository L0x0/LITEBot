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
std::vector<bot_port> bot_prts;

// MTX_PRC
bot_procs prcs;

// MTX_CIPS
std::vector<carr_256> bot_cips;

// MTX_BIPS
std::vector<carr_64> bot_bips;

// MTX_SES
bot_session bot_ses;

// MTX_SVPKO
bot_vblko bot_pkto[BOT_SCKT_MAX];

// MTX_SVPKI
bot_vblki bot_pkti[BOT_SCKT_MAX];

// MTX_SVPKO
bot_svblko bot_spkto[BOT_SCKT_MAX];

// MTX_SVPKI
bot_svblki bot_spkti[BOT_SCKT_MAX];

// MTX_NET_FOUT
std::vector<bot_file_hdr> bot_net_fout;

// MTX_NET_FINC
std::vector<bot_file_hdr> bot_net_finc;

// MTX_VARS
bot_vars xmv;

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

		while (x < 13)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
			{
				x = 13;
			}
			x++;
		}

		if (x == 13)
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
		for (x = 0; x < 13; x++)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
			{
				return (sint)slen;
			}
		}
	}
	return -1;
}
bool bot_sisf(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}
	_char f = 'f';

	if (!memcmp((void*)&val[slen], (void*)&f, sizeof(_char)))
	{
		slen--;
	}

	sint x = 0;
	c_char* nstr = BOT_N_STR;

	for (slen--; slen > -1; slen--)
	{
		x = 0;

		while (x < 13)
		{
			if (!memcmp((void*)&val[slen], (void*)&nstr[x], sizeof(_char)))
			{
				x = 13;
			}
			x++;
		}

		if (x == 13)
		{
			return false;
		}
	}
	return true;
}
bool bot_sisi(c_char* val, sint slen)
{
	if (!val || !slen || slen >= BOT_STRLEN_MAX)
	{
		return false;
	}
	
	sint x = 0;
	c_char* nstr = BOT_I_STR;

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
			if (!slen)
			{
				_char f = '-';

				if (!memcmp((void*)&val[0], (void*)&f, sizeof(_char)))
				{
					return true;
				}
			}
			return false;
		}
	}
	return true;
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

void bot_strclr(_char inchr[], size_t nl)
{
	if (!inchr)
	{
		return;
	}
	if (!nl)
	{
		nl = bot_strlen(inchr);
	}

	if (nl)
	{
		_char n = '\0';

		for (; nl; nl--)
		{
			memcpy((void*)&inchr[nl-1], (void*)&n, sizeof(_char));
		}
	}
}

void bot_ustrclr(u_char inchr[], size_t nl)
{
	if (!inchr)
	{
		return;
	}

	if (!nl)
	{
		nl = bot_ustrlen(inchr);
	}
	if (nl)
	{
		u_char n = (u_char)'\0';

		for (; nl; nl--)
		{
			memcpy((void*)&inchr[nl-1], (void*)&n, sizeof(u_char));
		}
	}
}

void bot_cstrclr(c_char inchr[], size_t nl)
{
	if (!inchr)
	{
		return;
	}

	_char term = '\0';

	if (!nl)
	{
		nl = strlen(inchr);
	}

	for (size_t y = 0; y < nl; y++)
	{
		memcpy((void*)&inchr[y], (void*)&term, 1);
	}
}

void bot_custrclr(cu_char inchr[], size_t nl)
{
	if (!inchr)
	{
		return;
	}

	u_char term = '\0';

	if (!nl)
	{
		nl = bot_custrlen(inchr);
	}

	for (size_t y = 0; y < nl; y++)
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
					if (bot_sisn(&fspecs[siz][nsiz + 1], 1))
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
						size_t slen = strlen(spc.carr);

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

// Date / Time 

sint BOTDateTimeMS(_char str_[], size_t siz, bool form)
{
	if (!str_ || !siz)
	{
		return -1;
	}
#ifdef _WIN32
	SYSTEMTIME tim;
	GetSystemTime(&tim);

	if (form)
	{
		sint xc = bot_sprintf(str_, siz, "%.2u/%.2u/%.4u %.2u:%.2u:%.2u:%.3u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond, tim.wMilliseconds);
	}
	else
	{
		sint xc = bot_sprintf(str_, siz, "%.2u%.2u%.4u%.2u%.2u%.2u%.3u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond, tim.wMilliseconds);
	}
#else
	std::time_t tstamp;
	struct tm t;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	t = *gmtime(&tstamp);
	xc = bot_sprintf(str_, 128, "%.2u/%.2u/%.4u %.2u:%.2u:%.2u:%.3u", (uint)t.tm_mon, (uint)t.tm_mday, (uint)t.tm_year, (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec, (uint)ti.tv_nsec);
#endif	
	return 0;
}
sint BOTDateTime(_char str_[], size_t siz, bool form)
{
	if (!str_ || !siz)
	{
		return -1;
	}
#ifdef _WIN32
	SYSTEMTIME tim;
	GetSystemTime(&tim);

	if (form)
	{
		sint xc = bot_sprintf(str_, siz, "%.2u/%.2u/%.4u %.2u:%.2u:%.2u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond);
	}
	else
	{
		sint xc = bot_sprintf(str_, siz, "%.2u%.2u%.4u%.2u%.2u%.2u", tim.wMonth, tim.wDay, tim.wYear, tim.wHour, tim.wMinute, tim.wSecond);
	}
#else
	std::time_t tstamp;
	struct tm t;
	struct timespec ti;
	sint xc = (sint)time(&tstamp);
	xc = clock_gettime(CLOCK_REALTIME, &ti);
	t = *gmtime(&tstamp);

	if (form)
	{
		xc = bot_sprintf(str_, siz, "%.2u/%.2u/%.4u %.2u:%.2u:%.2u", (uint)t.tm_mon, (uint)t.tm_mday, (uint)t.tm_year, (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
	}
	else
	{
		xc = bot_sprintf(str_, siz, "%.2u%.2u%.4u%.2u:%.2u:%.2u", (uint)t.tm_mon, (uint)t.tm_mday, (uint)t.tm_year, (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
	}
#endif
	return 0;
}
sint BOTTime(_char str_[], size_t siz, bool forms)
{
	if (!str_ || !siz)
	{
		return -1;
	}
#ifdef _WIN32
	SYSTEMTIME tim;
	GetSystemTime(&tim);

	if (forms)
	{
		sint xc = bot_sprintf(str_, siz, "%.2u:%.2u:%.2u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond);
	}
	else
	{
		sint xc = bot_sprintf(str_, siz, "%.2u%.2u%.2u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond);
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
		xc = bot_sprintf(str_, siz, "%.2u:%.2u:%.2u", (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
	}
	else
	{
		xc = bot_sprintf(str_, siz, "%.2u%.2u%.2u", (uint)t.tm_hour, (uint)t.tm_min, (uint)t.tm_sec);
	}
#endif
	return 0;
}
sint BOTTimeMS(_char str_[], size_t siz, bool forms)
{
	if (!str_ || !siz)
	{
		return -1;
	}
#ifdef _WIN32
	SYSTEMTIME tim;
	GetSystemTime(&tim);

	if (forms)
	{
		sint xc = bot_sprintf(str_, siz, "%.2u:%.2u:%.2u:%.3u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond, (uint)tim.wMilliseconds);
	}
	else
	{
		sint xc = bot_sprintf(str_, siz, "%.2u%.2u%.2u%.3u", (uint)tim.wHour, (uint)tim.wMinute, (uint)tim.wSecond, (uint)tim.wMilliseconds);
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
		xc = bot_sprintf(str_, siz, "%.2u:%.2u:%.2u:%.3u", (uint)tms.tm_hour, (uint)tms.tm_min, (uint)tms.tm_sec, (uint)ti.tv_nsec);
	}
	else
	{
		xc = bot_sprintf(str_, siz, "%.2u%.2u%.2u%.3u", (uint)tms.tm_hour, (uint)tms.tm_min, (uint)tms.tm_sec, (uint)ti.tv_nsec);
	}
#endif
	return 0;
}
sint BOTDate(_char str_[], size_t siz, bool form)
{
	if (!str_ || !siz)
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
		xc = strftime(str_, siz, "%m/%d/%Y", &t);
	}
	else
	{
		xc = strftime(str_, siz, "%m%d%Y", &t);
	}
	return 0;
}
sllint BOTCentSec()
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
/* -------------------------------------------------------------------------------- */
sint main(sint argc, _char* argv[])
{
	carr_256 ncar;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, 0, "machine", true, true);
	sint xc = LITEBot.LITEBot(&ncar, argc, argv);

	if (xc)
	{
		std::cout << ncar.carr << std::endl;
	}
	return xc;
	pthread_exit(0);
}
/* -------------------------------------------------------------------------------- */
machine::machine(sint i_debug_lvl, sint i_debug_m, sint nlid, c_char* i_name, bool logmain, bool logmine)
{
	quit = false;
	req_lock = false;
	boto_file = false;
	mk_thr = false;
	bot_mode = -1;
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
	BOTDate(ses_date.carr, ses_date.siz, false);
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
sint machine::LITEBot(carr_256 *ncar_, sint argc, _char* argv[])
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_128 outp;
		sint rc = bot_sprintf(outp.carr, outp.siz, "LITEBot(carr_256* ncar_(%i), sint arc(%i), _char* argv[](%i))", (sint)ncar_, argc, (sint)argv);
		rc = Output(outp.carr, 2, false);
	}

	if (!ncar_ || !argc)
	{
		return -1;
	}

	sint xc = SetDBG(debug_lvl, debug_m);

	if (argc)
	{
		bot_proc mp(argv[0]);
#ifdef _WIN32
		mp.pinfo.dwProcessId = GetCurrentProcessId();
		mp.pid = (slint)mp.pinfo.dwProcessId;
		mp.pinfo.dwThreadId = GetCurrentThreadId();
#else
		mp.pid = (slint)getpid();
#endif
		xc = PushToVec((void*)&mp, MTX_PRC, true, true, false);
	}

	if (!strcmp(UCASE(argv[0]).c_str(), "MON"))
	{
		BOTSetSessionName(argv[0]);
		bot_mode = 9999;

		if (!AllocConsole())
		{
			return -1;
		}
		sint xc = BOTMonitor();
	}
	else if (!strcmp(UCASE(argv[0]).c_str(), "SERVP"))
	{
		BOTSetSessionName(argv[0]);
		bot_mode = 1;
		sint xc = Output("Server Process", 0, false);
	}
	else
	{
		BOTSetSessionName("LITEBot");
		bot_mode = 0;
		//bot_proc xp(argv[0], CREATE_NEW_CONSOLE);
		//xc = BOTFork(&xp, "mon");
	}

	std::vector<ullint> vals;

	if (argc > 1)
	{
		ullint inv = (ullint)SType(argv[1]);
		vals.push_back(inv);
	}

	if (argc > 2)
	{
		if (bot_sisi(argv[2], bot_strlen(argv[2])))
		{
			vals.push_back((ullint)_atoi64(argv[2]));
		}
		else
		{
			size_t ln = bot_strlen(argv[2]);

			for (size_t y = 0; y < ln; y++)
			{
				vals.push_back((ullint)argv[2][y]);
			}
		}
	}

	vals.push_back(UINT64_MAX);

	if (argc > 3)
	{
		ullint inv = 0;

		if (bot_sisn(argv[3], bot_strlen(argv[3])))
		{
			vals.push_back((ullint)_atoi64(argv[3]));
		}
		else
		{
			size_t ln = bot_strlen(argv[3]);

			for (size_t y = 0; y < ln; y++)
			{
				vals.push_back((ullint)argv[3][y]);
			}
		}
	}

#ifdef _WIN32
	WSADATA WSD;

	if ((xc = WSAStartup(MAKEWORD(1, 1), &WSD)) != 0)
	{
		if ((xc = WSAStartup(MAKEWORD(2, 2), &WSD)) != 0)
		{
			sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "Winsork Startup Failed (%i)", xc);
			return -1;
		}
	}
#endif

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

	xc = MT(&vals);

	if (xc)
	{
		sint oc = bot_sprintf(ncar_->carr, ncar_->siz, "Main Thread fault: %i", xc);
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

	if (xret > -1 && ele > -1)
	{
		if (!is_meta)
		{
			xret = vtool.VIV(&h_mtxs[xret].h_mems, ele);
		}
		else
		{
			xret = vtool.VIV(&h_mtxs[xret].m_mems, ele);
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
	else
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

sint machine::BOTOpenObject(sint nobj, sint nele, sint is_meta, sint* omode, sint* r_opt, sint* n_opt)
{
	if (debug_lvl >= 900 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTOpenObject(sint nobj(%i), sint nele(%i), sint is_meta(%i), sint* omode(%i), sint* r_opt(%i), sint* n_opt(%i))", nobj, nele, (uint)is_meta, (sint)omode, (sint)r_opt, (sint)n_opt);
		op = Output(outp.carr, 2);
	}
	/*if (!omode)
	{
		return -1;
	}
	if (nobj < 0)
	{
		return -1;
	}*/
	if (!omode || !r_opt)
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
		case MTX_REQ:
		{
			lok_req nreq(nele, nobj, lid, is_meta);
			return ReqMTX(&nreq);
			break;
		}
		case MTX_FO:
		{
			if (!is_meta)
			{
				ret = vtool.VIV(&f_con, nele);

				if (ret > -1)
				{
					return BOTOpenFile(nele, r_opt, false, false, true);
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
sint machine::BOTCloseObject(sint nobj, sint nele, sint is_meta, sint* r_opt, sint* n_opt)
{
	if (debug_lvl >= 900 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTCloseObject(sint nobj(%i), sint nele(%i), sint is_meta(%i), sint* r_opt(%i), sint* n_opt(%i))", nobj, nele, is_meta, (sint)r_opt, (sint)n_opt);
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

				if (!vp->name.empty() || vp->prt.lid > -1)
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&bot_c_vec.dvec, vp, check, use_empty);

					if (ret > -1)
					{
						BOT_CLIENT_M ns;
						ns.Renew(vp);
						sint iret = PushToVec(&ns, g_opt, check, use_empty, true);
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
					ret = vtool.AVTV(&bot_log_vec.dvec, vp, check, use_empty);

					if (ret > -1)
					{
						BOT_LOGDET_M ns;
						ns.Renew(vp);
						sint iret = PushToVec(&ns, g_opt, check, use_empty, true);
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
					ret = vtool.AVTV(&tts_vec.dvec, vp, check, use_empty);

					if (ret > -1)
					{
						TINFO_M ns;
						ns.Renew(vp);
						sint iret = PushToVec(&ns, g_opt, check, use_empty, true);
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
					ret = vtool.AVTV(&bot_db_vec.dvec, vp, check, use_empty);

					if (ret > -1)
					{
						BOT_DB_M ns;
						ns.Renew(vp);
						sint iret = PushToVec(&ns, g_opt, check, use_empty, true);
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
					ret = vtool.AVTV(&fileo_vec.dvec, vp, check, use_empty);

					if (ret > -1)
					{
						BOT_FILE_M ns;
						ns.Renew(vp);
						sint iret = PushToVec(&ns, g_opt, check, use_empty, true);
					}
				}
				break;
			}
			case MTX_PRC:
			{
				bot_proc* vp = reinterpret_cast<bot_proc*>(val_);

				if (!vp->anm.empty())
				{
					ret = vtool.AVTV(&prcs.dvec, vp, check, use_empty);

					if (ret > -1)
					{
						bot_proc_m ns;
						ns.Renew(vp);
						sint iret = PushToVec(&ns, g_opt, check, use_empty, true);
					}
				}
				break;
			}
			case MTX_PORTS:
			{
				bot_port* vp = reinterpret_cast<bot_port*>(val_);

				if (vp->portn > 0 && vp->portn < 65535)
				{
					ret = vtool.AVTV(&bot_prts, vp, check, use_empty);
				}
				break;
			}
			case MTX_CIPS:
			{
				carr_256* vp = reinterpret_cast<carr_256*>(val_);
				ret = vtool.AVTV(&bot_cips, vp->carr, check, use_empty);
				break;
			}
			case MTX_BIPS:
			{
				carr_64* vp = reinterpret_cast<carr_64*>(val_);
				ret = vtool.AVTV(&bot_bips, vp->carr, check, use_empty);
				break;
			}
			case MTX_NET_FOUT:
			{
				bot_file_hdr* vp = reinterpret_cast<bot_file_hdr*>(val_);
				ret = vtool.AVTV(&bot_net_fout, vp, check, use_empty);
				break;
			}
			case MTX_NET_FINC:
			{
				bot_file_hdr* vp = reinterpret_cast<bot_file_hdr*>(val_);
				ret = vtool.AVTV(&bot_net_finc, vp, check, use_empty);
				break;
			}
			case MTX_VARS:
			{
				BOT_VAR_T* vp = reinterpret_cast<BOT_VAR_T*>(val_);
				xmv.AddVar(vp->n, vp, BOT_RTV_VAR, vp->t, false);
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

				if (!vp->name.empty() || vp->prt.lid > -1)
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&bot_c_vec.mvec, vp, check, use_empty);
				}
				break;
			}
			case MTX_LOG:
			{
				BOT_LOGDET_M* vp = reinterpret_cast<BOT_LOGDET_M*>(val_);

				if (!vp->logtitle.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&bot_log_vec.mvec, vp, check, use_empty);
				}
				break;
			}
			case MTX_TTS:
			{
				TINFO_M* vp = reinterpret_cast<TINFO_M*>(val_);

				if (!vp->thread_name.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&tts_vec.mvec, vp, check, use_empty);
				}
				break;
			}
			case MTX_DBL:
			{
				BOT_DB_M* vp = reinterpret_cast<BOT_DB_M*>(val_);

				if (!vp->name.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&bot_db_vec.mvec, vp, check, use_empty);
				}
				break;
			}
			case MTX_FO:
			{
				BOT_FILE_M* vp = reinterpret_cast<BOT_FILE_M*>(val_);

				if (!vp->name.empty())
				{
					vp->c_by = lid;
					ret = vtool.AVTV(&fileo_vec.mvec, vp, check, use_empty);
				}
				break;
			}
			case MTX_PRC:
			{
				bot_proc_m* vp = reinterpret_cast<bot_proc_m*>(val_);

				if (!vp->anm.empty())
				{
					ret = vtool.AVTV(&prcs.mvec, vp, check, use_empty);
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
					ret = vtool.PTM(&bot_c_vec.dvec, ele, memb, v_opt, val_);

					if (ret > -1)
					{
						sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.PTM(&bot_log_vec.dvec, ele, memb, v_opt, val_);

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
					ret = vtool.PTM(&tts_vec.dvec, ele, memb, v_opt, val_);

					if (ret > -1)
					{
						sint iret = PushToVecEleMem(val_, g_opt, ele, memb, v_opt);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.PTM(&bot_db_vec.dvec, ele, memb, v_opt, val_);

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
					ret = vtool.PTM(&fileo_vec.dvec, ele, memb, v_opt, val_);

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
					ret = vtool.PTM(&bot_c_vec.mvec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.PTM(&bot_log_vec.mvec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.PTM(&tts_vec.mvec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.PTM(&bot_db_vec.mvec, ele, memb, v_opt, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.PTM(&fileo_vec.mvec, ele, memb, v_opt, val_);
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
					ret = vtool.GVIV(&bot_c_vec.dvec, ele, (BOT_CLIENT*)val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GVIV(&bot_log_vec.dvec, ele, (BOT_LOGDET*)val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GVIV(&tts_vec.dvec, ele, (TINFO*)val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GVIV(&bot_db_vec.dvec, ele, (BOT_DB*)val_);
					break;
				}
				case MTX_DBC:
				{
					ret = vtool.GVIA(DCON, ele, (DB_CONN*)val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GVIV(&fileo_vec.dvec, ele, (BOT_FILE*)val_);
					break;
				}
				case MTX_FCON:
				{
					ret = vtool.GVIA(FCON, ele, (BOTF_CONN*)val_);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.GVIV(&prcs.dvec, ele, (bot_proc*)val_);
					break;
				}
				case MTX_PORTS:
				{
					ret = vtool.GVIV(&bot_prts, ele, (bot_port*)val_);
					break;

				}
				case MTX_CIPS:
				{
					ret = vtool.GVIV(&bot_cips, ele, (carr_256*)val_);
					break;
				}
				case MTX_BIPS:
				{
					ret = vtool.GVIV(&bot_bips, ele, (carr_64*)val_);
					break;
				}
				case MTX_NET_FOUT:
				{
					ret = vtool.GVIV(&bot_net_fout, ele, (bot_file_hdr*)val_);
					break;
				}
				case MTX_NET_FINC:
				{
					ret = vtool.GVIV(&bot_net_finc, ele, (bot_file_hdr*)val_);
					break;
				}
				case MTX_VARS:
				{
					ret = xmv.GetVar(ele, BOT_RTV_VAR, val_);
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
					ret = vtool.GVIV(&bot_c_vec.mvec, ele, (BOT_CLIENT_M*)val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GVIV(&bot_log_vec.mvec, ele, (BOT_LOGDET_M*)val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GVIV(&tts_vec.mvec, ele, (TINFO_M*)val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GVIV(&bot_db_vec.mvec, ele, (BOT_DB_M*)val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GVIV(&fileo_vec.mvec, ele, (BOT_FILE_M*)val_);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.GVIV(&prcs.mvec, ele, (bot_proc_m*)val_);
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
					ret = vtool.GMIV(&bot_c_vec.dvec, ele, memb, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GMIV(&bot_log_vec.dvec, ele, memb, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GMIV(&tts_vec.dvec, ele, memb, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GMIV(&bot_db_vec.dvec, ele, memb, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GMIV(&fileo_vec.dvec, ele, memb, val_);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.GMIV(&prcs.dvec, ele, memb, val_);
					break;
				}
				case MTX_PORTS:
				{
					ret = vtool.GMIV(&bot_prts, ele, memb, val_);
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
					ret = vtool.GMIV(&bot_c_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.GMIV(&bot_log_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.GMIV(&tts_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.GMIV(&bot_db_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.GMIV(&fileo_vec.dvec, ele, memb, val_);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.GMIV(&prcs.dvec, ele, memb, val_);
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
						x = vtool.AVTV(&bot_c_vec.mvec, &nval, false, false);
					}
					else
					{
						BOT_CLIENT nval;
						x = vtool.AVTV(&bot_c_vec.dvec, &nval, false, false);
					}
					break;
				}
				case MTX_LOG:
				{
					if (is_meta)
					{
						BOT_LOGDET_M nval;
						x = vtool.AVTV(&bot_log_vec.mvec, &nval, false, false);
					}
					else
					{
						BOT_LOGDET nval;
						x = vtool.AVTV(&bot_log_vec.dvec, &nval, false, false);
					}
					break;
				}
				case MTX_TTS:
				{
					if (is_meta)
					{
						TINFO_M nval;
						x = vtool.AVTV(&tts_vec.mvec, &nval, false, false);
					}
					else
					{
						TINFO nval;
						x = vtool.AVTV(&tts_vec.dvec, &nval, false, false);
					}
					break;
				}
				case MTX_DBL:
				{
					if (is_meta)
					{
						BOT_DB_M nval;
						x = vtool.AVTV(&bot_db_vec.mvec, &nval, false, false);
					}
					else
					{
						BOT_DB nval;
						x = vtool.AVTV(&bot_db_vec.dvec, &nval, false, false);
					}
					break;
				}
				case MTX_FO:
				{
					if (is_meta)
					{
						BOT_FILE_M nval;
						x = vtool.AVTV(&fileo_vec.mvec, &nval, false, false);
					}
					else
					{
						BOT_FILE nval;
						x = vtool.AVTV(&fileo_vec.dvec, &nval, false, false);

					}
					break;
				}
				case MTX_PRC:
				{
					if (is_meta)
					{
						bot_proc_m nval;
						x = vtool.AVTV(&prcs.mvec, &nval, false, false);
					}
					else
					{
						bot_proc nval;
						x = vtool.AVTV(&prcs.dvec, &nval, false, false);

					}
					break;
				}
				case MTX_PORTS:
				{
					bot_port nval;
					x = vtool.AVTV(&bot_prts, &nval, false, false);
					break;
				}
				case MTX_CIPS:
				{
					carr_256 nval;
					x = vtool.AVTV(&bot_cips, nval.carr, false, false);
					break;
				}
				case MTX_BIPS:
				{
					carr_64 nval;
					x = vtool.AVTV(&bot_bips, nval.carr, false, false);
					break;
				}
				case MTX_NET_FOUT:
				{
					bot_file_hdr nval;
					x = vtool.AVTV(&bot_net_fout, &nval, false, false);
					break;
				}
				case MTX_NET_FINC:
				{
					bot_file_hdr nval;
					x = vtool.AVTV(&bot_net_finc, &nval, false, false);
					break;
				}
				case MTX_VARS:
				{
					BOT_VAR_T nval;
					carr_21  ncar;
					bot_sprintf(ncar.carr, ncar.siz, "%i", x);
					x = SVAR(ncar.carr, BOT_RTV_VAR, &nval);
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
					ret = vtool.SVIV(&bot_c_vec.dvec, ele, (BOT_CLIENT*)val_);

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
					ret = vtool.SVIV(&bot_log_vec.dvec, ele, (BOT_LOGDET*)val_);

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
					ret = vtool.SVIV(&tts_vec.dvec, ele, (TINFO*)val_);

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
					ret = vtool.SVIV(&bot_db_vec.dvec, ele, (BOT_DB*)val_);

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
					ret = vtool.SVIV(&fileo_vec.dvec, ele, (BOT_FILE*)val_);

					if (ret > -1)
					{
						BOT_FILE_M ns;
						ns.Renew((BOT_FILE*)val_);
						sint iret = SetVecEle(&ns, g_opt, ele, true);
					}
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.SVIV(&prcs.dvec, ele, (bot_proc*)val_);

					if (ret > -1)
					{
						bot_proc_m ns;
						ns.Renew((bot_proc*)val_);
						sint iret = SetVecEle(&ns, g_opt, ele, true);
					}
					break;
				}
				case MTX_PORTS:
				{
					ret = vtool.SVIV(&bot_prts, ele, (bot_port*)val_);
					break;
				}
				case MTX_CIPS:
				{
					ret = vtool.SVIV(&bot_cips, ele, (carr_256*)val_);
					break;
				}
				case MTX_BIPS:
				{
					ret = vtool.SVIV(&bot_bips, ele, (carr_64*)val_);
					break;
				}
				case MTX_NET_FOUT:
				{
					ret = vtool.SVIV(&bot_net_fout, ele, (bot_file_hdr*)val_);
					break;
				}
				case MTX_NET_FINC:
				{
					ret = vtool.SVIV(&bot_net_finc, ele, (bot_file_hdr*)val_);
					break;
				}
				case MTX_VARS:
				{
					BOT_VAR_T* var = reinterpret_cast<BOT_VAR_T*>(val_);

					if (var)
					{
						ret = xmv.AddVar(var->n, var, BOT_RTV_MAX, var->t, true);
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
					ret = vtool.SVIV(&bot_c_vec.mvec, ele, (BOT_CLIENT_M*)val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.SVIV(&bot_log_vec.mvec, ele, (BOT_LOGDET_M*)val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.SVIV(&tts_vec.mvec, ele, (TINFO_M*)val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.SVIV(&bot_db_vec.mvec, ele, (BOT_DB_M*)val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.SVIV(&fileo_vec.mvec, ele, (BOT_FILE_M*)val_);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.SVIV(&prcs.mvec, ele, (bot_proc_m*)val_);
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
					ret = vtool.SMIV(&bot_c_vec.dvec, ele, memb, val_);

					if (ret > -1)
					{
						sint iret = SetVecEleMem(val_, g_opt, ele, memb);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.SMIV(&bot_log_vec.dvec, ele, memb, val_);

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
					ret = vtool.SMIV(&tts_vec.dvec, ele, memb, val_);
					if (ret > -1)
					{
						sint iret = SetVecEleMem(val_, g_opt, ele, memb);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.SMIV(&bot_db_vec.dvec, ele, memb, val_);

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
					ret = vtool.SMIV(&fileo_vec.dvec, ele, memb, val_);

					if (ret > -1)
					{
						sint iret = SetVecEleMem(val_, g_opt, ele, memb);

						if (iret == ret)
						{

						}
					}
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.SMIV(&prcs.dvec, ele, memb, val_);

					if (ret > -1)
					{
						sint iret = SetVecEleMem(val_, g_opt, ele, memb);

						if (iret == ret)
						{

						}
					}
					break;
				}
				case MTX_PORTS:
				{
					ret = vtool.SMIV(&bot_prts, ele, memb, val_);
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
					ret = vtool.SMIV(&bot_c_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.SMIV(&bot_log_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.SMIV(&tts_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.SMIV(&bot_db_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.SMIV(&fileo_vec.mvec, ele, memb, val_);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.SMIV(&prcs.mvec, ele, memb, val_);
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
					ret = vtool.CEFV(&bot_c_vec.dvec, ele);
					sint cl = vtool.CLNV(&bot_c_vec.dvec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CEFV(&bot_log_vec.dvec, ele);
					sint cl = vtool.CLNV(&bot_log_vec.dvec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CEFV(&tts_vec.dvec, ele);
					sint cl = vtool.CLNV(&tts_vec.dvec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CEFV(&bot_db_vec.dvec, ele);
					sint cl = vtool.CLNV(&bot_db_vec.dvec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CEFV(&fileo_vec.dvec, ele);
					sint cl = vtool.CLNV(&fileo_vec.dvec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.CEFV(&prcs.dvec, ele);
					sint cl = vtool.CLNV(&prcs.dvec);

					if (ret > -1)
					{
						sint iret = ClearVecEle(g_opt, ele);
					}
					break;
				}
				case MTX_PORTS:
				{
					ret = vtool.CEFV(&bot_prts, ele);
					sint cl = vtool.CLNV(&bot_prts);
					break;
				}
				case MTX_CIPS:
				{
					ret = vtool.CEFV(&bot_cips, ele);
					sint cl = vtool.CLNV(&bot_cips);
					break;
				}
				case MTX_BIPS:
				{
					ret = vtool.CEFV(&bot_bips, ele);
					sint cl = vtool.CLNV(&bot_bips);
					break;
				}
				case MTX_NET_FOUT:
				{
					ret = vtool.CEFV(&bot_net_fout, ele);
					sint cl = vtool.CLNV(&bot_net_fout);
					break;
				}
				case MTX_NET_FINC:
				{
					ret = vtool.CEFV(&bot_net_finc, ele);
					sint cl = vtool.CLNV(&bot_net_finc);
					break;
				}
				case MTX_VARS:
				{
					ret = xmv.RemVar(ele);
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
					ret = vtool.CEFV(&bot_c_vec.mvec, ele);
					sint cl = vtool.CLNV(&bot_c_vec.mvec);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CEFV(&bot_log_vec.mvec, ele);
					sint cl = vtool.CLNV(&bot_log_vec.mvec);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CEFV(&tts_vec.mvec, ele);
					sint cl = vtool.CLNV(&tts_vec.mvec);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CEFV(&bot_db_vec.mvec, ele);
					sint cl = vtool.CLNV(&bot_db_vec.mvec);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CEFV(&fileo_vec.mvec, ele);
					sint cl = vtool.CLNV(&fileo_vec.mvec);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.CEFV(&prcs.mvec, ele);
					sint cl = vtool.CLNV(&prcs.mvec);
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
					ret = vtool.CMV(&bot_c_vec.dvec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CMV(&bot_log_vec.dvec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CMV(&tts_vec.dvec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CMV(&bot_db_vec.dvec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CMV(&fileo_vec.dvec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.CMV(&prcs.dvec, ele, memb);
					if (ret > -1)
					{
						sint iret = ClearVecEleMem(g_opt, ele, memb);
					}
					break;
				}
				case MTX_PORTS:
				{
					ret = vtool.CMV(&bot_prts, ele, memb);
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
					ret = vtool.CMV(&bot_c_vec.mvec, ele, memb);
					break;
				}
				case MTX_LOG:
				{
					ret = vtool.CMV(&bot_log_vec.mvec, ele, memb);
					break;
				}
				case MTX_TTS:
				{
					ret = vtool.CMV(&tts_vec.mvec, ele, memb);
					break;
				}
				case MTX_DBL:
				{
					ret = vtool.CMV(&bot_db_vec.mvec, ele, memb);
					break;
				}
				case MTX_FO:
				{
					ret = vtool.CMV(&fileo_vec.mvec, ele, memb);
					break;
				}
				case MTX_PRC:
				{
					ret = vtool.CMV(&prcs.mvec, ele, memb);
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
				ret = (sint)bot_c_vec.dvec.size();
				break;
			}
			case MTX_LOG:
			{
				ret = (sint)bot_log_vec.dvec.size();
				break;
			}
			case MTX_TTS:
			{
				ret = (sint)tts_vec.dvec.size();
				break;
			}
			case MTX_DBL:
			{
				ret = (sint)bot_db_vec.dvec.size();
				break;
			}
			case MTX_FO:
			{
				ret = (sint)fileo_vec.dvec.size();
				break;
			}
			case MTX_PRC:
			{
				ret = (sint)prcs.dvec.size();
				break;
			}
			case MTX_PORTS:
			{
				ret = (sint)bot_prts.size();
				break;
			}
			case MTX_CIPS:
			{
				ret = (sint)bot_cips.size();
				break;
			}
			case MTX_BIPS:
			{
				ret = (sint)bot_bips.size();
				break;
			}
			case MTX_NET_FOUT:
			{
				ret = (sint)bot_net_fout.size();
				break;
			}
			case MTX_NET_FINC:
			{
				ret = (sint)bot_net_finc.size();
				break;
			}
			case MTX_VARS:
			{
				ret = (sint)xmv.vars.size();
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
				ret = (sint)bot_c_vec.mvec.size();
				break;
			}
			case MTX_LOG:
			{
				ret = (sint)bot_log_vec.mvec.size();
				break;
			}
			case MTX_TTS:
			{
				ret = (sint)tts_vec.mvec.size();
				break;
			}
			case MTX_DBL:
			{
				ret = (sint)bot_db_vec.mvec.size();
				break;
			}
			case MTX_FO:
			{
				ret = (sint)fileo_vec.dvec.size();
				break;
			}
			case MTX_PRC:
			{
				ret = (sint)prcs.dvec.size();
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
sint machine::GetInVec(void* val_, sint g_opt, bool cine, bool is_meta)
{
	if (debug_lvl >= 800 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "GetInVec(void* val_(%i), sint g_opt(%i), bool cine(%u), bool is_meta(%u))", (sint)val_, g_opt, (uint)cine, (uint)is_meta);
		op = Output(outp.carr, 2);
	}

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
				if (!strcmp(np.name.c_str(), vp->name.c_str()) && np.prt.lid == vp->prt.lid)
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

			while (GetVecEle((void*)&np, g_opt, siz, is_meta) > -1)
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
	case MTX_PRC:
	{
		if (!is_meta)
		{
			bot_proc_m xval;
			xval.Renew(reinterpret_cast<bot_proc*>(val_));
			sint xc = GetInVec((void*)&xval, g_opt, false, true);

			if (xc > -1)
			{
				return GetVecEle(val_, g_opt, xval.lid, false);
			}
		}
		else
		{
			bot_proc_m* vp = reinterpret_cast<bot_proc_m*>(val_);
			bot_proc_m np;
			sint siz = 0;

			for (sint x = GetVecEle(&np, g_opt, siz, is_meta); x > -1; x = GetVecEle(&np, g_opt, siz, is_meta))
			{
				if (!strcmp(np.anm.c_str(), vp->anm.c_str()) && np.pid == vp->pid)
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
	case MTX_PORTS:
	{
		bot_port* vp = reinterpret_cast<bot_port*>(val_);
		bot_port np;
		sint siz = 0;

		while (GetVecEle((void*)&np, g_opt, siz, is_meta) > -1)
		{
			if (np.portn == vp->portn && ((bot_strlen(np.ipstr.carr) && !strcmp(np.ipstr.carr, vp->ipstr.carr)) || (bot_strlen(np.oipstr.carr) && !strcmp(np.oipstr.carr, vp->oipstr.carr))) && np.proto == vp->proto)
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
		break;
	}
	case MTX_CIPS:
	{
		carr_256* vp = reinterpret_cast<carr_256*>(val_);
		carr_256 np;
		sint siz = 0;

		while (GetVecEle((void*)&np, g_opt, siz, is_meta) > -1)
		{
			if (!strcmp(vp->carr, np.carr))
			{
				return siz;
			}
			siz++;
		}
		if (cine)
		{
			return PushToVec(val_, g_opt, true, true, is_meta);
		}
		break;
	}
	case MTX_NET_FOUT:
	{
		bot_file_hdr* vp = reinterpret_cast<bot_file_hdr*>(val_);
		bot_file_hdr np;
		sint siz = 0;

		if (vp->idh)
		{
			while (GetVecEle((void*)&np, g_opt, siz, is_meta) > -1)
			{
				if (np.idh && np.idh == vp->idh)
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
	case MTX_NET_FINC:
	{
		bot_file_hdr* vp = reinterpret_cast<bot_file_hdr*>(val_);
		bot_file_hdr np;
		sint siz = 0;

		if (vp->idh)
		{
			while (GetVecEle((void*)&np, g_opt, siz, is_meta) > -1)
			{
				if (np.idh && np.idh == vp->idh && np.seq == vp->seq)
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
	case MTX_VARS:
	{
		BOT_VAR_T* vp = reinterpret_cast<BOT_VAR_T*>(val_);
		BOT_VAR_T np;
		sint siz = 0;

		if (vp->n)
		{
			siz = GVAR(vp->n, BOT_RTV_VAR, val_);

			if (siz > -1)
			{
				return siz;
			}
			if (cine)
			{
				return PushToVec(val_, g_opt, true, true, is_meta);
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
			case MTX_PRC:
			{
				ret = GetVecEleMem(&str, g_opt, ele, BOT_PROC_NM);
				nvec->push_back(str);
				break;
			}
			case MTX_PORTS:
			{
				sint xret;
				sint sck;
				ret = GetVecEleMem(&xret, g_opt, ele, BOT_PORT_PTN);
				ret = GetVecEleMem(&sck, g_opt, ele, BOT_PORT_SCK);
				ret = bot_sprintfs(&str, true, "%i(%i)", xret, sck);
				ret = ele;
				nvec->push_back(str);
				break;
			}
			case MTX_CIPS:
			{
				carr_256 nc;
				ret = GetVecEle(&nc, g_opt, ele, false);
				str.append(nc.carr);

				if (!str.empty())
				{
					nvec->push_back(str);
				}
				break;
			}
			case MTX_BIPS:
			{
				carr_64 nc;
				ret = GetVecEle(&nc, g_opt, ele, false);
				str.append(nc.carr);

				if (!str.empty())
				{
					nvec->push_back(str);
				}
				break;
			}
			case MTX_NET_FOUT:
			case MTX_NET_FINC:
			{
				bot_file_hdr nc;
				ret = GetVecEle(&nc, g_opt, ele, false);
				bot_sprintfs(&str, true, "%li", nc.idh);

				if (!str.empty())
				{
					nvec->push_back(str);
				}
				break;
			}
			case MTX_VARS:
			{
				BOT_VAR_T nc;
				ret = GetVecEle(&nc, g_opt, ele, false);
				bot_sprintfs(&str, true, "%s", nc.n);

				if (!str.empty())
				{
					nvec->push_back(str);
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
			case MTX_PRC:
			{
				ret = GetVecEleMem(&str, g_opt, ele, BOT_PROC_NM);
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
			case MTX_PRC:
			{
				ret = GetVecEleMem(&r, g_opt, ele, BOT_PROC_LID);
				nvec->push_back(r);
				break;
			}
			case MTX_PORTS:
			{
				ret = GetVecEleMem(&r, g_opt, ele, BOT_PORT_LID);
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
			case MTX_PRC:
			{
				ret = GetVecEleMem(&r, g_opt, ele, BOT_PROC_LID);
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
		for (size_t siz = 0; siz < u_logs.size(); siz++)
		{
			if (!strcmp(nm, u_logs[siz].logtitle.c_str()))
			{
				return (sint)siz;
			}
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
	char nl = '\n';

	if (log_to[0])
	{
		carr_256 nam;
		sint xc = LogName(option, &nam, &ses_date);
		sint uc = UsingLog(nam.carr);
		std::string str;

		if (uc < 0)
		{
			BOT_LOGDET Current(nam.carr, ses_date.carr, option);
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
		BOT_LOGDET_M Current_m(nam.carr, ses_date.carr, option);
		xc = GetInVec(&Current_m, MTX_LOG);

		if (xc < 0)
		{
			BOT_LOGDET Current(nam.carr, ses_date.carr, option);
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
		sint xc = LogName(option, &nam, &ses_date, true);
		sint uc = UsingLog(nam.carr);
		std::string str;

		if (uc < 0)
		{
			BOT_LOGDET Current(nam.carr, ses_date.carr, option);
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
		BOT_LOGDET_M Current_m(nam.carr, ses_date.carr, option);
		xc = GetInVec(&Current_m, MTX_LOG);

		if (xc < 0)
		{
			BOT_LOGDET Current(nam.carr, ses_date.carr, option);
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

// Runtime Variables

sint machine::IVAR(c_char* typ, c_char* nm, c_char* val)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "IVAR(c_char* typ(%i), c_char* nm(%i), c_char* val(%i)", (sint)typ, (sint)nm, (sint)val);
		oc = Output(ncar.carr, 2);
	}

	if (!nm)
	{
		return -1;
	}

	size_t nl = bot_cstrlen(nm);

	if (nl > 512)
	{
		return -1;
	}

	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);
	
	if (lx > -1)
	{
		sint xc = xmv.FindVar(nm);

		if (xc < 0)
		{
			if (!strcmp(UCASE(typ).c_str(), "INT"))
			{
				if (val)
				{
					sllint var = (sllint)_atoi64(val);
					xc = xmv.AddVar(nm, &var, BOT_RTV_SLLINT, BOT_RTV_SLLINT);
				}
				else
				{
					sllint var = 0;
					xc = xmv.AddVar(nm, &var, BOT_RTV_SLLINT, BOT_RTV_SLLINT);
				}

			}
			else if (!strcmp(UCASE(typ).c_str(), "REAL"))
			{
				if (val)
				{
					float var = (float)atof(val);
					xc = xmv.AddVar(nm, &var, BOT_RTV_REAL, BOT_RTV_REAL);
				}
				else
				{
					float var = 0.0f;
					xc = xmv.AddVar(nm, &var, BOT_RTV_REAL, BOT_RTV_REAL);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "TEXT"))
			{
				if (val)
				{
					std::string var(val);
					xc = xmv.AddVar(nm, &var, BOT_RTV_STR, BOT_RTV_STR);
				}
				else
				{
					std::string var;
					xc = xmv.AddVar(nm, &var, BOT_RTV_STR, BOT_RTV_STR);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "BLOB"))
			{
				if (val)
				{
					size_t vl = bot_cstrlen(val);
					_char* var = (_char*)malloc(vl + 1);

					if (var)
					{
						_char trm = '\0';
						memcpy((void*)var, (void*)val, vl);
						memcpy((void*)&var[vl], (void*)&trm, sizeof(_char));
						xc = xmv.AddVar(nm, var, BOT_RTV_BLOB, BOT_RTV_BLOB);
						free(var);
					}
				}
				else
				{
					_char var[2] = { 0 };
					xc = xmv.AddVar(nm, var, BOT_RTV_BLOB, BOT_RTV_BLOB);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "VINT"))
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSLLINT, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSLLINT, BOT_RTV_SLLINT);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "VREAL"))
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VREAL, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VREAL, BOT_RTV_REAL);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "VTEXT"))
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSTR, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSTR, BOT_RTV_VARG);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "VBLOB"))
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VBLOB, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VBLOB, BOT_RTV_VBLOB);
				}
			}
			else if (!strcmp(UCASE(typ).c_str(), "FILE"))
			{
				if (val)
				{
					BOT_FILE_M file(val, "", "", BOT_FILE_READ);
					sint ox = -1;
					xc = BOTOpenFile(&file, &ox, true, false, false, true);

					if (xc > -1)
					{
						if (!ox)
						{
							ox = BOTCloseFile(&file);
						}
						bot_file_hdr hdr(&file);
						xc = xmv.AddVar(nm, &hdr, BOT_RTV_FHD, BOT_RTV_FHD);
					}
				}
			}
			else {}
		}

		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return xc;
	}
	return -1;
}
sint machine::IVAR(sint typ, c_char* nm, c_char* val)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "IVAR(sint typ(%i), c_char* nm(%i), c_char* val(%i)", typ, (sint)nm, (sint)val);
		oc = Output(ncar.carr, 2);
	}

	if (!nm)
	{
		return -1;
	}

	size_t nl = bot_cstrlen(nm);

	if (nl > 512)
	{
		return -1;
	}

	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);

	if (lx > -1)
	{
		sint xc = xmv.FindVar(nm);

		if (xc < 0)
		{
			if (typ == BOT_RTV_SLLINT)
			{
				if (val)
				{
					sllint var = (sllint)_atoi64(val);
					xc = xmv.AddVar(nm, &var, BOT_RTV_SLLINT, BOT_RTV_SLLINT);
				}
				else
				{
					sllint var = 0;
					xc = xmv.AddVar(nm, &var, BOT_RTV_SLLINT, BOT_RTV_SLLINT);
				}

			}
			else if (typ == BOT_RTV_REAL)
			{
				if (val)
				{
					float var = (float)atof(val);
					xc = xmv.AddVar(nm, &var, BOT_RTV_REAL, BOT_RTV_REAL);
				}
				else
				{
					float var = 0.0f;
					xc = xmv.AddVar(nm, &var, BOT_RTV_REAL, BOT_RTV_REAL);
				}
			}
			else if (typ == BOT_RTV_STR)
			{
				if (val)
				{
					std::string var(val);
					xc = xmv.AddVar(nm, &var, BOT_RTV_STR, BOT_RTV_STR);
				}
				else
				{
					std::string var;
					xc = xmv.AddVar(nm, &var, BOT_RTV_STR, BOT_RTV_STR);
				}
			}
			else if (typ == BOT_RTV_BLOB)
			{
				if (val)
				{
					size_t vl = bot_cstrlen(val);
					_char* var = (_char*)malloc(vl + 1);

					if (var)
					{
						_char trm = '\0';
						memcpy((void*)var, (void*)val, vl);
						memcpy((void*)&var[vl], (void*)&trm, sizeof(_char));
						xc = xmv.AddVar(nm, var, BOT_RTV_BLOB, BOT_RTV_BLOB);
						free(var);
					}
				}
				else
				{
					_char var[2] = { 0 };
					xc = xmv.AddVar(nm, &var, BOT_RTV_BLOB, BOT_RTV_BLOB);
				}
			}
			else if (typ == BOT_RTV_VSLLINT)
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSLLINT, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSLLINT, BOT_RTV_SLLINT);
				}
			}
			else if (typ == BOT_RTV_VREAL)
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VREAL, BOT_RTV_VREAL);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VREAL, BOT_RTV_REAL);
				}
			}
			else if (typ == BOT_RTV_VSTR)
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSTR, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VSTR, BOT_RTV_VSTR);
				}
			}
			else if (typ == BOT_RTV_VBLOB)
			{
				std::vector<BOT_ARG> vec;

				if (val)
				{
					size_t vl = bot_cstrlen(val);
					xc = ArgSep(&vec, false, 0, vl, val, BOT_RTV_CHAR, ' ');
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VBLOB, BOT_RTV_VARG);
				}
				else
				{
					xc = xmv.AddVar(nm, &vec, BOT_RTV_VBLOB, BOT_RTV_VBLOB);
				}
			}
			else if (typ == BOT_RTV_FHD)
			{
				if (val)
				{
					BOT_FILE_M file(val, "", "", 0);
					sint ox = -1;
					xc = BOTOpenFile(&file, &ox, true, false, false, true);

					if (xc > -1)
					{
						if (!ox)
						{
							ox = BOTCloseFile(&file);
						}
						bot_file_hdr hdr(&file);
						xc = xmv.AddVar(nm, &file, BOT_RTV_FHD, BOT_RTV_FHD);
					}
				}
			}
			else {}
		}
		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return xc;
	}
	return -1;
}
sint machine::PVAR(c_char* nm, ...)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::PVAR(c_char* nm(%i), ...)", (sint)nm);
		op = Output(outp.carr, 2);
	}

	if (!nm)
	{
		return -1;
	}

	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);

	if (lx > -1)
	{
		sint xc = xmv.FindVar(nm);

		if (xc > -1)
		{
			std::vector<sint> outs;
			va_list args;
			va_start(args, nm);
			bool done = false;

			while (!done)
			{
				sint inv = va_arg(args, sint);

				if (inv > -1)
				{
					outs.push_back(inv);
				}
				else
				{
					done = true;
				}
			}

			va_end(args);

			for (size_t siz = 0; siz < outs.size(); siz++)
			{
				switch (xmv.vars[xc].t)
				{
				case BOT_RTV_SLLINT:
				{
					std::string xcar("INT ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						if (!xmv.vars[xc].v[0].empty())
						{
							_char* nv = (_char*)malloc(sizeof(sllint));

							if (nv)
							{
								for (size_t z = 0; z < sizeof(sllint); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[xc].v[0][z], sizeof(_char));
								}

								sllint val;
								memcpy((void*)&val, (void*)nv, sizeof(sllint));
								sint xp = bot_sprintfs(&xcar, false, " = %lli", val);
								free(nv);
							}
						}
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_REAL:
				{
					std::string xcar("REAL ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						if (!xmv.vars[xc].v[0].empty())
						{
							_char* nv = (_char*)malloc(sizeof(float));

							if (nv)
							{
								for (size_t z = 0; z < sizeof(float); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[xc].v[0][z], sizeof(_char));
								}

								float val;
								memcpy((void*)&val, (void*)nv, sizeof(float));
								sint xp = bot_sprintfs(&xcar, false, " = %.9f", val);
								free(nv);
							}
						}
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_STR:
				{
					std::string xcar("TEXT ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						if (!xmv.vars[xc].v[0].empty())
						{
							xcar.append(" = ");

							for (size_t z = 0; z < xmv.vars[xc].v[0].size(); z++)
							{
								xcar.push_back(xmv.vars[xc].v[0][z]);
							}
						}
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_BLOB:
				{
					std::string xcar("BLOB ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						if (!xmv.vars[xc].v[0].empty())
						{
							xcar.append(" = ");

							for (size_t z = 0; z < xmv.vars[xc].v[0].size(); z++)
							{
								sint xp = bot_sprintfs(&xcar, false, "0x%02X ", xmv.vars[xc].v[0][z]);
							}
							xcar.pop_back();
						}
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					std::string xcar("VINT ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						_char* np = (_char*)malloc(sizeof(sllint));

						if (np)
						{
							xcar.append("\n{\n\t");

							for (size_t z = 0; z < xmv.vars[xc].v.size(); z++)
							{
								sint xp = bot_sprintfs(&xcar, false, "[%u] ", z);

								for (size_t w = 0; w < xmv.vars[xc].v[z].size(); w++)
								{
									memcpy((void*)&np[w], (void*)&xmv.vars[xc].v[z][w], sizeof(_char));
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
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_VREAL:
				{
					std::string xcar("VREAL ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						xcar.append("\n{\n\t");
						_char* nv = (_char*)malloc(sizeof(float));

						if (nv)
						{
							for (size_t z = 0; z < xmv.vars[xc].v.size(); z++)
							{
								sint xp = bot_sprintfs(&xcar, false, "[%u] ", z);

								for (size_t w = 0; w < sizeof(float); w++)
								{
									memcpy((void*)&nv[w], (void*)&xmv.vars[xc].v[z][w], sizeof(_char));
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
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_VSTR:
				{
					std::string xcar("VTEXT ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						xcar.append("\n{\n\t");
						for (size_t z = 0; z < xmv.vars[xc].v.size(); z++)
						{
							sint xp = bot_sprintfs(&xcar, false, "[%u] ", z);

							for (size_t w = 0; w < xmv.vars[xc].v[z].size(); w++)
							{
								xcar.push_back(xmv.vars[xc].v[z][w]);
							}
							xcar.append(",\n\t");
						}
						xcar.pop_back();
						xcar.pop_back();
						xcar.pop_back();
						xcar.append("\n}");
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_VBLOB:
				{
					std::string xcar("VBLOB ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						xcar.append("\n{\n\t");
						for (size_t z = 0; z < xmv.vars[xc].v.size(); z++)
						{
							sint xp = bot_sprintfs(&xcar, false, "[%u] %v0x%02X %,\n\t", z, &xmv.vars[xc].v[z]);
						}
						xcar.pop_back();
						xcar.pop_back();
						xcar.pop_back();
						xcar.append("\n}");
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				case BOT_RTV_FHD:
				{
					std::string xcar("FILE ");
					xcar.append(xmv.vars[xc].n);

					if (!xmv.vars[xc].v.empty())
					{
						if (!xmv.vars[xc].v[0].empty() && !xmv.vars[xc].v[1].empty())
						{
							bot_file_hdr hdr;
							slint av = 0;
							sint bv = 0;
							_char* nv = (_char*)malloc(sizeof(slint));

							if (nv)
							{
								for (size_t z = 0; z < sizeof(slint); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[xc].v[0][z], sizeof(_char));
								}

								memcpy((void*)&av, (void*)nv, sizeof(slint));

								for (size_t z = 0; z < sizeof(sint); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[xc].v[1][z], sizeof(_char));
								}

								memcpy((void*)&bv, (void*)nv, sizeof(sint));
								BOT_FILE_M file;
								sint rc = GetVecEle(&file, MTX_FO, bv);

								if (rc > -1)
								{
									sint xp = bot_sprintfs(&xcar, false, "\n%s\n%lu bytes", BOTFileStr(&file).c_str(), file.fst.filestats.st_size);
								}
								else
								{
									sint xp = bot_sprintfs(&xcar, false, "file: %s not found", xmv.vars[xc].n);
								}
								free(nv);
							}
						}
					}
					sint xp = Output(0, true, xcar.c_str(), outs[siz], -1);
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return xc;
	}
	return -1;
}
sint machine::FVAR(c_char* nm)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::FVAR(c_char* nm(%i))", (sint)nm);
		op = Output(outp.carr, 2);
	}
	if (!nm)
	{
		return -1;
	}
	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);
	
	if (lx > -1)
	{
		sint ret = xmv.FindVar(nm);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return ret;
	}
	return -1;
}
sint machine::GVAR(c_char* nm, sint as_t, void* val)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GVAR(c_char* nm(%i), sint as_t, void*(%i))", (sint)nm, as_t, (sint)val);
		op = Output(outp.carr, 2);
	}
	if (!nm || !val)
	{
		return -1;
	}
	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);

	if (lx > -1)
	{
		sint ret = xmv.GetVar(nm, as_t, val);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return ret;
	}
	return -1;
}
sint machine::SVAR(c_char* nm, sint nt, void* val)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::SVAR(c_char* nm(%i), sint nt(%i), void* val(%i))", (sint)nm, nt, (sint)val);
		op = Output(outp.carr, 2);
	}
	if (!nm || !val)
	{
		return -1;
	}

	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);

	if (lx > -1)
	{
		sint ret = xmv.AddVar(nm, val, BOT_RTV_MAX, nt, true);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return ret;
	}
	return -1;
}
sint machine::RVAR(c_char* nm)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_48 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::RVAR(c_char* nm(%i))", (sint)nm);
		op = Output(outp.carr, 2);
	}
	if (!nm)
	{
		return -1;
	}

	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);

	if (lx > -1)
	{
		sint ret = xmv.RemVar(nm);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return ret;
	}
	return -1;
}
sint machine::LVARS(sint n, ...)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::LVARS(sint n(%i), ...)", n);
		op = Output(outp.carr, 2);
	}

	std::vector<sint> outs;
	va_list args;
	va_start(args, n);
	bool done = false;

	while (!done)
	{
		sint inv = va_arg(args, sint);

		if (inv > -1)
		{
			outs.push_back(inv);
		}
		else
		{
			done = true;
		}
	}

	va_end(args);
	sint ox = -1;
	sint lx = LockGMutex(MTX_VARS, &ox);

	if (lx > -1)
	{
		sint xc = -1;

		for (size_t siz = 0; siz < outs.size(); siz++)
		{
			for (size_t x = 0; x < xmv.vars.size(); x++)
			{
				std::string str;

				switch (xmv.vars[x].t)
				{
				case BOT_RTV_SLLINT:
				{
					str.append("INT ");

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}
					if (!xmv.vars[x].v.empty())
					{
						_char* nv = (_char*)malloc(sizeof(sllint));

						if (nv)
						{
							for (size_t z = 0; z < sizeof(sllint); z++)
							{
								memcpy((void*)&nv[z], (void*)&xmv.vars[x].v[0][z], sizeof(_char));
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

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}
					if (!xmv.vars[x].v.empty())
					{
						_char* nv = (_char*)malloc(sizeof(float));

						if (nv)
						{
							for (size_t z = 0; z < sizeof(float); z++)
							{
								memcpy((void*)&nv[z], (void*)&xmv.vars[x].v[0][z], sizeof(_char));
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

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}
					if (!xmv.vars[x].v.empty())
					{
						str.append(" = ");

						for (size_t y = 0; y < xmv.vars[x].v[0].size(); y++)
						{
							str.push_back(xmv.vars[x].v[0][y]);
						}
					}
					break;
				}
				case BOT_RTV_BLOB:
				{
					str.append("BLOB ");

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}
					if (!xmv.vars[x].v.empty())
					{
						str.append(" = ");

						for (size_t y = 0; y < xmv.vars[x].v[0].size(); y++)
						{
							xc = bot_sprintfs(&str, false, "0x%02X ", xmv.vars[x].v[0][y]);
						}
						str.pop_back();
					}
					break;
				}
				case BOT_RTV_VSLLINT:
				{
					str.append("VINT ");

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}
					_char* nv = (_char*)malloc(sizeof(sllint));

					if (nv)
					{
						if (!xmv.vars[x].v.empty())
						{
							str.append("\n{\n\t");
							for (size_t y = 0; y < xmv.vars[x].v.size(); y++)
							{
								xc = bot_sprintfs(&str, false, "[%u] ", y);
								for (size_t z = 0; z < sizeof(sllint); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[x].v[y][z], sizeof(_char));
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

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}
					_char* nv = (_char*)malloc(sizeof(float));

					if (nv)
					{
						if (!xmv.vars[x].v.empty())
						{
							str.append("\n{\n\t");
							for (size_t y = 0; y < xmv.vars[x].v.size(); y++)
							{
								xc = bot_sprintfs(&str, false, "[%u] ", y);
								for (size_t z = 0; z < sizeof(float); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[x].v[y][z], sizeof(_char));
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

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}

					if (!xmv.vars[x].v.empty())
					{
						str.append("\n{\n\t");
						for (size_t y = 0; y < xmv.vars[x].v.size(); y++)
						{
							xc = bot_sprintfs(&str, false, "[%u] %v%c%,\n\t", y, &xmv.vars[x].v[y]);
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

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}

					if (!xmv.vars[x].v.empty())
					{
						str.append("\n{\n\t");
						for (size_t y = 0; y < xmv.vars[x].v.size(); y++)
						{
							xc = bot_sprintfs(&str, false, "[%u] %v0x%02X %,\n\t", y, &xmv.vars[x].v[y]);
						}
						str.pop_back();
						str.pop_back();
						str.pop_back();
						str.append("\n}");
					}
					break;
				}
				case BOT_RTV_FHD:
				{
					str.append("FILE ");

					if (xmv.vars[x].n)
					{
						str.append(xmv.vars[x].n);
					}

					if (!xmv.vars[x].v.empty())
					{
						if (!xmv.vars[x].v[0].empty() && !xmv.vars[x].v[1].empty())
						{
							bot_file_hdr hdr;
							slint av = 0;
							sint bv = 0;
							_char* nv = (_char*)malloc(sizeof(slint));

							if (nv)
							{
								for (size_t z = 0; z < sizeof(slint); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[x].v[0][z], sizeof(_char));
								}

								memcpy((void*)&av, (void*)nv, sizeof(slint));

								for (size_t z = 0; z < sizeof(sint); z++)
								{
									memcpy((void*)&nv[z], (void*)&xmv.vars[x].v[1][z], sizeof(_char));
								}

								memcpy((void*)&bv, (void*)nv, sizeof(sint));
								BOT_FILE_M file;
								sint rc = GetVecEle(&file, MTX_FO, bv);

								if (rc > -1)
								{
									sint ox = -1;
									rc = BOTOpenFile(&file, &ox, true);

									if (rc > -1)
									{
										sint xp = bot_sprintfs(&str, false, "\n%s\n%lu bytes", BOTFileStr(&file).c_str(), file.fst.filestats.st_size);

										if (!ox)
										{
											ox = BOTCloseFile(&file);
										}
									}
									else
									{
										sint xp = bot_sprintfs(&str, false, "\nfile: %s not found", xmv.vars[x].n);
									}
								}
								free(nv);
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
				xc = Output(0, true, str.c_str(), outs[siz], -1);
			}
		}
		if (!ox)
		{
			ox = UnlockGMutex(MTX_VARS);
		}
		return xc;
	}
	return -1;
}

// Commands

sint machine::Command(BOT_CLIENT_M* cli, std::vector<BOT_ARG>* vec_)
{
	if (debug_lvl >= 1000 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::Command(BOT_CLIENT_M* cli(%i), std::vector<BOT_ARG>* vec_(%i))", (sint)cli, (sint)vec_);
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
	sint xc = GetCommand(cli, &Command);

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
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 1", 2);
		}
		if (vec_->size() > 1)
		{
			carr_256 ips;
			xc = 0;
			while (GetVecEle(&ips, MTX_CIPS, xc++, false) > -1)
			{
				std::vector<std::string> av;
				sint rc = ArgSep(&av, false, 0, bot_strlen(ips.carr), ips.carr, BOT_RTV_CHAR, ' ');

				if (rc > -1 && av.size() > 2)
				{
					rc = BOTXNCon(av[0].c_str(), av[1].c_str(), atoi(av[2].c_str()));
				}
			}

			if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "ALL") || !strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "0"))
			{
				bot_proc np;
				xc = 1;

				while (GetVecEle(&np, MTX_PRC, xc++, false) > -1)
				{
					if (BOTUnFork(&np) > -1)
					{
						carr_1024 xcar;
						xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
						xc = Output(cli, true, xcar.carr, 2, 0);
						xc = ClearVecEle(MTX_PRC, np.lid, false);
					}
				}
			}
			else if (bot_sisn(vec_->at(1).arg.c_str(), vec_->at(1).arg.length()))
			{
				bot_proc np;
				xc = GetVecEle(&np, MTX_PRC, (sint)atoi(vec_->at(1).arg.c_str()), false);

				if (xc > -1)
				{
					if (BOTUnFork(&np) > -1)
					{
						carr_1024 xcar;
						xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
						xc = Output(cli, true, xcar.carr, 2, 0);
						xc = ClearVecEle(MTX_PRC, np.lid, false);
					}
				}
				else
				{
					slint nid = (slint)_atoi64(vec_->at(1).arg.c_str());
					xc = 0;

					while (GetVecEle(&np, MTX_PRC, xc++, false) > -1)
					{
						if (np.pid == nid)
						{
							if (BOTUnFork(&np) > -1)
							{
								carr_1024 xcar;
								xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
								xc = Output(cli, true, xcar.carr, 2, 0);
								xc = ClearVecEle(MTX_PRC, np.lid, false);
							}
						}
					}
				}
			}
			else {}
		}
		sint oc = SetThreadQuit(1);
		break;
	}
	case 2:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 2", 2);
		}
		if (vec_->size() > 2)
		{
			if (!vec_->at(1).arg.empty() && !vec_->at(2).arg.empty())
			{
				if (cli->name.empty())
				{
					cli->name.append(vec_->at(1).arg.c_str());
				}

				xc = BOTGetLogin(cli, vec_->at(2).arg.c_str());

				if (!cli->loggedin)
				{
					xc = Output(cli, true, "login failed", 2, 0);
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
		xc = GetCommands(cli, &vec);

		if (vec_->size() == 1)
		{
			for (uint x = 0; x < vec.size(); x++)
			{
				carr_128 ncar;
				sint oc = bot_sprintf(ncar.carr, ncar.siz, "%i %s", vec[x].cmd_id, vec[x].cmd.c_str());
				oc = Output(cli, true, ncar.carr, 2, 0);
			}
		}
		else
		{
			for (size_t y = 1; y < vec_->size() && y < 21; y++)
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
								"\n(optional)a: new level 0-UINT_MAX - If arg(a) set the current level. debug_level restricts debug messages by approximate level of execution within code." \
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
								"\nInitialize a variable of type: INT, REAL, TEXT, BLOB, VINT, VREAL, VTEXT, VBLOB", ncar.carr);
							break;
						}
						case 7:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: name" \
								"\nShow variable", ncar.carr);
							break;
						}
						case 8:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n(optional)1: name" \
								"\nClear variable - if none specified clear all variables", ncar.carr);
							break;
						}
						case 9:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nList variables", ncar.carr);
							break;
						}
						case 20:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: args" \
								"\nSpawn a process", ncar.carr);
							break;
						}
						case 21:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nList spawned processes", ncar.carr);
							break;
						}
						case 22:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: arg - path or id or pid" \
								"\nClose a spawned process", ncar.carr);
							break;
						}
						case 30:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nList threads", ncar.carr);
							break;
						}
						case 31:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n(optional)1: num test threads (default=100)" \
								"\nTest threads", ncar.carr);
							break;
						}
						case 32:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: arg - lid or thread name" \
								"\nClose a thread", ncar.carr);
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
								"\n1: mode" \
								"\n2: encoding" \
								"\n3: name" \
								"\n4: type" \
								"\n5: file destination" \
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
						case 101:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: protocol [ TCP ] || [ UDP ] || [ RAW ] || [ PGM ]" \
								"\n2: port = 0-65535" \
								"\n3: duration [ 0 || I || i = Indefinite ] or [ 0-UINT_MAX seconds ]" \
								"\n4: timeout [ 0-600 seconds ]" \
								"\n5: q [ 0 = 100 ] or [ 1-100 ]" \
								"\nStart a server process.", ncar.carr);
							break;
						}
						case 102:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\n2: port = 0-65535" \
								"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ]" \
								"\nConnect to a server process.", ncar.carr);
							break;
						}
						case 103:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\n2: port = 0-65535" \
								"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ]" \
								"\nDisconnect from a server process.", ncar.carr);
							break;
						}
						case 104:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\n2: port = 0-65535" \
								"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ]" \
								"\n4: data" \
								"\nSend var data to an address.", ncar.carr);
							break;
						}
						case 105:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\n2: port = 0-65535" \
								"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ]" \
								"\n4: data" \
								"\nSend secure data to an address.", ncar.carr);
							break;
						}
						case 106:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\n2: port = 0-65535" \
								"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ]" \
								"\n4: file location" \
								"\nSend secure file to an address.", ncar.carr);
							break;
						}
						case 125:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\nBan an address.", ncar.carr);
							break;
						}
						case 126:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: address" \
								"\nUnban an address.", ncar.carr);
							break;
						}
						case 107:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\nList banned addresses.", ncar.carr);
							break;
						}
						case 200:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: file name" \
								"\n(optional)2: init as list held in memory [1/0] || [True/False] || [Yes/No] Default:0" \
								"\nAdd Create a list of VINs in \\bot_ldso\\ldso\\ from file in \\bot_lds\\ldsi\\", ncar.carr);
							break;
						}
						case 201:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: file name" \
								"\nCreate a script to rename photos of VINs in \\bot_lds\\ldso\\ from variable <file name > if file name matches variable held in memory; else from file in \\bot_lds\\ldsi\\<file name>", ncar.carr);
							break;
						}
						case 202:
						{
							oc = bot_sprintf(xcar.carr, xcar.siz, "%s" \
								"\n1: file name" \
								"\n(optional)2: is variable" \
								"\nCreate a statement to update inspections for VINs in \\bot_lds\\ldso\\ if 'is variable' from variable 'vins' held in memory; else from file in \\bot_lds\\ldsi\\<file name>;", ncar.carr);
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
							oc = Output(cli, true, xcar.carr, 2, 0);
						}
					}
				}
			}
		}
		break;
	}
	case 4:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 5", 2);
		}
		carr_256 ips;
		xc = 0;
		while (GetVecEle(&ips, MTX_CIPS, xc++, false) > -1)
		{
			std::vector<std::string> av;
			sint rc = ArgSep(&av, false, 0, bot_strlen(ips.carr), ips.carr, BOT_RTV_CHAR, ' ');

			if (rc > -1 && av.size() > 2)
			{
				rc = BOTXNCon(av[0].c_str(), av[1].c_str(), atoi(av[2].c_str()));
			}
		}

		if (vec_->size() > 1)
		{
			if (strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "1"))
			{
				bot_proc np;
				xc = 1;

				while (GetVecEle(&np, MTX_PRC, xc++, false) > -1)
				{
					if (BOTUnFork(&np) > -1)
					{
						carr_1024 xcar;
						sint rc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
						rc = Output(cli, true, xcar.carr, 2, 0);
						rc = ClearVecEle(MTX_PRC, np.lid, false);
					}
				}
			}
		}
		xc = GetInVec(cli, MTX_CV);

		if (xc > -1)
		{
			sint rc = ClearVecEle(MTX_CV, cli->lid, false);
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
			xc = GetDBG(&debug_lvl, &debug_m);
			carr_128 ncar;
			xc = bot_sprintf(ncar.carr, ncar.siz, "debug level:%i debug mode:%i", debug_lvl, debug_m);
			xc = Output(cli, true, ncar.carr, 2, 0);
		}
		else if (vec_->size() == 2)
		{
			if (bot_sisn(vec_->at(1).arg.c_str(), (sint)vec_->at(1).arg.length()))
			{
				xc = SetDBG(atoi(vec_->at(1).arg.c_str()), -1);
			}
			else if (!strcmp(&vec_->at(1).arg[0], "l"))
			{
				xc = GetDBG(&debug_lvl, &debug_m);
				carr_64 ncar;
				xc = bot_sprintf(ncar.carr, ncar.siz, "debug level:%i", debug_lvl);
				xc = Output(cli, true, ncar.carr, 2, 0);
			}
			else if (!strcmp(&vec_->at(1).arg[0], "m"))
			{
				xc = GetDBG(&debug_lvl, &debug_m);
				carr_64 ncar;
				xc = bot_sprintf(ncar.carr, ncar.siz, "debug mode:%i", debug_m);
				xc = Output(cli, true, ncar.carr, 2, 0);
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
				"\nIf args: \ndebug_level restricts debug messages by approximate level of execution within code.\nmode 0: no debug output, 1: debug output to logs only, 2: debug output to console and logs" \
				"\nIf 0 args: show current level and mode");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 6:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 6", 2);
		}
		if (vec_->size() == 3)
		{
			xc = IVAR(vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str());
		}
		else if (vec_->size() > 3)
		{
			for (size_t x = 4; x < vec_->size(); x++)
			{
				vec_->at(3).arg.push_back(' ');
				vec_->at(3).arg.append(vec_->at(x).arg.c_str());
			}
			xc = IVAR(vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str(), vec_->at(3).arg.c_str());
		}
		else
		{
			carr_168 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: type" \
				"\n2: name" \
				"\n(optional)3: value" \
				"\nInitialize a variable of type: INT, REAL, TEXT, BLOB, VINT, VREAL, VTEXT, VBLOB, FILE");
			oc = Output(cli, true, xcar.carr, 2, 0);
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
			xc = PVAR(vec_->at(1).arg.c_str(), 2, 0, -1);
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: name" \
				"\nShow variable");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 8:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 8", 2);
		}
		if (vec_->size() == 1)
		{
			sint ox = -1;
			sint lx = LockGMutex(MTX_VARS, &ox);

			if (lx > -1)
			{
				xmv.Clear();

				if (!ox)
				{
					ox = UnlockGMutex(MTX_VARS);
				}
			}
		}
		else
		{
			for (size_t y = 1; y < vec_->size(); y++)
			{
				xc = RVAR(vec_->at(y).arg.c_str());
			}
		}
		break;
	}
	case 9:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 9", 2);
		}
		if (!vec_->empty())
		{
			xc = LVARS(0, 2, 0, -1);
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: name" \
				"\nShow variable");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 20:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 20", 2);
		}
		if (vec_->size() > 1)
		{
			bot_proc np;
			xc = GetVecEle(&np, MTX_PRC, 0, false);
			np.f = CREATE_NEW_CONSOLE;
			size_t ln = 0;

			for (size_t x = 1; x < vec_->size(); x++)
			{
				ln += (vec_->at(x).arg.length() + 7);
			}

			if (ln && ln < 32768)
			{
				_char* cl = (_char*)malloc(ln);

				if (cl)
				{
					size_t xl = 0;
					_char trm = '\0';
					_char spc = ' ';

					for (size_t x = 1; x < vec_->size(); x++)
					{
						memcpy((void*)&cl[xl], (void*)vec_->at(x).arg.c_str(), vec_->at(x).arg.length());
						xl += vec_->at(x).arg.length();
						memcpy((void*)&cl[xl], (void*)&spc, sizeof(_char));
						xl += sizeof(_char);
					}
					memcpy((void*)&cl[xl - 1], (void*)&trm, sizeof(_char));
					xc = BOTFork(&np, cl);
					sllint rst = Rest(BOT_MILLI_REST * 1000);
					free(cl);
				}
			}
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: args" \
				"\nSpawn a process");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 21:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 21", 2);
		}
		if (!vec_->empty())
		{
			std::string pstr;
			bot_proc np;
			xc = 0;

			while (GetVecEle(&np, MTX_PRC, xc++, false) > -1)
			{
				bot_sprintfs(&pstr, false, "\n%s[%i] pid:%li", np.anm.c_str(), np.lid, np.pid);
			}

			xc = Output(cli, true, pstr.c_str(), 2, 0);
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\nList spawned processes");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 22:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 22", 2);
		}
		if (vec_->size() > 1)
		{
			if (!bot_sisn(vec_->at(1).arg.c_str(), vec_->at(1).arg.length()))
			{
				bot_proc np(vec_->at(1).arg.c_str());
				xc = GetInVec(&np, MTX_PRC, false, false);

				if (xc > -1)
				{
					if (BOTUnFork(&np) > -1)
					{
						carr_1024 xcar;
						xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
						xc = Output(cli, true, xcar.carr, 2, 0);
						xc = ClearVecEle(MTX_PRC, np.lid, false);
					}
				}
			}
			else
			{
				if (!strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "ALL") || !strcmp(UCASE(vec_->at(1).arg.c_str()).c_str(), "0"))
				{
					bot_proc np;
					xc = 1;

					while (GetVecEle(&np, MTX_PRC, xc++, false) > -1)
					{
						if (BOTUnFork(&np) > -1)
						{
							carr_1024 xcar;
							xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
							xc = Output(cli, true, xcar.carr, 2, 0);
							xc = ClearVecEle(MTX_PRC, np.lid, false);
						}
					}
				}
				else
				{
					bot_proc np;
					xc = GetVecEle(&np, MTX_PRC, (sint)atoi(vec_->at(1).arg.c_str()), false);

					if (xc > -1)
					{
						if (BOTUnFork(&np) > -1)
						{
							carr_1024 xcar;
							xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
							xc = Output(cli, true, xcar.carr, 2, 0);
							xc = ClearVecEle(MTX_PRC, np.lid, false);
						}
					}
					else
					{
						slint nid = (slint)_atoi64(vec_->at(1).arg.c_str());
						xc = 0;

						while (GetVecEle(&np, MTX_PRC, xc++, false) > -1)
						{
							if (np.pid == nid)
							{
								if (BOTUnFork(&np) > -1)
								{
									carr_1024 xcar;
									xc = bot_sprintf(xcar.carr, xcar.siz, "closed process: '%s' pid: %li", np.anm.c_str(), np.pid);
									xc = Output(cli, true, xcar.carr, 2, 0);
									xc = ClearVecEle(MTX_PRC, np.lid, false);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: arg - path or id or pid" \
				"\nClose a spawned process");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 30:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 30", 2);
		}
		if (!vec_->empty())
		{
			std::string pstr;
			TINFO_M np;
			xc = 0;

			while (GetVecEle(&np, MTX_TTS, xc++) > -1)
			{
				bot_sprintfs(&pstr, false, "\n%s[%i] opt:%i", np.thread_name.c_str(), np.lid, np.opt);
			}

			xc = Output(cli, true, pstr.c_str(), 2, 0);
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\nList threads");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 31:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 31", 2);
		}
		if (!vec_->empty())
		{
			if (vec_->size() > 1)
			{
				if (bot_sisn(vec_->at(1).arg.c_str(), vec_->at(1).arg.length()))
				{
					xc = TestThreads((sint)atoi(vec_->at(1).arg.c_str()));
				}
			}
			else
			{
				xc = TestThreads(100);
			}

			xc = Output(cli, true, "Test Threads complete.", 2, 0);
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n(optional)1: num test threads (default=100)" \
				"\nTest threads");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 32:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 32", 2);
		}
		if (vec_->size() > 1)
		{
			xc = SignalThread((_char*)vec_->at(1).arg.c_str(), BOT_TSG_CLS);
		}
		else
		{
			carr_64 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: arg - lid or thread name" \
				"\nClose a thread");
			oc = Output(cli, true, xcar.carr, 2, 0);
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
		oc = Output(cli, true, xcar.carr, 2, 0);
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

			if (!ox)
			{
				ox = BOTCloseFile(&scp);
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
			oc = Output(cli, true, xcar.carr, 2, 0);
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
			carr_96 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\na: script name or id" \
				"\nAttempt to run script with a call to system(c_char*)");
			oc = Output(cli, true, xcar.carr, 2, 0);
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
	case 101:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 101", 2);
		}
		if (vec_->size() > 1)
		{
			xc = SType(vec_->at(1).arg.c_str());

			if (xc > -1)
			{
				bot_proc np;
				xc = GetVecEle(&np, MTX_PRC, 0, false);
				np.f = CREATE_NEW_CONSOLE;
				size_t ln = 6;

				for (size_t x = 1; x < vec_->size(); x++)
				{
					ln += (vec_->at(x).arg.length() + sizeof(_char));
				}

				if (ln && ln < 32768)
				{
					_char* cl = (_char*)malloc(ln);

					if (cl)
					{
						c_char* nm = "servp ";
						size_t xl = 6;
						memcpy((void*)&cl[0], (void*)nm, xl);
						_char trm = '\0';
						_char spc = ' ';
						for (size_t x = 1; x < vec_->size(); x++)
						{
							memcpy((void*)&cl[xl], (void*)vec_->at(x).arg.c_str(), vec_->at(x).arg.length());
							xl += vec_->at(x).arg.length();
							memcpy((void*)&cl[xl], (void*)&spc, sizeof(_char));
							xl += sizeof(_char);
						}
						memcpy((void*)&cl[ln - 1], (void*)&trm, sizeof(_char));
						xc = BOTFork(&np, cl);
						sllint rst = Rest(BOT_MILLI_REST * 100);
						free(cl);
					}
				}
			}
		}
		else
		{
			carr_512 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: protocol [ TCP ] || [ UDP ] || [ RAW ] || [ PGM ]" \
				"\n(optional) 2: port = 0-65535 (default=17776)" \
				"\n(optional) 3: duration [ 0 || I || i = Indefinite ] or [ 0-UINT_MAX seconds ] (default = i)" \
				"\n(optional) 4: timeout [ 0-600 seconds ] (default = 30)" \
				"\n(optional) 5: q [ 0 = 100 ] or [ 1-100 ] (default = 10)" \
				"\nStart a server process.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 102:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 102", 2);
		}
		if (vec_->size() == 2)
		{
			carr_256 ips;
			xc = 0;
			while (GetVecEle(&ips, MTX_CIPS, xc++, false) > -1)
			{
				std::vector<std::string> av;
				sint rc = ArgSep(&av, false, 0, bot_strlen(ips.carr), ips.carr, BOT_RTV_CHAR, ' ');

				if (rc > -1 && av.size() > 2)
				{
					rc = BOTNCon(av[0].c_str(), av[1].c_str(), atoi(av[2].c_str()));
				}
			}
		}
		else if (vec_->size() == 3)
		{
			sint inv = SType(vec_->at(3).arg.c_str());
			carr_256 ips;
			xc = 0;
			while (GetVecEle(&ips, MTX_CIPS, xc++, false) > -1)
			{
				std::vector<std::string> av;
				sint rc = ArgSep(&av, false, 0, bot_strlen(ips.carr), ips.carr, BOT_RTV_CHAR, ' ');

				if (rc > -1 && av.size() > 2 && atoi(av[2].c_str()) == inv)
				{
					rc = BOTNCon(av[0].c_str(), av[1].c_str(), inv);
				}
			}
		}
		else if (vec_->size() > 3)
		{
			sint inv = SType(vec_->at(3).arg.c_str());
			xc = BOTNCon(vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str(), inv);
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz, 
				"\n1: address" \
				"\n2: port = 0-65535" \
				"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ] " \
				"\nConnect to a server process.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 103:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 103", 2);
		}
		if (vec_->size() == 2)
		{
			carr_256 ips;
			xc = 0;
			while (GetVecEle(&ips, MTX_CIPS, xc++, false) > -1)
			{
				std::vector<std::string> av;
				sint rc = ArgSep(&av, false, 0, bot_strlen(ips.carr), ips.carr, BOT_RTV_CHAR, ' ');

				if (rc > -1 && av.size() > 2)
				{
					rc = BOTXNCon(av[0].c_str(), av[1].c_str(), atoi(av[2].c_str()));
				}
			}
		}
		else if (vec_->size() == 3)
		{
			sint inv = SType(vec_->at(3).arg.c_str());

			carr_256 ips;
			xc = 0;
			while (GetVecEle(&ips, MTX_CIPS, xc++, false) > -1)
			{
				std::vector<std::string> av;
				sint rc = ArgSep(&av, false, 0, bot_strlen(ips.carr), ips.carr, BOT_RTV_CHAR, ' ');

				if (rc > -1 && av.size() > 2 && atoi(av[2].c_str()) == inv)
				{
					rc = BOTXNCon(av[0].c_str(), av[1].c_str(), inv);
				}
			}
		}
		else if (vec_->size() > 3)
		{
			sint inv = SType(vec_->at(3).arg.c_str());
			xc = BOTXNCon(vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str(), inv);
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: all" \
				"\n--------" \
				"\n1: address" \
				"\n2: port = 0-65535" \
				"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ] " \
				"\nDisconnect from a server process.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 104:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 104", 2);
		}
		if (vec_->size() > 4)
		{
			bot_vblko oblk((_char)BOT_OP_VDAT);

			for (size_t x = 4; x < vec_->size(); x++)
			{
				if (bot_sisi(vec_->at(x).arg.c_str(), vec_->at(x).arg.length()))
				{
					sllint vali = (sllint)_atoi64(vec_->at(x).arg.c_str());
					xc = oblk.Add(0, BOT_RTV_SLLINT, vali, BOT_RTV_MAX);
				}
				else if (bot_sisf(vec_->at(x).arg.c_str(), vec_->at(x).arg.length()))
				{
					if (!strcmp(&vec_->at(x).arg[vec_->at(x).arg.length() - 1], "f"))
					{
						vec_->at(x).arg.pop_back();
					}
					float vali = (float)atof(vec_->at(x).arg.c_str());
					xc = oblk.Add(0, BOT_RTV_REAL, &vali, BOT_RTV_MAX);
				}
				else
				{
					xc = oblk.Add(0, BOT_RTV_STR, &vec_->at(x).arg, BOT_RTV_MAX);
				}
			}

			sint inv = SType(vec_->at(3).arg.c_str());
			xc = AddVPKO(inv, oblk.siz, oblk.blk, vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str());
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: address" \
				"\n2: port = 0-65535" \
				"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ] " \
				"\n4: data" \
				"\nSend var data to an address.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 105:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 105", 2);
		}
		if (vec_->size() > 4)
		{
			bot_vblko oblk((_char)BOT_OP_VDAT, vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str());

			for (size_t x = 4; x < vec_->size(); x++)
			{
				if (vec_->at(x).arg[0] == '$')
				{
					BOT_VAR_T var;
					xc = GVAR(vec_->at(x).arg.c_str(), BOT_RTV_VAR, &var);

					if (xc > -1)
					{
						xc = oblk.Add(0, BOT_RTV_VAR, &var, BOT_RTV_MAX);
					}
					else
					{
						carr_192 xcar;
						sint oc = bot_sprintf(xcar.carr, xcar.siz, "variable %s not found.", vec_->at(x).arg.c_str());
						oc = Output(cli, true, xcar.carr, 2, 0);
					}
				}
				else
				{
					if (bot_sisi(vec_->at(x).arg.c_str(), vec_->at(x).arg.length()))
					{
						sllint vali = (sllint)_atoi64(vec_->at(x).arg.c_str());
						xc = oblk.Add(0, BOT_RTV_SLLINT, vali, BOT_RTV_MAX);
					}
					else if (bot_sisf(vec_->at(x).arg.c_str(), vec_->at(x).arg.length()))
					{
						if (!strcmp(&vec_->at(x).arg[vec_->at(x).arg.length() - 1], "f"))
						{
							vec_->at(x).arg.pop_back();
						}
						float vali = (float)atof(vec_->at(x).arg.c_str());
						xc = oblk.Add(0, BOT_RTV_REAL, &vali, BOT_RTV_MAX);
					}
					else
					{
						xc = oblk.Add(0, BOT_RTV_STR, &vec_->at(x).arg, BOT_RTV_MAX);
					}
				}
			}
			if (xc > -1)
			{
				sint inv = SType(vec_->at(3).arg.c_str());

				if (inv > -1)
				{
					xc = AddSVPKO(inv, &oblk);
				}
			}
			else
			{
				carr_192 xcar;
				sint oc = bot_sprintf(xcar.carr, xcar.siz, "failed send to %s", vec_->at(1).arg.c_str());
				oc = Output(cli, true, xcar.carr, 2, 1, 0);
			}
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: address" \
				"\n2: port = 0-65535" \
				"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ] " \
				"\n4: data" \
				"\nSend sec data to an address.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 106:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 106", 2);
		}
		if (vec_->size() > 4)
		{
			for (size_t x = 4; x < vec_->size(); x++)
			{
				BOT_FILE_M nfile;
				
				if (vec_->at(x).arg[0] == '$')
				{
					bot_file_hdr hdr;
					xc = ArgRep((_char*)vec_->at(x).arg.c_str(), BOT_RTV_FHD, &hdr);

					if (xc < 0)
					{
						carr_192 xcar;
						sint oc = bot_sprintf(xcar.carr, xcar.siz, "variable %s not found.", vec_->at(x).arg.c_str());
						oc = Output(cli, true, xcar.carr, 2, 0);
					}
					xc = GetVecEle(&nfile, MTX_FO, hdr.fid);
				}
				else
				{
					nfile.Renew(vec_->at(4).arg.c_str(), "", "", BOT_FILE_READ, BOT_F_CON);
				}
				
				sint ox = -1;
				xc = BOTOpenFile(&nfile, &ox, true, false, false, true);

				if (xc > -1)
				{
					if (!ox)
					{
						ox = BOTCloseFile(&nfile);
					}
					sint stype = SType(vec_->at(3).arg.c_str());
					size_t lim = BOT_FILE_CHUNK * BOT_FILE_HCHUNK;
					size_t x = 0;
					sint ct = 0;
					bot_vblko* blkp = 0;

					for (size_t x = 0; x < nfile.dsiz; x += lim)
					{
						bot_file_hdr hdr(&nfile);
						bot_vblko oblk((_char)BOT_OP_VDAT, vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str(), 1);
						blkp = &oblk;

						if (x + lim > nfile.dsiz)
						{
							lim = (nfile.dsiz - 1) - x;
						}
						
						hdr.seq = ct++;
						BOT_FILE_CHK chk;
						xc = ChunkDat(nfile.datp, x, &lim, &hdr, &chk);

						if (xc > -1)
						{
							xc = PushToVec(&hdr, MTX_NET_FOUT, false, false, false);

							if (xc > -1)
							{
								xc = blkp->Add(0, BOT_RTV_FHD, &hdr, BOT_RTV_MAX);

								if (xc > -1)
								{
									BOT_FILE_CHK* p = &chk;

									while (p && blkp)
									{
										xc = blkp->AddBlk((_char)BOT_OP_VDAT, vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str(), 1);
										
										if (xc > -1)
										{
											blkp = blkp->nxt;
											xc = blkp->Add(0, BOT_RTV_FLC, p, BOT_RTV_MAX);
											p = p->nxt;
										}
									}
								}
								if (!hdr.rec.empty())
								{
									xc = blkp->AddBlk((_char)BOT_OP_VDAT, vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str(), 1);

									if (xc > -1)
									{
										blkp = blkp->nxt;
										hdr.rec.clear();
										xc = blkp->Add(0, BOT_RTV_FHD, &hdr, BOT_RTV_MAX);
										xc = AddSVPKO(stype, &oblk);
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: address" \
				"\n2: port = 0-65535" \
				"\n3: protocol [ TCP(default) ] || [ UDP ] || [ RAW ] || [ PGM ] " \
				"\n4: file location" \
				"\nSend sec file to an address.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 125:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 125", 2);
		}
		if (vec_->size() > 1)
		{
			if (vec_->size() > 2)
			{
				xc = BanIP(vec_->at(1).arg.c_str(), vec_->at(2).arg.c_str());

				if (xc > -1)
				{
					if (!xc)
					{
						carr_256 xcar;
						sint oc = bot_sprintf(xcar.carr, xcar.siz, "added ip (%s) to banned list.", vec_->at(1).arg.c_str());
						oc = Output(cli, true, xcar.carr, 2, 0);
					}
					else
					{

					}
				}
			}
			else
			{
				xc = BanIP(vec_->at(1).arg.c_str());

				if (xc > -1)
				{
					if (!xc)
					{
						carr_256 xcar;
						sint oc = bot_sprintf(xcar.carr, xcar.siz, "added ip (%s) to banned list.", vec_->at(1).arg.c_str());
						oc = Output(cli, true, xcar.carr, 2, 0);
					}
					else
					{
						carr_256 xcar;
						sint oc = bot_sprintf(xcar.carr, xcar.siz, "ip (%s) exists in banned list.", vec_->at(1).arg.c_str());
						oc = Output(cli, true, xcar.carr, 2, 0);
					}
				}
			}
		}
		else
		{
			carr_32 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: address" \
				"\nBan an address.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 126:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 126", 2);
		}
		if (vec_->size() > 1)
		{
			xc = UnbanIP(vec_->at(1).arg.c_str());

			if (xc > -1)
			{
				if (!xc)
				{
					carr_256 xcar;
					sint oc = bot_sprintf(xcar.carr, xcar.siz, "removed ip (%s) from banned list.", vec_->at(1).arg.c_str());
					oc = Output(cli, true, xcar.carr, 2, 0);
				}
				else
				{
					carr_256 xcar;
					sint oc = bot_sprintf(xcar.carr, xcar.siz, "ip (%s) not found in banned list.", vec_->at(1).arg.c_str());
					oc = Output(cli, true, xcar.carr, 2, 0);
				}
			}
		}
		else
		{
			carr_32 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: address" \
				"\nUnban an address.");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 107:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 107", 2);
		}
		std::vector<std::string> kvec;
		BOT_STMT t(false, 0, "litebot", "BIPS", 1, &kvec);
		xc = t.AddCol("ADR", "", true);
		xc = Query(&t, BOT_RTV_VSTR);

		if (xc > -1)
		{
			std::string str;

			for (size_t x = 0; x < kvec.size(); x++)
			{
				xc = bot_sprintfs(&str, false, "\n(%s)", kvec[x].c_str());
			}
			xc = Output(cli, true, str.c_str(), 2, 0);
		}
		break;
	}
	case 200:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 200", 2);
		}
		if (vec_->size() > 1)
		{
			bool tomem = false;

			if (vec_->size() > 2)
			{
				if (bot_sisn(vec_->at(2).arg.c_str(), vec_->at(2).arg.length()))
				{
					xc = atoi(vec_->at(2).arg.c_str());

					if (xc > 0)
					{
						tomem = true;
					}
				}
				else
				{
					if (!strcmp(UCASE(&vec_->at(2).arg[0]).c_str(), "T") || !strcmp(UCASE(&vec_->at(2).arg[0]).c_str(), "Y"))
					{
						tomem = true;
					}
				}
			}
			carr_6 rmp;
			carr_12 dat;
			carr_6 emp;
			carr_3 typ;
			std::string resp;
			carr_128 xcar;
			bool done = false;
			
			while (!done)
			{
				xc = Input("ramp: ", &resp);

				if (xc < 0)
				{
					return -1;
				}
				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() > 5)
				{
					xc = Output(cli, true, "Length exceeds 5 characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					done = true;
					while (resp.length() < 5)
					{
						resp.push_back(' ');
					}
					xc = bot_sprintf(rmp.carr, rmp.siz, "%s", resp.c_str());
				}
				else {}
			}

			resp.clear();
			bot_strclr(xcar.carr);
			done = false;

			while (!done)
			{
				xc = Input("type: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() != 2)
				{
					xc = Output(cli, true, "Incorrect format.", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					done = true;
					xc = bot_sprintf(typ.carr, typ.siz, "%s", resp.c_str());
				}
				else {}
			}
			resp.clear();
			bot_strclr(xcar.carr);
			done = false;

			while (!done)
			{
				xc = Input("emp: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (!bot_sisn(resp.c_str(), resp.length()))
				{
					xc = Output(cli, true, "Non numerical", 2, 0);
				}
				else if (resp.length() > 5)
				{
					xc = Output(cli, true, "Length exceeds 5 characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					done = true;
					xc = sprintf_s(emp.carr, emp.siz, "%05s", resp.c_str());
				}
				else {}
			}
			resp.clear();
			bot_strclr(xcar.carr);
			done = false;

			while (!done)
			{
				std::string datstr;
				xc = Input("date: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (bot_cstrlen(CPunc(resp.c_str()).c_str()) != 8)
				{
					xc = Output(cli, true, "incorrect format, use MMDDYYYY or YYYYMMDD or  MM/DD/YYYY", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					done = true;
					xc = bot_sprintf(dat.carr, dat.siz, "%s", CPunc(resp.c_str()).c_str());
				}
				else {}
			}
			resp.clear();
			bot_strclr(xcar.carr);
			BOT_FILE_M nfile(vec_->at(1).arg.c_str(), "txt", BOTPathS(BOT_LDSI_NM).c_str(), BOT_FILE_READ, BOT_F_CON);
			xc = GetVINs(&nfile, rmp.carr, emp.carr, dat.carr, typ.carr, tomem);
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: file name" \
				"\n(optional)2: init as list held in memory [1/0] || [True/False] || [Yes/No] Default:0" \
				"\nAdd Create a list of VINs in \\bot_lds\\ldso\\ from file in \\bot_lds\\ldsi\\");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 201:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 201", 2);
		}
		if (vec_->size() > 1)
		{
			bool isvar = (vec_->at(1).arg[0] == '$') ? true:false;
			carr_6 rmp, xrmp;
			carr_12 dat, xdat;
			carr_6 emp;
			carr_3 typ, xtyp;
			carr_2 ds, xds;
			std::string resp;
			carr_128 xcar;
			bool done = false;

			while (!done)
			{
				xc = Input("from set: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
					xc = bot_sprintf(ds.carr, ds.siz, "?");
					xc = bot_sprintf(xds.carr, xds.siz, "?");
				}
				else if (resp.length() > 1)
				{
					xc = Output(cli, true, "Length exceeds 1 characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					xc = bot_sprintf(ds.carr, ds.siz, "%s", resp.c_str());

					while (!done)
					{
						resp.clear();
						bot_strclr(xcar.carr);
						xc = Input("to set: ", &resp);

						if (xc < 0)
						{
							return -1;
						}

						if (resp.length() > 1)
						{
							xc = Output(cli, true, "Length exceeds 1 characters", 2, 0);
						}
						else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
						{
							return 0;
						}
						else if (!resp.empty())
						{
							xc = bot_sprintf(xds.carr, xds.siz, "%s", resp.c_str());
							done = true;
						}
						else {}
					}
				}
				else {}
			}
			
			resp.clear();
			bot_strclr(xcar.carr);
			done = false;

			while (!done)
			{
				xc = Input("from ramp: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
					xc = bot_sprintf(rmp.carr, rmp.siz, "?????");
					xc = bot_sprintf(xrmp.carr, xrmp.siz, "?????");
				}
				else if (resp.length() > 5)
				{
					xc = Output(cli, true, "Length exceeds 5 characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					while (resp.length() < 5)
					{
						resp.push_back('?');
					}
					xc = bot_sprintf(rmp.carr, rmp.siz, "%s", resp.c_str());

					while (!done)
					{
						resp.clear();
						bot_strclr(xcar.carr);
						xc = Input("to ramp: ", &resp);

						if (xc < 0)
						{
							return -1;
						}
						if (resp.length() > 5)
						{
							xc = Output(cli, true, "Length exceeds 5 characters", 2, 0);
						}
						else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
						{
							return 0;
						}
						else if (!resp.empty())
						{
							while (resp.length() < 5)
							{
								resp.push_back('?');
							}
							xc = bot_sprintf(xrmp.carr, xrmp.siz, "%s", resp.c_str());
							done = true;
						}
						else {}

					}
				}
				else {}
			}

			resp.clear();
			bot_strclr(xcar.carr);
			done = false;

			while (!done)
			{
				xc = Input("from type: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
					xc = bot_sprintf(typ.carr, typ.siz, "??");
					xc = bot_sprintf(xtyp.carr, xtyp.siz, "??");
				}
				else if (resp.length() != 2)
				{
					xc = Output(cli, true, "Incorrect format.", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					while (resp.length() < 2)
					{
						resp.push_back('?');
					}
					xc = bot_sprintf(typ.carr, typ.siz, "%s", resp.c_str());

					while (!done)
					{
						resp.clear();
						bot_strclr(xcar.carr);
						xc = Input("to type: ", &resp);

						if (xc < 0)
						{
							return -1;
						}

						if (resp.length() != 2)
						{
							xc = Output(cli, true, "Incorrect format.", 2, 0);
						}
						else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
						{
							return 0;
						}
						else if (!resp.empty())
						{
							while (resp.length() < 2)
							{
								resp.push_back('?');
							}
							xc = bot_sprintf(xtyp.carr, xtyp.siz, "%s", resp.c_str());
							done = true;
						}
						else {}
					}
				}
				else {}
			}
			resp.clear();
			bot_strclr(xcar.carr);

			if (!isvar)
			{
				done = false;

				while (!done)
				{
					xc = Input("from emp: ", &resp);

					if (xc < 0)
					{
						return -1;
					}

					if (resp.empty())
					{
						done = true;
						xc = bot_sprintf(ds.carr, ds.siz, "?????");
					}
					else if (resp.length() > 5)
					{
						xc = Output(cli, true, "Length exceeds 5 characters", 2, 0);
					}
					else if (!bot_sisn(resp.c_str(), resp.length()))
					{
						xc = Output(cli, true, "Value non numerical", 2, 0);
					}
					else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else if (!resp.empty())
					{
						xc = bot_sprintf(emp.carr, emp.siz, "%s", resp.c_str());
						bool done = false;

						while (!done)
						{
							resp.clear();
							bot_strclr(xcar.carr);
							xc = Input("to emp: ", &resp);

							if (xc > -1)
							{
								if (xc < 0)
								{
									return -1;
								}

								if (resp.length() > 5)
								{
									xc = Output(cli, true, "Length exceeds 5 characters", 2, 0);
								}
								else if (!bot_sisn(resp.c_str(), resp.length()))
								{
									xc = Output(cli, true, "Value non numerical", 2, 0);
								}
								else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
								{
									return 0;
								}
								else if (!resp.empty())
								{
									xc = bot_sprintf(emp.carr, emp.siz, "%s", resp.c_str());
									bool done = true;
								}
								else {}
							}
						}
					}
					else {}
				}
			}
			resp.clear();
			bot_strclr(xcar.carr);
			done = false;

			while (!done)
			{
				xc = Input("from date: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					xc = bot_sprintf(dat.carr, dat.siz, "????????");
					xc = bot_sprintf(xdat.carr, xdat.siz, "????????");
					done = true;
				}
				else if (bot_cstrlen(CPunc(resp.c_str()).c_str()) != 8)
				{
					xc = Output(cli, true, "incorrect format, use MMDDYYYY or YYYYMMDD or  MM/DD/YYYY", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					if (!strcmp(&resp[0], "2"))
					{
						xc = bot_sprintf(dat.carr, dat.siz, "%s", resp.c_str());
					}
					else
					{
						carr_6 adat, bdat;
						xc = bot_sprintf(adat.carr, adat.siz, "%s", resp.substr(4, 4).c_str());
						xc = bot_sprintf(bdat.carr, bdat.siz, "%s", resp.substr(0, 4).c_str());
						xc = bot_sprintf(dat.carr, dat.siz, "%s%s", adat.carr, bdat.carr);
					}

					while (!done)
					{
						resp.clear();
						bot_strclr(xcar.carr);
						xc = Input("to date: ", &resp);

						if (xc < 0)
						{
							return -1;
						}

						if (bot_cstrlen(CPunc(resp.c_str()).c_str()) != 8)
						{
							xc = Output(cli, true, "incorrect format, use MMDDYYYY or YYYYMMDD or  MM/DD/YYYY", 2, 0);
						}
						else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
						{
							return 0;
						}
						else if (!resp.empty())
						{
							if (!strcmp(&resp[0], "2"))
							{
								xc = bot_sprintf(xdat.carr, xdat.siz, "%s", CPunc(resp.c_str()).c_str());
							}
							else
							{
								carr_6 adat, bdat;
								xc = bot_sprintf(adat.carr, adat.siz, "%s", CPunc(resp.c_str()).substr(4, 4).c_str());
								xc = bot_sprintf(bdat.carr, bdat.siz, "%s", CPunc(resp.c_str()).substr(0, 4).c_str());
								xc = bot_sprintf(xdat.carr, xdat.siz, "%s%s", adat.carr, bdat.carr);
							}
							done = true;
						}
						else {}
					}
				}
				else {}
			}
			
			resp.clear();
			bot_strclr(xcar.carr);
			std::vector<std::string> vvec;

			if (!isvar)
			{
				BOT_FILE_M nfile(vec_->at(1).arg.c_str(), "txt", BOTPathS(BOT_LDSI_NM).c_str(), BOT_FILE_READ, BOT_F_CON);
				xc = GetVINs(&nfile, rmp.carr, emp.carr, dat.carr, typ.carr, true);
				xc = ArgSep(&vvec, false, 0, 0, vec_->at(1).arg.c_str(), BOT_RTV_CHAR, ' ');
			}
			else
			{
				xc = ArgRep((_char*)vec_->at(1).arg.c_str(), BOT_RTV_VSTR, &vvec);
			}
			if (xc > -1)
			{
				std::string fout;
				for (size_t x = 0; x < vvec.size(); x++)
				{
					xc = bot_sprintfs(&fout, false, "REN %s%s_%s%s%s*.* %s%s_%s%s%s*.*\r", ds.carr, rmp.carr, typ.carr, dat.carr, vvec[x].c_str(), xds.carr, xrmp.carr, xtyp.carr, xdat.carr, vvec[x].c_str());
				}

				carr_256 nn;
				xc = 0;
				sint ox = -1;
				sint ctx = 0;

				while (xc > -1)
				{
					ctx++;
					xc = bot_sprintf(nn.carr, nn.siz, "PhotoScript%s_%i", ses_date.carr, ctx);
					BOT_FILE_M nfile(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
					ox = -1;
					xc = BOTOpenFile(&nfile, &ox, false, false);

					if (!ox && xc > -1)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				BOT_FILE_M nfile(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
				ox = -1;
				xc = BOTOpenFile(&nfile, &ox, false, true);

				if (xc > -1)
				{
					xc = BOTFileOUT(&nfile, nfile.fst.e_loc, 0, false, BOT_RTV_STR, &fout, BOT_RTV_MAX);

					if (!ox)
					{
						ox = BOTCloseFile(&nfile);
					}
				}
			}
		}
		else
		{
			carr_192 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: file name" \
				"\nCreate a script to rename photos of VINs in \\bot_lds\\ldso\\ from variable <file name > if file name matches variable held in memory; else from file in \\bot_lds\\ldsi\\<file name>");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 202:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 202", 2);
		}
		if (vec_->size() > 1)
		{
			bool isvar = false;
			
			if (vec_->at(1).arg[0] == '$')
			{
				isvar = true;
			}
			BOT_STMT istm(false, -1, "vehicleadmin", "inspect", 1);
			BOT_STMT dstm(false, -1, "vehicleadmin", "damage", 1);
			carr_6 rmp, xrmp;
			carr_12 dat, xdat;
			carr_6 emp;
			carr_3 typ, xtyp;
			std::string resp;
			bool done = false;

			while (!done)
			{
				xc = Input("type: 0:SELECT 1:UPDATE 2:INSERT 3:CREATE 4:DELETE - ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() > 1)
				{
					xc = Output(cli, true, "Length exceeds 1 character", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					if (bot_sisn(resp.c_str(), resp.length()))
					{
						istm.it_type = atoi(resp.c_str());
						dstm.it_type = istm.it_type;
						done = true;
					}
					resp.clear();
				}
				else {}
			}

			switch (istm.it_type)
			{
			case 0:
			{
				done = false;
				while (!done)
				{
					xc = Input("From Columns:", &resp);
					xc = ArgSep(&istm.cols, false, 0, resp.length(), resp.c_str(), BOT_RTV_VCHAR, &msy.nrts_sep);
				}
				break;
			}
			case 1:
			{
				xc = Output(cli, true, "UPDATE vehicleadmin.inspect SET [a]=[b] WHERE ", 2, 0);
				xc = Input("a: 0:inspdate 1:insptype 2:ramp 3:empno - ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				sint coli = -1;

				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() > 1)
				{
					xc = Output(cli, true, "Length exceeds 1 characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					if (bot_sisn(resp.c_str(), resp.length()))
					{
						coli = atoi(resp.c_str());
						done = true;
					}
					resp.clear();
				}

				xc = Input("b: ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() > BOT_STRLEN_MAX)
				{
					xc = Output(cli, true, "Length exceeds max characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					if (!coli)
					{
						std::string dstr("to_date('");
						dstr.append(resp.c_str());
						dstr.append("','mm/dd/yyyy')");
						xc = istm.AddCol("inspdate", dstr.c_str());
						xc = dstm.AddCol("inspdate", dstr.c_str());
					}
					else if (coli == 1)
					{
						xc = istm.AddCol("insptype", EStr(resp.c_str()).c_str());
						xc = dstm.AddCol("insptype", EStr(resp.c_str()).c_str());
					}
					else if (coli == 2)
					{
						xc = istm.AddCol("ramp", EStr(resp.c_str()).c_str());
						xc = dstm.AddCol("ramp", EStr(resp.c_str()).c_str());
					}
					else if (coli == 3)
					{
						xc = istm.AddCol("empno", EStr(resp.c_str()).c_str());
					}
					else {}
					resp.clear();
				}

				xc = Input("conditions: 0:inspdate 1:insptype 2:ramp 3:empno - ", &resp);

				while (!resp.empty())
				{
					if (xc < 0)
					{
						return -1;
					}

					sint coli = -1;

					if (resp.length() > 1)
					{
						xc = Output(cli, true, "Length exceeds one characters", 2, 0);
						xc = Input("conditions: 0:inspdate 1:insptype 2:ramp 3:empno - ", &resp);
					}
					else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else
					{
						if (bot_sisn(resp.c_str(), resp.length()))
						{
							coli = atoi(resp.c_str());
							done = true;
						}
						resp.clear();
						xc = Input("value: ", &resp);

						if (!coli)
						{
							std::string dstr("to_date('");
							dstr.append(resp.c_str());
							dstr.append("','mm/dd/yyyy')");
							xc = istm.AddCond("AND", "inspdate", "=", dstr.c_str());
							xc = dstm.AddCond("AND", "inspdate", "=", dstr.c_str());
						}
						else if (coli == 1)
						{
							xc = istm.AddCond("AND", "insptype", "=", EStr(resp.c_str()).c_str());
							xc = dstm.AddCond("AND", "insptype", "=", EStr(resp.c_str()).c_str());
						}
						else if (coli == 2)
						{
							xc = istm.AddCond("AND", "ramp", "=", EStr(resp.c_str()).c_str());
							xc = dstm.AddCond("AND", "ramp", "=", EStr(resp.c_str()).c_str());
						}
						else if (coli == 3)
						{
							xc = istm.AddCond("AND", "empno", "=", EStr(resp.c_str()).c_str());
						}
						else {}
						resp.clear();
						xc = Input("conditions: 0:inspdate 1:insptype 2:ramp 3:empno - ", &resp);
					}
				}

				std::vector<std::string> vvec;
				std::string fout("\n(");

				if (!isvar)
				{
					BOT_FILE_M nfile(vec_->at(1).arg.c_str(), "txt", BOTPathS(BOT_LDSI_NM).c_str(), BOT_FILE_READ, BOT_F_CON);
					xc = GetVINs(&nfile, rmp.carr, emp.carr, dat.carr, typ.carr, true);
					xc = ArgSep(&vvec, false, 0, 0, vec_->at(1).arg.c_str(), BOT_RTV_CHAR, ' ');
				}
				else
				{
					xc = ArgRep((_char*)vec_->at(1).arg.c_str(), BOT_RTV_VSTR, &vvec);
				}

				if (xc > -1)
				{
					for (size_t x = 0; x < vvec.size(); x++)
					{
						fout.push_back('\n');
						std::string vstr;
						for (size_t y = 0; y < vvec[x].size(); y++)
						{
							vstr.push_back(vvec[x][y]);
						}
						fout.append(EStr(vstr.c_str()).c_str());
						fout.push_back(',');
					}
					fout.pop_back();
					fout.append("\n)");
					xc = istm.AddCond("AND", "vin", "IN", fout.c_str());
					xc = dstm.AddCond("AND", "vin", "IN", fout.c_str());
				}

				xc = BTS(&istm);
				xc = BTS(&dstm);
				carr_256 nn;
				xc = 0;
				sint ox = -1;
				sint ctx = 0;

				while (xc > -1)
				{
					ctx++;
					xc = bot_sprintf(nn.carr, nn.siz, "LDS_UPDATE_%s_%i", ses_date.carr, ctx);
					BOT_FILE_M nfile(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
					ox = -1;
					xc = BOTOpenFile(&nfile, &ox, false, false);

					if (!ox && xc > -1)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				BOT_FILE_M nfile(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
				ox = -1;
				xc = BOTOpenFile(&nfile, &ox, false, true);

				if (xc > -1)
				{
					xc = BOTFileOUT(&nfile, nfile.fst.e_loc, 0, false, BOT_RTV_STR, &istm.stmt, BOT_RTV_MAX);

					if (!ox)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				xc = 0;
				ctx = 0;

				while (xc > -1)
				{
					ctx++;
					xc = bot_sprintf(nn.carr, nn.siz, "LDS_DUPDATE_%s_%i", ses_date.carr, ctx);
					nfile.Renew(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
					ox = -1;
					xc = BOTOpenFile(&nfile, &ox, false, false);

					if (!ox && xc > -1)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				ox = -1;
				xc = BOTOpenFile(&nfile, &ox, false, true);

				if (xc > -1)
				{
					xc = BOTFileOUT(&nfile, nfile.fst.e_loc, 0, false, BOT_RTV_STR, &dstm.stmt, BOT_RTV_MAX);

					if (!ox)
					{
						ox = BOTCloseFile(&nfile);
					}
				}
				break;
			}
			case 4:
			{
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
			carr_256 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: file name or variable" \
				"\nCreate a statement to update inspections for VINs in \\bot_lds\\ldso\\ if 'is variable' from variable 'vins' held in memory; else from file in \\bot_lds\\ldsi\\<file name>;");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
		break;
	}
	case 203:
	{
		if (debug_lvl >= 1000 && debug_m)
		{
			sint oc = Output("Found BOTCOMMAND id 203", 2);
		}
		if (vec_->size() > 1)
		{
			bool isvar = false;

			if (vec_->at(1).arg[0] == '$')
			{
				isvar = true;
				xc = ArgRep((_char*)vec_->at(1).arg.c_str(), BOT_RTV_STR, &vec_->at(1).arg);
			}
			BOT_STMT istm(false, -1, "user_db", "user_table", 1);
			BOT_STMT dstm(false, -1, "user_db", "user_table", 1);
			carr_6 rmp, xrmp;
			carr_12 dat, xdat;
			carr_6 emp;
			carr_3 typ, xtyp;
			std::string resp;
			bool done = false;

			while (!done)
			{
				xc = Input("type: 0:SELECT 1:UPDATE 2:INSERT 3:CREATE 4:DELETE - ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() > BOT_STRLEN_MAX)
				{
					xc = Output(cli, true, "Length exceeds max character", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					if (bot_sisn(resp.c_str(), resp.length()))
					{
						istm.it_type = atoi(resp.c_str());
						dstm.it_type = istm.it_type;
						done = true;
					}
					resp.clear();
				}
				else {}
			}

			switch (istm.it_type)
			{
			case 0:
			{
				done = false;
				while (!done)
				{
					xc = Input("From Columns:", &resp);
					xc = ArgSep(&istm.cols, false, 0, resp.length(), resp.c_str(), BOT_RTV_VCHAR, &msy.nrts_sep);
				}
				break;
			}
			case 1:
			{
				xc = Output(cli, true, "UPDATE user_db.user_table SET [a]=[b] WHERE ", 2, 0);
				xc = Input("[a](column): ", &resp);

				if (xc < 0)
				{
					return -1;
				}

				if (resp.empty())
				{
					done = true;
				}
				else if (resp.length() > BOT_STRLEN_MAX)
				{
					xc = Output(cli, true, "Length exceeds max characters", 2, 0);
				}
				else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
				{
					return 0;
				}
				else if (!resp.empty())
				{
					std::string nresp;
					xc = Input("[b](value): ", &nresp);

					if (xc < 0)
					{
						return -1;
					}

					if (nresp.empty())
					{
						done = true;
					}
					else if (nresp.length() > BOT_STRLEN_MAX)
					{
						xc = Output(cli, true, "Length exceeds max characters", 2, 0);
					}
					else if (!strcmp(UCASE(nresp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else if (!nresp.empty())
					{
						xc = istm.AddCol(resp.c_str(), EStr(nresp.c_str()).c_str());
						xc = dstm.AddCol(resp.c_str(), EStr(nresp.c_str()).c_str());
					}
					else {}
				}

				resp.clear();
				xc = Input("WHERE column:", &resp);

				while (!resp.empty())
				{
					if (xc < 0)
					{
						return -1;
					}

					sint coli = -1;

					if (resp.length() > 1)
					{
						xc = Output(cli, true, "Length exceeds one characters", 2, 0);
						xc = Input("conditions: 0:inspdate 1:insptype 2:ramp 3:empno - ", &resp);
					}
					else if (!strcmp(UCASE(resp.c_str()).c_str(), "EXIT"))
					{
						return 0;
					}
					else
					{
						if (bot_sisn(resp.c_str(), resp.length()))
						{
							coli = atoi(resp.c_str());
							done = true;
						}
						std::string cresp;
						xc = Input("comparison: (=, !=, >, >=, <, <=)", &cresp);

						if (!cresp.empty())
						{
							std::string nresp;
							xc = Input("value: ", &nresp);

							if (!nresp.empty())
							{
								if (istm.conds.empty())
								{
									xc = istm.AddCond("", resp.c_str(), cresp.c_str(), nresp.c_str());
								}
								else
								{
									xc = istm.AddCond("AND", resp.c_str(), cresp.c_str(), nresp.c_str());
								}
								xc = dstm.AddCond("AND", resp.c_str(), cresp.c_str(), nresp.c_str());
							}
							
						}
						resp.clear();
						xc = Input("WHERE column:", &resp);
					}
				}
				std::string fout("\n(");

				if (!vec_->at(1).arg.empty())
				{
					std::vector<std::string> vvec;
					xc = ArgSep(&vvec, false, 0, 0, vec_->at(1).arg.c_str(), BOT_RTV_CHAR, ' ');

					if (xc > -1)
					{
						for (size_t x = 0; x < vvec.size(); x++)
						{
							fout.push_back('\n');
							std::string vstr;
							for (size_t y = 0; y < vvec[x].size(); y++)
							{
								vstr.push_back(vvec[x][y]);
							}
							fout.append(EStr(vstr.c_str()).c_str());
							fout.push_back(',');
						}
						fout.pop_back();
						fout.append("\n)");
						xc = istm.AddCond("AND", "vin", "IN", fout.c_str());
						xc = dstm.AddCond("AND", "vin", "IN", fout.c_str());
					}
				}
				xc = BTS(&istm);
				xc = BTS(&dstm);
				carr_256 nn;
				xc = 0;
				sint ox = -1;
				sint ctx = 0;

				while (xc > -1)
				{
					ctx++;
					xc = bot_sprintf(nn.carr, nn.siz, "LDS_UPDATE_%s_%i", ses_date.carr, ctx);
					BOT_FILE_M nfile(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
					ox = -1;
					xc = BOTOpenFile(&nfile, &ox, false, false);

					if (!ox && xc > -1)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				BOT_FILE_M nfile(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
				ox = -1;
				xc = BOTOpenFile(&nfile, &ox, false, true);

				if (xc > -1)
				{
					xc = BOTFileOUT(&nfile, nfile.fst.e_loc, 0, false, BOT_RTV_STR, &istm.stmt, BOT_RTV_MAX);

					if (!ox)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				xc = 0;
				ctx = 0;

				while (xc > -1)
				{
					ctx++;
					xc = bot_sprintf(nn.carr, nn.siz, "LDS_DUPDATE_%s_%i", ses_date.carr, ctx);
					nfile.Renew(nn.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
					ox = -1;
					xc = BOTOpenFile(&nfile, &ox, false, false);

					if (!ox && xc > -1)
					{
						ox = BOTCloseFile(&nfile);
					}
				}

				ox = -1;
				xc = BOTOpenFile(&nfile, &ox, false, true);

				if (xc > -1)
				{
					xc = BOTFileOUT(&nfile, nfile.fst.e_loc, 0, false, BOT_RTV_STR, &dstm.stmt, BOT_RTV_MAX);

					if (!ox)
					{
						ox = BOTCloseFile(&nfile);
					}
				}
				break;
			}
			case 4:
			{
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
			carr_256 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz,
				"\n1: file name or variable" \
				"\nCreate a statement to update inspections for VINs in \\bot_lds\\ldso\\ if 'is variable' from variable 'vins' held in memory; else from file in \\bot_lds\\ldsi\\<file name>;");
			oc = Output(cli, true, xcar.carr, 2, 0);
		}
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
				xp = Output(cli, true, ncar.carr, 2, 0);
				return -1;
			}
			if (!bot_sisn(vec_->at(3).arg.c_str(), vec_->at(3).arg.length()))
			{
				carr_128 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "Command Priv(%s) invalid", vec_->at(3).arg.c_str());
				xp = Output(cli, true, ncar.carr, 2, 0);
				return -1;
			}
			
			sint ox = (sint)atoi(vec_->at(3).arg.c_str());

			if (ox > xc)
			{
				carr_128 ncar;
				sint xp = bot_sprintf(ncar.carr, ncar.siz, "Command Priv(%i) exceeds User Priv(%i)", ox, xc);
				xp = Output(cli, true, ncar.carr, 2, 0);
				return -1;
			}

			ox = (sint)atoi(vec_->at(2).arg.c_str());

			if (ox > 999)
			{
				return -1;
			}

			BOTCOMMAND Cmd("", ox);
			xc = GetCommand(cli, &Cmd);

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
			xc = GetCommand(cli, &Cmd);

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
					xc = Output(cli, true, xcar.carr, 2, 0);
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
					xc = Output(cli, true, xcar.carr, 2, 0);
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
					xc = Output(cli, true, xcar.carr, 2, 0);
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
					xc = BOTOpenFile(&hfile, &ox, false, false, false, true);

					if (xc < 0)
					{
						BOT_FILE_M xfile("litebot", ".cpp", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
						sint nx = -1;
						xc = BOTOpenFile(&xfile, &nx, false, false, false, true);

						if (xc > -1)
						{
							xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

							if (!nx)
							{
								nx = BOTCloseFile(&xfile, true, false, true);
							}

							hfile.lid = -1;
							xc = BOTOpenFile(&hfile, &ox, false, false, false, true);
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
									if (ct)
									{
										xc = BOTFindInFile(&hfile, true, lcrsa.t + 1, hfile.dsiz - 1, lcara.carr, bot_strlen(lcara.carr));

										if (xc > -1)
										{
											xc = hfile.GetCrs(&lcrsa);
										}
									}

									sint rc = 4;

									while (rc > -1 && rc < 1000)
									{
										if (rc > 4)
										{
											xc = hfile.GetCrs(&crs);

											
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
															scar.append(");\n\t\t\toc = Output(cli, true, xcar.carr, 2, 0);\n");
															scar.append(fstr.c_str());
															scar.append("\t}\n");
														}

														scar.append(fstr.c_str());
														scar.append("\tbreak;\n");
														scar.append(fstr.c_str());
														scar.append("}\n");
														scar.append(fstr.c_str());
														xc = BOTFileOUT(&hfile, crs.f, 0, true, BOT_RTV_STR, &scar, BOT_RTV_MAX);
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
															scar.append(");\n\t\t\toc = Output(cli, true, xcar.carr, 2, 0);\n");
															scar.append(fstr.c_str());
															scar.append("\t}\n");
														}
														xc = BOTFileOUT(&hfile, ncs.f + 1, 0, true, BOT_RTV_STR, &scar, BOT_RTV_MAX);
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
					xc = BOTOpenFile(&hfile, &ox, false, false, false, true);

					if (xc < 0)
					{
						BOT_FILE_M xfile("litebot", ".h", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
						sint nx = -1;
						xc = BOTOpenFile(&xfile, &nx, false, false, false, true);

						if (xc > -1)
						{
							xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

							if (!nx)
							{
								nx = BOTCloseFile(&xfile, true, false, true);
							}

							hfile.lid = -1;
							xc = BOTOpenFile(&hfile, &ox, false, false, false, true);
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
							xc = BOTFileOUT(&hfile, crs.t + 1, 0, true, BOT_RTV_BLOB, ocar.carr, BOT_RTV_MAX);
						}

						xc = BOTSaveFile(&hfile, 0, true);

						if (!ox)
						{
							ox = BOTCloseFile(&hfile, true, false, true);
						}
					}

					xc = bot_sprintf(xcar.carr, xcar.siz, "Command: \"%s\" ID: %s added", UCASE(vec_->at(1).arg.c_str()).c_str(), vec_->at(2).arg.c_str());
					xc = Output(cli, true, xcar.carr, 2, 0);
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
			oc = Output(cli, true, xcar.carr, 2, 0);
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
						xc = GetCommand(cli, &Cmd);

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
					xc = GetCommand(cli, &Cmd);

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
						xc = BOTOpenFile(&hfile, &ox, false, false, false, true);

						if (xc < 0)
						{
							BOT_FILE_M xfile("litebot", ".h", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
							sint nx = -1;
							xc = BOTOpenFile(&xfile, &nx, false, false, false, true);

							if (xc > -1)
							{
								xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

								if (!nx)
								{
									nx = BOTCloseFile(&xfile, true, false, true);
								}

								hfile.lid = -1;
								xc = BOTOpenFile(&hfile, &ox, false, false, false, true);
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
						xc = BOTOpenFile(&hfile, &ox, false, false, false, true);

						if (xc < 0)
						{
							BOT_FILE_M xfile("litebot", ".cpp", BOTPathS().c_str(), BOT_FILE_INS, BOT_F_CON, -1, lid);
							sint nx = -1;
							xc = BOTOpenFile(&xfile, &nx, false, false, false, true);

							if (xc > -1)
							{
								xc = BOTSaveFile(&xfile, BOTPathS(BOT_MOD_NM).c_str());

								if (!nx)
								{
									nx = BOTCloseFile(&xfile, true, false, true);
								}

								hfile.lid = -1;
								xc = BOTOpenFile(&hfile, &ox, false, false, false, true);
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
						xc = Output(cli, true, xcar.carr, 2, 0);
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
			oc = Output(cli, true, xcar.carr, 2, 0);
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
	case BOT_RTV_BLOB:
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
	case BOT_RTV_BLOB:
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
sint machine::ArgRep(_char* arg, sint rett, void* ret)
{
	if (debug_lvl >= 650 && debug_m)
	{
		carr_128 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::ArgRep(_char* arg(%i), sint rett, void* ret(%i))", (sint)arg, rett, (sint)ret);
		oc = Output(ncar.carr, 2);
	}
	if (!arg || !ret)
	{
		return -1;
	}

	sint xc = -1;

	switch (rett)
	{
	case BOT_RTV_FHD:
	{
		bot_file_hdr hdr;
		xc = GVAR(arg, rett, &hdr);
	}
	default:
	{
		xc = GVAR(arg, rett, ret);
		break;
	}
	}
	return xc;
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
	xc = BOTOpenFile(&ndir, &of, false, true);

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

							ndir.Renew("", "", BOTPathS(BOT_LDSI_NM).c_str(), 0, BOT_DIR_CON);
							of = -1;
							p = BOTOpenFile(&ndir, &of, false, true);

							if (p > -1)
							{
								if (!of)
								{
									BOTCloseFile(&ndir);
								}
							}

							ndir.Renew("", "", BOTPathS(BOT_LDSO_NM).c_str(), 0, BOT_DIR_CON);
							of = -1;
							p = BOTOpenFile(&ndir, &of, false, true);

							if (p > -1)
							{
								if (!of)
								{
									BOTCloseFile(&ndir);
								}
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
sint machine::BOTDirSep(BOT_FILE_M* val_)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_64 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTDirSep(BOT_FILE_M *val_(%i))", (sint)val_);
		oc = Output(ncar.carr, 2);
	}

	if (!val_)
	{
		return -1;
	}

	if (val_->name.empty() && val_->type.empty() && !val_->path.empty())
	{
		bool swt = false;
		_char cmp[3]{ '.','\\','\0' };

		for (sint x = (sint)val_->path.length() - 1; x > -1; x--)
		{
			if (!memcmp((void*)&val_->path[x], (void*)&cmp[0], sizeof(_char)))
			{
				val_->type.append(val_->path.substr((size_t)x + 1, val_->path.length() - ((size_t)x + 1)));
				val_->path.erase((size_t)x + 1, val_->path.length() - 1);

				for (x--; x > -1; x--)
				{
					if (!memcmp((void*)&val_->path[x], (void*)&cmp[1], sizeof(_char)))
					{
						val_->name.append(val_->path.substr((size_t)x + 1, val_->path.length() - ((size_t)x + 1)));
						val_->path.erase((size_t)x + 1, val_->path.length() - 1);
						return 0;
					}
				}
			}
			else if (!memcmp((void*)&val_->path[x], (void*)&cmp[1], sizeof(_char)))
			{
				val_->name.append(val_->path.substr((size_t)x + 1, val_->path.length() - ((size_t)x + 1)));
				val_->path.erase((size_t)x + 1, val_->path.length() - 1);
				return 0;
			}
			else {}
		}
	}
	return 0;
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

	sint xc = BOTDirSep(val_);

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
		xc = SetVecEleMem((void*)&val_->cm, MTX_FO, val_->lid, BOT_FS_CM, false);
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
	case BOT_DIR_CON:
	{
		return -1;
		break;
	}
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
		break;
	}
	case BOT_EXE_CON:
	{
		return -1;
		break;
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
					for (sint siz = 0; siz < (sint)BOT_FS_LIM; siz++)
					{
						sint xh = HasLock(MTX_FCON, siz, false);

						if (xh < 0)
						{
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
								siz = (sint)BOT_FS_LIM;
							}
						}
					}

					if (!h)
					{
						h = UnlockGMutex(MTX_FCON);
					}
				}
				mt--;
				if (mt > -1)
				{
					rst = nsRest((sllint)BOT_FO_REST);
				}
			}
			break;
		}
		case BOT_EXE_CON:
		{
			ret = 0;
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
sint machine::GetFPad(BOT_FILE_M* val_, slint mt)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_96 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::GetFPad(BOT_FILE_M *val_(%i)), sllint mt(%li))", (sint)val_, mt);
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
	if (val_->fpad > -1)
	{
		return val_->fpad;
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

	sllint rst = -1;

	while (mt > -1)
	{
		sint h = -1;
		ret = LockGMutex(MTX_FPAD, &h);

		if (ret > -1)
		{
			for (sint siz = 0; siz < (sint)BOT_FPAD_MAX; siz++)
			{
				sint xh = -1;
				ret = LockElement(MTX_FPAD, siz, &xh, false, false);

				if (!ret)
				{
					val_->fpad = siz;
					mt = -1;
					siz = (sint)BOT_FPAD_MAX;
				}
			}

			if (!h)
			{
				h = UnlockGMutex(MTX_FPAD);
			}
		}
		mt--;

		if (mt > -1)
		{
			rst = nsRest((sllint)BOT_FO_REST);
		}
	}
	return ret;
}
sint machine::CloseFPad(BOT_FILE_M* xfile_)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_96 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::CloseFPad(BOT_FILE_M *xfile_(%i))", (sint)xfile_);
		oc = Output(ncar.carr, 2);
	}

	if (!xfile_)
	{
		return -1;
	}

	sint xret = UnlockElement(MTX_FPAD, xfile_->fpad, false);
	sint hx = -1;
	xret = SetVecEleMem((void*)&hx, MTX_FO, xfile_->lid, BOT_FS_FPAD, false);
	return xret;
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
				//f_con[file_->fcon]->fstrm.close();
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

						sint xret = HasLock(MTX_FO, file_->lid, false);

						if (xret > -1)
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

							xret = HasLock(MTX_FO, file_->lid, false);

							if (xret > -1)
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
					ret = BOTOpenFile(&dirf, &of, false, true);

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
						if (!of)
						{
							of = BOTCloseFile(&dirf);
						}
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
sint machine::BOTNewFile(BOT_FILE_M* file_, bool overw, _char* argv)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_72 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTNewFile(BOT_FILE_M* file_(%i), bool overw(%u), _char* argv(%i))", (sint)file_, (uint)overw, (sint)argv);
		oc = Output(ncar.carr, 2);
	}

	if (!file_)
	{
		return -1;
	}

	if (file_->cm < 0)
	{
		sint gc = BOTConnMethod(file_);
	}

	if (file_->cm != BOT_DIR_CON)
	{
		sint fc = GetFPad(file_);

		if (fc < 0)
		{
			return -1;
		}
	}

	BOT_FILE nfile(file_->name.c_str(), file_->type.c_str(), file_->path.c_str(), file_->omode, file_->cm, -1, lid, -1, file_->encode);
	nfile.fpad = file_->fpad;
	sint gc = PushToVec((void*)&nfile, MTX_FO, true, true, false);

	if (argv)
	{
		size_t ln = bot_strlen(argv) + 1;
		
		/*if (nfile.Alloc(ln + 1))
		{
			_char trm = '\0';
			memcpy((void*)nfile.dat, (void*)argv, ln);
			memcpy((void*)&nfile.dat[nfile.dsiz], (void*)&trm, ln);
		}*/
		if (fileo_vec.dvec[nfile.lid].Alloc(ln + 1))
		{
			_char trm = '\0';
			memcpy((void*)&fileo_vec.dvec[nfile.lid].dat[0], (void*)argv, ln);
			memcpy((void*)&fileo_vec.dvec[nfile.lid].dat[ln], (void*)&trm, sizeof(_char));
		}
	}

	if (gc < 0)
	{
		return -1;
	}

	gc = GetVecEle((void*)file_, MTX_FO, nfile.lid);

	if (gc < 0)
	{
		return -1;
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
	return file_->lid;
}
sint machine::BOTOpenFile(sint flid, sint *was_open, bool do_scan, bool cine, bool r_to_st, bool dtp, _char* dat_, void* blk)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenFile(sint flid(%i), sint *was_open(%i), bool do_scan(%u), bool cine(%u), bool r_to_st(%u), bool dtp(%u),  _char* dat_(%i), void* blk(%i))", flid, (sint)was_open, (uint)do_scan, (uint)cine, (uint)r_to_st, (uint)dtp, (sint)dat_, (sint)blk);
		oc = Output(ncar.carr, 2);
	}

	BOT_FILE_M nf;
	sint gc = GetVecEle((void*)&nf, MTX_FO, flid);

	if (gc < 0)
	{
		return -1;
	}
	return BOTOpenFile(&nf, was_open, cine, r_to_st, dtp, dat_);
}
sint machine::BOTOpenFile(BOT_FILE_M* mfile_, sint *was_open, bool do_scan, bool cine, bool r_to_st, bool dtp, _char* dat_, void* blk)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTOpenFile(BOT_FILE_M* mfile_(%i), sint *was_open(%i), bool do_scan(%u), bool cine(%u), bool r_to_st(%u), bool dtp(%u),_char* dat_(%i), void* blk(%i))", (sint)mfile_, (sint)was_open, (uint)do_scan, (uint)cine, (uint)r_to_st, (uint)dtp, (sint)dat_, (sint)blk);
		oc = Output(ncar.carr, 2);
	}

	if (!mfile_ || !was_open)
	{
		return -10;
	}

	sint xh = mfile_->omode;
	sint gc = -1;

	if (mfile_->lid < 0)
	{
		gc = GetInVec((void*)mfile_, MTX_FO);
	}
	else
	{
		gc = GetVecEle((void*)mfile_, MTX_FO, mfile_->lid);
	}

	if (mfile_->omode != xh)
	{
		mfile_->omode = xh;

		if (mfile_->lid > -1)
		{
			gc = SetVecEleMem(&mfile_->omode, MTX_FO, mfile_->lid, BOT_FS_OMODE, false);
		}
	}

	if (gc < 0)
	{
		gc = BOTNewFile(mfile_, dtp, dat_);

		if (gc < 0)
		{
			return -1;
		}
	}

	gc = BOTFileStats(mfile_, do_scan);
	xh = -1;
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
				if (!cine)
				{
					if (dtp)
					{
						sint ox = -1;
						sint hx = LockGMutex(MTX_FO, &ox);

						if (hx > -1)
						{
							if (fileo_vec.dvec[mfile_->lid].Alloc(mfile_->fst.filestats.st_size + 1))
							{
								mfile_->Renew(&fileo_vec.dvec[mfile_->lid]);
								gc = SetVecEle((void*)mfile_, MTX_FO, mfile_->lid);
								gc = BOTFileIN(mfile_, false, 0, mfile_->fst.filestats.st_size, BOT_RTV_BLOB, fileo_vec.dvec[mfile_->lid].dat, BOT_RTV_MAX);
							}

							if (!ox)
							{
								ox = UnlockGMutex(MTX_FO);
							}
						}
					}
				}
			}
			break;
		}
		case BOT_EXE_CON:
		{
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

	if (!file_ || !f_ || !len || len > (size_t)BOT_FILESIZE_MAX)
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
						ret = BOTFileIN(file_, false, f, t, BOT_RTV_BLOB, &n, BOT_RTV_MAX);
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
sint machine::BOTFileOUT(BOT_FILE_M* file_, size_t f, size_t t, bool to_fdat, ...)
{
	if (debug_lvl >= 600 && debug_m)
	{
		carr_192 ncar;
		sint oc = bot_sprintf(ncar.carr, ncar.siz, "::BOTFileOUT(BOT_FILE_M* file_(%i), size_t f(%u), size_t t(%u), bool to_fdat(%u), ...)", (sint)file_, f, t, (uint)to_fdat);
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
					case BOT_RTV_BLOB:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_)
						{
							if (!t || t <= f)
							{
								t = bot_strlen(val_);
							}
							for (size_t x = 0; x < t - f; x++)
							{
								std::cout.put(val_[x]);
							}
							file_->fst.oa_loc += (t - f);
							ret = 0;
						}
						break;
					}
					case BOT_RTV_CCHAR:
					{
						c_char* val_ = va_arg(args, c_char*);

						if (val_)
						{
							if (!t || t <= f)
							{
								t = bot_cstrlen(val_);
							}
							for (size_t x = 0; x < t - f; x++)
							{
								std::cout.put(val_[x]);
							}
							file_->fst.oa_loc += (t - f);
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

			if (file_->fcon < 0)
			{
				ret = GetOFConn(file_, &ox);

				if (ret < 0)
				{
					ret = BOTOpenFile(file_, &ox);
				}
			}
			if (file_->fcon > -1)
			{
				boto_file = true;
				sint ud = UpdMTXPrio();
				bool done = false;

				if (f > (size_t)file_->fst.filestats.st_size)
				{
					_char val = ' ';
					f_con[file_->fcon]->fstrm.seekp(file_->fst.filestats.st_size);

					while ((size_t)f_con[file_->fcon]->fstrm.tellp() < f)
					{
						f_con[file_->fcon]->fstrm.put(val);
					}
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
							
							if (!t || t <= f)
							{
								t = f + bot_ustrlen(val);
							}

							for (size_t x = 0; x < t - f; x++)
							{
								f_con[file_->fcon]->fstrm.put(val[x]);
							}
							file_->fst.oa_loc = (size_t)f_con[file_->fcon]->fstrm.tellp();
							ret = 0;
						}
						break;
					}
					case BOT_RTV_BLOB:
					{
						_char* val_ = va_arg(args, _char*);

						if (val_)
						{
							if (!t || t <= f)
							{
								t = f + bot_strlen(val_);
							}
							for (size_t x = 0; x < t - f; x++)
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
							if (!t || t <= f)
							{
								t = f + bot_cstrlen(op_);
							}

							for (size_t x = 0; x < t - f; x++)
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
							if (!str->empty() && str->length() < BOT_FILESIZE_MAX)
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
									if (strvec->at(siz).length() < BOT_FILESIZE_MAX)
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
						size_t osiz = bot_cstrlen(op_);

						if (osiz && osiz < BOT_FILESIZE_MAX)
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
						if (fileo_vec.dvec[file_->lid].Alloc(file_->dsiz + sizeof(uint)))
						{
							uint val_ = va_arg(args, uint);
							uint xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], sizeof(uint));
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)&val_, sizeof(uint));

							for (size_t x = f + 1; x < fileo_vec.dvec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], sizeof(uint));
								memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&xval, sizeof(uint));
								memcpy((void*)&xval, (void*)&val_, sizeof(uint));
							}
							uint term = (uint)'\0';
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(uint));
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
						if (fileo_vec.dvec[file_->lid].Alloc(file_->dsiz + sizeof(u_char)))
						{
							uint val_ = va_arg(args, uint);
							u_char val = (u_char)val_;
							u_char xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], sizeof(u_char));
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)&val_, sizeof(u_char));

							for (size_t x = f + 1; x < fileo_vec.dvec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], sizeof(u_char));
								memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&xval, sizeof(u_char));
								memcpy((void*)&xval, (void*)&val_, sizeof(u_char));
							}
							u_char term = (u_char)'\0';
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(u_char));
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
						if (fileo_vec.dvec[file_->lid].Alloc(file_->dsiz + sizeof(sint)))
						{
							sint val_ = va_arg(args, sint);
							sint xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], sizeof(sint));
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)&val_, sizeof(sint));

							for (size_t x = f + 1; x < fileo_vec.dvec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], sizeof(sint));
								memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&xval, sizeof(sint));
								memcpy((void*)&xval, (void*)&val_, sizeof(sint));
							}
							sint term = (sint)'\0';
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(sint));
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
						if (fileo_vec.dvec[file_->lid].Alloc(file_->dsiz + sizeof(_char)))
						{
							sint val_ = va_arg(args, sint);
							_char val = (_char)val_;
							_char xval = 0;
							memcpy((void*)&xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], sizeof(_char));
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)&val_, sizeof(_char));

							for (size_t x = f + 1; x < fileo_vec.dvec[file_->lid].dsiz; x++)
							{
								memcpy((void*)&val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], sizeof(_char));
								memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&xval, sizeof(_char));
								memcpy((void*)&xval, (void*)&val_, sizeof(_char));
							}
							_char term = '\0';
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
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
						size_t nt = 0;

						if (!t || t <= f)
						{
							nt = bot_ustrlen(val_);
						}
						else
						{
							nt = t - f;
						}

						if (file_->omode == BOT_FILE_OVRL)
						{
							if (f + nt > fileo_vec.dvec[file_->lid].dsiz - 1)
							{
								if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + ((f + nt) - fileo_vec.dvec[file_->lid].dsiz)))
								{
									ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									size_t x = f;

									while (x < (f + nt))
									{
										if (memcmp((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char)))
										{
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char));
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
									if (memcmp((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char)))
									{
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(u_char));
									}
									x++;
								}
							}
							u_char term = (u_char)'\0';
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(u_char));
						}
						else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
						{
							size_t osiz = fileo_vec.dvec[file_->lid].dsiz;

							if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + nt))
							{
								u_char* xval = (u_char*)malloc(nt + 1);

								if (xval)
								{
									ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									memcpy((void*)xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], nt);
									memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)val_, nt);
									u_char term = (u_char)'\0';
									memcpy((void*)&xval[nt], (void*)&term, sizeof(u_char));
									size_t x = f + nt;

									while (x + nt < fileo_vec.dvec[file_->lid].dsiz)
									{
										memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], nt);
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, nt);
										memcpy((void*)xval, (void*)val_, nt);
										x += nt;
									}

									if (x < fileo_vec.dvec[file_->lid].dsiz)
									{
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, fileo_vec.dvec[file_->lid].dsiz - x);
									}

									memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(u_char));
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
				case BOT_RTV_BLOB:
				{
					_char* val_ = va_arg(args, _char*);

					if (val_)
					{
						size_t nt = 0;

						if (!t || t <= f)
						{
							nt = bot_strlen(val_);
						}
						else
						{
							nt = t - f;
						}

						if (file_->omode == BOT_FILE_OVRL)
						{
							if (f + nt > fileo_vec.dvec[file_->lid].dsiz - 1)
							{
								if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + ((f + nt) - fileo_vec.dvec[file_->lid].dsiz)))
								{
									ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									size_t x = f;

									while (x < (f + nt))
									{
										if (memcmp((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char)))
										{
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char));
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
									if (memcmp((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char)))
									{
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&val_[x - f], sizeof(_char));
									}
									x++;
								}
							}
							_char term = '\0';
							memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
						}
						else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
						{
							size_t osiz = fileo_vec.dvec[file_->lid].dsiz;

							if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + nt))
							{
								_char* xval = (_char*)malloc(nt + 1);

								if (xval)
								{
									ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									memcpy((void*)xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], nt);
									memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)val_, nt);
									_char term = '\0';
									memcpy((void*)&xval[nt], (void*)&term, sizeof(_char));
									size_t x = f + nt;

									while (x + nt < fileo_vec.dvec[file_->lid].dsiz)
									{
										memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], nt);
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, nt);
										memcpy((void*)xval, (void*)val_, nt);
										x += nt;
									}

									if (x < fileo_vec.dvec[file_->lid].dsiz)
									{
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, nt);
									}

									memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
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
								if (f + str->length() > fileo_vec.dvec[file_->lid].dsiz - 1)
								{
									if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + ((f + str->length()) - fileo_vec.dvec[file_->lid].dsiz)))
									{
										ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
										size_t x = f;

										while (x < (f + str->length()))
										{
											if (memcmp((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char)))
											{
												memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char));
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
										if (memcmp((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char)))
										{
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)&str[x - f], sizeof(_char));
										}
										x++;
									}
								}
								_char term = '\0';
								memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
							}
							else if (file_->omode == BOT_FILE_APND || file_->omode == BOT_FILE_INS)
							{
								size_t osiz = fileo_vec.dvec[file_->lid].dsiz;

								if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + str->length()))
								{
									ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
									_char* val_ = (_char*)malloc(str->length() + 1);
									_char* xval = (_char*)malloc(str->length() + 1);

									if (val_ && xval)
									{
										_char term = '\0';
										memcpy((void*)xval, (void*)&fileo_vec.dvec[file_->lid].dat[f], str->length());
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[f], (void*)str->c_str(), str->length());
										memcpy((void*)&val_[str->length()], (void*)&term, sizeof(_char));
										memcpy((void*)&xval[str->length()], (void*)&term, sizeof(_char));
										size_t x = f + str->length();

										while (x + str->length() < fileo_vec.dvec[file_->lid].dsiz)
										{
											memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], str->length());
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, str->length());
											memcpy((void*)xval, (void*)val_, str->length());
											x += str->length();
										}

										if (x < fileo_vec.dvec[file_->lid].dsiz)
										{
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, fileo_vec.dvec[file_->lid].dsiz - x);
										}

										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
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
								tot += strvec->at(siz).length();
							}

							if (BOT_FILE_OVRL)
							{
								if (f + tot < file_->dsiz)
								{
									size_t x = f;

									for (size_t siz = 0; siz < strvec->size(); siz++)
									{
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)strvec->at(siz).c_str(), strvec->at(siz).length());
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
								if (fileo_vec.dvec[file_->lid].Alloc(fileo_vec.dvec[file_->lid].dsiz + tot))
								{
									ud = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
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
											memcpy((void*)xval[x - f], (void*)&fileo_vec.dvec[file_->lid].dat[x], strvec->at(siz).length());
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)strvec->at(siz).c_str(), strvec->at(siz).length());
											x += strvec->at(siz).length();
											strvec->at(siz).clear();
										}

										while (x + tot < fileo_vec.dvec[file_->lid].dsiz)
										{
											memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[x], tot);
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, tot);
											memcpy((void*)xval, (void*)val_, tot);
											x += tot;
										}

										if (x < file_->dsiz)
										{
											memcpy((void*)&fileo_vec.dvec[file_->lid].dat[x], (void*)xval, fileo_vec.dvec[file_->lid].dsiz - x);
										}
										memcpy((void*)&fileo_vec.dvec[file_->lid].dat[fileo_vec.dvec[file_->lid].dsiz - 1], (void*)&term, sizeof(_char));
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
				sint xret = SetVecEleMem(fileo_vec.dvec[file_->lid].dat, MTX_FO, file_->lid, BOT_FS_DATP);
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
					case BOT_RTV_BLOB:
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
					case BOT_RTV_BLOB:
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

							while (f_con[file_->fcon]->fstrm.get(xc) && str_->length() < (size_t)BOT_FILESIZE_MAX)
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

							while (f_con[file_->fcon]->fstrm.get(xc) && nstr.length() < (size_t)BOT_FILESIZE_MAX)
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
							memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[ct], sizeof(sint));
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
							memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[ct], sizeof(_char));
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
							memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[ct], sizeof(uint));
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
							memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[ct], sizeof(u_char));
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
							memcpy((void*)val_, (void*)&fileo_vec.dvec[file_->lid].dat[ct], sizeof(float));
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
						for (ullint ct = from; ct < to - from && ct < BOT_FILESIZE_MAX; ct++)
						{
							str_->push_back(fileo_vec.dvec[file_->lid].dat[ct]);
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
							val_->push_back((sint)fileo_vec.dvec[file_->lid].dat[ct]);
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
							val_->push_back(fileo_vec.dvec[file_->lid].dat[ct]);
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
							val_->push_back((uint)fileo_vec.dvec[file_->lid].dat[ct]);
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
							val_->push_back((u_char)fileo_vec.dvec[file_->lid].dat[ct]);
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
							memcpy((void*)&nc, (void*)&fileo_vec.dvec[file_->lid].dat[ct], sizeof(float));
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
						for (ullint ct = from; ct < to - from && nstr.length() < BOT_FILESIZE_MAX && strvec_->size() < BOTVEC_LIM; ct++)
						{
							nstr.push_back(fileo_vec.dvec[file_->lid].dat[ct]);
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

				if (fileo_vec.dvec[file_->lid].Alloc(file_->dsiz - (to - from)))
				{
					ret = SetVecEleMem((void*)&fileo_vec.dvec[file_->lid].dsiz, MTX_FO, file_->lid, BOT_FS_DSIZ, false);
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

	sint ret = CloseFPad(xfile_);

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
	else
	{
		ret = GetVecEle(xfile_, MTX_FO, xfile_->lid);
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
	ret = BOTOpenFile(&xfile, &ox, false, true);

	if (ret > -1)
	{
		if (file_->datp)
		{
			ret = BOTFileOUT(&xfile, 0, 0, false, BOT_RTV_BLOB, file_->datp, BOT_RTV_MAX);

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
					cheq = BOTCloseObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid); // returns fid as openmode

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
				sint cheq = BOTOpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);

				while (cheq < 0) // returns is_meta as wasopen, uses value set in fid by BOTCloseObject() as var arg option for openmode
				{
					cheq = BOTOpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);
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
					cheq = BOTCloseObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid); // returns fid as openmode

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
				sint cheq = BOTOpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);

				while (cheq < 0) // returns is_meta as wasopen, uses value set in fid by BOTCloseObject() as var arg option for openmode
				{
					cheq = BOTOpenObject(relocks[x].gmtx, relocks[x].ele, relocks[x].is_meta, &relocks[x].fid, &relocks[x].lid);
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
			//std::cout.put(np->at(x));
			fputc((sint)np->at(x), stdout);
		}
		if (!h)
		{
			h = UnlockGMutex(MTX_O);
		}
		return 0;
	}
	return -1;
}
sint machine::BOTNOutput(std::string* np, BOT_CLIENT_M* cli)
{
	if (!np)
	{
		return -1;
	}

	carr_16 rport;
	bot_sprintf(rport.carr, rport.siz, "%i", cli->prt.rport);
	bot_vblko oblk((_char)BOT_OP_MSG, cli->prt.oipstr.carr, rport.carr, 1);
	sint xc = oblk.Add(0, BOT_RTV_STR, np, BOT_RTV_MAX);

	if (xc > -1)
	{
		xc = AddSVPKO(SOCK_DGRAM, &oblk);
	}
	return -1;
}
sint machine::BOTNOutput(std::string* np, std::vector<BOT_CLIENT_M>* cliv)
{
	if (!np || !cliv)
	{
		return -1;
	}
	if (cliv->empty())
	{
		return -2;
	}

	sint xc = -1;
	carr_16 rport;
	bot_sprintf(rport.carr, rport.siz, "%i", cliv->at(0).prt.rport);
	bot_vblko oblk((_char)BOT_OP_MSG, cliv->at(0).prt.oipstr.carr, rport.carr, 1);
	xc = oblk.Add(0, BOT_RTV_STR, np, BOT_RTV_MAX);

	for (size_t x = 1; x < cliv->size(); x++)
	{
		bot_sprintf(rport.carr, rport.siz, "%i", cliv->at(x).prt.rport);

		if (strcmp(cliv->at(x).prt.oipstr.carr, oblk.addr.carr) || strcmp(rport.carr, oblk.servc.carr))
		{
			oblk.AddBlk((_char)BOT_OP_MSG, cliv->at(x).prt.oipstr.carr, rport.carr, 1);
		}
		else
		{
			xc = oblk.Add(0, BOT_RTV_STR, np, BOT_RTV_MAX);
		}
	}

	if (xc > -1)
	{
		xc = AddSVPKO(SOCK_DGRAM, &oblk);
	}
	return -1;
}
sint machine::Output(c_char* op_, sint opt, bool newl, BOT_CLIENT_M* cli)
{
	carr_64 tdata;
	sint xc = BOTTimeMS(tdata.carr, tdata.siz);
	carr_256 instr;
	std::string str;
	BOT_CLIENT_M ncli;

	if (!cli)
	{
		xc = GetPCli(&ncli);
	}
	else
	{
		ncli.Renew(cli);
	}

	if (newl)
	{
		str.push_back('\n');
	}

	if (ncli.priv > 99)
	{
		xc = bot_sprintfs(&str, false, "%s [%i][%s] ", tdata.carr, lid, ptn.c_str());
	}
	else
	{
		xc = bot_sprintfs(&str, false, "%s [%i][machine] ", tdata.carr, lid);
	}

	if (op_)
	{
		str.append(op_);
	}

	if (opt > -1)
	{
		if (opt == 1)
		{
			xc = 1;
		}

		xc = LogPut(str.c_str(), opt);

		if (!opt)
		{
			if (ncli.atcons)
			{
				sint h = -1;
				sint y = LockGMutex(MTX_I, &h, false);

				if (y > -1)
				{
					if (!h)
					{
						h = UnlockGMutex(MTX_I);
					}
				}
				if (y < 0)
				{
					if (ncli.priv > 99)
					{
						xc = bot_sprintfs(&str, false, "\n%s [%i][%s] : ", tdata.carr, lid, ptn.c_str());
					}
					else
					{
						xc = bot_sprintfs(&str, false, "\n%s [%i][machine] : ", tdata.carr, lid);
					}
				}
				xc = BOTCOutput(&str);
			}
			else
			{
				xc = BOTNOutput(&str, &ncli);
			}
		}
	}
	return xc;
}
sint machine::Output(BOT_CLIENT_M* cli, bool newl, c_char* op_, ...)
{
	carr_64 tdata;
	sint xc = BOTTimeMS(tdata.carr, tdata.siz);
	carr_256 instr;
	BOT_CLIENT_M ncli;

	if (!cli)
	{
		xc = GetPCli(&ncli);
	}
	else
	{
		ncli.Renew(cli);
	}

	std::string str;

	if (newl)
	{
		str.push_back('\n');
	}

	if (ncli.priv > 99)
	{
		xc = bot_sprintfs(&str, false, "%s [%i][%s] ", tdata.carr, lid, ptn.c_str());
	}
	else
	{
		xc = bot_sprintfs(&str, false, "%s [%i][machine] ", tdata.carr, lid);
	}
	
	if (op_)
	{
		str.append(op_);
	}

	va_list args;
	va_start(args, op_);

	for (sint x = 0; x < (sint)BOT_OUT_OPTS; x++)
	{
		sint rc = va_arg(args, sint);

		if (rc < 0 || rc >(sint)BOT_OUT_OPTS)
		{
			x = (sint)BOT_OUT_OPTS;
		}
		else
		{
			if (rc == 1)
			{
				xc = 1;
			}

			xc = LogPut(str.c_str(), rc);

			if (rc < 1)
			{
				if (!rc)
				{
					if (ncli.atcons)
					{
						sint h = -1;
						sint y = LockGMutex(MTX_I, &h, false);

						if (y > -1)
						{
							if (!h)
							{
								h = UnlockGMutex(MTX_I);
							}
						}
						if (y < 0)
						{
							if (ncli.priv > 99)
							{
								xc = bot_sprintfs(&str, false, "\n%s [%i][ConsoleThread] : ", tdata.carr, lid, ptn.c_str());
							}
							else
							{
								xc = bot_sprintfs(&str, false, "\n%s [%i][machine] : ", tdata.carr, lid);
							}
						}
						rc = BOTCOutput(&str);
					}
					else
					{
						rc = BOTNOutput(&str, &ncli);
					}
				}
				x = (sint)BOT_OUT_OPTS;
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
	sint p = LockGMutex(MTX_I, &h);

	if (p > -1)
	{
		sllint rst = 0;
		sint chk = '\n';
		sint rhk = '\r';
		sint spc = ' ';
		sint x = -1;
		sint rc = -1;

		while (x > -2 && np->length() < (size_t)BOT_STRLEN_MAX)
		{
			rc = getc(stdin);
			//rc = std::cin.get();

			if (rc)
			{
				if (x < 0)
				{
					if (!memcmp((void*)&bot_strt_s.nrts_term[0], (void*)&rc, sizeof(sint)) || !memcmp((void*)&chk, (void*)&rc, sizeof(sint)) || !memcmp((void*)&rhk, (void*)&rc, sizeof(sint)))
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
					if (!memcmp((void*)&chk, (void*)&rc, sizeof(sint)) || !memcmp((void*)&rhk, (void*)&rc, sizeof(sint)) || !memcmp((void*)&bot_strt_s.nrts_term[0], (void*)&rc, sizeof(sint)))
					{
						x = -2;
					}
					else
					{
						np->push_back(rc);
					}
				}
				else {}
			}
		}

		x = BOTTimeMS(tdata->carr, tdata->siz);

		if (!h)
		{
			h = UnlockGMutex(MTX_I);
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

	BOT_CLIENT_M cli;
	sint ret = GetPCli(&cli);
	ret = UNRTS();
	std::vector<std::string> args;
	std::vector<BOT_ARG> vec;
	carr_64 tdata;
	ret = vtool.CombV(&args, VTV_VSTR, VTV_VCHAR, &msy.nrts_sep, /*VTV_VCHAR, &msy.nrts_lit, VTV_VCHAR, &msy.nrts_ord, VTV_VCHAR, &msy.nrts_ord_,*/ VTV_MAX);

	if (prp)
	{
		sint op = Output(&cli, true, prp, 2, 0);
	}

	sint x = BOTCInput(np, &tdata);

	if (np->length() > 1)
	{
		if (!strcmp(np->substr(0, 2).c_str(), "/#"))
		{
			ret = ArgSep(&vec, false, 0, np->length() - 1, np->c_str(), BOT_RTV_VSTR, &args);
			np->clear();
			ret = Command(&cli, &vec);
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

	vec.clear();

	if (cli.name.empty())
	{
		if (cli.lid > -1)
		{
			x = GetVecEleMem((void*)&cli.name, MTX_CV, cli.lid, BOT_C_NAME);
		}
	}

	std::string str;
	x = bot_sprintfs(&str, false, "%s [%i][%s] %s", tdata.carr, lid, cli.name.c_str(), np->c_str());
	x = LogPut(str.c_str(), 0);
	x = LogPut(str.c_str(), 2);
	str.clear();
	bot_strclr(tdata.carr);
	return ret;
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

	for (sint x = nstr.find("'", 0); x > -1; x = nstr.find("'", x + 1))
	{
		nstr.at(x) = '"';
	}
	s.append("'");
	s.append(nstr.c_str());
	nstr.clear();
	s.append("'");

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

	if (t_->it_type == 1)
	{
		if (t_->act < 0)
		{
			t_->act = 0;
		}
		if (t_->spec < 0)
		{
			t_->spec = 0;
		}
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
		else
		{
			statement.append(t_->dbname);
			statement.append(".");
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
						sllint xc = BOTCentSec();
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
						sllint xc = BOTCentSec();
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
				statement.append(" \n");
				statement.append(msy.sql_spec_keywords[t_->spec].c_str());

				for (uint x = 0; x < t_->conds.size(); x++)
				{
					statement.append(" \n");
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

	bool began = false;
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

						if (pend_->at(i).it_type > 0)
						{
							if (!began)
							{
								BOT_STMT beg(pend_->at(i).maint, -1, pend_->at(i).dbname.c_str());
								beg.stmt.append("BEGIN;");
								dx = vtool.AVTV(&com_->t, &beg, false, false);
								began = true;
							}
						}
						else if (!pend_->at(i).it_type)
						{
							if (began)
							{
								BOT_STMT beg(pend_->at(i).maint, -1, pend_->at(i).dbname.c_str());
								beg.stmt.append("COMMIT;");
								dx = vtool.AVTV(&com_->t, &beg, false, false);
								began = false;
							}
						}
						else {}

						sint nx = vtool.AVTV(&cont_names[cont_names.size() - 1], &pend_->at(i).cont, true, false);
						//dx = BTS(&stmts_->at(i));

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
					//dx = BTS(&stmts_->at(i));

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

					if (stmts_->at(i).it_type > 0)
					{
						if (!began)
						{
							BOT_STMT beg(stmts_->at(i).maint, -1, stmts_->at(i).dbname.c_str());
							beg.stmt.append("BEGIN;");
							dx = vtool.AVTV(&com_->t, &beg, false, false);
							began = true;
						}
					}
					else if (!stmts_->at(i).it_type)
					{
						if (began)
						{
							BOT_STMT beg(stmts_->at(i).maint, -1, stmts_->at(i).dbname.c_str());
							beg.stmt.append("COMMIT;");
							dx = vtool.AVTV(&com_->t, &beg, false, false);
							began = false;
						}
					}
					else {}

					sint nx = vtool.AVTV(&cont_names[cont_names.size() - 1], &stmts_->at(i).cont, true, false);
					//dx = BTS(&stmts_->at(i));

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
				//dx = BTS(&stmts_->at(i));

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
		//xc = BTS(&trans);
		xc = vtool.AVTV(&com_->t, &trans, true, false);

		for (size_t c = 0; c < cont_names[i].size(); c++)
		{
			trans.Clear();
			trans.Renew((bool)db_maint[i], 8, com_->dbs[i].name.c_str(), cont_names[i][c].c_str(), 1);
			//xc = BTS(&trans);
			xc = vtool.AVTV(&com_->an, &trans, true, false);
		}
	}
	if (began)
	{
		BOT_STMT beg(false, -1, com_->dbs[0].name.c_str());
		beg.stmt.append("COMMIT;");
		sint dx = vtool.AVTV(&com_->t, &beg, false, false);
		began = false;
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
					sint xh = HasLock(MTX_DBC, siz, false);

					if (xh < 0)
					{
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
					xc = Output(0, true, GetError().c_str(), 1, 2, -1);

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
				bool fdone = false;

				while (!fdone)
				{
					rc = sqlite3_prepare_v2(d_con_->db_, bstmt.carr, (sint)strlen(bstmt.carr), &ppstmt, &tail);

					if (rc == SQLITE_BUSY)
					{
						sllint rst = Rest(BOT_MILLI_REST);
					}
					else if (rc)
					{
						fdone = true;
						d_con_->o_com = false;
						rc = UpdMTXPrio();
						xc = Output(0, true, GetError().c_str(), 1, 2, -1);

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
					else
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
								fdone = done = true;
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
								fdone = done = true;
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
								xc = Output(0, true, GetError().c_str(), 1, 2, -1);
								fdone = done = true;
								break;
							}
							}
						}
						rc = FinStmt(&ppstmt);
					}
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
		bool fdone = false;

		while (!fdone)
		{
			xc = sqlite3_prepare_v2(d_con_->db_, bstmt.carr, (sint)strlen(bstmt.carr), &ppstmt, &tail);

			if (xc == SQLITE_BUSY)
			{
				sllint rst = Rest(BOT_MILLI_REST);
			}
			else if (xc)
			{
				xc = Output(0, true, GetError().c_str(), 1, 2, -1);
				fdone = true;
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
						xc = Output(0, true, GetError().c_str(), 1, 2, -1);
						done = true;
						break;
					}
					}
				}
				xc = FinStmt(&ppstmt);
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
					xc = Output(0, true, GetError().c_str(), 1, 2, -1);
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
							xc = Output(0, true, "Error CloseDBConn()", 1, 2, -1);
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
	if (debug_lvl >= 500 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::Query(BOT_COMMIT* qval_(%i), sint as_opt(%i))", (sint)qval_, as_opt);
		op = Output(outp.carr, 2);
	}

	if (!qval_ || as_opt < 0)
	{
		return -1;
	}

	if (qval_->dbname.empty())
	{
		if (!qval_->stmt.empty())
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
	sint ret = GetInVec((void*)&dbs, MTX_DBL, false);

	if (ret < 0)
	{
		return -1;
	}

	sint of = -1;
	sint hdb = -1;
	ret = OpenDB(&dbs, 1, &hdb, &of);

	if (ret > -1)
	{
		d_con_->o_com = true;
		ret = UpdMTXPrio();
		c_char* tail;
		sqlite3_stmt* ppstmt;
		bool fdone = false;

		while (!fdone)
		{
			ret = sqlite3_prepare_v2(d_con_->db_, qval_->stmt.c_str(), (sint)qval_->stmt.length(), &ppstmt, &tail);

			if (ret == SQLITE_BUSY)
			{
				sllint rst = Rest(BOT_MILLI_REST);
			}
			else if (ret)
			{
				ret = Output(0, true, GetError().c_str(), 1, 2, -1);
				fdone = true;
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
						if (debug_lvl >= 500 && debug_m)
						{
							ret = Output("SQLITE_OK", 2);
						}
						fdone = done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 500 && debug_m)
						{
							ret = Output("SQLITE_DONE", 2);
						}
						fdone = done = true;
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 500 && debug_m)
						{
							ret = Output("SQLITE_ROW", 2);
						}

						if (qval_->fcols.empty())
						{
							std::vector<std::string> tbls;
							ret = GetVecEleMem((void*)&tbls, MTX_DBL, dbs.lid, BOT_DB_TABLES, false);

							for (size_t z = 0; z < tbls.size(); z++)
							{
								if (!strcmp(tbls[z].c_str(), qval_->cont.c_str()))
								{
									std::vector<std::vector<std::vector<std::string>>> ncols;
									ret = GetVecEleMem((void*)&ncols, MTX_DBL, dbs.lid, BOT_DB_COLUMNS, false);

									for (uint i = 0; i < ncols[z][0].size(); i++)
									{
										qval_->fcols.push_back(ncols[z][0][i]);
									}
								}
							}
						}

						switch (as_opt)
						{
						case BOT_RTV_SINT:
						{
							sint* inv = reinterpret_cast<sint*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									*inv = sqlite3_column_int(ppstmt, ret);
								}
								else if (ct == SQLITE_FLOAT)
								{
									*inv = (sint)sqlite3_column_double(ppstmt, ret);
								}
								else if (ct == SQLITE_TEXT)
								{
									*inv = atoi(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret)));
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (xret == sizeof(sint))
									{
										memcpy((void*)inv, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), sizeof(sint));
									}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_REAL:
						{
							float* inv = reinterpret_cast<float*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									*inv = (float)sqlite3_column_int(ppstmt, ret);
								}
								else if (ct == SQLITE_FLOAT)
								{
									*inv = (float)sqlite3_column_double(ppstmt, ret);
								}
								else if (ct == SQLITE_TEXT)
								{
									*inv = (float)atof(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret)));
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (xret == sizeof(float))
									{
										memcpy((void*)inv, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), sizeof(float));
									}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_STR:
						{
							std::string* inv = reinterpret_cast<std::string*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									bot_itoa(sqlite3_column_int(ppstmt, ret), inv);
								}
								else if (ct == SQLITE_FLOAT)
								{
									bot_dtoa(sqlite3_column_double(ppstmt, ret), inv);
								}
								else if (ct == SQLITE_TEXT)
								{
									inv->append(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret)));
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									u_char* nuchar = (u_char*)malloc(xret);
								
									if (nuchar)
									{
										memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
										u_char trm = (u_char)'\0';

										for (sint nx = 0; nx < xret; nx++)
										{
											ret = bot_sprintfs(inv, false, "%02X ", nuchar[nx]);
										}
										free(nuchar);
									}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_BLOB:
						{
							_char* inv = reinterpret_cast<_char*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									ret = sqlite3_column_int(ppstmt, ret);
									memcpy((void*)inv, (void*)&ret, sizeof(sint));
								}
								else if (ct == SQLITE_FLOAT)
								{
									float nval = (float)sqlite3_column_double(ppstmt, ret);
									memcpy((void*)inv, (void*)&nval, sizeof(float));
								}
								else if (ct == SQLITE_TEXT)
								{
									memcpy((void*)inv, reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret)), xret);
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									memcpy((void*)inv, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
								}
								else {}
							}
							break;
						}
						case BOT_RTV_MICS:
						{
							u_char echar = (u_char)'\0';
							MICSYM* inv = reinterpret_cast<MICSYM*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										inv->id = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										inv->last_maintained = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										inv->last_maintained_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										inv->last_modified = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										inv->last_modified_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ENCODINGS"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, sizeof(u_char));

											for (sint fi = 0; fi < xret; fi++)
											{
												sint xi = vtool.AVTV(&inv->encodings, (uint)nuchar[fi], true, false);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "CONSTITUENT_TO"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char lsep = (u_char)' ';
											u_char sep = (u_char)',';
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<std::vector<u_char>> nvec;
											std::vector<u_char> uvec;

											for (sint usiz = 0; usiz < xret; usiz++)
											{
												if (!memcmp((void*)&nuchar[usiz], (void*)&sep, 1) && !nvec.empty())
												{
													inv->constituent_to.push_back(nvec);
													nvec.clear();
													usiz++;
												}
												else if (!memcmp((void*)&nuchar[usiz], (void*)&lsep, 1) && !uvec.empty())
												{
													sint xi = vtool.AVTV(&nvec, &uvec, true, false);
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
												inv->constituent_to.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_FOLLOWING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char sep = (u_char)',';
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_F> nvec;

											for (sint usiz = 0; (usiz + 1) < xret; usiz += 3)
											{
												if (!memcmp((void*)&nuchar[usiz], &sep, 1) && !nvec.empty())
												{
													inv->history_following.push_back(nvec);
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
												inv->history_following.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_PRECEEDING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char sep = (u_char)',';
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_P> nvec;

											for (sint usiz = 0; (usiz + 1) < xret; usiz += 3)
											{
												if (!memcmp((void*)&nuchar[usiz], &sep, 1) && !nvec.empty())
												{
													inv->history_preceeding.push_back(nvec);
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
												inv->history_preceeding.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else {}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_MACS:
						{
							u_char echar = (u_char)'\0';
							MACSYM* inv = reinterpret_cast<MACSYM*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										inv->id = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										inv->last_maintained = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										inv->last_maintained_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										inv->last_modified = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										inv->last_modified_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "USAGES"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);

											for (sint fi = 0; fi < xret; fi++)
											{
												sint xi = vtool.AVTV(&inv->usages, (uint)nuchar[fi], false, false);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "USED"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);

											for (sint fi = 0; fi < xret; fi++)
											{
												sint xi = vtool.AVTV(&inv->used, (uint)nuchar[fi], false, false);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_FOLLOWING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_FV> nvec;
											HIST_FV hf;
											u_char lsep = (u_char)' ';
											u_char sep = (u_char)',';

											for (sint csiz = 0; (csiz + 1) < xret; csiz++)
											{
												if (!memcmp(&nuchar[csiz], &sep, xret) && !nvec.empty())
												{
													hf.ct = (uint)nuchar[csiz - 1];
													nvec.push_back(hf);
													hf.cons.clear();
													hf.ct = 0;
													csiz++;
												}
												else if (memcmp(&nuchar[csiz], &lsep, sizeof(u_char)) && !nvec.empty())
												{
													inv->history_following.push_back(nvec);
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
												inv->history_following.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_PRECEEDING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_PV> nvec;
											HIST_PV hf;
											u_char lsep = (u_char)' ';
											u_char sep = (u_char)',';

											for (sint csiz = 0; (csiz + 1) < xret; csiz++)
											{
												if (!memcmp(&nuchar[csiz], &sep, xret) && !nvec.empty())
												{
													hf.ct = (uint)nuchar[csiz - 1];
													nvec.push_back(hf);
													hf.cons.clear();
													hf.ct = 0;
													csiz++;
												}
												else if (memcmp(&nuchar[csiz], &lsep, sizeof(u_char)) && !nvec.empty())
												{
													inv->history_preceeding.push_back(nvec);
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
												inv->history_preceeding.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else {}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_SCRPT:
						{
							bot_script* inv = reinterpret_cast<bot_script*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										inv->lid = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										inv->last_maint = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										inv->last_maint_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										inv->last_mod = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										inv->last_mod_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "MODE"))
									{
										inv->mode = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "ENCODING"))
									{
										inv->encoding = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "USED"))
									{
										inv->used = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED_BY"))
									{
										inv->lub = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "NAME"))
									{
										inv->name.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "TYPE"))
									{
										inv->type.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "DEST"))
									{
										inv->dest.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED"))
									{
										inv->lused.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else {}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_SES:
						{
							bot_session* inv = reinterpret_cast<bot_session*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										inv->id = sqlite3_column_int(ppstmt, ret);
									}
									if (!strcmp(qval_->fcols[iter].c_str(), "PID"))
									{
										inv->pid = sqlite3_column_int(ppstmt, ret);
									}
									if (!strcmp(qval_->fcols[iter].c_str(), "QUIT"))
									{
										inv->quit = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										inv->last_maint = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										inv->last_maint_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										inv->last_mod = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										inv->last_mod_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "NAME"))
									{
										bot_sprintf(inv->nm.carr, inv->nm.siz, "%s", reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_VAR:
						{
							BOT_VAR_T* inv = reinterpret_cast<BOT_VAR_T*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "VALUE"))
									{
										sllint xv = (sllint)sqlite3_column_int(ppstmt, ret);
										_char ov[sizeof(sllint)];
										memcpy((void*)&ov, (void*)&xv, sizeof(sllint));
										std::vector<_char> xvec;
										inv->v.clear();
										inv->v.push_back(xvec);

										for (size_t x = 0; x < sizeof(sllint); x++)
										{
											inv->v[0].push_back(ov[x]);
										}
									}
								}
								else if (ct == SQLITE_FLOAT)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "VALUE"))
									{
										float xv = (float)sqlite3_column_double(ppstmt, ret);
										_char ov[sizeof(float)];
										memcpy((void*)&ov, (void*)&xv, sizeof(float));
										std::vector<_char> xvec;
										inv->v.clear();
										inv->v.push_back(xvec);

										for (size_t x = 0; x < sizeof(float); x++)
										{
											inv->v[0].push_back(ov[x]);
										}
									}
								}
								else if (ct == SQLITE_TEXT)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "VALUE"))
									{
										size_t siz = sqlite3_column_bytes(ppstmt, ret);
										c_char* xv = reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret));
										std::vector<_char> xvec;
										inv->v.clear();
										inv->v.push_back(xvec);

										for (size_t x = 0; x < siz; x++)
										{
											inv->v[0].push_back(xv[x]);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "ABSTR"))
									{
										size_t siz = sqlite3_column_bytes(ppstmt, ret);
										c_char* xv = reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret));
										bot_strclr(inv->n);
										inv->n = (_char*)malloc(siz + 1);

										if (inv->n)
										{
											inv->n[siz] = '0';
											bot_sprintf(inv->n, siz, "%s", xv);
										}
									}
									else {}
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "VALUE"))
									{
										size_t siz = sqlite3_column_bytes(ppstmt, ret);
										const u_char* xv = (const u_char*)malloc(siz + 1);

										if (xv)
										{
											xv = reinterpret_cast<const u_char*>(sqlite3_column_blob(ppstmt, ret));
											u_char trm = (u_char)'\0';
											memcpy((void*)&xv[siz], (void*)&trm, sizeof(u_char));
											std::vector<_char> xvec;
											inv->v.clear();
											inv->v.push_back(xvec);

											for (size_t x = 0; x < siz; x++)
											{
												inv->v[0].push_back(xv[x]);
											}
											free((void*)xv);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "WVALUE"))
									{
										size_t siz = sqlite3_column_bytes(ppstmt, ret);
										const u_char* xv = (const u_char*)malloc(siz + 1);

										if (xv)
										{
											xv = reinterpret_cast<const u_char*>(sqlite3_column_blob(ppstmt, ret));
											u_char trm = (u_char)'\0';
											memcpy((void*)&xv[siz], (void*)&trm, sizeof(u_char));
											std::vector<_char> xvec;
											inv->v.clear();
											inv->v.push_back(xvec);

											for (size_t x = 0; x < siz; x++)
											{
												inv->v[0].push_back(xv[x]);
											}
											free((void*)xv);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "WABSTR"))
									{
										size_t siz = sqlite3_column_bytes(ppstmt, ret);
										const u_char* xv = (const u_char*)malloc(siz + 1);

										if (xv)
										{
											xv = reinterpret_cast<const u_char*>(sqlite3_column_blob(ppstmt, ret));
											u_char trm = (u_char)'\0';
											memcpy((void*)&xv[siz], (void*)&trm, sizeof(u_char));
											std::vector<_char> xvec;
											inv->v.clear();
											inv->v.push_back(xvec);

											for (size_t x = 0; x < siz; x++)
											{
												inv->v[0].push_back(xv[x]);
											}
											free((void*)xv);
										}
									}
									else {}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_VSINT:
						{
							std::vector<sint>* inv = reinterpret_cast<std::vector<sint>*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									inv->push_back(sqlite3_column_int(ppstmt, ret));
								}
								else if (ct == SQLITE_FLOAT)
								{
									inv->push_back((sint)sqlite3_column_double(ppstmt, ret));
								}
								else if (ct == SQLITE_TEXT)
								{
									inv->push_back(atoi(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret))));
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (xret == sizeof(sint))
									{
										sint val;
										memcpy((void*)&val, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), sizeof(sint));
										inv->push_back(val);
									}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_VREAL:
						{
							std::vector<float>* inv = reinterpret_cast<std::vector<float>*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									inv->push_back((float)sqlite3_column_int(ppstmt, ret));
								}
								else if (ct == SQLITE_FLOAT)
								{
									inv->push_back((float)sqlite3_column_double(ppstmt, ret));
								}
								else if (ct == SQLITE_TEXT)
								{
									inv->push_back((float)atof(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret))));
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (xret == sizeof(float))
									{
										float val;
										memcpy((void*)&val, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), sizeof(float));
										inv->push_back(val);
									}
								}
								else {}
							}
							break;
						}
						case BOT_RTV_VSTR:
						{
							std::vector<std::string>* inv = reinterpret_cast<std::vector<std::string>*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);
								std::string val;

								if (ct == SQLITE_INTEGER)
								{
									bot_itoa(sqlite3_column_int(ppstmt, ret), &val);
								}
								else if (ct == SQLITE_FLOAT)
								{
									bot_dtoa(sqlite3_column_double(ppstmt, ret), &val);
								}
								else if (ct == SQLITE_TEXT)
								{
									val.append(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret)));
								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									u_char* nuchar = (u_char*)malloc(xret);

									if (nuchar)
									{
										memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
										u_char trm = (u_char)'\0';

										for (sint nx = 0; nx < xret; nx++)
										{
											ret = bot_sprintfs(&val, false, "%02X ", nuchar[nx]);
										}
										free(nuchar);
									}
								}
								else {}
								inv->push_back(val);
							}
							break;
						}
						case BOT_RTV_VBLOB:
						{
							std::vector<std::vector<_char>>* inv = reinterpret_cast<std::vector<std::vector<_char>>*>(qval_->rblk);

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);
								u_char* val = (u_char*)malloc(xret + 1);

								if (val)
								{
									size_t vsiz = inv->size();
									std::vector<_char> nvec;
									inv->push_back(nvec);

									if (ct == SQLITE_INTEGER)
									{
										ret = sqlite3_column_int(ppstmt, ret);
										memcpy((void*)val, (void*)&ret, sizeof(sint));

										for (sint siz = 0; siz < xret; siz++)
										{
											inv->at(vsiz).push_back(val[siz]);
										}
									}
									else if (ct == SQLITE_FLOAT)
									{
										float nval = (float)sqlite3_column_double(ppstmt, ret);
										memcpy((void*)val, (void*)&nval, sizeof(float));

										for (sint siz = 0; siz < xret; siz++)
										{
											inv->at(vsiz).push_back(val[siz]);
										}
									}
									else if (ct == SQLITE_TEXT)
									{
										memcpy((void*)val, reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, ret)), xret);

										for (sint siz = 0; siz < xret; siz++)
										{
											inv->at(vsiz).push_back(val[siz]);
										}
									}
									else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
									{
										memcpy((void*)val, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);

										for (sint siz = 0; siz < xret; siz++)
										{
											inv->at(vsiz).push_back(val[siz]);
										}
									}
									else {}
									free(val);
								}
							}
							break;
						}
						case BOT_RTV_VMICS:
						{
							u_char echar = (u_char)'\0';
							std::vector<MICSYM>* inv = reinterpret_cast<std::vector<MICSYM>*>(qval_->rblk);
							MICSYM val;

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										val.id = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										val.last_maintained = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										val.last_maintained_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										val.last_modified = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										val.last_modified_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ENCODINGS"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);

											for (sint fi = 0; fi < xret; fi++)
											{
												sint xi = vtool.AVTV(&val.encodings, (uint)nuchar[fi], true, false);
											}
										}
										free(nuchar);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "CONSTITUENT_TO"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char lsep = (u_char)' ';
											u_char sep = (u_char)',';
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<std::vector<u_char>> nvec;
											std::vector<u_char> uvec;

											for (sint usiz = 0; usiz < xret; usiz++)
											{
												if (!memcmp((void*)&nuchar[usiz], (void*)&sep, 1) && !nvec.empty())
												{
													val.constituent_to.push_back(nvec);
													nvec.clear();
													usiz++;
												}
												else if (!memcmp((void*)&nuchar[usiz], (void*)&lsep, 1) && !uvec.empty())
												{
													sint xi = vtool.AVTV(&nvec, &uvec, true, false);
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
												val.constituent_to.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_FOLLOWING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char sep = (u_char)',';
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_F> nvec;

											for (sint usiz = 0; (usiz + 1) < xret; usiz += 3)
											{
												if (!memcmp((void*)&nuchar[usiz], &sep, 1) && !nvec.empty())
												{
													val.history_following.push_back(nvec);
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
												val.history_following.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_PRECEEDING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											u_char sep = (u_char)',';
											memcpy((void*)nuchar, reinterpret_cast<const void*>(sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_P> nvec;

											for (sint usiz = 0; (usiz + 1) < xret; usiz += 3)
											{
												if (!memcmp((void*)&nuchar[usiz], &sep, 1) && !nvec.empty())
												{
													val.history_preceeding.push_back(nvec);
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
												val.history_preceeding.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else {}
								}
								else {}
							}
							inv->push_back(val);
							break;
						}
						case BOT_RTV_VMACS:
						{
							u_char echar = (u_char)'\0';
							std::vector<MACSYM>* inv = reinterpret_cast<std::vector<MACSYM>*>(qval_->rblk);
							MACSYM val;

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										val.id = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										val.last_maintained = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										val.last_maintained_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										val.last_modified = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										val.last_modified_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "USAGES"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);

											for (sint fi = 0; fi < xret; fi++)
											{
												sint xi = vtool.AVTV(&val.usages, (uint)nuchar[fi], false, false);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "USED"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);

											for (sint fi = 0; fi < xret; fi++)
											{
												sint xi = vtool.AVTV(&val.used, (uint)nuchar[fi], false, false);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_FOLLOWING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_FV> nvec;
											HIST_FV hf;
											u_char lsep = (u_char)' ';
											u_char sep = (u_char)',';

											for (sint csiz = 0; (csiz + 1) < xret; csiz++)
											{
												if (!memcmp(&nuchar[csiz], &sep, xret) && !nvec.empty())
												{
													hf.ct = (uint)nuchar[csiz - 1];
													nvec.push_back(hf);
													hf.cons.clear();
													hf.ct = 0;
													csiz++;
												}
												else if (memcmp(&nuchar[csiz], &lsep, sizeof(u_char)) && !nvec.empty())
												{
													val.history_following.push_back(nvec);
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
												val.history_following.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "HISTORY_PRECEEDING"))
									{
										u_char* nuchar = (u_char*)malloc(xret + 1);

										if (nuchar)
										{
											memcpy((void*)nuchar, reinterpret_cast <const void*> (sqlite3_column_blob(ppstmt, ret)), xret);
											memcpy((void*)&nuchar[xret], (void*)&echar, 1);
											std::vector<HIST_PV> nvec;
											HIST_PV hf;
											u_char lsep = (u_char)' ';
											u_char sep = (u_char)',';

											for (sint csiz = 0; (csiz + 1) < xret; csiz++)
											{
												if (!memcmp(&nuchar[csiz], &sep, xret) && !nvec.empty())
												{
													hf.ct = (uint)nuchar[csiz - 1];
													nvec.push_back(hf);
													hf.cons.clear();
													hf.ct = 0;
													csiz++;
												}
												else if (memcmp(&nuchar[csiz], &lsep, sizeof(u_char)) && !nvec.empty())
												{
													val.history_preceeding.push_back(nvec);
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
												val.history_preceeding.push_back(nvec);
											}
											free(nuchar);
										}
									}
									else {}
								}
								else {}
							}
							inv->push_back(val);
							break;
						}
						case BOT_RTV_VSCRPT:
						{
							std::vector<bot_script>* inv = reinterpret_cast<std::vector<bot_script>*>(qval_->rblk);
							bot_script val;

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										val.lid = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										val.last_maint = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										val.last_maint_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										val.last_mod = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										val.last_mod_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "MODE"))
									{
										val.mode = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "ENCODING"))
									{
										val.encoding = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "USED"))
									{
										val.used = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED_BY"))
									{
										val.lub = *(reinterpret_cast<const uint*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "NAME"))
									{
										val.name.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "TYPE"))
									{
										val.type.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "DEST"))
									{
										val.dest.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_USED"))
									{
										val.lused.append(reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
									else {}
								}
								else {}
							}
							inv->push_back(val);
							break;
						}
						case BOT_RTV_VSES:
						{
							std::vector<bot_session>* inv = reinterpret_cast<std::vector<bot_session>*>(qval_->rblk);
							bot_session val;

							for (size_t iter = 0; iter < qval_->fcols.size(); iter++)
							{
								ret = FindColumn(qval_->fcols[iter].c_str(), ppstmt);
								sint ct = sqlite3_column_type(ppstmt, ret);
								sint xret = sqlite3_column_bytes(ppstmt, ret);

								if (ct == SQLITE_INTEGER)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "ID"))
									{
										val.id = sqlite3_column_int(ppstmt, ret);
									}
									if (!strcmp(qval_->fcols[iter].c_str(), "PID"))
									{
										val.pid = sqlite3_column_int(ppstmt, ret);
									}
									if (!strcmp(qval_->fcols[iter].c_str(), "QUIT"))
									{
										val.quit = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED"))
									{
										val.last_maint = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MAINTAINED_NS"))
									{
										val.last_maint_ns = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED"))
									{
										val.last_mod = sqlite3_column_int(ppstmt, ret);
									}
									else if (!strcmp(qval_->fcols[iter].c_str(), "LAST_MODIFIED_NS"))
									{
										val.last_mod_ns = sqlite3_column_int(ppstmt, ret);
									}
									else {}
								}
								else if (ct == SQLITE_FLOAT)
								{

								}
								else if (ct == SQLITE_TEXT)
								{

								}
								else if (ct == SQLITE_BLOB || ct == SQLITE_NULL)
								{
									if (!strcmp(qval_->fcols[iter].c_str(), "NAME"))
									{
										bot_sprintf(val.nm.carr,val.nm.siz,"%s", reinterpret_cast<c_char*>(sqlite3_column_blob(ppstmt, ret)));
									}
								}
								else {}
							}
							inv->push_back(val);
							break;
						}
						default:
						{
							break;
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
						sllint rst = Rest(BOT_MILLI_REST);
						break;
					}
					default:
					{
						sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
						fdone = done = true;
						break;
					}
					}
				}
				ret = FinStmt(&ppstmt);
			}
			d_con_->o_com = false;
			ret = UpdMTXPrio();
		}
		if (!hdb)
		{
			hdb = CloseDB(&dbs, &of);
		}
	}
	return ret;
}
sint machine::Commit(BOT_STMT* stmt_)
{
	if (debug_lvl >= 500 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::Commit(BOT_STMT* stmt_(%i))", (sint)stmt_);
		op = Output(outp.carr, 2);
	}

	if (!stmt_)
	{
		return -1;
	}
	std::vector<BOT_STMT> vec;
	vtool.AVTV(&vec, stmt_, true, true);
	return Commit(&vec);
}
sint machine::Commit(std::vector<BOT_STMT>* stmts_)
{
	if (debug_lvl >= 500 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::Commit(std::vector<BOT_STMT>* stmts_(%i))", (sint)stmts_);
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
			std::vector<sint> wos;
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
				d_con_->o_com = true;
				sint xc = UpdMTXPrio();
				size_t nsiz = 0;

				while (nsiz < Comm.t.size())
				{
					sint vv = vtool.VIV(&Comm.dbs, Comm.t[nsiz].dbname.c_str());

					if (vv > -1)
					{
						sint rc = 0;

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
								outp.append("preparing statement: ");
								outp.append(Comm.t[nsiz].stmt.c_str());
								sint xp = Output(outp.c_str(), 2);
							}

							rc = sqlite3_prepare_v2(d_con_->db_, Comm.t[nsiz].stmt.c_str(), (sint)Comm.t[nsiz].stmt.length(), &ppstmt, &tail);

							if (rc == SQLITE_BUSY)
							{
								sllint rst = Rest(BOT_MILLI_REST);
							}
							else if (rc)
							{
								sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
								nsiz++;
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
										Comm.t[nsiz].Clear();
										nsiz++;
										sdone = true;
										break;
									}
									case SQLITE_DONE:
									{
										if (debug_lvl >= 500 && debug_m)
										{
											sint xp = Output("SQLITE_DONE", 2);
										}
										Comm.t[nsiz].Clear();
										nsiz++;
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
										sllint rst = Rest(BOT_MILLI_REST);
										break;
									}
									default:
									{
										sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
										sdone = true;
										Comm.t[nsiz].Clear();
										nsiz++;
										break;
									}
									}
								}
								rc = FinStmt(&ppstmt);
							}
						}
					}
					else
					{
						nsiz++;
					}
				}
				
				nsiz = 0;

				while (nsiz < Comm.an.size())
				{
					sint viv = vtool.VIV(&Comm.dbs, Comm.an[nsiz].dbname.c_str());

					if (viv > -1)
					{
						sint rc = 0;

						if (Comm.an[nsiz].stmt.empty())
						{
							rc = BTS(&Comm.an[nsiz]);
						}
						if (!rc)
						{
							c_char* tail = "";
							sqlite3_stmt* ppstmt;

							if (debug_lvl >= 500 && debug_m)
							{
								std::string output;
								output.append("preparing analyze statement: ");
								output.append(Comm.an[nsiz].stmt);
								sint xp = Output(output.c_str(), 2);
							}
							rc = sqlite3_prepare_v2(d_con_->db_, Comm.an[nsiz].stmt.c_str(), (sint)Comm.an[nsiz].stmt.length(), &ppstmt, &tail);

							if (rc == SQLITE_BUSY)
							{
								sllint rst = Rest(BOT_MILLI_REST);
							}
							else if (rc)
							{
								sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
								nsiz++;
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
									Comm.t[nsiz].Clear();
									nsiz++;
									break;
								}
								case SQLITE_DONE:
								{
									if (debug_lvl >= 500 && debug_m)
									{
										sint xp = Output("SQLITE_DONE", 2);
									}
									Comm.an[nsiz].Clear();
									nsiz++;
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
									sllint rst = Rest(BOT_MILLI_REST);
									break;
								}
								default:
								{
									sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
									Comm.an[nsiz].Clear();
									nsiz++;
									break;
								}
								}
								rc = FinStmt(&ppstmt);
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

sint machine::FinStmt(sqlite3_stmt** ppstmt)
{
	if (debug_lvl >= 500 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::FinStmt(sqlite3_stmt** ppstmt(%i)))", (sint)ppstmt);
		op = Output(outp.carr, 2);
	}
	if (!ppstmt)
	{
		return -1;
	}

	sint rc = sqlite3_finalize(*ppstmt);

	if (rc == SQLITE_BUSY)
	{
		rc = 0;
	}
	else if (rc)
	{
		sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
	}
	else {}
	return rc;
}
sint machine::VerifyDatabases()
{
	if (debug_lvl >= 450 && debug_m)
	{
		sint op = Output("::VerifyDatabases()", 2);
	}

	uint db_failed = 0;
	std::vector<std::string> nms;
	sint hx = -1;
	sint h = LockGMutex(MTX_STRT, &hx);
	
	for (uint x = 0; x < bot_strt.dbn.size(); x++)
	{
		nms.push_back(bot_strt.dbn[x]);
	}

	for (size_t x = 0; x < nms.size(); x++)
	{
		std::string pth;
		sint xc = BOTPath(&pth, BOT_DBD_NM);
		BOT_FILE_M ndb(nms[x].c_str(), ".db", pth.c_str(), 3, BOT_DB_CON, -1, -1, lid);
		sint of = -1;
		xc = BOTOpenFile(&ndb, &of, false, true);

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

			for (size_t cc = 0; cc < dbs_->tsiz; cc++)
			{
				sint v = VerifyTable(&dbs, &tvec, (sint)cc, odb);

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

		if (rc == SQLITE_BUSY)
		{
			sllint rst = Rest(BOT_MILLI_REST);
		}
		else if (rc)
		{
			std::string output(GetError().c_str());

			if (debug_lvl >= 1 && debug_m)
			{
				rc = Output(0, true, output.c_str(), 1, 2, -1);
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
									op = Output(0, true, outp.carr, 1, 2, -1);
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
									op = Output(0, true, outp.carr, 1, 2, -1);
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
					sllint rst = Rest(BOT_MILLI_REST);
					tries++;
					break;
				}
				default:
				{
					rc = Output(0, true, GetError().c_str(), 1, 2, -1);
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
			rc = FinStmt(&ppstmt);
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
		size_t siz = 0;

		while (siz < stmts.size())
		{
			rc = 0;

			if (stmts[siz].stmt.empty())
			{
				rc = BQS(&stmts[siz]);
			}

			if (!rc)
			{
				d_con_->o_com = true;
				rc = UpdMTXPrio();
				c_char* tail;
				sqlite3_stmt* ppstmt;
				rc = sqlite3_prepare_v2(d_con_->db_, stmts[siz].stmt.c_str(), (sint)stmts[siz].stmt.length(), &ppstmt, &tail);

				if (rc == SQLITE_BUSY)
				{
					sllint rst = Rest(BOT_MILLI_REST);
				}
				else if (rc)
				{
					rc = Output(0, true, GetError().c_str(), 1, 2, -1);
					siz++;
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
							siz++;
							done = true;
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								rc = Output("SQLITE_DONE", 2);
							}
							siz++;
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
															free(nuchar);
														}
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
															free(nuchar);
														}
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
															free(nuchar);
														}
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
							sllint Rest(BOT_MILLI_REST);
							break;
						}
						default:
						{
							rc = Output(0, true, GetError().c_str(), 1, 2, -1);
							done = true;
							siz++;
							break;
						}
						}
					}
					rc = FinStmt(&ppstmt);
				}
				d_con_->o_com = false;
				rc = UpdMTXPrio();
			}
			else
			{
				siz++;
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
		size_t siz = 0;

		while (siz < stmts.size())
		{
			rc = 0;

			if (stmts[siz].stmt.empty())
			{
				rc = BQS(&stmts[siz]);
			}

			if (!rc)
			{
				d_con_->o_com = true;
				rc = UpdMTXPrio();
				c_char* tail;
				sqlite3_stmt* ppstmt;
				rc = sqlite3_prepare_v2(d_con_->db_, stmts[siz].stmt.c_str(), (sint)stmts[siz].stmt.length(), &ppstmt, &tail);

				if (rc == SQLITE_BUSY)
				{
					sllint rst = Rest(BOT_MILLI_REST);
				}
				else if (rc)
				{
					rc = Output(0, true, GetError().c_str(), 1, 2, -1);
					siz++;
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
							siz++;
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 500 && debug_m)
							{
								rc = Output("SQLITE_DONE", 2);
							}
							done = true;
							siz++;
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
																free(nuchar);
															}
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
																free(nuchar);
															}
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
																free(nuchar);
															}
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
																free(nuchar);
															}
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
																free(nuchar);
															}
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
							sllint rst = Rest(BOT_MILLI_REST);
							break;
						}
						default:
						{
							sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
							done = true;
							siz++;
							break;
						}
						}
					}
					rc = FinStmt(&ppstmt);
				}
				d_con_->o_com = false;
				rc = UpdMTXPrio();
			}
			else
			{
				siz++;
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
sint machine::GetCommand(BOT_CLIENT_M* cli, BOTCOMMAND *Command_, std::vector<std::string> *conds_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetCommand(BOT_CLIENT_M* cli(%i), BOTCOMMAND *Command_(%i), std::vector<std::string> *conds_(%i))", (sint)cli, (sint)Command_, (sint)conds_);
		op = Output(outp.carr, 2);
	}
	if (!Command_)
	{
		return -1;
	}
	std::vector<BOTCOMMAND> vec;
	vec.push_back(*Command_);
	sint xc = GetCommands(cli, &vec);

	if (xc > -1 && !vec.empty())
	{
		Command_->Renew(&vec[0]);
	}
	return xc;
}
sint machine::GetCommands(BOT_CLIENT_M* cli, std::vector<BOTCOMMAND> *Commands_, std::vector<std::string> *conds_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetCommands(BOT_CLIENT_M* cli(%i), std::vector<BOTCOMMAND> *Command_(%i), std::vector<std::string>* conds_(%i))", (sint)cli, (sint)Commands_, (sint)conds_);
		op = Output(outp.carr, 2);
	}

	if (!Commands_ || !cli)
	{
		return -1;
	}

	std::vector<BOT_STMT> stmts;
	sint rc = 0;
	sint xc = -1;

	if (!Commands_->empty())
	{
		for (size_t x = 0; x < Commands_->size(); x++)
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
			if (cli->priv > -1)
			{
				xc = t.AddCond(0, "PRIV", msy.sql_comp_keywords[9].c_str(), stool.ITOA(cli->priv).c_str());
			}
			else
			{
				xc = t.AddCond(0, "PRIV", msy.sql_comp_keywords[5].c_str(), "0");
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
			size_t s = 0;

			while (s < stmts.size())
			{
				c_char* tail;
				sqlite3_stmt* ppstmt;
				rc = sqlite3_prepare_v2(d_con_->db_, stmts[s].stmt.c_str(), (sint)stmts[s].stmt.length(), &ppstmt, &tail);

				if (rc == SQLITE_BUSY)
				{
					sllint rst = Rest(BOT_MILLI_REST);
				}
				else if (rc)
				{
					rc = Output(0, true, GetError().c_str(), 1, 2, -1);
					s++;
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
							if (debug_lvl >= 700 && debug_m)
							{
								rc = Output("SQLITE_OK", 2);
							}
							done = true;
							s++;
							break;
						}
						case SQLITE_DONE:
						{
							if (debug_lvl >= 700 && debug_m)
							{
								rc = Output("SQLITE_DONE", 2);
							}
							s++;
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
								xc = cli->priv;

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
											Commands_->at(ret).cmd.append(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, rc)));
										}
									}
									ret++;
								}
							}
							break;
						}
						case SQLITE_BUSY:
						{
							sllint rst = Rest(BOT_MILLI_REST);
							break;
						}
						default:
						{
							done = true;
							s++;
							rc = Output(0, true, GetError().c_str(), 1, 2, -1);
							break;
						}
						}
					}
					rc = FinStmt(&ppstmt);
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
sint machine::BOTGetLogin(BOT_CLIENT_M* c_, c_char* str_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 ncar;
		sint xc = bot_sprintf(ncar.carr, ncar.siz, "::BOTGetLogin(BOT_CLIENT_M* c(%i), c_char* str_(%i))", (sint)c_, (sint)str_);
		xc = Output(ncar.carr, 2);
	}

	if (!c_)
	{
		return -1;
	}

	if (c_->atcons)
	{
		BOT_CLIENT_M pcli;
		sint xc = GetPCli(&pcli);

		if (xc > -1)
		{
			if (xc > -1)
			{
				sint rc = ClearVecEle(MTX_CV, pcli.lid, false);
			}
		}
	}

	sint xc = GetInVec(c_, MTX_CV);

	if (xc > -1)
	{
		if (c_->loggedin)
		{
			bot_cstrclr(str_);
			return 0;
		}
	}

	carr_64 dated;
	xc = BOTDateTime(dated.carr, dated.siz);
	BOT_STMT t(false, 0, "litebot", "ACCOUNTS", 1);
	t.AddCond(0, "LOGIN_NAME", msy.sql_comp_keywords[5].c_str(), EStr(UCASE(c_->name.c_str()).c_str()).c_str());
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
			BOT_CLIENT nc(c_->name.c_str(), &c_->prt);
			bool fdone = false;

			while (!fdone)
			{
				xc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

				if (xc == SQLITE_BUSY)
				{
					sllint rst = Rest(BOT_MILLI_REST);
				}
				else if (xc)
				{
					sint op = Output(0, true, GetError().c_str(), 1, 2, -1);
					xc = FinStmt(&ppstmt);
					fdone = true;
				}
				else
				{
					
					bool done = false;

					while (!done)
					{
						xc = sqlite3_step(ppstmt);

						switch (xc)
						{
						case SQLITE_DONE:
						{
							if (debug_lvl >= 700 && debug_m)
							{
								sint op = Output("SQLITE_DONE", 2);
							}
							fdone = done = true;
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
								if (!strcmp(str_, reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, 2))))
								{
									bot_cstrclr(str_);
									nc.failed_logins = 0;
									nc.loggedin = true;
									xc = FindColumn("ID", ppstmt);

									if (xc > -1)
									{
										nc.id = sqlite3_column_int(ppstmt, xc);
									}

									xc = FindColumn("PRIV", ppstmt);

									if (xc > -1)
									{
										nc.priv = sqlite3_column_int(ppstmt, xc);
									}

									xc = FindColumn("TOTAL_LOGINS", ppstmt);

									if (xc > -1)
									{
										nc.totallogins = sqlite3_column_int(ppstmt, xc) + 1;
									}

									xc = FindColumn("KIPS", ppstmt);

									if (xc > -1)
									{
										if (sqlite3_column_text(ppstmt, xc) != NULL)
										{
											nc.kips.append(reinterpret_cast<c_char*>(sqlite3_column_text(ppstmt, xc)));
										}
									}

									if (!nc.lastlogin.empty())
									{
										nc.lastlogin.clear();
									}
									nc.lastlogin.append(dated.carr);

									if (c_->lid > -1)
									{
										xc = SetVecEle((void*)&nc, MTX_CV, c_->lid, true, false);
									}
									else
									{
										xc = PushToVec((void*)&nc, MTX_CV, true, true, false);
									}
								}
								else
								{
									xc = BOTDateTimeMS(dated.carr, dated.siz);
									nc.last_failed_login.clear();
									nc.last_failed_login.append(dated.carr);

									xc = FindColumn("FAILED_LOGINS", ppstmt);

									if (xc > -1)
									{
										nc.failed_logins = sqlite3_column_int(ppstmt, xc) + 1;
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
							sllint rst = Rest(BOT_MILLI_REST);
							break;
						}
						default:
						{
							sint op = Output(0, true, GetError().c_str(), 1, 2, -1);
							fdone = done = true;
							break;
						}
						}
					}
					bot_cstrclr(str_);
					xc = FinStmt(&ppstmt);
				}
			}

			bot_cstrclr(str_);
			d_con_->o_com = false;
			xc = UpdMTXPrio();

			if (!hdb)
			{
				hdb = CloseDB(&dbs, &fdb);
			}

			if (nc.loggedin || nc.failed_logins != c_->failed_logins)
			{
				c_->Renew(&nc);
				c_->updatelogin = true;
				xc = BOTUpdateAccount(c_);
				c_->updatelogin = false;
			}
			return xc;
		}
		bot_cstrclr(str_);
	}
	bot_cstrclr(str_);
	return -1;
}
sint machine::BOTUpdateAccount(BOT_CLIENT_M *c_)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_128 ncar;
		sint xc = bot_sprintf(ncar.carr, ncar.siz, "::BOTUpdateAccount(BOT_CLIENT_M* c_(%i))", (sint)c_);
		xc = Output(ncar.carr, 2);
	}
	if (!c_)
	{
		return -1;
	}
	std::vector<BOT_STMT> tvec;
	BOT_STMT t(false, 1, "litebot", "ACCOUNTS", 1);
	t.spec = 0;
	t.act = 0;
	sint xc = t.AddCond(0, "LOGIN_NAME", msy.sql_comp_keywords[5].c_str(), EStr(UCASE(c_->name.c_str()).c_str()).c_str());

	if (c_->id > -1)
	{
		xc = t.AddCond(0, "ID", msy.sql_comp_keywords[5].c_str(), stool.ITOA(c_->id).c_str());
	}

	if (c_->loggedin)
	{
		if (c_->changename)
		{
			xc = t.AddCol("LOGIN_NAME", EStr(UCASE(c_->name.c_str()).c_str()).c_str());
		}

		if (c_->updatepriv)
		{
			xc = t.AddCol("PRIV", stool.ITOA(c_->priv).c_str());
		}

		if (c_->updatelogin)
		{
			xc = t.AddCol("LAST_LOGIN", EStr(c_->lastlogin.c_str()).c_str());
			xc = t.AddCol("TOTAL_LOGINS", stool.ITOA(c_->totallogins).c_str());
			xc = t.AddCol("FAILED_LOGINS", stool.ITOA(0).c_str());
		}
		xc = t.AddCol("LAST_IP", EStr(c_->prt.oipstr.carr).c_str());

		if (c_->kips.empty())
		{
			c_->kips.append(c_->prt.oipstr.carr);
			xc = t.AddCol("KIPS", EStr(c_->kips.c_str()).c_str());
		}
		else
		{
			xc = c_->kips.find(c_->prt.oipstr.carr, 0);

			if (xc < 0)
			{
				bot_sprintfs(&c_->kips, false, ", %s", c_->prt.oipstr.carr);
				xc = t.AddCol("KIPS", EStr(c_->kips.c_str()).c_str());
			}
		}
	}
	else
	{
		if (c_->updatelogin)
		{
			xc = t.AddCol("LAST_FAILED_LOGIN", EStr(c_->last_failed_login.c_str()).c_str());
			xc = t.AddCol("FAILED_LOGINS", stool.ITOA(c_->failed_logins + 1).c_str());
			xc = t.AddCol("LAST_FAILED_IP", c_->prt.oipstr.carr);
		}
	}
	xc = vtool.AVTV(&tvec, &t, false, false);
	xc = Commit(&tvec);
	return xc;
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
			sint xc = 0;

			if (t.stmt.empty())
			{
				xc = BQS(&t);
			}

			if (!xc)
			{
				d_con_->o_com = true;
				xc = UpdMTXPrio();
				c_char* tail;
				sqlite3_stmt* ppstmt;
				bool fdone = false;

				while (!fdone)
				{
					xc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

					if (xc == SQLITE_BUSY)
					{
						sllint rst = Rest(BOT_MILLI_REST);
					}
					else if (xc)
					{
						sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
						fdone = true;
					}
					else
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
								fdone = done = true;
								break;
							}
							case SQLITE_DONE:
							{
								if (debug_lvl >= 750 && debug_m)
								{
									sint xp = Output("SQLITE_DONE", 2);
								}
								fdone = done = true;
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
								sllint rst = Rest(BOT_MILLI_REST);
								break;
							}
							default:
							{
								sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
								fdone = done = true;
								break;
							}
							}
						}
						xc = FinStmt(&ppstmt);
					}
				}

				d_con_->o_com = false;
				xc = UpdMTXPrio();

				if (!hdb)
				{
					hdb = CloseDB(dbs_, &fdb);
				}
				return xc;
			}
			if (!hdb)
			{
				hdb = CloseDB(dbs_, &fdb);
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
		return -1;
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
				bool fdone = false;

				while (!fdone)
				{
					xc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

					if (xc == SQLITE_BUSY)
					{
						sllint rst = Rest(BOT_MILLI_REST);
					}
					else if (xc)
					{
						xc = Output(0, true, GetError().c_str(), 1, 2, -1);
						fdone = true;
					}
					else
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
								fdone = done = true;
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
								fdone = done = true;
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
								sllint rst = Rest(BOT_MILLI_REST);
								break;
							}
							default:
							{
								sint xp = Output(0, true, GetError().c_str(), 1, 2, -1);
								fdone = done = true;
								break;
							}
							}
						}

						xc = FinStmt(&ppstmt);

						if (!tvec.empty())
						{
							xc = Commit(&tvec);
						}
					}
				}

				d_con_->o_com = false;
				xc = UpdMTXPrio();

				if (!hdb)
				{
					hdb = CloseDB(dbs_, &fdb);
				}
				return 0;
			}
			if (!hdb)
			{
				hdb = CloseDB(dbs_, &fdb);
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
		else if (!strcmp(dbs_->name.c_str(), "vars"))
		{
			dbs_->type = 5;
		}
		else if (strlen(dbs_->name.c_str()) < 3)
		{
			dbs_->type = 6;
		}
		else
		{
			dbs_->type = 7;
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
			for (size_t t = 0; t < bot_strt.litebot_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.litebot_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols;
				dbs_->columns[ret].push_back(cols);
				dbs_->columns[ret].push_back(cols);

				if (t < (sint)bot_strt.litebot_columns.size())
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.litebot_columns[t]), bot_strt.litebot_columns[t], BOT_RTV_CHAR, ' ');
				}
				else
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.litebot_columns[(sint)bot_strt.litebot_columns.size() - 1]), bot_strt.litebot_columns[(sint)bot_strt.litebot_columns.size() - 1], BOT_RTV_CHAR, ' ');
				}

				if (cols.size() > 1)
				{
					if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
					{
						cols[1].append(" PRIMARY KEY");
					}
					for (size_t x = 0; x < cols.size(); )
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
			for (size_t t = 0; t < bot_strt.math_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.math_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols;
				dbs_->columns[ret].push_back(cols);
				dbs_->columns[ret].push_back(cols);

				if (t < (sint)bot_strt.math_columns.size())
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.math_columns[t]), bot_strt.math_columns[t], BOT_RTV_CHAR, ' ');
				}
				else
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.math_columns[(sint)bot_strt.math_columns.size() - 1]), bot_strt.math_columns[(sint)bot_strt.math_columns.size() - 1], BOT_RTV_CHAR, ' ');
				}

				if (cols.size() > 1)
				{
					if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
					{
						cols[1].append(" PRIMARY KEY");
					}
					for (size_t x = 0; x < cols.size(); )
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
			sint nh = -1;
			sint np = LockGMutex(MTX_FTYPE, &nh);

			if (np > -1)
			{
				for (size_t t = 1; t < bot_symbol_types.size(); t++)
				{
					std::vector<std::vector<std::string>> tcols;
					std::vector<std::string> cols;
					ret = vtool.AVTV(&dbs_->tables, bot_symbol_types[t], false, false);
					dbs_->columns.push_back(tcols);
					dbs_->columns[ret].push_back(cols);
					dbs_->columns[ret].push_back(cols);

					if (t < (sint)bot_strt.code_columns.size())
					{
						sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.code_columns[t]), bot_strt.code_columns[t], BOT_RTV_CHAR, ' ');
					}
					else
					{
						sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.code_columns[(sint)bot_strt.code_columns.size() - 1]), bot_strt.code_columns[(sint)bot_strt.code_columns.size() - 1], BOT_RTV_CHAR, ' ');
					}

					if (cols.size() > 1)
					{
						if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
						{
							cols[1].append(" PRIMARY KEY");
						}
						for (size_t x = 0; x < cols.size(); )
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
			for (size_t t = 0; t < bot_strt.syms_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.syms_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols;
				dbs_->columns[ret].push_back(cols);
				dbs_->columns[ret].push_back(cols);

				if (t < (sint)bot_strt.syms_cols.size())
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.syms_cols[t]), bot_strt.syms_cols[t], BOT_RTV_CHAR, ' ');
				}
				else
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.syms_cols[(sint)bot_strt.syms_cols.size() - 1]), bot_strt.syms_cols[(sint)bot_strt.syms_cols.size() - 1], BOT_RTV_CHAR, ' ');
				}

				if (cols.size() > 1)
				{
					if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
					{
						cols[1].append(" PRIMARY KEY");
					}
					for (size_t x = 0; x < cols.size(); )
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
			for (size_t t = 0; t < bot_strt.scripts_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.scripts_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols;
				dbs_->columns[ret].push_back(cols);
				dbs_->columns[ret].push_back(cols);

				if (t < (sint)bot_strt.scripts_cols.size())
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.scripts_cols[t]), bot_strt.scripts_cols[t], BOT_RTV_CHAR, ' ');
				}
				else
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.scripts_cols[(sint)bot_strt.scripts_cols.size() - 1]), bot_strt.scripts_cols[(sint)bot_strt.scripts_cols.size() - 1], BOT_RTV_CHAR, ' ');
				}

				if (cols.size() > 1)
				{
					if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
					{
						cols[1].append(" PRIMARY KEY");
					}
					for (size_t x = 0; x < cols.size(); )
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
		case 5:
		{
			for (size_t t = 0; t < bot_strt.vars_tablenames.size(); t++)
			{
				ret = vtool.AVTV(&dbs_->tables, bot_strt.vars_tablenames[t], false, false);
				std::vector<std::vector<std::string>> tcols;
				dbs_->columns.push_back(tcols);
				std::vector<std::string> cols;
				dbs_->columns[ret].push_back(cols);
				dbs_->columns[ret].push_back(cols);

				if (t < (sint)bot_strt.vars_cols.size())
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.vars_cols[t]), bot_strt.vars_cols[t], BOT_RTV_CHAR, ' ');
				}
				else
				{
					sint xp = ArgSep(&cols, false, 0, bot_cstrlen(bot_strt.vars_cols[(sint)bot_strt.vars_cols.size() - 1]), bot_strt.vars_cols[(sint)bot_strt.vars_cols.size() - 1], BOT_RTV_CHAR, ' ');
				}

				if (cols.size() > 1)
				{
					if (!strcmp(cols[0].c_str(), "ID") && !strcmp(cols[1].c_str(), "INTEGER"))
					{
						cols[1].append(" PRIMARY KEY");
					}
					for (size_t x = 0; x < cols.size(); )
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
	xc = GetThreadQuit(1);

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

	slint id = -1;
#ifdef _WIN32
	id = (slint)GetCurrentThreadId();
#else
	id = pthread_self();
#endif

	rc = SetVecEleMem((void*)&id, MTX_TTS, lid, BOT_TTS_TID, false);

	if (rc < 0)
	{
		mk_thr = false;
		UpdMTXPrio();
		return (sint)BOT_THR_FIN;
	}
	return (sint)BOT_THR_RUN;
}
sint machine::SignalThread(_char* thr, sint sign)
{
	if (bot_sisn(thr, bot_strlen(thr)))
	{
		if (!strcmp(UCASE(thr).c_str(), "0"))
		{
			TINFO_M np;
			sint xc = 1;

			while (GetVecEle(&np, MTX_TTS, xc++) > -1)
			{
				sint rc = SetVecEleMem((void*)&sign, MTX_TTS, np.lid, BOT_TTS_SIG, false);

				if (rc > -1)
				{
					carr_1024 xcar;
					rc = bot_sprintf(xcar.carr, xcar.siz, "thread signal(%i) set: [%i]'%s' opt: %i", sign, np.lid, np.thread_name.c_str(), np.opt);
					rc = Output(0, true, xcar.carr, 2, 0);
				}
			}
		}
		else
		{
			TINFO_M np;
			sint xc = GetVecEle(&np, MTX_TTS, (sint)atoi(thr));

			if (xc > -1)
			{
				xc = SetVecEleMem((void*)&sign, MTX_TTS, np.lid, BOT_TTS_SIG, false);

				if (xc > -1)
				{
					carr_1024 xcar;
					xc = bot_sprintf(xcar.carr, xcar.siz, "thread signal(%i) set: [%i]'%s' opt: %i", sign, np.lid, np.thread_name.c_str(), np.opt);
					xc = Output(0, true, xcar.carr, 2, 0);
				}
			}
		}
		
	}
	else
	{
		if (!strcmp(UCASE(thr).c_str(), "ALL"))
		{
			TINFO_M np;
			sint xc = 1;

			while (GetVecEle(&np, MTX_TTS, xc++) > -1)
			{
				sint rc = SetVecEleMem((void*)&sign, MTX_TTS, np.lid, BOT_TTS_SIG, false);

				if (rc > -1)
				{
					carr_1024 xcar;
					rc = bot_sprintf(xcar.carr, xcar.siz, "thread signal(%i) set: [%i]'%s' opt: %i", sign, np.lid, np.thread_name.c_str(), np.opt);
					rc = Output(0, true, xcar.carr, 2, 0);
				}
			}
		}
		else
		{
			TINFO_M np(-1, thr);
			sint xc = GetInVec(&np, MTX_TTS, false);

			if (xc > -1)
			{
				xc = SetVecEleMem((void*)&sign, MTX_TTS, np.lid, BOT_TTS_SIG, false);

				if (xc > -1)
				{
					carr_1024 xcar;
					xc = bot_sprintf(xcar.carr, xcar.siz, "thread signal(%i) set: [%i]'%s' opt: %i", sign, np.lid, np.thread_name.c_str(), np.opt);
					xc = Output(0, true, xcar.carr, 2, 0);
				}
			}
		}
	}
	return 0;
}
sint machine::ThreadSignal()
{
	sint ret = BOT_TSG_MIN;
	sint rc = GetVecEleMem((void*)&ret, MTX_TTS, lid, BOT_TTS_SIG);
	
	if (rc > -1)
	{
		sint xc = BOT_TSG_OK;
		rc = SetVecEleMem((void*)&xc, MTX_TTS, lid, BOT_TTS_SIG, false);
	}
	return ret;
}
sint machine::ThreadRest(sllint dur, sint qt_lvl)
{
	sint qt = GetThreadQuit(qt_lvl);

	if (qt)
	{
		if (debug_lvl >= 100 && debug_m)
		{
			sint rc = Output("finish signal", 2);
		}
		return qt;
	}
	else
	{
		sint rc = ThreadSignal();

		if (rc == BOT_TSG_CLS)
		{
			if (debug_lvl >= 100 && debug_m)
			{
				rc = Output("finish signal", 2);
			}
			return rc;
		}
		else
		{
			sllint rst = Rest(dur);
			std::chrono::steady_clock::time_point nt = std::chrono::steady_clock::now();
			rc = SetVecEleMem((void*)&nt, MTX_TTS, lid, BOT_TTS_TIMEP, false);
			rc = GetDBG(&debug_lvl, &debug_m);
			return 0;
		}
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
sint machine::GetThreadQuit(sint qlvl)
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
	if (ret >= qlvl)
	{
		return 1;
	}
	return 0;
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
		sint xc = pthread_join(tts_vec.dvec[thrid].thread, &vp_);

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
		TINFO tts(tts_->opt, tts_->thread_name.c_str(), tts_->func, tts_->c_by, tts_->min_ratv, &tts_->vals);
		tts.fin = (sint)BOT_THR_PCL;
		xc = PushToVec(&tts, MTX_TTS, false, true, false);

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
				sint xp = Output(0, true, "error: decrementing open thread count.", 1, 2, -1);
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
			lx = Output(0, true, outp.carr, 1, 2, -1);

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
								lx = Output(0, true, outp.carr, 1, 2, -1);
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
									lx = Output(0, true, outp.carr, 1, 2, -1);
								}
							}

							lx = ClearVecEle(MTX_TTS, tts_->lid, false);
							lx = IncrThreads();

							if (lx < 0)
							{
								lx = Output(0, true, "error: incrementing open thread count.", 1, 2, -1);
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
sint machine::MT(std::vector<ullint>* vals)
{
	if (debug_lvl >= 200 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::MT(std::vector<ullint>* vals(%i))", (sint)vals);
		op = Output(outp.carr, 2);
	}
	if (!vals)
	{
		return -1;
	}
#ifdef __GNUC__
	struct sigaction sa;
#endif

	uint bot_started = 0;
	bool done = false;

	while (!done)
	{
		sint xc = BOTDate(ses_date.carr, ses_date.siz, false);

		if (!done)
		{
			xc = RefBIPS();
		}

		xc = TM(&bot_started);

		if (xc)
		{
			carr_64 ncar;
			sint oc = bot_sprintf(ncar.carr, ncar.siz, "ThreadMaintenance fault: %i", xc);
			return -1;
		}

		if (GetThreadQuit(1))
		{
			if (!bot_mode)
			{
				xc = CloseConnection(0, 2, (sint)vals->at(1));
			}
			else
			{
				xc = CloseConnection((sint)vals->at(0), 2, (sint)vals->at(1));
			}
			xc = StopAllThreads();
			done = true;
		}
		else
		{
			/*before we rest*/
			
			if (!bot_mode)
			{
				vals->push_back(BOTLPORT_B);
				vals->at(0) = (ullint)SOCK_STREAM;
				xc = StartConnection(vals, 2);

				if (xc)
				{
					carr_64 ncar;
					sint oc = bot_sprintf(ncar.carr, ncar.siz, "StartConnection stream fault: %i", xc);
				}

				vals->at(0) = (ullint)SOCK_DGRAM;
				xc = StartConnection(vals, 2);

				if (xc)
				{
					carr_64 ncar;
					sint oc = bot_sprintf(ncar.carr, ncar.siz, "StartConnection data fault: %i", xc);
				}
			}
			else if (bot_mode == 1)
			{
				xc = StartConnection(vals, 2);

				if (xc)
				{
					carr_64 ncar;
					sint oc = bot_sprintf(ncar.carr, ncar.siz, "StartConnection fault: %i", xc);
				}
			}
			else {}

			xc = BOTStartSession((slint)GetCurrentProcessId());

			if (xc)
			{
				carr_64 ncar;
				sint oc = bot_sprintf(ncar.carr, ncar.siz, "StartSession fault: %i", xc);
			}

			if (!bot_mode)
			{
				sllint rst = Rest((sllint)BOT_THRREST);
			}
			else if (bot_mode == 1)
			{
#ifdef _WIN32
				MSG mmsg;

				if (PeekMessage(&mmsg, NULL, 0, 0, PM_NOREMOVE))
				{
					switch (mmsg.message)
					{
					case WM_QUIT:
					{
						bool b;
						LPMSG mmsg = 0;

						if ((b = GetMessage(mmsg, NULL, 0, 0)) != 0)
						{
							sllint rst = Rest((sllint)BOT_MILLI_REST * 1000);
						}
						else
						{
							SetThreadQuit(1);
						}
						break;
					}
					default:
					{
						sllint rst = Rest((sllint)BOT_MILLI_REST * 1000);
						break;
					}
					}
				}
				else
				{
					sllint rst = Rest((sllint)BOT_MILLI_REST * 1000);
				}
#else
				sllint rst = Rest((sllint)BOT_MILLI_REST * 1000);
#endif
			}
			else
			{
				sllint rst = Rest((sllint)BOT_MILLI_REST * 1000);
			}
		}

#ifdef __GNUC__
		sa.sa_handler = sigchld_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;

		ret = sigaction(SIGCHLD, &sa, NULL);

		if (ret < 0)
		{
			perror(emsg.carr);
		}
#endif
	}
	return BOTEndSession((slint)GetCurrentProcessId());
}

sint machine::TM(uint* is_s)
{
	if (debug_lvl >= 200 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::TM(uint* is_s(%i))", (sint)is_s);
		op = Output(outp.carr, 2);
	}

	if (!is_s)
	{
		return -1;
	}

	if (!GetThreadQuit(1))
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
				else
				{
					if (!bot_mode)
					{
						if (!strcmp(ntts.thread_name.c_str(), "DBMaintenance"))
						{
							has_dm = true;
						}
						else if (!strcmp(ntts.thread_name.c_str(), "ConsoleThread"))
						{
							has_cons = true;
						}
						else {}
					}
					else if (bot_mode == 2)
					{
						if (!strcmp(ntts.thread_name.c_str(), "ConsoleThread"))
						{
							has_cons = true;
						}
					}
					else {}
				}
				if (ntts.fin > (sint)BOT_THR_RUN && ntts.opt == (sint)PTHREAD_CREATE_DETACHED)
				{
					if (debug_lvl >= 200 && debug_m)
					{
						carr_64 outp;
						sint op = bot_sprintf(outp.carr, outp.siz, "clearing ele(%i)", p);
						op = Output(outp.carr, 2);
					}
					ClearVecEle(MTX_TTS, ntts.lid, false);
					sint op = IncrThreads();
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
			xc = TestThreads(100);
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
		if (!has_dm && !bot_mode)
		{
			if (debug_lvl >= 200 && debug_m)
			{
				sint xc = Output("adding DBMaintenance to thread list", 2);
			}
			TINFO_M tts((sint)PTHREAD_CREATE_DETACHED, "DBMaintenance", DBMaintenance, lid, 1.0f);
			sint xc = InitThread(&tts);
		}
		if (!has_cons && (!bot_mode || bot_mode == 2))
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
sint machine::TestThreads(sint num)
{
	if (debug_lvl >= 200 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::TestThreads(sint num(%i))", (sint)num);
		op = Output(outp.carr, 2);
	}

	std::vector<TINFO_M> create_vec;

	for (sint p = 0; p < num; p++)
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
		return p;
	}
	return -1;
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
sint machine::GetPCli(BOT_CLIENT_M* val)
{
	if (debug_lvl >= 90 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetPCli(BOT_CLIENT_M* val(%i))", (sint)val);
		op = Output(outp.carr, 2);
	}
	if (!val)
	{
		return -1;
	}

	sint xc = 0;
	BOT_CLIENT_M c;

	while (GetVecEle((void*)&c, MTX_CV, xc) > -1)
	{
		if (c.atcons)
		{
			val->Renew(&c);
			return xc;
		}
		else
		{
			xc++;
		}
	}
	return -1;
}
sint machine::GetClientByPort(BOT_CLIENT_M* c_, _char* addr, sint portn, sint stype)
{
	if (debug_lvl >= 90 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetClientByPort(BOT_CLIENT_M* c_(%i), _char* addr(%i), sint portn(%i), sint stype(%i))", (sint)c_, (sint)addr, portn, stype);
		op = Output(outp.carr, 2);
	}
	if (!c_ || !addr || !portn || !stype)
	{
		return -1;
	}

	BOT_CLIENT_M n;

	for (sint xc = 0; GetVecEle((void*)&n, MTX_CV, xc) > -1; xc++)
	{
		if (!strcmp(addr, n.prt.oipstr.carr) && stype == n.prt.stype && portn == n.prt.portn)
		{
			c_->Renew(&n);
			return xc;
		}
	}
	return -1;
}
sint machine::GetVINs(BOT_FILE_M* file_, c_char* ramp, c_char* emp, c_char* fdate, c_char* ftyp, bool as_var)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetVINs(BOT_FILE_M* file_(%i), c_char* ramp(%i), c_char* emp(%i), c_char* fdate(%i), c_char* ftyp(%i), bool as_var(%u))", (sint)file_, (sint)ramp, (sint)emp, (sint)fdate, (sint)ftyp, (uint)as_var);
		op = Output(outp.carr, 2);
	}

	if (!file_)
	{
		return -1;
	}

	sint ret = -1;
	sint f = file_->name.find("error", 0);
	sint of = -1;
	sint ox = BOTOpenFile(file_, &of, true, false, false, true);

	if (ox > -1)
	{
		std::vector<BOT_ARG> args;
		ox = ArgSep(&args, false, 0, file_->dsiz - 1, file_->datp, BOT_RTV_CHAR, '\n');

		if (!of)
		{
			of = BOTCloseFile(file_, true, false, true);
		}

		if (ox > -1)
		{
			if (as_var)
			{
				std::vector<std::string> vstr;

				if (f < 0)
				{
					for (size_t x = 0; x < args.size(); x++)
					{
						if (args[x].arg.length() >= 17)
						{
							vstr.push_back(args[x].arg.substr(0,17));
						}
					}

					ret = 0;
					carr_21 vnm("vins");

					while (FVAR(vnm.carr) > -1)
					{
						bot_sprintf(vnm.carr, vnm.siz, "vins_%i", ret++);
					}
					ret = SVAR(vnm.carr, BOT_RTV_VSTR, &vstr);
				}
				else
				{

					for (size_t x = 0; x < args.size(); x++)
					{
						bool pass = true;

						if (bot_cstrlen(ramp))
						{
							if (strcmp(&ramp[0], "?"))
							{
								if (strcmp(args[x].arg.substr(0, 5).c_str(), ramp))
								{
									pass = false;
								}
								else {}
							}
						}

						if (bot_cstrlen(emp))
						{
							if (strcmp(&emp[0], "?"))
							{
								if (strcmp(args[x].arg.substr(37, 5).c_str(), emp))
								{
									pass = false;
								}
								else {}
							}
						}

						if (bot_cstrlen(ftyp))
						{
							if (strcmp(&ftyp[0], "?"))
							{
								if (strcmp(args[x].arg.substr(45, 2).c_str(), ftyp))
								{
									pass = false;
								}
								else {}
							}
						}

						if (bot_cstrlen(fdate))
						{
							if (strcmp(&fdate[0], "?"))
							{
								std::string datstr(fdate);

								if (datstr.length() > 8)
								{
									if (strcmp(args[x].arg.substr(29, 4).c_str(), CPunc(datstr.c_str()).substr(3, 4).c_str()))
									{
										pass = false;
									}
									if (strcmp(args[x].arg.substr(33, 4).c_str(), CPunc(datstr.c_str()).substr(0, 4).c_str()))
									{
										pass = false;
									}
								}
								else if (datstr.length() == 8)
								{
									if (strcmp(args[x].arg.substr(29, 4).c_str(), datstr.substr(4, 4).c_str()))
									{
										pass = false;
									}
									if (strcmp(args[x].arg.substr(33, 4).c_str(), datstr.substr(0, 4).c_str()))
									{
										pass = false;
									}
								}
								else {}
							}
						}

						if (pass)
						{
							vstr.push_back(args[x].arg.substr(5, 17));
						}
					}
					ret = 0;
					carr_21 vnm("vins");

					while (FVAR(vnm.carr) > -1)
					{
						bot_sprintf(vnm.carr, vnm.siz, "vins_%i", ret++);
					}
					ret = SVAR(vnm.carr, BOT_RTV_VSTR, &vstr);
				}			
			}
			else
			{
				carr_64 nm;
				ox = bot_sprintf(nm.carr, nm.siz, "vins_%s%s%s%s_%s", ramp, ftyp, emp, fdate, ses_date.carr);
				BOT_FILE_M pcs(nm.carr, "txt", BOTPathS(BOT_LDSO_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
				ox = BOTOpenFile(&pcs, &of, true, true);

				if (ox > -1)
				{
					std::string vstr;
					if (f < 0)
					{
						for (size_t x = 0; x < args.size(); x++)
						{
							if (args[x].arg.length() == 17)
							{
								vstr.append(args[x].arg.c_str());
								vstr.push_back('\n');
							}
						}
						ox = BOTFileOUT(&pcs, pcs.fst.e_loc, 0, true, BOT_RTV_STR, &vstr);
					}
					else
					{
						for (size_t x = 0; x < args.size(); x++)
						{
							bool pass = true;

							if (bot_cstrlen(ramp))
							{
								if (strcmp(&ramp[0], "?"))
								{
									if (strcmp(args[x].arg.substr(0, 5).c_str(), ramp))
									{
										pass = false;
									}
								}
							}

							if (bot_cstrlen(emp))
							{
								if (strcmp(&emp[0], "?"))
								{
									if (strcmp(args[x].arg.substr(37, 5).c_str(), emp))
									{
										pass = false;
									}
								}
							}

							if (bot_cstrlen(ftyp))
							{
								if (strcmp(&ftyp[0], "?"))
								{
									if (strcmp(args[x].arg.substr(45, 2).c_str(), ftyp))
									{
										pass = false;
									}
								}
							}

							if (bot_cstrlen(fdate))
							{
								if (strcmp(&fdate[0], "?"))
								{
									std::string datstr(fdate);

									if (datstr.length() > 8)
									{
										if (strcmp(args[x].arg.substr(29, 4).c_str(), CPunc(datstr.c_str()).substr(4, 4).c_str()))
										{
											pass = false;
										}
										if (strcmp(args[x].arg.substr(33, 4).c_str(), CPunc(datstr.c_str()).substr(0, 4).c_str()))
										{
											pass = false;
										}
									}
									else if (datstr.length() == 8)
									{
										if (strcmp(args[x].arg.substr(29, 4).c_str(), datstr.substr(3, 4).c_str()))
										{
											pass = false;
										}
										if (strcmp(args[x].arg.substr(33, 4).c_str(), datstr.substr(0, 4).c_str()))
										{
											pass = false;
										}
									}
									else {}
								}
							}

							if (pass)
							{
								vstr.append(args[x].arg.substr(5, 17).c_str());
								vstr.append("\n");
							}
						}
						ox = BOTFileOUT(&pcs, pcs.fst.e_loc, 0, true, BOT_RTV_STR, &vstr);
					}

					ret = BOTSaveFile(&pcs, BOTPathS(BOT_LDSO_NM).c_str(), true);

					if (!of)
					{
						of = BOTCloseFile(&pcs);
					}
				}
			}
		}
	}
	return ret;
}
sint machine::GetStringV(BOT_FILE_M* file_, bool as_var)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::GetStringV(BOT_FILE_M* file_(%i), bool as_var(%u))", (sint)file_, (uint)as_var);
		op = Output(outp.carr, 2);
	}

	if (!file_)
	{
		return -1;
	}

	sint ret = -1;
	sint of = -1;
	sint ox = BOTOpenFile(file_, &of, true, false, false, true);

	if (ox > -1)
	{
		std::vector<BOT_ARG> args;
		ox = ArgSep(&args, false, 0, file_->dsiz - 1, file_->datp, BOT_RTV_VCHAR, &msy.nrts_sep);

		if (!of)
		{
			of = BOTCloseFile(file_, true, false, true);
		}

		if (ox > -1)
		{
			if (as_var)
			{
				std::vector<std::string> vstr;

				for (size_t x = 0; x < args.size(); x++)
				{
					if (!args[x].arg.empty())
					{
						vstr.push_back(args[x].arg.c_str());
					}
				}

				ret = 0;
				carr_21 vnm("str_list");

				while (FVAR(vnm.carr) > -1)
				{
					bot_sprintf(vnm.carr, vnm.siz, "str_list_%i", ret++);
				}
				ret = SVAR(vnm.carr, BOT_RTV_VSTR, &vstr);
			}
		}
	}
	return ret;
}
sint machine::ProcVINList(BOT_FILE_M* file_, c_char* stmt_, c_char* ramp, c_char* date, c_char* empno, bool is_errlog)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::ProcVINList(BOT_FILE_M* file_(%i), c_char* stmt_(%i), c_char* ramp(%i), c_char* date(%i), c_char* empno(%i), bool is_errlog(%u))", (sint)file_, (sint)stmt_, (sint)ramp, (sint)date, (sint)empno, (uint)is_errlog);
		op = Output(outp.carr, 2);
	}
	if (!file_)
	{
		return -1;
	}

	sint of = -1;
	sint ox = BOTOpenFile(file_, &of);

	if (ox > -1)
	{
		std::vector<std::string> orvec;
		std::vector<std::string> ibvec;
		std::vector<std::string> vvec;
		std::vector<std::string> dvec;

		if (!is_errlog)
		{
			bool done = false;

			while (!done)
			{
				carr_32 ncar;

				if (f_con[file_->fcon]->fstrm.getline(ncar.carr, 32))
				{
					std::string istr;
					istr.append(ncar.carr);
					vvec.push_back(istr.substr(0, 17).c_str());
				}
				else
				{
					done = true;
				}
			}
		}
		else
		{
			bool done = false;

			while (!done)
			{
				carr_512 ncar;

				if (f_con[file_->fcon]->fstrm.getline(ncar.carr, 512))
				{
					std::string istr;
					istr.append(ncar.carr);

					if (istr.length() > 17 && !strcmp(istr.substr(0, 5).c_str(), "5B   "))
					{
						vvec.push_back(istr.substr(5, 17));
						ibvec.push_back(istr.substr(67, 2));
						orvec.push_back(istr.substr(96, 6));

						if (istr.length() > 192)
						{
							dvec.push_back(istr.substr(191, istr.length() - 192));
						}
						else
						{
							dvec.push_back("");
						}
					}
				}
				else
				{
					done = true;
				}
			}
		}
		if (!of)
		{
			of = BOTCloseFile(file_);
		}

		if (!vvec.empty() && is_errlog)
		{
			BOT_FILE_M pcs("vins091618_1", ".txt", BOTPathS(BOT_MOD_NM).c_str(), lid, BOT_FILE_APND);
			ox = BOTOpenFile(&pcs, &of, true, true);

			if (ox > -1)
			{
				std::vector<std::string> ovec;

				for (uint x = 0; x < vvec.size(); x++)
				{
					std::string ncar;
					sint xc = bot_sprintfs(&ncar, false, "%s", vvec[x].c_str(), vvec[x].c_str());
					ovec.push_back(ncar);
				}
				for (uint x = 0; x < ovec.size(); x++)
				{
					f_con[pcs.fcon]->fstrm << ovec[x].c_str() << std::endl;
				}
				if (!of)
				{
					BOTCloseFile(&pcs);
				}
			}
		}

		if (!vvec.empty() && strcmp(stmt_, "insert"))
		{
			BOT_FILE_M pcs("photo_script091618_1", ".txt", BOTPathS(BOT_MOD_NM).c_str(), lid, BOT_FILE_APND);
			ox = BOTOpenFile(&pcs, &of, true, true);

			if (ox > -1)
			{
				std::vector<std::string> ovec;

				for (uint x = 0; x < vvec.size(); x++)
				{
					std::string ncar;
					sint xc = bot_sprintfs(&ncar, false, "REN ?5B??????20181016%s*.* ?5B??????20180916%s*.*", vvec[x].c_str(), vvec[x].c_str());
					ovec.push_back(ncar);
				}
				for (uint x = 0; x < ovec.size(); x++)
				{
					f_con[pcs.fcon]->fstrm << ovec[x].c_str() << std::endl;
				}
				if (!of)
				{
					BOTCloseFile(&pcs);
				}
			}
		}
		if (!vvec.empty())
		{
			if (!strcmp(stmt_, "update"))
			{
				BOT_FILE_M pcs("upd_1_090718_2", ".txt", BOTPathS(BOT_MOD_NM).c_str(), lid, BOT_FILE_APND);
				ox = BOTOpenFile(&pcs, &of, true, true);

				if (ox > -1)
				{
					std::string upd("update vehicleadmin.inspect\n set insptype='04'\n where ramp='MT002'\n and insptype='08'\n and inspdate=to_date('09/07/2018','mm/dd/yyyy')\n and vin in(\n");

					for (uint x = 0; x < vvec.size(); x++)
					{
						std::string str;

						if (x < vvec.size() - 1)
						{
							upd.append("'");
							upd.append(vvec[x].c_str());
							upd.append("',\n");
						}
						else
						{
							upd.append("'");
							upd.append(vvec[x].c_str());
							upd.append("'\n);");
						}
					}

					f_con[pcs.fcon]->fstrm << upd << std::endl;

					if (!of)
					{
						ox = BOTCloseFile(&pcs);
					}
				}
			}
			else if (!strcmp(stmt_, "insert"))
			{
				BOT_FILE_M pcs("ins_1_062918_1", ".txt", BOTPathS(BOT_MOD_NM).c_str(), lid, BOT_FILE_APND);
				ox = BOTOpenFile(&pcs, &of, true, true);

				if (ox > -1)
				{
					std::string upd;

					for (uint x = 0; x < vvec.size(); x++)
					{
						carr_1024 ncar;
						ox = bot_sprintf(ncar.carr, ncar.siz, "insert into vehicleadmin.inspect (vin,ramp,insptype,inspdate,empno,val1,val2) values ('%s','ALTAL','02',to_date('05/04/2018','mm/dd/yyyy'),'00277','%s','%s');\n", vvec[x].c_str(), ibvec[x].c_str(), orvec[x].c_str());
						upd.append(ncar.carr);
					}

					f_con[pcs.fcon]->fstrm << upd << std::endl;

					if (!of)
					{
						ox = BOTCloseFile(&pcs);
					}
				}
			}
			else {}
		}
		if (!vvec.empty())
		{
			if (!strcmp(stmt_, "update"))
			{
				BOT_FILE_M pcs("upd_2_090718_2", ".txt", BOTPathS(BOT_MOD_NM).c_str(), lid, BOT_FILE_APND);
				ox = BOTOpenFile(&pcs, &of, true, true);

				if (ox > -1)
				{
					std::string upd("update vehicleadmin.damage\n set insptype='04'\n where ramp='MT002'\n and insptype='08'\n and inspdate=to_date('09/07/2018','mm/dd/yyyy')\n and vin in(\n");

					for (uint x = 0; x < vvec.size(); x++)
					{
						std::string str;

						if (x < vvec.size() - 1)
						{
							upd.append("'");
							upd.append(vvec[x].c_str());
							upd.append("',\n");
						}
						else
						{
							upd.append("'");
							upd.append(vvec[x].c_str());
							upd.append("'\n);");
						}
					}

					f_con[pcs.fcon]->fstrm << upd.c_str() << std::endl;

					if (!of)
					{
						BOTCloseFile(&pcs);
					}
				}
			}
			else if (!strcmp(stmt_, "insert"))
			{
				BOT_FILE_M pcs("ins_2_062918_1", ".txt", BOTPathS(BOT_MOD_NM).c_str(), lid, BOT_FILE_APND);
				ox = BOTOpenFile(&pcs, &of, true, true);

				if (ox > -1)
				{
					std::string upd;

					for (uint x = 0; x < vvec.size(); x++)
					{
						std::string str;
						for (uint y = 0; y < dvec[x].length(); y += 9)
						{
							if (!dvec[x].empty())
							{
								str.append(dvec[x].substr(y, 9));
								carr_1024 ncar;
								ox = bot_sprintf(ncar.carr, ncar.siz, "insert into vehicleadmin.damage (vin,ramp,insptype,inspdate,dmg) values (%s,'ALTAL','02',to_date('05/04/2018','mm/dd/yyyy',%s));\n", vvec[x].c_str(), str.c_str());
								upd.append(ncar.carr);
							}
						}
					}

					f_con[pcs.fcon]->fstrm << upd << std::endl;

					if (!of)
					{
						ox = BOTCloseFile(&pcs);
					}
				}
			}
			else {}
		}
		return 0;
	}
	return -1;
}

// Fork

sint machine::BOTFork(bot_proc* np, _char* cl, _char* cdir)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTFork(bot_proc* np(%i), _char* cl(%i), _char* cdir(%i))", (sint)np, (sint)cl, (sint)cdir);
		op = Output(outp.carr, 2);
	}

	sint ret = -1;
	size_t ln = np->anm.length();

	if (ln > 4096)
	{
		return -1;
	}

	ln = bot_strlen(cl);

	if (ln > 32768)
	{
		return -1;
	}

	BOT_FILE_M ef(np->anm.c_str(), "", "", 0, BOT_EXE_CON);
	sint ox = -1;
	ret = BOTOpenFile(&ef, &ox, false, false, false, true, cl, &np);

	if (ret > -1)
	{
#ifdef _WIN32
#ifdef UNICODE
		if (!CreateProcessW(np->anm.c_str(), cl, NULL, NULL, false, np->f, np->env, 0, &np->sinfo, &np->pinfo))
		{
			carr_256 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz, "CreateProcessW Error: %u", GetLastError());
			oc = Output(0, true, xcar.carr, 2, 0);
			return -1;
		}
#else
		if (!CreateProcessA(np->anm.c_str(), cl, NULL, NULL, false, np->f, np->env, 0, &np->sinfo, &np->pinfo))
		{
			carr_256 xcar;
			sint oc = bot_sprintf(xcar.carr, xcar.siz, "CreateProcess Error: %u", GetLastError());
			oc = Output(0, true, xcar.carr, 2, 0);
			return -1;
		}
		np->pid = np->pinfo.dwProcessId;
#endif
#else
		ret = fork();

		if (ret > 0)
		{
			np->pid = ret;

			if (np->env)
			{
				ret = execve(BOTFileStr(mfile_).c_str(), mfile_->datp, np->env);
			}
			else
			{
				ret = execv(BOTFileStr(mfile_).c_str(), mfile_->datp);
			}
		}
#endif
		ret = PushToVec((void*)np, MTX_PRC, false, true, false);
	}
	return ret;
}
sint machine::BOTUnFork(bot_proc* np, ulint wt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTUnFork(bot_proc* np(%i), ulint wt(%lu))", (sint)np, wt);
		op = Output(outp.carr, 2);
	}

	if (!np)
	{
		return -1;
	}

	sint ret = -1;

#ifdef _WIN32
	if (PostThreadMessage(np->pinfo.dwThreadId, WM_QUIT, 0, 0))
	{
		WaitForSingleObject(np->pinfo.hProcess, wt);
		ret = 0;
	}
#else
	return kill(np->pid, SIGTRM);
#endif
	return ret;
}

// Monitor

sint machine::BOTMonitor()
{
	if (debug_lvl >= 1 && debug_m)
	{
		sint op = Output("BOTMonitor()", 2);
	}

	sint ret = -1;
	bool done = false;
	ret = Output("Monitoring...", 2, 0);
	
	while (!done)
	{
		bot_session ses;
		BOT_STMT q(false, 0, "litebot", "SESSION", 1, &ses);
		q.spec = 0;
		q.AddCond("", "NAME", "=", EStr("win_LITEBot").c_str());
		ret = Query(&q, BOT_RTV_SES);

		if (ret > -1)
		{
			if (ses.id > -1)
			{
				if (!ses.quit)
				{
					sllint diff = ses.last_maint - ses.last_mod;

					if (diff > 30)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							sint op = Output("main program has ceased responding; attempting to restart...", 2);
						}
						//bot_proc xp("win_LITEBot", CREATE_NEW_CONSOLE, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
						//BOTFork(&xp);
					}
					else
					{
						q.Renew(true, 1, "litebot", "SESSION", 1);
						q.AddCond("", "NAME", "=", EStr("win_LITEBot").c_str());
						ret = Commit(&q);
					}
				}
				else
				{
					done = true;
				}
			}
			else
			{
				done = true;
			}
		}
		if (!done)
		{
			sllint rst = Rest(BOT_MILLI_REST * 10000);
		}
	}
	ret = SetThreadQuit(1);
	return ret;
}

// Start/End Session

sint machine::BOTStartSession(slint pid)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTStartSession(slint pid(%li))", pid);
		op = Output(outp.carr, 2);
	}
	sint ret = -1;
	bot_session ses((_char*)BOTSessionName().c_str());
	BOT_STMT q(false, 0, "litebot", "SESSION", 1, &ses);
	q.spec = 0;
	q.AddCond("", "NAME", "=", EStr(ses.nm.carr).c_str());
	ret = Query(&q, BOT_RTV_SES);

	if (ret > -1)
	{
		q.Renew(false, 1, "litebot", "SESSION", 1);

		if (ses.id < 0)
		{
			q.it_type = 2;
			q.AddCol("NAME", EStr(ses.nm.carr).c_str());
		}
		carr_21 xcar;
		bot_sprintf(xcar.carr, xcar.siz, "%li", pid);
		q.AddCol("PID", xcar.carr);
		q.AddCol("QUIT", "0");
		q.AddCond("", "NAME", "=", EStr(ses.nm.carr).c_str());
		ret = Commit(&q);
	}
	return ret;
}
std::string machine::BOTSessionName()
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_32 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTSessionName()");
		op = Output(outp.carr, 2);
	}
	std::string nnm;
	sint ox = -1;
	sint hx = LockGMutex(MTX_SES, &ox);

	if (hx > -1)
	{
		nnm.append(bot_ses.nm.carr);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_SES);
		}
	}
	return nnm;
}
sint machine::BOTSetSessionName(c_char* nm)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTSetSessionName(c_char* nm(%i))", (sint)nm);
		op = Output(outp.carr, 2);
	}
	sint ox = -1;
	sint hx = LockGMutex(MTX_SES, &ox);

	if (hx > -1)
	{
		hx = bot_sprintf(bot_ses.nm.carr, bot_ses.nm.siz, "%s", nm);

		if (!ox)
		{
			ox = UnlockGMutex(MTX_SES);
		}
	}
	return hx;
}
sint machine::BOTEndSession(slint pid)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTEndSession(slint pid(%li))", pid);
		op = Output(outp.carr, 2);
	}
	sint ret = -1;
	bot_session ses((_char*)BOTSessionName().c_str());
	BOT_STMT q(false, 0, "litebot", "SESSION", 1, &ses);
	q.AddCond("", "NAME", "=", EStr(ses.nm.carr).c_str());
	ret = Query(&q, BOT_RTV_SES);

	if (ret > -1)
	{
		q.Renew(false, 1, "litebot", "SESSION", 1);
		carr_21 xcar;
		bot_sprintf(xcar.carr, xcar.siz, "%li", pid);
		q.AddCol("PID", xcar.carr);
		q.AddCol("QUIT", "1");
		q.AddCond("", "NAME", "=", EStr(ses.nm.carr).c_str());
		ret = Commit(&q);
	}
	return ret;
}

// Network Functions

sint machine::SType(c_char* inv)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::SType(c_char* inv(%i))", (sint)inv);
		op = Output(outp.carr, 2);
	}
	if (!inv)
	{
		return -1;
	}
	sint stype = -1;

	if (!strcmp(UCASE(inv).c_str(), "TCP"))
	{
		stype = SOCK_STREAM;
	}
	else if (!strcmp(UCASE(inv).c_str(), "UDP"))
	{
		stype = SOCK_DGRAM;
	}
	else if (!strcmp(UCASE(inv).c_str(), "RAW"))
	{
		stype = SOCK_RAW;
	}
	else if (!strcmp(UCASE(inv).c_str(), "PGM"))
	{
		stype = SOCK_RDM;
	}
	else {}
	return stype;
}
sint machine::StartConnection(std::vector<ullint>* vals, sint opt)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::StartConnection(std::vector<ullint>* vals(%i), sint opt(%i))", (sint)vals, opt);
		op = Output(outp.carr, 2);
	}
	if (!vals)
	{
		return -1;
	}
	if (vals->empty())
	{
		return -1;
	}

	if (opt > 0)
	{
		std::string snm("Serv_");

		if (vals->at(0) == (ullint)SOCK_STREAM)
		{
			bot_sprintfs(&snm, false, "TCP_S");
		}
		else if (vals->at(0) == (ullint)SOCK_DGRAM)
		{
			bot_sprintfs(&snm, false, "UDP_S");
		}
		else if (vals->at(0) == (ullint)SOCK_RAW)
		{
			bot_sprintfs(&snm, false, "RAW_S");
		}
		else if (vals->at(0) == (ullint)SOCK_RDM)
		{
			bot_sprintfs(&snm, false, "RDM_S");
		}
		else
		{
			return -1;
		}

		TINFO_M thr((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServS, lid, 0.0f, vals);
		sint xc = GetInVec(&thr, MTX_TTS);

		if (xc < 0)
		{
			thr.Renew((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServS, lid, 0.0f, vals);
			xc = InitThread(&thr);
		}
	}
	if (!opt || opt > 1)
	{
		std::string snm("Serv_");

		if (vals->at(0) == (ullint)SOCK_STREAM)
		{
			bot_sprintfs(&snm, false, "TCP_R");
		}
		else if (vals->at(0) == (ullint)SOCK_DGRAM)
		{
			bot_sprintfs(&snm, false, "UDP_R");
		}
		else if (vals->at(0) == (ullint)SOCK_RAW)
		{
			bot_sprintfs(&snm, false, "RAW_R");
		}
		else if (vals->at(0) == (ullint)SOCK_RDM)
		{
			bot_sprintfs(&snm, false, "RDM_R");
		}
		else
		{
			return -1;
		}

		TINFO_M thr((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServR, lid, 0.0f, vals);
		sint xc = GetInVec(&thr, MTX_TTS);

		if (xc < 0)
		{
			for (sint ct = 0; ct < 3; ct++)
			{
				thr.Renew((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServR, lid, 0.0f, vals);
				xc = InitThread(&thr);
			}
		}

		snm.clear();
		snm.append("Serv_");

		if (vals->at(0) == (ullint)SOCK_STREAM)
		{
			bot_sprintfs(&snm, false, "TCP_P");
		}
		else if (vals->at(0) == (ullint)SOCK_DGRAM)
		{
			bot_sprintfs(&snm, false, "UDP_P");
		}
		else if (vals->at(0) == (ullint)SOCK_RAW)
		{
			bot_sprintfs(&snm, false, "RAW_P");
		}
		else if (vals->at(0) == (ullint)SOCK_RDM)
		{
			bot_sprintfs(&snm, false, "RDM_P");
		}
		else
		{
			return -1;
		}

		thr.Renew((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServP, lid, 1.0f, vals);
		xc = GetInVec(&thr, MTX_TTS);

		if (xc < 0)
		{
			thr.Renew((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServP, lid, 1.0f, vals);
			xc = InitThread(&thr);
		}
	}
	return 0;
}
sint machine::CloseConnection(sint stype, sint opt, sint portn)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::CloseConnection(sint stype(%i), sint opt(%i), sint portn(%i))", stype, opt, portn);
		op = Output(outp.carr, 2);
	}
	if (stype < 0 || opt < 0 || portn < 0)
	{
		return -1;
	}

	sint ret = -1;

	if (!stype)
	{
		sint close = 2;
		bot_port n;
		sint xc = 0;

		while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
		{
			if (n.portn == portn)
			{
				ret = SetVecEleMem((void*)&close, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
				ret = closesocket(n.sck);
				n.sck = -1;
				ret = SetVecEleMem((void*)&n.sck, MTX_PORTS, n.lid, BOT_PORT_SCK, false);
			}
		}
	}
	else
	{
		if (opt > 0)
		{
			sint close = 2;
			bot_port n;
			sint xc = 0;

			while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
			{
				if (n.portn == portn && n.stype == stype && n.bndp == false)
				{
					ret = SetVecEleMem((void*)&close, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
					ret = closesocket(n.sck);
					n.sck = -1;
					ret = SetVecEleMem((void*)&n.sck, MTX_PORTS, n.lid, BOT_PORT_SCK, false);
				}
			}
		}
		if (!opt || opt > 1)
		{
			sint close = 2;
			bot_port n;
			sint xc = 0;

			while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
			{
				if (n.portn == portn && n.stype == stype && n.bndp == true)
				{
					ret = SetVecEleMem((void*)&close, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
					ret = closesocket(n.sck);
					n.sck = -1;
					ret = SetVecEleMem((void*)&n.sck, MTX_PORTS, n.lid, BOT_PORT_SCK, false);
				}
			}
		}
	}
	return ret;
}
sint machine::ConnectionStatus(sint stype, sint opt, sint portn)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::ConnectionStatus(sint stype(%i), sint opt(%i), sint portn(%i))", stype, opt, portn);
		op = Output(outp.carr, 2);
	}
	if (stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint xc = 0;
	bot_port n;

	while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
	{
		if (opt > 0)
		{
			if (n.portn == portn && n.stype == stype && n.bndp == false)
			{
				return n.signal;
			}
		}
		if (!opt || opt > 1)
		{
			if (n.portn == portn && n.stype == stype && n.bndp == true)
			{
				return n.signal;
			}
		}
	}
	return -1;
}/*
sint machine::PauseConnection(sint stype, sint opt, sint portn)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::PauseConnection(sint stype(%i), sint opt(%i), sint portn(%i))", stype, opt, portn);
		op = Output(outp.carr, 2);
	}

	if (stype < 0 || stype >= BOT_SCKT_MAX || portn < 0)
	{
		return -1;
	}

	sint ret = -1;

	if (opt > 0)
	{
		sint pause = 1;
		bot_port n;
		sint xc = 0;

		while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
		{
			if (n.portn == portn && n.stype == stype && n.bndp == false)
			{
				ret = SetVecEleMem((void*)&pause, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
				ret = closesocket(n.sck);
				n.sck = -1;
				ret = SetVecEleMem((void*)&n.sck, MTX_PORTS, n.lid, BOT_PORT_SCK, false);
			}
		}
	}
	if (!opt || opt > 1)
	{
		sint pause = 1;
		bot_port n;
		sint xc = 0;

		while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
		{
			if (n.portn == portn && n.stype == stype && n.bndp == true)
			{
				ret = SetVecEleMem((void*)&pause, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
				ret = closesocket(n.sck);
				n.sck = -1;
				ret = SetVecEleMem((void*)&n.sck, MTX_PORTS, n.lid, BOT_PORT_SCK, false);
			}
		}
	}
	return ret;
}
sint machine::UnPauseConnection(sint stype, sint opt, sint portn)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::UnPauseConnection(sint stype(%i), sint opt(%i), sint portn(%i))", stype, opt, portn);
		op = Output(outp.carr, 2);
	}

	if (stype < 0 || stype >= BOT_SCKT_MAX || portn < 0)
	{
		return -1;
	}

	sint ret = -1;

	if (opt > 0)
	{
		sint pause = 0;
		bot_port n;
		sint xc = 0;

		while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
		{
			if (n.portn == portn && n.stype == stype && n.bndp == false)
			{
				ret = SetVecEleMem((void*)&pause, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
			}
		}
	}
	if (!opt || opt > 1)
	{
		sint pause = 0;
		bot_port n;
		sint xc = 0;

		while (GetVecEle((void*)&n, MTX_PORTS, xc++, false) > -1)
		{
			if (n.portn == portn && n.stype == stype && n.bndp == true)
			{
				ret = SetVecEleMem((void*)&pause, MTX_PORTS, n.lid, BOT_PORT_SIG, false);
			}
		}
	}
	return ret;
}*/
sint machine::BOTNCon(c_char* addr, c_char* port, sint type)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTNCon(c_char* addr(%i), c_char* port(%i), sint type(%i))", (sint)addr, (sint)port, type);
		op = Output(outp.carr, 2);
	}
	if (!addr || type < 0)
	{
		return -1;
	}

	sint ret = -1;
	bot_plug clp(addr, port, type, AF_UNSPEC);
	sint xc = clp.Open(0);

	if (xc)
	{
		carr_256 outp;
		xc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
		xc = Output(0, true, outp.carr, 1, 0);
	}
	else
	{
		xc = clp.Sock(false);

		if (xc)
		{
			clp.Close();
			carr_256 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
			oc = Output(0, true, outp.carr, 1, 0);
		}
		else
		{
			uint sopt = 10000;
			xc = clp.AddSOpt(SOL_SOCKET, SO_RCVTIMEO, (_char*)&sopt, sizeof(sopt));

			if (clp.prt.stype != SOCK_DGRAM)
			{
				xc = clp.Conn();

				if (xc)
				{
					clp.Close();
					carr_256 outp;
					sint oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}
			}

			if (xc > -1)
			{
				bot_port lport;

				for (sint i = 0; i > -1; i++)
				{
					GetVecEle((void*)&lport, MTX_PORTS, i, false);

					if (lport.bndp && lport.stype == type && lport.sck != INVALID_SOCKET)
					{
						i = -2;
					}
				}
				clp.prt.rport = lport.portn;
				xc = PushToVec((void*)&clp.prt, MTX_PORTS, false, true, false);
				BOT_HDR_PKT pkt((_char)BOT_OP_KNK, (size_t)lport.portn, KeyACGen());
				sllint xret = clp.Send((_char*)&pkt, sizeof(BOT_HDR_PKT));

				if (xret < 0)
				{
					clp.Close();
					sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
					carr_256 outp;
					oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}
				
				carr_32 indat;
				xret = clp.Rec(indat.carr, sizeof(BOT_HDR_PKT));

				if (xret < 0)
				{
					clp.Close();
					sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
					carr_256 outp;
					oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}

				pkt = *(reinterpret_cast<BOT_HDR_PKT*>(indat.carr));
				xc = KeyAClientProcII(&pkt.ka);
				xret = clp.Send((_char*)&pkt, sizeof(BOT_HDR_PKT));

				if (xret < 0)
				{
					clp.Close();
					sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
					carr_256 outp;
					oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}

				bot_strclr(indat.carr);
				xret = clp.Rec(indat.carr, sizeof(BOT_HDR_PKT));

				if (xret < 0)
				{
					clp.Close();
					sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
					carr_256 outp;
					oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}

				pkt = *(reinterpret_cast<BOT_HDR_PKT*>(indat.carr));

				if (pkt.op[0] == (_char)BOT_OP_ESTA)
				{
					xc = KeyAClientProcII(&pkt.ka);
					clp.prt.key_a = pkt.ka;
					xc = SetVecEle(&clp.prt, MTX_PORTS, clp.prt.lid, false, false);
					carr_256 cipstr;
					xc = bot_sprintf(cipstr.carr, cipstr.siz, "%s %i %i", clp.prt.ipstr.carr, clp.prt.portn, clp.prt.stype);
					xc = PushToVec(&cipstr, MTX_CIPS, true, true, false);
					BOT_CLIENT_M isc;
					ret = GetClientByPort(&isc, clp.prt.ipstr.carr, lport.portn, lport.stype);

					if (ret < 0)
					{
						std::string str;
						xc = Input("user: ", &str, false);

						if (!str.empty())
						{
							bot_vblko oblk((_char)BOT_OP_ESTA, addr, port, 1);
							bot_vblko pblk((_char)BOT_OP_ESTB, addr, port, 1);
							oblk.Add(0, BOT_RTV_STR, &str, BOT_RTV_MAX);
							str.clear();
							xc = AddSVPKO(type, &oblk);

							while (str.length() < 5 || str.length() > 255)
							{
								xc = Input("password: ", &str, false);

								if (str.length() > 5 && str.length() < 256)
								{
									pblk.Add(0, BOT_RTV_STR, &str, BOT_RTV_MAX);
									xc = AddSVPKO(type, &pblk);
								}
							}

							for (sllint rst = 0; rst < 10000 && isc.lid < 0; rst += Rest(BOT_MILLI_REST))
							{
								ret = GetClientByPort(&isc, clp.prt.ipstr.carr, lport.portn, lport.stype);
							}

							if (isc.lid < 0)
							{
								ret = -1;
							}
							else
							{
								if (debug_lvl >= 1 && debug_m)
								{
									carr_128 outp;
									sint rc = bot_sprintf(outp.carr, outp.siz, "logged in to server at: (%s) port(%i)", clp.prt.ipstr.carr, clp.prt.portn);
									rc = Output(0, true, outp.carr, 2, 0);
								}
								ret = 0;
							}
							bot_strclr(indat.carr);
						}
						else
						{
							xc = GetInVec((void*)&cipstr, MTX_CIPS, false, false);
							xc = ClearVecEle(MTX_CIPS, xc, false);
							pkt.op[0] = BOT_OP_CLS;
							xret = clp.Send((_char*)&pkt, sizeof(BOT_HDR_PKT));

							if (xret < 0)
							{
								clp.Close();
								sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
								carr_256 outp;
								oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
								oc = Output(0, true, outp.carr, 1, 0);
							}
						}
					}
					bot_strclr(indat.carr, indat.siz);
				}
			}
		}
		clp.Close();
	}
	return ret;
}
sint machine::BOTXNCon(c_char* addr, c_char* port, sint type)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BOTXNCon(c_char* addr(%i), c_char* port(%i), sint type(%i))", (sint)addr, (sint)port, type);
		op = Output(outp.carr, 2);
	}
	if (!addr || type < 0)
	{
		return -1;
	}

	sint ret = -1;
	bot_plug clp(addr, port, type, AF_UNSPEC);
	sint xc = clp.Open(0);

	if (xc)
	{
		carr_256 outp;
		xc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
		xc = Output(0, true, outp.carr, 1, 0);
	}
	else
	{
		xc = GetInVec((void*)&clp.prt, MTX_PORTS, false, false);
		xc = clp.Sock(false);

		if (xc)
		{
			clp.Close();
			carr_256 outp;
			sint oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
			oc = Output(0, true, outp.carr, 1, 0);
		}
		else
		{
			if (clp.prt.stype != SOCK_DGRAM)
			{
				xc = clp.Conn();

				if (xc)
				{
					clp.Close();
					carr_256 outp;
					sint oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}
			}

			if (xc > -1)
			{
				BOT_HDR_PKT pkt((_char)BOT_OP_CLS, 0, 0);
				sllint xret = clp.Send((_char*)&pkt, sizeof(BOT_HDR_PKT));

				if (xret < 0)
				{
					clp.Close();
					sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
					carr_256 outp;
					oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}

				carr_32 indat;
				uint sopt = 10000;
				xc = clp.AddSOpt(SOL_SOCKET, SO_RCVTIMEO, (_char*)&sopt, sizeof(sopt));
				xret = clp.Rec(indat.carr, sizeof(_char));

				if (xret < 0)
				{
					clp.Close();
					sint oc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
					carr_256 outp;
					oc = bot_sprintf(outp.carr, outp.siz, "Error:%s", clp.emsg.carr);
					oc = Output(0, true, outp.carr, 1, 0);
				}

				carr_256 cipstr;
				xc = bot_sprintf(cipstr.carr, cipstr.siz, "%s %i %i", clp.prt.ipstr.carr, clp.prt.portn, clp.prt.stype);
				clp.Close();
				xc = ClearVecEle(MTX_PORTS, clp.prt.lid, false);
				xc = GetInVec(&cipstr, MTX_CIPS, false, false);
				xc = ClearVecEle(MTX_CIPS, xc, false);
				ret = 0;
				BOT_CLIENT cli;
				while (GetVecEle((void*)&cli, MTX_CV, ret++, false) > -1)
				{
					if (cli.prt.rport == clp.prt.portn && !strcmp("serv", cli.name.c_str()) && cli.prt.stype == type)
					{
						ret = ClearVecEle(MTX_CV, cli.lid, false);
					}
				}
				ret = 0;
			}
		}
	}
	return ret;
}
slint machine::KeyACGen()
{
	if (debug_lvl >= 100 && debug_m)
	{
		sint op = Output("::KeyACGen()", 2);
	}
	slint ret = 0;

	switch (ses_date.carr[3])
	{
	case '0':
	{
		ret = (slint)(9613);
		break;
	}
	case '1':
	{
		ret = (slint)(1367);
		break;
	}
	case '2':
	{
		ret = (slint)(737);
		break;
	}
	case '3':
	{
		ret = (slint)(244);
		break;
	}
	case '4':
	{
		ret = (slint)(1316);
		break;
	}
	case '5':
	{
		ret = (slint)(2474);
		break;
	}
	case '6':
	{
		ret = (slint)(426);
		break;
	}
	case '7':
	{
		ret = (slint)(23);
		break;
	}
	case '8':
	{
		ret = (slint)(48346);
		break;
	}
	case '9':
	{
		ret = (slint)(4247);
		break;
	}
	default:
	{
		return -1;
		break;
	}
	}
	return ret;
}
sint machine::KeyAServR(slint* in)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::KeyAServR(slint* in(%i))", (sint)in);
		op = Output(outp.carr, 2);
	}
	if (!in)
	{
		return -1;
	}

	*in = ntohl(*in);

	switch (ses_date.carr[3])
	{
	case '0':
	{
		if (*in == 9613)
		{
			return 0;
		}
		break;
	}
	case '1':
	{
		if (*in == 1367)
		{
			return 0;
		}
		break;
	}
	case '2':
	{
		if (*in == 737)
		{
			return 0;
		}
		break;
	}
	case '3':
	{
		if (*in == 244)
		{
			return 0;
		}
		break;
	}
	case '4':
	{
		if (*in == 1316)
		{
			return 0;
		}
		break;
	}
	case '5':
	{
		if (*in == 2474)
		{
			return 0;
		}
		break;
	}
	case '6':
	{
		if (*in == 426)
		{
			return 0;
		}
		break;
	}
	case '7':
	{
		if (*in == 23)
		{
			return 0;
		}
		break;
	}
	case '8':
	{
		if (*in == 48346)
		{
			return 0;
		}
		break;
	}
	case '9':
	{
		if (*in == 4247)
		{
			return 0;
		}
		break;
	}
	default:
	{
		return -1;
		break;
	}
	}
	return -1;
}
sint machine::KeyAServCreateII(slint* in)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::KeyAServCreateII(slint* in(%i))", (sint)in);
		op = Output(outp.carr, 2);
	}
	if (!in)
	{
		return -1;
	}

	switch (ses_date.carr[3])
	{
	case '0':
	{
		srand(23);
		break;
	}
	case '1':
	{
		srand(1378);
		break;
	}
	case '2':
	{
		srand(238);
		break;
	}
	case '3':
	{
		srand(7597);
		break;
	}
	case '4':
	{
		srand(4387);
		break;
	}
	case '5':
	{
		srand(453);
		break;
	}
	case '6':
	{
		srand(3758);
		break;
	}
	case '7':
	{
		srand(79157);
		break;
	}
	case '8':
	{
		srand(2648);
		break;
	}
	case '9':
	{
		srand(907);
		break;
	}
	default:
	{
		return -1;
		break;
	}
	}
	*in = (slint)(rand()) * 1000;
	return 0;
}
sint machine::KeyAClientProcII(slint* in)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::KeyAClientProcII(slint* in(%i)))", (sint)in);
		op = Output(outp.carr, 2);
	}
	if (!in)
	{
		return -1;
	}

	*in = ntohl(*in);

	switch (ses_date.carr[2])
	{
	case '0':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			*in /= 2;
			break;
		}
		case '1':
		{
			*in += 1;
			break;
		}
		case '2':
		{
			*in -= 13;
			break;
		}
		case '3':
		{
			*in *= 2;
			break;
		}
		case '4':
		{
			*in += 15;
			break;
		}
		case '5':
		{
			*in -= 1;
			break;
		}
		case '6':
		{
			break;
		}
		case '7':
		{
			*in += 11;
			break;
		}
		case '8':
		{
			*in -= 21;
			break;
		}
		case '9':
		{
			*in += 19;
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		break;
	}
	case '1':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			*in -= 2362;
			break;
		}
		case '1':
		{
			*in += 11;
			break;
		}
		case '2':
		{
			*in /= 2;
			break;
		}
		case '3':
		{
			*in += 2;
			break;
		}
		case '4':
		{
			*in -= 15;
			break;
		}
		case '5':
		{
			*in -= 321;
			break;
		}
		case '6':
		{
			*in -= 54;
			break;
		}
		case '7':
		{
			*in += 101;
			break;
		}
		case '8':
		{
			*in -= 1;
			break;
		}
		case '9':
		{
			*in += 19;
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		break;
	}
	case '2':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			*in /= 2;
			break;
		}
		case '1':
		{
			*in += 1;
			break;
		}
		case '2':
		{
			*in -= 13;
			break;
		}
		case '3':
		{
			*in += 2;
			break;
		}
		case '4':
		{
			*in += 15;
			break;
		}
		case '5':
		{
			*in -= 1;
			break;
		}
		case '6':
		{
			*in = 23956;
			break;
		}
		case '7':
		{
			*in += 11;
			break;
		}
		case '8':
		{
			*in += 21;
			break;
		}
		case '9':
		{
			*in = 109;
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		break;
	}
	case '3':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			*in += 21;
			break;
		}
		case '1':
		{
			*in -= 41;
			break;
		}
		case '2':
		{
			*in += 136;
			break;
		}
		case '3':
		{
			*in = 222;
			break;
		}
		case '4':
		{
			*in += 120;
			break;
		}
		case '5':
		{
			*in -= 1111;
			break;
		}
		case '6':
		{
			*in -= 1211;
			break;
		}
		case '7':
		{
			*in += 1361;
			break;
		}
		case '8':
		{
			*in -= 234;
			break;
		}
		case '9':
		{
			*in += 6959;
			break;
		}
		default:
		{
			return -1;
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
	
	*in = htonl(*in);
	return 0;
}
sint machine::KeyAServRecII(slint* in, slint* prt)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::KeyAServRecII(slint* in(%li), slint* prt(%li))", (sint)in, (sint)prt);
		op = Output(outp.carr, 2);
	}
	if (!in || !prt)
	{
		return -1;
	}

	sint ret = -1;
	*in = ntohl(*in);

	switch (ses_date.carr[2])
	{
	case '0':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			if (*in * 2 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '1':
		{
			if (*in - 1 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '2':
		{
			if (*in + 13 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '3':
		{
			if (*in / 2 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '4':
		{
			if (*in - 15 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '5':
		{
			if (*in + 1 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '6':
		{
			if (*in == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '7':
		{
			if (*in - 11 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '8':
		{
			if (*in + 21 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '9':
		{
			if (*in - 19 == *prt)
			{
				ret = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
		if (!ret)
		{
			KeyAServCreateII(in);
			*prt = *in;
			*in = htonl(*in);
		}
		break;
	}
	case '1':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			if (*in + 2362 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '1':
		{
			if (*in - 11 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '2':
		{
			if (*in * 2 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '3':
		{
			if (*in - 2 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '4':
		{
			if (*in + 15 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '5':
		{
			if (*in + 321 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '6':
		{
			if (*in + 54 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '7':
		{
			if (*in - 101 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '8':
		{
			if (*in + 1 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '9':
		{
			if (*in - 19 == *prt)
			{
				ret = 0;
			}
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		if (!ret)
		{
			KeyAServCreateII(in);
			*prt = *in;
			*in = htonl(*in);
		}
		break;
	}
	case '2':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			if (*in * 2 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '1':
		{
			if (*in - 1 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '2':
		{
			if (*in + 13 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '3':
		{
			if (*in - 2 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '4':
		{
			if (*in - 15 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '5':
		{
			if (*in + 1 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '6':
		{
			if (*in == 23956)
			{
				ret = 0;
			}
			break;
		}
		case '7':
		{
			if (*in - 11 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '8':
		{
			if (*in - 21 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '9':
		{
			if (*in == 109)
			{
				ret = 0;
			}
			break;
		}
		default:
		{
			return -1;
			break;
		}
		}
		if (!ret)
		{
			KeyAServCreateII(in);
			*prt = *in;
			*in = htonl(*in);
		}
		break;
	}
	case '3':
	{
		switch (ses_date.carr[3])
		{
		case '0':
		{
			if (*in - 21 == *prt)
			{
				ret = 0;
			}
			break;
		}
		case '1':
		{
			if (*in + 41 == *prt)
			{
				ret = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
		if (!ret)
		{
			KeyAServCreateII(in);
			*prt = *in;
			*in = htonl(*in);
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
sint machine::BanIP(c_char* ipstr, c_char* note)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_96 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::BanIP(c_char* ipstr(%i), c_char* note(%i))", (sint)ipstr, (sint)note);
		op = Output(outp.carr, 2);
	}
	if (!ipstr)
	{
		return -1;
	}
	sint xc = -1;
	std::string rstr;
	BOT_STMT t(false, 0, "litebot", "BIPS", 1, &rstr);
	t.spec = 0;
	xc = t.AddCol("ADR", "", true);
	xc = t.AddCond("", "ADR", "=", EStr(ipstr).c_str());
	xc = Query(&t, BOT_RTV_STR);

	if (xc > -1)
	{
		if (!rstr.empty())
		{
			xc = 1;
		}
		else
		{
			std::vector<BOT_STMT> tvec;
			bot_plug bp(ipstr, "", SOCK_DGRAM, AF_UNSPEC);
			xc = bp.Open(AI_PASSIVE);

			if (xc > -1)
			{
				while (xc > -1)
				{
					t.Renew(false, 2, "litebot", "BIPS", 1);
					t.spec = 2;
					t.AddCol("ADR", EStr(bp.prt.ipstr.carr).c_str());

					if (note)
					{
						t.AddCol("NOTE", EStr(note).c_str());
					}

					carr_32 ndat;
					xc = BOTDate(ndat.carr, ndat.siz);
					t.AddCol("DATE", EStr(ndat.carr).c_str());
					xc = vtool.AVTV(&tvec, &t, true, true);
					xc = bp.Next();
				}

				bp.Close();
				xc = Commit(&tvec);

				if (xc < 0)
				{
					sint oc = Output(0, true, "Failed to commit banned ip", 1, 0);
				}
				else
				{
					carr_256 ncar;
					sint oc = bot_sprintf(ncar.carr, ncar.siz, "Added ip (%s) to banned list.", ipstr);
					oc = Output(0, true, ncar.carr, 2);
				}
			}
			else
			{
				sint oc = Output(0, true, "Failed to find banned ip", 1, 0);
			}
		}
	}
	return xc;
}
sint machine::UnbanIP(c_char* ipstr)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::UnbanIP(c_char* ipstr(%i))", (sint)ipstr);
		op = Output(outp.carr, 2);
	}
	if (!ipstr)
	{
		return -1;
	}
	sint xc = -1;
	std::string rstr;
	BOT_STMT t(false, 0, "litebot", "BIPS", 1, &rstr);
	t.spec = 0;
	xc = t.AddCol("ADR", "", true);
	xc = t.AddCond("", "ADR", "=", EStr(ipstr).c_str());
	xc = Query(&t, BOT_RTV_STR);

	if (xc > -1)
	{
		if (rstr.empty())
		{
			xc = 1;
		}
		else
		{
			std::vector<BOT_STMT> tvec;
			bot_plug bp(ipstr, "", SOCK_DGRAM, AF_UNSPEC);
			xc = bp.Open(AI_PASSIVE);

			if (xc > -1)
			{
				while (xc > -1)
				{
					t.Renew(false, 4, "litebot", "BIPS", 1);
					t.spec = 0;
					t.AddCond("", "ADR", "=", EStr(bp.prt.ipstr.carr).c_str());
					xc = vtool.AVTV(&tvec, &t, true, true);
					xc = bp.Next();
				}

				bp.Close();
				xc = Commit(&tvec);

				if (xc < 0)
				{
					sint oc = Output(0, true, "Failed to commit remove banned ip", 1, 0);
				}
				else
				{
					carr_256 ncar;
					sint oc = bot_sprintf(ncar.carr, ncar.siz, "Removed ip (%s) from banned list.", ipstr);
					oc = Output(0, true, ncar.carr, 2);
				}
			}
			else
			{
				sint oc = Output(0, true, "Failed to find banned ip", 1, 0);
			}
		}
	}
	return xc;
}
sint machine::RefBIPS()
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_64 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "::RefBIPS()");
		op = Output(outp.carr, 2);
	}

	sint xc = 0;
	std::vector<std::string> ivec;
	carr_64 nip;

	while (GetVecEle((void*)&nip, MTX_BIPS, xc++, false) > -1)
	{
		std::string str;
		str.append(nip.carr);
		ivec.push_back(str);
	}

	std::vector<std::string> kvec;
	BOT_STMT t(false, 0, "litebot", "BIPS", 1, &kvec);
	xc = t.AddCol("ADR", "", true);
	xc = Query(&t, BOT_RTV_VSTR);

	for (size_t x = 0; x < kvec.size(); x++)
	{
		xc = vtool.VIV(&ivec, kvec[x].c_str());

		if (xc < 0)
		{
			xc = bot_sprintf(nip.carr, nip.siz, "%s", kvec[x].c_str());
			xc = PushToVec((void*)&nip, MTX_BIPS, true, true, false);
		}
	}

	for (size_t x = 0; x < ivec.size(); x++)
	{
		xc = vtool.VIV(&kvec, ivec[x].c_str());

		if (xc < 0)
		{
			sint rc = 0;
			xc = 0;

			while (xc > -1)
			{
				xc = GetVecEle((void*)&nip, MTX_BIPS, rc++, false);

				if (!strcmp(nip.carr, ivec[x].c_str()))
				{
					rc = ClearVecEle(MTX_BIPS, xc, false);
					xc = -1;
				}
			}
		}
	}
	return xc;
}
sint machine::AddVPKI(sint stype, size_t len, _char* dat, c_char* addr, c_char* port, _char ack)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_192 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::AddVPKI(sint stype(%i), size_t len(%u), _char* dat(%i), c_char* addr(%i), c_char* port(%i), _char ack(%i))", stype, len, (sint)dat, (sint)addr, (sint)port, (sint)ack);
		oc = Output(outp.carr, 2);
	}
	if (!dat || !len || stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}
	sint hx = -1;
	sint lx = LockGMutex(MTX_VPKI, &hx);

	if (lx > -1)
	{
		lx = -1;
		bot_vblki* p = &bot_pkti[stype];

		if (!p->nxt)
		{
			p->nxt = (bot_vblki*)malloc(sizeof(bot_vblki));
		}
		else
		{
			while (p->nxt)
			{
				p = p->nxt;
			}
			p->nxt = (bot_vblki*)malloc(sizeof(bot_vblki));
		}

		if (p->nxt)
		{
			p = p->nxt;
			memset((void*)p, 0, sizeof(bot_vblki));
			p->addr.siz = 64;
			p->servc.siz = 64;
			p->ack = ack;
			bot_sprintf(p->addr.carr, p->addr.siz, "%s", addr);
			bot_sprintf(p->servc.carr, p->servc.siz, "%s", port);
			p->SetBlk(dat, len);
			lx = 0;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_VPKI);
		}
	}
	return lx;
}
sint machine::AddVPKO(sint stype, size_t len, _char* dat, c_char* addr, c_char* port, _char ack)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_192 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::AddVPKO(sint stype(%i), size_t len(%u), _char* dat(%i), c_char* addr(%i), c_char* port(%i), _char ack(%i))", stype, len, (sint)dat, (sint)addr, (sint)port, (sint)ack);
		oc = Output(outp.carr, 2);
	}

	if (!dat || !len || stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_VPKO, &hx);

	if (lx > -1)
	{
		lx = -1;
		bot_vblko* p = &bot_pkto[stype];

		if (!p->nxt)
		{
			p->nxt = (bot_vblko*)malloc(sizeof(bot_vblko));
		}
		else
		{
			while (p->nxt)
			{
				p = p->nxt;
			}
			p->nxt = (bot_vblko*)malloc(sizeof(bot_vblko));
		}

		if (p->nxt)
		{
			p = p->nxt;
			memset((void*)p, 0, sizeof(bot_vblko));
			p->addr.siz = 64;
			p->servc.siz = 64;
			p->ack = ack;
			bot_sprintf(p->addr.carr, p->addr.siz, "%s", addr);
			bot_sprintf(p->servc.carr, p->servc.siz, "%s", port);
			p->SetBlk(dat, len);
			lx = 0;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_VPKO);
		}
	}
	return lx;
}
sint machine::AddVPKO(sint stype, bot_vblko* dat)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_192 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::AddVPKO(sint stype(%i), bot_vblko* dat(%i))", stype, (sint)dat);
		oc = Output(outp.carr, 2);
	}

	if (!dat || stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_VPKO, &hx);

	if (lx > -1)
	{
		lx = -1;
		bot_vblko* d = dat;
		bot_vblko* p = &bot_pkto[stype];

		while (d)
		{
			if (!p->nxt)
			{
				p->nxt = (bot_vblko*)malloc(sizeof(bot_vblko));
			}
			else
			{
				while (p->nxt)
				{
					p = p->nxt;
				}
				p->nxt = (bot_vblko*)malloc(sizeof(bot_vblko));
			}

			if (p->nxt)
			{
				p = p->nxt;
				memset((void*)p, 0, sizeof(bot_vblko));
				p->addr.siz = 64;
				p->servc.siz = 64;
				p->ack = d->ack;
				bot_sprintf(p->addr.carr, p->addr.siz, "%s", dat->addr.carr);
				bot_sprintf(p->servc.carr, p->servc.siz, "%s", dat->servc.carr);
				p->SetBlk(d->blk, d->siz);
				lx = 0;
			}
			d = d->nxt;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_VPKO);
		}
	}
	return lx;
}
sint machine::VPKO(sint stype)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::VPKO(sint stype(%i))", stype);
		oc = Output(outp.carr, 2);
	}

	if (stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_VPKO, &hx);

	if (lx > -1)
	{
		carr_2 ackr;
		carr_256 cipstr;
		lx = 0;
		bot_vblko* np = bot_pkto[stype].nxt;

		while (np)
		{
			lx = bot_sprintf(cipstr.carr, cipstr.siz, "%s %s %i", np->addr.carr, np->servc.carr, stype);
			lx = GetInVec(&cipstr, MTX_CIPS, false, false);

			if (lx < 0)
			{
				lx = BOTNCon(np->addr.carr, np->servc.carr, stype);
			}

			if (lx > -1)
			{
				bot_plug oth(np->addr.carr, np->servc.carr, stype, AF_UNSPEC);
				lx = oth.Open(0);

				if (lx > -1)
				{
					lx = GetInVec(&oth.prt, MTX_PORTS, false, false);

					if (lx > -1)
					{
						lx = oth.Sock(false);

						if (lx > -1)
						{
							if (stype != SOCK_DGRAM)
							{
								lx = oth.Conn();
							}

							if (lx > -1)
							{
								BOT_HDR_PKT hdr(BOT_OP_SEC, np->siz, 0, np->ack);
								hdr.ka = oth.prt.key_a;
								sllint ret = oth.Send((_char*)&hdr, sizeof(BOT_HDR_PKT));

								if (ret > 0)
								{
									ret = oth.Send(np->blk, np->siz);

									if (ret < 0)
									{
										carr_168 outp;
										sint oc = bot_sprintf(outp.carr, outp.siz, "failed to send stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
										oc = Output(outp.carr, 1);
									}
									else
									{
										if (np->ack)
										{
											uint sopt = 6000;
											//lx = oth.AddSOpt(SOL_SOCKET, SO_RCVTIMEO, (_char*)&sopt, sizeof(sopt));
											ret = oth.Rec(ackr.carr, sizeof(_char));

											while (ret < 0)
											{
												carr_168 outp;
												sint oc = bot_sprintf(outp.carr, outp.siz, "failed ack stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
												oc = Output(outp.carr, 1);
												ret = oth.Send((_char*)&hdr, sizeof(BOT_HDR_PKT));

												if (ret > 0)
												{
													ret = oth.Send(np->blk, np->siz);

													if (ret < 0)
													{
														carr_168 outp;
														sint oc = bot_sprintf(outp.carr, outp.siz, "failed to send stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
														oc = Output(outp.carr, 1);
													}
													ret = oth.Rec(ackr.carr, sizeof(_char));
												}
											}
										}
									}
								}
								else
								{
									carr_168 outp;
									sint oc = bot_sprintf(outp.carr, outp.siz, "failed to send header stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, sizeof(BOT_HDR_PKT), oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
									oc = Output(outp.carr, 1);
								}
							}
							else
							{
								carr_168 outp;
								sint oc = bot_sprintf(outp.carr, outp.siz, "socket error sending stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
								oc = Output(outp.carr, 1);
							}
						}
						else
						{
							carr_128 outp;
							sint oc = bot_sprintf(outp.carr, outp.siz, "socket error sending stype(%i) bytes(%u) to (%s port:%s) Error:%s", stype, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
							oc = Output(outp.carr, 1);
						}
					}
				}
				else
				{
					carr_128 outp;
					sint oc = bot_sprintf(outp.carr, outp.siz, "error opening (%s port:%s) stype(%i) bytes(%u) Error:%s", oth.prt.ipstr.carr, oth.servc.carr, stype, np->siz, oth.emsg.carr);
					oc = Output(outp.carr, 1);
				}

				oth.Close();
			}
			np = np->nxt;
		}

		np = bot_pkto[stype].nxt;

		while (np)
		{
			bot_pkto[stype].nxt = np->nxt;
			np->ClearBlk();
			free(np);
			np = bot_pkto[stype].nxt;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_VPKO);
		}
		hx = 0;
	}
	return hx;
}
sint machine::AddSVPKI(sint stype, size_t len, _char* dat, c_char* addr, c_char* port, _char ack)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_192 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::AddSVPKI(sint stype(%i), size_t len(%u), _char* dat(%i), c_char* addr(%i), c_char* port(%i), _char ack(%i))", stype, len, (sint)dat, (sint)addr, (sint)port, (sint)ack);
		oc = Output(outp.carr, 2);
	}
	if (!dat || !len || stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}
	sint hx = -1;
	sint lx = LockGMutex(MTX_SVPKI, &hx);

	if (lx > -1)
	{
		lx = -1;
		bot_svblki* p = &bot_spkti[stype];

		if (!p->nxt)
		{
			p->nxt = (bot_svblki*)malloc(sizeof(bot_svblki));
		}
		else
		{
			while (p->nxt)
			{
				p = p->nxt;
			}
			p->nxt = (bot_svblki*)malloc(sizeof(bot_svblki));
		}

		if (p->nxt)
		{
			p = p->nxt;
			memset((void*)p, 0, sizeof(bot_svblki));
			p->addr.siz = 64;
			p->servc.siz = 64;
			p->ack = ack;
			bot_sprintf(p->addr.carr,p->addr.siz, "%s", addr);
			bot_sprintf(p->servc.carr, p->servc.siz, "%s", port);
			p->SetBlk(dat, len);
			lx = 0;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_SVPKI);
		}
	}
	return lx;
}
sint machine::AddSVPKO(sint stype, size_t len, _char* dat, c_char* addr, c_char* port, _char ack)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_192 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::AddSVPKO(sint stype(%i), size_t len(%u), _char* dat(%i), c_char* addr(%i), c_char* port(%i), _char ack(%i))", stype, len, (sint)dat, (sint)addr, (sint)port, (sint)ack);
		oc = Output(outp.carr, 2);
	}

	if (!dat || !len || stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_SVPKO, &hx);

	if (lx > -1)
	{
		lx = -1;
		bot_svblko* p = &bot_spkto[stype];

		if (!p->nxt)
		{
			p->nxt = (bot_svblko*)malloc(sizeof(bot_svblko));
		}
		else
		{
			while (p->nxt)
			{
				p = p->nxt;
			}
			p->nxt = (bot_svblko*)malloc(sizeof(bot_svblko));
		}

		if (p->nxt)
		{
			p = p->nxt;
			memset((void*)p, 0, sizeof(bot_svblko));
			p->addr.siz = 64;
			p->servc.siz = 64;
			p->ack = ack;
			bot_sprintf(p->addr.carr, p->addr.siz, "%s", addr);
			bot_sprintf(p->servc.carr, p->servc.siz, "%s", port);
			p->SetBlk(dat, len);
			lx = 0;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_SVPKO);
		}
	}
	return lx;
}
sint machine::AddSVPKO(sint stype, bot_vblko* dat)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_192 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::AddSVPKO(sint stype(%i), bot_vblko* dat(%i))", stype, (sint)dat);
		oc = Output(outp.carr, 2);
	}

	if (!dat || stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_SVPKO, &hx);

	if (lx > -1)
	{
		lx = -1;
		bot_vblko* d = dat;
		bot_svblko* p = &bot_spkto[stype];

		while (d)
		{
			if (!p->nxt)
			{
				p->nxt = (bot_svblko*)malloc(sizeof(bot_svblko));
			}
			else
			{
				while (p->nxt)
				{
					p = p->nxt;
				}
				p->nxt = (bot_svblko*)malloc(sizeof(bot_svblko));
			}

			if (p->nxt)
			{
				p = p->nxt;
				memset((void*)p, 0, sizeof(bot_svblko));
				p->addr.siz = 64;
				p->servc.siz = 64;
				p->ack = d->ack;
				bot_sprintf(p->addr.carr, p->addr.siz, "%s", d->addr.carr);
				bot_sprintf(p->servc.carr, p->servc.siz, "%s", d->servc.carr);
				p->SetBlk(d->blk, d->siz);
				lx = 0;
			}
			d = d->nxt;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_SVPKO);
		}
	}
	return lx;
}
sint machine::SVPKO(sint stype)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::SVPKO(sint stype(%i))", stype);
		oc = Output(outp.carr, 2);
	}

	if (stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_SVPKO, &hx);

	if (lx > -1)
	{
		carr_2 ackr;
		carr_256 cipstr;
		lx = 0;
		bot_svblko* np = bot_spkto[stype].nxt;

		while (np)
		{
			lx = bot_sprintf(cipstr.carr, cipstr.siz, "%s %s %i", np->addr.carr, np->servc.carr, stype);
			lx = GetInVec(&cipstr, MTX_CIPS, false, false);

			if (lx < 0)
			{
				lx = BOTNCon(np->addr.carr, np->servc.carr, stype);
			}

			if (lx > -1)
			{
				bot_plug oth(np->addr.carr, np->servc.carr, stype, AF_UNSPEC);
				lx = oth.Open(0);

				if (lx > -1)
				{
					lx = GetInVec(&oth.prt, MTX_PORTS, false, false);

					if (lx > -1)
					{
						lx = oth.Sock(false);

						if (lx > -1)
						{
							if (stype != SOCK_DGRAM)
							{
								lx = oth.Conn();
							}

							if (lx > -1)
							{
								BOT_HDR_PKT hdr(BOT_OP_SEC, np->siz, 0, np->ack);
								hdr.ka = oth.prt.key_a;
								sllint ret = oth.Send((_char*)&hdr, sizeof(BOT_HDR_PKT));

								if (ret > 0)
								{
									ret = oth.Send(np->blk, np->siz);

									if (ret < 0)
									{
										carr_168 outp;
										sint oc = bot_sprintf(outp.carr, outp.siz, "failed to send stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
										oc = Output(outp.carr, 1);
									}
									else
									{
										if (np->ack)
										{
											uint sopt = 6000;
											//lx = oth.AddSOpt(SOL_SOCKET, SO_RCVTIMEO, (_char*)&sopt, sizeof(sopt));
											ret = oth.Rec(ackr.carr, sizeof(_char));

											while (ret < 0)
											{
												carr_168 outp;
												sint oc = bot_sprintf(outp.carr, outp.siz, "failed ack stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
												oc = Output(outp.carr, 1);
												ret = oth.Send((_char*)&hdr, sizeof(BOT_HDR_PKT));

												if (ret > 0)
												{
													ret = oth.Send(np->blk, np->siz);

													if (ret < 0)
													{
														carr_168 outp;
														sint oc = bot_sprintf(outp.carr, outp.siz, "failed to send stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
														oc = Output(outp.carr, 1);
													}
													ret = oth.Rec(ackr.carr, sizeof(_char));
												}
											}
										}
									}
								}
								else
								{
									carr_168 outp;
									sint oc = bot_sprintf(outp.carr, outp.siz, "failed to send header stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, sizeof(BOT_HDR_PKT), oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
									oc = Output(outp.carr, 1);
								}
							}
							else
							{
								carr_168 outp;
								sint oc = bot_sprintf(outp.carr, outp.siz, "socket error sending stype(%i) sock:%i bytes(%u) to (%s port:%s) Error:%s", stype, (sint)oth.prt.sck, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
								oc = Output(outp.carr, 1);
							}
						}
						else
						{
							carr_128 outp;
							sint oc = bot_sprintf(outp.carr, outp.siz, "socket error sending stype(%i) bytes(%u) to (%s port:%s) Error:%s", stype, np->siz, oth.prt.ipstr.carr, oth.servc.carr, oth.emsg.carr);
							oc = Output(outp.carr, 1);
						}
					}
				}
				else
				{
					carr_128 outp;
					sint oc = bot_sprintf(outp.carr, outp.siz, "error opening (%s port:%s) stype(%i) bytes(%u) Error:%s", oth.prt.ipstr.carr, oth.servc.carr, stype, np->siz, oth.emsg.carr);
					oc = Output(outp.carr, 1);
				}

				oth.Close();
			}
			np = np->nxt;
		}

		np = bot_spkto[stype].nxt;

		while (np)
		{
			bot_spkto[stype].nxt = np->nxt;
			np->ClearBlk();
			free(np);
			np = bot_spkto[stype].nxt;
		}
		if (!hx)
		{
			hx = UnlockGMutex(MTX_SVPKO);
		}
		hx = 0;
	}
	return hx;
}
sint machine::ClearDSum(slint nidh, sint seq, slint sumv)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::ClearDSum(slint nidh(%i), sint seq(%i), slint sumv(%li))", nidh, seq, sumv);
		oc = Output(outp.carr, 2);
	}

	if (!nidh || !sumv || seq < 0)
	{
		return -1;
	}
	bot_file_hdr nh;
	nh.idh = nidh;
	nh.seq = seq;
	sint ret = -1;
	sint rc = GetInVec(&nh, MTX_NET_FINC, false, false);

	if (rc > -1)
	{
		sint ox = -1;
		sint lx = LockGMutex(MTX_NET_FINC, &ox);

		if (lx > -1)
		{
			sint xc = vtool.VIV(&bot_net_finc[rc].rec, sumv);

			if (xc > -1)
			{
				bot_net_finc[rc].rec[xc] = 0;
				ret = xc;
				vtool.CLNV(&bot_net_finc[rc].rec, true);

				if (!ox)
				{
					ox = UnlockGMutex(MTX_NET_FINC);
				}
			}
		}
	}
	return ret;
}
sint machine::ChunkDat(_char* dat, size_t f, size_t* len, bot_file_hdr* hdr, BOT_FILE_CHK* chk)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::ChunkDat(_char* dat(%i), size_t f(%u), size_t* len(%i), bot_file_hdr* hdr(%i), BOT_FILE_CHK* chk(%i))", (sint)dat, f, (sint)len, (sint)hdr, (sint)chk);
		oc = Output(outp.carr, 2);
	}

	if (!dat || !len || !hdr || !chk)
	{
		return -1;
	}

	if (!hdr->rec.empty())
	{
		hdr->rec.clear();
	}

	size_t lim = BOT_FILE_CHUNK;

	if (!*len)
	{
		*len = bot_strlen(dat);
	}
	
	if (*len > BOT_FILE_CHUNK * BOT_FILE_HCHUNK)
	{
		*len = BOT_FILE_CHUNK * BOT_FILE_HCHUNK;
	}
	
	_char trm = '\0';
	sint ret = -1;
	BOT_FILE_CHK* p = chk;

	while (f < *len && hdr->rec.size() < BOT_FILE_HCHUNK)
	{
		if (p)
		{
			if (f + lim >= *len)
			{
				lim = *len - f;
			}

			p->dat = (_char*)malloc(lim + 1);

			if (p->dat)
			{
				p->seq = hdr->seq;
				p->f = f;
				p->t = f + lim;
				p->idh = hdr->idh;
				memcpy((void*)p->dat, (void*)&dat[f], lim);
				memcpy((void*)&p->dat[lim], (void*)&trm, sizeof(_char));
				slint nsum = 0;

				for (size_t x = 0; x < lim; x++)
				{
					nsum += (slint)p->dat[x];
				}
				hdr->rec.push_back(nsum);
				ret++;
			}

			f += lim;

			if (f < *len && hdr->rec.size() < BOT_FILE_HCHUNK)
			{
				p->nxt = (BOT_FILE_CHK*)malloc(sizeof(BOT_FILE_CHK));

				if (p->nxt)
				{
					memset((void*)p->nxt, 0, sizeof(BOT_FILE_CHK));
					p = p->nxt;
				}
			}
		}
		else
		{
			f = *len;
		}
	}
	return ret;
}
sint machine::BOTServPS(sint stype)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::BOTServPS(sint stype(%i))", stype);
		oc = Output(outp.carr, 2);
	}

	if (stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_SVPKI, &hx);

	if (lx > -1)
	{
		lx = 0;
		bot_svblki* np = bot_spkti[stype].nxt;

		while (np)
		{
			lx++;

			if (np->blk)
			{
				bot_vblki sp(np->blk, np->siz, np->addr.carr, np->servc.carr, np->ack);

				switch (sp.blk[0])
				{
				case BOT_OP_COM:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received command packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_MSG:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received smsg packet (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					std::string datstr;
					size_t i = 1;

					while (i < sp.siz)
					{
						switch (sp.blk[i])
						{
						case BOT_RTV_SINT:
						{
							i += sizeof(_char);
							sint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sint));
							i += sizeof(sint);
							sint rc = bot_sprintfs(&datstr, false, "\n%i", xval);
							break;
						}
						case BOT_RTV_SLINT:
						{
							i += sizeof(_char);
							slint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint);
							sint rc = bot_sprintfs(&datstr, false, "\n%li", xval);
							break;
						}
						case BOT_RTV_SLLINT:
						{
							i += sizeof(_char);
							sllint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sllint));
							i += sizeof(sllint);
							sint rc = bot_sprintfs(&datstr, false, "\n%lli", xval);
							break;
						}
						case BOT_RTV_UINT:
						{
							i += sizeof(_char);
							uint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(uint));
							i += sizeof(uint);
							sint rc = bot_sprintfs(&datstr, false, "\n%u", xval);
							break;
						}
						case BOT_RTV_ULINT:
						{
							i += sizeof(_char);
							ulint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ulint));
							i += sizeof(ulint);
							sint rc = bot_sprintfs(&datstr, false, "\n%lu", xval);
							break;
						}
						case BOT_RTV_ULLINT:
						{
							i += sizeof(_char);
							ullint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ullint));
							i += sizeof(ullint);
							sint rc = bot_sprintfs(&datstr, false, "\n%llu", xval);
							break;
						}
						case BOT_RTV_REAL:
						{
							i += sizeof(_char);
							float xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(float));
							i += sizeof(float);
							sint rc = bot_sprintfs(&datstr, false, "\n%.9f", xval);
							break;
						}
						case BOT_RTV_CHAR:
						{
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\n%c", sp.blk[i]);
							i += (sizeof(_char) + sizeof(_char));
							break;
						}
						case BOT_RTV_UCHAR:
						{
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\n%c", sp.blk[i]);
							i += (sizeof(u_char) + sizeof(_char));
							break;
						}
						case BOT_RTV_STR:
						{
							i += sizeof(_char);
							size_t ln = bot_strlen(&sp.blk[i]);
							sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
							i += (ln + sizeof(_char));
							break;
						}
						case BOT_RTV_VSINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sint));
								i += sizeof(sint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%i,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VSLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								slint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(slint));
								i += sizeof(slint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%li,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VSLLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sllint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sllint));
								i += sizeof(sllint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%lli,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VUINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								uint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(uint));
								i += sizeof(uint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%u,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VULINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								ulint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ulint));
								i += sizeof(ulint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%lu,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VULLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								ullint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ullint));
								i += sizeof(ullint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%llu,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VREAL:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								float xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(float));
								i += sizeof(float);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%.9f,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VCHAR:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%c,", sp.blk[i]);
									i += sizeof(_char);
								}
								i += sizeof(_char);
							}
							break;
						}
						case BOT_RTV_VUCHAR:
						{
							u_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%c,", sp.blk[i]);
									i += sizeof(u_char);
								}
								i += sizeof(u_char);
							}
							break;
						}
						case BOT_RTV_VSTR:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								size_t ln = bot_strlen(&sp.blk[i]);
								sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
								i += (ln + sizeof(_char));

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
							}
							break;
						}
						case BOT_RTV_VBLOB:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sint rc = bot_sprintfs(&datstr, false, "%02X ", sp.blk[i]);
								i += sizeof(_char);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
							}
							break;
						}
						default:
						{
							i = sp.siz;
							break;
						}
						}
					}
					if (debug_lvl >= 1 && debug_m)
					{
						sint rc = Output(0, true, datstr.c_str(), 2, 0);
					}
					break;
				}
				case BOT_OP_NPT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received new port packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_GDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received gdat packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_NDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received EST packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						std::vector<ulint> uvec;
						ulint val = 0;

						for (size_t iter = 1; iter < sp.siz; iter += sizeof(ulint))
						{
							ulint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[iter], sizeof(ulint));
							val = ntohl(xval);
							uvec.push_back(val);
							val = 0;
						}
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data:\n%v%lu\n%", &uvec);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_SDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received sdat packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_WDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received wdat packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_VDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received vdat packet (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					std::string datstr("data: ");
					size_t i = 1;

					while (i < sp.siz)
					{
						switch (sp.blk[i])
						{
						case BOT_RTV_SINT:
						{
							i += sizeof(_char);
							sint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sint));
							i += sizeof(sint);
							sint rc = bot_sprintfs(&datstr, false, "\n%i", xval);
							break;
						}
						case BOT_RTV_SLINT:
						{
							i += sizeof(_char);
							slint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint);
							sint rc = bot_sprintfs(&datstr, false, "\n%li", xval);
							break;
						}
						case BOT_RTV_SLLINT:
						{
							i += sizeof(_char);
							sllint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sllint));
							i += sizeof(sllint);
							sint rc = bot_sprintfs(&datstr, false, "\n%lli", xval);
							break;
						}
						case BOT_RTV_UINT:
						{
							i += sizeof(_char);
							uint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(uint));
							i += sizeof(uint);
							sint rc = bot_sprintfs(&datstr, false, "\n%u", xval);
							break;
						}
						case BOT_RTV_ULINT:
						{
							i += sizeof(_char);
							ulint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ulint));
							i += sizeof(ulint);
							sint rc = bot_sprintfs(&datstr, false, "\n%lu", xval);
							break;
						}
						case BOT_RTV_ULLINT:
						{
							i += sizeof(_char);
							ullint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ullint));
							i += sizeof(ullint);
							sint rc = bot_sprintfs(&datstr, false, "\n%llu", xval);
							break;
						}
						case BOT_RTV_REAL:
						{
							i += sizeof(_char);
							float xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(float));
							i += sizeof(float);
							sint rc = bot_sprintfs(&datstr, false, "\n%.9f", xval);
							break;
						}
						case BOT_RTV_CHAR:
						{
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\n%c", sp.blk[i]);
							i += (sizeof(_char) + sizeof(_char));
							break;
						}
						case BOT_RTV_UCHAR:
						{
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\n%c", sp.blk[i]);
							i += (sizeof(u_char) + sizeof(_char));
							break;
						}
						case BOT_RTV_STR:
						{
							i += sizeof(_char);
							size_t ln = bot_strlen(&sp.blk[i]);

							if (sp.blk[i] == '/' && sp.blk[i + 1] == '#')
							{
								sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
								BOT_CLIENT_M cli;
								rc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

								if (rc > -1)
								{
									std::vector<BOT_ARG> avec;
									rc = ArgSep(&avec, false, i, sp.siz, sp.blk, BOT_RTV_VCHAR, &msy.nrts_sep, VTV_MAX);

									if (rc > -1)
									{
										rc = Command(&cli, &avec);
									}
								}
							}
							else
							{
								sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
							}
							i += (ln + sizeof(_char));
							break;
						}
						case BOT_RTV_VAR:
						{
							i += sizeof(_char);
							BOT_VAR_T nvar;
							nvar.t = sp.blk[i];
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\nvariable: $%s", &sp.blk[i]);
							size_t ln = bot_strlen(&sp.blk[i]);
							rc = FVAR(&sp.blk[i]);

							if (rc < 0)
							{
								nvar.n = (_char*)malloc(ln + 1);

								if (nvar.n)
								{
									_char trm = '\0';
									memcpy((void*)&nvar.n[ln], (void*)&trm, sizeof(_char));
									memcpy((void*)nvar.n, (void*)&sp.blk[i], ln);
									i += (ln + sizeof(_char));
									bool done = false;
									rc = 0;

									while (!done)
									{
										std::vector<_char> nvec;
										nvar.v.push_back(nvec);

										switch (nvar.t)
										{
										case BOT_RTV_SLLINT:
										{
											for (size_t x = 0; x < sizeof(sllint); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_REAL:
										{
											for (size_t x = 0; x < sizeof(float); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_STR:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										case BOT_RTV_BLOB:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										case BOT_RTV_VSLLINT:
										{
											for (size_t x = 0; x < sizeof(sllint); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_VREAL:
										{
											for (size_t x = 0; x < sizeof(float); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_VSTR:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										case BOT_RTV_VBLOB:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										default:
										{
											break;
										}
										}
										if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
										{
											done = true;
										}
										else
										{
											rc++;
										}
									}
									rc = PushToVec(&nvar, MTX_VARS, true, true, false);
								}
							}
							rc = bot_sprintfs(&datstr, false, " %s", nvar.n);
							break;
						}
						case BOT_RTV_FHD:
						{
							i += sizeof(_char);
							bot_file_hdr nh;
							memcpy((void*)&nh.idh, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint);
							memcpy((void*)&nh.seq, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&nh.dsiz, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t);

							for (size_t x = 0; x < BOT_FILE_HCHUNK; x++)
							{
								slint v = 0;
								memcpy((void*)&v, (void*)&sp.blk[i], sizeof(slint));
								i += sizeof(slint);

								if (v == INT32_MAX)
								{
									x = BOT_FILE_HCHUNK;
								}
								else
								{
									nh.rec.push_back(v);
								}
							}

							if (nh.rec.empty())
							{
								sint rc = GetInVec(&nh, MTX_NET_FINC, false, false);

								if (rc > -1)
								{
									BOT_CLIENT_M cli;
									sint xc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);
									
									if (xc > -1)
									{
										carr_16 rport;
										bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);

										if (!nh.rec.empty())
										{
											sint trs = 0;
											sint ct = 0;

											while (!nh.rec.empty() && trs < 10)
											{
												if (ct == 100)
												{
													for (size_t x = 0; x < nh.rec.size(); x++)
													{
														bot_vblko req((_char)BOT_OP_FCK, cli.prt.oipstr.carr, rport.carr, 1);
														xc = req.Add(0, BOT_RTV_SLINT, nh.idh, BOT_RTV_SLINT, nh.seq, BOT_RTV_ULINT, x * BOT_FILE_CHUNK, BOT_RTV_MAX);

														if (xc > -1)
														{
															xc = AddSVPKO(stype, &req);
														}
													}
													ct = 0;
													trs++;
												}
												sllint rst = Rest(BOT_MILLI_REST * 10);
												xc = GetVecEle(&nh, MTX_NET_FINC, rc, false);
												ct++;
											}
										}
										bot_vblko req((_char)BOT_OP_FCD, cli.prt.oipstr.carr, rport.carr, 1);
										xc = req.Add(0, BOT_RTV_SLINT, nh.idh, BOT_RTV_SLINT, nh.seq, BOT_RTV_MAX);

										if (xc > -1)
										{
											xc = AddSVPKO(stype, &req);
										}
									}
									rc = ClearVecEle(MTX_NET_FINC, rc, false);
								}
							}
							else
							{
								carr_24 nm;
								bot_sprintf(nm.carr, nm.siz, "%li", nh.idh);
								BOT_FILE_M nf(nm.carr, "", BOTPathS(BOT_NETI_NM).c_str(), BOT_FILE_APND, BOT_F_CON, -1, lid);
								sint ct = 0;
								sint ox = -1;
								sint xc = BOTOpenFile(&nf, &ox);

								if (xc < 0)
								{
									nf.lid = -1;
									ox = -1;
									xc = BOTOpenFile(&nf, &ox, false, true);

									if (xc < 0)
									{
										bot_sprintfs(&datstr, false, "\nerror 30");
									}
									else
									{
										bot_sprintfs(&datstr, false, "\n%s\n%lu bytes 1", BOTFileStr(&nf).c_str(), (size_t)nf.fst.filestats.st_size);
										nh.fid = nf.lid;
										sint rc = PushToVec(&nh, MTX_NET_FINC, true, true, false);

										if (rc < 0)
										{
											bot_sprintfs(&datstr, false, "\nerror 10");
										}

										if (!ox)
										{
											ox = BOTCloseFile(&nf);
										}
									}
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%s\n%lu bytes 2", BOTFileStr(&nf).c_str(), (size_t)nf.fst.filestats.st_size);
									nh.fid = nf.lid;
									sint rc = PushToVec(&nh, MTX_NET_FINC, true, true, false);

									if (rc < 0)
									{
										bot_sprintfs(&datstr, false, "\nerror 10");
									}

									if (!ox)
									{
										ox = BOTCloseFile(&nf);
									}
								}
							}
							break;
						}
						case BOT_RTV_FLC:
						{
							BOT_FILE_CHK ck;
							i += sizeof(_char);
							memcpy((void*)&ck.idh, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.seq, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.f, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);
							memcpy((void*)&ck.t, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);

							if (ck.t > ck.f && ck.t - ck.f <= BOT_FILE_CHUNK)
							{
								bot_sprintfs(&datstr, false, "\nfile chunk: %li seq: %i\nfrom: %lu to: %lu", ck.idh, ck.seq, ck.f, ck.t);
								slint dsum = 0;

								for (size_t x = 0; x < ck.t - ck.f; x++)
								{
									dsum += (slint)sp.blk[i + x];
								}

								sint rc = ClearDSum(ck.idh, ck.seq, dsum);

								if (rc < 0)
								{
									BOT_CLIENT_M cli;
									rc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

									if (rc > -1)
									{
										carr_16 rport;
										bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);
										bot_vblko req((_char)BOT_OP_FCK, cli.prt.oipstr.carr, rport.carr, 1);
										rc = req.Add(0, BOT_RTV_SLINT, ck.idh, BOT_RTV_SLINT, ck.seq, BOT_RTV_ULINT, ck.f, BOT_RTV_MAX);

										if (rc > -1)
										{
											rc = AddSVPKO(stype, &req);
										}
									}
								}
								else
								{
									carr_24 nm;
									bot_sprintf(nm.carr, nm.siz, "%li", ck.idh);
									BOT_FILE_M nf(nm.carr, "", BOTPathS(BOT_NETI_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
									sint ct = 0;
									sint ox = -1;
									rc = BOTOpenFile(&nf, &ox);

									if (rc > -1)
									{
										rc = BOTFileOUT(&nf, ck.f, ck.t, false, BOT_RTV_BLOB, &sp.blk[i], BOT_RTV_MAX);

										if (rc < 0)
										{
											bot_sprintfs(&datstr, false, "\nerror 20");
										}

										if (!ox)
										{
											BOTCloseFile(&nf);
										}
									}
								}
							}
							break;
						}
						case BOT_RTV_FLN:
						{
							BOT_FILE_CHK ck;
							i += sizeof(_char);
							memcpy((void*)&ck.idh, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.seq, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.f, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);
							memcpy((void*)&ck.t, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);
							carr_24 nm;
							bot_sprintf(nm.carr, nm.siz, "%li", ck.idh);
							BOT_FILE_M nf(nm.carr, "", BOTPathS(BOT_NETI_NM).c_str(), BOT_FILE_READ, BOT_F_CON);
							sint ox = -1;
							sint rc = BOTOpenFile(&nf, &ox, true, false, false, true);

							if (rc > -1)
							{
								BOT_FILE_M xf(&sp.blk[i], "", nf.path.c_str(), BOT_FILE_APND, BOT_F_CON, -1, lid);
								bot_sprintfs(&datstr, false, "\nfile name: %li\n%s", ck.idh, BOTFileStr(&xf).c_str());
								sint xx = -1;
								rc = BOTOpenFile(&xf, &xx);

								if (rc < 0)
								{
									rc = BOTOpenFile(&xf, &xx, false, true);

									if (rc > -1)
									{
										rc = BOTFileOUT(&xf, 0, nf.dsiz - 1, false, BOT_RTV_BLOB, nf.datp, BOT_RTV_MAX);

										if (!xx)
										{
											xx = BOTCloseFile(&xf);
										}
									}
								}
								else
								{
									sint ct = 0;
									bool done = false;

									while (!done && ct < INT_MAX)
									{
										xf.lid = -1;
										size_t len = xf.name.length();
										bot_sprintfs(&xf.name, false, "_%i", ct);
										xx = -1;
										rc = BOTOpenFile(&xf, &xx);

										if (rc < 0)
										{
											done = true;
											xf.lid = -1;
											xx = -1;
											rc = BOTOpenFile(&xf, &xx, false, true);

											if (rc > -1)
											{
												rc = BOTFileOUT(&xf, 0, nf.dsiz - 1, false, BOT_RTV_BLOB, nf.datp, BOT_RTV_MAX);

												if (!xx)
												{
													xx = BOTCloseFile(&xf);
												}
											}
										}
										else
										{
											if (!xx)
											{
												xx = BOTCloseFile(&xf);
											}
											len = xf.name.length() - len;
											for (size_t y = 0; y < len; y++)
											{
												xf.name.pop_back();
											}
											ct++;
										}
									}
								}

								if (!ox)
								{
									ox = BOTCloseFile(&nf, true, true, true);
								}
							}
							break;
						}
						case BOT_RTV_VSINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sint));
								i += sizeof(sint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%i,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VSLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								slint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(slint));
								i += sizeof(slint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%li,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VSLLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sllint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sllint));
								i += sizeof(sllint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%lli,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VUINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								uint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(uint));
								i += sizeof(uint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%u,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VULINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								ulint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ulint));
								i += sizeof(ulint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%lu,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VULLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								ullint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ullint));
								i += sizeof(ullint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%llu,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VREAL:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								float xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(float));
								i += sizeof(float);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%.9f,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VCHAR:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%c,", sp.blk[i]);
									i += sizeof(_char);
								}
								i += sizeof(_char);
							}
							break;
						}
						case BOT_RTV_VUCHAR:
						{
							u_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%c,", sp.blk[i]);
									i += sizeof(u_char);
								}
								i += sizeof(u_char);
							}
							break;
						}
						case BOT_RTV_VSTR:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								size_t ln = bot_strlen(&sp.blk[i]);

								if (sp.blk[i] == '/' && sp.blk[i + 1] == '#')
								{
									sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
									BOT_CLIENT_M cli;
									rc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

									if (rc > -1)
									{
										std::vector<BOT_ARG> avec;
										rc = ArgSep(&avec, false, i, sp.siz, sp.blk, BOT_RTV_VCHAR, &msy.nrts_sep, VTV_MAX);

										if (rc > -1)
										{
											rc = Command(&cli, &avec);
										}
									}
								}
								else
								{
									sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
								}

								i += sizeof(_char);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									i += (ln + sizeof(_char));
								}
							}
							break;
						}
						case BOT_RTV_VBLOB:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sint rc = bot_sprintfs(&datstr, false, "%02X ", sp.blk[i]);
								i += sizeof(_char);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
							}
							break;
						}
						default:
						{
							i = sp.siz;
							break;
						}
						}
					}
					if (debug_lvl >= 1 && debug_m)
					{
						sint rc = Output(0, true, datstr.c_str(), 2, 0);
					}
					break;
				}
				case BOT_OP_FCK:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received file chunk request (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}
					size_t i = 0;
					slint a = 0;
					memcpy((void*)&a, (void*)&sp.blk[i], sizeof(slint));
					i += sizeof(slint);
					sint c = 0;
					memcpy((void*)&c, (void*)&sp.blk[i], sizeof(sint));
					i += sizeof(sint);
					size_t b = 0;
					memcpy((void*)&b, (void*)&sp.blk[i], sizeof(size_t));
					i += sizeof(size_t);
					bot_file_hdr hdr;
					hdr.idh = a;
					hdr.seq = c;
					sint rc = GetInVec(&hdr, MTX_NET_FOUT, false, false);

					if (rc > -1)
					{
						BOT_FILE_M nf;
						rc = GetVecEle((void*)&nf, MTX_FO, hdr.fid);

						if (rc > -1)
						{
							i = b + BOT_FILE_CHUNK;
							BOT_FILE_CHK chk;
							rc = ChunkDat(nf.datp, b, &i, &hdr, &chk);

							if (rc > -1)
							{
								BOT_CLIENT_M cli;
								sint xc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

								if (xc > -1)
								{
									carr_16 rport;
									bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);
									bot_vblko blk((_char)BOT_OP_VDAT, sp.addr.carr, rport.carr, 1);
									rc = blk.Add(0, BOT_RTV_FHD, &hdr, BOT_RTV_FLC, &chk);

									if (rc > -1)
									{
										rc = AddSVPKO(stype, &blk);
									}
								}
							}
						}
					}
					break;
				}
				case BOT_OP_FCD:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received file done (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}
					bot_file_hdr hdr;
					size_t i = 1;

					if (sp.blk[i] == BOT_RTV_SLINT)
					{
						i += sizeof(_char);
						memcpy((void*)&hdr.idh, (void*)&sp.blk[i], sizeof(slint));
						i += sizeof(slint);
					}
					if (sp.blk[i] == BOT_RTV_SLINT)
					{
						i += sizeof(_char);
						memcpy((void*)&hdr.seq, (void*)&sp.blk[i], sizeof(slint));
						i += sizeof(slint);
					}
					sint rc = GetInVec(&hdr, MTX_NET_FOUT, false, false);

					if (rc > -1)
					{
						BOT_FILE_M nfile;
						sint xc = GetVecEle(&nfile, MTX_FO, hdr.fid);

						if (xc > -1)
						{
							BOT_CLIENT_M cli;
							xc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

							if (xc > -1)
							{
								carr_512 ncar;
								bot_sprintf(ncar.carr, ncar.siz, "%s.%s", nfile.name.c_str(), nfile.type.c_str());
								BOT_FILE_CHK chk(hdr.idh, 0, bot_strlen(ncar.carr), ncar.carr);
								carr_16 rport;
								bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);
								bot_vblko oblk((_char)BOT_OP_VDAT, sp.addr.carr, rport.carr, 1);
								xc = oblk.Add(0, BOT_RTV_FLN, &chk, BOT_RTV_MAX);

								if (xc > -1)
								{
									xc = AddSVPKO(stype, &oblk);
								}
							}
						}
						rc = ClearVecEle(MTX_NET_FOUT, rc, false);
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
			np->siz = 0;
			np = np->nxt;
		}

		np = bot_spkti[stype].nxt;

		while (np)
		{
			if (!np->siz)
			{
				bot_spkti[stype].nxt = np->nxt;
				np->ClearBlk();
				free(np);
				np = bot_spkti[stype].nxt;
			}
		}

		if (!hx)
		{
			hx = UnlockGMutex(MTX_SVPKI);
		}
	}
	return lx;
}
sint machine::BOTServP(sint stype)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint oc = bot_sprintf(outp.carr, outp.siz, "::BOTServP(sint stype(%i))", stype);
		oc = Output(outp.carr, 2);
	}

	if (stype < 0 || stype >= BOT_SCKT_MAX)
	{
		return -1;
	}

	sint hx = -1;
	sint lx = LockGMutex(MTX_VPKI, &hx);

	if (lx > -1)
	{
		lx = 0;
		bot_vblki* np = bot_pkti[stype].nxt;

		while (np)
		{
			lx++;

			if (np->blk)
			{
				bot_vblki sp(np->blk, np->siz, np->addr.carr, np->servc.carr, np->ack);

				switch (sp.blk[0])
				{
				case BOT_OP_COM:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received command packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_NPT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received new port packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_GDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received gdat packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_NDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received EST packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						std::vector<ulint> uvec;
						ulint val = 0;

						for (size_t iter = 1; iter < sp.siz; iter += sizeof(ulint))
						{
							ulint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[iter], sizeof(ulint));
							val = ntohl(xval);
							uvec.push_back(val);
							val = 0;
						}
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data:\n%v%lu\n%", &uvec);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_SDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received sdat packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_WDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received wdat packet (%s port:%s) - data: %u bytes", sp.addr.carr, sp.servc.carr, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (sp.siz < BOT_FILESIZE_MAX)
					{
						if (debug_lvl >= 1 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "data: %s", &sp.blk[1]);
							rc = Output(0, true, outp.carr, 2, 0);
						}
					}
					break;
				}
				case BOT_OP_FCK:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received file chunk request (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}
					size_t i = 0;
					slint a = 0;
					memcpy((void*)&a, (void*)&sp.blk[i], sizeof(slint));
					i += sizeof(slint);
					sint c = 0;
					memcpy((void*)&c, (void*)&sp.blk[i], sizeof(sint));
					i += sizeof(sint);
					size_t b = 0;
					memcpy((void*)&b, (void*)&sp.blk[i], sizeof(size_t));
					i += sizeof(size_t);
					bot_file_hdr hdr;
					hdr.idh = a;
					hdr.seq = c;
					sint rc = GetInVec(&hdr, MTX_NET_FOUT, false, false);

					if (rc > -1)
					{
						BOT_FILE_M nf;
						rc = GetVecEle((void*)&nf, MTX_FO, hdr.fid);

						if (rc > -1)
						{
							i = b + BOT_FILE_CHUNK;
							BOT_FILE_CHK chk;
							rc = ChunkDat(nf.datp, b, &i, &hdr, &chk);

							if (rc > -1)
							{
								BOT_CLIENT_M cli;
								sint xc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

								if (xc > -1)
								{
									carr_16 rport;
									bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);
									bot_vblko blk((_char)BOT_OP_VDAT, sp.addr.carr, rport.carr, 1);
									rc = blk.Add(0, BOT_RTV_FHD, &hdr, BOT_RTV_FLC, &chk);

									if (rc > -1)
									{
										rc = AddVPKO(stype, &blk);
									}
								}
							}
						}
					}
					break;
				}
				case BOT_OP_FCD:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received file done (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					bot_file_hdr hdr;
					size_t i = 1;

					if (sp.blk[i] == BOT_RTV_SLINT)
					{
						i += sizeof(_char);
						memcpy((void*)&hdr.idh, (void*)&sp.blk[i], sizeof(slint));
						i += sizeof(slint);
					}
					if (sp.blk[i] == BOT_RTV_SLINT)
					{
						i += sizeof(_char);
						memcpy((void*)&hdr.seq, (void*)&sp.blk[i], sizeof(slint));
						i += sizeof(slint);
					}

					sint rc = GetInVec(&hdr, MTX_NET_FOUT, false, false);

					if (rc > -1)
					{
						BOT_FILE_M nfile;
						sint xc = GetVecEle(&nfile, MTX_FO, rc);

						if (xc > -1)
						{
							BOT_CLIENT_M cli;
							xc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

							if (xc > -1)
							{
								carr_512 ncar;
								bot_sprintf(ncar.carr, ncar.siz, "%s.%s", nfile.name.c_str(), nfile.type.c_str());
								BOT_FILE_CHK chk(hdr.idh, 0, bot_strlen(ncar.carr), ncar.carr);
								carr_16 rport;
								bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);
								bot_vblko oblk((_char)BOT_OP_VDAT, sp.addr.carr, rport.carr, 1);
								xc = oblk.Add(0, BOT_RTV_FLN, &chk, BOT_RTV_MAX);

								if (xc > -1)
								{
									xc = AddVPKO(stype, &oblk);
								}
							}
						}
						rc = ClearVecEle(MTX_NET_FOUT, rc, false);
					}
					break;
				}
				case BOT_OP_VDAT:
				{
					if (debug_lvl >= 1 && debug_m)
					{
						carr_128 outp;
						sint rc = bot_sprintf(outp.carr, outp.siz, "received vdat packet (%s port:%s type:%i) - data: %u bytes", sp.addr.carr, sp.servc.carr, stype, sp.siz);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					std::string datstr("data: ");
					size_t i = 1;

					while (i < sp.siz)
					{
						switch (sp.blk[i])
						{
						case BOT_RTV_SINT:
						{
							i += sizeof(_char);
							sint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sint));
							i += sizeof(sint);
							sint rc = bot_sprintfs(&datstr, false, "\n%i", xval);
							break;
						}
						case BOT_RTV_SLINT:
						{
							i += sizeof(_char);
							slint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint);
							sint rc = bot_sprintfs(&datstr, false, "\n%li", xval);
							break;
						}
						case BOT_RTV_SLLINT:
						{
							i += sizeof(_char);
							sllint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sllint));
							i += sizeof(sllint);
							sint rc = bot_sprintfs(&datstr, false, "\n%lli", xval);
							break;
						}
						case BOT_RTV_UINT:
						{
							i += sizeof(_char);
							uint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(uint));
							i += sizeof(uint);
							sint rc = bot_sprintfs(&datstr, false, "\n%u", xval);
							break;
						}
						case BOT_RTV_ULINT:
						{
							i += sizeof(_char);
							ulint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ulint));
							i += sizeof(ulint);
							sint rc = bot_sprintfs(&datstr, false, "\n%lu", xval);
							break;
						}
						case BOT_RTV_ULLINT:
						{
							i += sizeof(_char);
							ullint xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ullint));
							i += sizeof(ullint);
							sint rc = bot_sprintfs(&datstr, false, "\n%llu", xval);
							break;
						}
						case BOT_RTV_REAL:
						{
							i += sizeof(_char);
							float xval = 0;
							memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(float));
							i += sizeof(float);
							sint rc = bot_sprintfs(&datstr, false, "\n%.9f", xval);
							break;
						}
						case BOT_RTV_CHAR:
						{
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\n%c", sp.blk[i]);
							i += (sizeof(_char) + sizeof(_char));
							break;
						}
						case BOT_RTV_UCHAR:
						{
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\n%c", sp.blk[i]);
							i += (sizeof(u_char) + sizeof(_char));
							break;
						}
						case BOT_RTV_STR:
						{
							i += sizeof(_char);
							size_t ln = bot_strlen(&sp.blk[i]);

							if (sp.blk[i] == '/' && sp.blk[i + 1] == '#')
							{
								sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
								BOT_CLIENT_M cli;
								rc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

								if (rc > -1)
								{
									std::vector<BOT_ARG> avec;
									rc = ArgSep(&avec, false, i, sp.siz, sp.blk, BOT_RTV_VCHAR, &msy.nrts_sep, VTV_MAX);

									if (rc > -1)
									{
										rc = Command(&cli, &avec);
									}
								}
							}
							else
							{
								sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
							}
							i += (ln + sizeof(_char));
							break;
						}
						case BOT_RTV_VAR:
						{
							i += sizeof(_char);
							BOT_VAR_T nvar;
							nvar.t = sp.blk[i];
							i += sizeof(_char);
							sint rc = bot_sprintfs(&datstr, false, "\nvariable: $%s", &sp.blk[i]);
							size_t ln = bot_strlen(&sp.blk[i]);
							rc = FVAR(&sp.blk[i]);

							if (rc < 0)
							{
								nvar.n = (_char*)malloc(ln + 1);

								if (nvar.n)
								{
									_char trm = '\0';
									memcpy((void*)&nvar.n[ln], (void*)&trm, sizeof(_char));
									memcpy((void*)nvar.n, (void*)&sp.blk[i], ln);
									i += (ln + sizeof(_char));
									bool done = false;
									rc = 0;

									while (!done)
									{
										std::vector<_char> nvec;
										nvar.v.push_back(nvec);

										switch (nvar.t)
										{
										case BOT_RTV_SLLINT:
										{
											for (size_t x = 0; x < sizeof(sllint); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_REAL:
										{
											for (size_t x = 0; x < sizeof(float); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_STR:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										case BOT_RTV_BLOB:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										case BOT_RTV_VSLLINT:
										{
											for (size_t x = 0; x < sizeof(sllint); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_VREAL:
										{
											for (size_t x = 0; x < sizeof(float); x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											break;
										}
										case BOT_RTV_VSTR:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										case BOT_RTV_VBLOB:
										{
											ln = bot_strlen(&sp.blk[i]);
											for (size_t x = 0; x < ln; x++)
											{
												nvar.v[rc].push_back(sp.blk[i]);
												i += sizeof(_char);
											}
											i += sizeof(_char);
											break;
										}
										default:
										{
											break;
										}
										}
										if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
										{
											done = true;
										}
										else
										{
											rc++;
										}
									}
									rc = PushToVec(&nvar, MTX_VARS, true, true, false);
								}
							}
							rc = bot_sprintfs(&datstr, false, " %s", nvar.n);
							break;
						}
						case BOT_RTV_FHD:
						{
							i += sizeof(_char);
							bot_file_hdr nh;
							memcpy((void*)&nh.idh, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint);
							memcpy((void*)&nh.seq, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&nh.dsiz, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t);

							for (size_t x = 0; x < BOT_FILE_HCHUNK; x++)
							{
								slint v = 0;
								memcpy((void*)&v, (void*)&sp.blk[i], sizeof(slint));
								i += sizeof(slint);

								if (v == INT32_MAX)
								{
									x = BOT_FILE_HCHUNK;
								}
								else
								{
									nh.rec.push_back(v);
								}
							}

							if (nh.rec.empty())
							{
								sint rc = GetInVec(&nh, MTX_NET_FINC, false, false);

								if (rc > -1)
								{
									BOT_CLIENT_M cli;
									sint xc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

									if (xc > -1)
									{
										carr_16 rport;
										bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);

										if (!nh.rec.empty())
										{
											sint trs = 0;
											sint ct = 0;

											while (!nh.rec.empty() && trs < 10)
											{
												if (ct == 100)
												{
													for (size_t x = 0; x < nh.rec.size(); x++)
													{
														bot_vblko req((_char)BOT_OP_FCK, cli.prt.oipstr.carr, rport.carr, 1);
														xc = req.Add(0, BOT_RTV_SLINT, nh.idh, BOT_RTV_SINT, nh.seq, BOT_RTV_ULINT, x * BOT_FILE_CHUNK, BOT_RTV_MAX);

														if (xc > -1)
														{
															xc = AddVPKO(stype, &req);
														}
													}
													ct = 0;
													trs++;
												}
												sllint rst = Rest(BOT_MILLI_REST * 10);
												xc = GetVecEle(&nh, MTX_NET_FINC, rc, false);
												ct++;
											}
										}
										else
										{
											bot_vblko req((_char)BOT_OP_FCD, cli.prt.oipstr.carr, rport.carr, 1);
											xc = req.Add(0, BOT_RTV_SLINT, nh.idh, BOT_RTV_SINT, nh.seq, BOT_RTV_MAX);

											if (xc > -1)
											{
												xc = AddVPKO(stype, &req);
											}
										}
									}
									rc = ClearVecEle(MTX_NET_FINC, rc, false);
								}
							}
							else
							{
								carr_24 nm;
								bot_sprintf(nm.carr, nm.siz, "%li", nh.idh);
								BOT_FILE_M nf(nm.carr, "", BOTPathS(BOT_NETI_NM).c_str(), BOT_FILE_APND, BOT_F_CON);
								sint ct = 0;
								sint ox = -1;
								sint xc = BOTOpenFile(&nf, &ox);

								if (xc < 0)
								{
									nf.lid = -1;
									ox = -1;
									xc = BOTOpenFile(&nf, &ox, false, true);

									if (xc < 0)
									{
										bot_sprintfs(&datstr, false, "\nerror 30");
									}
									else
									{
										bot_sprintfs(&datstr, false, "\n%s\n%lu bytes 1", BOTFileStr(&nf).c_str(), (size_t)nf.fst.filestats.st_size);
										nh.fid = nf.lid;
										sint rc = PushToVec(&nh, MTX_NET_FINC, true, true, false);

										if (rc < 0)
										{
											bot_sprintfs(&datstr, false, "\nerror 10");
										}

										if (!ox)
										{
											ox = BOTCloseFile(&nf);
										}
									}
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%s\n%lu bytes 2", BOTFileStr(&nf).c_str(), (size_t)nf.fst.filestats.st_size);
									nh.fid = nf.lid;
									sint rc = PushToVec(&nh, MTX_NET_FINC, true, true, false);

									if (rc < 0)
									{
										bot_sprintfs(&datstr, false, "\nerror 10");
									}

									if (!ox)
									{
										ox = BOTCloseFile(&nf);
									}
								}
							}
							break;
						}
						case BOT_RTV_FLC:
						{
							BOT_FILE_CHK ck;
							i += sizeof(_char);
							memcpy((void*)&ck.idh, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.seq, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.f, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);
							memcpy((void*)&ck.t, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);

							if (ck.t > ck.f && ck.t - ck.f <= BOT_FILE_CHUNK)
							{
								bot_sprintfs(&datstr, false, "\nfile chunk: %li seq: %i\nfrom: %lu to: %lu", ck.idh, ck.seq, ck.f, ck.t);
								slint dsum = 0;

								for (size_t x = 0; x < ck.t - ck.f; x++)
								{
									dsum += (slint)sp.blk[i];
									i += sizeof(_char);
								}

								sint rc = ClearDSum(ck.idh, ck.seq, dsum);

								if (rc < 0)
								{
									BOT_CLIENT_M cli;
									rc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

									if (rc > -1)
									{
										carr_16 rport;
										bot_sprintf(rport.carr, rport.siz, "%i", cli.prt.rport);
										bot_vblko req((_char)BOT_OP_FCK, cli.prt.oipstr.carr, rport.carr, 1);
										rc = req.Add(0, BOT_RTV_SLINT, ck.idh, BOT_RTV_SINT, ck.seq, BOT_RTV_ULINT, ck.f, BOT_RTV_MAX);

										if (rc > -1)
										{
											rc = AddVPKO(stype, &req);
										}
									}
								}
								else
								{
									carr_24 nm;
									bot_sprintf(nm.carr, nm.siz, "%li", ck.idh);
									BOT_FILE_M nf(nm.carr, "", BOTPathS(BOT_NETI_NM).c_str(), BOT_FILE_OVRL, BOT_F_CON);
									sint ct = 0;
									sint ox = -1;
									rc = BOTOpenFile(&nf, &ox);

									if (rc > -1)
									{
										rc = BOTFileOUT(&nf, ck.f, ck.t, false, BOT_RTV_BLOB, &sp.blk[i], BOT_RTV_MAX);

										if (rc < 0)
										{
											bot_sprintfs(&datstr, false, "\nerror 20");
										}

										if (!ox)
										{
											BOTCloseFile(&nf);
										}
									}
								}
							}
							break;
						}
						case BOT_RTV_FLN:
						{
							BOT_FILE_CHK ck;
							i += sizeof(_char);
							memcpy((void*)&ck.idh, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.seq, (void*)&sp.blk[i], sizeof(slint));
							i += sizeof(slint) * sizeof(_char);
							memcpy((void*)&ck.f, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);
							memcpy((void*)&ck.t, (void*)&sp.blk[i], sizeof(size_t));
							i += sizeof(size_t) * sizeof(_char);
							carr_24 nm;
							bot_sprintf(nm.carr, nm.siz, "%li", ck.idh);
							BOT_FILE_M nf(nm.carr, "", BOTPathS(BOT_NETI_NM).c_str(), BOT_FILE_READ, BOT_F_CON);
							sint ox = -1;
							sint rc = BOTOpenFile(&nf, &ox, true, false, false, true);

							if (rc > -1)
							{
								BOT_FILE_M xf(&sp.blk[i], "", nf.path.c_str(), BOT_FILE_APND, BOT_F_CON, -1, lid);
								bot_sprintfs(&datstr, false, "\nfile name: %li\n%s", ck.idh, BOTFileStr(&xf).c_str());
								sint xx = -1;
								rc = BOTOpenFile(&xf, &xx);

								if (rc < 0)
								{
									xf.lid = -1;
									rc = BOTOpenFile(&xf, &xx, false, true);

									if (rc > -1)
									{
										rc = BOTFileOUT(&xf, 0, nf.dsiz - 1, false, BOT_RTV_BLOB, nf.datp, BOT_RTV_MAX);

										if (!xx)
										{
											xx = BOTCloseFile(&xf);
										}
									}
								}
								else
								{
									sint ct = 0;
									bool done = false;

									while (!done && ct < INT_MAX)
									{
										size_t len = xf.name.length();
										bot_sprintfs(&xf.name, false, "_%i", ct);
										rc = BOTOpenFile(&xf, &xx);

										if (rc < 0)
										{
											done = true;
											xf.lid = -1;
											rc = BOTOpenFile(&xf, &xx, false, true);

											if (rc > -1)
											{
												rc = BOTFileOUT(&xf, 0, nf.dsiz - 1, false, BOT_RTV_BLOB, nf.datp, BOT_RTV_MAX);

												if (!xx)
												{
													xx = BOTCloseFile(&xf);
												}
											}
										}
										else
										{
											if (!xx)
											{
												xx = BOTCloseFile(&xf);
											}
											len = xf.name.length() - len;
											for (size_t y = 0; y < len; y++)
											{
												xf.name.pop_back();
											}
											ct++;
										}
									}
								}

								if (!ox)
								{
									ox = BOTCloseFile(&nf, true, true, true);
								}
							}
							break;
						}
						case BOT_RTV_VSINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sint));
								i += sizeof(sint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%i,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VSLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								slint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(slint));
								i += sizeof(slint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%li,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VSLLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sllint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(sllint));
								i += sizeof(sllint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%lli,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VUINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								uint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(uint));
								i += sizeof(uint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%u,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VULINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								ulint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ulint));
								i += sizeof(ulint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%lu,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VULLINT:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								ullint xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(ullint));
								i += sizeof(ullint);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%llu,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VREAL:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								float xval = 0;
								memcpy((void*)&xval, (void*)&sp.blk[i], sizeof(float));
								i += sizeof(float);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%.9f,", xval);
								}
							}
							break;
						}
						case BOT_RTV_VCHAR:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%c,", sp.blk[i]);
									i += sizeof(_char);
								}
								i += sizeof(_char);
							}
							break;
						}
						case BOT_RTV_VUCHAR:
						{
							u_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									bot_sprintfs(&datstr, false, "\n%c,", sp.blk[i]);
									i += sizeof(u_char);
								}
								i += sizeof(u_char);
							}
							break;
						}
						case BOT_RTV_VSTR:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								size_t ln = bot_strlen(&sp.blk[i]);

								if (sp.blk[i] == '/' && sp.blk[i + 1] == '#')
								{
									sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
									BOT_CLIENT_M cli;
									rc = GetClientByPort(&cli, sp.addr.carr, atoi(sp.servc.carr), stype);

									if (rc > -1)
									{
										std::vector<BOT_ARG> avec;
										rc = ArgSep(&avec, false, i, sp.siz, sp.blk, BOT_RTV_VCHAR, &msy.nrts_sep, VTV_MAX);

										if (rc > -1)
										{
											rc = Command(&cli, &avec);
										}
									}
								}
								else
								{
									sint rc = bot_sprintfs(&datstr, false, "\n%s", &sp.blk[i]);
								}

								i += sizeof(_char);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
								else
								{
									i += (ln + sizeof(_char));
								}
							}
							break;
						}
						case BOT_RTV_VBLOB:
						{
							_char trm = '\0';
							i += sizeof(_char);
							bool done = false;

							while (!done)
							{
								sint rc = bot_sprintfs(&datstr, false, "%02X ", sp.blk[i]);
								i += sizeof(_char);

								if (sp.blk[i] == trm || sp.blk[i] == BOT_RTV_MAX)
								{
									datstr.pop_back();
									done = true;
								}
							}
							break;
						}
						default:
						{
							i = sp.siz;
							break;
						}
						}
					}
					if (debug_lvl >= 1 && debug_m)
					{
						sint rc = Output(0, true, datstr.c_str(), 2, 0);
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
			np->siz = 0;
			np = np->nxt;
		}

		np = bot_pkti[stype].nxt;

		while (np)
		{
			if (!np->siz)
			{
				bot_pkti[stype].nxt = np->nxt;
				np->ClearBlk();
				free(np);
				np = bot_pkti[stype].nxt;
			}
		}

		if (!hx)
		{
			hx = UnlockGMutex(MTX_VPKI);
		}
	}
	return lx;
}
sint machine::BOTServR(std::vector<ullint>* vals)
{
	if (debug_lvl >= 100 && debug_m)
	{
		carr_128 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "BOTServR(std::vector<ullint>* vals(%i))", (sint)vals);
		op = Output(outp.carr, 2);
	}

	std::string snm;
	sint rc = GetVecEleMem((void*)&snm, MTX_TTS, lid, BOT_TTS_TNAME);
	sint ret = rc = -1;
	sllint xret = 0;
	carr_64 nsvc;
	carr_512 add;

	if (vals)
	{
		if (!vals->empty())
		{
			if (vals->at(0) < UINT64_MAX)
			{
				rc = (sint)vals->at(0);
			}
			
			size_t z = 0;
			size_t ln = 0;
			size_t x = 1;

			for (; x < vals->size(); x++)
			{
				if (vals->at(x) < UINT64_MAX)
				{
					ln++;
				}
			}

			if (ln == 1)
			{
				ret = bot_sprintf(nsvc.carr, nsvc.siz, "%llu", vals->at(1));
			}
			else if (ln > 1)
			{
				_char trm = '\0';
				for (x = 1; x < vals->size(); x++)
				{
					if (vals->at(x) < UINT64_MAX)
					{
						_char v = (_char)vals->at(x);
						memcpy((void*)&nsvc.carr[z++], (void*)&v, sizeof(_char));
					}
					else
					{
						memcpy((void*)&nsvc.carr[z++], (void*)&trm, sizeof(_char));
						z = 0;

						for (x++; x < vals->size(); x++)
						{
							if (vals->at(x) < UINT64_MAX)
							{
								_char v = (_char)vals->at(x);
								memcpy((void*)&add.carr[z++], (void*)&v, sizeof(_char));
							}
							else
							{
								memcpy((void*)&add.carr[z++], (void*)&trm, sizeof(_char));
								x = vals->size();
							}
						}
						x = vals->size();
					}
				}
			}
			else {}
		}
	}

	bot_plug servp("", nsvc.carr, rc, AF_UNSPEC, true);
	std::vector<carr_64> bipv;

	if (bipv.empty())
	{
		carr_64 nc;

		while (GetVecEle((void*)&nc, MTX_BIPS, ret++, false) > -1)
		{
			bipv.push_back(nc);
		}
	}

	carr_256 outp;
	ret = servp.Open(AI_PASSIVE, true);

	if (ret)
	{
		rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
		rc = Output(0, true, outp.carr, 1, 0);
		return ret;
	}

	while (!ret)
	{
		if (debug_lvl >= 50 && debug_m)
		{
			rc = bot_sprintf(outp.carr, outp.siz, "host IP (%s)%s", servp.ifam.carr, servp.prt.ipstr.carr);
			rc = Output(0, true, outp.carr, 2, 0);
		}

		for (size_t y = 0; y < bipv.size(); y++)
		{
			if (!strcmp(bipv[y].carr, servp.prt.ipstr.carr))
			{
				rc = bot_sprintf(outp.carr, outp.siz, "Error:BannedIP(%s) port(%i) socket(%i)", servp.prt.ipstr.carr, servp.prt.portn, (sint)servp.prt.sck);
				rc = Output(outp.carr, 1);
				servp.Close();
				return ret;
			}
		}
		if (servp.prt.fam == AF_INET6)
		{
			ret = 1;
		}
		else
		{
			servp.Next();
		}
	}

	rc = ConnectionStatus(servp.prt.stype, 0, servp.prt.portn);

	while (rc > 0)
	{
		rc = ThreadRest(BOT_MILLI_REST, (sint)BOT_THRQ_CONS);

		if (rc)
		{
			servp.Close();
			return 0;
		}

		rc = ConnectionStatus(servp.prt.stype, 0, servp.prt.portn);

		if (rc == 2)
		{
			servp.Close();
			return 0;
		}
	}

	ret = GetInVec(&servp.prt, MTX_PORTS, false, false);
	ret = servp.Sock(false);

	if (ret)
	{
		servp.Close();
		rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
		rc = Output(0, true, outp.carr, 1, 0);
		return ret;
	}
	else
	{
		ret = PushToVec((void*)&servp.prt, MTX_PORTS, false, true, false);
	}

	if (ret > -1)
	{
		BOT_CLIENT_M cli;
		cli.atcons = false;

		if (debug_lvl >= 50 && debug_m)
		{
			carr_64 outp;
			bot_sprintf(outp.carr, outp.siz, "port:%i waiting for connections..", servp.prt.portn);
			rc = Output(0, true, outp.carr, 2, 0);
		}

		if (servp.prt.stype != SOCK_DGRAM)
		{
			ret = servp.Listen(10);

			if (ret)
			{
				servp.Close();
				rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
				rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
				rc = Output(0, true, outp.carr, 1, 0);
				return ret;
			}

			ret = servp.Accept();

			if (ret)
			{
				servp.Close();
				rc = ConnectionStatus(servp.prt.stype, 0, servp.prt.portn);

				if (rc < 2)
				{
					rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
					rc = Output(0, true, outp.carr, 1, 0);
				}
				rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
				return ret;
			}

			if (debug_lvl >= 50 && debug_m)
			{
				bot_strclr(outp.carr);
				rc = bot_sprintf(outp.carr, outp.siz, "accepted on socket(%i) port(%s) from (%s)", (sint)servp.prt.sck, servp.servc.carr, servp.prt.oipstr.carr);
				rc = Output(0, true, outp.carr, 2, 0);
			}

			rc = SetVecEleMem((void*)&servp.prt.sck, MTX_PORTS, servp.prt.lid, BOT_PORT_SCK, false);

			for (size_t y = 0; y < bipv.size(); y++)
			{
				if (!strcmp(bipv[y].carr, servp.prt.oipstr.carr))
				{
					rc = bot_sprintf(outp.carr, outp.siz, "Error:BannedIP(%s) port(%i) socket(%i)", servp.prt.oipstr.carr, servp.prt.portn, (sint)servp.prt.sck);
					rc = Output(outp.carr, 1);
					servp.Close();
					rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
					return ret;
				}
			}
		}

		if (ret > -1)
		{
			carr_256 ips;
			xret = 1;
			carr_32 indat;
			xret = servp.Rec(indat.carr, sizeof(BOT_HDR_PKT));

			if (xret < 0)
			{
				servp.Close();
				rc = ConnectionStatus(servp.prt.stype, 0, servp.prt.portn);

				if (rc < 2)
				{
					rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
					rc = Output(0, true, outp.carr, 1, 0);
				}

				rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
				return -1;
			}

			if (servp.prt.stype == SOCK_DGRAM)
			{
				for (size_t y = 0; y < bipv.size(); y++)
				{
					if (!strcmp(bipv[y].carr, servp.prt.oipstr.carr))
					{
						rc = bot_sprintf(outp.carr, outp.siz, "Error:BannedIP(%s) port(%i) socket(%i)", servp.prt.oipstr.carr, servp.prt.portn, (sint)servp.prt.sck);
						rc = Output(outp.carr, 1);
						servp.Close();
						rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
						return -1;
					}
				}
			}

			rc = GetClientByPort(&cli, servp.prt.oipstr.carr, servp.prt.portn, servp.prt.stype);

			if (rc < 0)
			{
				BOT_HDR_PKT* inp = reinterpret_cast<BOT_HDR_PKT*>(indat.carr);
				ret = KeyAServR(&inp->ka);

				if (xret == sizeof(BOT_HDR_PKT) && !ret && indat.carr[0] == BOT_OP_KNK)
				{
					inp->siz = ntohl(inp->siz);
					servp.prt.rport = (sint)inp->siz;
					cli.prt.Renew(&servp.prt);
					rc = KeyAServCreateII(&cli.prt.key_a);
					BOT_HDR_PKT fs(BOT_OP_KNK, 0, cli.prt.key_a);
					xret = servp.Send((_char*)&fs, sizeof(BOT_HDR_PKT));

					if (xret < 0)
					{
						servp.Close();
						rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
						rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
						rc = Output(0, true, outp.carr, 1, 0);
						return ret;
					}

					bot_strclr(indat.carr, indat.siz);
					xret = servp.Rec(indat.carr, sizeof(BOT_HDR_PKT));

					if (xret < 0)
					{
						servp.Close();
						rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
						rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
						rc = Output(0, true, outp.carr, 1, 0);
						return ret;
					}

					fs = *(reinterpret_cast<BOT_HDR_PKT*>(indat.carr));
					ret = KeyAServRecII(&fs.ka, &cli.prt.key_a);

					if (!ret)
					{
						fs.op[0] = (_char)BOT_OP_ESTA;
						xret = servp.Send((_char*)&fs, sizeof(BOT_HDR_PKT));

						if (xret < 0)
						{
							servp.Close();
							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
							rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
							rc = Output(0, true, outp.carr, 1, 0);
							return ret;
						}
					}
					else
					{
						servp.Close();
						rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
						rc = bot_sprintf(outp.carr, outp.siz, "Error:KeyA", servp.emsg.carr);
						rc = Output(0, true, outp.carr, 1, 0);
						return ret;
					}

					carr_256 cipstr;
					rc = bot_sprintf(cipstr.carr, cipstr.siz, "%s %i %i", cli.prt.oipstr.carr, cli.prt.rport, cli.prt.stype);
					rc = GetInVec((void*)&cipstr, MTX_CIPS, false, false);

					if (rc > -1)
					{
						cli.name.append("serv");
						cli.loggedin = true;
					}

					if (cli.lid > -1)
					{
						ret = SetVecEleMem((void*)&cli.prt.key_a, MTX_CV, cli.lid, BOT_C_KYA, false);
					}
					else
					{
						ret = PushToVec(&cli, MTX_CV, false, true, false);
					}

					if (debug_lvl >= 1 && debug_m)
					{
						rc = bot_sprintf(outp.carr, outp.siz, "connection on port(%s) socket(%i) from (%s)", servp.servc.carr, (sint)servp.prt.sck, servp.prt.oipstr.carr);
						rc = Output(0, true, outp.carr, 2, 0);
					}

					if (servp.prt.stype == SOCK_DGRAM)
					{
						bot_strclr(indat.carr, indat.siz);
						xret = servp.Rec(indat.carr, sizeof(BOT_HDR_PKT));

						if (xret < 0)
						{
							servp.Close();
							rc = ConnectionStatus(servp.prt.stype, 0, servp.prt.portn);

							if (rc < 2)
							{
								rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
							}

							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
						}
					}
					ret = 0;
				}
			}

			TINFO_M thr((sint)PTHREAD_CREATE_DETACHED, snm.c_str(), ServR, lid, 0.0f, vals);
			rc = InitThread(&thr);

			if (ret > -1 && xret > 0)
			{
				if (debug_lvl >= 50 && debug_m)
				{
					rc = bot_sprintf(outp.carr, outp.siz, "received data on port(%s) socket(%i) from (%s) size: %lli bytes", servp.servc.carr, (sint)servp.prt.sck, servp.prt.oipstr.carr, xret);
					rc = Output(0, true, outp.carr, 2, 0);
				}

				if (!cli.loggedin)
				{
					switch (indat.carr[0])
					{
					case BOT_OP_KNK:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received KNK packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						if (indat.carr[3])
						{
							_char op = (_char)BOT_OP_ACK;
							sllint nret = servp.Send(&op, sizeof(_char));

							if (nret < 0)
							{
								rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
							}
						}
						break;
					}
					case BOT_OP_SEC:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received SEC packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						BOT_HDR_PKT* np = reinterpret_cast<BOT_HDR_PKT*>(indat.carr);
						ret = KeyAServRecII(&np->ka, &cli.prt.key_a);

						if (ret)
						{
							servp.Close();
							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
							rc = bot_sprintf(outp.carr, outp.siz, "Error:KeyA", servp.emsg.carr);
							rc = Output(0, true, outp.carr, 1, 0);
							return ret;
						}

						np->siz = ntohl(np->siz);

						if (np->siz < 256)
						{
							_char* ind = (_char*)malloc(np->siz + 1);

							if (ind)
							{
								xret = servp.Rec(ind, np->siz);

								if (xret < 0)
								{
									servp.Close();
									rc = ConnectionStatus(servp.prt.stype, 0, servp.prt.portn);

									if (rc < 2)
									{
										rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
										rc = Output(0, true, outp.carr, 1, 0);
									}

									rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
									return -1;
								}

								if (indat.carr[3])
								{
									_char op = (_char)BOT_OP_ACK;
									sllint nret = servp.Send(&op, sizeof(_char));

									if (nret < 0)
									{
										rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
										rc = Output(0, true, outp.carr, 1, 0);
									}
								}

								if (xret > 0)
								{
									_char trm = '\0';
									memcpy((void*)&ind[xret], (void*)&trm, sizeof(_char));

									if (xret < 256)
									{
										bot_svblki nm(ind, np->siz);

										if (nm.siz > 2)
										{
											switch (nm.blk[0])
											{
											case BOT_OP_ESTA:
											{
												if (nm.blk[1] == BOT_RTV_STR)
												{
													cli.name.append(&nm.blk[2]);
													rc = SetVecEleMem((void*)&cli.name, MTX_CV, cli.lid, BOT_C_NAME, false);
												}
												break;
											}
											case BOT_OP_ESTB:
											{
												if (nm.blk[1] == BOT_RTV_STR)
												{
													rc = BOTGetLogin(&cli, &nm.blk[2]);

													if (cli.loggedin)
													{
														rc = SetVecEle((void*)&cli, MTX_CV, cli.lid, false, false);

														if (debug_lvl >= 1 && debug_m)
														{
															carr_384 outp;
															sint rc = bot_sprintf(outp.carr, outp.siz, "%s logged in.", cli.name.c_str());
															rc = Output(0, true, outp.carr, 2, 0);
														}

														carr_16 nport;
														rc = bot_sprintf(nport.carr, nport.siz, "%i", cli.prt.rport);
														bot_vblko rep((_char)BOT_OP_ESTC, cli.prt.oipstr.carr, nport.carr, 1);
														rc = AddSVPKO(servp.prt.stype, &rep);

														if (xret < 0)
														{
															servp.Close();
															rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
															rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
															rc = Output(0, true, outp.carr, 1, 0);
															return (sint)xret;
														}
													}
													else
													{
														carr_512 outp;
														bot_sprintf(outp.carr, outp.siz, "login failed %s addr:%s port:%s type:%i", cli.name.c_str(), servp.prt.oipstr.carr, servp.servc.carr, servp.prt.stype);
														rc = Output(0, true, outp.carr, 2, 0);
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
								}
								bot_strclr(ind, np->siz);
								free(ind);
							}
						}
						break;
					}
					case BOT_OP_CLS:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received CLS packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}

						_char op = (_char)BOT_OP_ACK;
						xret = servp.Send(&op, sizeof(_char));

						if (xret < 0)
						{
							servp.Close();
							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
							rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
							rc = Output(0, true, outp.carr, 1, 0);
							return (sint)xret;
						}
						carr_256 cipstr;
						rc = bot_sprintf(cipstr.carr, cipstr.siz, "%s %i %i", cli.prt.oipstr.carr, cli.prt.rport, cli.prt.stype);
						rc = GetInVec((void*)&cipstr, MTX_CIPS, false, false);

						if (rc > -1)
						{
							rc = ClearVecEle(MTX_CIPS, rc, false);
						}
						rc = ClearVecEle(MTX_CV, cli.lid, false);
						break;
					}
					default:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							rc = bot_sprintf(outp.carr, outp.siz, "received unknown packet socket(%i))", (sint)servp.prt.sck);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						if (indat.carr[3])
						{
							_char op = (_char)BOT_OP_ACK;
							sllint nret = servp.Send(&op, sizeof(_char));

							if (nret < 0)
							{
								rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
							}
						}
						break;
					}
					}
				}
				else
				{
					switch (indat.carr[0])
					{
					case BOT_OP_ACK:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							rc = bot_sprintf(outp.carr, outp.siz, "received packet ack port(%s) socket(%i) - data: %lli bytes", servp.servc.carr, (sint)servp.prt.sck, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						if (indat.carr[3])
						{
							_char op = (_char)BOT_OP_ACK;
							sllint nret = servp.Send(&op, sizeof(_char));

							if (nret < 0)
							{
								rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
							}
						}
						break;
					}
					case BOT_OP_KNK:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received KNK packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						if (indat.carr[3])
						{
							_char op = (_char)BOT_OP_ACK;
							sllint nret = servp.Send(&op, sizeof(_char));

							if (nret < 0)
							{
								rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
							}
						}
						break;
					}
					case BOT_OP_SEC:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received SEC packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						BOT_HDR_PKT* np = reinterpret_cast<BOT_HDR_PKT*>(indat.carr);
						ret = KeyAServRecII(&np->ka, &cli.prt.key_a);

						if (!ret)
						{
							/*np->op[0] = (_char)BOT_OP_ESTA;
							xret = servp.Send((_char*)np, sizeof(BOT_HDR_PKT));

							if (xret < 0)
							{
								servp.Close();
								rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
								rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
								return ret;
							}*/
						}
						else
						{
							servp.Close();
							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
							rc = bot_sprintf(outp.carr, outp.siz, "Error:KeyA", servp.emsg.carr);
							rc = Output(0, true, outp.carr, 1, 0);
							return ret;
						}

						np->siz = ntohl(np->siz);

						if (np->siz < BOT_FILESIZE_MAX - 1)
						{
							_char* ind = (_char*)malloc(np->siz + 1);

							if (ind)
							{
								xret = servp.Rec(ind, np->siz);

								if (xret < 0)
								{
									servp.Close();
									rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
									rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
									rc = Output(0, true, outp.carr, 1, 0);
									return -1;
								}

								if (xret > 0)
								{
									_char trm = '\0';
									memcpy((void*)&ind[xret], (void*)&trm, sizeof(_char));

									if (xret < BOT_FILESIZE_MAX)
									{
										rc = AddSVPKI(servp.prt.stype, np->siz, ind, servp.prt.oipstr.carr, servp.servc.carr, indat.carr[3]);
									}
								}
								if (indat.carr[3])
								{
									_char op = (_char)BOT_OP_ACK;
									sllint nret = servp.Send(&op, sizeof(_char));

									if (nret < 0)
									{
										rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
										rc = Output(0, true, outp.carr, 1, 0);
									}
								}
								bot_strclr(ind, np->siz);
								free(ind);
							}
							bot_strclr(indat.carr, indat.siz);
						}
						break;
					}
					case BOT_OP_SIZ:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received SIZ packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						BOT_HDR_PKT* np = reinterpret_cast<BOT_HDR_PKT*>(indat.carr);
						ret = KeyAServRecII(&np->ka, &cli.prt.key_a);

						if (!ret)
						{
							/*np->op[0] = (_char)BOT_OP_ESTA;
							xret = servp.Send((_char*)np, sizeof(BOT_HDR_PKT));

							if (xret < 0)
							{
							servp.Close();
							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
							rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
							rc = Output(0, true, outp.carr, 1, 0);
							return ret;
							}*/
						}
						else
						{
							servp.Close();
							rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
							rc = bot_sprintf(outp.carr, outp.siz, "Error:KeyA", servp.emsg.carr);
							rc = Output(0, true, outp.carr, 1, 0);
							return ret;
						}

						np->siz = ntohl(np->siz);

						if (np->siz < BOT_FILESIZE_MAX - 1)
						{
							_char* ind = (_char*)malloc(np->siz + 1);

							if (ind)
							{
								xret = servp.Rec(ind, np->siz);

								if (xret < 0)
								{
									servp.Close();
									rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
									rc = bot_sprintf(outp.carr, outp.siz, "Error:%s", servp.emsg.carr);
									rc = Output(0, true, outp.carr, 1, 0);
									return -1;
								}

								if (xret > 0)
								{
									_char trm = '\0';
									memcpy((void*)&ind[xret], (void*)&trm, sizeof(_char));

									if (xret < BOT_FILESIZE_MAX)
									{
										rc = AddVPKI(servp.prt.stype, np->siz, ind, servp.prt.oipstr.carr, servp.servc.carr, indat.carr[3]);
									}
								}
								if (indat.carr[3])
								{
									_char op = (_char)BOT_OP_ACK;
									sllint nret = servp.Send(&op, sizeof(_char));

									if (nret < 0)
									{
										rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
										rc = Output(0, true, outp.carr, 1, 0);
									}
								}
								bot_strclr(ind, np->siz);
								free(ind);
							}
							bot_strclr(indat.carr, indat.siz);
						}
						break;
					}
					case BOT_OP_CLS:
					{
						if (debug_lvl >= 50 && debug_m)
						{
							carr_128 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "received CLS packet (%s port:%s) - data: %lli bytes", servp.prt.oipstr.carr, servp.servc.carr, xret);
							rc = Output(0, true, outp.carr, 2, 0);
						}

						_char op = (_char)BOT_OP_ACK;
						sllint nret = servp.Send(&op, sizeof(_char));

						if (debug_lvl >= 1 && debug_m)
						{
							carr_384 outp;
							sint rc = bot_sprintf(outp.carr, outp.siz, "%s logged out.", cli.name.c_str());
							rc = Output(0, true, outp.carr, 2, 0);
						}
						carr_256 cipstr;
						rc = bot_sprintf(cipstr.carr, cipstr.siz, "%s %i %i", cli.prt.oipstr.carr, cli.prt.rport, cli.prt.stype);
						rc = GetInVec((void*)&cipstr, MTX_CIPS, false, false);

						if (rc > -1)
						{
							rc = ClearVecEle(MTX_CIPS, rc, false);
						}
						rc = ClearVecEle(MTX_CV, cli.lid, false);
						break;
					}
					default:
					{
						if (debug_lvl >= 1 && debug_m)
						{
							rc = bot_sprintf(outp.carr, outp.siz, "received unknown packet socket(%i))", (sint)servp.prt.sck);
							rc = Output(0, true, outp.carr, 2, 0);
						}
						if (indat.carr[3])
						{
							_char op = (_char)BOT_OP_ACK;
							sllint nret = servp.Send(&op, sizeof(_char));

							if (nret < 0)
							{
								rc = bot_sprintf(outp.carr, outp.siz, "Error:ACK", servp.emsg.carr);
								rc = Output(0, true, outp.carr, 1, 0);
							}
						}
						break;
					}
					}
				}
			}
			bot_strclr(indat.carr, indat.siz);
		}
	}

	if (debug_lvl >= 50 && debug_m)
	{
		rc = bot_sprintf(outp.carr, outp.siz, "closing port(%s) socket(%i) %i", servp.servc.carr, (sint)servp.prt.sck, servp.prt.stype);
		rc = Output(0, true, outp.carr, 2, 0);
	}

	servp.Close();
	rc = ClearVecEle(MTX_PORTS, servp.prt.lid, false);
	return ret;
}

// pthreads Functions

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

	if (LITEBot.pcn.empty())
	{
		LITEBot.pcn.append(LITEBot.BOTSessionName().c_str());
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
					std::string fn;
					bot_sprintfs(&fn, false, "%s_%s", LITEBot.pcn.c_str(), logm.logtitle.c_str());
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
							BOT_FILE_M xfile(fn.c_str(), ".txt", pth.c_str(), BOT_FILE_APND, BOT_F_CON, -1, LITEBot.lid);
							sint ox = -1;
							rc = LITEBot.BOTOpenFile(&xfile, &ox, false, true);

							if (rc > -1)
							{
								sint op = LITEBot.BOTFileOUT(&xfile, xfile.fst.e_loc, 0, false, BOT_RTV_VSTR, &bot_log_vec.dvec[siz].log_q, BOT_RTV_MAX);

								if (!op)
								{
									bot_log_vec.dvec[logm.lid].log_q.clear();
									rc = LITEBot.SetVecEleMem((void*)&bot_log_vec.dvec[logm.lid].log_q, MTX_LOG, logm.lid, BOT_LOG_Q, false);
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

	rc = LITEBot.Output("win_LITEBot_I 2018", 0, false);
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
	carr_1024 outp;
	carr_64 adcar;
	sint ret = gethostname(adcar.carr, adcar.siz);
	ret = bot_sprintf(outp.carr, outp.siz, "gethostname() = %s", adcar.carr);
	ret = LITEBot.Output(0, true, outp.carr, 2, 0);
	hostent *hoe = gethostbyname(adcar.carr);

	if (hoe != NULL)
	{
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

		ret = LITEBot.Output(0, true, outp.carr, 2, 0);
		bot_strclr(outp.carr, outp.siz);

#ifdef _WIN32
		struct in_addr addr;
		for (uint x = 0; hoe->h_addr_list[x] != NULL; x++)
		{
			addr.s_addr = *(uint*)hoe->h_addr_list[x];
			_char nadd[INET6_ADDRSTRLEN];
			ret = bot_sprintf(outp.carr, outp.siz, "Host IP: %s", inet_ntop(hoe->h_addrtype, &addr, nadd, INET6_ADDRSTRLEN));
			ret = LITEBot.Output(0, true, outp.carr, 2, 0);
		}
#else
		struct sockaddr_storage addr;
		for (uint x = 0; hoe->h_addr_list[x] != NULL; x++)
		{
			if (hoe->h_addrtype == AF_INET)
			{
				addr.sin_addr = *(struct sockaddr_in*)hoe->h_addr_list[x];
				_char nadd[INET6_ADDRSTRLEN];
				ret = bot_sprintf(outp.carr, outp.siz, "Host IP: %s", inet_ntop(hoe->h_addrtype, &addr, nadd, INET6_ADDRSTRLEN));
			}
			else if (hoe->h_addrtype == AF_INET6)
			{
				addr.sin_addr = *(struct sockaddr_in6*)hoe->h_addr_list[x];
				_char nadd[INET6_ADDRSTRLEN];
				ret = bot_sprintf(outp.carr, outp.siz, "Host IP: %s", inet_ntop(hoe->h_addrtype, &addr, nadd, INET6_ADDRSTRLEN));
			}
			else if (hoe->h_addrtype == AF_NETBIOS)
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
void* machine::ServR(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ServR", true, false);
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ServR(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	std::vector<ullint> vals;
	sint ret = LITEBot.GetVecEleMem((void*)&vals, MTX_TTS, LITEBot.lid, BOT_TTS_VALS);
	
	if (ret > -1)
	{
		ret = LITEBot.BOTServR(&vals);
	}

	rc = LITEBot.ThreadEnd();

	if (xc)
	{
		pthread_detach(pthread_self());
	}
	pthread_exit((void*)rc);
	return NULL;
}
void* machine::ServS(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ServS", true, false);
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ServS(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	std::vector<ullint> vals;
	sint ret = LITEBot.GetVecEleMem((void*)&vals, MTX_TTS, LITEBot.lid, BOT_TTS_VALS);

	if (ret > -1)
	{
		carr_64 nsvc;
		carr_512 add;
		sint rc = -1;

		if (!vals.empty())
		{
			if (vals[0] < UINT64_MAX)
			{
				rc = (sint)vals[0];
			}
			size_t z = 0;
			size_t ln = 0;
			size_t x = 1;

			for (; x < vals.size(); x++)
			{
				if (vals[x] < UINT64_MAX)
				{
					ln++;
				}
			}

			if (ln == 1)
			{
				bot_sprintf(nsvc.carr, nsvc.siz, "%llu", vals[1]);
			}
			else if (ln > 1)
			{
				_char trm = '\0';
				for (x = 1; x < vals.size(); x++)
				{
					if (vals[x] < UINT64_MAX)
					{
						_char v = (_char)vals[x];
						memcpy((void*)&nsvc.carr[z++], (void*)&v, sizeof(_char));
					}
					else
					{
						memcpy((void*)&nsvc.carr[z++], (void*)&trm, sizeof(_char));
						z = 0;

						for (x++; x < vals.size(); x++)
						{
							if (vals[x] < UINT64_MAX)
							{
								_char v = (_char)vals[x];
								memcpy((void*)&add.carr[z++], (void*)&v, sizeof(_char));
							}
							else
							{
								memcpy((void*)&add.carr[z++], (void*)&trm, sizeof(_char));
								x = vals.size();
							}
						}
						x = vals.size();
					}
				}
			}
			else {}
		}

		while (ret > -1)
		{
			ret = LITEBot.VPKO(rc);

			if (ret < 0)
			{
				rc = LITEBot.ThreadEnd();

				if (xc)
				{
					pthread_detach(pthread_self());
				}
				pthread_exit((void*)rc);
				return NULL;
			}

			ret = LITEBot.SVPKO(rc);

			if (ret < 0)
			{
				rc = LITEBot.ThreadEnd();

				if (xc)
				{
					pthread_detach(pthread_self());
				}
				pthread_exit((void*)rc);
				return NULL;
			}
			else
			{
				ret = LITEBot.ThreadRest(BOT_MILLI_REST, BOT_THRQ_CONS);

				if (ret)
				{
					ret = -1;
				}
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
void* machine::ServP(void* vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ServP", true, false);
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ServP(void* vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	std::vector<ullint> vals;
	sint ret = LITEBot.GetVecEleMem((void*)&vals, MTX_TTS, LITEBot.lid, BOT_TTS_VALS);

	if (ret > -1)
	{
		while (ret > -1)
		{
			ret = LITEBot.BOTServP((sint)vals[0]);

			if (ret < 0)
			{
				rc = LITEBot.ThreadEnd();

				if (xc)
				{
					pthread_detach(pthread_self());
				}
				pthread_exit((void*)rc);
				return NULL;
			}

			ret = LITEBot.BOTServPS((sint)vals[0]);

			if (ret < 0)
			{
				rc = LITEBot.ThreadEnd();

				if (xc)
				{
					pthread_detach(pthread_self());
				}
				pthread_exit((void*)rc);
				return NULL;
			}
			else
			{
				if (!ret)
				{
					ret = LITEBot.ThreadRest(BOT_SERVREST, BOT_THRQ_CONS);

					if (ret)
					{
						ret = -1;
					}
				}
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
	bot_plug clip(0, "3141", SOCK_STREAM, AF_UNSPEC);

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