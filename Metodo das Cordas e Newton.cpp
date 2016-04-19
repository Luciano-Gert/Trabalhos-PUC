/* Trabalho de Calculo Numerico
	Luciano Almeida Gertrudes
	478523
*/

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iomanip>
#include <cstdlib>

using namespace std;


// Função fx definida pelo usuario (A mesma que a do caderno)
float fx (float x){
	float result;
	result = exp(x) - 8;
	return result;
}

// Derivada primeira da função fx
float derivate1 (float x){
	float result;
	result = exp(x);
	return result;
}

// Derivada segunda da função fx
float derivate2 (float x){
	float result;
	result = exp(x);
	return result;
}

// Formula para testar se existe raiz no intervalo inserido
bool IntervalTest(float a, float b){
	if ((fx(a)*fx(b)) > 0)
		return false;
	else return true;
}

// Testando se os sinais das derivadas são constantes
void testderivate(float a, float b){

	int z;
	float aux, result;
	aux = a + (a - b) / 100; // Dividindo a bagaça em 100 partes

	// Testando a derivada primeira
	while (aux < b){
		result = derivate1(aux);
		if ( (derivate1(a) * result ) < 0){
			cout << "\nA derivada primeira da função mudou de sinal. Deseja continuar mesmo assim ? [1 Sim - 2 Nao] ";
			cin >> z;
			if (z == 1){
				break;
			};
		};
		aux = aux + (b - a) / 100;
	};
	cout << "\n  Teste derivada primeira: Ok";

	//Testando a derivada segunda
	while (aux < b){
		result = derivate2(aux);
		if ( (derivate2(a) * result) < 0){
			cout << "\nA derivada segunda da função mudou de sinal. Deseja continuar mesmo assim ? [1 Sim - 2 Nao] ";
			cin >> z;
			if (z == 1){
				break;
			};
		};
		aux = aux + (b - a) / 100;
	};

	cout << "\n  Teste derivada segunda: Ok";
}

// Definindo entre A ou B, quem será o C e o X0 - Para o metodo das Cordas
void fc(float a, float b, float *c, float *x0){
	float resultA, resultB;
	resultA = fx(a)*derivate2(a);
	resultB = fx(b)*derivate2(b);
	if (resultA > 0){
		*c = a;
		*x0 = b;
	} else {
		*c = b;
		*x0 = a;
	};
}

// Formula do metodo das Cordas
float cordas(float xn, float c){
	float result;
	result = xn - (fx(xn) / (fx(xn) - fx(c))) * (xn - c);
	return result;
}

void fxo(float a, float b, float *x02){
	float resultA, resultB;
	resultA = fx(a)*derivate2(a);
	resultB = fx(b)*derivate2(b);
	if (resultA > 0)
		*x02 = a;
	else
		*x02 = b;
}

// Formula do metodo de Newton
float newton(float xn){
	float result;
	result = xn - (fx(xn) / derivate1(xn));
	return result;
}

// Formula da tolerancia
float tolerancia(float x1, float x0){
	float result;
	result = (x1 - x0) / x0;
	if (result < 0){
		return (result * (-1));
	}
	else {
		return result;
	};
}


int _tmain(int argc, _TCHAR* argv[])
{
	float a, b, c, x0, x02, xi, fxi, e, aux;
	int ite, metodo;

	// Fixando o valor de casas decimais do Cout
	cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	cout.precision(5);


	cout << "\n\nDigite o valor do intervalo [a,b]: ";
	cin >> a;
	cin >> b;
	if (IntervalTest(a, b) == 0){
		cout << "\n\n Nao ha raizes no intervalo fornecido!";
		return 0;
	};
	cout << "\nDigite o numero de iteracoes desejadas: ";
	cin >> ite;
	cout << "\n Valor de A: " << a;
	cout << "\n Valor de B: " << b;
	cout << "\n Resultado da funcao com o valor A: " << fx(a);
	cout << "\n Resultado da funcao com o valor B: " << fx(b);
	testderivate(a, b);
	getchar();
	getchar();
	getchar();

	system("CLS");

	cout << "\n\n\n Qual metodo deseja usar ? ";
	cout << "\n Newton [1]";
	cout << "\n Cordas [2] \n ";
	cin >> metodo;
	getchar();

	system("CLS");

	switch (metodo)
	{

	case 1:
		cout << " --- Metodo de Newton --- ";
		fxo(a, b, &x02);
		cout << "\n\n X0 ira assumir o valor de: " << x02;

		for (int i = 0; i < ite; i++){
			if (i == 0){
				cout << "\n\n |  i   |      Xi           |      F(Xi)         |      E            ";
				cout << "\n |  0   |     " << x02 << "       |      " << fx(x02) << "      |      -            ";
			}
			else {
				aux = x02;
				xi = newton(aux);
				fxi = fx(xi);
				e = tolerancia(xi, aux);
				cout << "\n |  " << i << "   |     " << xi << "       |       " << fx(xi) << "      |      " << e << "      ";
				x02 = xi;
			};
		};
		break;

	case 2:
		cout << " --- Metodo das Cordas --- ";
		fc(a, b, &c, &x0);
		cout << "\n\n C ira assumir o valor de: " << c << "\n e X0 ira assumir o valor de: " << x0;

		for (int i = 0; i < ite; i++){
			if (i == 0){
				cout << "\n\n |  i   |      Xi           |      F(Xi)         |      E            ";
				cout << "\n |  0   |      " << x0 << "      |      " << fx(x0) << "      |      -            ";
			}
			else {
				aux = x0;
				xi = cordas(aux, c);
				fxi = fx(xi);
				e = tolerancia(xi, aux);
				cout << "\n |  " << i << "   |      " << xi << "      |      " << fx(xi) << "      |      " << e << "      ";
				x0 = xi;
			};
		};
		break;

	default: cout << "Metodo não escolhido!";
			break;
	}

	getchar();
	getchar();
	getchar();
	getchar();
	return 0;
}
