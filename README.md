# mettle

[![Latest release][release-image]][release-link]
[![Documentation][documentation-image]][documentation-link]
[![Build status][ci-image]][ci-link]

**mettle** is a "batteries included" unit testing framework for C++17. Its
mission is to provide a full toolbox to address your testing needs and to look
good doing it.

## Features

#### Build your own assertions

Expectations (assertions) are defined using composable matchers that
automatically generate human-readable output, ensuring even complex objects are
easy to test.

#### Nest your tests

Suites group your tests together and can be nested as deeply as you need,
so you can use their hierarchy to set up and tear down your fixtures for you.

#### Don't repeat yourself

Type- and value-parameterized tests let you write your tests once and apply them
to multiple implementations or preconditions.

#### Aggregate everything

The `mettle` unified test runner makes it a snap to write multiple, independent
test files – even ones running completely different kinds of tests – and
aggregate them into a single list of results.

## A Brief Example

A picture is worth a thousand words, and code's almost as good (I'm sure it's
worth at least 100 words), so let's take a look at a test file:

```c++
#include <mettle.hpp>
using namespace mettle;

suite<> basic("a basic suite", [](auto &_) {

  _.test("a test", []() {
    expect(true, equal_to(true));
  });

  for(int i = 0; i < 4; i++) {
    _.test("test number " + std::to_string(i), [i]() {
      expect(i % 2, less(2));
    });
  }

  subsuite<>(_, "a subsuite", [](auto &_) {
    _.test("a sub-test", []() {
      expect(true, equal_to(true));
    });
  });

});
```

## License

This library is licensed under the [BSD 3-Clause license](LICENSE).

[release-image]: https://img.shields.io/github/release/jimporter/mettle.svg
[release-link]: https://github.com/jimporter/mettle/releases/latest
[documentation-image]: https://img.shields.io/badge/docs-mettle-blue.svg
[documentation-link]: https://jimporter.github.io/mettle/
[ci-image]: https://github.com/jimporter/mettle/workflows/build/badge.svg
[ci-link]: https://github.com/jimporter/mettle/actions?query=branch%3Amaster+workflow%3Abuild
