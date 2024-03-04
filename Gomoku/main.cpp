
int  main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	Gomoku myGomoku;
	myGomoku.GameRun();

	return 0;

}
