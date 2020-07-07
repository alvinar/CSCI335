// Alvin Rosario
// Main File for Part 1 of Homework 2.

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
using namespace std;

/*  
	Objects of this class have an enzyme's recognition sequence as a string data member, and
	a vector containing its corresponding acronym(s).
	*  Constructor sets recognition_seqence_ and pushes one acronym onto the vector, depending on which acronym
	   was read in the line.
	*  bool operator< checks if one string is less than another using regular string comparison.
	*  &ostream operator<< prints everything in the object's enzyme_acronyms.
	*  void Merge merges two objects together if they contain the same recognition_sequence_.
	*  getRecSeq() returns the object's recognition sequence.
 */
class SequenceMap
{
	public:
	// Zero-parameter constructor.
	SequenceMap() = default;
	// Copy-constructor.
	SequenceMap(const SequenceMap &rhs) = default;
	// Copy-assignment.
	SequenceMap& operator=(const SequenceMap &rhs) = default;
	// Move-constructor. 
	SequenceMap(SequenceMap &&rhs) = default;
	// Move-assignment.
	SequenceMap& operator=(SequenceMap &&rhs) = default;
	// Destructor.
	~SequenceMap() = default;

	// Stores a recognition sequence as a string and a corresponding acronym into a vector.
	SequenceMap(const string &a_rec_seq, const string &an_enz_acro)
	{
		recognition_sequence_ = a_rec_seq;
		enzyme_acronyms_.push_back(an_enz_acro);
	}

	// Overloads the < operator for regular string comparison.
	bool operator<(const SequenceMap &sm) const
	{
		if (recognition_sequence_ < sm.recognition_sequence_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Overloads the << operator to mean "print every acronym stored in this object's vector."
	friend ostream& operator<<(ostream &os, const SequenceMap &sm)
	{
		int y = sm.enzyme_acronyms_.size();
		for (int x = 0; x < y; x++)
		{
			if (x == y-1)
	        {
				os << sm.enzyme_acronyms_[x];
	       	 }
	        else
	        {
				os << sm.enzyme_acronyms_[x] << " ";
	      	}
		}
   		return os;
	}
	// Function that pushes all of the enzyme acronyms of one objects into the vector of another object.
	// Assumes other_sequence has the same recognition sequence as the item it is being pushed into.
	void Merge(const SequenceMap &other_sequence)
	{
		int y = other_sequence.enzyme_acronyms_.size();
		for (int x = 0; x < y; x++)
		{
			enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[x]);
		}
	}
	string getRecSeq()
	{
		return recognition_sequence_;
	}
	private:
		string recognition_sequence_;
		vector<string> enzyme_acronyms_;
};

#endif
