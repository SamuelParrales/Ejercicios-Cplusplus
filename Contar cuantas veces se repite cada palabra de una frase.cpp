/*
Escuela Superior Politécnica de Chimborazo
	By: Samuel Parrales
	Compilador de C++: GCC 4.9.2 
*/

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctype.h>
using namespace std;

struct stringHash
{
	string texto;
	int cont=0;	
};

//***************************************************************prototipos de funciones

std::vector<string> split(char *cad);   //función que devuelve las palabras de un texto
std::vector<string> eliminarCrtsEs(std::vector<string> palabras);
std::vector<stringHash> crearVctrHash(std::vector<string> palabras);
int hashModulo(string cadena, int longitud);
int pruebaLineal(std::vector<stringHash> &palabras,int longitud, stringHash palabra, bool guardar);//Evita las colisiones
//**************************************************************función principal



main()
{
	char cadena[] = "objetivo? ejercicio... de lectoescritura esta dirigido a ninos de tres años y pretende iniciar al nino en la escritura. Esta actividad esta dirigida a que los ninos reconozcan palabras iguales ficha esta elaborada por profesores de primaria e infantil. El objetivo del ejercicio es que los ninos puedan identificar palabras iguales y asociarlas.";
	int colisiones=0;
	int con=0;
	std::vector<string> palabras, prueba;	
	std::vector<stringHash> vectorHash;
	
	palabras = split(cadena); //Separa las palabras en un vector;
	palabras = eliminarCrtsEs(palabras); //de cada palabra elimina caracteres ? ¿ . , 
	vectorHash = crearVctrHash(palabras); // VectorHash 
	
	
	int suma=0;
	for(int i=0;i<vectorHash.size();i++)
	{
		cout<<vectorHash[i].texto<<"||"<<vectorHash[i].cont<<endl;
		suma+=vectorHash[i].cont;
	}
	cout<<"elementos: "<<suma;
}

//************************************************************** concepto de funciones
std::vector<string> split(char *cad)   //devuelve las palabras 
{
	std::vector<string> palabras;
	string token;
    	for(int i=0;cad[i]!='\0';i++)
    	{
    		if(cad[i]==' ')
    		{
    			if((i!=0)&&(cad[i-1]==' '))
    				continue;
    			palabras.push_back(token.c_str());   
				token.clear();		
    			continue;
			}
			token.push_back(cad[i]);    
		}
		palabras.push_back(token.c_str());
	return palabras;
}

std::vector<string> eliminarCrtsEs(std::vector<string> palabras)
{

	for(int i=0;i<palabras.size();i++)
	{

		string token = palabras[i];	
		for(int j=0;j<token.length();j++)
		{
			if(token[j]=='.')

			
			if(token[j]=='?'||token[j]=='.'||token[j]==' '||token[j]==','||token[j]=='¿')
				{
					token.replace(j,j,"");
			
				}

		}
		palabras[i]=token;
	}
	return palabras;
}

std::vector<stringHash> crearVctrHash(std::vector<string> palabras)
{
	std::vector<stringHash> vectorHash;
	vectorHash.resize(palabras.size());	
	for(int i=0;i<palabras.size();i++)
	{
		stringHash palabra;
		palabra.texto = palabras[i];
		pruebaLineal(vectorHash, palabras.size(),palabra, true);	
	}
	return vectorHash;
}



unsigned long long obtenerClave(string cadena)
{
	unsigned long long resultado=0;
	for(int i=0;i<cadena.length();i=i+2)
	{
		resultado*=10;
		resultado+=toupper(cadena[i])/10;
	}	
	return resultado;
}

////********Funciones hash
int hashModulo(string cadena, int longitud)
{
	unsigned long long clave = obtenerClave(cadena);
	return clave%longitud;	
}

//***********Colisiones

int pruebaLineal(std::vector<stringHash> &palabras,int longitud, stringHash palabra, bool guardar)
{
	int colisiones=0; //para contar el numero de colisiones
	int clave = hashModulo(palabra.texto, longitud);

	if(guardar)
	{
		int i=clave;
	
		while(true)				//Se busca una nueva posicion para la clave
		{
			if(i>=palabras.size())
				i=0;
			
			if(palabras[i].texto=="")			//Si no hay nada guardado en la posicion de la clave se guarda la palabra
			{	
				palabras[i].texto=palabra.texto;
		
				if(palabra.cont!=0)
					palabras[i].cont = palabra.cont;
				else
					palabras[i].cont=1;
				break;
			}			
			if(palabras[i].texto==palabra.texto)
			{
				palabras[i].cont++;
				
				stringHash ultimaPalabra = palabras[palabras.size()-1];
				palabras.pop_back();
				
				if(ultimaPalabra.texto!="")
				{
					pruebaLineal(palabras,longitud,ultimaPalabra, true);	
				}	
				break;
			}
			colisiones++;
			i++;
		}
	}
	return colisiones;
}
	
