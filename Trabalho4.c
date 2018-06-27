/* Trabalho Interdisciplinar Icc X Ga 
   Disciplina: SCC0221 - Introdução à Ciência da Computação I - Professor Moacir Antonelli Ponti
   Disciplina: SMA0300 - Geometria Analítica - Professora Miriam Garcia Manoel
   Trabalho 4 - Escalonamento, retas e planos
   Nome: Guilherme Targon Marques Barcellos
   Num. USP: 10724181	
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct{
			
			int numerador;														//Como neste trabalho cada coeficiente das equacoes é expresao
			int denominador;													//por uma divisao, para guardar em um vetor seria necessario 2 
																				//posicoes do vetor para armazenar um coeficiente. Portanto utilizamos
} coeficiente;																	//struct. Logo embaixo usaremos uma matriz de struct, onde cada posicao 
																				//da matriz guarda 1 coeficiente, porem 2 números(numerador\denominador).




coeficiente** aloca_matriz_heap(int linhas, int colunas){						//Aqui a funcao para alocar a matriz struct na mem heap.
	
	coeficiente** p;
	
	p = (coeficiente**) malloc(linhas * sizeof(coeficiente*));
	
	for(int i =0; i<linhas; i++){
		p[i] = (coeficiente*) malloc(colunas * sizeof(coeficiente));
	}
	
	return p;
}

void funcaodesalocaheap(coeficiente** matrizstruct, int linhas){
	
	for(int i = 0; i<linhas; i++){												//Desalocando a memoria heap, lembrando de desalocar primeiro as
		free(matrizstruct[i]);													//colunas, pois caso desaloquemos as linhas antes, endereco das 
	}																			//colunas sera perdido e teremos "memory leak".
	
	free(matrizstruct);
	
}


void printamatrizescalonada(int numequacoes, coeficiente** matrizstruct){
	
	for(int i =0; i<numequacoes; i++){
		for(int j = 0; j<4; j++){																		//Aqui a funcao para simplificar e printar a matriz escalonada.Nos
			if(matrizstruct[i][j].numerador == 0 || matrizstruct[i][j].denominador == 1){				//casos onde o numerador é zero, denominador é ocultado e apenas o zero
				printf("%d\t", matrizstruct[i][j].numerador);											//é printado. Quando o denominador é igual, apenas o numerador é printado;
			}																							//Se o numerador/denominador tem resto zero, printa a simplificacao.Nos outros
			else if(matrizstruct[i][j].numerador % matrizstruct[i][j].denominador ==0){					//onde n é possivel simplificar, printa-se numerador e denominador.
				printf("%d\t", matrizstruct[i][j].numerador/ matrizstruct[i][j].denominador);
			}
			else{
				printf("%d/%d\t", matrizstruct[i][j].numerador, matrizstruct[i][j].denominador);
			}
		}
		printf("\n");
	}
	
}

void funcaopreenche(int *cont, coeficiente** matrizstruct){
	
	
	
	for(int i = 0; i<4;i++){
		
		scanf("%d %d", &matrizstruct[*cont][i].numerador, &matrizstruct[*cont][i].denominador);
		
	}
	
	*cont = *cont + 1;
	
}

void funcao_swap (int linha, int linhaauxiliar, coeficiente** matrizstruct){
	
			coeficiente aux;
			
			for(int i =0; i<4; i++){												//Aqui onde é feito a troca de uma linha inteira da matriz
																					
				aux = matrizstruct[linhaauxiliar][i];								
				matrizstruct[linhaauxiliar][i] = matrizstruct[linha][i];
				matrizstruct[linha][i] = aux;
				
			}		
			
}


int MMC(int a, int b){
	
	int mmc;															//Funcao para calcular o MMC(Minimo multiplo comum)entre 2 numeros.
																		//Será necessario para realizar o escalonamento.
	
	if(a>b && a % b == 0){	
		mmc = a;
	}
	else if(b>a && b % a == 0){
		mmc = b;
	}
	else if(a == b){
		mmc = a;
	}
	else if(a == 1){
		mmc = b;
	}
	else if(b==1){
		mmc = a;
	}
	else{
		mmc = a*b;
	}
	
	
	return mmc;
}


void funcaoescalona(int linhaauxiliar, int colunaauxiliar, int*contador, coeficiente** matrizstruct, int numequacoes){
	
	if(linhaauxiliar == numequacoes -1){							//Aqui verifica a parada da funcao
		return;
	}
	
	
	if(matrizstruct[linhaauxiliar][colunaauxiliar].numerador == 0){
		
		for(int i = linhaauxiliar+1; i<4; i++){							//Checando se sera necessario realizar o swap, e se preciso chama
																		//a funcao swap.
			if(matrizstruct[i][colunaauxiliar].numerador != 0){
				
				funcao_swap(i, linhaauxiliar, matrizstruct);
				break;
			}
		}
	}
	
	coeficiente vetorlinha[4];
	for(int i =0; i<4; i++){															//A partir desta parte sera calculado os valores que serao
		vetorlinha[i].numerador = matrizstruct[linhaauxiliar][i].numerador;				//colocados na matriz escalonada.
		vetorlinha[i].denominador = matrizstruct[linhaauxiliar][i].denominador;
	}
	
	coeficiente pivo;
	
	pivo.numerador = matrizstruct[linhaauxiliar][colunaauxiliar].numerador;
	pivo.denominador = matrizstruct[linhaauxiliar][colunaauxiliar].denominador;
	
	int mmc, auxiliar1, auxiliar2;
	
	for(int i = linhaauxiliar; i<numequacoes; i++){
		
		auxiliar1 = matrizstruct[i][colunaauxiliar].numerador * pivo.denominador;
		auxiliar2 = matrizstruct[i][colunaauxiliar].denominador * pivo.numerador;
		
		for(int j =colunaauxiliar; j<4; j++){
			
			matrizstruct[linhaauxiliar][j].numerador = auxiliar1 * matrizstruct[linhaauxiliar][j].numerador;
			matrizstruct[linhaauxiliar][j].denominador = auxiliar2 * matrizstruct[linhaauxiliar][j].denominador;
			mmc = MMC(matrizstruct[linhaauxiliar][j].denominador, matrizstruct[i][j].denominador);
			matrizstruct[linhaauxiliar][j].numerador = (mmc/matrizstruct[linhaauxiliar][j].denominador)*matrizstruct[linhaauxiliar][j].numerador;
			matrizstruct[i][j].numerador = (mmc/matrizstruct[i][j].denominador) * matrizstruct[i][j].numerador;
			matrizstruct[i][j].denominador = mmc;
			matrizstruct[linhaauxiliar][j].denominador = mmc;
			matrizstruct[i][j].numerador = matrizstruct[i][j].numerador - matrizstruct[linhaauxiliar][j].numerador;
			
			matrizstruct[linhaauxiliar][j].numerador = vetorlinha[j].numerador;
			matrizstruct[linhaauxiliar][j].denominador = vetorlinha[j].denominador;
		}
	}
	
	for(int i =0; i<numequacoes; i++){
		if(matrizstruct[i][0].numerador == 0 && matrizstruct[i][1].numerador == 0 && matrizstruct[i][2].numerador == 0 && matrizstruct[i][3].numerador != 0){
			*contador = *contador + 1;
		}
	}
	
	
	
	funcaoescalona(linhaauxiliar+1, colunaauxiliar+1, contador, matrizstruct, numequacoes);			//Aqui entra a recursividade da funcao, ao chegar ao final
}																									//chama a mesma funcao denovo, apenas adicionando +1 na linhaauxiliar
																									//e tb na colunaauxiliar até q seja atingido o caso de parada da funcao
																									//(comeco desta funcao é testado caso parada).



int main(){
	
	
	int numequacoes = 0;
	int numcoeficientes = 0;
	char objeto1, objeto2;
	int contador1 = 0;
	
	scanf("%d %d", &numequacoes, &numcoeficientes);
	scanf(" %c", &objeto1); 
	
	coeficiente** matrizstruct;
	matrizstruct = aloca_matriz_heap(numequacoes, numcoeficientes);
	
	switch(objeto1){
		
		case 'r':	funcaopreenche(&contador1, matrizstruct);					//Uso do switch pois se for reta, sera necessario chamar
					funcaopreenche(&contador1, matrizstruct);					//a funcao preenche 2 vezes, enquanto se for plano só chama
		break;																	//uma vez.
		
		case 'p':	funcaopreenche(&contador1, matrizstruct);
		break;
		
	}
	
	scanf(" %c", &objeto2);
	
	switch(objeto2){
		
		case 'r':	funcaopreenche(&contador1, matrizstruct);
					funcaopreenche(&contador1, matrizstruct);
		break;
		
		case 'p':	funcaopreenche(&contador1, matrizstruct);
		break;
		
	}
	
	
	int linhaauxiliar = 0;        
	int colunaauxiliar = 0;
	int contador = 0;              
	
	funcaoescalona(linhaauxiliar, colunaauxiliar, &contador, matrizstruct, numequacoes);
	
	if(contador == 0){
		printf("sim\n");			//Este contador serve para determinar se houve intersecao ou nao. Cada vez que houver um absurdo(dentro da funcao escalona),
	}								//será adicionado "+1" no contador. Portanto contador != 0 significa q nao ha colisao.
	else{
		printf("nao\n");
	}
	
	printamatrizescalonada(numequacoes, matrizstruct);
	
	funcaodesalocaheap(matrizstruct, numequacoes);

}
