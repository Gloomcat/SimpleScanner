#pragma once

#ifndef SCANNER_MAPPED_FILE_H
#define SCANNER_MAPPED_FILE_H

#include "bytes.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace SimpleScanner {
	
	class MappedFileForRead {
	
	public:
		raw_const_byte_data get_data() const {
			return static_cast<raw_const_byte_data>(region.get_address());
		}

		size_t get_data_size() const {
			return region.get_size();
		}

		byte_iterator_range get_range() const
		{
			byte_const_ptr const data(get_data());
			return boost::make_iterator_range(data, data + get_data_size());
		}

		MappedFileForRead(boost::filesystem::path const& file_path)
			: mapping(file_path.string().c_str(), boost::interprocess::read_only) 
			, region(mapping, boost::interprocess::read_only) {}

		boost::interprocess::file_mapping const mapping;
		boost::interprocess::mapped_region const region;
	};
}

#endif

