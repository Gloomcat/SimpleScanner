#include "stdafx.h"

#include "signature_parser.h"

#include <boost/fusion/adapted/struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(SimpleScanner::Signature, (SimpleScanner::byte_string, value) (SimpleScanner::byte_string, guid));

namespace SimpleScanner {

	HexadecimalGrammar::HexadecimalGrammar() : base_type(m_start)
		, m_hex_1_digit(hex_1_digit_parser()) {
		using boost::phoenix::at;
		using boost::spirit::qi::_1;
		using boost::spirit::qi::_val;
		using boost::spirit::qi::repeat;

		m_hex_digit = repeat(2)[m_hex_1_digit][_val = at(_1, 0) << 4 | at(_1, 1)] | m_hex_1_digit[_val = _1 << 4];

		m_start = +m_hex_digit;
	}

	GUIDGrammar::GUIDGrammar() : base_type(m_start)
		, m_hex_digit(boost::spirit::qi::char_("0-9a-fA-F")) {
		using boost::spirit::qi::char_;

		m_start = char_('{')
			>> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit
			>> char_('-') >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit
			>> char_('-') >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit
			>> char_('-') >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit
			>> char_('-') >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit >> m_hex_digit
			>> char_('}')
			;
	}

	SignatureStoreGrammar::SignatureStoreGrammar() : base_type(m_start) {
		using boost::spirit::qi::eol;
		using boost::spirit::qi::eoi;

		m_start = +(m_signature >> '.' >> m_guid >> eol) >> -eoi;
	}

	bool SignatureStoreGrammar::parse(byte_iterator_range const& inputRange,
		signature_store& sig_store,
		bool needCheckLastParserPosition) {

		bool const parseResult = boost::spirit::qi::phrase_parse(inputRange.begin(), inputRange.end(), SignatureStoreGrammar(), boost::spirit::qi::ascii::space, sig_store);
		return parseResult && (needCheckLastParserPosition ? inputRange.begin() == inputRange.end() : true);
	}

	SignatureStore::SignatureStore(signature_store&& storage)
		: signature_store(std::forward<signature_store>(storage)) {}

	signature_store_ptr SignatureStore::create(boost::filesystem::path const& file_path,
		bool need_check_last_parser_position) {
		try {
			if (!file_path.empty()
				&& boost::filesystem::exists(file_path)
				&& !boost::filesystem::is_empty(file_path)
				&& boost::filesystem::is_regular_file(file_path))
			{
				MappedFileForRead const mapped_file_read_only(file_path);
				signature_store storage;

				if (SignatureStoreGrammar::parse(
					mapped_file_read_only.get_range(),
					storage,
					need_check_last_parser_position))
					return signature_store_ptr(new SignatureStore(std::move(storage)));

				return nullptr;
			}

			return nullptr;
		}
		catch (...) {
			return nullptr;
		}
	}
}