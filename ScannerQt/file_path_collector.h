#pragma once

#ifndef FILE_PATH_COLLECTOR_H
#define FILE_PATH_COLLECTOR_H

#include <boost\filesystem\path.hpp>
#include <boost\filesystem\operations.hpp>
#include <boost\unordered_set.hpp>

namespace SimpleScanner {
	
	typedef std::vector<boost::filesystem::path> input_path_store;
	typedef std::shared_ptr<input_path_store> input_path_store_ptr;
	typedef boost::unordered_set<boost::filesystem::path> unique_path_store;

	class ScannerFilePathCollector
	{
	public:
		static unique_path_store collect_file_paths(input_path_store const& path_store) {

			unique_path_store unique_path_store;

			for (auto const& path : path_store) {

				if (!path.empty() && boost::filesystem::exists(path) && !boost::filesystem::is_empty(path)) {
					
					boost::system::error_code ec;
					
					if (boost::filesystem::is_directory(path)) {

						for (boost::filesystem::recursive_directory_iterator rdi(path, ec), rdi_end; 
							rdi != rdi_end; rdi.increment(ec)) {

							if (ec) {

								if (rdi.level())
									rdi.pop();
								continue;
							}

							auto const& current_path = rdi->path();
							if (boost::filesystem::is_regular_file(current_path))
								unique_path_store.insert(current_path);
						}

					}
					else if (boost::filesystem::is_regular_file(path)) {

						unique_path_store.insert(path);

					}
					else {

						assert(!"unknown type of file");

					}
				}
			}

			return unique_path_store;
		}
	};

}

#endif
