#pragma once

#include "gmp.h"
//#include <Windows.h>

typedef struct QRNodeStruct
{
	QRNodeStruct* next;
	char* data;

	QRNodeStruct() :next(nullptr), data(nullptr)
	{
	
	}
	QRNodeStruct(mpz_t iteration, mpz_t q, mpz_t r) : next(nullptr)
	{
		data = new char[1024];
		gmp_sprintf(data, "%-20Zd%-20Zd%-20Zd\n", iteration, q, r);
	}
	~QRNodeStruct()
	{
		delete[] data;
		next = nullptr;
	}

}QRNode,*PQRNode;

class QRList
{
private:
	PQRNode head;
	PQRNode middle;
	PQRNode end;
	//long nodesCount;
	mpz_t nodesCount;
	unsigned long size;


public:

	explicit QRList(unsigned long size) :head(nullptr), end(nullptr)
	{
		this->size = size;
		mpz_init(nodesCount);
		mpz_set_d(nodesCount, 0);
	}

	~QRList()
	{
		//clean
	}


	void Add(mpz_t iteration, mpz_t q, mpz_t r)
	{
		PQRNode newNode = new QRNode(iteration, q, r);
		if (mpz_cmp_d(nodesCount,0) == 0)
		{
			head = new QRNode();
			head->next = newNode;
			end = new QRNode();
			end->next = newNode;
			mpz_add_ui(nodesCount, nodesCount, 1); // nodesCount++
			return;
		}
		//add new node and move end
		if (mpz_cmp_d(nodesCount, size)==0)
			end->next->next = nullptr;
		else
			end->next->next = newNode;

		end->next = newNode;
		mpz_add_ui(nodesCount, nodesCount, 1);
		// if we reached size, we remove the first node
		// so that the list has always the same size
		if (mpz_cmp_d(nodesCount, size+1)==0)
		{
			middle = new QRNode();
			middle->next = newNode;
			//nodesCount++;
		}
		if (mpz_cmp_d(nodesCount, 2 * size) > 0)
		{
			//move moddle
			PQRNode aux = new QRNode();
			aux->next = middle->next;
			middle->next = middle->next->next;
			delete aux->next;
			delete aux;
		}
	};
	std::string toString()
	{
		PQRNode pCurrNode = head->next;
		std::stringstream ss;
		//long counter = 0;
		//char* msgbuf= new char[100];

		//print first set of size = "size"
		do
		{
			//sprintf(msgbuf, "Counter %d\n", counter++);
			//OutputDebugString(msgbuf);
			std::string sline(pCurrNode->data);
			ss << sline;
			pCurrNode = pCurrNode->next;
		} while (pCurrNode != nullptr);
		
		//print second set from middle to end
		pCurrNode = middle->next;
		do
		{
			//sprintf(msgbuf, "Counter %d\n", counter++);
			//OutputDebugString(msgbuf);
			std::string sline(pCurrNode->data);
			ss << sline;
			pCurrNode = pCurrNode->next;
		} while (pCurrNode != nullptr);

		return ss.str();
	};

};

