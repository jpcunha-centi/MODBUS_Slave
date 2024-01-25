/* 
 * Path:    Project/CeNTI_Library/lib/Utils/
 * File:    CeNTI_Data_types.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_DATA_TYPES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_DATA_TYPES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* General library. */
#include <stdlib.h>
/* Include library to use bool type. */
#include <stdbool.h>
/* Include library to use int types. */
#include <stdint.h>
/* Include library to use common definitions. */
#include <stddef.h>
/* Tools defines. */
#include "../Defines/CeNTI_Tools_defines.h"


/* ************************************************************************************ */
/* * Data Types                                                                       * */
/* ************************************************************************************ */
/* ********** Size ****************************************************************** */

/* Define t_size type. */
#if ((!(defined(__DEFINED_size_t)))     && \
     (!(defined(__SIZE_TYPE__)))        )
    typedef uint16_t size_t;
#endif
    
/* ********************************************************************************** */
/* ********** Level ***************************************************************** */
    
/* Create a t_LEVEL type based on a bool type. */
typedef bool t_LEVEL;

/* Define modes to turn a level on/off. */
#define LEVEL_OFF     (false)
#define LEVEL_ON      (true)

/* Define modes to set a level high/low. */
#define LEVEL_LOW     (LEVEL_OFF)
#define LEVEL_HIGH    (LEVEL_ON)

/* Define modes to turn a level enable/disable. */
#define LEVEL_DISABLE (LEVEL_OFF)
#define LEVEL_ENABLE  (LEVEL_ON)

/* ********************************************************************************** */
/* ********** Flag ****************************************************************** */

/* Create a t_FLAG type based on a bool type. */
typedef bool t_FLAG;

/* Define modes to set a flag on/off. */
#define FLAG_OFF (false)
#define FLAG_ON  (true)

/* ********************************************************************************** */
/* ********** Unsigned Data 1 Byte ************************************************** */

/* Union to divide unsigned data with 1 byte of size as big endian. */
typedef union _union_unsigned_1_byte_big_endian {

    /* Divide into bits. */
    struct {
        uint8_t b7 : 1;
        uint8_t b6 : 1;
        uint8_t b5 : 1;
        uint8_t b4 : 1;
        uint8_t b3 : 1;
        uint8_t b2 : 1;
        uint8_t b1 : 1;
        uint8_t b0 : 1;
    } st_bits;

    /* Divide into nibbles. */
    struct {
        uint8_t high : 4;
        uint8_t low  : 4;
    } st_nibbles;

    /* Vector based on bytes. */
    uint8_t vec_u8[1];
    /* Full 1 byte. */
    uint8_t value_u8;

} ut_u1B_big_endian;

/* Union to divide unsigned data with 1 byte of size as little endian. */
typedef union _union_unsigned_1_byte_little_endian {

    /* Divide into bits. */
    struct {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } st_bits;

    /* Divide into nibbles. */
    struct {
        uint8_t low  : 4;
        uint8_t high : 4;
    } st_nibbles;

    /* Vector based on bytes. */
    uint8_t vec_u8[1];
    /* Full 1 byte. */
    uint8_t value_u8;

} ut_u1B_little_endian;

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_u1B_big_endian ut_u1B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_u1B_little_endian ut_u1B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Signed Data 1 Byte **************************************************** */

/* Union to divide signed data with 1 byte of size as big endian. */
typedef union _union_signed_1_byte_big_endian {

    /* Divide into bits. */
    struct {
        uint8_t b7 : 1;
        uint8_t b6 : 1;
        uint8_t b5 : 1;
        uint8_t b4 : 1;
        uint8_t b3 : 1;
        uint8_t b2 : 1;
        uint8_t b1 : 1;
        uint8_t b0 : 1;
    } st_bits;

    /* Divide into nibbles. */
    struct {
        uint8_t high : 4;
        uint8_t low  : 4;
    } st_nibbles;

    /* Vector based on bytes. */
    int8_t  vec_s8[1];
    /* Full 1 byte. */
    int8_t value_s8;

} ut_s1B_big_endian;

/* Union to divide signed data with 1 byte of size as little endian. */
typedef union _union_signed_1_byte_little_endian {

    /* Divide into bits. */
    struct {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } st_bits;

    /* Divide into nibbles. */
    struct {
        uint8_t low  : 4;
        uint8_t high : 4;
    } st_nibbles;

    /* Vector based on bytes. */
    int8_t  vec_s8[1];
    /* Full 1 byte. */
    int8_t value_sq8;

} ut_s1B_little_endian;

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_s1B_big_endian ut_s1B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_s1B_little_endian ut_s1B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Unsigned Data 2 Bytes ************************************************* */

/* Union to divide unsigned data with 2 bytes of size as big endian. */
typedef union _union_unsigned_2_bytes_big_endian {

    /* Divide into bytes. */
    struct {
        ut_u1B_big_endian ut_high_u1B;
        ut_u1B_big_endian ut_low_u1B;
    };

    /* Vector based on bytes. */
    uint8_t  vec_u8[2];
    /* Full 2 bytes. */
    uint16_t value_u16;

} ut_u2B_big_endian;

/* Union to divide unsigned data with 2 bytes of size as little endian. */
typedef union _union_unsigned_2_bytes_little_endian {
    
    /* Divide into bytes. */
    struct {
        ut_u1B_little_endian ut_low_u1B;
        ut_u1B_little_endian ut_high_u1B;
    };

    /* Vector based on bytes. */
    uint8_t  vec_u8[2];
    /* Full 2 bytes. */
    uint16_t value_u16;

} ut_u2B_little_endian;

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_u2B_big_endian ut_u2B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_u2B_little_endian ut_u2B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Signed Data 2 Bytes *************************************************** */

/* Union to divide signed data with 2 bytes of size as big endian. */
typedef union _union_signed_2_bytes_big_endian {

    /* Divide into bytes. */
    struct {
        ut_s1B_big_endian ut_high_s1B;
        ut_s1B_big_endian ut_low_s1B;
    };

    /* Vector based on bytes. */
    int8_t  vec_s8[2];
    /* Full 2 bytes. */
    int16_t value_s16;

} ut_s2B_big_endian;

/* Union to divide signed data with 2 bytes of size as little endian. */
typedef union _union_signed_2_bytes_little_endian {
    
    /* Divide into bytes. */
    struct {
        ut_s1B_little_endian ut_low_s1B;
        ut_s1B_little_endian ut_high_s1B;
    };

    /* Vector based on bytes. */
    int8_t  vec_s8[2];
    /* Full 2 bytes. */
    int16_t value_s16;

} ut_s2B_little_endian;

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_s2B_big_endian ut_s2B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_s2B_little_endian ut_s2B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Unsigned Data 3 Bytes ************************************************* */

#if (defined(__DEFINED_uint24_t))

    /* Union to divide unsigned data with 3 bytes of size as big endian. */
    typedef union _union_unsigned_3_bytes_big_endian {

        /* Divide into bytes. */
        struct {
            ut_u1B_big_endian ut_high_u1B;
            ut_u1B_big_endian ut_mid_u1B;
            ut_u1B_big_endian ut_low_u1B;
        };

        /* Vector based on bytes. */
        uint8_t  vec_u8[3];
        /* Full 3 bytes. */
        uint24_t value_u24;

    } ut_u3B_big_endian;

    /* Union to divide unsigned data with 3 bytes of size as little endian. */
    typedef union _union_unsigned_3_bytes_little_endian {

        /* Divide into bytes. */
        struct {
            ut_u1B_little_endian ut_low_u1B;
            ut_u1B_little_endian ut_mid_u1B;
            ut_u1B_little_endian ut_high_u1B;
        };

        /* Vector based on bytes. */
        uint8_t  vec_u8[3];
        /* Full 3 bytes. */
        uint24_t value_u24;

    } ut_u3B_little_endian;

#else

    /* Union to divide unsigned data with 3 bytes of size as big endian. */
    typedef union _union_unsigned_3_bytes_big_endian {

        /* Divide into bytes. */
        struct {
            ut_u1B_big_endian ut_high_u1B;
            ut_u1B_big_endian ut_mid_u1B;
            ut_u1B_big_endian ut_low_u1B;
        };

        /* Vector based on bytes. */
        uint8_t  vec_u8[3];
        /* Full 3 bytes. */
        uint32_t value_u24;

    } ut_u3B_big_endian;

    /* Union to divide unsigned data with 3 bytes of size as little endian. */
    typedef union _union_unsigned_3_bytes_little_endian {
        
        /* Divide into bytes. */
        struct {
            ut_u1B_little_endian ut_low_u1B;
            ut_u1B_little_endian ut_mid_u1B;
            ut_u1B_little_endian ut_high_u1B;
        };

        /* Vector based on bytes. */
        uint8_t  vec_u8[3];
        /* Full 3 bytes. */
        uint32_t value_u24;

    } ut_u3B_little_endian;

#endif

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_u3B_big_endian ut_u3B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_u3B_little_endian ut_u3B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Signed Data 3 Bytes *************************************************** */
    
#if (defined(__DEFINED_uint24_t))

    /* Union to divide signed data with 3 bytes of size as big endian. */
    typedef union _union_signed_3_bytes_big_endian {
        
        /* Divide into bytes. */
        struct {
            ut_s1B_big_endian ut_high_s1B;
            ut_s1B_big_endian ut_mid_s1B;
            ut_s1B_big_endian ut_low_s1B;
        };

        /* Vector based on bytes. */
        int8_t  vec_s8[3];
        /* Full 3 bytes. */
        int24_t value_s24;

    } ut_s3B_big_endian;

    /* Union to divide signed data with 3 bytes of size as little endian. */
    typedef union _union_signed_3_bytes_little_endian {
        
        /* Divide into bytes. */
        struct {
            ut_s1B_little_endian ut_low_s1B;
            ut_s1B_little_endian ut_mid_s1B;
            ut_s1B_little_endian ut_high_s1B;
        };

        /* Vector based on bytes. */
        int8_t  vec_s8[3];
        /* Full 3 bytes. */
        int24_t value_s24;

    } ut_s3B_little_endian;

#else
    
    /* Union to divide signed data with 3 bytes of size as big endian. */
    typedef union _union_signed_3_bytes_big_endian {
        
        /* Divide into bytes. */
        struct {
            ut_s1B_big_endian ut_high_s1B;
            ut_s1B_big_endian ut_mid_s1B;
            ut_s1B_big_endian ut_low_s1B;
        };

        /* Vector based on bytes. */
        int8_t  vec_s8[3];
        /* Full 3 bytes. */
        int32_t value_s24;

    } ut_s3B_big_endian;

    /* Union to divide signed data with 3 bytes of size as little endian. */
    typedef union _union_signed_3_bytes_little_endian {
        
        /* Divide into bytes. */
        struct {
            ut_s1B_little_endian ut_low_s1B;
            ut_s1B_little_endian ut_mid_s1B;
            ut_s1B_little_endian ut_high_s1B;
        };

        /* Vector based on bytes. */
        int8_t  vec_s8[3];
        /* Full 3 bytes. */
        int32_t value_s24;

    } ut_s3B_little_endian;

#endif

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_s3B_big_endian ut_s3B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_s3B_little_endian ut_s3B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Unsigned Data 4 Bytes ************************************************* */

/* Union to divide unsigned data with 4 bytes of size as big endian. */
typedef union _union_unsigned_4_bytes_big_endian {

    /* Divide into data with 2 bytes of size. */
    struct {
        ut_u2B_big_endian ut_high_u2B;
        ut_u2B_big_endian ut_low_u2B;
    };

    /* Vector based on bytes. */
    uint8_t  vec_u8[4];
    /* Full 4 bytes. */
    uint32_t value_u32;
    /* Value converted into float type. */
    float    value_f;

} ut_u4B_big_endian;

/* Union to divide unsigned data with 4 bytes of size as little endian. */
typedef union _union_unsigned_4_bytes_little_endian {
    
    /* Divide into data with 2 bytes of size. */
    struct {
        ut_u2B_little_endian ut_low_u2B;
        ut_u2B_little_endian ut_high_u2B;
    };

    /* Vector based on bytes. */
    uint8_t  vec_u8[4];
    /* Full 4 bytes. */
    uint32_t value_u32;
    /* Value converted into float type. */
    float    value_f;

} ut_u4B_little_endian;

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef ut_u4B_big_endian ut_u4B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef ut_u4B_little_endian ut_u4B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */
/* ********** Signed Data 4 Bytes *************************************************** */

/* Union to divide signed data with 4 bytes of size as big endian. */
typedef union _union_signed_4_bytes_big_endian {

    /* Divide into data with 2 bytes of size. */
    struct {
        ut_s2B_big_endian ut_high_s2B;
        ut_s2B_big_endian ut_low_s2B;
    };

    /* Vector based on bytes. */
    uint8_t  vec_s8[4];
    /* Full 4 bytes. */
    int32_t value_s32;
    /* Value converted into float type. */
    float    value_f;

} st_s4B_big_endian;

/* Union to divide signed data with 4 bytes of size as little endian. */
typedef union _union_signed_4_bytes_little_endian {
    
    /* Divide into data with 2 bytes of size. */
    struct {
        ut_s2B_little_endian ut_low_s2B;
        ut_s2B_little_endian ut_high_s2B;
    };

    /* Vector based on bytes. */
    uint8_t  vec_s8[4];
    /* Full 4 bytes. */
    int32_t value_s32;
    /* Value converted into float type. */
    float    value_f;

} st_s4B_little_endian;

#if (CENTI_ENDIANNESS == CENTI_ENDIANNESS_BIG)
    typedef st_s4B_big_endian st_s4B;
#elif (CENTI_ENDIANNESS == CENTI_ENDIANNESS_LITTLE)
    typedef st_s4B_little_endian st_s4B;
#else
    #error "CENTI_ENDIANNESS is not defined"
#endif

/* ********************************************************************************** */


#endif /* __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_DATA_TYPES_H__ */

/* -- End of file -- */
