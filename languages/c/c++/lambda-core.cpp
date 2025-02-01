#include <print>

namespace logic {
constexpr auto _true = [](const auto &x) {
  return [&x](const auto &) { return x; };
};

constexpr auto _false = [](const auto &) {
  return [](const auto &y) { return y; };
};

constexpr auto _not = [](const auto &x) { return x(_false)(_true); };

constexpr auto _and = [](const auto &x) {
  return [&x](const auto &y) { return x(y)(_false); };
};

constexpr auto _or = [](const auto &x) {
  return [&x](const auto &y) { return x(_true)(y); };
};

namespace test {
constexpr bool convert(const auto &x) { return x(true)(false); }

void print(const auto &x) { std::println("{}", convert(x)); }
} // namespace test
} // namespace logic

namespace church {
constexpr auto zero = [](const auto &) {
  return [](const auto &x) { return x; };
};

constexpr auto succ = [](const auto &n) {
  return [&n](const auto &f) {
    return [&n, &f](const auto &x) { return f(n(f)(x)); };
  };
};

constexpr auto one = succ(zero);

constexpr auto pred = [](const auto &n) {
  return [&n](const auto &f) {
    return [&n, &f](auto x) {
      return n([&f](const auto &g) {
        return [&f, g](const auto &h) { return h(g(f)); };
      })([x](const auto &u) { return x; })([](const auto &a) { return a; });
    };
  };
};

namespace test {
constexpr unsigned int convert(const auto &n) {
  return n([](const auto &x) { return x + 1; })(0);
}

void print(const auto &n) { std::println("{}", convert(n)); }
} // namespace test
} // namespace church

int main() {
  using namespace logic;
  using namespace church;

  static_assert(logic::test::convert(_true) == true);
  static_assert(logic::test::convert(_false) == false);
  static_assert(logic::test::convert(_and(_true)(_true)) == true);
  static_assert(logic::test::convert(_and(_true)(_false)) == false);
  static_assert(logic::test::convert(_or(_true)(_true)) == true);
  static_assert(logic::test::convert(_or(_true)(_false)) == true);
  logic::test::print(_true);

  static_assert(church::test::convert(zero) == 0);
  static_assert(church::test::convert(succ(zero)) == 1);
  static_assert(church::test::convert(pred(succ(one))) == 1);
  church::test::print(one);
}
