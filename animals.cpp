/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-09-04 23:52:39
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-09-05 00:25:27
 * @FilePath: /inheritance_dynamic_cast/animals.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class Speakable {
public:
    virtual ~Speakable() = default;
    virtual void Speak(ostream& out) const = 0;
};

class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void Draw(ostream& out) const = 0;
};

class Animal {
public:
    virtual ~Animal() = default;
    void Eat(string_view food) {
        cout << GetType() << " is eating "sv << food << endl;
        ++energy_;
    }
    virtual string GetType() const = 0;

private:
    int energy_ = 100;
};

class Fish : public Animal, public Drawable {
public:
    string GetType() const override {
        return "fish"s;
    }
    void Draw(ostream& out) const override {
        out << "><(((*>"sv << endl;
    }
};

class Cat : public Animal, public Speakable, public Drawable {
public:
    void Speak(ostream& out) const override {
        out << "Meow-meow"sv << endl;
    }
    void Draw(ostream& out) const override {
        out << "(^w^)"sv << endl;
    }
    string GetType() const override {
        return "cat"s;
    }
};

// Рисует животных, которых можно нарисовать
void DrawAnimals(const std::vector<const Animal*>& animals, ostream& out) {
    for(auto animal : animals){
        if (const Drawable* drawable = dynamic_cast<const Drawable*>(animal)) {
            drawable->Draw(out);
        }
    }
}

void TalkToAnimals(const std::vector<const Animal*> animals, ostream& out) {
    for(auto animal : animals){
        if (const Speakable* speakable = dynamic_cast<const Speakable*>(animal)) {
            speakable->Speak(out);
        }
    }
}

void PlayWithAnimals(const std::vector<const Animal*> animals, ostream& out) {
    TalkToAnimals(animals, out);
    DrawAnimals(animals, out);
}

int main() {
    Cat cat;
    Fish fish;
    vector<const Animal*> animals{&cat, &fish};
    PlayWithAnimals(animals, cerr);
}