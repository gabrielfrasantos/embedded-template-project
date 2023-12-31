# embedded-template-project

<div align="center">

[![Continuous Integration](https://github.com/gabrielfrasantos/embedded-template-project/actions/workflows/ci.yml/badge.svg)](https://github.com/gabrielfrasantos/embedded-template-project/actions/workflows/ci.yml)
[![Linting & Formatting](https://github.com/gabrielfrasantos/embedded-template-project/actions/workflows/linting-formatting.yml/badge.svg)](https://github.com/gabrielfrasantos/embedded-template-project/actions/workflows/linting-formatting.yml)
[![Static Analysis](https://github.com/gabrielfrasantos/embedded-template-project/actions/workflows/static-analysis.yml/badge.svg)](https://github.com/gabrielfrasantos/embedded-template-project/actions/workflows/static-analysis.yml)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=gabrielfrasantos_embedded-reference-project&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=gabrielfrasantos_embedded-reference-project)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=gabrielfrasantos_embedded-reference-project&metric=coverage)](https://sonarcloud.io/dashboard?id=gabrielfrasantos_embedded-reference-project)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=gabrielfrasantos_embedded-reference-project&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=gabrielfrasantos_embedded-reference-project)

[![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://choosealicense.com/licenses/mit/)
[![OpenSSF Scorecard](https://api.securityscorecards.dev/projects/github.com/gabrielfrasantos/embedded-template-project/badge)](https://securityscorecards.dev/viewer/?uri=github.com/gabrielfrasantos/embedded-template-project)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/6667/badge)](https://bestpractices.coreinfrastructure.org/projects/6667)

</div>

**Description**: embedded-template-project is a base project which contains all submodules related to embedded development.

## Dependencies

EmIL requires:
- A recent C++ compiler that supports C++17 at minimum (for a host build it should support std::filesystem).
- CMake 3.24 or higher.

EmIL is know to build under the following configurations:
- Windows from Visual Studio 2019 onwards.
- Linux from GCC 7 onwards.
- OSX from XCode 11 and target platform 10.15 onwards.

## How to build the software

EmIL can be built by-itself, for example to execute the included micro-tests, or it can be built as part of a larger project. This paragraph describes how to build EmIL by-itself.

```
cmake -B Build
cmake --build Build
```

## How to test the software

After EmIL has been built. The included automated tests can be run with CTest like so:

```
ctest -D Experimental -C Debug
```

## Code examples

Code examples can be found under the [examples](examples) folder.

## Documentation

Documentation is available on [gabrielfrasantos.github.io/embedded-template-project](https://gabrielfrasantos.github.io/embedded-template-project/).

## Contributing

[![Conventional Commits](https://img.shields.io/badge/Conventional%20Commits-1.0.0-%23FE5196?logo=conventionalcommits&logoColor=white)](https://conventionalcommits.org)

embedded-template-project uses semantic versioning and conventional commits.

Please refer to our [Contributing](CONTRIBUTING.md) guide when you want to contribute to this project.

## License

embedded-template-project is licensed under the [MIT](https://choosealicense.com/licenses/mit/) license. See [LICENSE file](LICENSE.md).
