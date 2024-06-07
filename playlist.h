#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct Node {
    char artista[50];
    char musica[50];
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct Playlist {
    Node *head;
    Node *tail;
    Node *current;
} Playlist;

void cria_playlist(Playlist *playlist);
void abre_arquivo(Playlist *playlist, const char *lista_musicas);
void salva_playlist_no_arquivo(Playlist *playlist, const char *lista_musicas);
void exibe_playlist_por_cad(Playlist *playlist);
void exibe_playlist_por_musica(Playlist *playlist);
void insere_musica(Playlist *playlist, const char *artista, const char *musica);
void remove_musica(Playlist *playlist, const char *musica);
Node* busca_musica(Playlist *playlist, const char *musica);
void seleciona_musica(Playlist *playlist, const char *musica);
void proxima_musica(Playlist *playlist);
void musica_anterior(Playlist *playlist);

#endif 
