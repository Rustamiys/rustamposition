1.
Написать консольное приложение, реализующее шифрование/дешифровку по таблице Виженера. В вырожденном случае с использованием односимвольного ключа алгоритм сводится к одноалфавитной подстановке.

Требования к реализации: в качестве кодируемого материала используется файл неограниченной длины; предпочтительно задание имен входных/выходных файлов и пароля в командной строке.

2.
Реализовать диалоговое приложение, позволяющее декодировать информацию, закодированную с помощью многоалфавитной подстановки по таблице Виженера. В качестве источника закодированного текста взять файл, обработанный с помощью программы из первой лабораторной работы.

В основе работы программы - частотный анализ закодированного текста и некоторого эталонного текста на языке источника с учетом предположения о длине использованного пароля (задается в интерфейсе на основе анализа индекса соответствия). По итогам сопоставления результатов частотного анализа для закодированного текста и эталона проводится первичное декодирование, декодированный текст и подобранный пароль отображаются в окне приложения.

Требования к реализации: возможность загрузки произвольных исходных и эталонных текстов; сохранение результата в произвольный файл; возможность перехода к другим зашифрованным текстам и эталонам без завершения приложения; использование стандартного алгоритма sort.
