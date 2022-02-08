#include <iostream>
#include <fstream>
#include<string>
#include <ctime>
#include <sstream>
#include "node.h"
#include "hashing.h"
#include "heapSorting.h"
#include <chrono>

int counter = 0;


bool isStopWord(std::string stop[], std::string uwords) {
    for (int j = 0; j < 571; j++) {
        if (uwords == stop[j]) {
            uwords.clear();
            return true;
        }
    }
    return false;
}

template <class Type>
void filter(std::string str, hashing<Type>& hash, std::string stop[]) {
    std::string searchStr = "\"unigramCount\":{";
    std::string unigramWord = "", wordsinUnigrams = "", counts = "";

    size_t startUnigramsIndex = str.find(searchStr) + searchStr.length(), endUnigramsIndex = str.length() - 1;

    bool digitcame = false;
    for (size_t i = startUnigramsIndex; i < endUnigramsIndex; i++) {
        if (wordsinUnigrams.find("\":") == std::string::npos) {
            wordsinUnigrams += str[i];
            //convert lowercase
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] = str[i] + 32;
            }
            //separate punctuations out of the word
            if (std::ispunct(str[i]) && str[i] != '\'') {
                unigramWord += "";
            }
            //dont count words if numbers in it
            else if (std::isdigit(str[i])) {
                unigramWord = "";
                digitcame = true;
            }
            else if (!digitcame) {
                unigramWord += str[i];
            }
        }
        else {
            while (str[i] != ',') {
                counts += str[i++];
                if (counts.find("}}") != std::string::npos) {
                    break;
                }
            }

            if (unigramWord != "") {
                std::string uwords;
                std::stringstream iss(unigramWord);
                while (std::getline(iss, uwords, ' ')) {

                    //no need to check single letters in stopwords.
                    if (uwords.length() > 1 && !isStopWord(stop, uwords)) {
                        hash.insert(uwords, atoi(counts.c_str()));
                        counter++;
                    }

                }
            }
            unigramWord = "";
            wordsinUnigrams = "";
            counts = "";
            digitcame = false;
        }
    }
}

void heapAll(hashing<node>& heapHash) {
    heapSorting<heapnode> hadi;
    heapnode* arry = new heapnode[counter];
    int x = 0; //total unique word number
    node* current;
    for (int i = 0; i < size; i++) {
        current = heapHash.table[i];
        while (current != NULL) {
            arry[x].words = current->getWords();
            arry[x].count = (current->getCount());
            current = current->getLink();
            x++;
        }
    }
   hadi.heapSort(arry, x);
    int top10 = 0;
    int i = 0;
    while (top10 < 10) {
        std::cout << "<" << arry[i].words << "> <" << arry[i].count << ">" << std::endl;
        i++;
        top10++;
    }
    delete[] arry;
}
int main() {
    auto start = std::chrono::steady_clock::now();
    std::string publications("/Users/omniaelmenshawy/Desktop/TermProject/PublicationsDataSet.txt");
    std::string stop("/Users/omniaelmenshawy/Desktop/TermProject/stopwords.txt");
    std::ifstream publications_file(publications);
    std::ifstream stop_file(stop);
    std::string words;
    std::string stopWords[571];
    hashing<node> hash;
//    heapSorting<heapnode> sort;
    if (!publications_file.is_open()) {
        std::cerr << "Could not open the file PublicationsDataSet.txt" << std::endl;
        return EXIT_FAILURE;
    }
    if (!stop_file.is_open()) {
        std::cerr << "Could not open the file stopwords.txt" << std::endl;
        return EXIT_FAILURE;
    }
    if (stop_file.is_open()) {
        for (auto& stopWord : stopWords) {
            stop_file >> stopWord;
        }
    }
    while (std::getline(publications_file, words)) {
        filter(words, hash, stopWords);

    }
    heapAll(hash);
    publications_file.close();
    publications_file.close();
    stop_file.close();
//    clock_t endTime0 = clock();
//    std::cout << std::endl << "Total Elapsed Time: " << (int)(endTime0 - startTime0) /1000 << " seconds" << std::endl;
    auto end =std:: chrono::steady_clock::now(); //gets time at the end
    std:: cout << "Total Elapsed Time: "
    << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() //substract the times
    << "." <<std:: chrono::duration_cast<std::chrono::milliseconds>(end - start).count() % 1000<<" Seconds"  << std::endl;
    return 0;
}

