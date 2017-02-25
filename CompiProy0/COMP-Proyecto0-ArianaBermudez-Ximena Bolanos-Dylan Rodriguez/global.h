#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED



//Se definen los tokens disponibles en un enum
typedef enum token_types
{
	BEGIN, END, READ, WRITE, ID, INTLITERAL,
	LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
	PLUSOP, MINUSOP, SCANEOF, IF
} token;

/*
 * typedef y enum necesarios para analizador semantico
 */


#define MAXIDLEN 33
typedef char string [MAXIDLEN];

typedef struct operator
{
	/* for operators */
	enum op {PLUS, MINUS} operator;
} op_rec;

 /* expression types */
enum expr {IDEXPR, LITERALEXPR, TEMPEXPR};

/* for <primary> and <expression> */
typedef struct expression
{

	enum expr kind;
	bool flag;
	string name; /* for IDEXPR, TEMPEXPR */
    int val; /* for LITERALEXPR */

} expr_rec;

extern token scanner(void);
extern char token_buffer[6];
extern int parada;

extern char startH[500] = ".global _start\n _start: \n";
extern char end[500] = "end:\n";
extern char data[500] = ".data\n";
extern char address[500] = "\n";
extern char finalFile[2000] = "";
#endif // GLOBAL_H_INCLUDED

