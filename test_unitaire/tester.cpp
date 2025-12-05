#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::filesystem::path appOutputs = "../data/outputs";

class Tester {
  private:
    std::filesystem::path inputs;
    std::filesystem::path outputs;
    int iterationCount;

    std::string cleanLine(const std::string &line) const {
        std::string result;
        for (char c : line) {
            if (c == '0' || c == '1') {
                result += c;
            }
        }
        return result;
    }

    std::vector<std::vector<std::string>>
    extractMatrices(std::ifstream &file) const {
        std::vector<std::vector<std::string>> matrices;
        std::vector<std::string> currentMatrix;
        std::string line;

        while (std::getline(file, line)) {
            std::string cleaned = cleanLine(line);

            if (!cleaned.empty()) {
                currentMatrix.push_back(cleaned);
            } else if (!currentMatrix.empty()) {
                matrices.push_back(currentMatrix);
                currentMatrix.clear();
            }
        }

        if (!currentMatrix.empty()) {
            matrices.push_back(currentMatrix);
        }

        return matrices;
    }

    bool compareMatrices(const std::vector<std::string> &mat1,
                         const std::vector<std::string> &mat2,
                         int matrixIndex) const {
        if (mat1.size() != mat2.size()) {
            std::cout << "Matrice " << matrixIndex
                      << ": nombre de lignes different (" << mat1.size()
                      << " vs " << mat2.size() << ")" << std::endl;
            return false;
        }

        for (size_t i = 0; i < mat1.size(); ++i) {
            if (mat1[i] != mat2[i]) {
                std::cout << "Matrice " << matrixIndex << ", ligne " << (i + 1)
                          << " differente" << std::endl;
                std::cout << "Attendu: " << mat1[i] << std::endl;
                std::cout << "Obtenu: " << mat2[i] << std::endl;
                return false;
            }
        }

        return true;
    }

  public:
    Tester(const std::filesystem::path &in, const std::filesystem::path &out,
           int iterations)
        : inputs(in), outputs(out), iterationCount(iterations) {}

    bool folderExists(const std::filesystem::path &folder) const {
        if (!std::filesystem::exists(folder) ||
            !std::filesystem::is_directory(folder)) {
            std::cerr << "Le dossier '" << folder << "' n'existe pas."
                      << std::endl;
            return false;
        }
        return true;
    }

    bool test(std::filesystem::path inputFile) {
        std::filesystem::path generatedFile =
            appOutputs / (inputFile.stem().string() + "_out.txt");
        std::filesystem::path expectedFile =
            outputs / (inputFile.stem().string() + "_out.txt");

        std::ifstream genStream(generatedFile);
        std::ifstream expStream(expectedFile);

        if (!genStream.is_open() || !expStream.is_open()) {
            std::cerr << "Impossible d'ouvrir les fichiers pour: "
                      << inputFile.filename() << std::endl;
            return false;
        }

        auto genMatrices = extractMatrices(genStream);
        auto expMatrices = extractMatrices(expStream);

        genStream.close();
        expStream.close();

        if (genMatrices.size() != expMatrices.size()) {
            std::cout << "Echec du test pour : " << inputFile.filename()
                      << std::endl;
            std::cout << "Nombre de matrices differents : "
                      << genMatrices.size() << " vs " << expMatrices.size()
                      << std::endl;
            return false;
        }

        bool success = true;
        for (size_t i = 0; i < genMatrices.size(); ++i) {
            if (!compareMatrices(expMatrices[i], genMatrices[i], i + 1)) {
                success = false;
                break;
            }
        }

        if (success) {
            std::cout << "Test reussi pour : " << inputFile.filename() << " ("
                      << genMatrices.size() << " matrices)\n"
                      << std::endl;
        } else {
            std::cout << "Echec du test pour : " << inputFile.filename() << "\n"
                      << std::endl;
        }

        return success;
    }

    void execute() {
        if (!this->folderExists(inputs) || !this->folderExists(outputs)) {
            return;
        }

        int totalTests = 0;
        int passedTests = 0;

        for (const auto &entry : std::filesystem::directory_iterator(inputs)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                std::filesystem::path inputFile = entry.path();
                std::filesystem::path expectedOut =
                    outputs / (inputFile.stem().string() + "_out.txt");

                if (!std::filesystem::exists(expectedOut)) {
                    std::cout << "Fichier de sortie manquant pour : "
                              << inputFile.filename() << std::endl;
                    continue;
                }

                std::string cmd = "../build/JeuDeLaVie -lc " +
                                  inputFile.string() + " -ic " +
                                  std::to_string(iterationCount) + " -g -it 1";
                system(cmd.c_str());

                totalTests++;
                if (this->test(inputFile)) {
                    passedTests++;
                }
            }
        }

        std::cout << "\nResultats: " << passedTests << "/" << totalTests
                  << " tests reussis\n"
                  << std::endl;
    }
};

int main() {
    Tester tester("inputs", "expectedOutputs", 10);
    tester.execute();
    return 0;
}