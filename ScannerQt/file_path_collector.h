#pragma once

#ifndef FILE_PATH_COLLECTOR_H
#define FILE_PATH_COLLECTOR_H

#include <boost\filesystem\path.hpp>
#include <boost\filesystem\operations.hpp>
#include <boost\unordered_set.hpp>

#include "..\Scanner\i_scanner.h"

namespace SimpleScanner {
	
	typedef std::vector<boost::filesystem::path> input_path_store;
	typedef std::shared_ptr<input_path_store> input_path_store_ptr;
	typedef boost::unordered_set<boost::filesystem::path> unique_path_store;
	typedef std::pair<IScanner::Results, std::string> result_type;
	typedef std::function<void(const unique_path_store&)> file_path_collector_callback;

	class FilePathCollector
	{
	public:
		std::pair<IScanner::Results, std::string> collect_file_paths(
			input_path_store const& path_store, unique_path_store& unique_paths) {

			for (auto const& path : path_store) {

				if (!path.empty() && boost::filesystem::exists(path) && !boost::filesystem::is_empty(path)) {

					boost::system::error_code ec;

					if (boost::filesystem::is_directory(path)) {

						for (boost::filesystem::recursive_directory_iterator rdi(path, ec), rdi_end;
						rdi != rdi_end; rdi.increment(ec)) {

							if (ec) {

								//TODO: handle cases when directory or file access is not permitted

								if (rdi.level())
									rdi.pop();
								continue;
							}

							auto const& current_path = rdi->path();
							if (boost::filesystem::is_regular_file(current_path))
								unique_paths.insert(current_path);
						}

					}
					else if (boost::filesystem::is_regular_file(path)) {

						unique_paths.insert(path);

					}
					else {

						assert(!"unknown type of file");

					}
				}
			}

			fpc_callback(unique_paths);

			return std::make_pair<IScanner::Results, std::string>(
				IScanner::Results::SCANNER_OK, std::string("Collected unique files info!"));
		}

		FilePathCollector(file_path_collector_callback&& callback = std::move([](const unique_path_store&) {}))
			: fpc_callback(std::move(callback)) {}

		~FilePathCollector() = default;
		FilePathCollector(const FilePathCollector& rhs) = delete;
		FilePathCollector& operator=(const FilePathCollector& rhs) = delete;

	private:

		file_path_collector_callback fpc_callback;
	};

}

#endif
