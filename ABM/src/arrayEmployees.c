#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayEmployees.h"
#include "utn.h"

int menu(void)
{
    int opcion;

    system("cls");

    printf("***Bienvenido***\n\n");
    printf("---Menu de opciones--- \n\n");
    printf("1_ ALTA \n");
    printf("2_ MODIFICAR \n");
    printf("3_ BAJA \n");
    printf("4_ INFORMAR \n");
    printf("5_ SALIR \n");
    printf("0_ HARDCODEO \n\n\n");

    printf("Ingrese la opcion deseada: ");
    fflush(stdin);

    scanf("%d", &opcion);
    return opcion;


}

int initEmployees(eEmployee* listi, int len){
    int ret = -1;
    if(listi!=NULL && len > 0){
        for(int i=0; i < len; i++){
            listi[i].isEmpty = 1;
        }
        ret = 0;
    }
    return ret;
}

int freeSpace(eEmployee* listi, int len){
    int index = -1;
    for(int i=0; i< len; i++){
        if( listi[i].isEmpty == 1){
            index = i;
            break;
        }
    }
    return index;
}

void printSector(void){
    printf("\n******Sectores******\n");
    printf("  1_ Sistemas\n");
    printf("  2_ Ventas\n");
    printf("  3_ Mantenimiento\n");
    printf("  4_ Atencion\n");
    printf("  5_ RRHH\n");
}

int findEmployeeById(eEmployee* listi, int len, int id){
    int ret;
    for(int i=0; i < len; i++){
        if(listi[i].id == id && listi[i].isEmpty == 0){
            ret = i;
        }
    }
    return ret;
}

int printEmployee(eEmployee* listi, int index){
    printf("-ID: %d\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\n\n", listi[index].id, listi[index].name, listi[index].lastName, listi[index].salary, listi[index].sector);
    return 0;
}

int addEmployee(eEmployee* listi, int len, int id, char name[],char lastName[], float salary, int sector){
    eEmployee emplAdd;
    int index = freeSpace(listi, len);
    int ret = -1;
    if(index == -1){
        printf("ERROR: Sin espacio \n\n");
    } else {
        if (listi != NULL && len > 0){
            emplAdd.id = id;
            strcpy(emplAdd.name, name);
            strcpy(emplAdd.lastName, lastName);
            emplAdd.salary = salary;
            emplAdd.sector = sector;

            emplAdd.isEmpty = 0;
            listi[index] = emplAdd;
            ret = 0;
        }
    }
    return ret;
}

int editEmployeeById(eEmployee* listi, int len, int id){
    int index;
    int subMenu;
    eEmployee emplAux;
    int ret = -1;

    index = findEmployeeById(listi, len, id);
    char cont = 's';

    if(index != -1){
        if (listi != NULL && len > 0){
            do{
                printf("ID\tNombre\tApellido\tSalario\t\tSector\n");
                printEmployee(listi, index);
                printf("Que desea modificar?\n");
                printf("\t1_ Nombre\n");
                printf("\t2_ Apellido\n");
                printf("\t3_ Salario\n");
                printf("\t4_ Sector\n");
                printf("\t5_ Salir\n");
                scanf("%d", &subMenu);
                switch(subMenu){
                    case 1:
                        getValidString("Ingrese nombre: ", "Valor incorrecto.", emplAux.name);
                        strcpy(listi[index].name, emplAux.name);
                        printf("Campo modificado con exito\n\n");
                        break;
                    case 2:
                        getValidString("Ingrese apellido: ", "Valor incorrecto.", emplAux.lastName);
                        strcpy(listi[index].lastName, emplAux.lastName);
                        printf("Campo modificado con exito\n\n");
                        break;
                    case 3:
                        emplAux.salary =getValidFloat("Ingrese salario: ","Valor incorrecto", 10000, 1000000);
                        listi[index].salary=emplAux.salary;
                        printf("Campo modificado con exito\n\n");
                        break;
                    case 4:
                        printSector();
                        emplAux.sector =getValidInt("Ingrese sector: ","Valor incorrecto", 0, 5);
                        listi[index].sector= emplAux.sector;
                        printf("Campo modificado con exito.\n\n");
                        break;
                    case 5:
                        break;
                    default :
                        printf("Error, ingrese numero entre 1 y 5.\n");
                        break;
                }
                printf("Desea editar otro dato? Presione 's' para aceptar, presione cualquier otra tecla para salir.\n");
                fflush(stdin);
                scanf("%c", &cont);
            }while (cont == 's');
            printf("Volviendo al Menu...\n");
            ret = 0;
        }
    } else {
        printf("ERROR: La ID ingresada no pertenece a ningun empleado \n");
    }
    return ret;
}

int removeEmployee(eEmployee* listi, int len, int id){
    int index;
    char del;
    int ret = -1;

    index = findEmployeeById(listi, len, id);
    if(index != -1){
        if (listi != NULL && len > 0){
            printf("ID\tNombre\tApellido\tSalario\t\tSector\n");
            printEmployee(listi, index);
            printf("Confirmar eliminado? 's' para confirmar: ");
            fflush(stdin);
            scanf("%c", &del);
            if(del != 's'){
                printf("Cancelado\n\n");
            }else {
                listi[index].isEmpty = 1;
                printf("Empleado eliminado\n\n");
            }
            ret = 0;
        }
    }else {
        printf("ERROR: La ID ingresada no pertenece a ningun empleado \n");
    }
    return ret;
}

int printEmployees(eEmployee* listi, int len){
    for(int i=0; i< len; i++){
        if(listi[i].isEmpty == 0){
            printEmployee(listi, i);
        }
    }
    return 0;
}

int sortEmployees(eEmployee* listi, int len, int order){
    int ret = -1;
    eEmployee auxEmployees;
    if (listi != NULL && len > 0){
        if(order == 1){
            for(int i =0 ; i<len-1 ; i ++){
                for(int j= i+1 ; j<len; j++){
                    if(strcmp(listi[j].lastName,listi[i].lastName)<0 && listi[j].isEmpty==0 && listi[i].isEmpty==0){
                        auxEmployees = listi[i];
                        listi[i] = listi[j];
                        listi[j] = auxEmployees;
                    }else if(strcmp(listi[j].lastName,listi[i].lastName) ==0 && listi[j].sector<listi[i].sector && listi[j].isEmpty==0 && listi[i].isEmpty==0){
                        auxEmployees = listi[i];
                        listi[i] = listi[j];
                        listi[j] = auxEmployees;
                    }
                }
            }
            printf("\t1--Listado de empleados Apellido y Sector - Ascendente\n\n");
            printEmployees(listi, len);
        }else if(order == 2){
            for(int i =0 ; i<len-1 ; i ++){
                for(int j= i+1 ; j<len; j++){
                    if(strcmp(listi[j].lastName,listi[i].lastName)>0 && listi[j].sector<listi[i].sector && listi[j].isEmpty==0 && listi[i].isEmpty==0){
                        auxEmployees = listi[i];
                        listi[i] = listi[j];
                        listi[j] = auxEmployees;
                    }else if(strcmp(listi[j].lastName,listi[i].lastName) ==0 && listi[j].sector>listi[i].sector && listi[j].sector<listi[i].sector && listi[j].isEmpty==0 && listi[i].isEmpty==0){
                        auxEmployees = listi[i];
                        listi[i] = listi[j];
                        listi[j] = auxEmployees;
                    }
                }
            }
            printf("\t1--Listado de empleados Apellido y Sector - Descendente\n\n");
            printEmployees(listi, len);
        } else {
                printf("Opcion incorrecta\n");
        }
        ret = 0;
    }
    return ret;
}

int averageSalary(eEmployee* listi, int len){
    float empl=0;
    float salaryTotal=0;
    float average = -1;
    for (int i = 0; i<len; i++){
        if(listi[i].isEmpty==0){
            empl++;
            salaryTotal = salaryTotal + listi[i].salary;
        }
    }
    average = salaryTotal / empl;
    printf("\t2--Total y promedio de los salarios \n\n");
    printf("Total: %.2f\t", salaryTotal);
    printf("Promedio: %.2f\n", average);
    return average;
}
/*
int aboveAverageSalary(eEmployee* listi, int len){
    int average;
    int aboveA = 0;
    average = averageSalary(listi, len);
    for(int i = 0; i<len; i++){
        if(listi[i].salary > average){
            aboveA++;
        }
    }
    printf("\n\t2--Cuantxs empleadxs superan el salario promedio? \n");
    printf("%d \n", aboveA);
    return 0;
}
*/

void hardcodeo(eEmployee* listi){
    eEmployee y[]={
        {1, "Lionel", "Messi", 15000, 5, 0},
        {2, "Luis Alberto", "Spinetta", 25000, 4, 0},
        {3, "Armando", "Puertas", 10000, 5, 0},
        {4, "Antonio", "Margarette", 30000, 1, 0},
        {5, "Monica", "Galindo", 23000, 2, 0},
        {6, "Martin", "Cabrera", 31000, 5, 0},
        {7, "Esteban", "Quito", 27000, 5, 0},
    };

    for(int i=0; i<7; i++){
        listi[i] = y[i];
    }
    printf("LISTO\n");
}

