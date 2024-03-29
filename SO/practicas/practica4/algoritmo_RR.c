#include <stdio.h>
#include <string.h>

#define NPROC 5

typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;

} parametros;

void main(){
    int i=0,j=0,k;
    int cont=0,comienzo=0;
    int t_ejecORIGINALES[NPROC];
    parametros procesos[NPROC];

    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
		t_ejecORIGINALES[0] = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_fin = procesos[0].t_ejec;
    procesos[0].t_ret = procesos[0].t_fin;
    procesos[0].t_esp = 0;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
		t_ejecORIGINALES[1] = 4;
    procesos[1].t_lleg = 1;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
		t_ejecORIGINALES[2] = 9;
    procesos[2].t_lleg = 2;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
		t_ejecORIGINALES[3] = 5;
    procesos[3].t_lleg = 3;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
		t_ejecORIGINALES[4] = 2;
    procesos[4].t_lleg = 4;

    while(j!=3){
      printf("\nProceso | t_comienzo | t_fin\n");
	     for(i=0;i<NPROC;i++){//primera iteración
	        if(procesos[i].t_ejec>0){
            procesos[i].t_com=comienzo;//
            if(procesos[i].t_ejec<3){
              procesos[i].t_fin=procesos[i].t_com+procesos[i].t_ejec;
		          procesos[i].t_ejec=0;
              comienzo=procesos[i].t_fin;
            }
            else{
              procesos[i].t_fin=procesos[i].t_com+3;
              procesos[i].t_ejec-=3;
              comienzo=procesos[i].t_fin;
            }
          }
          printf("-------------------------------\n");
          printf("   %s \t\t %d \t %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin);
        }
        j++;
      }
      printf("\n\n");
      printf("\nProceso | t_retorno | t_espera\n");
      printf("-------------------------------\n");
      for(i=0;i<NPROC;i++){
        procesos[i].t_ret=procesos[i].t_fin-i;
        procesos[i].t_esp=procesos[i].t_ret-t_ejecORIGINALES[i];
        printf("   %s \t\t %d \t %d \n", procesos[i].nombre,procesos[i].t_ret, procesos[i].t_esp);
      }
    }
