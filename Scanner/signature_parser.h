#pragma once

#ifndef SIGNATURE_PARSER_H
#define SIGNATURE_PARSER_H

#include "signature_store.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace SimpleScanner {

	typedef boost::spirit::qi::rule<raw_const_byte_data, byte()> hex_digit_rule;
	typedef boost::spirit::qi::uint_parser<byte, 16, 1, 1> hex_1_digit_parser;

	class HexadecimalGrammar
		: public boost::spirit::qi::grammar<raw_const_byte_data, byte_string()>
	{
	public:
		HexadecimalGrammar();

	private:
		hex_digit_rule const m_hex_1_digit;
		hex_digit_rule m_hex_digit;
		start_type m_start;
	};

	class GUIDGrammar
		: public boost::spirit::qi::grammar<raw_const_byte_data, byte_string()>
	{
	public:
		GUIDGrammar();

	private:
		start_type m_start;
		hex_digit_rule const m_hex_digit;
	};

	class SignatureStoreGrammar
		: public boost::spirit::qi::grammar<raw_const_byte_data, signature_store()>
	{
	public:
		SignatureStoreGrammar();

		static bool parse(byte_iterator_range const& inputRange,
			signature_store& sigStore,
			bool needCheckLastParserPosition);

	private:
		GUIDGrammar const m_guid;
		HexadecimalGrammar const m_signature;
		start_type m_start;
	};

}

#endif