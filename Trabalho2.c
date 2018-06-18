/*  Disciplina: SCC0221 - Introdução à Ciência da Computação I - Professor Moacir Antonelli Ponti
	Trabalho 2 - Sistema de Recomendacao
	Nome: Guilherme Targon Marques Barcellos
	Num. USP: 10724181	
*/

#include <stdio.h>
#include <math.h>

int main () {

	int npessoas, filmes;                                   //npessoas (4 <= n <= 15) filmes (1 <= i <= 15)
	double limiar;                          
	int primeira[15][15];                                   //Matriz que armazena nota de cada usuario para cada filme
	double medianotas[15];                                  //Vetor armazena media das notas
	
	scanf("%d %d %lf", &npessoas, &filmes, &limiar);        //armazena os valores nas respectiveis variaveis

	

	for(int i = 0; i<npessoas; i++){                        //Nesta parte, estou preenchendo a matriz de n linhas(usuarios) e f colunas(filmes)
		for (int j = 0; j<filmes; j++){
			primeira[i][j] = 0;	              
			scanf("%d", &primeira[i][j]);
		}
	}	


	double similaridades[15][15];
	int produtoescalar = 0;
	double norma1, norma2, raiz1, raiz2, mult;


	for(int i=0; i<npessoas; i++){                           //Calculando similaridades e armazenando na matriz similaridades
		for(int j=0; j<npessoas; j++){
			for(int k=0; k<filmes; k++){
			
				produtoescalar += primeira[i][k]*primeira[j][k];
				norma1 += pow(primeira[i][k], 2);
				norma2 += pow(primeira[j][k], 2);
				
			}
		raiz1 = sqrt(norma1);
		raiz2 = sqrt(norma2);
		mult = raiz1 * raiz2;	
		similaridades[i][j] = produtoescalar/mult; 
		produtoescalar = 0;
		norma1 = 0;
		norma2 = 0;
		raiz1 = 0;
		raiz2 = 0;
		mult = 0; 	 

		}
	}
		
	int auxiliar1, auxiliar2;                             //Tirando as medias e armazenando no vetor medianotas

	for (int i = 0; i<npessoas ; i++){
		auxiliar1 = 0;
		auxiliar2 = 0;
		for (int j = 0; j<filmes;j++){
			if (primeira[i][j] != 0){
				auxiliar1 += primeira[i][j];
				auxiliar2++;
			}
		}	
		
		medianotas[i] = (double)auxiliar1/auxiliar2;
		
	}	

	int auxiliar3;
	double maiorqlimiar, nota, notafinal, somatorio;
	
	for (int i = 0; i<npessoas; i++){                                                                  //Esta é a ultima parte do trabalho, onde temos que encontrar zeros na matriz
		for (int j =0; j<filmes; j++){																   //de notas (pois o intuito é prever a nota de um filme ainda não visto portanto
			if (primeira[i][j] == 0){																   //uma nota zero). Além disso, é preciso verificar se a similaridade entre os 
				auxiliar3 = 0; 																		   //usuarios é maior que o limiar digitado na entrada, pois a nota será feita
				maiorqlimiar = 0;                                                                      //comparando usuarios que tenham limiar maior, e se isso nao acontecer, ou seja, 
				somatorio = 0;                                                                         //nao houver uma similaridade maior que o limiar, não é possivel prever a nota(DI)
				
				for (int k = 0; k<npessoas; k++){
					if (similaridades[i][k] > limiar && similaridades[i][k] !=1){
						if (primeira[k][j] != 0){
							somatorio += (primeira[k][j] - medianotas[k]) * similaridades[i][k];
							maiorqlimiar += similaridades[i][k];
						}
					}
				}
				
				if (maiorqlimiar == 0){
					printf("DI ");
				}
				else{
					nota = somatorio/maiorqlimiar;
					notafinal = nota + medianotas[i];
					printf("%.2lf ", notafinal);
				}
			}	
		}
		if (auxiliar3 < 1){
			printf("\n");
			auxiliar3++;
		}
	}	


	
	return 0;
}
