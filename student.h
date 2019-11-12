#ifndef LAB5_STUDENT_H
#define LAB5_STUDENT_H

#include <string>
#include <vector>

using std::istream;
using std::ostream;
using std::string;
using std::vector;

struct student {
    string name, surname, patronymic;
    unsigned short age;
    unsigned short studied_lessons;
    float average_score;

    void read_from_console();

    void read_from_file(const string &filename, bool binary = true);

    void append_to_console();

    void append_to_file(const string &filename, bool binary = true);

    [[nodiscard]] string to_string() const {
        return "student {  name = " + name + ", surname = " + surname + ", patronymic = " + patronymic
               + ", age = " + std::to_string(age)
               + ", studied_lessons = " + std::to_string(studied_lessons)
               + ", average_score = " + std::to_string(average_score)
               + " }";
    }
};

vector<student> read_students_from_file(const string &filename, bool binary = true);

void write_students_to_file(const string &filename, vector<student>& students, bool binary = true);

#endif //LAB5_STUDENT_H