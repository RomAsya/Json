class Json {
public:
	std::vector<std::any> key_code;
	std::vector<std::any> mean_code;
	std::vector<std::any> array_code;
	// Конструктор из строки, содержащей Json-данные.
	Json(const std::string& s);
	// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
	bool is_array() const;
	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
	bool is_object() const;
	// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-массивом, генерируется исключение.
	std::any& operator[](const std::string& key);
	// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-объектом, генерируется исключение.
	std::any operator[](int index);
	// Метод возвращает объект класса Json из строки, содержащей Json-данные.
	static Json parse(const std::string& s) {
		Json curr(s);
		return curr;
	};
	// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
	static Json parseFile(const std::string& path_to_file);
};