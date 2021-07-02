#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "hangman.h"



//variáveis globais
char secretWord[WORD_SIZE];
char guesses[26];
int numberOfGuesses = 0;



void opening() {
  printf("*************************\n");
  printf("*     Jogo de Forca     *\n");
  printf("*************************\n\n");
}

void guessing() {
  char guess;    
  scanf(" %c", &guess);
  guesses[numberOfGuesses] = guess;
  numberOfGuesses++;
}

int doneGuessing(char letter) {
  int achou = 0;
  for (int j = 0; j < numberOfGuesses; j++) {
    if(guesses[j] == letter) {
      achou = 1;
      break;
    }
  }  
  return achou;
}

void drawHangman(){
  
  int errors = wrongGuesses();

  printf("  _______      \n");
  printf(" |/      |     \n");
  printf(" |      %c%c%c \n", (errors >= 1 ? '(' : ' '),(errors >= 1 ? '_' : ' '),(errors >= 1 ? ')' : ' '));
  printf(" |      %c%c%c \n", (errors >= 3 ? '\\' : ' '), (errors >= 2 ? '|' : ' '), (errors >= 3 ? '/' : ' '));
  printf(" |       %c    \n", (errors >= 2 ? '|' : ' '));
  printf(" |      %c %c  \n", (errors >= 4 ? '/' : ' '),(errors>=4?'\\':' '));
  printf(" |             \n");
  printf("_|___          \n");
  printf("\n\n");



    // imprime a palavra secreta
  for(int i = 0; i < strlen(secretWord); i++){ 
    int achou = doneGuessing(secretWord[i]);
    if(achou) {
      printf("%c ", secretWord[i]);
    } else {
      printf("_ ");
    }
  }
  printf("\n");
}

void addWord(){
  char wants;
  printf("Você deseja adicionar uma nova palavra no jogo? (S/N)\n");
  scanf(" %c", &wants);

  if (wants == 'S'){

    //cogita nova palavra e a captura
    char newWord[WORD_SIZE];
    printf("Qual a nova palavra?\n");
    scanf("%s", newWord);

    //abre file
    FILE* f;

    f = fopen("palavras.txt", "r+");
    if(f == 0){
      printf("Desculpe, banco de dados não disponível\n");
      exit(1);
    }

    //identifica e aumenta a qtd total de palavras
    int amountOfWords;
    fscanf(f, "%d", &amountOfWords);
    amountOfWords++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", amountOfWords);

    //adiciona a nova palavra ao final
    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", newWord);

    fclose(f);

  }
}


void chooseWord(){
  FILE* f;

  f = fopen("palavras.txt", "r");
  if(f == 0) {
    printf("Desculpe, banco de dados não disponível\n\n");
    exit(1);
  }


  int numberOfWords;
  fscanf(f, "%d", &numberOfWords);

  srand(time(0));
  int random = rand() % numberOfWords;

  for(int i = 0; i <= random; i++){
    fscanf(f, "%s", secretWord);
  }

  fclose(f);
}

int won(){
  for(int i = 0; i < strlen(secretWord); i++){
    if(!doneGuessing(secretWord[i])){
      return 0;
    }
  }
  return 1;
}

int wrongGuesses(){
  int errors = 0;
  for(int i = 0; i < numberOfGuesses; i++){
    int exists = 0;
    exists = doneGuessing(secretWord[i]);
    if(!exists) {
      errors++;
    }
  
  }
  return errors;

}


int hang(){
  // retorna 1 se o número de erros for maior que 5, e 0 se não for
  return wrongGuesses() >= 5;
}


int main() {

  

  chooseWord();
  opening();

  do {
    drawHangman();
    guessing(guesses);
  } while(!won() && !hang());
  
  
  if(won()){
    printf("Parabéns! Você ganhou!\n");
  } else {

	
  printf("    .... NO! ...                  ... MNO! ...\n");
  printf("  ..... MNO!! ...................... MNNOO! ...\n");
  printf("..... MMNO! ......................... MNNOO!! .\n");
  printf("..... MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!! .\n");
  printf("... !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO! ....\n");
  printf("    ...... ! MMMMMMMMMMMMMPPPPOOOOIII! ! ...\n");
  printf("  ........ MMMMMMMMMMMMPPPPPOOOOOOII!! .....\n");
  printf("  ........ MMMMMOOOOOOPPPPPPPPOOOOMII! ...\n");
  printf("    ....... MMMMM..    OPPMMP    .,OMI! ....\n");
  printf("    ...... MMMM::   o.,OPMP,.o   ::I!! ...\n");
  printf("        .... NNM:::.,,OOPM!P,.::::!! ....\n");
  printf("          .. MMNNNNNOOOOPMO!!IIPPO!!O! .....\n");
  printf("        ... MMMMMNNNNOO:!!:!!IPPPPOO! ....\n");
  printf("          .. MMMMMNNOOMMNNIIIPPPOO!! ......\n");
  printf("          ...... MMMONNMMNNNIIIOO!..........\n");
  printf("      ....... MN MOMMMNNNIIIIIO! OO ..........\n");
  printf("    ......... MNO! IiiiiiiiiiiiI OOOO ...........\n");
  printf("  ...... NNN.MNO! . O!!!!!!!!!O . OONO NO! ........\n");
  printf("  .... MNNNNNO! ...OOOOOOOOOOO .  MMNNON!........\n");
  printf("  ...... MNNNNO! .. PPPPPPPPP .. MMNON!........\n");
  printf("      ...... OO! ................. ON! .......\n");
  printf("        ................................\n");




    printf("\nVocê perdeu! Mas tente novamente!\n");
  }
  
  
  addWord();


}

