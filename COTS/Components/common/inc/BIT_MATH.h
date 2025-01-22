//
// Created by ali on 12/17/24.
//

#ifndef BIT_MATH_H
#define BIT_MATH_H

// Bitwise operations
#define SET_BIT(REG, BIT) ((REG) |= (1 << BIT))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(1 << BIT))
#define GET_BIT(REG, BIT) (((REG) >> (BIT)) & (1))
#define TOGGLE_BIT(REG, BIT) (((REG) ^= (1 << BIT)))

// Nibble operations
#define SET_HIGH_NIB(REG) ((REG) |= 0xF0)
#define CLR_HIGH_NIB(REG) ((REG) &= 0x0F)
#define GET_HIGH_NIB(REG) (((REG) & 0xF0) >> 4)
#define TGL_HIGH_NIB(REG) ((REG) ^= 0xF0)
#define SET_LOW_NIB(REG) ((REG) |= 0x0F)
#define CLR_LOW_NIB(REG) ((REG) &= 0xF0)
#define GET_LOW_NIB(REG) ((REG) & 0x0F)
#define TGL_LOW_NIB(REG) ((REG) ^= 0x0F)

// Assignment operations
#define ASSIGN_REG(REG, VALUE) ((REG) = (VALUE))
#define ASSIGN_HIGH_NIB(REG, VALUE) ((REG) = ((REG) & 0x0F) | ((VALUE & 0x0F) << 4))
#define ASSIGN_LOW_NIB(REG, VALUE) ((REG) = ((REG) & 0xF0) | (VALUE & 0x0F))

// Shift operations
#define RSHFT_REG(REG, NO) ((REG) >>= (NO))
#define LSHFT_REG(REG, NO) ((REG) <<= (NO))
#define CRSHFT_REG(REG, NO) ((REG) = ((REG) >> (NO)) | ((REG) << (8 - (NO))))
#define CLSHFT_REG(REG, NO) ((REG) = ((REG) << (NO)) | ((REG) >> (8 - (NO))))

#endif // BIT_MATH_H
