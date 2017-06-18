#ifndef STRATEGY_H
#define STRATEGY_H

#include <functional>
#include <iostream>
#include <string>

namespace exercise {

/*use strategy model to replace virtual function*/

class Character;

struct Actions {
    static void defaultAct(const Character& ch);
    static void kill(const Character& ch);
    static void help(const Character& ch);
};


class Character {
public:
    using functType = std::function<void(const Character&)>;
    Character(const std::string& name,
              const functType& func =
                  std::bind(&Actions::defaultAct, std::placeholders::_1))
        : name_(name), action_(func) {}

    void behave() {
        action_(*this);
    }

    const std::string& getName() const {
        return name_;
    }
private:
    std::string name_;
    std::function<void(Character&)> action_; // not use virtual
};

class Evil: public Character {
public:
    Evil(const std::string& name,
         const functType& func =
             std::bind(&Actions::kill, std::placeholders::_1)) 
        : Character(name, func) {}
};

class Angel: public Character {
public:
    Angel(const std::string& name,
          const functType& func =
              std::bind(&Actions::help, std::placeholders::_1))
        : Character(name, func) {}
};


void Actions::defaultAct(const Character& chr) {
    std::cout << chr.getName() << " act" << std::endl;
}
void Actions::kill(const Character& chr) {
    std::cout << chr.getName() << " kill" << std::endl;
}
void Actions::help(const Character& chr) {
    std::cout << chr.getName() << " help" << std::endl;
}

}
#endif