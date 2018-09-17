#include"json.hpp"

int main() {
	const char * const json_data = R"(
{
    "lastname" : "Ivanov",
    "firstname" : "Ivan",
    "age" : 25,
    "islegal" : false,
    "marks" : [
    	4,5,5,5,2,3
    ],
    "address" : {
    	"city" : "Moscow",
        "street" : "Vozdvijenka"
    }
})";

	Json object(json_data);
	auto marks = std::any_cast<Json>(object["marks"]);
	try {
		std::cout << std::any_cast<std::string>(object["lastname"]) << std::endl;
		std::cout << std::any_cast<bool>(object["islegal"]) << std::endl;
		std::cout << std::any_cast<double>(object["age"]) << std::endl;
		std::cout << std::any_cast<double>(marks[0]) << std::endl;;
		std::cout << std::any_cast<double>(marks[2]) << std::endl;;
		std::cout << std::any_cast<double>(marks[4]) << std::endl;;
	}
	catch (int i) {
		std::cerr << "Error!!!" << std::endl;
	}
	return 0;
}
