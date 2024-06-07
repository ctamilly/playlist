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
