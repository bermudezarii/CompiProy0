/*
FIGURE 2.1 SCANNER LOOP TO RECOGNIZE IDENTIFIER AND INTEGER
LITERALS
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "global.h"



/* character classification macros */


/*Variables globales que se utilizarán*/

/* ************************************** */
token current_token = ID;
char token_buffer[6];

int i=0;
int parada=0;
FILE *file;
int symbol_table_i = 0;


//prueba ari de matrices


string symbol_table [1000];

/*
 * Las funciones lookup y enter van a consultar si el string esta en la tabla de simbolos
*/
int lookup(string s)
{
    for (int i = 0; i < 1000; i++) {
        //strcmp tira 0 si lo que compara es igual
            if(!strcmp(s,symbol_table[i])){

                return 1;
            }
    }

    return 0;
}
void enter(string s){



 if(!lookup(s)){
        strcpy(symbol_table[symbol_table_i], s);
        symbol_table_i = symbol_table_i + 1 ;
    }

}



//imprime la tabla de los simbolos
void verSymbol_table(){
    for (int i = 0; i < 1000; i++) {
            printf(symbol_table[i]);
    }

}




/*Funciones encargadas de leer el archivo*/

/* ************************************** */

/*Función encargada de ller el archivo, el cual se abre y guarda en el puntero file*/
void leerArchivo(){
    printf("Ruta del archivo:\n");
    char NombreArchivo[50];
    gets(NombreArchivo);
    file = fopen(NombreArchivo, "r");
}

/*Función que indica si se leyó o no correctamente el archivo*/
bool seLeyoArchivo(){
    if (file) {
        return true;

    }else{
    return false;
    }

}

/*Función que se encarga de cerrar el archivo*/
void cerrarArchivo(){
    fclose(file);
}

/* ************************************** */


/*Scanner: encargado de comprobar que los tokens estén bien escritos*/


/* ***************************************************************************************************** */

/*Función que imprime en pantalla un mensaje de error léxico*/
void lexical_error(int in_char){
    printf("Se ha producido un error, %d  \n",in_char);

}

/*Función que se encarga de actualizar el token_buffer, el cual irá guardando los caracteres del archivo*/
void buffer_char(int c){
    token_buffer[i]=toupper(c);

    i=i+1;
}

/*Función que se encarga de limpiar el token_buffer para que sea capaz de tomar nuevos caracteres*/
void clear_buffer(){
    i=0;




    //temporarie=token_buffer;
    memset(&token_buffer[0], 0, sizeof(token_buffer));
}




/*Función encargada de comparar el token_buffer y ver si este coincide con una palabra reservada para retornarla
En caso contrario, retornará el token ID*/
token check_reserved(){


     if(token_buffer[0]=='B' && token_buffer[1]=='E' && token_buffer[2]=='G' &&token_buffer[3]=='I'&&token_buffer[4]=='N'){

      return BEGIN;
     }

     else{

          if(token_buffer[0]=='W'&&token_buffer[1]=='R'&&token_buffer[2]=='I'&&token_buffer[3]=='T'&&token_buffer[4]=='E'){

               return WRITE;
          }

          else{

              if(token_buffer[0]=='E'&&token_buffer[1]=='N'&&token_buffer[2]=='D'){

              return END;
              }

              else{

                  if(token_buffer[0]=='R'&&token_buffer[1]=='E'&&token_buffer[2]=='A'&&token_buffer[3]=='D'){

                        return READ;}

                  else{

                      if(token_buffer[0]=='S'&&token_buffer[1]=='C'&&token_buffer[2]=='A'&&token_buffer[3]=='N'&&token_buffer[4]=='E'&&token_buffer[5]=='O'&&token_buffer[6]=='F'){

                            return SCANEOF;}

                      else{


                          return ID;
                          }
                      }
              }
          }
      }


 }



/*Función encargada de ir leyendo el archivo e ir formando el token_buffer por medio de llamadas a las funciones correspondientes.
  Dará error cuando algún token no coincida con el token_buffer*/
token scanner(){
	int in_char, c;

	clear_buffer();
	if(feof(stdin))
		return SCANEOF;
	while ((in_char = getc(file)) != EOF){

		if (isspace(in_char))
			continue; /*No se hace nada*/
		else if (isalpha(in_char)){
			/* En esta sección se reconocen los identificadores */
			/*
			* ID ::= LETTER | ID LETTER
			*				| ID DIGIT
			*				| ID UNDERSCORE
			*/



			buffer_char(in_char);

			//putchar(in_char);

			for (c = getc(file); isalnum(c) || c == '_'; c = getc(file)){

				//Cada caracter es enviado a la función buffer char, para modificar el token_buffer
				buffer_char(c);
				//putchar(c);

            }

			//Devuelve el caracter del espacio al archivo que se está leyendo

			ungetc(c, stdin);

			//Se llama a la función check_reserved, para comparar las palabras reservadas
			return check_reserved();
		}
		else if (isdigit(in_char)){
			/* En esta sección se reconocen los literales enteros */
			/*
			* INTLITERAL ::= DIGIT |
			*				 INTLITERAL DIGIT
			*/

			buffer_char(in_char);
			for (c = getc(file); isdigit(c); c = getc(file))
				buffer_char(c);
			ungetc(c, stdin);


			return INTLITERAL;

		}

		//Se comprueba si el caracter o caracteres actuales coinciden con algunos de los símbolos disponibles para micro
		else if (in_char == '('){


			return LPAREN;
        }

		else if (in_char == ')'){

			return RPAREN;

        }

		else if (in_char == ';'){


			return SEMICOLON;

        }

		else if (in_char == ','){


			return COMMA;

        }

		else if (in_char == '+'){


			return PLUSOP;
        }

		else if (in_char == ':'){
			/* Se espera ":="*/


			c = getc(file);

			if (c == '='){


				return ASSIGNOP;
            }

			else {


				ungetc(c, stdin);
				lexical_error(in_char);

			}
		}

		else if(in_char == '-'){
			/*se espera --,inicio del comentario*/

			c = getc(file);
			if (c == '-'){

				while ((in_char = getchar()) != '\n');

			}

			else{


				ungetc(c,stdin);
				return MINUSOP;

			}

		}
		else{

		    //putchar(c);
            //putchar(in_char);
			lexical_error(in_char);

		}

	}

	parada=1;

}

/* ***************************************************************************************************** */


/*Parser: encargado de comprobar que se cumple con las gramáticas libres de contexto*/


/* ***************************************************************************************************** */


//Función encargada de llamar al scanner para tomar el siguiente token
token next_token(void){

    current_token = scanner();
    return current_token;

}

//Función encargada de dar un mensaje de error de sintaxis, con respecto al token que generó el error
void syntax_error(token comparar){

    printf("Error, no se encontro la palabra esperada");

}

//Función encargada de llamar al scanner para conocer el siguiente token y conocer si coincide con la estructura correcta del programa
void match(token comparar){

    /*Se obtiene el siguiente token, llamando a la función correspondiente*/
    token siguiente = next_token();/*
    printf("%i\¿\n", comparar);
    printf("\n");
    printf("%i\¿\n", siguiente);*/
    /*Se comparan el token siguiente con el token de entrada, si coinciden, está correcto sintácticamente
    En caso contrario, se llama a la función de syntax error*/
    if (comparar != siguiente){

        syntax_error(comparar);

    }

}


















void program(void){

	/* <program> ::= BEGIN <statement list> END*/

	match(BEGIN);
	statement_list();

	if(current_token != END)
        syntax_error(current_token);

}



void statement_list(void){

	/* <statement list> ::= <statement> { <statement> }*/

	statement(true);
	while (1) {
		switch (next_token()){
		case ID:
		case READ:
		case WRITE:
			statement(false);
			break;
		default:
			return;
		}
	}
}

void statement(bool primerSentencia){

    /* <STATEMENT> ::= ID := <expression> ;*/
    if (primerSentencia)
        next_token();
	//token tok = next_token();
	expr_rec result;
    expr_rec target;
	switch (current_token){
		case ID:


		/*Se omitió el match(ID), porque el tok ya contiene al next_token y es evaluado en uno de los case
        /*match(ID);*/

        target.kind=IDEXPR;

        check_id(token_buffer);
        strcpy(target.name,token_buffer);
		match(ASSIGNOP);
		expression1(& result);
		assign(result,target);

		/*Se omitió el match(SEMICOLON), porque en la función expression ya se tomó el netx_token*/
		/*match(SEMICOLON);*/

		//printf("%i\n",current_token);

		if(current_token != SEMICOLON)
            syntax_error(current_token);



		break;

		case READ:

		/* <statement> ::= READ ( <id list> ) ;*/

		/*Se omitió match(READ) ya que el tok es evaluado en este case*/
		/*match(READ);*/

		match(LPAREN);
		id_list();

		if(current_token != RPAREN)
            syntax_error(current_token);

		//match(RPAREN);
		match(SEMICOLON);
		break;

		case WRITE:

		/* <statement> ::= WRITE ( <expr list> ) ;*/
		/*Se omitió match(WRITE) ya que el tok es evaluado en este case*/
		/*match(WRITE);*/

		match(LPAREN);
		expr_list();

		if(current_token != RPAREN)
            syntax_error(current_token);


		//match(RPAREN);

		match(SEMICOLON);
		break;

	default:
		syntax_error(current_token);
		break;
	}
}




void id_list(void){

	/* <id list> ::= ID { , ID }*/

	match(ID);


	token tok;
	for(tok = next_token(); tok == COMMA; tok = next_token()){
        printf("Entro");
        //Se omite porque ya se evaluó en tok == COMMA
        //match(COMMA);
		match(ID);
    }
	/*
	while(next_token() == COMMA){
		match(COMMA);
		match(ID);
	}*/

}



/*

void expression(void){

    /*
	* <expression> ::= <primary> {<add op> <primary>}



	token t;
	primary();

	/*Ciclo for que lee tokens hasta que sean diferentes de PLUSOP y MINUSOP
	for(t = next_token(); t == PLUSOP || t == MINUSOP; t = next_token()){

		add_op();
		primary();

	}

}

*/



void expr_list(void){

	/* <expr list> ::= <expression> { , <expression> }*/
    expr_rec result;
	expression1(& result);
    //expression();

	//token tok;


	while(current_token == COMMA){
        printf("Entra");
		//match(COMMA);

		//expression();
        expression1(result);
    }

	/*while(next_token() == COMMA){
        printf("Entra");
		match(COMMA);
		//expression();
		expression1(result);

	}*/

}





void add_op(op_rec *op){

	//token tok = next_token(); //¿Current token?

	token tok = current_token;



    /* <addop> ::= PLUSOP | MINUSOP*/

	if (tok != PLUSOP && tok != MINUSOP)
		syntax_error(tok);

    else{
        if(tok == PLUSOP)
            op->operator = PLUS;
        else
            op->operator = MINUS;
    }
		/*Se omitió el match(tok) ya que ya se obtiene del current_token*/
		/*match(tok);*/


}



void primary(expr_rec *result){

	token tok = next_token();

	//printf("%i\n", tok);

	switch(tok){
		case LPAREN:
		/* <primary> ::= (<expression>)*/

        /*Se omitió el match(LPAREN) ya que el next_token guardado en tok es evaluado en este case*/
		//match(LPAREN);

		current_token = LPAREN;

        result->kind = TEMPEXPR;
        strcpy(result->name,token_buffer);




		expression1(result);

		//expression();
		if(current_token != RPAREN)
            syntax_error(current_token);

		/*Se omite match(RPAREN) ya que en el for de la función expression se obtiene este token*/
		//match(RPAREN);

		break;

		case ID:
		/*<primary> ::= ID*/

        /*Se asigna como token actual al ID*/
        check_id(token_buffer);
        current_token = ID;

        result->kind = IDEXPR;
        strcpy(result->name,token_buffer);




        /*Se omite match(ID) ya que en el for de la función expression se obtiene este token*/
		/*match(ID);*/
		break;

		case INTLITERAL:

		/*<primary> ::= INTLITERAL*/

        /*Se asigna como token actual al INTLITERAL*/
        current_token = INTLITERAL;

        result->kind = LITERALEXPR;

        result->val = atoi(token_buffer);


		/*Se omite match(INTLITERAL) ya que en el for de la función expression se obtiene este token*/
		//match(INTLITERAL);
		break;

	default:
		syntax_error(tok);
		break;

	}

}

/* ***************************************************************************************************** */



/*
* Inicio del analizador semantico
* La parte donde definen las estructuras necesarias estan arriba
*/

void generate(string a,string b, string c, string d, char *destino)
{   strcat(destino, a);
    strcat(destino, b);
    strcat(destino, c);
    strcat(destino, d);
    strcat(destino, "\n");
}
void ingresarADDOP(string num1, string num2){
    if(num1[0]!='#'){
        generate("  LDR", " R4, addr_of_",  num1, "", startH);
        generate("  LDR", " R4, ",  "[R4]", "", startH);

    }else{
        generate("  MOV", " R4, ",  num1, "", startH);

    }

    if(num2[0]!='#'){
         generate("  LDR", " R5, addr_of_",  num2, "", startH);
         generate("  LDR", " R5, ",  "[R5]", "", startH);

    }else{
        generate("  MOV", " R5, ",  num2, "", startH);

    }


    generate("  ADD", " R4, ", "R4,", "R5\n" , startH);
}


void ingresarMINUSOP(string num1, string num2){
    if(num1[0]!='#'){
        generate("  LDR", " R4, addr_of_",  num1, "", startH);
        generate("  LDR", " R4, ",  "[R4]", "", startH);

    }else{
        generate("  MOV", " R4, ",  num1, "", startH);

    }

    if(num2[0]!='#'){
         generate("  LDR", " R5, addr_of_",  num2, "", startH);
         generate("  LDR", " R5, ",  "[R5]", "", startH);

    }else{
        generate("  MOV", " R5, ",  num2, "", startH);

    }
    generate("  SUB", " R4, ", "R4,", "R5\n" , startH);
}

void finalizarArchivo(){
    generate("    ", "MOV ", "R1, ", "#1", startH);
    generate("    ", "SWI ", "0", "", startH);
}

char *extract(expr_rec *ex)
{

  int num = ex->val;
  string snum;

  switch(ex->kind){
      case IDEXPR:
        return ex->name;
      case LITERALEXPR:

        // convert 123 to string [buf]

        sprintf(ex->name, "#%i", num);

        //strncpy(strcat(h, ex->name), ex->name, 0);

        return ex->name;
      case TEMPEXPR:

        return ex->name;
  }
}
char *extract_op(op_rec *ope)
{


  switch(ope->operator){
      case PLUS:

        return "Add";
      case MINUS:

        // convert 123 to string [buf]

        return "Sub";

  }
}


void check_id(string s){

    if(! lookup(s)){
        enter(s);
        generate("addr_of_", s, ": .word ", s, address);
        generate(".balign 4\n", s,":\n    .word ", "0", data);
    }
}

//addr_of_myvar1 : .word myvar1

char *get_temp(void)
{
    /*max temporary allocated so far*/
    static int max_temp=0;
    static char tempname[MAXIDLEN];


    max_temp++;
    sprintf(tempname,"Temp&%d",max_temp);
    check_id(tempname);
    return tempname;
}

void start(void){
    /*Semantic initializations, none needed*/

}

void finish(void){
    /*Generate  code to finish program.*/
    strcat(finalFile, data);
    generate("  BX", " ","lr", " ", startH);
    strcat(finalFile, startH);
	//strcat(finalFile, end);
	strcat(finalFile, address);
	printf(finalFile);
	FILE *fp;
	fp = fopen ( "PruebaA.s", "ab+" );

 	fputs( finalFile, fp );

 	fclose ( fp );

}

/*
.balign 4
myvar1:
    .word 3

*/

void assign(expr_rec target, expr_rec source){
    /*Generate code for assigment.*/

    /*if (target.flag == 1){
        sprintf(target.name, "%i", target.val);
        generate(".balign 4\n", extract(& source),":\n    .word ", target.name, data);
    }
    else{
        generate(".balign 4\n", extract(& source),":\n    .word ", "0", data);
    }*/

    // falta if: cuando pasamos un intliteral se pone un #


    generate("  LDR ", "r1, addr_of_", extract(& source), "", startH);
    //if
    if (target.kind == LITERALEXPR){
        sprintf(target.name, "#%i", target.val);
        generate("  MOV ", "r3, ",target.name, "", startH);
        memset(target.name, 0, sizeof(target.name));
    }
    else{
        generate("  ADR ", "r3, ",target.name, "", startH);
    }

    generate("  STR ", "r3, ", "[r1] ", "\n", startH);





    //generate("Store", extract(& source), target.val,"",data);
}
op_rec process_op(void)
{
/*Produce operator descriptor. */
    op_rec o;
    if(current_token==PLUSOP)
        o.operator=PLUS;
    else
        o.operator=MINUS;
    return o;
}

expr_rec gen_infix(expr_rec e1,op_rec op,expr_rec e2)
{
    expr_rec e_rec;
    /*An expr_rec with temp variant set.*/
    e_rec.kind= TEMPEXPR;

    /*
    *Generate code for infix operation.
    *Get result temp and set up semantic record.
    *for result.
    */

    strcpy(e_rec.name,get_temp());
    if(extract_op(& op)=="Add")
    {
        ingresarADDOP(extract(& e1),extract(& e2));
        generate("  LDR ", "r1, addr_of_", e_rec.name, "", startH);
        generate("  STR ", "r4, ", "[r1] ", "\n", startH);
    }
    else
    {
        ingresarMINUSOP(extract(& e1),extract(& e2));
        generate("  LDR ", "r1, addr_of_", e_rec.name, "", startH);
        generate("  STR ", "r4, ", "[r1] ", "\n", startH);
    }
    //generate(extract_op(& op), extract(& e1),extract(& e2),e_rec.name);

    return e_rec;
}
expr_rec process_literal(void){

	expr_rec t;
	/*
	*	Convert literal to a numeric representation
	*	and build sematic record.
	*/
	t.kind = LITERALEXPR;

	(void) sscanf(token_buffer, "%d", & t.val);
	return t;
}

void read_id(expr_rec in_var)
{
    /*Generate code for read.*/
    generate("Read", in_var.name, "Integer","",data);
}
expr_rec process_id(void)
{
    expr_rec t;
    /*
    *Declare ID and build a
    *corresponding semantic record.
    */
    check_id(token_buffer);
    t.kind=IDEXPR;

    strcpy(t.name,token_buffer);
    return t;
}

void write_expr(expr_rec out_expr)
{
    generate("Write", extract(&out_expr),"Integer","",data);
}


void expression1(expr_rec * result)
{

    expr_rec left_operand, right_operand;
    op_rec op;
    primary(& left_operand);
    token t;
    for(t = next_token(); t == PLUSOP || t == MINUSOP; t = next_token()){

        add_op(& op);
        primary(& right_operand);

        left_operand=gen_infix(left_operand,op,right_operand);
    }


    /*while(next_token() == PLUSOP || next_token()==MINUSOP)
    {   printf("Entro al while expression\n");
        add_op(& op);
        primary(& right_operand);
        left_operand=gen_infix(left_operand,op,right_operand);
    }*/
    *result=left_operand;
  }

void system_goal(void){

	/* <system goal> ::= <program> SCANEOF*/

    start();
	program();
	match(SCANEOF);
	finish();

}




