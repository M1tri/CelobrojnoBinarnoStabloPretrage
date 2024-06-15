#include "BSTreeInt.h"

//#define LAB

void main()
{
	//TODO: Proveriti rad implementiranog metoda za različite slučajeve izvršenja 

	BSTreeInt drvo;

	drvo.insert(10);
	drvo.insert(6);
	drvo.insert(13);
	drvo.insert(0);
	drvo.insert(7);
	drvo.insert(19);
	drvo.insert(11);
	drvo.insert(18);
	drvo.insert(21);
	drvo.insert(5);
	drvo.insert(3);
	drvo.insert(4);

	// KOL2 grupa A 2022 
	BSTNodeInt* max = drvo.maxRazlikaA();

	if (max)
		max->visit();
	std::cout << '\n';
	// KOL2 grupa A 2022


	// KOL2 grupa B 2022
	max = drvo.maxRazlikaB();

	if (max)
		max->visit();
	std::cout << '\n';
	// KOL2 grupa B 2022


	// JUN 2023 
	max = drvo.MaxRazlikaVisina();

	if (max)
		max->visit();
	std::cout << '\n';
	// JUN 2023 


	// JUN II 2023
	
	int count = drvo.countSmaller(7);

	std::cout << count << '\n';

	// JUN II 2023


	// SEP 2023
	BSTNodeInt* maxAvg = drvo.findMaxAvg();

	if (maxAvg)
		maxAvg->visit();

	std::cout << '\n';
	// SEP 2023


	// OKT 2023

	BSTNodeInt* duboko = drvo.findDeepestLeaf();
	if (duboko)
		duboko->visit();
	std::cout << '\n';

	// OKT 2023

	// JUN2 2022

	int k = drvo.brojCvorova(11, 5.);
	std::cout << k << '\n';

	// JUN2 2022

	// OKT2 2022

	BSTNodeInt* p = drvo.getNode(3);
	BSTNodeInt* sibling = drvo.findSibling(p);
	if (sibling)
		sibling->visit();

	// OKT2 2022

	int maxLvl = drvo.levelWithMostNodes();



#ifdef LAB
	// zao mi ovo da brisem neka ga ovako
	drvo.inorder();
	std::cout << '\n';

	drvo.deleteAllLeafsDepth(1);

	drvo.inorder();
	std::cout << '\n';

	drvo.deleteAllLeafsDepth(1);

	drvo.inorder();
	std::cout << '\n';

	drvo.deleteAllLeafsDepth(0);

	drvo.inorder();
	std::cout << '\n';

	drvo.insert(10);
	drvo.insert(6);
	drvo.insert(13);
	drvo.insert(0);
	drvo.insert(7);

	drvo.inorder();
	std::cout << '\n';

	drvo.deleteAllLeafsDepth(2);

	drvo.inorder();
#endif LAB
}
