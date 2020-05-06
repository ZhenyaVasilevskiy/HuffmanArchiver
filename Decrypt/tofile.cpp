#include "tofile.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decryptMe(node_t* main_tree, FILE** input)
{
	char symbol; //������ ��� ����������.
	char* str = (char*)malloc(sizeof(char) * 256), code, number;	 //������ ��� ������ � ������.
	int ptr = 0, number_int;
	node_t* temp_tree = main_tree; //������ ��� ����������.
	if (main_tree == NULL) return 1;
	FILE* output; //���� ��� ������.
	fopen_s(&output, "decrypted.decompressed", "w");
	char* string = (char*)malloc(256 * sizeof(char));
	int size = 0;
	

	while((size = fread(string, sizeof(char), 256, (*input)))) //���� �� ����� �����.
	{
		for (int i = 0; i < size; ++i)
		{
			symbol = string[i];
			if (symbol >= '0' && symbol <= '8' && i == (size - 2) && size!=256)  //���� �������� �����.
			{
				number = symbol;
				code = string[i+1];
				number_int = number - '0'; //����� ����, ��� ��������� ���� ����� ���� ��������� �� ��������, �� ��� ������ ������� ���������� �������� ���.
				for (int j = 0; j < number_int; code <<= 1, ++j); //�������, ������ �������� ����.
				byteToTreeCode(code, 8-number_int, str, &ptr, &temp_tree, main_tree, &output); //���������� ����.
				fputs(str, output); //������� ��������� ������ � ����.
				break;
			}
			else
			{
				byteToTreeCode(symbol, 8, str, &ptr, &temp_tree, main_tree, &output); //���� �� ��� ������ ������, �� ������ ��� ����������.
			}
		}
	}
	fclose(output); //��������� ����.

	return 0;
}

void byteToTreeCode(unsigned char symbol, int symbol_size, char* str, int* ptr, node_t** temp_tree, node_t* main_tree, FILE** output)
{
	for (int i = 0; i < symbol_size; symbol <<= 1, ++i) //�������� � ��������� �������
	{
		if (symbol >= 128) (*temp_tree) = (*temp_tree)->right; //����� ����, ��� �� �������� �����, �� �������� ����� ����� ���, ���������� �� 128. ���� ����� ������, 
															   //�� ��� 0. ���� ��� �� 1, �� ���� ������.
		else (*temp_tree) = (*temp_tree)->left; //���� ����, �� �����.

		if ((*temp_tree)->letter != STOPELEMENT) { //���� ��� �����.
			str[(*ptr)++] = (*temp_tree)->letter; //���������� � ������.
			str[(*ptr)] = '\0';
			(*temp_tree) = main_tree; //���������� ��������� �� ������ ������.
		}

		if ((*ptr) == 255) { //���� ������ �����, �� ��������� �� � ����.
			fputs(str, (*output));
			memset(str, '\0', 256);
			(*ptr) = 0;
		}
	}
}