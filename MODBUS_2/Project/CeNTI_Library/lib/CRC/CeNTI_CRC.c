/* 
 * Path:    Project/CeNTI_Library/lib/CRC/
 * File:    CeNTI_CRC.c
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_CRC_defines.h"
#if (defined(__CENTI_CRC_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_CRC.h"


/* ************************************************************************************ */
/* * Constants                                                                        * */
/* ************************************************************************************ */
/* ********** CRC 8bits ********** */
/* Vector with initial value. */
const uint8_t CRC_8BITS_INIT_VEC[CRC_8BITS_TOTAL] =\
    { FOREACH_CRC_8BITS(GENERATE_CRC_8_INIT) };

/* Vector with polynomial value. */
const uint8_t CRC_8BITS_POLY_VEC[CRC_8BITS_TOTAL] =\
    { FOREACH_CRC_8BITS(GENERATE_CRC_8_POLY) };

/* Vector with XOR value for output CRC. */
const uint8_t CRC_8BITS_XOR_OUT_VEC[CRC_8BITS_TOTAL] =\
    { FOREACH_CRC_8BITS(GENERATE_CRC_8_XOROUT) };

/* Vector indicating if reverse input is needed. */
const bool CRC_8BITS_REF_IN_VEC[CRC_8BITS_TOTAL] =\
    { FOREACH_CRC_8BITS(GENERATE_CRC_8_REFIN) };

/* Vector indicating if reverse output is needed. */
const bool CRC_8BITS_REF_OUT_VEC[CRC_8BITS_TOTAL] =\
    { FOREACH_CRC_8BITS(GENERATE_CRC_8_REFOUT) };

/* ********** CRC 16bits ********** */
/* Vector with initial value. */
const uint16_t CRC_16BITS_INIT_VEC[CRC_16BITS_TOTAL] =\
    { FOREACH_CRC_16BITS(GENERATE_CRC_16_INIT) };

/* Vector with polynomial value. */
const uint16_t CRC_16BITS_POLY_VEC[CRC_16BITS_TOTAL] =\
    { FOREACH_CRC_16BITS(GENERATE_CRC_16_POLY) };

/* Vector with XOR value for output CRC. */
const uint16_t CRC_16BITS_XOR_OUT_VEC[CRC_16BITS_TOTAL] =\
    { FOREACH_CRC_16BITS(GENERATE_CRC_16_XOROUT) };

/* Vector indicating if reverse input is needed. */
const bool CRC_16BITS_REF_IN_VEC[CRC_16BITS_TOTAL] =\
    { FOREACH_CRC_16BITS(GENERATE_CRC_16_REFIN) };

/* Vector indicating if reverse output is needed. */
const bool CRC_16BITS_REF_OUT_VEC[CRC_16BITS_TOTAL] =\
    { FOREACH_CRC_16BITS(GENERATE_CRC_16_REFOUT) };


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
uint8_t CENTI_CRC_8__Calculate(et_CRC_8BITS   et_crc,\
                               uint8_t *const data_vec,\
                               size_t         data_vec_size)
{
    ut_u1B  ut_crc_u1B       = {};
    ut_u1B  ut_final_crc_u1B = {};
    uint8_t crc_msb_u8       = 0;
    uint8_t data_msb_u8      = 0;
    uint8_t bit_shift_u8     = 0;
    
    ut_crc_u1B.value_u8 = CRC_8BITS_INIT_VEC[et_crc];
    
    for (uint8_t data_idx_u8=0; data_idx_u8<data_vec_size; data_idx_u8++)
    {
        for (uint8_t bit_idx_u8=0; bit_idx_u8<8; bit_idx_u8++)
        {
            /* Reflect input bits. */
            if (CRC_8BITS_REF_IN_VEC[et_crc])
            {
                bit_shift_u8 = (uint8_t)(1<<bit_idx_u8);
            }
            else
            {
                bit_shift_u8 = (uint8_t)(1<<(7-bit_idx_u8));
            }
            
            data_msb_u8 = (data_vec[data_idx_u8]&bit_shift_u8) ? 1 : 0;
            crc_msb_u8  = (ut_crc_u1B.value_u8 & 0x80) ? 1 : 0;
            
            if (data_msb_u8 ^ crc_msb_u8)
            {
                ut_crc_u1B.value_u8 =\
                        (uint8_t)((ut_crc_u1B.value_u8<<1)^CRC_8BITS_POLY_VEC[et_crc]);
            }
            else
            {
                ut_crc_u1B.value_u8 <<= 1;
            }
        }
    }
    
    /* Reflect output bits. */
    if (CRC_8BITS_REF_OUT_VEC[et_crc])
    {
    	ut_final_crc_u1B.st_bits.b0 = ut_crc_u1B.st_bits.b7;
    	ut_final_crc_u1B.st_bits.b1 = ut_crc_u1B.st_bits.b6;
    	ut_final_crc_u1B.st_bits.b2 = ut_crc_u1B.st_bits.b5;
    	ut_final_crc_u1B.st_bits.b3 = ut_crc_u1B.st_bits.b4;
    	ut_final_crc_u1B.st_bits.b4 = ut_crc_u1B.st_bits.b3;
    	ut_final_crc_u1B.st_bits.b5 = ut_crc_u1B.st_bits.b2;
    	ut_final_crc_u1B.st_bits.b6 = ut_crc_u1B.st_bits.b1;
    	ut_final_crc_u1B.st_bits.b7 = ut_crc_u1B.st_bits.b0;
    }
    else
    {
        ut_final_crc_u1B = ut_crc_u1B;
    }
	
    ut_final_crc_u1B.value_u8 ^= CRC_8BITS_XOR_OUT_VEC[et_crc];
    
    return ut_final_crc_u1B.value_u8;
}

uint16_t CENTI_CRC_16__Calculate(et_CRC_16BITS  et_crc,\
                                 uint8_t *const data_vec,\
                                 size_t         data_vec_size)
{
    ut_u2B  ut_crc_u2B       = {};
    ut_u2B  ut_final_crc_u2B = {};
    uint8_t bit_shift_u8     = 0;
    uint8_t data_bit_u8      = 0;
    uint8_t crc_bit_u8       = 0;
    uint8_t crc_carry_u8     = 0;
    
    ut_crc_u2B.value_u16 = CRC_16BITS_INIT_VEC[et_crc];
    
    for (uint8_t data_idx_u8=0; data_idx_u8<data_vec_size; data_idx_u8++)
    {
        for (uint8_t bit_idx_u8=0; bit_idx_u8<8; bit_idx_u8++)
        {
            /* Reflect input bits. */
            if (CRC_16BITS_REF_IN_VEC[et_crc])
            {
                bit_shift_u8 = (uint8_t)(1<<bit_idx_u8);
            }
            else
            {
                bit_shift_u8 = (uint8_t)(1<<(7-bit_idx_u8));
            }
            
            data_bit_u8  = ((data_vec[data_idx_u8]&bit_shift_u8) ? 1 : 0);
            crc_bit_u8   = ut_crc_u2B.ut_high_u1B.value_u8 >> 7;
            crc_carry_u8 = ut_crc_u2B.ut_low_u1B.value_u8 >> 7;
            
            ut_crc_u2B.ut_low_u1B.value_u8 <<= 1;
            ut_crc_u2B.ut_high_u1B.value_u8 <<= 1;
            ut_crc_u2B.ut_high_u1B.value_u8 |= crc_carry_u8;
            
            if ((data_bit_u8 ^ crc_bit_u8) != 0)
            {
                ut_crc_u2B.value_u16 ^= CRC_16BITS_POLY_VEC[et_crc];
            }
        }
    }
    
    /* Reflect output bits. */
    if (CRC_16BITS_REF_OUT_VEC[et_crc])
    {
        ut_final_crc_u2B.ut_low_u1B.st_bits.b0 = ut_crc_u2B.ut_high_u1B.st_bits.b7;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b1 = ut_crc_u2B.ut_high_u1B.st_bits.b6;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b2 = ut_crc_u2B.ut_high_u1B.st_bits.b5;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b3 = ut_crc_u2B.ut_high_u1B.st_bits.b4;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b4 = ut_crc_u2B.ut_high_u1B.st_bits.b3;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b5 = ut_crc_u2B.ut_high_u1B.st_bits.b2;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b6 = ut_crc_u2B.ut_high_u1B.st_bits.b1;
        ut_final_crc_u2B.ut_low_u1B.st_bits.b7 = ut_crc_u2B.ut_high_u1B.st_bits.b0;
        
        ut_final_crc_u2B.ut_high_u1B.st_bits.b0 = ut_crc_u2B.ut_low_u1B.st_bits.b7;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b1 = ut_crc_u2B.ut_low_u1B.st_bits.b6;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b2 = ut_crc_u2B.ut_low_u1B.st_bits.b5;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b3 = ut_crc_u2B.ut_low_u1B.st_bits.b4;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b4 = ut_crc_u2B.ut_low_u1B.st_bits.b3;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b5 = ut_crc_u2B.ut_low_u1B.st_bits.b2;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b6 = ut_crc_u2B.ut_low_u1B.st_bits.b1;
        ut_final_crc_u2B.ut_high_u1B.st_bits.b7 = ut_crc_u2B.ut_low_u1B.st_bits.b0;
    }
    else
    {
        ut_final_crc_u2B = ut_crc_u2B;
    }
    
    ut_final_crc_u2B.value_u16 ^= CRC_16BITS_XOR_OUT_VEC[et_crc];
    
    return ut_final_crc_u2B.value_u16;
}


#endif /* (defined(__CENTI_CRC_IN_USE__)) */

/* -- End of file -- */
