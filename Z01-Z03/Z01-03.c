
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>         
#include <inttypes.h>


char* toSaltTransform(const char* intext) {
	char* outtext = NULL;
	uint8_t ind = 0;

	while (*intext) {
		if (strchr(vowels, *intext)) {
			outtext = (char*)realloc(outtext, ind * sizeof(char) + 3);
			*(outtext + ind++) = *intext;
			*(outtext + ind++) = tolower(*intext);
		}
		else {
			outtext = (char*)realloc(outtext, ind * sizeof(char) + 1);
			*(outtext + ind++) = *intext;
		}
		intext++;
	}
	outtext = (char*)realloc(outtext, ind * sizeof(char) + 1);
	*(outtext + ind) = '\0';

	return outtext;
}

double saltMeasure(const char* intext) {
	uint8_t saltLet = 0;
	uint8_t vowelsLet = 0;

	while (*(intext + 2)) {
			saltLet++;
			vowelsLet++;
			intext += 2;
		}
		else if (strchr(vowels, *intext)) {
			vowelsLet++;
		}

		intext++;
	}
	while (*intext) {
		if (strchr(vowels, *intext)) {
			vowelsLet++;
		}
		intext++;
	}

	return (double)saltLet / vowelsLet++ * 100;
}

char* toNormalTransform(const char* intext) {
	char* outtext = NULL;
	uint8_t ln = 0;

	while (*intext) {
		outtext = (char*)realloc(outtext, ln * sizeof(char) + 1);
		*(outtext + ln++) = *intext;

			intext += 3;
		}
		else {
			intext++;
		}
	}
	outtext = (char*)realloc(outtext, ln * sizeof(char) + 1);
	*(outtext + ln) = *intext;

	return outtext;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	setlocale(LC_ALL, "Russian");

	char* salttext = NULL;
	uint8_t ch = 0;

	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			if (intext) {
				puts(intext);
			}

			if (salttext) {
				puts(salttext);
			}

			break;

		case 2:
			salttext = toSaltTransform(intext);
			puts(salttext);
			break;

		case 3:
			if (intext) {
				puts(intext);
			}

			if (salttext) {
				puts(salttext);
			}

			break;

		case 4: {
			char* txt = NULL;

			if (intext) {
				txt = toNormalTransform(intext);
				puts(txt);
				free(txt);
				txt = NULL;
			}
			if (salttext) {
				txt = toNormalTransform(salttext);
				puts(txt);
				free(txt);
				txt = NULL;
			}

			break;
		}

		default:
			pass();
			break;
		}

		_getch();
	}

	free(salttext);

	return 0;
}
