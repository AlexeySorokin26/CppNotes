# list comprehension списочное выражение (включение) это способ компактно описать операции обработки списков (массивов упорядоченных наборов данных)

# without list comprehension we should do this
fruits = ["apple", "banana", "cherry", "kiwi", "mango"]
newlist = []

for x in fruits:
  if "a" in x:
    newlist.append(x)

print(newlist)

# with 
fruits = ["apple", "banana", "cherry", "kiwi", "mango"]

newlist = [x for x in fruits if "a" in x]

print(newlist)

# syntax 
# newlist = [expression for item in iterable if condition == True]
# name in expresssion should has be "item"
# we just can do smth with this item like here 
newlist = [x.upper() for x in fruits]

# function any accept iterable object and return True if at least one of them is ok

# Generator experession генераторное выражение это по смыслу тоже списочное выражение только поведение отличается 
# idea use lazy evalutation [..] computes all elements and keep them in memory; (..) only keeps how to compute (recept) and compute if someone asks  

gen = (ln.upper() for ln in lines)

# то же самое:
def make_gen():
    for ln in lines:
        yield ln.upper()
gen = make_gen()

# В обоих случаях в момент создания gen ни одна строка ещё не обработана. ln.upper() не вызвался ни разу. Функция как бы «заморожена» на старте.

# we can check it 
def loud(x):
    print(f"обрабатываю {x}")
    return x * 2

gen = (loud(x) for x in [1, 2, 3])
print("генератор создан")   # тут ещё ничего не напечаталось про обработку!

print(next(gen))            # только сейчас: "обрабатываю 1", потом 2
print(next(gen))            # "обрабатываю 2", потом 4

# 3 ways to get next element 
gen = (x * 2 for x in [1, 2, 3])

# 1. вручную через next()
next(gen)   # 2
next(gen)   # 4
next(gen)   # 6
next(gen)   # StopIteration — элементы кончились

# 2. циклом for (он сам зовёт next и ловит StopIteration)
for val in gen:
    print(val)

# 3. передать в функцию, которая умеет итерировать
sum(x * 2 for x in [1, 2, 3])    # 12
any(...), all(...), list(...), max(...), " ".join(...)