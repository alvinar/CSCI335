// Alvin Rosario
// Main file for Part2(a) of Assignment 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function for extracting the acronym from db_line.
string GetEnzymeAcronym(string &db_line)
{
	string acronym = "";
	for (int i = 0; db_line[i] != '/'; i++)
	{
		acronym += db_line[i];
	}
	db_line.erase(0, acronym.size()+1);
	return acronym;
}

// Function for extracting recognition sequences from db_line.
bool GetNextRecognitionSequence(string &db_line, string &a_reco_seq)
{
	if (db_line == "/") // every line ends in "//" and "/" is our delimiter
	{
		return false;
	}
	a_reco_seq = "";
	for (int i = 0; db_line[i] != '/'; i++)
	{
		a_reco_seq += db_line[i];
	}
	db_line.erase(0, a_reco_seq.size() + 1);
	return true;
}

// Function for populating our AvlTree. Returns an AvlTree<SequenceMap> built from db_filename.
AvlTree<SequenceMap> Parser(const string &db_filename)
{
	ifstream fin;
	string db_line = "";
	string recseq = "";
	string junk = "";
	AvlTree<SequenceMap> sometree;
	fin.open(db_filename);
	
	for (int x = 0; x < 10; x++) // skip the first 10 lines of the file
	{
	  getline(fin, junk);
	}
	
	while (getline(fin, db_line)) // read the file line-by-line
	{
		string an_enz_acro = GetEnzymeAcronym(db_line); // first part of line
		string a_reco_seq;
		while (GetNextRecognitionSequence(db_line, a_reco_seq)) // loop for every recognition sequence
		{
			sometree.insert(SequenceMap(a_reco_seq, an_enz_acro));
		}
		if (an_enz_acro == "Zsp2I") // stop once we get to last acronym to avoid creating empty nodes
		{
			break;
		}
	}
	fin.close();
	
	return sometree;
}

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
	a_tree = Parser(db_filename); // create our tree
	//a_tree.printTree();
	cout << endl;
	ifstream fin;
	string aline = "";
	string aline2 = "";
	string aline3 = "";
	fin.open("input_part2a.txt");
    bool flag = false;
	// Store every line to find in the tree:
	getline(fin, aline);
	getline(fin, aline2);
	getline(fin, aline3);
	SequenceMap result = a_tree.find(aline, flag);
	
	if (flag)
	{
		cout << result << endl;
	}
	
	else
	{
		cout << "Not Found" << endl;
	}
	
	flag = false;
	result = a_tree.find(aline2, flag);
	
	if (flag)
	{
		cout << result << endl;
	}
	
	else
	{
		cout << "Not Found" << endl;
	}
	flag = false;
	
	result = a_tree.find(aline3, flag);
	if (flag)
	{
		cout << result << endl;
	}
	
	else
	{
		cout << "Not Found" << endl;
	}
	fin.close();
} 

} // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  return 0;
}
