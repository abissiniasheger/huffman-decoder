#ifndef DECODER_H_
#define DECODER_H_

/* > Defines ******************************************************************/

/* > Type Declarations ********************************************************/

#define MAX_SYMBOLS 255
#define MAX_LEN     10

// Node definition
typedef struct tnode
{
    struct  tnode* left; /*used when in tree*/
    struct  tnode* right; /*used when in tree*/
    int            isleaf;
    char           symbol;
}treeNode;

// Code (a sequence of 1's and 0's) corresponding
// to each character
// Code is supposed to be read from a file
// and stored in a struct
typedef struct codeStorage
{
	char    symbol;
	char	   strcode[MAX_LEN];
}codeStorage;


#endif /* DECODER_H_ */
