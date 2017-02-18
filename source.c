/*
FIGURE 2.1 SCANNER LOOP TO RECOGNIZE IDENTIFIER AND INTEGER 
LITERALS
*/

#include <source.h> 
#include <stdio.h> 
#include <ctype.h> 

int in_char, c; 

while ((in_char = getchar()) != EOF){
	if (isspace(in_char))
		continue; /*no hace nada*/ 
	else if (isaplpha(in_char)){
		/*
		* ID::= LETTER | ID LETTER 
		*			   | ID DIGIT
		*			   | ID UNDERSCORE
		*/

		for (c = getchar(); isalum(c) || c == _; c = getchar())
			; 
		ungetc(c, stdin); 
		return ID; 
	}
	else if (isdigit(in_char)){
		/*
		* INTLITERAL ::= DIGIT | 
		*				 INTLITERAL DIGIT
		*/ 
		while (isdigit((c = getchar())))
			; 
		ungetc(c, stdin); 

		return INTLITERAL; 
	}
	else
		lexical_error(in_char); 
}










/*
FIGURE 2.2 SCANNER LOOP WITH NEW CODE TO RECOGNIZE OPERATOR, 
COMMENTS, AND DELIMITERS
*/

//#include <stdio.h> 
//#include <ctype.h> 

int in_char, c; 

while ((in_char = getchar()) != EOF){
	IF (isspace(in_char))
	 /*no hace nada*/ 
	continue; 
	else if (isaplpha(in_char))
		/* code to recognize identifieres goes here */ 
	else if (isdigit(in_char))
		/* code to recgonize int literals goes here */
	else if (in_char == '(')
		return LPAREN; 
	else if (in_char == ')')
		return RPAREN;
	else if (in_char == ';')
		return SEMICOLON; 
	else if (in_char == ',')
		return COMMA; 
	else if (in_char == '+')
		return PLUSOP 
	else if (in_char == ':'){
		/* LOOKING FOR ":=" */ 
		c = getchar(); 
		if (c == '=')
			return ASSIGNOP; 
		else {
			ungetc(c, stdin); 
			lexical_error(in_char);
		}
	}
	else if(in_char == '-'){
		/*looking for --,comment start*/ 
		c = getchar(); 
		if (c == '-'){
			while ((in_char = getchar()) != '\n');
		}
		else{
			ungetc(c,stdin);
			return MINUSOP; 
		}
	} 
	else 
		lexical_error(in_char); 
}







/*  buffer_char(): añade el argumento a un buffer de caracteres llamado  token_buffer
	clear_buffer(): va a resetear el buffer
	SCANEOF : crearon un token de final del archivo 
			osea con el scanner se llama feof(stdin) y si es true se retorna SCANEOF
*/

/*
FIGURE 2.3 COMPLETE SCANNER FUNCTION FOR MICRO
*/

//#include <stdio.h> 
/* character classification macros */ 
//#include <ctype.h> 

extern char token_buffer[]; 

token scanner(void){
	int in_char, c; 

	clear_buffer(); 
	if(feof(stdin))
		return SCANEOF; 
	while ((in_char = getchar()) != EOF){
		if (isspace(in_char))
			continue; /*do nothing*/ 
		else if (isaplpha(in_char)){
			/* code to recognize identifieres goes here */ 
			/*
			* ID ::= LETTER | ID LETTER 
			*				| ID DIGIT
			*				| ID UNDERSCORE
			*/

			buffer_char(in_char); 
			for (c = getchar(); isalum(c) || c == _; c = getchar())
				buffer_char(c); 
			ungetc(c, stdin); 
			return check_reserved; 
		}
		else if (isdigit(in_char)){
			/* code to recgonize int literals goes here */
			/*
			* INTLITERAL ::= DIGIT |
			*				 INTLITERAL DIGIT
			*/
			buffer_char(in_char); 
			for (c = getchar(); isdigit(c); c = getchar())
				buffer_char(c); 
			ungetc(c, stdin); 
			return INTLITERAL;  
		} 	
		
		else if (in_char == '(')
			return LPAREN; 
		else if (in_char == ')')
			return RPAREN;
		else if (in_char == ';')
			return SEMICOLON; 
		else if (in_char == ',')
			return COMMA; 
		else if (in_char == '+')
			return PLUSOP 
		else if (in_char == ':'){
			/* LOOKING FOR ":=" */ 
			c = getchar(); 
			if (c == '=')
				return ASSIGNOP; 
			else {
				ungetc(c, stdin); 
				lexical_error(in_char);
			}
		}
		else if(in_char == '-'){
			/*looking for --,comment start*/ 
			c = getchar(); 
			if (c == '-'){
				while ((in_char = getchar()) != '\n');
			}
			else{
				ungetc(c,stdin);
				return MINUSOP; 
			}
		} 
		else 
			lexical_error(in_char); 
	}
}







/*
THE PARSER IS STARTED BY CALLING THE PROCEDURE CORRESPONDINGO TO SYSTEM GOAL
*/

void system_goal(void){
	/* <system goal> ::= <program> SCANEOF */
	program(); 
	match(SCANEOF); 
}






/*-*/

void program(void){
	/* <program> ::= BEGIN <statement list> END*/
	match(BEGIN); 
	statement_list(); 
	match(END);
}







/*
THE STATEMENT LIST, ES A LO QUE SUENA XD, EL NEXT_TOKEN TOMA EL DE LA MAS IZQUIERDA 
*/

//VERSION 1 

void statement_list(void){
	/*
	* <statement list> ::= <statement> { <statement> }
	*/

	statement(); 
	while (TRUE) {
		switch (next_token()){
		case ID:
		case READ:
		case WRITE: 
			statement(); 
			break; 
		default: 
			return; 
		}
	}
}

/*-*/

void statement(void){
	token tok = next_token(); 

	switch (tok){
		case ID: 
		/* <STATEMENT> ::= ID := <expression> ; */
		match(ID); match(ASSIGNOP); 
		expression(); match(SEMICOLON); 
		break; 

		case READ: 
		/* <statement> ::= READ ( <id list> ) ; */
		match(READ); match(LPAREN); 
		id_list(); match(RPAREN); 
		match(SEMICOLON); 
		break; 

		case WRITE: 
		/* <statement> ::= WRITE ( <expr list> ) ; */
		match(WRITE); match(LPAREN); 
		expr_list(); match(RPAREN); 
		match(SEMICOLON); 
		break; 

	default: 
		syntax_error(tok); 
		break;
	}
}




void id_list(void){
	/* <id list> ::= ID { , ID } */
	match(ID); 

	while(next_token() == COMMA){
		match(COMMA); 
		match(ID); 
	}
}





void expression(void){
	token t; 

	/*
	* <expression> ::= <primary> {<add op> <primary>}
	*/

	primary(); 
	for(t = next_token(); t== PLUSOP || t == MINUSOP; t = next_token()){
		add_op(); 
		primary(); 
	}
}





void expr_list(void){
	/* <expr list> ::= <expression> { , <expression> }*/

	expression(); 

	while(next_token() == COMMA){
		match(COMMA);
		expression(); 
	}
}






void add_op(void){
	token tok = next_token(); 

	/* <addop> ::= PLUSOP | MINUSOP*/
	if (tok == PLUSOP | MINUSOP)
		match(tok); 
	else 
		syntax_error(tok); 
}







void primary(void){
	token tok = next_token(); 

	switch(tok){
		case LPAREN: 
		/* <primary> ::= (<expression>)*/
		match(LPAREN), expression();
		match(RPAREN); 
		break; 

		case ID: 
		/*<primary> ::= ID*/
		match(ID); 
		break; 

		case INTLITERAL: 
		/*<primary> ::= INTLITERAL*/
		match(INTLITERAL); 
		break; 

	default: 
		syntax_error(tok); 
		break; 
	}
}

/*
FIGURE 2.8 SEMANTIC RECORDS FOR MICRO GRAMMAR SYMBOLS 
*/

#define MAXIDLEN 33 
typedef char string [MAXIDLEN]; 

typedef struct operator
{
	/* for operators */
	enum op {PLUS, MINUS} operator; 
} op_rec;
 
 /* expression types */
enum expr {IDEXPR, LITERALEXPR, TEMPEXR}

/* for <primary> and <expression> */
typedef struct expression
{
	enum expr kind; 
	union{
		string name; /* for IDEXPR, TEMPEXPR */
		int val; /* for LITERALEXPR */
	}
} expr_rec;



/**/


/* Is s in the symbol table? */
extern int lookup(string s); 

/* Put s unconditionally into symbol table */
extern void enter(string s); 

void check_id(string s){
	if (! lookup(s)){
		enter(s);
		generate("Declare", s, "Integer", ""); 
	}
}


/**/



char *get_temp(void){
	/*maax temporary allocated so far*/ 
	static int max_temp = 0; 
	static char tempname[MAXIDLEN]; 

	max_temp++; 
	sprintf(tempname, "Temp&%d", max_temp); 
	check_id(tempname); 
	return tempname; 
}


/*
FIGURE 2.10 ACTION RUTINES FOR MICRO
*/



void start(void){
	/*Semantic initializations, none needed*/ 
	generate("Halt", "","",""); 
}

void assign(expr_rec, target, expr_rec, source){
	/* Generate code for assignment */ 
	generate("Store", extract(source), target.name, ""); 
}





op_rec process_literal(void){

	expr_rec t; 
	/*
	*	Convert literal to a numeric representation
	*	and build sematic record. 
	*/
	t.kind = LITERALEXPR; 
	(void) sscanf(token_buffer, "%d", & t.val); 
	return t; 
}








void write_expr(expr_rec out_expr){
	generate("Write", extract(out_expr), "Integer", ""); 
}





/*
FIGURE 2.11 A PARSING PROCEDURE 
INCLUDING SEMANTIC PROCESSING
*/


void expression(expr_rec * result){

	expr_rec, left_operand, right_operand; 
	op_rec op; 

	primary(& left_operand); 
	while(next_token = PLUSOP || next_token == MINUSOP){
		add_op(& op); 
		primary(& right_operand); 
		left_operand = gen_infix(left_operand, op, right_operand); 
	}
	*result = left_operand; 
}
