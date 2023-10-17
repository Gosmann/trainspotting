/******************************************************************************/
/* APPLICATION : ecrivain udp                                                  */
/* Auteur : A. TOGUYENI                                                       */
/* Date : 15/09/2023                                                         */
/* Version : 1.0                                                             */
/* Compilation : gcc ecrivain_udp.c -o ecrivain_udp                           */
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

#define LOCALPORT   4000
#define REMOTEPORT   2000
#define LOCALIP     "127.0.0.1"
#define REMOTE     "127.0.0.1"


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
    adrlect.sin_port=htons(REMOTEPORT);
    adrlect.sin_addr.s_addr=inet_addr(LOCALIP);
    
    //Affectation d'une adresse a la socket
//    erreur=bind(sd,(const struct sockaddr *) &adrlect,sizeof(adrlect));
//    CHECK_ERROR(erreur,-1, "Erreur de bind !!! \n");
    
    printf("ECRIVAIN>");
    fgets(buff,MAXOCTETS,stdin);//lecture au clavier
    nbcar=sendto(sd, buff,strlen(buff),0,(const struct sockaddr *) &adrlect,sizeof(adrlect));
    CHECK_ERROR(nbcar,0,"\nProbleme d'emission !!! \n");
    printf("Appuyer sur une touche pour arreter le programme !!! \n");
    getchar(); //pause
    
    close(sd);
    
    exit(EXIT_SUCCESS);
}
    
    