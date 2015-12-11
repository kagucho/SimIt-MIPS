
/* this file is the adapter between two libraries */


#include <vector>
#include <list>
#include <string>
#include "decode.h"
#include "bin_pattern.hpp"

using std::list;
using std::vector;
using std::string;

static
BinPattern entry2pattern(DecodeEntry& entry)
{
	int ii;
	int nbits = INSTSIZE * 8;
	string spat;

	for (ii=nbits-1; ii>=0; ii--) {

		if (!entry.mask.bit_n(ii)) {
			spat += '-';
		}	
		else if (entry.signature.bit_n(ii)) {
			spat += '1';
		}
		else {
			spat += '0';
		}
	}
		
	return BinPattern(spat);
}

static
DecodeEntry pattern2entry(BinPattern& pat)
{
	string mask = "0x" + pat.get_hex_mask();
	string sign = "0x" + pat.get_hex_signature();

	return DecodeEntry(mask.c_str(), sign.c_str(), "null", 1e-10);
}


bool compute_undef(vector<DecodeEntry>& entries)
{
	list<BinPattern> pats;

	vector<DecodeEntry>::iterator ent_it;
	for (ent_it = entries.begin(); ent_it!=entries.end(); ent_it++) {
		pats.push_back(entry2pattern(*ent_it));
	}

	list<BinPattern> results;
	inverse(pats, results);
	
	// augment the original entries with null ones
	list<BinPattern>::iterator pat_it;
	for (pat_it = results.begin(); pat_it!=results.end(); pat_it++) {
		entries.push_back(pattern2entry(*pat_it));
	}
}
