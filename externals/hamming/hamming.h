/*
================================================================================
 Plik: hamming.h
--------------------------------------------------------------------------------
 Autorzy:       Andrzej Kuroœ, £ukasz Krzak (uzupe³nienie dokumentacji)
 Projekt:       modu³ uniwersalny
 Kompilator:    GCC
 Hardware:      AVR, ARM
 Doc:           doxygen 1.4.3
--------------------------------------------------------------------------------
 Zawiera:     funkcje obs³uguj¹ce kodowanie Hamming'a
--------------------------------------------------------------------------------
 Komentarze:

================================================================================
*/

#ifndef HAMMING_H
#define HAMMING_H

#include <stdint.h>


/** \defgroup hamming Hamming encoding routines
 *  \code
 *  #include "hamming.h"
 *   \endcode
 *
 *  This module delivers functions that handle channel encoding and decoding using
 *  modified Hamming (7,4) encoding. The modification adds additional bit to every
 *  seven bits of the codeword to balance it (make the number of ones and zeros more
 *  even).
 *  The encoding has efficiency of 50% and guarantees detection of two bit errors and
 *  correction of one bit error across a single byte of information.
 *
 *  This module uses LUTs for speed.
 *
 *  <b> Usage. </b>
 *
 *  To encode data use \ref HAMMING_EncodeBalanced function. To decode use
 *  \ref HAMMING_DecodeBalanced.
 *
*/
/*@{*/

/**
 *  Encodes a single byte into 2-byte codeword.
 *
 *  \param data byte to encode
 *  \return Hamming codeword
*/
uint16_t HAMMING_EncodeBalanced(uint8_t data);

/**
 *  Decodes data previously encoded with \ref HAMMING_EncodeBalanced
 *
 *  \param input received codeword to decode
    \param data pointer to a variable, where decoded byte will be stored
    \return 0 - the codeword was decoded and no error was found
            1 - the codeword was decoded, single error was detected and corrected
            2 - at least two bits were bad, unable to decode
*/
uint16_t HAMMING_DecodeBalanced(uint16_t input, uint8_t *data);

/*@}*/

/*! \file hamming.h
    \brief Hamming channel encoding and decoding

	This module delivers functions that handle channel encoding and decoding using
    modified Hamming (7,4) encoding.
*/

#endif // HAMMING_H
