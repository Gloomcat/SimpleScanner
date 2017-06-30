// Scanner.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

#include "scanner.h"

#include <boost/config.hpp>
#include <boost/optional.hpp>

namespace SimpleScanner {
	
	typedef std::lock_guard<std::mutex> g_Lock;
	typedef boost::optional<byte_string> optional_guid;
	typedef boost::iterator_range<signature_store::const_iterator> signature_range;

	Scanner::Scanner() : sig_storage(nullptr), data_counter(0) {}

	std::pair<Scanner::Results, std::string> Scanner::load_signatures_file(std::string sig_file_path) {
		
		if (sig_storage != nullptr) {
			sig_storage->clear();
			sig_storage = nullptr;
		}
		
		sig_storage = SignatureStore::create(sig_file_path);
		if (sig_storage == nullptr) {
			return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_ERROR, 
				std::string("ERROR:\n1) Check signature file is not empty\n2) Check signature structure in file"));
		}

		return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_OK, 
			std::string("Signatures loaded successfully!"));
	}

	std::pair<Scanner::Results, std::string> Scanner::scan_file(std::string file_path) {
		if (sig_storage != nullptr) {
			
			if (!file_path.empty()
				&& boost::filesystem::exists(file_path)
				&& !boost::filesystem::is_empty(file_path)
				&& boost::filesystem::is_regular_file(file_path)) {

				MappedFileForRead const file(file_path);
				auto const& data_range = file.get_range();
				signature_range sig_range = boost::make_iterator_range(*sig_storage);

				optional_guid result;
				int sig_storage_size = get_sig_storage_size();
				for (auto const& current_signature : sig_range) {
					if (std::search(data_range.begin(), data_range.end(),
						current_signature.value.begin(),
						current_signature.value.end()) != data_range.end()
						) {
						result = current_signature.guid;
						update_data_counter(sig_storage_size);
						break;
					}
					update_data_counter(1);
					sig_storage_size--;
				}


				if (result) {
					std::string result_message = file_path += std::string(" is infected!\nMalware GUID: ") 
						+= std::string((const char*)(result->data()));
					return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_INFECTED, 
						std::move(result_message));
				}
				else {
					std::string result_message = file_path += std::string(" is clean");
					return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_OK, std::move(result_message));
				}
			} 
			else {
				update_data_counter(get_sig_storage_size());
				std::string result_message = file_path += std::string(" is empty");
				return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_WARN, std::move(result_message));
			}
		}
		return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_ERROR, 
			std::string("ERROR: Signature storage is empty!"));
	}

	std::pair<Scanner::Results, std::string> Scanner::scan_bytes(byte_string data) {
		if (sig_storage != nullptr) {
			if (data.size()) {

				optional_guid result;
				signature_range sig_range = boost::make_iterator_range(*sig_storage);
				auto const& data_range = boost::make_iterator_range(data.begin(), data.end());

				int sig_storage_size = get_sig_storage_size();
				for (auto const& current_signature : sig_range) {
					if (std::search(data_range.begin(), data_range.end(),
						current_signature.value.begin(),
						current_signature.value.end()) != data_range.end()
						) {
						result = current_signature.guid;
						update_data_counter(sig_storage_size);
						break;
					}
					update_data_counter(1);
					sig_storage_size--;
				}

				if (result) {
					std::string result_message = std::string("Data is infected!\nMalware GUID: ") 
						+= std::string((const char*)(result->data()));
					return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_INFECTED, 
						std::move(result_message));
				}
				else {
					return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_OK, 
						std::string("Data is clean"));
				}
			}
		}
		return std::make_pair<Scanner::Results, std::string>(Scanner::Results::SCANNER_ERROR, 
			std::string("Signature storage is empty!"));
	}

	int Scanner::get_sig_storage_size() const {
		if (sig_storage == nullptr) return 0;
		else return (int)((*sig_storage).size());
	}

	int Scanner::get_data_counter() {
		g_Lock lock(data_counter_mutex);
		return data_counter;
	}

	void Scanner::reset_data_counter() {
		g_Lock lock(data_counter_mutex);
		data_counter = 0;
	}

	void Scanner::update_data_counter(int how) {
		g_Lock lock(data_counter_mutex);
		data_counter += how;
	}

	extern "C" BOOST_SYMBOL_EXPORT Scanner SimpleScanner;
	Scanner SimpleScanner;
}
