/*  Disciplina: SCC0221 - Introdução à Ciência da Computação I - Professor Moacir Antonelli Ponti
	Trabalho 3 - Balanceamento de Recrusos
	Nome: Guilherme Targon Marques Barcellos
	Num. USP: 10724181	
*/


#include <stdlib.h>                              //Precisamos incluir a biblioteca "stdlib.h" dessa vez pois vamos alocar na        
#include <stdio.h>								 //na memoria HEAP, e para fazer isso vamos utilizar "calloc", uma funcao
												 //disponivel nesta biblioteca.


void flood_fill1(int matrizmapa[9][9], int pos1x, int pos1y, int matrizmapaauxiliar[9][9], int* contador1 ){				   //Esta funcao e a funcao de baixo sao o "flood fill". A primeira e para o jogador 1 e a outra para o 2.
																															   //Como parametros, precisamos passar a matriz que corresponde ao mapa do jogo, posicao do jogador(coord x, y),
																															   //o endereco de um contador, que serve para contar "os passos dados" pelo flood fiil, alem de uma matriz auxiliar,						
																																//que vai ser usada para marcar a quantidade de passos dados para chegar em uma determinada posicao(posicao na matriz recebe valor contador).
																																//Dessa forma, independente de onde o(s) recurso(s) estiver(em), o flood fill nao vai parar msm que ache  um recurso, o flood fiil
																																//vai percorrer toda a matriz mapa e vai marcar todas as posicoes transponiveis com o respectivo numero de passos dados ate chegar naquele ponto.
																																//Posteriormente, com as coordenadas do recurso, vms acessar a matriz auxiliar para ver qnts passos foram necessarios para chegar naquele ponto. 

	if(matrizmapa[pos1x][pos1y] == 0 && pos1x <9 && pos1y<9 && pos1x>= 0 && pos1y>=0 && matrizmapaauxiliar[pos1x][pos1y] ==0){															
		*contador1 = *contador1 + 1;
		matrizmapaauxiliar[pos1x][pos1y] = *contador1;
		flood_fill1(matrizmapa, pos1x +1, pos1y, matrizmapaauxiliar, contador1); //Sul
		flood_fill1(matrizmapa, pos1x -1, pos1y, matrizmapaauxiliar, contador1); //Norte
		flood_fill1(matrizmapa, pos1x , pos1y -1, matrizmapaauxiliar, contador1); //Oeste
		flood_fill1(matrizmapa, pos1x , pos1y +1, matrizmapaauxiliar, contador1); //Leste

	}


}

void flood_fill2(int matrizmapa[9][9], int pos2x, int pos2y, int matrizmapaauxiliar2[9][9], int* contador2 ){


	if(matrizmapa[pos2x][pos2y] == 0 && pos2x <9 && pos2y<9 && pos2x>= 0 && pos2y>=0 && matrizmapaauxiliar2[pos2x][pos2y] == 0){   //Esta funcao tem o mesmo funcionamento da de cima, unica diferenca que e chamada a partir das coord do 
																																	//segundo jogador.
		*contador2 = *contador2 + 1;
		matrizmapaauxiliar2[pos2x][pos2y] = *contador2;
		flood_fill2(matrizmapa, pos2x +1, pos2y, matrizmapaauxiliar2, contador2); //Sul
		flood_fill2(matrizmapa, pos2x -1, pos2y, matrizmapaauxiliar2, contador2); //Norte
		flood_fill2(matrizmapa, pos2x , pos2y -1, matrizmapaauxiliar2, contador2); //Oeste
		flood_fill2(matrizmapa, pos2x , pos2y +1, matrizmapaauxiliar2, contador2); //Leste

	}


}




int main (){		

	int matrizmapa[9][9];
	int matrizmapaauxiliar[9][9];
	int matrizmapaauxiliar2[9][9];
	int contador1 = 0;
	int contador2 = 0;

	for(int i = 0; i<9; i++){							//Zerando a matriz mapaauxiliar
		for(int j = 0; j<9; j++){
			matrizmapaauxiliar[i][j] = 0;
		}
	}

	for(int i = 0; i<9; i++){
		for(int j = 0; j<9; j++){					   //Zerando a matrizmapaauxiliar2
			matrizmapaauxiliar2[i][j] = 0;
		}
	}


	for (int i = 0; i<9; i++){					 	     //Preenchendo a matriz "mapa", onde 1 representa um espaco intransponivel e 0
		for(int j = 0; j<9; j++){				        //um espaco transponivel.
			scanf("%d", &matrizmapa[i][j]);
		}
	}



	int pos1x, pos1y, pos2x, pos2y;						//Armazenando as posicoes x e y de cada jogador em 4 variaveis.

	scanf("%d", &pos1x);	
	scanf("%d", &pos1y);
	scanf("%d", &pos2x);
	scanf("%d", &pos2y);

			


	int nrecursos;
	scanf("%d",&nrecursos);

	int** matrizrecursos = (int**)calloc(sizeof(int*),nrecursos);          //Alocando uma matriz na memoria HEAP, com numero de linhas iguais 
	for (int i = 0; i<nrecursos ; i++){									   // a nrecursos e colunas = 2(Coord x,y).
		matrizrecursos[i] = (int*)calloc(sizeof(int), 2);
	}


	for(int i = 0; i<nrecursos; i++){										//Preenchendo a matrizrecursos(alocada na HEAP) com as coordenadas dos
		for (int j = 0; j<2; j++){											//recursos.
			scanf("%d", &matrizrecursos[i][j]);
		}
	}


	double valorexploracao1 = 0;
	double valorexploracao2 = 0;
	int numzeros = 0;

	flood_fill1(matrizmapa, pos1x, pos1y, matrizmapaauxiliar, &contador1);    //"Chamando" a funcao flood_fill1 e passando os parametros


	for (int i = 0; i<9; i++){
		for (int j = 0; j<9; j++){
			if (matrizmapa[i][j] == 0){                                       //Nesta parte do codigo, esta sendo contabilizado a quantidade de
				numzeros ++;												  //zeros da "matrizmapa", isso pq sera necessarios para o calculo final
			}																  //(valor exploracao)
		}
	}

	int auxiliar1 = 0;
	int auxiliar2 = 0;
	double auxiliar3 = 0;

	for (int i = 0; i<nrecursos; i++){															//Aqui e feito um dos calculos finais. Eh feito o somatorio do
		auxiliar1 = matrizrecursos[i][0];														// flood fiil(dividido num zeros matriz), ou seja, acessa a matriz mapa auxiliar na posicao onde
																								//o(s) recurso(s) se encontra(m), tirando de la o "valor do flood fill",
																								//, num de "passos" dados pelo flood fill p chegar naquela posicao a partir
																								//das coordenadas do jogador.Tudo isso fica armazenado na variavel "auxiliar 3",que
		auxiliar2 = matrizrecursos[i][1];														//logo em seguida e multiplicado por 1/numerorecuros, obtendo entao o valor exploracao.
		auxiliar3 = auxiliar3 + matrizmapaauxiliar[auxiliar1][auxiliar2]/(double)numzeros;
	}


	valorexploracao1 = auxiliar3 * (1/(double)nrecursos);
	

	auxiliar1 = 0;																				//Passo muito importante, pois as variaveis ja contem valores que foram usados nas linhas
	auxiliar2 = 0;																				//anteriores, entao precisamos zera-las.
	auxiliar3 = 0;																				

	flood_fill2(matrizmapa, pos2x, pos2y, matrizmapaauxiliar2, &contador2);									//"Chamando" a funcao flood_fill2 e passndo parametros.

	for (int i = 0; i<nrecursos; i++){
		auxiliar1 = matrizrecursos[i][0];														//Ocorre mesmo processo de novo.
		auxiliar2 = matrizrecursos[i][1];
		auxiliar3 = auxiliar3 + matrizmapaauxiliar2[auxiliar1][auxiliar2]/(double)numzeros;
	}


	valorexploracao2 = auxiliar3 * (1/(double)nrecursos);

	printf("%lf\n%lf\n", valorexploracao1, valorexploracao2);

	if(valorexploracao1 == valorexploracao2){							 //Esta e a parte final onde ja temos o valor de exploracao de cada jogador,
		printf("O mapa eh balanceado\n");								 //onde e decidido se o mapa eh balanceado e caso nao seja e decidido qual dos
	}																	 //dos jogadores tem vantagem.
	else if(valorexploracao1<valorexploracao2){
		printf("O jogador 1 possui vantagem\n");
	}
	else{
		printf("O jogador 2 possui vantagem\n");
	}





	for (int i = 0; i<nrecursos; i++){										//Aqui estamos desalocando a memoria heap, para nao "perder" memoria.
		free(matrizrecursos[i]);											//Dessa vez precisamos primeiro desalocar as colunas e somente depois as
	}																		//as linhas, pois se desalocarmos as linhas primeiro, vamos perder o endereco
																			//das colunas, perdendo parte da memoria alocada.                               
	free(matrizrecursos);														



  										
  
  return 0;
}
