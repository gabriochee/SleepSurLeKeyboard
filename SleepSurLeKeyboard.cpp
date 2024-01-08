#include <iostream>
#include <string>

// z décalage bit à droite
// Z décalage bit à gauche
// zz décalage octet à droite
// ZZ décalage octet à gauche
// zzz incrémente l'octet actuel
// ZZZ décrémente l'octet actuel
// zZ or Zz flip current bit
// zzzz si l'octet est égal à 0, on saute au prochain ZZZZ
// ZZZZ si l'octet est différent de 0

int main()
{
	std::string str_tape = "Z Z Z zZ Z Z Z zZ zz Z Z zZ Z zZ Z Z zZ Z zZ zzzz ZZZ zz zzz zz zzz ZZ ZZ ZZZZ zZ Z Z zZ Z Z Z zZ Z zZ zz zz zz zZ Z zZ Z zZ Z zZ Z Z zZ Z zZ zz Z Z Z Z Z zZ zz zZ Z zZ Z zZ Z Z zZ Z zZ Z zZ zz zZ Z zZ Z zZ Z zZ Z Z zZ Z zZ zz Z zZ Z Z Z zZ Z zZ Z zZ zz Z Z zZ Z zZ Z Z zZ Z zZ zz Z Z zZ Z Z Z zZ Z zZ zz zZ Z Z Z Z Z zZ";
	str_tape += '\0';
	uint8_t* instructions_tape = new uint8_t[str_tape.length()]{0xFF};

	const uint8_t FUNC_NUMBER = 8;
	const uint8_t FUNC_NUM_MID = FUNC_NUMBER / 2;
	const uint8_t ARRAY_LENGTH = 10000;
	const uint16_t last_instr = 0;

	uint8_t bit_ptr = 0;
	uint8_t func_index = FUNC_NUM_MID;
	uint16_t ptr = 0;
	uint16_t boucle_counter = 0;
	uint16_t instr_index = 0;

	char* arr = new char[ARRAY_LENGTH] {0};
	
	for (char c : str_tape) {
		switch (c)
		{
		case 'z':
			func_index += (func_index < FUNC_NUMBER) ? 1 : 0;
			break;
		case 'Z':
			func_index -= (func_index > 0) ? 1 : 0;
			break;
		default:
			break;
		}
		if (c == ' ' || c == '\0') {
			instructions_tape[instr_index] = func_index;
			instr_index++;
			func_index = FUNC_NUM_MID;
		}
	}

	for (uint16_t i = 0; i < instr_index; i++) {
		switch (instructions_tape[i])
		{
		case FUNC_NUM_MID:
			arr[ptr] ^= (1 << bit_ptr);
			break;
		case FUNC_NUM_MID - 1:
			if (bit_ptr >= 7) {
				ptr++;
				bit_ptr = 0;
			}
			else {
				bit_ptr++;
			}
			break;
		case FUNC_NUM_MID + 1:
			if (bit_ptr <= 0) {
				bit_ptr = 7;
				if (ptr > 0) {
					ptr--;
				}
				else {
					return -1;
				}
			}
			else {
				bit_ptr--;
			}
			break;
		case FUNC_NUM_MID + 2:
			if (ptr < ARRAY_LENGTH) {
				ptr++;
				bit_ptr = 0;
			}
			else
			{
				return -1;
			}
			break;
		case FUNC_NUM_MID - 2:
			if (ptr > 0) {
				ptr--;
				bit_ptr = 0;
			}
			else
			{
				return -1;
			}
			break;
		case FUNC_NUM_MID + 3:
			arr[ptr]++;
			break;
		case FUNC_NUM_MID - 3:
			arr[ptr]--;
			break;
		case FUNC_NUM_MID + 4:
			if (arr[ptr] == 0) {
				while (instructions_tape[i] != FUNC_NUM_MID - 4 || boucle_counter != 0) {
					i++;
					if (instructions_tape[i] == FUNC_NUM_MID + 4) {
						boucle_counter++;
					}
					else if (instructions_tape[i] == FUNC_NUM_MID - 4 && boucle_counter > 0) {
						boucle_counter--;
					}
				}
			}
			break;
		case FUNC_NUM_MID - 4:
			if (arr[ptr] != 0) {
				while (instructions_tape[i] != FUNC_NUM_MID + 4 || boucle_counter != 0) {
					i--;
					if (instructions_tape[i] == FUNC_NUM_MID - 4) {
						boucle_counter++;
					}
					else if (instructions_tape[i] == FUNC_NUM_MID + 4 && boucle_counter > 0) {
						boucle_counter--;
					}
				}
			}
			break;
		default:
			break;
		}
		func_index = FUNC_NUM_MID;
	}

	std::cout << arr << std::endl;

	return 0;
}
