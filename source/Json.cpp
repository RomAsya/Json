#include "Json.hpp"


Json::Json(const std::string& s) {
	int count = 0;
	switch (s[count]) {
		case '{': {
		while (s[count] != '}') {
			std::string key_str;
			std::string mean_str;
			while (s[count] != '"') count++;
			count++;
			while (s[count] != '"') {
				key_str += s[count];
				count++;
			}
			key_code.push_back(key_str);
			for (int i = 0; i < 4; i++) count++;
			if (s[count] == '{') {
				while (s[count] != '}') {
					mean_str += s[count];
					count++;
				}
				mean_str += s[count];
				count++;
				Json mean(mean_str);
				mean_code.push_back(mean);
				continue;
			}
			if (s[count] == '[') {
				while (s[count] != ']') {
					mean_str += s[count];
					count++;
				}
				mean_str += s[count];
				count++;
				Json mean(mean_str);
				mean_code.push_back(mean);
				continue;
			}
			if (s[count] == '"') {
				count++;
				while (s[count] != '"') {
					mean_str += s[count];
					count++;
				}
				count++;
				mean_code.push_back(mean_str);
				continue;
			}
			if ((s[count] == 'f') || (s[count] == 't')) {
				if (s[count] == 'f') mean_code.push_back(false);
				else mean_code.push_back(true);
				while ((s[count] != ',') && (s[count] != '}')) {
					count++;
				}
				continue;
			}
			if ((s[count] == '1') || (s[count] == '2') || (s[count] == '3') || (s[count] == '4') || (s[count] == '5') || (s[count] == '6') || (s[count] == '7') || (s[count] == '8') || (s[count] == '9') || (s[count] == '0')) {
				while ((s[count] != ',') && (s[count] != '}')) {
					mean_str += s[count];
					count++;
				}
				double mean = atof(mean_str.c_str());
				mean_code.push_back(mean);
				continue;
			}
		}
	} break;
		case '[': {
				std::string mean_str;
				count++;
				if (s[count] == '{') {
					while (s[count] != ']') {
						while (s[count] != '}') {
							mean_str += s[count];
							count++;
						}
						mean_str += s[count];
						count++;
						Json mean(mean_str);
						array_code.push_back(mean);
						mean_str = "";
						if (s[count] == ',') {
							count++;
							count++;
						}
					}
				}
				if (s[count] == '[') {
					while (s[count] != ']') {
						while (s[count] != ']') {
							mean_str += s[count];
							count++;
						}
						mean_str += s[count];
						count++;
						if (s[count] == ',') {
							count++;
							count++;
						}
						Json mean(mean_str);
						array_code.push_back(mean);
						mean_str = "";
					}
				}
				if (s[count] == '"') {
					while (s[count] != ']') {
						count++;
						while (s[count] != '"') {
							mean_str += s[count];
							count++;
						}
						count++;
						if (s[count] == ',') {
							count++; 
							count++;
						}
						array_code.push_back(mean_str);
						mean_str = "";
					}
				}
				if ((s[count] == 'f') || (s[count] == 't')) {
					while (s[count] != ']') {
						if (s[count] == 'f') array_code.push_back(false);
						else array_code.push_back(true);
						while ((s[count] != ',') && (s[count] != ']')) {
							count++;
						}
						if (s[count] == ',') {
							count++;
							count++;
						}
					}
				}
				if ((s[count] == '1') || (s[count] == '2') || (s[count] == '3') || (s[count] == '4') || (s[count] == '5') || (s[count] == '6') || (s[count] == '7') || (s[count] == '8') || (s[count] == '9') || (s[count] == '0')) {
					while (s[count] != ']') {
						while ((s[count] != ',') && (s[count] != ']')) {
							mean_str += s[count];
							count++;
						}
						double mean = atof(mean_str.c_str());
						array_code.push_back(mean);
						mean_str = "";
						if (s[count] == ',') {
							count++;
							count++;
						}
					}
				}
		} break;
	}
}

bool Json::is_array() const {
	if (array_code.size() > 0) return true;
	for (int i = 0; i < mean_code.size(); i++) {
		if (mean_code[i].type() == typeid(Json)) {
			Json json = std::any_cast<Json>(mean_code[i]);
			if (json.is_array()) return true;
		}
	}
	return false;
}

bool Json::is_object() const {
	if (mean_code.size() > 0) return true;
	for (int i = 0; i < array_code.size(); i++) {
		if (array_code[i].type() == typeid(Json)) {
			Json json = std::any_cast<Json>(array_code[i]);
			if (json.is_object()) return true;
		}
	}
	return false;
}

std::any& Json::operator[](const std::string& key) {
	if (array_code.size() > 0) {
		throw 1;
	}
	for (int i = 0; i < key_code.size(); i++) {
		if (std::any_cast<std::string>(key_code[i]) == key)
			return mean_code[i];
	}
}

std::any Json::operator[](int index) {
	if (mean_code.size() > 0) {
		throw 1;
	}
	return array_code[index];
}
