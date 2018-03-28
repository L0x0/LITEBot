#include "litebot.h"

sint main()
{
	sint xc = 0;
	carr_256 ncar;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, 0, "machine", true, true);
	xc = LITEBot.LITEBot(&ncar, true);
	std::cout << ncar.carr << std::endl;
	exit(xc);
	pthread_exit(NULL);
	return 0;
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

	if (Client.nameset)
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
			char c = ' ';
			sint xc = SeparateStrByChar(input_->substr(2,input_->length()-2).c_str(), c, &vec);
			input_->clear();
			//xc = SeparateSymbolsI( &PInputStruct, 5, 1 );
			//xc = SeparateSymbolsII( &PInputStruct, 0 );
			xc = Command(&vec);

			if (!xc)
			{
				return xc;
			}
		}
	}
	return 0;
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

	str_->append(Client.login_name.c_str());

	return 0;
}

sint machine::SetClientLastLogin(std::string* LastLogin = 0)
{
	if (!LastLogin)
	{
		return -1;
	}

	Client.lastlogin.clear();
	Client.lastlogin.append(LastLogin->c_str());
	return 0;
}

sint machine::GetClientLastLogin(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.lastlogin.c_str());
	return 0;
}

sint machine::SetClientLastFailedLogin(std::string* LastFailedLogin = 0)
{
	if (!LastFailedLogin)
	{
		return -1;
	}

	Client.last_failed_login.clear();
	Client.last_failed_login.append(LastFailedLogin->c_str());
	return 0;
}

sint machine::GetClientLastFailedLogin(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.last_failed_login.c_str());
	return 0;
}

sint machine::SetClientLastExchange(std::string* LastExchange = 0)
{
	if (!LastExchange)
	{
		return -1;
	}
	Client.lastexchange.clear();
	Client.lastexchange.append(LastExchange->c_str());
	return 0;
}

sint machine::GetClientLastExchange(std::string* str_ = 0)
{
	if (!str_)
	{
		return -1;
	}

	str_->clear();
	str_->append(Client.lastexchange.c_str());
	return 0;
}

sint machine::SetClientLoginDate(std::string* LoginDate = 0)
{
	if (!LoginDate)
	{
		return -1;
	}

	Client.logindate.clear();
	Client.logindate.append(LoginDate->c_str());
	return 0;
}

sint machine::GetClientLoginDate(std::string* str_ = 0)
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
	sint xc = GetClientName(&name);

	if (xc)
	{
		return xc;
	}
	else
	{
		xc = GetClientID();
	}

	if (!strcmp(Uppercase(name.c_str()).c_str(), "LOXO") && xc == 2)
	{
		output.append("Hail, ");
		output.append(name);
		xc = Output(output.c_str(), 0);
		output.clear();
		srand((uint)time(0));
		sint questionmk1(rand() % 10);

		if (questionmk1 == 0)
		{
			output.append("Wie gehts?");
		}
		else if (questionmk1 == 1)
		{
			output.append("What's up?");
		}
		else
		{
			output.append("What do you wish of me, oh Great One?");
		}
	}
	else
	{
		output.append("I don't know you ");
		output.append(name);
		output.append(".");
	}

	xc = Output(output.c_str(), 0);
	return 0;
}

void* machine::LogMaintenance(void *vp)
{
	sint xc = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "LogMaintenance", true, true);
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::LogMaintenance(void *vp(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	slint rst_for = (slint)BOT_LOGREST;
	uint done = 2;

	while (done)
	{
		for (sint siz = 0; siz < LITEBot.VecSize(MTX_LOG); siz++)
		{
			BOT_LOGDET_M logm;
			rc = LITEBot.GetVecEle((void*)&logm, MTX_LOG, siz);

			if (rc > -1)
			{
				if (logm.lsiz)
				{
					sint hl = -1;
					rc = LITEBot.LockElement(MTX_LOG, siz, &hl, true, false);

					if (!rc)
					{
						sint h = -1;
						sint p = LITEBot.LockGMutex(MTX_LOG, &h, true);

						if (p > -1)
						{
							BOT_FILE_M xfile(logm.logtitle.c_str(), ".txt", BOT_LOG_PATH, LITEBot.lid, BOT_FILE_APPEND);
							sint ox = -1;
							rc = LITEBot.OpenFile(&xfile, &ox, true);

							if (rc > -1)
							{
								sint op = LITEBot.FileOut(xfile.fcon, 3, &bot_log_vec.d_vec[siz].log_q, 0);

								if (!op)
								{
									bot_log_vec.d_vec[logm.lid].log_q.clear();
								}
								if (!ox)
								{
									ox = LITEBot.CloseFile(&xfile);
								}
							}
							if (!h)
							{
								h = LITEBot.UnlockGMutex(MTX_LOG);
							}
						}
						if (!hl)
						{
							hl = LITEBot.UnlockElement(MTX_LOG, siz, false);
						}
					}
				}
			}
		}

		done--;
		rc = LITEBot.ThreadRest((slint)BOT_LOGREST, 2);
		
		if (rc < 3)
		{
			done++;
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

void* machine::ThreadMaintenance(void *vp)
{
	sint xc = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "ThreadMaintenance", true, true);
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::ThreadMaintenance(void *vp(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	bool done = false;

	while (!done)
	{
		rc = LITEBot.TM(0);
		rc = LITEBot.ThreadRest((slint)BOT_THRREST, 1);

		if (rc == 2)
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

void* machine::TestThread(void *vp_)
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::TestThread(void *vp_(%i))", LITEBot.lid);
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

void* machine::AddThisCode(void *vp_)
{
	sint xc = (sint)vp_;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, xc, "AddThisCode", true, true);
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

	if (LITEBot.debug_lvl >= 1 && &LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::AddThisCode(void *vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);
	}

	std::vector<MACSYM> codes;
	BOT_DB_M dbs("code", 2);
	rc = LITEBot.GetInVec((void*)&dbs, MTX_DBL);

	if (rc == -1)
	{
		sint ret = LITEBot.SetVecEleMem((void*)&rc, MTX_TTS, LITEBot.lid, BOT_TTS_FIN, false);
		ret = LITEBot.ThreadEnd();
		pthread_exit((void*)rc);

		if (!xc)
		{
			pthread_detach(pthread_self());
		}
	}

	sint ret = 1;
	xc = LITEBot.AddCode(&codes);
	rc = LITEBot.ThreadEnd();
	pthread_exit((void*)ret);

	if (!xc)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

void* machine::DBMaintenance(void * vp_)
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_256 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::DBMaintenance(void *vp_(%i))", LITEBot.lid);
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
	
		rc = LITEBot.ThreadRest((slint)BOT_DBREST, 0);

		if (rc == 1)
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

void* machine::LITEBotMaintenance(void *vp_)
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
		if (LITEBot.debug_lvl >= 5 && LITEBot.debug_m)
		{
			carr_64 outc;
			rc = bot_sprintf(outc.carr, outc.siz, "::LITEBotMaintenance(void *vp_(%i))", LITEBot.lid);
			rc = LITEBot.Output(outc.carr, 2);

			if (LITEBot.debug_lvl >= 10 && LITEBot.debug_m)
			{
				carr_256 outp;
				rc = bot_sprintf(outp.carr, outp.siz, "for database:%s", dbs.name.c_str());
				rc = LITEBot.Output(outp.carr, 2);
			}
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

void* machine::CodeMaintenance(void *vp_)
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

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_64 outc;
		rc = bot_sprintf(outc.carr, outc.siz, "::CodeMaintenance(void *vp_(%i))", LITEBot.lid);
		rc = LITEBot.Output(outc.carr, 2);

		if (LITEBot.debug_lvl >= 10 && LITEBot.debug_m)
		{
			carr_256 outp;
			rc = bot_sprintf(outp.carr, outp.siz, "for database:%s", dbs.name.c_str());
			rc = LITEBot.Output(outp.carr, 2);
		}
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
					if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
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