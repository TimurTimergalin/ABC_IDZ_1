# ИДЗ №1

**Выполнил:** Тимергалин Тимур Маратович, группа БПИ227

## Условие

**Вариант 20:** Сформировать массив B из элементов массива A перестановкой местами минимального и первого элементов.

## Решение

### Содержание

**Внимание:** эмулятор *RARS* работает с файлами кодировки *cp1251*, которая некорректно отображается в браузере. Скриптом  *convert_encoding.py* файлы были перекодированы в *utf-8*, результат лежит в папке *utf8*.

Решение состоит из следующих файлов:

- **mfunc.inc** - макрос-библиотека с одним макросом `func`, предназначенным для автоматической генерации определений подпрограмм.

- **convenience.inc** - макрос-библиотека для "quality-of-life" макросами - 2 вариации макроса `exit` для завершения работы программы.

- **idz1.inc** - библиотека макросов (и, формально, подпрограмм), в которой реализована вся содержательная часть домашнего задания, а именно подпрограммы:

  - `_input`, считывающая массив из консоли и возвращающая его размер;
  - `_createB`, копирующая содержимое одного массива в другой, параллельно ища адрес минимального массива в результирующем массиве, и возвращающая этот адрес;
  - `_swap`, меняющая местами первый элемент массива и элемент по данному адресу;
  - `_print`, выводящая содержимое массива в консоль;

  Для каждой вышеперечисленной подпрограммы написан макрос их вызова. Также в библиотеке представлен макрос `mmain`, выполняющий поставленную в условии задачу на заранее созданном массиве.

- **idz1.asm** - основной исполняемый файл, осуществляющий ввод массива из консоли, выполнение поставленной задачи и вывод результата в консоль.

- **idz1_test.asm** - файл с тестами. В нем представлены 4 тестовых случая, а также реализованы следующие компоненты:

  - Подпрограмма `_compare`, проверяющая пару массивов на поэлементное равенство, а также макрос для её удобного вызова;
  - Макрос `testcase`, запускающий проверку корректности программы на определенных входных данных.
