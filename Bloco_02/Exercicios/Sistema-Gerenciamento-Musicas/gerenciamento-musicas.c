#include <stdio.h>
#include <stdlib.h>

#define ADICIONAR_MUSICA 1
#define EXIBIR_PLAYLIST  2
#define PROXIMA          3
#define VOLTAR           4
#define FINALIZAR        5

#define N_MAX_MUSICAS 15

typedef struct musica
{
    char *nome;
    char *artista;
    int   duracao;
} musica_t;

typedef struct playlist
{
    char     *nome;
    musica_t *musicas[N_MAX_MUSICAS];
    int       n_musicas;
    int       now_playing;    
} playlist_t;

char     *ler_string();
musica_t *ler_musica();
void      adicionar_musica(playlist_t *);
void      exibir_playlist(playlist_t *);

void limpar_musica(musica_t *);
void limpar_playlist(playlist_t *);

int main()
{
    //CRIAR PLAYLIST (vazia)
    playlist_t *playlist = (playlist_t *)malloc(sizeof(playlist_t));
    playlist->nome = ler_string();
    playlist->n_musicas = 0;

    //LER E EXECUTAR COMANDOS
    int comando;
    do
    {
        scanf("%d ", &comando);

        if (comando == ADICIONAR_MUSICA)
            adicionar_musica(playlist);
        else if (comando == EXIBIR_PLAYLIST)
            exibir_playlist(playlist);
        else if (comando == PROXIMA && playlist->now_playing < playlist->n_musicas - 1)
            playlist->now_playing++;
        else if (comando == VOLTAR && playlist->now_playing > 0)
            playlist->now_playing--;
    } while (comando != FINALIZAR);

    //LIMPAR MEMÓRIA
    limpar_playlist(playlist);

    return 0;
}

// Lê e armazena uma string da entrada padrão.
char *ler_string()
{
    char *string = (char *)malloc(sizeof(char));
    int string_size = 0;

    do
    {
        string[string_size] = fgetc(stdin);
        string_size++;

        if (string[string_size - 1] != '\n')
            string = (char *)realloc(string, string_size + 1);

    } while (string[string_size - 1] != '\n');

    string[string_size - 1] = '\0';

    return string;
}

// Lê e armazena uma música da entrada padrão (struct).
musica_t *ler_musica()
{
    musica_t *musica_temp = (musica_t *)malloc(sizeof(musica_t));

    musica_temp->nome = ler_string();
    musica_temp->artista = ler_string();
    scanf("%d ", &musica_temp->duracao);
  
    return musica_temp;
}

// Se couber, adiciona música.
void adicionar_musica(playlist_t *playlist)
{
    if (playlist->n_musicas < N_MAX_MUSICAS)
    {
        musica_t *musica = ler_musica();
        playlist->musicas[playlist->n_musicas] = musica;
        playlist->n_musicas++;

        printf("Musica %s de %s adicionada com sucesso.\n", musica->nome, musica->artista);

        if (playlist->n_musicas == 1)
            playlist->now_playing = 0;
    }
    else
        printf("Playlist cheia!\n");
}

// Imprime informações sobre a playlist.
void exibir_playlist(playlist_t *playlist)
{
    printf("---- Playlist: %s ----\n", playlist->nome);
    printf("Total de musicas: %d\n\n", playlist->n_musicas);

    for (int i = 0; i < playlist->n_musicas; i++)
    {
        if (i == playlist->now_playing)
            printf("=== NOW PLAYING ===\n");

        printf("(%d). '%s'\n", i + 1, playlist->musicas[i]->nome);
        printf("Artista: %s\n", playlist->musicas[i]->artista);
        printf("Duracao: %d segundos\n\n", playlist->musicas[i]->duracao);
    }
}

// Limpa a memória utilizada para armazenar uma música.
void limpar_musica(musica_t *musica_ptr)
{
    free(musica_ptr->nome);
    free(musica_ptr->artista);
    free(musica_ptr);
}

// Limpa a memória utilizada para armazenar a playlist.
void limpar_playlist(playlist_t *playlist)
{
    free(playlist->nome);
    for (int i = 0; i < playlist->n_musicas; i++)
        limpar_musica(playlist->musicas[i]);
    free(playlist);
}