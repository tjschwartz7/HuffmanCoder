#include "HuffmanTree.h"


/// <summary>
/// This function takes a character and adds it to our current list of nodes. 
/// If the character is new, make a new node. Else, increment the weight of the existing node.
/// This insertion is O(N) - N caps out at the size of the character set we're using, but it should probably be around 256 (ASCII), and even less on average.
/// </summary>
/// <param name="c"> - The character we're adding.</param>
void HuffmanTree::AddCharacterToTree(char c)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].symb == c)
		{
			//Character already exists - increment weight
			nodes[i].weight++;

			//Bubble sort in place.
			//Doing this on each iteration will keep the list "mostly sorted",
			//which, on top of the list size always being relatively small, makes bubble sort not so bad.
			//This will keep it O(1) when finding the two smallest nodes later
			while (i > 1 && nodes[i].weight < nodes[i - 1].weight)
			{
				//Swap these
				HuffmanNode temp = nodes[i - 1];
				nodes[i - 1] = nodes[i];
				nodes[i] = temp;
			}
			//----------------------------------------------------------------------------//
			// You might notice I bubbled the smallest weights towards the front -        //
			// This means that the two smallest weights are ALWAYS nodes[0] and nodes[1]. //
			//----------------------------------------------------------------------------//
			 
			break;
		}
	}
	HuffmanNode character;
	//New character - weight is 1.
	character.symb = c;
	character.weight = 1;

	//These are currently null
	character.LCH = nullptr;
	character.RCH = nullptr;
	//Insert this new node at the front of the vector - size one is the smallest a weight can be.
	//This means that this node is 'pre=sorted'
	nodes.insert(nodes.begin(), character);
}

/// <summary>
/// This function will compile our nodes until only one remains. It does this by calling PerformOneNodeMerge over and over again,
/// which, on each iteration, will decrease the total size of nodes by one.
/// This algorithm is O(N^2), where N should remain pretty small (similar to the time complexity of AddCharacterToTree).
/// </summary>
void HuffmanTree::CompileCompletedTree()
{
	//O(N)
	while (nodes.size() > 1)
	{
		//O(N)
		PerformOneNodeMerge();
	}
}


/// <summary>
/// This function will find the index of the two smallest nodes, and then merge them.
/// This function is O(N) because of the inplace sort.
/// </summary>
void HuffmanTree::PerformOneNodeMerge()
{
	//Because of how we sorted our nodes,
	//nodes[0] and nodes[1] will ALWAYS contain our two smallest nodes.
	HuffmanNode smallestOne = nodes[0];
	HuffmanNode smallestTwo = nodes[1];
	HuffmanNode parent;
	parent.LCH = &smallestOne;
	parent.RCH = &smallestTwo;
	parent.weight = smallestOne.weight + smallestTwo.weight; //Parent node is the sum of the two children.
	parent.symb = (char)0x00; //NUL character - because no character exists.

	//Erase the first two nodes - they've been integrated.
	nodes.erase(nodes.begin());
	nodes.erase(nodes.begin());

	//Replace those nodes we deleted with the parent node.
	nodes.insert(nodes.begin(), parent);

	//Now we need to sort this node back into place
	for (int i = 0; i < nodes.size()-1; i++)
	{
		//This nodes weight is larger than the next node - swap them
		if (nodes[i].weight > nodes[i + 1].weight)
		{
			//Swap these
			HuffmanNode temp = nodes[i + 1];
			nodes[i + 1] = nodes[i];
			nodes[i] = temp;
		}
		else break; //This node is sorted because the next node is larger than this node -
		//This only works because the list is always completely sorted except for the item
		//which is currently being 'bubbled-up'.
	}

	//--------------------------------------------------------------//
	// We've now merged two of the smallest weighted nodes together //
	// and then swapped them back into place.                       //
	//--------------------------------------------------------------//
}