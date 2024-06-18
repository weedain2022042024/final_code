#include "ocr.h"
#include "summarizer.h"
#include "menu.h"
#include "utils.h"
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

void printinitview() {
    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t==========================================" << endl;
    cout << "\t\t\t\t\t                                          " << endl;
    cout << "\t\t\t\t\t                  세 줄 톡                " << endl;
    cout << "\t\t\t\t\t                                          " << endl;
    cout << "\t\t\t\t\t==========================================" << endl;

    cout << "\n\n";
    //cout << "\t\t\t\t\t==========================================" << endl;
    cout << "\t\t\t\t\t          오픈소스개발프로젝트\n";
    cout << "\t\t\t\t\t            제작자: 뚜벅이들\n\n\n";
    //cout << "\t\t\t\t\t==========================================\n" << endl;
    // 사용자가 엔터를 누를 때까지 대기
    cout << "\t\t\t\t\t        엔터를 누르면 계속합니다...";
    cin.get();

}


int main() {
    printinitview();

    // 메뉴 옵션 설정
    vector<string> options = { "이미지 입력", "텍스트 입력", "문서 입력" };
    int currentselection = 0;

    // 메뉴 선택 반복
    while (true) {
        // 메뉴 출력
        system("cls"); // 콘솔 창 지우기
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t==========================================" << endl;
        cout << "\t\t\t\t\t   사용하고자 하는 기능을 선택하세요:\n";
        cout << "\t\t\t\t\t==========================================" << endl;
        cout << "\n";
        for (int i = 0; i < options.size(); ++i) {
            if (i == currentselection) {

                cout << "\t\t\t\t\t\t\t" << "> " << options[i] << " <" << endl; // 선택된 항목을 강조
            }
            else {
                cout << "\t\t\t\t\t\t\t" << options[i] << endl;
            }
        }

        int ch = _getch(); // 키 입력 받기
        if (ch == 224) { // 화살표 키 입력
            switch (_getch()) {
            case 72: // 위 화살표 키
                currentselection = (currentselection - 1 + options.size()) % options.size();
                break;
            case 80: // 아래 화살표 키
                currentselection = (currentselection + 1) % options.size();
                break;
            }
        }
        else if (ch == 13) { // 엔터 키 입력
            break;
        }
    }

    // 선택된 기능 실행
    switch (currentselection) {
    case 0: {
        system("cls"); // 화면 지우기
        std::string image_path = "test.png";
        std::string ocr_text = performOCR(image_path);
        if (!ocr_text.empty()) {
            std::cout << "OCR 결과:\n" << ocr_text << std::endl;
            summarizeText(ocr_text);
        }
        // 계속할지 종료할지 선택
        while (true) {
            cout << "\n계속하려면 'a', 종료하려면 'e', 이전 메뉴로 가려면 'q'를 누르세요: ";
            char choice = _getch();
            if (choice == 'a') {
                std::string image_path = "test.png";
                std::string ocr_text = performOCR(image_path);
                if (!ocr_text.empty()) {
                    std::cout << "OCR 결과:\n" << ocr_text << std::endl;
                    summarizeText(ocr_text);
                }
            }
            else if (choice == 'e') {
                return 0; // 종료
            }
            else if (choice == 'q') {
                system("cls");
                main(); // 이전 메뉴로 돌아가기
            }
        }
        break;
    }
    case 1: {
        // 사용자로부터 텍스트 입력받기
        std::cout << "\n사용자 텍스트 입력:\n";
        std::string userinput;
        //std::cout << "\t\t\t\t\t\t\t";
        std::getline(std::cin, userinput);
        cout << endl;
        summarizeText(userinput);
        // 계속할지 종료할지 선택
        while (true) {
            cout << "\n계속하려면 'a', 종료하려면 'e', 이전 메뉴로 가려면 'q'를 누르세요: ";
            char choice = _getch();
            if (choice == 'a') {
                std::cout << "\n사용자 텍스트 입력:\n";
                std::string userinput;
                std::getline(std::cin, userinput);
                cout << endl;
                summarizeText(userinput);
            }
            else if (choice == 'e') {
                return 0; // 종료
            }
            else if (choice == 'q') {
                system("cls");
                main(); // 이전 메뉴로 돌아가기
            }
        }
        break;
    }
    case 2: {
        // 파일 경로 입력 받아서 요약
        cout << "\n파일 경로 입력:\n";
        string filepath;
        getline(cin, filepath);
        //cout << endl;
        summarizeFile(filepath);
        // 계속할지 종료할지 선택
        while (true) {
            cout << "\n계속하려면 'a', 종료하려면 'e', 이전 메뉴로 가려면 'q'를 누르세요: ";
            char choice = _getch();
            if (choice == 'a') {
                cout << "\n파일 경로 입력:\n";
                string filepath;
                getline(cin, filepath);
                //cout << endl;
                summarizeFile(filepath);
            }
            else if (choice == 'e') {
                return 0; // 종료
            }
            else if (choice == 'q') {
                system("cls");
                main(); // 이전 메뉴로 돌아가기
            }
        }
        break;
    }
    default:
        std::cerr << "잘못된 입력입니다." << std::endl;
        return -1;
    }
    return 0;
}
