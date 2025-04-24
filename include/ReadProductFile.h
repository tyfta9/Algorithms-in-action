// if ReadProductFile.h is not included, do so
#if !defined(READPRODUCTFILE_H)
#define READPRODUCTFILE_H

#include "CarPartProduct.h"
// public functions of a ReadProductFile.c file

// get total product or line count in all files excluding headers
int FGetRowCount(char *fullFilePath);
// read all product from file
void FReadProducts(part **products, int size, char *fullFilePath, char *delim);

#endif