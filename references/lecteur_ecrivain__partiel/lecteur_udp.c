/******************************************************************************/
/* APPLICATION : lecteur udp                                                  */
/* Auteur : A. TOGUYENI                                                       */
/* Date : 15/09/2023                                                         */
/* Version : 1.0                                                             */
/* Compilation : gcc lecteur_udp.c -o lecteur_udp                           */
/* usage : ./lecteur_udp                                                     */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 #include <unistd.h>



#define CHECK_ERROR(val1,val2,msg)   if (val1==val2) \
                                    { perror(msg); \
                                        exit(EXIT_FAILURE); }

#define LOCALPORT   2000
#define LOCALIP     "127.0.0.1"

#define MAXOCTETS   150

int main() {
    int sd ; //socket de dialogue
    struct sockaddr_in adrlect; //adresse du lecteur
    int erreur; //gestion des erreurs
    int nbcar; //nb d'octets recu
    char buff[MAXOCTETS+1]; //buffer de reception d'octets
    
    
    sd=socket(AF_INET,SOCK_DGRAM,0); //Utilisation de lecteur_udp
    CHECK_ERROR(sd,-1, "Erreur socket non cree !!! \n");
    printf("N° de la socket : %d \n", sd);
    
    //preparation de l'adresse de la socket
    adrlect.sin_family=AF_INET;
    adrlect.sin_port=htons(LOCALPORT);
    adrlect.sin_addr.s_addr=inet_addr(LOCALIP);
    
    //Affectation d'une adresse a la socket
    erreur=bind(sd,(const struct sockaddr *) &adrlect,sizeof(adrlect));
    CHECK_ERROR(erreur,-1, "Erreur de bind !!! \n");
    
    printf("LECTEUR>");
    nbcar=recvfrom(sd, buff,MAXOCTETS+1,0,NULL,NULL);
    CHECK_ERROR(nbcar,0,"\nProbleme de reception !!! \n");
    printf("%s\n LECTEUR>",buff);
    getchar(); //pause
    
    close(sd);
    
    exit(EXIT_SUCCESS);
}
    
    