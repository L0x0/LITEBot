#include "litebot.h"

sint main()
{
	sint xc = 0;
	cchar* err_ret = "";
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, 0, "machine", true, true);
	xc = LITEBot.LITEBot(err_ret, true);
	
	switch ( xc )
	{
		case 0 :
		{
			break;
		}
		default :
		{
			break;
		}
	}
	
	pthread_exit( NULL );
	return 0;
}

sint machine::LITEBot(cchar* cret_, bool do_start_up)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint rc = bot_sprintf(outp.carr, outp.siz, "LITEBot(cchar* cret_(\"%s\"), bool do_start_up(%u))", cret_, (uint)do_start_up);
		rc = Output(outp.carr, 2);
	}
	//if (do_start_up)
	//{
		//sint xc = AddDlrCode("4T1B11HK7JU059277");
	//}
	TINFO tts(0,ptn.c_str());
	tts.lid = lid;
	tts.fin = 0;
	tts.t_I = std::chrono::steady_clock::now();
	sint xc = PushToVec(&tts, MTX_TTS, true, true, false);

	if (do_start_up)
	{
		xc = LITEBotStartUp();

		if (!xc)
		{
			while (!quit)
			{
				xc = LITEBotProcess();
			}

			switch (xc)
			{
			case 1:
			{
				sint rc = Output("LITEBotProcess() fault.", 1, 2, -1);
				break;
			}
			case (-1):
			{
				sint rc = Output("LITEBotProcess() quit.", 1, 2, -1);
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
				sint rc = Output("start up broken", 1, 2, 0, -1);
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

sint machine::LITEBotStartUp()
{
	sint xc = DoIntro();
	xc = VerifyDatabases();

	if (xc)
	{
		sint oc = Output("VerifyDatabases fault.", 1, 2, 0, -1);
		oc = Output("VerifyDatabases fault.", 1, 2, 0, -1);
	}
	else
	{
		xc = TM(0);
	}
	return xc;
}

sint machine::LITEBotProcess()
{
	sint xc = 0;

	while (!xc && !quit)
	{
		if (!VecSize(MTX_CV))
		{
			xc = DoLogin();

			/*if (xc || quit)
			{
				break;
			}*/
		}
		else
		{
			xc = Input();

			/*if (xc || quit)
			{
				break;
			}*/

			xc = DoOutput();

			/*if (xc || quit)
			{
				break;
			}*/
		}
	}

	if (quit)
	{
		return -1;
	}
	return xc;
}

sint machine::DoLogin()
{
	std::string namestr;
	sint xc = GetName(&namestr);

	if (!namestr.empty())
	{
		xc = InterpretInput(&namestr);
	}
	else
	{
		return 1;
	}

	if (Client_->nameset)
	{
		xc = DoGreeting();
	}

	return 0;
}

sint machine::GetName(std::string *str_)
{
	std::string output;
	output.append("Who's this?");
	sint xc = Output(output.c_str(), 0);
	std::getline(std::cin, *str_);
	xc = LogPut(str_->c_str(), 0);
	return 0;
}

sint machine::InterpretInput(std::string *input_)
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

	if (input_->length() > 2)
	{
		if (input_->at(0) == '/' && input_->at(1) == '#')
		{
			std::vector<std::string> vec;
			uchar c;
			c = ' ';
			sint xc = SeparateStrByChar(input_, &c, &vec, 1);
			input_->clear();
			//xc = SeparateSymbolsI( &PInputStruct, 5, 1 );
			//xc = SeparateSymbolsII( &PInputStruct, 0 );
			xc = _Command(&vec);

			if (!xc)
			{
				return xc;
			}
		}
	}
	return 0;
}

sint machine::SeparateStrBySymbols(std::string *str_, std::vector<std::string> *vec_, std::vector<std::string> *rvec_, sint sort_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrBySymbols(std::string *str_(%i), std::vector<std::string> *vec_(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)vec_, (sint)rvec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 10)
		{
			op = Output(str_->c_str(), 2);
		}
	}
	if (str_->length())
	{
		if (vec_->empty())
		{
			vec_->push_back(" ");
			vec_->push_back("\n");
		}

		std::string Sym;
		sint last_was = -1;
		for (size_t sx = 0; sx < (sint)str_->length(); sx++)
		{
			size_t x = 0;
			for (x = 0; x < (sint)vec_->size(); x++)
			{
				if (sx + (sint)vec_->at(x).length() <= (sint)str_->length())
				{
					if (debug_lvl >= 700 && debug_m)
					{
						std::string output;
						output.append("comparing \"");
						output.append(vec_->at(x));
						output.append("\" vs. \"");
						output.append(str_->substr(sx, vec_->at(x).length()));
						output.append("\"");
						sint xc = Output(output.c_str(), 2);
					}

					if (!strcmp(vec_->at(x).c_str(), str_->substr(sx, vec_->at(x).length()).c_str()))
					{
						if (last_was != x)
						{
							rvec_->push_back(Sym);
							Sym.clear();
						}

						Sym.append(str_->substr(sx, vec_->at(x).length()));
						sx += (sint)vec_->at(x).length() - 1;
						last_was = x;
						x = (sint)vec_->size();
					}
				}
			}
			if (x == (sint)vec_->size())
			{
				if (last_was != -1)
				{
					rvec_->push_back(Sym);
					Sym.clear();
				}

				Sym.append(str_->substr(sx, 1));
				last_was = -1;
			}
		}

		if (!Sym.empty())
		{
			rvec_->push_back(Sym);
		}
	}

	if (rvec_->empty())
	{
		rvec_->push_back(*str_);
	}
	else
	{
		if (sort_opt == 2 || sort_opt == 3)
		{
			std::vector<std::string> RevSymVec;
			for (sint r = (sint)rvec_->size() - 1; r > -1; r--)
			{
				if (!rvec_->at(r).empty())
				{
					RevSymVec.push_back(rvec_->at(r));
				}
			}
			*rvec_ = RevSymVec;
		}
	}
	return 0;
}

sint machine::SeparateStrByStr(std::string *str_, std::string *sstr_, std::vector<std::string> *rvec_, sint sort_opt)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrByStr(std::string *str_(%i), std::string *sstr_(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)sstr_, (sint)rvec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 700)
		{
			op = Output(str_->c_str(), 2);
		}
	}

	if (!str_)
	{
		return -1;
	}

	sint x = 0;
	bool last_was = true;
	for (size_t sx = 0; sx < (sint)str_->length(); sx++)
	{
		if (sx + (sint)sstr_->length() <= (sint)str_->length())
		{
			if (debug_lvl >= 700 && debug_m)
			{
				std::string output;
				output.append("comparing \"");
				output.append(*sstr_);
				output.append("\" vs. \"");
				output.append(str_->substr(sx, sstr_->length()));
				output.append("\"");
				sint xc = Output(output.c_str(), 2);
			}

			if (!strcmp(sstr_->c_str(), str_->substr(sx, sstr_->length()).c_str()))
			{
				if (last_was)
				{
					rvec_->push_back(str_->substr(x, sx - x));
					x = sx;
				}

				sx += (sint)sstr_->length() - 1;
				last_was = false;

				if (sx == (sint)str_->length() - 1)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str_->substr(x, (sint)str_->length() - x));
					}
				}
			}
			else
			{
				if (!last_was)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str_->substr(x, sx - x));
					}

					x = sx;
				}

				last_was = true;

				if (sx == (sint)str_->length() - 1)
				{
					rvec_->push_back(str_->substr(x, (sint)str_->length() - x));
				}
			}
		}
	}
	if (rvec_->empty())
	{
		rvec_->push_back(*str_);
	}
	else
	{
		if (sort_opt == 2 || sort_opt == 3)
		{
			std::vector<std::string> RevSymVec;
			for (sint r = (sint)rvec_->size() - 1; r > -1; r--)
			{
				if (!rvec_->at(r).empty())
				{
					RevSymVec.push_back(rvec_->at(r));
				}
			}
			*rvec_ = RevSymVec;
		}
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

sint machine::SeparateStrByCChar(std::string *str_, cchar *sstr_, std::vector<std::string> *rvec_, sint sort_opt)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrByCChar(std::string *str_(%i), cchar *sstr_(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)sstr_, (sint)rvec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 700 && str_)
		{
			op = Output(str_->c_str(), 2);
		}
	}
	if (!str_ || !rvec_)
	{
		return -1;
	}

	if (!sstr_)
	{
		size_t siz = 0;

		while (siz < str_->length())
		{
			std::string nstr;
			nstr.push_back(str_->at(siz));
			rvec_->push_back(nstr);
			siz++;
		}
		return 0;
	}

	size_t sslen = strlen(sstr_);

	if (!str_->empty())
	{
		sint x = 0;
		bool last_was = true;

		for (size_t sx = 0; sx < str_->length(); sx++)
		{
			if (sx + sslen <= (sint)str_->length())
			{
				if (debug_lvl >= 700 && debug_m)
				{
					std::string output;
					output.append("comparing \"");
					output.append(sstr_);
					output.append("\" vs. \"");
					output.append(str_->substr(sx, sslen));
					output.append("\"");
					sint xc = Output(output.c_str(), 2);
				}

				if (!strcmp(sstr_, str_->substr(sx, sslen).c_str()))
				{
					if (last_was)
					{
						rvec_->push_back(str_->substr(x, sx - x));
						x = sx;
					}

					sx += sslen - 1;
					last_was = false;

					if (sx == (sint)str_->length() - 1)
					{
						if (sort_opt == 2 || !sort_opt)
						{
							rvec_->push_back(str_->substr(x, (sint)str_->length() - x));
						}
					}
				}
				else
				{
					if (!last_was)
					{
						if (sort_opt == 2 || !sort_opt)
						{
							rvec_->push_back(str_->substr(x, sx - x));
						}

						x = sx;
					}

					last_was = true;

					if (sx == (sint)str_->length() - 1)
					{
						rvec_->push_back(str_->substr(x, (sint)str_->length() - x));
					}
				}
			}
		}
	}

	if (rvec_->empty())
	{
		std::string nstr;
		nstr.append(str_->c_str());
		rvec_->push_back(nstr);
	}
	else
	{
		if (sort_opt == 2 || sort_opt == 3)
		{
			std::vector<std::string> RevSymVec;
			for (sint r = (sint)rvec_->size() - 1; r > -1; r--)
			{
				if (!rvec_->at(r).empty())
				{
					RevSymVec.push_back(rvec_->at(r));
				}
			}
			*rvec_ = RevSymVec;
		}
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

sint machine::SeparateStrByChar(std::string *str_, uchar *chr, std::vector<std::string> *rvec_, sint sort_opt)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "SeparateStrByChar(std::string *str_(%i), uchar *chr(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)chr, (sint)rvec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 700 && str_)
		{
			op = Output(str_->c_str(), 2);
		}
	}

	if (!str_ || !rvec_)
	{
		return -1;
	}
	if (!chr)
	{
		for (size_t siz = 0; siz < str_->length(); siz++)
		{
			std::string nstr;
			nstr.push_back(str_->at(siz));
			rvec_->push_back(nstr);
		}
		return 0;
	}

	if (!str_->empty())
	{
		sint x = 0;
		bool last_was = true;
		for (uint sx = 0; sx < str_->length(); sx++)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				std::string output;
				output.append("comparing \"");
				output.push_back(*chr);
				output.append("\" vs. \"");
				output.push_back(str_->at(sx));
				output.append("\"");
				sint xc = Output(output.c_str(), 2);
			}

			if (*chr == str_->at(sx))
			{
				if (last_was)
				{
					rvec_->push_back(str_->substr(x, sx - x));
					x = sx;
				}

				last_was = false;

				if (sx == (sint)str_->length() - 1)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str_->substr(x, (sint)str_->length() - x));
					}
				}
			}
			else
			{
				if (!last_was)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str_->substr(x, sx - x));
					}

					x = sx;
				}

				last_was = true;

				if (sx == (sint)str_->length() - 1)
				{
					rvec_->push_back(str_->substr(x, (sint)str_->length() - x));
				}
			}
		}
	}

	if (rvec_->empty())
	{
		std::string nstr;
		nstr.push_back(*(char*)str_);
		rvec_->push_back(nstr);
	}
	else
	{
		if (sort_opt == 2 || sort_opt == 3)
		{
			std::vector<std::string> RevSymVec;
			for (sint r = (sint)rvec_->size() - 1; r > -1; r--)
			{
				if (!rvec_->at(r).empty())
				{
					RevSymVec.push_back(rvec_->at(r));
				}
			}
			*rvec_ = RevSymVec;
		}
	}

	if (debug_lvl >= 700 && debug_m)
	{
		std::string output;
		for (uint r = 0; r < rvec_->size(); r++)
		{
			output.append("\n");
			output.append(rvec_->at(r));
		}
		sint xc = Output(output.c_str(), 2);
	}
	return 0;
}

sint machine::SeparateCByChar(cchar* cstr_, uchar *chr, std::vector<cchar* > *rvec_, sint sort_opt)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "SeparateCByChar(cchar* cstr_(%i), uchar *chr(%i), std::vector<cchar* > *rvec_(%i), sint sort_opt(%i))", (sint)cstr_, (sint)chr, (sint)rvec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 700 && cstr_)
		{
			op = Output(cstr_, 2);
		}
	}

	if (!cstr_ || !chr || !rvec_)
	{
		return -1;
	}

	if (!chr)
	{
		size_t siz = 0;

		while (siz < sizeof(*cstr_))
		{
			cchar* ncar = (cchar*)cstr_[siz];
			rvec_->push_back(ncar);
			siz++;
		}
		return 0;
	}
	std::string str;
	str.append(cstr_);

	if (!str.empty())
	{
		sint x = 0;
		bool last_was = true;
		for (uint sx = 0; sx < str.length(); sx++)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				std::string output;
				output.append("comparing \"");
				output.push_back(*chr);
				output.append("\" vs. \"");
				output.push_back(str.at(sx));
				output.append("\"");
				sint xc = Output(output.c_str(), 2);
			}

			if (*chr == str.at(sx))
			{
				if (last_was)
				{
					rvec_->push_back(str.substr(x, sx - x).c_str());
					x = sx;
				}

				last_was = false;

				if (sx == (sint)str.length() - 1)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str.substr(x, (sint)str.length() - x).c_str());
					}
				}
			}
			else
			{
				if (!last_was)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str.substr(x, sx - x).c_str());
					}
					x = sx;
				}

				last_was = true;

				if (sx == (sint)str.length() - 1)
				{
					rvec_->push_back(str.substr(x, (sint)str.length() - x).c_str());
				}
			}
		}
	}

	if (rvec_->empty())
	{
		rvec_->push_back(cstr_);
	}
	else
	{
		if (sort_opt == 2 || sort_opt == 3)
		{
			std::vector<cchar* > RevSymVec;

			for (sint r = (sint)rvec_->size() - 1; r > -1; r--)
			{
				if (strlen(rvec_->at(r)))
				{
					RevSymVec.push_back(rvec_->at(r));
				}
			}
			*rvec_ = RevSymVec;
		}
	}
	if (debug_lvl >= 700 && debug_m)
	{
		std::string output;
		for (uint r = 0; r < rvec_->size(); r++)
		{
			output.append("\n");
			output.append(rvec_->at(r));
		}
		sint xc = Output(output.c_str(), 2);
	}
	return 0;
}

sint machine::SeparateCByChar(cchar* cstr_, uchar *chr, std::vector<std::string> *rvec_, sint sort_opt)
{
	if (debug_lvl >= 700 && debug_m)
	{
		carr_256 outp;
		sint op = bot_sprintf(outp.carr, outp.siz, "SeparateCByChar(cchar* cstr_(%i), uchar *chr(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)cstr_, (sint)chr, (sint)rvec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 700 && cstr_)
		{
			op = Output(cstr_, 2);
		}
	}

	if (!cstr_ || !rvec_)
	{
		return -1;
	}

	if (!chr)
	{
		size_t slen = strlen(cstr_);

		for (size_t siz = 0; siz < slen; siz++)
		{
			std::string nstr;
			nstr.push_back(cstr_[siz]);
			rvec_->push_back(nstr);
		}
		return 0;
	}

	std::string str;
	str.append(cstr_);

	if (!str.empty())
	{
		sint x = 0;
		bool last_was = true;
		for (uint sx = 0; sx < (sint)str.length(); sx++)
		{
			if (debug_lvl >= 700 && debug_m)
			{
				std::string output;
				output.append("comparing \"");
				output.push_back(*chr);
				output.append("\" vs. \"");
				output.push_back(str.at(sx));
				output.append("\"");
				sint xc = Output(output.c_str(), 2);
			}

			if (*chr == str.at(sx))
			{
				if (last_was)
				{
					rvec_->push_back(str.substr(x, sx - x));
					x = sx;
				}

				last_was = false;

				if (sx == str.length() - 1)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str.substr(x, (sint)str.length() - x).c_str());
					}
				}
			}
			else
			{
				if (!last_was)
				{
					if (sort_opt == 2 || !sort_opt)
					{
						rvec_->push_back(str.substr(x, sx - x).c_str());
					}

					x = (sint)sx;
				}

				last_was = true;

				if (sx == (sint)str.length() - 1)
				{
					rvec_->push_back(str.substr(x, (sint)str.length() - x).c_str());
				}
			}
		}
	}

	if (rvec_->empty())
	{
		std::string nstr;
		nstr.append(cstr_);
		rvec_->push_back(nstr);
	}
	else
	{
		if (sort_opt == 2 || sort_opt == 3)
		{
			std::vector<std::string> RevSymVec;
			sint r = 0;
			for (r = 0; r < (sint)rvec_->size(); r++)
			{
				if (!rvec_->at(r).empty())
				{
					RevSymVec.push_back(rvec_->at(r));
				}
			}

			for (r = (sint)RevSymVec.size() - 1; r > -1; r--)
			{
				if (!RevSymVec[r].empty())
				{
					rvec_->push_back(RevSymVec[r]);
				}
			}
		}
	}

	if (debug_lvl >= 700 && debug_m)
	{
		std::string output;
		for (uint r = 0; r < rvec_->size(); r++)
		{
			output.append("\n");
			output.append(rvec_->at(r));
		}
		sint xc = Output(output.c_str(), 2);
	}
	return 0;
}

std::vector<std::string> machine::SeparateCharGroups(cchar* clientinput_ )
{
	std::vector<std::string> istr, swap;
	std::string clientinput;
	clientinput.append(clientinput_);
	std::vector<char> enders
	{
		'\n',
		' ',
		'\0'
	};
	
	bool done = false;
	sint loc = -1;
	
	if ( debug_lvl >= 25 && debug_m )
	{
		std::string output;
		output.append( "Separating groups of chars in std::string:" );
		Output(output.c_str(), 2 );
		Output(clientinput_, 2 );
	}
	
	sint x = 0;
	
	while ( !done )
	{
		if ( clientinput.length() > 0 )
		{
			if ( debug_lvl >= 30 && debug_m )
			{
				std::string output;
				output.append( "input length was >0" );
				Output(output.c_str(), 2 );
				Output(clientinput_, 2 );
			}
			
			sint endloc = (sint)clientinput.length() - 1;
			sint atloc = endloc;
			
			while ( atloc > -1 )
			{
				sint e = 0;
				
				while ( e < (sint)enders.size() )
				{
					if ( clientinput[ atloc ] == enders[ e ] )
					{
						if ( atloc == endloc )
						{
							clientinput.pop_back();
							e = 0;
						}
						
						else
						{
							istr.push_back( clientinput.substr( atloc + 1, ( endloc - ( atloc ) ) ) );
							clientinput.erase( atloc, ( endloc - atloc + 1 ) );
							endloc = clientinput.length() - 1;
							atloc = endloc;
							e = (sint)enders.size() + 1;
						}
					}
					
					else
					{
						e++;
					}
					
					if ( e == (sint)enders.size() )
					{
						atloc--;
					}
					
					if ( atloc == 0 )
					{
						istr.push_back( clientinput );
						clientinput.clear();
						atloc--;
					}
				}
			}
		}
		
		else
		{
			done = true;
		}
	}

	sint i = (sint)istr.size() - 1;
	
	while ( i > -1 )
	{
		swap.push_back( istr[ i ] );
		istr.pop_back();
		i--;
	}

	i = 0;
	
	if ( debug_lvl >= 25 && debug_m )
	{
		std::string output;
		output.append( "vector built\n" );
		Output(output.c_str(), 2 );
		
		while ( i < (sint)swap.size() )
		{
			output.append( ITOA( i ) );
			output.append( ": " );
			output.append( swap[ i ] );
			output.append( "\n" );
			i++;
		}
		
		sint xc = Output(output.c_str(), 2 );
	}
	
	return swap;
}

sint machine::GetClient(BOT_CLIENT *Client_ )
{
	*Client_ = *Client_;
	return 0;
}

sint machine::SetClient(BOT_CLIENT *Client_ )
{
	*Client_ = *Client_;
	return 0;
}

sint machine::SetClientName(std::string* ClientName )
{
	Client_->name.clear();
	Client_->name.append(*ClientName);
	Client_->nameset = true;
	return 0;
}

sint machine::GetClientName(std::string* str_ )
{
	str_->clear();
	str_->append(Client_->name.c_str() );
	return 0;
}

sint machine::SetClientLoginName(std::string* ClientLoginName )
{
	Client_->login_name.clear();
	Client_->login_name.append( *ClientLoginName);
	return 0;
}

sint machine::GetClientLoginName(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	if (!str_->empty())
	{
		str_->clear();
	}

	str_->append(Client_->login_name.c_str());

	return 0;
}

sint machine::SetClientLastLogin(std::string* LastLogin = 0)
{
	if (!LastLogin)
	{
		return -1;
	}

	Client_->lastlogin.clear();
	Client_->lastlogin.append(LastLogin->c_str());
	return 0;
}

sint machine::GetClientLastLogin(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client_->lastlogin.c_str());
	return 0;
}

sint machine::SetClientLastFailedLogin(std::string* LastFailedLogin = 0)
{
	if (!LastFailedLogin)
	{
		return -1;
	}

	Client_->last_failed_login.clear();
	Client_->last_failed_login.append(LastFailedLogin->c_str());
	return 0;
}

sint machine::GetClientLastFailedLogin(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client_->last_failed_login.c_str());
	return 0;
}

sint machine::SetClientLastExchange(std::string* LastExchange = 0)
{
	if (!LastExchange)
	{
		return -1;
	}
	Client_->lastexchange.clear();
	Client_->lastexchange.append(LastExchange->c_str());
	return 0;
}

sint machine::GetClientLastExchange(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client_->lastexchange.c_str());
	return 0;
}

sint machine::SetClientLoginDate(std::string* LoginDate = 0)
{
	if (!LoginDate)
	{
		return -1;
	}

	Client_->logindate.clear();
	Client_->logindate.append(LoginDate->c_str());
	return 0;
}

sint machine::GetClientLoginDate(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client_->logindate.c_str());
	return 0;
}

sint machine::SetClientID(sint x)
{
	Client_->lid = x;
	return 0;
}

sint machine::GetClientID()
{
	sint xc = Client_->lid;
	return xc;
}

sint machine::SetClientPriv(sint x)
{
	Client_->priv = x;
	return 0;
}

sint machine::GetClientPriv()
{
	sint xc = Client_->priv;
	return xc;
}

sint machine::SetClientTotalLogins(sint x)
{
	Client_->totallogins = x;
	return 0;
}

sint machine::GetClientTotalLogins()
{
	sint xc = Client_->totallogins;
	return xc;
}

sint machine::SetClientFailedLogins(sint x)
{
	Client_->failed_logins = x;
	return 0;
}

sint machine::GetClientFailedLogins()
{
	sint xc = Client_->failed_logins;
	return xc;
}

sint machine::SetClientLoggedIn(bool x)
{
	Client_->loggedin = x;
	return 0;
}

bool machine::GetClientLoggedIn()
{
	bool x = Client_->loggedin;
	return x;
}

sint machine::DoOutput()
{
	if (Client_->name.empty())
	{
		return 0;
	}

	std::string output = DetermineOutput();
	sint oc = Output(output.c_str(), 0);
	return oc;
}

sint machine::DoIntro()
{
	sint xc = Output("LITEBot XXIX 2017", 0);
	return 0;
}

std::string machine::DetermineOutput()
{
	std::string suboutput;
	return suboutput;
}

sint machine::DoGreeting()
{
	std::string output;
	std::string name;
	sint xc = GetClientName(&name );
	
	if ( xc )
	{
		return xc;
	}
	else
	{
		xc = GetClientID();
	}
	
	if ( !strcmp( Uppercase(name.c_str() ).c_str(), "LOXO" ) && xc == 2 )
	{
		output.append( "Hail, " );
		output.append( name );
		xc = Output(output.c_str(), 0 );
		output.clear();
		srand( (UINT)time( 0 ) );
		sint questionmk1( rand() % 10 );
		
		if ( questionmk1 == 0 )
		{
			output.append( "Wie gehts?" );
		}
		else if ( questionmk1 == 1 )
		{
			output.append( "What's up?" );
		}
		else
		{
			output.append( "What do you wish of me, oh Great One?" );
		}
	}
	else
	{
		output.append( "I don't know you " );
		output.append( name );
		output.append( "." );
	}
	
	xc = Output(output.c_str(), 0 );
	return 0;
}

sint machine::_Command(std::vector<std::string> *vec_)
{
	BOTCOMMAND Command;
	Command.cmd.append(vec_->at(0));
	std::vector<BOTCOMMAND> cmdvec;
	std::vector<std::string> conds;
	sint xc = GetCommand(&Command, &cmdvec, &conds);

	if (cmdvec.empty())
	{
		return 1;
	}

	Command = cmdvec[0];
	cmdvec.clear();

	if (debug_lvl >= 1 && debug_m)
	{
		std::string output;
		output.append("Finding Command by id: ");
		xc = Output(output.c_str(), 2);
	}

	switch (Command.cmd_id)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		std::string output;
		output.append("Telling threads to finish");
		sint oc = Output(output.c_str(), 2);
		xc = StopAllThreads();
		output.clear();
		output.append("quitting\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");
		xc = Output(output.c_str(), 2);
		quit = true;
		//exit( 1 );
		break;
	}
	case 2:
	{
		xc = Output("Found BOTCOMMAND id 2", 2);
		break;
	}
	case 3:
	{
		std::string output;
		output.append("Found BOTCOMMAND id 3");
		xc = Output(output.c_str(), 2);

		if (strlen(vec_->at(1).c_str()))
		{
			debug_lvl = atoi(vec_->at(1).c_str());
		}
		break;
	}
	case 4:
	{
		std::string output;
		output.append("Found BOTCOMMAND id 4");
		xc = Output(output.c_str(), 2);
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
				xc = SetClientLoginName(&str);
				xc = GetLogin(vec_->at(2).c_str());
				vec_->at(2) = "";

				if (GetClientLoggedIn())
				{
					ProcClient.loggedin = true;
					ProcClient.lid = GetClientID();
					xc = GetClientName(&ProcClient.name);
					xc = GetClientLoginName(&ProcClient.login_name);
					ProcClient.nameset = true;
					ProcClient.priv = GetClientPriv();
					ProcClient.updatelogin = true;
					xc = GetClientLastLogin(&ProcClient.lastlogin);
					ProcClient.totallogins = GetClientTotalLogins() + 1;
					char dated[128]{ 0 };
					xc = GetDateTime(dated);
					ProcClient.logindate.append(dated);
					xc = UpdateAccount(&ProcClient);
					ProcClient.updatelogin = false;
					xc = PushToVec((void*)&ProcClient, MTX_CV, true, true, false);
				}
				else
				{
					std::string output;
					output.append("incorrect login name and/or password");
					xc = Output(output.c_str(), 2);
					ProcClient.updatelogin = true;
					ProcClient.lid = GetClientID();
					ProcClient.login_name.append(Uppercase(vec_->at(1).c_str()));
					ProcClient.failed_logins = GetClientFailedLogins() + 1;
					char dated[128]{ 0 };
					xc = GetDateTimeMS(dated);
					ProcClient.last_failed_login.append(dated);
					xc = UpdateAccount(&ProcClient);
				}
			}
		}

		break;
	}
	case 6:
	{
		BOTCOMMAND Cmd;
		bool done = false;
		conds.push_back("CMD_ID > 0");
		xc = GetCommand(&Cmd, &cmdvec, &conds);
		xc = 0;

		while (xc < (sint)cmdvec.size())
		{
			if (cmdvec[xc].id < 0)
			{
				done = true;
			}
			else
			{
				if (cmdvec[xc].id > 0)
				{
					std::string output;
					output.append(cmdvec[xc].cmd);
					output.append(" ");
					output.append(ITOA(cmdvec[xc].cmd_id));
					sint rc = Output(output.c_str(), 0);
				}
			}
			xc++;
		}
		break;
	}
	case 7:
	{
		xc = 1;
		BOTCOMMAND Cmd;
		Cmd.cmd.append(vec_->at(1));

		if (vec_->size() > 2)
		{
			xc = GetCommand(&Cmd, &cmdvec, &conds);

			if (cmdvec.empty())
			{
				Cmd.cmd.clear();
				xc = atoi(vec_->at(2).c_str());

				if (xc < INT_MAX && xc > 0)
				{
					Cmd.cmd_id = xc;
					xc = GetCommand(&Cmd, &cmdvec, &conds);
				}
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}

		if (cmdvec.empty())
		{
			BOT_STMT t;
			t.AddDB("litebot");
			t.AddCont("COMMANDS", 1);
			t.it_type = 2;
			AddStrToVec(&t.cols, "COMMAND");
			AddStrToVec(&t.vals, Uppercase(LEncStrI(vec_->at(1).c_str(), -1).c_str()).c_str());
			AddStrToVec(&t.cols, "CMD_ID");
			AddStrToVec(&t.vals, vec_->at(2).c_str());
			t.opts[0].push_back(2);
			std::vector<BOT_STMT> tvec;
			tvec.push_back(t);
			Commit(&tvec);
		}
		else
		{
			return 1;
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

void* machine::LogMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, "LogMaintenance", true, true);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid, "LogMaintenance");

	if (xc < 0)
	{
		sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
		pthread_exit((void *)xc);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}
		return NULL;
	}

	xc = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		xc = LITEBot.Output("::LogMaintenance( void * vp )", 2);
	}

	bool done = false;

	while (!done)
	{
		//sllint lc = LITEBot.TestThreadTRat(&Info);
		for (size_t siz = 0; (sint)siz < LITEBot.VecSize(MTX_LOG); siz++)
		{
			BOT_LOGDET_M logm;
			xc = LITEBot.GetVecEle((void*)&logm, MTX_LOG, siz);

			if (xc > -1)
			{
				if (logm.lsiz)
				{
					sint xh = -1;
					xc = LITEBot.LockElement(&logm, &xh, false, true);

					if (!xc)
					{
						std::vector<std::string> strvec;
						sint hx = LITEBot.GetVecEleMem(&strvec, MTX_LOG, logm.lid, BOT_LOG_Q, true);

						if (hx > -1 && !strvec.empty())
						{
							std::fstream fstrm;
							BOT_FILE nfile(logm.logtitle.c_str(), ".txt", BOT_LOG_PATH);
							//hx = LITEBot.FileOut(&nfile, &fstrm, 3, &strvec);
							hx = LITEBot.ClearVecEleMem(MTX_LOG, logm.lid, BOT_LOG_Q, false);
							hx = LITEBot.ClearVecEleMem(MTX_LOG, logm.lid, BOT_LOG_Q);
						}
						if (!xh)
						{
							xh = LITEBot.UnlockElement(MTX_LOG, logm.lid, false);
						}
					}
				}

			}
		}
		xc = LITEBot.Rest(BOT_LOGREST);
		sint fin = -1;
		xc = LITEBot.GetVecEleMem(&fin, MTX_TTS, LITEBot.lid, BOT_TTS_FIN);

		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			std::string output;
			output.append("finish signal: ");
			output.append(LITEBot.ITOA(fin));
			xc = LITEBot.Output(output.c_str(), 2);
		}

		if (fin == 2)
		{
			done = true;
		}
	}

	xc = 1;
	rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
	pthread_exit((void *)xc);

	if (!tts.opt)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::ThreadMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, "ThreadMaintainence", true, true);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid);
	
	if ( xc < 0)
	{
		sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
		pthread_exit((void *)xc);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}
		return NULL;
	}

	xc = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		xc = LITEBot.Output("::ThreadMaintenance( void * vp )", 2);
	}

	bool done = false;

	while (!done)
	{
		//sllint lc = LITEBot.TestThreadTRat(&Info);
		xc = LITEBot.TM(0);
		xc = LITEBot.Rest(BOT_THRREST);
		sint fin = -1;
		xc = LITEBot.GetVecEleMem(&fin, MTX_TTS, LITEBot.lid, BOT_TTS_FIN);

		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			std::string output;
			output.append("finish signal: ");
			output.append(LITEBot.ITOA(fin));
			xc = LITEBot.Output(output.c_str(), 2);
		}

		if (fin == 2)
		{
			done = true;
		}
	}

	xc = 1;
	rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
	pthread_exit((void *)xc);

	if (!tts.opt)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::TestThread(void * vp_)
{
	sint nlid = (sint)vp_;
	carr_64 ncar;
	sint xc = bot_sprintf(ncar.carr, ncar.siz, "TestThread%i", nlid);
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, ncar.carr, true, true);
	TINFO_M tts;
	xc = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid);

	if (xc < 0)
	{
		sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
		pthread_exit((void *)xc);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}

		return NULL;
	}

	xc = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		xc = LITEBot.Output("::TestThread(void * vp_)", 2, true, false);
	}

	//sllint lc = LITEBot.TestThreadTRat(&Info, 1, true, false);
	xc = 1;
	rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
	pthread_exit((void*)xc);

	if (!tts.opt)
	{
		pthread_detach(pthread_self());
	}

	return NULL;
}

std::string machine::Uppercase(cchar* str_)
{
	if (debug_lvl >= 1 && debug_m)
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
	if (debug_lvl >= 1 && debug_m)
	{
		std::string output;
		output.append("uppercased: ");
		output.append(r_str);
		sint oc = Output(output.c_str(), 2);
	}
	return r_str;
}

std::string machine::CleanPunctuation(cchar* clientinput_)
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

// Database Functions

void* machine::AddThisCode(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, "AddThisCode", true, true);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid);

	if (xc < 0)
	{
		sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
		pthread_exit((void*)xc);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}
		return NULL;
	}

	xc = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);

	if (LITEBot.debug_lvl >= 1 && &LITEBot.debug_m)
	{
		xc = LITEBot.Output("AddThisCode( void * vp ) ", 2);
	}

	//sllint lc = LITEBot.TestThreadTRat(&Info);
	std::vector<MACSYM> codes;
	BOT_DB_M dbs;
	xc = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "code");

	if (xc == -1)
	{
		rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
		pthread_exit((void*)xc);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}
	}

	xc = LITEBot.AddCode(&codes);
	xc = 1;
	rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&xc, false);
	pthread_exit((void*)xc);

	if (!tts.opt)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::DBMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, "DBMaintenance", true, true);
	TINFO_M tts;
	sint x = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid);

	if (x<0)
	{
		sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);
		pthread_exit((void *)x);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}
		return NULL;
	}

	x = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_256 outc;
		x = bot_sprintf(outc.carr, outc.siz, "::DBMaintenance(void *vp(%i))", LITEBot.lid);
		x = LITEBot.Output(outc.carr, 2);
	}

	bool done = false;

	while (!done)
	{
		//sllint lx = LITEBot.TestThreadTRat(&Info);
		BOT_DB_M dbs;
		sint z = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "litebot");

		if (z > -1)
		{
			TINFO ntts(1, "", LITEBot.LITEBotMaintenance);
			ntts.thread_name.append("Maintenance[");
			ntts.thread_name.append(dbs.name.c_str());
			ntts.thread_name.append("]");
			x = LITEBot.InitThread(&ntts);
		}
		else
		{
			if (LITEBot.debug_lvl >= 1 && &LITEBot.debug_m)
			{
				x = LITEBot.Output("could not find db: litebot", 2);
			}
		}
	
		x = LITEBot.Rest(BOT_DBREST);
		z = -1;
		x = LITEBot.GetVecEleMem(&z, MTX_TTS, LITEBot.lid, BOT_TTS_FIN);

		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			std::string output;
			output.append("finish signal: ");
			output.append(LITEBot.ITOA(z).c_str());
			x = LITEBot.Output(output.c_str(), 2);
		}

		if (z == 2)
		{
			done = true;
		}
	}

	x = 1;
	rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);
	pthread_exit((void *)x);

	if (!tts.opt)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::LITEBotMaintenance(void *vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, "LITEBotMaintenance", true, true);
	TINFO_M tts;
	sint rc = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid);

	if (rc<0)
	{
		sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
		pthread_exit((void *)rc);
		return NULL;
	}

	rc = 0;
	sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	BOT_DB dbs;
	xc = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "litebot", false, false);

	if (dbs.type)
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "LITEBotMaintenance attempted on database:%s", dbs.name.c_str());
			op = LITEBot.Output(outp.carr, 2);
		}
	}
	else
	{
		if (LITEBot.debug_lvl >= 5 && LITEBot.debug_m)
		{
			carr_256 outc;
			sint op = bot_sprintf(outc.carr, outc.siz, "::LITEBotMaintenance(void *vp(%i))", LITEBot.lid);
			op = LITEBot.Output(outc.carr, 2);

			if (LITEBot.debug_lvl >= 10 && LITEBot.debug_m)
			{
				carr_256 outp;
				op = bot_sprintf(outp.carr, outp.siz, "for database:%s",dbs.name.c_str());
				op = LITEBot.Output(outp.carr, 2);
			}
		}

		//sllint lc = LITEBot.TestThreadTRat(&Info);
		sint hdb = 0;
		sint odb = LITEBot.OpenDB(dbs.name.c_str(), 2, &hdb);

		if (odb < 0)
		{
			odb = LITEBot.VerifyDatabase(&dbs);
			pthread_exit((void *)odb);
		}
		else
		{
			sint last_modi = 0;
			sint last_maint = 0;
			sint last_modi_ns = 0;
			sint last_maint_ns = 0;
			xc = LITEBot.GetLastAccess(&dbs, &last_modi, &last_modi_ns, &last_maint, &last_maint_ns);
			xc = LITEBot.LastAccessMaintenance(&dbs);

			if ((last_maint == last_modi && last_maint_ns > last_modi_ns) || last_modi > last_maint)
			{
				rc = 0;
			}
			else
			{
				std::vector<std::string> strvec;
				strvec.push_back("(LAST_MODIFIED > LAST_MAINTAINED) OR ");
				strvec.push_back("(LAST_MODIFIED = LAST_MAINTAINED AND LAST_MODIFIED_NS > LAST_MAINTAINED_NS)");

				for (sint i = (sint)dbs.tables.size() - 1; i > 0; i--)
				{
					if (!strcmp("SYMS", dbs.tables[i].c_str()))
					{
						
					}
					else if (!strcmp("LANGUAGES", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("ACCOUNTS", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("COMMANDS", dbs.tables[i].c_str()))
					{

					}
					else{}
				}
			}
			if (!hdb)
			{
				odb = LITEBot.CloseDB(dbs.name.c_str());
			}
		}
	}
	rc = 1;
	xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	pthread_exit((void *)rc);
	return NULL;
}

void* machine::CodeMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid, "CodeMaintenance", true, true);
	TINFO_M tts;
	sint rc = LITEBot.GetVecEle((void*)&tts, MTX_TTS, LITEBot.lid);

	if (rc<0)
	{
		sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
		pthread_exit((void *)rc);
		return NULL;
	}

	rc = 0;
	sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	BOT_DB dbs;
	rc = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "code", false, false);

	if (dbs.type != 2)
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			carr_256 outp;
			sint op = bot_sprintf(outp.carr, outp.siz, "CodeMaintenance attempted on:%s",dbs.name.c_str());
			op = LITEBot.Output(outp.carr, 2);
		}
	}
	else
	{

		if (LITEBot.debug_lvl >= 5 && LITEBot.debug_m)
		{
			sint op = LITEBot.Output("::CodeMaintenance(void * vp)", 2);

			if (LITEBot.debug_lvl >= 10 && LITEBot.debug_m)
			{
				carr_256 outp;
				op = bot_sprintf(outp.carr, outp.siz, "for database:%s", dbs.name.c_str());
				op = LITEBot.Output(outp.carr, 2);
			}
		}

		//sllint lc = LITEBot.TestThreadTRat(&Info);
		sint hdb = 0;
		sint odb = LITEBot.OpenDB(dbs.name.c_str(), 2, &hdb);
		sint last_modi = 0;
		sint last_maint = 0;
		sint last_modi_ns = 0;
		sint last_maint_ns = 0;
		xc = LITEBot.GetLastAccess(&dbs, &last_modi, &last_modi_ns, &last_maint, &last_maint_ns);
		xc = LITEBot.LastAccessMaintenance(&dbs);

		if ((last_maint == last_modi && last_maint_ns > last_modi_ns) || last_modi < last_maint)
		{
			rc = 0;
		}
		else
		{
			sint ct = 0;

			std::vector<MACSYM> rcodes;

			for (sint i = (sint)dbs.tables.size() - 1; i > 0; i--)
			{
				MACSYM nc;
				xc = LITEBot.GetCode(&rcodes, "LAST_MODIFIED > LAST_MAINTAINED OR LAST_MODIFIED = LAST_MAINTAINED AND LAST_MODIFIED_NS > LAST_MAINTAINED_NS", true);

				if (!rcodes.empty())
				{
					if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
					{
						std::string output;
						output.append("Maintenance for table: ");
						output.append(dbs.name);
						output.append(".");
						output.append(dbs.tables[i]);
						xc = LITEBot.Output(output.c_str(), 2);
					}

					if (!strcmp("unclassified", dbs.tables[i].c_str()))
					{
						for (xc = ct; xc < (sint)rcodes.size(); xc++)
						{
							rcodes[xc].ud_last_maintained = true;
							for (sint a = 0; a < (sint)rcodes[xc].usages.size(); a++)
							{
								if (rcodes[xc].usages[a] > -1)
								{
									for (sint b = (sint)rcodes[xc].usages.size() - 1; b > a; b--)
									{
										if (rcodes[xc].usages[a] == rcodes[xc].usages[b])
										{
											rcodes[xc].ud_usages = true;
											rcodes[xc].usages[b] = -1;
										}
									}
								}
							}
							rcodes[xc].used_as = -1;
						}
						ct = xc;
					}
					else if (!strcmp("word", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("punctuation", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("filename", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("filetype", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("command_symbol", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("logical", dbs.tables[i].c_str()))
					{

					}
					else if (!strcmp("LAST_ACCESS", dbs.tables[i].c_str()))
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
		if (!hdb)
		{
			odb = LITEBot.CloseDB(dbs.name.c_str());
		}
	}
	rc = 1;
	xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	pthread_exit((void *)rc);
	return NULL;
}