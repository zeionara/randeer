# randeer

<p align="center">
    <img src="assets/images/logo.png"/>
</p>

A simple randomization library

## Prerequisites

If you don't have `cmake` installed, install it using the following command:

```sh
sudo apt-get update && sudo apt-get install cmake clangd
```

## Build

### Automatically

To install the application a provided script can be used:

```sh
tools/init.sh
```

After changing the library source code, use `tools/install.sh` script to reinstall the project without regenerating a `Makefile`. Conversely, to generate a `Makefile` without recompiling the project, use `tools/cmake.sh` script.

### Manually

1. Generate a `Makefile`:

```sh
cmake -B build
```

2. Compile and install the library

```sh
sudo make install -C build
```

The library will be available at `/usr/lib/librandeer.so`

## Test

### Automatically

```sh
./tools/test.sh
```

### Manually

After building the project, tests can be run using the following command:

```sh
ctest --test-dir build
```

## Clean up

To delete compiled files, remove the `build` folder. It will be recreated automatically on `Makefile` generation:

```sh
rm -rf build
```

## Architecture

The following UML class diagram contains description of the `randeer/state` subpackage. The subpackage contains classes for representing randomizer state which can be used for sampling integers.

```mermaid
classDiagram
direction TB

RandomizationState~T~ <|-- DefaultRandomizationState~T~
RandomizationState~T~ <|-- LcgRandomizationState~T~
LcgRandomizationState~T~ <|-- JavaLikeLcgRandomizationState~T~
class RandomizationState~T~ {
    -sample(): RandomState
    +RandomState state
    +reset(RandomState seed)
    +sample(): T
    +sample(T max): T
    +sample(T min, T max): T
}
class DefaultRandomizationState~T~ {
    +reset(RandomState seed)
    -sample(): RandomState
}
class LcgRandomizationState~T~ {
    +RandomState multiplier
    +RandomState increment
    +RandomState modulus
    -sample(): RandomState
}
class JavaLikeLcgRandomizationState~T~ {
    +RandomState multiplier = 25214903917
    +RandomState increment = 11
    +RandomState modulus = 281474976710656
}
```

The next UML class diagram demonstrates the implamented randomizers.

```mermaid
classDiagram
direction TB

RandomizationState~T~ -- Randomizer~T~: state
RandomizationTask -- Randomizer~T~: task
Randomizer~T~ <|-- LoopingRandomizer~T~
Randomizer~T~ <|-- ShiftingRandomizer~T~
Randomizer~T~ <|-- ConstrainedShiftingRandomizer~T~

LoopingRandomizer~T~ -- InIntervalExcludingLoopingRandomizationTaskContext~T~: context
ShiftingRandomizer~T~ -- InIntervalExcludingShiftingRandomizationTaskContext~T~: context
ConstrainedShiftingRandomizer~T~ -- InIntervalExcludingConstrainedShiftingRandomizationTaskContext~T~: context

class RandomizationState~T~ {
    -sample(): RandomState
    +RandomState state
    +reset(RandomState seed)
    +sample(): T
    +sample(T max): T
    +sample(T min, T max): T
}

class RandomizationTask {
    <<enum>>
    IN_INTERVAL_EXCLUDING
}

class Randomizer~T~ {
    -void* context
    +next(): T
    +setTask(RandomizationTask task, void* context)
    +initNextInIntervalExcludingContext(T min, T max, T* excluded, long length)*
    +nextInIntervalExcluding()*: T
}

class InIntervalExcludingLoopingRandomizationTaskContext~T~ {
    +T diff
    +T min
    +unordered_set~T~ excludedItems
}

class LoopingRandomizer~T~ {
    +initNextInIntervalExcludingContext(T min, T max, T* excluded, long length)
    +nextInIntervalExcluding(): T
}

class InIntervalExcludingShiftingRandomizationTaskContext~T~ {
    T min
    T maxShifted
    T* excludedItems
    long nExcluded

    T smallestExcluded
    T greatestExcluded

    T greatestExcludedMinusNexcluded
}

class ShiftingRandomizer~T~ {
    +initNextInIntervalExcludingContext(T min, T max, T* excluded, long length)
    +nextInIntervalExcluding(): T
}

class InIntervalExcludingConstrainedShiftingRandomizationTaskContext~T~ {
    T min
    T maxShifted
    T* excludedItems
    long nExcluded

    T smallestExcluded
    T greatestExcluded

    T greatestExcludedMinusNexcluded
}

class ConstrainedShiftingRandomizer~T~ {
    +initNextInIntervalExcludingContext(T min, T max, T* excluded, long length)
    +nextInIntervalExcluding(): T
}
```

The following diagram depicts the structure of the `randeer/utils` subpackage:

```mermaid
classDiagram
direction TB

class Sampling {
    sampleN(long n, callable sample)
}

class Collection {
    toSet(T* items, long length): unordered_set~T~
    sortAndShift(T* items, long& length, T offset)
}
```

There is also a list of functions provided through static library interface. The functions can be grouped by containing file and listed as follows:

```mermaid
classDiagram
direction LR

Main -- RandomizerType
LcgLooping -- Lcg

class Lcg {
    long lastNumber
    long randomizerSeed
    random(): long
}

class DefaultLooping {
    sample_default_by_looping(long min, long max, long* excluded, long length)
    sample_default_n_by_looping_without_init(long n, long min, long max, long* excluded, long length)
    sample_default_n_by_looping_with_init(long n, long min, long max, long* excluded, long length)
}

class DefaultLoopingUsingObjects {
    sample_default_by_looping_using_objects(long min, long max, long* excluded, long length)
    sample_default_n_by_looping_without_init_using_objects(long n, long min, long max, long* excluded, long length)
    sample_default_n_by_looping_with_init_using_objects(long n, long min, long max, long* excluded, long length)
}

class LcgLooping {
    sample_lcg_by_looping(long min, long max, long* excluded, long length)
    sample_lcg_n_by_looping_without_init(long n, long min, long max, long* excluded, long length)
    sample_lcg_n_by_looping_with_init(long n, long min, long max, long* excluded, long length)
}

class RandomizerType {
    <<enum>>
    DEFAULT_LOOPING
    JAVA_LOOPING
    DEFAULT_SHIFTING
}

class Main {
    init(long id, long seed, RandomizerType type)
    init_in_interval_excluding_task(long id, long min, long max, long* excluding, long length)
    next(long id): long
}

class DefaultShiftingUsingObjects {
    sample_default_by_shifting_using_objects(long min, long max, long* excluded, long length)
    sample_default_n_by_shifting_without_init_using_objects(long n, long min, long max, long* excluded, long length)
    sample_default_n_by_shifting_with_init_using_objects(long n, long min, long max, long* excluded, long length)
}

class DefaultConstrainedShiftingUsingObjects {
    sample_default_by_constrained_using_objects(long min, long max, long* excluded, long length)
    sample_default_n_by_constrained_shifting_without_init_using_objects(long n, long min, long max, long* excluded, long length)
    sample_default_n_by_constrained_shifting_with_init_using_objects(long n, long min, long max, long* excluded, long length)
}
```

The following diagram describes communication between user and system during random numbers generation using objective interface:

<p align="center">
    <img src="assets/diagrams/communication.jpg" alt="communication diagram"/>
</p>
