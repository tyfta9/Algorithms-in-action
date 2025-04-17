// public functions of a ReadProductFile.c file

// get total product or line count in all files excluding headers
int FGetProductCount();

// read all product from file
void FReadProduct(struct carPartProduct* products, int size);