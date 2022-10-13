<!--
 * @Author: avert-win
 * @Date: 2022-05-02 00:02:30
 * @LastEditTime: 2022-05-08 21:45:56
 * @FilePath: /ProgramDaily/pythonSample/Type.md
 * @Description: 简介
 * @LastEditors: avert-ubt
-->
https://blog.daftcode.pl/first-steps-with-python-type-system-30e4296722af
https://blog.daftcode.pl/covariance-contravariance-and-invariance-the-ultimate-python-guide-8fabc0c24278

- A type is a type checker concept and a class is a runtime concept.

-  Type is defined not only by a set of objects but also by functions/methods that can be used with these objects.

- `Any` has all attributes while `object` has no attrs. So, `Any` can be any type's subtype, but `object` can only be the top type.

使用`mypy`进行静态类型检查。

__type annotation__: 
```py
name: Type = initial_value
def func1(param1: int, param2: str) -> list:
    None
def func2(param2: int) -> Optional[int]:
    func2(func2(3:int))             # mypy error.
    None
```

__subtype__:
```py
class Animal:
    None
class Dog(Animal):
    None

dog: Dog
animal: Animal

animal = dog  # no error by mypy.
dog = animal  # error.
```

__alias__:

```py
from typing import List, Tuple
Id = int
Name = str
Tag = str
Tags = List[str]
Object = Tuple[Id, Name, Tag]
# Instead of `Objects = Tupe[list[Tuple[int, str, str]], List[str]]`
Objects = Tuple[List[Object], Tags]

def detect_id() -> Id:
    None
def detect_object() -> Objects:
    None
```

But mypy cannot distinguish `Name` and `Tag`, so using this way:

```py
from typing import NewType

ItemId = NewType('ItemId', int)
OrderId = NewType('OrderId', int)

def detect_id(id:ItmeId):
    pass
def get_orderId() -> OrderId:
    pass

order_id = get_orderId()
detect_id(order_id)             # mypy error, although require int and given int.
```

### Generic Type

A type that takes other types as parameters in square brackets, like `List`, `Tuple`, `Union`, etc.

### Covariance

Regard generic type of subtypes as generic type of supertypes.

Including `Tuple`, `Union`, return type of `Callable`, and anything that provides something.

```py
class Animal:
    pass
class Dog(Animal):
    pass
# an_animal = Animal()
an_animal:Animal = Animal()
snoopy:Dog = Dog()

animals:Tuple[Animal,...] = (an_animal,snoopy)      # OK.
dogs:Tuple[Dog,...] = (an_animal,snoopy)            # type error.
```

For `Callable`, it's __covariant only in the return type__.

### Contravariant

The contrary term to "covariance": regarding generic type of supertypes as generic type of subtypes. For `callable`, it's __`contravariant` only in the argument types__.

Includinig arguments of `Callable`, and anything that takes something.

For example, we cann't pass `dog_run` as `animal_run` as a callable argument. What that mean is that we cann't make kangaroos running as a dog.

```py
class Animal: ...
class Dog(Animal): ...
class Kangaroo(Animal): ...

def animal_run(animal: Animal) -> None:
    # its type is `Callable[[Animal], None]`
    print('An animal is running!')

def dog_run(dog: Dog) -> None:
    # its type is `Callable[[Dog], None]`
    print('A dog is running!')

def make_animal_run(an_animal: Animal, run_function: Callable[[Animal], None], ) -> None:
    run_function(an_animal)

bob_a_kangaroo: Kangaroo = Kangaroo()

make_animal_run(bob_a_kangaroo, dog_run)  # mypy error: 
# Argument 2 to "make_animal_run" has incompatible type 
#   "Callable[[Dog], None]"; expected "Callable[[Animal], None]"
```

### Invariance

Neither covariant nor contravariant.

Including `List`, `Set`, `Dict`, and many more __mutable__ containers.

For example, `List`:
```py
dogs:List[Dog]
animals:List[Animal]

# not contravariant:
dogs = animals          # error: Cannot assign List[supertype] to List[subtype]

# not covariant:
animals = dogs          # also an error occur.
```