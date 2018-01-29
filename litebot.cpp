#include "litebot.h"

sint main()
{
	sint xc = 0;
	cchar* err_ret = "";
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, 0, "machine");
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
		sint rc = BStrP(outp.carr, outp.siz, "LITEBot(cchar* cret_(\"%s\"), bool do_start_up(%u))", cret_, (uint)do_start_up);
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
	sint xc = PushToVec(&tts, MTX_TTSV, true, true, false);

	if (do_start_up)
	{
		xc = LITEBotStartUp();

		if (!xc)
		{
			while (!xc)
			{
				xc = LITEBotProcess();
			}

			switch (xc)
			{
			case 1:
			{
				sint rc = Output("LITEBotProcess() fault.", 1);
				break;
			}
			case (-1):
			{
				sint rc = Output("LITEBotProcess() quit.", 1);
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
				sint rc = Output("start up broken", 1);
				rc = Output("start up broken", 0);
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
		sint oc = Output("VerifyDatabases fault.", 2);
		oc = Output("VerifyDatabases fault.", 1);
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
		sint op = BStrP(outp.carr, outp.siz, "::InterpretInput(std::string *input_(%i))", (sint)input_);
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

	PINPUT_STRUCT PInputStruct;
	PInputStruct.istr_ = input_;
	std::vector<PARSS> SymVec;
	PInputStruct.SymVec_ = &SymVec;
	std::vector<MICSYM> MSymVec;
	PInputStruct.MSymVec_ = &MSymVec;
	std::vector<SYMBOL_STRUCT> AltSymsVec;
	PInputStruct.AltSymsVec_ = &AltSymsVec;
	std::string ol_str;
	PInputStruct.ol_str_ = &ol_str;
	sint xc = SeparateSymbolsI(&PInputStruct, 0, 1);
	xc = SeparateSymbolsII(&PInputStruct, 0);
	xc = SeparateSymbolsIII(&PInputStruct, 1);
	xc = SeparateSymbolsIV(&PInputStruct, 1);
	//xc = SeparateSymbolsV( &PInputStruct, 1 );
	/* very old code
	database DB;
	std::vector<std::string> word_adds;
	std::vector<CODE_STRUCT > code_adds;
	sint x = 0;
	sint xmax = InputVecs.wordstructs.size();

	while ( x < xmax )
	{
		if ( InputVecs.wordstructs[x].id >= 0 )
		{
			if ( InputVecs.wordstructs[x].id == 0 )
			{
				word_adds.push_back( InputVecs.wordstructs[x].word );
			}

			else
			{
				sint y = x - 1;

				while ( y > -1 )
				{
					if ( InputVecs.wordstructs[y].id == InputVecs.wordstructs[x].id && InputVecs.wordstructs[y].word == InputVecs.wordstructs[x].word )
					{
						InputVecs.wordstructs[x] = InputVecs.wordstructs[y];
						y = -2;
					}

					y--;
				}

				InputVecs.wordstructs[x].used++;
				InputVecs.wordstructs[x].as_code = true;
				InputVecs.wordstructs[x].used_as_code++;

				if ( x > 0 )
				{
					if ( InputVecs.wordstructs[ x - 1 ].id > 0 )
					{
						std::string str;

						if ( !InputVecs.wordstructs[ x ].history_preceeding.empty() )
						{
							str.append( InputVecs.wordstructs[ x ].history_preceeding );
							str.append( " " );
						}

						str.append( Uppercase( InputVecs.wordstructs[ x - 1 ].word ) );
						InputVecs.wordstructs[ x ].history_preceeding = str;
					}
				}

				if ( x + 1 < xmax )
				{
					if ( InputVecs.wordstructs[ x + 1 ].id > 0 )
					{
						std::string str;

						if ( !InputVecs.wordstructs[ x ].history_following.empty() )
						{
							str.append( InputVecs.wordstructs[ x ].history_following );
							str.append( " " );
						}

						str.append( Uppercase( InputVecs.wordstructs[ x + 1 ].word ) );
						InputVecs.wordstructs[ x ].history_following = str;
					}
				}

				DB.UpdateWord( InputVecs.wordstructs[x] );
			}
		}

		if ( InputVecs.codestructs[x].id >= 0 )
		{
			if ( InputVecs.codestructs[x].id == 0 )
			{
				code_adds.push_back( InputVecs.codestructs[x] );
			}

			else
			{
				sint y = x - 1;

				while ( y > -1 )
				{
					if ( InputVecs.codestructs[y].id == InputVecs.codestructs[x].id )
					{
						InputVecs.codestructs[x] = InputVecs.codestructs[y];
						y = -2;
					}

					y--;
				}

				InputVecs.codestructs[x].used++;
					//InputVecs.codestructs[x].used_as.append( InputVecs.inputvecs[3][x] );
					//eventually use an analysis of usage to det language
				DB.UpdateCode( InputVecs.codestructs[ x ] );
			}
		}

		x++;
	}

	if ( !word_adds.empty() )
	{
		DB.AddWords( word_adds );
		word_adds.clear();
	}

	if ( !code_adds.empty() )
	{
		DB.AddCode( code_adds );
		code_adds.clear();
	}

	DB.CommitPendingTransaction();

//	if ( Client.name.empty() )
	{
		ParseForName( InputVecs );
	} //

	if ( quitcond )
	{
		Output( "quitting", 2 );
		return;
	}
//
	if ( !Client.nameset )
	{
		ParseName( clientinput );
	}

	else
	{
	 DetermineInput( clientinput );
	}
	//
	*/
	return xc;
}

sint machine::PISO(PINPUT_STRUCT* InputStruct_, sint opt)
{
	switch ( opt )
	{
		case 0 :
		{
			sint s = Output(InputStruct_->istr_->c_str(), 2);
			std::string output;

			for (s = 0; s < (sint)InputStruct_->SymVec_->size(); s++)
			{
				output.append("\nSymVec[ ");
				output.append(ITOA(s));
				output.append(" ].sym: \"");
				output.append(InputStruct_->SymVec_->at(s).sym);
				output.append("\" loc: ");
				output.append(ITOA(InputStruct_->SymVec_->at(s).loc));

				if (!InputStruct_->SymVec_->at(s).enc.empty())
				{
					output.append(" enc: \"");
					output.append(InputStruct_->SymVec_->at(s).enc);
					output.append("\" enc_loc: ");
					output.append(ITOA(InputStruct_->SymVec_->at(s).enc_loc));
				}

				if (!InputStruct_->SymVec_->at(s).closer.empty())
				{
					output.append(" closer: \"");
					output.append(InputStruct_->SymVec_->at(s).closer);
					output.append("\" closer_loc: ");
					output.append(ITOA(InputStruct_->SymVec_->at(s).closer_loc));
				}

				if (InputStruct_->SymVec_->at(s).encloseris > -1)
				{
					output.append(" encloseris: ");
					output.append(ITOA(InputStruct_->SymVec_->at(s).encloseris));
				}

				output.append(" open: ");
				output.append(ITOA(InputStruct_->SymVec_->at(s).open));
				output.append(" order_open: ");
				output.append(ITOA(InputStruct_->SymVec_->at(s).order_open));

				if (!InputStruct_->SymVec_->at(s).usages.empty())
				{
					output.append("\nusages: ");
					for (size_t o = 0; o < (sint)InputStruct_->SymVec_->at(s).usages.size(); o++)
					{
						output.append(ITOA(InputStruct_->SymVec_->at(s).usages[o]));
						output.append(", ");
					}
					output.erase((sint)output.length() - 2, 2);
				}

				if (!InputStruct_->SymVec_->at(s).constituent_to.empty())
				{
					output.append("\nconstituent_to: ");
					for (size_t o = 0; o < (sint)InputStruct_->SymVec_->at(s).constituent_to.size(); o++)
					{
						output.append(InputStruct_->SymVec_->at(s).constituent_to[o]);
						output.append(", ");
					}
					output.erase((sint)output.length() - 2, 2);
				}

				if (!InputStruct_->SymVec_->at(s).constituent_types.empty())
				{
					output.append("\nconstituent_types: ");
					for (size_t o = 0; o < (sint)InputStruct_->SymVec_->at(s).constituent_types.size(); o++)
					{
						output.append(InputStruct_->SymVec_->at(s).constituent_types[o]);
						output.append(", ");
					}
					output.erase((sint)output.length() - 2, 2);
				}
			}

			if (!InputStruct_->MSymVec_->empty())
			{
				for (s = 0; s < (sint)InputStruct_->MSymVec_->size(); s++)
				{
					output.append("\nMSymVec[ ");
					output.append(ITOA(s));
					output.append(" ].sym: \"");
					output.push_back(InputStruct_->MSymVec_->at(s).sym);
					output.append("\" loc: ");
					output.append(ITOA(InputStruct_->MSymVec_->at(s).loc));

					if (!InputStruct_->MSymVec_->at(s).constituent_to.empty())
					{
						output.append("\nconstituent_to: ");
						for (size_t o = 0; o < (sint)InputStruct_->MSymVec_->at(s).constituent_to.size(); o++)
						{
							const size_t csiz = (sizeof(InputStruct_->MSymVec_->at(s).constituent_to[o]) * 2) + 8;
							char outc[csiz]{ 0 };
							sint xo = BStrP(outc, csiz, "%02X, ", InputStruct_->MSymVec_->at(s).constituent_to[o]);
							output.append(outc);
						}
						output.erase((sint)output.length() - 2, 2);
					}
				}
			}

			if (!InputStruct_->AltSymsVec_->empty())
			{
				for (s = 0; s < (sint)InputStruct_->AltSymsVec_->size(); s++)
				{
					carr_128 op;
					sint xp = BStrP(op.carr, op.siz, "\nAltSymsVec[%i].sym \"%s\" loc:%i \nenc: \"%s\" enc_loc:%i closer: \"%s\" closer_loc:%i encloseris:%i open:%i o-open:%i usage:%i", s, InputStruct_->AltSymsVec_->at(s).sym.c_str(), InputStruct_->AltSymsVec_->at(s).loc, InputStruct_->AltSymsVec_->at(s).enc.c_str(), InputStruct_->AltSymsVec_->at(s).enc_loc, InputStruct_->AltSymsVec_->at(s).closer.c_str(), InputStruct_->AltSymsVec_->at(s).closer_loc, InputStruct_->AltSymsVec_->at(s).encloseris, InputStruct_->AltSymsVec_->at(s).open, InputStruct_->AltSymsVec_->at(s).order_open, InputStruct_->AltSymsVec_->at(s).usage);
					output.append(op.carr);
				}
			}
			s = Output(output.c_str(), 2);
			break;
		}
		default :
		{
			break;
		}
	}
	return 0;
}

sint machine::SeparateSymbolsBySymbols(PINPUT_STRUCT* InputStruct_, std::vector<PARSS> *vec_, sint sort_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "SeparateSymbolsBySymbols(PINPUT_STRUCT* InputStruct_(%i), std::vector<PARSS> *vec_(%i), sint sort_opt(%i))", (sint)InputStruct_, (sint)vec_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 10)
		{
			op = PISO(InputStruct_, 0);
		}
	}

	if (InputStruct_->istr_->length())
	{
		PARSS Sym, ClearSym;
		sint last_was = -1;
		for (size_t sx = 0; sx < (sint)InputStruct_->istr_->length(); sx++)
		{
			sint i = 0;
			for (i = 0; i < GetIdentsSize(); i++)
			{
				sint x = 0;
				for (x = 0; x < GetIdentsSizeV(i); x++)
				{
					PARSS IDSym;
					sint xc = GetIdentsVE(&IDSym, x, i);

					if (sx + (sint)IDSym.sym.length() <= (sint)InputStruct_->istr_->length())
					{
						if (debug_lvl >= 10 && debug_m)
						{
							carr_64 outc;
							xc = BStrP(outc.carr, outc.siz, "comparing \"%s\" vs. \"%s\"", IDSym.sym.c_str(), InputStruct_->istr_->substr(sx, IDSym.sym.length()));
							xc = Output(outc.carr, 2);
						}

						if (!strcmp(IDSym.sym.c_str(), InputStruct_->istr_->substr(sx, IDSym.sym.length()).c_str()))
						{
							if (last_was != i)
							{
								if (!vec_->empty())
								{
									for (xc = 0; xc < (sint)vec_->size(); xc++)
									{
										if (!strcmp(vec_->at(xc).sym.c_str(), Sym.sym.c_str()))
										{
											if (sort_opt == 1 || sort_opt == 3)
											{
												Sym = ClearSym;
											}
											else
											{
												if (!Sym.sym.empty())
												{
													InputStruct_->SymVec_->push_back(Sym);
												}
												Sym = ClearSym;
											}
										}
									}
								}
								else
								{
									if (i == 1 || i == 2)
									{
										if (last_was != 1 && last_was != 2)
										{
											if ((!last_was && sort_opt == 1) || (!last_was && sort_opt == 3))
											{
												Sym = ClearSym;
											}
											else
											{
												if (!Sym.sym.empty())
												{
													InputStruct_->SymVec_->push_back(Sym);
												}
												Sym = ClearSym;
											}
										}
									}
									else
									{
										if ((!last_was && sort_opt == 1) || (!last_was && sort_opt == 3))
										{
											Sym = ClearSym;
										}
										else
										{
											if (!Sym.sym.empty())
											{
												InputStruct_->SymVec_->push_back(Sym);
											}
											Sym = ClearSym;
										}
									}
								}
							}
							else
							{
								if (last_was > 3)
								{
									if (!vec_->empty())
									{
										for (xc = 0; xc < (sint)vec_->size(); xc++)
										{
											if (!strcmp(vec_->at(xc).sym.c_str(), Sym.sym.c_str()))
											{
												if (sort_opt == 1 || sort_opt == 3)
												{
													Sym = ClearSym;
												}
												else
												{
													if (!Sym.sym.empty())
													{
														InputStruct_->SymVec_->push_back(Sym);
													}
													Sym = ClearSym;
												}
											}
										}
									}
									else
									{
										if (!Sym.sym.empty())
										{
											InputStruct_->SymVec_->push_back(Sym);
										}
										Sym = ClearSym;
									}
								}
							}

							Sym.sym.append(InputStruct_->istr_->substr(sx, IDSym.sym.length()));

							if (Sym.loc < 0)
							{
								Sym.loc = sx;
							}

							Sym.encloseris = IDSym.encloseris;

							if (!IDSym.closer.empty())
							{
								if (Sym.closer.empty())
								{
									Sym.closer = IDSym.closer;
								}
							}

							if (!IDSym.enc.empty())
							{
								if (Sym.enc.empty())
								{
									Sym.enc = IDSym.enc;
								}
							}

							if (!IDSym.usages.empty())
							{
								for (size_t u = 0; u < IDSym.usages.size(); u++)
								{
									for (xc = 0; xc < (sint)Sym.usages.size(); xc++)
									{
										if (IDSym.usages[u] == Sym.usages[xc])
										{
											xc = (sint)Sym.usages.size();
										}
									}
									if (xc == (sint)Sym.usages.size())
									{
										Sym.usages.push_back(IDSym.usages[u]);
									}
								}
							}

							if (!IDSym.constituent_to.empty())
							{
								for (size_t u = 0; u < IDSym.constituent_to.size(); u++)
								{
									for (xc = 0; xc < (sint)Sym.constituent_to.size(); xc++)
									{
										if (!strcmp(IDSym.constituent_to[u].c_str(), Sym.constituent_to[xc].c_str()))
										{
											xc = (sint)Sym.constituent_to.size();
										}
									}
									if (xc == (sint)Sym.constituent_to.size())
									{
										Sym.constituent_to.push_back(IDSym.constituent_to[u]);

										if (u < IDSym.constituent_types.size())
										{
											Sym.constituent_types.push_back(IDSym.constituent_types[u]);
										}
									}
								}
							}
							sx += IDSym.sym.length() - 1;
							last_was = i;
							x = GetIdentsSizeV(i);
						}
					}
				}
				if (x == GetIdentsSizeV(i) + 1)
				{
					i = GetIdentsSize();
				}
			}
			if (i == 8)
			{
				if (last_was > -1)
				{
					if (!Sym.sym.empty())
					{
						InputStruct_->SymVec_->push_back(Sym);
					}
					Sym = ClearSym;
				}

				Sym.sym.append(InputStruct_->istr_->substr(sx, 1));

				if (Sym.loc < 0)
				{
					Sym.loc = sx;
				}

				Sym.enc.clear();
				Sym.closer.clear();
				Sym.encloseris = -1;
				Sym.usages.clear();
				Sym.constituent_to.clear();
				Sym.constituent_types.clear();
				last_was = -1;
			}
			sx++;
		}

		if (!Sym.sym.empty())
		{
			InputStruct_->SymVec_->push_back(Sym);
		}
	}

	if (sort_opt == 2 || sort_opt == 3)
	{
		std::vector<PARSS> RevSymVec;
		for (sint r = (sint)InputStruct_->SymVec_->size() - 1; r > -1; r--)
		{
			if (!InputStruct_->SymVec_->at(r).sym.empty())
			{
				RevSymVec.push_back(InputStruct_->SymVec_->at(r));
			}
		}
		*InputStruct_->SymVec_ = RevSymVec;
	}

	if (debug_lvl >= 1 && debug_m)
	{
		sint xc = PISO(InputStruct_, 0);
	}
	return 0;
}

sint machine::SeparateStrBySymbols(std::string *str_, std::vector<std::string> *vec_, std::vector<std::string> *rvec_, sint sort_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "SeparateStrBySymbols(std::string *str_(%i), std::vector<std::string> *vec_(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)vec_, (sint)rvec_, sort_opt);
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
		sint op = BStrP(outp.carr, outp.siz, "SeparateStrByStr(std::string *str_(%i), std::string *sstr_(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)sstr_, (sint)rvec_, sort_opt);
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
		sint op = BStrP(outp.carr, outp.siz, "SeparateStrByCChar(std::string *str_(%i), cchar *sstr_(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)sstr_, (sint)rvec_, sort_opt);
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
		sint op = BStrP(outp.carr, outp.siz, "SeparateStrByChar(std::string *str_(%i), uchar *chr(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)str_, (sint)chr, (sint)rvec_, sort_opt);
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
		sint op = BStrP(outp.carr, outp.siz, "SeparateCByChar(cchar* cstr_(%i), uchar *chr(%i), std::vector<cchar* > *rvec_(%i), sint sort_opt(%i))", (sint)cstr_, (sint)chr, (sint)rvec_, sort_opt);
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
		sint op = BStrP(outp.carr, outp.siz, "SeparateCByChar(cchar* cstr_(%i), uchar *chr(%i), std::vector<std::string> *rvec_(%i), sint sort_opt(%i))", (sint)cstr_, (sint)chr, (sint)rvec_, sort_opt);
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

sint machine::PushToPSymVecAdd(PINPUT_STRUCT* PIS_, PARSS *Sym_, std::vector<CODE_STRUCT > *Codes_ )
{/*
	PIS_->SymVec_->push_back( *Sym_ );
	CODE_STRUCT Code;
	Code.abstraction.append( Sym_->sym );
							
	if ( PIS_->istr_->length() < INT_MAX )
	{
		Code.used_as.push_back( *PIS_->istr_ );
	}
							
	Code.ud_usages = true;
	Code.ud_used_as = true;
	Code.ud_used = true;
	Codes_->push_back( Code );*/
	return 0;
}

sint machine::PushToPSymVec(PINPUT_STRUCT* PIS_, PARSS *Sym_ )
{/*
	PIS_->SymVec_->push_back( *Sym_ );*/
	return 0;
}

sint machine::GetMSSV(PINPUT_STRUCT* PIS_, std::vector<std::vector<MICSYM>> *msvec_)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "GetMSSV(PINPUT_STRUCT* PIS_(%i), std::vector<std::vector<MICSYM>> *msvec_(%i))", (sint)PIS_, (sint)msvec_);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 25 && PIS_)
		{
			op = PISO(PIS_, 0);
		}
	}

	if (!PIS_ || !msvec_)
	{
		return -1;
	}

	bool uni = false;
	sint xc = (sint)PIS_->istr_->length() - 1;

	while (xc > 0)
	{
		if ((sint)((uchar)PIS_->istr_->at(xc)) != (sint)((uchar)PIS_->istr_->at(0)))
		{
			xc = -1;
		}
		xc--;
	}

	if (!xc)
	{
		uni = true;
	}

	xc = 0;

	while (xc < (sint)PIS_->istr_->length())
	{
		sint x = (sint)msvec_->size() - 1;

		while (x > -1)
		{
			if (!msvec_->at(x).empty())
			{
				if ((sint)((uchar)PIS_->istr_->at(xc)) == (sint)((uchar)msvec_->at(x).at(0).sym))
				{
					std::string str;
					sint atloc = 0;
					sint z = (sint)msvec_->at(x).size() - 1;

					while (z > -1)
					{
						sint cx = xc - 1;
						sint yc = msvec_->at(x).at(z).loc - 1;

						if (str.empty())
						{
							sint m = 0;

							while (yc > -1 && cx > -1)
							{
								if ((sint)((uchar)PIS_->istr_->at(cx)) == (sint)((uchar)PIS_->istr_->at(yc)))
								{
									m++;
								}
								else
								{
									yc = -1;
									cx = -1;
								}
								yc--;
								cx--;
							}

							if (m > 0)
							{
								/*if (msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_locs.size() == msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_to.size())
								{
									msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_locs.push_back(xc - m);
								}*/

								while (m)
								{
									str.push_back(PIS_->istr_->at(xc - m));
									m--;
								}
							}
							m = 0;
							atloc = (sint)str.length();
							str.push_back(PIS_->istr_->at(xc));

							/*if (msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_locs.size() == msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_to.size())
							{
								msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_locs.push_back(xc);
							}*/
							cx = xc + 1;
							yc = msvec_->at(x).at(z).loc + 1;

							while (yc < xc && cx < (sint)PIS_->istr_->length())
							{
								if ((sint)((uchar)PIS_->istr_->at(cx)) == (sint)((uchar)PIS_->istr_->at(yc)))
								{
									m++;
								}
								else
								{
									yc = xc;
									cx = (sint)PIS_->istr_->length();
								}
								cx++;
								yc++;
							}

							if (m)
							{
								yc = 1;

								while (m)
								{
									str.push_back(PIS_->istr_->at(xc + yc));
									yc++;
									m--;
								}
							}
						}
						else
						{
							yc = xc;
							cx = atloc;

							while (cx > -1 && yc > -1)
							{
								if ((sint)((uchar)PIS_->istr_->at(yc)) != (sint)((uchar)str[cx]))
								{
									if (yc == xc)
									{

									}
									else
									{
										cx++;
										//msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_locs[msvec_->at(x).at((sint)msvec_->at(x).size() - 1).constituent_locs.size() - 1] = yc + 1;
										std::string stri;

										while (cx < (sint)str.length())
										{
											stri.push_back(str[cx]);
											cx++;
										}
										str.clear();
										str.append(stri);
									}
									cx = -1;
								}
								cx--;

								if (cx > -1)
								{
									yc--;
								}
							}
							cx = atloc;
							yc = xc;

							while (cx < (sint)str.length() && yc < (sint)PIS_->istr_->length())
							{
								if ((sint)((uchar)PIS_->istr_->at(yc)) != (sint)((uchar)str[cx]))
								{
									if (yc == xc)
									{

									}
									else
									{
										std::string stri;
										cx--;

										while (cx > -1)
										{
											stri.push_back(str[cx]);
											cx++;
										}

										str.clear();
										cx = (sint)stri.length() - 1;

										while (cx > -1)
										{
											str.push_back(stri[cx]);
											cx--;
										}
									}

									cx = (sint)str.length();
								}
								cx++;

								if (cx < (sint)str.length())
								{
									yc++;
								}
							}

							yc = (sint)msvec_->at(x).at(z).constituent_to.size() - 1;

							while (yc > -1)
							{
								if (str.length() <= sizeof(msvec_->at(x).at(z).constituent_to[yc]))
								{
									if (!memcmp(&msvec_->at(x).at(z).constituent_to[yc], str.c_str(), strlen(str.c_str())))
									{
										yc = -1;
									}
									else
									{
										if (str.length() > 1)
										{
											//cx = FindInStr(*(const uchar*)str.data(), &msvec_->at(x).at(z).constituent_to[yc], 0, sizeof(msvec_->at(x).at(z).constituent_to[yc]));

											if (cx > -1)
											{
												//msvec_->at(x).at(z).constituent_to[yc] = *(const uchar*)str.data();
												//msvec_->at(x).at(z).constituent_locs[yc] = msvec_->at(x).at(z).constituent_locs[yc] + cx;
												yc = -1;
											}
										}
									}
								}
								yc--;
							}

							if (yc == -1)
							{
								//msvec_->at(x).at(z).constituent_to.push_back(*(const uchar*)str.data());

								/*if (msvec_->at(x).at(z).constituent_locs.size() < msvec_->at(x).at(z).constituent_to.size())
								{
									msvec_->at(x).at(z).constituent_locs.push_back(xc);
								}*/
							}
						}
						z--;
					}
					/*MICSYM Sym((uchar*)&PIS_->istr_->at(xc), 0, (uchar*)str.data());
					Sym.loc = xc;
					msvec_->at(x).push_back(Sym);*/
					x = -1;
				}
			}
			x--;
		}

		if (x == -1)
		{
			std::vector<MICSYM> msvec;
			msvec_->push_back(msvec);
			std::string str;
			str.push_back(PIS_->istr_->at(xc));
			/*MICSYM Sym((uchar*)&PIS_->istr_->at(xc), 0, (uchar*)str.data());
			Sym.loc = xc;
			msvec_->at((sint)msvec_->size() - 1).push_back(Sym);*/
			//msvec_->at((sint)msvec_->size() - 1).at((sint)msvec_->at((sint)msvec_->size() - 1).size() - 1).sym[0] = (uchar)PIS_->istr_->at(xc);
			//msvec_->at((sint)msvec_->size() - 1).at((sint)msvec_->at((sint)msvec_->size() - 1).size() - 1).loc = xc;
			
			//msvec_->at((sint)msvec_->size() - 1).at((sint)msvec_->at((sint)msvec_->size() - 1).size() - 1).constituent_to.push_back(*(const uchar*)str.data());
			//msvec_->at((sint)msvec_->size() - 1).at((sint)msvec_->at((sint)msvec_->size() - 1).size() - 1).constituent_locs.push_back(xc);

			if (uni)
			{
				xc = (sint)PIS_->istr_->length();
			}
		}
		xc++;
	}
	
	xc = GetMSSVUsages(PIS_, msvec_);
	return 0;
}

sint machine::GetMSSVUsages(PINPUT_STRUCT* PIS_, std::vector<std::vector<MICSYM>> *msvec_)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "GetMSSVUsages(PINPUT_STRUCT* PIS_(%i), std::vector<std::vector<MICSYM>> *msvec_(%i))", (sint)PIS_, (sint)msvec_);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 25 && PIS_)
		{
			op = PISO(PIS_, 0);
		}
	}

	if (!PIS_ || !msvec_)
	{
		return -1;
	}
	/*
	for (size_t x = 0; x < msvec_->size(); x++)
	{
		if (!msvec_->at(x).empty())
		{
			std::vector<MACSYM> cvec;
			cchar* str = "";
			MACSYM nc;
			for (size_t nx = 0; x < msvec_->at(x).size(); nx++)
			{
				nc.cons.push_back(msvec_->at(x)[nx]);
			}
			sint y = GetCode(&nc, &cvec, str, 1);
			for (y = 0; y < (sint)msvec_->at(x).size(); y++)
			{
				for (size_t xc = 0; xc < cvec.size(); xc++)
				{
					for ( size_t yc = 0; yc < msvec_->at(x).at(y).constituent_to.size(); yc++)
					{
						sint c = (sint)cvec[xc].constituent_to.size() - 1;

						while (c > -1)
						{
							if (!memcmp(&msvec_->at(x).at(y).constituent_to[yc], &cvec[xc].abstractions[c], sizeof(cvec[xc].abstractions[c])))
							{
								yc = 0;

								while (yc < (sint)cvec[xc].usages.size())
								{
									c = (sint)msvec_->at(x).at(y).usages.size() - 1;

									while (c > -1)
									{
										if (cvec[xc].usages[yc] == msvec_->at(x).at(y).usages[c])
										{
											c = -1;
										}
										c--;
									}

									if (c == -1)
									{
										msvec_->at(x).at(y).usages.push_back(cvec[xc].usages[yc]);
									}
									yc++;
								}
								c = -1;
								yc = -1;
							}
							else
							{
								sint fc = FindInStr(cvec[xc].abstractions[c], &msvec_->at(x).at(y).constituent_to[yc], 0, (sint)sizeof(msvec_->at(x).at(y).constituent_to[yc]) - 1);

								if (fc > -1)
								{
									fc = (sint)sizeof(cvec[xc].abstractions[c]) - 1;

									while (fc > -1)
									{
										if (!memcmp(&msvec_->at(x).at(y).constituent_to[yc], &cvec[xc].abstractions[fc], sizeof(cvec[xc].abstractions[fc])))
										{
											yc = 0;

											while (yc < (sint)cvec[xc].usages.size())
											{
												c = (sint)msvec_->at(x).at(y).usages.size() - 1;

												while (c > -1)
												{
													if (cvec[xc].usages[yc] == msvec_->at(x).at(y).usages[c])
													{
														c = -1;
													}
													c--;
												}

												if (c == -1)
												{
													msvec_->at(x).at(y).usages.push_back(cvec[xc].usages[yc]);
												}
												yc++;
											}
											fc = -1;
										}
										fc--;
									}
									c = -1;
									yc = -1;
								}
								else
								{
									fc = FindInStr(msvec_->at(x).at(y).constituent_to[yc], &cvec[xc].abstractions[c], 0, (sint)sizeof(cvec[xc].abstractions[c]));

									if (fc > -1)
									{
										fc = (sint)sizeof(cvec[xc].abstractions[c]) - 1;

										while (fc > -1)
										{
											if (!memcmp(&msvec_->at(x).at(y).constituent_to[yc], &cvec[xc].abstractions[fc], sizeof(cvec[xc].abstractions[fc])))
											{
												yc = 0;

												while (yc < (sint)cvec[xc].usages.size())
												{
													c = (sint)msvec_->at(x).at(y).usages.size() - 1;

													while (c > -1)
													{
														if (cvec[xc].usages[yc] == msvec_->at(x).at(y).usages[c])
														{
															c = -1;
														}
														c--;
													}

													if (c == -1)
													{
														msvec_->at(x).at(y).usages.push_back(cvec[xc].usages[yc]);
													}
													yc++;
												}
												fc = -1;
											}
											fc--;
										}
										c = -1;
										yc = -1;
									}
								}
							}
							c--;
						}
					}
				}
			}
		}
	}*/
	return 0;
}
/*
sint machine::SSeparators(PINPUT_STRUCT* PIS_, std::vector<std::vector<MICSYM>> *msvec_ )
{
	if (debug_lvl >= 1 && debug_m )
	{
		std::string output;
		output.append( "SSeparators( PIS_, msvec_ " );
		
		if (debug_lvl >= 25 )
		{
			sint xc = PISO(PIS_, 0 );
		}
		
		output.append( ")" );
		sint xc = Output(output.c_str(), 2 );
	}
	
	sint sn = -1;
	
	if ( sn == -1 )
	{
		BOT_DB dbs;
		sn = GetVecEleByName(&dbs, MTX_DBL, "code", false, false);
		bool done = false;
		sn = (sint)dbs.tables.size() - 1;
		
		while ( !done && sn > -1 )
		{
			if ( !strcmp( dbs.tables[ sn ].c_str(), "separators" ) )
			{
				done = true;
			}
			
			else
			{
				sn--;
			}
			
			if ( sn == -1 )
			{
				sn = (sint)dbs.tables.size();
			}
		}
	}
	
	if ( sn == -1 )
	{
		return 1;
	}

	sint x = 0;
	
	while ( x < (sint)msvec_->size() )
	{
		sint y = 0;
		
		while ( y < (sint)msvec_->at( x ).size() )
		{
			sint xc = 0;
			std::vector<sint> lens;
			
			while ( xc < (sint)msvec_->at( x ).at( y ).constituent_to.size() )
			{
				sint yc = (sint)lens.size() - 1;
				
				while ( yc > -1 )
				{
					if ( lens[ yc ] == (sint)sizeof(msvec_->at( x ).at( y ).constituent_to[ xc ]) )
					{
						yc = -1;
					}
					yc--;
				}
				
				if ( yc == -1 )
				{
					lens.push_back((sint)sizeof(msvec_->at( x ).at( y ).constituent_to[ xc ]) );
				}
				xc++;
			}
			
			if ( !lens.empty() )
			{
				if (lens.size() == 1)
				{
					std::vector<std::string> strvec;
					sint yc = SeparateStrByChar(PIS_->istr_, &msvec_->at(x).at(y).constituent_to[0], &strvec, 0);
					sint a = 1;
					sint b = (sint)strvec.size();

					if (!yc)
					{
						while (yc < (sint)strvec.size())
						{
							if (sizeof(strvec[yc].data()) == sizeof(msvec_->at(x).at(y).constituent_to[0]))
							{
								if (!memcmp(strvec[yc].data(), &msvec_->at(x).at(y).constituent_to[0], sizeof(strvec[yc].data())))
								{
									a++;
									b--;
								}
							}
							yc++;
						}

						if (a >= b - 2 && a <= b + 2)
						{
							yc = (sint)msvec_->at(x).size() - 1;

							while (yc > -1)
							{
								sint c = (sint)msvec_->at(x).at(y).usages.size() - 1;

								while (c > -1)
								{
									if (msvec_->at(x).at(y).usages[c] == sn)
									{
										c = -1;
									}
									c--;
								}

								if (c == -1)
								{
									msvec_->at(x).at(y).usages.push_back(sn);
								}
								yc--;
							}
						}
					}
				}
				else
				{
					if ( lens.size() <= msvec_->at( x ).at( y ).constituent_to.size() )
					{
						sint yc = 0;
						
						while ( yc < (sint)msvec_->at( x ).at( y ).constituent_to.size() )
						{
							sint a = (sint)sizeof(msvec_->at( x ).at( y ).constituent_to[ yc ]) - 1;
							
							while ( a > -1 )
							{
								if ( msvec_->at( x ).at( y ).constituent_to[ yc ] != msvec_->at( x ).at( y ).sym[ 0 ] )
								{
									a = -1;
								}
								a--;
							}
							
							if ( a == -1 )
							{
								a = (sint)msvec_->at( x ).at( y ).usages.size() - 1;
								
								while ( a > -1 )
								{
									if ( msvec_->at( x ).at( y ).usages[ a ] == sn )
									{
										a = -1;
									}
									a--;
								}
								
								if ( a == -1 )
								{
									msvec_->at( x ).at( y ).usages.push_back( sn );
								}
							}
							yc++;
						}
					}
				}
			}
			y++;
		}
		x++;
	}
	
	x = (sint)msvec_->size() - 1;
	
	while ( x > -1 )
	{
		sint y = (sint)msvec_->at( x ).size() - 1;
		
		while ( y > -1 )
		{
			sint xc = (sint)msvec_->at( x ).at( y ).usages.size() - 1;
			
			while ( xc > -1 )
			{
				if ( msvec_->at( x ).at( y ).usages[ xc ] == sn )
				{
					xc = -1;
					y = -1;
					x = -1;
				}
				xc--;
			}
			y--;
		}
		x--;
	}
	
	if ( x == -1 )
	{
		return 1;
	}
	return 0;
}

sint machine::SEnclosers(PINPUT_STRUCT* PIS_, std::vector<std::vector<MICSYM>> *msvec_, sint sep)
{
	if (debug_lvl >= 1 && debug_m)
	{
		std::string output;
		output.append("SEnclosers( PIS_, msvec_ ");

		if (debug_lvl >= 25)
		{
			sint xc = PISO(PIS_, 0);
		}

		output.append(")");
		sint xc = Output(output.c_str(), 2);
	}

	sint sn = -1;

	if (sn == -1)
	{
		BOT_DB dbs;
		sn = GetVecEleByName(&dbs, MTX_DBL, "code", false, false);
		bool done = false;
		sn = (sint)dbs.tables.size() - 1;

		while (!done && sn > -1)
		{
			if (!strcmp(dbs.tables[sn].c_str(), "literal_enclosers"))
			{
				done = true;
			}
			else
			{
				sn--;
			}

			if (sn == -1)
			{
				sn = (sint)dbs.tables.size();
			}
		}
	}

	if (sn == -1)
	{
		return 1;
	}

	if (sep > 0)
	{
		sint x = 0;

		while (x < (sint)msvec_->size())
		{
			sint y = 0;

			while (y < (sint)msvec_->at(x).size())
			{
				sint xc = 0;

				while (xc < (sint)msvec_->at(x).at(y).usages.size())
				{
					if (msvec_->at(x).at(y).usages[xc] == sep)
					{
						sint xf = -1;

						if (!msvec_->at(x).at(y).constituent_to.empty())
						{
							xf = FindInStr(msvec_->at(x).at(y).constituent_to[0], &msvec_->at(x).at(y).sym[0], 0, sizeof((msvec_->at(x).at(y).constituent_to[0])));
						}

						if (msvec_->at(x).at(y).loc - xf == msvec_->at(x).at(y).constituent_locs[0] && xf > -1)
						{
							xf = PIS_->istr_->find(msvec_->at(x).at(y).constituent_to[0], msvec_->at(x).at(y).constituent_locs[0]);

							if (xf > -1)
							{
								if (xf)
								{
									sint f = xf - 1;
									char b = PIS_->istr_->at(f);

									while (f > -1)
									{
										if ((sint)((uchar)b) == (sint)((uchar)PIS_->istr_->at(f)))
										{
											if (f - 1 > -1 && y)
											{
												sint yc = y - 1;

												while (yc > -1)
												{
													if (msvec_->at(x).at(yc).constituent_to[0])
													{
														sint fx = 1;

														while ((sint)sizeof(msvec_->at(x).at(yc).constituent_to[0]) - fx > -1 && f - fx > -1)
														{
															if ((PIS_->istr_->at(f - fx)) != (msvec_->at(x).at(yc).constituent_to[0]))
															{
																fx = (sint)sizeof(msvec_->at(x).at(yc).constituent_to[0]) + 1;
															}
															fx++;
														}

														if ((sint)sizeof(msvec_->at(x).at(yc).constituent_to[0]) - fx == -1)
														{
															fx = (sint)msvec_->at(x).at(yc).usages.size() - 1;

															while (fx > -1)
															{
																if (msvec_->at(x).at(yc).usages[fx] == sn)
																{
																	fx = -1;
																}
																fx--;
															}

															if (fx == -1)
															{
																msvec_->at(x).at(yc).usages.push_back(sn);
															}

															fx = (sint)msvec_->at(x).at(y).usages.size() - 1;

															while (fx > -1)
															{
																if (msvec_->at(x).at(y).usages[fx] == sn)
																{
																	fx = -1;
																}
																fx--;
															}

															if (fx == -1)
															{
																msvec_->at(x).at(y).usages.push_back(sn);
															}
														}
													}
													yc--;
												}
											}
										}
										f--;
									}
								}

								sint f = xf + 1;
								char b = PIS_->istr_->at(f);

								while (f < (sint)PIS_->istr_->length())
								{
									if ((sint)((uchar)b) == (sint)((uchar)PIS_->istr_->at(f)))
									{
										if (f + 1 < (sint)PIS_->istr_->length() && y < (sint)msvec_->at(x).size())
										{
											sint yc = y + 1;

											while (yc < (sint)msvec_->at(x).size())
											{
												if (msvec_->at(x).at(yc).constituent_to[0])
												{
													sint fx = 1;

													while ((sint)sizeof(msvec_->at(x).at(yc).constituent_to[0]) - fx > -1 && f - fx > -1)
													{
														if (PIS_->istr_->at(f - fx) != msvec_->at(x).at(yc).constituent_to[0])
														{
															fx = (sint)sizeof(msvec_->at(x).at(yc).constituent_to[0]) + 1;
														}
														fx++;
													}

													if ((sint)sizeof(msvec_->at(x).at(yc).constituent_to[0]) - fx == -1)
													{
														fx = (sint)msvec_->at(x).at(yc).usages.size() - 1;

														while (fx > -1)
														{
															if (msvec_->at(x).at(yc).usages[fx] == sn)
															{
																fx = -1;
															}
															fx--;
														}

														if (fx == -1)
														{
															msvec_->at(x).at(yc).usages.push_back(sn);
														}

														fx = (sint)msvec_->at(x).at(y).usages.size() - 1;

														while (fx > -1)
														{
															if (msvec_->at(x).at(y).usages[fx] == sn)
															{
																fx = -1;
															}
															fx--;
														}

														if (fx == -1)
														{
															msvec_->at(x).at(y).usages.push_back(sn);
														}
													}
												}
												yc++;
											}
										}
									}
									f++;
								}
							}
						}
					}
					xc++;
				}
				y++;
			}
			x++;
		}
	}
	else
	{

	}

	sint x = (sint)msvec_->size() - 1;

	while (x > -1)
	{
		sint y = (sint)msvec_->at(x).size() - 1;

		while (y > -1)
		{
			sint xc = (sint)msvec_->at(x).at(y).usages.size() - 1;

			while (xc > -1)
			{
				if (msvec_->at(x).at(y).usages[xc] == sn)
				{
					xc = -1;
					y = -1;
					x = -1;
				}
				xc--;
			}
			y--;
		}
		x--;
	}

	if (x == -1)
	{
		return 1;
	}
	return 0;
}

sint machine::SWords(PINPUT_STRUCT* PIS_, std::vector<std::vector<MICSYM>> *msvec_, sint sep )
{
	sint sn = -1;
	
	if ( sn == -1 )
	{
		BOT_DB dbs;
		sn = GetVecEleByName(&dbs, MTX_DBL, "code", false, false);
		bool done = false;
		sn = (sint)dbs.tables.size() - 1;
		
		while ( !done && sn > -1 )
		{
			if ( !strcmp( dbs.tables[ sn ].c_str(), "word" ) )
			{
				done = true;
			}
			
			else
			{
				sn--;
			}
			
			if ( sn == -1 )
			{
				sn = (sint)dbs.tables.size();
			}
		}
	}
	
	if ( sn == -1 )
	{
		return 1;
	}
	
	if ( sep > 0 )
	{
		sint x = 0;
		
		while ( x < (sint)msvec_->size() )
		{
			sint y = (sint)msvec_->at( x ).size();
			
			while ( y < (sint)msvec_->at( y ).size() )
			{
				
				
				y++;
			}
			
			x++;
		}
	}
	
	else
	{
		
	}
	
	sint x = (sint)msvec_->size() - 1;
	
	while ( x > -1 )
	{
		sint y = (sint)msvec_->at( x ).size() - 1;
		
		while ( y > -1 )
		{
			sint xc = (sint)msvec_->at( x ).at( y ).usages.size() - 1;
			
			while ( xc > -1 )
			{
				if ( msvec_->at( x ).at( y ).usages[ xc ] == sn )
				{
					xc = -1;
					y = -1;
					x = -1;
				}
				
				xc--;
			}
			
			y--;
		}
		
		x--;
	}
	
	if ( x == -1 )
	{
		return 1;
	}
	
	return 0;
}
*/
sint machine::BuildMSymVec(PINPUT_STRUCT* PIS_, std::vector<std::vector<MICSYM>> *msvec_)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "GetMSSVUsages(PINPUT_STRUCT* PIS_(%i), std::vector<std::vector<MICSYM>> *msvec_(%i))", (sint)PIS_, (sint)msvec_);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 25 && PIS_)
		{
			op = PISO(PIS_, 0);
		}
	}

	if (!PIS_ || !msvec_)
	{
		return -1;
	}

	for (size_t xc = 0; xc < PIS_->istr_->length(); xc++)
	{
		for (sint x = (sint)msvec_->size() - 1; x > -1; x--)
		{
			for (sint y = (sint)msvec_->at( x ).size() - 1; y > -1; y--)
			{
				if ( msvec_->at( x ).at( y ).loc == xc )
				{
					//MICSYM Sym(&msvec_->at(x).at(y).sym, 0, (uchar*)PIS_->istr_->c_str());
					//PIS_->MSymVec_->push_back( Sym );
					//PIS_->MSymVec_->at((sint)PIS_->MSymVec_->size() - 1 ) = msvec_->at( x ).at( y );
					y = -1;
					x = -1;
				}
			}
		}
	}
	return 0;
}

// what we're going to do is build a vector of vectors of std::strings of symbols. then we can assign usages as we build each symbol struct. code/word gets need to wait for re-assembly of some words. instead we just break down all the symbols in the std::string. instead of just separation by spaces lets pull groups of consonants, vowels, spaces/newlines, and formulaic symbols. analyzing usages at this point helps us decide how to reconstruct words and code. our get idents scheme will build vectors of symbol idents in sync with code_types. first we'll break them down by word enders, then those groups by all letters or numbers, break down all letter groups by known consonant groups and vowels, then by symbols, then break down any remaining pure letter groups... no instead of vectors we build every time we use this lets separate by spaces and then look for vowels/consonant groups we store in the heap; then we only have some groups of symbols left to try to get symbols from the db. for each row we get we can add a usage to the symbol struct. this is just possibly one get from the db for each symbol, instead of holding massive vectors of all code idents from all inclusive gets from each code table. this should also leave us with some single symbols and some groups of symbols to sort out.

sint machine::SeparateSymbolsI(PINPUT_STRUCT* InputStruct_, sint sort_opt, sint add_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "::SeparateSymbolsI(PINPUT_STRUCT* InputStruct_(%i), sint sort_opt(%i), sint add_opt(%i))", (sint)InputStruct_, sort_opt, add_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 10 && InputStruct_)
		{
			op = PISO(InputStruct_, 0);
		}
	}

	if (!InputStruct_)
	{
		return -1;
	}

	std::vector<MICSYM> Codes;

	if (!InputStruct_->istr_->empty())
	{
		std::vector<std::vector<MICSYM>> msvec;
		sint sx = GetMSSV(InputStruct_, &msvec);
		sx = BuildMSymVec(InputStruct_, &msvec);
		sx = PISO(InputStruct_, 0);
		//cchar* cvec[ sizeof( *InputStruct_->istr_ ) ] = { InputStruct_->istr_->data() };
		PARSS Sym, ClearSym;
		sint last_was = -1;

		for (sx = 0; sx < (sint)InputStruct_->istr_->length(); sx++)
		{
			sint i = 0;

			while (i < GetIdentsSize())
			{
				sint x = 0;

				while (x < GetIdentsSizeV(i))
				{
					PARSS IDSym;
					sint xc = GetIdentsVE(&IDSym, i, x);

					if (sx + (sint)IDSym.sym.length() <= (sint)InputStruct_->istr_->length())
					{
						if (debug_lvl >= 10 && debug_m)
						{
							std::string output;
							output.append("comparing \"");
							output.append(IDSym.sym);
							output.append("\" vs. \"");
							output.append(InputStruct_->istr_->substr(sx, IDSym.sym.length()));
							output.append("\"");
							sint rc = Output(output.c_str(), 2);
						}

						if (!strcmp(IDSym.sym.c_str(), InputStruct_->istr_->substr(sx, IDSym.sym.length()).c_str()))
						{
							if (last_was != i)
							{
								if (i == 1 || i == 2)
								{
									if (last_was != 1 && last_was != 2)
									{
										if ((!last_was && sort_opt == 1) || (!last_was && sort_opt == 3))
										{
											Sym = ClearSym;
										}
										else
										{
											if (!Sym.sym.empty())
											{
												InputStruct_->SymVec_->push_back(Sym);
											}
											Sym = ClearSym;
										}
									}
								}
								else
								{
									if ((!last_was && sort_opt == 1) || (!last_was && sort_opt == 3))
									{
										Sym = ClearSym;
									}
									else
									{
										if (!Sym.sym.empty())
										{
											InputStruct_->SymVec_->push_back(Sym);
										}
										Sym = ClearSym;
									}
								}
							}
							else
							{
								if (last_was > 3)
								{
									if (!Sym.sym.empty())
									{
										InputStruct_->SymVec_->push_back(Sym);
									}
									Sym = ClearSym;
								}
							}/*

							xc = 0;

							while ( xc < IDSym.sym.length() )
							{
								Sym.sym.push_back( InputStruct_->istr_->at( xc ) );
								xc++;
							}
							*/
							Sym.sym.append(InputStruct_->istr_->substr(sx, IDSym.sym.length()));

							if (Sym.loc < 0)
							{
								Sym.loc = sx;
							}

							Sym.encloseris = IDSym.encloseris;

							if (!IDSym.closer.empty())
							{
								if (Sym.closer.empty())
								{
									Sym.closer.append(IDSym.closer);
								}
							}

							if (!IDSym.enc.empty())
							{
								if (Sym.enc.empty())
								{
									Sym.enc.append(IDSym.enc);
								}
							}

							if (!IDSym.usages.empty())
							{
								for (uint u = 0; u < IDSym.usages.size(); u++)
								{
									xc = 0;

									while (xc < (sint)Sym.usages.size())
									{
										if (IDSym.usages[u] == Sym.usages[xc])
										{
											xc = (sint)Sym.usages.size();
										}
										xc++;
									}

									if (xc == (sint)Sym.usages.size())
									{
										Sym.usages.push_back(IDSym.usages[u]);
									}
								}
							}

							if (!IDSym.constituent_to.empty())
							{
								for (uint u = 0; u < IDSym.constituent_to.size(); u++)
								{
									xc = 0;

									while (xc < (sint)Sym.constituent_to.size())
									{
										if (!strcmp(IDSym.constituent_to[u].c_str(), Sym.constituent_to[xc].c_str()))
										{
											xc = (sint)Sym.constituent_to.size();
										}
										xc++;
									}

									if (xc == (sint)Sym.constituent_to.size())
									{
										Sym.constituent_to.push_back(IDSym.constituent_to[u]);

										if (u < (sint)IDSym.constituent_types.size())
										{
											Sym.constituent_types.push_back(IDSym.constituent_types[u]);
										}
									}
								}
							}
							sx += (sint)IDSym.sym.length() - 1;
							last_was = i;
							x = GetIdentsSizeV(i);
						}
					}
					x++;
				}
				if (x == GetIdentsSizeV(i) + 1)
				{
					i = GetIdentsSize();
				}
				i++;
			}

			if (i == GetIdentsSize())
			{
				if (last_was > -1)
				{
					if (!Sym.sym.empty())
					{
						InputStruct_->SymVec_->push_back(Sym);
						/*
						if ( add_opt )
						{
							CODE_STRUCT Code;
							Code.abstraction.append( Sym.sym );
							Code.ud_usages = true;

							if ( InputStruct_->istr_->length() < INT_MAX )
							{
								Code.used_as.push_back( *InputStruct_->istr_ );
								Code.ud_used_as = true;
							}

							Code.ud_used = true;
							Codes.push_back( Code );
						}
						*/
					}
					Sym = ClearSym;
				}
				/*
				char chrstr[ sizeof( InputStruct_->istr_->at( sx ) )];
				sint s = 0;

				while ( s < ( sint )sizeof( InputStruct_->istr_->at( sx ) ) )
				{
					chrstr[ s ] = InputStruct_->istr_->at( sx );
					s++;
				}


				*/
				Sym.sym.push_back(InputStruct_->istr_->at(sx));

				if (add_opt)
				{
					for (size_t u_siz = 0; u_siz < Sym.usages.size(); u_siz++)
					{
						//MICSYM Code((uchar*)&InputStruct_->istr_->at(sx), 0, (uchar*)InputStruct_->istr_);
						//Codes.push_back(Code);
					}
				}

				if (Sym.loc < 0)
				{
					Sym.loc = sx;
				}

				Sym.enc.clear();
				Sym.closer.clear();
				Sym.encloseris = -1;
				Sym.usages.clear();
				Sym.constituent_to.clear();
				Sym.constituent_types.clear();
				last_was = -1;
			}
		}
		/*
		while ( sx < InputStruct_->istr_->length() )
		{
			sint i = 0;

			while ( i < GetIdentsSize() )
			{
				sint x = 0;

				while ( x < GetIdentsSizeV(i ) )
				{
					PARSS IDSym;
					sint xc = GetIdentsVE(&IDSym, i, x );

					if ( sx + IDSym.sym.length() <= InputStruct_->istr_->length() )
					{

					if ( debug_lvl >= 10 && debug_m )
					{
						std::string output;
						output.append( "comparing \"" );
						output.append( IDSym.sym );
						output.append( "\" vs. \"" );
						output.append( InputStruct_->istr_->substr( sx, IDSym.sym.length() ) );
						output.append( "\"" );
						sint rc = Output(output.c_str(), 2 );
					}

					if ( !strcmp( IDSym.sym.c_str(), InputStruct_->istr_->substr( sx, IDSym.sym.length() ).c_str() ) )
					{
						if ( last_was != i )
						{
								if ( i == 1 || i == 2 )
								{
									if ( last_was != 1 && last_was != 2 )
									{
										if ( ( !last_was && sort_opt == 1 ) || ( !last_was && sort_opt == 3 ) )
										{
											Sym = ClearSym;
										}

										else
										{
											if ( !Sym.sym.empty() )
											{
												InputStruct_->SymVec_->push_back( Sym );
											}

											Sym = ClearSym;
										}
									}
								}

								else
								{
									if ( ( !last_was && sort_opt == 1 ) || ( !last_was && sort_opt == 3 ) )
									{
										Sym = ClearSym;
									}

									else
									{
										if ( !Sym.sym.empty() )
										{
											InputStruct_->SymVec_->push_back( Sym );
										}

										Sym = ClearSym;
									}
								}

						}

						else
						{
							if ( last_was > 3 )
							{
								if ( !Sym.sym.empty() )
								{
									InputStruct_->SymVec_->push_back( Sym );
								}

								Sym = ClearSym;
							}
						}/*

						xc = 0;

						while ( xc < IDSym.sym.length() )
						{
							Sym.sym.push_back( InputStruct_->istr_->at( xc ) );
							xc++;
						}
						* /
						Sym.sym.append( InputStruct_->istr_->substr( sx, IDSym.sym.length() ) );

						if ( Sym.loc < 0 )
						{
							Sym.loc = sx;
						}

						Sym.encloseris = IDSym.encloseris;

						if ( !IDSym.closer.empty() )
						{
							if ( Sym.closer.empty() )
							{
								Sym.closer.append( IDSym.closer );
							}
						}

						if ( !IDSym.enc.empty() )
						{
							if ( Sym.enc.empty() )
							{
								Sym.enc.append( IDSym.enc );
							}
						}

						if ( !IDSym.usages.empty() )
						{
							sint u = 0;

							while ( u < IDSym.usages.size() )
							{
								xc = 0;

								while ( xc < Sym.usages.size() )
								{
									if ( IDSym.usages[ u ] == Sym.usages[ xc ] )
									{
										xc = Sym.usages.size();
									}

									xc++;
								}

								if ( xc == Sym.usages.size() )
								{
									Sym.usages.push_back( IDSym.usages[ u ] );
								}

								u++;
							}
						}

						if ( !IDSym.constituent_to.empty() )
						{
							sint u = 0;

							while ( u < IDSym.constituent_to.size() )
							{
								xc = 0;

								while ( xc < Sym.constituent_to.size() )
								{
									if ( !strcmp( IDSym.constituent_to[ u ].c_str(), Sym.constituent_to[ xc ].c_str() ) )
									{
										xc = Sym.constituent_to.size();
									}

									xc++;
								}

								if ( xc == Sym.constituent_to.size() )
								{
									Sym.constituent_to.push_back( IDSym.constituent_to[ u ] );

									if ( u < IDSym.constituent_types.size() )
									{
										Sym.constituent_types.push_back( IDSym.constituent_types[ u ] );
									}
								}

								u++;
							}
						}

						sx+=IDSym.sym.length() - 1;
						last_was = i;
						x = GetIdentsSizeV(i );
					}
					}

					x++;
				}

				if ( x == GetIdentsSizeV(i ) + 1 )
				{
					i = GetIdentsSize();
				}

				i++;
			}

			if ( i == GetIdentsSize() )
			{
				if ( last_was > -1 )
				{
					if ( !Sym.sym.empty() )
					{
						InputStruct_->SymVec_->push_back( Sym );

						if ( add_opt )
						{
							CODE_STRUCT Code;
							Code.abstraction.append( Sym.sym );
							Code.ud_usages = true;

							if ( InputStruct_->istr_->length() < INT_MAX )
							{
								Code.used_as.push_back( *InputStruct_->istr_ );
								Code.ud_used_as = true;
							}

							Code.ud_used = true;
							Codes.push_back( Code );
						}
					}

					Sym = ClearSym;
				}
				/*
				char chrstr[ sizeof( InputStruct_->istr_->at( sx ) )];
				sint s = 0;

				while ( s < ( sint )sizeof( InputStruct_->istr_->at( sx ) ) )
				{
					chrstr[ s ] = InputStruct_->istr_->at( sx );
					s++;
				}


				* /
				Sym.sym.push_back( InputStruct_->istr_->at( sx ) );
				/*
				if ( add_opt )
				{
				CODE_STRUCT Code;
				Code.abstraction.push_back( InputStruct_->istr_->at( sx ) );
				Code.ud_usages = true;

				if ( InputStruct_->istr_->length() < INT_MAX )
				{
					Code.used_as.push_back( *InputStruct_->istr_ );
					Code.ud_used_as = true;
				}

				Code.ud_used = true;
				Codes.push_back( Code );
				}
				* /
				if ( Sym.loc < 0 )
				{
					Sym.loc = sx;
				}

				Sym.enc.clear();
				Sym.closer.clear();
				Sym.encloseris = -1;
				Sym.usages.clear();
				Sym.constituent_to.clear();
				Sym.constituent_types.clear();
				last_was = -1;
			}

			sx++;
		}
		*/
		if (!Sym.sym.empty())
		{
			InputStruct_->SymVec_->push_back(Sym);
		}

		if ((sint)Codes.size() && add_opt)
		{
			/*uchar ctv = 0;
			memcpy((void*)(&ctv), (void*)(&Codes), sizeof(Codes));
			TINFO tts(0, "AddThisCode", AddThisCode);
			sint xc = InitThread(&tts);*/

			//while (xc < 0)
			//{
			//	nsRest(BOT_NANO_REST);
			//}
			//sint xc = AddCode(&Codes, -1, -1, 2 ); // this will add or update our single char idents candidates in unclassified, code maint can build context vals so we can start determining usages by surrounding chars and pattern recog. new idents aren't going straight to common_syms so we should just create a thread to add these.
		}

		if (sort_opt > 1)
		{
			if (sort_opt == 2 || sort_opt == 3)
			{
				std::vector<PARSS> RevSymVec;
				for (sint r = (sint)InputStruct_->SymVec_->size() - 1; r > -1; r--)
				{
					if (!InputStruct_->SymVec_->at(r).sym.empty())
					{
						RevSymVec.push_back(InputStruct_->SymVec_->at(r));
					}
				}
				*InputStruct_->SymVec_ = RevSymVec;
			}
		}

		if (debug_lvl >= 1 && debug_m)
		{
			sint xc = PISO(InputStruct_, 0);
		}
	}
	return 0;
}

sint machine::SeparateSymbolsII(PINPUT_STRUCT* InputStruct_, sint sort_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "SeparateSymbolsII(PINPUT_STRUCT* InputStruct_(%i), sint sort_opt(%i))", (sint)InputStruct_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 10)
		{
			op = PISO(InputStruct_, 0);
		}
	}

	for (uint s = 0; s < InputStruct_->SymVec_->size(); s++)
	{
		for (sint u = (sint)InputStruct_->SymVec_->at(s).constituent_to.size() - 1; u > -1; u--)
		{
			sint sx = 0;
			sint su = InputStruct_->SymVec_->at(s).sym.find(InputStruct_->SymVec_->at(s).constituent_to[u], 0);

			if (su < 0)
			{
				if (InputStruct_->SymVec_->at(s).loc - (sint)InputStruct_->SymVec_->at(s).constituent_to[u].length() > -1)
				{
					su = InputStruct_->istr_->find(InputStruct_->SymVec_->at(s).constituent_to[u], (InputStruct_->SymVec_->at(s).loc - (sint)InputStruct_->SymVec_->at(s).constituent_to[u].length()));
				}

				if (su < 0)
				{

				}
				else
				{
					if (InputStruct_->SymVec_->at(s).loc > su)
					{
						sx = 0;
					}
					else
					{
						sx = s + 1;
					}

					while (sx < (sint)InputStruct_->SymVec_->size())
					{
						if (InputStruct_->SymVec_->at(s).loc > su)
						{
							if (su >= InputStruct_->SymVec_->at(sx).loc && su < InputStruct_->SymVec_->at(sx).loc + (sint)InputStruct_->SymVec_->at(sx).sym.length())
							{
								for (sint xs = sx; xs < (sint)InputStruct_->SymVec_->size(); xs++)
								{
									if (su + (sint)InputStruct_->SymVec_->at(s).constituent_to[u].length() < InputStruct_->SymVec_->at(xs).loc + (sint)InputStruct_->SymVec_->at(xs).sym.length())
									{
										SYMBOL_STRUCT Sym;
										Sym.sym.append(InputStruct_->SymVec_->at(s).constituent_to[u]);
										//InputStruct_->SymVec[ sx ].sym.erase( su - InputStruct_->SymVec[ sx ].loc, InputStruct_->SymVec[ sx ].sym.length() - ( su - InputStruct_->SymVec[ sx ].loc ) );
										PINPUT_STRUCT IS;
										IS.istr_->append(InputStruct_->SymVec_->at(s).constituent_types[u]);
										std::string ol_str;
										IS.ol_str_ = &ol_str;
										std::vector<PARSS> symv;
										IS.SymVec_ = &symv;
										std::vector<MICSYM> msymv;
										IS.MSymVec_ = &msymv;
										std::vector<SYMBOL_STRUCT> altv;
										IS.AltSymsVec_ = &altv;
										sint xc = SeparateSymbolsI(&IS, 1, 0);

										if (!xc)
										{
											if (u < (sint)IS.SymVec_->size())
											{
												Sym.usage = atoi(IS.SymVec_->at(u).sym.c_str());
											}
										}

										Sym.loc = su;
										InputStruct_->AltSymsVec_->push_back(Sym);
										xs = (sint)InputStruct_->SymVec_->size();
									}
								}
								//u = -1;
							}
						}
						else
						{
							if (InputStruct_->SymVec_->at(s).loc > su && su < (InputStruct_->SymVec_->at(s).loc + (sint)InputStruct_->SymVec_->at(s).sym.length()))
							{
								if ((sint)InputStruct_->SymVec_->at(s).constituent_to[u].length() + su >= InputStruct_->SymVec_->at(sx).loc && (sint)InputStruct_->SymVec_->at(s).constituent_to[u].length() + su < InputStruct_->SymVec_->at(sx).loc + (sint)InputStruct_->SymVec_->at(sx).sym.length())
								{
									SYMBOL_STRUCT Sym;
									Sym.sym.append(InputStruct_->SymVec_->at(s).constituent_to[u]);
									PINPUT_STRUCT IS;
									IS.istr_->append(InputStruct_->SymVec_->at(s).constituent_types[u]);
									std::string ol_str;
									IS.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									IS.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									IS.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									IS.AltSymsVec_ = &altv;
									sint xc = SeparateSymbolsI(&IS, 1, 0);

									if (!xc)
									{
										if (u < (sint)IS.SymVec_->size())
										{
											Sym.usage = atoi(IS.SymVec_->at(u).sym.c_str());
										}
									}
									Sym.loc = su;
									InputStruct_->AltSymsVec_->push_back(Sym);
									sx = (sint)InputStruct_->SymVec_->size();
								}
							}
						}
						sx++;
					}
				}
			}
		}
	}

	if (debug_lvl >= 1 && debug_m)
	{
		sint x = PISO(InputStruct_, 0);
	}
	return 0;
}

sint machine::SeparateSymbolsIII(PINPUT_STRUCT* InputStruct_, sint sort_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "SeparateSymbolsIII(PINPUT_STRUCT* InputStruct_(%i), sint sort_opt(%i))", (sint)InputStruct_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 10 && InputStruct_)
		{
			op = PISO(InputStruct_, 0);
		}
	}

	if (!InputStruct_)
	{
		return -1;
	}

	std::vector<sint> inter_ele;
	sint open = 0;

	for (sint s = 0; s < (sint)InputStruct_->SymVec_->size(); s++)
	{
		if (debug_lvl >= 10 && debug_m)
		{
			std::string output;
			output.append("Checking if InputStruct_->SymVec[");
			output.append(ITOA(s));
			output.append("] is an encloser.");
			sint xc = Output(output.c_str(), 2);
		}

		InputStruct_->SymVec_->at(s).open = open;
		sint u = -1;

		for (u = (sint)InputStruct_->SymVec_->at(s).usages.size() - 1; u > -1; u--)
		{
			if (InputStruct_->SymVec_->at(s).usages[u] == 4 && InputStruct_->SymVec_->at(s).encloseris > -1)
			{
				if (!InputStruct_->SymVec_->at(s).enc.empty())
				{
					u = -1;
				}
				else if (!InputStruct_->SymVec_->at(s).closer.empty())
				{
					u = -2;
				}
				else {}
			}
		}

		if (u == -2)
		{
			if (InputStruct_->SymVec_->at(s).open > 0)
			{
				if (debug_lvl >= 10 && debug_m)
				{
					carr_128 outp;
					sint op = BStrP(outp.carr, outp.siz, "SymVec[%i] was identified as an uncloser and an encloser is open", s);
					op = Output(outp.carr, 2);
				}

				sint xs = -1;

				for (xs = s - 1; xs > -1; xs--)
				{
					if (InputStruct_->SymVec_->at(xs).closer_loc == InputStruct_->SymVec_->at(s).loc)
					{
						xs = -1;
					}
					xs--;
				}

				if (xs == -1)
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("uncloser was not already assigned to another encloser.");
						sint xc = Output(output.c_str(), 2);
					}

					for (xs = s - 1; xs > -1; xs--) // here we just look for the next available closer in the std::string. inter_encs should be dealt with here..
					{
						sint i = -1;

						for (i = (sint)inter_ele.size() - 1; i > -1; i--)
						{
							if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1 && !strcmp(InputStruct_->SymVec_->at(inter_ele[i]).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
							{
								sint n = 0;
								sint ni = -1;

								for (ni = inter_ele[i] - 1; ni > -1; ni--)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										carr_256 outp;
										sint op = BStrP(outp.carr, outp.siz, "SymVec[%i].closer is \"%s\" SymVec[%i].closer_loc:%i", ni, InputStruct_->SymVec_->at(ni).closer.c_str(), ni, InputStruct_->SymVec_->at(ni).closer_loc);
										op = Output(outp.carr, 2);
									}

									if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
									{
										n++;
									}
								}

								if (debug_lvl >= 10 && debug_m)
								{
									carr_64 outp;
									sint op = BStrP(outp.carr, outp.siz, "%i viable enclosers", n);
									op = Output(outp.carr, 2);
								}

								if (!n)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										carr_128 outp;
										sint op = BStrP(outp.carr, outp.siz, "there were no viable enclosers before inter_ele[%i] which is element:%i", i, inter_ele[i]);
										op = Output(outp.carr, 2);
									}

									for (sint ii = i + 1; ii < (sint)inter_ele.size(); ii++)
									{
										if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc < 0 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
											{
												for (sint si = inter_ele[ii] + 1; si < s; si++)
												{
													if (InputStruct_->SymVec_->at(si).open > 0)
													{
														if (open > 0)
														{
															open--;
														}
														InputStruct_->SymVec_->at(si).open--;
													}
												}

												InputStruct_->SymVec_->at(inter_ele[ii]).enc.clear();
												InputStruct_->SymVec_->at(inter_ele[ii]).closer.clear();
												InputStruct_->SymVec_->at(inter_ele[ii]).enc_loc = -2;
												InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc = -2;
												InputStruct_->SymVec_->at(inter_ele[ii]).encloseris = -1;
											}
										}
									}

									if (InputStruct_->SymVec_->at(s).open > 0)
									{
										if (open > 0)
										{
											open--;
										}

										InputStruct_->SymVec_->at(s).open = open;
									}

									InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
									InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;
									i = -1;
									xs = -1;
								}
								else
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("there were ");
										output.append(ITOA(n));
										output.append("viable enclosers before inter_ele[ ");
										output.append(ITOA(i));
										output.append(" ] which is element ");
										output.append(ITOA(inter_ele[i]));
										sint xc = Output(output.c_str(), 2);
									}

									ni = inter_ele[i] + 1;
									sint xn = 0;

									while (ni < s)
									{
										if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
										{
											xn++;
										}
										ni++;
									}

									if (debug_lvl >= 10 && debug_m)
									{
										carr_256 outp;
										sint op = BStrP(outp.carr, outp.siz, "there were %i viable enclosers after inter_ele[%i] which is element:%i", xn, i, inter_ele[i]);
										op = Output(outp.carr, 2);
									}

									for (sint ii = i + 1; ii < (sint)inter_ele.size(); ii++)
									{
										if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
											{
												for (sint si = inter_ele[ii] + 1; si < s; si++)
												{
													if (InputStruct_->SymVec_->at(si).open > 0)
													{
														if (open > 0)
														{
															open--;
														}
														InputStruct_->SymVec_->at(si).open--;
													}
												}
												InputStruct_->SymVec_->at(inter_ele[ii]).enc.clear();
												InputStruct_->SymVec_->at(inter_ele[ii]).closer.clear();
												InputStruct_->SymVec_->at(inter_ele[ii]).enc_loc = -2;
												InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc = -2;
												InputStruct_->SymVec_->at(inter_ele[ii]).encloseris = -1;
											}
										}
									}

									if (InputStruct_->SymVec_->at(s).open > 0)
									{
										if (open > 0)
										{
											open--;
										}
										InputStruct_->SymVec_->at(s).open = open;
									}

									InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
									InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;

									for (xs = inter_ele[i]; xs < s; xs++)
									{
										for (sint us = (sint)InputStruct_->SymVec_->at(xs).usages.size() - 1; us > -1; us--)
										{
											if (InputStruct_->SymVec_->at(xs).usages[us] == 5)
											{
												InputStruct_->SymVec_->at(xs).closer_loc = -2;
												InputStruct_->SymVec_->at(xs).encloseris = -1;
												us = -1;
											}
										}
									}
									i = -1;
									xs = -1;
								}
							}
						}

						if (i == -1)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] is not an uncloser for any interceeding enclosers");
								sint xc = Output(output.c_str(), 2);
							}

							if (!strcmp(InputStruct_->SymVec_->at(xs).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(xs));
									output.append(" ].closer equal to SymVec[ ");
									output.append(ITOA(s));
									output.append(" ].sym");
									sint xc = Output(output.c_str(), 2);
								}

								if (InputStruct_->SymVec_->at(xs).closer_loc == -1)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("encloser at ");
										output.append(ITOA(xs));
										output.append(" has not been deemed as enclosed itself.");
										sint xc = Output(output.c_str(), 2);
									}

									InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(xs).loc;
									InputStruct_->SymVec_->at(xs).closer_loc = InputStruct_->SymVec_->at(s).loc;
									i = 0;

									while (i < (sint)inter_ele.size())
									{
										if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1)
										{
											sint ix = inter_ele[i] + 1;

											while (ix <= s)
											{
												if (InputStruct_->SymVec_->at(ix).open > 0)
												{
													if (open > 0)
													{
														open--;
													}

													InputStruct_->SymVec_->at(ix).open--;
												}
												ix++;
											}
										}
										i++;
									}

									while (xs < s)
									{
										sint us = (sint)InputStruct_->SymVec_->at(xs).usages.size() - 1;

										while (us > -1)
										{
											if (InputStruct_->SymVec_->at(xs).usages[us] == 5)
											{
												InputStruct_->SymVec_->at(xs).closer_loc = -2;
												InputStruct_->SymVec_->at(xs).encloseris = -1;
												us = -1;
											}
											us--;
										}
										xs++;
									}
									xs = -1;

									if (InputStruct_->SymVec_->at(s).open > 0)
									{
										if (open > 0)
										{
											open--;
										}

										InputStruct_->SymVec_->at(s).open = open;
									}
								}
							}
						}
						xs--;
					}

					if (xs == -1)
					{
						if (debug_lvl >= 10 && debug_m)
						{
							std::string output;
							output.append("SymVec[ ");
							output.append(ITOA(s));
							output.append(" ] did not match as closer for any prior symbol in the std::string. ");
							sint xc = Output(output.c_str(), 2);
						}

						// it was an encloser with an identical uncloser, a non relevant uncloser, or the remainder of a prior incomplete statement with unresolved enclosers.
						if (InputStruct_->SymVec_->at(s).closer_loc > -2 && InputStruct_->SymVec_->at(s).enc_loc > -2)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] has not been deemed as enclosed. ");
								sint xc = Output(output.c_str(), 2);
							}

							if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).closer.c_str()))
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] is an uncloser with an identical encloser. ");
									sint xc = Output(output.c_str(), 2);
								}

								inter_ele.push_back(s);
								open++;
							}
						}
						else
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] has already been deemed as enclosed. ");
								sint xc = Output(output.c_str(), 2);
							}
						}
					}
				}
			}
			else
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an uncloser and no enclosers are open");
					sint xc = Output(output.c_str(), 2);
				}

				if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).enc.c_str()) || !strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).closer.c_str()))
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("SymVec[ ");
						output.append(ITOA(s));
						output.append(" ] matches encloser \" ");
						output.append(InputStruct_->SymVec_->at(s).enc);
						output.append(" \" and no enclosers are open");
						sint xc = Output(output.c_str(), 2);
					}

					InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
					InputStruct_->SymVec_->at(s).closer.clear();
					inter_ele.push_back(s);
					open++;
				}
			}
		}
		else if (u == -3)
		{
			if (InputStruct_->SymVec_->at(s).open > 0)
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an encloser and an encloser is open");
					sint xc = Output(output.c_str(), 2);
				}

				if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).closer.c_str()))
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("SymVec[ ");
						output.append(ITOA(s));
						output.append(" ] matches identical uncloser \" ");
						output.append(InputStruct_->SymVec_->at(s).closer);
						output.append(" \" and enclosers are open");
						sint xc = Output(output.c_str(), 2);
					}

					sint xs = s - 1;

					while (xs > -1)
					{
						if (InputStruct_->SymVec_->at(xs).closer_loc == InputStruct_->SymVec_->at(s).loc || InputStruct_->SymVec_->at(xs).enc_loc == InputStruct_->SymVec_->at(s).loc)
						{
							xs = -1;
						}

						xs--;
					}

					if (xs == -1)
					{
						if (debug_lvl >= 10 && debug_m)
						{
							std::string output;
							output.append("encloser was not already assigned to another uncloser or encloser.");
							sint xc = Output(output.c_str(), 2);
						}

						xs = s - 1;

						while (xs > -1) // here we just look for the next available closer in the std::string. inter_encs should be dealt with here..
						{
							sint i = (sint)inter_ele.size() - 1;

							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("there are ");
								output.append(ITOA(i + 1));
								output.append(" interceeding enclosers. checking those first.");
								sint xc = Output(output.c_str(), 2);
							}

							while (i > -1)
							{
								if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1 && !strcmp(InputStruct_->SymVec_->at(inter_ele[i]).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
								{
									sint n = 0;
									sint ni = inter_ele[i] - 1;

									while (ni > -1)
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("SymVec[ ");
											output.append(ITOA(ni));
											output.append(" ].closer is \" ");
											output.append(InputStruct_->SymVec_->at(ni).closer);
											output.append(" \" SymVec[ ");
											output.append(ITOA(ni));
											output.append(" ].closer_loc == ");
											output.append(ITOA(InputStruct_->SymVec_->at(ni).closer_loc));
											sint xc = Output(output.c_str(), 2);
										}

										if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
										{
											n++;
										}

										ni--;
									}

									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append(ITOA(n));
										output.append(" viable enclosers");
										sint xc = Output(output.c_str(), 2);
									}

									if (!n)
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("there were no viable enclosers before inter_ele[ ");
											output.append(ITOA(i));
											output.append(" ] which is element ");
											output.append(ITOA(inter_ele[i]));
											sint xc = Output(output.c_str(), 2);
										}

										sint ii = i + 1;

										while (ii < (sint)inter_ele.size())
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
											{
												if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
												{
													sint si = inter_ele[ii] + 1;

													//if ( InputStruct_->SymVec[ inter_ele[ si ] ].open > InputStruct_->SymVec[ inter_ele[ ii ] ].open )
												//	{
													while (si < s)
													{
														if (InputStruct_->SymVec_->at(si).open > 0)
														{
															if (open > 0)
															{
																open--;
															}

															InputStruct_->SymVec_->at(si).open--;
														}

														si++;
													}

													InputStruct_->SymVec_->at(inter_ele[ii]).enc.clear();
													InputStruct_->SymVec_->at(inter_ele[ii]).closer.clear();
													InputStruct_->SymVec_->at(inter_ele[ii]).enc_loc = -2;
													InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc = -2;
													InputStruct_->SymVec_->at(inter_ele[ii]).encloseris = -1;
													//}
												}
											}

											ii++;
										}

										if (InputStruct_->SymVec_->at(s).open > 0)
										{
											if (open > 0)
											{
												open--;
											}

											InputStruct_->SymVec_->at(s).open = open;
										}

										InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
										InputStruct_->SymVec_->at(s).closer.clear();
										InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
										InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;

										i = -1;
										xs = -1;
									}
									else
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("there were ");
											output.append(ITOA(n));
											output.append("viable enclosers before inter_ele[ ");
											output.append(ITOA(i));
											output.append(" ] which is element ");
											output.append(ITOA(inter_ele[i]));
											sint xc = Output(output.c_str(), 2);
										}

										ni = inter_ele[i] + 1;
										sint xn = 0;

										while (ni < s)
										{
											if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
											{
												xn++;
											}

											ni++;
										}

										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("there were ");
											output.append(ITOA(xn));
											output.append("viable enclosers after inter_ele[ ");
											output.append(ITOA(i));
											output.append(" ] which is element ");
											output.append(ITOA(inter_ele[i]));
											sint xc = Output(output.c_str(), 2);
										}

										sint ii = i + 1;

										while (ii < (sint)inter_ele.size())
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
											{
												if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
												{
													sint si = inter_ele[ii] + 1;

													//	if ( InputStruct_->SymVec[ inter_ele[ si ] ].open > InputStruct_->SymVec[ inter_ele[ ii ] ].open )
													//	{
													while (si < s)
													{
														if (InputStruct_->SymVec_->at(si).open > 0)
														{
															if (open > 0)
															{
																open--;
															}

															InputStruct_->SymVec_->at(si).open--;
														}

														si++;
													}

													InputStruct_->SymVec_->at(inter_ele[ii]).enc.clear();
													InputStruct_->SymVec_->at(inter_ele[ii]).closer.clear();
													InputStruct_->SymVec_->at(inter_ele[ii]).enc_loc = -2;
													InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc = -2;
													InputStruct_->SymVec_->at(inter_ele[ii]).encloseris;
													//	}
												}
											}

											ii++;
										}

										if (InputStruct_->SymVec_->at(s).open > 0)
										{
											if (open > 0)
											{
												open--;
											}

											InputStruct_->SymVec_->at(s).open = open;
										}

										InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
										InputStruct_->SymVec_->at(s).closer.clear();
										InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
										InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;

										xs = inter_ele[i];

										while (xs < s)
										{
											sint us = (sint)InputStruct_->SymVec_->at(xs).usages.size() - 1;

											while (us > -1)
											{
												if (InputStruct_->SymVec_->at(xs).usages[us] == 5)
												{
													InputStruct_->SymVec_->at(xs).closer_loc = -2;
													InputStruct_->SymVec_->at(xs).encloseris = -1;
													us = -1;
												}
												else
												{

												}

												us--;
											}

											xs++;
										}

										i = -1;
										xs = -1;
									}
								}

								i--;
							}

							if (i == -1)
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] is not an uncloser for any interceeding enclosers");
									sint xc = Output(output.c_str(), 2);
								}

								if (!strcmp(InputStruct_->SymVec_->at(xs).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("SymVec[ ");
										output.append(ITOA(xs));
										output.append(" ].closer equal to SymVec[ ");
										output.append(ITOA(s));
										output.append(" ].sym");
										sint xc = Output(output.c_str(), 2);
									}

									if (InputStruct_->SymVec_->at(xs).closer_loc == -1)
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("encloser at ");
											output.append(ITOA(xs));
											output.append(" has not been deemed as enclosed itself.");
											sint xc = Output(output.c_str(), 2);
										}

										InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
										InputStruct_->SymVec_->at(s).closer.clear();
										InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(xs).loc;
										InputStruct_->SymVec_->at(xs).closer_loc = InputStruct_->SymVec_->at(s).loc;

										i = 0;

										while (i < (sint)inter_ele.size())
										{
											if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[i]).closer_loc > InputStruct_->SymVec_->at(s).loc)
											{
												sint ix = inter_ele[i] + 1;

												while (ix <= s)
												{
													if (InputStruct_->SymVec_->at(ix).open > 0)
													{
														if (open > 0)
														{
															open--;
														}

														InputStruct_->SymVec_->at(ix).open--;
													}

													ix++;
												}
											}

											i++;
										}

										while (xs < s)
										{
											sint us = (sint)InputStruct_->SymVec_->at(xs).usages.size() - 1;

											while (us > -1)
											{
												if (InputStruct_->SymVec_->at(xs).usages[us] == 5)
												{
													InputStruct_->SymVec_->at(xs).closer_loc = -2;
													InputStruct_->SymVec_->at(xs).encloseris = -1;
													us = -1;
												}
												else
												{

												}

												us--;
											}

											xs++;
										}

										xs = -1;

										if (InputStruct_->SymVec_->at(s).open > 0)
										{
											if (open > 0)
											{
												open--;
											}

											InputStruct_->SymVec_->at(s).open = open;
										}
									}
								}
							}

							xs--;
						}

						if (xs == -1)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] did not match as closer for any prior symbol in the std::string. ");
								sint xc = Output(output.c_str(), 2);
							}

							// it was an encloser with an identical uncloser, a non relevant uncloser, or the remainder of a prior incomplete statement with unresolved enclosers.
							if (InputStruct_->SymVec_->at(s).closer_loc >= -1)
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] has not been deemed as enclosed. ");
									sint xc = Output(output.c_str(), 2);
								}

								if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).closer.c_str()))
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("SymVec[ ");
										output.append(ITOA(s));
										output.append(" ] is an encloser with an identical uncloser. ");
										sint xc = Output(output.c_str(), 2);
									}

									inter_ele.push_back(s);
									open++;
								}
							}
							else // non-relevant or incomplete.
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] has already been deemed as enclosed. ");
									sint xc = Output(output.c_str(), 2);
								}
							}
						}
					}
				}
				else
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("SymVec[ ");
						output.append(ITOA(s));
						output.append(" ] was identified as an encloser and enclosers are open");
						sint xc = Output(output.c_str(), 2);
					}

					inter_ele.push_back(s);
					open++;
				}
			}
			else
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an encloser and no enclosers are open");
					sint xc = Output(output.c_str(), 2);
				}

				inter_ele.push_back(s);
				open++;
			}
		}
		else
		{

		}

		if (!inter_ele.empty())
		{
			std::vector<sint> alt_eles;
			sint x = 0;

			while (x < (sint)inter_ele.size())
			{
				if (InputStruct_->SymVec_->at(inter_ele[x]).closer_loc == -1)
				{
					alt_eles.push_back(inter_ele[x]);
				}
				else
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("removing resolved interceeding encloser, inter_ele[");
						output.append(ITOA(x));
						output.append("]");
						sint xc = Output(output.c_str(), 2);
					}
				}

				x++;
			}

			inter_ele = alt_eles;

			if (debug_lvl >= 10 && debug_m)
			{
				std::string output;
				output.append("inter_ele.size(): ");
				output.append(ITOA((sint)inter_ele.size()));
				sint xc = Output(output.c_str(), 2);
				output.clear();

				sint o = 0;

				while (o < (sint)inter_ele.size())
				{
					output.append("SymVec[ ");
					output.append(ITOA(inter_ele[o]));
					output.append(" ] ");
					output.append("sym: \"");
					output.append(InputStruct_->SymVec_->at(inter_ele[o]).sym);
					output.append("\" loc: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).loc));
					output.append("enc: \"");
					output.append(InputStruct_->SymVec_->at(inter_ele[o]).enc);
					output.append("\" closer: \"");
					output.append(InputStruct_->SymVec_->at(inter_ele[o]).closer);
					output.append("\" closer_loc: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).closer_loc));
					output.append(" open: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).open));
					output.append(" order_open: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).order_open));
					sint xc = Output(output.c_str(), 2);
					output.clear();
					o++;
				}
			}
		}
	}
	
	if (!InputStruct_->SymVec_->empty())
	{
		std::vector<PARSS> RevSymVec;
		for (sint s = 0; s < (sint)InputStruct_->SymVec_->size(); s++)
		{
			if (InputStruct_->SymVec_->at(s).closer_loc > 0)
			{
				RevSymVec.push_back(InputStruct_->SymVec_->at(s));
				sint xs = s + 1;
				PARSS Sym;
				Sym.sym.append(InputStruct_->istr_->substr(InputStruct_->SymVec_->at(xs).loc, InputStruct_->SymVec_->at(s).closer_loc - InputStruct_->SymVec_->at(xs).loc));
				Sym.loc = InputStruct_->SymVec_->at(xs).loc;
				Sym.closer_loc = -2;
				Sym.enc_loc = -2;
				Sym.open = InputStruct_->SymVec_->at(xs).open;
				Sym.encloseris = -1;

				while (InputStruct_->SymVec_->at(xs).loc < InputStruct_->SymVec_->at(s).closer_loc)
				{
					for (sint u = 0; u < (sint)InputStruct_->SymVec_->at(xs).usages.size(); u++)
					{
						sint xu = (sint)Sym.usages.size() - 1;

						while (xu > -1)
						{
							if (InputStruct_->SymVec_->at(xs).usages[u] == Sym.usages[xu])
							{
								xu = -1;
							}
							xu--;
						}
						if (xu == -1)
						{
							Sym.usages.push_back(InputStruct_->SymVec_->at(xs).usages[u]);
						}
					}
					xs++;
				}
				RevSymVec.push_back(Sym);
				RevSymVec.push_back(InputStruct_->SymVec_->at(xs));
				s = xs;
			}
			else
			{
				RevSymVec.push_back(InputStruct_->SymVec_->at(s));
			}
		}
		*InputStruct_->SymVec_ = RevSymVec;
	}
	
	if (debug_lvl >= 1 && debug_m )
	{
		sint xc = PISO(InputStruct_, 0);
	}
	
	return 0;
}

sint machine::SeparateSymbolsIV(PINPUT_STRUCT* InputStruct_, sint sort_opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "SeparateSymbolsIV(PINPUT_STRUCT* InputStruct_(%i), sint sort_opt(%i))", (sint)InputStruct_, sort_opt);
		op = Output(outp.carr, 2);

		if (debug_lvl >= 10)
		{
			op = PISO(InputStruct_, 0);
		}
	}
	
	std::vector<sint> inter_ele;
	sint open = 0;
	sint s = 0;
	
	while (s < (sint)InputStruct_->SymVec_->size())
	{
		if (debug_lvl >= 10 && debug_m)
		{
			std::string output;
			output.append("Checking if InputStruct_->SymVec[");
			output.append(ITOA(s));
			output.append("] is an encloser.");
			sint xc = Output(output.c_str(), 2);
		}

		InputStruct_->SymVec_->at(s).order_open = open;
		sint u = (sint)InputStruct_->SymVec_->at(s).usages.size() - 1;

		while (u > -1)
		{
			if (InputStruct_->SymVec_->at(s).usages[u] == 5 && InputStruct_->SymVec_->at(s).encloseris > -1)
			{
				if (!InputStruct_->SymVec_->at(s).enc.empty())
				{
					u = -1;
				}
				else if (!InputStruct_->SymVec_->at(s).closer.empty())
				{
					u = -2;
				}
				else
				{

				}
			}

			u--;
		}

		if (u == -2)
		{
			if (InputStruct_->SymVec_->at(s).order_open > 0)
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an uncloser and an encloser is open");
					sint xc = Output(output.c_str(), 2);
				}

				sint xs = s - 1;

				while (xs > -1)
				{
					if (InputStruct_->SymVec_->at(xs).closer_loc == InputStruct_->SymVec_->at(s).loc)
					{
						xs = -1;
					}

					xs--;
				}

				if (xs == -1)
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("uncloser was not already assigned to another encloser.");
						sint xc = Output(output.c_str(), 2);
					}

					xs = s - 1;

					while (xs > -1) // here we just look for the next available closer in the std::string. inter_encs should be dealt with here..
					{
						sint i = (sint)inter_ele.size() - 1;

						if (debug_lvl >= 10 && debug_m)
						{
							std::string output;
							output.append("there are ");
							output.append(ITOA(i + 1));
							output.append(" interceeding enclosers. checking those first.");
							sint xc = Output(output.c_str(), 2);
						}

						while (i > -1)
						{
							if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1 && !strcmp(InputStruct_->SymVec_->at(inter_ele[i]).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
							{
								sint n = 0;
								sint ni = inter_ele[i] - 1;

								while (ni > -1)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("SymVec[ ");
										output.append(ITOA(ni));
										output.append(" ].closer is \" ");
										output.append(InputStruct_->SymVec_->at(ni).closer);
										output.append(" \" SymVec[ ");
										output.append(ITOA(ni));
										output.append(" ].closer_loc == ");
										output.append(ITOA(InputStruct_->SymVec_->at(ni).closer_loc));
										sint xc = Output(output.c_str(), 2);
									}

									if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
									{
										n++;
									}

									ni--;
								}

								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append(ITOA(n));
									output.append(" viable enclosers");
									sint xc = Output(output.c_str(), 2);
								}

								if (!n)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("there were no viable enclosers before inter_ele[ ");
										output.append(ITOA(i));
										output.append(" ] which is element ");
										output.append(ITOA(inter_ele[i]));
										sint xc = Output(output.c_str(), 2);
									}

									sint ii = i + 1;

									while (ii < (sint)inter_ele.size())
									{
										if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc < 0 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
											{
												sint si = inter_ele[ii] + 1;

												//	if ( InputStruct_->SymVec[ inter_ele[ si ] ].open > InputStruct_->SymVec[ inter_ele[ ii ] ].open )
												//	{
												while (si < s)
												{
													if (InputStruct_->SymVec_->at(si).order_open > 0)
													{
														if (open > 0)
														{
															open--;
														}

														InputStruct_->SymVec_->at(si).order_open--;
													}

													si++;
												}
												//	}
											}
										}

										ii++;
									}

									if (InputStruct_->SymVec_->at(s).order_open > 0)
									{
										if (open > 0)
										{
											open--;
										}

										InputStruct_->SymVec_->at(s).order_open = open;
									}

									InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
									InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;
									i = -1;
									xs = -1;
								}
								else
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("there were ");
										output.append(ITOA(n));
										output.append("viable enclosers before inter_ele[ ");
										output.append(ITOA(i));
										output.append(" ] which is element ");
										output.append(ITOA(inter_ele[i]));
										sint xc = Output(output.c_str(), 2);
									}

									ni = inter_ele[i] + 1;
									sint xn = 0;

									while (ni < s)
									{
										if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
										{
											xn++;
										}

										ni++;
									}

									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("there were ");
										output.append(ITOA(xn));
										output.append("viable enclosers after inter_ele[ ");
										output.append(ITOA(i));
										output.append(" ] which is element ");
										output.append(ITOA(inter_ele[i]));
										sint xc = Output(output.c_str(), 2);
									}

									sint ii = i + 1;

									while (ii < (sint)inter_ele.size())
									{
										if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
											{
												sint si = inter_ele[ii] + 1;

												//	if ( InputStruct_->SymVec[ inter_ele[ si ] ].open > InputStruct_->SymVec[ inter_ele[ ii ] ].open )
												//	{
												while (si < s)
												{
													if (InputStruct_->SymVec_->at(si).order_open > 0)
													{
														if (open > 0)
														{
															open--;
														}

														InputStruct_->SymVec_->at(si).order_open--;
													}

													si++;
												}
												//}
											}
										}

										ii++;
									}

									if (InputStruct_->SymVec_->at(s).order_open > 0)
									{
										if (open > 0)
										{
											open--;
										}

										InputStruct_->SymVec_->at(s).order_open = open;
									}

									InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
									InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;
									i = -1;
									xs = -1;
								}
							}

							i--;
						}

						if (i == -1)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] is not an uncloser for any interceeding enclosers");
								sint xc = Output(output.c_str(), 2);
							}

							if (!strcmp(InputStruct_->SymVec_->at(xs).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(xs));
									output.append(" ].closer equal to SymVec[ ");
									output.append(ITOA(s));
									output.append(" ].sym");
									sint xc = Output(output.c_str(), 2);
								}

								if (InputStruct_->SymVec_->at(xs).closer_loc == -1)
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("encloser at ");
										output.append(ITOA(xs));
										output.append(" has not been deemed as enclosed itself.");
										sint xc = Output(output.c_str(), 2);
									}

									InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(xs).loc;
									InputStruct_->SymVec_->at(xs).closer_loc = InputStruct_->SymVec_->at(s).loc;
									i = 0;

									while (i < (sint)inter_ele.size())
									{
										if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1)
										{
											sint ix = inter_ele[i] + 1;

											while (ix <= s)
											{
												if (InputStruct_->SymVec_->at(ix).order_open > 0)
												{
													if (open > 0)
													{
														open--;
													}

													InputStruct_->SymVec_->at(ix).order_open--;
												}

												ix++;
											}
										}

										i++;
									}

									xs = -1;

									if (InputStruct_->SymVec_->at(s).order_open > 0)
									{
										if (open > 0)
										{
											open--;
										}

										InputStruct_->SymVec_->at(s).order_open = open;
									}
								}
							}
						}

						xs--;
					}

					if (xs == -1)
					{
						if (debug_lvl >= 10 && debug_m)
						{
							std::string output;
							output.append("SymVec[ ");
							output.append(ITOA(s));
							output.append(" ] did not match as closer for any prior symbol in the std::string. ");
							sint xc = Output(output.c_str(), 2);
						}

						// it was an encloser with an identical uncloser, a non relevant uncloser, or the remainder of a prior incomplete statement with unresolved enclosers.
						if (InputStruct_->SymVec_->at(s).closer_loc > -2 && InputStruct_->SymVec_->at(s).enc_loc > -2)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] has not been deemed as enclosed. ");
								sint xc = Output(output.c_str(), 2);
							}

							if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).enc.c_str()))
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] is an uncloser with an identical encloser. ");
									sint xc = Output(output.c_str(), 2);
								}

								InputStruct_->SymVec_->at(s).closer.append(InputStruct_->SymVec_->at(s).enc);
								InputStruct_->SymVec_->at(s).enc.clear();

								inter_ele.push_back(s);
								open++;
							}
						}
						else
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] has already been deemed as enclosed. ");
								sint xc = Output(output.c_str(), 2);
							}
						}
					}
				}
			}
			else
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an uncloser and no enclosers are open");
					sint xc = Output(output.c_str(), 2);
				}

				if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).enc.c_str()))
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("SymVec[ ");
						output.append(ITOA(s));
						output.append(" ] matches encloser \" ");
						output.append(InputStruct_->SymVec_->at(s).enc);
						output.append(" \" and no enclosers are open");
						sint xc = Output(output.c_str(), 2);
					}

					InputStruct_->SymVec_->at(s).closer.append(InputStruct_->SymVec_->at(s).enc);
					InputStruct_->SymVec_->at(s).enc.clear();

					inter_ele.push_back(s);
					open++;
				}
			}
		}
		else if (u == -3)
		{
			if (InputStruct_->SymVec_->at(s).order_open > 0)
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an encloser and an encloser is open");
					sint xc = Output(output.c_str(), 2);
				}

				if (!strcmp(InputStruct_->SymVec_->at(s).sym.c_str(), InputStruct_->SymVec_->at(s).closer.c_str()))
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("SymVec[ ");
						output.append(ITOA(s));
						output.append(" ] matches identical uncloser \" ");
						output.append(InputStruct_->SymVec_->at(s).closer);
						output.append(" \" and enclosers are open");
						sint xc = Output(output.c_str(), 2);
					}

					sint xs = s - 1;

					while (xs > -1)
					{
						if (InputStruct_->SymVec_->at(xs).closer_loc == InputStruct_->SymVec_->at(s).loc || InputStruct_->SymVec_->at(xs).enc_loc == InputStruct_->SymVec_->at(s).loc)
						{
							xs = -1;
						}

						xs--;
					}

					if (xs == -1)
					{
						if (debug_lvl >= 10 && debug_m)
						{
							std::string output;
							output.append("encloser was not already assigned to another uncloser or encloser.");
							sint xc = Output(output.c_str(), 2);
						}

						xs = s - 1;

						while (xs > -1) // here we just look for the next available closer in the std::string. inter_encs should be dealt with here..
						{
							sint i = (sint)inter_ele.size() - 1;

							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("there are ");
								output.append(ITOA(i + 1));
								output.append(" interceeding enclosers. checking those first.");
								sint xc = Output(output.c_str(), 2);
							}

							while (i > -1)
							{
								if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1 && !strcmp(InputStruct_->SymVec_->at(inter_ele[i]).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
								{
									sint n = 0;
									sint ni = inter_ele[i] - 1;

									while (ni > -1)
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("SymVec[ ");
											output.append(ITOA(ni));
											output.append(" ].closer is \" ");
											output.append(InputStruct_->SymVec_->at(ni).closer);
											output.append(" \" SymVec[ ");
											output.append(ITOA(ni));
											output.append(" ].closer_loc == ");
											output.append(ITOA(InputStruct_->SymVec_->at(ni).closer_loc));
											sint xc = Output(output.c_str(), 2);
										}

										if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
										{
											n++;
										}

										ni--;
									}

									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append(ITOA(n));
										output.append(" viable enclosers");
										sint xc = Output(output.c_str(), 2);
									}

									if (!n)
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("there were no viable enclosers before inter_ele[ ");
											output.append(ITOA(i));
											output.append(" ] which is element ");
											output.append(ITOA(inter_ele[i]));
											sint xc = Output(output.c_str(), 2);
										}

										sint ii = i + 1;

										while (ii < (sint)inter_ele.size())
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
											{
												if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
												{
													sint si = inter_ele[ii] + 1;

													//if ( InputStruct_->SymVec[ inter_ele[ si ] ].open > InputStruct_->SymVec[ inter_ele[ ii ] ].open )
												//	{
													while (si < s)
													{
														if (InputStruct_->SymVec_->at(si).order_open > 0)
														{
															if (open > 0)
															{
																open--;
															}

															InputStruct_->SymVec_->at(si).order_open--;
														}

														si++;
													}
													//}
												}
											}

											ii++;
										}

										if (InputStruct_->SymVec_->at(s).order_open > 0)
										{
											if (open > 0)
											{
												open--;
											}

											InputStruct_->SymVec_->at(s).order_open = open;
										}

										InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
										InputStruct_->SymVec_->at(s).enc.clear();
										InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
										InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;

										i = -1;
										xs = -1;
									}
									else
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("there were ");
											output.append(ITOA(n));
											output.append("viable enclosers before inter_ele[ ");
											output.append(ITOA(i));
											output.append(" ] which is element ");
											output.append(ITOA(inter_ele[i]));
											sint xc = Output(output.c_str(), 2);
										}

										ni = inter_ele[i] + 1;
										sint xn = 0;

										while (ni < s)
										{
											if (!strcmp(InputStruct_->SymVec_->at(ni).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()) && InputStruct_->SymVec_->at(ni).closer_loc == -1)
											{
												xn++;
											}

											ni++;
										}

										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("there were ");
											output.append(ITOA(xn));
											output.append("viable enclosers after inter_ele[ ");
											output.append(ITOA(i));
											output.append(" ] which is element ");
											output.append(ITOA(inter_ele[i]));
											sint xc = Output(output.c_str(), 2);
										}

										sint ii = i + 1;

										while (ii < (sint)inter_ele.size())
										{
											if (InputStruct_->SymVec_->at(inter_ele[ii]).loc > InputStruct_->SymVec_->at(inter_ele[i]).loc)
											{
												if (InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[ii]).closer_loc > InputStruct_->SymVec_->at(s).loc)
												{
													sint si = inter_ele[ii] + 1;

													//	if ( InputStruct_->SymVec[ inter_ele[ si ] ].open > InputStruct_->SymVec[ inter_ele[ ii ] ].open )
													//	{
													while (si < s)
													{
														if (InputStruct_->SymVec_->at(si).order_open > 0)
														{
															if (open > 0)
															{
																open--;
															}

															InputStruct_->SymVec_->at(si).order_open--;
														}

														si++;
													}
													//	}
												}
											}

											ii++;
										}

										if (InputStruct_->SymVec_->at(s).order_open > 0)
										{
											if (open > 0)
											{
												open--;
											}

											InputStruct_->SymVec_->at(s).order_open = open;
										}

										InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
										InputStruct_->SymVec_->at(s).closer.clear();
										InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(inter_ele[i]).loc;
										InputStruct_->SymVec_->at(inter_ele[i]).closer_loc = InputStruct_->SymVec_->at(s).loc;

										i = -1;
										xs = -1;
									}
								}

								i--;
							}

							if (i == -1)
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] is not an uncloser for any interceeding enclosers");
									sint xc = Output(output.c_str(), 2);
								}

								if (!strcmp(InputStruct_->SymVec_->at(xs).closer.c_str(), InputStruct_->SymVec_->at(s).sym.c_str()))
								{
									if (debug_lvl >= 10 && debug_m)
									{
										std::string output;
										output.append("SymVec[ ");
										output.append(ITOA(xs));
										output.append(" ].closer equal to SymVec[ ");
										output.append(ITOA(s));
										output.append(" ].sym");
										sint xc = Output(output.c_str(), 2);
									}

									if (InputStruct_->SymVec_->at(xs).closer_loc == -1)
									{
										if (debug_lvl >= 10 && debug_m)
										{
											std::string output;
											output.append("encloser at ");
											output.append(ITOA(xs));
											output.append(" has not been deemed as enclosed itself.");
											sint xc = Output(output.c_str(), 2);
										}

										InputStruct_->SymVec_->at(s).enc.append(InputStruct_->SymVec_->at(s).closer);
										InputStruct_->SymVec_->at(s).closer.clear();
										InputStruct_->SymVec_->at(s).enc_loc = InputStruct_->SymVec_->at(xs).loc;
										InputStruct_->SymVec_->at(xs).closer_loc = InputStruct_->SymVec_->at(s).loc;

										i = 0;

										while (i < (sint)inter_ele.size())
										{
											if (InputStruct_->SymVec_->at(inter_ele[i]).closer_loc == -1 || InputStruct_->SymVec_->at(inter_ele[i]).closer_loc > InputStruct_->SymVec_->at(s).loc)
											{
												sint ix = inter_ele[i] + 1;

												while (ix <= s)
												{
													if (InputStruct_->SymVec_->at(ix).order_open > 0)
													{
														if (open > 0)
														{
															open--;
														}

														InputStruct_->SymVec_->at(ix).order_open--;
													}

													ix++;
												}
											}

											i++;
										}

										xs = -1;

										if (InputStruct_->SymVec_->at(s).order_open > 0)
										{
											if (open > 0)
											{
												open--;
											}

											InputStruct_->SymVec_->at(s).order_open = open;
										}
									}
								}
							}

							xs--;
						}

						if (xs == -1)
						{
							if (debug_lvl >= 10 && debug_m)
							{
								std::string output;
								output.append("SymVec[ ");
								output.append(ITOA(s));
								output.append(" ] did not match as closer for any prior symbol in the std::string. ");
								sint xc = Output(output.c_str(), 2);
							}

							// it was an encloser with an identical uncloser, a non relevant uncloser, or the remainder of a prior incomplete statement with unresolved enclosers.
							if (InputStruct_->SymVec_->at(s).closer_loc >= -1)
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] has not been deemed as enclosed. ");
									sint xc = Output(output.c_str(), 2);
								}

								inter_ele.push_back(s);
								open++;
							}
							else // non-relevant or incomplete.
							{
								if (debug_lvl >= 10 && debug_m)
								{
									std::string output;
									output.append("SymVec[ ");
									output.append(ITOA(s));
									output.append(" ] has already been deemed as enclosed. ");
									sint xc = Output(output.c_str(), 2);
								}
							}
						}
					}
				}
				else
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("SymVec[ ");
						output.append(ITOA(s));
						output.append(" ] was identified as an encloser and enclosers are open");
						sint xc = Output(output.c_str(), 2);
					}

					inter_ele.push_back(s);
					open++;
				}
			}
			else
			{
				if (debug_lvl >= 10 && debug_m)
				{
					std::string output;
					output.append("SymVec[ ");
					output.append(ITOA(s));
					output.append(" ] was identified as an encloser and no enclosers are open");
					sint xc = Output(output.c_str(), 2);
				}

				inter_ele.push_back(s);
				open++;
			}
		}
		else
		{

		}

		if (!inter_ele.empty())
		{
			std::vector<sint> alt_eles;
			sint x = 0;

			while (x < (sint)inter_ele.size())
			{
				if (InputStruct_->SymVec_->at(inter_ele[x]).closer_loc == -1)
				{
					alt_eles.push_back(inter_ele[x]);
				}

				else
				{
					if (debug_lvl >= 10 && debug_m)
					{
						std::string output;
						output.append("removing resolved interceeding encloser, inter_ele[");
						output.append(ITOA(x));
						output.append("]");
						sint xc = Output(output.c_str(), 2);
					}
				}

				x++;
			}

			inter_ele = alt_eles;

			if (debug_lvl >= 10 && debug_m)
			{
				std::string output;
				output.append("inter_ele.size(): ");
				output.append(ITOA((sint)inter_ele.size()));
				sint xc = Output(output.c_str(), 2);
				output.clear();

				sint o = 0;

				while (o < (sint)inter_ele.size())
				{
					output.append("SymVec[ ");
					output.append(ITOA(inter_ele[o]));
					output.append(" ] ");
					output.append("sym: \"");
					output.append(InputStruct_->SymVec_->at(inter_ele[o]).sym);
					output.append("\" loc: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).loc));
					output.append("enc: \"");
					output.append(InputStruct_->SymVec_->at(inter_ele[o]).enc);
					output.append("\" closer: \"");
					output.append(InputStruct_->SymVec_->at(inter_ele[o]).closer);
					output.append("\" closer_loc: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).closer_loc));
					output.append(" open: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).open));
					output.append(" order_open: ");
					output.append(ITOA(InputStruct_->SymVec_->at(inter_ele[o]).order_open));
					xc = Output(output.c_str(), 2);
					output.clear();
					o++;
				}
			}
		}

		s++;
	}
	
	if (debug_lvl >= 1 && debug_m )
	{
		sint xc = PISO(InputStruct_, 0);
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
	/*
	if ( answer )
	{
		suboutput = Answer();
	}

	if ( askq )
	{
		suboutput = AskQuestion();
	}
	*/
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

std::string machine::AskQuestion()
{

	std::string output;
	/*
			if ( foundme )
			{
				output = "what?";
			}

			else
			{
				output = "huh?";
			}
	*/
	return output;
}

std::string machine::Answer()
{
	std::string output = "answer";
	return output;
}

void* machine::ReadFile(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint i = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

	if (!i)
	{
		sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&i, false);
		pthread_exit((void*)i);
		return NULL;
	}

	LITEBot.ptn.append(tts.thread_name);
	i = 0;
	sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&i, false);

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		std::string output;
		output.append("::ReadFile() : ");
		i = LITEBot.Output(output.c_str(), 2);
	}

	//sllint xi = LITEBot.TestThreadTRat(&Info);
	BOT_FILE FileStruct;

	//	sint xc = 0;
	//	sint i = LITEBot.SetTTSVEleM( &Info, lid, 3, ( void *)xc );
		/*
		std::vector<tothread_struct > *ttsv_ = ( std::vector<tothread_struct > *)ttsv_;

		if ( LITEBot.debug_lvl >= 1 && debug_m )
		{
			std::string output;
			output.append( "ReadFile() : " );
			i = LITEBot.Output( &Info, output, 2 );
		}

		i = 0;

		if ( LITEBot.debug_lvl >= 1 && debug_m )
		{
			std::string output;
			output.append( "new vec " );
			output.append( FileStruct_->strvec[ 1 ] );
			output.append( " size is: " );
			output.append( LITEBot.ITOA( FileStruct_->strvec.size() ) );
			sint xc = LITEBot.Output( &Info, output, 2 );
		}

		ifstream txtfile( FileStruct_->strvec[ 1 ] );
		std::string txtline, b_txt, rem_txt;
		sint lines = 100;

		if ( FileStruct_->strvec.size() > 2 )
		{
			sint max = 2147483647;

			if ( atoi( FileStruct_->strvec[ 2 ].c_str() ) < max )
			{
				lines = atoi( FileStruct_->strvec[ 2 ].c_str() );
			}
		}

		sint emptylines = 0;
		bool done = false;

		while ( !done )
		{
			sint line = 0;

			while ( line < lines )
			{
				getline( txtfile, txtline );
				sint len = 0;

				if ( !txtline.empty() )
				{
					len = txtline.length();
				}

				switch ( txtline[ 0 ] )
				{
					case '\0' :
					{
						len = 0;
						break;
					}

					case '\n' :
					{
						len = 0;
						break;
					}

					default :
					{
						break;
					}
				}

				if ( len > 1 )
				{
					//analyze a few lines
					emptylines = 0;

					if ( LITEBot.debug_lvl >= 2 )
					{
						sint xc = LITEBot.Output( &Info, txtline, 0 );
					}

					b_txt.append( txtline );
				}

				else if ( len == 1 )
				{

				}

				else
				{
					emptylines++;
				}

				line++;

				if ( emptylines > 999 )
				{
					done = true;
					line = lines;
				}
			}

			sint xc = LITEBot.InterpretInput( &Info, &b_txt );
			b_txt.clear();
		}

		txtfile.close();
		std::string output;
		output.append( "Finished reading file " );
		output.append( FileStruct_->strvec[ 1 ] );
		i = LITEBot.Output( &Info, output, 2 );
		/*
		i = ttsv_->size() - 1;

		while ( i > - 1 )
		{
			if ( ttsv_->at( i ).thread_name == ptn && ttsv_->at( i ).lid == lid ) // d should == lid
			{
				ttsv_->at( i ).thread_name.clear();
				ttsv_->at( i ).lid = -1;
			}

			i--;
		}
		*/
	i = 1;
	xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&i, false);
	pthread_exit((void*)i);
	return NULL;
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
		/*
		if ( str_vec.size() > 1 )
		{
			Output( "str_vec not empty", 2 );
			std::string filename;
			std::vector<std::string> filetypes = DB.Get
			//if ( !str_vec[1].empty() )
		//	{
				sint x = 0;
				sint xmax = str_vec.size();

				while ( x < xmax )
				{
					sint f = filetypes.size() - 1;

					while ( f > -1 )
					{
						if ( filetypes[ f ] == str_vec[ x ] )
						{
							if ( x > 1 )
							{
								filename.append( str_vec[ x - 1 ].append( str_vec[ x ] ) );
							}
						}

						f--;
					}

					x++;
				}

				Output( "str_vec[1] not empty init read file", 2 );
				sint xc = InitReadFile( filename, str_vec );

				if ( !xc )
				{
					// returned nothing, we made it?
				}

				else
				{
					output = "ERROR initializing file: xc = ";
					output.append( ITOA( xc ) );
					Output( output, 1 );

					if ( xc < 100 )
					{

					}

					else if ( xc < 200 )
					{

					}

					else if ( xc < 300 )
					{

					}

					else if ( xc < 400 )
					{

					}

					else if ( xc < 500 )
					{

					}

					else if ( xc < 600 )
					{

					}

					else if ( xc < 700 )
					{

					}

					else
					{
						if ( xc == 999 )
						{

						}

						else
						{

						}
					}
				}
			/*
			ifstream header( str_vec[1] );
			std::string headerfile;
			done = false;

			while ( !done )
			{
				getline( header, headerfile);
				sint len = headerfile.length();

				if ( len > 0 )
				{
					char comparison = headerfile.at( 0 );

					if ( comparison != '#' )
					{
						 done = true;
					}
				}
			}

			header.close();
			//
	//		}

		}
		*/
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
					xc = GetDateTimeNS(dated);
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
			AddStrToVec(&t.vals, Uppercase(LEncStrI(&vec_->at(1), -1).c_str()).c_str());
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

/*
sint machine::std::stringSimilarity(std::string strI, std::string strII )
{
	sint xc = 0;
	sint a = strI.length();
	sint b = strII.length();
	sint c = 0;
	sint d = 0;
	
	while ( c < a && d < b )
	{
		if ( strI[ c ] == strII[ d ] )
		{
			xc++;
			c++;
			d++;
		}
		
		else
		{
			if 
		}
	}
	
	return xc;
}
*/

sint machine::OutputBasicIdents()
{
	uint x = (uint)Output("Basic Idents :", 2);
	std::string output;
	for (x = 0; x < bidents.idents.size(); x++)
	{
		std::string idtype;
		uint i = (uint)GetIdentsSpec(&idtype, x);

		for (i = 0; i < (sint)bidents.idents[x].size(); i++)
		{
			carr_512 ncar;
			PARSS Sym;
			sint o = GetIdentsVE(&Sym, i, x);
			o = BStrP(ncar.carr, ncar.siz, "idents[%i][%i}.sym: \"%s\" id:%i enc: \"%s\" closer: \"%s\" enc_is:%i\n", x, i, Sym.sym.c_str(), Sym.id, Sym.enc.c_str(), Sym.closer.c_str(), Sym.encloseris);
			output.append(ncar.carr);

			if (!Sym.usages.empty())
			{
				output.append(" usages: ");
				for (o = 0; o < (sint)Sym.usages.size(); o++)
				{
					output.append(ITOA(Sym.usages[o]));
					output.append(" ");
				}
				output.pop_back();
			}

			if (!Sym.constituent_to.empty())
			{
				output.append(" constituent_to: \" ");
				for (o = 0; o < (sint)Sym.constituent_to.size(); o++)
				{
					output.pop_back();
					output.append(Sym.constituent_to[o]);
					output.append(" \"");
				}
			}

			if (!Sym.constituent_types.empty())
			{
				output.append(" constituent_types: ");
				for (o = 0; o < (sint)Sym.constituent_types.size(); o++)
				{
					output.append(Sym.constituent_types[o]);
					output.append(" ");
				}
				output.pop_back();
			}
			output.append("\n");
		}
	}
	x = (uint)Output(output.c_str(), 2);
	return 0;
}

sint machine::GetIdents(cchar* str_, std::vector<std::string> *strvec_, sint idents, sint opt)
{
	std::vector<PARSS> rvec;
	sint p = GetBasicIdents("", strvec_, &rvec, idents, opt);

	if (!rvec.empty())
	{
		p = 0;

		while (p < (sint)rvec.size())
		{
			sint xc = 0;

			while (xc < (sint)rvec[p].usages.size())
			{
				if (rvec[p].usages[xc] < (sint)bidents.idents.size())
				{
					sint x = (sint)bidents.idents[rvec[p].usages[xc]].size() - 1;

					while (x > -1)
					{
						if (!strcmp(bidents.idents[rvec[p].usages[xc]][x].sym.c_str(), rvec[p].sym.c_str()))
						{
							x = -1;
						}						x--;
					}

					if (x == -1)
					{
						bidents.idents[rvec[p].usages[xc]].push_back(rvec[p]);
					}
				}
				xc++;
			}
			p++;
		}
	}
	return 0;
}

sint machine::PushToIdents(std::vector<PARSS> *vec_, cchar *str_ )
{
	if ( debug_lvl >= 1 && debug_m )
	{
		std::string output;
		output.append( "pushing new ident type " );
		output.append( str_ );
		output.append( " to idents " );
		sint xc = Output(output.c_str(), 2 );
	}
	sint p = (sint)bidents.idents.size() - 1;
	
	while ( p > -1 )
	{
		if ( !strcmp( str_, bidents.specs.at( p ).c_str() ) )
		{
			p = -1;
		}
		
		p--;
	}
	
	if ( p == -1 )
	{
		bidents.idents.push_back( *vec_ );
		bidents.specs.push_back( str_ );
	}
	return 0;
}

sint machine::PushToIdentsV(PARSS *Sym_, sint x )
{
	if ( debug_lvl >= 1 && debug_m )
	{
		std::string output;
		output.append( "pushing " );
		output.append( Sym_->sym );
		output.append( " to idents " );
		output.append( ITOA( x ) );
		sint xc = Output(output.c_str(), 2 );
	}
	
	if ( x < (sint)bidents.idents.size() )
	{
		bidents.idents[ x ].push_back( *Sym_ );
	}
	return 0;
}

sint machine::ClearIdents()
{
	if ( debug_lvl >= 1 && debug_m )
	{
		std::string output;
		output.append( "clearing all idents" );
		sint xc = Output(output.c_str(), 2 );
	}
	
	bidents.idents.clear();
	return 0;
}

sint machine::ClearIdentsV(sint x )
{
	if ( debug_lvl >= 1 && debug_m )
	{
		std::string output;
		output.append( "clearing idents type " );
		output.append( ITOA( x ) );
		sint xc = Output(output.c_str(), 2 );
	}
	
	if ( x < (sint)bidents.idents.size() )
	{
		bidents.idents[ x ].clear();
	}
	return 0;
}

sint machine::ClearIdentsVE(sint x, sint e )
{
	if ( debug_lvl >= 1 && debug_m )
	{
		std::string output;
		output.append( "clearing idents type " );
		output.append( ITOA( x ) );
		output.append( "element " );
		output.append( ITOA( e ) );
		sint xc = Output(output.c_str(), 2 );
	}
	
	if ( e < (sint)bidents.idents[ x ].size() && x < (sint)bidents.idents.size() )
	{
		PARSS Sym;
		bidents.idents[ x ][ e ] = Sym;
	}
	return 0;
}

sint machine::SetIdentsV(std::vector<PARSS> *vec_, sint x )
{
	if ( x < (sint)bidents.idents.size() )
	{
		bidents.idents[ x ] = *vec_;
	}
	return 0;
}

sint machine::SetIdentsVE(PARSS *Sym_, sint x, sint e )
{
	if ( e < (sint)bidents.idents[ x ].size() && x < (sint)bidents.idents.size() )
	{
		bidents.idents[ x ][ e ] = *Sym_;
	}
	return 0;
}

sint machine::GetIdentsV(std::vector<PARSS> *vec_, sint x )
{
	if ( x < (sint)bidents.idents.size() )
	{
		*vec_ = bidents.idents[ x ];
	}
	return 0;
}

sint machine::GetIdentsVE(PARSS *Sym_, sint x, sint e )
{
	if ( e < (sint)bidents.idents[ x ].size() && x < (sint)bidents.idents.size() )
	{
		*Sym_ = bidents.idents[ x ][ e ];
	}
	return 0;
}

sint machine::GetIdentsSize()
{
	sint x = (sint)bidents.idents.size();
	return x;
}

sint machine::GetIdentsSizeV(sint x )
{
	sint xc = 0;
	
	if ( x < (sint)bidents.idents.size() )
	{
		xc = (sint)bidents.idents[ x ].size();
	}
	return xc;
}

sint machine::GetIdentsSpec(std::string *str_, sint x )
{
	sint xc = 0;
	
	if ( x < (sint)bidents.specs.size() )
	{
		*str_ = bidents.specs[ x ];
	}
	return xc;
}

sint machine::ClearClient(BOT_CLIENT *c_)
{
	BOT_CLIENT c;
	*c_ = c;
	return 0;
}

void* machine::LogMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

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
	LITEBot.ptn.append(tts.thread_name);
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
					xc = LITEBot.LockElement(MTX_LOG, logm.lid, false, true, false);

					if (LITEBot.LockRet(xc) > -1)
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
						if (!xc)
						{
							xc = LITEBot.UnlockElement(MTX_LOG, logm.lid, false);
						}
					}
				}

			}
		}
		xc = LITEBot.Rest(10);
		sint fin = -1;
		xc = LITEBot.GetVecEleMem(&fin, MTX_TTSV, LITEBot.lid, BOT_TTS_FIN);

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
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);
	
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
	LITEBot.ptn.append(tts.thread_name);
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
		xc = LITEBot.Rest(1000);
		sint fin = -1;
		xc = LITEBot.GetVecEleMem(&fin, MTX_TTSV, LITEBot.lid, BOT_TTS_FIN);

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
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

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

	LITEBot.ptn.append(tts.thread_name);
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

std::string machine::CleanPunctuation(cchar* clientinput_ = 0)
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

sint machine::GetBasicIdents(cchar *str_, std::vector<std::string> *strvec_, std::vector<PARSS> *rvec_, sint ident, sint opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_1024 outp;
		sint op = BStrP(outp.carr, outp.siz, "GetBasicIdents(cchar* str_ \"%s\", vector<std::string>* strvec_(%i), vector<PARSS>* rvec_(%i), sint ident(%i), sint opt(%i))", str_, (sint)strvec_->size(), (sint)rvec_->size(), ident, opt);
		op = Output(outp.carr, 2);
	}

	if (!str_ || !strvec_ || !rvec_)
	{
		return -1;
	}

	BOT_DB dbs;
	sint rc = GetVecEleByName((void*)&dbs, MTX_DBL, "litebot", false, false);

	if (rc)
	{
		return -1;
	}

	BOT_STMT t(false, 0, "litebot");
	t.AddCont("SYMS",1);

	if (!strvec_->empty())
	{
		for (size_t siz = 0; siz < strvec_->size(); siz++)
		{
			AddStrToVec(&t.conds, strvec_->at(siz).c_str());
		}
	}

	if (!strlen(str_))
	{
		if (!t.conds.empty())
		{
			t.opts[3].push_back(0);
		}
		AddStrToVec(&t.cols,"SYMBOL",false,false);
		AddStrToVec(&t.vals,str_,false,false);
	}

	sint tc = 0;

	while (rc < (sint)dbs.tables.size())
	{
		if (!strcmp("SYMS", dbs.tables[rc].c_str()))
		{
			tc = rc;

			if (rc < (sint)dbs.columns.size())
			{
				if (!dbs.columns[rc].empty())
				{
					if (ident > -1)
					{
						if (ident + 10 < (sint)dbs.columns[rc][0].size())
						{
							if (!t.conds.empty())
							{
								t.opts[3].push_back(1);
							}

							t.opts[0].push_back(1);
							AddStrToVec(&t.cols, "", false,false);
							AddStrToVec(&t.cols,dbs.columns[rc][0][ident + 10].c_str());
							t.opts[1].push_back(3);
							AddStrToVec(&t.vals,"1",false,false);
						}
						else
						{
							return 1;
						}
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
			rc = (sint)dbs.tables.size();
		}
		rc++;
	}
	
	sint hdb = 0;
	sint odb = OpenDB(t.dbname.c_str(), 1, &hdb);

	if (odb > -1)
	{
		rc = BQS(&t);

		if (!rc)
		{
			if (debug_lvl >= 10 && debug_m)
			{
				std::string output;
				output.append("Preparing SELECT statement: ");
				output.append(t.stmt);
				rc = Output(output.c_str(), 2);
			}

			cchar* tail;
			sqlite3_stmt* ppstmt;
			rc = sqlite3_prepare_v2(d_con_->db_, t.stmt.c_str(), (sint)t.stmt.length(), &ppstmt, &tail);

			if (!rc)
			{
				if (opt == 1)
				{
					ClearIdentsV(ident);
				}

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
							sint op = Output("SQLITE_OK", 2);
						}
						done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							sint op = Output("SQLITE_DONE", 2);
						}
						done = true;
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							sint op = Output("SQLITE_ROW", 2);
						}

						PARSS Sym;
						rc = FindColumn("ID", ppstmt);

						if (rc > -1)
						{
							Sym.id = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("CONFIRMED", ppstmt);

						if (rc > -1)
						{
							rc = sqlite3_column_int(ppstmt, rc);

							if (rc)
							{
								Sym.confirmed = true;
							}
						}

						rc = FindColumn("SYMBOL", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								Sym.sym.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
							}
						}

						rc = FindColumn("CONSTITUENT_TO", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string str;
								str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								std::vector<std::string> vec;
								uchar chr = ' ';
								rc = SeparateStrByChar(&str, &chr, &vec, 1);
								str.clear();
								rc = 0;

								while (rc < (sint)vec.size())
								{
									Sym.constituent_to.push_back(vec[rc]);
									rc++;
								}
							}
						}

						rc = FindColumn("CONSTITUENT_TYPES", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string str;
								str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								std::vector<std::string> vec;
								uchar chr = ' ';
								rc = SeparateStrByChar(&str, &chr, &vec, 1);
								str.clear();
								rc = 0;

								while (rc < (sint)vec.size())
								{
									if (!strcmp(vec[rc].c_str(), ","))
									{
										if (!str.empty())
										{
											Sym.constituent_types.push_back(str);
											str.clear();
										}
									}
									else
									{
										str.append(vec[rc]);
										str.append(" ");
									}

									rc++;
								}
							}
						}

						rc = 10; //there are 10 cols for common_syms before usage columns

						while (rc < (sint)dbs.columns[tc][0].size())
						{
							sint xc = FindColumn(dbs.columns[tc][0][rc].c_str(), ppstmt);

							if (xc > -1)
							{
								xc = sqlite3_column_int(ppstmt, xc);

								if (xc > 0)
								{
									Sym.usages.push_back(rc - 10);
								}
							}

							rc++;
						}

						rc = FindColumn("PAIR_SYM", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								Sym.closer.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
							}
						}

						rvec_->push_back(Sym);
						break;
					}
					case SQLITE_BUSY:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							sint op = Output("SQLITE_BUSY", 2);
						}
						done = true;
						break;
					}
					default:
					{
						std::string output;
						rc = IGetError(&output, 0);
						rc = Output(output.c_str(), 2);
						rc = Output(output.c_str(), 1);
						done = true;
						break;
					}
					}
				}

				rc = sqlite3_finalize(ppstmt);

				if (rc)
				{
					sint oc = Output(GetError().c_str(), 1);
				}
			}
			else
			{
				std::string output;
				rc = IGetError(&output, 0);
				rc = Output(output.c_str(), 2);
				rc = Output(output.c_str(), 1);
			}
		}
		if (!hdb)
		{
			sint xc = CloseDB("litebot");
		}
		if (debug_lvl >= 1 && debug_m)
		{
			sint oc = Output("Returning basic idents", 2);
			oc = OutputBasicIdents();
		}
		return 0;
	}
	return -1;
}

sint machine::VerifyBasicIdents(BOT_DB *dbs_, std::vector<BOT_STMT> *tvec_, sint table)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint oc = BStrP(outp.carr, outp.siz, "::VerifyBasicIdents(BOT_DB* dbs_ \"%s\", vector<BOT_STMT>* tvec_(%i), sint table(%i))", (sint)dbs_, (sint)tvec_, table);
		oc = Output(outp.carr, 2);
	}

	if (!dbs_ || !tvec_ || table < 0)
	{
		return -1;
	}

	if (table < (sint)dbs_->columns.size())
	{
		if (dbs_->columns[table].size() > 1)
		{
			if (dbs_->columns[table][0].size() > 10)
			{

			}
			else
			{

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

	std::vector<std::string> strvec;
	sint x = GetIdents("", &strvec, -1, -1);
	std::vector<sint> vec;
	x = GetIdentsSize();

	if (!x)
	{
		if (debug_lvl >= 1 && debug_m)
		{
			x = Output("no idents.", 2);
		}
		BuildBasicIdents(dbs_, tvec_, &vec);
		return 1;
	}

	if (x < (sint)dbs_->columns[table][0].size() - 10 && x > -1)
	{
		while (x < (sint)dbs_->columns[table][0].size() - 10 && x > -1)
		{
			std::vector<PARSS> pvec;
			sint xc = PushToIdents(&pvec, dbs_->columns[table][0][x + 10].c_str());
			x++;
		}
	}

	x = 0;

	while (x < GetIdentsSize())
	{
		if (!GetIdentsSizeV(x))
		{
			vec.push_back(x);
		}

		x++;
	}

	if (!vec.empty())
	{
		if (debug_lvl >= 1 && debug_m)
		{
			std::string output;
			output.append(ITOA((sint)vec.size()));
			output.append(" idents were empty ");
			x = Output(output.c_str(), 2);
		}
		BuildBasicIdents(dbs_, tvec_, &vec);
		return 1;
	}
	else
	{
		if (debug_lvl >= 1 && debug_m)
		{
			x = Output("verified idents", 2);
		}
		return 0;
	}
}

sint machine::BuildBasicIdents(BOT_DB *dbs_, std::vector<BOT_STMT> *tvec_, std::vector<sint> *opts_)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "::BuildBasicIdents(BOT_DB* dbs_ \"%s\", vector<BOT_STMT>* tvec_(%i), vector<sint> opts_(%i))", (sint)dbs_, (sint)tvec_, (sint)opts_);
		op = Output(outp.carr, 2);
	}

	if (!dbs_ || !tvec_ || !opts_)
	{
		return -1;
	}

	if (opts_->empty())
	{
		return 1;
	}

	sint tc = 0;

	for (sint ip = (sint)dbs_->tables.size() - 1; ip > -1; ip--)
	{
		if (!strcmp("SYMS", dbs_->tables[ip].c_str()))
		{
			tc = ip;

			if (ip < (sint)dbs_->columns.size())
			{
				if (!dbs_->columns[ip].empty())
				{

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

			ip = -1;
		}
	}

	if (debug_lvl >= 1 && debug_m)
	{
		int oc = Output("building idents.", 2);
	}

	if (opts_->empty())
	{
		int nsiz = 0;
		while (nsiz < 8)
		{
			opts_->push_back(nsiz);
			nsiz++;
		}
	}
	for (uint y = 0; y < opts_->size(); y++)
	{
		std::vector<PARSS> pvec;

		switch (opts_->at(y))
		{
		case 0:
		{
			size_t nsiz = 0;

			while (nsiz < nrts_sep.size())
			{
				PARSS p;
				p.sym.push_back(nrts_sep[nsiz]);
				p.usages.push_back(opts_->at(y));
				pvec.push_back(p);
				nsiz++;
			}
			break;
		}
		case 1 :
		{
			std::string str;
			sint rc = GetChars(&pvec, &str, opts_->at(y));
			break;
		}
		case 2 :
		{
			std::string str;
			sint rc = GetChars(&pvec, &str, opts_->at(y));
			break;
		}
		case 3 :
		{
			std::string str;
			sint rc = GetChars(&pvec, &str, opts_->at(y));
			break;
		}
		case 4 :
		{
			for (size_t nsiz = 0; nsiz < nrts_lit.size(); nsiz++)
			{
				PARSS p;
				p.usages.push_back(opts_->at(y));
				p.sym.push_back(nrts_lit[nsiz]);
				p.closer.push_back(nrts_lit[nsiz]);
				pvec.push_back(p);
			}
			break;
		}
		case 5 :
		{
			bool enc = true;

			for (size_t nsiz = 0; nsiz < nrts_ord.size(); nsiz++)
			{
				if (enc)
				{
					PARSS p;
					p.usages.push_back(opts_->at(y));
					p.sym.push_back(nrts_lit[nsiz]);
					p.closer.push_back(nrts_lit[nsiz + 1]);
					pvec.push_back(p);
					enc = false;
				}
				else
				{
					PARSS p;
					p.usages.push_back(opts_->at(y));
					p.sym.push_back(nrts_lit[nsiz]);
					p.enc.push_back(nrts_lit[nsiz - 1]);
					pvec.push_back(p);
					enc = true;
				}
			}
			break;
		}
		case 6 :
		{
			for (size_t nsiz = 0; nsiz < nrts_end.size(); nsiz++)
			{
				PARSS p;
				p.usages.push_back(opts_->at(y));
				p.sym.push_back(nrts_end[nsiz]);
				pvec.push_back(p);
			}
			break;
		}
		case 7 :
		{
			for (size_t nsiz = 0; nsiz < nrts_ass.size(); nsiz++)
			{
				PARSS p;
				p.usages.push_back(opts_->at(y));
				p.sym.push_back(nrts_ass[nsiz]);
				pvec.push_back(p);
			}
			break;
		}
		default:
		{

			break;
		}
		}

		for (uint ip = 0; ip < pvec.size(); ip++)
		{
			sint x = GetIdentsSizeV(opts_->at(y)) - 1;

			while (x > -1)
			{
				PARSS Sym;
				sint rc = GetIdentsVE(&Sym, opts_->at(y), x);

				if (!strcmp(Sym.sym.c_str(), pvec[ip].sym.c_str()))
				{
					for (uint u = 0; u < (sint)pvec[ip].usages.size(); u++)
					{
						sint xu = (sint)Sym.usages.size() - 1;

						while (xu > -1)
						{
							if (pvec[ip].usages[u] == Sym.usages[xu])
							{
								xu = -1;
							}
							xu--;
						}
						if (xu == -1)
						{
							for (xu = 0; xu < (sint)Sym.usages.size(); xu++)
							{
								sint ux = (sint)pvec[ip].usages.size() - 1;

								while (ux > -1)
								{
									if (Sym.usages[xu] == pvec[ip].usages[ux])
									{
										ux = -1;
									}
									ux--;
								}
								if (ux == -1)
								{
									pvec[ip].usages.push_back(Sym.usages[xu]);
								}
							}
							Sym.usages.push_back(pvec[ip].usages[u]);
						}
					}
					rc = SetIdentsVE(&Sym, opts_->at(y), x);
					x = -1;
				}
				x--;
			}
			if (x == -1)
			{
				BOT_STMT t(false, 2, "litebot");
				t.opts[0].push_back(2);
				t.AddCont("SYMS", 1);
				AddStrToVec(&t.cols,"SYMBOL",false,false);
				sint f = pvec[ip].sym.find("\"", 0);
				std::string enc;

				if (f > -1)
				{
					f = pvec[ip].sym.find("'", 0);

					if (f > -1)
					{

					}
					else
					{
						enc.append("'");
					}
				}
				else
				{
					enc.append("\"");
				}

				if (!pvec[ip].sym.empty())
				{
					std::string str;
					str.append(enc);
					str.append(pvec[ip].sym);
					str.append(enc);
					AddStrToVec(&t.vals,str.c_str());
				}

				if (!pvec[ip].closer.empty())
				{
					std::string str;
					AddStrToVec(&t.cols, "PAIR_SYM");
					str.append(enc);
					str.append(pvec[ip].closer);
					str.append(enc);
					AddStrToVec(&t.vals,str.c_str());
				}
				else if (!pvec[ip].enc.empty())
				{
					std::string str;
					AddStrToVec(&t.cols, "PAIR_SYM");
					str.append(enc);
					str.append(pvec[ip].enc);
					str.append(enc);
					AddStrToVec(&t.vals,str.c_str());
				}
				else{}

				std::vector<std::string> columns;
				columns = dbs_->columns[tc][0];

				for (f = (sint)pvec[ip].usages.size() - 1; f > -1; f--)
				{
					x = pvec[ip].usages[f];

					if (x + 10 < (sint)columns.size())
					{
						AddStrToVec(&t.cols,columns[x + 10].c_str());
						columns[x + 10].clear();
						AddStrToVec(&t.vals,"1");
					}
				}

				for (f = 10; f < (sint)columns.size(); f++)
				{
					if (columns[f].length())
					{
						AddStrToVec(&t.cols,columns[f].c_str());
						AddStrToVec(&t.vals,"0");
					}
				}
				tvec_->push_back(t);
			}
		}
	}
	return 0;
}

sint machine::AddBasicIdents(std::vector<PARSS> *vec_)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_128 outp;
		sint op = BStrP(outp.carr, outp.siz, "::AddBasicIdents(vector<PARSS>* vec_(%i))", (sint)vec_);
		op = Output(outp.carr, 2);
	}

	if (!vec_)
	{
		return -1;
	}

	BOT_DB dbs;
	sint v = GetVecEleByName((void*)&dbs, MTX_DBL, "litebot", false, false);
	sint tc = 0;
	
	for (v = (sint)dbs.tables.size() - 1; v > -1; v--)
	{
		if (!strcmp("SYMS", dbs.tables[v].c_str()))
		{
			tc = v;

			if (v < (sint)dbs.columns.size())
			{
				if (!dbs.columns[v].empty())
				{

				}
				else
				{
					return 1;
				}
			}
			v = -1;
		}
	}

	std::vector<BOT_STMT> tvec;
	for (v = 0; v < (sint)vec_->size(); v++)
	{
		if (!vec_->at(v).usages.empty())
		{
			BOT_STMT t(false, 2, "litebot");
			t.opts[0].push_back(2);
			t.AddCont("SYMS", 1);
			AddStrToVec(&t.cols,"SYMBOL",false,false);
			sint f = vec_->at(v).sym.find("\"", 0);
			std::string str, enc;

			if (f > -1)
			{
				f = vec_->at(v).sym.find("'", 0);

				if (f > -1)
				{

				}
				else
				{
					enc.append("'");
				}
			}
			else
			{
				enc.append("\"");
			}

			str.append(enc);
			str.append(vec_->at(v).sym);
			str.append(enc);
			std::string nval;
			nval.append(str);
			AddStrToVec(&t.vals,nval.c_str());
			nval.clear();
			str.clear();
			std::string ncol;
			ncol.append("PAIR_SYM");
			AddStrToVec(&t.cols,ncol.c_str());
			str.append(enc);
			nval.append(str);
			AddStrToVec(&t.vals,nval.c_str());
			str.clear();

			if (!vec_->at(v).closer.empty())
			{
				str.append(enc);
				str.append(vec_->at(v).closer);
				str.append(enc);
				AddStrToVec(&t.vals,str.c_str());
				str.clear();
			}
			else if (!vec_->at(v).enc.empty())
			{
				str.append(enc);
				str.append(vec_->at(v).enc);
				str.append(enc);
				AddStrToVec(&t.vals,str.c_str());
				str.clear();
			}
			else
			{
				t.cols.pop_back();
			}

			std::vector<std::string> columns;
			columns = dbs.columns[tc][0];
			for (f = (sint)vec_->at(v).usages.size() - 1; f > -1; f--)
			{
				sint x = vec_->at(v).usages[f];

				if (x + 10 < (sint)columns.size())
				{
					AddStrToVec(&t.cols,columns[x + 10].c_str());
					columns[x + 10].clear();
					AddStrToVec(&t.vals,"1");
				}
				/*
				else
				{
				if ( vec_->at( v ).confirmed )
				{
				while ( dbs.columns[ tc ][ 0 ].size() )
				{

				}
				}
				}
				*/
			}

			for (f = 10; f < (sint)columns.size(); f++)
			{
				if (columns[f].length())
				{
					AddStrToVec(&t.cols,columns[f].c_str());
					nval.append("0");
					AddStrToVec(&t.vals,nval.c_str());
				}
			}
			tvec.push_back(t);
		}
	}
	v = Commit(&tvec);
	return v;
}

sint machine::GetChars(std::vector<PARSS> *pvec_, std::string* lang_, sint opt)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "::GetChars(vector<PARSS>* pvec_(%i), std::string* lang_ \"%s\", sint opt(%i))", (sint)pvec_, (sint)lang_, opt);
		op = Output(outp.carr, 2);
	}

	if (!pvec_ || !lang_)
	{
		return -1;
	}

	BOT_STMT t(false, 0, "litebot");
	t.AddCont("LANGUAGES", 1);
	
	sint hdb = 0;
	sint odb = OpenDB(t.dbname.c_str(), 1, &hdb);
	sint rc = -1;

	if (odb > -1)
	{
		if (lang_->length()) // chars for specific languages specified by id
		{
			t.opts[0].push_back(0);
			t.opts[1].push_back(3);
			AddStrToVec(&t.cols, "", false, false);
			AddStrToVec(&t.cols, "LANGUAGE", false, false);
			AddStrToVec(&t.vals, LEncStrI(lang_, -1).c_str(), false, false);
			t.opts[6].push_back(0);
		}

		rc = BQS(&t);

		if (!rc)
		{
			if (debug_lvl >= 1 && debug_m)
			{
				std::string output;
				output.append("Preparing SELECT statement: ");
				output.append(t.stmt);
				rc = Output(output.c_str(), 2);
			}

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
						if (debug_lvl >= 5 && debug_m)
						{
							sint op = Output("SQLITE_OK", 2);
						}
						done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 10 && debug_m)
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
							std::string output;
							output.append("Found language: ");
							rc = FindColumn("LANGUAGE", ppstmt);

							if (rc > -1)
							{
								if (sqlite3_column_text(ppstmt, rc) != NULL)
								{
									output.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								}
							}
							sint op = Output(output.c_str(), 2);
						}

						std::vector<PARSS> pvec;
						std::string strI;
						cchar* cstr;

						if (opt == 1)
						{
							rc = FindColumn("U_CASE_CONSONANTS", ppstmt);

							if (rc > -1)
							{
								if (sqlite3_column_text(ppstmt, rc) != NULL)
								{
									cstr = reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc));
									strI.append(cstr);
								}
							}

							rc = 0;

							while (rc < (sint)strI.length())
							{
								PARSS p;
								sint yay = sizeof(strI.substr(rc, 1)) - 1;
								char strii[sizeof(strI.at(rc))]{ 0 };

								while (yay > -1)
								{
									strii[yay] = strI.at(rc) - yay;
									yay--;
								}

								yay = 0;

								while (yay < sizeof(strii))
								{
									p.sym.push_back(strii[yay]);
									yay++;
								}
								p.usages.push_back(1);
								pvec.push_back(p);
								rc++;
							}

							strI.clear();
							rc = (sint)pvec.size() - 1;

							while (rc > -1)
							{
								sint x = (sint)pvec_->size() - 1;

								while (x > -1)
								{
									if (!strcmp(pvec_->at(x).sym.c_str(), pvec[rc].sym.c_str()))
									{
										x = -1;
									}
									x--;
								}
								if (x == -1)
								{
									pvec_->push_back(pvec[rc]);
								}
								rc--;
							}

							pvec.clear();
							rc = FindColumn("L_CASE_CONSONANTS", ppstmt);

							if (rc > -1)
							{
								if (sqlite3_column_text(ppstmt, rc) != NULL)
								{
									cstr = reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc));
									strI.append(cstr);
								}
							}

							rc = 0;

							while (rc < (sint)strI.length())
							{
								PARSS p;
								sint yay = sizeof(strI.at(rc)) - 1;
								char strii[sizeof(strI.at(rc))]{ 0 };

								while (yay > -1)
								{
									strii[yay] = strI.at(rc) - yay;
									yay--;
								}

								yay = 0;

								while (yay < sizeof(strii))
								{
									p.sym.push_back(strii[yay]);
									yay++;
								}

								p.usages.push_back(1);
								pvec.push_back(p);
								rc++;
							}

							strI.clear();
							rc = (sint)pvec.size() - 1;

							while (rc > -1)
							{
								sint x = (sint)pvec_->size() - 1;

								while (x > -1)
								{
									if (!strcmp(pvec_->at(x).sym.c_str(), pvec[rc].sym.c_str()))
									{
										x = -1;
									}
									x--;
								}
								if (x == -1)
								{
									pvec_->push_back(pvec[rc]);
								}
								rc--;
							}
							pvec.clear();
						}
						else if (opt == 2)
						{
							rc = FindColumn("U_CASE_VOWELS", ppstmt);

							if (rc > -1)
							{
								if (sqlite3_column_text(ppstmt, rc) != NULL)
								{
									strI.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								}
							}
							rc = 0;

							while (rc < (sint)strI.length())
							{
								PARSS p;
								sint yay = sizeof(strI.at(rc)) - 1;
								char strii[sizeof(strI.at(rc))]{ 0 };

								while (yay > -1)
								{
									strii[yay] = strI.at(rc) - yay;
									yay--;
								}

								yay = 0;

								while (yay < sizeof(strii))
								{
									p.sym.push_back(strii[yay]);
									yay++;
								}

								p.usages.push_back(2);
								pvec.push_back(p);
								rc++;
							}

							strI.clear();
							rc = (sint)pvec.size() - 1;

							while (rc > -1)
							{
								sint x = (sint)pvec_->size() - 1;

								while (x > -1)
								{
									if (!strcmp(pvec_->at(x).sym.c_str(), pvec[rc].sym.c_str()))
									{
										x = -1;
									}
									x--;
								}
								if (x == -1)
								{
									pvec_->push_back(pvec[rc]);
								}
								rc--;
							}

							pvec.clear();
							rc = FindColumn("L_CASE_VOWELS", ppstmt);

							if (rc > -1)
							{
								if (sqlite3_column_text(ppstmt, rc) != NULL)
								{
									strI.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								}
							}

							rc = 0;

							while (rc < (sint)strI.length())
							{
								PARSS p;
								sint yay = sizeof(strI.at(rc)) - 1;
								char strii[sizeof(strI.at(rc))]{ 0 };

								while (yay > -1)
								{
									strii[yay] = strI.at(rc) - yay;
									yay--;
								}

								yay = 0;

								while (yay < sizeof(strii))
								{
									p.sym.push_back(strii[yay]);
									yay++;
								}

								p.usages.push_back(2);
								pvec.push_back(p);
								rc++;
							}

							strI.clear();
							rc = (sint)pvec.size() - 1;

							while (rc > -1)
							{
								sint x = (sint)pvec_->size() - 1;

								while (x > -1)
								{
									if (!strcmp(pvec_->at(x).sym.c_str(), pvec[rc].sym.c_str()))
									{
										x = -1;
									}
									x--;
								}

								if (x == -1)
								{
									pvec_->push_back(pvec[rc]);
								}
								rc--;
							}

							pvec.clear();
						}
						else if (opt == 3)
						{
							rc = FindColumn("NUMBER_SYMS", ppstmt);

							if (rc > -1)
							{
								if (sqlite3_column_text(ppstmt, rc) != NULL)
								{
									strI.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								}
							}

							rc = 0;

							while (rc < (sint)strI.length())
							{
								PARSS p;
								sint yay = sizeof(strI.at(rc)) - 1;
								char strii[sizeof(strI.at(rc))]{ 0 };

								while (yay > -1)
								{
									strii[yay] = strI.at(rc) - yay;
									yay--;
								}

								yay = 0;

								while (yay < sizeof(strii))
								{
									p.sym.push_back(strii[yay]);
									yay++;
								}

								p.usages.push_back(3);
								pvec.push_back(p);
								rc++;
							}

							strI.clear();
							rc = (sint)pvec.size() - 1;

							while (rc > -1)
							{
								sint x = (sint)pvec_->size() - 1;

								while (x > -1)
								{
									if (!strcmp(pvec_->at(x).sym.c_str(), pvec[rc].sym.c_str()))
									{
										x = -1;
									}
									x--;
								}

								if (x == -1)
								{
									pvec_->push_back(pvec[rc]);
								}
								rc--;
							}
							pvec.clear();
						}
						break;
					}
					case SQLITE_BUSY:
					{
						if (debug_lvl >= 5 && debug_m)
						{
							sint op = Output("SQLITE_BUSY", 2);
						}
						done = true;
						break;
					}
					default:
					{
						std::string output;
						sint op = IGetError(&output, 0);
						op = Output(output.c_str(), 2);
						op = Output(output.c_str(), 1);
						done = true;
						break;
					}
					}
				}

				rc = sqlite3_finalize(ppstmt);

				if (rc)
				{
					rc = Output(GetError().c_str(), 1);
				}

				if (debug_lvl >= 10 && debug_m)
				{
					sint rc = Output("GetChars() success", 2);
				}
			}
			else
			{
				std::string output;
				rc = IGetError(&output, 0);
				rc = Output(output.c_str(), 2);
				rc = Output(output.c_str(), 1);
			}
		}
		if (!hdb)
		{
			rc = CloseDB("litebot");
		}
	}
	return rc;
}

void* machine::AddThisCode(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint xc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

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

	LITEBot.ptn.append(tts.thread_name);
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

sint machine::GetWord(cchar *str_, std::vector<WORD_STRUCT> *Words_, char x_cond_[], sint row)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "GetWord(cchar* str_(%i), vector<WORD_STRUCT>* Words_(%i), cchar* x_cond_(%i), sint row(%i))", (sint)str_, (sint)Words_, (sint)x_cond_, row);
		op = Output(outp.carr, 2);
	}

	if (!str_ || !Words_)
	{
		return -1;
	}

	if (!strlen(str_))
	{
		return 1;
	}

	std::string dbn;
	dbn.push_back(str_[0]);
	BOT_DB_M dbs;
	sint rc = GetVecEleByName((void*)&dbs, MTX_DBL, dbn.c_str());

	if (dbs.type != 3)
	{
		return 1;
	}

	BOT_STMT t(false, 0, dbs.name.c_str());
	std::string str;
	str.push_back(str_[0]);

	if (strlen(str_) > 1)
	{
		str.push_back(str_[1]);
	}

	rc = t.AddCont(str.c_str(),1);
	str.clear();
	rc = AddStrToVec(&t.cols, "");
	t.opts[0].push_back(0);

	if (row > -1)
	{
		rc = AddStrToVec(&t.cols, "WORD");
		t.opts[1].push_back(3);
		std::string str;
		str.append(str_);
		rc = AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
		t.opts[3].push_back(0);
		rc = AddStrToVec(&t.cols, "ID");
		t.opts[1].push_back(3);
		rc = AddStrToVec(&t.vals, ITOA(row).c_str());
	}
	else
	{
		rc = AddStrToVec(&t.cols, "WORD");
		t.opts[1].push_back(3);
		std::string str;
		str.append(str_);
		rc = AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
	}

	sint hdb = 0;
	sint odb = OpenDB(dbs.name.c_str(), 1, &hdb);

	if (odb > -1)
	{
		rc = BQS(&t);

		if (!rc)
		{
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
						if (debug_lvl >= 10 && debug_m)
						{
							cchar* output("SQLITE_OK");
							rc = Output(output, 2);
						}
						done = true;
						break;
					}
					case SQLITE_DONE:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							cchar* output("SQLITE_OK");
							rc = Output(output, 2);
						}
						done = true;
						break;
					}
					case SQLITE_ROW:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							cchar* output("SQLITE_OK");
							rc = Output(output, 2);
						}

						WORD_STRUCT Word;
						rc = FindColumn("ID", ppstmt);

						if (rc > -1)
						{
							Word.id = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("WORD", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								Word.word.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
							}
						}

						rc = FindColumn("LAST_USED_AS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);

									for (rc = 0; rc < (sint)PI.SymVec_->size(); rc++)
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.last_used_as.push_back(PI.SymVec_->at(rc).sym);
										}
									}
								}
							}
						}

						rc = FindColumn("USAGES", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);

									for (rc = 0; rc < (sint)PI.SymVec_->size(); rc++)
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.usages.push_back(PI.SymVec_->at(rc).sym);
										}
									}
								}
							}
						}

						rc = FindColumn("USED", ppstmt);

						if (rc > -1)
						{
							Word.used = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("FUNCTIONS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);

									for (rc = 0; rc < (sint)PI.SymVec_->size(); rc++)
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.functions.push_back(PI.SymVec_->at(rc).sym);
										}
									}
								}
							}
						}

						rc = FindColumn("LANGUAGES", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);

									for (rc = 0; rc < (sint)PI.SymVec_->size(); rc++)
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.languages.push_back(PI.SymVec_->at(rc).sym);
										}
									}
								}
							}
						}

						rc = FindColumn("ROOTWORDS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);

									for (rc = 0; rc < (sint)PI.SymVec_->size(); rc++)
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.rootwords.push_back(PI.SymVec_->at(rc).sym);
										}
									}
								}
							}
						}

						rc = FindColumn("NUMBER_EQUIV", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.number_equiv.push_back(atoi(PI.SymVec_->at(rc).sym.c_str()));
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("USED_AS_CODE", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.used_as_code.push_back(atoi(PI.SymVec_->at(rc).sym.c_str()));
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("INTERCHANGEABLES", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.interchangeables.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("CONJUNCTION_OF", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.conjunction_of.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("COMMON_PRECEEDING", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.common_preceeding.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("COMMON_FOLLOWING", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.common_following.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("HISTORY_PRECEEDING", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.history_preceeding.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("HISTORY_FOLLOWING", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.history_following.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("DEFINITIONS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.definitions.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("EXAMPLES", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.examples.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("ALT_LANG_EQUIVS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.alt_lang_equivs.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("PHOENETICS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string str;
								str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								std::vector<std::string> vec;
								uchar chr = ' ';
								rc = SeparateStrByChar(&str, &chr, &vec, 1);
								rc = 0;

								while (rc < (sint)vec.size())
								{
									Word.phoenetics.append(vec[rc]);
									Word.phoenetics.append(" ");
									rc++;
								}

								if (rc)
								{
									Word.phoenetics.pop_back();
								}
							}
						}

						rc = FindColumn("SYLLABLES", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string str;
								str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								std::vector<std::string> vec;
								uchar chr = ' ';
								rc = SeparateStrByChar(&str, &chr, &vec, 1);
								rc = 0;

								while (rc < (sint)vec.size())
								{
									Word.syllables.append(vec[rc]);
									Word.syllables.append(" ");
									rc++;
								}

								if (rc)
								{
									Word.syllables.pop_back();
								}
							}
						}

						rc = FindColumn("SYNTAX", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string str;
								str.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));
								std::vector<std::string> vec;
								uchar chr = ' ';
								rc = SeparateStrByChar(&str, &chr, &vec, 1);
								rc = 0;

								while (rc < (sint)vec.size())
								{
									Word.syntax.append(vec[rc]);
									Word.syntax.append(" ");
									rc++;
								}

								if (rc)
								{
									Word.syntax.pop_back();
								}
							}
						}

						rc = FindColumn("DUPLICATE", ppstmt);

						if (rc > -1)
						{
							Word.duplicate = (bool)sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("AS_NAME", ppstmt);

						if (rc > -1)
						{
							Word.as_name = (bool)sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("AS_TITLE", ppstmt);

						if (rc > -1)
						{
							Word.as_title = (bool)sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("PROFANITY", ppstmt);

						if (rc > -1)
						{
							Word.profanity = (bool)sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("AS_CODE", ppstmt);

						if (rc > -1)
						{
							Word.as_code = (bool)sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("LAST_USED_AS", ppstmt);

						if (rc > -1)
						{
							if (sqlite3_column_text(ppstmt, rc) != NULL)
							{
								std::string pstr;
								pstr.append(reinterpret_cast <cchar*> (sqlite3_column_text(ppstmt, rc)));

								if (!pstr.empty())
								{
									PINPUT_STRUCT PI;
									PI.istr_ = &pstr;
									std::string ol_str;
									PI.ol_str_ = &ol_str;
									std::vector<PARSS> symv;
									PI.SymVec_ = &symv;
									std::vector<MICSYM> msymv;
									PI.MSymVec_ = &msymv;
									std::vector<SYMBOL_STRUCT> altv;
									PI.AltSymsVec_ = &altv;
									rc = SeparateSymbolsI(&PI, 0, 0);
									rc = SeparateSymbolsIII(&PI, 1);
									rc = 0;

									while (rc < (sint)PI.SymVec_->size())
									{
										if (PI.SymVec_->at(rc).open > 0)
										{
											Word.last_used_as.push_back(PI.SymVec_->at(rc).sym);
										}
										rc++;
									}
								}
							}
						}

						rc = FindColumn("LAST_USED", ppstmt);

						if (rc > -1)
						{
							Word.last_used = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("LAST_MODIFIED", ppstmt);

						if (rc > -1)
						{
							Word.last_modified = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("LAST_MAINTAINED", ppstmt);

						if (rc > -1)
						{
							Word.last_maintained = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("LAST_MODIFIED_NS", ppstmt);

						if (rc > -1)
						{
							Word.last_modified_ns = sqlite3_column_int(ppstmt, rc);
						}

						rc = FindColumn("LAST_MAINTAINED_NS", ppstmt);

						if (rc > -1)
						{
							Word.last_maintained_ns = sqlite3_column_int(ppstmt, rc);
						}

						Words_->push_back(Word);
						break;
					}
					case SQLITE_BUSY:
					{
						if (debug_lvl >= 10 && debug_m)
						{
							rc = Output("SQLITE_BUSY", 2);
						}
						done = true;
						break;
					}
					default:
					{
						std::string output;
						rc = IGetError(&output, 0);
						rc = Output(output.c_str(), 1);

						if (debug_lvl >= 1 && debug_m)
						{
							rc = Output(output.c_str(), 2);
						}
						done = true;
						break;
					}
					}
				}

				rc = sqlite3_finalize(ppstmt);

				if (rc)
				{
					rc = Output(GetError().c_str(), 1);
				}
			}
			else
			{
				std::string output;
				rc = IGetError(&output, 0);
				rc = Output(output.c_str(), 2);
				rc = Output(output.c_str(), 1);
			}
		}
		if (!hdb)
		{
			odb = CloseDB(dbs.name.c_str());
		}
		if (Words_->empty())
		{
			if (debug_lvl >= 10 && debug_m)
			{
				rc = Output("found no word struct(s)", 2);
			}
		}
		return 0;
	}
	return -1;
}

void* machine::AddTheseWords(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	LITEBot.lid = (sint)vp;
	TINFO_M tts;
	sint x = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

	if (x < 0)
	{
		sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);
		pthread_exit((void*)x);

		if (!tts.opt)
		{
			pthread_detach(pthread_self());
		}
		return NULL;
	}

	LITEBot.ptn.append(tts.thread_name);
	x = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);

	if (LITEBot.debug_lvl >= 1 && &LITEBot.debug_m)
	{
		cchar* output("AddTheseWords( void * vp ) ");
		x = LITEBot.Output(output, 2);
	}
	
	//sllint lx = LITEBot.TestThreadTRat(&Info);
	std::vector<WORD_STRUCT> words;
	x = LITEBot.AddWords(&words);
	x = 1;
	rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);
	pthread_exit((void*)x);

	if (!tts.opt)
	{
		pthread_detach(pthread_self());
	}
	return NULL;
}

sint machine::AddWords(std::vector<WORD_STRUCT> *words_)
{
	if (debug_lvl >= 1 && debug_m)
	{
		carr_256 outp;
		sint op = BStrP(outp.carr, outp.siz, "AddWords(std::vector<WORD_STRUCT> *words_(%i))", (sint)words_->size());
		op = Output(outp.carr, 2);
	}

	if (words_->empty())
	{
		return 1;
	}

	sint x = 0;

	while (x < (sint)words_->size())
	{
		if (words_->at(x).id > -2)
		{
			if (words_->at(x).used < 1 && words_->at(x).ud_used)
			{
				words_->at(x).used = 1;
			}

			sint xc = x + 1;

			while (xc < (sint)words_->size())
			{
				if (!strcmp(words_->at(x).word.c_str(), words_->at(xc).word.c_str()) && (words_->at(x).id == words_->at(xc).id || words_->at(xc).id < 0))
				{
					words_->at(x).used++;

					if (!words_->at(xc).last_used_as.empty())
					{
						if (!words_->at(x).last_used_as.empty())
						{
							if (strcmp(words_->at(x).last_used_as[(sint)words_->at(x).last_used_as.size() - 1].c_str(), words_->at(xc).last_used_as[(sint)words_->at(xc).last_used_as.size() - 1].c_str()))
							{
								words_->at(x).last_used_as.push_back(words_->at(xc).last_used_as[(sint)words_->at(xc).last_used_as.size() - 1]);
							}
						}
						else
						{
							sint c = 0;

							while (c < (sint)words_->at(xc).last_used_as.size())
							{
								words_->at(x).last_used_as.push_back(words_->at(xc).last_used_as[c]);
								c++;
							}
						}
					}

					if (words_->at(xc).last_used > 0)
					{
						if (words_->at(x).last_used > 0)
						{
							if (words_->at(x).last_used < words_->at(xc).last_used)
							{
								words_->at(x).last_used = words_->at(xc).last_used;
							}
						}
						else
						{
							words_->at(x).last_used = words_->at(xc).last_used;
						}
					}

					if (!words_->at(xc).functions.empty())
					{
						sint cf = 0;

						while (cf < (sint)words_->at(xc).functions.size())
						{
							sint xf = (sint)words_->at(x).functions.size() - 1;

							while (xf > -1)
							{
								if (!strcmp(words_->at(x).functions[xf].c_str(), words_->at(xc).functions[cf].c_str()))
								{
									xf = -1;
								}
								xf--;
							}

							if (xf == -1)
							{
								words_->at(x).functions.push_back(words_->at(xc).functions[cf]);
							}
							cf++;
						}
					}

					if (!words_->at(xc).languages.empty())
					{
						sint cf = 0;

						while (cf < (sint)words_->at(xc).languages.size())
						{
							sint xf = (sint)words_->at(x).languages.size() - 1;

							while (xf > -1)
							{
								if (!strcmp(words_->at(x).languages[xf].c_str(), words_->at(xc).languages[cf].c_str()))
								{
									xf = -1;
								}
								xf--;
							}

							if (xf == -1)
							{
								words_->at(x).languages.push_back(words_->at(xc).languages[cf]);
							}
							cf++;
						}
					}

					if (!words_->at(xc).usages.empty())
					{
						sint cf = 0;

						while (cf < (sint)words_->at(xc).usages.size())
						{
							sint xf = (sint)words_->at(x).usages.size() - 1;

							while (xf > -1)
							{
								if (!strcmp(words_->at(x).usages[xf].c_str(), words_->at(xc).usages[cf].c_str()))
								{
									xf = -1;
								}
								xf--;
							}

							if (xf == -1)
							{
								words_->at(x).usages.push_back(words_->at(xc).usages[cf]);
							}
							cf++;
						}
					}
					words_->at(xc).id = -2;
				}
				xc++;
			}
		}
		x++;
	}

	x = 0;
	std::vector<BOT_STMT> tvec;

	while (x < (sint)words_->size())
	{
		if (words_->at(x).id > -2)
		{
			BOT_STMT t;

			if (words_->at(x).ud_last_maintained)
			{
				t.maint = true;
			}

			std::vector<WORD_STRUCT> rwords;
			cchar* nchr = "";

			if (!t.maint)
			{
				sint rc = GetWord(words_->at(x).word.c_str(), &rwords, 0, words_->at(x).id);

				if (rc)
				{
					std::string str, stri;
					stri.append(words_->at(x).word.substr(0, 1));
					str.append(Uppercase(stri.c_str()));
					BOT_DB dbs(str.c_str(), 3);
					rc = PushToDBList(&dbs);
					rc = GetVecEleByName((void*)&dbs, MTX_DBL, str.c_str(), false, false);
					rc = VerifyDatabase(&dbs);
				}
			}

			if (rwords.empty() && !t.maint)
			{
				t.it_type = 2;
				std::string str;
				str.push_back(words_->at(x).word[0]);
				sint rc = t.AddDB(str.c_str());

				if (words_->at(x).word.length() > 1)
				{
					str.push_back(words_->at(x).word[1]);
				}

				AddStrToVec(&t.tables, str.c_str());
				rc = t.AddCont(str.c_str(), 1);
				t.opts[0].push_back(2);
				AddStrToVec(&t.cols, "WORD");
				AddStrToVec(&t.vals, LEncStrI(&words_->at(x).word, -1).c_str());
				AddStrToVec(&t.cols, "USED");
				AddStrToVec(&t.vals, ITOA(words_->at(x).used).c_str());
				AddStrToVec(&t.cols, "LAST_USED_AS");
				str.clear();
				rc = 0;

				while (rc < (sint)words_->at(x).last_used_as.size())
				{
					str.append(LEncStrI(&words_->at(x).last_used_as[rc], -1));
					str.append(" ");
					rc++;
				}

				if (!str.empty())
				{
					str.pop_back();
				}

				AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
				str.clear();
				AddStrToVec(&t.cols, "USAGES");
				rc = 0;

				while (rc < (sint)words_->at(x).usages.size())
				{
					str.append(LEncStrI(&words_->at(x).usages[rc], -1));
					str.append(" ");
					rc++;
				}

				if (!str.empty())
				{
					str.pop_back();
				}

				AddStrToVec(&t.vals, str.c_str());
				str.clear();

				if (words_->at(x).id > 0)
				{
					AddStrToVec(&t.cols, "ID");
					AddStrToVec(&t.vals, ITOA(words_->at(x).id).c_str());
				}

				if (!t.tables.empty())
				{
					tvec.push_back(t);
				}
				t.Clear();
			}
			else
			{
				if (t.maint)
				{
					t.it_type = 1;
					std::string str;
					str.push_back(words_->at(x).word[0]);
					sint nc = t.AddDB(str.c_str());

					if (words_->at(x).word.length() > 1)
					{
						str.push_back(words_->at(x).word[1]);
					}
					nc = t.AddCont(str.c_str(), 1);
					t.opts[0].push_back(0);
					t.opts[9].push_back(0);

					if (words_->at(x).ud_assoc_img)
					{
						AddStrToVec(&t.cols, "ASSOC_IMG");
						AddStrToVec(&t.vals, LEncStrI(&words_->at(x).assoc_img, -1).c_str());
					}

					if (words_->at(x).ud_assoc_sound)
					{
						AddStrToVec(&t.cols, "ASSOC_SOUND");
						AddStrToVec(&t.vals, LEncStrI(&words_->at(x).assoc_sound, -1).c_str());
					}

					if (words_->at(x).ud_phoenetics)
					{
						AddStrToVec(&t.cols, "PHOENETICS");
						AddStrToVec(&t.vals, LEncStrI(&words_->at(x).phoenetics, -1).c_str());
					}

					if (words_->at(x).ud_syllables)
					{
						AddStrToVec(&t.cols, "SYLLABLES");
						AddStrToVec(&t.vals, LEncStrI(&words_->at(x).syllables, -1).c_str());
					}

					if (words_->at(x).ud_syntax)
					{
						AddStrToVec(&t.cols, "SYNTAX");
						AddStrToVec(&t.vals, LEncStrI(&words_->at(x).syntax, -1).c_str());
					}

					if (words_->at(x).ud_profanity)
					{
						AddStrToVec(&t.cols, "PROFANITY");
						AddStrToVec(&t.vals, ITOA((sint)words_->at(x).profanity).c_str());
					}

					if (words_->at(x).ud_duplicate)
					{
						AddStrToVec(&t.cols, "DUPLICATE");
						AddStrToVec(&t.vals, ITOA((sint)words_->at(x).duplicate).c_str());
					}

					if (words_->at(x).ud_as_name)
					{
						AddStrToVec(&t.cols, "AS_NAME");
						AddStrToVec(&t.vals, ITOA((sint)words_->at(x).as_name).c_str());
					}

					if (words_->at(x).ud_as_title)
					{
						AddStrToVec(&t.cols, "AS_TITLE");
						AddStrToVec(&t.vals, ITOA((sint)words_->at(x).as_title).c_str());
					}

					if (words_->at(x).ud_as_code)
					{
						AddStrToVec(&t.cols, "AS_CODE");
						AddStrToVec(&t.vals, ITOA((sint)words_->at(x).as_code).c_str());
					}

					if (words_->at(x).ud_last_used_as)
					{
						AddStrToVec(&t.cols, "LAST_USED_AS");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).last_used_as.size())
						{
							if (!words_->at(x).last_used_as[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).last_used_as[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_usages)
					{
						AddStrToVec(&t.cols, "USAGES");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).usages.size())
						{
							if (!words_->at(x).usages[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).usages[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_languages)
					{
						AddStrToVec(&t.cols, "LANGUAGES");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).languages.size())
						{
							if (!words_->at(x).languages[a].empty())
							{
								str.append(words_->at(x).languages[a]);
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_functions)
					{
						AddStrToVec(&t.cols, "FUNCTIONS");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).functions.size())
						{
							if (!words_->at(x).functions[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).functions[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_interchangeables)
					{
						AddStrToVec(&t.cols, "INTERCHANGEABLES");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).interchangeables.size())
						{
							if (!words_->at(x).interchangeables[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).interchangeables[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_synonyms)
					{
						AddStrToVec(&t.cols, "SYNONYMS");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).synonyms.size())
						{
							if (!words_->at(x).synonyms[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).synonyms[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_definitions)
					{
						AddStrToVec(&t.cols, "DEFINITIONS");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).definitions.size())
						{
							if (!words_->at(x).definitions[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).definitions[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_alt_lang_equivs)
					{
						AddStrToVec(&t.cols, "ALT_LANG_EQUIVS");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).alt_lang_equivs.size())
						{
							if (!words_->at(x).alt_lang_equivs[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).alt_lang_equivs[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_examples)
					{
						AddStrToVec(&t.cols, "EXAMPLES");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).examples.size())
						{
							if (!words_->at(x).examples[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).examples[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_rootwords)
					{
						AddStrToVec(&t.cols, "ROOTWORDS");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).rootwords.size())
						{
							if (!words_->at(x).rootwords[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).rootwords[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_conjunction_of)
					{
						AddStrToVec(&t.cols, "CONJUNCTION_OF");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).conjunction_of.size())
						{
							if (!words_->at(x).conjunction_of[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).conjunction_of[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_history_preceeding)
					{
						AddStrToVec(&t.cols, "HISTORY_PRECEEDING");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).history_preceeding.size())
						{
							if (!words_->at(x).history_preceeding[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).history_preceeding[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_history_following)
					{
						AddStrToVec(&t.cols, "HISTORY_FOLLOWING");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).history_following.size())
						{
							if (!words_->at(x).history_following[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).history_following[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_common_preceeding)
					{
						AddStrToVec(&t.cols, "COMMON_PRECEEDING");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).common_preceeding.size())
						{
							if (!words_->at(x).common_preceeding[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).common_preceeding[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_common_following)
					{
						AddStrToVec(&t.cols, "COMMON_FOLLOWING");
						std::string str;
						sint a = 0;

						while (a < (sint)words_->at(x).common_following.size())
						{
							if (!words_->at(x).common_following[a].empty())
							{
								str.append(LEncStrI(&words_->at(x).common_following[a], -1));
								str.append(" ");
							}
							a++;
						}

						if (!str.empty())
						{
							str.pop_back();
						}
						AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
					}

					if (words_->at(x).ud_id && words_->at(x).id > 0)
					{
						AddStrToVec(&t.cols, "ID");
						AddStrToVec(&t.vals, ITOA(words_->at(x).id).c_str());
					}

					if (words_->at(x).ud_used)
					{
						AddStrToVec(&t.cols, "USED");
						AddStrToVec(&t.vals, ITOA(words_->at(x).used).c_str());
					}

					if (words_->at(x).ud_last_used)
					{
						AddStrToVec(&t.cols, "LAST_USED");
						AddStrToVec(&t.vals, LLITOA(words_->at(x).last_used).c_str());
					}

					if (t.conds.size())
					{
						t.opts[3].push_back(0);
					}

					if (words_->at(x).id > -1)
					{
						carr_32 outp;
						sint op = BStrP(outp.carr, outp.siz, "ID = %i",words_->at(x).id);
						AddStrToVec(&t.conds, outp.carr);
					}
					else
					{
						carr_256 outp;
						sint op = BStrP(outp.carr, outp.siz, "WORD = %s", LEncStrI(&words_->at(x).word, -1).c_str());
						AddStrToVec(&t.conds, outp.carr);
					}
					tvec.push_back(t);
					t.Clear();
				}
				else
				{
					sint rc = 0;

					while (rc < (sint)rwords.size())
					{
						t.it_type = 1;
						std::string str;
						str.push_back(words_->at(x).word[0]);
						sint nc = t.AddDB(str.c_str());

						if (words_->at(x).word.length() > 1)
						{
							str.push_back(words_->at(x).word[1]);
						}
						nc = t.AddCont(str.c_str(),1);
						t.opts[0].push_back(0);
						t.opts[9].push_back(0);

						if (words_->at(x).ud_assoc_img)
						{
							AddStrToVec(&t.cols, "ASSOC_IMG");
							AddStrToVec(&t.vals, LEncStrI(&words_->at(x).assoc_img, -1).c_str());
						}

						if (words_->at(x).ud_assoc_sound)
						{
							AddStrToVec(&t.cols, "ASSOC_SOUND");
							AddStrToVec(&t.vals, LEncStrI(&words_->at(x).assoc_sound, -1).c_str());
						}

						if (words_->at(x).ud_phoenetics)
						{
							AddStrToVec(&t.cols, "PHOENETICS");
							AddStrToVec(&t.vals, LEncStrI(&words_->at(x).phoenetics, -1).c_str());
						}

						if (words_->at(x).ud_syllables)
						{
							AddStrToVec(&t.cols, "SYLLABLES");
							AddStrToVec(&t.vals, LEncStrI(&words_->at(x).syllables, -1).c_str());
						}

						if (words_->at(x).ud_syntax)
						{
							AddStrToVec(&t.cols, "SYNTAX");
							AddStrToVec(&t.vals, LEncStrI(&words_->at(x).syntax, -1).c_str());
						}

						if (words_->at(x).ud_profanity)
						{
							AddStrToVec(&t.cols, "PROFANITY");
							AddStrToVec(&t.vals, ITOA((sint)words_->at(x).profanity).c_str());
						}

						if (words_->at(x).ud_duplicate)
						{
							AddStrToVec(&t.cols, "DUPLICATE");
							AddStrToVec(&t.vals, ITOA((sint)words_->at(x).duplicate).c_str());
						}

						if (words_->at(x).ud_as_name)
						{
							AddStrToVec(&t.cols, "AS_NAME");
							AddStrToVec(&t.vals, ITOA((sint)words_->at(x).as_name).c_str());
						}

						if (words_->at(x).ud_as_title)
						{
							AddStrToVec(&t.cols, "AS_TITLE");
							AddStrToVec(&t.vals, ITOA((sint)words_->at(x).as_title).c_str());
						}

						if (words_->at(x).ud_as_code)
						{
							AddStrToVec(&t.cols, "AS_CODE");
							AddStrToVec(&t.vals, ITOA((sint)words_->at(x).as_code).c_str());
						}

						if (words_->at(x).ud_last_used_as)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).last_used_as.size())
							{
								rwords[rc].last_used_as.push_back(words_->at(x).last_used_as[a]);
								a++;
							}

							AddStrToVec(&t.cols, "LAST_USED_AS");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].last_used_as.size())
							{
								if (!rwords[rc].last_used_as[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].last_used_as[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_usages)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).usages.size())
							{
								sint b = (sint)rwords[rc].usages.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).usages[a].c_str(), rwords[rc].usages[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].usages.push_back(words_->at(x).usages[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "USAGES");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].usages.size())
							{
								if (!rwords[rc].usages[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].usages[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_languages)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).languages.size())
							{
								sint b = (sint)rwords[rc].languages.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).languages[a].c_str(), rwords[rc].languages[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].languages.push_back(words_->at(x).languages[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "LANGUAGES");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].languages.size())
							{
								if (!rwords[rc].languages[a].empty())
								{
									str.append(rwords[rc].languages[a]);
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_functions)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).functions.size())
							{
								sint b = (sint)rwords[rc].functions.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).functions[a].c_str(), rwords[rc].functions[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].functions.push_back(words_->at(x).functions[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "FUNCTIONS");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].functions.size())
							{
								if (!rwords[rc].functions[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].functions[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_interchangeables)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).interchangeables.size())
							{
								sint b = (sint)rwords[rc].interchangeables.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).interchangeables[a].c_str(), rwords[rc].interchangeables[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].interchangeables.push_back(words_->at(x).interchangeables[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "INTERCHANGEABLES");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].interchangeables.size())
							{
								if (!rwords[rc].interchangeables[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].interchangeables[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_synonyms)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).synonyms.size())
							{
								sint b = (sint)rwords[rc].synonyms.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).synonyms[a].c_str(), rwords[rc].synonyms[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].synonyms.push_back(words_->at(x).synonyms[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "SYNONYMS");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].synonyms.size())
							{
								if (!rwords[rc].synonyms[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].synonyms[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_definitions)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).definitions.size())
							{
								sint b = (sint)rwords[rc].definitions.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).definitions[a].c_str(), rwords[rc].definitions[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].definitions.push_back(words_->at(x).definitions[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "DEFINITIONS");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].definitions.size())
							{
								if (!rwords[rc].definitions[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].definitions[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_alt_lang_equivs)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).alt_lang_equivs.size())
							{
								sint b = (sint)rwords[rc].alt_lang_equivs.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).alt_lang_equivs[a].c_str(), rwords[rc].alt_lang_equivs[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].alt_lang_equivs.push_back(words_->at(x).alt_lang_equivs[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "ALT_LANG_EQUIVS");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].alt_lang_equivs.size())
							{
								if (!rwords[rc].alt_lang_equivs[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].alt_lang_equivs[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_examples)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).examples.size())
							{
								sint b = (sint)rwords[rc].examples.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).examples[a].c_str(), rwords[rc].examples[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].examples.push_back(words_->at(x).examples[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "EXAMPLES");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].examples.size())
							{
								if (!rwords[rc].examples[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].examples[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_rootwords)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).rootwords.size())
							{
								sint b = (sint)rwords[rc].rootwords.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).rootwords[a].c_str(), rwords[rc].rootwords[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].rootwords.push_back(words_->at(x).rootwords[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "ROOTWORDS");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].rootwords.size())
							{
								if (!rwords[rc].rootwords[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].rootwords[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_conjunction_of)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).conjunction_of.size())
							{
								sint b = (sint)rwords[rc].conjunction_of.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).conjunction_of[a].c_str(), rwords[rc].conjunction_of[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].conjunction_of.push_back(words_->at(x).conjunction_of[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "CONJUNCTION_OF");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].conjunction_of.size())
							{
								if (!rwords[rc].conjunction_of[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].conjunction_of[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_history_preceeding)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).history_preceeding.size())
							{
								sint b = (sint)rwords[rc].history_preceeding.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).history_preceeding[a].c_str(), rwords[rc].history_preceeding[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].history_preceeding.push_back(words_->at(x).history_preceeding[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "HISTORY_PRECEEDING");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].history_preceeding.size())
							{
								if (!rwords[rc].history_preceeding[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].history_preceeding[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_history_following)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).history_following.size())
							{
								sint b = (sint)rwords[rc].history_following.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).history_following[a].c_str(), rwords[rc].history_following[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].history_following.push_back(words_->at(x).history_following[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "HISTORY_FOLLOWING");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].history_following.size())
							{
								if (!rwords[rc].history_following[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].history_following[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}
							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_common_preceeding)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).common_preceeding.size())
							{
								sint b = (sint)rwords[rc].common_preceeding.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).common_preceeding[a].c_str(), rwords[rc].common_preceeding[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].common_preceeding.push_back(words_->at(x).common_preceeding[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "COMMON_PRECEEDING");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].common_preceeding.size())
							{
								if (!rwords[rc].common_preceeding[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].common_preceeding[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_common_following)
						{
							sint a = 0;

							while (a < (sint)words_->at(x).common_following.size())
							{
								sint b = (sint)rwords[rc].common_following.size() - 1;

								while (b > -1)
								{
									if (!strcmp(words_->at(x).common_following[a].c_str(), rwords[rc].common_following[b].c_str()))
									{
										b = -1;
									}
									b--;
								}

								if (b == -1)
								{
									rwords[rc].common_following.push_back(words_->at(x).common_following[a]);
								}
								a++;
							}

							AddStrToVec(&t.cols, "COMMON_FOLLOWING");
							std::string str;
							a = 0;

							while (a < (sint)rwords[rc].common_following.size())
							{
								if (!rwords[rc].common_following[a].empty())
								{
									str.append(LEncStrI(&rwords[rc].common_following[a], -1));
									str.append(" ");
								}
								a++;
							}

							if (!str.empty())
							{
								str.pop_back();
							}

							AddStrToVec(&t.vals, LEncStrI(&str, -1).c_str());
						}

						if (words_->at(x).ud_id && words_->at(x).id == rwords[rc].id && words_->at(x).id > 0)
						{
							AddStrToVec(&t.cols, "ID");
							AddStrToVec(&t.vals, ITOA(words_->at(x).id).c_str());
						}

						if (words_->at(x).ud_used)
						{
							rwords[rc].used += words_->at(x).used + 1;
						}

						if (words_->at(x).id == rwords[rc].id)
						{
							AddStrToVec(&t.cols, "LAST_USED");
							AddStrToVec(&t.vals, LLITOA(words_->at(x).last_used).c_str());
							AddStrToVec(&t.cols, "USED");
							AddStrToVec(&t.vals, LLITOA(rwords[rc].used).c_str());

							if (t.conds.size())
							{
								t.opts[3].push_back(1);
							}
							std::string condstr;
							condstr.append("ID = ");
							condstr.append(ITOA(rwords[rc].id));
							AddStrToVec(&t.conds, condstr.c_str());
						}
						else
						{
							if (rwords.size() == 1)
							{
								AddStrToVec(&t.cols, "LAST_USED");
								AddStrToVec(&t.vals, LLITOA(words_->at(x).last_used).c_str());
								AddStrToVec(&t.cols, "USED");
								AddStrToVec(&t.vals, ITOA(rwords[rc].used).c_str());
							}

							if (t.conds.size())
							{
								t.opts[3].push_back(1);
							}
							std::string condstr;
							condstr.append("WORD = ");
							condstr.append(LEncStrI(&rwords[rc].word, -1));
							AddStrToVec(&t.conds, condstr.c_str());
						}
						tvec.push_back(t);
						t.Clear();
						rc++;
					}
				}
			}
		}
		x++;
	}
	x = Commit(&tvec);
	return x;
}

void* machine::DBMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint x = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

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

	LITEBot.ptn.append(tts.thread_name);
	x = 0;
	sint rc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&x, false);

	if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
	{
		carr_256 outc;
		x = LITEBot.BStrP(outc.carr, outc.siz, "::DBMaintenance(void *vp(%i))", LITEBot.lid);
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
	
		x = LITEBot.Rest(1000);
		z = -1;
		x = LITEBot.GetVecEleMem(&z, MTX_TTSV, LITEBot.lid, BOT_TTS_FIN);

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
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint rc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

	if (rc<0)
	{
		sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
		pthread_exit((void *)rc);
		return NULL;
	}

	LITEBot.ptn.append(tts.thread_name);
	rc = 0;
	sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	BOT_DB dbs;
	xc = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "litebot", false, false);

	if (dbs.type)
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			carr_256 outp;
			sint op = LITEBot.BStrP(outp.carr, outp.siz, "LITEBotMaintenance attempted on database:%s", dbs.name.c_str());
			op = LITEBot.Output(outp.carr, 2);
		}
	}
	else
	{
		if (LITEBot.debug_lvl >= 5 && LITEBot.debug_m)
		{
			carr_256 outc;
			sint op = LITEBot.BStrP(outc.carr, outc.siz, "::LITEBotMaintenance(void *vp(%i))", LITEBot.lid);
			op = LITEBot.Output(outc.carr, 2);

			if (LITEBot.debug_lvl >= 10 && LITEBot.debug_m)
			{
				carr_256 outp;
				op = LITEBot.BStrP(outp.carr, outp.siz, "for database:%s",dbs.name.c_str());
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
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint rc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

	if (rc<0)
	{
		sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
		pthread_exit((void *)rc);
		return NULL;
	}

	LITEBot.ptn.append(tts.thread_name);
	rc = 0;
	sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	BOT_DB dbs;
	rc = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "code", false, false);

	if (dbs.type != 2)
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			carr_256 outp;
			sint op = LITEBot.BStrP(outp.carr, outp.siz, "CodeMaintenance attempted on:%s",dbs.name.c_str());
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
				op = LITEBot.BStrP(outp.carr, outp.siz, "for database:%s", dbs.name.c_str());
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

void* machine::WordMaintenance(void * vp)
{
	sint nlid = (sint)vp;
	machine LITEBot(BOT_DEBUG_LVL, BOT_DEBUG_M, nlid);
	TINFO_M tts;
	sint rc = LITEBot.GetVecEle((void*)&tts, MTX_TTSV, LITEBot.lid);

	if (!rc)
	{
		sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
		pthread_exit((void *)rc);
		return NULL;
	}

	LITEBot.ptn.append(tts.thread_name);
	rc = 0;
	sint xc = LITEBot.SetTTSVEleM(LITEBot.lid, BOT_TTS_FIN, (void*)&rc, false);
	BOT_DB dbs;
	xc = LITEBot.GetVecEleByName((void*)&dbs, MTX_DBL, "-word-", false, false);

	if (dbs.type != 3)
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			carr_256 outp;
			sint op = LITEBot.BStrP(outp.carr, outp.siz, "WordMaintenance attempted on %s", dbs.name.c_str());
			op = LITEBot.Output(outp.carr, 2);
		}
	}
	else
	{
		if (LITEBot.debug_lvl >= 1 && LITEBot.debug_m)
		{
			sint op = LITEBot.Output("::WordMaintenance(void * vp)", 2);

			if (LITEBot.debug_lvl >= 10 && LITEBot.debug_m)
			{
				carr_256 outp;
				op = LITEBot.BStrP(outp.carr, outp.siz, "for database:%s", dbs.name.c_str());
				op = LITEBot.Output(outp.carr, 2);
			}
		}

		//sllint lc = LITEBot.TestThreadTRat(&Info);
		sint hdb = 0;
		sint odb = LITEBot.OpenDB(dbs.name.c_str(), 2, &hdb);

		if (odb < 0)
		{
			//odb = LITEBot.VerifyDatabases();
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

			if ((last_maint == last_modi && last_maint_ns > last_modi_ns) || last_modi < last_maint)
			{
				rc = 0;
			}
			else
			{
				std::vector<WORD_STRUCT> rwords;
				sint ct = 0;
				sint i = (sint)dbs.tables.size() - 1;

				while (i > 0)
				{
					xc = LITEBot.GetWord("", &rwords, "LAST_MODIFIED > LAST_MAINTAINED OR LAST_MODIFIED = LAST_MAINTAINED AND LAST_MODIFIED_NS > LAST_MAINTAINED_NS", -1);

					if (!rwords.empty())
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

						if (!strcmp("LAST_ACCESS", dbs.tables[i].c_str()))
						{

						}
						else
						{
							sint x = ct;

							while (x < (sint)rwords.size())
							{
								rwords[x].ud_last_maintained = true;

								if (!rwords[x].last_used_as.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].last_used_as.size())
									{
										if (!rwords[x].last_used_as[xc].empty())
										{
											PINPUT_STRUCT PI;
											PI.istr_ = &rwords[x].last_used_as[xc];
											std::string ol_str;
											PI.ol_str_ = &ol_str;
											std::vector<PARSS> symv;
											PI.SymVec_ = &symv;
											std::vector<MICSYM> msymv;
											PI.MSymVec_ = &msymv;
											std::vector<SYMBOL_STRUCT> altv;
											PI.AltSymsVec_ = &altv;
											sint zc = LITEBot.SeparateSymbolsI(&PI, 0, 0);
											zc = LITEBot.SeparateSymbolsIII(&PI, 1);
											zc = 0;

											while (zc < (sint)PI.SymVec_->size())
											{
												if (PI.SymVec_->at(zc).sym.length() == rwords[x].word.length())
												{
													if (!strcmp(PI.SymVec_->at(zc).sym.c_str(), rwords[x].word.c_str()))
													{
														sint yc = zc - 1;

														while (yc > -1)
														{
															sint uc = (sint)PI.SymVec_->at(yc).usages.size() - 1;

															while (uc > -1)
															{
																if (PI.SymVec_->at(yc).usages[uc] == 2 || PI.SymVec_->at(yc).usages[uc] == 1)
																{
																	while (yc < xc)
																	{
																		rwords[x].history_preceeding.push_back(PI.SymVec_->at(yc).sym);
																		yc++;
																	}
																	uc = -1;
																	yc = -1;
																}
																uc--;
															}
															yc--;
														}

														if (yc == -1)
														{
															yc = 0;

															while (yc < zc)
															{
																rwords[x].history_preceeding.push_back(PI.SymVec_->at(yc).sym);
																yc++;
															}
														}

														yc = zc + 1;

														while (yc < (sint)PI.SymVec_->size())
														{
															sint uc = (sint)PI.SymVec_->at(yc).usages.size() - 1;

															while (uc > -1)
															{
																if (PI.SymVec_->at(yc).usages[uc] == 2 || PI.SymVec_->at(yc).usages[uc] == 1)
																{
																	yc = zc + 1;

																	while (yc < zc)
																	{
																		rwords[x].history_following.push_back(PI.SymVec_->at(yc).sym);
																		yc++;
																	}
																	uc = -1;
																	yc = (sint)PI.SymVec_->size();
																}
																uc--;
															}
															yc++;
														}

														if (yc == (sint)PI.SymVec_->size())
														{
															yc = zc + 1;

															while (yc < (sint)PI.SymVec_->size())
															{
																rwords[x].history_following.push_back(PI.SymVec_->at(yc).sym);
																yc++;
															}
														}
													}
												}
												zc++;
											}
										}
										xc++;
									}

									rwords[x].last_used_as.clear();
									rwords[x].ud_last_used_as = true;
								}

								if (!rwords[x].history_preceeding.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].history_preceeding.size())
									{
										if (!rwords[x].history_preceeding[xc].empty())
										{
											PINPUT_STRUCT PI;
											PI.istr_ = &rwords[x].history_preceeding[xc];
											std::string ol_str;
											PI.ol_str_ = &ol_str;
											std::vector<PARSS> symv;
											PI.SymVec_ = &symv;
											std::vector<MICSYM> msymv;
											PI.MSymVec_ = &msymv;
											std::vector<SYMBOL_STRUCT> altv;
											PI.AltSymsVec_ = &altv;
											sint zc = LITEBot.SeparateSymbolsI(&PI, 0, 0);
											zc = LITEBot.SeparateSymbolsIII(&PI, 1);
											zc = 0;

											while (zc < (sint)PI.SymVec_->size())
											{
												sint uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

												while (uc > -1)
												{
													if (PI.SymVec_->at(zc).usages[uc] == 3)
													{
														while (zc > -1)
														{
															uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

															while (uc > -1)
															{
																if (PI.SymVec_->at(zc).usages[uc] == 3)
																{
																	uc = -1;
																}
																uc--;
															}

															if (uc == -1)
															{
																std::string N, S;
																sint yc = zc + 1;

																while (yc < (sint)PI.SymVec_->size())
																{
																	N.append(PI.SymVec_->at(yc).sym);
																	yc++;
																}
																yc = zc;

																while (zc > -1)
																{
																	uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

																	while (uc > -1)
																	{
																		if (!PI.SymVec_->at(zc).usages[uc])
																		{
																			uc = -1;
																		}
																		uc--;
																	}

																	if (uc == -1)
																	{
																		uc = 0;
																		yc = 0;

																		while (yc <= zc)
																		{
																			S.append(PI.SymVec_->at(yc).sym);
																			yc++;
																		}

																		yc = 0;

																		while (yc < (sint)rwords[x].history_preceeding.size())
																		{
																			if (!strcmp(S.c_str(), rwords[x].history_preceeding[yc].c_str()))
																			{
																				uc = atoi(N.c_str()) + uc;
																				N.clear();
																				N.append(LITEBot.ITOA(uc));

																				if (uc > 10000)
																				{
																					S.append(" ");
																					S.append(N);
																					rwords[x].common_preceeding.push_back(S);
																				}

																				rwords[x].history_preceeding[yc].clear();
																			}
																			yc++;
																		}
																		zc = -1;
																	}
																	zc--;
																}
																zc = -1;
															}
															zc--;
														}
														uc = -1;
													}
													uc--;
												}
												zc++;
											}
										}
										xc++;
									}

									xc = 0;

									while (xc < (sint)rwords[x].history_preceeding.size())
									{
										if (!rwords[x].history_preceeding[xc].empty())
										{
											rwords[x].history_preceeding[xc].append(" 1");
										}

										xc++;
									}

									rwords[x].ud_history_preceeding = true;
								}

								if (!rwords[x].history_following.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].history_following.size())
									{
										if (!rwords[x].history_following[xc].empty())
										{
											PINPUT_STRUCT PI;
											PI.istr_ = &rwords[x].history_following[xc];
											std::string ol_str;
											PI.ol_str_ = &ol_str;
											std::vector<PARSS> symv;
											PI.SymVec_ = &symv;
											std::vector<MICSYM> msymv;
											PI.MSymVec_ = &msymv;
											std::vector<SYMBOL_STRUCT> altv;
											PI.AltSymsVec_ = &altv;
											sint zc = LITEBot.SeparateSymbolsI(&PI, 0, 0);
											zc = LITEBot.SeparateSymbolsIII(&PI, 1);
											zc = 0;

											while (zc < (sint)PI.SymVec_->size())
											{
												sint uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

												while (uc > -1)
												{
													if (PI.SymVec_->at(zc).usages[uc] == 3)
													{
														while (zc > -1)
														{
															uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

															while (uc > -1)
															{
																if (PI.SymVec_->at(zc).usages[uc] == 3)
																{
																	uc = -1;
																}
																uc--;
															}

															if (uc == -1)
															{
																std::string N, S;
																sint yc = zc + 1;

																while (yc < (sint)PI.SymVec_->size())
																{
																	N.append(PI.SymVec_->at(yc).sym);
																	yc++;
																}

																yc = zc;

																while (zc > -1)
																{
																	uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

																	while (uc > -1)
																	{
																		if (!PI.SymVec_->at(zc).usages[uc])
																		{
																			uc = -1;
																		}
																		uc--;
																	}

																	if (uc == -1)
																	{
																		uc = 0;
																		yc = 0;

																		while (yc <= zc)
																		{
																			S.append(PI.SymVec_->at(yc).sym);
																			yc++;
																		}

																		yc = 0;

																		while (yc < (sint)rwords[x].history_following.size())
																		{
																			if (!strcmp(S.c_str(), rwords[x].history_following[yc].c_str()))
																			{
																				uc = atoi(N.c_str()) + uc;
																				N.clear();
																				N.append(LITEBot.ITOA(uc));

																				if (uc > 10000)
																				{
																					S.append(" ");
																					S.append(N);
																					rwords[x].common_following.push_back(S);
																				}

																				rwords[x].history_following[yc].clear();
																			}
																			yc++;
																		}
																		zc = -1;
																	}
																	zc--;
																}
																zc = -1;
															}
															zc--;
														}
														uc = -1;
													}
													uc--;
												}
												zc++;
											}
										}
										xc++;
									}

									xc = 0;

									while (xc < (sint)rwords[x].history_following.size())
									{
										if (!rwords[x].history_following[xc].empty())
										{
											rwords[x].history_following[xc].append(" 1");
										}

										xc++;
									}

									rwords[x].ud_history_following = true;
								}

								if (!rwords[x].common_preceeding.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].common_preceeding.size())
									{
										if (!rwords[x].common_preceeding[xc].empty())
										{
											PINPUT_STRUCT PI;
											PI.istr_ = &rwords[x].common_preceeding[xc];
											std::string ol_str;
											PI.ol_str_ = &ol_str;
											std::vector<PARSS> symv;
											PI.SymVec_ = &symv;
											std::vector<MICSYM> msymv;
											PI.MSymVec_ = &msymv;
											std::vector<SYMBOL_STRUCT> altv;
											PI.AltSymsVec_ = &altv;
											sint zc = LITEBot.SeparateSymbolsI(&PI, 0, 0);
											zc = LITEBot.SeparateSymbolsIII(&PI, 1);
											zc = 0;

											while (zc < (sint)PI.SymVec_->size())
											{
												sint uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

												while (uc > -1)
												{
													if (PI.SymVec_->at(zc).usages[uc] == 3)
													{
														while (zc > -1)
														{
															uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

															while (uc > -1)
															{
																if (PI.SymVec_->at(zc).usages[uc] == 3)
																{
																	uc = -1;
																}
																uc--;
															}

															if (uc == -1)
															{
																std::string N, S;
																sint yc = zc + 1;

																while (yc < (sint)PI.SymVec_->size())
																{
																	N.append(PI.SymVec_->at(yc).sym);
																	yc++;
																}

																yc = zc;

																while (zc > -1)
																{
																	uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

																	while (uc > -1)
																	{
																		if (!PI.SymVec_->at(zc).usages[uc])
																		{
																			uc = -1;
																		}
																		uc--;
																	}

																	if (uc == -1)
																	{
																		uc = 0;
																		yc = 0;

																		while (yc <= zc)
																		{
																			S.append(PI.SymVec_->at(yc).sym);
																			yc++;
																		}

																		yc = 0;

																		while (yc < (sint)rwords[x].common_preceeding.size())
																		{
																			if (!strcmp(S.c_str(), rwords[x].common_preceeding[yc].c_str()))
																			{
																				uc = atoi(N.c_str()) + uc;
																				N.clear();
																				N.append(LITEBot.ITOA(uc));
																				rwords[x].common_preceeding[yc].clear();
																			}

																			yc++;
																		}
																		zc = -1;
																	}
																	zc--;
																}
																zc = -1;
															}
															zc--;
														}
														uc = -1;
													}
													uc--;
												}
												zc++;
											}
										}
										xc++;
									}

									xc = 0;

									while (xc < (sint)rwords[x].common_preceeding.size())
									{
										if (!rwords[x].common_preceeding[xc].empty())
										{
											rwords[x].common_preceeding[xc].append(" 1");
										}
										xc++;
									}

									rwords[x].ud_common_preceeding = true;
								}

								if (!rwords[x].common_following.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].common_following.size())
									{
										if (!rwords[x].common_following[xc].empty())
										{
											PINPUT_STRUCT PI;
											PI.istr_ = &rwords[x].common_following[xc];
											std::string ol_str;
											PI.ol_str_ = &ol_str;
											std::vector<PARSS> symv;
											PI.SymVec_ = &symv;
											std::vector<MICSYM> msymv;
											PI.MSymVec_ = &msymv;
											std::vector<SYMBOL_STRUCT> altv;
											PI.AltSymsVec_ = &altv;
											sint zc = LITEBot.SeparateSymbolsI(&PI, 0, 0);
											zc = LITEBot.SeparateSymbolsIII(&PI, 1);
											zc = 0;

											while (zc < (sint)PI.SymVec_->size())
											{
												sint uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

												while (uc > -1)
												{
													if (PI.SymVec_->at(zc).usages[uc] == 3)
													{
														while (zc > -1)
														{
															uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

															while (uc > -1)
															{
																if (PI.SymVec_->at(zc).usages[uc] == 3)
																{
																	uc = -1;
																}
																uc--;
															}

															if (uc == -1)
															{
																std::string N, S;
																sint yc = zc + 1;

																while (yc < (sint)PI.SymVec_->size())
																{
																	N.append(PI.SymVec_->at(yc).sym);
																	yc++;
																}

																yc = zc;

																while (zc > -1)
																{
																	uc = (sint)PI.SymVec_->at(zc).usages.size() - 1;

																	while (uc > -1)
																	{
																		if (!PI.SymVec_->at(zc).usages[uc])
																		{
																			uc = -1;
																		}
																		uc--;
																	}

																	if (uc == -1)
																	{
																		uc = 0;
																		yc = 0;

																		while (yc <= zc)
																		{
																			S.append(PI.SymVec_->at(yc).sym);
																			yc++;
																		}

																		yc = 0;

																		while (yc < (sint)rwords[x].common_following.size())
																		{
																			if (!strcmp(S.c_str(), rwords[x].common_following[yc].c_str()))
																			{
																				uc = atoi(N.c_str()) + uc;
																				N.clear();
																				N.append(LITEBot.ITOA(uc));
																				rwords[x].common_following[yc].clear();
																			}
																			yc++;
																		}

																		zc = -1;
																	}
																	zc--;
																}
																zc = -1;
															}
															zc--;
														}
														uc = -1;
													}
													uc--;
												}
												zc++;
											}
										}
										xc++;
									}

									xc = 0;

									while (xc < (sint)rwords[x].common_following.size())
									{
										if (!rwords[x].common_following[xc].empty())
										{
											rwords[x].common_following[xc].append(" 1");
										}
										xc++;
									}

									rwords[x].ud_common_following = true;
								}

								if (!rwords[x].usages.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].usages.size())
									{
										sint yc = (sint)rwords[x].usages.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].usages[xc].c_str(), rwords[x].usages[yc].c_str()))
											{
												rwords[x].usages[yc].clear();
												rwords[x].ud_usages = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].languages.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].languages.size())
									{
										sint yc = (sint)rwords[x].languages.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].languages[xc].c_str(), rwords[x].languages[yc].c_str()))
											{
												rwords[x].languages[yc].clear();
												rwords[x].ud_languages = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].functions.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].functions.size())
									{
										sint yc = (sint)rwords[x].functions.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].functions[xc].c_str(), rwords[x].functions[yc].c_str()))
											{
												rwords[x].functions[yc].clear();
												rwords[x].ud_functions = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].rootwords.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].rootwords.size())
									{
										sint yc = (sint)rwords[x].rootwords.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].rootwords[xc].c_str(), rwords[x].rootwords[yc].c_str()))
											{
												rwords[x].rootwords[yc].clear();
												rwords[x].ud_rootwords = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].interchangeables.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].interchangeables.size())
									{
										sint yc = (sint)rwords[x].interchangeables.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].interchangeables[xc].c_str(), rwords[x].interchangeables[yc].c_str()))
											{
												rwords[x].interchangeables[yc].clear();
												rwords[x].ud_interchangeables = true;
											}
											yc--;
										}

										xc++;
									}
								}

								if (!rwords[x].definitions.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].definitions.size())
									{
										sint yc = (sint)rwords[x].definitions.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].definitions[xc].c_str(), rwords[x].definitions[yc].c_str()))
											{
												rwords[x].definitions[yc].clear();
												rwords[x].ud_definitions = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].examples.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].examples.size())
									{
										sint yc = (sint)rwords[x].examples.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].examples[xc].c_str(), rwords[x].examples[yc].c_str()))
											{
												rwords[x].examples[yc].clear();
												rwords[x].ud_examples = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].alt_lang_equivs.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].alt_lang_equivs.size())
									{
										sint yc = (sint)rwords[x].alt_lang_equivs.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].alt_lang_equivs[xc].c_str(), rwords[x].alt_lang_equivs[yc].c_str()))
											{
												rwords[x].alt_lang_equivs[yc].clear();
												rwords[x].ud_alt_lang_equivs = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].synonyms.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].synonyms.size())
									{
										sint yc = (sint)rwords[x].synonyms.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].synonyms[xc].c_str(), rwords[x].synonyms[yc].c_str()))
											{
												rwords[x].synonyms[yc].clear();
												rwords[x].ud_synonyms = true;
											}
											yc--;
										}
										xc++;
									}
								}

								if (!rwords[x].conjunction_of.empty())
								{
									xc = 0;

									while (xc < (sint)rwords[x].conjunction_of.size())
									{
										sint yc = (sint)rwords[x].conjunction_of.size() - 1;

										while (yc > xc)
										{
											if (!strcmp(rwords[x].conjunction_of[xc].c_str(), rwords[x].conjunction_of[yc].c_str()))
											{
												rwords[x].conjunction_of[yc].clear();
												rwords[x].ud_conjunction_of = true;
											}
											yc--;
										}
										xc++;
									}
								}
								x++;
							}
							ct = x;
						}
					}
					i--;
				}

				if (!rwords.empty())
				{
					rc = LITEBot.AddWords(&rwords);
				}
				else
				{
					BOT_STMT t(true,1);
					t.AddDB(dbs.name.c_str());
					t.AddCont("LAST_ACCESS", 1);
					std::vector<BOT_STMT> tvec;
					tvec.push_back(t);
					rc = LITEBot.Commit(&tvec);
				}
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