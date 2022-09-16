//Formulas Obtidas em: http://efisica.if.usp.br/mecanica/universitario/incertezas/formulas/
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <iostream>
# include <string.h>

#define PI 3.1415926535897932
#define E  2.7182818284590452

using namespace std;
typedef struct grandeza {
double valor;
double incert;
}grandeza;

double abs(double a){
	return a >= 0 ? a : -a;
}

grandeza pot(grandeza a, grandeza b){
	grandeza c;
	c.valor = pow(a.valor,b.valor);
	c.incert = abs(c.valor*sqrt(b.incert*b.incert*log10(a.valor)*log10(a.valor)+pow(b.valor*a.incert/a.valor,2)));
	return c;
}
grandeza operator+(grandeza a, grandeza b){
	grandeza c;
	c.valor = a.valor + b.valor;
	c.incert = sqrt(a.incert*a.incert + b.incert*b.incert);
	return c;
}

grandeza operator-(grandeza a, grandeza b){
	grandeza c;
	c.valor = a.valor - b.valor;
	c.incert = sqrt(a.incert*a.incert + b.incert*b.incert);
	return c;
}

grandeza operator*(grandeza a, grandeza b){
	grandeza c;
	c.valor = a.valor * b.valor;
	c.incert = abs(c.valor*sqrt(pow(a.incert/a.valor, 2) + pow(b.incert/b.valor, 2)));
	return c;
}

grandeza operator/(grandeza a, grandeza b){
	grandeza c;
	c.valor = a.valor / b.valor;
	c.incert = abs(c.valor*sqrt(pow(a.incert/a.valor, 2) + pow(b.incert/b.valor, 2)));
	return c;
}

grandeza cos (grandeza a){
	grandeza b;
	b.valor = cos(a.valor);
	b.incert = abs(sin(a.valor)*a.incert);
	return b;
}

grandeza sin (grandeza a){
	grandeza b;
	b.valor = sin(a.valor);
	b.incert = abs(cos(a.valor)*a.incert);
	return b;
}

grandeza tan (grandeza a){
	grandeza b, c;
	b.valor = sin(a.valor);
	b.incert = abs(cos(a.valor)*a.incert);
	c.valor = cos(a.valor);
	c.incert = abs(sin(a.valor)*a.incert);
	a = b/c;
	return a;
}

grandeza ln (grandeza a){
	grandeza b;
	b.valor = log(a.valor);
	b.incert = a.incert/a.valor;
	return b;
}

grandeza log (grandeza a){
	grandeza b, c;
	b.valor = log(a.valor);
	b.incert = a.incert/a.valor;
	c.valor = log(10);
	c.incert = 0;
	a = b/c;
	return a;
}

grandeza convertString(char* exp){
	int i, ponto,fim = 0, mark, count = 0, sinal;
	bool existePonto;
	double t;
	grandeza novo[20];
	while(exp[i] != '\0'){
		if(exp[i] == ' ' )
			i++;
		else if(exp[i] == '+' ){
			novo[count - 2] = novo[count - 2] + novo[count - 1];
			count--;
			i++;
		}
		else if(exp[i] == '-' ){
			novo[count - 2] = novo[count - 2] - novo[count - 1];
			count--;
			i++;
		}
		else if(exp[i] == '*' ){
			novo[count - 2] = novo[count - 2] * novo[count - 1];
			count--;
			i++;
		}
		else if(exp[i] == '/' ){
			novo[count - 2] = novo[count - 2] / novo[count - 1];
			count--;
			i++;
		}
		else if(exp[i] == '^' ){
			novo[count - 2] = pot(novo[count - 2] , novo[count - 1]);
			count--;
			i++;
		}
		else if(exp[i] == 'c' ){
			novo[count - 1] = cos(novo[count - 1]);
			i++;
		}
		else if(exp[i] == 's' ){
			novo[count - 1] = sin(novo[count - 1]);
			i++;
		}
		else if(exp[i] == 't' ){
			novo[count - 1] = tan(novo[count - 1]);
			i++;
		}
		else if(exp[i] == 'l' ){
			novo[count - 1] = ln(novo[count - 1]);
			i++;
		}
		else if(exp[i] == 'k' ){
			novo[count - 1] = log(novo[count - 1]);
			i++;
		}
		else if (exp[i]>='0' and exp[i]<='9' or exp[i]=='!'){
			sinal = 1;
			if(exp[i] == '!'){
				sinal = -1;
				i++;
			}
			mark = i;
			existePonto = false;
			while((exp[i]>='0' and exp[i]<='9') or exp[i]=='.'){
				if(exp[i] == '.'){
					ponto = i;
					existePonto = true;
				}
				i++;
			}
			fim = i;
			i--;
			t=0;
			if(not existePonto)
				ponto = i;
			for(i; i>= mark; i--){
				if(exp[i]== '.'){
					i--; ponto--;
				}
				t = t +((exp[i]-'0')*pow(10,ponto-i));
			}
			novo[count].valor = t*sinal;
			i = fim;
			if(exp[i] == '['){
				mark = i;
				existePonto = false;
				while(exp[i] != ']'){
					if(exp[i] == '.'){
						ponto = i;
						existePonto = true;
					}
					i++;
				}
				fim = i+1;
				i--;
				t=0;
				if(not existePonto)
					ponto = i;
				for(i; i> mark ; i--){
					if(exp[i]== '.'){
						i--; ponto--;
					}
					t = t +((exp[i]-'0')*pow(10,ponto-i));
				}
			}
			else
				t = 0;
			novo[count++].incert = t;
			i=fim;
		}
		else if(exp[i] == 'p' && exp[i+1] == 'i'){
			novo[count].valor = PI;
			novo[count++].incert = 0;
			i = i+2;	
		}
		else if(exp[i] == 'e'){
			novo[count].valor = E;
			novo[count++].incert = 0;
			i++;
		}
		else{
			exp[i] = '\0';
		}
	}
	if(count == 1)
		cout << "Este Resultado provavelmente esta correto" << endl;
	else
		cout << "Formula mal formada" << endl;
	return novo[0];
}

char *infix2posfix(char *inf)
{
	bool falsoMenos;
 	int n = strlen(inf);
 	char *posf; // expressão pósfixa
 	posf = (char*)malloc((n + 1) * sizeof(char));
 	int i; // percorre infixa
 	int j; // percorre posfixa
 	char *s; // pilha
 	int t; // topo da pilha
 	// inicializa a pilha
 	s = (char*)malloc(n * sizeof(char));
 	t = 0;
 	for (i = j = 0; inf[i] != '\0'; i++){
 		switch (inf[i]){
 			char x; // auxiliar para item do topo da pilha
			case '(':
				falsoMenos = true;
				s[t++] = inf[i]; // empilha
 				break;
 			case ')':
 				falsoMenos = false;
 				x = s[--t]; // desempilha
 				while (x != '('){
 					posf[j++] = x;
 					x = s[--t]; // desempilha
				}
 				break;
 			case '-':
 				if(falsoMenos){
 					inf[i] = '!';
 					i--;
 					break;
				 }
 			case '+':
 			// desempilha enquanto pilha não for vazia e não encontrar '('
 				falsoMenos  = true;
 				posf[j++] = ' ';
 				while (t > 0 && s[t - 1] != '('){
 					posf[j++] = s[--t]; // desempilha
 				}
 				s[t++] = inf[i]; // empilha
 				break;
 			case '*':
 			case '/':
			 // desempilha enquanto não encontrar início do bloco ou operador de menor precedência na pilha
			 	falsoMenos = true;
			 	posf[j++] = ' ';
 				while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-'){
 					posf[j++] = s[--t]; // desempilha
 				}
 				s[t++] = inf[i];
 				break;
 			case '^':
			 // desempilha enquanto não encontrar início do bloco ou operador de menor precedência na pilha
			 	falsoMenos = true;
			 	posf[j++] = ' ';
 				while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-' && x != '*' && x != '/'){
 					posf[j++] = s[--t]; // desempilha
 				}
 				s[t++] = inf[i];
 				break;
 			case 's':
 				if((inf [i+1] == 'e' or inf[i+1] == 'i') and inf[i+2] == 'n'){
 					inf [i+1] = ' ';
 					inf [i+2] = ' ';
 					
 					falsoMenos = true;
				 	posf[j++] = ' ';
 					while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-' && x != '*' && x != '/' && x != '^'){
 						posf[j++] = s[--t]; // desempilha
 					}
 					s[t++] = inf[i];
 					break;
				}
				else{
					cout << "Operacao Invalida detectada!" << endl;
					break;
				}

 			case 'c':
 				if(inf [i+1] == 'o'  and inf[i+2] == 's'){
 					inf [i+1] = ' ';
 					inf [i+2] = ' ';
 					
 					falsoMenos = true;
			 		posf[j++] = ' ';
 					while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-' && x != '*' && x != '/' && x != '^'){
 						posf[j++] = s[--t]; // desempilha
 					}
 					s[t++] = inf[i];
 					break;
				}
				else{
					cout << "Operacao Invalida detectada!" << endl;
					break;
				}
			case 't':
 				if(inf [i+1] == 'a'  and inf[i+2] == 'n'){
 					inf [i+1] = ' ';
 					inf [i+2] = ' ';
 					
 					falsoMenos = true;
			 		posf[j++] = ' ';
 					while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-' && x != '*' && x != '/' && x != '^'){
 						posf[j++] = s[--t]; // desempilha
 					}
 					s[t++] = inf[i];
 					break;
				}
				else{
					cout << "Operacao Invalida detectada!" << endl;
					break;
				}
			case 'l':
 				if(inf [i+1] == 'n' ){
 					inf [i+1] = ' ';
 					
 					falsoMenos = true;
			 		posf[j++] = ' ';
 					while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-' && x != '*' && x != '/' && x != '^'){
 						posf[j++] = s[--t]; // desempilha
 					}
 					s[t++] = inf[i];
 					break;
				}
				else if(inf [i+1] == 'o'  and inf[i+2] == 'g'){
					inf [ i ] = 'k';
 					inf [i+1] = ' ';
 					inf [i+2] = ' ';
 					
 					falsoMenos = true;
			 		posf[j++] = ' ';
 					while (t > 0 && (x = s[t - 1]) != '(' && x != '+' && x != '-' && x != '*' && x != '/' && x != '^'){
 						posf[j++] = s[--t]; // desempilha
 					}
 					s[t++] = inf[i];
 					break;
				}
				else{
					cout << "Operacao Invalida detectada!" << endl;
					break;
				}

 			default:
 				if (inf[i] != ' '){
 					posf[j++] = inf[i];
 					falsoMenos = false;
 				}
 					
 		}
 	}
 	// desempilha o que sobrou na pilha
 	while (t > 0)
 		posf[j++] = s[--t];
 	posf[j] = '\0';
	free(s);
 	return posf;
}

int main(){
	char exp[100];
	char * exp2;
	grandeza v;
	if (false){
		labe:
		getchar();
	}
	cout << "Digite a Formula:"<< endl;
	gets(exp);
	exp2 = infix2posfix(exp);
	v = convertString(exp2);
	cout << "Result:" << v.valor << "[" <<v.incert<< "]" << endl;
	cout << endl << "Deseja Repetir? S ou N" << endl;
	cin >> exp;
	cout << endl;
	if(exp[0] == 's' or exp[0] == 'S')
		goto labe;
}
