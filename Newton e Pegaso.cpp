#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

void Cabecalho() {
	cout << "\t++=====================================++";
	cout << "\n\t||   1° Trabalho de Cálculo Numérico   ||";
	cout << "\n\t||     Luciano Almeida Gertrudes       ||";
	cout << "\n\t||     Engenharia de Computação        ||";
	cout << "\n\t||                                     ||";
	cout << "\n\t||         Pegaso e Newton             ||";
	cout << "\n\t++=====================================++\n\n";
}

// Função fx definida pelo usuario (A mesma que a do caderno)
float fx(float x) {
	float result;
	result = pow(x,4)-4*pow(x,2)+3;
	return result;
}

// Derivada primeira da função fx
float derivate1(float x) {
	float result;
	result = 4*pow(x,3)-8*x;
	return result;
}

// Derivada segunda da função fx
float derivate2(float x) {
	float result;
	result = 12*pow(x,2)-8;
	return result;
}

// Formula para testar se existe raiz no intervalo inserido
bool IntervalTest(float a, float b) {
	if ((fx(a)*fx(b)) > 0)
		return false;
	else return true;
}

// Testando se os sinais das derivadas são constantes
int testderivate(float a, float b) {

	int z = 0;
	float aux, result;
	aux = a + (a - b) / 100; // Dividindo o intervalo em 100 partes

    // Testando a derivada primeira
	while (aux < b) {
		result = derivate1(aux);
		if ((derivate1(a) * result) < 0) {
			cout << "\nA derivada primeira da função mudou de sinal. Deseja continuar mesmo assim ? [1 Sim - 2 Não]: ";
			cin >> z;
			if (z == 2) {
				return 0;
			};
		};
		aux = aux + (b - a) / 100;
	};

	if (z != 2)
		cout << "\n  Teste derivada primeira: Ok";

	//Testando a derivada segunda
	while (aux < b) {
		result = derivate2(aux);
		if ((derivate2(a) * result) < 0) {
			cout << "\nA derivada segunda da função mudou de sinal. Deseja continuar mesmo assim ? [1 Sim - 2 Não]: ";
			cin >> z;
			if (z == 2) {
				return 0;
			};
		};
		aux = aux + (b - a) / 100;
	};

	if (z != 2)
		cout << "\n  Teste derivada segunda: Ok\n";
}


// Formula do metodo de pegaso
float pegaso(float x0, float x1, float fx0, float fx1) {
	float result;
	result = x1 - ((fx1 * (x1 - x0)) / (fx1 - fx0));
	return result;
}

//Fator de Redução para pegaso
float fredut(float fx0, float fx1, float fx2) {
	float result;
	result = fx0*(fx1 / (fx1 + fx2));
	return result;
}

//Determinar novo X0 pra pegaso
float xo(float x0, float x1, float fx0, float fx1, float fx2) {
	if ((fx0 <= 0) && (fx2 <= 0) || (fx0 >= 0) && (fx2 >= 0))
		return x1;
	else
		return x0;
}

// Definindo entre A ou B, quem será o X0 - Para o metodo de Newton
void fxo(float a, float b, float *x02) {
	float resultA, resultB;
	resultA = fx(a)*derivate2(a);
	resultB = fx(b)*derivate2(b);
	if (resultA > 0)
		*x02 = a;
	else
		*x02 = b;
}

// Formula do metodo de Newton
float newton(float xn) {
	float result;
	result = xn - (fx(xn) / derivate1(xn));
	return result;
}

// Formula da tolerancia
float tolerancia(float x1, float x0) {
	float result;
	result = (x1 - x0) / x0;
	if (result < 0) {
		return (result * (-1));
	}
	else {
		return result;
	};
}


int _tmain(int argc, _TCHAR* argv[])
{
	float a, b, x0 = 0, x02, x1 = 0, x2 = 0, xi, fxi, e, aux, fx0, fx1, fx2, tole;
	int ite, metodo, menu;
	menu = 1;

	// Acentuação
	setlocale(LC_ALL, "Portuguese");

	// Fixando o valor de casas decimais do Cout
	cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	cout.precision(5);

	do {
		Cabecalho();

		cout << "\n\nDigite o valor do intervalo [a,b]: ";
		cin >> a;
		cin >> b;
		if (IntervalTest(a, b) == 0) {
			cout << "\n\n --- Não há raizes no intervalo fornecido! --- \n\n";
			system("pause");
			return 0;
		};
		cout << "\nDigite o número de iterações desejadas: ";
		cin >> ite;
		cout << "\nDigite a tolerância, (Exp: 0.001): ";
		cin >> tole;

		system("pause");
		system("CLS");

		cout << "\n Valor de A: " << a;
		cout << "\n Valor de B: " << b;
		cout << "\n Resultado da função com o valor A: " << fx(a);
		cout << "\n Resultado da função com o valor B: " << fx(b) <<"\n\n";
		system("pause");
		system("CLS");

		cout << "\n\n\nQual método deseja usar ? ";
		cout << "\nNewton [1]";
		cout << "\nPegaso [2] \n ";
		cin >> metodo;

		if (testderivate(a, b) == 0)
			metodo = 3;



		system("pause");
		system("CLS");

		switch (metodo)
		{

		case 1:
			cout << " --- Método de Newton --- ";
			fxo(a, b, &x02);
			cout << "\n\n X0 irá assumir o valor de: " << x02;

			for (int i = 0; i < ite; i++) {
				if (i == 0) {
					cout << "\n\n |   i|      Xi  |   F(Xi)  |      E            ";
					cout << "\n |  " << setw(2) << 0 << '|' << setw(10) << x02 << '|' << setw(10) << fx(x02) << '|';
				}
				else {
					aux = x02;
					xi = newton(aux);
					fxi = fx(xi);
					e = tolerancia(xi, aux);
					cout << "\n |  " << setw(2) << i << '|' << setw(10) << xi << '|'  << setw(10) << fx(xi) << '|' << setw(10) << e << '|';
					x02 = xi;
					if (e < tole)
						break;
				};
			};
			break;

		case 2:
			cout << " --- Método de Pegaso ---";
			for (int i = 0; i < ite; i++) {
				if (i == 0) {
					x0 = a;
					x1 = b;
					fx0 = fx(x0);
					fx1 = fx(x1);
					x2 = pegaso(x0, x1, fx0, fx1);
					fx2 = fx(x2);
					cout << "\n\n |  i|  Xn-1    |  Xn      |   Xn+1   | FXn-1    |  FXn     | FXn+1    |   E  ";
					cout << "\n |  1|   " << x0 << "|  " << x1 << " |  " << x2 << " |  " << fx0 << " | " << fx1 << " | " << fx2 << " |   ---";

				}
				else {
					aux = x0;
					x0 = xo(x0, x1, fx0, fx1, fx2);
					if (x0 == aux)
						fx0 = fredut(fx0, fx1, fx2);
					else
						fx0 = fx(x0);
					x1 = x2;
					fx1 = fx2;
					x2 = pegaso(x0, x1, fx0, fx1);
					fx2 = fx(x2);
					e = tolerancia(x2, x1);
					cout << "\n | " << setw(2) << i + 1 << '|' << setw(10) << x0 << '|' << setw(10) << x1 << '|' << setw(10) << x2 << '|' << setw(10) << fx0 << '|' << setw(10) << fx1 << '|' << setw(10) << fx2 << '|' << setw(15) << e;
					if (e < tole)
						break;
				}
			}

			break;
		case 3:
			break;
		default: cout << "Método não escolhido!";
			break;
		}
		cout << "\n\nDeseja Sair ? [0 = Sim] [ 1 = Não]: ";
		cin >> menu;

		system("pause");
		system("CLS");

	} while (menu != 0);

	return 0;
}
