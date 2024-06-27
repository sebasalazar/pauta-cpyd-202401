#include "file_service.h"

FileService::FileService() {
    const std::string tmpDirectory = createTempDirectory();
    std::cout << "Carpeta temporal " << tmpDirectory << std::endl;
}

FileService::~FileService() {
    if (!fileMap.empty()) {
        for (std::pair<const std::string, std::ofstream>& pair : fileMap) {
            pair.second.close();
        }
    }
}

std::vector<std::string> FileService::parseLine(const std::string& line) {
    std::vector<std::string> result;
    std::string field;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            // Cambia el estado de dentro/fuera de comillas
            insideQuotes = !insideQuotes;
        } else if (c == ';' && !insideQuotes) {
            // Si encontramos un delimitador y no estamos dentro de comillas, es el fin de un campo
            result.push_back(field);
            field.clear();
        } else {
            // Cualquier otro carácter se añade al campo actual
            field += c;
        }
    }
    // Añadir el último campo al resultado
    result.push_back(field);

    // Eliminar las comillas de los campos
    for (std::string& str : result) {
        if (!str.empty() && str.front() == '"' && str.back() == '"') {
            str = str.substr(1, str.size() - 2);
        }
    }

    return result;
}

void FileService::removeDirectory(const std::string& dirPath) {
    if (rmdir(dirPath.c_str()) == 0) {
        std::cout << "Directorio eliminado: " << dirPath << std::endl;
    } else {
        std::cerr << "Error al eliminar el directorio o el directorio no existe: " << dirPath << std::endl;
    }
}

std::string FileService::createDirectory(const std::string& dirPath) {
    std::string directory;
    if (mkdir(dirPath.c_str(), 0755) == 0) {
        char absPath[PATH_MAX];
        if (realpath(dirPath.c_str(), absPath)) {
            directory = std::string(absPath);
        } else {
            std::cerr << "Error al obtener la ruta absoluta del directorio: " << dirPath << std::endl;
        }
    } else {
        std::cerr << "Error al crear el directorio o el directorio ya existe: " << dirPath << std::endl;
    }
    return directory;
}

std::string FileService::createTempDirectory() {
    removeDirectory(utem::tempPath);
    return createDirectory(utem::tempPath);
}

void FileService::write(int ym, std::string& sku, double amount) {
    std::string filename(utem::tempPath + "/" + std::to_string(ym));
    if (fileMap.find(filename) == fileMap.end()) {
        fileMap[filename] = std::ofstream(filename, std::ios::out | std::ios::app);
        if (!fileMap[filename].is_open()) {
            std::cerr << "Error abriendo el archivo: " << filename << std::endl;
            return;
        }
    }

    if (fileMap[filename].is_open()) {
        fileMap[filename] << sku << ";" << amount << std::endl;
    } else {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
    }
}

int FileService::parseCsvLine(const std::string& line) {
    int code = 0;
    std::vector<std::string> fields = parseLine(line);
    if (fields.size() == 10) {
        std::string sku = fields[6];
        if (sku != utem::zeroStr) {
            std::string created = fields[0];
            double amount = std::stod(fields[9]);

            if (amount > 0) {
                YearMonth ym = utem::parseYearMonth(created);
                code = ym.GetYearMonth();
                Product producto = Product(sku, amount);
                write(code, sku, amount);

            }
        }
    }
    fields.clear();
    return code;
}
