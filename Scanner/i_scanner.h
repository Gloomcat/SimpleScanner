#pragma once

#ifndef I_SCANNER_H
#define I_SCANNER_H

#include <string>

class IScanner {

public:
	// Results enum
	enum class Results {
		SCANNER_OK,
		SCANNER_STAT,
		SCANNER_ERROR,
		SCANNER_WARN,
		SCANNER_INFECTED
	};

	
	// Load sigs from file ( initialization )   
	virtual std::pair<Results, std::string> load_signatures_file(std::string sig_file_path) = 0;

	// Perform file scan and returns signature's guid if found  
	virtual std::pair<Results, std::string> scan_file(std::string file_path) = 0;

	// Perform data_range scan and returns signature's guid if found   
	virtual std::pair<Results, std::string> scan_bytes(std::basic_string<unsigned char> data) = 0;

	// Get current signature storage size
	virtual int get_sig_storage_size() const = 0;

	// Get processed data counter
	virtual int get_data_counter() = 0;

	// Reset processed data counter
	virtual void reset_data_counter() = 0;

	virtual ~IScanner() = default;
};

#endif
