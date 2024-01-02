#include "Compression.hpp"
#include <zlib.h>
#include "Log.hpp"

std::optional<std::vector<uint8_t>> Compression::DecompressGZip(std::vector<uint8_t> compressedBytes)
{
	std::vector<uint8_t> ret;
	if (compressedBytes.size() == 0) {
		ELOG_WARNING("Compressed bytes size is 0");
		return ret;
	}

	size_t full_length = compressedBytes.size();
	size_t half_length = compressedBytes.size() / 2;

	size_t uncompLength = full_length;
	std::unique_ptr<char> uncomp(new char[uncompLength]);

	z_stream strm;
	strm.next_in = (Bytef*)compressedBytes.data();
	strm.avail_in = (uInt)compressedBytes.size();
	strm.total_out = 0;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;

	bool done = false;

	if (inflateInit(&strm) != Z_OK) {
		ELOG_ERROR("Cannot initialize zlib inflation stream");
		return std::nullopt;
	}

	while (!done) {
		// If our output buffer is too small  
		if (strm.total_out >= uncompLength) {
			// Increase size of output buffer  
			char* uncomp2 = new char[uncompLength + half_length];
			memcpy(uncomp2, uncomp.get(), uncompLength);
			uncompLength += half_length;
			uncomp.reset(uncomp2);
		}

		strm.next_out = (Bytef*)(uncomp.get() + strm.total_out);
		strm.avail_out = (uInt)(uncompLength - strm.total_out);

		// Inflate another chunk.  
		int err = inflate(&strm, Z_SYNC_FLUSH);
		if (err == Z_STREAM_END) done = true;
		else if (err != Z_OK) {
			ELOG_ERROR("Cannot inflate zlib stream, error ", err, " - ", strm.msg);
			break;
		}
	}

	if (inflateEnd(&strm) != Z_OK) {
		ELOG_ERROR("Cannot deinitialize zlib inflation stream");
		return std::nullopt;
	}

	for (size_t i = 0; i < strm.total_out; ++i) {
		ret.push_back(uncomp.get()[i]);
	}

	return ret;
}
