#include<iostream>
#include<fstream>
#include<cstdlib>
#include<Windows.h>

int main() {
	setlocale(LC_ALL, "RUS");
	int rows{}, columns{};
	std::ifstream file("Курсач1.txt");
	if (file.is_open()) {
		file >> rows;
		file >> columns;
		//создание массивов
		char** old_arr = new char* [rows];
		char** new_arr = new char* [rows];
		for (size_t i = 0; i < rows; i++) {
			old_arr[i] = new char[columns];//создание массива, который будет хранить предыдущую генерацию
			new_arr[i] = new char[columns];//создание массива, который будет хранить новую генерацию
			for (size_t j = 0; j < columns; j++) {
				new_arr[i][j] = '-';
				old_arr[i][j] = '-';
			}
		}
		int file_i{}, file_j{}, count{}, generous{};
		while (file >> file_i >> file_j) {
			new_arr[file_i][file_j] = '*';
			old_arr[file_i][file_j] = '*';
			count += 1;
		}
		file.close();
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				std::cout << old_arr[i][j] << " ";
			}
			std::cout << std::endl;
		}
		generous += 1;
		std::cout << "Generation: " << generous << ". " << "Active cells: " << count << std::endl;
		Sleep(2000);
		std::system("cls");
		//вторая и последующая генерация
		while (count != 0) {
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					int countAliveCells{ 0 };//сколько рядом живых
					for (int k=-1; k < 2; k++) {
						for (int l = -1; l < 2; l++) {
							if (k==0 && l==0) {
								continue;
							}
							int neighbour_i = i + k;
							int neighbour_j = j + l;
							if ((neighbour_i >= 0 && neighbour_i < rows) && (neighbour_j >= 0 && neighbour_j < columns)) {
								if (old_arr[neighbour_i][neighbour_j] == '*') {
									countAliveCells +=1;
								}
							}
						}
					}
					if (old_arr[i][j] == '*') {
						if (countAliveCells < 2 || countAliveCells > 3) {
							new_arr[i][j] = '-';
						}
					}
					else if (old_arr[i][j] == '-') {
						if (countAliveCells == 3) {
							new_arr[i][j] = '*';
						}
					}
				}
			}	
			count = 0;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					if (new_arr[i][j] == '*') {
						count++;
					}
				}
			}
			int count_equl_arr{};
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					if (old_arr[i][j] == new_arr[i][j]) {
						count_equl_arr += 1;
					}
				}
			}
			generous += 1;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					std::cout << new_arr[i][j] << " ";
				}
				std::cout << std::endl;
			}
			if (count == 0) {
				std::cout << "Generation : " << generous << ". Alive cells: " << count << std::endl;
				std::cout << "All cells are dead. Game over :( " << std::endl;
				break;
			}
			else if (count_equl_arr == rows * columns) {
				std::cout << "Generation : " << generous << ". Alive cells: " << count << std::endl;
				std::cout << "The world has stagnated. Game over :( " << std::endl;
				break;
			}
			else {
				std::cout << "Generation: " << generous << ". " << "Active cells: " << count << std::endl;
				for (size_t i = 0; i < rows; i++) {
					for (size_t j = 0; j < columns; j++) {
						old_arr[i][j] = new_arr[i][j];
					}
				}
			}
			Sleep(2000);
			std::system("cls");
		}
		for (size_t i = 0; i < rows; i++) {
			delete[] old_arr[i];
			delete[] new_arr[i];
		}
		delete[] old_arr;
		delete[] new_arr;
	}
	else {
		std::cout << "Файл не наден " << std::endl;
	}
	return EXIT_SUCCESS;
}
