/*************************************************************************
    Copyright (C) 2005 Joseph D'Errico, Wei Qin
    See file COPYING for more information.

    This program is free software; you can redistribute it and/or modify    
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*************************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <list>

/* WQin: Implemented these two classes because I want to avoid including
   std::list template in dyn_mips_emul.hpp, which is included by
   the Xcompiled_?.cpp. I suspect that having std::list in it may 
   slow down g++ noticeably since list depends on many other library headers.
*/

namespace emulator {

class uw_list {

  public:

	/* iterator */
	typedef std::list<unsigned>::iterator iterator;

	iterator begin() {return val.begin();}
	iterator end()   {return val.end();}

	iterator erase(iterator ii) {return val.erase(ii);}

	/* constructor */
	uw_list() {}

	/* destructor */
	~uw_list() {}

	/* access methods */
	void push_back(unsigned n) {val.push_back(n);}
	void push_front(unsigned n) {val.push_front(n);}

	unsigned pop_back()  {
		unsigned ret=val.back();
		val.pop_back();
		return ret;
	}
	unsigned pop_front() {
		unsigned ret=val.front();
		val.pop_front();
		return ret;
	}

	unsigned size() const {return val.size();}

	/* empty or not */
	bool empty() const {return val.empty();}

  private:
	std::list<unsigned> val;

};


class vp_list {

  public:
	/* constructor */
	vp_list() {}

	/* destructor */
	~vp_list() {}

	/* access methods */
	void push_back(void *n) {val.push_back(n);}
	void push_front(void *n) {val.push_front(n);}
	void *pop_back()  {
		void *ret=val.back();
		val.pop_back();
		return ret;
	}
	void *pop_front() {
		void *ret=val.front();
		val.pop_front();
		return ret;
	}

	unsigned size() const {return val.size();}

	/* empty or not */
	bool empty() const {return val.empty();}

  private:
	std::list<void *> val;

};


}

#endif
