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
 Zawiera:     funkcje obs³uguj¹ce zbalansowane kodowanie Hamming'a
--------------------------------------------------------------------------------
 Komentarze:

================================================================================
*/

#include "hamming.h"

//Prototypy wewnetrzne
static uint16_t HAMMING_XorBits (uint16_t data, uint16_t pattern);
static uint16_t HAMMING_GetSyndrome (uint16_t CodeWord);
static uint16_t HAMMING_FindCodePosition (uint16_t Code, uint8_t *Data);
static uint16_t HAMMING_DecodeSystematic (uint16_t input, uint16_t *d);

/// Tablica u¿ywana do kodowania
static const uint16_t HAMMING_EncodeLUT[256] = {
	0x2034, 0x207F, 0x1B5, 0x21D4, 0x21E7, 0x21F9, 0x1FE, 0x2B6,
	0x22D7, 0x22E4, 0x22FA, 0x2FD, 0x31D, 0x32E, 0x330, 0x2337,
	0x234F, 0x2351, 0x356, 0x2362, 0x365, 0x37B, 0x24B7, 0x4D6,
	0x4E5, 0x4FB, 0x24FC, 0x251C, 0x252F, 0x2531, 0x536, 0x54E,
	0x550, 0x2557, 0x563, 0x2564, 0x257A, 0x261F, 0x262C, 0x2632,
	0x635, 0x64D, 0x653, 0x2654, 0x660, 0x2667, 0x2679, 0x780,
	0x2787, 0x2799, 0x79E, 0x27AA, 0x7AD, 0x7B3, 0x27B4, 0x7CB,
	0x27CC, 0x27D2, 0x27E1, 0x8BC, 0x28DD, 0x28EE, 0x28F0, 0x8F7,
	0x917, 0x924, 0x93A, 0x293D, 0x2945, 0x295B, 0x95C, 0x2968,
	0x96F, 0x971, 0xA14, 0xA27, 0xA39, 0x2A3E, 0x2A46, 0x2A58,
	0xA5F, 0x2A6B, 0xA6C, 0xA72, 0xB8C, 0xB92, 0x2B95, 0xBA1,
	0x2BA6, 0x2BB8, 0x2BC0, 0xBC7, 0xBD9, 0xBEA, 0x2C15, 0x2C26,
	0x2C38, 0xC3F, 0xC47, 0xC59, 0x2C5E, 0xC6A, 0x2C6D, 0x2C73,
	0x2D8D, 0x2D93, 0xD94, 0x2DA0, 0xDA7, 0xDB9, 0xDC1, 0x2DC6,
	0x2DD8, 0x2DEB, 0x2E8E, 0x2E90, 0xE97, 0x2EA3, 0xEA4, 0xEBA,
	0xEC2, 0x2EC5, 0x2EDB, 0x2EE8, 0xEF1, 0x2F08, 0xF0F, 0xF11,
	0xF22, 0x2F43, 0x30BD, 0x10DC, 0x10EF, 0x10F1, 0x30F6, 0x3116,
	0x3125, 0x313B, 0x113C, 0x1144, 0x115A, 0x315D, 0x1169, 0x316E,
	0x3170, 0x3215, 0x3226, 0x3238, 0x123F, 0x1247, 0x1259, 0x325E,
	0x126A, 0x326D, 0x3273, 0x338D, 0x3393, 0x1394, 0x33A0, 0x13A7,
	0x13B9, 0x13C1, 0x33C6, 0x33D8, 0x33EB, 0x1414, 0x1427, 0x1439,
	0x343E, 0x3446, 0x3458, 0x145F, 0x346B, 0x146C, 0x1472, 0x158C,
	0x1592, 0x3595, 0x15A1, 0x35A6, 0x35B8, 0x35C0, 0x15C7, 0x15D9,
	0x15EA, 0x168F, 0x1691, 0x3696, 0x16A2, 0x36A5, 0x36BB, 0x36C3,
	0x16C4, 0x16DA, 0x16E9, 0x1709, 0x370E, 0x3710, 0x3723, 0x1742,
	0x381F, 0x382C, 0x3832, 0x1835, 0x184D, 0x1853, 0x3854, 0x1860,
	0x3867, 0x3879, 0x3987, 0x3999, 0x199E, 0x39AA, 0x19AD, 0x19B3,
	0x19CB, 0x39CC, 0x39D2, 0x39E1, 0x3A84, 0x3A9A, 0x1A9D, 0x3AA9,
	0x1AAE, 0x1AB0, 0x1AC8, 0x3ACF, 0x3AD1, 0x3AE2, 0x3B02, 0x1B05,
	0x1B1B, 0x1B28, 0x3B49, 0x1C85, 0x1C9B, 0x3C9C, 0x1CA8, 0x3CAF,
	0x3CB1, 0x3CC9, 0x1CCE, 0x1CD0, 0x1CE3, 0x1D03, 0x3D04, 0x3D1A,
	0x3D29, 0x1D48, 0x1E00, 0x3E07, 0x3E19, 0x3E2A, 0x1E4B, 0x3F81
};

/// Tablica u¿ywana do dekodowania
static const uint16_t HAMMING_IntermediateLUT[256] = {
	0x7, 0xF, 0x17, 0x1B, 0x1D, 0x1E, 0x1F, 0x27,
	0x2B, 0x2D, 0x2E, 0x2F, 0x33, 0x35, 0x36, 0x37,
	0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x47, 0x4B,
	0x4D, 0x4E, 0x4F, 0x53, 0x55, 0x56, 0x57, 0x59,
	0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x63, 0x65, 0x66,
	0x67, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x70,
	0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7A, 0x7C, 0x87, 0x8B, 0x8D, 0x8E, 0x8F,
	0x93, 0x95, 0x96, 0x97, 0x99, 0x9A, 0x9B, 0x9C,
	0x9D, 0x9E, 0xA3, 0xA5, 0xA6, 0xA7, 0xA9, 0xAA,
	0xAB, 0xAC, 0xAD, 0xAE, 0xB1, 0xB2, 0xB3, 0xB4,
	0xB5, 0xB6, 0xB8, 0xB9, 0xBA, 0xBC, 0xC3, 0xC5,
	0xC6, 0xC7, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE,
	0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD8, 0xD9,
	0xDA, 0xDC, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
	0xE8, 0xE9, 0xEA, 0xEC, 0xEE, 0xF0, 0xF1, 0xF2,
	0xF4, 0xF8, 0x107, 0x10B, 0x10D, 0x10E, 0x10F, 0x113,
	0x115, 0x116, 0x117, 0x119, 0x11A, 0x11B, 0x11C, 0x11D,
	0x11E, 0x123, 0x125, 0x126, 0x127, 0x129, 0x12A, 0x12B,
	0x12C, 0x12D, 0x12E, 0x131, 0x132, 0x133, 0x134, 0x135,
	0x136, 0x138, 0x139, 0x13A, 0x13C, 0x143, 0x145, 0x146,
	0x147, 0x149, 0x14A, 0x14B, 0x14C, 0x14D, 0x14E, 0x151,
	0x152, 0x153, 0x154, 0x155, 0x156, 0x158, 0x159, 0x15A,
	0x15C, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x168,
	0x169, 0x16A, 0x16C, 0x170, 0x171, 0x172, 0x174, 0x178,
	0x183, 0x185, 0x186, 0x187, 0x189, 0x18A, 0x18B, 0x18C,
	0x18D, 0x18E, 0x191, 0x192, 0x193, 0x194, 0x195, 0x196,
	0x198, 0x199, 0x19A, 0x19C, 0x1A1, 0x1A2, 0x1A3, 0x1A4,
	0x1A5, 0x1A6, 0x1A8, 0x1A9, 0x1AA, 0x1AC, 0x1B0, 0x1B1,
	0x1B2, 0x1B4, 0x1B8, 0x1C1, 0x1C2, 0x1C3, 0x1C4, 0x1C5,
	0x1C6, 0x1C8, 0x1C9, 0x1CA, 0x1CC, 0x1D0, 0x1D1, 0x1D2,
	0x1D4, 0x1D8, 0x1E0, 0x1E1, 0x1E2, 0x1E4, 0x1E8, 0x1F0
};


//Stala tablica w pamieci programu o tej wlasnosci, ze
//wartosc pod indeksem i jest liczb¹ jedynek 4-bitowego indeksu i
const uint8_t LUT_OnesCount [] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};


/****************************************************************
  Name        :   HAMMING_XorBits
  Parameters  :   [i] - input, [o] - output, [i/o] - input/output
    [i]   uint16_t  data    - dana do wuyznaczenia parzystosci
    [i]   uint16_t  pattern - maska (do obliczenia parzystosci wchodzi
            bit z data, dla ktorego odpowiadajacy bit z pattern jest ustawiony
  Return value:
    0 - byla parzysta liczba jedynek
    1 - byla nieparzysta liczba jedynek
  Description :
    Wyznacza selektywnie parzystosc (odd-parity)
****************************************************************/
static uint16_t HAMMING_XorBits (uint16_t data, uint16_t pattern)
{
  uint16_t jedynki, wynik = 0;
  jedynki = data & pattern;
  wynik = LUT_OnesCount[jedynki & 0x0F] +
          LUT_OnesCount[(jedynki>>4) & 0x0F] +
          LUT_OnesCount[(jedynki>>8) & 0x0F] +
          LUT_OnesCount[(jedynki>>12) & 0x03];
  
  return wynik & 1;

} /* HAMMING_XorBits */

/****************************************************************
  Name        :   HAMMING_GetSyndrome
  Parameters  :   [i] - input, [o] - output, [i/o] - input/output
    [i]   uint16_t CodeWord - 14-bitowe slowo (zapisane na 16-bitach)
            dla ktorego obliczany jest syndrom
  Return value:
    0 - je¿eli CodeWord jest poprawnym s³owem kodowym
    inna wartosc - numer blednego bitu (LSB ma numer 1)
  Description :
    Wyznacza syndrom s³owa (detekcja bledu na 1 bicie).
    Rozdzial 3.2 dokumentacji
****************************************************************/
static uint16_t HAMMING_GetSyndrome (uint16_t CodeWord)
{
	uint16_t r;
	r = HAMMING_XorBits (CodeWord, 0x5555 & 0x1FFF) |
	 (HAMMING_XorBits (CodeWord, 0x6666 & 0x1FFF) << 1) |
	 (HAMMING_XorBits (CodeWord, 0x7878 & 0x1FFF) << 2) |
	 (HAMMING_XorBits (CodeWord, 0x7f80 & 0x1FFF) << 3);
	return r;
} /* HAMMING_GetSyndrome */



/****************************************************************
  Name        :   HAMMING_FindCodePosition
  Parameters  :   [i] - input, [o] - output, [i/o] - input/output
    [i] - uint16_t Code - kod, ktory probujemy znalezc w tablicy
      HAMMING_IntermediateLUT
    [o] - uint16_t Data - jezeli znaleziono kod Code w
      HAMMING_IntermediateLUT, to wskazuje na numer w tej
      tablicy, pod ktorym wystepuje code
  Return value:
    1 - jezeli znaleziono kod
    0 - je¿eli nie znaleziono kodu
  Description :
    Funkcja realizuje rzutwoanie przestrzeni slow 9-bitowych
    zawartych w tablicy HAMMING_IntermediateLUT na
    przestrzen slow 8-bitowych. Jest to mozliwe, poniewaz
    wspomniana tablica ma tylko 256 elementow. Ze wzgledu na
    wyszukiwanie metoda drzewa binarnego, tablica musi byc
    posortowana rosnaco (dolaczana z pliku HammingCodingAVR_LUTs.h
    jest juz posortowana).
****************************************************************/
static uint16_t HAMMING_FindCodePosition (uint16_t Code, uint8_t *Data)
{
	uint8_t  index,	 //Wskazuje numer aktualnie porownywanego elementu tablicy
			     maska;  //Ma ustawiont ten bit, ktory jest aktualnie ustalany
	uint8_t	i;		   //Licznik bitow
	uint16_t BookAtIndex;

	maska = 0x80;		//MSB
	index = maska;	//Zaczynamy od po³owy

	for (i = 0; i <= 8; i++)
	{
    //Zaladowanie danej z pamieci programu:
    BookAtIndex = HAMMING_IntermediateLUT[(uint16_t)index];
    
		if (Code == BookAtIndex)	//Szczesliwy traf (predzej czy pozniej)
		{
			*Data = (uint8_t)index;
			return 1;
		}
		else
			if (i != 8)
			{
				if (Code < BookAtIndex)
					index ^= maska;	//Usuwamy bit maski z indeksu
				maska >>= 1;	//Przechodzimy do nastepnego bitu adresu index
				index |= maska;
			}
	}
	return 0;
} /* HAMMING_FindCodePosition */


/****************************************************************
  Name        :   HAMMING_EncodeBalanced
  Parameters  :   [i] - input, [o] - output, [i/o] - input/output
    [i] uint8_t data - bajt, ktory kodujemy
  Return value:
    Zbalansowany kod Hamminga opdowiadajacy danej data
  Description :
    Zwraca zbalansowany kod Hamminga odpowiadajacy danej data
    poprzez wczytanie go ze stalej tablicy umieszczonej w pamieci
    programu
****************************************************************/
uint16_t HAMMING_EncodeBalanced(uint8_t data)
{
  
    return HAMMING_EncodeLUT[(uint16_t)data];

} /* HAMMING_EncodeBalanced */

/****************************************************************
  Name        :   HAMMING_DecodeSystematic
  Parameters  :   [i] - input, [o] - output, [i/o] - input/output
    [i] uint16_t  input - wejsciowy kod, ktory jest dekodowany
    [o] uint16_t  d     - jezeli kod byl poprawny, lub
      mozliwy do naprawienia, to jest to wskaznik do rozkodowanej
      danej
  Return value:
    0 - podczas dekodowania nie bylo bledow
    1 - wykryto blad na 1 bicie, zostal on poprawiony
    2 - wykryto niekorygowalny blad
  Description :
    Funkcja wyznacza syndrom slowa kodowego, sprawdza parzystosc
    oraz dekoduje dana z kodu.
****************************************************************/
static uint16_t HAMMING_DecodeSystematic (uint16_t input, uint16_t *d)
{
	uint16_t p, s;

	p = HAMMING_XorBits (input, 0x1FFF) ^ ((input >> 13) & 1);
	s = HAMMING_GetSyndrome (input);

    if (p == 0) {
		if (s == 0)
		{	//Bezb³êdnie
		//Ekstrakcja bitów informacyjnych
			*d =	((input & 0x0004) >> 2) |
					((input & 0x0010) >> 3) |
					((input & 0x0020) >> 3) |
					((input & 0x0040) >> 3) |
					((input & 0x0100) >> 4) |
   					((input & 0x0200) >> 4) |
   					((input & 0x0400) >> 4) |
   					((input & 0x0800) >> 4) |
   					((input & 0x1000) >> 4);
			*d &= 0x1FF;
			return 0;	//Bez b³êdów
		}
		else
		{	//B³¹d niekorygowalny na dwoch pozycjach
			return 2;
		}
    } else {
		if (s == 0)
		{	//B³¹d na bicie parzystoœci
			*d =	((input & 0x0004) >> 2) |
					((input & 0x0010) >> 3) |
					((input & 0x0020) >> 3) |
					((input & 0x0040) >> 3) |
					((input & 0x0100) >> 4) |
   					((input & 0x0200) >> 4) |
   					((input & 0x0400) >> 4) |
   					((input & 0x0800) >> 4) |
   					((input & 0x1000) >> 4);
			*d &= 0x1FF;
			return 1;		//skorygowany
		}
		else
		{	//B³¹d korygowalny
			input =  (input ^ (1 << (s-1))) & 0x1FFF;

			*d =	((input & 0x0004) >> 2) |
					((input & 0x0010) >> 3) |
					((input & 0x0020) >> 3) |
					((input & 0x0040) >> 3) |
					((input & 0x0100) >> 4) |
   					((input & 0x0200) >> 4) |
   					((input & 0x0400) >> 4) |
   					((input & 0x0800) >> 4) |
   					((input & 0x1000) >> 4);
			*d &= 0x1FF;
			return 1;
		}
    }
} /* HAMMING_DecodeSystematic */


/****************************************************************
  Name        :   HAMMING_DecodeBalanced
  Parameters  :   [i] - input, [o] - output, [i/o] - input/output
    [i] uint16_t input  - wejsciowy kod do zdekodowania
    [o] uint8_t d - jezeli funkcja zwrocila 0 lub 1, to wskazuje
      na zdekodowany bajt danych z kodu input
  Return value:
    0 - zdekodowano poprawnie
    1 - zdekodowano z korekcja na 1 bicie
    2 - niemozliwe zdekodowanie, blod na wiecej niz jednym bicie
  Description :
    Realizuje dekodowanie zbalansowanych kodow Hamminga
    (funkcja odwrotna do EncodeBalancedHamming). Rozdzial 5 dokumentacji
****************************************************************/
uint16_t HAMMING_DecodeBalanced (uint16_t input, uint8_t *d)
{
	uint16_t d9bit = 0;

  //Dekodujemy najpierw 9-bitowe slowo posrednie
	switch (HAMMING_DecodeSystematic(input, &d9bit))
	{
	case 0:	//By³o OK
		//Rzutowanie wsteczne 9bit kod poœredni-> 8bit dana
		if (HAMMING_FindCodePosition(d9bit, d))
			return 0;
		else
			return 2;	//Nie by³o takiego kodu
	case 1: //B³¹d skorygowany
		if (HAMMING_FindCodePosition(d9bit, d))
			return 1;
		else
			return 2;	//Nie by³o takiego kodu
	default:
		return 2;   //Blad nieskorygowany
	}
} /* HAMMING_DecodeBalanced */

/*! \file hamming.c
    \brief Obs³uga kodowania hamminga

    Modu³ zawiera funkcje obs³uguj¹ce kodowanie i dekodowanie danych algorytmem (7,4) Hamminga.
*/
