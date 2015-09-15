#pragma once

#include "stdafx.h"


typedef struct QRNodeStruct
{
	const long DataLength = 4096;

	QRNodeStruct* next;
	char* data;

	QRNodeStruct() :next(nullptr), data(nullptr)
	{
	
	}
	QRNodeStruct(mpz_t iteration, mpz_t q, mpz_t r) : next(nullptr)
	{
		size_t sz = mpz_sizeinbase(iteration, 10) + mpz_sizeinbase(q, 10) + mpz_sizeinbase(r, 10) + 50;
		data = (char*)malloc(sz + 1);
		gmp_sprintf(data, "%-20Zd%-20Zd%-20Zd", iteration, q, r);
	}
	~QRNodeStruct()
	{
		free(data);
		next = nullptr;
	}

}QRNode,*PQRNode;

class QRList
{
private:
	PQRNode head;
	PQRNode middle;
	PQRNode tail;

	//long nodesCount;
	mpz_t nodesCount;
	unsigned long size;


public:

	explicit QRList(unsigned long size = 0) : head(nullptr), tail(nullptr)
	{
		this->size = size;
		mpz_init(nodesCount);
		mpz_set_d(nodesCount, 0);
	}

	~QRList()
	{
		//clean
	}

	// Add a new node to the list
	void Add(mpz_t iteration,mpz_t q, mpz_t r)	
	{
		// Create new node
		PQRNode newNode = new QRNode(iteration, q, r);

		if (IsListEmpty()) {
			//Attach head and tile to the node
			head = new QRNode();
			head->next = newNode;
			tail = new QRNode();
			tail->next = newNode;
			IncNodesCount();
			return;
		}


		if (size == 0)
		{
			// link last node to the new one
			tail->next->next = newNode;
			// move tail to point to the new node
			tail->next = newNode;
			IncNodesCount();
		}
		else // static size, move head and tail in order to preserve size
		{
			if (mpz_cmp_d(nodesCount, size) == 0)
				tail->next->next = nullptr;
			// if we reached size, we remove the first node
			// so that the list has always the same size
			if (mpz_cmp_d(nodesCount, size + 1) == 0) {
				middle = new QRNode();
				middle->next = newNode;
				//nodesCount++;
			}

			if (mpz_cmp_d(nodesCount, 2 * size) > 0) {
				//move moddle
				PQRNode aux = new QRNode();
				aux->next = middle->next;
				middle->next = middle->next->next;
				delete aux->next;
				delete aux;
			}
		}
		
	};

	void Print()
	{
		int c;
		c = 0;
		PQRNode pCurrNode = head->next;
		std::stringstream ss;
		do	{
			std::string sline(pCurrNode->data);
			ss << pCurrNode << ": " << sline << " next=" << pCurrNode->next << std::endl;
			std::cout << ss.str();
			pCurrNode = pCurrNode->next;
			c++;
		} while (mpz_cmp_d(nodesCount, c) != 0);
		//while (pCurrNode != 0);
	}


	std::string ToString()
	{
		PQRNode pCurrNode = head->next;
		std::stringstream ss;
		//long counter = 0;
		//char* msgbuf= new char[100];

		//print first set of size = "size"
		do	{
			//sprintf(msgbuf, "Counter %d\n", counter++);
			//OutputDebugString(msgbuf);
			std::string sline(pCurrNode->data);
			ss << sline;
			pCurrNode = pCurrNode->next;
		} while (pCurrNode != nullptr);
		
		//print second set from middle to end
		pCurrNode = middle->next;
		do	{
			//sprintf(msgbuf, "Counter %d\n", counter++);
			//OutputDebugString(msgbuf);
			std::string sline(pCurrNode->data);
			ss << sline;
			pCurrNode = pCurrNode->next;
		} while (pCurrNode != nullptr);

		return ss.str();
	};

private:
	void IncNodesCount()
	{
		mpz_add_ui(nodesCount, nodesCount, 1); // nodesCount++
	}

	bool IsListEmpty()
	{
		return (mpz_cmp_d(nodesCount, 0) == 0);
	}

	bool IsListFull()
	{
		return (size > 0 && mpz_cmp_d(nodesCount, size) == 0);
	}

};

