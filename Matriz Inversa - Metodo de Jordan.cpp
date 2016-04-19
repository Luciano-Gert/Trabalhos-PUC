#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iomanip>
#include <cstdlib>

#define TAM 100
using namespace std;

void Cabecalho() {
	cout << "\t++=====================================++";
	cout << "\n\t||   2° Trabalho de Cálculo Numérico   ||";
	cout << "\n\t||      Ciro de Oliveira Auais         ||";
	cout << "\n\t||     Luciano Almeida Gertrudes       ||";
	cout << "\n\t||     Engenharia de Computação        ||";
	cout << "\n\t||          Matriz Inversa             ||";
	cout << "\n\t||         Metodo de Jordan            ||";
	cout << "\n\t++=====================================++\n\n";
}

int menu() {
	int menu;
	system("CLS");
	Cabecalho();
	cout << "\n\n -- [1] Inversa";
	cout << "\n -- [2] Sair";
	cout << "\n opção:\t";
	cin >> menu;
	return (menu);
}


int main(int argc, _TCHAR* argv[])
{

	// Acentuação
	setlocale(LC_ALL, "Portuguese");

	int opc = 1;

	do {
		float matriz[TAM][TAM] = { 0 }, matriz2[TAM][TAM] = { 0 };
		float multiplicador, pivo;
		int ordem, det = 1;

		opc = menu();
		switch (opc) {
		case 1:

			cout << "- Digite a ordem da matriz: ";
			cin >> ordem;

			// preenchendo a matriz
			cout << "\n- Preencha cada linha da matriz, com espaço entre os numeros:\n";
			for (int lin = 0; lin < ordem; lin++) {
				cout << "Linha " << lin + 1 << ": ";
				for (int col = 0; col < ordem; col++) {
					cin >> matriz[lin][col];
				}
			}

			// preenchendo a matriz identidade ao lado da matriz digitada
			for (int lin = 0; lin < ordem; lin++)
				for (int col = 0; col < 2 * ordem; col++)
					if (col == (lin + ordem))
						matriz[lin][col] = 1;


			// exibindo a matriz digitada
			system("CLS");
			Cabecalho();
			cout << "\nA matriz digitada:";
			for (int lin = 0; lin < ordem; lin++) {
				cout << "\n| ";
				for (int col = 0; col < ordem; col++)
					cout << "  " << matriz[lin][col];
				cout << "  | ";
			}

			// exibindo a matriz identidade
			cout << "\n\nA matriz identidade:";
			for (int lin = 0; lin < ordem; lin++) {
				cout << "\n| ";
				for (int col = ordem; col < ordem * 2; col++)
					cout << "  " << matriz[lin][col];
				cout << "  | ";
			}


			//metodo de jordan
			cout << "\n\n- Operações elementares executadas: \n";
			for (int lin = 0; lin < ordem; lin++) {
				for (int col = 0; col < ordem; col++) {
					if ((col != lin) && (matriz[lin][lin] != 0)) {
						multiplicador = matriz[col][lin] / matriz[lin][lin];	// calcula o multiplicador
						if (multiplicador != 0) {
							for (int i = 0; i < ordem * 2; i++) {
								matriz[col][i] -= matriz[lin][i] * multiplicador;	// aplica operação elementar

								//Pegando a matriz triangular inferior para calcular o determinante
								for (int f = 0; f < ordem; f++)
									for (int u = 0; u < ordem; u++) {
										matriz2[f][u] = matriz[f][u];
									}
							}
						}
						cout << "\nL" << col + 1 << " = " << "L" << col + 1 << "-" << multiplicador << "*" << "L" << lin + 1;
					}
				}
			}
			cout << "\n\n";

			//Calcular o determinante
			for (int i = 0; i < ordem; i++)
				det = det * matriz2[i][i];
			cout << "\n- O valor do determinante é de: " << det;
			if (det == 0) {
				cout << "\n- Determinante igual a zero, logo não existe inversa!\n\n\n";
				system("pause");
				break;
			}

			if (det != 0) {
				//fazendo com que a diagonal principal vire 1
				for (int lin = 0; lin < ordem; lin++) {
					pivo = matriz[lin][lin];					//pivo recebe o elemento da diagonal principal
					for (int col = 0; col < ordem * 2; col++)
						matriz[lin][col] = matriz[lin][col] / pivo;		// aplica operação elementar
				}

				// Fixando o valor de casas decimais do Cout
				cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
				cout.precision(5);


				// exibindo a matriz inversa calculada
				cout << "\n\n\n -- A matriz inversa FINAL É: \n";
				for (int lin = 0; lin < ordem; lin++) {
					cout << "\n";
					for (int col = ordem; col < ordem * 2; col++)
						cout << setw(5) << " |  " << setw(5) << matriz[lin][col] << setw(5);
					cout << setw(5) << "  | " << setw(5);
				}
				cout << "\n\n";
				system("pause");
			}
			break;


		case 2:
			system("cls");
			Cabecalho();
			cout << "\nSaindo do sistema...\n\n";
			system("pause");
			break;

		default:
			cout << "\nOpcao invalida.\n\n";
			system("pause");
			break;
		}

	} while (opc != 2);
	return 0;
}
