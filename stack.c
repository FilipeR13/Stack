#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack_.h"
#include <assert.h>

/** 
 * Função new_stack:
 *
 * Aloca o espaço para a stack.
 */
stack * new_stack () {
    stack *s = malloc (sizeof(stack));
    s->sp = 0;
    s->cp = 0;
    return s;
}

/**
 * Funcao inicia_variaveis:
 *
 * Esta função utiliza um ciclo for para preencher o array das variaveis com os valores predefenidos.
 */
void inicia_variaveis (elem_da_stack var []) {
    for (int i = 0; i < 26; i++) {
        if (i<6) var [i] = (elem_da_stack) {.t = LONG, .valor_guardado.l = 10 + i};
        if (i == 13)  var[i] = (elem_da_stack) {.t = CHAR, .valor_guardado.c = '\n'};
        if (i == 18)  var[i] = (elem_da_stack) {.t = CHAR, .valor_guardado.c = ' '};
        if (i>22) var [i] = (elem_da_stack) {.t = LONG, .valor_guardado.l =  i - 23};
    }
}
/**  
 * Função push:
 * 
 * Adiciona o elemento elem à stack aumentando ao mesmo tempo o stack pointer (sp).
*/
void push(stack *s,elem_da_stack elem){
    if(s-> sp == s-> cp){
        if(s->cp == 0) s->stack = (elem_da_stack*)realloc(NULL,(++s->cp) * sizeof(elem_da_stack));
        else{
            s->stack = (elem_da_stack*)realloc(s->stack,2 * s->cp * sizeof(elem_da_stack));
            s->cp *= 2;
        }
    }
    s->stack[s->sp++] = elem;   
}
/**
 *Função pop:
 *
 * Retira da o elemento do topo da stack, fazendo return do mesmo e diminuindo o stack pointer.
*/
elem_da_stack pop (stack *s) {
    assert(s->sp > 0);
    return s->stack[--s->sp];
}