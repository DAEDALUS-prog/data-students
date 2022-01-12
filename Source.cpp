#include <iostream>
#include <locale.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>


enum Exercise {
	Exit,
	CreateNewFile,
	ShowStudent,
	AddStudent,
	EditDATA,
	Exercise,
};

enum EditFile {
	Pass,
	Delete,
	Correct,
};

struct Name {
	std::string surname;
	std::string name;
	std::string patronymic;
};

struct Mark {
	int markPhysics;
	int markMaths;
	int markCS;
	int markChemistry;
	double middleMark;
};

struct Student {
	Name name;
	int yearBirth;
	int digitGroup;
	Mark mark;
};


void createFile();
void showStudent(Student* student);
void addStudent(Student* student);
void editDataFile(Student* student);
void mainExercise(Student* student);

bool checkExistsFile();
bool checkExistStudentExericse(Student* student, int groupNumber);
int calculateCountStudents();
double middleValueMarks(int& markMath, int& markPhysics, int& markCS, int& markChemistry);
void addExistStudents(Student* student);

void rewriteDataStudent(Student* student, int index);
void rewriteDataStudents(Student* student);
void deleteStudent(Student* student, int idStudent);

bool checkName(std::string name);
int checkTypeDataBirth();
int checkTypeDataDigitGroup();
int checkTypeDataMark();
int checkTypeDataNumber();


int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	int sizeArray = 10;
	if (checkExistsFile()) sizeArray = calculateCountStudents() + 10;
	Student* student = new Student[sizeArray];
	addExistStudents(student);
	

	int choise{};
	do {
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		std::cout << "\n1 - ������� ����\t2 - �������� ������\t3 - �������� ���������\t4 - ��������� ������\t5 - �������� ����������\t0 - �����\n\n---> ";

		choise = checkTypeDataNumber();
		switch (choise) {
		case CreateNewFile: {
			createFile();
			break;
		}
		case ShowStudent: {
			showStudent(student);
			break;
		}
		case AddStudent: {
			addStudent(student);
			break;
		}
		case EditDATA: {
			editDataFile(student);
			break;
		}
		case Exercise: {
			mainExercise(student);
			break;
		}
		default: std::cout << "\n�������� �������� �� 1 �� 5!\n\n" << std::endl;
		}
	} while (choise != Exit);
	return 0;
}


bool checkExistsFile()
{
	std::ifstream fin;
	fin.open("students.txt");
	if (fin.is_open()) {
		fin.close();
		return true;
	}
	else {
		fin.close();
		return false;
	}
}


void createFile()
{
	std::ofstream fout;

	if (!checkExistsFile()) {
		fout.open("students.txt");
		std::cout << "\n���� ��� ������� ������!";
		fout.close();
	}
	else {
		std::cout << "���� ����������! ��� �������� ������ ����� ���������� ������ ����� �������! (Y-yes | N-no) -> ";
		char choose;
		std::cin >> choose;
		if (choose == 'Y') {

			fout.open("students.txt");
			std::cout << "\n���� ��� ������� ������!";
			fout.close();
		}
	}

}


void addExistStudents(Student* student)
{

	if (checkExistsFile()) {
		std::ifstream fin("students.txt");

		int countStudents = calculateCountStudents();
		int index = 0;
		while (index < countStudents)
		{
			fin >> student[index].name.surname;
			fin >> student[index].name.name;
			fin >> student[index].name.patronymic;

			fin >> student[index].yearBirth;
			fin >> student[index].digitGroup;
			fin >> student[index].mark.markMaths;
			fin >> student[index].mark.markPhysics;
			fin >> student[index].mark.markCS;
			fin >> student[index].mark.markChemistry;
			fin >> student[index].mark.middleMark;

			index++;
		}
		fin.close();
	}
}


int calculateCountStudents()
{
	int count = 0;
	if (checkExistsFile())
	{
		std::ifstream fin("students.txt");
		std::string str;
		while (getline(fin, str)) count++;
		fin.close();
	}
	else std::cout << "������! ���� �����������!" << std::endl;

	return count;
}


void showStudent(Student* student) {

	if (checkExistsFile())
	{
		if (calculateCountStudents() != 0) {
			std::ifstream fin("students.txt");
			
			std::cout << "\n" << std::endl;
			std::cout << std::setw(20) << "���" << std::setw(21) << "��� ��������" << std::setw(17) << "����� ������" << std::setw(30) << "�������" << std::endl;
			std::cout << std::setw(187) << "���" << std::setw(7) << "���" << std::setw(7) << "���" << std::setw(7) << "���" << std::setw(18) << "������� ������" << std::endl;

			int countStudents = calculateCountStudents();
			for (int index = 0; index < countStudents; index++)
			{
				std::cout << std::setw(20) << student[index].name.surname << " " << student[index].name.name[0] << ". " << student[index].name.patronymic[0]
					<< "." << std::setw(11) << student[index].yearBirth << std::setw(17) << student[index].digitGroup << std::setw(13)
					<< student[index].mark.markMaths << std::setw(7) << student[index].mark.markPhysics << std::setw(7) << student[index].mark.markCS << std::setw(7)
					<< student[index].mark.markChemistry << std::setw(12) << student[index].mark.middleMark << std::endl;
			}
			std::cout << "\n" << std::endl;
			fin.close();
		}
		else std::cout << "������ ����! ������� 3 ��� ���������� ���������!" << std::endl;
	}
	else std::cout << "���� �����������t! ������� 1 ��� �������� �����!" << std::endl;
}


void addStudent(Student* student)
{
	if (checkExistsFile())
	{
		std::ofstream fout;
		fout.open("students.txt", std::ios::app);

		int index = calculateCountStudents();

		bool result;
		std::cout << "\n���������� ������!" << std::endl;
		do 
		{
			result = true;
			std::cout << "\n������� | ";
			std::cin >> student[index].name.surname;
			if (checkName(student[index].name.surname) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
			}
		} while (result == false);
		do
		{
			result == true;
			std::cout << "��� | ";
			std::cin >> student[index].name.name;
			if (checkName(student[index].name.name) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
			}
		} while (result == false);
		do 
		{
			result = true;
			std::cout << "�������� | ";
			std::cin >> student[index].name.patronymic;
			if (checkName(student[index].name.patronymic) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
			}
		} while (result == false);

		fout << student[index].name.surname << " ";
		fout << student[index].name.name[0] << ". ";
		fout << student[index].name.patronymic[0] << ". ";


		int resultYearBirth = -1;
		do {
			std::cout << "��� �������� | ";
			resultYearBirth = checkTypeDataBirth();

			if (resultYearBirth == -1) std::cout << "\n>>>��� �������� ������ �������� �� 4 ����!" << std::endl;
		} while (resultYearBirth == -1);

		student[index].yearBirth = resultYearBirth;
		fout << student[index].yearBirth << " ";


		int resultDigitGroup = -1;
		do {
			std::cout << "����� ������ | ";
			resultDigitGroup = checkTypeDataDigitGroup();

			if (resultDigitGroup == -1) std::cout << "\n>>>����� ������ ������ �������� �� 6 ����!" << std::endl;
		} while (resultDigitGroup == -1);

		student[index].digitGroup = resultDigitGroup;
		fout << student[index].digitGroup << " ";

		int resultMark{};
		do
		{
			std::cout << "������� �� ���������� | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markMaths = resultMark;
		} while (resultMark == -1);
		do
		{
			std::cout << "������� �� ������ | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markPhysics = resultMark;
		} while (resultMark == -1);
		do
		{
			std::cout << "������� �� ����������� | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markCS = resultMark;
		} while (resultMark == -1);
		do
		{
			std::cout << "������� �� ����� | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markChemistry = resultMark;
			if (resultMark == -1) std::cout << "������� ����� ��������� � ���� ������ ����� �� 0 �� 10!";
		} while (resultMark == -1);

		fout << student[index].mark.markMaths << " ";
		fout << student[index].mark.markPhysics << " ";
		fout << student[index].mark.markCS << " ";
		fout << student[index].mark.markChemistry << " ";

		student[index].mark.middleMark = middleValueMarks(student[index].mark.markMaths, student[index].mark.markPhysics, student[index].mark.markCS, student[index].mark.markChemistry);
		fout << student[index].mark.middleMark << "\n";
		fout.close();
	}
	else std::cout << "���� �����������! ������� 1 ��� �������� �����!" << std::endl;
}


void editDataFile(Student* student)
{
	if (checkExistsFile())
	{
		std::string surname, name;
		int digitGroup;

		bool result;
		do {
			std::cout << "\n������� | ";
			std::cin >> surname;
			result = true;
			if (checkName(surname) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
			}
		} while (result == false);

		do {
			std::cout << "��� | ";
			std::cin >> name;
			result = true;
			if (checkName(name) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
			}
		} while (result == false);

		do {
			std::cout << "����� ������ | ";
			result = true;
			digitGroup = checkTypeDataDigitGroup();
			if (digitGroup == -1)
			{
				std::cout << "����� ������ ����� ��������� ������ 6 ����!" << std::endl;
				result = false;
			}
		} while (result == false);
		
		
		int countStudents = calculateCountStudents(), idStudent = -1;
		for (int index = 0; index < countStudents; index++) {
			if (student[index].name.surname == surname && student[index].name.name[0] == name[0] && student[index].digitGroup == digitGroup)
			{
				idStudent = index;
				break;
			}
		}

		if (idStudent != -1)
		{
			std::cout << "1 - ��������\t2 - ��������\n---> ";

			
			int variantEdit;
			do {
				variantEdit = checkTypeDataNumber();
				if (variantEdit == -1) std::cout << "\n�������� �������� 1 ��� 2!" << std::endl;
			} while (variantEdit < 1 && variantEdit > 2);

			switch (variantEdit) 
			{
			case Delete: {
				deleteStudent(student, idStudent);
				break;
			}
			case Correct: {
				rewriteDataStudent(student, idStudent);
				break;
			}
			}
		}
		else std::cout << "��������� ��� � ������! ������� 3 ��� ���������� ���������!" << std::endl;
	}
}


double middleValueMarks(int& markMath, int& markPhysics, int& markCS, int& markChemistry)
{
	double middleValueMarks = (markMath + markPhysics + markCS + markChemistry) / 4.;
	return middleValueMarks;
}


void mainExercise(Student* student)
{
	if (checkExistsFile())
	{
		std::ofstream fout("newStudentsFile.txt");
		if (fout.is_open())
		{
			int countStudents = calculateCountStudents();

			int groupNumber = -1;
			do {
				std::cout << "������� ����� ������ | ";
				groupNumber = checkTypeDataDigitGroup();

				if (groupNumber == -1) std::cout << "\n>>>����� ������ ������ �������� �� 6 ����!" << std::endl;
			} while (groupNumber == -1);


			if (checkExistStudentExericse(student, groupNumber)) {
				std::cout << "\n\n" << std::setw(20) << "���" << std::setw(21) << "��� ��������" << std::setw(17)
					<< "����� ������" << std::setw(30) << "�������" << std::endl;

				std::cout << std::setw(187) << "���" << std::setw(7) << "���" << std::setw(7)
					<< "���" << std::setw(7) << "���" << std::setw(18) << "������� ������" << std::endl;

				for (int index = 0; index < countStudents; index++)
				{
					if (
						(student[index].name.surname[0] == '�'
							|| student[index].name.surname[0] == '�'
							|| student[index].name.surname[0] == '�') && groupNumber == student[index].digitGroup)
					{
						std::cout << std::setw(20)
							<< student[index].name.surname << " "
							<< student[index].name.name[0] << ". "
							<< student[index].name.patronymic[0] << "." << std::setw(11)
							<< student[index].yearBirth << std::setw(17)
							<< student[index].digitGroup << std::setw(13)
							<< student[index].mark.markMaths << std::setw(7)
							<< student[index].mark.markPhysics << std::setw(7)
							<< student[index].mark.markCS << std::setw(7)
							<< student[index].mark.markChemistry << std::setw(12)
							<< student[index].mark.middleMark << std::endl;


						fout
							<< student[index].name.surname << " "
							<< student[index].name.name[0] << ". "
							<< student[index].name.patronymic[0] << ". "
							<< student[index].yearBirth << " "
							<< student[index].digitGroup << " "
							<< student[index].mark.markMaths << " "
							<< student[index].mark.markPhysics << " "
							<< student[index].mark.markCS << " "
							<< student[index].mark.markChemistry << " "
							<< student[index].mark.middleMark
							<< "\n";
					}
				}
				std::cout << "\n" << std::endl;
			}
			else std::cout << "�������� ��������� ������ ��� ������� ���������� �� �, �, � � ������ �����������!" << std::endl;
		}
	}
	else std::cout << "������ ������ � ����� ����!" << std::endl;
}


void rewriteDataStudent(Student* student, int index)
{
	if (checkExistsFile())
	{
		std::ofstream fout;
		fout.open("students.txt", std::ios::app);
		std::cout << "\n�������������� ������!" << std::endl;

		bool result;
		do {
			result = true;
			std::cout << "\n������� | ";
			std::cin >> student[index].name.surname;
			if (checkName(student[index].name.surname) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
				continue;
			}

			std::cout << "��� | ";
			std::cin >> student[index].name.name;
			if (checkName(student[index].name.name) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
				continue;
			}

			std::cout << "�������� | ";
			std::cin >> student[index].name.patronymic;
			if (checkName(student[index].name.patronymic) == false)
			{
				std::cout << "\n>>> ��� ����� ��������� ������ ��������� � (���) ������ '-'!" << std::endl;
				result = false;
				continue;
			}
		} while (result == false);

		fout << student[index].name.surname << " ";
		fout << student[index].name.name[0] << ". ";
		fout << student[index].name.patronymic[0] << ". ";


		int resultYearBirth = -1;
		do {
			std::cout << "��� �������� | ";
			resultYearBirth = checkTypeDataBirth();

			if (resultYearBirth == -1) std::cout << "\n>>>��� �������� ������ �������� �� 4 ����!" << std::endl;
		} while (resultYearBirth == -1);

		student[index].yearBirth = resultYearBirth;
		fout << student[index].yearBirth << " ";


		int resultDigitGroup = -1;
		char digitGroup[6]{};
		do {
			std::cout << "����� ������ | ";
			resultDigitGroup = checkTypeDataDigitGroup();

			if (resultDigitGroup == -1) std::cout << "\n>>>����� ������ ������ �������� �� 6 ����!" << std::endl;
		} while (resultDigitGroup == -1);

		student[index].digitGroup = resultDigitGroup;
		fout << student[index].digitGroup << " ";

		int resultMark = -1;
		do
		{
			std::cout << "������� �� ���������� | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markMaths = resultMark;

			std::cout << "������� �� ������ | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markPhysics = resultMark;

			std::cout << "������� �� ����������� | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markCS = resultMark;


			std::cout << "������� �� ����� | ";
			resultMark = checkTypeDataMark();
			if (resultMark == -1) continue;
			student[index].mark.markChemistry = resultMark;
			if (resultMark == -1) std::cout << "������� ����� ��������� � ���� ������ ����� �� 0 �� 10!";
		} while (resultMark == -1);

		fout << student[index].mark.markMaths << " ";
		fout << student[index].mark.markPhysics << " ";
		fout << student[index].mark.markCS << " ";
		fout << student[index].mark.markChemistry << " ";

		student[index].mark.middleMark = middleValueMarks(student[index].mark.markMaths, student[index].mark.markPhysics, student[index].mark.markCS, student[index].mark.markChemistry);
		fout << student[index].mark.middleMark << "\n";
		fout.close();
	}
	rewriteDataStudents(student);
}


void rewriteDataStudents(Student* student)
{
	int countStudents = calculateCountStudents() - 1;

	std::ofstream fout;
	fout.open("students.txt");

	for (int index = 0; index < countStudents; index++)
	{

		fout << student[index].name.surname << " ";
		fout << student[index].name.name[0] << ". ";
		fout << student[index].name.patronymic[0] << ". ";

		fout << student[index].yearBirth << " ";

		fout << student[index].digitGroup << " ";

		fout << student[index].mark.markMaths << " ";
		fout << student[index].mark.markPhysics << " ";
		fout << student[index].mark.markCS << " ";
		fout << student[index].mark.markChemistry << " ";

		student[index].mark.middleMark = middleValueMarks(student[index].mark.markMaths, student[index].mark.markPhysics, student[index].mark.markCS, student[index].mark.markChemistry);
		fout << student[index].mark.middleMark << "\n";
	}
	fout.close();
}


void deleteStudent(Student* student, int idStudent)
{
	if (checkExistsFile()) {


		int countStudents = calculateCountStudents();
		std::ofstream fout("students.txt");

		for (int index = 0; index < countStudents; index++)
		{
			if (index == idStudent) continue;

			fout << student[index].name.surname << " ";
			fout << student[index].name.name[0] << ". ";
			fout << student[index].name.patronymic[0] << ". ";

			fout << student[index].yearBirth << " ";
			fout << student[index].digitGroup << " ";

			fout << student[index].mark.markMaths << " ";
			fout << student[index].mark.markPhysics << " ";
			fout << student[index].mark.markCS << " ";
			fout << student[index].mark.markChemistry << " ";

			fout << student[index].mark.middleMark << "\n";
		}
		addExistStudents(student);
		
		fout.close();
		std::cout << "�������� ������ �������!" << std::endl;
	}
}


bool checkExistStudentExericse(Student* student, int groupNumber)
{
	int countStudents = calculateCountStudents();

	bool existStudentExercise = false;
	for (int index = 0; index < countStudents; index++)
	{
		if (
			(student[index].name.surname[0] == '�'
				|| student[index].name.surname[0] == '�'
				|| student[index].name.surname[0] == '�') && groupNumber == student[index].digitGroup)
		{
			return true;
		}
	}
	return false;
}


bool checkName(std::string name)
{
	int lengthName = name.length();
	for (int index = 0; index < lengthName; index++)
	{
		if (!((name[index] >= '�' && name[index] <= '�') || (name[index] == '-') || (name[index] >= '�' && name[index] <= '�'))) return false;
	}
	return true;
}


int checkTypeDataBirth()
{
	char yearBirth[20]{};
	std::cin >> yearBirth;

	int lengthDigitYearBirth = strlen(yearBirth);
	if (lengthDigitYearBirth != 4) return -1;
	for (int index = 0; index < 4; index++)
	{
		if (!(yearBirth[index] >= '0' && yearBirth[index] <= '9')) return -1;
	}
	return atoi(yearBirth);
}


int checkTypeDataDigitGroup()
{
	char digitGroup[20]{};
	std::cin >> digitGroup;

	int lengthStrDigitYearBirth = strlen(digitGroup);
	if (lengthStrDigitYearBirth != 6) return -1;
	for (int index = 0; index < 6; index++)
	{
		if (!(digitGroup[index] >= '0' && digitGroup[index] <= '9')) return -1;
	}
	return atoi(digitGroup);
}


int checkTypeDataMark()
{
	char mark[10]{};
	std::cin >> mark;

	int lengthStrMark = strlen(mark);
	if (lengthStrMark > 2) return -1;
	for (int index = 0; index < lengthStrMark; index++)
	{
		if (!(mark[index] >= '0' && mark[index] <= '9')) return -1;
	}
	int resultMark = atoi(mark);
	if (resultMark > 10) return -1;

	return resultMark;
}


int checkTypeDataNumber()
{
	char number[10]{};
	std::cin >> number;

	int lengthStrNumber = strlen(number);
	if (lengthStrNumber != 1) return -1;
	
	if (number[0] >= '0' && number[0] <= '9') return atoi(number);
	return -1;
}