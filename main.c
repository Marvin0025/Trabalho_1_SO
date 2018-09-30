/*Desenvolver um sistema de arquivos distribuídos que simula padrão EXT3. 
O sistema deve ser desenvolvido em C ou C++ utilizando o compilador GNU GCC e chamadas de sistemas do padrão POSIX. 
O sistema deve permitir que arquivos locais sejam acessados por usuários remotos simultaneamente. 
As operações permitidas pelo sistema devem incluir:
	
	criar (sub)diretório (mkdir)
	remover (sub)diretório (rm -r)
	entrar em (sub)diretório (cd)
	mostrar conteúdo do diretório (ls)
	criar arquivo (touch)
	remover arquivo (rm)
	escrever um sequência de caracteres em um arquivo (echo)
	mostrar conteúdo do arquivo (cat)

Etapa 1
Desenvolver a estrutura de acesso do servidor de arquivos. Ele deverá será acessado via socket TCP.
Cada conexão deverá ser gerida por uma thread. Condições de corrida deverão ser tratadas por meio de semáforos ou mutexes.
Nesta etapa você não precisa implementar as operações sobre arquivos listadas acima.
Ao invés disso, use as operações diretamente do sistema de arquivos do seu sistema operacional.
Recomenda-se que o servidor imprima mensagens na tela para demonstrar o funcionamento ao professor.

Observações:
Não é necessário autenticação dos usuários.
Não é necessário criar um aplicativo cliente. Você pode usar o aplicativo netcat disponível para Linux e Windows.
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>


pthread_mutex_t mutex; // precisa ser global!
/*
char* listDir(){
	char *retorno = calloc(2048,1);
	int offset = 0;

		DIR *d;
	    struct dirent *dir;
	    d = opendir(".");

    if (d){
        while ((dir = readdir(d)) != NULL)
            offset = offset + sprintf(retorno + offset, "%s ", dir->d_name);
        
        closedir(d);
    }

    return retorno;
}
				
void *func_thread(void *arg){

	pthread_mutex_lock(&mutex);
	//região crı́tica
	pthread_mutex_unlock(&mutex);
	return 0;
}*/

void *ls(void *threadid){
   	int *connfd = (int *)threadid;
   	char sendBuff[1025];

   	while (strcmp("exit\n", sendBuff) != 0){
	   	int recebido = recv(*connfd, sendBuff, 1025, 0);
		sendBuff[recebido] = '\0';
		printf ("Valor recebido foi: %s", sendBuff);
	   
	   	if ((strncmp("mkdir ", sendBuff, 6)) == 0){
			printf("\nESTOU NO MKDIR\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("rm -r ", sendBuff, 6)) == 0){
			printf("\nESTOU NO RM -R\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);		
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("cd ", sendBuff, 3)) == 0){
			printf("\nESTOU NO CD\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("ls", sendBuff, 2)) == 0){
			printf("\nESTOU NO LS\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("touch ", sendBuff, 6)) == 0){
			printf("\nESTOU NO TOUCH\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("rm ", sendBuff, 3)) == 0){
			printf("\nESTOU NO RM\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("echo ", sendBuff, 5)) == 0){			
			printf("\nESTOU NO ECHO\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}

		if ((strncmp("cat ", sendBuff, 4)) == 0){
			printf("\nESTOU NO CAT\n");
			pthread_mutex_lock(&mutex);
			system(sendBuff);
			pthread_mutex_unlock(&mutex);
		}
	}
}

int main(int argc, char **argv){
	int listenfd = 0;
	struct sockaddr_in serv_addr;
	char sendBuff[1025];

	listenfd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&serv_addr, '0', sizeof(serv_addr));
		
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5001);

	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);

	while(1){

		int *connfd = calloc(sizeof(int),1);
		pthread_t thread;

		*connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
			
		printf("Socket criado: %d\n", *connfd);
		pthread_create(&thread, NULL, ls, connfd);
			
		//pthread_mutex_init(&mutex, NULL);

		/*if(sendBuff == "ls")
		{
			printf("cheguei ate AQUI\n");
			pthread_create(&thread, NULL, ls, connfd);
		/*} else if (strcmp(sendBuff, mkdir)== 0){
		
			pthread_create(&thread, NULL, mkdir, connfd);	
		};
		*/
		

		//case cwd:
		//pthread_create(&thread, NULL, cwd, connfd);			
            
		//snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
 		//write(connfd, sendBuff, strlen(sendBuff));

			//bzero(sendBuff, sizeof(sendBuff));


		
	}

	//pthread_mutex_destroy(&mutex);
	return 0;
}
