#pragma once

#ifndef SIGNATURE_STORE_H
#define SIGNATURE_STORE_H

#include "signature.h"
#include "scanner_mapped_file.h"

namespace SimpleScanner {

	class SignatureStore : public signature_store {
	
	public:

		SignatureStore(signature_store&& storage);

		static signature_store_ptr create(boost::filesystem::path const& file_path,
			bool need_check_last_parser_position = false);
	
	};
}

#endif
