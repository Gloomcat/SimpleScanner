#pragma once

#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "bytes.h"

#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>

namespace SimpleScanner {
	struct Signature
	{
	public:
		bool Equal(Signature const& other) const;

	public:
		byte_string value;
		byte_string guid;
	};

	bool operator == (Signature const& l, Signature const& r);

	typedef boost::unordered_set<Signature> signature_store;
	typedef std::unique_ptr<signature_store> signature_store_ptr;
}

namespace boost {
	size_t hash_value(SimpleScanner::Signature const& sig);
}

#endif