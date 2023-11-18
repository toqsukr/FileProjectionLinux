# Приложение для проецирования файлов для Linux

Это приложение для проецирования файлов для Linux с двумя функциями - клиентской и серверной.

## Серверная функция
Сервер создает файл на диске, а затем проецирует его в память. Затем он записывает информацию в файл и ждет, пока клиент прочтет ее. Как только клиент прочитает информацию, сервер отменяет проекцию и удаляет файл.

### Меню сервера
- "Project file": Инициирует процесс проецирования файла
- "Write data": Позволяет серверу записывать данные в проецируемый файл
- "Exit": Завершает работу серверного приложения

## Клиентская функция
Клиент открывает файл, проецирует его в память и ожидает возможности его чтения. Как только файл становится доступен для чтения, клиент считывает данные и выводит результат. По завершении своей задачи клиент отменяет проецирование.

### Меню клиента
- "Project file": Инициирует процесс проецирования файла
- "Read data": Позволяет клиенту считывать данные из запроектированного файла
- "Exit": Завершает работу клиентского приложения

## Использование
Чтобы использовать это приложение, сначала запустите серверное приложение, а затем клиентское приложение. Используйте меню для выбора необходимого действия.

Примечание: Как клиентское, так и серверное приложения должны быть запущены на одном компьютере для обеспечения надлежащей функциональности.

## Установка
Это приложение можно установить в системе Linux, загрузив исходный код и скомпилировав его с помощью компилятора C++. После компиляции серверный и клиентский исполняемые файлы могут запускаться отдельно.
