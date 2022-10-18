/*Libreria para llamar funciones de entrada y salida de datos*/
#include<iostream>
/*Librer�a para el manejo de archivos*/
#include<fstream>
/*Librer�a para leer dato desde un archivo*/
#include<fstream>
/*Librer�a para leer archivos csv y seperar los datos entre punto y comas*/
#include<sstream>
/*Esta librer�a tiene una funci�n que permite convertir minusculas a mayusculas*/
#include<bits/stdc++.h>
/*Librería para poder usar las funciones de windows*/
#include<windows.h>
using namespace::std;

/*Declaraciones forward*/
void crear_cliente();
void listado_general();/*Muestra los clientes (por consola)*/
void buscar_x_id();/*Busca un cliente por número de ID*/
void buscar_x_ciudad();/*Busca un cliente por ciudad*/
void buscar_x_ciudad_estado();/*Busca un cliente por ciudad y estado de afiliación*/
int getFrecuencia(string);/*Función para comprobar que no se repita el número de ID*/
void modificar();/*Función para modificar los datos de algún cliente*/
void eliminar();/*Función para eliminar un cliente*/
void listado_general_web();/*Función para mostrar una lista de clientes en una página web*/
void menu();

/*Método main*/
main()
{
	/*Llamada a función para mostrar menú*/
	menu();
}

/*Implementación de funciones*/

void crear_cliente(){
	/*Crear objeto archivo*/
	/*Usamos el valor app en la variable ios para añadir contenido a lo que ya existe en el archivo*/
	ofstream archivo("clientes.csv",ios::app);
	/*Si no se crea el archivo, se imprimirá un mensaje de error*/
	if(!archivo){
		cout<<"Error al crear el archivo clientes.csv"<<endl;
	}else{
		/*En caso contrario, se piden los datos al usuario*/
		/*Variables para almacenar los datos del usuario*/
		string ape,nom,ciudad,correo,num_id;
		/*Variable para almacenar el estado de afiliación*/
		int estado;
		cout<<"ingrese el numero de identificacion: ";
		cin>>num_id;
		/*Si no hay ID repetidos, se pedirán los datos al usuario*/
		if(getFrecuencia(num_id)==0){
			/*Limpiar buffer de entrada*/
			fflush(stdin);
			cout<<"Ingrese el apellido: ";
			getline(cin,ape);
			cout<<"Ingrese el nombre: ";
			getline(cin,nom);
			cout<<"Ingrese la ciudad de residencia: ";
			getline(cin,ciudad);
			cout<<"Ingrese el correo: ";
			getline(cin,correo);
			cout<<"Afiliado [1= Esta afiliado, 0= No esta afiliado]: ";
			fflush(stdin);
			cin>>estado;
			/*Se escriben los datos en el archivo, separados por punto y coma*/
			archivo<<num_id<<";"<<ape<<";"<<nom<<";"<<ciudad<<";"<<correo<<";"<<estado<<endl;
			/*Cierre del archivo, para evitar errores*/
			archivo.close();
			cout<<"Se ingreso con exito el cliente"<<endl<<endl;
		}else{
			/*Si ya existe el ID, se imprimirá este aviso*/
			cout<<"El cliente con identificacion "<<num_id<<" ya existe"<<endl;
		}
	}
}
/*Mostrar clientes por consola*/
void listado_general(){
	system("cls");
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo está en modo lectura, esto evitará que se pierdan los datos*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		/*En esta se almacenarán los registros como una sola linea de texto*/
		string registro;
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos en "tokens"*/
		/*Variables para almecenar los datos de los clientes y extraerlos de forma "atómica"*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*Bucle para leer el archivo linea por linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		/*LA función devuelve 0 o False cuando ya no encuentra mas registros en el archivo, eso termina el bucle*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividirá la información por cada campo*/
			stringstream token(registro);
			/*La variable token, tiene todos los registros del archivo almacenados como una cadena
			el parámetro ";" indica que la cadena de texto de debe de separar cuando encuentre un ";", separando
			así los valores individualmente*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			/*Una vez separados los datos, éstos se imprimiran*/
			cout<<num_id<<" "<<ape<<" "<<nom<<" "<<ciudad<<" "<<correo<<" "<<estado<<endl;
		}
		/*Una vez que se hayan terminen de imprimir los datos, se cerrará el archivo*/
		archivo.close();
		/*Se pausará el programa antes de que el usuario pueda elegir otra opción*/
		system("pause");
	}
}

/*Función para buscar algún cliente por ID*/
void buscar_x_id(){
	/*Limpiar la pantalla*/
	system("cls");
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo está en modo lectura, esto evitará que se modifiquen o eliminen
	los datos*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		/*En esta se almacenarán los registros como una sola linea de texto*/
		string registro;
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos en "tokens"*/
		/*Variables para almecenar los datos de los clientes y extraerlos de forma "atómica"*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*variable para buscar el id*/
		string numid_buscar;
		cout<<"ingrese el numero de id a buscar: ";
		cin>>numid_buscar;
		/*Cuando se haga el recorrido del archivo, ésta variable determinará si existe el 
		registro o no*/
		bool existe=false;
		/*Bucle para leer el archivo linea por linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividirá la información por cada campo*/
			stringstream token(registro);
			/*Se usa el método getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			/*Como se están manejando strings, se usará el metodo compare para comparar entre 2 cadenas*/
			/*Si el numero digitado por el usuario coincide con alguno existente en el archivo, se imprimirá
			el resultado con el ID*/
			if(numid_buscar.compare(num_id)==0){
				existe=true;
				cout<<num_id<<" "<<ape<<" "<<nom<<" "<<ciudad<<" "<<correo<<" "<<estado<<endl<<endl;
			}
		}
		archivo.close();
		/*Si se cumple la condición de que no existe el ID, se imprimirá el siguiente mensaje*/
		if(!existe){
			cout<<"No existe el id"<<endl<<endl;
		}
	}
}

/*Función para buscar un cliente por ciudad*/
void buscar_x_ciudad(){
	system("cls");
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo est� en modo lectura*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		/*En esta variable sirve para almacenar el texto del archivo*/
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos*/
		string registro;
		/*Variables para almecenar los datos de los clientes y extraerlos*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*variable para buscar la ciudad*/
		string ciudad_buscar;
		fflush(stdin);
		cout<<"ingrese la ciudad a buscar: ";
		getline(cin,ciudad_buscar);
		/*Cuando se haga el recorrido del archivo, �sta variable determinar� si existe el 
		registro o no*/
		bool existe=false;
		/*Convertir la variable a mayuscula*/
		transform(ciudad_buscar.begin(),ciudad_buscar.end(),
		          ciudad_buscar.begin(),::toupper);
		/*Bucle para leer el archivo linea x linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividir� la informaci�n por cada campo*/
			stringstream token(registro);
			/*Se usa el m�todo getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			transform(ciudad.begin(),ciudad.end(),
		          ciudad.begin(),::toupper);
			if(ciudad_buscar.compare(ciudad)==0){
				existe=true;
				cout<<num_id<<" "<<ape<<" "<<nom<<" "<<ciudad<<" "<<correo<<" "<<estado<<endl<<endl;
			}
		}
		archivo.close();
		if(!existe){
			cout<<"No existe la ciudad en el sistema"<<endl<<endl;
		}
	}
}
void buscar_x_ciudad_estado(){
	system("cls");
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo est� en modo lectura*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		/*En esta variable sirve para almacenar el texto del archivo*/
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos*/
		string registro;
		/*Variables para almecenar los datos de los clientes y extraerlos*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*variable para buscar la ciudad*/
		string ciudad_buscar,estado_buscar;
		fflush(stdin);
		cout<<"ingrese la ciudad a buscar: ";
		getline(cin,ciudad_buscar);
		cout<<"Ingrese el estado a buscar [1=Afiliado 0=No afiliado]: ";
		cin>>estado_buscar;
		/*Cuando se haga el recorrido del archivo, �sta variable determinar� si existe el 
		registro o no*/
		bool existe=false;
		/*Convertir la variable a mayuscula*/
		transform(ciudad_buscar.begin(),ciudad_buscar.end(),
		          ciudad_buscar.begin(),::toupper);
		/*Bucle para leer el archivo linea x linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividir� la informaci�n por cada campo*/
			stringstream token(registro);
			/*Se usa el m�todo getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			transform(ciudad.begin(),ciudad.end(),
		              ciudad.begin(),::toupper);
			if((ciudad_buscar.compare(ciudad)==0)&&
			    (estado_buscar.compare(estado)==0)){
				existe=true;
				cout<<num_id<<" "<<ape<<" "<<nom<<" "<<ciudad<<" "<<correo<<" "<<estado<<endl<<endl;
			}
		}
		archivo.close();
		if(!existe){
			cout<<"No existen clientes en esa ciudad con estado afiliado "<<endl<<endl;
		}
	}
}

int getFrecuencia(string num_id_buscar){
	int cont=0;
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		/*En esta variable sirve para almacenar el texto del archivo*/
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos*/
		string registro;
		/*Variables para almecenar los datos de los clientes y extraerlos*/
		string num_id;
		/*Bucle para leer el archivo linea x linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividir� la informaci�n por cada campo*/
			stringstream token(registro);
			/*Se usa el m�todo getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			if(num_id_buscar.compare(num_id)==0)
				cont=1;
			
		}
		return cont;
		archivo.close();
	}
}

void modificar(){
	system("cls");
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo est� en modo lectura*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		vector<string> all_registros;
		/*En esta variable sirve para almacenar el texto del archivo*/
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos*/
		string registro;
		/*Variables para almecenar los datos de los clientes y extraerlos*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*variable para buscar el id*/
		string numid_buscar;
		cout<<"ingrese el numero de id a buscar: ";
		cin>>numid_buscar;
		/*Cuando se haga el recorrido del archivo, �sta variable determinar� si existe el 
		registro o no*/
		bool existe=false,modifico=false;
		int opc=0;
		/*Bucle para leer el archivo linea x linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividir� la informaci�n por cada campo*/
			stringstream token(registro);
			/*Se usa el m�todo getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			if(numid_buscar.compare(num_id)==0){
				existe=true;
				cout<<"Datos actuales del cliente:"<<endl;
				cout<<"Numero de ID: "<<num_id<<endl;
				cout<<"1.Apellido: "<<ape<<endl;
				cout<<"2.Nombre: "<<nom<<endl;
				cout<<"3.Ciudad: "<<ciudad<<endl;
				cout<<"4.Correo: "<<correo<<endl;
				cout<<"5.Estado: "<<estado<<endl;
				cout<<"0.Ninguno "<<endl<<endl;
				do{
					cout<<"Seleccione el campo a modificar: "<<endl;
					cin>>opc;
				}while(opc<0||opc>5);
				fflush(stdin);
				switch(opc){
					case 1:
						modifico=true;
						cout<<"Ingrese el nuevo apellido: "<<endl;
						getline(cin,ape);
						break;
					case 2:
						modifico=true;
						cout<<"Ingrese el nuevo nombre: "<<endl;
						getline(cin,nom);
						break;
					case 3:
						modifico=true;
						cout<<"Ingrese la nueva ciudad: "<<endl;
						getline(cin,ciudad);
						break;
					case 4:
						modifico=true;
						cout<<"Ingrese el nuevo correo: "<<endl;
						getline(cin,correo);
						break;
					case 5:
						modifico=true;
						cout<<"Ingrese el nuevo estado: "<<endl;
						getline(cin,estado);
						break;
				}
				all_registros.push_back(num_id+";"+ape+";"+nom+";"+ciudad+";"+correo+";"+estado);
			}else{
				all_registros.push_back(registro);
			}
		}
		if(existe){
			if(modifico){
				/*Sobre escribe el documento anterior*/
				ofstream nuevo("clientes.csv");
				for(int i=0;i<int(all_registros.size());i++){
					/*Almacenar el i-�simo registro en el nuevo archivo "nuevo"*/
					nuevo<<all_registros[i]<<endl;
				}
				nuevo.close();
				cout<<"Se modifico el cliente"<<endl<<endl;
			}
		}else{
			cout<<"No existe el id"<<endl<<endl;
		}
	}archivo.close();
}

void eliminar(){
	system("cls");
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo est� en modo lectura*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		vector<string> registros_no_eliminar;
		/*En esta variable sirve para almacenar el texto del archivo*/
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos*/
		string registro;
		/*Variables para almecenar los datos de los clientes y extraerlos*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*variable para buscar el id*/
		string numid_buscar;
		cout<<"ingrese el numero de id a eliminar: ";
		cin>>numid_buscar;
		/*Cuando se haga el recorrido del archivo, �sta variable determinar� si existe el 
		registro o no*/
		bool existe=false;
		/*Bucle para leer el archivo linea x linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividir� la informaci�n por cada campo*/
			stringstream token(registro);
			/*Se usa el m�todo getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			if(numid_buscar.compare(num_id)==0)
				existe=true;
			else
				registros_no_eliminar.push_back(registro);
		}
		if(existe){
			/*Sobre escribe el documento anterior*/
			ofstream nuevo("clientes.csv");
			for(int i=0;i<int(registros_no_eliminar.size());i++){
			/*Almacenar el i-�simo registro en el nuevo archivo "nuevo"*/
				nuevo<<registros_no_eliminar[i]<<endl;
			}
			nuevo.close();
			cout<<"Se elimino el cliente"<<endl<<endl;
		}else{
			cout<<"No existe el id"<<endl<<endl;
		}
	}archivo.close();
}
/*Método para mostrar resultados en la web*/
void listado_general_web(){
	/*Crear objeto ifstream para poder leer el archivo*/
	/*'ios::in' sirve para indicar que el archivo est� en modo lectura*/
	ifstream archivo("clientes.csv",ios::in);
	if(!archivo){
		cout<<"Error al tratar de abrir el archivo 'clientes.csv'"<<endl;
	}else{
		ofstream web("Listado_general_web.html");
		ofstream estilos("estilos.css");
		web<<"<html><head><title>Listado general de clientes</title><link rel=\"stylesheet\" href=\"estilos.css\"></head><body>"<<endl;
		estilos<<"table{width:80%; border-collapse:collapse;}"<<endl;
		estilos<<"table,th,td{border:1px solid;font-family:Tahoma;text-align:center}"<<endl;
		estilos<<"th{text-align:center;font-weight:bold;font-size:20px;}"<<endl;
		estilos<<"tr.afiliado{background-color:rgb(191,255,207);}"<<endl;
		estilos<<"tr.no_afiliado{background-color:rgb(255,144,86);}"<<endl;
		web<<"<div align=center>"<<endl;
		web<<"<h2>Listado general de clientes</h2><br>"<<endl;
		web<<"<table>"<<endl;
		web<<"<tr>"<<endl;
			web<<"<th>Numero de ID</th>"<<endl;
			web<<"<th>Apellido</th>"<<endl;
			web<<"<th>Nombre</th>"<<endl;
			web<<"<th>Ciudad</th>"<<endl;
			web<<"<th>Correo</th>"<<endl;
			web<<"<th>Estado</th>"<<endl;
		web<<"</tr>"<<endl;
		/*En esta variable sirve para almacenar el texto del archivo*/
		/*Todos los datos de los clientes se almacenan como una sola cadena de texto, y hay que 
		separarlos*/
		string registro;
		/*Variables para almecenar los datos de los clientes y extraerlos*/
		string num_id,ape,nom,ciudad,correo,estado;
		/*Bucle para leer el archivo linea x linea mediante el metodo getline*/
		/*getline(obj_archivo, string registro)*/
		while(getline(archivo,registro)){
			/*Convertimos el registro a un stream por medio de la clse stringstream*/
			/*Por medio de esta clase, se dividir� la informaci�n por cada campo*/
			stringstream token(registro);
			/*Se usa el m�todo getline, especificando el caracter delimitador (;) para 
			extraer cada campo (token) del string registro*/
			getline(token,num_id,';');
			getline(token,ape,';');
			getline(token,nom,';');
			getline(token,ciudad,';');
			getline(token,correo,';');
			getline(token,estado,';');
			/*Una vez separados los datos, �stos se imprimiran*/
			if(estado.compare("1")==0)
				web<<"<tr class=\"afiliado\">"<<endl;
			else
				web<<"<tr class=\"no_afiliado\">"<<endl;
				web<<"<td>"<<num_id<<"</td>"<<endl;
				web<<"<td>"<<ape<<"</td>"<<endl;
				web<<"<td>"<<nom<<"</td>"<<endl;
				web<<"<td>"<<ciudad<<"</td>"<<endl;
				web<<"<td>"<<correo<<"</td>"<<endl;
				if(estado.compare("1")==0)
					web<<"<td>Afiliado</td>"<<endl;
				else
					web<<"<td>No Afiliado</td>"<<endl;
			web<<"</tr>"<<endl;
		}
		archivo.close();
		web<<"</table></body></div></html>"<<endl;
		web.close();
		cout<<"Se creo con exito la pagina web"<<endl;
		cout<<"Desea visualizar la pagina web\? [1->Si 0->No]: "<<endl;
		int resp;
		cin>>resp;
		if(resp==1)
			ShellExecute(GetDesktopWindow(),"open","listado_general_web.html",NULL,NULL,SW_SHOWNORMAL);
		else
			cout<<"perra"<<endl;
		system("pause");
	}
}

/*Método para menú*/
void menu(){
	int opc;/*Variable para controlar la opción del usuario*/
	/*Este bucle se ejecutará mientras el usuario no digite 0*/
	do{
		cout<<"Menu de opciones"<<endl;
		cout<<"1. Crear cliente"<<endl;
		cout<<"2. Listado general de clientes"<<endl;
		cout<<"3. Buscar por ID"<<endl;
		cout<<"4. Buscar por ciudad"<<endl;
		cout<<"5. Buscar por ciudad y estado de afiliacion"<<endl;
		cout<<"6. Modificar cliente por ID"<<endl;
		cout<<"7. Eliminar cliente (por ID)"<<endl;
		cout<<"8. Listado general de clientes (web)"<<endl;
		cout<<"0. Salir"<<endl;
		cout<<"Seleccione una opcion: "<<endl;
		cin>>opc;
		/*switch-case para llamar a funciones del programa*/
		switch(opc){
			case 1: 
				crear_cliente();
				break;
		    case 2:
		    	listado_general();
		    	break;
		    case 3:
		    	buscar_x_id();
		    	break;
		    case 4:
		    	buscar_x_ciudad();
		    	break;
		    case 5:
		    	buscar_x_ciudad_estado();
		    	break;
		    case 6:
		    	modificar();
		    	break;
		    case 7:
		    	eliminar();
		    	break;
			case 8:
		    	listado_general_web();
		    	break;
			case 0:
				cout<<"Adios";
				break;
			default:
				cout<<"Opcion incorrecta"<<endl<<endl;
		}
	}while(opc!=0);
}
