#include <iostream>

#include "student.h"

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::back_inserter;
using std::cin;
using std::count_if;
using std::cout;
using std::endl;
using std::find;
using std::istream;
using std::less;
using std::map;
using std::ostream;
using std::pair;
using std::replace_if;
using std::sort;
using std::string;
using std::to_string;
using std::transform;
using std::unordered_multimap;
using std::unordered_set;
using std::vector;

template<typename E>
string to_string(const vector<E> vector) {
    string value = "{";
    {
        auto not_first = false;
        for (auto &element : vector) {
            if (not_first) value += ", ";
            else not_first = true;

            value += element;
        }
    }
    return value + "}";
}

template<typename E>
string to_string(const unordered_set<E> vector) {
    string value = "{";
    {
        auto not_first = false;
        for (auto &element : vector) {
            if (not_first) value += ", ";
            else not_first = true;

            value += element;
        }
    }
    return value + "}";
}

template<typename K, typename V>
string to_string(const map<K, V> map) {
    string value = "{";
    {
        const auto end = map.end();
        auto not_first = false;
        for (auto iterator = map.begin(); iterator != end; iterator++) {
            if (not_first) value += ", ";
            else not_first = true;

            const auto pair = *iterator;
            value += (to_string(pair.first) + ":" + pair.second);
        }
    }
    return value + "}";
}

template<typename K, typename V>
string to_string(const unordered_multimap<K, V> map) {
    string value = "{";
    {
        const auto end = map.end();
        auto not_first = false;
        for (auto iterator = map.begin(); iterator != end; iterator++) {
            if (not_first) value += ", ";
            else not_first = true;

            const auto pair = *iterator;
            value += (to_string(pair.first) + ":" + pair.second);
        }
    }
    return value + "}";
}

void task_lambda();

void task_io();

int main() {
    while (true) {
        cout << "Select task group (`lambda`, `io` or `exit`):" << endl;
        string mode;
        cin >> mode;

        if (mode == "lambda") task_lambda();
        else if (mode == "io") task_io();
        if (mode == "exit") {
            cout << "Goodbye!" << endl;
            return 0;
        } else cout << "Unknown mode" << endl;
    }
}

void task_lambda() {
    unordered_multimap<int, string> original_map;
    /* Task 1 */
    {
        size_t size;
        cout << "Insert size: ";
        cin >> size;
        for (size_t i = 0; i < size; i++) {
            cout << "Insert key and value: ";
            int key;
            string value;
            cin >> key >> value;
            original_map.insert(pair<int, string>(key, value));
        }
        cout << "Read collection: " << to_string(original_map) << endl;
    }
    {
        original_map.erase(5);
        original_map.erase(8);
        cout << "After erasing: " << to_string(original_map) << endl;
    }
    {
        for (auto i = 0U; i < 2U; i++) {
            cout << "Insert value for key 2: ";
            string value;
            cin >> value;
            original_map.insert(pair<int, string>(2, value));
        }
        cout << "After adding two values at 2: " << to_string(original_map) << endl;
    }
    map<int, string> shortened_map;
    {
        const auto end = original_map.end();
        for (auto iterator = original_map.begin(); iterator != end; iterator++) {
            const auto pair = *iterator;
            shortened_map.insert(::pair < int, string > (pair.first, pair.second));
        }
        cout << "Shortened map: " << to_string(shortened_map) << endl;
    }

    /* Task 2 */
    {
        cout << "Number of positive elements: " << count_if(
                shortened_map.begin(), shortened_map.end(),
                [](const pair<int, string> &pair) { return pair.first > 0; }
        );
    }
    vector<int> keys;
    {
        transform(
                shortened_map.begin(), shortened_map.end(), std::back_inserter(keys),
                [](const pair<const int, const string> &pair) { return pair.first; }
        );
        cout << "Keys: " << to_string(keys) << endl;
    }

    /* Task 3 */
    {
        cout << "Found 2 at " << *find(keys.begin(), keys.end(), 2) << endl;
    }
    {
        replace_if(keys.begin(), keys.end(), [](const int &key) { return key < 0; }, 10);
        cout << "Vector after replacement: " << to_string(keys) << endl;
    }
    {
        sort(keys.begin(), keys.end(), less<>());
    }

    {
        unordered_set<int> keySet;
        for (auto &key : keys) keySet.insert(key);
        cout << "Key-set: " << to_string(keySet);
    }
}

void task_io() {
    string action;
    cout << "Select action (`read` or `write`)" << endl;
    cin >> action;

    if (action == "read") {
        cout << "Insert file name: ";
        string file_name;
        cin.ignore();
        getline(cin, file_name);
        cout << "Got file name `" << file_name << "`" << endl;

        cout << "Reading students..." << endl;
        auto students = read_students_from_file(file_name);
        {
            int i = 0;
            for (auto &student : students) cout << "Student #" << ++i << ": " << student.to_string() << endl;
        }
        cout << "Read students: " << students.size() << endl;
    } else if (action == "write") {
        size_t student_count;
        cout << "Enter the amount of students: ";
        cin >> student_count;

        // use pre-defined size
        if (student_count > 0) cout
                << "Use the following pattern: <name> <surname> <patronymic> <age> <studied lessons> <average score>"
                << endl;

        vector<student> students(student_count);
        for (size_t i = 0; i < student_count; i++) {
            cout << "Enter student #" << i + 1 << ": ";

            student student;
            student.read_from_console();

            students[i] = student;
        }

        cout << "Insert file name: ";
        string file_name;

        cin.ignore();
        getline(cin, file_name);
        write_students_to_file(file_name, students);
    } else cout << "Unknown action" << endl;
}
