#include "tofile.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decryptMe(node_t* main_tree, FILE** input)
{
	char symbol; //Символ для считывания.
	char* str = (char*)malloc(sizeof(char) * 256), code, number;	 //Строка для записи и буферы.
	int ptr = 0, number_int;
	node_t* temp_tree = main_tree; //Дерево для дешифровки.
	if (main_tree == NULL) return 1;
	FILE* output; //Файл для записи.
	fopen_s(&output, "decrypted.decompressed", "w");
	char* string = (char*)malloc(256 * sizeof(char));
	int size = 0;
	

	while((size = fread(string, sizeof(char), 256, (*input)))) //Пока не конец файла.
	{
		for (int i = 0; i < size; ++i)
		{
			symbol = string[i];
			if (symbol >= '0' && symbol <= '8' && i == (size - 2) && size!=256)  //Если попалось число.
			{
				number = symbol;
				code = string[i+1];
				number_int = number - '0'; //Ввиду того, что последний байт может быть полностью не заполнен, то для начала получим количество ненужных бит.
				for (int j = 0; j < number_int; code <<= 1, ++j); //Сдвинем, удалив ненужные биты.
				byteToTreeCode(code, 8-number_int, str, &ptr, &temp_tree, main_tree, &output); //Расшифруем байт.
				fputs(str, output); //Закинем последнюю строку в файл.
				break;
			}
			else
			{
				byteToTreeCode(symbol, 8, str, &ptr, &temp_tree, main_tree, &output); //Если же это другой символ, то просто его обработаем.
			}
		}
	}
	fclose(output); //Закрываем файл.

	return 0;
}

void byteToTreeCode(unsigned char symbol, int symbol_size, char* str, int* ptr, node_t** temp_tree, node_t* main_tree, FILE** output)
{
	for (int i = 0; i < symbol_size; symbol <<= 1, ++i) //Итерация с побитовым сдвигом
	{
		if (symbol >= 128) (*temp_tree) = (*temp_tree)->right; //Ввиду того, что мы сдвигаем влево, то меняется самый левый бит, отвечающий за 128. Если число меньше, 
															   //то там 0. Если все же 1, то идем вправо.
		else (*temp_tree) = (*temp_tree)->left; //Если ноль, то влево.

		if ((*temp_tree)->letter != STOPELEMENT) { //Если это буква.
			str[(*ptr)++] = (*temp_tree)->letter; //Записываем в строку.
			str[(*ptr)] = '\0';
			(*temp_tree) = main_tree; //Возвращаем указатель на начало деерва.
		}

		if ((*ptr) == 255) { //Если строка полна, то вставляем ее в файл.
			fputs(str, (*output));
			memset(str, '\0', 256);
			(*ptr) = 0;
		}
	}
}