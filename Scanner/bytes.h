#pragma once

#ifndef BYTES_H
#define BYTES_H

#include <boost/range/iterator_range_core.hpp>

namespace SimpleScanner {
	
	typedef unsigned char byte;
	typedef byte const* byte_const_ptr;
	typedef byte_const_ptr raw_const_byte_data;
	typedef std::basic_string<byte> byte_string;
	typedef boost::iterator_range<byte_const_ptr> byte_iterator_range;
}

#endif