#include "StackManipulation.h"

namespace s21::expression {

void StackManipulation::ReverseStack(DataStack &stack) {
  std::vector<data_structs::Data> temp_vector{};

  while (!stack.empty()) {
    temp_vector.push_back(stack.top());
    stack.pop();
  }

  for (const auto &elem : temp_vector) {
    stack.push(elem);
  }
}
}  // namespace s21::expression