#include "Uuid.h"

#ifdef SHELL_PLATFORM_WINDOWS

#define UUID_SYSTEM_GENERATOR

    #ifdef UUID_SYSTEM_GENERATOR
        #include <objbase.h>
    #endif

    #ifdef UUID_TIME_GENERATOR
        #include <iphlpapi.h>
        #pragma comment(lib, "IPHLPAPI.lib")
    #endif

#elif SHELL_PLATFORM_LINUX

    #ifdef UUID_SYSTEM_GENERATOR
        #include <uuid/uuid.h>
    #endif

#elif SHELL_PLATFORM_MACOS

    #ifdef UUID_SYSTEM_GENERATOR
        #include <CoreFoundation/CFUUID.h>
    #endif

#endif

namespace Shell {
    Uuid Uuid::Create() {
#ifdef SHELL_PLATFORM_WINDOWS
        GUID newId;
        ::CoCreateGuid(&newId);

        std::array<uint8_t, 16> bytes =
                { {
                          (unsigned char)((newId.Data1 >> 24) & 0xFF),
                          (unsigned char)((newId.Data1 >> 16) & 0xFF),
                          (unsigned char)((newId.Data1 >> 8) & 0xFF),
                          (unsigned char)((newId.Data1) & 0xFF),

                          (unsigned char)((newId.Data2 >> 8) & 0xFF),
                          (unsigned char)((newId.Data2) & 0xFF),

                          (unsigned char)((newId.Data3 >> 8) & 0xFF),
                          (unsigned char)((newId.Data3) & 0xFF),

                          newId.Data4[0],
                          newId.Data4[1],
                          newId.Data4[2],
                          newId.Data4[3],
                          newId.Data4[4],
                          newId.Data4[5],
                          newId.Data4[6],
                          newId.Data4[7]
                  } };

        return Uuid{ std::begin(bytes), std::end(bytes) };

#elif SHELL_PLATFORM_LINUX

        uuid_t id;
        uuid_generate(id);

         std::array<uint8_t, 16> bytes =
         { {
               id[0],
               id[1],
               id[2],
               id[3],
               id[4],
               id[5],
               id[6],
               id[7],
               id[8],
               id[9],
               id[10],
               id[11],
               id[12],
               id[13],
               id[14],
               id[15]
            } };

         return Uuid{ std::begin(bytes), std::end(bytes) };

#elif SHELL_PLATFORM_MACOS
         auto newId = CFUUIDCreate(NULL);
         auto bytes = CFUUIDGetUUIDBytes(newId);
         CFRelease(newId);

         std::array<uint8_t, 16> arrbytes =
         { {
               bytes.byte0,
               bytes.byte1,
               bytes.byte2,
               bytes.byte3,
               bytes.byte4,
               bytes.byte5,
               bytes.byte6,
               bytes.byte7,
               bytes.byte8,
               bytes.byte9,
               bytes.byte10,
               bytes.byte11,
               bytes.byte12,
               bytes.byte13,
               bytes.byte14,
               bytes.byte15
            } };
         return Uuid{ std::begin(arrbytes), std::end(arrbytes) };
#else
         return Uuid{};
#endif
    }

    Uuid Uuid::Create(const std::string & id) {
        std::array<uint8_t, 16> bytes =
                { {
                          id[0],
                          id[1],
                          id[2],
                          id[3],
                          id[4],
                          id[5],
                          id[6],
                          id[7],
                          id[8],
                          id[9],
                          id[10],
                          id[11],
                          id[12],
                          id[13],
                          id[14],
                          id[15]
                  } };

        return Uuid{ std::begin(bytes), std::end(bytes) };
    }
}