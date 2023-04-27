#include "aio.hpp"

/* Example of defining an enum */
MAKE_ENUM(Status,
  ALIVE,
  DEAD,
);

/* Example of defining a struct */
#define FIELDS(x) \
  x(int, age) \
  x(std::string_view, name) \
  x(Status, status)
STRUCT(PersonInfo,
  /* Example of a method declared for a struct */
  void self_introduction() const {
    std::cout << "Hello, my name is " << name << " and I am " << age << " years old." << std::endl;
  }
);
#undef FIELDS

#define FIELDS(x) \
  x(std::vector<PersonInfo>, passengers)
STRUCT(Bus,
  void introduce_passengers() const {
    std::cout << "The passengers are: " << '\n';
    std::for_each(passengers.begin(), passengers.end(), [](const PersonInfo& passenger) {
      std::cout << passenger.name << " (" << passenger.age << ")" << '\n';
    });
  }
);
#undef FIELDS

auto main() -> int {
  auto person = PersonInfo(20, "John", Status::ALIVE);
  DEBUG(person);
  DEBUG(person.name);
  DEBUG(person.age);
  DEBUG(person.status);
  person.self_introduction();
  auto person2 = PersonInfo{ 17, "Bob", Status::ALIVE };
  auto bus = Bus({person, person2});
  bus.introduce_passengers();
}