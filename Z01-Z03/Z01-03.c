#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>         
#include <inttypes.h>

const char* vowels = "уУеЕёЁыЫаАоОэЭяЯиИюЮ";
const char* consonants = "йЙцЦкКнНгГшШщЩзЗхХфФвВпПрРлЛдДжЖчЧсСмМтТбБ";

char* toSaltTransform(const char* intext) {
	char* outtext = NULL;
	uint8_t ind = 0;

	while (*intext) {
		if (strchr(vowels, *intext)) {
			outtext = (char*)realloc(outtext, ind * sizeof(char) + 3);
			*(outtext + ind++) = *intext;
			*(outtext + ind++) = 'с';
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
		if (strchr(vowels, *intext) && *(intext + 1) == 'с' && (*(intext + 2) == *intext || (char)toupper(*(intext + 2)) == *intext)) {
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

		if (strchr(vowels, *intext) && *(intext + 1) == 'с' && (*(intext + 2) == *intext || (char)toupper(*(intext + 2)) == *intext)) {
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

	printf("Меню:\n"); 
	printf("1 - Печать текста.\n");
	printf("2 - Перевод в соленый.\n");
	printf("3 - Измеритель солености.\n");
	printf("4 - Перевод в нормальный.\n");
	printf("5 - Выход.\n");
	printf("Выбор: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	setlocale(LC_ALL, "Russian");

	const char* intext = { "Привет. У лукоморья дуб зеленый, златая цепь на дубе том висит. И днем и ночью кот ученый, всё ходит по цепи кругом." };
	char* salttext = NULL;
	uint8_t ch = 0;

	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			if (intext) {
				printf("\nИсходный текст: ");
				puts(intext);
			}

			if (salttext) {
				printf("\nСоленый текст: ");
				puts(salttext);
			}

			break;

		case 2:
			salttext = toSaltTransform(intext);
			printf("Соленый текст: ");
			puts(salttext);
			break;

		case 3:
			if (intext) {
				printf("\nИсходный текст: ");
				puts(intext);
				printf("Процент солености: %.2f.\n", saltMeasure(intext));
			}

			if (salttext) {
				printf("\nСоленый текст: ");
				puts(salttext);
				printf("Процент солености: %.2f.\n", saltMeasure(salttext));
			}

			break;

		case 4: {
			char* txt = NULL;

			if (intext) {
				printf("\nПеревод исходного текста в нормальный: ");
				txt = toNormalTransform(intext);
				puts(txt);
				free(txt);
				txt = NULL;
			}
			if (salttext) {
				printf("\nПеревод соленого текста в нормальный: ");
				txt = toNormalTransform(salttext);
				puts(txt);
				free(txt);
				txt = NULL;
			}

			break;
		}

		default:
			printf("Неверный ввод.\n");
			pass();
			break;
		}

		printf("Нажмите любую клавишу.\n");
		_getch();
	}

	free(salttext);

	return 0;
}