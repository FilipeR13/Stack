#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack_.h"

/**
* Função concatena_array:
*
* Se x ou y forem do tipo ARR concatena os elementos x e y e faz push;
*/

void concatena_array (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == ARR && x.t != ARR) {
        push(y.valor_guardado.arr, x);
        push (s,y);
    }
    else if (y.t == ARR && x.t == ARR) {
        for (int i = 0; i < x.valor_guardado.arr->sp; i++) {
            push (y.valor_guardado.arr,x.valor_guardado.arr->stack [i]);
        }
        push(s,y);
    }
    else {
        push (x.valor_guardado.arr,x.valor_guardado.arr->stack[x.valor_guardado.arr->sp-1]);
        for (long i = x.valor_guardado.arr->sp-2; i>=0; i--) {
            x.valor_guardado.arr->stack[i+1] = x.valor_guardado.arr->stack[i]; 
        }
        x.valor_guardado.arr->stack[0] = y;
        push (s,x);
    }
}

/**
* Função concatena:
*
* Se x ou y forem do tipo STR concatena os elementos x e y e faz push;
* 
* Se x ou y forem do tipo ARR invoca a função concatena_array;
*/

void concatena (stack *s,elem_da_stack x, elem_da_stack y) {
    if (x.t == ARR || y.t == ARR ) concatena_array(s,x,y);
    else {
        if (y.t == STR) {
            char *aux = malloc ( sizeof (char) * strlen(y.valor_guardado.s));
            char new[strlen(y.valor_guardado.s)];
            strcpy (new,y.valor_guardado.s);
            if (x.t == STR) {
                strcat (new, x.valor_guardado.s);
            }
            else if (x.t == LONG)  {
                sprintf (aux,"%ld", x.valor_guardado.l);
                strcat (new, aux);
                }
            else if (x.t == DBL)  {
                sprintf (aux,"%g", x.valor_guardado.d);
                strcat (new, aux);
                }
            else if (x.t == CHAR)  {
                strcat (new, &x.valor_guardado.c);
                }
            elem_da_stack r = (elem_da_stack) {.t = STR, .valor_guardado.s = strdup (new)};
            push (s,r);
            free (aux);
            }
        else if (x.t == STR){
            char *new = strdup (x.valor_guardado.s);
            char *aux = malloc (strlen(x.valor_guardado.s) * sizeof (char));
            if (y.t == LONG)  {
                sprintf (aux,"%ld", y.valor_guardado.l);
                strcat (aux,new);
                }
            else if (y.t == DBL)  {
                sprintf (aux,"%g", y.valor_guardado.d);
                strcat (aux,new);
                }
            else if (y.t == CHAR)  {
                sprintf (aux, "%c", y.valor_guardado.c);
                strcat (aux,new);
                }
            elem_da_stack r = (elem_da_stack) {.t = STR, .valor_guardado.s = aux};
            push (s,r);
        }
    }
}

/**
* Função replicar:
*
* Se y for do tipo STR adiciona à string x-1 vezes a string original e faz push;
* 
* Se y for do tipo ARR adiciona ao array x-1 vezes os elementos do array original e faz push;
*/

void replicar (stack *s,elem_da_stack x, elem_da_stack y)  {
    if (y.t == STR) {
        char aux [BUFSIZ];
        strcpy (aux,y.valor_guardado.s);
        for (int i = 1; i < x.valor_guardado.l; i++) {
            strcat (aux,y.valor_guardado.s);
        }
        y.valor_guardado.s = aux;
        push (s,y);
    }
    if (y.t == ARR) {
        elem_da_stack r = ( elem_da_stack) {.t = ARR, .valor_guardado.arr = new_stack()};
        long tamanho = y.valor_guardado.arr->sp ;
        for (int i = 0; i < x.valor_guardado.l; i++) {
            for (int j = 0; j < tamanho; j++) {
                push (r.valor_guardado.arr, y.valor_guardado.arr->stack [j]);
            }
        }
        push (s,r);
    }
}

/**
* Função tamanho:
*
* Se y for do tipo ARR ou STR devolve o tamanho de y;
* 
* Se y for do tipo LONG devolve um array com os númerosde 0 ao valor de y;
* 
* Se y for do tipo BLC faz a função filtro;
*/

int tamanho (stack *s,elem_da_stack var [] ,char * token) {
    if (token [0] == ',') {
        elem_da_stack x = pop (s);
        if (x.t == BLC) {
            elem_da_stack y = pop (s);
            filtra (s,x,y,var);
        }
        if (x.t == LONG) {
            stack *arr = new_stack();
            for (int i = 0; i < x.valor_guardado.l; i++) {
                elem_da_stack r = (elem_da_stack) {.t = LONG, .valor_guardado.l = i};
                push (arr, r);
            } 
            elem_da_stack r = {.t = ARR, .valor_guardado.arr = arr};
            push (s,r);
        }
        if (x.t == STR) {
            push (s,x = (elem_da_stack) {.t = LONG, .valor_guardado.l = strlen (x.valor_guardado.s)});
        }
        if (x.t == ARR) {
            elem_da_stack r = {.t = LONG, .valor_guardado.l = x.valor_guardado.arr -> sp};
            push (s,r);
        }
        return 1;
    }
    return 0;
}

/**
* Função procuraindice:
*
* Se o tipo de y for STR ele devolve o caratér no índice x e faz push;
* 
* Se o tipo de y for ARR ele devolve o elemento no índice x e faz push;
*/

void procuraindice (stack *s, elem_da_stack x,elem_da_stack y) {
    if (y.t == STR) {
        push (s, x = (elem_da_stack) {.t = CHAR, .valor_guardado.c = y.valor_guardado.s [x.valor_guardado.l]});
    }
    if (y.t == ARR) {
        push (s, y.valor_guardado.arr->stack [x.valor_guardado.l]);
    }
}

/**
* Função pegaeleminit:
* 
* Se o tipo de y for STR devolve a string com os primeiros x caratéres e faz push;
* 
* Se o tipo de y for ARR devolve o array com os primeiros x elementos e faz push;
*/

void pegaeleminit (stack *s, elem_da_stack x, elem_da_stack y) {
    if (y.t == STR) {
        if (x.t == LONG) {
            y.valor_guardado.s [x.valor_guardado.l] = '\0';
            push (s,y);
        }
    }
    if (y.t == ARR) {
        if (x.t == LONG) {
            y.valor_guardado.arr->sp = x.valor_guardado.l;
            push (s,y);
        }
    } 
}

/**
* Função pegaelemend:
*
* Se o tipo de y for STR devolve a string formada pelos últimos n caratéres;
* 
* Se o tipo de y for ARR devolve um array com os últimos x elementos do array original;
*/

void pegaelemend (stack *s, elem_da_stack x,elem_da_stack y) {
    if (y.t == STR) {
        if (x.t == LONG) {
            y.valor_guardado.s += strlen(y.valor_guardado.s) - x.valor_guardado.l;
            push (s,y);
        }
    }
    if (y.t == ARR) {
        if (x.t == LONG) {
            elem_da_stack r = (elem_da_stack) {.t = ARR, .valor_guardado.arr = new_stack()};
            for (int i = y.valor_guardado.arr->sp - x.valor_guardado.l; i < y.valor_guardado.arr->sp; i++) {
                push (r.valor_guardado.arr, y.valor_guardado.arr->stack[i]);
            }
            push (s,r);
            free (y.valor_guardado.arr);
        }
    }
}

/**
* Função retiraeleminitaux:
*
* Esta função retira o primeiro elemento de um array, no caso uma string;
*/

void retiraeleminitaux (char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = s[i+1];
    }
}

/**
* Função retiraeleminitaux_array:
*
* Esta função retira o primeiro elemento de um array;
* 
* Aplica a função pop ao array sem o primeiro elemento;
*/

void retiraeleminitaux_array (stack *arr) {
    for (int i = 0; i < arr->sp ; i++) {
        arr->stack[i] = arr->stack[i+1];
    }
    pop (arr);
}

/**
* Função retiraeleminit:
*
* Se o elemento x da stack for do tipo STR (string) aplica a funçao retiraeleminitaux a x e faz push;
* 
* Se o elemento x da stack for do tipo ARR (array) aplica a funçao retiraeleminitaux_array a x e faz push;
*/

void retiraeleminit (stack *s,elem_da_stack x) {
    if (x.t == STR) {
        elem_da_stack r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = x.valor_guardado.s[0]};
        retiraeleminitaux (x.valor_guardado.s);
        push(s,x);
        push(s,r);
    }
    if (x.t == ARR) {
        elem_da_stack r = x.valor_guardado.arr->stack[0];
        retiraeleminitaux_array(x.valor_guardado.arr);
        push (s,x);
        push (s,r);
    }
}

/**
* Função retiraelemend:
*
* Se o elemento x da stack for do tipo STR (string) retira o caratér na posição dada e faz push a x;
* 
* Se o elemento x da stack for do tipo ARR (array) retira o elemento na posição dada e faz push a x; 
*/

void retiraelemend (stack *s,elem_da_stack x) {
    if (x.t == STR) {
        elem_da_stack r = (elem_da_stack) {.t = CHAR, .valor_guardado.c = x.valor_guardado.s[strlen(x.valor_guardado.s)-1]};
        x.valor_guardado.s [strlen(x.valor_guardado.s) - 1] = '\0';
        push(s,x);
        push(s,r);
    }
    if (x.t == ARR) {
        elem_da_stack r = pop (x.valor_guardado.arr);
        push (s,x);
        push (s,r);
    }
}

/**
 * Função findsubstring:
 * 
 * Procura a substring dentro da string e devolve a posição;
 */

void findsubstring (stack *s, elem_da_stack x, elem_da_stack y) {
    if (x.t == CHAR) {
        char* point = strchr (y.valor_guardado.s,x.valor_guardado.c);
        long pos;
        if (point != NULL) 
            pos = point - y.valor_guardado.s;
        else
            pos = -1;
        push (s, x= (elem_da_stack) {.t = LONG, .valor_guardado.l = pos});
    }
    if (x.t == STR) {
        char* point = strstr (y.valor_guardado.s,x.valor_guardado.s);
        long pos ;
        if (point != NULL) 
            pos = point - y.valor_guardado.s;
        else
            pos = -1;
        push (s, x= (elem_da_stack) {.t = LONG, .valor_guardado.l = pos});
    }
}

/**
 * Função lertudo:
 * 
 * Lê o input, coloca-o na mesma string e faz o seu push;
 */

int lertudo (stack *s, char *token) {
    if (token [0] == 't') {
        char str [BUFSIZ] = {0};
        char aux[10081] = {0};
        while (fgets (str, BUFSIZ, stdin) != NULL) {
            strcat (aux, str);
        }
        elem_da_stack r = (elem_da_stack) {.t = STR, .valor_guardado.s = aux};
        push (s,r);
        return 1;
    }
    return 0;
}

/**
 * Função coloca_stack:
 * 
 * Coloca todos os elementos do array na stack com recurso à função push;
 */

void coloca_stack (stack *s, elem_da_stack x) {
    for (int i = 0; i < x.valor_guardado.arr->sp; i++) {
        push (s,x.valor_guardado.arr->stack[i]);
    }
    free (x.valor_guardado.arr);
}

/**
 * Função separa_string:
 * 
 * Separa a primeira string em várias strings sempre que encontrar no seu interior a segunda string e coloca-as num array;
 */

void separa_string(stack* s, elem_da_stack x, elem_da_stack y) {
    elem_da_stack r = (elem_da_stack) {.t = ARR, .valor_guardado.arr= new_stack()};
    if (x.valor_guardado.s[0] == '\0') {
        push(s,y);
        return;
    }
    int pos = 0, stop = 1;
    long tamanho = strlen (y.valor_guardado.s);
    char *string = strdup (y.valor_guardado.s);
    while (pos <= tamanho && stop && string[0] != '\0') {
        char *aux = strdup (string); 
        char *substr = strstr (string, x.valor_guardado.s);
        if (substr == NULL) {
            stop = 0;
            elem_da_stack p = (elem_da_stack) {.t = STR, .valor_guardado.s = aux};
            push (r.valor_guardado.arr, p);
            }
        else {
        long posicao = substr - string;
        aux [posicao] = '\0';
        elem_da_stack p = (elem_da_stack) {.t = STR, .valor_guardado.s = aux};
        push (r.valor_guardado.arr, p);
        pos += posicao + strlen(x.valor_guardado.s) ;
        string +=posicao + strlen(x.valor_guardado.s) ;
        }
    }
    push (s,r);
}

/**
 * Função separar_string_por:
 * 
 * Se o token for igual a S separa a string por espaços, coloca-a num array e faz push;
 * 
 * Se o token for igual a N separa a string por quebra de linha, coloca-a num array e faz push;
 */

int separar_string_por (stack *s, char* token) {
    elem_da_stack r = {.t = ARR, .valor_guardado.arr = new_stack()};
    elem_da_stack x = pop (s),auxiliar;
    char *str = strdup (x.valor_guardado.s);
    char *aux = {0};
    if (token[0] == 'S') {
        while ((aux = strtok_r (str, " \n",&str)) != NULL) {
            char *res = strdup (aux);
            push (r.valor_guardado.arr, auxiliar = (elem_da_stack) {.t = STR, .valor_guardado.s = res });
        }
        push (s,r);
    }
    if (token [0] == 'N') {
        while ((aux = strtok_r (str, "\n", &str)) != NULL) {
            char *res = strdup (aux);
            push (r.valor_guardado.arr, auxiliar = (elem_da_stack) {.t = STR, .valor_guardado.s = res });
        }
        push (s,r);
    }
    return 1;
}
