#include<iostream>
#include<fstream>
#include<cstdlib>
#include<Windows.h>

int main() {
	setlocale(LC_ALL, "RUS");
	int rows{}, columns{};
	std::ifstream file("курсач.txt");
	if (file.is_open()) {
		file >> rows;
		file >> columns;
		//создание массивов
		std::string** old_arr = new std::string * [rows];
		std::string** new_arr = new std::string * [rows];
		for (size_t i = 0; i < rows; i++) {
			old_arr[i] = new std::string[columns];//создание массива, который будет хранить предыдущую генерацию
			new_arr[i] = new std::string[columns];//создание массива, который будет хранить новую генерацию
			for (size_t j = 0; j < columns; j++) {
				new_arr[i][j] = "-";
				old_arr[i][j] = "-";
			}
		}
		int file_i{}, file_j{}, count{}, generous{};
		while (file >> file_i >> file_j) {
			new_arr[file_i][file_j] = "*";
			old_arr[file_i][file_j] = "*";
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
					int countAliveCells{0};//сколько рядом живых
					if (old_arr[i][j] == "*") {
						countAliveCells = -1;
					}
				//4 крайние точки
					//точка (0;0)
					if (i == 0 && j == 0) {
						for (size_t k = i; k < i + 2; k++) {
							for (size_t l = j; l < j + 2; l++) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells > 3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//точка (rows-1:0)
					else if (i == rows - 1 && j == 0) {
						for (int k = i; k > i - 2; k--) {
							for (size_t l = j; l < j + 2; l++) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells > 3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//точка (0:columns-1)
					else if (i == 0 && j == columns - 1) {
						for (size_t k = i; k < i + 2; k++) {
							for (int l = j; l > j - 2; l--) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells > 3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//точка (rows-1:columns-1)
					else if (i == rows - 1 && j == columns - 1) {
						for (int k = i; k > i - 2; k--) {
							for (int l = j; l > j - 2; l--) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells > 3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
				//5 соседей 
					//левая стенка
					if (i > 0 && i < rows - 1 && j == 0) {
						for (size_t k = i - 1; k < i + 2; k++) {
							for (size_t l = j; l < j + 2; l++) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells>3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//верхняя стенка
					else if (i == 0 && j > 0 && j < columns - 1) {
						for (size_t k = i; k < i + 2; k++) {
							for (size_t l = j - 1; l < j + 2; l++) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells >3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//нижняя стенка
					else if (i == rows - 1 && j > 0 && j < columns - 1) {
						for (int k = i; k > i - 2; k--) {
							for (size_t l = j-1; l < j + 2; l++) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells>3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//правая стенка
					else if (i > 0 && i < rows - 1 && j == columns - 1) {
						for (size_t k = i - 1; k < i + 2; k++) {
							for (int l = j; l > j - 2; l--) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells >3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
					}
					//когда 8 соседей
					if ((i > 0 && (i < rows - 1)) && (j>0 && (j < columns - 1))) {
						for (size_t k = i - 1; k < i + 2; k++) {
							for (size_t l = j - 1; l < j + 2; l++) {
								if (old_arr[k][l] == "*") {
									countAliveCells += 1;
								}
							}
						}
						if (old_arr[i][j] == "*") {
							if (countAliveCells < 2 || countAliveCells>3) {
								new_arr[i][j] = "-";
								count -= 1;
							}
						}
						else if (old_arr[i][j] == "-") {
							if (countAliveCells == 3) {
								new_arr[i][j] = "*";
								count += 1;
							}
						}
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
	}
	else {
		std::cout << "Файл не наден " << std::endl;
	}
	return EXIT_SUCCESS;
}