// Periodo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gmp.h"
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>
//#include "gmp.h"
//#include "mpfr.h"
#include "QRList.h"
#include <time.h>
#include <stdint.h>
//#include <unordered_map>
#include <fstream>
#include <math.h>
#include <string.h>
//#include <afxwin.h>// MFC
//#include <gdiplus.h>//GDI
//#include "sqlite3.h"
#include <windows.h>
//#include "rand_sse.h"




using namespace std;

#pragma region Prototypes

void ProcessParameters(int argc, char* argv[]);
void ComputeDivision(mpz_t numerator, mpz_t denominator, mpz_t antiPeriod, bool printPartial, int imageSize, bool log, mpz_t period);
int	Test_presenza_AP(mpz_t d, mpz_t ap);
void gmp_power(mpz_t risultato, mpz_t base, mpz_t exp);

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

int _tmain(int argc, char* argv[])
{
	time_t start, stop;
	mpz_t antiPeriod;
	mpz_init(antiPeriod);
	mpz_set_d(antiPeriod,0);
	mpz_init(matrixColumns); mpz_set_d(matrixColumns, -1);
	mpz_init(matrixRows); mpz_set_d(matrixRows, -1);

	// Process parameters
	ProcessParameters(argc, argv);
	// Log Start
	time(&start);
	cout << ctime(&start) << endl;

	mpz_t periodLength;
	mpz_init(periodLength);
	// verify anti-period
	bool multiple = Test_presenza_AP(denominator, antiPeriod);
	// compute calculation and log on file
	ComputeDivision(numerator, denominator, antiPeriod, partial, imageSize, logDivision, periodLength);

	system("PAUSE");
	//return 0;
}
void ComputeDivision(mpz_t numerator, mpz_t denominator, mpz_t antiPeriod, bool printPartial, int imageSize, bool log, mpz_t periodLength)
{
	bool foundPeriod = false;
//	char line[1024];

	mpz_t r, r0, q, n, d, cycle, copyAntiPeriod, columnCounter;

	mpz_init(r); mpz_init(r0); mpz_init(q);	mpz_init(n); mpz_init(d); mpz_set(n, numerator); mpz_set(d, denominator); mpz_set_d(periodLength, 0); mpz_init(cycle); mpz_set_d(cycle, 0);
	mpz_init(columnCounter); mpz_set_d(columnCounter, 1);
	mpz_init(copyAntiPeriod); mpz_set(copyAntiPeriod, antiPeriod);
	QRList qrList(1000);


	// Anti period present
	if (mpz_cmp_d(copyAntiPeriod, 0) != 0)
	{
		mpz_tdiv_qr(q, r, n, d);
		while (mpz_cmp_d(copyAntiPeriod, 0) != 0)
		{
			mpz_mul_si(r, r, 10);
			mpz_set(n, r);
			mpz_tdiv_qr(q, r, n, d);

			//Write division result
			if (updateNumberDB == false && imageSize == NULL && logDivision)
			{
				//if (knowledgeBase)
				//{
				//	if (mpz_cmp_d(matrixColumns, -1) != 0) // matrix format set...
				//	{
				//		//print the reminder
				//		if (mpz_cmp(matrixColumns, columnCounter) == 0)
				//		{
				//			gmp_sprintf(line, "%Zd\n", r);
				//			mpz_set_d(columnCounter, 1);
				//		}
				//		else
				//		{
				//			gmp_sprintf(line, "%Zd\t", r);
				//			mpz_add_ui(columnCounter, columnCounter, 1); //columnCounter++
				//		}
				//	}
				//	else
				//	{
				//		gmp_sprintf(line, "%Zd\t%Zd\n", q, r);

				//	}

				//}
				//else
				//{
					//gmp_sprintf(line, "%-20Zd%-20Zd%-20Zd\n", qrList->GetCount(), q, r);
				//}


				qrList.Add(periodLength, q, r);
			}
			// antiPeriod-- 
			mpz_sub_ui(copyAntiPeriod, copyAntiPeriod, 1);
		}
		mpz_tdiv_qr(q, r, n, d);
		mpz_set(r0, r);
	}
	else
	{
		mpz_tdiv_qr(q, r, n, d);
		mpz_set(r0, r);
	}

	do
	{
		//perform the division
		mpz_mul_si(r, r, 10);
		mpz_set(n, r);
		mpz_tdiv_qr(q, r, n, d);

		////if (imageSize > 0)
		////{
		////	if (imageDepth == 1) // 8 bit gray
		////	{

		////	}
		////	else if (imageDepth == 2) //16 bit gray
		////	{
		////		if (imgIndex <= ((image.dataSize) - 1))
		////		{
		////			unsigned long v = mpz_get_ui(r);
		////			int rndIndex = imgIndex;
		////			int rndExtIndex = imgIndex;
		////			// nat image
		////			image.data[imgIndex++] = (BYTE)((v >> 8) & 0xFF);
		////			image.data[imgIndex++] = (BYTE)(v & 0xFF);
		////			// rand image
		////			randImage.data[rndIndex++] = rand() % 255;
		////			randImage.data[rndIndex++] = rand() % 255;

		////			int rv = fastrand();
		////			randExtImage.data[rndExtIndex++] = (rv & 0XFF);
		////			//printf("val: %d\n", randExtImage.data[rndExtIndex]);
		////			rv = fastrand();
		////			randExtImage.data[rndExtIndex++] = (rv & 0XFF);
		////			//printf("val: %d\n", randExtImage.data[rndExtIndex]);
		////		}
		////	}
		////	else if (imageDepth == 3) //24 bit color
		////	{
		////		if (imgIndex <= ((imageSize*imageSize*imageDepth) - 1))
		////		{
		////			unsigned long v = mpz_get_ui(r);
		////			int rndIndex = imgIndex;
		////			int rndExtIndex = imgIndex;
		////			//v |= 0xFF000000;
		////			//char aC = (char)((v >> 24) & 0xFF);
		////			BYTE rC = (BYTE)((v >> 16) & 0xFF);
		////			BYTE gC = (BYTE)((v >> 8) & 0xFF);
		////			BYTE bC = (BYTE)(v & 0xFF);

		////			//srand(int(time(0)));//seed
		////			randImage.data[rndIndex++] = rand() % 255;
		////			randImage.data[rndIndex++] = rand() % 255;
		////			randImage.data[rndIndex++] = rand() % 255;
		////			//randomImg[rndIndex++] = 0xFF;

		////			//unsigned int l;
		////			//rand_sse(&l);
		////			randExtImage.data[rndExtIndex++] = fastrand() % 255;
		////			//rand_sse(&l);
		////			randExtImage.data[rndExtIndex++] = fastrand() % 255;
		////			//rand_sse(&l);
		////			randExtImage.data[rndExtIndex++] = fastrand() % 255;

		////			image.data[imgIndex++] = bC;
		////			image.data[imgIndex++] = gC;
		////			image.data[imgIndex++] = rC;
		////			//image[imgIndex++] = aC;
		////		}
		////	}
		////	else if (imageDepth == 4) //32 bit
		////	{


		////	}
		////}


		// Found period of exact division
		if (mpz_cmp(r0, r) == 0 || mpz_cmp_d(r, 0) == 0)
			foundPeriod = true;

		mpz_add_ui(periodLength, periodLength, 1);
		if (updateNumberDB == false && imageSize == NULL && logDivision)
		{
			if (knowledgeBase)
			{
				//gmp_sprintf(line, "%Zd\t%Zd\n", q, r);
			}
			else
			{
				//gmp_sprintf(line, "%-20Zd%-20Zd%-20Zd\n", qrList->GetCount(), q, r);
				qrList.Add(periodLength,q, r);
			}

			//qrList->Add(line);
		}

		

		//console log
		mpz_mod_ui(cycle, periodLength, 1000000);
		if (mpz_cmp_d(cycle, 0) == 0)
			gmp_printf("Cycle: %Zd\r", periodLength);

	} while (!foundPeriod);

	//gmp_printf("Division Completed. Period length: %Zd\n", periodLength);

	if (imageSize > 0)
	{
		////char imageNameBuff[512];
		////memset(imageNameBuff, 0, sizeof(imageNameBuff));
		////sprintf(imageNameBuff, "Image_%d_%d_%dbit.pgm", image.width, image.height, 8 * image.depth);

		//////save image
		////savePGM16bit(imageNameBuff, &image);

		//////save rand image
		////char randImageNameBuff[512];
		////memset(randImageNameBuff, 0, sizeof(randImageNameBuff));
		////sprintf(randImageNameBuff, "Rand_Image_%d_%d_%dbit.pgm", randImage.width, randImage.height, 8 * randImage.depth);
		////savePGM16bit(randImageNameBuff, &randImage);

		////char randExtImageNameBuff[512];
		////memset(randExtImageNameBuff, 0, sizeof(randExtImageNameBuff));
		////sprintf(randExtImageNameBuff, "RandExt_Image_%d_%d_%dbit.pgm", randExtImage.width, randExtImage.height, 8 * randExtImage.depth);
		////savePGM16bit(randExtImageNameBuff, &randExtImage);



		//////Start GDI+
		////////ULONG_PTR gdiplusToken;
		////////Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		////////Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		////////Gdiplus::Bitmap* bmp = NULL;
		////////Gdiplus::Bitmap* bmpRand = NULL;
		////////if(imageSize == 4096)
		////////{
		////////	bmp = new Gdiplus::Bitmap(imageSize, imageSize, imageSize * 3, PixelFormat24bppRGB, (BYTE*)image /*videoBuffer*/);
		////////	bmpRand = new Gdiplus::Bitmap(imageSize, imageSize, imageSize * 3, PixelFormat24bppRGB, (BYTE*)randomImg /*videoBuffer*/);
		////////}
		////////else if( imageSize == 16)
		////////{
		////////	//bmp = new Gdiplus::Bitmap(imageSize, imageSize, imageSize *3, PixelFormat24bppRGB, (BYTE*)image /*videoBuffer*/);
		////////	//bmpRand = new Gdiplus::Bitmap(imageSize, imageSize, imageSize *3, PixelFormat24bppRGB, (BYTE*)randomImg /*videoBuffer*/);
		////////}

		////////CLSID pngClsid;
		////////GetEncoderClsid(L"image/png", &pngClsid);


		////std::wostringstream wss, wssrnd;
		////std::stringstream ss, ssrnd, ssl;

		////wss << "Image_" << imageSize << "_" << imageSize << ".png";
		////wssrnd << "Image_Rnd_" << imageSize << "_" << imageSize << ".png";

		////ss << "Image_" << imageSize << "_" << imageSize << ".png";
		////ssrnd << "Image_Rnd_" << imageSize << "_" << imageSize << ".png";

		///////*if(imageSize != 16)
		//////{
		//////	bmp->Save(wss.str().c_str(), &pngClsid,NULL);
		//////	bmpRand->Save(wssrnd.str().c_str(), &pngClsid,NULL);
		//////	Gdiplus::GdiplusShutdown(gdiplusToken);
		//////}*/
		////FILE* lFile;
		////ssl << "EntropyLog_" << imageSize << ".txt";
		////lFile = fopen(ssl.str().c_str(), "w");
		////if (lFile != NULL)
		////{
		////	ComputeShannonEntropyS(image.data, image.dataSize, lFile);
		////	ComputeShannonEntropyS(randImage.data, randImage.dataSize, lFile);
		////	ComputeShannonEntropyS(randExtImage.data, randImage.dataSize, lFile);

		////	ComputeShannonEntropyDoubleS(image.data, image.dataSize, lFile);
		////	ComputeShannonEntropyDoubleS(randImage.data, randImage.dataSize, lFile);
		////	ComputeShannonEntropyDoubleS(randExtImage.data, randImage.dataSize, lFile);

		////	ComputeShannonEntropyArbS(image.data, image.dataSize, lFile);
		////	ComputeShannonEntropyArbS(randImage.data, randImage.dataSize, lFile);
		////	ComputeShannonEntropyArbS(randExtImage.data, randImage.dataSize, lFile);

		////	fclose(lFile);
		////}
		////else
		////{
		////	cout << "Error opening log file" << endl;
		////}
	}
	else
	{
		if (updateNumberDB == false && logDivision)
		{
			cout << "Writing on log file..." << endl;
			FILE* logFile;
			char fileName[2048];
			gmp_sprintf(fileName, "n[%Zd]d[%Zd].txt", numerator, denominator);
			logFile = fopen(fileName, "w");
			if (!knowledgeBase)
			{
				fprintf(logFile, "Numerator   : "); mpz_out_str(logFile, 10, numerator); fprintf(logFile, "\n");
				fprintf(logFile, "Denominator : "); mpz_out_str(logFile, 10, denominator); fprintf(logFile, "\n");
				fprintf(logFile, "Anti-P      : "); mpz_out_str(logFile, 10, antiPeriod); fprintf(logFile, "\n"); mpz_clear(antiPeriod);
				fprintf(logFile, "Period Len  : "); mpz_out_str(logFile, 10, periodLength); fprintf(logFile, "\n"); mpz_clear(periodLength);
				fprintf(logFile, "\n"); fprintf(logFile, "\n"); fprintf(logFile, "\n");
				fprintf(logFile, "Cycle #          Quotient            Reminder "); fprintf(logFile, "\n");
				fprintf(logFile, "_____________________________________________ ");
				fprintf(logFile, "\n");
				if (partial)
				{
					//qrList->SetPartial(1000);
					fprintf(logFile, "%s", qrList.toString().c_str());
				}
				else
				{
					//fprintf(logFile, "%s", (new string(qrList->ss.str()))->c_str());
				}
			}
			else
			{
				/*if (partial)
				{
					qrList->SetPartial(1000);
					fprintf(logFile, "%s", (new string(qrList->partialss.str()))->c_str());
				}
				else
					fprintf(logFile, "%s", (new string(qrList->ss.str()))->c_str());*/
			}

			fclose(logFile);
		}
	}
	//delete qrList;
	mpz_clear(r);
	mpz_clear(r0);
	mpz_clear(q);
	mpz_clear(n);
	mpz_clear(d);
	mpz_clear(cycle);
	mpz_clear(copyAntiPeriod);
	//mpz_clear(rnd);

}

int Test_presenza_AP(mpz_t d, mpz_t ap)
{
	int div_perfetto = 0;
	mpz_t cinque, due, exp2, exp5, daux;
	mpz_t  i, j;
	mpz_init(i);
	mpz_init(j);
	mpz_init(cinque);
	mpz_init(due);
	mpz_init(exp5);
	mpz_init(exp2);
	mpz_init(daux);
	mpz_set_d(cinque, 5); /* cinque=5 */
	mpz_set_d(due, 2);
	mpz_set_d(i, 5);
	mpz_set_d(j, 2);
	/* Verifico la divisibilità per 5 e calcolo l'esponente */
	while (mpz_divisible_p(d, cinque) != 0)
	{
		mpz_add_ui(exp5, exp5, 1);     /*exp5=exp5+1*/
		mpz_mul_si(cinque, cinque, 5); /* cinque_n=cinque_n*5 */
	}
	/* Verifico la divisibilità per 2 e calcolo l'esponente */
	while (mpz_divisible_p(d, due) != 0)
	{
		mpz_add_ui(exp2, exp2, 1); /*exp2=exp2+1*/
		mpz_mul_si(due, due, 2);   /* cinque_n=cinque_n*5 */
	}
	//gmp_printf("exp5=%Zd\n", exp5);gmp_printf("exp2=%Zd\n", exp2);
	gmp_power(cinque, i, exp5); /* cinque=5^exp5*/
	gmp_power(due, j, exp2);    /* due=2^exp2 */
	mpz_mul(daux, cinque, due);/* daux=(5^exp5 * 2^exp2) */
	// gmp_printf("daux=%Zd\n", daux);
	if (mpz_cmp(d, daux) != 0)
	{
		/* scelgo il maggiore esponente tra quello di due e cnque */
		if (mpz_cmp(exp5, exp2) <= 0)
		{
			mpz_set(ap, exp2);        /* AP=exp2 */
		}
		else if (mpz_cmp(exp5, exp2)>0)
		{
			mpz_set(ap, exp5);        /* AP=exp5 */
		}
		div_perfetto = 0;
		mpz_clear(i); mpz_clear(j); mpz_clear(cinque); mpz_clear(due); mpz_clear(exp2);
		mpz_clear(exp5); mpz_clear(daux);
		return(div_perfetto);
	}
	else
	{
		mpz_set_d(ap, 0);
		div_perfetto = 1;
		mpz_clear(i); mpz_clear(j); mpz_clear(cinque); mpz_clear(due); mpz_clear(exp2);
		mpz_clear(exp5); mpz_clear(daux);
		return(div_perfetto);
	}

	mpz_clear(i); mpz_clear(j); mpz_clear(cinque); mpz_clear(due); mpz_clear(exp2);
	mpz_clear(exp5); mpz_clear(daux);
}/*function*/
void gmp_power(mpz_t risultato, mpz_t base, mpz_t exp)
{
	mpz_t aux;
	mpz_init(aux);
	mpz_set(aux, exp);
	mpz_set(risultato, base);

	while (mpz_cmp_d(aux, 2) >= 0)
	{
		mpz_mul(risultato, risultato, base);
		mpz_sub_ui(aux, aux, 1);
	}/*while*/
	if (mpz_cmp_d(exp, 0) == 0){ mpz_set_d(risultato, 1); }
	mpz_clear(aux);
};/* function */


void ProcessParameters(int argc, char* argv[])
{
	int i = 0;
	mpz_init(numerator);
	mpz_set_d(numerator, 0);
	mpz_init(denominator);
	mpz_set_d(denominator,0);
	for (int i = 1; i < argc; i++)
	{
		string s(argv[i]);
		if (s == "-n") // Set numerator
		{
			mpz_set_str(numerator, argv[i + 1], 10);
		}
		if (s == "-d") // Set denominator
		{
			mpz_set_str(denominator, argv[i + 1], 10);
		}
		if (s == "-is") // image size
		{
			imageSize = atoi(argv[i + 1]);
		}
		//if (s == "-id") // image depth
		//{
		//	imageDepth = atoi(argv[i + 1]);
		//}
		if (s == "-l")
		{
			logDivision = true;
		}
		if (s == "-p") //partial print in the log (first 1000 cycles and last 1000 cycles)
		{
			partial = true;
		}
		if (s == "-u") //continue updatgin sqlite db
		{
			updateNumberDB = true;
		}
		if (s == "-k") // create a kb in sqlite db
		{
			knowledgeBase = true;
		}
		if (s == "-r")
		{
			mpz_set_str(matrixRows, argv[i + 1], 10);
		}
		if (s == "-c")
		{
			mpz_set_str(matrixColumns, argv[i + 1], 10);
		}
	}
}
