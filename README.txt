* для работы проекта нужно отформотировать файл config.json
* в поля "files" нужно внести пути к файлам по которым нужно производить поиск

** в файл request.json нужно добавить слова для поиска
** в поле "requests" нужно добавить слова через запятую как указно в файле

*** далее запускаем проект в main

*** ответы будут сформированы в файле "answers"
*** флаг false покажет отсутсвие слова, флаг true покажет искомое слово.
*** docid указывает на номер файла из документа config.json в соответвии с его порядковым номером
*** rank указывает на то как часто искомое слово встречается в файле