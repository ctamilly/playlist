#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playlist.h"

int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = tolower((unsigned char) *s1);
        char c2 = tolower((unsigned char) *s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char) *s1) - tolower((unsigned char) *s2);
}

void cria_playlist(Playlist *playlist) {
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
}

void abre_arquivo(Playlist *playlist, const char *lista_musicas) {
    FILE *arquivo = fopen(lista_musicas, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), arquivo)) {
        char artista[50];
        char musica[50];
        sscanf(line, "%[^;];%[^\n]", artista, musica);
        insere_musica(playlist, artista, musica);
    }

    fclose(arquivo);
}

void salva_playlist_no_arquivo(Playlist *playlist, const char *lista_musicas) {
    FILE *arquivo = fopen(lista_musicas, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita");
        exit(1);
    }

    Node *current = playlist->head;
    if (current != NULL) {
        do {
            fprintf(arquivo, "%s;%s\n", current->artista, current->musica);
            current = current->next;
        } while (current != playlist->head);
    }

    fclose(arquivo);
}

void exibe_playlist_por_cad(Playlist *playlist) {
    Node *current = playlist->head;
    printf(">> Playlist ordenada por cadastro:\n\n");
    if (current != NULL) {
        do {
            printf("Artista: %s, Musica: %s\n", current->artista, current->musica);
            current = current->next;
        } while (current != playlist->head);
    } else {
        printf("\n>> Playlist vazia!\n");
    }
}

void exibe_playlist_por_musica(Playlist *playlist) {
    int contador = 0;
    Node *current = playlist->head;
    printf(">> Playlist ordenada por musica:\n\n");
    if (current != NULL) {
        do {
            contador++;
            current = current->next;
        } while (current != playlist->head);
    }

    Node **lista = malloc(contador * sizeof(Node *));
    if(lista == NULL){
        printf("Erro ao alocar memoria");
        exit(1);
    }
    current = playlist->head;
    for (int i = 0; i < contador; i++) {
        lista[i] = current;
        current = current->next;
    }

    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (strcasecmp(lista[i]->musica, lista[j]->musica) > 0) {
                Node *temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    for (int i = 0; i < contador; i++) {
        printf("Artista: %s, Musica: %s\n", lista[i]->artista, lista[i]->musica);
    }

    free(lista);
}

void insere_musica(Playlist *playlist, const char *artista, const char *musica) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if(new_node == NULL){
        printf("Erro ao alocar memoria");
        exit(1);
    }
    strcpy(new_node->artista, artista);
    strcpy(new_node->musica, musica);

    if (playlist->head == NULL) {
        new_node->next = new_node;
        new_node->prev = new_node;
        playlist->head = new_node;
        playlist->tail = new_node;
        playlist->current = new_node;
    } else {
        new_node->next = playlist->head;
        new_node->prev = playlist->tail;
        playlist->tail->next = new_node;
        playlist->head->prev = new_node;
        playlist->tail = new_node;
    }

    salva_playlist_no_arquivo(playlist, "lista_musicas.txt"); 
}

void remove_musica(Playlist *playlist, const char *musica) {
    Node *current = playlist->head;
    if (current == NULL) {
        printf(">> Playlist vazia!\n");
        return;
    }

    do {
        if (strcasecmp(current->musica, musica) == 0) {
            if (current == playlist->head && current == playlist->tail) {
                playlist->head = NULL;
                playlist->tail = NULL;
                playlist->current = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == playlist->head) {
                    playlist->head = current->next;
                }
                if (current == playlist->tail) {
                    playlist->tail = current->prev;
                }
                if (current == playlist->current) {
                    playlist->current = current->next;
                }
            }
            free(current);
            salva_playlist_no_arquivo(playlist, "lista_musicas.txt"); // Salva a playlist atualizada no arquivo existente
            printf(">> Musica removida com sucesso!\n");
            return;
        }
        current = current->next;
    } while (current != playlist->head);

    printf(">> Musica nao encontrada!\n");
}

Node* busca_musica(Playlist *playlist, const char *musica) {
    Node *current = playlist->head;
    if (current != NULL) {
        do {
            if (strcasecmp(current->musica, musica) == 0) {
                return current;
            }
            current = current->next;
        } while (current != playlist->head);
    }
    return NULL;
}

void seleciona_musica(Playlist *playlist, const char *musica) {
    Node *encontrada = busca_musica(playlist, musica);
    if (encontrada != NULL) {
        playlist->current = encontrada;
        printf("\n>> Tocando agora: %s - %s\n", playlist->current->artista, playlist->current->musica);
    } else {
        printf(">> Musica nao encontrada!\n");
    }
}

void proxima_musica(Playlist *playlist) {
    if (playlist->current != NULL) {
        playlist->current = playlist->current->next;
        printf("\n>> Tocando agora: %s - %s\n", playlist->current->artista, playlist->current->musica);
    } else {
        printf(">> Playlist vazia!\n");
    }
}

void musica_anterior(Playlist *playlist) {
    if (playlist->current != NULL) {
        playlist->current = playlist->current->prev;
        printf("\n>> Tocando agora: %s - %s\n", playlist->current->artista, playlist->current->musica);
    } else {
        printf(">> Playlist vazia!\n");
    }
}
