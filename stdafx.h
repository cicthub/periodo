// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "gmp.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <fstream>
//#include <afxwin.h>// MFC
//#include <gdiplus.h>//GDI
//#include <unordered_map>

#include "QRList.h"

//#include "mpfr.h"
//#include "sqlite3.h"
//#include "rand_sse.h"


#pragma region Prototypes

void ProcessParameters(int argc, char* argv[]);
void ComputeDivision(mpz_t numerator, mpz_t denominator, mpz_t antiPeriod, bool printPartial, int imageSize, bool log, mpz_t period);
int	Test_presenza_AP(mpz_t d, mpz_t ap);
void gmp_power(mpz_t risultato, mpz_t base, mpz_t exp);
void QRListTest();

#pragma endregion


//globals
mpz_t numerator;
mpz_t denominator;
int imageSize = 0;
bool logDivision = false;
bool partial = false;
bool updateNumberDB = false;
bool wantExit = false;
bool knowledgeBase = false;
mpz_t matrixRows;
mpz_t matrixColumns;

