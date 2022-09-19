#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack_.h"

/**
* Função conjuncao_check_false:
*
* Esta função, torna o valor de x igual ao de y caso y seja falso, seja ele do tipo DBL, LONG ou CHAR.
*/

elem_da_stack conjuncao_check_false ( elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (y.valor_guardado.d == 0) x = y;
    }    
    if (y.t == LONG) {
        if (y.valor_guardado.l == 0) x = y;

    }    
    if (y.t == CHAR) {
        if (y.valor_guardado.c == 0) x = y;
    }
    return x;
}

/**
* Função conjução:
*
* Retira um elemento da stack para x e outro para y, através da função pop
*
* Devolve à stack, através da função push, o elemento r, descoberto através da função conjuncao_check_false entre x e y.
*/

void conjuncao (stack *s) {
    elem_da_stack x = pop(s);
    elem_da_stack y = pop(s);
    elem_da_stack r;
    r = conjuncao_check_false( x,y);
    push (s,r);
}

/**
* Função disjuncao_check_false:
*
* Esta função, torna o valor de y igual ao de x caso y seja falso, seja ele do tipo DBL, LONG ou CHAR
*/

elem_da_stack disjuncao_check_false ( elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (y.valor_guardado.d == 0) y = x;
    }    
    if (y.t == LONG) {
        if (y.valor_guardado.l == 0) y = x;

    }    
    if (y.t == CHAR) {
        if (y.valor_guardado.c == 0) y = x;
    }
    return y;
}

/**
* Função disjunção:
*
* Retira um elemento da stack para x e outro para y, através da função pop
*
* Devolve à stack, através da função push, o elemento r, descoberto através da função disjuncao_check_false entre x e y.
*/

void disjuncao (stack *s){
    elem_da_stack x = pop(s);
    elem_da_stack y = pop(s);
    elem_da_stack r;
    r = disjuncao_check_false( x,y);
    push (s,r);
}

/**
* Funções menor_double.
*
* Esta função verifica qual dos 2 elementos (x ou y) é menor, seja ele do tipo DBL, LONG ou CHAR, e devolve-o à stack.
*/

void menor_double (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (x.valor_guardado.d < y.valor_guardado.d) push (s,x);
        else push (s,y);
    }
    if (y.t == LONG) {
        if (x.valor_guardado.d < y.valor_guardado.l) push (s,x);
        else push (s,y);
    }    
    if (y.t == CHAR) {
        if (x.valor_guardado.d < y.valor_guardado.c) push (s,x);
        else push (s,y);
    }
}

/**
 * Função menor_long.
 * 
 * Esta função verifica qual dos 2 elementos (x ou y) é menor, seja ele do tipo DBL, LONG ou CHAR, e devolve-o à stack.
*/

void menor_long (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (x.valor_guardado.l < y.valor_guardado.d) push (s,x);
        else push (s,y);
    }
    if (y.t == LONG) {
        if (x.valor_guardado.l < y.valor_guardado.l) push (s,x);
        else push (s,y);
    }    
    if (y.t == CHAR) {
        if (x.valor_guardado.l < y.valor_guardado.c) push (s,x);
        else push (s,y);
    }
}

/**
 * Função menor_char.
 * 
 * Esta função verifica qual dos 2 elementos (x ou y) é menor, seja ele do tipo DBL, LONG ou CHAR, e devolve-o à stack.
*/

void menor_char (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (x.valor_guardado.c < y.valor_guardado.d) push (s,x);
        else push (s,y);
    }
    if (y.t == LONG) {
        if (x.valor_guardado.c < y.valor_guardado.l) push (s,x);
        else push (s,y);
    }    
    if (y.t == CHAR) {
        if (x.valor_guardado.c < y.valor_guardado.c) push (s,x);
        else push (s,y);
    }
}

/**
* Função menor_str:
*
* Através da função strcmp verificamos caracter a caracter se a string é igual.
*
* Caso sejam diferentes devolve um valor maior que 0 e, consequentemente devolve x, caso contrário devolve y.
*/

void menor_str (stack *s, elem_da_stack x, elem_da_stack y) {
    if (strcmp (y.valor_guardado.s, x.valor_guardado.s) > 0) push(s,x);
    else push (s,y);
}

/**
* Função menor:
*
* Retira um elemento da stack para x e outro para y através da função pop;
*
* Dependendo do tipo do elemento, usa uma das funções auxiliares anteriores para descobrir o menor.
*/

void menor (stack *s) {
    elem_da_stack x = pop(s);
    elem_da_stack y = pop(s);
    if (x.t == DBL) menor_double (s,x,y);
    if (x.t == LONG) menor_long (s,x,y);
    if (x.t == CHAR) menor_char (s,x,y);
    if (x.t == STR) menor_str (s,x,y);
}

/**
* Funções maior_double;
*
* Esta função verifica qual dos 2 elementos (x ou y) é maior, seja ele do tipo DBL, LONG ou CHAR, e devolve-o à stack.
*/

void maior_double (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (x.valor_guardado.d > y.valor_guardado.d) push (s,x);
        else push (s,y);
    }
    if (y.t == LONG) {
        if (x.valor_guardado.d > y.valor_guardado.l) push (s,x);
        else push (s,y);
    }    
    if (y.t == CHAR) {
        if (x.valor_guardado.d > y.valor_guardado.c) push (s,x);
        else push (s,y);
    }
}

/**
* Funções maior_long:
*
* Esta função verifica qual dos 2 elementos (x ou y) é maior, seja ele do tipo DBL, LONG ou CHAR, e devolve-o à stack.
*/

void maior_long (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (x.valor_guardado.l > y.valor_guardado.d) push (s,x);
        else push (s,y);
    }
    if (y.t == LONG) {
        if (x.valor_guardado.l > y.valor_guardado.l) push (s,x);
        else push (s,y);
    }    
    if (y.t == CHAR) {
        if (x.valor_guardado.l > y.valor_guardado.c) push (s,x);
        else push (s,y);
    }
}

/**
* Funções maior_char:
*
* Esta função verifica qual dos 2 elementos (x ou y) é maior, seja ele do tipo DBL, LONG ou CHAR, e devolve-o à stack.
*/

void maior_char (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) {
        if (x.valor_guardado.c > y.valor_guardado.d) push (s,x);
        else push (s,y);
    }
    if (y.t == LONG) {
        if (x.valor_guardado.c > y.valor_guardado.l) push (s,x);
        else push (s,y);
    }    
    if (y.t == CHAR) {
        if (x.valor_guardado.c > y.valor_guardado.c) push (s,x);
        else push (s,y);
    }
}

/**
* Função maior_str:
*
* Através da função strcmp verificamos caracter a caracter se a string é igual.
*
* Caso sejam diferentes devolve um valor maior que 0 e, consequentemente devolve y, caso contrário devolve x.
*/

void maior_str (stack *s, elem_da_stack x, elem_da_stack y) {
    if (strcmp (y.valor_guardado.s, x.valor_guardado.s) > 0) push(s,y);
    else push (s,x);
}

/**
* Função maior:
*
* Retira um elemento da stack para x e outro para y através da função pop;
*
* Dependendo do tipo do elemento, usa uma das funções auxiliares anteriores para descobrir o maior:
*/

void maior (stack *s) {
    elem_da_stack x = pop(s);
    elem_da_stack y = pop(s);
    if (x.t == DBL) maior_double (s,x,y);
    if (x.t == LONG) maior_long (s,x,y);
    if (x.t == CHAR) maior_char (s,x,y);
    if (x.t == STR) maior_str (s,x,y);
}

/**
* Função op_logica:
*
* Esta função verifica o valor da token [1]  e:
*
*       - se token [1] == '&', recorre à função conjuncao;
*
*       - se token [1] == '|', recorre à função disjuncao;
*
*       - se token [1] == '<', recorre à função menor;
*
*       - se token [1] == '>', recorre à função maior;
*       .
*/

int op_logica (stack *s, char *token) {
    if (token[0] == 'e') {
        if (token [1] == '&') conjuncao (s);
        if (token [1] == '|') disjuncao (s);
        if (token [1] == '<') menor (s);
        if (token [1] == '>') maior (s);
        return 1;
    }
    return 0;
}

/**
* Funções maior_log_double:
*
* Caso o valor de y for maior, seja ele do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

long maior_log_double (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) 
        if (y.valor_guardado.d > x.valor_guardado.d) return 1;
    if (y.t == LONG) 
        if (y.valor_guardado.l > x.valor_guardado.d) return 1;
    if (y.t == CHAR) 
        if (y.valor_guardado.c > x.valor_guardado.d) return 1;
    return 0;
}

/**
* Funções maior_log_long:
*
* Caso o valor de y for maior, seja ele do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

long maior_log_long (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) 
        if (y.valor_guardado.d > x.valor_guardado.l) return 1;
    if (y.t == LONG) 
        if (y.valor_guardado.l > x.valor_guardado.l) return 1;
    if (y.t == CHAR) 
        if (y.valor_guardado.c > x.valor_guardado.l) return 1;
    return 0;
}

/**
* Funções maior_log_char:
*
* Caso o valor de y for maior, seja ele do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

long maior_log_char (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) 
        if (y.valor_guardado.d > x.valor_guardado.c) return 1;
    if (y.t == LONG) 
        if (y.valor_guardado.l > x.valor_guardado.c) return 1;
    if (y.t == CHAR) 
        if (y.valor_guardado.c > x.valor_guardado.c) return 1;
    return 0;
}

/**
* Função maior_log_str:
*
* Através da função strcmp verificamos caracter a caracter se a string é igual.
*
* Caso sejam diferentes e y seja maior que x, devolve como verdadeiro.
*/

long maior_log_str (elem_da_stack x, elem_da_stack y) {
    if (strcmp (y.valor_guardado.s, x.valor_guardado.s) > 0) return 1;
    else return 0;
}

/**
* Função maior_log_aux:
*
* Retira um elemento da stack para x e outro para y através da função pop;
*
* Dependendo do tipo do elemento, usa uma das funções auxiliares anteriores para descobrir se é verdadeiro.
*/

long maior_log_aux (elem_da_stack x, elem_da_stack y) {
    long r = 0;
    if (x.t == DBL) r = maior_log_double (x, y);   
    if (x.t == LONG) r = maior_log_long (x, y);   
    if (x.t == CHAR) r = maior_log_char (x, y);
    if (x.t == STR) r = maior_log_str (x, y);
    return r; 
}

/**
* Função maior_logico:
*
* Se token[0] for '>', retiramos um elemento da stack para x e outro para y através da função pop.
*
* Caso x seja do tipo LONG e y seja do tipo STR ou ARR, recorremos à função pegaelemend para retirarmos elementos do fim do array.
*
* Caso contrário, recorremos à função maior_log_aux para descobrir o maior entre o x e y e devolvermos à stack através da função push.
*/

int maior_logico (stack *s, char *token) {
    if (token [0] == '>') {
        elem_da_stack x = pop (s);
        elem_da_stack y = pop (s);
        if ((y.t == STR || y.t == ARR) && x.t == LONG) pegaelemend (s,x,y);
        else {
        elem_da_stack r = (elem_da_stack) {.t = LONG, .valor_guardado.l = maior_log_aux (x,y)};
        push (s,r);
        }
        return 1;
    }
    return 0;
}

/**
* Funções menor_log_double:
*
* Caso o valor de y for menor, seja ele do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

long menor_log_double (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) 
        if (y.valor_guardado.d < x.valor_guardado.d) return 1;
    if (y.t == LONG) 
        if (y.valor_guardado.l < x.valor_guardado.d) return 1;
    if (y.t == CHAR) 
        if (y.valor_guardado.c < x.valor_guardado.d) return 1;
    return 0;
}

/**
* Funções menor_log_long:
*
* Caso o valor de y for menor, seja ele do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

long menor_log_long (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) 
        if (y.valor_guardado.d < x.valor_guardado.l) return 1;
    if (y.t == LONG) 
        if (y.valor_guardado.l < x.valor_guardado.l) return 1;
    if (y.t == CHAR) 
        if (y.valor_guardado.c < x.valor_guardado.l) return 1;
    return 0;
}

/**
* Funções menor_log_char:
*
* Caso o valor de y for menor, seja ele do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

long menor_log_char (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL) 
        if (y.valor_guardado.d < x.valor_guardado.c) return 1;
    if (y.t == LONG) 
        if (y.valor_guardado.l < x.valor_guardado.c) return 1;
    if (y.t == CHAR) 
        if (y.valor_guardado.c < x.valor_guardado.c) return 1;
    return 0;
}

/**
* Função menor_log_str:
*
* Através da função strcmp verificamos caracter a caracter se a string é igual.
*
* Caso sejam diferentes e y seja menor que x, devolve como verdadeiro.
*/

long menor_log_str (elem_da_stack x, elem_da_stack y) {
    if (strcmp (y.valor_guardado.s, x.valor_guardado.s) < 0) return 1;
    else return 0;
}

/**
* Função menor_log_aux:
*
* Retira um elemento da stack para x e outro para y através da função pop;
*
* Dependendo do tipo do elemento, usa uma das funções auxiliares anteriores para descobrir se é verdadeiro.
*/

long menor_log_aux (elem_da_stack x, elem_da_stack y) {
    long r = 0;
    if (x.t == DBL) r = menor_log_double (x, y);   
    if (x.t == LONG) r = menor_log_long (x, y);   
    if (x.t == CHAR) r = menor_log_char (x, y);
    if (x.t == STR) r = menor_log_str (x,y);
    return r; 
}

/**
* Função menor_logico:
*
* Se token[0] for '<', retiramos um elemento da stack para x e outro para y através da função pop.
*
* Caso x seja do tipo LONG e y seja do tipo STR ou ARR, recorremos à função pegaeleminit para retirarmos elementos do início do array.
*
* Caso contrário, recorremos à função menor_log_aux para descobrir o menor entre o x e y e devolvermos à stack através da função push.
*
*/


int menor_logico (stack *s, char *token) {
    if (token [0] == '<') {
        elem_da_stack x = pop (s);
        elem_da_stack y = pop (s);
        if ((y.t == STR || y.t == ARR) && x.t == LONG) pegaeleminit (s,x,y);
        else {
        elem_da_stack r = (elem_da_stack) {.t = LONG, .valor_guardado.l = menor_log_aux (x,y)};
        push (s,r);
        }
        return 1;
    }
    return 0;
}

/**
* Função verdadeiro:
*
* Verifica se x é verdadeiro e, se o for devolve o r como 1, caso contrário devolve como 0.
*/

int verdadeiro (elem_da_stack x) {
    int r = 0;
    if (x.t== LONG) 
        if (x.valor_guardado.l) r = 1;
    if (x.t== DBL) 
        if (x.valor_guardado.d) r = 1;    
    if (x.t== CHAR) 
        if (x.valor_guardado.c) r = 1;
    if (x.t == STR) 
        if (x.valor_guardado.s[0] != '\0') r = 1;
    if (x.t == ARR)
        if (x.valor_guardado.arr->sp != 0) r = 1; 
    return r;
}

/**
* Função if_then_else
*
* Se token[0] for '?', retiramos um elemento da stack para x e outro para y através da função pop.
*
* Retira 3 elementos da stack através da função pop.
*
* Se z, recorrendo à função verdadeiro, tiver valor 1, devolvemos à stack o elemento y, caso contrário é devolvido o x.
*/

int if_then_else (stack *s, char *token) {
    if (token [0] == '?') {
        elem_da_stack x = pop (s);
        elem_da_stack y = pop (s);
        elem_da_stack z = pop (s);
        if (verdadeiro(z)) push (s,y);
        else push (s,x);
        return 1;
    }
    return 0;
}

/**
* Função negacao:
*
* Se token[0] for '!', retiramos um elemento da stack para x através da função pop.
*
* Se x for verdadeiro, devolvemos à stack o elemento fal, neste caso, que é falso. Caso contrário é devolvido um elemento verdadeiro.
*/

int negacao (stack *s , char * token) {
    if (token [0] == '!') {
        elem_da_stack x = pop(s);
        elem_da_stack vdd = (elem_da_stack) {.t = LONG, .valor_guardado.l = 1};
        elem_da_stack fal = (elem_da_stack) {.t = LONG, .valor_guardado.l = 0};
        if (verdadeiro(x)) push (s,fal);
        else push (s, vdd);
        return 1;
    }
    return 0;
}

/**
* Funções igual_dbl:
*
* Se os elementos x e y forem iguais, sejam eles do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/


int igual_dbl (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL)
        if (x.valor_guardado.d == y.valor_guardado.d) return 1;
    if (y.t == LONG)
        if (x.valor_guardado.d == y.valor_guardado.l) return 1;    
    if (y.t == CHAR)
        if (x.valor_guardado.d == y.valor_guardado.c) return 1;
    return 0;
}

/**
* Funções igual_long:
*
* Se os elementos x e y forem iguais, sejam eles do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

int igual_long (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL)
        if (x.valor_guardado.l == y.valor_guardado.d) return 1;
    if (y.t == LONG)
        if (x.valor_guardado.l == y.valor_guardado.l) return 1;    
    if (y.t == CHAR)
        if (x.valor_guardado.l == y.valor_guardado.c) return 1;
    return 0;
}

/**
* Funções igual_char:
*
* Se os elementos x e y forem iguais, sejam eles do tipo DBL, LONG ou CHAR, devolve como verdadeiro.
*/

int igual_char (elem_da_stack x, elem_da_stack y) {
    if (y.t == DBL)
        if (x.valor_guardado.c == y.valor_guardado.d) return 1;
    if (y.t == LONG)
        if (x.valor_guardado.c == y.valor_guardado.l) return 1;    
    if (y.t == CHAR)
        if (x.valor_guardado.c == y.valor_guardado.c) return 1;
    return 0;
}

/**
* Função igual_aux:
*
* Se x e y forem iguais, devolve o r com o valor 1.
*
*/

int igual_aux (elem_da_stack x,elem_da_stack y) {
    int r = 0;
    if (x.t == DBL) 
        if (igual_dbl (x,y)) r = 1;
    if (x.t == LONG)
        if (igual_long (x,y)) r = 1;
    if (x.t == CHAR)
        if (igual_char (x,y)) r = 1;
    if (x.t == STR)
        if (strcmp (x.valor_guardado.s , y.valor_guardado.s)==0) r = 1;
    return r;
}

/**
* Função igual:
*
* Se token[0] for '=', retiramos um elemento da stack para x e outro para y através da função pop.
*
* Se x for do tipo LONG e y for STR ou ARR, recorremos à função procuraindice para ir buscar um elemento ao array.
*
* Caso cotrário verifica se são iguais e, se tal acontecer devolve-se um valor verdadeiro. Se não for o caso, devolve-se um valor falso.
*/

int igual (stack *s, char * token) {
    if (token [0] == '=') {
        elem_da_stack x = pop (s);
        elem_da_stack y = pop (s);
        if ((y.t == STR || y.t == ARR) && x.t == LONG ) procuraindice (s,x,y);
        else {
        elem_da_stack vdd = (elem_da_stack) {.t = LONG, .valor_guardado.l = 1};
        elem_da_stack fal = (elem_da_stack) {.t = LONG, .valor_guardado.l = 0};
        if (igual_aux(x,y)) push (s,vdd);
        else push (s,fal); 
        }
        return 1;
    }
    return 0;
}