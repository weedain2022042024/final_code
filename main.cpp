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
    cout << "\t\t\t\t\t                  �� �� ��                " << endl;
    cout << "\t\t\t\t\t                                          " << endl;
    cout << "\t\t\t\t\t==========================================" << endl;

    cout << "\n\n";
    //cout << "\t\t\t\t\t==========================================" << endl;
    cout << "\t\t\t\t\t          ���¼ҽ�����������Ʈ\n";
    cout << "\t\t\t\t\t            ������: �ѹ��̵�\n\n\n";
    //cout << "\t\t\t\t\t==========================================\n" << endl;
    // ����ڰ� ���͸� ���� ������ ���
    cout << "\t\t\t\t\t        ���͸� ������ ����մϴ�...";
    cin.get();

}


int main() {
    printinitview();

    // �޴� �ɼ� ����
    vector<string> options = { "�̹��� �Է�", "�ؽ�Ʈ �Է�", "���� �Է�" };
    int currentselection = 0;

    // �޴� ���� �ݺ�
    while (true) {
        // �޴� ���
        system("cls"); // �ܼ� â �����
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t==========================================" << endl;
        cout << "\t\t\t\t\t   ����ϰ��� �ϴ� ����� �����ϼ���:\n";
        cout << "\t\t\t\t\t==========================================" << endl;
        cout << "\n";
        for (int i = 0; i < options.size(); ++i) {
            if (i == currentselection) {

                cout << "\t\t\t\t\t\t\t" << "> " << options[i] << " <" << endl; // ���õ� �׸��� ����
            }
            else {
                cout << "\t\t\t\t\t\t\t" << options[i] << endl;
            }
        }

        int ch = _getch(); // Ű �Է� �ޱ�
        if (ch == 224) { // ȭ��ǥ Ű �Է�
            switch (_getch()) {
            case 72: // �� ȭ��ǥ Ű
                currentselection = (currentselection - 1 + options.size()) % options.size();
                break;
            case 80: // �Ʒ� ȭ��ǥ Ű
                currentselection = (currentselection + 1) % options.size();
                break;
            }
        }
        else if (ch == 13) { // ���� Ű �Է�
            break;
        }
    }

    // ���õ� ��� ����
    switch (currentselection) {
    case 0: {
        system("cls"); // ȭ�� �����
        std::string image_path = "test.png";
        std::string ocr_text = performOCR(image_path);
        if (!ocr_text.empty()) {
            std::cout << "OCR ���:\n" << ocr_text << std::endl;
            summarizeText(ocr_text);
        }
        // ������� �������� ����
        while (true) {
            cout << "\n����Ϸ��� 'a', �����Ϸ��� 'e', ���� �޴��� ������ 'q'�� ��������: ";
            char choice = _getch();
            if (choice == 'a') {
                std::string image_path = "test.png";
                std::string ocr_text = performOCR(image_path);
                if (!ocr_text.empty()) {
                    std::cout << "OCR ���:\n" << ocr_text << std::endl;
                    summarizeText(ocr_text);
                }
            }
            else if (choice == 'e') {
                return 0; // ����
            }
            else if (choice == 'q') {
                system("cls");
                main(); // ���� �޴��� ���ư���
            }
        }
        break;
    }
    case 1: {
        // ����ڷκ��� �ؽ�Ʈ �Է¹ޱ�
        std::cout << "\n����� �ؽ�Ʈ �Է�:\n";
        std::string userinput;
        //std::cout << "\t\t\t\t\t\t\t";
        std::getline(std::cin, userinput);
        cout << endl;
        summarizeText(userinput);
        // ������� �������� ����
        while (true) {
            cout << "\n����Ϸ��� 'a', �����Ϸ��� 'e', ���� �޴��� ������ 'q'�� ��������: ";
            char choice = _getch();
            if (choice == 'a') {
                std::cout << "\n����� �ؽ�Ʈ �Է�:\n";
                std::string userinput;
                std::getline(std::cin, userinput);
                cout << endl;
                summarizeText(userinput);
            }
            else if (choice == 'e') {
                return 0; // ����
            }
            else if (choice == 'q') {
                system("cls");
                main(); // ���� �޴��� ���ư���
            }
        }
        break;
    }
    case 2: {
        // ���� ��� �Է� �޾Ƽ� ���
        cout << "\n���� ��� �Է�:\n";
        string filepath;
        getline(cin, filepath);
        //cout << endl;
        summarizeFile(filepath);
        // ������� �������� ����
        while (true) {
            cout << "\n����Ϸ��� 'a', �����Ϸ��� 'e', ���� �޴��� ������ 'q'�� ��������: ";
            char choice = _getch();
            if (choice == 'a') {
                cout << "\n���� ��� �Է�:\n";
                string filepath;
                getline(cin, filepath);
                //cout << endl;
                summarizeFile(filepath);
            }
            else if (choice == 'e') {
                return 0; // ����
            }
            else if (choice == 'q') {
                system("cls");
                main(); // ���� �޴��� ���ư���
            }
        }
        break;
    }
    default:
        std::cerr << "�߸��� �Է��Դϴ�." << std::endl;
        return -1;
    }
    return 0;
}
