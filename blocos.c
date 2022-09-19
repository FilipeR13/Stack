#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "stack_.h"

/**
 * @brief Função executar_bloco:
 *
 * Executa o conteúdo do bloco uma vez. 
 * @param s Stack
 * @param var Array que guarda as variávies
 * @param string String que guarda o bloco
 */

void executarbloco (stack *s, elem_da_stack var [],char *string) {
    char *str = strdup (string);
    int tamanho = strlen (str);
    str [tamanho-1] = '\0';
    str += 2;
    tokenizer (s,var,str);
}

/**
 * @brief Função aplica_bloco_arr:
 * 
 * Executa o bloco o mesmo número de vezes que o stack pointer do y. Vai fazendo push dos valores de y para o array de r e executa o bloco sobre este array.
 * @param r Array para colocar os resultados
 * @param y Array com os valores em que o bloco vai ser aplicado
 * @param str  String que guarda o bloco
 * @param var Array que guarda as variávies
*/

void aplica_bloco_arr (elem_da_stack r, elem_da_stack y, char *str, elem_da_stack var []) {
    for (int i = 0; i < y.valor_guardado.arr->sp; i++) {
            char *token = strdup (str); 
            push (r.valor_guardado.arr,y.valor_guardado.arr->stack[i]);
            executarbloco(r.valor_guardado.arr, var , token);     
            free(token);
        }
}

/**
 * @brief Função aplica_bloco:
 *
 * Aplica o bloco a todos os elemetos de um array ou de uma string, colocando os resultados num array novo ou string nova e faz push dos mesmos no fim.
 * @param s Stack
 * @param x elemento da stack que foi feito push
 * @param y elemento da stack que foi feito push
 * @param var Array que guarda as variávies
 */
void aplica_bloco (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var []) {
    char *str = x.valor_guardado.bloco;
    if (y.t == ARR) {
        elem_da_stack r = (elem_da_stack) {.t = ARR, .valor_guardado.arr = new_stack()};
        aplica_bloco_arr(r,  y, str,var);
        free (y.valor_guardado.arr);
        push (s,r);
    }
    if (y.t == STR) {
        stack *res = new_stack();
        int j=0;
        for (int i = 0; y.valor_guardado.s[i] != '\0'; i++) {
            char *token = strdup (x.valor_guardado.bloco);
            elem_da_stack new = {.t = CHAR, .valor_guardado.c = y.valor_guardado.s[i]};
            push (res,new);
            executarbloco(res,var,token);
            free (token);
        }
        for (int i = 0; i < res->sp; i++) {
            if (res->stack[i].t == CHAR) {
                y.valor_guardado.s[j] = res->stack[i].valor_guardado.c;
                j++;
            }
            if (res->stack[i].t == STR) {
                for(int z = 0; z < (int) (strlen (res->stack[i].valor_guardado.s)); z++) {
                    y.valor_guardado.s[j] = res->stack[i].valor_guardado.s[z];
                    j++;
                }
            }
            if (res->stack[i].t == LONG) {
                y.valor_guardado.s[j] = res->stack[i].valor_guardado.l;
                j++;
            }
        }
        y.valor_guardado.s[j] = '\0';
        free(res);
        push (s,y);
    }
}

/**
 * @brief Função fold:
 *
 * Primeiramente cria um novo array e coloca o primeiro elemento de y nele para servir de acumulador.
 * Vai executando o bloco ate ao fim do array de y no novo array r, fazendo push do mesmo no fim.
 * @param s Stack
 * @param x elemento que contém um bloco
 * @param y elemento que contém o array
 * @param var Array que guarda as variávies
 */

void fold (stack *s, elem_da_stack x, elem_da_stack y,elem_da_stack var[]) {
    elem_da_stack r = {.t = ARR, .valor_guardado.arr = new_stack()};
    push (r.valor_guardado.arr, y.valor_guardado.arr->stack [0]);
    for (int i = 1; i < y.valor_guardado.arr->sp; i++) {
        char *token = strdup (x.valor_guardado.bloco);
        push (r.valor_guardado.arr, y.valor_guardado.arr->stack[i]);
        executarbloco(r.valor_guardado.arr, var, token);
        free (token);
    }
    push (s,r);
}

/**
 * @brief Função verificatrue
 *
 * Verifica se o elemento recebido é verdadeiro, retornando 1 ou 0; 
 * @param x Elemento da stack
 */

int verificatrue (elem_da_stack x) {
    if (x.t == LONG && x.valor_guardado.l) return 1;
    if (x.t == STR && x.valor_guardado.s) return 1;
    if (x.t == CHAR && x.valor_guardado.c) return 1;
    if (x.t == DBL && x.valor_guardado.d) return 1;
    return 0;
}
/**
 * @brief Função deletar:
 * 
 * Retira um elmento de uma string.
 * @param s string para alterar
 * @param pos posição a eliminar
 */
void deletar (char *s, int pos) {
    for (int i = pos; s[i] != '\0'; i++) {
        s[i] = s[i+1];
    }
}

/**
 * @brief Função filtra.
 *
 * Cria um novo array auxiliar o qual ira guardar os resultados de executar o bloco a todos os elementos do array ou string.
 *
 * Após isso, através do valor do array é decidido se o elemento do array/string mantem-se ou é deletado. 
 * @param s Stack
 * @param x elemento que guarda o bloco
 * @param y elemento que guarda o elemento a ser filtrado
 * @param var Array que guarda as variáveis
 */

void filtra (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var []) {
    if (y.t == ARR) {
        elem_da_stack r = {.t = ARR, .valor_guardado.arr = new_stack()};
        int j = y.valor_guardado.arr->sp;
        for (int i = 0; i < j; i++) {
            elem_da_stack aux = {.t = ARR, .valor_guardado.arr = new_stack()};
            char *token = strdup (x.valor_guardado.bloco);
            push (aux.valor_guardado.arr, y.valor_guardado.arr->stack[i]);
            executarbloco(aux.valor_guardado.arr,var, token);
            if (verificatrue (aux.valor_guardado.arr->stack[0])) push(r.valor_guardado.arr,y.valor_guardado.arr->stack[i]);
            free(token);
            free(aux.valor_guardado.arr);
        }
        push (s,r);
    }
    if (y.t == STR) {
        for (int i = 0; y.valor_guardado.s[i] != '\0';) {
            elem_da_stack aux = {.t = ARR, .valor_guardado.arr = new_stack()};
            char *token = strdup (x.valor_guardado.bloco);
            elem_da_stack chr =(elem_da_stack) {.t = CHAR , .valor_guardado.c = y.valor_guardado.s[i]};
            push (aux.valor_guardado.arr, chr);
            executarbloco(aux.valor_guardado.arr,var, token);
            if (! verificatrue (aux.valor_guardado.arr->stack[0])) deletar (y.valor_guardado.s, i);
            else i++;
            free(token);
            free(aux.valor_guardado.arr);
        }
        push (s,y);
    }
}

/**
 * @brief Função swap
 * 
 * Faz swap dos elementos do array através das posições.
 * @param a array
 * @param i Posicao a ser trocada
 * @param j Posicao a ser trocada
 */

void swap(stack a[], int i, int j) {
    elem_da_stack aux = a->stack[i];
    a->stack[i] = a->stack[j];
    a->stack[j] = aux;
}

/**
 * @brief Função ssort:
 * 
 * Função para ordenar um array consoante um array de resultados.
 * @param a array de resultados
 * @param n número de elementos
 * @param y array original
 */
void ssort(stack a[], int n,stack y []) {
    int i, j, m;
    for (i = n; i > 0; i--) {
        m = 0;
        for (j = 0; j < i; j++)
            if (maior_log_aux(a->stack[m], a->stack[j])) m = j;
        swap(a, i-1, m);
        swap(y, i-1, m);
    }
}

/**
 * @brief Função ordena:
 * 
 * Executa o bloco a todos os elementos do array colocando os resultados num novo array. Depois ordena o array original consoante os valores dos resultados.
 * @param s stack
 * @param x elemento que guarda o bloco
 * @param y elemento que contém o array
 * @param var Array que guarda as variávies
 */

void ordena (stack *s, elem_da_stack x, elem_da_stack y, elem_da_stack var[]) {
    elem_da_stack valores = (elem_da_stack) {.t = ARR, .valor_guardado.arr = new_stack()};
    aplica_bloco_arr(valores, y,x.valor_guardado.bloco , var);
    ssort(valores.valor_guardado.arr, valores.valor_guardado.arr->sp, y.valor_guardado.arr);
    push (s,y);
    free (valores.valor_guardado.arr);
}

/**
 * @brief Função executar_vdd
 *
 * Executa o bloco enquanto o valor do topo da stack for true, fazendo pop desse valor no fim. 
 * @param s Stack
 * @param var Array que guarda as variávies
 * @param token Token
 */

int executar_vdd (stack *s, elem_da_stack var [],char *token) {
    if (token [0] == 'w') {
        elem_da_stack x = pop(s);
        if (x.t == BLC) {
            elem_da_stack y = s->stack[s-> sp-1];
            while (verificatrue(y)) {
                char *aux = strdup (x.valor_guardado.bloco);
                executarbloco(s, var, aux);
                y = pop(s);
            }
        }
        return 1;
    }
    return 0;
}