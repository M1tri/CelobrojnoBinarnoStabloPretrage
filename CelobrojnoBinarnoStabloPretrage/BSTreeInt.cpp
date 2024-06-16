#include "BSTreeInt.h"

#include <exception>
#include <math.h>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

void BSTreeInt::deleteTree(BSTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}

BSTNodeInt* BSTreeInt::search(int el) const
{
	BSTNodeInt* ptr = root;
	while (ptr != nullptr)
		if (ptr->isEQ(el))
			return ptr;
		else if (ptr->isGT(el))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	return nullptr;
}

void BSTreeInt::insert(int el)
{
	BSTNodeInt* ptr = root, * par = nullptr;
	while (ptr != nullptr) {  // trazenje mesta za umetanje novog cvora
		par = ptr;
		if (ptr->isLT(el))
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if (root == nullptr)    // stablo je prazno
		root = new BSTNodeInt(el);
	else if (par->isLT(el))
		par->right = new BSTNodeInt(el, float(el));
	else
		par->left = new BSTNodeInt(el, float(el));
	numOfElements++;
}

void BSTreeInt::deleteByCopying(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) { 	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)             // cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)         // cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			BSTNodeInt* parent = node;
			while (tmp->right != nullptr) {		// nalazenje krajnjeg desnog cvora
				parent = tmp;             		// u levom podstablu
				tmp = tmp->right;
			}
			node->setKey(tmp->getKey());		// prepisivanje reference na kljuc 
			if (parent == node)           		// tmp je direktni levi potomak node-a
				parent->left = tmp->left;		// ostaje isti raspored u levom podstablu
			else
				parent->right = tmp->left; 		// levi potomak tmp-a 
			delete tmp;							// se pomera na mesto tmp-a
			numOfElements--;
			return;
		}
		if (ptr == root)						// u slucaju (1) i (2) samo je pomerena
			root = node;						// referenca node pa je potrebno
		else if (par->left == ptr)				// izmeniti i link prethodnog cvora
			par->left = node;					// u slucaju (3) ovo nema dejstva
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::deleteByMerging(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) {	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)				// cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)			// cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			while (tmp->right != nullptr)		// nalazenje krajnjeg desnog cvora
				tmp = tmp->right;				// u levom podstablu
			tmp->right = node->right;			// prebacivanje desnog linka node-a u tmp
			node = node->left;					// na tekucem mestu bice prvi levi potomak
		}
		if (ptr == root)
			root = node;
		else if (par->left == ptr)
			par->left = node;
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::preorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		ptr->visit();
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void BSTreeInt::inorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		inorder(ptr->left);
		ptr->visit();
		inorder(ptr->right);
	}
}

void BSTreeInt::postorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		ptr->visit();
	}
}

void BSTreeInt::iterativePreorder() const
{
	BSTNodeInt* ptr = root;
	StackAsArrayBSTNodeInt stack(numOfElements);
	if (ptr != nullptr) {
		stack.push(ptr);
		while (!stack.isEmpty()) {
			ptr = stack.pop();
			ptr->visit();
			if (ptr->right != nullptr)	// levi potomak se stavlja u magacin
				stack.push(ptr->right); // posle desnog, da bi se prvi obradio
			if (ptr->left != nullptr)
				stack.push(ptr->left);
		}
	}
}

void BSTreeInt::breadthFirstSearch() const
{
	BSTNodeInt* ptr = root;
	QueueAsArrayBSTNodeInt queue(numOfElements);
	if (ptr != nullptr) {
		queue.enqueue(ptr);
		while (!queue.isEmpty()) {
			ptr = queue.dequeue();
			ptr->visit();
			if (ptr->left != nullptr)
				queue.enqueue(ptr->left);
			if (ptr->right != nullptr)
				queue.enqueue(ptr->right);
		}
	}
}
//TODO: Realizovati rekurzivni metod koji briše sve listove stabla, tj. čvorove koji nemaju nijednog potomka, 
// ako su na dubini (koren je na dubini 0) većoj od zadate (voditi računa o efikasnosti ovog metoda – ne koristiti metod za brisanje elementa iz stabla). 
// Rekurzivni metod sa potrebnim parametrima je neophodno dodati u klasu binarnog stabla.
void BSTreeInt::deleteAllLeafsDepth(int minDepth)
{
	//TODO: Obezbediti pozivanje implementiranog rekurzivnog metoda
	if (deleteAllLeafsDepth(root, 0, minDepth))
		root = nullptr;
}

bool BSTreeInt::deleteAllLeafsDepth(BSTNodeInt* ptr, int currDepth, int minDepth)
{
	if (ptr == nullptr)
		return false;

	if (ptr->left == nullptr && ptr->right == nullptr)
	{
		if (currDepth >= minDepth)
		{
			delete ptr;
			return true;
		}
	}

	if (ptr->left)
	{
		if (deleteAllLeafsDepth(ptr->left, currDepth + 1, minDepth))
		{
			ptr->left = nullptr;
		}
	}

	if (ptr->right)
	{
		if (deleteAllLeafsDepth(ptr->right, currDepth + 1, minDepth))
		{
			ptr->right = nullptr;
		}
	}

	return false;
}

// KOL2 grupa A 2022
int BSTreeInt::brCvorova()
{
	return brCvorova(root);
}

int BSTreeInt::brCvorova(BSTNodeInt* node)
{
	if (node == nullptr)
		return 0;

	if (node->left == nullptr && node->right == nullptr)
		return 1;

	return 1 + brCvorova(node->left) + brCvorova(node->right);
}

int BSTreeInt::razlika(BSTNodeInt* node)
{
	if (node == nullptr)
		return 0;

	int l = brCvorova(node->left);
	int r = brCvorova(node->right);

	return abs(l - r);
}

BSTNodeInt* BSTreeInt::maxRazlikaA()
{
	if (!root)
		return nullptr;

	return maxRazlikaA(root);
}

BSTNodeInt* BSTreeInt::maxRazlikaA(BSTNodeInt* node)
{
	if (node->left == nullptr && node->right == nullptr)
		return node;

	BSTNodeInt* toRet = nullptr;
	BSTNodeInt* left = nullptr;
	BSTNodeInt* right = nullptr;
	int max;
	int leftCount;
	int desnoCount;
	
	if (node->left != nullptr)
	{
		left = maxRazlikaA(node->left);
		leftCount = razlika(node->left);

		toRet = left;
		max = leftCount;
	}

	if (node->right != nullptr)
	{
		right = maxRazlikaA(node->right);
		desnoCount = razlika(node->right);

		if (toRet == nullptr)
		{ 
			toRet = right;
			max = desnoCount;
		}
		else
		{
			if (max < desnoCount)
			{
				toRet = right;
				max = desnoCount;
			}

		}
	}

	int self = razlika(node);
	if (max < self)
		toRet = node;

	return toRet;
}
// KOL2 grupa A 2022 


// KOL2 grupa B 2022
int BSTreeInt::sumaParnih()
{
	if (!root)
		return 0;

	return sumaParnih(root);
}

int BSTreeInt::sumaNeparnih()
{
	if (!root)
		return 0;

	return sumaNeparnih(root);
}

int BSTreeInt::sumaParnih(BSTNodeInt* node)
{
	if (node == nullptr)
		return 0;
	
	int sum = 0;

	if (node->left)
	{
		if (node->left->getKey() % 2 == 0)
		{
			sum += node->left->getKey();
		}
	}

	if (node->right)
	{
		if (node->right->getKey() % 2 == 0)
		{
			sum += node->right->getKey();
		}
	}

	return sum + sumaParnih(node->left) + sumaParnih(node->right);
}

int BSTreeInt::sumaNeparnih(BSTNodeInt* node)
{
	if (node == nullptr)
		return 0;

	int sum = 0;

	if (node->left)
	{
		if (node->left->getKey() % 2 != 0)
		{
			sum += node->left->getKey();
		}
	}

	if (node->right)
	{
		if (node->right->getKey() % 2 != 0)
		{
			sum += node->right->getKey();
		}
	}

	return sum + sumaNeparnih(node->left) + sumaNeparnih(node->right);
}

int BSTreeInt::razlikaB(BSTNodeInt* node)
{
	int l = sumaParnih(node);
	int r = sumaNeparnih(node);

	return abs(l - r);
}

BSTNodeInt* BSTreeInt::maxRazlikaB()
{
	if (!root)
		return nullptr;

	return maxRazlikaB(root);
}

BSTNodeInt* BSTreeInt::maxRazlikaB(BSTNodeInt* node)
{
	if (node->left == nullptr && node->right == nullptr)
		return node;

	BSTNodeInt* toRet = node;
	int currMax = razlikaB(node);

	if (node->left)
	{
		BSTNodeInt* left = maxRazlikaB(node->left);
		int lVisina = razlikaB(left);

		if (lVisina > currMax)
		{
			toRet = left;
			currMax = lVisina;
		}
	}

	if (node->right)
	{
		BSTNodeInt* right = maxRazlikaB(node->right);
		int rVisina = razlikaB(right);

		if (rVisina > currMax)
		{
			toRet = right;
			currMax = rVisina;
		}
	}

	return toRet;
}
// KOL2 grupa B 2022


// JUN 2023 
int BSTreeInt::visina()
{
	if (!root)
		return 0;

	return visina(root);
}

int BSTreeInt::visina(BSTNodeInt* node)
{
	if (node == nullptr)
		return 0;

	if (node->left == nullptr && node->right == nullptr)
		return 1;

	return 1 + max(visina(node->left), visina(node->right));
}

int BSTreeInt::razlikaVisina(BSTNodeInt* node)
{
	if (node == nullptr)
		return 0;

	int l = visina(node->left);
	int r = visina(node->right);

	return abs(l - r);
}

BSTNodeInt* BSTreeInt::MaxRazlikaVisina()
{
	if (!root)
		return nullptr;

	return MaxRazlikaVisina(root);
}

BSTNodeInt* BSTreeInt::MaxRazlikaVisina(BSTNodeInt* node)
{
	if (node->left == nullptr && node->right == nullptr)
		return node;

	BSTNodeInt* toRet = node;
	int currMax = razlikaVisina(node);

	if (node->left)
	{
		BSTNodeInt* left = MaxRazlikaVisina(node->left);
		int lVisina = razlikaVisina(left);

		if (lVisina > currMax)
		{
			toRet = left;
			currMax = lVisina;
		}
	}

	if (node->right)
	{
		BSTNodeInt* right = MaxRazlikaVisina(node->right);
		int rVisina = razlikaVisina(right);

		if (rVisina > currMax)
		{
			toRet = right;
			currMax = rVisina;
		}
	}

	return toRet;
}
// JUN 2023 

// JUN II 2023

int BSTreeInt::countSmallerSpecific(BSTNodeInt* node, int d, int n)
{
	int count = 0;

	if (node->left)
	{
		if (n - d < node->left->getKey() && node->left->getKey() < n)
			count++;

		count += countSmallerSpecific(node->left, d, n);
	}

	if (node->right)
	{
		if (n - d < node->right->getKey() && node->right->getKey() < n)
			count++;

		count += countSmallerSpecific(node->right, d, n);
	}

	return count;
}

int BSTreeInt::countSmaller(int d)
{
	if (!root)
		return 0;
	
	return countSmaller(root, d);
}

int BSTreeInt::countSmaller(BSTNodeInt* node, int d)
{
	if (node == nullptr)
		return 0;

	int count = 0;

	count += countSmallerSpecific(node, d, node->getKey());
	
	if (node->left)
	{
		count += countSmaller(node->left, d);
	}

	if (node->right)
	{
		count += countSmaller(node->right, d);
	}

	return count;
}

// JUN II 2023


// SEP 2023

int BSTreeInt::sum(BSTNodeInt* node)
{
	int suma = 0;

	if (node->left)
	{
		suma += node->left->getKey();
		suma += sum(node->left);
	}

	if (node->right)
	{
		suma += node->right->getKey();
		suma += sum(node->right);
	}

	return suma;
}

double BSTreeInt::average(BSTNodeInt* node)
{
	int suma = node->getKey() + sum(node);
	int count = brCvorova(node);

	return ((float)suma) / count;
}

BSTNodeInt* BSTreeInt::findMaxAvg()
{
	if (!root)
		return nullptr;

	return findMaxAvg(root);
}

BSTNodeInt* BSTreeInt::findMaxAvg(BSTNodeInt* node)
{
	if (node->left == nullptr && node->right == nullptr)
		return node;

	BSTNodeInt* toRet = node;
	double currMax = average(node);

	if (node->left)
	{
		BSTNodeInt* left = findMaxAvg(node->left);
		double lAvg = average(left);

		if (lAvg > currMax)
		{ 
			toRet = left;
			currMax = lAvg;
		}
	}

	if (node->right)
	{
		BSTNodeInt* right = findMaxAvg(node->right);
		double rAvg = average(right);

		if (rAvg > currMax)
		{
			toRet = right;
			currMax = rAvg;
		}

	}

	return toRet;
}

// SEP 2023


// OKT 2023
int BSTreeInt::depth(int node)
{
	if (!root)
		return -1;

	return depth(node, root, 0);
}

int BSTreeInt::depth(int wanted, BSTNodeInt* current, int currDepth)
{
	if (current->getKey() == wanted)
	{
		return currDepth;
	}
	
	int dubina = -1;

	if (current->left && dubina == -1)
	{
		dubina = depth(wanted, current->left, currDepth + 1);
	}

	if (current->right && dubina == -1)
	{
		dubina = depth(wanted, current->right, currDepth + 1);
	}

	return dubina;
}


BSTNodeInt* BSTreeInt::findDeepestLeaf()
{
	if (!root)
		return nullptr;

	return findDeepestLeaf(root);
}

BSTNodeInt* BSTreeInt::findDeepestLeaf(BSTNodeInt* node)
{
	if (node->left == nullptr && node->right == nullptr)
		return node;

	BSTNodeInt* left = nullptr;
	int lDepth = -1;

	BSTNodeInt* right = nullptr;
	int rDepth = -1;

	BSTNodeInt* toRet = nullptr;
	
	if (node->left)
	{
		left = findDeepestLeaf(node->left);
		toRet = left;
	}

	if (node->right)
	{
		right = findDeepestLeaf(node->right);
		
		if (toRet == nullptr)
		{
			toRet = right;
		}
		else
		{
			int lD = depth(left->getKey());
			int rD = depth(right->getKey());

			if (lD > rD)
			{
				toRet = left;
			}
			else
			{
				toRet = right;
			}
		}
	}

	return toRet;
}

// OKT 2023


// JUN2 2022
int BSTreeInt::brojCvorova(int keyMin, double valueMin)
{
	if (!root)
		return 0;

	int count = 0;
	bool keyMinRoot = false;

	if (root->key >= keyMin)
		keyMinRoot = true;

	brojCvorova(root, keyMin, valueMin, keyMinRoot, count);

	return count;
}

// Obican preorder obilazak stabla samo vodimo red da li smo do sad videli keyMin i da li
// trenutni cvor ima valueMin, po referenci saljemo brojac
void BSTreeInt::brojCvorova(BSTNodeInt* ptr, int keyMin, double valueMin, bool hasKeyMin, int& count)
{
	// proveravamo roditelja
	if (hasKeyMin && ptr->value >= valueMin)
		count++;

	// Prosledjujemo na sledece koleno dal ima keyMin
	bool toPass = false;
	if (hasKeyMin || ptr->key >= keyMin)
		toPass = true;

	if (ptr->left)
		brojCvorova(ptr->left, keyMin, valueMin, toPass, count);

	if (ptr->right)
		brojCvorova(ptr->right, keyMin, valueMin, toPass, count);
}

// JUN2 2022


// OKT2 2022

// Mora dodam ovo da moz dobijes pointer na node lol
BSTNodeInt* BSTreeInt::getNode(int p)
{
	if (!root)
		return nullptr;

	return getNode(root, p);
}

BSTNodeInt* BSTreeInt::getNode(BSTNodeInt* ptr, int p)
{
	if (ptr->getKey() == p)
		return ptr;

	if (ptr->left)
	{
		BSTNodeInt* left = getNode(ptr->left, p);
		if (left)
			return left;
	}

	if (ptr->right)
	{
		BSTNodeInt* right = getNode(ptr->right, p);
		if (right)
			return right;
	}

	return nullptr;
}

BSTNodeInt* BSTreeInt::findSibling(BSTNodeInt* p)
{
	if (!root || !p)
		return nullptr;

	int brojCvorova = brCvorova();

	QueueAsArrayBSTNodeInt red(brojCvorova);
	BSTNodeInt** nivo = new BSTNodeInt * [brojCvorova]();
	int nizIndex = 0;
	bool foundP = false;
	red.enqueue(root);

	while (!red.isEmpty())
	{
		int nivoSize = red.numberOfElements();

		for (int i = 0; i < nivoSize; i++)
		{
			BSTNodeInt* pom = red.dequeue();
			nivo[nizIndex++] = pom;

			if (pom->getKey() == p->getKey())
				foundP = true;

			if (pom->left)
				red.enqueue(pom->left);

			if (pom->right)
				red.enqueue(pom->right);

			if (foundP && nizIndex > 1)
			{
				// Prvi sibling koji naidje a da nije p se vraca
				for (int i = 0; i < nizIndex; i++)
				{
					if (nivo[i]->getKey() != p->getKey())
					{
						BSTNodeInt* toRet = nivo[i];
						delete[] nivo;
						return toRet;
					}
				}
			}
		}

		// p je jedinac
		if (foundP && nizIndex == 1)
		{
			delete[] nivo;
			return nullptr;
		}

		nizIndex = 0;
	}

	delete[] nivo;
	return nullptr;
}

// OK2 2022


// JUN 2022

bool BSTreeInt::isPerfect()
{
	// kao nmp svejedno sta se vrati jer stablo ne postoji
	if (!root)
		return true;

	return isPerfect(root);
}

bool BSTreeInt::isPerfect(BSTNodeInt* ptr)
{
	int levoCount = 0;
	int desnoCount = 0;

	if (!ptr->left && !ptr->right)
		return true;

	if (ptr->left)
		levoCount = brCvorova(ptr->left);

	if (ptr->right)
		desnoCount = brCvorova(ptr->right);

	if (abs(levoCount - desnoCount) > 1)
		return false;

	if (ptr->left && !ptr->right)
		return isPerfect(ptr->left);

	if (ptr->right && !ptr->left)
		return isPerfect(ptr->right);

	return isPerfect(ptr->left) && isPerfect(ptr->right);
}
// JUN 2022


// JUN 2021

int BSTreeInt::countSL()
{
	if (!root)
		return 0;

	int count = 0;
	countSL(root, count);

	return count;
}

void BSTreeInt::countSL(BSTNodeInt* ptr, int& count)
{
	int sumLeft = 0;
	if (ptr->left)
		sumLeft = sumOfChildren(ptr->left);

	int sumRight = 0;
	if (ptr->right)
		sumRight = sumOfChildren(ptr->right);

	if (sumLeft > sumRight)
		count++;

	if (ptr->left)
		countSL(ptr->left, count);

	if (ptr->right)
		countSL(ptr->right, count);
}

int BSTreeInt::sumOfChildren(BSTNodeInt* ptr)
{
	int sum = ptr->key;

	if (ptr->left)
		sum += sumOfChildren(ptr->left);

	if (ptr->right)
		sum += sumOfChildren(ptr->right);

	return sum;
}

// JUN 2021

