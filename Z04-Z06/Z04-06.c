#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

const char* vowels = "уУеЕёЁыЫаАоОэЭяЯиИюЮ";
const char* consonants = "йЙцЦкКнНгГшШщЩзЗхХфФвВпПрРлЛдДжЖчЧсСмМтТбБ";
const char* alfabeth = "АаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПппПрРсСтТуУфФхХцЦчЧшШщЩъЪыЫьЬэЭюЮяЯ";

char* textTransform(const char* intext) {
	char* out = NULL;
	uint8_t ln = 0;

	while (*intext) {
		out = (char*)realloc(out, ln * sizeof(char) + 1);

		if (strchr(alfabeth, *intext)) {
			*(out + ln++) = *(alfabeth + (alfabeth + strlen(alfabeth) - 1 - strchr(alfabeth, *intext)));
		}
		else {
			*(out + ln++) = *intext;
		}

		intext++;
	}

	out = (char*)realloc(out, ln * sizeof(char) + 1);
	*(out + ln) = '\0';

	return out;
}

double ratioVowelsConsonants(const char* text) {
	uint8_t vowelsLt = 0;
	uint8_t consonantLt = 0;

	while (*text) {
		if (strchr(vowels, *text)) {
			vowelsLt++;
		}

		if (strchr(consonants, *text)) {
			consonantLt++;
		}

		text++;
	}

	return (double)vowelsLt / consonantLt;
}

uint8_t middleVowelsConsonants(const char* text) {
	char* word = NULL;
	uint8_t ln = 0;
	uint8_t vowelsLt = 0;
	uint8_t consonantsLt = 0;
	uint8_t other = 0;

	while (*text) {
		word = (char*)realloc(word, ln * sizeof(char) + 1);
		*(word + ln++) = *text;

		if (strchr(vowels, *text)) {
			vowelsLt++;
		}

		if (strchr(consonants, *text)) {
			consonantsLt++;
		}

		if (*text == 'ъ' || *text == 'ь' || *text == 'Ъ' || *text == 'Ь') {
			other++;
		}

		text++;

		if (!strchr(alfabeth, *text)) {
			word = (char*)realloc(word, ln * sizeof(char) + 1);
			*(word + ln) = '\0';
			printf("В слове \"%s\" среднее количество гласных - %.2f, согласных - %.2f.\n", word, (double)vowelsLt / (vowelsLt + consonantsLt + other), (double)consonantsLt / (vowelsLt + consonantsLt + other));

			ln = 0;
			other = 0;
			vowelsLt = 0;
			consonantsLt = 0;
			free(word);
			word = NULL;

			while (!strchr(alfabeth, *text)) {
				text++;
			}
		}
	}

	return vowelsLt + consonantsLt + other;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Меню:\n");
	printf("1 - Исходный текст.\n");
	printf("2 - Преобразование каждой буквы строки в обратную.\n");
	printf("3 - Соотношение гласных и согласных букв в тексте.\n");
	printf("4 - Среднее количество грасных согласных букв в слове текста.\n");
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

	uint8_t ch = 0;
	const char* intext = { "Привет. У лукоморья дуб зеленый, златая цепь на дубе том висит. И днем и ночью кот ученый, всё ходит по цепи кругом." };

	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			if (intext) {
				printf("\nИсходный текст: ");
				puts(intext);
			}
			break;

		case 2: {
			char* outtext = textTransform(intext);
			puts(outtext);
			free(outtext);
			outtext = NULL;
			break;
		}

		case 3:
			printf("\nСоотношение гласных и согласных букв в тексте - %.2f.\n\n", ratioVowelsConsonants(intext));
			break;

		case 4:
			middleVowelsConsonants(intext);
			break;

		default:
			printf("Неверный ввод.\n");
			pass();
			break;
		}

		printf("Нажмите любую клавишу.\n");
		_getch();
	}

	return 0;
}