#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "stack_.h"

/**
 * Função con_long_char:
 * 
 * Dependendo do tipo do elemento da stack, no caso para elementos do tipo LONG e CHAR, realiza a função con (&) tendo como argumentos os dois elementos anteriores;
 * 
 * Devolve à stack através da função push o resultado da aplicação de con aos elementos referidos anteriormente 
*/

void con_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l & x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c & x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l & x.valor_guardado.c});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c & x.valor_guardado.c});
}

/** 
 *Função con:
 *
 *Retira com recurso à função pop as duas variáveis no topo da stack.
 *
 * Verifica o valor do resultado entre as duas variaveis retiradas da stack e as manda para a função con_long_char. Visto q esta operacao so esta defenida para longs e chars, nada é feito se o resultado
 se mostrar double.
*/
int con (stack *s, char *token) {
    if (token[0] == '&') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        TYPE valor = resultado(x.t, y.t);
        if (valor == LONG || valor == CHAR) con_long_char(s,  x, y); 
        return 1;
    }
    return 0;
}

/**
 * Função not_bitwise:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Devolve ao topo da stack através da função push o contrário dos bits dos elementos retirados substituindo todos os 0s por 1s e vice versa, realizando antes a verificacao de cada tipo.
*/
int not_bitwise (stack *s, elem_da_stack var [],char *token) {
    if (token[0] == '~') {
        elem_da_stack x = pop(s);
        if (x.t == BLC) executarbloco (s,var,x.valor_guardado.bloco);
        else if (x.t == ARR) coloca_stack (s,x);
        else {
        elem_da_stack r;
        if (x.t == LONG) push (s, r = (elem_da_stack) {.t = LONG, .valor_guardado.l = ~x.valor_guardado.l});
        if (x.t == CHAR) push (s, r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = ~x.valor_guardado.c});
        }
        return 1;
    }
    return 0;
}

/**
 * Função xor_long_char:
 * 
 * Dependendo do tipo do elemento da stack, no caso para elementos do tipo LONG e CHAR, realiza a função xor (^) tendo como argumentos os dois elementos anteriores;
 * 
 * Devolve à stack através da função push o resultado da aplicação de xor aos elementos referidos anteriormente 
*/ 

void xor_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l ^ x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c ^ x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l ^ x.valor_guardado.c});
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c ^ x.valor_guardado.c});
}
/**
 * Função xor_bitwise:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Devolve ao topo da stack através da função push a disjunção exclusiva entre os valores dos bits dos elementos retirados com recurso à funcao xor_long_char.
 * A função é apenas executada para Longs e Chars.
*/
int xor_bitwise (stack *s, char *token) {
    if (token[0] == '^') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        TYPE valor = resultado(x.t, y.t);
        if (valor == LONG || valor == CHAR) xor_long_char(s, x, y);
        return 1;
    }
    return 0;
}

/**
 * Função dis_long_char:
 * 
 * Dependendo do tipo do elemento da stack, no caso para elementos do tipo LONG e CHAR, realiza a função dis (|) tendo como argumentos os dois elementos anteriores;
 * 
 * Devolve à stack através da função push o resultado da aplicação de dis aos elementos referidos anteriormente 
*/ 

void dis_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l | x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c | x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l | x.valor_guardado.c}); 
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c | x.valor_guardado.c});    
}

/**
 * Função dis:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Devolve ao topo da stack através da função push a disjunção entre os valores dos bits dos elementos retirados, com recurso à funcao dis_long_char.
 * Apenas é executada para longs e chars.
*/
int dis(stack *s, char *token) {
    if (token[0] == '|') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        TYPE valor = resultado(x.t, y.t);
        if (valor == LONG || valor == CHAR) dis_long_char(s,  x, y); 
        return 1;   
    }
    return 0;
}

/**
 * Função mod_long_char:
 * 
 * Dependendo do tipo do elemento da stack, no caso para elementos do tipo LONG e CHAR, realiza a função mod (%) tendo como argumentos os dois elementos anteriores;
 * 
 * Devolve à stack através da função push o resultado da aplicação de mod aos elementos referidos anteriormente 
*/
void mod_long_char (stack *s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r;
    if (x.t == LONG && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l % x.valor_guardado.l});
    if (x.t == LONG && y.t == CHAR) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.c % x.valor_guardado.l});
    if (x.t == CHAR && y.t == LONG) push (s,r = (elem_da_stack) {.t = LONG, .valor_guardado.l = y.valor_guardado.l % x.valor_guardado.c});    
    if (x.t == CHAR && y.t == CHAR) push (s,r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.c % x.valor_guardado.c});
}

/**
 * Função mod:
 * 
 * Retira com recurso à função pop as duas variáveis no topo da stack
 * 
 * Devolve ao topo da stack através da função push o resto da divisão entre os dois valores retirados com recurso à funcao mod_long_char.
 * Só é realizada para Longs e Chars.
*/
int mod(stack *s,elem_da_stack var[] ,char *token) {
    if (token[0] == '%') {
        elem_da_stack x = pop(s);
        elem_da_stack y = pop(s);
        if ( (y.t == ARR || y.t == STR ) && x.t == BLC) aplica_bloco (s,x,y,var);
        else {
        TYPE valor = resultado(x.t, y.t);
        if (valor == LONG || valor == CHAR) mod_long_char(s, x,  y); 
        }
        return 1;
    }
    return 0;
}

/**
*Função duplica:
*
* Copia o último elemento da stack
*
* Devolve ao topo da stack através da função push o último valor duplicado
*/
int duplica (stack *s, char *token) {
    if (token[0] == '_') {
        elem_da_stack x = s->stack[s->sp-1];
        push (s,x);
        return 1;
    }
    return 0;
}

/**
 * Função pop_operacao:
 *
 *  Com recurso à função pop, retira um elemento da stack
*/
int pop_operacao (stack *s,char *token) {
    if (token [0] == ';') {
        pop(s);
        return 1;
    }
    return 0;
}
/**
*Função roda:
*
* Os elementos da stack passam para a posição anterior e o primeiro passa para o topo da stack.
*/
int roda (stack *s, char *token) {
    if (token[0] == '@') {
        elem_da_stack x = pop (s);
        elem_da_stack y = pop (s);
        elem_da_stack z = pop (s);
        push (s,y);
        push (s,x);
        push (s,z);
        return 1;
    }
    return 0;
}
/**
 * Função troca:
 * 
 * Retira através da função pop os dois últimos elementos da stack e devolve-os em ordem invertida
*/

int troca (stack *s, char *token) {
    if (token[0] == '\\') {
        elem_da_stack x = pop (s);
        elem_da_stack y = pop (s);
        push (s,x);
        push (s,y);
        return 1;
    }
    return 0;
}

/**
 * Função copiar:
 * 
 * Retira o último elemento da stack com recurso à função pop.
 *
 * Devolve à stack com recurso à função push o elemento da stack cuja posição é o valor do stack pointer menos o valor do elemento que foi retirado anteriormente (n).
 */
int copiar (stack *s,elem_da_stack var[] ,char *token) {
    if (token[0] == '$') {
        elem_da_stack n = pop (s);
        if (n.t == BLC) ordena(s, n, pop (s), var);
        else {
        elem_da_stack x = s->stack[s->sp - n.valor_guardado.l -1];
        push (s,x);
        }
        return 1;
    }
    return 0;
}

/**
* Função transformar_char:
*
* Retira um elemento da stack através da função pop
*
* Analisa o tipo do elemento e:
*
*           - se for um caracter, devolve o elemento à stack através da função push;
*
*           - se for do tipo LONG, converte em caracter e devolve o elemento à stack através da função push
*/
int transformar_char (stack *s, char *token) {
    if (token[0] == 'c') {
        elem_da_stack x = pop (s);
        elem_da_stack r;
        if (x.t == CHAR) {
            push(s,x);
        }    
        else if (x.t == LONG) { 
            char c = x.valor_guardado.l;
            push (s, r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = c } );
        }
        else if (x.t == DBL) {
            char c = x.valor_guardado.d;
            push (s, r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = c } );
        }
        return 1;
    }
    return 0;
}  

/**
 * @brief Função atibui_int:
 *
 *
 * Transforma o topo da stack num long. 
 * @param x Topo da stack.
 * @param l Pointer para guardar o valor.
 */

void atribui_int (elem_da_stack x, long *l) {
    if (x.t == CHAR) { 
        *l = x.valor_guardado.c;
    }
    if (x.t == STR) { 
        *l = atoi (x.valor_guardado.s);
    }
    if (x.t == DBL) { 
        *l = x.valor_guardado.d;
    }
}

/**
 * @brief Função transformar_int:
 *
 * Função principal que transforma o topo da stack num long.
 *
 * Se o elemento ja for um long apenas faz push do elemento, senao chama a funcao atribui_int para coverter o elemento e depois dar push. 
 * @param s Stack
 * @param token Token vindo do input.
 */

int transformar_int (stack *s, char *token) {
    if (token[0] == 'i') {
        elem_da_stack x = pop (s);
        elem_da_stack r;
        long l = 0;
        if (x.t == LONG) {
            push(s,x);
        }
        else {
        atribui_int(x, &l);
        push (s, r = (elem_da_stack) {.t = LONG, .valor_guardado.l = l } );
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Função atibui_double:
 *
 *
 * Transforma o topo da stack num double. 
 * @param x Topo da stack.
 * @param l Pointer para guardar o valor.
 */

void atribui_double (elem_da_stack x, double *l) {
    if (x.t == CHAR) {
        *l = x.valor_guardado.c;
    }
    if (x.t == LONG) {
        *l = x.valor_guardado.l;
    }
    if (x.t == STR) { 
        sscanf (x.valor_guardado.s,"%lf", l);
    }
}

/**
 * @brief Função transformar_double:
 *
 * Função principal que transforma o topo da stack num long.
 *
 * Se o elemento ja for um double apenas faz push do elemento, senao chama a funcao atribui_double para coverter o elemento e depois dar push. 
 * @param s Stack
 * @param token Token vindo do input.
 */

int transformar_double (stack *s, char *token) {
    if (token[0] == 'f') {
        double l = 0;
        elem_da_stack x = pop (s);
        elem_da_stack r;
        if (x.t == DBL) {
            push (s, x);
        }
        else {
        atribui_double(x, &l);
        push (s, r = (elem_da_stack) {.t = DBL, .valor_guardado.d = l } );
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Função transformar_string:
 *
 * Transforma o topo da stack numa string com recurso a sprintf, se o elemento ja for uma string, devolve o proprio.
 * 
 * @param s Stack
 * @param token Token vindo do input
 */

int transformar_string (stack *s, char *token) {
    if (token [0] == 's') {
        elem_da_stack x = pop(s);
        char aux [BUFSIZ];
        if (x.t == STR) {
            push (s,x);
        }
        if (x.t == LONG) {
            sprintf(aux, "%lu", x.valor_guardado.l);
            push (s,x= (elem_da_stack) {.t = STR, .valor_guardado.s = aux});
        }
        if (x.t == CHAR) {
            sprintf(aux, "%c", x.valor_guardado.c);
            push (s,x= (elem_da_stack) {.t = STR, .valor_guardado.s = aux});
        }
        if (x.t == DBL) {
            sprintf(aux, "%g", x.valor_guardado.d);
            push (s,x= (elem_da_stack) {.t = STR, .valor_guardado.s = aux});
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Função getstring:
 *
 * Lê uma linha do input e coloca numa string que posteriormente é colocada na stack.
 * 
 * @param s Stack
 * @param token Token vindo do input 
 */

int getstring (stack *s, char *token) {
    if (token[0] == 'l') {
        char linha[10001];
        elem_da_stack r;
        if (fgets(linha,10001,stdin)!= NULL) {
            if (linha[strlen (linha) -1 ] == '\n') linha[strlen (linha) -1 ] = '\0';
            push(s,r = (elem_da_stack) {.t = STR , .valor_guardado.s = strdup (linha)});
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Função push_double:
 *
 * Coloca um double na Stack, fazendo sscanf do token.
 * 
 * @param r Pointer para onde o valor é guardado
 * @param token Token que guarda o valor.
 */

void push_double (elem_da_stack *r, char *token) {
    double valor;
    sscanf (token,"%lg",&valor);
    *r = (elem_da_stack) {
        .t = DBL,
        .valor_guardado.d = valor
    };
}

/**
 * @brief Função push_double:
 *
 * Coloca um long na Stack, fazendo sscanf do token.
 * 
 * @param r Pointer para onde o valor é guardado
 * @param token Token que guarda o valor.
 */

void push_long (elem_da_stack *r, char *token) {
    long valor;
    sscanf (token,"%ld",&valor);
    *r = (elem_da_stack) {
        .t = LONG,
        .valor_guardado.l = valor
    };
}

/**
 * @brief Função pop_variavel:
 *
 * Copia o valor do topo da stack para a variavel, atualizando-a.
 * 
 * @param s Stack
 * @param v Array onde as variáveis sao guardadas. 
 * @param token Token vindo do input.
 */

int pop_variavel (stack *s, elem_da_stack v [], char *token) {
    if (token [0] == ':') {
        if (token [1] > 64 && token [1] < 91) {
        elem_da_stack x = s->stack[s->sp-1];
        if (x.t == ARR) {
            elem_da_stack r = {.t = ARR, .valor_guardado.arr = new_stack()};
            for (int i = 0; i < x.valor_guardado.arr->sp; i++) {
                push (r.valor_guardado.arr,x.valor_guardado.arr->stack[i]);
            }
            v [token [1] - 65] = r;
        }
        else if (x.t == BLC) {
            elem_da_stack r = (elem_da_stack) {.t = BLC, .valor_guardado.bloco = strdup (x.valor_guardado.bloco)};
            v [token [1] - 65] = r;
        }
        else v [token [1] - 65] = x;
        return 1;
        }
    }
    return 0;
}

/**
 * @brief Funçao push_variavel:
 *
 * Copia o valor da variavel para a stack.
 * 
 * @param s Stack
 * @param v Array onde as variáveis sao guardadas. 
 * @param token Token vindo do input.
 */

int push_variavel (stack *s, elem_da_stack v [],char *token) {
    if (token [0] > 64 && token [0] < 91) {
        int posicao = token [0] - 65;
        if (v[posicao].t == ARR) {
            elem_da_stack r = (elem_da_stack) {.t = ARR, .valor_guardado.arr = new_stack()};
            for (int i = 0; i < v[posicao].valor_guardado.arr->sp; i++) {
                push (r.valor_guardado.arr, v[posicao].valor_guardado.arr->stack[i]);
            }
            push (s,r);
        }
        else push (s,v[posicao]);
        return 1;
    }
    return 0;
}
/**
 * @brief Função pushvalor.
 *
 * Verifica primeiro se tem algum ponto no input para assim identificar doubles.
 *
 * Se tiver, irá chamar a função push_double, senão chama a função push_long.
 * @param s Stack
 * @param token Token
 */

int pushvalor (stack *s, char *token) {
    int  ponto = 0;
    elem_da_stack r;
    for (int i = 0; token[i] != '\0'; i++) {
        if (token [i] == '.') ponto = 1;
    }
    if (ponto) push_double(&r, token);
    else push_long(&r, token);
    push (s,r);
    return 1;
}

/**
 * @brief Função print_stack:
 * 
 * Faz print a todos os elementos da stack.
 * @param s Stack 
 */

void print_stack (stack *s) {
    for ( int i = 0; i < s->sp; i++) {
        if (s->stack[i].t == DBL)  printf ("%g",s -> stack [i] .valor_guardado.d);
        if (s->stack[i].t == CHAR)  printf ("%c",s -> stack [i].valor_guardado.c);
        if (s->stack[i].t == STR)  printf ("%s",s -> stack [i].valor_guardado.s);
        if (s->stack[i].t == BLC)  printf ("%s",s -> stack [i].valor_guardado.bloco);
        if (s->stack[i].t == LONG)  printf ("%ld",s -> stack [i].valor_guardado.l);
        if (s->stack[i].t == ARR)  print_stack(s->stack[i].valor_guardado.arr);
    }
}

/**
 * @brief Função imprimirtopo:
 *
 * Imprime o topo da stack e coloca um '\n' no final. 
 * @param s Stack
 * @param token Token
 */

int imprimirtopo (stack *s, char *token){
    if (token[0] == 'p') {
        elem_da_stack x = s->stack[s->sp -1];
        if (x.t== DBL)  printf ("%g",x.valor_guardado.d); 
        if (x.t == CHAR)  printf ("%c",x.valor_guardado.c);
        if (x.t == STR)  printf ("%s",x.valor_guardado.s);
        if (x.t == BLC)  printf ("%s", x.valor_guardado.bloco);
        if (x.t == LONG)  printf ("%ld",x.valor_guardado.l);
        if (x.t == ARR)  print_stack(x.valor_guardado.arr);
        printf("\n");
        return 1;
    }
    return 0;
}

/**
 * @brief Função op_bitwise:
 *
 * Função que trata das operações bitwise. 
 * @param s Stack
 * @param var Array que guarda as variaveis
 * @param token Token
 */

int op_bitwise (stack *s, elem_da_stack var [],char *token) {
    if (con (s,token) || not_bitwise(s,var,token) || xor_bitwise(s,token) || dis(s,token)) return 1;
    return 0;
}

/**
 * @brief Função handle_pushvalores:
 *
 * Função que trata das operações de push de valores e de separar as strings. 
 * @param s Stack
 * @param var Array que guarda as variaveis
 * @param token Token
 */

int handle_pushvalores (stack *s, elem_da_stack v[], char * token) {
    if ((token [0] == 'S' || token [0] == 'N') && token [1] == '/') separar_string_por (s,token);
    else if (push_variavel (s,v,token)|| pop_variavel(s, v, token)||pushvalor(s, token)) return 1;
    return 0;
}

/**
 * @brief Função handle_aritmetico:
 *
 * Função que trata das operações de aritmetica.
 * @param s Stack
 * @param var Array que guarda as variaveis
 * @param token Token
 */

int handle_aritmetico (stack *s,elem_da_stack v [] ,char *token) {
    if (add(s,token) || sub (s,token) || mult(s,v,token) || divs (s,token) || inc (s,token) || dec (s,token) || expp (s,token) || mod (s,v,token) || op_bitwise(s,v , token) || handle_pushvalores(s, v,token)) return 1;
    return 0;
}

/**
 * @brief Função handle_stack:
 *
 * Função que trata das operações de aritmetica.
 * @param s Stack
 * @param var Array que guarda as variaveis
 * @param token Token
 */

int handle_stack(stack *s,elem_da_stack var[] ,char *token) {
    if (duplica(s,token) || pop_operacao (s,token) || roda(s,token) || troca(s,token) || copiar(s,var,token) || transformar_char(s,token) || 
    transformar_int(s,token) || transformar_double(s,token) || getstring(s,token)) return 1;
    return 0;
}

/**
 * @brief Função handle_logica:
 *
 * Função que trata das operações de logica.
 * @param s Stack
 * @param token Token
 */

int handle_logica (stack *s, char *token) {
    if (op_logica (s, token) || maior_logico (s,token)||menor_logico(s, token) || if_then_else (s,token) || negacao (s,token) || igual (s,token)) return 1;
    return 0;
}

/**
 * @brief Função handle_array:
 *
 * Função que trata das operações referente a arrays.
 * @param s Stack
 * @param var Array que guarda as variaveis
 * @param token Token
 */

int handle_array (stack *s,elem_da_stack var [] ,char * token) {
    if (tamanho (s,var,token) || lertudo (s,token) || transformar_string(s,token) || executar_vdd (s,var, token) || imprimirtopo (s,token)) return 1;
    return 0;
}

/**
 * Função handle:
 * 
 * A função irá receber uma string ,esses elementos da string irão ser comparados com todos os simbolos apresentados se estes forem iguais a opersação será executada.
 * Caso a string não contenha nenhum dos simbolos apresentados irá ser representado como um int que vai ser transportado através da função sscanf para &val,
 depois é utilizada a função push que irá devolver à stack os valores de s e val;
 * 
*/
void handle (stack *s,elem_da_stack v [], char *token) 
{
    if (strchr ("+-*()%#&|^~/",token[0]) != NULL) handle_aritmetico (s,v,token);
    else if (strchr ("_;\\@$clif", token [0]) != NULL) handle_stack (s,v,token);
    else if (strchr ("=<>!e?",token[0]) != NULL) handle_logica (s,token);
    else if (strchr (",tswp",token[0]) != NULL) handle_array (s,v,token);
    else handle_pushvalores (s,v,token);
} 

/**
 * @brief Função trim_whitespace:
 *
 * Retira os espacos de uma string ate encontar um caracter diferente de um espaco.
 * 
 * @param str 
 * @return Retorna a string sem os espacos
 */

char* trim_whitespace(char* str){
  while(isspace(*str)){
    str++;
  }
  return str;
}

/**
 * @brief Função try_parse_string:
 *
 * Filtra a string do input, devolvendo o que está dentro das aspas para uma string. Depois faz push dessa string e avanca o input dos tokens para o proximo.
 * @param str Input
 */

char* try_parse_string (char** str){
    if(*str[0] == '\"'){
        char* string = strdup(*str);
        string++;
        char *aux = strstr(string,"\"");
        int pos = aux - string;
        string[pos] = '\0';
        return string;
    }
    return NULL;
}

/**
 * @brief Função try_parse_token:
 *
 * Separa o token do input fazendo return do mesmo. 
 * @param str Input
 */

char *try_parse_token (char **str) {
    char *stop = " ";
    char * token = strtok (*str, stop);
    return token;
}

/**
 * @brief Função try_parse_array:
 *
 * Filtra o array do input, devolvendo o que está dentro dos parenteses para uma string. Depois faz return dessa string.
 * @param str Input
 */

char *try_parse_array (char **str) {
    if (*str[0] == '[') {
        char *token = strdup (*str);
        int aberto = 0, fechado = 0, stop = 1;
        token += 2;
        for (int pos = 0; token [pos] != '\0' && stop;pos ++) {
            if (token[pos] == '[') aberto ++;
            else if (token[pos] == ']') {
                    if (aberto == fechado) {
                        token [pos] = '\0';
                        stop = 0;
                    }
                    else fechado ++;
            }
        }
        return token;
    }
    return NULL;
}

/**
 * @brief Função try_parse_array:
 *
 * Filtra o bloco do input, devolvendo o tudo de uma chaveta para a outra para uma string. Depois faz return dessa string.
 * @param str Input
 */

char* try_parse_bloco (char** str){
    if(*str[0] == '{'){
        char *token = strdup (*str);
        int aberto = 0, fechado = 0, stop = 1;
        for (int pos = 1; token [pos] != '\0' && stop;pos ++) {
            if (token[pos] == '{') aberto ++;
            else if (token[pos] == '}') {
                    if (aberto == fechado) {
                        token [pos+1] = '\0';
                        stop = 0;
                    }
                    else fechado ++;
            }
        }
        return token;
    }
    return NULL;
}

/**
 * @brief Função tokenizer:
 * 
 * Vai separando o input em varios tokens e mandando para as funções que tratam desses tokens.
 * @param s Stack
 * @param var Array que guarda as variaveis
 * @param str Input
 */

void tokenizer (stack *s, elem_da_stack var [], char *str) {
    while(*(str = trim_whitespace(str)) != '\0'){
        char* token;
        if ((token = try_parse_string(&str)) != NULL){
            elem_da_stack r = (elem_da_stack) {.t = STR, .valor_guardado.s = token};
            push(s,r);
            str += strlen (token) + 3;
        }
        else if ((token = try_parse_array(&str)) != NULL) {
            stack *arr = new_stack();
            str += strlen (token) + 4;
            elem_da_stack r = (elem_da_stack) {.t = ARR, .valor_guardado.arr = arr};
            push (s,r);
            tokenizer(arr, var, token);
        }
        else if ((token = try_parse_bloco(&str)) != NULL){
            elem_da_stack r = (elem_da_stack) {.t = BLC, .valor_guardado.bloco = token};
            push (s,r);
            str += strlen (token) + 1;
        }
        else if((token = try_parse_token(&str)) != NULL){
            handle (s,var,token);
            str += strlen (token) +1 ;
        } 
        else {
            fprintf(stderr, "algo correu mal com o input.\n");
            exit(1);
        }
    }
}
 

/**  
 * Função main:
 *
 * É a função principal que irá ler o input, dividindo-o em vários tokens, separando-os até encontrar um espaço,
 e manda os mesmos para a função handle. No final deste processo, é dado um printf a todos os elementos da stack.
*/
int main () {
    stack *s = new_stack();
    elem_da_stack var [26];
    inicia_variaveis (var);
    char linha [BUFSIZ];
    if (fgets (linha,BUFSIZ,stdin) != NULL) {
        linha[strlen (linha) -1 ] = '\0';
        tokenizer(s,var,linha);
    }
    print_stack (s);
    printf ("\n");
    free (s);
    return 0;
}