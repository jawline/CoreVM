#ifndef _CORE_UTILS_DEF_H_
#define _CORE_UTILS_DEF_H_
#include <cstdint>

class CoreUtils {
public:
  static inline void intFromBuffer(int32_t& dest, uint8_t* buffer) {
  	dest = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
  }
  static inline void uintFromBuffer(uint32_t& dest, uint8_t* buffer) {
  	dest = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
  }
  static inline void ushortFromBuffer(uint16_t& dest, uint8_t* buffer) {
    dest = buffer[0] | (buffer[1] << 8);
  }
  static inline void byteFromBuffer(uint8_t& dest, uint8_t* buffer) {
    dest = buffer[0];
  }
  static inline void uintToBuffer(uint32_t const& src, uint8_t* buffer) {
    ((uint32_t*)buffer)[0] = src;
  }
};

#endif //_CORE_UTILS_DEF_H_