#include "Menus.h"
#define WIN
void Print_TrackTitle(Track item,size_t c){
	printf("%ld. %s\n",c,item.title);
}
void Print_PlaylistName(Playlist item,size_t c){
	printf("%ld. %s\n",c,item.name);
}

void Clear()
{
    #ifdef WIN
        system( "cls" ); //Limpia la pantalla en windows
    #endif

    #ifdef LIN

        system( "clear ");   //Limpia la pantalla en Linux
    #endif // LIN
}

void PrintMenuPrincipal(Player* this,Playlist* that)

{
	printf("\nReproductor (%d playlists)(%d canciones)\n",Player_Len(this),Playlist_Len(that));
	
    printf("\n\tMen� principal\n");
    printf("A) Lista de canciones completa\n");    //Mostraria todas las canciones de la lista principal
    printf("N) Nueva Playlist\n");                 //Crearia una nueva playlist y la almacenaria en la lista secundaria
    printf("Z) Nueva cancion\n");
	printf("D) Eliminar Playlist\n");              //Eliminaria una playlist contenida en la lista secundaria
    printf("X) Eliminar cancion\n");
	printf("R) Abrir Playlist\n");            //Mostraria un menu con opciones para una playlist
    printf("C) Limpiar pantalla\n");
	printf("E) Salir\n");                          //Salimos del programa de manera defenitiva

    //printf("H) Mostrar ayuda\n ");                  //Vuelve a mostrar este mensaje


}

void PrintMenuPlaylist(Playlist* this)
{
	
	printf("\nPlaylist: %s (%d canciones)\n",this->name,Playlist_Len(this));
	
    printf("\n\tMen� para Playlist\n");
    printf("A) Agregar canci�n\n");       										//Agrega una canci�n a la playlist en la que se este trabajando
    printf("X) Remover canci�n\n");       										//Quita una canci�n seleccionada por el usuario
    printf("P) Reproducir canci�n\n");    										//Simula la reproducci�n de la canci�n ( aun falta un detalle)
    //printf("H) Mostrar ayuda\n");         									//Vuelve a mostrar este men�
    //printf("T) Mostrar canciones\n");
    printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");                 										//Salimos de este men� y regresamos al principal
}

void PrintMenuCancion(Playlist* this,bool play)
{	if(play){
		printf("\nReproduciendo: ");
	} else{
		printf("\nEn pausa: ");
	}
	
	printf("%s\n",this->cursor->datos.title);
	
	Print_DataTrack(&this->cursor->datos);
	
    printf("\n\tMen� para Cancion\n");
    printf("R) Siguiente\n");       
    printf("L) Anterior\n");       
    printf("P) Pausar/Reproducir\n");    
	printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");                 
}

//Funcion de activacion del tercer menu

void TestMenuCancion(Playlist* this)
{
	Clear();
    bool play=true;
    char cmd;
    char str[80];

    do{
    	PrintMenuCancion(this,play);
        printf("\ncmd > > >: ");
        scanf( "%s", &str );
        cmd = str[0];

        switch( cmd )
        {
        	case 'C': case 'c': Clear(); /*PrintMenuPlaylist(this);*/ 
			break;
            case 'S': case 's':   
			break;
            case 'R': case 'r': 
            	Playlist_Cursor_next(this);
			break;
            case 'L': case 'l':
            	Playlist_Cursor_prev(this);
            break;
            case 'P': case 'p':
            	if(play){
            		play=false;
            	} else{
            		play=true;
            	}
            break;
            default:
                printf("Opci�n invalida!\n");
                //PrintMenuPlaylist(this);
            break;
        }
    } while( cmd != 'S' && cmd != 's');
}

// Funci�n de activaci�n de segundo men�

void TestMenuPlaylist( Player* player, Playlist* this, Playlist* that) 			//Deberia de pasarse una playlist en la que se guardara o modificaran canciones
{
    Clear();
    int opt;
    char cmd;
    char str[80];

    //PrintMenuPlaylist(this);

    do{
    	PrintMenuPlaylist(this);
        printf("\ncmd > > >: ");
        scanf( "%s", &str );
        cmd = str[0];

        switch( cmd )
        {
        	case 'C': case 'c': Clear(); 
			//*PrintMenuPlaylist(this);
			break;
        	case 'S': case 's':  
			break;
            case 'H': case 'h': 
			//PrintMenuPlaylist(this);
			break;
            case 'A': case 'a':;   												//";" corrige el error de compilaci�n
                                
                assert(!Playlist_IsEmpty(that));								//assert
				printf("\nElija una cancion\n");
				
            	Playlist_Traverse(that,Print_TrackTitle);
            	printf("\ncmd > > >: ");
            	scanf("%d",&opt);
            	
            																	//coloca al cursor en opt
            	Playlist_Cursor_front(that);
            	for(size_t i=0;i<opt;++i){
            		Playlist_Cursor_next(that);
            	}
            	Playlist_Cursor_prev(that);
            																	///////////////////////////////////
            	
            	Track v1=Playlist_Get(that);
                Playlist_Insert_back( this, &v1 ); 
				printf("\nInsertando %s en %s...\n",v1.title,this->name);
                
                //Print_DataTrack( v1 );
            break;
            case 'X': case 'x':
            	
                if( Playlist_IsEmpty( this ) == true ){
                    printf("\n��� Error !!! , la playlist esta vacia\n");
                    break;
                } else{
                    Clear();
                    printf("\n\t Eliga la canci�n que sera removida:\n");
                    Playlist_Cursor_front( this );

                    for( size_t i = 0; i<Playlist_Len( this ); ++i ){
                        printf("%d.- ",i+1); 
						puts( this->cursor->datos.title ); 						//Mostramos la lista de canciones en la playlist
                        Playlist_Cursor_next( this );
                    }

                    size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%ld", &p );

                    Playlist_Cursor_front( this );

                    if( p == 1){
                        printf("Removiendo "); 
						puts( this->cursor->datos.title); 
						printf("...\n");
						
                        Playlist_Remove_front( this );
                        
                    } else{
                        for( size_t i = 0; i< p-1; ++i ){
                            Playlist_Cursor_next( this );
                        }
                        printf("Removiendo "); 
						puts( this->cursor->datos.title);
                        Playlist_Remove( this );
                    }
                }
            break;
            case 'P': case 'p':

                if( Playlist_IsEmpty( this ) == true ){
                    printf("\n��� Error !!! , la playlist esta vacia\n");
                    break;
                } else{
                	
                	printf("\nElija una cancion\n"); 
                	Playlist_Traverse(this,Print_TrackTitle);					//Mostramos la lista de canciones en la playlist
                    					
                    size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%ld", &p );

                    Playlist_Cursor_front( this );

                    if( p == 1){
                        //printf("Reproduciendo "); 
						//puts( this->cursor->datos.title); 
						//printf("...\n");
						  														
                    } else{
                    	
                        for( size_t i = 0; i< p-1; ++i ){
                            Playlist_Cursor_next( this );
                        }
                        //printf("Reproduciendo "); 
						//puts( this->cursor->datos.title);
                    }
                    
                    Track t=Playlist_Get(this);
                    TestMenuCancion(this);										//Simulaci�n de la reproducci�n

                }

                																//Faltaria escoger una cancion, y nosotros simulamos la reproducci�n, ya sea agregando un indice
                																//o recorriendo la lista desde el primer nodo hasta el "numero" escogido por el usuario

                																// !!!ACTUALIZACI�N: El usuario ya puede escoger la canci�n, pero podria buscarse la forma
                																// de hacer "mas detallada" la simulaci�n de la reproducci�n

				//PrintMenuPlaylist(this);
            break;
            default:
                printf("Opci�n invalida!\n");
                //PrintMenuPlaylist(this);
            break;
        }
    } while( cmd != 'S' && cmd != 's');
}

void TestPrincipal()
{
	int opt;
	int id=1;
	
    char cmd;
    char str[80];
    																			/*  Se pueden crear dos listas doblemente enlazadas
        																		la primera para guardar las canciones favoritas sin necesidad
        																		de estar almacenadas en una playlist y la segunda serviria como
        																		contenedor de varias playlist's
    																			*/
    
	Player* player=Player_New();
	Playlist* playlist_gral=Playlist_New("lista general");

    //PrintMenuPrincipal(player,playlist_gral);

    do{
    	PrintMenuPrincipal(player,playlist_gral);
        printf("\ncmd > > >: ");
        scanf("%s", &str );
        cmd = str[ 0 ];

        switch( cmd )
        {
        	case 'X': case 'x':
        		assert(!Playlist_IsEmpty(playlist_gral));						//asssert
        		
        		printf("\nElija la cancion que se va a eliminar\n");
            	Playlist_Traverse(playlist_gral,Print_TrackTitle);
            	printf("\ncmd > > >: ");
            	scanf("%d",&opt);
            	
            																	//Coloca al cursor en opt
            	Playlist_Cursor_front(playlist_gral);
            	for(size_t i=0;i<opt;++i){
            		Playlist_Cursor_next(playlist_gral);
            	}
            	Playlist_Cursor_prev(playlist_gral);
            																	/////////////////////////
            	
            	printf("Se elimino la cancion: %s\n",playlist_gral->cursor->datos.title);
            	
            																
            	Player_GralRemove(player,Playlist_GetID(playlist_gral));		//Elimina la cancion de todas las playlists
            	Playlist_Remove(playlist_gral);									//Elimina la cancion de la lista general
            	
        	break;
        	case 'Z': case 'z':; 
        		Track *v2 = Track_New(id);
        		
                Playlist_Insert_back( playlist_gral, v2 ); 
				printf("\nInsertando %s en %s...\n",v2->title,playlist_gral->name);
				
    			Track_Delete( &v2 );

    			id++;															//Id de cada cancion
    			
                //PrintMenuPrincipal(player,playlist_gral);
        	break;
        	case 'C': case 'c': 
				Clear(); 
				//PrintMenuPrincipal(player,playlist_gral);
			break;
            case 'E': case 'e': 
			break;
			/*
            case 'H': case 'h': 												//�Quitar el caso H?
				//PrintMenuPrincipal(player,playlist_gral);
			break;
			*/
            case 'A': case 'a':
                assert(!Playlist_IsEmpty(playlist_gral));						//assert
                
				printf("\nTodas las canciones: \n\n");
                Playlist_Traverse(playlist_gral,Print_TrackTitle);
                
                //PrintMenuPrincipal(player,playlist_gral);
            break;
            case 'N': case 'n':
                printf("\nNombre del Playlist: ");

                char name[MAX];
                
                fflush( stdin );
                gets(name);
                
                Playlist* p1 = Playlist_New( name );
    
                Player_Insert_back(player,p1);
                printf("Insertando la playlist %s... \n",name);
                
                Playlist_Delete(&p1);
                
                //PrintMenuPrincipal(player,playlist_gral);
            break;

            case 'D': case 'd':
                //Funcion eliminar playlist's
                assert(!Player_IsEmpty(player));								//assert
                
                printf("\nElija una playlist\n");           	
            	
            	Player_Traverse(player,Print_PlaylistName);
            	printf("\ncmd > > >: ");
            	scanf("%d",&opt);
            	
            	//Coloca al cursor en opt
            	Player_Cursor_front(player);
            	for(size_t i=0;i<opt;++i){
            		Player_Cursor_next(player);
            	}
            	Player_Cursor_prev(player);
            	//////////////////////////////
            	
            	printf("Se elimino la playlist: %s", player->cursor->datos.name);
            	Player_Remove(player);               

            break;
            case 'R': case 'r':
            	assert(!Player_IsEmpty(player));								//assert
            	
            	printf("\nElija una playlist\n");         	
            	Player_Traverse(player,Print_PlaylistName);
            	printf("\ncmd > > >: ");
            	scanf("%d",&opt);
            	
            	//Coloca el cursor en la posicion opt
            	Player_Cursor_front(player);
            	for(size_t i=0;i<opt;++i){
            		Player_Cursor_next(player);
            	}
            	Player_Cursor_prev(player);
            	/////////////////////////////////////////
            	
                TestMenuPlaylist(player,&player->cursor->datos,playlist_gral);                    
                
				//PrintMenuPrincipal(player,playlist_gral);
            break;
            default:
                printf("Comando inv�lido\n");
                //PrintMenuPrincipal(player,playlist_gral);
            break;


        }


    } while( cmd != 'E' && cmd != 'e');

    																			/* Una vez llegados a este punto es posible que el usuario ya
       																			ya haya elegido salir del programa, por lo tanto deberiamos
      																			devolver la memoria pedida por las primeras dos listas; con la
      																			primera no habria demasiado problema, con la segunda deberia
       																			devolverse la memoria de cada nodo, pero cada nodo es una
       																			playlist independiente y una vez que no existan nodos, devolver
       																			la del objeto en si mismo*/

       Playlist_Delete(&playlist_gral);
       Player_Delete(&player);


}
