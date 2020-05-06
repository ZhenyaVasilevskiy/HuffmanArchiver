#pragma once
#include "tree.h"
int decryptMe(node_t*, FILE**);
void byteToTreeCode(unsigned char, int, char*, int*, node_t**, node_t*, FILE**);