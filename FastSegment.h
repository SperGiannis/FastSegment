/// 
///  Created for personal use, use it at your own risk and benefit.
///  https://github.com/GitMoDu/FastSegment
///  Depends on Fast for IO https://github.com/GitMoDu/Fast
/// 

#ifndef _FASTSEGMENT_h
#define _FASTSEGMENT_h

#include <Arduino.h>
#include <Fast.h>

#ifndef MAX_SEGMENT_DIGIT_COUNT
#define MAX_SEGMENT_DIGIT_COUNT 10
#endif // !MAX_SEGMENT_DIGIT_COUNT


#define BYTE_SIZE 8

class FastSegment
{
private:
#define SEGMENT_ERROR B10101010

	uint32_t DataPin, ClockPin, ShiftPin, DigitCount;

	FastOut Data;
	FastShifter Clock, Shift;

	uint32_t LastNumber = 0;

	bool NeedsRefresh = true;

	void SetHead(const bool value);
	void Reset();
	void WriteByte(const uint8_t value);	

	//Equivalent to 10^power up to 10 power but much, much faster.
	uint16_t TenPower16(const uint8_t power);
	uint32_t TenPower32(const uint8_t power);

public:

///////////////////B76543210
#define SEGMENT_0  B11000000 //All but 6 and 7
#define SEGMENT_1  B11111001 //1 and 2
#define SEGMENT_2  B10100100 //0, 1, 3, 4, 6
#define SEGMENT_3  B10110000 //0, 1, 2, 3, 6
#define SEGMENT_4  B10011001 //1, 2, 5, 6
#define SEGMENT_5  B10010010 //0, 2, 3, 5, 6
#define SEGMENT_6  B10000010 //2, 3, 4, 5, 6
#define SEGMENT_7  B11111000 //0, 1, 2
#define SEGMENT_8  B10000000 //All but 7
#define SEGMENT_9  B10010000 //0, 1, 2, 5, 6

#define SEGMENT_0D  B01000000
#define SEGMENT_1D  B01111001
#define SEGMENT_2D  B00100100
#define SEGMENT_3D  B00110000
#define SEGMENT_4D  B00011001
#define SEGMENT_5D  B00010010
#define SEGMENT_6D  B00000010
#define SEGMENT_7D  B01111000
#define SEGMENT_8D  B00000000
#define SEGMENT_9D  B00010000

#define SEGMENT_UNDER  B11110111
#define SEGMENT_BAR	   B10111111

#define SEGMENT_CLEAR  B11111111
#define SEGMENT_ALL_ON B00000000

	uint8_t Digits[MAX_SEGMENT_DIGIT_COUNT];
	
	bool Setup(const uint8_t dataPin, const uint8_t clockPin, const uint8_t shiftPin, const uint8_t digitCount);

	//Set all digits to the same value.
	void SetDigitsAll(const uint8_t value);

	//Show the digits set from the set number. 
	//Clear the screen before if clearBefore == true .
	void ShowNumber(const bool clearBefore = false);

	//Set the digits from the number, omitting the leftmost zeros by default.
	//Returns true if the number has changed since last time.
	bool SetNumber(const uint32_t number, const bool forceUpdate, const bool replaceZero = true);

	bool SetNumber(const uint16_t number, const bool forceUpdate, const bool replaceZero = true);

	//Get the last set number.
	uint8_t GetLastNumber();

	//Set all outputs to the same bit value
	void SetAll(const bool bitValue);

	//Display the bytes in the provided array
	void ShowBytes(uint8_t byteArray[], uint8_t byteArraySize);

	//Translate single digit value to representation in a 7-segment byte.
	uint8_t GetDigitByte(const uint8_t number1to9, const bool decimalOn = false);

	//Clear display
	void Clear();

};

#endif

