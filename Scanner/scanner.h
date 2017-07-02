#pragma once

#ifndef SCANNER_H
#define SCANNER_H

#include "signature_store.h"

#include "i_scanner.h"

#include <mutex>


namespace SimpleScanner {
	
	// This class is exported from the Scanner.dll  
	class Scanner : public IScanner	{
	
	public:
		
		// Load sigs from file ( initialization )   
		std::pair<Results, std::string> load_signatures_file(std::string sig_file_path) override;

		// Perform file scan and returns signature's guid if found  
		std::pair<Results, std::string> scan_file(std::string file_path) override;

		// Perform data_range scan and returns signature's guid if found   
		std::pair<Results, std::string> scan_bytes(byte_string data) override;
		
		// Get current signature storage size
		int get_sig_storage_size() const override;

		// Get processed data counter
		int get_data_counter() override;

		// Reset processed data counter
		void reset_data_counter() override;

		Scanner();
		~Scanner() override = default;
		Scanner(const Scanner& rhs) = delete;
		Scanner& operator=(const Scanner& rhs) = delete;

	private:
		// Update data_counter
		void update_data_counter(int how);

		// Processed data counter
		std::atomic<int> data_counter;

		// For thread safe operations on data_counter
		//std::mutex data_counter_mutex;

		// Signature storage, initialized after successfull call to load_signatures_file
		signature_store_ptr sig_storage;

	};
}

#endif