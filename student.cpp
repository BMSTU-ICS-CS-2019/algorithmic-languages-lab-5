#include "student.h"

#include <iostream>
#include <fstream>

#define __STUDENT_SUGARED_WRITE(target) << target name << " " << target surname << " " << target patronymic << " " << target age << " " << target studied_lessons << " " << target average_score
#define __STUDENT_SUGARED_READ(target) >> target name >> target surname >> target patronymic >> target age >> target studied_lessons >> target average_score

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;

static void write_binary(ofstream &output, const unsigned short &value) {
    output.write((char *) &value, sizeof value);
}

static void write_binary(ofstream &output, const float &value) {
    output.write((char *) &value, sizeof value);
}

static void write_binary(ofstream &output, const string &string) {
    const auto length = string.length();
    output.write((char *) &length, sizeof length);
    output.write(string.c_str(), length);
}

static void read_binary(ifstream &input, const unsigned short &value) {
    input.read((char *) &value, sizeof value);
}

static void read_binary(ifstream &input, const float &value) {
    input.read((char *) &value, sizeof value);
}

static void read_binary(ifstream &input, string &value) {
    typeof value.length() length;
    input.read((char *) &length, sizeof length);
    value.resize(length);
    input.read((char *) value.c_str(), length);
}

static void write_binary(ofstream &output, const student &student) {
    write_binary(output, student.name);
    write_binary(output, student.surname);
    write_binary(output, student.patronymic);
    write_binary(output, student.age);
    write_binary(output, student.studied_lessons);
    write_binary(output, student.average_score);
}

static void read_binary(ifstream &input, student &student) {
    read_binary(input, (string &) student.name);
    read_binary(input, (string &) student.surname);
    read_binary(input, (string &) student.patronymic);
    read_binary(input, student.age);
    read_binary(input, student.studied_lessons);
    read_binary(input, student.average_score);
}

void student::read_from_console() {
    cin __STUDENT_SUGARED_READ(this->);
}

void write_students_to_file(const string &filename, vector<student> &students, bool binary) {
    ofstream output;

    if (binary) {
        output.open(filename, fstream::out | fstream::binary);
        for (auto &student : students) write_binary(output, student);
    } else {
        output.open(filename, fstream::out);

        auto student_iterator = students.begin();
        const auto student_iterator_end = students.end();

        bool do_continue = student_iterator != student_iterator_end;
        while (do_continue) {
            const auto student = *student_iterator;

            output __STUDENT_SUGARED_WRITE(student.);
            if ((do_continue = (++student_iterator) != student_iterator_end)) output << endl;
        }
    }

    output.close();
}

vector<student> read_students_from_file(const string &filename, const bool binary) {
    ifstream input;

    vector<student> students;
    if (binary) {
        input.open(filename, fstream::in | fstream::binary);

        // cannot use #eof() here
        while (input.peek() != EOF) {
            student student;
            read_binary(input, student);
            students.push_back(student);
        }
    } else {
        input.open(filename, fstream::in);

        // cannot use #eof() here
        while (input.peek() != EOF) {
            student student;
            input __STUDENT_SUGARED_READ(student.);
            students.push_back(student);
        }
    }

    input.close();

    return students;
}
