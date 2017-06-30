#pragma once

#include "stdafx.h"

#include <string>

#include <boost/range/iterator_range_core.hpp>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

namespace SimpleScanner {

	namespace bytes {
		typedef unsigned char byte;
		typedef byte const* byte_const_ptr;
		typedef byte_const_ptr raw_const_byte_data;
		typedef std::basic_string<byte> byte_string;
		typedef boost::iterator_range<byte_const_ptr> byte_iterator_range;
	}
	
	namespace data {
		typedef boost::iterator_range<bytes::byte_const_ptr> byte_data_range;
		typedef boost::unordered_map<std::string, byte_data_range> byte_data_range_store;
		typedef std::shared_ptr<byte_data_range_store> byte_data_range_store_ptr;
	}

	namespace sc_grammar {
		typedef boost::spirit::qi::rule<bytes::raw_const_byte_data, bytes::byte()> hex_digit_rule;
		typedef boost::spirit::qi::uint_parser<bytes::byte, 16, 1, 1> hex_1_digit_parser;
	}
}
