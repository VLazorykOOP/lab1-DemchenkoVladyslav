// ArrayFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
#include <time.h>

using namespace std;

typedef double* pDouble;
/*
*   ConsoleInputArrayDouble
*
*/
struct matrixSize
{
	int m;
	int n;
};
char buffer[30];
const int MAX_SIZE = 560;
int ConsoleInputSizeArray(const int sizeMax)
{
	int size = 0;
	do {
		cout << " Input size Array ( 0< 1 < " << sizeMax << " ) ";
		cin >> size;
	} while (size <= 0 || size >= sizeMax);
	return size;
}
/*
*   ConsoleInputArrayDouble
*
*/
int ConsoleInputArray(int sizeMax, double A[])
{
	int size = ConsoleInputSizeArray(sizeMax);
	for (int i = 0; i < size; i++) {
		cout << " Array[ " << i << "] "; cin >> A[i];
	}
	return size;
}

/*
*   RndInputArrayDouble
*
*/
int RndInputArray(int sizeMax, double A[])
{
	int size = ConsoleInputSizeArray(sizeMax);
	int r1 = 0, r2 = 0;
	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		r1 = rand();
		r2 = rand();
		A[i] = 100.0 * r1;
		A[i] = A[i] / (1.0 + r2);
		if (rand() % 2)
			A[i] *= -1;
		cout << A[i] << "   ";
	}
	return size;
}
void RndInputMatrix(int m, int n, double* C[])
{
	int r1 = 0, r2 = 0;
	srand(time(NULL));
	for (int i = 0; i < m; i++) {
		C[i] = new double[n];
		double r1, r2;
		for (int j = 0; j < n; j++) {
			r1 = rand();
			r2 = rand();
			C[i][j] = 100.0 * r1;
			C[i][j] = C[i][j] / (1.0 + r2);
			if (rand() % 2)
				C[i][j] *= -1;
			cout << C[i][j] << "   ";
		}
		cout << endl;
	}
}
int ConsoleInputDynamicArrayNew(int sizeMax, pDouble& pA)
{
	int size = ConsoleInputSizeArray(sizeMax);
	pA = new double[size];
	if (pA == nullptr) { return 0; }
	for (int i = 0; i < size; i++) {
		cout << " Array[ " << i << "] "; cin >> pA[i];
	}
	return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, pDouble& pA)
{
	int size = ConsoleInputSizeArray(sizeMax);
	pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
	if (pA == nullptr) { return 0; }
	for (int i = 0; i < size; i++) {
		cout << " Array[ " << i << "] "; cin >> pA[i];
	}
	return size;
}

void ConsoleInputVector(int sizeMax, vector<double>& A)
{
	int size = ConsoleInputSizeArray(sizeMax);
	double d;
	for (int i = 0; i < size; i++) {
		cout << " Vector[ " << i << "] "; cin >> d; A.push_back(d);
	}
	return;
}


/*
*  WriteArrayTextFile
*
*/

void WriteArrayTextFile(int n, double* arr, const char* fileName)
{
	ofstream fout(fileName);
	if (!fout.is_open()) return;
	if (fout.fail()) return;
	fout << n << endl;
	for (int i = 0; i < n; i++)
		fout << arr[i] << "   ";
	cout << endl;
	fout.close(); //
}
/*
*  ReadArrayTextFile
*
*/


int ReadArrayTextFile(int n, double* arr, const char* fileName)
{
	int size;
	ifstream fin(fileName);
	if (fin.fail()) return 0;
	fin >> size;
	if (size <= 0) return 0;
	if (size > n)
	{
		size = n;
	}
	double d;
	for (int i = 0; i < size; i++)
	{
		fin >> d;
		arr[i] = d;
	}
	fin.close();
	return size;
}
void WriteMatrixTextFile(int m, int n, double* arr[], const char* fileName)
{
	ofstream fout(fileName);
	if (!fout.is_open()) return;
	if (fout.fail()) return;
	fout << n << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			fout << arr[i][j] << "   ";
	}
	fout.close(); //
}
/*
*  ReadArrayTextFile
*
*/


matrixSize ReadMatrixTextFile(int m, int n, double* arr[], const char* fileName)
{
	ifstream fin(fileName);
	if (fin.fail()) return { 0,0 };
	fin >> m >> n;
	if (m <= 0 || n <= 0) return { 0,0 };
	double d;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> d;
			arr[i][j] = d;
		}
	}
	fin.close();
	return { m,n };
}
void WriteVectorTextFile(vector<double> v, const char* fileName)
{
	ofstream fout(fileName);
	if (fout.fail()) return;
	fout << v.size() << endl;
	for (int i = 0; i < v.size(); i++)
		fout << v[i] << "   ";
	cout << endl;
	fout.close(); //
}
/*
*  ReadArrayTextFile
*
*/


void ReadVectorTextFile(vector<double> v, const char* fileName)
{
	ifstream fin(fileName);
	if (fin.fail()) return;
	int n;
	double d;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> d;
		v.push_back(d);
	}
	fin.close(); //
}


void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
	//ios_base
	ofstream bfout(fileName, ios_base::binary);
	if (bfout.fail()) return;
	bfout.write((const char*)&n, sizeof(int));
	std::streamsize  cn = static_cast<std::streamsize>(n) * sizeof(double);
	bfout.write((const char*)arr, cn);
	bfout.close();
}

int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
	int size = 0;
	ifstream bfin(fileName, ios_base::binary);
	if (bfin.fail()) return 0;
	bfin.read((char*)&size, sizeof(int));
	if (size <= 0) return 0;
	if (size > n) size = n;
	bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
	bfin.close();
	// ssdhs
	return size;
}
void WriteAnswerBinFile(double answer, const char* fileName)
{
	//ios_base
	ofstream bfout(fileName, ios_base::binary);
	if (bfout.fail()) return;
	bfout.write((const char*)&answer, sizeof(double));
	bfout.close();
}
void WriteAnswerTextFile(double answer, const char* fileName)
{
	ofstream fout(fileName);
	if (!fout.is_open()) return;
	if (fout.fail()) return;
	fout << answer;
	fout.close(); //
}
void ShowMainMenu()
{
	cout << "    Main Menu  \n";
	cout << "    1.  Task 1  \n";
	cout << "    2.  Task 2  \n";
	cout << "    3.  Task 3  \n";
}

void Task1()
{
	double A[MAX_SIZE], B[MAX_SIZE];//масиви для першого завдання
	int m = 0, minIn;//розмір масиву та індекс мінімального елемента
	double minEl;//сам мінімальний елемент	
	ReadArrayTextFile(m, B, "1Read.txt");
	if (m == 0)
	{
		ReadArrayBinFile(m, B, "1Read.bin");
		if (m == 0)
		{
			m = RndInputArray(MAX_SIZE, A);
			WriteArrayBinFile(m, A, "1Write.bin");
			WriteArrayTextFile(m, A, "1Write.txt");//у випадку, якщо масив не зчитається, то він заповнюється випадковими елементами та записується у бінарний та текстовий файли
			WriteArrayBinFile(m, A, "1Read.bin");
			WriteArrayTextFile(m, A, "1Read.txt");
		}
	}
	ReadArrayTextFile(m, B, "1Read.txt");
	minEl = B[0];
	minIn = 0;
	for (int i = 0; i < m; i++)
	{
		if (minEl > B[i])
		{
			minEl = B[i];
			minIn = i;
		}
	}//перебирається кожен елемент у пошуку найменшого
	cout << endl << " min element and it`s index:" << minEl << " | " << minIn << endl;
	WriteAnswerBinFile(minEl, "1Answer.bin");
	WriteAnswerTextFile(minEl, "1Answer.txt");

}
void Task2()
{
	double A[MAX_SIZE], B[MAX_SIZE];//масиви для другого завдання
	int m = 0, findIndex = -1, firstIndex = -1;//розмір масиву, номер найменшого елемента з умови, номер першого числа, яке більше за Т
	cout << endl << "Enter the T number" << endl;
	double T, curr_min = 0;//число Т з умови та поточний найменший елемент
	cin >> T;
	ReadArrayTextFile(m, B, "1Read.txt");
	if (m == 0)
	{
		m = RndInputArray(MAX_SIZE, A);
		WriteArrayBinFile(m, A, "2Write.bin");
		WriteArrayTextFile(m, A, "2Write.txt");//у випадку, якщо масив не зчитається, то він заповнюється випадковими елементами та записується у бінарний та текстовий файли
		WriteArrayBinFile(m, A, "2Read.bin");
		WriteArrayTextFile(m, A, "2Read.txt");
	}
	ReadArrayTextFile(m, B, "2Read.txt");
	cout << endl;
	for (int i = 0; i < m; i++)
	{
		if (T < *(B + i))
		{
			firstIndex = i;
			break;
		}
	}// шукається номер першого числа, яке більше за Т
	if (firstIndex != -1)
	{
		curr_min = LLONG_MIN;
		for (int i = 0; i < firstIndex; i++)
		{
			if (*(B + i) < 0 && *(B + i) > curr_min)
			{
				findIndex = i;
				curr_min = *(B + i);
			}
		}// шукається потрібний елемент з умови та його індекс
		if (findIndex == -1)
		{
			cout << "No needed elements found" << endl;
			return;
		}
		WriteAnswerBinFile(curr_min, "2Answer.bin");
		WriteAnswerTextFile(curr_min, "2Answer.txt");
		cout << "Needed element and it`s index: " << curr_min << " | " << findIndex << endl;
	}
	else
	{
		cout << "No elements bigger than T found" << endl;
		return;
	}
}
void Task3()
{
	int m = 0, n = 0;//розміри масиву	
	double** C = new double* [m];//масив для третього завдання
	double* minimums = new double[m];//масив для найменших елементів кожного рядка
	cout << endl;
	srand(time(NULL));
	matrixSize mS = ReadMatrixTextFile(m, n, C, "3Read.txt");
	m = mS.m;
	n = mS.n;
	if (m == 0 || n == 0)
	{
		cout << "Error in file reading" << endl;
		cout << "Enter matrix size:" << endl;
		do {
			cin >> m >> n;
		} while (m <= 0 || n <= 0);
		RndInputMatrix(m, n, C);
	}
	// розподіляється динамічно пам'ять під двовимірний масив С та додає випадкові елементи		
	for (int i = 0; i < m; i++)
	{
		double curr_min = C[i][0];
		for (int j = 1; j < n; j++)
		{
			if (C[i][j] < curr_min)
				curr_min = C[i][j];
		}
		minimums[i] = curr_min;
	}//у кожному рядку шукається мінімальний елемент та додається у масив мінімумів
	double Z = minimums[0];
	for (int i = 1; i < m; i++)
	{
		if (minimums[i] > Z)
			Z = minimums[i];
	}//шукається найбільший серед найменших елементів
	WriteMatrixTextFile(m, n, C, "3Write.txt");
	WriteAnswerBinFile(Z, "3Answer.bin");
	WriteAnswerTextFile(Z, "3Answer.txt");
	cout << endl << "Z = " << Z << endl;
}
int main()
{
	ShowMainMenu();
	int v;
	do {
		cin >> v;
	} while (v < 1 || v > 3);
	system("CLS");
	switch (v)
	{
	case 1:
	{
		Task1();
	}
	break;
	case 2:
	{
		Task2();
	}
	break;
	case 3:
	{
		Task3();
	}
	break;
	default:
		break;
	}
	return 1;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
