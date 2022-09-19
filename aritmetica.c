#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack_.h"

/**
 *Função resultado.
 *
 *Determina o tipo do resultado em opecacoes matemáticas.
 */

TYPE resultado (TYPE x, TYPE y) {
    if (x==DBL || y == DBL) return DBL;
    if (x==LONG || y == LONG) return LONG;
    return CHAR;
}

/** 
 * Funcao somar_double:
 *
 * Realiza o push ao resultado da soma entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um double, ou seja, que pelo menos um dos elementos da função seja double.
*/
void somar_double (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == DBL && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = x.valor_guardado.d + y.valor_guardado.d });
    if (x.t == DBL && y.t == LONG) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = x.valor_guardado.d + y.valor_guardado.l });
    if (x.t == LONG && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = x.valor_guardado.l + y.valor_guardado.d });
    if (x.t == DBL && y.t == CHAR) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = x.valor_guardado.d + y.valor_guardado.c });
    if (x.t == CHAR && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = x.valor_guardado.c + y.valor_guardado.d });
}

/** 
 * Funcao somar_long_char:
 *
 * Realiza o push ao resultado da soma entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um long ou char, ou seja, que pelo menos um dos elementos da função seja long ou os dois elementos sejam char, respetivamente.
 */

void somar_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = x.valor_guardado.l + y.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = x.valor_guardado.l + y.valor_guardado.c});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = x.valor_guardado.c + y.valor_guardado.l});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = x.valor_guardado.c + y.valor_guardado.c});
}
/**
 * Função add:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Verifica o tipo do resultado da soma entre as duas variaveis e utiliza as funcoes somar_double e somar_long_char para calcular o resultado no caso de ser double ou entao long e char, respetivamente.
*/
int add (stack *s, char *token) {
    if (token[0] == '+') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        if (y.t == STR || y.t == ARR || x.t == ARR || x.t == STR) concatena (s,x,y);
        else {
            TYPE valor = resultado(x.t, y.t);
            if (valor == DBL) somar_double(s, x, y);
            else if (valor == LONG || valor == CHAR) somar_long_char(s,  x, y);
        }
        return 1;
    }
    return 0;
}

/** 
 * Funcao sub_double:
 *
 * Realiza o push ao resultado da subtracao entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um double, ou seja, que pelo menos um dos elementos da função seja double.
*/
void sub_double (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == DBL && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d - x.valor_guardado.d });
    if (x.t == DBL && y.t == LONG) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.l - x.valor_guardado.d });
    if (x.t == LONG && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d - x.valor_guardado.l });
    if (x.t == DBL && y.t == CHAR) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.c - x.valor_guardado.d });
    if (x.t == CHAR && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d - x.valor_guardado.c });
}

/** 
 * Funcao sub_long_char:
 *
 * Realiza o push ao resultado da subtração entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um long ou char, ou seja, que pelo menos um dos elementos da função seja long ou os dois elementos sejam char, respetivamente.
 */
void sub_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l - x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c - x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l - x.valor_guardado.c});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c - x.valor_guardado.c});
}
/**
 * Função sub:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Verifica o tipo do resultado da subtracao entre as duas variaveis e utiliza as funcoes sub_double e sub_long_char para calcular o resultado no caso de ser double ou entao long e char, respetivamente.
*/
int sub (stack *s, char *token) {
    if (token[0] == '-' && (token[1] == '\0' || token [1] == '\n')) {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        TYPE valor = resultado(x.t, y.t);
        if (valor == DBL) sub_double(s, x,y);
        else if (valor == LONG || valor == CHAR) sub_long_char(s,  x,  y);
        return 1;
    }
    return 0;
}

/** 
 * Funcao mult_double:
 *
 * Realiza o push ao resultado da multiplicao entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um double, ou seja, que pelo menos um dos elementos da função seja double.
*/
void mult_double (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == DBL && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d * x.valor_guardado.d });
    if (x.t == DBL && y.t == LONG) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.l * x.valor_guardado.d });
    if (x.t == LONG && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d * x.valor_guardado.l });
    if (x.t == DBL && y.t == CHAR) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.c * x.valor_guardado.d });
    if (x.t == CHAR && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d * x.valor_guardado.c });
}

/** 
 * Funcao mult_long_char:
 *
 * Realiza o push ao resultado da multiplicao entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um long ou char, ou seja, que pelo menos um dos elementos da função seja long ou os dois elementos sejam char, respetivamente.
 */
void mult_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l * x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c * x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l * x.valor_guardado.c});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c * x.valor_guardado.c});
}

/**
 * Função mult:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack;
 * 
 * Verifica o tipo do resultado da multiplicacao entre as duas variaveis e utiliza as funcoes mult_double e mult_long_char para calcular o resultado no caso de ser double ou entao long e char, respetivamente.
*/
int mult (stack *s, elem_da_stack var [],char *token) {
    if (token[0] == '*') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        if (x.t == BLC && y.t == ARR) fold(s,x,y,var);
        else if (y.t == STR || y.t == ARR) replicar (s,x,y);
        else {
        TYPE valor = resultado(x.t, y.t);
        if (valor == DBL) mult_double(s,  x,  y);
        else if (valor == LONG || valor == CHAR)  mult_long_char(s,  x, y);
        }
        return 1;
    }   
    return 0;
}

/** 
 * Funcao divs_double:
 *
 * Realiza o push ao resultado da divisao inteira entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um double, ou seja, que pelo menos um dos elementos da função seja double.
*/
void divs_double (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == DBL && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d / x.valor_guardado.d });
    if (x.t == DBL && y.t == LONG) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.l / x.valor_guardado.d });
    if (x.t == LONG && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d / x.valor_guardado.l });
    if (x.t == DBL && y.t == CHAR) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.c / x.valor_guardado.d });
    if (x.t == CHAR && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = y.valor_guardado.d / x.valor_guardado.c });
}

/** 
 * Funcao divs_long_char:
 *
 * Realiza o push ao resultado da divisao inteira entre as duas variaveis recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um long ou char, ou seja, que pelo menos um dos elementos da função seja long ou os dois elementos sejam char, respetivamente.
 */
void divs_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l / x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c / x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l / x.valor_guardado.c});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c / x.valor_guardado.c}); 
}
/**
 * Função divs:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack;
 * 
 * Verifica o tipo do resultado da divisao inteira entre as duas variaveis e utiliza as funcoes divs_double e divs_long_char para calcular o resultado no caso de ser double ou entao long e char, respetivamente.
*/
int divs(stack *s, char *token) {
    if (token[0] == '/') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        if (x.t == STR || y.t == STR) separa_string (s,x,y);
        else {
            TYPE valor = resultado(x.t, y.t);
            if (valor == DBL) divs_double(s,  x,  y);
            else if (valor == LONG || valor == CHAR) divs_long_char(s,  x, y);
        }
        return 1;
    }
    return 0;
}
/**
 * Função inc:
 * 
 * Retira com recurso à função pop a variável no topo da stack;
 * 
 * Devolve ao topo da stack, através da função push, o resultado da incrementação do valor 1 à variável anterior;
*/
int inc(stack *s, char *token) {
    if (token[0] == ')') {
        elem_da_stack x = pop (s);
        if (x.t == STR || x.t == ARR) retiraelemend (s,x);
        else {
        elem_da_stack r;
        if (x.t == DBL) {
            push(s,r= (elem_da_stack) {.t = DBL, .valor_guardado.d = ++x.valor_guardado.d });
        }
        if (x.t == LONG) {
            push(s,r= (elem_da_stack) {x.t, .valor_guardado.l = ++x.valor_guardado.l });
        }
        if (x.t == CHAR) {
            push(s,r= (elem_da_stack) {x.t, .valor_guardado.c = ++x.valor_guardado.c});
        }
        }
        return 1;
    }
    return 0;
}

/**
 * Função dec:
 * 
 * Retira com recurso à função pop a variável no topo da stack;
 * 
 * Devolve ao topo da stack, através da função push, o resultado da decrementação do valor 1 à variável anterior;
*/
int dec(stack *s, char *token) {
    if (token[0] == '(') {
        elem_da_stack x = pop (s); 
        if (x.t == STR || x.t == ARR) retiraeleminit (s,x);
        else {
        elem_da_stack r;
        if (x.t == DBL) {
            push(s,r= (elem_da_stack) {x.t, .valor_guardado.d = --x.valor_guardado.d });
        }
        if (x.t == LONG) {
            push(s,r= (elem_da_stack) {x.t, .valor_guardado.l = --x.valor_guardado.l });
        }
        if (x.t == CHAR) {
            push(s,r= (elem_da_stack) {x.t, .valor_guardado.c = --x.valor_guardado.c});

        }
        }
        return 1;
    }
    return 0;
}
/** 
 * Funcao expp_double:
 *
 * Realiza o push ao resultado de elevar o valor da variavel y à variável x recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um double, ou seja, que pelo menos um dos elementos da função seja double.
*/
void expp_double (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == DBL && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = pow (y.valor_guardado.d , x.valor_guardado.d) });
    if (x.t == DBL && y.t == LONG) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = pow (y.valor_guardado.l , x.valor_guardado.d) });
    if (x.t == LONG && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = pow ( y.valor_guardado.d , x.valor_guardado.l )});
    if (x.t == DBL && y.t == CHAR) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = pow (y.valor_guardado.c , x.valor_guardado.d) });
    if (x.t == CHAR && y.t == DBL) push (s,r = (elem_da_stack) {.t = DBL, .valor_guardado.d = pow (y.valor_guardado.d , x.valor_guardado.c) });
}
/** 
 * Funcao expp_long_char:
 *
 * Realiza o push ao resultado de elevar o valor da variavel y à variável x recebidas como argumeto. 
 * Esta função apenas realiza a operacao que dá resultado a um long ou char, ou seja, que pelo menos um dos elementos da função seja long ou os dois elementos sejam char, respetivamente.
*/
void expp_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = pow (y.valor_guardado.l , x.valor_guardado.l)});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = pow (y.valor_guardado.c , x.valor_guardado.l)});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = pow (y.valor_guardado.l , x.valor_guardado.c)});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = pow (y.valor_guardado.c , x.valor_guardado.c)});   
}
/**
 * Função expp:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Verifica o tipo do resultado da expoenciacao entre as duas variaveis e utiliza as funcoes expp_double e expp_long_char para calcular o resultado no caso de ser double ou entao long e char, respetivamente.
*/
int expp(stack *s, char *token) {
    if (token[0] == '#') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        if (y.t == STR) findsubstring (s,x,y);
        else {
        TYPE valor = resultado(x.t, y.t);
        if (valor == DBL) expp_double(s,  x,  y);
        else if (valor == LONG || valor == CHAR) expp_long_char(s,  x, y);
        }
        return 1;
    }
    return 0;
}
