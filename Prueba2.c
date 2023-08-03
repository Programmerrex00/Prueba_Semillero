#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#define TAM 50

//structs
struct admin{
    char usuario[TAM];
    char password[TAM];
    char frase_secreta[TAM];
};
typedef struct admin Admin;

struct libro{
    int id_libro;
    int id_usuario;
    char nombre_libro[TAM];
    char autor[TAM];
    char editorial[TAM];
    char estado[TAM];
};

typedef struct libro Libro;

struct usuario{
    int id_usuario;
    char nombre_usuario[TAM];
    int cedula;
    char password[TAM];
    char bloqueo[TAM];
    int cantidadLibros;
};

typedef struct usuario Usuario;

struct prestamos{
    int id_prestamo;
    int id_libro;
    int id_usuario;
    int tiempo_prestamo;
    char verificar_entrega[TAM];
    struct tm fecha_inicio;
    struct tm fecha_final;
};

typedef struct prestamos Prestamos;

int main(){
    setlocale(LC_ALL, "spanish");
    menuPrincipal();
    return 0;
}

void menuPrincipal(){
    int opcion;
    do{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t\tBIENVENIDO A APP-BOOK\n");
        printf("\n\t\t[1]. Login\n");
		printf("\t\t[2]. Registrate aca!!\n");
		printf("\t\t[3]. Panel de Admistrador\n");
        printf("\t\t[4]. Salir\n");
        printf("\n\t\tIngrese su opcion: [ ]\b\b");
        scanf("%i", &opcion);
        switch (opcion){
        case 1:    
            logueoYFunciones();
            break;
        case 2:    
            registroUsuario(); 
            break;
        case 3:   
            panelAdministrador(); 
            break;      
        case 4:    
        printf("\t\t--Sistema Finalizado--");
            break;      
        }
    } while (opcion != 4);
}





//Metodos para el registro

Usuario *obtenerUsuarios(int *n){
    FILE *archivo;
    Usuario usuario;
    Usuario *Usuarios;
    int i;

    archivo = fopen("usuarios.dat", "rb");

    if(archivo == NULL){
        *n = 0;
        Usuarios = NULL;
    }else{
        fseek(archivo, 0, SEEK_END);
        *n = ftell(archivo) / sizeof(Usuario);
        Usuarios = (Usuario *)malloc((*n) * sizeof(Usuario));

        fseek(archivo, 0, SEEK_SET);
        fread(&usuario, sizeof(usuario), 1, archivo);
        i = 0;
        while(!feof(archivo)){
            Usuarios[i++] = usuario;
            fread(&usuario, sizeof(usuario), 1, archivo);
        }
         fclose(archivo);
    }
   
    return Usuarios;
}


void registroUsuario(){
    Usuario usuario;
    FILE *archUsuario;
    int  numeroUsuarios;
    char archivoID[TAM];
    char nombreUsuario[TAM];
    Usuario *Usuarios;

    strcpy(archivoID, "autoincrementoUser.dat");
    Usuarios = obtenerUsuarios(&numeroUsuarios);
    system(CLEAR);
    tituloPrincipal();
    archUsuario = fopen("usuarios.dat", "ab");
    if(archUsuario == NULL)
        exit(1);
    printf("\n\t\t\t==> REGISTRO USUARIO <==\n");
    fflush(stdin);
    printf("\n\tNombre de Usuario: ");
    gets(nombreUsuario);

    if(numeroUsuarios != 0){
    for (int i = 0; i < numeroUsuarios; i++){
            while (strcmp(nombreUsuario, Usuarios[i].nombre_usuario) == 0){
                printf("\tEste nombre de usuario ya se encuentra en el sistema (Porfavor Ingrese otro): ");
                gets(nombreUsuario);
                i = 0;
            }
        }
    }
    strcpy(usuario.nombre_usuario, nombreUsuario);
    fflush(stdin);
    usuario.id_usuario = archivoAutoincremento(archivoID);

    printf("\tCedula: ");
    scanf("%i", &usuario.cedula);

    fflush(stdin);
    printf("\tContraseña: ");
    gets(usuario.password);
   
    strcpy(usuario.bloqueo, "NO");
    usuario.cantidadLibros = 0;
    fwrite(&usuario, sizeof(Usuario), 1, archUsuario);
    fclose(archUsuario);
    printf("\t\n USUARIO %s REGISTRADO EXITOSAMENTE!!!", usuario.nombre_usuario);
    getchar();
}



//---------------------------------------------------------------

//metodos para funciones del logueo del usuario


void logueoYFunciones(){
    Usuario *Usuarios;
    int numeroUsuarios, ok = 0, opcion, bloqueado = 0;
    Usuario user;
    char userName[TAM], userPassword[TAM];
    Usuarios = obtenerUsuarios(&numeroUsuarios);
    system(CLEAR);
    tituloPrincipal();
   

    fflush(stdin);
    printf("\n\tNOMBRE DEL USUARIO  (Para regresar al menu principal dijite (x)): ");
    gets(userName);
    if (strcmp(userName, "x") == 0 || strcmp(userName, "X") == 0 ) {
        return;
    }
    printf("\n\tPASSWORD DEL USUARIO  (Para regresar al menu principal dijite (x)): ");
    gets(userPassword);
    if (strcmp(userPassword, "x") == 0 || strcmp(userPassword, "X") == 0 ) {
        return;
    }

    for (int i = 0; i <= numeroUsuarios; i++){
        if(bloqueado == 1){
            i = 0;
        }
        bloqueado = 0;
        while( strcmp(userName, Usuarios[i].nombre_usuario) != 0 && strcmp(userPassword, Usuarios[i].password) != 0  && i == numeroUsuarios){
            system(CLEAR);
            tituloPrincipal();
            printf("\n\t\t\t==> LOGIN USUARIO <==\n");
            printf("\n\t\t\t==> USUARIO O PASSWORD INCORRECTAS <==\n");
            fflush(stdin);
            printf("\n\tNOMBRE DEL USUARIO  (Para regresar al menu principal dijite (x)): ");
            gets(userName);
            if (strcmp(userName, "x") == 0 || strcmp(userName, "X") == 0 ) {
                return;
            }
            printf("\n\tPASSWORD DEL USUARIO  (Para regresar al menu principal dijite (x)): ");
            gets(userPassword);
            if (strcmp(userPassword, "x") == 0 || strcmp(userPassword, "X") == 0 ) {
                return;
            }            
            ok = 0;
            i = 0;
        }
         if(strcmp(userName, Usuarios[i].nombre_usuario) == 0 && strcmp(userPassword, Usuarios[i].password) == 0 && strcmp(Usuarios[i].bloqueo, "SI") == 0){
            system(CLEAR);
            tituloPrincipal();
            printf("\n\t\t\t==> LOGIN USUARIO <==\n");
            printf("\n\t\t\t==> ESTE USUARIO ESTA BLOQUEADO <==\n");
            fflush(stdin);
            printf("\n\tNOMBRE DEL USUARIO  (Para regresar al menu principal dijite (x)): ");
            gets(userName);
            if (strcmp(userName, "x") == 0 || strcmp(userName, "X") == 0 ) {
                return;
            }
            printf("\n\tPASSWORD DEL USUARIO  (Para regresar al menu principal dijite (x)): ");
            gets(userPassword);
            if (strcmp(userPassword, "x") == 0 || strcmp(userPassword, "X") == 0 ) {
                return;
            }
            ok = 0;
            i = 0;
            bloqueado = 1;
        }
         if(strcmp(userName, Usuarios[i].nombre_usuario) == 0 && strcmp(userPassword, Usuarios[i].password) == 0 && strcmp(Usuarios[i].bloqueo, "NO") == 0){
            user = Usuarios[i];
            ok = 1;
        }
        if(ok == 1){
            break;
        }
    }





    do{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t==> USUARIO %s <==\n", userName);
        printf("\n\t\t[1]. Ver libros disponibles\n");
		printf("\t\t[2]. Libros que tengo en mi servicio\n");
		printf("\t\t[3]. Pedir un libro\n");
        printf("\t\t[4]. Entregar un libro\n");
        printf("\t\t[5]. Cerrar cesion\n");
        printf("\n\t\tIngrese su opcion: [ ]\b\b");
        scanf("%i", &opcion);
        //Con esto limpiamos el buffe, para utilizar getch
        while (getchar() != '\n');
        switch (opcion){
        case 1:
            listadoLibrosDisponibles();
            break;
        case 2:
             verMisLibros(user);
            break;
        case 3:
            pedirLibro(user);
            break;
        case 4:
            entregarLibro(user);
            break;
        case 5:
        printf("\n\tSESION CERRADA");
            getchar(); 
            break;
        }

    } while (opcion != 5);


}

Libro *obtenerLibros(int *n){
    FILE *archivo;
    Libro libro;
    Libro *Libros;
    int i;

    archivo = fopen("libros.dat", "rb");

    if(archivo == NULL){
        *n = 0;
        Libros = NULL;
    }else{
        fseek(archivo, 0, SEEK_END);
        *n = ftell(archivo) / sizeof(Libro);
        Libros = (Libro *)malloc((*n) * sizeof(Libro));

        fseek(archivo, 0, SEEK_SET);
        fread(&libro, sizeof(libro), 1, archivo);
        i = 0;
        while(!feof(archivo)){
            Libros[i++] = libro;
            fread(&libro, sizeof(libro), 1, archivo);
        }
        fclose(archivo);
    }

    return Libros;
}

void listadoLibrosDisponibles(){
    Libro *Libros;
    int cantidadLibros;
    Libros = obtenerLibros(&cantidadLibros);

    system(CLEAR);
    tituloPrincipal();
    printf("\n\t\t    ==> LISTADO DE LIBROS DISPONIBLES <==\n");
    if(cantidadLibros == 0){
        printf("\n\t\t    ==> NO HAY LIBROS DISPONIBLES <==\n");
        getchar();
        return;
    }else{
        printf(" ------------------------------------------------------------------------------\n");
        printf("%8s \t%-20s%15s%20s\n", "ID", "NOMBRE", "AUTOR", "EDITORIAL");
        printf(" ------------------------------------------------------------------------------\n");
        for (int i = 0; i < cantidadLibros; i++){
            if(strcmp(Libros[i].estado, "NO PRESTADO") == 0){
                printf("%7d \t%-30.30s%-20.20s%-20.20s\n", Libros[i].id_libro, Libros[i].nombre_libro, Libros[i].autor, Libros[i].editorial);
            }
        }
        getchar();
        return;
    }
} 





char modificarLibro(Libro newLibro){
    FILE *archivo;
    char modifica;
    Libro libroAux;

    archivo = fopen("libros.dat", "rb+");
    if(archivo == NULL){
        modifica = 0;
    }else{
        modifica = 0;
        fread(&libroAux, sizeof(Libro), 1, archivo);
        while(!feof(archivo)){
            if(libroAux.id_libro == newLibro.id_libro){
                fseek(archivo, ftell(archivo) - sizeof(newLibro), SEEK_SET);
                fwrite(&newLibro, sizeof(newLibro), 1, archivo);
                modifica = 1;
                break;
            }
            fread(&libroAux, sizeof(libroAux), 1, archivo);
        }
        fclose(archivo);
    }
    return modifica;
}



//CAMBIAR
// void verMisLibros(Usuario usuario){
//     Libro libro;
//     Usuario user;
//     FILE* archivoUsuarios = fopen("usuarios.dat", "rb");
//     int encontrado = 0;

//     system(CLEAR);
//     tituloPrincipal();
//     printf("\n\t\t    ==> LIBROS DE %s <==\n", usuario.nombre_usuario);
//     if(usuario.cantidadLibros > 0 ){
//     printf(" ------------------------------------------------------------------------------\n");
//     printf("%8s \t%-20s%15s%15s\n", "ID", "NOMBRE", "AUTOR", "EDITORIAL");
//     printf(" ------------------------------------------------------------------------------\n");
//     while(fread(&user, sizeof(Usuario), 1, archivoUsuarios) == 1){
//         if(user.id_usuario == usuario.id_usuario){
//             for (int i = 0; i < usuario.cantidadLibros; i++){
//                 fread(&libro, sizeof(Libro), 1, archivoUsuarios);
//                  printf("%7d \t%-30.20s%-13.20s%-40.20s\n", libro.id_libro, libro.nombre_libro, libro.autor, libro.editorial);
//                  encontrado = 1;
//             }
//             if(encontrado == 1){
//                 break;
//             }
//         }
//     }    
//     fclose(archivoUsuarios);
//     getchar();
//     return;


//     }else{
//         printf("\n\t    ==> EL USUARIO %s NO TIENE LIBROS PRESTADOS <==\n", usuario.nombre_usuario);
//         getchar();
//         return;
//     }
// }



void verMisLibros(Usuario usuario){
    Libro libro;
    FILE* archivoLibros = fopen("libros.dat", "rb");
    int cantidadUsuarios;
    Usuario userVerdadero;
    Usuario *user = obtenerUsuarios(&cantidadUsuarios);
    for (int i = 0; i < cantidadUsuarios; i++){
        if(usuario.id_usuario == user[i].id_usuario){
            userVerdadero = user[i];
            break;
        }
    }
    system(CLEAR);
    tituloPrincipal();
    printf("\n\t\t    ==> LIBROS DE %s <==\n", usuario.nombre_usuario);
    if(userVerdadero.cantidadLibros > 0 ){
    printf(" ------------------------------------------------------------------------------\n");
    printf("%8s \t%-20s%15s%15s\n", "ID", "NOMBRE", "AUTOR", "EDITORIAL");
    printf(" ------------------------------------------------------------------------------\n");
    fread(&libro, sizeof(Libro), 1, archivoLibros);
    while(!feof(archivoLibros)){
        if(libro.id_usuario == userVerdadero.id_usuario){
            printf("%7d \t%-30.20s%-13.20s%-40.20s\n", libro.id_libro, libro.nombre_libro, libro.autor, libro.editorial);
        }
        fread(&libro, sizeof(Libro), 1, archivoLibros);
    }    
    fclose(archivoLibros);
    getchar();
    return;
    }else{
        printf("\n\t    ==> EL USUARIO %s NO TIENE LIBROS PRESTADOS <==\n", usuario.nombre_usuario);
        getchar();
        return;
    }
}





void pedirLibro(Usuario user){
    Prestamos prestamo;
    char archivoID[TAM], respuesta[TAM];
    int cantidadLibros, repite = 0, id, correcto = 0;
    Libro *libros = obtenerLibros(&cantidadLibros);
    Libro libroCambiarEstado;

    if(cantidadLibros > 0){
        do{
            listadoLibrosDisponibles();
            printf("\tID del libro a Prestar atras->(0): ");
            scanf("%i", &id);
            if(id == 0){
                return;
            }
            for (int i = 0; i <= cantidadLibros; i++){
            if(libros[i].id_libro != id && i == cantidadLibros){
                system(CLEAR);
                tituloPrincipal();
                listadoLibrosDisponibles();
                printf("\n\t\t\t==> ID NO ENCONTRADO!!<==\n");
                printf("\tID de libro a Prestar atras->(0): ");
                scanf("%i", &id);
                fflush(stdin);
                if(id == 0){
                    return;
                }
                i = 0;
            }
            if(libros[i].id_libro == id && strcmp(libros[i].estado, "NO PRESTADO") == 0){
                libroCambiarEstado = libros[i];
                correcto = 1;
                break;
            }
            if(libros[i].id_libro == id && strcmp(libros[i].estado, "PRESTADO") == 0){
                correcto = 0;
                printf("\n\t==> ESTE LIBRO SE ENCUENTRA PRESTADO, NO ES POSIBLE RESERVARLO<==\n");
                break;
            }
        }

        if(correcto == 1){
        FILE *archivoPrestamos;

        archivoPrestamos = fopen("prestamos.dat", "ab");

        strcpy(archivoID, "autoincrementoPrestamo.dat");
        prestamo.id_prestamo = archivoAutoincremento(archivoID);
        printf("\tIngrese el tiempo que desea tener el libro, atras->(0): ");
        scanf("%i", &prestamo.tiempo_prestamo);
        if(prestamo.tiempo_prestamo == 0){
            fclose(archivoPrestamos);
            return;
        }
        prestamo.id_usuario = user.id_usuario;
        prestamo.id_libro = id;
        strcpy(prestamo.verificar_entrega, "NO ENTREGADO");

        time_t t_actual = time(NULL);
        prestamo.fecha_inicio = *localtime(&t_actual);
        prestamo.fecha_final = prestamo.fecha_inicio;

        sumarDias(&prestamo.fecha_final, prestamo.tiempo_prestamo);

         fwrite(&prestamo, sizeof(Prestamos), 1, archivoPrestamos);
         fclose(archivoPrestamos);

        fflush(stdin);
        //Manipulamos archivo usuario y libros
        libroCambiarEstado.id_usuario = user.id_usuario;
        strcpy(libroCambiarEstado.estado, "PRESTADO");
        char actualizacion = modificarLibro(libroCambiarEstado);

        user.cantidadLibros = 1 + user.cantidadLibros;
        // if(user->libros == NULL){
        //     user->libros = (Libro*)malloc(user->cantidadLibros * sizeof(Libro));
        // }else{
        //     user->libros = (Libro*)realloc(user->libros, user->cantidadLibros * sizeof(Libro));
        // }
        // user->libros[user->cantidadLibros - 1] = libroCambiarEstado;

        FILE *archivoUsuarios;
        Usuario usuarioLibro;
        archivoUsuarios = fopen("usuarios.dat", "rb+");
        if(archivoUsuarios == NULL)
             exit(1);
        fread(&usuarioLibro, sizeof(usuarioLibro), 1, archivoUsuarios);
        while(!feof(archivoUsuarios)){
            if(usuarioLibro.id_usuario == user.id_usuario){
                fseek(archivoUsuarios, ftell(archivoUsuarios) - sizeof(user), SEEK_SET);
                break;
            }
            fread(&usuarioLibro, sizeof(usuarioLibro), 1, archivoUsuarios);
        }
        fwrite(&user, sizeof(user), 1, archivoUsuarios);
//    for (int i = 0; i < user->cantidadLibros; i++) {
//         fwrite(&user->libros[i], sizeof(Libro), 1, archivoUsuarios);
//     }
        fclose(archivoUsuarios);
        printf("\n\t\t\t==> LIBRO %s AGREGADO RESERVADO EXITOSAMENTE <==\n", libroCambiarEstado.nombre_libro);
        }
        fflush(stdin);
        printf("\n\tDesea reservar otro libro? [S/N]");
        gets(respuesta);
        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
            repite = 1;
        }
        } while (repite);
    }else{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t==> LISTADO DE LIBROS DISPONIBLES <==\n");
        printf("\n\t\t\t==> NO HAY LIBROS PARA RESERVAR <==\n");
        getchar();
    }
}

void sumarDias(struct tm* fecha, int dias){
    time_t tiempo = mktime(fecha);
    tiempo += (dias * 86400);
    *fecha = *localtime(&tiempo); 
}





void entregarLibro(Usuario user){
    int idLibroEntregar, repite = 0;
    char respuesta[TAM];

    do{
        verMisLibros(user);
        Libro *libros, libroActualizado;
        int cantidadLibros;
        libros = obtenerLibros(&cantidadLibros);
        printf("\n\tID del libro a devolver atras->(0)");
        scanf("%i", &idLibroEntregar);
        if(idLibroEntregar == 0){
            return;
        }
        for (int i = 0; i <= cantidadLibros; i++){
            if(idLibroEntregar == libros[i].id_usuario && i == cantidadLibros){
                verMisLibros(user);
                printf("\n\t\t\t==> ID NO ENCONTRADO!!<==\n");
                printf("\tID del libro que desea entregar atras->(0)");
                scanf("%i", &idLibroEntregar);
                fflush(stdin);
                if(idLibroEntregar == 0){
                    return;
                }
                i = 0;
            }
            if(idLibroEntregar == libros[i].id_libro){
                libroActualizado = libros[i];
                libroActualizado.id_usuario = 0;
                strcpy(libroActualizado.estado, "NO PRESTADO");
                break;
            }
        }
        modificarLibro(libroActualizado);

        FILE* archivoPrestamo;
        Prestamos prestamo;
        archivoPrestamo = fopen("prestamos.dat", "rb+");

        fread(&prestamo, sizeof(Prestamos), 1, archivoPrestamo);
        while(!feof(archivoPrestamo)){
            if(prestamo.id_libro = libroActualizado.id_libro){
                fseek(archivoPrestamo, ftell(archivoPrestamo) - sizeof(prestamo), SEEK_SET);
                break;
            }
            fread(&prestamo, sizeof(prestamo), 1, archivoPrestamo);
        }
        strcpy(prestamo.verificar_entrega, "ENTREGADO");
        fwrite(&prestamo, sizeof(prestamo), 1, archivoPrestamo);
        fclose(archivoPrestamo);
        printf("\n\tLibro %s entregado exitosamente", libroActualizado.nombre_libro);


        fflush(stdin);
        printf("\n\tDesea bloquear desbloquear otro usuario? [S/N]");
        gets(respuesta);
        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
            repite = 1;
        }
    } while(repite);
    
}

























//Metodos del administrador

void panelAdministrador(){
    int validar, opcion;
    validar = loginAdmin();
    if(validar == 0){
        return;
    }

    system(CLEAR);
    tituloPrincipal();
    printf("\n\t\t    ==> PANEL DE CONTROL <==\n");


    do{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t\t==> ADMIN <==");
        printf("\n\t\t[1]. Agregar libros\n");
		printf("\t\t[2]. Editar Libros\n");
		printf("\t\t[3]. Eliminar libros\n");
        printf("\t\t[4]. Bloquear Usuarios\n");
        printf("\t\t[5]. Ver Usuarios y Libros\n");
        printf("\t\t[6]. Ver usuarios con Retraso en entrega\n");
        printf("\t\t[7]. Cerrar cesion\n");
        printf("\n\t\tIngrese su opcion: [ ]\b\b");
        scanf("%i", &opcion);
        //Con esto limpiamos el buffe, para utilizar getch
        while (getchar() != '\n');
        switch (opcion){
        case 1:
            agregarLibro();
            break;
        case 2:
            editar();
            break;
        case 3:
            Eliminar();
            break;
        case 4:
           bloquearUsuarios();
            break;
        case 5:
            break;
        case 6:
            break;        
        case 7:
        printf("\n\tSESION CERRADA");
            getchar(); 
            break;
        }
    } while (opcion != 7);

}

void listarUsuarios(){
    Usuario *usuarios;
    int cantidadUsuarios = 0;
    usuarios = obtenerUsuarios(&cantidadUsuarios);
    system(CLEAR);
    tituloPrincipal();
    printf("\n\t\t    ==> GESTIONAR ESTADO DEL USUARIO <==\n");
    printf(" ------------------------------------------------------------------------------\n");
    printf("%8s \t%-20s%15s%15s%15s%30s\n", "ID", "NOMBRE", "CEDULA", "PASSWORD", "BLOQUEO", "CANTIDAD DE LIBROS");
    printf(" ------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidadUsuarios; i++){
        printf("%7d \t%-30.20s%20d%-13.20s%-13.20s%10d\n", usuarios[i].id_usuario, usuarios[i].nombre_usuario,
         usuarios[i].cedula, usuarios[i].password, usuarios[i].bloqueo, usuarios[i].cantidadLibros);
    }
    
}

void bloquearUsuarios(){
    int cantidadUsuarios, idBloquear, repite = 0;
    char respuesta[TAM];
    Usuario *usuarios, usuarioEdit;
    usuarios = obtenerUsuarios(&cantidadUsuarios);
    if(cantidadUsuarios > 0){
    do{
        listarUsuarios();
        printf("\n\tID del usuario que desea bloquear o desbloquear atras->(0)");
        scanf("%i", &idBloquear);
        if(idBloquear == 0){
            return;
        }
        for (int i = 0; i <= cantidadUsuarios; i++){
            if(usuarios[i].id_usuario != idBloquear && i == cantidadUsuarios){
            listarUsuarios();
            printf("\n\t\t\t==> ID NO ENCONTRADO!!<==\n");
            printf("\tID del usuario que desea bloquear o desbloquear atras->(0)");
            scanf("%i", &idBloquear);
            fflush(stdin);
            if(idBloquear == 0){
                return;
            }
            i = 0;
            }
            if(usuarios[i].id_usuario == idBloquear && strcmp(usuarios[i].bloqueo, "NO") == 0){
                printf("\n\t\t\t==> USUARIO %s BLOQUEADO!!<==\n", usuarios[i].nombre_usuario);
                usuarioEdit = usuarios[i];
                strcpy(usuarioEdit.bloqueo, "SI");
                break;
            }
            if(usuarios[i].id_usuario == idBloquear && strcmp(usuarios[i].bloqueo, "SI") == 0){
                printf("\n\t\t\t==> USUARIO %s DESBLOQUEADO!!<==\n", usuarios[i].nombre_usuario);
                usuarioEdit = usuarios[i];
                strcpy(usuarioEdit.bloqueo, "NO");
                break;
            }
        }
        FILE *archivoUsuarios;
        Usuario userAux;

        archivoUsuarios = fopen("usuarios.dat", "rb+");
        fread(&userAux, sizeof(userAux), 1, archivoUsuarios);
        while(!feof(archivoUsuarios)){
            if(userAux.id_usuario == usuarioEdit.id_usuario){
                fseek(archivoUsuarios, ftell(archivoUsuarios) - sizeof(usuarioEdit), SEEK_SET);
                fwrite(&usuarioEdit, sizeof(usuarioEdit), 1, archivoUsuarios);   
                break;
            }
            fread(&userAux, sizeof(userAux), 1, archivoUsuarios);
        }
        fclose(archivoUsuarios);

        fflush(stdin);
        printf("\n\tDesea bloquear desbloquear otro usuario? [S/N]");
        gets(respuesta);
        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
            repite = 1;
        }
    } while (repite);
    }else{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t    ==> GESTIONAR ESTADO DEL USUARIO <==\n");
        printf("\n\t\t\t==> NO HAY USUARIOS DISPONIBLES <==\n");
        getchar();        
    }

    
}

// void verPrestamos(){
//     system(CLEAR);
//     tituloPrincipal();
//     int idLibro;
//     printf("Ingrese el id del Libro del prestamo: ");
//     scanf("%i", &idLibro);
//     Prestamos prestamo;
//     FILE* archivoPrestamos = fopen("prestamos.dat", "rb");
//     int in;
//     fread(&prestamo, sizeof(Prestamos), 1, archivoPrestamos);
//     while(!feof(archivoPrestamos)){
//         if(prestamo.id_libro == idLibro){
//             printf("%i %i %i FECHA INICIO: %i/%i/%i FECHA FIN: %i/%i/%i", prestamo.id_prestamo, prestamo.id_usuario, prestamo.id_libro,
//             prestamo.fecha_inicio.tm_mday, prestamo.fecha_inicio.tm_mon + 1, prestamo.fecha_inicio.tm_year + 1900,
//             prestamo.fecha_final.tm_mday, prestamo.fecha_final.tm_mon + 1, prestamo.fecha_final.tm_year + 1900);
//             scanf("%i", &in);
//             break;
//         }
//         fread(&prestamo, sizeof(prestamo), 1, archivoPrestamos);
//     }

// }



void agregarLibro(){
    FILE *archivoLibros;
    Libro librito;
    char repite = 0;
    char archivoID[TAM], respuesta[TAM];
    archivoLibros = fopen("libros.dat", "ab");
    if(archivoLibros == NULL)
        exit(1);
    do{
        system(CLEAR);
        tituloPrincipal();
        strcpy(archivoID, "autoincrementoLib.dat");
        librito.id_libro = archivoAutoincremento(archivoID);
        printf("\n\t\t\t==> REGISTRO LIBROS <==\n");

        printf("\tID: %i\n", librito.id_libro);
        
        fflush(stdin); 

        printf("\tNombre: ");
        gets(librito.nombre_libro);
        librito.id_usuario =0;
        printf("\tAutor: ");
        gets(librito.autor);

        printf("\tEditorial: ");
        gets(librito.editorial);

        strcpy(librito.estado, "NO PRESTADO");
        repite = 0;
        fwrite(&librito, sizeof(Libro), 1, archivoLibros);
        printf("\n\tDesea agregar otro libro? [S/N]");
        gets(respuesta);
        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
            repite = 1;
        }
    } while (repite);
    
    fclose(archivoLibros);
}





void Eliminar(){
    FILE *archivoLibros;
    FILE *archivoTemporal;
    Libro libro;
    char respuesta[TAM];
    int id, repite = 0, longitud, correcto = 0;
    Libro *Libros;
    Libros = obtenerLibros(&longitud);
    if(longitud > 0){
    do{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t==> ELIMINAR LIBROS <==\n");
        printf("\tID de libro a eliminar atras->(0): ");
        scanf("%i", &id);
        if(id == 0){
            return;
        }
        for (int i = 0; i <= longitud; i++){
            if(Libros[i].id_libro != id && i == longitud){
                system(CLEAR);
                tituloPrincipal();
                printf("\n\t\t\t==> ELIMINAR LIBROS <==\n");
                printf("\n\t\t\t==> ID NO ENCONTRADO!!<==\n");
                printf("\tID de libro a eliminar atras->(0): ");
                scanf("%i", &id);
                fflush(stdin);
                if(id == 0){
                    return;
                }
                i = 0;
            }
            if(Libros[i].id_libro == id && strcmp(Libros[i].estado, "NO PRESTADO") == 0){
                correcto = 1;
                break;
            }
            if(Libros[i].id_libro == id && strcmp(Libros[i].estado, "PRESTADO") == 0){
                correcto = 0;
                printf("\n\t==> ESTE LIBRO SE ENCUENTRA PRESTADO, NO ES POSIBLE ELIMINARLO<==\n");
                break;
            }
        }
        if(correcto == 1){
            archivoLibros = fopen("libros.dat", "rb");
            if(archivoLibros == NULL)
                return;

            archivoTemporal = fopen("archivoTemporal.dat", "ab");
            if(archivoTemporal == NULL)
                return;

            while (fread(&libro, sizeof(Libro), 1, archivoLibros) == 1){
                if(libro.id_libro != id){
                    fwrite(&libro, sizeof(Libro), 1, archivoTemporal);
                }
            }
            fclose(archivoLibros);
            fclose(archivoTemporal);

            remove("libros.dat");
            rename("archivoTemporal.dat", "libros.dat");
            printf("\n\t\t\t==> LIBRO ELIMINADO EXITOSAMENTE<==\n");
        }

        fflush(stdin);
        printf("\n\tDesea eliminar otro libro? [S/N]");
        gets(respuesta);
        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
            repite = 1;
        }
    } while (repite);
    }else{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t==> ELIMINAR LIBROS <==\n");
        printf("\n\t\t\t==> NO HAY LIBROS PARA ELIMINAR <==\n");
        getchar();
    }
}





void editar(){
    Libro *Libros;
    int longitud;
    char respuesta[TAM];
    Libros = obtenerLibros(&longitud);
    int id, repite = 0, correcto = 0;
    Libro libParam;
    if(longitud > 0){
    do{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t==> EDITAR LIBROS <==\n");
        printf("\tID de libro a editar atras->(0): ");
        scanf("%i", &id);
        if(id == 0){
            return;
        }
        for (int i = 0; i <= longitud; i++){
            if(Libros[i].id_libro != id && i == longitud){
                system(CLEAR);
                tituloPrincipal();
                printf("\n\t\t\t==> EDITAR LIBROS <==\n");
                printf("\n\t\t\t==> ID NO ENCONTRADO!!<==\n");
                printf("\tID de libro a editar atras->(0): ");
                scanf("%i", &id);
                fflush(stdin);
                if(id == 0){
                    return;
                }
                i = 0;
            }
            if(Libros[i].id_libro == id && strcmp(Libros[i].estado, "NO PRESTADO") == 0){
                correcto = 1;
                libParam = Libros[i];
                break;
            }
            if(Libros[i].id_libro == id && strcmp(Libros[i].estado, "PRESTADO") == 0){
                correcto = 0;
                printf("\n\t==> ESTE LIBRO SE ENCUENTRA PRESTADO, NO ES POSIBLE EDITARLO<==\n");
                break;
            }
        }

        if(correcto == 1){
            printf("\n\tNombre del libro: %s\n", libParam.nombre_libro);
			printf("\tAutor del libro: %s\n", libParam.autor);
			printf("\tEditorial del libro: %s\n", libParam.editorial);
            printf("\tEstado del libro: %s\n", libParam.estado);

            printf("\n\tElija los datos a modificar\n");
            fflush(stdin);
            printf("\n\tNombre actual del libro: %s\n", libParam.nombre_libro);
            printf("\tDesea modificar el nombre del libro? [S/N]");
            gets(respuesta);
            if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
                printf("\tIngrese el nuevo nombre del libro: ");
                gets(libParam.nombre_libro);
            }


            printf("\n\tAutor actual del libro: %s\n", libParam.autor);
            printf("\tDesea modificar el autor del libro? [S/N]");
            gets(respuesta);
            if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
                printf("\tIngrese el nuevo autor del libro: ");
                gets(libParam.autor);
            }


            printf("\n\tEditorial actual del libro: %s\n", libParam.editorial);
            printf("\tDesea modificar la editorial del libro? [S/N]");
            gets(respuesta);
            if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
                printf("\tIngrese la nueva editorial del libro: ");
                gets(libParam.editorial);
            }

            printf("\n\tEstado actual del libro: %s\n", libParam.estado);
            printf("\tDesea modificar el estado del libro? [S/N]");
            gets(respuesta);
            if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
                printf("\tIngrese el nuevo estado del libro (PRESTADO - NO PRESTADO): ");
                gets(libParam.estado);
            }

            if(modificarLibro(libParam)){
                printf("\n\tEl Libro ha sido modificado exitosamente!");
                printf("\n\t\t\t==> LIBRO ACTUALIZADO EXITOSAMENTE <==\n");
            }else{
                printf("\n\tOcurrió un error al intentar modificar el producto\n");
				printf("\tInténtelo mas tarde\n");
            }
        }        

        fflush(stdin);
        printf("\n\tDesea editar otro libro? [S/N]");
        gets(respuesta);
        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0){
            repite = 1;
        }
    } while (repite);

    }else{
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t\t==> EDITAR LIBROS <==\n");
        printf("\n\t\t\t==> NO HAY LIBROS PARA EDITAR <==\n");
        getchar();
    }
}

int loginAdmin(){
    Admin administrador, verificarAdmin;
    strcpy(administrador.usuario, "admin");
    strcpy(administrador.password, "123");
    strcpy(administrador.frase_secreta, "wow");

    system(CLEAR);
    tituloPrincipal();
    printf("\n\t\t    ==> LOGIN ADMINISTRADOR <==\n");

    fflush(stdin);
    printf("\tUsuario regresar->(x): ");
    gets(verificarAdmin.usuario);
    if(strcmp(verificarAdmin.usuario, "x") == 0 || strcmp(verificarAdmin.usuario, "X") == 0){
        return 0;
    }
    printf("\tPassword regresar->(x): ");
    gets(verificarAdmin.password);
        if(strcmp(verificarAdmin.password, "x") == 0 || strcmp(verificarAdmin.password, "X") == 0){
        return 0;
    }
    printf("\tFrase secreta regresar->(x): ");
    gets(verificarAdmin.frase_secreta);
        if(strcmp(verificarAdmin.frase_secreta, "x") == 0 || strcmp(verificarAdmin.frase_secreta, "X") == 0){
        return 0;
    }

    while(strcmp(verificarAdmin.usuario, administrador.usuario) != 0 ||
    strcmp(verificarAdmin.password, administrador.password) != 0 ||
    strcmp(verificarAdmin.frase_secreta, administrador.frase_secreta) != 0){
        system(CLEAR);
        tituloPrincipal();
        printf("\n\t\t    ==> ERROR DE CREENCIALES <==\n");

        fflush(stdin);
        printf("\tUsuario regresar->(x): ");
        gets(verificarAdmin.usuario);
        if(strcmp(verificarAdmin.usuario, "x") == 0 || strcmp(verificarAdmin.usuario, "X") == 0){
        return 0;
        }
        printf("\tPassword regresar->(x): ");
        gets(verificarAdmin.password);
        if(strcmp(verificarAdmin.password, "x") == 0 || strcmp(verificarAdmin.password, "X") == 0){
        return 0;
        }
        printf("\tFrase secreta regresar->(x): ");
        gets(verificarAdmin.frase_secreta);
        if(strcmp(verificarAdmin.frase_secreta, "x") == 0 || strcmp(verificarAdmin.frase_secreta, "X") == 0){
        return 0;
        }
    }
    return 7;
}

//-----------------------------------------------------------

int archivoAutoincremento(char archivoo[TAM]){
    FILE *archivo = fopen(archivoo, "r+b");
    int idAculmulado;
    if(archivo == NULL){
        idAculmulado = 1;
        archivo = fopen(archivoo, "wb");
        fwrite(&idAculmulado, sizeof(int),1,archivo);
    }else{
        fread(&idAculmulado, sizeof(int),1,archivo);
    }
    idAculmulado+=1;
    fseek(archivo, 0 , SEEK_SET);
    fwrite(&idAculmulado, sizeof(int), 1, archivo);
    fclose(archivo);
    return idAculmulado;
}


void tituloPrincipal(){
    int i;
    printf("\n     ======================================================================\n");
	printf("\t\t\t\t     LIBRERIA\n");
	printf("\t\t\t   SISTEMA DE GESTION DE LIBROS\n");
	printf("     ======================================================================\n");
 
	i = 0;
	putchar('\n');
	for (; i < 80; i++) {
		putchar('_');
	}
}