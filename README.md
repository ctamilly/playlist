# Playlist de Músicas

Este projeto implementa uma playlist de músicas em C, oferecendo ao usuário várias funcionalidades para navegar e gerenciar as músicas da lista. 
A interação é feita por meio de um menu no qual o usuário pode exibir as musicas, incluir ou remover musicas do arquivo 'lista_musicas.txt' etc.

## Funcionalidades
- Exibir a playlist na ordem de cadastro.
- Exibir a playlist ordenada por nome da música.
- Inserir uma nova música na playlist.
- Remover uma música da playlist.
- Buscar uma música na playlist.
- Selecionar uma música para tocar.
- Avançar para a próxima música.
- Retornar para a música anterior.

## Estrutura de Dados Utilizada
A playlist é implementada como uma lista circular duplamente encadeada.

## Arquivos do Projeto
- `main.c`: Arquivo principal contendo a implementação do programa.
- `playlist.h`: Arquivo de cabeçalho contendo a definição das estruturas de dados e declarações das funções.
- `lista_musicas.txt`: Arquivo de texto contendo a lista de músicas. Cada linha do arquivo segue o formato artista;musica.

## Como Usar
### Requisitos
- Compilador C (gcc, clang, etc.)

### Compilação e Execução
1. Baixe o projeto:
- Clone o repositório ou baixe os arquivos diretamente.

2. Salve o arquivo de texto:
- Salve lista_musicas.txt no mesmo diretório do executável.

3. Compile o código

4. Interaja com o programa:
- Use as opções do menu para navegar entre as músicas da playlist.
