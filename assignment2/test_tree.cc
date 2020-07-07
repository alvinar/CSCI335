// Alvin Rosario
// Main file for Part2(b) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

// Function for extracting the acronym from db_line.
string GetEnzymeAcronym(string &db_line)
{
	string acronym = "";
	for (int i = 0; db_line[i] != '/'; i++)
	{
		acronym += db_line[i];
	}
	db_line.erase(0, acronym.size() + 1);
	return acronym;
}

// Function for extracting recognition sequences from db_line.
bool GetNextRecognitionSequence(string &db_line, string &a_reco_seq)
{
	if (db_line == "/") // every line ends in "//" and "/" is our delimiter
	{
		return false; // a '/' means we got the last recognition sequence
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
	
	while (getline(fin, db_line))
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

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
{
	a_tree = Parser(db_filename); // populate our tree
	
	int number_of_nodes = a_tree.countNodes();
	cout << "2: " << number_of_nodes << endl;
	
	int sum_of_depths = a_tree.getDepth();
	float internal_path_length = (float)sum_of_depths / (float)number_of_nodes;
	cout << "3a: " << internal_path_length << endl;
	
	float ratio = internal_path_length / log2(number_of_nodes);
	cout << "3b: " << ratio << endl;
	
	bool flag = false; // set flag for use of find()
	ifstream fin;
	string db_line;
	int successful_queries = 0;
	fin.open(seq_filename);
	
	while (getline(fin, db_line))
	{
		// we know we got a match if a SequenceMap was returned
		if (typeid(a_tree.find(db_line, flag)) == typeid(SequenceMap))
		{
			successful_queries++;
		}
	}
	
	fin.close();
	cout << "4a: " << successful_queries << endl;
	
	int total_queries = 0;
	fin.open(seq_filename);
	
	while (getline(fin, db_line))
	{
		// count recursive calls for each sequence then add to running total
		total_queries += a_tree.recursiveCalls_for_find(db_line, flag);
	}
	
	float avg_num_recursive_calls = (float)total_queries / (float)successful_queries;
	fin.close();
	cout << "4b: " <<  avg_num_recursive_calls << endl;
	
	fin.open(seq_filename);
	flag = false;
	int total_removes = 0;
	int remove_recursive_calls = 0;
	
	while (getline(fin, db_line))
	{
		// count recursive call for each sequence then add to running total
		remove_recursive_calls += a_tree.recursiveCalls_for_remove(a_tree.find(db_line, flag));
		if (flag)
		{
			total_removes++;
			flag = false;
		}
		getline(fin, db_line); // do getline again to skip the next line
	}
	
	fin.close();
	cout << "5a: "  << total_removes << endl;
	
	float average_remove_recursions = (float)remove_recursive_calls / (float)total_removes;
	cout << "5b: " << average_remove_recursions << endl;
	
	number_of_nodes = a_tree.countNodes();
	cout << "6a: " << number_of_nodes << endl;
	
	sum_of_depths = a_tree.getDepth();
	internal_path_length = (float)sum_of_depths / (float)number_of_nodes;
	cout << "6b: " << internal_path_length << endl;
	
	ratio = internal_path_length / log2(number_of_nodes);
	cout << "6c: " << ratio << endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
