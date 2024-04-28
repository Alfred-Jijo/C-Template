/*
* Function ARRAY_SIZE: calculates and returns the sizeof an array
* Params : An array
* Returns : size_t
*/
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
