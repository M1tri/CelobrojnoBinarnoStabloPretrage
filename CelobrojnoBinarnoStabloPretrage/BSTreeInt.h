#pragma once

#include "BSTNodeInt.h"
#include "QueueAsArrayInt.h"

class BSTreeInt
{
protected:
	BSTNodeInt* root;
	long numOfElements;

	void deleteTree(BSTNodeInt* ptr);

	void inorder(const BSTNodeInt* ptr) const;
	void preorder(const BSTNodeInt* ptr) const;
	void postorder(const BSTNodeInt* ptr) const;

public:
	BSTreeInt() { root = nullptr; numOfElements = 0; }
	~BSTreeInt() { deleteTree(root); }

	bool isEmpty() const { return root == nullptr; }

	bool isInTree(int el) const { return search(el) != nullptr; }
	BSTNodeInt* search(int el) const;

	void insert(int el);
	void deleteByCopying(int el);
	void deleteByMerging(int el);

	void preorder() const { preorder(root); }
	void inorder() const { inorder(root); }
	void postorder() const { postorder(root); }

	void iterativePreorder() const;
	void breadthFirstSearch() const;

	void deleteAllLeafsDepth(int minDepth);
	
	// random ahh
	int levelWithMostNodes()
	{
		if (!root)
			return -1;

		QueueAsArrayBSTNodeInt red(brCvorova());
		int max = 0;

		int maxLevel = 0;
		int currLevel = 0;

		red.enqueue(root);

		while (!red.isEmpty())
		{
			int nivoSize = red.numberOfElements();

			if (nivoSize > max)
			{
				max = nivoSize;
				maxLevel = currLevel;
			}

			std::cout << "Nivo " << currLevel << " :\n";
			for (int i = 0; i < nivoSize; i++)
			{
				BSTNodeInt* pom = red.dequeue();
				pom->visit();

				if (pom->left)
					red.enqueue(pom->left);

				if (pom->right)
					red.enqueue(pom->right);
			}
			std::cout << '\n';
			currLevel++;
		}

		return maxLevel;
	}
	int levelWithHighestNodeSum()
	{
		if (!root)
			return -1;

		QueueAsArrayBSTNodeInt red(brCvorova());
		int maxLvl = 0;
		int maxSum = 0;
		int currLvl = -1;

		red.enqueue(root);

		while (!red.isEmpty())
		{
			currLvl++;
			int velicinaNivoa = red.numberOfElements();

			int sum = 0;
			for (int i = 0; i < velicinaNivoa; i++)
			{
				BSTNodeInt* pom = red.dequeue();

				if (pom->right)
					red.enqueue(pom->right);

				if (pom->left)
					red.enqueue(pom->left);

				sum += pom->key;
			}

			if (sum > maxSum)
			{
				maxSum = sum;
				maxLvl = currLvl;
			}
		}

		return maxLvl;
	}

	// random ahh

	// KOL2 grupa A 2022
	BSTNodeInt* maxRazlikaA();
	int brCvorova();
	// KOL2 grupa A 2022

	// KOL2 grupa B 2020
	int sumaParnih();
	int sumaNeparnih();	
	BSTNodeInt* maxRazlikaB();
	// KOL2 grupa B 2020

	// JUN 2023 
	int visina();
	BSTNodeInt* MaxRazlikaVisina();
	// JUN 2023

	// JUN II 2023
	int countSmaller(int d);
	// JUN II 2023

	// SEP 2023
	BSTNodeInt* findMaxAvg();
	// SEP 2023

	// OKT 2023
	BSTNodeInt* findDeepestLeaf();
	int depth(int Wanted);
	// OKT 2023

	// JUN2 2022
	int brojCvorova(int keyMin, double valueMin);
	// JUN2 2022


	// OKT2 2022

	BSTNodeInt* getNode(int p);

	BSTNodeInt* findSibling(BSTNodeInt* p);

	// OKT2 2022

	// JUN 2022

	bool isPerfect();

	// JUN 2022
	
	// JUN 2021

	int countSL();

	// JUN 2021


private:
	bool deleteAllLeafsDepth(BSTNodeInt* ptr, int currDepth, int minDepth);

	// KOL2 grupa A 2022
	BSTNodeInt* maxRazlikaA(BSTNodeInt* node);
	int brCvorova(BSTNodeInt* node);
	int razlika(BSTNodeInt* node);
	// KOL2 grupa A 2022

	// KOL2 grupa B 2020
	int sumaParnih(BSTNodeInt* node);
	int sumaNeparnih(BSTNodeInt* node);
	int razlikaB(BSTNodeInt* node);
	BSTNodeInt* maxRazlikaB(BSTNodeInt* node);
	// KOL2 grupa B 2020

	// JUN 2023 
	int visina(BSTNodeInt* node);
	int razlikaVisina(BSTNodeInt* node);
	BSTNodeInt* MaxRazlikaVisina(BSTNodeInt* node);
	// JUN 2023


	// JUN II 2023
	int countSmaller(BSTNodeInt* node, int d);
	int countSmallerSpecific(BSTNodeInt* node, int d, int n);
	// JUN II 2023

	
	// SEP 2023

	double average(BSTNodeInt* node);
	int sum(BSTNodeInt* node);
	// int brCvorova(BSTNodeInt* node); Vec postoji jer je ovo kolekcija resenja 
	// ali bi u izolacija morala opet da se implementira sto traje nekih 30 sekundi
	BSTNodeInt* findMaxAvg(BSTNodeInt* node);
	// SEP 2023

	// OKT 2023

	BSTNodeInt* findDeepestLeaf(BSTNodeInt* node);
	int depth(int Wanted, BSTNodeInt* current, int currDepth);

	// OKT 2023


	// JUN2 2022
		
		// Obican preorder obilazak stabla samo vodimo red da li smo do sad videli keyMin i da li
		// trenutni cvor ima valueMin, po referenci saljemo brojac

	void brojCvorova(BSTNodeInt* ptr, int keyMin, double valueMin, bool hasKeyMin, int& count);

	// JUN2 2022

	// OKT2 2022

	BSTNodeInt* getNode(BSTNodeInt* ptr, int p);
	
	// OK2 2022

	// JUN 2022

	bool isPerfect(BSTNodeInt* ptr);

	// JUN 2022

	// JUN 2021

	void countSL(BSTNodeInt* ptr, int& count);
	int sumOfChildren(BSTNodeInt* ptr);

	// JUN 2021


};

