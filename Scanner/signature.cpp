#include "stdafx.h"

#include "signature.h"

namespace SimpleScanner {
	bool Signature::Equal(Signature const& other) const {
		return value == other.value;
	}

	bool operator == (Signature const& l, Signature const& r) {
		return l.Equal(r);
	}
}

namespace boost {
	size_t hash_value(SimpleScanner::Signature const& sig) {
		return hash_value(sig.value);
	}
}
