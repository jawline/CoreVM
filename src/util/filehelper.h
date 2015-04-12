#ifndef _FILE_HELPER_DEF_H_
#define _FILE_HELPER_DEF_H_
#include <cstdint>

class FileHelper {
public:
	static bool readFileToMemory(char const* filename, uint8_t*& resultDest, unsigned long& sizeDest);
};

#endif //_FILE_HELPER_DEF_H_