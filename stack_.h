#ifndef stack_
#define stack_
#include <stdio.h>
 
/**
 * @brief Struct enum:
 *
 * Estrutura para identificar os tipos dos elementos. 
 */

typedef enum {
  CHAR, /**< Campo para indicar o tipo Char */
  DBL, /**< Campo para indicar o tipo double */
  STR, /**< Campo para indicar o tipo string */
  LONG, /**< Campo para indicar o tipo long */
  ARR, /**< Campo para indicar o tipo array */
  BLC /**< Campo para indicar o tipo bloco */
} TYPE;

struct stack;

/**
 * @brief Struct elem_da_stack
 * 
 * Estrutura para guardar qualquer tipo de elemento no array.
 */

typedef struct elem_da_stack {
  TYPE t; /**< Campo para indicar o tipo do elemento*/
  union {
    double d; /**< Campo para guardar o tipo double */
    long l; /**< Campo para guardar o tipo long */
    char *s; /**< Campo para guardar o tipo string */
    char c; /**< Campo para guardar o tipo Char */
    struct stack (*arr); /**< Campo para guardar o tipo array */
    char *bloco; /**< Campo para guardar o tipo bloco */
  } valor_guardado; /**< Union dos valores*/
} elem_da_stack;

/**
 * Struct stack:
 *
 * Estrutura que define a stack. Possui um array para 1000 elementos e um stack pointer. 
*/
typedef struct stack{
    elem_da_stack *stack; /**< Campo para indicar o tipo Char */
    int sp; /**< Campo para indicar o stack pointer */
    int cp; /**< Campo para indicar a capacidade */
} stack;

/**
 * Inicialização da função new_stack.
 */
stack *new_stack ();
/**
 * Inicialização da função inicia_variaveis.
 */
void inicia_variaveis (elem_da_stack v []);
/**
 * Inicialização da função push.
 */
void push (stack *s, elem_da_stack elem);
/**
 * Inicialização da função pop.
 */
elem_da_stack pop(stack *s);
/**
 * Inicialização da função pushvalor.
 */
int pushvalor (stack *s, char *token);
/**
 * Inicialização da função resultado.
 */
TYPE resultado (TYPE x, TYPE y);
/**
 * Inicialização da função add.
 */
int add (stack *s, char *token);
/**
 * Inicialização da função sub.
 */
int sub (stack *s, char *token);
/**
 * Inicialização da função mult.
 */
int mult (stack *s,elem_da_stack var [], char *token);
/**
 * Inicialização da função divs.
 */
int divs (stack *s, char *token);
/**
 * Inicialização da função inc.
 */
int inc (stack *s, char *token);
/**
 * Inicialização da função dec.
 */
int dec (stack *s, char *token);
/**
 * Inicialização da função expp.
 */
int expp (stack *s, char *token);
/**
 * Inicialização da função troca.
 */
int op_logica (stack *s, char *token);
/**
 * Inicialização da função maior_log_aux.
 */
long maior_log_aux (elem_da_stack x, elem_da_stack y) ;
/**
 * Inicialização da função maior_logico.
 */
int maior_logico (stack *s, char *token);
/**
 * Inicialização da função menor_logico.
 */
int menor_logico (stack *s, char *token);
/**
 * Inicialização da função if_then_else.
 */
int if_then_else (stack *s, char *token);
/**
 * Inicialização da função negacao.
 */
int negacao (stack *s, char *token);
/**
 * Inicialização da função igual.
 */
int igual (stack *s, char *token);
/**
 * Inicialização da função concatena.
 */
 void concatena (stack *s,elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função concatenanvezes.
 */
 void replicar (stack *s,elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função tamanho.
 */
int tamanho (stack *s,elem_da_stack var [],char * token);
/**
 * Inicialização da função procuraindice.
 */
void procuraindice (stack *s,elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função pegaelemint.
 */
void pegaeleminit (stack *s,elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função pegaelemend.
 */
void pegaelemend (stack *s,elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função retiraeleminit.
 */
void retiraeleminit (stack *s,elem_da_stack x);
/**
 * Inicialização da função retiraelemend.
 */
void retiraelemend (stack *s,elem_da_stack x);
/**
 * Inicialização da função findsubstring.
 */
void findsubstring (stack *s, elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função lertudo.
 */
int lertudo (stack *s, char *token);
/**
 * Inicialização da função tokenizer.
 */
void tokenizer (stack *s, elem_da_stack v [],char *token);
/**
 * Inicialização da função tokenizer_array.
 */
void tokenizer_array (stack *arr, elem_da_stack v [],char *token);
/**
 * Inicialização da função colocar_stack.
 */
void coloca_stack (stack *s, elem_da_stack x);
/**
 * Inicialização da função colocar_stack.
 */
void separa_string (stack *s, elem_da_stack x, elem_da_stack y);
/**
 * Inicialização da função colocar_stack.
 */
int separar_string_por (stack *s, char *token);
/**
 * Inicialização da função executarbloco.
 */
void executarbloco (stack *s, elem_da_stack var [],char *str) ;
/**
 * Inicialização da função aplica_bloco.
 */
void aplica_bloco (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var []) ;
/**
 * Inicialização da função aplica_bloco.
 */
void fold (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var []) ;
/**
 * Inicialização da função filtra.
 */
void filtra (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var []) ;
/**
 * Inicialização da função ordena.
 */
void ordena (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var[]) ;
/**
 * Inicialização da função executar_vdd.
 */
int executar_vdd (stack *s, elem_da_stack var [],char *token) ;
/**
 * Inicialização da função handle.
 */
void handle (stack *s,elem_da_stack v [], char *token);

#endif